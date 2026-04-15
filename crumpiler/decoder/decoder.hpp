#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Decoder v2 (The Crumpiler itself)
// ═══════════════════════════════════════════════════════════════════════
// Reads .crk (legend) + .crm (bitstream w/ [ local ident table + phrases)
// and reconstructs the original source.
// ═══════════════════════════════════════════════════════════════════════

#include "../core/types.hpp"
#include "../core/rings.hpp"
#include "../core/bitstream.hpp"
#include <string>
#include <vector>
#include <fstream>

namespace crumpiler {

class Decoder {
public:
    bool load_key(const std::string& crk_path) {
        std::ifstream in(crk_path, std::ios::binary);
        if (!in.is_open()) return false;

        in.read(reinterpret_cast<char*>(&crk_header_), sizeof(CrkHeader));
        if (crk_header_.magic != CRK_MAGIC) return false;

        // Read frequency rank table
        rank_table_.resize(crk_header_.freq_count);
        for (uint32_t i = 0; i < crk_header_.freq_count; ++i) {
            uint8_t ch = 0;
            uint32_t id = 0, count = 0;
            in.read(reinterpret_cast<char*>(&ch), 1);
            in.read(reinterpret_cast<char*>(&id), 4);
            in.read(reinterpret_cast<char*>(&count), 4);
            rank_table_[i] = {static_cast<Channel>(ch), id, count};
        }

        // Read global identifier table
        ident_table_.resize(crk_header_.ident_count);
        for (uint32_t i = 0; i < crk_header_.ident_count; ++i) {
            uint16_t len = 0;
            in.read(reinterpret_cast<char*>(&len), 2);
            ident_table_[i].resize(len);
            in.read(ident_table_[i].data(), len);
        }

        // Read string literal table
        string_table_.resize(crk_header_.string_count);
        for (uint32_t i = 0; i < crk_header_.string_count; ++i) {
            uint32_t len = 0;
            in.read(reinterpret_cast<char*>(&len), 4);
            string_table_[i].resize(len);
            in.read(string_table_[i].data(), len);
        }

        // Read number literal table
        number_table_.resize(crk_header_.number_count);
        for (uint32_t i = 0; i < crk_header_.number_count; ++i) {
            uint16_t len = 0;
            in.read(reinterpret_cast<char*>(&len), 2);
            number_table_[i].resize(len);
            in.read(number_table_[i].data(), len);
        }

        key_loaded_ = true;
        return true;
    }

