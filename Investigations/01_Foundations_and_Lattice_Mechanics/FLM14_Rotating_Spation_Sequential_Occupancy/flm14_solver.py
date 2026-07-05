"""
FLM14 - flm14_solver.py - RULE-FORM-3: bond-local geared rotation + ENTRAINMENT.
J. C. Harvey, Melbourne - 2026-07-04 (run 2).

Instrument committed in RUN_LOG.md ADJ-4 / ADJ-5 / ADJ-6 BEFORE this file was written.
Committed gates UNMOVED: P1-G3 anisotropy ratio <= 1.2 (geared/ungeared, same geometry);
P2-G1 emergent exponent reported as a beta SCAN (no committed value; fitting beta to a
target = FISHED); P2-G2 closure drift < 1%; F6 one rule throughout; R-Born: no cos^2 or
psi^2 weighting inserted anywhere.

Rule-form ladder (committed baselines):
  form-1  global clock           : x7.47  KILLED (run 1, flm14_rotor_tour.py)
  form-2  bond-local rel. phase  : x2.88  FAIL   (ADJ-3, old jittered-FCC instrument)
  form-3  bond-local + entrainment (THIS RUN, FLM10-grade CRN, N=1000): must beat 1.2.

THE ONE RULE (F6), used identically in P1 and P2:
  phase       phi_i(t) = base_i + omega_i * t + dphi_i(t)
  rate        omega_i  = OMEGA0 * z_i / <z>       (per-site rate from local coordination)
  window      (g = -1 contact gearing) bond i-j OPEN  iff  c_ij = (phi_i + phi_j) mod 1 < W
  ENTRAINMENT at contact formation the pulse kicks the RECEIVER once:
                  dphi_j += -beta * wrap(c_ij)    (pull toward the gearing lock c = 0)
  wake decay  dphi -> dphi * exp(-dt / T_W)
Nothing else. beta is the DECLARED exploratory parameter (FLM03's open coefficient),
scanned and reported as a scan. Lattice generation is FLM10's (diamond seed + WWW bond
switches + Keating relaxation) - reused, not reinvented.
"""
import numpy as np, heapq, itertools, math, sys, time
from scipy.optimize import minimize
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass

# ---------------- committed instrument constants (ADJ-4; run-1 continuity) ----------------
OMEGA0 = 0.37          # base rotation rate, turns/tick (run 1)
W      = 0.5           # hand-off window duty (run 1)
T_W    = 27.0          # wake decay, ticks (= 10 rotor periods; ADJ-4, NOT scanned)
BETA_GRID_A = [0.0, 0.05, 0.10, 0.20, 0.40, 0.80, 1.00]   # 0.0 = form-2 control
BETA_GRID_B = [0.02, 0.05, 0.10, 0.20, 0.40, 0.80]
GLASS_SEEDS = [21, 22, 23]
TOUR_SEEDS  = [1, 2, 3]

def wrap(c):                       # signed distance of c (in [0,1)) to the lock point 0
    return c - math.floor(c + 0.5)

# =================== FLM10 lattice machinery (reused from flm10_phase1_isotropy.py) =======
K_ALPHA, K_BETA = 1.0, 0.285       # Keating stretch/bend (Si-like; geometry class)

def diamond(n):
    basis = np.array([[0,0,0],[0,.5,.5],[.5,0,.5],[.5,.5,0],
                      [.25,.25,.25],[.25,.75,.75],[.75,.25,.75],[.75,.75,.25]])
    cells = np.array([[i,j,k] for i in range(n) for j in range(n) for k in range(n)])
    pos = (cells[:,None,:] + basis[None,:,:]).reshape(-1,3)
    return pos, float(n), np.sqrt(3)/4.0

def mic(dr, L): return dr - L*np.round(dr/L)

def build_bonds(pos, L, cutoff):
    N = len(pos); nbr = [[] for _ in range(N)]
    for i in range(N):
        dr = mic(pos - pos[i], L); r2 = np.einsum('ij,ij->i', dr, dr)
        for j in np.where((r2 < cutoff**2) & (np.arange(N) != i))[0]:
            if j > i: nbr[i].append(int(j)); nbr[j].append(int(i))
    return nbr

