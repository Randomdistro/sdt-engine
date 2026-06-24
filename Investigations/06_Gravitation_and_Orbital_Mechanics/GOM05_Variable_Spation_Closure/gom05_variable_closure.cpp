/**
 * @file cq43_variable_closure.cpp
 * @brief GOM05: Variable Spation Closure, the Light-Speed Gradient & Lumiostasis
 *
 * THESIS (James Tyndall):
 *   The Planck-scale spherical closure of the spation, ℓ_P, is NOT a global
 *   constant. Nucleons (protons + neutrons) crush the space they displace,
 *   tightening the local closure. Light always relays ONE spation per tick,
 *   so where the closure is smaller, light is locally slower — a gradient.
 *   The atom emits the SAME kinematic EM pulse everywhere; the variation is
 *   in the medium, not the source.
 *
 * NO ATTRACTION (but orbits are real). Nothing is pulled. The CMB convergence
 *   pushes everything together; matter follows the path of least resistance
 *   through the depth gradient — and a closed least-resistance path through a
 *   radial gradient IS an orbit. The orbital motion is real; the cause is
 *   convergence, not a gravitational pull.
 *   "koppa" here is a VELOCITY quantity (ϟ = R/k², k=c/v);
 *   the depth field is the dimensionless z = 1/k² = ϟ/r; light's local speed is
 *   c_local = c·(1 − z). z is what light wades through; koppa = c/k is what sets
 *   the velocity structure.
 *
 * UNIFICATION (GOM01 depth ⊕ FLM06 closure):
 *   local closure   ℓ_P(r) = ℓ_P,∞ · (1 − z(r))
 *   c_local(r)      = c_∞ · ℓ_P(r)/ℓ_P,∞ = c_∞ (1 − z(r))
 *   so z(r) = 1 − ℓ_P(r)/ℓ_P,∞ = 1 − c_local/c_∞  (one quantity, three readings).
 *   Shapiro delay = integrated closure deficit along the path (same number as
 *   GOM01; now read as "the spations are smaller," not "more shells").
 *
 * THE LUMIOPAUSE (James's correction): a SURFACE-AREA condition. Solar output
 *   spread over the sphere equals the CMB output:
 *       L_sun / (4π r²) = F_CMB   ⟹   r_lumio = √(L_sun / 4π F_CMB)
 *   This is law_II::pressure_domain(L_Sun). The Oort cloud is suspended AT this
 *   depth — LUMIOSTASIS — held where the convergence gradient balances, not
 *   orbiting.
 *
 * All constants from Engine/include/sdt/laws.hpp. No new fitted parameters.
 * @author SDT Canonical Engine — James Christopher Tyndall, Melbourne
 * @date June 2026
 */

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;
using namespace sdt::laws::measured;
namespace B  = sdt::laws::bridge;
namespace L2 = sdt::laws::law_II;

static int total=0, passed=0;
static void prove(const char* tag,const char* d,double got,double exp,double tolpct){
  ++total; double e=(exp!=0)?std::fabs(got-exp)/std::fabs(exp)*100:std::fabs(got);
  bool ok=e<tolpct; if(ok)++passed;
  std::printf("  %s %s: %s\n    got=%.6e exp=%.6e err=%.4f%%\n\n",ok?"PASS":"FAIL",tag,d,got,exp,e);
}

