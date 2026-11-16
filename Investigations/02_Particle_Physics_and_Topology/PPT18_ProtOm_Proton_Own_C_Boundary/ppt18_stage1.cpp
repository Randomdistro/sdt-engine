// PPT18 stage 1 (2026-10-12): ProtOm deconstruction — inventory of proton geometries, consistency checks, Om_p candidates.
// Registration: PROMPT.md (written before this file). No target exists for Om_p. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static double vT(int p, int q) { return std::sqrt(double(p) / (p + q)); }   // in c
static double vP(int p, int q) { return std::sqrt(double(q) / (p + q)); }
int main() {
    const double fm = 1e-15, Rp = M::R_p / fm, lbar = M::hbar / (M::m_p * M::c) / fm, re = M::r_e / fm, PI = std::numbers::pi;
    std::printf("PPT18 stage 1 (2026-10-12): ProtOm deconstruction\n==================================================\n");
    int bad = 0;
    for (auto [p, q] : {std::pair{2, 3}, std::pair{4, 5}}) { double b = vT(p, q) * vT(p, q) + vP(p, q) * vP(p, q); bool ok = std::fabs(b - 1) < 1e-15;
        std::printf("[V1] (%d,%d) budget v_T^2+v_P^2 = %.17f -> %s\n", p, q, b, ok ? "met" : "NOT MET"); bad += !ok; }
    { double r4 = 4 * lbar * fm; bool ok = std::fabs(r4 / law_III::R_p_lock - 1) < 1e-15; std::printf("[V2] 4 hbar/(m_p c) = %.6f fm vs R_p_lock %.6f fm -> %s\n", r4 / fm, law_III::R_p_lock / fm, ok ? "met" : "NOT MET"); bad += !ok; }
    { double e = 0.62 + 0.22 + 0.16; bool ok = std::fabs(e - 1) < 1e-12; std::printf("[V3] G5 envelope (R+a+b)/R_p = %.15f -> %s\n", e, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\nReference scales: R_p (measured) %.4f fm ; R_p_lock = 4 lbar_p %.5f fm ; lbar_p = hbar/(m_p c) %.5f fm ; r_e = Om_H %.4f fm\n", Rp, 4 * lbar, lbar, re);
    std::printf("hydrogen-ladder speed v_H(r) = c sqrt(r_e/r): at R_p %.4fc ; at R_p/3 %.4fc\n\n", std::sqrt(re / Rp), std::sqrt(re / (Rp / 3)));

    std::printf("INVENTORY (fm, c)\n");
    std::printf("G1 canon topology (2,3): v_T %.4fc v_P %.4fc ; aspect R/a = sqrt(3/2) = %.4f ; no absolute size\n", vT(2, 3), vP(2, 3), std::sqrt(1.5));
    std::printf("G2 confinement R_trefoil = lbar_p/sqrt3 = %.5f fm (= %.4f R_p)\n", lbar / std::sqrt(3.0), lbar / std::sqrt(3.0) / Rp);
    std::printf("G3 FLM07 R_p_lock = 4 lbar_p = %.5f fm\n", 4 * lbar);
    std::printf("G4 NP30 (2,3) filament: extent R_p %.4f ; node R_p/3 %.4f ; tube << R_p (no value) ; surface 1.83c on hydrogen's ladder\n", Rp, Rp / 3);
    const double g5R = 0.62 * Rp, g5a = 0.22 * Rp, g5b = 0.16 * Rp;
    std::printf("G5 NSEQ16 braid (4,5): R %.4f a %.4f b %.4f ; R/a = %.4f\n", g5R, g5a, g5b, g5R / g5a);
    const double g6R = 5.28 / (2 * PI), g6a = 0.06 / std::sqrt(2.0), g6b = 0.03;
    std::printf("G6 live engine H1 (4 tours x 3 cross-section turns): R %.4f helix a %.4f strand b %.4f ; R/a = %.3f ; outer envelope R+a+b = %.4f fm = %.4f R_p\n\n", g6R, g6a, g6b, g6R / g6a, g6R + g6a + g6b, (g6R + g6a + g6b) / Rp);

    std::printf("CONSISTENCY\n");
    std::printf("K1 envelope vs R_p: G5 %.4f R_p ; G6 %.4f R_p (%s) ; G2 R_trefoil %.4f R_p\n", (g5R + g5a + g5b) / Rp, (g6R + g6a + g6b) / Rp, (g6R + g6a + g6b) / Rp > 1.0001 ? "EXCEEDS the rim" : "within", lbar / std::sqrt(3.0) / Rp);
    std::printf("K2 aspect vs canon sqrt(q/p): G5 (4,5) canon %.4f vs registered %.4f ; G6 as (4,3) canon %.4f vs %.3f ; G1 (2,3) %.4f (no size to compare)\n", std::sqrt(5.0 / 4), g5R / g5a, std::sqrt(3.0 / 4), g6R / g6a, std::sqrt(1.5));
    std::printf("K3 speed: canon budget makes every mode <= c (v_T^2+v_P^2=c^2); 1.83c at R_p is hydrogen's ladder (PPT06 phase speed). Different quantities: %s\n", "both reported, not reconciled in canon");
    std::printf("K4 winding labels: G1/G4 (2,3) ; G5 (4,5) ; G6 4 tours x 3 turns -> three different pairs for one proton\n\n");

    std::printf("Om_p CANDIDATES (D1 = a (v_P/c)^2 ; D2 = a c/v_P control ; D3 = lbar_p)\n");
    struct Row { const char* g; double a; int p, q; const char* note; };
    const double g1a = Rp / (1 + std::sqrt(1.5));   // G1 sized only if R + a = R_p is assumed (assumption flagged)
    const Row rows[] = {{"G1 (2,3), sized by R+a=R_p [ASSUMED]", g1a, 2, 3, "size assumption not in canon"},
                        {"G5 (4,5) braid", g5a, 4, 5, "registered NSEQ16"},
                        {"G6 engine, read as (4,3)", g6a, 4, 3, "0.06 fm untraced"},
                        {"G6 engine, read as (2,3) speeds", g6a, 2, 3, "0.06 fm untraced"}};
    std::printf("  geometry                               tube a (fm)  v_P (c)   D1 Om_p (fm)  D1/R_p   D1 inside tube?  D2 rho_c (fm) D2 inside?\n");
    for (const auto& r : rows) { double v = vP(r.p, r.q), d1 = r.a * v * v, d2 = r.a / v;
        std::printf("  %-38s %9.4f   %7.4f   %10.5f   %7.4f   %-14s  %10.4f   %s   [%s]\n", r.g, r.a, v, d1, d1 / Rp, d1 < r.a ? "yes" : "no", d2, d2 < r.a ? "yes" : "no (outside tube)", r.note); }
    std::printf("  D3 action seat lbar_p = %.5f fm = R_p/4 (geometry-independent; inside the tours, not tied to a tube)\n", lbar);
    std::printf("\nFor scale: proton's own depth at a contact r = 2R_p, z_p = Om_p/(2R_p), for each D1 row: ");
    for (const auto& r : rows) { double v = vP(r.p, r.q); std::printf("%.4f  ", r.a * v * v / (2 * Rp)); }
    std::printf("; D3: %.4f ; hydrogen's z_H = r_e/(2R_p) = %.4f\n", lbar / (2 * Rp), re / (2 * Rp));
    return 0;
}
