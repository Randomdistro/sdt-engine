#pragma once

#include <charconv>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace sdt_solver::json {

struct Value;
using Array = std::vector<Value>;
using Object = std::map<std::string, Value>;

struct Value {
    using Storage = std::variant<
        std::nullptr_t,
        bool,
        double,
        std::string,
        Array,
        Object
    >;

    Storage storage{};

    Value() = default;
    Value(std::nullptr_t) : storage(nullptr) {}
    Value(bool value) : storage(value) {}
    Value(double value) : storage(value) {}
    Value(int value) : storage(static_cast<double>(value)) {}
    Value(std::string value) : storage(std::move(value)) {}
    Value(const char* value) : storage(std::string(value)) {}
    Value(Array value) : storage(std::move(value)) {}
    Value(Object value) : storage(std::move(value)) {}

    [[nodiscard]] auto is_null() const noexcept -> bool {
        return std::holds_alternative<std::nullptr_t>(storage);
    }
    [[nodiscard]] auto is_bool() const noexcept -> bool {
        return std::holds_alternative<bool>(storage);
    }
    [[nodiscard]] auto is_number() const noexcept -> bool {
        return std::holds_alternative<double>(storage);
    }
    [[nodiscard]] auto is_string() const noexcept -> bool {
        return std::holds_alternative<std::string>(storage);
    }
    [[nodiscard]] auto is_array() const noexcept -> bool {
        return std::holds_alternative<Array>(storage);
    }
    [[nodiscard]] auto is_object() const noexcept -> bool {
        return std::holds_alternative<Object>(storage);
    }

    [[nodiscard]] auto boolean() const -> bool {
        return std::get<bool>(storage);
    }
    [[nodiscard]] auto number() const -> double {
        return std::get<double>(storage);
    }
    [[nodiscard]] auto string() const -> const std::string& {
        return std::get<std::string>(storage);
    }
    [[nodiscard]] auto array() const -> const Array& {
        return std::get<Array>(storage);
    }
    [[nodiscard]] auto array() -> Array& {
        return std::get<Array>(storage);
    }
    [[nodiscard]] auto object() const -> const Object& {
        return std::get<Object>(storage);
    }
    [[nodiscard]] auto object() -> Object& {
        return std::get<Object>(storage);
    }
};

class ParseError final : public std::runtime_error {
public:
    ParseError(std::string message, std::size_t offset)
        : std::runtime_error(
            std::move(message) + " at byte " + std::to_string(offset)
        ) {}
};

class Parser {
public:
    explicit Parser(std::string_view input) : input_(input) {}

    [[nodiscard]] auto parse() -> Value {
        skip_space();
        Value result = parse_value();
        skip_space();
        if (position_ != input_.size()) fail("trailing JSON content");
        return result;
    }

private:
    std::string_view input_;
    std::size_t position_{};

    [[noreturn]] void fail(const std::string& message) const {
        throw ParseError(message, position_);
    }

    void skip_space() noexcept {
        while (position_ < input_.size()) {
            const char ch = input_[position_];
            if (ch != ' ' && ch != '\t' && ch != '\r' && ch != '\n') break;
            ++position_;
        }
    }

    [[nodiscard]] auto take(char expected) -> bool {
        if (position_ < input_.size() && input_[position_] == expected) {
            ++position_;
            return true;
        }
        return false;
    }

    void expect(char expected) {
        if (!take(expected)) {
            fail(std::string("expected '") + expected + "'");
        }
    }

    void expect_literal(std::string_view literal) {
        if (input_.substr(position_, literal.size()) != literal) {
            fail("invalid JSON literal");
        }
        position_ += literal.size();
    }

    [[nodiscard]] auto parse_value() -> Value {
        if (position_ >= input_.size()) fail("expected JSON value");
        switch (input_[position_]) {
            case 'n':
                expect_literal("null");
                return nullptr;
            case 't':
                expect_literal("true");
                return true;
            case 'f':
                expect_literal("false");
                return false;
            case '"':
                return parse_string();
            case '[':
                return parse_array();
            case '{':
                return parse_object();
            default:
                if (input_[position_] == '-'
                    || (input_[position_] >= '0' && input_[position_] <= '9')) {
                    return parse_number();
                }
                fail("invalid JSON value");
        }
    }

