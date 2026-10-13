// FLM15-inf R2 (2026-10-06) — independent regular-grid quadrature of trace(K) = integral |g|^2 dV
// for the registered circle and (2,3) trefoil filaments, plus V_lock / V_wake / 6/7 checks.
// Pre-registered in R2_REOPEN_2026-10-05.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <array>
#include <cmath>
#include <cstdio>
#include <thread>
#include <vector>
#include <algorithm>
#include <numbers>

using V3 = std::array<double, 3>;
static const double PI = std::numbers::pi;

struct Fil { std::vector<V3> x, dl; double length = 0, maxabs = 0; };
static Fil make(bool trefoil, double a, int N, bool rms_norm = false) {
    std::vector<V3> P(N);
    for (int i = 0; i < N; ++i) {
        double t = 2.0 * PI * i / N;
        if (trefoil) P[i] = {(1 + a * std::cos(3 * t)) * std::cos(2 * t), (1 + a * std::cos(3 * t)) * std::sin(2 * t), a * std::sin(3 * t)};
        else P[i] = {std::cos(t), std::sin(t), 0.0};
    }
    if (rms_norm) {   // A3: sealed convention, centroid removed and unit RMS distance from the centre
        V3 m{0, 0, 0}; for (auto& p : P) for (int k = 0; k < 3; ++k) m[k] += p[k] / N;
        double r2 = 0; for (auto& p : P) { for (int k = 0; k < 3; ++k) p[k] -= m[k]; r2 += p[0]*p[0] + p[1]*p[1] + p[2]*p[2]; }
        double s = 1.0 / std::sqrt(r2 / N); for (auto& p : P) for (int k = 0; k < 3; ++k) p[k] *= s;
    }
    Fil f;
    for (int i = 0; i < N; ++i) {
        const V3& p = P[i]; const V3& q = P[(i + 1) % N];
        f.x.push_back({(p[0] + q[0]) / 2, (p[1] + q[1]) / 2, (p[2] + q[2]) / 2});
        V3 d{q[0] - p[0], q[1] - p[1], q[2] - p[2]}; f.dl.push_back(d);
        f.length += std::sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]);
        for (double c : p) f.maxabs = std::max(f.maxabs, std::fabs(c));
    }
    return f;
}
static V3 field(const Fil& f, V3 x, double core) {
    V3 g{0, 0, 0};
    for (size_t i = 0; i < f.x.size(); ++i) {
        double rx = x[0] - f.x[i][0], ry = x[1] - f.x[i][1], rz = x[2] - f.x[i][2];
        double d2 = rx*rx + ry*ry + rz*rz + core*core, inv = 1.0 / (d2 * std::sqrt(d2));
        const V3& l = f.dl[i];
        g[0] += (l[1]*rz - l[2]*ry) * inv; g[1] += (l[2]*rx - l[0]*rz) * inv; g[2] += (l[0]*ry - l[1]*rx) * inv;
    }
    const double pre = 1.0 / (4.0 * PI);   // A1: sealed instrument prefactor circulation/(4 pi)
    g[0] *= pre; g[1] *= pre; g[2] *= pre;
    return g;
}
static double stiffness(const Fil& f, double H, int n, double core) {
    const double h = 2.0 * H / n;
    unsigned nt = std::max(1u, std::thread::hardware_concurrency());
    std::vector<double> part(nt, 0.0); std::vector<std::thread> th;
    for (unsigned t = 0; t < nt; ++t) th.emplace_back([&, t] {
        double s = 0;
        for (int i = (int)t; i < n; i += (int)nt) {
            double x = -H + (i + 0.5) * h;
            for (int j = 0; j < n; ++j) { double y = -H + (j + 0.5) * h;
                for (int k = 0; k < n; ++k) { double z = -H + (k + 0.5) * h; V3 g = field(f, {x, y, z}, core); s += g[0]*g[0] + g[1]*g[1] + g[2]*g[2]; } }
        }
        part[t] = s;
    });
    for (auto& t : th) t.join();
    double s = 0; for (double v : part) s += v; return s * h * h * h;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    std::printf("FLM15-inf R2 — independent quadrature (pre-registered 2026-10-06)\n=================================================================\n\n");
    const double core = 0.12; const int NSEG = 192; int fails = 0;

    Fil circ = make(false, 0, NSEG);
    // V1/V2 (amended A2): convergence-order tests at N = 96, 192, 384, with the sealed 1/(4 pi) prefactor
    double e1[3], e2[3]; int Ns[3] = {96, 192, 384};
    for (int q = 0; q < 3; ++q) {
        Fil c = make(false, 0, Ns[q]);
        V3 a0 = field(c, {0, 0, 0}, core); double r0 = 2 * PI / std::pow(1 + core * core, 1.5) / (4 * PI);
        V3 a3 = field(c, {0, 0, 3.0}, core); double r3 = 2 * PI / std::pow(1 + 9 + core * core, 1.5) / (4 * PI);
        e1[q] = std::fabs(std::sqrt(a0[0]*a0[0] + a0[1]*a0[1] + a0[2]*a0[2]) - r0) / r0; e2[q] = std::fabs(a3[2] - r3) / r3;
    }
    bool v1 = e1[2] < 1e-4 && e1[1] / e1[2] > 3 && e1[1] / e1[2] < 5;
    bool v2 = e2[2] < 1e-4 && e2[1] / e2[2] > 3 && e2[1] / e2[2] < 5;
    std::printf("[V1] circle centre-field relative error N=96,192,384: %.2e %.2e %.2e ; ratio(192/384) %.2f -> %s\n", e1[0], e1[1], e1[2], e1[1] / e1[2], v1 ? "PASS" : "FAIL");
    std::printf("[V2] circle on-axis (z=3) relative error N=96,192,384: %.2e %.2e %.2e ; ratio(192/384) %.2f -> %s\n", e2[0], e2[1], e2[2], e2[1] / e2[2], v2 ? "PASS" : "FAIL");
    if (!v1) ++fails; if (!v2) ++fails;

    auto gl = [](int n, std::vector<double>& xs, std::vector<double>& ws) {
        xs.resize(n); ws.resize(n);
        for (int i = 0; i < n; ++i) {
            double z = std::cos(PI * (i + 0.75) / (n + 0.5)), pp = 0;
            for (int it = 0; it < 100; ++it) { double p1 = 1, p2 = 0; for (int j = 0; j < n; ++j) { double p3 = p2; p2 = p1; p1 = ((2.0*j + 1) * z * p2 - j * p3) / (j + 1); } pp = n * (z * p1 - p2) / (z*z - 1); double dz = p1 / pp; z -= dz; if (std::fabs(dz) < 1e-15) break; }
            xs[i] = z; ws[i] = 2.0 / ((1 - z*z) * pp * pp);
        }
    };
    std::vector<double> xs, ws; gl(64, xs, ws);
    double Vl = 0; for (int i = 0; i < 64; ++i) { double r = 0.5 * (xs[i] + 1.0); Vl += 0.5 * ws[i] * 4 * PI * r * r * std::sqrt(r); }
    double Vw = 4 * PI / 3 - Vl;
    double eng_l = sdt::laws::law_IV::locked_engaged_volume_sphere(1.0), eng_w = sdt::laws::law_IV::wake_volume_sphere(1.0);
    bool v4 = std::fabs(Vl - 8 * PI / 7) < 1e-12 && std::fabs(Vw - 4 * PI / 21) < 1e-12 && std::fabs(Vl / (4 * PI / 3) - 6.0 / 7.0) < 1e-12 && std::fabs(eng_l - Vl) < 1e-12 && std::fabs(eng_w - Vw) < 1e-12;
    std::printf("[V4] V_lock = %.15f (8pi/7 = %.15f); V_wake = %.15f (4pi/21 = %.15f); fraction %.15f; engine functions %.15f, %.15f -> %s\n", Vl, 8 * PI / 7, Vw, 4 * PI / 21, Vl / (4 * PI / 3), eng_l, eng_w, v4 ? "PASS" : "FAIL");
    if (!v4) ++fails;

    const double asp[4] = {0.35, 0.50, std::sqrt(2.0 / 3.0), 0.90};
    const double sc[4] = {1.672938, 1.677982, 1.682593, 1.682955}, st[4] = {4.370854, 4.098237, 4.504342, 4.766977};
    const double sr[4] = {2.61268, 2.44236, 2.67702, 2.83250};
    auto Hbox = [&](double a) { return std::max(1.0, 1.0 + a) + 5 * core; };
    {
        double H = Hbox(asp[0]); int n1 = (int)std::lround(2 * H / 0.03), n2 = (int)std::lround(2 * H / 0.02);
        double a1 = stiffness(circ, H, n1, core), a2 = stiffness(circ, H, n2, core);
        bool v3 = std::fabs(a1 - a2) / a2 < 0.01;
        std::printf("[V3] circle stiffness h=0.03: %.6f ; h=0.02: %.6f ; relative change %.2e -> %s\n\n", a1, a2, (a1 - a2) / a2, v3 ? "PASS" : "FAIL");
        if (!v3) ++fails;
    }
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    std::printf("[T1/T2] independent grid (h = 0.02) vs sealed QMC rows (orientation 0), SEALED RMS convention (A3)\n");
    std::printf("  a      | circle: indep   sealed   diff%%  | trefoil: indep   sealed   diff%% | ratio: indep   sealed   diff%% | L3/L1  ratio/(L3/L1)  J/L circ  J/L tref\n");
    bool all = true;
    for (int q = 0; q < 4; ++q) {
        Fil cn = make(false, 0, NSEG, true), tre = make(true, asp[q], NSEG, true);
        double H = std::max(cn.maxabs, tre.maxabs) + 5 * core; int n = (int)std::lround(2 * H / 0.02);
        double Jc = stiffness(cn, H, n, core), Jt = stiffness(tre, H, n, core), r = Jt / Jc;
        double dc = (Jc - sc[q]) / sc[q] * 100, dt = (Jt - st[q]) / st[q] * 100, dr = (r - sr[q]) / sr[q] * 100;
        if (std::fabs(dc) > 3 || std::fabs(dt) > 3 || std::fabs(dr) > 3) all = false;
        std::printf("  %.4f | %8.5f %8.5f %+6.2f | %8.5f %8.5f %+6.2f | %7.5f %7.5f %+6.2f | %.4f  %.4f  %.4f  %.4f\n",
                    asp[q], Jc, sc[q], dc, Jt, st[q], dt, r, sr[q], dr, tre.length / cn.length, r / (tre.length / cn.length), Jc / cn.length, Jt / tre.length);
    }
    std::printf("\nT1 gate (every circle, trefoil and ratio within 3%% of the sealed row, RMS convention): %s\n\n", all ? "met" : "NOT MET");
    std::printf("[T3] convention sensitivity (report only): ratio J3/J1 with unit-RMS-radius vs unit-major-radius normalisation\n");
    std::printf("  a      | RMS convention   major-radius convention   difference\n");
    for (int q = 0; q < 4; ++q) {
        double rr[2];
        for (int cv = 0; cv < 2; ++cv) {
            Fil cn = make(false, 0, NSEG, cv == 0), tre = make(true, asp[q], NSEG, cv == 0);
            double H = std::max(cn.maxabs, tre.maxabs) + 5 * core; int n = (int)std::lround(2 * H / 0.02);
            rr[cv] = stiffness(tre, H, n, core) / stiffness(cn, H, n, core);
        }
        std::printf("  %.4f | %8.5f         %8.5f                  %+6.1f%%\n", asp[q], rr[0], rr[1], (rr[1] - rr[0]) / rr[0] * 100);
    }
    return 0;
}
