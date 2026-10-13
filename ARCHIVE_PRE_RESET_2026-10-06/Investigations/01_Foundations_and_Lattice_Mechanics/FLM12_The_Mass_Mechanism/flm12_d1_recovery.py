#!/usr/bin/env python3
# ============================================================================
#  FLM12 / D1' -- influx-regime recovery of the nuclear occlusion pressure
#
#  Supersedes the localized->extended premise fix (prior version of this file),
#  which used the fixed EM/electropause P_eff, found scalar occlusion ~34x too
#  weak, and RULED IT OUT -- landing on handed 3*alpha*hbar*c/D. Harvey's
#  correction re-opens that: "different occlusions occur at different INFLUX
#  REGIMES -- that is the whole concept behind P_eff. Calculate the CMB-onto-
#  sphere-surface for a sphere that only just engulfs the proton-deuteron."
#  Occlusion was ruled out only because the WRONG (EM) P_eff was used.
#
#  TEST (cannot be fished -- TARGET and INFLUX are computed INDEPENDENTLY):
#   * TARGET : what P_eff does the deuteron 2.224 MeV DEMAND, via occlusion?
#   * INFLUX : what is the CMB/boundary influx pressure AT the nuclear sphere,
#              built ONLY from law_I + law_IV (no target peeking)?
#  If the influx regime meets the target from its own construction, D1's
#  "no strong force" gap closes. If it only brackets it, grade it PARTIAL.
#
#  Author: J. C. Harvey, Melbourne.
# ============================================================================
import math

# --- canon (Engine/include/sdt/laws.hpp :: measured, law_I) -----------------
c      = 299792458.0
hbar   = 1.054571817e-34
l_P    = 1.616255e-35
a_rad  = 7.5657e-16            # Stefan radiation constant [J/m^3/K^4]
T_CMB  = 2.7255
R_CMB  = 9.527e26             # measured::R_CMB  [m] (distance to the Clearing)
m_p    = 1.67262192369e-27
m_e    = 9.1093837015e-31
alpha  = 7.2973525693e-3
e_SI   = 1.602176634e-19
MeV    = 1e6*e_SI
def to_MeVfm(J_m): return J_m/MeV*1e15          # J*m  -> MeV*fm

R_p    = 8.414e-16            # measured::R_p [m] (muonic; = 4 hbar/m_p c)
V_p    = (4/3)*math.pi*R_p**3 # geometric (boundary) proton volume

# --- law_I influx chain (verify against laws.hpp comments) ------------------
u_CMB  = a_rad*T_CMB**4                 # CMB energy density [J/m^3]
N      = R_CMB/l_P                      # causal depth (Planck shells)
P_conv = N*u_CMB                        # convergence pressure at PLANCK scale [Pa]
print("=== law_I influx chain (canon check) ===")
print(f"  u_CMB   = {u_CMB:.3e} J/m^3 ;  N = {N:.3e} (laws.hpp ~5.9e61)")
print(f"  P_conv  = {P_conv:.3e} Pa ;  P_conv/3 = {P_conv/3:.3e} Pa  (laws.hpp: 8.197e47)\n")

# --- TARGET: P_eff the deuteron DEMANDS (independent of any influx model) ---
E_d, r_d_fm = 2.224, 1.94       # occlusion: E = (pi/4) P_eff R_p^4 / r
Peff_needed = E_d*r_d_fm / ((math.pi/4)*(R_p*1e15)**4)   # MeV/fm^3
Peff_needed_Pa = Peff_needed*MeV/1e-45
print("=== TARGET (deuteron demands, occlusion at r=1.94 fm) ===")
print(f"  P_eff needed = {Peff_needed:.3f} MeV/fm^3 = {Peff_needed_Pa:.3e} Pa\n")

# --- three candidate INFLUX REGIMES 'CMB onto a sphere ~ R_p' ---------------
P_thermal = u_CMB/3                       # (1) literal thermal CMB radiation pressure
rho_nuc   = m_p*c**2 / V_p                # (3) influx ENGAGED at the proton scale =
                                          #     m_p c^2 / V_p  (Law IV: engaged influx per
                                          #     volume IS the energy density). Principled.
