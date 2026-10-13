"""
FLM14 - flm14_form4b.py - RUN 4: the TWO-CHANNEL TOUR (constraint channel in P2).
J. C. Harvey, Melbourne - 2026-07-05.

Ordered by Harvey's SG audit: run-3's P2 ran single-channel (run_tour had no rigid-
cluster coupling), so its p_occ values and probe negative are scoped to the uncorrected
instrument. Instrument committed in RUN_LOG.md ADJ-11 BEFORE this file was written.
Held fixed from ADJ-8/ADJ-10: geometry (seed 1), 64 draws x 40,000 hops, phase seeds
10001-10064, beta grid, p_occ criteria, drift < 1%, T_W robustness at beta=0.20.

THE TWO-CHANNEL TOUR RULE (ADJ-11):
  state    theta_k (rotor, free rate omega_k) + wake dphi_k (decay exp(-dt/T_W))
  contact  c_kj = (theta_k + dphi_k + theta_j + dphi_j) mod 1
  landing  dwell cluster C={s} (sigma_s=+1); neighbours in fixed adjacency order:
           LOCK if c_sj < W (j joins C, sigma_j=-1, Omega_C = mean sigma*omega);
           KICK to j's cluster, every member k: dphi_k += -beta*wrap(c_sj)*sigma_k*sigma_j
           SAME tick (rigid, uncapped; singleton j == ADJ-5 kick verbatim).
  theorem  the sigma-signed cluster kick leaves intra-cluster contacts INVARIANT, so a
           locked bond holds its engaged c < W -> gap 0; dwell > 0 only when nothing
           locks (C={s}, natural positive rates; no halt path). Verified at runtime.
  release  all locks dissolve at departure (separation); theta re-based continuously.
CLAIM RULE (hardened, ADJ-11): stable regime (ADJ-5) AND split-half (32/32, both
defined, +-0.4 of pooled) AND geometry-seed-2 replication (32 draws, +-0.4). Part C
licensed only on the full conjunction. Probe: four Q observables at beta=0.20 FIXED.
"""
import numpy as np, math, sys, os, time
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from flm14_solver import OMEGA0, W, T_W, wrap, fit_exponent
from flm14_form4 import build_seats3d, chsh, BETA_GRID_B

N_DRAWS = 64
HOPS    = 40000
PROBE_BETA   = 0.20
PROBE_TARGET = 0.9186

# ===================== the two-channel tour (ADJ-11, one rule) =====================
def run_tour_2ch(pts, nbr, z, beta, phase_seed, hops=HOPS, T_w=T_W, probe=None):
    N = len(pts); omega = OMEGA0 * z / z.mean()
    base = np.random.default_rng(phase_seed).random(N)
    D = np.linalg.norm(pts[:, None, :] - pts[None, :, :], axis=2)
    theta = base.copy(); tth = np.zeros(N)      # rotor coordinate (lockable)
    dphi = np.zeros(N); tlast = np.zeros(N)     # wake ledger (decaying)
    dwell_sum = np.zeros(N); visits = np.zeros(N)
    amp_sum = np.zeros(N); amp_n = 0
    q3s = q4s = 0.0; q3n = q4n = 0
    bad_gaps = 0; lock_dwell_time = 0.0          # instrument guards (expect 0 / 0)
    s = 0; t = 0.0; half = hops // 2; q34 = hops*3//4
    for h in range(hops):
        nb = nbr[s]
        for k in nb + [s]:
            theta[k] += omega[k]*(t - tth[k]); tth[k] = t
            dphi[k] *= math.exp(-(t - tlast[k]) / T_w); tlast[k] = t
        # ---- constraint channel: star cluster + same-tick rigid kicks ----
        C = [s]; sig = {s: 1.0}; Om = omega[s]
        locked = []
        for j in nb:
            c = (theta[s] + dphi[s] + theta[j] + dphi[j]) % 1.0
            kick = -beta * wrap(c)
            if c < W:                                    # window coincidence -> LOCK
                sig[j] = -1.0; C.append(j); locked.append(j)
                Om = sum(sig[k]*omega[k] for k in C) / len(C)
                for k in C:                              # cluster-wide, SAME tick
                    dphi[k] += kick * sig[k] * sig[j]
            else:
                dphi[j] += kick                          # singleton == ADJ-5 verbatim
        # ---- departure: gaps with final cluster state ----
        rate_s = sig[s]*Om if len(C) >= 2 else omega[s]
        gaps = np.empty(len(nb))
        for a, j in enumerate(nb):
            c = (theta[s] + dphi[s] + theta[j] + dphi[j]) % 1.0
            if c < W:
                gaps[a] = 0.0
            else:
                r = (rate_s + omega[j])
                if r <= 0: gaps[a] = np.inf; bad_gaps += 1
                else:      gaps[a] = (1.0 - c) / r
        a_star = int(np.argmin(gaps)); g = float(gaps[a_star]); j_star = nb[a_star]
        if not np.isfinite(g):                           # no departure path (expect never)
            bad_gaps += 10**6; g = 0.0; j_star = nb[0]
        # dwell evolution: locked members advance at sigma*Om (theorem: g>0 => C={s})
        if g > 0 and len(C) >= 2:
            lock_dwell_time += g
            for k in C:
                theta[k] += sig[k]*Om*g; tth[k] = t + g   # release with memory
        if h >= half:
            dwell_sum[s] += g; visits[s] += 1
            amp_sum += np.abs(dphi * np.exp(-(t - tlast) / T_w)); amp_n += 1
            if h < q34: q3s += g; q3n += 1
            else:       q4s += g; q4n += 1
            if probe is not None:
                if len(C) >= 2:
                    probe['om_c'] += abs(Om); probe['n_c'] += 1
                    for k in C: probe['om_mem'] += omega[k]; probe['n_mem'] += 1
                    for j in locked:
                        probe['rim'] += math.pi * D[s, j] * abs(Om); probe['n_rim'] += 1
                probe['sum_D'] += D[s, j_star]; probe['sum_gD'] += g + D[s, j_star]
        t += g + D[s, j_star]
        s = j_star
    A = amp_sum / max(amp_n, 1)
    return (dwell_sum, visits, A, (q3s, q3n, q4s, q4n),
            float((visits > 0).mean()), bad_gaps, lock_dwell_time)

