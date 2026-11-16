"""
FLM14 - flm14_form7_partC.py - RUN 7: Part C-prime, the EMERGENT-CHANNEL BELL TEST (ADJ-14).
J. C. Harvey, Melbourne - 2026-07-07.

Spec: RUN_LOG.md ADJ-14 + the ADJ-14 build note, BOTH committed before this file was
written. QM05 RUN 2 retired the ADJ-6 C^p/(C^p+S^p) transcription (Bell is LINEAR in one
conserved kick); Part C-prime's job is to show the FLM14 instrument REALIZES the
conserved-kick channel, not to produce p = 2.

  PAIR      two wings = two seat annuli (run-4 3-D shell geometry, build_seats3d(1), one
            mirrored copy), joined by ONE permanent gear-locked rigid pair {b_L, b_R}
            (ADJ-11 lock machinery). k-hat = the bridge bond's contact phase, conserved
            by the rigidity theorem. One electron tours BOTH wings (one tour, two wings).
  STAGE 1   L1 conservation (within-trial bridge-phase drift, machine precision);
            L2 memory-free native counting readout (sign of sector dwell-difference,
            NO cosine anywhere in the readout); L3 marginals |P(+/-)-0.5| <= 0.002 at
            every setting of both wings at every beta. ALL THREE or Part C-prime stops.
  STAGE 2   C1 E(Delta) on {0,15,...,90} deg, fit E = k*cos(2*Delta - psi), RMS gate
            0.05, k and psi reported wherever they land (k < 1 expected, publishable);
            C2 CHSH at standard angles, S <= 2.8334; C3 unlocked control (same seeds,
            same readout), S_unlocked <= 2.004, locked > unlocked at >= 5 sigma =
            transmission demonstrated. beta scanned {0.10, 0.20, 0.40}, nothing fitted.
  ANCHORS   (a) imported form4b ensemble reproduces run-4/6's p_occ = +2.040 (<= 5e-4);
            (b) THIS tool's core, single-wing mode, reproduces (a) to |dp| <= 1e-6
            (bit-identical tours). Locked-dwell (transient) 0.00e+00 at every arm.
            Any anchor fault: halt, exit 1, nothing bankable.
"""
import numpy as np, math, sys, os, time
try: sys.stdout.reconfigure(encoding='utf-8')
except Exception: pass
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from flm14_solver import OMEGA0, W, T_W, wrap, fit_exponent
from flm14_form4 import build_seats3d
import flm14_form4b as f4b

# ---------------- committed constants (ADJ-14 + build note; declared, not tuned) ----------------
BETAS       = [0.10, 0.20, 0.40]          # ADJ-14 scan; no beta fitted
N_TRIALS    = 2560                        # build note: trial multiplicity for sign readout
HOPS_TRIAL  = 10000                       # build note: ~several bridge crossings/measured half
ANCHOR_HOPS = 40000                       # run-4/6 arm convention (anchor legs only)
RUN4_P20    = +2.040                      # the record anchor (3 dp)
TOL_A, TOL_B = 5e-4, 1e-6                 # ADJ-12 / ADJ-13 conventions
DELTA_GRID  = [0, 15, 30, 45, 60, 75, 90]                    # C1 grid, degrees
CHSH_PAIRS  = [(0.0, 22.5), (0.0, 67.5), (45.0, 22.5), (45.0, 67.5)]
CHSH_SIGNS  = [+1, -1, +1, +1]                                # S = E00 - E01 + E10 + E11
L_SETTINGS  = [0.0, 15.0, 30.0, 45.0, 60.0, 75.0, 90.0]       # wing-L analyzer angles used
R_SETTINGS  = [0.0, 22.5, 67.5]                               # wing-R analyzer angles used
GATE_L1     = 1e-12                       # "machine precision" operationalised; expect 0.00e+00
GATE_L3     = 0.002                       # ADJ-14 committed (Synchrony anchor)
GATE_C1_RMS = 0.05
GATE_C2     = 2.8334
GATE_C3_U   = 2.004
def seed0(beta): return 700000 + 100*int(round(1000*beta))    # + trial index (declared)

