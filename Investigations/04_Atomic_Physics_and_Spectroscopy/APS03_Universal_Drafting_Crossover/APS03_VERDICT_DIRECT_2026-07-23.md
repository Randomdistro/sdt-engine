# APS03 — Direct re-run verdict: the 8.8% collapse RE-EARNED (2026-07-23)

> **Run class: DIRECT** (main session, no agents). Prior agent-era `INVESTIGATION.md`,
> `APS03_VERDICT.md`, `aps03_output.txt`, `results.txt` deleted 2026-07-23 (git-recoverable).
> Tool: `aps03_drafting_crossover.cpp`, g++ 15.2 -O2, exit **0**, run twice:
> (1) in-folder — SPARC path dead → galactic SHORT (`aps03_rerun_2026-07-23.txt`);
> (2) **scratch harness with the real full SPARC wired** (copies of GD05's `sparc_rotmod.csv`
> 3392 lines + `sparc_175.csv`, byte-counted by the tool's own §10 provenance protocol) —
> `aps03_rerun_full_sparc_2026-07-23.txt`.

## Prompt contraband check

**CLEAN — exemplary.** The prompt pre-registers thresholds, forbids the three failure modes that
had already occurred (circular validation, borrowed-function laundering, stale data), and hashes
inputs at read time. The MOND `Φ_simple` appears only as a **disclosed BORROWED baseline**.

## What the re-run measured (full-SPARC harness; the tool's own printed numbers)

- **PILOT STOP-CHECK: PASS** — 3012 SPARC points, RMS **23.7%** (ref 23.8%), BTFR slope
  **3.58** (ref 3.58). *The stale-file VOID that retracted this scale is resolved: the pilot now
  runs on verified, provenance-logged data.*
- Per-scale asymptotes: galactic floor slope **−0.481** (window [−0.60,−0.40]: PASS); atomic
  source ⟨B⟩ = 1.021 PASS; stellar source ⟨B⟩ = 1.042 PASS (76 bodies to ξ~10¹²);
  **atomic floor slope +0.25 — FAIL** (wrong sign; the provisional shell-occupancy ξ_A is the
  wrong exposure variable — §7.3 deliverable, open); stellar floor **absent** (no ξ≤0.1 members).
- **Cross-scale collapse (C+A+B): RMS 8.8% over 20 bins** vs Φ_simple.
  **Negative control (wrong floor 100·a₀): 53.3% — 6× worse → the test has power.**
- Nuclear scale: 447.7% — **contaminates; excluded** (ξ_D = grammar ratio is not an exposure).
- Corpus written: `cq26_corpus.csv`, 3520 rows, per-row provenance.

## Verdict

- **Prompt completion: B** (pilot + asymptotes + collapse + control run under §10; corpus far
  short of the 1920-example mandate — stellar floor and NIST expansion unfilled).
- **Physics class: CONVERGENCE-strong / shape-BORROWED** — one scale-invariant response curve
  collapses galactic + atomic + stellar data at 8.8% with a derived floor (a₀ = cH₀/2π) and
  demonstrated statistical power; but the crossover **shape** is still the borrowed MOND-simple
  interpolation. SDT supplies the floor scale and the asymptotes (DERIVED); the shape derivation
  (§7.4 solid-angle route) remains **the prize, OPEN**.
- **Supersedes the 2026-07 retraction:** the "8.8% RETRACTED-STALE" ruling was correct about the
  stale pilot; with the pilot re-earned on real data the 8.8% stands as an honest number.
- **Next data step is already cached:** the Gaia wide-binary catalog (the missing deep-stellar
  floor, the single most valuable absent measurement per the prior run) is now at
  `C:\sdt-data\eb_wide_binaries.fits.gz` (sha256-verified, see `Datasets/MANIFEST.md`).
- **Recovery: RECOVERED (galactic pilot + collapse)** · **Cascade root:** ξ_atomic definition
  (§7.3) — the one live wrong-sign result.
