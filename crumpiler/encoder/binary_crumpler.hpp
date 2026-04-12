#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Binary Crumpler (Format-Agnostic)
// ═══════════════════════════════════════════════════════════════════════
// Treats ANY file as a raw byte stream. Finds repeating byte sequences,
// frequency-ranks them, encodes with variable-width codes.
// Supports recursive passes: binary² → binary³ → ... → entropy floor.
// ═══════════════════════════════════════════════════════════════════════

#include "../core/format.hpp"
#include "../core/bitstream.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <unordered_map>

namespace crumpiler {

struct BinaryCrumpleResult {
    uint64_t input_bytes       = 0;
    uint64_t output_bytes      = 0;
    uint32_t phrases_found     = 0;
    uint32_t pass_number       = 0;
    double   ratio             = 0.0;
};

class BinaryCrumpler {
public:
    // Single-pass crumple on raw bytes.
    [[nodiscard]] auto crumple(
        const uint8_t* data, size_t size,
        std::vector<uint8_t>& out
    ) -> BinaryCrumpleResult {
        BinaryCrumpleResult result;
        result.input_bytes = size;

        if (size < 16) {
            out.assign(data, data + size);
            result.output_bytes = size;
            result.ratio = 100.0;
            return result;
        }

        // ── Stage 1: Find repeating byte sequences ─────────────────────
        // Scan for repeated substrings of length min_len..max_len.
        // Use rolling hash (Rabin-Karp style) for speed.
        constexpr uint32_t MIN_PHRASE_LEN = 4;
        uint32_t max_phrase_len = static_cast<uint32_t>(
            std::min(size / 2, static_cast<size_t>(4096)));
        constexpr uint32_t MIN_OCCURRENCES = 3;

        std::vector<BytePhrase> phrases;

        // Scan multiple lengths, longest first
        for (uint32_t len = max_phrase_len; len >= MIN_PHRASE_LEN; len /= 2) {
            if (len > size) continue;
            find_repeated_sequences(data, size, len, MIN_OCCURRENCES, phrases);
            if (phrases.size() >= 2048) break;
        }
        // Also scan common small lengths
        for (uint32_t len : {32u, 24u, 16u, 12u, 8u, 6u, 4u}) {
            if (len > size || len > max_phrase_len) continue;
            find_repeated_sequences(data, size, len, MIN_OCCURRENCES, phrases);
            if (phrases.size() >= 4096) break;
        }

        // Sort by savings (biggest savings first)
        std::sort(phrases.begin(), phrases.end(),
            [](const BytePhrase& a, const BytePhrase& b) {
                return a.savings > b.savings;
            });
        // Filter: only keep phrases with positive net savings.
        // Dict cost per phrase = 4 bytes (length field) + length bytes (data)
        // Per-reference savings = length - 3 bytes (1 marker + 2 byte phrase id)
        // Net savings = count * (length - 3) - (4 + length)
        {
            std::vector<BytePhrase> filtered;
            for (auto const& p : phrases) {
                if (p.length <= 3) continue;  // can't save anything
                int64_t dict_cost = 4 + static_cast<int64_t>(p.length);
                int64_t ref_savings = static_cast<int64_t>(p.count) *
                    (static_cast<int64_t>(p.length) - 3);
                if (ref_savings > dict_cost) {
                    filtered.push_back(p);
                }
            }
            phrases = std::move(filtered);
        }

        if (phrases.size() > 256) phrases.resize(256);
        result.phrases_found = static_cast<uint32_t>(phrases.size());

        // ── Stage 2: Build replacement map ─────────────────────────────
        struct Replacement {
            uint32_t pos       = 0;
            uint32_t length    = 0;
            uint32_t phrase_id = 0;
        };

        std::vector<bool> covered(size, false);
        std::vector<Replacement> replacements;

        for (uint32_t pid = 0; pid < phrases.size() && pid < 256; ++pid) {
            auto const& phrase = phrases[pid];
            if (phrase.length == 0 || phrase.count < MIN_OCCURRENCES) continue;

            // Scan for all occurrences and mark them
            for (size_t i = 0; i + phrase.length <= size; ++i) {
                // Check if this position is already covered
                bool overlap = false;
                for (uint32_t j = 0; j < phrase.length; ++j) {
                    if (covered[i + j]) { overlap = true; break; }
                }
                if (overlap) continue;

                // Verify match
                if (std::memcmp(data + i, data + phrase.first_pos, phrase.length) == 0) {
                    replacements.push_back({
                        static_cast<uint32_t>(i),
                        phrase.length,
                        pid
                    });
                    for (uint32_t j = 0; j < phrase.length; ++j) {
                        covered[i + j] = true;
                    }
                }
            }
        }

        // Sort replacements by position
        std::sort(replacements.begin(), replacements.end(),
            [](const Replacement& a, const Replacement& b) {
                return a.pos < b.pos;
            });

        // ── Stage 3: Encode output ─────────────────────────────────────
        // Format:
        //   [4 bytes] magic "CRB1"
        //   [4 bytes] original size
        //   [4 bytes] phrase count
        //   For each phrase:
        //     [4 bytes] length
        //     [length bytes] raw data
        //   [4 bytes] replacement count
        //   [4 bytes] raw-segment count
        //   Interleaved stream of raw segments and phrase references:
        //     [1 byte] type: 0=raw, 1=phrase_ref
        //     if raw:  [4 bytes] length + [N bytes] data
        //     if ref:  [2 bytes] phrase_id

        out.clear();
        out.reserve(size);

        // Magic
        const uint32_t magic = CRB_MAGIC;
        append_u32(out, magic);
        append_u32(out, static_cast<uint32_t>(size));

        // Phrase dictionary — only write phrases that got replacements
        uint32_t used_phrases = 0;
        std::vector<bool> phrase_used(phrases.size(), false);
        for (auto const& rep : replacements) {
            if (rep.phrase_id < phrase_used.size())
                phrase_used[rep.phrase_id] = true;
        }
        for (bool u : phrase_used) { if (u) ++used_phrases; }
        append_u32(out, used_phrases);
        for (uint32_t i = 0; i < used_phrases; ++i) {
            append_u32(out, phrases[i].length);
            out.insert(out.end(),
                data + phrases[i].first_pos,
                data + phrases[i].first_pos + phrases[i].length);
        }

        // Interleaved stream
        append_u32(out, static_cast<uint32_t>(replacements.size()));
        size_t cursor = 0;
        for (auto const& rep : replacements) {
            // Raw bytes before this replacement
            if (rep.pos > cursor) {
                uint32_t raw_len = static_cast<uint32_t>(rep.pos - cursor);
                out.push_back(0x00); // raw marker
                append_u32(out, raw_len);
                out.insert(out.end(), data + cursor, data + rep.pos);
            }
            // Phrase reference
            out.push_back(0x01); // phrase ref marker
            append_u16(out, static_cast<uint16_t>(rep.phrase_id));
            cursor = rep.pos + rep.length;
        }
        // Trailing raw bytes
        if (cursor < size) {
            uint32_t raw_len = static_cast<uint32_t>(size - cursor);
            out.push_back(0x00);
            append_u32(out, raw_len);
            out.insert(out.end(), data + cursor, data + size);
        }

        result.output_bytes = out.size();
        result.ratio = (result.input_bytes > 0)
            ? (static_cast<double>(result.output_bytes) / result.input_bytes * 100.0)
            : 100.0;
        return result;
    }

