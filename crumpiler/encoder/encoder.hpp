#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Encoder Pipeline v2
// ═══════════════════════════════════════════════════════════════════════
// Pipeline: tokenize → ring map → [ local ident → phrase dedup → freq rank → bitpack
// [ = file-local identifier indexing (5-6 bits vs 18 bits global)
// Phrases are encoded as single tokens with [ parameter slots.
// ═══════════════════════════════════════════════════════════════════════

#include "../core/types.hpp"
#include "../core/rings.hpp"
#include "../core/bitstream.hpp"
#include "../core/freq_rank.hpp"
#include "lexer.hpp"
#include "phrase_finder.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>

namespace crumpiler {

struct EncodeResult {
    uint64_t original_bytes     = 0;
    uint64_t crm_bytes          = 0;
    uint64_t crk_bytes          = 0;
    uint64_t total_tokens       = 0;
    uint64_t stream_tokens      = 0;  // tokens after phrase collapse
    uint64_t unique_tokens      = 0;
    uint64_t ring_token_count   = 0;
    uint64_t ident_count        = 0;
    uint64_t literal_count      = 0;
    uint64_t phrase_count       = 0;
    uint64_t phrase_replacements = 0;
    uint32_t local_ident_count  = 0;
    double   compression_ratio  = 0.0;
};

// ── Encoded token (after all transformations) ──────────────────────────
// A unified token reference used in the final bitstream.
struct EncodedToken {
    Channel  channel = Channel::Ring;
    uint32_t id      = 0;
};

class Encoder {
public:
    [[nodiscard]] auto encode(
        std::string_view source,
        const std::string& crm_path,
        const std::string& crk_path
    ) -> EncodeResult {
        EncodeResult result;
        result.original_bytes = source.size();

        // ── Stage 1: Tokenize ──────────────────────────────────────────
        Lexer lexer;
        auto tokens = lexer.tokenize(source);
        result.total_tokens = tokens.size();

        // ── Stage 2: Build global identifier and literal tables ────────
        std::vector<std::string> ident_table;  // global ident strings
        std::vector<std::string> string_table;
        std::vector<std::string> number_table;

        for (auto& tok : tokens) {
            if (tok.channel == Channel::Ident) {
                uint32_t id = find_or_add(ident_table, tok.text);
                tok.ring_pos = static_cast<uint16_t>(id & 0xFFFF);
                result.ident_count++;
            } else if (tok.channel == Channel::Ring) {
                result.ring_token_count++;
            }
        }
        for (auto& tok : tokens) {
            if (tok.is_literal) {
                if (tok.lit_kind == LiteralKind::String || tok.lit_kind == LiteralKind::Char) {
                    tok.ring_pos = static_cast<uint16_t>(
                        find_or_add(string_table, tok.text) & 0xFFFF);
                } else if (tok.lit_kind == LiteralKind::Number) {
                    tok.ring_pos = static_cast<uint16_t>(
                        find_or_add(number_table, tok.text) & 0xFFFF);
                }
                result.literal_count++;
            }
        }

        // ── Stage 3: [ Local identifier indexing ───────────────────────
        // Build per-file local ident table sorted by frequency.
        // Each ident gets a [N local index (N = 0-based, small).
        struct LocalIdent {
            uint32_t global_id = 0;  // index into ident_table
            uint32_t count     = 0;  // occurrences in this file
            uint32_t local_id  = 0;  // assigned local index
        };
        std::vector<LocalIdent> local_idents;

        // Count occurrences per global ident
        for (auto const& tok : tokens) {
            if (tok.channel == Channel::Ident) {
                uint32_t gid = tok.ring_pos;
                bool found = false;
                for (auto& li : local_idents) {
                    if (li.global_id == gid) { ++li.count; found = true; break; }
                }
                if (!found) {
                    local_idents.push_back({gid, 1, 0});
                }
            }
        }

        // Sort by frequency (highest first) → lowest local_id
        std::sort(local_idents.begin(), local_idents.end(),
            [](const LocalIdent& a, const LocalIdent& b) {
                return a.count > b.count;
            });
        for (uint32_t i = 0; i < local_idents.size(); ++i) {
            local_idents[i].local_id = i;
        }
        result.local_ident_count = static_cast<uint32_t>(local_idents.size());

        // Build global → local mapping for quick lookup
        // (global_id → local_id)
        auto global_to_local = [&](uint32_t gid) -> uint32_t {
            for (auto const& li : local_idents) {
                if (li.global_id == gid) return li.local_id;
            }
            return 0;
        };

        // ── Stage 4: Convert token stream to encoded tokens ────────────
        // Replace global ident IDs with local [ indices.
        std::vector<EncodedToken> stream;
        stream.reserve(tokens.size());

        for (auto const& tok : tokens) {
            EncodedToken et;
            if (tok.channel == Channel::Ring) {
                et.channel = Channel::Ring;
                et.id = ring_global_id(tok.ring_id, tok.ring_pos);
            } else if (tok.channel == Channel::Ident) {
                et.channel = Channel::Ident;
                et.id = global_to_local(tok.ring_pos);  // [ local index!
            } else if (tok.is_literal) {
                et.channel = Channel::Literal;
                et.id = (static_cast<uint32_t>(tok.lit_kind) << 16) | tok.ring_pos;
            }
            stream.push_back(et);
        }

        // ── Stage 5: Phrase dedup on encoded stream ────────────────────
        // Find repeated sequences and replace with phrase references.
        auto phrase_candidates = find_encoded_phrases(stream, 3, 10, 3);
        result.phrase_count = phrase_candidates.size();

        // Store phrase definitions (the actual token sequences)
        struct PhraseDef {
            std::vector<EncodedToken> tokens;
            uint32_t phrase_id = 0;
        };
        std::vector<PhraseDef> phrase_defs;

        // Apply phrase replacements (greedy, longest first)
        for (auto const& pc : phrase_candidates) {
            if (pc.length == 0 || pc.occurrences < 3) continue;
            if (phrase_defs.size() >= 512) break; // cap phrase count

            // Find the first actual occurrence in the CURRENT stream
            // (positions may have shifted from prior replacements)
            int first_match = -1;
            for (size_t i = 0; i + pc.length <= stream.size(); ++i) {
                // Skip tokens already replaced by phrases
                if (stream[i].channel == Channel::Phrase) continue;

                bool match = true;
                // Check using the original signature
                uint64_t sig = 0xcbf29ce484222325ULL;
                for (uint32_t j = 0; j < pc.length; ++j) {
                    sig ^= static_cast<uint64_t>(stream[i + j].channel);
                    sig *= 0x100000001b3ULL;
                    sig ^= stream[i + j].id;
                    sig *= 0x100000001b3ULL;
                }
                if (sig != pc.signature) { continue; }

                first_match = static_cast<int>(i);
                break;
            }
            if (first_match < 0) continue;

            // Capture the phrase definition from the current stream
            PhraseDef def;
            def.phrase_id = static_cast<uint32_t>(phrase_defs.size());
            for (uint32_t i = 0; i < pc.length; ++i) {
                def.tokens.push_back(stream[first_match + i]);
            }

            // Scan stream and replace ALL matching sequences
            uint32_t replacements = 0;
            for (size_t i = 0; i + pc.length <= stream.size(); ) {
                bool match = true;
                for (uint32_t j = 0; j < pc.length; ++j) {
                    if (stream[i + j].channel != def.tokens[j].channel ||
                        stream[i + j].id != def.tokens[j].id) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    stream[i].channel = Channel::Phrase;
                    stream[i].id = def.phrase_id;
                    stream.erase(stream.begin() + i + 1,
                                stream.begin() + i + pc.length);
                    ++replacements;
                    ++i;
                } else {
                    ++i;
                }
            }

            if (replacements >= 2) {
                phrase_defs.push_back(std::move(def));
                result.phrase_replacements += replacements;
            }
        }

        result.stream_tokens = stream.size();

        // ── Stage 6: Frequency ranking on final stream ─────────────────
        FrequencyTable freq;
        for (auto const& et : stream) {
            freq.record(et.channel, et.id);
        }
        freq.finalize();
        result.unique_tokens = freq.size();

        // ── Stage 7: Bitstream encoding ────────────────────────────────
        BitWriter writer;

        // Write CRM header
        CrmHeader crm_hdr;
        crm_hdr.token_count = stream.size();
        writer.write_bytes(&crm_hdr, sizeof(CrmHeader));

        // Write local ident table size + mapping (local_id → global_id)
        uint32_t n_local = static_cast<uint32_t>(local_idents.size());
        writer.write_bytes(&n_local, 4);
        for (auto const& li : local_idents) {
            writer.write_bytes(&li.global_id, 4);
        }

        // Write phrase definitions
        uint32_t n_phrases = static_cast<uint32_t>(phrase_defs.size());
        writer.write_bytes(&n_phrases, 4);
        for (auto const& pd : phrase_defs) {
            uint32_t plen = static_cast<uint32_t>(pd.tokens.size());
            writer.write_bytes(&plen, 4);
            for (auto const& pt : pd.tokens) {
                uint8_t ch = static_cast<uint8_t>(pt.channel);
                writer.write_bytes(&ch, 1);
                writer.write_bytes(&pt.id, 4);
            }
        }

        writer.flush_byte();

        // Encode each token as its frequency rank via Elias gamma
        for (auto const& et : stream) {
            uint32_t rank = freq.find_rank(et.channel, et.id);
            if (rank > 0) {
                writer.write_gamma(rank);
            } else {
                writer.write_gamma(1); // fallback
            }
        }

        writer.flush_byte();

        // ── Write .crm file ────────────────────────────────────────────
        {
            std::ofstream out(crm_path, std::ios::binary);
            if (out.is_open()) {
                out.write(reinterpret_cast<const char*>(writer.data()), writer.size());
                result.crm_bytes = writer.size();
            }
        }

        // ── Write .crk legend ──────────────────────────────────────────
        {
            std::ofstream out(crk_path, std::ios::binary);
            if (out.is_open()) {
                CrkHeader crk_hdr;
                crk_hdr.ident_count = static_cast<uint32_t>(ident_table.size());
                crk_hdr.phrase_count = static_cast<uint32_t>(phrase_defs.size());
                crk_hdr.string_count = static_cast<uint32_t>(string_table.size());
                crk_hdr.number_count = static_cast<uint32_t>(number_table.size());
                crk_hdr.freq_count = static_cast<uint32_t>(freq.size());
                out.write(reinterpret_cast<const char*>(&crk_hdr), sizeof(CrkHeader));

                // Frequency rank table
                for (auto const& entry : freq.entries()) {
                    uint8_t ch = static_cast<uint8_t>(entry.key.channel);
                    out.write(reinterpret_cast<const char*>(&ch), 1);
                    out.write(reinterpret_cast<const char*>(&entry.key.id), 4);
                    out.write(reinterpret_cast<const char*>(&entry.count), 4);
                }

                // Global identifier strings
                for (auto const& ident : ident_table) {
                    uint16_t len = static_cast<uint16_t>(ident.size());
                    out.write(reinterpret_cast<const char*>(&len), 2);
                    out.write(ident.c_str(), ident.size());
                }

                // String literal table
                for (auto const& s : string_table) {
                    uint32_t len = static_cast<uint32_t>(s.size());
                    out.write(reinterpret_cast<const char*>(&len), 4);
                    out.write(s.c_str(), s.size());
                }

                // Number literal table
                for (auto const& n : number_table) {
                    uint16_t len = static_cast<uint16_t>(n.size());
                    out.write(reinterpret_cast<const char*>(&len), 2);
                    out.write(n.c_str(), n.size());
                }

                result.crk_bytes = static_cast<uint64_t>(out.tellp());
            }
        }

        // ── Stats ──────────────────────────────────────────────────────
        uint64_t total_compressed = result.crm_bytes + result.crk_bytes;
        result.compression_ratio = (total_compressed > 0 && result.original_bytes > 0)
            ? (static_cast<double>(total_compressed) / result.original_bytes) * 100.0
            : 0.0;

        return result;
    }

private:
    [[nodiscard]] static auto find_or_add(
        std::vector<std::string>& table,
        const std::string& value
    ) -> uint32_t {
        for (uint32_t i = 0; i < table.size(); ++i) {
            if (table[i] == value) return i;
        }
        table.push_back(value);
        return static_cast<uint32_t>(table.size() - 1);
    }

