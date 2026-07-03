# GOM11 — Verdict: Ocean Tidal Analysis

**Classification: CLASS C (CONVERGENCE).**
**Author:** James Christopher Tyndall, Melbourne · Tool: `gom11_ocean_tidal.cpp`.

## Hypothesis

Tides from koppa gradient reproduce Newtonian r⁻³ tides without G or M.

## Key numbers

- h_M2 (dynamic): **0.628 m** vs 0.63 m (**0.4%** [CALIBRATED via Q — not a prediction])
- M2/S2 ratio: **2.177** vs 2.17 (**0.3%** error) — PASS (DERIVED from koppa alone)
- h₂: **OBSERVED** Earth-ocean input. Q: **CALIBRATED** (tuned: the Q that lands 0.63 m exactly is 2.319; source uses Q_M2=2.31, labelled `[OBSERVED]` in `gom11_ocean_tidal.cpp` line 19 — it is a back-solved resonance factor, not an independently measured ocean-resonance Q)

**Sign-off: SPLIT — M2/S2 ratio PASS (genuine convergence, Class C); M2 amplitude CALIBRATED via tuned Q, not a prediction (see above).**
