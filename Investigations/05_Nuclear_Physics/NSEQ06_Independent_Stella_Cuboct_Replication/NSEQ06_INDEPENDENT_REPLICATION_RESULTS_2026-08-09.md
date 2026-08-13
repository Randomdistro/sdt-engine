# NSEQ06 Results — Independent Stella/Cuboct Relation Replication

**Date:** 2026-08-09  
**Scope:** formal/combinatorial audit; no empirical data were downloaded or fitted  
**Canon edited:** no  
**Verdict:** `FORMAL_RELATION_REPRODUCED_ONLY`

## Provenance and correction trail

The source-registered independent script is
`nseq06_independent_replication.py`. Its SHA-256 is
`e057da6d6c25cae16cbef97a1c0d93097abf6728a214d41da0feaa27d24407b9`.
All frozen inputs matched after Amendments 01 and 04; the accepted current-canon
result JSON has file SHA-256
`61bc555815cdae29e1057290f089ac12ea07d8ea9e17f653473f42ab094d969e`
and canonical-payload SHA-256
`cc74cd209ecdb2dca53c907090a8d186d61e357d49e8c45e9ed36bae9938cbf8`.
Two consecutive executions produced byte-identical JSON.

The first output was invalidated before acceptance. Amendment 02 records the
two errors: NSEQ06 incorrectly assembled the expected cuboctahedral direction
set, and it added an unregistered expectation of three symmetric Q-Q choices.
Both were auditor implementation errors, not model failures. The corrected run
is the only result used below.

After that accepted run, `laws.hpp` changed its shell identifiers and prose.
Amendment 04 re-froze the new canonical hash and reran the independent audit;
the numerical formal gates are unchanged. The new prose is not accepted as a
mechanism derivation merely because it has entered canonical comments.

## Formal gates

| Gate | Result | Independent result |
|---|---|---|
| F1 | PASS | The proposed pure sequence expands the already-coded grouped ledger: `20→28→40→50→70→82→112→126→168→184`. |
| F2 | PASS | Eight cube/stella directions have 12 nearest links. Their normalized midpoints are exactly the 12 cuboctahedral directions, with body-diagonal latitude census `3/6/3` at `−54.7356°/0°/+54.7356°`. |
| F3 | PASS | The cuboctahedron has 14 face-normal directions: eight triangular/body-diagonal and six square/axis directions. About a body-diagonal pole the census is two poles, six at `±19.4712°`, and six at `±35.2644°`. |
| F4 | PASS | The incidence construction has 24 T-Q edges, 12 T-T edges, and 12 possible Q-Q edges. Exhaustive enumeration finds 20 Q-Q degree-two selections; under the pre-registered `C3 × inversion` condition exactly two remain. Both produce a connected 14-node, 42-edge, 6-regular graph. |
| F5 | OPEN | `42 > 3×14−6 = 36`; the D42 graph cannot be a simple planar/surface-contact graph. A non-planar 3D contact mechanism is still required. |

The two `C3 × inversion` selections are one pair of opposite-sign triangles and
one mixed-sign six-cycle. Therefore the proposed **two-branch count is formally
reproduced under that explicit symmetry condition**. The symmetry condition is
not, by itself, a physical rule selecting either branch.

## What is corrected

| Earlier statement | Corrected status | Reason |
|---|---|---|
| `+D+T` groups must mean a single mixed shell | `FORMAL_BOOKKEEPING_CLARIFIED` | The existing capacity formulas can be algebraically expanded into alternating pure D/T increments after 20. This clarifies notation only. |
| T8 stella, D12 edge-midpoints, and T14 face-normal counts | `FORMALLY_REPRODUCED` | The vector and incidence counts are exact. |
| "two polar branches" | `FORMALLY_REPRODUCED_UNDER_C3_X_INVERSION` | The complete degree-two enumeration has 20 choices; the stated symmetry reduces these to the two documented graph types. |
| The alternative `12,16,20` face sequence is physically excluded | `NOT_ESTABLISHED` | It is an ad hoc arithmetic continuation that differs from an already-coded ledger. No complete competing physical geometry, formation rule, or observable was specified, so a non-match does not exclude all face-based mechanisms. |
| `F/B/R` count agreement derives nuclear closures | `NOT_ESTABLISHED` | The audit verifies identities among literals and formulas in `laws.hpp`; it does not derive why the occupied shells, closure locations, or contact graph occur. |

## What remains unresolved

The valid formal relations do **not** repair any of the following empirical or
mechanism gates:

| Item | Existing status retained | Why NSEQ06 cannot clear it |
|---|---|---|
| NP12b charge-radius comparison | `PROXY_REPRODUCED_UNDER_UNDERIVED_SURFACE_CHARGE_MAPPING`; physical law `UNADJUDICATED` | A direction/count construction does not provide a boundary-to-RMS charge measurement map. |
| NP30 contraction/closure root | `OBSERVATIONAL_REGULARITY_REPRODUCED_MECHANISM_UNADJUDICATED`; closure locations empirically imported | The cube/cuboct construction is not an executable derivation of N=28, 50, or 82 from SDT primitives before the labels are used. |
| NP32 scission selection | empirical SDT verdict `UNADJUDICATED` | There is still no zero-fit executable graph, contact cost, cut, and partition calculation. The N=82/Z=50 anchor remains imported; historical P3 also fails its own every-system gate. |
| NSEQ04 binding energy | `CALIBRATED(1)`, fails as a per-nucleon account | No energy, mass, or uncertainty calculation appears in a count/incidence proof. |
| Other attachment claims (lensing, timing, particle, neutrino, Cherenkov) | `EXTERNAL_TRANSCRIPT_UNVERIFIED` | The attachment supplies no frozen local observational datasets and executable analyses for them in this checkout. |

## Required next mechanism gate

To promote this formal result, freeze a native model that specifies: the
physical object at each graph node, an allowed contact relation and energy,
which of the two Q-Q branches is selected and why, a transition/occupation rule
for the `T_n` and `D_n` sequence, and a derivation of closure locations without
inserting their observed values. It must then predict a declared nuclear
observable on a source-registered holdout set. Until that exists, this branch
may improve nomenclature and internal consistency but cannot be called a
physical closure, binding, radius, or fission prediction.
