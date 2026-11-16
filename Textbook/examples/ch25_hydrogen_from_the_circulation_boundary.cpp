// Chapter 25 — hydrogen from the circulation boundary: worked-example instrument.
// Pre-registration: Textbook/validation/ch25_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch25_hydrogen_from_the_circulation_boundary
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>

int main() {
    namespace M = sdt::laws::measured;
    namespace A = sdt::laws::atomic;
    tb::validate_helpers();
    const double c = M::c, alpha = M::alpha, a0 = M::a_0, re = M::r_e;

    tb::heading("V1 reduced-mass factor");
    {
        double worst = 0.0;
        for (double m : {M::m_p, M::m_d, M::m_t, M::m_He3}) worst = std::fmax(worst, std::fabs(A::reduced_mass_factor(m) / (1.0 / (1.0 + M::m_e / m)) - 1.0));
        tb::check("V1", "reduced_mass_factor equals 1/(1 + m_e/m_nuc), worst relative", worst, 0.0, 1e-15, false);
        const double heavy = 1e3 * M::m_p, x = M::m_e / heavy;
        tb::check("V1", "(1 - factor)/(m_e/m_nuc) = 1/(1 + m_e/m_nuc) for a heavy nucleus (10^3 m_p)", (1.0 - A::reduced_mass_factor(heavy)) / x, 1.0 / (1.0 + x), 1e-8);
    }

    tb::heading("T1 the ladder, the boundary length and the rotation-field function");
    {
        double w_om = 0.0, w_z = 0.0, w_zk = 0.0, w_rf1 = 0.0, w_rfZ = 0.0;
        double min_dev_Zgt1 = 1e300;
        for (int Z = 1; Z <= 5; ++Z)
            for (int n = 1; n <= 10; ++n) {
                const double v = A::bohr_velocity(Z, n), r = A::bohr_radius(Z, n);
                const double om = v * v * r / (c * c), z = om / r, k = c / v;
                w_om = std::fmax(w_om, std::fabs(om / (Z * re) - 1.0));
                w_z = std::fmax(w_z, std::fabs(z / std::pow(Z * alpha / n, 2) - 1.0));
                w_zk = std::fmax(w_zk, std::fabs(z * k * k - 1.0));
                const double rf = A::rotation_field_velocity(r);
                const double ratio = rf / v;
                if (Z == 1) w_rf1 = std::fmax(w_rf1, std::fabs(ratio - 1.0));
                else {
                    w_rfZ = std::fmax(w_rfZ, std::fabs(ratio * std::sqrt(double(Z)) - 1.0));
                    min_dev_Zgt1 = std::fmin(min_dev_Zgt1, std::fabs(ratio - 1.0));
                }
            }
        tb::check("T1", "Om_Z = v^2 r/c^2 equals Z r_e over 50 states, worst relative", w_om, 0.0, 1e-14, false);
        tb::check("T1", "z = Om/r equals (Z alpha/n)^2, worst relative", w_z, 0.0, 1e-14, false);
        tb::check("T1", "z k^2 = 1 (identity of the definitions), worst deviation", w_zk, 0.0, 1e-14, false);
        tb::check("T1", "rotation_field_velocity at r_n equals bohr_velocity for Z = 1", w_rf1, 0.0, 1e-14, false);
        tb::check("T1", "for Z > 1 it equals bohr_velocity/sqrt(Z), worst relative", w_rfZ, 0.0, 1e-14, false);
        tb::check_true("T1", "for Z > 1 it differs from bohr_velocity by at least 29% in every state", min_dev_Zgt1 > 0.29);
        tb::note("Z=2: ratio rotation_field/bohr = %.6f (1/sqrt 2 = %.6f)", A::rotation_field_velocity(A::bohr_radius(2, 1)) / A::bohr_velocity(2, 1), 1.0 / std::sqrt(2.0));
    }

    tb::heading("T2 spectral scale and the two engine routes");
    {
        tb::check("T2a", "R_inf_derived / R_inf = 1 (shared-input)", A::R_inf_derived, M::R_inf, 1e-9);
        tb::check("T2a", "Ry = h c R_inf / e (shared-input)", M::h * c * M::R_inf / M::e_charge, M::Ry_eV, 1e-9);
        const double hc = M::h * c;
        const double l12 = A::emission_wavelength_m(1, 1, 2, M::m_p), l23 = A::emission_wavelength_m(1, 2, 3, M::m_p);
        const double E12 = (A::level_energy_eV(1, 2, M::m_p) - A::level_energy_eV(1, 1, M::m_p)) * M::e_charge;
        const double E23 = (A::level_energy_eV(1, 3, M::m_p) - A::level_energy_eV(1, 2, M::m_p)) * M::e_charge;
        tb::check("T2b", "Lyman-alpha: emission_wavelength_m equals hc/(E2 - E1) from level_energy_eV", l12, hc / E12, 1e-9);
        tb::check("T2b", "Balmer-alpha: emission_wavelength_m equals hc/(E3 - E2)", l23, hc / E23, 1e-9);
        tb::note("leading-order hydrogen (m_nuc = m_p): Lyman-alpha %.6f nm ; Balmer-alpha %.6f nm (not compared with a measured value)", l12 * 1e9, l23 * 1e9);
        tb::check("T2c", "lambda_Lya / lambda_Ha = 5/27", l12 / l23, 5.0 / 27.0, 1e-14);
    }

    tb::heading("T3 isotope shifts from one nuclear response");
    {
        auto mu = [](double m) { return m / (M::m_e + m); };
        const double lHa = A::emission_wavelength_m(1, 2, 3, M::m_p), lDa = A::emission_wavelength_m(1, 2, 3, M::m_d), lTa = A::emission_wavelength_m(1, 2, 3, M::m_t);
        tb::check("T3", "lambda_H/lambda_D = mu_D/mu_H", lHa / lDa, mu(M::m_d) / mu(M::m_p), 1e-14);
        tb::check("T3", "lambda_D/lambda_T = mu_T/mu_D", lDa / lTa, mu(M::m_t) / mu(M::m_d), 1e-14);
        tb::note("Balmer-alpha: lambda_H - lambda_D = %.5f nm (fractional %.4e) ; lambda_H - lambda_T = %.5f nm ; lambda_D - lambda_T = %.5f nm", (lHa - lDa) * 1e9, (lHa - lDa) / lHa, (lHa - lTa) * 1e9, (lDa - lTa) * 1e9);
        const double lHe_inf = 1.0 / (A::R_inf_derived * 4.0 * (1.0 / 4.0 - 1.0 / 9.0));  // Z = 2 infinite nucleus, n=2->3
        const double lHe = A::emission_wavelength_m(2, 2, 3, M::m_He3);
        tb::note("hydrogen-like helion, n=2->3: %.6f nm with the helion mass ; %.6f nm for an infinite nucleus ; shift %.5f nm", lHe * 1e9, lHe_inf * 1e9, (lHe - lHe_inf) * 1e9);
        double worst = 0.0;
        for (double m : {M::m_p, M::m_d, M::m_t, M::m_He3}) {
            const double approx = 1.0 - M::m_e / m, exact = mu(m);
            worst = std::fmax(worst, std::fabs((exact - approx) / ((M::m_e / m) * (M::m_e / m)) - 1.0 * 1.0 * (-1.0) * (-1.0) * 0.0 - 1.0));
        }
        // exact - approx = (m_e/m)^2 / (1 + m_e/m) so relative to (m_e/m)^2 it is 1/(1+m_e/m): deviation from 1 is m_e/m
        double dev = 0.0;
        for (double m : {M::m_p, M::m_d, M::m_t, M::m_He3}) {
            const double x = M::m_e / m;
            dev = std::fmax(dev, std::fabs((mu(m) - (1.0 - x)) / (x * x) - 1.0 / (1.0 + x)));
        }
        (void)worst;
        tb::check("T3", "(mu - (1 - m_e/m))/(m_e/m)^2 = 1/(1 + m_e/m): error of the first-order form is second order", dev, 0.0, 1e-6, false);
    }

    tb::heading("T4 size of the first omitted correction (reported)");
    {
        tb::note("(Z alpha/n)^2 for Z=1, n=1: %.2f ppm ; for Z=30, n=1: %.2f ppm", alpha * alpha * 1e6, std::pow(30 * alpha, 2) * 1e6);
    }

    return tb::finish();
}
