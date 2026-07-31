#!/usr/bin/env python3
"""
CR17 - The radiative saturation state.

Task (Harvey, 2026-07-31): use P_eff and the Shapiro-delay c-variance as one pressure/
gradient regime, scale back to near-infrared saturation, and report at that state:
    (1) the speed c        (2) the radiation pressure      (3) the spation-matrix temperature

ANCHOR DISCIPLINE. z = 1100 and T = 3000 K are struck (LCDM fit outputs). CR13's
lambda_emit = 974.7 nm is ALSO not used as an anchor: it was produced by applying Wien to
T_0*(1+z) with the imported z, so anchoring on it would be circular. The anchor here is the
near-infrared BAND itself - the SDT claim that the logjam clears when peak emission crosses
out of the visible. The band is swept; nothing is tuned.
"""
import math

# ---- measured inputs (mirror sdt::laws::measured) ----
c        = 2.99792458e8        # m/s   exact
sigma_SB = 5.670374419e-8      # W m^-2 K^-4   CODATA
b_wien   = 2.897771955e-3      # m K           CODATA displacement constant
T_0      = 2.7255              # K             FIRAS
z_sun    = 2.12e-6             # solar gravitational redshift
R_sun    = 6.957e8             # m
k_B      = 1.380649e-23
eV_J     = 1.602176634e-19

# ---- laws.hpp law_III ----
P_eff    = 5.225e31            # Pa   = 4 k_e e^2 / (pi R_p^2 r_e^2)   [class E, calibrated]

a_rad = 4.0 * sigma_SB / c
P_0   = a_rad * T_0 ** 4 / 3.0          # CR16: this IS the document's P_0, derived

out = []
def p(s=""):
    out.append(s); print(s)

p("=" * 90)
p("CR17 - RADIATIVE SATURATION STATE")
p("anchor = the near-infrared band (swept). z=1100, T=3000 K and CR13's 975 nm are NOT used.")
p("=" * 90)
p()

# ============================================================== 1. one gradient law
p("-" * 90)
p("[1] THE GRADIENT REGIME IS ONE LAW - Shapiro locally, epoch depth cosmologically")
p("-" * 90)
p("  refractive form:   v = c / n      with    n = 1 + z      (z = depth)")
p()
n_sun = 1.0 + z_sun
p("  SOLAR (Shapiro regime):  z_sun = %.3e  ->  n = %.9f" % (z_sun, n_sun))
p("    speed deficit at the solar surface  c - c/n = %.1f m/s" % (c - c / n_sun))
p("    om_sun = z_sun * R_sun              = %.1f m   (document Prop 6: ~1476 m)"
  % (z_sun * R_sun))
p()
p("  EPOCH (cosmological regime):  n = N = 1 + z ,  v(N) = c/N")
p("    Same functional form. The Sun's gradient is a local depth; the epoch is a global one.")
p()
N_Peff = (P_eff / P_0) ** 0.25
p("  P_eff on the same pressure ladder,  N = (P/P_0)^(1/4):")
p("    P_eff  = %.4e Pa  ->  N = %.4e   (matrix/atomic pressure ceiling)" % (P_eff, N_Peff))
p("    P_0    = %.4e Pa  ->  N = 1      (present epoch)" % P_0)
p("    ladder span from present to P_eff: %.2f decades in pressure, %.2f in N"
  % (math.log10(P_eff / P_0), math.log10(N_Peff)))
p()

# ============================================================== 2. the anchor
p("-" * 90)
p("[2] THE SATURATION ANCHOR - peak emission crosses out of the visible")
p("-" * 90)
p("  Wien:  lambda_peak * T = b = %.6e m K" % b_wien)
p("  At saturation the bath peak sits at lambda_sat, so   T_sat = b / lambda_sat,")
p("  and the epoch index follows from the ladder  N = T_sat / T_0.")
p("  Nothing is fitted: lambda_sat is the input, everything else is forced.")
p()

def state(lam):
    T = b_wien / lam
    N = T / T_0
    v = c / N
    P = a_rad * T ** 4 / 3.0
    u = a_rad * T ** 4
    return T, N, v, P, u

p("  %-26s %-9s %-10s %-12s %-13s %-11s"
  % ("lambda_sat", "T_sat [K]", "N", "v = c/N", "P_rad [Pa]", "u [J/m3]"))
p("  " + "-" * 84)
bands = [
    ("620 nm  visible red",        620e-9),
    ("700 nm  deep red",           700e-9),
    ("750 nm  RED EDGE",           750e-9),
    ("780 nm  near-IR onset",      780e-9),
    ("1000 nm  near-IR",          1000e-9),
    ("1400 nm  near-IR (DIN end)",1400e-9),
    ("2500 nm  short-wave IR",    2500e-9),
]
rows = []
for name, lam in bands:
    T, N, v, P, u = state(lam)
    rows.append((name, lam, T, N, v, P, u))
    p("  %-26s %-9.1f %-10.1f %-12.4e %-13.4e %-11.4e" % (name, T, N, v, P, u))
p()