# ================= the tour core: flm14_form4b.run_tour_2ch + the pair extension =================
# Every dynamics line is form4b's run_tour_2ch unchanged (probe hooks removed; amp accumulation
# behind a flag - passive, never feeds back). Lines marked "# PAIR:" are the build-note
# extension: a permanent rigid port pair {pL,pR} (sigma +1/-1, Omega_P = mean sigma*omega),
# ports evolve/close windows at the rigid rate, kicks/locks addressed to a port engage the
# whole permanent cluster the SAME tick. With ports=None this function is form4b verbatim.
def run_tour_pair(pts, nbr, z, beta, phase_seed, hops, D, ports=None, port_locked=True,
                  amp_track=False, T_w=T_W):
    N = len(pts); omega = OMEGA0 * z / z.mean()
    base = np.random.default_rng(phase_seed).random(N)
    theta = base.copy(); tth = np.zeros(N)      # rotor coordinate (lockable)
    dphi = np.zeros(N); tlast = np.zeros(N)     # wake ledger (decaying)
    dwell_sum = np.zeros(N); visits = np.zeros(N)
    amp_sum = np.zeros(N) if amp_track else None; amp_n = 0
    q3s = q4s = 0.0; q3n = q4n = 0
    bad_gaps = 0; tl_dwell = 0.0                 # guards (expect 0 / 0.00e+00)
    perm_dwell = 0.0; n_static = 0; crossings = 0
    rate = omega.copy()                          # PAIR: theta-evolution / window rate
    pL = pR = -1; Om_P = 0.0; psig = None
    if ports is not None and port_locked:
        pL, pR = ports
        psig = {pL: 1.0, pR: -1.0}               # PAIR: g=-1 across the bridge
        Om_P = 0.5*(psig[pL]*omega[pL] + psig[pR]*omega[pR])
        rate[pL] = psig[pL]*Om_P; rate[pR] = psig[pR]*Om_P
    elif ports is not None:
        pL, pR = ports                           # unlocked control: natural rates
    cb0 = None; l1_drift = 0.0
    half_n = N // 2                              # wing split (build note: L = first half)
    s = 0; t = 0.0; half = hops // 2; q34 = hops*3//4
    for h in range(hops):
        nb = nbr[s]
        upd = nb + [s]
        if ports is not None:                    # PAIR: keep the bridge pair current
            if pL not in upd: upd.append(pL)
            if pR not in upd: upd.append(pR)
        for k in upd:
            theta[k] += rate[k]*(t - tth[k]); tth[k] = t
            dphi[k] *= math.exp(-(t - tlast[k]) / T_w); tlast[k] = t
        if ports is not None:                    # PAIR: L1 - conserved director phase
                                                 # (tracked in the unlocked control too,
                                                 #  as the severing contrast)
            cb = (theta[pL] + dphi[pL] + theta[pR] + dphi[pR]) % 1.0
            if cb0 is None: cb0 = cb
            else:
                dcb = abs(cb - cb0)
                l1_drift = max(l1_drift, min(dcb, 1.0 - dcb))
        # ---- constraint channel: star cluster + same-tick rigid kicks (ADJ-11) ----
        C = [s]; sig = {s: 1.0}
        if psig is not None and s in (pL, pR):   # PAIR: s's permanent cluster joins whole
            o = pR if s == pL else pL
            sig[o] = -1.0; C.append(o)
        Om = sum(sig[k]*omega[k] for k in C) / len(C)
        n_tlocks = 0
        for j in nb:
            c = (theta[s] + dphi[s] + theta[j] + dphi[j]) % 1.0
            kick = -beta * wrap(c)
            if c < W:                                    # window coincidence -> LOCK
                if j in sig:                             # PAIR: same-cluster re-affirm
                    for k in C: dphi[k] += kick * sig[k] * sig[j]
                else:
                    sig[j] = -sig[s]; C.append(j); n_tlocks += 1
                    if psig is not None and j in (pL, pR):
                        o = pR if j == pL else pL        # PAIR: partner joins rigidly
                        if o not in sig: sig[o] = -sig[j]; C.append(o)
                    Om = sum(sig[k]*omega[k] for k in C) / len(C)
                    for k in C:                          # cluster-wide, SAME tick
                        dphi[k] += kick * sig[k] * sig[j]
            else:
                if j in sig:                             # PAIR: same-cluster kick
                    for k in C: dphi[k] += kick * sig[k] * sig[j]
                elif psig is not None and j in (pL, pR):
                    o = pR if j == pL else pL            # PAIR: cross-bridge, SAME tick
                    dphi[j] += kick; dphi[o] += -kick    # sigma_k*sigma_j = +1 / -1
                else:
                    dphi[j] += kick                      # singleton == ADJ-5 verbatim
        # ---- departure: gaps with final cluster state ----
        rate_s = sig[s]*Om if len(C) >= 2 else omega[s]
        gaps = np.empty(len(nb))
        for a, j in enumerate(nb):
            c = (theta[s] + dphi[s] + theta[j] + dphi[j]) % 1.0
            if c < W or (j in sig):   # PAIR amendment 1: LOCKED bond => gap 0 (ADJ-11
                gaps[a] = 0.0         # rule; anchor-mode no-op - transient locks hold
            else:                     # c < W exactly, the run-4/6 theorem)
                rj = rate[j] if (psig is not None and j in (pL, pR)) else omega[j]
                r = (rate_s + rj)
                if r <= 0:
                    gaps[a] = np.inf
                    if ports is None: bad_gaps += 1      # form4b verbatim (anchor mode)
                    else: n_static += 1                  # PAIR: static window, declared
                else:
                    gaps[a] = (1.0 - c) / r
        a_star = int(np.argmin(gaps)); g = float(gaps[a_star]); j_star = nb[a_star]
        if not np.isfinite(g):                           # no departure path (expect never)
            bad_gaps += 10**6; g = 0.0; j_star = nb[0]
        # dwell evolution (theorem: g > 0 => no transient locks)
        if g > 0 and len(C) >= 2:
            if ports is None or n_tlocks > 0: tl_dwell += g
            else: perm_dwell += g                        # PAIR: frozen pair, Om = 0
            for k in C:
                theta[k] += sig[k]*Om*g; tth[k] = t + g   # release with memory
        if h >= half:
            dwell_sum[s] += g; visits[s] += 1
            if amp_track:
                amp_sum += np.abs(dphi * np.exp(-(t - tlast) / T_w)); amp_n += 1
            if h < q34: q3s += g; q3n += 1
            else:       q4s += g; q4n += 1
        if ports is not None and (s < half_n) != (j_star < half_n): crossings += 1
        t += g + D[s, j_star]
        s = j_star
    A = (amp_sum / max(amp_n, 1)) if amp_track else None
    return dict(dwell=dwell_sum, visits=visits, A=A, q=(q3s, q3n, q4s, q4n),
                cover=float((visits > 0).mean()), bad=bad_gaps, tl_dwell=tl_dwell,
                perm_dwell=perm_dwell, n_static=n_static, crossings=crossings,
                l1=l1_drift, cb0=cb0)

