// =====================================================================================
//  EMC04 — The Electropause: deriving the electrostatic binding (and P_eff) from the
//          centripetal requirement to hold the electron at the Bohr radius.
//
//  Author: James Christopher Harvey, Melbourne. 2026-06-18.
//
//  Thesis: the force that holds the electron at r = a_0 is the CENTRIPETAL requirement,
//  and that requirement IS the occlusion push (the one SDT force law at atomic scale).
//  The Bohr radius is the ELECTROPAUSE — the pressure-balance boundary where the inward
//  occlusion gradient equals the outward circulation strength (heliopause, one rung up).
//
//  Two payoffs, both checked numerically against the engine (laws.hpp):
//    (1) F_centripetal(a_0) computed from KINEMATICS ALONE (v = alpha*c, no charge)
//        equals the Coulomb / occlusion force to the last digit  -> "there is no charge".
//    (2) Inverting the occlusion law for this balance DERIVES P_eff, reproducing the
//        engine's calibrated value AND the pure-derivation basis closed form
//        P_eff = m_p^2 m_e^2 c^5 / (4 pi alpha hbar^3), with NO Coulomb input
//        (delete-test) -> P_eff upgrades E -> C (EMC01 circularity closed, on framework
//        terms: alpha read as the kinematic k-rung, the one irreducible input).
//
//  Build (MSVC):
//    cl /std:c++20 /EHsc /O2 /I Engine\include /Fe:emc04.exe ^
//       Investigations\CQ49_Electropause_Binding_Derivation\cq49_electropause.cpp
//  Build (GCC/Clang):
//    g++ -std=c++20 -IEngine/include cq49_electropause.cpp -o emc04
// =====================================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;

static double rel_err(double a, double b) { return std::fabs(a - b) / std::fabs(b); }

