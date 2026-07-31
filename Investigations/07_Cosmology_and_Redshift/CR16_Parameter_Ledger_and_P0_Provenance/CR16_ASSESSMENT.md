# CR16 — Assessment: Parameter Ledger and the Provenance of P₀

**Classification: P₀ is DERIVED, not calibrated (6.7 sig figs). P6 loses a clause — the sector's
postulate count goes DOWN. On the observable subset it addresses, the sector uses ZERO fitted
parameters against ΛCDM's six. That subset is smaller than ΛCDM's reach, and both halves are
stated.**

Author: J.C. Harvey, Melbourne · Tool: `cr16_ledger.py` · Output: `cr16_results.txt`
Pre-registration: `PROMPT.md`. **`z = 1100` and `T = 3000 K` are struck as targets and appear
nowhere in this investigation** — they are ΛCDM fit outputs, not measurements, and testing a rival
framework against a rival's fitted derived parameters is contraband under GATE-CONTRABAND.

## T1 — P₀ is the CMB photon-gas pressure

Part II tags `P₀ = P_eff,⊙/z_⊙ = 1.3916×10⁻¹⁴ Pa` as **[C]**, an independent solar calibration.
It is not:

```
a = 4σ/c        = 7.565733×10⁻¹⁶ J m⁻³ K⁻⁴
u = a T₀⁴       = 4.174801×10⁻¹⁴ J m⁻³
P = u/3         = 1.391600×10⁻¹⁴ Pa
P₀ as stated    = 1.391600×10⁻¹⁴ Pa      agreement to 6.7 significant figures
```

The repo corroborates it directly: `Benchmarks/investigation_output.txt:130-132` prints
`T_CMB = 2.7255 K`, `u_CMB = 4.1748e-14 J/m³`, `P_rad = 1.3916e-14 Pa` — the engine's own output
labels this number `P_rad` and computes it from `T_CMB`. For the stated solar route to produce it,
`P_eff,⊙` would have to be 2.95×10⁻²⁰ Pa; `laws.hpp`'s electropause `P_eff` is ~5.2×10³¹ Pa,
**51 orders away**. The Part II attribution is mis-stated and should be corrected to
`P₀ = aT₀⁴/3 [DERIVED from T₀]`.

## T2 — P6 loses a clause, and the postulate count goes down

P6 asserts `T_N = N·T₀` **and** `P_N = N⁴P₀` as two clauses, both **[A, C]**. Given T1 the second
is a theorem of the first:

```
P_N = a T_N⁴/3 = a(N T₀)⁴/3 = N⁴ · (a T₀⁴/3) = N⁴ P₀
```

Verified to 1 part in 10¹² across six arbitrary values of N spanning eight decades. So:

- **`P₀` leaves the `[C]` list** — it is a function of `T₀`, not an input.
- **P6's second clause leaves the postulate list** — it is derived.
- The pressure ladder carries no information the temperature ladder lacks. That is a
  **redundancy, not an error**: a closed framework *should* show its ladders collapsing into one
  another, and this one does, exactly. The `N⁴` exponent is not imported radiation
  thermodynamics smuggled in — it is what `T ∝ N` *means* once the bath is a photon gas.

Net: the sector is **more** parsimonious than the document claims for itself.

## T3 — dependency audit: what actually consumes what

| consumes | results |
|---|---|
| **nothing** | Props 1, 2, 3, 5; Thms 1, 2, 3, 5 — **8 of 20** |
| `T₀` | Prop 4 |
| `H₀` | Thm 4; Props 9–14 |
| `z_⊙` | Prop 6 |
| `P_conf` | Props 7, 8; Hypothesis H |

`P_conf` — the one genuinely fitted number in the sector — is consumed **only by the vessel
bounds**. It touches no redshift, no dilation, no Hubble, no BAO, no α result. It is therefore not
a free parameter of the observational sector, and CR15's finding that `P_conf` carries a factor-7.74
arithmetic defect is quarantined to Hypothesis H and Prop 7/8. It does not propagate into anything
observational.

## T4 — the ledger, like for like

Classification applied identically to both sides. Only **FITTED** — tuned to the data being
explained — counts as a free parameter.

