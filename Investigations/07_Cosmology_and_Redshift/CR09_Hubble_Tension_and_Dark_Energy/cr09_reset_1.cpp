// CR09 blank-slate run 1 (2026-10-08): Route B, the section-3 distance law against the raw Pantheon+ apparent magnitudes.
// Pre-registered in CR09_RESET_ASSESSMENT_2026-10-08.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>
using namespace sdt::laws;

struct SN { double z, mB, err, x1, c, vpe = 0; };
struct Fit { double M, a, b, chi2, n; int N; };

static double shapeTerm(double z, double n) { return 5.0 * std::log10((1 + z) * std::pow(std::log(1 + z), 1.0 / n)); }
// weighted linear least squares for y = M + a x1 + b c given fixed shape term
static Fit lsq(const std::vector<SN>& s, double n, double sint, bool lowz) {
    double A[3][3] = {{0}}, B[3] = {0}; int N = 0;
    for (auto& p : s) { double sg2 = p.err * p.err + sint * sint, w = 1 / sg2, y = p.mB - (lowz ? 5.0 * std::log10(p.z * (1 + p.z / 2)) : shapeTerm(p.z, n)), f[3] = {1, p.x1, p.c};
        for (int i = 0; i < 3; ++i) { B[i] += w * f[i] * y; for (int j = 0; j < 3; ++j) A[i][j] += w * f[i] * f[j]; } ++N; }
    // solve 3x3 by Gaussian elimination
    double M3[3][4]; for (int i = 0; i < 3; ++i) { for (int j = 0; j < 3; ++j) M3[i][j] = A[i][j]; M3[i][3] = B[i]; }
    for (int i = 0; i < 3; ++i) { int p = i; for (int r = i + 1; r < 3; ++r) if (std::fabs(M3[r][i]) > std::fabs(M3[p][i])) p = r; for (int j = 0; j < 4; ++j) std::swap(M3[i][j], M3[p][j]); for (int r = i + 1; r < 3; ++r) { double fct = M3[r][i] / M3[i][i]; for (int j = i; j < 4; ++j) M3[r][j] -= fct * M3[i][j]; } }
    double x[3]; for (int i = 2; i >= 0; --i) { double sum = M3[i][3]; for (int j = i + 1; j < 3; ++j) sum -= M3[i][j] * x[j]; x[i] = sum / M3[i][i]; }
    double chi2 = 0; for (auto& p : s) { double y = p.mB - (lowz ? 5.0 * std::log10(p.z * (1 + p.z / 2)) : shapeTerm(p.z, n)), r = y - (x[0] + x[1] * p.x1 + x[2] * p.c); chi2 += r * r / (p.err * p.err + sint * sint); }
    return {x[0], x[1], x[2], chi2, n, N};
}

