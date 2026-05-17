// =============================================================================
// CQ20b — Proton Torus: Spation Surface Count
//
// The proton is a torus. The spation lattice tiles its surface.
// Each surface spation is a contact point carrying perfect traction.
//
// Dimensional promotion (sphere → torus):
//   point at centre     → line along centre (axis)
//   diameter line       → axial plane
//   circumference line  → torus surface
//   central plane slice → torus volume
//   sphere volume       → rotational sweep of sphere along axis
//
// Three rotations:
//   1. Toroidal:  around the major circumference C_major = 2πR
//   2. Poloidal:  around the tube circumference  C_minor = 2πr
//   3. Differential: inner minor C rotates FASTER than outer → contrarotation
//
// Contact properties:
//   - Perfect traction (no slip)
//   - Incompressibility
//   - Contact point area ~ (l_P)^n << spation cross-section
//
// No G. No M. zk² = 1.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static constexpr double r_s = l_P / 2.0;  // spation radius

// =============================================================================
// TORUS GEOMETRY
//
// R = major radius (centre of torus to centre of tube)
// r = minor radius (tube radius)
//
// Surface area   = 4π²Rr
// Volume         = 2π²Rr²
// C_major        = 2πR  (toroidal circumference)
// C_minor        = 2πr  (poloidal circumference)
// C_inner        = 2π(R - r)  (inner circumference)
// C_outer        = 2π(R + r)  (outer circumference)
// =============================================================================

struct TorusGeometry {
    double R;           // major radius [m]
    double r;           // minor radius [m]

    double surface_area() const { return 4.0 * M_PI * M_PI * R * r; }
    double volume()      const { return 2.0 * M_PI * M_PI * R * r * r; }
    double C_major()     const { return 2.0 * M_PI * R; }
    double C_minor()     const { return 2.0 * M_PI * r; }
    double C_inner()     const { return 2.0 * M_PI * (R - r); }
    double C_outer()     const { return 2.0 * M_PI * (R + r); }

    // Spation counts
    double spations_on_surface() const {
        // Each spation occupies a circle of diameter l_P on the surface
        // Hexagonal close packing efficiency = π/(2√3) ≈ 0.9069
        double A_per_spation = M_PI * r_s * r_s;  // circle area of one spation
        return surface_area() / A_per_spation;
    }

    double spations_around_major() const {
        return C_major() / (2.0 * r_s);  // diameter = l_P
    }

    double spations_around_minor() const {
        return C_minor() / (2.0 * r_s);
    }

    double spations_around_inner() const {
        return C_inner() / (2.0 * r_s);
    }

    double spations_around_outer() const {
        return C_outer() / (2.0 * r_s);
    }

    // Differential rotation ratio: inner C / outer C
    double differential_ratio() const {
        if (R <= r) return 0.0;  // degenerate
        return C_inner() / C_outer();
    }
};

// =============================================================================
// CONTACT POINT GEOMETRY
//
// Two perfect spheres of radius r_s touching:
//   Contact area = 0 (mathematical point for rigid spheres)
//   But real: Hertzian contact gives A = π a² where a = (F r_s / E*)^(1/3)
//   For incompressible spations under P_conv:
//   The contact "point" has an effective radius much smaller than r_s.
//
// The user says: contact point is ~10^n smaller than the spation itself.
// Let's compute what n is from the lattice mechanics.
// =============================================================================

