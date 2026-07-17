# -*- coding: utf-8 -*-
# NP23 -- Monoisotopy from Mesh Windows
# J. C. Harvey, Melbourne -- 2026-07-06
# Phase A: grammar mapping of all stable windows Z=1..83 (leads only, NO gates).
# Phase B: committed rule V1 (RUN_LOG.md, written before this file) -- gate >=20/26 + Be-9 row.
# Anchors: NUBASE2020-class stable table (convention C1: no observed decay), typed by element.
# A, Z exact integers. NP08 ledger rows cited from repo record (IDENTITY).

import statistics
import sys

# ---------------------------------------------------------------------------
# ANCHOR TABLE (declared measured anchor -- PROMPT paragraph 6, convention C1)
# ---------------------------------------------------------------------------
STABLE = {
    1:  ("H",  [1, 2]),
    2:  ("He", [3, 4]),
    3:  ("Li", [6, 7]),
    4:  ("Be", [9]),
    5:  ("B",  [10, 11]),
    6:  ("C",  [12, 13]),
    7:  ("N",  [14, 15]),
    8:  ("O",  [16, 17, 18]),
    9:  ("F",  [19]),
    10: ("Ne", [20, 21, 22]),
    11: ("Na", [23]),
    12: ("Mg", [24, 25, 26]),
    13: ("Al", [27]),
    14: ("Si", [28, 29, 30]),
    15: ("P",  [31]),
    16: ("S",  [32, 33, 34, 36]),
    17: ("Cl", [35, 37]),
    18: ("Ar", [36, 38, 40]),
    19: ("K",  [39, 41]),
    20: ("Ca", [40, 42, 43, 44, 46]),
    21: ("Sc", [45]),
    22: ("Ti", [46, 47, 48, 49, 50]),
    23: ("V",  [51]),
    24: ("Cr", [50, 52, 53, 54]),
    25: ("Mn", [55]),
    26: ("Fe", [54, 56, 57, 58]),
    27: ("Co", [59]),
    28: ("Ni", [58, 60, 61, 62, 64]),
    29: ("Cu", [63, 65]),
    30: ("Zn", [64, 66, 67, 68, 70]),
    31: ("Ga", [69, 71]),
    32: ("Ge", [70, 72, 73, 74]),
    33: ("As", [75]),
    34: ("Se", [74, 76, 77, 78, 80]),
    35: ("Br", [79, 81]),
    36: ("Kr", [80, 82, 83, 84, 86]),
    37: ("Rb", [85]),
    38: ("Sr", [84, 86, 87, 88]),
    39: ("Y",  [89]),
    40: ("Zr", [90, 91, 92, 94]),
    41: ("Nb", [93]),
    42: ("Mo", [92, 94, 95, 96, 97, 98]),
    43: ("Tc", []),
    44: ("Ru", [96, 98, 99, 100, 101, 102, 104]),
    45: ("Rh", [103]),
    46: ("Pd", [102, 104, 105, 106, 108, 110]),
    47: ("Ag", [107, 109]),
    48: ("Cd", [106, 108, 110, 111, 112, 114]),
    49: ("In", [113]),
    50: ("Sn", [112, 114, 115, 116, 117, 118, 119, 120, 122, 124]),
    51: ("Sb", [121, 123]),
    52: ("Te", [120, 122, 123, 124, 125, 126]),
    53: ("I",  [127]),
    54: ("Xe", [126, 128, 129, 130, 131, 132, 134]),
    55: ("Cs", [133]),
    56: ("Ba", [132, 134, 135, 136, 137, 138]),
    57: ("La", [139]),
    58: ("Ce", [136, 138, 140, 142]),
    59: ("Pr", [141]),
    60: ("Nd", [142, 143, 145, 146, 148]),
    61: ("Pm", []),
    62: ("Sm", [144, 149, 150, 152, 154]),
    63: ("Eu", [153]),
    64: ("Gd", [154, 155, 156, 157, 158, 160]),
    65: ("Tb", [159]),
    66: ("Dy", [156, 158, 160, 161, 162, 163, 164]),
    67: ("Ho", [165]),
    68: ("Er", [162, 164, 166, 167, 168, 170]),
    69: ("Tm", [169]),
    70: ("Yb", [168, 170, 171, 172, 173, 174, 176]),
    71: ("Lu", [175]),
    72: ("Hf", [176, 177, 178, 179, 180]),
    73: ("Ta", [180, 181]),   # 180 = Ta-180m, observationally stable ISOMER (odd-odd) -- flagged
    74: ("W",  [182, 183, 184, 186]),
    75: ("Re", [185]),
    76: ("Os", [184, 187, 188, 189, 190, 192]),
    77: ("Ir", [191, 193]),
    78: ("Pt", [192, 194, 195, 196, 198]),
    79: ("Au", [197]),
    80: ("Hg", [196, 198, 199, 200, 201, 202, 204]),
    81: ("Tl", [203, 205]),
    82: ("Pb", [204, 206, 207, 208]),
    83: ("Bi", []),
}

