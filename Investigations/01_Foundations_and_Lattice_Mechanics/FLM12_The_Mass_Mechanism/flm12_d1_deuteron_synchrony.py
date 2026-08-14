#!/usr/bin/env python3
# FLM12 - D1 : does the DEUTERON binding fall OUT of the synchrony-saving mechanism?
# Mechanism (FLM12 Step 8): a bond = two forms' field-engagements OVERLAP and phase-lock;
# the shared region is re-relayed ONCE not twice, so the joint engagement is LESS than the
# sum by the shared amount -> E_bind = (engagement density) x (overlap volume).
#
# STRESS DISCIPLINE: every input tagged [derivation basis] or [MEASURED-ANCHOR]; every candidate tagged
# PRINCIPLED / COMPARATOR / FISHED. A number is only a RESULT if it falls out with no fitted scale
# and no fished exponent. We do NOT pick a winner; we show the whole spread and let it speak.
import math

# ---- constants -------------------------------------------------------------
hbar_c   = 197.3269804      # MeV*fm            [derivation basis: hbar,c]
alpha    = 1/137.035999084  #                   [derivation basis]
mN_c2    = 938.918          # MeV (avg p,n)     [MEASURED-ANCHOR]
me_c2    = 0.51099895       # MeV               [derivation basis: m_e]
R_p      = 0.8414           # fm                [MEASURED-ANCHOR: proton boundary radius]
D        = 1.94             # fm  n-p separation[MEASURED-ANCHOR: deuteron gap, NP17]
E_meas   = 2.224566         # MeV               [MEASURED-ANCHOR: deuteron binding, the TARGET]

aC       = alpha*hbar_c     # = 1.4400 MeV*fm   Coulomb constant in natural units

print("="*70)
print(" FLM12-D1 : deuteron binding from the synchrony-saving mechanism")
print("="*70)
print(f"  TARGET (measured)         E_bind = {E_meas:.4f} MeV")
print(f"  inputs: R_p={R_p} fm  D={D} fm  m_N c^2={mN_c2} MeV  alpha*hbar*c={aC:.4f} MeV*fm\n")

# geometric facts
touch = 2*R_p
print(f"  [FACT] hard boundaries touch only if D < 2R_p = {touch:.3f} fm.  Here D={D} fm.")
print(f"         => at the deuteron separation the R_p boundaries DO NOT OVERLAP",
      "(gap %.3f fm)."%(D-touch), "\n")

Omega_frac = R_p**2 / (4*D**2)   # solid angle nucleon-B subtends at A, /4pi (small-angle disk)

cands = []
# --- PRINCIPLED readings of "engagement-density x overlap-volume" ---
cands.append(("hard-sphere R_p overlap x density", "PRINCIPLED",
              0.0 if D>=touch else (mN_c2)*( (math.pi/12)*(2*R_p-D)**2*(4*R_p+D) )/((4/3)*math.pi*R_p**3)))
cands.append(("influx solid-angle share  m_N c^2 * (Omega_B/4pi)", "PRINCIPLED",
              mN_c2*Omega_frac))
cands.append(("bare shared internal electron  m_e c^2", "PRINCIPLED",
              me_c2))
# --- COMPARATOR: the OTHER mechanism (NP17 electrostatic geared bond) that already lands ---
cands.append(("NP17 electrostatic  3*alpha*hbar*c / D  (DIFFERENT mechanism)", "COMPARATOR",
              3*aC/D))
# --- FISHED: exponents/coefficients tried until one lands (NOT a derivation) ---
cands.append(("mutual solid-angle SQUARED  m_N c^2 *(Omega/4pi)^2", "FISHED",
              mN_c2*Omega_frac**2))
cands.append(("shared-electron x factor 4.35", "FISHED",
              me_c2*4.353))

print(f"  {'candidate':<52}{'tag':<12}{'E(MeV)':>9}  x target")
print("  "+"-"*84)
for name,tag,E in cands:
    r = E/E_meas if E_meas else 0
    print(f"  {name:<52}{tag:<12}{E:>9.3f}  {r:>6.2f}x")

print("\n  READING:")
print("  - PRINCIPLED spread = %.3f .. %.1f MeV : brackets 2.224 but does NOT predict it."%(
      me_c2, mN_c2*Omega_frac))
print("  - hard R_p boundaries do not touch at D -> binding is a FAR-FIELD influx effect,")
print("    profile rho_eng(r>R_p) UNSPECIFIED (same open kernel as FLM03<->FLM10).")
print("  - the only expression that LANDS is the COMPARATOR (NP17 electrostatic), a DIFFERENT")
print("    mechanism; the synchrony route does not independently reproduce it.")
print("  - the SQUARED form lands at 2.08 MeV but its exponent was FISHED -> numerology, not a result.")
print("\n  VERDICT: D1 does NOT pay out. Synchrony mechanism ACCOMMODATES 2.224 MeV (with a chosen")
print("           profile/exponent) but does not DERIVE it. FLM12 quantitative ledger stays UNPAID.")
