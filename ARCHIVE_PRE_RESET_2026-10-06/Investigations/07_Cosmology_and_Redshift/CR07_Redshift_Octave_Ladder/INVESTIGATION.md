# CR07 — Redshift, the Octave Ladder, and Why Light Does Not Compound

> **Author:** James Christopher Harvey, Melbourne. 2026-06-18.
> **Status:** theory investigation. Every number reproduces from `redshift_octaves.js`,
> `redshift_ruler.js`, `sizegrad.js` (one run each, Node).
> **Honesty contract:** the gravitational/endpoint results and the *redshift = octaves*
> identity are rigorous and labelled **[SOLID]**. The cosmological **source** of the
> large-scale spation gradient is the open part, labelled **[FRONTIER]** and routed to
> [[CR06]] (emission/propagation split) and the cyclic-cosmology programme. Nothing here
> claims the cosmology is closed; it claims the *non-compounding* is.

---

## 0. The thesis, in three sentences

1. **A photon is a fixed count of relay cycles** (its energy, gated at emission by the atom's
   α-rung); its *wavelength* is that count times the **local spation size**: λ = N·ℓ_P(r).
2. **Redshift is therefore a ruler comparison, not a process**: z = ℓ_P(observer)/ℓ_P(source) − 1.
   Expressed in base-2 this is literally an **octave count**: 1 + z = 2^Δn, Δn = log₂(1+z).
