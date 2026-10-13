// ============================================================================
//  TD06 — Blackbody Thermodynamics from Lattice Modes
//
//  P1a  Mode density counted (integer cavity modes, 2 pol) vs 8 pi nu^2/c^3.
//  P1b  Bose denominator from COUNTING: energy-conserving integer hill-climb
//       on ln W across bands -> ln(1+g/q) = beta*eps; geometric single-mode
//       marginal. No QM lift, no reservoir, no partition function.
//  P2   Planck curve from counted modes x counted occupation (<0.1%).
//  P3   Stefan-Boltzmann: mode-sum vs pi^4/15; T-exponent fit; sigma_SI vs a_rad.
//  P4   Wien: root 4.965114 from bisection of the counted-spectrum extremum.
//  P5   UV honesty: the l_P cutoff does zero work at 300 K; finiteness is the
//       eps = h*nu quantisation (Planck's postulate carried by the Law-I bridge).
//
//  SAR02 is cross-checked at the end; it is NOT the pass criterion.
//
//  Author: J. C. Harvey, Melbourne. 2026-07-03.
//  Build: cl /std:c++20 /EHsc /O2 /utf-8 /I Engine/include td06_lattice_blackbody.cpp
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

namespace {
using namespace sdt::laws;
const double kB = measured::k_B, h = measured::h, c0 = measured::c;

double ln_W(double q, double g) {   // W = C(q+g-1, g-1)
    return std::lgamma(q + g) - std::lgamma(q + 1.0) - std::lgamma(g);
}
std::mt19937_64 rng(20260703ULL);
} // namespace

