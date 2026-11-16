"""
FLM14 - flm14_form4.py - RULE-FORM-4: two-channel dynamics (run 3).
J. C. Harvey, Melbourne - 2026-07-04.

Instrument committed in RUN_LOG.md ADJ-8 / ADJ-9 BEFORE this file was written.
Committed gates UNMOVED: P1-G3 <= 1.2 (ladder to beat: 7.47 -> 2.88/2.29 -> 1.35);
P2-G1 exponent criteria; P2-G2 pooled drift < 1%; ADJ-5 stable-regime rule; F6.

THE FORM-4 RULE (ADJ-7 two-channel, made structural):
  PULSE channel      every hop travels at c (travel time = bond length). NO waits,
                     NO kicks. Transparent BY ARCHITECTURE - run-2's beta=1 lesson
                     made non-degenerate: there is no parameter to saturate.
  CONSTRAINT channel at each FIRST contact per bond (i,j): if the window coincides,
                     c_ij = (phi_i + phi_j) mod 1 < W, the bond GEAR-LOCKS. Locked
                     clusters are RIGID: one collective coordinate,
                     phi_i(t) = A_i + sigma_i * Omega_c * (t - t_c), sigma alternating
                     g=-1 across every locked bond; any phase re-basing applies to ALL
                     members the SAME tick, uncapped (canon: 1.83c seat, instantaneous
                     throughpole, GOM05 rigid hinges). Omega_c = (1/n) sum sigma_i*omega_i
                     (rigid train, equal coupling - no new constant). No snap-to-lock
                     kick: gears engage at the coincident relation as found. Same-cluster
                     contact with sigma_i*sigma_j = +1 is a FRUSTRATED refusal (the
                     P1-G2 0.347 carrier population) - counted, never silently dropped.
Native quantities: {base phi, omega_i = OMEGA0*z_i/<z>, g=-1, W, lock-rigidity} = 5.
beta does NOT exist on the lattice channel; it survives only as the electron's declared
contact-kick coefficient in Part B (ADJ-5 verbatim). Nothing is fitted anywhere.
"""
import numpy as np, heapq, itertools, math, sys, os, time
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

# reuse run-2 CRN + measurement machinery verbatim (ADJ-4 instrument, unchanged)
from flm14_solver import (OMEGA0, W, T_W, GLASS_SEEDS, wrap, make_amorphous_1000,
                          bonds_angles, mic, golden_dirs, geometric_coordination,
                          anisotropy, fit_exponent)

BETA_GRID_B = [0.02, 0.05, 0.10, 0.20, 0.40, 0.80]   # ADJ-5, unchanged
N_DRAWS     = 64          # ADJ-8: ensemble-over-phase (R-seq)
HOPS        = 40000       # per draw, first half discarded (ADJ-8; 8000 -> 40000 per
                          # ADJ-10: drift estimator under-sampled at degree ~7.5)
PROBE_TARGET = 0.9186     # ADJ-9: NP14 internal-electron seat (0.91859; ratio 0.91808)

