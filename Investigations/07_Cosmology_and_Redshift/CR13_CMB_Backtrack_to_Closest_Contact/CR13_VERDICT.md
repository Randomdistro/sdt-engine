# CR13 — Verdict

**Question:** What was the wavelength of the CMB radiation bath at the closest point of contact, and
does a multi-distance ("trillion raindrops") gradient bath survive FIRAS?

**Verdict:** **EXECUTED — Class C (CONVERGENCE) on the anchors; the discriminating SDT claim is OPEN.**

**Answer, in one line:** the bath peaked at **974.7 nm** (red / near-IR edge) the moment transparency
set in — the naïve "closest contact" wavelength approaches this — **but FIRAS forbids a broad-distance
bath by ~183×, so the closest-contact question is really the temperature-coherence question: the source
must be coherent to < 0.55%.**

**Key numbers (frame-neutral, `λ_rx = λ_em·(1+z)`):**
```
λ_emit = 974.7 nm      T_rec  = 2973 K       kT_rec = 0.256 eV
λ_recv = 1.0632 mm     13.6 eV / kT_rec = 53  (= 13.6 eV ÷ log(1/η), the "bottom of visible")
FIRAS gate: y<1.5e-5 ⟹ source temperature spread s < 0.548%  (broad-z bath excluded ×183)
c/√3 = 1.7309e8 m/s ;  c/√(3(1+R)), R=0.6 = 1.3684e8 m/s = 0.456 c   (BAO/opacity link)
```

**What this closes:**
- The "why the bottom of the visible spectrum" question — quantitatively: `13.6 eV ÷ log(1/η) → 0.26 eV
  → 2973 K → 975 nm`. Not a coincidence.
- The backtrack itself — run for the first time, frame-neutral, reproducible via `cr13_backtrack.py`.
- The strongest constraint on every gradient/tired-light/multi-distance CMB model: **temperature
  coherence to < 0.55%.**

**What this does NOT close (owed):**
- The **SDT-specific distance** to the nearest contribution needs Harvey's quantitative gradient law
  (`dz/dr` in the no-expansion frame); the tool returns it in one line once supplied.
- The **coherence mechanism** that collapses the smear to < 0.55% is asserted (CR07 non-compounding
  octaves), not yet derived from the open-close synchrony picture — the live frontier.

**Provenance:** all inputs MEASURED (FIRAS `T₀`, Planck `z_rec`, `η`, FIRAS `y`) or DERIVED (Wien);
zero fitted parameters; no expansion assumed.

**Artifacts:** `cr13_backtrack.py`, `cr13_results.txt`, `INVESTIGATION.md`.

*J. C. Harvey, Melbourne, 2026-06-29.*
