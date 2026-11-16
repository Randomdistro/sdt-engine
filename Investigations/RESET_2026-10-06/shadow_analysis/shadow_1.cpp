// Shadow analysis of the paste-math evaluation (2026-10-07) and the algebra demos (2026-10-08).
// Pre-registration: ../SHADOW_ANALYSIS_2026-10-08_PRE_REGISTRATION.md (with its dated amendment).
// Engine constants from sdt::laws. External values carry [MEASURED-INPUT, source]; G and GM_Sun enter S5 only,
// to decompose the demo's comparison, never as inputs to an SDT chain.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi;
static const double c = M::c;
static double gam(double b) { return 1.0 / std::sqrt(1 - b * b); }
// F/(u sigma) for a cross-section sigma moving at beta through isotropic radiation (midpoint rule in mu)
static double drag(double b) { int n = 400000; double s = 0, g = gam(b); for (int i = 0; i < n; ++i) { double mu = -1 + 2 * (i + 0.5) / n; s += mu * std::pow(g * (1 - b * mu), -4); } return -0.5 * s * 2.0 / n; }
// c-closure with the solar surface speed rebuilt from Earth's orbital speed: v_surf(R) = v_E sqrt(AU/R)
static double c_closure(double R, double vE) { return bridge::k_from_precession(R, bridge::a_Mercury, bridge::e_Mercury, bridge::delta_phi_Mercury) * vE * std::sqrt(M::AU / R); }

