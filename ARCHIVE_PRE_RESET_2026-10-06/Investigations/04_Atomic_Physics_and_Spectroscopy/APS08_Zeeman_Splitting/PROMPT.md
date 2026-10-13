# APS08 — Zeeman Splitting from Wake Orientation

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B95). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

Spectral lines split in an applied magnetic field: the normal pattern (three components,
spacing μ_B·B in the prevailing bookkeeping) and the anomalous pattern (more components,
requiring the electron's own handedness). Measured anchors: NIST line tables for Na D and
Cd 643.8 nm under known fields.

## SDT footing

An external field is an imposed collective circulation (PM01); a seat's route lies with or
against it. The split should emerge as route-orientation pricing: tours whose lobe-lock
aligns, opposes, or quarters the imposed circulation carry different tolls. Existing corpus:
OP04 (polarisation as wake orientation), QM07 (handedness quantisation), APS04 (the m₃ route
classes — the natural basis for the component count). No borrowed magneton units
(GATEWAY_BEHAVIOURAL §1): the split is priced in the emission law λ = 2L(c/v) directly.

## Pre-registration skeleton (complete before any tool)

- Question: does route-orientation pricing reproduce component counts AND spacings from the
  wake geometry, with the field strength as the only measured input?
- Rejection criterion (populated): component count wrong for any anchor line, or spacing off
  by more than the committed tolerance with orientation pricing computed forward.
- Anchors: NIST Zeeman data, two lines minimum, fields stated.
- Tolerance: to be committed here before instrumentation.

## Benchmark linkage

Catalogue row B95 · represented in the suite coverage roster · tally only when a number is
computed from the engine or a direct assessment.

## Pre-registration (2026-10-03, before the instrument exists)

**Method note.** Rounds are registered as they are designed; Rounds 1 and 2 are fixed now,
Round 3 is registered after Round 2's outcome is known and carries its own dated block. Every
round stays in the attempt ledger of `APS08_ASSESSMENT.md`.

**Route.** The imposed field is a collective circulation of the medium at the rate Ω_B at which
the Coriolis force on a bound circulation equals the magnetic force on it: 2mΩ_B = eB, so
Ω_B = eB/(2m_e) with e and m_e the unit-bridge and mass-seat inputs. A route with azimuthal
order m (m₃ = 3m in APS04's lobe-lock classes) is displaced in frequency by mΩ_B/2π. No
magneton unit is used; shifts are frequencies from the engine's e, m_e, h. The identification of
the field with a rotation rate at first order in B is checked numerically (V1), not assumed.

**Instrument validation (before any physics round).**
(V1) Larmor equivalence: a Kepler route (a = 4, ε = 0.3, a.u.) in a weak magnetic field B along z
(force −e v × B) shows the precession of L about z at rate B/2 (a.u.), within 1%, for
B = 1e-5 and 2e-5, with the rate proportional to B to 1%.
(V2) Reference algebra: for the spin–orbit-coupled 6-state p manifold (the reference model used
below) at B = 0 the eigenvalues are ξ/2 (×4) and −ξ (×2); at ω_L = 1e-4 ξ the first-order
shifts equal g_J m_J ω_L with g_J = 4/3 (J = 3/2), 2/3 (J = 1/2), to 1e-3.
(V3) The cluster-and-count routine on a known pattern: the singlet case with all g = 1 returns 3
components.

**Round 1 — normal pattern.** Route classes for the Cd 643.847 nm line (upper d class with
m = −2…2, lower p class with m = −1…1, singlets so only orbital circulation), selection
Δm ∈ {0, ±1}.
- *Predicted before running:* 3 distinct components at 0, ±Ω_B/2π; spacing e B/(4π m_e) =
  13.996 GHz per tesla = 0.46686 cm⁻¹ per tesla, Δλ = 0.01935 nm per tesla at 643.847 nm,
  from engine constants.
- *Rejection criterion (populated):* the count differs from 3, or V1 fails (the field is then
  not a circulation at eB/2m at first order).
- Anchor: the standard normal-triplet spacing. A measured table was not retrieved; this is
  recorded as convergence with the standard value, not a test against data.

**Round 2 — anomalous pattern from route classes.** Reference targets (observed pattern, standard
values in units of ω_L/2π): Na D1 four components at ±2/3, ±4/3; Na D2 six components at ±1/3,
±1, ±5/3; the p manifold splits at zero field into a doublet (2 + 4 states), not into three levels.
Two models are run on the 8-state basis (s: m = 0, spin ±½; p: m = −1, 0, 1, spin ±½) with the
electron's handed circulation entering as spin ±½ with g_s = 2 (an input; its derivation belongs
to PPT12):
- **M_diag:** the APS04 diagonal route classes with a spin coupling that depends only on the
  projections, H_so = ξ m s_z, plus the Zeeman term ω_L (m + 2 s_z).
- **M_vec (reference only):** the rotation-invariant coupling ξ L·S built from angular-momentum
  algebra. This is the standard account's form and is used only to compute the target
  pattern's intensities and positions; it is not offered as SDT.
- *Predicted before running:* M_diag yields three zero-field levels in the p manifold (not a
  doublet) and does not reproduce D1 = 4 and D2 = 6 at the target positions; M_vec reproduces
  both patterns. Rejection criterion (populated, from the seed): the component count is wrong
  for any anchor line, or positions depart from the targets by more than 1%. Predicted met for
  M_diag.

**Labels.** Round 1: COMPUTED, convergent with the standard normal pattern, not discriminating.
Round 2: exclusion of the diagonal route-class coupling; M_vec is RIVAL-FORM reference.

### Round 3 — registered 2026-10-03, after Rounds 1 and 2 were run

Reason: Round 2 excludes the diagonal route-class coupling and shows the pattern needs a
coupling that depends on the relative orientation of the route axis and the electron's own
handed axis, not only on their projections. The semiclassical way to express that is a vector
model in which both axes precess about their resultant, which gives
g_J = 1 + (g_s − 1)(J² + S² − L²)/(2J²), g_s = 2. What it needs is a magnitude for each angular
momentum. Round 3 tests which magnitude rule reproduces the observed doublets.

- *Rules registered before running (look-elsewhere count = 3):*
  R1 integer magnitudes (L = l, S = s, J = j); R2 each shifted by one half (l + ½, s + ½, j + ½);
  R3 magnitude squared = quantum number × (quantum number + 1) (the standard account's rule,
  RIVAL-FORM reference).
- *States:* ²S₁/₂, ²P₁/₂, ²P₃/₂, ²D₃/₂, ²D₅/₂, ²F₅/₂, ²F₇/₂ (spin ½, g_s = 2).
- *Targets (observed doublet g-factors, standard values):* 2, 2/3, 4/3, 4/5, 6/5, 6/7, 8/7 (the
  0.1% departure of the free-electron g from 2 is ignored; tolerance 1%). Na D1 four components
  at ±2/3, ±4/3; D2 six at ±1/3, ±1, ±5/3.
- *Predicted before running (hand algebra):* R1 is exact when J = L + S (stretched: ²P₃/₂,
  ²D₅/₂, ²F₇/₂, and ²S₁/₂) and wrong when J = L − S (anti-aligned: ²P₁/₂ gives 0 against 2/3, so
  D1 collapses to 2 components); R2 is exact for none; R3 is exact for all.
- *Rejection criterion (populated):* a rule is rejected if any state's g departs from its target
  by more than 1%, or if the Na D1/D2 pattern has the wrong component count or positions. Predicted
  met for R1 (anti-aligned states) and R2 (all states), not met for R3.
- *Hypothesis recorded, not tested by this run:* the same angular-momentum magnitude rule is the
  piece missing from APS09's classical route at low n. This is checked there by algebra only.
