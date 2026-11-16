// ============================================================================
//  TD04 — Heat Conduction and Diffusion from Relay
//
//  P1  D = v*lambda/3 from the relay random walk (MSD).
//  P2  Diffusion equation: stripe release, variance ~ 2*alpha*t, Gaussian.
//  P3  Fourier slab: flux between diffuse walls vs k = (1/3) n v lambda k_B.
//  P4  Materials (argon, air) with OBSERVED inputs; sqrt(T) law; Cu DEFERRED.
//  P5  Wiedemann-Franz: classical one-channel Lorenz number reported; the
//      measured 2.44e-8 needs degenerate statistics -> OPEN (no native route).
//
//  Author: J. C. Harvey, Melbourne. 2026-07-03.
//  Build: cl /std:c++20 /EHsc /O2 /utf-8 /I Engine/include td04_relay_conduction.cpp
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>

namespace {
const double kB = sdt::laws::measured::k_B;
std::mt19937_64 rng(20260703ULL);
std::uniform_real_distribution<double> u01(0.0, 1.0);

struct Dir { double x, y, z; };
Dir iso_dir() {
    const double c = 2.0*u01(rng) - 1.0, ph = 2.0*std::numbers::pi*u01(rng);
    const double s = std::sqrt(1.0 - c*c);
    return { s*std::cos(ph), s*std::sin(ph), c };
}
} // namespace

