# GOM03: 3D Volumetric Eclipse Saturation  

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## Pure Geometric Unification of HSB and LSB Galaxy Rotation

> **Classification:** SCore Engine Formalization  
> **Domain:** Galactic rotation / volumetric occlusion / eclipse saturation  
> **Prerequisites:** `laws.hpp`, `galactic.hpp`, GD05 failure analysis  
> **Target:** Replace the empirical 2D surface-density saturation anchor with a pure 3D radial occlusion integral.

---

# 1. Core Problem: The 2D Saturation Error

Early SDT galactic-rotation models treated galaxies as flat exponential disks:

\[
\Sigma(r)=\Sigma_0e^{-r/h_R}
\]

This 2D approximation was useful as a proof of concept, but it is not physically complete. A galaxy is not a sheet. It is a three-dimensional displacement volume.

Because the 2D model had no physical depth, it could not calculate the true occlusion of convergence lines through the galactic body. To bypass this, earlier implementations introduced an empirical saturation threshold:

\[
\Sigma_{\text{sat}}=175\ M_\odot/\text{pc}^2
\]

This number was effectively a Milky-Way-calibrated anchor. It forced the engine to behave like a MOND-style interpolation function rather than a pure SDT geometric engine.

That anchor must be removed.

---

# 2. Failure Mode: Low Surface Brightness Galaxies

The 2D model fails for Low Surface Brightness galaxies such as UGC 128 and IC 2574.

These galaxies are diffuse. Their vertical surface density may remain far below the old threshold:

\[
\Sigma_0 \approx 50\ M_\odot/\text{pc}^2
\]

Since the 2D engine only asked:

\[
\Sigma(r) \geq \Sigma_{\text{sat}}
\]

it incorrectly concluded:

\[
r_{\text{sat}}=0
\]

and therefore predicted:

\[
v_{\text{flat}}=0
\]

This is physically wrong.

The failure is not evidence against eclipse saturation. It is evidence that the 2D approximation is incomplete.

---

# 3. Correct SDT Interpretation

Galactic eclipse saturation is not controlled by vertical surface density alone.

It is controlled by the accumulated occlusion of convergence lines travelling through the galaxy’s displacement volume.

For a body orbiting in the galactic mid-plane, the relevant convergence path is primarily radial / horizontal, not vertical through the disk face.

Therefore, the correct question is not:

\[
\text{Does the vertical surface density cross a fixed threshold?}
\]

The correct question is:

\[
\boxed{
\text{How much total baryonic displacement is encountered along the radial path through the galactic volume?}
}
\]

---

# 4. Steel vs Cheese: The Scale-Inversion Principle

In SDT, greater compression produces smaller, denser structures. Lower compression produces larger, more diffuse structures.

This is the same scaling logic seen in particle geometry:

\[
\text{higher mass}
\rightarrow
\text{tighter topology}
\rightarrow
\text{smaller effective extent}
\]

\[
\text{lower mass}
\rightarrow
\text{looser topology}
\rightarrow
\text{larger effective extent}
\]

At galactic scale:

## High Surface Brightness Galaxy

\[
\text{high density}
+
\text{compact radius}
+
\text{shorter radial path}
\]

This is the “steel wheel”.

## Low Surface Brightness Galaxy

\[
\text{low density}
+
\text{large radius}
+
\text{long radial path}
\]

This is the “cheese wheel”.

The cheese is less dense, but the wheel is much wider. A radial convergence line travels through a much longer displacement path.

Therefore, an LSB galaxy can still reach the same eclipse-saturation condition as an HSB galaxy:

\[
f_{\text{occ}}\rightarrow \frac{1}{2}
\]

without requiring dark matter and without requiring an empirical MOND anchor.

---

# 5. Zero-Parameter Doctrine

GOM03 must obey strict zero-parameter rules.

## Forbidden

The implementation must not use:

```cpp
Sigma_sat_Msun_pc2 = 175.0;
```

or any equivalent hardcoded galaxy-calibrated threshold.

The implementation must not use:

\[
a_0 = 1.2\times10^{-10}\ \text{m/s}^2
\]

or any MOND-like empirical acceleration constant.

The implementation must not use:

* NFW halos,
* dark-matter mass profiles,
* Milky Way calibration anchors,
* SPARC-fitted constants,
* empirical interpolation functions,
* hidden tuning factors.

## Permitted

The only allowed constants are fundamental invariants and directly observed baryonic geometry:

* $c$,
* $l_P$,
* $m_p$,
* $\hbar$,
* total baryonic mass $M_{\text{bar}}$,
* radial scale length $h_R$,
* vertical scale height $h_z$,
* gas fraction,
* inclination,
* observed luminous / baryonic distribution.

From the invariants, SDT may derive:

\[
\kappa_{\text{per baryon}}
\]

the effective baryonic occlusion cross-section.

---

# 6. 3D Density Formulation

Replace the 2D surface-density disk with a cylindrical 3D exponential disk:

\[
\rho(r,z)=\rho_0e^{-r/h_R}e^{-|z|/h_z}
\]

where:

* $\rho(r,z)$ is baryonic volume density,
* $h_R$ is radial scale length,
* $h_z$ is vertical scale height,
* $\rho_0$ is central volume density.

The total baryonic mass is:

\[
M_{\text{bar}}
=
\int_0^\infty
\int_{-\infty}^{\infty}
\rho_0e^{-r/h_R}e^{-|z|/h_z}
2\pi r\,dz\,dr
\]

Evaluate the vertical integral:

\[
\int_{-\infty}^{\infty}e^{-|z|/h_z}dz
=
2h_z
\]

Evaluate the radial integral:

\[
\int_0^\infty re^{-r/h_R}dr
=
h_R^2
\]

Therefore:

\[
M_{\text{bar}}
=
4\pi\rho_0h_R^2h_z
\]

so:

\[
\boxed{
\rho_0=
\frac{M_{\text{bar}}}{4\pi h_R^2h_z}
}
\]

This is not fitted. It is forced by the 3D mass normalization.

---

# 7. Horizontal Column Density

For an orbiting body in the galactic mid-plane:

\[
z=0
\]

The horizontal baryonic column encountered along the radial path is:

\[
\Lambda(R)=\int_0^R \rho(r,0)\,dr
\]

Since:

\[
\rho(r,0)=\rho_0e^{-r/h_R}
\]

we get:

\[
\Lambda(R)
=
\rho_0h_R
\left(1-e^{-R/h_R}\right)
\]

Substituting $\rho_0$:

\[
\boxed{
\Lambda(R)
=
\frac{M_{\text{bar}}}{4\pi h_Rh_z}
\left(1-e^{-R/h_R}\right)
}
\]

This has units of mass per area:

\[
\text{kg/m}^2
\]

or:

\[
M_\odot/\text{pc}^2
\]

---

# 8. Why the $h_R/h_z$ Factor Appears

The central vertical surface density of the same disk is:

\[
\Sigma_0
=
\int_{-\infty}^{\infty}\rho(0,z)\,dz
=
2\rho_0h_z
\]

Using the mass normalization:

\[
\Sigma_0=
\frac{M_{\text{bar}}}{2\pi h_R^2}
\]

Now compare the horizontal radial column to the vertical surface density:

\[
\Lambda(R)
=
\frac{\Sigma_0}{2}
\frac{h_R}{h_z}
\left(1-e^{-R/h_R}\right)
\]

Therefore:

\[
\boxed{
\Lambda(R)
=
\Sigma_0
\left[
\frac{h_R}{2h_z}
\left(1-e^{-R/h_R}\right)
\right]
}
\]

This is the key GOM03 result.

The factor:

\[
\frac{h_R}{h_z}
\]

is not empirical. It is the geometric consequence of comparing a long radial path through the disk against a short vertical path through the disk.

This is why LSB galaxies survive.

They may have low $\Sigma_0$, but if they have large $h_R$ relative to $h_z$, the radial column can still be large.

---

# 9. Eclipse Optical Depth

Convert horizontal column density into baryon column number:

\[
N_b(R)=\frac{\Lambda(R)}{m_p}
\]

where $m_p$ is proton mass.

Let:

\[
\kappa_{\text{per baryon}}
\]

be the SDT-derived effective occlusion cross-section per baryon.

Then the radial eclipse optical depth is:

\[
\boxed{
\tau(R)
=
\kappa_{\text{per baryon}}
\frac{\Lambda(R)}{m_p}
}
\]

No empirical galaxy threshold is permitted.

---

# 10. Eclipse Fraction

The eclipse fraction is calculated from optical depth:

\[
f_{\text{raw}}(R)
=
1-e^{-\tau(R)}
\]

The SDT saturation ceiling is half-sky occlusion:

\[
f_{\text{occ}}\rightarrow\frac{1}{2}
\]

Therefore:

\[
\boxed{
f_{\text{occ}}(R)
=
\frac{1}{2}
\left(1-e^{-\tau(R)}\right)
}
\]

This ensures:

\[
0\leq f_{\text{occ}}(R)<\frac{1}{2}
\]

and:

\[
\tau\rightarrow\infty
\Rightarrow
f_{\text{occ}}\rightarrow\frac{1}{2}
\]

This replaces the old hard threshold with a continuous geometric saturation law.

---

# 11. Rotation Velocity Relation

The SDT rotation velocity should be calculated from the eclipse fraction and displacement-pressure response.

A provisional engine form is:

\[
v_{\text{SDT}}(R)
=
v_{\text{limit}}(R)
\sqrt{2f_{\text{occ}}(R)}
\]

where:

\[
2f_{\text{occ}}(R)
\]

normalizes saturation to unity at half-sky eclipse.

When:

\[
f_{\text{occ}}\rightarrow\frac{1}{2}
\]

then:

\[
v_{\text{SDT}}\rightarrow v_{\text{limit}}
\]

The velocity-limit term must be derived from SDT bridge invariants in `laws.hpp`, not from MOND, NFW, or fitted halo parameters.

---

# 12. Required Engine Changes

Update:

```text
Engine/include/sdt/galactic.hpp
```

Remove:

```cpp
constexpr double Sigma_sat_Msun_pc2 = 175.0;
```

Remove or deprecate:

```cpp
double eclipse_fraction(double Sigma);
```

Replace with:

```cpp
double rho0_from_mass(
    double M_bar,
    double h_R,
    double h_z
);

double horizontal_column_density(
    double R,
    double M_bar,
    double h_R,
    double h_z
);

double baryon_column_number(
    double Lambda,
    double m_p
);

double radial_eclipse_optical_depth(
    double Lambda,
    double kappa_per_baryon,
    double m_p
);

double radial_eclipse_fraction(
    double tau
);

double predicted_velocity_3d(
    double R,
    const Galaxy3DProfile& galaxy
);
```

Suggested structures:

```cpp
struct Galaxy3DProfile {
    double baryonic_mass_kg;
    double radial_scale_length_m;
    double vertical_scale_height_m;
    double gas_fraction;
    double inclination_rad;
};

struct VolumetricEclipseResult {
    double rho0_kg_m3;
    double horizontal_column_kg_m2;
    double baryon_column_m2;
    double optical_depth;
    double eclipse_fraction;
    double predicted_velocity_m_s;
};
```

---

# 13. Required Investigation File

Create:

```text
Investigations/CQ23_3D_Volumetric_Integration/cq23_3d_volumetric_integration.cpp
```

This file must:

1. load galaxy profiles,
2. compute $\rho_0$,
3. compute $\Lambda(R)$,
4. compute $\tau(R)$,
5. compute $f_{\text{occ}}(R)$,
6. compute $v_{\text{SDT}}(R)$,
7. compare HSB and LSB behaviour,
8. prove that LSB galaxies no longer return $r_{\text{sat}}=0$.

---

# 14. Test Classes

GOM03 must test at least four classes:

1. High Surface Brightness spirals,
2. Low Surface Brightness galaxies,
3. dwarf irregulars,
4. gas-dominated extended disks.

The minimum success test is:

```text
UGC 128 and IC 2574 must not return zero saturation.
```

---

# 15. Success Criteria

GOM03 succeeds if:

1. the empirical $175 M_\odot/\text{pc}^2$ threshold is removed;
2. LSB galaxies no longer fail by returning $v=0$;
3. saturation emerges from $\Lambda(R)$, not $\Sigma(R)$;
4. HSB and LSB galaxies are handled by the same equations;
5. no dark-matter halo is introduced;
6. no MOND acceleration constant is introduced;
7. no galaxy-calibrated free parameter is introduced;
8. all inputs are physical geometry or fundamental invariants;
9. the resulting model compiles cleanly;
10. the GD05 galaxy-rotation investigation can be rerun using the 3D volumetric engine.

---

# 16. Failure Criteria

GOM03 fails if:

1. any empirical surface-density threshold remains;
2. any MOND-like constant is introduced;
3. any dark-matter halo profile is used;
4. $h_z$ becomes an unconstrained tuning knob;
5. LSB galaxies still return zero flat velocity;
6. the model fits HSB galaxies only by breaking LSB galaxies;
7. the engine cannot explain why diffuse galaxies survive.

---

# 17. Deliverables

GOM03 must produce:

1. a markdown proof of the 3D density normalization;
2. a markdown proof of the horizontal column density integral;
3. an updated `galactic.hpp`;
4. a compiled `cq23_3d_volumetric_integration.cpp`;
5. a rerun GD05 comparison using the 3D volumetric model;
6. a result table comparing 2D failure against 3D recovery;
7. a clear statement of whether LSB galaxies survive.

---

# 18. Final Principle

The galaxy is not a sheet.

It is a displacement volume.

\[
\boxed{
\text{Flat rotation curves emerge from integrated 3D eclipse saturation, not from a 2D surface-density threshold.}
}
\]

\[
\boxed{
\text{LSB galaxies are not failures of SDT. They are failures of flat modelling.}
}
\]
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GD04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: galactic.hpp, GD01 eclipse saturation
- Phase thresholds (committed before run): [commit per phase in RUN_LOG]
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*GD04 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
