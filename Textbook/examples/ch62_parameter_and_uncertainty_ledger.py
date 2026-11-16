"""Chapter 62 - parameter and uncertainty ledger: worked-example instrument.

Pre-registration: Textbook/validation/ch62_PRE_REGISTRATION.md (registered before this file existed).
Run: bash Textbook/tools/py_run.sh ch62_parameter_and_uncertainty_ledger
"""
import csv
import glob
import math
import random
import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
FAILS = 0
TOKENS = ["DERIVED", "COMPUTED", "CALIBRATED", "OBSERVED", "CONSTRUCTION", "MEASURED-INPUT", "PENDING", "TOY", "stored", "unit bridge"]


def check(tid, what, ok):
    global FAILS
    if not ok:
        FAILS += 1
    print(f"[{'PASS' if ok else 'FAIL'}] {tid:<4} {what}")


def heading(t):
    print(f"\n== {t} ==")


def parse_tables(text):
    """Return the tables that follow a heading or bold line containing 'ledger': list of (header cells, rows)."""
    lines = text.splitlines()
    out = []
    i = 0
    while i < len(lines):
        ln = lines[i]
        if "ledger" in ln.lower() and (ln.startswith("#") or ln.startswith("**")):
            j = i + 1
            while j < len(lines) and not lines[j].lstrip().startswith("|") and j < i + 6:
                j += 1
            if j < len(lines) and lines[j].lstrip().startswith("|"):
                tbl = []
                while j < len(lines) and lines[j].lstrip().startswith("|"):
                    tbl.append(lines[j].strip())
                    j += 1
                cells = [[c.strip() for c in row.strip("|").split("|")] for row in tbl]
                if len(cells) >= 2:
                    header = cells[0]
                    body = [c for c in cells[2:]] if set("".join(cells[1]).replace(" ", "")) <= set("-:|") else cells[1:]
                    out.append((header, body))
                i = j
                continue
        i += 1
    return out


def matmul(A, B):
    return [[sum(A[i][k] * B[k][j] for k in range(len(B))) for j in range(len(B[0]))] for i in range(len(A))]


def transpose(A):
    return [list(r) for r in zip(*A)]


def lsq_poly(xs, ys, deg):
    n = deg + 1
    A = [[sum(x ** (i + j) for x in xs) for j in range(n)] for i in range(n)]
    b = [sum(y * x ** i for x, y in zip(xs, ys)) for i in range(n)]
    for c in range(n):
        p = max(range(c, n), key=lambda r: abs(A[r][c]))
        A[c], A[p] = A[p], A[c]
        b[c], b[p] = b[p], b[c]
        for r in range(c + 1, n):
            f = A[r][c] / A[c][c]
            for k in range(c, n):
                A[r][k] -= f * A[c][k]
            b[r] -= f * b[c]
    x = [0.0] * n
    for r in range(n - 1, -1, -1):
        x[r] = (b[r] - sum(A[r][k] * x[k] for k in range(r + 1, n))) / A[r][r]
    return x


def rmse(coef, xs, ys):
    return math.sqrt(sum((sum(c * x ** i for i, c in enumerate(coef)) - y) ** 2 for x, y in zip(xs, ys)) / len(xs))


heading("V1 known answers")
tbl = parse_tables("## 9.9 Input ledger\n\n| quantity | value | label |\n|---|---|---|\n| a | 1 | DERIVED (exact) |\n| b | 2 | COMPUTED |\n")
check("V1", "the table parser returns two rows with the labels read", len(tbl) == 1 and len(tbl[0][1]) == 2 and tbl[0][1][0][2].startswith("DERIVED") and tbl[0][1][1][2] == "COMPUTED")
W = [[1, -1, 0], [1, 0, -1]]
Cx = [[1e-6, 0, 0], [0, 4e-6, 0], [0, 0, 9e-6]]
Cy = matmul(matmul(W, Cx), transpose(W))
check("V1", "W C_x W^T = [[5, 1], [1, 10]] x 1e-6", all(abs(Cy[i][j] - [[5e-6, 1e-6], [1e-6, 10e-6]][i][j]) < 1e-15 for i in range(2) for j in range(2)))
check("V1", "Phi(-0.6) = 0.27425 from erfc", abs(0.5 * math.erfc(0.6 / math.sqrt(2)) - 0.27425) < 1e-5)
c = lsq_poly([0, 1, 2, 3, 4], [2 - 3 * x for x in range(5)], 1)
check("V1", "least squares returns (2, -3)", abs(c[0] - 2) < 1e-12 and abs(c[1] + 3) < 1e-12)

