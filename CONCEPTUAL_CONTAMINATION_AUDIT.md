# Conceptual Contamination Audit — the *narration* axis

> **Status:** progressive, in-progress. Pass 1 = the magnetism thread.
> **Author of this pass:** Claude (Opus 4.8), under James Tyndall's audit brief, 2026-06-07.
> **Stance:** hostile-but-fair, and *conservative*. SDT genuinely converges on many QM
> results — a QM-sounding result is **not** automatically contamination. Nothing here is a
> recommendation to delete a result. The output is a **classification + a re-narration / derivation
> task list**, to be ratified by someone who knows SDT backwards.

---

## 0. Why a new axis at all

The repo already has a **value-provenance** audit: `Theory/05_Provenance_and_Correspondence.md`
(the A–F spine) and `FORMULATIONS_PROVENANCE_AUDIT.md` (three axes + the **delete-test**).
Those answer one question:

> *Did the matched target value enter the derivation?* (path/fuel/endpoint of a **number**)

They do **not** answer the question this audit exists for:

> *Is the explanatory apparatus — the words and the math-structure used to narrate the mechanism —
> native SDT, or borrowed from QM / classical field theory?*

These are **orthogonal**. Proof by example: census **#64 `μ_ν≡0`** is value-class **D** (the
matched value never entered — delete-test passes) **and yet** it is narrated entirely through the
imported **spherical-harmonic ℓ=2 "magnetic dipole moment"** apparatus. The value-audit is blind to
that by construction. So:

```
value_status      :  (existing spine)  A | B | C | D | E | X | F
concept_status    :  (this audit)      NATIVE | CONVERGENCE | LINGUISTIC-BORROW | STRUCTURAL-BORROW
```

A result has **both** labels. The dangerous quadrant is `value=C/D` × `concept=BORROW`: it *looks*
fully derived on the value-audit, so the borrowed concept rides in undetected.

---

## 0b. The operative de-narration rule (James, 2026-06-07)

> **The fix for borrowed language is PLAIN ENGLISH describing the motion — not a swap from QM-jargon to
> SDT-jargon.** "Technical jargon is still common English." If a sentence can't be said plainly to a
> person who can picture it, it's still hiding something.

And the specific disease to cut: **observeritis.** Borrowed physics narrates the world through an
*observer* and a *test particle* — "what a probe placed here *would feel*." SDT has no observer in its
ontology: a body whirls the lattice around it whether or not anyone drops a dummy in to measure it.
**A "test particle" is an imaginary crash-test dummy; the orbital structure is identical without it.**

So every de-narration must: (a) say what the **matter does to its neighbours** (it spins them; they spin
theirs), never what a probe would read; (b) use words a person can picture; (c) never invoke an observer
to define the thing. A re-narration that still needs a test particle to make sense has not been cured.

---

## 1. The discriminator — the **translation test**

Analogue of the delete-test, but for concepts. For any claim:

> **Strip every QM / classical-EM term and unit** (multipole, ℓ/m quantum numbers, "moment",
> magneton, spin, wavefunction, susceptibility, `∇×B`, …). **Ask: does a complete SDT-native
> mechanism remain that produces the same math / the same number?**

Four outcomes:

| concept_status | meaning | what survives the strip | fix |
|---|---|---|---|
| **NATIVE** | built from SDT primitives (pressure, occlusion, displacement, circulation, wake, relay, koppa) | everything | none |
| **CONVERGENCE** | SDT-native math that *lands on* a QM result; the QM name is only a label of the endpoint | the mechanism + the number | keep; label the match as downstream correspondence (this is the §3 defence of the value-spine) |
| **LINGUISTIC-BORROW** | the **math is native** but it is **narrated** in borrowed QM words/units | the mechanism + the number; only the *words* fall away | **re-narrate.** Do not touch the number. |
| **STRUCTURAL-BORROW** | the borrowed concept **is load-bearing** — strip it and a *gap* opens (a step, a coefficient, a count with no SDT derivation) | an incomplete mechanism | **derive it from SDT, or quarantine honestly.** Never relabel as native. |

The taste-test failure mode James named — *"sampling the core" used as if it explains something* —
is a **STRUCTURAL-BORROW masquerading as NATIVE**: a cute mechanical-sounding phrase stands in for a
mechanism that was never derived. The audit's job is to either find the real mechanism or flag the gap.

