"""NP24 blank-slate pass (2026-10-13). Registration: NP24_RESET_ASSESSMENT_2026-10-13.md sections 0-2 (written before this file existed).
P0 grammar recount, P3 stability band against decay-channel contours, P4 ionisation ladder (I1, I3 against an atomic-only null). P1/P2 are PENDING_MODEL.
Run from the repository root: python -I Investigations/05_Nuclear_Physics/NP24_Grammar_Rule_Extraction/np24_reset_1.py
Author: J. C. Harvey, Melbourne."""
import json, math, random

D = 'Datasets/nuclear/'


def parse_ame():
    me = {}      # (Z,A) -> (mass excess keV, estimated?)
    gs = []
    started = False
    for ln in open(D + 'AME2020_mass_excess.txt', encoding='utf-8', errors='replace'):
        if not started:
            if ln.startswith('1N-Z'):
                started = True
            continue
        if len(ln) < 45 or ln.strip().startswith('(keV)') or ln.startswith('1N-Z'):
            continue
        try:
            n = int(ln[4:9]); z = int(ln[9:14]); a = int(ln[14:19])
        except ValueError:
            continue
        raw = ln[28:42].strip()
        est = '#' in raw
        try:
            v = float(raw.replace('#', '.'))
        except ValueError:
            continue
        me[(z, a)] = (v, est)
        gs.append((z, a))
    return me, gs


def parse_nubase():
    gs = []; stable = {}; abund = {}
    for ln in open(D + 'NUBASE2020.txt', encoding='utf-8', errors='replace'):
        if ln.startswith('#') or len(ln) < 80:
            continue
        try:
            a = int(ln[0:3]); zi = ln[4:8]; z = int(zi[:3]); iso = int(zi[3])
        except ValueError:
            continue
        if iso != 0:
            continue
        gs.append((z, a))
        if 'stbl' in ln[69:79]:
            stable[(z, a)] = True
            k = ln.find('IS=')
            if k >= 0:
                try:
                    abund[(z, a)] = float(ln[k + 3:].split()[0])
                except ValueError:
                    pass
    return gs, stable, abund


def grammar(z, a):
    nt = a - 2 * z; nd = 3 * z - a - 2
    return nd, nt


me, ame_gs = parse_ame()
nub_gs, stable, abund = parse_nubase()
print('P0: AME2020 ground-state rows %d ; NUBASE2020 ground-state rows %d ; stable (NUBASE stbl) %d' % (len(ame_gs), len(nub_gs), len(stable)))
for name, gs in (('AME2020', ame_gs), ('NUBASE2020', nub_gs)):
    valid = [(z, a) for (z, a) in gs if z >= 3 and grammar(z, a)[0] >= 0 and grammar(z, a)[1] >= 0]
    bad = 0
    for (z, a) in valid:
        nd, nt = grammar(z, a)
        if a != 4 + 2 * nd + 3 * nt or z != 2 + nd + nt:
            bad += 1
    print('  %-10s grammar-valid (Z>=3, n_d>=0, n_t>=0): %d ; conservation failures %d (IDENTITY)' % (name, len(valid), bad))

# ---- P3 ----
def q_beta(z, a):
    if (z, a) in me and (z + 1, a) in me and not me[(z, a)][1] and not me[(z + 1, a)][1]:
        return me[(z, a)][0] - me[(z + 1, a)][0]
    return None


def q_ec(z, a):
    if (z, a) in me and (z - 1, a) in me and not me[(z, a)][1] and not me[(z - 1, a)][1]:
        return me[(z, a)][0] - me[(z - 1, a)][0]
    return None


def in_band(z, a):
    qb, qe = q_beta(z, a), q_ec(z, a)
    if qb is None or qe is None:
        return None
    return qb <= 0 and qe <= 0


