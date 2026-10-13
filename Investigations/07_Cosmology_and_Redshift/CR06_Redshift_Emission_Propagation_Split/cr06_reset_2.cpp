// CR06 reframe run 2 (2026-10-09). REGISTRATION (written before this tool was run). No gates: nothing here classifies, thresholds or ranks a result.
// Exposure (not blind): run 1 (cr06_reset_1.cpp) had fitted the same 40 bins; its numbers (single power n = 0.6555, chi2 81.027; LCDM Om = 0.2841, chi2 49.738, diagonal errors) are used below only as known answers for validation V6.
//
// Frame (PROMPT.md, "Reframe 2026-10-09"): redshift is an endpoint ratio of lattice states; photon energy and event rate scale with the same ruler ratio, so D_L = r (1+z)^p with p = 1 derived from that premise; r is a physical distance (Law III inverse square);
//  the unknown is the profile 1+z(r), represented with no assumed shape by the octave-rate function n(x), x = ln(1+z):  r~(x) = int_0^x exp((1 - n(x')) x') dx'  (n piecewise-linear on K equally spaced knots over the data range; K = 1 is the single power).
//  m = 5 log10[(1+z)^p r~] + a (+ delta x when the emission-luminosity drift is fitted); a = M - 5 log10 H_eff + const and delta are linear nuisance parameters solved analytically against the covariance.
// Fits (all by weighted least squares with the stated covariance, one pass over the whole range per dataset): K = 1..5 with p = 1 fixed; K = 1..3 with p free; K = 1..3 with the drift delta free; fixed n = 1 and n = 4 (the documented single-power forms, reported as fits, not as candidates under test);
//  comparators: Milne, EdS, de Sitter z(1+z), flat LCDM(Om) (shape parameter Om), each with the offset; the LCDM local exponent n_eff = 1.5 Om (1+z)^3/[Om (1+z)^3 + 1 - Om].
// Reported: chi2 and parameter count for every fit; knot values and n_eff(z) with 1-sigma bands from the profile Hessian (cov = 2 H^-1); p-hat and delta-hat with sigma; per-bin residual m - model - a in magnitudes for the 40-bin file (the amount the emission term would have to supply under each profile).
// Datasets: (A) data/pantheon_binned_DS17f.txt with C = diag(dmb^2) + C_sys (Datasets/cosmology/Pantheon_DS17f_binned_sys_covariance.txt); (B) the same file with diagonal errors only (reported beside A to show what the covariance changes);
//  (C) Datasets/cosmology/PantheonPlusSH0ES.dat, rows with IS_CALIBRATOR = 0 and zHD >= 0.01, columns zHD, m_b_corr, m_b_corr_err_DIAG, diagonal errors only (covariance not in the repository: PENDING).
// Look-elsewhere: K = 1..5 are all reported, none selected; 3 datasets; p and delta variants reported alongside.
// Validations (instrument, known answers; tolerances are tool checks): V1 closed form of r~ for constant n (n = 0.3, 1, 2.5, 4; rel 1e-9); V2 K = 3 with equal knot values has the chi2 of K = 1 (1e-9); V3 (toy) noiseless K = 3 truth (0.4, 0.9, 1.4) recovered (1e-4) with chi2 < 1e-9;
//  V4 (toy) 300 noisy realisations of K = 1 truth n = 0.7 (errors = dmb, Box-Muller on raw mt19937): the fraction with |n-hat - 0.7| <= sigma-hat lies in [0.60, 0.76] and the mean sigma-hat is within 15% of the scatter of n-hat;
//  V5 the covariance is symmetric (1e-12) and C_sys + diag is positive definite (Cholesky); V6 (B) reproduces run 1: LCDM Om = 0.2841 (0.0005), chi2 49.738 (0.005); K = 1 n = 0.6555 (0.0005), chi2 81.027 (0.005); V7 the parse counts: A, B 40 rows; C count printed.
// [CORRECTION 2026-10-09, after attempt 1 was seen; computation unchanged, report changed] Attempt 1 printed the profile's n(x) under the name n_eff(z) and printed the LCDM local slope under the same name. They are different quantities:
//   secant exponent   n_sec(x) = ln(dz/dr)/x            (the profile's n(x): dz/dr = (1+z)^n(x));  LCDM: n_sec = ln E / ln(1+z), E = sqrt(Om (1+z)^3 + 1 - Om)
//   local slope       s(x)     = d ln(dz/dr)/d ln(1+z) = n(x) + x n'(x);                           LCDM: s = 1.5 Om (1+z)^3 / E^2
// For a single power they coincide. Attempt 2 prints both for every profile (with bands; s is linear in the knot values: s = n + x n', n' piecewise constant, right-hand segment at a knot) and for LCDM. Attempt 1 output kept as cr06_reset_2_results_attempt1_label_fault.txt.
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>
using Vec = std::vector<double>;

