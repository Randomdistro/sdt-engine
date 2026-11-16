import json, numpy as np
d = json.load(open('np41_residual_map.json', encoding='utf-8'))
R = d['rows']
print('built', d['n'], 'failed/non-finite', len(d['bad']), d['bad'][:10])
A = np.array([r['A'] for r in R], float); Z = np.array([r['Z'] for r in R], float)
Bm = np.array([r['Bmeas'] for r in R]); Bc = np.array([r['Bcalc'] for r in R]); deg = np.array([r['maxdeg'] for r in R], float)
ratio = Bc / Bm; r = (Bc - Bm) / Bm
print('B_calc/B_meas: median %.3f  IQR %.3f-%.3f  min %.3f  max %.3f' % (np.median(ratio), *np.percentile(ratio, [25, 75]), ratio.min(), ratio.max()))
# R^2 of B_calc/A against B_meas/A (same definition as the NP24 null)
y = Bm / A; yh = Bc / A
r2 = 1 - ((y - yh) ** 2).sum() / ((y - y.mean()) ** 2).sum()
r2_tot = 1 - ((Bm - Bc) ** 2).sum() / ((Bm - Bm.mean()) ** 2).sum()
print('R2 (BE/A) = %.3f   R2 (total BE) = %.3f   [NP24 shadow-overlap null: BE/A -12.2, total 0.988 (non-reproduction 0.510)]' % (r2, r2_tot))
# rank agreement, scale-free
from scipy.stats import spearmanr, pearsonr
print('Spearman(B_calc,B_meas)=%.4f  Spearman(B_calc/A,B_meas/A)=%.4f' % (spearmanr(Bc, Bm)[0], spearmanr(yh, y)[0]))
for lo, hi in ((2, 20), (20, 60), (60, 120), (120, 200), (200, 260)):
    m = (A >= lo) & (A < hi)
    if m.sum(): print('  A %3d-%3d n=%3d  median B_calc/B_meas %.3f' % (lo, hi, m.sum(), np.median(ratio[m])))
print('corr(ratio, A)=%.3f  corr(ratio, max degree)=%.3f  corr(ratio, Z/A)=%.3f' % (pearsonr(ratio, A)[0], pearsonr(ratio, deg)[0], pearsonr(ratio, Z / A)[0]))
# does a single scale factor remove the residual? (diagnostic only, NOT a registered law)
k = (Bm * Bc).sum() / (Bc ** 2).sum()
print('diagnostic: best single scale k=%.3f -> median |residual| %.3f (not a model; would be CALIBRATED(1))' % (k, np.median(np.abs(k * Bc - Bm) / Bm)))
