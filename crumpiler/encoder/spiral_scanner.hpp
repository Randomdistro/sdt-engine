#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Spiral Scanner (Torah Column Algorithm) v3
// ═══════════════════════════════════════════════════════════════════════
// Takes the ENTIRE flat pixel stream.
// Tests EVERY wrap width from N-1 down to 2. No skipping.
// At each width, checks column-wise repetition (crossword match).
// Each width creates a different 2D grid — patterns that are
// diagonal/complex in the original become simple columns at some width.
// ═══════════════════════════════════════════════════════════════════════

#include "../core/format.hpp"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

namespace crumpiler {

struct SpiralHit {
    uint32_t width          = 0;     // wrap width
    uint32_t rows           = 0;     // full rows at this width
    uint32_t matching_cols  = 0;     // columns where all rows match
    double   match_rate     = 0.0;   // matching_cols / width
    double   score          = 0.0;   // rate × rows
};

struct SpiralEncoded {
    uint32_t width          = 0;
    uint32_t rows           = 0;
    uint8_t  element_size   = 1;
    uint8_t  tolerance      = 0;
    std::vector<uint8_t> base_row;
    std::vector<int8_t>  deltas;
    uint32_t tail_length    = 0;
    std::vector<uint8_t> tail;
};

class SpiralScanner {
public:

    // Test EVERY wrap width from 2 to N-1.
    // Returns ALL hits that exceed min_match_rate, sorted by score.
    [[nodiscard]] auto scan_all_widths(
        const uint8_t* data,
        uint32_t element_count,
        uint8_t  element_size,
        uint8_t  tolerance,
        double   min_match_rate = 0.75,
        bool     verbose = false
    ) const -> std::vector<SpiralHit> {
        std::vector<SpiralHit> hits;

        if (element_count < 4) return hits;

        // Test EVERY width from 2 to element_count/2
        // Each width creates a different 2D grid
        uint32_t max_width = element_count / 2;

        for (uint32_t w = 2; w <= max_width; ++w) {
            uint32_t full_rows = element_count / w;
            if (full_rows < 2) continue;

            // Check each column: does position c match position c+w, c+2w, ...?
            uint32_t matching = 0;
            for (uint32_t c = 0; c < w; ++c) {
                bool col_ok = true;
                for (uint32_t r = 1; r < full_rows && col_ok; ++r) {
                    uint32_t base_byte = c * element_size;
                    uint32_t row_byte = (r * w + c) * element_size;
                    if (row_byte + element_size >
                        static_cast<uint32_t>(element_count) * element_size) {
                        col_ok = false;
                        break;
                    }
                    for (uint8_t b = 0; b < element_size; ++b) {
                        int diff = static_cast<int>(data[row_byte + b]) -
                                   static_cast<int>(data[base_byte + b]);
                        if (diff < -tolerance || diff > tolerance) {
                            col_ok = false;
                            break;
                        }
                    }
                }
                if (col_ok) ++matching;
            }

            double rate = static_cast<double>(matching) / w;
            double score = rate * full_rows;

            if (rate >= min_match_rate) {
                hits.push_back({w, full_rows, matching, rate, score});
            }

            if (verbose && matching > 0 && rate >= 0.5) {
                std::printf("    w=%5u: %3u/%u cols match (%.0f%%), %u rows, score=%.1f\n",
                    w, matching, w, rate * 100.0, full_rows, score);
            }
        }

        // Sort by score descending
        std::sort(hits.begin(), hits.end(),
            [](const SpiralHit& a, const SpiralHit& b) {
                return a.score > b.score;
            });

        return hits;
    }

    // Get the single best width
    [[nodiscard]] auto find_best_width(
        const uint8_t* data,
        uint32_t element_count,
        uint8_t  element_size,
        uint8_t  tolerance,
        double   min_match_rate = 0.75,
        bool     verbose = false
    ) const -> SpiralHit {
        auto hits = scan_all_widths(data, element_count, element_size,
            tolerance, min_match_rate, verbose);
        if (hits.empty()) return {};
        return hits[0];
    }

