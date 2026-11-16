"""NP42 Round 7 (2026-10-14). Registration: NP42_RESET_ASSESSMENT_2026-10-14.md sections 0-2 (written before this file existed).
Hockey-stick break scan on U-235, U-233 (consistency) and Cf-252 (held-out), second forms Q and S for U-233.
Run from the repository root: python -I Investigations/05_Nuclear_Physics/NP42_Nu_A_Closure_Reset/np42_reset_2.py
Author: J. C. Harvey, Melbourne."""
import csv, math, random

D = 'Datasets/nuclear/neutron_multiplicity/'
SYS = {'U-235': ('Nishio1998_U235_nth_f_nuA.csv', 92, 236, 'ERR-S'), 'U-233': ('Nishio1998_U233_nth_f_nuA.csv', 92, 234, 'ERR-S'), 'Cf-252': ('BudtzJorgensen1988_Cf252_sf_nuA.csv', 98, 252, 'DATA-ERR')}


def load(name, lo=74.0):
    f, zp, ap, ecol = SYS[name]
    out = []
    for r in csv.DictReader(open(D + f, encoding='utf-8')):
        try:
            A = float(r['MASS']); nu = float(r['DATA']); e = float(r[ecol]) if r[ecol].strip() else None
        except (ValueError, KeyError):
            continue
        if e is None or e <= 0:
            continue
        N = A - A * zp / ap
        if N >= lo:
            out.append((N, nu, e))
    return out


def wls(rows, basis):
    # fit y = a + b*x where x = basis(N) ; weights 1/sigma^2 ; closed form
    sw = sx = sy = sxx = sxy = 0.0
    for N, y, e in rows:
        w = 1.0 / (e * e); x = basis(N)
        sw += w; sx += w * x; sy += w * y; sxx += w * x * x; sxy += w * x * y
    d = sw * sxx - sx * sx
    if abs(d) < 1e-18:
        return None
    b = (sw * sxy - sx * sy) / d; a = (sy - b * sx) / sw
    chi = sum(((y - a - b * basis(N)) / e) ** 2 for N, y, e in rows)
    return a, b, chi


def scan(rows, kind):
    best = None; prof = []
    ws = [None] if kind in ('H', 'Q') else [0.5, 1, 1.5, 2, 3, 4, 6]
    for w in ws:
        for k in range(0, 161):
            ns = 60.0 + 0.25 * k
            if kind == 'H':
                basis = lambda N, ns=ns: max(0.0, N - ns)
            elif kind == 'Q':
                basis = lambda N, ns=ns: max(0.0, N - ns) ** 2
            else:
                basis = lambda N, ns=ns, w=w: w * math.log1p(math.exp(min(50.0, (N - ns) / w)))
            r = wls(rows, basis)
            if r is None:
                continue
            a, b, chi = r
            prof.append((ns, w, chi))
            if best is None or chi < best[0]:
                best = (chi, ns, w, a, b)
    return best, prof


def interval(prof, chimin):
    ok = sorted(ns for ns, w, c in prof if c <= chimin + 4.0)
    return (ok[0], ok[-1]) if ok else (None, None)


def chi_at(prof, ns0):
    return min(c for ns, w, c in prof if abs(ns - ns0) < 1e-9)


