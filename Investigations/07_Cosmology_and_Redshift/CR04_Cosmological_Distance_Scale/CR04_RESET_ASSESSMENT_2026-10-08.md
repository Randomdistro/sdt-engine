# CR04 (cosmological distance scale) — blank-slate specification audit (2026-10-08)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`, with the method of 2026-10-07 (native mechanism first; the measured value loaded only against a fixed prediction; no census over candidate forms). Record type: specification audit with the arithmetic that is executable. No instrument was written, because the prompt does not specify the native quantities its phases need.

## 0. Inputs read and exposure
Read: `CR04/PROMPT.md` in full; the graph (CR04: layer 0, reach 39; named dependents CR03, CR05, CQ41, FLM06, GOM05); `laws.hpp` comments at the R_CMB definition and at the cosmology block (R_CMB is an observed input; the engine comment at the Law VI header states that the T2/T3/T10 derivations use "No BAO ruler, H_0, R_CMB, metric history, G"). Not read: `CR04_VERDICT.md`, `README.md`, the four `CR04_*.md` phase notes, `cr04_cosmological_derivation.cpp`, the two results files.
Exposure: the prompt's own header states that the earlier tool did not compile, that its results file was hand-written, and an earlier outcome ("r_c −50%, QUALIFIED, R_CMB = CLASS X"). Those were read before this record.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | The two stated targets are not consistent. The objective gives R_CMB ≈ 4.4×10²⁶ m (the comoving distance to recombination); Phase 2 and the acceptance criteria give 9.527×10²⁶ m (the engine's `measured::R_CMB`). They differ by a factor of 2.17. |
| D2 | gating | Phase 1 uses "BAO wavelength = c_s × t_coupled" with "coupled epoch duration" t_coupled. No native definition of the duration is given, and the engine has no expansion history (its comment: no metric history). The sound speed c/√3 follows from the radiation pressure u/3 (Law I): that part is native. |
| D3 | gating | Phase 2 defines H(z) as "(dP/dr)/(ρ_eff c²)", a pressure-gradient strain rate, with ρ_eff and the pressure distribution unspecified; the integral r_c = ∫c dz/H(z) then has no native integrand. The prompt itself says H₀ is measured unless CR05 derives it. |
| D4 | construction | Phase 3: the linking-number densities are τ_plasma = (W_e + W_p)n_b = 4n_b and τ_neutral = n_H W_H ≈ n_b, so the ratio 4 is the sum of the two input integers (1 + 3) divided by an assumed W_H = 1. The prompt notes that W_H = 2 or 4 changes the ratio. The step from the ratio to "the lattice decouples and sound waves freeze at the BAO wavelength" has no stated equation. |
| D5 | method | Phase 4 is a search for a pattern ("is k_Hubble an integer, rational, or a simple formula in {k_p, k_H, k_e}?") against a value built from measured H₀ and R_CMB. This is a census against a target and is not run here. |
| D6 | data | H₀ is not in the engine's `measured`; the BAO ruler (147 or 150 Mpc, both appear) has no manifest row. |
| D7 | gating | The success metrics are agreement percentages against measured values (5%, 3%, 10%); no registered native prediction exists to be tested. |
No downgrade is made on agreement grounds.

## 2. Dependencies
**Suppliers:** none among the investigations (graph); named in the prompt: GOM02 (k-hierarchy), APS03, CR03 (transfer function), Law I, Law VI. **Dependents:** CR03 (f), CR05, CQ41, FLM06, GOM05. The engine states that R_CMB and H₀ are observed inputs and that f = P_eff/P_conv is conditioned on R_CMB (class B-conditioned): CR04 does not change that at present.

