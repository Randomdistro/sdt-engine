#!/usr/bin/env python3
# ================================================================
# SAR09 — KIC 8462852: redirection vs absorption. THE INSTRUMENT.
# Pre-registration: PROMPT.md (committed before this file was written).
# Single pass, whole range, no per-event re-tuning. Direct execution.
# Data: C:\sdt-data\kic8462852\  (DATA_MANIFEST.md)
# ================================================================
import glob, os, re, math
import numpy as np
from astropy.io import fits
from astropy.timeseries import LombScargle

DATA = r"C:\sdt-data\kic8462852"
OUT  = []
def log(s=""):
    print(s); OUT.append(s)

# ── load + stitch all 18 Kepler quarters (PDCSAP, median-normalised) ──
t_all, f_all = [], []
for fn in sorted(glob.glob(os.path.join(DATA, "kplr*_llc.fits"))):
    with fits.open(fn) as h:
        d = h[1].data
        t, f = d["TIME"], d["PDCSAP_FLUX"]
        m = np.isfinite(t) & np.isfinite(f)
        t, f = t[m], f[m]
        if len(f) < 100: continue
        f = f / np.median(f)
        t_all.append(t); f_all.append(f)
t = np.concatenate(t_all); f = np.concatenate(f_all)
o = np.argsort(t); t, f = t[o], f[o]
log(f"[LOAD] stitched Kepler PDCSAP: {len(t)} cadences, BKJD {t[0]:.1f}–{t[-1]:.1f}")

# ══════════════ V1 — dip census recovery (validation gate) ══════════════
# published anchors (Boyajian 2015): D792 depth ~0.16 at BKJD~792.7;
# D1519 depth ~0.21 at BKJD~1519.6. Tolerances: depth ±15% rel, epoch ±1 d.
log("\n══ V1: DIP CENSUS RECOVERY ══")
dips = []
below = f < 0.95
i = 0
while i < len(f):
    if below[i]:
        j = i
        while j < len(f) and (below[j] or (j+5 < len(f) and np.min(f[j:j+5]) < 0.95)): j += 1
        seg = slice(max(0,i-2), min(len(f), j+2))
        k = seg.start + int(np.argmin(f[seg]))
        dips.append((t[k], 1-f[k]))
        i = j + 1
    else:
        i += 1
for ep, dp in dips: log(f"  dip: BKJD {ep:9.3f}  depth {100*dp:6.2f}%")
def check(ep0, dp0, tol_t=1.0, tol_rel=0.15):
    for ep, dp in dips:
        if abs(ep-ep0) <= tol_t and abs(dp-dp0)/dp0 <= tol_rel: return (ep, dp, True)
    near = min(dips, key=lambda x: abs(x[0]-ep0)) if dips else (float('nan'),)*2
    return (*near, False)
e1, d1, ok1 = check(792.7, 0.16)
e2, d2, ok2 = check(1519.6, 0.21)
log(f"  V1a D792 : found BKJD {e1:.3f} depth {100*d1:.2f}% vs published ~16%  -> {'PASS' if ok1 else 'FAIL'}")
log(f"  V1b D1519: found BKJD {e2:.3f} depth {100*d2:.2f}% vs published ~21%  -> {'PASS' if ok2 else 'FAIL'}")
V1 = ok1 and ok2

# ══════════════ V2 — rotation recovery (validation gate) ══════════════
log("\n══ V2: ROTATION RECOVERY ══")
qm = (t > 200) & (t < 380)          # a dip-free stretch
freq = np.linspace(1/2.0, 1/0.4, 20000)
pw = LombScargle(t[qm], f[qm]).power(freq)
P = 1/freq[int(np.argmax(pw))]
V2 = abs(P - 0.88) <= 0.02
log(f"  peak period {P:.4f} d vs published 0.88 d -> {'PASS' if V2 else 'FAIL'}")

# ══════════════ V3 + Q1 — the infrared ledger ══════════════
log("\n══ V3 + Q1: THE INFRARED LEDGER ══")
# photosphere model: blackbody T*=6750 K scaled to 2MASS J,H,Ks (measured);
# read W1..W4 predictions; V3 = W1,W2 within 3σ; Q1 = W3/W4 budget test.
h_,c_,kB = 6.62607015e-34, 2.99792458e8, 1.380649e-23
def Bnu(T, lam):
    nu = c_/lam
    return 2*h_*nu**3/c_**2/(np.expm1(h_*nu/(kB*T)))
Tstar = 6750.0
# zero points (Jy) and effective wavelengths (m)
bands = {  # name: (lam, F0_Jy, measured_mag, err)
 "J":(1.235e-6,1594.0,10.763,0.021), "H":(1.662e-6,1024.0,10.551,0.019), "Ks":(2.159e-6,666.8,10.499,0.020),
 "W1":(3.368e-6,309.54,10.425,0.023), "W2":(4.618e-6,171.79,10.436,0.020),
 "W3":(12.082e-6,31.674,10.591,0.123), "W4":(22.194e-6,8.363,9.423,None)}  # W4 = upper limit
