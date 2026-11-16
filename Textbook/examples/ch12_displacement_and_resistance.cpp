// Chapter 12 — displacement and resistance: worked-example instrument.
// Pre-registration: Textbook/validation/ch12_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch12_displacement_and_resistance
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <functional>

namespace {

constexpr double kPi = std::numbers::pi;

// Axisymmetric angular integral: oint f(mu) dOmega = 2 pi int_{-1}^{1} f(mu) dmu (mu = cos of the angle to the axis).
double sphere(const std::function<double(double)>& f) { return 2.0 * kPi * tb::integrate(f, -1.0, 1.0, 48, 16); }

}  // namespace

int main() {
    namespace L = sdt::laws;
    namespace M = sdt::laws::measured;
    namespace IV = sdt::laws::law_IV;
    tb::validate_helpers();

    tb::heading("V1 angular integrals");
    tb::check("V1", "oint dOmega = 4 pi", sphere([](double) { return 1.0; }), 4.0 * kPi, 1e-13);
    tb::check("V1", "oint n_z dOmega = 0 (absolute)", sphere([](double mu) { return mu; }), 0.0, 1e-13, false);
    tb::check("V1", "oint (v . n) n_z dOmega = 4 pi / 3 for v = 1 along z", sphere([](double mu) { return mu * mu; }), 4.0 * kPi / 3.0, 1e-13);

    tb::heading("T1 momentum of the content in the exclusion volume under the first-order dipole");
    {
        const double v = 0.01 * M::c;  // the integrand is linear in v; at 1 m/s the cancelling monopole sum swamps the dipole
        for (int k = 0; k < 2; ++k) {
            const double V = k == 0 ? IV::V_disp_p : IV::V_disp_e;
            const double m = IV::mass_from_V_disp(V);
            const double p = (V / (M::l_P3 * M::c)) * (L::law_I::Phi / (4.0 * kPi)) *
                             sphere([&](double mu) { return (1.0 + v * mu / M::c) * mu; });
            tb::check("T1", k == 0 ? "p / (m_p v), V = V_disp,p" : "p / (m_e v), V = V_disp,e", p / (m * v), 1.0, 1e-12);
        }
    }

    tb::heading("T2 the dipole of the two forms in the source");
    {
        const double beta = 1e-4;
        auto D = [&](const std::function<double(double)>& phi) {
            return sphere([&](double mu) { return phi(mu) * mu; }) / sphere(phi);
        };
        const double d31 = D([&](double mu) { return 1.0 + beta * mu; }) / beta;
        const double d71 = D([&](double mu) { return 1.0 / ((1.0 - beta * mu) * (1.0 - beta * mu)); }) / beta;
        tb::check("T2", "Eq. 3.1: D/beta -> 1/3", d31, 1.0 / 3.0, 1e-3);
        tb::check("T2", "Corollary 7.1: D/beta -> 2/3", d71, 2.0 / 3.0, 1e-3);
        tb::note("D/beta: Eq. 3.1 %.9f ; Corollary 7.1 %.9f ; ratio %.6f", d31, d71, d71 / d31);
    }

    tb::heading("T3 Corollary 7.1 used as in the derivation of Theorem 5");
    {
        auto I1_quad = [](double b) {
            return tb::integrate([&](double mu) { return mu / ((1.0 - b * mu) * (1.0 - b * mu)); }, -1.0, 1.0, 48, 16);
        };
        auto I1_closed = [](double b) {
            return (2.0 * b / (1.0 - b * b) - std::log((1.0 + b) / (1.0 - b))) / (b * b);
        };
        auto r = [&](double b) { return 3.0 * I1_quad(b) / (2.0 * b); };
        tb::check("T3", "r(beta) -> 2 as beta -> 0 (beta = 1e-3)", r(1e-3), 2.0, 1e-5);
        double worst = 0.0;
        for (double b : {0.1, 0.5, 0.9}) worst = std::fmax(worst, std::fabs(I1_quad(b) / I1_closed(b) - 1.0));
        tb::check("T3", "I_1 closed form vs quadrature at beta = 0.1, 0.5, 0.9 (worst relative)", worst, 0.0, 1e-12, false);
        for (double b : {0.1, 0.5, 0.9}) {
            const double g = L::law_V::gamma(b * M::c);
            tb::note("beta = %.1f: r(beta)/2 = %.6f ; gamma = %.6f ; ratio %.6f", b, r(b) / 2.0, g, r(b) / (2.0 * g));
        }
        const double g5 = L::law_V::gamma(0.5 * M::c);
        tb::check_true("T3", "at beta = 0.5, r/2 differs from gamma by more than 5%", std::fabs(r(0.5) / (2.0 * g5) - 1.0) > 0.05);
    }

    tb::heading("T4 relay-lock volumes");
    {
        const double b = 2.5;
        const double eng_vol = 4.0 * kPi * tb::integrate([&](double s) {  // r = b s^2: dr = 2 b s ds, sqrt(r/b) = s
                                    const double r = b * s * s;
                                    return r * r * s * 2.0 * b * s;
                                }, 0.0, 1.0, 48, 4);
        tb::check("T4", "4 pi int r^2 sqrt(r/b) dr vs locked_engaged_volume_sphere(b)", eng_vol, IV::locked_engaged_volume_sphere(b), 1e-12);
        tb::check("T4", "locked volume = 8 pi b^3 / 7", IV::locked_engaged_volume_sphere(b), 8.0 * kPi * b * b * b / 7.0, 1e-14);
        tb::check("T4", "wake volume = 4 pi b^3 / 21", IV::wake_volume_sphere(b), 4.0 * kPi * b * b * b / 21.0, 1e-14);
        tb::check("T4", "locked + wake = (4 pi/3) b^3", IV::locked_engaged_volume_sphere(b) + IV::wake_volume_sphere(b), 4.0 * kPi * b * b * b / 3.0, 1e-14);
        tb::check("T4", "locked fraction 6/7", IV::locked_engaged_volume_sphere(b) / (4.0 * kPi * b * b * b / 3.0), 6.0 / 7.0, 1e-14);
    }

    tb::heading("T5 convergence floor");
    {
        const double b = M::R_CMB;
        tb::check("T5", "average_resistance_density = 2 P_conv / (7 c^2)", IV::convergence_floor::average_resistance_density(b), 2.0 * L::law_I::P_conv / (7.0 * M::c * M::c), 1e-12);
        tb::check("T5", "acceleration(R_CMB) = 7 c^2 / (6 R_CMB)", IV::convergence_floor::acceleration(b), 7.0 * M::c * M::c / (6.0 * b), 1e-12);
        tb::check("T5", "cosmological_acceleration = acceleration(R_CMB)", IV::convergence_floor::cosmological_acceleration, IV::convergence_floor::acceleration(b), 1e-14);
        tb::note("floor acceleration 7 c^2 / (6 R_CMB) = %.6e m/s^2 (R_CMB is a measured boundary; COMPUTED, not an independent prediction)", 7.0 * M::c * M::c / (6.0 * b));
    }

    tb::heading("T6 binding as reduced exclusion volume (CONSTRUCTION)");
    {
        struct Case {
            const char* name;
            double joint, a, b, B_MeV;
        };
        const Case cs[] = {{"deuteron", M::m_d, M::m_p, M::m_n, M::B_deuteron},
                           {"triton", M::m_t, M::m_p, 2.0 * M::m_n, M::B_triton},
                           {"helion", M::m_He3, 2.0 * M::m_p, M::m_n, M::B_helion}};
        for (const Case& c : cs) {
            const double Vj = IV::V_disp_from_mass(c.joint), Vp = IV::V_disp_from_mass(c.a) + IV::V_disp_from_mass(c.b);
            const double delta = IV::synchrony_resistance_delta(Vj, Vp);
            tb::check("T6", (std::string(c.name) + ": synchrony_resistance_delta = -B (joules)").c_str(), delta, -c.B_MeV * M::MeV_to_J, 1e-9);
            tb::check("T6", (std::string(c.name) + ": fractional volume reduction = B/(M c^2)").c_str(), (Vp - Vj) / Vj, c.B_MeV * M::MeV_to_J / (c.joint * M::c * M::c), 1e-9);
            tb::note("%s: V_joint = %.6e m^3, V_parts = %.6e m^3, reduction %.6e m^3 (%.4e of V_joint)", c.name, Vj, Vp, Vp - Vj, (Vp - Vj) / Vj);
        }
    }

    tb::heading("Sensitivity to the numerical factor of Law IV (reported)");
    {
        const double Vp3 = IV::V_disp_p, Vp6 = 2.0 * IV::V_disp_p;
        tb::note("V_disp,p with factor 3: %.6e m^3, R_excl %.6e m ; with factor 6: %.6e m^3, R_excl %.6e m (ratio of radii %.6f)", Vp3, IV::R_excl_p,
                 Vp6, IV::exclusion_radius(Vp6), IV::exclusion_radius(Vp6) / IV::R_excl_p);
    }

    return tb::finish();
}
