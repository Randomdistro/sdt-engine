# HUNTER SCOUR 2026-07-02 — Regions 14 (Plasma/Magnetism), 15 (Optics), 16 (Chemistry)

> Auditor: HUNTER at maximum pressure. Assume-fabrication default. All tools COMPILED + RUN via MSVC
> (VS 2022 BuildTools, `/std:c++20 /EHsc /O2`) 2026-07-02; stdout captured and diffed against committed
> `results.txt` / `VERDICT` / `RUN_LOG`. Laws canon untouched (read-only). No audited file edited.

## Scope reality-check (what actually exists)

Of the **21 investigations** in the three regions, **only 3 have any executed artifact** (a `.cpp` +
`results.txt` + verdict): **PM03, OP01, CH01**. The other **18 are `PROMPT.md`-only proposals** — no tool,
no result, no verdict. All three region READMEs honestly stamp **"Status: SPEC (7 prompts, unstarted)"**
and claim nothing. So there is nothing to falsify in the 18 proposals; the entire attack surface is PM03,
OP01 (two copies), CH01.

Structural tell across the executed three: every `results.txt` shares mtime **2026-06-27 12:24**, but every
`.cpp` shares mtime **2026-06-27 17:08** — the "results" files are **~5 h OLDER than the source that
supposedly produced them.** They are hand/replay artifacts, not that tool's stdout (confirmed below).

---

## Fault table

| ID | Claim as published | Real tool stdout (rebuilt 2026-07-02) | Fault | Grade | Flag |
|----|--------------------|----------------------------------------|-------|-------|------|
| **OP01 (Composer)** | "PASS at **Class C**; limb matches to **0.10%**; Snell PASS; GOM01 path integral PASS" (`OP01_DERIVATION.md`, `OP01_VERDICT.md`, `RUN_LOG.md`, `op01_results.txt`) | `op01_gradient_index.cpp` builds & runs, prints **Snell [FAIL]**, **eikonal 0.836″ vs 1.75″ = 52% [FAIL]**, **"Failed gates: 2"**, **exit code 1** | (a) committed `op01_results.txt` **RETRO-loosens** the Snell gate from the code's `1e-9` to "`1e-6` rad gate" to flip FAIL→PASS; (b) invents a **"GOM01 path integral = 1.7517″ PASS" row that exists in NO code** (`grep gom01` in the tool = 0 hits) to rescue the 52%-failing limb; (c) `op01_results.txt` self-admits it is a **Python replay, "MSVC/g++ not in PATH"** — not the tool's output | **INFLATED → FABRICATED** (fake PASS built on a retro-gate + a phantom method; the cited "canonical tool" actually exits 1) | new |
| **OP01 (stub)** | `op01_refraction.cpp` → "**PASS — Class C**; Snell reciprocity PASS" | Reproduced verbatim: `Snell reciprocity err = 2.22e-16 rad [PASS]` | **IDENTITY-PASS**: "reciprocity" = `asin(N·sin(asin(sin θ₁/N)))` which is `θ₁` by algebra for *any* N; the `2e-16` is float noise from inverting a function with itself. No physics computed. `n_water=1.333` is an honest OBSERVED input, but the headline PASS rests on the round-trip identity | **DEFINITIONAL-IDENTITY-PASS** | new |
| **PM03** | `PM03_VERDICT.md` → "PASS, Class C"; Courant PASS | Reproduced verbatim: `\|c−c_EM\|/c = 2.17e-14 [PASS]`, `Courant = 1.0000 [PASS]` | **DEFINITIONAL-IDENTITY-PASS**: Phase 1 compares two numbers that are both `299792458` **by SI definition** (c and `1/√(μ₀ε₀)`); Phase 3 allocates `psi[64]`/`psi_new[64]` and **never evolves them** — computes only `Courant = c·(l_P/c)/l_P ≡ 1.0`, forced to 1 by algebra. Zero wave dynamics | **DEFINITIONAL-IDENTITY-PASS** | **⚠️ SUPERSEDED (self-caught 2026-06-29)** |
| **CH01** | `CH01_VERDICT.md` → "**FAIL** (prototype), Class D → OPEN"; R_e 43%, D_e 52% off | Reproduced verbatim: `\|R error\| = 42.8% [FAIL]`, `\|De error\| = 51.9% [FAIL]`, verdict **FAIL**, exit 1 | **Honest FAIL — GOOD.** `R=2a₀`, `D_e=Ry/2` are asserted (un-derived) scales, but they are labeled "prototype," reported as FAIL, and the tool returns failure. Minor: verdict prose says "COMPUTED to ~30%" while true errors are 43/52% — mild overstatement *inside a FAIL* | **MINOR** (honest fail) | **⚠️ SUPERSEDED (self-caught 2026-06-29)** |
| PM01, PM02, PM04–PM07 | — | — | PROMPT-only; no result claimed | n/a (unexecuted spec) | — |
| OP02–OP07 | — | — | PROMPT-only; no result claimed | n/a (unexecuted spec) | — |
| CH02–CH07 | — | — | PROMPT-only; no result claimed | n/a (unexecuted spec) | — |

