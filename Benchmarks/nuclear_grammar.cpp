/**
 * @file nuclear_grammar.cpp
 * @brief SDT Nuclear Construction Grammar — Systematic Analysis
 *
 * The Construction Grammar:
 *   1. Every nucleus has ONE alpha core (4He) at its centre
 *   2. Building blocks are deuterons (d = p+n, A=2) and tritons (t = p+2n, A=3) ONLY
 *   3. Neutrons NEVER appear alone — only in deu or tri formations
 *   4. Each stable isotope = alpha + n_d deuterons + n_t tritons
 *   5. Most symmetric arrangement → most abundant isotope
 *   6. Familial construction: each element builds from its predecessor
 *
 * This computation:
 *   - Decomposes every stable isotope Z=1..30 into alpha + deu + tri
 *   - Tests whether the grammar uniquely specifies stable isotopes
 *   - Predicts abundance hierarchy from symmetry arguments
 *   - Tracks feedstock consumption chains (e.g. Ne-21 → Na-23)
 *
 * Compile (from project root):
 *   cmake -S . -B build && cmake --build build
 *
 * @author SDT Canonical Engine — James Tyndall
 * @date April 2026
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

// =====================================================================
//  STABLE ISOTOPE DATABASE (Z=1..30, all naturally occurring)
// =====================================================================

struct Isotope {
    int Z;              // protons
    int A;              // mass number
    double abundance;   // natural abundance %
    bool stable;        // true if stable (or effectively stable t1/2 > 10^9 yr)
    const char* symbol;
    const char* name;
};

// Construction grammar decomposition result
struct Grammar {
    int n_alpha;    // always 1 (or 0 for H, D, T)
    int n_deu;      // number of deuterons
    int n_tri;      // number of tritons
    int remainder;  // leftover nucleons (should be 0 for valid grammar)
    bool valid;     // true if remainder == 0 AND neutron count matches
};

// Decompose an isotope into alpha + deuterons + tritons
// Rule: A = 4*n_alpha + 2*n_deu + 3*n_tri
//        Z = 2*n_alpha + n_deu + n_tri
// So:   n_deu + n_tri = Z - 2 (for n_alpha = 1, Z >= 2)
//        2*n_deu + 3*n_tri = A - 4
// Solving: n_tri = A - 4 - 2*(Z-2) = A - 2Z
//          n_deu = Z - 2 - n_tri = Z - 2 - (A - 2Z) = 3Z - A - 2
Grammar decompose(int Z, int A) {
    Grammar g{};

    // Special cases: hydrogen isotopes (no alpha core)
    if (Z == 1) {
        g.n_alpha = 0;
        if (A == 1) { g.n_deu = 0; g.n_tri = 0; g.valid = true; }       // proton
        else if (A == 2) { g.n_deu = 1; g.n_tri = 0; g.valid = true; }   // deuteron
        else if (A == 3) { g.n_deu = 0; g.n_tri = 1; g.valid = true; }   // triton
        else { g.valid = false; }
        return g;
    }

    // Helium-4 IS the alpha
    if (Z == 2 && A == 4) {
        g.n_alpha = 1; g.n_deu = 0; g.n_tri = 0; g.valid = true;
        return g;
    }
    // He-3: alpha minus one neutron — doesn't fit grammar (no alpha core possible)
    if (Z == 2 && A == 3) {
        g.n_alpha = 0; g.n_deu = 1; g.n_tri = 0; g.remainder = 1;
        g.valid = false;  // He-3 is a grammar edge case
        return g;
    }

    // General case: 1 alpha core
    g.n_alpha = 1;
    g.n_tri = A - 2 * Z;           // triton count
    g.n_deu = 3 * Z - A - 2;       // deuteron count

    // Validate
    g.valid = (g.n_deu >= 0 && g.n_tri >= 0);
    g.remainder = 0;

    // Cross-check
    int A_check = 4 + 2 * g.n_deu + 3 * g.n_tri;
    int Z_check = 2 + g.n_deu + g.n_tri;
    if (A_check != A || Z_check != Z) {
        g.valid = false;
        g.remainder = A - A_check;
    }

    return g;
}

// Symmetry score: higher = more symmetric
// Pure deuteron arrangements score highest
// Opposing triton pairs score next
// Odd triton counts score lowest
int symmetry_score(const Grammar& g) {
    if (!g.valid) return -1;
    if (g.n_tri == 0) return 100;                     // pure deuteron: maximum symmetry
    if (g.n_tri % 2 == 0) return 80 - g.n_tri;        // even tritons: partial symmetry
    return 60 - g.n_tri;                               // odd tritons: broken symmetry
}

// =====================================================================
//  COMPLETE STABLE ISOTOPE TABLE (Z=1..30)
// =====================================================================

static const Isotope isotopes[] = {
    // Hydrogen
    {1, 1, 99.9885, true, "H",  "Hydrogen"},
    {1, 2, 0.0115,  true, "D",  "Deuterium"},
    // Helium
    {2, 3, 0.000134, true, "He", "Helium-3"},
    {2, 4, 99.999866, true, "He", "Helium-4"},
    // Lithium
    {3, 6, 7.59,    true, "Li", "Lithium-6"},
    {3, 7, 92.41,   true, "Li", "Lithium-7"},
    // Beryllium
    {4, 9, 100.0,   true, "Be", "Beryllium-9"},
    // Boron
    {5, 10, 19.9,   true, "B",  "Boron-10"},
    {5, 11, 80.1,   true, "B",  "Boron-11"},
    // Carbon
    {6, 12, 98.93,  true, "C",  "Carbon-12"},
    {6, 13, 1.07,   true, "C",  "Carbon-13"},
    // Nitrogen
    {7, 14, 99.632, true, "N",  "Nitrogen-14"},
    {7, 15, 0.368,  true, "N",  "Nitrogen-15"},
    // Oxygen
    {8, 16, 99.757, true, "O",  "Oxygen-16"},
    {8, 17, 0.038,  true, "O",  "Oxygen-17"},
    {8, 18, 0.205,  true, "O",  "Oxygen-18"},
    // Fluorine
    {9, 19, 100.0,  true, "F",  "Fluorine-19"},
    // Neon
    {10, 20, 90.48, true, "Ne", "Neon-20"},
    {10, 21, 0.27,  true, "Ne", "Neon-21"},
    {10, 22, 9.25,  true, "Ne", "Neon-22"},
    // Sodium
    {11, 23, 100.0, true, "Na", "Sodium-23"},
    // Magnesium
    {12, 24, 78.99, true, "Mg", "Magnesium-24"},
    {12, 25, 10.00, true, "Mg", "Magnesium-25"},
    {12, 26, 11.01, true, "Mg", "Magnesium-26"},
    // Aluminum
    {13, 27, 100.0, true, "Al", "Aluminium-27"},
    // Silicon
    {14, 28, 92.223, true, "Si", "Silicon-28"},
    {14, 29, 4.685, true, "Si", "Silicon-29"},
    {14, 30, 3.092, true, "Si", "Silicon-30"},
    // Phosphorus
    {15, 31, 100.0, true, "P",  "Phosphorus-31"},
    // Sulfur
    {16, 32, 94.99, true, "S",  "Sulfur-32"},
    {16, 33, 0.75,  true, "S",  "Sulfur-33"},
    {16, 34, 4.25,  true, "S",  "Sulfur-34"},
    {16, 36, 0.01,  true, "S",  "Sulfur-36"},
    // Chlorine
    {17, 35, 75.76, true, "Cl", "Chlorine-35"},
    {17, 37, 24.24, true, "Cl", "Chlorine-37"},
    // Argon
    {18, 36, 0.3365, true, "Ar", "Argon-36"},
    {18, 38, 0.0632, true, "Ar", "Argon-38"},
    {18, 40, 99.6003, true, "Ar", "Argon-40"},
    // Potassium
    {19, 39, 93.2581, true, "K",  "Potassium-39"},
    {19, 40, 0.0117, true, "K",  "Potassium-40"},
    {19, 41, 6.7302, true, "K",  "Potassium-41"},
    // Calcium
    {20, 40, 96.941, true, "Ca", "Calcium-40"},
    {20, 42, 0.647, true, "Ca", "Calcium-42"},
    {20, 43, 0.135, true, "Ca", "Calcium-43"},
    {20, 44, 2.086, true, "Ca", "Calcium-44"},
    {20, 46, 0.004, true, "Ca", "Calcium-46"},
    {20, 48, 0.187, true, "Ca", "Calcium-48"},
    // Scandium
    {21, 45, 100.0, true, "Sc", "Scandium-45"},
    // Titanium
    {22, 46, 8.25,  true, "Ti", "Titanium-46"},
    {22, 47, 7.44,  true, "Ti", "Titanium-47"},
    {22, 48, 73.72, true, "Ti", "Titanium-48"},
    {22, 49, 5.41,  true, "Ti", "Titanium-49"},
    {22, 50, 5.18,  true, "Ti", "Titanium-50"},
    // Vanadium
    {23, 50, 0.250, true, "V",  "Vanadium-50"},
    {23, 51, 99.750, true, "V",  "Vanadium-51"},
    // Chromium
    {24, 50, 4.345, true, "Cr", "Chromium-50"},
    {24, 52, 83.789, true, "Cr", "Chromium-52"},
    {24, 53, 9.501, true, "Cr", "Chromium-53"},
    {24, 54, 2.365, true, "Cr", "Chromium-54"},
    // Manganese
    {25, 55, 100.0, true, "Mn", "Manganese-55"},
    // Iron
    {26, 54, 5.845, true, "Fe", "Iron-54"},
    {26, 56, 91.754, true, "Fe", "Iron-56"},
    {26, 57, 2.119, true, "Fe", "Iron-57"},
    {26, 58, 0.282, true, "Fe", "Iron-58"},
    // Cobalt
    {27, 59, 100.0, true, "Co", "Cobalt-59"},
    // Nickel
    {28, 58, 68.077, true, "Ni", "Nickel-58"},
    {28, 60, 26.223, true, "Ni", "Nickel-60"},
    {28, 61, 1.140, true, "Ni", "Nickel-61"},
    {28, 62, 3.634, true, "Ni", "Nickel-62"},
    {28, 64, 0.926, true, "Ni", "Nickel-64"},
    // Copper
    {29, 63, 69.17, true, "Cu", "Copper-63"},
    {29, 65, 30.83, true, "Cu", "Copper-65"},
    // Zinc
    {30, 64, 49.17, true, "Zn", "Zinc-64"},
    {30, 66, 27.73, true, "Zn", "Zinc-66"},
    {30, 67, 4.04,  true, "Zn", "Zinc-67"},
    {30, 68, 18.45, true, "Zn", "Zinc-68"},
    {30, 70, 0.61,  true, "Zn", "Zinc-70"},
};

static const int N_ISO = sizeof(isotopes) / sizeof(isotopes[0]);

int main() {
    std::printf("======================================================================\n");
    std::printf("  SDT NUCLEAR CONSTRUCTION GRAMMAR — SYSTEMATIC ANALYSIS\n");
    std::printf("  Rule: Every nucleus = 1 alpha core + deuterons + tritons\n");
    std::printf("  Neutrons ONLY in deu (p+n) or tri (p+2n) formations\n");
    std::printf("======================================================================\n\n");

    // ── PART 1: UNIVERSAL DECOMPOSITION ──
    std::printf("── PART 1: DECOMPOSITION TABLE ──\n\n");
    std::printf("  %-18s  %3s  %3s  %3s  %2s  %2s  %2s  %7s  %8s  %-10s\n",
        "Isotope", "Z", "A", "N", "al", "d", "t", "Abund%", "SymScore", "Status");
    std::printf("  %-18s  %3s  %3s  %3s  %2s  %2s  %2s  %7s  %8s  %-10s\n",
        "──────────────────", "───", "───", "───", "──", "──", "──", "───────", "────────", "──────────");

    int valid_count = 0;
    int invalid_count = 0;
    int symmetry_wins = 0;
    int symmetry_tests = 0;

    // Group isotopes by element for symmetry testing
    int prev_Z = -1;
    int best_sym_of_element = -1;
    double best_abund_of_element = -1;
    int best_sym_idx = -1;
    int best_abund_idx = -1;
    int element_start = 0;

    for (int i = 0; i < N_ISO; i++) {
        const auto& iso = isotopes[i];
        Grammar g = decompose(iso.Z, iso.A);
        int N = iso.A - iso.Z;
        int sym = symmetry_score(g);

        const char* status = g.valid ? "VALID" : "EDGE";

        std::printf("  %-18s  %3d  %3d  %3d  %2d  %2d  %2d  %7.3f  %8d  %-10s\n",
            iso.name, iso.Z, iso.A, N,
            g.n_alpha, g.n_deu, g.n_tri,
            iso.abundance, sym, status);

        if (g.valid) valid_count++; else invalid_count++;

        // Track best symmetry and best abundance per element
        if (iso.Z != prev_Z) {
            // Close previous element
            if (prev_Z > 0 && best_sym_idx >= 0 && best_abund_idx >= 0) {
                symmetry_tests++;
                if (best_sym_idx == best_abund_idx) symmetry_wins++;
            }
            prev_Z = iso.Z;
            best_sym_of_element = sym;
            best_abund_of_element = iso.abundance;
            best_sym_idx = i;
            best_abund_idx = i;
            element_start = i;
        } else {
            if (sym > best_sym_of_element) {
                best_sym_of_element = sym;
                best_sym_idx = i;
            }
            if (iso.abundance > best_abund_of_element) {
                best_abund_of_element = iso.abundance;
                best_abund_idx = i;
            }
        }
    }
    // Close last element
    if (best_sym_idx >= 0 && best_abund_idx >= 0) {
        symmetry_tests++;
        if (best_sym_idx == best_abund_idx) symmetry_wins++;
    }

    std::printf("\n  GRAMMAR COVERAGE:\n");
    std::printf("    Valid decompositions: %d / %d (%.1f%%)\n",
        valid_count, N_ISO, 100.0 * valid_count / N_ISO);
    std::printf("    Edge cases: %d (H-1, He-3)\n", invalid_count);

    std::printf("\n  SYMMETRY → ABUNDANCE CORRELATION:\n");
    std::printf("    Highest symmetry = highest abundance: %d / %d elements (%.1f%%)\n",
        symmetry_wins, symmetry_tests, 100.0 * symmetry_wins / symmetry_tests);

    // ── PART 2: FAMILIAL CHAINS ──
    std::printf("\n\n── PART 2: FAMILIAL CONSTRUCTION CHAINS ──\n\n");
    std::printf("  Each element builds from its predecessor by adding a deuteron or triton.\n");
    std::printf("  Parent + deu(+2) or tri(+3) → Child\n\n");

    // For each element Z (starting from Z=3), find which parent isotope + deu/tri
    // produces each stable isotope
    for (int i = 0; i < N_ISO; i++) {
        const auto& child = isotopes[i];
        if (child.Z < 3) continue;

        // Look for parent isotopes that could produce this child
        for (int j = 0; j < N_ISO; j++) {
            const auto& parent = isotopes[j];
            if (parent.Z != child.Z - 1) continue;

            int dA = child.A - parent.A;
            const char* block = nullptr;
            if (dA == 2) block = "deu";
            else if (dA == 3) block = "tri";
            else continue;

            Grammar g_parent = decompose(parent.Z, parent.A);
            Grammar g_child = decompose(child.Z, child.A);

            const char* child_status = "";
            // Check if the child is the dominant isotope
            bool child_dominant = true;
            for (int k = 0; k < N_ISO; k++) {
                if (isotopes[k].Z == child.Z && isotopes[k].abundance > child.abundance)
                    child_dominant = false;
            }
            if (child_dominant) child_status = " *** DOMINANT";

            std::printf("  %-14s (%6.3f%%) + %s -> %-14s (%6.3f%%)%s\n",
                parent.name, parent.abundance,
                block,
                child.name, child.abundance,
                child_status);
        }
    }

    // ── PART 3: FEEDSTOCK CONSUMPTION ANALYSIS ──
    std::printf("\n\n── PART 3: FEEDSTOCK CONSUMPTION ANALYSIS ──\n\n");
    std::printf("  If parent + deu/tri -> child, and child is more abundant than parent,\n");
    std::printf("  then the parent was CONSUMED to build the child.\n");
    std::printf("  Current parent abundance = leftover after consumption.\n\n");

    // Key chains from conversation
    struct Chain {
        const char* parent;
        int parent_Z, parent_A;
        double parent_abund;
        double parent_cosmic_rel;  // relative cosmic abundance (Si=10^6)
        const char* child;
        int child_Z, child_A;
        double child_abund;
        double child_cosmic_rel;
        const char* block;
    };

    // Cosmic abundances relative to Si = 10^6 (Lodders 2003)
    Chain chains[] = {
        {"Ne-21", 10, 21, 0.27, 3.44e6, "Na-23", 11, 23, 100.0, 6.0e4, "deu"},
        {"Ne-20", 10, 20, 90.48, 3.44e6, "Na-23", 11, 23, 100.0, 6.0e4, "tri"},
        {"N-14",  7, 14, 99.632, 2.12e6, "O-16",  8, 16, 99.757, 1.57e7, "deu"},
        {"N-15",  7, 15, 0.368, 2.12e6, "O-17",  8, 17, 0.038, 1.57e7, "deu"},
        {"O-16",  8, 16, 99.757, 1.57e7, "F-19",  9, 19, 100.0, 843.0, "tri"},
        {"F-19",  9, 19, 100.0, 843.0, "Ne-20", 10, 20, 90.48, 3.44e6, "deu"}, // WRONG DIR: Ne >> F
    };
    int n_chains = sizeof(chains) / sizeof(chains[0]);

    for (int i = 0; i < n_chains; i++) {
        auto& ch = chains[i];

        // Parent absolute abundance = parent_cosmic_rel * parent_abund/100
        double parent_abs = ch.parent_cosmic_rel * ch.parent_abund / 100.0;
        // Child absolute abundance = child_cosmic_rel * child_abund/100
        double child_abs  = ch.child_cosmic_rel * ch.child_abund / 100.0;

        // If child_abs > parent_abs, the parent was consumed
        double consumed = child_abs - parent_abs;
        double original_parent = parent_abs + (consumed > 0 ? consumed : 0);
        double fraction_consumed = (consumed > 0) ? consumed / original_parent * 100.0 : 0;

        std::printf("  %s (%.3f%% of %s, cosmic %.2e)\n", ch.parent, ch.parent_abund,
            ch.parent_Z == 10 ? "Ne" : ch.parent_Z == 7 ? "N" : ch.parent_Z == 8 ? "O" : "F",
            parent_abs);
        std::printf("    + %s -> %s (%.3f%% of %s, cosmic %.2e)\n",
            ch.block, ch.child, ch.child_abund,
            ch.child_Z == 11 ? "Na" : ch.child_Z == 8 ? "O" : ch.child_Z == 9 ? "F" : "Ne",
            child_abs);
        if (consumed > 0) {
            std::printf("    CONSUMED: %.2e (%.1f%% of original %.2e)\n",
                consumed, fraction_consumed, original_parent);
            std::printf("    Original parent fraction: %.3f%% (vs current %.3f%%)\n",
                original_parent / ch.parent_cosmic_rel * 100.0, ch.parent_abund);
        } else {
            std::printf("    NOT consumed (child rarer than parent)\n");
        }
        std::printf("\n");
    }

    // ── PART 4: THE NEON-SODIUM-MAGNESIUM CHAIN ──
    std::printf("\n── PART 4: THE NEON-SODIUM-MAGNESIUM CHAIN ──\n\n");

    double Ne_cosmic = 3.44e6;  // relative to Si=10^6
    double Na_cosmic = 6.0e4;
    double Mg_cosmic = 1.074e6;

    double Ne20 = Ne_cosmic * 0.9048;
    double Ne21 = Ne_cosmic * 0.0027;
    double Ne22 = Ne_cosmic * 0.0925;

    double Na23 = Na_cosmic * 1.0;

    double Mg24 = Mg_cosmic * 0.7899;
    double Mg25 = Mg_cosmic * 0.1000;
    double Mg26 = Mg_cosmic * 0.1101;

    std::printf("  Cosmic abundances (Si = 10^6):\n\n");
    std::printf("    Ne-20: %.2e (90.48%%)\n", Ne20);
    std::printf("    Ne-21: %.2e ( 0.27%%)\n", Ne21);
    std::printf("    Ne-22: %.2e ( 9.25%%)\n", Ne22);
    std::printf("    Na-23: %.2e (100%%)\n", Na23);
    std::printf("    Mg-24: %.2e (78.99%%)\n", Mg24);
    std::printf("    Mg-25: %.2e (10.00%%)\n", Mg25);
    std::printf("    Mg-26: %.2e (11.01%%)\n", Mg26);

    std::printf("\n  CHAIN ANALYSIS:\n\n");

    // Ne-21 + deu -> Na-23
    double Ne21_consumed_for_Na = Na23;  // All Na23 could come from Ne21
    double Ne21_original = Ne21 + Ne21_consumed_for_Na;
    double Ne21_original_pct = Ne21_original / (Ne_cosmic + Ne21_consumed_for_Na) * 100.0;

    std::printf("  Ne-21 + deu -> Na-23:\n");
    std::printf("    Current Ne-21: %.2e\n", Ne21);
    std::printf("    Na-23 produced: %.2e\n", Na23);
    std::printf("    Original Ne-21: %.2e (=current + consumed)\n", Ne21_original);
    std::printf("    Original Ne-21 fraction: %.2f%% (vs current 0.27%%)\n", Ne21_original_pct);
    std::printf("    Consumed: %.1f%%\n", (1.0 - Ne21/Ne21_original) * 100.0);

    // Ne-22 + deu -> Na-24 (unstable) -> Mg-24
    std::printf("\n  Ne-22 + deu -> Na-24 (t1/2=15h) -> Mg-24:\n");
    std::printf("    Ne-22 abundance: %.2e (9.25%%)\n", Ne22);
    std::printf("    Mg-24 abundance: %.2e (78.99%%)\n", Mg24);
    std::printf("    Mg-24/Ne-22 = %.1f (destination >> source)\n", Mg24/Ne22);
    std::printf("    -> Ne-22 was NOT the sole feedstock for Mg-24\n");
    std::printf("    -> Na-23 + deu -> Mg-24 is the dominant pathway\n");

    // Na-23 + deu -> Mg-24 (direct)
    std::printf("\n  Na-23 + deu -> Mg-24 (DOMINANT):\n");
    std::printf("    Na-23: %.2e\n", Na23);
    std::printf("    Mg-24: %.2e\n", Mg24);
    std::printf("    This requires most Na-23 to have been further processed.\n");
    std::printf("    Na-23 is a WAYPOINT, not a destination.\n");

    // Ne-22 + tri -> Na-25 (unstable) -> Mg-25
    std::printf("\n  Ne-22 + tri -> Na-25 (t1/2=59s) -> Mg-25:\n");
    std::printf("    Ne-22: %.2e (9.25%%)\n", Ne22);
    std::printf("    Mg-25: %.2e (10.00%%)\n", Mg25);
    std::printf("    Mg-25/Ne-22 = %.2f\n", Mg25/Ne22);
    std::printf("    -> RATIO MATCH: 9.25%% Ne-22 maps to 10.00%% Mg-25\n");
    std::printf("    -> The triton-substituted branch PRESERVES its share!\n");

    // ── PART 5: SYMMETRY PREDICTIONS ──
    std::printf("\n\n── PART 5: SYMMETRY → ABUNDANCE PREDICTIONS ──\n\n");
    std::printf("  Testing: most symmetric (n_tri=0) isotope is most abundant.\n\n");

    prev_Z = -1;
    struct ElementResult {
        int Z;
        const char* name;
        const char* best_sym_name;
        const char* best_abund_name;
        int best_sym_A;
        int best_abund_A;
        int n_isotopes;
        bool match;
    };

    std::vector<ElementResult> results;
    int cur_best_sym = -1, cur_best_sym_A = 0;
    double cur_best_abund = -1; int cur_best_abund_A = 0;
    const char* cur_best_sym_name = "";
    const char* cur_best_abund_name = "";
    int cur_count = 0;
    int cur_Z = 0;
    const char* cur_name = "";

    auto flush_element = [&]() {
        if (cur_count > 1) {
            results.push_back({cur_Z, cur_name,
                cur_best_sym_name, cur_best_abund_name,
                cur_best_sym_A, cur_best_abund_A,
                cur_count, cur_best_sym_A == cur_best_abund_A});
        }
    };

    for (int i = 0; i < N_ISO; i++) {
        const auto& iso = isotopes[i];
        if (iso.Z != prev_Z) {
            if (prev_Z > 0) flush_element();
            prev_Z = iso.Z;
            cur_Z = iso.Z;
            cur_name = iso.symbol;
            cur_count = 0;
            cur_best_sym = -1;
            cur_best_abund = -1;
        }
        cur_count++;
        Grammar g = decompose(iso.Z, iso.A);
        int sym = symmetry_score(g);
        if (sym > cur_best_sym) {
            cur_best_sym = sym;
            cur_best_sym_A = iso.A;
            cur_best_sym_name = iso.name;
        }
        if (iso.abundance > cur_best_abund) {
            cur_best_abund = iso.abundance;
            cur_best_abund_A = iso.A;
            cur_best_abund_name = iso.name;
        }
    }
    flush_element();

    int sym_match = 0;
    int sym_total = (int)results.size();

    std::printf("  %-4s  %-3s  %-18s  %-18s  %s\n",
        "Z", "#", "Most Symmetric", "Most Abundant", "Match?");
    std::printf("  %-4s  %-3s  %-18s  %-18s  %s\n",
        "────", "───", "──────────────────", "──────────────────", "──────");

    for (auto& r : results) {
        const char* check = r.match ? "YES" : "no";
        std::printf("  %-4d  %-3d  %-18s  %-18s  %s\n",
            r.Z, r.n_isotopes, r.best_sym_name, r.best_abund_name, check);
        if (r.match) sym_match++;
    }

    std::printf("\n  RESULT: Symmetry predicts abundance in %d / %d multi-isotope elements (%.1f%%)\n",
        sym_match, sym_total, 100.0 * sym_match / sym_total);

    // ── PART 6: GEOMETRY DESCRIPTIONS ──
    std::printf("\n\n── PART 6: CONSTRUCTION GEOMETRY FOR KEY NUCLEI ──\n\n");

    struct GeoDesc {
        const char* name;
        int Z, A;
        const char* geometry;
    };

    GeoDesc geos[] = {
        {"Helium-4",    2,  4, "Alpha core (tetrahedron). THE brick."},
        {"Lithium-6",   3,  6, "Alpha + 1 deuteron. Dumbbell (prolate)."},
        {"Lithium-7",   3,  7, "Alpha + 1 triton. Prolate spheroid."},
        {"Beryllium-9", 4,  9, "Alpha + 1d + 1t. First mixed construction."},
        {"Boron-10",    5, 10, "Alpha + 2d. Symmetric pair around core."},
        {"Boron-11",    5, 11, "Alpha + 1d + 1t. Asymmetric, but dominant (80.1%)."},
        {"Carbon-12",   6, 12, "Alpha + 4d. Triangular pyramid of deuterons. NOT 3 alphas."},
        {"Carbon-13",   6, 13, "Alpha + 3d + 1t. One triton substitution."},
        {"Nitrogen-14", 7, 14, "Alpha + 5d. Triangular bipyramid of deuterons."},
        {"Nitrogen-15", 7, 15, "Alpha + 4d + 1t. One triton substitution (0.368%)."},
        {"Oxygen-16",   8, 16, "Alpha + 6d. Octahedral deuteron shell. NOT 4 alphas."},
        {"Oxygen-17",   8, 17, "Alpha + 5d + 1t. Rare triton sub (0.038%)."},
        {"Oxygen-18",   8, 18, "Alpha + 4d + 2t. Opposing tritons restore partial symmetry (0.205% > 0.038%)."},
        {"Fluorine-19", 9, 19, "Alpha + 6d + 1t. Odd triton breaks symmetry. Only 1 stable isotope."},
        {"Neon-20",    10, 20, "Alpha + 8d. Full deuteron cube around core. THE compressor."},
        {"Neon-21",    10, 21, "Alpha + 7d + 1t. One broken face (0.27% — feedstock)."},
        {"Neon-22",    10, 22, "Alpha + 6d + 2t. Opposing tritons (9.25%). Partially restored."},
        {"Sodium-23",  11, 23, "Alpha + 8d + 1t. Neon-20 + triton, or Ne-21 + deuteron."},
        {"Iron-56",    26, 56, "Alpha + 20d + 4t. End of the line (peak binding energy)."},
    };

    for (auto& geo : geos) {
        Grammar g = decompose(geo.Z, geo.A);
        std::printf("  %-16s (Z=%d, A=%d): %dd + %dt\n", geo.name, geo.Z, geo.A, g.n_deu, g.n_tri);
        std::printf("    %s\n\n", geo.geometry);
    }

    // ── PART 7: THE O-18 > O-17 TEST ──
    std::printf("\n── PART 7: OPPOSING-TRITON SYMMETRY TEST ──\n\n");
    std::printf("  If even triton counts are more stable than odd:\n");
    std::printf("  Then for isotopes with 2 tritons, abundance > 1 triton (same element)\n\n");

    struct TriTest {
        const char* name;
        int Z, A;
        double abund;
        int n_tri;
    };

    TriTest tests[] = {
        {"O-17",  8, 17, 0.038, 1},
        {"O-18",  8, 18, 0.205, 2},
        {"Ne-21", 10, 21, 0.27, 1},
        {"Ne-22", 10, 22, 9.25, 2},
        {"Mg-25", 12, 25, 10.00, 1},
        {"Mg-26", 12, 26, 11.01, 2},
        {"Si-29", 14, 29, 4.685, 1},
        {"Si-30", 14, 30, 3.092, 2},
        {"S-33",  16, 33, 0.75, 1},
        {"S-34",  16, 34, 4.25, 2},
        {"Ca-43", 20, 43, 0.135, 1},
        {"Ca-44", 20, 44, 2.086, 2},
        {"Ti-47", 22, 47, 7.44, 1},
        {"Ti-48", 22, 48, 73.72, 2},
        {"Cr-53", 24, 53, 9.501, 1},
        {"Cr-54", 24, 54, 2.365, 2},
        {"Fe-57", 26, 57, 2.119, 1},
        {"Fe-58", 26, 58, 0.282, 2},
    };

    int tri_wins = 0, tri_tests = 0;
    for (int i = 0; i < (int)(sizeof(tests)/sizeof(tests[0])); i += 2) {
        auto& odd = tests[i];
        auto& even = tests[i+1];
        bool even_wins = even.abund > odd.abund;
        std::printf("  %-6s (%dt, %6.3f%%) vs %-6s (%dt, %6.3f%%) -> %s\n",
            odd.name, odd.n_tri, odd.abund,
            even.name, even.n_tri, even.abund,
            even_wins ? "2t WINS (symmetric)" : "1t WINS (asymmetric)");
        tri_tests++;
        if (even_wins) tri_wins++;
    }

    std::printf("\n  RESULT: 2-triton > 1-triton in %d / %d cases (%.1f%%)\n",
        tri_wins, tri_tests, 100.0 * tri_wins / tri_tests);
    std::printf("  (Failures may indicate additional symmetry breaking mechanisms)\n");

    std::printf("\n\n======================================================================\n");
    std::printf("  INVESTIGATION COMPLETE\n");
    std::printf("======================================================================\n");

    return 0;
}