def mag2Jy(name):
    lam,F0,m,e = bands[name]; return F0*10**(-m/2.5)
# scale factor from JHKs
scales = [mag2Jy(n)/(Bnu(Tstar,bands[n][0])) for n in ("J","H","Ks")]
A = float(np.mean(scales)); spread = float(np.std(scales)/np.mean(scales))
# ADJ-1 (instrument): a bare blackbody carries known band-dependent systematics
# for F stars (CO at 4.6 μm dims W2 below blackbody). Stated model floor of
# 0.08 mag added in quadrature to all band errors — quantified, not ignored.
MFLOOR = 0.08
log(f"  photosphere scale from JHKs: rel spread {100*spread:.1f}% · model floor {MFLOOR} mag (ADJ-1)")
V3 = True
for n in ("W1","W2","W3"):
    lam,F0,m,e = bands[n]
    pred = A*Bnu(Tstar,lam); meas = mag2Jy(n)
    dm = -2.5*math.log10(meas/pred)
    etot = math.hypot(e if e else 0.1, MFLOOR)
    sig = dm/etot
    log(f"  {n}: measured {meas*1e3:8.3f} mJy  photosphere {pred*1e3:8.3f} mJy  Δm {dm:+.3f} ({sig:+.1f}σ)")
    if n in ("W1","W2") and abs(sig) > 3: V3 = False
lam4,F04,m4,_ = bands["W4"]; pred4 = A*Bnu(Tstar,lam4); meas4 = mag2Jy("W4")
log(f"  W4: measured {meas4*1e3:8.3f} mJy (UPPER LIMIT)  photosphere {pred4*1e3:8.3f} mJy")
log(f"  V3 photosphere anchor (W1,W2 within 3σ): {'PASS' if V3 else 'FAIL'}")
# Q1 budget: steady screen absorbing f_abs of L*, re-emitting as blackbody T_d(r).
Lsun = 3.828e26; Lstar = 4.7*Lsun; d_pc = 443.6; d_m = d_pc*3.0857e16
sigma = 5.670374419e-8
f_abs = 0.03                        # the Kepler-mission secular deficit (Montet & Simon)
log(f"  budget: steady screen f_abs = {f_abs} of L* (the measured Kepler-era deficit)")
log(f"  {'r [AU]':>7} {'T_d [K]':>8} {'ΔW3 [mag]':>10} {'ΔW4 [mag]':>10}")
Q1_rows = []
for r_au in (0.1, 0.3, 1.0, 3.0, 10.0):
    Td = 278.0*(Lstar/Lsun)**0.25/math.sqrt(r_au)
    # ADJ-2 (instrument): dust term is SI [W/m²/Hz]; photosphere scale A·Bnu is in
    # Jy-derived units — convert dust flux density to Jy (÷1e-26) before comparing.
    add3 = f_abs*Lstar/(4*math.pi*d_m**2) * (math.pi*Bnu(Td,bands["W3"][0]))/(sigma*Td**4) / 1e-26
    add4 = f_abs*Lstar/(4*math.pi*d_m**2) * (math.pi*Bnu(Td,bands["W4"][0]))/(sigma*Td**4) / 1e-26
    dm3 = 2.5*math.log10(1 + add3/(A*Bnu(Tstar,bands["W3"][0])))
    dm4 = 2.5*math.log10(1 + add4/(A*Bnu(Tstar,bands["W4"][0])))
    Q1_rows.append((r_au, Td, dm3, dm4))
    log(f"  {r_au:7.1f} {Td:8.0f} {dm3:10.3f} {dm4:10.3f}")
# measured excess at W3 (Δm from photosphere) with its error:
lam3,F03,m3,e3 = bands["W3"]
excess_W3 = -2.5*math.log10(mag2Jy("W3")/(A*Bnu(Tstar,lam3)))
log(f"  measured W3 offset from photosphere: {excess_W3:+.3f} ± {e3:.3f} mag")

# ══════════════ Q3 — spin-phase coherence in the deep dips ══════════════
log("\n══ Q3: SPIN-PHASE COHERENCE ══")
Prot = P
def dip_power(t0, w=6.0):
    m = (t > t0-w) & (t < t0+w) & np.isfinite(f)
    tt, ff = t[m], f[m]
    if len(tt) < 100: return np.nan
    sm = np.interp(tt, tt[::8], np.convolve(ff, np.ones(25)/25, mode="same")[::8])
    res = ff - sm
    return float(LombScargle(tt, res).power(np.array([1/Prot]))[0])
