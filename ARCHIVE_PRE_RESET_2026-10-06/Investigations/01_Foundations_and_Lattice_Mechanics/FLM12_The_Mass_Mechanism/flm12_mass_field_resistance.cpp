// ============================================================================
//  FLM12 — The Mass Mechanism: Field-Resistance to Change of Form
//  Grounding tool. Prints every mass-relevant CODATA anchor with its
//  field-as-resistance reading and an HONEST label:
//     [DISSOLVED] [NATIVE] [RE-DESCRIPTION] [OPEN] [RESOLVED]
//
//  This tool does NOT derive mass values. It (a) shows the confinement
//  objection that forces the field-as-resistance ontology, (b) lists the
//  anomaly anchors the mechanism must explain, and (c) states, per item,
//  whether the mechanism dissolves it, reads it natively, merely
//  re-describes it, or leaves it open. See FLM12_MASS_MECHANISM.md.
//
//  Build (MSVC):  cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include ^
//                    Investigations\01_Foundations_and_Lattice_Mechanics\FLM12_The_Mass_Mechanism\flm12_mass_field_resistance.cpp
//  Build (GCC) :  g++ -std=c++20 -IEngine/include flm12_mass_field_resistance.cpp -o flm12
//
//  Author: J. C. Harvey, Melbourne.
// ============================================================================
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;

