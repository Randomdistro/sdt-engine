# CR15 — Assessment: The Ionisation Trilemma and the Cold Dense Past

**Classification: T2 FAIL · T3 no-ionised-era · T4 CR14 Branch E WITHDRAWN · T1 one arithmetic
defect (ρ_s / P_conf). The Clearing at N = 1100 is not obtainable from ionisation physics under
any of the three available readings — under each it costs one calibration.**

Author: J.C. Harvey, Melbourne · Tool: `cr15_trilemma.py` · Output: `cr15_results.txt`
Pre-registration: `PROMPT.md` (T1–T5 thresholds fixed before the instrument existed).
Object: *SDT — Cosmological Sector* (2026-07-30), Props 4/5/11/13, P5/P6, PENDING (1)(2)(5).
Gates: CR14's V1–V3 re-run, all PASS (V2 = z 1379.3 against textbook ≈ 1370).

## T1 — arithmetic audit: 13 of 14 reproduce

`N_max`, `v_min`, `T_max`, `P_min`, `T_end`, `v_dec`, `1/H₀`, `t_lb(1100)`, `t_lb(N_max)`,
`D_CMB`, `τ_now`, and both BAO numbers all reproduce to their quoted precision (worst 2.2 %).
The derivational spine of Parts VI–IX is arithmetically sound.

**One defect.** Part VI states `ρ_s = 2P_conf/c² ≈ 2.3×10¹⁷ kg/m³ (nuclear saturation)`. With
`P_conf = 8×10³⁴ Pa` the formula gives **1.78×10¹⁸ kg/m³** — a factor **7.74** high. The stated
value is the right figure for nuclear saturation; the formula does not produce it from the stated
`P_conf`. One of the two is wrong, and it is load-bearing:

- If `ρ_s = 2P_conf/c²` is the correct relation, then `P_conf = 1.034×10³⁴ Pa`, not `8×10³⁴`.
- That moves `N_max` from 1.55×10¹² to **9.28×10¹¹**, and rescales every Hypothesis-H
  prediction (`P_min`, `T_end`, `v_dec`) along with the halfway claim that depends on them.

`P_conf` is tagged **[C]**; it should be reported as the *fitted* quantity it is, and its
provenance stated. Recommend resolving before Hypothesis H is quoted anywhere.

## T2 — the trilemma is real (FAIL, 99 % off)

With the framework's own two scaling laws taken as local statements — `B(N) = B₀/N²` (P5/Prop 5)
and `T_local(N) = N·T₀` (P6) — the Boltzmann argument runs as

```
B/(k_B T) = (θ/T₀)/N³ = 5.793×10⁴ / N³
```

so the past is **hotter** while binding is **weaker**: ionisation runs away. Half-ionisation
lands at **N = 10.554**, a factor **104** from the CMB identification.

| N | T_local [K] | B/(k_BT) | x_e |
|---|---|---|---|
| 1 | 2.73 | 5.79×10⁴ | 0 |
| 10 | 27.3 | 57.9 | 0.0097 |
| 100 | 273 | 0.058 | 1 |
| **1100** | **2998** | **4.35×10⁻⁵** | **1** |

At N = 1100 hydrogen is **fully ionised**, with the binding energy four orders of magnitude
*below* the thermal scale. There is no neutral epoch there to identify with the CMB. Exactly one
leg must be withdrawn: (i) `E_b ∝ N⁻²`, (ii) `T = N·T₀` as a *local* temperature, or (iii) the
identification of the CMB with an ionisation transition at N = 1100.

**Named trap held.** `1100^(1/3) = 10.32` falls near the observed reionisation epoch. That is the
cube root of an imported number and is **not** reported as a match.

## T3 — Prop 5 at face value: there is no ionised era at any epoch

Prop 5's actual claim is that bath quanta and binding energies scale *together*, so `B/k_BT` is
epoch-invariant at its present value, **5.793×10⁴**. The Boltzmann factor `exp(−57930)` underflows
at every epoch. Computed across nine decades of N (10⁻³ … 10⁶), `x_e = 0` throughout, monotonically
decreasing toward the past — a **cold, dense, permanently neutral** past.

This is internally consistent and it is the reading Prop 5 intends, but it carries a consequence
the document has not yet drawn: **no recombination event exists to be triggered.** Prop 11's
phrase "recombination is a global density event" then has no referent, and `z_rec` / `T_rec` have
no mechanical role — they should leave `laws.hpp`'s `measured` namespace rather than sit there as
inputs. The Clearing must be a *different* physical event: the percolation/headroom transition of
P8 and Prop 8. On this reading **PENDING (2) collapses into PENDING (5)**, and the priority list
shortens by one item.

## T4 — CR14's Branch E objection is WITHDRAWN

Registered against my own prior result before running. Prop 13 derives `r(t) ∝ 1/N` for coasting
matter, so `n_b ∝ N³` **without expanding space** — matter dilutes by coasting. CR14's Branch B
assumed `n_b = const` on the reasoning "static, therefore no dilution." That was the wrong density
law, and the error was mine.

