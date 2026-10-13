"""
FLM14 - flm14_form5.py - RUN 5: the CLAIM DECISION (ADJ-12).
J. C. Harvey, Melbourne - 2026-07-05.

Instrument committed in RUN_LOG.md ADJ-12 BEFORE this file was written. Machinery =
flm14_form4b VERBATIM (two-channel tour); T_W = 27 stays the committed constant
everywhere except the declared scan. Nothing re-tuned, nothing fitted.

  (1) seed-2 replication UNCONDITIONAL: geometry seed 2, beta {0.10, 0.20},
      64 draws x 40k hops, phase seeds 20001-20064.
  (2) T_W scan {13.5, 27, 54, 108} at beta=0.20 seed-1; machinery anchor: the
      13.5/27/54 points must reproduce run-4 (deterministic identity; run 4 persisted
      p at 3 dp, so the anchor is operationalised at |dp| <= 5e-4 = print rounding).
      Convergence rule declared in ADJ-12 (PLATEAU / CONVERGING / NO-PLATEAU).
  (3) beta=0.40 mask-erosion check (report, don't gate): fixed-mask slope.
  (4) claim conjunction unchanged; run-4 leg (i) cited, not re-run (deterministic).
"""
import numpy as np, math, sys, os, time
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from flm14_solver import T_W, fit_exponent
from flm14_form4 import build_seats3d, chsh
from flm14_form4b import ensemble, half_p

N_DRAWS = 64

# ---- run-4 results, cited from flm14_form4b_results.txt (T_W=27, seed 1) ----
RUN4_P    = {0.05: +2.278, 0.10: +2.109, 0.20: +2.040, 0.40: +2.855, 0.80: +3.769}
RUN4_OK   = {0.10, 0.20, 0.40}            # defined AND drift-PASS
RUN4_GRID = [0.02, 0.05, 0.10, 0.20, 0.40, 0.80]
RUN4_SH   = {0.10: ("+2.161", "undef"), 0.20: ("+2.015", "+2.128"),
             0.40: ("+3.005", "+2.760")}
RUN4_TW   = {13.5: +2.596, 27.0: +2.040, 54.0: +1.620}

def fit_str(f, why):
    return f"{f[0]:+.3f} (|r|={abs(f[1]):.2f}, n={f[2]})" if f else f"undefined ({why})"

