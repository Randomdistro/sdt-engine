// GOM26 blank-slate run 1 (2026-10-10). Registration: GOM26_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
// Pairwise energy-equality estimator of mu from (r, |v|); invariant koppa = mu/c^2; per-epoch reconstruction; CV gate; held-out year; spectral map c*koppa/R_Sun.
// Delete-test: koppa is printed before bridge::koppa_Sun or any HARPS value is used.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

struct Orb { std::vector<double> r, v2; };            // SI: m, m^2/s^2
static Orb readOrb(const char* path) { Orb o; std::ifstream f(path); std::string ln; bool in = false; while (std::getline(f, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue;
        std::vector<std::string> t; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; t.push_back(ln.substr(p, q - p)); p = q + 1; } if (t.size() < 8) continue;
        double X = std::stod(t[2]) * 1e3, Y = std::stod(t[3]) * 1e3, Z = std::stod(t[4]) * 1e3, VX = std::stod(t[5]) * 1e3, VY = std::stod(t[6]) * 1e3, VZ = std::stod(t[7]) * 1e3; o.r.push_back(std::sqrt(X * X + Y * Y + Z * Z)); o.v2.push_back(VX * VX + VY * VY + VZ * VZ); } return o; }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); size_t n = v.size(); return n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]); }
struct Res { double mu, sigMu, sigMuPairs, a, cv, kappa; int pairs, usable; };
static Res analyse(const Orb& o, const double c) {
    const int n = (int)o.r.size(); std::vector<double> mus; int pairs = 0; const double eps = 1e-15;
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) { ++pairs; double d = 1.0 / o.r[j] - 1.0 / o.r[i]; if (std::fabs(d) > eps) mus.push_back((o.v2[j] - o.v2[i]) / (2.0 * d)); }
    Res R{}; R.pairs = pairs; R.usable = (int)mus.size(); R.mu = med(mus); std::vector<double> dev; for (double m : mus) dev.push_back(std::fabs(m - R.mu)); double mad = med(dev);
    R.sigMu = 1.4826 * mad / std::sqrt((double)n); R.sigMuPairs = 1.4826 * mad / std::sqrt((double)mus.size());
    double Em = 0; for (int i = 0; i < n; ++i) Em += o.v2[i] / 2 - R.mu / o.r[i]; Em /= n; R.a = -R.mu / (2 * Em);
    std::vector<double> k; for (int i = 0; i < n; ++i) { double den = 2.0 / o.r[i] - 1.0 / R.a; if (den > 0) k.push_back(o.v2[i] / (c * c * den)); }
    double m = 0; for (double x : k) m += x; m /= k.size(); double s = 0; for (double x : k) s += (x - m) * (x - m); s = std::sqrt(s / (k.size() - 1)); R.cv = s / m; R.kappa = R.mu / (c * c); return R; }
static Orb mock(double e, double mu, double a, int n, double dtDays) { Orb o; double nn = std::sqrt(mu / (a * a * a)); for (int k = 0; k < n; ++k) { double Mk = nn * dtDays * 86400.0 * k, E = Mk; for (int it = 0; it < 60; ++it) E -= (E - e * std::sin(E) - Mk) / (1 - e * std::cos(E)); double r = a * (1 - e * std::cos(E)); o.r.push_back(r); o.v2.push_back(mu * (2.0 / r - 1.0 / a)); } return o; }

