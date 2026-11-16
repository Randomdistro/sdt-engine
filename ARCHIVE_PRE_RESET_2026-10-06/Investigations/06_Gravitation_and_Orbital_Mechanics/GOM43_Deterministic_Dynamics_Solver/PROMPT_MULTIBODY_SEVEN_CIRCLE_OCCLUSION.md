# GOM43-E — Multibody Seven-Circle Occlusion

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED · EXECUTION PENDING  
**Date:** 2026-08-18  
**Contract:** `sdtcase-3.0.0`

## Question

Can an arbitrary number of finite bodies be integrated by resolving every
ordered body pair into two seven-circle cross-sections, evaluating all
forty-nine target-channel/source-channel relations by retarded solid angle,
and applying Law-IV and Law-V resistance without using `G`, source mass,
softening or a force centre?

Contract 1.0 point-koppa dynamics remain a shared-input comparison. The
contract 2.x fixed-three-body instrument remains unchanged.

## Frozen body inputs

Every body supplies an exact positive decimal-string baryon count \(N_i\), a
physical radius \(R_i\), a non-negative collision radius, and inertial
Cartesian position and velocity. Optional proton/neutron displacement ledgers
must reconstruct the same baryon count.

The instrument reads, without alteration:

\[
c=\texttt{measured::c},\quad
\kappa_b=\texttt{bridge::koppa_per_baryon},\quad
V_b=\texttt{law_IV::V_disp_from_mass}(\texttt{measured::m_p}).
\]

No observed trajectory or residual is a coefficient.

## Exact seven-circle ledger

The pair-facing cross-section has one centre circle and six outer circles.
Every geometric circle has radius \(R_i/3\). Outer centres lie at \(2R_i/3\)
and phases \(0,\pi/3,\ldots,5\pi/3\).

\[
w_0=\frac19,\qquad w_{1\ldots6}=\frac4{27},\qquad
\sum_{a=0}^{6}w_a=1.
\]

Allocate integer baryons by largest remainder, with channel index as the
tie-break. The seven values must reconstruct \(N_i\) exactly. Effective outer
weights include their interstitial sectors; geometric circle area and baryon
weight are separate quantities.

## Ordered-pair frame and forty-nine relations

For target \(i\) at \(t\) and source \(j\) at its retarded epoch \(t_r\),

\[
\hat{\mathbf n}_{ij}=
\frac{\mathbf r_j(t_r)-\mathbf r_i(t)}
{|\mathbf r_j(t_r)-\mathbf r_i(t)|}.
\]

A deterministic orthonormal pair plane \((\mathbf e_1,\mathbf e_2)\) is built
from the Cartesian axis least aligned with \(\hat{\mathbf n}_{ij}\). The same
plane carries both seven-circle sections. Reversing an ordered pair reverses
the normal while preserving the physical plane.

For every \(a,b\in[0,6]\), evaluate target channel \(a\) against source channel
\(b\). The interaction count at every evaluated state is

\[
49N(N-1).
\]

## Retardation

The source body state satisfies

\[
t-t_r=
\frac{|\mathbf r_i(t)-\mathbf r_j(t_r)|}{c}.
\]

Solve by fixed-point iteration against deterministic history. Ballistic
prehistory is permitted only before the first stored epoch and is reported.
Retardation is solved once per ordered body pair; channel geometry is then
constructed from that retarded body state.

## Solid-angle instrument

For each source channel, calculate the apparent solid angle at each target
channel by deterministic area quadrature over the face-on source circle:

\[
\Omega_{ijab}=
\int_{A_{jb}}
\frac{\max(0,\hat{\mathbf n}_{A}\cdot\hat{\mathbf r})}
{|\mathbf r|^2}\,dA.
\]

The quadrature uses fixed radial and azimuthal nodes and no adaptive or
case-dependent refinement. Its analytic checks are:

\[
\Omega_{\rm axis}=2\pi\left(1-\frac{d}{\sqrt{d^2+q^2}}\right),
\qquad
\frac{\Omega}{\pi q^2}\rightarrow\frac1{d^2}.
\]

Here \(q=R_j/3\). The channel drive is

\[
\mathbf a^{(0)}_{ijab}=
\frac{N_{jb}\kappa_b c^2\Omega_{ijab}}{\pi q^2}
\hat{\mathbf r}_{ijab}.
\]

