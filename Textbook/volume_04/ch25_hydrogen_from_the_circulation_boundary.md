# Chapter 25 — Hydrogen from the Circulation Boundary

*Volume IV — Atomic Recurrence, Spectra and Material Organisation.*
Draft of 10 November 2026. Notation: length $\mathrm{Om}=R/k^2$ (the engine's koppa), ratio $k=c/v$, depth $z=\mathrm{Om}/r$ as a defined geometric ratio only (author's ruling of 2026-11-03: $z$ is not $\varpi/r$ as a physical slowing). Executable companion: `Textbook/examples/ch25_hydrogen_from_the_circulation_boundary.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 25.1 The physical question

The hydrogen rung fixes a circulation speed, a route radius and a boundary length from one input. The chapter asks what follows from the rung alone (the ladder of admissible routes and their boundary length), what the engine's spectral scale adds, how a responding nucleus changes the line positions, and which statements are identities of the definitions and so cannot be evidence. No measured line is loaded here; the engine's own comparison with a line list is engine-recorded and not re-run.

## 25.2 The ladder and the boundary length

The rung is $k_{\rm H}=1/\alpha$ at $r=a_0$, giving $v_{\rm H}=c/k_{\rm H}=\alpha c$ and $\mathrm{Om}_{\rm H}=r/k_{\rm H}^2=\alpha^2a_0=r_e$. For the engine's ladder, $v_{Zn}=Z\alpha c/n$ and $r_{Zn}=n^2a_0/Z$ (Chapter 17), so

$$\mathrm{Om}_Z=\frac{v^2r}{c^2}=Z\,r_e,\qquad z=\frac{\mathrm{Om}}{r}=\Big(\frac{Z\alpha}{n}\Big)^2,\qquad k=\frac{n}{Z\alpha},\qquad zk^2=1. \tag{25.1}$$

The relation $zk^2=1$ is an identity of the definitions when $z$ and $k$ come from the same input; it becomes a test only if an independently measured depth and circulation speed are available, and none is loaded here. **Executed (T1).** Over the 50 states $Z=1\ldots5$, $n=1\ldots10$: $\mathrm{Om}_Z/(Zr_e)=1$ to $3.3\times10^{-16}$; $z=(Z\alpha/n)^2$ to $3.3\times10^{-16}$; $zk^2=1$ to $2.2\times10^{-16}$.

**A note on the rotation-field function.** The engine gives the circulation at radius $r$ as `atomic::rotation_field_velocity(r)` $=c\alpha\sqrt{a_0/r}$, which has no $Z$ argument. At the closed radii it equals $\alpha c/n$ for $Z=1$ to $10^{-16}$. For $Z>1$ it equals the ladder speed divided by $\sqrt Z$ (to $2.2\times10^{-16}$; at $Z=2$ the ratio is $0.707107$) and so differs from $Z\alpha c/n$ by at least 29% in every state. The ladder follows from $v^2r=c^2\,Zr_e$, which gives $v=c\alpha\sqrt{Za_0/r}$ for a nucleus of $Z$ units. This is recorded as a proposal to the author (residual R25.1); the function is correct as a hydrogen field, and the canon is not edited.

## 25.3 Three radii for the atom

A spectral recurrence radius, an effective boundary radius and a structural nuclear radius are different observables. Equating them globally can make a successful hydrogen reference misleading for another species. The engine warns that the spectroscopic source length need not equal the electromagnetic boundary $r_e$ in every derivation chain (Chapter 17 kept route, boundary and interaction lengths apart; Chapter 18 the lock radius).

## 25.4 The spectral scale

The engine rebuilds the Rydberg constant from the invariant inputs, $R_{\infty}^{\rm derived}=m_ec\alpha^2/(2h)$ (`atomic::R_inf_derived`), before a spectrum is consulted, and consumes it in `emission_wavelength_m`; other routines consume the stored energy $\mathrm{Ry}$. The two routes stay distinct in the equation ledger.

**Executed (T2).** $R_\infty^{\rm derived}/R_\infty=1$ to $1.1\times10^{-11}$ and $\mathrm{Ry}=hcR_\infty/e$ to $3.8\times10^{-14}$. Both are **shared-input**: the stored $R_\infty$ and $\mathrm{Ry}$ are computed from $\alpha$, $m_e$, $c$, $h$, so they test the consistency of the stored set and are not independent evidence for the rung. The two engine routes agree for hydrogen ($m_{\rm nuc}=m_p$): Lyman-$\alpha$ from `emission_wavelength_m` equals $hc/(E_2-E_1)$ from `level_energy_eV` to $1.1\times10^{-11}$, and Balmer-$\alpha$ likewise. The leading-order wavelengths are $121.568446$ nm and $656.469606$ nm (printed, not compared with a measured value), and their ratio is $5/27$ exactly (the combination principle).

## 25.5 The responding nucleus

The nucleus responds dynamically in the two-body construction; the factor is $\mu/m_e=m_{\rm nuc}/(m_e+m_{\rm nuc})$ (`reduced_mass_factor`), and $E_n=-\mathrm{Ry}\,(\mu/m_e)Z^2/n^2$. The infinite-nucleus approximation $\mu/m_e\approx1$ overstates the binding by $m_e/m_{\rm nuc}$ ($0.0545\%$ for hydrogen). Its error has a definite order: $\mu/m_e-(1-m_e/m_{\rm nuc})=(m_e/m_{\rm nuc})^2/(1+m_e/m_{\rm nuc})$, second order in the electron-to-nucleus ratio (T3, to $2\times10^{-9}$ of the second-order term).

**Isotope shifts from one nuclear response (T3).** Since $\lambda\propto1/\mu$, $\lambda_H/\lambda_D=\mu_D/\mu_H=1.000272099$ and $\lambda_D/\lambda_T=1.000090507$ (exact to $10^{-14}$). For Balmer-$\alpha$ the shifts are $\lambda_H-\lambda_D=0.17858$ nm (fractional $2.72\times10^{-4}$), $\lambda_H-\lambda_T=0.23797$ nm and $\lambda_D-\lambda_T=0.05939$ nm. For hydrogen-like helion ($Z=2$, $n=2\to3$) the wavelength is $164.057915$ nm with the helion mass against $164.028069$ nm for an infinite nucleus, a shift of $0.02985$ nm. These are predictions from the stored masses with no species-specific coefficient; their comparison with measured isotope shifts needs a sourced line list and is outstanding (residual R25.3).

## 25.6 What is omitted

The leading-order formula omits the next movement-budget term, of relative order $(Z\alpha/n)^2$: $53.25$ ppm for $Z=1$, $n=1$, and $47\,926$ ppm ($4.8\%$) for $Z=30$, $n=1$ (T4, reported). The engine records that hydrogen spectra agree within $12.5$ ppm and hydrogen-like ions with $Z\le30$ within $263$ ppm of a tabulated line list. At $Z=30$ the size of the omitted term is large compared with $263$ ppm, so that record must refer to a quantity that includes more than the leading-order formula or to a restricted set of transitions; the header does not say which. The reconciliation is outstanding until the line list is loaded (residual R25.2). This chapter makes no claim at the ppm level.

## 25.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $\alpha$, $a_0$, $m_e$, $m_p$, $m_d$, $m_t$, $m_h$, $h$, $c$ | `measured::` | MEASURED-INPUT |
| (25.1) | Section 25.2 | COMPUTED (identities of the definitions) |
| $R_\infty$, Ry | `measured::` | MEASURED-INPUT; shared-input with the set above |
| $R_\infty^{\rm derived}$, wavelengths, shifts | Sections 25.4–25.5 | COMPUTED |
| engine's 12.5 ppm and 263 ppm figures | engine header | engine-recorded; not re-run |

**Residuals.**

* **R25.1 — the rotation-field function.** No $Z$ argument; for $Z>1$ it is the ladder speed over $\sqrt Z$. Proposal: $c\alpha\sqrt{Za_0/r}$. Not applied.
* **R25.2 — the line list.** The engine's ppm figures are not reproduced; the size of the omitted term at large $Z$ is not reconciled with them.
* **R25.3 — isotope shifts.** The predicted shifts are not compared with measured shifts.
* **R25.4 — a native depth.** An independent spectroscopic depth and circulation speed, which would make $zk^2=1$ a test, are not available.
* **R25.5 — the stability of the ladder.** Persistence of each rung needs a restoring response (Chapter 17, R17.1); the identities above do not supply it.

## 25.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch25_hydrogen_from_the_circulation_boundary
```

