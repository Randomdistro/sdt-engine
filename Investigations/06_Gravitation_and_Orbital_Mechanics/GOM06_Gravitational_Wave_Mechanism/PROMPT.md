# GOM06 — GRAVITATIONAL WAVES: MOVE THE SEA, DON'T MAKE WAVES

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes
> 2026-06-27). The prior spec embedded run outcomes ("DONE this pass", "EXECUTED", coefficient
> bands from its own outputs) — those products were the June agent-era layer, **deleted
> 2026-07-24** (git-recoverable), and every one of their claims is demoted to
> **ROUTE-TO-ATTEMPT** below. Nothing in this file is a result.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` · `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G.
> **Engine:** `#include <sdt/laws.hpp>` only. **Execution: DIRECT ONLY — no agents.**
> **Lineage note:** opened as CQ-44; upstream CQ-IDs map to current: CQ-42→FLM06 (spation
> scale/self-boundary), CQ-43→GOM05 (variable closure), CQ-40/41→FLM lattice-EoS/gearing set,
> CQ-16/24→bridge (GM=c²ϟ). E48 (GW speed) and E68 (max-compression interior) are the promoted
> one-liners.

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Whether the inspiral–chirp–merger–ringdown–memory sequence can be
   carried end-to-end by ONE length (ϟ) in a near-incompressible relay lattice, such that:
   (a) the chirp scale and f^{11/3} track come out of `v² = c²ϟ/r` with no G/M (the koppa-meter
   reading of LIGO); (b) the polarisation content is forced to two tensor modes by conservation +
   multipole order, with the scalar "breathing" channel confined to the merger-epoch monopole
   CHANGE Δϟ/ϟ; (c) that same Δϟ is the permanent memory offset — **breathing(AC) ≡ memory(DC),
   one quantity — the correlation GR does not predict**; and (d) the ringdown carries structure
   (echoes at Δt ~ ϟ_f·ln(ϟ_f/ℓ_P)) that pure-Kerr GR forbids. None of these is currently earned:
   the June pass's claims died with its deleted layer.
2. **Why does it matter?** — This is the campaign's strong-field front. The weak-field sector
   (GOM01) is degeneracy-locked (ϟ≡GM/c²); if SDT differs from GR anywhere measurable, it is
   HERE: echoes (F5), the breathing↔memory correlation (F3/F4), and the GOM19 remnant-spin fork.
   E68's no-singularity interior stands or falls with this mechanism.
3. **How will we find out?** — Four gates (§2), each derivation-first with anchors declared (§R1′);
   the existing three tools re-audited against this spec and re-run direct; the two DISTINCTIVE
   predictions (echoes; breathing≡memory) stated with numbers and search protocols.
4. **What would prove us wrong?** — §3: an order-unity or steady-inspiral scalar mode (G3 kill —
   binary-pulsar decay and GW170817 polarisation already exclude it: model DEAD, log it); chirp
   scale unreachable without inserting G (G2 kill); no memory (G4 — the "moved sea" picture
   fails); dispersion in band (G1).
5. **How will we know we're done?** — Dual verdict in a fresh `GOM06_VERDICT_DIRECT_<date>.md`
   with the coefficient ledger (96/5, κ, η — each DERIVED or OWED, no third state) and the two
   distinctive predictions carried as pre-registered numbers or explicitly dropped.

## 0. THE SEED (the spec is a poem — read it first)

> *The black hole, she is a big girl, but she don't like to smash head on. She is a big girl, but
> also a very good dancer, she approach gingerly, very nimble, the other black hole, he a bigger
> boy, but also he no like to just ram her, he must woo her, and so they circle, gently, closer
> and closer, faster and faster, and they pulse, make little mirror go chirp chirp, as the spation
> gears go in and out, in and out, like moving a sea as opposed to making waves. And then they
> kiss, and spin, and now he inside her, and they meld into one, and the pulse, she stop, but
> also, she go, forever.* — J.T.

