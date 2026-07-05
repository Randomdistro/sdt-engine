# ============================================================================
#  CH04 - Molecular Geometry from Wake Balance (no hybridisation, no targets in)
#  Author: J. C. Harvey, Melbourne - 2026-07-05
#  Machinery: N weighted unit directions, pairwise energy w_i w_j / |u_i - u_j|,
#  projected-gradient minimisation with random restarts. Angles are OUTPUT.
#  Gates committed in RUN_LOG.md before this file was written. Exit 0 iff all pass.
# ============================================================================
import math, random, sys

random.seed(20260705)

def norm(v):
    m = math.sqrt(sum(x * x for x in v))
    return [x / m for x in v]

def minimise(weights, restarts=60, iters=4000):
    n = len(weights)
    best_e, best_u = None, None
    for _ in range(restarts):
        u = [norm([random.gauss(0, 1) for _ in range(3)]) for _ in range(n)]
        eta = 0.1
        e_prev = energy(u, weights)
        for _ in range(iters):
            g = grad(u, weights)
            trial = []
            for i in range(n):
                gi = g[i]
                dot = sum(gi[k] * u[i][k] for k in range(3))
                gt = [gi[k] - dot * u[i][k] for k in range(3)]
                trial.append(norm([u[i][k] - eta * gt[k] for k in range(3)]))
            e_new = energy(trial, weights)
            if e_new < e_prev:
                u, e_prev = trial, e_new
                eta = min(eta * 1.05, 0.2)
            else:
                eta *= 0.5
                if eta < 1e-14: break
        if best_e is None or e_prev < best_e - 1e-12:
            best_e, best_u = e_prev, u
    return best_e, best_u

def energy(u, w):
    e = 0.0
    for i in range(len(u)):
        for j in range(i + 1, len(u)):
            d = math.sqrt(sum((u[i][k] - u[j][k]) ** 2 for k in range(3)))
            e += w[i] * w[j] / d
    return e

def grad(u, w):
    n = len(u)
    g = [[0.0, 0.0, 0.0] for _ in range(n)]
    for i in range(n):
        for j in range(i + 1, n):
            d = [u[i][k] - u[j][k] for k in range(3)]
            r = math.sqrt(sum(x * x for x in d))
            c = -w[i] * w[j] / r ** 3
            for k in range(3):
                g[i][k] += c * d[k]
                g[j][k] -= c * d[k]
    return g

def ang(a, b):
    return math.degrees(math.acos(max(-1, min(1, sum(a[k] * b[k] for k in range(3))))))

def pair_angles(u, idx):
    return sorted(ang(u[i], u[j]) for x, i in enumerate(idx) for j in idx[x + 1:])

fails = []
print("=" * 68)
print("  CH04 - Molecular Geometry from Wake Balance (minimiser output only)")
print("  Author: J. C. Harvey, Melbourne - 2026-07-05")
print("=" * 68)

# ---------------- P1: equal wakes ----------------
print("\nP1  EQUAL WAKES (all weights 1) - angles OUT of the minimiser")
targets = {2: [180.0], 3: [120.0], 4: [109.471], 6: [90.0]}
for n in (2, 3, 4, 5, 6):
    e, u = minimise([1.0] * n)
    angs = pair_angles(u, list(range(n)))
    if n == 5:
        s = ", ".join(f"{a:.2f}" for a in angs)
        tbp = all(any(abs(a - t) < 1.0 for t in (90.0, 120.0, 180.0)) for a in angs)
        print(f"    N=5: angle set [{s}]  TBP {{90,120,180}}: {'[PASS]' if tbp else '[FAIL]'}")
        if not tbp: fails.append("P1-N5")
    else:
        amin = angs[0]
        t = targets[n][0]
        ok = abs(amin - t) < 1.0
        print(f"    N={n}: min angle {amin:8.3f}  (ideal solid {t})  {'[PASS]' if ok else '[FAIL]'}")
        if not ok: fails.append(f"P1-N{n}")

# ---------------- P2: single lone/bond ratio scan ----------------
print("\nP2  LONE-PAIR LADDER - scan the ONE ratio w_L/w_B against NH3 + H2O jointly")
def bond_angle_AX(nb, nl, w):
    wts = [1.0] * nb + [w] * nl
    e, u = minimise(wts, restarts=30)
    bonds = list(range(nb))
    angs = pair_angles(u, bonds)
    return sum(angs) / len(angs)

best = None
for wi in range(100, 171, 2):
    w = wi / 100.0
    a3 = bond_angle_AX(3, 1, w)   # NH3
    a2 = bond_angle_AX(2, 2, w)   # H2O
    err = max(abs(a3 - 107.0), abs(a2 - 104.5))
    if best is None or err < best[0]:
        best = (err, w, a3, a2)
