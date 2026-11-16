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

---

## ⟐ RE-OPENED (2026-07-06) — recorded condition FIRED + §G.3 premise-class event (Harvey order)

**Trigger 1 (the recorded condition fired):** the MgO §D re-open condition named "NP10
saturated-occlusion run lands its lock ladder" — NP10 run 2 (2026-07-05) landed it, both ways:
the (Z−1)! Face-T lock PASSED (d −1.1% / t +0.9% / α −5.6%, zero constants) AND the radial
saturation wall was KILLED structurally (it can only deepen attraction). So the missing MgO/1:1
contact term is now known NOT to be occlusion saturation — its named successor is **ROOT-WALL**
(rolling wake firewall, ~ℏ²/2m_e curvature budget).
**Trigger 2 (refinement 8):** electron repulsion = nuclear repulsion TRANSMITTED (shell =
gearbox). Sharp consequence for THIS file: **Mg²⁺ and O²⁻ are both neon-shell — MgO is an
isoelectronic pair.** If the wall is nuclear-transmitted, the wall stiffens with Z under the
same shell, and the overshoot growing with charge product (NaCl +9.4% → MgO +21.6%) is that
prediction's first uncontrolled data point. **Named decidable (pre-registered here):** fit the
wall on isoelectronic series (Ne / Na⁺ / Mg²⁺ vs measured Born–Mayer hardness/range from
crystallography) — nuclear transmission predicts hardness tracks Z at fixed shell; the
electron-source rival predicts flat. **What this does NOT do:** P2/P4 labels unchanged; the
MgO FAIL stands until a derived wall (registered cross-check: k(H₂)=575 N/m ∧ NaCl +9.4% ∧
α ×6.35) is computed, not fitted. P3 metallic stays OPEN — refinement 8's "press" mode
(pressure = movement that cannot move) is the named frame for the ROOT-BUDGET confinement
cost, still underived.

---

# CH02 — RUN 2 VERDICT, Phase A (2026-07-06): the isoelectronic fork

> Tool: `ch02_r2_isoelectronic_fork.py` (exit 0; `ch02_r2_isoelectronic_results.txt` = teed
> stdout). Spec: PROMPT.md §R2 Phase A, GATE-A verbatim; ADJ-R2-1 committed in RUN_LOG before
> the tool existed, including the rival-degeneracy declaration and the S3 design-preview
> disclosure. All inputs measured literature values (Shannon 1976 radii; standard elastic B₀),
> data-boundary units. No G/M/GM anywhere.

## GATE-A: PASS on the committed scoring — the shell-only wall is dead

- **S1 (range):** Shannon radii strictly decreasing with Z in ALL THREE shells — He {0.76→0.45
  →0.27}, Ne {1.40→1.33→1.02→0.72→0.535→0.40}, Ar {1.84→1.81→1.38→1.00→0.745→0.605}. Exact
  permutation nulls 1/6, 1/720, 1/720.
- **S2 (hardness):** measured B₀ rises with cation Z in all three structure-matched rocksalt
  pairs: NaF→MgO ×3.44, KF→CaO ×3.70, KCl→CaS ×3.22 (sign-test null 1/8). LiF→BeO same
  direction, excluded as committed (wurtzite).
- **Machinery validation:** the deconvolution instrument reproduces the classical Born
  exponents where they are known — NaF n = 6.98 (convention: 7), KF 7.96 (8), KCl 8.61 (9).

**What is settled:** at fixed electron count, the wall tracks what is UNDER the shell. The
"electron shell alone sets the wall" model is killed — and note the collinearity is a feature:
at fixed N_e, net charge ≡ nuclear surplus (z = Z − N_e), so ANY Z-dependence at fixed shell
refutes shell-only walls regardless of bookkeeping. **Class (fixed pre-run): CONVERGENCE** —
the rival's Z_eff contraction predicts the same sign, so this PASS is consistent-with
transmission, not native evidence for it. The kill-gate did not fire; the claim lives.

## The tension row (reported prominently, per ADJ disclosure)

The z²-deconvolved wall exponent n FALLS with Z in every pair (6.98→4.51, 7.96→5.22,
8.61→5.09) — the alternate scoring WITH S3 fails on this leg (both scorings printed in the
results file). Under transmission this reads: the wall's onset moves inward faster than its
power-law steepens. **Flagged OPEN as a required reproduction target for Phase B:** any
derived rolling-firewall W(R) must produce BOTH the B₀ rise AND the exponent fall, or explain
which measurement it disowns. This is now the sharpest quantitative constraint the wall has —
sharper than the three-field cross-check alone, because it is a SHAPE constraint, not a point.

---
**Prompt completion A (Phase A executed as committed; nulls honoured; disclosure printed) ·
Physics class: GATE-A PASS at CONVERGENCE (shell-only wall KILLED; transmission consistent,
rival-degenerate — declared pre-run) · Tension: n falls with Z [OPEN → Phase-B reproduction
target] · Recovery n/a · Cascade: ROOT-WALL gains two quantitative targets (B₀ ratios ~×3.4;
exponent fall ~7→4.5).**
