# Source manifest

Opened 2026-10-27. Repository head `5b3e0c1`. One row per source cited by a drafted chapter. SHA-256 is of the working-tree bytes read on the date above. A source marked MODIFIED differs from head and is cited at its working-tree state.

| path | sha256 | git state | cited by | role |
|---|---|---|---|---|
| `Engine/include/sdt/laws.hpp` | `2154c01eb01ebab82daf8ea43f66ec842fd0e3377b098e404dcde490fec8f33e` | tracked, MODIFIED (working-tree blob `c855765`, head blob `7937ea5`) | Ch 4 | engine reference; lines cited are working-tree lines |
| `Theory/00_Ruleset.md` | `b4d4bf7c6e669d7add9f119c9253b054d691e84a2729f856a9eb585e97d0a41d` | tracked, clean | Ch 4 | axioms R1–R6, theorems T1–T17 |
| `Theory/04_Notation.md` | `9450e9c4d3333c78805108849e45df5b6ea27e895d4367021770f063ac5dfb4d` | tracked, clean | notation ledger | ℶ, k, z assignments |
| `Laws/SDT_Complete_Laws.md` | `e02d01cb4dd4ef95fb78ec2513c143b2c41213195f4b3813f4ad7cbfd92cac25` | tracked, clean | Ch 4 | Lemma 1–2, Theorems 1–2 (§4–5) |
| `Laws/Law_I_Cosmological_Relay_Throughput/LAW_I_COSMOLOGICAL_RELAY_THROUGHPUT.md` | `ee27117ee5c9b4ba7092f4431e4647ffa2af510f177c69727bda510c3706b918` | tracked, clean | Ch 4 | R1–R6 (§7), shell cancellation (§8) |
| `Engine/include/sdt/sphere_frame.hpp` | `487e4bb41786658f73f4137dfd513046fb2043cf1f1f98f800305ef84892743b` | untracked | Ch 2 (later), Ch 58 | `Locus` excludes $r=0$ (line 44) |
| `docs/SDT_TEXTBOOK_ARCHITECTURE.md` | `aabbcc4620a71518392308d3aaec5c025d0272dcde00ffdf3f04b095e2e72bcd` | untracked | notation ledger | earlier architecture plan of the same date |
| `GATEWAY_BEHAVIOURAL.md` | `0226bbb3b754b9b85b0290596c8ecfcd212d372564d4f5847d841bff5c2be15a` | tracked, clean | conduct | register and conduct |
| `GATEWAY_PROCEDURAL.md` | `8bc093f8df2cd5ad87a3a1304fe3a011a1b65c401ab038b5d174e7d2e5f46bc8` | tracked, clean | procedure | pre-registration, instrument validation |

Textbook files produced with this manifest:

| path | sha256 |
|---|---|
| `Textbook/examples/ch04_shell_cancellation.cpp` | `48982b1cc1411804bddeb64df6fbe9f964e779d6f57a2551ea6d574c083e6454` |
| `Textbook/validation/ch04_run1_output.txt` | `9f86b47cb225669946868f1216430dd7b0fd66cecc557695fc3fd434f24d80b7` |
| `Textbook/validation/ch04_run2_output.txt` | `15bbccf6bbf47acd3b1733962476a996741e0c2c1fd04d44a47e82fc6be62389` |

(The `.cpp` hash is of the file as run for `ch04_run2_output.txt`. A function rename after that run was followed by a rebuild and rerun; the output was byte-identical. Run 1 was produced by the earlier T5 routine described in Chapter 4 §4.8.)

## Chapter 9 (added 2026-11-03)

Repository head `7b49eb7`. `Engine/include/sdt/laws.hpp`, `Theory/00_Ruleset.md` and `Laws/SDT_Complete_Laws.md` are tracked and clean at the hashes in the table above (unchanged since Chapter 4; `laws.hpp` was committed in `7b49eb7`). Lines cited in Chapter 9 are those of that file: `law_III::F_occlusion` 535, `solid_angle_occluded` 567, `solid_angle_cap` 578, `cap_over_projected` 587, the `law_IV` $P_{\rm cf}$ comment 607, `law_I::P_conv` 288.

| path | sha256 | git state | cited by | role |
|---|---|---|---|---|
| `Projects/sdt-investigations/Investigations/SDT_Traction_Normalisation_2026-10-27_2/TRACTION_ASSESSMENT2.md` | `f704c81ac00ff636483a2f9ac2c5e7a3a51deedaf53eef93fe697f96123690ad` | untracked | Ch 9 | retrieval lead: factor-six discrepancy; $P_{\rm conv}$ against microwave radiation pressure |
| `Textbook/validation/ch09_PRE_REGISTRATION.md` | `12ad698f6b203bdb425de0dff431a1aecf877a17e5ad449d765dee0ae986decb` | untracked | Ch 9 | criteria registered before the instrument |
| `Textbook/examples/ch09_directional_convergence.cpp` | `e396eb57eb6217acc402810beb42cdfe7acff8d60f8cc0644ec51244d128b809` | untracked | Ch 9 | instrument, as run |
| `Textbook/validation/ch09_run1_output.txt` | `5848e3742c46753f4aecbd29c4d36306950d2124adf0c18e190513bcb36e6f2f` | untracked | Ch 9 | captured output of the single run |

## Unavailable or unresolved

- `ATOMICUS/` is not present in the working tree (it appears among the deleted paths in `git status`). The plan's 287-isotope catalogue (Chapters 20–24) cannot be resolved from the working tree on this date; the archive or the last commit that held it is to be identified in Stage A before those chapters are drafted.
- `Experiments/`, `Hubble/` and other folders named in `CLAUDE.md` are likewise absent from the working tree.
- `Projects/sdt-investigations/…` (the Spaz runs) was not read for Chapter 4.
