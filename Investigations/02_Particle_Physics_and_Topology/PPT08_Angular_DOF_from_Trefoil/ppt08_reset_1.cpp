// PPT08 blank-slate run 1 (2026-10-07): orbit-orientation energy of an electron in the wake of a (2,3) torus-knot source.
// Pre-registered in PPT08_RESET_ASSESSMENT_2026-10-07.md §4 (with Amendment 1) before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
using V3 = std::array<double, 3>;
static const double PI = std::numbers::pi;

struct Src { std::vector<V3> x; std::vector<double> w; };
// (p,q) torus knot, R = 1, a given; weights: arclength (speed-weighted) or parameter-uniform
static Src knot(int p, int q, double a, int N, bool arclength) {
    Src s; s.x.resize(N); s.w.resize(N); double sw = 0;
    for (int i = 0; i < N; ++i) {
        double t = 2 * PI * i / N, rho = 1 + a * std::cos(q * t);
        s.x[i] = {rho * std::cos(p * t), rho * std::sin(p * t), a * std::sin(q * t)};
        s.w[i] = arclength ? std::sqrt(a * a * q * q + double(p) * p * rho * rho) : 1.0; sw += s.w[i];
    }
    for (auto& w : s.w) w /= sw; return s;
}
static Src ring(int N) { Src s; s.x.resize(N); s.w.assign(N, 1.0 / N); for (int i = 0; i < N; ++i) { double t = 2 * PI * i / N; s.x[i] = {std::cos(t), std::sin(t), 0}; } return s; }
static Src rotz(const Src& s, double ang) { Src r = s; double c = std::cos(ang), sn = std::sin(ang); for (auto& v : r.x) { double x = v[0], y = v[1]; v[0] = c * x - sn * y; v[1] = sn * x + c * y; } return r; }
static void basis(const V3& n, V3& e1, V3& e2) {
    V3 h = std::fabs(n[2]) < 0.9 ? V3{0, 0, 1} : V3{1, 0, 0};
    e1 = {n[1] * h[2] - n[2] * h[1], n[2] * h[0] - n[0] * h[2], n[0] * h[1] - n[1] * h[0]}; double l = std::sqrt(e1[0] * e1[0] + e1[1] * e1[1] + e1[2] * e1[2]); for (auto& v : e1) v /= l;
    e2 = {n[1] * e1[2] - n[2] * e1[1], n[2] * e1[0] - n[0] * e1[2], n[0] * e1[1] - n[1] * e1[0]};
}
// first-order orbit energy in units of kappa/R: E = -< sum w / |X - x| > over a circle of radius r (units of R), normal n
static double orbitE(const Src& s, double r, const V3& n, int M) {
    V3 e1, e2; basis(n, e1, e2); double tot = 0;
    for (int k = 0; k < M; ++k) {
        double ps = 2 * PI * (k + 0.5) / M, c = std::cos(ps), sn = std::sin(ps);
        double X = r * (c * e1[0] + sn * e2[0]), Y = r * (c * e1[1] + sn * e2[1]), Z = r * (c * e1[2] + sn * e2[2]), sum = 0;
        for (size_t i = 0; i < s.x.size(); ++i) { double dx = X - s.x[i][0], dy = Y - s.x[i][1], dz = Z - s.x[i][2]; sum += s.w[i] / std::sqrt(dx * dx + dy * dy + dz * dz); }
        tot += sum;
    }
    return -tot / M;
}
static void moments(const Src& s, double& sz, double& sxy) { double zz = 0, xx = 0, yy = 0; for (size_t i = 0; i < s.x.size(); ++i) { zz += s.w[i] * s.x[i][2] * s.x[i][2]; xx += s.w[i] * s.x[i][0] * s.x[i][0]; yy += s.w[i] * s.x[i][1] * s.x[i][1]; } sz = zz; sxy = 0.5 * (xx + yy); }