int main() {
    const double hbarc_MeVfm = 197.3269804;      // ℏc [MeV·fm]
    const double u_MeV       = 931.49410242;     // atomic mass unit [MeV/c²]
    const double mec2        = 0.51099895000;    // [MeV]
    const double mpc2        = 938.27208816;     // [MeV]
    const double mnc2        = 939.56542052;     // [MeV]

    printf("================================================================\n");
    printf(" FLM12 — THE MASS MECHANISM : field-resistance to change of form\n");
    printf("================================================================\n\n");

    // ---- PART I : the clue that forces the ontology --------------------------
    printf("PART I  —  WHY MASS CANNOT BE A LOCALISED SUBSTANCE\n");
    printf("--------------------------------------------------\n");
    printf(" Confinement cost of localising an electron to size dx  =  hbar*c/dx :\n");
    struct Loc { const char* where; double dx_fm; };
    Loc L[] = { {"proton R_p (neutron seat)", measured::R_p*1e15},
                {"deuteron gap (NP17)",        1.94},
                {"trefoil node",               0.28} };
    for (auto& x : L)
        printf("   dx = %5.2f fm  (%-26s) : %7.1f MeV\n", x.dx_fm, x.where, hbarc_MeVfm/x.dx_fm);
    printf("   ...vs the 0.8-2.2 MeV bindings they must supply  => 50-300x too big.\n");
    printf("   => mass is NOT carried by a localised particle. It is a property of\n");
    printf("      the FIELD (the convergent influx), scaled by the form. [ontology forced]\n\n");

    printf(" Consonance check (RESOLVED, not anomalous): SDT R_p = (W+1)*hbar/(m_p c), W=3\n");
    double reduced_Cp = measured::hbar/(measured::m_p*measured::c);   // reduced Compton [m]
    printf("   4*hbar/(m_p c) = %.4f fm   vs measured R_p = %.4f fm  (muonic value)\n",
           4.0*reduced_Cp*1e15, measured::R_p*1e15);
    printf("\n");

    printf(" The mechanism (Steps 1-9, see .md):\n");
    printf("   Newton I  : rest in isotropic influx -> no net force.\n");
    printf("   Newton II : acceleration -> relay-Doppler imbalance of the discrete\n");
    printf("               influx -> F = m*a ;  m = the field's push-back coefficient.\n");
    printf("   E=mc^2    : one field-engagement read as resistance (m) or throughput (E).\n");
    printf("   m_inert == m_grav : both are 'how much influx the form engages' [THEOREM].\n");
    printf("   mass defect = field-resistance SAVED when two forms synchronise.\n\n");

    // ---- PART II : the anomaly scope ---------------------------------------
    printf("PART II  —  CODATA ANOMALY SCOPE (honestly sorted)\n");
    printf("-------------------------------------------------\n\n");

    printf("[DISSOLVED]  A1 Equivalence principle: m_inert=m_grav to eta<1e-15 (MICROSCOPE)\n");
    printf("             -> a THEOREM here (one field-engagement), GR must postulate it. [the win]\n");
    printf("[DISSOLVED]  A2 mass<->energy 'without mechanism' -> one substrate, two readings.\n");
    printf("[DISSOLVED]  A3 'no electrons in the nucleus' (confinement) -> no localised carrier.\n");
    printf("[DISSOLVED]  A4 vacuum-energy catastrophe ~1e123 -> category error: no energy\n");
    printf("             substance is posited; empty isotropic influx exerts no net force.\n");
    printf("[DISSOLVED*] A5 muon g-2: 2025 result AGREES with lattice SM; residual ~5sigma is\n");
    printf("             lattice-vs-data-driven HADRONIC VACUUM POLARISATION = how you compute\n");
    printf("             the FIELD. Consonant. (*SDT does not yet compute a_mu -> number OPEN.)\n\n");

    printf("[NATIVE]     B1 magnetic carriers are always the loose electrons (least-gripped=most flux)\n");
    printf("[NATIVE]     B2 neutron moment is NEGATIVE not zero (counter-synchrony)  [mag. OPEN]\n");
    printf("[NATIVE]     B3 proton mu_p=+2.793 not 1 (W=3 trefoil, not a point)      [val. OPEN]\n");
    // binding curve as a resistance landscape
    auto binding_per_A = [&](double dm_u, int A){ return dm_u*u_MeV/A; };
    double B_d  = binding_per_A(1.00782503207+1.008664916-2.014101778, 2);
    double B_he = binding_per_A(2*1.00782503207+2*1.008664916-4.002603254, 4);
    double B_fe = binding_per_A(26*1.00782503207+30*1.008664916-55.93493633, 56);
    double B_u  = binding_per_A(92*1.00782503207+146*1.008664916-238.0507882, 238);
    printf("[NATIVE]     B4 binding curve = resistance landscape, Fe/Ni = the floor:\n");
    printf("                d=%.3f  He4=%.3f  Fe56=%.3f  U238=%.3f  MeV/nucleon\n",
           B_d, B_he, B_fe, B_u);
    printf("                fusion(light)+fission(heavy) both run downhill to Fe. [iron floor OWED]\n\n");

    // Koide
    double me=mec2, mmu=105.6583755, mtau=1776.86;
    double Q = (me+mmu+mtau)/std::pow(std::sqrt(me)+std::sqrt(mmu)+std::sqrt(mtau),2);
    printf("[RE-DESCR]   C1 Koide Q = %.6f  (~2/3 = %.6f, to 1e-5): 3 leptons = 3 W=1 harmonics\n", Q, 2.0/3.0);
    printf("                -> motivates combining sqrt(m), but 2/3 NOT derived. [target]\n");
    printf("[RE-DESCR]   C2 lepton ratios m_mu/m_e=%.2f  m_tau/m_e=%.1f : harmonics, not derived\n", mmu/me, mtau/me);
    double ratio = measured::m_p/measured::m_e;
    double sixpi5 = 6.0*std::pow(std::numbers::pi,5);
    printf("[RE-DESCR]   C3 m_p/m_e = %.5f  vs 6*pi^5 = %.5f  (%.1f ppm): W=3/W=1 engagement\n",
           ratio, sixpi5, std::fabs(ratio-sixpi5)/ratio*1e6);
    printf("                ratio -> field-as-resistance HOUSES 6pi^5; mechanism [OPEN] (PPT07)\n");
    printf("[RE-DESCR]   C4 exact mu_n=-1.913, Q_beta=%.4f MeV from one seat geometry [OWED, doc-05]\n\n",
           mnc2-mpc2-mec2);

    printf("[OPEN]       D1 deuteron binding %.3f MeV *from* the synchrony overlap  <-- PRIORITY test\n", B_d);
    printf("[OPEN]       D2 the iron floor, COMPUTED (one-parameter landscape, exponent from geometry)\n");
    printf("[OPEN]       D3 neutron tau=880 s + beam/bottle ~4sigma: barrier B; rate = SDT's G_F\n");
    printf("[OPEN]       D4 alpha Cs vs Rb ~5.4sigma (137.035999046 vs 206): which recoil is right?\n");
    printf("[OPEN]       D5 neutrino oscillation (nonzero mass, flavour cycling): HARDEST, unaddressed\n\n");

    printf("[RESOLVED]   E1 W mass: CDF-2022 (80433) isolated; ATLAS/CMS (80360) on SM (80357). Not anomalous.\n");
    printf("[RESOLVED]   E2 proton radius 'puzzle' resolved to muonic 0.8414 fm = SDT R_p. Check passed.\n\n");

    printf("----------------------------------------------------------------\n");
    printf(" VERDICT: mechanism DETERMINED (what mass is); values OWED (D1,D2).\n");
    printf("   SM mass MYSTERIES dissolve; SM mass NUMBERS housed-not-derived;\n");
    printf("   oscillation / alpha-split / G_F stay open and named.\n");
    printf("----------------------------------------------------------------\n");
    return 0;
}