The target body averages its seven receiving channels by
\(N_{ia}/N_i\). Thus the far-field sum over all 49 relations recovers
\(c^2N_j\kappa_b/r^2\).

## Angular shielding union

An intervening channel may cover part of a source-channel quadrature domain.
At each fixed quadrature ray, only the nearest positive intersection is
counted. This is a deterministic angular union: coincident blocked rays are
never added twice. The unshielded fraction and covering body/channel are
reported. Shielding can reduce a pressure deficit but cannot create an
opposite contribution.

## Law-IV depth and resistance

For target channel \(a\), the engaged fraction is its weighted, unioned
hemispherical occlusion:

\[
D_{ia}=\sum_{\text{visible }j,b}
\frac{N_{ia}}{N_i}\frac{\Omega_{ijab}}{2\pi}.
\]

\[
D_i=\sum_aD_{ia},\qquad
V_{i,\mathrm{eff}}=V_{i,0}(1+D_i).
\]

The response divides by

\[
\rho_i=
\frac{\texttt{law_IV::mass_from_V_disp}(V_{i,\mathrm{eff}})}
{\texttt{law_IV::mass_from_V_disp}(V_{i,0})}.
\]

The same ratio applies to every signed velocity change, so increased
engagement resists starting and stopping by the same rule.

## Law-V c boundary

Let \(\mathbf a\) be the Law-IV response and decompose it parallel and
perpendicular to the current velocity. With
\(\gamma=\texttt{law_V::gamma}(|\mathbf v|)\),

\[
\mathbf a_{\rm applied}=
\frac{\mathbf a_\parallel}{\gamma^3}
+\frac{\mathbf a_\perp}{\gamma}.
\]

Cases with initial \(|\mathbf v|\ge c\) are invalid. An integration step that
reaches or exceeds \(c\) is rejected. No velocity clamp is permitted.

## Medium impulse

Finite retardation and shielding need not produce an instantaneous
equal-and-opposite body sum. Every accepted step records

\[
\Delta\mathbf p_{\rm medium}=-\sum_i\Delta\mathbf p_i.
\]

Body-plus-medium momentum, not body momentum alone, is the closure ledger.

## Fixed integration and streaming

- Production uses fixed-step velocity-Verlet.
- Fixed-step RK4 is the verification route.
- Runs advance caller-selected finite chunks and may continue until stopped.
- Checkpoints contain states, time, step, history, exact ledgers, diagnostics
  and medium impulse.
- Full 49-channel matrices are emitted for the current state or selected pair;
  stored trajectory frames remain bounded.
- Rendering does not enter the calculation.

## Registered gates

1. **M0 exact ledger:** every seven-channel allocation reconstructs \(N_i\).
2. **M1 matrix count:** exactly \(49N(N-1)\) relations are evaluated.
3. **M2 geometry:** circle centres and radii satisfy the registered section to
   \(10^{-12}R\).
4. **M3 solid angle:** axial quadrature agrees with the analytic disc result
   within \(2\times10^{-6}\) relative.
5. **M4 far field:** the 49-relation sum agrees with point-koppa acceleration
   within \(2\times10^{-5}\) at \(r/R\ge10^4\).
6. **M5 covariance:** translation, rotation and mirror residuals are at most
   \(10^{-10}\) of the registered scale.
7. **M6 retardation:** residual is at most
   \(10^{-12}\max(1,\Delta t)\).
8. **M7 angular union:** complete cover gives zero visible solid angle;
   disjoint cover leaves it unchanged; duplicated cover is counted once.
9. **M8 Law-IV:** increasing unioned depth never decreases \(\rho_i\).
10. **M9 Law-V:** every accepted finite-matter state has \(|v|<c\), and both
    parallel acceleration and deceleration decrease as \(|v|/c\) rises.
11. **M10 streaming:** uninterrupted and checkpoint/resumed states and hashes
    are identical.
12. **M11 parity:** native and WASM fixture outputs agree within the declared
    floating-point policy.
13. **M12 bounded rendering:** the browser draws no more than one selected
    ordered pair's 49 relations while all matrices remain calculated.

## Classification

- `COMPUTED`: exact channel ledgers, retarded geometry, quadrature, Law-IV and
  Law-V response after their registered gates pass.
- `IDENTITY/shared-input`: far-field point-koppa comparison.
- `PENDING`: angular-union or dimensional claims whose registered gate has not
  been executed.

This instrument is not navigation or flight software.
