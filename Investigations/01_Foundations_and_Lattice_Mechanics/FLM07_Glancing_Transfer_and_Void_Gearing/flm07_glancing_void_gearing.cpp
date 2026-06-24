// =====================================================================================
//  FLM07 — Glancing-transfer geometry of the trefoil, the 0.103 frustration of the even
//         packing, and the tetrahedral-void gearing of the contra-rotating shell.
//
//  Author: James Christopher Harvey, Melbourne.
//
//  Thesis chain (each part computed below from laws.hpp primitives):
//    A. The (2,3) trefoil's phase velocity is v_phase(r)=c/k(r) — superluminal inside the
//       c-boundary r_e. It couples to the lattice cleanly only where the GLANCING projection
//       equals c: cos(theta)=k(r). That c-locus theta(r)=arccos(k(r)) sweeps the toroid and
//       SEPARATES the radiating wake (inside, super-c) from sub-c entrainment (outside).
//    B. Driving the lattice means spation ROTATION, co-dragging of neighbours, and the
//       contra-rotating shell (FLM03). The lattice's densest EVEN packing (icosahedral
//       12-around-1) is FRUSTRATED: the 12 touch the core but not each other — a 0.103 gap.
//    C. Crushing out that gap forces close-packing (FCC/HCP), whose interstices are
//       TETRAHEDRAL (4-coordinated) and OCTAHEDRAL (6-coordinated) voids.
//    D. The contra-rotating shell threads the sparsest (tetrahedral, 4-coordinated) voids,
//       so it carries the LEAST spations and gears ONE-for-FOUR. And 4 = W+1, so the PPT06
//       traction ratio factorises: T = 3(W+1) = 12 = (trefoil C3 = 3) x (tet gearing = 4).
//
//  HONESTY: Parts A-C are GEOMETRY (exact, delete-test clean). Part D's identification of the
//  contra-rotating shell with the tetrahedral-void sublattice, and the 1:4 gearing, is a
//  STRUCTURAL conjecture [STRONG-but-unverified] — the numbers line up (4 = W+1 = tet
//  coordination; 12 = 3x4), but that the physical shell IS the tet-void thread is not proven.
//
//  Build (MSVC):  cl /std:c++20 /EHsc /O2 /I Engine\include /Fe:flm07.exe ^
//                 Investigations\01_Foundations_and_Lattice_Mechanics\CQ52_Glancing_Transfer_and_Void_Gearing\cq52_glancing_void_gearing.cpp
//  Build (GCC):   g++ -std=c++20 -IEngine/include cq52_glancing_void_gearing.cpp -o flm07
// =====================================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;
namespace M = sdt::laws::measured;

