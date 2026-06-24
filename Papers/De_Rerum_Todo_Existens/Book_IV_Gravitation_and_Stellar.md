# Book IV — Gravitation & Stellar Structure
### *De Rerum Todo Existens*, Book the Fourth: no pull, real orbits, and the star as a giant atom

> **Author:** James Christopher Harvey, Melbourne. 2026.
> **Engine:** every number below is emitted by [`de_rerum.cpp`](de_rerum.cpp) (Book IV section) and
> reproduced in [`de_rerum_results.txt`](de_rerum_results.txt). Class labels (A/B/C/F) are the
> engine's own certification, kept verbatim. See [README](README.md) for the class key.

---

## 0. Orientation: gravity is a push, and mass is an absence

Standard physics treats gravity as a force that mass *emits* — a pull that reaches out, scaled by a
universal constant `G`. SDT keeps neither object. There is no `G` and no `M` among the inputs, and
there is no attraction at all. What is real is the relay of Book I: the cosmic-microwave convergence
floods in from every direction and **pushes** on everything. A body, being a displacement boundary
(Book I, §1), casts a **convergence shadow** — it occludes the convergence behind it. Two bodies each
sit in the other's shadow, so on the line between them the push is weaker than on the far sides. The
**imbalance** drives them together. Gravity is **subtractive occlusion**: the unoccluded side wins.

This single move — mass as *absence*, force as *imbalance in a push* — settles the sign question that
defeats field theories of gravity (Book III, the EMC03 sign-gap): occlusion can only remove convergence,
never add it, so gravity is **attraction-only by construction**. There is no antigravity because there
is no surplus channel for mass. Everything that follows reads one observable — the **koppa length**
`ϟ = v²R/c²` — as the local geometry of that imbalance.

And crucially: **no pull, real orbits.** A closed least-resistance path through the radial depth
gradient *is* an orbit. The planet is not held by a string of force; it follows the easiest path
through a graded medium, and the easiest closed path is the ellipse. This book derives gravity, the
constants of orbital mechanics, the speed of light, gravitational waves, and the structure of stars
from that one reading — with `G` appearing nowhere except in the legacy `GM_equivalent()` helper that
translates results *out* to textbook units.

## 1. The koppa ladder: `g = v²/R`, one law across forty orders of magnitude

Take away `G` and `M` and you are left with what is actually measured at a surface: a velocity and a
radius. SDT's gravitational descriptor is the **koppa length**

$$ ϟ = \frac{v^2 R}{c^2} = \frac{R}{k^2}, \qquad k \equiv \frac{c}{v}, $$

a length built from a surface velocity `v`, a radius `R`, and `c` — nothing else. The surface gravity
is then `g = v²/R = c²ϟ/R²`, with no `G` and no `M` anywhere in it. `k` is the **rung index** (`c/v`,
how many steps the body sits from the light-speed boundary); `ϟ` is the **geometric length** the rung
encodes. The same two-line law runs from a hydrogen atom to a star:

| body | koppa `ϟ = v²R/c²` | meaning | class |
|---|---|---|---|
| **hydrogen** | `ϟ_H = α²a₀ = 2.817940×10⁻¹⁵ m` | **equals the classical electron radius `r_e`** to rel `1.94×10⁻¹²` | B |
| **Moon** | `ϟ_Moon = 5.456033×10⁻⁵ m` | lunar surface gravity, no G/M | B |
| **Earth** | `ϟ_Earth = 4.434139×10⁻³ m` | `g_surface = v²/R = 9.818283 m/s²` (Earth gravity, **no G, no M**) | B |
| **Sun** | `ϟ_Sun = R_Sun/k_Sun² = 1.477046×10³ m` | `k_Sun = 686.3`; the solar field in one number | B |

The hydrogen rung is the hinge that ties this book to Book II: the koppa of the hydrogen ground state
**is** the classical electron radius (`ϟ_H = α²a₀ = r_e`), and its rung index is `k_H = 1/α = 137.036`.
Gravity and the atom are the *same* ladder; the only difference between a hydrogen atom and the Sun is
how many rungs `k` you stand from the c-boundary. One law, ~40 orders of magnitude.

