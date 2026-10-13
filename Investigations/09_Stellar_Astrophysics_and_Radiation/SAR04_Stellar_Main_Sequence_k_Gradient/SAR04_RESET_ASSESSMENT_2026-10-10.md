# SAR04 — Main sequence from the k-gradient: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0. **Read:** PROMPT.md. **Not opened:** SAR04_VERDICT.md, esults.txt, the old tool, RUN_LOG.md.

**Exposure:** E109 §11's statement that T, L and R inter-correlate at +0.80 to +0.95 in this table, and that v↔k is a construction, was read earlier in this session.

## Registration (fixed before the run)

**Premise defect.** The prompt computes k = c/√(2GM/R), which uses G and M (prohibited inputs) and the escape speed rather than the canon's circular speed (k = c/v_surface). The prompt also lists no gate numbers. Replaced by the mass-free route below.

**Data.** Experiments/E109_Solar_Spectral_Prism/data/dunes_koppa_table.txt: FGK stars from DUNES. v_surf = √(gR) from spectroscopic g and a radius from L and T_eff, so k = c/v_surf with no G and no M. All rows are used as given; none are excluded after the run.

**Gates.**
- **G1 (monotonic sequence):** |ρ_Spearman(k, L)| ≥ 0.9 and |ρ_Spearman(k, T_eff)| ≥ 0.9.
- **G2 (L–k relation):** a least-squares fit of log L against log k, with slope and scatter reported.
- **G3 (the Sun):** k = 686.3, L = 1 lies inside the 16–84% residual band of that fit.

**Span.** The prompt's "≥ 50 stars spanning O–M" cannot be met with an FGK table. That criterion is recorded as not met by the data.

**Label.** T, L and R co-vary along the main sequence (shared structure). A monotonic k-sequence would be consistent, and not discriminating.

## Run and results
(below)
- 123 stars parsed: F, G and K types, k from 353 to 3213. Output in `sar04_reset_1_results.txt`. Single pass.
- **G1, monotonic k-sequence: NOT MET.** ρ(k, L) = **+0.419** and ρ(k, T_eff) = **+0.339**. The relations are weak, and their **sign is opposite** to the prompt's picture (hotter, brighter stars at lower k). Within FGK, k = c/√(gR) does not order the main sequence.
- **G2:** log L = −1.488 + 0.492·log k, scatter 0.441 dex; 16–84% residual band [−0.436, +0.423].
- **G3:** the Sun (k = 686.3, L = 1) has a residual of +0.092 dex, inside the band.
- **Span (O–M):** not met; the table is FGK only.

**Grades:** G1 → **G1 (excluded within FGK)**. G2 computed. G3 consistent, but trivially so: the Sun sits mid-sample. O–M → PENDING_DATA (a mass-free k for O, B and M stars needs spectroscopic g and radii).

**Origin.** Surface speed √(gR) varies little across FGK dwarfs, about ×2 against L's ×100, and the sample mixes dwarfs with some evolved stars (larger R at lower g). The prompt's k illustrations were escape-speed guesses (O ≈ 300, M ≈ 1500); its mass-based formula is a prohibited route.

## Comparison with the archived record
Deferred.
