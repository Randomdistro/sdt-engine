#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Phrase Finder
// ═══════════════════════════════════════════════════════════════════════
// Discovers repeated multi-token sequences in the token stream.
// Replaces them with single phrase references for massive dedup.
// ═══════════════════════════════════════════════════════════════════════

#include "../core/types.hpp"
#include "lexer.hpp"
#include <vector>
#include <algorithm>
#include <cstdint>
#include <string>

namespace crumpiler {

struct PhraseCandidate {
    std::vector<uint32_t> token_indices;  // Which positions in the token stream
    uint32_t length      = 0;             // How many tokens in the phrase
    uint32_t occurrences = 0;             // How many times it appears
    uint64_t bytes_saved = 0;             // Bytes saved by replacing with one ref

    // A key for comparing phrases (hash of token sequence)
    uint64_t signature   = 0;
};

class PhraseFinder {
public:
    // Find repeated phrases in the token stream.
    // min_len: minimum phrase length (tokens)
    // max_len: maximum phrase length (tokens)
    // min_occurrences: minimum number of times a phrase must appear
    [[nodiscard]] auto find_phrases(
        const std::vector<LexedToken>& tokens,
        uint32_t min_len = 3,
        uint32_t max_len = 12,
        uint32_t min_occurrences = 3
    ) -> std::vector<PhraseCandidate> {

        std::vector<PhraseCandidate> results;

        // For each candidate phrase length, scan for repeats.
        // Start from longest — longer phrases save more bytes.
        for (uint32_t len = max_len; len >= min_len; --len) {
            if (tokens.size() < len) continue;

            // Build signature-indexed list of phrase positions
            struct Entry {
                uint64_t sig = 0;
                uint32_t start = 0;
            };
            std::vector<Entry> entries;
            entries.reserve(tokens.size() - len + 1);

            for (uint32_t i = 0; i <= tokens.size() - len; ++i) {
                uint64_t sig = compute_signature(tokens, i, len);
                entries.push_back({sig, i});
            }

            // Sort by signature to group identical phrases
            std::sort(entries.begin(), entries.end(),
                [](const Entry& a, const Entry& b) { return a.sig < b.sig; });

            // Walk sorted entries, group consecutive identical sigs
            uint32_t group_start = 0;
            while (group_start < entries.size()) {
                uint64_t sig = entries[group_start].sig;
                uint32_t group_end = group_start + 1;
                while (group_end < entries.size() && entries[group_end].sig == sig) {
                    ++group_end;
                }

                uint32_t count = group_end - group_start;
                if (count >= min_occurrences) {
                    // Verify actual equality (not just hash collision)
                    // by checking first occurrence against the rest
                    uint32_t verified = 0;
                    uint32_t ref_start = entries[group_start].start;
                    for (uint32_t j = group_start; j < group_end; ++j) {
                        if (phrases_equal(tokens, ref_start, entries[j].start, len)) {
                            ++verified;
                        }
                    }

                    if (verified >= min_occurrences) {
                        PhraseCandidate pc;
                        pc.length = len;
                        pc.occurrences = verified;
                        pc.signature = sig;

                        // Estimate bytes saved
                        uint64_t phrase_chars = 0;
                        for (uint32_t k = 0; k < len; ++k) {
                            phrase_chars += tokens[ref_start + k].text.size() + 1;
                        }
                        pc.bytes_saved = (verified - 1) * phrase_chars;

                        results.push_back(std::move(pc));
                    }
                }

                group_start = group_end;
            }
        }

        // Sort by bytes saved (descending) — greediest first
        std::sort(results.begin(), results.end(),
            [](const PhraseCandidate& a, const PhraseCandidate& b) {
                return a.bytes_saved > b.bytes_saved;
            });

        // Limit to top N phrases to keep legend small
        if (results.size() > MAX_PHRASES) {
            results.resize(MAX_PHRASES);
        }

        return results;
    }

    static constexpr uint32_t MAX_PHRASES = 4096;

private:
    // Compute a 64-bit signature for a phrase at position start, length len.
    [[nodiscard]] static auto compute_signature(
        const std::vector<LexedToken>& tokens,
        uint32_t start, uint32_t len
    ) noexcept -> uint64_t {
        uint64_t hash = 0xcbf29ce484222325ULL; // FNV-1a offset
        for (uint32_t i = 0; i < len; ++i) {
            auto const& tok = tokens[start + i];
            // Hash channel
            hash ^= static_cast<uint64_t>(tok.channel);
            hash *= 0x100000001b3ULL;
            // Hash text (or ring position for ring tokens)
            if (tok.channel == Channel::Ring) {
                hash ^= ring_global_id(tok.ring_id, tok.ring_pos);
                hash *= 0x100000001b3ULL;
            } else if (tok.is_literal) {
                // For literals, hash the kind (String/Number/Char)
                // not the actual content (we use ^STRING, ^NUM, ^CHAR)
                hash ^= static_cast<uint64_t>(tok.lit_kind);
                hash *= 0x100000001b3ULL;
            } else {
                for (char c : tok.text) {
                    hash ^= static_cast<uint64_t>(c);
                    hash *= 0x100000001b3ULL;
                }
            }
        }
        return hash;
    }

    // Check if two phrases are actually equal (not just hash match).
    [[nodiscard]] static bool phrases_equal(
        const std::vector<LexedToken>& tokens,
        uint32_t a_start, uint32_t b_start, uint32_t len
    ) noexcept {
        for (uint32_t i = 0; i < len; ++i) {
            auto const& ta = tokens[a_start + i];
            auto const& tb = tokens[b_start + i];
            if (ta.channel != tb.channel) return false;
            if (ta.channel == Channel::Ring) {
                if (ta.ring_id != tb.ring_id || ta.ring_pos != tb.ring_pos) return false;
            } else if (ta.is_literal) {
                if (ta.lit_kind != tb.lit_kind) return false;
            } else {
                if (ta.text != tb.text) return false;
            }
        }
        return true;
    }
};

} // namespace crumpiler