int main(int argc, char** argv) {
    const bool useVpec = argc > 1 && std::string(argv[1]) == "vpec";   // run 2 (Amendment 1, made after run 1 was seen): add the peculiar-velocity variance
    std::printf("CR09 blank-slate run 1, Route B (pre-registered 2026-10-08)\n===========================================================\n\n");
    int fails = 0;
    // ---- V1 exact recovery
    { std::vector<SN> s; std::mt19937 g(1); for (int i = 0; i < 300; ++i) { SN p; p.z = 0.02 + 1.9 * (double(g()) / 4294967296.0); p.x1 = -2 + 4 * (double(g()) / 4294967296.0); p.c = -0.3 + 0.6 * (double(g()) / 4294967296.0); p.err = 0.1;
        p.mB = -19.3 + 43.0 + shapeTerm(p.z, 0.8) + 0.14 * p.x1 + 3.1 * p.c; s.push_back(p); }
      Fit f = lsq(s, 0.8, 0.0, false); bool v = std::fabs(f.M - 23.7) < 1e-9 && std::fabs(f.a - 0.14) < 1e-9 && std::fabs(f.b - 3.1) < 1e-9; std::printf("[V1] exact recovery of (M, a, b) = (23.7, 0.14, 3.1): (%.10f, %.10f, %.10f) -> %s\n", f.M, f.a, f.b, v ? "met" : "NOT MET"); if (!v) ++fails; }
    // ---- V2 shape recovery
    { std::vector<SN> s; std::mt19937 g(7); std::normal_distribution<double> nd(0.0, 1.0); auto U = [&]() { return double(g()) / 4294967296.0; };
      for (int i = 0; i < 500; ++i) { SN p; p.z = 0.01 + 1.99 * U(); p.x1 = -2 + 4 * U(); p.c = -0.3 + 0.6 * U(); p.err = 0.10; p.mB = 24.0 + shapeTerm(p.z, 0.66) + 0.14 * p.x1 + 3.1 * p.c + 0.10 * nd(g); s.push_back(p); }
      double best = 1e99, bn = 0; for (int k = 0; k <= 280; ++k) { double n = 0.2 + 0.01 * k; Fit f = lsq(s, n, 0.0, false); if (f.chi2 < best) { best = f.chi2; bn = n; } }
      bool v = std::fabs(bn - 0.66) <= 0.05; std::printf("[V2] shape recovery from synthetic n = 0.66, noise 0.10 mag, 500 points: n = %.2f -> %s\n", bn, v ? "met" : "NOT MET"); if (!v) ++fails; }
    // ---- V3 parser
    std::vector<SN> all, hf; int rows = 0;
    { std::ifstream f("Datasets/cosmology/PantheonPlusSH0ES.dat"); if (!f) { std::printf("cannot open the data file (run from the repo root)\n"); return 2; }
      std::string line; std::getline(f, line); std::istringstream hs(line); std::map<std::string, int> col; std::string tok; int k = 0; while (hs >> tok) col[tok] = k++;
      while (std::getline(f, line)) { std::istringstream ls(line); std::vector<std::string> v; std::string t; while (ls >> t) v.push_back(t); if ((int)v.size() < k) continue; ++rows;
        SN p; p.z = std::stod(v[col["zHD"]]); p.mB = std::stod(v[col["mB"]]); p.err = std::stod(v[col["mBERR"]]); p.x1 = std::stod(v[col["x1"]]); p.c = std::stod(v[col["c"]]); p.vpe = std::stod(v[col["VPECERR"]]); int cal = std::stoi(v[col["IS_CALIBRATOR"]]);
        all.push_back(p); if (cal == 0 && p.z > 0.01) hf.push_back(p); } }
    bool v3 = rows == 1701; std::printf("[V3] rows read: %d (expected 1701) ; Hubble-flow selection (IS_CALIBRATOR = 0, zHD > 0.01): %zu -> %s\n\n", rows, hf.size(), v3 ? "met" : "NOT MET"); if (!v3) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0"); if (fails) return 1;

    if (useVpec) { const double cK = sdt::laws::measured::c / 1000.0; for (auto& p : hf) p.err = std::sqrt(p.err * p.err + std::pow(2.171472 * p.vpe / (cK * p.z), 2)); std::printf("[Amendment 1] peculiar-velocity variance added: err^2 = mBERR^2 + (5/ln10 x VPECERR/(c zHD))^2\n\n"); }
    // ---- sigma_int by the registered local rule
    std::vector<SN> lo; for (auto& p : hf) if (p.z < 0.08) lo.push_back(p);
    Fit fl = lsq(lo, 0, 0.0, true); double sw = 0, sr = 0, se = 0; for (auto& p : lo) { double y = p.mB - 5.0 * std::log10(p.z * (1 + p.z / 2)), r = y - (fl.M + fl.a * p.x1 + fl.b * p.c), w = 1 / (p.err * p.err); sw += w; sr += w * r * r; se += w * p.err * p.err; }
    double rms2 = sr / sw, merr2 = se / sw, sint = std::sqrt(std::max(0.0, rms2 - merr2));
    std::printf("[rule] local subset 0.01 < z < 0.08: N = %zu, weighted rms = %.4f mag, <mBERR^2>^(1/2) = %.4f mag -> sigma_int = %.4f mag (fit: M = %.4f, a = %.4f, b = %.4f)\n\n", lo.size(), std::sqrt(rms2), std::sqrt(merr2), sint, fl.M, fl.a, fl.b);

    // ---- T1 scan
    int N = (int)hf.size(); double best = 1e99, bn = 0; Fit bf{};
    for (int k = 0; k <= 280; ++k) { double n = 0.2 + 0.01 * k; Fit f = lsq(hf, n, sint, false); if (f.chi2 < best) { best = f.chi2; bn = n; bf = f; } }
    int dof = N - 4;
    std::printf("[T1] Hubble-flow sample N = %d, dof = N - 4 = %d (n, M, a, b fitted)\n     best n = %.2f : chi2 = %.2f, chi2/dof = %.4f ; M = %.4f, a = %.4f, b = %.4f\n     shape scan chi2/dof: ", N, dof, bn, bf.chi2, bf.chi2 / dof, bf.M, bf.a, bf.b);
    for (double n : {0.5, 0.66, 1.0, 2.0, 4.0}) { Fit f = lsq(hf, n, sint, false); std::printf("n = %.2f: %.4f ; ", n, f.chi2 / (N - 3)); }
    std::printf("\n     (for the fixed-n entries dof = N - 3)\n\n");
    // ---- T2 binned residuals
    std::vector<SN> srt = hf; std::sort(srt.begin(), srt.end(), [](const SN& a, const SN& b) { return a.z < b.z; });
    std::printf("[T2] binned residuals at the best n (equal counts, 8 bins): z range, N, mean residual [mag], standard error, mean/se\n"); int off = 0;
    for (int b = 0; b < 8; ++b) { int i0 = b * N / 8, i1 = (b + 1) * N / 8; double sw2 = 0, swr = 0; for (int i = i0; i < i1; ++i) { auto& p = srt[i]; double r = p.mB - shapeTerm(p.z, bn) - (bf.M + bf.a * p.x1 + bf.b * p.c), w = 1 / (p.err * p.err + sint * sint); sw2 += w; swr += w * r; }
        double m = swr / sw2, se = 1 / std::sqrt(sw2); if (std::fabs(m / se) > 3) ++off; std::printf("     z %.4f - %.4f : N = %3d  mean = %+.4f  se = %.4f  (%+.2f se)\n", srt[i0].z, srt[i1 - 1].z, i1 - i0, m, se, m / se); }
    double chi = bf.chi2 / dof; const char* verdict = (chi > 2) ? "EXCLUDED at this parameter count (chi2/dof > 2 at the best n; check every n: see scan)" : ((chi <= 1.2 && off == 0) ? "TRACKS the raw magnitudes" : "STRUCTURED RESIDUAL");
    std::printf("\n     bins off by more than 3 se: %d ; registered reading: %s\n", off, verdict);
    return 0;
}