def ensemble(pts, nbr, z, beta, seeds, T_w=T_W, probe=None):
    N = len(pts)
    dw = np.zeros(N); vi = np.zeros(N); Astk = []
    q3s = q4s = 0.0; q3n = q4n = 0; covers = []; per_draw = []
    bad = 0; lockdw = 0.0
    for ps in seeds:
        d, v, A, (a3, n3, a4, n4), cov, bg, ld = run_tour_2ch(
            pts, nbr, z, beta, ps, T_w=T_w, probe=probe)
        dw += d; vi += v; Astk.append(A); covers.append(cov)
        q3s += a3; q3n += n3; q4s += a4; q4n += n4
        per_draw.append((d, A)); bad += bg; lockdw += ld
    A = np.mean(Astk, axis=0)
    occ = dw / max(dw.sum(), 1e-300)
    dpv = np.where(vi > 0, dw / np.maximum(vi, 1), 0.0)
    m3, m4 = q3s/max(q3n, 1), q4s/max(q4n, 1)
    drift = abs(m4 - m3) / max(0.5*(m3 + m4), 1e-12)
    return dict(occ=occ, dpv=dpv, A=A, drift=drift,
                cover_pool=float((vi > 0).mean()), cover_draw=float(np.mean(covers)),
                per_draw=per_draw, bad=bad, lockdw=lockdw)

def half_p(per_draw, lo, hi):
    dw = np.sum([d for d, _ in per_draw[lo:hi]], axis=0)
    A = np.mean([a for _, a in per_draw[lo:hi]], axis=0)
    occ = dw / max(dw.sum(), 1e-300)
    return fit_exponent(occ, A)