struct Dat {
    std::string name; Vec z, x, m, e; int n = 0; bool cov = false; Vec L; Vec u1, ux;
    void whiten(const Vec& y, Vec& w) const { w.assign(n, 0); if (!cov) { for (int i = 0; i < n; ++i) w[i] = y[i] / e[i]; return; } for (int i = 0; i < n; ++i) { double s = y[i]; for (int j = 0; j < i; ++j) s -= L[i * n + j] * w[j]; w[i] = s / L[i * n + i]; } }
    void prep() { n = (int)z.size(); x.resize(n); for (int i = 0; i < n; ++i) x[i] = std::log1p(z[i]); Vec ones(n, 1.0); whiten(ones, u1); whiten(x, ux); }
};
static bool chol(const Vec& A, int n, Vec& L) { L.assign(n * n, 0); for (int i = 0; i < n; ++i) for (int j = 0; j <= i; ++j) { double s = A[i * n + j]; for (int k = 0; k < j; ++k) s -= L[i * n + k] * L[j * n + k]; if (i == j) { if (s <= 0) return false; L[i * n + i] = std::sqrt(s); } else L[i * n + j] = s / L[j * n + j]; } return true; }
struct Res { double chi2; double a, delta; };
static Res chi2_of(const Dat& d, const Vec& mu, int ncol) {
    Vec y(d.n), w; for (int i = 0; i < d.n; ++i) y[i] = d.m[i] - mu[i]; d.whiten(y, w);
    double w2 = 0, s11 = 0, s12 = 0, s22 = 0, b1 = 0, b2 = 0; for (int i = 0; i < d.n; ++i) { w2 += w[i] * w[i]; s11 += d.u1[i] * d.u1[i]; b1 += d.u1[i] * w[i]; if (ncol == 2) { s12 += d.u1[i] * d.ux[i]; s22 += d.ux[i] * d.ux[i]; b2 += d.ux[i] * w[i]; } }
    Res r{}; if (ncol == 1) { r.a = b1 / s11; r.delta = 0; r.chi2 = w2 - b1 * b1 / s11; } else { double det = s11 * s22 - s12 * s12; r.a = (b1 * s22 - b2 * s12) / det; r.delta = (s11 * b2 - s12 * b1) / det; r.chi2 = w2 - (r.a * b1 + r.delta * b2); }
    return r; }
// ---- profile model
static double nprof(const Vec& th, int K, double x, double xmax) { if (K == 1) return th[0]; double t = x / xmax * (K - 1); int j = std::min((int)t, K - 2); double f = t - j; return th[j] * (1 - f) + th[j + 1] * f; }
static bool mu_prof(const Dat& d, const Vec& th, int K, bool fitP, double pfix, Vec& mu) {
    const int G = 3000; double xmax = d.x.back(), h = xmax / G; double p = fitP ? th[K] : pfix;
    auto f = [&](double x) { return std::exp((1 - nprof(th, K, x, xmax)) * x); };
    Vec C(G + 1, 0); for (int i = 0; i < G; ++i) { double a = i * h, b = a + h; C[i + 1] = C[i] + h / 6 * (f(a) + 4 * f(0.5 * (a + b)) + f(b)); }
    mu.resize(d.n); for (int k = 0; k < d.n; ++k) { double x = d.x[k]; int i = std::min((int)(x / h), G - 1); double a = i * h; double part = (x - a) / 6 * (f(a) + 4 * f(0.5 * (a + x)) + f(x)); double r = C[i] + part; if (!(r > 0)) return false; mu[k] = 5 * std::log10(r) + 5 * p * std::log10(1 + d.z[k]); }
    return true; }
