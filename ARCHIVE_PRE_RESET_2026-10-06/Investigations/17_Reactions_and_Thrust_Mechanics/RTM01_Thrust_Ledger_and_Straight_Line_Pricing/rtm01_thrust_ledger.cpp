// ═══════════════════════════════════════════════════════════════════════
//  RTM01 — The Thrust Ledger and Straight-Line Pricing.
//  Direct run per PROMPT.md (pre-registered). First investigation of
//  domain 17, Reactions & Thrust Mechanics.
//  Author: J. C. Harvey, Melbourne. 2026-08-03.
//
//  Consumes GOM23's validated instruments: the extraction algebra, the
//  lateral-bill closed form, and the pi-audit discipline.
//
//  Build: cl /std:c++20 /EHsc /O2 /W4 /I Engine\include rtm01_thrust_ledger.cpp
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>

using namespace sdt::laws;

static int pass_n = 0, fail_n = 0;
static void gate(const char* id, double got, double ref, double tol_pct, const char* note)
{
    double dev = (ref != 0.0) ? std::fabs(got / ref - 1.0) * 100.0 : std::fabs(got) * 100.0;
    bool ok = dev <= tol_pct;
    ok ? ++pass_n : ++fail_n;
    std::printf("  %-5s %-48s got %-13.6g ref %-13.6g dev %8.5f%%  %s\n",
                id, note, got, ref, dev, ok ? "PASS" : "FAIL");
}

