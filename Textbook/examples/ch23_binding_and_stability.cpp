// Chapter 23 — binding and stability: worked-example instrument.
// Pre-registration: Textbook/validation/ch23_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch23_binding_and_stability
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>

int main() {
    namespace M = sdt::laws::measured;
    namespace NL = sdt::laws::nuclear;
    tb::validate_helpers();
    const double c2 = M::c * M::c, MeV = M::MeV_to_J;

    tb::heading("V1 binding energies from the stored CODATA masses");
    tb::check("V1", "B_d = 2.224566 MeV", M::B_deuteron, 2.224566, 1e-6);
    tb::check("V1", "B_t = 8.481798 MeV", M::B_triton, 8.481798, 1e-6);
    tb::check("V1", "B_h equals 2 m_p + m_n - m_h from the stored masses (nuclear-mass form)", M::B_helion, (2.0 * M::m_p + M::m_n - M::m_He3) * c2 / MeV, 1e-12);
    {
        const double mp = M::m_p * c2 / MeV, mn = M::m_n * c2 / MeV;
        const double Balpha = 2.0 * mp + 2.0 * mn - 3727.3794066;
        tb::note("B_alpha from the published nuclear mass: %.6f MeV ; stored typed value: %.6f MeV ; difference %.2e MeV (%.1e relative; reported, not a criterion)", Balpha, M::B_alpha, M::B_alpha - Balpha, (M::B_alpha - Balpha) / Balpha);
        tb::note("B_h (nuclear-mass form) = %.6f MeV", M::B_helion);
    }

    tb::heading("T1 registered test of H_c: B = eps E_contacts with one constant eps");
    {
        struct S { const char* n; double B; int E; int A; };
        const S sp[4] = {{"d", M::B_deuteron, 1, 2}, {"t", M::B_triton, 2, 3}, {"3He", M::B_helion, 2, 3}, {"4He", M::B_alpha, 4, 4}};
        double lo = 1e300, hi = 0.0, sum = 0.0;
        for (const auto& s : sp) {
            const double e = s.B / s.E;
            lo = std::fmin(lo, e);
            hi = std::fmax(hi, e);
            sum += e;
            tb::note("%-4s : B = %8.4f MeV ; contacts %d ; eps = B/E = %.4f MeV ; B/A = %.4f MeV", s.n, s.B, s.E, e, s.B / s.A);
        }
        const double spread = (hi - lo) / (sum / 4.0);
        tb::note("(eps_max - eps_min)/mean = %.4f ; acceptance limit 0.10", spread);
        tb::check_true("T1", "H_c is rejected (spread exceeds 10%) as registered", spread > 0.10);
    }

    tb::heading("T2 separation energies as finite differences");
    {
        const double Bd = M::B_deuteron, Bt = M::B_triton, Bh = M::B_helion, Ba = M::B_alpha;
        tb::note("S_n(d) = %.6f ; S_n(t) = B_t - B_d = %.6f ; S_n(4He) = B_a - B_h = %.6f ; S_p(4He) = B_a - B_t = %.6f ; S_p(3He) = B_h - B_d = %.6f MeV", Bd, Bt - Bd, Ba - Bh, Ba - Bt, Bh - Bd);
        // mass forms
        const double Sn_d_mass = (M::m_p + M::m_n - M::m_d) * c2 / MeV;                     // m(1,0)=m_p
        const double Sn_t_mass = (M::m_d + M::m_n - M::m_t) * c2 / MeV;
        tb::check("T2", "S_n(d): mass form equals B_d", Sn_d_mass, Bd, 1e-12);
        tb::check("T2", "S_n(t): mass form equals B_t - B_d", Sn_t_mass, Bt - Bd, 1e-9);
        const double mirror = (M::m_n - M::m_p) * c2 / MeV - (M::m_t - M::m_He3) * c2 / MeV;
        tb::check("T2", "mirror identity B_t - B_h = (m_n - m_p) c^2 - (m_t - m_h) c^2", mirror, Bt - Bh, 1e-9);
        tb::note("energy per added contact: d (0 -> 1): %.4f ; t from d (1 -> 2): %.4f ; 4He from 3He (2 -> 4): %.4f MeV per contact", Bd, Bt - Bd, (Ba - Bh) / 2.0);
    }

    tb::heading("T3 bulk radius law and the two radius definitions");
    {
        const double eta = std::numbers::pi / std::sqrt(18.0);
        tb::check("T3", "eta = pi/sqrt(18) = 0.7404805", eta, 0.7404805, 1e-7);
        tb::check("T3", "R(8A)/R(A) = 2", NL::nuclear_boundary_radius(32) / NL::nuclear_boundary_radius(4), 2.0, 1e-12);
        tb::check("T3", "R(1) = R_p eta^(-1/3)", NL::nuclear_boundary_radius(1), M::R_p * std::pow(eta, -1.0 / 3.0), 1e-12);
        const double bulk = NL::nuclear_boundary_radius(4), contact = NL::R_He_contact_diameter;
        tb::note("A=4: bulk-law radius %.4f fm ; contact diameter 2 R_p = %.4f fm ; stored measured R_He = %.4f fm", bulk * 1e15, contact * 1e15, M::R_He * 1e15);
        tb::note("ratios to R_He: bulk %.4f ; contact diameter %.4f", bulk / M::R_He, contact / M::R_He);
    }

    return tb::finish();
}