# ========================================= run =========================================
if __name__ == "__main__":
    print("="*88)
    print("  FLM14 - run 4: TWO-CHANNEL TOUR (constraint channel in P2).  ADJ-11.")
    print("  Held from ADJ-8/10: geometry seed 1, 64 draws x 40k hops, beta grid, all")
    print("  criteria. New: locks + same-tick rigid cluster kicks in the tour itself.")
    print("  CLAIM RULE hardened (SG order): regime AND split-half AND seed-2 replication.")
    print("="*88)
    pts, nbr, z, sid, deg = build_seats3d(1)
    print(f"  geometry seed 1: {len(pts)} seats, degree min/mean/max = "
          f"{int(deg.min())}/{deg.mean():.2f}/{int(deg.max())}")
    omega_all = OMEGA0 * z / z.mean()
    results = {}; probe_acc = None
    for b in BETA_GRID_B:
        t0 = time.time()
        pr = (dict(om_c=0.0, n_c=0, om_mem=0.0, n_mem=0, rim=0.0, n_rim=0,
                   sum_D=0.0, sum_gD=0.0) if b == PROBE_BETA else None)
        E = ensemble(pts, nbr, z, b, [10001 + k for k in range(N_DRAWS)], probe=pr)
        if pr is not None: probe_acc = pr
        fo, whyo = fit_exponent(E['occ'], E['A'])
        fd, whyd = fit_exponent(E['dpv'], E['A'])
        results[b] = dict(E=E, fo=fo)
        ostr = f"{fo[0]:+.3f} (|r|={abs(fo[1]):.2f}, n={fo[2]})" if fo else f"undefined ({whyo})"
        dstr = f"{fd[0]:+.3f} (|r|={abs(fd[1]):.2f}, n={fd[2]})" if fd else f"undefined ({whyd})"
        sh = None
        if fo:
            h1, _ = half_p(E['per_draw'], 0, 32); h2, _ = half_p(E['per_draw'], 32, 64)
            sh = (f"{h1[0]:+.3f}" if h1 else "undef", f"{h2[0]:+.3f}" if h2 else "undef")
            results[b]['sh'] = (h1, h2)
        print(f"\n  beta={b:4.2f}:  p_occ = {ostr}")
        print(f"             p_dwell = {dstr}")
        print(f"             drift {E['drift']:.4f} (gate <0.01: "
              f"{'PASS' if E['drift'] < 0.01 else 'FAIL'})   coverage pooled "
              f"{E['cover_pool']*100:.0f}% / per-draw {E['cover_draw']*100:.0f}%   "
              f"guards: bad-gaps {E['bad']}, locked-dwell time {E['lockdw']:.2e} "
              f"(theorem: 0)   [{time.time()-t0:.0f}s]"
              + (f"   split-half p_occ: {sh[0]} / {sh[1]}" if sh else ""))
    # ---- stable regime (ADJ-5 rule, unchanged) ----
    defined = [(b, results[b]['fo'][0]) for b in BETA_GRID_B
               if results[b]['fo'] and results[b]['E']['drift'] < 0.01]
    stable = []
    for i0 in range(len(defined)):
        for i1 in range(i0 + 2, len(defined)):
            win = defined[i0:i1+1]; bs = [b for b, _ in win]
            if BETA_GRID_B.index(bs[-1]) - BETA_GRID_B.index(bs[0]) != len(bs) - 1: continue
            ps = np.array([p for _, p in win]); med = np.median(ps)
            if np.all(np.abs(ps - med) <= 0.3) and len(win) > len(stable): stable = win
    print("\n  P2-G1 STABLE-REGIME TEST (ADJ-5 rule unchanged):")
    p_med = None; claim = False
    if stable:
        bs = [b for b, _ in stable]; ps = [p for _, p in stable]
        p_med = float(np.median(ps))
        print(f"    STABLE regime: beta in [{bs[0]}, {bs[-1]}] ({len(bs)} consecutive)")
        print(f"    p_occ over regime: {[f'{p:+.3f}' for p in ps]}  ->  median p = {p_med:+.4f}")
        # ---- CLAIM RULE (ADJ-11): split-half + seed-2 replication ----
        sh_ok = True
        for b, p in stable:
            h1, h2 = results[b].get('sh', (None, None))
            ok = (h1 is not None and h2 is not None
                  and abs(h1[0] - p) <= 0.4 and abs(h2[0] - p) <= 0.4)
            print(f"    split-half @ beta={b}: "
                  + (f"{h1[0]:+.3f} / {h2[0]:+.3f}" if h1 and h2 else
                     f"{'undef' if not h1 else f'{h1[0]:+.3f}'} / "
                     f"{'undef' if not h2 else f'{h2[0]:+.3f}'}")
                  + f"  vs pooled {p:+.3f} (+-0.4)  [{'OK' if ok else 'FAIL'}]")
            sh_ok &= ok
        b_med = min(bs, key=lambda b: abs(dict(stable)[b] - p_med))
        pts2, nbr2, z2, _, deg2 = build_seats3d(2)
        E2 = ensemble(pts2, nbr2, z2, b_med, [20001 + k for k in range(32)])
        f2, why2 = fit_exponent(E2['occ'], E2['A'])
        rep_ok = f2 is not None and abs(f2[0] - dict(stable)[b_med]) <= 0.4
        print(f"    seed-2 replication (32 draws) @ beta={b_med}: "
              + (f"p_occ = {f2[0]:+.3f} (|r|={abs(f2[1]):.2f})" if f2 else f"undefined ({why2})")
              + f"  vs seed-1 {dict(stable)[b_med]:+.3f} (+-0.4)  [{'OK' if rep_ok else 'FAIL'}]")
        claim = sh_ok and rep_ok
        print(f"    CLAIM (regime AND split-half AND replication): "
              f"{'EARNED' if claim else 'NOT EARNED - regime-without-claim, reported'}")
    else:
        print("    NO stable regime by the committed rule - reported as such.")
    # ---- T_W robustness (held from ADJ-8; not gates) ----
    print("\n  robustness (declared, not gates):")
    for tw in (T_W/2, 2*T_W):
        E = ensemble(pts, nbr, z, 0.20, [10001 + k for k in range(N_DRAWS)], T_w=tw)
        f, why = fit_exponent(E['occ'], E['A'])
        print(f"    T_W={tw:4.1f} @ beta=0.20: p_occ = "
              + (f"{f[0]:+.3f} (|r|={abs(f[1]):.2f})" if f else f"undefined ({why})"))
    # ---- Part C: licensed only on the full ADJ-11 conjunction ----
    if claim and p_med is not None:
        print("\n" + "="*88)
        print("  PART C - CHSH via the constraint channel (ADJ-6 verbatim), "
              f"p = {p_med:+.4f} (measured)")
        print("="*88)
        N = 2_000_000
        S, worst, rows = chsh(p_med, N, np.random.default_rng(11))
        deg_ = np.pi/180
        for a, b, Eab, dA, dB in rows:
            print(f"    (a={a:5.1f}, b={b:5.1f})  E={Eab:+.4f}   marginal devs {dA:.4f}/{dB:.4f}")
        Cc, Ss = np.cos(np.pi/8), np.sin(np.pi/8)
        San = 4*(Cc**p_med - Ss**p_med)/(Cc**p_med + Ss**p_med)
        print(f"\n    S(sampled, N={N}) = {S:+.4f}    S(analytic, same law) = {San:+.4f}")
        print(f"    reference: local bound 2 at p={np.log(3)/np.log(Cc/Ss):.3f}; "
              f"Tsirelson 2sqrt2 = {2*np.sqrt(2):.4f} at p=2 exactly")
        if worst > 0.002:
            print(f"    marginal dev {worst:.4f} > 0.002 -> FARMER ref.5: investigate as bug")
            S2, worst2, _ = chsh(p_med, 4*N, np.random.default_rng(101))
            print(f"    diagnostic 4x N: worst dev {worst2:.4f}  S = {S2:+.4f}")
            if worst2 < worst/1.5:
                print("    -> scales with N: SAMPLING ARTIFACT; larger-N values adopted.")
                S, worst = S2, worst2
            else:
                print("    -> does NOT scale: implementation fault suspected; instrument-OPEN.")
        print(f"    marginals vs measured Bell data (ADJ-7 anchor): worst dev = {worst:.4f} -> "
              + ("AGREES (flat WITH the v>c constraint channel)." if worst <= 0.002
                 else "DISAGREES: data-FAIL for this transcription."))
    else:
        print("\n  PART C: NOT RUN - ADJ-11 claim conjunction not met (committed condition).")
    # ---- probe (ADJ-11 re-scope; one scan at beta=0.20, declared) ----
    print("\n" + "="*88)
    print("  PROBE (ADJ-11, one scan @ beta=0.20 fixed): 0.9186 in TWO-CHANNEL tour")
    print("  kinematics? Four declared observables; hit = within 1% relative.")
    print("="*88)
    pr = probe_acc
    Q1 = (pr['om_c']/max(pr['n_c'], 1)) / (pr['om_mem']/max(pr['n_mem'], 1))
    Q2 = pr['rim'] / max(pr['n_rim'], 1)
    Q3 = pr['sum_D'] / max(pr['sum_gD'], 1e-300)
    Q4 = (pr['om_mem']/max(pr['n_mem'], 1)) / float(np.mean(omega_all))
    names = dict(Q1="<|Omega_C|>/<omega>_members (star rate retention)",
                 Q2="<pi*D*|Omega_C|> locked bonds, units c (star rim speed)",
                 Q3="sum(D)/sum(g+D) (effective tour speed / c)",
                 Q4="<omega>_locked/<omega>_all (selection)")
    any_hit = False
    for k, v in zip(('Q1', 'Q2', 'Q3', 'Q4'), (Q1, Q2, Q3, Q4)):
        hit = abs(v/PROBE_TARGET - 1) <= 0.01; any_hit |= hit
        print(f"    {k} = {v:.5f}   {names[k]}  ->  "
              f"{'** HIT **' if hit else 'not 0.9186 (miss)'}")
    print(f"\n    PROBE VERDICT: {'FOUND' if any_hit else 'NOT FOUND'} on the two-channel")
    print("    tour instrument (run-3 negative was scoped to single-channel, SG note).")
    print("\n" + "="*88)
    print("  F6: one rule throughout - lock/kick/window identical at every beta and in")
    print("  both geometry seeds; T_W, W, OMEGA0 untouched; p (if used) is measured.")
    print("="*88)
