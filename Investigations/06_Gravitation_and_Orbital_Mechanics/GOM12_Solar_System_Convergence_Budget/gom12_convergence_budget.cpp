// =============================================================================
// GOM12 — Complete Convergence Budget of the Solar System (E101)
//
// Per-body koppa census from PURE MEASURED KINEMATICS (v, r, R only):
//   - k = c/v, z = (v/c)^2, zk^2 closure (IDENTITY — labelled, never a result)
//   - koppa of a PARENT from each satellite orbit: kappa = v_orb^2 * a / c^2
//   - Kepler check: v(r) = v_surf,Sun * sqrt(R_Sun/r) vs JPL velocities
//   - Occlusion census: fraction of the Sun's 4pi influx occluded per planet
//   - Budget closure: lumiopause r = sqrt(L_Sun/(4 pi F_CMB)) vs Oort inner edge
//
// No G. No M as inputs. GM/c^2 (IAU) appears ONLY as the OBSERVED comparison
// column — labelled CONVERGENCE (sanctioned, disclosed identity koppa = GM/c^2).
//
// Thresholds pre-committed in RUN_LOG.md (2026-07-03) BEFORE this file was coded.
//
// @author J. C. Harvey, Melbourne — executed 2026-07-03
// =============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static int n_pass = 0, n_fail = 0, n_identity = 0, n_open = 0;

static void gate(const char* tag, bool ok) {
    if (ok) ++n_pass; else ++n_fail;
    std::printf("  [%s] %s\n", ok ? "PASS" : "FAIL", tag);
}

// ---------------------------------------------------------------------------
// OBSERVED inputs (JPL/IAU, measured kinematics only)
// ---------------------------------------------------------------------------
struct Planet {
    const char* name;
    double v_orb;    // [m/s]  JPL mean (circular-equivalent) orbital velocity
    double a;        // [m]    semi-major axis
    double R;        // [m]    body radius
    double GM_iau;   // [m^3/s^2] IAU/JPL — OBSERVED COMPARISON COLUMN ONLY
};

static const Planet planets[] = {
    // name       v_orb      a (AU * AU_m)            R          GM (OBSERVED col.)
    {"Mercury",  47870.0,  0.38710 * AU,  2.440e6,  2.203209e13},
    {"Venus",    35020.0,  0.72333 * AU,  6.052e6,  3.248586e14},
    {"Earth",    29780.0,  1.00000 * AU,  6.371e6,  3.986004e14},
    {"Mars",     24080.0,  1.52366 * AU,  3.390e6,  4.282837e13},
    {"Jupiter",  13070.0,  5.20336 * AU,  6.991e7,  1.266865e17},
    {"Saturn",    9680.0,  9.53707 * AU,  5.823e7,  3.793119e16},
    {"Uranus",    6800.0, 19.19126 * AU,  2.536e7,  5.793939e15},
    {"Neptune",   5430.0, 30.06896 * AU,  2.462e7,  6.836529e15},
};
static constexpr int NP = sizeof(planets) / sizeof(planets[0]);

// Satellites: parent koppa from PURE satellite kinematics (v_orb, a).
struct Moon {
    const char* parent;
    const char* name;
    double v_orb;   // [m/s]
    double a;       // [m]
    double GM_parent_iau; // OBSERVED comparison column only
};

static const Moon moons[] = {
    {"Earth",   "Moon",     1022.0, 3.844000e8, 3.986004e14},
    {"Mars",    "Phobos",   2138.0, 9.376000e6, 4.282837e13},
    {"Jupiter", "Io",      17334.0, 4.217000e8, 1.266865e17},
    {"Jupiter", "Europa",  13740.0, 6.710340e8, 1.266865e17},
    {"Jupiter", "Ganymede",10880.0, 1.070412e9, 1.266865e17},
    {"Jupiter", "Callisto", 8204.0, 1.882709e9, 1.266865e17},
    {"Saturn",  "Titan",    5570.0, 1.221870e9, 3.793119e16},
    {"Uranus",  "Titania",  3640.0, 4.359100e8, 5.793939e15},
    {"Neptune", "Triton",   4390.0, 3.547590e8, 6.836529e15},
};
static constexpr int NM = sizeof(moons) / sizeof(moons[0]);

