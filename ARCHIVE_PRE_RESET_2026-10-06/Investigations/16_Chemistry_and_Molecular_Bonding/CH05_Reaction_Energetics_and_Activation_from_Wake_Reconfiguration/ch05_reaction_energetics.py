# ============================================================================
#  CH05 - Reaction Energetics & Activation from Wake Reconfiguration
#  Author: J. C. Harvey, Melbourne - 2026-07-05
#  P1: DH bookkeeping (bond-sum, OBSERVED anchors) - firewall: near-IDENTITY.
#  P2: committed M-SADDLE machinery for collinear H+H2 - does a barrier EMERGE?
#  Models and gates committed in RUN_LOG.md BEFORE this file. Exit honest.
# ============================================================================
import math, sys

fails = []
print("=" * 68)
print("  CH05 - Reaction Energetics & Activation (wake reconfiguration)")
print("  Author: J. C. Harvey, Melbourne - 2026-07-05")
print("=" * 68)

# ---------------------------------------------------------------------------
# P1 - DH bookkeeping. Mean bond enthalpies [kJ/mol], OBSERVED anchors.
# ---------------------------------------------------------------------------
BE = {"H-H":436, "Cl-Cl":242, "H-Cl":431, "F-F":158, "H-F":565, "Br-Br":193,
      "H-Br":366, "I-I":151, "H-I":298, "N#N":945, "N-H":391, "O=O":498,
      "O-H":463, "C-H":413, "C-C":347, "C=C":614, "C#C":839,
      "C=O(CO2)":799, "C#O":1072, "C-Cl":328, "N=O(NO)":631}

rxns = [
    ("H2 + Cl2 -> 2 HCl",        [("H-H",1),("Cl-Cl",1)], [("H-Cl",2)],            -184.6),
    ("H2 + F2 -> 2 HF",          [("H-H",1),("F-F",1)],   [("H-F",2)],             -546.0),
    ("H2 + Br2 -> 2 HBr",        [("H-H",1),("Br-Br",1)], [("H-Br",2)],            -103.7),
    ("H2 + I2 -> 2 HI",          [("H-H",1),("I-I",1)],   [("H-I",2)],               -9.5),
    ("N2 + 3 H2 -> 2 NH3",       [("N#N",1),("H-H",3)],   [("N-H",6)],              -92.2),
    ("2 H2 + O2 -> 2 H2O(g)",    [("H-H",2),("O=O",1)],   [("O-H",4)],             -483.6),
    ("CH4 + 2 O2 -> CO2 + 2 H2O",[("C-H",4),("O=O",2)],   [("C=O(CO2)",2),("O-H",4)], -802.3),
    ("C2H4 + H2 -> C2H6",        [("C=C",1),("H-H",1)],   [("C-C",1),("C-H",2)],   -136.9),
    ("C2H2 + H2 -> C2H4",        [("C#C",1),("H-H",1)],   [("C=C",1),("C-H",2)],   -174.5),
    ("CH4 + Cl2 -> CH3Cl + HCl", [("C-H",1),("Cl-Cl",1)], [("C-Cl",1),("H-Cl",1)],  -99.4),
    ("N2 + O2 -> 2 NO",          [("N#N",1),("O=O",1)],   [("N=O(NO)",2)],         +180.6),
    ("2 CO + O2 -> 2 CO2",       [("C#O",2),("O=O",1)],   [("C=O(CO2)",4)],        -566.0),
]

print("\nP1  DH BOOKKEEPING (bonds broken - bonds formed; near-IDENTITY per firewall)")
print("    reaction                        DH_pred   DH_meas   sign  |err|")
sign_ok = mag_ok = mag_tested = 0
for name, broken, formed, meas in rxns:
    dh = sum(BE[b] * n for b, n in broken) - sum(BE[b] * n for b, n in formed)
    s_ok = (dh * meas > 0)
    sign_ok += s_ok
    if abs(meas) >= 20.0:
        mag_tested += 1
        m_ok = abs(dh - meas) / abs(meas) <= 0.15
        mag_ok += m_ok
        tag = "ok" if m_ok else "X"
    else:
        tag = "exempt(|DH|<20)"
    print(f"    {name:31s} {dh:+7.0f}   {meas:+7.1f}   {'ok' if s_ok else 'X'}    {abs(dh-meas)/abs(meas)*100:5.1f}% {tag}")
print(f"    signs {sign_ok}/12 (gate 12) ; magnitudes within 15%: {mag_ok}/{mag_tested} (gate >=9)")
if sign_ok < 12: fails.append("P1-sign")
if mag_ok < 9: fails.append("P1-mag")
print("    LABEL: CONVERGENCE/IDENTITY - this IS bond-energy bookkeeping re-read as")
print("    shared-electron re-seating; it earns no NATIVE credit (firewall honoured).")

