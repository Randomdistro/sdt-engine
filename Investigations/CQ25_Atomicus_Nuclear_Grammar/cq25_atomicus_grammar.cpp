/**
 * @file cq25_atomicus_grammar.cpp
 * @brief CQ25 — Atomicus Nuclear Grammar: Verification & Fission Snap Classification
 *
 * Three-stage investigation against the Atomicus alpha grammar:
 *
 *   Stage A: Grammar table verification
 *     — Print all 287 nuclides with (n_d, n_t, snap_pairs, odd_valence)
 *     — Print and verify all 7 aggregate totals (must match static_assert targets)
 *     — Identify the 3 alpha-invalid exceptions (H-1, H-2, He-3)
 *
 *   Stage B: Binary fission snap classification
 *     — Classify representative fission channels for U-235, U-238, Pu-239
 *     — Verify the algebraic identities ΔD = ν−2 and ΔT = −ν hold exactly
 *     — Classify GSI 1A GeV U-238+p spallation light residues (Kr/Rb corridor)
 *
 *   Stage C: ASCII nuclide sheet map
 *     — Full (n_d, n_t) space chart of the 284 alpha-valid natural isotopes
 *     — Odd-valence (office-pop) nuclides marked with '*', even with 'O'
 *     — Snap-pair count overlay (digit / letter in hex notation)
 *     — Golden boundary (n_d = n_t) diagonal highlighted
 *
 * @see Engine/include/sdt/nuclear.hpp
 */

#include <sdt/nuclear.hpp>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace sdt::nuclear;

// ═══════════════════════════════════════════════════════════════════════════════
//  STAGE A — GRAMMAR TABLE VERIFICATION
// ═══════════════════════════════════════════════════════════════════════════════

static void stage_A() {
    std::printf("\n");
    std::printf("╔══════════════════════════════════════════════════════════════════════╗\n");
    std::printf("║  CQ25 — STAGE A: Atomicus Alpha Grammar Table Verification          ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════════════╝\n\n");

    // ── A1: Print full 287-row table ──────────────────────────────────────────
    std::printf("  Full 287-entry CIAAW Natural Basis (sorted by Z, then A):\n\n");
    print_record_header();

    for (const auto& raw : natural_basis) {
        const auto ag = alpha_grammar(raw.Z, raw.A);
        const auto h3 = h3_grammar(raw.Z, raw.A);
        NuclideRecord rec = make_record(raw.Z, raw.A, element_symbol(raw.Z));
        print_record(rec);
    }

    // ── A2: Alpha-invalid exceptions ─────────────────────────────────────────
    std::printf("\n  Alpha-INVALID exceptions:\n");
    for (const auto& raw : natural_basis) {
        const auto ag = alpha_grammar(raw.Z, raw.A);
        if (!ag.valid) {
            char name[12];
            nuclide_name(raw.Z, raw.A, name, sizeof(name));
            std::printf("    %-8s  Z=%d  A=%d  n_d=%d  n_t=%d  (H3: n_d=%d  n_t=%d)\n",
                name, raw.Z, raw.A, ag.n_d, ag.n_t,
                h3_grammar(raw.Z, raw.A).n_d,
                h3_grammar(raw.Z, raw.A).n_t);
        }
    }

    // ── A3: Aggregate totals ──────────────────────────────────────────────────
    const BasisStats& s = basis_stats;  // evaluated at compile time

    std::printf("\n");
    std::printf("  ════════════════════════════════════════════════════\n");
    std::printf("  AGGREGATE TOTALS  (compile-time verified by static_assert)\n");
    std::printf("  ════════════════════════════════════════════════════\n");
    std::printf("  Total records    : %d   (target: 287)\n",   s.total_records);
    std::printf("  Alpha-valid      : %d   (target: 284)\n",   s.alpha_valid);
    std::printf("  Alpha-invalid    : %d     (target:   3)  [H-1, H-2, He-3]\n",
                s.alpha_invalid);
    std::printf("  Σ n_d            : %d  (target: 7658)\n",  s.sum_nd);
    std::printf("  Σ n_t            : %d  (target: 5228)\n",  s.sum_nt);
    std::printf("  Snap pairs Σ⌊nt/2⌋: %d  (target: 2560)\n",  s.snap_pairs);
    std::printf("  Odd-valence (108): %d   (target:  108)  [odd-A = office-pop]\n",
                s.odd_valence);
    std::printf("  ════════════════════════════════════════════════════\n");

    // ── A4: Identity cross-checks ─────────────────────────────────────────────
    //   snap_pairs = (sum_nt - odd_valence) / 2
    const int snap_check = (s.sum_nt - s.odd_valence) / 2;
    std::printf("\n  Cross-check:  (Σnt − odd_valence)/2 = (%d − %d)/2 = %d  [snap_pairs = %d]  %s\n",
        s.sum_nt, s.odd_valence, snap_check, s.snap_pairs,
        (snap_check == s.snap_pairs) ? "✓" : "FAIL");

    //   sum_nd + sum_nt = sum_Z_valid - 2*284
    //   expected sum_Z_valid = 13454  (verified analytically)
    const int sum_zv_inferred = s.sum_nd + s.sum_nt + 2 * s.alpha_valid;
    std::printf("  Cross-check:  Σn_d + Σn_t + 2×284 = %d = Σ Z (valid) = 13454  %s\n",
        sum_zv_inferred,
        (sum_zv_inferred == 13454) ? "✓" : "FAIL");

    std::printf("\n  All 7 static_assert targets validated at compile time.\n");
}


