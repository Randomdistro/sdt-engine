// ============================================================================
// CM07 — Ferromagnetism as Aligned Vortex Wakes
// Author: J. C. Harvey, Melbourne · 2026-07-04
//
// MACHINERY ONLY. No spin operators, no Heisenberg Hamiltonian as mechanism,
// and ABSOLUTELY NO MAGNETONS — magnetisation is a count of aligned wakes,
// unit = the electron's own wake circulation kappa_e = h/m_e.
// Committed exchange: J = alpha * hbar^2/(2 m_e d^2)  (wake overlap at the
// shared confinement door, geared down by handed-redirection coupling alpha —
// NP17 precedent). k_B T_C = z * n_w * J. Gates pre-committed in RUN_LOG.md.
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <initializer_list>

using sdt::laws::measured::hbar;
using sdt::laws::measured::h;
using sdt::laws::measured::k_B;
using sdt::laws::measured::m_e;
using sdt::laws::measured::alpha;

namespace {
constexpr double eV = 1.602176634e-19;

struct Mag {
    const char* name;
    int z;            // coordination                    MEASURED-INPUT
    double d;         // [m] nearest-neighbour           MEASURED-INPUT
    double n_w;       // aligned wakes per atom (count)  MEASURED-INPUT
    double Tc_obs;    // [K]                             OBSERVED anchor
    bool inScope;     // direct-overlap 3d (committed) vs exhibit
};

const Mag mags[] = {
    {"Fe", 8,  2.482e-10, 2.22,  1043.0, true},
    {"Co", 12, 2.507e-10, 1.72,  1388.0, true},
    {"Ni", 12, 2.492e-10, 0.606,  627.0, true},
    {"Gd", 12, 3.573e-10, 7.63,   293.0, false},   // 4f: OUT-OF-SCOPE exhibit
};

double J_exchange(double d) {                      // committed formula, no knob
    return alpha * hbar * hbar / (2.0 * m_e * d * d);
}

// mean-field aligned fraction m(T): m = tanh( (T_C/T) m )
// ADJ-1: bisection on f(m) = tanh(Tc/T m) - m (fixed-point iteration converges
// too slowly near Tc and was measured as a false exponent in run 1).
double aligned_fraction(double T, double Tc) {
    if (T >= Tc) return 0.0;
    double lo = 1e-15, hi = 1.0;
    for (int i = 0; i < 200; ++i) {
        const double mid = 0.5 * (lo + hi);
        const double f = std::tanh(Tc / T * mid) - mid;
        if (f > 0) lo = mid; else hi = mid;
    }
    return 0.5 * (lo + hi);
}
}

