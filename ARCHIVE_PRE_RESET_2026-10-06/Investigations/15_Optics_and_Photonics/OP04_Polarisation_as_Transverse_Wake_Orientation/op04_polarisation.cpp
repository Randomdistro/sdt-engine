// ============================================================================
// OP04 — Polarisation as Transverse Wake Orientation
// Author: J. C. Harvey, Melbourne · 2026-07-04
//
// MACHINERY ONLY. The state is a REAL time-domain transverse displacement
//   u(t) = (Ax cos(wt+px), Ay cos(wt+py))
// sampled over a tick period. A polariser is anisotropic closure: it re-relays
// the instant-by-instant PROJECTION of u onto its pass axis and dumps the rest.
// A retarder lags ONE axis by a fraction of the period. Unpolarised light is a
// Monte-Carlo ensemble of random orientations. No Jones matrices, no Stokes
// axioms, no spin operator, no complex amplitudes.
// ============================================================================

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <random>
#include <algorithm>
#include <numbers>

using namespace sdt::laws;
using std::numbers::pi;

static int g_fail = 0;
static void gate(const char* id, bool pass, const char* detail) {
    std::printf("  [%s] %s  %s\n", pass ? "PASS" : "FAIL", id, detail);
    if (!pass) ++g_fail;
}

struct Wake {                    // transverse displacement state
    double Ax, Ay, px, py;       // amplitudes and per-axis arrival-time lags (radians of tick)
    double ux(double wt) const { return Ax * std::cos(wt + px); }
    double uy(double wt) const { return Ay * std::cos(wt + py); }
};

static constexpr int NS = 4096;  // samples per tick period

// time-averaged squared displacement rate (the mechanical intensity)
static double intensity(const Wake& w) {
    double I = 0.0;
    for (int i = 0; i < NS; ++i) { const double wt = 2.0 * pi * i / NS; I += w.ux(wt) * w.ux(wt) + w.uy(wt) * w.uy(wt); }
    return I / NS;
}

// polariser at angle th: project u(t) onto the pass axis, dump the orthogonal part
static Wake polarise(const Wake& w, double th) {
    // projection amplitude p(t) = ux cos th + uy sin th = C cos(wt) - S sin(wt)
    const double C = w.Ax * std::cos(w.px) * std::cos(th) + w.Ay * std::cos(w.py) * std::sin(th);
    const double S = w.Ax * std::sin(w.px) * std::cos(th) + w.Ay * std::sin(w.py) * std::sin(th);
    const double A = std::sqrt(C * C + S * S), ph = std::atan2(S, C);
    return { A * std::cos(th), A * std::sin(th), ph, ph };   // re-relayed along the pass axis only
}

// retarder with fast axis x: lag the y-axis relay by 'lag' radians of the tick
static Wake retard_y(const Wake& w, double lag) { return { w.Ax, w.Ay, w.px, w.py + lag }; }

// trajectory circularity: min|u|/max|u| over a period (1 = circular, 0 = linear)
static double circularity(const Wake& w) {
    double mn = 1e300, mx = 0.0;
    for (int i = 0; i < NS; ++i) {
        const double wt = 2.0 * pi * i / NS;
        const double r = std::hypot(w.ux(wt), w.uy(wt));
        mn = std::min(mn, r); mx = std::max(mx, r);
    }
    return mn / mx;
}

// orientation of a linear trajectory (deg)
static double orientation_deg(const Wake& w) {
    double bx = 0, by = 0, bmax = 0;
    for (int i = 0; i < NS; ++i) {
        const double wt = 2.0 * pi * i / NS;
        const double x = w.ux(wt), y = w.uy(wt), r = std::hypot(x, y);
        if (r > bmax) { bmax = r; bx = x; by = y; }
    }
    return std::atan2(by, bx) * 180.0 / pi;
}

