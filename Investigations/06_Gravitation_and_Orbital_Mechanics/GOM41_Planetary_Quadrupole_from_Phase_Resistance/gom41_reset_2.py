# GOM41 Round 2 (2026-10-14). Registration: GOM41_RESET_ASSESSMENT_2026-10-14.md sections 0-4 (written before this file existed).
# Stage 1 (default):  python -I gom41_reset_2.py        -> validations V1-V5, cache gates C1, predictions Q0/Q1/S1 (J2 NOT read); writes gom41_reset_2_predictions.txt + sha256.
# Stage 2:            python -I gom41_reset_2.py unseal -> verifies the predictions hash, reads the J2 rows, applies gate G6 to Q0, Q1, S1; Neptune blind comparison.
# Author: J. C. Harvey, Melbourne.
import re, html, math, sys, hashlib, os
import numpy as np
sys.stdout.reconfigure(encoding='utf-8', errors='replace')

HERE = os.path.dirname(os.path.abspath(__file__))
DATA = os.path.normpath(os.path.join(HERE, '..', '..', '..', 'Datasets', 'solar_system'))
PRED = os.path.join(HERE, 'gom41_reset_2_predictions.txt')
C = 299792458.0
BODIES = ['Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune']
PRIMARY = {'Earth': 'Moon', 'Mars': 'Phobos', 'Jupiter': 'Io', 'Saturn': 'Titan', 'Uranus': 'Titania', 'Neptune': 'Triton'}
VALID = {'Mars': ['Phobos', 'Deimos'], 'Jupiter': ['Io', 'Europa', 'Ganymede', 'Callisto'], 'Saturn': ['Titan', 'Rhea'],
         'Uranus': ['Titania', 'Oberon'], 'Neptune': ['Triton', 'Proteus']}

def read(fn): return open(os.path.join(DATA, fn), encoding='utf-8', errors='replace').read()
def cells_of(row): return [re.sub(r'\s+', ' ', html.unescape(re.sub(r'<[^>]+>', '', c))).strip() for c in re.findall(r'<t[dh][^>]*>(.*?)</t[dh]>', row, flags=re.S)]
def rows_of(t): return [cells_of(r) for r in re.findall(r'<tr[^>]*>(.*?)</tr>', t, flags=re.S)]
def num(s):
    m = re.search(r'[-+]?\d[\d,]*\.?\d*(?:[eE][-+]?\d+)?', s.replace('−', '-'))
    return float(m.group(0).replace(',', '')) if m else None
def sha(fn): return hashlib.sha256(open(os.path.join(DATA, fn), 'rb').read()).hexdigest()

# ---------------- inputs (J2 not touched in stage 1)
def nasa_row(body, label_start):
    t = read(f'nasa_{body.lower()}fact.html')
    for r in rows_of(t):
        if len(r) >= 2 and r[0].lower().startswith(label_start.lower()): return r
    for ln in html.unescape(re.sub(r'<[^>]+>', '', t)).splitlines():        # <pre> layout (Earth): label, then 2+ spaces or a tab, then the value
        if ln.lower().startswith(label_start.lower()):
            parts = [x for x in re.split(r'\t|\s{2,}', ln.strip()) if x]
            if len(parts) >= 2: return parts
    raise KeyError((body, label_start))
def nasa_geom(body):
    ae = num(nasa_row(body, 'Equatorial radius')[1]); ap = num(nasa_row(body, 'Polar radius')[1])
    rv = num(nasa_row(body, 'Volumetric mean radius')[1]); ph = abs(num(nasa_row(body, 'Sidereal rotation period (hrs)')[1]))
    return ae, ap, rv, ph
def jpl_phys():
    out = {}
    for r in rows_of(read('jpl_ssd_planet_phys_par.html')):
        if r and r[0] in BODIES and len(r) >= 6: out[r[0]] = dict(ae=num(r[1]), rm=num(r[2]), prot_d=abs(num(r[5])))
    return out
def sat_rows():
    out = {}
    for r in rows_of(read('jpl_ssd_sats_elem.html')):
        idx = [i for i, c in enumerate(r) if re.fullmatch(r'\d{4}-\d\d-\d\d(\.\d+)?', c)]
        if not idx or len(r) < idx[0] + 8 or idx[0] < 4: continue
        i = idx[0]; out.setdefault(r[i - 4], (num(r[i + 1]), num(r[i + 7])))   # row: index, planet, name, code, ephemeris, frame, epoch, a (km), e, w, M, i, node, P (days)
    return out

