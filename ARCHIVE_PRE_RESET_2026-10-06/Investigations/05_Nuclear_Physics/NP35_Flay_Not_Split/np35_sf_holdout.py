#!/usr/bin/env python3
"""NP35 F3 spontaneous-fission hold-out. Predictions are printed and asserted against the pre-registration table BEFORE any yield file is opened."""
import sys, re, zipfile
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import np35_flay_sim as S
ROOT = S.ROOT
D = ROOT / "Datasets/nuclear/fission_yields/endf_b8_sfy/ENDF-B-VIII.0_sfy"
SYS = [("U-238", "sfy-092_U_238.endf", 92, 238), ("Cm-244", "sfy-096_Cm_244.endf", 96, 244), ("Cm-246", "sfy-096_Cm_246.endf", 96, 246),
       ("Cm-248", "sfy-096_Cm_248.endf", 96, 248), ("Cf-250", "sfy-098_Cf_250.endf", 98, 250), ("Cf-252", "sfy-098_Cf_252.endf", 98, 252),
       ("Es-253", "sfy-099_Es_253.endf", 99, 253), ("Fm-254", "sfy-100_Fm_254.endf", 100, 254), ("Fm-256", "sfy-100_Fm_256.endf", 100, 256)]
REG = {"U-238": (52, 134, 104), "Cm-244": (53, 135, 109), "Cm-246": (52, 134, 112), "Cm-248": (52, 134, 114), "Cf-250": (53, 135, 115),
       "Cf-252": (52, 134, 118), "Es-253": (53, 135, 118), "Fm-254": (53, 135, 119), "Fm-256": (53, 135, 121)}
S.validate_instrument()
print("\n--- predictions (yield files not opened) ---")
preds = {}
for lab, fn, Z, A in SYS:
    N = A - Z; nH = S.outermost_sealed_T(N); f3 = S.split_from_NH(Z, A, nH)
    assert nH == 82
    assert (f3["Z_H"], f3["A_H"], f3["A_L"]) == REG[lab], (lab, f3, REG[lab])
    preds[lab] = f3
    print(f"{lab:>7} A*={A} N={N} N_H={nH} Z_H={f3['Z_H']} A_H_pre={f3['A_H']} A_L_pre={f3['A_L']}  [matches pre-registration table]")

def ef(s):
    s = s.strip()
    if not s: return 0.0
    m = re.match(r'^([+-]?\d*\.?\d*)([+-]\d+)$', s)
    return float(m.group(1) + 'e' + m.group(2)) if m else float(s)

def read454(path):
    lines = [l.rstrip("\n") for l in open(path)]
    rec = [l for l in lines if len(l) >= 75 and l[70:72].strip() == "8" and l[72:75].strip() == "454"]
    # HEAD, then LIST header, then data
    head = rec[0]; ne = int(ef(head[22:33])); assert ne >= 1
    lst = rec[1]; npl = int(ef(lst[44:55])); nfp = int(ef(lst[55:66]))
    vals = []
    for l in rec[2:]:
        for k in range(6):
            fld = l[11 * k:11 * (k + 1)]
            vals.append(ef(fld))
        if len(vals) >= npl: break
    vals = vals[:npl]; assert npl == 4 * nfp, (npl, nfp)
    out = {}
    for i in range(nfp):
        zafp, fps, yi, dyi = vals[4 * i:4 * i + 4]
        out[(int(round(zafp)) // 1000, int(round(zafp)) % 1000, int(round(fps)))] = yi
    return out, ne

print("\n--- comparison (ENDF/B-VIII.0 SFY opened now) ---")
print(f"{'sys':>7} {'sumY':>6} {'obs A_L':>8} {'obs A_H':>8} {'dAH':>7} {'class':>9} {'dAL':>7}")
rows = []
for lab, fn, Z, A in SYS:
    ind, ne = read454(D / fn)
    Y = {}
    for (z, a, m), y in ind.items(): Y[a] = Y.get(a, 0.0) + y
    sY = sum(Y.values())
    mid = A / 2.0
    AL, _ = S.hump_centroid(Y, 70, int(mid)); AH, _ = S.hump_centroid(Y, int(mid) + 1, 175)
    f3 = preds[lab]; dH = f3["A_H"] - AH; dL = f3["A_L"] - AL
    rows.append((lab, A, f3["A_H"], AH, AL, dH, dL, S.classify_dA(dH)))
    print(f"{lab:>7} {sY:>6.2f} {AL:>8.1f} {AH:>8.1f} {dH:>+7.1f} {S.classify_dA(dH):>9} {dL:>+7.1f}")
print("\n--- gates ---")
h1 = [r[7] for r in rows]; print("  H1 classes:", dict((c, h1.count(c)) for c in set(h1)), " all MATCH:", all(c == "MATCH" for c in h1))
print("  H2 observed A_H in [128,148] all:", all(128 <= r[3] <= 148 for r in rows), " any <120 or >160:", any(r[3] < 120 or r[3] > 160 for r in rows))
sl = S.slope([r[1] for r in rows], [r[3] for r in rows]); print(f"  H3 slope obs A_H vs A*: {sl:+.3f}  (|slope|<0.25: {abs(sl) < 0.25})")
print("  H4 A_L_pre-A_L_obs in [1,8]:", [round(r[6], 2) for r in rows], " all:", all(1 <= r[6] <= 8 for r in rows))
