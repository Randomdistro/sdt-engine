// FLM07 R2 (2026-10-05) — voids from an explicit lattice, glancing locus, price monotonicity, R_p test.
// Pre-registered in R2_REOPEN_2026-10-05.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>
#include <array>
#include <map>
#include <random>
#include <algorithm>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
using V3 = std::array<double, 3>;

struct Lat { std::vector<V3> c; double R; };
static double nearest(const Lat& L, V3 p, std::vector<double>* all = nullptr) {
    double best = 1e9;
    for (auto& s : L.c) for (int i = -1; i <= 1; ++i) for (int j = -1; j <= 1; ++j) for (int k = -1; k <= 1; ++k) {
        double dx = p[0]-(s[0]+i), dy = p[1]-(s[1]+j), dz = p[2]-(s[2]+k), d = std::sqrt(dx*dx+dy*dy+dz*dz);
        if (all) all->push_back(d);
        best = std::min(best, d);
    }
    return best;
}
struct Hole { V3 pos; int coord; double rR; };
// Exact method (run 3): every hole is the circumcentre of four lattice centres whose circumsphere contains no other centre.
static std::vector<Hole> find_holes(const Lat& L, int /*starts*/, unsigned /*seed*/) {
    std::vector<V3> P;
    for (auto& s : L.c) for (int i = -1; i <= 1; ++i) for (int j = -1; j <= 1; ++j) for (int k = -1; k <= 1; ++k) P.push_back({s[0]+i, s[1]+j, s[2]+k});
    const int n = (int)P.size();
    auto d2 = [&](const V3& a, const V3& b) { double x = a[0]-b[0], y = a[1]-b[1], z = a[2]-b[2]; return x*x+y*y+z*z; };
    std::map<std::array<long, 3>, Hole> found;
    for (int a = 0; a < n; ++a) for (int b = a+1; b < n; ++b) { if (d2(P[a], P[b]) > 4.0) continue;
      for (int c = b+1; c < n; ++c) { if (d2(P[a], P[c]) > 4.0 || d2(P[b], P[c]) > 4.0) continue;
        for (int d = c+1; d < n; ++d) { if (d2(P[a], P[d]) > 4.0 || d2(P[b], P[d]) > 4.0 || d2(P[c], P[d]) > 4.0) continue;
          double A[3][3], rhs[3]; const V3* Q[3] = {&P[b], &P[c], &P[d]};
          for (int r = 0; r < 3; ++r) { for (int k = 0; k < 3; ++k) A[r][k] = 2.0 * ((*Q[r])[k] - P[a][k]); rhs[r] = 0; for (int k = 0; k < 3; ++k) rhs[r] += (*Q[r])[k]*(*Q[r])[k] - P[a][k]*P[a][k]; }
          double det = A[0][0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1]) - A[0][1]*(A[1][0]*A[2][2]-A[1][2]*A[2][0]) + A[0][2]*(A[1][0]*A[2][1]-A[1][1]*A[2][0]);
          if (std::fabs(det) < 1e-9) continue;
          V3 x; for (int k = 0; k < 3; ++k) { double B[3][3]; for (int r = 0; r < 3; ++r) for (int m = 0; m < 3; ++m) B[r][m] = (m == k) ? rhs[r] : A[r][m];
            x[k] = (B[0][0]*(B[1][1]*B[2][2]-B[1][2]*B[2][1]) - B[0][1]*(B[1][0]*B[2][2]-B[1][2]*B[2][0]) + B[0][2]*(B[1][0]*B[2][1]-B[1][1]*B[2][0])) / det; }
          double rad2 = d2(x, P[a]); if (rad2 > 1.0) continue;
          if (x[0] < -1e-9 || x[0] >= 1 - 1e-9 || x[1] < -1e-9 || x[1] >= 1 - 1e-9 || x[2] < -1e-9 || x[2] >= 1 - 1e-9) continue;
          bool empty = true; int coord = 0;
          for (int m = 0; m < n; ++m) { double dm = d2(x, P[m]); if (dm < rad2 - 1e-9) { empty = false; break; } if (std::fabs(dm - rad2) < 1e-9) ++coord; }
          if (!empty) continue;
          V3 w = x; for (auto& v : w) { v -= std::floor(v); if (v > 1 - 1e-7) v = 0; }
          std::array<long, 3> key{std::lround(w[0]*1e5), std::lround(w[1]*1e5), std::lround(w[2]*1e5)};
          found[key] = {w, coord, std::sqrt(rad2) / L.R - 1.0};
        } } }
    std::vector<Hole> out; for (auto& kv : found) out.push_back(kv.second); return out;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    std::printf("FLM07 R2 — voids, glancing locus, price sign, R_p test (pre-registered 2026-10-05)\n");
    std::printf("==================================================================================\n\n");
    int fails = 0;
    const double hb = M::hbar, c = M::c, mp = M::m_p, a0 = M::a_0, al = M::alpha;
    const double lam = hb / (mp * c);

    // ---- V1 ----
    Lat sc{{{0, 0, 0}}, 0.5};
    auto hs = find_holes(sc, 80, 1);
    bool v1a = hs.size() == 1 && hs[0].coord == 8 && std::fabs(hs[0].rR - (std::sqrt(3.0) - 1.0)) < 1e-6;
    std::printf("[V1a] simple cubic: %zu hole class(es); coordination %d; r/R = %.7f (sqrt3-1 = %.7f) -> %s\n", hs.size(), hs.empty() ? 0 : hs[0].coord, hs.empty() ? 0 : hs[0].rR, std::sqrt(3.0) - 1.0, v1a ? "PASS" : "FAIL");
    Lat fcc{{{0, 0, 0}, {0.5, 0.5, 0}, {0.5, 0, 0.5}, {0, 0.5, 0.5}}, std::sqrt(2.0) / 4.0};
    auto hf = find_holes(fcc, 1500, 2);
    int nt = 0, no = 0, other = 0; double rt = 0, ro = 0;
    for (auto& h : hf) { if (h.coord == 4) { ++nt; rt = h.rR; } else if (h.coord == 6) { ++no; ro = h.rR; } else ++other; }
    bool v1b = nt == 8 && no == 4 && other == 0 && std::fabs(rt - (std::sqrt(1.5) - 1)) < 1e-6 && std::fabs(ro - (std::sqrt(2.0) - 1)) < 1e-6;
    std::printf("[V1b] FCC conventional cell (4 spheres): tetrahedral holes %d (coord 4, r/R %.7f vs %.7f), octahedral holes %d (coord 6, r/R %.7f vs %.7f), other %d -> %s\n",
                nt, rt, std::sqrt(1.5) - 1, no, ro, std::sqrt(2.0) - 1, other, v1b ? "PASS" : "FAIL");
    std::printf("      per sphere: %.1f tetrahedral : %.1f octahedral\n", nt / 4.0, no / 4.0);
    bool v2 = std::fabs(lam - 2.10309e-16) / 2.10309e-16 < 1e-5;
    std::printf("[V2] hbar/(m_p c) = %.5e m (2.10309e-16) -> %s\n\n", lam, v2 ? "PASS" : "FAIL");
    if (!(v1a && v1b && v2)) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");

    // ---- T1 ----
    std::printf("[T1] glancing locus: k(r) = (1/alpha) sqrt(r/a0), v = c/k, theta = arccos k\n");
    struct P { const char* nm; double r; double kk, vv, th; } pts[4] = {{"throat", 0.010e-15, 0.0596, 16.79, 86.58}, {"deep", 0.554e-15, 0.4434, 2.255, 63.68}, {"R_p", M::R_p, 0.5464, 1.830, 56.88}, {"r_e", M::r_e, 1.0000, 1.000, 0.00}};
    for (auto& p : pts) {
        double k = std::sqrt(p.r / a0) / al, th = std::acos(std::min(1.0, k)) * 180 / std::numbers::pi;
        std::printf("     %-7s r = %.4e m  k = %.4f (rec %.4f)  v = %.3f c (rec %.3f)  theta = %.2f deg (rec %.2f)\n", p.nm, p.r, k, p.kk, 1.0 / k, p.vv, th, p.th);
    }
    std::printf("     k(r_e) = %.12f (r_e = alpha^2 a0 exactly)\n\n", std::sqrt(M::r_e / a0) / al);

    // ---- T2 ----
    const double rt_ = std::sqrt(1.5) - 1, ro_ = std::sqrt(2.0) - 1;
    std::printf("[T2] octahedral/tetrahedral price ratio (q_oct/q_tet = 1.5) for prices ~ r^n q^m\n");
    std::printf("     n\\m |      m=0 |      m=1\n");
    for (int n : {1, 2, 3, 4}) std::printf("     %d   | %8.4f | %8.4f\n", n, std::pow(ro_ / rt_, n), std::pow(ro_ / rt_, n) * 1.5);
    std::printf("     decreasing prices ~ r^-n q^-m:  n=1,m=0 -> %.4f ; n=3,m=1 -> %.4f\n", std::pow(ro_ / rt_, -1), std::pow(ro_ / rt_, -3) / 1.5);
    std::printf("     recorded: 6.2604 (n=3,m=0) and 9.3906 (n=3,m=1): reproduced as %.4f and %.4f\n", std::pow(ro_ / rt_, 3), std::pow(ro_ / rt_, 3) * 1.5);
    std::printf("     reading: every price increasing in void size selects the tetrahedral void; every price decreasing in void size selects the octahedral. The selection is the sign of the premise.\n\n");

    // ---- T3 ----
    const double R4 = 4 * lam, R6 = 6 * lam;
    struct Meas { const char* nm; double v, s; const char* st; } ms[3] = {
        {"CODATA 2022", 8.4075e-16, 0.0064e-16, "fetched 2026-10-05 physics.nist.gov"},
        {"CODATA 2018", 8.414e-16, 0.019e-16, "repo (PPT09 text); VERIFY"},
        {"muonic-H (GOM02 prompt)", 8.4087e-16, 0.0039e-16, "repo (GOM02 prompt); VERIFY"}};
    std::printf("[T3] R_4 = 4 hbar/(m_p c) = %.5e m ; R_6 = 6 hbar/(m_p c) = %.5e m ; stored M::R_p = %.4e m\n", R4, R6, M::R_p);
    bool r4_in = true, r6_out = true;
    for (auto& m : ms) {
        double d4 = (R4 - m.v) / m.v * 100, s4 = (R4 - m.v) / m.s, d6 = (R6 - m.v) / m.v * 100, s6 = (R6 - m.v) / m.s;
        std::printf("     %-24s %.4e +- %.1e  [%s]\n       R_4: %+7.4f%% (%+5.2f sigma)   R_6: %+8.3f%% (%+7.1f sigma)\n", m.nm, m.v, m.s, m.st, d4, s4, d6, s6);
        if (std::fabs(s4) > 3.0) r4_in = false; if (std::fabs(s6) <= 3.0) r6_out = false;
    }
    std::printf("     R_4 within 3 sigma of all three: %s ; R_6 beyond 3 sigma of all three: %s\n\n", r4_in ? "yes" : "no", r6_out ? "yes" : "no");

    // ---- T4 ----
    const double ratio = ms[0].v / lam, off = std::fabs(ratio - std::round(ratio));
    std::printf("[T4] chance coincidence: R_p/lam_p = %.5f (CODATA 2022), distance from nearest integer %.5f\n", ratio, off);
    std::printf("     P(random real within that distance of ANY integer) = 2 x %.5f = %.4f\n", off, 2 * off);
    std::printf("     P(within that distance of 4 or 6, ratio uniform on [1,8)) = 2 x 2 x %.5f / 7 = %.4f\n", off, 4 * off / 7.0);
    std::printf("     (the integer was identified from this same datum: post-hoc; the mechanism supplies a second, independent selection of q = 4)\n\n");
    std::printf("SUMMARY: validations met; R_4 within 3 sigma: %s; R_6 excluded: %s\n", r4_in ? "yes" : "no", r6_out ? "yes" : "no");
    return 0;
}
