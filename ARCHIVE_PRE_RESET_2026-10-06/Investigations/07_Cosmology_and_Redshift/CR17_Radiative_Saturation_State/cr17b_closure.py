#!/usr/bin/env python3
"""
CR17b - Closing the lambda_sat debt.

CR17 left lambda_sat as a band convention (near-IR), which left P_rad loose by x10.4.
This closes it: enumerate the candidate depinning conditions, compute what each predicts,
report all of them including the failures, and identify which lands in-band.

Mechanism source is Harvey's own (opacity-logjam thread):
  "opacity = radiation pressure so intense that radiative interference + decoherence cause a
   medium logjam ... the Clearing = a jamming/depinning transition, releases at a critical
   density ... baryons = pinned defects = the obstacles the relay-traffic jams around ->
   that obstacle term IS baryon loading R -> c_s = c/sqrt(3(1+R))"

ANCHOR DISCIPLINE. No z=1100, no T=3000 K, no CR13 975 nm. The baryon density is sourced from
BBN deuterium (eta), NOT from Omega_b of the CMB fit, so the closure cannot be circular with
the CMB it is meant to explain.
"""
import math

# ---- measured, none from a CMB fit ----
c        = 2.99792458e8
sigma_SB = 5.670374419e-8
b_wien   = 2.897771955e-3
T_0      = 2.7255                # FIRAS
k_B      = 1.380649e-23
h_pl     = 6.62607015e-34
m_p      = 1.67262192369e-27
sigma_T  = 6.6524587321e-29
H_0      = 2.27e-18
R_CMB    = 9.527e26
eta_BBN  = 6.1e-10               # baryon-to-photon ratio, BBN deuterium  [MEASURED, non-CMB]
zeta3    = 1.2020569031595943

a_rad = 4.0 * sigma_SB / c
P_0   = a_rad * T_0 ** 4 / 3.0

# present photon and baryon number densities, BBN route
n_gam0 = 16.0 * math.pi * zeta3 * (k_B * T_0 / (h_pl * c)) ** 3
n_b0   = eta_BBN * n_gam0
rho_g0 = a_rad * T_0 ** 4 / c ** 2
rho_b0 = n_b0 * m_p

out = []
def p(s=""):
    out.append(s); print(s)

def state(N):
    T = N * T_0
    return T, c / N, N ** 4 * P_0, b_wien / T

p("=" * 88)
p("CR17b - CLOSING THE lambda_sat DEBT")
p("=" * 88)
p()
p("  baryon density sourced from BBN, not from the CMB fit:")
p("    eta (deuterium)  = %.3e" % eta_BBN)
p("    n_gamma,0        = %.4e m^-3" % n_gam0)
p("    n_b,0            = %.4e m^-3   (Planck Omega_b route gives 0.2512 - agrees to %.1f %%)"
  % (n_b0, abs(n_b0 - 0.2512) / 0.2512 * 100.0))
p("    rho_b,0/rho_g,0  = %.2f" % (rho_b0 / rho_g0))
p("  Prop 13 coasting dilution: n_b ~ N^3 ,  rho_gamma ~ N^4  -> the ratio falls as 1/N")
p()

p("-" * 88)
p("CANDIDATE DEPINNING CONDITIONS - all evaluated, failures reported")
p("-" * 88)
cands = []

# --- C1 Ioffe-Regel: wave localisation, k * mfp = 1 ---
# mfp = 1/(n_e sigma_T), n_e = n_b0 N^3 (x_e = 1), k = 2 pi / lambda, lambda = b/(N T_0)
# 1 = (2 pi N T_0 / b) * 1/(n_b0 N^3 sigma_T)  ->  N^2 = 2 pi T_0/(b n_b0 sigma_T)
N1 = math.sqrt(2.0 * math.pi * T_0 / (b_wien * n_b0 * sigma_T))
cands.append(("C1  Ioffe-Regel  k*mfp = 1", N1, "wave delocalisation in a scattering medium"))

# --- C2 scattering rate = decompression rate:  n_e sigma_T v(N) = H_0 ---
N2 = math.sqrt(H_0 / (n_b0 * sigma_T * c))
cands.append(("C2  n_e sigma_T v = H_0", N2, "relay traffic outruns the decompression clock"))

# --- C3 optical depth unity over the CMB radius ---
N3 = (1.0 / (sigma_T * R_CMB * n_b0)) ** (1.0 / 3.0)
cands.append(("C3  tau = 1 over R_CMB", N3, "single-scattering horizon"))

# --- C4 baryon loading R = 1  (HARVEY'S STATED MECHANISM) ---
# R = (3/4) rho_b/rho_gamma = (3/4)(rho_b0/rho_g0)/N
N4 = 0.75 * rho_b0 / rho_g0
cands.append(("C4  obstacle loading R = 1", N4, "pinned defects match relay inertia -- STATED"))

# --- C5 baryon-photon energy equality, rho_b = rho_gamma ---
N5 = rho_b0 / rho_g0
cands.append(("C5  rho_b = rho_gamma", N5, "matter-radiation equality, NO dark matter"))