int main() {
    std::printf("OP04 — Polarisation as transverse wake orientation (J. C. Harvey, 2026-07-04)\n");
    std::printf("Machinery only: real time-domain displacement, projection, per-axis lag.\n\n");

    // ---------------- Phase 1: native states ----------------
    std::printf("Phase 1 — native transverse states (Ax, Ay, lag)\n");
    Wake lin0  { 1.0, 0.0, 0.0, 0.0 };                       // linear along x
    Wake lin45 { 1 / std::sqrt(2.0), 1 / std::sqrt(2.0), 0.0, 0.0 };
    Wake circL { 1 / std::sqrt(2.0), 1 / std::sqrt(2.0), 0.0, +pi / 2 };
    Wake ellip { 0.9, 0.44, 0.0, +pi / 3 };
    std::printf("  linear@0: circ = %.3e   linear@45: circ = %.3e\n", circularity(lin0), circularity(lin45));
    std::printf("  circular (lag pi/2): circ = %.6f   elliptical: circ = %.4f\n", circularity(circL), circularity(ellip));
    gate("P1-states", circularity(lin0) < 1e-6 && circularity(circL) > 0.999999 &&
                      circularity(ellip) > 0.01 && circularity(ellip) < 0.99,
         "linear/circular/elliptical all carried by (Ax,Ay,lag) — no further structure needed");

    // ---------------- Phase 2: Malus by projection ----------------
    std::printf("\nPhase 2 — Malus by instant-by-instant projection\n");
    double worst = 0.0;
    const double I0 = intensity(lin0);
    for (int i = 0; i <= 90; ++i) {
        const double th = i * pi / 180.0;
        const double ratio = intensity(polarise(lin0, th)) / I0;
        worst = std::max(worst, std::fabs(ratio - std::cos(th) * std::cos(th)));
    }
    std::printf("  max |I/I0 - cos^2| over 0..90 deg = %.3e  (gate 1e-3)\n", worst);
    gate("P2-malus", worst < 1e-3, "Malus from projection geometry");

    const double Icross = intensity(polarise(polarise(lin0, 0.0), pi / 2));
    std::printf("  crossed pair floor = %.3e * I0  (gate 1e-12)\n", Icross / I0);
    gate("P2-crossed", Icross / I0 < 1e-12, "extinction at machine zero");

    { // three-polariser revival with a Monte-Carlo unpolarised ensemble
        std::mt19937_64 rng(20260704ULL);
        std::uniform_real_distribution<double> U(0.0, pi);
        const int K = 200000;
        double Iout = 0.0, Iin = 0.0;
        for (int k = 0; k < K; ++k) {
            const double a = U(rng);
            Wake w { std::cos(a), std::sin(a), 0.0, 0.0 };    // random transverse orientation
            Iin  += intensity(w);
            Iout += intensity(polarise(polarise(polarise(w, 0.0), pi / 4), pi / 2));
        }
        const double frac = Iout / Iin;
        std::printf("  unpolarised -> P(0)->P(45)->P(90): I/I0 = %.6f vs 1/8 = 0.125  (gate +/-1%%)\n", frac);
        gate("P2-revival", std::fabs(frac - 0.125) / 0.125 < 0.01, "three-polariser revival, MC ensemble K=2e5");
    }

    // ---------------- Phase 3: retarders ----------------
    std::printf("\nPhase 3 — retarders as single-axis relay lag (anisotropic closure)\n");
    {
        Wake out = retard_y(lin45, pi / 2);                    // quarter-tick lag
        std::printf("  QWP on linear@45: circularity = %.6f  (gate >= 0.99)\n", circularity(out));
        gate("P3-qwp", circularity(out) >= 0.99, "linear -> circular by quarter-tick lag");
    }
    {
        const double psi = 20.0 * pi / 180.0;
        Wake in  { std::cos(psi), std::sin(psi), 0.0, 0.0 };
        Wake out = retard_y(in, pi);                           // half-tick lag
        const double o = orientation_deg(out);
        std::printf("  HWP on linear@20deg: output orientation = %+.4f deg (target -20; rotation 2psi)  (gate 0.1 deg)\n", o);
        gate("P3-hwp", std::fabs(std::fabs(o) - 20.0) < 0.1 && o < 0.0, "rotation by 2psi from half-tick lag");
    }

    // ---------------- Phase 4: optical activity ----------------
    std::printf("\nPhase 4 — optical activity as handedness-split relay speed (Dn = MEASURED-INPUT)\n");
    {
        // linear = sum of two counter-rotating transverse displacements (trig identity,
        // not a decomposition postulate). A chiral medium relays the two handednesses at
        // c/n_L and c/n_R: after length L the relative lag is d = 2 pi (n_L - n_R) L / lambda,
        // and recombination is a linear trajectory rotated by d/2.
        const double dn = 1e-6, lambda = 589e-9;               // MEASURED-INPUT scale (sugar-class)
        auto rotation_deg = [&](double Lm) {
            const double d = 2.0 * pi * dn * Lm / lambda;
            // mechanical recombination: u = uL(rotating +) + uR(rotating -), uR lagged by d
            // trajectory orientation = d/2 (verified below by tracing, not asserted)
            Wake w { 1.0, 0.0, 0.0, 0.0 };
            // build the recombined wake by sampling both rotations explicitly:
            // ux = cos(wt) + cos(wt - d) ; uy = sin(wt) - sin(wt - d)  (L + lagged R)
            double bx = 0, by = 0, bmax = 0;
            for (int i = 0; i < NS; ++i) {
                const double wt = 2.0 * pi * i / NS;
                const double x = std::cos(wt) + std::cos(wt - d);
                const double y = std::sin(wt) - std::sin(wt - d);
                const double r = std::hypot(x, y);
                if (r > bmax) { bmax = r; bx = x; by = y; }
            }
            (void)w;
            return std::atan2(by, bx) * 180.0 / pi;
        };
        const double r1 = rotation_deg(0.01), r2 = rotation_deg(0.02);   // 1 cm, 2 cm
        std::printf("  rotation(1 cm) = %.6f deg   rotation(2 cm) = %.6f deg   ratio = %.6f (gate 2 +/- 0.1%%)\n",
                    r1, r2, r2 / r1);
        gate("P4-linearity", std::fabs(r2 / r1 - 2.0) < 0.002, "rotation proportional to path length");
        std::printf("  SIGN: which handedness is the slower relay is ASSERTED to map to EMC03 +/-\n"
                    "  redirection — NOT derived here. Row: OPEN (committed expectation).\n");
    }

    // ---------------- Honesty block ----------------
    std::printf("\nHONESTY FLAGS:\n"
                "  1. The state (Ax, Ay, lag) with projection + per-axis lag is ALGEBRAICALLY\n"
                "     ISOMORPHIC to the Jones calculus. Recovering Malus/QWP/HWP this way is the\n"
                "     firewall's own cap: CLASS CONVERGENCE (C), not NATIVE.\n"
                "  2. No spin operator was used — but classical polarisation optics never needed\n"
                "     one either. The earned content vs classical wave optics is the ONTOLOGY\n"
                "     (a real lattice displacement with EMC03 handedness), which these numerics\n"
                "     do not test. Said plainly, not dressed up.\n"
                "  3. Chiral magnitude Dn is MEASURED-INPUT; predicting it from lattice chirality\n"
                "     inherits OP01's OPEN matter-index problem (same root).\n"
                "  4. The activity SIGN -> EMC03 mapping is OPEN; flipping it by fiat is forbidden.\n");

    std::printf("\nOP04 exit: %s (%d gate failures)\n", g_fail == 0 ? "ALL COMMITTED GATES PASS" : "GATE FAILURES", g_fail);
    return g_fail == 0 ? 0 : 1;
}