    // Encode the data at a given wrap width
    [[nodiscard]] auto encode(
        const uint8_t* data,
        uint32_t element_count,
        uint8_t  element_size,
        uint8_t  tolerance,
        const SpiralHit& hit
    ) const -> SpiralEncoded {
        SpiralEncoded enc;
        enc.width = hit.width;
        enc.rows = hit.rows;
        enc.element_size = element_size;
        enc.tolerance = tolerance;

        uint32_t row_bytes = enc.width * element_size;

        // Base row = first row
        enc.base_row.assign(data, data + row_bytes);

        // Deltas for rows 1..rows-1
        enc.deltas.resize(static_cast<size_t>(enc.rows - 1) * row_bytes);
        for (uint32_t r = 1; r < enc.rows; ++r) {
            for (uint32_t i = 0; i < row_bytes; ++i) {
                uint32_t src = r * row_bytes + i;
                int diff = static_cast<int>(data[src]) -
                           static_cast<int>(enc.base_row[i]);
                if (diff < -tolerance) diff = -tolerance;
                if (diff > tolerance) diff = tolerance;
                enc.deltas[(r - 1) * row_bytes + i] = static_cast<int8_t>(diff);
            }
        }

        // Tail
        uint32_t used = enc.rows * enc.width;
        enc.tail_length = element_count - used;
        if (enc.tail_length > 0) {
            uint32_t tb = enc.tail_length * element_size;
            uint32_t ts = used * element_size;
            enc.tail.assign(data + ts, data + ts + tb);
        }

        return enc;
    }

    // Serialize to bytes
    [[nodiscard]] auto serialize(const SpiralEncoded& enc) const
        -> std::vector<uint8_t>
    {
        std::vector<uint8_t> out;

        uint32_t magic = 0x4C525053; // "SPRL"
        append_u32(out, magic);
        append_u32(out, enc.width);
        append_u32(out, enc.rows);
        out.push_back(enc.element_size);
        out.push_back(enc.tolerance);

        out.insert(out.end(), enc.base_row.begin(), enc.base_row.end());

        uint8_t delta_bits = 1;
        { uint32_t range = enc.tolerance * 2 + 1;
          while ((1u << delta_bits) < range) ++delta_bits; }
        out.push_back(delta_bits);

        uint8_t accum = 0;
        uint8_t bits_used = 0;
        for (int8_t d : enc.deltas) {
            uint8_t val = static_cast<uint8_t>(d + enc.tolerance);
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

        append_u32(out, enc.tail_length);
        out.insert(out.end(), enc.tail.begin(), enc.tail.end());

        return out;
    }

    // Estimate encoded size
    [[nodiscard]] auto estimate_size(
        const SpiralHit& hit,
        uint8_t element_size, uint8_t tolerance,
        uint32_t element_count
    ) const -> uint64_t {
        uint32_t row_bytes = hit.width * element_size;
        uint64_t size = 4 + 4 + 4 + 1 + 1 + 1; // header
        size += row_bytes;                        // base row
        uint8_t delta_bits = 1;
        { uint32_t range = tolerance * 2 + 1;
          while ((1u << delta_bits) < range) ++delta_bits; }
        uint64_t dtotal = static_cast<uint64_t>(hit.rows - 1) * row_bytes * delta_bits;
        size += (dtotal + 7) / 8;
        uint32_t tail = element_count - hit.rows * hit.width;
        size += 4 + static_cast<uint64_t>(tail) * element_size;
        return size;
    }

private:
    static void append_u32(std::vector<uint8_t>& v, uint32_t val) {
        v.push_back(static_cast<uint8_t>(val));
        v.push_back(static_cast<uint8_t>(val >> 8));
        v.push_back(static_cast<uint8_t>(val >> 16));
        v.push_back(static_cast<uint8_t>(val >> 24));
    }
};

} // namespace crumpiler
