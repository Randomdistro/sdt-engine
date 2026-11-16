# Outstanding Closure Batch — Pre-registration (Iteration 44)

**Date:** 2026-08-13  
**Canon edits:** none  
**Upstream:** Iteration 43 reopen conditions (new ontology/data — not a rerun of L1–L10 / E1–E9 / DAT9 Fbias hunt)

## Scope

| ID | New claim under test | Labels |
|---|---|---|
| NU02 | Ergodic 3-pitch occupation (W=0) ⇒ CC/NC = 1/3, NC/SSM = 1, no PDG mixing | `APPEARANCE_CONDITIONAL` / `PITCH_MAP_EXCLUDED` |
| CK02 | Bulk `n` from packing identities in `laws.hpp` (no lab n in formula) | `PACKING_NUMERIC_MATCH__CONSTITUTIVE_OPEN` / `CONSTITUTIVE_STILL_OPEN` |
| NSEQ14 | Contact energy = Law-III `F_occlusion × r` at nuclear lengths (no B_d leak) | `CONTACT_ENERGY_SURVIVES` / `UNDERDETERMINED` |
| OM04 | RSR *payload* vs label census; residual definition still DAT9 | `RSR_PAYLOAD_ABSENT` / `DEFINITION_STILL_BLOCKED` |

Not in this batch (still parked / author-gated):

- MM04 koppa Law-III — no new axiom supplied  
- AS02 discrete action — no new axiom supplied  
- PSP02 TNF — not staged  
- `laws.hpp` D42 comment — no approve phrase  
- GOM06 GW — still route-to-attempt; not a one-pass combinatorial screen  

## Gates

| ID | Hold-out | MATCH |
|---|---|---|
| NU02 | SNO CC/SSM ≈ 0.34, NC/SSM ≈ 1 | \|Pee−0.34\| < 0.15 **and** NC=1 (not 1/3) |
| CK02 | water n_D = 1.3330 (OBSERVED) | \|log10(n_cand/n_obs)\| < 0.05 **and** formula uses no lab n |
| NSEQ14 | NSEQ09 SEAL medD = 4.242 MeV | rel < 0.15, no B_d/B_t import |
| OM04 | `.1A1` / `.rsr` next to SCE1 labels | payload present ⇒ inventory PASS; EMPIRICALLY SURVIVES still forbidden without DAT9 close |

## Forbidden

- PDG mixing as SDT derivation (NU02 control column only)  
- Inverting observed n → z (CK01 circularity)  
- Binding-energy leaks (NSEQ13 E7/E8)  
- Fitting Ω or Fbias to ODF  
- Claiming koppa / A_s derived  
