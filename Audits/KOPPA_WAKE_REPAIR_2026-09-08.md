# Koppa–wake relation and provenance repair — 2026-09-08

The geometric relation is ℓ_P = √(ϟ·ƛ), exact and mass-independent.
FLM06 §3b describes the reduction to SDT length geometry and the integer W+1.
The failed Clearing-subdivision route does not establish a general impossibility
of deriving the lattice length. Repository summaries, engine provenance, the
input ledger, website mirrors and affected archived papers now distinguish these.

The engine baryon bridge now evaluates:

```
proton_wake_seats = 3 + 1
proton_wake = measured::R_p / proton_wake_seats
koppa_per_baryon = measured::l_P² / proton_wake
```

No ℏ, mass, G or c enters this calculation. The forward closure uses the same
proton wake. The engine continues to store ℓ_P as a numerical reference; solving
the inverse and forward relation with that same reference is a consistency check,
not an independent numerical determination of both lengths.

With R_p = 8.414×10⁻¹⁶ m, the wake is 2.1035×10⁻¹⁶ m and the baryon koppa is
1.241873175671×10⁻⁵⁴ m. The small change from the previous Compton-wake substitution
is expected because the measured radius and that substitution differ slightly.

Validation: the C++20 input ledger and full benchmark suite rebuilt and ran;
66/66 earned predictions passed, with 19 construction checks, 3 pending note-only
rows and zero genuine failures. The focused `scripts/koppa_wake_regression.cpp`
checks the measured wake, the changed baryon quantum, closure, and downstream
baryon counting. Seven canonical/release/distribution headers passed dependency
checks. Both website copies and their regenerated data/ledger outputs agree.

Historical experiment calculations and route-specific negative results remain
evidence for the routes they actually tested. Existing compiled application
distributions are not rebuilt by this source and website-data repair.
