# FLM13 — The Koppa Route to the Action (ℏ)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
>
> **Sibling of** FLM11 (ruler count) and **FLM12 (The Mass Mechanism)**. This one asks the last derivation basis
> question of the classical sector: once the koppa ladder gives length (koppa from `g`/orbit), `c` (Mercury's
> precession), and α (off the list via PPT02/APS05) — **can koppa also reach the quantum of action, ℏ, or is ℏ
> the one irreducible seat?** Its main result — `{ℏ, m_e, m_p}` collapse to **one mass/action seat** — hands
> that seat directly to **FLM12**, whose job is what the seat *is*. FLM13 fixes ℏ's ROLE; FLM12 owns the mass.

---

## §0 Anti-creep protocol (R0–R5)

- **R0 — declared dependencies:** `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables in their measured units. The `sdt::laws::measured` derivation basis is the only external fact source. **This investigation's target is to REMOVE ℏ from that set — so ℏ may not appear in any extraction path (delete-test discipline).**
- **R1 — Prohibited:** wavefunctions, ψ, operators, Hilbert space, quantised action *asserted* (the quantisation must be *mechanical* — Onsager–Feynman circulation, not a postulate), quarks/gluons, dark sector, ΛCDM, wave–particle duality.
- **R2 — No charge-as-substance:** `e` is a unit-bridge; charge is handed redirection. No "charge radius."
- **R3 — Native yardsticks only:** koppa `ϟ = R/k²`, `k = c/v`, winding `W`, circulation `v_T/v_P` (Law V). Never μ_B / magnetons.
- **R4 — No G/M/GM in the chain.** `c` is sourced from Mercury's precession (`c = k_Sun·v_surface`, GOM04), never from `GM`.
- **R5 — Value honesty (the hinge of this whole prompt):** distinguish **ROLE** (what ℏ *is* mechanically) from **VALUE** (deriving `1.0546×10⁻³⁴` without ℏ in the inputs). A relation that is an **exact identity** in ℏ (e.g. `ℏ = r_e·m_e·c/α` when `r_e ≡ αℏ/m_e c`) derives the ROLE, **not** the VALUE. Do not present a tautology as an extraction. If every path routes through an ℏ-encoding quantity, the verdict is **ROLE-only / OPEN**, not PASS.

---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether the quantum of action ℏ is an *independent* fundamental, or the **circulation quantum of the W=1 vortex** — the bottom rung of the koppa ladder — and if so whether its *value* can be read off the ladder without ℏ ever entering the inputs.
2. **Why does it matter?** — It is the **last classical-sector seat**. Length (koppa from `g`), `c` (Mercury precession), and α (PPT02/APS05) are already off the derivation basis. If ℏ collapses into the mass seat, the residual derivation basis is `{one mass/action anchor (→ FLM12), α (dimensionless), k_B, T_CMB}` — the theory's irreducible core, made explicit.
3. **How will we find out?** — (P1) express ℏ as the W=1 rung circulation and prove the Onsager–Feynman identity mechanically; (P2) delete-test every extraction path for hidden ℏ; (P3) prove the ℏ↔m_e degeneracy and collapse `{ℏ,m_e,m_p}`→one seat (handed to FLM12); (P4) hunt an **ℏ-free (non-atomic) koppa path** to the action.
4. **What would prove us wrong?** — §⑧: a "value derivation" that is secretly an identity (ℏ on both sides); an ℏ-free path that on audit still routes through atomic spectroscopy; or a claim that both ℏ *and* m_e are independently derived (violates the one-mass-seat count).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). The strong core is **(a)** the mechanical Onsager–Feynman ROLE and **(b)** a definite yes/no on an ℏ-free VALUE path.

---

## 1. Executive Summary

The koppa ladder — `v = (c/ϟ)√(R/r)`, `zϟ² = 1`, `ϟ = R/k²` — runs from the proton (k=0.5464) through the
hydrogen ground state (**k=137.036=1/α**, koppa = r_e) to the Sun (**k=686.3**, koppa=1477 m) to the Earth
(koppa=4.43 mm) on **one kinematic law with no ℏ in it.** ℏ enters at exactly one place: it fixes the *absolute
atomic scale* of the ladder's bottom rung. The claim of FLM13 is that **ℏ is the Onsager–Feynman circulation
quantum of the W=1 vortex** — `ℏ = m_e·κ/2π` with `κ = h/m_e` the quantised circulation — equivalently the
angular momentum of the fundamental rung, `ℏ = m_e·(αc)·a₀ = r_e·m_e·c/α`. **We expect:** the **ROLE** derives
cleanly and natively (ℏ *is* the rung's action), and the mass-domain derivation basis `{ℏ, m_e, m_p}` **collapses to a
single seat** (fix one, the geometry hands you the rest) — which FLM12 then interprets. We do **not** expect the
**VALUE** `1.0546×10⁻³⁴` to fall out ℏ-free: unlike α (a dimensionless ratio, extractable from a pure spectral
ratio — APS05 Route B), ℏ is a *dimensionful action* entangled in every atomic length, so the honest target is
**one native mass/action seat, not zero.** A clean ℏ-free (macroscopic) path would be a genuine surprise — and
P4 goes looking for it.

---

## 2. Physical Context

**The ladder (search-confirmed, `Papers/an_argument_for_koppa.md`, `laws.hpp` bridge namespace, GOM02 15/15 PASS):**

| system | k = c/v | koppa ϟ = R/k² | note |
|---|---|---|---|
| proton surface | 0.5464 | (superluminal) | `ϟ_H = 0.5464` — invariant across **126 ionisation events**, 21 elements |
| **hydrogen ground** | **137.036 = 1/α** | **r_e = 2.818×10⁻¹⁵ m** | the rung ℏ anchors |
| Sun | 686.3 | 1477 m | from Mercury precession, no G/M |
| Earth | 37,905 | 4.43×10⁻³ m | matches the barometer koppa |
| Moon | 178,448 | 5.46×10⁻⁵ m | — |

`c` itself is an **output**: GOM04 gives `c = k_Sun·v_surface = 299,795,136 m/s` (+0.0009%) from Mercury's
precession alone. α is **off the derivation basis** two ways: PPT02 seat-closure (`α=1/k`, `k=c/√(2E_ion/m_e)`,
137.0725) and APS05 (Route A virial `α=√(2E_ion/m_e c²)`; **Route B pure ratio `α²=16Δν_2P/cR∞`, no m_e/e/h**).

**Where ℏ lives.** The ladder is scale-free (ratios `k`, `ϟ`). ℏ sets the one absolute atomic length:
`a₀ = ℏ/(m_e c α)`, `r_e = α²a₀ = αℏ/(m_e c) = ϟ_H`-boundary. So **ℏ is the rung's absolute size** — and the
rung's *motion* at that size is the electron circulating at `v=αc`, angular momentum `m_e·αc·a₀ = ℏ`. That is the
Bohr quantisation, read here **not** as a postulate but as the **superfluid circulation quantum** of the W=1
vortex (substrate = reconfigurable superfluid; particles = quantised vortices; OP-2 = Onsager–Feynman + knot).

**Key variables.** circulation `κ = ∮v·dl` (quantised, `= n·h/m`); W=1 vortex (electron unknot); rung radius a₀,
c-boundary r_e; `ϟ_H = 0.5464` (proton kinematic ratio); the mass seat `m` (m_e or m_p, tied by W=3 geometry — see FLM12).

---

## 3. Theoretical Framework

**The ROLE (native, expected to derive).** In a superfluid the circulation is quantised: `∮v·dl = n·h/m`.
The fundamental W=1 vortex carries one quantum, `κ = h/m_e = 2πℏ/m_e`, so
```
ℏ = m_e·κ / 2π                      (Onsager–Feynman — mechanical, not postulated)
   = m_e·(αc)·a₀                    (the W=1 rung's angular momentum, v=αc at R=a₀)
   = r_e·m_e·c / α                  (r_e = the rung's c-boundary = koppa of hydrogen)
```
All three are the same statement: **ℏ is the action of the koppa ladder's bottom rung.** Verified numerically to
ratio 1.000000 (all three) and 1.0001 via the proton-geometry `r_e = R_p/ϟ_H²`.

**The VALUE problem (R5 — the hinge).** `r_e = αℏ/(m_e c)` and `a₀ = ℏ/(m_e c α)` are *definitions in ℏ*. So
`ℏ = r_e·m_e·c/α` is an **exact identity** — it hands back the ℏ you put into `r_e`. It derives the ROLE; it does
**not** extract the VALUE. The only ℏ-lighter path is `r_e = R_p/ϟ_H²` (proton geometry) — but `R_p` and the
kinematic ratio `ϟ_H` are themselves *measured by atomic physics that encodes ℏ* (spectroscopy, muonic-H). **So
the audit question is whether ANY path reaches ℏ without an ℏ-bearing input — the ℏ analog of α's Route-B pure
ratio.** There is a strong prior that none exists, for a dimensional reason:

**The dimensional degeneracy (expected result → FLM12).** Koppa fixes **Length**; `c` fixes **Length/Time**.
Fixing **Mass** needs one more dimensionful anchor — an *action* (ℏ) **or** a *mass* (m_e) — and **neither is
constructible from length-and-velocity alone.** The circulation quantum `ℏ = m_e κ/2π` **ties them**: fix either,
the W=1 geometry yields the other; and m_p follows via the W=3 trefoil (`g_proton = R_p m_p c/ℏ ≈ 4 = W+1`). So
`{ℏ, m_e, m_p}` **collapse to a single mass/action seat** — which is the object **FLM12 (The Mass Mechanism)**
takes as its subject. FLM13's job ends at the collapse; FLM12's begins there. Producing the seat's *number* from
pure geometry is **forbidden by the seed theorem** (one dimensionful anchor is unavoidable) unless P4 finds a
genuinely ℏ-free measurement.

**Do NOT:** assert quantisation (derive it from circulation); write `ℏ = r_e m_e c/α` as a "derivation of ℏ"
(it is an identity — R5); import a mass value to "close" the loop and call ℏ derived.

---

## 4. Investigation Strategy (≥4 phases — gate each)

> Pre-commit thresholds in `RUN_LOG.md` (§⑩) before coding.

### Phase 1 — The ROLE: ℏ as the W=1 circulation quantum (THEORY + tool, ~2 h)
- **Goal:** derive `ℏ = m_e κ/2π` **mechanically** from Onsager–Feynman circulation of the W=1 vortex, and show its three ladder forms agree.
- **Method:** state the quantised-circulation condition for a superfluid vortex; identify the W=1 unknot as the single-quantum vortex; compute `ℏ` three ways (`m_e κ/2π`, `m_e·αc·a₀`, `r_e m_e c/α`) in `flm13_action.cpp`; confirm agreement to machine precision.
- **Gate:** all three forms equal to ≤1e-6 relative; the circulation quantisation is *derived from the superfluid*, not asserted. **OUT OF SCOPE:** claiming this fixes ℏ's value (that is P2).

### Phase 2 — The delete-test: is there an ℏ-free VALUE path? (AUDIT, ~2–3 h)
- **Goal:** a **pre-committed verdict** — does any extraction reach ℏ's number without an ℏ-bearing input?
- **Method:** enumerate every candidate input to the ℏ formulae (`r_e, a₀, R_p, ϟ_H, E_ion, m_e, α, c`); for each, trace whether its *measurement* encodes ℏ (spectroscopy/Rydberg → yes; a purely mechanical length/time → no). Seek the ℏ-analog of APS05 Route B (a **dimensionless ratio** that yields ℏ) — and prove it cannot exist (ℏ is dimensionful, no ratio is an action) **or** exhibit it.
- **Pre-committed metric:** the verdict is **ROLE-only** unless a delete-test-clean ℏ-free path is exhibited with numbers. **Failure trigger:** if a path is claimed clean but audit finds hidden ℏ → record and route OPEN; do **not** relabel a tautology as an extraction (R5).

### Phase 3 — The seat collapse: `{ℏ, m_e, m_p}` → one anchor (CALCULATION, ~2 h)
- **Goal:** prove the three mass-domain inputs are **one** seat, state the residual derivation basis exactly, and **hand the seat to FLM12**.
- **Method:** show `ℏ ↔ m_e` bijective via the W=1 circulation (fix one → other); show `m_p ↔ m_e` via the W=3 trefoil (`g_proton = R_p m_p c/ℏ = W+1`, engine-verified 0.02%); count the surviving independent dimensionful seats after koppa (length), c (Mercury), α (dimensionless). Output the reduced derivation basis and cross-reference FLM12 as the seat's owner.
- **Metric:** exactly **one** mass/action seat remains; the reduction `{ℏ,m_e,m_p}→1` is exhibited with the two bijections stated as SDT relations, not asserted.

### Phase 4 — The ℏ-free frontier: a non-atomic koppa path? (THEORY, ~2–4 h, may OPEN)
- **Goal:** determine whether the action's *value* can be reached by a **macroscopic/classical** koppa measurement (no atomic spectroscopy) — or confirm ℏ is the irreducible seat.
- **Method:** examine candidate non-atomic routes where an action appears natively — vortex circulation in a *macroscopic* superfluid analog (κ = h/m measured in liquid He), the Josephson/flux-quantum relations, blackbody/`T_CMB` (which carries ℏ via `u = a_rad T⁴`, linking to the thermal seat) — and test whether any yields ℏ without pre-loading it. Report **PASS (ℏ-free path found)**, or **OPEN (none; ℏ is the seat)** with the reason.
- **Metric:** a concrete ℏ-free path with a number, **or** a clear OPEN with the dimensional argument as the standing reason. **OUT OF SCOPE:** the thermal seat `k_B, T_CMB` (its own investigation) — only note the ℏ↔blackbody link.

---

## 5. Success Criteria (dual verdict)

- ✅ **PASS (Class A — VALUE derived).** A delete-test-clean, **ℏ-free** path lands `1.0546×10⁻³⁴` (P2 or P4). *This would be a major result and is not expected — flag extraordinary evidence.*
- ✅ **QUALIFIED (Class C — ROLE + collapse).** ℏ is derived as the W=1 circulation quantum (P1), the mass-domain derivation basis collapses `{ℏ,m_e,m_p}→one seat` (P3, handed to FLM12), and the value honestly rests on that single seat. **This is the expected, honest win.**
- ⚠️ **PENDING (Class D).** The ROLE holds but a bijection (P3) rests on an unproven relation → ship with the gap named.
- ❌ **FAIL / OPEN.** A "value derivation" is exposed as an ℏ-identity (R5 violation), or the seat-count is ambiguous. Do **not** call ℏ derived on the strength of `ℏ = r_e m_e c/α`.

**Dual verdict (`FLM13_VERDICT.md`):** prompt completion (A–F) **and** physics class (NATIVE = mechanical circulation ROLE + collapse; CONVERGENCE = the Onsager–Feynman identity merely *coincides*; OPEN = ℏ-free path unresolved). Honesty note: the **strong falsifiable core is the ℏ-free-path yes/no**, not the identity.

---

## 6. Outputs

1. **`FLM13_DERIVATION.md`** — the Onsager–Feynman ROLE (P1) with symbols; the delete-test table (P2, each input × does-its-measurement-encode-ℏ); the two bijections and the seat collapse (P3, → FLM12); the ℏ-free frontier verdict (P4). DERIVED vs IDENTITY vs OPEN flagged per line (R5).
2. **`flm13_action.cpp`** — computes ℏ three ladder ways + the Onsager–Feynman `m_e κ/2π`; prints the delete-test flags; prints the reduced derivation basis after the collapse. `#include <sdt/laws.hpp>` only; standalone (`cl /std:c++20 /EHsc /O2 /I Engine\include` or `g++ -std=c++20 -IEngine/include`).
3. **`flm13_results.txt`** — the three ℏ values + ratios; the input×ℏ-encoding table; the surviving-seat count.
4. **`FLM13_VERDICT.md`** — dual verdict + §⑧ table filled.
5. **`RUN_LOG.md`** — Pre-Run Commitment Block (the pre-committed ROLE-only-vs-VALUE verdict, the expected seat count = 1).

---

## 7. Dependencies & References

**Upstream (required):** `Papers/an_argument_for_koppa.md` (the ladder, `v=(c/ϟ)√(R/r)`, zϟ²=1); `laws.hpp` bridge (k-hierarchy, `koppa_hydrogen`, `k_Sun`) + `law_VI::winding` (`g_electron=α` tautology, `g_proton=W+1`); **PPT02 / APS05** (α off the derivation basis — the template for "measured anchor read off the ladder"); **GOM04** (c from Mercury precession); **GOM02** (15/15 k-hierarchy PASS); the barometer koppa (ℓ_P from `g, ρ_E, R`).

**Sibling / hands-off (tightly coupled):** **FLM12 (The Mass Mechanism)** — the single mass/action seat that FLM13's collapse produces is FLM12's *subject*; keep the boundary clean (FLM13 = ℏ's ROLE + the collapse; FLM12 = what the seat *is*). **FLM11 (ruler count)** — the "how many seats" epistemology.

**Downstream (fed by this):** the **reduced derivation basis** (`{one mass seat (FLM12), α, k_B, T_CMB}`) — the theory's irreducible core; the thermal-seat investigation (`k_B, T_CMB` — the ℏ↔blackbody link noted in P4).

**Related:** OP-3/E51 (α value from W=1 torus `v_P/v_T` — the *dimensionless* analog of this *dimensionful* question).

---

## 8. Falsification Tests

| ID | Hypothesis | Predicted outcome | If FAIL |
|----|-----------|-------------------|---------|
| **F1** | ℏ = the W=1 circulation quantum (mechanical) | `ℏ = m_e κ/2π` derived from superfluid quantisation; three ladder forms agree to 1e-6 | quantisation must be *asserted* → ROLE not derived; KILL the "mechanical" claim |
| **F2** | No ℏ-free VALUE path exists (ℏ is dimensionful) | every extraction routes through an ℏ-encoding atomic quantity; no ratio yields an action | a **clean ℏ-free path is found** → Class A VALUE (extraordinary; demote the seed-theorem claim, celebrate) |
| **F3** | `{ℏ,m_e,m_p}` collapse to one seat | two SDT bijections (W=1 circulation, W=3 trefoil) exhibited; one seat survives → FLM12 | a second independent mass seat survives → the collapse is wrong; re-audit |
| **F4** | `ℏ = r_e m_e c/α` is an IDENTITY, not an extraction (R5) | audit shows `r_e ≡ αℏ/m_e c` on both sides | if someone ships it as "ℏ derived" → **R5 violation**, revert to ROLE-only |
| **F5** | ℏ is the irreducible mass/action seat (seed theorem) | after koppa+c+α, exactly one dimensionful anchor remains | zero anchors needed → the seed theorem is broken here (extraordinary; document) |

**Recovery:** F2/F5 — if a path *looks* clean, re-audit the measurement chain of every input for hidden ℏ before claiming VALUE. Never relabel an identity as an extraction to force a PASS.

---

## 9. Implementation Notes

- **Double precision.** ℏ chain is exact to 1e-6; the proton-geometry path (`R_p/ϟ_H²`) lands 1.0001 — keep both and *label the 0.01% as the R_p/ϟ_H measurement residual*, not physics.
- **The tool's real job is the delete-test table, not the number.** The ℏ *value* is not in doubt (it is an identity); the deliverable is **which inputs encode ℏ** — encode that as an explicit boolean per input, sourced to how each is measured.
- **Circulation, not postulate.** `κ = h/m` must appear as the superfluid quantised-circulation result (Onsager–Feynman), with the W=1 unknot as the single-quantum vortex — not "Bohr said L=nℏ."
- **No borrowed units, no ψ.** Say "circulation quantum κ," not "angular-momentum operator." (R1/R3)
- **Report the reduced derivation basis explicitly** in `flm13_results.txt`: `{ℓ_P←koppa(g,ρ,R), c←Mercury, α←PPT02/APS05, ONE mass seat (→FLM12), k_B, T_CMB}` — so the compression 8→core is on the record.

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)
```markdown
## Pre-Run Commitments — FLM13
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE (ROLE+collapse) | CONVERGENCE | OPEN]
- CALIBRATED budget: [0 — no fitting; this is an identity + an audit]
- PRE-COMMITTED VERDICT: ROLE-only expected (ℏ = W=1 circulation quantum); VALUE expected OPEN (ℏ dimensionful)
- PRE-COMMITTED SEAT COUNT after collapse: 1 (one mass/action anchor → FLM12; ℏ≡m_e via κ, m_p via W=3)
- ℏ-free path (P4): [expected NONE — state the dimensional reason; overturn only with a numbered path]
- Forbidden: shipping `ℏ=r_e m_e c/α` as a VALUE derivation (R5); asserting quantisation; importing a mass to "close" ℏ
- Phase gates: P1 (three forms agree, circulation mechanical) → P2 (delete-test verdict) → P3 (one seat → FLM12) → P4 (ℏ-free yes/no)
```

### Pivot table
| Trigger | First response (PIVOT) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 quantisation must be asserted | derive κ from superfluid vortex circulation explicitly | **OPEN** the mechanism | "Bohr postulate" as the derivation |
| P2 a path claimed ℏ-free | audit each input's measurement chain for hidden ℏ | **OPEN** (ROLE-only) | relabel an identity as extraction (R5) |
| P3 a second mass seat survives | re-check the W=1 / W=3 bijections | **PENDING** the collapse | assert one seat without both bijections |
| P4 an ℏ-free path *appears* to work | demand a number + full delete-test | **OPEN**; keep seed-theorem reason | claim Class A on a hand-wave |
| Onsager–Feynman merely coincides | label **CONVERGENCE**, not NATIVE | — | claim mechanical ROLE from coincidence |

### Disallowed adjustments
- Presenting `ℏ = r_e m_e c/α` (or `m_e αc a₀`) as a **value** derivation (it is an identity — R5); rounding the R_p/ϟ_H residual into a "prediction"; importing a mass to close the loop; widening "ℏ-free" to include atomic spectroscopy.

### Dual verdict reminder
Report both axes in `FLM13_VERDICT.md`. The honest expected outcome is **QUALIFIED / NATIVE (ROLE + one-seat
collapse)** — a genuine reduction of `{ℏ,m_e,m_p}` to a single native anchor handed to FLM12 — with the
**VALUE** left **OPEN** behind the seed theorem, and the ℏ-free frontier (P4) named as the one door that could
change that.

---

*FLM13 · SPEC · ℏ is the koppa ladder's bottom-rung circulation — native in ROLE, one seat after collapse (→
FLM12), and honest about the value the seed theorem still guards. Execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
