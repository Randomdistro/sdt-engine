# ============================================================================
#  CH03 - Periodic Table & Valence from Shell Wake-Cancellation
#  Author: J. C. Harvey, Melbourne - 2026-07-05
#  Machinery only: seat geometry + exact enumeration. No orbitals, no subshells.
#  Models M0/M1/M2 committed in RUN_LOG.md BEFORE this file was written.
#  Exit 0 only if ALL committed gates pass; honest nonzero otherwise.
# ============================================================================
import itertools, math, sys

fails = []

print("=" * 68)
print("  CH03 - Valence from Wake Cancellation (M0 seeded / M1 native / M2)")
print("  Author: J. C. Harvey, Melbourne - 2026-07-05")
print("=" * 68)

# ---------------------------------------------------------------------------
# M0 - seeded tally: active(n) = min(n, 2S - n), capacities {2,8,8} CALIBRATED(1)
# ---------------------------------------------------------------------------
caps = [2, 8, 8]
elements = ["H","He","Li","Be","B","C","N","O","F","Ne",
            "Na","Mg","Al","Si","P","S","Cl","Ar"]
standard_valence = [1,0,1,2,3,4,3,2,1,0,1,2,3,4,3,2,1,0]  # OBSERVED (primary valences)

print("\nM0  SEEDED TALLY  active(n)=min(n, 2S-n) on capacities {2,8,8}")
print("    Z  El  n_in_period  active  standard  ")
m0_ok = 0
z = 0
tally = []
for cap in caps:
    for n in range(1, cap + 1):
        if z >= len(elements): break
        a = min(n, cap - n)
        tally.append(a)
        ok = (a == standard_valence[z])
        m0_ok += ok
        print(f"    {z+1:2d}  {elements[z]:2s}  {n:2d}/{cap}         {a}       {standard_valence[z]}      {'[ok]' if ok else '[X]'}")
        z += 1
print(f"    M0: {m0_ok}/18 match. NOTE: capacities are CALIBRATED(1) input ->")
print("    matching is a RE-LABELLING unless M1 derives the filling (firewall).")
if m0_ok < 18: fails.append("M0")

# P2 octet: nobles = all-paired fixed point
nobles = [(2,"He"), (10,"Ne"), (18,"Ar")]
print("\nP2  OCTET/INERTNESS: noble = all-paired fixed point (active = 0)")
for zi, name in nobles:
    a = tally[zi-1]
    print(f"    {name}: active = {a}  {'[ok]' if a == 0 else '[X]'}")
    if a != 0: fails.append(f"P2-{name}")

# ---------------------------------------------------------------------------
# M1 - NATIVE filling attempt: 8 cube-corner seats, energy = sum 1/d,
# exact enumeration of C(8,n). Active axis = body diagonal with exactly one
# occupied end. Does the min-energy filling reproduce the M0 pattern?
# ---------------------------------------------------------------------------
corners = [(sx, sy, sz) for sx in (-1, 1) for sy in (-1, 1) for sz in (-1, 1)]
def dist(p, q): return math.sqrt(sum((a - b) ** 2 for a, b in zip(p, q)))
def energy(cfg): return sum(1.0 / dist(corners[i], corners[j])
                            for i, j in itertools.combinations(cfg, 2))
def active_axes(cfg):
    s = set(cfg)
    count = 0
    for i in range(8):
        j = 7 - i  # antipodal corner index (bit-complement)
        if i < j and ((i in s) != (j in s)):
            count += 1
    return count

print("\nM1  NATIVE FILLING (period 2: Li..Ne as n=1..8 on cube seats, kernel 1/d)")
print("    n  E_min      active(min-E cfg)  needed(M0)  ")
m1_match = 0
for n in range(1, 9):
    best = None
    for cfg in itertools.combinations(range(8), n):
        e = energy(cfg) if n > 1 else 0.0
        if best is None or e < best[0] - 1e-12:
            best = (e, cfg)
    a = active_axes(best[1])
    need = min(n, 8 - n)
    ok = (a == need)
    m1_match += ok
    print(f"    {n}  {best[0]:8.5f}   {a}                  {need}          {'[ok]' if ok else '[X]  <-- native filling disagrees'}")
print(f"    M1: {m1_match}/8 — committed prediction: <8 means the tally is SEEDED,")
print("    not derived from the 1/d seat machinery -> firewall fires, cap C.")
m1_failed = (m1_match < 8)
if m1_failed: fails.append("M1-native-filling")

# ---------------------------------------------------------------------------
# M2 - diatomic pairing map -> residual actives -> magnetic call
# Gate: measured molar susceptibilities: O2 PARAMAGNETIC (+3449e-6 cm3/mol),
# N2 diamagnetic (-12e-6 cm3/mol). Measured NUMBERS as anchors (section B).
# ---------------------------------------------------------------------------
print("\nM2  DIATOMIC PAIRING MAP (all mutually pairable wakes pair fore/aft)")
diatomics = [("N2", tally[6], tally[6], "diamagnetic"),
             ("O2", tally[7], tally[7], "PARAMAGNETIC"),
             ("NO", tally[6], tally[7], "PARAMAGNETIC")]  # P4 novel call
for name, aA, aB, measured in diatomics:
    residual = abs(aA - aB)
    call = "PARAMAGNETIC" if residual > 0 else "diamagnetic"
    ok = (call.lower() == measured.lower())
    if not ok: fails.append(f"M2-{name}")
    print(f"    {name}: actives {aA}+{aB} -> residual {residual} -> {call:12s}  measured {measured:12s} {'[ok]' if ok else '[X]  KILL TRIGGER'}")
print("    Gate anchors: chi_mol(O2) = +3449e-6 cm3/mol (paramagnetic, measured);")
print("    chi_mol(N2) = -12e-6 cm3/mol (diamagnetic, measured).")

# ---------------------------------------------------------------------------
print("\n" + "=" * 68)
print("  CH03 SUMMARY")
print(f"  M0 seeded tally     : {m0_ok}/18 (re-labelling unless M1 holds)")
print(f"  P2 octet fixed point: nobles zero-active (arithmetic of M0)")
print(f"  M1 native filling   : {m1_match}/8 {'FAIL - tally is seeded' if m1_failed else 'PASS'}")
m2f = [f for f in fails if f.startswith('M2')]
print(f"  M2 pairing->magnetism: {'FAIL on ' + ', '.join(m2f) if m2f else 'PASS'}")
print(f"  Committed-gate failures: {fails if fails else 'none'}")
print(f"  Exit: {1 if fails else 0}")
print("=" * 68)
sys.exit(1 if fails else 0)
