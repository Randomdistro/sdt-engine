// RTM01 blank-slate run 1 (2026-10-11). Registration: RTM01_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Thrust ledger laws (hover, straight-pass lateral bill, per-metre toll), powered-ascent toll table, propulsion pricing, decomposition by numerical integration, Gate M against the measured solar deflection (gamma).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

struct P { double K, b, v; int mode; };      // K = c^2 koppa ; mode 0: slow impulse integrand ; mode 1: light index-gradient integrand (koppa in K via c)
static double simpson(double (*f)(double, void*), void* p, double a, double b, int n) { double h = (b - a) / n, s = f(a, p) + f(b, p); for (int i = 1; i < n; ++i) s += f(a + i * h, p) * (i % 2 ? 4.0 : 2.0); return s * h / 3.0; }
static double slowInt(double u, void* q) { P* p = (P*)q; double l = p->b * std::sinh(u), r2 = p->b * p->b + l * l; return p->K * p->b / (r2 * std::sqrt(r2)) * (p->b * std::cosh(u)); }              // a_perp dl
static double lightInt(double u, void* q) { P* p = (P*)q; double l = p->b * std::sinh(u), r = std::sqrt(p->b * p->b + l * l), kop = p->K, z = kop / r; double nprime = 2.0 * kop / (r * r * std::pow(1.0 - z, 3)); return nprime * (p->b / r) * (p->b * std::cosh(u)); }   // dn/db dl
static double weakInt(double u, void* q) { P* p = (P*)q; double l = p->b * std::sinh(u), r = std::sqrt(p->b * p->b + l * l); return 2.0 * p->K * (p->b / (r * r * r)) * (p->b * std::cosh(u)); }       // n = 1 + 2 koppa/r

