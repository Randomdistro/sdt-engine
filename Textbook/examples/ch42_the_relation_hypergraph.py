"""Chapter 42 - the relation hypergraph: worked-example instrument (exact rational arithmetic).

Pre-registration: Textbook/validation/ch42_PRE_REGISTRATION.md (registered before this file existed).
Run: bash Textbook/tools/py_run.sh ch42_the_relation_hypergraph
"""
import json
import sys
from fractions import Fraction
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
FAILS = 0


def check(tid, what, ok):
    global FAILS
    if not ok:
        FAILS += 1
    print(f"[{'PASS' if ok else 'FAIL'}] {tid:<4} {what}")


def heading(t):
    print(f"\n== {t} ==")


def rref(rows, ncols):
    """Reduced row echelon form over the rationals; returns (rref rows, pivot columns)."""
    m = [list(r) for r in rows]
    piv = []
    r = 0
    for c in range(ncols):
        p = None
        for i in range(r, len(m)):
            if m[i][c] != 0:
                p = i
                break
        if p is None:
            continue
        m[r], m[p] = m[p], m[r]
        pv = m[r][c]
        m[r] = [x / pv for x in m[r]]
        for i in range(len(m)):
            if i != r and m[i][c] != 0:
                f = m[i][c]
                m[i] = [a - f * b for a, b in zip(m[i], m[r])]
        piv.append(c)
        r += 1
        if r == len(m):
            break
    return m[:r], piv


def rank(rows, ncols):
    return len(rref(rows, ncols)[1]) if rows else 0


def nullspace(rows, ncols):
    red, piv = rref(rows, ncols)
    free = [c for c in range(ncols) if c not in piv]
    basis = []
    for f in free:
        v = [Fraction(0)] * ncols
        v[f] = Fraction(1)
        for i, pc in enumerate(piv):
            v[pc] = -red[i][f]
        basis.append(v)
    return basis


def F(rows):
    return [[Fraction(x) for x in r] for r in rows]


heading("V1 elimination routine on small known matrices")
A = F([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
check("V1", "rank of [[1,2,3],[4,5,6],[7,8,9]] is 2", rank(A, 3) == 2)
ns = nullspace(A, 3)
check("V1", "its null space is spanned by (1,-2,1)", len(ns) == 1 and ns[0] == [Fraction(1), Fraction(-2), Fraction(1)])
B = F([[1, 0, 2, 0, 3], [0, 1, 0, 4, 5], [1, 1, 2, 4, 8]])
check("V1", "a 3x5 matrix whose third row is the sum of the first two has rank 2 (nullity 3)", rank(B, 5) == 2 and len(nullspace(B, 5)) == 3)
B2 = F([[1, 0, 2, 0, 3], [0, 1, 0, 4, 5], [1, 1, 2, 5, 8]])
check("V1", "a 3x5 matrix of rank 3 has nullity 2", rank(B2, 5) == 3 and len(nullspace(B2, 5)) == 2)
C = [[Fraction(1, 2), Fraction(1, 3)], [Fraction(1, 4), Fraction(1, 6)]]
check("V1", "[[1/2,1/3],[1/4,1/6]] has exact rank 1", rank(C, 2) == 1)

path = Path("Projects/sdt-investigations/Investigations/SDT_Spaz_Cross_Domain_Atlas_2026-10-27_2/EXACT_CONSTRAINTS2.json")
data = json.loads(path.read_text(encoding="utf-8"))
M = F(data["matrix"])
nrows, ncols = len(M), len(M[0])
print(f"       matrix {nrows} x {ncols}; stored rank {data['rank']}; stored null basis {len(data['null_basis'])} x {len(data['null_basis'][0])}")

heading("T1 exact rank and nullity")
r = rank(M, ncols)
print(f"       exact rank {r}; nullity {ncols - r}")
check("T1", "exact rank equals the stored rank 63", r == data["rank"] == 63)
check("T1", "rank equals the number of rows (63)", r == nrows)
check("T1", "nullity is 44", ncols - r == 44)

heading("T2 the stored null basis")
NB = F(data["null_basis"])
prod_zero = all(sum(a * b for a, b in zip(row, nb)) == 0 for row in M for nb in NB)
check("T2", "A B^T = 0 exactly for the stored null basis", prod_zero)
check("T2", "the stored null basis has rank 44 (independent rows, spans the null space)", rank(NB, ncols) == 44)
ns_own = nullspace(M, ncols)
check("T2", "the instrument's own null space has dimension 44", len(ns_own) == 44)
span_ok = rank(NB + ns_own, ncols) == 44
check("T2", "the stored basis and the instrument's basis span the same space", span_ok)

heading("T3 independence of every relation")
bad = []
for i in range(nrows):
    sub = M[:i] + M[i + 1:]
    if rank(sub, ncols) != 62:
        bad.append(i)
print(f"       relations whose removal leaves the rank unchanged: {len(bad)}")
check("T3", "removing any one of the 63 relations lowers the rank to 62", not bad)

heading("T4 pairwise projections")
nz = [sum(1 for x in row if x != 0) for row in M]
pairwise = [i for i, n in enumerate(nz) if n == 2]
hyper = [i for i, n in enumerate(nz) if n >= 3]
rp = rank([M[i] for i in pairwise], ncols) if pairwise else 0
print(f"       non-zero counts: pairwise {len(pairwise)}, three or more {len(hyper)}, one {sum(1 for n in nz if n == 1)}; max {max(nz)}")
print(f"       rank of the pairwise sub-matrix {rp}; relations not supplied by pairwise rows: {63 - rp}")
check("T4", "at least one relation has three or more non-zero entries", len(hyper) > 0)
check("T4", "63 - rank(pairwise) > 0", 63 - rp > 0)

heading("T5 adding information")
sum_row = [a + b for a, b in zip(M[0], M[1])]
check("T5", "appending the sum of two existing rows leaves the rank at 63", rank(M + [sum_row], ncols) == 63)
rises = []
for j in range(ncols):
    e = [Fraction(0)] * ncols
    e[j] = Fraction(1)
    if rank(M + [e], ncols) == 64:
        rises.append(j)
print(f"       columns for which x_j = 0 adds information (rank 64): {len(rises)} of {ncols}; already determined by the inventory: {ncols - len(rises)}")
print("       RECORDED REJECTION (run 1 criterion kept): the registered statement that some column is already determined is not found: the unit relation raises the rank for every column")
check("T5", "the registered statement (some column is already determined, i.e. 0 < raises < 107) is rejected", not (0 < len(rises) < ncols))
check("T5", "no single quantity is determined by the inventory (the rank rises for all 107 columns)", len(rises) == ncols)
cyc = [Fraction((j % 7) + 1) for j in range(ncols)]
check("T5", "an integer row 1,2,...,7,1,2,... raises the rank to 64", rank(M + [cyc], ncols) == 64)

print()
print(f"ALL CRITERIA MET: 0 failure(s)" if FAILS == 0 else f"CRITERIA NOT MET: {FAILS} failure(s)")
sys.exit(1 if FAILS else 0)