# ==================================== pair geometry ====================================
def build_pair():
    pts1, nbr1, z1, sid1, deg1 = build_seats3d(1)
    n = len(pts1)
    inner = np.where(sid1 == 0)[0]                        # build amendment 3: port = the
    bL = int(inner[np.argmax(pts1[inner, 2])])            # INNER-shell max-z seat (core
                                                          # pole; outer pole is starved
                                                          # by the tour's self-trapping)
    bl = [float(np.linalg.norm(pts1[i] - pts1[j]))
          for i in range(n) for j in nbr1[i] if j > i]
    d_b = float(np.median(bl))                            # bridge = one median bond long
    zp = float(pts1[bL, 2])
    ptsR = pts1 * np.array([1.0, 1.0, -1.0])
    ptsR[:, 2] += 2*zp + d_b                              # mirror + translate: pole-to-pole
    pts = np.vstack([pts1, ptsR])
    nbr = [list(x) for x in nbr1] + [[j + n for j in x] for x in nbr1]
    bR = bL + n
    nbr[bL].insert(1, bR); nbr[bR].insert(1, bL)          # bridge bond SECOND both ports
                                                          # (build amendment 2: first =
                                                          #  ping-pong trap, last = starved)
    z = np.concatenate([z1, z1]).astype(float)
    z[bL] += 1.0; z[bR] += 1.0                            # real bond: port z += 1 (ADJ-8)
    wing = np.array([0]*n + [1]*n)
    az = np.mod(np.arctan2(pts[:, 1], pts[:, 0]), np.pi)  # director azimuth (period pi)
    D = np.linalg.norm(pts[:, None, :] - pts[None, :, :], axis=2)
    return dict(pts=pts, nbr=nbr, z=z, wing=wing, az=az, D=D, ports=(bL, bR),
                n=n, d_b=d_b, sid=np.concatenate([sid1, sid1]))

