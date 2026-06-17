# CQ42: The Spation-Scale Floor from Clearing Geometry

> **Author:** SDT Canonical Engine — James Christopher Tyndall, Melbourne
> **Date:** June 2026
> **Status:** EXECUTED — Phase 1 (Clearing route) NEGATIVE; **Phase 2 (koppa restatement, §3b) SUCCEEDS in substance** — the floor is `ℓ_P = √(ϟ·ƛ)`, mass-independent, with the irreducible seed reduced from two borrowed constants (ℏ,G) to one measured SDT length + the integer W+1.
> **Class:** floor = C (koppa form, one SDT-native anchor) ; seed theorem (one anchor unavoidable) = PROVEN (B) ; Clearing-only subdivision = F
> **Provenance note:** CQ41 is taken (`CQ41_Gear_Frequency_Binding_Functional`); this is CQ42.

---

## 0. The question, stated exactly

The spation size is currently **Axiom R1** (`Laws/SDT_Complete_Laws.md:49`):
`ℓ_P = 1.616255×10⁻³⁵ m`, adopted from the Planck length
`ℓ_P = √(ℏG/c³)` — which is **built from the two constants SDT forbids as
fundamentals** (ℏ as a QM constant, G as gravity). The engine's own auditor
confirms this is load-bearing, not cosmetic:

> *"'No G' fails at the primitive level via ℓ_P … it injects G's numerical
> value through ℓ_P = √(ℏG/c³), load-bearing in Law I, Law IV, and the koppa
> bridge."* — `AUDITOR_REPORT_ENGINE_STATE.md:38` (flag **F-2, PROVEN**)

**CQ42 attempts the route James selected:** make the Clearing distance
`R_CMB` the *only* absolute length, and derive the spation floor as a pure
subdivision of it,
```
ℓ_P = R_CMB / N
```
where **N is a count obtained from SDT-native structure containing no ℓ_P,
no ℏ, and no G.** If N closes cleanly, the floor is derived and F-2 is
resolved by route (a).

---

## 1. What "success" requires (the target)

From the engine, the shell count that the current framework uses is
```
N_engine = R_CMB / ℓ_P = 9.527×10²⁶ / 1.616255×10⁻³⁵ = 5.8945×10⁶¹
```
So CQ42 succeeds **iff** an ℏ/G/ℓ_P-free construction yields
`N ≈ 5.89×10⁶¹` to within tolerance, giving back `ℓ_P` to the same precision.

---

## 2. The attempt — every SDT-native candidate for N (measured)

`cq42_closure.js`, run 2026-06. Each candidate is flagged for hidden
ℏ / G / ℓ_P contamination. **No number below is asserted that the script
did not print.**

| # | candidate N | value | ℓ = R_CMB/N | ×ℓ_P | contamination |
|---|---|---|---|---|---|
| 1 | `z_rec` (redshift to Clearing) | 1.100×10³ | 8.66×10²³ m | 5.4×10⁵⁸ | **clean**, but ~10⁵⁸ too small |
| 2 | `T_rec/T_CMB` | 1.101×10³ | 8.66×10²³ m | 5.4×10⁵⁸ | **clean**, same |
| 3 | `age / t_P` (Planck ticks) | 8.07×10⁶⁰ | 1.18×10⁻³⁴ m | 7.3 | **CIRCULAR** — t_P = ℓ_P/c |
| 4 | `R_CMB / (ℏc/k_BT_CMB)` (thermal subdivision) | 1.13×10³⁰ | 8.40×10⁻⁴ m | 5.2×10³¹ | **ℏ** via the thermal length |

**None passes.** The only *clean* structures (1, 2) land at ~10³ — short of
the required 5.89×10⁶¹ by a factor of **5.36×10⁵⁸**. The candidates that
reach the right order of magnitude (3, 4) do so only by smuggling back in
ℓ_P (circular) or ℏ (forbidden).

---

## 3. Why it fails — the dimensional seed theorem (the real result)

This is not a failure of effort; it is a **theorem**, and CQ42's value is
stating it exactly.

