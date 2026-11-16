// =====================================================================
//  GD09 : Milky Way baryon inventory — observed masses of each portion
//  converted to baryon counts through the engine's own census.
//  ---------------------------------------------------------------------
//  N_b = (M / M_Sun) * N_Sun,   N_Sun = bridge::N_baryons(bridge::koppa_Sun)
//  M_Sun in kilograms is not used in any count (reference check V1 only).
//  Masses: OBSERVED (source and estimation chain named per row). Counts: COMPUTED.
//  Pre-registration: PROMPT.md (same folder). No SDT claim is made from the record.
//
//  Build: cl /std:c++20 /EHsc /O2 /I Engine/include gd09_baryon_inventory.cpp
//  Writes: baryon_inventory.csv  mw_baryons.js
//
//  Author: SDT Canonical Engine — J. C. Harvey, Melbourne
// =====================================================================

#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <sdt/laws.hpp>

namespace {

using namespace sdt::laws;

struct Row {
    const char* id;
    const char* group;
    const char* label;
    double lo, c, hi;          // solar masses
    const char* standing;      // KNOWN / ESTIMATED / SUSPECTED
    const char* role;          // additive / nested / reference / total
    const char* source;
    const char* note;
};

// ±  : lo = c - s, hi = c + s.   range : c = midpoint.
constexpr Row pm(const char* id, const char* g, const char* l, double c, double s, const char* st,
                 const char* role, const char* src, const char* note) {
    return {id, g, l, c - s, c, c + s, st, role, src, note};
}
constexpr Row rg(const char* id, const char* g, const char* l, double lo, double hi, const char* st,
                 const char* role, const char* src, const char* note) {
    return {id, g, l, lo, 0.5 * (lo + hi), hi, st, role, src, note};
}

const char* BHG = "Bland-Hawthorn & Gerhard 2016, ARA&A 54, 529";
const char* KUB = "Kubryk, Prantzos & Athanassoula 2015, A&A 580, A126 (compilation)";

// All masses in M_Sun, as the sources state them (no R0 rescaling).
const Row ROWS[] = {
    pm("smbh", "Nucleus", "Sgr A* black hole", 4.2e6, 0.2e6, "KNOWN", "reference",
       "BHG16 Sec.3 (stellar orbits, R0=8.2 kpc)", "dynamical mass; baryon content not observed; excluded from the stellar partition"),
    pm("nsc", "Nucleus", "Nuclear star cluster", 1.8e7, 0.3e7, "ESTIMATED", "nested",
       "BHG16 Sec.4.1 (Schoedel+2014, Sersic model, M/L_4.5)", "dynamical mass within 4 pc is 8.9e6"),
    pm("nsd", "Nucleus", "Nuclear stellar disc", 1.4e9, 0.6e9, "ESTIMATED", "nested",
       "BHG16 Sec.4.1 (Launhardt+2002)", "about 10% of the bulge mass"),
    rg("bulge_stellar", "Bulge", "b/p bulge region, stellar (incl. inner-disc stars)", 1.4e10, 1.7e10, "ESTIMATED", "additive",
       "BHG16 Sec.4.2.4 (Portail+2015, VVV box +-2.2 x +-1.4 x +-1.2 kpc)", "Kroupa/Chabrier-type IMF"),
    pm("bulge_dynamical", "Bulge", "b/p bulge region, dynamical (reference)", 1.84e10, 0.07e10, "ESTIMATED", "reference",
       "BHG16 Sec.4.2.4 (Portail+2015)", "includes 10-25% dark matter: not a baryon count"),
    rg("bar_thin", "Bar", "Long bar, thin component", 6e9, 8e9, "ESTIMATED", "nested",
       "BHG16 Sec.4.3 (Wegg+2015, RCG + Kroupa IMF, 10 Gyr)", "part of the disc mass (BHG16 Sec.6.4.4)"),
    pm("bar_superthin", "Bar", "Long bar, super-thin component", 3.3e9, 0.0, "ESTIMATED", "nested",
       "BHG16 Sec.4.3 (Wegg+2015, constant past SFR)", "no uncertainty stated; low = high = central"),
    pm("disc_thin", "Disc", "Thin disc, stellar", 3.5e10, 1.0e10, "ESTIMATED", "additive",
       "BHG16 Sec.5.1.3", "R_t = 2.6 +- 0.5 kpc"),
    pm("disc_thick", "Disc", "Thick disc, stellar", 6e9, 3e9, "ESTIMATED", "additive",
       "BHG16 Sec.5.2.2", "R_T = 2.0 +- 0.2 kpc; about a fifth of the thin disc"),
    rg("halo_stellar", "Halo", "Stellar halo (incl. substructure)", 4e8, 7e8, "ESTIMATED", "additive",
       "BHG16 Sec.6.1.2", "Bell+2008 3.7e8 within 1-40 kpc plus ~50% of substructure"),
    rg("halo_substructure", "Halo", "Halo substructure (within the halo row)", 2e8, 3e8, "ESTIMATED", "nested",
       "BHG16 Sec.6.1.2", "Sgr stream, anticentre, Virgo, Hercules-Aquila"),
    pm("stellar_total", "Totals", "Total stellar mass", 5e10, 1e10, "ESTIMATED", "total",
       "BHG16 Sec.6.4.4", "dynamical models gave 4.7-5.7e10"),
    pm("hi", "Gas", "Atomic hydrogen HI (2-19 kpc, hydrogen only)", 4.9e9, 2.2e9, "ESTIMATED", "nested",
       KUB, "Table A.1 adopted average; entries 2.75e9 to 7.7e9; part of the helium-inclusive disc gas row; HI beyond 19 kpc not counted"),
    pm("h2", "Gas", "Molecular hydrogen H2 (2-19 kpc, hydrogen only)", 0.9e9, 0.35e9, "ESTIMATED", "nested",
       KUB, "Table A.1 adopted average; Miville-Deschenes+2017 abstract gives 1.2e9; part of the helium-inclusive disc gas row"),
    pm("gas_disc_He", "Gas", "Cold gas incl. helium, disc 2-19 kpc", 8.1e9, 4.5e9, "ESTIMATED", "additive_gas",
       KUB, "Table 1; total = 1.4 x (HI + H2), helium 28% by mass; baryon count includes the helium nucleons"),
    pm("gas_bulge", "Gas", "Cold gas incl. helium, bulge <2 kpc", 1.1e9, 0.8e9, "ESTIMATED", "additive_gas",
       KUB, "Table 1 (Ferriere+2007); gas-mass row carries the helium footnote"),
    pm("corona", "Corona", "Hot gas corona within r_vir", 2.5e10, 1.0e10, "SUSPECTED", "additive_corona",
       "BHG16 Sec.6.2 (Tepper-Garcia+2015); Miller & Bregman ~1e10 within 250 kpc", "inferred from X-ray/UV absorption and emission under model assumptions"),
    pm("stars_cold", "Totals", "Stars + cold gas", 6.3e10, 0.5e10, "ESTIMATED", "total",
       "BHG16 Sec.6.2 (dynamical models with disc fitting)", "rescaled to R0 = 8.3 kpc by the source"),
    pm("baryon_total_text", "Totals", "Total baryonic incl. corona (text value)", 8.8e10, 1.2e10, "SUSPECTED", "total",
       "BHG16 Sec.6.2 text", "the source also states 8.5 +- 1.3 e10 in its sidebar"),
    pm("baryon_total_sidebar", "Totals", "Total baryonic incl. corona (sidebar value)", 8.5e10, 1.3e10, "SUSPECTED", "total",
       "BHG16 Sec.6.2 sidebar", "differs from the text value in the same source"),
};
constexpr int NR = sizeof(ROWS) / sizeof(ROWS[0]);

int g_fail = 0;
void check(const char* id, const char* what, bool ok, double v) {
    std::printf("  [%s] %s : %s  (%.3e)\n", ok ? "PASS" : "FAIL", id, what, v);
    if (!ok) ++g_fail;
}

} // namespace

