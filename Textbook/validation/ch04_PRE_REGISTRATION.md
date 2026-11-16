# Chapter 4 — pre-registration of the worked-example instruments

Registered 2026-10-27, before `Textbook/examples/ch04_shell_cancellation.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Units for T3–T5: lattice units, cell edge ℓ = 1, source content ε = 1, interception cross-section σ = ℓ² = 1.

## Quantities under test

- `S_pt(R)  = Σ_{p ∈ Z³, 0<|p|≤R} 1/(4π|p|²)` — point-kernel lattice sum.
- `S_sph(R) = Σ_{p ∈ Z³, 0<|p|≤R} ½(1 − √(1 − a²/|p|²))`, `a² = σ/π = 1/π` — exact solid-angle kernel for a spherical target of cross-section σ.
- Continuum value of both: `R` (Proposition 4.1, ray-length form).
- `F(R,s)` — vector sum `Σ_{0<|p−t|, |p|≤R} (p−t)/(4π|p−t|³)` for a target at lattice point `t = (s,0,0)`; continuum value (Proposition 4.3): magnitude `s/3`, directed toward the ball centre.
- Fidelity-loss sum `Σ_{d=1}^{N} τ^d` against its closed form `τ(1−τ^N)/(1−τ)`.

## Instrument validation (must pass before T3–T5 are read)

| id | known answer | tolerance |
|---|---|---|
| V1 | lattice points in ball of radius R=1,2,3,4,5,10 (origin included): 7, 33, 123, 257, 515, 4169 | exact |
| V2 | Σ′ |p|⁻⁶ over Z³ = 8.40192 ; Σ′ |p|⁻¹² = 6.20215 (simple-cubic lattice sums), cutoff R=64 | 1×10⁻⁵ relative |

If V1 or V2 fails the instrument is faulty; no T-result is quoted until it is repaired and re-validated. If a recalled reference value is the suspect, it is re-derived by an independent brute-force route before the instrument is blamed.

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T3 | lattice sums reproduce the continuum shell identity | `|S_pt(R) − R| ≤ 1` and `|S_sph(R) − R| ≤ 1` for R ∈ {16, 32, 64, 128, 256} | yes — an O(R) or O(log R) offset would exceed 1 at R=256 |
| T4 | displaced-observer vector sum equals s/3 toward the centre | `|F| within 2 %` of `s/3`, and x-component negative, for (R,s) ∈ {(64,4), (96,8), (96,24)} | yes — a 1/2 or 1/4 coefficient, or a wrong sign, fails |
| T5 | fidelity closed form | relative difference ≤ 10⁻¹² against direct summation for (N,τ) ∈ {(1000, 1−10⁻⁴), (10⁵, 1−10⁻⁷)} | yes |
| T6 | engine implementation agrees with the chapter's closed forms | `Φ = Nε`, `P_conv = N u_CMB`, `convergence_floor::pressure_gradient(R_CMB) = P_conv/(3 R_CMB)`, each within 10⁻¹² relative | yes |

T6 is an implementation-consistency check: it establishes that the chapter's closed forms and the engine's code are the same expression. It makes no claim about the magnitudes, which carry the measured inputs recorded in the chapter's input ledger.

## Single-pass rule

Every R and (R,s) pair above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such.

## Build line

`cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:<scratchpad>/ch04.exe Textbook/examples/ch04_shell_cancellation.cpp`

## Record of run 1 (added 2026-11-10 as a dated amendment, from the captured outputs of runs 1 and 2)

This section was not written when run 1 was executed; it is added on 2026-11-10 after the verification of Chapter 63 found the gap, and it is derived from `ch04_run1_output.txt` and `ch04_run2_output.txt` only. Run 1 (`ch04_run1_output.txt`) ended with "SUMMARY: one or more pre-registered criteria were not met": criterion T5 (closed form against direct summation to $10^{-12}$) was marked inconsistent at $(N,\tau)=(10^5,1-10^{-7})$, where the relative difference was $2.63\times10^{-12}$ (the case $(1000,1-10^{-4})$ gave $6.1\times10^{-15}$). The cause was cancellation in the closed form at the small per-hop loss $\delta=10^{-7}$ (a difference of terms of size $10^{5}$ giving a sum of the same order with a relative rounding of $10^{-12}$); it was an instrument defect and not a property of the sum. Run 2 (`ch04_run2_output.txt`) used a numerically stable evaluation of the closed form (the relative differences are $1.19\times10^{-16}$ and $0$) and met every pre-registered criterion with the registered tolerance unchanged. Run 2 is the run of record. Run 1 is kept.
