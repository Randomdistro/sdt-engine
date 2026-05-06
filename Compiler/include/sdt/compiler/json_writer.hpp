#pragma once

/**
 * @file json_writer.hpp
 * @brief Minimal hand-rolled JSON serialiser — zero dependencies
 *
 * Stream-based JSON output with pretty-printing.
 * No nlohmann, no rapidjson. Pure C++20.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdio>

namespace sdt::compiler {

class JsonWriter {
public:
    explicit JsonWriter(int indent_size = 2)
        : indent_size_(indent_size) {}

    // ─── Object ───

    auto begin_object() -> JsonWriter& {
        write_separator();
        out_ << '{';
        push_context(Context::OBJECT);
        return *this;
    }

    auto end_object() -> JsonWriter& {
        pop_context();
        newline();
        out_ << '}';
        return *this;
    }

    auto key(const std::string& k) -> JsonWriter& {
        write_separator();
        newline();
        write_string(k);
        out_ << ": ";
        expect_value_ = true;
        return *this;
    }

    // ─── Array ───

    auto begin_array() -> JsonWriter& {
        write_separator();
        out_ << '[';
        push_context(Context::ARRAY);
        return *this;
    }

    auto end_array() -> JsonWriter& {
        pop_context();
        newline();
        out_ << ']';
        return *this;
    }

    // ─── Values ───

    auto value(const std::string& v) -> JsonWriter& {
        write_separator();
        if (!expect_value_) newline();
        write_string(v);
        expect_value_ = false;
        return *this;
    }

    auto value(const char* v) -> JsonWriter& {
        return value(std::string(v));
    }

    auto value(double v) -> JsonWriter& {
        write_separator();
        if (!expect_value_) newline();
        if (std::isnan(v) || std::isinf(v)) {
            out_ << "null";
        } else {
            char buf[64];
            std::snprintf(buf, sizeof(buf), "%.15g", v);
            out_ << buf;
        }
        expect_value_ = false;
        return *this;
    }

    auto value(int v) -> JsonWriter& {
        write_separator();
        if (!expect_value_) newline();
        out_ << v;
        expect_value_ = false;
        return *this;
    }

    auto value(int64_t v) -> JsonWriter& {
        write_separator();
        if (!expect_value_) newline();
        out_ << v;
        expect_value_ = false;
        return *this;
    }

    auto value(uint64_t v) -> JsonWriter& {
        write_separator();
        if (!expect_value_) newline();
        out_ << v;
        expect_value_ = false;
        return *this;
    }

    auto value(bool v) -> JsonWriter& {
        write_separator();
        if (!expect_value_) newline();
        out_ << (v ? "true" : "false");
        expect_value_ = false;
        return *this;
    }

    auto null_value() -> JsonWriter& {
        write_separator();
        if (!expect_value_) newline();
        out_ << "null";
        expect_value_ = false;
        return *this;
    }

    // ─── String array shortcut ───

    auto string_array(const std::vector<std::string>& arr) -> JsonWriter& {
        begin_array();
        for (auto& s : arr) value(s);
        end_array();
        return *this;
    }

    // ─── Output ───

    [[nodiscard]] auto str() const -> std::string {
        return out_.str();
    }

    void reset() {
        out_.str("");
        out_.clear();
        stack_.clear();
        expect_value_ = false;
    }

private:
    enum class Context { OBJECT, ARRAY };

    struct StackEntry {
        Context ctx;
        int     count = 0;
    };

    std::ostringstream     out_;
    std::vector<StackEntry> stack_;
    int                    indent_size_ = 2;
    bool                   expect_value_ = false;

    void push_context(Context c) {
        stack_.push_back({c, 0});
    }

    void pop_context() {
        if (!stack_.empty()) stack_.pop_back();
    }

    [[nodiscard]] auto depth() const -> int {
        return static_cast<int>(stack_.size());
    }

    void newline() {
        out_ << '\n';
        for (int i = 0; i < depth() * indent_size_; ++i) out_ << ' ';
    }

    void write_separator() {
        if (expect_value_) {
            expect_value_ = false;
            return;
        }
        if (!stack_.empty()) {
            auto& top = stack_.back();
            if (top.count > 0) {
                out_ << ',';
            }
            ++top.count;
        }
    }

    void write_string(const std::string& s) {
        out_ << '"';
        for (char ch : s) {
            switch (ch) {
                case '"':  out_ << "\\\""; break;
                case '\\': out_ << "\\\\"; break;
                case '\b': out_ << "\\b";  break;
                case '\f': out_ << "\\f";  break;
                case '\n': out_ << "\\n";  break;
                case '\r': out_ << "\\r";  break;
                case '\t': out_ << "\\t";  break;
                default:
                    if (static_cast<unsigned char>(ch) < 0x20) {
                        char esc[8];
                        std::snprintf(esc, sizeof(esc), "\\u%04x", static_cast<unsigned>(ch));
                        out_ << esc;
                    } else {
                        out_ << ch;
                    }
                    break;
            }
        }
        out_ << '"';
    }
};

} // namespace sdt::compiler
