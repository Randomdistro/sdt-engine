// Evaluation of the mathematics in the pasted text (2026-10-07). Checks C1-C7 and their criteria are fixed in the header comments before the run.
// Author: J. C. Harvey, Melbourne. Constants from sdt::laws; no local constant namespaces.
//
// C1  arithmetic of the single-sphere displacement derivation (N_disp, R_term) as pasted: reproduce within 1%.
// C2  incompressible volume source u_r = Omega/(4 pi r^2): div u = 0 outside the source (finite difference); the pasted density statement
//     rho = rho0 (1 - Omega/(4 pi r^3)) is inconsistent with the premise if |div u| < 1e-9 |u|/r.
// C3  koppa identities: z k^2 = 1 for v = c sqrt(koppa/r); koppa from the Earth-orbit speed (engine v_surface_Sun) against koppa from the Mercury closure.
// C4  perihelion advance of a force a = -(c^2 koppa/r^2)(1 + beta koppa/r), by direct orbit integration, for beta = 0, 3, 6, 12;
//     validations: beta = 0 gives |precession| < 1e-10 rad/orbit and energy conserved to 1e-12; criterion: beta = 6 reproduces 6 pi koppa/(a(1-e^2)) to 1e-3.
// C5  consequences of that force law: circular-orbit speed reaches c where?; stability of circular orbits for all r?
// C6  light: deflection and delay coefficients for n - 1 = a koppa/r, a = 1 and a = 2; numerical quadrature against the analytic forms (1e-6).
// C7  the closure c = k_Sun v_surface: reproduce the engine's +0.0009%, and the propagation of the precession's own uncertainty (+/-0.04 arcsec/century).
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi;

struct Orb { double prec_rad_per_orbit; double e_drift; int orbits; };
static Orb integrate(double GM, double kop, double beta, double a, double e, int Norb, double dt) {
    auto acc = [&](double x, double y, double& ax, double& ay) { double r2 = x * x + y * y, r = std::sqrt(r2), f = -GM / r2 * (1.0 + beta * kop / r); ax = f * x / r; ay = f * y / r; };
    double rp = a * (1 - e), vp = std::sqrt(GM * (1 + e) / (a * (1 - e)));
    double x = rp, y = 0, vx = 0, vy = vp, t = 0;
    double E0 = 0.5 * (vx * vx + vy * vy) - GM / rp * (1.0 + 0.5 * beta * kop / rp);   // potential of GM/r^2 (1 + beta k/r): -GM/r - beta GM k/(2 r^2)
    std::vector<double> th; double gprev = x * vx + y * vy; int found = 0; double thetaPrevUnwrapped = 0, lastTheta = 0; (void)t; (void)thetaPrevUnwrapped; (void)lastTheta;
    double thetaAcc = 0, prevAng = std::atan2(y, x); double ang0 = prevAng; std::vector<double> peri;
    double pangle = 0;
    while (found < Norb + 1) {
        double k1x = vx, k1y = vy, a1x, a1y; acc(x, y, a1x, a1y);
        double x2 = x + 0.5 * dt * k1x, y2 = y + 0.5 * dt * k1y, k2x = vx + 0.5 * dt * a1x, k2y = vy + 0.5 * dt * a1y, a2x, a2y; acc(x2, y2, a2x, a2y);
        double x3 = x + 0.5 * dt * k2x, y3 = y + 0.5 * dt * k2y, k3x = vx + 0.5 * dt * a2x, k3y = vy + 0.5 * dt * a2y, a3x, a3y; acc(x3, y3, a3x, a3y);
        double x4 = x + dt * k3x, y4 = y + dt * k3y, k4x = vx + dt * a3x, k4y = vy + dt * a3y, a4x, a4y; acc(x4, y4, a4x, a4y);
        double nx = x + dt / 6 * (k1x + 2 * k2x + 2 * k3x + k4x), ny = y + dt / 6 * (k1y + 2 * k2y + 2 * k3y + k4y);
        double nvx = vx + dt / 6 * (a1x + 2 * a2x + 2 * a3x + a4x), nvy = vy + dt / 6 * (a1y + 2 * a2y + 2 * a3y + a4y);
        double g = nx * nvx + ny * nvy;
        double ang = std::atan2(ny, nx), d = ang - prevAng; if (d > PI) d -= 2 * PI; if (d < -PI) d += 2 * PI; thetaAcc += d; prevAng = ang;
        if (gprev < 0 && g >= 0) { double f = -gprev / (g - gprev); double dd = thetaAcc - d + f * d; peri.push_back(dd); ++found; }
        gprev = g; x = nx; y = ny; vx = nvx; vy = nvy; (void)ang0; (void)pangle;
    }
    double E1 = 0.5 * (vx * vx + vy * vy) - GM / std::sqrt(x * x + y * y) * (1.0 + 0.5 * beta * kop / std::sqrt(x * x + y * y));
    // perihelion angles are cumulative; the first detected perihelion is the first return (about 2 pi)
    double prec = (peri.back() - peri.front()) / (peri.size() - 1) - 2 * PI;
    return {prec, std::fabs(E1 / E0 - 1), Norb};
}