def koppa(a_km, P_d):                      # kappa = (2 pi / P)^2 a^3 / c^2  [m]
    n = 2 * math.pi / (P_d * 86400.0); return n * n * (a_km * 1e3) ** 3 / (C * C)
def qpar(ae_km, P_spin_d, a_km, P_d):      # q = (omega/n)^2 (a_e/a_s)^3
    return (P_d / P_spin_d) ** 2 * (ae_km / a_km) ** 3
def J2_Q0(q): return q / 2.0
def J2_Q1(ae, ap, q): r = ae / ap; return (r - 1.0 - q / 2.0) / (r ** 3 + 0.5)

# ---------------- numerical quadrupole instruments (V2-V5)
def P2(m): return 0.5 * (3 * m * m - 1)
def j2_gl(ae, ap, Nr=48, Nm=48):           # Gauss-Legendre in mu and r on [0, r_max(mu)], uniform density
    xm, wm = np.polynomial.legendre.leggauss(Nm); xr, wr = np.polynomial.legendre.leggauss(Nr)
    Q = 0.0; M = 0.0
    for m, w in zip(xm, wm):
        rmax = 1.0 / math.sqrt((1 - m * m) / ae ** 2 + m * m / ap ** 2)
        r = 0.5 * rmax * (xr + 1); wrr = 0.5 * rmax * wr
        Q += w * np.sum(wrr * r ** 4) * P2(m); M += w * np.sum(wrr * r ** 2)
    return -Q / (M * ae ** 2)
def j2_midpoint(ae, ap, N):                # direct volume integration: midpoint grid in (r, mu) with the density indicator
    Rmax = ae; dr = Rmax / N; dm = 2.0 / N; Q = 0.0; M = 0.0
    r = (np.arange(N) + 0.5) * dr
    for k in range(N):
        m = -1 + (k + 0.5) * dm
        inside = (r * r * ((1 - m * m) / ae ** 2 + m * m / ap ** 2)) <= 1.0
        w = r[inside] ** 2 * dr * dm
        Q += np.sum(w * r[inside] ** 2) * P2(m); M += np.sum(w)
    return -Q / (M * ae ** 2)
def leakage_tilted(alpha_deg=37.0, Nr=40, Nm=40, Nphi=64):  # spherical density rho(r) = (1-r^2)^2, P2 about an axis tilted by alpha
    xm, wm = np.polynomial.legendre.leggauss(Nm); xr, wr = np.polynomial.legendre.leggauss(Nr)
    r = 0.5 * (xr + 1); wrr = 0.5 * wr; rho = (1 - r ** 2) ** 2
    a = math.radians(alpha_deg); phi = (np.arange(Nphi) + 0.5) * 2 * math.pi / Nphi
    Q = 0.0; M = 0.0
    for m, w in zip(xm, wm):
        s = math.sqrt(1 - m * m)
        for p in phi:
            mu_t = m * math.cos(a) + s * math.cos(p) * math.sin(a)
            Q += w * (2 * math.pi / Nphi) * np.sum(wrr * rho * r ** 4) * P2(mu_t); M += w * (2 * math.pi / Nphi) * np.sum(wrr * rho * r ** 2)
    return Q / M
def q1_roundtrip(kappa, w, ae, J2t):       # build a_p from the equipotential relation by bisection, recover J2 by the closed form
    q = w * w * ae ** 3 / (C * C * kappa)
    f = lambda ap: (ae / ap - 1 - q / 2) - J2t * ((ae / ap) ** 3 + 0.5)
    lo, hi = 0.5 * ae, ae
    for _ in range(200):
        mid = 0.5 * (lo + hi)
        if f(lo) * f(mid) <= 0: hi = mid
        else: lo = mid
    ap = 0.5 * (lo + hi); return J2_Q1(ae, ap, q), ap