# ========================= PART A - form-4 front + constraint channel ======================
class RigidClusters:
    """Union-find of gear-locked rigid clusters. phi_i(t) = A_i + sigma_i*Om_r*(t-tc_r)."""
    def __init__(self, omega, base):
        n = len(omega)
        self.par = list(range(n)); self.size = [1]*n
        self.mem = [[i] for i in range(n)]
        self.sig = np.ones(n)
        self.A   = base.astype(float).copy()
        self.Om  = omega.astype(float).copy()
        self.tc  = np.zeros(n)
        self.om_nat = omega.astype(float).copy()
        self.frus = 0; self.same_ok = 0; self.locked_bonds = []
    def find(self, x):
        r = x
        while self.par[r] != r: r = self.par[r]
        while self.par[x] != r: self.par[x], x = r, self.par[x]
        return r
    def phase(self, k, t):
        r = self.find(k)
        return self.A[k] + self.sig[k]*self.Om[r]*(t - self.tc[r])
    def _rebase(self, r, t):
        dt = t - self.tc[r]
        for k in self.mem[r]: self.A[k] += self.sig[k]*self.Om[r]*dt
        self.tc[r] = t
    def lock(self, i, j, t):
        """Attempt gear-lock on bond (i,j) at time t. Returns True if locked."""
        ri, rj = self.find(i), self.find(j)
        if ri == rj:
            if self.sig[i]*self.sig[j] > 0:
                self.frus += 1; return False          # frustrated (odd ring) - refused
            self.same_ok += 1; self.locked_bonds.append((i, j)); return True
        self._rebase(ri, t); self._rebase(rj, t)       # cluster-wide, SAME tick (ADJ-7)
        if self.size[ri] < self.size[rj]: ri, rj = rj, ri
        if self.sig[i]*self.sig[j] > 0:                # need g=-1 across the new bond
            for k in self.mem[rj]: self.sig[k] = -self.sig[k]
        for k in self.mem[rj]: self.par[k] = ri
        self.mem[ri] += self.mem[rj]; self.mem[rj] = []
        self.size[ri] += self.size[rj]
        m = self.mem[ri]
        self.Om[ri] = float(np.mean([self.sig[k]*self.om_nat[k] for k in m]))
        self.tc[ri] = t
        self.locked_bonds.append((i, j)); return True

def run_front_form4(pos, L, nbr, blen, omega, base, geared):
    """Pulse channel: pure c-relay (identical to ungeared BY ARCHITECTURE).
    Constraint channel (geared arm only): lock bookkeeping at first contact per bond."""
    N = len(pos)
    arr = np.full(N, np.inf); ctr = itertools.count()
    src = int(np.argmin(np.einsum('ij,ij->i', pos - L/2, pos - L/2)))
    arr[src] = 0.0
    heap = []; contacted = set()
    cl = RigidClusters(omega, base) if geared else None
    n_contact = n_lock = n_winref = 0
    def send(i, t):
        for j in nbr[i]:
            if arr[j] == np.inf:
                heapq.heappush(heap, (t + blen[(i, j)], next(ctr), i, j))
    send(src, 0.0)
    while heap:
        t, _, i, j = heapq.heappop(heap)
        if geared:
            key = (min(i, j), max(i, j))
            if key not in contacted:                   # first contact per bond
                contacted.add(key); n_contact += 1
                c = (cl.phase(i, t) + cl.phase(j, t)) % 1.0
                if c < W:
                    if cl.lock(i, j, t): n_lock += 1
                else:
                    n_winref += 1
        if arr[j] == np.inf:
            arr[j] = t; send(j, t)                     # pulse passes REGARDLESS: no wait
    return arr, src, cl, dict(contacts=n_contact, locks=n_lock, winref=n_winref)

def lock_anisotropy(pos, L, bonds_all, locked_set, dirs, cosw=0.75):
    """std/mean of locked-bond fraction over the 24 cones (bond orientation, +-u pooled)."""
    dr = mic(pos[bonds_all[:, 1]] - pos[bonds_all[:, 0]], L)
    u = dr / np.linalg.norm(dr, axis=1)[:, None]
    is_locked = np.array([(min(a, b), max(a, b)) in locked_set for a, b in bonds_all])
    fs = []
    for d in dirs:
        m = np.abs(u @ d) >= cosw
        if m.sum() >= 5: fs.append(is_locked[m].mean())
    fs = np.array(fs)
    return float(fs.std()/fs.mean()) if len(fs) and fs.mean() > 0 else float('nan'), len(fs)

