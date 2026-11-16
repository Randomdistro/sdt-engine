// FLM01 R2 (2026-10-05) — (a) G-free Coulomb/gravity hierarchy from the koppa per baryon,
// (b) dormant state28d normalisations against the engine's native scales.
// Pre-registered in R2_REOPEN_2026-10-05.md §4 before this file existed.
// Author: J. C. Harvey, Melbourne.
//
// G appears ONLY in the comparison column (CODATA 2018, labelled), never in the SDT chain.

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

using namespace sdt::laws;
namespace M = sdt::laws::measured;

struct Dim { int kg, m, s; };
static Dim operator*(Dim a, Dim b) { return {a.kg + b.kg, a.m + b.m, a.s + b.s}; }
static Dim operator/(Dim a, Dim b) { return {a.kg - b.kg, a.m - b.m, a.s - b.s}; }
static bool eq(Dim a, Dim b) { return a.kg == b.kg && a.m == b.m && a.s == b.s; }
static std::string str(Dim a) { char b[64]; std::snprintf(b, sizeof b, "kg^%d m^%d s^%d", a.kg, a.m, a.s); return b; }

int main() {
    std::printf("FLM01 R2 — hierarchy and dormant scales (pre-registered 2026-10-05)\n");
    std::printf("====================================================================\n\n");
    int fails = 0;

    // ---------------- V1: dimension tracker ----------------
    const Dim m1{0,1,0}, kg{1,0,0}, s1{0,0,1};
    const Dim Newton = kg * m1 / (s1 * s1);                 // kg m s^-2
    const Dim Pa     = Newton / (m1 * m1);                  // N/m^2
    const Dim V      = m1 * m1 * m1;
    const Dim Gdim   = (m1 * m1 * m1) / (kg * s1 * s1);
    const Dim r2     = m1 * m1;
    // F_coulomb = P_eff R^4 / r^2
    Dim Fc = Pa * (m1 * m1 * m1 * m1) / r2;
    // INVESTIGATION.md F_G = P_conv V1 V2 / (S_boundary r^2); S_boundary dimensionless
    Dim FG_inv = Pa * V * V / r2;
    // tool F_G = P_conv (l_P/r)^2 r^2  -> P_conv l_P^2 ; r-exponent 0
    Dim FG_tool = Pa * (m1 * m1);
    const int r_exp_tool = 0;
    // G m1 m2 / r^2
    Dim FG_newton = Gdim * kg * kg / r2;
    bool v1 = eq(Fc, Newton) && eq(FG_newton, Newton) && !eq(FG_inv, Newton) && eq(FG_inv, Newton * r2) && eq(FG_tool, Newton) && r_exp_tool != -2;
    std::printf("[V1] dimension tracker\n");
    std::printf("     P_eff R^4/r^2            = %-18s  expected force            %s\n", str(Fc).c_str(), eq(Fc, Newton) ? "ok" : "X");
    std::printf("     G m1 m2/r^2              = %-18s  expected force            %s\n", str(FG_newton).c_str(), eq(FG_newton, Newton) ? "ok" : "X");
    std::printf("     INVESTIGATION.md F_G     = %-18s  = force x m^2, NOT a force (flagged)  %s\n", str(FG_inv).c_str(), (!eq(FG_inv, Newton)) ? "ok (flagged)" : "X");
    std::printf("     tool F_G = P_conv l_P^2  = %-18s  force dimension but r-exponent %d, not -2 (flagged)  %s\n\n", str(FG_tool).c_str(), r_exp_tool, "ok (flagged)");
    if (!v1) ++fails;

    // ---------------- V2: known values on the comparison side ----------------
    const double G_cmp = 6.67430e-11;                       // COMPARISON ONLY (CODATA 2018)
    const double hb = M::hbar, c = M::c, mp = M::m_p, me = M::m_e;
    const double aG = G_cmp * mp * mp / (hb * c);
    const double ke_e2 = coulomb_identity::k_e_e2_codata;   // k_e e^2 from CODATA k_e and e
    const double ratio_pp_cmp = ke_e2 / (G_cmp * mp * mp);
    bool v2 = std::fabs(aG - 5.906e-39) / 5.906e-39 < 5e-4 && std::fabs(ratio_pp_cmp - 1.2355e36) / 1.2355e36 < 1e-3;
    std::printf("[V2] comparison side known values\n");
    std::printf("     alpha_G(p) = G m_p^2/(hbar c) = %.4e (published 5.906e-39, tol 0.05%%)\n", aG);
    std::printf("     k_e e^2/(G m_p^2) = %.5e (published 1.2355e36, tol 0.1%%)  -> %s\n\n", ratio_pp_cmp, v2 ? "PASS" : "FAIL");
    if (!v2) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // ---------------- T1: G-free hierarchy from the engine ----------------
    const double koppa_b = bridge::koppa_per_baryon;                    // l_P^2 / (R_p/4)
    const double koppa_b_alt = M::l_P * M::l_P * mp * c / hb;                 // alternative out 1: R_p -> 4 hbar/(m_p c), so lam_w = hbar/(m_p c) (run 1 carried a spurious /4: instrument fault, superseded)
    const double lam_p = hb / (mp * c);
    const double E_p = mp * c * c;
    const double Nbar_e = me / mp;                                       // census conversion N = m/m_p
    // F_C/F_G(ij) = (k_e e^2) / (m_p c^2 * koppa_b) / (N_i N_j)
    auto engine_ratio = [&](double ki, double Ni, double Nj) { return coulomb_identity::k_e_e2 / (E_p * ki) / (Ni * Nj); };
    struct Pair { const char* nm; double Ni, Nj, mi, mj; } pr[3] = {
        {"p-p", 1.0, 1.0, mp, mp}, {"e-p", Nbar_e, 1.0, me, mp}, {"e-e", Nbar_e, Nbar_e, me, me}};
    std::printf("[T1] Coulomb/gravity ratio, engine route (G-free) vs comparison column (k_e e^2/(G m_i m_j))\n");
    std::printf("     koppa_per_baryon = %.5e m (bridge); alt (R_p -> 4 hbar/(m_p c)) = %.5e m; hbar/(m_p c) = %.5e m\n", koppa_b, koppa_b_alt, lam_p);
    std::printf("     closed form: alpha (lam_p/l_P)^2 = %.5e  (p-p, using Compton lam_p)\n", M::alpha * (lam_p / M::l_P) * (lam_p / M::l_P));
    std::printf("     pair |  engine (bridge)  |  engine (alt)     |  comparison (G)   | dev bridge | dev alt\n");
    int in_tol = 0;
    for (auto& p : pr) {
        double e1 = engine_ratio(koppa_b, p.Ni, p.Nj), e2 = engine_ratio(koppa_b_alt, p.Ni, p.Nj);
        double cmp = ke_e2 / (G_cmp * p.mi * p.mj);
        double d1 = (e1 - cmp) / cmp * 100, d2 = (e2 - cmp) / cmp * 100;
        if (std::fabs(d1) < 0.5) ++in_tol;
        std::printf("     %-4s | %.5e | %.5e | %.5e | %+8.4f%% | %+8.4f%%\n", p.nm, e1, e2, cmp, d1, d2);
    }
    std::printf("     pairs within 0.5%% (bridge route): %d of 3 -> %s\n", in_tol, in_tol == 3 ? "G3 (consistent; shared-input: l_P via G)" : "see grade table");
    std::printf("     contaminating input: l_P = 1.616255e-35 m -- CODATA, computed from sqrt(hbar G/c^3), measured through G -- enters at laws.hpp:99 and bridge::koppa_per_baryon (laws.hpp:1059)\n");
    std::printf("     reduction: F_C/F_G(p-p) = alpha (lam_p/l_P)^2 ; lam_p/l_P = %.5e is the one number the hierarchy rests on\n\n", lam_p / M::l_P);

    // ---------------- T2: dormant constants vs native scales ----------------
    const double Rp = M::R_p, re = M::r_e, lamCe = hb / (me * c);
    const double Peff = law_III::P_eff, Pconv = law_I::P_conv, RCMB = law_I::R_CMB, eps = law_I::epsilon;
    struct Cand { const char* nm; double v; };
    const double S0 = 1e10, E0 = 1e-20;
    std::vector<Cand> Sc = {{"S1 P_conv/R_p", Pconv / Rp}, {"S2 P_conv/r_e", Pconv / re}, {"S3 P_eff/R_p", Peff / Rp},
                            {"S4 P_eff/r_e", Peff / re}, {"S5 P_conv/(3 R_CMB)", Pconv / (3 * RCMB)}, {"S6 P_conv/lam_C,e", Pconv / lamCe}};
    std::vector<Cand> Ec = {{"E1 k_B T_CMB", M::k_B * M::T_CMB}, {"E2 m_e c^2/4", me * c * c / 4}, {"E3 alpha^2 m_e c^2", M::alpha * M::alpha * me * c * c},
                            {"E4 hbar c/R_p", hb * c / Rp}, {"E5 hbar c/r_e", hb * c / re}, {"E6 epsilon", eps}};
    const double win = std::log10(3.0);
    std::printf("[T2] candidate scales vs the two normalisations (window: factor 3 = %.3f decades; K = 6 each)\n", win);
    int hitS = 0, hitE = 0;
    std::printf("     pressure gradient, constant 1e10 Pa/m:\n");
    for (auto& s : Sc) { double d = std::log10(s.v / S0); if (std::fabs(d) < win) ++hitS; std::printf("       %-22s %.4e  log10(cand/const) = %+7.2f\n", s.nm, s.v, d); }
    std::printf("     energy, constant 1e-20 J:\n");
    for (auto& e : Ec) { double d = std::log10(e.v / E0); if (std::fabs(d) < win) ++hitE; std::printf("       %-22s %.4e  log10(cand/const) = %+7.2f\n", e.nm, e.v, d); }
    std::printf("     inside window: pressure %d of 6, energy %d of 6 (chance coincidence per constant over +-50 decades ~ 5.7%%)\n\n", hitS, hitE);

    // ---------------- T3: effect size in the only code that sets T_5 / Phi_5 ----------------
    const double T5_core = 330e9 / bridge::R_Earth;
    const double rho_sw = 5.0e6 * mp, v_sw = 400e3, Pdyn = 0.5 * rho_sw * v_sw * v_sw;
    const double T5_sw = Pdyn / M::AU;
    std::printf("[T3] effect size of the normalisations in magnetosphere.hpp's own inputs\n");
    std::printf("     Earth core   T_5 = 330e9/R_Earth = %.4e Pa/m  tanh(T_5/1e10) = %.3e\n", T5_core, std::tanh(T5_core / S0));
    std::printf("     solar wind   T_5 = P_dyn/AU      = %.4e Pa/m  tanh(T_5/1e10) = %.3e  (P_dyn = %.3e Pa)\n", T5_sw, std::tanh(T5_sw / S0), Pdyn);
    std::printf("     Phi_5 = 0 at every call site (magnetosphere.hpp:105,188,373): phase factor 1 + 0/1e-20 = %.1f exactly\n", 1.0 + 0.0 / E0);
    const double worst = std::tanh(T5_core / S0);
    std::printf("     largest effect on E_mutual*(1+gradation): relative %.2e\n\n", worst);

    std::printf("SUMMARY: validations met; T1 %d/3 pairs within 0.5%%; T2 windows: pressure %d, energy %d; T3 largest effect %.2e\n", in_tol, hitS, hitE, worst);
    return 0;
}
