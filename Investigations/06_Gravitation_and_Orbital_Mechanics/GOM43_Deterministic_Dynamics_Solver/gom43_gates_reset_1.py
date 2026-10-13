"""GOM43 subset gates (2026-10-13): K0-K3, N1, R1 against the existing solver binary (no rebuild).
Registration: GOM43_RESET_ASSESSMENT_2026-10-13.md sections 0-3 (written before this file existed).
Run from the repository root: python -I Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/gom43_gates_reset_1.py <work_dir>
(work_dir: an empty directory for the generated case files.)
Author: J. C. Harvey, Melbourne."""
import hashlib, json, math, os, subprocess, sys

G = 'Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/'
EXE = G + 'build-gom43/Release/sdt-dynamics-solver.exe'
SMOKE = G + 'build-gom43/Release/sdt-dynamics-c-api-smoke.exe'
work = sys.argv[1]
os.makedirs(work, exist_ok=True)
C = 299792458.0


def run(path):
    p = subprocess.run([EXE, path], capture_output=True)
    return p.returncode, p.stdout


def write(name, obj):
    path = os.path.join(work, name)
    with open(path, 'w', encoding='utf-8') as f:
        f.write(obj if isinstance(obj, str) else json.dumps(obj))
    return path


base = json.load(open(G + 'examples/circular-pair.sdtcase.json'))

# ---- K0 ----
print('K0 parser rejection (each must return invalid_case and execute no step):')
cases = {}
cases['invalid_json'] = '{"contract_version": '
b = json.loads(json.dumps(base)); b['contract_version'] = '9.9.9'; cases['unsupported_version'] = b
b = json.loads(json.dumps(base)); b['problem_class'] = 'nonsense'; cases['unknown_problem_class'] = b
b = json.loads(json.dumps(base)); b['timestep_s'] = -1; cases['nonpositive_timestep'] = b
b = json.loads(json.dumps(base)); b['duration_s'] = 100.5; cases['fractional_step_count'] = b
b = json.loads(json.dumps(base)); b['mystery_member'] = 1; cases['unknown_member'] = b
b = json.loads(json.dumps(base)); b['bodies'][1]['id'] = b['bodies'][0]['id']; cases['duplicate_ids'] = b
b = json.loads(json.dumps(base)); b['record_every_steps'] = 1000; cases['impossible_cadence'] = b
k0ok = 0
for name, obj in cases.items():
    rc, out = run(write('k0_' + name + '.json', obj))
    try:
        d = json.loads(out)
        st, ex = d.get('status'), d.get('executed_steps')
    except Exception:
        st, ex = 'unparseable', None
    ok = (st == 'invalid_case') and (ex in (0, None))
    k0ok += ok
    print('  %-24s exit %d status %-14s executed_steps %s -> %s' % (name, rc, st, ex, 'met' if ok else 'NOT MET'))
print('  K0: %d of %d met' % (k0ok, len(cases)))

# ---- K1 ----
p1 = G + 'examples/circular-pair.sdtcase.json'
a, b2 = run(p1)[1], run(p1)[1]
print('\nK1 replay determinism: two runs of the same case give byte-identical output: %s (%d bytes, sha256 %s)' % ('met' if a == b2 else 'NOT MET', len(a), hashlib.sha256(a).hexdigest()[:16]))

# ---- K2 ----
man = json.loads(subprocess.run([EXE, '--manifest'], capture_output=True).stdout)
laws = hashlib.sha256(open('Engine/include/sdt/laws.hpp', 'rb').read()).hexdigest()
import re
fields = {k: (k in man) for k in ('laws_sha256', 'build_id', 'contract_version', 'compiler', 'floating_point_policy')}
hexok = bool(re.fullmatch(r'[0-9a-f]{64}', man.get('laws_sha256', '')))
print('\nK2 provenance: fields present %s ; laws hash is 64 lowercase hex: %s' % (fields, hexok))
print('   manifest laws_sha256 %s ; SHA-256 of the current laws.hpp %s -> %s' % (man.get('laws_sha256'), laws, 'CURRENT' if man.get('laws_sha256') == laws else 'STALE (the binary was built against an earlier laws.hpp)'))
res = json.loads(a)
print('   result provenance: %s ; solver %s' % (res.get('provenance'), res.get('solver')))

# ---- K3 ----
sm = subprocess.run([SMOKE], capture_output=True)
print('\nK3 C ABI smoke executable: exit %d ; stdout %d bytes, begins %r' % (sm.returncode, len(sm.stdout), sm.stdout[:80]))

