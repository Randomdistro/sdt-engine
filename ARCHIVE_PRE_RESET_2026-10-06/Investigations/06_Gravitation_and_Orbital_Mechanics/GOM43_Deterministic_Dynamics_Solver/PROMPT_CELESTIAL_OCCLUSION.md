# GOM43-C — Retarded Seven-Cone Celestial Occlusion Solver

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED · EXECUTION PENDING  
**Date:** 2026-08-17  
**Contract:** `sdtcase-2.0.0`

## Question

Can a settable three-body trajectory be calculated as a directional pressure
imbalance caused by finite, retarded baryonic occlusion, using the repository's
Law-IV resistance per baryon, without encoding attraction, `G`, source mass,
softening or a force centre?

The point-koppa runner remains a declared comparison route. It is not the
production mechanism qualified here.

## Frozen inputs

For each body \(i\):

- exact positive integer bulk baryon count \(N_i\);
- physical radius \(R_i\);
- inertial Cartesian position and velocity at epoch \(t_0\);
- collision radius, normally \(R_i\);
- provenance for the baryon census and initial state.

Canonical constants are read without modification from `sdt/laws.hpp`:

\[
\kappa_b=\texttt{bridge::koppa_per_baryon},\quad
c=\texttt{measured::c},\quad
m_b=\texttt{measured::m_p}.
\]

The Law-IV per-baryon exclusion volume is

\[
V_b=\texttt{law_IV::V_disp_from_mass}(m_b).
\]

No measured trajectory, Lagrange position or residual enters these equations
as a fitted coefficient.

## Exact baryon packet ledger

Parse all three counts as arbitrary-precision unsigned integers and calculate

\[
g=\gcd(N_1,N_2,N_3),\qquad q_i=N_i/g.
\]

The normalized packet ledger must reconstruct every input exactly:
\(q_i g=N_i\). Dynamics use aggregate floating representations only after this
exact ledger has been recorded.

## Pair projections and seven channels

There are three unordered pairs: \(12,13,23\). Each pair has two directed,
co-facing body projections. Every projection has a centre channel and one
hexagonal shell of six channels, producing 14 directed cones per pair and 42
for the complete three-body state.

For a body radius \(R\), each geometric channel circle has radius \(R/3\). The
outer channel centres are at projected radius \(2R/3\), separated by
\(60^\circ\). Effective full-disc area weights are frozen as

\[
w_0=\frac19,\qquad w_{1\ldots6}=\frac{4}{27},\qquad
w_0+\sum_{k=1}^{6}w_k=1.
\]

The outer weights include their associated interstitial sectors. The seven
weighted baryon populations must sum to the body's exact count; integer
remainders are assigned deterministically by largest remainder, then channel
index.

For channel-centre offset \(\rho_k\), the body chord is

\[
h_k=2\sqrt{R^2-\rho_k^2},\qquad d_k=h_k/(2R).
\]

The reported cone includes its front point, rear point, chord, rear spherical
cap, solid angle and directed axis. Lines and cones continue through the body;
they do not terminate at its centre.

## Retarded geometry

Occlusion information propagates at \(c\). For target \(i\) at solver time
\(t\), the source state is evaluated at the retarded epoch \(t_r\) satisfying

\[
t-t_r=\frac{\left|\mathbf r_i(t)-\mathbf r_j(t_r)\right|}{c}.
\]

Solve this equation iteratively against deterministic trajectory history.
Before the first stored epoch, use the declared ballistic prehistory and flag
every such sample. A checkpoint must retain enough history to reproduce every
outstanding light-time query exactly.

The pair projection is normal to

\[
\hat{\mathbf n}_{ij}=
\frac{\mathbf r_j(t_r)-\mathbf r_i(t)}
{\left|\mathbf r_j(t_r)-\mathbf r_i(t)\right|}.
\]

Thus the pressure deficit points toward where the source was, not where it is.

## Finite occlusion depth and Law-IV resistance

For source angular radius

\[
\alpha_{ij}=\arcsin\!\left(\min(1,R_j/r_{ij})\right),
\]

the normalized hemispherical occlusion is

\[
o_{ij}=\Omega_{ij}/(2\pi)=1-\cos\alpha_{ij}.
\]

For channel \(k\), before third-body shielding,

\[
D_{ijk}=w_k d_k o_{ij}.
\]

The target's total engaged fraction is

\[
D_i=\sum_{j\ne i}\sum_{k=0}^{6}D_{ijk}.
\]

The rest and engaged exclusion volumes are

\[
V_{i,0}=N_iV_b,\qquad V_{i,\mathrm{eff}}=V_{i,0}(1+D_i).
\]

Effective inertial resistance is calculated only through the existing Law-IV
functions:

\[
m_{i,\mathrm{eff}}=
\texttt{law_IV::mass_from_V_disp}(V_{i,\mathrm{eff}}).
\]