Criteria were registered in `Textbook/validation/ch25_PRE_REGISTRATION.md` before the instrument existed. Run 1 failed one V1 line through double-precision cancellation ($1-\mu$ for a nucleus of $10^6m_p$ is resolved only to about $2\times10^{-7}$); the line was repaired with a lighter nucleus. Run 2 (`ch25_run2_output.txt`) is the run of record and met every criterion.

## 25.9 Exercises and answers

**Exercise 1.** Show $zk^2=1$ from the definitions.

*Answer.* $z=\mathrm{Om}/r=v^2/c^2$ and $k=c/v$, so $zk^2=1$.

**Exercise 2.** Derive the general rotation field for $Z$ units.

*Answer.* $v^2r=c^2Zr_e=c^2Z\alpha^2a_0$ gives $v=c\alpha\sqrt{Za_0/r}$; at $r=n^2a_0/Z$ this is $Z\alpha c/n$.

**Exercise 3.** Show the Lyman-$\alpha$ to Balmer-$\alpha$ wavelength ratio is $5/27$.

*Answer.* $1/\lambda_{L}=R\cdot\tfrac34$ and $1/\lambda_B=R\cdot\tfrac5{36}$, so $\lambda_L/\lambda_B=(5/36)/(3/4)=5/27$.

**Exercise 4.** Estimate the fractional H–D shift.

*Answer.* $\mu_D/\mu_H-1\approx(m_e/m_p-m_e/m_d)=m_e/m_p\,(1-m_p/m_d)\approx2.72\times10^{-4}$.

**Exercise 5.** Why is the infinite-nucleus error second order after the first-order correction?

*Answer.* $\mu/m_e=1/(1+x)=1-x+x^2-\ldots$ with $x=m_e/m_{\rm nuc}$.

**Exercise 6.** Why is $R_\infty^{\rm derived}/R_\infty=1$ not evidence for the rung?

*Answer.* The stored $R_\infty$ is itself computed from $\alpha$, $m_e$, $c$, $h$; the ratio checks the arithmetic of the set.

## 25.10 Scope

Established: the ladder identities and the boundary length $Zr_e$; the finding that the rotation-field function equals the ladder speed over $\sqrt Z$ for $Z>1$; the shared-input status of the Rydberg comparison; agreement of the two engine routes; the reduced-mass response, its second-order approximation error and the isotope shifts it predicts; and the size of the omitted term.

Not established: any line position at ppm level (R25.2), a comparison of isotope shifts with measurement (R25.3), an independent depth (R25.4) and the stability of each rung (R25.5).

*Where it leads.* Chapter 26 derives the discrete closure of the ladder and what a quantisation argument needs beyond integer counting.
