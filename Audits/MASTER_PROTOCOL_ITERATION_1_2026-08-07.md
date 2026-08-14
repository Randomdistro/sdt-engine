# Master-Protocol Iteration 1 — 2026-08-07

**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Executable loop:** GOM25 (completed)

This record continues `Audits/MASTER_PROTOCOL_COVERAGE_2026-08-07.md` after dataset freeze, instrument validation, and direct execution.

## Whole-repository coverage ledger (inventory)

Tracked files: **2307**. Working-tree files by top-level region (includes untracked audit/dataset artifacts):

| Region | Files | Category | Authority | Active claims? | Data? | Generated? | Historical only? | Read status this cycle |
|---|---:|---|---|---|---|---|---|---|
| Investigations | 1293 | investigation prompts/tools/assessments | high for direct assessments | yes | some | mixed | no | solar chain + GOM25 executed; remainder inventoried |
| ATOMICUS | 465 | nuclear grammar + isotope DB | high within nuclear domain | yes | yes | reports regenerated | no | inventoried; not opened this loop |
| Release | 156 | public distribution mirror | low until source-of-record traced | yes (public) | no | largely derived | no | inventoried only |
| docs | 131 | public documentation | low (mirror) | yes (public) | no | derived | no | inventoried only |
| Experiments | 107 | experiment proposals | medium (predictions) | yes | some | no | no | E109 indexed |
| Hubble | 52 | cosmology tools/data | medium | yes | yes | mixed | no | inventoried |
| Datasets | 55 | manifests + raw caches | high for data provenance | no (inputs) | yes | no | no | solar_propagation frozen + checksummed |
| Compiler | 26 | tooling | low | no | no | no | no | inventoried |
| Papers | 22 | manuscripts | medium provenance | yes | no | no | no | depth-closure thread previously read |
| Audits | 18 | audit records | provenance / non-authoritative vs data | meta | no | no | mixed | today’s audits + this iteration |
| Laws | 17 | law manuscripts | high (propose-and-wait) | yes | no | no | no | not edited; not re-opened line-by-line |
| Engine | 9 | canonical headers | **highest** | yes | measured derivation basis | no | no | `depth_closure` + bridge solar symbols read |
| Theory | 9 | ruleset / open problems | high | yes | no | no | no | gateways applied; Theory files remain on standing read list |
| Benchmarks | 9 | suite | medium (detox required) | yes | no | no | no | prior adversarial run cited |
| Theory_SCT / other | <20 | alternate/historical | low | mixed | no | no | often | inventoried |

**Not silently omitted:** binary ZIPs (`ATOMICUS.zip`, website zips), `.audit-tmp` build outputs, and Cassini binary TDF are classified as binary/non-readable-as-text or raw instrument products. TDF is retained as PENDING_DATA pending decoder.

**AGENTS.md:** none present in this repository.

## Claim graph — highest-leverage unresolved roots

| Root ID | Claim family | Why highest leverage | Current status |
|---|---|---|---|
| R1 | Solar ϟ → spectral shift → `c_far` delay (coupled §XII) | Shared profile must earn all optical markers from one IC set | Spectral COMPATIBLE/UNADJUDICATED; delay PENDING_DATA; IC debt on instantaneous ϟ |
| R2 | Benchmark earned-count (B15/B16/B25 literals) | Inflates public prediction tallies without mechanism | FORMAL — literals; detox required |
| R3 | GOM22 constructed “measured” delay | Contaminates Shapiro narrative | FORMAL circularity; superseded by GOM25 D4 gate |
| R4 | Unguarded `c_far` for z>1 | Domain/branch defect in live engine API | FORMAL DEFECT |
| R5 | Blueprint missing ICs (Φ-rate, N map, eta_slip, …) | Blocks empirical adjudication of blueprint prose | UNADJUDICATED / FORMAL (prior observational addendum) |

## Iteration 1 execution checklist

1. Coverage ledger — this file + prior MASTER coverage  
2. Claim graph roots — table above  
3. Highest-leverage root selected — R1 (GOM25)  
4. Pre-registration — `GOM25/.../PROMPT.md`  
5. Instrument validation — PASS (A/B/C)  
6. Execute — `.audit-tmp/gom25_run.txt`  
7. Audit — `GOM25_ASSESSMENT.md`  
8. Reformulation — orbital-invariant ϟ proposed; **OPEN** (not re-audited as adopted)  
9. Cascade — assessment §18  
10. Next test — Cassini ATDF decode + geometry (D4)

## Framework-level statement (required form)

This iteration does not conclude that SDT is true or false, nor that it matches or fails a competitor theory. The ledger state after Iteration 1:

| Bucket | Entries |
|---|---|
| Empirically surviving predictions | (none newly earned) |
| Empirically excluded predictions | (none in GOM25) |
| Formal defects | unguarded `c_far` (z>1); benchmark literals B15/B16/B25; GOM22 constructed delay |
| Identities / leading-order approximations | `shapiro_delay` ≈ weak-field `c_far` integral |
| Calibrated correspondences | (none introduced) |
| Unadjudicated claims | solar spectral depth map (nuisance-limited) |
| Open mechanisms | solar ϟ orbital invariant; endpoint sync for external-frame speed |
| Active discriminating predictions | exact vs leading delay (too small in solar WF); NS-surface / horizon fork (prior) |
| Coverage gaps | admissible ranging residual; deflection vs impact parameter; whole-repo claim extraction beyond solar chain |
| Next tests by information value | (1) Cassini residual reconstruction (2) invariant-ϟ re-run (3) deflection scan (4) benchmark detox |
