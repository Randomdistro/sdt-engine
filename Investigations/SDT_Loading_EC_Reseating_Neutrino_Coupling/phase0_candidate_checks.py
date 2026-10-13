"""Phase 0 candidate-relation checks (algebra against engine constants; no fitting).

Constants are the values in Engine/include/sdt/laws.hpp: a_0 (line 129), alpha (line 112),
R_inf (line 138). The spec's candidate relation is
    k_R = (c/v(r)) sqrt(R/r),   lambda = 4 pi k_R r_l r_u / (r_u - r_l)
on the seat ladder r_n = n^2 a_0 / Z, v_n = Z alpha c / n.
Run: python phase0_candidate_checks.py
"""
import math

a0 = 5.29177210903e-11
alpha = 7.2973525693e-3
Rinf = 1.0973731568160e7


def candidate(Z, nl, nu, R):
    rl, ru = nl**2 * a0 / Z, nu**2 * a0 / Z
    k_lo = (nl / (Z * alpha)) * math.sqrt(R / rl)
    k_up = (nu / (Z * alpha)) * math.sqrt(R / ru)
    return 4 * math.pi * k_lo * rl * ru / (ru - rl), k_lo, k_up


print("P0-3a  hydrogen: candidate vs Rydberg, R = a_0")
for nl, nu in [(1, 2), (1, 3), (2, 3), (2, 4), (3, 5)]:
    lam = candidate(1, nl, nu, a0)[0]
    ryd = 1.0 / (Rinf * (1 / nl**2 - 1 / nu**2))
    print(f"  n={nl}->{nu}: {lam*1e9:.6f} nm  Rydberg {ryd*1e9:.6f} nm  ratio {lam/ryd:.9f}")
print(f"  analytic: alpha/(4 pi a_0) = {alpha/(4*math.pi*a0):.6f}  R_inf = {Rinf:.6f}  ratio {alpha/(4*math.pi*a0)/Rinf:.12f}")
print(f"  Om = R/k_R^2 = {a0/(1/alpha)**2:.6e} m (alpha^2 a_0 = r_e = {alpha**2*a0:.6e} m)")

print("\nP0-3b  hydrogenlike ions: candidate vs Z^2 Rydberg, for R = a_0 and R = a_0/Z")
print(f"{'Z':>2} {'n':>4} {'R':>6} {'k_R':>9} {'candidate nm':>13} {'Z^2 Ryd nm':>11} {'ratio':>8}")
for Z in (1, 2, 3):
    for nl, nu in [(1, 2), (2, 3)]:
        ryd = 1.0 / (Z * Z * Rinf * (1 / nl**2 - 1 / nu**2))
        for lab, R in (("a0", a0), ("a0/Z", a0 / Z)):
            lam, k1, k2 = candidate(Z, nl, nu, R)
            assert abs(k1 - k2) < 1e-9 * k1, "k_R should be constant along the seat ladder"
            print(f"{Z:>2} {nl}->{nu} {lab:>6} {k1:9.4f} {lam*1e9:13.5f} {ryd*1e9:11.5f} {lam/ryd:8.5f}")
print("\nreading: with a universal R = a_0 the candidate is off by exactly sqrt(Z) for ions; it reproduces the")
print("Z^2 scaling only when R is each ion's own seat radius a_0/Z, i.e. when the seat is supplied.")
