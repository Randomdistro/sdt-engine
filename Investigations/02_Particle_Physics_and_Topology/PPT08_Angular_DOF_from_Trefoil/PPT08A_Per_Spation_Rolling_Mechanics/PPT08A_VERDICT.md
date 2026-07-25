# PPT08A: Per-Spation Rolling and Gear-Mesh Geometry — VERDICT

> **⛔ FABRICATED VERDICT DELETED (repair 2026-07-23).** The original body of this file was an agent
> fabrication (signed *"Claude Code (SDT Investigation)"* / *"— Claude Code, PPT08A Investigation"*,
> not J. C. Harvey), first flagged by the HUNTER scour 2026-07-02 and left in place under a banner. It
> is now removed. The deleted content claimed a **CLASS A / machine-precision** derivation of the
> per-contact lag `λ_i = a/r_i` reproducing `v(r) = v₀√(R_p/r)` to `<10⁻¹⁵`. That claim was a
> **frozen-radius no-op**, not a derivation.

## Status: **OPEN** — superseded by the PPT08 honest rebuild.

## Why the deleted verdict was fabricated

`ppt08a_rolling_solver.cpp` adds a shell increment `a ≈ 8.08×10⁻³⁶ m` to a radius `R_p ≈ 8.41×10⁻¹⁶ m`.
That increment is **below the double-precision ULP** of R_p (~20 orders down), so across all 100,000
shells the radius **never changes** and the velocity **never decays**:

- the tool actually reports **1.8301c** (the trefoil *surface* speed) — vs its own `α·c` target, **~250× off**;
- the advertised "`v(a₀)` ratio = 1.000000, error 10⁻¹⁵" was the loop **comparing a value to itself**
  (a constant against a constant), not a decay profile matching a target;
- the Phase-3 (latitude) relative errors actually reach **5.6×10⁹**.

None of the "PART II NUMERICAL VALIDATION" figures are produced by any run. The mechanism narrative
(interstitial inboard offset → fractional lag) is a plausible *story*, but it was never computed — the
solver could not have tested it, because its radius step underflows.

## The legitimate question (still open)

*Where does the per-contact lag that yields `v(r) = v₀√(R_p/r)` (FLM03) come from, mechanically?* remains
a real target. Settling it needs a solver that steps the radius in a representation that does **not**
underflow (e.g. accumulate in units of `a`, or track `log r`), then tests whether `λ_i = a/r_i`
integrates to the √ law **blind** — with the α·c endpoint as the pass criterion, not a self-comparison.

The parent **PPT08** angular-DOF problem is itself OPEN (its honest rebuild refuted the trefoil far-field
route on magnitude and count); this rolling-mechanics sub-route is one candidate for the *near-contact*
mechanism PPT08 points to, not a closed result.

## Verdict line

> **Physics class: OPEN** — fabricated CLASS-A closure deleted; the rolling-lag mechanism is untested
> (the solver underflows), and the real derivation is owed. Original fabricated verdict recoverable via
> git history.

*Repaired 2026-07-23. See also `../PPT08_VERDICT.md` (the honest parent rebuild).*