int main() {
    std::printf("RTM01 blank-slate run 1 (registered in RTM01_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    const double c = M::c, kE = bridge::koppa_Earth, kS = bridge::koppa_Sun, RE = bridge::R_Earth, RS = M::R_Sun; int fails = 0;
    const double GMsun = 1.32712440e20, kGM = GMsun / (c * c), kCal = 1476.3512, kHold = 1476.8693, sigK = 4e-4, gam = 0.9998, sigGam = 0.0003, vex = 4500.0;
    // ---- validations
    { P p{1.0, 3.7, 1}; double X = 250.0, ua = std::asinh(X / 3.7); double num = simpson([](double u, void* q) { P* pp = (P*)q; double l = pp->b * std::sinh(u), r2 = pp->b * pp->b + l * l; return pp->b * std::cosh(u) / (r2 * std::sqrt(r2)); }, &p, -ua, ua, 4000), an = 2 * X / (3.7 * 3.7 * std::sqrt(3.7 * 3.7 + X * X)); double e = std::fabs(num / an - 1); bool ok = e < 1e-10; std::printf("[V1] Simpson (l = b sinh u) against 2L/(b^2 sqrt(b^2 + L^2)): relative %.2e -> %s\n", e, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { double b = 1.0e7, K = 1.0e12; double worst = 0; for (double l : {-3e7, -1e7, -2e6, 0.0, 2e6, 7.07e6, 1e7, 3e7}) { auto z = [&](double ll) { return (K / c / c) / std::sqrt(b * b + ll * ll); }; double h = 1.0; double num = (z(l + h) - z(l - h)) / (2 * h), an = -(K / c / c) * l / std::pow(b * b + l * l, 1.5); if (std::fabs(an) > 0) worst = std::max(worst, std::fabs(num / an - 1)); } bool ok = worst < 1e-8; std::printf("[V2] numerical toll dz/dl against the analytic -koppa l / r^3 : worst relative %.2e -> %s\n", worst, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { // V3: light integral for the weak index n = 1 + 2 koppa/r gives 4 koppa/b (X/b large)
      P p{kS, RS, 1}; double ua = std::asinh(1e4), num = simpson(weakInt, &p, -ua, ua, 20000), an = 4 * kS / RS; double e = std::fabs(num / an - 1); bool ok = e < 1e-6; std::printf("[V3] weak-index light integral against 4 koppa/b (Sun limb, X/b = 1e4): relative %.2e -> %s\n\n", e, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    // ---- P1
    { const char* ch[4] = {"hover a(r) = c^2 xi / r^2", "pass bill dv_perp = 2 c^2 xi / (b v)", "toll dz/dl = - xi l / r^3 ; z = xi / r", "light: theta = 4 xi / b"}; int pis = 0; for (auto s : ch) { std::string t = s; size_t p = 0; while ((p = t.find("pi", p)) != std::string::npos) { ++pis; p += 2; } }
      std::printf("[P1] ledger laws: %s ; %s ; %s ; %s ; occurrences of pi: %d -> %s (F3)\n", ch[0], ch[1], ch[2], ch[3], pis, pis == 0 ? "zero" : "PRESENT"); }
    { double aE = c * c * kE / (RE * RE), aS = c * c * kS / (RS * RS), gE = bridge::g_surface(bridge::v_Earth, RE), gS = bridge::g_surface(c / bridge::k_Sun, RS), gIAU = GMsun / (RS * RS);
      std::printf("[P1] hover: Earth surface %.5f m/s^2 (g_surface identity %.5f, difference %.1e) ; Sun photosphere %.4f m/s^2 (g_surface identity %.4f, difference %.1e: IDENTITY)\n     independent comparison (shared form): GM_sun/R_sun^2 = %.4f m/s^2 : hover/that - 1 = %+.4f%% (gate 0.1%%: %s)\n", aE, gE, aE / gE - 1, aS, gS, aS / gS - 1, gIAU, (aS / gIAU - 1) * 100, std::fabs(aS / gIAU - 1) < 1e-3 ? "met" : "NOT MET"); }
    { // toll maximum location and size
      double b = 1.0, best = 0, lb = 0; for (int i = 0; i <= 200000; ++i) { double l = 3.0 * i / 200000.0; double v = l / std::pow(b * b + l * l, 1.5); if (v > best) { best = v; lb = l; } } double an = 2.0 / (3.0 * std::sqrt(3.0));
      std::printf("[P1] toll |dz/dl| along a chord peaks at l = %.5f b (b/sqrt2 = %.5f) with size %.6f xi/b^2 (closed form 2/(3 sqrt3) = %.6f): relative %.1e\n", lb, 1 / std::sqrt(2.0), best, an, std::fabs(best / an - 1));
      std::printf("     toll at the Sun limb chord: peak |dz/dl| = %.3e per metre ; Earth surface chord: %.3e per metre\n\n", an * kS / (RS * RS), an * kE / (RE * RE)); }
    // ---- P2
    { std::printf("[P2] powered-ascent toll table (Earth): r, z = xi/r, hover a, circular speed c sqrt(z), identity v^2/c^2 / z - 1\n"); double w = 0; for (int i = 0; i <= 4; ++i) { double r = RE + 50e3 * i, z = kE / r, a = c * c * kE / (r * r), vc = c * std::sqrt(z), id = (vc * vc / (c * c)) / z - 1; w = std::max(w, std::fabs(id)); std::printf("     r = %.0f m : z = %.6e ; a = %.5f m/s^2 ; v_circ = %.2f m/s ; identity %.1e\n", r, z, a, vc, id); }
      double rI = RE + 408e3, vI = c * std::sqrt(kE / rI); std::printf("     identity worst %.1e (%s) ; descriptive: circular speed at the ISS radius (6371 + 408 km) = %.1f m/s against the approximate observed 7660 m/s (%+.2f%%)\n\n", w, w < 1e-12 ? "met" : "NOT MET", vI, (vI / 7660.0 - 1) * 100); }
    // ---- P3
    { double a = c * c * kE / (RE * RE), t = 86400.0, ex = a * t / vex; std::printf("[P3] hover price at the Earth's surface: a = %.5f m/s^2 held for one day with v_ex = 4.5 km/s : exponent a t / v_ex = %.2f ; mass ratio exp(.) = 10^%.2f (astronomical: the curve is cheap, the line is not). Per second: exponent %.3e ; per metre of refusing the curve (dz/dl at the surface): %.3e m^-1\n\n", a, ex, ex / std::log(10.0), a / vex, kE / (RE * RE)); }
    { std::printf("[P3] straight-pass lateral bill dv_perp = 2 c^2 xi/(b v) [m/s]; '*' = outside the straight-line regime (dv_perp/v > 0.1)\n  Earth: rows b = R, 2R, 10R ; columns v = 1e4, 1e5, 1e6, 1e7 m/s\n"); for (double fb : {1.0, 2.0, 10.0}) { std::printf("   b = %4.0f R :", fb); for (double v : {1e4, 1e5, 1e6, 1e7}) { double d = 2 * c * c * kE / (fb * RE * v); std::printf(" %11.4e%s", d, d / v > 0.1 ? "*" : " "); } std::printf("\n"); }
      std::printf("  Sun: rows b = R, 2R, 10R ; columns v = 1e6, 1e7, 3e7, 1e8 m/s\n"); for (double fb : {1.0, 2.0, 10.0}) { std::printf("   b = %4.0f R :", fb); for (double v : {1e6, 1e7, 3e7, 1e8}) { double d = 2 * c * c * kS / (fb * RS * v); std::printf(" %11.4e%s", d, d / v > 0.1 ? "*" : " "); } std::printf("\n"); } std::printf("\n"); }
    // ---- P4
    { std::printf("[P4] decomposition by numerical integration: v, b_v (theta_slow = 1e-3), theta_slow (impulse integral / v^2), theta_light (exact-index gradient integral), ratio, c^2/(2v^2), deviation\n"); double worst = 0;
      for (double vkm : {10.0, 30.0, 100.0, 300.0}) { double v = vkm * 1e3, bv = 2 * c * c * kS / (v * v * 1e-3); double ua = std::asinh(1e4); P ps{c * c * kS, bv, v, 0}, pl{kS, bv, v, 1};
          double ths = simpson(slowInt, &ps, -ua, ua, 20000) / (v * v), thl = simpson(lightInt, &pl, -ua, ua, 20000), ratio = ths / thl, law = c * c / (2 * v * v), dev = ratio / law - 1; worst = std::max(worst, std::fabs(dev));
          std::printf("     v = %5.0f km/s : b_v = %.4e m (%.3e AU) ; theta_slow = %.6e ; theta_light = %.6e ; ratio %.6e ; c^2/2v^2 = %.6e ; deviation %+.2e\n", vkm, bv, bv / M::AU, ths, thl, ratio, law, dev); }
      std::printf("     F4 (deviation < 1e-3 in the slow limit): worst %.2e -> %s\n", worst, worst < 1e-3 ? "met" : "NOT MET");
      P pl{kS, RS, 1, 1}; double ua = std::asinh(1e4), thl = simpson(lightInt, &pl, -ua, ua, 40000), th4 = 4 * kS / RS; const double asec = 206264.806247;
      std::printf("     light at the Sun limb: exact-index integral %.6e rad = %.5f arcsec ; 4 xi/R = %.6e rad = %.5f arcsec ; ratio %.8f\n\n", thl, thl * asec, th4, th4 * asec, thl / th4); }
    // ---- Gate M
    { double meas = (1 + gam) / 2, sMeas = sigGam / 2, sc = std::sqrt(sMeas * sMeas + sigK * sigK); std::printf("[Gate M] measured solar deflection (shared-form normalisation by GM_sun/c^2 = %.4f m): (1 + gamma)/2 = %.5f +- %.5f (VLBA, fitted PPN parameter)\n", kGM, meas, sMeas);
      struct R { const char* nm; double k; } rs[3] = {{"koppa_cal (2025 invariant, GOM26)", kCal}, {"koppa_hold (2024, GOM26)", kHold}, {"bridge::koppa_Sun", kS}};
      for (auto& r : rs) { double R = r.k / kGM, d = R - meas; std::printf("     %-36s R_defl = koppa/(GM/c^2) = %.6f ; difference from (1+gamma)/2 = %+.2e ; combined sigma %.2e ; %.2f sigma ; gate 2 sigma: %s\n", r.nm, R, d, sc, std::fabs(d) / sc, std::fabs(d) < 2 * sc ? "met" : "NOT MET"); }
      std::printf("     Cassini (1 + gamma)/2 = 1.00001 +- 0.00001: orbit-invariant systematic %.0e is %.0f times its precision -> not decidable with this koppa\n", sigK, sigK / 1e-5);
      std::printf("     predicted limb deflection with koppa_cal: %.5f arcsec ; with the GM_sun/c^2 normalisation (GR value for these constants): %.5f arcsec\n", 4 * kCal / RS * 206264.806247, 4 * kGM / RS * 206264.806247); }
    return 0;
}