# Naturally occurring nuclides EXCLUDED from windows under C1 (decay observed) -- leads only.
EXCLUDED_NATURAL = [
    (19, 40,  "beta-/EC measured, t1/2 1.2e9 yr (primordial)"),
    (20, 48,  "2b- measured (NEMO-3), 6.4e19 yr"),
    (23, 50,  "beta/EC measured, 2.7e17 yr (primordial)"),
    (32, 76,  "2b- measured (GERDA), 1.9e21 yr"),
    (34, 82,  "2b- measured (NEMO-3), 8.8e19 yr"),
    (36, 78,  "2EC measured (Baksan 2019), 9.2e21 yr"),
    (37, 87,  "beta- measured, 5.0e10 yr (primordial)"),
    (40, 96,  "2b- measured (NEMO-3), 2.4e19 yr"),
    (42, 100, "2b- measured (NEMO-3), 7.1e18 yr"),
    (48, 113, "beta- measured, 8.0e15 yr (primordial)"),
    (48, 116, "2b- measured (NEMO-3), 2.7e19 yr"),
    (49, 115, "beta- measured, 4.4e14 yr (primordial; the ABUNDANT In isotope)"),
    (52, 128, "2b- measured (geochemical), 2.2e24 yr"),
    (52, 130, "2b- measured, 7.9e20 yr"),
    (54, 124, "2EC measured (XENON1T 2019), 1.8e22 yr"),
    (54, 136, "2b- measured (EXO/KamLAND-Zen), 2.2e21 yr"),
    (56, 130, "2EC measured (geochemical), 2.2e21 yr"),
    (57, 138, "beta/EC measured, 1.0e11 yr (primordial)"),
    (60, 144, "alpha measured, 2.3e15 yr"),
    (60, 150, "2b- measured (NEMO-3), 9.3e18 yr"),
    (62, 147, "alpha measured, 1.1e11 yr (primordial)"),
    (62, 148, "alpha measured, 6.3e15 yr"),
    (63, 151, "alpha measured (2007), 4.6e18 yr"),
    (64, 152, "alpha measured, 1.1e14 yr"),
    (71, 176, "beta- measured, 3.8e10 yr (primordial)"),
    (72, 174, "alpha measured, 7.0e16 yr"),
    (74, 180, "alpha measured (2004), 1.8e18 yr"),
    (75, 187, "beta- measured, 4.2e10 yr (primordial)"),
    (76, 186, "alpha measured, 2.0e15 yr"),
    (78, 190, "alpha measured, 6.5e11 yr (primordial)"),
    (83, 209, "alpha measured (2003), 2.0e19 yr -- the near-stable Bi row"),
]

# The declared 26-element monoisotopic target set (C3): Z -> stable A (measured anchor).
TARGETS = {
    4: 9, 9: 19, 11: 23, 13: 27, 15: 31, 21: 45, 23: 51, 25: 55, 27: 59,
    33: 75, 37: 85, 39: 89, 41: 93, 45: 103, 49: 113, 53: 127, 55: 133,
    57: 139, 59: 141, 63: 153, 65: 159, 67: 165, 69: 169, 71: 175,
    75: 185, 79: 197,
}
MONONUCLIDIC_19 = {4, 9, 11, 13, 15, 21, 25, 27, 33, 39, 41, 45, 53, 55, 59, 65, 67, 69, 79}

# NP08 ledger (repo record, IDENTITY -- measured BEs consumed; 5 s.f.)
B_ALPHA = 28.296       # MeV
B_BE8 = 56.500         # MeV
DELTA_BE8_2A = B_BE8 - 2.0 * B_ALPHA   # -0.092 MeV: alpha+2d loses to 2alpha

LINE = "-" * 100


