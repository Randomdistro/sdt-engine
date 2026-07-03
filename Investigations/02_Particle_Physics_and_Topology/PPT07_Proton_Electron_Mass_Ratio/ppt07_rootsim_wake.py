"""
PPT07 ROOT-SIM (honest blind test) — does trefoil(W=3)-vs-unknot(W=1) TOPOLOGY give 1836?
J. C. Harvey, Melbourne — 2026-06-24.   Domain: 02_Particle_Physics_and_Topology.

THE DISCIPLINE. 6π⁵ = 1836.118 matches m_p/m_e = 1836.153 to 0.002%, and the engine
(laws.hpp law_VI::mass_ratio) labels it "SDT-derived / passes delete-test". PPT07's own
write-up admits the bare flux-tube ratio is only 1.45 and that 6π⁵ was found by an
"exhaustive topological search against the target 1836.15" — i.e. the formula was selected
BECAUSE it matched. That is the numerology CONDENSA already [KILLED].

So this tool computes EVERY honest topological measure of the W=3 trefoil vs the W=1 unknot
BLIND — the target 1836 never enters any computation; it is shown only at the very end for
comparison. If any honest measure lands near 1836 without the answer in hand, 6π⁵ is earned.
If they all land O(1)-O(50), it is a fit, and we say so.

NO peeking: search this file — the literal 1836 / six_pi_5 appears only in the final report.
"""
import numpy as np

# ─── MEASURE 1 — winding-W vortex elastic energy (the "mass = phase stiffness" claim) ────
# A defect of winding W in a phase field θ has E = ½∫|∇θ|². Compute it on a grid, BLIND,
# for W = 1,2,3 and read off the scaling. (This is the cleanest "drop a W-defect, measure
# its wake-energy" experiment; the network just renormalises the prefactor, not the ratio.)
def vortex_energy(W, N=601, a=6.0):
    ax = np.arange(N) - N//2
    X, Y = np.meshgrid(ax, ax)
    th = W * np.arctan2(Y, X)                 # imposed winding field
    gx = np.gradient(np.unwrap(th, axis=1), axis=1)   # unwrap removes the 2π branch cut
    gy = np.gradient(np.unwrap(th, axis=0), axis=0)
    e  = 0.5 * (gx*gx + gy*gy)
    r  = np.hypot(X, Y)
    e[r < a] = 0.0                            # exclude the core (cutoff a)
    return e.sum()

E1, E2, E3 = vortex_energy(1), vortex_energy(2), vortex_energy(3)
print("MEASURE 1 — winding-W vortex energy (E ∝ W² expected):")
print(f"   E(W=1)={E1:.4e}   E(W=2)/E1={E2/E1:.4f} (W²=4)   E(W=3)/E1={E3/E1:.4f} (W²=9)")
m1 = E3/E1
print(f"   => trefoil(W=3)/unknot(W=1) energy ratio = {m1:.3f}   [pure winding]\n")

# ─── MEASURE 2 — knot length (ropelength): the trefoil is a LONGER tube than the circle ──
# Energy of a vortex loop ∝ W² · (loop length) · ln(L/a). The trefoil's ideal ropelength is
# a knot invariant (literature, no fit): trefoil 3_1 ≈ 16.372, unknot (round circle) = 2π.
ROPELEN = {"unknot(W=1)": 2*np.pi, "trefoil(W=3)": 16.372}
len_ratio = ROPELEN["trefoil(W=3)"] / ROPELEN["unknot(W=1)"]
print("MEASURE 2 — ideal ropelength (knot invariant, not fitted):")
print(f"   unknot = 2π = {2*np.pi:.3f}    trefoil 3_1 = {ROPELEN['trefoil(W=3)']:.3f}")
print(f"   => length ratio = {len_ratio:.3f}\n")

# ─── MEASURE 3 — assemble the BEST-CASE honest topological mass estimate ─────────────────
# mass ≈ W² · (length) · ln(L/a). Combine winding (×9) and length (×2.6); allow a GENEROUS
# log/core enhancement up to ~2× to be maximally fair to the topology side.
best = m1 * len_ratio
best_generous = best * 2.0
print("MEASURE 3 — best-case topological mass ratio (winding × length × log):")
print(f"   winding × length              = 9 × {len_ratio:.2f} = {best:.1f}")
print(f"   × generous log/core (≤2×)     = up to {best_generous:.1f}")
print(f"   bare flux-tube (PPT07, on record) = 1.45\n")

# ─── COMPARE — only now does the target appear ──────────────────────────────────────────
TARGET = 1.67262192369e-27 / 9.1093837015e-31     # m_p/m_e, the measured number
six_pi_5 = 6.0 * np.pi**5
print("="*70)
print("COMPARISON (target revealed only here):")
print(f"   measured  m_p/m_e            = {TARGET:.4f}")
print(f"   6π⁵                          = {six_pi_5:.4f}   ({100*(six_pi_5-TARGET)/TARGET:+.4f}%)  <- the engine's claim")
print(f"   honest topology best-case    = {best:.1f}   (generous {best_generous:.1f})")
print(f"   GAP: target / best-case      = {TARGET/best:.0f}×   <- topology misses by ~two orders\n")

print("VERDICT: every blind topological measure of trefoil-vs-unknot lands O(1)–O(50)")
print("(winding 9, length 2.6, product ~23, bare tube 1.45). NONE is near 1836. The 1836")
print("is NOT a topology invariant — it is a SCALE ratio (the Compton-length hierarchy")
print("λ_C,e/λ_C,p), which pure winding/length geometry cannot supply. 6π⁵ matches only")
print("because π-products with small integers densely cover the line; it was selected")
print("against the target. => 6π⁵ is a FIT, not a derivation. Held [KILLED-as-derivation].")
print()
print("WHY^n TO ROOT:")
print("  why no derivation?  -> honest topology gives O(10), not 1836.")
print("  why O(10)?          -> winding(W²) and length are dimensionless O(1) invariants.")
print("  why not 1836 there? -> 1836 is a ratio of two LENGTH SCALES (proton vs electron")
print("                          natural size), not a winding invariant.")
print("  why not derivable?  -> a scale ratio needs the scales; deriving it = the mass")
print("                          hierarchy = a dimensionful seed (the m_e/ℓ_P wall again).")
print("  why does 6π⁵ fit?   -> analytic π-counting is intrinsically fittable to any target.")
print("  ROOT: 6π⁵ is a target-selected coincidence; the mass ratio is an unearned SCALE,")
print("        same dimensional-necessity wall as m_e magnitude and ℓ_P (FLM06 seed theorem).")