    // ── Phrase finder for encoded stream ───────────────────────────────
    struct EncodedPhrase {
        uint32_t first_pos    = 0;
        uint32_t length       = 0;
        uint32_t occurrences  = 0;
        uint64_t bytes_saved  = 0;
        uint64_t signature    = 0;
    };

    [[nodiscard]] static auto find_encoded_phrases(
        const std::vector<EncodedToken>& stream,
        uint32_t min_len, uint32_t max_len, uint32_t min_occ
    ) -> std::vector<EncodedPhrase> {

        std::vector<EncodedPhrase> results;

        for (uint32_t len = max_len; len >= min_len; --len) {
            if (stream.size() < len) continue;

            struct Entry { uint64_t sig; uint32_t start; };
            std::vector<Entry> entries;
            entries.reserve(stream.size() - len + 1);

            for (uint32_t i = 0; i <= stream.size() - len; ++i) {
                uint64_t sig = 0xcbf29ce484222325ULL;
                for (uint32_t j = 0; j < len; ++j) {
                    sig ^= static_cast<uint64_t>(stream[i + j].channel);
                    sig *= 0x100000001b3ULL;
                    sig ^= stream[i + j].id;
                    sig *= 0x100000001b3ULL;
                }
                entries.push_back({sig, i});
            }

            std::sort(entries.begin(), entries.end(),
                [](const Entry& a, const Entry& b) { return a.sig < b.sig; });

            uint32_t gs = 0;
            while (gs < entries.size()) {
                uint64_t sig = entries[gs].sig;
                uint32_t ge = gs + 1;
                while (ge < entries.size() && entries[ge].sig == sig) ++ge;

                uint32_t count = ge - gs;
                if (count >= min_occ) {
                    // Verify first vs rest
                    uint32_t verified = 0;
                    for (uint32_t j = gs; j < ge; ++j) {
                        bool match = true;
                        for (uint32_t k = 0; k < len; ++k) {
                            if (stream[entries[gs].start + k].channel !=
                                stream[entries[j].start + k].channel ||
                                stream[entries[gs].start + k].id !=
                                stream[entries[j].start + k].id) {
                                match = false; break;
                            }
                        }
                        if (match) ++verified;
                    }

                    if (verified >= min_occ) {
                        EncodedPhrase ep;
                        ep.first_pos = entries[gs].start;
                        ep.length = len;
                        ep.occurrences = verified;
                        ep.bytes_saved = static_cast<uint64_t>(verified - 1) * len * 3;
                        ep.signature = sig;
                        results.push_back(ep);
                    }
                }
                gs = ge;
            }
        }

        std::sort(results.begin(), results.end(),
            [](const EncodedPhrase& a, const EncodedPhrase& b) {
                return a.bytes_saved > b.bytes_saved;
            });

        // Cap at 1024 most impactful phrases
        if (results.size() > 1024) results.resize(1024);
        return results;
    }
};

} // namespace crumpiler
