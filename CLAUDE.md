# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this repo is

`sdt-engine` is the canonical implementation of **Spatial Displacement Theory (SDT)** — a zero-free-parameter physics framework by James Tyndall. It is half research codebase (C++20 benchmarks + investigations) and half formal framework (Markdown theory, proofs, rules, and experiment proposals). Code and prose are tightly coupled: derivations live in `.md` files; numerical verifications live in `.cpp` files that consume the single-source-of-truth header.

## Build & run

Header-only engine + one benchmarks executable. Windows is the primary dev environment (MSVC) but GCC/Clang also work.

```bash
# Full build (from repo root)
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
./build/Benchmarks/Release/sdt-benchmarks.exe   # runs B01-B25

# Single-tool standalone compile (common pattern for Investigations/ and ATOMICUS/tools/)
cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:tool.exe path/to/tool.cpp
# or: g++ -std=c++20 -IEngine/include path/to/tool.cpp -o tool
```

There is no test runner. Benchmarks self-report PASS/FAIL by comparing SDT-derived values to measured constants within a tolerance (`report()` in `Benchmarks/B01_B25/benchmarks_suite.cpp`). Investigations are standalone `.cpp` files that each print their own assessment; run them individually.

## Architectural spine

**`Engine/include/sdt/laws.hpp` is THE single source of truth.** Every numerical constant, every force law, every derivation ultimately flows through this file. Downstream headers (`cosmology.hpp`, `magnetosphere.hpp`, `neutrino.hpp`, `state28d.hpp`) and all benchmark/investigation `.cpp` files `#include <sdt/laws.hpp>` and must not redefine constants it already exposes. Everything lives in `namespace sdt::laws` with sub-namespaces mirroring the Six Laws:

- `sdt::laws::measured` — the ONLY external inputs (CODATA 2018, IAU, FIRAS). A fact not in here is not a measured fact. Do not add fitted values.
- `sdt::laws::law_I` — cosmological relay throughput (Φ = Nε, P_conv)
- `sdt::laws::law_II` — release cascade, pressure domains
- `sdt::laws::law_III` — occlusion force: `F = (π/4) P_eff R₁² R₂² / r²` — the universal force law (Coulomb, gravity, nuclear all share this)
- `sdt::laws::law_IV` — inertial mass as throughput reorganisation cost
- `sdt::laws::law_V` — movement budget (`v_circ² + v² = c²`), special relativity
- `sdt::laws::law_VI` — vortex topology quantisation (T18, W+1 conjecture, winding)
- `sdt::laws::bridge` — k-hierarchy, koppa (ϟ = R/k²), orbital mechanics without G
- `sdt::laws::atomic`, `nuclear`, `coulomb_identity` — domain functions

When adding a new derivation: put the formula in the appropriate namespace of `laws.hpp`, cite the theorem number (T1–T18) in a comment, and reference it from benchmarks rather than duplicating the math.

## Gateways (binding on every session)

`GATEWAY_BEHAVIOURAL.md` (register, terminology, conduct) and `GATEWAY_PROCEDURAL.md`
(execution procedure) bind all LLM work in this repository. Core points: professional physics
vocabulary — **excluded / ruled out / falsified / withdrawn**, never "KILLED";
**pre-registered**, never "pre-commit"; **shared-input (not independent)**, never the evidence
label "DEGENERATE"; the word **"honest" is banned as a modifier** (state the fact; use Scope /
Limitations / Residuals). Direct execution only — delegated-agent output is not citable.
Pre-registration before instrumentation; instruments validated on known answers before use;
whole-range single-pass comparisons. `VOICE_MODEL_HARVEY.md` governs public copy.

## The hard constraints ("Prohibitions")

These are framework-level and apply to any code or prose you write in this repo. They come from `Theory/00_Ruleset.md` and `ATOMICUS/rules/On the Nature of Atomicus Rules.md`:

- **No G, no M as fundamentals.** Gravity is derived from `v_surface` and `R`: `g = v²/R`, `koppa = v²R/c²`. The legacy `GM_equivalent()` helper exists for conversions only.
- **No quantum wavefunctions, no fields as primitives, no dark matter/energy, no ΛCDM, no quarks/gluons, no wave-particle duality.** These are not "unsupported" — they are prohibited inputs. Derivations must not import them.
- **Scales.** `ℓ_P` is Axiom R1 (the one dimensional seed). `c`, `k_B`, `e` are unit bridges. `{ℏ, m_e, m_p}` are one mass/action seat (FLM13). `α` is hydrogen’s koppa rung `k_H = 1/α` (PPT02/APS05). `T_CMB` is a FIRAS clock. `sdt::laws::measured` is the engine's CODATA/FIRAS lookup. Record: `derivelist/README.md`.
- **Certification labels** (`DERIVED`, `COMPUTED`, `CALIBRATED`, `OBSERVED`, `PENDING`) tag every result in benchmarks. "CALIBRATED" means one parameter was fitted and MUST be documented.

## Nuclear construction grammar (ATOMICUS)

Every nucleus with Z ≥ 2 decomposes uniquely into **1 alpha core + n_d deuterons + n_t tritons**:

```
n_t = A - 2Z
n_d = 3Z - A - 2
```

Electron-capture isotopes use the **alternate grammar** (He-3 core instead of He-4): `n_t = A - 2Z + 1`, `n_d = 3Z - A - 3`. Free neutrons are forbidden in stable nuclei; a "free neutron" is an exposed triton remnant. Don't invent other decompositions — the grammar is constitutional.

`ATOMICUS/` holds per-isotope Markdown characterisations (`isotopes/NNN_XN.md`), per-element files (`elements/`), and generators/validators in `tools/`. Reports like `STRUCTURAL_ANALYSIS_REPORT.md` are regenerated outputs — edit the tool, not the report.

## Directory layout (what to read where)

- `Engine/include/sdt/` — header-only C++20 library. Start with `laws.hpp`.
- `Theory/` — formal framework, read in order `00_Ruleset.md` → `01_Closure_Derivations.md` → `02_Inputs_and_Derivations.md` → `03_Open_Problems.md` → `04_Notation.md` → `06_Input_Elimination.md` → `07_Cyclic_Reiteration.md` (Shapiro–Wien chain; heat death is Law III at `P→0`; recharge to `c_far → 0`). Input status: `derivelist/README.md`.
- `Laws/` — the Six Laws as standalone papers (`.md` + `.docx`).
- `ATOMICUS/` — atomic/nuclear database and construction grammar; `rules/On the Nature of Atomicus Rules.md` is the nuclear constitution.
- `Hubble/` — cosmological analysis suite with ~18 `zk²` tools in `tools/` and datasets in `data/`. Independent from the benchmarks CMake build; tools compile standalone.
- `Experiments/` — falsifiable prediction specs `E01.md` … `E102.md`. Each specifies SDT prediction, standard-model prediction, observable difference.
- `Investigations/` — active research folders; each contains `PROMPT.md` (methodology), optional `DATA_REQUIREMENTS.md`, and `.cpp` tools. `EMC01–PPT04` address open problems in the engine code itself.
- `Benchmarks/B01_B25/` — the single `benchmarks_suite.cpp` (B01 and up) that verifies the framework end-to-end. This is what the CMake build produces.
- `derivelist/` — how each scale sits: unit bridge, seat, rung, clock, or seed.
- `Papers/SPATIAL_DISPLACEMENT_THEORY.md` — the long-form manuscript. `Papers/SDT_LLM_UPTAKE.md` — spine, explanation then qualifier gates. `Papers/SDT_FOR_PEOPLE.md` — same model, no homework. `Papers/SDT_THEORETICAL_MODEL.md` — current total model. Web: `universe-lifecycle.html`, `sdt-for-people.html`, `theoretical-model.html`.

## Editing conventions

- The engine is header-only and `constexpr`-heavy. Prefer `inline constexpr` for new constants, `[[nodiscard]] inline auto` for derived functions. Existing style uses `std::numbers::pi` and raw C-style printf in tools.
- Experiments (`E##`) and Investigations (`CQ##` / `E##`) are numbered; when adding a new one, continue the sequence and update `Experiments/README.md` or `Investigations/README.md`.
- Reports under `ATOMICUS/reports/` and analysis outputs are generated. Regenerate them by running the corresponding tool rather than editing by hand.
- Author attribution throughout is James Christopher Tyndall, Melbourne. Keep it.