def bonds_angles(nbr):
    bonds = [(i,j) for i in range(len(nbr)) for j in nbr[i] if j > i]
    angs  = [(i,j,k) for i in range(len(nbr)) for a,j in enumerate(nbr[i]) for k in nbr[i][a+1:]]
    return np.array(bonds), np.array(angs)

def ring_lt5(nbr, u, v):
    su = set(nbr[u]); sv = set(nbr[v]); su.discard(v); sv.discard(u)
    if su & sv: return True
    for x in su:
        if set(nbr[x]) & sv: return True
    return False

def www_move(nbr, rng):
    N = len(nbr)
    for _ in range(300):
        a = int(rng.integers(N)); b = int(rng.choice(nbr[a]))
        nb_a = [x for x in nbr[a] if x != b]; nb_b = [x for x in nbr[b] if x != a]
        if not nb_a or not nb_b: continue
        c = int(rng.choice(nb_a)); e = int(rng.choice(nb_b))
        if len({a,b,c,e}) < 4 or e in nbr[a] or c in nbr[b]: continue
        new = [list(v) for v in nbr]
        new[a].remove(c); new[c].remove(a); new[b].remove(e); new[e].remove(b)
        new[a].append(e); new[e].append(a); new[b].append(c); new[c].append(b)
        if ring_lt5(new, a, e) or ring_lt5(new, b, c): continue
        return new
    return None

def keating_box(svec, Hbox, bonds, angs, d):
    s = svec.reshape(-1,3); g = np.zeros_like(s)
    cs = K_ALPHA*3/16/d**2; cb = K_BETA*3/8/d**2
    dsb = s[bonds[:,1]] - s[bonds[:,0]]; dsb -= np.round(dsb); rij = dsb @ Hbox.T
    sq = np.einsum('ij,ij->i', rij, rij); E = cs*np.sum((sq-d**2)**2)
    f = cs*4*(sq-d**2)[:,None]*rij
    np.add.at(g, bonds[:,1],  f @ Hbox); np.add.at(g, bonds[:,0], -f @ Hbox)
    dsj = s[angs[:,1]] - s[angs[:,0]]; dsj -= np.round(dsj); rj = dsj @ Hbox.T
    dsk = s[angs[:,2]] - s[angs[:,0]]; dsk -= np.round(dsk); rk = dsk @ Hbox.T
    pp = np.einsum('ij,ij->i', rj, rk); E += cb*np.sum((pp+d**2/3)**2)
    pref = cb*2*(pp+d**2/3)[:,None]; gj = pref*rk; gk = pref*rj; gi = -(gj+gk)
    np.add.at(g, angs[:,1], gj @ Hbox); np.add.at(g, angs[:,2], gk @ Hbox); np.add.at(g, angs[:,0], gi @ Hbox)
    return E, g.ravel()

def relax_box(s0, Hbox, bonds, angs, d, maxiter=400):
    res = minimize(keating_box, s0.ravel(), args=(Hbox,bonds,angs,d), jac=True,
                   method='L-BFGS-B', options={'maxiter':maxiter,'ftol':1e-14,'gtol':1e-9})
    return res.x.reshape(-1,3), res.fun

def make_amorphous_1000(n_sw, seed):
    """diamond(5) -> N=1000 CRN via WWW + Keating (ADJ-4: 500 attempted switches,
    anneal relax maxiter=100, final 2000). Returns pos, L, d, nbr, n_accepted."""
    rng = np.random.default_rng(seed)
    pos, L, d = diamond(5); nbr = build_bonds(pos, L, cutoff=0.55)
    s = pos/L; Hbox0 = L*np.eye(3)
    s,_ = relax_box(s, Hbox0, *bonds_angles(nbr), d, maxiter=200)
    E = keating_box(s.ravel(), Hbox0, *bonds_angles(nbr), d)[0]
    kT = 0.14; acc = 0
    for it in range(1, n_sw+1):
        new = www_move(nbr, rng)
        if new is None: continue
        bf, af = bonds_angles(new); st, Et = relax_box(s, Hbox0, bf, af, d, maxiter=100)
        if Et-E < 0 or rng.random() < np.exp(-(Et-E)/max(kT,1e-12)):
            nbr, s, E = new, st, Et; acc += 1
        if it % 80 == 0: kT *= 0.85
    s,_ = relax_box(s, Hbox0, *bonds_angles(nbr), d, maxiter=2000)
    return s*L, L, d, nbr, acc