def grammar(Z, A):
    """Standard constitutional grammar. None = non-decomposable (flagged)."""
    if Z < 2:
        return None
    nt = A - 2 * Z
    nd = 3 * Z - A - 2
    if nt < 0 or nd < 0:
        return None
    return nd, nt


def main():
    print("NP23 -- MONOISOTOPY FROM MESH WINDOWS")
    print("J. C. Harvey, Melbourne -- 2026-07-06")
    print("Commitments: RUN_LOG.md (written before this tool). Convention C1; grammar C2;")
    print("targets C3; held-out calibration C4; parity C5. Gated rule: V1 (LOW tie-break, GX).")
    print(LINE)

    # -----------------------------------------------------------------------
    # PHASE A -- mapping (leads only, NO gates)
    # -----------------------------------------------------------------------
    print("PHASE A -- GRAMMAR MAP OF THE STABLE WINDOWS (leads only; nothing here is scored)")
    print(LINE)
    print(f"{'Z':>3} {'El':<3} {'width':>5}  {'stable A':<28} {'(n_d,n_t) per A':<34} {'n_t range':<9}")

    widths_odd, widths_even = [], []
    width1_set = []
    elem_median = {}
    parity_violations = []
    all_rows = []  # (Z, A, nd, nt)

    for Z in range(1, 84):
        sym, As = STABLE[Z]
        gs = []
        for A in As:
            g = grammar(Z, A)
            if g is not None:
                gs.append((A, g[0], g[1]))
                all_rows.append((Z, A, g[0], g[1]))
                if Z % 2 == 1 and Z > 7 and A % 2 == 0 and not (Z == 73 and A == 180):
                    parity_violations.append((Z, A))
        width = len(As)
        if width > 0:
            (widths_odd if Z % 2 == 1 else widths_even).append(width)
            if width == 1:
                width1_set.append(Z)
        if gs:
            elem_median[Z] = statistics.median(nt for _, _, nt in gs)
        nts = [nt for _, _, nt in gs]
        rng = f"{min(nts)}..{max(nts)}" if nts else "-"
        pair_str = " ".join(f"{A}:({nd},{nt})" for A, nd, nt in gs)
        note = ""
        if Z == 1:
            note = "  [pre-grammar: H-1=proton, H-2=free deuteron; excluded from stats]"
            pair_str = "n/a"
        if Z == 2:
            note = "  [He-3 non-decomposable (proto-alpha), flagged]"
        if Z == 73:
            note = "  [Ta-180m = observationally stable ISOMER, odd-odd; flagged]"
        if Z in (43, 61, 83):
            note = "  [no stable isotope]"
        print(f"{Z:>3} {sym:<3} {len(As):>5}  {str(As):<28} {pair_str:<34} {rng:<9}{note}")

    print(LINE)
    n_stable = sum(len(As) for _, As in STABLE.values())
    print(f"Total stable nuclides under C1: {n_stable} (H-1/H-2 pre-grammar; He-3 non-decomposable)")
    print(f"Naturally-occurring nuclides EXCLUDED under C1 (decay observed): {len(EXCLUDED_NATURAL)} -- leads, not windows:")
    for Z, A, why in EXCLUDED_NATURAL:
        print(f"    {STABLE[Z][0]}-{A}: {why}")
    print(LINE)

    # A2 -- window width statistics
    print("A2 -- WINDOW WIDTH BY Z PARITY (reported, not gated)")
    print(f"  odd-Z  elements with stable isotopes: {len(widths_odd):>2}  mean width {statistics.mean(widths_odd):.2f}  "
          f"widths: {sorted(set(widths_odd))} (distribution {[widths_odd.count(w) for w in sorted(set(widths_odd))]})")
    print(f"  even-Z elements with stable isotopes: {len(widths_even):>2}  mean width {statistics.mean(widths_even):.2f}  "
          f"widths: {sorted(set(widths_even))} (distribution {[widths_even.count(w) for w in sorted(set(widths_even))]})")
    print(f"  width-1 (monoisotopic) elements: {len(width1_set)} -> {[STABLE[Z][0] for Z in width1_set]}")
    print(f"  ONLY even-Z single: {[STABLE[Z][0] for Z in width1_set if Z % 2 == 0]}")

    # G0 data integrity (numerics-class gate, not physics)
    g0 = sorted(width1_set) == sorted(TARGETS.keys())
    print(f"  G0 data integrity (width-1 set == declared 26 targets): {'PASS' if g0 else 'FAIL'}")
    if not g0:
        print("  G0 FAIL -- typed table defect; grading forbidden per RUN_LOG.")
        sys.exit(1)

    # A3 -- parity / signature analysis
    print(LINE)
    print("A3 -- GRAMMAR SIGNATURES (reported, not gated)")
    print(f"  C5 check -- odd-Z (Z>7) even-A stable ground states: {parity_violations if parity_violations else 'NONE'}"
          f"  (Ta-180m isomer excepted)")
    print("  => every odd-Z stable nuclide above Z=7 has ODD n_t and EVEN n_d (n_t odd <=> A odd).")
    odd_singles = [Z for Z in TARGETS if Z % 2 == 1]
    sig = all(grammar(Z, TARGETS[Z])[1] % 2 == 1 and grammar(Z, TARGETS[Z])[0] % 2 == 0 for Z in odd_singles)
    print(f"  all 25 odd-Z singles have (n_d even, n_t odd): {sig}")
    bez = grammar(4, 9)
    print(f"  the ONE even-Z single, Be-9: (n_d,n_t) = {bez} -- the lone (odd,odd) single.")
    doubles = [(Z, STABLE[Z][1]) for Z in range(9, 84, 2) if len(STABLE[Z][1]) == 2 and Z != 73]
    print(f"  odd-Z doubles (Z>7): {[(STABLE[Z][0], As) for Z, As in doubles]}")
    print("  every double = two odd-n_t points separated by exactly 2 (one deuteron -> one triton swap")
    ok_gap2 = all(As[1] - As[0] == 2 for _, As in doubles)
    print(f"    at fixed alpha core moves A by +1; stable pairs sit at A, A+2): gap==2 for all: {ok_gap2}")
    print("  RIVAL DECLARATION (PROMPT paragraph 3): this odd/even skeleton IS Mattauch/pairing physics")
    print("  in grammar coordinates (n_t = N-Z). CONVERGENCE at most; nothing above is scored.")

    # A4 -- position structure: D/T crossover + n_d plateaus
    print(LINE)
    print("A4 -- POSITION STRUCTURE (reported, not gated)")
    first_tgtd = next((r for r in all_rows if r[3] > r[2]), None)
    last_dgtt = next((r for r in reversed(all_rows) if r[2] > r[3]), None)
    eq = [r for r in all_rows if r[2] == r[3]]
    print(f"  first stable nuclide with n_t > n_d: {STABLE[first_tgtd[0]][0]}-{first_tgtd[1]} (n_d={first_tgtd[2]}, n_t={first_tgtd[3]})")
    print(f"  last  stable nuclide with n_d > n_t: {STABLE[last_dgtt[0]][0]}-{last_dgtt[1]} (n_d={last_dgtt[2]}, n_t={last_dgtt[3]})")
    print(f"  n_d == n_t rows: {[(STABLE[Z][0], A) for Z, A, _, _ in eq]}")
    print("  LEAD: the D/T crossover is a BAND, not a line at Z=79 -- ATOMICUS rules paragraph 8")
    print("  ('Golden Boundary: gold is the last element where D > T') does not survive the")
    print("  constitutional formulas (Au-197 itself has n_d=38 < n_t=39). PROPOSE-AND-WAIT: no canon edit.")
    nds = [grammar(Z, TARGETS[Z])[0] for Z in sorted(TARGETS)]
    print(f"  n_d sequence of the 26 singles (Z ascending): {nds}")
    print("  LEAD: n_d plateaus (30 at Rh/I/Cs, 34 at Pr/Tb/Ho, 38 at Au/Bi-region) -- unexplained, reported.")

    # A5 -- the NP08 even-Z pinch convergence
    print(LINE)
    print("A5 -- THE NP08 PACKING-COMPETITION CONVERGENCE (the even-Z half of Harvey's question)")
    print(f"  At even Z the grammar configuration competes against whole-alpha reassembly.")
    print(f"  Z=4: B(Be-8 = alpha+2d) = {B_BE8:.3f} MeV vs 2*B(alpha) = {2*B_ALPHA:.3f} MeV")
    print(f"       -> alpha+2d LOSES by {DELTA_BE8_2A:+.3f} MeV (NP08, IDENTITY) => n_t=0 killed at Z=4.")
    print(f"  Z=6: alpha+4d BEATS 3*alpha by +7.275 MeV (NP08) => no pinch; C keeps a wide window.")
    print(f"  At odd Z the pure-alpha competitor is grammatically IMPOSSIBLE (odd Z is not a sum of alphas)")
    print(f"  => the packing competition can only pinch EVEN-Z windows, and the unique even-Z single (Be)")
    print(f"     is exactly the Z where the ledger flips sign. This is the convergence the question predicts.")

    # A6 -- valley residuals of the singles (positions relative to interpolated valley)
    print(LINE)
    print("A6 -- SINGLES vs INTERPOLATED VALLEY t_hat(Z) = mean of neighbour medians (reported)")
    print(f"{'El':<4} {'Z':>3} {'A':>4} {'n_t':>4} {'t_hat':>7} {'resid':>7}")
    residuals = {}
    for Z in sorted(TARGETS):
        tL, tU = elem_median[Z - 1], elem_median[Z + 1]
        that = (tL + tU) / 2.0
        nt = grammar(Z, TARGETS[Z])[1]
        residuals[Z] = nt - that
        print(f"{STABLE[Z][0]:<4} {Z:>3} {TARGETS[Z]:>4} {nt:>4} {that:>7.2f} {nt - that:>+7.2f}")
    print(f"  mean |resid| = {statistics.mean(abs(r) for r in residuals.values()):.3f}; "
          f"max resid = {max(residuals.values()):+.2f} ({STABLE[max(residuals, key=residuals.get)][0]})")

    # -----------------------------------------------------------------------
    # PHASE B -- the committed gate (rule V1, declared in RUN_LOG before this tool)
    # -----------------------------------------------------------------------
    print(LINE)
    print("PHASE B -- COMMITTED RULE V1 (RUN_LOG: held-out neighbour interpolation, C5 parity,")
    print("GX packing exclusion, LOW tie-break). GATE G1: >=20/26 AND Be row == 9.")
    print("Class cap declared in RUN_LOG: CONVERGENCE / CALIBRATED (data-interpolated), post-diction-exposed.")
    print(LINE)

    def candidates(Z):
        cs = [nt for nt in range(0, Z - 1) if (Z % 2 == 0 or nt % 2 == 1)]
        # GX: even-Z whole-alpha-reassembly exclusion; repo ledger exists only at Z=4 (NP08)
        if Z == 4 and DELTA_BE8_2A < 0:
            cs = [nt for nt in cs if nt != 0]
        return cs

    def pick(cs, that):
        best = min(cs, key=lambda nt: (abs(nt - that), nt))   # LOW tie-break (committed)
        tie = [nt for nt in cs if abs(nt - that) == abs(best - that)]
        return best, (len(tie) > 1)

    def score_v1(median_map, tie_low=True):
        rows, correct = [], 0
        for Z in sorted(TARGETS):
            that = (median_map[Z - 1] + median_map[Z + 1]) / 2.0
            cs = candidates(Z)
            if tie_low:
                best, tied = pick(cs, that)
            else:
                best = min(cs, key=lambda nt: (abs(nt - that), -nt))
                tied = len([nt for nt in cs if abs(nt - that) == abs(best - that)]) > 1
            A_pred = 2 * Z + best
            hit = (A_pred == TARGETS[Z])
            correct += hit
            rows.append((Z, that, best, A_pred, TARGETS[Z], hit, tied))
        return rows, correct

    rows, correct = score_v1(elem_median, tie_low=True)
    print(f"{'El':<4} {'Z':>3} {'t_hat':>7} {'n_t*':>5} {'A_pred':>7} {'A_meas':>7} {'tie?':>5} {'hit':>4}")
    for Z, that, nt, A_pred, A_meas, hit, tied in rows:
        gx = "  [GX: n_t=0 excluded, NP08 -0.092 MeV]" if Z == 4 else ""
        print(f"{STABLE[Z][0]:<4} {Z:>3} {that:>7.2f} {nt:>5} {A_pred:>7} {A_meas:>7} "
              f"{'TIE' if tied else '':>5} {'YES' if hit else 'MISS':>4}{gx}")
    be_hit = dict((r[0], r[3]) for r in rows)[4] == 9
    misses = [STABLE[r[0]][0] + "-" + str(r[4]) for r in rows if not r[5]]
    tie_rows = [r for r in rows if r[6]]
    tie_saves = sum(1 for r in tie_rows if r[5])
    print(LINE)
    print(f"V1 SCORE: {correct}/26 correct stable-A picks.  Be row -> A={dict((r[0], r[3]) for r in rows)[4]} "
          f"({'A=9 via GX complement, as required' if be_hit else 'MISS'})")
    print(f"Misses: {misses}")
    print(f"Tie rows resolved by committed LOW (deuteron-rich) tie-break: {len(tie_rows)} "
          f"({[STABLE[r[0]][0] for r in tie_rows]}), of which correct: {tie_saves}")
    g1 = (correct >= 20) and be_hit
    print(f"GATE G1 (>=20/26 AND Be==9): {'PASS' if g1 else 'FAIL'}"
          f"  -- class cap: CONVERGENCE / CALIBRATED (data-interpolated), post-diction-exposed (RUN_LOG)")

    # Unscored committed rows
    print(LINE)
    print("UNSCORED COMMITTED ROWS (leads)")
    m81, m82 = elem_median[81], elem_median[82]
    that_bi = 2 * m82 - m81
    cs_bi = [nt for nt in range(0, 82) if nt % 2 == 1]
    nt_bi = min(cs_bi, key=lambda nt: (abs(nt - that_bi), nt))
    print(f"  Bi (Z=83, near-stable, alpha 2.0e19 yr): extrapolated t_hat={that_bi:.2f} -> n_t*={nt_bi} "
          f"-> A={166 + nt_bi} (Bi-209 measured: {'HIT' if 166 + nt_bi == 209 else 'MISS'}; unscored)")
    for Z, name, best_known in ((43, "Tc", "Tc-97/98 longest-lived (4.2e6 yr)"),
                                (61, "Pm", "Pm-145 longest-lived (17.7 yr)")):
        that = (elem_median[Z - 1] + elem_median[Z + 1]) / 2.0
        cs = [nt for nt in range(0, Z - 1) if nt % 2 == 1]
        nt = min(cs, key=lambda n: (abs(n - that), n))
        print(f"  {name} (Z={Z}, NO stable isotope): t_hat={that:.2f} -> A={2 * Z + nt}  "
              f"[proxy anchor: {best_known}; lead only -- no stable A exists to score]")

    # Declared scans (cannot PASS) + sensitivity
    print(LINE)
    print("DECLARED SCANS AND SENSITIVITY (look-elsewhere ledger; none can PASS)")
    held_out = [(Z, A, nd, nt) for Z, A, nd, nt in all_rows if Z not in TARGETS and Z >= 2]

    c = statistics.median(nt / (A ** (5.0 / 3.0)) for _, A, _, nt in held_out if nt >= 1)
    v0_correct = 0
    for Z in sorted(TARGETS):
        cs = candidates(Z)
        nt = min(cs, key=lambda n: (abs(n - c * (2 * Z + n) ** (5.0 / 3.0)), n))
        v0_correct += (2 * Z + nt == TARGETS[Z])
    print(f"  V0 (rival-shaped valley power law, c = {c:.5f} held-out median): {v0_correct}/26  [scan]")

    kappa = statistics.median((Z - 2) ** 2 / nt for Z, _, _, nt in held_out if nt >= 1)
    v2_correct = 0
    for Z in sorted(TARGETS):
        cs = candidates(Z)
        target = (Z - 2) ** 2 / kappa
        nt = min(cs, key=lambda n: (abs(n - target), n))
        v2_correct += (2 * Z + nt == TARGETS[Z])
    print(f"  V2 (quadratic-in-blocks, kappa = {kappa:.2f} held-out median): {v2_correct}/26  [scan]")

    _, hi_correct = score_v1(elem_median, tie_low=False)
    print(f"  V1 with HIGH tie-break (sensitivity, unscored): {hi_correct}/26")

    # convention flip: restore 2b/2EC-measured nuclides to the windows (medians only)
    twob = {(Z, A) for Z, A, why in EXCLUDED_NATURAL if "2b-" in why or "2EC" in why}
    med2 = {}
    for Z in range(2, 84):
        As = list(STABLE[Z][1]) + [A for (z, A) in twob if z == Z]
        gs = [grammar(Z, A) for A in sorted(As)]
        gs = [g for g in gs if g is not None]
        if gs:
            med2[Z] = statistics.median(nt for _, nt in gs)
    _, flip_correct = score_v1(med2, tie_low=True)
    print(f"  V1 with 2b-measured nuclides restored (convention flip, unscored): {flip_correct}/26")

    print(LINE)
    print("END OF RUN. Nothing above was altered after first execution; commitments in RUN_LOG.md.")
    return 0  # committed hygiene: teed stdout, exit 0; the VERDICT carries the grade


if __name__ == "__main__":
    sys.exit(main())