static void contact_analysis() {
    printf("\n=== CONTACT POINT ANALYSIS ===\n\n");

    // For incompressible spheres, the contact is a mathematical point.
    // But pressure must be transmitted. The effective contact area
    // scales with the deformation of the lattice under P_conv.
    //
    // If spations are truly incompressible, contact is zero-area.
    // Traction is transmitted through GEOMETRIC CONSTRAINT, not deformation.
    // The 12-around-1 packing means each spation is constrained by
    // its 12 neighbours — no slip is possible without rearranging ALL 12.
    //
    // The "contact point" is therefore the GEOMETRIC TANGENT POINT:
    //   radius = 0 (mathematical)
    //   but effective traction radius ~ l_P × (some small fraction)
    //
    // From dimensional analysis: if the contact transmits P_conv
    // through area A_contact, and the force is F = P_conv × A_spation:
    //   P_contact = F / A_contact = P_conv × (4π r_s²) / A_contact
    //   A_contact = 4π r_s² (if pressure is uniform — but it's concentrated)
    //
    // The ratio of contact area to spation cross-section:

    printf("   Spation radius:             r_s = %.4e m\n", r_s);
    printf("   Spation cross-section:      A_s = %.4e m²\n", M_PI * r_s * r_s);
    printf("   Spation surface area:       S_s = %.4e m²\n", 4.0 * M_PI * r_s * r_s);
    printf("   Convergence pressure:       P   = %.4e Pa\n\n", law_I::P_conv);

    // Contact point scaling: for two touching spheres of radius r_s,
    // the tangent point is a single mathematical point.
    // Effective traction transmitted per contact = P_conv × (4π r_s² / 12)
    // (shared among 12 contacts in close packing)
    double F_per_contact = law_I::P_conv * 4.0 * M_PI * r_s * r_s / 12.0;
    printf("   Force per contact (12 neighbours): %.4e N\n", F_per_contact);
    printf("   (P_conv × 4π r_s² / 12)\n\n");

    // If contact is a point: infinite pressure at the point
    // This is the mathematical idealisation of perfect traction.
    // In practice: "10^n smaller than the spation" means the contact
    // region has radius ~ r_s × 10^{-n}

    for (int n = 5; n <= 25; n += 5) {
        double r_contact = r_s * std::pow(10.0, -n);
        double A_contact = M_PI * r_contact * r_contact;
        double P_contact = F_per_contact / A_contact;
        printf("   n=%2d: r_contact = %.2e m, A = %.2e m², P_contact = %.2e Pa\n",
               n, r_contact, A_contact, P_contact);
    }
}