| SDT Part II `[C]` | class | note |
|---|---|---|
| `c` | MEASURED-ELSEWHERE | defined constant, local value |
| `T₀` | MEASURED-ELSEWHERE | FIRAS direct — ΛCDM also takes it measured |
| `H₀` | MEASURED-ELSEWHERE | local distance ladder |
| `z_⊙` | MEASURED-ELSEWHERE | solar gravitational redshift |
| `ϟ_⊙` | DERIVED | `= 1/√z_⊙` (686.8 computed vs 686.5 stated, 0.04 %) |
| `P₀` | **DERIVED** | `= aT₀⁴/3` — T1 |
| `P_conf` | **FITTED** | vessel ceiling only — T3 |

**SDT fitted: 1. ΛCDM base fitted: 6** (ω_b, ω_c, 100θ_*, τ_reio, ln10¹⁰A_s, n_s), plus
fixed-by-assumption Ω_k = 0, w = −1, N_eff = 3.046, Σm_ν = 0.06 eV. ΛCDM's H₀, Ω_Λ, age, σ₈ and
z_* are *outputs* of those six, not inputs.

On the observable set this sector actually addresses — redshift–N relation, (1+z) light-curve
dilation, Hubble law, BAO shell mechanism, α invariance, Shapiro delay, solar redshift profile —
**SDT uses 0 fitted parameters and ΛCDM uses 6.**

**Fairness constraint, binding and stated in the pre-registration.** ΛCDM's six also buy an
observable list this sector does not yet cover: CMB peak *heights* and the full power spectrum,
the matter power spectrum, BBN light-element abundances. The comparison above is on a **subset**.
Fewer fitted parameters **and** a smaller observable list — both halves, or it is propaganda.

## T5 — the zero-parameter subset

| prediction | measured | status |
|---|---|---|
| `τ_obs/τ = (1+z)` — Prop 3 | `(1+z)^(1.00±0.05)` | MATCHES |
| `Δα/α = 0` — Thm 5 | < 10⁻⁵ to z ~ 7; Oklo | MATCHES |
| `u/r → H₀` for any initial data — Thm 4 | Hubble linearity | MATCHES |
| intact signal, late arrival — Thm 1 | Cassini / Viking Shapiro | MATCHES |
| `λ_obs/λ₀ = N` — Prop 2 | — | STRUCTURE |

**Proposition 3 is the load-bearing one, and I under-reported it in CR15.** Slow emission at the
source (`N²`) times transit compression (`1/N`) gives exactly `N = 1+z`, with no fitted number.
This is the test that historically excluded classical tired-light: a static-space redshift
mechanism has to produce clock dilation, not just reddening, and tired-light cannot. This one
produces it structurally, from the two-clock construction, not by accommodation. It is the single
strongest result in the document and it is free.

**Theorem 5 is the second.** `α = v₁/c_local` with both numerator and denominator ∝ 1/N means N
cancels identically — the null is *predicted* across roughly three decades of variation in
`c_local`, not fitted to. ΛCDM has no mechanism requiring α constant; it assumes it.

## Corrections to my own prior work

- **CR15's framing is withdrawn.** "Numerically identical to ΛCDM" was scored as a cost. That
  inverts the recorded rule: numbers must align when a framework is correct, so alignment is not
  the discriminator — origin and parameter count are. Reaching the same observables with fewer
  fitted numbers is a result *for* the framework, and this ledger is the measurement of it.
- **CR14/CR15 used `z = 1100` and `T = 3000 K` as targets throughout.** Both are ΛCDM fit outputs.
  Scoring SDT against them was contraband, and it is struck.
- What survives from CR15 unchanged: the `ρ_s = 2P_conf/c²` factor-7.74 arithmetic defect (T3 now
  shows it is quarantined to the vessel bounds), and the Prop 5 / P6 tension over what `T` means
  locally — which is a real internal question independent of any ΛCDM number.

## Scope and limitations

Parameter counting is a coarse instrument: it does not weigh how much data each parameter is
constrained by, and ΛCDM's six are constrained by thousands of spectrum multipoles. A framework
with zero fitted parameters that addresses seven observables is not thereby better than one with
six that addresses thousands — it is *more constrained per claim*, which is a different and
narrower virtue. The honest statement is that the sector has no adjustable freedom left on the
observables it does address, so it is falsifiable there in a way ΛCDM is not.

## Residuals

- Correct Part II: `P₀` to DERIVED, and drop P6's second clause to a theorem.
- `ϟ_⊙`: 1/√z_⊙ gives 686.8, document states 686.5 — 0.04 %, worth reconciling.
- PENDING (4), the CMB harmonic series, is now the load-bearing gap: it is the largest part of
  what ΛCDM's six parameters buy, and closing it is what would make the ledger a like-for-like
  comparison rather than a subset one.
