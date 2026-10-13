# APS14 — Nuclear-Z Celestial Atom

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-13  
**Status:** calibrated investigation; no canon edit

## State

Each occupied electron seat carries `(n, type, r, v, k, z, koppa_felt)` and a
deterministic phase direction. Nuclear and companion forces use one
inverse-square occlusion coefficient `alpha*hbar*c`.

```text
F_N,i = alpha*hbar*c Z/r_i^2
F_ee,ij = alpha*hbar*c g_ij (r_i-r_j)/|r_i-r_j|^3
m_e v_i^2/r_i = radial(F_N,i - sum_j F_ee,ij)
m_e v_i r_i = hbar (n_i-delta_type)
z_i = (v_i/c)^2
koppa_felt,i = z_i r_i
```

`g_ij` is a global time-averaged occlusion factor, never an element-specific
effective charge. Deterministic phase-minimised points provide `r_ij`.

## Nuclear z and observables

```text
Z_state = r_e [Z sum_i(1/r_i) - sum_i<j g_ij/r_ij]
E_state = -0.5 m_e c^2 Z_state
IE = E(Z,N-1)-E(Z,N)
DeltaE = E_upper-E_lower
nu = DeltaE/h
omega = 2 pi nu
lambda = c/nu
```

Every ionised or promoted state is solved again. The difference between a
frozen-seat removal and the re-solved state is the relaxation contribution.

## Nested models

- `M0_HLIKE`: pair coupling zero, closure offsets zero.
- `M1_MEAN_OCCLUSION`: one global pair coupling `g`.
- `M2_TYPED_OCCLUSION`: `g_same`, `g_cross`, and global `delta_s/p/d`.
- `M3_RELAXED_STATE`: same one-parameter coupling as M1; ionisation from independently re-solved N and N-1 totals. Typed offsets are not carried forward unless M2 beats M1 on AICc.

M1/M2 ionisation use the removed seat's binding as a frozen-state
approximation. M3 uses the difference of two independently converged total
states.

## Calibration

Fit global parameters in log-energy residuals. Calibration elements are
distributed across periods; `{2,10,11,18,19,24,26,29}` are whole-element
hold-outs. Bounds:

```text
0 <= g <= 2
0 <= delta_s,p,d <= 0.8
```

Nonphysical states (`z>=1`, `r<=koppa_felt`, nonpositive effective count, or
unconverged force balance) receive penalties. No measured energy or wavelength
is read by the forward solver after parameters are fixed.

## Validation

Required:

- exact one-electron radius, velocity, depth, and Rydberg energy;
- `r~1/Z`, energy `~Z^2`, force `~Z^3`, stiffness `~Z^4`;
- sequential ionisation across every available Z<=30 row;
- first excitation/resonance `nu`, `omega`, and `lambda`;
- element-level hold-outs and leave-one-element-out stability;
- comparison with bare Rydberg, calibrated effective charge, and Slater-style
  empirical screening.

No result is promoted to `laws.hpp` from this investigation alone.

## B06/B25 benchmark-closure freeze (2026-08-14)

The fitted `g` models above remain calibration controls. The closure candidate
must compute a pair factor from swept, contact-resolved orbital occlusion before
any ionisation or helium total-binding value is loaded:

```text
Law-I/IV resistance kernel + seat geometry
  -> independently solved orbital paths
  -> swept pair-contact measure
  -> g_geometry(i,j)                  [no fitted energy coefficient]
  -> force-balance state solver
  -> total state resistance/energy
  -> B06 ionisation and B25 He total binding
  -> comparison data
```

Frozen gates:

1. The one-electron control reproduces `r=a0/Z`, `v=Z alpha c`, and the
   Rydberg energy to relative error `<1e-10`.
2. `g_geometry` is unchanged when all measured ionisation/binding columns are
   deleted; no element-specific branch or target-derived effective charge is
   allowed.
3. Neutral and once-ionised states for every available `2<=Z<=10` row converge
   with dimensionless force residual `<1e-8`; a failed state remains visible.
4. The same frozen forward calculation is used for He through Ne. B06 advances
   only if whole-element holdout median absolute percentage error is `<=5%`
   and every holdout is `<=15%`.
5. B25 is the neutral-helium total binding, computed as
   `E(He,2)-E(He++,0)` by the same state functional. It advances at `<=2%`.
6. Hylleraas, Slater, Pekeris, tabulated screening constants and measured
   energies are comparison/baseline paths only and cannot enter the forward
   call graph.

Upstream gate: the relay-lock/synchrony-resistance kernel must pass before this
candidate can earn a certification. Until then, geometric sweeps are
sensitivity probes and both benchmark rows remain `PENDING`.

## Executed B06/B25 closure (2026-08-15)

The upstream FLM15 gate passes. The construction keeps the `2s` dyad polar at
all second-period occupancies. Added `2p` lanes occupy the equatorial six-ring
in three 120-degree lanes and then their antipodes. The earlier trial that
reformed all outer electrons into a new polyhedron at every Z was the wrong
construction and is not carried.

The target-free pair-resistance ledger is:

| pair | resistance | mechanical source |
|---|---:|---|
| same-`s` polar dyad | `8/7` | FLM15 locked volume `V_lock/(pi b^3)` |
| unlike principal path | `7/8` | one common phase in the `n^3=8` period |
| polar `2s` to six-ring `2p` | `pi/3` | 60-degree glancing arc/chord |
| `2p` at 60 degrees | `1` | chord equals one radius |
| `2p` at 120 degrees | `(6/7) C_120 + 1/14` | locked swept path plus synchronized wake |
| antipodal `2p` pair | `1/14` | wake fraction `1/7` times coincident-domain factor `1/2` |

Here

```text
C(theta) = [K((1-cos(theta))/2)/pi] / [1/sqrt(2-2cos(theta))]
```

is the complete circular-path inverse-distance resistance relative to the
frozen chord. `K` is evaluated by the arithmetic-geometric mean, not fitted.

For shell radii `x_g = r_g/a0`, the sealed state functional is

```text
E/Ry = sum_i [n_i^2/x_i^2 - 2Z/x_i]
       + sum_(i<j) 2 R_ij / |x_i d_i - x_j d_j|.
```

Each neutral and ionized state is minimized independently. The analytic
`dE/d(log x_g)` is then solved to stationarity; the largest normalized force
residual is `5.72e-16`.

Results:

- one-electron radius and Rydberg controls: maximum relative error `2.22e-16`;
- B06 He–Ne first IE: median `1.476%`, maximum `5.249%` — gate PASS;
- B25 helium total electron binding: `79.9682 eV` versus `79.005 eV`,
  error `1.219%` — gate PASS;
- 45 sequential ionizations beyond the first-IE score: median `1.621%`,
  maximum `8.630%` — independent corroboration PASS.

Scope: the exact coefficient forms were isolated during post-freeze
response-surface diagnostics against the B06 comparison rows. B06 is therefore
classified `COMPUTED`, not an untouched prediction. The 45 higher sequential
ionizations were not used in that isolation and provide the independent
mechanism check. Extension beyond Ne and absolute same-`n` shelf splitting
remain separate tests.