def part_A():
    print("="*88)
    print("  PART A - P1-G3 on RULE-FORM-4 (two channels).  Gate <= 1.2 (UNMOVED).")
    print("  Ladder: form-1 x7.47 KILLED -> form-2 x2.88/x2.29 FAIL -> form-3 x1.35 FAIL")
    print("  (x1.00 only at degenerate beta=1) -> form-4 = pulse channel transparent BY")
    print("  ARCHITECTURE. Pre-stated (ADJ-8): the ratio is 1.00 by construction; the run")
    print("  verifies the identity and measures the RESIDUAL constraint-channel signature.")
    print("="*88)
    dirs = golden_dirs(24)
    ratios, anchors = [], []
    probes = {k: [] for k in ('R1', 'R2', 'R3', 'R4')}
    sig_rows = []
    for seed in GLASS_SEEDS:
        t0 = time.time()
        pos, L, d, nbr, acc = make_amorphous_1000(500, seed)
        bonds, _ = bonds_angles(nbr)
        bl = np.linalg.norm(mic(pos[bonds[:, 1]] - pos[bonds[:, 0]], L), axis=1)
        dbar = float(np.median(bl))
        blen = {}
        for (i, j), l in zip(bonds, bl):
            blen[(int(i), int(j))] = float(l); blen[(int(j), int(i))] = float(l)
        z = geometric_coordination(pos, L, dbar)
        omega = OMEGA0 * z / z.mean()
        print(f"\n  glass seed {seed}: N={len(pos)}  accepted WWW switches={acc}  "
              f"bond length {bl.mean():.3f}+-{bl.std():.3f}  "
              f"z min/mean/max = {z.min()}/{z.mean():.2f}/{z.max()}  [{time.time()-t0:.0f}s]")
        rngp = np.random.default_rng(1000 + seed)      # same phase-draw rule as run 2
        base = rngp.random(len(pos))
        arr_u, src, _, _ = run_front_form4(pos, L, nbr, blen, omega, base, geared=False)
        arr_g, _, cl, st = run_front_form4(pos, L, nbr, blen, omega, base, geared=True)
        anchor = float(np.nanmax(np.abs(np.where(np.isfinite(arr_g) & np.isfinite(arr_u),
                                                 arr_g - arr_u, 0.0))))
        anchors.append(anchor)
        a_u, nd_u = anisotropy(pos, L, src, arr_u, dbar, dirs)
        a_g, nd_g = anisotropy(pos, L, src, arr_g, dbar, dirs)
        ratio = a_g / a_u; ratios.append(ratio)
        print(f"    pulse channel: ungeared anisotropy {a_u:.4f} ({nd_u} dirs)  "
              f"geared {a_g:.4f} ({nd_g} dirs)  ratio {ratio:.4f}  "
              f"identity max|t_g - t_u| = {anchor:.2e}")
        # ---- constraint-channel residual signature (declared set, ADJ-8) ----
        roots = {cl.find(k) for k in range(len(pos))}
        cls2 = [cl.mem[r] for r in roots if cl.size[r] >= 2]
        sizes = sorted((len(m) for m in cls2), reverse=True)
        largest = sizes[0] if sizes else 0
        rmax = max((r for r in roots if cl.size[r] >= 2),
                   key=lambda r: cl.size[r], default=None)
        om_large = abs(cl.Om[rmax]) if rmax is not None else float('nan')
        locked_set = {(min(a, b), max(a, b)) for a, b in cl.locked_bonds}
        a_lock, nc = lock_anisotropy(pos, L, bonds, locked_set, dirs)
        f_lock = st['locks'] / max(st['contacts'], 1)
        f_win  = st['winref'] / max(st['contacts'], 1)
        f_frus = cl.frus / max(cl.frus + cl.same_ok, 1)
        print(f"    constraint channel: contacts {st['contacts']}  locked {st['locks']} "
              f"({f_lock*100:.1f}%)  window-refused {f_win*100:.1f}%  "
              f"frustrated-refused {cl.frus} of {cl.frus+cl.same_ok} same-cluster "
              f"attempts ({f_frus*100:.1f}%; P1-G2 forecast 34.7%)")
        print(f"    clusters (size>=2): n={len(cls2)}  largest {largest}/{len(pos)} "
              f"({largest/len(pos)*100:.1f}% - percolation)  "
              f"|Omega|_largest/OMEGA0 = {om_large/OMEGA0:.4f} (freeze test)  "
              f"lock-network anisotropy {a_lock:.3f} ({nc} cones)")
        sig_rows.append((f_lock, f_frus, largest/len(pos), om_large/OMEGA0, a_lock))
        # ---- ADJ-9 probe observables (end-of-front state; declared, no post-hoc) ----
        mem_all = [k for m in cls2 for k in m]
        mean_abs_Om = float(np.mean([abs(cl.Om[cl.find(m[0])]) for m in cls2])) if cls2 else float('nan')
        mean_om_mem = float(np.mean(omega[mem_all])) if mem_all else float('nan')
        R1 = mean_abs_Om / mean_om_mem
        R2 = om_large / OMEGA0
        R3 = float(np.mean([math.pi * blen[(a, b)] * abs(cl.Om[cl.find(a)])
                            for a, b in cl.locked_bonds])) if cl.locked_bonds else float('nan')
        R4 = mean_om_mem / float(np.mean(omega))
        for k, v in zip(('R1', 'R2', 'R3', 'R4'), (R1, R2, R3, R4)): probes[k].append(v)
    print(f"\n  P1-G3 SUMMARY: ratio geared/ungeared = "
          f"{np.mean(ratios):.4f} +- {np.std(ratios):.4f} over {len(GLASS_SEEDS)} glasses; "
          f"identity anchor max = {max(anchors):.2e}")
    print(f"    gate <= 1.2: {'PASS' if np.mean(ratios) <= 1.2 else 'FAIL'} - "
          f"TRIVIALLY SATISFIED BY ARCHITECTURE (pre-stated ADJ-8): the pulse channel")
    print(f"    carries no gearing waits, so the P1-G3 observable can no longer see the")
    print(f"    gearing at all. The MEASURABLE residual lives on the constraint channel:")
    m = np.mean(np.array(sig_rows), axis=0)
    print(f"    <locked bond fraction> = {m[0]*100:.1f}%  (window duty W = {W} forecast)")
    print(f"    <frustrated refusal>   = {m[1]*100:.1f}%  of same-cluster attempts")
    print(f"    <largest cluster>      = {m[2]*100:.1f}%  of sites (constraint percolation)")
    print(f"    <|Omega|/OMEGA0>       = {m[3]:.4f}       (locking FREEZES rotation)")
    print(f"    <lock anisotropy>      = {m[4]:.3f}       (direction structure of the lock net)")
    return ratios, anchors, probes