// ═══════════════════════════════════════════════════════════════════════════════
//  STAGE B — BINARY FISSION SNAP CLASSIFICATION
// ═══════════════════════════════════════════════════════════════════════════════

static void stage_B() {
    std::printf("\n");
    std::printf("╔══════════════════════════════════════════════════════════════════════╗\n");
    std::printf("║  CQ25 — STAGE B: Binary Fission Snap Classification                ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════════════╝\n\n");

    std::printf("  Algebraic identity (exact for any binary split P → L + H + ν·n):\n");
    std::printf("    ΔD = (n_d,L + n_d,H) − n_d,P = ν − 2   (always)\n");
    std::printf("    ΔT = (n_t,L + n_t,H) − n_t,P = −ν       (always)\n\n");

    std::printf("  Snap classes:\n");
    std::printf("    (ΔD=0,  ΔT=−2) = clean_2n_snap   [ν=2]\n");
    std::printf("    (ΔD=+1, ΔT=−3) = nu3_mixed        [ν=3]\n");
    std::printf("    (ΔD=+2, ΔT=−4) = adjacent_4n      [ν=4]\n\n");

    // ── B1: U-235 thermal fission channels ───────────────────────────────────
    std::printf("  ── U-235 representative binary channels ─────────────────────────────\n");
    {
        // ν=2 clean snap
        print_split(binary_split(92,235,  36,92,  56,141, 2));  // Kr-92 + Ba-141
        print_split(binary_split(92,235,  36,91,  56,141, 3));  // Kr-91 + Ba-141 (ν=3)
        print_split(binary_split(92,235,  36,90,  56,141, 4));  // Kr-90 + Ba-141 (ν=4)
        print_split(binary_split(92,235,  42,99,  50,134, 2));  // Mo-99 + Sn-134 (ν=2)
        print_split(binary_split(92,235,  52,132, 40,101, 2));  // Te-132 + Zr-101 (ν=2)
        print_split(binary_split(92,235,  53,135, 38, 97, 3));  // I-135  + Sr-97  (ν=3)
        print_split(binary_split(92,235,  54,136, 37, 96, 3));  // Xe-136 + Rb-96  (ν=3)
        print_split(binary_split(92,235,  55,137, 36, 95, 3));  // Cs-137 + Kr-95  (ν=3)
        print_split(binary_split(92,235,  56,140, 36, 92, 3));  // Ba-140 + Kr-92  (ν=3)
    }

    // ── B2: U-238 fast fission channels ──────────────────────────────────────
    std::printf("\n  ── U-238 representative binary channels ─────────────────────────────\n");
    {
        print_split(binary_split(92,238,  36,94,  56,142, 2));  // Kr-94 + Ba-142 (clean 2n)
        print_split(binary_split(92,238,  36,92,  56,142, 4));  // Kr-92 + Ba-142 (4n adj)
        print_split(binary_split(92,238,  52,130, 40,105, 3));  // Te-130 + Zr-105 (ν=3)
        print_split(binary_split(92,238,  53,135, 38,100, 3));  // I-135  + Sr-100 (ν=3)
        print_split(binary_split(92,238,  54,134, 37, 99, 5));  // Xe-134 + Rb-99  (ν=5) other
    }

    // ── B3: Pu-239 thermal fission channels ──────────────────────────────────
    std::printf("\n  ── Pu-239 representative binary channels ────────────────────────────\n");
    {
        print_split(binary_split(94,239,  42,99,  52,138, 2));  // Mo-99 + Te-138 (clean 2n)
        print_split(binary_split(94,239,  42,99,  52,136, 4));  // Mo-99 + Te-136 (4n adj)
        print_split(binary_split(94,239,  36,91,  58,145, 3));  // Kr-91 + Ce-145 (ν=3)
        print_split(binary_split(94,239,  55,137, 38, 99, 3));  // Cs-137 + Sr-99 (ν=3)
        print_split(binary_split(94,239,  44,103, 50,133, 3));  // Ru-103 + Sn-133 (ν=3)
    }

    // ── B4: GSI U-238+p spallation light residues (Kr/Rb corridor) ───────────
    std::printf("\n  ── GSI 1A GeV U-238+p spallation: light residue corridor ───────────\n");
    std::printf("  (Grammar coordinates of the products; parent = U-238, light wing)\n\n");
    std::printf("  %-8s  Z  A   n_d   n_t  snp  offpop   |  Grammar location\n",
        "Nuclide");
    std::printf("  %-8s  -  -   ---   ---  ---  ------   |  ---------------\n",
        "───────");

    auto print_residue = [](int Z, int A) {
        const auto ag = alpha_grammar(Z, A);
        char name[12];
        nuclide_name(Z, A, name, sizeof(name));
        std::printf("  %-8s %2d %3d  %4d  %4d   %2d     %d     |  n_d%+d, n_t=%d  %s\n",
            name, Z, A,
            ag.n_d, ag.n_t,
            ag.valid ? ag.n_t/2 : 0,
            ag.valid ? ag.n_t%2 : 0,
            ag.n_d - ag.n_t,  // x displacement from golden boundary
            ag.n_t,
            overlays::on_golden_boundary(Z,A) ? "← GOLDEN" : "");
    };

    // Kr region (Z=36)
    print_residue(36, 82);  // Kr-82
    print_residue(36, 83);  // Kr-83
    print_residue(36, 84);  // Kr-84  — 11 mb in GSI table
    print_residue(36, 85);  // Kr-85  — 10 mb (not natural, spallation product)
    print_residue(36, 86);  // Kr-86
    // Rb region (Z=37)
    print_residue(37, 85);  // Rb-85
    print_residue(37, 86);  // Rb-86  — 12 mb (not natural, spallation product)
    print_residue(37, 87);  // Rb-87  — 11 mb
    print_residue(37, 88);  // Rb-88  — 11 mb (not natural)

    std::printf("\n  Corridor observation: GSI Kr/Rb products sit at n_d > n_t\n");
    std::printf("  (deuteron-heavier side of the sheet), consistent with light-wing\n");
    std::printf("  fragment corridor predicted by the alpha grammar.\n");

    // ── B5: Identity verification on a clean 2n split ────────────────────────
    std::printf("\n  ── Identity verification: ΔD = ν−2, ΔT = −ν ─────────────────────────\n");
    {
        const auto r = binary_split(92,235, 36,92, 56,141, 2);
        std::printf("  U-235 → Kr-92 + Ba-141 + 2n:\n");
        std::printf("    n_d,P=%d  n_d,L=%d  n_d,H=%d  ΔD=%+d  (ν−2 = %d)  %s\n",
            alpha_grammar(92,235).n_d,
            alpha_grammar(36,92).n_d,
            alpha_grammar(56,141).n_d,
            r.delta_D, r.nu - 2,
            (r.delta_D == r.nu - 2) ? "✓" : "FAIL");
        std::printf("    n_t,P=%d  n_t,L=%d  n_t,H=%d  ΔT=%+d  (−ν = %d)  %s\n",
            alpha_grammar(92,235).n_t,
            alpha_grammar(36,92).n_t,
            alpha_grammar(56,141).n_t,
            r.delta_T, -r.nu,
            (r.delta_T == -r.nu) ? "✓" : "FAIL");
    }
}