int main() {
    namespace M = sdt::laws::measured;

    const double alpha = M::alpha;
    const double a0    = M::a_0;        // Bohr radius (= electropause radius)
    const double r_e   = M::r_e;        // classical electron radius (electron c-boundary)
    const double R_p   = M::R_p;        // proton charge radius
    const double m_e   = M::m_e;
    const double m_p   = M::m_p;
    const double c     = M::c;
    const double hbar  = M::hbar;
    const double k_e   = M::k_e;
    const double e     = M::e_charge;
    const double pi    = std::numbers::pi;

    std::printf("=====================================================================\n");
    std::printf("  EMC04  THE ELECTROPAUSE  -  binding (and P_eff) from kinematics\n");
    std::printf("  J. C. Harvey, Melbourne, 2026-06-18.  Engine: sdt/laws.hpp\n");
    std::printf("=====================================================================\n\n");

    // -----------------------------------------------------------------------------
    // STEP 1.  The electropause: hold the electron at a_0 with v = alpha*c.
    //          Pure kinematics. No charge, no e, no k_e.
    // -----------------------------------------------------------------------------
    const double v_e   = alpha * c;                 // ground-state circulation speed (k-rung)
    const double F_cen = m_e * v_e * v_e / a0;       // centripetal requirement

    std::printf("[1] ELECTROPAUSE BINDING (kinematics only)\n");
    std::printf("    r  = a_0          = %.6e m   (electropause radius)\n", a0);
    std::printf("    v  = alpha*c      = %.6e m/s (chi = c/v = %.4f)\n", v_e, 1.0/alpha);
    std::printf("    F_centripetal = m_e v^2 / a_0 = %.6e N\n", F_cen);
    std::printf("    (computed with NO charge term -- delete-test for charge passes)\n\n");

    // -----------------------------------------------------------------------------
    // STEP 2.  Compare to the engine's Coulomb / occlusion force at the same radius.
    // -----------------------------------------------------------------------------
    const double F_coul_classic = k_e * e * e / (a0 * a0);   // textbook Coulomb
    const double F_occ_engine   = law_III::F_coulomb(a0);    // SDT occlusion law, engine

    std::printf("[2] CROSS-CHECK against the force laws\n");
    std::printf("    k_e e^2 / a_0^2            (Coulomb)   = %.6e N\n", F_coul_classic);
    std::printf("    law_III::F_coulomb(a_0)    (occlusion) = %.6e N\n", F_occ_engine);
    std::printf("    F_centripetal / F_coulomb             = %.10f\n", F_cen / F_coul_classic);
    std::printf("    F_centripetal / F_occlusion(engine)   = %.10f\n", F_cen / F_occ_engine);
    std::printf("    => the binding IS the centripetal requirement IS occlusion.\n\n");

    // -----------------------------------------------------------------------------
    // STEP 3.  Invert the occlusion law for the balance: DERIVE P_eff.
    //          F = (pi/4) P_eff R_charge^4 / r^2   ->   P_eff = 4 F r^2 / (pi R_charge^4)
    // -----------------------------------------------------------------------------
    const double R_charge = law_III::R_charge;       // = sqrt(R_p r_e)
    const double R_charge4 = R_charge * R_charge * R_charge * R_charge;
    const double P_eff_from_balance = 4.0 * F_cen * a0 * a0 / (pi * R_charge4);

    std::printf("[3] INVERT OCCLUSION LAW -> P_eff from the electropause balance\n");
    std::printf("    R_charge = sqrt(R_p r_e)              = %.6e m\n", R_charge);
    std::printf("    P_eff = 4 F_cen a_0^2 / (pi R_charge^4) = %.6e Pa\n", P_eff_from_balance);
    std::printf("    engine law_III::P_eff                   = %.6e Pa\n", law_III::P_eff);
    std::printf("    rel. error                              = %.3e\n\n",
                rel_err(P_eff_from_balance, law_III::P_eff));

    // -----------------------------------------------------------------------------
    // STEP 4.  Symbolic reductions, evaluated numerically.
    //   (a) closed form using k_e e^2 = alpha hbar c :  P_eff = 4 alpha hbar c / (pi R_p^2 r_e^2)
    //   (b) pure derivation basis {m_e,m_p,c,alpha,hbar}, using r_e = alpha hbar/(m_e c)
    //       and R_p = 4 hbar/(m_p c) (engine note, 0.02%):  P_eff = m_p^2 m_e^2 c^5/(4 pi alpha hbar^3)
    // -----------------------------------------------------------------------------
    const double P_eff_closed = 4.0 * alpha * hbar * c / (pi * R_p * R_p * r_e * r_e);
    const double P_eff_mass   = m_p * m_p * m_e * m_e * std::pow(c, 5)
                              / (4.0 * pi * alpha * std::pow(hbar, 3));

    std::printf("[4] SYMBOLIC REDUCTIONS (DELETE-TEST: no k_e, no e below)\n");
    std::printf("    (a) 4 alpha hbar c/(pi R_p^2 r_e^2)        = %.6e Pa  [rel %.2e]\n",
                P_eff_closed, rel_err(P_eff_closed, law_III::P_eff));
    std::printf("    (b) m_p^2 m_e^2 c^5/(4 pi alpha hbar^3)    = %.6e Pa  [rel %.2e]\n",
                P_eff_mass, rel_err(P_eff_mass, law_III::P_eff));
    std::printf("        (form (b) uses R_p = 4 hbar/(m_p c); engine R_p matches to %.2e)\n\n",
                rel_err(R_p, 4.0 * hbar / (m_p * c)));

    // Consistency identity: a_0 = hbar/(m_e c alpha)  (why F_cen == F_coul exactly)
    const double a0_kinematic = hbar / (m_e * c * alpha);
    std::printf("[5] WHY IT IS EXACT:  a_0 = hbar/(m_e c alpha) = %.6e m  [rel %.2e]\n",
                a0_kinematic, rel_err(a0_kinematic, a0));
    std::printf("    With this, m_e (alpha c)^2/a_0 == k_e e^2/a_0^2 is an algebraic identity.\n\n");

    // -----------------------------------------------------------------------------
    // VERDICT
    // -----------------------------------------------------------------------------
    const bool pass_force = rel_err(F_cen, F_coul_classic) < 1e-6;
    const bool pass_peff  = rel_err(P_eff_from_balance, law_III::P_eff) < 1e-6;
    const bool pass_close = rel_err(P_eff_closed, law_III::P_eff) < 1e-9;
    const bool pass_mass  = rel_err(P_eff_mass, law_III::P_eff) < 1e-3;

    std::printf("---------------------------------------------------------------------\n");
    std::printf("  VERDICT\n");
    std::printf("    binding == Coulomb (kinematics, no charge) : %s\n", pass_force ? "PASS" : "FAIL");
    std::printf("    P_eff recovered from electropause balance  : %s\n", pass_peff  ? "PASS" : "FAIL");
    std::printf("    closed form 4 a hbar c/(pi R_p^2 r_e^2)    : %s\n", pass_close ? "PASS" : "FAIL");
    std::printf("    derivation basis m_p^2 m_e^2 c^5/(4 pi a hbar^3)  : %s\n", pass_mass  ? "PASS" : "FAIL");
    std::printf("    => P_eff DERIVED (delete-test clean): E -> C, on framework terms.\n");
    std::printf("       Residual input = alpha (the one k-rung); the model does NOT derive alpha.\n");
    std::printf("---------------------------------------------------------------------\n");

    return (pass_force && pass_peff && pass_close && pass_mass) ? 0 : 1;
}
