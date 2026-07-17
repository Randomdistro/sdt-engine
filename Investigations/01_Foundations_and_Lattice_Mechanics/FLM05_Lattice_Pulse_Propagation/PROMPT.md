# FLM05: Lattice Pulse Propagation — The Non-Contact Mechanism

> **Author:** J. C. Harvey, Melbourne. **Status:** RICH-SPEC · **§K-DEEPENED 2026-07-13** (300% rule, HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K.
> **Engine:** `#include <sdt/laws.hpp>`, `<sdt/lattice_structure.hpp>` (FLM08) only. **Propose-only** on canon flags.
> **Run:** Pre-commit per Part in `RUN_LOG.md`; four-root sort (§⑨.E) on every FAIL.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **The tick-by-tick relay mechanism that MAKES 1/r² from ~10²⁴ discrete Planck-shell handoffs** (CQ09b showed the smooth field v(r)=cα√(a₀/r) is algebra, not mechanism), AND the gap width g₀ (sphere/gap fraction of ℓ_P) — currently under-determined (Part V).
2. **Why does it matter?** — This is the substrate's operating manual: gap = medium, matter = forced contact, gravity = gap reasserting, light = transverse gap. Everything downstream (occlusion, redshift, light) inherits it.
3. **How will we find out?** — Parts I–V (§structure), each gated; geometry (1/r² from d=3) is earned, the g₀ determination and the redshift form are the open/flagged pieces.
4. **What would prove us wrong?** — §⑧: if 1/r² needs anything beyond d=3 solid angle; if g₀ can't be fixed from f; if the rigid-sphere premise contradicts the superfluid substrate (see PREMISE FLAG).
5. **How will we know we're done?** — Dual verdict; the three canon flags below resolved or logged; g₀ determination graded DERIVED/OPEN.

> ### ⚠ THREE FLAGS (fixed in-prompt this pass; verify on run)
> **(A) "charge radius" → boundary radius.** Old §DEEP-STRUCTURE said *"Its surface IS the charge radius."*
> **Corrected:** the contact-zone surface is the particle's **boundary/displacement radius** (`laws.hpp:145`
> already: "'charge radius' is the literature's obfuscation"). No charge substance (handed redirection).
> **(B) Redshift is ENDPOINT, non-compounding (CR07).** Old Part IV said *"Accumulated stretch = z"* (photon
> cycles stretching *in transit*). **This is the transit-narration bug the Interchange Sweep struck.** SDT
> redshift is **emission depth z = ϟ/r** (Depth-Closure), endpoint counting — octaves telescope, they do NOT
> accumulate per-gap along the path. Reconcile the stray **z = 1/ϟ²** form against canonical **z = ϟ/r**
> (they are not the same; one is wrong or mis-normalised — resolve, don't carry both).
> **(C) PREMISE TENSION — rigid spheres vs superfluid substrate.** FLM05 treats spations as *inert,
> incompressible, indeformable* Planck spheres (frozen glass). The **substrate-superfluid upgrade
> (2026-06-25)** holds the substrate is a **reconfigurable lightspeed superfluid** — CRN = *transient*
> structure, bond-switch = flow, particles = quantised vortices — **not a frozen glass; don't quench.** And
> **FLM10** found periodic FCC is anisotropic (wrong) vs amorphous-icosahedral (isotropic, frustrated, gap
> 0.103). FLM05's "12-around-1 recursive infinite tessellation" is exactly FLM10's packing fork. **Reconcile:
> is the inert-sphere gap model an effective/rigid-limit picture of the superfluid, or superseded by it?**

## The mechanism (earned core — keep)

Gap `g₀ = d − ℓ_P` between incompressible spheres is the medium; relay ε crosses at c. Displacement δ compresses the gap (0 ≤ δ ≤ g₀). **Mode A** (δ<g₀) = gravity (asymmetric relay, Δv/c≈δ/g₀); **Mode B** (δ=g₀, contact) = matter. From the contact zone outward the gap reopens; flux over 4πn² shells ⟹ **1/r² is FORCED by d=3 geometry, not dynamics.** Transverse gap perturbation = light (cannot convert to longitudinal); longitudinal = gravity.

## Structure (Parts I–V, gated)

- **I — One tick:** gap geometry, displacement mechanics, Modes A/B. *Metric:* δ hard-bounded [0,g₀]; contact=matter.
- **II — Shell-by-shell:** δ_n = F₀/(4πn²) → 1/r²; g(r) profile; test at R_p, r_e, a₀. *Metric:* g→g₀ at ∞, g→0 at R_matter.
- **III — Rotorpause:** r_rp/(a₀−r_rp)=√(m_p/m_e)=42.85 → r_rp=0.9772 a₀; flail-tail θ≈√(m_e/m_p)≈1.34°. *(Cross-ref the electron domain; movement-only.)*
- **IV — Pulse as light:** transverse survives (orthogonality), longitudinal absorbed. **Redshift per FLAG (B): z=ϟ/r endpoint, NOT accumulated transit stretch.**
- **V — Gap width g₀:** the open. c=ℓ_P/t_P with d=ℓ_P gives g₀=0 (problem). Resolution: ℓ_P = lattice constant (sphere fraction f_sphere < 1); gap = ℓ_P(1−f_sphere). *Does f = P_eff/P_conv = 2.125×10⁻¹⁷ fix f_gap?* — **the real Part-V question, currently a "relates to," not a derivation.**

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| FLM08 lattice_structure.hpp | Engine | relay geometry | ✔ |
| **FLM10 per-spation solver (FCC vs icosahedral, gap 0.103)** | Investigations/01 | **packing fork — FLAG C** | ⚠ dep |
| substrate-superfluid upgrade (2026-06-25) | project note | **premise reconciliation — FLAG C** | ⚠ dep |
| f = P_eff/P_conv = 2.125e-17 | `laws.hpp` (EMC01) | Part V g₀ constraint | ✔ |
| CR07 non-compounding redshift | Investigations/cosmology | **FLAG B** (z=ϟ/r endpoint) | ✔ |
| z = ϟ/r Depth-Closure | GOM/Depth-Closure paper | canonical redshift form | ✔ |
| CQ09b smooth field v(r)=cα√(a₀/r) | prior | the algebra FLM05 must mechanise | ✔ |

## ④ Strategy — routes/parts with pre-committed metrics
Run Parts I→II (earned geometry, verify 1/r² at H scales), then the two open/flagged pieces:
**Route V (g₀ from f):** does f constrain f_gap to a definite value, or is "f relates to f_gap" hand-waving? *Metric:* g₀ pinned to <10% from f, or declare OPEN.
**Route C (premise reconciliation):** run the rigid-sphere gap model AND the superfluid picture on the isotropy test; do they agree in the rigid limit? *Metric:* FLM05 gap model = superfluid effective limit, or one is superseded (name which).

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | 1/r² from d=3 solid angle alone | root-1 (needs extra assumption) |
| T2 | g₀ pinned from f | root-3 (Part V is "relates to", not derived) → OPEN |
| T3 | redshift z=ϟ/r endpoint, no transit accumulation | root-4 (CR07 contraband if compounding kept) |
| T4 | rigid-sphere = superfluid rigid limit | root-2 (premise superseded by FLM10/superfluid) |
| T5 | rotorpause 0.9772 a₀ independent of fitted inputs | root-1 |

## ⑨.E Four-root sort
root-1 claim false · root-2 dependency (FLM10 packing, superfluid substrate) · root-3 prompt (g₀ under-determined) · root-4 contraband (compounding redshift; charge-substance). The g₀ gap is a **named OPEN closure** (§D), not a kill. FLAG C is root-2 — CLOSE by reconciling, don't amputate FLM05.

## Brainstorm — overlooked/newly-discovered factors
- **The superfluid upgrade is the biggest overlooked factor.** FLM05 predates it. "Inert incompressible spheres" may be the *rigid-limit cartoon* of a reconfigurable superfluid — useful pedagogically, but the real substrate flows (bond-switch). Say which FLM05 claims survive the upgrade (1/r²=d=3 does; "spheres never deform" may not).
- **Redshift form.** z=1/ϟ² (Part IV) vs z=ϟ/r (canon) must be reconciled — a genuine inconsistency, not cosmetic. Depth-Closure (z=ϟ/r at emission) is the earned form.
- **1/r² = d=3 is the crown jewel** — it's geometry not dynamics, survives every premise change. Lead with it.
- **Transverse-survives-longitudinal-absorbed** is the light/gravity split; check against FLM09 (light = transient bond-switch wave) — same phenomenon, two descriptions; reconcile.
- **f → f_gap** would be a beautiful closure (the transfer function fixing the lattice geometry) — but only if it's a derivation, not a coincidence of magnitude.

## ⑤ Success / ⑥ Outputs
Class A: 1/r² + rotorpause + light-split clean, g₀ pinned from f, three flags resolved, superfluid reconciled. **Honest floor:** geometry earned, g₀ OPEN, redshift+charge-radius+premise flags logged. Outputs: `RUN_LOG.md`, `flm05_lattice_pulse.cpp`, `flm05_torus_derives_mass.cpp`, `FLM05_DERIVATION.md`, `FLM05_VERDICT.md`, CANON_FLAGS/STACK entries.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — FLM05 (§K-deepened)
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|OPEN]
- CALIBRATED budget: 0 (g₀ from f, not fitted)
- Parts this session: I,II (geometry) · V (g₀ from f) · C (superfluid reconcile)
- Flags to resolve: (A) charge→boundary radius (B) redshift endpoint z=ϟ/r (C) rigid vs superfluid
- Verify on file: FLM10 packing result, substrate-superfluid note, f value
- Forbidden: "charge radius"; accumulated transit redshift; asserting spheres never deform if superfluid says otherwise
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| g₀ won't pin from f | declare OPEN (Part V) | ship geometry-only | claim f fixes g₀ by hand-wave |
| redshift wants transit accumulation | enforce CR07 endpoint | flag & strike (root-4) | keep compounding z |
| rigid-sphere ≠ superfluid | reconcile as rigid limit / name superseded | OPEN premise (root-2) | ignore the upgrade |
| "charge radius" appears | boundary/displacement radius | — | say charge radius |

**Disallowed:** post-hoc tolerance widening · "charge radius" · compounding/transit redshift · asserting incompressible spheres against the superfluid upgrade without reconciliation.

---

*FLM05 · §K-deepened 2026-07-13 · 1/r²=d=3 is the earned crown; three flags fixed/logged (charge→boundary radius, redshift endpoint z=ϟ/r not transit-accumulated, rigid-sphere vs reconfigurable-superfluid); g₀-from-f is the live open.*
