#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
NP21 — The Binding Curve as a Resistance Landscape (iron at the floor)
======================================================================
Author: J. C. Harvey, Melbourne.
Execute per Investigations/PROMPT_EXECUTION_PROTOCOL.md and NP21/PROMPT.md.

This tool is a CHECKER, not a fitter of exponents. It:
  1. Pulls the alpha-grammar piece inventory (n_d, n_t) EXACTLY as sdt::nuclear::alpha_grammar:
         n_d = 3Z - A - 2 ,  n_t = A - 2Z ,  valid iff (n_d>=0 and n_t>=0).
     (Mirrored here in Python; formulas are the engine's, not re-derived.)
  2. Reads the measured BINDING ENERGY / A from AME2020 (OBSERVED-TARGET anchor only).
  3. Evaluates a resistance functional R~/A whose A-EXPONENTS are frozen-GEOMETRIC
     (see RUN_LOG.md exponent ledger). NO exponent is tuned to place the floor.
  4. Runs the floor search in TWO explicit modes:
         Run G : geometric-ratio coefficients (0 fitted ratios)  -> the Class-A bar
         Run F : ratios least-squares-fit to the AME curve       -> the honest CALIBRATED fork
  5. Reports shape (monotone + Spearman), the derived floor argmin, an exponent-perturbation
     robustness sweep, the A=48..70 profile, and the Fe-56 vs Ni-62 ordering.

NO G / M / GM, no wavefunctions, no SEMF fitted COEFFICIENTS as inputs. The measured B/A is
an anchor (its data), never the SEMF model. Charge is "handed redirection"; e is a unit-bridge.
"""

import os
import sys
import math

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", "..", ".."))
AME_PATH = os.path.join(
    REPO, "Investigations", "04_Atomic_Physics_and_Spectroscopy",
    "APS03_Universal_Drafting_Crossover", "mass_1.mas20.txt",
)
NUCLEAR_HPP = os.path.join(REPO, "Engine", "include", "sdt", "nuclear.hpp")


def load_natural_basis(path):
    """Parse the {Z, A} entries of sdt::nuclear::natural_basis[] straight from the engine
    header — the canonical stable/natural isotope set (287 rows, 284 alpha-valid). This
    keeps the *scan domain* sourced from the engine rather than re-listed locally.
    Returns a set of (Z,A)."""
    import re
    txt = open(path, "r", encoding="latin-1").read()
    m = re.search(r"natural_basis\[287\]\s*=\s*\{(.*?)\};", txt, re.S)
    if not m:
        return set()
    body = m.group(1)
    pairs = set()
    for mm in re.finditer(r"\{\s*(\d+)\s*,\s*(\d+)\s*\}", body):
        pairs.add((int(mm.group(1)), int(mm.group(2))))
    return pairs

# ----------------------------------------------------------------------------
# 1. alpha grammar  (mirror of sdt::nuclear::alpha_grammar — engine is the source)
# ----------------------------------------------------------------------------
def alpha_grammar(Z, A):
    nd = 3 * Z - A - 2
    nt = A - 2 * Z
    return nd, nt, (nd >= 0 and nt >= 0)


# ----------------------------------------------------------------------------
# 2. AME2020 loader  (OBSERVED-TARGET only)  -> {(Z,A): BA_MeV}
#    Fixed-width per header:  a1,i3,i5,i5,i5,1x,a3,a4,1x,f14.6,f12.6,f13.5,...
#    Columns (1-based char positions from the AME format string):
#      N  : 5..9    Z : 10..14   A : 15..19   EL : 21..23
#      BINDING ENERGY/A (keV) : the f13.5 field after MASS EXCESS + unc.
#    We parse structurally: split off the fixed head, then take the B/A token as the
#    3rd numeric field (mass_excess, unc, B/A). Robust to the '#'/'*' estimate marks.
# ----------------------------------------------------------------------------
def load_ame_ba(path):
    ba = {}
    with open(path, "r", encoding="latin-1") as fh:
        lines = fh.readlines()
    # find the data start: first line whose char[4:19] parse as N Z A ints
    for ln in lines:
        if len(ln) < 25:
            continue
        head = ln[0:1]  # page-feed control char, ignore
        try:
            N = int(ln[4:9])
            Z = int(ln[9:14])
            A = int(ln[14:19])
        except ValueError:
            continue
        # element symbol block ln[20:23]; then the numeric tail, which may carry an
        # optional origin flag (e.g. '-n', '-p', 'x') BEFORE the mass excess. So we
        # cannot rely on positional index 2. Instead anchor on the beta-decay flag
        # token 'B-'/'B+'/'B' : the AME layout is
        #    ... MASS_EXCESS unc  BINDING/A  unc  <Bflag>  beta unc  atomic_mass ...
        # hence  B/A = token two positions before the beta flag.
        tail = ln[23:]
        tail = tail.replace("#", " ").replace("*", " ")
        toks = tail.split()
        bidx = None
        for i, t in enumerate(toks):
            if t in ("B-", "B+", "B", "B-x"):
                bidx = i
                break
        if bidx is None or bidx < 3:
            continue
        try:
            ba_kev = float(toks[bidx - 2])
        except ValueError:
            continue
        # sanity: B/A must be positive and < ~9000 keV for bound nuclei
        if 0.0 < ba_kev < 12000.0:
            ba[(Z, A)] = ba_kev / 1000.0  # MeV per nucleon
    return ba


# ----------------------------------------------------------------------------
# 3. Resistance functional  R~/A  (frozen exponents; ratios are the only lever)
#      R~/A = -a_V + a_S*A^(-1/3) + a_C*Z(Z-1)*A^(-4/3) + a_A*(nt-nd)^2 / A^2
#    All A-exponents GEOMETRIC (RUN_LOG ledger). a_V is pure scale (does not move argmin
#    of R~/A since it is an A-independent additive constant -> it shifts every point equally,
#    so argmin is set entirely by a_S, a_C, a_A ratios). We therefore drop a_V for the
#    floor search (it cannot affect argmin) and reinstate it only for the MeV overlay.
# ----------------------------------------------------------------------------
def R_tilde_per_A(Z, A, aS, aC, aA):
    nd, nt, valid = alpha_grammar(Z, A)
    surf = aS * A ** (-1.0 / 3.0)
    spread = aC * (Z * (Z - 1)) * A ** (-4.0 / 3.0)
    asym = aA * ((nt - nd) ** 2) / (A ** 2)
    return surf + spread + asym  # a_V omitted (additive constant, argmin-invariant)


# minus-R~/A ranks like binding-per-nucleon (larger = more bound = deeper relaxation)
def neg_R_per_A(Z, A, aS, aC, aA):
    return -R_tilde_per_A(Z, A, aS, aC, aA)


# ----------------------------------------------------------------------------
# 4. geometric coefficient ratios  (Run G — the no-fit bar)
#    We must fix a_S : a_C : a_A from GEOMETRY, not from the AME curve.
#      surface weight a_S : energy per surface piece. Take the packing kissing number 12
#                     (cuboctahedron / FCC coordination) as the interior bond count a piece
#                     forgoes at the surface -> a_S ~ (bonds per interior piece)/2 * unit.
#      spread  weight a_C : handed-redirection unit = alpha * (hbar c) geared per pair over
#                     the shell radius. In derivation basis units this is a fixed small number vs a_S.
#      asym    weight a_A : grammar restoring, unit weight.
#    To avoid smuggling a fitted MeV coefficient, Run G works in RATIO space: we set
#      a_S := kiss/2 = 6      (12 nearest neighbours, each shared bond counts 1/2)
#      a_C := alpha           (= 1/137.036, the single dependency-traced redirection constant)
#      a_A := 1               (grammar unit)
#    These are declared GEOMETRIC/derivation basis in RUN_LOG. They are NOT tuned to the floor.
# ----------------------------------------------------------------------------
ALPHA = 1.0 / 137.035999084
KISS = 12  # cuboctahedron coordination (packing.hpp preset_cuboct12)
GEOM = dict(aS=KISS / 2.0, aC=ALPHA, aA=1.0)


# ----------------------------------------------------------------------------
# 5. Spearman rank correlation (scale-invariant shape test)
# ----------------------------------------------------------------------------
def spearman(x, y):
    n = len(x)
    if n < 3:
        return float("nan")

    def rank(v):
        order = sorted(range(n), key=lambda i: v[i])
        r = [0.0] * n
        i = 0
        while i < n:
            j = i
            while j + 1 < n and v[order[j + 1]] == v[order[i]]:
                j += 1
            avg = (i + j) / 2.0 + 1.0
            for k in range(i, j + 1):
                r[order[k]] = avg
            i = j + 1
        return r

    rx, ry = rank(x), rank(y)
    mx = sum(rx) / n
    my = sum(ry) / n
    num = sum((rx[i] - mx) * (ry[i] - my) for i in range(n))
    dx = math.sqrt(sum((rx[i] - mx) ** 2 for i in range(n)))
    dy = math.sqrt(sum((ry[i] - my) ** 2 for i in range(n)))
    if dx == 0 or dy == 0:
        return float("nan")
    return num / (dx * dy)


# ----------------------------------------------------------------------------
# 6. Run F — fit a_S,a_C,a_A to AME B/A by linear least squares (honest CALIBRATED fork)
#    Model: BA_meas ≈ a_V - a_S*A^-1/3 - a_C*Z(Z-1)*A^-4/3 - a_A*(nt-nd)^2/A^2
#    i.e. BA = c0 + c1*f1 + c2*f2 + c3*f3 with f_i the (negative) per-nucleon basis fns.
#    Solve normal equations (4x4). This IS a fit -> anything it enables is Class C.
# ----------------------------------------------------------------------------
def fit_coeffs(rows):
    # design: [1, -A^-1/3, -Z(Z-1)A^-4/3, -(nt-nd)^2/A^2]  target BA_meas
    X = []
    y = []
    for (Z, A, nd, nt, ba) in rows:
        f1 = -(A ** (-1.0 / 3.0))
        f2 = -(Z * (Z - 1)) * A ** (-4.0 / 3.0)
        f3 = -((nt - nd) ** 2) / (A ** 2)
        X.append([1.0, f1, f2, f3])
        y.append(ba)
    m = 4
    XtX = [[0.0] * m for _ in range(m)]
    Xty = [0.0] * m
    for i in range(len(X)):
        for a in range(m):
            Xty[a] += X[i][a] * y[i]
            for b in range(m):
                XtX[a][b] += X[i][a] * X[i][b]
    # Gaussian elimination
    Aug = [XtX[r][:] + [Xty[r]] for r in range(m)]
    for c in range(m):
        piv = max(range(c, m), key=lambda r: abs(Aug[r][c]))
        Aug[c], Aug[piv] = Aug[piv], Aug[c]
        pv = Aug[c][c]
        for k in range(c, m + 1):
            Aug[c][k] /= pv
        for r in range(m):
            if r != c:
                fac = Aug[r][c]
                for k in range(c, m + 1):
                    Aug[r][k] -= fac * Aug[c][k]
    coef = [Aug[r][m] for r in range(m)]
    # coef = [a_V, a_S, a_C, a_A]  (signs absorbed into design)
    return coef


# ----------------------------------------------------------------------------
#  DRIVER
# ----------------------------------------------------------------------------
def build_rows(ba, domain):
    """One row per alpha-valid nuclide in `domain` (the engine natural_basis stable set)
    that also has an AME B/A value. Restricting to the valley of stability is the correct
    landscape domain (the 'iron floor' is a valley statement, not an off-stability one)."""
    rows = []
    for (Z, A) in sorted(domain):
        if Z < 2 or Z > 92:
            continue
        nd, nt, valid = alpha_grammar(Z, A)
        if not valid:
            continue
        b = ba.get((Z, A))
        if b is None:
            continue
        rows.append((Z, A, nd, nt, b))
    return rows


def floor_of(rows, aS, aC, aA):
    """Return (Z,A) minimising R~/A  == maximising -R~/A."""
    best = None
    for (Z, A, nd, nt, ba) in rows:
        val = R_tilde_per_A(Z, A, aS, aC, aA)
        if best is None or val < best[0]:
            best = (val, Z, A)
    return best  # (Rmin, Z, A)


def main():
    if not os.path.exists(AME_PATH):
        print("ERROR: AME2020 file not found at", AME_PATH)
        sys.exit(1)

    ba = load_ame_ba(AME_PATH)
    domain = load_natural_basis(NUCLEAR_HPP)
    rows = build_rows(ba, domain)
    print("=" * 78)
    print("NP21 — Binding curve as a resistance landscape (iron at the floor)")
    print("=" * 78)
    print(f"AME2020 nuclides loaded              : {len(ba)}")
    print(f"engine natural_basis (Z,A) parsed    : {len(domain)}  [scan domain = valley of stability]")
    print(f"alpha-valid stable rows (Z in [2,92]): {len(rows)}")
    print(f"Fe-56 present : {(26,56) in ba}   B/A={ba.get((26,56)):.4f} MeV [OBSERVED-TARGET]")
    print(f"Ni-62 present : {(28,62) in ba}   B/A={ba.get((28,62)):.4f} MeV [OBSERVED-TARGET]")

    # ---- element-symbol helper
    SYM = {2:"He",3:"Li",4:"Be",5:"B",6:"C",7:"N",8:"O",9:"F",10:"Ne",11:"Na",
           12:"Mg",13:"Al",14:"Si",15:"P",16:"S",17:"Cl",18:"Ar",19:"K",20:"Ca",
           21:"Sc",22:"Ti",23:"V",24:"Cr",25:"Mn",26:"Fe",27:"Co",28:"Ni",29:"Cu",
           30:"Zn",31:"Ga",32:"Ge",33:"As",34:"Se",35:"Br",36:"Kr",37:"Rb",38:"Sr",
           39:"Y",40:"Zr",41:"Nb",42:"Mo",44:"Ru",45:"Rh",46:"Pd",47:"Ag",48:"Cd",
           49:"In",50:"Sn",51:"Sb",52:"Te",53:"I",54:"Xe",55:"Cs",56:"Ba",57:"La",
           58:"Ce",59:"Pr",60:"Nd",62:"Sm",63:"Eu",64:"Gd",65:"Tb",66:"Dy",67:"Ho",
           68:"Er",69:"Tm",70:"Yb",71:"Lu",72:"Hf",73:"Ta",74:"W",75:"Re",76:"Os",
           77:"Ir",78:"Pt",79:"Au",80:"Hg",81:"Tl",82:"Pb",83:"Bi",90:"Th",92:"U"}
    sym = lambda Z: SYM.get(Z, "?")

    # =====================================================================
    # RUN G  — geometric ratios (the Class-A bar; ZERO fitted ratios)
    # =====================================================================
    print("\n" + "-" * 78)
    print("RUN G — geometric-ratio coefficients  (0 fitted ratios) [DERIVED-attempt]")
    print(f"  a_S = kiss/2 = {GEOM['aS']}  (cuboctahedron coordination 12, packing.hpp)")
    print(f"  a_C = alpha  = {GEOM['aC']:.6e}  (derivation basis redirection constant)")
    print(f"  a_A = {GEOM['aA']}  (grammar unit)")
    print("-" * 78)
    Rmin_G, Zf_G, Af_G = floor_of(rows, **GEOM)
    negR = [neg_R_per_A(Z, A, **GEOM) for (Z, A, nd, nt, ba_) in rows]
    bam = [ba_ for (Z, A, nd, nt, ba_) in rows]
    rho_G = spearman(negR, bam)
    print(f"  Spearman(-R~/A, B/A_meas)  = {rho_G:+.4f}   [COMPUTED]")
    print(f"  DERIVED FLOOR (argmin R~/A) = {sym(Zf_G)}-{Af_G}  (Z={Zf_G}, A={Af_G})   [DERIVED]")
    print(f"  target Fe/Ni window A in [54,64]; |A_floor-56| = {abs(Af_G-56)}")

    # =====================================================================
    # RUN F  — fitted ratios (honest CALIBRATED fork; result caps at Class C)
    # =====================================================================
    coef = fit_coeffs(rows)
    aV_f, aS_f, aC_f, aA_f = coef
    print("\n" + "-" * 78)
    print("RUN F — ratios least-squares-FITTED to AME B/A  [CALIBRATED — caps at Class C]")
    print(f"  fitted a_V={aV_f:.4f}  a_S={aS_f:.4f}  a_C={aC_f:.4f}  a_A={aA_f:.4f}  (MeV)")
    print("-" * 78)
    Rmin_F, Zf_F, Af_F = floor_of(rows, aS_f, aC_f, aA_f)
    negR_F = [neg_R_per_A(Z, A, aS_f, aC_f, aA_f) for (Z, A, nd, nt, ba_) in rows]
    rho_F = spearman(negR_F, bam)
    # reconstructed B/A rms
    def ba_model(Z, A):
        return aV_f - R_tilde_per_A(Z, A, aS_f, aC_f, aA_f)
    rms = math.sqrt(sum((ba_model(Z, A) - ba_) ** 2 for (Z, A, nd, nt, ba_) in rows) / len(rows))
    print(f"  Spearman(-R~/A, B/A_meas)  = {rho_F:+.4f}   [COMPUTED]")
    print(f"  RMS(model B/A vs AME)      = {rms:.4f} MeV/n   [COMPUTED]")
    print(f"  FITTED-run floor (argmin)  = {sym(Zf_F)}-{Af_F}  (Z={Zf_F}, A={Af_F})   [CALIBRATED]")
    print(f"  |A_floor-56| = {abs(Af_F-56)}")

    # =====================================================================
    # FLOOR-vs-RATIO diagnostic — the crux. The argmin of R~/A is set ENTIRELY by the
    # a_C/a_S ratio (a_A only nudges via asymmetry; a_V is argmin-invariant). Sweep the
    # ratio r = a_C/a_S over decades and record where the floor lands. Then SOLVE for the
    # ratio that puts the floor at A≈56, and compare it to (i) the geometric guess a_C=alpha
    # and (ii) the SEMF ratio a_C/a_S ≈ 0.71/18.3 = 0.0388 (OBSERVED comparison only).
    # =====================================================================
    print("\n" + "-" * 78)
    print("FLOOR vs a_C/a_S RATIO  (the crux: floor location IS this ratio) [COMPUTED]")
    print("-" * 78)
    print(f"  {'a_C/a_S':>10}   floor(Z-A)   |A-56|")
    ratio_for_iron = None
    for r in [0.001, 0.003, 0.01, 0.02, 0.03, 0.0388, 0.05, 0.08, 0.15, 0.3, 0.6]:
        _, Zr, Ar = floor_of(rows, 1.0, r, GEOM['aA'])  # a_S=1, a_C=r
        flag = "  <-- Fe/Ni window" if 54 <= Ar <= 64 else ""
        print(f"  {r:>10.4f}   {sym(Zr)}-{Ar:<3d}      {abs(Ar-56):>3d}{flag}")
        if 54 <= Ar <= 64 and ratio_for_iron is None:
            ratio_for_iron = r
    geom_ratio = GEOM['aC'] / GEOM['aS']
    semf_ratio = 0.71 / 18.3
    print(f"\n  geometric guess a_C/a_S (alpha / (kiss/2)) = {geom_ratio:.5f}")
    print(f"  ratio needed to land floor in Fe/Ni window ~ {ratio_for_iron}")
    print(f"  SEMF a_C/a_S (OBSERVED comparison, NOT an input) = {semf_ratio:.5f}")
    print(f"  => floor-at-iron requires ratio ~{semf_ratio:.3f}; geometric guess gives {geom_ratio:.4f}"
          f"  (factor {semf_ratio/geom_ratio:.1f} off)")

    # =====================================================================
    # P3 robustness — perturb the GEOMETRIC ratios ±10..20% ; where does the floor go?
    # =====================================================================
    print("\n" + "-" * 78)
    print("P3 robustness — perturb Run-G geometric ratios; track the floor [COMPUTED]")
    print("-" * 78)
    print(f"  {'aS x':>6} {'aC x':>6} {'aA x':>6}   floor")
    stable = 0
    total = 0
    for ds in (0.8, 0.9, 1.0, 1.1, 1.2):
        for dc in (0.8, 1.0, 1.2):
            for da in (0.8, 1.0, 1.2):
                total += 1
                _, Zp, Ap = floor_of(rows, GEOM['aS']*ds, GEOM['aC']*dc, GEOM['aA']*da)
                on_iron = 54 <= Ap <= 64
                stable += on_iron
                if ds in (0.8, 1.0, 1.2) and dc in (0.8, 1.2) and da == 1.0:
                    print(f"  {ds:>6.2f} {dc:>6.2f} {da:>6.2f}   {sym(Zp)}-{Ap}"
                          f"  {'[in Fe/Ni window]' if on_iron else '[OFF]'}")
    print(f"  floor within A in [54,64] for {stable}/{total} perturbations "
          f"({100.0*stable/total:.0f}%)")

    # =====================================================================
    # Profile A=48..70 near the floor (Run G) — expose flat/sharp minimum
    # =====================================================================
    print("\n" + "-" * 78)
    print("R~/A profile near the floor  (Run G, geometric ratios)  A=48..70 [COMPUTED]")
    print("  (lowest-R~ nuclide printed per A; * marks global floor)")
    print("-" * 78)
    by_A = {}
    for (Z, A, nd, nt, ba_) in rows:
        v = R_tilde_per_A(Z, A, **GEOM)
        if A not in by_A or v < by_A[A][0]:
            by_A[A] = (v, Z, nd, nt, ba_)
    print(f"  {'A':>3} {'nuc':>7} {'R~/A':>10} {'-R~/A':>10} {'B/A_meas':>9}")
    for A in range(48, 71):
        if A in by_A:
            v, Z, nd, nt, ba_ = by_A[A]
            mark = " *" if (Z == Zf_G and A == Af_G) else ""
            print(f"  {A:>3} {sym(Z)+'-'+str(A):>7} {v:>10.5f} {-v:>10.5f} {ba_:>9.4f}{mark}")

    # =====================================================================
    # P4 — Fe-56 vs Ni-62 ordering under the landscape
    # =====================================================================
    print("\n" + "-" * 78)
    print("P4 — Fe-56 vs Ni-62 ordering [COMPUTED]")
    print("-" * 78)
    for (Z, A) in [(26, 56), (28, 62)]:
        nd, nt, _ = alpha_grammar(Z, A)
        sigma = abs(nd - nt) / (nd + nt) if (nd + nt) else 0.0
        v = R_tilde_per_A(Z, A, **GEOM)
        print(f"  {sym(Z)}-{A}: (n_d={nd}, n_t={nt})  sigma={sigma:.3f}  "
              f"R~/A={v:.5f}  B/A_meas={ba[(Z,A)]:.4f} MeV")
    v_fe = R_tilde_per_A(26, 56, **GEOM)
    v_ni = R_tilde_per_A(28, 62, **GEOM)
    deeper = "Fe-56" if v_fe < v_ni else "Ni-62"
    print(f"  Landscape places DEEPER (more bound): {deeper}")
    print(f"  Measured B/A deeper: Ni-62 (8.7946 > 8.7904)")
    print(f"  Grammar sigma smaller (more symmetric): Ni-62 (0.538 < 0.667)")

    # =====================================================================
    # CSV OUTPUT
    # =====================================================================
    csv_path = os.path.join(HERE, "NP21_results.csv")
    with open(csv_path, "w", encoding="utf-8") as out:
        out.write("Z,A,elem,n_d,n_t,sigma,f_geom,R_tilde_per_A_G,neg_R_per_A_G,BA_measured_MeV\n")
        for (Z, A, nd, nt, ba_) in rows:
            sigma = abs(nd - nt) / (nd + nt) if (nd + nt) else 0.0
            # f_geom: closure score = fraction of pieces (n_d+n_t+1 clusters) that seat in a
            # closed low-frustration shell, proxied by symmetry (1 - sigma). Geometric proxy.
            fgeom = 1.0 - sigma
            v = R_tilde_per_A(Z, A, **GEOM)
            out.write(f"{Z},{A},{sym(Z)},{nd},{nt},{sigma:.4f},{fgeom:.4f},"
                      f"{v:.6f},{-v:.6f},{ba_:.4f}\n")
        # trailer
        out.write("# TRAILER\n")
        out.write(f"# floor_Run_G,{sym(Zf_G)}-{Af_G},Z={Zf_G},A={Af_G}\n")
        out.write(f"# floor_Run_F,{sym(Zf_F)}-{Af_F},Z={Zf_F},A={Af_F}\n")
        out.write(f"# spearman_G,{rho_G:.4f}\n")
        out.write(f"# spearman_F,{rho_F:.4f}\n")
        out.write(f"# robustness_on_iron,{stable}/{total}\n")
        out.write("# exponent_tags: bulk=A^0 GEOMETRIC; surface=A^-1/3 GEOMETRIC; "
                  "spread=Z(Z-1)A^-4/3 GEOMETRIC; asym=(nt-nd)^2/A^2 GEOMETRIC(quadratic ASSUMED)\n")
        out.write("# Run_G ratios: a_S=kiss/2=6 GEOMETRIC; a_C=alpha derivation basis; a_A=1 GRAMMAR-UNIT (0 fitted)\n")
        out.write(f"# Run_F ratios: a_V={aV_f:.4f} a_S={aS_f:.4f} a_C={aC_f:.4f} a_A={aA_f:.4f} FITTED (CALIBRATED)\n")
    print("\nWrote CSV:", csv_path)
    print("\nDONE.")


if __name__ == "__main__":
    main()
