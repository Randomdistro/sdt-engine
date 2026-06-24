# NP02B — Grammar Chain Growth (Investigation B)

**Companion to `CQ27_Stellar_Fusion_and_Nuclear_Growth`.** That investigation runs a 5-stage A→E pipeline (growth → occlusion → spin → EC gate → shell mirror). **NP02B takes the complementary angle**: it reads nucleosynthesis as a *walk on the `(n_d, n_t)` construction lattice* and studies the structures that emerge from the walk itself.

## Thesis

The Atomicus deuteron–triton grammar makes nucleosynthesis a 2-D integer lattice: He-4 at the origin, `+d` steps `n_d`, `+t` steps `n_t`. NP02B tests what falls out of that geometry — pathway multiplicity, the alpha-process reconciliation, an occlusion pathway-integral, triton-overload decay, EC timing by product, and the nucleus↔electron-shell inversion.

## Sections (single driver `cq27b_grammar_chain_growth.cpp`)

1. **The `n_t=0` spine** — the pure-deuteron / alpha-conjugate ladder. Every `+2` deuterons = one stellar alpha-capture; the captured He-4 dissolves into 2 deuterons around the single core. Reconciles "alpha process" with "one alpha core + deuterons."
2. **Dominant familial linkages** — Rule 4 (`parent + d/t → child`); each child differs from its parent by exactly one lattice step.
3. **Pathway multiplicity** — distinct construction orders to `(n_d,n_t)` = `C(Z−2, n_t)`; peaks on the golden diagonal `n_d=n_t` (maximal configurational entropy).
4. **Occlusion pathway-integral** — `B = k_occ·bonds`, `k_occ = 2.224 MeV/contact` (deuteron-pinned, **class E**). Bond accumulation along a chain; the *linkage points* are the interface bonds. Tracks measured binding to a roughly constant ratio (~0.4) — a single-scale proxy, **not** a parameter-free prediction.
5. **Trefoil rotation & overload** — `f_t = n_t/(n_d+n_t)`; overload past the iron-equilibrium fraction (~17%) drives alpha shedding (He-5 ejection).
6. **EC timing by product** — He-3 core grammar, `n_d ≥ 2` viability gate, core-change `−2`d`+1`t. PF spread (>9 orders) is Q-driven (`rate ∝ Q²`); the validated `Z³(In-111)/Z³(Be-7) = 1838 ≈ m_p/m_e`.
7. **Inversion test** — Rule 18 ("the proton is the code"). Falsifiable form `n_t(most-abundant) == unpaired electrons?` over Z=2..30.

## Result (see `run_log.txt`)

- Lattice, multiplicity, alpha-process reconciliation, overload thresholds, and EC `n_d≥2` gate all behave as constructed.
- **Inversion test: 14/29 = 48% match** — better than chance, **not a clean law**. Holds for single-odd-block remainders (Li, B, F, Na, Al, Cl, K: `n_t=1 ↔ 1` unpaired e) and the iron region (Mn, Fe, Ni); fails systematically for the `n_t=0` light nuclei (C, N, O, Si, S — unpaired electrons come from p-orbital Hund filling, a DoF the grammar does not carry) and neutron-rich isotopes (Ar-40, Sc–Cr). **Verdict:** the inversion is a real *conceptual* principle with only a *partial* quantitative map — `n_t` tracks neutron-excess asymmetry, unpaired-e tracks shell-fill asymmetry; mirrored, not identical.

## Build & run (standalone — does not touch the shared CMakeLists)

```
cl /std:c++20 /EHsc /O2 /I Engine/include Investigations/CQ27B_Grammar_Chain_Growth/cq27b_grammar_chain_growth.cpp /Fe:np02b.exe
g++ -std=c++20 -O2 -IEngine/include Investigations/CQ27B_Grammar_Chain_Growth/cq27b_grammar_chain_growth.cpp -o np02b
```

Consumes `<sdt/nuclear.hpp>` (the frozen NP01 grammar). See `CLASSIFICATION.md` for provenance labels.

*Author attribution: James Christopher Tyndall, Melbourne.*
