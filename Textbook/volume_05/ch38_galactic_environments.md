# Chapter 38 — Galactic Environments

*Volume V — Bodies, Fields and Propagation.*
Draft of 10 November 2026. Notation: $\mathrm{Om}_{\rm eff}(r)=v^2r/c^2$ is the source length implied by an observed circular speed; $\varpi_{\rm bar}=M_{\rm bar}\varpi_\odot$ is the engine's total baryonic source length ($M_{\rm bar}=5.17\times10^{10}M_\odot$ in `galactic::milky_way`, $\varpi_\odot=$ `bridge::koppa_Sun`); $h_R$ is a disc scale length. Executable companion: `Textbook/examples/ch38_galactic_environments.cpp`; pre-registration and captured output in `Textbook/validation/`. The rotation table is OBSERVED, compiled by the engine from named literature sources and used as stored; it was not re-derived here. The engine's enhancement exponents are fitted inputs and are not used.

## 38.1 Geometry beyond a point source

A galactic environment includes a bulge, a disc, a bar, arms and an external directional bath. For an extended source one integrates the directional response over the actual construction and the transport paths; a scalar enclosed-source approximation is justified only under the symmetry and response assumptions that produce that reduction. The engine's galactic header describes bulge and disc regimes with different geometry, midplane response and transition scales. Its descriptive comments and its explicit numerical forms carry different evidential roles, and an exponent or transition radius inherited from a fitted investigation remains a fitted input until a native response derivation removes that freedom.

**Extended-source geometry, executed.** An exponential thin disc, surface density $\Sigma_0e^{-r/h_R}$ and total source length $\varpi_d$, under the inverse-square occlusion kernel of Chapter 15 (each element contributing $c^2\,d\varpi/r^2$) has the circular speed

$$v^2(R)=\frac{2c^2\varpi_d}{h_R}\,y^2\big[I_0(y)K_0(y)-I_1(y)K_1(y)\big],\qquad y=\frac R{2h_R}, \tag{38.1}$$

which tends to the spherical value $c^2\varpi_d/R$ at large $R$. The Bessel functions were evaluated by their integral representations and checked (V1): $I_0(1)=1.2660658777$, $K_0(1)=0.4210244382$, $I_1(1)=0.5651591040$, $K_1(1)=0.6019072302$ (to $10^{-10}$), the Wronskian $I_0K_1+I_1K_0=1/x$ to $4\times10^{-16}$, and the limit $v^2R/(c^2\varpi_d)=1+9/(8y^2)$ at $R=200h_R$ to $5\times10^{-8}$ (the registered tolerance did not allow for the known correction and was repaired, as recorded in the pre-registration).

**Disc against the scalar enclosed source (T3).** The scalar approximation replaces the disc by the source length enclosed within $R$, $v_{\rm sph}^2=c^2\varpi_d\,m(R)/R$ with $m(R)=1-e^{-R/h_R}(1+R/h_R)$. The ratio $v_{\rm disc}^2/v_{\rm sph}^2$ is $0.758$, $1.052$, $1.319$, $1.247$, $1.059$, $1.012$ at $R/h_R=0.5,1,2.2,5,10,20$, with its maximum $1.345$ at $R/h_R=2.89$. The scalar reduction understates the disc's speed squared by up to a third, and by less than 2% beyond $20h_R$. **A registered prediction that failed:** the pre-registration stated that the ratio reaches about $2$ (between $1.9$ and $2.3$) near $2.2h_R$. That figure came from a recalled coefficient of the Freeman peak and was wrong ($v_{\max}^2\approx0.387\,c^2\varpi_d/h_R$ by direct evaluation); the registered statement is rejected, the criterion was not retuned, and the computed maximum is the result.

## 38.2 What a flat curve constrains

If the circular speed remains nearly constant over a radial interval, the effective source length $\mathrm{Om}_{\rm eff}(r)=v^2r/c^2$ grows approximately linearly with $r$ at fixed $c$. This inference describes the response required by the observed curve; it does not say whether source geometry, directional convergence or relay response supplies it.

