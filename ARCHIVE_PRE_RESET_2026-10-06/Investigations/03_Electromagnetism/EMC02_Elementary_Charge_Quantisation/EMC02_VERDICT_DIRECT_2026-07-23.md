# EMC02 — Direct re-run verdict (2026-07-23)

> **Run class: DIRECT** (main session, no agents). Prior agent-era outcome files deleted
> 2026-07-23 (`INVESTIGATION.md`, `EMC02_CHARGE_DERIVATION.md`, `EMC02_VERDICT.md`,
> `emc02_results.txt` — git-recoverable). Tool: `emc02_charge_solver.cpp`, g++ 15.2 -O2,
> exit **0**. Output: `emc02_rerun_2026-07-23.txt` (162 lines).

## Prompt contraband check

`PROMPT.md` is **CLEAN** of rival axioms (ε₀/k_e appear as SI unit-bridges only; the
superconductor flux-quantisation reference is analogy, not mechanism). Hygiene note: the 2026-06-27
bulk template upgrade left prior phase-outcomes embedded in the prompt body — those claims were
treated as unverified and re-earned today.

## What the re-run measured

- **Candidate 1 (P_conv × ℓ_P⁴/ε₀): FAILS** — dimensionally incorrect, and requires ε₀ (which
  encodes e): circular at the dimensional level.
- **Candidate 2 (e = e₀·√Lk): DEFERRED** — dimensionally sound; blocked on the hydrogen linking
  number (PPT09) and a lattice-derived e₀.
- **Candidate 3 (e = √(αℏc/k_e)): exact to 3e-8 % but CIRCULAR** — the Coulomb identity is
  definitional; r_e = αℏ/(m_e c) *defines* α's conversion; requires PPT02 first.
- Dimensional closure: derivation basis {ℓ_P, c, ℏ, k_B, T_CMB} **cannot produce [A·s]** — no current
  dimension exists to build from. Confirmed by today's run.

## Verdict

- **Prompt completion: B** (all three candidates tested, dimensional analysis complete, path
  forward stated).
- **Physics class: OPEN (structural negative, honest)** — **e remains a Tier-1 measured input
  (unit-bridge)**. This is consistent with the EMC03 ontology: e is a *unit*, not a substance;
  "derive e" is a category error — the live target is the **redirection magnitude** (P_eff),
  which EMC04 now derives on framework terms.
- **Recovery:** n/a · **Cascade root:** PPT02/PPT09 (α and Lk) — both open.

*Consistent with the campaign doc's derivation basis note: no derivation basis member is claimed derived; e's
irreducibility here is a direct-run dimensional result, not an agent assertion.*
