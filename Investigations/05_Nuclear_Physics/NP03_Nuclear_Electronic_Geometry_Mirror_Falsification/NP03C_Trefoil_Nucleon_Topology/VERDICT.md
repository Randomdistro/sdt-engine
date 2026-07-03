# NP03C — VERDICT

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (agent executor).
> **Tool:** `np03c_trefoil_topology.cpp` → `np03c.exe` (MSVC 19.44, build exit 0, final run exit 0).
> Real stdout: `np03c_results.txt`. Output: `np03c_topology.txt` (input to NP03D).
> Input: NP03B `np03b_positions.txt` (frozen, hash-verified).

## Dual verdict

- **Prompt completion: A** — every fixed metric executed with numeric checks; two
  instrumentation faults found on the first run were traced to root and corrected
  (ADJ-001 epsilon-vs-scale, ADJ-002 crossing-on-endpoint degeneracy — see RUN_LOG).
- **Physics class: B (internal embodiment).** Topology imposed on frozen NP03B positions.
  Rendering is not evidence and none is claimed; the deliverable is the checked substrate.

## Key numbers

| Gate | Committed | Result |
| --- | --- | --- |
| C0 input integrity | hash match | 6/6 MATCH (He-4: n/a, no blocks) |
| C1 zero position drift | < 1e-12 | max 2.22e-16 (machine floor) PASS |
| C2 knot closure + crossings | closure < 1e-9 R_p; count == 3 | 69/69 knots, count range [3,3] PASS |
| C3 tube non-degeneracy | self-dist ≥ 0.16 R_p | 0.1840 R_p PASS (thin margin, reported) |
| C4 radial orientation | axis·û > 1−1e-9 | 1.000000000000 PASS |
| C5 R_p scale + clearance | clearance ≥ 0 all pairs | worst +0.0295 R_p (C-12) PASS |

R_p = 8.414e-16 m from `laws.hpp::measured` (boundary radius — never "charge radius");
W+1 value 4ℏ/(m_p c) = 8.412356e-16 m echoed for reference only.

## Declared simplifications (inherited by NP03D, not hidden)

- One trefoil per block (the block's proton); triton/deuteron internal neutrons not resolved.
- Alpha core = 2 proton trefoils at ±0.5 R_p on +Y (the NP17 interleaved-lock geometry is NOT
  reproduced here; it is not needed for the drift/threading metrics).
- R_t = 0.6 R_p, a_t = 0.2 R_p, r_tube = 0.08 R_p — representation choices declared pre-run.

## Files

- `np03c_trefoil_topology.cpp`, `np03c.exe`, `np03c_results.txt`, `np03c_topology.txt`,
  `RUN_LOG.md` (ADJ-001/002 + owned premise-error on the self-distance bound).

---

## SUPERSESSION (same day, on Harvey's direction) — NP17 is the death knell

NP17's RESOLVED packing order is **interleaved** trefoils sharing internal electrons — tubes
threading one another, electron nodes in the gaps, alphas at icosahedral interstices. NP03C
placed **non-interleaved** trefoils at ≥ 2 R_p separation on the (now killed) NP03B ball
positions: geometrically valid knots on the wrong skeleton. The knot-validation machinery
(closure, crossing count, self-distance, clearance audits) survives and is directly reusable
on the NP17 imported geometry (`trefoil_mappings.json`); the emitted `np03c_topology.txt` is
**dead as nuclear structure** and must not feed NP03E.

**Prompt completion A (as spec'd) · Physics class: knot-audit machinery earned; embodiment KILLED (superseded by NP17 interleaving) · Recovery PARTIAL (re-run the same audits on NP17 geometry) · Cascade root NP17-packing-order (shared with NP03B, NP03D)**