- **Class C** for the gravitational use (`g = v²/R` passes its delete-test: surface gravity recovered
  with no `G`/`M`); **Class B** for the koppa lengths, which are built from measured `v`, `R`, and the
  whitelist. **Caveat:** `ϟ` equals `GM/c²` numerically — but that is a *consequence*, not an input.
  The model never loads `GM`; it loads `v` and `R` and lets the identity emerge.

## 2. `c` recovered from Mercury's precession (GOM04)

If gravity is geometry and not a `G`-coupling, then the orbital anomaly that founded general relativity
should be re-derivable as a koppa-closure with no `G` in the chain. The engine does exactly this:
treating Mercury's perihelion advance as a closure condition on the solar koppa rung, it solves for the
relay tick speed and recovers

$$ c_{\text{from closure}} = 2.99795\times10^{8}\ \text{m/s} \;=\; c \;\text{to rel}\; 8.93\times10^{-6}. $$

The speed of light, to six significant figures, falls out of an **orbital anomaly** with `G` nowhere in
the computation. In the textbook account the precession is a metric effect proportional to `GM/(c²a)`;
in SDT it is the same koppa geometry read inversely — the anomaly *measures* `c`, because the anomaly is
a depth effect and depth is a closure deficit (§3). **Class C** (sound on framework terms: it uses the
solar koppa rung, which is a measured `v`,`R` observable, not a fitted coupling).

## 3. Depth–Closure: depth = closure deficit = light-speed deficit (the capstone)

This is the theorem the whole book converges on, stated in full in
[`Papers/Depth_Closure_Theorem/01_THEOREM.md`](../Depth_Closure_Theorem/01_THEOREM.md). The claim is an
**identity of four quantities** that standard physics keeps separate:

$$ z \;=\; \frac{ϟ}{r} \;=\; 1 - \frac{\ell_P(r)}{\ell_{P,\infty}} \;=\; 1 - \frac{c_{\text{local}}}{c_\infty} \;=\; \left(\frac{v}{c}\right)^2. $$

The **convergence depth** `z = ϟ/r` *is* the fractional tightening of the local spation closure `ℓ_P(r)`,
which *is* the fractional deficit in the local relay speed `c_local`, which *is* (via the Law V movement
budget) the local clock rate `dτ/dt = √(1−z)`. Depth, closure, light-speed, and clock are **one
quantity** read four ways. The bound-motion law is the unique velocity consistent with it:
`v(r) = c√(ϟ/r) = c√z`, i.e. `v²/r = g = c²ϟ/r²`.

Two measured corollaries anchor the theorem:

- **Solar gravitational redshift = depth at emission.** `z = ϟ_Sun/R_Sun = 2.12311×10⁻⁶`, equal to the
  observed solar redshift to rel `1.47×10⁻³` (0.03% in the original Depth-Closure paper). The shift is
  **the displacement depth at the point of emission** — light leaving a tighter-closure region carries a
  longer ruler — **not** a metric climb out of a well. This is the keystone result of SDT gravitation.
  **Class C.**
- **Shapiro delay = accumulated depth, not slowing in a well.** For Sun-grazing geometry the engine
  returns `Δt = 1.195055×10⁻⁴ s`, matching GR and the Cassini/Viking measurements. The mechanism is the
  inverse of the textbook story: the ray crosses regions of **smaller spations** (tighter closure), so it
  takes more ticks to cross the same coordinate distance — the **local light speed stays `c`**; what
  accumulates is depth. **Class C.**

**Class:** C throughout — the theorem is sound *on framework terms*, given SDT's reading of `α` as the
koppa-rung. **Caveat:** the proven content is the redshift–depth identity (C1) and the single
centripetal law (C2). The absolute closure `ℓ_P,∞`, the galactic-floor magnitude, and the proton/electron
internal radii remain open and travel with the theorem as stated caveats, not as theorem content.

## 4. No pull, real orbits — and the acceleration floor