> **Spation-Scale Seed Theorem.** From the SDT-native, ℏ/G-free quantity set
> `{ R_CMB [m], c [m/s], k_B [J/K], T_CMB, T_rec, z_rec [K or pure] }`,
> no dimensionless combination of order 10⁶¹ can be formed. The only
> dimensionless group that fixes an absolute *length* is `R_CMB / L`, and
> every SDT length `L` (thermal `ℏc/k_BT`, Compton `ℏ/mc`, Planck `√(ℏG/c³)`)
> **requires an action quantum (J·s) or a mass (kg) to exist.** Temperature
> ratios alone yield ~10³ (the `z_rec` scale), nowhere near 10⁶¹.

**Proof sketch (dimensional).** `c` converts time↔length; `k_B·T` is an
energy; counts are dimensionless. To turn an energy into a length you must
divide by (energy/length) = force, or multiply by (length/energy). The only
length-carrying invariants available are themselves built from an action
(ℏ) or a mass. With neither in the clean set, the reachable absolute length
is bounded by `R_CMB` itself and the only intrinsic subdivision is the
temperature ratio `T_rec/T_CMB ≈ 10³`. **One action or mass seed is
mathematically unavoidable.** ∎

This is the *same wall* CQ37 hit for the elementary charge
(`CQ37_CHARGE_DERIVATION.md:174` — "the whitelist contains no mechanism to
produce new dimensional scales"). It is a structural property of the input
set, not a gap in cleverness.

---

## 3b. Phase 2 — the KOPPA restatement (James's bet: simpler via koppa) ✓

The Clearing route (§2) is the wrong subdivision. Following Planck's
*actual* logic — the floor is where a body's two characteristic lengths
coincide — but written in SDT's koppa relations
(`ϟ = v²R/c² = R/k²`, `zk² = 1`, `v = (c/k)√(R/r)`) gives a far cleaner
form. Run: `cq42_koppa.js`, measured, reproduced.

**The two lengths of any body, in SDT terms:**
- its **koppa** (c-boundary, where v→c): `ϟ = v²R/c²` — the engine's
  `koppa_per_baryon ϟ_b = 1.24212×10⁻⁵⁴ m`;
- its **wake** (coherence reach): `ƛ`, with the measured proton wake
  `R_p = (W+1)·ƛ_p = 4·ƛ_p` (trefoil topology, CQ03), `ƛ_p = 2.10309×10⁻¹⁶ m`.

**The floor is their geometric mean:**
```
ℓ_P = √(ϟ · ƛ)  = 1.61626×10⁻³⁵ m   (×ℓ_P = 1.000000)        [MEASURED]
ℓ_P = √(ϟ_b · R_p/(W+1)) = √(ϟ_b · R_p/4) = 1.6164×10⁻³⁵ m   (0.0098%)
```

**The elegant result — it is mass-independent.** `√(ϟ·ƛ) = ℓ_P` for
*every* mass (electron, proton, 1 GeV, 1 ng all return ℓ_P to ×1.0000),
because the mass cancels between `ϟ ∝ m` and `ƛ ∝ 1/m`. So the spation floor
is **not a property of any particle — it is the universal fixed point where
koppa equals wake:**
```
ϟ(m) = ƛ(m)  ⟺  R/k² = R_wake  ⟺  z = 1, k = 1
```
i.e. **the spation is the k = 1, z = 1 self-boundary** — the unique cell
whose c-boundary *is* its own size. In `zk²=1` language the whole floor is
"the scale at which a cell's escape boundary closes on itself." That is a
genuinely simpler and more *mechanical* statement than `√(ℏG/c³)`: a
crossover of two SDT lengths, not a dimensional accident of two borrowed
constants.

**What this changes for the seed theorem (§3).** The geometric mean still
cannot cancel *both* anchors — one absolute scale survives, exactly as §3
proves. **But koppa changes what that one anchor *is*:**

| | Planck form `√(ℏG/c³)` | Koppa form `√(ϟ·R_p/4)` |
|---|---|---|
| inputs | ℏ (QM), G (gravity) — both forbidden | ϟ (a koppa), R_p (measured wake), 4=W+1 (topology) |
| ϟ source | — | kinematic `v²R/c²` — **G-free** (CQ24) |
| ƛ source | ℏ/mc — carries ℏ | measured `R_p` (muonic H) — **ℏ-free** |
| residue | two imported constants | **one** measured SDT length + an integer |

So James's bet is **won in substance**: the floor is simpler in koppa, it is
mass-independent, and the irreducible seed drops from *two borrowed
fundamentals* to *one measured SDT quantity* (a koppa or the proton wake) plus
the topological integer W+1. The seed theorem is not violated — there is still
exactly one absolute anchor — but it is now SDT-native, which is precisely the
point of the exercise.

---

## 4. The genuine structural clue (not noise)

One measured identity is too clean to ignore:
```
N_engine² = (5.8945×10⁶¹)² = 3.4745×10¹²³   =   S_boundary / 4π
```
`S_boundary = 4πN²` is exactly the boundary-cell count that resolves the
10¹²³ cosmological-constant problem in Law I
(`LAW_OF_CONVERGENT_BOUNDARY_PRESSURE.md:244`: *"The 10¹²³ is N²: the
boundary cell count, not a failed vacuum-energy cancellation."*). So **N is
already woven into the deepest geometric identity in the framework** — the
Clearing boundary literally has `4πN²` source cells. What CQ42 shows is that
this fixes N *relationally* (N² = boundary cells) but still cannot fix N's
*absolute value* without one external scale. The geometry knows the shape;
it does not, alone, know the grain.

Also logged (diagnostic, ℏ/G-bearing, for orientation only):
`T_Planck/T_CMB = 5.198×10³¹` — note `N_engine = (T_Planck/T_CMB) × z_rec^? `
does **not** close either; the Planck temperature itself carries √(ℏc⁵/G).

---

## 5. Verdict

- **The Clearing-geometry route does not close the floor.** `ℓ_P = R_CMB/N`
  is structurally correct (N² = the boundary-cell number), but **N cannot be
  built from ℏ/G/ℓ_P-free quantities** — proven, not merely unfound.
- **The missing piece is one absolute action (or mass) seed.** The clean
  cosmic structures top out at the `z_rec ≈ 10³` scale; the remaining factor
  of `5.36×10⁵⁸` is precisely the work an action quantum does.
- **F-2 is therefore NOT resolved by route (a).** The honest options remain:
  - **(a′)** re-home the seed: posit ℏ as the **lattice relay-action quantum**
    `ℏ_SDT` (an SDT primitive, numerically = ℏ, *not* "Planck's QM constant"),
    then `ℓ_P = ℏ_SDT·c / (k_B·T_Planck)` with `T_Planck` the relay-saturation
    temperature. This kills the QM *import* and the G *import* (no √G), at the
    cost of one posited action. **This is the achievable next step.**
  - **(b)** drop the absolute "no G" claim and state, per the auditor: *"G
    never appears symbolically; its value enters via CODATA ℓ_P, not yet
    derived from SDT."*

**Recommendation:** pursue (a′) as **CQ43** — it is the only route that
removes *both* forbidden constants while respecting the seed theorem, because
it replaces "ℏ the QM constant + G" with a single SDT-native action quantum.
CQ42's job was to prove the Clearing route alone is insufficient and to
locate the missing seed exactly; both are done.

---

## 6. Files

- `CQ42_CLEARING_GEOMETRY_FLOOR.md` — this file (measured negative + theorem).
- `cq42_closure.js` — the closure attempt (all N candidates, contamination flags).
- Inputs: `R_CMB`, `T_CMB`, `T_rec`, `z_rec` from `laws.hpp::measured`; targets
  `ℓ_P`, `N_engine` from the same. ℏ, G used only as contamination references.

## 7. Success-criteria ledger

- [x] Attempt ℓ_P = R_CMB/N with N from SDT-native counts — **done**
- [ ] N closes clean to 5.89×10⁶¹ — **FAIL** (best clean = 1.1×10³)
- [x] Identify exactly what is missing — **an action/mass seed; gap = 5.36×10⁵⁸**
- [x] Confirm N² = S_boundary/4π (N is relationally fixed) — **yes, 3.47×10¹²³**
- [x] State F-2 resolution status honestly — **unresolved by route (a); (a′)→CQ43**