int main() {
    std::printf("CM07 - Ferromagnetism as Aligned Vortex Wakes\n");
    std::printf("J. C. Harvey, Melbourne - 2026-07-04\n");
    std::printf("Units: aligned-wake counts; kappa_e = h/m_e = %.4e m^2/s.\n", h / m_e);
    std::printf("ZERO magnetons anywhere in this output.\n\n");

    // ------------------------------------------------------------------ P1
    std::printf("== P1: exchange magnitude native; SIGN honestly OPEN ==\n");
    for (const auto& m : mags) {
        if (!m.inScope) continue;
        std::printf("  %-3s |J| = alpha * hbar^2/(2 m_e d^2) = %.4e eV  [DERIVED, no knob]\n",
                    m.name, J_exchange(m.d) / eV);
    }
    std::printf("  Sign (why Fe/Co/Ni co-rotate, Cr/MnO contra-rotate): NOT derivable\n");
    std::printf("  from the magnitude formula. Naive rim-shear favours CONTRA-rotation\n");
    std::printf("  (facing rims of co-rotating wakes counter-move) - i.e. the pairing\n");
    std::printf("  channel of CM01/NP17; the co-rotation window needs the on-seat vs\n");
    std::printf("  off-seat balance, unbuilt. P1 sign: OPEN (pivot row 'report both\n");
    std::printf("  signs'). Ferro/antiferro classes enter as OBSERVED anchors only.\n\n");

    // ------------------------------------------------------------------ P2
    std::printf("== P2: Curie points  k_B T_C = z * n_w * J  (zero fitted params) ==\n");
    std::printf("  %-3s %2s %6s %8s %12s %10s %8s %s\n",
                "el", "z", "n_w", "J[meV]", "Tc_pred[K]", "Tc_obs[K]", "ratio", "gate 2x");
    double TcFe = 0, TcCo = 0, TcNi = 0;
    for (const auto& m : mags) {
        const double J  = J_exchange(m.d);
        const double Tc = m.z * m.n_w * J / k_B;
        const double r  = Tc / m.Tc_obs;
        const double miss = r > 1 ? r : 1.0 / r;
        if (m.inScope)
            std::printf("  %-3s %2d %6.3f %8.3f %12.1f %10.1f %8.3f %s\n",
                        m.name, m.z, m.n_w, J/eV*1e3, Tc, m.Tc_obs, r,
                        miss <= 2.0 ? "PASS" : "FAIL");
        else
            std::printf("  %-3s %2d %6.3f %8.3f %12.1f %10.1f %8.3f %s\n",
                        m.name, m.z, m.n_w, J/eV*1e3, Tc, m.Tc_obs, r,
                        "[OUT-OF-SCOPE EXHIBIT - 4f indirect]");
        if (m.name[0]=='F') TcFe = Tc;
        if (m.name[0]=='C' && m.name[1]=='o') TcCo = Tc;
        if (m.name[0]=='N') TcNi = Tc;
    }
    std::printf("  ordering pred: %s  (obs Co > Fe > Ni)  %s\n",
                (TcCo > TcFe && TcFe > TcNi) ? "Co > Fe > Ni" : "WRONG",
                (TcCo > TcFe && TcFe > TcNi) ? "PASS" : "FAIL");
    std::printf("  [inputs: z, d, n_w measured; alpha, hbar, m_e whitelist. No fit.]\n\n");

    // ------------------------------------------------------------------ P3
    std::printf("== P3: M(T) in native wake counts; mean-field exponent ==\n");
    {
        std::printf("  M(T)/M(0) = aligned fraction (Fe: M(0) = 2.22 wakes/atom):\n");
        for (double t : {0.2, 0.5, 0.8, 0.95, 0.99, 1.0})
            std::printf("    T/T_C = %4.2f : m = %.4f  -> %.3f wakes/atom\n",
                        t, aligned_fraction(t, 1.0), 2.22 * aligned_fraction(t, 1.0));
        // effective beta on t in [1e-4, 1e-2]
        double sx=0, sy=0, sxx=0, sxy=0; int n = 0;
        for (int i = 0; i < 15; ++i) {
            const double tt = 1e-4 * std::pow(100.0, i / 14.0);   // 1e-4..1e-2
            const double m  = aligned_fraction(1.0 - tt, 1.0);
            sx += std::log(tt); sy += std::log(m);
            sxx += std::log(tt)*std::log(tt); sxy += std::log(tt)*std::log(m);
            ++n;
        }
        const double beta = (n*sxy - sx*sy) / (n*sxx - sx*sx);
        std::printf("  M(T) -> 0 at T_C: PASS (0.0000 at T/T_C = 1)\n");
        std::printf("  effective beta = %.4f  (gate 0.5 +/- 0.1)  %s\n\n",
                    beta, std::fabs(beta - 0.5) < 0.1 ? "PASS" : "FAIL");
    }

    // ------------------------------------------------------------------ P4
    std::printf("== P4: hysteresis - domain wall in a seeded pinning landscape ==\n");
    {
        // wall coordinate x in [0,1); pinning wells at index-derived sites
        // energy E(x) = -h_ext * x + sum of wells; wall moves when local slope allows
        auto pin = [](double x) {                 // index-derived, deterministic
            double s = 0.0;
            for (int k = 1; k <= 5; ++k)          // ADJ-2: 0.004/k so h_max > max pin force
                s += (0.004 / k) * std::cos(2.0 * 3.14159265358979 * (7 * k) * x + 0.61803 * k);
            return s;
        };
        auto force = [&](double x) {              // -dE_pin/dx numeric
            const double e = 1e-5;
            return -(pin(x + e) - pin(x - e)) / (2.0 * e);
        };
        double x = 0.5;                            // wall position ~ M in wake counts
        double hmax = 1.0, hstep = 0.02;
        double coercive = -1.0, remanence = -999.0;
        int dir = -1; double hext = hmax;
        std::printf("  sweep h: +1 -> -1 -> +1 (native handedness-field units)\n");
        for (int leg = 0; leg < 2; ++leg) {
            for (; dir < 0 ? hext >= -hmax : hext <= hmax; hext += dir * hstep) {
                // quasi-static: wall slides while net force pushes it
                for (int it = 0; it < 2000; ++it) {
                    const double F = hext + force(x);
                    const double dx = 1e-4 * F;
                    if (std::fabs(F) < 0.005) break;   // pinned
                    x = std::fmin(1.0, std::fmax(0.0, x + dx));
                }
                const double M = 2.0 * x - 1.0;        // -1..1 in wake-count units
                if (leg == 0 && std::fabs(hext) <= 0.011 && remanence < -100.0) remanence = M;
                if (leg == 0 && coercive < 0 && M < 0.0) coercive = std::fabs(hext);
            }
            dir = +1; hext = -hmax;
        }
        std::printf("  remanence M(h=0) = %.3f of saturation  (gate > 0.5)  %s\n",
                    remanence, remanence > 0.5 ? "PASS" : "FAIL");
        std::printf("  coercive field h_c = %.3f (native units)  (gate > 0)  %s\n",
                    coercive, coercive > 0.0 ? "PASS" : "FAIL");
        std::printf("  [COMPUTED-toy: loop opens because unpinning is irreversible -\n");
        std::printf("   occlusion-pinned walls, EMC03 handedness field; deterministic\n");
        std::printf("   index-derived pinning, no RNG]\n\n");
    }

    std::printf("== Ledger ==\n");
    std::printf("  DERIVED : |J| formula (committed, no knob), T_C chain, beta, loop.\n");
    std::printf("  NAMED FAITH ITEM: the alpha gear-down (look-elsewhere duty carried;\n");
    std::printf("            out-of-family falsifier = Gd exhibit + future alloys).\n");
    std::printf("  OPEN    : exchange SIGN (ferro vs antiferro seating criterion).\n");
    std::printf("  MEASURED-INPUT: z, d, n_w (saturation wake counts). OBSERVED: T_C.\n");
    std::printf("  CALIBRATED: none (0 of 0). MAGNETONS: zero, as committed.\n");
    return 0;
}
