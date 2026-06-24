// =====================================================================================
//  cq42_five_routes.cpp  —  Five routes to the Planck length, ALL from SDT primitives.
//
//  Author: James Christopher Harvey, Melbourne.
//
//  ℓ_P is reachable five physically-distinct ways — gravity, Planck-mass, koppa geometric
//  mean, holographic boundary, thermal relay. Written in SDT primitives ONLY (Newton's G
//  replaced by its SDT identity  G = ℓ_P² c³ / ℏ), every route collapses to ℓ_P = ℓ_P,
//  EXACTLY.
//
//  THE PRECISION FLIP (the proof of one-seed):
//    routes 1,2,5 invoke G in standard physics and so carry CODATA G's ~1.5e-8 error —
//    they LOOK like independent measurements. Replace measured G with SDT's G = ℓ_P²c³/ℏ
//    and the error VANISHES: all five snap to machine-exact = ℓ_P. A route that loses its
//    uncertainty the moment it goes native was never measuring anything; it was ℓ_P in a
//    costume. This is FLM06's Seed Theorem made visible: five FACES, ONE seed.
//
//  HONEST SCOPE: this does NOT derive ℓ_P. Every route loops back to it (G_sdt, m_P, T_P,
//  ϟ_b, N are all built from ℓ_P). What it shows is that SDT is SELF-CONTAINED around ℓ_P
//  — it writes G, m_P, T_P in pure primitives, never borrowing Newton's constant — while
//  remaining honestly NOT self-deriving. ℓ_P stays Axiom R1, the one irreducible seed
//  (see measured::l_P provenance in laws.hpp, and FLM06 §3 Seed Theorem).
//
//  Build (MSVC):
//    cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:cq42_5.exe ^
//       Investigations\01_Foundations_and_Lattice_Mechanics\CQ42_Spation_Scale_Closure\cq42_five_routes.cpp
//  Build (GCC/Clang):
//    g++ -std=c++20 -IEngine/include cq42_five_routes.cpp -o cq42_5
// =====================================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;
namespace M = sdt::laws::measured;

// One route to ℓ_P. value_sdt is computed in pure SDT primitives (G -> ℓ_P²c³/ℏ).
// value_extG re-runs the SAME formula with measured CODATA G where the standard form
// uses one; for the G-free routes (3,4) the two columns are identical by construction.
struct Route {
    const char* label;
    const char* formula;
    double      value_sdt;   // SDT-native  (no borrowed G)
    double      value_extG;  // with CODATA G  (comparison ONLY — G is not an SDT primitive)
    bool        uses_G;      // does the standard-physics form invoke G?
};

static double rel(double a, double b) { return std::fabs(a - b) / std::fabs(b); }

int main() {
    // ── SDT primitives (the ONLY inputs; straight from laws.hpp::measured) ────────────
    const double lP    = M::l_P;
    const double c     = M::c;
    const double hbar  = M::hbar;
    const double k_B   = M::k_B;
    const double m_p   = M::m_p;
    const double R_CMB = M::R_CMB;
    const double pi    = std::numbers::pi;

    // ── SDT identity for Newton's constant: G = ℓ_P² c³ / ℏ  (laws.hpp G-bridge) ───────
    const double G_sdt = lP * lP * c * c * c / hbar;

    // ── CODATA G — EXTERNAL, used ONLY to show the precision flip (NOT a primitive) ────
    const double G_ext = 6.67430e-11;

    // ── SDT-native Planck quantities (the G symbol never appears) ─────────────────────
    const double m_P_sdt = hbar / (lP * c);          // Planck mass = ℏ/(ℓ_P c)
    const double T_P_sdt = hbar * c / (lP * k_B);    // Planck temp = ℏc/(ℓ_P k_B)
    // their CODATA-G counterparts, for the comparison column only:
    const double m_P_ext = std::sqrt(hbar * c / G_ext);
    const double T_P_ext = std::sqrt(hbar * std::pow(c, 5) / G_ext) / k_B;

    // ── the five routes ───────────────────────────────────────────────────────────────
    const Route routes[5] = {
        { "1 Gravitational",  "sqrt(hbar G / c^3)",
          std::sqrt(hbar * G_sdt / std::pow(c, 3)),
          std::sqrt(hbar * G_ext / std::pow(c, 3)), true  },

        { "2 Planck-mass",    "hbar / (m_P c)",
          hbar / (m_P_sdt * c),
          hbar / (m_P_ext * c), true  },

        { "3 Koppa geo-mean", "sqrt(koppa_b . lambda_p)",
          depth_closure::lP_from_closure_floor,          // engine: sqrt(koppa_per_baryon * ℏ/(m_p c))
          depth_closure::lP_from_closure_floor, false },

        { "4 Holographic",    "R_CMB / sqrt(S/4pi)",
          R_CMB / std::sqrt(law_I::S_boundary / (4.0 * pi)),
          R_CMB / std::sqrt(law_I::S_boundary / (4.0 * pi)), false },

        { "5 Relay/thermal",  "hbar c / (k_B T_P)",
          hbar * c / (k_B * T_P_sdt),
          hbar * c / (k_B * T_P_ext), true  },
    };

    std::printf("=====================================================================\n");
    std::printf("  FLM06  —  FIVE ROUTES TO THE PLANCK LENGTH (all SDT primitives)\n");
    std::printf("  J. C. Harvey, Melbourne.  Engine: sdt/laws.hpp   (G is never a primitive)\n");
    std::printf("=====================================================================\n\n");

    std::printf("  SDT-native Planck quantities (no G symbol anywhere):\n");
    std::printf("    G   = l_P^2 c^3 / hbar   = %.6e   (CODATA G = %.6e)\n", G_sdt, G_ext);
    std::printf("    m_P = hbar / (l_P c)     = %.6e kg\n", m_P_sdt);
    std::printf("    T_P = hbar c / (l_P k_B) = %.6e K\n\n", T_P_sdt);

    std::printf("  route               formula                     l_P (SDT-native)   rel    | usesG  rel(CODATA G)\n");
    std::printf("  ---------------------------------------------------------------------------------------------------\n");
    int exact_native = 0;
    for (const auto& r : routes) {
        const double rel_sdt = rel(r.value_sdt, lP);
        const double rel_ext = rel(r.value_extG, lP);
        if (rel_sdt < 1e-12) ++exact_native;
        std::printf("  %-16s  %-26s  %.6e   %.0e | %-4s   %.1e\n",
                    r.label, r.formula, r.value_sdt, rel_sdt,
                    r.uses_G ? "yes" : "no", rel_ext);
    }
    std::printf("\n  target l_P = %.6e m\n\n", lP);

    std::printf("---------------------------------------------------------------------\n");
    std::printf("  THE PRECISION FLIP (the proof of one-seed):\n");
    std::printf("    routes 1,2,5 carry CODATA G's ~1.5e-8 error -> they LOOK independent.\n");
    std::printf("    replace measured G with SDT's G = l_P^2 c^3/hbar -> error vanishes;\n");
    std::printf("    %d/5 routes snap to machine-exact = l_P.  They were l_P in disguise.\n\n",
                exact_native);
    std::printf("  VERDICT: five physically-distinct PICTURES, ONE seed (FLM06 Seed Theorem).\n");
    std::printf("    SDT is SELF-CONTAINED around l_P (writes G, m_P, T_P in pure primitives)\n");
    std::printf("    but NOT self-deriving: every route loops back to l_P (Axiom R1).\n");
    std::printf("---------------------------------------------------------------------\n");

    return (exact_native == 5) ? 0 : 1;
}