int main() {
    std::printf("GOM26 blank-slate run 1 (registered in GOM26_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n=======================================================================\n\n");
    const double c = M::c; int fails = 0;
    for (double e : {0.01, 0.0167}) { const double muT = 1.0e20; Orb o = mock(e, muT, 1.5e11, 27, 14.0); Res r = analyse(o, c); bool ok = std::fabs(r.mu / muT - 1) < 1e-8 && r.cv < 1e-6; std::printf("[V%s] Kepler mock e = %.4f: mu recovered %.12e vs %.1e (relative %.2e), CV %.2e, pairs usable %d of %d -> %s\n", e < 0.015 ? "A" : "B", e, r.mu, muT, r.mu / muT - 1, r.cv, r.usable, r.pairs, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS A, B: met (C, the delete-test, is the order of the prints below)\n\n");
    Orb cal = readOrb("Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2025.csv"), hold = readOrb("Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2024.csv");
    Res rc = analyse(cal, c), rh = analyse(hold, c);
    std::printf("CALIBRATION (2025, %zu epochs): pairs %d, usable %d (%.1f%%) ; mu = %.9e m^3/s^2 ; sigma_mu (N_eff = %zu) = %.3e (relative %.2e) ; sigma_mu (N_eff = usable pairs) = %.3e (relative %.2e)\n", cal.r.size(), rc.pairs, rc.usable, 100.0 * rc.usable / rc.pairs, rc.mu, cal.r.size(), rc.sigMu, rc.sigMu / rc.mu, rc.sigMuPairs, rc.sigMuPairs / rc.mu);
    std::printf("  semi-major axis a = %.6e m (%.6f AU) ; invariant koppa = mu/c^2 = %.6f m ; CV of koppa_i = %.3e (gate 1e-3: %s)\n", rc.a, rc.a / M::AU, rc.kappa, rc.cv, rc.cv < 1e-3 ? "met" : "NOT MET");
    std::printf("HELD-OUT (2024, %zu epochs): mu = %.9e ; koppa = %.6f m ; CV %.3e ; |koppa_hold - koppa_cal|/koppa_cal = %.3e (gate 1e-3: %s)\n", hold.r.size(), rh.mu, rh.kappa, rh.cv, std::fabs(rh.kappa - rc.kappa) / rc.kappa, std::fabs(rh.kappa - rc.kappa) / rc.kappa < 1e-3 ? "met" : "NOT MET");
    { Orb odd, even; for (size_t i = 0; i < cal.r.size(); ++i) { (i % 2 ? even : odd).r.push_back(cal.r[i]); (i % 2 ? even : odd).v2.push_back(cal.v2[i]); } Res ro = analyse(odd, c), re = analyse(even, c); std::printf("  intra-year split (descriptive): odd %.6f m, even %.6f m : relative difference %.3e\n", ro.kappa, re.kappa, std::fabs(ro.kappa - re.kappa) / rc.kappa); }
    // spectral map (after koppa is printed)
    const double Rn = M::R_Sun, Rd = 695658e3; double vp = c * rc.kappa / Rn, sP = vp * rc.sigMu / rc.mu, thr = 2 * std::sqrt(sP * sP + 36.0), vpD = c * rc.kappa / Rd;
    std::printf("\nSPECTRAL MAP: v_pred = c koppa / R_Sun = %.4f m/s (R = %.4e m) ; sigma_pred = %.4f m/s ; |v_pred - 638| = %.4f ; threshold 2 sqrt(sigma_pred^2 + 6^2) = %.4f -> %s (UNADJUDICATED)\n", vp, Rn, sP, std::fabs(vp - 638.0), thr, std::fabs(vp - 638.0) > thr ? "EXCLUDED" : "COMPATIBLE");
    std::printf("  sensitivity R = 695658 km: v_pred = %.4f m/s ; with the observer term (GOM25 amendment): v_pred - c koppa/AU = %.4f m/s (difference %.3f m/s)\n", vpD, vp - c * rc.kappa / M::AU, c * rc.kappa / M::AU);
    // descriptive after the print
    const double kS = bridge::koppa_Sun; std::printf("\nDESCRIPTIVE (after the print): koppa / bridge::koppa_Sun = %.6f ; GOM25 regression constant A/2 = 1.476399 km -> ratio %.6f ; instantaneous mean v^2 r/c^2 (GOM25) 1.477262 km -> ratio %.6f\n", rc.kappa / kS, rc.kappa / 1476.399, rc.kappa / 1477.262);
    return 0;
}