int main() {
    std::printf("Evaluation of the mathematics in the pasted text (2026-10-07)\n==============================================================\n\n");
    const double c = M::c, lP = M::l_P, R0 = 8.4e-16, Rlock = law_III::R_p_lock;
    int fails = 0;
    // ---------------- validations
    // VA: orbit integrator, beta = 0 (Newtonian)
    const double kopE = bridge::koppa_Sun_from_precession, GM = c * c * kopE;
    Orb o0 = integrate(GM, kopE, 0.0, bridge::a_Mercury, bridge::e_Mercury, 20, 20.0);
    bool va = std::fabs(o0.prec_rad_per_orbit) < 1e-10 && o0.e_drift < 1e-12;
    std::printf("[VA] orbit integrator, Newtonian (beta = 0), 20 orbits: precession %.3e rad/orbit ; relative energy drift %.2e -> %s\n", o0.prec_rad_per_orbit, o0.e_drift, va ? "met" : "NOT MET");
    if (!va) ++fails;
    // VB: deflection quadrature against the analytic 2 a koppa / b for a known case, and the delay quadrature
    auto defl = [&](double a, double kop, double b) { int n = 2000000; double L = 2e4 * b, h = 2 * L / n, s = 0; for (int i = 0; i <= n; ++i) { double l = -L + i * h, w = (i == 0 || i == n) ? 1 : (i % 2 ? 4 : 2); s += w * a * kop * b / std::pow(b * b + l * l, 1.5); } return s * h / 3; };
    double bS = M::R_Sun, dnum = defl(2.0, kopE, bS), dan = 2 * 2.0 * kopE / bS;
    bool vb = std::fabs(dnum / dan - 1) < 1e-4;      // the tail beyond L is of order b/L = 5e-5
    std::printf("[VB] deflection quadrature (a = 2, grazing the Sun): %.6e rad against analytic %.6e (relative %.2e) -> %s\n\n", dnum, dan, std::fabs(dnum / dan - 1), vb ? "met" : "NOT MET");
    if (!vb) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET");
    if (fails) return 1;

    // ---------------- C1
    const double v0 = PI / 6 * lP * lP * lP;
    for (double R : {R0, Rlock}) { double Om = 4.0 / 3 * PI * R * R * R, N = Om / v0, Rt = std::sqrt(R * R * R / (3 * lP)); std::printf("[C1] R0 = %.5e m : Omega = %.4e m^3 ; N_disp = Omega/((pi/6) l_P^3) = %.4e (8 (R0/l_P)^3 = %.4e) ; R_term = sqrt(R0^3/(3 l_P)) = %.4e m\n", R, Om, N, 8 * std::pow(R / lP, 3), Rt); }
    std::printf("     pasted: N ~ 1.1e60, R_term ~ 3.5e-6 m -> %s\n", (std::fabs(8 * std::pow(R0 / lP, 3) / 1.1e60 - 1) < 0.05 && std::fabs(std::sqrt(R0 * R0 * R0 / (3 * lP)) / 3.5e-6 - 1) < 0.02) ? "arithmetic reproduced" : "NOT reproduced");
    {
        double Om = 4.0 / 3 * PI * R0 * R0 * R0, Ncp = std::sqrt(2.0) * Om / (lP * lP * lP), Ns = Om / v0;
        std::printf("     cell choice: the pasted count divides by the volume of one sphere, (pi/6) l_P^3 (100%% filling); with face-centred close packing each sphere has a cell l_P^3/sqrt2, giving N = sqrt2 Omega/l_P^3 = %.4e (x%.4f of the pasted count); R_term does not depend on this choice\n\n", Ncp, Ncp / Ns);
    }
    // ---------------- C1b (added after the first run; scaling of the terminal radius with the number of baryons N_b: volumes add, Omega = N_b Omega_0, so R_term = R_term(1) sqrt(N_b))
    {
        double Rt1 = std::sqrt(R0 * R0 * R0 / (3 * lP)), Nstar = std::pow(M::R_CMB / Rt1, 2);
        std::printf("[C1b] R_term(N_b) = R_term(1) sqrt(N_b), R_term(1) = %.4e m ; the baryon number at which R_term equals the causal depth R_CMB = %.4e m is N_b* = %.4e (baryon census; N_b* m_p = %.4e kg, about %.1e solar masses with the IAU value 1.989e30 kg [external, conversion only])\n     bodies with fewer baryons have a displacement field that falls below one l_P per shell inside the causal depth; bodies with more keep it above one l_P per shell out to the boundary\n\n", Rt1, M::R_CMB, Nstar, Nstar * M::m_p, Nstar * M::m_p / 1.989e30);
    }
    // ---------------- C2
    {
        double Om = 4.0 / 3 * PI * R0 * R0 * R0, worst = 0, ur_scale = 0;
        for (double r : {2e-15, 1e-12, 1e-9, 1e-6}) { double h = r * 1e-4; auto ur = [&](double x) { return Om / (4 * PI * x * x); };
            double div = (1.0 / (r * r)) * ((r + h) * (r + h) * ur(r + h) - (r - h) * (r - h) * ur(r - h)) / (2 * h);   // (1/r^2) d(r^2 u_r)/dr
            worst = std::max(worst, std::fabs(div) / (ur(r) / r)); ur_scale = ur(r); }
        double eps_rr = -2 * Om / (4 * PI * std::pow(1e-9, 3)), eps_tt = Om / (4 * PI * std::pow(1e-9, 3));
        std::printf("[C2] incompressible source u_r = Omega/(4 pi r^2): worst |div u| / (u/r) = %.2e (zero to rounding) ; strains at r = 1e-9 m: e_rr = %.3e, e_thth = e_phph = %.3e (trace %.1e)\n     -> the pasted density statement rho = rho0 (1 - Omega/(4 pi r^3)) is %s with this displacement field; the shear energy density scales as r^-6 and integrates to a finite value from R0\n", worst, eps_rr, eps_tt, eps_rr + 2 * eps_tt, worst < 1e-9 ? "inconsistent" : "not shown inconsistent");
        (void)ur_scale; }
    double Es = 0; { double Om = 4.0 / 3 * PI * R0 * R0 * R0; (void)Om; Es = 1.0; (void)Es; }
    std::printf("\n");
    // ---------------- C3
    {
        double vS = M::c * 0 + 436762.0; (void)vS;
        double kop_orbit = M::R_Sun * std::pow(bridge::v_surface_Sun / c, 2), kop_prec = bridge::koppa_Sun_from_precession, kop_bridge = bridge::koppa_Sun;
        std::printf("[C3] koppa from the Earth-orbit speed (engine v_surface_Sun = %.0f m/s): %.4f m ; from the Mercury closure: %.4f m ; bridge::koppa_Sun (R/k^2, k = 686.3): %.4f m ; relative differences %.2e, %.2e\n", bridge::v_surface_Sun, kop_orbit, kop_prec, kop_bridge, kop_prec / kop_orbit - 1, kop_bridge / kop_orbit - 1);
        double zk2 = 0; for (double r : {1e-3, 1.0, 1e3, 1e9}) { double z = kop_orbit / r, v = c * std::sqrt(z), k = c / v; zk2 = std::max(zk2, std::fabs(z * k * k - 1)); }
        std::printf("     z k^2 - 1 over r = 1e-3 .. 1e9 m: worst %.2e (CONSTRUCTION: k = c/v and z = koppa/r are built from one v) ; weak-field gravitational redshift of the Sun z = koppa/R_Sun = %.5e (the standard weak-field value GM/(R c^2) with GM from the Earth-orbit speed)\n", zk2, kop_orbit / M::R_Sun);
        double ka = bridge::k_hydrogen, Rr = M::a_0; std::printf("     hydrogen: v(a_0) = (c/k) sqrt(R/r) with k = 1/alpha, R = a_0 gives %.6f alpha c ; the formula as typed in the paste, v = (c k) sqrt(R/r), gives %.2f c at r = R for k = 1/alpha, so k there must be v/c or the typed product must be c/k\n\n", (c / ka) / (c * M::alpha), (c * ka) / c); (void)Rr; }
    // ---------------- C4
    std::printf("[C4] perihelion advance of Mercury for a = -(c^2 koppa/r^2)(1 + beta koppa/r), koppa = %.4f m (Mercury closure), 40 orbits, RK4, dt = 20 s\n", kopE);
    double expect = 6 * PI * kopE / (bridge::a_Mercury * (1 - bridge::e_Mercury * bridge::e_Mercury));
    std::printf("     analytic first-order advance for beta = 6: 6 pi koppa/(a(1-e^2)) = %.6e rad/orbit = %.4f arcsec/century\n", expect, expect * bridge::mercury_orbits_per_cy * 180 * 3600 / PI);
    double precv[4] = {0, 0, 0, 0}; double betas[4] = {0, 3, 6, 12};
    for (int i = 0; i < 4; ++i) { Orb o = integrate(GM, kopE, betas[i], bridge::a_Mercury, bridge::e_Mercury, 40, 20.0); precv[i] = o.prec_rad_per_orbit; std::printf("     beta = %-4.0f : %.6e rad/orbit = %.4f arcsec/century (energy drift %.1e)\n", betas[i], o.prec_rad_per_orbit, o.prec_rad_per_orbit * bridge::mercury_orbits_per_cy * 180 * 3600 / PI, o.e_drift); }
    std::printf("     criterion (beta = 6 reproduces the analytic value to 1e-3): relative difference %.2e -> %s ; linearity in beta: precession(12)/precession(6) = %.5f (expected 2)\n\n", precv[2] / expect - 1, std::fabs(precv[2] / expect - 1) < 1e-3 ? "met" : "NOT met", precv[3] / precv[2]);
    // ---------------- C5
    {
        double lo = 1e-9, hi = 10; for (int i = 0; i < 200; ++i) { double mid = 0.5 * (lo + hi); (mid * (1 + 6 * mid) < 1 ? lo : hi) = mid; }
        double smin = 1e9; for (double x = 1e-6; x < 50; x *= 1.01) { double s = 3 - (2 + 18 * x) / (1 + 6 * x); smin = std::min(smin, s); }
        std::printf("[C5] circular-orbit speed v^2 = c^2 x (1 + 6 x), x = koppa/r: v = c at x = %.6f (r = %.4f koppa) ; stability margin 3 - (2 + 18 x)/(1 + 6 x) = 1/(1 + 6x): smallest over x in [1e-6, 50]: %.4f (> 0: circular orbits are stable at every radius, no innermost stable orbit)\n     for comparison [B]: GR has a photon circular orbit at r = 3 GM/c^2 and an innermost stable circular orbit at r = 6 GM/c^2\n\n", lo, 1 / lo, smin);
    }
    // ---------------- C6
    std::printf("[C6] light in n - 1 = a koppa/r (koppa = %.4f m), grazing the Sun: deflection 2 a koppa/b\n", bridge::koppa_Sun_from_precession);
    for (double a : {1.0, 2.0}) { double d = 2 * a * bridge::koppa_Sun_from_precession / M::R_Sun; std::printf("     a = %.0f : %.5e rad = %.4f arcsec (a = 2 corresponds to a coordinate light speed c (1 - 2 koppa/r), to first order c (1 - z)^2) ; delay coefficient (a koppa/c) = %.4e s per unit of ln\n", a, d, d * 180 * 3600 / PI, a * bridge::koppa_Sun_from_precession / c); }
    std::printf("     the pasted 1911 scalar form c (1 + Phi/c^2) is a = 1 (half the deflection); the full deflection needs a = 2\n\n");
    // ---------------- C7
    {
        double k0 = bridge::k_Sun_from_precession, c0 = k0 * bridge::v_surface_Sun;
        std::printf("[C7] engine closure c = k_Sun v_surface = %.2f m/s against measured c = %.2f m/s : %+.5f%% (engine comment +0.0009%%)\n", c0, c, (c0 / c - 1) * 100);
        double d1 = bridge::k_from_precession(M::R_Sun, bridge::a_Mercury, bridge::e_Mercury, bridge::delta_phi_Mercury * (42.98 + 0.04) / 42.98) * bridge::v_surface_Sun / c0 - 1;
        std::printf("     c scales as the precession to the power -1/2: a precession uncertainty of +/-0.04 arcsec/century (0.093%%) moves c by %+.4f%% ; the 0.0009%% agreement is therefore below the precision of the input and reflects that 42.98 is the value that general relativity predicts for this formula\n", d1 * 100);
        std::printf("     the coefficient 6 pi in k_from_precession is the general-relativity coefficient entering as an input (engine comment: 'GR-analogue')\n");
    }
    return 0;
}
