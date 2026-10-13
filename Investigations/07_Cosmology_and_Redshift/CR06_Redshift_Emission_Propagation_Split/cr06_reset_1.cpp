// CR06 blank-slate run 1 (2026-10-09). REGISTRATION (fixed before the data rows were read; only the file header had been seen).
//
// Question: the prompt asks which single-power propagation law dz/dr = kappa (1+z)^n reproduces the Pantheon distance moduli, with n derived rather than fitted.
// Canon check (laws/cosmology.hpp, "NO-DERIVED-d(z) root"): the engine holds no derived d(z); an in-flight compounding law (ln(1+z)/sigma_0) may not be cited as an SDT derivation. The prompt's family is a transit family; therefore n has no native derivation here and
//  the registered content is the TEST of two candidate laws that the SDT documents state, each with ZERO shape parameters, against the free-n diagnostic and same-fidelity comparators:
//   N1: dz/dr = kappa (1+z)   (n = 1; octaves telescoping at constant octaves per distance: the prompt's "SDT-exp")          origin: CR07-type octave counting, premise "octave count proportional to distance" (not derived)
//   N4: dz/dr = kappa (1+z)^4 (n = 4; kappa proportional to T(z)^4 with T(z) = T_CMB (1+z))                                origin: Hubble/INVESTIGATION_Hubble_Tension.md 4.3, 7.2 (premise: T(z) used as a transit property)
// Model: r(z;n) = integral_0^z (1+z')^-n dz' = [1 - (1+z)^(1-n)]/(n-1) (n != 1), ln(1+z) (n = 1); luminosity distance shape D = (1+z) r  (prefactor exponent p = 1, as the prompt). Magnitude m = 5 log10 D + a, a = M - 5 log10 H0 + const: ONE nuisance offset per model, solved analytically (weighted least squares).
// Comparators (same fidelity, all with the same offset): flat LCDM(Om) D = (1+z) int dz'/sqrt(Om (1+z')^3 + 1 - Om); EdS (Om = 1); Milne D = z (1 + z/2); Linear D = z (1+z).  Diagnostic: SDT n-free (n fitted: CALIBRATED(1)).
// Parameter ledger (shape parameters): N1 0, N4 0, Milne 0, EdS 0, Linear 0, n-free 1 (CALIBRATED), LCDM 1 (Om, CALIBRATED). Offset: 1 each (nuisance).
// Data: data/pantheon_binned_DS17f.txt (named by the prompt; 40 bins, zcmb, mb, dmb; Scolnic et al. 2018). LIMITATION registered: diagonal errors only (the full covariance file is not in the repository: PENDING); absolute chi2/dof is not a gate, only differences are used.
// Selections registered: models 7, splits 2, prefactor sensitivity 3 (not a selection). Look-elsewhere: the native-candidate comparison selects between 2 members.
// Splits (fixed by sorted z only): S1 = train on the lowest 20 bins, test on the highest 20 (extrapolation); S2 = train on even sorted positions 0,2,4,..., test on odd (interpolation); and S2' = the swap. Predictive chi2 = chi2 over the test bins with the parameters (offset, shape) fitted on the train bins only.
// Criteria (numeric, registered):
//  RC1 (exclusion of a candidate law): N1 or N4 excluded if chi2(candidate) - chi2(n-free best) > 9 on the full data (one extra parameter, 3 sigma gate). Outcome classes: both consistent / N1 only / N4 only / both excluded; each is populated (n-hat can lie near 1, near 4, between, or elsewhere).
//  RC2 (the prompt's own classes, applied to the lower-chi2 candidate): PASS if AIC(candidate) - AIC(LCDM) <= 0 and bend reproduced; QUALIFIED if <= 10 and bend reproduced; PARTIAL if it beats EdS and Linear in chi2 and reproduces the bend but LCDM wins by > 10; FAIL otherwise.
//    Bend reproduced: f = [chi2(Milne) - chi2(model)] / [chi2(Milne) - chi2(LCDM)] >= 0.9, provided chi2(Milne) - chi2(LCDM) > 9 (otherwise the data show no bend and f is not defined).
//  RC3 (stability of a fitted exponent): n-hat from the S1 train, S2 train and S2' train fits must each agree with the full-data n-hat within 2 combined sigma (profile Delta chi2 = 1 intervals); if not, the exponent is not a stable property of these data.
//  RC4 (held-out): the candidate is predictively consistent if its test chi2 does not exceed the LCDM test chi2 by more than 9 on S1 and on S2/S2'.
// Gradation (REOPEN protocol 5): G0 any validation not met; G1 a candidate excluded by RC1; G2 open; G3 consistent with a named shared input; G4 consistent, independent origin; G5 discriminating.
// Validations (known answers, toy inputs labelled toy): V1 the n-family against numerical quadrature of (1+z)^-n (n = 0.5, 1, 2, 4; z = 1.612; rel 1e-9); V2 LCDM(Om = 1) = EdS closed form and LCDM(Om = 0) = z(1+z) (rel 1e-9);
//  [CORRECTION 2026-10-09, attempt 1 stopped at V2 before any fit: V2 as first written compared LCDM(Om = 0) with Milne. Flat LCDM with Om = 0 is de Sitter, D = z(1+z), which is the prompt's "Linear" model; Milne is the open empty model and is not a flat-LCDM limit. The registered known answer was wrong, the instrument was not. Attempt 1 output kept as cr06_reset_1_results_attempt1_G0.txt.]
//  V3 (toy) noiseless synthetic m = 5 log10 D(z; n = 2.5) + 3.7 on the data z grid: the n-free fit recovers n = 2.5 and a = 3.7 (1e-6), chi2 < 1e-12; V4 (toy) 200 noisy realisations (Box-Muller on mt19937 raw output, errors = dmb of the file) of n = 4: mean of n-hat within 3 sigma/sqrt(200) of 4;
//  V5 the file parses to 40 rows with z between 0.014 and 1.612 (as the prompt states).
// Sensitivity (reported, not selected): prefactor D = (1+z)^p r with p = 1/2 (energy loss only), 1, 2 for the n-free fit.
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <random>
#include <sstream>
#include <string>
#include <vector>