3. **It cannot compound** because a static, conservative spation gradient's line-integral
   **telescopes to its two endpoints** — every well the light enters it also leaves, and the
   count is an exact invariant so nothing is lost and nothing blurs. Compounding requires a
   *time-varying* medium (ΛCDM's ongoing expansion); SDT's lattice is not expanding.

Everything below is these three sentences, pushed to the wall.

---

## 1. The redshift primitive (the mechanism, made exact) **[SOLID]**

From the spation ontology (compressible, **not** deformable: cells shrink hard against matter
by their displaced volume, keeping shape): the closure field is

$$ \ell_P(r) = \ell_{P,\infty}\,(1-z), \qquad z \equiv \frac{\varkappa}{r} = 1 - \frac{c_{\text{local}}}{c_\infty}. $$

A photon emitted by an atomic transition carries a **count** N — the number of relay cycles in
one wavelength — fixed by the transition energy, which is set by the dimensionless α-ladder and
is therefore **independent of local spation size**. The relay conserves N exactly (each tick
advances the pattern one spation; the pattern is topological). So at every point the *physical*
wavelength is

$$ \lambda(r) = N\,\ell_P(r) = N\,\ell_{P,\infty}(1-z(r)). $$

The observed shift is the ratio of the rulers at the two ends:

$$ \boxed{\;1+z_{\text{obs}} = \frac{\lambda_{\text{obs}}}{\lambda_{\text{emit}}}
= \frac{\ell_P(\text{observer})}{\ell_P(\text{source})} = \frac{1-z(r_{\text{obs}})}{1-z(r_{\text{emit}})}\;}$$

The atom is the same; the **spations are not**. Light born on the Sun's surface is born into
spations smaller than ours by exactly z = ϟ☉/R☉, so when we read it on our larger spations it
reads long — redshifted — by that same fraction. **The redshift number IS the source's
spation-shrinkage.** (`redshift_ruler.js`.)

| source | spations smaller than ours by | z_spectral |
|---|---|---|
| Earth surface | 0.0007 ppm | 6.96×10⁻¹⁰ |
| Sun surface | **2.12 ppm** | **2.12×10⁻⁶** (= measured solar redshift, keystone C1, 0.03 %) |
| white dwarf (Sirius B) | 264 ppm | 2.6×10⁻⁴ |
| neutron star | 17 % | 0.21 |
| black-hole horizon (z=½, r=2ϟ) | 50 % | 1.0 |

This is *not* "energy lost climbing a well." Nothing pulls; nothing is lost. The count is
conserved; the meter-stick grew under it. This is the mechanism behind every gravitational
redshift the engine computes (B28, keystone C1).

---

## 2. Redshift **is** octaves **[SOLID]**

Write the ruler ratio in base 2. An octave is a factor of two in wavelength — equivalently a
factor of two in the photon's spation-count, or a halving of the spation ruler. Then

$$ \boxed{\;1+z = 2^{\,\Delta n}, \qquad \Delta n = \log_2(1+z)\ \text{octaves}\;} $$

Redshift and the octave ladder are the **same ladder**. Redshift slides a spectrum down it
toward longer wavelength; Δn is how many rungs. (`redshift_octaves.js`.)

| redshift | Δn = log₂(1+z) |
|---|---|
| Sun gravitational (2.12×10⁻⁶) | 3.06×10⁻⁶ octaves |
| galaxy z = 0.1 | 0.1375 octaves |
| **z = 1** | **1 octave (exactly)** |
| z = 3 | 2 octaves |
| z = 7 (earliest JWST galaxies) | 3 octaves |
| **CMB, z = 1100** | **10.10 octaves** |

z = 1 is *exactly one octave*. z = 3 is two. The cosmological redshift is **quantised in
octaves of (1+z)**: each octave down is another doubling of how much bigger our spations are
than the source's. Gravitational redshifts are micro-octaves (10⁻⁶); cosmological redshifts are
whole octaves. Same ruler, two regimes.

---

## 3. The CMB as a 10-octave slide (the centerpiece) **[SOLID]**

This is the cleanest possible confirmation that redshift = octaves, because it can be checked two
independent ways and they must agree. (`redshift_octaves.js`.)

- **By temperature** (Wien): at recombination the blackbody peak was at T = 3000 K → λ = 966 nm
  (near-IR), octave 43.65. Today the CMB peak is at T = 2.7255 K → λ = 1.06 mm (microwave),
  octave 33.55. The peak **slid 10.10 octaves down the ladder.**
- **By redshift**: log₂(1 + z_rec) = log₂(3000/2.7255) = log₂(1101) = **10.10 octaves.**

They are the same number to the second decimal — not by fitting, by identity. The microwave
background is the recombination spectrum **slid exactly ten rungs down the octave ladder**, and
"ten rungs" is what z = 1100 *means*. The temperature ratio, the redshift, and the octave-slide
are one quantity.

---

## 3b. The foreground ladder — the background was once a foreground **[SOLID phenomenon; SDT reframe]**

The microwave *background* was once the infrared *foreground* — the universe's own blackbody glow,
all around, near-IR (966 nm) at recombination. Walk it **backward** (earlier = hotter, T ∝ 1+z)
and the foreground climbs the octave ladder. (`foreground_ladder.js`.)

| epoch (T) | λ_peak | band | octave | redshift-to-now (octaves) | transparent? |
|---|---|---|---|---|---|
| now (2.7255 K) | 1.06 mm | microwave | 33.6 | 0 | **yes — what we see** |
| recomb / **the Clearing** (3000 K) | 966 nm | near-IR | 43.7 | 10.10 | ← becomes transparent here (last scattering) |
| red-star sky (3800 K) | 763 nm | red edge | 44.0 | 10.45 | no — opaque glowing fog |
| Sun-surface sky (5772 K) | 502 nm | **VISIBLE** | 44.6 | 11.05 | no — opaque |
| blue-white sky (7600 K) | 381 nm | violet edge | 45.0 | 11.45 | no — opaque |
| UV sky (15000 K) | 193 nm | ultraviolet | 46.0 | 12.43 | no — opaque |
| X-ray sky (3×10⁶ K) | 966 pm | X-ray | 53.6 | 20.1 | no — opaque |
| gamma sky (3×10⁹ K) | 0.97 pm | gamma | 63.6 | 30.0 | no — opaque, near the prior detonation |

**What was just before the infrared foreground? — the clearing is GRADUAL, not a floor.**
(Author correction: *"when something clarifies it does so gradually — first point to point, then a
little further."*) Opacity in SDT is **finite relay range**, not a wall. A **"stuffed" (loaded,
compressed) spation that releases is reflected back** — it cannot relay far through a dense
neighbourhood, so the mean free path is short. As the lattice cools and **un-stuffs**, each relay
reaches further: point-to-point, then a little further, then to the horizon. Even a **superheated
plasma has space between the electrons and the protons**, so short-range relay *always* happens —
there is never zero light, only light whose range is short. So there is **no "first light" instant
and no hard floor**: the near-IR/recombination rung is simply where the relay range grew to
**cosmic (free-streaming) scale** and the light reaches *us*; shorter-range light existed before
and clarified continuously. (This is the SDT mechanism for what standard cosmology calls the
**finite-thickness surface of last scattering** — a gradual fall in opacity, here a gradual growth
in relay range.)

**So "solid still" on the high-energy side of near-UV was overstated — it is "shorter-range," not
"perfectly solid."** Hotter and denser = more stuffed = more reflection = shorter relay range, so
the upper rungs become *progressively* harder to see through, not abruptly opaque. (Standard
parallel: a free-electron plasma scatters at all energies by Thomson, so the mean free path is
short through UV and X-ray; the bound-matter X-ray *transparency window*, photoelectric ∝ E⁻³·⁵,
does not apply to free electrons.) Read the upper rungs as the lattice's **temperature history at
ever-shorter relay range**, clarifying smoothly down to the recombination rung where the range
finally reaches us. The visible-temperature epoch (T ≈ 3800–7600 K, the stellar-colour sweep) was
*real as temperature* but short-range — a glow you could see a little way into, not a vista and not
a wall.

**Honest note.** The thermal history (T ∝ 1+z; opacity falling smoothly through a finite-thickness
last-scattering layer) is **shared** with standard cosmology — this section reframes it, it does
not replace it. The SDT content is the *mechanism*: redshift = octaves of spation-ruler growth (not
metric stretch); opacity = **finite relay range** from reflection of stuffed spations (not Thomson
per se); the clearing = a **gradual** growth of relay range as the cyclic lattice un-stuffs — not a
recombination of bound atoms, and **not a hard floor**. *Two earlier draft errors, both fixed:*
the upper rungs are not free-streaming "opaque foregrounds," **and** the clearing is not a one-way
floor — it is a continuous clarification. Why the early lattice was hotter/denser without expansion
is the same **[FRONTIER]** as §7 (cyclic cosmology, [[CR06]]).

---

## 4. The octave ladder, phenomenon by phenomenon **[SOLID structure; anchor convention noted]**

Anchor the ladder on **Earth's optical diameter** — thermosphere to thermosphere, ≈ 13,370 km,
the rock plus one atmosphere on each side, the diameter that lands the visible band cleanly on
the grid (see [[CR06]] companion note and the walkthrough). Count halvings down. Each octave
**halves the photon's wavelength**, which **halves its spation-count** N = λ/ℓ_P. The ladder is
a count ladder; the Wien temperature column is what blackbody peaks at that rung.
(`redshift_octaves.js`.)

| octave | wavelength | Wien T | photon count N | what physically lives there, and **why** |
|---|---|---|---|---|
| 0 (anchor) | 13,370 km | — | 8.3×10⁴¹ | Earth's optical span; ELF (~23 Hz) — the planetary resonance (Schumann) |
| 10 | 26 km | — | 1.6×10³⁹ | radio: macroscopic conductor/plasma resonances |
| 20 | 25.5 m | — | 1.6×10³⁶ | radio (VHF): antenna-scale oscillation |
| 28 | 100 mm | 29 mK | 6.2×10³³ | microwave: molecular **rotation** |
| 34 | 1.56 mm | 2 K | 9.6×10³¹ | **the CMB peak rung** — convergence-influx blackbody |
| 40 | 24 µm | 119 K | 1.5×10³⁰ | infrared: molecular **vibration** |
| 43–44 | 1.5–3 µm | 1–2 kK | ~10²⁹ | near-IR: low atomic transitions, hot dust |
| **44** | **760–380 nm** | **4–8 kK** | **~3×10²⁸** | **VISIBLE — atomic outer-shell transitions (the α-ladder); stellar surface Wien peak** |
| 45–47 | 380–90 nm | 8–32 kK | ~10²⁷ | ultraviolet: atomic ionisation, hot stars |
| 50 | 24 nm | 122 kK | 1.5×10²⁷ | extreme-UV / soft X-ray |
| 60 | 23 pm | 125 MK | 1.4×10²⁴ | X-ray: **inner-shell** transitions (deep k-rungs) |
| 70 | 0.02 pm | 10⁵ MK | 1.4×10²¹ | gamma: **nuclear** transitions |

**Why visible is octave 44 — honest version.** Two things are true. (i) The *physics* that puts
light in the visible band is **not** the anchor: it is that atomic outer-shell transition
energies (set by α, the hydrogen k-rung k = 1/α = 137) and stellar surface temperatures
(4000–8000 K, set by the convergence-processing balance, Law II) **both** land in the
380–760 nm octave — which is *why eyes evolved there and why stars look the colour they do*.
(ii) The *integer* "44" is the anchor talking: it is the number of halvings from Earth's optical
diameter to that band, and it is **anchor-dependent** — shift the anchor by a factor of two and
it becomes 43 or 45. What is *not* anchor-dependent, and is the genuinely arresting fact, is that
**Earth's optical diameter lands the visible octave on a clean rung at all** (shown to ~0.005
octave robustness across equatorial/mean/axial diameters in the prior session), and that the
deep regimes line up rung-by-rung: rotation → vibration → outer-shell → ionisation → inner-shell
→ nuclear, each roughly an octave-decade apart, because each samples the next tier of binding.
The ladder is real; the label "44" is a unit choice. Both are stated.

