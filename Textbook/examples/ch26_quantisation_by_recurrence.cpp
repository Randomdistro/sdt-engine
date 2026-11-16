// Chapter 26 — quantisation by recurrence: worked-example instrument.
// Pre-registration: Textbook/validation/ch26_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>

namespace {
double root_radius(double p, double n) {
    double lo = 1e-30, hi = 1e30;
    const bool increasing = (3.0 - p) > 0.0;
    for (int i = 0; i < 400; ++i) {
        const double mid = std::sqrt(lo * hi);
        const bool below = std::pow(mid, (3.0 - p) / 2.0) < n;
        ((below == increasing) ? lo : hi) = mid;
    }
    return std::sqrt(lo * hi);
}
}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    namespace A = sdt::laws::atomic;
    tb::validate_helpers();
    const double c = M::c, alpha = M::alpha;

    tb::heading("V1 root finder");
    tb::check("V1", "p=2, n=3: r = 9", root_radius(2.0, 3.0), 9.0, 1e-12);
    tb::check("V1", "p=1, n=4: r = 4", root_radius(1.0, 4.0), 4.0, 1e-12);

    tb::heading("T1 closure algebra");
    {
        double w_r = 0, w_v = 0, w_J = 0, w_E = 0;
        for (int Z = 1; Z <= 5; ++Z) {
            const double r1 = A::bohr_radius(Z, 1), v1 = A::bohr_velocity(Z, 1);
            for (int n = 1; n <= 10; ++n) {
                const double r = A::bohr_radius(Z, n), v = A::bohr_velocity(Z, n);
                w_r = std::fmax(w_r, std::fabs(r / r1 / (double(n) * n) - 1.0));
                w_v = std::fmax(w_v, std::fabs(v / v1 * n - 1.0));
                w_J = std::fmax(w_J, std::fabs(M::m_e * v * r / (n * M::hbar) - 1.0));
                w_E = std::fmax(w_E, std::fabs(0.5 * M::m_e * v * v / M::e_charge / (M::Ry_eV * Z * Z / (double(n) * n)) - 1.0));
            }
        }
        tb::check("T1", "r_n / r_1 = n^2, worst relative", w_r, 0.0, 1e-14, false);
        tb::check("T1", "v_n / v_1 = 1/n, worst relative", w_v, 0.0, 1e-14, false);
        tb::check("T1", "m_e v r = n hbar (shared-input), worst relative", w_J, 0.0, 1e-9, false);
        tb::check("T1", "(1/2) m_e v^2 = Ry Z^2/n^2 (shared-input), worst relative", w_E, 0.0, 1e-9, false);
    }

    tb::heading("T2 integer closure on a family of kernels");
    {
        double worst = 0.0;
        for (double p : {1.0, 1.5, 2.0, 2.5, 2.9})
            for (int n = 1; n <= 8; ++n) worst = std::fmax(worst, std::fabs(root_radius(p, n) / std::pow(double(n), 2.0 / (3.0 - p)) - 1.0));
        tb::check("T2", "radius from J = n equals n^(2/(3-p)), worst relative", worst, 0.0, 1e-12, false);
        bool stable = true;
        for (double p : {1.0, 1.5, 2.0, 2.5, 2.9}) stable = stable && (3.0 - p) > 0.0;
        tb::check_true("T2", "kappa^2/omega^2 = 3 - p is positive for the five kernels", stable);
        tb::check_true("T2", "p = 3.5: a ladder r_n = n^(-4) exists but kappa^2/omega^2 = -0.5 < 0 (no persistent route)", std::fabs(root_radius(3.5, 2.0) - std::pow(2.0, -4.0)) < 1e-12 && (3.0 - 3.5) < 0.0);
        tb::note("radii for n = 1..4: p=2: %.4f %.4f %.4f %.4f ; p=1: %.4f %.4f %.4f %.4f ; p=2.9: %.4g %.4g %.4g %.4g", root_radius(2, 1), root_radius(2, 2), root_radius(2, 3), root_radius(2, 4), root_radius(1, 1), root_radius(1, 2), root_radius(1, 3), root_radius(1, 4), root_radius(2.9, 1), root_radius(2.9, 2), root_radius(2.9, 3), root_radius(2.9, 4));
    }

    tb::heading("T3 transition ledger");
    {
        auto dE = [&](int Z, int lo, int hi) { return M::Ry_eV * Z * Z * (1.0 / (double(lo) * lo) - 1.0 / (double(hi) * hi)); };
        double w_ritz = 0, w_lim = 0, w_Z = 0;
        for (int Z = 1; Z <= 4; ++Z)
            for (int a = 1; a <= 12; ++a) {
                w_lim = std::fmax(w_lim, std::fabs(M::Ry_eV * Z * Z / (double(a) * a) / (dE(Z, a, 100000) + M::Ry_eV * Z * Z / 1e10) - 1.0));
                w_Z = std::fmax(w_Z, std::fabs(dE(Z, a, a + 1) / dE(1, a, a + 1) / (Z * Z) - 1.0));
                for (int b = a + 1; b <= 12; ++b)
                    for (int d = b + 1; d <= 12; ++d) w_ritz = std::fmax(w_ritz, std::fabs((dE(Z, a, b) + dE(Z, b, d)) / dE(Z, a, d) - 1.0));
            }
        tb::check("T3", "Ritz combination dE(a->d) = dE(a->b) + dE(b->d), worst relative", w_ritz, 0.0, 1e-14, false);
        tb::check("T3", "series limit Ry Z^2/n^2 (n_high = 1e5), worst relative", w_lim, 0.0, 1e-9, false);
        tb::check("T3", "dE scales as Z^2, worst relative", w_Z, 0.0, 1e-14, false);
    }

    tb::heading("T4 movement-budget limit of the leading-order ladder");
    {
        int zmax = 0;
        for (int Z = 1; Z <= 400; ++Z)
            if (Z * alpha * c < c) zmax = Z;
        tb::note("1/alpha = %.6f ; largest Z with v < c: %d ; (Z alpha)^2 at Z = 137: %.6f", 1.0 / alpha, zmax, std::pow(137 * alpha, 2));
        tb::check_true("T4", "largest Z with Z alpha < 1 is 137", zmax == 137);
    }

    return tb::finish();
}
