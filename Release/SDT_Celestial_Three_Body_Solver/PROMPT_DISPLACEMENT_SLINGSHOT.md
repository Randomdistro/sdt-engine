# GOM43-D — Displacement and Slingshot Extension

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-17  
**Status:** PRE-REGISTERED · EXECUTION PENDING  
**Contract:** `sdtcase-2.1.0`

## Question

Can the retarded seven-cone solver expose the Law-IV displacement carried by
each body and test a rearward angular-concentration slingshot formulation
without inserting that unclosed tail formulation into the qualified production
acceleration?

The existing seven-cone pressure route remains production. The transported
tail is a separate `PENDING` branch until a terminal solid-angle or local
equalisation gate is derived.

## Material-to-displacement ledger

For each material region \(m\), begin with body volume \(V_{\rm body}\),
material volume fraction \(f_m\), density \(\rho_m\), elemental mass fraction
\(w_{me}\), and isotope fraction \(q_{mea}\). The isotope count is

\[
N_{mea}=
\operatorname{round}\!\left(
\frac{V_{\rm body}f_m\rho_mw_{me}q_{mea}}{m_{ea}}
\right).
\]

At least 98 percent of each registered body composition must be represented.
The residual fraction and all density/composition sources remain in the
dataset. Exact integer proton and neutron ledgers are then

\[
N_p=\sum_{mea}Z_eN_{mea},\qquad
N_n=\sum_{mea}(A_{ea}-Z_e)N_{mea}.
\]

The solver must require \(N_p+N_n=N_b\) for a declared displacement ledger.
Its exact trefoil burden is

\[
B_i=1836N_{p,i}+1838N_{n,i}.
\]

Law-IV displacement volumes are calculated through the unchanged canonical
functions:

\[
V_{p,i}=N_{p,i}V_{\rm disp}(m_p),\quad
V_{n,i}=N_{n,i}V_{\rm disp}(m_n),\quad
V_{i,0}=V_{p,i}+V_{n,i}.
\]

No `laws.hpp` value is changed.

## Earth/Sun burden ratio

\[
K_{\rm SDT}=\frac{B_\oplus}{B_\odot}.
\]

The ratio is calculated from exact integer ledgers and emitted with composition
coverage and uncertainty. The approximate \(3.003\times10^{-6}\) value is a
comparison, not an input.

## Rearward angular-concentration stages

The instantaneous anti-solar axis at endpoint \(t_j\) is

\[
\hat{\mathbf t}_j=
\frac{\mathbf r_\oplus(t_j)-\mathbf r_\odot(t_j)}
{\left|\mathbf r_\oplus(t_j)-\mathbf r_\odot(t_j)\right|}.
\]

Stage \(n\) concentrates one conserved burden into

\[
\Omega_n=\frac{4\pi}{2^n},\qquad
K_n=2^nK_{\rm SDT},\qquad
\Omega_nK_n=4\pi K_{\rm SDT}.
\]

The equivalent circular-cone half-angle is

\[
\theta_n=\cos^{-1}\!\left(1-\frac{\Omega_n}{2\pi}\right).
\]

The pause and rearward concentration distances are

\[
x_{\rm pause}=
\frac{D\sqrt{K_{\rm SDT}}}{1+\sqrt{K_{\rm SDT}}},
\qquad
z_n=
\frac{D\sqrt{K_n}}{1-\sqrt{K_n}}.
\]

Scan \(n=0,\ldots,8\). Stage 8 is a candidate only. At \(D\) near one
astronomical unit it should have a half-angle near 7.2 degrees and
\(z_8\) near 4.27 million kilometres. No code may call stage 8 a terminal
prediction.

## Position-angle endpoint formula

At equal geocentric reference radius,

\[
\hat{\boldsymbol\rho}_j=
\frac{\mathbf r_{\rm sc}(t_j)-\mathbf r_\oplus(t_j)}
{\left|\mathbf r_{\rm sc}(t_j)-\mathbf r_\oplus(t_j)\right|},
\qquad
\cos\psi_j=\hat{\boldsymbol\rho}_j\cdot\hat{\mathbf t}_j.
\]

If only asymptotic velocity is supplied,
\(\hat{\boldsymbol\rho}_{\rm in}=-\hat{\mathbf v}_{\infty,\rm in}\) and
\(\hat{\boldsymbol\rho}_{\rm out}=+\hat{\mathbf v}_{\infty,\rm out}\).
Raw velocity angles may not replace the position angle at both endpoints.

The supplied endpoint formulation is

\[
\Delta v_\infty =
v_\infty K_{\rm SDT}
\left[
\left(\frac{D}{R_{\odot,\rm in}}\right)^2\cos\psi_{\rm in}
-
\left(\frac{D}{R_{\odot,\rm out}}\right)^2\cos\psi_{\rm out}
\right].
\]

The solver reports endpoint-radius mismatch rather than silently forcing equal
radii.

## Route separation

1. **Production / COMPUTED:** unchanged retarded seven-cone pressure,
   canonical Law-IV engaged displacement, c-speed retardation, eclipse
   shielding and medium impulse.
2. **Tail / PENDING:** stage geometry, concentrated endpoint values and their
   trajectory finite-difference integral. This branch does not alter body
   state.
3. **Straight-line / IDENTITY/shared-input:** the GOM23/RTM01 control
   \(\Delta v_\perp=2c^2\kappa/(bv_\infty)\).
4. **Anderson / comparison-only:** \(2\omega R/c\) remains separate and is not
   used to construct \(K_{\rm SDT}\).

## Registered gates

1. Composition coverage is at least 0.98 and reported fractions close.
2. Exact \(N_p+N_n=N_b\) and exact weighted burdens reconstruct.
3. C++ displacement volumes agree with direct Law-IV calls.
4. \(\Omega_nK_n=4\pi K_{\rm SDT}\) over all stages.
5. Stage solid angles decrease monotonically and \(z_n\) increases while
   \(K_n<1\).
6. Stage 8 lands in the registered 7.2-degree / 4.27-million-kilometre class
   for the Earth/Sun fixture but remains `PENDING`.
7. Inbound position-angle sign is applied exactly as registered.
8. Equal-radius mismatch is emitted and bounded by the case tolerance.
9. Endpoint and trajectory finite-difference routes agree to floating-point
   tolerance; this is an internal closure, not independent evidence.
10. Production displacement-on/off diagnostics leave canonical trajectories
    unchanged because the tail branch is non-driving.
11. Flyby-frame speed, host-frame energy transfer, canonical impulse,
    straight-line control and medium closure are all reported separately.
12. Native/WASM parity, checkpoint replay and Release/docs parity pass.

## Classification

- `COMPUTED`: material ledger arithmetic, Law-IV displacement volumes,
  stage geometry and unchanged production pressure after their gates pass.
- `PENDING`: transported-tail acceleration interpretation and terminal-stage
  selection.
- `IDENTITY/shared-input`: straight-line and telescoping endpoint-integral
  closures.
- `OBSERVED`: cited composition and trajectory inputs only.

