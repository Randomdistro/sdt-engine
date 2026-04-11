/**
 * @file nuclear_grammar_heavy.cpp
 * @brief SDT Nuclear Construction Grammar — Heavy Elements, Fission & Decay Chains
 *
 * Extension: apply the alpha+deu+tri grammar to ALL elements Z=1..92,
 * trace the U-238 decay chain, analyze fission products, and show that
 * heavy element decay = systematic removal of triton bonds.
 *
 * @author SDT Canonical Engine — James Tyndall
 * @date April 2026
 */

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

struct Grammar {
    int Z, A, N;
    int n_alpha;
    int n_deu;
    int n_tri;
    bool valid;
};

Grammar decompose(int Z, int A) {
    Grammar g{Z, A, A-Z, 0, 0, 0, false};
    if (Z == 1) {
        g.n_alpha = 0;
        if (A == 1) { g.valid = true; }
        else if (A == 2) { g.n_deu = 1; g.valid = true; }
        else if (A == 3) { g.n_tri = 1; g.valid = true; }
        return g;
    }
    if (Z == 2 && A == 3) return g; // He-3 edge case
    if (Z == 2 && A == 4) { g.n_alpha = 1; g.valid = true; return g; }

    g.n_alpha = 1;
    g.n_tri = A - 2 * Z;
    g.n_deu = 3 * Z - A - 2;
    g.valid = (g.n_deu >= 0 && g.n_tri >= 0);
    return g;
}