def sector_signs(az_wing, a_deg):
    a = math.radians(a_deg)
    return np.where(np.mod(az_wing - a, np.pi) < np.pi/2, 1.0, -1.0)

# ================================== production arm ==================================
def run_arm(G, beta, locked, label):
    n = G['n']; azL = G['az'][:n]; azR = G['az'][n:]
    svL = {a: sector_signs(azL, a) for a in L_SETTINGS}
    svR = {b: sector_signs(azR, b) for b in R_SETTINGS}
    dL = np.zeros((N_TRIALS, len(L_SETTINGS))); dR = np.zeros((N_TRIALS, len(R_SETTINGS)))
    tot = np.zeros((N_TRIALS, 2)); pooled = np.zeros(2*n)
    l1max = 0.0; tl = 0.0; perm = 0.0; bad = 0; nstat = 0; cross = 0
    q3s = q4s = 0.0; q3n = q4n = 0; covers = []
    t0 = time.time()
    for tr in range(N_TRIALS):
        r = run_tour_pair(G['pts'], G['nbr'], G['z'], beta, seed0(beta) + tr,
                          HOPS_TRIAL, G['D'], ports=G['ports'], port_locked=locked)
        dw = r['dwell']; pooled += dw
        wL, wR = dw[:n], dw[n:]
        tot[tr] = (wL.sum(), wR.sum())
        for i, a in enumerate(L_SETTINGS): dL[tr, i] = float(wL @ svL[a])
        for i, b in enumerate(R_SETTINGS): dR[tr, i] = float(wR @ svR[b])
        l1max = max(l1max, r['l1']); tl = max(tl, r['tl_dwell']); perm += r['perm_dwell']
        bad += r['bad']; nstat += r['n_static']; cross += r['crossings']
        a3, n3, a4, n4 = r['q']; q3s += a3; q3n += n3; q4s += a4; q4n += n4
        covers.append(r['cover'])
    m3, m4 = q3s/max(q3n, 1), q4s/max(q4n, 1)
    drift = abs(m4 - m3) / max(0.5*(m3 + m4), 1e-12)
    det = (tot[:, 0] > 0) & (tot[:, 1] > 0)               # settings-independent detection
    print(f"  arm {label}: {N_TRIALS} trials x {HOPS_TRIAL} hops   "
          f"detection {det.mean()*100:.1f}%   mean crossings/trial {cross/N_TRIALS:.1f}   "
          f"coverage/trial {np.mean(covers)*100:.0f}%   drift {drift:.4f} (descriptive)")
    print(f"      guards: bad-gaps {bad}   locked-dwell(transient) {tl:.2e} (theorem: 0)   "
          f"frozen-pair dwell {perm:.2e}   static-windows {nstat}   "
          f"L1 max within-trial bridge drift {l1max:.2e}   [{time.time()-t0:.0f}s]")
    return dict(dL=dL, dR=dR, det=det, pooled=pooled, l1=l1max, tl=tl, drift=drift,
                svL=svL, svR=svR)

