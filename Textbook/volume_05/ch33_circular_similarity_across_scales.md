# Chapter 33 — Circular Similarity Across Scales

*Volume V — Bodies, Fields and Propagation.*
Draft of 10 November 2026. Notation: $\mathrm{Om}=R/k^2$ (the engine's koppa length), $k=c/v$, $x=r/\mathrm{Om}$, $z_{\rm depth}=\mathrm{Om}/r$ as a defined geometric ratio only (author's ruling of 2026-11-03; it is not a slowing of the relay speed). Executable companion: `Textbook/examples/ch33_circular_similarity_across_scales.cpp`; pre-registration and captured output in `Textbook/validation/`. The orbital elements of Section 33.4 are OBSERVED and processed (published mean elements), not raw measurements.

## 33.1 A common state family

At a reference radius $R$ define $k_R=c/v_R$ and the circulation boundary length $\mathrm{Om}=R/k_R^2$. Under the inverse-square circular-response law,

$$v(r)=c\sqrt{\mathrm{Om}/r},\qquad z_{\rm depth}=\mathrm{Om}/r,\qquad k_r=\sqrt{r/\mathrm{Om}}, \tag{33.1}$$

so that $v^2r=c^2\mathrm{Om}$ and the circular acceleration is $a=c^2\mathrm{Om}/r^2$. No mass parameter is extracted: every expression keeps its geometric meaning.

## 33.2 Dimensionless similarity

With $x=r/\mathrm{Om}$,

$$\frac vc=x^{-1/2},\qquad\frac{a\,\mathrm{Om}}{c^2}=x^{-2},\qquad\frac{P_{\rm orb}\,c}{\mathrm{Om}}=2\pi x^{3/2}. \tag{33.2}$$

For positive $\mathrm{Om}$ the finite-speed circular domain is $x\ge1$. At $x=4$: $v/c=\tfrac12$, $a\mathrm{Om}/c^2=\tfrac1{16}$, $P_{\rm orb}c/\mathrm{Om}=16\pi$, exact illustrative ratios (V1) and not measured results.

**What is and is not content.** Since $\mathrm{Om}$ is defined as $v^2r/c^2$ at a point, (33.2) holds at that point as an identity. **Executed (T1).** The three relations held to $2.2\times10^{-16}$ at all nine system points tested (hydrogen $n=1$, the Earth's surface, the six planets Mercury to Saturn, the Moon's orbit). The content of the similarity claim is different: that $\mathrm{Om}$ takes **the same value at different radii** in one system, and that determinations of $\mathrm{Om}$ from **independently defined inputs** agree. Sections 33.3–33.5 test these.

The atom, planet and star correspondence consists of shared geometric relations plus different boundary conditions and response corrections. Source topology, finite extent, orientation, shielding, retardation and admissible recurrence can differ. A similarity map does not erase those differences.

## 33.3 Hydrogen

The engine's hydrogen rung is $v_H=\alpha c$ at $a_0$, so

$$k_H=\frac1\alpha,\qquad\mathrm{Om}_H=\alpha^2a_0,\qquad z_H=\alpha^2, \tag{33.3}$$

and the engine identifies $\mathrm{Om}_H$ with $r_e$. **Executed (T2).** Along the ladder $n=1\ldots8$ ($Z=1$) the product $v_n^2r_n/c^2$ equals $r_e$ to $1.1\times10^{-16}$ at every $n$: $\mathrm{Om}$ is the same at eight radii. This is **shared-input** with the CODATA set (Chapter 17): the stored $a_0$ and $\alpha$ already contain the relation, so the ladder is a statement about the stored set. The boundary interpretation is SDT-specific; algebraic correspondence with established atomic scale relations is stated after the native chain, and independent testing needs measured inputs that do not already determine the output.

The hydrogen boundary and the proton structural radius are different objects. **Executed (T6).** $r_e/R_p=3.349$ and $\mathrm{Om}_H/R_{p,\rm lock}=3.350$: neither is 1. A condition $\mathrm{Om}_H=R_p$ would require a relative structural response, and a shared rescaling of dimensional lengths cannot change a dimensionless contact ratio.

