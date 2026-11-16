// Chapter 45 — pressure-origin redshift: worked-example instrument.
// Pre-registration: Textbook/validation/ch45_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
namespace D = sdt::laws::depth_closure;

double zA(double ze, double zo) { return D::z_spectral(ze, zo); }
// Registered convention B in its cancellation-free form: z_B = (z_e - z_o)/(1 - z_e), identical to C_o/C_e - 1.
double zB(double ze, double zo) { return (ze - zo) / D::clock_rate(ze); }
// The product form, kept to report its loss of digits at shallow depth.
double zB_product(double ze, double zo) { return (D::clock_rate(zo) / D::clock_rate(ze)) - 1.0; }

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    tb::check("V1", "A(0.5, 0) = 0.5", zA(0.5, 0.0), 0.5, 1e-14);
    tb::check("V1", "B(0.5, 0) = 1.0", zB(0.5, 0.0), 1.0, 1e-14);
    tb::check("V1", "A(0.2, 0.1) = 0.1", zA(0.2, 0.1), 0.1, 1e-14);
    tb::check("V1", "B(0.2, 0.1) = 0.125", zB(0.2, 0.1), 0.125, 1e-14);
    tb::check("V1", "A(0.3, 0.3) = 0", zA(0.3, 0.3), 0.0, 1e-14, false);
    tb::check("V1", "B(0.3, 0.3) = 0", zB(0.3, 0.3), 0.0, 1e-14, false);
    tb::check("V1", "clock_rate(0.25) = 0.75", D::clock_rate(0.25), 0.75, 1e-14);

    tb::heading("T1 difference between the conventions");
    {
        double worst = 0.0;
        for (double ze : {1e-6, 1e-3, 0.1, 0.3, 0.9})
            for (double zo : {0.0, 0.5 * ze}) {
                const double ratio = zB(ze, zo) / zA(ze, zo);
                worst = std::fmax(worst, std::fabs(ratio * (1.0 - ze) - 1.0));
            }
        tb::check("T1", "z_B / z_A = 1/(1 - z_e) for every (z_e, z_o) in the grid (worst |ratio (1-z_e) - 1|)", worst, 0.0, 1e-12, false);
        const double zs = D::z_spectral_Sun;
        const double rel = zB(zs, 0.0) / zA(zs, 0.0) - 1.0;
        tb::note("solar surface: z_e = %.6e ; relative difference of the conventions %.6e ; absolute difference %.6e", zs, rel, zB(zs, 0.0) - zA(zs, 0.0));
        tb::check("T1", "solar: z_B / z_A = 1/(1 - z_e), i.e. relative difference z_e/(1-z_e)", zB(zs, 0.0) / zA(zs, 0.0), 1.0 / (1.0 - zs), 1e-12);
        tb::note("floating-point floors: subtraction form of the solar relative difference differs from z_e/(1-z_e) by %.3e (relative); product form (C_o/C_e - 1) differs from the difference form by %.3e (relative) at z_e = 1e-6",
                 std::fabs(rel / (zs / (1.0 - zs)) - 1.0), std::fabs(zB_product(1e-6, 0.0) / zB(1e-6, 0.0) - 1.0));
        tb::check_true("T1", "solar relative difference is below 2.2e-6", rel < 2.2e-6);
        const double rel3 = zB(0.3, 0.0) / zA(0.3, 0.0) - 1.0;
        tb::note("z_e = 0.3: relative difference %.4f", rel3);
        tb::check_true("T1", "at z_e = 0.3 the relative difference exceeds 40 per cent", rel3 > 0.40);
    }

    tb::heading("T2 composition across an intermediate state");
    {
        const double a = 0.30, b = 0.12, c = 0.02;
        const double bAB = zB(a, b), bBC = zB(b, c), bAC = zB(a, c);
        const double aAB = zA(a, b), aBC = zA(b, c), aAC = zA(a, c);
        const double mult_B = (1 + bAB) * (1 + bBC) - (1 + bAC);
        const double add_B = bAB + bBC - bAC;
        const double add_A = aAB + aBC - aAC;
        const double mult_A = (1 + aAB) * (1 + aBC) - (1 + aAC);
        tb::note("convention B: multiplicative residual %.3e ; additive residual %.6e", mult_B, add_B);
        tb::note("convention A: additive residual %.3e ; multiplicative residual %.6e (z_AB z_BC = %.6e)", add_A, mult_A, aAB * aBC);
        tb::check("T2", "B: (1+z_AB)(1+z_BC) = 1+z_AC", mult_B, 0.0, 1e-14, false);
        tb::check_true("T2", "B: the additive residual is nonzero", std::fabs(add_B) > 1e-6);
        tb::check("T2", "A: z_AB + z_BC = z_AC", add_A, 0.0, 1e-14, false);
        tb::check("T2", "A: the multiplicative residual equals z_AB z_BC", mult_A, aAB * aBC, 1e-12);
    }

    tb::heading("T3 agreement to first order");
    {
        std::vector<double> s = {1e-3, 1e-2, 1e-1}, rel;
        for (double si : s) {
            const double ze = 0.1 * si, zo = 0.03 * si;
            rel.push_back(zB(ze, zo) / zA(ze, zo) - 1.0);
            tb::check("T3", "z_B - z_A = (z_e - z_o) z_e/(1-z_e), tested as (z_B/z_A)(1-z_e) = 1", (zB(ze, zo) / zA(ze, zo)) * (1.0 - ze), 1.0, 1e-12);
        }
        const double slope = std::log(rel[2] / rel[0]) / std::log(s[2] / s[0]);
        tb::note("relative difference at s = 1e-3, 1e-2, 1e-1: %.4e %.4e %.4e ; log-log slope %.5f", rel[0], rel[1], rel[2], slope);
        tb::check_true("T3", "the log-log slope lies between 0.99 and 1.02", slope >= 0.99 && slope <= 1.02);
    }

    tb::heading("T4 matched emitter-route-observer experiment (solar surface to 1 AU)");
    {
        const double ks = sdt::laws::bridge::koppa_Sun;
        const double ze = ks / M::R_Sun, zo = ks / M::AU;
        tb::note("z_e = %.9e ; z_o = %.9e ; z_e - z_o = %.9e", ze, zo, ze - zo);
        const double Ce = D::clock_rate(ze), Co = D::clock_rate(zo);
        const double fe = 5e14, dt = 1e-9;
        const double N = fe * Ce * dt;
        const double fo = N / (Co * dt);
        tb::check("T4", "count bookkeeping: f_e / f_o = C_o / C_e", fe / fo, Co / Ce, 1e-12);
        tb::check_true("T4", "a deeper emitter gives a positive shift", zB(ze, zo) > 0.0 && zA(ze, zo) > 0.0);
        tb::check_true("T4", "an emitter shallower than the observer gives a negative shift", zB(zo, ze) < 0.0 && zA(zo, ze) < 0.0);
        const double vA = M::c * zA(ze, zo), vB = M::c * zB(ze, zo);
        tb::note("velocity-equivalent shifts: convention A %.6f m/s ; convention B %.6f m/s ; difference %.6e m/s", vA, vB, vB - vA);
        const double dv = vB - vA;
        tb::check_true("T4", "the difference between conventions lies between 1.0e-3 and 2.0e-3 m/s", dv >= 1.0e-3 && dv <= 2.0e-3);
        tb::note("for scale: the difference is %.3e of the shift", dv / vA);
    }

    tb::heading("T5 strong depth");
    {
        bool bounded = true, increasing = true;
        double prev = -1.0;
        for (double ze : {0.1, 0.5, 0.9, 0.99, 0.999}) {
            bounded = bounded && zA(ze, 0.0) <= 1.0;
            const double zb = zB(ze, 0.0);
            increasing = increasing && zb > prev;
            prev = zb;
        }
        tb::check_true("T5", "A stays at or below 1 for z_e <= 1 (z_o = 0)", bounded);
        tb::check_true("T5", "B increases monotonically with z_e", increasing);
        tb::check("T5", "B(0.999, 0) = 999", zB(0.999, 0.0), 999.0, 1e-9);
    }

    return tb::finish();
}
