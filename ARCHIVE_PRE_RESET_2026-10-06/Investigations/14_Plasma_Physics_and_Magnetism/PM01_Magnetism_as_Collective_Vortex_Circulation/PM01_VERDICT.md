# PM01 — Verdict: Magnetism as Collective Vortex Circulation

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04
**Tool:** `pm01_magnetism.cpp` (MSVC `/std:c++20 /O2 /utf-8`, real run, exit 0) → `pm01_results.txt`
**Pre-commitments:** `RUN_LOG.md` (written before code; no gate moved after run).

---

## 1. Deciding metrics (all vs pre-committed gates)

| Phase | Gate | Result | Class |
|---|---|---|---|
| P1 | Γ_v native, zero magnetons | κ = h/m_e = 7.274e-4 m²/s (a circulation, FD02); g = 2.0023 dimensionless; **0 magnetons in any number** | NATIVE units held |
| P2a | aligned-bundle \|w\| exponent −1±2% | **−1.0000**; enclosed-count error 1.3e-15 | **NATIVE** — forced by circulation-count conservation (Law VI quanta) |
| P2b | wire B_φ exponent −1±2% + control must fail | conserving wake → **−1.0000**; non-conserving control → **−2.0000 (fails, as it must)** | **NATIVE** — forced by per-carrier momentum-flux conservation (FD02 drag) |
| P2c | ∇·B/∇×w ≤ 1e-9 | **1.5e-16** | IDENTITY (pre-flagged: div∘curl≡0 is calculus; SDT content = the identification B≡∇×w, which makes E58 a theorem) |
| P3 | Lorentz sign matrix 4/4 from handedness | **Magnus 2/4** (signed by own h, field-blind: ω saturates 1.0→0.5→0.5 for Ω=0,1,10); **Coriolis 2/4** (ω∝Ω exact ratio 10.000, handedness-blind) | **OPEN** — see §2 |
| P4 | magnetosphere | **DEFERRED** (pivot row 5: needs the µ₀-free gain P3 shows is open). Chapman–Ferraro standoff 8.1 R_E vs ~10 R_E printed as OBSERVED-inputs context, labelled CONVERGENCE, not claimed | DEFERRED |

**Earned scaling law:** *the Ampère exponent −1 is a conservation law, not a fit* — it is forced in
both magnet geometry (conserved circulation count: ∮w·dl = N_enc·κ) and wire geometry (conserved
per-carrier momentum flux → 1/s wake), and the non-conserving control field **fails** it (−2.0000).
That is the delete-test in action: the exponent survives only when the native conservation law is in
the chain.

## 2. The load-bearing negative (P3) — Golden-Rule Q1 answered honestly

The prompt's own test: *"can the Lorentz sign be forced by EMC03 handedness alone… if it has to be
put in by hand, magnetism is borrowed narration and PM01 fails its own test."* Measured answer: **it
has to be put in by hand, today.** SDT's two native perpendicular-push channels split the Lorentz
force between them and neither is bilinear:

- **Magnus channel** (FD07-native): push signed by the carrier's OWN handedness — but gyration
  frequency is set by its own κρ/m and *saturates* with field strength (never ∝ field). 2/4 cells.
- **Entrainment/Coriolis channel**: gyration exactly ∝ field vorticity (ratio 10.000 for 10× field)
  with correct field-sign turning — but handedness-blind. 2/4 complementary cells.

`qv×B` is **bilinear** in (carrier handedness) × (ambient swirl). The bilinear coupling coefficient
is dimensionally e-shaped, i.e. it is the SAME quantity EMC02 certified as an irreducible Tier-1
input.

### §D seven questions (on the P3 OPEN)

1. **Why fail?** Both native channels are linear: Magnus F = ρκ_h ẑ×(v−w) carries h but not |∇×w|;
   Coriolis F = v×(∇×w) carries |∇×w| but not h. Cells: 2/4 + 2/4, and the frequency scalings
   (0.5/0.5 vs 1.0/10.0) prove it is not a numerics artefact.
2. **Recoverable?** Only by deriving a handedness-gated entrainment coefficient g_hb (grip per unit
   ambient swirl per unit handedness).
3. **What did the target fail to account for?** That Law III occlusion is scalar (unsigned); EMC03
   supplies the *static* surplus/deficit sign, not a dynamic swirl-grip magnitude.
4. **Errored premise:** "EMC03 handedness alone fixes the Lorentz sign." It fixes the electric sign;
   the magnetic sign needs the bilinear grip.
5. **Freedom that corrects it:** one native bilinear coefficient g_hb.
6. **Accounting for that freedom:** currently a bare knob. Named native candidates: (i) PPT06 ℓ=2
   traction gearing of the carrier wake into the collective swirl (needs the APS04 Phase-2 lattice
   wake solver — the same missing tool); (ii) the **FLM14 rotation DOF / geared constraint channel**
   (ADJ-7), a new carrier the EMC02 proof never examined.
7. **Cascade?** YES — shared root with PM02 (carrier-sign EMF), PM04 (native gain), PM06 (qB/m).
   Root ID: **HG-1 (handed bilinear gain ≡ EMC02 charge closure)**.

**§G-3 compliance:** this OPEN is *not* "never derivable." Premise class of the negative: static,
single-channel, linear vortex–swirl coupling (Magnus ⊕ Coriolis). **Re-open condition:** a native
bilinear coupling from the FLM14 rotation DOF or a lattice wake-solver traction computation.
**Faith ledger (§G-1):** the per-carrier wake profiles (1/s azimuthal, 1/s Stokeslet) are justified
by conservation, not faith; the identification B≡∇×w is named as the ontological posit under test.

## 3. Engine tension (required disclosure)

`laws.hpp:193–199` stores nuclear moments in µ_N. PM01 introduced no magnetons anywhere, but cannot
claim the engine is magneton-free. The no-magneton rule remains aspirational vs the engine
(Harvey's call; engine edit out of scope).

## 4. Generative questions opened (§10 log)

- Is µ₀ the per-carrier axial-wake amplitude per unit drift (γ ↔ µ₀e·v_d), i.e. a relay-stiffness
  ratio? (Blocked behind HG-1.)
- Does the co-handed Magnus instability in rigid ambient swirl (found in P3: runaway, not orbit)
  correspond to a real plasma instability class? Unexplored.

## 5. Verdict

Ampère-as-conservation (P2a/P2b, with a failing control) and ∇·B≡0-as-theorem-given-identification
are earned. The Lorentz bilinear sign×gain is not earned and is the cluster's root debt.

> **Prompt completion D** · **Physics class** NATIVE (P2 conservation-forced exponents) / IDENTITY
> (P2c, pre-flagged) / **OPEN** (P3 bilinear gain; P4 deferred) · **Recovery** PARTIAL (route +
> premise named: HG-1; freedom not yet justified) · **Cascade root** HG-1 (= EMC02 charge closure).
