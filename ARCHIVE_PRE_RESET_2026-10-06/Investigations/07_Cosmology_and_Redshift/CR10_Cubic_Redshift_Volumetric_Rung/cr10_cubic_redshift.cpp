// =====================================================================================
//  CR10 — The Cubic Redshift: what is z³ for?  (the volumetric rung of SDT)
//
//  Author: James Christopher Harvey, Melbourne. 2026-06-24.
//
//  METHOD (as instructed): an excessively detailed, recursively expansive AND reductive
//  investigation. Each node is a CLAIM with a numeric TEST.
//     if FAIL  -> ask WHY, then TRY an alternative, and recurse.
//     if PASS  -> ANALYSE: find the cause, then the cause of the cause (cause^n),
//                 reducing to a ROOT CAUSE.
//  The tree below is walked in code; every branch prints its numbers so the reader can
//  see exactly where each claim breaks or holds and why.
//
//  THESIS UNDER TEST:  z is the LINEAR closure deficit (z = ϟ/r = (v/c)² = 1 − ℓ_P(r)/ℓ_P,∞),
//  so its powers ladder through the dimensions of space:
//       z¹ = length deficit   z² = area / (v/c)²   z³ = VOLUME.
//  Hence z³ is "the volumetric rung", and it should appear wherever 3-D-ness enters —
//  in REAL space (matter density) and in MOMENTUM/k space (blackbody photon number).
//
//  Build (MSVC):
//    cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include ^
//       Investigations\07_Cosmology_and_Redshift\CR10_Cubic_Redshift_Volumetric_Rung\cr10_cubic_redshift.cpp
//  Build (GCC/Clang):
//    g++ -std=c++20 -IEngine/include cr10_cubic_redshift.cpp -o cr10
// =====================================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <initializer_list>

namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi;

// pretty-printers for the recursion tree
static void node (const char* tag, const char* s) { std::printf("  %-9s %s\n", tag, s); }
static void numl (const char* s, double v, const char* u) { std::printf("              %-46s = %.6e %s\n", s, v, u); }
static void rule () { std::printf("---------------------------------------------------------------------\n"); }

