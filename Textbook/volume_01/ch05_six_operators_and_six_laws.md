# Chapter 5 — Six Operators and Six Laws

*Volume I — Ontology, Geometry and Admissible States.*
Draft of 9 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. Executable companion: `Textbook/examples/ch05_operator_law_map.py`; pre-registration and captured output in `Textbook/validation/`.

## 5.1 The physical question

The constitution (`Theory/00_Ruleset.md`) states six operators on a state, nine axioms and seventeen theorems. The engine (`laws.hpp`) is organised as six laws and numbers eighteen theorems. A third text, the Complete Laws paper, numbers its theorems yet differently. Six operators and six laws are the same count and not the same list. This chapter maps one onto the other, records where the numbering of the three texts disagrees, and states how the rest of this book labels what it reports.

## 5.2 The six operators

The Ruleset's operators act on the state of the medium. Each is a requirement that a state description must support.

| operator | statement | role |
|---|---|---|
| (1) continuous throughput | $\Phi=N\varepsilon$ | the content the medium delivers at a point |
| (2) boundary event | $\varepsilon\to(\varepsilon_d,\varepsilon_t,\varepsilon_a)$ | the partition of arriving content at a boundary |
| (3) traction condition | $\tau=\varepsilon_d/\varepsilon=1/3$ | the share that reorganises a form |
| (4) wake formation | $\mathcal W$ = anisotropic residue of non-traction throughput; multipoles $\ell=1$ electric, $\ell=2$ magnetic, $\ell\ge3$ structure | what a moving or occluding form leaves behind |
| (5) propagation law | $\Delta\theta\propto\nabla\mathcal W$ | straight line, refraction, scattering, lensing as one mechanism |
| (6) persistence constraint | $v_T^2+v_P^2+v_C^2+v_t^2=c^2$ | the movement budget |

Table 5.1. The Ruleset's operators.

Operator (2) needs a declared accounting basis. Stored deformation, transmitted transport and other channels must not be counted twice: for an exhaustive energy partition the sum of the channel energies equals the incoming energy plus any released storage, and for momentum the directional signs enter as well. Operator (3) fixes a share, $1/3$; Chapter 9 shows that the factor is a statement about the second moment of the arrival and that the traction of a face depends on how the face responds, so that a universal substitution of one third in a directional wake would erase the wake. In the isotropic case, for a unit direction $\hat n$ distributed over the sphere,

$$\langle \hat n\otimes\hat n\rangle=\tfrac13 I,\qquad \Pi=\tfrac{\operatorname{tr}\Pi}{3}I,\qquad \Pi=\tfrac{\operatorname{tr}\Pi}{3}I+\Pi_{\rm dev}\ \text{in general}. \tag{5.1}$$

Rotational invariance forces the isotropic second moment to be proportional to the identity, and the trace fixes the constant. The deviatoric part $\Pi_{\rm dev}$ is what a directional projection $\hat m\cdot\Pi_{\rm dev}\cdot\hat m$ picks up (Chapter 9, Section 9.5).

## 5.3 The six laws

The engine's header states the laws and the theorem ranges they carry:

| law | engine namespace | banner | responsibility |
|---|---|---|---|
| I cosmological relay throughput | `law_I` | R1–R6; T1–T2 | convergence content $\Phi$, $P_{\rm conv}$ |
| II release cascade | `law_II` | corollaries (no numbered theorem) | release-cascade reference quantities, pressure domains |
| III convergent boundary pressure | `law_III` | T3–T4 | occlusion response and the universal interaction |
| IV inertial mass | `law_IV` | T5–T7 | exclusion volume, engaged-volume resistance, transport |
| V movement budget | `law_V` | M1–M3; T10–T17 | circulation budget and its consequences |
| VI vortex topology quantisation | `law_VI` | T18 | winding, topology, rotational structure |

Table 5.2. The Six-Law banner of `laws.hpp` (lines 8–13).

