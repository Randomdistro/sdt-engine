# PM07 — Verdict: Magnetohydrodynamics Coupling to the Fluid Suite

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05
**Tool:** `pm07_mhd_coupling.cpp` (MSVC, real run, exit 0) → `pm07_results.txt`
**Pre-commitments:** `RUN_LOG.md` (orphans predicted before the run; all three materialised).

---

## 1. Deciding metrics

| Phase | Gate | Result | Class |
|---|---|---|---|
| P1 | bijection, zero silent leftovers | Coupling map printed term-by-term; **3 orphans NAMED** (predicted in RUN_LOG): ORPHAN-1 swirl↔momentum gain (=HG-1), ORPHAN-2 η≡FD02 (identification, magnitude underived), ORPHAN-3 ⊥-pressure closure | **C by its own gate** (bijection not clean — as committed) |
| P2 η=0 | count drift ≤0.5% | **exactly 0** excursion (6418 quanta, 20 checks, full deformation) | **NATIVE — the earned theorem** |
| P2 η>0 | slip ∝ η, slope 1.0±0.3 | leak 7.5/21.9/59.8/206.8 quanta over 33× in η; **slope 0.943** | NATIVE mechanism (Fick), FD02-identified coefficient |
| P3 | v_A assembled | v_A = u_w√(ρ_a/ρ) (form); SI map on final line only; conversion ρ_a u_w² ↔ B²/µ₀ = ORPHAN-1 | CONVERGENCE (assembly), gain OPEN |
| P3/P4 | stress structure | **tension/energy-density = 2:1 in BOTH readings** (Maxwell stress; directed relay stream) — dimensionless structural match, flagged arithmetic | structural check |
| P4 | ⊥ closure | **honest mismatch owned**: Maxwell ⊥ pressure = FULL energy density (w=+1); cold stream gives 0, FD05 radiation u/3. Candidate: CR05 γ_eff=4 stiff lattice — logged, untested | **OPEN (ORPHAN-3)** |

## 2. The earned result — frozen-in flux is a counting theorem

Φ = enclosed wake-quanta count. Loop and quanta ride one flow ⇒ enclosure is advection-invariant ⇒
Φ conserved **exactly** (measured: zero count changes through full loop deformation). This produces
the ideal induction equation ∂B/∂t = ∇×(v×B) with **no Ohm's-law postulate** — the flux freezing is
not a dynamical balance but a topological invariance of transport, and it is the precise thing
PM05's reconnection must BREAK. Finite FD02 diffusion breaks it by Fick leakage, slip ∝ η
(slope 0.943). This is the FD07/FD01 house-style native mechanism result.

## 3. §D seven questions (on the not-clean bijection / orphans)

1. **Why not clean?** Three terms have no earned SDT producer: the J×B gain, the η magnitude, the
   ⊥ stress closure.
2. **Recoverable?** ORPHAN-1: iff HG-1 closes. ORPHAN-2: FD02's ν↔η handshake (same debt FD01 F5
   carries — one debt, not two). ORPHAN-3: needs a wake equation of state; CR05's γ_eff=4 stiff
   lattice is the named candidate (w=+1 pressure is exactly what a topologically stiff lattice
   supplies) — untested.
3. **Failed to account for:** the prompt hoped "swirl tension = PPT06 traction" quantitatively;
   PPT06 gives channels (ℓ=1,2,3), not a stress magnitude.
4. **Errored premise:** "every MHD term is already named in an FD/PM primitive." Three are not.
5. **Freedom:** one conversion constant (ρ_a u_w² ↔ B²/µ₀) + one EoS statement (wake w=+1).
6. **Accounting:** conversion = HG-1-adjacent (bare until PM01's gain closes); EoS = CR05 line
   (native candidate, testable).
7. **Cascade?** ORPHAN-1 → **HG-1**. ORPHAN-2 → **FD02-handshake** (pre-existing FD-suite debt).
   ORPHAN-3 → new root, name it **WEOS-1 (wake equation of state)**.

**§G:** faith ledger — the directed-stream reading of a swirl bundle is the named posit behind the
2:1 check; it is stated as a posit. No gate here enforces a rival axiom; MHD numbers appear only as
targets. "Not derivable" appears nowhere; every orphan carries its re-open condition.

## 4. Generative questions logged

- Prompt Q2 (one dispersion surface containing FD05's c/√3 and v_A): assembled form stated; the
  surface itself is the PM03-rebuild's job (same missing tool as PM06's coefficient).
- Prompt Q4 (single FD02 criterion for frozen-in breakdown shared with PM05): this run gives the
  quantitative slip law (leak ∝ η with measured coefficient) — PM05's sheet consumes exactly this.
- New: the 2:1 tension ratio suggests the swirl bundle IS a momentum-carrying stream; if WEOS-1
  confirms w=+1 wake pressure, the full Maxwell stress = relay Reynolds stress + stiff-lattice
  pressure, term for term.

## 5. Verdict

> **Prompt completion C** · **Physics class** NATIVE (frozen-in counting theorem + slip ∝ η) /
> CONVERGENCE (assembled set, 2:1 structural match) / OPEN (three named orphans) · **Recovery**
> PARTIAL (all three routes named; none paid) · **Cascade roots** HG-1; FD02-handshake; WEOS-1 (new).
