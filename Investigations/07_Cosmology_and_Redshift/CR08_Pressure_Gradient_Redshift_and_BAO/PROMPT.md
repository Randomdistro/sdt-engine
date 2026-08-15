# CR08: Pressure-Gradient Redshift and BAO Scale — Data/Prompt

> **Author:** James Christopher Tyndall, Melbourne. **Status:** EXECUTED; B15 COMPUTED (extension 2026-08-15).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `sdt/laws.hpp` is canonical; `cosmology.hpp` is used only for the
> quarantined class-X duration audit and historical distance-law comparison.
> **Run:** Pre-registered thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion
   (A–F) + physics class (NATIVE / CONVERGENCE / SHARED-INPUT /
   FALSIFIED / OPEN).

## DATA REQUIREMENTS
| Data | Source |
|------|--------|
| SDSS/BOSS/eBOSS BAO measurements: D_A(z), D_H(z) at z=0.15–2.33 | BOSS DR12, eBOSS |
| DESI BAO (2024) | DESI Y1 |
| CMB acoustic peak positions | Planck 2018 |
| Galaxy redshift surveys | SDSS, 6dF, WiggleZ |
| SDT strain rate σ | cosmology.hpp |
| SDT BAO scale interpretation | cosmology.hpp bao namespace |

## INVESTIGATION PROMPT

### CR08: Pressure-Gradient Redshift
**Target**: Derive the distance-redshift relation from pressure gradient traversal (no metric expansion).

SDT says: z = exp(∫σ dx) − 1, where σ is the local strain rate. At low z this is linear (z ≈ σd ≈ H₀d/c, reproducing the Hubble law). At high z it curves differently from ΛCDM.

Compute SDT μ(z) for the Pantheon+ sample and compare to ΛCDM.

### CR08: BAO as Lattice Standing Waves
**Target**: Predict the BAO scale as a lattice equilibrium length, then load the measured ruler for comparison.

The coupled-epoch lattice (before the Clearing) supported a baryon-loaded
relay mode. The historical `t_coupled=147 Mpc/c_s` implementation is circular
and excluded from prediction. The P0 opacity route below is retained as a
control; after it yielded no admissible clearing clock, the pre-registered P1
pivot derived a target-independent standing-equilibrium scale from the escape
response rate.

### Common Methodology
1. Compute SDT angular diameter distance D_A(z) from pressure-gradient integration
2. Compare to BAO-measured D_A at each redshift bin
3. Compute SDT Hubble distance D_H(z) = c/H(z) where H varies with z
4. χ² comparison: SDT vs ΛCDM at each BAO redshift

### Success Criteria
- [ ] SDT D_A(z) matches BAO measurements within 3%
- [x] BAO ruler reproduced within 3% from the independently derived standing response and relay speed
- [ ] No dark energy needed in the SDT fit
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT /
> FALSIFY / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CR08
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|SHARED-INPUT|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: cosmology.hpp, z_spectral, CR10 cubic rung
- Phase thresholds (committed before run): 3%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **FALSIFY** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **shared-input / not independent** | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*CR08 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

## B15 P0 release/opacity route freeze — retained control (2026-08-14)

The stored `147 Mpc` and the duration obtained by dividing it by a sound speed
are comparison-only and cannot enter the forward route:

```text
Law-II release history
  + free/bound winding populations
  + FD02/FLM15 relay scattering cross-section
  -> opacity(t) and mean free path(t)
  -> clearing condition optical_depth(t)=1
  -> t_coupled                         [printed and sealed here]
  -> baryon-loaded relay speed c_s(t)
  -> integral_0^t_coupled c_s(t) dt
  -> BAO comparison
```

Upstream gates are the FLM15 resistance kernel, the FD02 cross-section and a
free/bound winding population law. A provisional value from any of them may be
used for sensitivity only and cannot certify B15.

Frozen gates:

1. Every term in opacity has closed dimensions; independent time-step and
   adaptive-quadrature routes agree within `0.5%`.
