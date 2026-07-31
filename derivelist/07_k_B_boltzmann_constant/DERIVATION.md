# k_B — Boltzmann constant (kelvin unit bridge)

> **J. C. Harvey, Melbourne — 2026-07-30.** Value: 1.380649×10⁻²³ J/K (SI exact,
> definitional since 2019). Whitelist entry: `laws.hpp:130` — listed in-header
> under "Unit conversion constants (not fundamental scales)". Primary records:
> TD02 (`Investigations/11_Thermodynamics_and_Statistical_Mechanics/TD02_.../TD02_VERDICT_DIRECT_2026-07-26.md`),
> TD06 (same directory family). Re-run: `../derivelist_results.txt` §[7].

## Role in the framework

k_B converts the kelvin — a historical unit — into joules. Temperature itself
is derived natively: throughput per degree of freedom, counted (TD02).

## What is on record

**TD02 (direct run 2026-07-26).** The exponential occupation is an OUTPUT of
native relay counting three ways (exact complement-count marginal, R² 0.999994;
relay-exchange dynamics over 5×10⁷ ticks; Lagrange route) — all landing on
β = ln(1+N/E) from the movement budget, with the firewall printed (no partition
function, no predefined T, no S(E−ε) expansion). **P4 delete-test: k_B enters
only as the kelvin unit bridge.** Equipartition ⟨e_i⟩ = ½k_B·T per quadratic
DoF, initialisation-independent.

**TD06 (direct run 2026-07-26).** The whole blackbody suite from counted
lattice modes: Planck curve to 0.0014%, Stefan–Boltzmann σ to 4.4 ppm, Wien
b to 0.008%. Consistency re-run here:

```
a_rad = π²k_B⁴/(15ℏ³c³) = 7.5657332642e-16   (dev +0.0004% vs measured)   [DERIVED]
```

**SI status.** Since 2019 k_B is exact by definition — it *defines* the kelvin.
A defined conversion has no physical content left to derive; asking for a
derivation of k_B is asking to derive a unit choice.

## Scope / Limitations / Residuals

- TD02's physics class is CONVERGENCE (Class C): the Boltzmann form is shared —
  the form cannot discriminate between frameworks; the route (native counting,
  firewalled) is SDT's own. The SDT-distinct residue is the freeze-out
  separation (T_kin/T_ent < 1 at quantised throughput) — a live measurement
  target, not yet hunted.
- TD06's ceiling, stated on the record: ε = hν granularity is carried in as the
  Law-I bridge, asserted not derived — that open root belongs to ℏ/the seat,
  not to k_B.

## Status

**Line drawn — by reclassification.** k_B is a unit bridge (in-header label
already says so). Temperature is counted natively; the kelvin-to-joule ratio is
a definition. Nothing about k_B remains on the physics side of the ledger.