**Executed (T1).** From the engine's rotation table: $\mathrm{Om}_{\rm eff}$ is $2.47\times10^{11}$ m at 5.25 pc (370 km/s), $1.35\times10^{12}$ m at 200 pc, $1.51\times10^{13}$ m at 1 kpc, $5.69\times10^{13}$ m at 3 kpc, $8.92\times10^{13}$ m at 5 kpc, $1.63\times10^{14}$ m at 9 kpc, $2.43\times10^{14}$ m at 14 kpc and $2.94\times10^{14}$ m at 25 kpc. The least-squares slope of $\ln\mathrm{Om}_{\rm eff}$ against $\ln r$ over the nine points between 5 and 14 kpc is $0.986$ (flatness, registered window $[0.9,1.1]$). Relative to the total baryonic source length $\varpi_{\rm bar}=7.636\times10^{13}$ m, $\mathrm{Om}_{\rm eff}/\varpi_{\rm bar}$ is $0.745$ at 3 kpc, $1.169$ at 5 kpc, $1.931$ at the Sun's radius (8.178 kpc), $3.19$ at 14 kpc and $3.85$ at 25 kpc. Beyond about 4.5 kpc the source length required by the observed speed exceeds the whole baryonic source length of the stored mass.

**Reconstruction is not prediction.** Reconstructing $\mathrm{Om}_{\rm eff}$ from each observed speed and then reproducing that speed is an identity. **Executed (T2).** $v_{\rm pred}=c\sqrt{\mathrm{Om}_{\rm eff}/r}$ equalled $v$ to $2.2\times10^{-16}$ for the 28 table points and for 200 random curves alike, and the engine's closure identity $zk^2=1$ (`milky_way::zk2_at`) held to $4.4\times10^{-16}$ at 100 radii. Such a reconstruction is useful for mapping, and it is a construction display. A native calculation must predict the angular transport and the resulting acceleration from an independently specified baryonic geometry.

## 38.3 A baryon-only extended source, executed

