# FD08 — Verdict: Bernoulli from the Movement Budget

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Author**: James Christopher Tyndall, Melbourne
**Status**: EXECUTED — compiled (MSVC `/std:c++20 /O2`), run, exit code 0, double precision.

---

## Classification: **Class C (QUALIFIED — convergence)**

Bernoulli's invariant, the Venturi pressure drop, the Pitot/stagnation relation,
and the compressible stagnation correction are **reproduced term-for-term** as a
single Law-V budget partition, with the pressure–velocity trade sign **forced
negative** and the elevation head computed purely from SDT gravity $g=v^2/R$ (no
$G$, no $M$). Exactly **one** measured input is used — the adiabatic index
$\gamma$, and only for the compressible part.

### Why C and not A

The spec reserves **A** for an entirely CALIBRATED(0) reproduction. FD08 needs
one MEASURED-INPUT ($\gamma=1.4$) to *evaluate* the compressible correction of
Phase 4. The incompressible spine (Phases 1–3, 5) is fully DERIVED with zero
fitted parameters, so the result clears C comfortably and sits at the C/A border:
it is a clean analytic derivation plus exact numeric verification, with the only
non-derived number being a measured material property of air, not a tuned
coefficient. Per the honesty mandate (ledger $\gamma$ as measured-input), C is
the honest label.

### Why not D or F

- Not **D**: the compressible correction is reproduced (not PENDING) and the
  $c_s$/FD05 handshake is exercised (Phase 4 uses $c_s=340.3$ m/s).
- Not **F**: the momentum balance integrates to *exactly* $\tfrac12\rho v^2+P+\rho
  gz$ with no surplus/missing leading-order term (F1 cleared), the sign is
  $dP/dv=-\rho v<0$ (F2 cleared), and the head has a clean SDT route via
  $g=v^2/R$ (no R0 violation).

---

## Checkpoint ledger (real run)

| Checkpoint | Test | Result | Number |
|---|---|---|---|
| **C1** | streamline invariant from momentum balance | **PASS** | residual $2.4\times10^{-10}$ (pure $O(\Delta s^2)$) |
| **C2** (core gate) | forced sign $dP/dv=-\rho v<0$ | **PASS** | $-61.25$ Pa·(m/s)$^{-1}$; analytic≡numeric to $1.9\times10^{-11}$ |
| **C3a** | Venturi $\Delta P=\tfrac12\rho(v_2^2-v_1^2)$ | **PASS** | $v_2=50.0$ m/s, $\Delta P=1286.25$ Pa, ref rel.diff 0.0 |
| **C3b** | Pitot $P_0=P+\tfrac12\rho v^2$ | **PASS** | $q=2205$ Pa, $P_0=103530$ Pa, round-trip $<10^{-9}$ |
| **C4** | compressible / $M\to0$ corner + $c$-ceiling | **PASS** | $M\to0$ ratio $0.99999999$; bounded at $v=0.999c$ |
| **C5** | streamtube $B(s)=$const | **PASS** | $\max|B-B_0|/|B_0| = 0.0$ (machine precision) |

All falsification tests F1–F5 cleared.

---

## Provenance × correspondence audit

| Result | provenance_status | correspondence_status | projected class |
|---|---|---|---|
| Streamline invariant $\tfrac12\rho v^2+P+\rho gz$ | SDT-first (FD01 momentum integral) | known-match (classical Bernoulli) | **C** |
| Forced sign $dP/dv=-\rho v$ | SDT-first (Law V partition) | known-match | **C** |
| Venturi $\Delta P$ | SDT-first (continuity ⊕ budget) | known-match | **C** |
| Pitot $P_0$ | SDT-first ($v\to0$ of budget) | known-match | **C** |
| Compressible $P_0/P$ | external/imported ($\gamma$ measured) | known-match | **C** (one input) |
| Head $\rho gz$ via $g=v^2/R$ | SDT-first (bridge, no G/M) | known-match | **C** |

**Delete-test**: removing the classical-correspondence check leaves every SDT-first
row standing (the invariant is still the momentum integral, the sign is still
$-\rho v$). This is **convergence**, not borrowing — Bernoulli is recovered as a
*consequence* of the Law-V partition, not assumed.

---

## What is DERIVED vs MEASURED-INPUT vs PENDING

- **DERIVED (CALIBRATED(0))**: the invariant, the forced sign, Venturi $\Delta P$,
  Pitot $P_0$, the $M\to0$ incompressible corner, the SDT gravity head $g=v^2/R$.
- **MEASURED-INPUT**: $\gamma=1.4$ (adiabatic index of air), used only for the
  compressible correction in Phase 4.
- **Stated scales (not fitted)**: $\rho_\text{air}=1.225$, $c_s=340.3$, the test
  areas/velocities — used to *evaluate* the predictions, never to tune the law.
- **PENDING**: a full coefficient-level bijection of the Law-V partition to the
  *microscopic* relay-stiffness $c_s$ (the FD05 handshake is invoked at the
  continuum level but not yet derived bottom-up here); the explicit identification
  of the relativistic ($v\to c$, not just $v\to c_s$) corner is shown bounded but
  not characterised in detail.

---

## Downstream handoffs

- **FD07 (lift)** — consumes the streamtube pressure field $P(s)$ produced in
  Phase 5 (the negative $P$–$v$ trade around an aerofoil is the lift mechanism).
- **FD09 (drag / stagnation)** — consumes the stagnation result
  $P_0=P+\tfrac12\rho v^2$ (the front-face stagnation pressure of the drag
  cross-section).

---

## Honesty notes (R1/R2/R4/R5)

- All key numbers (Venturi $\Delta P$, Pitot $P_0$, $dP/dv$) were **committed in
  the run log before comparison** (R1) — the tool prints `PREDICT (committed)`
  lines ahead of `RESULT`.
- **R5 (anti-numerology)**: no free integer, $\pi$, or fudge factor was inserted
  to force any match. Every coefficient traces to Law V / continuity or is the
  flagged measured $\gamma$.
- **R0 (no G/M)**: the gravity head is computed exactly once via
  `bridge::g_surface(v,R)=v²/R`; there is no `GM/R²` code path. Confirmed
  $g=9.8183$ m/s² from $v_\text{Earth},R_\text{Earth}$ alone.
- **Engine fix (logged, R2/R4)**: a pre-existing dangling reference at
  `laws.hpp:1162` (`winding::W_proton` → `law_VI::winding::W_proton`) was
  corrected to restore standalone compilation of the single source of truth. No
  numeric change ($W+1=4$, ratio stays 12). Not a repaint of FD08 — a real
  blocker fix in the shared header, documented in FD08_DERIVATION §8.