The header reports "9 axioms, 2 lemmas, 18 theorems". The executable check of this chapter found the banner ranges exactly as stated: Law I T1–T2, Law III T3–T4, Law IV T5–T7, Law V T10–T17, Law VI T18, none for Law II (criterion C2); the six banners and the six `law_*` namespaces occur in the order I to VI (C3, banners at lines 242, 308, 452, 595, 880, 2377; namespaces at 248, 316, 457, 603, 895, 2395). The ranges leave the numbers 8 and 9 outside every banner (C5).

## 5.4 The map

An operator is a requirement on the state, and a law is an executable constraint on the response. The correspondence is many-to-many.

| operator | law carrying it | principal engine symbols | chapters of this book |
|---|---|---|---|
| (1) throughput | I | `law_I::N`, `epsilon`, `Phi`, `P_conv` | 4, 9 |
| (2) boundary event | II, with the partition share in IV | `law_II` pressure-domain quantities; `law_IV::resistance_from_engaged_volume` | 12, 15 |
| (3) traction | IV (T7), with the arrival moments in III | `law_IV::convergence_floor::angular_gradient_fraction`, `P_cf` | 9, 12 |
| (4) wake | III (the sign of the force), VI (wake geometry) | `law_III::F_occlusion`, `law_VI` winding | 11, 17–19 |
| (5) propagation | III with the depth block | `depth_closure::shapiro_delay`, bending relations | 14, 39 |
| (6) persistence | V, with VI for the winding speeds | `law_V::v_circ`, `law_VI::topology::budget_residual` | 7, 13, 17 |

Table 5.3. Operators against laws.

Law II has no numbered theorem; it supplies the reference quantities of the release cascade, the solar luminosity as a measured anchor and the pressure domain $r=\sqrt{L/(4\pi F_{\rm CMB})}$ computed from it. The anchor and the computation are separate: `pressure_domain(L)` is a function conditional on $L$. The winding classifier of Law VI distinguishes topology; a lifetime additionally needs an energy barrier and a dynamical operator (Chapter 7).

*Operator number and law number are not interchangeable identifiers.* The coincidence of six and six does not mean that operator (3) is Law III.

## 5.5 Theorem numbering and supersession

Three texts number the theorems. Table 5.4 sets them side by side for the statements they share. Rows where the numbers differ are marked.

| statement | Ruleset | engine | Complete Laws paper |
|---|---|---|---|
| shell cancellation | T1 | Law I, T1 | Theorem 1 |
| convergent throughput $\Phi=N\varepsilon$ | T2 | Law I, T2 | Theorem 2 |
| isotropy of arrival | not numbered | not numbered | Theorem 3 (Corollaries 3.1, 3.2) |
| occlusion force | T3 | Law III, T3 | **Theorem 4** |
| force unification | T4 | Law III, T4 | in Theorem 4's corollaries |
| inertial mass | T5 | Law IV, T5 | Theorem 5 |
| equivalence of inertial and gravitational mass | T6 | Law IV (stated, no number) | Theorem 6 |
| traction $\tau=1/3$ | **T7** | Law IV, T7 | Theorem 7 is the speed limit $c$ |
| interaction-radius relation $\sqrt{R_pr_e}$ | **T8** | carried in `law_III`, outside the banners | Theorem 8 is a per-shell epoch relation |
| Coulomb identity $k_ee^2=\alpha\hbar c$ | **T9** | `coulomb_identity`, outside the banners | Theorem 9 concerns a luminous body |
| movement budget … c-boundary | T10–T17 | Law V, T10–T17 | Theorems 10–17 |
| vortex topology quantisation | **none** | Law VI, T18 | none |

Table 5.4. Theorem numbering in three texts (executed reading of the Ruleset table, the engine banner and the Complete Laws headings).

Four discrepancies follow, and the supersession ledger carries each.