    [[nodiscard]] auto parse_number() -> Value {
        const std::size_t start = position_;
        static_cast<void>(take('-'));
        if (take('0')) {
            if (position_ < input_.size()
                && input_[position_] >= '0' && input_[position_] <= '9') {
                fail("leading zero in number");
            }
        } else {
            if (position_ >= input_.size()
                || input_[position_] < '1' || input_[position_] > '9') {
                fail("invalid number");
            }
            while (position_ < input_.size()
                && input_[position_] >= '0' && input_[position_] <= '9') {
                ++position_;
            }
        }
        if (take('.')) {
            if (position_ >= input_.size()
                || input_[position_] < '0' || input_[position_] > '9') {
                fail("fraction requires digits");
            }
            while (position_ < input_.size()
                && input_[position_] >= '0' && input_[position_] <= '9') {
                ++position_;
            }
        }
        if (position_ < input_.size()
            && (input_[position_] == 'e' || input_[position_] == 'E')) {
            ++position_;
            if (position_ < input_.size()
                && (input_[position_] == '+' || input_[position_] == '-')) {
                ++position_;
            }
            if (position_ >= input_.size()
                || input_[position_] < '0' || input_[position_] > '9') {
                fail("exponent requires digits");
            }
            while (position_ < input_.size()
                && input_[position_] >= '0' && input_[position_] <= '9') {
                ++position_;
            }
        }
        double result{};
        const auto token = input_.substr(start, position_ - start);
        const auto conversion =
            std::from_chars(token.data(), token.data() + token.size(), result);
        if (conversion.ec != std::errc{} || !std::isfinite(result)) {
            fail("number is outside finite double range");
        }
        return result;
    }

    [[nodiscard]] auto parse_hex4() -> std::uint32_t {
        std::uint32_t value = 0;
        for (int i = 0; i < 4; ++i) {
            if (position_ >= input_.size()) fail("truncated unicode escape");
            const char ch = input_[position_++];
            value <<= 4;
            if (ch >= '0' && ch <= '9') value |= static_cast<unsigned>(ch - '0');
            else if (ch >= 'a' && ch <= 'f') {
                value |= static_cast<unsigned>(ch - 'a' + 10);
            } else if (ch >= 'A' && ch <= 'F') {
                value |= static_cast<unsigned>(ch - 'A' + 10);
            } else {
                fail("invalid unicode escape");
            }
        }
        return value;
    }

