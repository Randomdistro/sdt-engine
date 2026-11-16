// Chapter 54 — cosmological accounting: worked-example instrument (factor ledger, generic conventions, no data).
// Pre-registration: Textbook/validation/ch54_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/cosmology.hpp>
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>

namespace {

constexpr double PI = 3.14159265358979323846;

// bolometric flux F = L / (4 pi d^2) * fE * fR
double flux(double L, double d, double fE, double fR) { return L / (4.0 * PI * d * d) * fE * fR; }
double dmag(double F1, double F2) { return 2.5 * std::log10(F2 / F1); }  // magnitude of F1 minus magnitude of F2 ... sign: dmag > 0 when F2 > F1

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    tb::check("V1", "5 log10 2", 5.0 * std::log10(2.0), 1.505150, 1e-6);
    tb::check("V1", "2.5 log10 2", 2.5 * std::log10(2.0), 0.752575, 1e-6);
    tb::check("V1", "magnitude difference of a factor 10 in flux is 2.5", dmag(1.0, 10.0), 2.5, 1e-12);

    const double zs[4] = {0.1, 0.5, 1.0, 2.0};
    const double L = 1.0, d = 3.7;

    tb::heading("T1 flux factors under declared conventions");
    for (double z : zs) {
        const double Fa = flux(L, d, 1.0 / (1.0 + z), 1.0 / (1.0 + z));            // endpoint-ratio branch
        const double Fb = flux(L, d, 1.0 / (1.0 + z), 1.0);                          // energy shift only
        const double dL = d * (1.0 + z);                                             // distance already containing the factor
        const double Fh = flux(L, dL, 1.0 / (1.0 + z), 1.0 / (1.0 + z));            // hybrid: factor applied twice
        const double m_h = dmag(Fh, Fa), m_b = dmag(Fa, Fb);                         // magnitudes by which (a) is brighter than the hybrid; (b) is brighter than (a)
        char lab[128];
        std::snprintf(lab, sizeof lab, "z = %.1f: hybrid is fainter than branch (a) by 5 log10(1+z) = %.6f mag", z, 5.0 * std::log10(1.0 + z));
        tb::check("T1", lab, m_h, 5.0 * std::log10(1.0 + z), 1e-12);
        std::snprintf(lab, sizeof lab, "z = %.1f: branch (b) is brighter than (a) by 2.5 log10(1+z) = %.6f mag", z, 2.5 * std::log10(1.0 + z));
        tb::check("T1", lab, m_b, 2.5 * std::log10(1.0 + z), 1e-12);
    }

    tb::heading("T2 reciprocity under two declared size conventions");
    for (double z : zs) {
        const double dd = 3.7;
        const double dL = dd * (1.0 + z);
        const double dA_A = dd;                 // sizes unscaled
        const double dA_B = dd / (1.0 + z);     // physical size transforms as the endpoint ruler ratio
        const double etaA = dL / ((1.0 + z) * (1.0 + z) * dA_A), etaB = dL / ((1.0 + z) * (1.0 + z) * dA_B);
        char lab[128];
        std::snprintf(lab, sizeof lab, "z = %.1f: eta_A = 1/(1+z)", z);
        tb::check("T2", lab, etaA, 1.0 / (1.0 + z), 1e-12);
        std::snprintf(lab, sizeof lab, "z = %.1f: eta_B = 1", z);
        tb::check("T2", lab, etaB, 1.0, 1e-12);
        std::snprintf(lab, sizeof lab, "z = %.1f: relative difference of the conventions z/(1+z) = %.4f", z, z / (1.0 + z));
        tb::check("T2", lab, (etaB - etaA) / etaB, z / (1.0 + z), 1e-12);
    }

    tb::heading("T3 a single observable can hide a hybrid; a second cannot");
    for (double z : zs) {
        const double Fa = flux(L, d, 1.0 / (1.0 + z), 1.0 / (1.0 + z));
        const double dprime = d / (1.0 + z);
        const double dL = dprime * (1.0 + z);  // hybrid distance law built from the redefined distance
        (void)dL;
        const double Fh = flux(L, d * (1.0 + z), 1.0 / (1.0 + z), 1.0 / (1.0 + z));  // hybrid with the factor in the distance
        // redefine the geometric distance used by the hybrid as d' = d/(1+z): the hybrid's flux then equals branch (a)
        const double Fhid = flux(L, dprime * (1.0 + z), 1.0 / (1.0 + z), 1.0 / (1.0 + z));  // d_L = d' (1+z) = d
        (void)Fh;
        char lab[128];
        std::snprintf(lab, sizeof lab, "z = %.1f: after d' = d/(1+z) the hybrid flux equals the consistent flux", z);
        tb::check("T3", lab, Fhid, Fa, 1e-12);
        std::snprintf(lab, sizeof lab, "z = %.1f: the angular size s/d' exceeds s/d by the factor 1+z", z);
        tb::check("T3", lab, (1.0 / dprime) / (1.0 / d), 1.0 + z, 1e-12);
    }
    tb::note("ln(1+z) at z = 1: %.6f", std::log(2.0));

    tb::heading("T4 stored distance and duration scales (addendum)");
    {
        namespace M = sdt::laws::measured;
        const double Gyr = 3.15576e7 * 1e9;
        const double Rc = sdt::laws::law_I::R_CMB;
        const double t_travel = Rc / M::c / Gyr;
        const double sigma = sdt::cosmology::strain::sigma_CMB;
        const double Rrec = std::log(1.0 + 1100.0) / sigma, Rrel = std::log(1.0 + M::z_release) / sigma;
        const double drec = Rrec / Rc - 1.0, drel = Rrel / Rc - 1.0;
        tb::note("R_CMB = %.6e m ; R_CMB/c = %.3f Gyr ; sigma_CMB = %.6e m^-1", Rc, t_travel, sigma);
        tb::note("ln(1+1100)/sigma = %.6e m (relative to R_CMB %+.5f) ; ln(1+1089)/sigma = %.6e m (%+.5f)", Rrec, drec, Rrel, drel);
        const double age = sdt::cosmology::age::age_SDT_Gyr;
        tb::note("stored age_SDT_Gyr = %.1f ; ratio to R_CMB/c = %.4f", age, age / t_travel);
        tb::check_true("T4", "R_CMB/c lies in [100.5, 100.9] Gyr", t_travel >= 100.5 && t_travel <= 100.9);
        tb::check_true("T4", "ln(1+z_rec)/sigma differs from R_CMB by a relative amount in [0.005, 0.015]", std::fabs(drec) >= 0.005 && std::fabs(drec) <= 0.015);
        tb::check_true("T4", "ln(1+z_release)/sigma differs from R_CMB by a relative amount in [0.003, 0.012]", std::fabs(drel) >= 0.003 && std::fabs(drel) <= 0.012);
        tb::check_true("T4", "the stored R_CMB equals neither to within 1e-3", std::fabs(drec) > 1e-3 && std::fabs(drel) > 1e-3);
        tb::check_true("T4", "age_SDT_Gyr / (R_CMB/c) lies in [0.45, 0.50]", age / t_travel >= 0.45 && age / t_travel <= 0.50);
    }

    return tb::finish();
}
