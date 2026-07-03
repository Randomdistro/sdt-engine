# RUN_LOG — GOM13 Occlusion-Altitude Cavendish (pre-flight prediction set, owed to E104)

> **Executor:** Claude (HUNTER-disciplined), on behalf of J. C. Harvey, Melbourne. **Date:** 2026-07-03.

## Pre-Run Commitments — GOM13 (written BEFORE the tool was coded or run)

- Prompt completion target: B (gate-zero / pre-flight set only — no hardware claims)
- Physics class hoped: honest PRE-FLIGHT fork analysis; committed in advance to print
  "not worth flying" if the numbers land below the floor
- CALIBRATED budget: disclosure-only — `law_III::P_eff` carries the in-header label
  "coefficient calibrated (class E)"; `bridge::koppa_per_baryon = ℓ_P²·c·m_p/ℏ` carries
  the in-header disclosure that CODATA ℓ_P conventionally encodes G ("disclosed, not
  laundered"). Both provenance strings will be quoted, not hidden.
- Deliverables committed (the E104 §8 pre-flight set):
  - (a) κ = shared-P_eff coupling: derivation chain from Law III shown. Since BOTH
    channels are linear in P_eff under EMC03's one-law claim, κ ≡ (∂lnF_Cas/∂lnP_eff)
    / (∂lnF_Cav/∂lnP_eff) must come out **exactly 1**, independent of P_eff's magnitude
    — so P_eff's class-E status does NOT infect κ. SM value: κ = 0. If the algebra
    yields anything but 1, report it.
  - (b) δ(h), 0–40 km, TWO models, both printed:
    G1 (the PROMPT §3.2 geometric-opacity law): ΔF/F = sin(arccos(R/(R+h)));
    G2 (mass-proportional): barometric overhead column σ(h) = (P₀/g₀)e^(−h/H),
    H = 7,640 m, converted to occlusion via ϟ_col = koppa_per_baryon·(σ/m_p)·(4πR²)
    aggregated / referenced to ϟ_Earth — i.e. δ ∝ occluding MASS, the only scaling
    consistent with Law III's R² (mass-area) dependence.
  - (c) Near-contact saturation g(x) = 2(1−√(1−x))/x, x = (R/r)² — table + limits
    (must recover g→1 as x→0, g→2 at contact; if not, the formula transcription is
    wrong and will be reported).
  - (d) Make-or-break: δ(h)·κ vs noise floors. Committed floors BEFORE run:
    F1 = 3e-3 (the PROMPT's own 0.3% per-altitude-bin target);
    F2 = 1e-5 (heroic long-integration lock-in, best laboratory class).
    If the predicted signal is below F2, the committed wording is: "orders below
    reachable sensitivity — not worth flying as designed."
- OBSERVED-anchor kill test (committed): the PROMPT itself says "re-examine the G
  record for a correlation with lab elevation." G1 predicts elevated labs read G high
  by √(2h/R): JILA/Boulder (1655 m) +2.28%, LANL (2231 m) +2.65%. The published
  CODATA-input record (UWash ~50 m: 6.674255e-11; BIPM ~60 m: 6.67554e-11; JILA
  1655 m: 6.67234e-11; LANL 2231 m: 6.6740e-11; HUST ~30 m: 6.674184e-11) scatters by
  ~5e-4 relative. Committed criterion: G1 is EXCLUDED if its predicted shift exceeds
  10× the observed inter-lab scatter. (Predicted 2.3e-2 vs scatter 5e-4 = 46×; and the
  highest lab, JILA, reads LOW, not high — sign check included.)
- H1 caveat carried on every line: if the fibre constant also rides the ambient flux,
  the ratio cancels and NO altitude experiment (nor the G record) can see the signal —
  the PROMPT's own §3.4 escape. Both branches must appear in the verdict.
- Forbidden retroactive changes: widen floors; drop the failing model; hide either
  branch of H1.

## Build log

- 2026-07-03: `gom13_preflight.cpp` written AFTER the commitments above. Compiled
  clean, MSVC 19.44.35223 x64, `/std:c++20 /EHsc /O2 /utf-8 /I Engine\include`.

## Run log

- 2026-07-03: `gom13_preflight.exe` → exit 0, full stdout in `results.txt`.
- (a) κ = 1 exactly (ratio of two linear P_eff responses; magnitude cancels).
  P_eff = 5.2252e+31 Pa printed with its verbatim header provenance
  ("risk_flag: coefficient calibrated", class E) — disclosed, and shown NOT to
  infect κ. SM comparison: Casimir 1.300e-3 Pa at 1 µm with no P_eff in it.
- (b) δ(h) both committed models:
  G1 (sin-dip): 1.25e-2 @ 0.5 km → 1.115e-1 @ 40 km.
  G2 (mass-proportional barometric): 8.83e-7 @ ground → 4.70e-9 @ 40 km;
  ramp signal Δδ = 8.78e-7. The models differ by 1e5 — that IS the fork.
  G2 sanity-anchored against the Bouguer plate (~4.4e-7 of g): same order. ✓
- (c) Saturation curve emitted: g(1e-4)=1.000025 → g(1)=2.000000; 7.2% deviation
  from 1/r² at 2 radii separation. Limits recover 1 and 2 as committed.
- (d) Make-or-break vs committed floors: G1 = 37× ABOVE F1 (measurable if real);
  G2 = 3,417× BELOW F1 and 11× below even the heroic F2 = 1e-5. Required
  sensitivity for G2 ≈ 3e-7. Committed wording triggered and printed.
- (e) OBSERVED anchor (the PROMPT's own suggested check): existing G record vs lab
  elevation. G1 predicts +1.97e-2 (JILA, 1655 m) and +2.34e-2 (LANL, 2231 m) vs
  sea-level labs; observed inter-lab scatter ~5e-4 AND JILA reads LOW (−2.8e-4).
  47× > committed 10× exclusion criterion → **G1 EXCLUDED pre-flight**.
- H1 fork printed with both branches; neither branch leaves a flyable altitude
  signal. Pre-flight verdict as committed: NOT WORTH FLYING for the altitude law.
