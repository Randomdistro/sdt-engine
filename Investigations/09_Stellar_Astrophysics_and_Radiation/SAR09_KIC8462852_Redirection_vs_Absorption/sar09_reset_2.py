# SAR09 Round 2, Q3 spin-phase coherence (2026-10-14). Registration: SAR09_RESET_ASSESSMENT_2026-10-14.md sections 0-3 (written before this file existed).
# Run:  python -I sar09_reset_2.py
# Author: J. C. Harvey, Melbourne.
import glob, sys, math
import numpy as np
from astropy.io import fits
from astropy.timeseries import LombScargle
from scipy.ndimage import median_filter, minimum_filter1d, uniform_filter1d
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
rng = np.random.default_rng(20261014)

DT = 29.4244 / 1440.0          # Kepler long cadence [d]
WIN = int(round(3.0 / DT)) | 1  # 3.0 d window as an odd cadence count (147)
HALF = int(round(0.22 / DT))    # +-0.22 d
TH = 3.0

def load():
    segs = []
    for p in sorted(glob.glob(r'C:\sdt-data\kic8462852\kplr008462852-*_llc.fits')):
        d = fits.open(p)[1].data; t = d['TIME']; f = d['PDCSAP_FLUX']; m = np.isfinite(t) & np.isfinite(f)
        t = t[m]; f = f[m] / np.median(f[m])
        cut = np.where(np.diff(t) > 0.5)[0] + 1
        for a, b in zip(np.r_[0, cut], np.r_[cut, len(t)]):
            if b - a > 2 * WIN: segs.append((t[a:b], f[a:b]))
    return segs

def envelope(segs):
    return [median_filter(f, size=WIN, mode='nearest') for t, f in segs]

def smooth(x): return uniform_filter1d(x, 3, mode='nearest')

def pipeline(segs, P=None, quiet=False):
    """returns dict with period, minima phases for D and O, sigma_O, counts"""
    Es = envelope(segs); T = []; F = []; E = []; R = []; RS = []; MIN = []
    for (t, f), e in zip(segs, Es):
        r = f / e - 1.0; rs = smooth(r)
        ismin = rs == minimum_filter1d(rs, size=2 * HALF + 1, mode='nearest')
        T.append(t); F.append(f); E.append(e); R.append(r); RS.append(rs); MIN.append(ismin)
    T = np.concatenate(T); F = np.concatenate(F); E = np.concatenate(E); R = np.concatenate(R); RS = np.concatenate(RS); MIN = np.concatenate(MIN)
    O = (E >= 0.995) & (F >= 0.99); D = E < 0.99
    sigO = 1.4826 * np.median(np.abs(RS[O] - np.median(RS[O])))
    if P is None:
        grid = np.arange(0.80, 0.96, 2e-6); pw = LombScargle(T[O], F[O]).power(grid, method='fast'); i = int(np.argmax(pw))
        if 0 < i < len(grid) - 1:
            y0, y1, y2 = np.log(pw[i - 1:i + 2]); P = grid[i] + 2e-6 * 0.5 * (y0 - y2) / (y0 - 2 * y1 + y2)
        else: P = grid[i]
    selD = MIN & D & (RS <= -TH * sigO); selO = MIN & O & (RS <= -TH * sigO)
    return dict(P=P, T=T, F=F, E=E, R=R, RS=RS, O=O, D=D, sigO=sigO, tD=T[selD], tO=T[selO], rD=R[D], phD=T[D], rO=R[O], phO=T[O])

def rayleigh(ph):
    n = len(ph)
    if n == 0: return 0, 0.0, 1.0, 0.0
    C = np.sum(np.cos(2 * np.pi * ph)); S = np.sum(np.sin(2 * np.pi * ph)); Rr = math.hypot(C, S); Rb = Rr / n; Z = Rr * Rr / n
    p = math.exp(math.sqrt(1 + 4 * n + 4 * (n * n - Rr * Rr)) - (1 + 2 * n)); return n, Z, min(p, 1.0), math.atan2(S, C) / (2 * math.pi)

def phases(t, P): return ((t - 2454833.0 * 0 - 131.5) / P) % 1.0     # arbitrary t0

