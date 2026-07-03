# QM07 — Spin & Stern–Gerlach from Handedness

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces. No μ_B / Bohr magnetons / imported moment units — use SDT-native yardsticks.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
> **Domain:** Quantum Foundations & Measurement (vortex handedness, differential occlusion, no ψ).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Can "spin-½" — its strict **two-valuedness**, a magnetic moment, and the
   **two-spot Stern–Gerlach split with no middle spot** — be reproduced as a vortex's intrinsic
   circulation handedness (EMC03) interacting with a swirl gradient via **differential occlusion**,
   *without* a spin operator, a Pauli algebra, or a Hilbert-space `s=½`? The two-valuedness is the
   strong native claim (handedness is binary); the **g-factor is the weak claim and is currently
   OPEN** — see the firewall below.
2. **Why does it matter?** — Spin is the QM degree of freedom with "no classical picture". A handedness
   picture removes that mystery and ties spin to SDT magnetism (PM-series). It also supplies QM05 the
   shared contra-handedness of an entangled pair. Getting the g-factor provenance *honest* matters more
   than getting a number: a fabricated engine citation poisons the audit.
3. **How will we find out?** — Four phases (§④). Phase 1 establishes binary circulation; Phase 3 is the
   discriminator (two spots, no middle) from differential occlusion; Phase 2 (the moment / g-factor) is
   explicitly flagged OPEN, not forced.
4. **What would prove us wrong?** — §⑧, three falsifiers with numeric triggers — a middle spot;
   sequential-SG that misses cos²(θ/2); a g-factor that can only be matched by importing a number.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

> **⚠️ Engine-fact correction (flagged for Harvey, 2026-06-29).** A prior draft cited "g≈2 from (W+1),
> the proton g=4=W+1 line, Law VI" as an engine result. **`laws.hpp` contains no magnetic g-factor from
> W+1.** What it actually contains: `winding::g_proton = R_p·m_p·c/ℏ ≈ 4` and `winding::g_electron =
> r_e·m_e·c/ℏ = α` are a **wake-to-quantum *ratio*** (explicitly class F, definitional for the electron),
> *not* a magnetic moment; `W+1 = 4` is the proton **boundary-radius** coefficient (`R_p = (W+1)ℏ/m_p c`);
> `3(W+1) = 12` is the **traction** ratio. The real electron magnetic g-factor (2.00232) is derived in
> **benchmark B17** via the Schwinger-style `g = 2(1 + α/2π)` — **not** via any W+1 route. This prompt
> removes the fabricated citation and relabels the g-from-(W+1) idea as OPEN/conjecture.

## Question

What is "spin"? Standard QM makes it an abstract internal two-state degree of freedom with no
classical picture. SDT already has a concrete candidate: a vortex has an **intrinsic handedness /
circulation** (the EMC03 redirection sign, [[project_cq47_repulsion_inverse]]). Can "spin-½" — its
strict **two-valuedness**, the g ≈ 2 magnetic moment, and the **two-spot Stern–Gerlach split** — be
reproduced as the vortex circulation interacting with a swirl/field gradient via **differential
occlusion**, tying directly to SDT magnetism (PM-series)? And can the famous sequential-SG
correlations come out without a spin operator algebra?

## SDT mechanism & hypotheses

The vortex spins one way or the other — its convergence circulation is left- or right-handed, the
same two handednesses that are "+e/−e" in [[project_foundational_ontology_influx_monopole]]. In a
magnetic gradient (a spatial swirl gradient of the relay field), a handed vortex experiences
**differential occlusion**: one side of its wake is occluded more than the other, producing a net
sideways push whose sign is set by handedness. Two handednesses ⇒ two deflections ⇒ two spots. The
two-valuedness is **topological** (circulation sign is binary), not a Hilbert-space axiom.

- **H1 (spin = circulation handedness):** intrinsic angular content is the vortex's own circulation;
  two values because handedness is binary (EMC03) — no `s=½` postulate. **This is the strong claim.**
