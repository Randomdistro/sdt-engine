# The Depth–Closure Thread — Distillation

> A start-to-finish record of the exchange that produced the Depth–Closure
> Theorem. Every number herein reproduces from `keystone.js` (one run).
> Author: James Christopher Harvey, Melbourne. Recorded June 2026.

---

## How the thread moved (chronological spine)

1. **Shapiro delay (CQ15).** SDT reproduces the Shapiro time delay exactly as a
   *depth integral* `Δt = (2/c)∫z dl` with `z(r)=ϟ/r`, giving the log form and
   matching GR/observation to 0.0000%. Light's local speed stays c; the delay is
   accumulated lattice depth, not slowing-in-a-well.

2. **The mechanism turn (James).** The depth is not "more shells at fixed ℓ_P" —
   **the spation closure ℓ_P itself shrinks where matter crushes the space it
   displaces.** Nucleons displace volume; that displacement is the depth. Light
   relays one spation per tick, so a smaller local closure = locally slower light.
   This became **CQ43**: `ℓ_P(r)=ℓ_P,∞(1−z)`, `c_local=c(1−z)`,
   `z = 1−ℓ_P(r)/ℓ_P,∞ = 1−c_local/c = ϟ/r` — one quantity, three readings.

3. **No attraction; orbits are real.** Nothing is pulled. The CMB convergence
   pushes everything together; matter follows the path of least resistance through
   the depth gradient — and a closed least-resistance path through a radial
   gradient *is* an orbit. (Author correction: "no attraction" ≠ "no orbits".)

4. **koppa is a velocity quantity** `ϟ = R/k², k = c/v`; the *depth* is the
   dimensionless `z = 1/k² = ϟ/r`. (Author correction, kept throughout.)

5. **The lumiopause (James's coined term).** A *surface-area* condition:
   `L_sun/(4πr²) = F_CMB ⟹ r = √(L_sun/4πF_CMB) = 20,857 AU`. The Oort cloud is
   suspended there — **lumiostasis** — held where the convergence gradient
   balances, not orbiting.

6. **k is a timer; 137 is a countdown.** From the movement budget (Law V),
   `dτ/dt = √(1−1/k²) = √(1−z)`. k *is* the clock-rate; it counts down toward the
   c-boundary k=1 (v=c, dτ/dt=0, matter dissolves). Hydrogen sits k=1/α=137 steps
   from the edge. α = v/c = 1/k is speed ratio, clock-rate, and countdown position
   at once.

7. **c is local.** Our 299,792,458 m/s is Earth's rung. We sit at depth
   z≈3.5×10⁻⁷ (galactic floor), so the absolute ceiling is `c_∞=c/(1−z)`, about
   **+105 m/s** above our c. The c-boundary radius is ceiling-relative and
   *breathes* with depth (∝(1−z)²).

8. **The spation floor (CQ42), in koppa form.** A length needs one absolute seed
   (proven: {c,T,counts} cannot make a length). Planck's `√(ℏG/c³)` imports both
   forbidden constants. The koppa restatement `ℓ_P = √(ϟ·ƛ)` — geometric mean of a
   koppa and a wake — is **mass-independent** (the spation is the universal fixed
   point where koppa = wake, i.e. z=1, k=1) and reduces the irreducible seed from
   two borrowed constants to one measured SDT length.

9. **The proton operator.** The (2,3) trefoil is a **6π** operator (q=3 poloidal
   wraps × 2π). The proton sits inside its own c-boundary (surface at 1.830c, k<1,
   superluminal phase). Its centre is the crushed throat: v→∞, fixed rotation→0,
   zero width, zero matter. The mass ratio is the *separate* 6π signature
   **6π⁵ = 1836.118** (not the 1.830c surface velocity — two distinct results that
   share digits).

10. **The point electron.** r_e (2.82×10⁻¹⁵ m) is the electron's *wake
    c-boundary*, not its body. The body is a true point particle, ~10⁻²⁰ m. Tidally
    locked (one axial rotation per orbit, ω=4.13×10¹⁶ rad/s), its surface crawls at
    ~1.2 mm/s while its orbit runs at αc — the point particle barely turns.

11. **The keystone test (James).** *Is the solar gravitational redshift equal to
    the SDT displacement depth at the emission depth?* **Yes — to 0.03%.** The
    redshift IS the depth. Solar hydrogen emits its wavelength in its pressure
    regime; lab hydrogen in ours; we read the difference as z. Satellite time
    dilation is exactly the pressure regime at altitude (the GPS correction).

12. **One law, all scales.** The pressure→orbit relation is centripetal:
    displacement pressure provides the centripetal force, `v²/r = c²ϟ/r²`, so
    **v = c√(ϟ/r) = c√z**. Validated forward: Earth orbit 29.789 km/s (obs 29.78),
    292 AU 1.742 km/s, hydrogen v=αc → k_H=137 → koppa=r_e → proton surface 1.830c.
    The same law spans ~15 orders of magnitude.

---

## The keystone numbers (one reproducible run, `keystone.js`)

| quantity | value | check |
|---|---|---|
| solar redshift GM/(c²R) | 2.1225×10⁻⁶ | — |
| SDT depth ϟ_Sun/R_Sun | 2.1231×10⁻⁶ | **ratio 1.0003** |
| Earth orbit v=c√(ϟ/r) | 29.789 km/s | obs 29.78 (0.03%) |
| 292 AU orbit v=c√(ϟ/r) | 1.742 km/s | — |
| hydrogen k_H = c/(αc) | 137.036 | = 1/α |
| koppa_H = α²a₀ | 2.818×10⁻¹⁵ m | = r_e (exact) |
| proton surface v_phase | 1.830 c | k=0.5464 |
| dτ/dt at k=1/α | 0.9999734 | clock-rate |
| absolute ceiling c_∞ | c+105 m/s | galactic floor |
| a₀ = cH₀/2π | 1.042×10⁻¹⁰ m/s² | derived floor |
| ℓ_P = √(ϟ_b·ƛ_p) | 1.616×10⁻³⁵ m | = ℓ_P (koppa form) |
| lumiopause √(L/4πF_CMB) | 20,857 AU | Oort edge |
| 6π⁵ (mass ratio) | 1836.118 | m_p/m_e=1836.153 |

Supporting prior runs: E46 M4 floor law (SPARC, 135 galaxies) RMS 23.8%,
BTFR 3.58; CQ26 cross-scale collapse RMS 8.8%, negative control 6× worse.

---

## What is proven vs open (honest ledger)

**Proven (measured this thread):**
- z (gravitational redshift) = ϟ/r = displacement depth at emission — 0.03%.
- v = c√z reproduces orbital velocities Earth→292 AU and the hydrogen ladder.
- k_H=137, koppa_H=r_e, proton surface 1.830c all from the one law.
- ℓ_P = √(ϟ·ƛ) reproduces the Planck length, mass-independent.
- lumiopause = √(L/4πF_CMB) = 20,857 AU exactly.

**Open / honest caveats:**
- The *absolute* ℓ_P,∞ still needs one seed (CQ42 seed theorem); only its
  *variation* (1−z) is fully SDT-native.
- The galactic floor (+105 m/s) carries the MW-mass uncertainty (~±20%).
- The 1.830c surface velocity and 6π⁵ mass ratio are *distinct* trefoil
  signatures; their shared digits are not (yet) bridged by any derivation.
- The point-electron radius (~3×10⁻²⁰ m) is measured from the 1.2 mm/s locked
  rotation, not yet derived from W=1 displacement geometry.

These caveats are the paper's "future work," stated plainly. The theorem rests
only on the proven row.
