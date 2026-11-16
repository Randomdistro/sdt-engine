#!/usr/bin/env python3
"""
CR13 — CMB backtrack to the 'closest point of contact'.

Question (Harvey, 2026-06-28): we have a speed, a rate, a size, a distance and a
gradient. What was the wavelength of the radiation bath at the closest point of
contact, and does a 'trillion raindrops from a trillion places' (gradient) bath
survive the FIRAS blackbody constraint?

This tool is frame-NEUTRAL: it uses only the observed redshift z and the identity
lambda_received = lambda_emit * (1+z), which holds whether the redshift is read as
metric expansion (LCDM) or as accumulated pressure/closure gradient (SDT, GOM05).
Nothing here assumes expansion. Constants are measured inputs, tagged below.
"""
import math

# ---- measured inputs (FIRAS / Planck 2018 / CODATA) ----
T0     = 2.7255            # K     CMB monopole today (FIRAS)            [MEASURED]
z_rec  = 1089.80           #       redshift of last scattering (Planck)  [MEASURED]
dz_LS  = 80.0              #       thickness of last-scattering surface   [MEASURED]
b      = 2.897771955e-3    # m K   Wien wavelength-displacement law       [DERIVED const]
kB     = 8.617333262e-5    # eV/K  Boltzmann                              [CODATA]
eta    = 6.1e-10           #       baryon/photon ratio (BBN+CMB)          [MEASURED]
y_firas= 1.5e-5            #       FIRAS Compton-y upper bound            [MEASURED]
R_drag = 0.60             #       baryon loading rho_b/(4/3 rho_gamma)~  [MEASURED, order]

c = 2.99792458e8           # m/s

# ---- 1. anchors: the bath at emission vs received ----
T_rec  = T0*(1+z_rec)
lam_em = b/T_rec           # Wien peak at last scattering (emission)
lam_rx = b/T0              # Wien peak received today
kT_rec = kB*T_rec
Emean  = 2.7011*kB*T_rec   # mean photon energy at emission

# ---- 2. why ~3000 K lands at the bottom of the visible ----
delay  = 13.6/kT_rec       # how far below the 13.6 eV binding recombination waits

# ---- 3. the gradient ('closest contact') reading and the FIRAS gate ----
# A bath sourced across a range of depths arrives as a superposition of blackbodies
# spanning T0 (farthest, z=z_rec) up to ~T_rec/(1+z_near) for the nearest contact.
# A temperature spread of fractional RMS s makes a Compton-y distortion y ~ 0.5 s^2.
# FIRAS |y| < 1.5e-5  =>  s < sqrt(2 y).
s_max  = math.sqrt(2*y_firas)        # max fractional temperature spread allowed
# single thin surface: spread in (1+z) across dz_LS
s_thin = dz_LS/(1+z_rec)

# ---- 4. baryon-loaded sound speed (ties FD05 / the opacity-logjam thread) ----
cs_pure = c/math.sqrt(3)             # radiation ceiling
cs_load = c/math.sqrt(3*(1+R_drag))  # with baryon obstacles at the drag epoch

def fmt(lam):
    if   lam < 1e-6: return f"{lam*1e9:8.1f} nm"
    elif lam < 1e-3: return f"{lam*1e6:8.2f} um"
    else:            return f"{lam*1e3:8.3f} mm"

print("="*66)
print("CR13 — CMB backtrack to the closest point of contact")
print("="*66)
print("\n[1] ANCHORS (frame-neutral: lambda_rx = lambda_em*(1+z))")
print(f"  z_rec        = {z_rec}")
print(f"  T_rec        = {T_rec:8.1f} K")
print(f"  kT_rec       = {kT_rec:8.4f} eV")
print(f"  lambda_emit  = {lam_em*1e9:8.1f} nm   <- bath peak when transparency set in")
print(f"  lambda_recv  = {lam_rx*1e3:8.4f} mm   <- bath peak received today")
print(f"  mean photon  = {Emean:8.4f} eV")

print("\n[2] WHY ~3000 K = 'the bottom of the visible spectrum'")
print(f"  13.6 eV / kT_rec     = {delay:6.1f}   (recombination waits ~50x below binding)")
print(f"  1/eta (photon/baryon)= {1/eta:.3e}   ln = {math.log(1/eta):.1f}")
print(f"  visible 380-750 nm; bath peak {lam_em*1e9:.0f} nm = near-IR, one step past red")

print("\n[3] THE CLOSEST-CONTACT WAVELENGTH + THE FIRAS GATE")
print(f"  nearest contact  z->0  : lambda -> {fmt(lam_em)}  (~emission, near-IR)")
print(f"  farthest  z={z_rec:.0f}     : lambda -> {fmt(lam_rx)}  (microwave)")
print(f"  broad-gradient SPREAD  : {lam_em*1e9:.0f} nm -> {lam_rx*1e6:.0f} um  (x{lam_rx/lam_em:.0f})")
print(f"  single thin surface    : fractional T spread s_thin = {s_thin:.4f} ({100*s_thin:.2f}%)")
print(f"  FIRAS allows           : s_max = sqrt(2*{y_firas}) = {s_max:.5f} ({100*s_max:.3f}%)")
print(f"  VERDICT: a broad-z bath (s ~ O(1)) is excluded by ~{(1.0)/ (s_max):.0f}x.")
print( "          contributions must share T to < %.2f%% -> synchrony MUST collapse the smear." % (100*s_max))
print(f"  (note: the thin surface s_thin={100*s_thin:.2f}% is NOT a temperature spread —")
print( "         every LS point is redshifted to the SAME T0 today, so it makes no distortion.)")

print("\n[4] BARYON-LOADED SOUND SPEED (ties FD05 / opacity-logjam)")
print(f"  c/sqrt(3)            = {cs_pure:.4e} m/s  (pure radiation ceiling)")
print(f"  c/sqrt(3(1+R)), R={R_drag} = {cs_load:.4e} m/s  (with baryon obstacles)")
print(f"  ratio cs_load/c      = {cs_load/c:.4f}")

print("\n[5] gradient table: received lambda vs fractional depth into the redshift")
for f in [0.0,0.001,0.01,0.05,0.10,0.25,0.50,0.75,0.90,0.99,1.0]:
    z = f*z_rec
    print(f"  depth {f:5.3f} -> 1+z={1+z:8.1f} -> lambda {fmt(lam_em*(1+z))}")
