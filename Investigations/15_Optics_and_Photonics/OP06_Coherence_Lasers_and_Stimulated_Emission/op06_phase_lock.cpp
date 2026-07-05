// ============================================================================
// OP06 — Coherence, Lasers and Stimulated Emission as Relay Phase-Lock
// Author: J. C. Harvey, Melbourne · 2026-07-04
//
// MACHINERY ONLY. Emitters dump real displacement impulses; the field is the
// SUM of their arrival-time registers. Locked = same tick phase (small jitter);
// independent = random tick phase. Intensity = mean-square of the summed
// registers. Stimulated emission = in-phase re-emission trigger; spontaneous =
// random-phase dump. Population bookkeeping in continuous intensity units.
// No Fock states, no boson bunching postulate, no quantised cavity mode.
// ============================================================================

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <random>
#include <vector>
#include <numbers>

using namespace sdt::laws;
using std::numbers::pi;

static int g_fail = 0;
static void gate(const char* id, bool pass, const char* detail) {
    std::printf("  [%s] %s  %s\n", pass ? "PASS" : "FAIL", id, detail);
    if (!pass) ++g_fail;
}

int main() {
    std::printf("OP06 — Coherence & lasing as macroscopic relay phase-lock (J. C. Harvey, 2026-07-04)\n");
    std::printf("Machinery only: summed real registers, in-phase triggers, random dumps.\n\n");
    std::mt19937_64 rng(20260704ULL);
    std::uniform_real_distribution<double> U(0.0, 2.0 * pi);
    std::normal_distribution<double> G(0.0, 1.0);

    // ---------------- Phase 1: g2(0) from lock vs independent ----------------
    std::printf("Phase 1 — g2(0) from lock-vs-independent emitters (N=200, M=200000 realisations)\n");
    const int N = 200, M = 200000;
    auto g2 = [&](bool locked) {
        double sI = 0.0, sI2 = 0.0;
        for (int m = 0; m < M; ++m) {
            double C = 0.0, S = 0.0;
            const double common = U(rng);
            for (int j = 0; j < N; ++j) {
                const double ph = locked ? common + 0.05 * G(rng) : U(rng);
                C += std::cos(ph); S += std::sin(ph);
            }
            const double I = C * C + S * S;
            sI += I; sI2 += I * I;
        }
        sI /= M; sI2 /= M;
        return sI2 / (sI * sI);
    };
    const double g2_th = g2(false), g2_lk = g2(true);
    const double target_th = 2.0 - 1.0 / N;
    std::printf("  independent (thermal): g2(0) = %.4f  vs 2 - 1/N = %.4f\n", g2_th, target_th);
    std::printf("  phase-locked (laser):  g2(0) = %.4f  vs 1.00\n", g2_lk);
    gate("P1-thermal", std::fabs(g2_th - target_th) / target_th < 0.01, "bunched statistics from independence alone");
    gate("P1-locked", std::fabs(g2_lk - 1.0) < 0.01, "flat statistics from the lock alone");
    std::printf("  -> NOTE (committed): this is CLASSICAL summed-register statistics. The boson\n"
                "     story was never needed for g2=2 vs 1 — and equally, matching it here is\n"
                "     CONVERGENCE with classical stochastic optics, not a native triumph.\n");

    // ---------------- Phase 2: gain & threshold ----------------
    std::printf("\nPhase 2 — threshold from in-phase trigger gain vs cavity loss (structural gates)\n");
    // dn2/dt = Pump - n2/tau - G n2 I ;  dI/dt = (G n2 - kappa) I + eps n2
    // MODEL-SCALE inputs (declared, not fitted): tau=1, G=1, kappa=10, eps=1e-4.
    const double tau = 1.0, Gg = 1.0, kap = 10.0, eps = 1e-4;
    const double n2_clamp = kap / Gg;                          // gain = loss
    const double P_th = n2_clamp / tau;                        // expected knee
    std::vector<double> pumps, Iout;
    for (double P = 2.0; P <= 30.0; P += 0.5) {
        double n2 = 0.0, I = 1e-9;
        for (int t = 0; t < 400000; ++t) {                     // relax to steady state
            const double dn2 = P - n2 / tau - Gg * n2 * I;
            const double dI  = (Gg * n2 - kap) * I + eps * n2;
            n2 += 1e-4 * dn2; I += 1e-4 * dI;
        }
        pumps.push_back(P); Iout.push_back(I);
        if (std::fabs(P - 20.0) < 1e-9)
            std::printf("  P = %.1f (2x threshold): n2 = %.4f vs clamp kappa/G = %.4f  (%.3f%%)\n",
                        P, n2, n2_clamp, 100.0 * std::fabs(n2 - n2_clamp) / n2_clamp);
        if (std::fabs(P - 20.0) < 1e-9)
            gate("P2-clamp", std::fabs(n2 - n2_clamp) / n2_clamp < 0.01, "excitation clamps at gain=loss above threshold");
    }
    { // linearity of output above threshold (P >= 1.5 P_th)
        double sx = 0, sy = 0, sxx = 0, sxy = 0, syy = 0; int k = 0;
        for (size_t i = 0; i < pumps.size(); ++i)
            if (pumps[i] >= 1.5 * P_th) { const double x = pumps[i], y = Iout[i];
                sx += x; sy += y; sxx += x * x; sxy += x * y; syy += y * y; ++k; }
        const double r = (k * sxy - sx * sy) / std::sqrt((k * sxx - sx * sx) * (k * syy - sy * sy));
        // knee sharpness: output at 0.8 P_th vs 1.6 P_th
        double Ibelow = 0, Iabove = 0;
        for (size_t i = 0; i < pumps.size(); ++i) {
            if (std::fabs(pumps[i] - 8.0) < 0.26) Ibelow = Iout[i];
            if (std::fabs(pumps[i] - 16.0) < 0.26) Iabove = Iout[i];
        }
        std::printf("  slope linearity above 1.5x threshold: R^2 = %.6f ;  I(1.6 Pth)/I(0.8 Pth) = %.0f\n",
                    r * r, Iabove / Ibelow);
        gate("P2-knee", r * r > 0.999 && Iabove / Ibelow > 100.0, "sharp turn-on at gain=loss; linear slope above");
    }

    // ---------------- Phase 3: linewidth as phase diffusion of the lock ----------------
    std::printf("\nPhase 3 — linewidth = phase diffusion from residual random dumps\n");
    // Locked field amplitude A (power ~ A^2); spontaneous dumps rate R_sp per tick,
    // each a unit register at random phase: phase kick = sin(theta)/A. Walk the phase.
    const double R_sp = 0.05;                                  // dumps per tick (model-scale)
    std::vector<double> lgP, lgD; double D10 = 0.0;
    std::poisson_distribution<int> Pois(R_sp);
    for (double A : {10.0, 20.0, 40.0, 80.0}) {
        const int T = 2000000;
        double phi = 0.0, sum2 = 0.0; int nseg = 0;
        double phi0 = 0.0;
        for (int t = 1; t <= T; ++t) {
            int k = Pois(rng);
            for (int j = 0; j < k; ++j) phi += std::sin(U(rng)) / A;
            if (t % 2000 == 0) { const double d = phi - phi0; sum2 += d * d; phi0 = phi; ++nseg; }
        }
        const double D = sum2 / nseg / 2000.0;                 // Var growth rate per tick
        const double D_ledger = R_sp / (2.0 * A * A);          // kick-ledger prediction
        std::printf("  A = %4.0f (P ~ %5.0f): D_sim = %.4e  vs kick-ledger R_sp/(2A^2) = %.4e (x%.2f)\n",
                    A, A * A, D, D_ledger, D / D_ledger);
        lgP.push_back(std::log(A * A)); lgD.push_back(std::log(D));
        if (A == 10.0) D10 = D;
    }
    {
        double n = 4, sx = 0, sy = 0, sxx = 0, sxy = 0;
        for (int i = 0; i < 4; ++i) { sx += lgP[i]; sy += lgD[i]; sxx += lgP[i] * lgP[i]; sxy += lgP[i] * lgD[i]; }
        const double slope = (n * sxy - sx * sy) / (n * sxx - sx * sx);
        std::printf("  linewidth-vs-power exponent: %.3f (committed gate -1 +/- 0.1)\n", slope);
        gate("P3-exponent", std::fabs(slope + 1.0) < 0.1, "Schawlow-Townes 1/P SCALING earned classically");
        std::printf("  -> ABSOLUTE prefactor pi*h*nu*(dnu_c)^2/P needs the h*nu emission quantum:\n"
                    "     the FLM12/hbar-entry root. Comparison note only — NOT gated (would smuggle\n"
                    "     the hbar debt in as if paid).\n");
    }

    // ---------------- Phase 4: coherence time from the same walk ----------------
    std::printf("\nPhase 4 — coherence time from field autocorrelation of the walked phase\n");
    {
        const double A = 10.0; const int T = 16000000;
        std::vector<float> phis(T);
        double phi = 0.0;
        for (int t = 0; t < T; ++t) {
            int k = Pois(rng);
            for (int j = 0; j < k; ++j) phi += std::sin(U(rng)) / A;
            phis[t] = float(phi);
        }
        auto corr = [&](int lag) {
            double s = 0.0; const int K = T - lag;
            for (int t = 0; t < K; t += 7) s += std::cos(phis[t + lag] - phis[t]);
            return s / ((K + 6) / 7);
        };
        const double tau_pred = 2.0 / D10;                     // e-fold of exp(-D tau/2)
        int lo = 1, hi = int(8.0 / D10);
        while (hi - lo > 1) { const int mid = (lo + hi) / 2; (corr(mid) > std::exp(-1.0)) ? lo = mid : hi = mid; }
        std::printf("  e-fold lag = %d ticks vs 2/D = %.0f ticks  (ratio %.3f)\n", lo, tau_pred, lo / tau_pred);
        gate("P4-coherence", std::fabs(lo / tau_pred - 1.0) < 0.10, "tau_c = 2/D; coherence length c*tau_c follows, ~P");
    }

    // ---------------- Honesty block ----------------
    std::printf("\nHONESTY FLAGS:\n"
                "  1. g2 = 2 vs 1 from independence-vs-lock is CLASSICAL summed-register statistics\n"
                "     (HBT already had the classical account). CLASS: CONVERGENCE. The lock model's\n"
                "     unification with CM01's order parameter is a structural narration, untested\n"
                "     here: F4 row OPEN.\n"
                "  2. ANTIBUNCHING g2(0) < 1 is unreachable by ANY classical summed-field model,\n"
                "     including this one. It is the real quantum discriminator. SDT's candidate\n"
                "     (single-vortex re-arm dead-time between dumps) is a NATIVE mechanism in kind\n"
                "     but was NOT built here: row OPEN, logged as the make-or-break follow-up.\n"
                "  3. Rate-equation constants are MODEL-SCALE; only structure was gated (knee at\n"
                "     gain=loss, clamping, exponents). Nothing was tuned to a lab magnitude.\n"
                "  4. The ST prefactor hangs on the h*nu emission quantum -> FLM12/hbar-entry root\n"
                "     (same debt as OP05).\n");

    std::printf("\nOP06 exit: %s (%d gate failures)\n", g_fail == 0 ? "ALL COMMITTED GATES PASS" : "GATE FAILURES", g_fail);
    return g_fail == 0 ? 0 : 1;
}
