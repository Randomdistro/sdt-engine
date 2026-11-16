// NP06 blank-slate run 1 (2026-10-06): candidate census for a rim-kinematic definition of the gear frequency.
// Pre-registered in NP06_RESET_ASSESSMENT_2026-10-06.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <map>
#include <random>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

struct Cand { double v; std::string lab; };
static const double W_LOG = std::log10(1.05 / 0.95);

static std::vector<Cand> generate(const std::vector<Cand>& F, int mmax, double extra, const std::string& extraLab) {
    std::vector<Cand> out; std::map<long long, size_t> seen;
    auto add = [&](double v, const std::string& lab) { long long key = std::llround(std::log10(v) * 1e11); if (!seen.count(key)) { seen[key] = out.size(); out.push_back({v, lab}); } };
    add(extra, extraLab.empty() ? "1" : extraLab);
    std::vector<int> idx;
    // unordered products with k factors, k = 1..mmax
    for (int k = 1; k <= mmax; ++k) {
        std::vector<int> c(k, 0);
        while (true) {
            double v = extra; std::string lab = extraLab; for (int i = 0; i < k; ++i) { v *= F[c[i]].v; lab += (lab.empty() ? "" : "*") + F[c[i]].lab; }
            add(v, lab);
            int p = k - 1; while (p >= 0 && c[p] == (int)F.size() - 1) --p; if (p < 0) break;
            ++c[p]; for (int j = p + 1; j < k; ++j) c[j] = c[p];
        }
    }
    return out;
}
struct Census { int count; double mean; double frac; size_t n; std::vector<std::string> members; };
static Census census(const std::vector<Cand>& cs, double target) {
    std::vector<double> lg; for (auto& c : cs) lg.push_back(std::log10(c.v)); std::sort(lg.begin(), lg.end());
    auto cnt = [&](double lo) { return (int)(std::upper_bound(lg.begin(), lg.end(), lo + W_LOG) - std::lower_bound(lg.begin(), lg.end(), lo)); };
    double lo0 = std::log10(target * 0.95); Census r; r.n = cs.size(); r.count = cnt(lo0);
    for (auto& c : cs) if (c.v >= 0.95 * target && c.v <= 1.05 * target) r.members.push_back(c.lab + "=" + std::to_string(c.v));
    double a = lg[(size_t)(0.05 * (lg.size() - 1))], b = lg[(size_t)(0.95 * (lg.size() - 1))] - W_LOG; double s = 0; int n = 0, ge = 0;
    for (double x = a; x <= b; x += 0.0005) { int k = cnt(x); s += k; ++n; if (k >= r.count) ++ge; }
    r.mean = n ? s / n : 0; r.frac = n ? double(ge) / n : 0; return r;
}

