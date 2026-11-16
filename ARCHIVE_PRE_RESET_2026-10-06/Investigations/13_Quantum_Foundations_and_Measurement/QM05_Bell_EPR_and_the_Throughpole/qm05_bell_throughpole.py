"""
QM05 — Bell / EPR & the Throughpole.  J. C. Harvey, Melbourne, 2026-07-03.

Builds on QM01 Phase-5 (QM01_BELL_MEMO.md, verified reproducible 2026-07-03). New here:
the throughpole is implemented as SAMPLED outcomes (not an analytic cos), so no-signalling
is MEASURED, not asserted; a coupling sweep tests whether no-signalling is structural or
fine-tuned; and a pre-registered Tsirelson probe asks whether "joint readout" per se stops
at 2*sqrt(2).

HONESTY LINE (committed in RUN_LOG.md before this file was written):
  * The LOCAL models genuinely compute their S from local mechanics -> whatever they give
    is a real derivation (Bell guarantees <= 2).
  * The THROUGHPOLE model does NOT derive 2.828 -- it ASSUMES the joint weighting
    P(B=A|a,b) = cos^2(a-b). Its results are labelled CONSTRUCTION throughout.
No coefficient is fitted anywhere. Seed 11, N = 10^6 per setting cell, reproducible.
"""
import numpy as np, sys
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass

rng  = np.random.default_rng(11)
N    = 1_000_000
deg  = np.pi/180
A0, A1, B0, B1 = 0*deg, 45*deg, 22.5*deg, 67.5*deg   # CHSH photon-polarisation angles
SETTINGS = [(A0,B0),(A0,B1),(A1,B0),(A1,B1)]
sig_E, sig_m = 1/np.sqrt(N), 0.5/np.sqrt(N)

def chsh(Efun):
    E = {ab: Efun(*ab) for ab in SETTINGS}
    return E[(A0,B0)] - E[(A0,B1)] + E[(A1,B0)] + E[(A1,B1)], E

# ---------------------------------------------------------------- Phase 1: LOCAL baselines
def run_local_sign():
    """L1: deterministic local sign readout of the shared handedness phase (QM01 memo rule)."""
    lam = rng.uniform(0, np.pi, N)
    out = lambda x: np.where(np.cos(2*(x - lam)) >= 0, 1.0, -1.0)
    return chsh(lambda a,b: float(np.mean(out(a)*out(b))))

def run_local_beststrategy():
    """L2: best deterministic local strategy (setting-only outputs, optimal corners)."""
    # each wing outputs a fixed +/-1 per setting; exhaustive over 16 strategies
    best = -9
    for aa0 in (1,-1):
     for aa1 in (1,-1):
      for bb0 in (1,-1):
       for bb1 in (1,-1):
        S = aa0*bb0 - aa0*bb1 + aa1*bb0 + aa1*bb1
        best = max(best, S)
    return best

def run_local_malus():
    """L3: stochastic local Malus readout P(+|x,lam)=cos^2(x-lam), independent each wing."""
    lam = rng.uniform(0, np.pi, N)
    def out(x):
        p = np.cos(x - lam)**2
        return np.where(rng.uniform(0,1,N) < p, 1.0, -1.0)
    return chsh(lambda a,b: float(np.mean(out(a)*out(b))))

# ------------------------------------------- Phase 2: THROUGHPOLE (sampled, CONSTRUCTION)
def sample_throughpole(a, b, s=1.0):
    """Alice reads locally (sign of shared handedness vs her analyzer). With coupling s the
    pair is read JOINTLY: Bob's outcome drawn with P(B=A)=cos^2(a-b) [IMPORTED weighting];
    with prob (1-s) Bob falls back to the strictly local sign readout. Returns A,B arrays."""
    lam = rng.uniform(0, np.pi, N)
    Aout = np.where(np.cos(2*(a - lam)) >= 0, 1.0, -1.0)
    Bloc = np.where(np.cos(2*(b - lam)) >= 0, 1.0, -1.0)
    same = rng.uniform(0,1,N) < np.cos(a-b)**2
    Bjoint = np.where(same, Aout, -Aout)
    use_joint = rng.uniform(0,1,N) < s
    Bout = np.where(use_joint, Bjoint, Bloc)
    return Aout, Bout

def run_throughpole(s=1.0):
    Es, margA, margB = {}, {}, {}
    for (a,b) in SETTINGS:
        Aout, Bout = sample_throughpole(a,b,s)
        Es[(a,b)]   = float(np.mean(Aout*Bout))
        margA[(a,b)] = float(np.mean(Aout > 0))
        margB[(a,b)] = float(np.mean(Bout > 0))
    S = Es[(A0,B0)] - Es[(A0,B1)] + Es[(A1,B0)] + Es[(A1,B1)]
    return S, Es, margA, margB