# ============================ PART A - P1-G3 retest (rule-form-3) ==========================
def golden_dirs(n=24):
    i = np.arange(n) + 0.5
    z = 1 - 2*i/n; th = np.pi*(3-np.sqrt(5))*i; r = np.sqrt(1-z*z)
    return np.stack([r*np.cos(th), r*np.sin(th), z], axis=1)

def geometric_coordination(pos, L, dbar):
    N = len(pos); z = np.zeros(N, int); cut2 = (1.25*dbar)**2
    for i in range(N):
        dr = mic(pos - pos[i], L); r2 = np.einsum('ij,ij->i', dr, dr)
        z[i] = int(((r2 > 1e-12) & (r2 < cut2)).sum())
    return z

def run_front(pos, L, nbr, blen, omega, base, beta, geared, T_w=T_W):
    """Event-driven single front from the site nearest box centre. Returns
    (arrival times, mean wait per settled bond, n_rechecks)."""
    N = len(pos)
    arr = np.full(N, np.inf)
    dphi = np.zeros(N); tlast = np.zeros(N)
    ctr = itertools.count()
    src = int(np.argmin(np.einsum('ij,ij->i', pos - L/2, pos - L/2)))
    arr[src] = 0.0
    heap = []; first_contact = {}; waits = []; rechecks = 0
    def touch(k, t):
        dphi[k] *= math.exp(-(t - tlast[k]) / T_w); tlast[k] = t
    def send(i, t):
        for j in nbr[i]:
            if arr[j] == np.inf:
                heapq.heappush(heap, (t + blen[(i,j)], next(ctr), i, j, True))
    send(src, 0.0)
    while heap:
        t, _, i, j, is_contact = heapq.heappop(heap)
        if arr[j] != np.inf: continue
        if not geared:
            arr[j] = t; send(j, t); continue
        touch(i, t); touch(j, t)
        c = (base[i] + base[j] + dphi[i] + dphi[j] + (omega[i]+omega[j])*t) % 1.0
        if is_contact:
            first_contact[(i,j)] = t
            kick = -beta * wrap(c)
            dphi[j] += kick
            c = (c + kick) % 1.0
        else:
            rechecks += 1
        if c < W:
            arr[j] = t
            waits.append(t - first_contact[(i,j)])
            send(j, t)
        else:
            gap = (1.0 - c) / (omega[i] + omega[j])
            heapq.heappush(heap, (t + gap, next(ctr), i, j, False))
    mw = float(np.mean(waits)) if waits else 0.0
    return arr, mw, rechecks, src

def anisotropy(pos, L, src, arr, dbar, dirs, cosw=0.75, minsites=5):
    dr = mic(pos - pos[src], L); r = np.linalg.norm(dr, axis=1)
    ok = (r > 2.5*dbar) & (r < 0.42*L) & np.isfinite(arr) & (arr > 0)
    if ok.sum() < 40: return np.nan, 0
    u = dr[ok] / r[ok, None]; v = r[ok] / arr[ok]
    vs = []
    for dvec in dirs:
        m = u @ dvec >= cosw
        if m.sum() >= minsites: vs.append(v[m].mean())
    vs = np.array(vs)
    if len(vs) < 16: return np.nan, len(vs)
    return float(vs.std()/vs.mean()), len(vs)

