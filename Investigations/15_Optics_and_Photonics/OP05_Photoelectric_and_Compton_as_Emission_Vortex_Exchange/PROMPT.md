# OP05 — Photoelectric and Compton as Emission↔Vortex Exchange

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

The photoelectric threshold and the Compton wavelength shift are the textbook proofs that light is
a particle carrying `E=hf` and `p=h/λ`. SDT has no photon-particle — light is an emission. **Can
E55 (photoelectric: prompt sub-attosecond absorption with a sharp frequency threshold) and E56
(Compton: a measured wavelength shift on scattering off a bound vortex) be reframed as
emission↔vortex exchange — the relay impulse being absorbed into, or recoiling off, an electron
vortex with lattice momentum bookkeeping — reproducing `hf = W + KE_max` and
`Δλ = λ_C(1−cosθ)` without ever invoking a point quantum of light?** The "quantum" facts become
threshold and recoil facts about how a relay emission couples to a vortex.

## SDT mechanism & hypotheses

An electron is a bound vortex (Law VI topology). The emission's energy is `E = h·f` where `f` is its
relay-tick rate; absorption is the vortex swallowing the relay impulse in one coherent gulp (fast =
sub-attosecond, E55), possible only above the binding threshold `W`. Compton is elastic recoil: the
emission hands transverse + forward momentum to the vortex, which the lattice must conserve.

- **H1 (photoelectric threshold = vortex binding):** the emission couples only if its per-tick energy
  exceeds the vortex binding `W`; above threshold `KE_max = hf − W`, slope `h` (the relay tick→energy
  conversion), intercept `W` — Millikan's line, native, with `h` not a photon mass.
- **H2 (prompt absorption):** absorption time is one relay coherence time (sub-attosecond), matching
  attosecond-streaking measurements — no semiclassical build-up delay.
- **H3 (Compton = lattice recoil):** momentum conservation between emission and vortex gives
  `Δλ = (h/m_e c)(1−cosθ) = λ_C(1−cosθ)`; `λ_C` is the electron-vortex relay scale, recoverable from
  the vortex geometry, not from a photon collision postulate.

## Strategy

**Phase 1 — Emission energy/momentum ledger.** *Goal:* native `E=hf`, `p=E/c` for a relay emission.
*Method:* tick-rate × relay quantum from CR07 ruler. *Success:* `E` and `p` of an emission defined
without a photon, consistent with measured photon energies to <0.1%.

**Phase 2 — Photoelectric line.** *Goal:* `KE_max=hf−W`. *Method:* threshold coupling to a vortex of
binding `W`. *Success:* Millikan slope = `h`; thresholds for Na/Cs/W to order; prompt (attosecond) time.

**Phase 3 — Compton shift.** *Goal:* `Δλ=λ_C(1−cosθ)`. *Method:* emission↔vortex elastic recoil with
lattice momentum conservation. *Success:* `λ_C=2.426 pm` and the full angular shift to <0.1%.

**Phase 4 — Inverse/Thomson limits (stretch).** *Goal:* Thomson (`Δλ→0`) and inverse-Compton limits.
*Success:* low-energy and moving-vortex limits correct in sign and scale.

## Success criteria

- **PASS (A):** photoelectric line and Compton shift from emission↔vortex exchange, zero photon-particle, zero fits.
- **QUALIFIED (C):** the above with `W` (work functions) and `m_e` as MEASURED inputs (expected).
- **PENDING (D):** Compton recovered, photoelectric threshold only schematic (or vice versa).
- **FAIL (F):** cannot get the threshold/shift without reintroducing a point photon.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 photoelectric | `KE_max=hf−W`, slope=h, sharp threshold | absorption not a vortex-coupling threshold |
| T2 Compton | `Δλ=λ_C(1−cosθ)`, λ_C=2.426 pm | scattering not lattice-momentum recoil |
| T3 prompt timing | sub-attosecond absorption (no delay) | emission↔vortex exchange not instantaneous-relay |

## Dependencies

**Upstream:** OP01 (emission relay, λ=N·ℓ_P). **Ties:** E55 (photoelectric), E56 (Compton).
**Downstream:** OP06 (stimulated emission = reverse exchange), pair-production/QED reframes.
**Related:** Law VI topology (electron vortex), [[project_cq46_redshift_octaves]] (relay ruler),
E57 (Cherenkov, the inverse "charge outruns c_local" case).
