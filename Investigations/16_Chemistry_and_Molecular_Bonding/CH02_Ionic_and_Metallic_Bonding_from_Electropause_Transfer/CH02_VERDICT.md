# CH02 — VERDICT: Ionic & Metallic Bonding from Electropause Transfer

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05 · Tool: `ch02_ionic_metallic.cpp` (exit 0) · Output: `results.txt` (verbatim stdout)
**Grounding:** NP17 shared-electron machinery (Σ±αℏc/r point sources); CH01 electropause-balance branch is the dead branch. Machinery only — no rival machinery anywhere in the chain.

## Results (all committed pre-run in RUN_LOG.md)

| Phase | Result | Gate | Call |
|---|---|---|---|
| P1 transfer split | 15/15 correct; **clean gap** — max covalent Δχ 1.114 eV < min ionic Δχ 3.717 eV (threshold non-critical across a 2.6 eV window) | ≥13/15 | **PASS** |
| P2 NaCl lattice energy | Evjen geometric sum **M = 1.747574** (pure lattice geometry; literature 1.747565 is a cross-check, not input) → **861.0 kJ/mol** vs 787 (**+9.4%**) | ±15% | **PASS** |
| P4 novel KCl | **771.8 kJ/mol** vs 715 (**+7.9%**), same formula, no refit | ±20% | **PASS** |
| P4 stress MgO | **4611.6 kJ/mol** vs 3791 (**+21.6%**) | ±20% | **FAIL** (reported) |
| P3 metallic Na | occlusion-only cohesion **6.231 eV/atom** vs 1.113 (**+460%**) | ±25% | **FAIL → OPEN** |

The earned content: the Madelung-analogue is **computed from lattice geometry** (six expanding Evjen cubes shown converging), the coupling is the engine's `αℏc` (class F identity, declared), and the systematic **+8–10% overshoot on the 1:1 salts is the fingerprint of the one underived term** — the short-range contact repulsion.

## Falsification table (updated)

- Transfer = deeper-well migration: **survived** (15/15, gap clean; symmetric pairs cannot transfer — no direction).
- Lattice = geometric occlusion sum: **survived at 1:1 charge**; sign correct; MgO (2+/2−) exceeds tolerance.
- Metallic = delocalised sea: **not survived as electrostatics-only** — OPEN, not killed: no rival machinery was used to fail it; the committed native gate (25%) failed.
- Firewall: no Coulomb/Madelung import — **held** (M computed; αℏc declared).

## FAILURE RECOVERY (§D seven questions)

**MgO (+21.6%):**
1. Why: overshoot grows with charge product (q²=4) — the missing short-range repulsion does more work in the stiffer 2+/2− lattice; sign right, magnitude high.
2. Recoverable: yes — by deriving the contact term, not by tuning.
3. Unaccounted: the energy cost of forcing two boundaries into contact (compression of the meshed region).
4. Errored premise: **point sources all the way to contact** — occlusion does not stay 1/r² at contact; it **saturates** (two-regime law, g→2; FARMER frame).
5. Freedom: a saturated-occlusion contact term (distance where the solid angle saturates).
6. Accounting: native — NP10's saturated solid-angle ledger / limited poloidal-rim contact (angle is the premium). Not a bare knob; not yet built.
7. Cascade: yes — shared root, see below. **Recovery: PARTIAL** (route + premise named; term not yet derived; re-open condition: NP10 saturated-occlusion run lands its lock ladder).

**P3 metallic (+460%):**
1. Why: the Wigner–Seitz occlusion sum counts all convergence gain and none of the cost of holding the sea inside a 2.08 Å cell.
2. Recoverable: possibly — the missing side of the balance is a Law V movement-budget cost of confinement, which SDT owns conceptually but has not derived as a magnitude.
3. Unaccounted: confinement cost of the delocalised sea (the sea is moving; movement in a bounded cell has a budget price).
4. Errored premise: **cohesion = electrostatics alone**; the sea was treated as free.
5. Freedom: the Law V confinement-cost law for a delocalised shared electropause.
6. Accounting: native in kind (Law V budget), underived in magnitude — status **CALIBRATED-until-derived is not claimed here; nothing was calibrated**; the phase is left OPEN. Re-open condition: FLM14 rotation/sequential-occupancy program supplies the seat-tour cost, or a Law V confinement derivation lands.
7. Cascade: partially — distinct from the contact root (this is a budget term, not a contact term); logged as its own root.

## Cascade roots (reported, not written to STACK)

- **ROOT-CONTACT** (shared with CH05, CH07, and NP10/NP17-alpha): the underived **saturated-occlusion contact/lock term**. In CH02 it is the +8–10% 1:1 overshoot and the MgO fail; in NP17 it is the alpha PENDING; in CH07 it is the missing restoring stiffness; in CH05 the missing barrier.
- **ROOT-BUDGET** (CH02-P3): Law V confinement cost of a delocalised sea (metals; feeds CM02).

## Canonical line

**Prompt completion C · Physics class CONVERGENCE (P1, P2, P4-KCl earned; the geometric sum survives the delete-test without SDT — it is honest convergence, not NATIVE) / OPEN (P3 metallic) · Recovery PARTIAL · Cascade root ROOT-CONTACT + ROOT-BUDGET**
