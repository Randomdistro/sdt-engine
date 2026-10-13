// =============================================================================
// CQ19c — MW Disk Ring Map: 100 Concentric Rings
//
// Divides the entire MW from Sag A* to disk edge (15 kpc) into 100
// concentric rings. Ring 1 (innermost) is populated with every
// individually known star in the central ~150 pc.
//
// Each star entry: name, type, r_from_SagA, position_angle, l, b
// Structure is enrichable — add stars as new data arrives.
//
// No G. No M. zk² = 1.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static constexpr double kpc_m = 3.085677581e19;
static constexpr double pc_m  = 3.085677581e16;
static constexpr double yr_s  = 365.25 * 86400.0;

// =============================================================================
// RING DEFINITION — 100 concentric rings, log-spaced inner, linear outer
// =============================================================================

static constexpr int    N_RINGS     = 100;
static constexpr double R_DISK_KPC  = 15.0;    // disk truncation radius [kpc]
static constexpr double R0_KPC      = 8.178;   // Sun's position [kpc]

struct Ring {
    int    id;
    double r_inner_pc;
    double r_outer_pc;
    double r_mid_pc;
    int    n_cataloged;  // known individually cataloged stars
};

// First 10 rings logarithmic (0.01 pc to 150 pc), remaining 90 linear
static std::vector<Ring> build_rings() {
    std::vector<Ring> rings;

    // Rings 1-10: logarithmic from 0 to 150 pc
    double log_boundaries[] = {
        0.0, 0.01, 0.04, 0.1, 0.5, 1.0, 5.0, 20.0, 50.0, 100.0, 150.0
    };
    for (int i = 0; i < 10; i++) {
        Ring r;
        r.id = i + 1;
        r.r_inner_pc = log_boundaries[i];
        r.r_outer_pc = log_boundaries[i + 1];
        r.r_mid_pc = (r.r_inner_pc + r.r_outer_pc) / 2.0;
        r.n_cataloged = 0;
        rings.push_back(r);
    }

    // Rings 11-100: linear from 150 pc to 15000 pc (15 kpc)
    double dr = (15000.0 - 150.0) / 90.0;  // ~165 pc per ring
    for (int i = 0; i < 90; i++) {
        Ring r;
        r.id = i + 11;
        r.r_inner_pc = 150.0 + i * dr;
        r.r_outer_pc = 150.0 + (i + 1) * dr;
        r.r_mid_pc = (r.r_inner_pc + r.r_outer_pc) / 2.0;
        r.n_cataloged = 0;
        rings.push_back(r);
    }

    return rings;
}

// =============================================================================
// STAR CATALOGUE — enrichable
//
// Every individually named/cataloged star in the GC region.
// Position: (r, PA) relative to Sag A*, plus galactic (l, b).
// Sag A* is at l = 359.944°, b = -0.046°
//
// Sources: Gillessen et al. 2017, Genzel et al. 2010, Paumard et al. 2006,
//          Fritz et al. 2016, GRAVITY Collaboration 2020+
// =============================================================================

struct Star {
    const char* name;
    const char* type;       // spectral/object type
    double r_arcsec;        // distance from Sag A* [arcsec]
    double PA_deg;          // position angle [degrees, N through E]
    double r_pc;            // physical distance from Sag A* [pc]
    double l_deg;           // galactic longitude
    double b_deg;           // galactic latitude
    int    ring_id;         // which ring this star belongs to
};

// 1 arcsec at 8.178 kpc = 0.03965 pc
static constexpr double ARCSEC_TO_PC = R0_KPC * 1000.0 / 206264.806;
// Sag A* galactic coords
static constexpr double L_SGRA = 359.944;
static constexpr double B_SGRA = -0.046;

static int assign_ring(double r_pc, const std::vector<Ring>& rings) {
    for (const auto& ring : rings) {
        if (r_pc >= ring.r_inner_pc && r_pc < ring.r_outer_pc)
            return ring.id;
    }
    return N_RINGS; // beyond last ring
}

