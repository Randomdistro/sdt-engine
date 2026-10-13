"""FLM02 R2 (2026-10-06): zero-force theorem on the FLM08 substrate (corner-sharing random network).
Pre-registered in R2_REOPEN_2026-10-05.md section 4 before this file existed.  Author: J. C. Harvey, Melbourne.
No measured input, no fitted parameter.  Network: ../FLM10_Per_Spation_Lattice_Solver/flm10_network.npz
"""
import sys
from pathlib import Path
import numpy as np

HERE = Path(__file__).resolve().parent
NPZ = HERE.parent / "FLM10_Per_Spation_Lattice_Solver" / "flm10_network.npz"
rng = np.random.default_rng(20261006)


def mic(dr, L):
    return dr - L * np.round(dr / L)


def residuals(pos, nbr, L):
    s = np.zeros_like(pos)
    for i, v in enumerate(nbr):
        for j in v:
            r = mic(pos[j] - pos[i], L)
            s[i] += r / np.linalg.norm(r)
    return s


def neighbours_by_distance(pos, L, dist, tol=1e-6):
    nbr = []
    for i in range(len(pos)):
        dr = mic(pos - pos[i], L)
        r = np.linalg.norm(dr, axis=1)
        nbr.append([int(j) for j in np.where(np.abs(r - dist) < tol)[0] if j != i])
    return nbr


def crystal(kind, n):
    cells = np.array([[i, j, k] for i in range(n) for j in range(n) for k in range(n)], dtype=float)
    if kind == "sc":
        basis = np.array([[0, 0, 0]]); dist = 1.0
    elif kind == "bcc":
        basis = np.array([[0, 0, 0], [.5, .5, .5]]); dist = np.sqrt(3) / 2
    elif kind == "fcc":
        basis = np.array([[0, 0, 0], [0, .5, .5], [.5, 0, .5], [.5, .5, 0]]); dist = np.sqrt(2) / 2
    else:
        basis = np.array([[0, 0, 0], [0, .5, .5], [.5, 0, .5], [.5, .5, 0], [.25, .25, .25], [.25, .75, .75], [.75, .25, .75], [.75, .75, .25]])
        dist = np.sqrt(3) / 4
    pos = (cells[:, None, :] + basis[None, :, :]).reshape(-1, 3)
    return pos, float(n), dist


def weighted_rho(pos, s, L, Rs, centres):
    out = []
    for R in Rs:
        rho = []; neff = []; pred = []
        srms = float(np.sqrt(np.mean(np.sum(s * s, axis=1))))
        for c in centres:
            dr = mic(pos - pos[c], L)
            w = np.exp(-np.sum(dr * dr, axis=1) / (2 * R * R))
            F = (w[:, None] * s).sum(axis=0)
            rho.append(np.linalg.norm(F) / w.sum()); neff.append(w.sum())
            pred.append(srms * np.sqrt(np.sum(w * w)) / w.sum())
        out.append((R, float(np.sqrt(np.mean(np.square(rho)))), float(np.mean(neff)), float(np.sqrt(np.mean(np.square(pred))))))
    return out


def tetra_dirs():
    return np.array([[1, 1, 1], [1, -1, -1], [-1, 1, -1], [-1, -1, 1]], dtype=float) / np.sqrt(3)


def jittered_residuals(count, psi):
    d = tetra_dirs()
    s = np.zeros((count, 3))
    for k in range(4):
        e1 = np.cross(d[k], [0.3, 0.5, 0.8]); e1 /= np.linalg.norm(e1); e2 = np.cross(d[k], e1)
        a = rng.normal(0, psi / np.sqrt(2), count); b = rng.normal(0, psi / np.sqrt(2), count)
        v = d[k][None, :] + a[:, None] * e1[None, :] + b[:, None] * e2[None, :]
        s += v / np.linalg.norm(v, axis=1)[:, None]
    return s