1. **Occlusion force.** The Complete Laws call it Theorem 4 and number isotropy Theorem 3; the Ruleset and the engine call it T3. The engine's comment at `F_occlusion` records that the label was corrected on 2026-10-16 to match the Ruleset. This book writes the Ruleset number and, where a Complete Laws passage is cited, writes "Complete Laws, Theorem 4".
2. **T7 to T9.** The numbers 7, 8 and 9 name different statements in the Ruleset and the Complete Laws paper. The book cites by name, and by the Ruleset number only where the engine does.
3. **T18.** The engine carries a theorem T18 (Law VI). The Ruleset's table stops at T17 (criterion C4: T18 appears in `laws.hpp` and is absent from the Ruleset table).
4. **T16.** The Ruleset states gravitational dilation as $d\tau/dt=\sqrt{1-zR/r}$. The engine defines no function of that name any longer and defines `depth_closure::clock_rate` $=1-z$ (criterion C6), after the repair recorded in Chapter 3 (R3.2). The Ruleset text has not been updated.

The axioms carry a smaller discrepancy, noted in Chapter 4: the Ruleset numbers shell structure R4, omnidirectional release R5 and shell cancellation R6, while Section 4 of the Complete Laws cites isotropic release as R4 and fidelity as R5.

**A limit of the scan.** The instrument counts the tokens `T<n>` in `laws.hpp`. A theorem number is a reference only inside the law that carries it: the counts for T11 to T15 lie in `law_V` (lines 921–946). The tokens T8 and T16 at lines 2180–2181 belong to the nuclear section and are labels of triton shells (the eight-triton and sixteen-triton shells of the closure sequence), not theorem numbers. T6 and T9 have no token in the file. The scan therefore establishes the banner ranges, not a count of references.

None of these discrepancies is edited here. The Ruleset and the engine are canon, and a change to either, including a comment, waits for the author's approval.

## 5.6 Closure versus implementation

An implemented expression can be an adopted law, a deduction, a metrological conversion or a measured anchor. The labels of this book keep these apart and are fixed here for the chapters that follow.

| label | meaning |
|---|---|
| MEASURED-INPUT | a value that enters from outside the framework (CODATA, IAU, FIRAS, a catalogue entry) |
| DERIVED | follows from the axioms and the laws with no input beyond the measured seed |
| COMPUTED | a deterministic calculation from the laws that may carry measured inputs |
| CALIBRATED($n$) | $n$ parameters set by a measured value; each is named |
| OBSERVED | validated against measurement, mechanism established |
| PENDING | mechanism identified, computation incomplete |
| CONSTRUCTION | true by construction: both sides computed from one input; shown for consistency and never counted as evidence |

Table 5.5. Labels used in this book.

Two further rules govern their use. A number carries exactly one label. A label of CONSTRUCTION, shared-input or CALIBRATED is applied only after the contaminating input has been named in one line: the quantity, the chain by which it was measured, and where it enters (the downgrade trace). Agreement with a formula of another framework is recorded as convergent and is never the content of that line; the direction of derivation is fixed, and a quantity that the Six Laws output (a gravitational constant, a Planck-form expression, a Lorentz factor) is never an input to them. Where a statement matches a known result the book gives provenance and discrimination separately: provenance says where the derivation started, and discrimination says whether the shared number can tell the frameworks apart.

The two-axis audit of `Theory/05_Provenance_and_Correspondence.md` supplies the crosswalk. The legacy labels DERIVED, COMPUTED, CALIBRATED, OBSERVED and PENDING map onto its provenance axis (SDT-first, calibrated, unresolved) with correspondence recorded separately; the classes A to F are a projection of the two axes. A formula earns class C, convergent with a known result, only when no field of its derivation depends on the known value it later matches (the circularity assertion): delete the correspondence check and a class C number is unchanged, whereas deleting it from a class E number removes the number.

## 5.7 Input ledger and residuals

This chapter reports no physical measurement; its executed values are structural readings of three texts.

**Residuals.**

