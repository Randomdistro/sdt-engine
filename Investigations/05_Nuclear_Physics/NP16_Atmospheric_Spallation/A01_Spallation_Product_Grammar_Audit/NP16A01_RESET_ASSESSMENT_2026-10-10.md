# NP16A01 — Spallation product grammar audit: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0.

**Read:** PROMPT.md, DATA_REQUIREMENTS.md, CLAUDE.md (grammar), graph_v2.json. No old record exists in this folder.

## Registration (fixed before the instrument)

**Data substitution (stated).** The prompt asks for EXFOR's catalogue of measured (p,xn) reactions, which is not in the repo.

**Registered substitute:**
- **Targets:** every NUBASE2020 ground state with Z = 3–92 that is stable ("stbl") or has a natural abundance ("IS=").
- **Products:** (Z_t + 1, A_t + 1 − x) for x = 1–10, kept if the nuclide exists in NUBASE.

This is the set of **kinematically listed (p,xn) products**, not the set of measured ones. A product counted here may never have been measured, and the result is labelled accordingly.

**Grammar (canonical, CLAUDE.md).** n_tri = A − 2Z and n_deu = 3Z − A − 2. Valid if both are ≥ 0, which is equivalent to Z ≤ N ≤ 2Z − 2.
- **Conservation check on every row:** A = 4 + 2n_deu + 3n_tri and Z = 2 + n_deu + n_tri.
- Also reported: validity under the EC alternate (n_t = A − 2Z + 1, n_d = 3Z − A − 3) for steps whose decay is EC/β⁺.

**Decay chains.** Follow NUBASE's dominant decay mode until the first stable or naturally abundant nuclide.
- Modes: B+/EC → (Z − 1, A); B− → (Z + 1, A); A (alpha) → (Z − 2, A − 4); p → (Z − 1, A − 1); n → (Z, A − 1).
- Cap of 40 steps. A mode not in this list ends the chain as "untracked", and the count is reported.

**Prompt criteria (carried).**
- **C1:** grammar validity at every step, 100%. Any exception is a finding.
- **C2:** neutron-budget identity N_endpoint = N_target, reported as a fraction (the prompt's "~100% for pure (p,xn) chains").
- **C3:** grammar trajectory rules. EC: Δn_tri = +2, Δn_deu = −3. β⁻: Δn_tri = −2, Δn_deu = +3. These are checked as arithmetic.

**Label, fixed now (NP24).** Grammar validity is a band in (Z, N). This audit therefore maps where the products sit relative to that band. It is not independent evidence for the grammar's physics.

**Validations:**
- V1: ⁶⁸Ga(p,2n): the target is not stable, so use the prompt's own example, Ga-69(p,2n) → Ge-68. Check the product grammar arithmetic and the chain Ge-68 → Ga-68 → Zn-68 (stable), with N_target = 38 = N_endpoint.
- V2: the conservation identities hold on 1000 random (Z, A).

## Run and results
(below)
- Instrument: `np16a01_reset_1.py`; output in `np16a01_reset_1_results.txt`. Single pass. V1 and V2 met.
- **Population:** 284 stable targets (Z = 3–92); 2,655 (p,xn) listings with x = 1–10 that exist in NUBASE; 1,003 unique products.
- **Chains:** 927 end at a stable nuclide; 76 are untracked (a dominant mode outside the registered list).

**C1, grammar valid at every step: NOT MET.**
- 270 of 3,195 chain steps are invalid (8.5%).
- 194 of 1,003 products have at least one invalid step (19.3%).
- Every exception is proton-rich, N < Z (n_tri < 0). Examples: ⁵Be, ⁶Be, ⁷Be, ⁶B, ⁷B, ⁸B, ⁹B, ⁸C, ⁹C, ¹⁰C.
- Under the EC alternate grammar, 93.9% of EC/β⁺ steps are valid. The remainder are the N < Z − 1 cases that NP40 already found.
- **G1 for "100% validity", as registered.** The grammar's band does not contain the proton-rich side of the (p,xn) product set.

**C2, neutron budget N_end = N_target: 349 of 2,475 pairs (14.1%).**
The distribution of N_end − N_target runs from −22 to +1, with modes at −2 (468) and −4 (417). Chains stop at the stable isobar of A_p = A_t + 1 − x, which usually sits at lower N than the target. The E20 identity holds for a minority of pairs; it is not a general law of (p,xn) chains. **G1 for "~100%".**

**C3, trajectory arithmetic: met** (0 violations). The EC and β⁻ grammar steps are exact consequences of the formulas, so this is construction (it cannot fail).

**Labels.** Every count here is a function of (Z, N) (NP24): shared-input, a map of where products sit. The product set is the kinematically listed (p,xn) set existing in NUBASE, not EXFOR-measured reactions; that is a stated data substitution.

**Grades:** C1 G1 · C2 G1 · C3 construction.

**What would open it:**
- the EXFOR-measured product list (to confirm that the N < Z exceptions are actually produced, which ⁷Be, ⁸B and ⁹C are in nature);
- a native construction for N < Z nuclides (the constitutional question NP40 also raised).

## Comparison with the archived record
Deferred.
