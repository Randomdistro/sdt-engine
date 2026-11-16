# OP04 — Verdict: Polarisation as Transverse Wake Orientation

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04 · Tool: `op04_polarisation.cpp` (exit 0; stdout in `results.txt`)

## What was done

The state is a real time-domain transverse displacement u(t) = (Ax·cos(ωt+φx), Ay·cos(ωt+φy)),
sampled mechanically. A polariser is anisotropic closure (instant-by-instant projection onto the
pass axis, orthogonal component dumped); a retarder lags one axis by a fraction of the tick;
unpolarised light is a Monte-Carlo ensemble of random orientations. No Jones matrices, no Stokes
axioms, no spin operator, no complex-amplitude ontology.

## Earned (real stdout)

- Linear / circular / elliptical all carried by (Ax, Ay, lag) — no further structure needed (P1).
- Malus I = I₀cos²θ from projection geometry to 4.6e-15; crossed extinction 3.7e-33·I₀;
  three-polariser revival 0.125176 vs 1/8 (0.14%, ensemble K = 2e5) (P2).
- QWP (quarter-tick lag on one axis): linear@45° → circularity 1.000000; HWP (half-tick lag):
  linear@20° → −20° = the 2ψ rotation (P3).
- Optical activity from handedness-split relay speed: rotation strictly ∝ L (ratio 2.000000),
  3.056°/cm at the MEASURED-INPUT Δn = 1e-6, λ = 589 nm (P4 magnitude).

## Owed (the honest caps and opens)

1. **The algebra is isomorphic to the Jones calculus.** (Ax, Ay, lag) + projection + per-axis lag
   *is* a Jones vector under renaming. Per the prompt's own firewall this caps the grade at **C /
   CONVERGENCE**. Stated without decoration: the earned content vs classical polarisation optics is
   the ONTOLOGY (a real lattice displacement with EMC03 handedness), which these numerics do not test.
2. **"No spin operator" is a soft target** — classical polarisation optics never required one either.
   F6 passes trivially; it discriminates SDT from the quantum story only at single-emission level,
   which is not simulated here.
3. **Activity SIGN → EMC03 mapping: OPEN** (asserted, not derived). **Δn magnitude: MEASURED-INPUT**,
   inheriting OP01's OPEN matter-index root.

## §D seven questions (on the sign-mapping OPEN)

1. **Why open?** The tool shows rotation = δ/2 with δ ∝ (n_L−n_R)L; nothing in it determines WHICH
   handedness relays slower in a given chiral lattice — the sign is a free assertion.
2. **Recoverable?** In principle: a chiral-lattice relay model (helical closure asymmetry) would fix
   the sign of n_L−n_R per structure; sugar-enantiomer data are the anchor pair.
3. **Fail to account for?** The microscopic chirality→closure-split link.
4. **Errored premise?** None errored; the unbuilt premise is the matter-closure model (OP01 root).
5. **Freedom?** The handedness-resolved closure of a chiral unit — a native quantity, currently absent.
6. **Native or knob?** Native in kind; nothing fitted here (Δn was declared MEASURED-INPUT, sign OPEN).
7. **Cascade?** Yes — the magnitude side runs to **OP01's matter-index OPEN**; the component-carrying
   side (what the transverse wake can carry) runs to the **OP-root** debt shared with OP02/OP03.

**Recovery grade: PARTIAL** (route named; blocked behind the OP01 matter-index closure).

## Generative questions logged

Q1 (spin-1 selection rules as handedness matching): untested, OPEN — needs OP05/QM06 machinery.
Q4 (QWP retardance as relay-tick count): supported in form — the tool's retarder IS a quarter-tick
lag; making waveplate thickness a spation count needs the material Δn derived first (OP01 root).

---

**Prompt completion C · Physics class CONVERGENCE · Recovery PARTIAL · Cascade root: OP01-matter-index (magnitude/sign); OP-root (component carriage, shared with OP02/OP03)**