static double obj_prof(const Dat& d, const Vec& th, int K, bool fitP, double pfix, int ncol, Res* out = nullptr) { for (double v : th) if (!(std::fabs(v) < 30)) return 1e30; Vec mu; if (!mu_prof(d, th, K, fitP, pfix, mu)) return 1e30; Res r = chi2_of(d, mu, ncol); if (out) *out = r; return r.chi2; }
static Vec nelder(const std::function<double(const Vec&)>& f, Vec x0, double step, double* fbest) {
    int n = (int)x0.size(); std::vector<Vec> S(n + 1, x0); for (int i = 0; i < n; ++i) S[i + 1][i] += step; Vec F(n + 1); for (int i = 0; i <= n; ++i) F[i] = f(S[i]);
    for (int it = 0; it < 6000; ++it) { std::vector<int> id(n + 1); for (int i = 0; i <= n; ++i) id[i] = i; std::sort(id.begin(), id.end(), [&](int a, int b) { return F[a] < F[b]; }); std::vector<Vec> S2(n + 1); Vec F2(n + 1); for (int i = 0; i <= n; ++i) { S2[i] = S[id[i]]; F2[i] = F[id[i]]; } S = S2; F = F2;
        if (std::fabs(F[n] - F[0]) < 1e-13 * (1 + std::fabs(F[0])) && it > 20) break; Vec c(n, 0); for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) c[j] += S[i][j] / n;
        auto mix = [&](double t) { Vec r(n); for (int j = 0; j < n; ++j) r[j] = c[j] + t * (S[n][j] - c[j]); return r; }; Vec xr = mix(-1); double fr = f(xr);
        if (fr < F[0]) { Vec xe = mix(-2); double fe = f(xe); if (fe < fr) { S[n] = xe; F[n] = fe; } else { S[n] = xr; F[n] = fr; } } else if (fr < F[n - 1]) { S[n] = xr; F[n] = fr; } else { Vec xc = mix(fr < F[n] ? -0.5 : 0.5); double fc = f(xc); if (fc < std::min(fr, F[n])) { S[n] = xc; F[n] = fc; } else { for (int i = 1; i <= n; ++i) { for (int j = 0; j < n; ++j) S[i][j] = S[0][j] + 0.5 * (S[i][j] - S[0][j]); F[i] = f(S[i]); } } } }
    int b = 0; for (int i = 1; i <= n; ++i) if (F[i] < F[b]) b = i; *fbest = F[b]; return S[b]; }
static Vec minimise(const std::function<double(const Vec&)>& f, int np, double* fb, const std::vector<Vec>& starts) { Vec best; double bf = 1e300; for (auto s : starts) { double fv; Vec r = nelder(f, s, 0.3, &fv); for (int k = 0; k < 3; ++k) { r = nelder(f, r, 0.1 / (k + 1), &fv); } if (fv < bf) { bf = fv; best = r; } } *fb = bf; return best; }
static bool invert(std::vector<Vec> A, std::vector<Vec>& inv) { int n = (int)A.size(); inv.assign(n, Vec(n, 0)); for (int i = 0; i < n; ++i) inv[i][i] = 1; for (int c = 0; c < n; ++c) { int p = c; for (int r = c + 1; r < n; ++r) if (std::fabs(A[r][c]) > std::fabs(A[p][c])) p = r; if (std::fabs(A[p][c]) < 1e-14) return false; std::swap(A[c], A[p]); std::swap(inv[c], inv[p]); double d = A[c][c]; for (int j = 0; j < n; ++j) { A[c][j] /= d; inv[c][j] /= d; } for (int r = 0; r < n; ++r) if (r != c) { double fct = A[r][c]; for (int j = 0; j < n; ++j) { A[r][j] -= fct * A[c][j]; inv[r][j] -= fct * inv[c][j]; } } } return true; }
// covariance of the parameters from the Hessian of the profile chi2: cov = 2 H^-1
static bool param_cov(const std::function<double(const Vec&)>& f, const Vec& th, double h, std::vector<Vec>& cov) { int n = (int)th.size(); std::vector<Vec> H(n, Vec(n)); double f0 = f(th);
    for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) { Vec a = th, b = th, c = th, e = th; if (i == j) { a[i] += h; b[i] -= h; H[i][i] = (f(a) - 2 * f0 + f(b)) / (h * h); } else { a[i] += h; a[j] += h; b[i] += h; b[j] -= h; c[i] -= h; c[j] += h; e[i] -= h; e[j] -= h; H[i][j] = H[j][i] = (f(a) - f(b) - f(c) + f(e)) / (4 * h * h); } }
    std::vector<Vec> inv; if (!invert(H, inv)) return false; cov = inv; for (auto& r : cov) for (auto& v : r) v *= 2; for (int i = 0; i < n; ++i) if (!(cov[i][i] > 0)) return false; return true; }