* **R5.1 — Ruleset currency.** The Ruleset's table lacks T18 and states the superseded T16. Proposed correction, pending approval: add the T18 row (Law VI, vortex topology quantisation) and replace the T16 expression by $d\tau/dt=1-z$ with its domain, citing the repair.
* **R5.2 — the numbering of T7–T9.** The Ruleset and the Complete Laws paper assign different statements to 7, 8 and 9. A single numbering has not been chosen.
* **R5.3 — the boundary event.** Operator (2) needs an accounting basis (energy, momentum, or both with signs); the engine implements no routine for the partition $\varepsilon\to(\varepsilon_d,\varepsilon_t,\varepsilon_a)$ as such, and Chapter 15 sets up the ledger.
* **R5.4 — wake formation.** Operator (4) is carried by two laws, and the multipole assignment ($\ell=1$ electric, $\ell=2$ magnetic, $\ell\ge3$ structure) is stated without a derivation in the Ruleset.
* **R5.5 — Law II.** The release cascade has no numbered theorem; the statements it supports are corollaries.

## 5.8 Implementation and verification

```
bash Textbook/tools/py_run.sh ch05_operator_law_map
```

The criteria of `Textbook/validation/ch05_PRE_REGISTRATION.md` were registered before the script existed. Run 1 evaluated V1, V2 and C1–C6, all consistent with the predictions, and then stopped in the reporting section with an output-encoding fault of the isolated interpreter; run 2 (`ch05_run2_output.txt`) is the run of record and met every criterion.

## 5.9 Exercises and answers

**Exercise 1.** Show $\langle\hat n\otimes\hat n\rangle=\tfrac13I$.

*Answer.* The average is a rotation-invariant symmetric tensor, so it is $A\,I$. Its trace is $\langle\hat n\cdot\hat n\rangle=1$, so $3A=1$.

**Exercise 2.** Which operators would an exact solution of Law VI alone leave unconstrained?

*Answer.* Law VI classifies windings and carries the circulation speeds, so it constrains operator (6) and part of (4). Operators (1), (2), (3) and (5) are carried by Laws I to IV and the depth block.

**Exercise 3.** Classify the koppa definition $\mathrm{Om}=v^2R/c^2$ and the engine's $P_{\rm eff}$ by the two-axis spine.

*Answer.* The koppa definition is a posited definition (provenance SDT-first, correspondence internal), class A in the spine, with the second label carrying the correspondence to the circular-motion identity. $P_{\rm eff}$ is class C in the engine (`laws.hpp:465–476`): it is built from $\alpha$, $\hbar$, $c$, the lock boundary $4\hbar/(m_pc)$ and $r_e=\alpha^2a_0$, with the measured $R_p$, $k_e$ and $e$ absent from the forward form; `P_eff_from_volume` is a rewriting of the same identity (Chapter 11).

**Exercise 4.** A result $y=f(x)$ matches a known value. How does the delete-test separate a class C number from a class E number?

*Answer.* Remove the correspondence check. If $y$ is computed from the derivation alone and is unchanged, it is class C. If $y$ was obtained by setting a parameter to match the known value, removing the check removes the means of obtaining $y$.

**Exercise 5.** Why does the scan of this chapter not count references to T6?

*Answer.* The engine states the equivalence of inertial and gravitational mass in prose ("both measure the same $V_{\rm disp}$") without writing the number, so a token scan finds none. The banner range for Law IV (T5–T7) is the reference.

## 5.10 Scope

Established in this chapter: the six operators and their roles; the six laws and their banner ranges, read from the engine; the many-to-many map between them; the theorem numbering of three texts and four discrepancies among them; and the labels used in the rest of the book.

Not established: a single agreed numbering of T7–T9 (R5.2), the accounting basis of the boundary event (R5.3), and the derivation of the multipole assignment of the wake (R5.4). Ruleset corrections are proposed and not applied.

*Where it leads.* Chapter 6 fixes the measurement chains and dimensions that the labels refer to. Chapter 12 returns to operator (3), Chapter 15 to operator (2).
