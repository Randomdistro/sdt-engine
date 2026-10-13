"""
QM02 — Uncertainty as Relay Bandwidth.  J. C. Harvey, Melbourne, 2026-07-03.

MACHINERY ONLY. A wake pulse is a REAL displacement field f(x) on a granular lattice
(spacing a = 1 = the lP analog). Its elastic energy density is w(x) = f(x)^2 (energy of a
strained medium goes as strain squared -- classical mechanics, not a probability rule).
Parseval gives the spectral energy density |F(k)|^2. The question run here: does the
energy-weighted width product Dx*Dk have a floor of 1/2, for every buildable pulse?

NO wavefunction, NO commutator, NO operator-variance inequality appears anywhere below.
The only mathematics is: real pulses, energy weights, discrete Fourier analysis of a real
signal. Thresholds pre-committed in RUN_LOG.md (P1a, P1b, P4) BEFORE this file was written.

hbar enters NOWHERE in the computation. It enters once, afterwards, at the k->p bridge
(Phase 2, provenance narrated in output): measured circulation kappa = h/m (FD02) plus the
substrate phase-gradient kinematics => Dp = hbar*Dk. That single point is the flagged borrow.
"""
import numpy as np, sys
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass

L = 8192
x = np.arange(L) - L//2          # site coordinates, a = 1
k = 2*np.pi*np.fft.fftfreq(L, d=1.0)

def widths(f, cell_smear=False):
    """Energy-weighted rms widths of a real pulse and of its spectral energy density."""
    w = f*f; w /= w.sum()
    xb = (w*x).sum()
    vx = (w*(x-xb)**2).sum()
    if cell_smear: vx += 1.0/12.0          # each spation is a cell of width a, not a point
    F = np.fft.fft(f)
    wk = np.abs(F)**2; wk /= wk.sum()
    kb = (wk*k).sum()
    vk = (wk*(k-kb)**2).sum()
    return np.sqrt(vx), np.sqrt(vk)

def product(f, cell_smear=False):
    sx, sk = widths(f, cell_smear)
    return sx*sk, sx, sk

