#pragma once

/**
 * @file dimension_engine.hpp
 * @brief Stage 3 — Unit and dimension validator
 *
 * Every equation must be checked dimensionally. Supports SI base dimensions,
 * custom theory-specific dimensions, and dimensionless ratios.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <sdt/compiler/types.hpp>
#include <sdt/compiler/expression.hpp>

#include <string>
#include <array>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <optional>

namespace sdt::compiler {

// ═══════════════════════════════════════════════════════════════════════
//  DIMENSION — SI base dimensions as exponent vector
// ═══════════════════════════════════════════════════════════════════════

struct Dimension {
    // SI base dimension exponents: [M, L, T, I, Θ, N, J]
    //   M = mass (kg), L = length (m), T = time (s), I = current (A)
    //   Θ = temperature (K), N = amount (mol), J = luminous (cd)
    std::array<int, 7> exp = {0, 0, 0, 0, 0, 0, 0};

    static constexpr int M = 0, L = 1, T = 2, I = 3, THETA = 4, N = 5, J = 6;

    // Named constructors
    static auto dimensionless() -> Dimension { return {}; }
    static auto mass()          -> Dimension { Dimension d; d.exp[M] = 1; return d; }
    static auto length()        -> Dimension { Dimension d; d.exp[L] = 1; return d; }
    static auto time()          -> Dimension { Dimension d; d.exp[T] = 1; return d; }
    static auto current()       -> Dimension { Dimension d; d.exp[I] = 1; return d; }
    static auto temperature()   -> Dimension { Dimension d; d.exp[THETA] = 1; return d; }

    // Derived dimensions
    static auto velocity()      -> Dimension { return length() / time(); }
    static auto acceleration()  -> Dimension { return velocity() / time(); }
    static auto force()         -> Dimension { return mass() * acceleration(); }
    static auto energy()        -> Dimension { return force() * length(); }
    static auto power()         -> Dimension { return energy() / time(); }
    static auto pressure()      -> Dimension { return force() / (length() * length()); }
    static auto charge()        -> Dimension { return current() * time(); }

    // Operations
    auto operator*(const Dimension& rhs) const -> Dimension {
        Dimension r;
        for (int i = 0; i < 7; ++i) r.exp[i] = exp[i] + rhs.exp[i];
        return r;
    }

    auto operator/(const Dimension& rhs) const -> Dimension {
        Dimension r;
        for (int i = 0; i < 7; ++i) r.exp[i] = exp[i] - rhs.exp[i];
        return r;
    }

    auto pow(int n) const -> Dimension {
        Dimension r;
        for (int i = 0; i < 7; ++i) r.exp[i] = exp[i] * n;
        return r;
    }

    auto sqrt() const -> std::optional<Dimension> {
        Dimension r;
        for (int i = 0; i < 7; ++i) {
            if (exp[i] % 2 != 0) return std::nullopt; // Not a perfect square
            r.exp[i] = exp[i] / 2;
        }
        return r;
    }

    auto operator==(const Dimension& rhs) const -> bool { return exp == rhs.exp; }
    auto operator!=(const Dimension& rhs) const -> bool { return exp != rhs.exp; }

    [[nodiscard]] auto is_dimensionless() const -> bool {
        for (int e : exp) if (e != 0) return false;
        return true;
    }

    [[nodiscard]] auto to_string() const -> std::string {
        if (is_dimensionless()) return "1";
        static const char* names[] = {"M", "L", "T", "I", "Θ", "N", "J"};
        std::string s;
        for (int i = 0; i < 7; ++i) {
            if (exp[i] != 0) {
                if (!s.empty()) s += " ";
                s += names[i];
                if (exp[i] != 1) s += "^" + std::to_string(exp[i]);
            }
        }
        return s;
    }

    // Parse from string like "M L^-1 T^-2"
    static auto parse(const std::string& s) -> Dimension {
        Dimension d;
        if (s.empty() || s == "1" || s == "-" || s == "dimensionless") return d;

        static const std::unordered_map<std::string, int> name_to_idx = {
            {"M", M}, {"kg", M}, {"mass", M},
            {"L", L}, {"m", L}, {"length", L},
            {"T", T}, {"s", T}, {"time", T},
            {"I", I}, {"A", I}, {"current", I},
            {"Θ", THETA}, {"K", THETA}, {"temp", THETA}, {"temperature", THETA},
            {"N", N}, {"mol", N},
            {"J", J}, {"cd", J},
        };

        std::istringstream iss(s);
        std::string token;
        while (iss >> token) {
            // Check for "X^n" pattern
            int power = 1;
            auto caret = token.find('^');
            std::string base = token;
            if (caret != std::string::npos) {
                base = token.substr(0, caret);
                try { power = std::stoi(token.substr(caret + 1)); } catch (...) {}
            }

            auto it = name_to_idx.find(base);
            if (it != name_to_idx.end()) {
                d.exp[it->second] += power;
            }
        }
        return d;
    }
};

// ═══════════════════════════════════════════════════════════════════════
//  DIMENSION ENGINE
// ═══════════════════════════════════════════════════════════════════════

class DimensionEngine {
public:
    // ─── Symbol Dimension Registration ───

    void register_dimension(const std::string& symbol, Dimension dim) {
        dim_table_[symbol] = dim;
    }

    // Register standard SDT symbols — comprehensive
    void register_sdt_defaults() {
        // ── Fundamental constants ──
        register_dimension("c",       Dimension::velocity());
        register_dimension("hbar",    Dimension::energy() * Dimension::time());
        register_dimension("h",       Dimension::energy() * Dimension::time());
        register_dimension("k_B",     Dimension::energy() / Dimension::temperature());
        register_dimension("e",       Dimension::charge());
        register_dimension("k_e",     Dimension::force() * Dimension::length().pow(2) / Dimension::charge().pow(2));
        register_dimension("alpha",   Dimension::dimensionless());
        register_dimension("pi",      Dimension::dimensionless());

        // ── Planck units ──
        register_dimension("l_P",     Dimension::length());
        register_dimension("t_P",     Dimension::time());

        // ── Masses ──
        register_dimension("m",       Dimension::mass());
        register_dimension("m_e",     Dimension::mass());
        register_dimension("m_p",     Dimension::mass());
        register_dimension("m_n",     Dimension::mass());
        register_dimension("m_inert", Dimension::mass());
        register_dimension("m_grav",  Dimension::mass());

        // ── Lengths / radii ──
        register_dimension("R",       Dimension::length());
        register_dimension("r",       Dimension::length());
        register_dimension("R_p",     Dimension::length());
        register_dimension("r_e",     Dimension::length());
        register_dimension("a_0",     Dimension::length());
        register_dimension("R_CMB",   Dimension::length());
        register_dimension("R_1",     Dimension::length());
        register_dimension("R_2",     Dimension::length());
        register_dimension("R_charge",Dimension::length());
        register_dimension("beth",    Dimension::length());
        register_dimension("L",       Dimension::length());
        register_dimension("L_0",     Dimension::length());
        register_dimension("a",       Dimension::length());  // torus minor radius

        // ── Temperatures ──
        register_dimension("T_CMB",   Dimension::temperature());
        register_dimension("T",       Dimension::temperature());

        // ── Velocities ──
        register_dimension("v",       Dimension::velocity());
        register_dimension("v_T",     Dimension::velocity());
        register_dimension("v_P",     Dimension::velocity());
        register_dimension("v_C",     Dimension::velocity());
        register_dimension("v_t",     Dimension::velocity());
        register_dimension("v_circ",  Dimension::velocity());
        register_dimension("v_orbital", Dimension::velocity());

        // ── Energy / power ──
        register_dimension("E",       Dimension::energy());
        register_dimension("E_0",     Dimension::energy());
        register_dimension("epsilon", Dimension::energy());
        register_dimension("Phi",     Dimension::energy());
        register_dimension("epsilon_d", Dimension::energy());
        register_dimension("epsilon_t", Dimension::energy());
        register_dimension("epsilon_a", Dimension::energy());
        register_dimension("u_CMB",   Dimension::energy() / Dimension::length().pow(3));

        // ── Pressure ──
        register_dimension("P_conv",  Dimension::pressure());
        register_dimension("P_eff",   Dimension::pressure());
        register_dimension("P_cf",    Dimension::pressure());
        register_dimension("sigma_n", Dimension::pressure());

        // ── Force ──
        register_dimension("F",       Dimension::force());

        // ── Volume ──
        register_dimension("V_disp",  Dimension::length().pow(3));
        register_dimension("V_disp_e", Dimension::length().pow(3));
        register_dimension("V_disp_p", Dimension::length().pow(3));

        // ── Momentum ──
        register_dimension("p",       Dimension::mass() * Dimension::velocity());

        // ── Dimensionless quantities ──
        register_dimension("N",       Dimension::dimensionless());
        register_dimension("k",       Dimension::dimensionless());
        register_dimension("z",       Dimension::dimensionless());
        register_dimension("W",       Dimension::dimensionless());
        register_dimension("W_eff",   Dimension::dimensionless());
        register_dimension("tau",     Dimension::dimensionless());
        register_dimension("f",       Dimension::dimensionless());
        register_dimension("gamma",   Dimension::dimensionless());
        register_dimension("d",       Dimension::dimensionless());  // dimensionality = 3
        register_dimension("i",       Dimension::dimensionless());  // shell index
        register_dimension("n",       Dimension::dimensionless());
        register_dimension("l",       Dimension::dimensionless());  // multipole ℓ

        // ── Time ──
        register_dimension("t",       Dimension::time());
        register_dimension("dt",      Dimension::time());
        register_dimension("dtau",    Dimension::time());

        // ── Tensor / derived ──
        // Pi_ij is a stress tensor → pressure dimensions
        register_dimension("Pi_ij",   Dimension::pressure());
        register_dimension("delta_ij", Dimension::dimensionless());

        // ── Coupling ──
        register_dimension("C_TP",    Dimension::dimensionless());

        // ── State28D Manifold — all 28 aspects ──
        // Registers every field from the canonical 28D state vector
        // so that equations referencing xi_0, T_1, Phi_3, eps_b etc.
        // are automatically dimensionally validated.
        for (auto& aspect : state28d_aspects()) {
            auto dim = Dimension::parse(aspect.dimension_str);
            register_dimension(aspect.symbol, dim);
        }
    }

    // ── Dimension Propagation ──
    // Iteratively infer dimensions from equations: if A = B*C and two are known, infer the third
    auto propagate_from_equations(const std::vector<EquationRecord>& records) -> int {
        int inferred = 0;
        bool changed = true;
        int max_iterations = 10;

        while (changed && max_iterations-- > 0) {
            changed = false;
            for (auto& rec : records) {
                if (rec.equation.empty()) continue;
                auto [lhs_expr, rhs_expr] = parse_equation(rec.equation);
                if (!lhs_expr || !rhs_expr) continue;

                auto lhs_dim = infer_dimension(lhs_expr);
                auto rhs_dim = infer_dimension(rhs_expr);

                if (lhs_dim && !rhs_dim) {
                    // Try to register unknown symbols on RHS
                    if (try_propagate(rhs_expr, *lhs_dim)) {
                        changed = true;
                        ++inferred;
                    }
                } else if (!lhs_dim && rhs_dim) {
                    if (try_propagate(lhs_expr, *rhs_dim)) {
                        changed = true;
                        ++inferred;
                    }
                }
            }
        }
        return inferred;
    }

private:
    std::unordered_map<std::string, Dimension> dim_table_;

    // Try to assign dimension to a single unknown symbol in an expression
    auto try_propagate(const ExprPtr& expr, const Dimension& target) -> bool {
        if (!expr) return false;

        // If this is a single unknown symbol, assign it the target dimension
        if (expr->kind == ExprKind::SYMBOL) {
            if (dim_table_.find(expr->sym_name) == dim_table_.end()) {
                dim_table_[expr->sym_name] = target;
                return true;
            }
            return false;
        }

        // For A * B where one side is known, infer the other
        if (expr->kind == ExprKind::MUL) {
            auto ld = infer_dimension(expr->lhs());
            auto rd = infer_dimension(expr->rhs());
            if (ld && !rd) return try_propagate(expr->rhs(), target / *ld);
            if (!ld && rd) return try_propagate(expr->lhs(), target / *rd);
        }

        // For A / B where one side is known
        if (expr->kind == ExprKind::DIV) {
            auto ld = infer_dimension(expr->lhs());
            auto rd = infer_dimension(expr->rhs());
            if (ld && !rd) return try_propagate(expr->rhs(), *ld / target);
            if (!ld && rd) return try_propagate(expr->lhs(), target * *rd);
        }

        // For A + B or A - B, both must have the same dimension
        if (expr->kind == ExprKind::ADD || expr->kind == ExprKind::SUB) {
            auto ld = infer_dimension(expr->lhs());
            auto rd = infer_dimension(expr->rhs());
            bool did = false;
            if (!ld) did |= try_propagate(expr->lhs(), target);
            if (!rd) did |= try_propagate(expr->rhs(), target);
            return did;
        }

        return false;
    }

public:
    // ─── Expression Dimension Inference ───

    [[nodiscard]] auto infer_dimension(const ExprPtr& expr) const -> std::optional<Dimension> {
        if (!expr) return std::nullopt;

        switch (expr->kind) {
            case ExprKind::NUMBER:
                return Dimension::dimensionless();

            case ExprKind::SYMBOL: {
                auto it = dim_table_.find(expr->sym_name);
                if (it != dim_table_.end()) return it->second;
                return std::nullopt; // Unknown dimension
            }

            case ExprKind::ADD:
            case ExprKind::SUB: {
                auto ld = infer_dimension(expr->lhs());
                auto rd = infer_dimension(expr->rhs());
                if (!ld || !rd) return std::nullopt;
                if (*ld != *rd) return std::nullopt; // Dimension mismatch
                return ld;
            }

            case ExprKind::MUL: {
                auto ld = infer_dimension(expr->lhs());
                auto rd = infer_dimension(expr->rhs());
                if (!ld || !rd) return std::nullopt;
                return *ld * *rd;
            }

            case ExprKind::DIV: {
                auto ld = infer_dimension(expr->lhs());
                auto rd = infer_dimension(expr->rhs());
                if (!ld || !rd) return std::nullopt;
                return *ld / *rd;
            }

            case ExprKind::POW: {
                auto bd = infer_dimension(expr->lhs());
                if (!bd) return std::nullopt;
                // Exponent must be dimensionless number
                if (expr->rhs()->is_number()) {
                    int n = static_cast<int>(expr->rhs()->num_val);
                    return bd->pow(n);
                }
                auto ed = infer_dimension(expr->rhs());
                if (ed && ed->is_dimensionless() && bd->is_dimensionless()) {
                    return Dimension::dimensionless();
                }
                return std::nullopt;
            }

            case ExprKind::SQRT: {
                auto d = infer_dimension(expr->children[0]);
                if (!d) return std::nullopt;
                return d->sqrt();
            }

            case ExprKind::NEGATE: {
                return infer_dimension(expr->children[0]);
            }

            case ExprKind::LOG:
            case ExprKind::EXP: {
                // Argument must be dimensionless
                auto d = infer_dimension(expr->children[0]);
                if (d && d->is_dimensionless()) return Dimension::dimensionless();
                return std::nullopt;
            }
        }
        return std::nullopt;
    }

    // ─── Equation Validation ───

    [[nodiscard]] auto validate_equation(const std::string& eq_str) const -> EquationRecord {
        EquationRecord record;
        record.equation = eq_str;

        auto [lhs, rhs] = parse_equation(eq_str);
        if (!lhs || !rhs) {
            record.status = EqStatus::UNRESOLVED;
            record.failure_reason = "Could not parse equation";
            return record;
        }

        record.lhs_expression = lhs->to_string();
        record.rhs_expression = rhs->to_string();

        auto lhs_dim = infer_dimension(lhs);
        auto rhs_dim = infer_dimension(rhs);

        if (lhs_dim) record.lhs_dimension = lhs_dim->to_string();
        else record.lhs_dimension = "unresolved";

        if (rhs_dim) record.rhs_dimension = rhs_dim->to_string();
        else record.rhs_dimension = "unresolved";

        if (!lhs_dim || !rhs_dim) {
            record.status = EqStatus::UNRESOLVED;
            record.failure_reason = "One or both sides have unresolved dimensions";
        } else if (*lhs_dim == *rhs_dim) {
            record.status = EqStatus::PASS;
        } else {
            record.status = EqStatus::FAIL;
            record.failure_reason = "LHS dimension [" + lhs_dim->to_string() +
                                    "] != RHS dimension [" + rhs_dim->to_string() + "]";
        }

        return record;
    }

    // Validate all equations from a parsed theory
    [[nodiscard]] auto validate_all(const ParsedTheory& parsed) const -> std::vector<EquationRecord> {
        std::vector<EquationRecord> results;
        for (auto& item : parsed.equations) {
            auto record = validate_equation(item.normalised);
            record.location = item.location;
            results.push_back(record);
        }
        return results;
    }


};

} // namespace sdt::compiler
