#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — C/C++ Lexer
// ═══════════════════════════════════════════════════════════════════════
// Tokenizes C/C++ source into a stream of classified tokens.
// Handles keywords, operators, preprocessor, std:: qualifications,
// string/char/number literals, and identifiers.
// ═══════════════════════════════════════════════════════════════════════

#include "../core/types.hpp"
#include "../core/rings.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
#include <cstring>

namespace crumpiler {

struct LexedToken {
    std::string text;
    Channel     channel = Channel::Ring;
    uint16_t    ring_id = rings::RING_COUNT;
    uint16_t    ring_pos = 0;
    LiteralKind lit_kind = LiteralKind::String;
    bool        is_literal = false;
};

class Lexer {
public:
    // Tokenize full source text. Returns vector of tokens.
    [[nodiscard]] auto tokenize(std::string_view source) -> std::vector<LexedToken> {
        src_ = source;
        pos_ = 0;
        tokens_.clear();
        strings_.clear();
        numbers_.clear();

        while (pos_ < src_.size()) {
            // ── Whitespace → single _ or | separator ───
            // Consume all whitespace between tokens.
            // If it contained a newline → emit |
            // If it was spaces/tabs only → emit _
            // One separator token per gap, no matter how wide.
            if (std::isspace(static_cast<unsigned char>(cur()))) {
                bool has_newline = false;
                while (pos_ < src_.size() &&
                       std::isspace(static_cast<unsigned char>(src_[pos_]))) {
                    if (src_[pos_] == '\n') has_newline = true;
                    ++pos_;
                }
                // Only emit separator if there are tokens before this
                if (!tokens_.empty()) {
                    emit_classified(has_newline ? "|" : "_");
                }
                continue;
            }

            // ── Comments ───────────────────────────────
            if (match("//")) {
                skip_line();
                continue;
            }
            if (match("/*")) {
                skip_block_comment();
                continue;
            }

            // ── String literals ────────────────────────
            if (cur() == '"') {
                auto s = read_string_literal();
                strings_.push_back(s);
                LexedToken tok;
                tok.text = s;
                tok.channel = Channel::Literal;
                tok.lit_kind = LiteralKind::String;
                tok.is_literal = true;
                tokens_.push_back(std::move(tok));
                continue;
            }

            // ── Char literals ──────────────────────────
            if (cur() == '\'') {
                auto s = read_char_literal();
                LexedToken tok;
                tok.text = s;
                tok.channel = Channel::Literal;
                tok.lit_kind = LiteralKind::Char;
                tok.is_literal = true;
                tokens_.push_back(std::move(tok));
                continue;
            }

            // ── Number literals ────────────────────────
            if (std::isdigit(static_cast<unsigned char>(cur())) ||
                (cur() == '.' && pos_ + 1 < src_.size() &&
                 std::isdigit(static_cast<unsigned char>(src_[pos_ + 1])))) {
                auto s = read_number();
                numbers_.push_back(s);
                LexedToken tok;
                tok.text = s;
                tok.channel = Channel::Literal;
                tok.lit_kind = LiteralKind::Number;
                tok.is_literal = true;
                tokens_.push_back(std::move(tok));
                continue;
            }

            // ── Preprocessor directives ────────────────
            if (cur() == '#') {
                auto s = read_preprocessor();
                emit_classified(s);
                continue;
            }

            // ── Multi-char operators (check longest first) ──
            if (auto op = try_multi_char_op(); !op.empty()) {
                emit_classified(op);
                continue;
            }

            // ── Identifiers and keywords ───────────────
            if (is_ident_start(cur())) {
                auto s = read_identifier();
                // Check for std:: qualification
                if (s == "std" && pos_ < src_.size() && match("::")) {
                    auto member = read_identifier();
                    s = "std::" + member;
                    // Handle nested :: (e.g., std::numbers::pi)
                    if (pos_ < src_.size() && match("::")) {
                        auto sub = read_identifier();
                        s += "::" + sub;
                    }
                }
                emit_classified(s);
                continue;
            }

            // ── Single-char operators/punctuation ──────
            {
                std::string s(1, cur());
                ++pos_;
                emit_classified(s);
            }
        }

        return std::move(tokens_);
    }

    // Access collected string and number literals
    [[nodiscard]] auto strings() const noexcept -> const std::vector<std::string>& { return strings_; }
    [[nodiscard]] auto numbers() const noexcept -> const std::vector<std::string>& { return numbers_; }

private:
    std::string_view src_;
    size_t pos_ = 0;
    std::vector<LexedToken> tokens_;
    std::vector<std::string> strings_;
    std::vector<std::string> numbers_;

    [[nodiscard]] char cur() const noexcept {
        return pos_ < src_.size() ? src_[pos_] : '\0';
    }

    [[nodiscard]] char peek(size_t ahead = 1) const noexcept {
        return (pos_ + ahead < src_.size()) ? src_[pos_ + ahead] : '\0';
    }

