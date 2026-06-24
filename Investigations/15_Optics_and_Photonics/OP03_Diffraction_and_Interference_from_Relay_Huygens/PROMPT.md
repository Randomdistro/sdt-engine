# OP03 — Diffraction and Interference from Relay-Huygens Summation

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Diffraction and interference are usually read as evidence for a continuous wavefield or for
single-photon "self-interference." SDT has neither: light is a relay emission, and the lattice is
discrete at ℓ_P. **Can double-slit fringes, the grating equation `d sinθ = mλ`, the single-slit
`sinc²` pattern, and the Airy disk all be reproduced by relay-Huygens summation — each illuminated
interface spation re-emitting its received phase-impulse on the next tick, the screen pattern being
the relay-time-phased sum of those re-emissions — with no wavefunction and no photon-particle?**
This makes the double slit a counting statement about relay paths, the same wake-summation
machinery as [[QM01]].

## SDT mechanism & hypotheses

Each spation that receives the emission re-emits it one tick later (a secondary relay source); the
arrival phase at a screen point is set by the *relay-time* along the path (`∫ds/c_local`), so paths
of different length add with a phase difference. This is Huygens' principle **derived** as the
discrete relay rule, not assumed as a wave postulate.

- **H1 (Huygens = relay re-emission):** the field at a screen point is `Σ_j exp(i·2π·L_j/λ)` over
  illuminated spations `j`, with `L_j` the relay path length; constructive when path difference = mλ.
- **H2 (grating/two-slit):** two relay apertures give `d sinθ = mλ`; N apertures sharpen to grating
  resolving power `R = mN` — a pure counting/geometry result, zero fit.
- **H3 (single-slit + Airy):** a finite aperture of re-emitting spations integrates to `sinc²` (slit)
  and the Airy `[2J₁(x)/x]²` (circular); `λ` is the emission's relay wavelength `λ = N·ℓ_P` (CR07).
- **H4 (no self-interference paradox):** because the emission is a real relayed disturbance, "one
  photon" interference is just one emission sampling many relay paths — no collapse, ties [[QM01]].

## Strategy

**Phase 1 — Relay-Huygens kernel.** *Goal:* derive the secondary-source sum from the tick rule.
*Method:* discrete spation re-emission with relay-time phase. *Success:* recovers the Huygens–Fresnel
integral in the continuum limit; obliquity factor emerges, not inserted.

**Phase 2 — Two-slit & grating.** *Goal:* `d sinθ=mλ`. *Method:* sum two/N apertures. *Success:*
fringe spacing and grating angles exact; `R=mN` recovered.

**Phase 3 — Single-slit & Airy.** *Goal:* `sinc²` and Airy disk. *Method:* integrate a finite
aperture. *Success:* first-null positions (`sinθ=λ/a`; `1.22λ/D`) to <0.1%.

**Phase 4 — Granularity correction (stretch).** *Goal:* an ℓ_P-scale deviation. *Method:* keep the
discrete sum un-continuum-limited. *Success:* predicted (tiny) departure from `sinc²` at extreme
angles — a falsifiable SDT≠wave-optics signature, flagged with its size.

## Success criteria

- **PASS (A):** two-slit, grating, single-slit, Airy all from one relay-Huygens sum, zero fits.
- **QUALIFIED (C):** the above with the continuum (wave-optics) limit borrowed for the envelope (expected).
- **PENDING (D):** two-slit/grating recovered, single-slit/Airy only schematic.
- **FAIL (F):** relay summation cannot produce fringes without importing a wavefield.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 grating `d sinθ=mλ` | orders at exact angles; R=mN | relay sum ≠ Huygens |
| T2 single-slit nulls | `sinθ=λ/a`; Airy 1.22λ/D | finite aperture not integrable as relay sources |
| T3 single-emission fringes | pattern builds from independent emissions, no collapse | "self-interference" needs a wavefunction |

## Dependencies

**Upstream:** OP01 (relay speed, λ=N·ℓ_P). **Downstream:** OP06 (coherence/laser linewidth uses the
phased sum), holography, interferometry. **Related:** [[QM01]] (wake construction / double slit),
CR07 ([[project_cq46_redshift_octaves]], the ruler λ=N·ℓ_P), OP02 (reflected branches interfere).