def part_A():
    print("="*88)
    print("  PART A - P1-G3 RETEST: rule-form-3 (bond-local windows + entrainment)")
    print("  FLM10-grade CRN, N=1000, 3 glass seeds, 24 directions. Gate <= 1.2 (UNMOVED).")
    print("  Ladder baseline: form-1 x7.47 (KILLED) -> form-2 x2.88 (FAIL) -> form-3 = this.")
    print("="*88)
    dirs = golden_dirs(24)
    table = {b: [] for b in BETA_GRID_A}   # beta -> list of ratios over seeds
    aniso_un = []; mean_waits = {b: [] for b in BETA_GRID_A}
    anchor_worst = 0.0
    for seed in GLASS_SEEDS:
        t0 = time.time()
        pos, L, d, nbr, acc = make_amorphous_1000(500, seed)
        bonds,_ = bonds_angles(nbr)
        bl = np.linalg.norm(mic(pos[bonds[:,1]] - pos[bonds[:,0]], L), axis=1)
        dbar = float(np.median(bl))
        blen = {}
        for (i,j), l in zip(bonds, bl):
            blen[(int(i),int(j))] = float(l); blen[(int(j),int(i))] = float(l)
        z = geometric_coordination(pos, L, dbar)
        omega = OMEGA0 * z / z.mean()
        print(f"\n  glass seed {seed}: N={len(pos)}  accepted WWW switches={acc}  "
              f"bond length {bl.mean():.3f}+-{bl.std():.3f} (crystal {d:.3f})  "
              f"z(geom) min/mean/max = {z.min()}/{z.mean():.2f}/{z.max()}  "
              f"[{time.time()-t0:.0f}s]")
        rngp = np.random.default_rng(1000 + seed)
        base = rngp.random(len(pos))
        arr_u, _, _, src = run_front(pos, L, nbr, blen, omega, base, 0.0, geared=False)
        a_u, nd_u = anisotropy(pos, L, src, arr_u, dbar, dirs)
        aniso_un.append(a_u)
        print(f"    ungeared: anisotropy {a_u:.4f}  ({nd_u} valid directions)")
        for b in BETA_GRID_A:
            arr_g, mw, rck, _ = run_front(pos, L, nbr, blen, omega, base, b, geared=True)
            a_g, nd_g = anisotropy(pos, L, src, arr_g, dbar, dirs)
            ratio = a_g / a_u
            table[b].append(ratio); mean_waits[b].append(mw)
            print(f"    geared beta={b:4.2f}: anisotropy {a_g:.4f}  ratio {ratio:5.2f}  "
                  f"mean wait {mw:.3f}  rechecks {rck}  ({nd_g} dirs)")
            if b == 1.0:
                anchor_worst = max(anchor_worst, float(np.nanmax(np.abs(
                    np.where(np.isfinite(arr_g) & np.isfinite(arr_u), arr_g - arr_u, 0.0)))))
    print(f"\n  machinery anchor: beta=1 geared must equal ungeared exactly -> "
          f"max |t_g - t_u| = {anchor_worst:.2e}  [{'OK' if anchor_worst < 1e-9 else 'INSTRUMENT FAULT'}]")
    print("\n  P1-G3 SUMMARY (ratio geared/ungeared, mean +- std over 3 glass seeds; gate <= 1.2):")
    print("    beta     ratio            mean wait   verdict")
    pass_betas = []
    for b in BETA_GRID_A:
        r = np.array(table[b]); w = np.mean(mean_waits[b])
        verdict = "PASS" if r.mean() <= 1.2 else "FAIL"
        if r.mean() <= 1.2: pass_betas.append(b)
        tag = "  (= form-2 control on this instrument)" if b == 0.0 else ""
        print(f"    {b:4.2f}   {r.mean():5.2f} +- {r.std():4.2f}      {w:6.3f}     [{verdict}]{tag}")
    return table, pass_betas

# ===================== PART B - P2: structured tour around a heavy defect =================
def build_seats(seed):
    rng = np.random.default_rng(seed)
    rings = [(1.0, 8), (1.55, 13), (2.3, 21)]
    pts = []; ring_id = []
    for k, (rad, n) in enumerate(rings):
        th = 2*np.pi*(np.arange(n) + rng.uniform(-0.15, 0.15, n))/n + rng.uniform(0, 2*np.pi)
        for a in th:
            pts.append((rad*np.cos(a), rad*np.sin(a))); ring_id.append(k)
    pts = np.array(pts); ring_id = np.array(ring_id)
    edges = set()
    for k in range(3):
        idx = np.where(ring_id == k)[0]
        ang = np.arctan2(pts[idx,1], pts[idx,0]); order = idx[np.argsort(ang)]
        for a in range(len(order)):
            i, j = int(order[a]), int(order[(a+1) % len(order)])
            edges.add((min(i,j), max(i,j)))
    for k in range(2):
        src_i = np.where(ring_id == k)[0]; dst_i = np.where(ring_id == k+1)[0]
        for i in src_i:
            dd = np.linalg.norm(pts[dst_i] - pts[i], axis=1)
            for j in dst_i[np.argsort(dd)[:2]]:
                edges.add((min(int(i),int(j)), max(int(i),int(j))))
    N = len(pts); nbr = [[] for _ in range(N)]
    for i, j in sorted(edges): nbr[i].append(j); nbr[j].append(i)
    z = np.array([len(nbr[i]) for i in range(N)], float)
    z[ring_id == 0] += 1.0        # the heavy central defect is a bond-partner of ring 0
    return pts, nbr, z, ring_id