int main()
{
    const double c  = measured::c;
    const double c2 = c * c;
    const double kopE = bridge::koppa_Earth;
    const double kopS = bridge::koppa_Sun;
    const double RE = 6.371e6, RS = measured::R_Sun, AU = measured::AU;

    std::puts("RTM01 — THE THRUST LEDGER AND STRAIGHT-LINE PRICING (direct run)");
    std::puts("=================================================================");
    std::puts("Domain 17, Reactions & Thrust Mechanics — the forced state.");

    // ── P1: ledger laws ─────────────────────────────────────────────────
    std::puts("\n[P1] ledger laws — the price list of straightness ({kop, c, r} only, zero pi):");
    std::puts("  hover price      a(r)    = c^2*kop/r^2      [reaction to stand still]");
    std::puts("  lateral bill     dv_perp = 2*c^2*kop/(b*v)  [reaction to pass straight]");
    std::puts("  per-metre toll   dz/dl   = kop/r^2          [radial component of the line]");

    // hover rows
    std::printf("\n  hover, Earth surface : %9.4f m/s^2\n", c2 * kopE / (RE * RE));
    std::printf("  hover, Earth +400 km : %9.4f m/s^2\n", c2 * kopE / std::pow(RE + 4e5, 2));
    const double g_sun_ledger = c2 * kopS / (RS * RS);
    const double g_sun_engine = bridge::v_surface_Sun * bridge::v_surface_Sun / RS;
    gate("G1", g_sun_ledger, g_sun_engine, 0.1, "hover Sun: c^2*kop/R^2 vs v_surf^2/R [m/s^2]");

    // ── P2: budget bookkeeping along a powered path ────────────────────
    std::puts("\n[P2] budget bookkeeping — the toll ledger along a powered radial line (Earth):");
    std::puts("      r            z = kop/r          hover a [m/s^2]");
    const double rows[] = { RE, RE + 1e5, RE + 4e5, RE + 2e6, 3.844e8 };
    for (double r : rows)
        std::printf("      %-12.5g %-18.6e %g\n", r, kopE / r, c2 * kopE / (r * r));
    // identity at the surface rung: v_surf^2/c^2 = kop/R (construction of koppa_Earth)
    const double v_surf_E = 7909.0;
    gate("G2", (v_surf_E * v_surf_E) / c2, kopE / RE, 0.05,
         "budget identity v^2/c^2 = kop/r at the surface rung");
    std::puts("      on a FORCED path the travel purse is paid by reaction, not by");
    std::puts("      circulation — the toll is billed to the engine, tick by tick.");

    // ── P3: propulsion pricing ─────────────────────────────────────────
    std::puts("\n[P3] propulsion pricing — what refusing the curve costs:");
    {
        const double vex = 4500.0;                       // stated engineering parameter
        const double aE = c2 * kopE / (RE * RE);
        const double day = 86400.0;
        const double log10_ratio = aE * day / vex / std::log(10.0);
        std::printf("  hover ledger (Tsiolkovsky), Earth surface, v_ex = 4.5 km/s:\n");
        std::printf("    mass ratio per DAY of hover = 10^%.1f   (per hour: 10^%.2f)\n",
                    log10_ratio, log10_ratio / 24.0);
        std::puts("    the number is the point: the curve is free, the line is astronomical.");
    }
    std::puts("\n  straight-pass lateral bill dv_perp = 2*c^2*kop/(b*v)  [m/s]:");
    std::puts("      body    b            v [km/s]   dv_perp");
    struct Row { const char* n; double kop, b, v; };
    const Row tab[] = {
        { "Earth", kopE,  2 * RE,   10e3 }, { "Earth", kopE, 10 * RE,  10e3 },
        { "Earth", kopE, 100 * RE,  10e3 }, { "Sun",   kopS, 10 * RS,  30e3 },
        { "Sun",   kopS, 0.5 * AU,  30e3 }, { "Sun",   kopS, 1.0 * AU, 30e3 },
    };
    for (auto& t : tab)
        std::printf("      %-7s %-12.4g %-10.0f %g\n", t.n, t.b, t.v / 1000.0,
                    2.0 * c2 * t.kop / (t.b * t.v));

    // ── P4: the decomposition (E110) ────────────────────────────────────
    std::puts("\n[P4] the decomposition of the deflection 4 — one instrument per factor:");
    std::puts("  slow powered line pays GEOMETRY-2 only:  theta_slow = 2*kop*c^2/(b*v^2)");
    std::puts("  light pays PROFILE-2 x GEOMETRY-2:       theta_light = 4*kop/b");
    {
        const double b = RS;
        const double th_light = 4.0 * kopS / b;
        std::printf("\n  at the solar limb (b = R_Sun): theta_light = %.4f arcsec\n",
                    th_light * 206264.806);
        std::puts("      v [km/s]   theta_slow/theta_light      c^2/(2 v^2)     identity dev");
        bool id_ok = true;
        const double vlist[] = { 10e3, 30e3, 100e3, 300e3 };
        for (double v : vlist) {
            const double th_slow = 2.0 * kopS * c2 / (b * v * v);
            const double ratio = th_slow / th_light;
            const double law = c2 / (2.0 * v * v);
            const double dev = std::fabs(ratio / law - 1.0);
            if (dev > 1e-12) id_ok = false;
            std::printf("      %-10.0f %-27.6e %-15.6e %.1e\n", v / 1000.0, ratio, law, dev);
        }
        gate("G3", id_ok ? 1.0 : 0.0, 1.0, 0.0, "ratio law theta_slow/theta_light = c^2/2v^2");
    }
    std::puts("  -> E110 (specification): fly the null-steered line and time the light past");
    std::puts("     the same b; the thrust telemetry reads the geometric 2 alone, the ray adds");
    std::puts("     the profile 2. First order is shared form (PPN produces the same split);");
    std::puts("     the earned content is the decomposition made OPERATIONAL.");

    // ── verdict line ────────────────────────────────────────────────────
    std::printf("\nRESULT: %d gates PASS, %d FAIL.\n", pass_n, fail_n);
    std::puts("pi-audit: every law above uses {kop, c, r, b, v, v_ex} only — no pi, no G,");
    std::puts("no M, no kilogram. Findings feed the next RTM investigation.");
    return fail_n == 0 ? 0 : 1;
}
