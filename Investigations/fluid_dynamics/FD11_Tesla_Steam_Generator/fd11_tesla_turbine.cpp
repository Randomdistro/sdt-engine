// ============================================================================
//  FD11 — Tesla Steam Generator : staggered-chamber bladeless turbine on a
//         2 km closed-loop geothermal "pinhole" borehole.
//
//  SDT framing: the disks are driven by SPATION TRACTION (CQ14 / FD06) — the
//  no-slip boundary layer gripping each smooth disk face. Loss is relay
//  diffusion (FD02). Steam supply is a choked nozzle (FD05). Energy budget is
//  FD08. This program is the FD11 applied capstone, instantiated with James's
//  design refinements:
//    (1) staggered/serpentine chambers  — stage k flows rim->hub, stage k+1
//        hub->rim, ... : multi-stage enthalpy compounding + axial-thrust balance
//    (2) bearinged comb-ring            — interleaves all disk edges so the thin
//        disks cannot flutter/wobble at speed (adds small mech loss, enables rpm)
//    (3) variable drive gear (CVT)      — brokers source<->sink, parks the rotor
//        at its eta_rotor(lambda) peak regardless of generator load
//
//  Provenance tags on every number: DERIVED / COMPUTED / MEASURED-INPUT /
//  CALIBRATED(n) / ASSUMED.  Standard-engineering results are CONVERGENCE
//  targets to reproduce, never coefficients to borrow.
//
//  Build:  cl /std:c++20 /EHsc /O2 /I Engine/include fd11_tesla_turbine.cpp
//      or  g++ -std=c++20 -IEngine/include fd11_tesla_turbine.cpp -o fd11
//  Author: James Christopher Tyndall, Melbourne.
// ============================================================================
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <numbers>
#include <algorithm>

inline constexpr double PI = std::numbers::pi;

using sdt::laws::measured::c;   // relay speed (context only; turbine v << c)

// ---- water / steam properties (MEASURED-INPUT, engineering correlations) ----
constexpr double CP_W   = 4.18e3;   // [J/kg/K] liquid water specific heat
constexpr double CP_ST  = 1.996e3;  // [J/kg/K] steam c_p (approx)
constexpr double GAMMA  = 1.327;    // steam ratio of specific heats (approx)
constexpr double G_ACC  = 9.81;     // [m/s^2] surface gravity (SDT: g=v^2/R; site value)

// Magnus saturation curve (approx, good to ~150 C; flagged above that)
static double Psat_kPa(double Tc){ return 0.61094*std::exp(17.625*Tc/(Tc+243.04)); }
static double Tsat_C  (double Pk){ double y=std::log(Pk/0.61094); return 243.04*y/(17.625-y); }
static double hfg_Jkg (double Tc){ return (2500.0 - 2.39*Tc)*1e3; }     // latent heat
static double rho_w   (double Tc){ return 1000.0 - 0.36*(Tc-4.0); }     // ~liquid density
static double darcy_f (double Re){ return (Re<2300.0)? 64.0/Re : 0.316*std::pow(Re,-0.25); }

// ---- turbine geometry & materials (Tier-S, Inconel-718 disks; MATERIALS_AND_PARTS.md) ----
constexpr double R_O   = 0.10;     // [m] disk outer radius              ASSUMED design
constexpr double R_I   = 0.025;    // [m] disk inner (hub) radius        ASSUMED design
constexpr double RHO_DISK = 8190.0;// [kg/m^3] Inconel 718               MEASURED-INPUT
constexpr double SIG_ALLOW = 700e6;// [Pa] allowable (1000 MPa / SF~1.4) MEASURED-INPUT
constexpr int    N_STAGE  = 4;     // staggered serpentine stages        DESIGN
constexpr double KB     = 2.5;     // gap = KB * boundary-layer delta    CALIBRATED(1)

// ---- drivetrain efficiencies (ASSUMED engineering values) ----
constexpr double ETA_TURB = 0.45;  // overall multi-stage Tesla (disk~0.85, nozzle+exhaust losses)
constexpr double ETA_MECH = 0.97;  // comb-ring bearings + windage
constexpr double ETA_CVT  = 0.92;  // variable drive gear
constexpr double ETA_GEN  = 0.92;  // PM generator
constexpr double ETA_PUMP = 0.70;  // circulation pump