int main() {
    printf("###################################################################\n");
    printf("   CQ20b: Proton Torus — Spation Surface Count\n");
    printf("   SDT Framework — James Tyndall, Melbourne\n");
    printf("###################################################################\n\n");

    printf("=== FUNDAMENTAL SCALES ===\n\n");
    printf("   Spation radius:        r_s = l_P/2 = %.6e m\n", r_s);
    printf("   Spation diameter:      l_P       = %.6e m\n", l_P);
    printf("   Proton charge radius:  R_p       = %.6e m\n", R_p);
    printf("   Classical electron R:  r_e       = %.6e m\n", r_e);
    printf("   Proton Compton:        lambda_Cp = %.6e m\n", lambda_C_p);
    printf("   R_p / r_s = %.4e  (spations across proton radius)\n", R_p / r_s);
    printf("   r_e / r_s = %.4e  (spations across c-boundary)\n\n", r_e / r_s);

    // Proton exclusion volume (actual displaced lattice)
    printf("   Proton exclusion volume:  V_disp = %.4e m³\n", law_IV::V_disp_p);
    printf("   Proton exclusion radius:  R_excl = %.4e m\n", law_IV::R_excl_p);
    printf("   R_excl / r_s = %.4e  (spations across exclusion)\n\n",
           law_IV::R_excl_p / r_s);

    // =================================================================
    // TORUS CONFIGURATIONS
    // The proton torus has two radii. Which physical scale maps to which?
    //
    // Config A: R = R_p, r = R_p (horn torus, aspect ratio 1)
    // Config B: R = r_e, r = R_p (c-boundary major, charge minor)
    // Config C: R = R_p, r = R_excl (charge major, exclusion minor)
    // Config D: R = lambda_Cp/(2π), r = R_p (Compton major, charge minor)
    // =================================================================

    printf("=== TORUS CONFIGURATIONS ===\n\n");

    struct Config {
        const char* name;
        double R, r;
        const char* description;
    };

    Config configs[] = {
        {"A: Horn torus",     R_p, R_p,
         "R=R_p, r=R_p (equal radii)"},
        {"B: c-boundary maj", r_e, R_p,
         "R=r_e, r=R_p (c-boundary outer, charge tube)"},
        {"C: Charge/excl",    R_p, law_IV::R_excl_p,
         "R=R_p, r=R_excl (charge outer, physical tube)"},
        {"D: Compton/charge", lambda_C_p/(2.0*M_PI), R_p,
         "R=reduced_Compton, r=R_p"},
    };
    int nc = 4;

    for (int i = 0; i < nc; i++) {
        TorusGeometry torus{configs[i].R, configs[i].r};
        printf("   --- %s ---\n", configs[i].name);
        printf("   %s\n", configs[i].description);
        printf("   R = %.4e m,  r = %.4e m\n", torus.R, torus.r);
        printf("   Surface area    = %.4e m²\n", torus.surface_area());
        printf("   Volume          = %.4e m²\n", torus.volume());
        printf("\n");
        printf("   SPATION COUNTS:\n");
        printf("     Surface total:    %.4e spations\n", torus.spations_on_surface());
        printf("     Major circ:       %.4e spations (toroidal ring)\n",
               torus.spations_around_major());
        printf("     Minor circ:       %.4e spations (poloidal ring)\n",
               torus.spations_around_minor());
        printf("     Outer circ:       %.4e spations\n",
               torus.spations_around_outer());
        printf("     Inner circ:       %.4e spations\n",
               torus.spations_around_inner());
        printf("\n");
        printf("   DIFFERENTIAL ROTATION:\n");
        printf("     C_inner / C_outer = %.6f\n", torus.differential_ratio());
        if (torus.R > torus.r) {
            printf("     Inner spations travel SHORTER path in same period\n");
            printf("     → angular velocity ratio = C_outer/C_inner = %.4f\n",
                   1.0 / torus.differential_ratio());
            printf("     → inner rotates %.2fx FASTER than outer\n",
                   1.0 / torus.differential_ratio());
        }
        printf("\n   THREE ROTATIONS:\n");
        printf("     1. Toroidal (major C): %12.4e contact spations/rev\n",
               torus.spations_around_major());
        printf("     2. Poloidal (minor C): %12.4e contact spations/rev\n",
               torus.spations_around_minor());
        printf("     3. Differential:       inner %.4fx faster than outer\n",
               torus.R > torus.r ? 1.0/torus.differential_ratio() : 0.0);
        printf("\n");

        // Trefoil: (2,3) knot wraps 3× toroidal, 2× poloidal
        double knot_length = std::sqrt(
            std::pow(3.0 * torus.C_major(), 2) +
            std::pow(2.0 * torus.C_minor(), 2));
        printf("   TREFOIL (2,3) KNOT:\n");
        printf("     Knot length = sqrt((3×C_maj)² + (2×C_min)²) = %.4e m\n",
               knot_length);
        printf("     Spations along knot: %.4e\n", knot_length / (2.0 * r_s));
        printf("\n");
    }

    contact_analysis();

    // =================================================================
    // KEY INSIGHT: TRACTION TRANSFER
    //
    // The proton's surface has N_surface spations in contact.
    // At v = 1.83c, the toroidal rotation drags ALL of them.
    // Each surface spation drags its 12 neighbours (minus the ones
    // already on the surface). Net: each surface spation drags
    // ~6 external spations (hemisphere facing outward).
    //
    // Total external traction points = N_surface × 6
    // This is the first shell of the drag wake.
    // =================================================================

    printf("\n=== DRAG WAKE INITIATION ===\n\n");

    // Use Config B as the most physically motivated
    TorusGeometry proton{r_e, R_p};
    double N_surf = proton.spations_on_surface();
    double N_ext  = N_surf * 6.0;  // hemisphere outward

    printf("   Using Config B: R=r_e, r=R_p\n");
    printf("   Surface spations:         %.4e\n", N_surf);
    printf("   External traction points: %.4e (×6 hemisphere)\n", N_ext);
    printf("   Proton surface velocity:  %.4e m/s (1.831c)\n", 1.831*c);
    printf("\n");
    printf("   Each of these %.2e contact points displaces convergence for one external spation.\n",
           N_ext);
    printf("   Those spations form Shell 1 of the convergence occlusion gradient.\n");
    printf("   Shell 1 has ~4π(r_e + l_P)²/A_spation ≈ %.4e spations.\n",
           4.0*M_PI*(r_e+l_P)*(r_e+l_P) / (M_PI*r_s*r_s));
    printf("   Engagement fraction: N_ext / N_shell1 = %.4e\n",
           N_ext / (4.0*M_PI*(r_e+l_P)*(r_e+l_P) / (M_PI*r_s*r_s)));
    printf("\n   This fraction determines how much of Shell 1 is directly driven\n");
    printf("   by the engine's displacement, setting the initial occlusion solid angle.\n");

    return 0;
}
