# CH02 RUN 2 Phase A — THE ISOELECTRONIC FORK. Spec: PROMPT.md §R2 Phase A (GATE-A verbatim);
# ADJ-R2-1 committed in RUN_LOG.md BEFORE this file existed. J. C. Harvey directive 2026-07-06.
# Claim under test: electron repulsion = nuclear repulsion TRANSMITTED (shell = gearbox) =>
# at FIXED shell, wall range shrinks and wall hardness rises MONOTONICALLY with Z.
# Rival-degeneracy declared in ADJ: PASS = convergence-class; only FAIL discriminates (kill-gate).
# No G, M, or GM anywhere. All inputs = measured literature values in measured units (declared).
import math, itertools, random

# ---------- S1: Shannon (1976) effective ionic radii, 6-coordinate, Angstrom ----------
S1 = {
 "He-shell": [("Li+",3,0.76),("Be2+",4,0.45),("B3+",5,0.27)],
 "Ne-shell": [("O2-",8,1.40),("F-",9,1.33),("Na+",11,1.02),("Mg2+",12,0.72),
              ("Al3+",13,0.535),("Si4+",14,0.40)],
 "Ar-shell": [("S2-",16,1.84),("Cl-",17,1.81),("K+",19,1.38),("Ca2+",20,1.00),
              ("Sc3+",21,0.745),("Ti4+",22,0.605)],
}
# ---------- S2: structure-matched ROCKSALT isoelectronic pairs: (name, cation Z, a0 [A], B0 [GPa], zz) ----
# B0 = measured bulk modulus (standard elastic data, 2-3 s.f.); zz = |z+ * z-|
S2 = [
 ("Ne/Ne", [("NaF",11,4.634,46.5,1),("MgO",12,4.212,160.0,4)]),
 ("Ar+/Ne-",[("KF",19,5.347,30.5,1),("CaO",20,4.811,113.0,4)]),
 ("Ar/Ar", [("KCl",19,6.293,17.4,1),("CaS",20,5.689,56.0,4)]),
]
CAVEAT = ("He+/Ne- (EXCLUDED from gate: BeO is wurtzite, structure mismatch)",
          [("LiF",3,4.027,66.5,1),("BeO",4,None,224.0,4)])

KE2   = 14.3996        # k_e * e^2 [eV*Angstrom] (identity constant for the diagnostic column only)
ALPHA_M = 1.747565     # Madelung, rocksalt

def born_n(a0,B0,zz):
    # z-deconvolved Born exponent from compressibility: n = 1 + 18*B0*r0^4/(alpha_M*k_e*e^2*zz)
    r0 = a0/2.0 * 1e-10                       # m
    B  = B0*1e9                               # Pa
    ke2_J = KE2 * 1.602176634e-19 * 1e-10     # J*m
    return 1.0 + 18.0*B*r0**4/(ALPHA_M*ke2_J*zz)

print("="*96)
print(" CH02 RUN 2 Phase A - ISOELECTRONIC FORK.  GATE-A (PROMPT.md R2 A.3, verbatim, committed):")
print(" hardness RISES and range SHRINKS monotonically with Z at fixed shell, >=2 shells,")
print(" >=2 independent parameter sources.  Null: Z-shuffle.  FAIL => transmission claim killed.")
print(" ADJ-R2-1: PASS = CONVERGENCE-class only (rival Z_eff degeneracy declared pre-run).")
print("="*96)

print("\n--- S1 (range): Shannon 6-coord radii [A] - radius must FALL strictly with Z ---")
s1_pass = True
for shell, rows in S1.items():
    zs  = [z for _,z,_ in rows]; rs = [r for _,_,r in rows]
    mono = all(rs[i] > rs[i+1] for i in range(len(rs)-1))
    s1_pass &= mono
    seq = "  ".join(f"{n}(Z={z}):{r:g}" for n,z,r in rows)
    m = len(rows); p_exact = 1.0/math.factorial(m)
    print(f"  {shell:9s} {seq}")
    print(f"           strictly decreasing: {'YES' if mono else 'NO'}   exact null P(monotone|shuffle) = 1/{m}! = {p_exact:.2e}")
print(f"  S1 verdict: {'MONOTONE in all 3 shells' if s1_pass else 'NOT monotone - GATE LEG FAILS'}")

print("\n--- S2 (hardness): measured B0 [GPa], structure-matched rocksalt pairs - B0 must RISE with Z ---")
s2_pass = True; ratios=[]
for label, pair in S2:
    (n1,z1,a1,b1,zz1),(n2,z2,a2,b2,zz2) = pair
    rise = b2 > b1; s2_pass &= rise; ratios.append(b2/b1)
    print(f"  {label:9s} {n1}(Z={z1}): a0={a1} A, B0={b1} GPa   ->   {n2}(Z={z2}): a0={a2} A, B0={b2} GPa"
          f"   ratio x{b2/b1:.2f}  rise: {'YES' if rise else 'NO'}")
print(f"  sign-test null: P(3/3 rises | random) = 1/8 = 0.125 ; combined with S1 nulls the joint null is negligible")
print(f"  S2 verdict: {'B0 RISES in all 3 pairs' if s2_pass else 'NOT monotone - GATE LEG FAILS'}")

print(f"\n  caveat row ({CAVEAT[0]}):")
(l1,zl1,al1,bl1,zzl1),(l2,zl2,al2,bl2,zzl2) = CAVEAT[1]
print(f"    {l1}(Z={zl1}): B0={bl1} GPa vs {l2}(Z={zl2}, wurtzite): B0={bl2} GPa - same direction, NOT scored")

print("\n--- S3 DIAGNOSTIC (REPORT-ONLY, ADJ-R2-1 disclosure: previewed at design; z^2-deconvolution")
print("    contaminates the shape with the attraction ledger; both scorings printed) ---")
s3_rows=[]
for label, pair in S2:
    ns = [(nm, z, born_n(a0,b0,zz)) for nm,z,a0,b0,zz in pair]
    s3_rows.append((label,ns))
    print(f"  {label:9s} " + "   ".join(f"{nm}: n={nv:.2f}" for nm,z,nv in ns) +
          f"   -> exponent {'RISES' if ns[1][2]>ns[0][2] else 'FALLS'} with Z")
s3_all_rise = all(ns[1][2] > ns[0][2] for _,ns in s3_rows)

print("\n--- GATE-A scoring (committed form: S1 range + S2 hardness = the two sources) ---")
gate = s1_pass and s2_pass
print(f"  S1 range shrinks monotonically, 3/3 shells: {'PASS' if s1_pass else 'FAIL'}")
print(f"  S2 hardness rises, 3/3 structure-matched pairs (2 distinct shell-pairs + Ar/Ar): {'PASS' if s2_pass else 'FAIL'}")
print(f"  GATE-A: {'PASS - conjunction holds on 2 sources, >=2 shells' if gate else 'FAIL - transmission claim chemistry expression KILLED'}")
print(f"  Alternate scoring WITH S3 included (per ADJ transparency clause): "
      f"{'PASS' if (gate and s3_all_rise) else 'FAIL on the S3 leg' if gate else 'FAIL'}")
print("\n  CLASS (fixed pre-run): " + ("CONVERGENCE - consistent with transmission; rival Z_eff degenerate; NOT native"
      if gate else "KILL - refinement-8 transmission claim loses its chemistry expression"))
print("  Tension row: the z-deconvolved exponent n FALLS with Z in every pair (7.0->4.5 class);")
print("  under transmission this reads as the wall's onset moving in (range leg) faster than its")
print("  power steepens - flagged OPEN for the Phase-B wall derivation to reproduce or kill.")