// ---- standard comparators
static double Dlcdm(double z, double Om) { const int N = 2000; double h = z / N, s; auto f = [&](double x) { return 1.0 / std::sqrt(Om * std::pow(1 + x, 3) + 1 - Om); }; s = f(0) + f(z); for (int i = 1; i < N; ++i) s += (i % 2 ? 4 : 2) * f(i * h); return (1 + z) * s * h / 3; }
static double Dmilne(double z) { return z * (1 + z / 2); }
static double Dlin(double z) { return z * (1 + z); }
static double Deds(double z) { return (1 + z) * 2 * (1 - 1 / std::sqrt(1 + z)); }
static Res fixedD(const Dat& d, const std::function<double(double)>& D, int ncol, Vec* mu_out = nullptr) { Vec mu(d.n); for (int i = 0; i < d.n; ++i) mu[i] = 5 * std::log10(D(d.z[i])); if (mu_out) *mu_out = mu; return chi2_of(d, mu, ncol); }
static double lcdm_fit(const Dat& d, int ncol, double* Om_lo, double* Om_hi, Res* r) { double best = 1e300, bo = 0; for (double o = 0; o <= 1.0001; o += 0.005) { double c = fixedD(d, [&](double z) { return Dlcdm(z, o); }, ncol).chi2; if (c < best) { best = c; bo = o; } }
    double a = std::max(0.0, bo - 0.005), b = std::min(1.0, bo + 0.005); const double g = (std::sqrt(5.0) - 1) / 2; auto F = [&](double o) { return fixedD(d, [&](double z) { return Dlcdm(z, o); }, ncol).chi2; }; double c = b - g * (b - a), e = a + g * (b - a), fc = F(c), fe = F(e); for (int i = 0; i < 80; ++i) { if (fc > fe) { a = c; c = e; fc = fe; e = a + g * (b - a); fe = F(e); } else { b = e; e = c; fe = fc; c = b - g * (b - a); fc = F(c); } } double o = 0.5 * (a + b); *r = fixedD(d, [&](double z) { return Dlcdm(z, o); }, ncol);
    auto prof = [&](double x) { return F(x) - r->chi2 - 1.0; }; double lo = o, hi = o; { double A = o, B = 0; if (prof(B) < 0) lo = B; else { for (int i = 0; i < 60; ++i) { double m = 0.5 * (A + B); if (prof(m) < 0) A = m; else B = m; } lo = 0.5 * (A + B); } } { double A = o, B = 1; if (prof(B) < 0) hi = B; else { for (int i = 0; i < 60; ++i) { double m = 0.5 * (A + B); if (prof(m) < 0) A = m; else B = m; } hi = 0.5 * (A + B); } } *Om_lo = lo; *Om_hi = hi; return o; }