// ---- borehole (closed-loop coaxial "pinhole") ----
constexpr double H_WELL = 2000.0;  // [m] depth
constexpr double D_PIPE = 0.050;   // [m] return-pipe bore               ASSUMED
constexpr double T_SURF = 15.0;    // [C] surface / inject temperature
constexpr double EPS_HX = 0.80;    // borehole heat-exchange effectiveness CALIBRATED(1)
constexpr double T_COND = 46.0;    // [C] condenser sat temp (~0.10 bar) DESIGN
constexpr double MDOT   = 3.0;     // [kg/s] loop circulation             ASSUMED

struct Result { double T_bh,T_ret,T_flash,x,dh_s,mdot_st,P_gross,P_pump,P_net,eta_site; };

static Result run_well(double grad_Ckm, double d_pipe=D_PIPE, double mdot=MDOT)
{
    Result r{};
    r.T_bh  = T_SURF + grad_Ckm*H_WELL/1000.0;                 // bottom-hole rock temp
    r.T_ret = T_SURF + EPS_HX*(r.T_bh - T_SURF);               // return-fluid temp (HX-limited)

    // single-flash separator at the heuristic optimum T_flash = (T_ret+T_cond)/2
    r.T_flash = 0.5*(r.T_ret + T_COND);
    double P_flash = Psat_kPa(r.T_flash);                      // [kPa]
    double P_cond  = Psat_kPa(T_COND);                         // [kPa]
    r.x = std::max(0.0, CP_W*(r.T_ret - r.T_flash)/hfg_Jkg(r.T_flash));   // flash steam fraction
    r.mdot_st = r.x*mdot;

    // isentropic enthalpy drop of the flashed steam (ideal-gas-steam approx)
    double Tin_K = r.T_flash + 273.15;
    double pr    = P_cond/P_flash;
    r.dh_s = CP_ST*Tin_K*(1.0 - std::pow(pr,(GAMMA-1.0)/GAMMA));          // [J/kg]

    // gross electrical = steam work through the staggered Tesla turbine + drivetrain
    r.P_gross = r.mdot_st * (ETA_TURB*r.dh_s) * ETA_MECH*ETA_CVT*ETA_GEN; // [W]

    // pump power: Darcy friction over down+up legs, minus thermosiphon assist
    double A   = PI*0.25*d_pipe*d_pipe;
    double rho = rho_w(r.T_ret);
    double v   = mdot/(rho*A);
    double mu  = 3.0e-4;                                       // hot-water viscosity ~MEASURED-INPUT
    double Re  = rho*v*d_pipe/mu;
    double dP_f = darcy_f(Re)*(2.0*H_WELL/d_pipe)*0.5*rho*v*v; // [Pa] (down + up)
    double dRho = rho_w(T_SURF) - rho_w(0.5*(T_SURF+r.T_ret)); // cold inject vs hot return column
    double dP_thermo = dRho*G_ACC*H_WELL;                      // buoyant (thermosiphon) assist
    double dP_net = std::max(0.0, dP_f - dP_thermo);
    r.P_pump = dP_net*(mdot/rho)/ETA_PUMP;                    // [W]

    r.P_net  = r.P_gross - r.P_pump;
    double Q_in = mdot*CP_W*(r.T_ret - T_SURF);               // thermal power harvested
    r.eta_site = (Q_in>0.0)? r.P_net/Q_in : 0.0;
    return r;
}