## 33.4 The Sun's planets: independent inputs, one boundary length

For a planet, $\mathrm{Om}_i=(2\pi a_i/T_i)^2a_i/c^2$ uses only the mean semi-major axis $a_i$ and the sidereal period $T_i$: no $G$ and no source mass enters, and the six planets are independent determinations. **Executed (T3).** From published mean elements (OBSERVED, processed; $c$ and the astronomical unit are the exact conversions):

| planet | $\mathrm{Om}$ (m) |
|---|---|
| Mercury | 1476.637 |
| Venus | 1476.650 |
| Earth | 1476.641 |
| Mars | 1476.679 |
| Jupiter | 1478.105 |
| Saturn | 1476.035 |

Table 33.1. $\mathrm{Om}$ of the Sun from six planets, executed (T3); the mean is $1476.791$ m.

The spread (max over min, minus 1) is $1.40\times10^{-3}$ (registered limit $2\times10^{-3}$), and the slope of $\ln\mathrm{Om}$ against $\ln x$ is $5.5\times10^{-5}$ (registered limit $10^{-4}$ in magnitude) over planets whose radii differ by a factor $24.6$ ($x$ from $3.9\times10^7$ to $9.7\times10^8$). One boundary length therefore describes the six orbits to the registered precision. The largest deviation is Jupiter's, $+1.0\times10^{-3}$ above the inner planets, which is of the size expected from the relative orbit of two sources: the engine's two-body relation (Chapter 15) gives the relative acceleration from the total source length of both bodies, so a planet of appreciable source length raises the apparent $\mathrm{Om}$ of its own orbit by about its fraction of the Sun's. That fraction (about $10^{-3}$ for Jupiter) is not loaded here and the attribution is not tested; Saturn's value lies $0.04\%$ below the inner planets, so the spread is not purely a source-length effect, and is within the processing of the elements (residual R33.3).

## 33.5 Earth: surface against the lunar orbit

Two determinations of the Earth's boundary length use different inputs: the surface circular speed and radius stored in the engine (`bridge::v_Earth`, `R_Earth`), at $x=1.4368\times10^9$, give $\mathrm{Om}_\oplus=4.434\times10^{-3}$ m; the Moon's orbit ($a=3.844\times10^8$ m, sidereal period $27.321661$ d), at $x=8.585\times10^{10}$, gives $4.477\times10^{-3}$ m. **Executed (T4).** The ratio is $1.00976$, inside the registered window $[0.98,1.02]$, over a ratio of radii of $60$. The $1\%$ excess is of the size of the Moon's own source length relative to the Earth's (about $1.2\%$) and the other perturbations of a lunar orbit (the Sun, oblateness); neither is isolated here. The stored surface speed $7909$ m/s is a rounded value (four digits, $6\times10^{-5}$ relative).

## 33.6 Pressure-state changes

For a state $S$ and a circular family,

$$\frac{d\ln v}{dS}=\frac{d\ln c}{dS}+\frac12\frac{d\ln\mathrm{Om}}{dS}-\frac12\frac{d\ln r}{dS}. \tag{33.4}$$

**Executed (T5).** For smooth test functions $c(S)=3(1+0.3S)$, $\mathrm{Om}(S)=2e^{0.2S}$, $r(S)=5(1+S^2)$, the finite-difference derivative of $\ln v$ at $S=0.4$ was $0.02302955668$, equal to the right side to $1.5\times10^{-9}$. At fixed $r$, widening $\mathrm{Om}$ slows $v$ only if the response of $c$ is sufficiently negative; at fixed $c$, widening $\mathrm{Om}$ increases the circular speed. The proposed widening and slowing behaviour therefore constrains the joint response law; the geometric definition of $\mathrm{Om}$ does not supply it.

## 33.7 Transition to the axis

Equations (33.1)–(33.2) define circular similarity. A trajectory with vanishing transverse extent needs a path-dependent formulation. The intended SDT arrest principle states that increasing phase loading can terminate physical movement before a physical infinity develops. A complete transition calculation has to determine circulation conversion, axial response, finite-size source stress and outgoing transport (Chapter 40). Circular extrapolation cannot replace it.