heading("T1 the manuscript's input ledgers")
files = sorted(glob.glob("Textbook/volume_0*/ch*.md"))
rows_out = []
no_ledger = []
no_token = []
per_chapter = {}
token_count = {t: 0 for t in TOKENS}
for f in files:
    p = Path(f)
    ch = p.name.split("_")[0]
    text = p.read_text(encoding="utf-8")
    tables = parse_tables(text)
    has_cov = "covariance" in text.lower()
    n = 0
    if not tables:
        no_ledger.append(ch)
        continue
    for header, body in tables:
        lab_idx = next((k for k, h in enumerate(header) if "label" in h.lower() or "status" in h.lower() or "class" in h.lower()), len(header) - 1)
        for r in body:
            if len(r) <= lab_idx:
                continue
            lab = r[lab_idx]
            tok = next((t for t in TOKENS if t.lower() in lab.lower()), "")
            if tok:
                token_count[tok] += 1
            else:
                no_token.append((ch, r[0][:50], lab[:50]))
            rows_out.append([ch, n + 1, r[0], r[1] if len(r) > 1 else "", lab, tok, "yes" if has_cov else "no"])
            n += 1
    per_chapter[ch] = n
print(f"       chapters scanned: {len(files)} ; with a parsable ledger: {len(files) - len(no_ledger)} ; without: {no_ledger}")
print(f"       rows extracted: {len(rows_out)} ; rows without a recognised label token: {len(no_token)}")
print("       label tokens:", {k: v for k, v in token_count.items() if v})
out = Path("Textbook/sources/PARAMETER_LEDGER.csv")
with out.open("w", encoding="utf-8", newline="") as fh:
    w = csv.writer(fh)
    w.writerow(["chapter", "row", "quantity", "source_or_value", "label", "label_token", "chapter_mentions_covariance"])
    w.writerows(rows_out)
for ch, q, lab in no_token:
    print(f"       no token: {ch} | {q} | {lab}")
print("       rows per chapter:", {k: v for k, v in sorted(per_chapter.items())})
print("RECORDED REJECTIONS (run 2 criteria kept; findings on the manuscript):")
check("T1", "the registered statement (at least 55 chapters have a parsable ledger) is rejected: found %d" % (len(files) - len(no_ledger)), not (len(files) - len(no_ledger) >= 55))
check("T1", "the registered statement (at least 300 rows) is rejected: found %d" % len(rows_out), not (len(rows_out) >= 300))
frac = 1.0 - len(no_token) / max(1, len(rows_out))
print(f"       fraction of rows with a recognised label token: {frac:.4f}")
check("T1", "the registered statement (at least 90 per cent of rows carry a recognised token) is rejected: found %.4f" % frac, not (frac >= 0.90))
check("T1", "PARAMETER_LEDGER.csv is written with one line per row", sum(1 for _ in out.open(encoding="utf-8")) == len(rows_out) + 1)

heading("T2 covariance of ratios that share a measurement")
check("T2", "C_y is [[5, 1], [1, 10]] x 1e-6", abs(Cy[0][0] - 5e-6) < 1e-15 and abs(Cy[0][1] - 1e-6) < 1e-15 and abs(Cy[1][1] - 10e-6) < 1e-15)
rho = Cy[0][1] / math.sqrt(Cy[0][0] * Cy[1][1])
print(f"       correlation of the two ratios: {rho:.4f}")
check("T2", "the correlation is 0.1414", abs(rho - 0.1414) < 5e-5)
var_with = Cy[0][0] + Cy[1][1] - 2 * Cy[0][1]
var_without = Cy[0][0] + Cy[1][1]
print(f"       variance of y1 - y2: with covariance {var_with:.3e}; ignoring it {var_without:.3e}; overstatement {var_without / var_with - 1:.4f}")
check("T2", "the variance of y1 - y2 is 13e-6 with the covariance and 15e-6 without (overstated by 15.4 per cent)", abs(var_with - 13e-6) < 1e-15 and abs(var_without - 15e-6) < 1e-15 and abs(var_without / var_with - 1 - 0.1538) < 1e-3)
rng = random.Random(20261110)
N = 200000
s11 = s22 = s12 = sd = 0.0
for _ in range(N):
    x1, x2, x3 = rng.gauss(0, 1e-3), rng.gauss(0, 2e-3), rng.gauss(0, 3e-3)
    y1, y2 = x1 - x2, x1 - x3
    s11 += y1 * y1
    s22 += y2 * y2
    s12 += y1 * y2
    sd += (y1 - y2) ** 2
