# Chapter 49 — Inertia and Equivalence

*Volume VII — Correspondence, Paradoxes and Discriminating Tests.*
Draft of 10 November 2026. Notation: $V_{\rm disp}$ the exclusion volume of Law IV (Chapters 1 and 12; it is not the engaged volume $V_{\rm eng}$ of the relay lock); $P_{cf}=\Phi/(3\ell_P^3)$ the Law IV pressure coefficient; $g_i$ the effective coupling and $m_i$ the inertial coefficient of body $i$; $D$ a common external directional drive; $\eta=2(a_1-a_2)/(a_1+a_2)$; $f=B/(Mc^2)$ the binding fraction; $\varpi_j$ the source strength (a length, `koppa_m`) of body $j$. Executable companion: `Textbook/examples/ch49_inertia_and_equivalence.cpp`; pre-registration and captured output in `Textbook/validation/`. Inputs: $\{c,m_e,m_p,m_n,m_d\}$ and the stored $B_\alpha=28.296$ MeV (`measured`); $B_d$, $B_t$, $B_{\rm He3}$ derived there from the measured masses. The stored $\ell_P$ carries $G$ (CALIBRATED (1); $G$ enters at `laws.hpp:99`); it enters $V_{\rm disp}$ and cancels from every ratio below.

## 49.1 Shared displacement, distinct responses

Law IV assigns the low-speed inertial resistance $m=P_{cf}V_{\rm disp}/c^2$. Orbital acceleration uses the directional response of the same persistent structure to the ambient bath. Equality of the inertial and orbital response requires the coupling to track the same exclusion-volume measure across composition, orientation and state. For a body with effective coupling $g_i(X)$ and inertial coefficient $m_i(X)$ under a common drive, $a_i=[g_i/m_i]D$; composition independence needs $g_i/m_i$ common, and the cancellation has to survive binding, shielding and material-state changes.

**Executed (V1, T1).** The Law IV map was reproduced: $m\to V_{\rm disp}\to m$ for $m_e$, $m_p$, $m_d$ to $2\times10^{-16}$; $V_{\rm disp}$ is additive in mass; $mc^2=P_{cf}V_{\rm disp}$. The electron's exclusion volume is $9.980942\times10^{-62}$ m$^3$ (exclusion radius $2.877582\times10^{-21}$ m) and the proton's $1.832653\times10^{-58}$ m$^3$ ($3.523686\times10^{-20}$ m). Their ratio is $1836.152673422$, the CODATA mass ratio to $4.6\times10^{-12}$, and the exclusion-radius ratio is $(m_p/m_e)^{1/3}=12.24530$. Replacing $\ell_P$ by $2\ell_P$ in the forward and inverse expressions returns the same mass and the same volume ratio: the stored calibrated scale cancels from the content of equivalence statements, which concern ratios.

## 49.2 The differential test

For two bodies under matched drive, $\eta=2(a_1-a_2)/(a_1+a_2)$. If $g_i$ and $m_i$ are both assigned from the same measured coefficient, $\eta=0$ follows by construction and the test checks the implementation. A physical test needs an independent material response.

**Construction I (executed, T2).** $g_i\propto V_{\rm disp,i}$ with $m_i\propto V_{\rm disp,i}$: for all 15 pairs of $m_e,m_p,m_n,m_d,m_t,m_\alpha$ the worst $|\eta|$ is $6\times10^{-16}$ (the arithmetic floor). This is consistency of the code with its own definition.

**Construction II (executed, T2).** The coupling tracks the sum of the constituent exclusion volumes (free constituents) while the inertia is the total mass, including the binding deficit. Then $a_i/D\propto1+f_i$ and $\eta_{12}=2(f_1-f_2)/(2+f_1+f_2)$. With the binding fractions $f_d=1.186048\times10^{-3}$, $f_t=3.019592\times10^{-3}$, $f_{\rm He3}=2.748189\times10^{-3}$ and $f_\alpha=7.591393\times10^{-3}$ ($m_\alpha=2m_p+2m_n-B_\alpha/c^2=6.644657\times10^{-27}$ kg):

| pair | $\eta$ |
|---|---|
| $\alpha$, p | $7.5627\times10^{-3}$ |
| d, p | $1.1853\times10^{-3}$ |
| t, p | $3.0150\times10^{-3}$ |
| $\alpha$, d | $6.3774\times10^{-3}$ |

The cancellation must survive binding: if the differential is to stay below a reference level $\eta_{\rm target}=10^{-13}$ (a stated scale for this arithmetic, not a measurement loaded here), the coupling must track the total exclusion volume to a relative accuracy of $\eta_{\rm target}/f_\alpha=1.317\times10^{-11}$ against the alpha. Whether the coupling follows the total volume (including the deficit) or the constituent sum is a statement about the contact mechanism, and the two constructions differ at the per-cent level for light nuclei.

## 49.3 Rotating and anisotropic structures

A directional body can have a tensor response. Take $g=g_0(I+\delta\,\hat n\hat n^T)$ with an isotropic inertia. **Executed (T3), $\delta=10^{-3}$.** The orientation average of $\hat D\cdot g\hat D$ with the axis direction uniform over a sphere ($\mu=\cos\theta$ uniform) is $g_0(1+\delta/3)$ ($1.000333333$ to $7\times10^{-16}$): the scalar equivalence limit concerns the averaged state. For a drive at $45^\circ$ to the axis the acceleration is rotated from the drive by $-4.9975\times10^{-4}$ rad, within $\delta^2$ of $-\delta/2$; along a principal axis the rotation is exactly $0$ and the magnitude ratio of the two principal responses is $1+\delta$. Wake alignment, internal deformation and phase change are candidate differential probes; the predicted magnitude has to precede the experiment.

