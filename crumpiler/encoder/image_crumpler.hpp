#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Image Crumpler (.crmpg) v2
// ═══════════════════════════════════════════════════════════════════════
// Crossword-puzzle scanner with FUZZY matching:
//   - Every pixel is a start position, 8 directional rays
//   - Pixel strings match if each channel is within ±tolerance
//   - Deltas stored per-match (like [ local ident indexing for pixels)
//   - Uncovered pixels stored as sequential scan (no coordinates)
// ═══════════════════════════════════════════════════════════════════════

#include "../core/format.hpp"
#include "../core/bitstream.hpp"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>

namespace crumpiler {

struct ImageCrumpleResult {
    uint32_t width              = 0;
    uint32_t height             = 0;
    uint8_t  channels           = 3;
    uint8_t  tolerance          = 8;    // ±N per channel
    uint64_t pixel_count        = 0;
    uint64_t input_bytes        = 0;
    uint64_t output_bytes       = 0;
    uint32_t phrases_found      = 0;
    uint32_t total_scans        = 0;
    uint32_t replacements       = 0;
    uint32_t pixels_covered     = 0;
    uint32_t pixels_uncovered   = 0;
    double   ratio              = 0.0;
};

class ImageCrumpler {
public:
    // 8 directional strides (dx, dy)
    static constexpr int DX[8] = { 1,  1,  0, -1, -1, -1,  0,  1 };
    static constexpr int DY[8] = { 0,  1,  1,  1,  0, -1, -1, -1 };