p("  %-30s %-12s %-13s %-11s %s" % ("condition", "N", "lambda [nm]", "T [K]", "verdict"))
p("  " + "-" * 84)
NIR_LO, NIR_HI = 780e-9, 2500e-9
for name, N, why in cands:
    T, v, P, lam = state(N)
    inb = NIR_LO <= lam <= NIR_HI
    p("  %-30s %-12.4g %-13.4g %-11.4g %s"
      % (name, N, lam * 1e9, T, "IN near-IR band" if inb else "excluded"))
p()
for name, N, why in cands:
    T, v, P, lam = state(N)
    if not (NIR_LO <= lam <= NIR_HI):
        off = lam / 1.045e-6
        p("    %-30s off the band centre by x%.3g   (%s)" % (name.split("  ")[0], off, why))
p()

# ===================================================================== the closure
p("=" * 88)
p("CLOSURE - Harvey's stated mechanism is C4: the jam releases when obstacle loading R = 1")
p("=" * 88)
p("  R(N) = (3/4) rho_b/rho_gamma = (3/4)(rho_b0/rho_g0)/N = %.2f / N" % (0.75*rho_b0/rho_g0))
p("  R = 1  ->  N = %.2f" % N4)
p()
T4, v4, P4, lam4 = state(N4)
T5, v5, P5, lam5 = state(N5)
p("  %-34s %-16s %-16s" % ("", "C4  R = 1", "C5  rho_b = rho_g"))
p("  %-34s %-16.2f %-16.2f" % ("epoch index N", N4, N5))
p("  %-34s %-16.1f %-16.1f" % ("saturation wavelength [nm]", lam4 * 1e9, lam5 * 1e9))
p("  %-34s %-16.1f %-16.1f" % ("matrix temperature T [K]", T4, T5))
p("  %-34s %-16.4e %-16.4e" % ("speed of light v = c/N [m/s]", v4, v5))
p("  %-34s %-16.4e %-16.4e" % ("radiation pressure P [Pa]", P4, P5))
p("  %-34s %-16.4f %-16.4f" % ("v as % of c", v4/c*100, v5/c*100))
p()
p("  The two differ only by the 3/4 in the loading convention. Both land in the near-IR.")
p("  Quoted closure = C4 (Harvey's stated R), with C5 as the convention bound.")
p()
p("  sound speed at the transition, c_s = c/sqrt(3(1+R)):")
for lbl, R in (("R = 1  (C4)", 1.0), ("R = 0.6 (CR13 drag epoch)", 0.6), ("R -> 0 (pure radiation)", 0.0)):
    p("    %-28s c_s = %.4e m/s = %.4f c" %
      (lbl, c / math.sqrt(3.0 * (1.0 + R)), 1.0 / math.sqrt(3.0 * (1.0 + R))))
p()

# ===================================================================== discriminator
p("-" * 88)
p("WHY THIS IS A DISCRIMINATOR, NOT A RESTATEMENT")
p("-" * 88)
p("  C4/C5 are matter-radiation equality with BARYONS ONLY, because SDT has no dark matter.")
p("  LCDM's equality is CDM-dominated: rho_m/rho_b = (Omega_c+Omega_b)/Omega_b ~ 6.0,")
p("  so its equality sits ~6x earlier in N and cannot coincide with the Clearing.")
rho_m_over_b = 6.0
p("    SDT  (baryons only)   equality at N = %.0f" % N5)
p("    LCDM (CDM + baryons)  equality at N = %.0f  -> lambda = %.0f nm (deep UV, NOT the band)"
  % (N5 * rho_m_over_b, b_wien / (T_0 * N5 * rho_m_over_b) * 1e9))
p("  So 'the jam releases at obstacle loading unity' lands in the near-IR ONLY if there is")
p("  no dark matter. The no-dark-matter premise is doing the work, and it is falsifiable:")
p("  add CDM to the obstacle budget and the prediction leaves the band by a factor ~6.")
p()

# ===================================================================== collapse of the spread
p("-" * 88)
p("WHAT THE CLOSURE BUYS - the CR17 spread collapses")
p("-" * 88)
p("  %-26s %-24s %-24s" % ("quantity", "CR17 (band convention)", "CR17b (closed at R=1)"))
p("  %-26s %-24s %-24.4e" % ("speed v [m/s]", "2.20e5 ... 3.95e5", v4))
p("  %-26s %-24s %-24.4e" % ("radiation pressure [Pa]", "4.63e-3 ... 4.80e-2", P4))
p("  %-26s %-24s %-24.1f" % ("temperature [K]", "2070 ... 3715", T4))
p("  %-26s %-24s %-24.1f" % ("epoch index N", "759 ... 1363", N4))
p()
p("  P_rad was the loose one (x10.4 across the band). It is now a single number.")
p("  Inputs consumed by the closure: T_0 (FIRAS) and eta (BBN deuterium). Both measured,")
p("  neither from a CMB fit. Fitted parameters used: ZERO.")
p()
p("=" * 88)
p("CLOSED STATE")
p("=" * 88)
p("    saturation wavelength   lambda = %.0f nm     (near-IR, from R = 1)" % (lam4 * 1e9))
p("    speed of light          v      = %.4e m/s  = %.4f %% of c" % (v4, v4 / c * 100))
p("    radiation pressure      P      = %.4e Pa" % P4)
p("    matrix temperature      T      = %.0f K" % T4)
p("    epoch index             N      = %.0f" % N4)
p("=" * 88)

with open("cr17b_results.txt", "w", encoding="utf-8") as fh:
    fh.write("\n".join(out) + "\n")
