/**
 * @file spherical_packing.cpp
 * @brief SDT Spherical Packing Engine — Diagnostic Console Tool
 *
 * Loads all 10 preset packing geometries, prints complete diagnostic
 * reports, and validates coordinate integrity. Cross-references with
 * nuclear construction grammar identities where applicable.
 *
 * Presets map to nuclear configurations:
 *   tammes-4     → He-4 alpha core (tetrahedron)
 *   tammes-6     → O-16 deuteron octahedral shell
 *   platonic-cube → Ca-40 cubic shell
 *   cuboct-12    → Fe-56 alpha cluster (Vector Equilibrium)
 *   cuboct-plugged → Fe-56 with interstitial neutrons
 *
 * Compile (from project root):
 *   cmake -S . -B build && cmake --build build --target sdt-spherical-packing
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 * @date April 2026
 */

#include <sdt/packing.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::packing;

// ═══════════════════════════════════════════════════════════════════════
//  VALIDATION TESTS
// ═══════════════════════════════════════════════════════════════════════

struct TestResult {
    const char* name;
    bool passed;
    double value;
    double expected;
    double tolerance;
};

static int g_pass = 0;
static int g_fail = 0;

static void check(const char* name, double value, double expected, double tolerance) {
    bool ok = std::abs(value - expected) < tolerance;
    if (ok) {
        std::printf("    [PASS] %-40s  %.6f ≈ %.6f\n", name, value, expected);
        g_pass++;
    } else {
        std::printf("    [FAIL] %-40s  %.6f ≠ %.6f (Δ=%.2e)\n",
            name, value, expected, std::abs(value - expected));
        g_fail++;
    }
}

