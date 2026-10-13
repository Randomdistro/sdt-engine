# FD12 — Direct verdict (2026-07-26): the operation is native; the ℓ_c identification is dead as posed

> **Run class: DIRECT** (main session, no agents). PROMPT.md written with pre-committed gates
> BEFORE the tool; tool `fd12_poloidal_parcel.cpp`, g++ 15.2 -O2, exit 0.
> Outputs: `fd12_rerun_2026-07-26.txt` (final), `fd12_rerun_v1_instrument_2026-07-26.txt`
> (first instrument, preserved).

## Instrument history (all in the open, gates never touched)

- **v1** (grid, random seed, upwind): G = 1.000 at every λ — instrument failure (near-zero
  projection on tilted Orr structures; first-order upwind numerical diffusion ~ ν at small λ).
  Recorded, preserved.
- **v2/ADJ-1** (spectral single-mode + tilt sweep): G = 3.6e7 at λ = 0.25 — explicit-Euler
  instability on the advection term's imaginary axis. Artifact, caught, recorded in-source.
- **v3/ADJ-2** (exact advection phase rotation): stable, clean interior maximum, physically
  sensible tilt pattern (longer waves need more initial tilt). This is the graded run.

## P1 — the poloidal operation (all four gates PASS)

| gate | committed | measured |
|---|---|---|
| G1a formation | extrema within 15% | dev 0.000 |
| G1b self-propulsion | ≥ 1.0a, control < 0.1a | **1.380a vs 0.000a** |
| G1c roll-back | flank u < −0.05·U_pair | **−1.097·U_pair** |
| G1d closed cell | centre jet ≥ 1.3·U_pair | **3.42·U_pair** |

The full operation — forward core, stall-aside, roll-back along the flank, closed carried
cell — emerges from the FD01 relay lattice with nothing imposed. Class ceiling as committed:
**consistency/convergence** (Lamb-dipole physics is known; what is banked is that the relay
lattice performs the operation natively, so the picture is the lattice's own behaviour).

## P2 — the discriminator (FAIL as committed)

Transient-gain selection at Re = 1000: interior maximum at **λ* = 1.0 L** (G = 2.12, tilt +4)
→ ℓ_c = λ*/2 = **L/2** → L/ℓ_c = **2** → exported Re_crit = **4**. Pipe demands 48 → 2300.
Outside the committed order-band [10, 200] by a factor of 5 at the ratio level.

**G2 verdict: FAIL — the identification "FD03's coherence length = the transient-growth-selected
poloidal roll dimension" is dead as posed.** No re-scoping. Two honest readings recorded, both
for a FUTURE pre-commit, neither a rescue: (a) 2-D transient growth is known-weak (gain 2.1);
the wall-bounded transition roll is a 3-D object (lift-up/streak mechanism) that a 2-D
poloidal-plane instrument may be structurally unable to select — a 3-D streak-spacing re-pose
would carry its own committed band before running; (b) the roll the 2-D channel *does* select
(half-width, channel-filling) may be the right object for a different observable than ℓ_c.

## Verdict

- **Prompt completion: A** (both phases run to their committed gates; instrument revisions
  logged; no gate moved).
- **Physics class: SPLIT.** P1 — the poloidal parcel operation is **NATIVE-consistent** on the
  relay lattice (cannot discriminate alone). P2 — **KILLED as posed**: the roll is not FD03's
  ℓ_c under 2-D transient selection. The picture survives as mechanism; its first quantitative
  identification died honestly on its first test. That is the test working.
- **Recovery:** 3-D streak re-pose available (new pre-commit required) · **Cascade root:**
  shares FD03's forward-ℓ_c closure.