## 3. The five questions
**1. What do we not know?** What distance scale the relay medium itself fixes. The stated ruler (BAO) is a standard-cosmology construct (a sound horizon at an epoch in an expansion history); a native statement must say what in the relay medium has a length that large, and from what rule. Until that is stated the question has no native observable.
**2. Why does it matter?** R_CMB is the one observed input that conditions the transfer function f and the causal depth N = R_CMB/ℓ_P on which the mass scale Φ and V_disp depend (Law I, Law IV); every absolute value that passes through Φ inherits it. If R_CMB has a native origin, the framework loses its last cosmological input; if it does not, it must be carried as an observed boundary.
**3. By what methods can we reach a better understanding?** (M1) State natively what sets the distance to the boundary of the convergence (a relay-depth rule: the number of relay shells and their rate), with the prediction fixed before any measured distance is loaded. (M2) Register what the BAO scale would be in the relay medium (the wavelength of the lowest standing relay mode between the coupling boundary and the matter) with its own derivation, not a fit. (M3) Define the topological ledger of recombination with the integers fixed by Law VI and a stated mechanism for the decoupling. (M4) Do not search for patterns in k_Hubble.
**4. What would prove us wrong?** (a) Failure-pathway indicators: a free duration or strain rate chosen to match a distance; agreement only after loading H₀ or R_CMB; a pattern found by scanning; two targets of different values (D1) treated as one. (b) Falsifying mathematics: the relay-depth rule must give R_CMB and the ruler with the same single input, before comparison; the ratio ruler/R_CMB (= 4.76×10⁻³, see §4) must follow with no new parameter. (c) What it breaks: if R_CMB is not derivable, f and N remain conditioned on an observed value, and every absolute V_disp and P_conv value is conditional on it, as the engine already states.
**5. Done when** the relay-depth rule is registered natively and its two predictions (R_CMB and the ruler) are compared once, or the specification is recorded as lacking and the missing quantities are named with their suppliers (this record).

## 4. What is executable now (arithmetic only; no mechanism tested)
- The sound speed from the radiation pressure (Law I): P = u/3 gives c_s = c/√3 = 1.7309×10⁸ m/s (the equation of state of an isotropic radiation bath; the engine holds u/3 as `law_I::P_rad`).
- The ratios of the stated targets: 147 Mpc = 4.5360×10²⁴ m; 4.5360×10²⁴/9.527×10²⁶ = 4.761×10⁻³ (1/210.0); against 4.4×10²⁶ m the ratio is 1.031×10⁻² (1/97). The two differ by 2.17 (D1).
- The time to cross 147 Mpc at c/√3 is 2.621×10¹⁶ s = 8.30×10⁸ years: this is the quantity "t_coupled" would have to equal, which is stated here as a requirement of the form of Phase 1, not as a result (no native duration exists).
- Phase 3: τ_plasma/τ_neutral = (1 + 3)/W_H = 4 for W_H = 1; 2 for W_H = 2; 1 for W_H = 4; the integers 1 and 3 are Law VI inputs; the ratio is a consequence of the assumed W_H (CONSTRUCTION; contaminating input: W_H, assumed in the prompt, not derived).
(Arithmetic by hand, checked twice; no instrument.)

## 5. Grades
| Item | Grade | Reason |
|---|---|---|
| Phase 1 (BAO from lattice resonance) | **G2, open: not run** | the sound speed is native; the duration is undefined; no native ruler rule |
| Phase 2 (R_CMB from H(z)) | **G2, open: not run** | H(z) as a strain rate is undefined; the prompt itself makes H₀ the bottleneck |
| Phase 3 (linking ratio) | **G3, CONSTRUCTION** | the ratio is an arithmetic consequence of W_e + W_p over an assumed W_H; no decoupling equation |
| Phase 4 (k_Hubble pattern) | **not run** | a census against a target; withdrawn as a method |
| The stated targets | note | two incompatible values (4.4×10²⁶ m and 9.527×10²⁶ m) |

## 6. Direction
1. A native relay-depth rule for R_CMB: the number of relay shells reached from a point and their rate, stated in relay terms, with the prediction registered before comparison; the engine's N = R_CMB/ℓ_P and the FLM06 closure ℓ_P² = ϟƛ are the relevant supplier statements.
2. The ruler as the lowest standing relay mode between the coupling boundary and the matter, with the ratio to R_CMB fixed by the same rule.
3. A decoupling equation for the recombination step (what quantity changes by the ratio found in Phase 3 and how that stops the relay of the sound mode), with W_H derived from Law VI.
4. Manifest rows for H₀ and for the BAO ruler (with the two values in use resolved).
5. CR05 (H₀) remains the supplier on which the prompt itself says R_CMB depends.

## 7. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