if __name__ == "__main__":
    print("="*88)
    print("  FLM14 - run 5: CLAIM DECISION.  Spec: RUN_LOG.md ADJ-12 (committed before")
    print("  code). Machinery: flm14_form4b two-channel tour, verbatim. Pre-declared:")
    print("  claim leg (i) is already known-FAILED from run-4's table; legs (ii)/(iii)")
    print("  and the T_W diagnosis run UNCONDITIONALLY (their evidence stands alone).")
    print("="*88)

    # ================= (1) seed-2 replication, unconditional =================
    print("\n  (1) SEED-2 REPLICATION (geometry seed 2, 64 draws x 40k, seeds 20001-20064)")
    pts2, nbr2, z2, _, deg2 = build_seats3d(2)
    print(f"      geometry seed 2: {len(pts2)} seats, degree min/mean/max = "
          f"{int(deg2.min())}/{deg2.mean():.2f}/{int(deg2.max())}")
    seed2 = {}
    for b in (0.10, 0.20):
        t0 = time.time()
        E = ensemble(pts2, nbr2, z2, b, [20001 + k for k in range(N_DRAWS)])
        fo, why = fit_exponent(E['occ'], E['A'])
        h1, _ = half_p(E['per_draw'], 0, 32); h2, _ = half_p(E['per_draw'], 32, 64)
        band_ok = fo is not None and abs(fo[0] - RUN4_P[b]) <= 0.3
        sh_ok = (fo is not None and h1 is not None and h2 is not None
                 and abs(h1[0] - fo[0]) <= 0.4 and abs(h2[0] - fo[0]) <= 0.4)
        rep = fo is not None and band_ok and sh_ok
        seed2[b] = dict(fo=fo, rep=rep)
        print(f"      beta={b:4.2f}: p_occ = {fit_str(fo, why)}   drift {E['drift']:.4f} "
              f"({'PASS' if E['drift'] < 0.01 else 'FAIL'})   "
              f"coverage {E['cover_pool']*100:.0f}%/{E['cover_draw']*100:.0f}%   "
              f"[{time.time()-t0:.0f}s]")
        print(f"                 vs seed-1 {RUN4_P[b]:+.3f} (band <=0.3: "
              f"{'OK' if band_ok else 'FAIL'})   split-half: "
              + (f"{h1[0]:+.3f}" if h1 else "undef") + " / "
              + (f"{h2[0]:+.3f}" if h2 else "undef")
              + f" (+-0.4: {'OK' if sh_ok else 'FAIL'})   REPLICATION: "
              f"{'PASS' if rep else 'FAIL'}")

    # ================= (2) T_W diagnosis at beta=0.20, seed 1 =================
    print("\n  (2) T_W DIAGNOSIS (beta=0.20, geometry seed 1, 64 draws each)")
    pts, nbr, z, _, _ = build_seats3d(1)
    pTW = {}
    anchor_fault = False
    for tw in (13.5, 27.0, 54.0, 108.0):
        t0 = time.time()
        E = ensemble(pts, nbr, z, 0.20, [10001 + k for k in range(N_DRAWS)], T_w=tw)
        fo, why = fit_exponent(E['occ'], E['A'])
        pTW[tw] = fo
        anch = ""
        if tw in RUN4_TW:
            ok = fo is not None and abs(fo[0] - RUN4_TW[tw]) <= 5e-4
            anch = (f"   anchor vs run-4 {RUN4_TW[tw]:+.3f}: "
                    f"{'OK' if ok else '** INSTRUMENT FAULT **'}")
            anchor_fault |= not ok
        print(f"      T_W={tw:5.1f}: p_occ = {fit_str(fo, why)}{anch}   [{time.time()-t0:.0f}s]")
        if tw == 27.0: E27 = E   # reused by (3): the committed-instrument centre
    if anchor_fault:
        print("      HALT per ADJ-12: anchor mismatch — results not bankable."); sys.exit(1)
    if all(pTW[t] is not None for t in (27.0, 54.0, 108.0)):
        d1 = pTW[54.0][0] - pTW[27.0][0]
        d2 = pTW[108.0][0] - pTW[54.0][0]
        print(f"      Delta1 = p(54)-p(27) = {d1:+.3f};  Delta2 = p(108)-p(54) = {d2:+.3f}")
        if abs(d2) <= 0.15:
            print(f"      -> PLATEAU (|Delta2| <= 0.15): instrument p := p(108) = "
                  f"{pTW[108.0][0]:+.4f}")
            tw_verdict = f"PLATEAU at p(108) = {pTW[108.0][0]:+.4f}"
        elif abs(d2) <= 0.5*abs(d1):
            r = d2/d1
            p_inf = pTW[108.0][0] + d2*r/(1 - r)
            print(f"      -> CONVERGING (|Delta2| <= 0.5|Delta1|): geometric DIAGNOSTIC "
                  f"p_inf ~= {p_inf:+.3f} (r={r:+.3f}); WAKE-MEMORY stays OPEN")
            tw_verdict = f"CONVERGING (diagnostic p_inf ~= {p_inf:+.3f}); OPEN"
        else:
            print("      -> NO PLATEAU (monotone slide): p is NOT a law on this "
                  "instrument; WAKE-MEMORY unresolved — reported as such")
            tw_verdict = "NO PLATEAU - monotone slide; p is not a law here"
    else:
        print("      -> scan point(s) undefined; T_W diagnosis inconclusive (reported)")
        tw_verdict = "inconclusive (undefined scan point)"

    # ================= (3) beta=0.40 mask-erosion check (report only) =================
    print("\n  (3) BETA=0.40 UPTURN - fixed-mask check (report, don't gate)")
    E40 = ensemble(pts, nbr, z, 0.40, [10001 + k for k in range(N_DRAWS)])
    A20, occ20 = E27['A'], E27['occ']
    A40, occ40 = E40['A'], E40['occ']
    m20 = (A20 > 0.05*A20.max()) & (A20 > 0) & (occ20 > 0)      # fit_exponent's mask
    m = m20 & (A40 > 0) & (occ40 > 0)
    lx, ly = np.log(A40[m]), np.log(occ40[m])
    r = float(np.corrcoef(lx, ly)[0, 1])
    slope = float(np.polyfit(lx, ly, 1)[0])
    free40, why40 = fit_exponent(occ40, A40)
    print(f"      beta=0.40 own-mask p_occ = {fit_str(free40, why40)} (run-4: +2.855)")
    print(f"      beta=0.40 slope on the FIXED beta=0.20 mask (n={int(m.sum())}): "
          f"{slope:+.3f} (|r|={abs(r):.2f})")
    hyp = ("SUPPORTED (within 0.3 of the centre p — the upturn is seat-selection)"
           if abs(slope - RUN4_P[0.20]) <= 0.3 else
           "CONTRADICTED (slope stays steep — the dynamics genuinely steepen)"
           if slope >= 2.5 else
           "INTERMEDIATE (neither criterion met — reported without classification)")
    print(f"      mask-erosion hypothesis: {hyp}")

    # ================= (4) the claim conjunction =================
    print("\n  (4) CLAIM CONJUNCTION (ADJ-11, unchanged)")
    # leg (i): stable regime on the committed instrument - run-4 table, cited
    blockers = []
    ok_bs = [b for b in RUN4_GRID if b in RUN4_OK]
    regime = []
    for i0 in range(len(ok_bs)):
        for i1 in range(i0 + 2, len(ok_bs)):
            bs = ok_bs[i0:i1+1]
            if RUN4_GRID.index(bs[-1]) - RUN4_GRID.index(bs[0]) != len(bs) - 1: continue
            ps = np.array([RUN4_P[b] for b in bs]); med = np.median(ps)
            if np.all(np.abs(ps - med) <= 0.3) and len(bs) > len(regime): regime = bs
    if regime:
        print(f"      leg (i) stable regime: PASS over beta {regime}")
    else:
        print("      leg (i) stable regime: FAIL - beta=0.05 drift-FAIL and beta=0.40")
        print("              band-break (+2.855 vs median +2.109) pincer the grid (run-4)")
        blockers.append("leg (i): no 3 consecutive drift-passing betas within the 0.3 band")
    # leg (ii): split-half at the would-be centre (run-4, cited)
    sh10 = RUN4_SH[0.10]; sh20 = RUN4_SH[0.20]
    print(f"      leg (ii) split-half (run-4): beta=0.10 {sh10[0]}/{sh10[1]} FAIL; "
          f"beta=0.20 {sh20[0]}/{sh20[1]} OK")
    if sh10[1] == "undef":
        blockers.append("leg (ii): split-half undefined in one half at beta=0.10")
    # leg (iii): seed-2 (this run)
    for b in (0.10, 0.20):
        st = "PASS" if seed2[b]['rep'] else "FAIL"
        print(f"      leg (iii) seed-2 @ beta={b}: {st}")
        if not seed2[b]['rep']:
            blockers.append(f"leg (iii): seed-2 replication FAIL at beta={b}")
    claim = not blockers
    print("\n  CLAIM DECISION: " + ("CLAIMED" if claim else "REFUSED"))
    if claim:
        ps = [RUN4_P[b] for b in regime]; p_med = float(np.median(ps))
        print(f"    p claimed at measured value: {p_med:+.4f} -> Part C (ADJ-6) runs.")
        N = 2_000_000
        S, worst, rows = chsh(p_med, N, np.random.default_rng(11))
        for a, b, Eab, dA, dB in rows:
            print(f"    (a={a:5.1f}, b={b:5.1f})  E={Eab:+.4f}   marginals {dA:.4f}/{dB:.4f}")
        print(f"    S(sampled, N={N}) = {S:+.4f}   (Tsirelson 2sqrt2 = {2*np.sqrt(2):.4f} "
              f"at p=2)   worst marginal dev {worst:.4f} (Synchrony check <= 0.002)")
    else:
        print("    Blocking condition(s), named:")
        for x in blockers: print(f"      - {x}")
        print("    Part C: NOT RUN (committed condition).")
    print(f"\n  T_W verdict carried to the ledger: {tw_verdict}")
    print("\n" + "="*88)
    print("  F6: machinery identical to run 4 in every arm; T_W varied ONLY inside the")
    print("  declared scan; no constant re-tuned; run-4 values cited, not adjusted.")
    print("="*88)