# ==================== PART B - P2: ensemble-over-phase, 3-D seat geometry ==================
def fib_sphere(n, rng):
    i = np.arange(n) + 0.5
    z = 1 - 2*i/n; th = np.pi*(3 - np.sqrt(5))*i
    r = np.sqrt(1 - z*z)
    p = np.stack([r*np.cos(th), r*np.sin(th), z], axis=1)
    p += rng.normal(0, 0.10, p.shape)                  # seeded jitter (ADJ-8)
    p /= np.linalg.norm(p, axis=1)[:, None]
    # random rotation to decorrelate shells
    q = rng.normal(size=(3, 3)); Q, _ = np.linalg.qr(q)
    return p @ Q

def build_seats3d(seed):
    """ADJ-8: three shells r={1.0,1.55,2.3}, counts {8,13,21}, adjacency = 4 nearest
    within-shell + 2 nearest in each adjacent shell (symmetrised). Min degree >= 6."""
    rng = np.random.default_rng(seed)
    shells = [(1.0, 8), (1.55, 13), (2.3, 21)]
    pts, sid = [], []
    for k, (rad, n) in enumerate(shells):
        for p in fib_sphere(n, rng):
            pts.append(rad*p); sid.append(k)
    pts = np.array(pts); sid = np.array(sid)
    edges = set()
    def near(i, cand, m):
        dd = np.linalg.norm(pts[cand] - pts[i], axis=1)
        return [int(cand[a]) for a in np.argsort(dd)[:m]]
    for i in range(len(pts)):
        same = np.array([j for j in np.where(sid == sid[i])[0] if j != i])
        for j in near(i, same, 4): edges.add((min(i, j), max(i, j)))
        for dk in (-1, 1):
            if 0 <= sid[i] + dk <= 2:
                adj = np.where(sid == sid[i] + dk)[0]
                for j in near(i, adj, 2): edges.add((min(i, j), max(i, j)))
    N = len(pts); nbr = [[] for _ in range(N)]
    for i, j in sorted(edges): nbr[i].append(j); nbr[j].append(i)
    deg = np.array([len(nbr[i]) for i in range(N)], float)
    z = deg.copy()
    z[sid == 0] += 1.0            # heavy central defect: bond-partner of the inner shell
    return pts, nbr, z, sid, deg

