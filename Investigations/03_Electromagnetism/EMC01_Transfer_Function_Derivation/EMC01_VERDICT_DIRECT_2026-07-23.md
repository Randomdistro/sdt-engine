# EMC01 — Direct re-run verdict (2026-07-23)

> **Run class: DIRECT** (main session, no agents). Prior agent-era `INVESTIGATION.md` deleted
> 2026-07-23 (git-recoverable); this verdict is written from today's program output only.
> Tool: `emc01_transfer_function.cpp` (legacy CQ01 tool), g++ 15.2 -O2, exit **1**.
> Output: `emc01_rerun_2026-07-23.txt` (174 lines).

## Prompt contraband check (Harvey directive)

`PROMPT.md` (§K-deepened 2026-07-13) is **CLEAN** of GR/QM/SM assumptions — it polices its own
contamination (flags the R_CMB dependency as CR07-forbidden, forbids define-by-Coulomb-then-call-
derived). No rival axiom enters any chain.

## What the re-run measured (today's output, not the record)

- **6/7 proofs PASS**: αℏc = k_e e² · P_eff from {α,ℏ,c,R_p,r_e} · f full-formula · expansion
  consistency · Coulomb at 1 Å · nuclear-over-Coulomb geometric ratio (0.0892, 0.0000% err).
- **G-test FAIL** (exit 1, honest): shell-cancellation G lands within ~5×, logged as FAIL.
- The f "universality" identity `f = 4αℏc·ℓ_P/(π R_p² r_e² R_CMB u_CMB)` verifies numerically
  (ratio 1.000000) — but per the prompt this is **the same equation written twice** (Route B is
  CONTAMINATED via R_CMB and is not a clean derivation).

## Verdict

- **Prompt completion: C** — the legacy tool re-ran clean; the §K prompt's dedicated
  `emc01_peff_routes.cpp` (Routes A/B/C separated) was NOT built this pass. Route C is covered by
  the **EMC04 direct run** (see `EMC04_VERDICT_DIRECT_2026-07-23.md`): P_eff inverted from
  kinematics to 4.1e-12 with delete-test clean.
- **Physics class:** force LAW = **CONVERGENCE** (class C, survives). Coefficient P_eff: the EMC04
  direct run supports **E → C on framework terms** with two named residuals — **α is read as the
  kinematic rung (not derived)** and the derivation basis form uses the **conjectural W+1 R_p** (2e-4).
  G recovery: **FAIL / OPEN** (class F stands; do not deploy).
- **Recovery:** n/a · **Cascade root:** W+1 rule (Law VI) — the single dependency the prompt's
  §2.RESOLUTION predicted, confirmed by today's runs.

*Remaining work: build `emc01_peff_routes.cpp` per §④ (A: derivation basis+delete-test standalone;
B: quantify the R_CMB contamination explicitly).*
