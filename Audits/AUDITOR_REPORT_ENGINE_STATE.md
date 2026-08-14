# Auditor's Report — SDT Engine (OrbOS upstream physics)

> **To:** The Architect
> **From:** The Auditor
> **Date:** 2026-06-16
> **Subject:** stress-test of `sdt-engine` — the canonical Spatial Displacement Theory engine, designated **the updated physics engine for OrbOS**. Where it breaks, fails, or misfires.
> **Method:** read the spine (`Engine/include/sdt/laws.hpp`), the headline claims (`README.md`, `CLAUDE.md`), and the project's own self-audits (`FORMULATIONS_PROVENANCE_AUDIT.md`, `CONCEPTUAL_CONTAMINATION_AUDIT.md`); **empirical MSVC builds** of the spine and the B01–B25 benchmarks; provenance/delete-test spot-checks. `[PROVEN]` = reproduced toolchain/grep output.
> **Snapshot:** the working tree is **dirty and mid-refactor** (laws.hpp, benchmarks, theory docs, deleted FLM03, new NP05–34 all uncommitted; last commit `5669a16` "getting closer"). This audits that snapshot; HEAD differs (see F-1).

---

## 0. Verdict

The engine is a **serious, internally self-aware framework with a genuine mathematical core — and a headline that overstates what it has closed.** Three things matter most for OrbOS:

