# ═══════════════════════════════════════════════════════════════════════
# NP12 - Nuclear Charge Radius Scaling: Z-linear (SDT canon) vs A^(1/3)
# Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
# Data: charge_radii_iaea.csv (IAEA / Angeli & Marinova 2013, downloaded
#       2026-07-03 — REAL data, provenance in RUN_LOG.md).
# Models M1-M5 and all gates pre-committed in RUN_LOG.md BEFORE this file.
# Engine constants cited from sdt/laws.hpp (values inlined, source noted):
#   R_p = 0.8414 fm  (measured::R_p, muonic-H)   — the ONLY SDT length used.
# ═══════════════════════════════════════════════════════════════════════
import csv, math, os

HERE = os.path.dirname(os.path.abspath(__file__))
R_P = 0.8414                      # fm — sdt::laws::measured::R_p
ETA = math.pi / math.sqrt(18.0)   # fcc/icosahedral close-packing fraction

rows = []
with open(os.path.join(HERE, "charge_radii_iaea.csv"), newline="") as f:
    for rec in csv.DictReader(f):
        try:
            z = int(rec["z"]); a = int(rec["a"])
            r = float(rec["radius_val"])
        except (ValueError, KeyError):
            continue
        if z >= 1 and r > 0:
            rows.append((z, a, r))

N = len(rows)
print("NP12 - Nuclear Charge Radius Scaling (J. C. Harvey, 2026-07-03)")
print("Data: IAEA charge_radii.csv (Angeli & Marinova 2013). REAL download.")
print("Filter: Z>=1, radius_val>0.  N = %d isotopes  (criterion N>=250: %s)" %
      (N, "MET" if N >= 250 else "NOT MET"))
print("=" * 74)

MODELS = [
    ("M1  Z*R_p (SDT canon)",        lambda z, a: z * R_P,                              0),
    ("M2  1.2*A^1/3 (rival as written)", lambda z, a: 1.2 * a ** (1/3),                 0),
    ("M3  0.9295*A^1/3 (fair rival)",    lambda z, a: math.sqrt(3/5) * 1.2 * a ** (1/3), 0),
    ("M4a 0.7207*A^1/3 (SDT pack, uniform)", lambda z, a: math.sqrt(3/5) * R_P * (a/ETA) ** (1/3), 0),
    ("M4b 0.9304*A^1/3 (SDT pack, surface)", lambda z, a: R_P * (a/ETA) ** (1/3),        0),
]
# M5 diagnostic: R = k_Z * Z^(1/3), k_Z fitted (CALIBRATED(1), declared)
k_Z = sum(r * z ** (1/3) for z, a, r in rows) / sum(z ** (2/3) for z, a, r in rows)
MODELS.append(("M5  %.4f*Z^1/3 [CALIBRATED(1)]" % k_Z, lambda z, a: k_Z * z ** (1/3), 1))

def metrics(sel):
    mean_r = sum(r for _, _, r in sel) / len(sel)
    ss_tot = sum((r - mean_r) ** 2 for _, _, r in sel)
    out = []
    for name, fn, npar in MODELS:
        res  = [(fn(z, a) - r) for z, a, r in sel]
        rel  = [(fn(z, a) - r) / r for z, a, r in sel]
        rms  = math.sqrt(sum(e * e for e in res) / len(sel))
        rmsr = math.sqrt(sum(e * e for e in rel) / len(sel)) * 100.0
        r2   = 1.0 - sum(e * e for e in res) / ss_tot
        out.append((name, rms, rmsr, r2, npar))
    return out

print("\n[Phase B] Global comparison (all %d isotopes)" % N)
print("  %-36s %10s %10s %9s %6s" % ("model", "RMS[fm]", "RMS[%]", "R^2", "npar"))
full = metrics(rows)
for name, rms, rmsr, r2, npar in full:
    print("  %-36s %10.4f %9.2f%% %9.4f %6d" % (name, rms, rmsr, r2, npar))

best0 = min((m for m in full if m[4] == 0 and not m[0].startswith("M1")), key=lambda m: m[2])
m1 = full[0]
print("\n  best zero-param A^1/3-family model: %s (RMS %.2f%%)" % (best0[0], best0[2]))
print("  KILL RULE (committed): RMS(M1) > 3x best -> %.2f%% vs %.2f%% : factor %.1fx -> %s"
      % (m1[2], best0[2], m1[2] / best0[2],
         "M1 KILLED as a global law" if m1[2] > 3 * best0[2] else "M1 survives"))

