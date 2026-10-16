# NSEQ16 solid-body pair test (2026-10-14). Registration: NSEQ16_RESET_ASSESSMENT_2026-10-14.md section 8 (written before this file existed).
# Run: python -I nseq16_solid_1.py        Author: J. C. Harvey, Melbourne.
import math, sys, itertools
import numpy as np
from scipy.spatial import cKDTree
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
rng = np.random.default_rng(20261014)
R, A_, S = 0.9987379362077577, 0.05042358791441983, 0.03565486094604231   # engine h1Spec fractions of R_p
RP_FM = 0.8414
TAU = 2 * math.pi
N = 1500

def curve(rho, N=N):
    u = np.arange(N) * TAU / N
    phi = 3 * u + rho
    rad = R + A_ * np.cos(phi); th = 4 * u
    P = np.c_[rad * np.cos(th), rad * np.sin(th), A_ * np.sin(phi)]
    drad = -3 * A_ * np.sin(phi)
    T = np.c_[drad * np.cos(th) - rad * 4 * np.sin(th), drad * np.sin(th) + rad * 4 * np.cos(th), 3 * A_ * np.cos(phi)]
    return P, T, phi % TAU

def rotz(b): c, s = math.cos(b), math.sin(b); return np.array([[c, -s, 0], [s, c, 0], [0, 0, 1.0]])

print('GOM/NSEQ16 solid-body pair test; curve N =', N, '; tube radius s =', round(S, 5), '; 2s =', round(2 * S, 5))
# V1 curve length
Pf, Tf, _ = curve(0.0, 20000)
length = np.sum(np.linalg.norm(Tf, axis=1)) * TAU / 20000
print(f'[V1] curve length {length:.5f} R_p-units x {RP_FM} = {length * RP_FM:.5f} fm against engine pathLength 21.13515 fm -> {"met" if abs(length * RP_FM / 21.13515 - 1) < 1e-4 else "NOT MET"} (rel {abs(length * RP_FM / 21.13515 - 1):.2e})')
# V2 distance routine
PA, TA, FA = curve(0.0)
tree = cKDTree(PA)
far = tree.query(PA + np.array([10.0, 0, 0]))[0].min()
same = tree.query(PA)[0].min()
dev = 0.0
for _ in range(20):
    D, xi, be, rb = 1.6 + 0.6 * rng.random(), TAU * rng.random(), TAU * rng.random(), TAU * rng.random()
    PB, TB, FB = curve(rb); PBt = PB @ rotz(be).T + D * np.array([math.cos(xi), math.sin(xi), 0])
    d_tree = tree.query(PBt)[0].min()
    d_brute = np.sqrt(((PA[:, None, :] - PBt[None, :, :]) ** 2).sum(-1)).min()
    dev = max(dev, abs(d_tree - d_brute))
print(f'[V2] far copies: min distance {far:.5f} (copies shifted by 10 R_p, expect > 8); identical copies at D=0: {same:.1e} (expect 0); tree vs brute-force on 20 random configs: max difference {dev:.1e} -> {"met" if far > 8 and same < 1e-12 and dev < 1e-12 else "NOT MET"}')

# scan
G = 24
grid = np.arange(G) * TAU / G
Ds = np.round(np.arange(1.80, 2.2001, 0.04), 3)
if 2.0 not in Ds: Ds = np.sort(np.append(Ds, 2.0))
curves = {rb: curve(rb) for rb in grid}
geom = {}
for mirror in (False, True):
    m = np.diag([1, 1, -1.0]) if mirror else np.eye(3)
    geom[mirror] = {rb: (curves[rb][0] @ m.T, curves[rb][1] @ m.T, curves[rb][2]) for rb in grid}
twoS = 2 * S
results = {False: {}, True: {}}
for mirror in (False, True):
    for D in Ds:
        feas = 0; touching = []
        for xi in grid:
            e = np.array([math.cos(xi), math.sin(xi), 0.0])
            for be in grid:
                Rb = rotz(be).T
                for rb in grid:
                    P0, T0, F0 = geom[mirror][rb]
                    PB = P0 @ Rb + D * e
                    d, idx = tree.query(PB)
                    j = int(np.argmin(d)); dm = d[j]
                    if dm >= twoS - 0.007:
                        feas += 1
                        if dm <= twoS * 1.03 + 0.007:
                            touching.append((xi, be, rb, dm, j, int(idx[j])))
        results[mirror][D] = (feas, touching)
    print(f'[scan] B geometry {"mirror" if mirror else "same chirality"}: ' + ', '.join(f'D={D:.2f}:{results[mirror][D][0]}' for D in Ds) + f'  (non-overlapping configurations of {G**3})')

best = None
for mirror in (False, True):
    for D in Ds:
        if results[mirror][D][0] > 0:
            best = (mirror, D) if best is None or D < best[1] else best; break
print('\n[1] smallest D with any non-overlapping configuration: ' + (f'{best[1]:.2f} R_p ({"mirror" if best[0] else "same-chirality"} geometry); engine contact distance 2.00 R_p' if best else 'none in 1.80-2.20'))
for mirror in (False, True):
    f, t = results[mirror][2.0]
    print(f'[2] D = 2.000 R_p, {"mirror" if mirror else "same chirality"}: non-overlapping {f} of {G**3}; touching {len(t)}')
    # [3] phases and tangents at closest points
    cnt = 0; same_phase = 0; par = 0; anti = 0
    for (xi, be, rb, dm, j, i) in t:
        # recompute the pair for tangent info
        P0, T0, F0 = geom[mirror][rb]; Rb = rotz(be).T
        TB = T0 @ Rb; flowB = -TB[j]; flowA = TA[i]
        c = float(flowA @ flowB / (np.linalg.norm(flowA) * np.linalg.norm(flowB)))
        dphi = (FA[i] - ((F0[j]) % TAU) + math.pi) % TAU - math.pi
        cnt += 1; same_phase += abs(dphi) < 0.35; par += c > 0.9; anti += c < -0.9
    if cnt:
        print(f'[3]   touching configs analysed {cnt}: closest-point poloidal phases equal within 0.35 rad: {same_phase}; B reversed flow parallel to A flow (cos > 0.9): {par}; antiparallel (cos < -0.9): {anti}')
    else:
        print('[3]   no touching configurations at D = 2.000')