int main() {
    std::printf("================================================================\n");
    std::printf(" TD04 - Heat Conduction and Diffusion from Relay\n");
    std::printf(" J. C. Harvey, Melbourne - 2026-07-03\n");
    std::printf(" Units: v = lambda = k_B = 1. All results pure numbers.\n");
    std::printf("================================================================\n\n");

    bool p1 = true, p2 = true, p3 = true;

    // ------------------------------------------------------------------
    // P1 - MSD: D = v lambda / 3
    // ------------------------------------------------------------------
    std::printf("P1: relay random walk -> D\n");
    {
        const int NW = 20000; const double tmax = 400.0;
        std::exponential_distribution<double> ell(1.0);   // mean free path 1
        double sum_r2 = 0;
        for (int w = 0; w < NW; ++w) {
            double x = 0, y = 0, z = 0, t = 0;
            while (t < tmax) {
                const double s = std::min(ell(rng), tmax - t);
                const Dir d = iso_dir();
                x += s*d.x; y += s*d.y; z += s*d.z; t += s;
            }
            sum_r2 += x*x + y*y + z*z;
        }
        const double D = sum_r2 / NW / (6.0 * tmax);
        const double dev = std::fabs(D - 1.0/3.0) * 3.0;
        std::printf("  D_fit = %.5f  (v*lambda/3 = 0.33333)  dev %.2f%%  [%s]\n\n",
                    D, 100.0*dev, dev < 0.02 ? "PASS" : "FAIL");
        if (dev > 0.02) p1 = false;
    }

    // ------------------------------------------------------------------
    // P2 - stripe release: variance ~ 2 alpha t, Gaussian profile
    // ------------------------------------------------------------------
    std::printf("P2: diffusion equation from stripe release\n");
    {
        const int NW = 40000;
        std::exponential_distribution<double> ell(1.0);
        std::vector<double> ts = {50.0, 100.0, 200.0, 400.0};
        std::printf("    t        var(x)/2t   kurtosis\n");
        double worst_alpha = 0, worst_kurt = 0;
        for (double tmax : ts) {
            double m2 = 0, m4 = 0;
            for (int w = 0; w < NW; ++w) {
                double x = 0, t = 0;
                while (t < tmax) {
                    const double s = std::min(ell(rng), tmax - t);
                    x += s * iso_dir().x; t += s;
                }
                m2 += x*x; m4 += x*x*x*x;
            }
            m2 /= NW; m4 /= NW;
            const double alpha = m2 / (2.0*tmax), kurt = m4/(m2*m2);
            worst_alpha = std::max(worst_alpha, std::fabs(alpha - 1.0/3.0)*3.0);
            worst_kurt = std::max(worst_kurt, std::fabs(kurt - 3.0));
            std::printf("  %6.0f     %.5f     %.4f\n", tmax, alpha, kurt);
        }
        std::printf("  worst |alpha/(vl/3)-1| = %.2f%% (<2%%), worst |kurt-3| = %.3f (<0.1) [%s]\n\n",
                    100.0*worst_alpha, worst_kurt,
                    (worst_alpha < 0.02 && worst_kurt < 0.1) ? "PASS" : "FAIL");
        if (worst_alpha > 0.02 || worst_kurt > 0.1) p2 = false;
    }

    // ------------------------------------------------------------------
    // P3 - Fourier slab: J vs (1/3) n v lambda k_B * dT/dx
    // ------------------------------------------------------------------
    std::printf("P3: Fourier slab (L=100 lambda, diffuse walls, tag carriers)\n");
    auto slab_flux = [&](double L, double Th, double Tc, double v, long nseg) -> double {
        // one carrier in volume A*L (A=1): n = 1/L. Energy tag = T of last wall.
        // Returns J = energy delivered to cold wall net per unit time.
        std::exponential_distribution<double> ell(1.0);
        double x = 0.5*L, mu = 2.0*u01(rng) - 1.0, tag = 0.5*(Th+Tc);
        double t = 0, Ecold = 0, Ehot = 0;
        for (long i = 0; i < nseg; ++i) {
            const double s = ell(rng);
            double dx = s * mu;
            // does it hit a wall first?
            if (mu > 0 && x + dx >= L) {
                const double sw = (L - x) / mu;
                t += sw / v; x = L;
                Ecold += (tag - Tc);            // deliver, re-thermalise (cold wall at L)
                tag = Tc;
                mu = -std::sqrt(u01(rng));      // cosine re-emission inward
            } else if (mu < 0 && x + dx <= 0.0) {
                const double sw = -x / mu;
                t += sw / v; x = 0.0;
                Ehot += (tag - Th);             // negative: wall GIVES energy
                tag = Th;
                mu = std::sqrt(u01(rng));
            } else {
                x += dx; t += s / v;
                mu = 2.0*u01(rng) - 1.0;        // isotropic bulk scatter (tag kept)
            }
        }
        return Ecold / t;                        // J per area (A=1)
    };
    {
        const double L = 100.0, Th = 1.1, Tc = 0.9, z0 = 0.7104;
        const double J = slab_flux(L, Th, Tc, 1.0, 200'000'000L);
        const double n = 1.0 / L;                // one carrier, V = L
        const double k_th = n / 3.0;             // (1/3) n v lambda k_B
        const double J_pred = k_th * (Th - Tc) / (L + 2.0*z0);
        const double dev = std::fabs(J/J_pred - 1.0);
        std::printf("  J_sim = %.4e   J_pred = k_th*dT/(L+2 z0 l) = %.4e   dev %.2f%%  [%s]\n",
                    J, J_pred, 100.0*dev, dev < 0.05 ? "PASS" : "FAIL");
        if (dev > 0.05) p3 = false;
        // linearity in dT
        const double J2 = slab_flux(L, 1.05, 0.95, 1.0, 200'000'000L);
        const double lin = J2 / J;
        std::printf("  linearity: J(dT/2)/J(dT) = %.4f (0.5 +- 3%%)  [%s]\n",
                    lin, std::fabs(lin - 0.5) < 0.015 ? "PASS" : "FAIL");
        if (std::fabs(lin - 0.5) > 0.015) p3 = false;
        // sqrt(T) law: carrier speed v ~ sqrt(T); flux at 4x T doubles (fixed lambda)
        const double J4 = slab_flux(L, 4.0*Th, 4.0*Tc, 2.0, 200'000'000L);
        const double ratio = J4 / (4.0 * J);     // tags scale by 4, v by 2 => J x8; /4 isolates v
        std::printf("  sqrt(T) (lattice fixed-lambda limit): J(4T)/(4 J(T)) = %.4f (2.0 +- 3%%) [%s]\n",
                    ratio, std::fabs(ratio - 2.0) < 0.06 ? "PASS" : "FAIL");
        std::printf("  (FD02 caveat restated: real gases at fixed P have lambda(T); Sutherland ~0.7)\n\n");
        if (std::fabs(ratio - 2.0) > 0.06) p3 = false;
    }

    // ------------------------------------------------------------------
    // P4 - materials with OBSERVED inputs (SI now; k_B enters here only)
    // ------------------------------------------------------------------
    std::printf("P4: real materials (OBSERVED inputs; elementary kinetic formula)\n");
    bool p4_ar = false, p4_air = false;
    {
        struct Gas { const char* name; double d, m_amu, cv_kB, k_meas; };
        const Gas gases[] = {
            {"argon", 3.40e-10, 39.948, 1.5, 0.0177},
            {"air  ", 3.70e-10, 28.97,  2.5, 0.0262},
        };
        const double P = 101325.0, T = 300.0, amu = 1.66053906660e-27;
        for (const Gas& g : gases) {
            const double n = P / (kB * T);
            const double m = g.m_amu * amu;
            const double vbar = std::sqrt(8.0 * kB * T / (std::numbers::pi * m));
            const double lam = kB * T / (std::sqrt(2.0) * std::numbers::pi * g.d*g.d * P);
            const double k_pred = (1.0/3.0) * n * vbar * lam * g.cv_kB * kB;
            const double fac = g.k_meas / k_pred;
            const bool ok = (fac <= 2.0 && fac >= 0.5);
            std::printf("  %s: k_pred = %.4f W/mK  vs measured %.4f  -> factor %.2f  [%s]\n",
                        g.name, k_pred, g.k_meas, fac, ok ? "PASS (<=2x)" : "FAIL (>2x, reported)");
            if (g.name[0] == 'a' && g.name[1] == 'r') p4_ar = ok; else p4_air = ok;
        }
        std::printf("  copper: DEFERRED/OPEN - a native metal channel needs degenerate carrier\n");
        std::printf("  statistics SDT has not derived; importing v_F, lambda_e would be a borrow.\n\n");
    }

    // ------------------------------------------------------------------
    // P5 - Wiedemann-Franz: committed statement, no simulation
    // ------------------------------------------------------------------
    std::printf("P5: Wiedemann-Franz (declared before run; no native route yet)\n");
    {
        const double e = 1.602176634e-19;
        const double L_classical = 1.5 * (kB/e) * (kB/e);
        const double L_meas = 2.44e-8;
        std::printf("  one-channel classical relay carriers: L = (3/2)(k_B/e)^2 = %.3e WOhm/K^2\n", L_classical);
        std::printf("  measured Sommerfeld value:             L = %.3e  (ratio %.2f)\n", L_meas, L_meas/L_classical);
        std::printf("  T3 falsifier status: FIRED at the 10%% gate. The pi^2/3 prefactor needs\n");
        std::printf("  degenerate carrier statistics; SDT has no native derivation -> OPEN (grade D\n");
        std::printf("  on this sub-claim). Constancy across metals is untestable natively (no\n");
        std::printf("  metal-specific native input exists). Reported, not buried.\n\n");
    }

    const bool core = p1 && p2 && p3;
    std::printf("================================================================\n");
    std::printf(" TD04 GATES: P1 %s | P2 %s | P3 %s | P4 argon %s, air %s, Cu DEFERRED | P5 OPEN (fired, reported)\n",
                p1?"PASS":"FAIL", p2?"PASS":"FAIL", p3?"PASS":"FAIL",
                p4_ar?"PASS":"FAIL", p4_air?"PASS":"FAIL");
    std::printf(" Core mechanism gates (P1-P3): %s. Exit code reflects core only;\n", core?"PASS":"FAIL");
    std::printf(" P4/P5 outcomes are graded in TD04_VERDICT.md, not laundered into the exit.\n");
    std::printf("================================================================\n");
    return core ? 0 : 1;
}
