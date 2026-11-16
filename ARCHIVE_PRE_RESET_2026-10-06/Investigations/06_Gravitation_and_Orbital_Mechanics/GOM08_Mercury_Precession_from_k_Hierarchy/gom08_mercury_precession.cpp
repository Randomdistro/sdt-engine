// ============================================================================
//  GOM08 — Mercury Precession from k-Hierarchy
//  Pure calculation: reproduce 42.98"/century from SDT displacement gradient.
//
//  Author: James Christopher Tyndall, Melbourne.
//
//  The SDT effective potential for orbital motion contains a 1/r³ correction
//  term arising from the k-gradient (spation displacement profile). This term
//  is algebraically identical to standard GR's Schwarzschild correction because
//  the equivalent metric length scales (koppa ϟ = R_Sun/k_Sun² vs standard
//  GM/c²) are mapped exactly by the equivalence principle.
//
//  No mass or G is used in the calculations.
//
//  Methodology:
//    Step 1: Compute SDT precession per orbit δφ = 6π ϟ_Sun / (a(1-e²))
//            where ϟ_Sun = R_Sun / k_Sun²
//    Step 2: Convert to arcsec/century (×415.2 orbits/cy × 206265 arcsec/rad)
//    Step 3: Compare to standard field length parameter (koppa equivalent L = 1476.625 m)
//    Step 4: Verify algebraic identity of the precession formulas
//
//  Build (MSVC):
//    cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:gom08.exe gom08_mercury_precession.cpp
// ============================================================================

#include <sdt/laws.hpp>

#include <cstdio>
#include <cmath>
#include <numbers>

namespace {

constexpr double PI = std::numbers::pi;

// ── Parameter ledger ──────────────────────────────────────────────────────
//   R_Sun      : sdt::laws::measured::R_Sun     MEASURED-INPUT   6.957e8 m
//   k_Sun      : sdt::laws::bridge::k_Sun       DERIVED          686.3
//   c          : sdt::laws::measured::c          MEASURED-INPUT   299792458 m/s
//   a_Mercury  : sdt::laws::bridge::a_Mercury    MEASURED-INPUT   5.7909e10 m
//   e_Mercury  : sdt::laws::bridge::e_Mercury    MEASURED-INPUT   0.20563
//   orbits/cy  : sdt::laws::bridge::mercury_orbits_per_cy  DERIVED  415.2
//   NONE redefined; ALL sourced from engine.

// ── Mercury orbital parameters (from engine) ──────────────────────────────
constexpr double R_Sun     = sdt::laws::measured::R_Sun;
constexpr double k_Sun     = sdt::laws::bridge::k_Sun;
constexpr double c         = sdt::laws::measured::c;
constexpr double a_Merc    = sdt::laws::bridge::a_Mercury;
constexpr double e_Merc    = sdt::laws::bridge::e_Mercury;
constexpr double orbits_cy = sdt::laws::bridge::mercury_orbits_per_cy;

// Measured target
constexpr double TARGET_ARCSEC_CY = 42.98;

// Standard comparison: equivalent field length scale (GM/c^2 in legacy terminology)
// L_standard = 1476.62504 m
constexpr double L_standard = 1476.62504;

// Conversion
constexpr double RAD_TO_ARCSEC = 180.0 * 3600.0 / PI;

// ============================================================================
//  Step 1: SDT precession per orbit
// ============================================================================

struct PrecessionResult {
    double delta_phi_rad;      // per orbit [rad]
    double delta_phi_arcsec;   // per orbit [arcsec]
    double arcsec_per_century; // [arcsec/century]
};

PrecessionResult sdt_precession() {
    // SDT formula: δφ = 6π ϟ_Sun / (a(1-e²))
    // where ϟ_Sun = R_Sun / k_Sun²
    double k_sq = k_Sun * k_Sun;
    double koppa_Sun = R_Sun / k_sq;
    double one_minus_e2 = 1.0 - e_Merc * e_Merc;
    double delta_phi = 6.0 * PI * koppa_Sun / (a_Merc * one_minus_e2);

    PrecessionResult r{};
    r.delta_phi_rad      = delta_phi;
    r.delta_phi_arcsec   = delta_phi * RAD_TO_ARCSEC;
    r.arcsec_per_century = delta_phi * RAD_TO_ARCSEC * orbits_cy;
    return r;
}

// ============================================================================
//  Step 2: Standard precession per orbit (comparison)
// ============================================================================

PrecessionResult standard_precession() {
    // Standard formula using equivalent field length: δφ = 6π L_standard / (a(1-e²))
    double one_minus_e2 = 1.0 - e_Merc * e_Merc;
    double delta_phi = 6.0 * PI * L_standard / (a_Merc * one_minus_e2);

    PrecessionResult r{};
    r.delta_phi_rad      = delta_phi;
    r.delta_phi_arcsec   = delta_phi * RAD_TO_ARCSEC;
    r.arcsec_per_century = delta_phi * RAD_TO_ARCSEC * orbits_cy;
    return r;
}

// ============================================================================
//  Step 3: Field length identity verification: ϟ_Sun ≈ L_standard
// ============================================================================

struct IdentityCheck {
    double koppa_from_SDT;     // R_Sun / k²
    double koppa_from_standard; // L_standard (JPL DE430 equivalent)
    double rel_error;
    bool   passes;
};

IdentityCheck verify_identity() {
    double koppa_sdt = R_Sun / (k_Sun * k_Sun);

    IdentityCheck ic{};
    ic.koppa_from_SDT      = koppa_sdt;
    ic.koppa_from_standard = L_standard;
    ic.rel_error           = std::abs(koppa_sdt - L_standard) / L_standard;
    ic.passes              = (ic.rel_error < 0.001);
    return ic;
}

// ============================================================================
//  Step 4: k_Sun verification from engine's k_from_precession
// ============================================================================

struct KVerification {
    double k_from_engine;
    double k_hardcoded;
    double rel_error;
};

KVerification verify_k() {
    KVerification kv{};
    kv.k_from_engine = sdt::laws::bridge::k_Sun_from_precession;
    kv.k_hardcoded   = k_Sun;
    kv.rel_error     = std::abs(kv.k_from_engine - kv.k_hardcoded) / kv.k_hardcoded;
    return kv;
}

} // anonymous namespace

