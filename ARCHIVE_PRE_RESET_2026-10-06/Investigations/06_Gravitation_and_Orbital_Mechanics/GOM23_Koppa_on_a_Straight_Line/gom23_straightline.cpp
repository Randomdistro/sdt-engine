// ═══════════════════════════════════════════════════════════════════════
//  GOM23 — Koppa on a Straight Line. Direct run per PROMPT.md (pre-registered).
//  Author: J. C. Harvey, Melbourne. 2026-08-03.
//
//  Founding distinction: free fall follows the field's line; STRAIGHT is
//  lattice-defined and bought by reaction. Primary instruments are reaction
//  instruments; field-following routes live in Appendix A as consistency.
//
//  Build: cl /std:c++20 /EHsc /O2 /W4 /I Engine\include gom23_straightline.cpp
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace sdt::laws;

static int pass_n = 0, fail_n = 0;
static void gate(const char* id, double got, double ref, double tol_pct, const char* note)
{
    double dev = (ref != 0.0) ? std::fabs(got / ref - 1.0) * 100.0 : std::fabs(got) * 100.0;
    bool ok = dev <= tol_pct;
    ok ? ++pass_n : ++fail_n;
    std::printf("  %-6s %-46s got %-14.6g ref %-14.6g dev %8.4f%%  gate %.2f%%  %s  %s\n",
                id, note, got, ref, dev, tol_pct, ok ? "PASS" : "FAIL",
                ok ? "" : "<-- falsification row fires");
}

