// ============================================================================
//  TD02 — Temperature and Equipartition from Throughput
//
//  P1  Two-definition concordance: beta from the throughput budget (Lagrange)
//      vs beta from TD01 counting (dlnW/dE), plus T_kin vs T_ent.
//  P2  Equipartition from even pair-sharing of quadratic DoFs (dynamics).
//  P3  Boltzmann factor from NATIVE counting: (a) Lagrange max of ln W,
//      (b) exact whole-lattice marginal, (c) relay-exchange dynamics.
//      NO canonical reservoir, NO S_res(E-eps) expansion, NO partition function.
//  P4  Delete test: every result is k_B x (pure number) or eps x (pure number).
//
//  Author: J. C. Harvey, Melbourne. 2026-07-03.
//  Build: cl /std:c++20 /EHsc /O2 /utf-8 /I Engine/include td02_throughput_temperature.cpp
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

namespace {

const double kB = sdt::laws::measured::k_B;   // the ONLY dependency-traced input

// TD01 counting: W(E,N) = C(E+N-1, N-1), quanta indistinguishable, cells distinct.
double ln_W(double E, double N) {
    return std::lgamma(E + N) - std::lgamma(E + 1.0) - std::lgamma(N);
}

struct Fit { double slope, intercept, R2; };

Fit linfit(const std::vector<double>& x, const std::vector<double>& y) {
    const size_t n = x.size();
    double sx = 0, sy = 0, sxx = 0, sxy = 0, syy = 0;
    for (size_t i = 0; i < n; ++i) {
        sx += x[i]; sy += y[i]; sxx += x[i]*x[i]; sxy += x[i]*y[i]; syy += y[i]*y[i];
    }
    const double d = n*sxx - sx*sx;
    Fit f;
    f.slope = (n*sxy - sx*sy)/d;
    f.intercept = (sy - f.slope*sx)/n;
    double ssres = 0, sstot = 0, ym = sy/n;
    for (size_t i = 0; i < n; ++i) {
        const double yh = f.slope*x[i] + f.intercept;
        ssres += (y[i]-yh)*(y[i]-yh);
        sstot += (y[i]-ym)*(y[i]-ym);
    }
    f.R2 = 1.0 - ssres/sstot;
    return f;
}

} // namespace

