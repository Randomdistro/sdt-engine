# NP03D — VERDICT

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (agent executor).
> **Tool:** `np03d_threading.cpp` → `np03d.exe` (MSVC 19.44, build exit 0, final run exit 0, 12 s).
> Real stdout: `np03d_results.txt` (final) and `np03d_results_run1.txt` (preserved fixed-orientation failure).
> Input: NP03C `np03c_topology.txt` (frozen).

## Dual verdict

- **Prompt completion: A** — a genuine intersection solver (not "rings parked outside"), with
  linking proof, dual-thickness fork, null control, and the full-fibration metric. The v4
  "feasibility theatre" is replaced by numbers.
- **Physics class: D (novel feasibility statement), CONDITIONAL — with two named OPENs.**
  - **Earned:** for every demo isotope (He-4, Li-7, C-12, O-16, Ne-20, Si-28, Fe-56), all
    Z electron paths thread the proton poloidal channels with **zero intersections** and
    |Lk| = 2 against their own trefoil — topological permission holds at thin-fibre scale.
  - **Owed (OPEN):** (1) the result flips to INFEASIBLE if the electron fibre is r_e-thick;
    which thickness is physical is exactly laws.hpp's `r_electron_body_open` OPEN.
    (2) a full Hopf fibration (all fibres pairwise linked) is NOT realised (0/508 pairs) —
    local threading is not a global fibration.

## Key numbers

| Metric | Result |
| --- | --- |
| D1 own-knot linking | 69/69 loops, Lk = ±2 exact (worst dev 0.0001) |
| D2 zero-intersection (thin fibre) | 7/7 isotopes PASS; tightest C-12: +0.0809 R_p loop–tube |
| D3 r_e-thickness fork | 0/7 feasible (worst −6.6 R_p) — r_e > R_p cannot thread |
| D4 null control | random loops intersect in all Z ≥ 6 cases (up to 14/26); construction 0 |
| D5 full Hopf fibration | 0/508 pairs linked — NOT MET, stays OPEN |
| Run-1 honesty | fixed orientation FAILED C-12/O-16 (−0.065/−0.070 R_p); pivot ADJ-001 logged |

## What this does and does not license

- Does: "Z electrons **can** be threaded without intersection through the NP03C topology at
  sub-channel fibre thickness" — a checkable, falsifiable geometric statement.
- Does not: any claim about electron dynamics, shell energies, or the NP03E mirror; any claim
  that the thin-fibre scale is the physical one (OPEN); any fibration claim.

## Files

- `np03d_threading.cpp`, `np03d.exe`, `np03d_results.txt`, `np03d_results_run1.txt`,
  `RUN_LOG.md` (pre-commitments, ADJ-001 pivot, §D seven questions).

---

## SUPERSESSION (same day, on Harvey's direction) — NP17 is the death knell

NP17 resolves that the nuclear electrons are **internal and shared between adjacent protons —
they ARE the binding** (shared-electron well, αℏc scale, deuteron to 1.1%). NP03D asked
whether electrons can thread **around the outside** of separated nucleon tubes: the question
itself stands on the killed pre-NP17 skeleton. The conditional feasibility result is therefore
**KILLED as posed** — it audited a geometry the theory no longer holds. What survives:
(1) the intersection/linking solver (Gauss linking, curve-clearance, orientation search) —
directly reusable for the REAL question NP17 poses (can shared-electron nodes sit in the
interleaved-trefoil gaps without tube intersection?); (2) the D3 scale fact that an r_e-thick
fibre cannot occupy fm-scale channels — consistent with the internal electron being a compact
node, not an atomic-scale loop (stated as consistency, not spin).

**Prompt completion A (as spec'd) · Physics class: solver machinery earned; feasibility claim KILLED as posed (superseded by NP17 internal shared electrons) · Recovery PARTIAL (re-pose threading as NP17 shared-node clearance on the interleaved geometry) · Cascade root NP17-packing-order (shared with NP03B, NP03C); electron-body-radius OPEN unchanged**
