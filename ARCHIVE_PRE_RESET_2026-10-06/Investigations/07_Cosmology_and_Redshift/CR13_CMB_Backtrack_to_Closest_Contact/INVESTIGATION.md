# CR13 — The CMB Backtrack to the Closest Point of Contact

> **Author:** J. C. Harvey, Melbourne. **Status:** EXECUTED (2026-06-29).
> **Tool:** `cr13_backtrack.py` → `cr13_results.txt`. **Frame-neutral** (uses only the observed
> redshift and `λ_received = λ_emit·(1+z)`; assumes **no** expansion — valid in both the ΛCDM and the
> SDT pressure-gradient readings).

---

## 0. The question (Harvey, 2026-06-28)

> *"Why did transparency stop right at the bottom of the visible spectrum? … has anyone performed the
> backtrack calculation? We have a speed, a rate, a size and a distance. We even have a gradient. What
> was the wavelength of the radiation bath at closest point of contact?"*

Two things are asked: **(a)** what wavelength was the radiation bath when it became transparent, and
**(b)** in the gradient reading — where the bath is *"a trillion raindrops from a trillion different
places, you at the centre"* — what is the wavelength of the **nearest** contribution, and does such a
multi-distance bath survive the FIRAS blackbody constraint?

This is the first time the backtrack has been run in-repo. It is deliberately **frame-neutral**: the
only physics used is the observed redshift `z` and the identity `λ_rx = λ_em·(1+z)`, which holds
whether `z` is metric expansion (ΛCDM) or accumulated pressure/closure gradient (SDT, GOM05). Nothing
here assumes expansion.

## 1. Method & inputs

Measured inputs (tagged in the tool): `T₀ = 2.7255 K` (FIRAS monopole), `z_rec = 1089.8` (Planck last
scattering), `Δz_LS = 80` (surface thickness), Wien `b = 2.8978×10⁻³ m·K`, `η = 6.1×10⁻¹⁰`
(baryon/photon), FIRAS `|y| < 1.5×10⁻⁵`, `R_drag ≈ 0.6` (baryon loading). Everything else is derived.

## 2. Results

### 2.1 The bath at transparency vs today — and "the bottom of the visible"

```
T_rec        = 2973.0 K          kT_rec = 0.2562 eV
λ_emit       = 974.7 nm          ← the bath's peak the moment transparency set in
λ_recv       = 1.0632 mm         ← that same bath, received today
mean photon  = 0.6920 eV
```

**The bath peaked at 974.7 nm — the red / near-IR edge, exactly "the bottom of the visible."** Why
there? Hydrogen binds at 13.6 eV, but `13.6 eV / kT_rec = 53`: recombination waits until the bath has
cooled ~50× *below* the binding energy, because there are `1/η ≈ 1.6×10⁹` photons per baryon
(`ln = 21`) and the high-energy tail keeps hydrogen ionised long after the mean photon has dropped
under 13.6 eV. **The visible-edge coincidence is 13.6 eV divided by the log of a billion.** It is not
a coincidence at all — it is forced by the binding energy and the photon-to-baryon ratio.

### 2.2 The closest-contact wavelength and the FIRAS gate (the real result)

In the gradient / "trillion raindrops" reading, contributions arrive from a range of depths, so the
received wavelength spans:

```
nearest contact  (z → 0)      λ → 974.7 nm    (≈ emission, near-IR)
farthest         (z = 1090)   λ → 1.063 mm    (microwave)
broad-gradient spread         975 nm → 1063 µm     (× 1091)
```

So the naïve answer to *"wavelength at closest contact"* is **≈ 975 nm** — but that answer is a trap,
and the trap is the point. A bath assembled from a broad range of depths is a **superposition of
blackbodies** spanning `T₀` up to `T_rec`. A temperature spread of fractional RMS `s` makes a
Compton-`y` distortion `y ≈ ½s²`. FIRAS caps it:

