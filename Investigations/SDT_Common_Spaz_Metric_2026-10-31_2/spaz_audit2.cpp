// ============================================================================
//  spaz_audit2.cpp — Common Spaz Metric run 2, workstreams W1, W2, W4, W7, W8
//  Author: James Christopher Tyndall, Melbourne.
//
//  Recomputes every arithmetic and geometric claim raised in the 2026-10
//  session stream and prints REPRODUCED / NOT REPRODUCED against the claim.
//  All constants are read from the engine (sdt::laws). Values quoted by the
//  audited texts are printed as CLAIM; literature comparators carry their
//  source in the label.
//
//  Build: g++ -std=c++20 -O2 -IEngine/include spaz_audit2.cpp -o spaz_audit2
// ============================================================================

#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <numbers>

namespace {

namespace M = sdt::laws::measured;
namespace B = sdt::laws::bridge;
constexpr double PI = std::numbers::pi;
constexpr double MeV = M::MeV_to_J;

void verdict(const char* label, double recomputed, double claim, double tol) {
    const double rel = std::abs(recomputed - claim) / std::abs(claim);
    std::printf("  %-46s recomputed % .6e  claim % .6e  rel %.2e  %s\n",
        label, recomputed, claim, rel,
        rel < tol ? "REPRODUCED" : "NOT REPRODUCED");
}

// ── W1 ──────────────────────────────────────────────────────────────────────
void w1() {
    std::printf("\nW1  Pasted electron self-energy / hydrogen derivation\n");
    const double r_e = M::r_e;
    const double hc_over_re = M::hbar * M::c / r_e;
    std::printf("  validation: hbar c / r_e = %.4f MeV (known 70.02)\n",
        hc_over_re / MeV);
    verdict("E_p(r_e) = 1 - e^-1", 1.0 - std::exp(-1.0), 0.63212055883, 1e-9);
    verdict("E_self = (hbar c/r_e) x 0.5772 [MeV]",
        hc_over_re * 0.5772156649 / MeV, 0.510998946, 1e-6);
    std::printf("  integral of E_p r^2 dr to R (diverges, units m^3):\n");
    for (double n : {10.0, 100.0, 1000.0}) {
        // integrand r_e^2 (1 - exp(-r/r_e)); closed form
        const double R = n * r_e;
        const double I = r_e * r_e * (R - r_e * (1.0 - std::exp(-R / r_e)));
        std::printf("    R = %6.0f r_e : %.4e m^3  (claim: r_e x 0.5772 = %.4e m)\n",
            n, I, r_e * 0.5772156649);
    }
    const double x = r_e / 5e-11;
    verdict("(r_e / 5e-11 m)^2", x * x, 3.17721e-8, 1e-3);
    const double E1 = x * x * (1.0 - std::exp(-5e-11 / r_e));
    verdict("r_1 = r_e/(1-E_1) [m]", r_e / (1.0 - E1), 5.29177209e-11, 1e-6);
    const double e4 = std::pow(M::e_charge, 4);
    verdict("m e^4/(2 hbar^2) as written [J]",
        M::m_e * e4 / (2.0 * M::hbar * M::hbar), 2.179873631e-18, 1e-6);
    verdict("with k_e^2 restored [J] (comparator)",
        M::m_e * e4 * M::k_e * M::k_e / (2.0 * M::hbar * M::hbar),
        2.179873631e-18, 1e-6);
}

// ── W2 ──────────────────────────────────────────────────────────────────────
void w2() {
    std::printf("\nW2  Gemini fault-line claims\n");
    const double frac = 1.27e-4 * 1.19e57 * 1.67262e-27 / 1.496e11;
    verdict("Earth: k N m_n / r", frac, 2.1276e14, 1e-3);
    verdict("Gemini correction 1.6895e15", frac, 1.6895e15, 1e-3);
    verdict("sqrt(2.1276e14 x 0.9425) [m/s]",
        std::sqrt(2.1276e14 * 0.9425), 29783.0, 1e-3);
    verdict("Gemini: sqrt(2.005e14) = 14,160,729",
        std::sqrt(2.1276e14 * 0.9425), 14160729.0, 1e-4);
    verdict("Jupiter 3.466e-15 x 4.0201e-19", 3.466e-15 * 4.0201e-19, 0.1393, 1e-3);
    verdict("sqrt(2.8540e9)", std::sqrt(2.8540e9), 17334.0, 1e-3);

    // Io under the koppa form; beta_J supplied by the Gemini text
    const double R_J = 6.9911e7, beta_J = 1.266865e17, r_Io = 4.217e8;
    const double k_J = M::c * std::sqrt(R_J / beta_J);
    const double v_Io = M::c / k_J * std::sqrt(R_J / r_Io);
    const double a_Io = M::c * M::c / (k_J * k_J) * R_J / (r_Io * r_Io);
    verdict("k_J = c sqrt(R_J/beta_J)", k_J, 7042.4, 1e-4);
    verdict("v(Io) [m/s]", v_Io, 17332.7, 1e-4);
    verdict("a(Io) [m/s^2]", a_Io, 0.7124, 1e-3);
    // beta_J against JPL GM_J (comparator, MEASURED-INPUT JPL): identity check
    std::printf("  beta_J / GM_J(JPL 1.26686534e17) = %.7f  -> beta_J IS the "
        "orbital calibration, not an independent input\n", beta_J / 1.26686534e17);

    // Cap vs projected solid angle, full range, plus quadrature validation
    std::printf("  solid-angle forms (force fraction x 4/(4pi) vs projected/pi):\n");
    std::printf("    %8s %12s %12s %12s\n", "d/R", "cap C=4", "projected", "cap/proj");
    for (double dr : {1.0, 1.05, 1.1, 1.5, 2.0, 3.0, 5.0, 10.0, 83.17, 100.0}) {
        const double s2 = 1.0 / (dr * dr);
        const double cap = 2.0 * (1.0 - std::sqrt(1.0 - s2));
        // projected: 2 pi int_0^asin(R/d) cos sin dtheta, by quadrature
        const double th = std::asin(1.0 / dr);
        const int n = 200000;
        double q = 0.0;
        for (int i = 0; i < n; ++i) {
            const double t = (i + 0.5) * th / n;
            q += std::cos(t) * std::sin(t);
        }
        q *= 2.0 * PI * th / n;
        const double proj = q / PI;
        if (std::abs(proj - s2) > 1e-9)
            std::printf("    VALIDATION FAIL at d/R=%g\n", dr);
        std::printf("    %8.2f %12.8f %12.8f %12.6f\n", dr, cap, proj, cap / proj);
    }

    // Icosahedral 13-sphere cluster
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    const double edge_over_R = 2.0 / std::sqrt(1.0 + phi * phi);
    std::printf("  icosahedron edge / circumradius = %.6f  -> outer neighbours %s "
        "(gap %.2f %% of a diameter); contacts = 12 radial, 0 tangential\n",
        edge_over_R, edge_over_R > 1.0 ? "DO NOT TOUCH" : "touch",
        100.0 * (edge_over_R - 1.0));
    verdict("polar ring angle atan(2) [deg]", std::atan(2.0) * 180.0 / PI, 63.4349, 1e-5);
    verdict("dodecahedron dihedral acos(-1/sqrt5) [deg]",
        std::acos(-1.0 / std::sqrt(5.0)) * 180.0 / PI, 116.5651, 1e-5);
    // Regular 4-polytopes: V, E, F, C
    const int c120[4] = {600, 1200, 720, 120}, c600[4] = {120, 720, 1200, 600};
    std::printf("  120-cell V E F C = %d %d %d %d (Euler %d), dodecahedra per vertex %d\n",
        c120[0], c120[1], c120[2], c120[3], c120[0] - c120[1] + c120[2] - c120[3],
        c120[3] * 20 / c120[0]);
    std::printf("  600-cell V E F C = %d %d %d %d (Euler %d), tetrahedra per vertex %d "
        "(Gemini claim 12: NOT REPRODUCED), neighbours per vertex %d\n",
        c600[0], c600[1], c600[2], c600[3], c600[0] - c600[1] + c600[2] - c600[3],
        c600[3] * 4 / c600[0], 2 * c600[1] / c600[0]);
    std::printf("  triangular numbers T6 = %d, T7 = %d\n", 6 * 7 / 2, 7 * 8 / 2);
}

// ── W4 ──────────────────────────────────────────────────────────────────────
void w4() {
    std::printf("\nW4  Gamma_ep = k_e e^2 m_p R_p (1+z) / hbar^2\n");
    const double kee = M::k_e * M::e_charge * M::e_charge;
    const double lbar_p = M::hbar / (M::m_p * M::c);
    struct Rp { const char* src; double v, s; };
    const Rp rps[] = {
        {"engine R_p (0.8414(19), CODATA-2018 value)", 0.8414e-15, 0.0019e-15},
        {"muonic H 0.84087(39) (Antognini 2013)",       0.84087e-15, 0.00039e-15},
        {"CODATA-2022 0.84075(64)",                     0.84075e-15, 0.00064e-15},
    };
    struct Ep { const char* name; double z; };
    const Ep eps[] = {{"z* 1089.92 (Planck 2018)", 1089.92},
                      {"z_drag 1059.94 (Planck 2018)", 1059.94}};
    std::printf("  route check: Gamma = 4 alpha (1+z) (R_p / 4 lbar_p)\n");
    for (const auto& rp : rps) {
        std::printf("  %s : R_p/lbar_p = %.5f\n", rp.src, rp.v / lbar_p);
        for (const auto& ep : eps) {
            const double g1 = kee * M::m_p * rp.v * (1.0 + ep.z) / (M::hbar * M::hbar);
            const double g2 = 4.0 * M::alpha * (1.0 + ep.z) * rp.v / (4.0 * lbar_p);
            const double Rneed = PI * PI * PI * M::hbar * M::hbar
                / (kee * M::m_p * (1.0 + ep.z));
            std::printf("    %-30s Gamma %.5f (route2 rel %.1e)  vs pi^3 %+.3f %%  "
                "vs 32 %+.3f %%  R_p(pi^3) %.5f fm = %+.1f sigma\n",
                ep.name, g1, std::abs(g1 - g2) / g1,
                100.0 * (g1 / (PI * PI * PI) - 1.0), 100.0 * (g1 / 32.0 - 1.0),
                Rneed * 1e15, (Rneed - rp.v) / rp.s);
        }
    }
    const double z_pi3 = PI * PI * PI * M::hbar * M::hbar / (kee * M::m_p * M::R_p) - 1.0;
    std::printf("  epoch at which Gamma = pi^3 exactly (engine R_p): 1+z = %.3f\n",
        z_pi3 + 1.0);
    std::printf("  epoch spread: (1+z*)/(1+z_drag) = %.6f; one unit of z = %.3f %%\n",
        1090.92 / 1060.94, 100.0 / 1060.94);
    std::printf("  look-elsewhere ledger: targets tried {pi^3, 32}, epochs tried "
        "{z*, z_drag}: 4 trials, selected after inspection\n");
}

// ── W7 ──────────────────────────────────────────────────────────────────────
void w7() {
    std::printf("\nW7  Shapiro-displacement torus\n");
    // validation: Pappus vs Monte Carlo for a ring torus R=3, r=1
    {
        const double R = 3.0, r = 1.0;
        unsigned long long s = 88172645463325252ULL, hit = 0, n = 4000000;
        auto rnd = [&]() { s ^= s << 13; s ^= s >> 7; s ^= s << 17;
                           return (s >> 11) * (1.0 / 9007199254740992.0); };
        for (unsigned long long i = 0; i < n; ++i) {
            const double x = (2 * rnd() - 1) * 4, y = (2 * rnd() - 1) * 4,
                         z = (2 * rnd() - 1) * 1;
            const double q = std::sqrt(x * x + y * y) - R;
            if (q * q + z * z <= r * r) ++hit;
        }
        const double mc = 8 * 8 * 2 * double(hit) / n;
        std::printf("  validation: ring torus Pappus %.4f vs Monte Carlo %.4f\n",
            2 * PI * PI * R * r * r, mc);
    }
    const double zs = B::koppa_Sun / M::R_Sun;         // solar surface depth
    const double dc = 2.0 * zs;                         // Shapiro factor 2
    const double dP = 4.0 * dc;                         // c ~ Pi^(-1/4) premise
    const double Nb = B::N_baryons(B::koppa_Sun);       // SDT-native count
    const double Vsun = 4.0 / 3.0 * PI * std::pow(M::R_Sun, 3);
    const double Vb = dP * Vsun / Nb;
    std::printf("  dc/c = %.4e  dPi/Pi = %.4e  N_b(koppa) = %.4e  V per baryon %.4e m^3\n",
        dc, dP, Nb, Vb);
    struct Var { const char* name; double factorV; double mult; };
    const Var vars[] = {{"as transcript (x1836, Shapiro 2, Pi^-1/4)", 1.0, 1836.0},
                        {"no x1836", 1.0, 1.0},
                        {"Shapiro factor 1", 0.5, 1836.0},
                        {"c ~ Pi^(-1/2) premise", 0.5, 1836.0}};
    const double lamC = M::lambda_C_e;
    for (const auto& v : vars) {
        const double r = std::sqrt(Vb * v.factorV / (2 * PI * PI * M::R_p * v.mult));
        std::printf("    %-42s r_tube %.4e m  r/(lambda_C/3) %.4f  r/R_p %.1f  %s\n",
            v.name, r, r / (lamC / 3.0), r / M::R_p,
            r < M::R_p ? "ring torus" : "SPINDLE (Pappus invalid)");
    }
}

// ── W8 ──────────────────────────────────────────────────────────────────────
void w8() {
    std::printf("\nW8  Neutrino tick test (prediction only)\n");
    std::printf("  %10s %14s %16s %16s\n", "koppa/R", "N=1/(1-z)", "E ratio (tick)",
        "E ratio (no tick)");
    for (double zd : {0.10, 0.15, 0.20, 0.25}) {
        const double N = 1.0 / (1.0 - zd);
        std::printf("  %10.2f %14.4f %16.4f %16.4f\n", zd, N, 1.0 / N, 1.0);
    }
}

} // namespace

int main() {
    std::printf("spaz_audit2 — Common Spaz Metric run 2 (W1 W2 W4 W7 W8)\n");
    w1(); w2(); w4(); w7(); w8();
    return 0;
}