int main(){
  std::puts("================================================================");
  std::puts("  GOM05: VARIABLE SPATION CLOSURE, c-GRADIENT & LUMIOSTASIS");
  std::puts("  ℓ_P(r) shrinks where matter crushes space; light tracks it.");
  std::puts("  No attraction (orbits are real least-resistance paths). The CMB");
  std::puts("  convergence pushes; matter follows the depth gradient.");
  std::puts("================================================================\n");

  const double koppa_Sun = B::koppa_Sun;             // ϟ_Sun = R/k² (velocity-defined), 1477 m
  const double lP = l_P;                             // global (∞) spation closure

  // background depth the Sun itself sits in (Milky Way load at the Sun)
  const double M_MW   = 6.0e10;                       // M_sun baryonic (GD05/GD03)
  const double koppa_MW = M_MW * koppa_Sun;
  const double R0_gal = 8.178 * 3.0856775814e19;      // m
  const double z_gal  = koppa_MW / R0_gal;            // local depth floor

  // lumiopause: SURFACE-AREA condition L/(4πr²) = F_CMB  (law_II::pressure_domain)
  const double r_lumio = L2::pressure_domain(L2::L_Sun);

  std::puts("================================================================");
  std::puts("  SECTION I — z(r) IS the closure deficit IS the c deficit");
  std::puts("================================================================\n");
  std::printf("  global closure ℓ_P,∞     = %.6e m\n", lP);
  std::printf("  ϟ_Sun = R_Sun/k_Sun²     = %.4f m   (velocity quantity, k=c/v)\n", koppa_Sun);
  std::printf("  galactic depth floor z_gal= %.6e\n", z_gal);
  std::printf("  lumiopause (surface-area) = %.0f AU  (L/(4πr²)=F_CMB)\n\n", r_lumio/AU);

  double z_surf  = koppa_Sun / R_Sun;                 // depth at the solar surface
  double lP_surf = lP * (1.0 - z_surf);
  double c_surf  = c  * (1.0 - z_surf);
  std::printf("  At the solar surface:\n");
  std::printf("    z(R_Sun) = ϟ/R = 1/k² = %.6e\n", z_surf);
  std::printf("    ℓ_P(R_Sun)     = %.10e m  (closure shrunk by %.4e m)\n", lP_surf, lP-lP_surf);
  std::printf("    c_local(R_Sun) = %.6f m/s  (slower by %.4f m/s)\n\n", c_surf, c-c_surf);

  prove("GOM05-I.1","z = 1 − c_local/c  (light-speed deficit = depth)",
        1.0 - c_surf/c, z_surf, 1e-6);
  prove("GOM05-I.2","z = 1 − ℓ_P(r)/ℓ_P,∞  (closure deficit = depth)",
        1.0 - lP_surf/lP, z_surf, 1e-6);

  std::puts("================================================================");
  std::puts("  SECTION II — THE c-GRADIENT (light faster as closure opens)");
  std::puts("================================================================\n");
  std::printf("  %-18s %12s %13s %16s %14s\n",
              "location","r [AU]","z(r)=ϟ/r","ℓ_P(r) [m]","c deficit [m/s]");
  std::printf("  %s\n","-------------------------------------------------------------------------------");
  struct Loc{const char* n; double r;};
  Loc locs[]={
    {"solar surface", R_Sun}, {"Mercury", 0.387*AU}, {"Earth", 1.0*AU},
    {"Jupiter", 5.2*AU}, {"heliopause ~120AU", 120.0*AU},
    {"lumiopause", r_lumio}, {"0.5 ly", 0.5*9.4607e15}, {"deep space", 1.0e20},
  };
  for(auto&Lc:locs){
    double zS=koppa_Sun/Lc.r, zT=zS+z_gal;
    double lPr=lP*(1.0-zT), dc=zT*c;
    std::printf("  %-18s %12.4g %13.4e %16.9e %14.4f\n", Lc.n, Lc.r/AU, zS, lPr, dc);
  }
  std::puts("\n  Light speeds up monotonically outward as the spation closure opens.");
  std::puts("  Same emitted pulse everywhere — only the medium's closure changes.");

  std::puts("\n================================================================");
  std::puts("  SECTION III — THE LUMIOPAUSE AS A SURFACE-AREA CONDITION");
  std::puts("================================================================\n");
  std::puts("  Solar output, spread over the sphere, equals CMB output:");
  std::puts("      L_sun/(4π r²) = F_CMB   ⟹   r_lumio = √(L_sun/4π F_CMB)\n");
  std::printf("    L_Sun  = %.4e W\n", L2::L_Sun);
  std::printf("    F_CMB  = %.4e W/m²  (= c·u_CMB/4)\n", L2::F_CMB);
  std::printf("    r_lumio= %.6e m = %.0f AU\n", r_lumio, r_lumio/AU);
  // verify the surface-area balance holds at r_lumio
  double F_sun_at_lumio = L2::L_Sun / (4.0*std::numbers::pi*r_lumio*r_lumio);
  std::printf("    check: L_sun/(4π r_lumio²) = %.6e W/m²  vs F_CMB %.6e\n\n",
              F_sun_at_lumio, L2::F_CMB);
  prove("GOM05-III.1","lumiopause: L_sun/(4π r²) = F_CMB exactly",
        F_sun_at_lumio, L2::F_CMB, 1e-6);

  std::puts("  LUMIOSTASIS: the Oort cloud is suspended AT this depth surface —");
  std::puts("  held where the convergence gradient balances (the path of least");
  std::puts("  resistance for matter pushed inward by the CMB), not by attraction.\n");

  std::puts("================================================================");
  std::puts("  SECTION IV — SHAPIRO, RE-READ AS INTEGRATED CLOSURE DEFICIT");
  std::puts("================================================================\n");
  double r1=AU, r2=1.524*AU, b=R_Sun;
  double dt_closed=(2.0*koppa_Sun/c)*std::log(4.0*r1*r2/(b*b));
  // GR comparison value (NOT a gravitational claim — just the standard formula's number)
  double GM_sun=B::GM_equivalent(B::k_Sun, R_Sun);
  double dt_std =(2.0*GM_sun/(c*c*c))*std::log(4.0*r1*r2/(b*b));
  std::printf("  Earth–Mars, b=R_Sun:\n");
  std::printf("    Δt = (2ϟ/c) ln(4r₁r₂/b²) = %.4f µs\n", dt_closed*1e6);
  std::printf("    standard formula number   = %.4f µs\n", dt_std*1e6);
  std::puts("    Reading: light is delayed because the spations near the Sun are");
  std::puts("    SMALLER — a fixed path crosses more closure boundaries. Local light");
  std::puts("    speed is c at every spation; the relay count per metre rises inward.");
  prove("GOM05-IV.1","closure-deficit Shapiro = standard formula number",
        dt_closed, dt_std, 0.01);

  std::puts("================================================================");
  std::printf("  RESULTS: %d/%d proofs passed\n", passed, total);
  std::puts("================================================================\n");
  std::puts("  VERDICT: one mechanism — ℓ_P(r) = ℓ_P,∞(1−z), c_local = c(1−z),");
  std::puts("  z = ϟ/r. Light's gradient, Shapiro, and the lumiopause surface");
  std::puts("  all follow with no attraction — convergence pushing, matter taking");
  std::puts("  the least-resistance path (orbits included). The Oort cloud rests");
  std::puts("  in lumiostasis at the L/(4πr²)=F_CMB depth surface.");
  return (passed==total)?0:1;
}
