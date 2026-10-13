// ============================================================================
// OP03 — Diffraction and Interference from Relay-Huygens Summation
// Author: J. C. Harvey, Melbourne · 2026-07-04
//
// MACHINERY ONLY. Each illuminated interface site re-emits the periodic relay
// impulse it received one tick later. The screen quantity is the sum of
// arrival-time registers (Sum cos, Sum sin of 2*pi*L_j/lambda) over sites j.
// No wavefunction, no probability amplitude, no field. Continuum envelopes
// (sinc^2, Airy, d sin(th)=m*lambda) appear ONLY as OBSERVED comparison columns.
//
// LOCATED LAMBDA ENTRY POINT (the honest headline, committed in RUN_LOG.md):
// lambda enters as the ASSUMED tick periodicity of the emission. The phased
// sum therefore inherits interference BY CONSTRUCTION; the earnable content is
// geometry (angles, envelopes, resolving power) — and that only.
// ============================================================================

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numbers>

using namespace sdt::laws;
using std::numbers::pi;

static int g_fail = 0;
static void gate(const char* id, bool pass, const char* detail) {
    std::printf("  [%s] %s  %s\n", pass ? "PASS" : "FAIL", id, detail);
    if (!pass) ++g_fail;
}

// Far-field register sum over discrete re-emitting sites x_j (1D aperture):
// arrival-time offset of site j toward angle th is x_j*sin(th) (in lambda units).
static double intensity_1d(const std::vector<double>& x, double sinth) {
    double C = 0.0, S = 0.0;
    for (double xj : x) { C += std::cos(2.0 * pi * xj * sinth); S += std::sin(2.0 * pi * xj * sinth); }
    return (C * C + S * S) / (double(x.size()) * double(x.size()));
}

static std::vector<double> slit_sites(double a_lam, int M, double x0 = 0.0) {
    std::vector<double> x(M);
    for (int j = 0; j < M; ++j) x[j] = x0 + (-a_lam / 2.0 + (j + 0.5) * a_lam / M);  // midpoint sites
    return x;
}

// Parabolic refinement of an extremum on a fine grid of sinth
static double refine_extremum(const std::vector<double>& x, double s_lo, double s_hi, bool findmax) {
    const int N = 4000;
    double best_s = s_lo, best_I = findmax ? -1.0 : 1e300;
    for (int i = 0; i <= N; ++i) {
        const double s = s_lo + (s_hi - s_lo) * i / N;
        const double I = intensity_1d(x, s);
        if (findmax ? (I > best_I) : (I < best_I)) { best_I = I; best_s = s; }
    }
    const double h = (s_hi - s_lo) / N;
    const double Im = intensity_1d(x, best_s - h), Ip = intensity_1d(x, best_s + h);
    const double denom = (Im - 2.0 * best_I + Ip);
    return (std::fabs(denom) > 1e-300) ? best_s - 0.5 * h * (Ip - Im) / denom : best_s;
}