    [[nodiscard]] auto crumple(
        const uint8_t* pixels,
        uint32_t width, uint32_t height,
        uint8_t channels,
        uint8_t tolerance,       // ±N per channel for fuzzy matching
        std::vector<uint8_t>& out
    ) -> ImageCrumpleResult {
        ImageCrumpleResult result;
        result.width = width;
        result.height = height;
        result.channels = channels;
        result.tolerance = tolerance;
        result.pixel_count = static_cast<uint64_t>(width) * height;
        result.input_bytes = result.pixel_count * channels;

        constexpr uint32_t MIN_OCC = 3;

        // ── Stage 1: Fuzzy phrase scan ─────────────────────────────────
        // For each direction and run length, scan all pixels.
        // Hash is QUANTIZED: each channel value is divided by (tolerance*2+1)
        // so "close" values hash the same.
        std::vector<FuzzyPhrase> phrases;

        for (uint32_t run_len : {32u, 16u, 8u, 4u}) {
            if (run_len > std::min(width, height)) continue;
            for (uint8_t dir = 0; dir < 8; ++dir) {
                scan_direction_fuzzy(pixels, width, height, channels,
                    tolerance, dir, run_len, MIN_OCC, phrases);
                result.total_scans += width * height;
            }
            if (phrases.size() >= 2048) break;
        }

        // Sort by savings (count × length)
        std::sort(phrases.begin(), phrases.end(),
            [](const FuzzyPhrase& a, const FuzzyPhrase& b) {
                return a.savings > b.savings;
            });

        // Determine delta bit width from tolerance
        // tolerance ±8 → delta range [-8, +8] → 17 values → 5 bits
        uint8_t delta_bits = 1;
        { uint32_t range = tolerance * 2 + 1; while ((1u << delta_bits) < range) ++delta_bits; }

        // Filter: keep only profitable phrases
        // Dict cost = 4 + 1 + run_len * channels bytes (base pixel data)
        // Ref cost  = 4(x) + 4(y) + (run_len * channels * delta_bits) / 8 bytes
        {
            std::vector<FuzzyPhrase> filtered;
            for (auto const& p : phrases) {
                int64_t pixel_bytes = static_cast<int64_t>(p.length) * channels;
                int64_t dict_cost = 5 + pixel_bytes; // base phrase storage
                int64_t ref_delta_bytes = (static_cast<int64_t>(p.length) *
                    channels * delta_bits + 7) / 8;
                int64_t ref_cost = 4 + ref_delta_bytes; // position + deltas
                int64_t savings = static_cast<int64_t>(p.count) *
                    (pixel_bytes - ref_cost) - dict_cost;
                if (savings > 0) {
                    filtered.push_back(p);
                }
            }
            phrases = std::move(filtered);
        }

        if (phrases.size() > 512) phrases.resize(512);
        result.phrases_found = static_cast<uint32_t>(phrases.size());

        // ── Stage 2: Build fuzzy replacement map ───────────────────────
        uint64_t total_pixels = static_cast<uint64_t>(width) * height;
        std::vector<bool> covered(total_pixels, false);

        struct FuzzyRef {
            uint16_t x, y;
            uint16_t phrase_id;
            // Per-pixel deltas stored inline (channels * length values, each ±tolerance)
            std::vector<int8_t> deltas;
        };
        std::vector<FuzzyRef> refs;

        for (uint32_t pid = 0; pid < phrases.size(); ++pid) {
            auto const& phrase = phrases[pid];
            int dx = DX[phrase.direction];
            int dy = DY[phrase.direction];

            for (uint32_t sy = 0; sy < height; ++sy) {
                for (uint32_t sx = 0; sx < width; ++sx) {
                    int ex = static_cast<int>(sx) + dx * (phrase.length - 1);
                    int ey = static_cast<int>(sy) + dy * (phrase.length - 1);
                    if (ex < 0 || ex >= static_cast<int>(width)) continue;
                    if (ey < 0 || ey >= static_cast<int>(height)) continue;

                    // Check overlap
                    bool overlap = false;
                    for (uint32_t i = 0; i < phrase.length && !overlap; ++i) {
                        uint32_t px = sx + dx * i;
                        uint32_t py = sy + dy * i;
                        if (covered[py * width + px]) overlap = true;
                    }
                    if (overlap) continue;

                    // Fuzzy match: compute deltas
                    std::vector<int8_t> deltas;
                    deltas.reserve(phrase.length * channels);
                    bool match = true;

                    for (uint32_t i = 0; i < phrase.length && match; ++i) {
                        uint32_t px = sx + dx * i;
                        uint32_t py = sy + dy * i;
                        size_t off = (py * width + px) * channels;
                        // Base phrase pixel
                        uint32_t bx = phrase.start_x + dx * i;
                        uint32_t by = phrase.start_y + dy * i;
                        size_t boff = (by * width + bx) * channels;

                        for (uint8_t c = 0; c < channels; ++c) {
                            int diff = static_cast<int>(pixels[off + c]) -
                                       static_cast<int>(pixels[boff + c]);
                            if (diff < -tolerance || diff > tolerance) {
                                match = false;
                                break;
                            }
                            deltas.push_back(static_cast<int8_t>(diff));
                        }
                    }
                    if (!match) continue;

                    // Mark covered
                    for (uint32_t i = 0; i < phrase.length; ++i) {
                        uint32_t px = sx + dx * i;
                        uint32_t py = sy + dy * i;
                        covered[py * width + px] = true;
                        ++result.pixels_covered;
                    }
                    refs.push_back({
                        static_cast<uint16_t>(sx),
                        static_cast<uint16_t>(sy),
                        static_cast<uint16_t>(pid),
                        std::move(deltas)
                    });
                    ++result.replacements;
                }
            }
        }

        // ── Stage 3: Write output ──────────────────────────────────────
        out.clear();
        out.reserve(result.input_bytes);

        // Header
        uint32_t magic_val = 0x47504D43; // "CMPG"
        append_u32(out, magic_val);
        append_u32(out, width);
        append_u32(out, height);
        out.push_back(channels);
        out.push_back(tolerance);
        out.push_back(delta_bits);
        append_u32(out, static_cast<uint32_t>(phrases.size()));
        append_u32(out, static_cast<uint32_t>(refs.size()));

        // Phrase dictionary: base pixel data for each phrase
        for (auto const& p : phrases) {
            append_u32(out, p.length);
            out.push_back(p.direction);
            int dx = DX[p.direction];
            int dy = DY[p.direction];
            for (uint32_t i = 0; i < p.length; ++i) {
                uint32_t px = p.start_x + dx * i;
                uint32_t py = p.start_y + dy * i;
                size_t off = (py * width + px) * channels;
                out.insert(out.end(), pixels + off, pixels + off + channels);
            }
        }

        // References: position + packed deltas
        for (auto const& r : refs) {
            append_u16(out, r.x);
            append_u16(out, r.y);
            append_u16(out, r.phrase_id);
            // Pack deltas: each delta is (value + tolerance) to make unsigned,
            // then packed at delta_bits per value
            uint8_t accum = 0;
            uint8_t bits_used = 0;
            for (int8_t d : r.deltas) {
                uint8_t val = static_cast<uint8_t>(d + tolerance);
                for (int b = delta_bits - 1; b >= 0; --b) {
                    accum = (accum << 1) | ((val >> b) & 1);
                    ++bits_used;
                    if (bits_used == 8) {
                        out.push_back(accum);
                        accum = 0;
                        bits_used = 0;
                    }
                }
            }
            if (bits_used > 0) {
                accum <<= (8 - bits_used);
                out.push_back(accum);
            }
        }

        // Uncovered pixels: sequential scan order, NO coordinates
        // Just raw RGB values for pixels not covered, in row-major order
        result.pixels_uncovered = 0;
        for (uint64_t i = 0; i < total_pixels; ++i) {
            if (!covered[i]) ++result.pixels_uncovered;
        }
        append_u32(out, result.pixels_uncovered);

        // Bitmap: 1 bit per pixel — 0=uncovered (raw follows), 1=covered (skip)
        // This tells the decoder which pixels are in phrases vs raw
        {
            uint8_t byte = 0;
            uint8_t bit = 0;
            for (uint64_t i = 0; i < total_pixels; ++i) {
                byte = (byte << 1) | (covered[i] ? 1 : 0);
                ++bit;
                if (bit == 8) {
                    out.push_back(byte);
                    byte = 0;
                    bit = 0;
                }
            }
            if (bit > 0) {
                byte <<= (8 - bit);
                out.push_back(byte);
            }
        }

        // Raw uncovered pixel data (sequential, no coords)
        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {
                if (!covered[y * width + x]) {
                    size_t off = (y * width + x) * channels;
                    out.insert(out.end(), pixels + off, pixels + off + channels);
                }
            }
        }