static std::vector<Star> build_catalog(const std::vector<Ring>& rings) {
    std::vector<Star> catalog;

    auto add = [&](const char* name, const char* type,
                   double r_as, double PA) {
        Star s;
        s.name = name;
        s.type = type;
        s.r_arcsec = r_as;
        s.PA_deg = PA;
        s.r_pc = r_as * ARCSEC_TO_PC;
        // Approximate galactic coords (offset from Sag A*)
        double dl = r_as * sin(PA * M_PI / 180.0) / 3600.0;
        double db = r_as * cos(PA * M_PI / 180.0) / 3600.0;
        s.l_deg = L_SGRA + dl;
        s.b_deg = B_SGRA + db;
        s.ring_id = assign_ring(s.r_pc, rings);
        catalog.push_back(s);
    };

    // Enriched catalogue: ~280 stars from published sources
    // Gillessen+2017, Peissker+2020/2022, Paumard+2006, Genzel+2010,
    // Figer+2002, Clark+2018, Liermann+2009, Mauerhan+2010, Fritz+2016
    #include "cq19c_star_data.hpp"

    return catalog;
}

// =============================================================================
// MAIN
// =============================================================================

int main() {
    printf("###################################################################\n");
    printf("   CQ19c: MW Disk Ring Map — 100 Concentric Rings\n");
    printf("   Ring 1 catalogue: every known star near Sag A*\n");
    printf("   Enrichable structure — add stars as data arrives\n");
    printf("###################################################################\n\n");

    auto rings = build_rings();
    auto catalog = build_catalog(rings);

    // Count stars per ring
    for (auto& star : catalog) {
        for (auto& ring : rings) {
            if (star.ring_id == ring.id) ring.n_cataloged++;
        }
    }

    // ---- Ring summary ----
    printf("=== RING STRUCTURE (100 rings, Sag A* to 15 kpc) ===\n\n");
    printf("   %-6s  %10s  %10s  %10s  %8s\n",
           "Ring", "r_inner[pc]", "r_outer[pc]", "width[pc]", "N_stars");
    printf("   %-6s  %10s  %10s  %10s  %8s\n",
           "────", "──────────", "──────────", "────────", "───────");

    int total_cat = 0;
    for (const auto& r : rings) {
        if (r.n_cataloged > 0 || r.id <= 10) {
            printf("   %4d    %10.3f  %10.1f  %10.3f  %8d",
                   r.id, r.r_inner_pc, r.r_outer_pc,
                   r.r_outer_pc - r.r_inner_pc, r.n_cataloged);
            if (r.id <= 10) {
                const char* labels[] = {"","Sag A* vicinity","Inner S-cluster",
                    "Outer S-cluster","Extended S + IRS","Central pc edge",
                    "Nuclear Cluster","Arches/Quintuplet","CMZ clouds",
                    "Outer CMZ","Inner bulge"};
                printf("  ← %s", labels[r.id]);
            }
            printf("\n");
        }
        total_cat += r.n_cataloged;
    }
    printf("\n   Total cataloged stars: %d\n\n", total_cat);

    // ---- Ring 1-4 detailed catalogue (the innermost structures) ----
    printf("=== DETAILED CATALOGUE: RINGS 1-6 ===\n\n");
    printf("   All individually known objects within ~5 pc of Sag A*\n");
    printf("   Sag A* at l = %.3f°, b = %.3f°\n\n", L_SGRA, B_SGRA);

    // Group by ring
    for (int ring_id = 1; ring_id <= 6; ring_id++) {
        // Find ring
        const Ring* ring = nullptr;
        for (const auto& r : rings) {
            if (r.id == ring_id) { ring = &r; break; }
        }
        if (!ring) continue;

        int count = 0;
        for (const auto& s : catalog) if (s.ring_id == ring_id) count++;
        if (count == 0) {
            printf("   ── Ring %d (%.3f - %.1f pc): [empty — no individually cataloged stars]\n\n",
                   ring_id, ring->r_inner_pc, ring->r_outer_pc);
            continue;
        }

        printf("   ── Ring %d (%.3f - %.1f pc): %d stars ──\n\n",
               ring_id, ring->r_inner_pc, ring->r_outer_pc, count);
        printf("   %-12s %-12s %8s %8s %10s %10s %10s\n",
               "Name", "Type", "r[\"]", "PA[°]", "r[pc]", "l[°]", "b[°]");
        printf("   %-12s %-12s %8s %8s %10s %10s %10s\n",
               "────────────","────────────","──────","──────",
               "────────","────────","────────");

        // Sort by PA within ring
        std::vector<const Star*> ring_stars;
        for (const auto& s : catalog) {
            if (s.ring_id == ring_id) ring_stars.push_back(&s);
        }
        std::sort(ring_stars.begin(), ring_stars.end(),
                  [](const Star* a, const Star* b){ return a->PA_deg < b->PA_deg; });

        for (const auto* s : ring_stars) {
            printf("   %-12s %-12s %8.3f %8.1f %10.5f %10.4f %10.4f\n",
                   s->name, s->type, s->r_arcsec, s->PA_deg,
                   s->r_pc, s->l_deg, s->b_deg);
        }
        printf("\n");
    }

    // ---- Angular coverage ----
    printf("=== ANGULAR COVERAGE: RING 3 (S-cluster, 0.04-0.1 pc) ===\n\n");
    printf("   Position angle distribution (N=0°, E=90°):\n\n");
    printf("   PA range   Stars\n");
    printf("   ────────   ─────\n");
    for (int pa = 0; pa < 360; pa += 30) {
        printf("   %3d°-%3d°  ", pa, pa+30);
        for (const auto& s : catalog) {
            if (s.ring_id == 3 && s.PA_deg >= pa && s.PA_deg < pa + 30) {
                printf(" %s", s.name);
            }
        }
        printf("\n");
    }

    printf("\n=== ANGULAR COVERAGE: RING 4 (Extended S + IRS, 0.1-0.5 pc) ===\n\n");
    printf("   Position angle distribution:\n\n");
    printf("   PA range   Stars\n");
    printf("   ────────   ─────\n");
    for (int pa = 0; pa < 360; pa += 30) {
        printf("   %3d°-%3d°  ", pa, pa+30);
        for (const auto& s : catalog) {
            if (s.ring_id == 4 && s.PA_deg >= pa && s.PA_deg < pa + 30) {
                printf(" %s", s.name);
            }
        }
        printf("\n");
    }

    // ---- Summary ----
    printf("\n=== ENRICHMENT STATUS ===\n\n");
    printf("   Ring 1 (< 0.01 pc):    %d stars — awaiting deeper surveys\n",
           rings[0].n_cataloged);
    printf("   Ring 2 (0.01-0.04 pc): %d stars — S62, S4714, S55, S2\n",
           rings[1].n_cataloged);
    printf("   Ring 3 (0.04-0.1 pc):  %d stars — main S-cluster\n",
           rings[2].n_cataloged);
    printf("   Ring 4 (0.1-0.5 pc):   %d stars — extended S + IRS complex\n",
           rings[3].n_cataloged);
    printf("   Ring 5 (0.5-1.0 pc):   %d stars — central parsec edge\n",
           rings[4].n_cataloged);
    printf("   Ring 6 (1.0-5.0 pc):   %d stars — nuclear star cluster\n",
           rings[5].n_cataloged);
    printf("   Ring 7 (5-20 pc):      %d stars — Arches + Quintuplet\n",
           rings[6].n_cataloged);
    printf("   Rings 8-100:           remaining MW disk (enrichable)\n\n");

    printf("   To enrich: add stars to build_catalog() with (name, type, r\", PA).\n");
    printf("   Ring assignment is automatic from r\".\n");
    printf("   Structure accepts any number of entries per ring.\n\n");

    printf("   zk² = 1. The map begins.\n\n");

    return 0;
}