---

## 5. Why redshift does **not** compound — three independent reasons **[SOLID]**

The standard worry, stated precisely: all the light arriving from one direction was emitted at
different times and distances and has traversed overlapping columns of medium. If redshift were
a *process acting on the photon in flight*, it would (a) accumulate multiplicatively with path,
(b) double-count the near-Earth medium that every photon shares, and (c) random-walk the
wavelength so that distant spectral lines smear. **None of this happens.** Here is why, three
ways, each sufficient on its own.

### 5a. Endpoint-only: the telescoping theorem
Because λ(r) = N·ℓ_P(r), the wavelength at any point depends only on the local ruler. The shift
between source and observer is

$$ \ln\frac{\lambda_{\text{obs}}}{\lambda_{\text{emit}}}
= \int_{\text{src}}^{\text{obs}} \frac{d\ell_P}{\ell_P}
= \ln\ell_P(\text{obs}) - \ln\ell_P(\text{src}). $$

A line integral of a **conservative, static** gradient **telescopes to its endpoints**. Every
intermediate value cancels: the photon's wavelength *shrinks* entering a mass's compressed
spations and *grows back* leaving them, netting exactly zero. The numerical demo
(`redshift_octaves.js`, §4) sends a 500 nm photon from the Sun (z=2.1×10⁻⁶) past Jupiter, through
interstellar space, past another star, to our detector: the wavelength dips and recovers at each
body, and the **observed net shift is exactly (1−z_obs)/(1−z_emit)−1 = 2.12×10⁻⁶** — the
endpoints alone, the intervening structure contributing nothing. This is the *same* telescoping
that makes the gravitational redshift path-independent in static GR; SDT shares it by construction.

