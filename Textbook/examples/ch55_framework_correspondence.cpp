// Chapter 55 — framework correspondence: worked-example instrument.
// Pre-registration: Textbook/validation/ch55_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <cstring>
#include <numbers>
#include <string>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
namespace V = sdt::laws::law_V;
namespace B = sdt::laws::bridge;
constexpr double PI = std::numbers::pi;
constexpr double MeV_J = 1.602176634e-13;

struct Row {
    const char* observable;
    const char* native;
    const char* equivalent;
    const char* inputs;
    const char* approx;
    char prov;           // A derived, B shared-input, C calibrated
    const char* discr;   // "none" or "candidate"
};

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    tb::check("V1", "gamma(0.6 c) = 1.25", V::gamma(0.6 * M::c), 1.25, 1e-14);
    tb::check("V1", "v_circ(v_trans(x)) = x", V::v_circ(V::v_trans(0.3 * M::c)), 0.3 * M::c, 1e-14);
    {
        const double Om = B::koppa_Sun, r = M::AU;
        const double T = 2.0 * PI * std::sqrt(r * r * r / (M::c * M::c * Om));
        tb::check("V1", "c sqrt(Om/r) = 2 pi r / T", M::c * std::sqrt(Om / r), 2.0 * PI * r / T, 1e-14);
    }

    tb::heading("T1 orbital chain, native-first");
    {
        const double Om = B::koppa_Sun, r = M::AU;
        const double T = 2.0 * PI * std::sqrt(r * r * r / (M::c * M::c * Om));
        const double Td = T / 86400.0;
        const double v = M::c * std::sqrt(Om / r);
        tb::note("Om_Sun = R_Sun/k_Sun^2 = %.6f m (k_Sun = 686.3 stored) ; period at 1 AU = %.4f d ; circular speed = %.4f km/s", Om, Td, v / 1e3);
        tb::check_true("T1", "the native period lies in [365.07, 365.44] d", Td >= 365.07 && Td <= 365.44);
        tb::check_true("T1", "the circular speed lies in [29.7, 29.9] km/s", v / 1e3 >= 29.7 && v / 1e3 <= 29.9);
        const double year = 365.256363;
        tb::note("read now: sidereal year %.6f d ; relative difference of the native period %+.3e", year, Td / year - 1.0);
    }

    tb::heading("T2 movement budget");
    {
        double worst = 0.0, worst_diff = 0.0;
        for (int i = 0; i < 20; ++i) {
            const double beta = 0.01 + (0.999 - 0.01) * i / 19.0;
            const double v = beta * M::c, m = 1.0;
            const double E = V::total_energy(m, v), p = V::momentum(m, v);
            const double mc2sq = m * m * std::pow(M::c, 4);
            worst = std::fmax(worst, std::fabs(E * E - p * p * M::c * M::c - mc2sq) / (E * E));  // relative to the size of the terms
            worst_diff = std::fmax(worst_diff, std::fabs((E * E - p * p * M::c * M::c) / mc2sq - 1.0));
        }
        tb::note("worst deviation relative to the difference (m c^2)^2: %.3e", worst_diff);
        tb::check("T2", "E^2 - (pc)^2 = (m c^2)^2 over 20 speeds (worst deviation relative to E^2)", worst, 0.0, 1e-14, false);
        tb::check("T2", "photon limit: v_circ = 0 gives v = c", V::v_trans(V::photon_v_circ), M::c, 1e-15);
        tb::check("T2", "gamma(0.6 c) = 1.25", V::gamma(0.6 * M::c), 1.25, 1e-14);
    }

    tb::heading("T3 the correspondence table");
    {
        const double zs = B::koppa_Sun / M::R_Sun;
        const double rel03 = 0.3 / (1.0 - 0.3), rel_sun = zs / (1.0 - zs);
        const double m_alpha = 2.0 * M::m_p + 2.0 * M::m_n - M::B_alpha * MeV_J / (M::c * M::c);
        const double src = (4.0 * M::m_p - m_alpha) / m_alpha;
        tb::note("convention difference at z_e = 0.3: %.4f ; at the solar surface: %.4e ; source-strength difference (alpha vs 4 protons): %.4e", rel03, rel_sun, src);
        tb::check("T3", "relative difference of the redshift conventions at z_e = 0.3", rel03, 0.4286, 1e-4);
        tb::check("T3", "relative difference of the conventions at the solar surface", rel_sun, 2.1231e-6, 1e-4);
        tb::check("T3", "source-strength difference (alpha vs four protons)", src, 6.897e-3, 1e-3);

        const std::vector<Row> rows = {
            {"circular orbit period", "T = 2 pi sqrt(r^3/(c^2 Om)), Om = R/k^2", "T = 2 pi sqrt(r^3/GM)", "Om from surface speed; the source strength is read from ephemeris fits (named shared input)", "point source, stationary central response", 'B', "none"},
            {"circular speed", "v = c sqrt(Om/r) = c sqrt(z)", "v = sqrt(GM/r)", "same Om (shared input)", "circular state", 'B', "none"},
            {"energy-momentum", "movement budget v_circ^2 + v^2 = c^2 -> gamma, E = gamma m c^2", "special-relativistic kinematics", "none beyond c (posited budget)", "adopted response premises", 'A', "none"},
            {"spectral shift between depths", "z_spec = z_e - z_o (A) or (z_e - z_o)/(1 - z_e) (B)", "weak-field redshift (first order)", "depths Om/r (defined geometric ratio)", "convention of the transport not derived", 'A', "candidate"},
            {"signal delay, second order", "c_far = c(1-z)^2 profile; delay coefficients", "weak-field delay to first order", "Om_Sun (shared input)", "second-order coefficient from the repaired profile", 'B', "candidate"},
            {"composite source strength", "koppa additive in baryon count", "mass-proportional source", "baryon count; B_alpha stored (rounded)", "binding not entering the source", 'A', "candidate"},
            {"plate energy amplitude", "mode price a (counting fixes the coefficient per a)", "ideal-plate coefficient for a = 1/2", "a calibrated", "ideal plates, smooth cutoff", 'C', "candidate"},
            {"registration statistics", "threshold accumulate-and-fire: Fano <= 1/(4 mu)", "Poisson counting for an ideal steady source", "none (stand-in rule)", "deterministic accumulation", 'A', "candidate"},
        };
        bool filled = true;
        int n_Anone = 0, n_Bnone = 0, n_Acand = 0, n_Bcand = 0;
        std::printf("       %-30s | %-1s | %-9s | native -> equivalent\n", "observable", "P", "discrimin.");
        for (const auto& r : rows) {
            filled = filled && std::strlen(r.native) > 0 && std::strlen(r.equivalent) > 0 && std::strlen(r.inputs) > 0 && std::strlen(r.approx) > 0;
            const bool none = std::strcmp(r.discr, "none") == 0;
            if (r.prov == 'A' && none) ++n_Anone;
            if (r.prov == 'B' && none) ++n_Bnone;
            if (r.prov == 'A' && !none) ++n_Acand;
            if (r.prov == 'B' && !none) ++n_Bcand;
            std::printf("       %-30s | %c | %-9s | %s -> %s | inputs: %s | retained: %s\n", r.observable, r.prov, r.discr, r.native, r.equivalent, r.inputs, r.approx);
        }
        tb::note("rows: (A,none) %d, (B,none) %d, (A,candidate) %d, (B,candidate) %d", n_Anone, n_Bnone, n_Acand, n_Bcand);
        tb::check_true("T3", "every row carries the five descriptive fields", filled && rows.size() == 8);
        tb::check_true("T3", "the four combinations of provenance and discrimination are all populated", n_Anone >= 1 && n_Bnone >= 1 && n_Acand >= 1 && n_Bcand >= 1);
    }

    return tb::finish();
}
