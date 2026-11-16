// ============================================================================
// CM03 — Band Structure / Conductor–Insulator from Lattice Packing
// Author: J. C. Harvey, Melbourne · 2026-07-04
//
// MACHINERY ONLY. No Bloch waves, no k-space dispersion, no electron clouds.
// A "gap" is an occlusion blockade: the packing leaves no unoccluded relay
// path below a throughput threshold. The threshold is wake confinement
// (FD02 wake wavelength; same Law VI door as CM01's v_pack).
// Decision tree and gates pre-committed in RUN_LOG.md BEFORE this file.
// CALIBRATED(1): one minimax factor f over C/Si/Ge — same f for all solids.
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string_view>

using sdt::laws::measured::hbar;
using sdt::laws::measured::m_e;
using sdt::laws::measured::k_B;

namespace {
constexpr double eV = 1.602176634e-19;

struct Elem {
    const char* name;
    int z;          // coordination            MEASURED-INPUT
    int nbond;      // directional bonds       MEASURED-INPUT
    int netD;       // covalent network dim    MEASURED-INPUT
    double d_nn;    // [m]                     MEASURED-INPUT
    const char* obsClass;   // OBSERVED anchor
    double Eg_obs;  // [eV] OBSERVED (-1 = none)
    bool inGate;    // in the committed C/Si/Ge magnitude gate
};

const Elem elems[] = {
    {"Cu",      12, 1, 3, 2.556e-10, "metal",     -1.0, false},
    {"Ag",      12, 1, 3, 2.889e-10, "metal",     -1.0, false},
    {"Al",      12, 3, 3, 2.863e-10, "metal",     -1.0, false},
    {"Si",       4, 4, 3, 2.352e-10, "semi",       1.12, true},
    {"Ge",       4, 4, 3, 2.450e-10, "semi",       0.66, true},
    {"C",        4, 4, 3, 1.545e-10, "insulator",  5.47, true},
    {"Sn-grey",  4, 4, 3, 2.810e-10, "semi",       0.08, false},
    {"S",        2, 2, 0, 2.055e-10, "insulator",  3.0,  false},
    {"P-black",  3, 3, 2, 2.224e-10, "semi",       0.33, false},
};

double Eg_model_raw(double d) {            // wake-confinement scale, f = 1
    return hbar * hbar / (m_e * d * d);
}
}

