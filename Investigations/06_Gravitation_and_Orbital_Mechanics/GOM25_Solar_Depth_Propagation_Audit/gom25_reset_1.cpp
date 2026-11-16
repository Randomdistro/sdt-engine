// GOM25 blank-slate run 1 (2026-10-10). Registration: GOM25_RESET_ASSESSMENT_2026-10-10.md sections 0-3 (written before this file existed).
//  V1 regression of koppa_i on |r_i|: R^2 >= 0.999 and -A/(2B) within 0.5% of 1 AU; V2 quadrature known integrals to 1e-10; V3 domain gate; V4 JD spacing 14.0 d.
//  Decision 1: EXCLUDED if |mean(v_pred) - v_obs| > 2 sqrt(sigma_pred^2 + sigma_obs^2); primary sigma_pred = v*140/695658; sensitivity adds sd of v_pred,i over rows.
//  Decision 2: CV of koppa_i. Decision 3: exact straight-path integral vs depth_closure::shapiro_delay (LEADING_ORDER). Decision 4: not run. Decision 5: domain 0 <= z < 1.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <numbers>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

static const double C = M::c;                                  // m/s
static std::string pad(const std::string& s, size_t n) { return s.size() >= n ? s : s + std::string(n - s.size(), ' '); }
static double fld(const std::string& line, int b1, int b2) { std::string p = pad(line, 80); return std::stod(p.substr(b1 - 1, b2 - b1 + 1)); }
static double simpson(const std::function<double(double)>& f, double a, double b, int n) { double h = (b - a) / n, s = f(a) + f(b); for (int i = 1; i < n; ++i) s += f(a + i * h) * (i % 2 ? 4.0 : 2.0); return s * h / 3.0; }
static bool domainOK(double z) { return std::isfinite(z) && z >= 0.0 && z < 1.0; }

