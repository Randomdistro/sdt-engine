# GOM25b — Orbital-Invariant Solar Koppa Reformulation

> **Status:** PRE-REGISTERED — 2026-08-07, after GOM25 Iteration 1  
> **Frozen failed model:** instantaneous `ϟ_i = v_i² r_i / c²` (CV ≈ 1.20% over 2025)  
> **Canon edit:** none. Investigation-level reformulation only.

## 1. Faulty premise (from GOM25 §17)

Identifying solar surface depth with the instantaneous product `v²r/c²` on an
elliptic Earth–Moon-barycenter orbit imports orbital eccentricity into a
quantity claimed to be a solar property.

## 2. Smallest repair

Keep the depth map `z = ϟ / r` and `z_spec = ϟ(1/R_Sun − 1/r_obs)`.  
Replace the solar input by an orbital invariant constructed from the same
state vectors without `G`, `M`, or `bridge::koppa_Sun`:

```text
a      := (r_min + r_max) / 2          over the registered epoch set
ϟ_vv,i := v_i² / [ c² (2/r_i − 1/a) ]  when (2/r_i − 1/a) > 0
ϟ_Sun  := mean_i(ϟ_vv,i)
```

Comparator retained for bookkeeping (not the adopted repair):

```text
ϟ_mean := mean_i(v_i² r_i / c²)
```

## 3. Hold-out protocol (fixed before execution)

1. **Within-year split:** estimate `a` once from the full registered year
   (`r_min`, `r_max` of all epochs). Compute `ϟ_vv,i` at every epoch with that
   single `a`. Freeze the mean of the first half of the time-ordered samples
   as `ϟ_H1` and compare to the second-half mean `ϟ_H2`. Require
   `|ϟ_H1 − ϟ_H2| / ϟ_full < 5×10⁻⁴` (pre-registered).
2. **Cross-year hold-out:** freeze a 2024 Horizons vector table under the same
   query template; compute `ϟ_2024` with that year’s own `a`; require
   `|ϟ_2025 − ϟ_2024| / ϟ_2025 < 5×10⁻⁴`.
3. If either hold-out fails, the repair is **EXCLUDED** for this invariant
   definition (not a widening of tolerance).

## 4. Spectral decision (unchanged 2σ rule)

```text
v_pred = c · ϟ_Sun · (1/R_Sun − 1/⟨r⟩)
```

Prediction uncertainty uses only:

- hold-out systematic `σ_ϟ = |ϟ_H1 − ϟ_H2|/√2` (or cross-year analogue if larger);
- photospheric radius uncertainty when that R is used.

Do **not** inflate `σ` by the instantaneous elliptic CV of `v²r/c²`.  
HARPS 638±6 m/s remains the summary comparator; CO⁵BOLD dependency still
caps confirmation at **UNADJUDICATED** even if numerically COMPATIBLE.

## 5. Invariant quality gate

Report `CV(ϟ_vv)` and `CV(ϟ_inst)`.  
Require `CV(ϟ_vv) < 0.1 · CV(ϟ_inst)` for the repair to count as PARTIAL→candidate
RECOVERED on the IC debt. Failure of this gate ⇒ NO RECOVERY for this form.

## 6. Explicit non-goals

No Cassini residual fit in this sub-loop. No canon write of `ϟ_Sun`. No
post-hoc change of the 5×10⁻⁴ hold-out threshold.
