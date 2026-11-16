// =====================================================================================
//  np13_grammar_efficiency.cpp — Fe-56 vs Ni-62 grammar symmetry vs B/A
//
//  Grammar: n_t = A - 2Z, n_d = 3Z - A - 2  (ATOMICUS constitution)
//  Symmetry metric: S = |n_d - n_t| / (n_d + n_t)  (0 = perfect balance)
//
//  Build (MSVC):
//    cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include np13_grammar_efficiency.cpp /Fe:np13.exe
//  Author: James Christopher Tyndall, Melbourne.
// =====================================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

struct Nuclide {
    const char* name;
    int Z, A;
    double B_per_A;   // MeV/nucleon (AME2020 anchors from prompt)
    double abundance; // relative cosmic / element fraction (prompt)
};

static void grammar(int Z, int A, int& nd, int& nt) {
    nt = A - 2 * Z;
    nd = 3 * Z - A - 2;
}

static double symmetry(int nd, int nt) {
    const int sum = nd + nt;
    if (sum <= 0) return 1.0;
    return std::fabs(double(nd - nt)) / double(sum);
}

int main() {
    std::printf("############################################################################\n");
    std::printf("#  NP13 — Fe-56 vs Ni-62 grammar efficiency (symmetry vs abundance)         #\n");
    std::printf("#  ATOMICUS grammar only — no fitted nuclear parameters.                    #\n");
    std::printf("############################################################################\n\n");

    const Nuclide cases[] = {
        {"Fe-56", 26, 56, 8.790, 1.00},
        {"Ni-62", 28, 62, 8.795, 0.036},
        {"Ni-58", 28, 58, 8.732, 0.682},
        {"O-16",  8,  16, 7.976, 1.00},
        {"C-12",  6,  12, 7.680, 1.00},
    };

    std::printf("  Isotope   Z  A   n_d  n_t   S=|d-t|/(d+t)  x=nd-nt  B/A  abund(rel)\n");
    std::printf("  --------  -  -   ---  ---   -------------  ------  ----  ---------\n");

    double fe_S = 0, ni62_S = 0, fe_B = 0, ni62_B = 0;
    int fe_x = 0, ni62_x = 0;

    for (const auto& n : cases) {
        int nd, nt;
        grammar(n.Z, n.A, nd, nt);
        const double S = symmetry(nd, nt);
        const int x = nd - nt;   // golden-boundary coordinate (x=0 is n_d=n_t)
        std::printf("  %-8s %2d %3d  %3d  %3d      %.3f    x=%+3d   %.3f   %.4f\n",
                    n.name, n.Z, n.A, nd, nt, S, x, n.B_per_A, n.abundance);
        if (n.A == 56 && n.Z == 26) { fe_S = S; fe_B = n.B_per_A; fe_x = x; }
        if (n.A == 62 && n.Z == 28) { ni62_S = S; ni62_B = n.B_per_A; ni62_x = x; }
    }

    std::printf("\n=== Headline (constitutional grammar: 1 alpha + n_d + n_t) ===\n");
    std::printf("  Fe-56: n_d=20 n_t=4  S=%.3f  |x|=|%d|  B/A=%.3f  dominant Fe isotope\n",
                fe_S, fe_x, fe_B);
    std::printf("  Ni-62: n_d=20 n_t=6  S=%.3f  |x|=|%d|  B/A=%.3f  (+0.06%% vs Fe-56)\n",
                ni62_S, ni62_x, ni62_B);
    std::printf("  NOTE: prompt's simplified 6d/6t counts are NOT the ATOMICUS transform.\n");
    std::printf("        np01 gives Fe-56 as n_d=20 n_t=4 (np01_output.txt).\n\n");

    const bool ni62_higher_BA = ni62_B > fe_B;
    const bool fe_more_symmetric = fe_S < ni62_S;   // lower S = more balanced d/t
    const bool explains = ni62_higher_BA && fe_more_symmetric;

    std::printf("================================================================\n");
    std::printf("  VERDICT: %s\n",
                explains ? "PASS — lower S favours abundance over B/A" :
                           "FAIL — simple |n_d-n_t|/(n_d+n_t) does NOT explain the paradox");
    if (!explains) {
        std::printf("  Ni-62 has HIGHER B/A (+0.06%%) AND lower asymmetry S (%.3f vs %.3f).\n",
                    ni62_S, fe_S);
        std::printf("  The iron-peak abundance favouring Fe-56 needs a metric BEYOND raw d/t balance\n");
        std::printf("  (e.g. alpha-cluster packing, snap-pair geometry, stellar Q-values).\n");
    }
    std::printf("  Class: B (STRUCTURAL audit) — grammar computed; thesis not confirmed.\n");
    std::printf("================================================================\n");

    return 0;   // investigation complete (honest negative is still a result)
}