    [[nodiscard]] auto decode(const std::string& crm_path) -> std::string {
        if (!key_loaded_) return "";

        // Read .crm into memory
        std::ifstream in(crm_path, std::ios::binary | std::ios::ate);
        if (!in.is_open()) return "";
        size_t file_size = in.tellg();
        in.seekg(0);
        std::vector<uint8_t> data(file_size);
        in.read(reinterpret_cast<char*>(data.data()), file_size);

        if (file_size < sizeof(CrmHeader)) return "";
        CrmHeader crm_hdr;
        std::memcpy(&crm_hdr, data.data(), sizeof(CrmHeader));
        if (crm_hdr.magic != CRM_MAGIC) return "";

        // Read past CRM header
        size_t offset = sizeof(CrmHeader);

        // ── Read [ local ident table ───────────────────────────────────
        uint32_t n_local = 0;
        std::memcpy(&n_local, data.data() + offset, 4);
        offset += 4;
        local_to_global_.resize(n_local);
        for (uint32_t i = 0; i < n_local; ++i) {
            uint32_t gid = 0;
            std::memcpy(&gid, data.data() + offset, 4);
            offset += 4;
            local_to_global_[i] = gid;
        }

        // ── Read phrase definitions ────────────────────────────────────
        uint32_t n_phrases = 0;
        std::memcpy(&n_phrases, data.data() + offset, 4);
        offset += 4;

        struct TokenRef {
            Channel channel;
            uint32_t id;
        };
        struct PhraseDef {
            std::vector<TokenRef> tokens;
        };
        phrase_defs_.clear();
        phrase_defs_.resize(n_phrases);

        for (uint32_t p = 0; p < n_phrases; ++p) {
            uint32_t plen = 0;
            std::memcpy(&plen, data.data() + offset, 4);
            offset += 4;
            phrase_defs_[p].tokens.resize(plen);
            for (uint32_t t = 0; t < plen; ++t) {
                uint8_t ch = 0;
                uint32_t id = 0;
                ch = data[offset]; offset += 1;
                std::memcpy(&id, data.data() + offset, 4); offset += 4;
                phrase_defs_[p].tokens[t] = {static_cast<Channel>(ch), id};
            }
        }

        // ── Decode bitstream ───────────────────────────────────────────
        BitReader reader(data.data() + offset, file_size - offset);

        std::string output;
        output.reserve(file_size * 8);

        for (uint64_t t = 0; t < crm_hdr.token_count; ++t) {
            uint32_t rank = reader.read_gamma();
            if (rank == 0 || rank > rank_table_.size()) break;

            auto const& entry = rank_table_[rank - 1];

            if (entry.channel == Channel::Phrase) {
                // Expand phrase: resolve each token in the definition
                if (entry.id < phrase_defs_.size()) {
                    for (auto const& pt : phrase_defs_[entry.id].tokens) {
                        output += resolve_token(pt.channel, pt.id);
                    }
                }
            } else {
                output += resolve_token(entry.channel, entry.id);
            }
        }

        return output;
    }

private:
    struct RankInfo {
        Channel  channel = Channel::Ring;
        uint32_t id      = 0;
        uint32_t count   = 0;
    };

    struct PhraseDefInternal {
        struct TokenRef { Channel channel; uint32_t id; };
        std::vector<TokenRef> tokens;
    };

    CrkHeader crk_header_{};
    std::vector<RankInfo>    rank_table_;
    std::vector<std::string> ident_table_;
    std::vector<std::string> string_table_;
    std::vector<std::string> number_table_;
    std::vector<uint32_t>    local_to_global_;   // [ local → global mapping
    std::vector<PhraseDefInternal> phrase_defs_;
    bool key_loaded_ = false;

    [[nodiscard]] auto resolve_token(Channel ch, uint32_t id) const -> std::string {
        switch (ch) {
        case Channel::Ring: {
            uint16_t ring_id = static_cast<uint16_t>(id / MAX_RING_SIZE);
            uint16_t ring_pos = static_cast<uint16_t>(id % MAX_RING_SIZE);
            if (ring_id < rings::RING_COUNT &&
                ring_pos < rings::RING_TABLE[ring_id].token_count) {
                std::string_view tok{rings::RING_TABLE[ring_id].tokens[ring_pos]};
                if (ring_id == rings::WHITESPACE) {
                    if (tok == "_")  return " ";
                    if (tok == "|")  return "\n";
                    if (tok == "\t") return "\t";
                    if (tok == "__") return "  ";
                }
                return std::string(tok);
            }
            return "??";
        }
        case Channel::Ident: {
            // [ local index → global index → string
            uint32_t global_id = id;
            if (id < local_to_global_.size()) {
                global_id = local_to_global_[id];
            }
            if (global_id < ident_table_.size()) return ident_table_[global_id];
            return "??";
        }
        case Channel::Literal: {
            auto kind = static_cast<LiteralKind>(id >> 16);
            uint32_t idx = id & 0xFFFF;
            switch (kind) {
            case LiteralKind::String:
            case LiteralKind::Char:
                if (idx < string_table_.size()) return string_table_[idx];
                break;
            case LiteralKind::Number:
                if (idx < number_table_.size()) return number_table_[idx];
                break;
            }
            return "??";
        }
        case Channel::Phrase:
            // Phrases should be expanded by the caller, not here
            return "^PHRASE";
        }
        return "??";
    }
};

} // namespace crumpiler
