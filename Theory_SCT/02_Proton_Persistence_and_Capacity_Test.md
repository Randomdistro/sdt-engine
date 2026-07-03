# SCT — The Proton Persistence Number (#1) + the Capacity-Selection Test (#2)

> Cashes the [Part 8.2 derivation](01_Axiom_Audit_and_SDT_Derivation.md) into numbers for the
> proton, and tests whether the `W=1,3` particle selection is the SCT's **capacity** cutoff.
> **Author:** J. C. Harvey, Melbourne. Order-of-magnitude where stated; the conclusions are
> robust to the estimates (the `2^{d_min}` factor swamps every prefactor).

---

## Result in one paragraph

The SCT's **persistence half** works, quantitatively: the proton's topological `d_min ≈ 10³⁹`
(spations across the trefoil tube that must reconnect *simultaneously* to unknot it) exceeds the
mere **`~218`** needed to already beat the measured proton lifetime — by **36 orders of
magnitude**. So SDT predicts proton stability *as a number*, not by fiat. The SCT's **capacity
half** does **not** do the selecting: the knot-code rate `R = k/n ≈ 10⁻⁶⁰` for *every* winding,
so `R < C_E` is satisfied by all of them and discriminates none. **The particle spectrum is a
`d_min` (topological-protection) selection, not a capacity cutoff** — which corrects open item #2
of the Part 8.2 audit.

---

## #1 — The proton persistence bound, as a number

**Inputs (SDT).** Sampling rate `λ`, topological minimum distance `d_min`:

- `λ = c/R_p = 3.56×10²³ Hz` — the proton's own coherence clock (PPT06 `ω_max`). *(Using the
  Planck rate `c/ℓ_P = 1.86×10⁴³ Hz` instead shifts the answer by 20 orders — negligible, see below.)*
- `d_min = π(a/ℓ_P)² ≈ 9.5×10³⁸` — spations across the trefoil **tube cross-section**
  (`a = R_p/3 = 0.28 fm`, the Level-5 `T_2`-scale minor radius). This is the *minimum number of
  simultaneous spation-reconnections* needed to cut a strand and change the knot class — the SCT's
  "smallest number of component changes to a distinct valid structure," read topologically.

**The bound.** `τ ≥ (1/λ)·2^{d_min−1}`:

| quantity | value |
|---|---|
| `d_min` **required** to exceed `τ_exp > 1.67×10³⁴ yr` | **217.8** (proton clock) / 283 (Planck rate) |
| `d_min` **actual** (trefoil tube cross-section) | **9.46×10³⁸** |
| margin `d_min_actual / d_min_required` | **4.3×10³⁶** |
| predicted `log₁₀(τ/s)` | **≈ 2.8×10³⁸** → `τ ~ 10^(10³⁸·…) ` — effectively eternal |

**Reading.** Only **~218** simultaneously-corrupted spations would be needed to push the proton
past the experimental lifetime floor; the protected trefoil demands **~10³⁹**. The proton is
stable because **unknotting it is a `2^{−10³⁹}`-probability event**. Proton decay is not "very
slow" — it is **topologically shut** for the protected `(2,3)` class. (This is also *why* the
`λ` choice is irrelevant: a 20-order change in the prefactor against a `2^{10³⁹}` factor is
nothing — the conclusion depends only on `d_min` being macroscopic, which topology guarantees.)