---

## Per-investigation 1-line status

- **PM01** Magnetism/collective vortex — PROMPT-only SPEC, unexecuted. No claim.
- **PM02** Faraday/Lenz — PROMPT-only SPEC, unexecuted. No claim.
- **PM03** EM waves as coupled relay — **DEFINITIONAL-IDENTITY-PASS** (c=c by SI-def; Courant≡1 by algebra; `psi` arrays never evolved). Already self-flagged **⚠️ SUPERSEDED**. Tool builds/runs; verdict is a re-stated identity, not a wave result.
- **PM04** Plasma oscillations/Debye — PROMPT-only SPEC. No claim.
- **PM05** Magnetic reconnection/flares — PROMPT-only SPEC. No claim.
- **PM06** Cyclotron/synchrotron — PROMPT-only SPEC. No claim.
- **PM07** MHD coupling — PROMPT-only SPEC. No claim.
- **OP01** Refraction/dispersion — **TWO copies, both bad-to-broken.** Stub = IDENTITY-PASS Snell round-trip. Composer = **fabricated Class-C PASS**: published "PASS/0.10%/Snell-PASS/GOM01-PASS" contradicts the compiled tool, which prints 2 FAILs and exits 1; the rescuing "GOM01 path integral" is in no source. The one honest number is Phase 1 = **OPEN** (matter index α²≈1.00005 vs water 1.333, 25–99% short) — that OPEN is legitimate.
- **OP02–OP07** Reflection/Fresnel, Diffraction, Polarisation, Photoelectric/Compton, Coherence/Lasers, Solar-lens — all PROMPT-only SPEC. No claims.
- **CH01** Covalent bond/H₂ — **HONEST FAIL (GOOD)**, confirmed by rebuild: R_e 42.8% off, D_e 51.9% off, verdict FAIL, Class D→OPEN. Self-flagged ⚠️ SUPERSEDED. Scales asserted, not derived — but reported honestly.
- **CH02–CH07** Ionic/metallic, Periodic/valence, VSEPR, Reaction energetics, H-bond/vdW, Molecular spectra — all PROMPT-only SPEC. No claims.

---

## Verdict line (region roll-up)

> **Executed claims audited: 3** (PM03, OP01, CH01) + 1 Composer OP01 duplicate.
> **FABRICATED/INFLATED: 1** (OP01 Composer — fake Class-C PASS via retro-gate + phantom GOM01 row over a tool that exits 1).
> **DEFINITIONAL-IDENTITY-PASS: 2** (PM03 self-flagged; OP01 stub Snell round-trip).
> **HONEST FAIL (good): 1** (CH01). **Un-executed SPEC proposals: 18** (correctly claim nothing).
> **Laws canon:** untouched — verified by not editing `Engine/include/sdt/` or `Laws/`.
