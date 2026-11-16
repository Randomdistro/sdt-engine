# Chapter 41 — The Spaz State and Sz

*Volume VI — Sz, Pressure History and Coupled Ratios.*
Draft of 10 November 2026. Notation: $S$ is a local state coordinate that indexes a branch of coupled response; Sz is the proposed reporting convention; $a_i=d\ln Q_i/dS$ is the log-derivative of a positive quantity $Q_i$ with respect to $S$; $k=c/v$, $\mathrm{Om}=R/k^2$. Executable companion: `Textbook/examples/ch41_the_spaz_state_and_sz.cpp`; pre-registration and captured output in `Textbook/validation/`. All functions in this chapter are generic test functions (TOY) with no measured input.

## 41.1 State reporting

Spaz measures how physical ratios scale together. A local state coordinate $S$ indexes a branch of coupled response, and Sz is the proposed reporting convention. Neither name assigns an absolute zero, a normalisation or a universal evolution rate. The operational content is a family of ratios $Q_i(S)/Q_i(S_0)$ under declared composition, orientation, boundary and history conditions. For positive quantities, $x_i=\ln[Q_i(S)/Q_i(S_0)]$ makes multiplicative changes additive.

## 41.2 Invariance under reparameterisation

Finite ratios are invariant under $S\to f(S)$; derivatives transform by the inverse derivative of $f$. A physical law therefore cannot depend on the numerical spacing of Sz marks unless that spacing has an operational calibration.

**Executed (T1; V1).** The log-derivative routine gave $d\ln e^{2S}/dS=2$ and $d\ln S^3/dS=3/2$ at $S=2$ to $1.5\times10^{-13}$. For $Q(S)=\exp(0.7S+0.2\sin3S)$ with $S_0=0.1$ and $f(S)=S+0.3S^3$, the ratio $Q(S)/Q(S_0)$ computed in the variable $S'=f(S)$ equalled the original at 50 points to $2.2\times10^{-16}$, and $d\ln Q/dS'$ equalled $(d\ln Q/dS)/f'(S)$ to $5.5\times10^{-12}$.

**Executed (T5).** A rate that is constant in $S$ is not constant in another parameterisation. For $Q=e^{-0.8S}$ the log-derivative is constant in $S$ (coefficient of variation $3.6\times10^{-13}$); in $S'=S^2$ it is $-0.8/(2\sqrt{S'})$, with a coefficient of variation $0.416$. A statement such as "the quantity decays at a constant rate per Sz mark" is a statement about a chosen spacing and needs the spacing's calibration to mean anything physical.

## 41.3 Compatibility and constitutive freedom

Relations among quantities constrain the response without forcing a universal exponent. For a speed ratio $c=P_l/P_t$,

$$a_c=a_{P_l}-a_{P_t}. \tag{41.1}$$

For $v=c/k$ and $k^2=r/\mathrm{Om}$, $a_v=a_c-a_k$ and $2a_k=a_r-a_{\rm Om}$. **Executed (T2).** For 20 values of $S$ and random smooth positive functions $P_l,P_t,r,\mathrm{Om},c$, the three relations held to $3.1\times10^{-13}$, $2.4\times10^{-13}$ and $3.5\times10^{-13}$.

Exact compatibility leaves constitutive freedom: the state can follow a curved route through the admissible ratio manifold. **Executed (T3).** Route A with $P_l=e^S$, $P_t=e^{S/2}$ and route B with $P_l=e^{2S}$, $P_t=e^{3S/2}$ give the same ratio $c=e^{S/2}$ at every $S$ (to $3.3\times10^{-16}$), while $a_{P_l}=1$ on A and $2$ on B. The relation (41.1) cannot select between them. Choosing a route needs a constitutive law, the subject of Chapter 43.

## 41.4 Beyond a scalar, and the limits of logarithms