# ============================================================== 3. the answers
p("-" * 90)
p("[3] THE THREE REQUESTED QUANTITIES AT RADIATIVE SATURATION")
p("-" * 90)
lo = state(780e-9)      # near-IR onset
hi = state(1400e-9)     # near-IR far end
mid = state(math.sqrt(780e-9 * 1400e-9))   # log-centre of the near-IR band
p("  Quoted as the near-IR band [780, 1400] nm, with the log-centre as the central value.")
p("  (log-centre used because every vessel variable is monomial in N - the halfway theorem)")
p("    log-centre wavelength = %.1f nm" % (math.sqrt(780e-9 * 1400e-9) * 1e9))
p()
p("  (1) SPEED OF LIGHT AT SATURATION      v_sat = c/N")
p("        central   %.4e m/s   = c / %.1f  = %.4f %% of c"
  % (mid[2], mid[1], mid[2] / c * 100.0))
p("        band      %.4e  ...  %.4e m/s" % (lo[2], hi[2]))
p("        equivalently a matrix refractive index n = %.1f (band %.1f - %.1f)"
  % (mid[1], lo[1], hi[1]))
p()
p("  (2) RADIATION PRESSURE AT SATURATION  P_rad = a T^4 / 3 = N^4 P_0")
p("        central   %.4e Pa" % mid[3])
p("        band      %.4e  ...  %.4e Pa" % (lo[3], hi[3]))
p("        energy density u = 3P = %.4e J/m3" % mid[4])
p()
p("  (3) SPATION-MATRIX TEMPERATURE        T_sat = N T_0 = b / lambda_sat")
p("        central   %.1f K   (kT = %.4f eV)" % (mid[0], k_B * mid[0] / eV_J))
p("        band      %.1f  ...  %.1f K" % (hi[0], lo[0]))
p()

# ============================================================== 4. distance to the ceiling
p("-" * 90)
p("[4] WHERE SATURATION SITS IN THE PRESSURE/GRADIENT REGIME")
p("-" * 90)
p("  %-34s %-14s %-14s" % ("state", "P [Pa]", "N"))
p("  %-34s %-14.4e %-14.4g" % ("present epoch", P_0, 1.0))
p("  %-34s %-14.4e %-14.4g" % ("radiative saturation (central)", mid[3], mid[1]))
p("  %-34s %-14.4e %-14.4g" % ("P_eff  matrix/atomic ceiling", P_eff, N_Peff))
p()
p("  saturation is %.2f decades in pressure above the present epoch," % math.log10(mid[3] / P_0))
p("  and still %.2f decades in pressure BELOW the P_eff matrix ceiling."
  % math.log10(P_eff / mid[3]))
p("  in N:  saturation N = %.1f ;  P_eff ceiling N = %.3e ;  ratio %.3e"
  % (mid[1], N_Peff, N_Peff / mid[1]))
p()
p("  So radiative saturation is nowhere near the matrix limit - the radiation field jams")
p("  the relay %.0f decades of pressure before the spations themselves are pressed to their"
  % math.log10(P_eff / mid[3]))
p("  atomic-scale ceiling. Saturation is a RADIATION-side limit, not a lattice-side one.")
p()
p("  Shapiro cross-check, one law over %.0f orders of depth:" % math.log10(mid[1] / z_sun))
p("    solar surface   n - 1 = %.3e   (v deficit %.0f m/s)" % (z_sun, c - c / n_sun))
p("    saturation      n - 1 = %.3e   (v deficit %.4e m/s)" % (mid[1] - 1.0, c - mid[2]))
p()

# ============================================================== 5. anchor sensitivity
p("-" * 90)
p("[5] ANCHOR SENSITIVITY - how hard does the answer depend on the band choice?")
p("-" * 90)
p("  All three outputs are pure powers of lambda_sat:")
p("      T ~ 1/lambda ,  N ~ 1/lambda ,  v ~ lambda ,  P_rad ~ 1/lambda^4")
p("  so a factor f error in the anchor gives f in T, N and v, and f^4 in P_rad.")
p("  Across the full near-IR band (780 -> 1400 nm, factor %.3f):" % (1400.0 / 780.0))
p("      T, N, v vary by  x%.2f      P_rad varies by  x%.1f"
  % (1400.0 / 780.0, (1400.0 / 780.0) ** 4))
p("  -> v_sat and T_sat are robust to the band choice; P_rad is NOT (it is the")
p("     quantity that most needs the saturation wavelength pinned by mechanism.")
p()
p("  For reference only, NOT used as an anchor: CR13's lambda_emit = 974.7 nm gives")
Tc, Nc, vc, Pc, uc = state(974.7e-9)
p("      T = %.1f K , N = %.1f , v = %.4e m/s , P_rad = %.4e Pa" % (Tc, Nc, vc, Pc))
p("  That N reproduces the imported redshift because 974.7 nm was BACK-COMPUTED from it")
p("  via Wien. It is a restatement of the input, not a check on it. Flagged, not used.")
p()
p("=" * 90)
p("ANSWER")
p("=" * 90)
p("  at radiative saturation, anchored on the near-IR band [780, 1400] nm:")
p("    speed of light        v = %.3e m/s   (%.4f %% of c ; band %.2e - %.2e)"
  % (mid[2], mid[2] / c * 100.0, lo[2], hi[2]))
p("    radiation pressure    P = %.3e Pa      (band %.2e - %.2e)" % (mid[3], lo[3], hi[3]))
p("    matrix temperature    T = %.0f K          (band %.0f - %.0f)" % (mid[0], hi[0], lo[0]))
p("    epoch index           N = %.0f            (band %.0f - %.0f)" % (mid[1], hi[1], lo[1]))
p("=" * 90)

with open("cr17_results.txt", "w", encoding="utf-8") as fh:
    fh.write("\n".join(out) + "\n")
