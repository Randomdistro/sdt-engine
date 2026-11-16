// NP14 blank-slate run 1 (2026-10-07): wake-energy fractions for the neutron-proton mass difference, with look-elsewhere census.
// Pre-registered in NP14_RESET_ASSESSMENT_2026-10-07.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <random>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

struct Cand { double v; std::string lab; };
// count candidates in [lo*t, hi*t]; chance baseline: slide a band of the same log width over [q05, q95 - w] of the candidate logs
struct Cen { int count; double mean; double frac; size_t n; std::vector<std::string> members; };
static Cen census(const std::vector<Cand>& cs, double t, double lo, double hi) {
    std::vector<double> lg; for (auto& c : cs) lg.push_back(std::log10(c.v)); std::sort(lg.begin(), lg.end());
    double w = std::log10(hi / lo); auto cnt = [&](double a) { return (int)(std::upper_bound(lg.begin(), lg.end(), a + w) - std::lower_bound(lg.begin(), lg.end(), a)); };
    Cen r; r.n = cs.size(); r.count = cnt(std::log10(lo * t)); for (auto& c : cs) if (c.v >= lo * t && c.v <= hi * t) r.members.push_back(c.lab);
    double a = lg[(size_t)(0.05 * (lg.size() - 1))], b = lg[(size_t)(0.95 * (lg.size() - 1))] - w, s = 0; int n = 0, ge = 0;
    for (double x = a; x <= b; x += 0.0005) { int k = cnt(x); s += k; ++n; if (k >= r.count) ++ge; }
    r.mean = n ? s / n : 0; r.frac = n ? double(ge) / n : 0; return r;
}
int main() {
    std::printf("NP14 blank-slate run 1 (pre-registered 2026-10-07)\n===================================================\n\n");
    int fails = 0;
    const double c = M::c, hb = M::hbar, al = M::alpha, mp = M::m_p, mn = M::m_n, me = M::m_e, MeV = M::MeV_to_J, Rp = M::R_p, Rl = law_III::R_p_lock;
    const double mpc2 = mp * c * c / MeV, dm = (mn - mp) * c * c / MeV, mec2 = me * c * c / MeV, s = dm - mec2, W1 = double(lock_geometry::trefoil_lock_coordination);
    const double Ew = al * hb * c / Rl / MeV, Ew2 = al * mpc2 / W1, Ewm = al * hb * c / Rp / MeV, ahc = al * hb * c / MeV * 1e15;
    // ---- V1
    bool v1 = std::fabs(dm / 1.29333 - 1) < 1e-5 && std::fabs(mec2 / 0.510999 - 1) < 1e-5 && std::fabs(ahc / 1.43996 - 1) < 1e-5 && std::fabs(Ew / Ew2 - 1) < 1e-12;
    std::printf("[V1] m_n - m_p = %.6f MeV ; m_e c^2 = %.6f MeV ; alpha hbar c = %.5f MeV fm ; E_w (R_lock) = %.8f MeV, alpha m_p c^2/(W+1) = %.8f MeV -> %s\n", dm, mec2, ahc, Ew, Ew2, v1 ? "met" : "NOT MET");
    if (!v1) ++fails;
    // ---- V2
    std::vector<Cand> pl; for (int a = 1; a <= 8; ++a) for (int b = 1; b <= 8; ++b) pl.push_back({double(a) / b, std::to_string(a) + "/" + std::to_string(b)});
    Cen cp = census(pl, 3.0 / 7.0, 0.99, 1.01); bool planted = false; for (auto& m : cp.members) if (m == "3/7") planted = true;
    std::mt19937 gen(20261007u); std::vector<double> lg; for (int i = 0; i < 20000; ++i) lg.push_back(-3 + 6 * (double(gen()) / 4294967296.0)); std::sort(lg.begin(), lg.end());
    double w = std::log10(1.2 / 0.8), sm = 0; int nn = 0; for (double x = lg.front(); x <= lg.back() - w; x += 0.002) { sm += (int)(std::upper_bound(lg.begin(), lg.end(), x + w) - std::lower_bound(lg.begin(), lg.end(), x)); ++nn; }
    double ex = 20000 * w / (lg.back() - lg.front()), me2 = sm / nn; bool v2 = planted && std::fabs(me2 / ex - 1) < 0.05;
    std::printf("[V2] planted 3/7 found: %s ; log-uniform sliding-band mean %.3f vs expected %.3f -> %s\n\n", planted ? "yes" : "no", me2, ex, v2 ? "met" : "NOT MET");
    if (!v2) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;
    // ---- T1
    const double rD = dm / Ew, rS = s / Ew;
    std::printf("[T1] Delta m c^2 = %.6f MeV ; surplus s = Delta m c^2 - m_e c^2 = %.6f MeV ; E_w = alpha hbar c / R_lock = %.6f MeV (measured R_p: %.6f MeV)\n     r_Delta = %.6f ; r_s = %.6f (measured R_p: %.6f, %.6f)\n\n", dm, s, Ew, Ewm, rD, rS, dm / Ewm, s / Ewm);
    // ---- T2
    std::vector<Cand> P = {{1.0, "1 (point-source interaction energy)"}, {0.5, "1/2 (quadratic field energy outside a sphere)"}, {0.6, "3/5 (uniform ball, total)"}, {0.1, "1/10 (uniform ball, interior)"}};
    std::printf("[T2] physical source models xi * E_w:\n");
    int inD = 0, inS = 0;
    for (auto& p : P) { double pr = p.v * Ew; double dD = pr / dm - 1, dS = pr / s - 1; if (std::fabs(dD) <= 0.2) ++inD; if (std::fabs(dS) <= 0.2) ++inS;
        std::printf("     xi = %-45s predicts %.6f MeV : vs Delta m %+.2f%% ; vs surplus s %+.2f%%\n", p.lab.c_str(), pr, dD * 100, dS * 100); }
    Cen cD = census(P, rD, 0.8, 1.2), cS = census(P, rS, 0.8, 1.2);
    std::printf("     members within 20%%: Delta m: %d (chance mean %.3f, fraction of band positions with >= observed %.4f) ; surplus: %d (chance mean %.3f, fraction %.4f) ; look-elsewhere count %zu\n", inD, cD.mean, cD.frac, inS, cS.mean, cS.frac, P.size());
    std::printf("     R1 (H_A for Delta m rejected if no member within 20%%): %s ; R2 (H_A for the surplus rejected if no member within 20%%): %s\n\n", inD == 0 ? "MET (rejected)" : "not met", inS == 0 ? "MET (rejected)" : "not met");
    // ---- T3
    std::vector<Cand> F; { std::map<long long, size_t> seen; for (int a = 1; a <= 8; ++a) for (int b = 1; b <= 8; ++b) { double v = double(a) / b; long long k = std::llround(v * 1e9); if (!seen.count(k)) { seen[k] = F.size(); F.push_back({v, std::to_string(a) + "/" + std::to_string(b)}); } } }
    std::printf("[T3] census of fractions a/b, 1 <= a, b <= 8: %zu distinct values\n", F.size());
    for (int tg = 0; tg < 2; ++tg) { double t = tg == 0 ? rD : rS; Cen g = census(F, t, 0.8, 1.2), tt = census(F, t, 0.99, 1.01);
        std::printf("     target r_%s = %.6f : within 20%%: %d (chance mean %.3f, fraction %.4f) ; within 1%%: %d (chance mean %.3f, fraction %.4f)", tg == 0 ? "Delta" : "s", t, g.count, g.mean, g.frac, tt.count, tt.mean, tt.frac);
        std::printf(" ; members within 1%%:"); for (auto& m : tt.members) { double v = 0; for (auto& f : F) if (f.lab == m) v = f.v; std::printf(" %s (%+.2f%%)", m.c_str(), (v / t - 1) * 100); } std::printf("\n"); }
    Cen g = census(F, rD, 0.8, 1.2), tt = census(F, rD, 0.99, 1.01), gs = census(F, rS, 0.8, 1.2);
    std::printf("     R3 (a 20%% agreement is non-discriminating if count >= 3 or chance fraction > 0.05): Delta m %s ; surplus %s ; (a 1%% agreement non-discriminating if count >= 1 and chance fraction > 0.05): Delta m %s\n\n",
                (g.count >= 3 || g.frac > 0.05) ? "MET" : "not met", (gs.count >= 3 || gs.frac > 0.05) ? "MET" : "not met", (tt.count >= 1 && tt.frac > 0.05) ? "MET" : "not met");
    // ---- T4
    double W = 3, pr = W * al * mpc2 / ((W + 1) * (W + 1)), res = pr - dm;
    std::printf("[T4] xi = W/(W+1) = 3/4 (selected after the exposure of the registration): Delta m c^2 = W alpha m_p c^2/(W+1)^2 = %.6f MeV ; measured %.6f MeV ; residual %+.3f keV (%+.3f%%) ; relative uncertainty of the engine masses ~1e-10 (residual is not a measurement error)\n", pr, dm, res * 1e3, res / dm * 100);
    std::printf("\n[T5] surplus derivation (NP17 neutron structure): DEFERRED ; hypotheses B and C: not instrumented\n");
    return 0;
}