def marginal_table(arm, beta, show_hunt=False):
    det = arm['det']; rows = []; worst = 0.0
    nd = int(det.sum()); sig = 0.5/math.sqrt(max(nd, 1))
    for i, a in enumerate(L_SETTINGS):
        d = arm['dL'][det, i]; m = d != 0
        p = float((d[m] > 0).mean()); dev = p - 0.5; worst = max(worst, abs(dev))
        mu = float(arm['pooled'][:len(arm['svL'][a])] @ arm['svL'][a])
        hunt = (f"   pooled-pattern sector diff sign {'+' if mu > 0 else '-'}"
                f" ({'MATCHES' if (mu > 0) == (dev > 0) else 'opposes'} dev)"
                if show_hunt else "")
        rows.append(f"      wing L a={a:5.1f}: P(+)-0.5 = {dev:+.4f} ({abs(dev)/sig:4.1f} "
                    f"sigma_samp)   ties {int((~m).sum())}{hunt}")
    n = len(arm['svL'][L_SETTINGS[0]])
    for i, b in enumerate(R_SETTINGS):
        d = arm['dR'][det, i]; m = d != 0
        p = float((d[m] > 0).mean()); dev = p - 0.5; worst = max(worst, abs(dev))
        mu = float(arm['pooled'][n:] @ arm['svR'][b])
        hunt = (f"   pooled-pattern sector diff sign {'+' if mu > 0 else '-'}"
                f" ({'MATCHES' if (mu > 0) == (dev > 0) else 'opposes'} dev)"
                if show_hunt else "")
        rows.append(f"      wing R b={b:5.1f}: P(+)-0.5 = {dev:+.4f} ({abs(dev)/sig:4.1f} "
                    f"sigma_samp)   ties {int((~m).sum())}{hunt}")
    return worst, sig, rows

def E_of(arm, iL, iR):
    det = arm['det']
    a = arm['dL'][det, iL]; b = arm['dR'][det, iR]
    m = (a != 0) & (b != 0)
    prod = np.sign(a[m]) * np.sign(b[m])
    return float(prod.mean()), float(prod.std()/math.sqrt(max(m.sum(), 1))), int(m.sum())

def chsh_of(arm):
    det = arm['det']
    sA = {a: np.sign(arm['dL'][det, L_SETTINGS.index(a)]) for a in (0.0, 45.0)}
    sB = {b: np.sign(arm['dR'][det, R_SETTINGS.index(b)]) for b in (22.5, 67.5)}
    m = np.ones(int(det.sum()), bool)
    for v in list(sA.values()) + list(sB.values()): m &= (v != 0)
    st = np.zeros(int(m.sum()))
    for (a, b), sn in zip(CHSH_PAIRS, CHSH_SIGNS): st += sn * sA[a][m] * sB[b][m]
    return float(st.mean()), float(st.std()/math.sqrt(max(len(st), 1))), st, m, det

def fit_cos(deltas_deg, Es):
    X = np.stack([np.cos(2*np.radians(deltas_deg)), np.sin(2*np.radians(deltas_deg))], axis=1)
    coef, *_ = np.linalg.lstsq(X, np.array(Es), rcond=None)
    P, Q = float(coef[0]), float(coef[1])
    k = math.hypot(P, Q); psi = math.degrees(math.atan2(Q, P))
    resid = np.array(Es) - X @ coef
    return k, psi, float(np.sqrt(np.mean(resid**2)))

# ==================================== mechanical smoke ====================================
def smoke():
    print("  SMOKE (mechanical only, ADJ-10 class): 2 trials x 2000 hops, locked + unlocked.")
    print("  Plumbing + guards only; no production statistics viewed.")
    G = build_pair()
    print(f"  pair: {len(G['pts'])} seats, ports {G['ports']}, bridge length {G['d_b']:.3f}")
    for lk in (True, False):
        r = run_tour_pair(G['pts'], G['nbr'], G['z'], 0.20, 999001, 2000, G['D'],
                          ports=G['ports'], port_locked=lk)
        print(f"    locked={lk}: L1 drift {r['l1']:.2e}  tl_dwell {r['tl_dwell']:.2e}  "
              f"bad {r['bad']}  static {r['n_static']}  crossings {r['crossings']}")
    sys.exit(0)