st = [k for k in stable if k[0] >= 3]
det = [(k, in_band(*k)) for k in st]
known = [(k, b) for k, b in det if b is not None]
inside = sum(1 for k, b in known if b)
print('\nP3: stable nuclides with Z>=3: %d ; with both Q determinable (measured neighbours): %d ; inside the single-step band (Q_beta- <= 0 and Q_EC <= 0): %d (%.1f%%)' % (len(st), len(known), inside, 100.0 * inside / max(1, len(known))))
outside = [k for k, b in known if not b]
print('  stable nuclides outside the band:', [(z, a, round(q_beta(z, a) or 0, 1), round(q_ec(z, a) or 0, 1)) for (z, a) in outside][:12])
print('  F3 (>= 90%% inside): %s' % ('met' if inside / max(1, len(known)) >= 0.9 else 'NOT MET'))
rows = {}
for z in range(3, 100):
    sa = sorted(a for (zz, a) in stable if zz == z)
    if not sa:
        continue
    band = [a for (zz, a) in me if zz == z and in_band(z, a)]
    band.sort()
    if not band:
        continue
    # contiguous band around the stable range: take the maximal run of consecutive A (step 1) containing any stable A
    runs = []; cur = [band[0]]
    for a in band[1:]:
        if a == cur[-1] + 1:
            cur.append(a)
        else:
            runs.append(cur); cur = [a]
    runs.append(cur)
    # for even-A the band is the set with both Q<=0 which need not be contiguous; use min and max over the band that contains stable nuclides
    inb = [a for a in band if sa[0] - 6 <= a <= sa[-1] + 6] or band
    rows[z] = (sa[0], sa[-1], min(inb), max(inb), len(sa), len(band))
exact = 0; off = {}
for z, (s0, s1, b0, b1, ns, nb) in sorted(rows.items()):
    d0, d1 = s0 - b0, b1 - s1
    key = (d0, d1)
    off[key] = off.get(key, 0) + 1
    if d0 == 0 and d1 == 0:
        exact += 1
print('  F4: rows (Z) with a stable range and a band: %d ; stable-range edges coincide with the band edges (same A at both ends): %d (%.1f%%)' % (len(rows), exact, 100.0 * exact / len(rows)))
print('  distribution of (stable min A - band min A, band max A - stable max A):', sorted(off.items(), key=lambda kv: -kv[1])[:8])
print('  F4 (>= 90%% of rows): %s' % ('met' if exact / len(rows) >= 0.9 else 'NOT MET'))
# S1 as a rule: u_mid(v) quadratic, cross-parity
pts = []
for z, (s0, s1, b0, b1, ns, nb) in rows.items():
    u0 = 5 * z - 2 * s0 - 2; u1 = 5 * z - 2 * s1 - 2
    pts.append((z - 2, 0.5 * (u0 + u1), z))


def polyfit2(xs, ys):
    n = len(xs)
    sx = [sum(x ** k for x in xs) for k in range(5)]
    sy = [sum(y * x ** k for x, y in zip(xs, ys)) for k in range(3)]
    A = [[sx[i + j] for j in range(3)] for i in range(3)]
    # gaussian elimination
    M = [A[i] + [sy[i]] for i in range(3)]
    for i in range(3):
        p = max(range(i, 3), key=lambda r: abs(M[r][i])); M[i], M[p] = M[p], M[i]
        for r in range(i + 1, 3):
            f = M[r][i] / M[i][i]
            for c in range(i, 4):
                M[r][c] -= f * M[i][c]
    c = [0, 0, 0]
    for i in (2, 1, 0):
        c[i] = (M[i][3] - sum(M[i][j] * c[j] for j in range(i + 1, 3))) / M[i][i]
    return c


def oos(train, test):
    c = polyfit2([p[0] for p in train], [p[1] for p in train])
    ys = [p[1] for p in test]; m = sum(ys) / len(ys)
    ss_res = sum((p[1] - (c[0] + c[1] * p[0] + c[2] * p[0] ** 2)) ** 2 for p in test); ss_tot = sum((y - m) ** 2 for y in ys)
    return 1 - ss_res / ss_tot, math.sqrt(ss_res / len(test))