**Conservation rule (the anti-rip-out clause):** a `CONVERGENCE` or `LINGUISTIC-BORROW` verdict
**never** licenses deleting the result. Only the *narration* changes. A `STRUCTURAL-BORROW` is flagged
for derivation, not deletion, unless it also fails the value-audit (then the existing spine handles it).

---

## 1c. Named contamination class — *"particle dissolved into its wake"* (added 2026-06-08)

**The contamination:** treating a particle as a **diffuse cloud / a collection of spations**, or using one
of its *field/displacement* radii as if it were the particle's **body size**. Symptoms: "the electron is a
gear assembly of N spations"; "most of its presence is its wake, not its body"; "exclusion volume = the
particle"; the "classical electron radius" used as the electron's size.

**The rule:** a particle is a **hard, localised vortex** (Law VI: a *solid* torus / filled handlebody;
ATOMICUS rules: "the electron is a hard point at all times"). The several radii it carries are what it
**does**, not what it **is**:
- **R_body** — the actual hard body. Electron ≈ **1.1×10⁻²² m** (Law VI §5c): ≫ a spation (ℓ_P≈1.6×10⁻³⁵),
  ≪ the proton (R_p≈8.4×10⁻¹⁶).
- **R_excl** (electron ≈ 2.9×10⁻²¹ m) — the volume of lattice it *displaces*.
- **R_wake** (electron's = r_e ≈ 2.82 fm = the c-boundary / EM-speed-limit; *larger than the proton*) — how
  far its field *reaches*.
- **R_quantum** = λ_C — its *coherence* scale.
`laws.hpp:413`'s three-radii struct keeps these separate on purpose; **do not collapse them into "size."**

**The discriminator:** `V_disp/ℓ_P³` and `(4/3)π(R/ℓ_P)³` are **definitional restatements of the displaced
volume** (class-F identities) — they say nothing about what the particle is *made of*. Quoting them as
"verification" of a makeup is the tell.

**Meta-failure logged:** I introduced this contamination this session (electron as a "gear assembly of
2.4×10⁴³ spations"), and the Explore agent then *defended* it as "correct metaphor." Both were overridden.
**Examine, don't amplify — including subagents.**

---

## 2. PASS 1 — the magnetism thread

Provenance traced via `FORMULATIONS_CENSUS.md` (`#n`) and source files.

| id | claim | developed in | value_status (existing) | concept_status (this audit) |
|---|---|---|---|---|
| M1 | wake **ℓ-expansion** `ℓ0 mass · ℓ1 Coulomb 1/r² · ℓ2 magnetic 1/r³ · ℓ≥3 nuclear` | Theory/01 §2 (#29); Law VI §8 (#28) | DERIVED / C | **MIXED** — see workings |
| M2 | **"magnetic moment"** `μ = I·A = e·v_T·R/2` | CQ07; `sdt-magnetism-advanced.md` | (feeds #64) | **LINGUISTIC-BORROW (+ partial structural)** |
| M3 | **`μ_ν ≡ 0`** (open winding → no ℓ=2) | Law VI §8; CQ07 (#64) | **D** | **CONVERGENCE/NATIVE result, borrowed narration** |
| M4 | nuclear moments `μ_P,μ_N,μ_D,μ_T` in nuclear magnetons | `laws.hpp::measured` | external-input / X | **values external; mechanism native; "moment" borrowed** |
| M5 | the PRIVATE magnetism docs (`B=−∇×(∇P/P₀)`, χ, Bessel, "quantum correlation function") | `SDT_Framework_PRIVATE/sdt_docs/*` | (not in engine) | **NATIVE kernel + STRUCTURAL-BORROW shell** |

### M1 — the wake ℓ-expansion  *(the load-bearing one)*

- **What the math does.** Decomposes the convergence field Φ(**r**,n̂) into spherical harmonics
  `Y_ℓ^m` and assigns each ℓ a role and a falloff. The *falloffs* `1/r²`, `1/r³`, `1/r^(ℓ+1)` and the
  ℓ=0/ℓ=1 roles are real and reproduce Coulomb and the mass monopole.
- **What the language imports.** `Y_ℓ^m`, the integer ℓ/m **quantum numbers**, "**multipole**",
  "**quadrupole**", "**magnetic dipole moment**", and the **component counts** `1,3,5,2ℓ+1`.
- **Translation test.**
  - ℓ=0 (mass = isotropic Φ) and ℓ=1 (Coulomb from directional occlusion, solid angle `πR²/r²`,
    census #27) **survive** — these are already derived natively in Law III without any harmonic.
    → **CONVERGENCE** (the harmonic label is decorative here).
  - ℓ=2 "magnetic dipole moment" **does not survive intact.** Strip the harmonic and the SDT-native
    object is **the helical wake of an organized circulation** (James's mechanism). The *helix* and a
    *steeper-than-Coulomb falloff* are plausibly native (more structured pressure pattern → faster
    dilution). But the specific **"5 traceless-symmetric components"** and the name "quadrupole moment"
    are pure angular-momentum representation theory — **STRUCTURAL-BORROW**: that count has no SDT
    derivation in the corpus; it's imported because it's what ℓ=2 *means in QM*.
  - ℓ≥3 "nuclear form factors" — same: the *name* is borrowed; the SDT-native object is direct
    vortex-mesh occlusion (Law III nuclear regime).
- **Verdict M1: MIXED.** The *hierarchy of pressure patterns with steeper falloff for more structure*
  is a candidate native idea; the **spherical-harmonic formalism and the multipole/"moment" names are
  a borrowed coordinate system laid over it.** It is not wrong arithmetic — it is a **borrowed map**.
- **Fix.** Re-derive the hierarchy in native terms: ℓ0 = isotropic occlusion (mass); ℓ1 = directional
  occlusion asymmetry (Coulomb, already native); ℓ2 = **helical-wake** of a closed circulation
  (replace "quadrupole moment" entirely); ℓ≥3 = mesh occlusion. If the `1,3,5,…` counts are to stay,
  they must be **derived from torus/helix geometry**, not inherited from `Y_ℓ^m`.

### M2 — "magnetic moment" `μ = I·A`

- **Math:** `μ = (e v_T / 2πR)·πR² = e v_T R / 2` — strength scales as circulation × loop size.
- **Borrow:** the formula **is** the classical Ampère current-loop law; "moment" and the magneton are EM/QM.
- **Translation test:** the native survivor is "**helical-wake strength ∝ v_T·R**" — a real
  circulation-kinematics statement. What does **not** survive is the *identification*
  "circulating charge = current = magnetic moment" (that's the EM bridge) and the magneton unit.
- **Verdict: LINGUISTIC-BORROW** on the scaling (keep it, rename to *wake strength*, express as a
  ratio to the electron's own wake — already done in `cq07_scroller.html`); **partial STRUCTURAL-BORROW**
  on `μ=I·A` itself (the step "circulation ⇒ a *moment*" is borrowed; the SDT step should be
  "circulation ⇒ a helical pressure wake of strength f(v_T,R)", and *that* function should be derived).

### M3 — `μ_ν ≡ 0`  *(the one to protect)*

- **Translation test:** strip ℓ=2/"moment". Native statement: *an open winding traces no closed
  helix → its wake cannot deflect EM → it has no magnetism.* That is **exactly James's mechanism** and
  it is fully native. The number (0) and the falsifiability (any deflection refutes the open winding)
  survive untouched.
- **Verdict: the RESULT is NATIVE/legitimate; only the *narration* (ℓ=2 wake = 0, "magnetic moment")
  is LINGUISTIC-BORROW.** **Do not rip it out.** Re-narrate as the helical-wake / EM-deflection chain.
  This is the canonical example of value-clean (D) × concept-contaminated-narration.

### M4 — nuclear moments μ_P, μ_N, μ_D, μ_T

- These are **measured constants** (`laws.hpp::measured`, in nuclear magnetons) — external-input (X) by
  value. The SDT *content* is the ATOMICUS claim **triton count `n_t` → uncancelled circulation →
  magnetism** (canon: `nuclear.hpp`, ATOMICUS), which is **native**. The "moment in magnetons" framing
  is the borrow.
- **Verdict:** values stay as external anchors; re-narrate the mechanism as **triton helical wakes**;
  the deuteron's silence = paired-circulation wake cancellation; the α's silence = closed/spin-0 shell.

### M5 — the PRIVATE magnetism docs

- **Native kernel (survives):** "magnetism isn't a force, it's a pattern in the spatial pressure
  gradient from moving/circulating displacements"; propagates at c; **no monopoles because the pattern
  must close** (pressure conservation). This is real SDT.
- **Structural-borrow shell (does not survive):** `B = −∇×(∇P/P₀)` (Maxwell curl), magnetic
  susceptibility χ, Bessel `J₀`, BCC/spinel crystal-field tensors, a literal **"quantum correlation
  function Q(r)"**, and the tell-tale AI sign-off *"Would you like me to…"*. These are imported to
  reproduce known formulas; none is derived from SDT primitives.
- **Verdict:** keep the kernel; the Maxwell/QM math layer is **STRUCTURAL-BORROW** (vibestyle) — quarantine
  it; rebuild from triton → helical wake → EM-deflection. These docs are *not* a clean ground truth.

---

## 3. Worked example — the Lamb shift  ("sampling the core" vs a real mechanism)

This is the case James named: a flippant phrase standing in for a mechanism.

- **Current state.** Benchmark **B04 Lamb** is value-class **E** — it carries a **fitted `k_Lamb`**
  (`FORMULATIONS_PROVENANCE_AUDIT` §E). Narration like "the electron *samples the core*" is a
  **STRUCTURAL-BORROW masquerading as NATIVE**: it sounds mechanical but no mechanism is computed; the
  number comes from the fit.
- **RETRACTED candidate (a self-caught contamination, 2026-06-07).** I first proposed "the s-orbital
  *penetrates* the superluminal interior" as a native mechanism. **It is not native — it is QED in
  disguise**, and James caught it. It smuggles in three prohibited QM constructs:
  1. **`|ψ(0)|²` penetration** — a wavefunction's "non-zero probability at the nucleus" promoted to the
     certainty that the electron is *inside* the core. SDT has **no probability cloud**: in CQ09 the
     electron is the **standing-wave node of the one field at a₀**, stationary in the co-rotating frame —
     it does not penetrate anything. "s vs p penetrate differently" is an artifact of a wavefunction SDT
     does not possess.
  2. **a quark-soup nucleus** for the electron to penetrate — the proton is a **(2,3) trefoil vortex**,
     not a bag of quarks.
  3. (the QED Lamb shift it would reproduce is built from **virtual photons / e⁺e⁻ loops** — prohibited.)
- **The actual SDT lead — structure-keyed, not probability-keyed.** QED's contact term `|ψ(0)|²` is
  **blind to nuclear structure** (one extra neutron barely moves it). The grammar is not:
  **Li-6 = 1α+1 deuteron (`n_t=0`, magnetically silent)** vs **Li-7 = 1α+1 triton (`n_t=1`, one uncancelled
  helical wake)** (`nuclear.hpp` `{3,6}→(1,0)`, `{3,7}→(0,1)`). SDT predicts these isotopes differ
  *qualitatively* via the **triton helical wake coupling outward through the one field to the valence
  circulation** — a structure-keyed effect QED's contact density must wave away as a small isotope shift.
- **Verdict: STRUCTURAL-BORROW (hand-waved fit `k_Lamb`); the QED s-penetration account is REJECTED
  (quarks, virtuals, `|ψ(0)|²` all prohibited); native mechanism is OPEN.** Do not fabricate one. The
  honest label is *"fitted via QED contact term; SDT mechanism (nuclear-grammar wake coupling) open;
  Li-6/Li-7 split is the discriminating test."*

> ⚠️ Meta-note: this entry is the audit catching **its own author** re-importing QM. That is the failure
> mode — a plausible "native" story that is QED relabelled. The guard is: if stripping the QM leaves a
> *mechanism gap you then fill with a QM-shaped guess*, you have not de-contaminated — you have repainted.

---

## 3b. Lamb shift, second pass — James's *"breaking a dyad first"* (2026-06-08)

James offered a replacement for the rejected s-penetration story: **"Lamb shift is the cost of breaking a
dyad first."** A refutation workflow (ground "dyad" in the corpus → 4 adversarial skeptics → synthesis)
returned **did NOT survive — 4/4 refute** — and, usefully, found the contamination is *already written down*.

- **The only worked-out version is contaminated.** `ATOMICUS/…/INVESTIGATION_Neutron_Identity.md` **Part VI
  "Dyad vs Plane"** states it as: *the 2s dyad couples isotropically to all wake multipoles ℓ=0,1,2…; the 2p
  plane couples anisotropically to ℓ=1 only; the missing higher-ℓ coupling IS the Lamb shift.* It fails 3 ways:
  1. **Borrowed ℓ-multipole language.** Stated entirely in the `Y_ℓ^m` coordinate system **M1** already
     flagged STRUCTURAL-BORROW. But **SDT has no native angular DOF**: the rotation field `v(r)=cα√(a₀/r)`
     depends on **r only** (CQ09). The mechanism cannot even be *stated* without importing the ℓ=0-vs-ℓ=1
     distinction it claims to explain — it **assumes its conclusion**.
  2. **A `|ψ(0)|²` repaint.** "ℓ=0 sees structure ℓ=1 cannot" is QED's origin-asymmetry (s nonzero at the
     origin, p vanishes) restated as a *long-range coupling integral* instead of *short-range penetration* —
     the same load-bearing claim, repainted (the exact move §3 forbids). The hard-point electron sits at the
     a₀ node in **both** 2s and 2p, so no native variable differs between them.
  3. **A category error.** Part VI maps 2s→"the Li/Be position (dyad)" and 2p→"the Boron position (plane)",
     silently swapping the **Sense-1 proton–electron dyad** (the only dyad in 1H) for the **Sense-2
     two-electron gear-pair** to borrow the paired-gear imagery. "Breaking a dyad" everywhere else in the
     grammar is a **~eV two-electron** event; the Lamb shift is **~4.4 µeV**. Wrong scale, members, process.
     It **predicts nothing**: B04 still carries the fitted `k_Lamb`; the sign 2S₁/₂>2P₁/₂ is supplied from
     standard physics.
- **Root blocker (the genuinely useful finding): no native angular degree of freedom.** SDT recovers
  radial/principal-`n` structure only. **Until an angular / orbital-shape DOF is *derived* from the
  torus/helix/occlusion geometry (not imported `Y_ℓ^m`), no s-vs-p splitting — hence no Lamb shift, no fine
  structure, not even its sign — is computable natively.** Logged as `ANGULAR-DOF` (INVESTIGATION_STACK L2).
- **What survives, separately.** The **Li-6 (`n_t=0`) vs Li-7 (`n_t=1`) triton-wake discriminator** (§3) is
  native — but it is **nuclear-structure-keyed**, applies to **lithium, not bare ¹H** (`n_t=0`), is still
  unworked quantitatively, and is a **different test**, not a rescue.
- **Verdict: REPAINT (again) + category error; not canon. Status parked, not killed** — pending James's own
  reading of *dyad* and *first* (a one-electron atom has only the proton–electron dyad, identical in 2S and
  2P, so the candidate needs a native variable that actually *differs* between the two).

---

## 4. The pattern across Pass 1

1. The **mechanisms** are mostly native or convergent (occlusion, circulation, helical wake,
   triton architecture, core penetration). **Almost nothing here warrants deletion.**
2. The **contamination is overwhelmingly a borrowed coordinate system / vocabulary** laid over native
   mechanics: spherical harmonics, "moments", magnetons, Maxwell `∇×`, susceptibility — adopted because
   they are the fastest bridge to the known number. That is the vibestyle signature.
3. The genuinely dangerous items are the **STRUCTURAL-BORROWs**: the `Y_ℓ^m` component counts (M1), the
   `μ=I·A` "moment" step (M2), the Maxwell/QM math layer in the PRIVATE docs (M5), and **hand-waved
   mechanisms hiding a fit** (Lamb, M-Lamb). These need real SDT derivation or honest quarantine.

---

## 4b. PASS 2 — CQ09 (Spation Rotation Kinematic Map): misnomenclature

**Top-line:** CQ09's spine is **native koppa** (`v(r)=cα√(a₀/r)`, the velocity profile, the
superluminal interior, the one-field thesis). The contamination is ~90% **borrowed labels** over real
mechanics (re-narrate, keep the numbers) + **one structural borrow** where the number itself is QED.

### A — LINGUISTIC-BORROW (misnomers; strip the word, native object remains)
| term (where) | native object | re-name |
|---|---|---|
| "charge radius" R_p (abstract, §I.1, §VI) | proton **surface** / displacement boundary; "charge" = ℓ=1 occlusion asymmetry | **proton surface radius** |
| symbol `r_e` / "classical electron radius" | the proton **c-boundary Ϟ_H = R_p/ϟ_H²** (prose already says c-boundary) | **Ϟ_H** |
| "Bohr radius/orbit", "Regime: BOHR" (§I.3, §III.4) | **ground-state node** of the field (v=αc) | **ground-state node radius** |
| "valence electron/shell" (title) | occupant of that node | **ground-state node** |
| "spin / antiparallel / singlet / triplet / spin-spin" (§IV) | **circulation sense (±)**; counter/co-rotating; circulation–circulation wake coupling | **circulation sense** |
| "covalent bond" (§IV.3) | rotation-field superposition well (CQ09: "not electron sharing") | **superposition well** |
| "frame dragging" (§IV.2) | lattice co-rotation at v(r) | **lattice co-rotation** |
| "event horizon" (§V.1) | c-boundary | **c-boundary** |
| "Compton / de Broglie / ƛ_C" (§I.3) | vortex coherence scale ℏ/(mc) | **coherence radius** |
| "QED-equivalent processes" (§VII) | strong-coupling subluminal regime | **strong-coupling regime** |
| "fine structure constant α" | here = ground-state koppa 1/ϟ_H=137 (α is permitted primitive) | **ground-state koppa** |

### B — CONVERGENCE (keep; native math lands on a QM result)
- **L_n = nℏ** (§III.4): `m·v·r` on the field at r_n=n²a₀ → `n·(m_e αc a₀)=nℏ`. CQ09 narrates it right
  ("emerges, not postulated"). Same for r_n=n²a₀ node ladder, v(a₀)=αc, k(a₀)=1/α.

### C — STRUCTURAL-BORROW (the number is borrowed; renaming won't fix)
- **21-cm / hyperfine (§IV.4) — biggest catch.** Native prose ("spin-spin … via the lattice") bolted onto
  the **imported QED formula** `ΔE_HF=(8/3)α⁴ m_e c²(m_e/m_p)μ_P`, which consumes **μ_P (proton magnetic
  moment — contaminated, measured)** and the **Fermi contact interaction**. The 0.054% match is QED's, not
  SDT's. Strip the QM → no derivation remains. **Fix: derive from circulation–circulation wake coupling.**
- **"spin ½ℏ"** (Open Q2): borrowed QM *target*; native `L_p=7.322ℏ`, `L_e=ℏ/√2` don't reach ½ — a real
  open divergence (honestly flagged).
- **bond energy 38.9 eV** (§IV.3): native mechanism, but classical `½m_e v²` → 8.6× over 4.52 eV; flagged
  for the occlusion integral.

### D — NATIVE / clean (protect)
`v(r)=cα√(a₀/r)`; koppa `k(r)`; velocity profile; **superluminal interior + saturation + load-sharing**
(phase-vs-transport / phonon = mechanical, not QM); winding/trefoil topology; displacement/exclusion volume;
"one field, two features"; **c-boundary = r_e by metrology exactness** (measurements were exact). The
superluminal interior (v>c) is also the **EM-deflection-capable zone** (wind/sound criterion: deflection
threshold = c) — load-bearing for magnetism + the Lamb-shift candidate, not contamination.

**CQ09 verdict:** pristine koppa skeleton + inherited QM/GR/chemistry *names* (re-narrate) + **one** borrowed
calculation (hyperfine). Best-case audit outcome — mostly labels to scrape, one number to re-derive.

---

## 5. Progressive plan (next passes — not yet done)

- **Pass 2 — the wake ℓ-expansion at the source.** Decide whether the `1,3,5,2ℓ+1` hierarchy can be
  re-derived from torus/helix geometry (native) or must be quarantined as a borrowed map. This is
  load-bearing: #28/#29 feed charge, magnetism, nuclear form factors, and μ_ν.
- **Pass 3 — atomic sector** (#70–#76): Rydberg, fine structure, Bohr, 21 cm, hyperfine — separate the
  native koppa/circulation content from borrowed QM term-by-term; revisit "α = 1/ϟ_H" narration.
- **Pass 4 — the QM-convergence catalogue** the corpus already gestures at (the deferred CQ "SDT↔QM
  parallels" investigation): for each QM result SDT reproduces, run the translation test and label
  CONVERGENCE vs BORROW. This is the constructive inverse of the audit — it documents where SDT
  *legitimately* lands on QM, so those are never mistaken for contamination.
- **Method to add to the spine:** carry `concept_status` alongside `value_status` in the §9 annotation
  block of `FORMULATIONS_PROVENANCE_AUDIT`, so every formula records both *"did the value enter"* and
  *"is the narration native."*
