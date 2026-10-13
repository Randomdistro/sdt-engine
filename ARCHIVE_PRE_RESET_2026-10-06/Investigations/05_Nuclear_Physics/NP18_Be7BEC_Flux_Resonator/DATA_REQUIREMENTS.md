# NP18 — Data Requirements

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **For:** `NP18_Be7BEC_Flux_Resonator/PROMPT.md` — the Be7BEC flux-resonator rate-scaling fork.
> **Rule:** every row is an **anchor** — use the measured DATA, never the standard-model **story** attached. Each item is tagged with **which link of the device it is the published proof of**. Tag on load: `MEASURED-INPUT` / `OBSERVED-TARGET`.

---

## A. Coherence enhancement of neutrino cross-sections (proof of LINK 4)

| Data | Value / form | Source to fetch | Proves |
|------|--------------|-----------------|--------|
| CEνNS coherent cross-section | σ ∝ N² (enhancement over single-nucleon), measured | COHERENT collaboration, *Science* **357** (2017) 1123; Akimov et al. follow-ups | **Coherence enhances neutrino cross-sections ~N²** — but over nucleons *within one nucleus* (honest-boundary anchor, §⑧ T3) |
| CEνNS theoretical basis | coherent-sum derivation, σ ∝ N² | Freedman, *Phys. Rev. D* **9** (1974) 1389 | The N²-coherence law exists and is established for intra-nucleus coherence |
| Momentum-transfer / wavelength condition | q·R ≲ 1 for coherence | CEνNS reviews (e.g. Akimov 2021 review) | The **span condition** λ ⊇ target — the exact thing the BEC claim must extend (and where it goes beyond known ground) |

## B. Electron-environment rate gating (proof of LINK 3)

| Data | Value | Source to fetch | Proves |
|------|-------|-----------------|--------|
| Re-187 bound-state β half-life, neutral | ≈ 41 Gyr | Bosch et al., *Phys. Rev. Lett.* **77** (1996) 5190 (GSI) | The electron environment is a **huge** rate knob (bound-state β) |
| Re-187 bound-state β half-life, fully ionised | ≈ 33 yr | Bosch et al. 1996 (GSI storage ring) | Fully stripping the ion changes the decay rate by ~10⁹ — the gating lever at extreme range |
| Dy-163 — stable neutral / decays fully ionised | stable (neutral) → β⁻ active (bare) | Jung et al., *Phys. Rev. Lett.* **69** (1992) 2164 (GSI) | Ionisation can **switch a channel on/off** — the stripped-Be-7 silent-trap principle (§④ Phase 4) |
| Be-7 EC rate, environment dependence | ΔλEC/λ up to ~10⁻³ (chemical / pressure / host) | Ohtsuki et al., *Phys. Rev. Lett.* **93** (2004) 112501 (Be@C60); Wang et al. host-dependence studies | Be-7's own EC rate is **electron-environment-dependent** (gating is real for the target isotope itself) |

## C. Be-7 source line (proof of LINK 1 — clean single channel)

| Data | Value | Source to fetch | Proves |
|------|-------|-----------------|--------|
| Be-7 decay mode | 100 % electron capture → Li-7 | NNDC / ENSDF (A=7); Be-7 half-life 53.22 d | One channel, no β⁺ — the clean source |
| νₑ line, ground-state branch | **0.862 MeV (≈ 90 %)** | NNDC ENSDF; solar-ν Be-7 line literature (Borexino) | The resonant drive energy (ground-state Li-7) |
| νₑ line, excited-state branch | **0.384 MeV (≈ 10 %)** | NNDC ENSDF | The second line (capture to Li-7\*) |
| 478 keV photon | **Li-7\* → Li-7 de-excitation GAMMA** | NNDC ENSDF | **NOT a neutrino line** — load explicitly labelled as a gamma (anti-contamination, §④ Phase 0) |
| n–p mass gap (context anchor) | 1.293 MeV | CODATA / `sdt::laws::measured` | Cross-check on EC/β energetics; do **not** import the W-mediator story |

## D. Li-7 BEC parameters + read-out flux (proof of LINK 4 + LINK 5)

| Data | Value / form | Source to fetch | Proves |
|------|--------------|-----------------|--------|
| Li BEC realisation & parameters | N ~ 10⁴–10⁷ atoms; n ~ 10¹³–10¹⁵ cm⁻³; size L ~ µm–tens of µm | Bradley et al. (⁷Li BEC) *Phys. Rev. Lett.* **75** (1995) 1687; modern ⁷Li condensate reviews | The **gapless single-wavefunction target** exists and is tabletop (LINK 4); supplies N, n, L for ρ_coh |
| Li/Be 2s valence flux per atom | shallow-seat flux quantum (SDT-native) | **NP19 / NP20** (sibling investigations) — *internal dependency, not external* | The **self-manufacturing read-out** B_step (LINK 5); may be `CALIBRATED(1)` until NP19/NP20 land |

## E. Read-out floor (proof of LINK 5 — detectability)

| Data | Value | Source to fetch | Proves |
|------|-------|-----------------|--------|
| SQUID magnetometer floor | ~ 1 fT (10⁻¹⁵ T), ~ few fT·Hz⁻¹ᐟ² | Clarke & Braginski, *The SQUID Handbook* (Wiley); commercial SQUID datasheets | The detection floor B_floor that B_sig(N\*) must clear by ≥10× (§④ Phase 3) |

---

## Fetch checklist (for the runner)

- [ ] COHERENT 2017 + Freedman 1974 — the N²-coherence law **and** its intra-nucleus span condition (B-boundary anchor).
- [ ] GSI bound-state β: Re-187 (neutral 41 Gyr / ionised 33 yr), Dy-163 (stable/active) — the gating proof.
- [ ] Be-7 environment-dependent EC rate (Ohtsuki Be@C60 + host studies).
- [ ] Be-7 ENSDF: mode (100 % EC), lines 0.862/0.384 MeV, **478 keV = gamma**, half-life 53.22 d.
- [ ] ⁷Li BEC parameters (N, n, L) from Bradley 1995 + modern reviews.
- [ ] NP19/NP20 for the 2s flux-per-atom read-out (internal — flag if not yet landed).
- [ ] SQUID floor ~fT from the SQUID Handbook / datasheet.

**Provenance discipline:** all rival numbers (G_F, CEνNS σ, standard EC rates) enter the tool **only** as `OBSERVED-TARGET` comparison columns — never inside the SDT derivation chain (§0 anti-creep; `PROMPT_EXECUTION_PROTOCOL.md` §2 BORROW-SMUGGLE prohibition).

---

*NP18 · data requirements · each row is the published proof of one device link · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