ev = [p for p in pts if p[2] % 2 == 0]; od = [p for p in pts if p[2] % 2 == 1]
r1, e1 = oos(ev, od); r2, e2 = oos(od, ev)
print('  S1 as a rule (u_mid quadratic in v): fit even-Z -> odd-Z R^2 %.4f (rms %.2f u-units); fit odd-Z -> even-Z R^2 %.4f (rms %.2f)' % (r1, e1, r2, e2))
print('  note: u_mid = 5Z - A_mid*2 - 2 is the relabeled mid-A of the valley; a high R^2 here restates the smoothness of the valley of stability in Z (D2).')

# ---- P4 ----
ie = json.load(open(D + 'ionisation_energies.json'))
H = 13.59844
print('\nP4: ladder scaled to H (z = IE/13.59844 eV, k = 1/sqrt(z)); elements with a list: %d' % len(ie))
print('  I1 (hydrogenic null) last electron z/Z^2 for the complete ladders:')
shown = []
for zs in sorted(ie, key=int):
    z = int(zs); lst = ie[zs]
    if len(lst) == z:
        shown.append((z, lst[-1] / H / (z * z)))
print('   ', ' '.join('Z%d:%.4f' % (z, r) for z, r in shown[:3] + shown[len(shown) // 2 - 1:len(shown) // 2 + 1] + shown[-3:]))
print('    complete ladders %d ; z_last/Z^2 from %.4f to %.4f' % (len(shown), min(r for z, r in shown), max(r for z, r in shown)))
# I3 test
f1 = {}
for zs in ie:
    if ie[zs]:
        f1[int(zs)] = ie[zs][0]
fr = {}
for z in range(3, 99):
    cand = [(abund.get((zz, a), 0.0), a) for (zz, a) in stable if zz == z]
    if not cand:
        continue
    ab, a = max(cand)
    nd, nt = grammar(z, a)
    fr[z] = nt / (nd + nt)
els = [z for z in sorted(fr) if (z - 1) in f1 and (z + 1) in f1 and z in f1]
res = {z: math.log(f1[z]) - 0.5 * (math.log(f1[z - 1]) + math.log(f1[z + 1])) for z in els}
print('  I3 test: elements with a stable isotope and an IE1 on both neighbours: %d ; feature r_Z = ln IE1(Z) - mean of neighbours ; f_t of the most abundant stable isotope' % len(els))


def r2_oos(train, test, x, y):
    # r = b f_t through the origin on train, R^2 on test relative to zero baseline? use mean-removed baseline of the test set
    sxy = sum(x[z] * y[z] for z in train); sxx = sum(x[z] * x[z] for z in train); b = sxy / sxx
    ys = [y[z] for z in test]; m = sum(ys) / len(ys)
    return 1 - sum((y[z] - b * x[z]) ** 2 for z in test) / sum((v - m) ** 2 for v in ys)


ev = [z for z in els if z % 2 == 0]; od = [z for z in els if z % 2 == 1]
ra, rb = r2_oos(ev, od, fr, res), r2_oos(od, ev, fr, res)
random.seed(24)
nulls = []
zs_ = list(els)
for _ in range(5000):
    sh = zs_[:]; random.shuffle(sh)
    pf = {z: fr[s] for z, s in zip(zs_, sh)}
    nulls.append((r2_oos(ev, od, pf, res), r2_oos(od, ev, pf, res)))
q95a = sorted(x[0] for x in nulls)[int(0.95 * len(nulls))]; q95b = sorted(x[1] for x in nulls)[int(0.95 * len(nulls))]
print('    fit even-Z -> test odd-Z R^2 = %.4f (permutation null 95th percentile %.4f) ; fit odd-Z -> test even-Z R^2 = %.4f (null 95th %.4f)' % (ra, q95a, rb, q95b))
print('    I3 beats I2 out of sample (both positive and above the null 95th percentile): %s' % ('YES' if (ra > 0 and rb > 0 and ra > q95a and rb > q95b) else 'NO'))
print('\nP1, P2, P5: PENDING_MODEL (no blind kappa-shadow model).')
