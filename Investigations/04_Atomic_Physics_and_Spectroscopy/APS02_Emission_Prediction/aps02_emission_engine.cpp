/**
 * APS02 v2: DRAG FACTOR ANALYSIS
 *
 * D = λ_meas / [(8/3) · λ_C · k²]
 *
 * If D = 1: the atom is koppa-class (full drafting)
 * If D ≈ 2: the atom is half-koppa (no drafting, lone opener)
 * Does D track with outer-shell electron count?
 */
#include <cstdio>
#include <cmath>
#include <sdt/laws.hpp>

namespace K = sdt::laws::measured;

struct El {
    int Z, A;
    double IE1;
    double lam_nist;  // resonance line nm
    int outer;        // electrons in outermost s+p shell
    const char* sym;
    const char* config;
};

static const El D[] = {
    { 1, 1, 13.598, 121.567, 1, "H",  "1s1"},
    { 2, 4, 24.587,  58.433, 2, "He", "1s2"},
    { 3, 7,  5.392, 670.776, 1, "Li", "[He]2s1"},
    { 4, 9,  9.323, 234.861, 2, "Be", "[He]2s2"},
    { 5,11,  8.298, 249.773, 3, "B",  "[He]2s2 2p1"},
    { 6,12, 11.260, 193.091, 4, "C",  "[He]2s2 2p2"},
    { 7,14, 14.534, 119.955, 5, "N",  "[He]2s2 2p3"},
    { 8,16, 13.618, 130.217, 6, "O",  "[He]2s2 2p4"},
    { 9,19, 17.423,  95.483, 7, "F",  "[He]2s2 2p5"},
    {10,20, 21.565,  73.590, 8, "Ne", "[He]2s2 2p6"},
    {11,23,  5.139, 588.995, 1, "Na", "[Ne]3s1"},
    {12,24,  7.646, 285.213, 2, "Mg", "[Ne]3s2"},
    {13,27,  5.986, 394.401, 3, "Al", "[Ne]3s2 3p1"},
    {14,28,  8.152, 251.611, 4, "Si", "[Ne]3s2 3p2"},
    {15,31, 10.487, 213.618, 5, "P",  "[Ne]3s2 3p3"},
    {16,32, 10.360, 180.731, 6, "S",  "[Ne]3s2 3p4"},
    {17,35, 12.968, 134.724, 7, "Cl", "[Ne]3s2 3p5"},
    {18,40, 15.760, 104.822, 8, "Ar", "[Ne]3s2 3p6"},
    {19,39,  4.341, 766.490, 1, "K",  "[Ar]4s1"},
    {20,40,  6.113, 422.673, 2, "Ca", "[Ar]4s2"},
    {26,56,  7.902, 371.994, 2, "Fe", "[Ar]3d6 4s2"},
    {29,63,  7.726, 324.754, 1, "Cu", "[Ar]3d10 4s1"},
    {30,64,  9.394, 213.856, 2, "Zn", "[Ar]3d10 4s2"},
    {31,69,  5.999, 403.298, 3, "Ga", "[Ar]..4s2 4p1"},
    {32,74,  7.900, 265.118, 4, "Ge", "[Ar]..4s2 4p2"},
    {34,80,  9.752, 196.090, 6, "Se", "[Ar]..4s2 4p4"},
    {36,84, 14.000, 123.584, 8, "Kr", "[Ar]..4s2 4p6"},
    {37,85,  4.177, 780.023, 1, "Rb", "[Kr]5s1"},
    {38,88,  5.695, 460.733, 2, "Sr", "[Kr]5s2"},
    {47,107, 7.576, 328.068, 1, "Ag", "[Kr]4d10 5s1"},
    {48,112, 8.994, 228.802, 2, "Cd", "[Kr]4d10 5s2"},
    {49,115, 5.786, 410.176, 3, "In", "[Kr]..5s2 5p1"},
    {50,120, 7.344, 283.999, 4, "Sn", "[Kr]..5s2 5p2"},
    {53,127,10.451, 183.038, 7, "I",  "[Kr]..5s2 5p5"},
    {54,131,12.130, 146.961, 8, "Xe", "[Kr]..5s2 5p6"},
    {55,133, 3.894, 894.347, 1, "Cs", "[Xe]6s1"},
    {56,137, 5.212, 553.548, 2, "Ba", "[Xe]6s2"},
};
constexpr int N = sizeof(D) / sizeof(D[0]);

int main() {
    double lc = K::lambda_C_e * 1e9; // Compton wavelength in nm

    std::printf("╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  APS02 v2: DRAG FACTOR D = λ / [(8/3)·λ_C·k²]             ║\n");
    std::printf("║  Does D track with outer-shell electron count?             ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    std::printf("  λ_C = %.6f nm\n", lc);
    std::printf("  Baseline: H → D = λ_Ly-α / [(8/3)·λ_C·k_H²] = 1.000\n\n");

    std::printf("  %2s %-3s  %5s  %8s  %8s  %8s  %3s  %-20s  %s\n",
        "Z","Sym","outer","k₁","λ(nm)","D","n_t","config","D visual");
    std::printf("  ────────────────────────────────────────────────────────────────────────────\n");

    // Collect D values grouped by outer count
    double sum_D[9] = {}; int cnt_D[9] = {};

    for (int i = 0; i < N; i++) {
        double v1 = std::sqrt(2.0 * D[i].IE1 * K::eV_to_J / K::m_e);
        double k1 = K::c / v1;
        int n_t = (D[i].Z >= 2) ? D[i].A - 2*D[i].Z : 0;

        double D_val = D[i].lam_nist / ((8.0/3.0) * lc * k1 * k1);

        int o = D[i].outer;
        if (o >= 1 && o <= 8) { sum_D[o] += D_val; cnt_D[o]++; }

        // Visual bar
        char bar[40] = {};
        int blen = (int)(D_val * 10);
        if (blen > 39) blen = 39;
        for (int b = 0; b < blen; b++) bar[b] = '#';

        std::printf("  %2d %-3s  %5d  %8.1f  %8.2f  %8.4f  %3d  %-20s  %s\n",
            D[i].Z, D[i].sym, o, k1, D[i].lam_nist, D_val, n_t, D[i].config, bar);
    }

    // ═══ SUMMARY BY OUTER ELECTRON COUNT ═══
    std::printf("\n══ DRAG FACTOR BY OUTER SHELL ELECTRON COUNT ══\n\n");
    std::printf("  %5s  %8s  %5s  %s\n", "outer", "avg D", "count", "interpretation");
    std::printf("  ─────────────────────────────────────────────────────\n");

    const char* interp[] = {"","lone opener","paired s","s+1p","s+2p","half shell","s+4p","near full","full shell"};
    for (int o = 1; o <= 8; o++) {
        if (cnt_D[o] > 0) {
            double avg = sum_D[o] / cnt_D[o];
            char bar[40] = {};
            int blen = (int)(avg * 10);
            if (blen > 39) blen = 39;
            for (int b = 0; b < blen; b++) bar[b] = '█';
            std::printf("  %5d  %8.4f  %5d  %-15s  %s\n", o, avg, cnt_D[o], interp[o], bar);
        }
    }

    std::printf("\n  If D tracks with outer count, then:\n");
    std::printf("  λ_predicted = (8/3) · λ_C · k² · D(outer)\n");
    std::printf("  where D(outer) is a geometric function of the shell population.\n");

    return 0;
}
