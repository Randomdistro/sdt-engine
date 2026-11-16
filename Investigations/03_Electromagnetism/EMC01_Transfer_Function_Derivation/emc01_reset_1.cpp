// EMC01 blank-slate run 1 (2026-10-07): P_eff routes, delete-test, dependence exponents, transfer function f.
// Pre-registered in EMC01_RESET_ASSESSMENT_2026-10-07.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <functional>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi;

static double dln(const std::function<double(double)>& f, double x0) { double h = 1e-5; return (std::log(f(x0 * (1 + h))) - std::log(f(x0 * (1 - h)))) / (std::log(1 + h) - std::log(1 - h)); }
// basis form of P_eff with R_p = W1 hbar/(m_p c), r_e = alpha hbar/(m_e c)
static double Pbasis(double al, double hb, double c, double mp, double me, double W1) { double Rp = W1 * hb / (mp * c), re = al * hb / (me * c); return 4 * al * hb * c / (PI * Rp * Rp * re * re); }

int main() {
    std::printf("EMC01 blank-slate run 1 (pre-registered 2026-10-07)\n====================================================\n\n");
    int fails = 0;
    const double c = M::c, hb = M::hbar, al = M::alpha, mp = M::m_p, me = M::m_e, a0 = M::a_0, Rp = M::R_p, re = M::r_e;
    const double Rl = law_III::R_p_lock, Pe = law_III::P_eff, W1 = double(lock_geometry::trefoil_lock_coordination);
    // ---- V1
    double Fh = al * hb * c / (a0 * a0), hbc = hb * c / M::MeV_to_J * 1e15;
    bool v1 = std::fabs(Fh / 8.2387e-8 - 1) < 1e-4 && std::fabs(hbc - 197.327) < 197.327 * 1e-5 && std::fabs(law_I::P_conv / 2.459e48 - 1) < 5e-3 && std::fabs(law_III::f_transfer / 2.123e-17 - 1) < 5e-3;
    std::printf("[V1] alpha hbar c / a_0^2 = %.5e N (8.2387e-8) ; hbar c = %.4f MeV fm ; P_conv = %.5e Pa (prompt 2.459e48) ; f = %.5e (prompt 2.123e-17) -> %s\n", Fh, hbc, law_I::P_conv, law_III::f_transfer, v1 ? "met" : "NOT MET");
    if (!v1) ++fails;
    // ---- V2
    auto tf = [](double x) { return x * x; };
    double e1 = std::fabs(dln(tf, 3.0) - 2) + std::fabs(dln([](double y) { return std::pow(y, -3.0); }, 1.7) + 3) + std::fabs(dln([](double z) { return std::sqrt(z); }, 0.4) - 0.5);
    bool v2 = e1 < 3e-8;
    std::printf("[V2] finite-difference exponents on test functions: summed error %.2e -> %s\n\n", e1, v2 ? "met" : "NOT MET");
    if (!v2) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // ---- T1
    double Pb = Pbasis(al, hb, c, mp, me, W1), Pform = mp * mp * me * me * std::pow(c, 5) / (4 * PI * al * std::pow(hb, 3)), Pc = 4 * al * hb * c / (PI * Rp * Rp * re * re);
    std::printf("[T1] P_basis (alpha hbar c / geometry, W+1 = %.0f) = %.6e Pa ; closed form m_p^2 m_e^2 c^5/(4 pi alpha hbar^3) = %.6e ; engine law_III::P_eff = %.6e ; Coulomb-defined with measured R_p = %.6e\n", W1, Pb, Pform, Pe, Pc);
    double d1 = Pb / Pe - 1, d1b = Pform / Pb - 1, d2 = Pe / Pc - 1;
    std::printf("     P_basis/P_engine - 1 = %+.3e ; closed form/P_basis - 1 = %+.3e ; P_engine/P_Coulomb-defined - 1 = %+.4e (R_p_lock = %.5e m, measured %.5e m, ratio^2 - 1 = %+.4e)\n", d1, d1b, d2, Rl, Rp, (Rp / Rl) * (Rp / Rl) - 1);
    bool R1 = std::fabs(d1) > 1e-3 || std::fabs(d2) > 5e-4;
    std::printf("     R1 (H1 rejected if |P_basis/P_engine - 1| > 1e-3 or |P_engine/P_Coulomb-defined - 1| > 5e-4): %s\n\n", R1 ? "MET (rejected)" : "not met");

    // ---- T2
    std::printf("[T2] dependence exponents d ln P_eff / d ln x (basis form):");
    double ex[6] = {dln([&](double x) { return Pbasis(x, hb, c, mp, me, W1); }, al), dln([&](double x) { return Pbasis(al, x, c, mp, me, W1); }, hb), dln([&](double x) { return Pbasis(al, hb, x, mp, me, W1); }, c),
                    dln([&](double x) { return Pbasis(al, hb, c, x, me, W1); }, mp), dln([&](double x) { return Pbasis(al, hb, c, mp, x, W1); }, me), dln([&](double x) { return Pbasis(al, hb, c, mp, me, x); }, W1)};
    std::printf(" alpha %+.4f, hbar %+.4f, c %+.4f, m_p %+.4f, m_e %+.4f, (W+1) %+.4f\n", ex[0], ex[1], ex[2], ex[3], ex[4], ex[5]);
    double a0b = hb / (me * c * al), rb = al * al * a0b, P_a0b = 4 * al * hb * c / (PI * Rl * Rl * rb * rb), dA = P_a0b / Pe - 1;
    std::printf("     a_0 (measured) = %.10e m ; hbar/(m_e c alpha) = %.10e m ; relative difference %+.3e ; P_eff with a_0 replaced: relative change %+.3e\n", a0, a0b, a0b / a0 - 1, dA);
    double Fc = law_III::F_coulomb(3.7e-10) * 3.7e-10 * 3.7e-10 / (al * hb * c) - 1;
    std::printf("     F_coulomb(r) r^2 / (alpha hbar c) - 1 = %+.3e (CONSTRUCTION: the numerator of P_eff is alpha hbar c; contaminating input: alpha hbar c - measured via CODATA alpha (g-2 and atom-recoil chains) - enters at laws.hpp:461)\n", Fc);
    bool R2 = std::fabs(dA) > 1e-6;
    std::printf("     R2 (H2 rejected if |change| > 1e-6): %s\n\n", R2 ? "MET (rejected)" : "not met");

    // ---- T3
    double PC = 4 * me * c * c / (PI * Rl * Rl * re);
    std::printf("[T3] Route C: P_C = 4 m_e c^2/(pi R_lock^2 r_e) = %.6e Pa ; P_C/P_A - 1 = %+.3e ; ratio = m_e c r_e/(alpha hbar) = %.12f\n", PC, PC / Pe - 1, me * c * re / (al * hb));
    bool R3 = std::fabs(PC / Pe - 1) > 1e-6;
    std::printf("     R3 (H3 rejected if |P_C/P_A - 1| > 1e-6): %s\n\n", R3 ? "MET (rejected)" : "not met");

    // ---- T4
    double fcl = 4 * al * hb * c * M::l_P / (PI * Rl * Rl * re * re * M::R_CMB * law_I::u_CMB), f0 = law_III::f_transfer;
    double eR = dln([&](double x) { return Pe / (x / M::l_P * law_I::u_CMB); }, M::R_CMB);
    std::printf("[T4] f = P_eff/P_conv = %.6e ; closed form = %.6e (relative difference %+.2e) ; d ln f / d ln R_CMB = %+.6f ; R_CMB = %.4e m (MEASURED-INPUT, observed cosmological scale)\n", f0, fcl, fcl / f0 - 1, eR, M::R_CMB);
    bool R4 = std::fabs(eR) > 1e-6;
    std::printf("     R4 (H4 rejected if |exponent| > 1e-6): %s\n\n", R4 ? "MET (rejected)" : "not met");

    // ---- T5
    double Weff = Rp * mp * c / hb, sR = 0.0019e-15, sW = sR * mp * c / hb, z = (Weff - W1) / sW;
    std::printf("[T5] (W+1)_eff = R_p m_p c/hbar = %.5f +/- %.5f (sigma from 0.0019 fm) ; deviation from %.0f: %+.2f sigma ; P_eff(W+1 = 3, 4, 5) = %.4e, %.4e, %.4e Pa ; P_eff shift if (W+1)_eff is used: %+.3e\n", Weff, sW, W1, z, Pbasis(al, hb, c, mp, me, 3), Pbasis(al, hb, c, mp, me, 4), Pbasis(al, hb, c, mp, me, 5), std::pow(W1 / Weff, 2) - 1);
    int within = 0; for (int w = 2; w <= 6; ++w) if (std::fabs(Weff - w) <= 3 * sW) ++within;
    bool R5 = std::fabs(z) > 3;
    std::printf("     integers (2..6) within 3 sigma of (W+1)_eff: %d ; R5 (H5 rejected if |deviation| > 3 sigma): %s\n", within, R5 ? "MET (rejected)" : "not met");
    std::printf("\n[T6] G gate: DEFERRED (FLM01/FLM06)\n");
    return 0;
}
