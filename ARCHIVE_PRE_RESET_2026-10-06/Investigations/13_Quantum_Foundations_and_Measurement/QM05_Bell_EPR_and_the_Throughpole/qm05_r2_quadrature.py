# QM05 RUN 2 — the action/reaction quadrature split (ADJ-R2-1, committed before this file).
# Harvey's split: "2 out the back gives 2 forward." Model: ONE conserved unit kick per trial in
# doubled-angle director space; joint readout = LINEAR projection; g sampled at (1+E)/2.
# NO cos^2 anywhere (disclosure in ADJ: (1+cos2D)/2 == cos^2 D — provenance changes, numbers must anchor).
# Seed 13, N=1e6/cell, sigma_E ~ 0.001. J. C. Harvey directive, 2026-07-07.
import numpy as np
rng = np.random.default_rng(13)
N = 1_000_000
A0, A1 = 0.0, np.pi/4          # Alice settings (radians): 0, 45 deg
B0, B1 = np.pi/8, 3*np.pi/8    # Bob: 22.5, 67.5 deg
PAIRS = [(A0,B0),(A0,B1),(A1,B0),(A1,B1)]
SIGNS = [+1,-1,+1,+1]          # CHSH: E00 - E01 + E10 + E11

def alice_local(lam, a):
    # run-1's marginal-flat local sign rule: sign of cos 2(lam - a)
    return np.where(np.cos(2*(lam-a)) >= 0, 1, -1)

def joint_arm(E_of_pair, label, show_pairs=False):
    # Bob = A * g, g sampled with P(+)=(1+E)/2 per setting pair. Returns S, worst marginal dev.
    S = 0.0; worst = 0.0; rows=[]
    for (a,b),sgn in zip(PAIRS,SIGNS):
        lam = rng.uniform(0, np.pi, N)
        A = alice_local(lam, a)
        E = E_of_pair(a,b)
        g = np.where(rng.uniform(0,1,N) < (1+E)/2, 1, -1)
        B = A*g
        Em = np.mean(A*B)
        S += sgn*Em
        mA = abs(np.mean(A==1)-0.5); mB = abs(np.mean(B==1)-0.5)
        worst = max(worst, mA, mB)
        rows.append((np.degrees(a),np.degrees(b),Em,mA,mB))
    if show_pairs:
        for a,b,Em,mA,mB in rows:
            print(f"      (a={a:5.1f}, b={b:5.1f})  E = {Em:+.4f}   |dP(A)|={mA:.4f} |dP(B)|={mB:.4f}")
    return S, worst

print("="*92)
print(" QM05 RUN 2 - ACTION/REACTION QUADRATURE (ADJ-R2-1). One conserved unit kick, linear")
print(" projection readout in doubled-angle director space. Gates committed before code.")
print("="*92)

# ---- G-A: anchor — run-1 Phase-2 machinery (imported cos^2 weighting), must reproduce 2.8286
S_anchor, w_anchor = joint_arm(lambda a,b: 2*np.cos(a-b)**2 - 1, "anchor")  # run-1 P2: P(same)=cos^2(D) -> E=2cos^2(D)-1
# (first build had cos(2D)**2 -> cos(4D), S~0 - angle doubled before squaring; caught by G-A's own gate, fixed, logged)
print(f"\n  G-A anchor (run-1 P2 weighting): S = {S_anchor:+.4f}  (gate 2.8286 +- 0.005)"
      f"  worst marginal dev = {w_anchor:.4f}   -> {'PASS' if abs(S_anchor-2.8286)<=0.005 and w_anchor<0.002 else 'FAIL'}")

# ---- the vector theorem row (pure algebra, printed for the record)
u = lambda th: np.array([np.cos(th), np.sin(th)])
vec = u(2*(A0-B0)) - u(2*(A0-B1)) + u(2*(A1-B0)) + u(2*(A1-B1))
print(f"\n  vector theorem: |sum of CHSH director combos| = {np.linalg.norm(vec):.6f}  (2*sqrt(2) = {2*np.sqrt(2):.6f});"
      f"  direction = ({vec[0]:+.4f},{vec[1]:+.4f})")

