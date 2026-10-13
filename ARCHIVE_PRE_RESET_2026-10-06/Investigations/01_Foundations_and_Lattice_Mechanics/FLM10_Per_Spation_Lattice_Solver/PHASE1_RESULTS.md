# FLM10 Phase 1 — The Isotropy Residual: results

**J. C. Harvey, Melbourne — 2026-06-25.** Tool: `flm10_phase1_isotropy.py` (reproducible seeds).
Reads the Phase-0 network `flm10_network.npz`; full run logged to `phase1_run.log`.
Class **[GEOMETRY]** — no coefficient is fitted to any measured target; the Keating stretch:bend
ratio (Si-like) cancels in the dimensionless anisotropy index.

---

## The question Phase 1 actually answers

Phase 0 showed the *bond-orientational* order (Steinhardt Q₄,Q₆) collapses ~10× in the amorphous
CRN. That is necessary but not sufficient. The Lorentz-emergence claim (FLM09-A2 / CONDENSA) is about
the **mechanical** response: does the medium carry **one longitudinal + two transverse** sound speeds
with **no preferred direction**, and does the residual elastic **anisotropy decay** as the network
grows? Phase 1 computes that directly.

## Method

- **Keating energy** (bond-stretch α + bond-bend β) on the real CRN, periodic box, scaled coordinates.
- **Elastic stiffness tensor C** by *deform–relax–fit*: apply many small random affine strains to the
  box, **re-relax the internal node positions** at each (the non-affine response), least-squares fit
  `E(η)=E₀+V·b·η+½V·η·C·η` → the 6×6 Voigt `C`. (The affine tensor — coords frozen — is also fit, for
  contrast.)
- **Anisotropy index**: the **Universal Elastic Anisotropy** `A^U = 5G_V/G_R + K_V/K_R − 6 ≥ 0`
  (Ranganathan–Ostoja-Starzewski 2008); `A^U = 0` **iff** perfectly isotropic. Frame-invariant.
- **Acoustic speeds**: eigenvalues of the Christoffel tensor `Γ_il = C_ijkl n_j n_k` along 9 directions
  → 3 branches (1 longitudinal + 2 transverse); their spread over directions = anisotropy by eye.

## The correctness anchor (this is what makes the rest trustworthy)

The **diamond crystal** must come out **cubic**. It does, cleanly:

```
C_relaxed (Voigt), diamond N=216:
  C11,C22,C33 = 1.375, 1.348, 1.378   (equal → cubic)
  C12,C13,C23 = 0.214, 0.228, 0.217   (equal → cubic)
  C44,C55,C66 = 0.736, 0.740, 0.706   (equal → cubic)
  all C1{4,5,6}, C2{4,5,6}, … ≈ 0     (|·| ≤ 0.018)
  A^U = 0.0725   (a FIXED, N-independent cubic anisotropy)
```

A cubic-symmetric tensor with the off-diagonal shear blocks ≈ 0 is the signature that the strain
machinery is correct. **The diamond anchor passes** → the amorphous numbers can be read.

## Results — anisotropy vs system size

| system | A^U (relaxed) | Δc_L/c_L | Δc_T/c_T | acoustic branches |
|---|---|---|---|---|
| diamond **crystal** (N=216) | **0.072** (fixed, cubic) | 2.6% | 4.8% | 1 L + 2 T |
| amorphous **N=64** (×3 seeds) | **0.43 ± 0.20** | 6.7% | 6.5% | 1 L + 2 T |
| amorphous **N=216** (saved CRN) | **0.049** | 2.5% | 2.5% | 1 L + 2 T |

**What is earned (robust):**
1. **The machinery is validated** by the cubic diamond anchor.
2. **Three acoustic branches — exactly 1 longitudinal + 2 transverse — appear in every network**
   (c_L ≈ 1.65 > c_T ≈ 1.04 at N=216). This *is* the "gravity's c_L + light's two c_T" mode structure
   CONDENSA/FLM08 assert, now read off a computed elastic tensor rather than assumed.
3. **The amorphous anisotropy is a finite-size residual that falls steeply with N** — from `0.43`
   (N=64) to `0.049` (N=216) — and is already **below the crystal's fixed 0.072 by N=216**. A crystal's
   anisotropy is a bulk property (N-independent); the glass's is a fluctuation that decays. The medium
   is **isotropising**, with direction-to-direction sound-speed spread down to ~2.5% at N=216.

**What is NOT yet earned (honest):**
1. **The decay exponent is not pinned.** Two sizes only (64, 216), the N=64 point is noisy
   (`A^U` scatters 0.14–0.61 across seeds — std ≈ mean, because 64 nodes is tiny), and N=216 is a
   **single** glass (the sub-gold "strained glass" flagged in Phase 0). The 2-point slope (`p≈−1.8`) is
   **not trustworthy**; only the *sign* and the sub-crystal crossover are robust. No `N^{−1/2}` (or any
   specific) law is claimed.
2. **Absolute moduli are not physical here** — the strained sub-gold glass is under residual stress,
   which inflates apparent stiffness (the glass reads *stiffer* than diamond, an artifact); and the
   hinge stiffness κ is arbitrary. Only the dimensionless `A^U` and the speed *ratios* are read.
3. **Non-affine relaxation does not monotonically reduce anisotropy** — for the glass, relaxed `A^U`
   (0.049) slightly exceeds affine (0.041): the soft non-affine modes carry their own anisotropy. An
   honest detail, not a bug (the diamond goes the other way: 0.125 → 0.073).
4. **This is the k→0 (elastic) limit, not the full `ω(k)`.** The 1+2 branch structure and isotropy are
   shown at long wavelength; the finite-k linear `ω=ck` with no dispersive residual is the next step.

## Verdict

**Phase 1 — QUALIFIED (Class C) on the qualitative result; PENDING (Class D) on the quantitative law.**
The elastic-isotropy machinery is anchor-validated; the amorphous CRN carries the correct
**1 longitudinal + 2 transverse** acoustic structure and is **elastically more isotropic than the
crystal by N=216**, with the residual anisotropy **falling with N** — the Lorentz-linearity
precondition is **supported, not plugged**. But the **decay exponent and the approach to `A^U→0`** are
not established: that needs a **gold-standard glass at N ≥ 512** (σ_angle ≈ 10°, 6-ring-peaked) with an
**ensemble of seeds at each size**, and the finite-`k` `ω(k)` dispersion. Per T1 of the FLM10
falsification table, the network did **not** stay anisotropic — so FLM08/CONDENSA is **not** falsified;
it is provisionally supported, pending the quantitative run.

## Next step

1. Rebuild the glass at N = 512, 1000 (longer WWW anneal → gold-standard) — likely in the C++ engine
   `flm10_lattice_solver.cpp` for speed, as Phase 0 anticipated.
2. Ensemble (≥5 seeds per size) → pin the `A^U(N)` decay law and confirm `A^U→0`.
3. Assemble the dynamical (RUM Hessian) matrix → full `ω(k)` along many directions: confirm `ω=ck`
   linear with no dispersive residual (FLM10 Phase-1 success criterion in full).
4. Then Phase 2 (the `6π⁵` wake phase-space integral), run blind.
