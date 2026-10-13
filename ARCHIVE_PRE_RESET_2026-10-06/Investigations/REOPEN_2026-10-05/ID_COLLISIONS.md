# Id collisions found 2026-10-05 (propose-only; no folder is renamed)

An id used by more than one investigation folder makes every dependency edge written with that id ambiguous. Until renames are decided (Harvey), edges and records here use `id` + a suffix.

| Id | Folder a | Folder b | Suffix used in the reopen |
|---|---|---|---|
| FLM15 | `01_Foundations_and_Lattice_Mechanics/FLM15_Casimir_as_Relay_Exclusion` | `01_Foundations_and_Lattice_Mechanics/FLM15_Influx_Phase_Resistance_Ratio` | FLM15-cas / FLM15-inf |
| NP21 | `05_Nuclear_Physics/NP21_AME2020_Geometric_Floor_Reproduction` | `05_Nuclear_Physics/NP21_Binding_Curve_Resistance_Landscape` | NP21-ame / NP21-bcr |
| GD06 | `08_Galactic_Dynamics/GD06_Collective_Displacement_Redshift_Law` | `08_Galactic_Dynamics/GD06_Gravitational_Lensing` | GD06-cdr / GD06-lens |
| Outstanding | `00_Master_Cascade/Outstanding_Closure_Iteration42`, `…43`, `…44` | | Iter42 / Iter43 / Iter44 |

Consequences already visible:
- The two-node cycle GD06 ↔ OP01 in the declared graph (and the OP01 → GD06 edge in the earlier dependency note) is the lensing folder only (GD06-lens). The OP01 prompt cites GD06 "cross-check only".
- FLM07's "FLM15 lock kernel" and "FLM15 R4 tests (11/11)" are FLM15-inf (Influx_Phase_Resistance_Ratio), not FLM15-cas.
- Dependency statements in `INVESTIGATION_STACK.md` that name FLM15, NP21 or GD06 need the suffix before they are used for ordering.