err, wstar, a3, a2 = best
print(f"    best single ratio w_L/w_B = {wstar:.2f}  [CALIBRATED(1)]")
print(f"    NH3 bond-bond = {a3:7.2f}  (measured 106.7-107.0)  err {a3-107.0:+.2f}")
print(f"    H2O bond-bond = {a2:7.2f}  (measured 104.5)        err {a2-104.5:+.2f}")
p2ok = abs(a3 - 107.0) <= 1.0 and abs(a2 - 104.5) <= 1.0
print(f"    committed gate (both within 1 deg, ONE ratio): {'[PASS]' if p2ok else '[FAIL]'}")
if not p2ok: fails.append("P2-ladder")
# CH4 check: all-equal AX4 is ratio-independent
e, u = minimise([1.0] * 4)
a4 = pair_angles(u, [0, 1, 2, 3])[0]
print(f"    CH4 (AX4, no lone): {a4:.2f} (measured 109.5) - ratio-independent")

# ---------------- P3: extended set, SAME ratio ----------------
print(f"\nP3  EXTENDED SET (same ratio {wstar:.2f}, no refit)")
# SF4: 4 bonds + 1 lone
e, u = minimise([1.0] * 4 + [wstar], restarts=40)
lb = sorted(ang(u[4], u[i]) for i in range(4))
bb = pair_angles(u, [0, 1, 2, 3])
seesaw = lb[0] < 100 and lb[3] > 110   # lone equatorial: two ~90 + two ~120 neighbours
print(f"    SF4 : lone-bond angles {['%.1f' % a for a in lb]} -> {'seesaw (lone equatorial) [PASS]' if seesaw else 'NOT seesaw [FAIL]'}")
print(f"          bond-bond {['%.1f' % a for a in bb]} (measured: eq-eq 101.6, ax-ax 173)")
if not seesaw: fails.append("P3-SF4")
# ClF3: 3 bonds + 2 lones
e, u = minimise([1.0] * 3 + [wstar] * 2, restarts=40)
ll = ang(u[3], u[4])
bb = pair_angles(u, [0, 1, 2])
tshape = ll > 100 and bb[0] < 100  # lones spread equatorial, T-shaped bonds
print(f"    ClF3: lone-lone {ll:.1f}, bond-bond {['%.1f' % a for a in bb]} -> {'T-shape [PASS]' if tshape else 'NOT T-shape [FAIL]'} (measured F-Cl-F 87.5)")
if not tshape: fails.append("P3-ClF3")
# XeF4: 4 bonds + 2 lones
e, u = minimise([1.0] * 4 + [wstar] * 2, restarts=40)
ll = ang(u[4], u[5])
bb = pair_angles(u, [0, 1, 2, 3])
sq = ll > 170 and abs(bb[0] - 90) < 3
print(f"    XeF4: lone-lone {ll:.1f} (trans?), bond-bond min {bb[0]:.1f} -> {'square planar [PASS]' if sq else 'NOT square planar [FAIL]'}")
if not sq: fails.append("P3-XeF4")
# CO2: two double bonds (weight 2 each)
e, u = minimise([2.0, 2.0])
a = ang(u[0], u[1])
print(f"    CO2 : O=C=O {a:.2f} (measured 180) {'[PASS]' if abs(a-180) < 1 else '[FAIL]'}")
if abs(a - 180) >= 1: fails.append("P3-CO2")
# H2CO: C=O fat (2) + 2 C-H (1)
e, u = minimise([2.0, 1.0, 1.0], restarts=40)
hch = ang(u[1], u[2]); hco = ang(u[0], u[1])
opening = hch < 120.0 < hco
print(f"    H2CO: H-C-H {hch:.2f} (measured 116.5), H-C=O {hco:.2f} (measured 121.8) -> fat-wake opening {'[PASS]' if opening else '[FAIL]'}")
if not opening: fails.append("P3-H2CO")

# ---------------- P4: novel outliers, SAME ratio ----------------
print(f"\nP4  NOVEL OUTLIERS (same ratio {wstar:.2f} - the model has NO central-atom")
print("    dependence, so H2S/PH3 predict identically to H2O/NH3; committed honesty test)")
h2s = bond_angle_AX(2, 2, wstar)
ph3 = bond_angle_AX(3, 1, wstar)
e1, e2 = h2s - 92.1, ph3 - 93.5
print(f"    H2S predicted {h2s:7.2f} vs measured  92.1  -> miss {e1:+.2f} deg {'[PASS]' if abs(e1) <= 5 else '[FAIL >5deg: fit-only trigger fires]'}")
print(f"    PH3 predicted {ph3:7.2f} vs measured  93.5  -> miss {e2:+.2f} deg {'[PASS]' if abs(e2) <= 5 else '[FAIL >5deg: fit-only trigger fires]'}")
if abs(e1) > 5: fails.append("P4-H2S")
if abs(e2) > 5: fails.append("P4-PH3")

print("\n" + "=" * 68)
print("  CH04 SUMMARY")
print(f"  committed-gate failures: {fails if fails else 'none'}")
print(f"  Exit: {1 if fails else 0}")
print("=" * 68)
sys.exit(1 if fails else 0)