    bool match(std::string_view s) noexcept {
        if (pos_ + s.size() > src_.size()) return false;
        if (src_.substr(pos_, s.size()) == s) {
            pos_ += s.size();
            return true;
        }
        return false;
    }

    void skip_whitespace() noexcept {
        while (pos_ < src_.size() && std::isspace(static_cast<unsigned char>(src_[pos_])))
            ++pos_;
    }

    void skip_line() noexcept {
        while (pos_ < src_.size() && src_[pos_] != '\n') ++pos_;
        if (pos_ < src_.size()) ++pos_;
    }

    void skip_block_comment() noexcept {
        while (pos_ + 1 < src_.size()) {
            if (src_[pos_] == '*' && src_[pos_ + 1] == '/') {
                pos_ += 2;
                return;
            }
            ++pos_;
        }
        pos_ = src_.size();
    }

    [[nodiscard]] static bool is_ident_start(char c) noexcept {
        return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
    }
    [[nodiscard]] static bool is_ident_char(char c) noexcept {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
    }

    [[nodiscard]] auto read_identifier() -> std::string {
        size_t start = pos_;
        while (pos_ < src_.size() && is_ident_char(src_[pos_])) ++pos_;
        return std::string(src_.substr(start, pos_ - start));
    }

    [[nodiscard]] auto read_string_literal() -> std::string {
        size_t start = pos_;
        ++pos_; // skip opening "
        while (pos_ < src_.size()) {
            if (src_[pos_] == '\\') { pos_ += 2; continue; }
            if (src_[pos_] == '"') { ++pos_; break; }
            ++pos_;
        }
        return std::string(src_.substr(start, pos_ - start));
    }

    [[nodiscard]] auto read_char_literal() -> std::string {
        size_t start = pos_;
        ++pos_; // skip opening '
        while (pos_ < src_.size()) {
            if (src_[pos_] == '\\') { pos_ += 2; continue; }
            if (src_[pos_] == '\'') { ++pos_; break; }
            ++pos_;
        }
        return std::string(src_.substr(start, pos_ - start));
    }

    [[nodiscard]] auto read_number() -> std::string {
        size_t start = pos_;
        // Handle hex: 0x...
        if (cur() == '0' && (peek() == 'x' || peek() == 'X')) {
            pos_ += 2;
            while (pos_ < src_.size() && std::isxdigit(static_cast<unsigned char>(src_[pos_])))
                ++pos_;
        } else {
            while (pos_ < src_.size() &&
                   (std::isdigit(static_cast<unsigned char>(src_[pos_])) || src_[pos_] == '.'))
                ++pos_;
        }
        // Handle suffixes: e/E, f, u, l, etc.
        while (pos_ < src_.size() && (src_[pos_] == 'e' || src_[pos_] == 'E' ||
               src_[pos_] == 'f' || src_[pos_] == 'F' ||
               src_[pos_] == 'u' || src_[pos_] == 'U' ||
               src_[pos_] == 'l' || src_[pos_] == 'L' ||
               src_[pos_] == '+' || src_[pos_] == '-' ||
               std::isdigit(static_cast<unsigned char>(src_[pos_])))) {
            ++pos_;
        }
        return std::string(src_.substr(start, pos_ - start));
    }

    [[nodiscard]] auto read_preprocessor() -> std::string {
        ++pos_; // skip #
        skip_whitespace();
        std::string directive = "#";
        while (pos_ < src_.size() && is_ident_char(src_[pos_])) {
            directive += src_[pos_++];
        }
        return directive;
    }

    // Try to match multi-character operators (longest match first).
    [[nodiscard]] auto try_multi_char_op() -> std::string {
        // 3-char operators
        static constexpr std::string_view ops3[] = {
            "<<=", ">>=", "..."
        };
        for (auto op : ops3) {
            if (pos_ + 3 <= src_.size() && src_.substr(pos_, 3) == op) {
                pos_ += 3;
                return std::string(op);
            }
        }
        // 2-char operators
        static constexpr std::string_view ops2[] = {
            "::", "->", "<<", ">>", "==", "!=", "<=", ">=",
            "+=", "-=", "*=", "/=", "&&", "||", "++", "--",
            "&=", "|=", "^=", "##"
        };
        for (auto op : ops2) {
            if (pos_ + 2 <= src_.size() && src_.substr(pos_, 2) == op) {
                pos_ += 2;
                return std::string(op);
            }
        }
        return {};
    }

    // Classify a token: ring lookup first, then project identifier.
    void emit_classified(const std::string& text) {
        LexedToken tok;
        tok.text = text;

        auto lookup = rings::find_in_rings(text);
        if (lookup.found) {
            tok.channel  = Channel::Ring;
            tok.ring_id  = lookup.ring_id;
            tok.ring_pos = lookup.position;
        } else {
            tok.channel = Channel::Ident;
        }

        tokens_.push_back(std::move(tok));
    }
};

} // namespace crumpiler
