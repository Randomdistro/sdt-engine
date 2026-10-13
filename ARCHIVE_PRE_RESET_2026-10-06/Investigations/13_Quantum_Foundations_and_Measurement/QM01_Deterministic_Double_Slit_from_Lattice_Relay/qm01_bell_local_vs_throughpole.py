"""
QM01 Phase-5 (the Bell scope memo) — CONCRETE.  J. C. Harvey, Melbourne, 2026-06-25.

Simulate the SDT split-pattern entanglement mechanism and MEASURE its CHSH, to locate exactly
where the non-locality must enter. This does NOT 'derive QM' — Bell's theorem forbids any local
model from exceeding S=2, so the value of the test is to make the gap a NUMBER and show which
readout rule sits on which side of Tsirelson (2√2).

The mechanism (Harvey): split ONE pattern (a vortex / emission) into two; both carry a shared
orientation λ — "turn one, turn all." Two analyzers at angles a, b each yield ±1. We compare two
readout rules, holding the SAME shared λ:

  (1) LOCAL       — each end reads its OWN analyzer locally from λ ("adjacently divergent
                    pathways through the flux"). A local hidden-variable model.
  (2) THROUGHPOLE — the shared phase is projected onto BOTH analyzers jointly (one object, two
                    ends — the non-local shared account that never terminates).

Outcome (guaranteed by Bell): (1) ≤ 2 ; the only way to reach QM's 2√2 is (2). The sim shows the
local mechanism SATURATES the classical bound (2.000) and the throughpole rule equals QM exactly.
No coefficient is fitted. CHSH photon-polarisation angles: a=0°, a'=45°, b=22.5°, b'=67.5°.
"""
import numpy as np, sys
try: sys.stdout.reconfigure(encoding='utf-8')        # Windows cp1252 chokes on √/→ otherwise
except Exception: pass
rng = np.random.default_rng(7)
N   = 3_000_000
deg = np.pi/180
a, ap, b, bp = 0*deg, 45*deg, 22.5*deg, 67.5*deg

lam = rng.uniform(0, np.pi, N)                       # the shared "one pattern" orientation

def local(x):                                        # each end reads its analyzer locally from λ
    return np.where(np.cos(2*(x - lam)) >= 0, 1.0, -1.0)

E_local = lambda x, y: float(np.mean(local(x)*local(y)))   # measured correlation, local readout
E_tp    = lambda x, y: float(np.cos(2*(x - y)))            # throughpole: shared phase, both ends
chsh    = lambda E: E(a,b) - E(a,bp) + E(ap,b) + E(ap,bp)

S_loc, S_tp = chsh(E_local), chsh(E_tp)
print("="*70)
print("  QM01 — BELL CHSH on the SDT split-pattern mechanism")
print("="*70)
print(f"  (1) LOCAL split-pattern   (Monte-Carlo, N={N:,})   S = {S_loc:+.4f}")
print(f"  (2) THROUGHPOLE / shared account                   S = {S_tp:+.4f}")
print(f"      ---- references ----")
print(f"      classical / local-hidden-variable Bell ceiling S = 2.0000")
print(f"      quantum mechanics (Tsirelson, 2√2)             S = {2*np.sqrt(2):.4f}")
print(f"      experiment (loophole-free Bell, 2015)          S ≈ 2.40")
print("\n  E(θ) correlation vs analyzer-angle difference θ:")
print("    θ(deg)    LOCAL (sim)    THROUGHPOLE = QM")
for th in [0, 22.5, 45, 67.5, 90]:
    print(f"    {th:6.1f}     {E_local(0.0, th*deg):+.3f}        {E_tp(0.0, th*deg):+.3f}")
print("\n  VERDICT (honest, not plugged):")
print("  * the LOCAL mechanism hits S = 2.000 — the classical ceiling, EXACTLY. Even the best")
print("    local 'adjacently-divergent-pathways' readout cannot exceed it (Bell).")
print("  * QM needs 2.828; experiment shows 2.40 > 2 -> the world is NOT locally causal.")
print("  * therefore SDT entanglement reaches QM IFF the shared phase is read non-locally —")
print("    the THROUGHPOLE. Local readout => SDT predicts SUB-quantum correlations (falsified).")
print("  * the c-relay still bounds any SIGNAL at c, so the throughpole correlates but cannot")
print("    transmit: non-local in structure, local in dynamics. That is the QM01 Bell debt,")
print("    now a number: the gap to pay is 2.828 − 2.000 = 0.828, and it lives in the throughpole.")
print("="*70)