### 5b. Coherence: the count is an exact invariant (the tired-light killer)
A genuine in-flight *process* — scattering, "tired light," any stochastic energy loss — adds a
small random δλ at each of the ~10⁶⁰ relays over a gigaparsec. Random increments accumulate in
**quadrature**: line width would grow ∝ √(number of interactions), smearing every distant
spectrum into mush. This is the classical, fatal objection to tired-light cosmologies. SDT is
**immune**: the count N is topological, conserved exactly per relay, so the per-relay δ is **zero**,
and the added line width is **exactly zero regardless of path length**. Every photon of a given
count from a given depth gets the *identical* shift — sharp lines stay razor-sharp, merely
repositioned. The observed razor-sharpness of high-z quasar absorption lines is therefore direct
evidence for a **coherent ruler-rescaling** and against any *accumulating* redshift. SDT predicts
it; tired-light forbids it.

### 5c. No time-integral: there is no expansion stretching photons in flight
Compounding in ΛCDM is real and specific: 1+z = a(t_obs)/a(t_emit) = ∏(1+dz_i), a **time-integral
of the expansion that occurs while the photon is in flight**. It compounds because the medium is
*changing during transit*. SDT's lattice does **not** expand; the spation gradient it reads is
**static during transit**, and §5a then forces the result to be endpoint-only. The
distance–redshift relation (Hubble's law) is recovered not as a path-accumulation but as the
**endpoint difference** between the source's spation size and ours — which correlates with
distance because farther sources sit at more-different lattice states. More distance → bigger
endpoint gap → more redshift, monotonic, **without anything compounding.**

**The one place they must differ (the test).** Compounding returns the instant the gradient is
*not* static during flight. In GR that is the Integrated Sachs–Wolfe effect (CMB photons crossing
*evolving* potentials net a real residual). SDT's strict static-endpoint picture predicts a
**different ISW signature** (no residual from a potential a photon enters and leaves unchanged
in time). That divergence — ISW cross-correlation with large-scale structure — is the cleanest
falsifiable separation of "endpoint ruler" (SDT) from "time-compounded stretch" (ΛCDM).

---

## 6. SDT vs the Standard Model — the compounding ledger

| question | ΛCDM | SDT |
|---|---|---|
| What is redshift? | metric stretch of space during flight | ruler ratio ℓ_P(obs)/ℓ_P(src) |
| Does it compound along the path? | **yes** — 1+z = ∏(1+dz) time-integral | **no** — static conservative gradient telescopes to endpoints |
| Do intervening masses add up? | (peculiar/ISW terms) | net **zero** — in and out cancel |
| Do distant lines blur? | no (also coherent) | no — count is an exact invariant (kills tired-light) |
| Redshift in octaves | log₂(1+z), interpreted as scale-factor doublings | log₂(1+z), interpreted as **ruler doublings** |
| z = 1 means | universe was half its size | source spations were **half** ours |
| Test that separates them | — | **ISW residual**; QSO-line sharpness vs path; emitter-depth gradient (E102) |

---

## 7. Honest ledger

**[SOLID] — established here / by the engine:**
- λ = N·ℓ_P(r) with N a conserved count: redshift = ruler ratio; gravitational case = keystone
  C1 (solar 0.03 %, B28).
- **Redshift = octaves**, 1+z = 2^Δn, exact identity; CMB = 10.10-octave slide cross-checked by
  Wien and by z — they agree to 0.01 octave.
- **Non-compounding** by three independent arguments (telescoping, coherence, no-time-integral),
  each sufficient; the coherence argument additionally **falsifies tired-light** and **SDT
  survives** the razor-sharp-line test.
- The EM octave ladder's *structure* (count-halving rungs; rotation→vibration→shell→nuclear).

**[FRONTIER] — not closed, routed onward:**
- The **cosmological source** of the large-scale spation-size gradient (why our spations differ
  from a distant source's) — the emission/propagation split is [[CR06]]; the no-expansion
  account is the cyclic-cosmology programme; the **Pantheon+ one-parameter d(z) fit is not yet
  started** (the real quantitative test).
- The **integer anchor** "44" for visible is a unit choice; only the *clean landing* and the
  rung-spacing of regimes are claimed as physical.
- Whether the ISW divergence (§5c) actually distinguishes SDT from ΛCDM at current sensitivity
  is unmodelled — stated as the test, not as a result.

**The headline that survives the ledger:** redshift is a coherent, endpoint-only ruler-rescaling
— *octaves of spation size* — and it does not compound because there is no in-flight process and
no expansion to integrate. That is rigorous. *Why* the cosmic ruler varies with distance without
expansion is the open frontier, and it is named, not hidden.

---

*Companion scripts: `redshift_octaves.js` (octaves, CMB slide, ladder, non-compounding demo,
no-blur), `redshift_ruler.js` (deficit ladder), `sizegrad.js` (size-gradient force magnitude).
Builds on [[GOM05]] (variable closure), [[CR06]] (emission/propagation), the Depth–Closure
Theorem, and the two-regime / occlusion-saturation thread.*
