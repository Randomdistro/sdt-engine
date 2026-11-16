// Chapter 11 — universal interaction: worked-example instrument.
// Pre-registration: Textbook/validation/ch11_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch11_universal_interaction
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>

namespace {
constexpr double kPi = std::numbers::pi;
// log-slope of f between r and 10 r
template <class F>
double slope(F f, double r) {
    return std::log(f(10.0 * r) / f(r)) / std::log(10.0);
}
}  // namespace

int main() {
    namespace L = sdt::laws;
    namespace M = sdt::laws::measured;
    namespace III = sdt::laws::law_III;
    tb::validate_helpers();

    tb::heading("V1 geometry factor");
    {
        const double R1 = 2, R2 = 3, r = 7, U = 5, q = U / (4.0 * kPi);
        tb::check("V1", "q pi^2 R1^2 R2^2 / r^2 = (pi/4) U R1^2 R2^2 / r^2", q * kPi * kPi * R1 * R1 * R2 * R2 / (r * r),
                  (kPi / 4.0) * U * R1 * R1 * R2 * R2 / (r * r), 1e-15);
    }
    tb::heading("V2 slope estimator");
    tb::check("V2", "log-slope of 1/r^2 between r and 10r is -2", slope([](double r) { return 1.0 / (r * r); }, 3.7), -2.0, 1e-13);

    const double Rlock = III::R_p_lock;
    const double r_e = M::r_e;
    const double Rint = std::sqrt(Rlock * r_e);  // the interaction radius, formed locally

    tb::heading("T1 three forms of P_eff");
    {
        const double p1 = III::P_eff;
        const double p2 = std::pow(M::m_p, 2) * std::pow(M::m_e, 2) * std::pow(M::c, 5) / (4.0 * kPi * M::alpha * std::pow(M::hbar, 3));
        const double p3 = M::m_e * M::c * M::c / III::V_int_pe;
        tb::check("T1", "engine P_eff vs m_p^2 m_e^2 c^5 / (4 pi alpha hbar^3)", p1, p2, 1e-9);
        tb::check("T1", "engine P_eff vs m_e c^2 / V_int", p1, p3, 1e-9);
        tb::check("T1", "closed form vs m_e c^2 / V_int", p2, p3, 1e-9);
        tb::check("T1", "P_eff_from_volume / P_eff - 1 inside the engine's 1e-8 bound", III::P_eff_from_volume / p1 - 1.0, 0.0, 1e-8, false);
        tb::note("R_lock = 4 hbar/(m_p c) = %.6e m ; r_e = %.6e m ; R_int = sqrt(R_lock r_e) = %.6e m", Rlock, r_e, Rint);
        tb::note("V_int = (pi/4) R_lock^2 r_e = %.6e m^3 ; P_eff = %.6e Pa", III::V_int_pe, p1);
    }

    tb::heading("T2 Coulomb form");
    {
        double worst_form = 0.0, worst_alg = 0.0;
        for (double r : {M::a_0, 1e-9, 1e-6, 1.0}) {
            const double F = III::F_coulomb(r);
            worst_alg = std::fmax(worst_alg, std::fabs(F * r * r / L::coulomb_identity::k_e_e2 - 1.0));
            worst_form = std::fmax(worst_form, std::fabs(F / ((kPi / 4.0) * III::P_eff * std::pow(Rint, 4) / (r * r)) - 1.0));
        }
        tb::check("T2", "F_Coulomb(r) r^2 = alpha hbar c at four separations (worst relative)", worst_alg, 0.0, 1e-14, false);
        tb::check("T2", "F_Coulomb = (pi/4) P_eff R_int^4 / r^2 with R_int formed locally (worst relative)", worst_form, 0.0, 1e-14, false);
        tb::check("T2", "alpha hbar c vs k_e e^2 of the stored CODATA constants", L::coulomb_identity::k_e_e2, L::coulomb_identity::k_e_e2_codata, 1e-9);
        tb::note("F_Coulomb(a_0) = %.9e N", III::F_coulomb(M::a_0));
    }

    tb::heading("T3 inverse-square over six decades");
    {
        double worst = 0.0;
        for (double r = 1e-10; r < 1e-3; r *= 10.0) {
            worst = std::fmax(worst, std::fabs(slope([&](double x) { return III::F_occlusion(Rlock, r_e, x); }, r) + 2.0));
            worst = std::fmax(worst, std::fabs(slope([&](double x) { return III::F_occlusion(2.0, 3.0, x); }, r * 1e10) + 2.0));
        }
        tb::check("T3", "log-slope of F_occlusion between r and 10 r, worst deviation from -2 (6 decades, 2 radius pairs)", worst, 0.0, 1e-12, false);
    }

    tb::heading("T4 count scaling");
    {
        double worst = 0.0;
        const double F1 = III::F_nuclear_electron(1, M::a_0);
        for (int Z = 1; Z <= 20; ++Z) worst = std::fmax(worst, std::fabs(III::F_nuclear_electron(Z, M::a_0) / F1 / Z - 1.0));
        tb::check("T4", "F_nuc-e(Z, a_0) / F_nuc-e(1, a_0) = Z, worst relative over Z = 1..20", worst, 0.0, 1e-14, false);
        tb::check("T4", "F_nuc-e(1, a_0) = F_Coulomb(a_0)", F1, III::F_coulomb(M::a_0), 1e-14);
        const double F_old = III::F_occlusion(2.0 * M::R_p, r_e, M::a_0) / III::F_occlusion(1.0 * M::R_p, r_e, M::a_0);
        tb::note("excluded geometry R_nuc = Z R_p: F(Z=2)/F(Z=1) = %.6f (Z^2 = 4)", F_old);
        tb::check("T4", "the excluded geometry would give Z^2 (ratio 4 at Z = 2)", F_old, 4.0, 1e-14);
    }

    tb::heading("T5 hydrogen balance (CONSTRUCTION)");
    {
        const double lhs = III::F_coulomb(M::a_0), rhs = M::m_e * std::pow(M::alpha * M::c, 2) / M::a_0;
        tb::check("T5", "F_Coulomb(a_0) vs m_e (alpha c)^2 / a_0", lhs, rhs, 1e-9);
        tb::note("%.9e N against %.9e N", lhs, rhs);
    }

    tb::heading("T6 measured boundary radius against the lock boundary");
    {
        const double ratio = III::F_occlusion(M::R_p, r_e, M::a_0) / III::F_coulomb(M::a_0);
        tb::check("T6", "F_occlusion(R_p, r_e, a_0) / F_Coulomb(a_0) = (R_p / R_lock)^2", ratio, std::pow(M::R_p / Rlock, 2), 1e-12);
        tb::note("(R_p/R_lock)^2 - 1 = %.4e (R_p measured %.6e m, R_lock %.6e m)", ratio - 1.0, M::R_p, Rlock);
    }

    tb::heading("T7 transfer function");
    {
        tb::check("T7", "f_transfer vs V_disp,e / (3 V_int)", III::f_transfer, L::law_IV::V_disp_e / (3.0 * III::V_int_pe), 1e-9);
    }

    tb::heading("Pressure ladder (reported, not criteria)");
    tb::note("u_CMB   = %.6e Pa (energy density a_rad T^4)", L::law_I::u_CMB);
    tb::note("P_rad   = u/3 = %.6e Pa", L::law_I::u_CMB / 3.0);
    tb::note("P_conv  = N u = %.6e Pa", L::law_I::P_conv);
    tb::note("P_cf    = P_conv/3 = %.6e Pa", L::law_I::P_conv / 3.0);
    tb::note("P_eff   = %.6e Pa ; f = P_eff/P_conv = %.6e", III::P_eff, III::f_transfer);

    return tb::finish();
}
