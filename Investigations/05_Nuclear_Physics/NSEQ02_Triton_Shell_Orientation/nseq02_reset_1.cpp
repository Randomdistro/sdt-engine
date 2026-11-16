// NSEQ02 blank-slate run 1 (2026-10-10). Registration: NSEQ02_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
// Geometry only (VERIFICATION): author dual-tetrahedron layout A, flat hex-bipyramid B, planar antipodal octagon C; radius rule 1.05 / 0.95.
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <vector>
using V3 = std::array<double, 3>;
static const double PI = 3.14159265358979323846;
static V3 sph(double latDeg, double azDeg) { double la = latDeg * PI / 180, az = azDeg * PI / 180; return {std::cos(la) * std::cos(az), std::cos(la) * std::sin(az), std::sin(la)}; }
static double dot(const V3& a, const V3& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
static double ang(const V3& a, const V3& b) { double c = std::max(-1.0, std::min(1.0, dot(a, b))); return std::acos(c) * 180 / PI; }
// eigenvalues of a symmetric 3x3 (Jacobi)
static std::array<double, 3> eig(double a[3][3]) { double v[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; for (int it = 0; it < 60; ++it) { int p = 0, q = 1; double mx = std::fabs(a[0][1]); if (std::fabs(a[0][2]) > mx) { p = 0; q = 2; mx = std::fabs(a[0][2]); } if (std::fabs(a[1][2]) > mx) { p = 1; q = 2; mx = std::fabs(a[1][2]); } if (mx < 1e-15) break;
        double th = 0.5 * std::atan2(2 * a[p][q], a[q][q] - a[p][p]), c = std::cos(th), s = std::sin(th); for (int k = 0; k < 3; ++k) { double akp = a[k][p], akq = a[k][q]; a[k][p] = c * akp - s * akq; a[k][q] = s * akp + c * akq; } for (int k = 0; k < 3; ++k) { double apk = a[p][k], aqk = a[q][k]; a[p][k] = c * apk - s * aqk; a[q][k] = s * apk + c * aqk; } } std::array<double, 3> e = {a[0][0], a[1][1], a[2][2]}; std::sort(e.begin(), e.end()); return e; }
static void report(const char* nm, const std::vector<V3>& u) {
    int n = (int)u.size(); std::vector<double> an; for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) an.push_back(ang(u[i], u[j])); std::sort(an.begin(), an.end());
    std::printf("%s: %d vectors, %zu pairs, min angle %.4f deg, max %.4f deg\n  histogram:", nm, n, an.size(), an.front(), an.back()); size_t i = 0; while (i < an.size()) { size_t j = i; while (j < an.size() && std::fabs(an[j] - an[i]) < 1e-6) ++j; std::printf(" %.4f x%zu;", an[i], j - i); i = j; } std::printf("\n");
    double T[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}; for (auto& v : u) for (int a = 0; a < 3; ++a) for (int b = 0; b < 3; ++b) T[a][b] += v[a] * v[b]; auto e = eig(T); std::printf("  second-moment eigenvalues: %.6f, %.6f, %.6f\n", e[0], e[1], e[2]);
}
int main() {
    std::printf("NSEQ02 blank-slate run 1 (registered in NSEQ02_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n====================================================================\n\n");
    const double lat = std::asin(1.0 / 3.0) * 180 / PI;
    std::vector<V3> open, close; open.push_back(sph(90, 0)); for (int k = 0; k < 3; ++k) open.push_back(sph(-lat, 120.0 * k)); close.push_back(sph(-90, 0)); for (int k = 0; k < 3; ++k) close.push_back(sph(lat, 60.0 + 120.0 * k));
    std::vector<V3> A = open; A.insert(A.end(), close.begin(), close.end());
    int fails = 0; { double w = 0; for (auto& v : A) w = std::max(w, std::fabs(std::sqrt(dot(v, v)) - 1)); bool ok = w < 1e-15; std::printf("[V1] unit norms: worst deviation %.2e -> %s\n", w, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { double th = std::acos(-1.0 / 3.0) * 180 / PI, cu = std::acos(1.0 / 3.0) * 180 / PI, e1 = 0, e2 = 0; for (int i = 0; i < 4; ++i) for (int j = i + 1; j < 4; ++j) e1 = std::max(e1, std::fabs(ang(open[i], open[j]) - th)); e2 = std::fabs(ang(A[1], A[4 + 1]) - cu); // opening vertex az 0 vs closing vertex az 60 (adjacent cube vertices)
      bool ok = e1 < 1e-9 && th - 109.471221 < 1e-6; std::printf("[V2] tetrahedron angle %.6f (analytic 109.471221), max deviation in the opening tetrahedron %.2e ; cube-edge angle %.6f (analytic 70.528779)\n", th, e1, cu); (void)e2; if (!ok) ++fails; }
    report("(A) author dual tetrahedra", A);
    { auto ed = [&](const std::vector<V3>& t) { std::vector<double> d; for (int i = 0; i < 4; ++i) for (int j = i + 1; j < 4; ++j) d.push_back(ang(t[i], t[j])); return std::make_pair(*std::min_element(d.begin(), d.end()), *std::max_element(d.begin(), d.end())); }; auto o = ed(open), c = ed(close);
      std::printf("  opening tetrahedron edge angles %.6f .. %.6f ; closing %.6f .. %.6f ; partition sizes %zu + %zu ; latitudes of the band vertices %.4f (opening), %.4f (closing)\n", o.first, o.second, c.first, c.second, open.size(), close.size(), -lat, lat); }
    { double T[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}; for (auto& v : A) for (int a = 0; a < 3; ++a) for (int b = 0; b < 3; ++b) T[a][b] += v[a] * v[b]; auto e = eig(T); bool iso = std::fabs(e[0] - 8.0 / 3) < 1e-12 && std::fabs(e[2] - 8.0 / 3) < 1e-12; std::vector<double> an; for (int i = 0; i < 8; ++i) for (int j = i + 1; j < 8; ++j) an.push_back(ang(A[i], A[j])); int n70 = 0, n109 = 0, n180 = 0; for (double a : an) { if (std::fabs(a - 70.528779) < 1e-5) ++n70; else if (std::fabs(a - 109.471221) < 1e-5) ++n109; else if (std::fabs(a - 180) < 1e-5) ++n180; }
      bool ok = iso && n70 == 12 && n109 == 12 && n180 == 4; std::printf("[V3] cube-vertex test: histogram 12/12/4 (%d/%d/%d), isotropic tensor 8/3 x3 (%s) -> %s\n\n", n70, n109, n180, iso ? "yes" : "no", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    std::vector<V3> B = {sph(90, 0), sph(-90, 0)}; for (int k = 0; k < 6; ++k) B.push_back(sph(0, 60.0 * k)); report("(B) flat hex-bipyramid (rejected misread)", B);
    { std::vector<V3> t = {B[0], B[2], B[4], B[6]}; std::vector<double> d; for (int i = 0; i < 4; ++i) for (int j = i + 1; j < 4; ++j) d.push_back(ang(t[i], t[j])); std::sort(d.begin(), d.end()); std::printf("  tetrahedron from pole + equator az 0,120,240: edge angles %.4f .. %.4f -> %s\n\n", d.front(), d.back(), d.back() - d.front() < 1e-6 ? "regular" : "NOT regular"); }
    std::vector<V3> Cc; for (int k = 0; k < 8; ++k) Cc.push_back(sph(0, 45.0 * k)); report("(C) planar: four antipodal pairs in z = 0 (regular octagon, example spacing)", Cc);
    std::printf("\nRadius rule (opening 1.05, closing 0.95; relative units):\n"); const double r1 = 1.05, r2 = 0.95;
    std::printf("  mean radius opening %.4f > closing %.4f: %s (C3: restates the inputs)\n", r1, r2, r1 > r2 ? "yes" : "no");
    std::printf("  opening-opening distance %.4f ; closing-closing %.4f (edge = r sqrt(8/3))\n", r1 * std::sqrt(8.0 / 3), r2 * std::sqrt(8.0 / 3));
    { double dmin = 1e9, dmax = 0; for (auto& a : open) for (auto& b : close) { double d2 = r1 * r1 + r2 * r2 - 2 * r1 * r2 * dot(a, b); double d = std::sqrt(d2); dmin = std::min(dmin, d); dmax = std::max(dmax, d); } std::printf("  nearest opening-closing %.4f (at 70.5288 deg) ; farthest %.4f (antipodal, r1 + r2)\n", dmin, dmax); }
    std::printf("\nCapacity identity: stella octangula vertex count 8 = B(3) = 2(3+1) = %d (a count)\nNumeric gate on a measured nuclear quantity (audit correction): OWED, orientation alone enters no capacity, binding or radius (D3)\n", 2 * (3 + 1));
    return 0;
}
