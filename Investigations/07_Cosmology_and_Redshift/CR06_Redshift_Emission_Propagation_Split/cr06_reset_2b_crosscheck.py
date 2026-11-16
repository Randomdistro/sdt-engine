"""CR06 reframe run 2b (2026-10-09): independent second route for run 2 and a representation check. No gates.

Registered purposes (written before running):
 (1) Two-route verification: re-implement the profile fit independently of cr06_reset_2.cpp (numpy/scipy, dense-grid quadrature, scipy minimiser) on dataset A (40 bins, full covariance)
     and report chi2 and knot values for K = 1, 2, 3 beside the C++ values (K=1 47.412 / 0.663; K=2 38.921 / 0.395, 1.011; K=3 38.668 / 0.431, 0.682, 1.098).
 (2) Representation check: the distance function r~(z) of the fitted K = 2, 3 profiles against flat LCDM (Om fitted on the same data): offset-removed difference 5 log10(r_K / r_LCDM) at the 40 data redshifts (max and rms),
     in magnitudes, beside the bin errors.
 (3) Representability of the LCDM exponent function by the knot family: chi2 (offset refitted) of the K = 3 and K = 5 profiles with the knots set to LCDM's n_eff at the knot positions, against the fitted chi2.
 (4) Distance function of the LCDM comparator versus the K = 1 single power, same measure as (2).
Author: J. C. Harvey, Melbourne.
"""
import numpy as np
from scipy.optimize import minimize, minimize_scalar

ROOT = r"C:\Users\Jimmi\OneDrive\Desktop\sdt-engine"
DATA = ROOT + r"\Investigations\07_Cosmology_and_Redshift\CR06_Redshift_Emission_Propagation_Split\data\pantheon_binned_DS17f.txt"
COV = ROOT + r"\Datasets\cosmology\Pantheon_DS17f_binned_sys_covariance.txt"

rows = []
for line in open(DATA):
    if line.startswith("#") or not line.strip():
        continue
    t = line.split()
    rows.append((float(t[1]), float(t[4]), float(t[5])))
orig = np.array(rows)
order = np.argsort(orig[:, 0], kind="stable")
z, m, e = orig[order, 0], orig[order, 1], orig[order, 2]
n = len(z)
with open(COV) as f:
    nn = int(f.readline())
    S = np.array([float(v) for v in f.read().split()]).reshape(nn, nn)
C = S[np.ix_(order, order)] + np.diag(e ** 2)
Lc = np.linalg.cholesky(C)
u = np.linalg.solve(Lc, np.ones(n))
x = np.log1p(z)
xmax = x[-1]


def nprof(th, xx):
    K = len(th)
    if K == 1:
        return np.full_like(xx, th[0])
    t = xx / xmax * (K - 1)
    j = np.minimum(t.astype(int), K - 2)
    f = t - j
    th = np.asarray(th)
    return th[j] * (1 - f) + th[j + 1] * f


GRID = np.linspace(0, xmax, 400001)


def rtilde(th):
    f = np.exp((1 - nprof(th, GRID)) * GRID)
    cum = np.concatenate([[0], np.cumsum(0.5 * (f[1:] + f[:-1]) * np.diff(GRID))])
    return np.interp(x, GRID, cum)


def chi2_mu(mu):
    w = np.linalg.solve(Lc, m - mu)
    a = (u @ w) / (u @ u)
    return float(w @ w - (u @ w) ** 2 / (u @ u)), a


def chi2_prof(th):
    r = rtilde(th)
    if np.any(r <= 0):
        return 1e30
    return chi2_mu(5 * np.log10(r) + 5 * np.log10(1 + z))[0]


def fit(K):
    best = None
    for n0 in (0.3, 1.0, 2.0):
        res = minimize(chi2_prof, np.full(K, n0), method="Nelder-Mead", options=dict(xatol=1e-9, fatol=1e-12, maxiter=20000, maxfev=20000))
        res = minimize(chi2_prof, res.x, method="Nelder-Mead", options=dict(xatol=1e-10, fatol=1e-13, maxiter=20000, maxfev=20000))
        if best is None or res.fun < best.fun:
            best = res
    return best