// ---- data
static Dat load_binned(const char* path, const char* covpath, bool withcov, const char* nm) {
    Dat d; d.name = nm; std::ifstream f(path); std::string line; struct R { double z, m, e; }; std::vector<R> v; while (std::getline(f, line)) { if (line.empty() || line[0] == '#') continue; std::istringstream s(line); std::string name; double zc, zh, dz, mb, dmb; if (s >> name >> zc >> zh >> dz >> mb >> dmb) v.push_back({zc, mb, dmb}); }
    std::sort(v.begin(), v.end(), [](const R& a, const R& b) { return a.z < b.z; }); for (auto& r : v) { d.z.push_back(r.z); d.m.push_back(r.m); d.e.push_back(r.e); } int n = (int)v.size();
    if (withcov) { std::ifstream c(covpath); int nn; c >> nn; Vec C(nn * nn); for (auto& t : C) c >> t; // file order matches the original (unsorted) file order: apply the same permutation
        std::ifstream f2(path); std::vector<R> orig; std::vector<int> idx; while (std::getline(f2, line)) { if (line.empty() || line[0] == '#') continue; std::istringstream s(line); std::string name; double zc, zh, dz, mb, dmb; if (s >> name >> zc >> zh >> dz >> mb >> dmb) orig.push_back({zc, mb, dmb}); }
        idx.resize(n); for (int i = 0; i < n; ++i) idx[i] = i; std::stable_sort(idx.begin(), idx.end(), [&](int a, int b) { return orig[a].z < orig[b].z; }); Vec T(n * n); for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) T[i * n + j] = C[idx[i] * nn + idx[j]] + (i == j ? d.e[i] * d.e[i] : 0.0); if (!chol(T, n, d.L)) { std::printf("covariance not positive definite\n"); std::exit(1); } d.cov = true; }
    d.prep(); return d; }
static Dat load_plus(const char* path) {
    Dat d; d.name = "C Pantheon+ (non-calibrators, zHD>=0.01, diagonal)"; std::ifstream f(path); std::string line; std::getline(f, line); std::istringstream h(line); std::map<std::string, int> col; std::string t; int k = 0; while (h >> t) col[t] = k++;
    struct R { double z, m, e; }; std::vector<R> v; while (std::getline(f, line)) { std::istringstream s(line); std::vector<std::string> tok; while (s >> t) tok.push_back(t); if ((int)tok.size() <= col["IS_CALIBRATOR"]) continue; if (std::atoi(tok[col["IS_CALIBRATOR"]].c_str()) != 0) continue; double z = std::atof(tok[col["zHD"]].c_str()); if (z < 0.01) continue; v.push_back({z, std::atof(tok[col["m_b_corr"]].c_str()), std::atof(tok[col["m_b_corr_err_DIAG"]].c_str())}); }
    std::sort(v.begin(), v.end(), [](const R& a, const R& b) { return a.z < b.z; }); for (auto& r : v) { d.z.push_back(r.z); d.m.push_back(r.m); d.e.push_back(r.e); } d.prep(); return d; }

struct Fit { Vec th; Res res; double chi2; std::vector<Vec> cov; bool covok; int K; bool fitP; int ncol; };
static Fit fit_prof(const Dat& d, int K, bool fitP, int ncol, double pfix = 1.0) {
    auto f = [&](const Vec& th) { return obj_prof(d, th, K, fitP, pfix, ncol); }; std::vector<Vec> starts; for (double n0 : {0.3, 1.0, 2.0}) { Vec s(K + (fitP ? 1 : 0), n0); if (fitP) s[K] = 1.0; starts.push_back(s); }
    Fit F; F.K = K; F.fitP = fitP; F.ncol = ncol; double fb; F.th = minimise(f, K + (fitP ? 1 : 0), &fb, starts); obj_prof(d, F.th, K, fitP, pfix, ncol, &F.res); F.chi2 = F.res.chi2; F.covok = param_cov(f, F.th, 0.02, F.cov); return F; }