def run_tour(pts, nbr, z, beta, seed, hops=40000, T_w=T_W):
    N = len(pts); omega = OMEGA0 * z / z.mean()
    rng = np.random.default_rng(seed)
    base = rng.random(N)
    D = np.linalg.norm(pts[:,None,:] - pts[None,:,:], axis=2)
    dphi = np.zeros(N); tlast = np.zeros(N)
    dwell_sum = np.zeros(N); visits = np.zeros(N)
    amp_sum = np.zeros(N); amp_n = 0
    q3 = []; q4 = []
    s = int(np.argmin(np.linalg.norm(pts - pts[0], axis=1)))  # start on ring 0 seat
    t = 0.0; half = hops // 2; q34 = hops*3//4
    for h in range(hops):
        nb = nbr[s]
        for k in nb + [s]:
            dphi[k] *= math.exp(-(t - tlast[k]) / T_w); tlast[k] = t
        gaps = np.empty(len(nb))
        for a, j in enumerate(nb):
            c = (base[s] + base[j] + dphi[s] + dphi[j] + (omega[s]+omega[j])*t) % 1.0
            kick = -beta * wrap(c)
            dphi[j] += kick
            c = (c + kick) % 1.0
            gaps[a] = 0.0 if c < W else (1.0 - c) / (omega[s] + omega[j])
        a_star = int(np.argmin(gaps)); g = float(gaps[a_star]); j_star = nb[a_star]
        if h >= half:
            dwell_sum[s] += g; visits[s] += 1
            amp_sum += np.abs(dphi * np.exp(-(t - tlast) / T_w)); amp_n += 1
            (q3 if h < q34 else q4).append(g)
        t += g + D[s, j_star]
        s = j_star
    A = amp_sum / max(amp_n, 1)
    m3, m4 = np.mean(q3), np.mean(q4)
    drift = abs(m4 - m3) / max(0.5*(m3+m4), 1e-12)
    cover = float((visits > 0).mean())
    return dwell_sum, visits, A, drift, cover

def fit_exponent(y, A):
    """Committed (ADJ-5): >=12 seats above 0.05*Amax, spread >=x3, |pearson r| >= 0.6."""
    m = (A > 0.05*A.max()) & (A > 0) & (y > 0)
    if m.sum() < 12: return None, f"only {m.sum()} usable seats (<12)"
    if A[m].max() / A[m].min() < 3: return None, f"amp spread x{A[m].max()/A[m].min():.1f} (<x3)"
    lx, ly = np.log(A[m]), np.log(y[m])
    r = float(np.corrcoef(lx, ly)[0,1])
    if abs(r) < 0.6: return None, f"|r|={abs(r):.2f} < 0.6 - no exponent defined"
    p = float(np.polyfit(lx, ly, 1)[0])
    return (p, r, int(m.sum())), ""

