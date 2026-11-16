// ============================================================================
// OP02 — Reflection and Fresnel from Relay Impedance
// Author: J. C. Harvey, Melbourne · 2026-07-03
//
// MACHINERY ONLY. No wavefunctions, no field quantisation, no amplitudes-as-
// ontology. Every quantity below is a displacement, an impulse flux, or an
// arrival-time offset of a periodic relay impulse. Phase bookkeeping is done
// with two REAL registers (in-phase / lagged components of arrival time).
//
// HYPOTHESIS UNDER TEST (H1–H3): at a closure step the relay medium is ONE
// lattice with ONE coupling; only c_local (hence n = c/c_local) changes.
// Relay impedance Z = Z0 * n (Z ∝ 1/c_local). Two mechanical continuity
// conditions are imposed at the step:
//   (i)  tangential transverse displacement continuous (lattice does not tear)
//   (ii) tangential relayed impulse-flux continuous (no momentum accumulates
//        on a massless step)
// The solver builds these as a 2x2 linear system per angle and solves it
// numerically. THE TEXTBOOK FRESNEL CLOSED FORMS APPEAR ONLY IN THE
// COMPARISON COLUMN (OBSERVED convergence target), NEVER IN THE SOLVER.
//
// PRE-DECLARED HONESTY FLAGS (RUN_LOG.md; also printed below):
//   * The two continuity rows are generic mechanics of any relaying medium.
//   * WHICH components are matched for the two transverse orientations is
//     asserted, not derived from relay mechanics — the named missing closure.
// ============================================================================

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <numbers>

using namespace sdt::laws;          // engine context; no local constant namespaces
using std::numbers::pi;

static int g_fail = 0;
static void gate(const char* id, bool pass, const char* detail) {
    std::printf("  [%s] %s  %s\n", pass ? "PASS" : "FAIL", id, detail);
    if (!pass) ++g_fail;
}

// --------------------------------------------------------------------------
// The impulse-match solver. Unknowns (r, t) from the two continuity rows.
// Branch 's': transverse displacement entirely tangential to the interface.
//   row 1 (displacement):    1 + r            = t
//   row 2 (impulse flux):    n1*ci*(1 - r)    = n2*ct*t     (flux ∝ Z * projection, Z ∝ n)
// Branch 'p': transverse displacement lies in the plane of incidence.
//   row 1 (displacement):    (1 - r)*ci       = t*ct        (tangential projection)
//   row 2 (impulse flux):    n1*(1 + r)       = n2*t
// Solved by Cramer's rule — no Fresnel closed form anywhere in here.
// --------------------------------------------------------------------------
struct RT { double r, t; };

static RT solve_continuity(char branch, double n1, double n2, double theta_i) {
    const double ci = std::cos(theta_i);
    const double st = n1 * std::sin(theta_i) / n2;        // relay-step continuity along
    const double ct = std::sqrt(1.0 - st * st);           // the interface (Snell, OP01)
    double a11, a12, b1, a21, a22, b2;                    // [a11 a12][r]   [b1]
    if (branch == 's') {                                  // [a21 a22][t] = [b2]
        a11 = 1.0;      a12 = -1.0;       b1 = -1.0;      // 1 + r - t = 0
        a21 = -n1 * ci; a22 = -n2 * ct;   b2 = -n1 * ci;  // n1 ci (1-r) - n2 ct t = 0
    } else {
        a11 = -ci;      a12 = -ct;        b1 = -ci;       // (1-r) ci - t ct = 0
        a21 = n1;       a22 = -n2;        b2 = -n1;       // n1 (1+r) - n2 t = 0
    }
    const double det = a11 * a22 - a12 * a21;
    return { (b1 * a22 - a12 * b2) / det, (a11 * b2 - b1 * a21) / det };
}

// OBSERVED comparison column: the textbook Fresnel amplitudes (targets, not inputs).
static double fresnel_r(char branch, double n1, double n2, double theta_i) {
    const double ci = std::cos(theta_i);
    const double st = n1 * std::sin(theta_i) / n2;
    const double ct = std::sqrt(1.0 - st * st);
    return (branch == 's') ? (n1 * ci - n2 * ct) / (n1 * ci + n2 * ct)
                           : (n2 * ci - n1 * ct) / (n2 * ci + n1 * ct);
}

// Energy bookkeeping from the same relay quantities (H3): R = r^2,
// T = (n2 ct)/(n1 ci) t^2  — the flux weight is the same Z * projection.
static double T_of(double n1, double n2, double theta_i, double t) {
    const double ci = std::cos(theta_i);
    const double st = n1 * std::sin(theta_i) / n2;
    const double ct = std::sqrt(1.0 - st * st);
    return (n2 * ct) / (n1 * ci) * t * t;
}