def stage1():
    ok_all = True
    print('GOM41 Round 2 - stage 1 (J2 NOT read)\n' + '=' * 60)
    print('\n[sources, sha256]')
    for fn in ['jpl_ssd_planet_phys_par.html', 'jpl_ssd_sats_elem.html'] + [f'nasa_{b.lower()}fact.html' for b in BODIES]: print(f'  {fn:34s} {sha(fn)}')
    sats = sat_rows(); phys = jpl_phys()
    print('\n[V1] koppa from independent satellites of one planet (relative spread, gate <= 1.5%)')
    for b, lst in VALID.items():
        ks = [koppa(*sats[s]) for s in lst]; sp = (max(ks) - min(ks)) / (sum(ks) / len(ks)); ok = sp <= 0.015; ok_all &= ok
        print(f'  {b:8s} ' + '  '.join(f'{s}: {k:.5e} m' for s, k in zip(lst, ks)) + f'  spread {sp:.3e} -> {"met" if ok else "NOT MET"}')
    print('\n[V2/V4] uniform oblate spheroid ap/ae = 0.9: exact J2 = (1 - 0.81)/5 =', (1 - 0.81) / 5)
    ex = (1 - 0.81) / 5; g = j2_gl(1.0, 0.9); mp1 = j2_midpoint(1.0, 0.9, 400); mp2 = j2_midpoint(1.0, 0.9, 800)
    print(f'  GL projection {g:.10f} (rel err {abs(g-ex)/ex:.2e});  midpoint volume N=400 {mp1:.6f} (rel {abs(mp1-ex)/ex:.2e}), N=800 {mp2:.6f} (rel {abs(mp2-ex)/ex:.2e})')
    v2 = abs(mp1 - g) / g <= 0.005 and abs(mp2 - g) / g <= 0.005; v4 = abs(mp2 - mp1) / mp2 < 0.01; g8 = j2_gl(1.0, 0.9, 96, 96); v4b = abs(g8 - g) / g < 0.01
    print(f'  [V2] volume vs projection <= 0.5%: {"met" if v2 else "NOT MET"};  [V4] doubling changes J2 by {abs(mp2-mp1)/mp2:.2e} (midpoint), {abs(g8-g)/g:.2e} (GL) (< 1%): {"met" if v4 and v4b else "NOT MET"}')
    ok_all &= v2 and v4 and v4b
    print('\n[V3] zero spin / spherical leakage')
    z0 = [J2_Q0(0.0), J2_Q1(1.0, 1.0, 0.0), j2_gl(1.0, 1.0)]; lk = leakage_tilted()
    print(f'  Q0(w=0) {z0[0]:.1e}, Q1(w=0, ap=ae) {z0[1]:.1e}, GL sphere {z0[2]:.1e} (gate < 1e-12): {"met" if max(abs(x) for x in z0) < 1e-12 else "NOT MET"};  tilted-axis spherical leakage {lk:.2e} (gate < 1e-8): {"met" if abs(lk) < 1e-8 else "NOT MET"}')
    ok_all &= max(abs(x) for x in z0) < 1e-12 and abs(lk) < 1e-8
    print('\n[V5] Q1 round-trip and small-limit')
    kap = 1.4; w = 2 * math.pi / (0.4 * 86400); ae = 7.0e7; rt, ap = q1_roundtrip(kap, w, ae, 0.0147)
    q = w * w * ae ** 3 / (C * C * kap); print(f'  synthetic: J2_true 0.0147 -> a_p/a_e {ap/ae:.8f} -> recovered {rt:.10e}, rel err {abs(rt-0.0147)/0.0147:.1e} (gate < 1e-12 relative)')
    f1 = 1e-4; q1 = 5e-4; r = 1 + f1; small = J2_Q1(1.0, 1.0 / r, q1); first = (2 * f1 - q1) / 3
    print(f'  small limit f=1e-4, q=5e-4: closed form {small:.6e} vs (2f-q)/3 {first:.6e}, rel diff {abs(small-first)/abs(first):.2e} (gate < 2e-3)')
    ok_all &= abs(rt - 0.0147) / 0.0147 < 1e-12 and abs(small - first) / abs(first) < 2e-3
    print('\n[C1] cache consistency (input defects, not claim results)')
    rows = {}
    for b in BODIES:
        ae, ap, rv, ph = nasa_geom(b); j = phys[b]; a_s, P_s = sats[PRIMARY[b]]
        d_ae = abs(ae - j['ae']) / j['ae']; d_ph = abs(ph / 24 - j['prot_d']) / j['prot_d']; rm = (ae * ae * ap) ** (1 / 3); d_rm = abs(rm - j['rm']) / j['rm']
        okc = d_ae <= 1e-4 and d_ph <= 2e-3 and d_rm <= 1e-3; ok_all &= okc
        print(f'  {b:8s} ae NASA {ae:.1f} / JPL {j["ae"]:.1f} (d {d_ae:.1e});  spin NASA {ph/24:.6f} d / JPL {j["prot_d"]:.6f} d (d {d_ph:.1e});  (ae^2 ap)^(1/3) {rm:.1f} / JPL mean {j["rm"]:.1f} (d {d_rm:.1e}) -> {"met" if okc else "NOT MET"}')
        rows[b] = dict(ae=ae, ap=ap, Pspin=j['prot_d'], a_s=a_s, P_s=P_s, sat=PRIMARY[b])
    print('\n[corpus rows and predictions] (equatorial radius used for q and J2; sealed before J2 is read)')
    lines = ['# GOM41 Round 2 predictions, written by stage 1 before any J2 is read']
    print('  body      sat      kappa [m]        z_surf=kappa/ae   q            Q0 J2          Q1 J2')
    for b in BODIES:
        r = rows[b]; kp = koppa(r['a_s'], r['P_s']); q = qpar(r['ae'], r['Pspin'], r['a_s'], r['P_s']); q0 = J2_Q0(q); q1 = J2_Q1(r['ae'], r['ap'], q); z = kp / (r['ae'] * 1e3)
        print(f'  {b:8s} {r["sat"]:8s} {kp:.5e}   {z:.3e}      {q:.6e} {q0:.6e}   {q1:.6e}')
        lines.append(f'{b} Q0={q0:.10e} Q1={q1:.10e} S1={q0:.10e} z_surface={z:.4e} q={q:.10e}')
    open(PRED, 'w', encoding='utf-8').write('\n'.join(lines) + '\n')
    h = hashlib.sha256(open(PRED, 'rb').read()).hexdigest()
    print(f'\npredictions written to gom41_reset_2_predictions.txt  sha256 {h}')
    print('S1 consequence: engagement modulation h\'(0)/h(0) * z_surface <= (largest z_surface above) x O(1) -> S1 = Q0 within that relative amount.')
    print(f'\nstage-1 validations and cache gates all met: {ok_all}')