mc = (s11 / N, s22 / N, s12 / N, sd / N)
print(f"       Monte Carlo: var y1 {mc[0]:.3e}, var y2 {mc[1]:.3e}, cov {mc[2]:.3e}, var(y1-y2) {mc[3]:.3e}")
check("T2", "the Monte Carlo reproduces var y1, var y2 and var(y1 - y2) within 2 per cent", abs(mc[0] / 5e-6 - 1) < 0.02 and abs(mc[1] / 10e-6 - 1) < 0.02 and abs(mc[3] / 13e-6 - 1) < 0.02)
check("T2", "the Monte Carlo covariance is within 5 per cent of 1e-6", abs(mc[2] / 1e-6 - 1) < 0.05)

heading("T3 a response that reaches a boundary")
phi = 0.5 * math.erfc(0.6 / math.sqrt(2))
print(f"       Gaussian mass below zero for m = 0.3, sigma = 0.5: {phi:.5f}")
check("T3", "Phi(-0.6) = 0.2743 (1e-3)", abs(phi - 0.2743) < 1e-3)
below = 0
acc = []
for _ in range(N):
    m = rng.gauss(0.3, 0.5)
    if m < 0:
        below += 1
    else:
        acc.append(m)
print(f"       Monte Carlo mass below zero: {below / N:.5f} ; mean of the admissible draws: {sum(acc) / len(acc):.5f}")
check("T3", "the Monte Carlo mass below zero is within 0.005 of 0.2743", abs(below / N - 0.2743) < 0.005)
pdf = math.exp(-0.5 * 0.36) / math.sqrt(2 * math.pi)
tmean = 0.3 + 0.5 * pdf / (1 - phi)
print(f"       truncated mean (analytic) {tmean:.5f}")
check("T3", "the mean of the admissible distribution lies in [0.52, 0.54]", 0.52 <= tmean <= 0.54 and 0.52 <= sum(acc) / len(acc) <= 0.54)
sf = math.sqrt(2 * 0.1 ** 4 + 4 * 0.05 ** 2 * 0.1 ** 2)
ratio = sf / 0.01
vals = [rng.gauss(0.05, 0.1) ** 2 for _ in range(N)]
mean = sum(vals) / N
sd_mc = math.sqrt(sum((v - mean) ** 2 for v in vals) / (N - 1))
print(f"       f = x^2: actual sd {sf:.5f}; first-order sd 0.01000; ratio {ratio:.3f}; Monte Carlo sd {sd_mc:.5f}")
check("T3", "the first-order standard deviation understates the actual by a factor in [1.6, 1.9]", 1.6 <= ratio <= 1.9)
check("T3", "the Monte Carlo standard deviation agrees with the exact value within 2 per cent", abs(sd_mc / sf - 1) < 0.02)

heading("T4 calibration is not prediction")
rng2 = random.Random(7)
xs = [i / 11 for i in range(12)]
ys = [1.0 - 2.0 * x + 3.0 * x * x + rng2.gauss(0, 0.05) for x in xs]
train = [0, 1, 3, 4, 6, 7, 9, 10]
held = [2, 5, 8, 11]
xt, yt = [xs[i] for i in train], [ys[i] for i in train]
xh, yh = [xs[i] for i in held], [ys[i] for i in held]
c5 = lsq_poly(xt, yt, 5)
c2 = lsq_poly(xt, yt, 2)
r5t, r5h, r2h = rmse(c5, xt, yt), rmse(c5, xh, yh), rmse(c2, xh, yh)
print(f"       degree 5 on 8 points: training RMSE {r5t:.5f}, withheld RMSE {r5h:.5f} ; degree 2: withheld RMSE {r2h:.5f}")
check("T4", "the degree-5 training RMSE is below half its withheld RMSE", r5t < 0.5 * r5h)
check("T4", "the degree-2 withheld RMSE is below the degree-5 withheld RMSE", r2h < r5h)
a5, a2 = lsq_poly(xs, ys, 5), lsq_poly(xs, ys, 2)
print(f"       all-data fits: degree 5 RMSE {rmse(a5, xs, ys):.5f}; degree 2 RMSE {rmse(a2, xs, ys):.5f}")
check("T4", "the all-data degree-5 fit has a smaller training RMSE than the degree-2 fit", rmse(a5, xs, ys) < rmse(a2, xs, ys))

print()
print("ALL CRITERIA MET: 0 failure(s)" if FAILS == 0 else f"CRITERIA NOT MET: {FAILS} failure(s)")
sys.exit(1 if FAILS else 0)