def part_B():
    print("\n" + "="*88)
    print("  PART B - P2: STRUCTURED TOUR (seats at varying radii around a heavy defect)")
    print("  dwell-per-visit AND occupancy vs wake amplitude; exponent from the rule alone.")
    print("  R-Born: nothing quadratic inserted. Committed observables/criteria: ADJ-5.")
    print("="*88)
    results = {}   # beta -> dict of lists
    for b in BETA_GRID_B:
        pd, po, rd, ro, drifts, covers, notes = [], [], [], [], [], [], []
        for seed in TOUR_SEEDS:
            pts, nbr, z, ring_id = build_seats(seed)
            dwell_sum, visits, A, drift, cover = run_tour(pts, nbr, z, b, seed)
            drifts.append(drift); covers.append(cover)
            dpv = np.where(visits > 0, dwell_sum / np.maximum(visits, 1), 0.0)
            occ = dwell_sum / max(dwell_sum.sum(), 1e-300)
            fd, whyd = fit_exponent(dpv, A)
            fo, whyo = fit_exponent(occ, A)
            if fd: pd.append(fd[0]); rd.append(fd[1])
            if fo: po.append(fo[0]); ro.append(fo[1])
            if not fo: notes.append(f"seed {seed}: occ fit undefined ({whyo})")
            if not fd: notes.append(f"seed {seed}: dwell fit undefined ({whyd})")
        results[b] = dict(pd=pd, po=po, rd=rd, ro=ro, drift=drifts, cover=covers, notes=notes)
        dstr = f"{np.mean(pd):+.3f}+-{np.std(pd):.3f} (n={len(pd)})" if pd else "undefined"
        ostr = f"{np.mean(po):+.3f}+-{np.std(po):.3f} (n={len(po)})" if po else "undefined"
        print(f"\n  beta={b:4.2f}:  p_dwell = {dstr:28s}  p_occ = {ostr:28s}")
        print(f"             drift {np.mean(drifts):.4f} (gate <0.01: "
              f"{'PASS' if all(d < 0.01 for d in drifts) else 'FAIL'})   "
              f"coverage {np.mean(covers)*100:.0f}%   "
              f"mean |r| occ = {np.mean(np.abs(ro)) if ro else float('nan'):.2f}")
        for note in results[b]['notes']: print(f"             {note}")
    # committed stable-regime rule (ADJ-5): >=3 consecutive betas, defined p_occ (>=2 seeds),
    # |p_i - median| <= 0.3, drift < 1%
    defined = [(b, np.mean(results[b]['po'])) for b in BETA_GRID_B
               if len(results[b]['po']) >= 2 and all(d < 0.01 for d in results[b]['drift'])]
    stable = []
    if len(defined) >= 3:
        for i0 in range(len(defined)-2):
            for i1 in range(i0+2, len(defined)):
                win = defined[i0:i1+1]
                bs = [b for b,_ in win]
                if BETA_GRID_B.index(bs[-1]) - BETA_GRID_B.index(bs[0]) != len(bs)-1: continue
                ps = np.array([p for _,p in win]); med = np.median(ps)
                if np.all(np.abs(ps - med) <= 0.3) and len(win) > len(stable):
                    stable = win
    print("\n  P2-G1 STABLE-REGIME TEST (committed ADJ-5):")
    if stable:
        bs = [b for b,_ in stable]; ps = [p for _,p in stable]
        p_med = float(np.median(ps))
        print(f"    STABLE regime found: beta in [{bs[0]}, {bs[-1]}]  ({len(bs)} consecutive)")
        print(f"    p_occ over regime: {ps}  ->  median p = {p_med:+.3f}")
        print(f"    (committed hope was p->2; the honest measured value is the number above)")
    else:
        p_med = None
        print("    NO stable regime by the committed rule - reported as such.")
    return results, stable, p_med

