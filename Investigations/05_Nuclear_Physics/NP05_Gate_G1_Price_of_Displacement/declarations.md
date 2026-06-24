# CQ-32 · STAGE 1 — Block Topology Declarations (FROZEN, blind to energies)

Made in ignorance of all binding energies (R1). Radii from the W+1 rule, computed in `stage2_volumes.py`.
Every choice is a ledger entry (R2). Decision points D1, D2 resolved with the alternate named for Stage 6.

## Decisions
- **D1 (neutron):** primary = **merger model** — a single genus-1 composite (W=3 with a merged W=1), mass m_n,
  treated as one tube for volume. Alternate (commuter) → Stage 6 sensitivity.
- **D2 (composites):** primary = **linked-tube model** — constituent tubes retain identity, linking number Lk
  recorded. Alternate (fused single re-knotted tube) → Stage 6. Justification: the linked model is
  parameter-free from the W+1 radii; the fused model needs a fused-radius rule that routes through the bound
  mass (circular vs binding). Linked first.

## Free tubes (genus 1 throughout — Genus Selection)
| block | W | (p,q) | a_tube (fm) | R_ring (fm) | V_free (fm³) | r_c conscription (fm) |
|------:|--:|:-----:|:-----------:|:-----------:|:------------:|:---------------------:|
| proton  | 3 | (2,3) | 0.8412 | 1.0303 | 14.392 | 2.818 |
| neutron | 3 | (2,3)+W1 merged | 0.8401 | 1.0289 | 14.333 | ≈2.818 |
| electron| 1 | (1,1) | 772.4  | —      | —      | — (UNDER TENSION 10^5.9 vs scattering; logged, not used in nuclear volumes) |

`a = (W+1)ℏ/(mc)`, `R = a/√(2/3)`, `V = 2π²Ra²`. `r_c = R/ϟ²` = nucleon c-boundary = 2.818 fm [corpus].

## Composite blocks (linked, Lk recorded; arrangement for the conscription-overlap)
| block | content (n_p,n_n) | topology | arrangement | structural facts licensed (no energies) |
|------:|:-----------------:|:---------|:------------|:----------------------------------------|
| d   | (1,1) | p ⊕ n, Lk=1 | prolate/oblique unlike-pair (shallow) | deuteron stretched/oblique |
| t   | (1,2) | p ⊕ 2n, Lk | deep **nn dyad** (paired neutrons) | t has a deep like-pair |
| h   | (2,1) | 2p ⊕ n, Lk | pp pair + n | He-3 core |
| α   | (2,2) | 2p ⊕ 2n | **tetrahedral** (4 vertices) | α presents NO free gears (Be-8 unbound — structural) |
| ⁶Li | (3,3) | **α ⊕ d** cluster | α core + linked d | cluster grammar (NP01) |
| ⁹Be | (4,5) | **2α ⊕ n** | two α + bridging n | cluster grammar |

## LOAD-BEARING OPEN (the pivot of Gate G1)
Stage 2 shows binding = **conscription-overlap deficit** (Candidate B), set by the **inter-block centre
separation `s`**. `s` is parameter-free ONLY if derived from **tube-contact / gear-mesh geometry** — NOT from
measured charge radii (the already-failed 9.3× path, instrument output). Primary rule to test: tube-surface
contact (s from a_tube, R_ring). **This is where Gate G1 stands or falls**, and it is the same unbuilt
mesh-geometry as the stack's ROOT-SIM. Declared as the investigation's pivotal input; FROZEN.