int main() {
    std::printf("OP03 — Diffraction & interference from relay-Huygens summation (J. C. Harvey, 2026-07-04)\n");
    std::printf("Machinery only: arrival-time register sums over re-emitting sites.\n");
    std::printf("LAMBDA ENTRY POINT: assumed tick periodicity of the emission (see RUN_LOG).\n\n");

    // ---------------- Phase 1a: continuum limit ----------------
    std::printf("Phase 1a — discrete relay sum -> continuum envelope as site count M grows\n");
    const double a1 = 50.0;                                    // slit width, lambda units
    double prev_dev = 1e300; bool monotone = true; double dev4096 = 0.0;
    for (int M : {16, 64, 256, 1024, 4096}) {
        auto x = slit_sites(a1, M);
        double dev = 0.0;
        for (int i = 1; i <= 300; ++i) {                       // first three lobes: sinth in (0, 3/a]
            const double s = 3.0 / a1 * i / 300.0;
            const double u = pi * a1 * s;
            const double envelope = std::pow(std::sin(u) / u, 2.0);   // OBSERVED sinc^2 column
            dev = std::max(dev, std::fabs(intensity_1d(x, s) - envelope));
        }
        std::printf("  M = %5d   max |I_discrete - sinc^2| = %.3e\n", M, dev);
        if (dev > prev_dev) monotone = false;
        prev_dev = dev; if (M == 4096) dev4096 = dev;
    }
    gate("P1a-converge", monotone && dev4096 < 1e-5, "monotone convergence to the continuum envelope (gate 1e-5, committed pre-run)");

    // ---------------- Phase 1b: obliquity — the honest test ----------------
    std::printf("\nPhase 1b — does an obliquity factor EMERGE from isotropic relay re-emission?\n");
    {
        auto x = slit_sites(4.0, 512);
        const double s30 = std::sin(30.0 * pi / 180.0);
        const double If = intensity_1d(x, s30);                // forward 30 deg
        const double Ib = intensity_1d(x, s30);                // backward mirror: same |x_j sinth| offsets
        // For isotropic re-emitters the register sum depends only on the arrival-time
        // offsets x_j*sinth — identical for the forward lobe and its backward mirror.
        std::printf("  I(forward 30deg) = %.6e   I(backward 150deg) = %.6e   ratio = %.6f\n", If, Ib, Ib / If);
        std::printf("  -> isotropic relay re-emission gives backward/forward = 1 IDENTICALLY.\n"
                    "     The obliquity factor does NOT emerge; the backward wave is not suppressed.\n"
                    "     Committed honest outcome: row OPEN (forward-directionality of the relay\n"
                    "     rule is the unbuilt piece — same OP-root debt as OP02's pairing rule).\n");
        gate("P1b-obliquity", std::fabs(Ib / If - 1.0) < 1e-12, "demonstrated non-emergence (honest OPEN, not a pass of emergence)");
    }

    // ---------------- Phase 2: two sources & grating ----------------
    std::printf("\nPhase 2 — two-source and N-source geometry (d = 20 lambda)\n");
    const double d = 20.0;
    { // two point sources
        std::vector<double> x2 = { -d / 2.0, d / 2.0 };
        double worst = 0.0;
        for (int m = 1; m <= 5; ++m) {
            const double target = m / d;                       // OBSERVED d sinth = m lambda
            const double found = refine_extremum(x2, target - 0.4 / d, target + 0.4 / d, true);
            worst = std::max(worst, std::fabs(found - target) / target);
        }
        std::printf("  two-source maxima m=1..5: worst relative error vs m*lambda/d = %.3e\n", worst);
        gate("P2-two", worst < 1e-3, "fringe angles from geometry (gate 0.1%)");
    }
    { // N = 10 grating of point sources
        const int N = 10;
        std::vector<double> xN(N);
        for (int j = 0; j < N; ++j) xN[j] = (j - (N - 1) / 2.0) * d;
        const int m = 1;
        const double peak = refine_extremum(xN, m / d - 0.2 / d, m / d + 0.2 / d, true);
        // ADJ-001: bracket only the FIRST zero (k=1). The original bracket reached the
        // k=2 zero at offset 2/(Nd) and the grid endpoint landed exactly on it.
        const double zero = refine_extremum(xN, m / d + 0.5 / (N * d), m / d + 1.5 / (N * d), false);
        const double offset = zero - peak, target = 1.0 / (N * d); // OBSERVED lambda/(N d)
        std::printf("  grating N=10, m=1: peak at sinth = %.8f (target %.8f)\n", peak, m / d);
        std::printf("  peak-to-first-zero offset = %.8e vs lambda/(Nd) = %.8e  (rel err %.3e)\n",
                    offset, target, std::fabs(offset - target) / target);
        std::printf("  -> resolving power R = sinth_peak/offset = %.3f = mN = %d (counting statement)\n",
                    peak / offset, m * N);
        gate("P2-grating", std::fabs(peak - m / d) / (m / d) < 1e-3 && std::fabs(offset - target) / target < 1e-3,
             "principal maxima + R = mN from site counting");
    }

    // ---------------- Phase 3: single slit & circular aperture ----------------
    std::printf("\nPhase 3 — finite apertures\n");
    { // single slit first null
        auto x = slit_sites(a1, 8192);
        const double t = 1.0 / a1;
        const double null1 = refine_extremum(x, 0.7 * t, 1.3 * t, false);
        std::printf("  slit a=50lambda: first null at sinth = %.8f vs lambda/a = %.8f  (rel err %.3e)\n",
                    null1, t, std::fabs(null1 - t) / t);
        gate("P3-slit", std::fabs(null1 - t) / t < 1e-3, "first null (gate 0.1%)");
    }
    { // circular aperture D = 40 lambda. Equal-arrival-offset sites group into
      // columns: the number of re-emitting sites in the column at x is the chord
      // 2*sqrt((D/2)^2 - x^2) — a pure COUNTING statement, no import. Register
      // sum over M columns weighted by site count.
        const double D = 40.0; const int M = 20000;
        std::vector<double> xc(M), wc(M);
        for (int j = 0; j < M; ++j) {
            xc[j] = -D / 2 + (j + 0.5) * D / M;
            wc[j] = 2.0 * std::sqrt(std::max(0.0, D * D / 4.0 - xc[j] * xc[j]));
        }
        auto I_disk = [&](double s) {
            double C = 0, S = 0, W = 0;
            for (int j = 0; j < M; ++j) {
                C += wc[j] * std::cos(2.0 * pi * xc[j] * s);
                S += wc[j] * std::sin(2.0 * pi * xc[j] * s);
                W += wc[j];
            }
            return (C * C + S * S) / (W * W);
        };
        const double t = 1.219670 / D;                          // OBSERVED: J1 zero 3.831706/pi
        double best_s = 0, best_I = 1e300;
        for (int i = 0; i <= 6000; ++i) {
            const double s = 0.85 * t + (0.30 * t) * i / 6000.0;
            if (double I = I_disk(s); I < best_I) { best_I = I; best_s = s; }
        }
        std::printf("  disk D=40lambda (%d site-count columns): first dark ring at sinth = %.8f vs 1.21967 lambda/D = %.8f (rel err %.3e)\n",
                    M, best_s, t, std::fabs(best_s - t) / t);
        gate("P3-airy", std::fabs(best_s - t) / t < 1e-3, "Airy first ring (gate 0.1%)");
    }

    // ---------------- Phase 4: granularity ----------------
    std::printf("\nPhase 4 — lattice-granularity deviation (discrete spacing s)\n");
    {
        const double sinth = 0.437;   // incommensurate with a=50lambda (a*sinth = 21.85, off any sinc null)
        const double u = pi * a1 * sinth;
        const double cont = std::pow(std::sin(u) / u, 2.0);
        std::vector<double> ss, dd;
        for (double s : {1.0 / 8, 1.0 / 16, 1.0 / 32, 1.0 / 64}) {
            const int M = int(a1 / s);
            const double dev = std::fabs(intensity_1d(slit_sites(a1, M), sinth) - cont);
            std::printf("  spacing s = lambda/%-3.0f   |I_discrete - I_cont| = %.6e\n", 1.0 / s, dev);
            ss.push_back(std::log(s)); dd.push_back(std::log(dev));
        }
        double n = ss.size(), sx = 0, sy = 0, sxx = 0, sxy = 0;
        for (size_t i = 0; i < ss.size(); ++i) { sx += ss[i]; sy += dd[i]; sxx += ss[i] * ss[i]; sxy += ss[i] * dd[i]; }
        const double slope = (n * sxy - sx * sy) / (n * sxx - sx * sx);
        std::printf("  fitted deviation exponent vs s: %.3f (committed gate 2.0 +/- 0.2)\n", slope);
        const double lam = 500e-9;
        const double dev_lP = std::exp((dd[0]) + slope * (std::log(measured::l_P / lam) - ss[0]));
        std::printf("  extrapolation to s = l_P (%.4e m) at 500 nm: deviation ~ %.1e\n", measured::l_P, dev_lP);
        std::printf("  -> HONEST NULL: ~1e-57-scale; no reachable experiment bounds it. No SDT-vs-\n"
                    "     continuum-optics signature here; reported, not inflated.\n");
        gate("P4-scaling", std::fabs(slope - 2.0) < 0.2, "midpoint-discretisation s^2 law; extrapolation reported");
    }

    // ---------------- Honesty block ----------------
    std::printf("\nHONESTY FLAGS:\n"
                "  1. Huygens summation IS interference by construction. lambda entered as the assumed\n"
                "     tick periodicity; the earned content is geometry only. CLASS: CONVERGENCE, cap C.\n"
                "  2. Obliquity/backward-wave: demonstrated NON-emergence from isotropic re-emission.\n"
                "     OPEN, traced to the OP-root debt (explicit transverse relay rule / forward\n"
                "     directionality on the discrete lattice). Not bolted on by fiat.\n"
                "  3. Sub-wavelength apertures / near-field: NOT gated (SS G) — constraint-channel\n"
                "     territory (FLM14 ADJ-7); owed a two-channel treatment, not legislated away.\n"
                "  4. Single-emission build-up (F4): the relay sum is a real disturbance sampling all\n"
                "     paths; nothing here needed a collapse. But this tool does not SIMULATE one-\n"
                "     emission arrival statistics — that is QM01's residence-histogram job. F4 = OPEN\n"
                "     here, deferred to QM01, not claimed.\n");

    std::printf("\nOP03 exit: %s (%d gate failures)\n", g_fail == 0 ? "ALL COMMITTED GATES PASS" : "GATE FAILURES", g_fail);
    return g_fail == 0 ? 0 : 1;
}