## 49.4 What the engine implements

**Executed (T4).** In `dynamics::accelerations` a body's acceleration is $c^2\sum_j\varpi_j\hat r_{ij}/r_{ij}^2$ over the other bodies: for a source of strength $\varpi_\odot$ and a test body at 1 AU the test body's acceleration equals $c^2\varpi_\odot/r^2$ exactly for test strengths $10^{-30},10^{-20},10^{-10}$ m (worst deviation $0$). The passive response is independent of the body's own strength (Construction I at the engine level). The source strength is `koppa_from_baryons`, additive in baryon count (verified to the floor), so an alpha and four free baryons carry identical engine source strengths. Law IV gives them different masses: against four free protons $(4m_p-m_\alpha)/m_\alpha=6.8974\times10^{-3}$ (the registered comparison); against the free constituents $2p+2n$ the difference is the binding fraction $f_\alpha=7.5914\times10^{-3}$. The engine counts a proton and a neutron alike (they differ in mass by $1.4\times10^{-3}$), so its convention differs from a mass-proportional source by the binding fraction and by the neutron–proton mass difference. Whether the source strength of a composite follows baryon count or total exclusion volume is a question the engine answers by definition and that a measurement of composite source strength could decide; no such limit was loaded here (R49.3).

## 49.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $c,m_e,m_p,m_n,m_d,m_t,m_{\rm He3}$ | `measured` | CODATA 2022 |
| $B_d,B_t,B_{\rm He3}$ | `measured` | derived from the measured masses |
| $B_\alpha=28.296$ MeV | `measured` | stored, rounded (computed in Chapter 23: $28.295616$) |
| $\Phi$, $P_{cf}$, $\ell_P$ | `law_I`, `law_IV` | stored; $\ell_P$ carries $G$: CALIBRATED (1); cancels from ratios |
| $V_{\rm disp}$ ratios, $f$, $\eta$ | Sections 49.1–49.2 | COMPUTED |
| Constructions I, II; tensor $g$ | Sections 49.2–49.3 | CONSTRUCTION (no measured input) |
| $\eta_{\rm target}=10^{-13}$ | Section 49.2 | reference scale for arithmetic |

**Residuals.**

* **R49.1 — the coupling.** No coupling $g_i$ is calculated for any composition: whether orbital response tracks the total exclusion volume (Construction I) or the constituent sum (II) is not derived.
* **R49.2 — independent materials.** The exclusion-volume and directional-coupling response for several independently constructed materials is not computed (`materials.hpp` was not used).
* **R49.3 — source strength.** The baryon-count convention of `koppa_from_baryons` against total exclusion volume (a $0.69$ per cent difference for the alpha) is not tested against any measured composite source strength.
* **R49.4 — shielding and state.** Binding, shielding and phase changes were treated through the binding fraction only.
* **R49.5 — the tensor.** The tensor $g$ and its axis dynamics for a rotating body are stand-ins.
* **R49.6 — stored alpha binding (proposal to the author, canon untouched).** `B_alpha` is rounded to five digits; the computed value from measured masses is available.

## 49.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch49_inertia_and_equivalence
```

Criteria were registered in `Textbook/validation/ch49_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch49_run1_output.txt`) met every criterion and is the run of record.

## 49.7 Exercises and answers

**Exercise 1.** Show $V_{\rm disp,p}/V_{\rm disp,e}=m_p/m_e$.

*Answer.* $V_{\rm disp}=3m\ell_P^3c^2/\Phi$ is linear in $m$ with a common coefficient, so the ratio is the mass ratio.

**Exercise 2.** What is $\eta$ for Construction II with $f_1=0.01$, $f_2=0$?

*Answer.* $2(0.01)/(2+0.01)=9.95\times10^{-3}$.

**Exercise 3.** How accurately must the coupling track the total volume of a body with $f=7.6\times10^{-3}$ for $\eta<10^{-13}$?

*Answer.* $10^{-13}/7.6\times10^{-3}=1.3\times10^{-11}$.

**Exercise 4.** Show the orientation average $\langle\mu^2\rangle=1/3$ and its role.

*Answer.* $\int_0^1\mu^2d\mu=1/3$; the averaged tensor coupling is $g_0(1+\delta/3)$ because $\langle\hat n\hat n^T\rangle=I/3$.

**Exercise 5.** Why does a test body's acceleration in the engine not depend on its own strength?

*Answer.* $a_i$ sums $c^2\varpi_j\hat r_{ij}/r_{ij}^2$ over the other bodies $j$; $\varpi_i$ appears only in the accelerations of the others.

**Exercise 6.** Compute the mass difference between an alpha and four free protons as a fraction of the alpha mass.

*Answer.* $4m_p-m_\alpha=B_\alpha/c^2-2(m_n-m_p)=28.296-2.587=25.709$ MeV$/c^2$; divided by $m_\alpha=3727.38$ MeV$/c^2$ this is $6.897\times10^{-3}$.

## 49.8 Scope

Established: the Law IV map and the cancellation of the stored $\ell_P$ from ratios; $\eta=0$ for Construction I by construction; the per-cent size of $\eta$ for Construction II and the tracking accuracy it implies; the tensor response and its orientation average; that the engine's test-body acceleration is independent of its own strength and its source strength additive in baryon count.

Not established: a calculated coupling for any composition (R49.1), independent material responses (R49.2), the composite source strength against measurement (R49.3).

*Where it leads.* Chapter 50 treats interference and detection: what a detector registers when a disturbance propagates through two apertures.