        result.output_bytes = out.size();
        result.ratio = (result.input_bytes > 0)
            ? static_cast<double>(result.output_bytes) / result.input_bytes * 100.0
            : 100.0;

        return result;
    }

    // Load a BMP file to raw pixels (24-bit uncompressed BMPs only)
    [[nodiscard]] static auto load_bmp(
        const std::string& path,
        uint32_t& width, uint32_t& height
    ) -> std::vector<uint8_t> {
        std::ifstream in(path, std::ios::binary | std::ios::ate);
        if (!in.is_open()) return {};
        size_t fsize = in.tellg();
        in.seekg(0);
        std::vector<uint8_t> file(fsize);
        in.read(reinterpret_cast<char*>(file.data()), fsize);

        if (fsize < 54) return {};
        if (file[0] != 'B' || file[1] != 'M') return {};

        uint32_t data_offset = 0;
        std::memcpy(&data_offset, file.data() + 10, 4);
        int32_t w = 0, h = 0;
        std::memcpy(&w, file.data() + 18, 4);
        std::memcpy(&h, file.data() + 22, 4);
        uint16_t bpp = 0;
        std::memcpy(&bpp, file.data() + 28, 2);

        if (bpp != 24) return {};
        bool bottom_up = (h > 0);
        width = static_cast<uint32_t>(w);
        height = static_cast<uint32_t>(std::abs(h));

        uint32_t row_stride = (width * 3 + 3) & ~3u;
        std::vector<uint8_t> pixels(width * height * 3);

        for (uint32_t y = 0; y < height; ++y) {
            uint32_t src_row = bottom_up ? (height - 1 - y) : y;
            const uint8_t* src = file.data() + data_offset + src_row * row_stride;
            uint8_t* dst = pixels.data() + y * width * 3;
            for (uint32_t x = 0; x < width; ++x) {
                dst[x * 3 + 0] = src[x * 3 + 2]; // BGR → RGB
                dst[x * 3 + 1] = src[x * 3 + 1];
                dst[x * 3 + 2] = src[x * 3 + 0];
            }
        }
        return pixels;
    }

private:
    struct FuzzyPhrase {
        uint64_t hash       = 0;
        uint32_t start_x    = 0;
        uint32_t start_y    = 0;
        uint8_t  direction  = 0;
        uint32_t length     = 0;
        uint32_t count      = 0;
        uint64_t savings    = 0;
    };