**The thesis, flat:** a gravitational wave is not a ripple made *in* a medium (GR's h_μν through
spacetime) — it is **the medium itself being moved**. A near-incompressible sea carries shear
cleanly and leaks only a whisper of compression; and a moved sea **stays moved** (memory).

| Poem fragment | Mechanism (R0 vocabulary) | Gate |
|---|---|---|
| "circle… faster and faster" | two occlusion cores in a koppa-governed decaying orbit — no G, no M, only ϟᵢ = vᵢ²Rᵢ/c² | G2 |
| "gears go in and out" | displacement-field quadrupole breathing at 2×f_orb | G2 |
| "little mirror go chirp chirp" | f_GW(t), df/dt ∝ f^{11/3}ϟ_c^{5/3} | G2 |
| **"moving a sea, not making waves"** | near-incompressible lattice: compression frozen out → radiation = transverse shear = 2 tensor modes + scalar residual ~Δϟ/ϟ | G1, G3 |
| "kiss, spin, meld into one" | common-core formation at the closure floor (FLM06 self-boundary) = max-compression remnant, **no singularity** (E68) | merger |
| "the pulse, she stop" | ringdown QNMs of the merged core — with possible **echoes** off the closure floor | G5 |
| **"but also, she go, forever"** | the net lattice reconfiguration is a permanent strain offset — memory as PRIMARY | G4 |

**The honest tension to resolve, not assume:** E48 says transverse; the seed says bulk. They
reconcile only if the lattice is incompressible — an incompressible medium *responds* with
volume-preserving flow yet *radiates* only shear. G1/G3 must demonstrate this.

## RULES (in force throughout)

- **R0 Vocabulary sovereignty** — SDT primitives only; GR terms (⟦chirp mass⟧, ⟦ISCO⟧, ⟦h_μν⟧)
  only in instrument-output brackets.
- **R1′ Declared anchors (replaces the old sealed/ protocol — no `sealed/` directory exists, and
  the famous numbers cannot be unlearned; declare instead, GOM19-style).** Stated NOW, before any
  run: GW150914 — ⟦M_tot ≈ 65 M☉⟧ → ϟ_tot ≈ 96 km; sweep band ~35–250 Hz; ⟦chirp mass ≈ 30 M☉⟧;
  E_rad/E ≈ 4.6%; ringdown ⟦≈ 250 Hz⟧. GW170817: |c_GW−c|/c < 1e-15. All are
  **OBSERVED-through-GR-waveforms** (theory-laden — the extraction pipeline is the rival's;
  usable as comparison columns only, per the GOM19 contract). Every derived number is committed
  to `RUN_LOG.md` BEFORE its comparison line is computed.
- **R2 Parameter ledger** — every number DERIVED / MEASURED-INPUT / CALIBRATED(n) / OWED at first
  use. Target CALIBRATED(0). The bridge GM = c²ϟ converts a measured observable (LIGO measures a
  koppa, never weighs a mass) — MEASURED-INPUT, never fitted.
- **R3 Two-stream** — any CONFIRMED result recomputed independently (closed-form vs numerical
  orbit integration, agreement <1%).
- **R4 Honesty over success** — a cleanly-logged fired gate outranks a soft pass. If G3 honestly
  yields an order-unity scalar mode, log the kill: the mechanism is dead.
- **R5 No borrowed targets** — never import GR's 96/5, M_c, or h_μν as targets; forward from
  koppa + movement budget; check downstream; the 96/5, the G3 coefficient κ, and the G4
  coefficient η are **OWED until natively derived** — they appear in the ledger as OWED, and no
  gate may quietly consume them.

## 2. THE GATES (all unchecked; every prior "EXECUTED/DONE" claim demoted to route-to-attempt)