# ---- V1: planted break ----
random.seed(7)
tmpl = load('U-233')
planted = [(N, 0.5 + 0.25 * max(0.0, N - 80.0) + random.gauss(0, e), e) for N, y, e in tmpl]
bp, _ = scan(planted, 'H')
print('[V1] planted break N* = 80 on the U-233 grid (%d points): recovered %.2f -> %s' % (len(planted), bp[1], 'met' if abs(bp[1] - 80.0) <= 0.5 else 'NOT MET'))
v1 = abs(bp[1] - 80.0) <= 0.5
# ---- V2 ----
print('[V2] Z_f = A Z_p / A_p gives N = 82 at A = %.2f (U-235 parent: 236/(1 - 92/236) = %.2f)' % (82.0 / (1 - 92.0 / 236.0), 82.0 / (1 - 92.0 / 236.0)))
# ---- systems ----
res = {}
for name in ('U-235', 'U-233', 'Cf-252'):
    rows = load(name)
    best, prof = scan(rows, 'H')
    lo, hi = interval(prof, best[0])
    dof = len(rows) - 3
    res[name] = (rows, best, prof)
    print('\n%s: %d points with N >= 74 ; hockey stick best N* = %.2f (a = %.3f, b = %.4f), chi2 = %.1f, chi2/dof = %.2f ; dchi2 <= 4 set [%.2f, %.2f] ; dchi2(80) = %.2f, dchi2(82) = %.2f' % (name, len(rows), best[1], best[3], best[4], best[0], best[0] / dof, lo, hi, chi_at(prof, 80.0) - best[0], chi_at(prof, 82.0) - best[0]))
    for edge in (70.0, 78.0):
        r2 = load(name, edge); b2, p2 = scan(r2, 'H'); l2, h2 = interval(p2, b2[0])
        print('   domain N >= %.0f: %d points, best N* = %.2f, set [%.2f, %.2f], chi2/dof %.2f' % (edge, len(r2), b2[1], l2, h2, b2[0] / (len(r2) - 3)))
# ---- V3 ----
v3a = abs(res['U-235'][1][1] - 80.50) <= 1.0; v3b = abs(res['U-233'][1][1] - 79.75) <= 1.0
print('\n[V3] consistency with the prompt\'s round-6 breaks: U-235 %.2f vs 80.50 -> %s ; U-233 %.2f vs 79.75 -> %s' % (res['U-235'][1][1], 'met' if v3a else 'NOT MET', res['U-233'][1][1], 'met' if v3b else 'NOT MET'))
# ---- held-out gates ----
b = res['Cf-252'][1]; lo, hi = interval(res['Cf-252'][2], b[0])
g7a = 78.0 <= b[1] <= 82.0; g7b = lo <= 80.0 <= hi
print('\nHELD-OUT Cf-252 (scanned once): best N* = %.2f ; G7a (in [78, 82]) %s ; G7b (80 inside the dchi2 <= 4 set [%.2f, %.2f]) %s ; dchi2(82) = %.2f (%s) ; chi2/dof %.2f' % (b[1], 'met' if g7a else 'NOT MET', lo, hi, 'met' if g7b else 'NOT MET', chi_at(res['Cf-252'][2], 82.0) - b[0], 'excluded at dchi2 > 4' if chi_at(res['Cf-252'][2], 82.0) - b[0] > 4 else 'not excluded', b[0] / (len(res['Cf-252'][0]) - 3)))
# ---- second forms ----
print('\nSECOND FORMS (chi2/dof): hockey stick H, quadratic hinge Q, soft hinge S (w scanned, 4 parameters)')
for name in ('U-233', 'U-235', 'Cf-252'):
    rows = res[name][0]
    hb = res[name][1]
    qb, _ = scan(rows, 'Q'); sb, _ = scan(rows, 'S')
    print('  %-7s H %.2f (N* %.2f) ; Q %.2f (N* %.2f) ; S %.2f (N* %.2f, w %.1f)' % (name, hb[0] / (len(rows) - 3), hb[1], qb[0] / (len(rows) - 3), qb[1], sb[0] / (len(rows) - 4), sb[1], sb[2]))
rows = res['U-233'][0]; hb = res['U-233'][1]; qb, _ = scan(rows, 'Q'); sb, _ = scan(rows, 'S')
better_q = hb[0] / (len(rows) - 3) - qb[0] / (len(rows) - 3) >= 3.0
better_s = hb[0] / (len(rows) - 3) - sb[0] / (len(rows) - 4) >= 3.0
print('U-233: Q better by >= 3 chi2/dof units: %s ; S better by >= 3: %s' % (better_q, better_s))
band = 'G4' if (g7a and g7b and v3a and v3b and v1) else ('G3' if (g7a and v1) else 'G1 or G0 (see validations)')
print('\ncascade band: %s' % band)