def run_tour(pts, nbr, z, beta, phase_seed, hops=HOPS, T_w=T_W):
    """ADJ-5 rule VERBATIM (run-2 machinery); only base-phase draw + geometry differ."""
    N = len(pts); omega = OMEGA0 * z / z.mean()
    base = np.random.default_rng(phase_seed).random(N)
    D = np.linalg.norm(pts[:, None, :] - pts[None, :, :], axis=2)
    dphi = np.zeros(N); tlast = np.zeros(N)
    dwell_sum = np.zeros(N); visits = np.zeros(N)
    amp_sum = np.zeros(N); amp_n = 0
    q3s = q4s = 0.0; q3n = q4n = 0
    s = 0                                              # start: inner shell seat (fixed)
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
            if h < q34: q3s += g; q3n += 1
            else:       q4s += g; q4n += 1
        t += g + D[s, j_star]
        s = j_star
    A = amp_sum / max(amp_n, 1)
    return dwell_sum, visits, A, (q3s, q3n, q4s, q4n), float((visits > 0).mean())

def ensemble(pts, nbr, z, beta, seeds, T_w=T_W):
    """ADJ-8 pooled aggregation over the phase ensemble."""
    N = len(pts)
    dw = np.zeros(N); vi = np.zeros(N); Astk = []
    q3s = q4s = 0.0; q3n = q4n = 0; covers = []
    per_draw = []
    for ps in seeds:
        d, v, A, (a3, n3, a4, n4), cov = run_tour(pts, nbr, z, beta, ps, T_w=T_w)
        dw += d; vi += v; Astk.append(A); covers.append(cov)
        q3s += a3; q3n += n3; q4s += a4; q4n += n4
        per_draw.append((d, A))
    A = np.mean(Astk, axis=0)
    occ = dw / max(dw.sum(), 1e-300)
    dpv = np.where(vi > 0, dw / np.maximum(vi, 1), 0.0)
    m3, m4 = q3s/max(q3n, 1), q4s/max(q4n, 1)
    drift = abs(m4 - m3) / max(0.5*(m3 + m4), 1e-12)
    return dict(occ=occ, dpv=dpv, A=A, drift=drift,
                cover_pool=float((vi > 0).mean()), cover_draw=float(np.mean(covers)),
                per_draw=per_draw)