int main() {
    std::printf("PPT08 blank-slate run 1 (pre-registered 2026-10-07)\n====================================================\n\n");
    int fails = 0; const V3 Z = {0, 0, 1}, X = {1, 0, 0};
    const int p = 2, q = 3; const double aR = std::sqrt(double(p) / q);   // a/R = v_T/v_P = sqrt(p/q) (PPT01 closure)
    // ---- V1
    Src rg = ring(2000); double r1 = 50, dnum = orbitE(rg, r1, Z, 720) - orbitE(rg, r1, X, 720), dan = -3.0 / (8 * r1 * r1 * r1);
    Src pt; pt.x = {{0, 0, 0}}; pt.w = {1.0}; double mono = orbitE(pt, 7.0, Z, 64) + 1.0 / 7.0;
    bool v1 = std::fabs(dnum / dan - 1) < 5e-3 && std::fabs(mono) < 1e-14;
    std::printf("[V1] ring r/R = 50: numerical E(z) - E(x) = %.6e, analytic -3/(8 r^3) = %.6e (ratio %.5f) ; single source monopole residual %.1e -> %s\n", dnum, dan, dnum / dan, mono, v1 ? "met" : "NOT MET");
    if (!v1) ++fails;
    // ---- V2
    Src k1 = knot(p, q, aR, 21000, true), k2 = knot(p, q, aR, 84000, true); double r2 = 20;
    double A1 = orbitE(k1, r2, Z, 720) - orbitE(k1, r2, X, 720), A2 = orbitE(k2, r2, Z, 2880) - orbitE(k2, r2, X, 2880);
    bool v2 = std::fabs(A1 / A2 - 1) < 1e-9;
    std::printf("[V2] knot r/R = 20 anisotropy: (N,M) = (21000,720): %.10e ; (84000,2880): %.10e ; relative difference %.2e -> %s\n", A1, A2, std::fabs(A1 / A2 - 1), v2 ? "met" : "NOT MET");
    if (!v2) ++fails;
    // ---- V3
    Src kp = knot(p, q, aR, 84000, false); double szp, sxyp; moments(kp, szp, sxyp);
    double szA = aR * aR / 2, sxyA = (1 + aR * aR / 2) / 2;
    bool v3 = std::fabs(szp / szA - 1) < 1e-6 && std::fabs(sxyp / sxyA - 1) < 1e-6;
    std::printf("[V3] parameter-uniform weights: s_z = %.8f (analytic %.8f), s_xy = %.8f (analytic %.8f) -> %s\n", szp, szA, sxyp, sxyA, v3 ? "met" : "NOT MET");
    if (!v3) ++fails;
    // ---- V4
    Src ka = knot(p, q, aR, 21000, true), kr = rotz(ka, 2 * PI / 3); double wsym = 0;
    for (V3 n : {V3{0.3, 0.5, 0.8}, V3{1, 0, 0}, V3{0.2, -0.9, 0.1}}) { double l = std::sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]); for (auto& v : n) v /= l; double e0 = orbitE(ka, 12, n, 360), e1 = orbitE(kr, 12, n, 360); V3 m = {-n[0], -n[1], -n[2]}; double e2 = orbitE(ka, 12, m, 360); wsym = std::max({wsym, std::fabs(e1 / e0 - 1), std::fabs(e2 / e0 - 1)}); }
    bool v4 = wsym < 1e-12;
    std::printf("[V4] rotation by 2 pi/3 and n -> -n: worst relative change %.2e -> %s\n\n", wsym, v4 ? "met" : "NOT MET");
    if (!v4) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // ---- T1
    std::printf("[T1] D(r) = (E(z) - E(x)) r^3 / (kappa R^2) for the (2,3) knot, arclength weights, a/R = %.5f\n", aR);
    Src K = knot(p, q, aR, 84000, true); double D[3]; double rs[3] = {20, 40, 80};
    for (int i = 0; i < 3; ++i) { double a = orbitE(K, rs[i], Z, 1440) - orbitE(K, rs[i], X, 1440); D[i] = a * rs[i] * rs[i] * rs[i]; std::printf("     r/R = %3.0f : D = %.8f\n", rs[i], D[i]); }
    double R1a = (4 * D[1] - D[0]) / 3, R1b = (4 * D[2] - D[1]) / 3, c2num = (16 * R1b - R1a) / 15;
    double sz, sxy; moments(K, sz, sxy); double c2mom = 3 * (sz - sxy) / 4;
    std::printf("     Richardson (r^-2 terms removed): %.8f (20,40), %.8f (40,80), %.8f (second order) ; route 2 (arclength second moments): s_z = %.8f, s_xy = %.8f, c2 = 3(s_z - s_xy)/4 = %.8f ; relative difference %.2e\n", R1a, R1b, c2num, sz, sxy, c2mom, std::fabs(c2num / c2mom - 1));
    double c2par = 3 * (szp - sxyp) / 4;
    std::printf("     parameter-uniform weights (sensitivity): c2 = %.8f (relative to arclength %.4f)\n\n", c2par, c2par / c2mom);

    // ---- T2, T3
    const double kappa = M::alpha * M::hbar * M::c, lamp = M::hbar / (M::m_p * M::c);
    const double vT = std::sqrt(double(p) / (p + q)), R_G1 = lamp / vT, a_G1 = lamp / std::sqrt(double(q) / (p + q)); (void)a_G1;
    const double R_G2 = M::R_p / (1 + aR);
    const double target = law_VI::angular::lamb_shift_measured_MHz * 1e6, tHe = law_VI::angular::lamb_shift_He_plus_measured_MHz * 1e6;
    struct G { const char* nm; double R; } gs[2] = {{"G1 PPT01 closure (R = hbar/(m_p v_T))", R_G1}, {"G2 outer extent R + a = R_p", R_G2}};
    std::printf("[T2/T3] DeltaE = E(equatorial) - E(polar) = kappa c2 R^2 / r^3, kappa = alpha hbar c = %.4e J m ; r = 4 a_0 (H n = 2)\n", kappa);
    bool signRej = false, magRej = false;
    for (int gi = 0; gi < 2; ++gi) {
        double R = gs[gi].R, r = 4 * M::a_0, dE = kappa * c2mom * R * R / (r * r * r), nu = dE / M::h;
        double rHe = 2 * M::a_0, dEHe = 2 * kappa * c2mom * R * R / (rHe * rHe * rHe), nuHe = dEHe / M::h;
        std::printf("     %-40s R = %.4e m a = %.4e m : DeltaE = %+.4e J = %+.4f Hz ; vs 1057.845 MHz: ratio %.3e ; He+ (r = 2 a_0, 2 kappa): %+.4f Hz, ratio to 14041.13 MHz %.3e\n", gs[gi].nm, R, R * aR, dE, nu, std::fabs(nu) / target, nuHe, std::fabs(nuHe) / tHe);
        if (gi == 0) { signRej = (c2mom < 0); magRej = !(std::fabs(nu) >= 0.1 * target && std::fabs(nu) <= 10 * target); }
    }
    std::printf("     R1 (H1 rejected if DeltaE < 0 on both routes, primary geometry): c2 route 1 = %+.6f, route 2 = %+.6f -> %s\n", c2num, c2mom, (c2num < 0 && c2mom < 0) ? "MET (rejected)" : "not met");
    std::printf("     R2 (H2 rejected if |DeltaE|/h is outside [0.1, 10] x 1057.845 MHz, primary geometry): %s\n\n", magRej ? "MET (rejected)" : "not met");
    (void)signRej;

    // ---- T4
    std::printf("[T4] E(phi_n) for polar orbit normals n = (cos phi, sin phi, 0): Fourier modes (units of the monopole |E0| = 1/r)\n");
    Src K4 = knot(p, q, aR, 21000, true); const int NP = 48;
    for (double r : {10.0, 20.0, 40.0}) {
        std::vector<double> E(NP); for (int k = 0; k < NP; ++k) { double ph = 2 * PI * k / NP; E[k] = orbitE(K4, r, V3{std::cos(ph), std::sin(ph), 0}, 720); }
        std::printf("     r/R = %2.0f :", r);
        double mag[13]; for (int m = 0; m <= 12; ++m) { double cs = 0, sn = 0; for (int k = 0; k < NP; ++k) { cs += E[k] * std::cos(2 * PI * m * k / NP); sn += E[k] * std::sin(2 * PI * m * k / NP); } mag[m] = std::sqrt(cs * cs + sn * sn) / NP * (m ? 2 : 1); }
        for (int m : {0, 1, 2, 3, 4, 5, 6, 12}) std::printf(" |c%d| = %.3e", m, m == 0 ? mag[0] * r : mag[m] * r);
        std::printf("  (c_m x r/kappa R^-1; m = 0 is the monopole)\n");
        double c3 = mag[3] * r, c6 = mag[6] * r; std::printf("          |c3|/|c6| = %.3e ; |c6| (relative to monopole) = %.3e\n", c6 > 0 ? c3 / c6 : 0.0, mag[6] / mag[0]);
    }
    std::printf("     (period of E(phi_n): invariance under 2 pi/3 and under n -> -n, i.e. a shift of pi, gives period pi/3 and modes m = 0, 6, 12)\n");
    std::printf("\n[T5] P1 (deuterium), P2 (muonic hydrogen): DEFERRED (deuteron geometry NP17/NP06; no muon mass in the engine, no muonic datum in Datasets) ; P3 not a test of this mechanism\n");
    return 0;
}
