# Chapter 50 — Interference and Detection

*Volume VII — Correspondence, Paradoxes and Discriminating Tests.*
Draft of 10 November 2026. Notation: $A_j$ complex amplitudes (bookkeeping for a physical phase), $d$ aperture separation, $a$ aperture width, $L$ screen distance, $k=2\pi/\lambda$, $\sigma_k$ spectral width, $V$ visibility, $\mu$ mean registration count, $F=\mathrm{var}/\mathrm{mean}$ the Fano factor. Executable companion: `Textbook/examples/ch50_interference_and_detection.cpp`; pre-registration and captured output in `Textbook/validation/`. Every model in this chapter is a generic stand-in (TOY): no engine function and no measured input is used.

## 50.1 Two apertures, one propagated disturbance

A contact-medium disturbance can propagate through both open apertures and recombine at a detector. In the linear regime the complex amplitudes are a bookkeeping representation of physical phase, $A=A_1+A_2$. A quadratic detector response gives

$$|A|^2=|A_1|^2+|A_2|^2+2\,\mathrm{Re}(A_1A_2^*), \tag{50.1}$$

whose cross term predicts fringes while phase coherence survives. The notation is not a microscopic detector mechanism: a single localised registration needs the contact response of the detector, an energy transfer and an event rule (Section 50.4).

**Executed (V1, T1).** Identity (50.1) holds to the arithmetic floor for $A_1=1+2i$, $A_2=-0.5+0.25i$. For two point apertures at $\pm d/2$ with $d=1$ mm, $\lambda=500$ nm and $L=1$ m (exact path lengths), the maxima lie where $r_1-r_2=n\lambda$; at the exact positions $I=4$ to $4\times10^{-16}$. They differ from the small-angle $n\lambda L/d$ by $2.5\times10^{-7}$, $6.2\times10^{-7}$, $1.25\times10^{-6}$, $2.1\times10^{-6}$ and $3.25\times10^{-6}$ relative for $n=1\ldots5$ (the first maximum is at $5.000001249\times10^{-4}$ m). For amplitudes $1$ and $r=0.5$ the visibility from the scanned maximum and minimum is $0.8=2r/(1+r^2)$.

## 50.2 Geometry and coherence

For a path difference $\Delta\ell$ the phase difference is the integrated local propagation phase, not automatically $2\pi\Delta\ell/\lambda$ when the medium varies. Finite aperture, bandwidth, source coherence and detector resolution reduce the visibility, and the calculated observable has to integrate the apparatus response.

**Executed (T2).** For a Gaussian spectrum of width $\sigma_k=0.05k_0$ ($k_0=2\pi/500$ nm) the visibility at path difference $\Delta\ell$ is the modulus of $\int S(k)e^{ik\Delta\ell}dk$ over $\int S\,dk$: $0.820869$, $0.169225$ and $2.675\times10^{-9}$ at $1$, $3$ and $10\ \mu$m, equal to $\exp(-\sigma_k^2\Delta\ell^2/2)$ to $3\times10^{-15}$, $1.3\times10^{-14}$ and (absolute) $1.5\times10^{-15}$. The coherence length is about $1/\sigma_k=1.6\ \mu$m.

**Blocking an aperture (T3).** Blocking one aperture changes the boundary-value problem. Two slits of width $a=0.1$ mm at separation $d=1$ mm, $\lambda=500$ nm, $L=1$ m, window $\pm5$ mm, exact path lengths and numerical integration over each slit: the single-slit pattern is the envelope without fringes, and the two-slit pattern equals the sum of the two single-slit patterns plus the cross term (to $2.4\times10^{-15}$ in the window integral). The cross term integrates to $-3\times10^{-5}$ of the single-slit integral over the window, yet it redistributes the intensity locally: the total-variation distance between the normalised two-slit and single-slit patterns is $0.3222$ ($1/\pi=0.3183$, the value for many fringes under an envelope). A model that leaves the two-aperture pattern unchanged and deletes half the detector events does not reproduce the single-aperture pattern: the physical contact geometry has to be recomputed.

## 50.3 Detection as the endpoint of transfer

The detector contains persistent structures coupled to the same substrate. A deposited disturbance can trigger a localised response after extended propagation, and deriving that response needs thresholds, stored excitation and outgoing channels. Assigning the observed detection distribution as an input is a comparison rule, not a completed contact derivation. Two rules were compared on the same pattern.

**Rule 1, deterministic threshold (T4).** A cell accumulates stored excitation from its local intensity and fires when a threshold is reached, then resets. Over a fixed exposure the count is $n=\lfloor\mu+\varphi\rfloor$ with $\varphi$ the initial stored fraction (uniform), the variance is $\{\mu\}(1-\{\mu\})\le\tfrac14$ and the Fano factor is at most $1/(4\mu)$. Executed for $\mu=20.37$ over $2\times10^5$ random initial phases: mean $20.37073$, variance $0.23329$, $F=0.011452$ (predicted $0.011443$; the upper limit $1/(4\mu)$ is $0.012273$). The counts are far more regular than Poisson counts.

