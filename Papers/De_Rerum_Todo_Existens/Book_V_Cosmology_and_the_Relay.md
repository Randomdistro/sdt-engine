# Book V — Cosmology & the Relay
### *De Rerum Todo Existens*, Book the Fifth: the sky is a source, redshift is a ruler

> **Author:** James Christopher Harvey, Melbourne. 2026.
> **Engine:** every number below is emitted by [`de_rerum.cpp`](de_rerum.cpp) (Book V section) and
> reproduced in [`de_rerum_results.txt`](de_rerum_results.txt). Class labels (A/B/C/F) are the
> engine's own certification, kept verbatim. See [README](README.md) for the class key.

---

## 0. Cosmology without expansion

Standard cosmology reads the night sky through one premise: that distance is *velocity*, that a
redshifted line means a receding source, and that to integrate those recessions backward is to find a
moment when everything was here at once. From that single premise grow the scale factor `a(t)`, the
Friedmann expansion, inflation to flatten it, dark matter to bind it, dark energy to accelerate it, and
a singular Big Bang to start it. SDT keeps none of these. They are not "unsupported" in this treatise;
they are **prohibited inputs** (see [README](README.md)). The work of this book is therefore to rebuild
the three things the standard story explains — the cosmic microwave background, the redshift–distance
relation, and the Hubble tension — using only the matrix, the relay, and the depth law already built in
Books I and IV.

The thesis is a single sentence, and the whole book is its unpacking: **redshift is not an expansion
velocity; it is a ruler comparison.** A photon's wavelength is a *count of spations*,
`λ = N · ℓ_P(r)`. When the local spation closure `ℓ_P(r)` differs between where a photon was emitted and
where it is read, the same count `N` measures a longer wavelength — and that, not motion, is the shift.
Nothing is expanding. The ruler is changing length along the path, and we are reading the difference.

## 1. The relay is the sky (Law I)

The cosmic microwave background is, in standard cosmology, the cooled relic of an explosion. In SDT it
is something present-tense: the **isotropic relay throughput** `Φ` of the matrix, the convergence
flooding in from every direction that Book I made the source of all pressure. The CMB is not an echo of
a beginning — it is the **present face of the relay**. The sky glows at `T_CMB` because that is the held
energy density of the throughput, here and now.

Because the relay is the convergence, its throughput *is* the cosmological reservoir, and from it the
engine reads the constants that the standard model fits:

| quantity | meaning | value | class |
|---|---|---|---|
| `H₀` | Hubble constant (from the pressure tensor) | 67.4 km/s/Mpc | C |
| `γ_eff` | freeze-out / polytropic factor | 4 | C |
| `P(z=1100)` | lattice pressure at recombination | 3.616008×10⁶⁰ Pa | C |

`H₀ = 67.4 km/s/Mpc` is read from the lattice pressure tensor `P(z) = P_conv·(1+z)⁴`
(`law_I::pressure_at_redshift`) carried through a Friedmann *structure*. It lands on the Planck value to
under one percent. **Honest caveat, kept in the open:** this row is class **C-flagged**, not B. The
Friedmann equation is *assumed as structure* — SDT borrows the bookkeeping shape and supplies the
pressure that fills it; an end-to-end SDT derivation of the expansion-rate structure is deferred (it is
the open work of GOM05). The number is right; the scaffolding is borrowed, and we say so.

`γ_eff = 4` is the polytropic exponent of the matrix — **not** the `4/3` of a photon gas. The lattice is
topologically stiff: each cell carries four degrees of freedom from its `W±1` winding modes (Book II,
Law VI). At recombination the linking-number density drops by an exact factor of four when free
electrons and protons (independent `W` defects) bind into neutral hydrogen; this is the **freeze-out**
that fixes the BAO scale. The pressure at recombination, `P(z=1100) = 3.616008×10⁶⁰ Pa`, is simply that
tensor evaluated at the recombination redshift. It is enormous because the relay reservoir `P_conv`
(Book I) is enormous; what we observe locally is always the heavily *screened* remainder.

## 2. Redshift is a ruler comparison — measured in octaves (CR07)

Here is the central mechanism stated plainly. A photon is a definite count `N` of spations along its
wavelength. The size of a spation is the local closure `ℓ_P(r)`, and Book IV (Depth-Closure) showed that
closure is not universal — it relaxes with convergence depth, `ℓ_P(r) = ℓ_P,∞·(1 − z)`. So a photon's
*physical* wavelength is

$$ \lambda(r) = N \cdot \ell_P(r), \qquad 1 + z = \frac{\ell_P(\text{observed})}{\ell_P(\text{source})}. $$

The count `N` is conserved; the ruler changes. Redshift is the ratio of two ruler-lengths, full stop.

This ratio has a natural logarithm base. Writing the slide as **octaves** down the spation ladder,

$$ 1 + z = 2^{\Delta n}, \qquad \Delta n = \log_2(1+z), $$

so `Δn` is *the number of octaves* the photon falls. Each octave **halves** the photon's spation count —
the same doubling structure that organises the spectral ladder in Book II (atomic transition lines sit
at definite rungs; the visible band is one octave). The engine reads the ladder directly:

- `z = 1 → 1.0000` octave **[C]** — one redshift unit is one octave, exactly.
- `z = 1100 (CMB) → 10.1046` octaves **[C]** — the CMB is a **~10-octave slide**.

Read that second line concretely. The recombination spectrum is emitted near **~966 nm** (near-infrared);
sliding ten-plus octaves down the ladder lands it at **~1.06 mm** (microwave) — which is exactly where we
find the CMB. The engine cross-checks the Wien-peak temperature against the octave count and the two agree
to **~0.01 octave**. The microwave background is not a fossil temperature; it is the recombination light
read ten octaves down a changing ruler.

## 3. Why redshift does not compound (and why tired-light is dead)

The obvious objection: if every spation along a billion-light-year path nudges the wavelength, surely
the effect accumulates and smears? It does not — for three independent reasons, and stating all three is
what separates this mechanism from the failed "tired-light" proposals.

1. **Endpoint telescoping.** The shift depends only on the *endpoints*: source closure versus observer
   closure. A photon descending into an intervening gravitational well and climbing back out gains and
   then loses the same depth — the intermediate wells **cancel**. Only `ℓ_P(source)` versus
   `ℓ_P(observer)` survives the integral. There is nothing to accumulate.

2. **Coherence / count-invariance.** Because redshift is a *re-reading of a conserved count* `N`, not a
   succession of independent scattering events, it introduces **zero blur**. The photon's phase
   coherence is untouched. This is precisely why **sharp quasar absorption lines survive** a journey of
   billions of light-years arriving still razor-thin. Tired-light models — which redshift by scattering
   photons against the medium — are *killed* here: scattering would fuzz those lines, and it is not
   observed. SDT's ruler-comparison is not a scattering; it leaves the lines sharp by construction.

3. **No time-integral.** ΛCDM compounds redshift through the scale factor `a(t)`: the wavelength is
   stretched continuously as the universe expands, an *accumulated* Doppler integral over cosmic time.
   SDT has **no such integral** — the comparison is static, a single ratio of two ruler-lengths taken at
   emission and reception. There is no `a(t)` to integrate, because nothing expands.

The three reasons are one fact viewed three ways: a ruler comparison is not a process. It cannot
compound, it cannot blur, and it cannot accumulate.

## 4. The Hubble tension, dissolved (emission + propagation)

The Hubble tension — Planck's early-universe `H₀ ≈ 67` versus SH0ES's local `H₀ ≈ 73`, a discrepancy at
several sigma — is, in SDT, **not a tension at all.** It is the signature of conflating two physically
distinct contributions to redshift that ΛCDM is forced to read as one "expansion velocity":

- **(a) Emission redshift.** Atoms sitting in high spation pressure emit at *longer* wavelength to begin
  with — this is the Depth-Closure shift `z = ϟ/r` at the moment of emission (Book IV), the same law that
  reads the solar gravitational redshift to **~0.03%** at the photosphere. The light leaves already
  reddened by where it was born.

- **(b) Propagation redshift.** As the photon crosses the relay, the `κ`-squeeze along the path — the
  changing closure `ℓ_P(r)` of §2 — adds the ruler-comparison shift between the source and the observer.

ΛCDM has only one knob, recession velocity, and must pour both contributions into it. The two famous
measurements then weight the contributions differently:

- **Planck** reads the CMB at `z = 1100`. That signal is **emission-dominated** — it is the deep-pressure
  recombination surface — and the inferred rate comes out near **67**.
- **SH0ES** reads the local distance ladder, dominated by **propagation** across the nearby underdense
  region (the local KBC void), and the inferred rate comes out near **73**.

The "tension" is the *conflation itself*. Two different mixtures of (a) and (b), forced through a single
velocity parameter, must disagree — and the size of the disagreement is just the difference in how
emission and propagation are weighted in each survey. **There is no expansion, and there is no dark
energy to reconcile.** Resolve the redshift into its two honest parts and the two `H₀` values are
measuring two different things, exactly as they should.

## 5. The absolute relay ceiling and the hidden frame (GOM05, corollary C4)

If closure relaxes with depth, then the speed of the relay does too: `c_local(r) = c_∞·(1 − z)`
(Book IV). The light-speed we *measure* is therefore not absolute — it is **Earth's local rung** of the
ladder. The engine carries the consequence:

| quantity | meaning | value | class |
|---|---|---|---|
| `z_galactic_floor` | residual relay-ceiling deficit in interstellar space | 3.5×10⁻⁷ | C |
| `c_∞ = c/(1 − z_gal)` | the absolute relay ceiling | 299 792 562.9 m/s | C |
| `c_∞ − c` | excess over locally measured `c` | ≈ 105 m/s | C |

Even far from any star, the galaxy's own convergence depth never falls to zero — there is an isotropic
**floor** `z_galactic_floor ≈ 3.5×10⁻⁷`, the relay-ceiling deficit that persists in the deep interstellar
medium. Hence the true ceiling `c_∞` *exceeds* the measured `c = 299 792 458 m/s` by `z_gal·c ≈ 105 m/s`.
The familiar constant of light is the speed *here*, on Earth's rung; the absolute relay speed is slightly
higher, and we have simply never been to a low enough depth to read it.