# ---- G-1: conserved unit kick, scan psi over the circle
print("\n  G-1 conserved kick |k|=1, psi scan (S(psi) = k . vec predicted = 2sqrt2 cos psi):")
best_S, best_psi = -9, None
for psi_deg in range(0, 360, 15):
    psi = np.radians(psi_deg)
    E_fn = lambda a,b,ps=psi: np.cos(2*(a-b) - ps)     # linear projection of unit kick at psi
    S_psi, w_psi = joint_arm(E_fn, f"psi={psi_deg}")
    tag = ""
    if S_psi > best_S: best_S, best_psi, best_w = S_psi, psi_deg, w_psi
    if psi_deg % 45 == 0:
        print(f"      psi = {psi_deg:3d} deg   S = {S_psi:+.4f}   (predict {2*np.sqrt(2)*np.cos(psi):+.4f})   marg dev {w_psi:.4f}")
print(f"    max over scan: S = {best_S:+.4f} at psi = {best_psi} deg   worst marginal dev {best_w:.4f}")
print(f"    ceiling gate (max = 2sqrt2 +- 0.005, none above 2.8334): "
      f"{'PASS' if abs(best_S-2*np.sqrt(2))<=0.005 and best_S<2.8334 else 'FAIL'}")
print("    per-pair correlations at optimum (gate |E| = 1/sqrt2 = 0.7071 +- 0.005 each):")
S_opt, w_opt = joint_arm(lambda a,b: np.cos(2*(a-b) - np.radians(best_psi)), "opt", show_pairs=True)

# ---- G-2: conservation OFF — kick renewed per setting pair (each pair gets its own aligned unit kick)
print("\n  G-2 control - conservation OFF (per-pair kick renewal; the reaction-free limit):")
E_free = lambda a,b: np.sign(np.cos(2*(a-b))) * 1.0    # each pair: own kick, perfectly aligned -> |E|=1
S_free, w_free = joint_arm(E_free, "free", show_pairs=True)
print(f"    S = {S_free:+.4f}  (gate 4.000 +- 0.005)  worst marginal dev = {w_free:.4f}"
      f"   -> {'PASS' if abs(S_free-4.0)<=0.005 and w_free<0.002 else 'FAIL'}")

# ---- G-4: the x2 identity — independent Malus (run-1 L3) vs joint
print("\n  G-4 the x2 identity (independent Malus vs joint):")
S_m = 0.0
for (a,b),sgn in zip(PAIRS,SIGNS):
    lam = rng.uniform(0, np.pi, N)
    pA = np.cos(lam-a)**2; pB = np.cos(lam-b)**2      # Malus response at each wing INDEPENDENTLY
    A = np.where(rng.uniform(0,1,N) < pA, 1, -1)
    B = np.where(rng.uniform(0,1,N) < pB, 1, -1)
    S_m += sgn*np.mean(A*B)
ratio = best_S / S_m
print(f"    independent-Malus S = {S_m:+.4f} (run-1 L3: +1.4148)   joint S = {best_S:+.4f}"
      f"   ratio = {ratio:.4f}  (gate 2.000 +- 0.01) -> {'PASS' if abs(ratio-2.0)<=0.01 else 'FAIL'}")

# ---- overdraw row (report): S(|k|) linearity; |k|=sqrt2 is algebraic only
print("\n  overdraw row (report-only): S = 2sqrt2 * |k|;  |k|=sqrt2 -> S=4 needs per-pair |E|=1 at")
print("  FOUR pairs of ONE vector: impossible at unit norm (max projection sum = |vec| = 2sqrt2).")
for k in (0.5, 1/np.sqrt(2), 1.0):
    E_fn = lambda a,b,kk=k: kk*np.cos(2*(a-b))
    S_k, _ = joint_arm(E_fn, f"k={k}")
    print(f"      |k| = {k:.4f}   S = {S_k:+.4f}   (predict {2*np.sqrt(2)*k:+.4f})")
print(f"      |k| = {np.sqrt(2):.4f}   S = 4.0000 ALGEBRAIC ONLY - per-pair |E| = 1 at all four pairs of one")
print(f"      conserved vector is unrealisable: the PR box is an OVERDRAW (more forward than booked back).")

print("\n  VERDICT LINE: gates printed above; class per ADJ-R2-1 (NATIVE-conditional at best,")
print("  CONSTRUCTION if projection-cosine is judged an import); the new falsifiable content is")
print("  the CONSERVATION <-> CEILING link: |k|=1 -> Tsirelson; kick renewal -> 4; nothing between.")
