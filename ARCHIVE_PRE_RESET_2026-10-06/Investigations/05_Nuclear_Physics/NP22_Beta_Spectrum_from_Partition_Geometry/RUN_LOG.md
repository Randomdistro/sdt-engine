# RUN_LOG — NP22: β-Spectrum SHAPE from Partition Geometry

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-04. **Written BEFORE any tool code.**
> Engine: `#include <sdt/laws.hpp>` only.

## Pre-Run Commitments — NP22

- Prompt completion target: **A** (every gate evaluated, no knob taken)
- Physics class hoped: **NATIVE** (shape from geometry); honest floor accepted: **FAIL → OPEN**
- CALIBRATED budget: **0** (no weights, no measure re-shaping, no per-zone factors)
- Engine namespaces: `measured` (m_e, m_p, m_n, c, MeV_to_J), `law_V` (budget statement only)
- Premise (binding, from NP14 2026-07-04 appendix): neutron decay = one fixed internal speed
  v₀ (the 0.9186c seat electron) unwinding; the electron keeps a geometry-dependent share, the
  neutrino takes the Law-V complement of the speed budget; E_ν = Q − T_e closes the energy
  ledger (conservation — the model has NO native budget-speed→E_ν map; that debt is declared,
  not hidden).

## Identities declared up front (can earn NOTHING)

- Q = (m_n − m_p − m_e)c² = 0.782333 MeV — **IDENTITY** (engine masses; this is NP14's S_meas ≡ Q_β).
- β₀ from (γ₀−1)m_ec² = Q — **IDENTITY inversion** (the endpoint lands at Q *by construction*;
  reporting T_max = Q as a success is IDENTITY-PASS and is forbidden).
- The SHAPE of dN/dT_e on (0, Q) is the ONLY earnable content of this investigation.

## Anchor (OBSERVED column ONLY — never enters the chain)

dN/dT ∝ p_e E_e (Q−T)², T ∈ [0,Q], E = T + m_ec², p = √(E²−m²) — the standard measured
allowed (Kurie) shape of the free-neutron β spectrum. This is the rival's phase-space
machinery used strictly as the observational stand-in (known-good for the neutron to few %).
**Declared v1 omissions:** Coulomb (Fermi-function) correction, recoil-order, radiative
corrections. None is imported into the SDT chain under any outcome.

## Committed measure (BEFORE code; the only PASS-capable route)

**M1 — isotropic release:** release direction n̂ isotropic on the sphere relative to the seat
velocity vector; the freed electron keeps the projection v_e = v₀|cosθ|
(⇒ u = |cosθ| ~ U(0,1); closed-form CDF F(T) = β(T)/β₀). Relativistic kinematics:
T_e = (γ(v_e)−1)m_ec²; E_ν = Q − T_e; Law-V complement speed v_ν = √(c²−v_e²) reported as a
column only.

**Declared scan (fixed NOW, graded as scan, can NEVER produce a PASS):**
- M0 — tangential/slingshot limit: electron always exits with full v₀ ⇒ line at T = Q
  (the historical two-body line problem, run for the record).
- M2 — energy projection: T = Q cos²θ, isotropic ⇒ F(T) = √(T/Q).
- M3 — planar seat phase: u = |cosφ|, φ ~ U[0,2π), same speed map as M1
  ⇒ F(T) = (2/π)·asin(β(T)/β₀).

No measure, weight, or map may be added or altered after any result is seen.

## Gates (committed now, before any number exists)

- **G1 (SHAPE — primary, only PASS-capable):** M1 Kolmogorov–Smirnov distance D between
  unit-normalised CDFs on [0,Q]:
  - D ≤ 0.05 → **PASS (NATIVE)** — recovers NP14's FAIL on the spot;
  - 0.05 < D ≤ 0.15 → **QUALIFIED (Class C)** with deviations named;
  - D > 0.15 → **FAIL → OPEN**, cascade root = the release-measure geometry (→ FLM14 lineage).
- **G2 (ENDPOINT):** T_max = Q — **IDENTITY by construction. Not gradable. Never sold.**
- **G3 (limit fingerprints, record):** anchor endpoint exponent = 2 (ν 3D state count) and
  low-E exponent = ½ (e 3D state count); report each measure's exponents against these.
  Diagnostic windows declared: T ∈ [10⁻⁴Q, 10⁻²Q]; (Q−T) ∈ [10⁻³Q, 3·10⁻²Q].
- **G4 (numerics):** M1 Monte-Carlo (10⁷ samples, seed 20260704) vs analytic CDF max deviation
  < 10⁻³, else fix numerics before grading anything.
- **Class-kill lemma (Phase 4, stated before running):** any analytic 1-DOF release map with
  bounded non-vanishing measure density has endpoint exponent in {0, −1/2, −2/3, …} — never +2.
  If the numerics confirm the exponent table, the WHOLE 1-DOF class is killed, not just M1.

## Secondary reported statistics (declared; none is a gate)

Total-variation distance on 50 equal bins; mean ⟨T⟩; zone ledger (probability mass in
[0, 0.1Q], the thirds, and [0.9Q, Q]) — these locate WHERE the shape deviates (low-E vs
endpoint), as the prompt requires.

## Forbidden retroactive changes

- Widening D gates; adding/reweighting measures after results; IDENTITY-PASS on the endpoint;
  importing p_e E_e or (Q−T)² state-counting into the SDT chain; promoting a scan member (M0/M2/M3)
  to PASS on proximity (look-elsewhere applies); local constant namespaces; per-zone fudge factors.

## Planned outputs

`np22_beta_spectrum.cpp` → compile (C++20, `/I Engine/include`) → `np22_results.txt`
(redirected stdout) → `NP22_VERDICT.md` (dual verdict; §D seven questions on any kill;
canonical verdict line; cascade root if the shape fails).
