"""
FLM14 - flm14_form6.py - RUN 6: the MEMORY-FREE MEASURE (ADJ-13).
J. C. Harvey, Melbourne - 2026-07-07.

Instrument committed in RUN_LOG.md ADJ-13 BEFORE this file was written. Machinery =
flm14_form4b two-channel tour VERBATIM: dynamics (tour rule, star locks, sigma-signed
same-tick cluster kicks, gap rule, release, T_W=27 wake decay IN THE DYNAMICS, W,
OMEGA0, hop counts, phase-seed conventions) UNCHANGED. ONE change: the MEASUREMENT.

  OLD measure (form4b): A[k] = mean over measured hops of |dphi_k(t)| - the
      T_W-integrated wake ledger. Run 5: p slides 2.596 -> 2.040 -> 1.620 -> undefined
      with T_W; p was a window property of the instrument (WAKE-MEMORY debt).
  NEW measure (ADJ-13, memory-free):
      A_mf[k] = (1/N_meas) * sum over measured hops h of |Delta dphi_k(h)|,
      Delta dphi_k(h) = NET wake deposited at seat k by hop h's contacts under the
      unchanged rule (singleton j: -beta*wrap(c_sj); cluster member k:
      sum_j [-beta*wrap(c_sj)]*sig_k*sig_j). Single tick, CURRENT configuration only:
      no decay factor, no history, NO T_W, no instrument constant. beta is a common
      positive scale at fixed beta -> slope invariant (declared). ONE formula.

  MACHINERY ANCHOR (halt on fail): (a) imported form4b ensemble at beta=0.20 seed-1
      must reproduce run-4's p_occ = +2.040 to |dp| <= 5e-4 (print rounding);
      (b) THIS tool's tour (form4b code + passive bookkeeping) must reproduce the
      imported machinery's old-measure slope to |dp| <= 1e-6 (bit-identical tours).
  GRID: beta {0.05, 0.10, 0.20, 0.40} x geometry seeds {1, 2} (seed-2 UNCONDITIONAL),
      64 draws x 40,000 hops, phase seeds 10001-10064 / 20001-20064.
  CLAIM CONJUNCTION: ADJ-11 verbatim (regime AND split-half AND seed-2 replication);
      if met -> p claimed at measured value AND Part C per ADJ-6 verbatim.
  EXPORT (regardless of claim): per-seat dwell-fraction table at beta=0.20, both
      seeds -> flm14_run6_dwell_table.txt (CH07-R2 WELL-DEPTH-AT-CONTACT stake).
"""
import numpy as np, math, sys, os, time
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from flm14_solver import OMEGA0, W, T_W, wrap, fit_exponent
from flm14_form4 import build_seats3d, chsh
import flm14_form4b as f4b

N_DRAWS = 64
HOPS    = 40000
GRID6   = [0.05, 0.10, 0.20, 0.40]           # ADJ-13 committed grid
CENTRE  = 0.20                               # export beta, fixed in ADJ-13
RUN4_P20      = +2.040                       # run-4 record (3 dp), anchor (a)
ANCHOR_TOL_A  = 5e-4                         # print rounding (ADJ-12 convention)
ANCHOR_TOL_B  = 1e-6                         # bit-identity of tours (ADJ-13)