# ---------------------------------------------------------------------------
# P2 - M-SADDLE: collinear H + H2. Committed machinery, no cost knobs.
# V(r) = Morse, OBSERVED anchors (De 4.747 eV, Re 0.7414 A, a 1.9426 1/A).
# U(r1,r2) = -max_b [ b*(-V(r1)) + (1-b)*(-V(r2)) ] = min(V(r1),V(r2))  [b linear]
# variant M-SADDLE+: + V(r1+r2) end-end pair term.
# Reactant reference: U(inf, Re) = -De.
# ---------------------------------------------------------------------------
De, Re, a = 4.747, 0.7414, 1.9426  # eV, Angstrom, 1/Angstrom (OBSERVED)
def V(r):  # Morse well, V(Re) = -De, V(inf) = 0
    x = 1.0 - math.exp(-a * (r - Re))
    return De * (x * x) - De

eV2kJmol = 96.485

def path_max(plus):
    # exchange path: r1 from 3.5 A down, r2 relaxed; by symmetry sweep the seam.
    # grid the (r1, r2) plane, find the minimum-energy path via the committed
    # definition: for each s = r1 - r2 (reaction coordinate), minimise U over
    # (r1, r2) with that difference; the path max is the barrier.
    best_barrier = None
    smax = 4.0
    n = 801
    for i in range(n):
        s = -smax + 2 * smax * i / (n - 1)
        umin = None
        for j in range(1601):
            r2 = 0.45 + 7.55 * j / 1600.0   # r2 in [0.45, 8.0]
            r1 = r2 + s
            if r1 < 0.45 or r1 > 8.0: continue
            u = min(V(r1), V(r2))
            if plus: u += V(r1 + r2)
            if umin is None or u < umin: umin = u
        if umin is None: continue
        if best_barrier is None or umin > best_barrier[0]:
            best_barrier = (umin, s)
    return best_barrier

print("\nP2  BARRIER AS WAKE SADDLE (collinear H+H2, committed M-SADDLE machinery)")
u0 = -De  # reactant asymptote H + H2
for name, plus in (("M-SADDLE  (budget split only)", False),
                   ("M-SADDLE+ (with end-end pair term)", True)):
    peak, s_at = path_max(plus)
    Ea = (peak - u0) * eV2kJmol
    print(f"    {name}: path max = {peak:+.3f} eV at s={s_at:+.2f} A -> Ea = {Ea:+7.1f} kJ/mol")
print("    measured Ea(H+H2) ~ 40 kJ/mol (0.42 eV)  [OBSERVED anchor]")
mid_plain = min(V(Re), V(Re))
mid_plus = mid_plain + V(2 * Re)
print(f"    midpoint check U(Re,Re): budget-split {mid_plain:+.3f} eV (= -De, barrierless);")
print(f"    with end-end term {mid_plus:+.3f} eV vs reactants {-De:+.3f} eV -> symmetric H3")
print(f"    BOUND by {(-De - mid_plus) * -eV2kJmol:+.1f} kJ/mol (measured: H3 is NOT a bound molecule -> wrong sign)")
# committed gate: a saddle EMERGES with Ea in [10,120] kJ/mol
peak, _ = path_max(False)
Ea0 = (peak - u0) * eV2kJmol
peakp, _ = path_max(True)
Eap = (peakp - u0) * eV2kJmol
emerged = 10.0 <= Ea0 <= 120.0 or 10.0 <= Eap <= 120.0
if not emerged:
    fails.append("P2-no-saddle")
    print("    RESULT: no barrier emerges from the committed machinery.")
    print(f"      budget-split alone: Ea = {Ea0:+.1f} kJ/mol (the deeper well always holds the seat)")
    print(f"      with end-end term : Ea = {Eap:+.1f} kJ/mol (end-end Morse ATTRACTS at 2Re -> bound H3, wrong)")
    print("    -> P2 FAIL/OPEN. The missing piece is the cost of the mis-meshed middle")
    print("       configuration (mis-cancellation surplus / angular-window mismatch).")
    print("       No such term is derived; inventing one with a tuned size = FISHED RECOVERY. Refused.")
else:
    print("    RESULT: saddle emerged - see numbers above.")

print("\nP3  CATALYSIS: DEFER (depends on P2 saddle existing).")
print("P4  NOVEL BEP SLOPE: DEFER (same dependency).")

print("\n" + "=" * 68)
print("  CH05 SUMMARY")
print(f"  P1 bookkeeping: signs {sign_ok}/12, magnitudes {mag_ok}/{mag_tested} within 15% - CONVERGENCE/IDENTITY")
print(f"  P2 saddle: {'EMERGED' if emerged else 'DID NOT EMERGE - honest FAIL/OPEN'}")
print(f"  committed-gate failures: {fails if fails else 'none'}")
print(f"  Exit: {1 if fails else 0}")
print("=" * 68)
sys.exit(1 if fails else 0)