**Rule 2, sampling from the intensity (comparison rule).** Event positions drawn from the normalised pattern reproduce it by assumption: $2\times10^5$ events binned in 40 bins give $\chi^2/\mathrm{dof}=0.9249$ against the pattern. Counts drawn as Poisson variates with the same mean give $F=1.0023$ (mean $20.37092$, variance $20.41849$).

The two rules disagree in the counting statistics by a factor of about $87$ ($1.0023/0.011452$), and rule 2 contains its statistics as an assumption while rule 1 predicts them. A completed detector derivation has to supply a registration rule whose statistics are computed from the contact response (thresholds, noise sources, stored excitation, outgoing channels) and then compared with observed counts. The reference counting statistics of an ideal steady source is the Poisson one; it is the target of such a derivation and was not loaded here as data (R50.3).

## 50.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $\lambda$, $d$, $a$, $L$, $\sigma_k$, $\mu$ | Sections 50.1–50.3 | CONSTRUCTION (no measured input) |
| path lengths, amplitudes, patterns | Sections 50.1–50.3 | COMPUTED |
| random-number stream | seed $20261110$ | fixed for the run of record |

**Residuals.**

* **R50.1 — the propagation operator.** The amplitudes are those of a stand-in scalar propagation; the constitutional propagation operator and the phase in a varying medium were not used.
* **R50.2 — the aperture problem.** The patterns use exact path lengths and a uniform illumination of each slit, not a boundary-value solution of the contact medium with the apertures as boundaries.
* **R50.3 — the registration rule.** No detector response was derived from contact mechanics; the threshold rule is a stand-in, and the observed counting statistics and event statistics were not loaded.
* **R50.4 — energy and event rule.** Detection energy, stored excitation, outgoing channels and the energy export of a registration were not modelled.
* **R50.5 — joint variation.** A single model predicting fringe phase, visibility, detection energy and event statistics while aperture geometry and detector state are varied independently is not supplied.

## 50.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch50_interference_and_detection
```

Criteria were registered in `Textbook/validation/ch50_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch50_run1_output.txt`) met every criterion except one at the floor of the integral: the visibility at $10\ \mu$m is nine orders below the integrand scale, so the registered relative tolerance could not be met by any correct implementation (a registration error, recorded). Run 2 (`ch50_run2_output.txt`) is the run of record and met every criterion, with that point evaluated in absolute terms.

## 50.6 Exercises and answers

**Exercise 1.** Amplitudes $1$ and $0.25$: what is the visibility?

*Answer.* $2(0.25)/(1+0.0625)=0.4706$.

**Exercise 2.** At what path difference does the Gaussian-spectrum visibility fall to $1/2$ for $\sigma_k=6.283\times10^5$ m$^{-1}$?

*Answer.* $\exp(-\sigma_k^2\Delta\ell^2/2)=\tfrac12$ gives $\Delta\ell=\sqrt{2\ln2}/\sigma_k=1.1774/6.283\times10^5=1.87\ \mu$m.

**Exercise 3.** Find the fringe spacing for $d=1$ mm, $\lambda=500$ nm, $L=1$ m.

*Answer.* $\lambda L/d=0.5$ mm.

**Exercise 4.** Why is the total-variation distance about $1/\pi$ for many fringes?

*Answer.* The two-slit pattern is the envelope times $(1+\cos\psi)$; against the envelope alone the distance is $\tfrac12\langle|\cos\psi|\rangle=\tfrac12\cdot\tfrac2\pi=1/\pi$.

**Exercise 5.** What is the largest Fano factor of the threshold detector at $\mu=100$?

*Answer.* $1/(4\mu)=0.0025$.

**Exercise 6.** Why does blocking one aperture not merely halve the counts?

*Answer.* The boundary-value problem changes: the cross term in (50.1) disappears, so the intensity at every point changes by $2\mathrm{Re}(A_1A_2^*)$ and by the removed $|A_2|^2$, not by a uniform factor.

## 50.7 Scope

Established: the cross-term structure (50.1) and its maxima and visibility for stand-in propagation; the Gaussian-spectrum visibility; that blocking an aperture changes the pattern (distance $0.322$) while event deletion does not; that a deterministic threshold detector and Poisson sampling give counting statistics that differ by a factor of about $87$.

Not established: the propagation operator (R50.1), the contact boundary-value solution (R50.2), a detector response from contact mechanics (R50.3), detection energy and event rule (R50.4) and a joint prediction (R50.5).

*Where it leads.* Chapter 51 turns to measurement and enmeshment: joint statistics of separated systems and what a model must supply to predict them.