Polarisation, anisotropy, phase fractions and memory need additional state coordinates unless a demonstrated mechanism slaves them to $S$. Logarithms fail at zeros, sign changes and discrete topology jumps. **Executed (T4).** For $Q=\sin S$ on 1000 points of $[0.1,6.2]$ the logarithm is undefined (non-positive argument) at $501$ points, while the signed chart $\sinh^{-1}(Q/Q_{\rm ref})$ is finite at all 1000. But the monomial relations rest on $\ln(AB)=\ln A+\ln B$ (held to $2.3\times10^{-16}$), which the signed chart does not satisfy: $\sinh^{-1}(AB)-\sinh^{-1}A-\sinh^{-1}B$ reaches $1.49$ for positive test functions. A single chart cannot carry both the finiteness across zeros and the additivity of the relations. An atlas uses overlapping mathematical descriptions rather than forcing every quantity through one logarithmic chart.

## 41.5 The determining calibration

Specify a reproducible ratio-based Sz reference and compare independent sectors at matched physical states, preserving any residual state dimensions. A reference defined by a count of a declared oscillator (a recurring mechanism, Chapter 3) has an operational spacing; a reference defined by an equal numerical step does not.

## 41.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| (41.1) and the companion relations | Section 41.3 | DERIVED (exact), checked on test functions |
| invariance and spacing statements | Section 41.2 | DERIVED (exact) |
| chart statements | Section 41.4 | DERIVED (exact) and COMPUTED |
| test functions | as stated | CONSTRUCTION (no measured input) |

**Residuals.**

* **R41.1 — the physical coordinate.** No calibrated Sz reference with an operational spacing is specified here.
* **R41.2 — extra coordinates.** Polarisation, anisotropy, phase fractions and memory are not included in a single $S$.
* **R41.3 — charts.** Which overlapping charts an atlas should use across zeros and topology jumps is not specified.
* **R41.4 — measured ratios.** No measured ratio family is loaded; the compatibility relations are checked on generic functions only.

## 41.7 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch41_the_spaz_state_and_sz
```

Criteria were registered in `Textbook/validation/ch41_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch41_run1_output.txt`) is the run of record and met every criterion.

## 41.8 Exercises and answers

**Exercise 1.** Show that the log-derivative transforms by $1/f'$.

*Answer.* $d\ln Q/dS'=(d\ln Q/dS)(dS/dS')=a/f'(S)$.

**Exercise 2.** Derive $2a_k=a_r-a_{\rm Om}$.

*Answer.* $\ln k=\tfrac12(\ln r-\ln\mathrm{Om})$; differentiate with respect to $S$.

**Exercise 3.** Give two routes with the same $c=P_l/P_t$ and different $a_{P_l}$.

*Answer.* $P_l=e^{S},P_t=e^{S/2}$ and $P_l=e^{2S},P_t=e^{3S/2}$: $c=e^{S/2}$ for both.

**Exercise 4.** Why does $\sinh^{-1}$ not preserve the product relations?

*Answer.* $\sinh^{-1}(AB)\ne\sinh^{-1}A+\sinh^{-1}B$; only the logarithm turns products into sums.

**Exercise 5.** At how many of the 1000 sample points does $\ln\sin S$ fail on $[0.1,6.2]$?

*Answer.* Where $\sin S\le0$, on $S\in[\pi,2\pi]$ (about half of the interval): 501.

**Exercise 6.** Why is a law of constant rate per Sz mark not a physical law without calibration?

*Answer.* A reparameterisation $S\to S^2$ makes the rate vary; the constancy belongs to the chosen spacing.

## 41.9 Scope

Established: invariance of finite ratios and the transformation of derivatives under reparameterisation; the exact compatibility relations among log-derivatives; the constitutive freedom they leave; and the limits of the logarithmic chart.

Not established: a calibrated Sz reference (R41.1), the extra state coordinates (R41.2), the atlas of charts (R41.3) and any measured ratio family (R41.4).

*Where it leads.* Chapter 42 treats the relation structure exactly: rank, null space and invariants of a frozen inventory of quantities and relations.
