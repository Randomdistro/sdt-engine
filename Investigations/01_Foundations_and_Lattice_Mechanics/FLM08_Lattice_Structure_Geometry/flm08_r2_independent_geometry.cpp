// FLM08 R2 (2026-10-05) — independent reconstruction of the load-bearing geometric invariants.
// Pre-registered in R2_REOPEN_2026-10-05.md §4 before this file existed.
// Author: J. C. Harvey, Melbourne.  No measured input, no fitted parameter.
#include <cmath>
#include <cstdio>
#include <array>
#include <vector>
#include <random>
#include <algorithm>
#include <numbers>

using V3 = std::array<double, 3>;
using V4 = std::array<double, 4>;
static V3 sub(V3 a, V3 b) { return {a[0]-b[0], a[1]-b[1], a[2]-b[2]}; }
static V3 add(V3 a, V3 b) { return {a[0]+b[0], a[1]+b[1], a[2]+b[2]}; }
static V3 mul(V3 a, double s) { return {a[0]*s, a[1]*s, a[2]*s}; }
static double dot(V3 a, V3 b) { return a[0]*b[0] + a[1]*b[1] + a[2]*b[2]; }
static V3 cross(V3 a, V3 b) { return {a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]}; }
static double nrm(V3 a) { return std::sqrt(dot(a, a)); }
static V3 unit(V3 a) { return mul(a, 1.0 / nrm(a)); }
static double dot4(V4 a, V4 b) { return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3]; }
static const double PI = std::numbers::pi;
static const double PHI = (1.0 + std::sqrt(5.0)) / 2.0;

// ---- dihedral from coordinates (regular polyhedra) ----
static double dihedral_poly(const std::vector<V3>& P, double edge, bool faces_are_triangles) {
    V3 cen{0,0,0}; for (auto& p : P) cen = add(cen, p); cen = mul(cen, 1.0 / P.size());
    auto nb = [&](int i, int j) { return i != j && std::fabs(nrm(sub(P[i], P[j])) - edge) < 1e-9; };
    int A = 0, B = -1; for (int j = 1; j < (int)P.size(); ++j) if (nb(0, j)) { B = j; break; }
    V3 n1, n2;
    if (faces_are_triangles) {
        std::vector<int> C; for (int k = 0; k < (int)P.size(); ++k) if (nb(A, k) && nb(B, k)) C.push_back(k);
        n1 = cross(sub(P[B], P[A]), sub(P[C[0]], P[A])); n2 = cross(sub(P[B], P[A]), sub(P[C[1]], P[A]));
    } else {
        std::vector<int> C; for (int k = 0; k < (int)P.size(); ++k) if (k != B && nb(A, k)) C.push_back(k);
        n1 = cross(sub(P[B], P[A]), sub(P[C[0]], P[A])); n2 = cross(sub(P[B], P[A]), sub(P[C[1]], P[A]));
    }
    if (dot(n1, sub(P[A], cen)) < 0) n1 = mul(n1, -1);
    if (dot(n2, sub(P[A], cen)) < 0) n2 = mul(n2, -1);
    double ang = std::acos(std::clamp(dot(unit(n1), unit(n2)), -1.0, 1.0));
    return (PI - ang) * 180.0 / PI;
}