static void print_prof(const Dat& d, const Fit& F, const std::vector<double>& zl) {
    double xmax = d.x.back(); std::printf("   K=%d%s%s  chi2 = %10.3f  (nuisance %d + shape %d%s)  a = %.5f", F.K, F.fitP ? " p-free" : "", F.ncol == 2 ? " drift" : "", F.chi2, F.ncol, F.K, F.fitP ? " + p" : "", F.res.a); if (F.ncol == 2) std::printf("  delta = %+.4f mag per unit ln(1+z)", F.res.delta); std::printf("\n");
    std::printf("      knots n_j:"); for (int j = 0; j < F.K; ++j) { double s = F.covok ? std::sqrt(F.cov[j][j]) : NAN; std::printf(" %.3f(+-%.3f)", F.th[j], s); } if (F.fitP) { double s = F.covok ? std::sqrt(F.cov[F.K][F.K]) : NAN; std::printf("   p = %.3f(+-%.3f)", F.th[F.K], s); } std::printf("\n");
    for (int kind = 0; kind < 2; ++kind) { std::printf(kind == 0 ? "      secant n(z) :" : "      local slope s(z):");
        for (double z : zl) { double x = std::log1p(z); if (x > xmax) continue; double n0 = nprof(F.th, F.K, x, xmax), val = n0, sg = NAN; Vec w(F.K + (F.fitP ? 1 : 0), 0.0); if (F.K == 1) w[0] = 1; else { double t = x / xmax * (F.K - 1); int j = std::min((int)t, F.K - 2); double fr = t - j; w[j] = 1 - fr; w[j + 1] = fr; if (kind == 1) { double dn = (F.th[j + 1] - F.th[j]) * (F.K - 1) / xmax; val = n0 + x * dn; double c = x * (F.K - 1) / xmax; w[j] -= c; w[j + 1] += c; } }
            if (F.covok) { double v = 0; for (size_t a = 0; a < w.size(); ++a) for (size_t b = 0; b < w.size(); ++b) v += w[a] * w[b] * F.cov[a][b]; sg = std::sqrt(std::max(v, 0.0)); } std::printf(" z=%.2f:%.3f(+-%.3f)", z, val, sg); } std::printf("\n"); } }