int main() {
    std::printf("GOM25 blank-slate run 1 (registered in GOM25_RESET_ASSESSMENT_2026-10-10.md sections 0-3)\n=====================================================================\n\n");
    int fails = 0;
    // ---- read D1
    std::vector<double> jd, rx, ry, rz, vx, vy, vz;
    { std::ifstream f("Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2025.csv"); std::string ln; bool in = false;
      while (std::getline(f, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue;
          std::vector<std::string> t; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; t.push_back(ln.substr(p, q - p)); p = q + 1; }
          if (t.size() < 8) continue; jd.push_back(std::stod(t[0])); rx.push_back(std::stod(t[2])); ry.push_back(std::stod(t[3])); rz.push_back(std::stod(t[4])); vx.push_back(std::stod(t[5])); vy.push_back(std::stod(t[6])); vz.push_back(std::stod(t[7])); } }
    const int n = (int)jd.size(); std::printf("D1 rows read: %d (JD %.1f to %.1f)\n", n, jd.front(), jd.back());
    std::vector<double> r(n), ks(n);                                // r in km, koppa in km
    for (int i = 0; i < n; ++i) { r[i] = std::sqrt(rx[i] * rx[i] + ry[i] * ry[i] + rz[i] * rz[i]); double v = std::sqrt(vx[i] * vx[i] + vy[i] * vy[i] + vz[i] * vz[i]); ks[i] = v * v * r[i] / ((C / 1000.0) * (C / 1000.0)); }
    // ---- V1
    double mx = 0, my = 0; for (int i = 0; i < n; ++i) { mx += r[i]; my += ks[i]; } mx /= n; my /= n; double sxy = 0, sxx = 0, syy = 0; for (int i = 0; i < n; ++i) { sxy += (r[i] - mx) * (ks[i] - my); sxx += (r[i] - mx) * (r[i] - mx); syy += (ks[i] - my) * (ks[i] - my); }
    const double B = sxy / sxx, A = my - B * mx, R2 = sxy * sxy / (sxx * syy), aReg = -A / (2.0 * B), AUkm = M::AU / 1000.0, k0 = A / 2.0;
    bool v1 = R2 >= 0.999 && std::fabs(aReg / AUkm - 1.0) < 5e-3; std::printf("[V1] koppa_i = A + B|r_i|: A = %.6f km, B = %.6e per km, R^2 = %.6f, -A/(2B) = %.6e km (%.5f AU) -> %s\n", A, B, R2, aReg, aReg / AUkm, v1 ? "met" : "NOT MET"); if (!v1) ++fails;
    // ---- V2
    { double b = 3.7, L = 250.0; auto f1 = [&](double s) { return 1.0 / std::sqrt(s * s + b * b); }; auto f2 = [&](double s) { return 1.0 / (s * s + b * b); };
      double e1 = std::fabs(simpson(f1, -L, L, 4000) / (2 * std::asinh(L / b)) - 1), e2 = std::fabs(simpson(f2, -L, L, 4000) / ((2 / b) * std::atan(L / b)) - 1);
      bool ok = e1 < 1e-10 && e2 < 1e-10; std::printf("[V2] Simpson N=4000: 1/sqrt relative error %.2e, 1/(s^2+b^2) relative error %.2e -> %s\n", e1, e2, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // ---- V3
    { bool ok = domainOK(0.0) && domainOK(0.5) && !domainOK(1.0) && !domainOK(1.5) && !domainOK(-0.01) && !domainOK(std::nan("")); std::printf("[V3] domain gate (accept 0, 0.5; reject 1, 1.5, -0.01, NaN) -> %s\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // ---- V4
    { double worst = 0; for (int i = 1; i < n; ++i) worst = std::max(worst, std::fabs(jd[i] - jd[i - 1] - 14.0)); bool ok = worst < 1e-6; std::printf("[V4] JD spacing: max |dJD - 14| = %.2e -> %s\n\n", worst, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0"); if (fails) return 1;

    // ---- D3 comparators
    std::vector<double> fit, efit, core1; double wsum = 0, wmean = 0;
    { std::ifstream f("Datasets/solar_propagation_2026-08/raw/harps_lfc_tablea2.dat"); std::string ln; while (std::getline(f, ln)) { if (ln.size() < 60) continue; fit.push_back(fld(ln, 65, 69)); efit.push_back(fld(ln, 71, 74)); } }
    { std::ifstream f("Datasets/solar_propagation_2026-08/raw/harps_lfc_tablea1.dat"); std::string ln; while (std::getline(f, ln)) { if (ln.size() < 60) continue; core1.push_back(fld(ln, 66, 70)); } }
    auto stats = [](const std::vector<double>& v, double& m, double& sd) { m = 0; for (double a : v) m += a; m /= v.size(); sd = 0; for (double a : v) sd += (a - m) * (a - m); sd = std::sqrt(sd / (v.size() - 1)); };
    double mB, sdB, mC, sdC; stats(fit, mB, sdB); stats(core1, mC, sdC); for (size_t i = 0; i < fit.size(); ++i) { double w = 1.0 / (efit[i] * efit[i]); wsum += w; wmean += w * fit[i]; } wmean /= wsum; std::vector<double> sorted = fit; std::sort(sorted.begin(), sorted.end());
    const double seB = sdB / std::sqrt((double)fit.size()), seC = sdC / std::sqrt((double)core1.size());
    std::printf("D3 comparators: (A) published 638 +- 6 m/s ; (B) table A.2 v_fit_3D_n: %zu lines, mean %.2f, sd %.1f, se %.2f, weighted mean %.2f +- %.2f, median %.1f ; (C) table A.1 v_core_obs: %zu lines, mean %.2f, sd %.1f, se %.2f\n\n", fit.size(), mB, sdB, seB, wmean, 1.0 / std::sqrt(wsum), sorted[sorted.size() / 2], core1.size(), mC, sdC, seC);

    // ---- Decision 5 and Decision 2
    const double Rnom = 695700.0, Rdir = 695658.0, sRdir = 140.0;
    bool domain = true; for (int i = 0; i < n; ++i) { double zR = ks[i] / Rnom, zr = ks[i] / r[i]; if (!domainOK(zR) || !domainOK(zr)) domain = false; }
    double kmean = my, ksd = 0, kmin = 1e9, kmax = -1e9; for (double k : ks) { ksd += (k - kmean) * (k - kmean); kmin = std::min(kmin, k); kmax = std::max(kmax, k); } ksd = std::sqrt(ksd / (n - 1));
    std::printf("[Decision 5] all z(R_Sun) and z(r_i) in [0,1): %s ; z(R_Sun) range %.4e to %.4e\n", domain ? "yes" : "NO", kmin / Rnom, kmax / Rnom);
    std::printf("[Decision 2] koppa_i (km): mean %.6f, sd %.6f, CV %.4f%%, min %.6f, max %.6f ; |r| range %.4e to %.4e km ; variation linear in |r| (V1 R^2 = %.6f); exploratory invariants: A/2 = %.6f km, -A/(2B) = %.5f AU\n\n", kmean, ksd, 100 * ksd / kmean, kmin, kmax, *std::min_element(r.begin(), r.end()), *std::max_element(r.begin(), r.end()), R2, k0, aReg / AUkm);

    // ---- Decision 1
    auto vpred = [&](int i, double R) { return C * (ks[i] * 1000.0) * (1.0 / (R * 1000.0) - 1.0 / (r[i] * 1000.0)); };   // m/s with koppa, R, r converted to m
    for (int pass = 0; pass < 2; ++pass) {
        double R = pass == 0 ? Rnom : Rdir; std::vector<double> vp(n); double m = 0; for (int i = 0; i < n; ++i) { vp[i] = vpred(i, R); m += vp[i]; } m /= n; double sd = 0; for (double a : vp) sd += (a - m) * (a - m); sd = std::sqrt(sd / (n - 1));
        double lo = 1e9, hi = -1e9; for (int j = 0; j < n; ++j) { double s = 0; for (int i = 0; i < n; ++i) if (i != j) s += vp[i]; s /= (n - 1); lo = std::min(lo, s); hi = std::max(hi, s); }
        double h1 = 0, h2 = 0; int nh = n / 2; for (int i = 0; i < nh; ++i) h1 += vp[i]; h1 /= nh; for (int i = nh; i < n; ++i) h2 += vp[i]; h2 /= (n - nh);
        double minv = *std::min_element(vp.begin(), vp.end()), maxv = *std::max_element(vp.begin(), vp.end());
        std::printf("[Decision 1] R = %.0f km: v_pred,i mean %.3f m/s, sd over rows %.3f, min %.3f, max %.3f ; leave-one-out range %.3f to %.3f ; first-half %.3f, second-half %.3f\n", R, m, sd, minv, maxv, lo, hi, h1, h2);
        if (pass == 1) {
            double sR = m * sRdir / Rdir, sEp = std::sqrt(sR * sR + sd * sd);
            struct Cmp { const char* nm; double v, s; } cs[2] = {{"A published 638 +- 6", 638.0, 6.0}, {"B table A.2 mean v_fit_3D_n", mB, seB}};
            for (auto& c : cs) { double d = std::fabs(m - c.v), thP = 2 * std::sqrt(sR * sR + c.s * c.s), thE = 2 * std::sqrt(sEp * sEp + c.s * c.s);
                std::printf("     vs %-30s v_obs = %.2f +- %.2f : difference %+.3f m/s ; primary sigma_pred %.3f -> threshold %.3f -> %s ; epoch sigma_pred %.3f -> threshold %.3f -> %s ; Q = v_obs/v_pred = %.5f +- %.5f\n", c.nm, c.v, c.s, c.v - m, sR, thP, d > thP ? "EXCLUDED" : "COMPATIBLE", sEp, thE, d > thE ? "EXCLUDED" : "COMPATIBLE", c.v / m, c.s / m); }
            std::printf("     vs (C) table A.1 mean v_core_obs %.2f +- %.2f : difference %+.2f m/s : no decision (convective shift unmodelled); UNADJUDICATED\n", mC, seC, mC - m);
            double vk0 = C * (k0 * 1000.0) * (1.0 / (Rdir * 1000.0) - 1.0 / (aReg * 1000.0)); std::printf("     exploratory invariant koppa = A/2 = %.6f km with r = a: v = %.3f m/s\n\n", k0, vk0);
        }
    }

    // ---- Decision 3
    { const double zbar = kmean * 1000.0, R = Rnom * 1000.0, r1 = AUkm * 1000.0, r2 = AUkm * 1000.0; std::printf("[Decision 3] straight path r1 = r2 = 1 AU on opposite sides, koppa = %.6f km\n", kmean);
      for (double fac : {2.0, 5.0, 20.0}) { double b = fac * R; double s1 = std::sqrt(r1 * r1 - b * b), s2 = std::sqrt(r2 * r2 - b * b), p1 = std::atan(s1 / b), p2 = std::atan(s2 / b);
          auto f = [&](double ph) { double rr = b / std::cos(ph), z = zbar / rr; return (z * (2.0 - z) / ((1.0 - z) * (1.0 - z))) / C * (b / (std::cos(ph) * std::cos(ph))); };
          double I2000 = simpson(f, -p1, p2, 2000), I4000 = simpson(f, -p1, p2, 4000); double lead = depth_closure::shapiro_delay(zbar, r1, r2, b), second = 3.0 * zbar * zbar / C * (p1 + p2) / b;
          std::printf("     b = %2.0f R: exact (N=4000) %.6e s ; N=2000 vs 4000 relative %.2e ; shapiro_delay (leading order) %.6e s ; exact/leading - 1 = %+.3e ; second-order term %.3e s (relative to exact %.3e) ; round trip exact %.4f us\n", fac, I4000, std::fabs(I2000 / I4000 - 1), lead, I4000 / lead - 1, second, second / I4000, 2e6 * I4000); } }
    std::printf("\n[Decision 4] not run: PENDING (Cassini SCE1 ODF/TDF product is local; decoding and timing belong to the GOM_DAT chain)\n");
    return 0;
}