// Two-register arrival-time bookkeeping for a periodic relay impulse.
// (c,s) = (cos, sin) of the accumulated arrival-time offset x [cycles*2pi].
// Adding two impulse trains = adding registers; delaying = rotating registers.
// This is clock arithmetic on arrival times — nothing more.
struct Reg {
    double c = 0.0, s = 0.0;
    void add(double amp, double x)      { c += amp * std::cos(x); s += amp * std::sin(x); }
    static Reg delayed(Reg a, double x) {                      // rotate by offset x
        return { a.c * std::cos(x) - a.s * std::sin(x), a.c * std::sin(x) + a.s * std::cos(x) };
    }
    double power() const { return c * c + s * s; }             // mean-square displacement rate
};

int main() {
    std::printf("OP02 — Reflection & Fresnel from relay impedance (J. C. Harvey, 2026-07-03)\n");
    std::printf("Machinery only: displacements, impulse fluxes, arrival-time registers.\n");
    std::printf("Media are MEASURED-INPUT descriptors: n1=1.0 (air), n2=1.5 (glass)\n\n");

    const double n_air = 1.0, n_glass = 1.5;

    // ---------------- Phase 1: normal incidence ----------------
    std::printf("Phase 1 — normal-incidence amplitude from impulse continuity\n");
    RT s0 = solve_continuity('s', n_air, n_glass, 0.0);
    const double R0 = s0.r * s0.r;
    std::printf("  air->glass  r = %+.10f   R = %.10f  (committed gate 0.0400 +/- 0.001)\n", s0.r, R0);
    gate("P1-R", std::fabs(R0 - 0.0400) <= 0.001, "glass reflectance");
    gate("P1-sign-hard", s0.r < 0.0, "impulse inverts on the denser-closure step (the 'pi flip')");
    RT s0r = solve_continuity('s', n_glass, n_air, 0.0);
    std::printf("  glass->air  r = %+.10f  (softer closure: no inversion expected)\n", s0r.r);
    gate("P1-sign-soft", s0r.r > 0.0, "no inversion when n2<n1");
    gate("P1-stokes", std::fabs(s0r.r + s0.r) < 1e-14, "reverse-direction r' = -r emerges from the same system (not imposed)");

    // ---------------- Phase 2: oblique s and p, Brewster ----------------
    std::printf("\nPhase 2 — oblique s/p from the transverse-projection split (Law V budget)\n");
    double dev_s = 0.0, dev_p = 0.0;
    for (int i = 0; i <= 899; ++i) {
        const double th = i * 0.1 * pi / 180.0;
        dev_s = std::max(dev_s, std::fabs(solve_continuity('s', n_air, n_glass, th).r - fresnel_r('s', n_air, n_glass, th)));
        dev_p = std::max(dev_p, std::fabs(solve_continuity('p', n_air, n_glass, th).r - fresnel_r('p', n_air, n_glass, th)));
    }
    std::printf("  max |r_solved - r_Fresnel| over 0..89.9 deg:  s: %.3e   p: %.3e\n", dev_s, dev_p);
    gate("P2-s", dev_s < 1e-9, "solved s-branch vs OBSERVED Fresnel column");
    gate("P2-p", dev_p < 1e-9, "solved p-branch vs OBSERVED Fresnel column");

    // Brewster: bisection for the zero of the SOLVED p-branch r (not the formula)
    double lo = 40.0 * pi / 180.0, hi = 70.0 * pi / 180.0;
    for (int i = 0; i < 200; ++i) {
        const double mid = 0.5 * (lo + hi);
        (solve_continuity('p', n_air, n_glass, lo).r * solve_continuity('p', n_air, n_glass, mid).r <= 0.0)
            ? hi = mid : lo = mid;
    }
    const double thB = 0.5 * (lo + hi) * 180.0 / pi;
    const double thB_ref = std::atan(n_glass / n_air) * 180.0 / pi;   // OBSERVED target
    const double rp_at_B = solve_continuity('p', n_air, n_glass, 0.5 * (lo + hi)).r;
    std::printf("  Brewster (root of solved r_p) = %.6f deg   arctan(n2/n1) = %.6f deg   |r_p(thB)| = %.2e\n",
                thB, thB_ref, std::fabs(rp_at_B));
    gate("P2-Brewster", std::fabs(thB - thB_ref) < 0.1 && std::fabs(rp_at_B) < 1e-9, "true zero at arctan(n2/n1)");

    // ---------------- Phase 3: conservation + AR coating ----------------
    std::printf("\nPhase 3 — relay-count conservation and quarter-wave AR by explicit path summation\n");
    double worst = 0.0;
    for (int i = 0; i <= 899; ++i) {
        const double th = i * 0.1 * pi / 180.0;
        for (char b : {'s', 'p'}) {
            RT rt = solve_continuity(b, n_air, n_glass, th);
            worst = std::max(worst, std::fabs(rt.r * rt.r + T_of(n_air, n_glass, th, rt.t) - 1.0));
        }
    }
    std::printf("  max |R+T-1| over all angles, both branches: %.3e  (committed gate 1e-12)\n", worst);
    gate("P3-RT", worst < 1e-12, "impulse-flux ledger closes; nothing external smuggled in");

    // Quarter-wave AR: air | coat(n_c, d = lambda0/(4 n_c)) | glass at 550 nm.
    // Total reflected impulse train built as an EXPLICIT relay-path (multi-bounce)
    // sum with arrival-time registers: each interface coefficient comes from
    // solve_continuity; each internal round trip adds arrival-time offset
    // 2*beta, beta = 2 pi n_c d / lambda. No closed-form thin-film formula.
    const double lambda0 = 550e-9;
    auto R_coat = [&](double nc) {
        const double d    = lambda0 / (4.0 * nc);
        const double beta = 2.0 * pi * nc * d / lambda0;               // = pi/2 at design lambda
        const double r1   = solve_continuity('s', n_air, nc,     0.0).r;
        const double t1   = solve_continuity('s', n_air, nc,     0.0).t;
        const double r2   = solve_continuity('s', nc,    n_glass,0.0).r;
        const double r1b  = solve_continuity('s', nc,    n_air,  0.0).r; // reverse bounce (soft)
        const double t1b  = solve_continuity('s', nc,    n_air,  0.0).t;
        Reg total; total.add(r1, 0.0);                                  // direct bounce
        double amp = t1 * r2 * t1b;                                     // first escape after 1 round trip
        double offset = 2.0 * beta;
        for (int k = 0; k < 400; ++k) {                                 // path-by-path relay sum
            total.add(amp, offset);
            amp    *= r1b * r2;                                         // one more internal round trip
            offset += 2.0 * beta;
        }
        return total.power();
    };
    double best_nc = 0.0, best_R = 1e9;
    for (double nc = 1.01; nc <= 1.49; nc += 0.0005)
        if (double R = R_coat(nc); R < best_R) { best_R = R; best_nc = nc; }
    const double nc_ref = std::sqrt(n_air * n_glass);                   // OBSERVED target sqrt(n1 n2)
    std::printf("  AR minimum (path sum, 400 bounces): n_c = %.4f, R_min = %.3e ;  sqrt(n1*n2) = %.6f\n",
                best_nc, best_R, nc_ref);
    gate("P3-AR", std::fabs(best_nc - nc_ref) / nc_ref < 0.01, "quarter-wave null at sqrt(n1 n2), within 1%");

    // ---------------- Phase 4 ----------------
    std::printf("\nPhase 4 — absorbing metal: DEFER (committed). A lossy-closure model is owed;\n"
                "  importing a conduction model as mechanism is forbidden by the prompt.\n");

    // ---------------- Honesty block ----------------
    std::printf("\nHONESTY FLAGS (pre-declared in RUN_LOG.md):\n"
                "  1. The two continuity rows are generic mechanics of ANY relaying medium (a string\n"
                "     junction obeys the same algebra). SDT's contribution is the identification\n"
                "     Z = Z0*n forced by one-lattice/constant-coupling with variable c_local.\n"
                "     CLASS: CONVERGENCE, not NATIVE.\n"
                "  2. WHICH displacement/impulse components the lattice hands across the step for\n"
                "     the two transverse orientations (the pairing rule) is ASSERTED here, not\n"
                "     derived from relay mechanics. A full lattice treatment would add a\n"
                "     longitudinal branch and more conditions; its suppression is asserted (GOM06\n"
                "     transverse channel), not derived. This is the named missing closure and is\n"
                "     what caps OP02 at CONVERGENCE.\n"
                "  3. Fresnel forms and arctan(n2/n1) were used ONLY as OBSERVED comparison columns.\n");

    std::printf("\nOP02 exit: %s (%d gate failures)\n", g_fail == 0 ? "ALL COMMITTED GATES PASS" : "GATE FAILURES", g_fail);
    return g_fail == 0 ? 0 : 1;
}