# ============ the two-channel tour, form4b VERBATIM + passive Delta-dphi ledger ============
# Every dynamics line below is flm14_form4b.run_tour_2ch unchanged (probe hooks removed -
# they were passive accumulators, never touched by dynamics; run-5's T_W=27 arm reproduced
# run-4's probe-arm slope exactly, confirming probe-independence). ADDED lines are marked
# "# MF:" and only read/accumulate - they never write theta, dphi, t, s, or any gap.
def run_tour_2ch_mf(pts, nbr, z, beta, phase_seed, hops=HOPS, T_w=T_W):
    N = len(pts); omega = OMEGA0 * z / z.mean()
    base = np.random.default_rng(phase_seed).random(N)
    D = np.linalg.norm(pts[:, None, :] - pts[None, :, :], axis=2)
    theta = base.copy(); tth = np.zeros(N)      # rotor coordinate (lockable)
    dphi = np.zeros(N); tlast = np.zeros(N)     # wake ledger (decaying)
    dwell_sum = np.zeros(N); visits = np.zeros(N)
    amp_sum = np.zeros(N); amp_n = 0
    inc = np.zeros(N); ampmf_sum = np.zeros(N)  # MF: per-hop net deposit + its ledger
    q3s = q4s = 0.0; q3n = q4n = 0
    bad_gaps = 0; lock_dwell_time = 0.0          # instrument guards (expect 0 / 0)
    s = 0; t = 0.0; half = hops // 2; q34 = hops*3//4
    for h in range(hops):
        nb = nbr[s]
        inc[:] = 0.0                             # MF: reset the single-tick deposit
        for k in nb + [s]:
            theta[k] += omega[k]*(t - tth[k]); tth[k] = t
            dphi[k] *= math.exp(-(t - tlast[k]) / T_w); tlast[k] = t
        # ---- constraint channel: star cluster + same-tick rigid kicks ----
        C = [s]; sig = {s: 1.0}; Om = omega[s]
        for j in nb:
            c = (theta[s] + dphi[s] + theta[j] + dphi[j]) % 1.0
            kick = -beta * wrap(c)
            if c < W:                                    # window coincidence -> LOCK
                sig[j] = -1.0; C.append(j)
                Om = sum(sig[k]*omega[k] for k in C) / len(C)
                for k in C:                              # cluster-wide, SAME tick
                    dphi[k] += kick * sig[k] * sig[j]
                    inc[k]  += kick * sig[k] * sig[j]    # MF: same deposit, recorded
            else:
                dphi[j] += kick                          # singleton == ADJ-5 verbatim
                inc[j]  += kick                          # MF: same deposit, recorded
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
            ampmf_sum += np.abs(inc)                     # MF: |net single-tick deposit|
            if h < q34: q3s += g; q3n += 1
            else:       q4s += g; q4n += 1
        t += g + D[s, j_star]
        s = j_star
    A = amp_sum / max(amp_n, 1)
    A_mf = ampmf_sum / max(amp_n, 1)                     # MF: same denominator convention
    return (dwell_sum, visits, A, A_mf, (q3s, q3n, q4s, q4n),
            float((visits > 0).mean()), bad_gaps, lock_dwell_time)

def ensemble_mf(pts, nbr, z, beta, seeds, T_w=T_W):
    """form4b.ensemble verbatim aggregation, carrying BOTH measures."""
    N = len(pts)
    dw = np.zeros(N); vi = np.zeros(N); Astk = []; Mstk = []
    q3s = q4s = 0.0; q3n = q4n = 0; covers = []; per_draw = []
    bad = 0; lockdw = 0.0
    for ps in seeds:
        d, v, A, Amf, (a3, n3, a4, n4), cov, bg, ld = run_tour_2ch_mf(
            pts, nbr, z, beta, ps, T_w=T_w)
        dw += d; vi += v; Astk.append(A); Mstk.append(Amf); covers.append(cov)
        q3s += a3; q3n += n3; q4s += a4; q4n += n4
        per_draw.append((d, A, Amf)); bad += bg; lockdw += ld
    A = np.mean(Astk, axis=0); Amf = np.mean(Mstk, axis=0)
    occ = dw / max(dw.sum(), 1e-300)
    dpv = np.where(vi > 0, dw / np.maximum(vi, 1), 0.0)
    m3, m4 = q3s/max(q3n, 1), q4s/max(q4n, 1)
    drift = abs(m4 - m3) / max(0.5*(m3 + m4), 1e-12)
    return dict(occ=occ, dpv=dpv, A=A, Amf=Amf, vi=vi, dw=dw, drift=drift,
                cover_pool=float((vi > 0).mean()), cover_draw=float(np.mean(covers)),
                per_draw=per_draw, bad=bad, lockdw=lockdw)

def half_p6(per_draw, lo, hi):
    """split-half fit on the MEMORY-FREE measure (pooled halves, form4b convention)."""
    dw = np.sum([d for d, _, _ in per_draw[lo:hi]], axis=0)
    Amf = np.mean([m for _, _, m in per_draw[lo:hi]], axis=0)
    occ = dw / max(dw.sum(), 1e-300)
    return fit_exponent(occ, Amf)