# ---- pulse zoo (all REAL displacement fields) ----------------------------------------
def gauss(s):    return np.exp(-x**2/(4.0*s*s))          # energy density exp(-x^2/2s^2)
def box(W):      return np.where(np.abs(x) < W/2, 1.0, 0.0)
def tri(W):      return np.clip(1.0 - np.abs(x)/(W/2), 0.0, None)
def expo(s):     return np.exp(-np.abs(x)/(2.0*s))       # energy density exp(-|x|/s)
def delta():     f = np.zeros(L); f[L//2] = 1.0; return f
def twosite():   f = np.zeros(L); f[L//2] = 1.0; f[L//2+1] = 1.0; return f

print("="*78)
print("  QM02 — relay bandwidth: energy-weighted width product of real lattice pulses")
print("  (thresholds pre-committed in RUN_LOG.md; a = 1 = spation width)")
print("="*78)

print("\n  PHASE 1a — continuum-regime pulses (width >= 3a). Gate: all >= 0.495;")
print("  Gaussian saturates (<= 0.505); box/triangle/exponential committed > 0.55.")
print(f"  {'pulse':<22}{'Dx*Dk (point)':>15}{'Dx*Dk (cell)':>15}   verdict vs gates")
rows = [("gauss sigma=3",   gauss(3)), ("gauss sigma=5",  gauss(5)),
        ("gauss sigma=20",  gauss(20)),("gauss sigma=100",gauss(100)),
        ("box W=64",        box(64)),  ("triangle W=64",  tri(64)),
        ("exponential s=16",expo(16))]
p1a_ok, sat_ok = True, True
for name, f in rows:
    pp,_,_ = product(f, False); pc,_,_ = product(f, True)
    if pp < 0.495: p1a_ok = False
    note = ""
    if name.startswith("gauss"):
        note = "saturates" if pp <= 0.505 else "DOES NOT SATURATE (gate!)"
        if pp > 0.505: sat_ok = False
    else:
        note = ">0.55 ok" if pp > 0.55 else f"non-saturating ({pp:.3f}>0.505) but under committed 0.55 — gate mis-set, logged as-is"
    print(f"  {name:<22}{pp:>15.4f}{pc:>15.4f}   {note}")
print(f"  gate P1a floor(0.495): {'PASS' if p1a_ok else 'FAIL'} · Gaussian saturation: {'PASS' if sat_ok else 'FAIL'}")

print("\n  PHASE 1b — lattice-scale probe (pre-registered danger case).")
print("  Point definition first; pre-registered pivot = finite-extent cell definition (+a^2/12).")
print(f"  {'pulse':<22}{'Dx*Dk (point)':>15}{'Dx*Dk (cell)':>15}")
p1b_cell_ok = True
for name, f in [("single site (delta)", delta()), ("two-site [1,1]", twosite()),
                ("gauss sigma=0.3", gauss(0.3)), ("gauss sigma=0.5", gauss(0.5)),
                ("gauss sigma=1.0", gauss(1.0))]:
    pp,_,_ = product(f, False); pc,_,_ = product(f, True)
    if pc < 0.49: p1b_cell_ok = False
    print(f"  {name:<22}{pp:>15.4f}{pc:>15.4f}")
print("  point definition: sub-site pulses BEAT 1/2 (expected, pre-registered) — a point-")
print("  lattice has no floor at the cutoff. Pivot (pre-registered, not retro): the spation")
print("  has finite extent a; a one-cell pulse then has Dx >= a/sqrt(12).")
print(f"  gate P1b (cell definition, min >= 0.49): {'PASS — floor survives at the cutoff' if p1b_cell_ok else 'FAIL — thesis dead (no third definition permitted)'}")

print("\n  PHASE 2 — where hbar enters (provenance, no computation):")
print("  * everything above is dimensionless machinery: Dx*Dk >= 1/2 for real energy-")
print("    weighted lattice pulses. No hbar was used.")
print("  * the k->p bridge: FD02 measured circulation kappa = h/m (OBSERVED anchor,")
print("    0.02%) + substrate phase-gradient kinematics (superfluid substrate: local")
print("    flow v = (kappa/2pi) * grad(phase)) => k = m*v/hbar => Dp = hbar*Dk")
print("    => Dx*Dp >= hbar/2.")
print("  * FLAGGED BORROW (caps grade at C): the identity v=(kappa/2pi)grad(phase) is the")
print("    substrate model's kinematic postulate, not yet derived from tick mechanics.")
print("    hbar itself arrives as a MEASURED anchor (via kappa), never as a commutator.")

print("\n  PHASE 3 — spreading packet: NOT RUN (pre-declared OPEN). The wake dispersion")
print("  law is the ROOT-SIM core, unavailable; running it with an imported dispersion")
print("  would fake the result. OPEN, owed to the same k->p closure as Phase 2.")

print("\n  PHASE 4 — same theorem on the time axis (real signals, ticks).")
T = 65536
t  = np.arange(T)
om = 2*np.pi*np.fft.fftfreq(T, d=1.0)
# Gaussian-in-time pulse
st = 300.0
g  = np.exp(-(t-T//2)**2/(4.0*st*st))
wg = g*g; wg/=wg.sum(); tb=(wg*t).sum(); vt=(wg*(t-tb)**2).sum()
G  = np.fft.fft(g); ww=np.abs(G)**2; ww/=ww.sum(); ob=(ww*om).sum(); vo=(ww*(om-ob)**2).sum()
ptime = np.sqrt(vt*vo)
print(f"  Gaussian-in-time:  Dt*Dw = {ptime:.4f}  (gate <= 0.505: {'PASS' if ptime<=0.505 else 'FAIL'})")
# damped 'emission' pulse: amplitude e^(-t/2tau) -> energy e^(-t/tau)
tau = 200.0
d   = np.exp(-t/(2*tau)); d[0]*=1.0
wd  = d*d; wd/=wd.sum(); tb=(wd*t).sum(); vt=(wd*(t-tb)**2).sum()
Dt  = np.sqrt(vt)
D   = np.fft.fft(d); wS = np.abs(D)**2
half = wS.max()/2
# FWHM by interpolation around the peak at om=0
idx = np.argsort(om); oms, S = om[idx], wS[idx]
above = S >= half
lo = oms[above][0]; hi = oms[above][-1]
# refine by linear interpolation at both crossings
def cross(oarr, sarr, side):
    ii = np.where(sarr >= half)[0]
    j = ii[0] if side=="lo" else ii[-1]
    j2 = j-1 if side=="lo" else j+1
    o1,o2,s1,s2 = oarr[j2],oarr[j],sarr[j2],sarr[j]
    return o1 + (half-s1)*(o2-o1)/(s2-s1)
fwhm = cross(oms,S,"hi") - cross(oms,S,"lo")
vo_d = ( (wS/wS.sum()) * (om-( (wS/wS.sum())*om ).sum())**2 ).sum()
print(f"  damped emission (tau={tau:.0f} ticks): Dt = {Dt:.1f} (analytic tau = {tau:.0f})")
print(f"    spectral FWHM = {fwhm:.6f}  vs 1/tau = {1/tau:.6f}  ratio = {fwhm*tau:.4f}"
      f"  (gate |ratio-1|<=0.02: {'PASS' if abs(fwhm*tau-1)<=0.02 else 'FAIL'})")
print(f"    variance-based Dw = {np.sqrt(vo_d):.4f} — cutoff-dominated (diverges in the")
print(f"    continuum; slow spectral tails). The honest width of a damped pulse is the FWHM.")
print("  -> Gamma = hbar/tau follows ONLY after the same single Phase-2 bridge (E = hbar*w),")
print("     i.e. the QM06 linewidth inherits exactly one borrow, in one place.")

print("\n  SUMMARY:")
print("  * the 1/2 floor is a property of real energy-weighted pulses on the lattice —")
print("    classical bandwidth machinery, derived with no quantum object anywhere;")
print("  * at the spation scale the floor survives ONLY because a spation has finite")
print("    extent (cell term a^2/12): granularity itself enforces the floor at the cutoff;")
print("  * the lattice fingerprint: floor = 1/2*(1 + O(a^2/Dx^2)) — at lab scales")
print("    (Dx ~ 1e-10 m, a = lP ~ 1.6e-35 m) the correction is ~1e-50: real but beyond")
print("    any measurement. Honest status: prediction, unfalsifiable at current precision;")
print("  * hbar enters ONCE (k->p bridge via measured kappa=h/m + substrate kinematics).")
print("    'Uncertainty' is wake bandwidth; the vortex keeps sharp (x,p) at every tick.")
print("  * SCOPE (FLM14 ADJ-7 two-channel doctrine): this floor binds the PULSE channel")
print("    only (real wake pulses at c). The geared CONSTRAINT channel (phase constraint")
print("    through gear-locked clusters, uncapped) carries no pulse bandwidth and is NOT")
print("    bound by this theorem. No statement about it is made here.")
print("="*78)