### G1 — Propagation speed & dispersion (CONVERGENCE, must hold)
Claim: the lattice's transverse shear mode propagates at exactly c, non-dispersively in band.
Route: relay advances one ℓ_P per t_P → single signal speed; show structurally why μ/ρ = c²
is not "we assumed c" (tie to the lattice EoS w₀ ≪ 1). Strong-field refinement (GOM05):
c_local = c(1−z) — the GW and its EM counterpart wade through the IDENTICAL z(r), predicting
equal Shapiro delay/lensing for both messengers (a clean co-propagation statement).
**Gate:** |c_GW−c|/c consistent with <1e-15 (GW170817 anchor); dispersion onset only at f ~ c/ℓ_P
(unobservable) → zero in band. **Risk:** circularity — state the non-circular step explicitly.

### G2 — The chirp from a LENGTH, no G, no M (the executable headline)
Claim: the whole inspiral is governed by ϟ_tot = Σϟᵢ and ϟ_c, with G and M absent from every
dynamical relation. Route: v² = c²ϟ/r ⟹ ω² = c²ϟ/r³; f_GW = 2f_orb; contact/⟦ISCO⟧ scale
r ≈ 6ϟ_tot ⟹ **f_GW = c/(6^{3/2}πϟ_tot)** — only c and a length. For ϟ_tot ≈ 96 km → ≈ 68 Hz
(inside the declared sweep band). Inspiral: df/dt ∝ f^{11/3}ϟ_c^{5/3} — the f^{11/3} FORM is the
deliverable; the leading coefficient (GR's 96/5) is **OWED** until derived from the rate the
orbiting occlusion sheds convergence-energy into shear.
**Gates (pre-registered):** frequency scale and track vs GW150914 within ±15% from c and ϟ alone;
cross-check c²ϟ_c/G recovers ⟦30 M☉⟧ ±15% (conversion, labeled). Tool: `gom06_chirp_from_koppa.cpp`
(re-audit against this spec — if it embeds old pass/fail prints keyed to the deleted layer,
patch and ADJ-log — then run direct).

### G3 — Polarisation: the kill gate
Danger stated plainly: the static SDT field is a scalar depth z = ϟ/r — a breathing mode is the
natural disaster, and binary-pulsar decay + GW170817 exclude any order-unity or steady-inspiral
scalar at <0.1%. Route-to-attempt (the June argument, to re-earn): the breathing channel IS the
monopole = total ϟ_tot; total displacement-load is conserved (a moving sea conserves volume) ⟹
no monopole radiation; momentum kills the dipole; leading radiated moment = quadrupole → two
tensor modes. Residual scalar = the merger-epoch CHANGE Δϟ_tot/ϟ_tot ≈ E_rad/E ≈ 4.6% —
transient, evading the steady-inspiral bounds.
**Gates:** (a) the conservation+multipole chain written with no step assumed (the incompressible
response, the monopole identification, the transient window); (b) the DISTINCTIVE prediction
carried as a number: a few-% breathing admixture confined to merger epoch and **equal to the
memory offset** (G4) — with the observational protocol named (≥5-detector merger-epoch
polarisation; LISA memory↔breathing correlation; PTA scalar overlap function). κ in ε = κ·Δϟ/ϟ:
OWED. **Fail = order-unity or steady scalar → model DEAD, logged.**

### G4 — Memory: "she stop, but also she go, forever"
Claim: a permanent strain offset remains — in SDT PRIMARY (a moved sea stays moved), not a
higher-order correction. Native handle (GOM05): memory = permanent change in the closure field —
Δh_mem = −Δz(detector) between the initial two-core and final one-core z-fields;
Δϟ_rad = ϟ_tot·(ΔM/M) is a radiated LENGTH (≈ 4.4 km for the GW150914 anchors), no G/M.
Structural band: Δh_mem = η·Δϟ_rad/R with η ∈ [0.2, 1] (geometry-bounded, stated BEFORE the
run; η's value is OWED). **Gates:** the derivation re-earned direct; the predicted magnitude
compared against GR's nonlinear memory (~few % of peak) as CONVERGENCE-or-DIVERGENCE with the
number stated; **the identity Δϟ_rad(G4) ≡ Δϟ_tot(G3) printed as the one-quantity correlation —
the unique SDT prediction of this investigation.** Tool: `gom06_memory.cpp` (re-audit, run).

### G5 — Ringdown & echoes (the SDT≠GR fork; formerly D8)
Route: QNMs of a max-compression core; ringdown frequency CONVERGENT with Kerr (⟦≈250 Hz⟧ band);
the DISTINCTIVE piece is **echoes off the closure floor**: no horizon + FLM06 self-boundary wall
⟹ Δt_echo ∝ ϟ_f·ln(ϟ_f/ℓ_P) ≈ **58 ms** for GW150914-class remnants. Pre-registration duty:
the echo claim is contested observationally (past echo searches are disputed); the gate here is
to re-derive Δt and its ϟ_f-scaling law direct, and state the stacking protocol (echo delay
scales LINEARLY-times-log with remnant koppa — a per-event prediction rival templates lack).
Tool: `gom06_echoes.cpp` (re-audit, run). Cross-link: the remnant-spin fork (a* = 1/√2 attractor
vs NR 0.6864) lives in **GOM19 P1/P2**, not here — cite, don't duplicate.

## 3. FALSIFICATION TABLE

| # | Test | SDT prediction | If it fails |
|---|---|---|---|
| F1 | GW speed/dispersion | = c to 1e-15; zero dispersion in band | E48 wrong; lattice not the light medium |
| F2 | chirp scale from ϟ only | ≈68 Hz from 96 km, ±15%; f^{11/3} track | koppa bridge fails radiatively — G2 kill |
| F3 | polarisation | 2 tensor + transient scalar ≈ Δϟ/ϟ only | order-unity/steady scalar ⟹ **model dead** |
| F4 | memory | permanent Δh = η·Δϟ_rad/R; ≡ the G3 transient | no memory ⟹ "make waves" wins over "move sea" |
| F5 | ringdown structure | echoes, Δt ≈ 58 ms scaling as ϟ_f·ln(ϟ_f/ℓ_P) | pure Kerr, no echoes ⟹ E68 unsupported (fork lost, recorded — not a model kill) |

## 4. SUCCESS CRITERIA
- **PASS (A/B):** G1+G2 from c and ϟ alone (±15%, no G/M) AND G3's kill-condition avoided by a
  fully-written conservation chain.
- **QUALIFIED (C):** form-level G2 + structural G3/G4 with the three coefficients OWED (this is
  the ceiling until the dynamic depth-closure extension is derived — say so).
- **PENDING (D):** mechanism dimensionally closed; radiative coefficients absent.
- **FAIL (F):** F2 or F3 fires — logged as the mechanism's death, no softening.

## 5. DEPENDENCIES
Upstream: bridge (GM=c²ϟ) · FLM06 (self-boundary/closure floor) · GOM05 (variable closure —
c_local, the memory handle) · lattice EoS (w₀ — the incompressibility G3 leans on; if that
dependency is unearned, G3's verdict says so) · Laws III/IV/V · E48, E68.
Data/anchors: declared in R1′ (theory-laden, comparison only); GWTC table = MUST_FETCH **F10**
(shared with GOM19). Downstream: GOM19 (merger ledger — consumes G2's chirp-as-length and the
remnant fork), E67 (NS mergers), the echo search protocol.

## 6. DELIVERABLES
Fresh `RUN_LOG.md` (commitments first) · re-audited `gom06_chirp_from_koppa.cpp`,
`gom06_echoes.cpp`, `gom06_memory.cpp` + teed `gom06_*_rerun_<date>.txt` · derivation notes
re-earned as `GOM06_G3_POLARISATION_<date>.md`, `GOM06_G4_MEMORY_<date>.md`,
`GOM06_G5_ECHOES_<date>.md` (fresh files — the deleted June docs are NOT restored, they are
replaced by direct work or not at all) · `GOM06_VERDICT_DIRECT_<date>.md` (dual verdict +
coefficient ledger + the two distinctive predictions as numbers or as dropped).

## 7. FINAL INSTRUCTION
One question, split five ways: **is a gravitational wave the medium being moved, not a wave made
in it?** Show the chirp is a length; show incompressibility forces shear and quantify the
whisper; show the sea stays moved and that the whisper and the staying-moved are ONE quantity;
show the floor echoes. Forward from c and ϟ; never insert G; every borrowed coefficient flagged
OWED. Open it honestly or report the gate that fires.

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM06 (2026-07-24 spec)
- Prompt completion target: [A|B|C]
- Physics class ceiling acknowledged: C until the 96/5 / κ / η ledger clears
- CALIBRATED budget: 0 · OWED ledger: 96/5 (G2), κ (G3), η (G4)
- Declared anchors (R1′): GW150914 ϟ_tot≈96 km, band 35–250 Hz, ⟦M_c≈30 M☉⟧, E_rad/E≈4.6%,
  ⟦ringdown≈250 Hz⟧; GW170817 speed bound — all OBSERVED-through-GR-waveforms, comparison only
- Gates: G1 1e-15/zero-dispersion · G2 ±15% scale+track · G3 kill-condition chain complete ·
  G4 identity Δϟ(G3)≡Δϟ(G4) printed · G5 Δt law re-derived + protocol stated
- Forbidden: borrowed 96/5 as target; softening F2/F3; restoring deleted June docs as evidence;
  agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| tool embeds deleted-layer prints | patch prints to this spec's labels, ADJ-log | rebuild tool minimal | trusting old banners |
| G2 outside ±15% | check ϟ_tot input chain (root-2) | G2 kill, logged | inserting G |
| G3 chain gaps at incompressibility | mark the w₀ dependency OWED, verdict ceiling D | — | assuming the modulus |
| echo Δt derivation shifts from 58 ms | report the new number with the scaling law | — | anchoring to 58 because it was written before |

---

*GOM06 · upgraded 2026-07-24 · move the sea, don't make waves; the whisper and the staying-moved
are one quantity, and that identity — not the chirp — is what GR cannot say.*

## B09 eccentric-binary closure freeze (2026-08-14)

The Hulse–Taylor route consumes raw timing geometry, not a body-source mass
parameter:

```text
timing geometry/movement
  -> koppa_total and eta from SDT orbital relations
  -> N_baryons=koppa_body/koppa_per_baryon
  -> Law-IV resistance of each body
  -> time-dependent resistance quadrupole Q_ij(t)
  -> relay shear flux integral
  -> P_shear and orbital-resistance loss
  -> predicted dP_b/dt
  -> observed intrinsic dP_b/dt comparison
```

The raw ledger must preserve the published orbital period, eccentricity,
projected light-time geometry, periastron timing, inclination constraints and
kinematic correction with source, units and uncertainty. Symbols or aliases
equivalent to source `G`, source `M`, `GM`, `mu`, or `u=GM` are forbidden from
the forward path. A conversion may be printed only after the prediction.

Frozen gates:

1. Constant total resistance gives zero monopole radiation and uniform
   centre-of-resistance motion gives zero dipole radiation to relative
   numerical leakage `<1e-10`.
2. The shear coefficient is the output of the angular/tensor flux integral;
   it may not be inserted from a rival quadrupole formula. Doubling orbital and
   angular resolution changes it by `<0.5%`.
3. The eccentricity enhancement is obtained by integrating the same orbit
   solver at `e={0,0.1,...,0.9}`. The `e=0` normalization is exactly one to
   `<1e-6`, and the Hulse–Taylor value is converged to `<0.5%`.
4. Two independent paths—time-domain resistance loss and frequency-domain
   quadrupole power—agree within `1%`.
5. The complete prediction is frozen before the intrinsic observed
   `dP_b/dt` is loaded. B09 advances at a residual `<=1%`; otherwise the
   coefficient, measured residual and failed premise remain explicit.
6. A second eccentric timed binary is a whole-system control and must preserve
   the sign and uncertainty overlap without any system-specific coefficient.