    // Scan one direction with quantized (fuzzy) hashing
    void scan_direction_fuzzy(
        const uint8_t* pixels,
        uint32_t width, uint32_t height, uint8_t channels,
        uint8_t tolerance, uint8_t dir, uint32_t run_len, uint32_t min_occ,
        std::vector<FuzzyPhrase>& results
    ) {
        int dx = DX[dir];
        int dy = DY[dir];
        uint32_t quant = tolerance * 2 + 1; // quantization step
        if (quant == 0) quant = 1;

        struct Entry {
            uint64_t hash;
            uint32_t x, y;
        };
        std::vector<Entry> entries;
        entries.reserve(static_cast<size_t>(width) * height / 2);

        for (uint32_t sy = 0; sy < height; ++sy) {
            for (uint32_t sx = 0; sx < width; ++sx) {
                int ex = static_cast<int>(sx) + dx * (run_len - 1);
                int ey = static_cast<int>(sy) + dy * (run_len - 1);
                if (ex < 0 || ex >= static_cast<int>(width)) continue;
                if (ey < 0 || ey >= static_cast<int>(height)) continue;

                // Quantized hash: divide each channel by quant before hashing
                // so pixels within ±tolerance hash the same
                uint64_t h = 0xcbf29ce484222325ULL;
                for (uint32_t i = 0; i < run_len; ++i) {
                    uint32_t px = sx + dx * i;
                    uint32_t py = sy + dy * i;
                    size_t off = (py * width + px) * channels;
                    for (uint8_t c = 0; c < channels; ++c) {
                        uint8_t q = pixels[off + c] / quant;
                        h ^= q;
                        h *= 0x100000001b3ULL;
                    }
                }
                entries.push_back({h, sx, sy});
            }
        }

        std::sort(entries.begin(), entries.end(),
            [](const Entry& a, const Entry& b) { return a.hash < b.hash; });

        size_t gs = 0;
        while (gs < entries.size()) {
            uint64_t sig = entries[gs].hash;
            size_t ge = gs + 1;
            while (ge < entries.size() && entries[ge].hash == sig) ++ge;

            uint32_t group_size = static_cast<uint32_t>(ge - gs);
            if (group_size >= min_occ) {
                // Verify fuzzy match: each pixel within ±tolerance
                uint32_t verified = 0;
                for (size_t j = gs; j < ge && j < gs + 200; ++j) {
                    bool match = true;
                    for (uint32_t i = 0; i < run_len && match; ++i) {
                        uint32_t px1 = entries[gs].x + dx * i;
                        uint32_t py1 = entries[gs].y + dy * i;
                        uint32_t px2 = entries[j].x + dx * i;
                        uint32_t py2 = entries[j].y + dy * i;
                        size_t o1 = (py1 * width + px1) * channels;
                        size_t o2 = (py2 * width + px2) * channels;
                        for (uint8_t c = 0; c < channels; ++c) {
                            int diff = static_cast<int>(pixels[o1 + c]) -
                                       static_cast<int>(pixels[o2 + c]);
                            if (diff < -tolerance || diff > tolerance) {
                                match = false;
                                break;
                            }
                        }
                    }
                    if (match) ++verified;
                }

                if (verified >= min_occ) {
                    FuzzyPhrase pp;
                    pp.hash = sig;
                    pp.start_x = entries[gs].x;
                    pp.start_y = entries[gs].y;
                    pp.direction = dir;
                    pp.length = run_len;
                    pp.count = verified;
                    pp.savings = static_cast<uint64_t>(verified - 1) *
                        run_len * channels;
                    results.push_back(pp);
                }
            }
            gs = ge;
        }
    }

    static void append_u32(std::vector<uint8_t>& v, uint32_t val) {
        v.push_back(static_cast<uint8_t>(val));
        v.push_back(static_cast<uint8_t>(val >> 8));
        v.push_back(static_cast<uint8_t>(val >> 16));
        v.push_back(static_cast<uint8_t>(val >> 24));
    }
    static void append_u16(std::vector<uint8_t>& v, uint16_t val) {
        v.push_back(static_cast<uint8_t>(val));
        v.push_back(static_cast<uint8_t>(val >> 8));
    }
};

} // namespace crumpiler
