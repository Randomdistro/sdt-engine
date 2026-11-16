# Chapter 38 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch38_galactic_environments.cpp` was written or run, and before any baryon-only disc curve was computed.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The geometry of an extended source and what a flat rotation curve does and does not constrain. The engine's Milky Way preset (`galactic::milky_way`) stores a 28-point rotation-curve table (OBSERVED, compiled by the engine from named literature sources; processed), a baryonic mass $M_{\rm bar}=5.17\times10^{10}M_\odot$ and a disc scale length $h_R=2.6$ kpc; its source length is $\varpi_{\rm bar}=M_{\rm bar}\,\varpi_\odot$ with `bridge::koppa_Sun`. (a) The source length implied by the observed speed, $\mathrm{Om}_{\rm eff}(r)=v^2r/c^2$ (`milky_way::koppa_at`): its growth with $r$ and its ratio to $\varpi_{\rm bar}$; the reconstruction of $v$ from $\mathrm{Om}_{\rm eff}$ is vacuous (identically exact for any curve), so it is a construction display, not a prediction; (b) extended-source geometry: an exponential thin disc under the inverse-square occlusion kernel of Chapter 15 has circular speed $v^2=(2c^2\varpi_d/h_R)\,y^2[I_0(y)K_0(y)-I_1(y)K_1(y)]$ with $y=R/2h_R$, which tends to the spherical enclosed-source value $c^2\varpi_d/R$ at large $R$ and exceeds the scalar enclosed-source value $c^2\varpi_{\rm enc}(R)/R$ by up to about a factor 2 near $R\approx2.2h_R$; (c) a **baryon-only** exponential disc carrying all of $\varpi_{\rm bar}$ with $h_R=2.6$ kpc and no enhancement of any kind, compared with the stored rotation table: the prediction fixed here before computing is that its speed at 8.178 kpc is 0.7 to 0.9 of the observed 229 km/s, that its speed at 25 kpc is below 0.6 of the observed 185 km/s, and that it declines beyond its maximum (near $2.15h_R=5.6$ kpc) while the observed curve is flat. The disc is a CONSTRUCTION (bulge, gas and arms not separated); the comparison tests the extended-source geometry, not any enhancement law. The engine's twin-regime enhancement exponents are fitted inputs and are not used.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | Bessel functions by the integral representations ($I_\nu(x)=\frac1\pi\int_0^\pi e^{x\cos\theta}\cos\nu\theta\,d\theta$, $K_\nu(x)=\int_0^\infty e^{-x\cosh t}\cosh\nu t\,dt$): $I_0(1)=1.2660658777$, $K_0(1)=0.4210244382$, $I_1(1)=0.5651591040$, $K_1(1)=0.6019072302$; the Wronskian $I_0K_1+I_1K_0=1/x$ at $x=0.3,1,4,10$; the disc formula tends to the spherical limit: $v^2R/(c^2\varpi_d)\to1$ at $R=200h_R$ | $10^{-9}$ (values), $10^{-12}$ (Wronskian), $10^{-4}$ (limit) |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | from the stored table: $\mathrm{Om}_{\rm eff}$ at 28 radii; the least-squares slope of $\ln\mathrm{Om}_{\rm eff}$ against $\ln r$ over the points between 5 and 14 kpc lies in $[0.9,1.1]$ (flatness); $\mathrm{Om}_{\rm eff}(8.178\ \mathrm{kpc})/\varpi_{\rm bar}$ is printed | slope in $[0.9,1.1]$ | yes |
| T2 | vacuity. $v_{\rm pred}=c\sqrt{\mathrm{Om}_{\rm eff}/r}$ reproduces the table and 200 random curves to $10^{-14}$ relative; `milky_way::zk2_at` equals 1 to $10^{-14}$ at 100 radii | as stated | yes — a residual above round-off would show the reconstruction is not an identity |
| T3 | extended geometry. $v_{\rm disc}^2/v_{\rm sph}^2$ with $v_{\rm sph}^2=c^2\varpi_d\,m(R)/R$, $m(R)=1-e^{-R/h_R}(1+R/h_R)$, over $R/h_R\in[0.1,30]$: the maximum lies between 1.9 and 2.3 at $R/h_R$ between 1.5 and 3.0; at $R=20h_R$ the ratio is within 2% of 1. Printed at $R/h_R=0.5,1,2.2,5,10,20$ | as stated | yes |
| T4 | baryon-only disc against the stored rotation curve at 5, 8.178, 11, 16, 25 kpc (linear interpolation of the table): the registered statements (c) above: $v_{\rm disc}(8.178)/229\in[0.7,0.9]$; $v_{\rm disc}(25)/185<0.6$; $v_{\rm disc}(25)<v_{\rm disc}(8.178)$. Ratios printed at all five radii | as stated; a miss is a finding | yes — a ratio near 1 at 25 kpc would reject the claim that a baryon-only extended source needs an additional response |

Reported, not criteria: all $\mathrm{Om}_{\rm eff}$ values, the ratios, the disc curve.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch38_galactic_environments`

## Record of run 1 (2026-11-10)

Run 1 (`ch38_run1_output.txt`) met the Bessel and Wronskian checks of V1, T1 (slope $0.9861$), T2 (reconstruction identity to $2.2\times10^{-16}$), the $20h_R$ clause of T3 and all three clauses of T4 (ratios $0.795$, $0.756$, $0.676$, $0.583$, $0.526$ at 5, 8.178, 11, 16, 25 kpc; the registered statements held). It failed two clauses.

1. **V1, spherical limit: registration error.** The disc speed squared times $R$ tends to the spherical value with the known leading correction $1+9/(8y^2)$ ($y=R/2h_R=100$ at $R=200h_R$), i.e. $1.000125$; the instrument returned $1.0001126$, within $2\times10^{-7}$ of that, and the registered tolerance $10^{-4}$ did not allow for the correction. The known answer is corrected to $1+9/(8y^2)$ with tolerance $10^{-6}$. This is an error in the registration of an instrument check, not a finding on the object.
2. **T3, maximum of the disc-to-scalar ratio: registered prediction rejected, kept.** The registered statement that the ratio $v_{\rm disc}^2/v_{\rm sph}^2$ has a maximum between $1.9$ and $2.3$ near $R=2.2h_R$ is **rejected**: the computed maximum is $1.3452$ at $R/h_R=2.89$ (values $0.7578$, $1.0519$, $1.3188$, $1.2474$, $1.0589$, $1.0118$ at $R/h_R=0.5,1,2.2,5,10,20$). The registered figure came from a recalled coefficient of the Freeman peak that was wrong ($v^2_{\max}\approx0.387\,GM/h_R$ by direct evaluation at $y=1.1$, not $0.62\,GM/h_R$); it was never checked against a computation. The formula's normalisation is confirmed by the Wronskian, the Bessel values and the spherical limit. The criterion is not retuned: run 2 keeps the clause and reports its rejection, and the corrected maximum is recorded as the result. Run 2 is the run of record.
