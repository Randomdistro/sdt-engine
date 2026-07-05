# NP22 — VERDICT: β-Spectrum SHAPE from Partition Geometry

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-04. **Engine:** `sdt/laws.hpp` only.
> Tool: `np22_beta_spectrum.cpp` (MSVC 19.44, exit 0) → `np22_results.txt` (redirected stdout).
> Gates pre-committed in `RUN_LOG.md` BEFORE the tool was written; none widened, no knob taken.

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **A** | Every gate evaluated (G1–G4 + class-kill check); committed measure graded first; scan graded as scan; CALIBRATED budget spent: 0. |
| **Physics class** | **FAIL → OPEN** (shape not earned; **1-DOF release-measure class KILLED**; endpoint IDENTITY as declared) | One release angle can carry the *continuum* but not the *shape*: the measured spectrum's two zeros are per-particle 3D state-count fingerprints, and a single angle has no sphere. |

## Numbers

| Quantity | Value | Anchor | Label |
|---|---|---|---|
| Q = (m_n−m_p−m_e)c² | 0.782333 MeV | ≡ Q_β | IDENTITY (endpoint by construction — never sold) |
| β₀ from (γ₀−1)m_ec² = Q | 0.918637 (γ₀ = 2.530988) | NP14's 0.91859c (+0.005%) | IDENTITY inversion |
| Law-V complement (symmetric point) | 0.395103c | NP14's 0.39522c | IDENTITY |
| Anchor shape | dN/dT ∝ p_e E_e (Q−T)²; ⟨T⟩ = 0.3028 MeV, peak 0.2471 MeV | measured allowed (Kurie) shape | OBSERVED (rival machinery, quarantined; Coulomb/recoil/radiative omitted — declared v1) |
| **M1 isotropic-projection (COMMITTED)** | **KS D = 0.4900**, TV = 0.4986, ⟨T⟩ = 0.1368 MeV | gate: D ≤ 0.05 PASS / ≤ 0.15 QUALIFIED | **FAIL G1 → OPEN** |
| M0 tangential line at Q (scan) | D = 1.0000 (δ-line — the two-body problem) | — | FAIL (scan) |
| M2 energy-projection Qcos²θ (scan) | D = 0.2436 | — | FAIL (scan; closest, still 5× past PASS) |
| M3 planar seat phase (scan) | D = 0.2932 | — | FAIL (scan) |
| G4 numerics (MC 10⁷ vs analytic CDF) | max dev 2.75×10⁻⁴ | < 10⁻³ | PASS |