2. `t_coupled` is emitted before any BAO distance is loaded and is unchanged
   when `147 Mpc` and all BAO columns are deleted.
3. The clearing root is unique over the registered Law-II release interval;
   halving/doubling the search interval or resolution changes it by `<1%`.
4. The sound-speed integrand uses the same derived baryon loading and
   scattering history; no metric-expansion history or target-defined duration
   enters.
5. This P0 route could advance B15 only if its predicted
   comoving-equivalent mechanical scale were
   within `3%` of the measured BAO ruler. A miss preserves the duration,
   predicted scale, residual and the upstream reopening condition.
6. The free-only and fully-bound populations are mandatory bracketing
   controls; the physical result must lie between them.

## B15 P1 standing-equilibrium pivot freeze (2026-08-15)

CR17b executed the optical candidates before this pivot. Its Ioffe-Regel,
rate-equality and line-of-sight `optical_depth=1` roots all fall outside the
Clearing band; the native transition is instead obstacle depinning across the
finite window from radiation/baryon energy equality to loading equality. The
`optical_depth=1` route above therefore remains a required control, but it is
not promoted into a clock by inserting a population curve.

The target-independent standing-equilibrium route is frozen before its CR08
instrumentation:

```text
FIRAS T_CMB + BBN-deuterium eta
  -> present photon and baryon counts
  -> N_eq from rho_b(N_eq)=rho_gamma(N_eq)
  -> n_b(N_eq) from the Prop-13 coasting law
  + phase-resistance length per baryon
  -> escape response rate of a uniform resistance sphere
  + baryon-loaded relay speed at R=3/4
  -> standing radius whose acoustic round trip equals one escape response
  -> present-equivalent scale N_eq times standing radius
  -> BAO comparison
```

The frozen equations are

```text
n_gamma,0 = 16 pi zeta(3) [k_B T_CMB/(h c)]^3
n_b,0     = eta n_gamma,0
N_eq      = (n_b,0 m_p)/(a T_CMB^4/c^2)
n_b,eq    = n_b,0 N_eq^3
R_eq      = (3/4) rho_b/rho_gamma = 3/4
Gamma_esc = c sqrt[(8 pi/3) koppa_b n_b,eq]
c_s,eq    = c/sqrt[3(1+R_eq)]
L_eq      = c_s,eq/(2 Gamma_esc)
L_BAO     = N_eq L_eq
```

Here `8 pi/3` is not a cosmology coefficient: integrating the SDT
phase-resistance length over a uniform sphere gives the `4 pi/3` orbital
response. The radial Law-III work integral to infinity is
`c^2 koppa/r` per unit resistance; equality with release cost `v^2/2` gives
the registered `bridge::v_escape` factor two. The second factor two is the
round trip required by a standing mode. Energy equality is selected because
the wavelength is an energy-partition equilibrium; `R=1` is the later
inertial-loading depinning endpoint and is printed as a frozen control.
`N_eq L_eq` is the Prop-13 present-equivalent separation; no
metric-expansion history enters.

Frozen gates:

1. No BAO ruler, `H_0`, `R_CMB`, metric history, `G`, source mass or source
   parameter enters the prediction call graph.
2. Analytic and radial finite-volume evaluations of `Gamma_esc` agree within
   `0.5%`; halving and doubling the radial resolution change `L_BAO` by `<0.5%`.
3. FLM15 collision measures at the conservative proton boundary, free
   electron/proton boundary and bound-seat boundary bracket the opacity.
   The standing region must remain coupled (`tau>1`) at the smallest
   non-zero geometric boundary.
4. The `R=1` depinning endpoint, orbital-not-escape response and
   travelling-wave-not-standing-wave variants are printed as controls; none
   may be substituted after comparison.
5. The prediction is emitted before the `147.09 Mpc` comparison is read.
   B15 advances only within the existing `3%` gate and is `COMPUTED`, not an
   independent cosmological result, because it inherits FIRAS and
   BBN-deuterium inputs.