int main() {
    std::printf("================================================================\n");
    std::printf("  GOM08 — Mercury Precession from k-Hierarchy\n");
    std::printf("  Target: 42.98 arcsec/century (± 0.1)\n");
    std::printf("  Physics: Pressurised occlusion & displacement gradient (NO MASS)\n");
    std::printf("================================================================\n\n");

    // ── Step 1: SDT precession ──────────────────────────────────────────
    auto sdt = sdt_precession();
    std::printf("STEP 1: SDT Precession (from k-hierarchy)\n");
    std::printf("  Formula: delta_phi = 6 pi ϟ_Sun / (a * (1-e^2))\n");
    std::printf("  Inputs:\n");
    std::printf("    R_Sun       = %.4e m\n", R_Sun);
    std::printf("    k_Sun       = %.1f\n", k_Sun);
    std::printf("    ϟ_Sun (R/k²)= %.6f m\n", R_Sun / (k_Sun * k_Sun));
    std::printf("    a_Mercury   = %.4e m\n", a_Merc);
    std::printf("    e_Mercury   = %.5f\n", e_Merc);
    std::printf("    1 - e^2     = %.6f\n", 1.0 - e_Merc * e_Merc);
    std::printf("    orbits/cy   = %.2f\n", orbits_cy);
    std::printf("  Results:\n");
    std::printf("    delta_phi   = %.6e rad/orbit\n", sdt.delta_phi_rad);
    std::printf("    delta_phi   = %.6f arcsec/orbit\n", sdt.delta_phi_arcsec);
    std::printf("    PRECESSION  = %.4f arcsec/century\n", sdt.arcsec_per_century);
    std::printf("    Target      = %.2f arcsec/century\n", TARGET_ARCSEC_CY);
    double sdt_err = std::abs(sdt.arcsec_per_century - TARGET_ARCSEC_CY);
    std::printf("    |SDT - target| = %.4f arcsec/century\n", sdt_err);
    std::printf("    STATUS: %s (threshold: 0.1 arcsec/century)\n\n",
                sdt_err < 0.1 ? "PASS" : "FAIL");

    // ── Step 2: Standard Precession Comparison ──────────────────────────
    auto std_prec = standard_precession();
    std::printf("STEP 2: Standard Precession (comparison)\n");
    std::printf("  Formula: delta_phi = 6 pi L_standard / (a * (1-e^2))\n");
    std::printf("  Inputs:\n");
    std::printf("    L_standard  = %.5f m\n", L_standard);
    std::printf("  Results:\n");
    std::printf("    delta_phi   = %.6e rad/orbit\n", std_prec.delta_phi_rad);
    std::printf("    delta_phi   = %.6f arcsec/orbit\n", std_prec.delta_phi_arcsec);
    std::printf("    PRECESSION  = %.4f arcsec/century\n", std_prec.arcsec_per_century);
    double std_err = std::abs(std_prec.arcsec_per_century - TARGET_ARCSEC_CY);
    std::printf("    |Std - target| = %.4f arcsec/century\n", std_err);
    std::printf("    STATUS: %s\n\n", std_err < 0.1 ? "PASS" : "FAIL");

    // ── Step 3: SDT vs Standard agreement ─────────────────────────────────────
    double sdt_gr_diff = std::abs(sdt.arcsec_per_century - std_prec.arcsec_per_century);
    double sdt_gr_rel  = sdt_gr_diff / std_prec.arcsec_per_century;
    std::printf("STEP 3: SDT vs Standard Agreement\n");
    std::printf("  |SDT - Standard| = %.6f arcsec/century\n", sdt_gr_diff);
    std::printf("  Relative         = %.6e\n", sdt_gr_rel);
    std::printf("  STATUS: %s (algebraic identity expected from Equivalence Principle)\n\n",
                sdt_gr_rel < 5e-4 ? "AGREES (< 0.05%)" : "DIVERGENT");

    // ── Step 4: Field Length Identity Verification (ϟ = L_standard) ─────────
    auto ic = verify_identity();
    std::printf("STEP 4: Field Length Identity Verification (ϟ_Sun = L_standard)\n");
    std::printf("  ϟ_SDT   = R_Sun / k_Sun^2 = %.6f m\n", ic.koppa_from_SDT);
    std::printf("  L_std   = %.6f m\n", ic.koppa_from_standard);
    std::printf("  Rel err = %.6f%%\n", ic.rel_error * 100.0);
    std::printf("  STATUS: %s\n\n", ic.passes ? "PASS (< 0.1%)" : "FAIL (> 0.1%)");

    // ── Step 5: k_Sun from precession (engine function) ─────────────────
    auto kv = verify_k();
    std::printf("STEP 5: k_Sun Recovery from Precession (GOM04 closure)\n");
    std::printf("  k_from_precession = %.4f\n", kv.k_from_engine);
    std::printf("  k_hardcoded       = %.1f\n", kv.k_hardcoded);
    std::printf("  Rel err           = %.6f%%\n", kv.rel_error * 100.0);
    std::printf("  c_from_closure    = %.6e m/s\n", sdt::laws::bridge::c_from_closure);
    std::printf("  c_measured        = %.6e m/s\n", c);
    double c_err = std::abs(sdt::laws::bridge::c_from_closure - c) / c * 100.0;
    std::printf("  c_error           = %.4f%%\n\n", c_err);

    // ── Step 6: Discussion ───────────────────────────────────
    std::printf("STEP 6: Where SDT and Standard Physics Could Diverge\n");
    std::printf("  The algebraic identity of the precession formulas arises because\n");
    std::printf("  the equivalent field length scales (ϟ vs GM/c²) agree to 0.03%%.\n");
    std::printf("  Under the Equivalence Principle, any formalism matching the standard\n");
    std::printf("  precession must be algebraically identical in spherically symmetric limits.\n");
    std::printf("  Divergence could occur in:\n");
    std::printf("  (a) Test bodies with significant internal displacement fields (k-coupling)\n");
    std::printf("  (b) Strong field dynamics (k ~ 1) at higher post-Newtonian orders\n");
    std::printf("  (c) Non-spherical geometries, where the local occlusion integrals\n");
    std::printf("      differ from standard multipole expansions\n\n");

    // ── Final verdict ───────────────────────────────────────────────────
    bool all_pass = (sdt_err < 0.1) && ic.passes && (sdt_gr_rel < 5e-4);
    std::printf("================================================================\n");
    std::printf("  VERDICT: %s\n", all_pass ? "PASS — Class C (CONVERGENCE)" : "FAIL");
    std::printf("  SDT precession = %.4f arcsec/cy (target: %.2f)\n",
                sdt.arcsec_per_century, TARGET_ARCSEC_CY);
    std::printf("  Classification: CONVERGENCE — the result matches standard observations\n");
    std::printf("  because the field length ϟ = R/k² is the single descriptor of the\n");
    std::printf("  displacement gradient. SDT uses no mass or G in calculations,\n");
    std::printf("  relying purely on geometry. CALIBRATED(0) — no free parameters.\n");
    std::printf("================================================================\n");

    return all_pass ? 0 : 1;
}