- **H2 (g-factor — OPEN/conjecture, NOT an engine result):** the moment-to-circulation ratio is
  *conjectured* to give g≈2 from vortex topology. **There is no g-factor-from-(W+1) in `laws.hpp`** —
  the `winding::g_proton ≈ 4` / `g_electron = α` symbols are a wake-to-quantum *ratio* (class F,
  definitional), and `W+1=4` is the proton **boundary-radius** coefficient, *not* a magnetic moment;
  do not cite them as a g-factor. The **measured** electron magnetic g = 2.00232 is reproduced in
  **benchmark B17** via `g = 2(1 + α/2π)` (Schwinger route), independent of any W+1 line. Phase 2
  must either build a genuinely native moment-from-occlusion derivation or mark the g-factor **OPEN**
  and defer to B17 — it may **not** claim a W+1 g-factor. (Anomalous a_e: also OPEN.)
- **H3 (SG two-spot = differential occlusion):** in a swirl gradient the handed wake gets a
  net transverse push ∝ gradient·handedness ⇒ exactly two beams; sequential-SG cos²(θ/2)
  correlations from the QM04 residence count over re-projected handedness. **This is the discriminator.**

## Strategy

**Phase 1 — Handedness as the spin variable.** *Goal:* establish binary circulation. *Method:* EMC03
handedness on a single vortex; show only two stable circulation senses (PPT01 equilibrium).
*Success:* exactly two values, no continuum — two-valuedness native.

**Phase 2 — Magnetic moment & g *(g-factor is OPEN — do not force it)*.** *Goal:* a **native**
moment-to-circulation ratio in SDT-native units (electron-wake / koppa yardsticks, **no μ_B**).
*Method:* moment = circulation × occlusion area (Law III/VI topology), expressed without borrowed
magneton units. *Success (the honest target):* the *binary* moment (two signs, equal magnitude) is
native; the **numerical g ≈ 2 is flagged OPEN** — the engine's measured g=2.00232 lives in B17
(`g = 2(1+α/2π)`), and there is **no W+1 g-factor** to cite. A genuine native derivation that lands
g within ~1% would be a bonus (Class C if it leans on one flagged factor); claiming g from (W+1) is
forbidden. Anomalous a_e: OPEN.

**Phase 3 — Stern–Gerlach split.** *Goal:* two spots. *Method:* propagate a handed vortex+wake
through a swirl gradient; differential occlusion gives transverse push. *Success:* exactly two
deflections, equal/opposite, magnitude ∝ gradient; **no middle spot**.

**Phase 4 — Sequential SG.** *Goal:* cos²(θ/2). *Method:* re-project handedness onto a second axis;
residence count (QM04). *Success:* transmission cos²(θ/2) reproduced to <2% over swept relative angle θ.

## Success criteria (canonical A–F) + anti-tautology gate

- **PASS (A — NATIVE):** two-valuedness (binary circulation), the two-spot SG (no middle), and
  cos²(θ/2) sequential correlations all native, zero fitted params. **The g-factor is NOT required for
  A** — it is OPEN; the strong claim is the two-spot discriminator, not the number.
- **QUALIFIED (C — CONVERGENCE):** picture reproduced but the cos²(θ/2) coefficient or a native moment
  derivation borrows one flagged factor. **Anti-tautology gate: any g-factor obtained by citing the
  W+1 line (`g_proton=4`) or by importing μ_B is invalid — that is a fabricated/borrowed result; the
  real g lives in B17.**
- **PENDING (D):** handedness→deflection shown qualitatively but the moment/correlation only heuristic.
- **FAIL (F):** needs a spin operator / Pauli algebra to get two spots. Report; handedness picture failed.

