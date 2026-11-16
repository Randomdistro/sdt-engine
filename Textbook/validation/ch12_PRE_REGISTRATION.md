# Chapter 12 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch12_displacement_and_resistance.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. Law IV as derived in `Laws/SDT_Complete_Laws.md` (Section "Law IV", Theorem 5) and implemented in `law_IV` of `laws.hpp`: the momentum of the content within the exclusion volume under a first-order dipole (Complete Laws Eq. 3.1, $\phi'=(\Phi/4\pi)(1+\vec v\cdot\hat n/c)$), the resulting $m=\Phi V_{\rm disp}/(3\ell_P^3c^2)$, the stated aberration form of Corollary 7.1, $\phi'\propto(1-\beta\cos\theta)^{-2}$, the engaged and wake volumes of the relay lock, the convergence floor, and the mass defect read as a reduction of exclusion volume. The derivation's premise that the content in the exclusion volume carries momentum equal to its density over $c$ is P7 of Chapter 9 (residual R9.1).

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | angular integrals by the instrument's quadrature: $\oint d\Omega=4\pi$; $\oint\hat n\,d\Omega=0$; $\oint(\vec v\cdot\hat n)\hat n\,d\Omega=(4\pi/3)\vec v$ (component along $\vec v$ for $v=1$) | $10^{-13}$ relative (absolute for the zero) |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | the momentum $p=(V/\ell_P^3c)(\Phi/4\pi)\oint(1+\vec v\cdot\hat n/c)\hat n\,d\Omega$ by quadrature, for $V=V_{\rm disp,p}$ and $v=1$ m/s, equals $m_pv$ with $m_p$ from the engine's `mass_from_V_disp(V_disp_p)`; the same with $V_{\rm disp,e}$ and $m_e$ | within $10^{-12}$ relative | yes — a missing factor 3 or an extra $4\pi$ rejects |
| T2 | the dipole of the two forms. For $\phi'=(1+\beta\mu)$ (Eq. 3.1) the normalised dipole $D(\beta)=\oint\phi'\mu\,d\Omega/\oint\phi'\,d\Omega$ obeys $D/\beta\to1/3$; for $\phi'=(1-\beta\mu)^{-2}$ (Corollary 7.1) $D/\beta\to2/3$ as $\beta\to0$. The two statements in the source therefore differ by a factor 2 in the first-order dipole | $D/\beta$ at $\beta=10^{-4}$ within $10^{-3}$ of $1/3$ and of $2/3$ respectively | yes — equal coefficients would reject the registered discrepancy |
| T3 | the Corollary 7.1 distribution used as in the derivation of Theorem 5. Define $r(\beta)=3I_1(\beta)/(2\beta)$ with $I_1=\int_{-1}^{1}\mu(1-\beta\mu)^{-2}d\mu$ (the momentum under Corollary 7.1 over the momentum under Eq. 3.1); then $r(\beta\to0)=2$, and $r(\beta)/2$ is not the Lorentz factor: at $\beta=0.5$ it differs from $\gamma$ by more than 5% | $\lvert r(10^{-3})-2\rvert<10^{-5}$; $\lvert r(0.5)/(2\gamma)-1\rvert>0.05$; closed form $I_1=\beta^{-2}[2\beta/(1-\beta^2)-\ln((1+\beta)/(1-\beta))]$ within $10^{-12}$ of quadrature | yes — $r/2=\gamma$ would reject |
| T4 | relay-lock volumes. $4\pi\int_0^br^2\sqrt{r/b}\,dr=8\pi b^3/7$ by quadrature equals `locked_engaged_volume_sphere(b)`; the wake complement $4\pi b^3/21$ equals `wake_volume_sphere(b)`; their sum is $\tfrac{4\pi}{3}b^3$ with fractions $6/7$ and $1/7$ | within $10^{-12}$ relative | yes |
| T5 | convergence floor. $\rho_{\rm eng}=(P_{\rm conv}/3)V_{\rm eng}/(Vc^2)=2P_{\rm conv}/(7c^2)$ (engine `average_resistance_density`); $a_{\rm floor}=|\nabla P|/\rho_{\rm eng}=7c^2/(6R_{\rm CMB})$ (engine `acceleration`, `cosmological_acceleration`) | within $10^{-12}$ relative | yes |
| T6 | binding as reduced exclusion volume (CONSTRUCTION: both sides share the measured masses). For the deuteron, triton and helion the engine's `synchrony_resistance_delta(V_joint, V_p+V_n...)` with $V=V_{\rm disp}$ of each mass, equals $-B$ in joules ($B$ = `B_deuteron` etc. times `MeV_to_J`); the fractional volume reduction equals $B/(Mc^2)$ | within $10^{-9}$ relative | yes |

Reported, not criteria: the sensitivity of $V_{\rm disp,p}$ and $R_{\rm excl,p}$ to the numerical factor of Law IV (3 against 6, residual R9.4); the value of the floor acceleration.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch12_displacement_and_resistance`

## Record of run 1 and repair of T1 (2026-11-09)

Run 1 (`ch12_run1_output.txt`) met every criterion except T1, where $p/(mv)=1.0000002058$ for both exclusion volumes instead of $1\pm10^{-12}$. The registered speed was $v=1$ m/s. At that speed the dipole term of the integrand is $v/c=3.3\times10^{-9}$ of the monopole term, which integrates to zero; the quadrature's rounding in the cancelling monopole sum (about $10^{-16}$ per term over several hundred terms) is then a relative $10^{-7}$ of the dipole result. This is an instrument-conditioning fault in the registered test conditions and not a property of the engine. The criterion is unchanged and the test condition is repaired: the integrand is exactly linear in $v$ (the monopole vanishes by V1, the dipole is proportional to $v$), so $p/(mv)$ does not depend on $v$, and the test is run at $v=0.01\,c$, where the dipole is $10^{-2}$ of the monopole and the rounding is $10^{-14}$ of the result. All other tests of run 1 met their criteria. Run 2 is the run of record.
