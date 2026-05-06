#pragma once

/**
 * @file expression.hpp
 * @brief Lightweight symbolic expression tree for equation representation
 *
 * Supports parsing simple equations, substitution, algebraic simplification,
 * and dimensional propagation. This is NOT a full CAS — it handles the
 * substitution/rearrangement/ratio operations the compiler requires.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include <optional>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace sdt::compiler {

// ═══════════════════════════════════════════════════════════════════════
//  EXPRESSION NODE TYPES
// ═══════════════════════════════════════════════════════════════════════

enum class ExprKind : uint8_t {
    NUMBER,
    SYMBOL,
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    SQRT,
    LOG,
    EXP,
    NEGATE,
};

// ═══════════════════════════════════════════════════════════════════════
//  EXPRESSION NODE
// ═══════════════════════════════════════════════════════════════════════

struct ExprNode;
using ExprPtr = std::shared_ptr<ExprNode>;

struct ExprNode {
    ExprKind kind;
    double   num_val = 0.0;        // For NUMBER
    std::string sym_name;          // For SYMBOL
    std::vector<ExprPtr> children; // Operands

    // ─── Factory functions ───

    static auto number(double v) -> ExprPtr {
        auto n = std::make_shared<ExprNode>();
        n->kind = ExprKind::NUMBER;
        n->num_val = v;
        return n;
    }

    static auto symbol(const std::string& name) -> ExprPtr {
        auto n = std::make_shared<ExprNode>();
        n->kind = ExprKind::SYMBOL;
        n->sym_name = name;
        return n;
    }

    static auto binary(ExprKind op, ExprPtr lhs, ExprPtr rhs) -> ExprPtr {
        auto n = std::make_shared<ExprNode>();
        n->kind = op;
        n->children.push_back(std::move(lhs));
        n->children.push_back(std::move(rhs));
        return n;
    }

    static auto unary(ExprKind op, ExprPtr operand) -> ExprPtr {
        auto n = std::make_shared<ExprNode>();
        n->kind = op;
        n->children.push_back(std::move(operand));
        return n;
    }

    // ─── Convenience operators ───

    static auto add(ExprPtr a, ExprPtr b) -> ExprPtr { return binary(ExprKind::ADD, std::move(a), std::move(b)); }
    static auto sub(ExprPtr a, ExprPtr b) -> ExprPtr { return binary(ExprKind::SUB, std::move(a), std::move(b)); }
    static auto mul(ExprPtr a, ExprPtr b) -> ExprPtr { return binary(ExprKind::MUL, std::move(a), std::move(b)); }
    static auto div(ExprPtr a, ExprPtr b) -> ExprPtr { return binary(ExprKind::DIV, std::move(a), std::move(b)); }
    static auto pow(ExprPtr base, ExprPtr exp) -> ExprPtr { return binary(ExprKind::POW, std::move(base), std::move(exp)); }
    static auto sqrt(ExprPtr v) -> ExprPtr { return unary(ExprKind::SQRT, std::move(v)); }
    static auto neg(ExprPtr v) -> ExprPtr { return unary(ExprKind::NEGATE, std::move(v)); }

    // ─── Queries ───

    [[nodiscard]] auto is_number() const noexcept -> bool { return kind == ExprKind::NUMBER; }
    [[nodiscard]] auto is_symbol() const noexcept -> bool { return kind == ExprKind::SYMBOL; }
    [[nodiscard]] auto is_zero() const noexcept -> bool { return kind == ExprKind::NUMBER && num_val == 0.0; }
    [[nodiscard]] auto is_one() const noexcept -> bool { return kind == ExprKind::NUMBER && num_val == 1.0; }

    [[nodiscard]] auto lhs() const -> const ExprPtr& { return children.at(0); }
    [[nodiscard]] auto rhs() const -> const ExprPtr& { return children.at(1); }

    // ─── Deep clone ───

    [[nodiscard]] auto clone() const -> ExprPtr {
        auto n = std::make_shared<ExprNode>();
        n->kind = kind;
        n->num_val = num_val;
        n->sym_name = sym_name;
        for (auto& child : children) {
            n->children.push_back(child->clone());
        }
        return n;
    }

    // ─── Collect all symbol names ───

    void collect_symbols(std::vector<std::string>& out) const {
        if (kind == ExprKind::SYMBOL) {
            if (std::find(out.begin(), out.end(), sym_name) == out.end()) {
                out.push_back(sym_name);
            }
        }
        for (auto& child : children) {
            child->collect_symbols(out);
        }
    }

    [[nodiscard]] auto symbols() const -> std::vector<std::string> {
        std::vector<std::string> result;
        collect_symbols(result);
        return result;
    }

    // ─── Substitution: replace symbol with expression ───

    [[nodiscard]] auto substitute(const std::string& sym, const ExprPtr& replacement) const -> ExprPtr {
        if (kind == ExprKind::SYMBOL && sym_name == sym) {
            return replacement->clone();
        }
        auto result = std::make_shared<ExprNode>();
        result->kind = kind;
        result->num_val = num_val;
        result->sym_name = sym_name;
        for (auto& child : children) {
            result->children.push_back(child->substitute(sym, replacement));
        }
        return result;
    }

    // ─── Structural equality ───

    [[nodiscard]] auto equals(const ExprPtr& other) const -> bool {
        if (!other) return false;
        if (kind != other->kind) return false;
        if (kind == ExprKind::NUMBER) return num_val == other->num_val;
        if (kind == ExprKind::SYMBOL) return sym_name == other->sym_name;
        if (children.size() != other->children.size()) return false;
        for (size_t i = 0; i < children.size(); ++i) {
            if (!children[i]->equals(other->children[i])) return false;
        }
        return true;
    }

    // ─── Numerical evaluation (all symbols must be resolved) ───

    [[nodiscard]] auto evaluate(const std::unordered_map<std::string, double>& env = {}) const -> std::optional<double> {
        switch (kind) {
            case ExprKind::NUMBER: return num_val;
            case ExprKind::SYMBOL: {
                auto it = env.find(sym_name);
                if (it != env.end()) return it->second;
                return std::nullopt;
            }
            case ExprKind::ADD: {
                auto l = children[0]->evaluate(env);
                auto r = children[1]->evaluate(env);
                if (l && r) return *l + *r;
                return std::nullopt;
            }
            case ExprKind::SUB: {
                auto l = children[0]->evaluate(env);
                auto r = children[1]->evaluate(env);
                if (l && r) return *l - *r;
                return std::nullopt;
            }
            case ExprKind::MUL: {
                auto l = children[0]->evaluate(env);
                auto r = children[1]->evaluate(env);
                if (l && r) return *l * *r;
                return std::nullopt;
            }
            case ExprKind::DIV: {
                auto l = children[0]->evaluate(env);
                auto r = children[1]->evaluate(env);
                if (l && r && *r != 0.0) return *l / *r;
                return std::nullopt;
            }
            case ExprKind::POW: {
                auto b = children[0]->evaluate(env);
                auto e = children[1]->evaluate(env);
                if (b && e) return std::pow(*b, *e);
                return std::nullopt;
            }
            case ExprKind::SQRT: {
                auto v = children[0]->evaluate(env);
                if (v && *v >= 0.0) return std::sqrt(*v);
                return std::nullopt;
            }
            case ExprKind::LOG: {
                auto v = children[0]->evaluate(env);
                if (v && *v > 0.0) return std::log(*v);
                return std::nullopt;
            }
            case ExprKind::EXP: {
                auto v = children[0]->evaluate(env);
                if (v) return std::exp(*v);
                return std::nullopt;
            }
            case ExprKind::NEGATE: {
                auto v = children[0]->evaluate(env);
                if (v) return -(*v);
                return std::nullopt;
            }
        }
        return std::nullopt;
    }

    // ─── Pretty print ───

    [[nodiscard]] auto to_string() const -> std::string {
        switch (kind) {
            case ExprKind::NUMBER: {
                char buf[64];
                if (num_val == static_cast<int64_t>(num_val) && std::abs(num_val) < 1e15) {
                    std::snprintf(buf, sizeof(buf), "%lld", static_cast<long long>(num_val));
                } else {
                    std::snprintf(buf, sizeof(buf), "%.15g", num_val);
                }
                return buf;
            }
            case ExprKind::SYMBOL: return sym_name;
            case ExprKind::ADD:    return "(" + children[0]->to_string() + " + " + children[1]->to_string() + ")";
            case ExprKind::SUB:    return "(" + children[0]->to_string() + " - " + children[1]->to_string() + ")";
            case ExprKind::MUL:    return "(" + children[0]->to_string() + " * " + children[1]->to_string() + ")";
            case ExprKind::DIV:    return "(" + children[0]->to_string() + " / " + children[1]->to_string() + ")";
            case ExprKind::POW:    return "(" + children[0]->to_string() + "^" + children[1]->to_string() + ")";
            case ExprKind::SQRT:   return "sqrt(" + children[0]->to_string() + ")";
            case ExprKind::LOG:    return "log(" + children[0]->to_string() + ")";
            case ExprKind::EXP:    return "exp(" + children[0]->to_string() + ")";
            case ExprKind::NEGATE: return "(-" + children[0]->to_string() + ")";
        }
        return "?";
    }
};

// ═══════════════════════════════════════════════════════════════════════
//  SIMPLIFIER
// ═══════════════════════════════════════════════════════════════════════

inline auto simplify(ExprPtr expr) -> ExprPtr {
    if (!expr) return expr;

    // Recursively simplify children first
    for (auto& child : expr->children) {
        child = simplify(child);
    }

    // Constant folding
    if (expr->children.size() == 2 &&
        expr->children[0]->is_number() &&
        expr->children[1]->is_number()) {
        double a = expr->children[0]->num_val;
        double b = expr->children[1]->num_val;
        switch (expr->kind) {
            case ExprKind::ADD: return ExprNode::number(a + b);
            case ExprKind::SUB: return ExprNode::number(a - b);
            case ExprKind::MUL: return ExprNode::number(a * b);
            case ExprKind::DIV: if (b != 0.0) return ExprNode::number(a / b); break;
            case ExprKind::POW: return ExprNode::number(std::pow(a, b)); break;
            default: break;
        }
    }

    if (expr->children.size() == 1 && expr->children[0]->is_number()) {
        double v = expr->children[0]->num_val;
        switch (expr->kind) {
            case ExprKind::NEGATE: return ExprNode::number(-v);
            case ExprKind::SQRT:   if (v >= 0) return ExprNode::number(std::sqrt(v)); break;
            case ExprKind::LOG:    if (v > 0) return ExprNode::number(std::log(v)); break;
            case ExprKind::EXP:    return ExprNode::number(std::exp(v));
            default: break;
        }
    }

    // Identity rules
    switch (expr->kind) {
        case ExprKind::ADD:
            // x + 0 = x, 0 + x = x
            if (expr->children[1]->is_zero()) return expr->children[0];
            if (expr->children[0]->is_zero()) return expr->children[1];
            break;

        case ExprKind::SUB:
            // x - 0 = x
            if (expr->children[1]->is_zero()) return expr->children[0];
            // x - x = 0
            if (expr->children[0]->equals(expr->children[1])) return ExprNode::number(0);
            break;

        case ExprKind::MUL:
            // x * 1 = x, 1 * x = x
            if (expr->children[1]->is_one()) return expr->children[0];
            if (expr->children[0]->is_one()) return expr->children[1];
            // x * 0 = 0, 0 * x = 0
            if (expr->children[1]->is_zero()) return ExprNode::number(0);
            if (expr->children[0]->is_zero()) return ExprNode::number(0);
            break;

        case ExprKind::DIV:
            // x / 1 = x
            if (expr->children[1]->is_one()) return expr->children[0];
            // x / x = 1 (when x is a single symbol)
            if (expr->children[0]->equals(expr->children[1]) &&
                !expr->children[0]->is_zero()) {
                return ExprNode::number(1);
            }
            break;

        case ExprKind::POW:
            // x^0 = 1
            if (expr->children[1]->is_zero()) return ExprNode::number(1);
            // x^1 = x
            if (expr->children[1]->is_one()) return expr->children[0];
            break;

        case ExprKind::NEGATE:
            // -(-x) = x
            if (expr->children[0]->kind == ExprKind::NEGATE) return expr->children[0]->children[0];
            break;

        default:
            break;
    }

    return expr;
}

// ═══════════════════════════════════════════════════════════════════════
//  EXPRESSION PARSER
//
//  Grammar:
//    expr     → additive
//    additive → multiplicative (('+' | '-') multiplicative)*
//    mult     → power (('*' | '/') power)*
//    power    → unary ('^' unary)?
//    unary    → '-' unary | atom
//    atom     → NUMBER | SYMBOL | FUNCTION '(' expr ')' | '(' expr ')'
// ═══════════════════════════════════════════════════════════════════════

class ExprParser {
public:
    explicit ExprParser(const std::string& input) : src_(input), pos_(0) {}

    [[nodiscard]] auto parse() -> ExprPtr {
        skip_ws();
        auto result = parse_additive();
        skip_ws();
        return result;
    }

    // Parse "LHS = RHS" and return pair
    [[nodiscard]] auto parse_equation() -> std::pair<ExprPtr, ExprPtr> {
        skip_ws();
        auto lhs = parse_additive();
        skip_ws();
        if (pos_ < src_.size() && src_[pos_] == '=') {
            ++pos_;
            skip_ws();
            auto rhs = parse_additive();
            return {lhs, rhs};
        }
        return {lhs, nullptr};
    }

    [[nodiscard]] auto remaining() const -> std::string {
        if (pos_ < src_.size()) return src_.substr(pos_);
        return "";
    }

private:
    std::string src_;
    size_t      pos_;

    [[nodiscard]] auto peek() const -> char {
        if (pos_ >= src_.size()) return '\0';
        return src_[pos_];
    }

    auto advance() -> char {
        if (pos_ >= src_.size()) return '\0';
        return src_[pos_++];
    }

    void skip_ws() {
        while (pos_ < src_.size() && (src_[pos_] == ' ' || src_[pos_] == '\t')) {
            ++pos_;
        }
    }

    auto parse_additive() -> ExprPtr {
        auto left = parse_multiplicative();
        skip_ws();
        while (pos_ < src_.size() && (src_[pos_] == '+' || src_[pos_] == '-')) {
            char op = advance();
            skip_ws();
            auto right = parse_multiplicative();
            if (op == '+') left = ExprNode::add(left, right);
            else           left = ExprNode::sub(left, right);
            skip_ws();
        }
        return left;
    }

    auto parse_multiplicative() -> ExprPtr {
        auto left = parse_power();
        skip_ws();
        while (pos_ < src_.size() && (src_[pos_] == '*' || src_[pos_] == '/')) {
            char op = advance();
            skip_ws();
            auto right = parse_power();
            if (op == '*') left = ExprNode::mul(left, right);
            else           left = ExprNode::div(left, right);
            skip_ws();
        }
        return left;
    }

    auto parse_power() -> ExprPtr {
        auto base = parse_unary();
        skip_ws();
        if (pos_ < src_.size() && (src_[pos_] == '^')) {
            ++pos_;
            skip_ws();
            auto exp = parse_unary();
            return ExprNode::pow(base, exp);
        }
        return base;
    }

    auto parse_unary() -> ExprPtr {
        skip_ws();
        if (pos_ < src_.size() && src_[pos_] == '-') {
            ++pos_;
            skip_ws();
            auto operand = parse_unary();
            return ExprNode::neg(operand);
        }
        return parse_atom();
    }

    auto parse_atom() -> ExprPtr {
        skip_ws();
        if (pos_ >= src_.size()) {
            return ExprNode::number(0); // Empty expression fallback
        }

        char ch = src_[pos_];

        // Parenthesised expression
        if (ch == '(') {
            ++pos_;
            skip_ws();
            auto inner = parse_additive();
            skip_ws();
            if (pos_ < src_.size() && src_[pos_] == ')') ++pos_;
            return inner;
        }

        // Number (including scientific notation)
        if (std::isdigit(ch) || ch == '.') {
            return parse_number();
        }

        // Symbol or function
        if (std::isalpha(ch) || ch == '_' || static_cast<unsigned char>(ch) > 127) {
            return parse_symbol_or_function();
        }

        // Unknown character — treat as end of expression
        return ExprNode::number(0);
    }

    auto parse_number() -> ExprPtr {
        size_t start = pos_;
        while (pos_ < src_.size() && (std::isdigit(src_[pos_]) || src_[pos_] == '.')) {
            ++pos_;
        }
        // Scientific notation
        if (pos_ < src_.size() && (src_[pos_] == 'e' || src_[pos_] == 'E')) {
            ++pos_;
            if (pos_ < src_.size() && (src_[pos_] == '+' || src_[pos_] == '-')) ++pos_;
            while (pos_ < src_.size() && std::isdigit(src_[pos_])) ++pos_;
        }
        std::string numstr = src_.substr(start, pos_ - start);
        double val = 0.0;
        try { val = std::stod(numstr); } catch (...) {}
        return ExprNode::number(val);
    }

    auto parse_symbol_or_function() -> ExprPtr {
        size_t start = pos_;
        // Allow Unicode-ish symbols, alphanumeric, underscore, prime (')
        while (pos_ < src_.size()) {
            char c = src_[pos_];
            if (std::isalnum(c) || c == '_' || c == '\'' ||
                static_cast<unsigned char>(c) > 127) {
                ++pos_;
            } else {
                break;
            }
        }
        std::string name = src_.substr(start, pos_ - start);
        skip_ws();

        // Check for function call: name(...)
        if (pos_ < src_.size() && src_[pos_] == '(') {
            ++pos_;
            skip_ws();
            auto arg = parse_additive();
            skip_ws();
            if (pos_ < src_.size() && src_[pos_] == ')') ++pos_;

            if (name == "sqrt") return ExprNode::sqrt(arg);
            if (name == "log" || name == "ln") return ExprNode::unary(ExprKind::LOG, arg);
            if (name == "exp") return ExprNode::unary(ExprKind::EXP, arg);

            // Unknown function — treat as symbol * (arg) for now
            return ExprNode::mul(ExprNode::symbol(name), arg);
        }

        return ExprNode::symbol(name);
    }
};

// Convenience function
inline auto parse_expr(const std::string& input) -> ExprPtr {
    ExprParser parser(input);
    return parser.parse();
}

inline auto parse_equation(const std::string& input) -> std::pair<ExprPtr, ExprPtr> {
    ExprParser parser(input);
    return parser.parse_equation();
}

} // namespace sdt::compiler