**The honest debt.** This makes SDT cosmology **neo-Lorentzian**: there is a preferred frame — the
absolute relay frame `c_∞` — but it is **not directly measurable**, because every clock and every ruler
we own is built at our own depth and slows in lockstep with the closure (Law V, `dτ/dt = √(1−z)`). `c_∞`
is *inferred* from the floor, not *measured*. We keep this in the open: a hidden frame that no local
experiment can reach is a structural cost of the theory, not a result of it. It is logged in the
treatise's debt ledger, not buried.

## 6. Scale closure: the Planck length from one SDT length (FLM06)

The deepest reach of the cosmology is to ask where the spation's own size comes from. Standard physics
builds `ℓ_P` from `ℏ` and `G` — but SDT forbids `G`. FLM06 instead rebuilds the Planck length from a
single SDT length via the **koppa form**:

$$ \ell_P = \sqrt{\varpi_{\text{baryon}} \cdot \lambda\!\!\!\bar{}\,_p}, \qquad
   \lambda\!\!\!\bar{}\,_p = \frac{\hbar}{m_p c}. $$

The engine evaluates `closure_floor(koppa_per_baryon, ℏ/(m_p c))` and lands on

- `ℓ_P = √(ϟ_baryon · ƛ_p) = 1.61626×10⁻³⁵ m` — equal to the input `ℓ_P` to **relative ~0** **[C, PASS]**.

This is a real reduction: it cuts the scale-seed from the *pair* `{ℏ, G}` down to **one measured SDT
length** (a baryon koppa and the proton's reduced Compton wake). **The caveat, kept honest:** this does
**not** derive `ℓ_P` from nothing. The seed is *reduced*, not *eliminated* — one length must still be
supplied. `ℓ_P` remains **Axiom R1** of the framework (see the FLM06 seed-theorem note at `law_I::N`): a
clean build of the relay count `N ≈ 5.9×10⁶¹` from below bottoms out at `z_rec ≈ 10³`, so one
action/length seed is dimensionally unavoidable. The achievement is that the *number* of independent
seeds drops to one, and that one is an SDT-native length rather than the foreign pair `{ℏ, G}`.

## 7. [FRONTIER] A cyclic cosmology — conjecture, not result

> **This section is a conjecture, not a committed investigation.** It is recorded here as the most
> natural cosmological *story* the relay suggests, but it has **no engine numbers**, no class label, and
> no delete-test. Nothing else in *De Rerum Todo Existens* depends on it. Read it as a direction, not a
> derivation.

If there was no singular Big Bang, what replaces "the beginning"? The relay points, speculatively, toward
a **cyclic detonation–recharge cosmology**:

1. Convergence builds protostars without needing a gravitational instability.
2. Some collapse promptly into **prompt darkstars** — dark, charged-up condensates that never lit
   (sidestepping the Eddington limit, and possibly easing the early-massive-object tension JWST has
   surfaced).
3. These **charge up** while the surrounding lattice cools — no heat death, because the cooling lattice
   is *storing* convergence, not dissipating it.
4. At threshold they **detonate** — a release with no singularity and no remnant horizon (Book IV's
   Depth-Closure has no true horizon to leave behind).
5. The blast **recharges** the matrix and seeds the next generation of structure on **BAO void-centred
   shells**.
6. Repeat.

On this picture the "Big Bang" would be a *prior cycle's catastrophe* — a detonation event, not a
gravity-off / inflation / singularity. Gravity (a convergence push, Book IV) is always on; there is no
moment when it switches off. Again: **conjecture.** The committed cosmology of this book is §§1–6; this
last section is the hypothesis we have not yet earned.

---

## Cross-references

- **Book I** — the relay throughput `Φ = N·ε` and convergence pressure `P_conv`; the CMB *is* this
  throughput read as the sky (`law_I`).
- **Book IV** — Depth-Closure (`z = ϟ/r`, `ℓ_P(r) = ℓ_P,∞(1−z)`), the koppa ladder, `H₀`, and `c_local`;
  this book is the cosmological reading of that depth law.
- **Book II** — the spectral ladder (octave structure of atomic lines) that §2 extends to cosmology.
- `Engine/include/sdt/laws.hpp` — `law_I` (`pressure_at_redshift`, `gamma_eff`, `H0_km_s_Mpc`),
  `depth_closure` (`z_galactic_floor`, `c_infinity`, `lP_from_closure_floor`).

## Regenerate

```bash
# MSVC
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:de_rerum.exe \
   Papers\De_Rerum_Todo_Existens\de_rerum.cpp && de_rerum.exe   # see BOOK V section
# GCC/Clang
g++ -std=c++20 -IEngine/include \
   Papers/De_Rerum_Todo_Existens/de_rerum.cpp -o de_rerum && ./de_rerum
```

*Spatial Displacement Theory · De Rerum Todo Existens · Book V · J. C. Harvey, Melbourne.*
