#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Delta Scanner v2 (Relative Distance + Stacked Encoding)
// ═══════════════════════════════════════════════════════════════════════
// 1. Find gradient shapes (delta chains) that repeat across the image
// 2. Sort all occurrences by base pixel value (lowest first)
// 3. Store: lowest base (absolute), then just distances between bases
//    and position offsets. Distances are small → compress tight.
//
// Storage per chain:
//   - Delta pattern: stored ONCE (the gradient shape)
//   - Lowest base: channels bytes (absolute)
//   - Each subsequent occurrence: distance + position
//     distance = (base[n] - base[n-1]) per channel (small positive int)
// ═══════════════════════════════════════════════════════════════════════

#include "../core/format.hpp"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstdio>
#include <numeric>

namespace crumpiler {

struct DeltaScanResult {
    uint32_t element_count   = 0;
    uint8_t  channels        = 3;
    uint32_t chains_found    = 0;
    uint32_t total_covered   = 0;
    uint64_t raw_size        = 0;
    uint64_t encoded_size    = 0;
    double   ratio           = 0.0;

    // Stacked encoding stats
    uint64_t dict_cost       = 0;  // delta patterns stored once each
    uint64_t base_cost       = 0;  // lowest base per chain
    uint64_t distance_cost   = 0;  // cumulative distances between bases
    uint64_t position_cost   = 0;  // pixel positions
    uint64_t uncovered_cost  = 0;  // raw pixels not covered

    struct ChainInfo {
        uint32_t length;
        uint32_t occurrences;
        uint64_t savings;
        uint8_t  max_base_dist; // largest distance step between sorted bases
    };
    std::vector<ChainInfo> top_chains;
};

class DeltaScanner {
public:

