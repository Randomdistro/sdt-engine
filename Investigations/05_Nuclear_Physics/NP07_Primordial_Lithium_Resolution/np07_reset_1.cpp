// NP07 blank-slate run 1 (2026-10-10). Registration: NP07_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
// Grammar rows (constitutional and alternate EC), the required lithium reduction, the K-electron count arithmetic, EC conservation of A.
// Author: J. C. Harvey, Melbourne.
#include <cmath>
#include <cstdio>
#include <vector>

struct Row { const char* nm; int Z, A; };
int main() {
    std::printf("NP07 blank-slate run 1 (registered in NP07_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0; const std::vector<Row> rows = {{"Li-6", 3, 6}, {"Li-7", 3, 7}, {"Be-7", 4, 7}, {"He-4", 2, 4}, {"B-10", 5, 10}};
    std::printf("Grammar (alpha core + n_d d + n_t t; alternate EC grammar: He-3 core + n_d d + n_t t with n_t = A - 2Z + 1, n_d = 3Z - A - 3):\n");
    for (auto& r : rows) { int nt = r.A - 2 * r.Z, nd = 3 * r.Z - r.A - 2; bool ok = nt >= 0 && nd >= 0; int ntE = r.A - 2 * r.Z + 1, ndE = 3 * r.Z - r.A - 3; bool okE = ntE >= 0 && ndE >= 0;
        int Zc = 2 + nd + nt, Nc = 2 + nd + 2 * nt; int ZcE = 2 + ndE + ntE, NcE = 1 + ndE + 2 * ntE + 0; // He-3 core has Z=2, N=1
        std::printf("  %-5s Z=%d A=%d : n_t = %2d, n_d = %2d -> %s", r.nm, r.Z, r.A, nt, nd, ok ? "valid" : "outside"); if (ok && (Zc != r.Z || Nc != r.A - r.Z)) { std::printf(" [RECONSTRUCTION FAILS]"); ++fails; }
        std::printf(" ; alternate: n_t = %2d, n_d = %2d -> %s", ntE, ndE, okE ? "valid" : "outside"); if (okE && (ZcE != r.Z || NcE != r.A - r.Z)) { std::printf(" [ALT RECONSTRUCTION FAILS: Z=%d N=%d]", ZcE, NcE); ++fails; } std::printf("\n"); }
    std::printf("[V1] reconstruction of (Z, N) for every grammar-valid row: %s\n", fails == 0 ? "met" : "NOT MET");
    std::printf("Prompt's table: Li-7 = alpha + d + t -> %d nucleons (A = 7) ; Be-7 = alpha + d -> %d nucleons (A = 7)\n\n", 4 + 2 + 3, 4 + 2);
    const double bbn = 4.68, bbnE = 0.67, obs = 1.58, obsE = 0.31; double R = bbn / obs, rel = std::sqrt((bbnE / bbn) * (bbnE / bbn) + (obsE / obs) * (obsE / obs));
    std::printf("Required reduction: BBN %.2f +- %.2f against observed %.2f +- %.2f (1e-10): factor R = %.3f (+- %.0f%%), loss of the A = 7 total %.1f%%, log10 R = %.3f\n", bbn, bbnE, obs, obsE, R, rel * 100, (1 - 1 / R) * 100, std::log10(R));
    { double t2 = 2 * 53.22, lit = 106.4; double d = std::fabs(t2 / lit - 1); bool ok = d < 1e-3; std::printf("[V2] K-electron count: neutral Be-7 has two 1s electrons, the hydrogenic ion one: 2 x 53.22 d = %.2f d against the literature 106.4 d: relative %.2e -> %s\n", t2, d, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    std::printf("EC conserves A: Be-7 (Z, N) = (4, 3) -> Li-7 (3, 4): A = %d -> %d ; the A = 7 total is unchanged by the timing of the capture\n", 4 + 3, 3 + 4);
    std::printf("A mechanism must change the A = 7 total at BBN (production or destruction) by a factor %.2f; an EC delay changes only the split between Be-7 and Li-7.\n", R);
    return fails ? 1 : 0;
}