def split_half_p(per_draw):
    out = []
    for hs in (per_draw[:len(per_draw)//2], per_draw[len(per_draw)//2:]):
        dw = np.sum([d for d, _ in hs], axis=0)
        A = np.mean([a for _, a in hs], axis=0)
        occ = dw / max(dw.sum(), 1e-300)
        f, why = fit_exponent(occ, A)
        out.append(f"{f[0]:+.3f}" if f else "undef")
    return out

def part_B():
    print("\n" + "="*88)
    print("  PART B - P2 per ADJ-5 VERBATIM + run-2's two corrections (ADJ-8):")
    print(f"  (1) ENSEMBLE-OVER-PHASE: {N_DRAWS} initial-phase draws x {HOPS} hops (ADJ-10)")
    print("      (R-seq:")
    print("      probability IS ignorance of the starting tick). (2) 3-D seat geometry:")
    print("      three shells {8,13,21}, adjacency >= 6 (kills short-cycle trapping).")
    print("  R-Born: nothing quadratic inserted. Exponent criteria + beta grid unchanged.")
    print("="*88)
    pts, nbr, z, sid, deg = build_seats3d(1)
    print(f"  geometry seed 1: {len(pts)} seats, degree min/mean/max = "
          f"{int(deg.min())}/{deg.mean():.2f}/{int(deg.max())}"
          + ("" if deg.min() >= 6 else "  ** INSTRUMENT FAULT: min degree < 6 **"))
    if deg.min() < 6:
        print("  Part B aborted per ADJ-8 (instrument fault)."); return None, None, None
    results = {}
    for b in BETA_GRID_B:
        t0 = time.time()
        E = ensemble(pts, nbr, z, b, [10001 + k for k in range(N_DRAWS)])
        fo, whyo = fit_exponent(E['occ'], E['A'])
        fd, whyd = fit_exponent(E['dpv'], E['A'])
        results[b] = dict(E=E, fo=fo, fd=fd)
        ostr = f"{fo[0]:+.3f} (|r|={abs(fo[1]):.2f}, n={fo[2]})" if fo else f"undefined ({whyo})"
        dstr = f"{fd[0]:+.3f} (|r|={abs(fd[1]):.2f}, n={fd[2]})" if fd else f"undefined ({whyd})"
        sh = split_half_p(E['per_draw']) if fo else None
        print(f"\n  beta={b:4.2f}:  p_occ = {ostr}")
        print(f"             p_dwell = {dstr}")
        print(f"             drift {E['drift']:.4f} (gate <0.01: "
              f"{'PASS' if E['drift'] < 0.01 else 'FAIL'})   coverage pooled "
              f"{E['cover_pool']*100:.0f}% / per-draw {E['cover_draw']*100:.0f}%   "
              f"[{time.time()-t0:.0f}s]"
              + (f"   split-half p_occ: {sh[0]} / {sh[1]}" if sh else ""))
    # committed stable-regime rule (ADJ-5/ADJ-8): >=3 consecutive betas, defined pooled
    # p_occ, drift < 1%, |p_i - median| <= 0.3
    defined = [(b, results[b]['fo'][0]) for b in BETA_GRID_B
               if results[b]['fo'] and results[b]['E']['drift'] < 0.01]
    stable = []
    for i0 in range(len(defined)):
        for i1 in range(i0 + 2, len(defined)):
            win = defined[i0:i1+1]; bs = [b for b, _ in win]
            if BETA_GRID_B.index(bs[-1]) - BETA_GRID_B.index(bs[0]) != len(bs) - 1: continue
            ps = np.array([p for _, p in win]); med = np.median(ps)
            if np.all(np.abs(ps - med) <= 0.3) and len(win) > len(stable): stable = win
    print("\n  P2-G1 STABLE-REGIME TEST (committed rule unchanged):")
    p_med = None
    if stable:
        bs = [b for b, _ in stable]; ps = [p for _, p in stable]
        p_med = float(np.median(ps))
        print(f"    STABLE regime: beta in [{bs[0]}, {bs[-1]}] ({len(bs)} consecutive)")
        print(f"    p_occ over regime: {[f'{p:+.3f}' for p in ps]}  ->  median p = {p_med:+.4f}")
        print(f"    (hope was p->2; the honest measured value is the number above)")
    else:
        print("    NO stable regime by the committed rule - reported as such.")
    # robustness lines (declared ADJ-8; not gates)
    b_rob = min(BETA_GRID_B, key=lambda b: abs(b - (stable[len(stable)//2][0] if stable else 0.20)))
    print(f"\n  robustness (declared, not gates):")
    for tw in (T_W/2, 2*T_W):
        E = ensemble(pts, nbr, z, 0.20, [10001 + k for k in range(N_DRAWS)], T_w=tw)
        f, why = fit_exponent(E['occ'], E['A'])
        print(f"    T_W={tw:4.1f} @ beta=0.20: p_occ = "
              + (f"{f[0]:+.3f} (|r|={abs(f[1]):.2f})" if f else f"undefined ({why})"))
    pts2, nbr2, z2, _, deg2 = build_seats3d(2)
    E2 = ensemble(pts2, nbr2, z2, b_rob, [20001 + k for k in range(16)])
    f2, why2 = fit_exponent(E2['occ'], E2['A'])
    print(f"    geometry seed 2 (16 draws) @ beta={b_rob}: p_occ = "
          + (f"{f2[0]:+.3f} (|r|={abs(f2[1]):.2f})" if f2 else f"undefined ({why2})"))
    return results, stable, p_med

# ================= PART C - CHSH via the constraint channel, emergent law ==================
def chsh(p, N, rng):
    deg = np.pi/180
    A0, A1, B0, B1 = 0*deg, 45*deg, 22.5*deg, 67.5*deg
    SET = [(A0, B0), (A0, B1), (A1, B0), (A1, B1)]
    Es = {}; worst = 0.0; rows = []
    for (a, b) in SET:
        lam = rng.uniform(0, np.pi, N)
        Aout = np.where(np.cos(2*(a - lam)) >= 0, 1.0, -1.0)
        C, S_ = abs(np.cos(a - b)), abs(np.sin(a - b))
        Psame = C**p / (C**p + S_**p)
        Bout = np.where(rng.uniform(0, 1, N) < Psame, Aout, -Aout)   # same-tick partner
        Es[(a, b)] = float(np.mean(Aout*Bout))                        # update (ADJ-7 ch.)
        dA, dB = abs(float(np.mean(Aout > 0)) - 0.5), abs(float(np.mean(Bout > 0)) - 0.5)
        worst = max(worst, dA, dB)
        rows.append((a/deg, b/deg, Es[(a, b)], dA, dB))
    S = Es[SET[0]] - Es[SET[1]] + Es[SET[2]] + Es[SET[3]]
    return S, worst, rows

def part_C(p):
    print("\n" + "="*88)
    print("  PART C - CHSH via QM05 throughpole, joint weighting REPLACED by the emergent")
    print(f"  residence law (ADJ-6): P(B=A|a,b) = C^p/(C^p+S^p), p = {p:+.4f} (measured, NOT")
    print("  rounded). Joint readout = the form-4 CONSTRAINT channel: the gear-locked pair")
    print("  is rigid, Bob's phase updates the SAME tick as Alice's readout (uncapped;")
    print("  pulses/energy stay at c). Marginal flatness <= 0.002 graded as a DATA ANCHOR")
    print("  (ADJ-7) and FIRST as a Synchrony-Theorem implementation check (FARMER ref. 5).")
    print("="*88)
    N = 2_000_000
    S, worst, rows = chsh(p, N, np.random.default_rng(11))
    for a, b, E, dA, dB in rows:
        print(f"    (a={a:5.1f}, b={b:5.1f})  E={E:+.4f}   marginal devs {dA:.4f}/{dB:.4f}")
    Cc, Ss = np.cos(np.pi/8), np.sin(np.pi/8)
    San = 4*(Cc**p - Ss**p)/(Cc**p + Ss**p)
    print(f"\n    S(sampled, N={N}) = {S:+.4f}    S(analytic, same law) = {San:+.4f}")
    print(f"    reference: local bound 2 at p={np.log(3)/np.log(Cc/Ss):.3f}; "
          f"Tsirelson 2sqrt2 = {2*np.sqrt(2):.4f} at p=2 exactly")
    if worst > 0.002:
        print(f"    marginal dev {worst:.4f} > 0.002 -> FARMER ref.5: investigate as bug")
        print("    diagnostic: re-run 4x N, fresh seed (sampling-noise hypothesis):")
        S2, worst2, _ = chsh(p, 4*N, np.random.default_rng(101))
        print(f"    -> N={4*N}: worst dev {worst2:.4f}  S = {S2:+.4f}")
        if worst2 < worst/1.5:
            print("    -> scales down with N: SAMPLING ARTIFACT (instrument, not physics);")
            print("       larger-N values adopted.")
            S, worst = S2, worst2
        else:
            print("    -> does NOT scale with N: implementation fault suspected; result")
            print("       NOT bankable until traced. Reported as instrument-OPEN.")
    verdict = ("AGREES with measured Bell marginals WITH the v>c constraint channel - the "
               "emergent result\n       (constraint carries no free energy; "
               "controllability to be ASSESSED, not presumed)."
               if worst <= 0.002 else
               "DISAGREES with measured marginals: data-FAIL for this transcription.")
    print(f"    marginals vs measured Bell data: worst dev = {worst:.4f} -> {verdict}")
    return S, worst

# ===================== PART D - ADJ-9 bonus probe (one scan, declared) =====================
def part_D(probes):
    print("\n" + "="*88)
    print("  PART D - ADJ-9 PROBE (one scan, declared before code): does form-4 gearing")
    print(f"  force the NP14 candidate 0.91859c (or ratio 0.91808) in locked-cluster")
    print("  kinematics? Four observables fixed in ADJ-9; hit = within 1% of 0.9186;")
    print("  no derived combinations after looking, no inversions, no second scan.")
    print("="*88)
    names = dict(R1="<|Omega_c|>/<omega>_members (rate retention)",
                 R2="|Omega_largest|/OMEGA0 (largest-cluster residual rate)",
                 R3="<pi*l*|Omega_c|> locked bonds, units c (gear rim speed)",
                 R4="<omega>_locked/<omega>_all (coordination selection)")
    any_hit = False
    for k in ('R1', 'R2', 'R3', 'R4'):
        vals = np.array(probes[k], float)
        v = float(np.nanmean(vals))
        hit = abs(v/PROBE_TARGET - 1) <= 0.01
        any_hit |= hit
        print(f"    {k} = {v:.5f}  (per-glass: {', '.join(f'{x:.5f}' for x in vals)})")
        print(f"         {names[k]}  ->  {'** HIT **' if hit else 'not 0.9186 (miss)'}")
    print(f"\n    PROBE VERDICT: {'FOUND' if any_hit else 'NOT FOUND'} - "
          + ("a declared observable sits within 1% of the NP14 seat." if any_hit else
         "no declared observable is within 1% of 0.9186. A miss is a miss; no fishing."))
    return any_hit

# ========================================== run ===========================================
if __name__ == "__main__":
    print("="*88)
    print("  FLM14 solver - run 3 (RULE-FORM-4, two channels).  Gates: RUN_LOG.md ADJ-8/9.")
    print("  One lattice rule (P1-G1): {base phi, omega_i = OMEGA0*z_i/<z>, g=-1, W,")
    print("  lock-rigidity} = 5 native quantities. beta exists only as the electron's")
    print("  declared contact-kick coefficient in Part B (ADJ-5 verbatim). Nothing fitted.")
    print("="*88)
    ratios, anchors, probes = part_A()
    resultsB, stable, p_med = part_B()
    if p_med is not None:
        S, worst = part_C(p_med)
    else:
        print("\n  PART C: NOT RUN - no stable P2 regime (committed condition, ADJ-6).")
    part_D(probes)
    print("\n" + "="*88)
    print("  F6 ONE-RULE CROSS-CHECK")
    print("    Part A lattice rule has NO beta (locking replaces entrainment structurally);")
    print("    Part B uses the ADJ-5 electron rule verbatim; Part C uses the MEASURED p")
    print("    with no re-tuning of beta, T_W, W, OMEGA0 anywhere between parts.")
    if stable:
        print(f"    P2 stable regime: beta in {[b for b, _ in stable]}; P1-G3 is now")
        print("    beta-independent by architecture, so the run-2 F6 tension (P1 pulling")
        print("    beta->1 against P2) is DISSOLVED, not re-tuned away.")
    print("  P3 (Lamb routes) / P4 (lock ladder): licensing depends on this run's P2.")
    print("="*88)
