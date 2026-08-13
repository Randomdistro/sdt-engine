# NSEQ08 Pre-registration — shared doublet-ray invariant

**Date:** 2026-08-09  
**Parent:** NSEQ06-C2 (complementarity EXCLUDED: ∩=4, ∪=8); NSEQ07-C4
(each doublet = QQ⊕S)  
**Objective:** With edge-class provenance, classify the four rays shared by
both polar branches and the two private rays of each branch. Test whether
the shared set is a fixed geometric invariant of the cuboct face graph
(independent of branch choice).

## Hypotheses

**H1 — Shared cardinality.** Directed doublet-ray intersection has size 4;
union size 8 (NSEQ06, reconfirm).

**H2 — Shared = edges in both QQ selections.**  
Every shared doublet ray’s Q−Q edge lies in `QQ_triangles ∩ QQ_hexagon`.  
(If `|QQ ∩|≠4`, H2 as stated fails — record actual `|QQ∩|` and OPEN.)

**H3 — Private = branch-private QQ.**  
Each branch’s two private doublet rays use Q−Q edges outside the
intersection.

**H4 — Surface partners.**  
The surface edge in each shared doublet is the same across branches
(identical undirected surface edge), i.e. the invariant is a set of
four fixed (QQ_shared_or_partner, S) pairs — or, if QQ sets intersect in
fewer than 4, the shared *rays* still reuse identical surface edges.

## Decision

- SURVIVE if H1 holds and (H2∧H3) **or** a single clear corrected invariant
  from H4 is stated with counts.
- EXCLUDE if intersection cardinality ≠ 4.
- OPEN if counts match but no unique edge-level invariant closes.

## Non-goals

No emission physics claim; no capacity change; no averaging of branches.