int main() {
    std::printf("======================================================================\n");
    std::printf("  SDT NUCLEAR GRAMMAR — HEAVY ELEMENTS, FISSION & DECAY CHAINS\n");
    std::printf("======================================================================\n\n");

    // ── PART 1: THE U-238 DECAY CHAIN ──
    std::printf("── PART 1: U-238 DECAY CHAIN IN GRAMMAR DECOMPOSITION ──\n\n");
    std::printf("  The natural decay chain of U-238 (Uranium series):\n");
    std::printf("  Each step: alpha decay removes 2p+2n, beta decay converts n->p\n\n");

    struct DecayStep {
        int Z, A;
        const char* name;
        const char* symbol;
        const char* decay;   // "alpha", "beta-", or "stable"
        double halflife;     // in years (0 for seconds-scale)
        const char* hl_str;
    };

    DecayStep chain[] = {
        {92, 238, "Uranium-238",    "U",  "alpha", 4.468e9,  "4.47 Gyr"},
        {90, 234, "Thorium-234",    "Th", "beta-", 0.066,    "24.1 days"},
        {91, 234, "Protactinium-234","Pa", "beta-", 0.0,     "1.17 min"},
        {92, 234, "Uranium-234",    "U",  "alpha", 2.455e5,  "245 kyr"},
        {90, 230, "Thorium-230",    "Th", "alpha", 7.538e4,  "75.4 kyr"},
        {88, 226, "Radium-226",     "Ra", "alpha", 1600.0,   "1600 yr"},
        {86, 222, "Radon-222",      "Rn", "alpha", 0.01048,  "3.82 days"},
        {84, 218, "Polonium-218",   "Po", "alpha", 0.0,      "3.10 min"},
        {82, 214, "Lead-214",       "Pb", "beta-", 0.0,      "26.8 min"},
        {83, 214, "Bismuth-214",    "Bi", "beta-", 0.0,      "19.9 min"},
        {84, 214, "Polonium-214",   "Po", "alpha", 0.0,      "164 us"},
        {82, 210, "Lead-210",       "Pb", "beta-", 22.2,     "22.2 yr"},
        {83, 210, "Bismuth-210",    "Bi", "beta-", 0.0,      "5.01 days"},
        {84, 210, "Polonium-210",   "Po", "alpha", 0.379,    "138 days"},
        {82, 206, "Lead-206",       "Pb", "stable", 0.0,     "STABLE"},
    };
    int n_chain = sizeof(chain) / sizeof(chain[0]);

    std::printf("  %-22s  %3s  %3s  %3s  %3s  %3s  %6s  %-12s  %-12s\n",
        "Nuclide", "Z", "A", "N", "d", "t", "d+t", "Decay", "Half-life");
    std::printf("  %-22s  %3s  %3s  %3s  %3s  %3s  %6s  %-12s  %-12s\n",
        "──────────────────────", "───", "───", "───", "───", "───", "──────",
        "────────────", "────────────");

    Grammar g_first = decompose(chain[0].Z, chain[0].A);
    Grammar g_prev = g_first;

    for (int i = 0; i < n_chain; i++) {
        Grammar g = decompose(chain[i].Z, chain[i].A);
        std::printf("  %-22s  %3d  %3d  %3d  %3d  %3d  %6d  %-12s  %-12s\n",
            chain[i].name, g.Z, g.A, g.N, g.n_deu, g.n_tri, g.n_deu + g.n_tri,
            chain[i].decay, chain[i].hl_str);
        g_prev = g;
    }

    Grammar g_last = decompose(chain[n_chain-1].Z, chain[n_chain-1].A);
    std::printf("\n  GRAMMAR SUMMARY OF FULL CHAIN:\n");
    std::printf("    U-238:  alpha + %dd + %dt = %d blocks\n",
        g_first.n_deu, g_first.n_tri, g_first.n_deu + g_first.n_tri);
    std::printf("    Pb-206: alpha + %dd + %dt = %d blocks\n",
        g_last.n_deu, g_last.n_tri, g_last.n_deu + g_last.n_tri);
    std::printf("    REMOVED: %d deu + %d tri = %d blocks\n",
        g_first.n_deu - g_last.n_deu,
        g_first.n_tri - g_last.n_tri,
        (g_first.n_deu + g_first.n_tri) - (g_last.n_deu + g_last.n_tri));
    std::printf("    That's %d nucleons shed as 8 alpha particles\n",
        g_first.A - g_last.A);
    std::printf("    Plus 6 beta decays (n->p conversions within existing blocks)\n");

    // Count alpha and beta decays
    int n_alpha_decays = 0, n_beta_decays = 0;
    for (int i = 0; i < n_chain - 1; i++) {
        if (chain[i].decay[0] == 'a') n_alpha_decays++;
        else if (chain[i].decay[0] == 'b') n_beta_decays++;
    }
    std::printf("    Alpha decays: %d, Beta decays: %d\n", n_alpha_decays, n_beta_decays);

    // ── PART 2: TRITON BOND COUNTING ALONG THE CHAIN ──
    std::printf("\n\n── PART 2: TRITON BOND EVOLUTION THROUGH DECAY CHAIN ──\n\n");
    std::printf("  Tracking triton count at each step:\n\n");

    for (int i = 0; i < n_chain; i++) {
        Grammar g = decompose(chain[i].Z, chain[i].A);
        int delta_t = g_first.n_tri - g.n_tri;
        int delta_d = g_first.n_deu - g.n_deu;

        char bar[100] = {};
        int bar_len = g.n_tri;
        if (bar_len > 60) bar_len = 60;
        for (int j = 0; j < bar_len; j++) bar[j] = '#';
        bar[bar_len] = '\0';

        std::printf("  %-6s %-3d: %2dt (delta: %+3dt, %+3dd) %s\n",
            chain[i].symbol, chain[i].A,
            g.n_tri, -delta_t, -delta_d, bar);
    }

    // ── PART 3: Po-214 — THE MIDPOINT ──
    std::printf("\n\n── PART 3: POLONIUM-214 — THE MIDPOINT ANALYSIS ──\n\n");

    Grammar g_u238 = decompose(92, 238);
    Grammar g_po214 = decompose(84, 214);
    Grammar g_pb206 = decompose(82, 206);

    std::printf("  U-238:  alpha + %dd + %dt\n", g_u238.n_deu, g_u238.n_tri);
    std::printf("  Po-214: alpha + %dd + %dt\n", g_po214.n_deu, g_po214.n_tri);
    std::printf("  Pb-206: alpha + %dd + %dt\n", g_pb206.n_deu, g_pb206.n_tri);

    std::printf("\n  U-238 -> Po-214: lost %dt + %dd\n",
        g_u238.n_tri - g_po214.n_tri, g_u238.n_deu - g_po214.n_deu);
    std::printf("  Po-214 -> Pb-206: lost %dt + %dd\n",
        g_po214.n_tri - g_pb206.n_tri, g_po214.n_deu - g_pb206.n_deu);

    std::printf("\n  KEY INSIGHT:\n");
    std::printf("    U-238 to Po-214: exactly %d triton bonds removed\n",
        g_u238.n_tri - g_po214.n_tri);
    std::printf("    That's the number James predicted: 8 triton bonds on each side\n");
    std::printf("    The alpha core + deuteron scaffold is PRESERVED\n");
    std::printf("    Only tritons are shed (as alpha particles + beta adjustments)\n");

    // ── PART 4: FISSION PRODUCTS IN GRAMMAR ──
    std::printf("\n\n── PART 4: U-235 FISSION PRODUCTS IN GRAMMAR ──\n\n");
    std::printf("  Common fission product pairs (U-235 + n -> products + neutrons):\n\n");

    struct FissionPair {
        int Z1, A1; const char* name1;
        int Z2, A2; const char* name2;
        int free_n;
        double yield_pct;
    };

    FissionPair fissions[] = {
        {36,  92, "Krypton-92",    56, 141, "Barium-141",    3, 6.0},
        {38,  94, "Strontium-94",  54, 140, "Xenon-140",     2, 5.8},
        {40,  97, "Zirconium-97",  52, 137, "Tellurium-137", 2, 6.1},
        {42,  99, "Molybdenum-99", 50, 134, "Tin-134",       3, 6.1},
        {39,  95, "Yttrium-95",    53, 139, "Iodine-139",    2, 6.3},
        {44, 103, "Ruthenium-103", 48, 131, "Cadmium-131",   2, 3.0},
        {55, 137, "Cesium-137",    37,  97, "Rubidium-97",   2, 6.2},
    };
    int n_fiss = sizeof(fissions) / sizeof(fissions[0]);

    std::printf("  %-18s  %2s %2s  ||  %-18s  %2s %2s  || free n  yield\n",
        "Light fragment", "d", "t", "Heavy fragment", "d", "t", "");
    std::printf("  %-18s  %2s %2s  ||  %-18s  %2s %2s  || ------  -----\n",
        "──────────────────", "──", "──", "──────────────────", "──", "──");

    for (int i = 0; i < n_fiss; i++) {
        auto& f = fissions[i];
        Grammar g1 = decompose(f.Z1, f.A1);
        Grammar g2 = decompose(f.Z2, f.A2);

        // Check: A1 + A2 + free_n should = 236 (U-235 + n)
        int total_A = f.A1 + f.A2 + f.free_n;

        std::printf("  %-18s  %2d %2d  ||  %-18s  %2d %2d  ||   %d    %.1f%%  (A=%d%s)\n",
            f.name1, g1.n_deu, g1.n_tri,
            f.name2, g2.n_deu, g2.n_tri,
            f.free_n, f.yield_pct, total_A,
            total_A == 236 ? " ok" : " !");

        // Grammar of the pair
        int pair_deu = g1.n_deu + g2.n_deu;
        int pair_tri = g1.n_tri + g2.n_tri;
        int pair_alpha = 2; // each fragment has its own alpha core

        std::printf("    Combined grammar: 2alpha + %dd + %dt + %dn_free\n",
            pair_deu, pair_tri, f.free_n);
    }

    // U-235 grammar
    Grammar g_u235 = decompose(92, 235);
    std::printf("\n  U-235 grammar: alpha + %dd + %dt\n", g_u235.n_deu, g_u235.n_tri);
    std::printf("  U-236* (U-235+n): Z=92, A=236\n");
    Grammar g_u236 = decompose(92, 236);
    std::printf("  U-236 grammar: alpha + %dd + %dt\n\n", g_u236.n_deu, g_u236.n_tri);

    std::printf("  FISSION GRAMMAR INSIGHT:\n");
    std::printf("    U-236* (compound nucleus) splits into two fragments,\n");
    std::printf("    each retaining or forming its own alpha core.\n");
    std::printf("    The free neutrons are bonds that couldn't find a home in either fragment.\n");
    std::printf("    Asymmetric fission = unequal division of the d+t scaffold.\n");

    // ── PART 5: SYMMETRIC SPLIT ANALYSIS ──
    std::printf("\n\n── PART 5: SYMMETRIC SPLIT ANALYSIS ──\n\n");
    std::printf("  If U-238 were split perfectly symmetrically:\n");
    std::printf("  U-238 → 2 × (Z=46, A=119) = 2 × Palladium-119\n\n");

    Grammar g_pd119 = decompose(46, 119);
    std::printf("  Pd-119: alpha + %dd + %dt  (valid: %s)\n",
        g_pd119.n_deu, g_pd119.n_tri, g_pd119.valid ? "yes" : "no");
    std::printf("  Pd-119 is UNSTABLE (beta- to Ag-119, t1/2 = 0.92s)\n");

    std::printf("\n  James's insight: instead of symmetric mass split,\n");
    std::printf("  do a SYMMETRIC BOND split — remove equal triton bonds from both sides.\n\n");

    // Try removing N tritons from each side of U-238
    std::printf("  Removing N triton-bonds from each side of U-238 (alpha + %dd + %dt):\n\n",
        g_u238.n_deu, g_u238.n_tri);
    std::printf("  %-6s  %-4s %-4s  %-20s  %-20s  %s\n",
        "N_rem", "d", "t", "Result", "Element", "Stable?");
    std::printf("  %-6s  %-4s %-4s  %-20s  %-20s  %s\n",
        "──────", "────", "────", "────────────────────", "────────────────────", "──────");

    const char* element_names[] = {
        "", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne",
        "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca",
        "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
        "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr",
        "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn",
        "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd",
        "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb",
        "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg",
        "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th",
        "Pa", "U"
    };

    for (int n_rem = 0; n_rem <= 20; n_rem++) {
        // Remove n_rem tritons: each triton has Z=1, A=3
        // So removing n_rem tritons: Z_new = Z - n_rem, A_new = A - 3*n_rem
        int Z_new = g_u238.Z - n_rem;
        int A_new = g_u238.A - 3 * n_rem;
        Grammar g_new = decompose(Z_new, A_new);

        char elem_str[64];
        if (Z_new >= 1 && Z_new <= 92)
            std::snprintf(elem_str, sizeof(elem_str), "%s-%d", element_names[Z_new], A_new);
        else
            std::snprintf(elem_str, sizeof(elem_str), "Z=%d, A=%d", Z_new, A_new);

        // Check if this is a known stable or long-lived nuclide
        const char* stability = "?";
        // Quick check for well-known stable endpoints
        if (Z_new == 82 && A_new == 206) stability = "STABLE (Pb-206)";
        else if (Z_new == 82 && A_new == 208) stability = "STABLE (Pb-208)";
        else if (Z_new == 83 && A_new == 209) stability = "~stable (Bi-209)";
        else if (Z_new == 84) stability = "Polonium (all radioactive)";
        else if (Z_new == 86) stability = "Radon (all radioactive)";
        else if (Z_new == 88) stability = "Radium (all radioactive)";
        else if (Z_new == 90) stability = "Thorium (radioactive)";
        else if (Z_new == 80 && (A_new == 196 || A_new == 198 || A_new == 199 || A_new == 200 || A_new == 201 || A_new == 202 || A_new == 204))
            stability = "STABLE (Hg)";
        else if (Z_new == 78 && (A_new >= 190 && A_new <= 198))
            stability = "near-stable (Pt)";
        else if (Z_new == 79 && A_new == 197)
            stability = "STABLE (Au-197!)";
        else if (Z_new == 76 && (A_new >= 184 && A_new <= 192))
            stability = "STABLE (Os)";
        else if (Z_new == 74 && (A_new >= 180 && A_new <= 186))
            stability = "STABLE (W)";
        else if (Z_new == 72 && (A_new >= 174 && A_new <= 180))
            stability = "STABLE (Hf)";

        std::printf("  %3d     %3d  %3d   %-20s  %-20s\n",
            n_rem, g_new.n_deu, g_new.n_tri, elem_str, stability);
    }

    // ── PART 6: SYMMETRIC PAIR FISSION — JAMES'S HYPOTHESIS ──
    std::printf("\n\n── PART 6: SYMMETRIC PAIR FISSION (EQUAL TRITON REMOVAL) ──\n\n");
    std::printf("  If we remove 4 tritons from each side (8 total):\n\n");

    // U-238 minus 8 tritons
    int Z_core = g_u238.Z - 8;
    int A_core = g_u238.A - 24;
    Grammar g_core = decompose(Z_core, A_core);
    std::printf("  U-238 minus 8 tritons: Z=%d, A=%d = %s-%d\n", Z_core, A_core,
        (Z_core >= 1 && Z_core <= 92) ? element_names[Z_core] : "?", A_core);
    std::printf("    Grammar: alpha + %dd + %dt\n", g_core.n_deu, g_core.n_tri);
    std::printf("    THIS IS POLONIUM-214 — exactly where the decay chain passes!\n\n");

    // The 8 tritons released = 8p + 16n = 24 nucleons
    // These rearrange into: 2 alphas (8 nucleons) + 2 alphas (8 nucleons) + ...
    // Actually: 8 tritons = 24 nucleons. As alphas: 24/4 = 6 alphas. Z from 8t = 8.
    // But 6 alphas = Z=12. Deficit: 12-8=4 protons. Hence 4 beta decays convert 4n->4p.
    std::printf("  The 8 shed tritons (8p + 16n = 24 nucleons):\n");
    std::printf("    Rearrange as 6 alpha particles (24 nucleons, Z=12)\n");
    std::printf("    But 8 tritons only have Z=8, not Z=12\n");
    std::printf("    Deficit: 4 protons -> 4 beta decays (n->p inside remaining blocks)\n");
    std::printf("    Result: 8 alpha decays + 6 beta decays in the actual chain\n");

    // ── PART 7: THE FULL PERIODIC TABLE AS TRITON-REMOVAL FROM U-238 ──
    std::printf("\n\n── PART 7: EVERY ELEMENT AS A TRITON-DEFICIENT URANIUM ──\n\n");
    std::printf("  Every element from Pb(82) down to Fe(26) can be reached by\n");
    std::printf("  removing tritons from U-238 (with beta-adjustments).\n");
    std::printf("  This is the REVERSE of stellar nucleosynthesis.\n\n");

    std::printf("  The most abundant stable isotope of each element, as U-238 minus N tritons:\n\n");

    struct StableTarget {
        int Z, A;
        const char* name;
        double abund;
    };

    StableTarget targets[] = {
        {82, 208, "Lead-208",       52.4},
        {80, 202, "Mercury-202",    29.86},
        {79, 197, "Gold-197",       100.0},
        {78, 195, "Platinum-195",   33.78},
        {77, 193, "Iridium-193",    62.7},
        {76, 192, "Osmium-192",     40.93},
        {75, 187, "Rhenium-187",    62.6},
        {74, 184, "Tungsten-184",   30.64},
        {73, 181, "Tantalum-181",   99.988},
        {72, 180, "Hafnium-180",    35.08},
        {56, 138, "Barium-138",     71.7},
        {50, 120, "Tin-120",        32.58},
        {47, 107, "Silver-107",     51.839},
        {46, 106, "Palladium-106",  27.33},
        {40, 90,  "Zirconium-90",   51.45},
        {38, 88,  "Strontium-88",   82.58},
        {30, 64,  "Zinc-64",        49.17},
        {28, 58,  "Nickel-58",      68.077},
        {26, 56,  "Iron-56",        91.754},
    };
    int n_targets = sizeof(targets) / sizeof(targets[0]);

    std::printf("  %-18s  %3s %3s  %3s %3s  %8s  %-6s\n",
        "Element", "Z", "A", "d", "t", "tri_rem", "valid");
    std::printf("  %-18s  %3s %3s  %3s %3s  %8s  %-6s\n",
        "──────────────────", "───", "───", "───", "───", "────────", "──────");

    for (int i = 0; i < n_targets; i++) {
        Grammar g = decompose(targets[i].Z, targets[i].A);
        int tri_from_U = g_u238.n_tri - g.n_tri;
        int deu_from_U = g_u238.n_deu - g.n_deu;
        std::printf("  %-18s  %3d %3d  %3d %3d  %+4dt %+3dd  %-6s\n",
            targets[i].name, targets[i].Z, targets[i].A,
            g.n_deu, g.n_tri,
            -tri_from_U, -deu_from_U,
            g.valid ? "valid" : "edge");
    }

    // ── PART 8: THE IRON ENDPOINT ──
    std::printf("\n\n── PART 8: THE IRON ENDPOINT — PEAK BINDING ENERGY ──\n\n");

    Grammar g_fe56 = decompose(26, 56);
    Grammar g_ni62 = decompose(28, 62);
    Grammar g_ni58 = decompose(28, 58);

    std::printf("  Fe-56:  alpha + %dd + %dt  (most abundant iron)\n", g_fe56.n_deu, g_fe56.n_tri);
    std::printf("  Ni-58:  alpha + %dd + %dt  (most abundant nickel)\n", g_ni58.n_deu, g_ni58.n_tri);
    std::printf("  Ni-62:  alpha + %dd + %dt  (highest binding energy per nucleon)\n\n", g_ni62.n_deu, g_ni62.n_tri);

    std::printf("  Iron peak in grammar terms:\n");
    std::printf("    Fe-56 has triton fraction: %d/%d = %.1f%% triton blocks\n",
        g_fe56.n_tri, g_fe56.n_deu + g_fe56.n_tri,
        100.0 * g_fe56.n_tri / (g_fe56.n_deu + g_fe56.n_tri));
    std::printf("    U-238 has triton fraction: %d/%d = %.1f%% triton blocks\n",
        g_u238.n_tri, g_u238.n_deu + g_u238.n_tri,
        100.0 * g_u238.n_tri / (g_u238.n_deu + g_u238.n_tri));
    std::printf("    The universe PREFERS deuteron-heavy constructions.\n");
    std::printf("    Heavy elements are triton-overloaded → unstable → decay back.\n");
    std::printf("    Iron is the equilibrium: enough tritons for stability,\n");
    std::printf("    not so many that the construction wants to shed them.\n");

    double fe_tri_frac = (double)g_fe56.n_tri / (g_fe56.n_deu + g_fe56.n_tri);
    double u_tri_frac = (double)g_u238.n_tri / (g_u238.n_deu + g_u238.n_tri);

    std::printf("\n  Triton fraction spectrum:\n");
    for (int Z_scan = 2; Z_scan <= 92; Z_scan += 2) {
        // Find most abundant isotope (approximate — use A = 2*Z for even-even, or known)
        int A_scan;
        if (Z_scan <= 20) A_scan = 2 * Z_scan;
        else if (Z_scan <= 28) A_scan = 2 * Z_scan + 4;
        else if (Z_scan <= 50) A_scan = (int)(2.15 * Z_scan);
        else A_scan = (int)(2.5 * Z_scan);

        Grammar g_scan = decompose(Z_scan, A_scan);
        if (!g_scan.valid) continue;

        double frac = (double)g_scan.n_tri / (g_scan.n_deu + g_scan.n_tri);

        char bar[61] = {};
        int bar_len = (int)(frac * 60);
        for (int j = 0; j < bar_len; j++) bar[j] = '#';
        bar[bar_len] = '\0';

        const char* marker = "";
        if (Z_scan == 26) marker = " <-- IRON (peak binding)";
        else if (Z_scan == 92) marker = " <-- URANIUM";
        else if (Z_scan == 82) marker = " <-- LEAD (stable endpoint)";
        else if (Z_scan == 2) marker = " <-- HELIUM (pure alpha)";

        std::printf("  Z=%2d: tri=%.0f%% %s%s\n", Z_scan, frac * 100, bar, marker);
    }

    std::printf("\n\n======================================================================\n");
    std::printf("  HEAVY ELEMENT GRAMMAR ANALYSIS COMPLETE\n");
    std::printf("======================================================================\n");

    return 0;
}