def main():
    print("FLM02 R2 - zero force on the substrate (pre-registered 2026-10-06)")
    print("=" * 66 + "\n")
    fails = 0
    # ---- V1 ----
    worst = 0.0
    for kind in ("sc", "bcc", "fcc", "diamond"):
        pos, L, dist = crystal(kind, 3 if kind != "diamond" else 3)
        nbr = neighbours_by_distance(pos, L, dist)
        s = residuals(pos, nbr, L)
        deg = {len(v) for v in nbr}
        m = np.abs(s).max()
        centres = list(range(0, len(pos), max(1, len(pos) // 20)))
        for R, rho, ne, _pr in weighted_rho(pos, s, L, [0.3 * dist * 3], centres):
            m = max(m, rho)
        worst = max(worst, m)
        print(f"  [V1] {kind:8s} nodes {len(pos):4d} coordination {sorted(deg)}  max |s| or weighted residual = {m:.2e}")
    v1 = worst < 1e-12
    print(f"[V1] centrosymmetric / diamond: worst {worst:.2e} -> {'PASS' if v1 else 'FAIL'}")
    if not v1: fails += 1
    # ---- V2 ----
    ok2 = True
    for deg_, tol in ((5.0, 0.02), (10.0, 0.05)):
        psi = np.radians(deg_)
        s = jittered_residuals(100000, psi)
        rms = np.sqrt(np.mean(np.sum(s * s, axis=1))); exp = 2 * psi
        rel = abs(rms - exp) / exp
        print(f"[V2] jitter {deg_:4.1f} deg rms: rms|s| = {rms:.5f}, expected 2 psi = {exp:.5f}, rel {rel:.3%} (tol {tol:.0%})")
        ok2 = ok2 and rel < tol
    print(f"[V2] -> {'PASS' if ok2 else 'FAIL'}")
    if not ok2: fails += 1
    # ---- V3 (amended A2): 8 realisations x 400 centres ----
    pos, L, dist = crystal("diamond", 8)
    Rs = [dist * k for k in (1, 2, 3, 4, 5)]
    allr = []
    for seed in range(8):
        rg = np.random.default_rng(1000 + seed)
        global rng
        rng = rg
        s = jittered_residuals(len(pos), np.radians(5.0))
        centres = rg.choice(len(pos), 400, replace=False)
        allr.append([r[1] / r[3] for r in weighted_rho(pos, s, L, Rs, centres)])
    allr = np.array(allr); mr = allr.mean(axis=0)
    v3 = bool(np.all(np.abs(mr - 1.0) < 0.05))
    print(f"[V3] synthetic uncorrelated residuals, 8 realisations x 400 centres: mean measured/predicted rho at R = {', '.join('%.2f' % r for r in Rs)}: {', '.join('%.3f' % q for q in mr)} (tol 5%); std {', '.join('%.3f' % q for q in allr.std(axis=0))} -> {'PASS' if v3 else 'FAIL'}")
    if not v3: fails += 1
    print(f"\nVALIDATIONS: {'met' if fails == 0 else 'NOT MET -> G0'}\n")
    if fails:
        return 1
    # ---- T1 / T2 ----
    d = np.load(NPZ)
    pos, bonds, L, dmean = d["pos"], d["bonds"], float(d["L"]), float(d["d"])
    nbr = [[] for _ in range(len(pos))]
    for a, b in bonds:
        nbr[a].append(int(b)); nbr[b].append(int(a))
    s = residuals(pos, nbr, L)
    mag = np.linalg.norm(s, axis=1)
    angs = []
    for i, v in enumerate(nbr):
        for a in range(len(v)):
            for b in range(a + 1, len(v)):
                r1 = mic(pos[v[a]] - pos[i], L); r2 = mic(pos[v[b]] - pos[i], L)
                angs.append(np.degrees(np.arccos(np.clip(r1 @ r2 / (np.linalg.norm(r1) * np.linalg.norm(r2)), -1, 1))))
    angs = np.array(angs)
    blen = np.array([np.linalg.norm(mic(pos[b] - pos[a], L)) for a, b in bonds])
    print(f"[T1] CRN: {len(pos)} nodes, {len(bonds)} bonds, L = {L:.3f}; mean bond length {blen.mean():.4f} (npz d = {dmean:.4f})")
    print(f"     node residual |s_i|: mean {mag.mean():.4f}, rms {np.sqrt(np.mean(mag**2)):.4f}, max {mag.max():.4f}; bond angle mean {angs.mean():.2f} deg, std {angs.std():.2f} deg")
    print(f"     exact node-level cancellation excluded (rms |s_i| > 1e-6): {'yes' if np.sqrt(np.mean(mag**2)) > 1e-6 else 'no'}")
    print(f"     mean of s_i over all nodes (net vector): {np.linalg.norm(s.mean(axis=0)):.2e} (bond antisymmetry does not force this to zero)")
    # T2
    Rs = [k * blen.mean() for k in (0.5, 1.0, 1.5, 2.0, 2.5)]
    res = weighted_rho(pos, s, L, Rs, list(range(len(pos))))
    print("\n[T2] weighted knot residual rho(R) = rms_c |sum w_i s_i| / sum w_i on the CRN (R in mean bond lengths)")
    print("     R/bond   N_eff     rho    predicted(uncorrelated)  ratio")
    for k, (R, rho, ne, pr) in zip((0.5, 1.0, 1.5, 2.0, 2.5), res):
        print(f"     {k:4.1f}  {ne:8.3f}  {rho:.5f}   {pr:.5f}              {rho / pr:.3f}")
    rat = [r[1] / r[3] for r in res][:3]   # gated radii R = 0.5, 1.0, 1.5 bond lengths (A2)
    print(f"     gated ratios (R = 0.5, 1.0, 1.5): {', '.join('%.3f' % q for q in rat)}: " + ("uncorrelated (0.7-1.4)" if all(0.7 <= q <= 1.4 for q in rat) else ("positively correlated (>1.4)" if max(rat) > 1.4 else "anti-correlated (<0.7)")))
    print("     R = 2.0, 2.5: indicative only (few independent samples in the 216-node box)")
    x = np.log([r[2] for r in res]); y = np.log([r[1] for r in res])
    slope, icpt = np.polyfit(x, y, 1)
    print(f"     fitted exponent d ln rho / d ln N_eff = {slope:+.3f}")
    Neff_p = (8.414e-16 / 1.616255e-35) ** 3
    rho_p = np.exp(icpt) * Neff_p ** slope
    print(f"     extrapolation (report only) to N_eff = (R_p/l_P)^3 = {Neff_p:.2e}: rho ~ {rho_p:.1e} if the exponent held and residuals stayed uncorrelated")
    return 0


if __name__ == "__main__":
    sys.exit(main())
