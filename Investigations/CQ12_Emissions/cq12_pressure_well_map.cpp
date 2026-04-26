/**
 * CQ12 Stage A: Pressure-Well Diagnostic Inversion
 *
 * There is no "nuclear field." SDT has no fields.
 * The mechanism is convergent boundary pressure occlusion.
 *
 * Each electron sits in a specific convergent pressure well.
 * Its binding energy = the pressure deficit at its void position.
 * There is no Z_eff. There is no shielding. There is only the
 * NET convergent pressure balance at each geometric void.
 *
 * Sequential ionisation energies are EXTRACTION DEPTHS:
 * IE₁ = cost to extract electron 1 from neutral atom
 * IE₂ = cost to extract electron 2 from the +1 ion (different!)
 * IE₃ = cost to extract electron 3 from the +2 ion, etc.
 *
 * IMPORTANT: These are many-body removal energies from successively
 * changed ionic states. They are NOT direct excitation energies.
 * Emission requires two bound void states in the SAME charge state:
 *   E_γ = |B(void_initial; charge_state) - B(void_final; charge_state)|
 *
 * Pipeline position: Stage A (diagnostic inversion).
 * Stage B: geometry discovery from pressure-well structure.
 * Stage C: forward derivation of well depths from nuclear grammar.
 * Stage D: emission prediction (cq12_forward_emission_generator.cpp).
 *
 * k_H = 137.036 throughout. alpha = 1/k_H.
 */

#include <cstdio>
#include <cmath>
#include <sdt/laws.hpp>
#include "cq12_element_data.hpp"

// Bridge aliases into canonical sdt::laws::measured
namespace K {
    using namespace sdt::laws::measured;
    inline constexpr double eV_J  = eV_to_J;
    inline constexpr double k_H   = alpha_inv;
}

// Velocity from binding energy: ½m_e v² = IE → v = √(2·IE/m_e)
double v_from_IE(double IE_eV) {
    return std::sqrt(2.0 * IE_eV * K::eV_J / K::m_e);
}
double k_from_IE(double IE_eV) {
    return K::c / v_from_IE(IE_eV);
}

// Movement budget: v_circ² + v² = c²
double v_circ(double v) {
    return std::sqrt(K::c * K::c - v * v);
}

// ═══════════════════════════════════════════════════════
//  SEQUENTIAL IONISATION DATA — Z=1 to Z=118
//  Sourced from cq12_element_data.hpp (single truth).
//  Each IE is the cost to peel the NEXT electron from
//  the CURRENT ionic state.
// ═══════════════════════════════════════════════════════

// Alias for backward-compat: data[i].sym, .Z, .nIE, .IE[]
static const Atom* data = ELEMENTS;
static constexpr int N_ATOMS = NUM_ELEMENTS;