int main() {
    std::printf("NP06 blank-slate run 1 (pre-registered 2026-10-06)\n===================================================\n\n");
    int fails = 0;
    const double c = M::c, hb = M::hbar, Rp = M::R_p, re = M::r_e, al = M::alpha, a0 = M::a_0, MeV = M::MeV_to_J, eV = M::eV_to_J;
    const double Bd = M::B_deuteron;
    const double vseat = c * std::sqrt(re / Rp), Om_rim = vseat / Rp, Om_c = c / Rp, wd = Bd * MeV / hb;
    const double rt = wd / Om_rim, rtc = wd / Om_c;

    // ---- V1
    double hbc = hb * c / MeV * 1e15, hartree = hb * (al * c / a0) / eV;
    bool v1 = std::fabs(hbc - 197.327) < 197.327 * 1e-5 && std::fabs(hartree - 27.211386) < 27.211386 * 1e-6 && std::fabs(wd / 3.38e21 - 1) < 0.015 && std::fabs(Om_rim / 6.52e23 - 1) < 0.015 && std::fabs(rt / 5.2e-3 - 1) < 0.015;
    std::printf("[V1] hbar c = %.4f MeV fm ; hbar (alpha c/a_0) = %.6f eV (Hartree 27.211386) ; E_d/hbar = %.4e rad/s ; Omega_rim = %.4e rad/s ; ratio = %.5e -> %s\n", hbc, hartree, wd, Om_rim, rt, v1 ? "met" : "NOT MET");
    if (!v1) ++fails;
    // ---- V2
    std::vector<Cand> Fs = {{0.5, "1/2"}, {1.0 / 3, "1/3"}};
    auto gs = generate(Fs, 3, 1.0, ""); Census cs = census(gs, 1.0 / 12);
    bool planted = cs.count >= 1;
    std::mt19937 gen(20261006u); std::vector<Cand> rnd; for (int i = 0; i < 20000; ++i) { double u = double(gen()) / 4294967296.0; rnd.push_back({std::pow(10.0, -3 + 6 * u), ""}); }
    std::vector<double> lg; for (auto& x : rnd) lg.push_back(std::log10(x.v)); std::sort(lg.begin(), lg.end());
    double s = 0; int n = 0; for (double x = lg.front(); x <= lg.back() - W_LOG; x += 0.002) { s += (int)(std::upper_bound(lg.begin(), lg.end(), x + W_LOG) - std::lower_bound(lg.begin(), lg.end(), x)); ++n; }
    double expct = 20000 * W_LOG / (lg.back() - lg.front()), meas = s / n;
    bool v2 = planted && std::fabs(meas / expct - 1) < 0.05;
    std::printf("[V2] planted candidate 1/12 found in band: %s ; random log-uniform: sliding-band mean %.3f vs expected %.3f -> %s\n\n", planted ? "yes" : "no", meas, expct, v2 ? "met" : "NOT MET");
    if (!v2) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // ---- T1
    std::printf("[T1] target ratios: r_t = B_d/(hbar Omega_rim) = %.5e (band %.5e .. %.5e) ; r_t' = B_d/(hbar c/R_p) = %.5e\n     (B_d = %.5f MeV; v_seat/c = %.5f; hbar Omega_rim = %.3f MeV; hbar c/R_p = %.3f MeV)\n\n", rt, 0.95 * rt, 1.05 * rt, rtc, Bd, vseat / c, hb * Om_rim / MeV, hb * Om_c / MeV);

    // ---- T2
    const double s2 = std::sqrt(2.0), s3 = std::sqrt(3.0);
    std::vector<Cand> F = {{0.5, "1/2"}, {1.0 / 3, "1/3"}, {0.25, "1/4"}, {1.0 / 6, "1/6"}, {3.0 / 7, "3/7"}, {7.0 / 3, "7/3"}, {2.0, "2"}, {3.0, "3"}, {4.0, "4"}, {1 / s2, "1/sqrt2"}, {1 / s3, "1/sqrt3"}};
    std::printf("[T2] alpha-free census: Delta_omega = base x product of m factors from F = {1/2, 1/3, 1/4, 1/6, 3/7, 7/3, 2, 3, 4, 1/sqrt2, 1/sqrt3}; band +/-5%% of the target ratio\n");
    std::printf("     %-14s %-3s %-9s %-7s %-12s %-14s\n", "base", "m", "grammar", "in band", "chance mean", "frac >= obs");
    int primaryCount = -1; double primaryFrac = 1;
    for (int b = 0; b < 2; ++b) for (int m = 1; m <= 5; ++m) {
        auto cs3 = generate(F, m, 1.0, ""); Census r = census(cs3, b == 0 ? rt : rtc);
        std::printf("     %-14s %-3d %-9zu %-7d %-12.3f %-14.4f", b == 0 ? "Omega_rim" : "c/R_p", m, r.n, r.count, r.mean, r.frac);
        if (!r.members.empty() && m <= 3) { std::printf(" members:"); for (auto& x : r.members) std::printf(" %s", x.c_str()); }
        std::printf("\n");
        if (b == 0 && m == 3) { primaryCount = r.count; primaryFrac = r.frac; }
    }
    std::printf("     m = 4 members (Omega_rim): "); { auto c4 = generate(F, 4, 1.0, ""); Census r = census(c4, rt); for (auto& x : r.members) std::printf("%s ", x.c_str()); std::printf("\n"); }
    std::printf("     R1 (P1 rejected as an alpha-free statement if the m = 3 count with base Omega_rim is 0): count = %d -> %s\n", primaryCount, primaryCount == 0 ? "MET (rejected)" : "not met");
    std::printf("     R2 (agreement non-discriminating if the m = 3 count >= 3 or chance fraction > 0.05): count = %d, fraction = %.4f -> %s\n\n", primaryCount, primaryFrac, (primaryCount >= 3 || primaryFrac > 0.05) ? "MET (non-discriminating)" : "not met");

    // ---- T3
    std::printf("[T3] census with a Coulomb-scale factor alpha (report-only), base Omega_rim\n");
    for (int m = 0; m <= 3; ++m) { auto ca = generate(F, m, al, "alpha"); Census r = census(ca, rt);
        std::printf("     alpha x (m = %d): grammar %zu, in band %d, chance mean %.3f, frac >= obs %.4f", m, r.n, r.count, r.mean, r.frac);
        if (m <= 2) { std::printf(" members:"); for (auto& x : r.members) std::printf(" %s", x.c_str()); }
        std::printf("\n"); }
    std::printf("\n");

    // ---- T4
    const double D = 7.0 * Rp / 3.0;
    struct L { const char* nm; double r; } Ls[] = {{"R_p/3", Rp / 3}, {"R_p/2", Rp / 2}, {"2R_p/3", 2 * Rp / 3}, {"R_p", Rp}, {"D/3 = 7R_p/9", D / 3}, {"D/2", D / 2}, {"D = 7R_p/3", D}, {"2R_p", 2 * Rp}};
    std::printf("[T4] report-only: hbar alpha c / r (CONSTRUCTION: E = alpha hbar c / r divided by hbar is alpha c / r) for the registered lengths; B_d = %.5f MeV\n", Bd);
    for (auto& l : Ls) { double E = hb * al * c / l.r / MeV; std::printf("     r = %-14s %.4f fm : %.4f MeV (%+.2f%% vs B_d)\n", l.nm, l.r * 1e15, E, (E / Bd - 1) * 100); }
    std::printf("\n[T5] P3 (He-3, alpha): DEFERRED (NP31 coordination, NP17 geometry)\n");
    return 0;
}
