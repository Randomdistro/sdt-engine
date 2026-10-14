"""NP12 Round 2 (2026-10-14): chain growth of the boundary radius against H2 = R_p (A/eta_eff(f_t))^(1/3).
Registration: NP12_RESET_ASSESSMENT_2026-10-14.md sections 0-2 (written before this file existed).
Run from the repository root: python -I Investigations/05_Nuclear_Physics/NP12_Nuclear_Charge_Radius_Scaling/np12_reset_2.py
Author: J. C. Harvey, Melbourne."""
import csv, math, statistics as st

RP = 8.414e-1   # fm (laws.hpp measured::R_p = 8.414e-16 m)
ETA_CP = math.pi / math.sqrt(18.0)
SQ35 = 1.0   # Amendment 1: the baseline R_p (A/eta)^(1/3) is compared with the RMS radius directly (no edge-to-RMS factor)

rows = []
for r in csv.DictReader(open('Datasets/nuclear/IAEA_ground_states_radii.csv', encoding='utf-8', errors='replace')):
    try:
        z = int(r['z']); n = int(r['n']); R = float(r['radius'])
    except (ValueError, KeyError):
        continue
    if z >= 1 and R > 0:
        rows.append((z, n, z + n, R))
print('[V0] radii rows with Z >= 1: %d (expected 908) -> %s' % (len(rows), 'met' if len(rows) == 908 else 'DIFFERS'))
dev = [(SQ35 * RP * (A / ETA_CP) ** (1 / 3.0) - R) / R for z, n, A, R in rows]
rms = math.sqrt(sum(d * d for d in dev) / len(dev))
print('[V1] baseline R = R_p (A/eta_cp)^(1/3) against the RMS radius: RMS relative deviation %.2f%% (target 4.96 +- 0.3) -> %s' % (100 * rms, 'met' if abs(100 * rms - 4.96) <= 0.3 else 'NOT MET'))
bz = {}
for z, n, A, R in rows:
    bz.setdefault(z, []).append((n, A, R))
chains = {z: sorted(v) for z, v in bz.items() if len(v) >= 5}
print('[V2] elements with >= 5 isotopes having a radius: %d (expected 60)' % len(chains))
Gm = []; Gn = []; spans = []
for z, v in chains.items():
    (n0, A0, R0), (n1, A1, R1) = v[0], v[-1]
    dn = n1 - n0
    Gm.append((R1 / R0 - 1) * 15.0 / dn); Gn.append(((A1 / A0) ** (1 / 3.0) - 1) * 15.0 / dn); spans.append(dn)
print('     mean span dN = %.1f ; mean growth normalised to dN = 15: measured %.2f%% (prompt 2.36), A^(1/3) null %.2f%% (prompt 5.10) ; null/measured %.2f (prompt 2.16)' % (st.mean(spans), 100 * st.mean(Gm), 100 * st.mean(Gn), st.mean(Gn) / st.mean(Gm)))
v2 = abs(100 * st.mean(Gm) - 2.36) <= 0.5 and abs(100 * st.mean(Gn) - 5.10) <= 0.8 and abs(st.mean(Gn) / st.mean(Gm) / 2.16 - 1) <= 0.10
print('[V2] chain-growth definition reproduces the prompt: %s' % ('met' if v2 else 'NOT MET (definition differs; the H2 comparison below is on my definition and says so)'))


def ft(z, A):
    nt = A - 2 * z; nd = 3 * z - A - 2
    if nd < 0 or nt < 0 or z < 3:
        return None
    return nt / (nd + nt + 1.0)


def Rh2(z, A, etad):
    f = ft(z, A)
    if f is None:
        return None
    eta = etad + (ETA_CP - etad) * f
    return SQ35 * RP * (A / eta) ** (1 / 3.0)


def chain_growth_h2(etad):
    out = []
    for z, v in chains.items():
        (n0, A0, R0), (n1, A1, R1) = v[0], v[-1]
        a, b = Rh2(z, A0, etad), Rh2(z, A1, etad)
        if a is None or b is None:
            continue
        out.append((z, (b / a - 1) * 15.0 / (n1 - n0), (R1 / R0 - 1) * 15.0 / (n1 - n0)))
    return out


used = chain_growth_h2(0.5)
print('chains usable by H2 (both endpoints inside the grammar, Z >= 3): %d of %d ; excluded %d' % (len(used), len(chains), len(chains) - len(used)))
print('\nPer-chain growth normalised to dN = 15: median over chains of G_H2/G_meas and of |G_H2 - G_meas|/G_meas, versus eta_d (eta_cp = %.4f)' % ETA_CP)
print('  eta_d    median ratio    median |error|')
grid = [0.40 + 0.02 * i for i in range(0, 18)] + [ETA_CP]
for e in grid:
    u = chain_growth_h2(e)
    rat = [g / m for z, g, m in u if m != 0]
    err = [abs(g - m) / abs(m) for z, g, m in u if m != 0]
    print('  %.4f   %10.3f   %12.3f' % (e, st.median(rat), st.median(err)))
lo, hi = 0.30, ETA_CP - 1e-9
f = lambda e: st.median([g / m for z, g, m in chain_growth_h2(e) if m != 0]) - 1.0
flo, fhi = f(lo), f(hi)
print('\nmedian ratio at eta_d = 0.30: %.3f ; at eta_cp: %.3f' % (flo + 1, fhi + 1))
if flo * fhi < 0:
    for _ in range(100):
        mid = 0.5 * (lo + hi)
        if f(lo) * f(mid) <= 0:
            hi = mid
        else:
            lo = mid
    req = 0.5 * (lo + hi)
    e_lo, e_hi = (RP / 1.08) ** 3, (RP / 1.02) ** 3
    print('REQUIRED eta_d (median ratio = 1; a target for the owed derivation, not a result): %.4f ; r0 at the deuteron end = R_p/eta_d^(1/3) = %.4f fm ; NP30 bracket eta_d in [%.4f, %.4f] (r0 1.08..1.02 fm): %s' % (req, RP / req ** (1 / 3.0), e_lo, e_hi, 'INSIDE' if e_lo <= req <= e_hi else 'OUTSIDE'))
    u = chain_growth_h2(req)
    ms = [g for z, g, m in u]; mm = [m for z, g, m in u]
    mx = sum(ms) / len(ms); my = sum(mm) / len(mm)
    c = sum((a - mx) * (b - my) for a, b in zip(ms, mm)) / math.sqrt(sum((a - mx) ** 2 for a in ms) * sum((b - my) ** 2 for b in mm))
    print('shape residual at the required eta_d: per-chain correlation of model and measured growth %.3f over %d chains; median |error| %.1f%%' % (c, len(u), 100 * st.median([abs(g - m) / abs(m) for z, g, m in u if m != 0])))
    for e in (e_lo, e_hi):
        u2 = chain_growth_h2(e)
        print('at the NP30 bracket end eta_d = %.4f: median ratio %.3f, median |error| %.1f%% (gate B3 <= 3%%: %s; information only)' % (e, st.median([g / m for z, g, m in u2 if m != 0]), 100 * st.median([abs(g - m) / abs(m) for z, g, m in u2 if m != 0]), 'met' if st.median([abs(g - m) / abs(m) for z, g, m in u2 if m != 0]) <= 0.03 else 'NOT MET'))
else:
    print('the median ratio does not cross 1 on [0.30, eta_cp): no required eta_d exists in the form')