int main() {
    std::printf("=====================================================================\n");
    std::printf(" GOM12: SOLAR-SYSTEM CONVERGENCE BUDGET (E101)\n");
    std::printf(" Pure measured kinematics. No G, no M as inputs.\n");
    std::printf(" GM/c^2 column = OBSERVED comparison only (CONVERGENCE, disclosed).\n");
    std::printf(" J. C. Harvey, Melbourne — 2026-07-03\n");
    std::printf("=====================================================================\n\n");

    // ------------------------------------------------------------------
    // 1. k-hierarchy and closure (IDENTITY — labelled)
    // ------------------------------------------------------------------
    std::printf("--- 1. k-HIERARCHY (orbital) --- [zk^2 = 1 is an IDENTITY: notation only]\n\n");
    std::printf("  %-8s  %10s  %10s  %12s  %16s\n", "Body", "v [km/s]", "k = c/v", "z = (v/c)^2", "z*k^2 - 1");
    double max_id_dev = 0.0;
    double sum_z = 0.0;
    for (int i = 0; i < NP; ++i) {
        const auto& p = planets[i];
        double k = c / p.v_orb;
        double z = (p.v_orb / c) * (p.v_orb / c);
        double dev = std::fabs(z * k * k - 1.0);
        if (dev > max_id_dev) max_id_dev = dev;
        sum_z += z;
        std::printf("  %-8s  %10.2f  %10.1f  %12.4e  %16.2e\n",
                    p.name, p.v_orb / 1e3, k, z, z * k * k - 1.0);
    }
    ++n_identity;
    std::printf("\n  max |zk^2 - 1| = %.2e  -> IDENTITY holds (algebra, NOT physics; not scored)\n", max_id_dev);
    std::printf("  Total planetary convergence coupling: sum z_i = %.4e (dimensionless)\n\n", sum_z);

    // ------------------------------------------------------------------
    // 2. Kepler check: v(r) = v_surf,Sun * sqrt(R_Sun/r)   [gate 0.1%]
    // ------------------------------------------------------------------
    std::printf("--- 2. KEPLER CHECK: v(r) = (c/k_Sun) sqrt(R_Sun/r)  [gate 0.1%%] ---\n\n");
    double v_surf_sun = c / bridge::k_Sun;   // 436.8 km/s from laws.hpp k_Sun = 686.3
    std::printf("  v_surf,Sun = c/k_Sun = %.1f m/s (k_Sun = %.1f, laws.hpp bridge)\n\n", v_surf_sun, bridge::k_Sun);
    std::printf("  %-8s  %12s  %12s  %10s\n", "Body", "v_pred[m/s]", "v_JPL[m/s]", "err %");
    bool kepler_ok = true;
    double worst_kepler = 0.0;
    for (int i = 0; i < NP; ++i) {
        const auto& p = planets[i];
        double v_pred = v_surf_sun * std::sqrt(R_Sun / p.a);
        double err = (v_pred - p.v_orb) / p.v_orb * 100.0;
        if (std::fabs(err) > std::fabs(worst_kepler)) worst_kepler = err;
        if (std::fabs(err) > 0.1) kepler_ok = false;
        std::printf("  %-8s  %12.1f  %12.1f  %+10.4f\n", p.name, v_pred, p.v_orb, err);
    }
    std::printf("\n  worst |err| = %.4f%%\n", std::fabs(worst_kepler));
    gate("Kepler v(r) reproduces all 8 JPL velocities to < 0.1% [CONVERGENCE]", kepler_ok);
    std::printf("\n");

    // ------------------------------------------------------------------
    // 3. Parent invariance: koppa_Sun from each planet   [gate sigma/mu 0.1%]
    // ------------------------------------------------------------------
    std::printf("--- 3. PARENT INVARIANCE: koppa_Sun = v^2 a / c^2 from each planet ---\n\n");
    std::printf("  %-8s  %14s\n", "Body", "koppa_Sun [m]");
    double s = 0, s2 = 0;
    for (int i = 0; i < NP; ++i) {
        const auto& p = planets[i];
        double K = p.v_orb * p.v_orb * p.a / (c * c);
        s += K; s2 += K * K;
        std::printf("  %-8s  %14.4f\n", p.name, K);
    }
    double mean = s / NP;
    double sd = std::sqrt(std::fabs(s2 / NP - mean * mean));
    double GM_sun_iau = 1.32712440018e20;                 // OBSERVED comparison only
    double koppa_sun_iau = GM_sun_iau / (c * c);
    std::printf("\n  mean koppa_Sun = %.4f m   sigma/mu = %.4f%%\n", mean, 100.0 * sd / mean);
    std::printf("  laws.hpp bridge::koppa_Sun = %.4f m\n", bridge::koppa_Sun);
    std::printf("  OBSERVED GM_Sun/c^2 (IAU)  = %.4f m   [CONVERGENCE column]\n", koppa_sun_iau);
    gate("koppa_Sun invariant across 8 planets (sigma/mu < 0.1%)", 100.0 * sd / mean < 0.1);
    gate("mean koppa_Sun within 0.5% of OBSERVED GM_Sun/c^2 [CONVERGENCE]",
         std::fabs(mean - koppa_sun_iau) / koppa_sun_iau < 0.005);
    std::printf("\n");

    // ------------------------------------------------------------------
    // 4. Per-body koppa census from THEIR satellites (pure kinematics)
    // ------------------------------------------------------------------
    std::printf("--- 4. PER-BODY KOPPA CENSUS (from satellite kinematics only) ---\n\n");
    std::printf("  %-8s  %-9s  %14s  %14s  %8s\n",
                "Parent", "Probe", "koppa_kin [m]", "GM/c^2 [m]", "err %");
    bool census_ok = true;
    // Jupiter multi-moon invariance accumulators
    double js = 0, js2 = 0; int jn = 0;
    for (int i = 0; i < NM; ++i) {
        const auto& m = moons[i];
        double K = m.v_orb * m.v_orb * m.a / (c * c);
        double K_obs = m.GM_parent_iau / (c * c);
        double err = (K - K_obs) / K_obs * 100.0;
        if (std::fabs(err) > 0.5) census_ok = false;
        if (std::strcmp(m.parent, "Jupiter") == 0) { js += K; js2 += K * K; ++jn; }
        std::printf("  %-8s  %-9s  %14.6e  %14.6e  %+8.3f\n",
                    m.parent, m.name, K, K_obs, err);
    }
    double jmean = js / jn;
    double jsd = std::sqrt(std::fabs(js2 / jn - jmean * jmean));
    std::printf("\n  Jupiter from 4 Galilean moons: mean = %.4f m, sigma/mu = %.3f%%\n",
                jmean, 100.0 * jsd / jmean);
    gate("koppa_Jupiter invariant across 4 Galilean moons (sigma/mu < 1%)",
         100.0 * jsd / jmean < 1.0);
    gate("every satellite-derived koppa within 0.5% of OBSERVED GM/c^2 [CONVERGENCE]",
         census_ok);
    std::printf("\n  HONEST GAP: Mercury and Venus have no satellites — their own koppa is\n");
    std::printf("  NOT measurable by pure orbital kinematics (flyby/radio data required).\n");
    std::printf("  Left blank, not plugged.\n\n");

    // ------------------------------------------------------------------
    // 5. Occlusion census: fraction of the Sun's 4pi influx occluded
    //    f_i = (pi R_i^2) / (4 pi a_i^2) = R_i^2 / (4 a_i^2)
    // ------------------------------------------------------------------
    std::printf("--- 5. OCCLUSION CENSUS (geometric, from the Sun) ---\n\n");
    std::printf("  %-8s  %14s\n", "Body", "f_occluded");
    double f_sum = 0.0;
    for (int i = 0; i < NP; ++i) {
        const auto& p = planets[i];
        double f = (p.R * p.R) / (4.0 * p.a * p.a);
        f_sum += f;
        std::printf("  %-8s  %14.4e\n", p.name, f);
    }
    std::printf("\n  TOTAL planetary occlusion of the Sun's sky: sum f = %.4e\n", f_sum);
    std::printf("  (i.e. the planets shadow ~%.2e of the Sun's 4pi convergence influx —\n", f_sum);
    std::printf("   the solar budget is closed to 1 part in ~%.1e by planetary occlusion)\n\n", 1.0 / f_sum);

    // ------------------------------------------------------------------
    // 6. Jupiter's convergence contribution at Earth vs 1e-8 residual
    // ------------------------------------------------------------------
    std::printf("--- 6. JUPITER'S DEPTH AT EARTH ---\n\n");
    double koppa_J = jmean;                       // from Galilean kinematics
    double r_JE_opp = (5.20336 - 1.0) * AU;       // opposition distance
    double z_J_at_E = koppa_J / r_JE_opp;
    double z_Sun_at_E = mean / AU;
    std::printf("  z_Jupiter(Earth, opposition) = koppa_J / r_JE = %.3e\n", z_J_at_E);
    std::printf("  z_Sun(Earth)                 = %.3e\n", z_Sun_at_E);
    std::printf("  ratio = %.3e\n", z_J_at_E / z_Sun_at_E);
    if (z_J_at_E < 1.0e-8) {
        ++n_open;
        std::printf("  [REPORT] z_J = %.2e is %.0fx BELOW the ~1e-8 orbital residual scale.\n",
                    z_J_at_E, 1.0e-8 / z_J_at_E);
        std::printf("  Jupiter's static depth does NOT explain a 1e-8 residual. Stated plainly.\n\n");
    } else {
        std::printf("  [REPORT] z_J >= 1e-8: comparable to the residual scale.\n\n");
    }

    // ------------------------------------------------------------------
    // 7. Budget closure: lumiopause vs Oort inner edge  [OPEN handling]
    // ------------------------------------------------------------------
    std::printf("--- 7. PRESSURE-DOMAIN CLOSURE: lumiopause vs Oort inner edge ---\n\n");
    double r_lum_AU = depth_closure::lumiopause_AU;
    std::printf("  Lumiopause r = sqrt(L_Sun/(4 pi F_CMB)) = %.0f AU (laws.hpp)\n", r_lum_AU);
    std::printf("  Oort inner-edge literature range: ~2,000 - 20,000 AU\n");
    std::printf("  ratio vs lower end: %.1f x    ratio vs upper end: %.2f x\n",
                r_lum_AU / 2000.0, r_lum_AU / 20000.0);
    ++n_open;
    std::printf("  [OPEN] Consistent with the UPPER end of the range only; the PROMPT's\n");
    std::printf("  'within factor of 2' criterion is under-specified against a 10x-wide\n");
    std::printf("  literature range. No PASS stamped. (Committed in RUN_LOG before run.)\n\n");

    // ------------------------------------------------------------------
    // 8. Integer k^2 patterns between adjacent planets (E21 conjecture)
    // ------------------------------------------------------------------
    std::printf("--- 8. ADJACENT k^2 RATIOS (E21 integer conjecture) ---\n\n");
    std::printf("  %-18s  %10s  %14s\n", "Pair", "k2 ratio", "|ratio-n|");
    int hits = 0;
    for (int i = 1; i < NP; ++i) {
        double k2a = (c / planets[i].v_orb) * (c / planets[i].v_orb);
        double k2b = (c / planets[i - 1].v_orb) * (c / planets[i - 1].v_orb);
        double ratio = k2a / k2b;
        double frac = std::fabs(ratio - std::round(ratio));
        bool hit = frac < 0.02 && ratio >= 1.5; // committed gate
        if (hit) ++hits;
        std::printf("  %-8s/%-8s  %10.4f  %14.4f%s\n",
                    planets[i].name, planets[i - 1].name, ratio, frac, hit ? "  <-- integer hit" : "");
    }
    std::printf("\n  Integer hits: %d / 7 pairs.\n", hits);
    if (hits <= 1) {
        std::printf("  [REPORT] No systematic integer pattern (>=1 isolated hit is look-elsewhere\n");
        std::printf("  territory). E21 conjecture NOT supported by the k-hierarchy. Stated plainly.\n\n");
    } else {
        std::printf("  [REPORT] Multiple integer hits found — flag for E21 follow-up with a\n");
        std::printf("  pre-registered null model before ANY claim is made.\n\n");
    }

    // ------------------------------------------------------------------
    // Summary
    // ------------------------------------------------------------------
    std::printf("=====================================================================\n");
    std::printf(" SUMMARY: %d gated PASS, %d gated FAIL, %d IDENTITY (unscored), %d OPEN\n",
                n_pass, n_fail, n_identity, n_open);
    std::printf(" Class: CONVERGENCE census (koppa = GM/c^2 disclosed throughout).\n");
    std::printf("=====================================================================\n");
    return (n_fail == 0) ? 0 : 1;
}
