# Chapter 49 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch49_inertia_and_equivalence.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. Law IV inertial mass $m=P_{cf}V_{\rm disp}/c^2$ (`law_IV::mass_from_V_disp`, $P_{cf}=\Phi/(3\ell_P^3)$) and the equivalence of inertial and orbital response. Under a common external directional drive $D$ a body responds as $a_i=[g_i/m_i]D$ with effective coupling $g_i$ and inertial coefficient $m_i$; the dimensionless differential is $\eta=2(a_1-a_2)/(a_1+a_2)$. (a) Construction I: $g_i$ assigned from the same engaged-volume measure as $m_i$ ($g_i\propto V_{\rm disp,i}$) gives $\eta=0$ by construction: an implementation-consistency statement, not a physical test. (b) Construction II: the coupling tracks the sum of the constituent engaged volumes (free constituents) while the inertia is the total mass including the binding deficit: with $f=B/(Mc^2)$, $a_i/D\propto1+f_i$ and $\eta_{12}=2(f_1-f_2)/(2+f_1+f_2)$. The cancellation must survive binding: the coupling must track the total engaged volume to a relative accuracy $\eta_{\rm target}/f$ if the differential is to stay below a reference level $\eta_{\rm target}$ (the reference level $10^{-13}$ is a stated scale for this arithmetic, not a measured result loaded here). (c) A directional body has a tensor coupling $g=g_0(I+\delta\,\hat n\hat n^T)$ with an isotropic inertia: the orientation-averaged response along $D$ is $g_0(1+\delta/3)$; for $D$ at $45^\circ$ to the axis the acceleration is rotated from $D$ by $\approx-\delta/2$ and along a principal axis by $0$. (d) The engine's dynamics (`dynamics::accelerations`) takes the source strength of each body as a length $\varpi_j$ (`koppa_m`) and gives $a_i=c^2\sum_j\varpi_j\hat r_{ij}/r_{ij}^2$: the acceleration of a body does not depend on its own source strength (Construction I at the engine level), and `koppa_from_baryons` is additive in baryon count, so a nucleus and the same number of free baryons carry the same source strength while Law IV gives them different masses. Inputs: $\{c,m_e,m_p,m_n,m_d\}$ and the stored $B_\alpha=28.296$ MeV (`measured`; rounded, see Chapter 23) and $B_d$ (derived from the measured masses); the stored $\ell_P$ (carrying $G$, CALIBRATED (1)) enters $V_{\rm disp}$ through $\Phi$ and $P_{cf}$ and cancels from every ratio tested here.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | `mass_from_V_disp(V_disp_from_mass(m))=m` for $m_e,m_p,m_d$; $V_{\rm disp}$ is additive in mass; $mc^2=P_{cf}V_{\rm disp}$ with $P_{cf}=\Phi/(3\ell_P^3)$; $\int_0^1\mu^2d\mu=1/3$ by the instrument's quadrature | $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | engaged volume as inertia. $V_{\rm disp,p}/V_{\rm disp,e}=m_p/m_e=1836.15267343$ (CODATA ratio) and the exclusion-radius ratio equals $(m_p/m_e)^{1/3}$; the ratios do not change when $\ell_P$ is replaced by $2\ell_P$ in the formulas (computed with the same expression, $\Phi\propto N\epsilon$ held as the engine states it) — tested as: $V_{\rm disp}(m)\,P_{cf}/c^2$ returns $m$ for both $\ell_P$ values | $10^{-10}$ for the CODATA ratio; $10^{-12}$ otherwise | yes |
| T2 | Construction I and II. (I) $\eta=0$ to $10^{-15}$ for six masses ($m_e,m_p,m_n,m_d,m_t,m_\alpha$); (II) $f_d=B_d/(m_dc^2)$, $f_\alpha=B_\alpha/(m_\alpha c^2)$ with $m_\alpha=2m_p+2m_n-B_\alpha/c^2$: $\eta(\alpha,p)=2f_\alpha/(2+f_\alpha)\in[7.0,8.0]\times10^{-3}$, $\eta(d,p)\in[1.1,1.3]\times10^{-3}$; the required tracking accuracy for $\eta_{\rm target}=10^{-13}$ against the alpha is $\eta_{\rm target}/f_\alpha\in[1.0,2.0]\times10^{-11}$ | as stated | yes |
| T3 | tensor response. $\delta=10^{-3}$: orientation average of $\hat D\cdot g\hat D$ over $\mu=\cos\theta$ uniform equals $g_0(1+\delta/3)$ ($10^{-12}$); at $45^\circ$ the acceleration is rotated from $D$ by an angle within $\delta^2$ of $-\delta/2$; along a principal axis the rotation is $0$ ($10^{-15}$); the magnitude ratios along the two principal axes are $1+\delta$ and $1$ | as stated | yes |
| T4 | engine implementation. In `dynamics::accelerations` for a source of strength $\varpi_\odot$ (`bridge::koppa_Sun`) and a test body at $r=1$ AU the test body's acceleration equals $c^2\varpi_\odot/r^2$ to $10^{-14}$ for test source strengths $10^{-30},10^{-20},10^{-10}$ m (independent of its own strength); `koppa_from_baryons(A+B)=koppa_from_baryons(A)+koppa_from_baryons(B)` to $10^{-14}$; an alpha (4 baryons) and 4 free baryons have identical engine source strength, while the Law IV masses differ by $(4m_p-m_\alpha)/m_\alpha\in[0.6,0.8]\times10^{-2}$ | as stated | yes |

Reported, not criteria: $V_{\rm disp}$ and exclusion radii of the electron and proton; the values of $f$ and $\eta$ for $d$, $t$, helion and alpha; the angles.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch49_inertia_and_equivalence`
