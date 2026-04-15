#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Universal Semantic Ring Definitions
// ═══════════════════════════════════════════════════════════════════════
// These rings are HARDCODED in the crumpiler binary.
// They do NOT ship in the .crk legend.
// Sub-10 bits encodes every token across all major languages.
// ═══════════════════════════════════════════════════════════════════════

#include "types.hpp"

namespace crumpiler::rings {

// ── Ring IDs ───────────────────────────────────────────────────────────
enum RingId : uint16_t {
    WHITESPACE = 0,
    CONDITIONAL,
    LOOP,
    TYPE_PRIM,
    TYPE_QUAL,
    ACCESS,
    CLASS_DEF,
    OOP,
    FLOW,
    LOGIC,
    PREPROC,
    CAST,
    MEMORY,
    USING,
    STD_CONTAINER,
    STD_IO,
    STD_ALGO,
    MATH,
    ASSERT,
    BRACKET,
    OPERATOR,
    RING_COUNT  // sentinel
};

// ── Ring Definitions ───────────────────────────────────────────────────
// Each ring is a constexpr array of tokens. Forward/back delta encoding
// navigates within a ring using small signed offsets.

static constexpr RingDef RING_TABLE[] = {
    // ── WHITESPACE ──────────────────────────────────
    // _ = space,  | = newline,  > = tab,  >> = indent(4 spaces)
    {"WHITESPACE", 4, {"_", "|", "\t", "__"}},

    // ── CONDITIONAL ─────────────────────────────────
    {"CONDITIONAL", 5, {"if", "else", "switch", "case", "default"}},

    // ── LOOP ────────────────────────────────────────
    {"LOOP", 6, {"for", "while", "do", "break", "continue", "goto"}},

    // ── TYPE_PRIM ───────────────────────────────────
    {"TYPE_PRIM", 22, {
        "void", "int", "float", "double", "char", "bool",
        "short", "long", "unsigned", "signed", "auto", "size_t",
        "uint8_t", "uint16_t", "uint32_t", "uint64_t",
        "int8_t", "int16_t", "int32_t", "int64_t",
        "uchar", "uint"
    }},

    // ── TYPE_QUAL ───────────────────────────────────
    {"TYPE_QUAL", 12, {
        "const", "constexpr", "consteval", "constinit",
        "volatile", "mutable", "static", "inline", "extern",
        "thread_local", "register", "restrict"
    }},

    // ── ACCESS ──────────────────────────────────────
    {"ACCESS", 4, {"public", "private", "protected", "friend"}},

    // ── CLASS_DEF ───────────────────────────────────
    {"CLASS_DEF", 9, {
        "class", "struct", "enum", "union", "namespace",
        "template", "typename", "concept", "requires"
    }},

    // ── OOP ─────────────────────────────────────────
    {"OOP", 6, {
        "virtual", "override", "final",
        "this", "new", "delete"
    }},

    // ── FLOW ────────────────────────────────────────
    {"FLOW", 5, {"return", "throw", "try", "catch", "noexcept"}},

    // ── LOGIC ───────────────────────────────────────
    {"LOGIC", 6, {"true", "false", "nullptr", "NULL", "TRUE", "FALSE"}},

    // ── PREPROC ─────────────────────────────────────
    {"PREPROC", 12, {
        "#include", "#define", "#ifdef", "#ifndef",
        "#endif", "#pragma", "#if", "#else", "#elif",
        "#undef", "#error", "#warning"
    }},

    // ── CAST ────────────────────────────────────────
    {"CAST", 4, {"static_cast", "dynamic_cast", "reinterpret_cast", "const_cast"}},

    // ── MEMORY ──────────────────────────────────────
    {"MEMORY", 5, {"sizeof", "alignof", "offsetof", "decltype", "typeid"}},

    // ── USING ───────────────────────────────────────
    {"USING", 3, {"using", "typedef", "operator"}},

    // ── STD_CONTAINER ───────────────────────────────
    {"STD_CONTAINER", 17, {
        "std::vector", "std::string", "std::map",
        "std::unordered_map", "std::set", "std::array",
        "std::pair", "std::tuple", "std::optional",
        "std::variant", "std::unique_ptr", "std::shared_ptr",
        "std::span", "std::deque", "std::list",
        "std::unordered_set", "std::string_view"
    }},

    // ── STD_IO ──────────────────────────────────────
    {"STD_IO", 22, {
        "std::cout", "std::cin", "std::cerr", "std::endl",
        "printf", "fprintf", "sprintf", "snprintf",
        "sscanf", "scanf", "puts", "fputs", "fgets",
        "fopen", "fclose", "fread", "fwrite", "fseek",
        "ftell", "fflush", "stderr", "stdout"
    }},

    // ── STD_ALGO ────────────────────────────────────
    {"STD_ALGO", 10, {
        "std::sort", "std::find", "std::transform",
        "std::min", "std::max", "std::clamp", "std::abs",
        "std::move", "std::forward", "std::swap"
    }},

    // ── MATH ────────────────────────────────────────
    {"MATH", 30, {
        "sqrtf", "sqrt", "sinf", "sin", "cosf", "cos",
        "tanf", "tan", "atan2f", "atan2", "fabsf", "fabs",
        "floorf", "floor", "ceilf", "ceil", "roundf", "round",
        "powf", "pow", "logf", "log", "expf", "exp",
        "fminf", "fmin", "fmaxf", "fmax", "M_PI", "M_PI_2"
    }},

    // ── ASSERT ──────────────────────────────────────
    {"ASSERT", 4, {"assert", "UNUSED", "UNUSED_VARS", "static_assert"}},

    // ── BRACKET ─────────────────────────────────────
    {"BRACKET", 10, {"{", "}", "(", ")", "[", "]", "<", ">", "<<", ">>"}},

    // ── OPERATOR ────────────────────────────────────
    {"OPERATOR", 36, {
        "=", "==", "!=", "<=", ">=", "+=", "-=", "*=", "/=",
        "++", "--", "&&", "||", "!", "&", "|", "^", "~",
        "+", "-", "*", "/", "%", "::", "->", ".", ",", ";",
        ":", "?", "|=", "&=", "^=", "<<=", ">>=", "..."
    }},
};

static_assert(
    sizeof(RING_TABLE) / sizeof(RING_TABLE[0]) == RING_COUNT,
    "Ring table size must match RING_COUNT"
);

// ── Total unique ring tokens ───────────────────────────────────────────
// Count all tokens across all rings at compile time.
consteval auto total_ring_tokens() noexcept -> uint16_t {
    uint16_t total = 0;
    for (auto const& ring : RING_TABLE) {
        total += ring.token_count;
    }
    return total;
}

static constexpr uint16_t TOTAL_RING_TOKENS = total_ring_tokens();
// Expected: ~232 tokens. Fits in 8 bits (256 capacity). Sub-10 bits confirmed.

// ── Lookup ─────────────────────────────────────────────────────────────
// Find which ring a token belongs to, and its position.
// Returns {ring_id, position} or {RING_COUNT, 0} if not found.
struct RingLookup {
    uint16_t ring_id  = RING_COUNT;
    uint16_t position = 0;
    bool     found    = false;
};

[[nodiscard]] inline auto find_in_rings(std::string_view token) noexcept -> RingLookup {
    for (uint16_t r = 0; r < RING_COUNT; ++r) {
        int pos = RING_TABLE[r].find(token);
        if (pos >= 0) {
            return {r, static_cast<uint16_t>(pos), true};
        }
    }
    return {};
}

} // namespace crumpiler::rings