1. **It does not build right now.** The "single source of truth" `laws.hpp` fails to compile in the working tree, and the benchmarks (the project's only end-to-end verification) fail with it. This is uncommitted mid-refactor WIP — **HEAD compiles** — but there is **no committed, building, labelled snapshot** to hand OrbOS today. **[PROVEN]**
2. **"No G" is false at the primitive level.** The framework never writes the symbol `G`, but it injects G's *numerical value* through the Planck length `ℓ_P = √(ℏG/c³)`, which is **load-bearing** in Law I (relay throughput), Law IV (inertial mass), and the koppa bridge. The project's own provenance audit already flags this (`risk: l_P↔G`); I confirm it is not cosmetic. **[PROVEN]**
3. **"Zero free parameters" is contradicted by the engine's own accounting.** README/CLAUDE.md say zero-free-parameter; the provenance audit honestly reports **~9% calibrated + ~8% external-input**, retains Bohr radius / Rydberg / Compton / R_p as measured anchors "for empirical checks only," keeps **α and the masses as inputs**, and lists α-from-topology and the mass ratio as **open problems**. The honest internal number (**~57 delete-test-passing derivations**) is a strong claim; the marketing number (zero) is not the same claim.

**The good news, stated up front:** the project's *own* self-audits are unusually rigorous — a delete-test, five certification labels, an explicit contamination taxonomy, and honest risk flags including the ℓ_P↔G one. The problem is the **gap between the top-level claims and the project's own honest internal accounting**, not a lack of self-knowledge. Fix the claims (and the build), and most of this resolves.

---

## 1. Findings

### F-1 — BUILD: the canonical header + benchmarks don't compile (working tree) **[PROVEN]**
`cl /std:c++20 /I Engine/include Benchmarks/B01_B25/benchmarks_b01_b25.cpp`:
```
laws.hpp(898): error C2454: 'sdt': namespace alias name cannot be declared using a qualified name
laws.hpp(898): error C2386: 'sdt': a symbol with this name already exists in the current scope
benchmarks_b01_b25.cpp(477): error C2653: 'winding' is not a class or namespace name
                       (481): error C2065: 'R_p_predicted' / 'W_eff' undeclared
```
Root cause — a **half-finished `winding` refactor**: `laws.hpp:898` is `namespace sdt::laws::winding = sdt::laws::law_VI::winding;` (you cannot alias with a qualified LHS → C2454), and it **collides** with the still-present `namespace winding {` at `:813` (→ C2386). The parse failure cascades into every benchmark using `winding::`.
- **Fairness:** HEAD's `laws.hpp` (879 lines, no line-898 alias, single `winding` at :799) **compiles clean** — the break is purely uncommitted WIP. **[PROVEN]**
- **Why it matters for OrbOS anyway:** the "single source of truth" and its end-to-end verification are, *as the tree stands*, non-building. A header that doesn't compile cannot gate anything, and there is no committed snapshot tagged as the canonical hand-off. Land a building commit before OrbOS syncs against it.

### F-2 — PHYSICS: "No G" fails at the primitive level via `ℓ_P` **[PROVEN, load-bearing]**
`ℓ_P = 1.616255e-35` is dependency-traced as a primitive (`laws.hpp:112`), but the CODATA Planck length **is computed from G** (`ℓ_P = √(ℏG/c³)`). It is load-bearing, not decorative:
```
laws.hpp:215  N        = R_CMB / l_P                  (Law I — relay count)
laws.hpp:234  P_conv   = Phi / l_P3                   (Law I — conversion pressure)
laws.hpp:367  V_disp   = 3·mass·l_P3·c² / Phi         (Law IV — inertial mass)
laws.hpp:672  koppa_per_baryon = l_P²·c·m_p / hbar    (bridge)
```
Powers partially cancel (`Φ = Nε ∝ ℓ_P²`), but a **net dependence survives** — e.g. `V_disp ∝ ℓ_P`, `P_conv ∝ 1/ℓ_P` — so the inertial-mass and pressure numbers **carry ℓ_P's value, hence G's**. The framework's own audit says it plainly: *"CODATA l_P conventionally encodes G"* and flags `koppa_per_baryon` as `C-flagged — risk: l_P↔G`. **Conclusion:** the absolute claim "**No G**" is not supportable as written. The defensible claim is: *"G never appears as a symbolic primitive; its numerical value enters through the CODATA `ℓ_P`, which we have not yet derived from SDT structure."* That is a materially weaker — and honest — claim.

### F-3 — CLAIMS vs ACCOUNTING: "zero free parameters" is overstated **[PROVEN by the project's own docs]**
- `laws.hpp:124-139` retains Bohr radius, classical electron radius, **proton charge radius R_p**, Rydberg, Ry_eV, and **both Compton wavelengths** as `measured` inputs — explicitly *"Validation anchors … currently retained for empirical checks only. In a fully closed SDT derivation, these should follow from the base invariants"*. They don't yet.
- **α is an input** (`:114` "Optional empirical anchor", `:122` `alpha_inv`), and `laws.hpp:884` admits α-from-topology *"Would eliminate α as input"* — i.e. **not yet eliminated**. PPT02 "Fine Structure from Topology" itself consumes `alpha_inv` (`cq03_fine_structure.cpp:436`). So α-derivation is **PENDING/exploratory, not closed** — consistent with the open-problem list, but not with a "derived" headline.
- **m_e, m_p, m_n are inputs**; the proton/electron mass ratio is an open problem (`laws.hpp:889`: *"Requires W=3 vs W=1 equilibrium calculation"*).
- The provenance audit's own ledger: **SDT-posited ≈ 6% · SDT-derived ≈ 72% · calibrated ≈ 9% · external-input ≈ 8% · unresolved ≈ 5%**, with the universal force-law pressure `P_eff` **calibrated to hydrogen** (`E — calibrated-target`). "Zero free parameters" and "9% calibrated + 8% external" are not the same statement.

### F-4 — SCOPE OF THE ORBITAL RESULT (corrected 2026-06-16 after author rebuttal)
*Original framing ("tautology / Kepler relabelled") was an overreach and is withdrawn.* The author's rebuttal is correct on two points: (1) algebraic equivalence to `GM/c²` where the framework overlaps established results is a **required consistency condition**, not evidence of emptiness — a correct framework *must* reproduce `GM = v²r`; (2) the orbital pipeline's inputs are **genuinely `{v, r, c}`** — an orbit yields only the product `μ = GM = v²r`, and G and M are *outputs*, not inputs (separating G from M needs an independent Cavendish-type measurement, which SDT correctly declines to assume). So "no G, no M as inputs" is **literally true** for this pipeline.

**EMPIRICAL UPDATE (ran CQ18a/b, 2026-06-16) — independent cross-domain match confirmed, delete-test passes.** I built and ran the solar/stellar z-decomposition. `Ϟ_sun` derived from the **spectroscopic** solar gravitational redshift (`z=2.12×10⁻⁶`, Fe I) × `R_sun` = **1474.9 m**; derived **independently** from each of the 8 planets' orbital `(r,T)` via Kepler = **1476.6 m** — **agree to ~0.12%**, with the redshift never entering the orbital path and vice-versa. CQ18b reproduces it for exoplanet hosts (spectroscopic `log g`×`R_star` `Ϟ` = orbital-timing `Ϟ`). **[PROVEN]** This is a genuine independent cross-domain consistency (spectroscopy ↔ orbital mechanics), zero free parameters, no G/M, delete-test clean. The author's rebuttal is **upheld empirically**: one number (`Ϟ` = `z·R`) links the two domains.

Two scope caveats that survive the confirmation: (a) **this reproduces a GR-level link** — standard GR also gives both = `GM/c²`, so the 0.12% match is a parameter-free *reproduction*, not (from this test) a discriminator against standard physics; (b) **the cross-scale claim ("all QM results at the Planck scale") is in a different regime and remains untested here** — CR01 is solar/stellar. *Action:* run the same delete-test on an **atomic/nuclear** prediction (PPT01/03/05/17) whose input path is `{v,r,c}`/`{z,k}` only — if it lands like CR01 did, the grand claim is carried and F-2/F-3 shrink. Note CQ18a/b are **self-contained** (they never include `laws.hpp`), so they are clean of F-2; the Planck-scale laws, which *do* read the CODATA `ℓ_P`, are not auto-cleared by this orbital result.

### F-5 — DEFINITIONAL: the Coulomb "identity" is a definition, not a result
`k_e e² = α ℏ c` (`coulomb_identity`) is the **definition** of α (`α ≡ k_e e²/ℏc`). The project correctly self-classifies this as `F — definitional identity`; flagged here only because it sits adjacent to claimed "derivations" and is easy to read as one.

### F-6 — PROCESS: dirty moving target; self-audits untracked
The tree is broadly dirty mid-refactor (F-1), `CONCEPTUAL_CONTAMINATION_AUDIT.md` is **untracked**, and the last commit is "getting closer." There is no tagged/committed "canonical engine vN" state. For an artifact designated as OrbOS's physics source, the absence of a frozen, building, labelled release is itself a finding (cf. the OrbOS-side "freeze before certification" rule).

---

## 2. What is genuinely credible (fairness)

- **The self-audit machinery is excellent and rare.** The delete-test ("the matched value is provably absent from the derivation"), the five certification labels, the contamination taxonomy (A–F/X), and the honest risk flags (including ℓ_P↔G) are exactly the right tools. Most frameworks making these claims have none of this. The **~57 SDT-derived × known-match results that pass the delete-test** is a real, defensible headline — if it were the headline.
- **The kinematic pipeline is sound** *as kinematics*: `Ϟ` from transit/timing, the `zk²=1` closure as a consistency check, self-calibration across planets. It is Kepler, correctly and parameter-free-ly implemented — useful, just not new gravity.
- **The benchmark methodology** (compare SDT value to measured within tolerance, tag with a certification label) is the right verification design — when it compiles.

---

## 3. OrbOS relevance (why the Architect should care)

This engine is upstream of OrbOS's `physics/sdt`. The OrbOS-side invariant is advertised as **"SDT v4 — no G, mass as output."** This audit shows the **source does not yet support that invariant absolutely**:
- **G** enters OrbOS-downstream through the same `ℓ_P` channel (F-2) wherever OrbOS uses Planck-scale quantities. OrbOS should not claim "no G" more strongly than the engine can — i.e., not absolutely.
- **Mass as output** is *not closed upstream* (masses are inputs; the mass ratio is open) — which is exactly why my **Module-4 audit** found OrbOS's `physics/sdt` still using **mass-as-input Newtonian `F = m·a`** (PH-10, deferred). The two are consistent: OrbOS can't make mass an output until the engine does, and the engine hasn't.
- Therefore OrbOS's physics invariant should be re-stated to mirror the engine's **honest labels** (DERIVED / CALIBRATED / external-input), not a blanket "SDT v4, no G."

---

## 4. Recommendations to the Architect

**Immediate (engine):**
1. **Fix F-1 and land a building commit.** Finish or revert the `winding` refactor: either `namespace sdt::laws { namespace winding = law_VI::winding; }` *inside* the namespace **and** delete the duplicate `:813 namespace winding`, or revert to the HEAD layout. Then re-run B01–B25 and confirm PASS/label counts. A "single source of truth" that doesn't compile can gate nothing.
2. **Tag a frozen, building, labelled snapshot** ("engine vN") before OrbOS syncs — and commit `CONCEPTUAL_CONTAMINATION_AUDIT.md`.

**Claims (do this before any external release):**
3. **Resolve `ℓ_P↔G` (F-2) one of two honest ways:** (a) derive `ℓ_P` from SDT primitives without G, or (b) drop the absolute "No G" and state "G never appears symbolically; its value enters via CODATA `ℓ_P`." Pick one; don't keep both the marketing and the risk-flag.
4. **Make the headline match the provenance ledger (F-3).** Replace "zero free parameters" with the engine's own honest claim — "~72% derived, ~9% calibrated (documented), ~8% external-input; ~57 results pass the delete-test." That claim is strong *and* true.
5. **F-4 (corrected):** the `Ϟ`/`zk²=1` orbital pipeline is genuinely `{v,r,c}`-grounded and G/M-input-free (G, M are outputs); a single orbit's `Ϟ` is a correct parameter-free **measurement of μ**. The substantive claim — same `zk²=1` across scales to atomic/nuclear/Planck quantities — is **pending audit**: supply 2–3 worked Planck/QM derivations with `{v,r,c}`-only input paths for a delete-test. **F-5:** the Coulomb identity `k_e e² = αℏc` is definitional — keep it, label it.

**OrbOS-side:**
6. **Re-state the OrbOS physics invariant** to mirror the engine's labels, and keep OrbOS's `physics/sdt` mass-as-output (PH-10) explicitly **blocked-on-upstream** until the engine closes mass — don't let OrbOS claim what the source can't.
7. **Gate OrbOS↔engine sync on a committed, building engine tag** (same "freeze before certification" discipline used on the OrbOS modules).

**Bottom line:** the SDT engine is a rigorous, self-critical framework whose *internal* honesty (provenance audit, delete-test, risk flags) is well ahead of its *external* claims. The build is broken only by uncommitted WIP; the real, durable issues are (F-2) G entering via `ℓ_P` and (F-3) a headline that claims more closure than the engine's own ledger reports. Both are fixable by aligning the claims with the project's own excellent accounting — and OrbOS should not market "no G / mass-as-output" any harder than the upstream engine can currently support.

*Cross-reference: OrbOS Module-4 physics audit (`hsml_os/audit/impl-audit/04-physics-sdt.md`) — the downstream consequence of F-2/F-3 (mass-as-input still live, deferred as PH-10).*
