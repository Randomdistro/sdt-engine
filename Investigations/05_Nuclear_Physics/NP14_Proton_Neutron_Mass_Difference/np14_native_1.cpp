// NP14 native run 1 (2026-10-07): unit-free ledger, component-list closure, native seat candidate N1 (sign test), discriminating thresholds.
// Registered in NP14_NATIVE_ASSESSMENT_2026-10-07.md §3 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

int main() {
    std::printf("NP14 native run 1 (registered 2026-10-07)\n==========================================\n\n");
    int fails = 0;
    const double c = M::c, hb = M::hbar, al = M::alpha, mp = M::m_p, mn = M::m_n, me = M::m_e, md = M::m_d, mt = M::m_t, mh = M::m_He3, MeV = M::MeV_to_J, eV = M::eV_to_J;
    const double c2 = c * c, Rl = law_III::R_p_lock, re = M::r_e;
    auto E = [&](double m) { return m * c2 / MeV; };   // MeV
    // ---- V1
    double ry = 0.5 * me * al * al * c2 / eV;
    double r_a0 = M::a_0, v_a0 = c * std::sqrt(re / r_a0), Et_a0 = (0.5 * me * v_a0 * v_a0 - al * hb * c / r_a0) / eV;
    double dm = E(mn - mp), Bd = E(mp + mn - md);
    bool v1 = std::fabs(ry / 13.605693 - 1) < 1e-6 && std::fabs(Et_a0 / (-ry) - 1) < 1e-6 && std::fabs(dm / 1.293333 - 1) < 1e-5 && std::fabs(Bd / 2.22457 - 1) < 1e-5;
    std::printf("[V1] hydrogen ladder: (1/2) m_e (alpha c)^2 = %.6f eV (13.605693) ; circular balance at a_0: E_total = %.6f eV = -(1/2) m v^2 ; (m_n - m_p) c^2 = %.6f MeV ; B_deuteron = %.6f MeV -> %s\n", ry, Et_a0, dm, Bd, v1 ? "met" : "NOT MET");
    if (!v1) ++fails;
    // ---- V2 / T2: unit invariance (everything in m_p = 1 units, no c, hbar or eV anywhere)
    const double u_n = mn / mp, u_e = me / mp, u_d = md / mp, u_t = mt / mp, u_h = mh / mp;
    const double s_u = u_n - 1 - u_e;                                  // surplus in m_p units
    double Bsm_d_u = 1 + u_n - u_d, Bp_d_u = 2 + u_e - u_d;            // d: {p,n} vs {p,p,e}
    double Bsm_t_u = 1 + 2 * u_n - u_t, Bp_t_u = 3 + 2 * u_e - u_t;
    double Bsm_h_u = 2 + u_n - u_h, Bp_h_u = 3 + u_e - u_h;
    const double sMeV = E(mn - mp - me), mp_MeV = E(mp);
    double Bsm_d = E(mp + mn - md), Bp_d = E(2 * mp + me - md), Bsm_t = E(mp + 2 * mn - mt), Bp_t = E(3 * mp + 2 * me - mt), Bsm_h = E(2 * mp + mn - mh), Bp_h = E(3 * mp + me - mh);
    double w = 0; for (auto pr : {std::pair<double, double>{Bsm_d_u * mp_MeV, Bsm_d}, {Bp_d_u * mp_MeV, Bp_d}, {Bsm_t_u * mp_MeV, Bsm_t}, {Bp_t_u * mp_MeV, Bp_t}, {Bsm_h_u * mp_MeV, Bsm_h}, {Bp_h_u * mp_MeV, Bp_h}, {s_u * mp_MeV, sMeV}}) w = std::max(w, std::fabs(pr.first / pr.second - 1));
    bool v2 = w < 1e-12;
    std::printf("[V2] unit-free (m_p = 1) ledger against the MeV ledger for d, t, 3He and the surplus: worst relative difference %.2e -> %s\n\n", w, v2 ? "met" : "NOT MET");
    if (!v2) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // ---- T1
    std::printf("[T1] unit-free resistances (m_p = 1): m_n/m_p - 1 = %.8e ; m_e/m_p = %.8e ; (m_n - m_p)/m_e = %.8f ; surplus s/m_e = (m_n - m_p - m_e)/m_e = %.8f ; s/m_p = %.8e\n     Law IV: V_disp is proportional to m, so V_n/V_p - 1 = %.8e and the extra exclusion volume is %.6f electron-volumes (one is the electron itself)\n\n", u_n - 1, u_e, (u_n - 1) / u_e, s_u / u_e, s_u, u_n - 1, (u_n - 1) / u_e);
    // ---- T2
    std::printf("[T2] unit invariance (R-U: F5 set if any ledger statement changes by > 1e-12): worst relative difference %.2e -> F5 %s\n\n", w, w > 1e-12 ? "SET" : "not set");
    // ---- T3
    int Nn[3] = {1, 2, 1}; const char* nm[3] = {"d  (Z=1, N=1)", "3H (Z=1, N=2)", "3He (Z=2, N=1)"}; double Bs[3] = {Bsm_d, Bsm_t, Bsm_h}, Bq[3] = {Bp_d, Bp_t, Bp_h}; int A[3] = {2, 3, 3};
    std::printf("[T3] component-list ledger (MeV): B_SM against {Z p, N n}, B' against {A p, N e}, s = %.6f MeV\n     %-16s %-10s %-10s %-12s %-12s %-14s %-12s\n", sMeV, "nucleus", "B_SM", "B'", "B_SM - B'", "N s", "(B_SM-B')/N s - 1", "list change [%]");
    double worst = 0; for (int i = 0; i < 3; ++i) { double dd = Bs[i] - Bq[i], ns = Nn[i] * sMeV; worst = std::max(worst, std::fabs(dd / ns - 1)); std::printf("     %-16s %-10.5f %-10.5f %-12.6f %-12.6f %-14.2e %-12.2f\n", nm[i], Bs[i], Bq[i], dd, ns, dd / ns - 1, (Bs[i] - Bq[i]) / Bs[i] * 100); }
    std::printf("     relation B_SM - B' = N s: worst relative deviation %.2e (CONSTRUCTION)\n", worst);
    std::printf("     per baryon: B_SM/A = %.4f, %.4f, %.4f ; B'/A = %.4f, %.4f, %.4f MeV (d, 3H, 3He)\n", Bs[0] / A[0], Bs[1] / A[1], Bs[2] / A[2], Bq[0] / A[0], Bq[1] / A[1], Bq[2] / A[2]);
    double Qb = E(mt - mh - me);
    std::printf("     mirror pair: B_SM(3H) - B_SM(3He) = %.6f MeV ; B'(3H) - B'(3He) = %.6f MeV ; -Q_beta(3H) = %.6f MeV (CONSTRUCTION: Q_beta = M(3H) - M(3He) - m_e) ; s = %.6f MeV ; [B_SM(3H) - B_SM(3He)]/s = %.4f ; s - [B_SM(3H) - B_SM(3He)] = %.6f MeV\n", Bsm_t - Bsm_h, Bp_t - Bp_h, -Qb, sMeV, (Bsm_t - Bsm_h) / sMeV, sMeV - (Bsm_t - Bsm_h));
    std::printf("     free neutron against {p, e}: B'(n) = m_p + m_e - m_n = %+.6f MeV (negative: a state above its constituents)\n", E(mp + me - mn));
    double lc = (Bsm_d - Bp_d) / Bsm_d * 100;
    std::printf("     R-L (H-L not supported if the list change for d is below 1%%): list change for d = %.2f%% -> %s\n\n", lc, lc >= 1 ? "H-L supported" : "not supported");
    // ---- T4
    std::printf("[T4] N1: Law III circular balance, v = c sqrt(r_e/r), E_kin = (1/2) m_e v^2, E_pot = -alpha hbar c / r, E_total = E_kin + E_pot (MeV); measured excess over p + e: s = %+.6f MeV\n", sMeV);
    std::printf("     %-22s %-10s %-8s %-10s %-10s %-10s %-26s\n", "radius", "r [fm]", "v/c", "E_kin", "E_pot", "E_total", "domain (v <= c)");
    struct R { const char* nm; double r; } rs[3] = {{"r_e (c-boundary)", re}, {"R_lock", Rl}, {"R_lock/3 (node)", Rl / 3}};
    bool anyPos = false;
    for (auto& r : rs) { double v = c * std::sqrt(re / r.r), Ek = 0.5 * me * v * v / MeV, Ep = -al * hb * c / r.r / MeV, Et = Ek + Ep; if (Et > 0) anyPos = true;
        std::printf("     %-22s %-10.4f %-8.4f %-+10.5f %-+10.5f %-+10.5f %-26s\n", r.nm, r.r * 1e15, v / c, Ek, Ep, Et, v / c <= 1.0000001 ? "inside the law's domain" : "outside (Law V budget): flagged"); }
    std::printf("     R-N1 (N1 rejected if its sign differs from the measured sign of the excess): predicted sign %s at every registered radius, measured sign %s -> %s\n\n", anyPos ? "mixed" : "negative", sMeV > 0 ? "positive" : "negative", (!anyPos && sMeV > 0) ? "MET (rejected)" : "not met");
    // ---- T5
    double Mth_pn = E(md) + 0; (void)Mth_pn;
    std::printf("[T5] O1 thresholds (invariant mass, recoil neglected): gamma d -> p n : %.6f MeV (B_SM(d)) ; gamma d -> p p e- : %.6f MeV (B'(d)) ; the interval in which only the second channel is open: %.6f MeV wide\n", Bsm_d, Bp_d, Bsm_d - Bp_d);
    std::printf("     O3 boundary radius under the lock rule R = 4 hbar/(m c) for both W = 3: R_n/R_p = m_p/m_n = %.8f (a %.3f%% difference; the measurement would need a precision of about 1e-3 on the radius)\n", mp / mn, (1 - mp / mn) * 100);
    return 0;
}
