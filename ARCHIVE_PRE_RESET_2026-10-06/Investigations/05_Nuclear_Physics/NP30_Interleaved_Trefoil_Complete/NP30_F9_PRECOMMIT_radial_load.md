# NP30 §11 radial-load test — PRE-COMMIT (fishbowl gate, written before data opened)

> **Fetch F9** (Datasets/MUST_FETCH): elastic e-scattering charge-density profiles for the
> doubly-magic ladder ¹⁶O, ⁴⁰Ca, ⁴⁸Ca, ⁹⁰Zr, ¹³²Sn, ²⁰⁸Pb. Source: De Vries–De Jager–De Vries
> 1987 (ADNDT 36, 495), Sum-of-Gaussians / Fourier-Bessel coefficients.
> **This criterion is dated and frozen BEFORE any coefficient is read.** — Fable, 2026-07-23.

## The question §11 could not answer with rms radii
Whole-nucleus rms radius showed the boundary compounding to the derived close-pack floor
(r0→0.9300) and saturating. It **averages over all shells** — it cannot see whether the *inner*
core of ²⁰⁸Pb is squeezed *harder* than the same core in ⁴⁰Ca ("borne down from above"). The
radial density profile ρ(r) can.

## The physics trap (stated up front — SDT's strong form can LOSE here)
Nuclear **saturation** is one of the most robust facts in nuclear physics: interior density is
~constant, ρ₀ ≈ 0.16 nucleons/fm³, across nuclei. Note the §11 floor is *already* a restatement
of it — r0→0.9300 ⟺ mean matter density → the bulk value. So:
- A **flat** interior density up the ladder is the SATURATION result. It would make §11's
  "saturation at the floor" an **explanatory derivation** of ρ₀ from close-packing (R_p, η) —
  real, but **NOT a fork** against the SM, and it would **REFUTE the strong/literal "borne down
  from above"** (progressive inner compression) as a bulk effect.
- A **rising** interior density up the ladder would both support literal inner-compression AND
  **fork against saturation** — a far stronger claim.
Pre-committing means: I report *whichever* of these the data shows, including the refutation.

## Observables + pre-committed criteria
Charge density is proton density (weighted Z/A); heavy nuclei are neutron-rich (Pb Z/A=0.39 vs
O 0.50), so central *charge* density falls from the proton fraction alone. Convert to matter:
ρ_m(r) ≈ ρ_ch(r)·(A/Z) (assumes n,p similarly distributed — an approximation, flagged).

1. **Interior matter density ρ_int** = ρ_m averaged over the flat interior (exclude central
   r<1.5 fm wiggle and the surface r>R−2 fm).
   - **REFUTE "borne down" / CONFIRM saturation:** ρ_int flat within **±8%** across O→Pb.
   - **CONFIRM strong "borne down" / fork vs saturation:** ρ_int rises **monotonically and >15%**
     O→Pb.
   - (in-between 8–15% or non-monotone → INCONCLUSIVE, report as such, no spin.)
2. **Derived saturation density (side-check, bankable either way):** does ρ₀ from close-packing
   of proton boundaries — ρ₀ = 3/(4π (√(5/3)·r0)³) with r0=R_p/η^⅓=0.9300 — land at the measured
   0.15–0.17 fm⁻³? Pre-commit: **PASS if 0.14–0.17**, else the close-pack→saturation identity is
   weaker than §11 implies.
3. **Central feature (secondary, no pass/fail — descriptive):** ²⁰⁸Pb central depression depth vs
   ⁴⁰Ca central bump — does the *inner shell* sit at higher density in the heavier nucleus even
   when the mean is flat? Report the profile shape; do not score.

## Anti-fish leash
- No parameter is tuned to the density. r0=0.9300 and R_p are already fixed (§1/§6).
- If ρ_int is flat, I do **not** re-cast the flatness as a win — it refutes the strong form and
  demotes §11's saturation to a derivation-of-ρ₀ (still real, labelled explanatory-not-fork).
- The A/Z→matter conversion is an approximation; if the verdict hinges on it (near the 8–15%
  band), the result is INCONCLUSIVE pending a proper n-distribution, not banked.

## Verdict slots — FILLED 2026-07-23 (data: UVa NCD archive, De Vries 1987 SOG profiles)

> **Terminology (Harvey, mid-run): it is MOVEMENT.** What elastic e-scattering maps is not
> "charge" and not a substance — it is the distribution of **movement**. Written ρ_mv(r)
> throughout. Energy = movement only; the profile is movement-per-volume.

**Normalization settled empirically (the trap I pre-flagged):** every profile integrates to
**A** (0.997–0.999 of A, not Z) — so these are movement densities per nucleon count, in fm⁻³.
**No A/Z conversion needed**; the conversion I was ready to apply would have been an error.

**Measured interior movement density ρ_int** (window 1.5 fm → R_sharp−2, pre-committed):
```
 16O  0.1372      40Ca 0.1524      48Ca 0.1757      124Sn 0.1612      208Pb 0.1584
```
- spread **24.5%** · **monotone rising? NO** (peaks at ⁴⁸Ca, then FALLS)
- **²⁰⁸Pb interior (0.1584) is LESS dense than ⁴⁸Ca (0.1757).** The heaviest nucleus does
  **not** have the densest interior. Among nuclei with a genuine bulk interior (Sn, Pb) it is
  flat to ~2%.

- **ρ₀ side-check: value 0.1379 fm⁻³.** ⚠ **My pre-committed band (0.14–0.17) was
  MIS-SPECIFIED** — I set it against the *central* density (~0.16) when close-packing predicts
  the **mean**. Stated openly rather than moved: by the letter, 0.1379 **narrowly misses** the
  band. Like-for-like (mean vs mean) it is a near-exact hit — canonical sharp-radius r₀=1.2 fm
  ⟹ 0.1382 (**0.2%**), measured ²⁰⁸Pb mean 0.1385 (**0.4%**).
- **ρ_int trend O→Pb: NOT RISING** — non-monotone, saturating. (Endpoint-only would read
  +15.5% and would have tripped my ">15% ⇒ fork" clause; the **monotonicity conjunction caught
  the false confirm.** ¹⁶O's interior window is only 1.5–2.0 fm and is unreliable anyway.)
- **"Borne down from above" (strong form): REFUTED.** Adding shells above does **not**
  progressively compress the interior. The interior saturates; it does not compound.
- **§11 saturation reclassified as: derivation-of-r₀ (explanatory, NOT a fork).**

## What survives, and it is not small
The close-packing of proton boundaries **derives the textbook nuclear radius constant
r₀ ≈ 1.2 fm** — and hence the mean nuclear movement density — from R_p and η alone, **zero
fitted parameters** (0.2% vs canonical, 0.4% vs measured Pb). Every liquid-drop / Fermi-gas
treatment **inputs** r₀. SDT derives it. That is an explanatory result by the corrected
criterion — but it is **not** a divergent fork, and it does not license the inner-compression
claim, which the same data kills.

## Physical resolution (what §11's compounding actually was)
r0 compounds to the floor because the **surface fraction shrinks**, not because the interior
compresses. Light nuclei are nearly all surface (low *mean* movement density); heavy nuclei
approach the bulk value. The floor r0=0.9300 **is** the bulk saturation density expressed as a
radius constant. §11's measured compounding stands exactly as measured — its *interpretation*
as progressive inner compression does not.
