// ============================================================================
//  FLM09 — Reconnection Dynamics: the Light Mode and the Boundary Arrival
//  J. C. Harvey, Melbourne — 2026-06-24
//
//  Arms kept SEPARATE per the charter. This tool currently computes only
//  ARM A step A1'' (the bond-switch saturation / opacity threshold). A2 (the
//  amorphous dispersion) and ARM B (the CMB boundary arrival) are flagged
//  [OPEN — pending] and print nothing numeric — by design, so the local score
//  and the cosmological score are never summed.
//
//  Build (from repo root):
//    cl /std:c++20 /EHsc /O2 /I Engine\include ^
//       Investigations\01_Foundations_and_Lattice_Mechanics\FLM09_Reconnection_Light_and_CMB_Arrival\flm09_reconnection.cpp
//    g++ -std=c++20 -IEngine/include <path>/flm09_reconnection.cpp -o flm09_reconnection
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

int main() {
    using namespace sdt::laws::measured;

    const double lam_C = hbar / (m_e * c);        // electron Compton length = the W=1 defect scale
    const double r_e   = 2.8179403262e-15;        // classical electron radius (reference length only)

    // The "nucleation field": the field whose work over a length L, on charge e,
    // reaches the relay quantum hbar*c/L of a defect of that size.
    auto E_of_L = [&](double L) { return hbar * c / (e_charge * L * L); };

    const double E_S_direct = m_e * m_e * c * c * c / (e_charge * hbar);  // Schwinger, standard form
    const double E_S_form   = E_of_L(lam_C);                              // same, written hbar*c/(e L^2)
    const double E_lattice  = E_of_L(l_P);                                // bare-lattice (Planck) ceiling
    const bool   self_ok    = std::fabs(E_S_form / E_S_direct - 1.0) < 1e-9;

    std::printf("============================================================\n");
    std::printf(" FLM09  ARM A — the light mode (local reconnection)\n");
    std::printf("   A1''  bond-switch saturation / opacity threshold\n");
    std::printf("============================================================\n");
    std::printf("  CLAIM: the medium goes opaque when the field nucleates a real defect.\n");
    std::printf("  ONE FORM:  E(L) = hbar*c / (e * L^2),  L = nucleating-defect size.\n\n");

    std::printf("  electron Compton   lam_C = hbar/(m_e c)  = %.4e m\n", lam_C);
    std::printf("  Schwinger (standard)  m_e^2 c^3/(e hbar) = %.4e V/m\n", E_S_direct);
    std::printf("  Schwinger (as form)   hbar c/(e lam_C^2) = %.4e V/m\n", E_S_form);
    std::printf("  self-consistency ratio                   = %.6f  [%s]\n\n",
                E_S_form / E_S_direct, self_ok ? "PASS" : "FAIL");

    std::printf("  threshold vs nucleating-defect length L:\n");
    std::printf("    L = lam_C (electron / W=1 defect)  %.3e m  ->  E = %.3e V/m\n", lam_C, E_of_L(lam_C));
    std::printf("    L = r_e   (classical e- radius)    %.3e m  ->  E = %.3e V/m\n", r_e,   E_of_L(r_e));
    std::printf("    L = l_P   (bare lattice ceiling)   %.3e m  ->  E = %.3e V/m\n", l_P,   E_lattice);
    std::printf("\n");

    std::printf("  FINDING — two distinct scales:\n");
    std::printf("   * observed vacuum nonlinearity (Schwinger) = ELECTRON-defect scale (L=lam_C).\n");
    std::printf("   * bare-lattice saturation (L=l_P) is %.2e x higher — a ceiling, NOT Schwinger.\n",
                E_lattice / E_S_form);
    std::printf("   => opacity onset is governed by nucleating the W=1 (electron) defect, not the\n");
    std::printf("      bare hinge lattice. SDT recovers E_S by that identification; the number is\n");
    std::printf("      all-whitelist (m_e,c,hbar,e) — inherited, not newly derived.\n\n");

    std::printf("  LEDGER (ARM A, A1''):\n");
    std::printf("    [FORM]           E(L) = hbar*c/(e L^2)   (threshold shape)\n");
    std::printf("    [IDENTIFICATION] opacity defect = the electron (W=1), L = lam_C\n");
    std::printf("    [INHERITED]      E_S = 1.323e18 V/m      (standard, all-whitelist)\n");
    std::printf("    [KILLED]         'bare-lattice saturation = Schwinger'  (off by %.0e)\n\n",
                E_lattice / E_S_form);

    std::printf("------------------------------------------------------------\n");
    std::printf(" FLM09  ARM A — A2 dispersion omega(k)      [OPEN — pending step 1]\n");
    std::printf(" FLM09  ARM B — CMB boundary arrival        [OPEN — separate ledger]\n");
    std::printf("------------------------------------------------------------\n");

    return self_ok ? 0 : 1;
}