**What this is and isn't.** It is a genuine SDT *prediction of proton stability from topology*,
with the right margin over experiment. It is **not** a computed *finite* lifetime — that would
require the lowest-`d_min` *decay channel*, and for the protected trefoil there is none below the
full cross-section. (A decay would need a path that changes the knot class with few reconnections;
PPT09's topological protection says no such path exists for `W=3`.)

---

## #2 — Is the `W=1,3` selection the capacity cutoff `R < C_E`? **No.**

**The knot-code rate.** `R = k/n` with `k` = bits to specify the winding class (`~log₂(W+1)`,
a few bits) and `n` = the structure's spation count (`~5.9×10⁵⁹` for the proton boundary).
`C_E` = relay capacity `~ O(1)` bit/spation (Law I, T2, generous upper bound):

| `W` | `k` (bits) | `R = k/n` | vs `C_E ~ 1` |
|---|---|---|---|
| 1 (unknot, electron) | 1.00 | `1.7×10⁻⁶⁰` | `R ≪ C_E` |
| 2 (reducible) | 1.58 | `2.7×10⁻⁶⁰` | `R ≪ C_E` |
| 3 (trefoil, proton) | 2.00 | `3.4×10⁻⁶⁰` | `R ≪ C_E` |
| 5 | 2.58 | `4.4×10⁻⁶⁰` | `R ≪ C_E` |

`R ≈ 10⁻⁶⁰` for **every** winding — the capacity bound is met with ~60 orders of margin and
**discriminates none of them.** So `W=1,3 ⟺ R<C_E` is **false as a capacity statement**.

**What actually selects the spectrum is `d_min`:**

- `W=1` (unknot) — the protected ground (no crossing to undo). Persists → **electron**.
- `W=2` — a connect-sum of two unknots: **reducible**, `d_min ~ 0` (it simply splits into two
  `W=1`). No protection → decays → **absent**, exactly as observed.
- `W=3` (trefoil) — a *true* knot (`Δ(t) ≠ 1`), `d_min ~ 10³⁹`. Persists → **proton**.
- `W≥5` — protected but high-crossing; PPT09 leaves these "awaits discovery." `R` is still
  `≪ C_E`, so **capacity does not forbid them** — only their formation cost / search status does.

**Conclusion (#2).** The SCT's *capacity iff* — the part the Part 0 audit already flagged as the
weakest, most-empirical axiom-content — is **satisfied but not load-bearing at the particle
scale.** The winding spectrum is governed entirely by the **`d_min` / topological-protection**
side, i.e. by **Law VI**. This *corrects* the Part 8.2 open item: "prove `W=1,3` is the capacity
cutoff" is answered **negatively** — it is a `d_min` threshold, not a capacity cutoff.

---

## Synthesis: what the SCT *is*, at the particle scale

Putting #1 and #2 together sharpens the Part 8.2 verdict:

> **For SDT particles, the Structural Coding Theorem reduces to its `d_min` half — which is
> exactly Law VI (topological protection) — while the Shannon *capacity* machinery is vacuously
> satisfied (`R ~ 10⁻⁶⁰ ≪ C_E`) and does no selecting.**

So the honest, refined picture:
- **The code, the decoder, the persistence bound** (`d_min`, Law VI + Law IV) — *real and
  load-bearing*; #1 shows it predicts proton stability with a 36-order margin.
- **The capacity bound** (`R < C_E`, the "iff") — *true but inert* for particles; it would only
  bite for **macroscopic, high-rate** structures (the crystal/DNA regime, where `n` and `k` are
  comparable and the §5 binomial-prefactor caveat also lives). That is where the capacity half of
  the SCT must be tested — **not** on particles.

**Net:** the SCT-from-SDT is genuine, and it is specifically the **Law-VI topological-protection
content**. The Shannon "iff" is a correct dressing that becomes substantive only at scales where
information rate approaches relay capacity — a regime the particle spectrum never enters.

---

### Honest residue

- `d_min` is taken as the tube **cross-section** spation count (`π(a/ℓ_P)²`); a fuller treatment
  would compute the minimum-energy reconnection set of the `(2,3)` knot. Either way `d_min` is
  macroscopic (`≫ 218`), so the conclusion holds.
- `C_E ~ 1` bit/spation is an upper-bound stand-in for the Law-I relay capacity (T2); a derived
  `C_E` would only *lower* it, strengthening "capacity doesn't bind particles."
- The macroscopic-structure capacity test (crystals, DNA) — where the SCT's `R < C_E` should
  actually do work — remains open and is the right next target for the *capacity* half.