def fit_str(f, why):
    return f"{f[0]:+.3f} (|r|={abs(f[1]):.2f}, n={f[2]})" if f else f"undefined ({why})"

# ================================ mechanical smoke (ADJ-13) ================================
def smoke():
    print("  SMOKE (mechanical only, ADJ-13 allowance): 2 draws x 2000 hops, beta=0.20,")
    print("  seed-1 geometry. Checks tour IDENTITY vs imported form4b; no statistics kept.")
    pts, nbr, z, _, _ = build_seats3d(1)
    worst_d = worst_A = 0.0
    for ps in (10001, 10002):
        d0, v0, A0, q0, c0, b0, l0 = f4b.run_tour_2ch(pts, nbr, z, 0.20, ps, hops=2000)
        d1, v1, A1, M1, q1, c1, b1, l1 = run_tour_2ch_mf(pts, nbr, z, 0.20, ps, hops=2000)
        worst_d = max(worst_d, float(np.max(np.abs(d0 - d1))))
        worst_A = max(worst_A, float(np.max(np.abs(A0 - A1))))
    ok = worst_d == 0.0 and worst_A == 0.0
    print(f"  identity: max|d_dwell| = {worst_d:.2e}  max|d_A_old| = {worst_A:.2e}  "
          f"-> {'PASS (bit-identical tours)' if ok else '** FAULT **'}")
    sys.exit(0 if ok else 1)

