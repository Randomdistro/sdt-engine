# NP12 — Nuclear Charge-Radius Scaling

> **Author:** J. C. Harvey, Melbourne
> **Status:** Z-linear law EXCLUDED; close-pack successor RECOVERED
> **Run:** 2026-07-03
> **Instrument:** `np12_radius_scaling.py` → `np12_results.txt`

## Evidence

The registered comparison used 908 isotopes from the IAEA/Angeli–Marinova
charge-radius compilation.

| Model | RMS relative error | R² | Result |
|---|---:|---:|---|
| $Z R_p$ | 890.8% | −3281.6 | EXCLUDED |
| $1.2A^{1/3}$, sharp radius compared as RMS | 25.6% | −1.46 | unit-mismatched form excluded |
| $0.9295A^{1/3}$, empirical reference | 5.00% | 0.960 | reference fit |
| $R_p(A/eta)^{1/3}$, $eta=pi/sqrt(18)$ | 4.96% | 0.961 | zero-fit close-pack result |
| $1.2708Z^{1/3}$ | 3.85% | 0.984 | CALIBRATED(1), diagnostic only |

The linear law fails because it adds proton radii in one dimension while the
nucleus occupies three-dimensional packed volume. The He-4 contact statement
$R_{He}=2R_p$ is a separate boundary construction and is not tested by the
all-nucleus $ZR_p$ scaling.

## Unit-consistent successor

$R_p=0.8414$ fm is an RMS radius. Converting it to a sharp radius,
close-packing, and converting the total back to RMS gives

$$R_{p,sharp}=R_p sqrt(5/3)=1.0862\;fm,$$

$$R_{sharp}=R_{p,sharp}(A/eta)^{1/3}=1.2007A^{1/3}\;fm,$$

$$R_{rms}=R_{sharp}sqrt(3/5)=R_p(A/eta)^{1/3}=0.9300A^{1/3}\;fm.$$

The conversion factors cancel. The previously evaluated
$0.7207A^{1/3}$ branch applied the RMS conversion on only one side and is
dimensionally inadmissible; it is not a physical uniform-charge alternative.

## Scope and remaining debt

- The close-pack coefficient is derived from prior $R_p$ and
  $eta=pi/sqrt(18)$, with no fitted coefficient.
- Its numerical shape is shared with the empirical $A^{1/3}$ law; this
  dataset distinguishes provenance, not curve shape.
- Isotopic chains are flatter than a bare $A^{1/3}$ law. The ATOMICUS
  triton-contraction rule supplies the identified correction, but a
  whole-range per-isotope prediction remains required.
- Canon must not expose $R=ZR_p$ as a general nuclear-radius law.