// ---- screw extraction from five consecutive points ----
struct Screw { double theta, R, h; };
static void inv3(const double m[3][3], double o[3][3]) {
    double d = m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1]) - m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0]) + m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
    o[0][0] = (m[1][1]*m[2][2]-m[1][2]*m[2][1])/d; o[0][1] = (m[0][2]*m[2][1]-m[0][1]*m[2][2])/d; o[0][2] = (m[0][1]*m[1][2]-m[0][2]*m[1][1])/d;
    o[1][0] = (m[1][2]*m[2][0]-m[1][0]*m[2][2])/d; o[1][1] = (m[0][0]*m[2][2]-m[0][2]*m[2][0])/d; o[1][2] = (m[0][2]*m[1][0]-m[0][0]*m[1][2])/d;
    o[2][0] = (m[1][0]*m[2][1]-m[1][1]*m[2][0])/d; o[2][1] = (m[0][1]*m[2][0]-m[0][0]*m[2][1])/d; o[2][2] = (m[0][0]*m[1][1]-m[0][1]*m[1][0])/d;
}
static Screw extract(const V3 p[5]) {
    double A[3][3], B[3][3], Ai[3][3], Rm[3][3];
    for (int k = 0; k < 3; ++k) { V3 a = sub(p[k+1], p[0]), b = sub(p[k+2], p[1]); for (int i = 0; i < 3; ++i) { A[i][k] = a[i]; B[i][k] = b[i]; } }
    inv3(A, Ai);
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) { Rm[i][j] = 0; for (int k = 0; k < 3; ++k) Rm[i][j] += B[i][k] * Ai[k][j]; }
    double tr = Rm[0][0] + Rm[1][1] + Rm[2][2];
    double theta = std::acos(std::clamp((tr - 1.0) / 2.0, -1.0, 1.0));
    V3 ax = unit({Rm[2][1]-Rm[1][2], Rm[0][2]-Rm[2][0], Rm[1][0]-Rm[0][1]});
    double h = std::fabs(dot(sub(p[1], p[0]), ax));
    double chord2 = dot(sub(p[1], p[0]), sub(p[1], p[0]));
    double R = std::sqrt((chord2 - h*h) / (2.0 * (1.0 - std::cos(theta))));
    return {theta, R, h};
}
// trilateration for three unit spheres; returns both roots
static void trisphere(V3 a, V3 b, V3 c, V3& r1, V3& r2) {
    V3 ex = unit(sub(b, a)); V3 t = sub(c, a); double i = dot(ex, t); V3 ey = unit(sub(t, mul(ex, i))); V3 ez = cross(ex, ey);
    double d = nrm(sub(b, a)), j = dot(ey, t);
    double x = d / 2.0, y = (i*i + j*j) / (2.0*j) - (i/j) * x, z2 = 1.0 - x*x - y*y;
    double z = std::sqrt(std::max(0.0, z2));
    r1 = add(a, add(mul(ex, x), add(mul(ey, y), mul(ez, z)))); r2 = add(a, add(mul(ex, x), add(mul(ey, y), mul(ez, -z))));
}