Because there is no attraction, an orbit is not a balance of pull against centrifugal flight. It is a
**closed least-resistance path** through the radial depth gradient `z(r) = ϟ/r`: the planet coasts along
the easiest contour, and the easiest *closed* contour is the orbit Kepler measured. The bound-motion law
`v = c√(ϟ/r)` reproduces orbital speeds across the solar system from the koppa alone — Earth's
29.79 km/s, a 292-AU orbit's 1.74 km/s — without `G` or `M`.

At the faint-field limit the depth gradient flattens to a floor. The engine derives the crossover
acceleration

$$ a_0 = \frac{c\,H_0}{2\pi} = 1.042190\times10^{-10}\ \text{m/s}^2, $$

numerically the MOND acceleration `a₀`, here **derived** from `c` and the relay rate `H₀` rather than
fitted. A deliberately wrong floor degrades the cross-scale APS03 collapse sixfold, confirming the value
is required, not cosmetic; the same floor fits 135 SPARC galaxies (GD05) unbiased at RMS 23.8% with the
correct baryonic Tully–Fisher slope. **Class C, with a flagged caveat:** `a₀` inherits `H₀`'s
Friedmann-structure caveat from Law I — the relay rate `H₀` is read through a cosmological-fit scaffold
whose internal structure is not yet fully SDT-native. That caveat is kept in the open and carried to
Book V.

## 5. Gravitational waves: move the sea, don't make waves (GOM06)

If gravity is a depth field and not a radiated force, what does LIGO detect? SDT's answer (GOM06, *"move
the sea, not make waves"*): the chirp is not energy launched into a vacuum — it is a **moving length**.
The detectable quantity is the binary's total koppa `ϟ_tot`, and LIGO is a **koppa-meter**. At the
innermost stable circular orbit the geometry fixes `r_isco = 6ϟ_tot` and

$$ f_{\text{GW,isco}} = \frac{c}{\pi\,6^{3/2}\,ϟ_{\text{tot}}}. $$

For a fiducial `ϟ_tot = 3 km` the engine returns `f_GW = 2.164326×10³ Hz`. The same formula gives the
GW150914 ISCO frequency from its koppa with no `G` and no `M` in the line. The strain is a **tensor
natively**: its trace is the depth (monopole, conserved — so no breathing mode), its shear is the wave.
**Class C.** **Caveat (disclosed):** the ISCO relation is the koppa-bridge identity `GM ≡ c²ϟ` applied to
GR's ISCO geometry — an algebraic identity flagged as such, not an independent derivation of the ISCO
condition.

## 6. The lumiopause and lumiostasis (GOM05)

The solar depth domain does not extend forever; it ends where the Sun's own outflow falls to the
convergence floor. The condition is a **surface-area** balance — solar flux equal to the CMB flux,
`L_Sun/(4πr²) = F_CMB` — which the engine solves to

$$ r_{\text{lumiopause}} = \sqrt{\frac{L_{\text{Sun}}}{4\pi F_{\text{CMB}}}} = 2.085731\times10^{4}\ \text{AU}. $$

This is the radius of the Oort cloud — and SDT's reading of *why* it sits there is sharp: the Oort
bodies are not orbiting in the Keplerian sense. They are held in **lumiostasis** — suspended at the depth
surface where the convergence gradient balances the residual outflow, like motes resting at a thermocline.
They sit at a *depth*, not on an orbit. **Class C.** This predicts (P3 of the theorem) that detached/Oort
objects cluster at the lumiopause depth surface rather than following a purely Keplerian
semi-major-axis distribution — a falsifiable departure from the standard picture.

## 7. Stellar structure: the star as a giant atom (ATOMICUS Laws 19–22)

The koppa ladder did not stop at the Sun by accident. The construction grammar of Book II
(`1 alpha core + n_d deuterons + n_t tritons`) is scale-free: **a star is the same architecture geared
up**, as chemistry is the same architecture geared down. These are the Stellar Laws (ATOMICUS Laws
19–22); they are **class C / structural** — mechanism-complete on framework terms, with the numbers
that exist quoted as order-matches, not closures.

- **Law 19 — A star is a giant atom.** A star is a giant baryonic core inside nested convergence
  cavities, bound by the one occlusion law — Atomicus geared up. Stellar structure and atomic structure
  are the *same* occlusion/circulation problem at two scales.
