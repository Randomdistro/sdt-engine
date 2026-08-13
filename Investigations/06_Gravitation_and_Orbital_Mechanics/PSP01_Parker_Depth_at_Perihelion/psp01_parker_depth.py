#!/usr/bin/env python3
"""PSP01 — SDT depth_closure predictions at Parker perihelion vs observation status."""
from __future__ import annotations

import math
import sys

C = 299792458.0
R_SUN = 6.957e8
AU = 1.495978707e11
OM = 1476.625  # GOM22 / B39 working Om (m)
R_PSP = 9.86 * R_SUN  # heliocentric perihelion (centre)
V_PSP = 191000.0  # ~m/s peak heliocentric speed (mission docs ~190 km/s)


def main() -> int:
    print("PSP01 depth_closure at Parker closest approach")
    print("formulas: laws.hpp depth_closure (GOM22 Shapiro repair)")
    print("--- geometry ---")
    print(f"  Om_sun              = {OM:.6f} m")
    print(f"  R_sun               = {R_SUN:.6e} m")
    print(f"  r_psp (9.86 R_sun)  = {R_PSP:.6e} m = {R_PSP/1e6:.3f} Gm")
    print(f"  altitude above phot = {(R_PSP-R_SUN)/1e6:.3f} Gm = {(R_PSP/R_SUN-1):.3f} R_sun")

    z_surf = OM / R_SUN
    z_psp = OM / R_PSP
    z_earth = OM / AU
    z_spec = z_psp - z_earth  # emit at PSP, observe at Earth

    print("--- depth z = Om/r ---")
    print(f"  z(photosphere) = {z_surf:.6e}  (C1 solar surface)")
    print(f"  z(psp)         = {z_psp:.6e}")
    print(f"  z(1 AU)        = {z_earth:.6e}")
    print(f"  z_spec emit-obs= {z_spec:.6e}  (relation 4)")
    print(f"  z_psp / z_surf = {z_psp/z_surf:.6f}  (= R_sun/r_psp = {R_SUN/R_PSP:.6f})")

    # clock / redshift as oscillation ratio
    clock = 1.0 - z_psp
    # B39 equivalent velocity for solar SURFACE used c*(1/clock - 1); for differential:
    # fractional frequency shift Earth←PSP ≈ z_spec (to first order)
    dnu_nu = z_spec
    v_equiv = C * dnu_nu

    print("--- gravitational / depth rate ratio (oscillation ratio) ---")
    print(f"  clock_rate dtau/dt = 1 - z_psp = {clock:.12f}")
    print(f"  fractional shift z_spec        = {dnu_nu:.6e}")
    print(f"  equiv 'velocity' c*z_spec      = {v_equiv:.3f} m/s")
    print(f"  solar-surface C1 (for scale)   = {C*z_surf:.3f} m/s (canon ~636 vs ~633 meas)")

    # c_far profile
    c_far = C * (1.0 - z_psp) ** 2
    dc_c = 1.0 - (1.0 - z_psp) ** 2  # = 2z - z^2
    print("--- variable relay speed c_far = c (1-z)^2 ---")
    print(f"  c_far(psp)     = {c_far:.6f} m/s")
    print(f"  (c - c_far)/c  = {dc_c:.6e}  (= 2z - z^2)")
    print(f"  superseded c(1-z) deficit = {z_psp:.6e} (half of leading 2z)")

    # kinematic Doppler dwarfs gravitational at perihelion
    beta = V_PSP / C
    # classical radial depends on geometry; order of magnitude:
    print("--- kinematic scale (not depth; for discrimination) ---")
    print(f"  v_psp ~ {V_PSP/1e3:.1f} km/s  beta = {beta:.6e}")
    print(f"  order |dv/c| ~ beta = {beta:.6e}  vs z_spec = {dnu_nu:.6e}")
    print(f"  ratio kinematic/depth ~ {beta/dnu_nu:.1f}x")

    # Shapiro one-way Earth to PSP at perihelion, impact param ~ perihelion radial
    # (order-of-magnitude; true geometry varies). Use b = r_psp for roughly radial?
    # Better: superior-conjunction style uses b~R_sun; for PSP near perihelion with
    # Earth nearly aligned, path grazes deep field. Publish both markers.
    dt_graze = (2.0 * OM / C) * math.log(4.0 * AU * R_PSP / (R_SUN * R_SUN))
    dt_loose = (2.0 * OM / C) * math.log(4.0 * AU * R_PSP / (R_PSP * R_PSP))
    print("--- Shapiro marker Delta t = (2 Om/c) ln(4 r1 r2 / b^2) [one-way] ---")
    print(f"  b=R_sun (deep)   dt = {dt_graze*1e6:.3f} us")
    print(f"  b=r_psp (loose)  dt = {dt_loose*1e6:.3f} us")
    print(f"  Viking/Cassini RT grazing Earth-Mars canon ~247 us (round-trip)")

    print("--- observation gate (literature status) ---")
    print("  PSP dedicated gravitational-redshift science result: NOT FOUND")
    print("  Shapiro in PSP nav: modeled routinely (not a PSP test of SDT)")
    print("  Dominant near-Sun radio observable: plasma scintillation/Doppler noise")
    print("  USO/clock grav shift << oscillator systematics (mission commentary)")
    print("STATUS PSP_DEPTH_PREDICTED__EMPIRICAL_MATCH_UNADJUDICATED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