print("\n  Z-band breakdown (RMS relative %):")
BANDS = [(1, 8), (9, 20), (21, 50), (51, 92)]
print("  %-36s" % "model" + "".join(" Z%3d-%-3d" % b for b in BANDS))
for name, fn, npar in MODELS:
    cells = []
    for lo, hi in BANDS:
        sel = [(z, a, r) for z, a, r in rows if lo <= z <= hi]
        rel = [(fn(z, a) - r) / r for z, a, r in sel]
        cells.append(math.sqrt(sum(e * e for e in rel) / len(sel)) * 100.0)
    print("  %-36s" % name + "".join(" %7.1f%%" % c for c in cells))

print("\n[Phase C] Isotope-chain spread (gates committed: <2%% Z-constancy ok, >5%% A^1/3 better)")
for zc, label in [(20, "Ca"), (50, "Sn"), (82, "Pb")]:
    chain = sorted([(a, r) for z, a, r in rows if z == zc])
    a_lo, a_hi = chain[0][0], chain[-1][0]
    vals = [r for _, r in chain]
    spread = (max(vals) - min(vals)) / (sum(vals) / len(vals)) * 100.0
    a13 = ((a_hi / a_lo) ** (1/3) - 1.0) * 100.0
    verdict = ("< 2%: Z-constancy essentially correct" if spread < 2.0 else
               ("> 5%: A^1/3 captures chains better" if spread > 5.0 else "2-5%: intermediate"))
    print("  %s (Z=%d): %d isotopes A=%d..%d  measured spread = %.2f%%  [%s]" %
          (label, zc, len(chain), a_lo, a_hi, spread, verdict))
    print("      A^1/3 PREDICTED spread for same A-range = %.2f%%  (flatness cuts both ways)" % a13)

print("\n[Phase D] Magic-Z residuals vs best A^1/3-family model (report only)")
_, bestfn, _ = next((n, f, p) for n, f, p in MODELS if n == best0[0])
magic = {2, 8, 20, 28, 50, 82}
res_m  = [abs(bestfn(z, a) - r) / r * 100 for z, a, r in rows if z in magic]
res_nm = [abs(bestfn(z, a) - r) / r * 100 for z, a, r in rows if z not in magic]
print("  mean |res| magic-Z: %.2f%% (n=%d)   non-magic: %.2f%% (n=%d)" %
      (sum(res_m)/len(res_m), len(res_m), sum(res_nm)/len(res_nm), len(res_nm)))

print("\n[Phase E] R/Z constancy test (M1 predicts R/Z = 0.8414 fm for all Z)")
rz = sorted((r / z, z) for z, a, r in rows)
byZ = {}
for z, a, r in rows:
    byZ.setdefault(z, []).append(r / z)
zs = sorted(byZ)
print("  R/Z: min = %.4f fm (Z=%d)  median = %.4f  max = %.4f fm (Z=%d)" %
      (rz[0][0], rz[0][1], rz[len(rz)//2][0], rz[-1][0], rz[-1][1]))
print("  element means: Z=1: %.3f  Z=8: %.3f  Z=20: %.3f  Z=50: %.3f  Z=82: %.3f fm" %
      tuple(sum(byZ[z])/len(byZ[z]) for z in (1, 8, 20, 50, 82)))
print("  -> monotone drift by ~%.0fx across the table: R/Z is NOT constant." %
      ((sum(byZ[1])/len(byZ[1])) / (sum(byZ[82])/len(byZ[82]))))

print("\n" + "=" * 74)
print("VERDICT (numeric):")
print("  M1 Z*R_p       : RMS %.1f%% -> %s" % (m1[2],
      "KILLED as a global scaling law (survives only at Z=2..3)" if m1[2] > 3 * best0[2] else "survives"))
print("  rival as written (M2 1.2*A^1/3): RMS %.1f%% - ALSO fails on RMS data (unit mismatch," % full[1][2])
print("                   pre-declared: sharp-surface vs RMS convention, factor ~1.29)")
print("  fair rival M3  : RMS %.1f%% | SDT-native M4b: RMS %.1f%% (pre-declared DEGENERATE pair," % (full[2][2], full[4][2]))
print("                   0.09%% apart; dataset cannot distinguish)")
print("  M4a uniform    : RMS %.1f%% (bracket lower limit - fails; charge sits at periphery)" % full[3][2])
print("  M5 k*Z^1/3     : RMS %.1f%% with k fitted = %.4f fm [CALIBRATED(1), diagnostic only]" % (full[5][2], k_Z))