int main() {
    std::printf("╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  CQ12: CORRECTED — NO NUCLEAR FIELD                        ║\n");
    std::printf("║  Sequential ionisation = convergent pressure map            ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    std::printf("  There is no 'nuclear field'. There is no 'shielding'.\n");
    std::printf("  Each electron sits in a convergent pressure well.\n");
    std::printf("  IE_n = extraction cost of the next electron from the\n");
    std::printf("         current ionic state (many-body removal energy).\n");
    std::printf("  v_n = √(2·IE_n / m_e),  k_n = c/v_n,  z_n = 1/k_n²\n\n");

    // ═══════════════════════════════════════════════════
    //  PART 1: CONVERGENT PRESSURE MAP
    //  Each IE → a velocity → a k-factor → a radius
    // ═══════════════════════════════════════════════════
    std::printf("══ PART 1: CONVERGENT PRESSURE MAP ══\n\n");

    for (int a = 0; a < N_ATOMS; a++) {
        auto& at = data[a];
        std::printf("  %s (Z=%d):\n", at.sym, at.Z);
        std::printf("    %-4s  %10s  %10s  %10s  %10s  %10s  %10s\n",
            "IE#","IE(eV)","v/c","k","z","v_circ/c","budget");

        double total_angular = 0;

        for (int i = 0; i < at.nIE; i++) {
            double v = v_from_IE(at.IE[i]);
            double beta = v / K::c;
            double k = K::c / v;
            double z = 1.0 / (k * k);
            double vc = v_circ(v);
            double budget = (v*v + vc*vc) / (K::c * K::c);
            total_angular += beta; // proxy for angular momentum contribution

            std::printf("    IE%-2d  %10.3f  %10.6f  %10.2f  %10.4e  %10.8f  %10.8f\n",
                i+1, at.IE[i], beta, k, z, vc/K::c, budget);
        }

        // H-like check: last IE should equal Ry × Z²
        double IE_Hlike = K::Ry_eV * at.Z * at.Z;
        double last_IE = at.IE[at.nIE - 1];
        double dev = 100.0 * (last_IE - IE_Hlike) / IE_Hlike;
        if (at.nIE == at.Z) {
            std::printf("    Last IE vs Ry·Z² = %.3f vs %.3f (%+.2f%%)\n",
                last_IE, IE_Hlike, dev);
        }

        // Shell structure: gaps
        if (at.nIE >= 2) {
            std::printf("    Gaps: ");
            for (int i = 1; i < at.nIE; i++) {
                double ratio = at.IE[i] / at.IE[i-1];
                std::printf("IE%d/IE%d=%.2f ", i+1, i, ratio);
            }
            std::printf("\n");
        }
        std::printf("\n");
    }

    // ═══════════════════════════════════════════════════
    //  PART 2: EXCITATION SLOWS ROTATION
    //  Keplerian: moving to wider orbit = slower velocity
    //  = less angular momentum contribution to the atom
    // ═══════════════════════════════════════════════════
    std::printf("╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  PART 2: DOES EXCITATION SLOW THE WHOLE ATOM?              ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    std::printf("  Movement budget: v_circ² + v_trans² = c²\n");
    std::printf("  In bound state: v_orbital IS v_trans (the electron's\n");
    std::printf("  circulation around the nucleus is its translational\n");
    std::printf("  velocity in the atomic frame).\n\n");
    std::printf("  v_circ = internal vortex circulation of the electron.\n");
    std::printf("  When electron is excited: v_orbital decreases\n");
    std::printf("  (SDT orbital velocity law: wider void = lower velocity).\n");
    std::printf("  Therefore v_circ INCREASES (movement budget conservation).\n\n");
    std::printf("  But the ORBITAL angular momentum L = m_e × v × r decreases?\n");
    std::printf("  Let's check. Bohr: v_n ∝ 1/n, r_n ∝ n², so L_n ∝ n.\n");
    std::printf("  ANGULAR MOMENTUM INCREASES with excitation level.\n\n");

    std::printf("  Hydrogen ground → excited:\n");
    std::printf("  %3s  %10s  %10s  %10s  %10s  %10s\n",
        "n","v/c","v_circ/c","r(pm)","L(ℏ)","ΔL/L₁");
    for (int n = 1; n <= 7; n++) {
        double v = K::c / (n * K::k_H);  // v_n = αc/n
        double vc = v_circ(v);
        double r = 52.918 * n * n;  // pm, Bohr radius × n²
        double L = n;  // L = nℏ
        std::printf("  %3d  %10.6f  %10.8f  %10.1f  %10.1f  %+9.1f%%\n",
            n, v/K::c, vc/K::c, r, (double)n, 100.0*(n-1));
    }

    std::printf("\n  RESULT: excitation INCREASES orbital angular momentum.\n");
    std::printf("  The electron moves slower but further out → net L increase.\n");
    std::printf("  The vortex circulation v_circ barely changes (Δ < 0.003%%)\n");
    std::printf("  because v << c for all bound states.\n\n");

    std::printf("  SDT interpretation: the nuclear toroidal wake (Reciprocal\n");
    std::printf("  Drive) couples to the electron at each void position.\n");
    std::printf("  When the electron moves to a higher void, the coupling\n");
    std::printf("  weakens (further from nucleus = weaker wake). The nucleus\n");
    std::printf("  experiences LESS drag → its own circulation doesn't slow.\n");
    std::printf("  The atom's TOTAL angular momentum budget redistributes:\n");
    std::printf("  more in electron orbital, less in nuclear wake coupling.\n");

    // ═══════════════════════════════════════════════════
    //  PART 3: MULTI-ELECTRON EXCITATION
    //  Can two electrons excite without ionising?
    // ═══════════════════════════════════════════════════
    std::printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  PART 3: MULTI-ELECTRON EXCITATION WITHOUT IONISATION      ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    std::printf("  Question: can two electrons excite simultaneously\n");
    std::printf("  with total energy BELOW the first ionisation energy?\n\n");

    // He: IE₁ = 24.587 eV. First excitation = 19.82 eV (orthohelium).
    // If BOTH electrons excite: E_total = 2 × E_exc.
    // For He, the first excitation to 2³S is 19.82 eV.
    // 19.82 > 24.587? No: 19.82 < 24.587.
    // But what about exciting the SECOND electron once the first is at 2s?
    // The remaining electron sees Z=2 with no other electron → hydrogenic.
    // Its binding from 1s in He+ = 54.418 eV. Excitation 1→2 costs
    // 54.418 × (1 - 1/4) = 40.81 eV. Total = 19.82 + 40.81 = 60.63 eV.
    // But IE₁ = 24.587 eV. So 19.82 + 40.81 >> 24.587.
    // The SECOND excitation costs more than full ionisation!

    struct ExcData {
        const char* sym;
        int Z;
        double IE1;
        double first_exc;
        double IE2;
        const char* state;
    };

    ExcData exc[] = {
        {"He", 2, 24.587, 19.820, 54.418, "2³S₁ orthohelium"},
        {"Li", 3,  5.392,  1.848, 75.640, "2s→2p"},
        {"Be", 4,  9.323,  2.725, 18.211, "2s²→2s2p ³P°"},
        {"C",  6, 11.260,  1.264, 24.384, "2p²→2p3s"},
        {"Ne",10, 21.565, 16.619, 40.963, "2p⁶→2p⁵3s"},
        {"Na",11,  5.139,  2.104, 47.286, "3s→3p (D-lines)"},
        {"Ar",18, 15.760, 11.548, 27.630, "3p⁶→3p⁵4s"},
    };
    int n_exc = sizeof(exc)/sizeof(exc[0]);

    std::printf("  %-4s  %7s  %7s  %7s  %7s  %7s  %s\n",
        "Atom","IE₁","E_exc1","IE₂","2×E_exc","IE₁-E₁","Doubly possible?");
    std::printf("  ────────────────────────────────────────────────────────────────\n");

    for (int i = 0; i < n_exc; i++) {
        auto& e = exc[i];
        double two_exc = 2.0 * e.first_exc;
        double remaining = e.IE1 - e.first_exc;
        // NECESSARY (not sufficient) condition for double excitation:
        // E_exc1 + E_exc2 < IE₁. Simplified: if both excitations
        // cost the same, then E_exc < IE₁/2.
        // Sufficient conditions also require:
        //   - both excited voids are pressure-balanced
        //   - wake coupling remains closed
        //   - no lower extraction channel opens (no autoionisation)
        bool possible = (e.first_exc < e.IE1 / 2.0);

        std::printf("  %-4s  %7.3f  %7.3f  %7.3f  %7.3f  %7.3f  %s\n",
            e.sym, e.IE1, e.first_exc, e.IE2,
            two_exc, remaining,
            possible ? "POSSIBLE (E_exc < IE₁/2)" : "NO (E_exc > IE₁/2)");
    }

    std::printf("\n  ENERGY BUDGET (necessary condition):\n");
    std::printf("  E_exc1 + E_exc2 < IE₁ is NECESSARY but NOT SUFFICIENT.\n");
    std::printf("  Also required: both excited voids pressure-balanced,\n");
    std::printf("  wake coupling closed, no autoionising channel open.\n\n");
    std::printf("  Li: E_exc = 1.85 eV << IE₁/2 = 2.70 eV → energy allows\n");
    std::printf("  Be: E_exc = 2.73 eV << IE₁/2 = 4.66 eV → energy allows\n");
    std::printf("  Na: E_exc = 2.10 eV << IE₁/2 = 2.57 eV → energy allows\n");
    std::printf("  He: E_exc = 19.82 eV > IE₁/2 = 12.29 eV → energy forbids\n\n");

    std::printf("  SDT interpretation: doubly-excited states exist when\n");
    std::printf("  the lowest excitation void is geometrically CLOSE to\n");
    std::printf("  the ground void (small energy gap). Alkali metals and\n");
    std::printf("  alkaline earths allow this (loose gears, low ρ).\n");
    std::printf("  Noble gases do NOT (rigid gears, high ρ = E_exc/IE ≈ 0.77).\n\n");

    std::printf("  Helium is special: its ONLY excitation (orthohelium)\n");
    std::printf("  costs 80%% of IE₁. No room for a second excitation.\n");
    std::printf("  This is why helium has no bound doubly-excited states —\n");
    std::printf("  all doubly-excited He states are ABOVE IE₁ and autoionise.\n");

    // ═══════════════════════════════════════════════════
    //  PART 4: THE CORRECT EMISSION PICTURE
    // ═══════════════════════════════════════════════════
    std::printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  PART 4: THE CORRECT SDT EMISSION PICTURE                  ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    std::printf("  1. The nucleus (exclusion volume) creates a convergent\n");
    std::printf("     pressure deficit in specific directions.\n\n");
    std::printf("  2. This deficit creates geometric voids — positions where\n");
    std::printf("     an electron (W=1 vortex) can be pressure-balanced.\n\n");
    std::printf("  3. Each void has a specific binding energy = the integral\n");
    std::printf("     of the convergent pressure deficit at that position.\n\n");
    std::printf("  4. The electron doesn't orbit due to a 'force'. It is\n");
    std::printf("     mechanically driven by the nuclear toroidal wake\n");
    std::printf("     (Reciprocal Drive, Atomicus Rule §14).\n\n");
    std::printf("  5. Excitation = photon pushes electron to a higher void.\n");
    std::printf("     Higher void = wider radius = lower orbital velocity\n");
    std::printf("     (SDT velocity law). Energy difference → photon.\n\n");
    std::printf("  6. De-excitation = electron falls to lower void.\n");
    std::printf("     Emits photon with E = ½m_e(v_low² - v_high²).\n\n");
    std::printf("  7. No Z_eff. No shielding. Each void has its own\n");
    std::printf("     convergent pressure binding.\n\n");
    std::printf("  CRITICAL DISTINCTION:\n");
    std::printf("  Sequential IE values are extraction-depths of pressure\n");
    std::printf("  wells from successively changed ionic states. They are\n");
    std::printf("  NOT automatically transition energies.\n\n");
    std::printf("  Emission energies require two BOUND void states in the\n");
    std::printf("  SAME charge configuration:\n");
    std::printf("    E_γ = |B(void_a; charge_state) - B(void_b; charge_state)|\n");
    std::printf("    λ = hc / E_γ\n\n");

    // Demonstrate with He: orthohelium transition
    double He_IE1 = 24.587;
    double He_exc = 19.820;
    double He_E_photon = He_exc;
    double He_lam = K::h * K::c / (He_E_photon * K::eV_J) * 1e9;
    std::printf("  Example — Helium orthohelium decay:\n");
    std::printf("    IE₁ = %.3f eV, excitation energy = %.3f eV\n", He_IE1, He_exc);
    std::printf("    Photon: E = %.3f eV → λ = %.2f nm (NIST: 62.56 nm)\n\n", He_E_photon, He_lam);

    // Na D-lines
    double Na_exc = 2.104;
    double Na_lam = K::h * K::c / (Na_exc * K::eV_J) * 1e9;
    std::printf("  Example — Sodium D-line:\n");
    std::printf("    3s→3p excitation = %.3f eV\n", Na_exc);
    std::printf("    Photon: E = %.3f eV → λ = %.1f nm (NIST: 589.0 nm)\n", Na_exc, Na_lam);

    // ═══════════════════════════════════════════════════
    //  SUMMARY
    // ═══════════════════════════════════════════════════
    std::printf("\n══════════════════════════════════════════════════════════════\n");
    std::printf("  CORRECTION APPLIED:\n\n");
    std::printf("  OLD (wrong): nucleus emits field → electrons shield it\n");
    std::printf("               → Z_eff = Z - σN\n\n");
    std::printf("  NEW (correct): convergent pressure arrives from 4π sr\n");
    std::printf("                 → nucleus occludes a solid angle\n");
    std::printf("                 → electrons sit in pressure-balanced voids\n");
    std::printf("                 → each void has its own binding energy\n");
    std::printf("                 → transitions between voids = photons\n\n");
    std::printf("  Excitation INCREASES orbital angular momentum (L = nℏ).\n");
    std::printf("  Excitation DECREASES orbital velocity (wider void).\n");
    std::printf("  Excitation BARELY changes v_circ (v << c for all states).\n");
    std::printf("  Nuclear rotation is NOT slowed — wake coupling weakens.\n\n");
    std::printf("  Multi-electron excitation is possible for loose-gear\n");
    std::printf("  atoms (Li, Be, Na) where E_exc < IE₁/2.\n");
    std::printf("  Impossible for rigid-gear atoms (He, Ne, Ar) where\n");
    std::printf("  E_exc ≈ 0.8 × IE₁.\n");

    return 0;
}
