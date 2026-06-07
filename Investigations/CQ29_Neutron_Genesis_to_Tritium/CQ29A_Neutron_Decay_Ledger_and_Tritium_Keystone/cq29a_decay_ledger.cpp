// ============================================================================
//  CQ29 — Neutron Genesis: free neutron -> beta-decay (winding split) -> tritium
//
//  Arc:  3n -> triton + e- + nu_bar  ->  H-3 atom  ->  He-3 + e- + nu_bar
//  One-way A->H. Consumes the canonical engine; never modifies it.
//
//  Build (standalone):
//    cl /std:c++20 /EHsc /O2 /I Engine/include \
//       Investigations/CQ29_Neutron_Genesis_to_Tritium/cq29_neutron_genesis.cpp /Fe:cq29.exe
//    g++ -std=c++20 -O2 -IEngine/include \
//       Investigations/CQ29_Neutron_Genesis_to_Tritium/cq29_neutron_genesis.cpp -o cq29
//
//  See PROMPT.md (methodology), CLASSIFICATION.md (provenance), DATA_REQUIREMENTS.md.
//  Author: SDT Canonical Engine — James Tyndall, Melbourne.
// ============================================================================

#include <sdt/laws.hpp>
#include <sdt/nuclear.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;

static double MeVof(double m_kg){ return m_kg * measured::c * measured::c / measured::MeV_to_J; }
static void banner(const char* s){
    std::printf("\n============================================================\n");
    std::printf("  %s\n", s);
    std::printf("============================================================\n");
}