def lcdm_r(Om, zz):
    zs = np.linspace(0, zz.max(), 200001)
    f = 1 / np.sqrt(Om * (1 + zs) ** 3 + 1 - Om)
    cum = np.concatenate([[0], np.cumsum(0.5 * (f[1:] + f[:-1]) * np.diff(zs))])
    return np.interp(zz, zs, cum)


def chi2_lcdm(Om):
    return chi2_mu(5 * np.log10(lcdm_r(Om, z)) + 5 * np.log10(1 + z))[0]


print("CR06 reframe run 2b (second route and representation check), dataset A: 40 bins, full covariance\n")
res_om = minimize_scalar(chi2_lcdm, bounds=(0.01, 0.99), method="bounded", options=dict(xatol=1e-8))
Om = res_om.x
print(f"[LCDM] Om = {Om:.4f}, chi2 = {res_om.fun:.3f}   (C++: 0.2963, 39.298)")
fits = {}
cpp = {1: (47.412, [0.663]), 2: (38.921, [0.395, 1.011]), 3: (38.668, [0.431, 0.682, 1.098])}
for K in (1, 2, 3):
    r = fit(K)
    fits[K] = r
    print(f"[ROUTE 2] K={K}: chi2 = {r.fun:.3f}, knots = {np.round(r.x, 3)}   (C++: chi2 {cpp[K][0]}, knots {cpp[K][1]})")

rl = lcdm_r(Om, z)
print("\n[REPRESENTATION] offset-removed distance-function difference 5 log10(r_model / r_LCDM) at the 40 redshifts (mag), beside the bin errors")
for K in (1, 2, 3):
    r = rtilde(fits[K].x)
    d = 5 * np.log10(r / rl)
    d = d - np.sum(d / e ** 2) / np.sum(1 / e ** 2)
    print(f"   K={K}: max |dmu| = {np.max(np.abs(d)):.4f} (at z = {z[np.argmax(np.abs(d))]:.3f}), rms = {np.sqrt(np.mean(d ** 2)):.4f}; median bin error {np.median(e):.3f}, error at z>1: {e[z > 1].round(3)}")
    print("        dmu at z = 0.1, 0.3, 0.5, 0.8, 1.0, 1.23, 1.61:", [round(float(np.interp(v, z, d)), 4) for v in (0.1, 0.3, 0.5, 0.8, 1.0, 1.2336, 1.6123)])

print("\n[REPRESENTABILITY] chi2 of the knot profile with knots set to LCDM's n_eff at the knot positions (offset refitted)")


def neff_lcdm_x(xx, Om_):
    """LCDM SECANT exponent n_sec(x) = ln E / x (the quantity the knot profile represents: dz/dr = (1+z)^n(x)); at x = 0 the limit 1.5 Om.
    [CORRECTION 2026-10-09: attempt 1 used the local slope 1.5 Om (1+z)^3/E^2 here, which is a different quantity for a varying exponent; output kept as cr06_reset_2b_results_attempt1_label_fault.txt.]"""
    xx = np.asarray(xx, dtype=float)
    zz = np.expm1(xx)
    E = np.sqrt(Om_ * (1 + zz) ** 3 + 1 - Om_)
    out = np.empty_like(xx)
    nz = xx > 0
    out[nz] = np.log(E[nz]) / xx[nz]
    out[~nz] = 1.5 * Om_
    return out


for K in (2, 3, 5, 9):
    kx = np.linspace(0, xmax, K)
    th = neff_lcdm_x(kx, Om)
    c = chi2_prof(th)
    # also with the knots refitted starting from the LCDM values
    r = minimize(chi2_prof, th, method="Nelder-Mead", options=dict(xatol=1e-9, fatol=1e-12, maxiter=40000, maxfev=40000))
    print(f"   K={K}: chi2 at LCDM knots = {c:.3f} ; refitted from there = {r.fun:.3f}  (LCDM itself {res_om.fun:.3f})")
