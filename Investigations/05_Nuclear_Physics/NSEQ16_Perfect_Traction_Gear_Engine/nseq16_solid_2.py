# NSEQ16 strand-thickness and winding dependence of the solid pair test (2026-10-14). Registration: NSEQ16_RESET_ASSESSMENT_2026-10-14.md section 9.
# Run: python -I nseq16_solid_2.py        Author: J. C. Harvey, Melbourne.
import math, sys
import numpy as np
from scipy.spatial import cKDTree
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
R, A_ = 0.9987379362077577, 0.05042358791441983
TAU = 2 * math.pi
N = 4000

def curve(rho, turns):
    u = np.arange(N) * TAU / N
    phi = turns * u + rho
    rad = R + A_ * np.cos(phi); th = 4 * u
    return np.c_[rad * np.cos(th), rad * np.sin(th), A_ * np.sin(phi)]

def rotz(b): c, s = math.cos(b), math.sin(b); return np.array([[c, -s, 0], [s, c, 0], [0, 0, 1.0]])

G = 18
grid = np.arange(G) * TAU / G
Ds = np.round(np.arange(1.50, 2.2001, 0.05), 3)
print('NSEQ16 section 9: strand radius and winding dependence; N =', N, '; poses per D =', G ** 3)
for turns in (3, 5):
    PA = curve(0.0, turns); tree = cKDTree(PA)
    # strand spacing in the cross-section for this winding
    ph = np.array([0, 1, 2, 3]) * (turns * math.pi / 2)
    sp = min(math.dist((A_ * math.cos(p), A_ * math.sin(p)), (A_ * math.cos(q), A_ * math.sin(q))) for i, p in enumerate(ph) for q in ph[i + 1:] if abs(p - q) > 1e-9)
    print(f'\n== cross-section turns {turns}: nearest strand spacing a*sqrt2-type = {sp:.5f} R_p')
    curves = {rb: curve(rb, turns) for rb in grid}
    for s in (0.03565486, 0.02, 0.01, 0.005):
        twoS = 2 * s; tol = 0.004
        first = None; at2 = 0; counts = []
        for D in Ds:
            feas = 0
            for xi in grid:
                e = np.array([math.cos(xi), math.sin(xi), 0.0])
                for be in grid:
                    Rb = rotz(be).T
                    for rb in grid:
                        PB = curves[rb] @ Rb + D * e
                        if tree.query(PB)[0].min() >= twoS - tol: feas += 1
            counts.append((D, feas))
            if feas and first is None: first = D
            if abs(D - 2.0) < 1e-9: at2 = feas
            if first is not None and D >= 2.0 - 1e-9: break
        print(f'  s = {s:.5f}: analytic cable contact 2(R+a+s) = {2 * (R + A_ + s):.4f}; smallest D with a clear pose on this grid: {first if first else "none up to 2.20"}; clear poses at D = 2.000: {at2} of {G ** 3}; per D: ' + ' '.join(f'{d:.2f}:{f}' for d, f in counts if f or d >= 1.95))