    static void append_utf8(std::string& output, std::uint32_t codepoint) {
        if (codepoint <= 0x7f) {
            output.push_back(static_cast<char>(codepoint));
        } else if (codepoint <= 0x7ff) {
            output.push_back(static_cast<char>(0xc0 | (codepoint >> 6)));
            output.push_back(static_cast<char>(0x80 | (codepoint & 0x3f)));
        } else if (codepoint <= 0xffff) {
            output.push_back(static_cast<char>(0xe0 | (codepoint >> 12)));
            output.push_back(
                static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f))
            );
            output.push_back(static_cast<char>(0x80 | (codepoint & 0x3f)));
        } else {
            output.push_back(static_cast<char>(0xf0 | (codepoint >> 18)));
            output.push_back(
                static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f))
            );
            output.push_back(
                static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f))
            );
            output.push_back(static_cast<char>(0x80 | (codepoint & 0x3f)));
        }
    }

    [[nodiscard]] auto parse_string() -> std::string {
        expect('"');
        std::string result;
        while (position_ < input_.size()) {
            const unsigned char ch =
                static_cast<unsigned char>(input_[position_++]);
            if (ch == '"') return result;
            if (ch < 0x20) fail("control byte in JSON string");
            if (ch != '\\') {
                result.push_back(static_cast<char>(ch));
                continue;
            }
            if (position_ >= input_.size()) fail("truncated string escape");
            const char escape = input_[position_++];
            switch (escape) {
                case '"': result.push_back('"'); break;
                case '\\': result.push_back('\\'); break;
                case '/': result.push_back('/'); break;
                case 'b': result.push_back('\b'); break;
                case 'f': result.push_back('\f'); break;
                case 'n': result.push_back('\n'); break;
                case 'r': result.push_back('\r'); break;
                case 't': result.push_back('\t'); break;
                case 'u': {
                    std::uint32_t codepoint = parse_hex4();
                    if (codepoint >= 0xd800 && codepoint <= 0xdbff) {
                        if (!take('\\') || !take('u')) {
                            fail("high surrogate requires low surrogate");
                        }
                        const std::uint32_t low = parse_hex4();
                        if (low < 0xdc00 || low > 0xdfff) {
                            fail("invalid low surrogate");
                        }
                        codepoint = 0x10000
                            + ((codepoint - 0xd800) << 10)
                            + (low - 0xdc00);
                    } else if (codepoint >= 0xdc00 && codepoint <= 0xdfff) {
                        fail("unpaired low surrogate");
                    }
                    append_utf8(result, codepoint);
                    break;
                }
                default:
                    fail("invalid string escape");
            }
        }
        fail("unterminated JSON string");
    }

    [[nodiscard]] auto parse_array() -> Array {
        expect('[');
        skip_space();
        Array result;
        if (take(']')) return result;
        while (true) {
            skip_space();
            result.push_back(parse_value());
            skip_space();
            if (take(']')) return result;
            expect(',');
        }
    }

    [[nodiscard]] auto parse_object() -> Object {
        expect('{');
        skip_space();
        Object result;
        if (take('}')) return result;
        while (true) {
            skip_space();
            if (position_ >= input_.size() || input_[position_] != '"') {
                fail("object key must be a string");
            }
            const std::string key = parse_string();
            skip_space();
            expect(':');
            skip_space();
            auto [iterator, inserted] =
                result.emplace(key, parse_value());
            static_cast<void>(iterator);
            if (!inserted) fail("duplicate object key");
            skip_space();
            if (take('}')) return result;
            expect(',');
        }
    }
};

[[nodiscard]] inline auto parse(std::string_view input) -> Value {
    return Parser(input).parse();
}

inline void append_escaped(std::string& output, const std::string& value) {
    output.push_back('"');
    for (const unsigned char ch : value) {
        switch (ch) {
            case '"': output += "\\\""; break;
            case '\\': output += "\\\\"; break;
            case '\b': output += "\\b"; break;
            case '\f': output += "\\f"; break;
            case '\n': output += "\\n"; break;
            case '\r': output += "\\r"; break;
            case '\t': output += "\\t"; break;
            default:
                if (ch < 0x20) {
                    char buffer[7]{};
                    std::snprintf(
                        buffer,
                        sizeof(buffer),
                        "\\u%04x",
                        static_cast<unsigned>(ch)
                    );
                    output += buffer;
                } else {
                    output.push_back(static_cast<char>(ch));
                }
        }
    }
    output.push_back('"');
}

inline void append_canonical(std::string& output, const Value& value) {
    if (value.is_null()) {
        output += "null";
    } else if (value.is_bool()) {
        output += value.boolean() ? "true" : "false";
    } else if (value.is_number()) {
        char buffer[64]{};
        const auto conversion = std::to_chars(
            buffer,
            buffer + sizeof(buffer),
            value.number(),
            std::chars_format::general,
            17
        );
        if (conversion.ec != std::errc{}) {
            throw std::runtime_error("failed to serialize JSON number");
        }
        output.append(buffer, conversion.ptr);
    } else if (value.is_string()) {
        append_escaped(output, value.string());
    } else if (value.is_array()) {
        output.push_back('[');
        bool first = true;
        for (const auto& element : value.array()) {
            if (!first) output.push_back(',');
            first = false;
            append_canonical(output, element);
        }
        output.push_back(']');
    } else {
        output.push_back('{');
        bool first = true;
        for (const auto& [key, member] : value.object()) {
            if (!first) output.push_back(',');
            first = false;
            append_escaped(output, key);
            output.push_back(':');
            append_canonical(output, member);
        }
        output.push_back('}');
    }
}

[[nodiscard]] inline auto canonical(const Value& value) -> std::string {
    std::string result;
    result.reserve(1024);
    append_canonical(result, value);
    return result;
}

} // namespace sdt_solver::json