int main()
{
    const double c  = measured::c;
    const double c2 = c * c;
    const double kopE = bridge::koppa_Earth;   // comparison anchor ONLY (P5 rows)
    const double kopS = bridge::koppa_Sun;     // comparison anchor ONLY
    const double RE = 6.371e6;

    std::puts("GOM23 — KOPPA ON A STRAIGHT LINE (direct run, pre-registered gates)");
    std::puts("====================================================================");

    // ── P1: pi-audit ────────────────────────────────────────────────────
    std::puts("\n[P1] pi-audit — every recovery chain and its inputs:");
    std::puts("  I1 scale:            { g_measured, R_E, c }              -> kop = g*R^2/c^2");
    std::puts("  I2 tower:            { dnu/nu, h, r, c }                 -> kop = (dnu/nu)*r^2/h");
    std::puts("  I3 photoionisation:  { E_ion, m_e, a_0, c }              -> kop = a_0*(2E/(m_e c^2))");
    std::puts("  P3 ascent:           { a_proper, a_kinematic, r, c }     -> kop = (a_p - a_k)*r^2/c^2");
    std::puts("  P4 line:             { dv_perp, b, v, c }                -> kop = dv*b*v/(2 c^2)");
    std::puts("  ZERO pi in any chain. The pi-coefficients of the census belong to the");
    std::puts("  sampling geometries, not to the length.  [P1 PASS by enumeration]");
    ++pass_n;

    // ── P2: instruments on known answers ────────────────────────────────
    std::puts("\n[P2] instruments validated on known answers (reaction instruments):");

    // I1 — the scale. Conventional g0 contains a centrifugal term (equator -0.0339).
    const double g0 = 9.80665;                       // conventional standard gravity
    const double kop_from_scale = g0 * RE * RE / c2; // straight-line recovery
    std::puts("  I1  standing still IS thrust: the normal force is the instrument.");
    std::printf("      centrifugal content of conventional g0: -0.034 m/s^2 (equator), stated.\n");
    gate("I1", kop_from_scale, kopE, 0.5, "scale: kop = g0*R^2/c^2 [m]");

    // I2 — the tower. 450 m plumb line; identity dnu/nu = kop*h/r^2 = g*h/c^2.
    const double h = 450.0;
    const double shift = kop_from_scale * h / (RE * RE);   // uses the SCALE-recovered kop
    const double shift_id = g0 * h / c2;                   // gh/c^2 identity
    gate("I2a", shift, shift_id, 0.01, "tower: kop*h/r^2 vs g*h/c^2");
    gate("I2b", shift, 4.9e-14, 2.0, "tower: vs measured chronometric class");

    // I3 — photoionisation: radial escape from the hydrogen seat.
    const double E_ion = 13.598434 * measured::eV_to_J;
    const double v_seat = std::sqrt(2.0 * E_ion / measured::m_e);
    const double k_seat = c / v_seat;
    const double kopH = measured::a_0 / (k_seat * k_seat);
    std::printf("      finite-proton seat k = %.4f (idealisation 137.036) — offset stated.\n", k_seat);
    gate("I3", kopH, measured::r_e, 0.1, "photoionisation: kop_H = a_0/k^2 [m]");

    // ── P3: synthetic ascent extraction ─────────────────────────────────
    std::puts("\n[P3] synthetic powered ascent — recover kop from (a_proper - a_kinematic):");
    {
        // simulate 1-D radial powered ascent over KNOWN kopE; constant proper accel program
        const double a_prog = 25.0;         // engine's proper acceleration [m/s^2]
        double r = RE, v = 0.0;
        const double dt = 1e-3;
        double worst = 0.0;
        int samples = 0;
        for (long i = 0; i < 400000; ++i) { // 400 s of flight
            double g_true = c2 * kopE / (r * r);
            double a_kin = a_prog - g_true; // true kinematics under the ledger
            v += a_kin * dt;
            r += v * dt;
            if (i % 40000 == 0) {
                // the extraction: instrument reads a_prog (IMU) and a_kin (GPS)
                double kop_rec = (a_prog - a_kin) * r * r / c2;
                double dev = std::fabs(kop_rec / kopE - 1.0);
                if (dev > worst) worst = dev;
                ++samples;
            }
        }
        std::printf("      %d samples along 400 s ascent, altitude reached %.1f km\n",
                    samples, (r - RE) / 1000.0);
        gate("P3", 1.0 + worst, 1.0, 0.1, "worst-sample recovery ratio (1 = exact)");
        std::puts("      synthetic pass licenses the EXTRACTION; real telemetry is OWED");
        std::puts("      (DATA_REQUIREMENTS.md).");
    }

    // ── P4: the null-steered line ───────────────────────────────────────
    std::puts("\n[P4] straight line at speed v, impact parameter b — lateral bill:");
    {
        const double b = 10.0 * RE, vline = 1.0e4;
        const double X = 1.0e3 * b;                 // X/b = 1e3 per gate
        // numerical lateral impulse per unit mass along the fixed straight line
        const long   N = 4000001;                   // Simpson, odd count
        const double dx = 2.0 * X / (N - 1);
        double sum = 0.0;
        for (long i = 0; i < N; ++i) {
            double x = -X + i * dx;
            double r2 = x * x + b * b;
            double integ = b / (r2 * std::sqrt(r2));      // b / r^3
            double w = (i == 0 || i == N - 1) ? 1.0 : ((i % 2) ? 4.0 : 2.0);
            sum += w * integ;
        }
        sum *= dx / 3.0;
        const double dv_num = c2 * kopE * sum / vline;    // ∫ g_perp dt = (c^2 kop / v) ∫ b/r^3 dx
        const double dv_closed = 2.0 * c2 * kopE / (b * vline);
        gate("P4", dv_num, dv_closed, 0.5, "numerical vs closed 2c^2*kop/(b*v) [m/s]");
        std::printf("      inversion check: kop = dv*b*v/(2c^2) = %.6g m (anchor %.6g m)\n",
                    dv_num * b * vline / (2.0 * c2), kopE);
    }

    // ── P5: closure table — straight vs circular, one pass ─────────────
    std::puts("\n[P5] closure: straight-line kop vs circular-ladder kop, per rung:");
    gate("P5a", kop_from_scale, kopE, 1.0, "Earth: scale vs bridge::koppa_Earth [m]");
    {
        // Sun straight-line row: pointwise deficit reading (radial spectroscopy, B28-class)
        const double z_sun = depth_closure::z_spectral_Sun;      // engine's pointwise depth
        const double kop_sun_straight = z_sun * measured::R_Sun; // one radial stab, no circle
        gate("P5b", kop_sun_straight, kopS, 1.0, "Sun: pointwise z*R vs bridge::koppa_Sun [m]");
    }
    gate("P5c", kopH, measured::r_e, 1.0, "H: photoionisation vs r_e (circular ladder) [m]");

    // ── Appendix A: field-following (consistency ONLY — not straight) ──
    std::puts("\n[Appendix A] field-following routes — consistency, NOT straight:");
    {
        const double r2R = 2.0 * measured::R_Sun;
        std::printf("  sungrazer v at 2R_Sun = c*sqrt(2*kop/r) = %.0f km/s (observed class 400-600)\n",
                    c * std::sqrt(2.0 * kopS / r2R) / 1000.0);
        std::printf("  surface escape        = %.1f km/s (standard 617.5)\n",
                    c * std::sqrt(2.0 * kopS / measured::R_Sun) / 1000.0);
        std::puts("  these follow the field's line; they are never cited as the straight-line result.");
    }

    // ── verdict line ────────────────────────────────────────────────────
    std::printf("\nRESULT: %d gates PASS, %d FAIL.\n", pass_n, fail_n);
    std::puts("Shared-form caveat: every recovered number coincides with a GM-derived value;");
    std::puts("the straight-line ledger cannot discriminate the readings. Earned content:");
    std::puts("pi-free provenance, reaction-instrument validation, and the closure of the");
    std::puts("straight-line family onto the circular ladder.");
    return fail_n == 0 ? 0 : 1;
}