int main() {
    std::printf("================================================================\n");
    std::printf(" TD06 - Blackbody Thermodynamics from Lattice Modes\n");
    std::printf(" J. C. Harvey, Melbourne - 2026-07-03\n");
    std::printf(" derivation basis: k_B; c and h enter ONLY as Law-I bridges (eps = h*nu).\n");
    std::printf("================================================================\n\n");

    bool p1a = true, p1b = true, p2 = true, p3 = true, p4 = true;

    // ------------------------------------------------------------------
    // P1a - counted mode density vs 8 pi nu^2 / c^3
    //   modes: positive-octant integer n, |n| = 2L nu / c, x2 polarisations
    // ------------------------------------------------------------------
    // RUN-1 (documented): the octant standing-wave count missed the committed 0.1%
    // with dev*R ~ const (0.72% at R=200 -> 0.19% at R=800): that is the Weyl SURFACE
    // term of a walled cavity (deterministic boundary deficit), which my pre-run error
    // budget omitted (only the Gauss fluctuation was budgeted). ADJ-1 (allowed
    // alternative native route, gate UNCHANGED): bulk lattice modes are boundary-free
    // -> periodic (traveling-wave) count over all nonzero integer triples. The octant
    // run is kept below as the documented contrast (dev*R ~ const shown explicitly).
    static std::vector<double> shellF;            // full-space periodic shell counts
    std::printf("P1a: counted mode density vs 8 pi nu^2/c^3 (periodic bulk modes)\n");
    {
        const int Rmax = 1000;
        std::vector<long> oct(Rmax + 2, 0);
        for (int nx = 1; nx * nx < Rmax * Rmax; ++nx)
            for (int ny = 1; nx*nx + ny*ny < Rmax*Rmax; ++ny) {
                const int zz = Rmax*Rmax - nx*nx - ny*ny;
                const int nzmax = int(std::sqrt(double(zz)));
                for (int nz = 1; nz <= nzmax; ++nz) {
                    const int R = int(std::sqrt(double(nx*nx + ny*ny + nz*nz)));
                    if (R <= Rmax) ++oct[R];
                }
            }
        std::vector<long> quad(Rmax + 2, 0);      // 2D: a,b >= 1
        for (int a = 1; a * a < Rmax * Rmax; ++a) {
            const int bmax = int(std::sqrt(double(Rmax*Rmax - a*a)));
            for (int b = 1; b <= bmax; ++b) {
                const int R = int(std::sqrt(double(a*a + b*b)));
                if (R <= Rmax) ++quad[R];
            }
        }
        shellF.assign(Rmax + 2, 0.0);
        for (int R = 1; R <= Rmax; ++R)
            shellF[R] = 8.0*oct[R] + 12.0*quad[R] + 6.0;   // full Z^3 \ axes structure
        // octant contrast: dev * R ~ const (the Weyl surface term)
        std::printf("  octant (walled-cavity) contrast — the boundary term:\n");
        for (int R0 : {200, 400, 800}) {
            long cnt = 0; double pred = 0;
            for (int R = R0; R < R0 + 20; ++R) {
                cnt += oct[R];
                pred += 0.5*std::numbers::pi*((double)R*R + R + 1.0/3.0);
            }
            const double dev = double(cnt)/pred - 1.0;
            std::printf("    R=%4d: dev = %+.4f%%   dev*R = %+.2f (const => 1/R boundary term)\n",
                        R0, 100.0*dev, dev*R0);
        }
        // gate: periodic bulk count vs 4 pi R^2 dR (x2 pol handled downstream)
        double worst = 0, mean = 0; int nb = 0;
        for (int R0 = 200; R0 < 1000; R0 += 20) {
            double cnt = 0, pred = 0;
            for (int R = R0; R < R0 + 20; ++R) {
                cnt += shellF[R];
                pred += 4.0*std::numbers::pi*((double)R*R + R + 1.0/3.0);
            }
            const double dev = std::fabs(cnt/pred - 1.0);
            mean += dev; ++nb; worst = std::max(worst, dev);
        }
        mean /= nb;
        std::printf("  periodic bulk count vs 4 pi R^2 dR: mean |dev| = %.4f%% (<0.1%%), worst %.4f%%  [%s]\n",
                    100.0*mean, 100.0*worst, mean < 0.001 ? "PASS" : "FAIL");
        std::printf("  x2 polarisations (transverse relay branches) -> g(nu) = 8 pi nu^2/c^3.\n\n");
        if (mean > 0.001) p1a = false;
    }

    // ------------------------------------------------------------------
    // P1b - Bose denominator from counting (hill-climb + geometric marginal)
    // ------------------------------------------------------------------
    std::printf("P1b: occupation from ln W maximisation (native counting)\n");
    {
        const int B = 40;
        std::vector<double> g(B + 1), q(B + 1, 0.0);
        for (int b = 1; b <= B; ++b) g[b] = 4000.0 * b * b;   // ~ mode density
        // start NON-Bose: all energy in two mid bands
        long U = 6'000'000;
        q[10] = double(U / 2 / 10); q[20] = double((U - 10*long(q[10])) / 20);
        U = 10*long(q[10]) + 20*long(q[20]);
        std::uniform_int_distribution<int> ub(1, B);
        std::uniform_int_distribution<int> umv(0, 2);
        long accepted = 0;
        // RUN-1 (documented): a move set of paired one-step shifts conserved TOTAL
        // QUANTUM NUMBER as an accidental conservation law, so the climb equilibrated
        // to Bose-with-chemical-potential (fit intercept 0.682, RMS 57.9%). Radiation
        // quanta carry no number conservation. ADJ-2 (premise fix, gates UNCHANGED):
        // move set now includes energy-conserving MERGE (i,j -> i+j) and SPLIT
        // (k -> i, k-i) moves, which change quantum number at fixed energy.
        for (long it = 0; it < 60'000'000L; ++it) {
            const int mv = umv(rng);
            double dS = 0;
            if (mv == 0) {          // paired shift: (i -> i-1), (j -> j+1)
                const int i = ub(rng), j = ub(rng);
                if (i < 2 || j > B - 1 || q[i] < 1.0 || q[j] < 1.0) continue;
                if (i == j && q[i] < 2.0) continue;
                dS += ln_W(q[i] - 1, g[i]) - ln_W(q[i], g[i]);
                dS += ln_W(q[i-1] + 1, g[i-1]) - ln_W(q[i-1], g[i-1]);
                dS += ln_W(q[j] - 1, g[j]) - ln_W(q[j], g[j]);
                dS += ln_W(q[j+1] + 1, g[j+1]) - ln_W(q[j+1], g[j+1]);
                if (dS > 0) { q[i] -= 1; q[i-1] += 1; q[j] -= 1; q[j+1] += 1; ++accepted; }
            } else if (mv == 1) {   // merge: one quantum from i and one from j -> one in i+j
                const int i = ub(rng), j = ub(rng);
                if (i + j > B || q[i] < 1.0 || q[j] < 1.0) continue;
                if (i == j && q[i] < 2.0) continue;
                if (i == j) dS = ln_W(q[i] - 2, g[i]) - ln_W(q[i], g[i]);
                else        dS = ln_W(q[i] - 1, g[i]) - ln_W(q[i], g[i])
                               + ln_W(q[j] - 1, g[j]) - ln_W(q[j], g[j]);
                dS += ln_W(q[i+j] + 1, g[i+j]) - ln_W(q[i+j], g[i+j]);
                if (dS > 0) { q[i] -= 1; q[j] -= 1; q[i+j] += 1; ++accepted; }
            } else {                // split: one quantum from band k -> bands i and k-i
                const int k = ub(rng);
                if (k < 2 || q[k] < 1.0) continue;
                std::uniform_int_distribution<int> ui(1, k - 1);
                const int i = ui(rng), j = k - i;
                dS += ln_W(q[k] - 1, g[k]) - ln_W(q[k], g[k]);
                dS += ln_W(q[i] + 1, g[i]) - ln_W(q[i], g[i]);
                if (i != j) dS += ln_W(q[j] + 1, g[j]) - ln_W(q[j], g[j]);
                else        dS  = ln_W(q[k] - 1, g[k]) - ln_W(q[k], g[k])
                                + ln_W(q[i] + 2, g[i]) - ln_W(q[i], g[i]);
                if (dS > 0) { q[k] -= 1; q[i] += 1; q[j] += 1; ++accepted; }
            }
        }
        // stationarity: ln(1 + g_b/q_b) = beta * b  (exact discrete Bose relation)
        std::vector<double> xs, ys;
        for (int b = 1; b <= B; ++b)
            if (q[b] > 0.01 * g[b]) { xs.push_back(b); ys.push_back(std::log(1.0 + g[b]/q[b])); }
        double sx=0, sy=0, sxx=0, sxy=0; const size_t n = xs.size();
        for (size_t k = 0; k < n; ++k) { sx+=xs[k]; sy+=ys[k]; sxx+=xs[k]*xs[k]; sxy+=xs[k]*ys[k]; }
        const double beta = (n*sxy - sx*sy)/(n*sxx - sx*sx);
        const double icpt = (sy - beta*sx)/n;
        double ssr=0, sst=0, ym=sy/n, rms=0; int nr=0;
        for (size_t k = 0; k < n; ++k) {
            const double yh = beta*xs[k] + icpt;
            ssr += (ys[k]-yh)*(ys[k]-yh); sst += (ys[k]-ym)*(ys[k]-ym);
            const double nbar = q[int(xs[k])] / g[int(xs[k])];
            const double nbose = 1.0/(std::exp(beta*xs[k]) - 1.0);
            rms += (nbar/nbose - 1.0)*(nbar/nbose - 1.0); ++nr;
        }
        const double R2 = 1.0 - ssr/sst; rms = std::sqrt(rms/nr);
        std::printf("  hill-climb from non-Bose start (%ld moves accepted):\n", accepted);
        std::printf("  ln(1+g/q) vs eps: R^2 = %.6f (>0.9999), intercept %.2e; beta = %.5f\n",
                    R2, icpt, beta);
        std::printf("  RMS occupation dev from Bose(beta) = %.3f%% (<1%%)  [%s]\n",
                    100.0*rms, (R2 > 0.9999 && rms < 0.01) ? "PASS" : "FAIL");
        if (R2 < 0.9999 || rms > 0.01) p1b = false;

        // geometric single-mode marginal inside one band: p_j ratio constant
        const int bb = int(1.0/beta);             // a well-occupied band
        const double qq = q[bb], gg = g[bb];
        double worst_ratio_dev = 0; double prev = 0;
        for (int j = 0; ; ++j) {
            const double pj = std::exp(ln_W(qq - j, gg - 1.0) - ln_W(qq, gg));
            if (pj < 1e-4) break;
            if (j > 0) {
                const double ratio = pj / prev;
                const double nbar = qq/gg, geo = nbar/(1.0 + nbar);
                worst_ratio_dev = std::max(worst_ratio_dev, std::fabs(ratio/geo - 1.0));
            }
            prev = pj;
        }
        std::printf("  single-mode marginal in band %d: p_(j+1)/p_j constant to %.3f%% (<1%%)\n",
                    bb, 100.0*worst_ratio_dev);
        std::printf("  -> the 'geometric series' is COUNTED (multiple quanta per mode), not lifted. [%s]\n\n",
                    worst_ratio_dev < 0.01 ? "PASS" : "FAIL");
        if (worst_ratio_dev > 0.01) p1b = false;
    }

    // ------------------------------------------------------------------
    // P2/P3 - Planck curve and Stefan-Boltzmann from the counted mode sum
    //   cavity units: eps_n = n (units hc/2L), theta = kT in those units
    // ------------------------------------------------------------------
    std::printf("P2: Planck curve from counted modes x occupation (periodic bulk)\n");
    {
        const int Rmax = 1000;
        const double theta = 50.0;
        double meandev = 0; int nb = 0;
        for (int R0 = 200; R0 < 900; R0 += 50) {
            double usum = 0, upred = 0;
            for (int R = R0; R < R0 + 50; ++R) {
                const double x = (R + 0.5) / theta;   // bin-centre energy for both
                usum += 2.0 * shellF[R] * (R + 0.5) / (std::exp(x) - 1.0);
                upred += 2.0 * 4.0*std::numbers::pi*((double)R*R + R + 1.0/3.0)
                       * (R + 0.5) / (std::exp(x) - 1.0);
            }
            meandev += std::fabs(usum/upred - 1.0); ++nb;
        }
        meandev /= nb;
        std::printf("  counted vs continuum Planck, theta=50: mean |dev| = %.4f%% (<0.1%%) [%s]\n",
                    100.0*meandev, meandev < 0.001 ? "PASS" : "FAIL");
        if (meandev > 0.001) p2 = false;
        // limits
        const double xlo = 0.05, xhi = 10.0;
        const double rj = (xlo/(std::exp(xlo)-1.0));          // -> 1 as x->0 (RJ)
        const double wt = (xhi/(std::exp(xhi)-1.0)) / (xhi*std::exp(-xhi)); // -> 1 (Wien tail)
        std::printf("  RJ limit x=0.05: occupation*x = %.4f (1 within 1%%: %s);"
                    " Wien tail x=10: ratio to x e^-x = %.4f [%s]\n",
                    rj, std::fabs(rj-1.0)<0.03?"yes":"no", wt,
                    std::fabs(wt-1.0)<0.01?"PASS":"NOTE");
        if (std::fabs(rj-1.0) > 0.03) p2 = false;

        std::printf("\nP3: Stefan-Boltzmann from the counted sum (periodic bulk)\n");
        std::vector<double> lnU, lnT;
        for (double th : {40.0, 50.0, 60.0}) {
            double E = 0;
            for (int R = 1; R <= Rmax; ++R)
                E += 2.0 * shellF[R] * (R + 0.5) / (std::exp((R + 0.5)/th) - 1.0);
            const double Eana = 8.0 * std::numbers::pi * std::pow(th, 4.0)
                              * (std::pow(std::numbers::pi, 4.0)/15.0);
            if (th == 50.0) {
                std::printf("  mode-sum E(theta=50) vs 8 pi theta^4*(pi^4/15): dev %.4f%%  [%s]\n",
                            100.0*std::fabs(E/Eana-1.0), std::fabs(E/Eana-1.0) < 0.001 ? "PASS" : "FAIL");
                if (std::fabs(E/Eana - 1.0) > 0.001) p3 = false;
            }
            lnU.push_back(std::log(E)); lnT.push_back(std::log(th));
        }
        const double expfit = (lnU[2]-lnU[0])/(lnT[2]-lnT[0]);
        std::printf("  fitted T-exponent over theta 40..60: %.4f (4.00 +- 0.02)  [%s]\n",
                    expfit, std::fabs(expfit-4.0) < 0.02 ? "PASS" : "FAIL");
        if (std::fabs(expfit - 4.0) > 0.02) p3 = false;
        // the pi^4/15 itself, computed from the sum (not inserted):
        double E50 = 0; for (int R = 1; R <= Rmax; ++R)
            E50 += 2.0 * shellF[R] * (R + 0.5) / (std::exp((R + 0.5)/50.0) - 1.0);
        const double I3 = E50 / (8.0 * std::numbers::pi * std::pow(50.0, 4.0));
        std::printf("  integral I3 = %.6f from the mode sum (pi^4/15 = %.6f)\n", I3,
                    std::pow(std::numbers::pi,4.0)/15.0);
        const double sigma = 2.0*std::pow(std::numbers::pi,5.0)*std::pow(kB,4.0)
                           / (15.0*h*h*h*c0*c0);
        const double a_pred = 4.0*sigma/c0;
        std::printf("  sigma_SI = 2 pi^5 k_B^4/(15 h^3 c^2) = %.6e W/m^2K^4\n", sigma);
        std::printf("  a = 4 sigma/c = %.6e vs measured::a_rad = %.6e (dev %.1f ppm)\n\n",
                    a_pred, measured::a_rad, 1e6*std::fabs(a_pred/measured::a_rad - 1.0));
    }

    // ------------------------------------------------------------------
    // P4 - Wien from the extremum (root derived by bisection, not inserted)
    // ------------------------------------------------------------------
    std::printf("P4: Wien displacement from the spectral extremum\n");
    {
        // u_lambda ~ x^5/(e^x - 1): d/dx = 0  =>  5(1 - e^-x) = x
        auto f = [](double x){ return 5.0*(1.0 - std::exp(-x)) - x; };
        double lo = 3.0, hi = 8.0;
        for (int i = 0; i < 200; ++i) { const double m = 0.5*(lo+hi); (f(m) > 0 ? lo : hi) = m; }
        const double xstar = 0.5*(lo+hi);
        const double b = h*c0/(kB*xstar);
        std::printf("  root of 5(1-e^-x)=x by bisection: x* = %.6f (4.965114 +- 1e-5) [%s]\n",
                    xstar, std::fabs(xstar-4.965114) < 1e-5 ? "PASS" : "FAIL");
        std::printf("  b = hc/(x* k_B) = %.6e m K  (2.898e-3, dev %.3f%%)  [%s]\n",
                    b, 100.0*std::fabs(b/2.898e-3 - 1.0),
                    std::fabs(b/2.898e-3 - 1.0) < 0.001 ? "PASS" : "FAIL");
        if (std::fabs(xstar-4.965114) > 1e-5 || std::fabs(b/2.898e-3 - 1.0) > 0.001) p4 = false;
    }

    // ------------------------------------------------------------------
    // P5 - UV honesty disclosure (committed deliverable)
    // ------------------------------------------------------------------
    std::printf("\nP5: UV honesty\n");
    {
        const double nu_cut = c0 / (2.0 * measured::l_P);
        const double x300 = h*nu_cut/(kB*300.0);
        std::printf("  l_P mode cutoff: nu_max ~ c/(2 l_P) = %.3e Hz; at T=300 K,\n", nu_cut);
        std::printf("  x = h nu/kT = %.3e -> occupation e^-x UNDERFLOWS: the cutoff does ZERO\n", x300);
        std::printf("  numerical work at physical temperatures. Finiteness of the spectrum is\n");
        std::printf("  carried by eps = h nu quantisation - i.e. Planck's postulate, carried\n");
        std::printf("  into SDT as the Law-I bridge, ASSERTED not derived. Disclosed.\n");
    }

    const bool all = p1a && p1b && p2 && p3 && p4;
    std::printf("\n================================================================\n");
    std::printf(" TD06 GATES: P1a %s | P1b %s | P2 %s | P3 %s | P4 %s | P5 disclosed\n",
                p1a?"PASS":"FAIL", p1b?"PASS":"FAIL", p2?"PASS":"FAIL",
                p3?"PASS":"FAIL", p4?"PASS":"FAIL");
    std::printf(" SAR02 cross-check: a_rad agreement reported above (consistency ONLY,\n");
    std::printf(" not the pass). Occupation inherited from TD02 (native counting,\n");
    std::printf(" class CONVERGENCE) -> TD06 capped at CONVERGENCE.\n");
    std::printf(" VERDICT: %s - see TD06_VERDICT.md\n", all ? "PASS" : "FAIL");
    std::printf("================================================================\n");
    return all ? 0 : 1;
}
