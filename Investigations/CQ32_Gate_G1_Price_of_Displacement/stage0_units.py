"""CQ-32 Stage 0 unit audit — verifies the Machian price equivalence in the protocol's Section 0.
Run: python stage0_units.py   (no repo deps; CODATA + corpus P_conv only)."""
import math
J_per_MeV = 1.602176634e-13
fm3_per_m3 = 1e45            # 1 m^3 = 1e45 fm^3
l_P = 1.616255e-35           # m
c   = 2.99792458e8           # m/s
m_p = 1.67262192369e-27      # kg
P_conv = 2.459e48            # Pa  (laws.hpp: Phi/l_P^3)

def Pa_to_MeV_fm3(Pa):  return Pa / J_per_MeV / fm3_per_m3
def MeV_fm3_to_Pa(x):   return x * J_per_MeV * fm3_per_m3

print(f"P_conv = {P_conv:.4e} Pa = {Pa_to_MeV_fm3(P_conv):.4e} MeV/fm^3")
print(f"P* = P_conv/3 = {P_conv/3:.4e} Pa = {Pa_to_MeV_fm3(P_conv/3):.4e} MeV/fm^3")
print(f"15.35 MeV/fm^3 = {MeV_fm3_to_Pa(15.35):.4e} Pa ; ratio P_conv/that = {P_conv/MeV_fm3_to_Pa(15.35):.3e}")

Phi = P_conv * l_P**3
V_disp_p = 3*m_p*l_P**3*c**2/Phi
print(f"V_disp_p = {V_disp_p:.4e} m^3 = {V_disp_p*fm3_per_m3:.4e} fm^3 ; "
      f"E=P*.V_disp_p = {(P_conv/3)*V_disp_p/J_per_MeV:.3f} MeV (m_p c^2 = {m_p*c*c/J_per_MeV:.3f})")
print(f"1 fm^3 @ P* -> {(P_conv/3)*1e-45/J_per_MeV:.3e} MeV (overshoot vs ~15 MeV/fm^3: "
      f"{(P_conv/3)*1e-45/J_per_MeV/15.35:.3e}x)")
