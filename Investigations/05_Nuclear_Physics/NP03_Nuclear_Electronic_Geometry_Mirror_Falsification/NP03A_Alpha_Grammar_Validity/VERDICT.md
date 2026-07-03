# NP03A — VERDICT

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (agent executor).
> **Tool:** `np03a_grammar_validity.cpp` → `np03a.exe` (MSVC 19.44, exit 0). Real stdout: `np03a_results.txt`.

## Dual verdict

- **Prompt completion: A** — all fixed metrics run, null control run, decay-vector table emitted for NP03E.
- **Physics class: IDENTITY (transform) + OBSERVED-consistency (wedge membership).**
  - Earned: the implementation is certified correct end-to-end (P2: 4186/4186 inverse-exact;
    P3: 16744/16744 decay-vector closures), and the natural-isotope wedge membership is
    re-confirmed (284/287, exceptions exactly H-1, H-2, He-3).
  - NOT earned (and not claimed): any geometry. Claim 1 is arithmetic; per the parent prompt it
    "proves NO geometry". Rule 18 is untouched by this result.

## Key numbers

| Metric | Committed gate | Result |
|---|---|---|
| P0 aggregate static_asserts | 7/7 (compile) | PASS — 287/284/3/7658/5228/2560/108 exact |
| P1 natural-basis validity | 284/287, exceptions = {H-1,H-2,He-3} | PASS, 0 inverse failures |
| P2 wedge inverse identity | 0 failures | PASS — 4186/4186 [IDENTITY] |
| P3 decay-vector closure | 0 mismatches | PASS — 16744/16744 [IDENTITY] |
| P4 null control | < 1e-3 accidental | PASS — 2.684e-4 (= chance level 1/3721) |

## What this does and does not license

- **Does:** downstream NP03B may consume `(n_d, n_t)` counts as certified inputs; NP03E may use
  `np03a_decay_vectors.csv` for its count/closure metric.
- **Does not:** license any statement about nuclear shape, electron shells, or the mirror.
  Selling P2/P3 as predictions would be an IDENTITY-PASS — they are labelled as identities in
  the tool output itself.

## Files

- `np03a_grammar_validity.cpp`, `np03a.exe` (build exit 0), `np03a_results.txt` (run exit 0),
  `np03a_decay_vectors.csv` (284 rows), `RUN_LOG.md` (pre-committed gates + correction note).

---

**Prompt completion A · Physics class IDENTITY (transform) + OBSERVED-consistency (wedge membership) · Recovery n/a (no fail — all pre-committed gates passed) · Cascade root none**
