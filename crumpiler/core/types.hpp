#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Core Type Definitions
// ═══════════════════════════════════════════════════════════════════════
// All value types. No heap allocation in hot paths.
// C++20. Zero dependencies. Everything from scratch.
//
// SEPARATION OF CONCERNS:
// - format.hpp   → magic numbers, format IDs, extensions
// - types.hpp    → code-mode types (Token, Channel, Ring, Phrase)
// - bitstream.hpp → universal bit I/O (used by ALL modes)
// - freq_rank.hpp → universal frequency ranking (used by ALL modes)
// ═══════════════════════════════════════════════════════════════════════

#include <cstdint>
#include <cstring>
#include <string>
#include <array>
#include <string_view>
#include "format.hpp"

namespace crumpiler {

// ── Token Channel (CODE MODE ONLY) ────────────────────────────────────
// 2-bit prefix in the code-mode bitstream identifies the channel.
enum class Channel : uint8_t {
    Ring    = 0b00,   // Universal language token (keyword, operator, bracket)
    Ident   = 0b01,   // Project-specific identifier
    Phrase  = 0b10,   // Reference to a repeated multi-token phrase
    Literal = 0b11,   // String/number/char literal reference
};

// ── Literal Kind ───────────────────────────────────────────────────────
enum class LiteralKind : uint8_t {
    String = 0,
    Number = 1,
    Char   = 2,
};

// ── Token ──────────────────────────────────────────────────────────────
// A single token as produced by the lexer.
// After ring mapping, ring_id and ring_pos are filled in.
// After frequency ranking, freq_rank is assigned.
struct Token {
    Channel   channel    = Channel::Ring;
    uint16_t  ring_id    = 0;       // Which semantic ring (for Channel::Ring)
    uint16_t  ring_pos   = 0;       // Position within that ring
    uint32_t  ident_id   = 0;       // Index into project identifier table
    uint32_t  literal_id = 0;       // Index into string/number table
    uint32_t  phrase_id  = 0;       // Index into phrase table
    LiteralKind lit_kind = LiteralKind::String;

    // Original text (used during encoding, not stored in .crm)
    // Using string instead of string_view for ownership safety
    std::string text{};
    bool is_literal = false;
};

// ── Ring Definition ────────────────────────────────────────────────────
static constexpr uint16_t MAX_RING_SIZE = 64;
static constexpr uint16_t MAX_RINGS     = 32;

struct RingDef {
    const char*  name         = "";
    uint16_t     token_count  = 0;
    std::array<const char*, MAX_RING_SIZE> tokens{};

    [[nodiscard]] constexpr auto find(std::string_view tok) const noexcept -> int {
        for (uint16_t i = 0; i < token_count; ++i) {
            if (tok == std::string_view{tokens[i]}) return static_cast<int>(i);
        }
        return -1;
    }
};

// ── Phrase (code mode) ─────────────────────────────────────────────────
static constexpr uint16_t MAX_PHRASE_LENGTH = 16;

struct Phrase {
    uint32_t id           = 0;
    uint16_t token_count  = 0;
    uint32_t occurrences  = 0;
    uint64_t bytes_saved  = 0;
    struct TokenRef {
        Channel  channel = Channel::Ring;
        uint32_t id      = 0;
    };
    std::array<TokenRef, MAX_PHRASE_LENGTH> tokens{};
};

// ── Code-Mode File Headers ─────────────────────────────────────────────
struct CrkHeader {
    uint32_t magic        = CRK_MAGIC;
    uint16_t version      = FORMAT_VERSION;
    uint8_t  lang_id      = 1;     // 0=C, 1=C++, 2=Python, etc.
    uint32_t ident_count  = 0;
    uint32_t phrase_count = 0;
    uint32_t string_count = 0;
    uint32_t number_count = 0;
    uint32_t freq_count   = 0;
};

struct CrmHeader {
    uint32_t magic        = CRM_MAGIC;
    uint32_t key_hash     = 0;
    uint64_t token_count  = 0;
    uint64_t bit_count    = 0;
};

// ── Utility ────────────────────────────────────────────────────────────
[[nodiscard]] constexpr auto bits_for_rank(uint32_t rank) noexcept -> uint8_t {
    if (rank == 0) return 1;
    uint8_t bits = 0;
    uint32_t v = rank;
    while (v > 0) { ++bits; v >>= 1; }
    return bits;
}

[[nodiscard]] constexpr auto ring_global_id(uint16_t ring_id, uint16_t ring_pos) noexcept -> uint32_t {
    return static_cast<uint32_t>(ring_id) * MAX_RING_SIZE + ring_pos;
}

} // namespace crumpiler