int main() {
    const double koppa_Sun = bridge::koppa_Sun;
    const double N_Sun = bridge::N_baryons(koppa_Sun);                 // engine census; no kilograms
    auto toN = [&](double M) { return M * N_Sun; };                    // M in solar masses
    auto toM = [&](double N) { return N / N_Sun; };

    std::printf("=================================================================\n");
    std::printf(" GD09 MILKY WAY BARYON INVENTORY\n");
    std::printf(" masses OBSERVED (source-stated) ; counts COMPUTED ; 0 fitted\n");
    std::printf("=================================================================\n");
    std::printf("koppa_Sun = %.4f m ; koppa_per_baryon = %.4e m ; N_Sun = %.4e baryons\n\n",
                koppa_Sun, bridge::koppa_per_baryon, N_Sun);

    // ---------------- instrument validation ----------------
    std::printf("== INSTRUMENT VALIDATION ==\n");
    {
        const double M_Sun_nominal_kg = 1.98841e30;                    // reference only
        double ref = M_Sun_nominal_kg / measured::m_p;
        check("V1", "N_Sun engine census vs M_Sun,nominal/m_p (1%, reference only)",
              std::fabs(N_Sun / ref - 1.0) < 0.01, N_Sun / ref - 1.0);
        double md = 0;
        for (int i = 0; i < NR; ++i) md = std::fmax(md, std::fabs(toM(toN(ROWS[i].c)) / ROWS[i].c - 1.0));
        check("V2", "round trip N -> M -> N", md < 1e-12, md);
        bool ok = true;
        for (int i = 0; i < NR; ++i) ok = ok && toN(ROWS[i].lo) <= toN(ROWS[i].c) && toN(ROWS[i].c) <= toN(ROWS[i].hi);
        check("V3", "low <= central <= high for every row", ok, 0.0);
        double bar = ROWS[5].c + ROWS[6].c;                            // thin + super-thin
        double r = bar / 1e10;
        check("V4", "long-bar sum within 1.2x of the stated ~1e10", r > 1.0 / 1.2 && r < 1.2, r);
    }
    std::printf("  validation failures: %d\n\n", g_fail);
    if (g_fail) { std::printf("validation failed — inventory not recorded.\n"); return 1; }

    // ---------------- table ----------------
    std::printf("== BARYON COUNTS (N = M/M_Sun x N_Sun) ==\n");
    std::printf("%-44s %-9s %-10s %10s %10s %10s | %9s %9s %9s\n", "component", "standing", "role", "M_lo", "M_c", "M_hi",
                "N_lo", "N_c", "N_hi");
    for (int i = 0; i < NR; ++i) {
        const Row& r = ROWS[i];
        std::printf("%-44s %-9s %-10s %10.3e %10.3e %10.3e | %9.2e %9.2e %9.2e\n", r.label, r.standing, r.role,
                    r.lo, r.c, r.hi, toN(r.lo), toN(r.c), toN(r.hi));
    }

    // ---------------- single-pass comparison ----------------
    std::printf("\n== STELLAR PARTITION vs TOTAL STELLAR MASS (criterion |d| <= 1 sigma_combined) ==\n");
    const char* part[] = {"bulge_stellar", "disc_thin", "disc_thick", "halo_stellar"};
    double sum = 0, var = 0;
    for (const char* id : part)
        for (int i = 0; i < NR; ++i) if (std::string(ROWS[i].id) == id) {
            double s = 0.5 * (ROWS[i].hi - ROWS[i].lo);
            sum += ROWS[i].c; var += s * s;
            std::printf("  %-36s %10.3e +- %9.2e\n", ROWS[i].label, ROWS[i].c, s);
        }
    double Mtot = 5e10, stot = 1e10;
    double sig = std::sqrt(var + stot * stot), d = sum - Mtot;
    std::printf("  partition sum %.3e ; source total %.3e ; difference %+.3e ; sigma_combined %.3e ; |d|/sigma = %.2f  -> %s\n",
                sum, Mtot, d, sig, std::fabs(d) / sig, std::fabs(d) <= sig ? "consistent" : "inconsistent");
    std::printf("  partition N = %.3e ; total-stellar N = %.3e\n", toN(sum), toN(Mtot));

    // ---------------- component roll-up (additive rows only) ----------------
    double st = sum, gas = 0, gvar = 0;
    for (int i = 0; i < NR; ++i) if (std::string(ROWS[i].role) == "additive_gas") {
        gas += ROWS[i].c; double s = 0.5 * (ROWS[i].hi - ROWS[i].lo); gvar += s * s;
    }
    std::printf("\n== ROLL-UP (additive rows) ==\n");
    std::printf("stars (partition)     M = %.3e  N = %.3e\n", st, toN(st));
    std::printf("cold gas (disc 2-19 kpc + bulge <2 kpc, helium included) M = %.3e +- %.2e  N = %.3e\n",
                gas, std::sqrt(gvar), toN(gas));
    std::printf("hot corona            M = %.3e  N = %.3e  [SUSPECTED]\n", 2.5e10, toN(2.5e10));
    std::printf("source total (text)   M = %.3e  N = %.3e ; sidebar value %.3e (the source states both)\n", 8.8e10, toN(8.8e10), 8.5e10);

    // ---------------- outputs ----------------
    FILE* csv = std::fopen("baryon_inventory.csv", "w");
    FILE* js = std::fopen("mw_baryons.js", "w");
    if (!csv || !js) { std::printf("cannot open outputs\n"); return 1; }
    std::fprintf(csv, "id,group,component,standing,role,M_lo_Msun,M_c_Msun,M_hi_Msun,N_lo,N_c,N_hi,source,note\n");
    std::fprintf(js, "// Generated by gd09_baryon_inventory.cpp. N = M/M_Sun x N_Sun (engine census).\n");
    std::fprintf(js, "window.MW_BARYONS={nSun:%.6e,koppaSun:%.4f,rows:[\n", N_Sun, koppa_Sun);
    for (int i = 0; i < NR; ++i) {
        const Row& r = ROWS[i];
        std::fprintf(csv, "%s,%s,\"%s\",%s,%s,%.6e,%.6e,%.6e,%.6e,%.6e,%.6e,\"%s\",\"%s\"\n", r.id, r.group, r.label, r.standing,
                     r.role, r.lo, r.c, r.hi, toN(r.lo), toN(r.c), toN(r.hi), r.source, r.note);
        std::fprintf(js, "{id:\"%s\",group:\"%s\",label:\"%s\",standing:\"%s\",role:\"%s\",m:[%.6e,%.6e,%.6e],n:[%.6e,%.6e,%.6e],"
                         "source:\"%s\",note:\"%s\"}%s\n",
                     r.id, r.group, r.label, r.standing, r.role, r.lo, r.c, r.hi, toN(r.lo), toN(r.c), toN(r.hi), r.source, r.note,
                     i + 1 < NR ? "," : "");
    }
    std::fprintf(js, "]};\n");
    std::fclose(csv); std::fclose(js);
    std::printf("\nwrote baryon_inventory.csv, mw_baryons.js\n");
    return 0;
}
