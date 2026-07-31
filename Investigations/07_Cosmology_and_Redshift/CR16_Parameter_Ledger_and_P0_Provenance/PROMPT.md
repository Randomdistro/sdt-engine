# CR16 — Parameter Ledger and the Provenance of P₀

**Pre-registration. Written before the instrument exists (§3.1).**
Author: J.C. Harvey, Melbourne. Category 07. Opened 2026-07-31.
Object: *SDT — Cosmological Sector* (2026-07-30), Part II, P6, Props 1–14, Theorems 4–5.

## Why this investigation replaces the last one's framing

CR14/CR15 scored the sector on whether it reproduced `z ≈ 1100` and `T ≈ 3000 K`. Both are ΛCDM
outputs, not measurements — `z_*` is a fitted derived parameter of the base-6 fit, and 3000 K is
its companion. Testing a rival framework against a rival's *fitted outputs* is the contraband the
HUNTER role forbids (§G GATE-CONTRABAND: a kill enforcing a rival's axiom is itself killed).
**Neither number appears anywhere in this investigation.** They are struck as targets.

The second error was scoring "numerically identical to ΛCDM" as a cost. Recorded rule: numbers
**must** align when a framework is correct, so alignment is not the discriminator — **origin and
parameter count are**. If two frameworks reach the same observables and one uses fewer fitted
numbers, that is a result *for* the parsimonious one. This investigation measures that directly.

## Tests, with thresholds fixed now

- **T1 — provenance of P₀.** The document tags `P₀ = P_eff,⊙/z_⊙ = 1.3916×10⁻¹⁴ Pa` as **[C]**,
  an independent solar calibration. Test whether `P₀ = aT₀⁴/3`, the photon-gas pressure of the
  measured CMB. **Registered:** agreement to ≥ 4 significant figures ⟹ `P₀` is **not** an
  independent input but a function of `T₀`, and the Part II attribution is mis-stated.
  Consequence to be traced either way, in both directions.
- **T2 — is `P ∝ N⁴` an independent postulate?** P6 asserts `T_N = N·T₀` **and** `P_N = N⁴P₀` as
  two clauses, both **[A, C]**. **Registered:** if T1 confirms `P₀ = aT₀⁴/3`, then the second
  clause follows from the first by Stefan–Boltzmann and P6 **loses a clause** — the postulate
  count goes *down*, not up. Report the reduction explicitly.
- **T3 — dependency audit.** For every Proposition and Theorem in Parts IV–IX, determine which of
  the seven **[C]** inputs it actually consumes. **Registered:** any input consumed by no
  observational result is not a free parameter of the observational sector and must not be
  counted against it.
- **T4 — parameter ledger, like for like.** Enumerate free parameters on both sides for the
  observable list SDT currently addresses. Classification for each input: **measured-elsewhere**
  (fixed by non-cosmological data), **derived** (a function of other inputs), **fitted** (tuned to
  the data being explained). Only *fitted* counts. ΛCDM's base-6 is counted the same way.
- **T5 — the zero-parameter subset.** Enumerate every SDT result that consumes **no** fitted
  number at all, and check each against measurement where a measurement exists.

## Fairness constraint, binding (§no-manufactured-opposition)

ΛCDM's six parameters buy an observable list SDT's current sector does **not** cover: CMB peak
*heights* and the full power spectrum, the matter power spectrum, BBN abundances. The ledger must
state both halves — fewer parameters **and** a smaller observable list — or it is propaganda.
A parameter advantage on a subset is not a parameter advantage overall, and will not be reported
as one.

## Deliverables

`cr16_ledger.py`, `cr16_results.txt`, `CR16_ASSESSMENT.md`.
