# CR14 — Ionisation Balance and the Clearing Rung

**Pre-registration. Written before the instrument exists (§3.1).**
Author: J.C. Harvey, Melbourne. Category 07 — Cosmology and Redshift.
Opened 2026-07-30.

## The question

`Engine/include/sdt/laws.hpp` carries two entries in the `measured` namespace:

```cpp
inline constexpr double T_rec = 3000.0;   // [K] Temperature at recombination
inline constexpr double z_rec = 1100.0;   // [-] Recombination redshift
```

Neither is a reading off an instrument. Both are *inferred* quantities — the standard route
gets them from the Saha ionisation balance run at ΛCDM baryon densities. `laws.hpp:240`
already concedes the dependence: "every clean ratio bottoms out at ~10³ (`z_rec`)."

So the temperature ladder `T_N = N·T₀` reproducing ~3000 K at N = 1100 is not yet a result:
N = 1100 went in, 2998 K came out, and the pressure law `P_N = N⁴·P₀` is not consulted
anywhere in that arithmetic. Deleting `P₀` leaves the temperature unchanged.

**Question under test:** run the ionisation balance with the *vessel's own* density behaviour
instead of ΛCDM's, and ask where neutrality onset actually falls. Does it land at N ≈ 1100?

## Why the density is the whole question

In ΛCDM the baryon density dilutes with expansion, `n_b(z) = n_b₀(1+z)³`, so at z = 1100 the
plasma is ~1.3×10⁹ times denser than today. SDT asserts a static vessel — "a cooling pressure
vessel with no end" — with no expansion to dilute anything. Under that reading the baryon
density at the Clearing epoch is the *present* density, and the two frameworks differ by ~9.1
orders of magnitude in the one input the balance actually needs.

Note in passing, to be resolved separately:
`Investigations/07_Cosmology_and_Redshift/CR05_Spation_Pressure_Tensor_Derivation/cr05_pressure_solver.cpp:93`
implements `n_b(z) = n_b(0)·(1+z)³` — expansion dilution — inside an SDT tool. That is
either an inconsistency in CR05 or an unstated commitment to comoving dilution. Flagged, not
adjudicated here.

## Instrument

Saha equilibrium for pure hydrogen, one equation:

```
x_e² / (1 − x_e) = S(T) / n_b ,      S(T) = (m_e k_B T / 2πℏ²)^{3/2} · exp(−B / k_B T)
```

`B` is taken as the engine's Rydberg energy (`measured::Ry_eV` = 13.6056931…, itself forced by
`{m_e, c, α, h}` via `R_inf_derived = m_e c α²/2h` at `laws.hpp:934`). Helium, and the
non-equilibrium Peebles correction, are out of scope — declared here, not discovered later.

**Branches, all run through the identical solver in one pass (§3.3):**

- **A — ΛCDM comparator.** `n_b = n_b₀(1+z)³`, `T = T₀(1+z)`. Coupled; solve jointly.
- **B — SDT static vessel.** `n_b = n_b₀` constant, `T = N·T₀`.
- **C — inverse.** What `n_b` places the chosen criterion exactly at `T = 1100·T₀ = 2998.05 K`?
- **D — density sweep.** `T_half(n_b)` for `n_b` over 10⁻⁶ … 10¹⁴ m⁻³, to measure directly how
  much the answer moves when the density moves.

Criterion: primary `x_e = 1/2`. Also reported at `x_e = 0.1` and `0.01`, because
"the recombination temperature" is criterion-dependent and the spread must be visible.

## Instrument validation, before the object (§3.2)

- **V1** Limits: `x_e → 1` as `T → 10⁵ K`; `x_e → 0` as `T → 10³ K`, on Branch A densities.
- **V2** Known answer: Branch A at `x_e = 1/2` must return **z = 1250–1450**. The textbook
  Saha half-ionisation redshift is ≈ 1370 (Dodelson, *Modern Cosmology* §3.3). Landing
  outside this window is an instrument fault, and **no branch result is reportable** if it does.
  Note this is deliberately *not* 1090: z ≈ 1090 is the last-scattering surface from the full
  non-equilibrium calculation, not the Saha half-point. Validating against 1090 would be
  validating against the wrong known answer.
- **V3** Two-route (§3.4): analytic `d ln T_half / d ln n_b = 1/(3/2 + B/k_B T)` versus a
  numerical central difference from the solver. Must agree to < 1%.

## Pre-registered rejection criteria

Every class below is populated by a physically possible outcome (§3.1).

- **R1 — reproduced.** Branch B returns `N_half` within ±10 % of 1100. The rung is then
  import-free: the vessel places its own Clearing without borrowing `z_rec`.
- **R2 — not reproduced.** Branch B falls outside ±10 %. Then `z_rec` stays MEASURED-INPUT,
  and the reproduction of 2998 K is CALIBRATED(1) — one imported number, documented.
- **R3 — non-discriminating.** If `d ln T_half / d ln n_b < 0.05`, then a ~9-order density
  disagreement moves the recombination temperature by less than a factor ~1.5, and recovering
  ~3000 K cannot discriminate the vessel from ΛCDM *even in the branch that succeeds*. Result
  is then [DEGENERATE] and **may not be cited as evidence for pressurised space**.
  **R3 outranks R1**: if both fire, the finding is the degeneracy, not the reproduction.
- **R4 — contraband, registered against myself.** The Saha relation is imported statistical
  mechanics: its phase-space factor counts states in ℏ³ cells, machinery SDT has not rebuilt.
  Its *inputs* are whitelist-legal (`m_e`, `k_B`, `ℏ`, `Ry_eV`); its *derivation* is not SDT's.
  Therefore **no outcome of this investigation may be labelled DERIVED**. The best available
  label for a Branch-B success is COMPUTED — a consistency check, not a derivation. Registered
  now so the label cannot be upgraded after the number is seen.

  This also disarms the demand that opened the investigation. Asking SDT to justify its
  Clearing rung *via Saha* asks it to be judged by a competitor's machinery, which §3.7
  forbids. What legitimately survives the demand is narrower: the vessel must supply the
  **density** from its own structure, and must produce a neutrality onset by whatever mechanism
  it owns. Running the identical instrument on both density laws is legal precisely because the
  instrument's provenance then cancels — only the density hypothesis is under test.

## Expected trap, named in advance

The log-structure of Saha makes `T_half` nearly linear in `ln n_b`. If Branch C's required
density lands near the geometric mean of Branch A's and Branch B's densities, that is a
**tautology of the log-linear structure, not a discovery**, and specifically must not be read
as support for any geometric-midpoint claim. Recorded here so the alignment cannot be
harvested after the fact.

## Deliverables

`cr14_saha_ladder.py`, `cr14_results.txt`, `CR14_ASSESSMENT.md`.
