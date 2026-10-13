import json, numpy as np
from scipy.optimize import nnls
R = json.load(open('np41_kinds.json', encoding='utf-8'))
kinds = sorted({k for r in R for k in r['kinds']})
X = np.array([[r['kinds'].get(k, 0) for k in kinds] for r in R], float)
y = np.array([r['Bmeas'] for r in R]); A = np.array([r['A'] for r in R], float)
print('n', len(R), 'kinds', kinds, 'total counts per kind', X.sum(0).astype(int).tolist())
def fit(m):
    c, _ = nnls(X[m], y[m]); return c
def med(m, c): return float(np.median(np.abs(X[m] @ c - y[m]) / y[m]))
c = fit(np.ones(len(R), bool))
print('all-fit energy per kind (MeV):', dict(zip(kinds, np.round(c, 3))), ' median |resid| %.4f' % med(np.ones(len(R), bool), c))
lo, hi = A < 60, A >= 60
for name, tr, te in (('train A<60 -> test A>=60', lo, hi), ('train A>=60 -> test A<60', hi, lo)):
    c2 = fit(tr)
    print(name, 'energies', dict(zip(kinds, np.round(c2, 3))), ' train median %.4f  TEST median %.4f' % (med(tr, c2), med(te, c2)))
# interleaved split (odd/even index) for a fair generalisation check
idx = np.arange(len(R)); tr = idx % 2 == 0; te = ~tr
c3 = fit(tr); print('train even idx -> test odd idx: train %.4f TEST %.4f' % (med(tr, c3), med(te, c3)))
# scaling check of a single global per-contact energy
cc = np.array([r['kinds'] and sum(r['kinds'].values()) for r in R], float)
k1 = (cc * y).sum() / (cc ** 2).sum(); print('single energy per contact %.3f MeV: median |resid| %.4f' % (k1, float(np.median(np.abs(k1 * cc - y) / y))))