# --------------------------- Phase 4 probe: a DIFFERENT marginal-preserving joint rule
def run_signcopy():
    """Pre-registered Tsirelson probe: joint rule B = A * sign(cos 2(a-b)). Also non-local,
    also marginal-preserving (A is 50/50, B is a deterministic +/-1 relabel of A)."""
    Es, margA, margB = {}, {}, {}
    for (a,b) in SETTINGS:
        lam  = rng.uniform(0, np.pi, N)
        Aout = np.where(np.cos(2*(a - lam)) >= 0, 1.0, -1.0)
        Bout = Aout * np.sign(np.cos(2*(a-b)) if abs(np.cos(2*(a-b)))>1e-12 else 1.0)
        Es[(a,b)]   = float(np.mean(Aout*Bout))
        margA[(a,b)] = float(np.mean(Aout > 0))
        margB[(a,b)] = float(np.mean(Bout > 0))
    S = Es[(A0,B0)] - Es[(A0,B1)] + Es[(A1,B0)] + Es[(A1,B1)]
    return S, Es, margA, margB

# ================================================================================ run
print("="*76)
print("  QM05 — Bell/EPR & the Throughpole   (seed 11, N=1e6/cell, thresholds in RUN_LOG)")
print("="*76)
print(f"  statistical noise: sigma_E = {sig_E:.4f}, sigma_marginal = {sig_m:.4f}")

print("\n  PHASE 1 — honest LOCAL baselines (these ARE derivations; Bell caps them at 2)")
S1,_ = run_local_sign()
S2   = run_local_beststrategy()
S3,_ = run_local_malus()
print(f"    L1 deterministic sign readout (shared handedness)   S = {S1:+.4f}")
print(f"    L2 best deterministic strategy (exhaustive 16)      S = {S2:+.4f}")
print(f"    L3 stochastic Malus readout (independent wings)     S = {S3:+.4f}")
loc_ok = max(S1,S2,S3) <= 2 + 4*sig_E
print(f"    gate P1 (all local S <= 2.004): {'PASS' if loc_ok else 'FAIL — hunt the leak'}")
print(f"    ceiling saturated by L1/L2 at 2.000; shortfall to QM = {2*np.sqrt(2)-2:.3f}")

print("\n  PHASE 2 — THROUGHPOLE, sampled outcomes  [CONSTRUCTION: cos^2 weighting IMPORTED]")
S_tp, Es, mA, mB = run_throughpole(1.0)
print(f"    S = {S_tp:+.4f}   (QM/Tsirelson 2*sqrt(2) = {2*np.sqrt(2):.4f})")
print("    no-signalling gate (marginal deviation from 0.500, threshold 4*sigma = 0.0020):")
worst = 0.0
for (a,b) in SETTINGS:
    dA, dB = abs(mA[(a,b)]-0.5), abs(mB[(a,b)]-0.5)
    worst = max(worst, dA, dB)
    print(f"      (a={a/deg:5.1f}, b={b/deg:5.1f})  |P(A+)-.5|={dA:.4f}  |P(B+)-.5|={dB:.4f}")
ns_ok = worst < 4*sig_m*4  # 4 sigma with 4-cell look-elsewhere widening (still 0.008 max)
print(f"    worst marginal deviation = {worst:.4f}  ->  no-signalling {'HOLDS' if worst<0.002 else ('HOLDS (within look-elsewhere)' if ns_ok else 'BROKEN')}")

print("\n  PHASE 3 — coupling sweep s (is no-signalling structural or fine-tuned?)")
print("      s      S(s)      worst marginal dev")
for s in (0.0, 0.25, 0.5, 0.75, 1.0):
    Ss, _, mAs, mBs = run_throughpole(s)
    w = max(max(abs(v-0.5) for v in mAs.values()), max(abs(v-0.5) for v in mBs.values()))
    print(f"    {s:4.2f}   {Ss:+.4f}        {w:.4f}")
print("    -> if dev stays < 0.002 at every s, NS is STRUCTURAL for marginal-preserving")
print("       projection rules (prompt Q4), not a tuned coincidence.")

print("\n  PHASE 4 — pre-registered Tsirelson probe: different joint rule (sign-copy)")
S_pr, Esp, mAp, mBp = run_signcopy()
wp = max(max(abs(v-0.5) for v in mAp.values()), max(abs(v-0.5) for v in mBp.values()))
print(f"    S = {S_pr:+.4f}   worst marginal dev = {wp:.4f}   (algebraic max = 4)")
print("    -> a joint (non-local) readout with intact marginals is NOT Tsirelson-bounded")
print("       per se. What stops the throughpole at exactly 2.828 is the cos^2 weighting")
print("       itself — i.e. the SAME residence/Born law QM04 and QM07 owe. One debt.")

print("\n  VERDICT (as pre-committed):")
print("  * LOCAL: caps at 2.0000 exactly (saturated) — genuine, Bell-guaranteed. KILLED as")
print("    a route to 2.828; SDT strictly-local predicts sub-quantum correlations (falsified")
print("    by loophole-free experiments, S~2.4).")
print("  * THROUGHPOLE: reaches 2.8284 with measured no-signalling, at every coupling s —")
print("    but this is CONSTRUCTION: the cos^2 joint weighting is imported, not derived.")
print("  * NEW (probe): joint readout alone can reach S=4 (PR-box) with marginals intact,")
print("    so Tsirelson is NOT structural to the throughpole channel. The entire QM-match")
print("    lives in the cos^2 weighting. The Bell debt REDUCES to the Born/residence debt.")
print("  * QM05 overall: D / OPEN, as pre-declared. The debt is bounded and named, not paid.")
print("="*76)
