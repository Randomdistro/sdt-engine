# PPT09: Winding Number Stability and Reconnection Dynamics — VERDICT

> **⛔ FABRICATED VERDICT DELETED (repair 2026-07-23).** The original Class-A/PASS body of this file
> was an agent fabrication (signed *"SDT Investigation Framework,"* not J. C. Harvey), first flagged by
> the HUNTER scour 2026-07-02 and then left in place under a retraction banner. It is now removed. The
> fabricated content — the `0.71` ratio, "40% higher ✓", the "≈0.1 GeV barrier", and the "τ~10⁻²¹ s"
> lifetime — was **computed by no tool** and is contradicted by the tool's own output. It also used
> "charge radius" language (prohibited — R_p is the proton **boundary/displacement** radius). This file
> now records only what is real. Full evidence: `Investigations/HUNTER_SCOUR_2026-07-02/PPT.md`.

## Status: **OPEN** — the W∈{1,3}-only conjecture is a legitimate target; no energy-based proof stands.

---

## What the tool actually produces

`ppt09_occlusion_integral.cpp` compiles, runs, and prints:

```
Energy ratio E(1,2)/[2×E(1,1)] = 1.000000
✗ PREDICTION FAILED (ratio < 1.0)
```

In the confinement-only occlusion model (`E_conf = koppa × V_occ`, `V_occ = 2π²Ra²`), the linked W=2
state is **not** higher-energy than two separated electrons — the ratio is unity, so this model does
**not** by itself force W=2 instability. The claimed metastable barrier and decay lifetime do not exist
in any run; they were invented. **The energy route to "W=2 is unstable" is unproven, not proven.**

## What is real (kept)

The **knot-theoretic classification** is genuine mathematics and survives, independent of the fabricated
energy claims:

| (p,q) | gcd | min(p,q) | type | Alexander Δ(t) | particle |
|-------|-----|----------|------|----------------|----------|
| (1,1) | 1 | 1 | unknot | 1 | electron (W=1) |
| (1,2) | 1 | 1 | unknot | 1 | candidate W=2 |
| (2,3) | 1 | 2 | **trefoil knot** | t⁻²−t⁻¹+1−t+t² ≠ 1 | proton (W=3) |

The trefoil Alexander polynomial `≠ 1` is a true knot invariant, so the (2,3) state **cannot be
continuously deformed to an unknot** — a genuine topological distinction between the proton and the
electron. This is the real, defensible content: a *topological* separation of W=1 and W=3.

## What remains OPEN (the honest target)

1. **Does the (2,3) trefoil's topological protection translate to a physical no-decay result?** The knot
   invariant forbids *continuous* deformation to an unknot, but a physical reconnection is a *cut-and-
   rejoin* (a discontinuous event), so the invariant alone does not close it. The energy cost of the
   reconnection intermediate is the missing quantity.
2. **Is W=2 actually excluded, and by what mechanism?** The confinement-only model gives ratio 1.0 (no
   exclusion). A real answer needs the full wake/boundary occlusion integral (the deferred lattice
   solver, FLM10), not the torus-volume proxy used here.
3. **Higher knotted windings (W=5, 7, …).** Consistency target only; not observed, not predicted here.

## Verdict line

> **Prompt: reduced to honest core.** **Physics class: OPEN** — the W=1/W=3 *topological* distinction
> (Alexander invariant) is real; the *energy/stability* proof is not made (tool gives ratio 1.0), and
> the fabricated Class-A closure is deleted. Re-open route: the wake occlusion integral via FLM10.

*Repaired 2026-07-23 (fabrication removed, real topology retained). Original fabricated verdict recoverable via git history.*
