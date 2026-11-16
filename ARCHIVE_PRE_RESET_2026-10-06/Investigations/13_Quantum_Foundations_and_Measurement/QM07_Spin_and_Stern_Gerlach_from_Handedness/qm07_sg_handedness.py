"""
QM07 — Spin & Stern-Gerlach from Handedness.  J. C. Harvey, Melbourne, 2026-07-04.

MACHINERY ONLY. A vortex carries a binary circulation handedness eta = +/-1 (EMC03). In a
swirl gradient G the differential-occlusion push is x = eta*G*L (+ thermal smear). No spin
operator, no Pauli algebra, no mu_B, no W+1 g-factor anywhere. The observed SG two-spot
pattern and the sequential-SG transmission cos^2(theta/2) are OBSERVED data anchors.
Thresholds pre-committed in RUN_LOG.md. Seed 23, N = 2e5 per condition.
"""
import numpy as np, sys
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass
rng = np.random.default_rng(23)
N   = 200_000

print("="*78)
print("  QM07 — spin two-valuedness & Stern-Gerlach from binary handedness")
print("="*78)

print("\n  PHASE 1/3 — two spots, no middle (the discriminator), deflection ~ gradient")
GL = 1.0                       # push magnitude (arb. units — NOT calibrated to any magneton)
sig = GL/6.0
eta = rng.choice([-1.0, 1.0], N)
ok = True
print(f"  {'G':>4}{'centre-band occ.':>18}{'peak asymmetry':>16}{'separation':>12}")
seps = {}
for G in (1.0, 2.0, 4.0):
    xdet = eta*G*GL + rng.normal(0, G*sig, N)          # smear scales with G (same beam optics)
    centre = np.mean(np.abs(xdet) < G*GL/2)
    up, dn = np.mean(xdet > 0), np.mean(xdet < 0)
    asym = abs(up-dn)
    sep = np.mean(xdet[xdet>0]) - np.mean(xdet[xdet<0])
    seps[G] = sep
    if centre >= 0.01 or asym > 4*np.sqrt(0.25/N)*2: ok = False
    print(f"  {G:>4.0f}{centre:>18.4%}{asym:>16.4f}{sep:>12.3f}")
lin_dev = max(abs(seps[2.0]/(2*seps[1.0]) - 1), abs(seps[4.0]/(4*seps[1.0]) - 1))
print(f"  linearity: max dev of separation vs G = {lin_dev:.3%} (gate 1%: {'PASS' if lin_dev<0.01 else 'FAIL'})")
print(f"  gates centre<1% & equal peaks: {'PASS' if ok else 'FAIL'}")
# rival comparison column (OBSERVED SG data kills this, not SDT):
mu_axis = rng.uniform(-1, 1, N)                        # classical dipole: cos(theta) isotropic
xcl = mu_axis*GL + rng.normal(0, sig, N)
print(f"  RIVAL (classical continuous dipole): centre-band occupancy = {np.mean(np.abs(xcl)<GL/2):.1%}"
      f"  -> filled continuum; the OBSERVED two-spot data falsifies the continuous rival.")

print("\n  PHASE 2 — moment magnitude / g-factor: NOT claimed here (pre-declared).")
print("  Binary moment (two signs, one magnitude) is structural from Phase 1. The g NUMBER")
print("  is OPEN: engine benchmark B17 owns the measured 2.00232; no W+1 citation, no mu_B.")

print("\n  PHASE 4 — sequential Stern-Gerlach, filter A then analyzer B at angle theta")
thetas = np.arange(0, 181, 15)*np.pi/180
obs = np.cos(thetas/2)**2                              # OBSERVED transmission curve (data anchor)

# M1: native candidate — undisturbed hidden handedness vector, uniform on sphere, filtered by A
v = rng.normal(size=(N,3)); v /= np.linalg.norm(v, axis=1)[:,None]
passA = v[:,2] > 0                                     # A along +z
vA = v[passA]
t_m1 = []
for th in thetas:
    b = np.array([np.sin(th), 0.0, np.cos(th)])
    t_m1.append(np.mean(vA@b > 0))
t_m1 = np.array(t_m1)
rms1 = np.sqrt(np.mean((t_m1-obs)**2))

# M2: diagnostic probe (LABELLED, not a derivation) — re-preparation residence density
# rho ~ cos(angle to A-axis) on the passed hemisphere:  theta_l = asin(sqrt(u))
u   = rng.uniform(0, 1, N); ph = rng.uniform(0, 2*np.pi, N)
tl  = np.arcsin(np.sqrt(u))
w2  = np.stack([np.sin(tl)*np.cos(ph), np.sin(tl)*np.sin(ph), np.cos(tl)], axis=1)
t_m2 = []
for th in thetas:
    b = np.array([np.sin(th), 0.0, np.cos(th)])
    t_m2.append(np.mean(w2@b > 0))
t_m2 = np.array(t_m2)
rms2 = np.sqrt(np.mean((t_m2-obs)**2))

print(f"  {'theta':>7}{'observed':>10}{'M1 native':>11}{'M2 probe':>10}")
for th, o, a, b_ in zip(thetas*180/np.pi, obs, t_m1, t_m2):
    print(f"  {th:>7.0f}{o:>10.3f}{a:>11.3f}{b_:>10.3f}")
print(f"  M1 (undisturbed vector, native candidate): RMS vs observed = {rms1:.4f}"
      f"  -> prompt gate <2%: {'PASS' if rms1<0.02 else 'FAIL — the triangle law, as pre-declared'}")
print(f"  M2 (cos-weighted re-preparation, PROBE):   RMS vs observed = {rms2:.4f}"
      f"  (gate <0.5%: {'PASS' if rms2<0.005 else 'FAIL'})")

print("\n  READING (honest):")
print("  * two-valuedness + two-spot + gradient-linearity: NATIVE machinery — binary")
print("    handedness IS the two-spot mechanism; the classical continuum rival dies on data.")
print("  * sequential SG: the undisturbed-vector machinery gives the TRIANGLE law (fails at")
print("    ~7% RMS) — the honest miss. The probe shows exactly WHAT closes it: a residence /")
print("    re-preparation density ~ cos(angle) after the filter. That density is the SAME")
print("    owed law as QM04/QM05 (RESIDENCE-LAW root, FLM14 rule-form-4 in flight): nothing")
print("    here derives it; naming it is the result.")
print("="*78)