The extended-source geometry gives a definite prediction for a baryon-only source. Take all of $\varpi_{\rm bar}$ in an exponential disc with $h_R=2.6$ kpc (the engine's disc scale length; a CONSTRUCTION, bulge, gas and arms not separated) and the unmodified inverse-square occlusion kernel, with no enhancement of any kind. The registered statements, fixed before the computation: the speed at 8.178 kpc is 0.7 to 0.9 of the observed 229 km/s; the speed at 25 kpc is below 0.6 of the observed 185 km/s; and the curve declines beyond its maximum near $2.15h_R=5.6$ kpc. **Executed (T4).**

| radius (kpc) | $v_{\rm disc}$ (km/s) | $v_{\rm obs}$ (km/s) | ratio |
|---|---|---|---|
| 5.0 | 181.2 | 228.0 | 0.795 |
| 8.178 | 173.2 | 229.2 | 0.756 |
| 11.0 | 155.6 | 230.0 | 0.676 |
| 16.0 | 127.0 | 218.0 | 0.583 |
| 25.0 | 97.3 | 185.0 | 0.526 |

Table 38.1. Baryon-only exponential disc against the stored rotation table, executed (T4).

All three registered statements held. The baryon-only curve falls with radius while the observed curve is flat, and at the outer edge it is about half the observed speed. The outer value is the robust one: beyond the extent of the sources, the speed squared tends to $c^2\varpi_{\rm bar}/R$ for any bounded distribution of the same total, which at 25 kpc is $94$ km/s whatever the inner geometry. The deficit is thus a property of the total source length and of the inverse-square kernel, not of the disc model. It can be removed only if the source length effective at large radius is larger by a factor of about $3.8$ ($\mathrm{Om}_{\rm eff}/\varpi_{\rm bar}$ at 25 kpc) or the kernel's response differs. Which of these holds is the question the framework has to answer; the engine's twin-regime modules attempt it with fitted exponents and transition radii (a spheroid enhancement exponent $0.3$, a bulge half-mass radius, a bar length and others), which remain fitted inputs. A proposed mechanism in which the pressure lowers the electromagnetic handoff is held as unregistered and is not tested here (residual R38.5).

## 38.4 Cross-scale consistency

The same response law should cover vertical disc confinement, radial rotation and propagation effects. A midplane enhancement tuned solely to a rotation curve may predict incorrect lensing or off-plane motion. The open-problems ledger retains the earlier negative galactic routes (for example the three-dimensional eclipse model that failed on real data after succeeding on a circular mock) and does not treat later descriptive models as closure. The determining test: freeze the source geometry and the transport law on one galaxy family, then predict a different orientation or radial range without altering the enhancement rule.

## 38.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| rotation table (28 points) | `milky_way::rc_table` | OBSERVED (compiled by the engine from named sources; used as stored) |
| $M_{\rm bar}$, $h_R$ | `milky_way` | the engine's canonical parameters (OBSERVED/CONSTRUCTION) |
| $\varpi_{\rm bar}=M_{\rm bar}\varpi_\odot$ | $7.636328\times10^{13}$ m | COMPUTED |
| (38.1), Table 38.1, T3 ratios | Sections 38.1, 38.3 | DERIVED (exact formula) and COMPUTED |
| twin-regime exponents and radii | `galactic.hpp` | CALIBRATED (fitted inputs; not used) |

**Residuals.**

* **R38.1 — the response.** What supplies the source length required at large radius (geometry, directional convergence or relay response) is not determined; the flat curve only constrains it.
* **R38.2 — baryon geometry.** The bulge, gas and arms are not separated; $M_{\rm bar}$ is the engine's stored value and was not re-derived.
* **R38.3 — fitted inputs.** The enhancement exponents and transition scales of the engine's twin regimes are fitted; they are not a native response.
* **R38.4 — consistency.** Vertical structure, lensing and propagation under the same law were not tested.
* **R38.5 — the proposed mechanism.** A pressure-dependent handoff mechanism is unregistered; no prediction is made.
* **R38.6 — the table.** The sources of the rotation points (several surveys and cluster orbits) were not re-examined.

## 38.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch38_galactic_environments
```

Criteria were registered in `Textbook/validation/ch38_PRE_REGISTRATION.md` before the instrument existed and before any baryon-only curve was computed. Run 1 met T1, T2 and T4 and failed two clauses: the spherical-limit check of V1 (a registration error: the known correction $9/(8y^2)$ was not allowed for) and the registered maximum of the disc-to-scalar ratio of T3 (a prediction from a wrong recalled coefficient: rejected and kept). Run 2 (`ch38_run2_output.txt`) is the run of record and met every criterion as recorded.

## 38.7 Exercises and answers

**Exercise 1.** Show that (38.1) tends to the spherical value.

*Answer.* For large $y$, $I_0K_0\approx\frac1{2y}(1+\frac1{8y^2})$ and $I_1K_1\approx\frac1{2y}(1-\frac3{8y^2})$, so $I_0K_0-I_1K_1\approx\frac1{4y^3}$ and $v^2\approx\frac{2c^2\varpi_d}{h_R}\frac1{4y}=\frac{c^2\varpi_d}{2yh_R}=\frac{c^2\varpi_d}{R}$.

**Exercise 2.** Compute $\mathrm{Om}_{\rm eff}$ at 8.178 kpc for $v=229$ km/s.

*Answer.* $v^2r/c^2=(2.29\times10^5)^2(8.178\times3.0857\times10^{19})/(2.998\times10^8)^2=1.47\times10^{14}$ m, $1.93\,\varpi_{\rm bar}$.

**Exercise 3.** What speed does any bounded distribution of total $\varpi_{\rm bar}$ give at 25 kpc?

*Answer.* $c\sqrt{\varpi_{\rm bar}/R}=2.998\times10^8\sqrt{7.636\times10^{13}/7.714\times10^{20}}=94.3$ km/s.

**Exercise 4.** Why is the reconstruction of $v$ from $\mathrm{Om}_{\rm eff}$ not a test?

*Answer.* $\mathrm{Om}_{\rm eff}$ is defined as $v^2r/c^2$; inverting it returns $v$ exactly.

**Exercise 5.** What does the maximum $1.345$ of $v_{\rm disc}^2/v_{\rm sph}^2$ mean for the scalar reduction?

*Answer.* The enclosed-source approximation understates the disc's circular speed squared by up to about a third near $R\approx2.9h_R$ and is accurate to 2% beyond $20h_R$.

**Exercise 6.** Why is a deficit at 25 kpc not a property of the disc model?

*Answer.* Beyond the sources the speed tends to $c\sqrt{\varpi_{\rm bar}/R}$ for any bounded distribution of the same total.

## 38.8 Scope

Established: the circular speed (38.1) of an exponential disc under the inverse-square kernel and its excess over the scalar enclosed-source value (up to $1.345$); that the source length implied by the stored rotation table grows nearly linearly with radius ($0.986$) and exceeds the stored baryonic total beyond about 4.5 kpc; that its reconstruction is an identity; and that a baryon-only disc with the unmodified kernel falls to $0.756$ of the observed speed at the Sun's radius and $0.526$ at 25 kpc, with an outer deficit independent of the geometry.

Not established: what supplies the missing response (R38.1), the baryon geometry (R38.2), a native replacement of the fitted exponents (R38.3), cross-scale consistency (R38.4) and the proposed handoff mechanism (R38.5).

*Where it leads.* Chapter 39 treats propagation: delay and bending along a path from one relay response.