| | n_b at transition [m⁻³] | τ = n_eσ_T R_CMB |
|---|---|---|
| CR14 Branch B (n_b const) | 0.251 | 0.0159 — optically thin by 62.8× |
| **CR15 corrected (Prop 13)** | **6.61×10⁸** | **4.19×10⁷ — optically thick** |

A scattering surface does form. **CR14's Branch E is withdrawn and recorded as withdrawn.**

But the correction carries its own cost: the corrected Branch B is **identical to the ΛCDM
comparator** — same `T(N)`, same `n_b(N)`, same solver, same answer, N = 1380.3. Prop 13 buys back
the optical depth by reproducing ΛCDM's density history exactly. CR14's R3 degeneracy therefore
tightens rather than loosens: in this sector the two frameworks are not merely
log-indistinguishable but numerically identical, and both inherit the same gap between the naive
Saha half-point (z ≈ 1379) and the observed last-scattering surface (z ≈ 1090), which only the
Peebles non-equilibrium treatment closes.

## T5 — what a density trigger would need

Under T3's reading the trigger must be purely density-driven, as Prop 5 requires. Granting a
constitutive bridge `n ∝ P^s = N^{4s}` (PENDING 1):

| Threshold | required n [m⁻³] | implies |
|---|---|---|
| τ = 1 over R_CMB | 15.8 | `n ∝ N^0.59`, s = 0.148 |
| CR14 Branch C thermal rung | 1.07×10⁴ | `n ∝ N^1.52`, s = 0.380 |

Prop 13's coasting law delivers `n ∝ N³` (s = 3/4), which **overshoots by 6.2×10⁴**. So Prop 13
and a pure density trigger at N = 1100 are not simultaneously satisfiable: if `n ∝ N³` holds, the
threshold density at N = 1100 is 3.34×10⁸ m⁻³, and *choosing* that threshold is a calibration,
not a derivation.

## The unified result

Across all three readings, N = 1100 costs exactly one fitted number:

1. **P6-local + constant binding** (T4) → reproduces ΛCDM identically; N from Saha is 1380, and
   1090 still requires the same non-equilibrium machinery ΛCDM uses. Nothing is derived.
2. **P5 + P6-local** (T2) → the trigger sits at N = 10.6. Falsified against the CMB identification.
3. **Prop 5 proper** (T3) → no ionised era ever; the Clearing is not recombination, and its
   threshold density is a free choice.

So `z_rec = 1100` remains **CALIBRATED(1)** exactly as CR14 concluded, and this investigation
closes the specific escape route CR14 left open. PENDING (2) as written — "density-triggered
recombination solve → N ≈ 1100" — is not attemptable: there is no recombination on the reading
that motivates it, and on the reading where there is, the answer is ΛCDM's.

**Constructive path.** Restate PENDING (2) as the percolation/Clearing threshold (merging into
PENDING 5), and derive `N ≈ 1100` from the headroom condition of P8 rather than from ionisation.
That route has a real advantage the ionisation route never had: `P8` already contains `N_max`, so
a percolation threshold is expressed in quantities the vessel owns — which also makes the T1
`P_conf` defect the first thing to fix, since `N_max` enters it directly.

## Labels

| Quantity | Value | Label |
|---|---|---|
| T1 spine (13 numbers) | as stated | COMPUTED — reproduced |
| `ρ_s` vs `2P_conf/c²` | 1.78×10¹⁸ vs 2.3×10¹⁷ | **DEFECT — factor 7.74** |
| Trilemma trigger epoch, legs (i)+(ii) | N = 10.554 | COMPUTED |
| `x_e` under Prop 5 | 0 at all N | COMPUTED |
| Corrected Branch B | N = 1380.3, τ = 4.19×10⁷ | COMPUTED (≡ ΛCDM) |
| CR14 Branch E optical-depth objection | — | **WITHDRAWN** |
| `z_rec` = 1100 | — | **CALIBRATED(1)**, unchanged |
| Required bridge exponent | s = 0.148 … 0.380 | COMPUTED — owed by PENDING (1) |

## Scope and limitations

Pure hydrogen; no helium; Saha equilibrium only, no Peebles correction — which is why every
thermal branch here lands at z ≈ 1379 rather than the observed ≈ 1090. `n_b0` is
comparator-sourced (Planck Ω_b h² through ρ_crit, which contains G). Saha remains imported
statistical mechanics (CR14 R4): it is used here only to test consistency *between two of the
framework's own postulates*, and a T2/T3 failure falsifies a combination of P5, P6 and the CMB
identification — **not** the vessel, the pressure ladder, or the Part V redshift derivation, none
of which were under test.

## Residuals

- `P_conf` / `ρ_s` factor 7.74 — resolve before Hypothesis H is quoted; `N_max` depends on it.
- PENDING (6), the ruler-shrinkage vs coasting-matter double-count, is now sharper: Theorem 5's
  corollary gives `a₀ ∝ N` (atoms larger toward the past) while Prop 13 gives separations
  `∝ 1/N`. Both are expansion-mimics and their independence is unestablished.
- Whether Prop 5's cold-dense past can produce the FIRAS blackbody spectrum at all, given that
  the bath is never in thermal equilibrium with matter on that reading. Not tested here.