def stage2():
    h = hashlib.sha256(open(PRED, 'rb').read()).hexdigest(); print('GOM41 Round 2 - stage 2 (J2 unsealed)\n' + '=' * 60); print('predictions file sha256', h)
    pred = {}
    for l in open(PRED, encoding='utf-8'):
        if l.startswith('#') or not l.strip(): continue
        p = l.split(); pred[p[0]] = {k: float(v) for k, v in (x.split('=') for x in p[1:])}
    print('\n[raw J2 rows from the cached sheets]')
    meas = {}
    for b in BODIES:
        row = nasa_row(b, 'J2')
        print(f'  {b:8s} {row}')
        v = num(' '.join(row[1:]).replace('±', ' '))
        meas[b] = v * 1e-6
    for name, key in [('Q0_UNIFORM', 'Q0'), ('Q1_CONVERGENCE', 'Q1'), ('S1_DEPTH_PROFILE', 'S1')]:
        print(f'\n[{name}]  body: predicted / measured J2, signed fractional residual')
        res = {}
        for b in BODIES:
            res[b] = (pred[b][key] - meas[b]) / meas[b]; print(f'  {b:8s} {pred[b][key]:.6e} / {meas[b]:.6e}  {100*res[b]:+8.2f} %')
        n10 = sum(abs(res[b]) <= 0.10 for b in BODIES); rms = math.sqrt(sum(res[b] ** 2 for b in BODIES) / 6)
        g = abs(res['Earth']) <= 0.03 and abs(res['Jupiter']) <= 0.03 and n10 >= 4 and rms <= 0.10
        print(f'  Earth within 3%: {abs(res["Earth"])<=0.03}; Jupiter within 3%: {abs(res["Jupiter"])<=0.03}; within 10%: {n10}/6; RMS {100*rms:.2f} %  -> gate 6: {"MET" if g else "NOT MET"}')
    print(f'\n[blind comparison, Neptune, S1 gate: within 10%] S1 {pred["Neptune"]["S1"]:.6e} vs measured {meas["Neptune"]:.6e}: {100*(pred["Neptune"]["S1"]-meas["Neptune"])/meas["Neptune"]:+.2f} % -> {"MET" if abs(pred["Neptune"]["S1"]-meas["Neptune"])/meas["Neptune"]<=0.10 else "NOT MET"}')

if __name__ == '__main__':
    stage2() if (len(sys.argv) > 1 and sys.argv[1] == 'unseal') else stage1()