# ========================================= run =========================================
if __name__ == "__main__":
    if "--smoke" in sys.argv: smoke()
    print("="*88)
    print("  FLM14 - run 6: MEMORY-FREE MEASURE (ADJ-13, committed before code).")
    print("  Machinery: flm14_form4b two-channel tour VERBATIM; dynamics untouched (T_W=27")
    print("  stays in the dynamics). ONE change: A -> A_mf = per-hop |net wake deposit|,")
    print("  no decay factor, no history, NO T_W in the measure. Claim rule: ADJ-11")
    print("  verbatim. Seed-2 UNCONDITIONAL. Export: dwell table at beta=0.20 (CH07 stake).")
    print("="*88)
    pts, nbr, z, sid1, deg = build_seats3d(1)
    print(f"  geometry seed 1: {len(pts)} seats, degree min/mean/max = "
          f"{int(deg.min())}/{deg.mean():.2f}/{int(deg.max())}")
    seeds1 = [10001 + k for k in range(N_DRAWS)]

    # ---------------- MACHINERY ANCHOR (ADJ-13; halt on fail) ----------------
    print("\n  MACHINERY ANCHOR (tours must be IDENTICAL to run-4/5's):")
    t0 = time.time()
    E_imp = f4b.ensemble(pts, nbr, z, CENTRE, seeds1)
    f_imp, why_imp = fit_exponent(E_imp['occ'], E_imp['A'])
    ok_a = f_imp is not None and abs(f_imp[0] - RUN4_P20) <= ANCHOR_TOL_A
    print(f"    (a) imported form4b @ beta=0.20 seed-1: p_occ(OLD) = {fit_str(f_imp, why_imp)}"
          f"   vs run-4 {RUN4_P20:+.3f} (|dp| <= 5e-4): {'OK' if ok_a else '** FAULT **'}"
          f"   [{time.time()-t0:.0f}s]")
    t0 = time.time()
    E20 = ensemble_mf(pts, nbr, z, CENTRE, seeds1)         # doubles as the grid centre arm
    f_old_new, why_on = fit_exponent(E20['occ'], E20['A'])
    docc = float(np.max(np.abs(E20['occ'] - E_imp['occ'])))
    ok_b = (f_imp is not None and f_old_new is not None
            and abs(f_old_new[0] - f_imp[0]) <= ANCHOR_TOL_B)
    print(f"    (b) THIS tool, OLD measure, same arm:   p_occ(OLD) = {fit_str(f_old_new, why_on)}"
          f"   |dp vs (a)| = {abs(f_old_new[0]-f_imp[0]) if (f_imp and f_old_new) else float('nan'):.2e}"
          f" (<= 1e-6): {'OK' if ok_b else '** FAULT **'}   max|d_occ| = {docc:.2e}"
          f"   [{time.time()-t0:.0f}s]")
    if not (ok_a and ok_b):
        print("  HALT per ADJ-13: machinery anchor failed - instrument fault, nothing bankable.")
        sys.exit(1)
    print("    anchors PASS -> the measure switch is licensed; dynamics proven unchanged.")

    # ---------------- production grid: beta x geometry seed ----------------
    geos = {1: (pts, nbr, z, sid1, deg, seeds1)}
    pts2, nbr2, z2, sid2, deg2 = build_seats3d(2)
    geos[2] = (pts2, nbr2, z2, sid2, deg2, [20001 + k for k in range(N_DRAWS)])
    print(f"\n  geometry seed 2: {len(pts2)} seats, degree min/mean/max = "
          f"{int(deg2.min())}/{deg2.mean():.2f}/{int(deg2.max())}")
    R = {}
    for gs in (1, 2):
        P, NB, Z, _, _, SD = geos[gs]
        print(f"\n  ---- geometry seed {gs} (phase seeds {SD[0]}-{SD[-1]}) ----")
        for b in GRID6:
            t0 = time.time()
            E = E20 if (gs == 1 and b == CENTRE) else ensemble_mf(P, NB, Z, b, SD)
            fmf, whymf = fit_exponent(E['occ'], E['Amf'])
            fold, whyold = fit_exponent(E['occ'], E['A'])
            fdw, whydw = fit_exponent(E['dpv'], E['Amf'])
            sh = None
            if fmf:
                h1, _ = half_p6(E['per_draw'], 0, 32); h2, _ = half_p6(E['per_draw'], 32, 64)
                sh = (h1, h2)
            R[(gs, b)] = dict(E=E, fmf=fmf, sh=sh)
            shs = (f"   split-half p_mf: " + (f"{sh[0][0]:+.3f}" if sh[0] else "undef")
                   + " / " + (f"{sh[1][0]:+.3f}" if sh[1] else "undef")) if sh else ""
            print(f"  beta={b:4.2f}:  p_occ(MF) = {fit_str(fmf, whymf)}   "
                  f"[old-measure diagnostic: {fit_str(fold, whyold)}]")
            print(f"             p_dwell(MF) = {fit_str(fdw, whydw)}")
            print(f"             drift {E['drift']:.4f} (gate <0.01: "
                  f"{'PASS' if E['drift'] < 0.01 else 'FAIL'})   coverage pooled "
                  f"{E['cover_pool']*100:.0f}% / per-draw {E['cover_draw']*100:.0f}%   "
                  f"guards: bad-gaps {E['bad']}, locked-dwell {E['lockdw']:.2e}   "
                  f"[{time.time()-t0:.0f}s]" + shs)
        # ---- fixed-mask discipline (ADJ-13; run-5 mask-erosion lesson) ----
        A20m, o20 = R[(gs, 0.20)]['E']['Amf'], R[(gs, 0.20)]['E']['occ']
        A40m, o40 = R[(gs, 0.40)]['E']['Amf'], R[(gs, 0.40)]['E']['occ']
        m20 = (A20m > 0.05*A20m.max()) & (A20m > 0) & (o20 > 0)
        m = m20 & (A40m > 0) & (o40 > 0)
        if m.sum() >= 3:
            lx, ly = np.log(A40m[m]), np.log(o40[m])
            rr = float(np.corrcoef(lx, ly)[0, 1]); sl = float(np.polyfit(lx, ly, 1)[0])
            p20 = R[(gs, 0.20)]['fmf'][0] if R[(gs, 0.20)]['fmf'] else None
            cls = ("no beta=0.20 reference (p_mf undefined)" if p20 is None else
                   "SUPPORTED (seat-selection, within 0.3 of centre)" if abs(sl - p20) <= 0.3 else
                   "CONTRADICTED (dynamics steepen)" if sl >= 2.5 else
                   "INTERMEDIATE (neither criterion)")
            print(f"  fixed-mask check seed {gs}: beta=0.40 slope on beta=0.20's MF mask "
                  f"(n={int(m.sum())}) = {sl:+.3f} (|r|={abs(rr):.2f})  -> mask-erosion: {cls}")
        else:
            print(f"  fixed-mask check seed {gs}: only {int(m.sum())} seats survive the "
                  f"fixed mask - slope not computable (reported, not classified)")

    # ---------------- CLAIM CONJUNCTION (ADJ-11 verbatim, on the MF table) ----------------
    print("\n" + "="*88)
    print("  CLAIM CONJUNCTION (ADJ-11 verbatim; seed 1 = committed instrument, MF measure)")
    print("="*88)
    blockers = []
    defined = [(b, R[(1, b)]['fmf'][0]) for b in GRID6
               if R[(1, b)]['fmf'] and R[(1, b)]['E']['drift'] < 0.01]
    stable = []
    for i0 in range(len(defined)):
        for i1 in range(i0 + 2, len(defined)):
            win = defined[i0:i1+1]; bs = [b for b, _ in win]
            if GRID6.index(bs[-1]) - GRID6.index(bs[0]) != len(bs) - 1: continue
            ps = np.array([p for _, p in win]); med = np.median(ps)
            if np.all(np.abs(ps - med) <= 0.3) and len(win) > len(stable): stable = win
    p_med = None; b_med = None
    if stable:
        bs = [b for b, _ in stable]; psv = [p for _, p in stable]
        p_med = float(np.median(psv))
        b_med = min(bs, key=lambda b: abs(dict(stable)[b] - p_med))
        print(f"  leg (i) stable regime: PASS - beta in [{bs[0]}, {bs[-1]}] "
              f"({len(bs)} consecutive), p_occ(MF) = {[f'{p:+.3f}' for p in psv]}, "
              f"median = {p_med:+.4f}")
    else:
        why_i = "; ".join(
            f"beta={b}: " + ("drift FAIL" if (R[(1, b)]['fmf'] and
                             R[(1, b)]['E']['drift'] >= 0.01) else
                             "undefined" if not R[(1, b)]['fmf'] else "defined")
            for b in GRID6)
        print(f"  leg (i) stable regime: FAIL ({why_i}; no 3-consecutive window in band)")
        blockers.append("leg (i): no 3 consecutive drift-passing betas within the 0.3 band")
    sh_ok = True
    if stable:
        for b, p in stable:
            h1, h2 = R[(1, b)]['sh']
            ok = (h1 is not None and h2 is not None
                  and abs(h1[0] - p) <= 0.4 and abs(h2[0] - p) <= 0.4)
            print(f"  leg (ii) split-half @ beta={b}: "
                  + (f"{h1[0]:+.3f}" if h1 else "undef") + " / "
                  + (f"{h2[0]:+.3f}" if h2 else "undef")
                  + f"  vs pooled {p:+.3f} (+-0.4)  [{'OK' if ok else 'FAIL'}]")
            if not ok:
                blockers.append(f"leg (ii): split-half broken at beta={b}")
            sh_ok &= ok
        # leg (iii): seed-2 replication at the regime-median beta (64 draws, unconditional arm)
        f2 = R[(2, b_med)]['fmf']; sh2 = R[(2, b_med)]['sh']
        p1 = dict(stable)[b_med]
        band_ok = f2 is not None and abs(f2[0] - p1) <= 0.3
        sh2_ok = (f2 is not None and sh2 is not None and sh2[0] is not None
                  and sh2[1] is not None and abs(sh2[0][0] - f2[0]) <= 0.4
                  and abs(sh2[1][0] - f2[0]) <= 0.4)
        rep_ok = band_ok and sh2_ok
        d2v = R[(2, b_med)]['E']['drift']
        print(f"  leg (iii) seed-2 @ beta={b_med}: p_occ(MF) = "
              + (f"{f2[0]:+.3f}" if f2 else "undefined")
              + f" vs seed-1 {p1:+.3f} (band <=0.3: {'OK' if band_ok else 'FAIL'});"
              f" split-half " + (f"{sh2[0][0]:+.3f}/{sh2[1][0]:+.3f}"
                                 if sh2 and sh2[0] and sh2[1] else "undef")
              + f" (+-0.4: {'OK' if sh2_ok else 'FAIL'})  [{'PASS' if rep_ok else 'FAIL'}]"
              f"   (seed-2 drift {d2v:.4f} - DRIFT-GEOMETRY caveat, reported not hidden)")
        if not rep_ok:
            blockers.append(f"leg (iii): seed-2 replication FAIL at beta={b_med}")
    claim = (not blockers) and stable and sh_ok
    print("\n  CLAIM DECISION: " + ("CLAIMED - p = " + f"{p_med:+.4f}" if claim else "REFUSED"))
    if not claim:
        print("    Blocking condition(s), named:")
        for x in blockers: print(f"      - {x}")

    # ---------------- Part C (ADJ-6 verbatim; only on the full conjunction) ----------------
    if claim and p_med is not None:
        print("\n" + "="*88)
        print("  PART C - CHSH via the constraint channel (ADJ-6 verbatim), "
              f"p = {p_med:+.4f} (measured)")
        print("="*88)
        N = 2_000_000
        S, worst, rows = chsh(p_med, N, np.random.default_rng(11))
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

    # ---------------- EXPORT: dwell table at beta=0.20, both seeds (CH07 stake) ----------------
    out = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                       "flm14_run6_dwell_table.txt")
    with open(out, "w", encoding="utf-8") as fh:
        fh.write("# FLM14 run-6 per-seat dwell-fraction table (ADJ-13 export)\n")
        fh.write("# J. C. Harvey, Melbourne - 2026-07-07. Tool: flm14_form6.py (exit 0).\n")
        fh.write("# Cross-program stake: CH07-R2 root WELL-DEPTH-AT-CONTACT - the chemistry\n")
        fh.write("# well is x17.2 too deep because seats count at FULL simultaneous weight;\n")
        fh.write("# the dwell-WEIGHTED well uses THESE fractions. Instrument: two-channel\n")
        fh.write("# tour (flm14_form4b dynamics verbatim, T_W=27), beta=0.20 (centre),\n")
        fh.write("# 64 phase draws x 40,000 hops, measurement half, pooled per ADJ-8.\n")
        fh.write("# dwell_frac = seat dwell time / total dwell time (the Born-mapped\n")
        fh.write("# occupancy); visit_frac = landing-count fraction; dpv = dwell per visit;\n")
        fh.write("# A_mf = memory-free per-hop |net wake deposit| (ADJ-13 measure).\n")
        for gs in (1, 2):
            P, NB, Z, SIDg, DEGg, SD = geos[gs]
            E = R[(gs, CENTRE)]['E']
            vfrac = E['vi'] / max(E['vi'].sum(), 1e-300)
            fh.write(f"\n# geometry seed {gs}: {len(P)} seats, phase seeds "
                     f"{SD[0]}-{SD[-1]}, drift {E['drift']:.4f} "
                     f"({'PASS' if E['drift'] < 0.01 else 'FAIL - DRIFT-GEOMETRY caveat'})\n")
            fh.write("# seat  shell  radius      x        y        z     deg  z_eff  "
                     "omega    dwell_frac   visit_frac   dpv          A_mf\n")
            om = OMEGA0 * Z / Z.mean()
            for i in range(len(P)):
                rad = float(np.linalg.norm(P[i]))
                fh.write(f"{i:5d}  {int(SIDg[i]):5d}  {rad:6.3f}  "
                         f"{P[i][0]:+7.3f} {P[i][1]:+7.3f} {P[i][2]:+7.3f}  "
                         f"{int(DEGg[i]):3d}  {Z[i]:5.1f}  {om[i]:.4f}  "
                         f"{E['occ'][i]:.6e}  {vfrac[i]:.6e}  {E['dpv'][i]:.6e}  "
                         f"{E['Amf'][i]:.6e}\n")
    print(f"\n  EXPORT written: {out}")
    print("  (per-seat dwell fractions at beta=0.20, both geometry seeds - the CH07")
    print("   WELL-DEPTH-AT-CONTACT input, delivered regardless of the claim outcome.)")

    print("\n" + "="*88)
    print("  F6: one rule throughout - dynamics bit-identical to run-4/5 (anchors (a)+(b)");
    print("  passed above); T_W, W, OMEGA0 untouched; the ONE change is the measurement")
    print("  A -> A_mf (ADJ-13, declared before code); no constant re-tuned anywhere.")
    print("="*88)
