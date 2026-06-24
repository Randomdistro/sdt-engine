# CQ-50 — THE GEAR-FREQUENCY BINDING FUNCTIONAL
## Successor to CQ-32: test whether binding is `E_bind = ℏ·Δω` (a mesh-coupling frequency *pull*), where the volume-deficit functional failed

**Framework:** Spatial Displacement Theory v6.0+, constitutional ruleset in full force.
**Lineage:** opened by the CQ-32 kill report (`CQ32_Gate_G1_Price_of_Displacement/KILL_REPORT.md`). CQ-32
falsified `E = price × geometric-deficit` at the nuclear scale (G1 fail, G4 fail; per-nucleus BE/deficit not
constant: 0.050→0.082→0.166). The named successor — declared *before* this investigation — is the
gear-frequency form. This is its test.
**Injection target:** fresh agentic session with sdt-engine access, Python (C++/packing.hpp optional).
Reuses CQ-32's sealed answers and two-stream-verified geometry engine.

---

## 0. WHAT IS AT STAKE (read before any tool call)

CQ-32 showed binding is **not** a static displaced volume. SDT's own gear theorems say why: the mechanism is
**rotation**, not volume — T-I rim quantisation `RΩ = (W+1)c`, T-J mesh `r_eΩ_e = a₀ω₁ = αc`, T-K gear ratio.
The successor hypothesis:

> **`E_bind = ℏ · Δω`** — binding is the change in the **meshed-circulation frequency** when structures lock.