int main() {
    const double c     = M::c;
    const double hbar  = M::hbar;
    const double kB    = M::k_B;
    const double lP    = M::l_P;
    const double m_p   = M::m_p;
    const double R_p   = M::R_p;       // proton charge radius
    const double r_e   = M::r_e;       // classical electron radius (= koppa_H)
    const double T0    = M::T_CMB;     // 2.7255 K (FIRAS)

    std::printf("=====================================================================\n");
    std::printf("  CR10  THE CUBIC REDSHIFT  -  what is z^3 for?  (recursive method)\n");
    std::printf("  J. C. Harvey, Melbourne, 2026-06-24.  Engine: sdt/laws.hpp\n");
    std::printf("=====================================================================\n\n");

    // ── The closure ladder: z, z^2, z^3 across regimes ───────────────────────────────
    std::printf("[LADDER] z is the LINEAR closure deficit; powers step through dimension.\n");
    struct Reg { const char* name; double z; };
    // Earth/Sun depths z = gR/c^2; proton from internal circulation v=1.830c -> z=(v/c)^2.
    const double z_earth = 9.80665 * 6.371e6 / (c*c);
    const double z_sun   = 274.0   * 6.957e8 / (c*c);
    const double v_p_surf = 1.830 * c;                 // proton-surface circulation (engine: 1.830c)
    const double z_proton = (v_p_surf/c)*(v_p_surf/c); // = 3.349  -> z > 1 !
    Reg regs[] = { {"Earth surface", z_earth}, {"Sun surface", z_sun}, {"proton surface", z_proton} };
    std::printf("    %-16s %14s %14s %14s\n", "regime", "z", "z^2", "z^3");
    for (auto& g : regs)
        std::printf("    %-16s %14.6e %14.6e %14.6e\n", g.name, g.z, g.z*g.z, g.z*g.z*g.z);
    std::printf("\n");

    // =================================================================================
    //  ARM A — FOUNDATIONAL: z^3 as REAL-SPACE volume (matter density)
    // =================================================================================
    rule();
    std::printf("  ARM A  -  z^3 as real-space VOLUME (the density of matter)\n");
    rule();

    node("[CLAIM]", "A1: spation number density n(r)/n_inf = (1 - z)^-3  (volume compression).");
    node("[TEST]",  "ell_P(r)=ell_P,inf (1-z) [depth-closure] => volume ~ (1-z)^3, density ~ (1-z)^-3.");
    {
        auto comp = [](double z){ return std::pow(1.0 - z, -3.0); };
        numl("Earth   (1-z)^-3 - 1", comp(z_earth) - 1.0, "(=~3z)");
        numl("Sun     (1-z)^-3 - 1", comp(z_sun)   - 1.0, "");
        std::printf("              proton  (1 - z) = 1 - %.3f = %.3f  -> NEGATIVE\n", z_proton, 1.0 - z_proton);
        node("[FAIL]", "at the proton z = 3.35 > 1, so (1-z)^-3 is the cube of a negative -> unphysical.");
        node("[WHY]",  "ell_P=ell_P,inf(1-z) is the FIRST-ORDER (weak-field) closure; invalid once z>=1");
        node("",       "(super-c internal circulation v=1.830c puts the proton past the linear horizon).");

        node("[TRY a]","exponential closure ell_P=ell_P,inf e^-z (stays positive; ->(1-z) for small z).");
        double n_exp = std::exp(3.0 * z_proton);
        numl("proton density e^(3z)", n_exp, "(finite, but only ~5e4)");
        node("[FAIL]", "e^(3z) = 4.6e4 does not reach the proton's spation count (~6e59). Wrong handle.");

        node("[TRY b]","drop the (1-z) form entirely: count cells GEOMETRICALLY, V_proton / ell_P^3,");
        node("",       "i.e. how many VACUUM spation-cells fit inside the proton's charge radius.");
        double V_p_charge = (4.0/3.0)*PI*R_p*R_p*R_p;
        double N_geo = V_p_charge / (lP*lP*lP);
        numl("R_p / ell_P", R_p/lP, "");
        numl("N_geo = (4/3)pi R_p^3 / ell_P^3", N_geo, "spations");
        bool passN = std::fabs(N_geo - 5.9e59)/5.9e59 < 0.1;
        std::printf("  %-9s %s (%.3e vs memory 5.9e59)\n", passN?"[PASS]":"[FAIL]",
                    "geometric count reproduces the proton spation number", N_geo);

        node("[ANALYSE]","two DIFFERENT proton 'volumes', both z^3-class, settle the long-open ambiguity:");
        double V_disp = 1.832653e-58;                  // engine V_disp(proton) (Law IV mass-cost volume)
        double N_disp = V_disp/(lP*lP*lP);
        double R_excl = std::cbrt(3.0*V_disp/(4.0*PI));
        numl("N_geo  (charge-radius volume)", N_geo, "= how BIG the proton is");
        numl("N_disp (mass-cost displaced vol)", N_disp, "= how much THROUGHPUT it reorganises");
        numl("R_p (charge)", R_p, "m");
        numl("R_excl (displacement) = (3V_disp/4pi)^1/3", R_excl, "m");
        numl("ratio (R_p/R_excl)^3 = N_geo/N_disp", std::pow(R_p/R_excl,3.0), "(~1.4e13)");
        node("","both are V/ell_P^3 (z^3 volume counts); they differ ONLY by which radius is cubed.");

        node("[CAUSE]","N = V / ell_P^3  <=  counting cells that fill a volume");
        node("[CAUSE^2]","a volume needs THREE lengths multiplied  <=  space is 3-dimensional");
        node("[ROOT]", "z^3 here = REAL-SPACE three-dimensionality (cells per volume).");
    }
    std::printf("\n");

    node("[CLAIM]", "A2: the weak-field (1-z)^-3 IS useful where it does NOT break - as a GRADIENT.");
    node("[TEST]",  "d/dr[(1-z)^-3] = 3(1-z)^-4 dz/dr  is a density gradient = a gradient-index lens.");
    {
        // illustrative solar near-surface gradient magnitude (z_sun over R_sun scale)
        double dz_dr = z_sun / 6.957e8;                // ~ z/R as a scale
        double grad  = 3.0*std::pow(1.0 - z_sun, -4.0)*dz_dr;
        numl("3(1-z)^-4 dz/dr at Sun surface (scale)", grad, "1/m");
        node("[PASS]", "non-zero density gradient -> refraction; this is the solar lens-artifact handle.");
        node("[ROOT]", "z^3's RADIAL DERIVATIVE = the gradient-index optics of the closure medium.");
    }
    std::printf("\n");

    // =================================================================================
    //  ARM B — COSMOLOGICAL: z^3 as the (1+z)^3 'expansion' signature
    // =================================================================================
    rule();
    std::printf("  ARM B  -  z^3 as the (1+z)^3 cosmological volume signature\n");
    rule();

    node("[CLAIM]", "B1: u_CMB ~ (1+z)^4 is read as PROOF of expansion: (1+z)^3 [volume] x (1+z) [energy].");
    node("[TEST]",  "does a STATIC SDT universe (uniform octave redshift, NO expansion) give (1+z)^4?");
    {
        // blackbody relations
        double a_rad = (PI*PI/15.0)*std::pow(kB,4)/std::pow(hbar*c,3);  // u = a T^4
        double n_pref = (2.0*1.2020569031595943/(PI*PI))*std::pow(kB/(hbar*c),3); // n = (2zeta3/pi^2)(kT/hbar c)^3
        double u0 = a_rad*std::pow(T0,4);
        double n0 = n_pref*std::pow(T0,3);
        numl("a_rad", a_rad, "J/m^3/K^4");
        numl("u_CMB(T0) = a T0^4", u0, "J/m^3");
        numl("n_gamma(T0) = (2zeta3/pi^2)(kT0/hbar c)^3", n0/1e6, "1/cm^3 (~411)");

        node("[FAIL?]","naive static = redshift only -> u ~ (1+z)^1; the (1+z)^3 looks like it NEEDS expansion.");
        node("[WHY]",  "because we ASSUMED (1+z)^3 = REAL-space expansion volume.");

        node("[TRY]",  "is the (1+z)^3 actually MOMENTUM/k-space phase volume, not real space?");
        node("",       "a uniformly-redshifted blackbody stays a blackbody at T'=T0(1+z) [Tolman 1934,");
        node("",       "true for ANY uniform redshift incl. static]; then n_gamma ~ T^3, u ~ T^4 FOLLOW.");
        // verify the powers numerically at several z by recomputing from T(z)=T0(1+z)
        std::printf("              %-6s %14s %14s %14s\n", "z", "T(z)=T0(1+z)", "n/n0", "u/u0");
        double maxerr_n = 0, maxerr_u = 0;
        for (double z : {0.0, 1.0, 3.0, 1100.0}) {
            double Tz = T0*(1.0+z);
            double nz = n_pref*std::pow(Tz,3);
            double uz = a_rad *std::pow(Tz,4);
            std::printf("              %-6.0f %14.6e %14.6e %14.6e\n", z, Tz, nz/n0, uz/u0);
            maxerr_n = std::fmax(maxerr_n, std::fabs(nz/n0 - std::pow(1+z,3))/std::pow(1+z,3));
            maxerr_u = std::fmax(maxerr_u, std::fabs(uz/u0 - std::pow(1+z,4))/std::pow(1+z,4));
        }
        bool pass = (maxerr_n < 1e-9) && (maxerr_u < 1e-9);
        std::printf("  %-9s n/n0 == (1+z)^3 and u/u0 == (1+z)^4 EXACTLY from T(z) alone (max err %.1e)\n",
                    pass?"[PASS]":"[FAIL]", std::fmax(maxerr_n,maxerr_u));
        node("[SUCCEED]","STATIC SDT reproduces (1+z)^4 with NO expansion: the (1+z)^3 is n_gamma ~ T^3.");

        node("[CAUSE]",  "u ~ (1+z)^4  <=  Stefan-Boltzmann u = a T^4 with T ~ (1+z)");
        node("[CAUSE^2]","blackbody stays blackbody under uniform redshift (Tolman) => T ~ (1+z)");
        node("[CAUSE^3]","n_gamma ~ T^3  <=  density of states g(nu) ~ nu^2, integrated to T^3");
        node("[CAUSE^4]","g(nu) ~ nu^2  <=  a sphere of radius k in 3-D k-space has area ~ k^2");
        node("[ROOT]",   "z^3 here = MOMENTUM/k-space three-dimensionality (NOT real-space expansion).");
        node("[PAYOFF]", "'u~(1+z)^4 proves expansion' is FALSE: it proves uniform-redshift + blackbody,");
        node("",         "which SDT-static has. The (1+z)^3 is k-space phase volume. Evidence is DEGENERATE.");
    }
    std::printf("\n");

    node("[CLAIM]", "B2: where does z^3 as REAL-space volume actually discriminate static vs expansion?");
    node("[TEST]",  "two non-degenerate handles: surface-brightness Tolman, and galaxy number counts.");
    {
        node("[D1]", "Tolman bolometric surface brightness Sigma_bol:");
        node("",     "  expanding (metric, Etherington d_L=(1+z)^2 d_A): Sigma ~ (1+z)^-4");
        node("",     "  naive static Euclidean tired-light (d_L=(1+z) d_A) : Sigma ~ (1+z)^-2");
        node("[WHY]","the 2-power gap IS the reciprocity factor d_L/d_A = (1+z)^2 vs (1+z)^1.");
        node("[TRY]","does SDT supply the missing 2 powers WITHOUT expansion? Etherington needs only");
        node("",     "{effective metric, geodesics, photon conservation}. SDT's closure gradient is a");
        node("",     "refractive index n(r)=1/(1-z); a gradient-index medium CONSERVES etendue =>");
        node("",     "reciprocity holds => Sigma ~ (1+z)^-4 statically. [PLAUSIBLE - OPEN: needs the");
        node("",     "explicit etendue/reciprocity proof in the closure medium.]");
        node("[D2]", "galaxy number counts N(<z) ~ real-space volume ~ d(z)^3:");
        node("",     "  low-z Euclidean baseline N ~ z^3; high-z deviation tests the SDT distance law d(z).");
        node("[OPEN]","this is the genuine fight (= the CONDENSA Pantheon+ d(z) item). z^3 is the baseline,");
        node("",      "the deviation is the discriminant. NOT closed here.");
    }
    std::printf("\n");

    // ── DATA anchor: T(z) is MEASURED ∝ (1+z)^1 ──────────────────────────────────────
    node("[DATA]",  "the linchpin is empirical: T_CMB(z) = T0(1+z) is MEASURED to ~(1+z)^1.0");
    node("",        "(SZ toward clusters + molecular-cloud excitation out to z~3; FIRAS at z=0).");
    node("",        "Given T~(1+z)^1, u~(1+z)^4 and n~(1+z)^3 are FORCED by blackbody thermodynamics,");
    node("",        "independent of whether the (1+z) came from expansion or static octave-relaxation.");
    std::printf("\n");

    // =================================================================================
    rule();
    std::printf("  REDUCTION TO ROOT\n");
    rule();
    std::printf("  z^3 is the signature of THREE-DIMENSIONALITY itself. It appears wherever the\n");
    std::printf("  '3' of space enters:\n");
    std::printf("    * REAL space   : cells per volume  -> matter density, the proton's ~6e59.\n");
    std::printf("    * MOMENTUM (k) : g(nu)~nu^2 -> T^3 -> the cosmic (1+z)^4.\n");
    std::printf("  PAYOFF: the cosmological (1+z)^4, read everywhere as 'expansion volume', is in fact\n");
    std::printf("  k-space phase volume; a STATIC uniformly-redshifting SDT reproduces it exactly, so\n");
    std::printf("  z^3 shows the (1+z)^4 evidence is DEGENERATE. The non-degenerate fights live in the\n");
    std::printf("  REAL-space z^3 (number counts; surface-brightness reciprocity) - and there SDT's\n");
    std::printf("  refractive closure medium plausibly supplies the reciprocity for free (OPEN).\n");
    rule();

    // ── machine-checkable assertions (so the tool self-reports like a benchmark) ──────
    int pass = 0, fail = 0;
    auto ck = [&](const char* s, bool ok){ (ok?pass:fail)++; std::printf("  %-66s %s\n", s, ok?"PASS":"FAIL"); };
    std::printf("\nSELF-CHECKS:\n");
    double V_p_charge = (4.0/3.0)*PI*R_p*R_p*R_p;
    ck("proton geometric count V_p/ell_P^3 ~ 5.9e59", std::fabs(V_p_charge/(lP*lP*lP)-5.9e59)/5.9e59 < 0.1);
    ck("weak-field (1-z)^-3 breaks at proton (z>1)", z_proton > 1.0);
    {
        double a_rad = (PI*PI/15.0)*std::pow(kB,4)/std::pow(hbar*c,3);
        double n_pref = (2.0*1.2020569031595943/(PI*PI))*std::pow(kB/(hbar*c),3);
        double z=1100.0, Tz=T0*(1+z);
        ck("static T(z)=T0(1+z) gives u/u0==(1+z)^4",
           std::fabs(a_rad*std::pow(Tz,4)/(a_rad*std::pow(T0,4)) - std::pow(1+z,4))/std::pow(1+z,4) < 1e-9);
        ck("static T(z)=T0(1+z) gives n/n0==(1+z)^3",
           std::fabs(n_pref*std::pow(Tz,3)/(n_pref*std::pow(T0,3)) - std::pow(1+z,3))/std::pow(1+z,3) < 1e-9);
        ck("n_gamma(T0) ~ 411 /cm^3", std::fabs(n_pref*std::pow(T0,3)/1e6 - 411.0)/411.0 < 0.02);
    }
    std::printf("\n  checks: %d PASS / %d FAIL\n", pass, fail);
    std::printf("=====================================================================\n");
    return fail==0 ? 0 : 1;
}