    [[nodiscard]] auto scan(
        const uint8_t* data,
        uint32_t pixel_count,
        uint8_t  channels,
        uint32_t min_chain_length = 4,
        uint32_t min_occurrences = 3,
        bool     verbose = false
    ) const -> DeltaScanResult {
        DeltaScanResult result;
        result.element_count = pixel_count;
        result.channels = channels;
        result.raw_size = static_cast<uint64_t>(pixel_count) * channels;

        if (pixel_count < 4) return result;

        // ── Step 1: Compute adjacent-pixel deltas ──────────────────────
        uint32_t delta_count = pixel_count - 1;
        std::vector<int16_t> all_deltas(delta_count * channels);

        for (uint32_t i = 0; i < delta_count; ++i) {
            for (uint8_t c = 0; c < channels; ++c) {
                all_deltas[i * channels + c] =
                    static_cast<int16_t>(data[(i + 1) * channels + c]) -
                    static_cast<int16_t>(data[i * channels + c]);
            }
        }

        // ── Step 2: Hash delta runs at each length ─────────────────────
        auto hash_run = [&](uint32_t start, uint32_t len) -> uint64_t {
            uint64_t h = 0xcbf29ce484222325ULL;
            for (uint32_t i = 0; i < len; ++i) {
                uint32_t di = (start + i) * channels;
                for (uint8_t c = 0; c < channels; ++c) {
                    h ^= static_cast<uint16_t>(all_deltas[di + c] + 256);
                    h *= 0x100000001b3ULL;
                }
            }
            return h;
        };

        // ── Step 3: Find and verify chains ─────────────────────────────
        struct FoundChain {
            uint32_t delta_len;              // number of deltas (pixels - 1)
            std::vector<uint32_t> positions; // all verified start positions
        };
        std::vector<FoundChain> found_chains;

        for (uint32_t dlen = min_chain_length - 1;
             dlen <= 64 && dlen < delta_count; ++dlen) {

            std::unordered_map<uint64_t, std::vector<uint32_t>> groups;
            for (uint32_t pos = 0; pos + dlen <= delta_count; ++pos) {
                groups[hash_run(pos, dlen)].push_back(pos);
            }

            uint32_t found_this_len = 0;
            for (auto& [hash, positions] : groups) {
                if (positions.size() < min_occurrences) continue;

                // Verify actual delta match
                std::vector<uint32_t> verified_pos;
                for (size_t j = 0; j < positions.size() && j < 500; ++j) {
                    bool match = true;
                    for (uint32_t k = 0; k < dlen && match; ++k) {
                        for (uint8_t c = 0; c < channels; ++c) {
                            if (all_deltas[(positions[0] + k) * channels + c] !=
                                all_deltas[(positions[j] + k) * channels + c]) {
                                match = false;
                            }
                        }
                    }
                    if (match) verified_pos.push_back(positions[j]);
                }

                if (verified_pos.size() >= min_occurrences) {
                    found_chains.push_back({dlen, std::move(verified_pos)});
                    ++found_this_len;
                }
            }

            if (verbose && found_this_len > 0) {
                std::printf("    delta-length %2u: %u chains\n", dlen, found_this_len);
            }
            if (found_this_len == 0 && dlen > min_chain_length + 10) break;
        }

        // ── Step 4: Stacked cost model ─────────────────────────────────
        // For each chain:
        //   dict_cost = dlen × channels × 2 bytes (delta pattern, stored once)
        //   base_cost = channels bytes (lowest base pixel, stored once)
        //   For N occurrences sorted by base value:
        //     distance_cost = (N-1) × bytes_per_distance
        //     position_cost = N × 4 bytes (pixel position)
        //
        // bytes_per_distance depends on how spread out the bases are.
        // If distances are small (< 256), 1 byte per channel.
        // If distances are very small (< 16), pack to 4 bits.

        // Sort chains by total pixel coverage
        std::sort(found_chains.begin(), found_chains.end(),
            [](const FoundChain& a, const FoundChain& b) {
                return static_cast<uint64_t>(a.positions.size()) * (a.delta_len + 1) >
                       static_cast<uint64_t>(b.positions.size()) * (b.delta_len + 1);
            });

        result.chains_found = static_cast<uint32_t>(found_chains.size());

        uint64_t total_dict = 0;
        uint64_t total_base = 0;
        uint64_t total_dist = 0;
        uint64_t total_pos = 0;

        for (auto const& chain : found_chains) {
            uint32_t n = static_cast<uint32_t>(chain.positions.size());
            uint32_t pixels_per = chain.delta_len + 1;

            // Sort occurrences by base pixel luminance
            // (sum of channel values as sorting key)
            struct Occ {
                uint32_t pos;
                uint16_t luma;  // sum of base pixel channels
            };
            std::vector<Occ> sorted_occ;
            sorted_occ.reserve(n);
            for (uint32_t p : chain.positions) {
                uint16_t luma = 0;
                for (uint8_t c = 0; c < channels; ++c) {
                    luma += data[p * channels + c];
                }
                sorted_occ.push_back({p, luma});
            }
            std::sort(sorted_occ.begin(), sorted_occ.end(),
                [](const Occ& a, const Occ& b) { return a.luma < b.luma; });

            // Compute distances between sorted bases
            uint8_t max_dist = 0;
            for (size_t i = 1; i < sorted_occ.size(); ++i) {
                for (uint8_t c = 0; c < channels; ++c) {
                    int d = static_cast<int>(data[sorted_occ[i].pos * channels + c]) -
                            static_cast<int>(data[sorted_occ[i-1].pos * channels + c]);
                    if (d < 0) d = -d;
                    if (d > max_dist) max_dist = static_cast<uint8_t>(std::min(d, 255));
                }
            }

            // Compute bits per distance value
            uint8_t dist_bits = 1;
            while ((1u << dist_bits) < (max_dist * 2 + 1)) ++dist_bits;
            if (dist_bits > 8) dist_bits = 8;

            // Costs for this chain
            uint64_t c_dict = static_cast<uint64_t>(chain.delta_len) * channels * 2 + 4;
            uint64_t c_base = channels;  // lowest base pixel
            // (n-1) distances × channels × dist_bits / 8
            uint64_t c_dist = (static_cast<uint64_t>(n - 1) * channels * dist_bits + 7) / 8;
            uint64_t c_pos = static_cast<uint64_t>(n) * 4;  // positions

            uint64_t enc_cost = c_dict + c_base + c_dist + c_pos;
            uint64_t raw_cost = static_cast<uint64_t>(n) * pixels_per * channels;

            total_dict += c_dict;
            total_base += c_base;
            total_dist += c_dist;
            total_pos += c_pos;

            result.total_covered += n * pixels_per;

            if (result.top_chains.size() < 20) {
                result.top_chains.push_back({
                    pixels_per, n, raw_cost, max_dist
                });
            }
        }

        if (result.total_covered > pixel_count)
            result.total_covered = pixel_count;

        uint64_t uncovered = pixel_count - result.total_covered;
        uint64_t uncov_cost = uncovered * channels;

        result.dict_cost = total_dict;
        result.base_cost = total_base;
        result.distance_cost = total_dist;
        result.position_cost = total_pos;
        result.uncovered_cost = uncov_cost;

        result.encoded_size = 16 + total_dict + total_base +
            total_dist + total_pos + uncov_cost;

        result.ratio = result.raw_size > 0
            ? static_cast<double>(result.encoded_size) / result.raw_size * 100.0
            : 100.0;

        return result;
    }
};

} // namespace crumpiler
