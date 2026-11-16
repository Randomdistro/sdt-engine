// =====================================================================================
//  np17_nuclear_packing.cpp — the nuclear packing order: 6π-trefoil interleaved nucleons
//  bound by SHARED ELECTRONS (the neutron's internal electron bonds adjacent protons).
//
//  Model (companion SDT repo: 6PI_TREFOIL_INTERLEAVED_SPEC.md, ELECTRON_SHARING_MODEL.md,
//  NUCLEAR_PACKING_STRUCTURE_AND_DATA.md, D-01):
//    - every nucleon is a 6π-winding trefoil torus (proton boundary R_p ≈ 0.84 fm)
//    - neutron = proton + ONE internal electron  (n = p⁺ + e⁻_internal ; no free neutron)
//    - that internal electron is SHARED between adjacent protons → a Coulomb pressure well
//    - binding is electrostatic: E = −Σ q_i q_j (αℏc)/r_ij  with q=+1 proton, −1 electron
//
//  The ONLY energy scale is the Coulomb identity k_e e² = αℏc = 1.44 MeV·fm. NO fitted
//  binding constant (this replaces NP05's killed volume-price hypothesis). "Chemistry is
//  nuclear physics geared down by 137": the SAME shared-electron bond as H₂⁺, at fm not Å.
//
//  Build (MSVC):  cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include <thisfile> /Fe:np17.exe
//  Author: J. C. Harvey, Melbourne.
// =====================================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>

namespace M = sdt::laws::measured;

struct Pt { double x, y, z; int q; };   // position in fm, q=+1 proton / −1 electron

// engine-sourced ℏc in MeV·fm, and the Coulomb identity αℏc = k_e e²
static const double HBARC = (M::hbar * M::c / M::MeV_to_J) * 1e15;   // MeV·fm
static const double AHC   = M::alpha * HBARC;                        // = k_e e²  [MeV·fm]
static const double R_p   = M::R_p * 1e15;                           // proton boundary [fm]

// total electrostatic binding (positive = bound) of a set of point charges:
//   U = Σ_{i<j} q_i q_j αℏc / r_ij ;  binding = −U
static double binding(const std::vector<Pt>& s) {
    double U = 0.0;
    for (size_t i = 0; i < s.size(); ++i)
        for (size_t j = i + 1; j < s.size(); ++j) {
            const double dx=s[i].x-s[j].x, dy=s[i].y-s[j].y, dz=s[i].z-s[j].z;
            const double r = std::sqrt(dx*dx+dy*dy+dz*dz);
            if (r < 1e-12) continue;
            U += double(s[i].q*s[j].q) * AHC / r;
        }
    return -U;
}

static double rel_pct(double a, double b){ return (a-b)/b*100.0; }