p792  = dip_power(e1); p1519 = dip_power(e2)
# bootstrap threshold from 40 quiet windows
rng = np.random.default_rng(1519)
quiet = []
for _ in range(40):
    t0 = rng.uniform(t[0]+10, t[-1]-10)
    if abs(t0-e1) < 15 or abs(t0-e2) < 15: continue
    q = dip_power(t0)
    if np.isfinite(q): quiet.append(q)
thresh = float(np.percentile(quiet, 95))
log(f"  P_rot power in D792 window : {p792:.4f}")
log(f"  P_rot power in D1519 window: {p1519:.4f}")
log(f"  95th percentile of {len(quiet)} quiet windows: {thresh:.4f}")
coh = (p792 > thresh) and (p1519 > thresh)
log(f"  coherence in BOTH deep dips: {'YES — field-locked structure supported' if coh else 'NO — structure is exterior to the spin (field-locked variant excluded)'}")

# ══════════════ Q4 — brightening census (characterisation only) ══════════════
log("\n══ Q4: BRIGHTENING CENSUS (no gate) ══")
# long-window median detrend, then sustained > +0.1% excursions > 1 d
fs = f - np.interp(t, t[::40], np.array([np.median(f[max(0,i-200):i+200]) for i in range(0,len(f),40)]))
hi = fs > 0.001
count, i = 0, 0
while i < len(fs):
    if hi[i]:
        j = i
        while j < len(fs) and hi[j]: j += 1
        if t[min(j,len(t)-1)] - t[i] > 1.0: count += 1
        i = j
    else: i += 1
log(f"  sustained brightenings (+0.1%, >1 d): {count} — recorded, no verdict attached")

# ══════════════ Q2 — chromatic ratio variability (GTC, measured) ══════════════
log("\n══ Q2: CHROMATIC RATIO VARIABILITY (GTC per-pointing, single pass) ══")
gtc_tex = os.path.join(DATA, "papers", "src_1801.00720", "WTF_GTC_spectro.tex")
rows = []
pat = re.compile(r"&\s*(\d{5}\.\d+)\s*&([\d.]+)\$\\pm\$([\d.]+)&([\d.]+)\$\\pm\$([\d.]+)&([\d.]+)\$\\pm\$([\d.]+)&([\d.]+)\$\\pm\$([\d.]+)&([\d.]+)\$\\pm\$([\d.]+)")
excluded = ("57890.6940", "57986.6427")     # the paper's own two excluded pointings
for line in open(gtc_tex, encoding="utf-8", errors="ignore"):
    m = pat.search(line)
    if m:
        if m.group(1) in excluded: continue
        v = [float(x) for x in m.groups()]
        rows.append(v)
log(f"  GTC pointings parsed: {len(rows)} (paper's own exclusions honoured)")
# per pointing: A_556 = -2.5 log10(F556), A_868 likewise; ratio where A_556 > 3σ
ratios = []
for v in rows:
    bjd, F556, e556, _, _, _, _, _, _, F868, e868 = v
    A556 = -2.5*math.log10(F556); sA556 = 2.5/math.log(10)*e556/F556
    A868 = -2.5*math.log10(F868); sA868 = 2.5/math.log(10)*e868/F868
    if A556 > 3*sA556 and A868 > 0:
        R = A556/A868
        sR = R*math.sqrt((sA556/A556)**2 + (sA868/A868)**2)
        ratios.append((bjd, R, sR))
        log(f"  BJD {bjd:.4f}: A556 {1000*A556:6.2f} mmag  A868 {1000*A868:6.2f} mmag  ratio {R:5.2f} ± {sR:4.2f}")
if len(ratios) >= 2:
    hi = max(ratios, key=lambda x: x[1]); lo = min(ratios, key=lambda x: x[1])
    diff = hi[1]-lo[1]; sd = math.hypot(hi[2], lo[2])
    log(f"  max−min ratio: {diff:.2f} ± {sd:.2f}  ({diff/sd:.1f}σ joint)")
    log(f"  Q2: ratios {'VARY beyond 2σ — geometry-set ratios consistent; single fixed grain population disfavoured' if diff > 2*sd else 'consistent with constant — one grain population stands'}")
    log("  scope: per-event grain populations remain an absorption escape — stated.")
log("  literature corroboration (quoted, not computed here): Bodman+ 2018 — 'a single")
log("  wavelength dependence does not fit the entire light curve'; dimming 'non-gray")
log("  and varies in time'. Meng+ 2017 — secular extinction wavelength-dependent.")

with open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "RUN_LOG.txt"), "w", encoding="utf-8") as fh:
    fh.write("\n".join(OUT) + "\n")
print("\n[log written to RUN_LOG.txt]")