int main() {
    const double alpha = M::alpha, a0 = M::a_0, Rp = M::R_p, re = M::r_e;
    const double pi = std::numbers::pi, deg = 180.0 / pi;
    auto kof   = [&](double r){ return std::sqrt(r / a0) / alpha; };   // k(r) = (1/alpha)sqrt(r/a0)
    auto vphof = [&](double r){ return 1.0 / kof(r); };               // phase velocity / c
    auto thof  = [&](double r){ const double k = kof(r); return k <= 1.0 ? std::acos(k) * deg : -1.0; };

    std::printf("=====================================================================\n");
    std::printf("  FLM07  GLANCING TRANSFER · 0.103 FRUSTRATION · VOID GEARING\n");
    std::printf("  J. C. Harvey, Melbourne.   Engine: sdt/laws.hpp\n");
    std::printf("=====================================================================\n\n");

    // ---- A. the glancing-c locus -----------------------------------------------------
    std::printf("[A] GLANCING-c LOCUS   cos(theta) = k(r) = (1/alpha) sqrt(r/a0)\n");
    std::printf("    v_phase(r) = c/k(r);  clean relay where v_phase*cos(theta) = c.\n");
    std::printf("      point      r [fm]    k        v_phase[c]   theta_glance\n");
    struct Pt { const char* n; double r; };
    const Pt pts[] = { {"throat~", 1e-17}, {"R_p    ", Rp}, {"deep   ", 5.54e-16}, {"r_e(cb)", re} };
    for (const auto& p : pts) {
        const double t = thof(p.r);
        if (t < 0) std::printf("      %-7s  %7.3f  %6.4f   %8.4f     sub-c (none)\n",
                               p.n, p.r * 1e15, kof(p.r), vphof(p.r));
        else       std::printf("      %-7s  %7.3f  %6.4f   %8.4f     %6.2f deg\n",
                               p.n, p.r * 1e15, kof(p.r), vphof(p.r), t);
    }
    std::printf("    => locus ~86.6deg (throat) -> 56.9deg (R_p) -> 0deg (r_e).\n");
    std::printf("       INSIDE (super-c): deficit RADIATES -> wake Phi2(l=2),Phi3(l=3) [APS04].\n");
    std::printf("       OUTSIDE (sub-c): lattice lags -> ENTRAINMENT (orbital drag).\n");
    std::printf("       The (2,3) winding threads this locus 3-fold (C3) -> native l=2,l=3\n");
    std::printf("       WITHOUT borrowing Legendre P2 (closes the APS04 honesty flag).\n\n");

    // ---- B. frustration of the even packing — the 0.103 ------------------------------
    std::printf("[B] EVEN-PACKING FRUSTRATION — the 0.103\n");
    const double aR = 4.0 / std::sqrt(10.0 + 2.0 * std::sqrt(5.0));  // icosa edge/circumradius
    const double edge = 2.0 * aR, gap = edge - 2.0;                  // outer centres at R_c=2
    std::printf("    12 unit spations icosahedrally around 1: outer centres at 2.000.\n");
    std::printf("    edge/circumradius = %.6f  ->  adjacent outer distance = %.6f\n", aR, edge);
    std::printf("    FRUSTRATION GAP = %.6f  ~ 0.103  (the 12 touch the core, NOT each other)\n\n", gap);

    // ---- C. crush -> close-packing voids ---------------------------------------------
    std::printf("[C] CRUSH THE GAP -> close-packing (FCC/HCP) interstitial voids\n");
    const double tet = std::sqrt(1.5) - 1.0, oct = std::sqrt(2.0) - 1.0;
    std::printf("    tetrahedral void  r/R = sqrt(3/2)-1 = %.4f   (4-coordinated)\n", tet);
    std::printf("    octahedral  void  r/R = sqrt(2)-1   = %.4f   (6-coordinated)\n", oct);
    std::printf("    per spation: 2 tetrahedral + 1 octahedral void.\n\n");

    // ---- D. the gearing — one for four -----------------------------------------------
    std::printf("[D] THE GEARING — 'one for four'\n");
    const int W = law_VI::winding::W_proton;
    std::printf("    W_proton = %d (trefoil)  ->  W+1 = %d   (R_p = (W+1) hbar/m_p c)\n", W, W + 1);
    std::printf("    tetrahedral coordination = 4 == W+1  ->  ONE void gears FOUR spations (1:4)\n");
    std::printf("    traction ratio T = 3(W+1) = %.0f = (trefoil C3 lobes 3) x (tet/W+1 gearing 4)\n",
                law_VI::traction::traction_ratio_proton);
    std::printf("    contra-rotating shell rides the 4-coord tet voids (sparsest) -> LEAST spations.\n\n");

    std::printf("---------------------------------------------------------------------\n");
    std::printf("  VERDICT: trefoil glancing transfer (A) drives a lattice whose densest\n");
    std::printf("  EVEN packing is frustrated by 0.103 (B); crushing yields tet+oct voids\n");
    std::printf("  (C); the contra-rotating shell threads the 4-coord tet voids (sparsest)\n");
    std::printf("  and gears 1:4 = W+1 (D).  12 = 3 x 4 runs through the whole chain.\n");
    std::printf("  A-C = exact geometry; D = structural conjecture (numbers align, not proven).\n");
    std::printf("---------------------------------------------------------------------\n");
    return 0;
}