```
FIRAS |y| < 1.5×10⁻⁵   ⟹   s < √(2y) = 0.548%
a broad-z bath (s ~ O(1)) is therefore excluded by ~183×.
```

**The contributions must share a temperature to better than 0.55%.** A literal "trillion raindrops
from a trillion different distances" bath, with a genuine near-IR closest contact, is ruled out by two
orders of magnitude — *unless the synchrony/coherence mechanism collapses the smear to a single
effective temperature.* This is exactly the [[CR07]] property (redshift as octaves that telescope and
do not compound) doing load-bearing work: it is what lets the gradient survive FIRAS.

(Subtlety, stated in the tool: the standard *thin* last-scattering surface has a redshift thickness
`Δz/(1+z) = 7.3%`, but that is **not** a temperature spread — every point on it is redshifted to the
*same* `T₀` today, so it makes no distortion. Only a spread in the *received* temperature distorts the
blackbody. That is why standard cosmology keeps a clean blackbody: its source is effectively one `z`.)

### 2.3 Baryon-loaded sound speed (ties FD05 / the opacity-logjam thread)

```
c/√3            = 1.7309×10⁸ m/s   (pure-radiation ceiling)
c/√(3(1+R))     = 1.3684×10⁸ m/s   (R = 0.6, baryon obstacles at the drag epoch)   → 0.456 c
```

The baryons-as-obstacles term of the opacity logjam ([[project_opacity_logjam_cmb_gradient]]) is the
same `R` that drags the coupled sound speed below `c/√3` — the number that sets the BAO ruler.

## 3. What is solid, what is owed

**Solid:**
- The anchors (975 nm at emission, 1.063 mm today) and the "bottom-of-visible" explanation are
  frame-neutral and exact.
- The FIRAS bound is a real, sharp constraint: **the CMB source must be coherent in temperature to
  < 0.55%.** This is the quantitative gate every gradient/tired-light/multi-distance model must clear,
  and it is the strongest single argument that the "trillion raindrops" must be *synchronised*.

**Owed (named, not hidden):**
- A **single SDT-specific "closest contact" distance/wavelength** needs Harvey's *quantitative*
  gradient law — the propagation-redshift-per-distance in the no-expansion frame (the SDT "Hubble"
  analogue). This tool computed the frame-neutral part fully; the distance to the nearest contribution
  is the one input still to pin. Give the gradient `dz/dr` and this tool returns it in one line.
- The **coherence mechanism** that collapses the smear to < 0.55% is asserted (CR07 telescoping), not
  yet derived from the open-close synchrony picture. That derivation is the live frontier
  ([[project_opacity_logjam_cmb_gradient]]).

## 4. Verdict

**EXECUTED — the backtrack is done and frame-neutral.** The bath's wavelength at transparency was
**974.7 nm** (the red/near-IR edge, forced by 13.6 eV ÷ log(1/η)); the naïve nearest-contact
wavelength in a broad-gradient bath approaches that value, **but FIRAS forbids a broad spread by ~183×,
so the source must be coherent to < 0.55%.** The honest headline: *the closest-contact question is
really the coherence question* — the number that matters is not the near-IR wavelength but the 0.55%
temperature-coherence FIRAS demands, which the CR07 non-compounding octave mechanism must supply.

Class **C (CONVERGENCE)** on the anchors (reproduces the standard recombination numbers with an SDT
narration); the discriminating SDT prediction (a distinct near-IR closest contact) is **OPEN**, gated
on the gradient law and the coherence derivation.

---

### Cross-references
- [[CR07]] — redshift as octaves that telescope/don't compound: the coherence that lets a gradient keep a blackbody.
- [[project_opacity_logjam_cmb_gradient]] — the Clearing as a depinning transition; baryons-as-obstacles → `R`; the FIRAS gate.
- [[project_hubble_tension_resolution]] / GOM05 — the pressure/closure gradient the "distance" reading rests on.
- **FD05** — `c/√3` and the baryon-loaded `c/√(3(1+R))` sound speed.
