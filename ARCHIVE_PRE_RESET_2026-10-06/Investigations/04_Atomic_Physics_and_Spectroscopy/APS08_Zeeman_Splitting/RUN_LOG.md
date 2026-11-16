# APS08 run log

## 2026-10-03 — pre-registration (before the instrument existed)

Validation V1–V3, Round 1 (normal pattern) and Round 2 (anomalous pattern: diagonal route
classes against a reference vector model) are in `PROMPT.md`, section "Pre-registration
(2026-10-03)". The vector model is registered as a reference only, not as SDT.

## 2026-10-03 — run 1 (Rounds 1 and 2)

MSVC build. V1–V3 passed on the first run (V1: Larmor precession 5.0000e-6 at B = 1e-5 against
the expected B/2). Round 1: 3 components. Round 2: M_diag gave a three-level p manifold and
2 / 1 / 2 components per line group; M_vec reproduced D1 (4 components) and D2 (6) at the
target positions. All registered predictions held.

## 2026-10-03 — Round 3 registered after Rounds 1 and 2

Reason and rules in `PROMPT.md`, "Round 3". Added to the same tool and the whole tool rerun
(Rounds 1 and 2 unchanged). Result: R1 (integer magnitudes) exact for the four stretched states
and wrong for every anti-aligned state (²P₁/₂: 0 against 2/3); R2 (shifted by one half) exact
for none; R3 (q(q + 1)) equals the standard values. Na D1 collapses to 2 components under R1.
Rejection criterion met for R1 and R2, not met for R3. As predicted. The R3 targets are the
standard g-values, which are R3's output, so R3's agreement is by construction; the result that
carries information is the rejection of R1 and R2.

Output: `aps08_results.txt`. Conclusions: `APS08_ASSESSMENT.md`.