static void check_int(const char* name, int value, int expected) {
    if (value == expected) {
        std::printf("    [PASS] %-40s  %d == %d\n", name, value, expected);
        g_pass++;
    } else {
        std::printf("    [FAIL] %-40s  %d ≠ %d\n", name, value, expected);
        g_fail++;
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  NUCLEAR GRAMMAR CROSS-REFERENCE
// ═══════════════════════════════════════════════════════════════════════

struct NuclearMapping {
    const char* preset;
    const char* nucleus;
    int Z, A;
    int n_deu, n_tri;
    int expected_scaffolds;     // number of outer spheres representing scaffold blocks
    const char* geometry;
};

static const NuclearMapping nuclear_map[] = {
    {"tammes-4",       "He-4",   2,  4, 0, 0,  4,  "tetrahedron (4 vertices → 2p+2n scaffold)"},
    {"tammes-6",       "O-16",   8, 16, 6, 0,  6,  "octahedron (6 deuterons around alpha)"},
    {"platonic-cube",  "Ca-40", 20, 40, 16, 2,  8,  "cube (8 vertices → 2×alpha sub-clusters)"},
    {"cuboct-12",      "Fe-56", 26, 56, 20, 4, 12,  "cuboctahedron (12 → 13-alpha Vector Equilibrium)"},
};
static constexpr int N_NUCLEAR = sizeof(nuclear_map) / sizeof(nuclear_map[0]);

// ═══════════════════════════════════════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════════════════════════════════════

int main() {
    std::printf("======================================================================\n");
    std::printf("  SDT SPHERICAL PACKING ENGINE — DIAGNOSTIC REPORT\n");
    std::printf("  Pure spherical coordinates. Zero external dependencies.\n");
    std::printf("  10 preset geometries. Nuclear grammar cross-reference.\n");
    std::printf("======================================================================\n\n");

    // ── PART 1: ALL PRESETS ──
    std::printf("══════════════════════════════════════════════════════════════════\n");
    std::printf("  PART 1: COMPLETE PRESET REPORTS\n");
    std::printf("══════════════════════════════════════════════════════════════════\n\n");

    for (int i = 0; i < NUM_PRESETS; ++i) {
        auto cfg = load_preset(PRESET_NAMES[i]);
        packing_report(cfg);
    }

    // ── PART 2: STRUCTURAL VALIDATION ──
    std::printf("══════════════════════════════════════════════════════════════════\n");
    std::printf("  PART 2: STRUCTURAL VALIDATION\n");
    std::printf("══════════════════════════════════════════════════════════════════\n\n");

    // Tammes-4 (tetrahedron): 4 outers, angular separation ≈ 109.471°
    {
        auto cfg = preset_tammes4();
        std::printf("  tammes-4 (tetrahedron / He-4):\n");
        check_int("sphere count", static_cast<int>(cfg.outers.size()), 4);
        auto pair = min_angular_pair(cfg);
        check("min angular separation (°)", pair.angle * DEG_PER_RAD, 109.471, 0.5);
    }

    // Tammes-6 (octahedron): 6 outers, angular separation = 90°
    {
        auto cfg = preset_tammes6();
        std::printf("\n  tammes-6 (octahedron / O-16):\n");
        check_int("sphere count", static_cast<int>(cfg.outers.size()), 6);
        auto pair = min_angular_pair(cfg);
        check("min angular separation (°)", pair.angle * DEG_PER_RAD, 90.0, 0.1);
    }

    // Cuboctahedron n=12: 12 outers, r = 2.0, kissing gap ≈ 0
    {
        auto cfg = preset_cuboct12();
        std::printf("\n  cuboct-12 (cuboctahedron / Fe-56 core):\n");
        check_int("sphere count", static_cast<int>(cfg.outers.size()), 12);
        check("radial distance (r)", cfg.outers[0].pos.r, 2.0, 0.001);
        double gap = central_outer_gap(cfg, 0);
        check("central-outer gap", gap, 0.0, 0.001);
        auto kp = kissing_pairs(cfg);
        std::printf("    [INFO] kissing pairs found: %d\n", static_cast<int>(kp.size()));
    }

    // Cuboct + plugs: 12 + 6 + 8 = 26 total
    {
        auto cfg = preset_cuboct_plugged();
        std::printf("\n  cuboct-plugged (Fe-56 full):\n");
        check_int("sphere count", static_cast<int>(cfg.outers.size()), 26);
        // Count by shell
        int s0 = 0, s1 = 0, s2 = 0;
        for (auto& s : cfg.outers) {
            if (s.shell == 0) s0++;
            else if (s.shell == 1) s1++;
            else if (s.shell == 2) s2++;
        }
        check_int("shell-0 (cuboct)", s0, 12);
        check_int("shell-1 (oct plugs)", s1, 6);
        check_int("shell-2 (tet plugs)", s2, 8);
    }

    // Cube: 8 outers
    {
        auto cfg = preset_cube8();
        std::printf("\n  platonic-cube (Ca-40):\n");
        check_int("sphere count", static_cast<int>(cfg.outers.size()), 8);
    }

    // Dodecahedron: 20 outers
    {
        auto cfg = preset_dodec20();
        std::printf("\n  platonic-dodec:\n");
        check_int("sphere count", static_cast<int>(cfg.outers.size()), 20);
    }

    // Tammes-12 (icosahedron): 12 outers
    {
        auto cfg = preset_tammes12();
        std::printf("\n  tammes-12 (icosahedron):\n");
        check_int("sphere count", static_cast<int>(cfg.outers.size()), 12);
    }

    // ── PART 3: COORDINATE ROUND-TRIP INTEGRITY ──
    std::printf("\n══════════════════════════════════════════════════════════════════\n");
    std::printf("  PART 3: COORDINATE ROUND-TRIP INTEGRITY\n");
    std::printf("══════════════════════════════════════════════════════════════════\n\n");

    double worst_err = 0.0;
    const char* worst_preset = "";

    for (int i = 0; i < NUM_PRESETS; ++i) {
        auto cfg = load_preset(PRESET_NAMES[i]);
        double max_err = 0.0;
        for (auto& s : cfg.outers) {
            double err = roundtrip_error(s.pos);
            if (err > max_err) max_err = err;
        }
        std::printf("    %-25s  max roundtrip err = %.2e  %s\n",
            PRESET_NAMES[i], max_err,
            max_err < 1e-12 ? "[PASS]" : "[WARN]");

        if (max_err < 1e-12) g_pass++; else g_fail++;

        if (max_err > worst_err) {
            worst_err = max_err;
            worst_preset = PRESET_NAMES[i];
        }
    }
    std::printf("\n    Worst case: %s  (%.2e)\n", worst_preset, worst_err);

    // ── PART 4: NUCLEAR GRAMMAR CROSS-REFERENCE ──
    std::printf("\n══════════════════════════════════════════════════════════════════\n");
    std::printf("  PART 4: NUCLEAR GRAMMAR CROSS-REFERENCE\n");
    std::printf("══════════════════════════════════════════════════════════════════\n\n");

    std::printf("  %-16s  %-6s  %3s  %3s  %3s  %3s  %5s  %-s\n",
        "Preset", "Nucl.", "Z", "A", "d", "t", "n_out", "Geometry");
    std::printf("  %-16s  %-6s  %3s  %3s  %3s  %3s  %5s  %-s\n",
        "────────────────", "──────", "───", "───", "───", "───", "─────", "──────────");

    for (int i = 0; i < N_NUCLEAR; ++i) {
        auto& nm = nuclear_map[i];
        auto cfg = load_preset(nm.preset);
        int actual = static_cast<int>(cfg.outers.size());

        std::printf("  %-16s  %-6s  %3d  %3d  %3d  %3d  %5d  %s\n",
            nm.preset, nm.nucleus, nm.Z, nm.A, nm.n_deu, nm.n_tri,
            actual, nm.geometry);

        check_int("  scaffold count matches", actual, nm.expected_scaffolds);
    }

    // ── SUMMARY ──
    std::printf("\n══════════════════════════════════════════════════════════════════\n");
    std::printf("  SUMMARY\n");
    std::printf("══════════════════════════════════════════════════════════════════\n\n");
    std::printf("    Tests passed: %d\n", g_pass);
    std::printf("    Tests FAILED: %d\n", g_fail);
    std::printf("    Status: %s\n\n", g_fail == 0 ? "ALL CLEAR ✓" : "ISSUES FOUND ✗");

    std::printf("======================================================================\n");
    std::printf("  SDT SPHERICAL PACKING ENGINE — INVESTIGATION COMPLETE\n");
    std::printf("======================================================================\n");

    return g_fail > 0 ? 1 : 0;
}