# ========================================= run =========================================
if __name__ == "__main__":
    if "--smoke" in sys.argv: smoke()
    print("="*92)
    print("  FLM14 - run 7: PART C-PRIME, the emergent-channel Bell test (ADJ-14, committed")
    print("  before code; build note in RUN_LOG.md logged before this file). Two wings, one")
    print("  permanent gear-locked bridge pair; k-hat = the bridge contact phase, conserved by")
    print("  the ADJ-11 rigidity theorem. Readout = SIGN of sector dwell-difference (counting;")
    print("  NO cosine in the readout path). Stage 1 license, then Stage 2 only if licensed.")
    print("="*92)

    # ---------------- MACHINERY ANCHORS (ADJ-14; halt on fail) ----------------
    print("\n  MACHINERY ANCHORS (the reused core must be run-4/6's tour, bit-identical):")
    pts1, nbr1, z1, sid1, deg1 = build_seats3d(1)
    seeds1 = [10001 + k for k in range(64)]
    t0 = time.time()
    E_imp = f4b.ensemble(pts1, nbr1, z1, 0.20, seeds1)
    f_imp, why_imp = fit_exponent(E_imp['occ'], E_imp['A'])
    ok_a = f_imp is not None and abs(f_imp[0] - RUN4_P20) <= TOL_A
    print(f"    (a) imported form4b @ beta=0.20 seed-1: p_occ(OLD) = "
          + (f"{f_imp[0]:+.3f} (|r|={abs(f_imp[1]):.2f}, n={f_imp[2]})" if f_imp else
             f"undefined ({why_imp})")
          + f"   vs record {RUN4_P20:+.3f} (<= 5e-4): {'OK' if ok_a else '** FAULT **'}"
          f"   [{time.time()-t0:.0f}s]")
    t0 = time.time()
    D1 = np.linalg.norm(pts1[:, None, :] - pts1[None, :, :], axis=2)
    dw = np.zeros(len(pts1)); Astk = []
    for ps in seeds1:
        r = run_tour_pair(pts1, nbr1, z1, 0.20, ps, ANCHOR_HOPS, D1, ports=None,
                          amp_track=True)
        dw += r['dwell']; Astk.append(r['A'])
    occ_b = dw / max(dw.sum(), 1e-300); A_b = np.mean(Astk, axis=0)
    f_b, why_b = fit_exponent(occ_b, A_b)
    docc = float(np.max(np.abs(occ_b - E_imp['occ'])))
    ok_b = (f_imp is not None and f_b is not None and abs(f_b[0] - f_imp[0]) <= TOL_B)
    print(f"    (b) THIS tool's core, single-wing mode:  p_occ(OLD) = "
          + (f"{f_b[0]:+.3f} (|r|={abs(f_b[1]):.2f}, n={f_b[2]})" if f_b else
             f"undefined ({why_b})")
          + f"   |dp vs (a)| = "
          + (f"{abs(f_b[0]-f_imp[0]):.2e}" if (f_b and f_imp) else "nan")
          + f" (<= 1e-6): {'OK' if ok_b else '** FAULT **'}   max|d_occ| = {docc:.2e}"
          f"   [{time.time()-t0:.0f}s]")
    if not (ok_a and ok_b):
        print("  HALT per ADJ-14: machinery anchor failed - instrument fault, nothing bankable.")
        sys.exit(1)
    print("    anchors PASS -> the pair build is licensed on this core.")

    # ---------------- pair build ----------------
    G = build_pair()
    om = OMEGA0 * G['z'] / G['z'].mean()
    bL, bR = G['ports']
    print(f"\n  PAIR: {len(G['pts'])} seats (2 x 42, mirrored seed-1 wings), bridge bond "
          f"({bL},{bR}) length {G['d_b']:.3f} (median wing bond)")
    print(f"        Omega_P = {0.5*(om[bL]-om[bR]):.6f} (frozen bridge, run-3 backbone at "
          f"n=2)   start seat 0 (wing-L inner shell, ADJ-8)")

    # ---------------- STAGE 1: the three locked production arms + LICENSE ----------------
    print("\n" + "="*92)
    print("  STAGE 1 - LICENSE (L1 conservation / L2 declared counting readout / L3 marginals)")
    print("  Locked arms run first; NO correlation quantity is computed before the license.")
    print("="*92)
    arms_L = {}
    for b in BETAS:
        arms_L[b] = run_arm(G, b, True, f"beta={b:.2f} LOCKED")

    print("\n  L1 - conservation (bridge contact phase, within-trial, every hop sampled):")
    l1_worst = max(arms_L[b]['l1'] for b in BETAS)
    l1_ok = l1_worst <= GATE_L1
    for b in BETAS:
        print(f"      beta={b:.2f}: max drift {arms_L[b]['l1']:.2e}")
    print(f"      worst {l1_worst:.2e}  (machine precision, <= 1e-12): "
          f"{'PASS' if l1_ok else 'FAIL'}")
    tl_worst = max(arms_L[b]['tl'] for b in BETAS)
    print(f"      locked-dwell (transient) worst arm: {tl_worst:.2e} (must be 0.00e+00): "
          f"{'OK' if tl_worst == 0.0 else '** FAULT **'}")
    if tl_worst != 0.0:
        print("  HALT per ADJ-14 machinery anchor: rigidity theorem violated."); sys.exit(1)

    print("\n  L2 - readout as declared (build note): outcome = sign(sector+ dwell - sector-")
    print("      dwell), director-quadrant partition rotated by the analyzer; occupancy =")
    print("      the Born-mapped dwell ledger (ADJ-5/8); no cosine/trig/T_W in the readout")
    print("      path; detection = both wings fired (settings-independent). IMPLEMENTED AS")
    print("      DECLARED - construction leg; functioning shown by the detection/tie counts")
    print("      above and in the L3 table. -> PASS (construction)")

    print("\n  L3 - marginals, every setting of both wings, every beta (gate <= 0.002):")
    l3_worst = 0.0
    for b in BETAS:
        worst, sig, rows = marginal_table(arms_L[b], b, show_hunt=True)
        nd = int(arms_L[b]['det'].sum())
        print(f"    beta={b:.2f} (detected {nd}; sampling sigma per marginal ~ {sig:.4f}):")
        for r_ in rows: print(r_)
        print(f"      worst |dev| = {worst:.4f}")
        l3_worst = max(l3_worst, worst)
    l3_ok = l3_worst <= GATE_L3
    print(f"\n    L3 worst over all settings/betas = {l3_worst:.4f}  (gate <= 0.002): "
          f"{'PASS' if l3_ok else 'FAIL'}")
    if not l3_ok:
        print("    FARMER ref-5 hunt (fault first): anchors OK, L1 exact, guards zero ->")
        print("    no implementation fault found; deviation mechanisms per the table above")
        print("    (dev/sigma_samp column; pooled-pattern sign-match column).")
        if l3_worst <= 0.05:
            print("    worst dev <= 0.05 -> declared 4x-trials scaling diagnostic @ beta=0.20:")
            # one declared diagnostic: 4x trials (seed superset seed0+0..4N-1), locked
            sv = N_TRIALS
            try:
                globals()['N_TRIALS'] = 4*sv
                armX = run_arm(G, 0.20, True, "beta=0.20 LOCKED 4x-diagnostic")
                wX, sX, _ = marginal_table(armX, 0.20)
                print(f"      4x trials: worst |dev| = {wX:.4f} (sigma_samp ~ {sX:.4f}) -> "
                      + ("scales down: SAMPLING-FLOOR mechanism supported"
                         if wX < l3_worst/1.5 else "does NOT scale: real readout bias"))
            finally:
                globals()['N_TRIALS'] = sv

    licensed = l1_ok and l3_ok
    print("\n  LICENSE: " + ("GRANTED (L1, L2, L3 all PASS)" if licensed else
          "REFUSED - LICENSE-FAIL at " +
          ", ".join([n_ for n_, ok in (("L1", l1_ok), ("L3", l3_ok)) if not ok])
          + " (committed: STOP, no Stage 2)"))

    if not licensed:
        print("\n" + "="*92)
        print("  STAGE 2 NOT RUN (ADJ-14 committed condition). Honest landing class per the")
        print("  pre-declared expectations: (a) LICENSE-FAIL - readout too crude. Verdict +")
        print("  section-D belong to FLM14_VERDICT.md run 7.")
        print("="*92)
        sys.exit(0)

    # ---------------- STAGE 2 (licensed only) ----------------
    print("\n" + "="*92)
    print("  STAGE 2 - C1 shape / C2 ceiling / C3 unlocked control; full beta scan reported")
    print("="*92)
    arms_U = {}
    for b in BETAS:
        arms_U[b] = run_arm(G, b, False, f"beta={b:.2f} UNLOCKED")
    scan = {}
    for b in BETAS:
        print(f"\n  ---- beta = {b:.2f} ----")
        print("  C1  E(Delta) grid, (a,b) = (Delta, 0):")
        Es = []; Eu = []
        for d_ in DELTA_GRID:
            iL = L_SETTINGS.index(float(d_)); iR = R_SETTINGS.index(0.0)
            e, se, nn = E_of(arms_L[b], iL, iR)
            eu, seu, _ = E_of(arms_U[b], iL, iR)
            Es.append(e); Eu.append(eu)
            print(f"      Delta={d_:3d} deg   E_locked = {e:+.4f} +- {se:.4f} (n={nn})   "
                  f"E_unlocked = {eu:+.4f} +- {seu:.4f}")
        k, psi, rms = fit_cos(DELTA_GRID, Es)
        ku, psiu, rmsu = fit_cos(DELTA_GRID, Eu)
        print(f"      fit locked:   E = k*cos(2D - psi): k = {k:.4f}, psi = {psi:+.1f} deg, "
              f"RMS = {rms:.4f} (gate <= 0.05: {'PASS' if rms <= GATE_C1_RMS else 'FAIL'})")
        print(f"      fit unlocked: k = {ku:.4f}, psi = {psiu:+.1f} deg, RMS = {rmsu:.4f}")
        S_l, sS_l, st_l, m_l, det_l = chsh_of(arms_L[b])
        S_u, sS_u, st_u, m_u, det_u = chsh_of(arms_U[b])
        print(f"  C2  CHSH (standard angles): S_locked = {S_l:+.4f} +- {sS_l:.4f}  "
              f"(gate <= 2.8334: {'PASS' if S_l <= GATE_C2 else 'FAIL - fault hunt'})")
        print(f"  C3  S_unlocked = {S_u:+.4f} +- {sS_u:.4f}  (gate <= 2.004: "
              f"{'PASS' if S_u <= GATE_C3_U else 'FAIL'})")
        # paired same-seed difference where both arms detected
        both = det_l & det_u
        # rebuild per-trial CHSH on the common detected set
        def st_on(arm, sel):
            sA = {a: np.sign(arm['dL'][sel, L_SETTINGS.index(a)]) for a in (0.0, 45.0)}
            sB = {bb: np.sign(arm['dR'][sel, R_SETTINGS.index(bb)]) for bb in (22.5, 67.5)}
            mm = np.ones(int(sel.sum()), bool)
            for v in list(sA.values()) + list(sB.values()): mm &= (v != 0)
            s_ = np.zeros(int(sel.sum()))
            for (a, bb), sn in zip(CHSH_PAIRS, CHSH_SIGNS): s_ += sn * sA[a] * sB[bb]
            return s_, mm
        sl, ml = st_on(arms_L[b], both); su, mu_ = st_on(arms_U[b], both)
        mm = ml & mu_
        dif = sl[mm] - su[mm]
        zsc = float(dif.mean() / max(dif.std()/math.sqrt(max(len(dif), 1)), 1e-12))
        print(f"      locked - unlocked (paired, same seeds, n={len(dif)}): "
              f"dS = {dif.mean():+.4f}, z = {zsc:+.1f} sigma  -> "
              + ("TRANSMISSION DEMONSTRATED (>= 5 sigma)" if zsc >= 5 else
                 "not demonstrated at 5 sigma" if dif.mean() > 0 else
                 "KILL CONDITION: locked <= unlocked (channel transmits nothing)"))
        scan[b] = (k, psi, rms, S_l, sS_l, S_u, sS_u, zsc)
    print("\n  BETA SCAN (full, nothing fitted to maximise S):")
    print("      beta    k_locked   psi(deg)   RMS      S_locked         S_unlocked       dS z")
    for b in BETAS:
        k, psi, rms, S_l, sS_l, S_u, sS_u, zsc = scan[b]
        print(f"      {b:.2f}   {k:8.4f}   {psi:+8.1f}   {rms:.4f}   "
              f"{S_l:+.4f}+-{sS_l:.4f}   {S_u:+.4f}+-{sS_u:.4f}   {zsc:+.1f}")
    print("\n" + "="*92)
    print("  F6: one rule throughout - tour dynamics anchored bit-identical to run-4/6; the")
    print("  pair extension is ADJ-11's own receiver-cluster wording; W, OMEGA0, T_W untouched;")
    print("  beta scanned as declared; analyzers touch the readout only; no cosine in it.")
    print("="*92)