struct Row { double z, m, e; };
static std::vector<Row> load(const char* path) {
    std::vector<Row> v; std::ifstream f(path); std::string line;
    while (std::getline(f, line)) { if (line.empty() || line[0] == '#') continue; std::istringstream s(line); std::string name; double zcmb, zhel, dz, mb, dmb; if (s >> name >> zcmb >> zhel >> dz >> mb >> dmb) v.push_back({zcmb, mb, dmb}); }
    std::sort(v.begin(), v.end(), [](const Row& a, const Row& b) { return a.z < b.z; }); return v;
}
// shapes
static double rfam(double z, double n) { if (std::fabs(n - 1) < 1e-9) return std::log1p(z); return (1.0 - std::pow(1 + z, 1 - n)) / (n - 1); }
static double Dfam(double z, double n, double p = 1.0) { return std::pow(1 + z, p) * rfam(z, n); }
static double Dlcdm(double z, double Om) { const int N = 2000; double h = z / N, s = 0; auto f = [&](double x) { return 1.0 / std::sqrt(Om * std::pow(1 + x, 3) + 1 - Om); }; s = f(0) + f(z); for (int i = 1; i < N; ++i) s += (i % 2 ? 4 : 2) * f(i * h); return (1 + z) * s * h / 3; }
static double Dmilne(double z) { return z * (1 + z / 2); }
static double Dlin(double z) { return z * (1 + z); }
static double Deds(double z) { return (1 + z) * 2 * (1 - 1 / std::sqrt(1 + z)); }
enum Model { N1, N4, NF, LCDM, EDS, MILNE, LIN };
static const char* mname[] = {"N1 (n=1)", "N4 (n=4)", "n-free", "LCDM(Om)", "EdS", "Milne", "Linear"};
static const int kshape[] = {0, 0, 1, 1, 0, 0, 0};
static double Dmodel(int mdl, double z, double par, double p = 1.0) { switch (mdl) { case N1: return Dfam(z, 1, p); case N4: return Dfam(z, 4, p); case NF: return Dfam(z, par, p); case LCDM: return Dlcdm(z, par); case EDS: return Deds(z); case MILNE: return Dmilne(z); default: return Dlin(z); } }
struct Fit { double par, a, chi2; };
static double offset_chi2(const std::vector<Row>& d, int mdl, double par, double p, double* a_out) { double sw = 0, sx = 0; std::vector<double> mu(d.size()); for (size_t i = 0; i < d.size(); ++i) { mu[i] = 5 * std::log10(Dmodel(mdl, d[i].z, par, p)); double w = 1 / (d[i].e * d[i].e); sw += w; sx += w * (d[i].m - mu[i]); } double a = sx / sw, c = 0; for (size_t i = 0; i < d.size(); ++i) { double r = d[i].m - mu[i] - a; c += r * r / (d[i].e * d[i].e); } if (a_out) *a_out = a; return c; }
static double chi2_with(const std::vector<Row>& d, int mdl, double par, double a, double p = 1.0) { double c = 0; for (auto& r : d) { double x = (r.m - 5 * std::log10(Dmodel(mdl, r.z, par, p)) - a) / r.e; c += x * x; } return c; }
static Fit fit(const std::vector<Row>& d, int mdl, double p = 1.0) {
    Fit b{0, 0, 0}; if (kshape[mdl] == 0) { b.chi2 = offset_chi2(d, mdl, 0, p, &b.a); return b; }
    double lo = mdl == NF ? -3 : 0.0, hi = mdl == NF ? 12 : 1.0, st = mdl == NF ? 0.05 : 0.005, best = 1e300, bp = lo;
    for (double x = lo; x <= hi + 1e-12; x += st) { double c = offset_chi2(d, mdl, x, p, nullptr); if (c < best) { best = c; bp = x; } }
    double a_ = std::max(lo, bp - st), b_ = std::min(hi, bp + st); const double g = (std::sqrt(5.0) - 1) / 2; double c = b_ - g * (b_ - a_), e = a_ + g * (b_ - a_), fc = offset_chi2(d, mdl, c, p, nullptr), fe = offset_chi2(d, mdl, e, p, nullptr);
    for (int i = 0; i < 100; ++i) { if (fc > fe) { a_ = c; c = e; fc = fe; e = a_ + g * (b_ - a_); fe = offset_chi2(d, mdl, e, p, nullptr); } else { b_ = e; e = c; fe = fc; c = b_ - g * (b_ - a_); fc = offset_chi2(d, mdl, c, p, nullptr); } }
    b.par = 0.5 * (a_ + b_); b.chi2 = offset_chi2(d, mdl, b.par, p, &b.a); return b; }
