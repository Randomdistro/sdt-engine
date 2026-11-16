# XSD-A — Technical Report (RUN 1, 2026-07-13)

**Node:** field shift as δΘ; extract h′(0), h″(0) of the sky-coverage law from the King plot.

**Run status: DEFERRED (data-blocked, honestly).** The point-source depth redshift of a nucleus at the electron is negligible (Ca@a₀: z_d≈9.4×10⁻⁴³) and, critically, **independent of nuclear size** in the point limit. The field shift is therefore *not* that point term — it is a **finite-size penetration effect**: an s-electron sampling the coverage *inside* the nuclear volume, where a larger ⟨r²⟩ changes the enclosed covered-sky. δν_FS/ν = h′(0)·δΘ_nuc with δΘ_nuc ∝ δ⟨r²⟩ (interior geometry).

**What is needed to run:** published isotope-shift constants F_i and δ⟨r²⟩ for Ca(40–48), Yb(168–176), Cd, Sr, Ba (the pre-registered King set), plus ⟨r⁴⟩ for the King-NL separation. Not in-repo; a literature pull.

**What can be stated now (no fabrication):**
- The **bridge test** is well-posed: h′(0) must be transition-independent; scatter > FS error ⟹ field shift ≠ δΘ ⟹ GD06 bridge KILLED.
- The King **nonlinearity** carries h″(0), to be separated from a genuine ⟨r⁴⟩ moment (≥3 transitions over-determine it).
- Pre-commit before the data pull: h″(0) sign (coverage stiffens ⟹ h″>0).

**Verdict:** Prompt completion **F (not executed)** · Physics class **PENDING** · reason: data pull required. This is the Hz-precision anchor of the cascade; until it runs, GD06's dilute-slope h′(0) is uncalibrated and the cross-scale extrapolation cannot be closed.

**Next action:** pull the isotope-shift tables (or hand XSD-A the numbers), build the King plots, extract h′(0)/h″(0).
