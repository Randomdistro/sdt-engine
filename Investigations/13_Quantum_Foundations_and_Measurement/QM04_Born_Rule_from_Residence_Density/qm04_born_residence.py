"""
QM04 — Born Rule from Residence Density (analytically-earnable part).
J. C. Harvey, Melbourne, 2026-07-04.

MACHINERY ONLY / FIREWALLED: the field chain below contains ONLY real travelling carriers
cos(k*r - w*t). No cos^2, no |amp|^2, no probability is ever written into the field or the
steering. Energy is the TIME-AVERAGE of (total real displacement)^2 — classical elastic
machinery (Law I strain energy). The residence law itself (landing count ~ energy density)
is DEFERRED to FLM14 rule-form-4 (in flight); the pre-registered negative demo below shows
why it cannot be waved in. Thresholds pre-committed in RUN_LOG.md. Seed 31.
"""
import numpy as np, sys
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass
rng = np.random.default_rng(31)

lam = 1.0; k = 2*np.pi/lam; w = 2*np.pi          # c = 1
d, D = 10.0, 200.0                                # slit separation, screen distance
x  = np.linspace(-60, 60, 4001)                   # screen coordinate
ra = np.sqrt(D**2 + (x - d/2)**2)
rb = np.sqrt(D**2 + (x + d/2)**2)
Aa, Ab = 1/np.sqrt(ra), 1/np.sqrt(rb)             # real carrier amplitudes

print("="*78)
print("  QM04 — the square as elastic energy (earnable part) + the deferred residence law")
print("="*78)

print("\n  PHASE 1 — energy density of two summed REAL carriers (no cos^2 in the code)")
ts = np.linspace(0, 1, 400, endpoint=False)       # one period, time average
I  = np.zeros_like(x)
Ia = np.zeros_like(x); Ib = np.zeros_like(x)
for t in ts:
    ua = Aa*np.cos(k*ra - w*t)                    # the ONLY field objects: real carriers
    ub = Ab*np.cos(k*rb - w*t)
    I  += (ua+ub)**2; Ia += ua**2; Ib += ub**2
I, Ia, Ib = I/len(ts), Ia/len(ts), Ib/len(ts)
cross_meas = I - Ia - Ib
cross_ana  = Aa*Ab*np.cos(k*(ra-rb))              # analytic elastic cross-term (comparison only)
rms_cross = np.sqrt(np.mean((cross_meas-cross_ana)**2))/I.max()
print(f"  cross-term RMS vs Aa*Ab*cos(k dr): {rms_cross:.2e} of peak (gate <0.1%: "
      f"{'PASS' if rms_cross<1e-3 else 'FAIL'})")
I_ana = 0.5*Aa**2 + 0.5*Ab**2 + cross_ana
rms_I = np.sqrt(np.mean((I-I_ana)**2))/I.max()
print(f"  full fringe vs (envelope)*cos^2 form:  RMS = {rms_I:.2e} of peak (gate <0.1%: "
      f"{'PASS' if rms_I<1e-3 else 'FAIL'})")
sign_flips = np.sum(np.diff(np.sign(cross_meas)) != 0)
print(f"  interference minima are real: cross-term sign flips {sign_flips} times across the screen")
print("  -> the SQUARE (and the cos^2 fringe) EMERGES from time-averaging summed real")
print("     carriers: it is the stored energy of a superposed displacement field. Geometric,")
print("     not axiomatic. (This is also QM01's Phase-3 wave-summation core.)")

print("\n  PHASE 2-neg — pre-registered NEGATIVE: naive least-resistance steering != Born")
Np = 40_000
xw = rng.uniform(x[0], x[-1], Np)                 # uniform start, one walker at a time
dI = np.gradient(I, x)
for _ in range(600):                              # gradient-ascent steering (naive reading of
    g = np.interp(xw, x, dI)                      #  'go where the wake delivers most')
    xw = np.clip(xw + 0.05*np.sign(g), x[0], x[-1])
hist, edges = np.histogram(xw, bins=200, range=(x[0], x[-1]))
centers = 0.5*(edges[1:]+edges[:-1])
I_b = np.interp(centers, x, I); I_b /= I_b.sum()
h   = hist/hist.sum()
rms_res = np.sqrt(np.mean((h-I_b)**2))/I_b.max()
print(f"  landing histogram vs energy density: RMS = {rms_res:.1%} of peak "
      f"(pre-registered expectation >20%: {'CONFIRMED — naive steering FAILS' if rms_res>0.20 else 'NOT confirmed (report as found)'})")
print("  -> walkers pile onto fringe maxima (delta spikes), NOT onto the I(x) profile.")
print("     'Any least-resistance steering gives Born' is DEAD as a hand-wave. The residence")
print("     law is a SPECIFIC balance — owed, not generic. DEFERRED to FLM14 rule-form-4.")

print("\n  PHASE 3 — normalisation & positivity (structural, conditional on Phase 2)")
print(f"  count conservation: every walker lands exactly once -> sum(hist) = {hist.sum()} = N ✔")
print(f"  energy density >= 0 everywhere: min(I) = {I.min():.3e} >= 0 ✔")
print("  -> IF residence ~ energy density (the deferred law), then sum(P)=1 and P>=0 come")
print("     free from counting + elasticity: no probability axiom needed. Conditional earn.")

print("\n  PROMPT-Q1 ANSWER (honest): as of this run, residence ~ energy density is a TRADED")
print("  postulate (Born-for-equidistribution), not a theorem — and Phase 2-neg shows it is")
print("  not even generic. It becomes a theorem only if FLM14 rule-form-4 produces it from")
print("  tick mechanics. That is the RESIDENCE-LAW root, named and owed.")
print("="*78)
