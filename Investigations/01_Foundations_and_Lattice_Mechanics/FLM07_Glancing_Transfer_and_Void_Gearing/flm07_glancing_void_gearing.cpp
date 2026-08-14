// =====================================================================================
//  FLM07 — Glancing-transfer geometry of the trefoil, the 0.103 frustration of the even
//         packing, and the tetrahedral-void gearing of the contra-rotating shell.
//
//  Author: James Christopher Tyndall, Melbourne.
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
//    D. Law-IV engaged-resistance pricing selects the tetrahedral,
//       4-coordinated void over the octahedral control before radius
//       comparison. Thus it carries the least resistance and gears 1:4.
//       The selected 4 equals W+1 and factorises T=3(W+1)=12.
//
//  Scope: Parts A-C are exact geometry. Part D is derived under Law IV's
//  minimum-resistance-path premise; the instrument does not re-derive that
//  variational premise.
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
    std::printf("  James Christopher Tyndall, Melbourne.   Engine: sdt/laws.hpp\n");
    std::printf("=====================================================================\n\n");

    // ---- A. the glancing-c locus -----------------------------------------------------
    std::printf("[A] GLANCING-c LOCUS   cos(theta) = k(r) = (1/alpha) sqrt(r/a0)\n");
    std::printf("    v_phase(r) = c/k(r);  clean relay where v_phase*cos(theta) = c.\n");
    std::printf("      point      r [fm]    k        v_phase[c]   theta_glance   f_lock  f_wake\n");
    struct Pt { const char* n; double r; };
    const Pt pts[] = { {"throat~", 1e-17}, {"R_p    ", Rp}, {"deep   ", 5.54e-16}, {"r_e(cb)", re} };
    for (const auto& p : pts) {
        const double t = thof(p.r);
        const double k = kof(p.r);
        const double f_lock = k < 1.0 ? k : 1.0;
        const double f_wake = 1.0 - f_lock;
        if (t < 0) std::printf("      %-7s  %7.3f  %6.4f   %8.4f     sub-c (none)  %6.4f  %6.4f\n",
                               p.n, p.r * 1e15, k, vphof(p.r), f_lock, f_wake);
        else       std::printf("      %-7s  %7.3f  %6.4f   %8.4f     %6.2f deg  %6.4f  %6.4f\n",
                               p.n, p.r * 1e15, k, vphof(p.r), t, f_lock, f_wake);
    }
    const double V_lock = 8.0 * pi * re * re * re / 7.0;
    const double V_wake = 4.0 * pi * re * re * re / 21.0;
    std::printf("    => locus ~86.6deg (throat) -> 56.9deg (R_p) -> 0deg (r_e).\n");
    std::printf("       isotropic mu=|cos(theta)|: f_lock=k, f_wake=1-k;\n");
    std::printf("       spherical integrals to r_e: V_lock=%.6e m^3, V_wake=%.6e m^3 (6:1).\n",
                V_lock, V_wake);
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

    // ---- D. target-free close-packed seat selection ---------------------------------
    std::printf("[D] CLOSE-PACKED SEAT SELECTION BY ENGAGED RESISTANCE\n");
    const int W = law_VI::winding::W_proton;
    const double tet_radius = std::sqrt(1.5) - 1.0;
    const double oct_radius = std::sqrt(2.0) - 1.0;
    const double V_tet = law_IV::locked_engaged_volume_sphere(tet_radius * M::l_P);
    const double V_oct = law_IV::locked_engaged_volume_sphere(oct_radius * M::l_P);
    const double R_tet = 4.0 * law_IV::resistance_from_engaged_volume(V_tet);
    const double R_oct = 6.0 * law_IV::resistance_from_engaged_volume(V_oct);
    const int selected_coordination = R_tet < R_oct ? 4 : 6;
    const double selected_radius = selected_coordination * M::hbar / (M::m_p * M::c);
    const double alternate_radius = 6.0 * M::hbar / (M::m_p * M::c);
    const double selected_error = (selected_radius / M::R_p - 1.0) * 100.0;
    const double alternate_error = (alternate_radius / M::R_p - 1.0) * 100.0;

    std::printf("    common Law-IV price: q*(P_conv/3)*V_lock(r_void)\n");
    std::printf("      tetrahedral q=4 r/R=%.6f  R/P=%.6e m^3\n",
                tet_radius, R_tet / law_I::P_conv);
    std::printf("      octahedral  q=6 r/R=%.6f  R/P=%.6e m^3\n",
                oct_radius, R_oct / law_I::P_conv);
    std::printf("    oct/tet ratio: seat-only %.6f; contact-weighted %.6f\n",
                V_oct / V_tet, R_oct / R_tet);
    std::printf("    both native prices select q=%d before R_p comparison\n",
                selected_coordination);
    std::printf("    W=1 control: 720-degree closure = two 2pi action relays = 2 hbar;\n");
    std::printf("    W=3 selected action = q hbar = %d hbar; q == W+1: %s\n",
                selected_coordination,
                selected_coordination == W + 1 ? "PASS" : "FAIL");
    std::printf("    predicted boundary q*hbar/(m_p c) = %.6f fm vs measured %.6f fm (%+.4f%%)\n",
                selected_radius * 1e15, M::R_p * 1e15, selected_error);
    std::printf("    alternate octahedral boundary      = %.6f fm (%+.2f%%)\n",
                alternate_radius * 1e15, alternate_error);
    std::printf("    tetrahedral coordination = 4 == W+1 -> ONE void gears FOUR spations (1:4)\n");
    std::printf("    traction ratio T = 3(W+1) = %.0f = (trefoil C3 lobes 3) x (tet/W+1 gearing 4)\n",
                law_VI::traction::traction_ratio_proton);
    std::printf("    contra-rotating shell rides the 4-coord tet voids (sparsest) -> LEAST spations.\n\n");

    std::printf("---------------------------------------------------------------------\n");
    std::printf("  VERDICT: trefoil glancing transfer (A) drives a lattice whose densest\n");
    std::printf("  EVEN packing is frustrated by 0.103 (B); crushing yields tet+oct voids\n");
    std::printf("  (C); Law-IV engaged-resistance pricing selects the 4-coordinate tet\n");
    std::printf("  thread before radius comparison (D), giving q=W+1 and q*hbar/(m_p c).\n");
    std::printf("  D is derived under the registered minimum-resistance path premise;\n");
    std::printf("  the octahedral control is 9.39x dearer and predicts a 50%% radius miss.\n");
    std::printf("---------------------------------------------------------------------\n");
    return 0;
}