## Falsification tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction | What kills it (numeric) |
|---|------|----------------|-------------------------|
| T1 | two-valued, **no middle** | SG gives exactly two spots, equal & opposite, magnitude ∝ gradient | if a middle (zero-deflection) spot appears, or a continuum of deflections, spin is not binary circulation → F |
| T2 | moment is binary & native (g OPEN) | two equal-and-opposite moment signs from circulation·occlusion in SDT-native units | if the *number* g can only be matched by citing the W+1 line or importing μ_B, the g-claim is fabricated/borrowed → invalid (the binary moment may still pass; g stays OPEN, see B17) |
| T3 | sequential cos²(θ/2) | transmission cos²(θ/2), RMS <2% over swept θ | if RMS >2% or the curve is not cos²(θ/2), the handedness re-projection picture is wrong |

## Dependencies

**Upstream:** EMC03 (handedness = inverse-of-convergence redirection — the spin variable), PPT06 (wake/occlusion), PPT01 (equilibrium).
**Engine:** **benchmark B17** (`g = 2(1+α/2π)` — the *real* electron g-factor result; Phase 2 defers
the number here), `winding::` (the W+1 = boundary-radius coefficient and the g_proton wake-RATIO — NOT
a magnetic g-factor; do not cite as one).
**Downstream:** QM05 (entangled pair = shared contra-handedness), QM06 (fine structure / l-degeneracy).
**Related:** PM01 (magnetism — SG gradient = swirl gradient; same differential-occlusion mechanism), [[project_cq47_repulsion_inverse]], [[project_foundational_ontology_influx_monopole]] (handedness = redirection sign, e = unit-bridge).

## Questions This Opens *(generative — log new ones in `QM07_VERDICT.md`)*

1. **Does any native route give g ≈ 2 *honestly*?** B17's `2(1+α/2π)` is Schwinger-style, not a vortex
   derivation. Is there an SDT-native moment-from-occlusion calculation that lands near 2 without
   importing μ_B or the W+1 line? If not, g stays a genuine OPEN — say so.
2. **Why is the SG split exactly two, not three?** Differential occlusion of a binary handedness gives
   two; a classical magnetic dipole would smear. Is the "no middle spot" a *prediction* the occlusion
   model makes that a classical-moment model cannot — a real SDT win?
3. **Is the cos²(θ/2) the *same* square as QM04's residence count?** If sequential-SG transmission is
   the QM04 energy-density residence over re-projected handedness, the half-angle factor should fall
   out of geometry, not be fitted — does it?
4. **Does handedness re-projection have a tick cost?** A real re-projection between SG axes is a
   mechanical relay event; does it predict a measurable timing or loss not present in the QM operator
   picture?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — QM07
- Prompt completion target: [A|B|C|D]  (A does NOT require the g-number; g is OPEN)
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the native chain (g-factor is OPEN, not a budgeted fit)
- Engine namespaces used: EMC03 handedness, PPT06 occlusion, PPT01 equilibrium; B17 for the g *number* only — NO ψ, NO μ_B, NO W+1 g-factor citation, NO atomic:: in the native chain
- Phase thresholds (committed before run): P1 exactly two circulation senses · P2 binary moment native (g number OPEN → B17) · P3 two spots, no middle, ∝ gradient · P4 cos²(θ/2) RMS <2%
- Forbidden retroactive changes: cite g from (W+1) / g_proton=4; import μ_B; widen tolerances; plug; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| P1 more than two circulation senses survive | re-check PPT01 equilibrium (binary handedness) | **KILL** the binary-spin claim | force two by hand |
| P2 no native g, only B17's Schwinger value | mark g **OPEN**, defer the number to B17 | **OPEN** honestly — A still possible via P1/P3 | cite g from (W+1) or import μ_B |
| P3 a middle spot appears | re-derive differential occlusion (handedness sign → push sign) | **KILL** the two-spot mechanism | suppress the middle spot by hand |
| P4 cos²(θ/2) RMS >2% | re-check the QM04 residence count over re-projected handedness | **OPEN** the sequential-SG link | plug the cos²(θ/2) |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |

### Allowed adjustments

- Finer numerics (angle sweep, sample count); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · g-factor cited from the W+1 line / `g_proton=4` · μ_B or borrowed
  magneton units · `atomic::`/GM/G in the native chain · a spin operator / Pauli algebra to force two spots.

---

*QM07 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
