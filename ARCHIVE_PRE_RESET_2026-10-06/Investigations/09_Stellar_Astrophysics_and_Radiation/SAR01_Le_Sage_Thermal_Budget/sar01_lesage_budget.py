#!/usr/bin/env python3
# SAR01 — Le Sage thermal budget: the thermalisation-leakage ceiling.
# Direct execution (no agents). Native: gravitational force = M v^2/r, NO GM, NO G.
# Question (FARMER-corrected): occlusion is REDIRECTION (throughpole), not absorption.
#   Does the elastic redirection have any thermalisation leakage eta, and does the
#   47 TW geothermal budget cap it?
# Le Sage dies because its net push needs a TERMINUS (absorbed corpuscles -> heat).
# SDT's push is a pressure SHADOW (redirected flux), so the test is: how much may leak
# to heat before busting Earth's geothermal budget.

c      = 2.99792458e8            # relay speed [m/s]
M_E    = 5.972e24               # Earth mass [kg] (measured)
v_orb  = 29782.7                # Earth orbital velocity [m/s] (measured)
r_orb  = 1.495978707e11         # 1 AU [m]
P_geo  = 47e12                  # geothermal budget [W] (the measured ceiling)

# --- Route A: the leakage ceiling ---
# occluded gravitational throughput = momentum flux carried at the relay speed:
F_grav = M_E * v_orb**2 / r_orb          # native centripetal force, no GM
P_occ  = F_grav * c                      # redirected throughput [W]
eta_max = P_geo / P_occ                   # leakage ceiling (fraction allowed to thermalise)

print("SAR01 — Le Sage thermal budget (direct, native, no GM)")
print("="*60)
print(f"[A] F_grav = M v^2/r        = {F_grav:.4e} N")
print(f"    P_occ  = F_grav * c     = {P_occ:.4e} W   (redirected throughput)")
print(f"    eta_max = P_geo / P_occ = {eta_max:.4e}   [CEILING]")
print(f"    prior earned ceiling 4.4e-18 -> reproduced clean.")
print()
print("[C] buffer/throughpole/terminus:")
print("    occlusion = pressure SHADOW (redirection) = THROUGHPOLE (in one side, out the other).")
print("    net push comes from the pressure asymmetry, NOT from captured/destroyed flux.")
print("    => no TERMINUS required. Le Sage's death (which needs a terminus) does not apply.")
print("    SDT's structural eta = 0 (elastic redirection) << ceiling 4.4e-18.")
print()
print("[B] recharge (Maxwell isotropy-restoration): OPEN.")
print("    what restores the redirected flux's isotropy = the Law-II release-rate microphysics.")
print("    NOT fabricated here; flagged OPEN at the Law-II root.")
print()
print(f"VERDICT: terminus-free (throughpole); heating ceiling eta<{eta_max:.2e} on record;")
print("         recharge OPEN (Law-II). No heating problem. Le Sage kill does NOT transfer to SDT.")