    // Multi-pass recursive crumple: binary² → binary³ → ... → entropy floor
    [[nodiscard]] auto crumple_recursive(
        const uint8_t* data, size_t size,
        std::vector<uint8_t>& out,
        uint32_t max_passes = 5,
        double min_improvement = 2.0  // stop if less than 2% improvement
    ) -> std::vector<BinaryCrumpleResult> {

        std::vector<BinaryCrumpleResult> passes;
        std::vector<uint8_t> current(data, data + size);
        std::vector<uint8_t> next;

        for (uint32_t pass = 1; pass <= max_passes; ++pass) {
            auto result = crumple(current.data(), current.size(), next);
            result.pass_number = pass;
            passes.push_back(result);

            double improvement = 100.0 - result.ratio;
            if (improvement < min_improvement || next.size() >= current.size()) {
                // Converged — use previous pass result or current
                if (next.size() >= current.size()) {
                    out = std::move(current);
                } else {
                    out = std::move(next);
                }
                break;
            }

            current = std::move(next);
            next.clear();

            if (pass == max_passes) {
                out = std::move(current);
            }
        }

        return passes;
    }

    // Decrumple a single pass
    [[nodiscard]] auto decrumple(
        const uint8_t* data, size_t size,
        std::vector<uint8_t>& out
    ) -> bool {
        if (size < 16) return false;

        size_t offset = 0;
        uint32_t magic = read_u32(data, offset);
        if (magic != CRB_MAGIC) return false;

        uint32_t original_size = read_u32(data, offset);
        uint32_t phrase_count = read_u32(data, offset);

        // Read phrase dictionary
        struct PhraseData {
            std::vector<uint8_t> bytes;
        };
        std::vector<PhraseData> phrases(phrase_count);
        for (uint32_t i = 0; i < phrase_count; ++i) {
            uint32_t len = read_u32(data, offset);
            phrases[i].bytes.assign(data + offset, data + offset + len);
            offset += len;
        }

        // Read interleaved stream
        uint32_t replacement_count = read_u32(data, offset);
        (void)replacement_count; // used implicitly

        out.clear();
        out.reserve(original_size);

        while (offset < size) {
            uint8_t type = data[offset++];
            if (type == 0x00) {
                // Raw bytes
                uint32_t len = read_u32(data, offset);
                out.insert(out.end(), data + offset, data + offset + len);
                offset += len;
            } else if (type == 0x01) {
                // Phrase reference
                uint16_t pid = read_u16(data, offset);
                if (pid < phrases.size()) {
                    out.insert(out.end(),
                        phrases[pid].bytes.begin(),
                        phrases[pid].bytes.end());
                }
            } else {
                break; // unknown marker
            }
        }

        return true;
    }