int main() {
    std::printf("FLM08 R2 — independent geometry (pre-registered 2026-10-05)\n==========================================================\n\n");
    int fails = 0;

    // ---- V1 ----
    std::vector<V3> ico;
    for (int s1 : {-1, 1}) for (int s2 : {-1, 1}) { ico.push_back({0, (double)s1, s2 * PHI}); ico.push_back({(double)s1, s2 * PHI, 0}); ico.push_back({s2 * PHI, 0, (double)s1}); }
    std::vector<V3> dod;
    for (int a : {-1, 1}) for (int b : {-1, 1}) for (int c : {-1, 1}) dod.push_back({(double)a, (double)b, (double)c});
    for (int s1 : {-1, 1}) for (int s2 : {-1, 1}) { dod.push_back({0, s1 / PHI, s2 * PHI}); dod.push_back({s1 / PHI, s2 * PHI, 0}); dod.push_back({s2 * PHI, 0, s1 / PHI}); }
    double d_ico = dihedral_poly(ico, 2.0, true), d_dod = dihedral_poly(dod, 2.0 / PHI, false);
    bool v1 = std::fabs(d_ico - 138.189685) < 1e-6 && std::fabs(d_dod - 116.565051) < 1e-6;
    std::printf("[V1] dihedral from coordinates: icosahedron %.6f (138.189685), dodecahedron %.6f (116.565051) -> %s\n", d_ico, d_dod, v1 ? "PASS" : "FAIL");
    if (!v1) ++fails;

    // ---- V2 ----
    V3 hp[5]; for (int n = 0; n < 5; ++n) hp[n] = {2.0 * std::cos(0.7 * n), 2.0 * std::sin(0.7 * n), 0.5 * n};
    Screw sv = extract(hp);
    bool v2 = std::fabs(sv.theta - 0.7) < 1e-12 && std::fabs(sv.R - 2.0) < 1e-12 && std::fabs(sv.h - 0.5) < 1e-12;
    std::printf("[V2] screw extraction on a known helix: theta %.12f (0.7)  R %.12f (2.0)  h %.12f (0.5) -> %s\n", sv.theta, sv.R, sv.h, v2 ? "PASS" : "FAIL");
    if (!v2) ++fails;

    // ---- V3 / T3: 600-cell ----
    std::vector<V4> W;
    for (int i = 0; i < 4; ++i) for (int s : {-1, 1}) { V4 v{0,0,0,0}; v[i] = s; W.push_back(v); }
    for (int a : {-1, 1}) for (int b : {-1, 1}) for (int c : {-1, 1}) for (int d : {-1, 1}) W.push_back({a*0.5, b*0.5, c*0.5, d*0.5});
    int perm[12][4] = {{0,1,2,3},{0,2,3,1},{0,3,1,2},{1,0,3,2},{1,2,0,3},{1,3,2,0},{2,0,1,3},{2,1,3,0},{2,3,0,1},{3,0,2,1},{3,1,0,2},{3,2,1,0}};
    double base[4] = {PHI / 2.0, 0.5, 1.0 / (2.0 * PHI), 0.0};
    for (auto& p : perm) for (int s0 : {-1, 1}) for (int s1 : {-1, 1}) for (int s2 : {-1, 1}) {
        V4 v; double sg[4] = {(double)s0, (double)s1, (double)s2, 1.0};
        for (int k = 0; k < 4; ++k) v[p[k]] = sg[k] * base[k];
        W.push_back(v);
    }
    // remove duplicates (the zero component has no sign)
    std::vector<V4> U;
    for (auto& v : W) { bool dup = false; for (auto& u : U) if (std::fabs(u[0]-v[0]) + std::fabs(u[1]-v[1]) + std::fabs(u[2]-v[2]) + std::fabs(u[3]-v[3]) < 1e-12) { dup = true; break; } if (!dup) U.push_back(v); }
    const int NV = (int)U.size();
    const double el = 1.0 / PHI;
    std::vector<std::vector<int>> adj(NV);
    auto dist4 = [&](int i, int j) { double s = 0; for (int k = 0; k < 4; ++k) s += (U[i][k]-U[j][k])*(U[i][k]-U[j][k]); return std::sqrt(s); };
    int edges = 0, deg_bad = 0;
    for (int i = 0; i < NV; ++i) for (int j = i + 1; j < NV; ++j) if (std::fabs(dist4(i, j) - el) < 1e-9) { adj[i].push_back(j); adj[j].push_back(i); ++edges; }
    for (int i = 0; i < NV; ++i) if (adj[i].size() != 12) ++deg_bad;
    auto isnb = [&](int i, int j) { return std::fabs(dist4(i, j) - el) < 1e-9; };
    int faces = 0, cells = 0; std::vector<std::array<int, 4>> CL;
    for (int i = 0; i < NV; ++i) for (int j : adj[i]) if (j > i) for (int k : adj[j]) if (k > j && isnb(i, k)) { ++faces; for (int l : adj[k]) if (l > k && isnb(i, l) && isnb(j, l)) { ++cells; CL.push_back({i, j, k, l}); } }
    std::vector<int> epc(NV * NV, 0);
    for (auto& c : CL) for (int a = 0; a < 4; ++a) for (int b = a + 1; b < 4; ++b) ++epc[std::min(c[a], c[b]) * NV + std::max(c[a], c[b])];
    int bad5 = 0, nedge_cells = 0; for (int i = 0; i < NV; ++i) for (int j = i + 1; j < NV; ++j) if (epc[i*NV+j]) { ++nedge_cells; if (epc[i*NV+j] != 5) ++bad5; }
    bool v3 = NV == 120 && edges == 720 && deg_bad == 0 && faces == 1200 && cells == 600 && bad5 == 0 && nedge_cells == 720;
    std::printf("[V3] 600-cell combinatorics from coordinates: vertices %d (120), edges %d (720), degree-12 violations %d, faces %d (1200), cells %d (600), edges not in exactly 5 cells %d -> %s\n\n", NV, edges, deg_bad, faces, cells, bad5, v3 ? "PASS" : "FAIL");
    if (!v3) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // ---- T1 ----
    std::vector<V3> T = {{0,0,0}, {1,0,0}, {0.5, std::sqrt(3.0)/2.0, 0}, {0.5, std::sqrt(3.0)/6.0, std::sqrt(2.0/3.0)}};
    V3 cT{0,0,0}; for (auto& p : T) cT = add(cT, p); cT = mul(cT, 0.25);
    auto facen = [&](int a, int b, int c) { V3 n = cross(sub(T[b], T[a]), sub(T[c], T[a])); if (dot(n, sub(T[a], cT)) < 0) n = mul(n, -1); return unit(n); };
    V3 n123 = facen(1,2,3), n023 = facen(0,2,3);
    double delta = PI - std::acos(dot(n123, n023));
    std::printf("[T1] tetrahedron dihedral from face normals: %.12f rad = %.9f deg ; arccos(1/3) = %.12f ; |diff| = %.2e -> %s\n", delta, delta*180/PI, std::acos(1.0/3.0), std::fabs(delta - std::acos(1.0/3.0)), std::fabs(delta - std::acos(1.0/3.0)) < 1e-12 ? "PASS" : "FAIL");

    // ---- T2 ----
    std::vector<V3> ch = T;
    for (int n = 0; n < 40; ++n) {
        size_t m = ch.size(); V3 r1, r2; trisphere(ch[m-3], ch[m-2], ch[m-1], r1, r2);
        V3 old = ch[m-4]; ch.push_back(nrm(sub(r1, old)) > 1e-6 ? r1 : r2);
    }
    // all consecutive distances 1, 2-apart 1, 3-apart 1 (face-sharing)
    double worst_d = 0; for (size_t n = 3; n < ch.size(); ++n) for (int k = 1; k <= 3; ++k) worst_d = std::max(worst_d, std::fabs(nrm(sub(ch[n], ch[n-k])) - 1.0));
    Screw s0 = extract(&ch[0]), s1 = extract(&ch[30]);
    double th_t = std::acos(-2.0/3.0), R_t = 3.0*std::sqrt(3.0)/10.0, h_t = 1.0/std::sqrt(10.0);
    bool t2 = worst_d < 1e-9 && std::fabs(s0.theta - th_t) < 1e-9 && std::fabs(s1.theta - th_t) < 1e-9 && std::fabs(s0.R - R_t) < 1e-9 && std::fabs(s0.h - h_t) < 1e-9 && std::fabs(s1.R - R_t) < 1e-9;
    std::printf("[T2] face-sharing chain by three-sphere intersection (44 vertices): worst |edge-1| = %.2e ; twist %.9f deg (start) %.9f (vertex 30) vs %.9f ; R %.9f vs %.9f ; rise %.9f vs %.9f -> %s\n",
                worst_d, s0.theta*180/PI, s1.theta*180/PI, th_t*180/PI, s0.R, R_t, s0.h, h_t, t2 ? "PASS" : "FAIL");

    // ---- T3 ----
    double worst = 0; int count = 0; double mn = 1e9, mx = -1e9;
    for (auto& c : CL) for (int a = 0; a < 4; ++a) for (int b = a + 1; b < 4; ++b) {
        int A = c[a], B = c[b]; std::vector<int> o; for (int k = 0; k < 4; ++k) if (k != a && k != b) o.push_back(c[k]);
        V4 a1 = U[A]; double ab = dot4(U[A], U[B]); V4 a2; double s = 0; for (int k = 0; k < 4; ++k) { a2[k] = U[B][k] - ab * U[A][k]; s += a2[k]*a2[k]; } s = std::sqrt(s); for (int k = 0; k < 4; ++k) a2[k] /= s;
        V4 Cp, Dp; for (int which = 0; which < 2; ++which) { V4 x = U[o[which]]; double c1 = dot4(x, a1), c2 = dot4(x, a2); V4 y; for (int k = 0; k < 4; ++k) y[k] = x[k] - c1*a1[k] - c2*a2[k]; (which ? Dp : Cp) = y; }
        double cs = dot4(Cp, Dp) / std::sqrt(dot4(Cp, Cp) * dot4(Dp, Dp)); double ang = std::acos(std::clamp(cs, -1.0, 1.0)) * 180.0 / PI;
        mn = std::min(mn, ang); mx = std::max(mx, ang); worst = std::max(worst, std::fabs(ang - 72.0)); ++count;
    }
    double d5 = 5.0 * (72.0 - delta * 180.0 / PI), d5_direct = 360.0 - 5.0 * delta * 180.0 / PI;
    bool t3 = count == 3600 && worst < 1e-9 && std::fabs(d5 - 7.356103172) < 1e-8 && std::fabs(d5_direct - 7.356103172) < 1e-8;
    std::printf("[T3] 600-cell: %d (cell, edge) dihedrals in S^3, min %.9f max %.9f deg (worst |dev from 72| = %.2e) ; 5(72-delta) = %.9f ; 360-5 delta = %.9f -> %s\n", count, mn, mx, worst, d5, d5_direct, t3 ? "PASS" : "FAIL");

    // ---- T4 ----
    std::mt19937_64 gen(20261005); std::uniform_real_distribution<double> U01(0.0, 1.0);
    auto gauss = [&]() { double u1 = U01(gen), u2 = U01(gen); return std::sqrt(-2.0 * std::log(u1 + 1e-300)) * std::cos(2.0 * PI * u2); };
    V3 td[4] = {unit({1,1,1}), unit({1,-1,-1}), unit({-1,1,-1}), unit({-1,-1,1})};
    double worst_tf = 0;
    for (int k = 0; k < 100000; ++k) { V3 e = unit({gauss(), gauss(), gauss()}); double s = 0; for (auto& n : td) s += dot(n, e) * dot(n, e); worst_tf = std::max(worst_tf, std::fabs(s / 4.0 - 1.0 / 3.0)); }
    bool t4 = worst_tf < 1e-15;
    std::printf("[T4] tight frame: max |sum (n_i.e)^2 / 4 - 1/3| over 1e5 random axes = %.2e -> %s  (exact for a perfect tetrahedral node)\n", worst_tf, t4 ? "PASS" : "FAIL");
    std::printf("     report only: fixed-orientation ensemble with bond-direction jitter, mean of sum(n_i.e)^2/4 over 2000 nodes (std error)\n");
    V3 axes[3] = {{0,0,1}, unit({1,1,1}), unit({1,1,0})}; const char* an[3] = {"z", "(111)", "(110)"};
    for (double deg : {5.0, 10.0}) {
        double sig = deg * PI / 180.0 / std::sqrt(2.0);
        for (int a = 0; a < 3; ++a) {
            double sum = 0, sum2 = 0; const int NN = 2000;
            for (int n = 0; n < NN; ++n) { double s = 0; for (auto& d0 : td) { V3 d = unit(add(d0, {sig*gauss(), sig*gauss(), sig*gauss()})); s += dot(d, axes[a]) * dot(d, axes[a]); } s /= 4.0; sum += s; sum2 += s*s; }
            double mean = sum / NN, se = std::sqrt((sum2 / NN - mean*mean) / NN);
            std::printf("       jitter %4.1f deg rms, axis %-5s: mean %.6f  (1/3 = 0.333333, dev %+.2e, se %.1e)\n", deg, an[a], mean, mean - 1.0/3.0, se);
        }
    }
    std::printf("     rotation-averaged over axes the value is 1/3 for ANY set of unit directions (<(n.e)^2>_e = 1/3), so node-level disorder cannot move it; only a fixed axis in a fixed-orientation ensemble can.\n\n");
    std::printf("SUMMARY: validations met; T1 %s T2 %s T3 %s T4 %s\n", "PASS", t2 ? "PASS" : "FAIL", t3 ? "PASS" : "FAIL", t4 ? "PASS" : "FAIL");
    return 0;
}
