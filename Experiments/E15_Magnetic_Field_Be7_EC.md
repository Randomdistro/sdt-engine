# E15: Magnetic Field Effect on Be-7 EC Rate

> Source: [FINAL_REPORT §20 Q3, §21 Pred3](../ATOMICUS/EC%20Investigations/FINAL_REPORT.md)
> SDT Finding: #24 (Be-7 = He-3 core + 2 deu)

---

## 1. Background

Be-7 is the minimal EC system: He-3 core (2p+1n) + 2 deuterons.
The 1s2 bare proton captures a 1s electron at 93% probability.
This is a deterministic mechanical event — the core reels in the
valence proton and transmutes it using the closest electron.

Standard nuclear physics treats EC as a weak-force process. The
weak interaction is flavour-changing and is not affected by
electromagnetic fields. Therefore, the standard prediction is
that magnetic fields have ZERO effect on the EC rate.

SDT treats EC as a mechanical reassembly driven by the nuclear
structure circulating at specific velocities. If the 1s electron
orbital is distorted by an external magnetic field (Zeeman effect,
orbital precession), this could alter the overlap with the nuclear
surface and change the capture rate.

## 2. SDT Prediction

**Standard model**: EC rate of Be-7 is independent of external
magnetic fields at any achievable strength. The weak interaction
coupling constant is not affected by electromagnetism.

**SDT prediction**: At sufficiently high fields (>10 T), the 1s
orbital distortion may produce a measurable change in EC rate.
The magnitude depends on the ratio of Zeeman energy to the 1s
binding energy:

```text
Be-7 K-shell binding energy: ~112 eV
Zeeman energy at 10 T: ~0.58 meV (for 1s electron)
Ratio: ~5 × 10⁻⁶
```

This ratio suggests any effect would be extremely small (~ppm level).
However, the SDT mechanism is a threshold process (mechanical reel-in),
not a continuous probability. If the magnetic field shifts the electron
density at the nuclear surface past a threshold, the effect could be
discontinuous rather than proportional.

**Conservative SDT estimate**: No detectable effect below 10 T.
Possible ppm-level effect at 20-45 T (pulsed field range).

## 3. Observable

Measure the Be-7 EC half-life (t½ = 53.22 ± 0.06 d) in:
- Zero field (reference)
- 10 T (superconducting magnet)
- 20 T (hybrid magnet)
- 45 T (pulsed field, if duration permits counting statistics)

Required precision: better than 0.01% (100 ppm) to detect a
magnetic field effect at the predicted magnitude.

## 4. Apparatus

- Be-7 source (produced by Li-7(p,n)Be-7, commercially available)
- High-field magnet facility (NHMFL Tallahassee: 45 T steady-state;
  Los Alamos: 100 T pulsed; Nijmegen: 38 T)
- Gamma-ray detector (HPGe) to count 477.6 keV photons from Be-7 EC
- Temperature-controlled sample holder (EC rate has known ~0.1%
  chemical environment dependence — must be controlled)
- Measurement duration: several half-lives (~150–200 days) at each
  field strength for sufficient statistics

## 5. Feasibility

**Difficulty: MODERATE**

- Be-7 sources are cheap and widely available
- 477.6 keV gamma detection is routine
- The primary challenge is maintaining a high magnetic field for
  months continuously. 10 T superconducting magnets can run
  indefinitely. Higher fields (20-45 T) require resistive or
  hybrid magnets with significant power consumption.
- Chemical environment effects must be rigorously controlled:
  same chemical form, same temperature, same pressure at all
  field strengths. The known ~0.1% variation in Be-7 half-life
  between metallic Be and BeO must be accounted for.

## 6. Existing Constraints

- Be-7 half-life varies by ~0.1% depending on chemical environment
  (metallic Be vs BeO vs BeF₂). This is a known atomic-physics
  effect (electron density at nucleus changes with bonding).
- No measurement of Be-7 EC rate in magnetic fields >1 T has been
  published.
- The chemical-environment effect confirms that electron density
  at the nuclear surface DOES affect EC rate — supporting the
  premise that magnetic orbital distortion could produce a similar
  (smaller) effect.

## 7. Impact

- **If effect detected**: Demonstrates electromagnetic coupling to
  a nominally weak-interaction process. Consistent with SDT's
  mechanical picture where the electron orbital geometry directly
  governs the capture. Major result.
- **If no effect detected (at ppm level)**: Places an upper bound
  on the magnetic sensitivity of EC. Consistent with both standard
  model and the conservative SDT estimate. Does not falsify SDT
  but constrains the coupling strength.