- **Law 20 — Stellar neutronisation = mass electron capture.** Near the stellar **c-boundary** the last
  electrons are pressure-trapped on their protons and cannot unbind, so each proton **force-captures** its
  electron: `p + e⁻ → n + ν`. This is the He-3-core electron-capture grammar (the *alternate* grammar of
  Book II) run across ~10⁵⁷ sites. It is **charge-balanced** (a plus and a minus removed together → no
  imbalance), so it builds the **neutron-star remnant** and fires the **neutrino burst** (≈2.7×10⁴⁵ J,
  order-matching the observed ~10⁴⁶ J — the burst *is* the capture receipts).
- **Law 21 — Fission causes electron capture.** Electron capture is **defect-repair**: a He-3 core is an
  incomplete tetrahedron (a vacant neutron site), healed by capturing an electron. What *makes* the defect
  is fission/spallation — splitting a nucleus leaves an exposed He-3 remnant. The Sun runs the gentle
  version now: the p-p chain makes He-3 → Be-7 → (Be-7 + e⁻ → Li-7 + ν), and those Be-7 neutrinos are
  measured. *(Open: the full "all EC isotopes are spallation remnants" claim still needs the per-isotope
  check; the He-3 → EC link is confirmed and ongoing in the Sun.)*
- **Law 22 — The supernova is the unscreened inverse-convergence.** This is the EMC03 sign-mechanism
  (Book III) at stellar scale. A star holds only while it stays neutral to ~1 part in 10¹⁸. The electron
  sea **screens** the proton repulsion; when capture/ablation outruns re-screening and the deficit crosses
  threshold, the **unscreened inverse-convergence detonates**. Two channels: the balanced core →
  neutron star + ν burst (Law 20); a tiny envelope imbalance (`f ≈ 5×10⁻¹⁸`) → a ~10⁴⁴ J Coulomb blast
  (the visible ejecta). The energy is electromagnetic (the EM/gravity budget ratio ~10³⁶, so the energy is
  trivially available) — it is **not** a gravitational bounce, which is why the explosion never stalls.
  *(Open: the channel-coupling and the light-curve / Ni-56 reproduction; the three energetics — remnant,
  neutrino burst, kinetic — are order-consistent.)*

The throughline: occlusion, circulation, and the He-3 grammar do not care about scale. The atom and the
star are the same machine, and the supernova is the same sign-flip (surplus, not deficit) that gives
electromagnetism its repulsion in Book III.

---

## Cross-references

- **Book I** — the convergence relay `P_conv` is the push; the movement budget `v_circ²+v²=c²` is the
  clock factor `√(1−z)` of the Depth–Closure theorem; mass-as-absence makes gravity attraction-only.
- **Book II** — `ϟ_H = α²a₀ = r_e` and `k_H = 1/α = 137.036`: the hydrogen rung of *this* book's koppa
  ladder; the He-3 / alpha+deuteron+triton grammar reappears as the Stellar Laws of §7.
- **Book III** — the supernova (Law 22) is the EMC03 inverse-convergence (surplus, not deficit) at
  stellar scale; the screening electron sea is the same handed-redirection mechanism.
- **Book V** — `a₀ = cH₀/2π` and the galactic depth floor inherit the relay's `H₀` caveat; redshift as
  depth here connects to redshift as octaves there.
- `Engine/include/sdt/laws.hpp` — `bridge` (koppa ladder, `c_from_closure`, `f_GW_isco`),
  `depth_closure` (the full theorem, Shapiro, `a0_floor`, `lumiopause_AU`).

## Regenerate

```bash
# MSVC
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:de_rerum.exe \
   Papers\De_Rerum_Todo_Existens\de_rerum.cpp && de_rerum.exe   # see BOOK IV section
# GCC/Clang
g++ -std=c++20 -IEngine/include \
   Papers/De_Rerum_Todo_Existens/de_rerum.cpp -o de_rerum && ./de_rerum
```

*Spatial Displacement Theory · De Rerum Todo Existens · Book IV · J. C. Harvey, Melbourne.*