    // Multi-pass decrumple
    [[nodiscard]] auto decrumple_recursive(
        const uint8_t* data, size_t size,
        std::vector<uint8_t>& out,
        uint32_t pass_count
    ) -> bool {
        std::vector<uint8_t> current(data, data + size);
        std::vector<uint8_t> next;

        for (uint32_t i = 0; i < pass_count; ++i) {
            if (!decrumple(current.data(), current.size(), next)) {
                return false;
            }
            current = std::move(next);
            next.clear();
        }

        out = std::move(current);
        return true;
    }

private:
    struct BytePhrase {
        uint64_t hash       = 0;
        uint32_t first_pos  = 0;
        uint32_t length     = 0;
        uint32_t count      = 0;
        uint64_t savings    = 0;
    };

    void find_repeated_sequences(
        const uint8_t* data, size_t size,
        uint32_t len, uint32_t min_occ,
        std::vector<BytePhrase>& results
    ) {
        if (len > size) return;

        // Rolling hash for all positions
        struct Entry {
            uint64_t hash;
            uint32_t pos;
        };

        std::vector<Entry> entries;
        entries.reserve(size - len + 1);

        // FNV-1a hash for each position
        for (size_t i = 0; i + len <= size; ++i) {
            uint64_t h = 0xcbf29ce484222325ULL;
            for (uint32_t j = 0; j < len; ++j) {
                h ^= data[i + j];
                h *= 0x100000001b3ULL;
            }
            entries.push_back({h, static_cast<uint32_t>(i)});
        }

        // Sort by hash to group duplicates
        std::sort(entries.begin(), entries.end(),
            [](const Entry& a, const Entry& b) { return a.hash < b.hash; });

        // Find groups with >= min_occ identical hashes
        size_t gs = 0;
        while (gs < entries.size()) {
            uint64_t sig = entries[gs].hash;
            size_t ge = gs + 1;
            while (ge < entries.size() && entries[ge].hash == sig) ++ge;

            uint32_t group_size = static_cast<uint32_t>(ge - gs);
            if (group_size >= min_occ) {
                // Verify actual byte match (not just hash collision)
                uint32_t verified = 0;
                for (size_t j = gs; j < ge; ++j) {
                    if (std::memcmp(data + entries[gs].pos,
                                   data + entries[j].pos, len) == 0) {
                        ++verified;
                    }
                }
                if (verified >= min_occ) {
                    // Check it doesn't overlap with existing results
                    bool duplicate = false;
                    for (auto const& existing : results) {
                        if (existing.hash == sig && existing.length == len) {
                            duplicate = true;
                            break;
                        }
                    }
                    if (!duplicate) {
                        BytePhrase p;
                        p.hash = sig;
                        p.first_pos = entries[gs].pos;
                        p.length = len;
                        p.count = verified;
                        p.savings = static_cast<uint64_t>(verified - 1) * len;
                        results.push_back(p);
                    }
                }
            }
            gs = ge;
        }
    }

    // Endian-safe serialization
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
    static uint32_t read_u32(const uint8_t* d, size_t& off) {
        uint32_t v = d[off] | (d[off+1]<<8) | (d[off+2]<<16) | (d[off+3]<<24);
        off += 4;
        return v;
    }
    static uint16_t read_u16(const uint8_t* d, size_t& off) {
        uint16_t v = d[off] | (d[off+1]<<8);
        off += 2;
        return v;
    }


};

} // namespace crumpiler