int main(int argc, char** argv) {
    const char* binned = argc > 1 ? argv[1] : "data/pantheon_binned_DS17f.txt"; const char* covf = argc > 2 ? argv[2] : "Datasets/cosmology/Pantheon_DS17f_binned_sys_covariance.txt"; const char* plusf = argc > 3 ? argv[3] : "Datasets/cosmology/PantheonPlusSH0ES.dat";
    std::printf("CR06 reframe run 2 (registered in the tool header, 2026-10-09)\n==============================================================\n\n"); int fails = 0; auto V = [&](const char* n, bool ok, const char* t) { std::printf("[%s] %s -> %s\n", n, t, ok ? "met" : "NOT MET"); if (!ok) ++fails; };
    Dat A = load_binned(binned, covf, true, "A DS17f 40 bins, full covariance"), B = load_binned(binned, covf, false, "B DS17f 40 bins, diagonal errors"), Cc = load_plus(plusf);
    { char b[200]; std::snprintf(b, 200, "A %d rows, B %d rows (expected 40); C %d rows, z %.4f-%.4f", A.n, B.n, Cc.n, Cc.z.front(), Cc.z.back()); V("V7", A.n == 40 && B.n == 40 && Cc.n > 1000, b); }
    { std::ifstream c(covf); int nn; c >> nn; Vec C(nn * nn); for (auto& t : C) c >> t; double asym = 0; for (int i = 0; i < nn; ++i) for (int j = 0; j < nn; ++j) asym = std::max(asym, std::fabs(C[i * nn + j] - C[j * nn + i])); char b[200]; std::snprintf(b, 200, "systematic covariance %dx%d: max asymmetry %.2e; total covariance Cholesky succeeded (loaded)", nn, nn, asym); V("V5", nn == 40 && asym < 1e-12 && A.cov, b); }
    { bool ok = true; double w = 0; for (double n : {0.3, 1.0, 2.5, 4.0}) { Dat t = B; Vec th{n}; Vec mu; mu_prof(t, th, 1, false, 1.0, mu); for (int i = 0; i < t.n; ++i) { double zz = t.z[i], r = std::fabs(n - 1) < 1e-9 ? std::log1p(zz) : (1 - std::pow(1 + zz, 1 - n)) / (n - 1); double ex = 5 * std::log10(r) + 5 * std::log10(1 + zz); w = std::max(w, std::fabs(mu[i] - ex)); } } ok = w < 1e-9 * 5; char b[160]; std::snprintf(b, 160, "r~ for constant n against the closed form: worst |dmu| = %.2e mag", w); V("V1", ok, b); }
    { Vec th1{0.7}, th3{0.7, 0.7, 0.7}; double c1 = obj_prof(B, th1, 1, false, 1.0, 1), c3 = obj_prof(B, th3, 3, false, 1.0, 1); char b[160]; std::snprintf(b, 160, "K=3 with equal knots %.12f vs K=1 %.12f (diff %.2e)", c3, c1, std::fabs(c3 - c1)); V("V2", std::fabs(c3 - c1) < 1e-9, b); }
    { Dat t = B; Vec th{0.4, 0.9, 1.4}, mu; mu_prof(t, th, 3, false, 1.0, mu); for (int i = 0; i < t.n; ++i) t.m[i] = mu[i] + 3.7; Fit F = fit_prof(t, 3, false, 1); char b[200]; std::snprintf(b, 200, "(toy) noiseless K=3 truth (0.4, 0.9, 1.4), a = 3.7 -> (%.5f, %.5f, %.5f), a-hat %.5f, chi2 %.2e", F.th[0], F.th[1], F.th[2], F.res.a, F.chi2); V("V3", std::fabs(F.th[0] - 0.4) < 1e-4 && std::fabs(F.th[1] - 0.9) < 1e-4 && std::fabs(F.th[2] - 1.4) < 1e-4 && F.chi2 < 1e-9, b); }
    { std::mt19937 g(20261009u); auto u = [&]() { return (g() + 0.5) / 4294967296.0; }; Dat t = B; Vec th{0.7}, mu; mu_prof(t, th, 1, false, 1.0, mu); int R = 300, cov1 = 0; double s1 = 0, s2 = 0, ssig = 0; for (int k = 0; k < R; ++k) { Dat s = t; for (int i = 0; i < s.n; ++i) { double z1 = std::sqrt(-2 * std::log(u())) * std::cos(2 * 3.14159265358979323846 * u()); s.m[i] = mu[i] + 3.7 + z1 * s.e[i]; } Fit F = fit_prof(s, 1, false, 1); double sg = F.covok ? std::sqrt(F.cov[0][0]) : 0; if (std::fabs(F.th[0] - 0.7) <= sg) ++cov1; s1 += F.th[0]; s2 += F.th[0] * F.th[0]; ssig += sg; } double mean = s1 / R, sd = std::sqrt(s2 / R - mean * mean), ms = ssig / R, frac = double(cov1) / R; char b[220]; std::snprintf(b, 220, "(toy) 300 realisations, K=1 truth 0.7: coverage of 1-sigma %.3f, mean sigma-hat %.4f vs scatter %.4f", frac, ms, sd); V("V4", frac >= 0.60 && frac <= 0.76 && std::fabs(ms / sd - 1) < 0.15, b); }
    { Fit F = fit_prof(B, 1, false, 1); Res r; double lo, hi; double Om = lcdm_fit(B, 1, &lo, &hi, &r); char b[220]; std::snprintf(b, 220, "(B) LCDM Om %.4f chi2 %.3f ; K=1 n %.4f chi2 %.3f (run 1: 0.2841, 49.738; 0.6555, 81.027)", Om, r.chi2, F.th[0], F.chi2); V("V6", std::fabs(Om - 0.2841) < 5e-4 && std::fabs(r.chi2 - 49.738) < 5e-3 && std::fabs(F.th[0] - 0.6555) < 5e-4 && std::fabs(F.chi2 - 81.027) < 5e-3, b); }
    std::printf("\nVALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> instrument fault, the object is not assessed"); if (fails) return 1;

    std::vector<Dat*> sets{&A, &B, &Cc};
    for (Dat* dp : sets) { Dat& d = *dp; std::vector<double> zl; for (double z : {0.02, 0.1, 0.3, 0.5, 0.8, 1.2, 1.6, 2.0}) zl.push_back(z);
        std::printf("==== %s ; N = %d, z %.4f-%.4f\n", d.name.c_str(), d.n, d.z.front(), d.z.back());
        std::printf("  [PROFILE, p = 1 (derived), no assumed shape] every K reported\n"); for (int K = 1; K <= 5; ++K) { Fit F = fit_prof(d, K, false, 1); print_prof(d, F, zl); }
        std::printf("  [PREFACTOR power p fitted with the profile]\n"); for (int K = 1; K <= 3; ++K) { Fit F = fit_prof(d, K, true, 1); print_prof(d, F, zl); }
        std::printf("  [EMISSION-LUMINOSITY DRIFT delta fitted with the profile, p = 1]\n"); for (int K = 1; K <= 3; ++K) { Fit F = fit_prof(d, K, false, 2); print_prof(d, F, zl); }
        std::printf("  [FIXED single powers, reported as fits]\n"); for (double n : {1.0, 4.0}) { Vec th{n}, mu; obj_prof(d, th, 1, false, 1.0, 1); mu_prof(d, th, 1, false, 1.0, mu); Res r1 = chi2_of(d, mu, 1), r2 = chi2_of(d, mu, 2); std::printf("   n = %.0f : chi2 = %.3f (offset only) ; with drift chi2 = %.3f, delta = %+.4f mag per unit ln(1+z)\n", n, r1.chi2, r2.chi2, r2.delta); }
        std::printf("  [COMPARATORS]\n"); { Res r; double lo, hi; double Om = lcdm_fit(d, 1, &lo, &hi, &r); std::printf("   flat LCDM: Om = %.4f [%.4f, %.4f], chi2 = %.3f\n      secant n(z) :", Om, lo, hi, r.chi2); for (double z : zl) { if (std::log1p(z) > d.x.back()) continue; double q = Om * std::pow(1 + z, 3); double E = std::sqrt(q + 1 - Om); std::printf(" z=%.2f:%.3f", z, std::log(E) / std::log1p(z)); } std::printf("\n      local slope s(z):"); for (double z : zl) { if (std::log1p(z) > d.x.back()) continue; double q = Om * std::pow(1 + z, 3); std::printf(" z=%.2f:%.3f", z, 1.5 * q / (q + 1 - Om)); } std::printf("\n"); Res rd; double lo2, hi2; double Om2 = lcdm_fit(d, 2, &lo2, &hi2, &rd); std::printf("   flat LCDM with drift: Om = %.4f, chi2 = %.3f, delta = %+.4f mag per unit ln(1+z)\n", Om2, rd.chi2, rd.delta); }
        std::printf("   Milne chi2 = %.3f ; EdS chi2 = %.3f ; de Sitter z(1+z) chi2 = %.3f\n\n", fixedD(d, Dmilne, 1).chi2, fixedD(d, Deds, 1).chi2, fixedD(d, Dlin, 1).chi2); }

    // emission-term residuals for the 40-bin file with full covariance
    std::printf("==== [EMISSION-TERM RESIDUAL] A: m_obs - m_model - a (magnitudes) = what the emission term would have to supply; columns: z, sigma(stat), n=1, n=4, K=1 best, K=3 best, LCDM, Milne\n");
    { Fit f1 = fit_prof(A, 1, false, 1), f3 = fit_prof(A, 3, false, 1); Vec mu1, mu3, muN1, muN4, muL, muM; Vec t1{1.0}, t4{4.0}; mu_prof(A, t1, 1, false, 1.0, muN1); mu_prof(A, t4, 1, false, 1.0, muN4); mu_prof(A, f1.th, 1, false, 1.0, mu1); mu_prof(A, f3.th, 3, false, 1.0, mu3); Res rl, r0, r4, r5, r1, r3, rm; double lo, hi; double Om = lcdm_fit(A, 1, &lo, &hi, &rl); fixedD(A, [&](double z) { return Dlcdm(z, Om); }, 1, &muL); rm = fixedD(A, Dmilne, 1, &muM); r0 = chi2_of(A, muN1, 1); r4 = chi2_of(A, muN4, 1); r1 = chi2_of(A, mu1, 1); r3 = chi2_of(A, mu3, 1);
        for (int i = 0; i < A.n; ++i) std::printf("   %.4f  %.3f  %+7.3f %+7.3f %+7.3f %+7.3f %+7.3f %+7.3f\n", A.z[i], A.e[i], A.m[i] - muN1[i] - r0.a, A.m[i] - muN4[i] - r4.a, A.m[i] - mu1[i] - f1.res.a, A.m[i] - mu3[i] - f3.res.a, A.m[i] - muL[i] - rl.a, A.m[i] - muM[i] - rm.a); }
    return 0;
}
