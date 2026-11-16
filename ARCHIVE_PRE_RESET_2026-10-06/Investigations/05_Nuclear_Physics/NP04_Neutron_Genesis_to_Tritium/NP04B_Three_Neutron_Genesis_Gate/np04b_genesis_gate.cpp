// ============================================================================
//  NP04B — Three-Neutron Genesis Gate
//  Tests  3n -> triton + e- + nu_bar  on TWO separate gates:
//    F0  energy gate  (PASS, exothermic)
//    F0b kinetic gate (UNRESOLVED — energy allowed, rate not predicted)
//  Consumes laws.hpp; never fabricates a rate.
//
//  Build:  cl /std:c++20 /EHsc /O2 /I Engine/include \
//             Investigations/CQ29_Neutron_Genesis_to_Tritium/CQ29B_Three_Neutron_Genesis_Gate/cq29b_genesis_gate.cpp /Fe:np04b.exe
//  Author: SDT Canonical Engine — James Tyndall, Melbourne.
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>

using namespace sdt::laws;
static double MeVof(double m_kg){ return m_kg * measured::c * measured::c / measured::MeV_to_J; }
static void banner(const char* s){
    std::printf("\n============================================================\n  %s\n============================================================\n", s);
}

int main(){
    const double m_n = MeVof(measured::m_n);
    const double m_p = MeVof(measured::m_p);
    const double m_e = MeVof(measured::m_e);
    const double Qn  = m_n - m_p - m_e;
    const double Bd  = measured::B_deuteron;   // 2.224 MeV
    const double Bt  = measured::B_triton;     // 8.482 MeV
    const double Q3n = Qn + Bt;

    std::printf("NP04B - THREE-NEUTRON GENESIS GATE  (3n -> triton + e + nu_bar)\n");
    std::printf("Two gates, never conflated: F0 energy (answerable) ; F0b kinetics (not yet).\n");

    // ── F0 — ENERGY GATE ────────────────────────────────────────────────────
    banner("STAGE F0 - 3n -> triton + e + nu_bar : genesis ENERGY gate");
    std::printf("  Q(3n -> t + e + nu_bar) = Q_n + B(t)\n");
    std::printf("                          = %.4f + %.4f = %.4f MeV\n", Qn, Bt, Q3n);
    std::printf("  ENERGY GATE: %s (exothermic by %.3f MeV)\n", Q3n>0?"PASS":"FAIL", Q3n);

    // sequential decomposition (di-neutron unbound => must route through a proton)
    const double s1 = Qn, s2 = Bd, s3 = Bt - Bd;
    std::printf("\n  Sequential path (di-neutron UNBOUND -> proton is the obligatory keystone):\n");
    std::printf("    step 1  n -> p + e + nu_bar   = %+0.3f MeV   (rate-limiting: tau_n ~ 880 s)\n", s1);
    std::printf("    step 2  p + n -> d + gamma     = %+0.3f MeV   (radiative capture)\n", s2);
    std::printf("    step 3  d + n -> t + gamma     = %+0.3f MeV   (radiative capture)\n", s3);
    std::printf("    --------------------------------------------------\n");
    std::printf("    sum = %.4f MeV   vs   F0 = %.4f MeV   %s (no double-count)\n",
        s1+s2+s3, Q3n, (std::fabs((s1+s2+s3)-Q3n)<1e-6)?"OK":"MISMATCH");

    // ── F0b — KINETIC GATE ──────────────────────────────────────────────────
    banner("STAGE F0b - 3n capture KINETICS : UNRESOLVED");
    std::printf("  Energy availability says NOTHING about rate. F0b requires (NOT yet derived):\n");
    std::printf("    - 3-body simultaneity / density   (three neutrons must coincide; rare when dilute)\n");
    std::printf("    - weak split timing               (step 1 gated by tau_n ~ 880 s; neutrons decay/escape)\n");
    std::printf("    - proton-keystone routing         (di-neutron unbound => no n+n build-up; must go via p)\n");
    std::printf("    - radiative-capture cross-sections (steps 2-3; BBN/stellar regime; not in occlusion units)\n");
    std::printf("  KINETIC GATE: UNRESOLVED  [F0b, class F]\n");

    // ── VERDICT ─────────────────────────────────────────────────────────────
    banner("VERDICT");
    std::printf("  energetics : ALLOWED  (Q = %.3f MeV > 0)        [F0  class C-flagged]\n", Q3n);
    std::printf("  kinetics   : NOT PREDICTED (rate/probability)    [F0b class F]\n");
    std::printf("\n[NP04B done]  energy gate closes; genesis rate remains an open problem.\n");
    return 0;
}