int main() {
    std::printf("############################################################################\n");
    std::printf("#  NP17 — nuclear packing order: 6π-trefoil + SHARED-ELECTRON binding       #\n");
    std::printf("#  E = -sum q_i q_j (alpha hbar c)/r_ij.  No fitted energy scale.           #\n");
    std::printf("############################################################################\n\n");
    std::printf("  k_e e^2 = alpha*hbar*c = %.4f MeV*fm   (Coulomb identity)\n", AHC);
    std::printf("  proton boundary R_p     = %.4f fm   (= 4 hbar/(m_p c), W+1)\n", R_p);
    std::printf("  trefoil minor radius    = R_p/3 = %.4f fm  (electron node gap)\n\n", R_p/3.0);

    // ================================================================== DEUTERON  (D-01)
    //  p --- e --- p collinear, electron at the gap centre.  Factor 3 is EXACT:
    //    p-e (x2): -4 k_e e^2/D ;  p-p: +k_e e^2/D  ->  -3 k_e e^2/D.
    std::printf("=== DEUTERON  (p + n = p + (p+e) = 2p + 1e) ===\n");
    const double r_node = R_p/3.0;
    const double D_geom = 2.0*R_p + r_node;            // proton boundaries + node gap
    {
        std::vector<Pt> d = {{0,0,0,+1}, {D_geom,0,0,+1}, {D_geom/2,0,0,-1}};
        const double E = binding(d);
        std::printf("  geometric D = 2 R_p + R_p/3 = %.4f fm\n", D_geom);
        std::printf("  E_bind = %.4f MeV   (measured 2.224 MeV, %+.2f%%)   [factor 3 exact]\n",
                    E, rel_pct(E, 2.224));
    }
    // forward: which D reproduces the measured 2.224?
    const double D_meas = 3.0*AHC/2.224;
    std::printf("  inverse: D giving 2.224 MeV = 3 k_e e^2/E = %.4f fm  (= 2R_p + %.3f fm gap)\n",
                D_meas, D_meas - 2.0*R_p);
    std::printf("  -> binding SCALE is NOT fitted: it is alpha hbar c / (a geometric length).\n\n");

    // ================================================================== ALPHA  (He-4)
    //  4 protons at a regular tetrahedron (edge a) + 2 internal electrons (one per neutron),
    //  placed at the midpoints of two OPPOSITE edges (two interlocked deuterons, L-R-L-R).
    std::printf("=== ALPHA  (He-4 = 2p + 2n = 4p + 2e, tetrahedral) ===\n");
    auto alpha_binding = [](double a)->double {
        const double s = a/(2.0*std::sqrt(2.0));
        std::vector<Pt> v = {
            {  s,  s,  s, +1}, {  s, -s, -s, +1},   // edge A (v0,v1)
            { -s,  s, -s, +1}, { -s, -s,  s, +1},   // edge B (v2,v3)
            {  s,  0,  0, -1},                        // electron at midpoint of edge A
            { -s,  0,  0, -1},                        // electron at midpoint of edge B
        };
        return binding(v);
    };
    const double a_touch = 2.0*R_p;                    // protons just touching
    std::printf("  electrostatic binding at a = 2R_p = %.3f fm : %.3f MeV\n",
                a_touch, alpha_binding(a_touch));
    // what edge would the pure-electrostatic model need to reach 28.296?
    {
        double lo=0.05, hi=4.0;
        for (int it=0; it<80; ++it){ double m=(lo+hi)/2; (alpha_binding(m) > 28.296 ? lo : hi) = m; }
        std::printf("  edge that would give 28.296 MeV electrostatically: a = %.3f fm  (< 2R_p!)\n",(lo+hi)/2);
    }
    std::printf("  HONEST: shared-electron electrostatics alone UNDER-binds the alpha at\n");
    std::printf("          physical spacing (~%.1f vs 28.3 MeV). The deuteron is pure\n", alpha_binding(a_touch));
    std::printf("          shared-electron well; the alpha's remainder is the 'tetrahedral\n");
    std::printf("          lock' (interlock + occlusion) — mechanism named, magnitude PENDING\n");
    std::printf("          (needs the imported geometry: NUCLEAR_PACKING_STRUCTURE_AND_DATA.md).\n\n");

    // ================================================================== GRAMMAR (ATOMICUS)
    //  every Z>=2 nucleus = 1 alpha core + n_d deuterons + n_t tritons.  Bond count scales
    //  the shared-electron mediation. (n_t = A-2Z ; n_d = 3Z-A-2)
    std::printf("=== ATOMICUS grammar decomposition (1 alpha + n_d d + n_t t) ===\n");
    struct Iso{ const char* name; int Z, A; };
    Iso list[] = {{"He-4",2,4},{"C-12",6,12},{"O-16",8,16},{"Ne-20",10,20},{"Ca-40",20,40}};
    std::printf("  %-6s %3s %3s | %3s %3s | internal e (=neutrons) = shared-bond mediators\n",
                "iso","Z","A","n_d","n_t");
    for (auto& I : list){
        const int n_t = I.A - 2*I.Z;
        const int n_d = 3*I.Z - I.A - 2;
        const int neutrons = I.A - I.Z;   // = number of internal (shared) electrons
        std::printf("  %-6s %3d %3d | %3d %3d | %d shared electrons\n",
                    I.name, I.Z, I.A, n_d, n_t, neutrons);
    }
    std::printf("  -> per-isotope (r,theta,phi) placement + full binding sum is the next stage\n");
    std::printf("     (port trefoil_mappings.json / icosahedral A<=40 from the companion repo).\n\n");

    // ================================================================== VERDICT
    const double Ed = binding(std::vector<Pt>{{0,0,0,+1},{D_geom,0,0,+1},{D_geom/2,0,0,-1}});
    const bool deuteron_ok = std::fabs(rel_pct(Ed,2.224)) < 3.0;
    std::printf("=== VERDICT ===\n");
    std::printf("  [%s] DEUTERON: shared-electron well E=3 alpha hbar c/D = %.3f MeV (meas 2.224)\n",
                deuteron_ok?"PASS":"FAIL", Ed);
    std::printf("  [MECHANISM] binding = shared-electron Coulomb well; NO fitted energy scale\n");
    std::printf("              (closes NP05's killed volume-price gap; uses only alpha hbar c).\n");
    std::printf("  [PENDING]   alpha + heavy: tetrahedral-lock/occlusion remainder + imported geometry\n");
    std::printf("  RESULT: the packing order is interleaved 6π trefoils, neutron=p+e, e shared.\n");
    return deuteron_ok ? 0 : 1;
}
