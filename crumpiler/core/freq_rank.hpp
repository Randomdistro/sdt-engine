#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Frequency Counter & Rank Assignment
// ═══════════════════════════════════════════════════════════════════════
// Counts occurrences of each unique token/phrase in the crumpled stream.
// Assigns ranks: highest frequency → rank 1 → fewest bits.
// ═══════════════════════════════════════════════════════════════════════

#include "types.hpp"
#include "bitstream.hpp"
#include <algorithm>
#include <vector>
#include <cstdint>

namespace crumpiler {

// ── Unified Token Key ──────────────────────────────────────────────────
// A unique identifier for any token across all channels.
// Used as the key for frequency counting.
struct TokenKey {
    Channel  channel = Channel::Ring;
    uint32_t id      = 0;           // channel-specific ID

    [[nodiscard]] constexpr bool operator==(const TokenKey& o) const noexcept {
        return channel == o.channel && id == o.id;
    }

    // Simple hash for use in flat arrays (we sort, not hash-map)
    [[nodiscard]] constexpr auto as_u64() const noexcept -> uint64_t {
        return (static_cast<uint64_t>(channel) << 32) | id;
    }

    [[nodiscard]] constexpr bool operator<(const TokenKey& o) const noexcept {
        return as_u64() < o.as_u64();
    }
};

// ── Frequency Rank Entry ───────────────────────────────────────────────
struct RankEntry {
    TokenKey key;
    uint32_t count     = 0;   // How many times this token appears
    uint32_t rank      = 0;   // 1-based rank (1 = most frequent)
    uint8_t  bit_cost  = 0;   // Elias gamma bit cost at this rank
};

// ── FrequencyTable ─────────────────────────────────────────────────────
// Collects token frequencies, sorts by count, assigns ranks.
class FrequencyTable {
public:
    // Record one occurrence of a token.
    void record(Channel ch, uint32_t id) {
        TokenKey key{ch, id};
        // Linear scan for now; sufficient for codebook sizes.
        for (auto& e : entries_) {
            if (e.key == key) {
                ++e.count;
                return;
            }
        }
        entries_.push_back({key, 1, 0, 0});
    }

    // Sort by frequency and assign ranks + bit costs.
    void finalize() {
        // Sort descending by count
        std::sort(entries_.begin(), entries_.end(),
            [](const RankEntry& a, const RankEntry& b) {
                return a.count > b.count;
            });

        // Assign ranks (1-based)
        for (uint32_t i = 0; i < entries_.size(); ++i) {
            entries_[i].rank = i + 1;
            entries_[i].bit_cost = gamma_bit_cost(i + 1);
        }

        finalized_ = true;
    }

    // Look up the rank for a token key.
    [[nodiscard]] auto find_rank(Channel ch, uint32_t id) const noexcept -> uint32_t {
        TokenKey key{ch, id};
        for (auto const& e : entries_) {
            if (e.key == key) return e.rank;
        }
        return 0; // not found
    }

    // Look up the token key for a rank.
    [[nodiscard]] auto find_key(uint32_t rank) const noexcept -> TokenKey {
        if (rank == 0 || rank > entries_.size()) return {};
        return entries_[rank - 1].key;
    }

    // Get bit cost for a token.
    [[nodiscard]] auto bit_cost(Channel ch, uint32_t id) const noexcept -> uint8_t {
        TokenKey key{ch, id};
        for (auto const& e : entries_) {
            if (e.key == key) return e.bit_cost;
        }
        return 32; // fallback
    }

    // Compute total bits needed for the entire token stream
    // (given that each token appears 'count' times at its bit cost).
    [[nodiscard]] auto total_bits() const noexcept -> uint64_t {
        uint64_t total = 0;
        for (auto const& e : entries_) {
            total += static_cast<uint64_t>(e.count) * e.bit_cost;
        }
        return total;
    }

    // Compute original ASCII size equivalent.
    [[nodiscard]] auto total_tokens() const noexcept -> uint64_t {
        uint64_t total = 0;
        for (auto const& e : entries_) {
            total += e.count;
        }
        return total;
    }

    [[nodiscard]] auto entries() const noexcept -> const std::vector<RankEntry>& {
        return entries_;
    }
    [[nodiscard]] auto size() const noexcept -> size_t { return entries_.size(); }
    [[nodiscard]] bool finalized() const noexcept { return finalized_; }

private:
    std::vector<RankEntry> entries_;
    bool finalized_ = false;
};

} // namespace crumpiler