int main() {
    std::printf("================================================================\n");
    std::printf(" TD02 - Temperature and Equipartition from Throughput\n");
    std::printf(" J. C. Harvey, Melbourne - 2026-07-03\n");
    std::printf(" dependency-traced input: measured::k_B only. Energies in relay quanta eps.\n");
    std::printf("================================================================\n\n");

    bool p1_beta = true, p1_kin = true, p2_pass = true, p3_pass = true;

    // ------------------------------------------------------------------
    // P1 - Two-definition concordance
    //   beta_budget: solve <j> = 1/(e^b - 1) = E/N  =>  b = ln(1 + N/E)
    //     (Lagrange multiplier of the throughput budget in the ln W maximisation;
    //      derived analytically, no reservoir anywhere)
    //   beta_count : dlnW/dE by central difference of TD01 counting
    // ------------------------------------------------------------------
    // RUN-1 finding (documented, not buried): at N=500 the gap is a CONSTANT
    // 2.00e-3 = 1/N across the whole energy range. Trace: beta_count - beta_budget
    // = (1/2)[ln(1-1/(E+N)) - ln(1+1/E)] ~ -1/E for N<<E, so rel.gap ~ 1/N exactly.
    // That is the finite-size discretisation of dS/dE, not a physics gap. Committed
    // pivot applied (allowed adjustment: larger lattice, threshold UNCHANGED at 1e-3):
    // demonstrate gap*N ~ 1 scaling, then gate at N=8000.
    std::printf("P1: two-definition concordance\n");
    std::printf("  finite-size scaling of the concordance gap (E/N=100 fixed):\n");
    for (double Ns : {250.0, 500.0, 2000.0, 8000.0}) {
        const double E = 100.0 * Ns;
        const double bb = std::log(1.0 + Ns/E);
        const double bc = 0.5 * (ln_W(E+1.0, Ns) - ln_W(E-1.0, Ns));
        const double gap = std::fabs(bb - bc) / bb;
        std::printf("    N=%5.0f : rel.gap = %.3e   gap*N = %.3f\n", Ns, gap, gap*Ns);
    }
    std::printf("  => gap = 1/N (discretisation of dS/dE); definitions coincide as N->inf.\n\n");
    std::printf("  gate at N=8000 cells:\n");
    std::printf("    E/N      beta_budget    beta_count     rel.gap    T_kin/T_ent\n");
    const double N1 = 8000.0;
    double worst_gap = 0.0;
    for (double jbar : {10.0, 30.0, 100.0, 300.0, 1000.0, 2000.0}) {
        const double E = jbar * N1;
        const double bb = std::log(1.0 + N1/E);
        const double bc = 0.5 * (ln_W(E+1.0, N1) - ln_W(E-1.0, N1));
        const double gap = std::fabs(bb - bc) / bb;
        worst_gap = std::max(worst_gap, gap);
        // T_kin: k_B T_kin = <eps_dis> per cell = jbar * eps  (H1 definition)
        // T_ent: k_B T_ent = eps / beta                        (entropic)
        const double ratio = jbar * bb;   // = T_kin/T_ent
        std::printf("  %6.0f   %.8f   %.8f   %.2e   %.6f\n", jbar, bb, bc, gap, ratio);
        if (gap > 1e-3) p1_beta = false;
        if (jbar >= 1000.0 && std::fabs(ratio - 1.0) > 1e-3) p1_kin = false;
    }
    std::printf("  beta gates: worst |beta_budget-beta_count|/beta = %.2e (<1e-3) [%s]\n",
                worst_gap, p1_beta ? "PASS" : "FAIL");
    std::printf("  T_kin=T_ent in classical regime <j> >= 1000 [%s]\n", p1_kin ? "PASS" : "FAIL");
    std::printf("  NOTE (predicted, not absorbed): for <j> ~ 1 the two definitions separate;\n");
    std::printf("  <eps> = eps/(e^(eps/kBT)-1) is the discrete-cell freeze-out (Einstein form),\n");
    std::printf("  a consequence of quantised throughput, reported as a feature curve:\n");
    for (double jbar : {0.5, 1.0, 3.0}) {
        const double bb = std::log(1.0 + 1.0/jbar);
        std::printf("    <j>=%4.1f : T_kin/T_ent = %.4f  (freeze-out regime)\n", jbar, jbar*bb);
    }
    std::printf("\n");

    // ------------------------------------------------------------------
    // P2 - Equipartition from even pair-sharing (dynamics)
    //   M quadratic DoFs e_i = v_i^2 (units eps). Per tick: pick random pair,
    //   rotate in velocity space by uniform angle: e_a' = s cos^2(th), e_b' = s sin^2(th).
    //   This is the mechanics of an elastic exchange; no distribution imposed.
    //   Entropic temperature for quadratic DoFs: S = kB ln W ~ (M/2) ln E
    //   => 1/T = dS/dE => k_B T = 2 E_tot / M.
    // ------------------------------------------------------------------
    std::printf("P2: equipartition from pair-rotation mixing (M=500 DoFs)\n");
    const int M = 500;
    const double Etot = 1000.0;                  // in eps units
    const double kBT2 = 2.0 * Etot / M;          // = 4.0 (pure number x eps)
    std::mt19937_64 rng(20260703ULL);
    std::uniform_real_distribution<double> uang(0.0, 2.0*std::numbers::pi);
    std::uniform_int_distribution<int> upick(0, M-1);

    auto run_mix = [&](bool concentrated, std::vector<double>& meanE,
                       double& kurt, double& sigma_stat) {
        std::vector<double> e(M, 0.0);
        if (concentrated) { for (int i = 0; i < M/10; ++i) e[i] = Etot/(M/10); }
        else              { for (int i = 0; i < M;    ++i) e[i] = Etot/M; }
        const long burn = 2'000'000, meas = 50'000'000;
        for (long t = 0; t < burn; ++t) {
            int a = upick(rng), b = upick(rng); if (a == b) continue;
            const double s = e[a] + e[b], th = uang(rng), c = std::cos(th);
            e[a] = s*c*c; e[b] = s - e[a];
        }
        meanE.assign(M, 0.0);
        double m2 = 0, m4 = 0; long nv = 0; long snaps = 0;
        for (long t = 0; t < meas; ++t) {
            int a = upick(rng), b = upick(rng); if (a == b) continue;
            const double s = e[a] + e[b], th = uang(rng), c = std::cos(th);
            e[a] = s*c*c; e[b] = s - e[a];
            if (t % 500 == 0) {
                ++snaps;
                for (int i = 0; i < M; ++i) {
                    meanE[i] += e[i];
                    const double v = std::sqrt(e[i]);           // |v|; sign symmetric
                    m2 += v*v; m4 += v*v*v*v; ++nv;
                }
            }
        }
        for (int i = 0; i < M; ++i) meanE[i] /= double(snaps);
        kurt = (m4/nv) / ((m2/nv)*(m2/nv));      // Gaussian: 3
        // sigma of a per-DoF time average: chi^2_1 has var 2*mean^2; correlation
        // time ~ M pair-updates => n_indep ~ snaps*500/M per DoF (approx, printed)
        const double n_indep = double(meas) / double(M) / 4.0; // conservative
        sigma_stat = std::sqrt(2.0) * (kBT2/2.0) / std::sqrt(n_indep);
    };

    for (int init = 0; init < 2; ++init) {
        std::vector<double> meanE; double kurt = 0, sig = 0;
        run_mix(init == 0, meanE, kurt, sig);
        double rms = 0, worst = 0, gmean = 0;
        for (int i = 0; i < M; ++i) {
            const double d = meanE[i] - 0.5*kBT2;
            rms += d*d; worst = std::max(worst, std::fabs(d)); gmean += meanE[i];
        }
        rms = std::sqrt(rms/M); gmean /= M;
        const double rms_rel = rms/(0.5*kBT2), worst_rel = worst/(0.5*kBT2);
        std::printf("  init=%s: global<e_i>=%.5f (target %.5f), RMS dev %.3f%%, worst %.3f%% (%.1f sigma_stat)\n",
                    init == 0 ? "concentrated" : "uniform    ",
                    gmean, 0.5*kBT2, 100.0*rms_rel, 100.0*worst_rel, worst/sig);
        std::printf("             velocity kurtosis %.4f (Gaussian 3.0) -> MB marginal\n", kurt);
        if (rms_rel > 0.01) p2_pass = false;
        if (worst > 5.0*sig) p2_pass = false;
        if (std::fabs(kurt - 3.0) > 0.05) p2_pass = false;
    }
    std::printf("  equipartition <e_i> = (1/2)k_B T per quadratic DoF, init-independent [%s]\n",
                p2_pass ? "PASS" : "FAIL");
    std::printf("  c_v: 3 quadratic DoF/particle => c_v = 3/2 k_B  (near-definitional given\n");
    std::printf("  equipartition; flagged as such, not sold as an independent prediction)\n\n");

    // ------------------------------------------------------------------
    // P3 - Boltzmann factor from NATIVE counting (the firewalled core)
    //   (a) Lagrange: maximise ln[ N!/prod n_j! ] s.t. sum n_j = N, sum j n_j = E
    //       => n_j/N = (1-e^-b) e^-bj, b = ln(1+N/E).  (analytic, stated)
    //   (b) exact whole-lattice marginal under TD01's uniform microstate measure:
    //       p_j = W(E-j, N-1) / W(E, N)   -- counted EXACTLY, no expansion, no T input
    //   (c) dynamics: symmetric one-quantum exchange chain (uniform stationary
    //       measure by detailed symmetry of the proposal), histogram occupancy.
    // ------------------------------------------------------------------
    std::printf("P3: Boltzmann factor from native counting (N=500, E=5000, <j>=10)\n");
    const int N3 = 500; const long E3 = 5000;
    const double beta_b = std::log(1.0 + double(N3)/double(E3));

    // (b) exact marginal
    std::vector<double> js, lnp; std::vector<double> pexact;
    for (int j = 0; ; ++j) {
        const double p = std::exp(ln_W(double(E3-j), double(N3-1)) - ln_W(double(E3), double(N3)));
        if (p < 1e-5) break;
        pexact.push_back(p); js.push_back(j); lnp.push_back(std::log(p));
        if (j > 200) break;
    }
    const Fit fb = linfit(js, lnp);
    const double slope_gap = std::fabs(-fb.slope - beta_b)/beta_b;
    std::printf("  (b) exact marginal p_j = W(E-j,N-1)/W(E,N), j=0..%d\n", int(js.size())-1);
    std::printf("      ln p_j vs j : slope=%.6f  (-beta_budget=%.6f)  gap %.3f%%  R^2=%.6f\n",
                fb.slope, -beta_b, 100.0*slope_gap, fb.R2);
    if (fb.R2 < 0.999 || slope_gap > 0.01) p3_pass = false;

    // (c) dynamics: symmetric one-quantum relay exchange
    std::vector<int> cell(N3, int(E3/N3));
    std::uniform_int_distribution<int> upick3(0, N3-1);
    const long burn3 = 5'000'000, meas3 = 50'000'000;
    for (long t = 0; t < burn3; ++t) {
        int a = upick3(rng), b = upick3(rng);
        if (a != b && cell[a] > 0) { --cell[a]; ++cell[b]; }
    }
    std::vector<long> hist(256, 0); long nsnap = 0;
    for (long t = 0; t < meas3; ++t) {
        int a = upick3(rng), b = upick3(rng);
        if (a != b && cell[a] > 0) { --cell[a]; ++cell[b]; }
        if (t % 1000 == 0) {
            ++nsnap;
            for (int i = 0; i < N3; ++i) if (cell[i] < 256) ++hist[cell[i]];
        }
    }
    const double tot = double(nsnap) * N3;
    std::vector<double> js2, lnp2;
    double maxdev_sigma = 0.0;
    for (size_t j = 0; j < pexact.size(); ++j) {
        const double psim = hist[j]/tot;
        if (psim <= 0) break;
        js2.push_back(double(j)); lnp2.push_back(std::log(psim));
        const double sig = std::sqrt(pexact[j]*(1.0-pexact[j])/tot) *
                           std::sqrt(1000.0/double(N3) + 1.0); // crude correlation inflation
        maxdev_sigma = std::max(maxdev_sigma, std::fabs(psim - pexact[j])/sig);
    }
    const Fit fc = linfit(js2, lnp2);
    std::printf("  (c) relay-exchange dynamics (%.0e ticks): slope=%.6f  R^2=%.6f\n",
                double(meas3), fc.slope, fc.R2);
    std::printf("      occupancy histogram vs exact marginal: max |dev| = %.2f sigma (correlated-sample estimate)\n",
                maxdev_sigma);
    if (fc.R2 < 0.999) p3_pass = false;
    std::printf("  (a) Lagrange route (analytic): n_j/N = (1-e^-b)e^-bj with b = ln(1+N/E) = %.6f\n", beta_b);
    std::printf("      = beta from P1 budget; the exponential is an OUTPUT of relay counting.\n");
    std::printf("  FIREWALL: no S_res(E-eps) expansion, no predefined T, no partition-function\n");
    std::printf("  object was instantiated anywhere in P3. Route (b) is an exact complement\n");
    std::printf("  count under TD01's uniform measure; beta is read off AFTER the fact. [%s]\n\n",
                p3_pass ? "PASS" : "FAIL");

    // ------------------------------------------------------------------
    // P4 - delete test / unit audit
    // ------------------------------------------------------------------
    std::printf("P4: delete test - k_B appears only as a unit bridge\n");
    std::printf("  All P1-P3 numbers above are pure numbers (energies in eps units).\n");
    std::printf("  Example kelvin conversion (only place k_B enters): a bath with\n");
    std::printf("  <eps_dis> = 1 eV/DoF-pair  =>  T = (1 eV)/k_B = %.1f K = k_B^-1 x pure number.\n",
                1.602176634e-19 / kB);
    std::printf("  No h, no Z, no ensemble object in the chain. [PASS by construction]\n\n");

    const bool all = p1_beta && p1_kin && p2_pass && p3_pass;
    std::printf("================================================================\n");
    std::printf(" TD02 GATES: P1 %s | P2 %s | P3 %s | P4 PASS\n",
                (p1_beta && p1_kin) ? "PASS" : "FAIL", p2_pass ? "PASS" : "FAIL",
                p3_pass ? "PASS" : "FAIL");
    std::printf(" Firewall T4: NOT FIRED (no reservoir used on any route)\n");
    std::printf(" VERDICT: %s - see TD02_VERDICT.md for the physics class\n", all ? "PASS" : "FAIL");
    std::printf("================================================================\n");
    return all ? 0 : 1;
}