def main():
    segs = load(); print('Kepler segments %d, cadences %d, window %d cadences (%.2f d), half-width %d cadences (%.3f d)' % (len(segs), sum(len(t) for t, f in segs), WIN, WIN * DT, HALF, HALF * DT))
    res = pipeline(segs); P = res['P']; T0 = res['T'].max() - res['T'].min()
    print('\n[V-A] rotation period from the quiet set: P = %.6f d (width ~ P^2/T = %.1e d), baseline %.1f d, quiet cadences %d, dip cadences %d -> %s' % (P, P * P / T0, T0, res['O'].sum(), res['D'].sum(), 'met' if abs(P - 0.88) <= 0.02 else 'NOT MET'))
    print('     sigma_O (robust, smoothed residual) = %.3e' % res['sigO'])
    nD, ZD, pD, mD = rayleigh(phases(res['tD'], P)); nO, ZO, pO, mO = rayleigh(phases(res['tO'], P))
    print('\n[G-Q3] minima in D (E<0.99, residual <= -3 sigma_O): n = %d, Z = %.3f, p = %.3e, mean phase %.4f' % (nD, ZD, pD, mD))
    print('[V-B] minima in O (rotation modulation alone):      n = %d, Z = %.3f, p = %.3e, mean phase %.4f -> %s' % (nO, ZO, pO, mO, 'met' if pO < 0.01 else 'NOT MET'))
    # V-E look-elsewhere: 200 trial periods
    trials = rng.uniform(0.70, 1.10, 4000); trials = trials[np.abs(trials - P) >= 0.01][:200]
    Zt = np.array([rayleigh(phases(res['tD'], pt))[1] for pt in trials]); frac = float(np.mean(Zt >= ZD))
    print('[V-E] trial periods %d in 0.70-1.10 d (|dP| >= 0.01): fraction with Z >= Z_obs = %.4f ; max trial Z %.3f' % (len(trials), frac, Zt.max()))
    # reported: offsets and amplitudes
    def fit(tt, rr):
        ph = phases(tt, P); A = np.c_[np.cos(2 * np.pi * ph), np.sin(2 * np.pi * ph), np.ones_like(ph)]; c, *_ = np.linalg.lstsq(A, rr, rcond=None); return math.hypot(c[0], c[1]), math.atan2(c[1], c[0]) / (2 * math.pi) % 1.0
    aD, phD = fit(res['phD'], res['rD']); aO, phO = fit(res['phO'], res['rO'])
    mean_def = float(np.mean(1 - res['E'][res['D']]))
    # bootstrap of the offset between D and O minima mean phases
    pd_ = phases(res['tD'], P); po_ = phases(res['tO'], P); offs = []
    for _ in range(1000):
        a = rng.choice(pd_, len(pd_)); b = rng.choice(po_, len(po_)); offs.append(((math.atan2(np.sin(2*np.pi*a).sum(), np.cos(2*np.pi*a).sum()) - math.atan2(np.sin(2*np.pi*b).sum(), np.cos(2*np.pi*b).sum())) / (2*math.pi) + 0.5) % 1.0 - 0.5)
    offs = np.array(offs); off = ((mD - mO) + 0.5) % 1.0 - 0.5
    print('\n[reported, not graded] sinusoid fit of the residual on the fold: A_D = %.3e (phase %.3f), A_O = %.3e (phase %.3f); A_D/A_O = %.3f against the covering-factor expectation 1 - mean deficit = %.3f' % (aD, phD, aO, phO, aD / aO, 1 - mean_def))
    print('                      minima mean-phase offset D - O = %+.4f cycles (95%% bootstrap %+.4f to %+.4f)' % (off, np.percentile(offs, 2.5), np.percentile(offs, 97.5)))
    # V-C planted, V-D null (synthetic on the real time stamps, real envelope as baseline)
    Es = envelope(segs); sig = res['sigO']
    def synth(amp):
        out = []
        for (t, f), e in zip(segs, Es):
            noise = rng.normal(0, 1.0, len(t)) * (sig * math.sqrt(3.0))      # unsmoothed sigma ~ sqrt(3) x smoothed (3-cadence boxcar)
            out.append((t, e * (1 + amp * np.cos(2 * np.pi * phases(t, P)) + noise)))
        return out
    pc = pipeline(synth(0.002), P=P); nC, ZC, pC, _ = rayleigh(phases(pc['tD'], P)); nC2, ZC2, pC2, _ = rayleigh(phases(pc['tO'], P))
    print('\n[V-C] planted 0.2%% sinusoid: D minima n = %d, Z = %.2f, p = %.2e ; O minima n = %d, p = %.2e -> %s' % (nC, ZC, pC, nC2, pC2, 'met' if pC < 1e-6 else 'NOT MET'))
    hits = 0; ns = []
    for k in range(200):
        pn = pipeline(synth(0.0), P=P); n_, Z_, p_, _ = rayleigh(phases(pn['tD'], P)); hits += p_ < 0.01; ns.append(n_)
    print('[V-D] null (noise only, 200 realisations): fraction with p < 0.01 = %.3f ; median D minima n = %d -> %s' % (hits / 200, int(np.median(ns)), 'met' if hits / 200 <= 0.03 else 'NOT MET'))
    gate = (nD >= 20) and pD < 0.01 and frac < 0.01
    print('\n[verdict by the registered gate] n_D >= 20: %s ; p < 0.01: %s ; look-elsewhere fraction < 0.01: %s -> G-Q3 %s' % (nD >= 20, pD < 0.01, frac < 0.01, 'MET (coherent, not discriminating)' if gate else 'NOT MET'))

if __name__ == '__main__': main()