int main() {
    std::printf("Shadow analysis instrument (2026-10-08)\n=======================================\n\n");
    int bad = 0;
    // ---- validations
    { double b = 0.3, num = drag(b), an = -4.0 / 3 * gam(b) * gam(b) * b; bool ok = std::fabs(num / an - 1) < 1e-6;
      std::printf("[V1] drag integral at beta = 0.3: %.10f ; closed form -(4/3) gamma^2 beta = %.10f ; relative %.1e -> %s\n", num, an, num / an - 1, ok ? "met" : "NOT MET"); bad += !ok; }
    { double A = 1.0, r = 2.0, h = 1e-5; auto u = [&](double x) { return A / (x * x); };
      double err = (u(r + h) - u(r - h)) / (2 * h), ett = u(r) / r, tr = err + 2 * ett; bool ok = std::fabs(err / (-2 * A / (r * r * r)) - 1) < 1e-6 && std::fabs(ett / (A / (r * r * r)) - 1) < 1e-12 && std::fabs(tr) < 1e-9;
      std::printf("[V2] dilatation centre A/r^2 at r = 2: e_rr = %.10f (-2A/r^3 = %.10f), e_thth = %.10f (A/r^3 = %.10f), trace %.1e -> %s\n", err, -2 * A / (r * r * r), ett, A / (r * r * r), tr, ok ? "met" : "NOT MET"); bad += !ok; }
    const double vE = bridge::v_surface_Sun * std::sqrt(M::R_Sun / M::AU);
    { double eng = bridge::k_Sun_from_precession * bridge::v_surface_Sun, red = vE * std::sqrt(6 * PI * M::AU / (bridge::delta_phi_Mercury * bridge::a_Mercury * (1 - bridge::e_Mercury * bridge::e_Mercury))); bool ok = std::fabs(eng / red - 1) < 1e-12;
      std::printf("[V3] engine c_from_closure = %.6f m/s ; reduced form v_E sqrt(6 pi AU/(dphi a (1-e^2))) = %.6f m/s ; relative %.1e -> %s\n\n", eng, red, eng / red - 1, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET: no checks run\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");

    // ---- S1 (E1): R_Sun cancels; the length scale of the closure is AU (and a_Mercury)
    { double c0 = c_closure(M::R_Sun, vE), cp = c_closure(1.1 * M::R_Sun, vE), cm = c_closure(0.9 * M::R_Sun, vE), d = std::max(std::fabs(cp / c0 - 1), std::fabs(cm / c0 - 1));
      double tauAU = M::AU / c, ca = c_closure(M::R_Sun, vE * 1.001) / c0; // v_E carries AU/yr
      std::printf("[S1] c_closure at R_Sun x 1.0, 1.1, 0.9: %.6f, %.6f, %.6f m/s ; worst change %.1e -> %s\n", c0, cp, cm, d, d < 1e-12 ? "confirmed" : "rejected");
      std::printf("     AU light-time tau_AU = AU/c = %.6f s (AU in metres is a ranging light-time times c) ; scaling all orbital lengths by s scales c_closure by s^1 (v_E x 1.001 -> x %.6f)\n\n", tauAU, ca); }
    // ---- S2 (E2): C3's koppa ratio and C7's c ratio are one fact
    { double kM = bridge::koppa_Sun_from_precession, kE = bridge::v_surface_Sun * bridge::v_surface_Sun * M::R_Sun / (c * c), cr = bridge::c_from_closure / c, pr = std::pow(kM / kE, -0.5), d = std::fabs(cr / pr - 1);
      std::printf("[S2] koppa_Mercury = %.6f m ; koppa_Earth-orbit = %.6f m ; ratio - 1 = %.4e\n     c_closure/c - 1 = %.4e ; (koppa_M/koppa_E)^(-1/2) - 1 = %.4e ; difference %.1e -> %s\n\n", kM, kE, kM / kE - 1, cr - 1, pr - 1, d, d < 1e-12 ? "confirmed" : "rejected"); }
    // ---- S3 (E4): Sirius B, koppa = z R in solar units
    { const double kS = bridge::koppa_Sun_from_precession, dyn = 1.018, sdyn = 0.011;           // [MEASURED-INPUT, Bond et al. 2017b as quoted by Joyce et al. 2018]
      const double v18 = 80.65e3, sv18 = 0.77e3, R18 = 0.803e-2 * M::R_Sun, sR18 = 0.011e-2 * M::R_Sun; // [MEASURED-INPUT, Joyce et al. 2018, Table 3 and 3.1.7]
      const double v05 = 80.42e3, R_eval = 5.84e6;                                                 // Barstow et al. 2005 redshift; the radius used in the demos [B]
      auto ms = [&](double v, double R) { return (v / c) * R / kS; };
      double m18 = ms(v18, R18), rel = std::sqrt(std::pow(sv18 / v18, 2) + std::pow(sR18 / R18, 2)), s18 = m18 * rel, sc = std::sqrt(s18 * s18 + sdyn * sdyn), dev = (m18 - dyn) / sc;
      std::printf("[S3] Sirius B, koppa = (v_gr/c) R, in units of koppa_Sun_from_precession = %.4f m:\n", kS);
      std::printf("     Joyce 2018 pair (80.65 km/s, 0.00803 R_Sun): koppa = %.2f m -> %.4f +/- %.4f ; dynamical %.3f +/- %.3f ; deviation %.2f sigma -> %s\n", (v18 / c) * R18, m18, s18, dyn, sdyn, dev, std::fabs(dev) <= 1 ? "confirmed" : "rejected");
      std::printf("     evaluation's pair (80.42 km/s, 5.84e6 m = %.5f R_Sun): %.4f ; 2005 z with 2018 R: %.4f ; 2018 z with 5.84e6 m: %.4f\n", R_eval / M::R_Sun, ms(v05, R_eval), ms(v05, R18), ms(v18, R_eval));
      std::printf("     origin of the evaluation's +4%%: radius term %.4f, redshift term %.4f (multiplicative)\n\n", R_eval / R18, v05 / v18); }
    // ---- S4 (E5): the paste's rho/rho0 is 1 - e_thth of the incompressible field
    { const double R0 = 8.4e-16, Om = 4.0 / 3 * PI * R0 * R0 * R0; double worst = 0;
      for (double f : {1.0, 2.0, 10.0}) { double r = f * R0, paste = 1 - Om / (4 * PI * r * r * r), ett = (Om / (4 * PI * r * r)) / r; worst = std::max(worst, std::fabs(paste - (1 - ett))); std::printf("[S4] r = %4.0f R0: paste rho/rho0 = %.12f ; 1 - e_thth = %.12f ; radial 1 - e_rr = %.12f\n", f, paste, 1 - ett, 1 + 2 * ett); }
      std::printf("     worst difference %.1e -> %s\n\n", worst, worst < 1e-12 ? "confirmed" : "rejected"); }
    // ---- S5 (E8): decomposition of the demo's Sun census
    { const double G = 6.67430e-11, GMS = 1.32712440018e20, MS_demo = 1.989e30;                   // [MEASURED-INPUT, CODATA 2018 G; IAU 2015 GM_Sun; demo's mass]
      double kb = bridge::koppa_per_baryon, kGM = GMS / (c * c), Q = (kGM / kb) / ((GMS / G) / M::m_p), lam = M::hbar / (M::m_p * c), red = M::R_p / (4 * lam), d = std::fabs(Q / red - 1);
      double demo = (bridge::koppa_Sun_from_precession / kb) / (MS_demo / M::m_p);
      std::printf("[S5] Q = (koppa_GM/koppa_b)/(M_GM/m_p) = %.9f ; R_p/(4 hbar/(m_p c)) = %.9f ; relative %.1e -> %s\n", Q, red, Q / red - 1, d < 1e-12 ? "confirmed" : "rejected");
      std::printf("     l_P^2 against hbar G/c^3: relative %.2e (stored l_P precision)\n", M::l_P * M::l_P / (M::hbar * G / (c * c * c)) - 1);
      std::printf("     demo ratio %.6f = Q (%.6f) x koppa_M/koppa_GM (%.6f) x (GM/G)/1.989e30 (%.6f) : product %.6f\n\n", demo, Q, bridge::koppa_Sun_from_precession / kGM, (GMS / G) / MS_demo, Q * (bridge::koppa_Sun_from_precession / kGM) * ((GMS / G) / MS_demo)); }
    // ---- S6 (E9): Earth's CMB drag at the CMB-frame speed
    { const double vC = 370e3, vO = 29.78e3, RE = bridge::R_Earth, sig = PI * RE * RE;               // [MEASURED-INPUT, CMB dipole speed ~370 km/s]
      double FC = -drag(vC / c) * law_I::u_CMB * sig, FO = -drag(vO / c) * law_I::u_CMB * sig, r = FC / FO;
      std::printf("[S6] Earth CMB drag at 370 km/s: %.4e N ; at 29.78 km/s: %.4e N ; ratio %.6f (370/29.78 = %.6f) -> %s\n\n", FC, FO, r, vC / vO, std::fabs(r / (vC / vO) - 1) < 1e-6 ? "confirmed" : "rejected"); }
    // ---- S7 (item 5): the demo's drag ratios are gamma^2
    { double worst = 0; for (double b : {1e-3, 1e-2, 0.1, 0.5}) { double r = drag(b) / (-4.0 / 3 * b); worst = std::max(worst, std::fabs(r / (gam(b) * gam(b)) - 1)); std::printf("[S7] beta = %-5g: F/(-(4/3) u sigma beta) = %.8f ; gamma^2 = %.8f\n", b, r, gam(b) * gam(b)); }
      std::printf("     worst relative %.1e -> %s\n\n", worst, worst < 1e-5 ? "confirmed" : "rejected"); }
    // ---- S8 (item 11): lattice group delay for GRB 090510, bound without a cosmological model
    { const double E = 30.53e9 * 1.602176634e-19, z = 0.903, bound = 0.859;                       // [MEASURED-INPUT, Fermi LAT, arXiv:1008.2913]
      double k = E / (M::hbar * c), kl = k * M::l_P, dt = std::pow(1 + z, 2) * kl * kl * M::R_CMB / (8 * c);
      std::printf("[S8] 30.53 GeV: k l_P = %.4e ; v_g = c cos(k l/2): 1 - v_g/c = %.4e ; Delta t <= (1+z)^2 (k l)^2 R_CMB/(8c) = %.3e s ; bound %.3f s -> %s ; spacing that would reach the bound: %.3e l_P\n\n", kl, kl * kl / 8, dt, bound, dt < bound ? "confirmed" : "rejected", std::sqrt(bound / dt)); }
    // ---- S9 (item 4): solar gravitational redshift observed at Earth
    { const double meas = 638.0, smeas = 6.0;                                                     // [MEASURED-INPUT, Gonzalez Hernandez et al. 2020, A&A 643 A146]
      double kS = bridge::koppa_Sun_from_precession, pred = c * kS * (1 / M::R_Sun - 1 / M::AU) - c * bridge::koppa_Earth / bridge::R_Earth, dev = (meas - pred) / smeas;
      std::printf("[S9] predicted c z at Earth = c koppa (1/R_Sun - 1/AU) - c koppa_Earth/R_Earth = %.3f - %.3f - %.3f = %.3f m/s ; measured %.0f +/- %.0f ; deviation %.2f sigma -> %s\n", c * kS / M::R_Sun, c * kS / M::AU, c * bridge::koppa_Earth / bridge::R_Earth, pred, meas, smeas, dev, std::fabs(dev) <= 2 ? "confirmed" : "rejected");
      std::printf("     koppa_Sun from the spectrum alone, koppa = z R_Sun with the Earth terms restored: %.2f +/- %.2f m (precession route %.4f m)\n", (meas + c * kS / M::AU + c * bridge::koppa_Earth / bridge::R_Earth) / c * M::R_Sun, smeas / c * M::R_Sun, kS); }
    return 0;
}
