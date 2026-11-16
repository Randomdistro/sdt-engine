# NP17 round 2-C (2026-10-13): Lambda-CDM-style calibrated run. Registration: ROUND2C_LCDM_PRE_REGISTRATION_2026-10-13.md.
# Fit K (= kappa * Om_p, fm) and L (MeV per loop) on 7 calibration nuclides; score 243 held-out. Author: J. C. Harvey, Melbourne.
import csv, math, sys, statistics as st
root = sys.argv[1]
U_KG, U_MEV22, U_KEV_AME = 1.66053906892e-27, 931.49410372, 931494.10242
mp = 1.67262192595e-27 / U_KG * U_MEV22; me = 9.1093837015e-31 / U_KG * U_MEV22; mn = 1.67492750056e-27 / U_KG * U_MEV22
ame = {}
for L in open(f'{root}/Datasets/nuclear/AME2020_mass_excess.txt', encoding='latin1'):
    if len(L) < 42 or not L[4:9].strip(): continue
    try: Z = int(L[9:14]); A = int(L[14:19])
    except ValueError: continue
    ex = L[28:42]
    if '#' in ex or not any(ch.isdigit() for ch in ex): continue
    ame[(Z, A)] = float(ex)
Matom = lambda Z, A: (A + ame[(Z, A)] / U_KEV_AME) * U_MEV22
Bnat = lambda Z, A: A * (mp + me) - Matom(Z, A)
Bpn = lambda Z, A: Z * (mp + me) + (A - Z) * mn - Matom(Z, A)
# validations
assert abs(Bnat(1, 1) * 1e6 - 13.598) < 0.5, 'V1 1H'
assert abs(Bnat(1, 2) - 1.442246) < 1e-5, 'V2 d native'
rows = list(csv.DictReader(open('np17_round2c_geometry.csv')))
for r in rows:
    for k in ('Z', 'A', 'contacts', 'pn', 'pp', 'nn', 'loops'): r[k] = int(r[k])
    r['S'] = float(r['sum_inv_d_fm']); r['Bn'] = Bnat(r['Z'], r['A']); r['Bp'] = Bpn(r['Z'], r['A'])
print(f'nuclides {len(rows)} ; p-p contacts total {sum(r["pp"] for r in rows)} ; n-n contacts total {sum(r["nn"] for r in rows)}')
CAL = {(2, 4), (6, 12), (8, 16), (20, 40), (26, 56), (50, 120), (82, 208)}
cal = [r for r in rows if (r['Z'], r['A']) in CAL]; held = [r for r in rows if (r['Z'], r['A']) not in CAL]
assert len(cal) == 7, f'calibration set incomplete: {len(cal)}'
def fit(xs, ys):  # weighted LSQ on relative residuals: minimise sum ((pred - y)/y)^2 ; xs = list of feature tuples
    n = len(xs[0]); M = [[0.0] * n for _ in range(n)]; v = [0.0] * n
    for x, y in zip(xs, ys):
        w = 1 / y ** 2
        for i in range(n):
            v[i] += w * x[i] * y
            for j in range(n): M[i][j] += w * x[i] * x[j]
    # solve
    import copy; A_ = copy.deepcopy(M); b = v[:]
    for i in range(n):
        p = max(range(i, n), key=lambda k: abs(A_[k][i])); A_[i], A_[p] = A_[p], A_[i]; b[i], b[p] = b[p], b[i]
        for k in range(i + 1, n):
            f = A_[k][i] / A_[i][i]
            for j in range(i, n): A_[k][j] -= f * A_[i][j]
            b[k] -= f * b[i]
    s = [0.0] * n
    for i in reversed(range(n)): s[i] = (b[i] - sum(A_[i][j] * s[j] for j in range(i + 1, n))) / A_[i][i]
    return s
band = lambda r: 'B1' if r <= 1e-3 else 'B2' if r <= 1e-2 else 'B3' if r <= 3e-2 else 'B4' if r <= .1 else 'B5' if r <= .3 else 'B6' if r <= 2 else 'B7'
def score(name, pred, key):
    rel = [(pred(r) - r[key]) / r[key] for r in held]; rho = [abs(x) for x in rel]
    h = {}; [h.__setitem__(band(x), h.get(band(x), 0) + 1) for x in rho]
    ratio = [pred(r) / r[key] for r in held]; q = max(1, len(held) // 5)
    med = st.median(rho)
    verdict = 'CARRIES BINDING (B3 or better)' if med <= .03 else 'EXCLUDED (median > 10%)' if med > .10 else 'B4: order-correct, structure missing'
    print(f'  {name:34s} held-out n={len(held)} median rho {100*med:6.2f}%  ratio CV {100*st.pstdev(ratio)/st.mean(ratio):5.2f}%  first/last A-quintile ratio {st.mean(ratio[:q]):.4f}/{st.mean(ratio[-q:]):.4f}  bands {dict(sorted(h.items()))} -> {verdict}')
    return med
for key, lab in (('Bn', 'native {A p, N e}'), ('Bp', '{Z p, N n}')):
    print(f'\n=== list: {lab}')
    K, Lp = fit([(mp * r['S'], r['loops']) for r in cal], [r[key] for r in cal])
    c, = fit([(r['A'],) for r in cal], [r[key] for r in cal])
    print(f'  CALIBRATED(2): K = kappa*Om_p = {K:.6f} fm ; L = {Lp:.4f} MeV/loop   |  null CALIBRATED(1): c = {c:.4f} MeV/nucleon')
    print(f'  read-off (not tested): kappa = K / 0.15538 fm = {K/0.15538:.4f}  (proton F 1, proton H 0.5, loop F 0.25, loop H 0.125)')
    for r in cal: print(f'    cal {r["Z"]:3d},{r["A"]:3d}: meas {r[key]:9.3f}  map {K*mp*r["S"]+Lp*r["loops"]:9.3f}  null {c*r["A"]:9.3f}')
    m1 = score('map: K*m_p*sum(1/d) + L*loops', lambda r: K * mp * r['S'] + Lp * r['loops'], key)
    m0 = score('null: c*A', lambda r: c * r['A'], key)
    print(f'  map beats null: {"YES" if m1 < m0 else "NO"} ({100*m1:.2f}% vs {100*m0:.2f}%)')
    # isotope-step sign check (map), all 250
    allr = sorted(rows, key=lambda r: (r['Z'], r['A'])); steps = bad = 0
    for a, b in zip(allr, allr[1:]):
        if a['Z'] == b['Z']:
            steps += 1; bad += (K * mp * b['S'] + Lp * b['loops']) < (K * mp * a['S'] + Lp * a['loops'])
    print(f'  isotope steps where the map binding falls: {bad} of {steps}')