**THE TRIVIAL-IDENTITY TRAP (the load-bearing warning).** The rim frequency is `Ω = (W+1)c/R`, and since
`R = (W+1)ℏ/(mc)`, this gives **`ℏΩ_rim = mc²` exactly**. So if `Δω` is taken as the change in *rim/rest*
frequency, `E = ℏΔω = Δ(mc²)` = the mass defect — which is `E=mc²` restated and predicts the binding by
definition. **THAT IS VACUOUS AND FORBIDDEN** (it is the same vacuity CQ-32's V_disp-from-mass route had).
The non-trivial content this investigation must test is the **MESH-COUPLING FREQUENCY PULL**: when two rotors
mesh (roll in contact, no slip), their coupled normal modes **split** from the free frequency by an amount set
by the *coupling geometry* — the bond energy is `ℏ ×` that split, derived from the mesh, never from the mass.

---

## RULES (carried verbatim from CQ-32; in force throughout)

- **R0 Vocabulary sovereignty** — reason in SDT primitives (tube, winding, mesh, gear, rim, rotor, contact,
  circulation, conscription, budget, tick). Conventional terms only inside ⟦instrument-output⟧ brackets.
- **R1 Predict-before-look** — derive the frequency quantities and commit to the run log BEFORE unsealing any
  energy. Sealed answers (H₂ 4.52 eV; the CQ-32 nuclear set) live in `sealed/`, read only by the harness.
- **R2 Parameter ledger** — every number tagged DERIVED / MEASURED-INPUT / CALIBRATED(n) at first use. Target
  state **CALIBRATED(0)**: the coupling comes from mesh geometry, nothing tuned.
- **R3 Two-stream verification** — any CONFIRMED result independently recomputed (different method / second
  instance). Frequency shifts: closed-form coupled-rotor where available, vs numerical mesh-mode solve, <1%.
- **R4 Honesty over success** — a cleanly-logged fired gate outranks a soft pass. If the frequency form dies
  too, the kill report (with the next successor named) is the deliverable.
- **R5 Anti-numerology** — no free-integer rescues; any factor derived from geometry first, look-elsewhere
  cost logged. **And the trivial-identity guard above: reject any route where Δω reduces to Δ(mc²)/ℏ.**

---

## 1. THE HYPOTHESIS, STATED MECHANICALLY

Each nucleon is a rotor (rim speed `(W+1)c`, free rim frequency `Ω_0 = mc²/ℏ`). A **bond** is a mesh contact
where two rims roll without slip. Meshed rotors are a coupled system; its normal modes are pulled off `Ω_0`:

    ω_± = Ω_0 · (1 ± κ_geom)        (schematic — the real split form is to be derived, not assumed)

where **`κ_geom` is the dimensionless coupling set by the contact geometry** (rim overlap, contact-arc,
relative axis orientation, no-slip constraint). The **binding per bond** is the energy stored in the pulled
mode relative to free: `ε_bond = ℏ·(Ω_0 − ω_lock)` for the locked (lowered) mode. For a nucleus:

    E_bind = Σ_bonds ℏ·Δω(contact)      — sum over the mesh-contact graph.

The investigation's whole job is to **derive `κ_geom` (hence Δω) from the mesh geometry, parameter-free**, and
test whether the resulting `E_bind` reproduces the measured binding across scales with **one** rule.

## 2. THE MESH-CONTACT GRAPH (reuse CQ-32 geometry)

- Nucleon positions: the CQ-32 declared clusters (d=dimer, t/h=triangle, α=tetra edge s, ⁶Li=α+ext d,
  ⁹Be=2α+n), separation `s = 2·R_ring` (ring-contact, parameter-free). The geometry engine (`stage2b/stage4`,
  two-stream verified to 0.08%) gives contact pairs and contact geometry directly.
- A **bond** exists where two rims are within ring-contact. For each bond compute the contact geometry
  (overlap depth, contact-arc, axis angle) → `κ_geom` → `Δω`. **Counter-rotation / no-slip** (gear parity,
  T-M) sets which contacts can lock vs frustrate (odd-cycle frustration — log it; may explain α's anomaly as
  a fully-satisfiable even mesh vs frustrated ones).

## 3. ANCHOR TEST — the H₂ frequency-pull (declared FIRST, cross-scale)

The single most important test, set before any nuclear run so it cannot be fudged:

> Two protons meshed at the H₂ bond length. Compute the coupled-rotor frequency pull `Δω` from the contact
> geometry; predict `ℏΔω`. **Unseal 4.52 eV last.** A pass here — a *frequency* price that lands 22 orders
> below the nucleus on the same `ε_bond = ℏΔω` rule — is the cross-scale vindication the volume form never
> reached. (It is also the protocol successor-test named in the CQ-32 kill report.)

## 4. NUCLEAR GATE (same sealed set as CQ-32)

Reuse `CQ32_Gate_G1_Price_of_Displacement/sealed/answers.json` (8 reactions + single-nucleus BE for
d,t,h,α,⁶Li,⁹Be). Predict each binding/Q from the mesh-frequency sum; unseal; score.

- **GATE Gω (the gate):** does the single rule `E_bind = Σ ℏΔω(contact)`, with `κ_geom` derived from the
  mesh, reproduce the 8 Q-values **and** the H₂ bond within ±15%, at **CALIBRATED(0)**?
- **Diagnostic targets (the two things that broke the volume form — does frequency fix them?):**
  (a) the **α-anomaly** — does a fully-satisfied even mesh (6 locked contacts, no frustration) naturally
  over-bind α relative to d, where the volume-deficit could not?
  (b) the **loose clusters** (⁶Li, ⁹Be) — does a *soft/few-contact* mesh give small Δω without needing a
  binding-dependent separation (the failure mode of CQ-32)?

## 5. KILL CONDITION (declared now)

If Gω fails after `κ_geom` is honestly derived (not tuned): log the kill, sort the residuals, and name the
next successor (candidate: binding as a **phase/winding-relock cost**, or an explicit per-tick lattice
relaxation — the ROOT-SIM). **Do not add free parameters to force Gω.** Two clean kills (volume, frequency)
would itself be a major structural result: binding is not reducible to a single local geometric OR frequency
price, and is irreducibly the full per-contact mesh dynamics (ROOT-SIM).

## 6. DELIVERABLES
D1 `mesh_graph.md` — the contact graph + per-bond contact geometry (frozen, blind to energies).
D2 `kappa_derivation.md` — `κ_geom → Δω` from the no-slip coupled-rotor mesh, two-stream verified.
D3 The H₂ frequency-pull result (the anchor page).
D4 The Gω verdict on the 8 reactions + single-nucleus BE; residuals sorted.
D5 Parameter ledger (target CALIBRATED(0); judged first) + run log (append-only, sealed hashes).
D6 Pass write-up OR kill report with the next successor named.

## FINAL INSTRUCTION
One question: **is binding a mesh-coupling frequency pull?** Forbid the rim/rest-frequency identity (R5),
derive `κ_geom` from the no-slip mesh, anchor on H₂, then face the sealed nuclear set. A frequency price that
is universal where the volume price was local would re-route the five locks and put the north-star
(forced structure → choosable scission) on the rotation mechanism SDT was always built on. Open it honestly
or report why it will not open.