P_EM      = m_p*m_p*m_e*m_e*c**5/(4*math.pi*alpha*hbar**3)   # electropause P_eff (D1 route)
print("=== CANDIDATE INFLUX REGIMES vs target ===")
print(f"  (1) thermal CMB  u/3          = {P_thermal:.3e} Pa  -> {P_thermal/Peff_needed_Pa:.0e}x  (46 orders SMALL)")
print(f"  (2) full P_conv (Planck)      = {P_conv:.3e} Pa  -> {P_conv/Peff_needed_Pa:.0e}x  (14 orders BIG)")
print(f"  (0) EM electropause (D1)      = {P_EM:.3e} Pa  -> {P_EM/Peff_needed_Pa:.2f}x  (33x too small; occlusion 'ruled out')")
print(f"  (3) nuclear m_p c^2/V_p       = {rho_nuc:.3e} Pa  -> {rho_nuc/Peff_needed_Pa:.1f}x   <-- THE REGIME")
print(f"      (as radiation pressure /3)= {rho_nuc/3:.3e} Pa  -> {(rho_nuc/3)/Peff_needed_Pa:.1f}x\n")

# --- binding each regime gives (occlusion, r = 1.94 fm) ---------------------
print("=== occlusion binding E=(pi/4)P_eff R_p^4/r  at r=1.94 fm ===")
for label,Peff in [("EM electropause (D1 failed)",P_EM),
                   ("nuclear /3 (radiation P)",rho_nuc/3),
                   ("nuclear m_p c^2/V_p",rho_nuc)]:
    Emev = to_MeVfm((math.pi/4)*Peff*R_p**4)/r_d_fm
    print(f"  P_eff={Peff:.2e} Pa [{label:26s}] -> {Emev:7.2f} MeV")
print(f"  (deuteron 2.224 ; typical nucleus ~8/nucleon ; alpha ~28 total)\n")

# --- HUNTER verdict ---------------------------------------------------------
gain = (rho_nuc/3)/P_EM
print("=== VERDICT (HUNTER: trace->ground->correct; bracket != prediction) ===")
print(f"  ROOT of D1's failure: the wrong INFLUX REGIME. The EM electropause P_eff")
print(f"  is not the pressure a NUCLEUS shadows. The influx engaged at the proton's")
print(f"  own volume is its energy density m_p c^2/V_p = {rho_nuc:.2e} Pa -- ~{gain:.0f}x stronger.")
print(f"  CORRECTION: with the nuclear regime, scalar occlusion is NOT ruled out; it")
print(f"  reaches the nuclear SCALE (tens of MeV). D1's 'SDT has no strong force' gap")
print(f"  CLOSES in order of magnitude -- the strong scale IS the CMB influx engaged")
print(f"  at the nuclear sphere. [premise VINDICATED at the scale level]")
print(f"  LIMIT: it OVERSHOOTS the anomalously-loose deuteron by ~{(rho_nuc/3)/Peff_needed_Pa:.0f}x. The two")
print(f"  regimes now BRACKET it (EM 33x under, nuclear 11x over); the exact 2.224 is")
print(f"  NOT predicted -- it needs the deuteron's loose geometry/separation, not just P.")
gm_full = math.sqrt(P_EM * rho_nuc)      # with full nuclear energy density
gm_rad  = math.sqrt(P_EM * rho_nuc/3)    # with radiation pressure /3
print(f"\n  [FLAG, REJECTED as numerology -- NOT robust] geometric mean of the two regimes:")
print(f"    sqrt(P_EM*P_nuc)   = {gm_full:.2e} Pa -> {gm_full/Peff_needed_Pa:.2f}x target (1% -- looks great)")
print(f"    sqrt(P_EM*P_nuc/3) = {gm_rad:.2e} Pa -> {gm_rad/Peff_needed_Pa:.2f}x target (42% off -- looks bad)")
print(f"  the 'match' flips on the u-vs-u/3 choice => regime-fragile => numerology, discarded.")
print(f"\n  GRADE: PARTIAL RECOVERY. Scale recovered & mechanism-regime identified; exact")
print(f"  deuteron bracketed. Absolute closure now needs the loose-geometry/topology (D1'').")