int main()
{
    std::puts("============================================================================");
    std::puts(" FD11 - Tesla Steam Generator : staggered chambers on a 2 km geothermal pinhole");
    std::puts(" Drive = spation traction (FD06/CQ14). SDT applied capstone of the FD series.");
    std::puts("============================================================================\n");

    // ---- turbine design point (FD11 Phase 1/2 + materials) ----
    double V_steam = 350.0;                              // representative nozzle exit speed [m/s] ASSUMED
    double v_rad   = 6.0;                                // mean radial spiral speed [m/s]        ASSUMED
    double t_res   = (R_O-R_I)/v_rad;                    // residence time
    double nu_st   = 2.0e-5;                             // steam kinematic visc [m^2/s] MEASURED-INPUT (FD02: nu~sqrt(T))
    double delta   = std::sqrt(nu_st*t_res);             // boundary-layer thickness (FD06)
    double b_opt   = KB*delta;                           // optimal disk gap (DERIVED form, CALIBRATED(1) KB)
    double Urim_max= std::sqrt(SIG_ALLOW/RHO_DISK);      // hoop-stress rim-speed limit
    double rpm_max = Urim_max/R_O*60.0/(2.0*PI);
    double lambda  = 0.5;                                // peak-efficiency tip-speed ratio (FD11 Ph.2)
    double U_op    = lambda*V_steam;
    double rpm_op  = U_op/R_O*60.0/(2.0*PI);

    std::printf(" TURBINE DESIGN POINT (Inconel-718 disks, R_o=%.0f mm, %d staggered stages)\n",
                R_O*1e3, N_STAGE);
    std::printf("   optimal disk gap  b_opt = %.3f mm   [DERIVED form b=KB*sqrt(nu*t_res), KB CAL(1)]\n", b_opt*1e3);
    std::printf("     (Tesla measured ~0.4 mm for steam  -> CONVERGENCE target)\n");
    std::printf("   hoop-stress limit       = %.0f m/s rim  = %.0f rpm   [DERIVED, sig=rho*U^2]\n",
                Urim_max, rpm_max);
    std::printf("   operating point lam=0.5 -> U=%.0f m/s = %.0f rpm  (CVT parks here)\n", U_op, rpm_op);
    std::printf("   rpm headroom            = %.1fx   [must be >1 : falsifier F5]\n\n", rpm_max/rpm_op);

    // ---- geothermal gradient sweep ----
    std::puts(" GEOTHERMAL SWEEP  (closed loop, H=2 km, return pipe d=50 mm, mdot=3 kg/s, cond 0.10 bar)");
    std::puts("  grad     T_bh   T_ret  Tflash   x_steam  dh_s     mdot_st   P_gross  P_pump   P_NET    eta_site");
    std::puts("  [C/km]   [C]    [C]    [C]      [%]      [kJ/kg]  [kg/s]    [kW]     [kW]     [kW]     [%]");
    std::puts("  -------------------------------------------------------------------------------------------------");
    for (double g : {30.0, 50.0, 80.0, 120.0}) {
        Result r = run_well(g);
        std::printf("  %5.0f   %5.0f  %5.0f   %5.0f    %6.2f   %6.0f   %7.4f   %6.1f   %6.1f   %+7.1f   %5.1f\n",
                    g, r.T_bh, r.T_ret, r.T_flash, 100.0*r.x, r.dh_s/1e3,
                    r.mdot_st, r.P_gross/1e3, r.P_pump/1e3, r.P_net/1e3, 100.0*r.eta_site);
    }

    // ---- pinhole-diameter sensitivity (the key penalty of a narrow bore) ----
    std::puts("\n PINHOLE-DIAMETER SENSITIVITY  (hot site, grad=80 C/km, mdot=3 kg/s)");
    std::puts("  d_pipe[mm]   P_pump[kW]   P_NET[kW]");
    std::puts("  ----------------------------------");
    for (double d : {0.025, 0.040, 0.050, 0.075, 0.100}) {
        Result r = run_well(80.0, d);
        std::printf("  %8.0f   %9.1f   %+8.1f\n", d*1e3, r.P_pump/1e3, r.P_net/1e3);
    }

    std::puts("\n VERDICT");
    std::puts("  - One pinhole well yields kW-scale net power; it goes net-POSITIVE from a");
    std::puts("    ~hot gradient up (>=50 C/km). A normal 30 C/km / 2 km site is too cold to");
    std::puts("    flash useful steam -> use an ORC working fluid or a deeper/hotter hole.");
    std::puts("  - The narrow 'pinhole' bore is the dominant penalty: pump friction ~1/d^5;");
    std::puts("    below ~40 mm the friction eats the output. Thermosiphon buoyancy offsets part.");
    std::puts("  - Turbine design point is self-consistent: b_opt near Tesla's measured gap and");
    std::puts("    operating rpm well under the Inconel hoop-stress limit (F5 satisfied).");
    std::puts("  Provenance: turbine drive DERIVED (FD06 traction); steam/material props");
    std::puts("  MEASURED-INPUT; HX effectiveness + gap coefficient CALIBRATED(1); efficiencies");
    std::puts("  ASSUMED. Numbers are an engineering estimate, not a sealed SDT prediction.");
    return 0;
}