## 33.8 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| (33.1)–(33.2), (33.4) | Sections 33.1–33.6 | DERIVED (exact) |
| $\alpha$, $a_0$, $r_e$ | `measured::` | MEASURED-INPUT (shared-input for the ladder) |
| $v_\oplus$, $R_\oplus$ | `bridge::` | MEASURED-INPUT (rounded stored values) |
| planetary $a_i$, $T_i$; lunar $a$, $T$ | published mean elements | OBSERVED (processed ephemeris elements) |
| $\mathrm{Om}$ values, spreads, slope | Table 33.1, T3, T4 | COMPUTED |
| $c$, AU | exact conversions | MEASURED-INPUT (unit bridge) |

**Residuals.**

* **R33.1 — what the similarity is.** The relations are identities at one point; the empirical content is the constancy of $\mathrm{Om}$ and the agreement of independent determinations, established here to $1.4\times10^{-3}$ (planets) and $1\%$ (Earth).
* **R33.2 — joint response law.** Whether a widening $\mathrm{Om}$ slows $v$ depends on the response of $c$, not supplied.
* **R33.3 — perturbations.** The source lengths of the planets and the Moon, and the processing of the mean elements, are not separated from the spread.
* **R33.4 — hydrogen.** The ladder is shared-input; an independent spectroscopic depth is not available.
* **R33.5 — the axis.** The transition to vanishing transverse extent is not computed.

## 33.9 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch33_circular_similarity_across_scales
```

Criteria were registered in `Textbook/validation/ch33_PRE_REGISTRATION.md` before the instrument existed and before the observed elements were read. Run 1 (`ch33_run1_output.txt`) is the run of record and met every criterion.

## 33.10 Exercises and answers

**Exercise 1.** Derive $P_{\rm orb}c/\mathrm{Om}=2\pi x^{3/2}$.

*Answer.* $P=2\pi r/v=2\pi r/(c\sqrt{\mathrm{Om}/r})=2\pi r^{3/2}/(c\sqrt{\mathrm{Om}})$, so $Pc/\mathrm{Om}=2\pi(r/\mathrm{Om})^{3/2}$.

**Exercise 2.** Evaluate $\mathrm{Om}$ for Earth's orbit from $a=1.495983\times10^{11}$ m and $T=365.25636$ d.

*Answer.* $v=2\pi a/T=29.78$ km/s, $\mathrm{Om}=v^2a/c^2=1476.6$ m.

**Exercise 3.** Why is $v^2r/c^2$ at one radius not a test of similarity?

*Answer.* It defines $\mathrm{Om}$ there; the test is the same value at another radius or from other inputs.

**Exercise 4.** Derive (33.4).

*Answer.* $\ln v=\ln c+\tfrac12\ln\mathrm{Om}-\tfrac12\ln r$; differentiate with respect to $S$.

**Exercise 5.** What is $x$ for hydrogen $n=1$?

*Answer.* $a_0/r_e=1/\alpha^2=18779$.

**Exercise 6.** Why can $\mathrm{Om}_H=R_p$ not be obtained by rescaling lengths?

*Answer.* Both lengths scale together under a common rescaling; their ratio $3.349$ is dimensionless.

## 33.11 Scope

Established: the master relations as identities and their values on nine system points; the constancy of $\mathrm{Om}$ along the hydrogen ladder (shared-input) and across six planets to $1.4\times10^{-3}$ with no trend in radius; the agreement of surface and lunar determinations of the Earth's $\mathrm{Om}$ to 1%; identity (33.4); and the distinctness of $\mathrm{Om}_H$ and the proton radii.

Not established: the joint response law (R33.2), the separation of source-length and processing effects in the spread (R33.3), an independent atomic depth (R33.4) and the transition to the axis (R33.5).

*Where it leads.* Chapter 34 treats trajectories that are not circular: radial and transverse motion, turning points and conserved quantities.