# ============ PART C - CHSH through the QM05 throughpole with the EMERGENT law ============
def part_C(p):
    print("\n" + "="*88)
    print("  PART C - CHSH via QM05 throughpole channel, probe weighting REPLACED by the")
    print(f"  emergent residence law (ADJ-6): P(B=A|a,b) = C^p/(C^p+S^p), p = {p:+.3f} (measured,")
    print("  NOT rounded). C=|cos(a-b)|, S=|sin(a-b)| = throughpole projection geometry.")
    print("  ADJ-7 two-channel dynamics: the joint readout IS the geared CONSTRAINT channel -")
    print("  Bob's phase updates the SAME tick as Alice's readout (uncapped constraint within")
    print("  the gear-locked pair; energy/pulses stay at c). Marginal flatness is graded as an")
    print("  OBSERVABLE COMPARISON to measured Bell data, not as a locality axiom.")
    print("="*88)
    rng = np.random.default_rng(11); N = 1_000_000; deg = np.pi/180
    A0, A1, B0, B1 = 0*deg, 45*deg, 22.5*deg, 67.5*deg
    SET = [(A0,B0),(A0,B1),(A1,B0),(A1,B1)]
    Es = {}; worst = 0.0
    for (a,b) in SET:
        lam = rng.uniform(0, np.pi, N)
        Aout = np.where(np.cos(2*(a - lam)) >= 0, 1.0, -1.0)
        C, S_ = abs(np.cos(a-b)), abs(np.sin(a-b))
        Psame = C**p / (C**p + S_**p)
        Bout = np.where(rng.uniform(0,1,N) < Psame, Aout, -Aout)
        Es[(a,b)] = float(np.mean(Aout*Bout))
        dA, dB = abs(float(np.mean(Aout>0))-0.5), abs(float(np.mean(Bout>0))-0.5)
        worst = max(worst, dA, dB)
        print(f"    (a={a/deg:5.1f}, b={b/deg:5.1f})  E={Es[(a,b)]:+.4f}   "
              f"marginal devs {dA:.4f}/{dB:.4f}")
    S = Es[SET[0]] - Es[SET[1]] + Es[SET[2]] + Es[SET[3]]
    Cc, Ss = np.cos(22.5*deg), np.sin(22.5*deg)
    San = 4*(Cc**p - Ss**p)/(Cc**p + Ss**p)
    print(f"\n    S(sampled) = {S:+.4f}    S(analytic, same law) = {San:+.4f}")
    print(f"    reference points: local bound 2.0000 at p={np.log(3)/np.log(Cc/Ss):.3f}; "
          f"Tsirelson 2sqrt2 = {2*np.sqrt(2):.4f} at p=2 exactly")
    print(f"    marginals vs measured Bell data (ADJ-7: data anchor, not axiom) <= 0.002: "
          f"worst dev = {worst:.4f}")
    if worst <= 0.002:
        print("    -> AGREES: marginals flat WITH the v>c constraint channel - the emergent")
        print("       result (constraint carries no free energy; controllability to be")
        print("       ASSESSED, not presumed).")
    else:
        print("    -> DISAGREES with measured marginals: data-FAIL for this transcription.")
    return S, worst

# ========================================== run ===========================================
if __name__ == "__main__":
    print("="*88)
    print("  FLM14 solver - run 2 (rule-form-3).  Gates: RUN_LOG.md (committed; ADJ-4/5/6).")
    print("  One rule (F6): {base, omega_i = OMEGA0*z_i/<z>, g=-1, W, beta-entrainment, T_W}.")
    print("="*88)
    tableA, pass_betas = part_A()
    resultsB, stable, p_med = part_B()

    # T_W robustness (declared in ADJ-4/5: one line each, NOT a scan-for-target)
    print("\n  T_W robustness (instrument-constant check at beta=0.20, seed 1):")
    for tw in (T_W/2, 2*T_W):
        pts, nbr, z, _ = build_seats(1)
        dwell_sum, visits, A, drift, cover = run_tour(pts, nbr, z, 0.20, 1, T_w=tw)
        occ = dwell_sum / max(dwell_sum.sum(), 1e-300)
        fo, why = fit_exponent(occ, A)
        print(f"    T_W={tw:4.1f}: p_occ = " + (f"{fo[0]:+.3f} (|r|={abs(fo[1]):.2f})" if fo else f"undefined ({why})"))

    if p_med is not None:
        S, worst = part_C(p_med)
    else:
        print("\n  PART C: NOT RUN - no stable P2 regime (committed condition, ADJ-6).")

    # F6 cross-check
    print("\n" + "="*88)
    print("  F6 ONE-RULE CROSS-CHECK")
    print(f"    P1 pass regime (ratio <= 1.2): beta in {pass_betas if pass_betas else 'NONE'}")
    if stable:
        bs = [b for b,_ in stable]
        overlap = [b for b in bs if b in pass_betas]
        print(f"    P2 stable regime:              beta in {bs}")
        print(f"    overlap: {overlap if overlap else 'NONE - F6 in doubt: the two phenomena demand different beta'}")
    else:
        print("    P2 stable regime: none - overlap test moot.")
    print("  P3 (Lamb routes) / P4 (lock ladder): DEFERRED per RUN_LOG pre-commitment -")
    print("  dependencies: P3 needs a radial seat ladder calibrated to koppa rungs (PPT08 table);")
    print("  P4 needs contact-geometry windows (NP10). Neither is licensed until the emergent")
    print("  law survives adversarial replication on a 3-D seat geometry.")
    print("="*88)