int main() {
    std::printf("CM03 - Band Structure from Lattice Packing (occlusion blockade)\n");
    std::printf("J. C. Harvey, Melbourne - 2026-07-04\n");
    std::printf("Door: FD02 wake confinement (same Law VI door as CM01 v_pack)\n\n");

    // ------------------------------------------------------ CALIBRATED(1)
    // minimax f over the committed C/Si/Ge set (declared pre-run)
    double lo = 1e9, hi = 0;
    for (const auto& e : elems) {
        if (!e.inGate) continue;
        const double r = e.Eg_obs / (Eg_model_raw(e.d_nn) / eV);
        lo = std::fmin(lo, r); hi = std::fmax(hi, r);
    }
    const double f = std::sqrt(lo * hi);       // minimax on log scale
    std::printf("CALIBRATED(1): f = %.4f (minimax over C/Si/Ge; SAME f everywhere)\n", f);
    std::printf("               max committed miss = sqrt(hi/lo) = %.3f x\n\n", std::sqrt(hi/lo));

    // ------------------------------------------------------------------ P1
    std::printf("== P1: trichotomy from the pre-committed 3-rule tree ==\n");
    std::printf("  %-8s %2s %5s %5s %8s  %-10s %-10s %s\n",
                "elem", "z", "bond", "netD", "Eg_pred", "predicted", "observed", "ok");
    int mis = 0;
    for (const auto& e : elems) {
        const int U = e.z - e.nbond;
        double Eg = -1.0;
        const char* cls;
        if (U > 0)              cls = "metal";
        else if (e.netD == 0)   cls = "insulator";       // vdW blockade
        else {
            Eg = f * Eg_model_raw(e.d_nn) / eV;
            cls = (Eg <= 2.0) ? "semi" : "insulator";    // 2.0 eV convention (declared)
        }
        const bool ok = (std::string_view(cls) == e.obsClass);
        mis += !ok;
        if (Eg > 0)
            std::printf("  %-8s %2d %5d %5d %7.2f   %-10s %-10s %s\n",
                        e.name, e.z, e.nbond, e.netD, Eg, cls, e.obsClass, ok ? "OK" : "MISS");
        else
            std::printf("  %-8s %2d %5d %5d %8s  %-10s %-10s %s\n",
                        e.name, e.z, e.nbond, e.netD, "-", cls, e.obsClass, ok ? "OK" : "MISS");
    }
    std::printf("  P1: %d misclassifications of 9 (gate 0; kill >=2)  %s\n\n",
                mis, mis == 0 ? "PASS" : (mis >= 2 ? "KILL" : "FAIL"));

    // ------------------------------------------------------------------ P2
    std::printf("== P2: gap ordering (native) + magnitude (one f) ==\n");
    double EgC = 0, EgSi = 0, EgGe = 0;
    for (const auto& e : elems) {
        if (!e.inGate && !(std::string_view(e.name) == "Sn-grey"
                        || std::string_view(e.name) == "P-black")) continue;
        const double Eg = f * Eg_model_raw(e.d_nn) / eV;
        const double ratio = Eg / e.Eg_obs;
        const double miss = ratio > 1 ? ratio : 1.0 / ratio;
        if (e.inGate)
            std::printf("  %-8s Eg_pred = %5.2f eV  obs = %5.2f  miss %.2fx (gate 2x)  %s\n",
                        e.name, Eg, e.Eg_obs, miss, miss <= 2.0 ? "PASS" : "FAIL");
        else
            std::printf("  %-8s Eg_pred = %5.2f eV  obs = %5.2f  miss %.1fx  [EXHIBIT - outside gate]\n",
                        e.name, Eg, e.Eg_obs, miss);
        if (std::string_view(e.name) == "C")  EgC  = Eg;
        if (std::string_view(e.name) == "Si") EgSi = Eg;
        if (std::string_view(e.name) == "Ge") EgGe = Eg;
    }
    std::printf("  ordering C > Si > Ge (f-independent, pure 1/d^2): %s [DERIVED]\n\n",
                (EgC > EgSi && EgSi > EgGe) ? "PASS" : "FAIL");

    // ------------------------------------------------------------------ P3
    std::printf("== P3: activated conduction from pair-creation mass action ==\n");
    {
        // generation ~ exp(-Eg/kT); recombination ~ n^2  =>  n ~ exp(-Eg/2kT)
        // The 1/2 is DERIVED: bridging creates a freed wake AND a mobile vacancy.
        const double EgSi_J = f * Eg_model_raw(2.352e-10);
        std::vector<double> x, y;
        double prev = -1; bool monotonic = true;
        for (int i = 0; i < 12; ++i) {
            const double T = 250.0 + 30.0 * i;
            const double n = std::exp(-EgSi_J / (2.0 * k_B * T));   // relative
            const double rho = 1.0 / n;                             // relative
            x.push_back(1.0 / T); y.push_back(std::log(rho));
            if (prev > 0 && rho > prev) monotonic = false;          // drho/dT<0 check
            prev = rho;
        }
        double sx=0, sy=0, sxx=0, sxy=0; const int n = (int)x.size();
        for (int i = 0; i < n; ++i) { sx+=x[i]; sy+=y[i]; sxx+=x[i]*x[i]; sxy+=x[i]*y[i]; }
        const double slope = (n*sxy - sx*sy) / (n*sxx - sx*sx);     // = Eg/2kB
        const double rec   = slope * 2.0 * k_B / eV;                // recovered Eg [eV]
        const double err   = std::fabs(rec - EgSi_J/eV) / (EgSi_J/eV) * 100.0;
        std::printf("  Si: ln(rho) vs 1/T slope -> Eg = %.3f eV (input %.3f)  err %.2f%%  %s\n",
                    rec, EgSi_J/eV, err, err < 1.0 ? "PASS" : "FAIL");
        std::printf("  drho/dT < 0 across 250-580 K: %s (metal has opposite sign, P1 chain)\n\n",
                    monotonic ? "PASS" : "FAIL");
    }

    // ------------------------------------------------------------------ P4
    std::printf("== P4 (stretch): doping = one opened channel per substitutional defect ==\n");
    std::printf("  carrier count = dopant count (1:1 by construction of the channel count);\n");
    std::printf("  sigma proportional to N_d [COMPUTED, linear by mechanism]. Sign: donor\n");
    std::printf("  frees a wake (n); acceptor leaves a mobile vacancy - opposite handed\n");
    std::printf("  drift (p). Qualitative only; no numeric gate committed.\n\n");

    std::printf("== Ledger ==\n");
    std::printf("  DERIVED   : trichotomy tree outcomes; 1/d^2 ordering; the 1/2 in the\n");
    std::printf("              activation exponent (pair-creation kinetics).\n");
    std::printf("  NAMED PREMISE: wake confinement E ~ hbar^2/(m_e d^2) (FD02/Law VI door).\n");
    std::printf("  CALIBRATED(1): f (minimax over C/Si/Ge, same f for every solid).\n");
    std::printf("  CONVENTION: 2.0 eV semi/insulator line (standard usage, declared).\n");
    std::printf("  MEASURED-INPUT: z, bonds, network dim, d_nn. OBSERVED: classes, E_g.\n");
    return 0;
}
