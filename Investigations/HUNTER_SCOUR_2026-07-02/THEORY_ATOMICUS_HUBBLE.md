# HUNTER SCOUR — Theory / Papers / ATOMICUS / Hubble / PV_canon

> Region: prose + tools **outside** the numbered Investigations.
> Auditor: HUNTER (max pressure, assume-fabrication). Date: 2026-07-02.
> Discipline: every fault shows a quote + contradicting verdict, a compile/run, or a recomputation.
> Read-only pass — **no files edited**; `Engine/`, `Laws/` untouched. Build artifacts in scratchpad.

## Verdict up front

The **tools in this region are honest**: De Rerum (19/0), ATOMICUS `structural_analysis`, and the
Hubble zk² tools I built **all compile and run and reproduce their stored outputs**. Nothing here is a
FABRICATED tool (unlike APS04, whose `.cpp` never compiled). **The faults are in PROSE**: overclaims that
outrun the tools' own honest verdicts, one prohibited primitive smuggled to the axiom layer, and one
fished constant (the APS04 `1051.8 MHz`) that has propagated from `laws.hpp` into the De Rerum treatise and
the PV_canon compendium.

---

## Fault table

| # | doc / tool | claim | fault | evidence | severity |
|---|-----------|-------|-------|----------|----------|
| 1 | `Hubble/data/17_Pantheon_Proof.md` (title + §5.2/§5.3) | filename "Pantheon **Proof**"; "n~1 … **This is the physically consistent SDT model**"; "SDT-A is PREFERRED over LCDM" | **OVERCLAIM** — the tool's own run KILLS the physical SDT model and no SDT model wins | I built+ran `zk2_pantheon_proof.cpp` (BUILD_EXIT=0). Ranking: **#1 Milne (empty) BIC 4.54**, #2 SDT-A 5.61, #4 LCDM 8.07, **#6 SDT-B (n=4, the T⁴ CMB-pressure model) BIC 271.45**; tool prints "T^4 … **CATASTROPHICALLY rejected** … 107x worse than LCDM." The n=1 survivor relabeled "physically consistent" is a RETRO-relabel (the *originally* physical model was n=4). Best SDT-C needs a **fitted** n=0.847 and still loses to empty-universe Milne. | **OVERCLAIM (high)** |
| 2 | `Investigations/PV_canon/SDT_Complete_Canonical_Compendium.md:4922` | "**Axiom 1.4 (Proton Structure).** The proton consists of three constituent toroidal vortices **(quarks)** …" | **PROHIBITED IMPORT (BORROW-SMUGGLE)** at the axiom layer — quarks are a forbidden primitive; also self-contradicts the next lines calling it a "6π trefoil torus" | Quote at :4922. CLAUDE.md/Ruleset: "no quarks/gluons." Repo's own NP17 model = interleaved trefoils + shared electrons, *no quarks*. Elevating "quarks" to an **Axiom** imports the thing SDT claims to replace. | **OVERCLAIM/IMPORT (high)** |
| 3 | same file `:7526`, `:7538` | "All nuclear physics: From single equation, **zero free parameters**" / "One equation. All nuclear physics. Zero free parameters." | **OVERCLAIM** — nuclear binding is NOT fully derived; alpha is honest-PENDING | Contradicted by NP17 real verdict (deuteron PASSES; **alpha under-binds via electrostatics, PENDING**). Same page `:7521` inserts `P_nuc = 1.65×10³¹ Pa (from geometric focusing)` and `:7525` "Validated to within 1% for heavy nuclei" — a tolerance-validation, not a zero-param derivation. | **OVERCLAIM (high)** |
| 4 | `Engine/include/sdt/laws.hpp:1340` **(READ-ONLY — reported, not edited)** → propagated to `Papers/De_Rerum…/Book_II…md:196` and de_rerum PASS row | `lamb_shift_native_MHz = 1051.8`, labelled `circularity_assertion: not tuned (emergent)`, `input_dependency: … (zero fitted params)`; De Rerum prints "2S–2P native candidate 1051.8 vs 1057.845 (0.57%) **PASS**" | **FISHED CONSTANT re-exposed as a PASS (IDENTITY-PASS)** | `laws.hpp:1338` self-labels it "emergent / not tuned / zero fitted params," but the **APS04_HUNTER_AUDIT** proved `1051.8` was hand-typed (solver never compiled; the actual formula gives ~3145 MHz). De Rerum "checks" the hard-coded 1051.8 against 1057.845 at tol 1e-2 and calls it PASS. The number is not earned; the 0.57% "match" is manufactured. **PPT08 is OPEN, not resolved.** | **OVERCLAIM (high)** |
| 5 | `Release/JPL_SSD_Orbital_Ephemeris/Theory/03_Open_Problems.md:3` | "Three computational problems remain. **Zero conceptual gaps.**" | **INTERNAL INCONSISTENCY** | Same file `:29` labels α-from-topology a "**Conjecture**" (a conceptual gap). Repo verdicts contradict "zero gaps": PPT08 OPEN, alpha-binding PENDING (NP17), rotation FAILED SPARC (GD05, RMS 66%), neutron barrier depth B "deep OPEN" (SCT). | **INCONSISTENCY (med)** |
| 6 | `Hubble/README.md:22,23,30` (Key Claims) | Row2 "Redshift = amplitude-to-wavelength conversion … **DERIVED**"; Row3 "H₀ measures local κ … **DERIVED**"; Row10 "Universe age **~46 Gyr** … DERIVED" | **OVERCLAIM** — mechanism is posited (Axiom R1 per Ruleset), not derived; the physical version was just KILLED (#1); Row3 is definitional; 46 Gyr is a dramatic result stamped DERIVED | Row2 mechanism = the same redshift story whose T⁴ realisation is catastrophically rejected by `zk2_pantheon_proof`. README `:41` still lists "Fit zk²=1 to Pantheon+" as an **OPEN** HIGH task while `17_Pantheon_Proof.md` claims it done → **stale/inconsistent**. | **OVERCLAIM (med)** |
| 7 | `Hubble/data/19_Exponent_Derivation.md` (title) + any "DERIVED" index label | title "Exponent **Derivation**" | **OVERCLAIM in framing, self-corrected in body** | Built+ran `zk2_exponent_derivation.cpp` (BUILD_EXIT=0). Tool + file §7 verdict `:185,:201`: "**PARTIALLY CONSTRAINED** … amplitudes still **fitted** … **not derived from lattice dynamics** … full derivation … does not yet exist." Body is honest; only the title/label "derivation/DERIVED" overreaches. | **MINOR** |
| 8 | `ATOMICUS/elements/032_Germanium…md:6,14` | "complete, **first-principles derivation** of the properties of Germanium"; "energy gap … 0.67 eV … a **direct consequence of its geometric stability**" | **OVERCLAIM** — 0.67 eV is the *measured* band gap, asserted as geometry-derived; no derivation shown | Quote at :6/:14. No calculation produces 0.67 eV from the tetrahedron; the number is the empirical value narrated as if consequent. (Pattern; byline "Framework Synthesis and Analysis: AI Collaborator".) | **OVERCLAIM (low-med)** |
| 9 | `ATOMICUS/reports/STRUCTURAL_ANALYSIS_REPORT.md §6` | "W+1 Radius **Verification**" table | **half-truth** — the rule fits the proton but the electron row is off by **27307%** | Report `:295` shows Electron predicted 7.7232e-13 vs measured 2.8179e-15 (27307% error), then swaps to a *different* formula (r_e = αℏ/m_e c). Verified by rebuild: `struct_an.exe` reproduces the table. Honest that the number is huge, but titling it "verification" while it fails 1 of 2 cases is generous. | **MINOR** |
| 10 | `Hubble/INVESTIGATION_Flyby_Anomaly.md:213` | "the same reason gravitational lensing deflection angle is **δ = 4GM/(c²b)**" | GM referenced (Ruleset-discouraged), but as an **analogy**, not load-bearing | Quote at :213. The load-bearing factor is native `K = 2ωR/c` (`:207`); GM appears only in an illustrative "same reason" aside. Fair-graded: not smuggled into the SDT chain. | **MINOR** |

---

## Tool-verification log (all reproduced; scratchpad)

| tool | build | run | claim reproduced? |
|------|-------|-----|-------------------|
| `Papers/De_Rerum_Todo_Existens/de_rerum.cpp` | ✅ BUILD_EXIT=0 | ✅ | **YES — "19 PASS / 0 FAIL" is REAL**; live output == `de_rerum_results.txt`. Honest tool: prints its own `[F!]` delete-test flags for the k_e e²=αℏc and l_P identities. Caveat: the Lamb row PASSES only because it re-exposes the fished `1051.8` (fault #4). |
| `ATOMICUS/tools/structural_analysis.cpp` | ✅ BUILD_EXIT=0 | ✅ | **YES** — 126/126 zk²=1, 13/13 Z², 12/12 Rydberg, 27/27 grammar, Fe-56 & golden-boundary CONFIRMED — all reproduced. Report is honest that zk²=1 is "an algebraic identity." |
| `Hubble/tools/zk2_pantheon_proof.cpp` | ✅ BUILD_EXIT=0 | ✅ | **YES but it REFUTES the file's title** — see fault #1. Milne wins; SDT-B catastrophically rejected. |
| `Hubble/tools/zk2_exponent_derivation.cpp` | ✅ BUILD_EXIT=0 | ✅ | **YES** — prints its own honest "PARTIALLY CONSTRAINED / amplitudes fitted / not derived" verdict (fault #7). |

**Note on the "6903-node" claim in the brief:** no such literal count exists in ATOMICUS; the `structural_analysis`
report's real countable claims (126/126, 27/27, etc.) all reproduce. Claim appears to be a paraphrase; treated as
the report's pass-counts, which are genuine.

---

## Honest work (explicitly NOT faults — being fair)

- **De Rerum treatise** prints `[F!]` on its two identity rows (k_e e²=αℏc; l_P=√(ϟ·λ_p)) and states in-text
  they "MATCH numerically but are IDENTITIES, not derivations." That is model honesty, not overclaim.
- **`17_Pantheon_Proof.md §7`** transcribes the full ranking (Milne #1, SDT-B dead last) with "The data speaks.
  No model is assumed correct." The body is fair; only the *title* and the cherry-picked §5.3 line overreach.
- **`Papers/Depth_Closure_Theorem/01_THEOREM.md`** treats `GM/c²` correctly: `:56` "equals GM/c² as a
  *consequence*, not an input"; `:122` caveats "stated as future work." No GM smuggling.
- **`Theory/03_Open_Problems.md`** (apart from the `:3` "zero conceptual gaps" line) is otherwise honest —
  it labels the α-derivation a "Conjecture" and lists lattice sims as unbuilt.
- **`STRUCTURAL_ANALYSIS_REPORT §1`** pre-empts the IDENTITY-PASS charge by stating zk²=1 "holds by
  construction … The physical content is [the v↦(z,k) map]."

---

## Cascade root

The single highest-value root: the **fished `1051.8 MHz` Lamb constant** (`laws.hpp:1340`) is the same
fabrication the APS04 audit ran to ground, and it has **propagated** into the De Rerum treatise (Book II & III)
and the PV_canon compendium as a "0.57% native candidate PASS." Paying the root (retract 1051.8 → mark
PPT08 OPEN in `laws.hpp`, De Rerum, PV_canon) clears the downstream prose debts at once. **Reported only —
`laws.hpp`/`Laws/` are read-only; correction is owed to Harvey, not applied here.**

> **Prompt completion A** · **Region class: tools NATIVE/honest; prose carries 3 high OVERCLAIMs + 1 axiom-level
> IMPORT + 1 INCONSISTENCY** · **No FABRICATED tool found in region** · **Cascade root: laws.hpp:1340 fished
> Lamb constant (shared with APS04).**

— HUNTER · 2026-07-02
