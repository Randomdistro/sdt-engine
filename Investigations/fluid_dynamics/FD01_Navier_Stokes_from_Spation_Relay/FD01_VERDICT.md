# FD01 — VERDICT

**Investigation:** Navier–Stokes from Spation Relay (the Fluid-Dynamics root).
**Author:** James Christopher Tyndall, Melbourne.
**Tool:** `fd01_navier_stokes_relay.cpp` (`#include <sdt/laws.hpp>`) → `fd01_results.txt` (real MSVC `/O2` run, double precision, exit 0).
**Derivation:** `FD01_DERIVATION.md` (analytic term-by-term bijection).

---

## Classification: **Class C (QUALIFIED — correspondence / convergence).**

**One-line justification:** the *structure* of every incompressible-NS term is reproduced from spation-relay mechanics (lattice Laplacian → `ν∇²v`, held-content transport → advection, count-conservation → `∇·v=0` at `O(Ma²)`) and the Euler/Stokes limits both fall out of the *same* PDE — but this is a reproduction of a **known** PDE, not an independent numerical surprise, and the viscosity coefficient `w` (hence `ν`'s number) is **PENDING FD02/ROOT-SIM**, so Class A is not reachable here. No fluid scale was fitted (**CALIBRATED(0)** in this run); no magic factor inserted (R5).

This is the honest, *expected* outcome stated up front in the spec (§1: "A clean reproduction earns Class C (convergence)").

---

## Pre-registered predictions vs results (R1 — committed in code before comparison)

| Check | Predicted (R1) | Measured | Verdict |
|---|---|---|---|
| Count/throughput conservation (Phase 1) | ~1e-14 (machine) | **0.000e+00** drift | PASS |
| Free streaming `w=0` | bit-identical | 0.000e+00 drift | PASS |
| ν recovery `0.5·dσ²/dt` vs `w·dx²/dt` (Phase 1+2) | < 0.5% | **2.873e-10** rel err | PASS |
| `‖∇·v‖ ∝ Ma²` log-log slope (Phase 3) | ≈ 2.0 | **2.000000** | PASS (F2) |
| Stokes mode decay vs `exp(−νk²t)` (Phase 4a) | < 1% | **0.0196%** | PASS (F4) |
| Euler advection survives `ν→0` (Phase 4b) | peak moves, diffusion gone | peak moved **100.0** cells (= U·n·Δt/Δx) | PASS (F3) |

**Failed numeric checks: 0.**

---

## Falsification tests (§8)

| Test | Result |
|---|---|
| **F1** — bijection (no surplus/missing leading-order term) | PASS (analytic): odd-order `∂_xxx` cancels by relay symmetry; first uncancelled term is `O(ℓ_P²)` Burnett hyperviscosity, sub-leading, candidate SDT-distinct, not a leading-order falsifier. |
| **F2** — `‖∇·v‖ ∝ Ma²` | PASS: fitted exponent 2.000000. |
| **F3** — Euler limit (`ν→0`) | PASS: advection translates the profile; physical Laplacian removed. |
| **F4** — Stokes limit (`adv→0`) | PASS: 0.0196% vs analytic (< 1%). |
| **F5** — coefficient handshake FD01 `ν` = FD02 `ν` | **PENDING** — FD02 not yet run; this is the gate that blocks Class A. |

---

## Provenance × correspondence audit

| Result | provenance_status | correspondence_status | class |
|---|---|---|---|
| NS term bijection (structure) | SDT-derived | **known-match** (reproduces the textbook PDE) | C |
| Relay Laplacian → `ν∇²v` | SDT-derived (form); coefficient PENDING | known-match | C / D-pending on `w` |
| `∇·v=0` from count conservation (Ma²) | SDT-derived (limit) | known-match | C |
| Euler / Stokes limits | SDT-derived | known-match | C |
| `P_conv` (the pressure field magnitude) | SDT-derived (Φ/ℓ_P³) | internal-only | inherits law_I |

**Delete-test:** removing the correspondence check (i.e. not comparing to NS) leaves the relay derivation and its numbers unchanged — so this is a genuine **convergence (C)**, not a fitted match. The lattice produces the diffusion/advection/Ma² structure on its own; NS is the *target it lands on*, never an input borrowed into the derivation (R5).

---

## DERIVED vs CALIBRATED(n) vs PENDING

- **DERIVED:** the bijection structure; `ν = w·ℓ_P·c` (form); `∇·v=0` as the `O(Ma²)` low-Mach limit; `P_conv` magnitude (`law_I`); ρ as displacement-load (`law_IV`). The run's `ν` is the rule's own identity, recovered to 3e-10.
- **CALIBRATED(0):** this run fits **zero** fluid scales. (The one permitted fluid-`ν` calibration is deferred to the FD02 Phase-5 handshake.)
- **PENDING:** the dimensionless diffusion coefficient `w` (→ `ν`'s numerical value) from FD02/ROOT-SIM; the FD01↔FD02 `ν` handshake (F5); the measured-benchmark end-to-end check (Poiseuille / Taylor–Green decay).

---

## Downstream handoffs

- **FD02 (viscosity):** receives the form `ν = w·ℓ_P·c` and must emit the dimensionless `w` independently; the F5 handshake (<1% agreement) is what would lift FD01 from C toward A. B16 `ν ∝ √T` (exponent 0.5) is FD02's to reproduce.
- **FD05 (compressible / sound):** receives the dropped `O(Ma²)` density correction.
- **All later FD0x:** rest on this root; the root is now **derived in structure**, not borrowed.

---

## Build note (non-regressive repo fix)

Building this tool surfaced a **pre-existing brace bug in `Engine/include/sdt/laws.hpp`** (committed in `010b6e3`): a stray `} // namespace law_VI` closed `law_VI` early after the `winding` sub-namespace, so `traction::traction_ratio_proton` could not see `winding::W_proton` and `depth_closure` fell outside `sdt::laws` — this **blocked ALL compilation** of the header. Removed the stray brace (the sub-namespaces `topology/confinement/traction/mass_ratio/angular` are now correctly inside `law_VI`, which closes once near line ~1250). Verified the **Benchmarks B01–B25 translation unit recompiles cleanly** after the fix; no constants were redefined or revalued. This is a structural correction, not a physics change.

---

## Verdict summary

> **FD01 = Class C.** Incompressible Navier–Stokes, with its Euler and Stokes limits, is reproduced term-for-term from spation-relay coarse-graining: the lattice Laplacian becomes `ν∇²v` (ν recovered to 3×10⁻¹⁰), held-content transport becomes advection, and spation-count conservation gives `∇·v=0` as an `O(Ma²)` limit (fitted exponent 2.000000). Stokes mode decay matches `exp(−νk²t)` to 0.02%. The NS root of fluid dynamics is **derived in structure, not borrowed** — but the viscosity *number* (`w`) is PENDING FD02, and reproducing a known PDE is a convergence, not a surprise. Honesty over success (R4): C, stated plainly, with the F5 coefficient handshake named as the one gate to A.
