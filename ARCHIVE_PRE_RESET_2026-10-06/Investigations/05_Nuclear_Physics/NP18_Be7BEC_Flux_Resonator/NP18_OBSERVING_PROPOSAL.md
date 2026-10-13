# NP18 — Observing Proposal: the Be-7 / BEC flux-resonator rate-scaling fork

> **Author:** per J. C. Harvey NP18 SPEC. **Status:** downstream proposal, gated on Phase-3 result.
> **Honest headline:** the *tabletop* whole-condensate N² version is **geometrically deferred**
> (λ_ν ≪ L). This proposal therefore ships as a **conditional design** plus the falsifier that is
> actually reachable now (the coherence-vs-G_F *slope*, and the stripped-Be-7 seat fork).

---

## 1. What NP18 established (and did not)

- **Established (NATIVE):** the grammar selection rule — Be-7 sits at the (3,−1) underflow, one EC
  vector (−3,+2) to on-lattice Li-7. Zero parameters. This selects candidate resonant-capture
  substrates with no fitting.
- **Established (DERIVED):** a G_F-free resonant inverse-EC cross-section ceiling and an
  N-vs-N² enhancement law with exact incoherent limits.
- **NOT established (DEFER, T3):** that the 0.862 MeV neutrino wavelength (λ_ν ≈ 1.4 pm) can span
  a tabletop BEC (L ≈ 2 µm). It cannot — ρ_coh ≈ 7×10⁻⁷. Whole-condensate N² is **out of reach**
  at achievable BEC parameters.
- **NOT established (PENDING):** the absolute per-capture magnetisation step B_step — it needs the
  2s shallow-seat flux-per-atom from NP19/NP20 (both still SPEC).

**Therefore the "tabletop N² resonator" is not proposable as a discovery experiment yet.** What IS
proposable is the *discriminator's* two reachable legs.

---

## 2. The reachable falsifier — coherence-slope vs G_F (does NOT need λ_ν ⊇ BEC)

Even without full-condensate span, the **local** coherence of the electron environment is a real,
measured rate knob (Ohtsuki Be@C60: Δλ_EC/λ ~ 10⁻³; GSI bound-state β: Re-187 41 Gyr neutral →
33 yr fully ionised, a ~10⁹ swing). The fork:

- **SDT prediction:** the Be-7 EC rate rises with the *gaplessness/coherence* of the electron
  target — steepening as the target approaches a condensed, single-wavefunction state — faster than
  any G_F-only curve permits.
- **Standard prediction (OBSERVED column):** the rate tracks G_F × (electron density at the
  nucleus) only; no extra slope from coherence per se.

**Measurement:** Be-7 EC rate vs a *controlled coherence parameter* of the host electron gas
(temperature through the BEC transition; condensate fraction), at fixed electron density at the
nucleus. Any rate slope beyond the density term that correlates with condensate fraction is the
wedge biting. A flat result KILLS the wedge (T1) — and that is a clean, publishable null.

- **Target N:** 10⁵–10⁷ ⁷Li atoms (tabletop BEC, Bradley-class).
- **Density n:** 10¹³–10¹⁵ cm⁻³.
- **ν_e flux:** the Be-7 supplies its *own* internal captures; no external ν beam needed for the
  *forward* EC-rate-vs-coherence leg. (The *inverse*-EC resonant-drive leg WOULD need a
  monochromatic 0.862 MeV ν_e source — explicitly OUT OF SCOPE per the SPEC.)
- **Integration time τ:** hours–days (Be-7 t_½ = 53.22 d sets the natural clock).
- **Read-out floor:** SQUID ~1 fT; require B_sig ≥ 10× floor (absolute PENDING NP19/NP20).

---

## 3. The stripped-Be-7 control (Phase 4) — manufacture vs reshuffle

Run the *same* target twice: (a) neutral Be-7 with a 2s-active product Li-7; (b) valence-stripped
Be-7 (only the deep K pair present). SDT (PPT10) predicts a *manufactured* electron from the
neutrino arrives as a **shallow-2s flux signature** identical to the neutral read-out; a mere
K-shell reshuffle gives a **deep, fast, low-flux** signature. The seat-depth proxy gives a
**11.75× linear / 1621× volume** separation — comfortably above the 3× fork threshold. This is the
"which electron did the work" discriminator; it does not need condensate span.

- **Control:** fully stripped Be-7 (established technique — GSI storage-ring class ionisation).
- **Observable:** the B_step *spectrum* (deep-K vs shallow-2s), not just the rate.
- **Owed:** absolute B_step and the flux-vs-seat-size exponent from NP19/NP20.

---

## 4. Feasibility bucket

| Leg | Bucket | Why |
|-----|--------|-----|
| Coherence-slope vs G_F (forward EC) | **TABLETOP** | Be-7-in-BEC; self-driven; SQUID read-out. Reachable. |
| Stripped-Be-7 seat fork | **BUILDING** | needs storage-ring-class ionisation + trap; larger rig. |
| Resonant inverse-EC N² resonator (whole-condensate) | **DEFER / reactor+** | needs λ_ν ⊇ BEC (fails, T3) *and* a monochromatic 0.862 MeV ν_e beam (out of scope). |

**Bottom line:** the *headline* whole-condensate N² resonator is **deferred** on geometry; the
*coherence-slope* falsifier and the *stripped-seat* control are the tabletop/building-scale
experiments NP18 actually licenses. Both can KILL or feed the wedge with numbers, without importing
G_F into the SDT chain.

---

*NP18 · observing proposal · conditional on NP19/NP20 for the absolute read-out; T3 span deferred to CEνNS scale.*