// profile interval Delta chi2 = 1 for n-free
static void interval(const std::vector<Row>& d, const Fit& f, double& nlo, double& nhi) {
    auto g = [&](double n) { return offset_chi2(d, NF, n, 1.0, nullptr) - f.chi2 - 1.0; };
    double L = -8, H = 20; { double a = f.par, b = L; if (g(b) < 0) nlo = L; else { for (int i = 0; i < 100; ++i) { double m = 0.5 * (a + b); if (g(m) < 0) a = m; else b = m; } nlo = 0.5 * (a + b); } }
    { double a = f.par, b = H; if (g(b) < 0) nhi = H; else { for (int i = 0; i < 100; ++i) { double m = 0.5 * (a + b); if (g(m) < 0) a = m; else b = m; } nhi = 0.5 * (a + b); } } }

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "data/pantheon_binned_DS17f.txt";
    std::printf("CR06 blank-slate run 1 (registered in the tool header, 2026-10-09)\n==================================================================\n\n");
    int fails = 0; auto V = [&](const char* n, bool ok, const char* d) { std::printf("[%s] %s -> %s\n", n, d, ok ? "met" : "NOT MET"); if (!ok) ++fails; };
    std::vector<Row> D = load(path); const int N = (int)D.size();
    { char b[200]; std::snprintf(b, 200, "file parses to %d rows, z from %.3f to %.3f (prompt: 40 bins, 0.014-1.612)", N, N ? D.front().z : 0, N ? D.back().z : 0); V("V5", N == 40 && std::fabs(D.front().z - 0.014) < 5e-4 && std::fabs(D.back().z - 1.612) < 5e-4, b); }
    { bool ok = true; double worst = 0; for (double n : {0.5, 1.0, 2.0, 4.0}) { double z = 1.612; int M = 200000; double h = z / M, s = 0; for (int i = 0; i < M; ++i) { double x = (i + 0.5) * h; s += std::pow(1 + x, -n); } s *= h; double an = rfam(z, n); worst = std::max(worst, std::fabs(an / s - 1)); } ok = worst < 1e-9; char b[160]; std::snprintf(b, 160, "family closed form against midpoint quadrature (n = 0.5, 1, 2, 4): worst rel %.2e", worst); V("V1", ok, b); }
    { double w1 = 0, w0 = 0; for (double z : {0.1, 0.5, 1.0, 1.612}) { w1 = std::max(w1, std::fabs(Dlcdm(z, 1.0) / Deds(z) - 1)); w0 = std::max(w0, std::fabs(Dlcdm(z, 0.0) / Dlin(z) - 1)); } char b[160]; std::snprintf(b, 160, "LCDM(1) vs EdS worst %.2e ; LCDM(0) vs z(1+z) (de Sitter) worst %.2e", w1, w0); V("V2", w1 < 1e-9 && w0 < 1e-9, b); }
    std::vector<Row> toy = D; for (auto& r : toy) r.m = 5 * std::log10(Dfam(r.z, 2.5)) + 3.7;
    { Fit f = fit(toy, NF); char b[200]; std::snprintf(b, 200, "(toy) noiseless n = 2.5, a = 3.7 -> n-hat %.8f, a-hat %.8f, chi2 %.2e", f.par, f.a, f.chi2); V("V3", std::fabs(f.par - 2.5) < 1e-6 && std::fabs(f.a - 3.7) < 1e-6 && f.chi2 < 1e-12, b); }
    { std::mt19937 g(20261009u); auto u = [&]() { return (g() + 0.5) / 4294967296.0; }; double sum = 0, sum2 = 0; const int R = 200; for (int k = 0; k < R; ++k) { std::vector<Row> s = D; for (auto& r : s) { double z1 = std::sqrt(-2 * std::log(u())) * std::cos(2 * 3.14159265358979323846 * u()); r.m = 5 * std::log10(Dfam(r.z, 4.0)) + 3.7 + z1 * r.e; } Fit f = fit(s, NF); sum += f.par; sum2 += f.par * f.par; } double mean = sum / R, sd = std::sqrt(std::max(0.0, sum2 / R - mean * mean)); char b[200]; std::snprintf(b, 200, "(toy) 200 realisations of n = 4: mean n-hat %.4f, scatter %.4f, |mean - 4| = %.4f vs 3 sigma/sqrt(200) = %.4f", mean, sd, std::fabs(mean - 4), 3 * sd / std::sqrt(200.0)); V("V4", std::fabs(mean - 4) < 3 * sd / std::sqrt(200.0), b); }
    std::printf("\nVALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0 (object not assessed)"); if (fails) return 1;

    // ---- single pass, full data
    Fit F[7]; for (int m = 0; m < 7; ++m) F[m] = fit(D, m);
    const double lnN = std::log((double)N);
    std::printf("[FULL] N = %d bins. model, shape parameter, offset a, chi2, chi2/dof (diagonal errors only: absolute value not a gate), AIC, BIC\n", N);
    double aicmin = 1e300; for (int m = 0; m < 7; ++m) { int k = kshape[m] + 1; aicmin = std::min(aicmin, F[m].chi2 + 2 * k); }
    for (int m = 0; m < 7; ++m) { int k = kshape[m] + 1; std::printf("   %-9s par = %8.4f  a = %9.5f  chi2 = %9.3f  chi2/dof = %6.3f  AIC = %9.3f  BIC = %9.3f  dAIC = %7.3f\n", mname[m], F[m].par, F[m].a, F[m].chi2, F[m].chi2 / (N - k), F[m].chi2 + 2 * k, F[m].chi2 + k * lnN, F[m].chi2 + 2 * k - aicmin); }
    double nlo, nhi; interval(D, F[NF], nlo, nhi); std::printf("[FULL] n-free: n-hat = %.4f, Delta chi2 = 1 interval [%.4f, %.4f]\n", F[NF].par, nlo, nhi);
    bool ex1 = F[N1].chi2 - F[NF].chi2 > 9, ex4 = F[N4].chi2 - F[NF].chi2 > 9;
    std::printf("[RC1] chi2(N1) - chi2(n-free) = %.3f -> %s ; chi2(N4) - chi2(n-free) = %.3f -> %s\n", F[N1].chi2 - F[NF].chi2, ex1 ? "excluded" : "not excluded", F[N4].chi2 - F[NF].chi2, ex4 ? "excluded" : "not excluded");
    // bend and RC2
    double dM = F[MILNE].chi2 - F[LCDM].chi2; std::printf("[RC2] bend: chi2(Milne) - chi2(LCDM) = %.3f -> %s\n", dM, dM > 9 ? "bend present in the data" : "no bend (f undefined)");
    int cand = F[N1].chi2 <= F[N4].chi2 ? N1 : N4; std::printf("[RC2] lower-chi2 native candidate: %s\n", mname[cand]);
    for (int m : {N1, N4, NF}) { double f = dM > 9 ? (F[MILNE].chi2 - F[m].chi2) / dM : NAN; double dA = (F[m].chi2 + 2 * (kshape[m] + 1)) - (F[LCDM].chi2 + 2 * 2); std::printf("      %-9s f = %.3f ; AIC - AIC(LCDM) = %.3f ; beats EdS: %s ; beats Linear: %s\n", mname[m], f, dA, F[m].chi2 < F[EDS].chi2 ? "yes" : "no", F[m].chi2 < F[LIN].chi2 ? "yes" : "no"); }
    { int m = cand; double f = dM > 9 ? (F[MILNE].chi2 - F[m].chi2) / dM : 0; double dA = (F[m].chi2 + 2) - (F[LCDM].chi2 + 4); bool bend = dM > 9 && f >= 0.9; const char* cls = (dA <= 0 && bend) ? "PASS" : (dA <= 10 && bend) ? "QUALIFIED" : (F[m].chi2 < F[EDS].chi2 && F[m].chi2 < F[LIN].chi2 && bend) ? "PARTIAL" : "FAIL"; std::printf("[RC2] class of %s: %s\n\n", mname[m], cls); }
    // residuals
    std::printf("[RES] per-bin residuals m_obs - m_model - a, in sigma: z, LCDM, N1, N4, n-free, Milne\n"); for (int i = 0; i < N; ++i) { auto rs = [&](int m) { return (D[i].m - 5 * std::log10(Dmodel(m, D[i].z, F[m].par)) - F[m].a) / D[i].e; }; std::printf("   %.4f  %+6.2f %+6.2f %+6.2f %+6.2f %+6.2f\n", D[i].z, rs(LCDM), rs(N1), rs(N4), rs(NF), rs(MILNE)); }
    // splits
    std::printf("\n[SPLIT] held-out: parameters from the train bins only, chi2 on the test bins\n");
    struct Sp { const char* nm; std::vector<Row> tr, te; } sp[3];
    sp[0].nm = "S1 lowest 20 -> highest 20"; sp[1].nm = "S2 even -> odd"; sp[2].nm = "S2' odd -> even";
    for (int i = 0; i < N; ++i) { (i < N / 2 ? sp[0].tr : sp[0].te).push_back(D[i]); (i % 2 == 0 ? sp[1].tr : sp[1].te).push_back(D[i]); (i % 2 == 1 ? sp[2].tr : sp[2].te).push_back(D[i]); }
    double nhat[3], nsig[3]; bool rc3 = true, rc4[2] = {true, true};
    for (int s = 0; s < 3; ++s) { std::printf("  %s (train %zu, test %zu)\n", sp[s].nm, sp[s].tr.size(), sp[s].te.size()); double tc[7];
        for (int m = 0; m < 7; ++m) { Fit t = fit(sp[s].tr, m); tc[m] = chi2_with(sp[s].te, m, t.par, t.a); std::printf("     %-9s train par %8.4f a %9.5f train chi2 %8.3f test chi2 %9.3f\n", mname[m], t.par, t.a, t.chi2, tc[m]); if (m == NF) { double lo, hi; interval(sp[s].tr, t, lo, hi); nhat[s] = t.par; nsig[s] = 0.5 * (hi - lo); std::printf("        n-free train interval [%.3f, %.3f]\n", lo, hi); } }
        for (int m : {N1, N4}) if (tc[m] - tc[LCDM] > 9) rc4[m == N1 ? 0 : 1] = false; }
    double sfull = 0.5 * (nhi - nlo); for (int s = 0; s < 3; ++s) { double comb = std::sqrt(sfull * sfull + nsig[s] * nsig[s]); double dn = std::fabs(nhat[s] - F[NF].par); std::printf("[RC3] %s: n-hat %.3f vs full %.3f: |diff| %.3f, combined sigma %.3f -> %s\n", sp[s].nm, nhat[s], F[NF].par, dn, comb, dn <= 2 * comb ? "stable" : "NOT stable"); if (dn > 2 * comb) rc3 = false; }
    std::printf("[RC3] overall: %s\n[RC4] predictive consistency with LCDM (test chi2 within +9 on S1, S2, S2'): N1 %s, N4 %s\n\n", rc3 ? "stable" : "NOT stable", rc4[0] ? "yes" : "no", rc4[1] ? "yes" : "no");
    // sensitivity
    std::printf("[SENS] prefactor D = (1+z)^p r, n-free fit on the full data (reported, not selected):\n"); for (double p : {0.5, 1.0, 2.0}) { Fit f = fit(D, NF, p); std::printf("   p = %.1f: n-hat %.4f, a %.5f, chi2 %.3f\n", p, f.par, f.a, f.chi2); }
    return 0;
}
