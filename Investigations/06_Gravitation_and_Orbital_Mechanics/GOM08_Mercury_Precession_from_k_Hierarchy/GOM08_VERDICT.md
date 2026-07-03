# GOM08 — Verdict: Mercury Precession from k-Hierarchy

**Classification: CLASS C (CONVERGENCE).**
**Author**: James Christopher Tyndall, Melbourne · Tool: `gom08_mercury_precession.cpp` (MSVC compiled clean, ran clean).

## Deciding metric

The investigation successfully demonstrates that SDT's k-hierarchy effective potential reproduces the standard relativistic precession of Mercury. 

This is classified as **CLASS C (CONVERGENCE)** because:
1. The precession formula in SDT is structurally identical to standard general relativity's precession formula.
2. The equivalent field length scale $\ϟ_{\text{Sun}} = R_{\text{Sun}}/k_{\text{Sun}}^2$ acts as an exact algebraic map that corresponds to standard general relativity's metric length scale $GM/c^2$.
3. SDT uses no mass or G in the calculations, describing the field entirely in terms of the spation displacement factor $k$ and the physical radius $R$.
4. The agreement is a consequence of the equivalence principle and the definition of the coppa scale in the bridge namespace rather than an independent prediction.

## Numbers (from the run)

- **SDT Precession**: **42.9930" / century** (vs target 42.98", deviation of **0.013" / century** or **0.03%**).
- **Standard Precession**: **42.9808" / century** (using standard equivalent field length scale $L_{\text{standard}} = 1476.625$ m).
- **SDT vs Standard Relative Agreement**: **2.85e-04** (diff of **0.0123" / century**, within the 0.05% margin of solar parameters).
- **Bridge Law Check**: $\ϟ_{\text{SDT}} = R_{\text{Sun}} / k_{\text{Sun}}^2 = 1477.046$ m vs $L_{\text{standard}} = 1476.625$ m (relative error **0.0285%**, PASS under the 0.1% verification limit).
- **k-Sun Verification**: The hardcoded $k_{\text{Sun}} = 686.3$ matches the value recovered from GOM04 closure ($686.4039$) to within **0.015%**.

## Provenance × correspondence

- **provenance**: SDT-derived (k-gradient potential, $v(r)$ profile, bridge laws); external (standard observed orbital parameters and target precession).
- **correspondence**: Exact structural mapping to the Schwarzschild metric's $1/r^3$ correction term at 1PN order.

## Parameter ledger (R2)

`c`, `R_Sun`, `a_Mercury`, `e_Mercury` OBSERVED · `k_Sun`, `mercury_orbits_per_cy` DERIVED · equivalent c-boundary $\ϟ_{\text{SDT}}$ DERIVED-mapping. Free parameters: **0** (CALIBRATED(0)).

## Open (path to Class A)

To achieve Class A status, the value of $k_{\text{Sun}} = 686.3$ must be derived from first principles of solar displacement accumulation (linking to fluid/spallation mechanics) rather than being treated as a bridge constant, and the orbital equations of motion must be integrated directly in the occlusion field without relying on the effective potential approximation.

**Sign-off: PASS, Class C.**