Because the same \(m_{i,\mathrm{eff}}\) divides every signed change of velocity,
deeper occlusion resists starting and stopping identically. No separate
linear, inverse-depth or velocity multiplier is permitted.

## Pressure-deficit resultant

The unshielded pairwise convergence scale is the SDT per-baryon limit

\[
a^{(0)}_{ij}=\frac{c^2N_j\kappa_b}{r_{ij}^2}.
\]

This is interpreted and implemented as the resultant of missing external
pressure over the seven rear-surface patches, not as a pull by body \(j\).
The rest-resistance drive on \(i\) is

\[
\mathbf F^{\rm press}_{ij}
=(N_im_b)a^{(0)}_{ij}(1-S_{ij})\hat{\mathbf n}_{ij}.
\]

The integrated response is

\[
\mathbf a_i=
\frac{\sum_{j\ne i}\mathbf F^{\rm press}_{ij}}
{m_{i,\mathrm{eff}}}.
\]

The seven channel vectors must sum to this directed pair contribution within
floating-point tolerance.

## Third-body eclipse shielding

From target \(i\), project source \(j\) and third body \(k\) at their separate
retarded epochs. Calculate exact apparent-disc circle overlap. The shield
fraction is the overlap area divided by source apparent-disc area:

\[
S_{ij}=\operatorname{clip}(A_{\rm overlap}/A_j,0,1).
\]

This reduces convergence strength only; it does not create an opposite pull.
Record no overlap, penumbra, umbra/totality, ingress and egress. Retarded phase
is the difference between current and retarded line-of-sight angles.

## Medium impulse and pivots

Retarded body forces are not required to be instantaneously equal and opposite.
The instrument therefore records

\[
\Delta\mathbf p_{\rm medium}
=-\sum_i\Delta\mathbf p_i
\]

at every accepted step. The body-plus-medium momentum ledger, not the bodies
alone, is the closure gate.

Pair and full-system baryonic pivots are diagnostics:

\[
\mathbf r_{\rm pivot}=
\frac{\sum_iN_i\mathbf r_i}{\sum_iN_i}.
\]

They are never used as force origins.

## Lagrange points

L1-L5 are numerical zeros of the calculated retarded seven-cone pressure
resultant plus the declared rotating-frame kinematics. Point-koppa roots may
be reported alongside them as `IDENTITY/shared-input` comparisons but may not
replace the pressure-root calculation.

## Fixed stepping and unlimited sessions

- Production: fixed-step velocity-Verlet using the same retarded evaluator at
  both acceleration stages.
- Verification: fixed-step RK4.
- A session advances a caller-selected finite chunk, emits bounded records,
  and may continue until the caller stops it.
- Checkpoint/resume must be byte-deterministic and include state, counters,
  diagnostics, medium impulse and retarded history.
- Rendering clocks never enter the calculation.

## Registered gates

1. **C0 exact packets:** arbitrary-precision GCD and all reconstructions exact.
2. **C1 channel closure:** \(1/9+6(4/27)=1\) to \(10^{-15}\); allocated integer
   channel populations reconstruct each \(N_i\).
3. **C2 cone geometry:** front/rear points lie on the sphere to \(10^{-12}R\);
   chord and cap values are finite and non-negative.
4. **C3 retardation:** each light-time residual is at most
   \(10^{-12}\max(1,\Delta t)\); translation and rotation covariance each pass
   at \(10^{-11}\) of the registered scale.
5. **C4 depth/resistance:** increasing source solid angle or chord depth never
   decreases Law-IV effective resistance.
6. **C5 channel resultant:** seven channels reproduce the directed pair
   pressure resultant within \(10^{-13}\) relative.
7. **C6 eclipse limits:** disjoint discs give zero shield; a contained source
   disc gives unit shield; overlap remains continuous through tangency.
8. **C7 medium ledger:** normalized body-plus-medium momentum residual remains
   at most \(10^{-11}\).
9. **C8 deterministic streaming:** uninterrupted and checkpoint/resumed runs
   have identical terminal state and trajectory hash.
10. **C9 native/WASM parity:** canonical fixture outputs agree within the
    declared floating-point policy and have identical classifications.
11. **C10 pressure roots:** reported L1-L5 pressure residuals are at most the
    case-declared tolerance.
12. **C11 whole-range comparison:** every JPL fixture interval is processed in
    one pass and publishes position/velocity residual series without tuning.

## Classification

- `COMPUTED`: seven-cone geometry, retardation, Law-IV resistance and pressure
  integration after C0-C10 pass.
- `OBSERVED`: supplied JPL/Horizons states and measured body radii, each with
  provenance.
- `IDENTITY/shared-input`: point-koppa comparison route.
- `PENDING`: any dimensional bridge or pressure-root case that fails a
  registered gate.

The instrument is not a closed-form solution of the general three-body problem
and is not navigation or flight software.