# ---- N1 ----
k1, k2 = base['bodies'][0]['koppa_m'], base['bodies'][1]['koppa_m']
r = 1.0e9
vrel = math.sqrt(C * C * (k1 + k2) / r)
P = 2 * math.pi * r / vrel
dt = P / 2000.0
steps = 200000
n1 = json.loads(json.dumps(base))
n1['case_id'] = 'n1-circular-pair'
n1['bodies'][0]['position_m'] = [-r * k2 / (k1 + k2), 0, 0]; n1['bodies'][1]['position_m'] = [r * k1 / (k1 + k2), 0, 0]
n1['bodies'][0]['velocity_m_s'] = [0, -vrel * k2 / (k1 + k2), 0]; n1['bodies'][1]['velocity_m_s'] = [0, vrel * k1 / (k1 + k2), 0]
n1['timestep_s'] = dt; n1['duration_s'] = dt * steps; n1['record_every_steps'] = 2000
n1['gates'] = [{'id': 'energy', 'metric': 'relative_energy_drift', 'relation': '<=', 'limit': 5e-6}]
rc, out = run(write('n1.json', n1))
try:
    d = json.loads(out)
except Exception:
    d = {}
print('\nN1 circular pair: P = %.6e s ; dt = P/2000 = %.6e s ; steps %d ; solver status %s executed_steps %s' % (P, dt, steps, d.get('status'), d.get('executed_steps')))
if d.get('trajectory'):
    tr = d['trajectory']
    def sep(s): return math.dist(s['states'][0]['position_m'], s['states'][1]['position_m'])
    def en(s):
        v1, v2 = s['states'][0]['velocity_m_s'], s['states'][1]['velocity_m_s']
        return 0.5 * k1 * sum(x * x for x in v1) + 0.5 * k2 * sum(x * x for x in v2) - C * C * k1 * k2 / sep(s)
    s0 = sep(tr[0]); e0 = en(tr[0])
    dr = max(abs(sep(s) - s0) / s0 for s in tr); de = max(abs(en(s) - e0) / abs(e0) for s in tr)
    print('   records %d ; max relative separation drift %.3e (gate 5e-5: %s) ; max relative energy drift (independent) %.3e (gate 5e-6: %s) ; solver diagnostic relative_energy_drift %s' % (len(tr), dr, 'met' if dr <= 5e-5 else 'NOT MET', de, 'met' if de <= 5e-6 else 'NOT MET', d.get('diagnostics', {}).get('relative_energy_drift')))


# ---- R1 ----
def pend(name, length, anchor_y, inertia, theta0, cx):
    c = json.load(open(G + 'examples/simple-pendulum.sdtcase.json'))
    c['case_id'] = name
    x, y = cx * math.sin(theta0), -cx * math.cos(theta0)
    L = c['links'][0]
    L['position_m'] = [x, y, 0]; L['quaternion_wxyz'] = [math.cos(theta0 / 2), 0, 0, math.sin(theta0 / 2)]
    L['inertia_diagonal_kg_m2'] = inertia; L['length_m'] = length
    c['joints'][0]['child_anchor_m'] = [0, anchor_y, 0]
    c['timestep_s'] = 5e-4; c['duration_s'] = 8.0; c['record_every_steps'] = 20
    return c


def period(tr):
    th = [(s['time_s'], math.atan2(s['states'][0]['position_m'][0], -s['states'][0]['position_m'][1])) for s in tr]
    ups = []
    for (t0, a0), (t1, a1) in zip(th, th[1:]):
        if a0 < 0 <= a1:
            ups.append(t0 + (t1 - t0) * (-a0) / (a1 - a0))
    if len(ups) < 2:
        return None, len(ups)
    return (ups[-1] - ups[0]) / (len(ups) - 1), len(ups)


g = 9.80665
for label, (length, anchor_y, inertia, cx) in (('R1 point bob at 1 m (link 2 m, centre 1 m from the pivot, inertia 1e-6)', (2.0, 1.0, [1e-6, 1e-6, 1e-6], 1.0)), ('control: uniform rod (L = 1 m, inertia 1/12), physical pendulum', (1.0, 0.5, [1.0 / 12, 1e-6, 1.0 / 12], 0.5))):
    c = pend('r1', length, anchor_y, inertia, 0.05, cx)
    rc, out = run(write('r1.json', c))
    try:
        d = json.loads(out)
    except Exception:
        d = {}
    T, n = period(d.get('trajectory', []))
    T0 = 2 * math.pi * math.sqrt(1.0 / g); Tr = 2 * math.pi * math.sqrt(2.0 / (3 * g))
    print('\n%s: status %s executed_steps %s ; upward zero crossings %s ; measured period %s s' % (label, d.get('status'), d.get('executed_steps'), n, ('%.6f' % T) if T else None))
    if T:
        print('   simple-pendulum T0 = %.6f s (relative difference %+.3e ; gate 2e-3: %s) ; uniform-rod physical-pendulum period 2pi sqrt(2L/3g) = %.6f s (relative difference %+.3e)' % (T0, T / T0 - 1, 'met' if abs(T / T0 - 1) <= 2e-3 else 'NOT MET', Tr, T / Tr - 1))
print('\nNOT RUN in this pass: N0, N2-N9, R0, R2-R6 (the instrument is not re-qualified by this record).')