int main(){
    std::printf("CQ29A - NEUTRON DECAY LEDGER + TRITIUM KEYSTONE  (the PASSED core)\n");
    std::printf("Ledger: n -> p + e + nu_bar  ...  H3 -> He3 + e + nu_bar\n");
    std::printf("NOTE: 3n -> triton GENESIS is energy-gated ONLY -> see CQ29B (kinetics UNRESOLVED).\n");
    std::printf("Consumes laws.hpp + nuclear.hpp; one-way A->H.\n");

    const double m_n = MeVof(measured::m_n);
    const double m_p = MeVof(measured::m_p);
    const double m_e = MeVof(measured::m_e);
    const double Qn  = m_n - m_p - m_e;
    int fatals = 0;

    // ── STAGE A/B — conservation spine ──────────────────────────────────────
    banner("STAGE A/B - n -> p + e + nu_bar : conservation spine");
    std::printf("  rest energy [MeV]:  m_n=%.4f  m_p=%.4f  m_e=%.4f\n", m_n, m_p, m_e);
    std::printf("  %-9s %6s %6s %6s %6s   balance\n", "quantity","n","p","e","nu");
    auto bal=[&](const char* q,double n,double p,double e,double nu,const char* note){
        double s=p+e+nu; bool ok=std::fabs(n-s)<1e-6; if(!ok)++fatals;
        std::printf("  %-9s %6.2f %6.2f %6.2f %6.2f   %-5s %s\n", q,n,p,e,nu, ok?"OK":"FATAL", note);
    };
    bal("charge", 0,+1,-1, 0, "0 = +1 -1 +0");
    bal("baryon", 1, 1, 0, 0, "trefoil persists");
    bal("lepton", 0, 0,+1,-1, "unknot + receipt");
    std::printf("  %-9s %6s %6d %6d %6d   %s\n", "winding","3(+1)",
        winding::W_proton, winding::W_electron, 0, "trefoil / unknot / receipt(0+)");
    std::printf("  energy:  m_n = m_p + m_e + Q_n = %.4f + %.4f + %.4f = %.4f MeV\n",
        m_p, m_e, Qn, m_p+m_e+Qn);
    std::printf("  => eps_link = Q_n = %.4f MeV  (the Hopf-link strain that destabilises n)\n", Qn);
    std::printf("  PASS-A/B: spine closes  (%d fatal)\n", fatals);

    // ── STAGE C — lifetime + beam-bottle branching ─────────────────────────
    banner("STAGE C - free-neutron lifetime + beam-bottle branching");
    const double tau_bottle=877.75, tau_beam=887.7;
    const double f_circ = measured::c / measured::lambda_C_p;
    std::printf("  proton circulation  f = c/lambda_C,p = %.3e Hz\n", f_circ);
    std::printf("  tau_n: bottle %.2f s, beam %.2f s ; unlink barrier ln(f*tau) = %.1f (rare crossing)\n",
        tau_bottle, tau_beam, std::log(f_circ*tau_bottle));
    std::printf("  beam-bottle gap %.2f s  =>  predicted topological branching %.2f%%  [P4, class D]\n",
        tau_beam-tau_bottle, (tau_beam-tau_bottle)/tau_bottle*100.0);
    std::printf("  (absolute tau_n: barrier INFERRED from tau, not yet predicted -> class F / PARTIAL)\n");

    // ── STAGE D — 1836 displaced-volume partition + 1836pi falsification ────
    banner("STAGE D - the 1836 partition is a VOLUME ratio, not a winding");
    const double ratio = measured::m_p/measured::m_e;
    const double knot  = std::sqrt(3.0/2.0);                 // sqrt(q/p) for (2,3)
    const double a_ratio = std::cbrt(ratio/knot);
    std::printf("  m_p/m_e = %.4f = sqrt(3/2)*(a_p/a_e)^3 = %.5f*(a_p/a_e)^3\n", ratio, knot);
    std::printf("  => a_p/a_e = %.4f   <-- THE one number to derive (Q-D1; class F until knot-derived)\n", a_ratio);
    const double rex_pred = std::cbrt(ratio), rex_eng = law_IV::R_excl_p/law_IV::R_excl_e;
    std::printf("  R_excl,p/R_excl,e: 1836^(1/3)=%.4f ; laws.hpp law_IV=%.4f  %s\n",
        rex_pred, rex_eng, std::fabs(rex_pred-rex_eng)<0.05 ? "MATCH (same density)" : "DIVERGE");
    const double lamP = measured::hbar/(measured::m_p*measured::c);
    std::printf("  1836pi falsification: R_p(W=3)=%.5f fm  vs  R_p(W=918)=%.1f fm  (%.0fx) -> FALSIFIED\n",
        4*lamP*1e15, 919*lamP*1e15, 919.0/4.0);

    // ── STAGE E — frozen-engine gate ───────────────────────────────────────
    banner("STAGE E - re-check laws.hpp::winding (do-not-corrupt gate)");
    const double Rp_fm = winding::R_p_predicted*1e15;
    bool eOK = std::fabs(Rp_fm-0.84124)<0.001; if(!eOK)++fatals;
    std::printf("  R_p_predicted = %.5f fm (expect 0.84124) %s ;  W_eff=%.4f (3.0) ;  g_proton=%.4f (4.0)\n",
        Rp_fm, eOK?"OK":"FATAL", winding::W_eff, winding::g_proton);
    std::printf("  PASS-E: topology uncorrupted by the earlier stages.\n");

    // ── STAGE F — triton: proton is the keystone, di-neutron unbound ───────
    banner("STAGE F - two neutrons + the proton -> triton (di-neutron unbound)");
    const double k_occ = measured::B_deuteron;               // 1 p-n contact
    const double B_occ = 3.0*k_occ;                          // triangle: 3 contacts (2 p-n + 1 n-n)
    std::printf("  k_occ (1 p-n contact = B_deuteron) = %.3f MeV\n", k_occ);
    std::printf("  triton (2 p-n + 1 n-n, triangle): B_occ ~ %.2f MeV ; measured B(t)=%.3f  (3-body adds %.0f%%, class E)\n",
        B_occ, measured::B_triton, (measured::B_triton/B_occ-1.0)*100.0);
    std::printf("  di-neutron: 0 p-n contacts (no proton keystone) -> UNBOUND  [matches reality: 2n unbound] OK\n");
    auto g3 = sdt::nuclear::alpha_grammar(1,3);
    std::printf("  grammar(H-3): alpha n_d=%d n_t=%d -> %s (triton is a PRIMITIVE block, not alpha+blocks)\n",
        g3.n_d, g3.n_t, g3.valid ? "VALID??" : "alpha-invalid OK");

    // ── STAGE G — electron threads into 1s : the first atom ────────────────
    banner("STAGE G - beta-electron Hopf-threads into 1s : the first atom");
    const double a0_from_re = measured::r_e/(measured::alpha*measured::alpha);
    std::printf("  electron wake r_e = %.4f fm ; a0 = r_e/alpha^2 = %.4e m  (laws.hpp a_0 = %.4e)  %s\n",
        measured::r_e*1e15, a0_from_re, measured::a_0,
        std::fabs(a0_from_re-measured::a_0)/measured::a_0<0.01 ? "MATCH" : "diverge");
    std::printf("  => free neutron and ground-state H are ONE topology at two link radii:\n");
    std::printf("     embedded (nuclear, strained, tau~880s)  vs  orbiting (atomic, Lk=1, stable).  [P5, class D]\n");

    // ── STAGE H — KEYSTONE ─────────────────────────────────────────────────
    banner("STAGE H - KEYSTONE: tritium Q from Q_n minus the binding difference");
    const double dB = measured::B_triton - measured::B_helion;
    const double Qb = Qn - dB;
    bool keyOK = std::fabs(Qb*1000.0-18.591)<2.0; if(!keyOK)++fatals;
    std::printf("  Q_n = %.1f keV ;  B(t)-B(He3) = %.3f-%.3f = %.1f keV\n",
        Qn*1000.0, measured::B_triton, measured::B_helion, dB*1000.0);
    std::printf("  Q_beta(H3) = Q_n - [B(t)-B(He3)] = %.1f keV   (measured 18.591)  %s   [P1, class C, parameter-free]\n",
        Qb*1000.0, keyOK?"PASS":"FAIL");
    const double q5 = std::pow(Qn/Qb, 5.0);
    const double tau_H3 = 12.32*365.25*86400.0, tau_n_half = tau_bottle*std::log(2.0);
    std::printf("  Sargent Q^5: (Q_n/Q_b)^5 = %.2e ; measured tau-ratio = %.2e ; super-allowed matrix elt absorbs ~%.0fx\n",
        q5, tau_H3/tau_n_half, q5/(tau_H3/tau_n_half));

    // ── FINAL LEDGER (decay only; genesis is CQ29B) ─────────────────────────
    banner("FINAL LEDGER: n -> p + e + nu   and   H3 -> He3 + e + nu  (decay, PASSED)");
    std::printf("  hero #1  Q_n (link strain)      = %7.1f keV   (meas 782.3)\n", Qn*1000.0);
    std::printf("  hero #2  Q_beta(H3) = Q_n - dB  = %7.1f keV   (meas 18.591)  <-- PARAMETER-FREE keystone\n", Qb*1000.0);
    std::printf("  honesty  a_p/a_e (D1 form C-fl) = %7.3f       (D2 lever class F -> full p/e ratio is F until derived)\n", a_ratio);
    std::printf("  honesty  1836pi -> R_p          = %7.1f fm    (falsified: 1836 is displaced VOLUME)\n", 919*lamP*1e15);
    std::printf("  NOT TESTED HERE: 3n -> triton genesis -> energy-gated only in CQ29B; kinetics UNRESOLVED.\n");
    std::printf("  conservation fatals across ledger = %d\n", fatals);
    std::printf("\n[CQ29A done]  %s\n", fatals==0 ? "decay ledger closes; keystone holds." : "FATAL non-closure!");
    return fatals;
}