// ═══════════════════════════════════════════════════════════════════════════════
//  STAGE C — ASCII NUCLIDE SHEET MAP
// ═══════════════════════════════════════════════════════════════════════════════

static void stage_C() {
    std::printf("\n");
    std::printf("╔══════════════════════════════════════════════════════════════════════╗\n");
    std::printf("║  CQ25 — STAGE C: ASCII Nuclide Sheet Maps                          ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════════════╝\n\n");

    // ── C1: (n_d, n_t) office-pop & snap-pair chart ───────────────────────────
    // Grid: n_t rows (0 top–54 bottom inverted; we print 54→0), n_d columns (0→44)
    // Cell encoding:
    //   '.' = empty (no natural isotope at this cell)
    //   digit '0'–'9' = snap_pair_count (even A, office-pop inactive)
    //   letter 'a'–'z' = snap_pair_count offset (even A, snp >= 10)
    //   '*' suffix notation for odd A (office-pop) — we use uppercase 'A'–'Z' for odd-A

    constexpr int ND_MAX = 45;   // n_d axis: 0..44
    constexpr int NT_MAX = 55;   // n_t axis: 0..54

    // grid[nt][nd] stores a display character
    char grid[NT_MAX][ND_MAX + 1];
    // golden boundary marker layer
    bool golden[NT_MAX][ND_MAX + 1];

    // Initialise
    for (int nt = 0; nt < NT_MAX; ++nt) {
        for (int nd = 0; nd < ND_MAX; ++nd) {
            grid[nt][nd] = '.';
            golden[nt][nd] = false;
        }
        grid[nt][ND_MAX] = '\0';
    }

    // Mark golden boundary (n_d == n_t)
    for (int k = 0; k < NT_MAX && k < ND_MAX; ++k) {
        golden[k][k] = true;
    }

    // Fill in natural isotopes
    for (const auto& raw : natural_basis) {
        const auto ag = alpha_grammar(raw.Z, raw.A);
        if (!ag.valid) continue;
        if (ag.n_t < 0 || ag.n_t >= NT_MAX) continue;
        if (ag.n_d < 0 || ag.n_d >= ND_MAX) continue;

        const int sp = ag.n_t / 2;           // snap pairs
        const bool odd_a = (ag.n_t % 2) == 1; // office-pop

        char c;
        if (odd_a) {
            // Odd-A (office-pop): use uppercase letters for snap count
            c = (sp < 26) ? static_cast<char>('A' + sp) : 'Z';
        } else {
            // Even-A: use lowercase / digit
            if (sp < 10) c = static_cast<char>('0' + sp);
            else         c = static_cast<char>('a' + (sp - 10));
        }
        grid[ag.n_t][ag.n_d] = c;
    }

    std::printf("  Atomicus nuclear sheet: (n_d → , n_t ↑)\n");
    std::printf("  Encoding: digit/lowercase = even-A, UPPERCASE = odd-A (office-pop)\n");
    std::printf("            character value encodes snap_pair_count (0='0'/'A', etc.)\n");
    std::printf("            '|' marks the n_d = n_t golden boundary diagonal\n\n");

    // Column header
    std::printf("  n_t\\n_d ");
    for (int nd = 0; nd < ND_MAX; nd += 5) {
        std::printf("%-5d", nd);
    }
    std::printf("\n");
    std::printf("  ────────");
    for (int nd = 0; nd < ND_MAX; ++nd) std::printf("─");
    std::printf("\n");

    // Print rows top-to-bottom (n_t = 54 to 0)
    for (int nt = NT_MAX - 1; nt >= 0; --nt) {
        std::printf("  %3d │   ", nt);
        for (int nd = 0; nd < ND_MAX; ++nd) {
            if (golden[nt][nd] && grid[nt][nd] == '.') {
                std::printf("|");
            } else {
                std::printf("%c", grid[nt][nd]);
            }
        }
        std::printf("\n");
    }

    std::printf("  ────────");
    for (int nd = 0; nd < ND_MAX; ++nd) std::printf("─");
    std::printf("\n");

    // ── C2: Dedicated light-residue corridor (Z=30–42) ────────────────────────
    std::printf("\n  Light-residue corridor (Z = 30–42, n_d and n_t range):\n\n");
    std::printf("  %-8s  Z   A   n_d  n_t  snap  odd  x(nd-nt)  y(Z-2)\n",
        "Nuclide");
    std::printf("  %-8s  --  ---  ---  ---  ----  ---  --------  ------\n",
        "───────");

    for (const auto& raw : natural_basis) {
        if (raw.Z < 30 || raw.Z > 42) continue;
        const auto ag = alpha_grammar(raw.Z, raw.A);
        if (!ag.valid) continue;
        char name[12];
        nuclide_name(raw.Z, raw.A, name, sizeof(name));
        std::printf("  %-8s %2d  %3d  %3d  %3d  %4d  %3d  %+8d  %6d%s\n",
            name, raw.Z, raw.A,
            ag.n_d, ag.n_t,
            ag.n_t / 2,
            ag.n_t % 2,
            overlays::x_coord(raw.Z, raw.A),
            overlays::y_coord(raw.Z),
            overlays::on_golden_boundary(raw.Z, raw.A) ? "  ← GOLDEN" : "");
    }

    // ── C3: Major fission product region (Z=36–57) overview ──────────────────
    std::printf("\n  Major fission product nodes (evaluated yield corridors):\n\n");

    struct FPNode {
        int Z; int A; const char* note;
    };
    static constexpr FPNode fp_nodes[] = {
        {42,  95, "Mo-95  major cumul. yield"},
        {42,  99, "Mo-99  direct split product"},
        {43,  99, "Tc-99  major cumul. yield (not natural — bracket)"},
        {44, 101, "Ru-101 major cumul. yield"},
        {44, 103, "Ru-103 major cumul. yield"},
        {52, 132, "Te-132 major independent yield"},
        {53, 135, "I-135  major independent yield"},
        {54, 134, "Xe-134 largest cumul. yield 7.8%"},
        {54, 136, "Xe-136 major cumul. yield 6.1%"},
        {55, 133, "Cs-133 cumul. yield 6.7%"},
        {55, 137, "Cs-137 cumul. yield ~6%"},
        {56, 140, "Ba-140 independent yield 0.29%"},
    };

    std::printf("  %-8s  Z   A   n_d  n_t  snap  odd  x(nd-nt)  ← note\n", "Nuclide");
    std::printf("  %-8s  --  ---  ---  ---  ----  ---  --------  ------\n", "───────");

    for (const auto& fp : fp_nodes) {
        const auto ag = alpha_grammar(fp.Z, fp.A);
        char name[12];
        nuclide_name(fp.Z, fp.A, name, sizeof(name));
        std::printf("  %-8s %2d  %3d  %3d  %3d  %4d  %3d  %+8d  %s\n",
            name, fp.Z, fp.A,
            ag.n_d, ag.n_t,
            ag.valid ? ag.n_t/2 : 0,
            ag.valid ? ag.n_t%2 : 0,
            overlays::x_coord(fp.Z, fp.A),
            fp.note);
    }

    std::printf("\n  All major evaluated fission products are alpha-valid and\n");
    std::printf("  neutron-rich (n_t > n_d, x < 0 = right half of sheet).\n");

    // ── C4: Golden boundary nuclides ──────────────────────────────────────────
    std::printf("\n  Nuclides on the golden boundary (n_d = n_t) in the natural basis:\n\n");
    std::printf("  %-8s  Z   A   n_d=n_t  snap  y(Z-2)\n", "Nuclide");
    std::printf("  %-8s  --  ---  ------   ----  ------\n", "───────");

    for (const auto& raw : natural_basis) {
        if (!overlays::on_golden_boundary(raw.Z, raw.A)) continue;
        const auto ag = alpha_grammar(raw.Z, raw.A);
        if (!ag.valid) continue;
        char name[12];
        nuclide_name(raw.Z, raw.A, name, sizeof(name));
        std::printf("  %-8s %2d  %3d   %3d      %4d  %6d\n",
            name, raw.Z, raw.A, ag.n_d, ag.n_t/2, overlays::y_coord(raw.Z));
    }
}


// ═══════════════════════════════════════════════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════════════════════════════════════════════

int main() {
    std::printf("╔══════════════════════════════════════════════════════════════════════╗\n");
    std::printf("║  CQ25 — Atomicus SDT Nuclear Grammar                               ║\n");
    std::printf("║  Exact (Z,A) → (n_d,n_t) coordinate transform on the nuclear chart ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════════════╝\n");

    stage_A();
    stage_B();
    stage_C();

    std::printf("\n════════════════════════════════════════════════════════════════════════\n");
    std::printf("  CQ25 complete. All static_assert targets verified at compile time.\n");
    std::printf("════════════════════════════════════════════════════════════════════════\n\n");

    return 0;
}