**Where it deviates (the prompt's required ledger):**

| Zone | Anchor | M1 committed | Reading |
|---|---|---|---|
| low-E mass [0, 0.1Q] | 0.0797 | **0.5420** | model dumps 6.8× too much probability at low E |
| low-E exponent (pdf ∝ Tⁿ) | **+0.500** | **−0.506** | anchor *vanishes* as √T; model *diverges* as 1/√T — opposite behaviour |
| mean ⟨T⟩ | 0.3028 MeV | 0.1368 MeV | ×2.2 too soft |
| endpoint mass [0.9Q, Q] | 0.0039 | 0.0124 | 3.2× too much at the top |
| endpoint exponent (pdf ∝ (Q−T)ⁿ) | **+1.990** | **+0.014** (step) | anchor vanishes *quadratically*; model hits the endpoint with a finite step |

## What is earned vs owed

**Earned:**
1. **The continuum exists** — a variable partition of one fixed seat speed does produce a
   continuous spectrum on [0,Q] (vs M0's line, the historical two-body problem). Flagged
   honestly: this is cheap — *any* variable split buys it; the shape was the earnable content.
2. **The class-kill, verified numerically (the real result).** The lemma stated in RUN_LOG
   before running is confirmed by the Phase-4 table: every analytic 1-DOF release measure has
   endpoint exponent in {0, −½, …} (measured: M1 +0.014, M2 +0.004, M3 −0.489) and low-E
   exponent −½ — the anchor demands **+2** and **+½**. No release-angle geometry, however
   clever, can reproduce the β shape. This is a *premise* kill, not a member kill: it closes
   the whole direction and cannot be fished back with weights (forbidden retro).
3. **The dimension-counter reading.** The anchor's two zeros are per-particle 3D state-count
   fingerprints: (Q−T)² = E_ν² is the area of the neutrino's exit-direction sphere; p_e E_e is
   the electron's. The β-spectrum shape *measures* that each outgoing light particle has three
   translational degrees of freedom — which is exactly PPT10's "straight light in a 3D lattice".
   This converts the FAIL into a sharp acceptance test for the cascade root (below).

**Owed (cascade root):**
- **The 3D exit-channel count.** To earn the shape natively SDT must *derive* — not import —
  N_exit(E) ∝ E² for the unwound remainder (neutrino) and ∝ p_e E_e for the freed electron,
  as counts of distinguishable straight-lattice exit rays / gear-release configurations.
  Candidate instrument: **FLM14** (rotating-spation sequential occupancy — what counts as a
  distinct exit configuration). Importing p²dp verbatim is the rival's phase space and stays
  forbidden. Secondary debt: the budget-speed → E_ν map (PPT10/PPT11) — declared in RUN_LOG,
  still open; conservation did that work in v1.
- Declared v1 omission (Coulomb/Fermi-function, recoil, radiative): irrelevant at this miss
  size (few-% effects vs D = 0.49); noted for any future v2.

## Success criteria scoring (PROMPT §5 / §8)

- [ ] T1 shape match — **FAIL** (D = 0.4900 > 0.15; no scan member below 0.24 — no
  look-elsewhere temptation arose)
- [ ] T2 endpoint behaviour — **FAIL** (step vs (Q−T)²; ν-side 3D count missing)
- [ ] T3 low-E behaviour — **FAIL** (T^(−½) divergence vs √T vanishing; e-side 3D count missing)
- [x] T4 class-kill lemma — **CONFIRMED** (whole 1-DOF class killed; the investigation's earned negative)
- [x] G2 endpoint = Q — IDENTITY by construction, labelled, never sold
- [x] G4 numerics — PASS (2.75×10⁻⁴)

## Stress-test self-audit

1. **Identity/circularity:** Q and β₀ are IDENTITY inputs (declared before code); the endpoint
   landing at 0.782333 MeV earns nothing and was never graded. The anchor shape sat in the
   OBSERVED column only — delete-test: nothing in the M1/M2/M3 chain references p_e E_e (Q−T)².
2. **Fished factors:** none. Measures fixed in RUN_LOG before any number existed; no weight,
   window, or measure added after results. CALIBRATED budget spent: 0 of 0.
3. **Dimensions:** all energies MeV via `measured::MeV_to_J`; u, β dimensionless; exponents
   dimensionless.
4. **Class:** FAIL → OPEN. No RETRO-PASS, no PLUG, no tolerance widening, no scan promotion.

## §D Seven questions (HUNTER_PROTOCOL, on the G1 FAIL)

1. **Why exactly?** KS D = 0.4900 (gate 0.15). Mechanism: the isotropic-projection measure
   piles 54.2% of probability into [0, 0.1Q] (anchor 8.0%) because T ∝ u² at small u; the
   spectrum diverges as T^(−½) where the anchor vanishes as T^(+½), and steps at the endpoint
   where the anchor vanishes as (Q−T)^1.99.
2. **Recoverable?** Not within the class. Phase 4 confirms the pre-stated lemma: no analytic
   1-DOF release measure can produce endpoint exponent +2 — the miss is not the member (M1)
   but the premise. Recovery requires a different *kind* of object, not a better angle map.
3. **What did the target fail to account for?** Multiplicity. The partition angle selects
   *which* (E_e, E_ν) split occurs but not *how many ways* it can point: the anchor's two zeros
   are the areas of the electron and neutrino momentum spheres. One angle has no sphere.
4. **Which premise erred?** "SHAPE = f(release angle on the seat)." The seat geometry sets the
   split; the *weight* of each split is a 3D state count per outgoing light particle.
5. **What freedom corrects it?** A native count of distinguishable straight-lattice exit rays:
   N_exit ∝ E² (massless remainder) and ∝ p_e E_e (freed electron) must fall out of lattice
   direction-counting / FLM14 sequential-occupancy gearing — derived, not inserted.
6. **Native or knob?** Neither exists today. No knob was available that could fake an exponent
   (+2 is unreachable by reweighting a 1-DOF measure with any bounded density — the kill is
   knob-proof, which is why it is clean).
7. **Cascades?** Yes — root shared with **FLM14** (what counts as a distinct exit
   configuration) and **PPT10/PPT11** (the budget-speed → E_ν map, the declared ontology debt).
   Not an independent failure; logged to the stack ledger.

**Recovery grade: PARTIAL** (premise error named and proven class-wide; the corrective freedom
identified with a concrete acceptance test — N_exit(E) ∝ E² from lattice counting — not yet
derived).

---

> **Prompt completion A · Physics class FAIL→OPEN (shape not earned; 1-DOF release-measure class KILLED; endpoint IDENTITY) · Recovery PARTIAL · Cascade root: native 3D exit-channel count — release-measure geometry → FLM14 gearing; PPT10/PPT11 ν-energy map debt**

*NP22 · executed 2026-07-04 · honest FAIL→OPEN · the continuum is free, the shape is a
dimension counter: it demands a sphere per light particle, and SDT must earn its spheres from
the lattice or concede the shape to phase space.*
