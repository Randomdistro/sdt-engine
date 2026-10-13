# CR11 — Reciprocity in the Closure Medium: the Tolman Test

**J. C. Harvey, Melbourne — 2026-06-24.** Domain: `07_Cosmology_and_Redshift`.
Tool: `cr11_reciprocity.cpp` (engine-coupled) → **4 PASS / 0 FAIL**.
Builds on **CR10** (z³; the `(1+z)⁴` degeneracy), **FLM09** (light = transverse bond-switch wave, Fermat
least-time, the "forever-aging glass"), **GOM05/depth-closure** (`c_local`, `ℓ_P`). **Discharges CR10's open
item D1** — with an honest verdict.

> **Method (recursive).** CLAIM → TEST. if FAIL → WHY → TRY. if PASS → cause → cause^n → ROOT.

---

## The question

CR10 left this open: SDT's closure gradient is a refractive medium `n(r)=1/(1−z)`; *can it deliver the Tolman
surface-brightness law `Σ_bol ∝ (1+z)⁻⁴` without expansion*, or is SDT-static stuck at the tired-light
`(1+z)⁻²` that the data disfavour? The answer needs FLM09's light mode (what light **is**) and the "aging
glass" spine (what the cosmic redshift **is**) — which is why this proof had to wait for FLM09.

---

## L1 — the surface-brightness theorem **[GEOMETRY]**

Along a ray bundle in a medium of refractive index `n`, the **étendue** `n² dA dΩ` is conserved (Liouville /
the optical Lagrange invariant), so **radiance `B/n²` is invariant.** Verified numerically (an `n₁→n₂`
interface with `B ∝ n²` keeps `B/n²` fixed). This is the optics that turns a distance law into a
surface-brightness law.

## L2 — the closure gradient IS an optical metric (validated by light bending) **[FORM → validated]**

**CLAIM.** In SDT *both* the relay speed and the length shrink with depth: `c_local = c(1−z)` **and**
`ℓ_P(r) = ℓ_P,∞(1−z)`. The optical index therefore carries **two** factors:

```
n_eff = (1 − z)⁻²  ≈  1 + 2z      (NOT the time-only 1/(1−z) ≈ 1 + z)
```

**TEST — solar light bending.** A refractive index `n = 1 + N·z` deflects a grazing ray by `α = 2N·(ϟ/b)`:

| index | `α` (grazing the Sun) | verdict |
|---|---|---|
| time-only `n = 1/(1−z)` | `2ϟ/R = 0.875″` | the **half** value (1801, Soldner/Newtonian) |
| **full `n = (1−z)⁻²`** | `4ϟ/R = 1.7499″` | the **measured** value (1919, GR) ✓ |

with `ϟ_Sun = gR²/c² = 1.476×10³ m` (no `G`, no `M`). **The optical metric is not ad hoc** — it is exactly the
depth-closure, and the full-closure index reproduces the famous factor-of-two and the measured deflection. This
is what licenses treating the closure medium as an effective metric.

## L3 — Etherington reciprocity → the Tolman law **[standard theorem on that metric]**

Etherington's distance-duality theorem: for light on **null geodesics of any Lorentzian metric** with **photon
number conserved**,

```
d_L = (1 + z)² d_A      ⟹      Σ_bol = B_emit / (1 + z)⁴
```

It is *metric-theory-agnostic* — it needs only geodesics + photon conservation, **not** expansion. Since L2
established that SDT's closure medium is an effective (Gordon) optical metric and FLM09 has light following its
Fermat null geodesics, Etherington applies and **`Σ_bol ∝ (1+z)⁻⁴` follows.** The data (Lubin & Sandage Tolman
test, bolometric `≈ (1+z)⁻⁴` after galaxy-evolution correction) match the metric exponent; the static-Euclidean
tired-light `(1+z)⁻²` is disfavoured.

---

## The fork (the honest core)

A *static* metric has **no** redshift. So where does the cosmological `z` enter Etherington?

**TRY (a) — path-local tired-light.** The photon bleeds energy per unit length — a **non-metric** process.
→ Etherington **fails** → `Σ ∝ (1+z)⁻²`.
> **[KILLED for SDT].** If SDT were energy-bleed tired-light, the Tolman data (`≈ −4`) would disfavour it. So
> SDT is **not** path-local tired light (and the naïve "static Euclidean → `(1+z)⁻²`" reading dies with it).

**TRY (b) — time-global aging glass (FLM09).** `ℓ_P` relaxes over cosmic **time** → an effective
**time-dependent** optical metric `n(t)` — an FRW-*like* optical metric.
→ Etherington **holds** → `Σ ∝ (1+z)⁻⁴`, matching the data, with **no space-expansion.**

**WHICH does SDT claim?** FLM09's "forever-aging glass" + the Hubble-tension propagation κ-squeeze → the closure
relaxes **globally in time** → **TIME-GLOBAL** → the metric exists → `(1+z)⁻⁴`.

---

## Reduction to root

- **CAUSE** `Σ ∝ (1+z)⁻⁴` ⇐ Etherington `d_L=(1+z)²d_A`
- **CAUSE²** ⇐ null-geodesic reciprocity + photon conservation
- **CAUSE³** ⇐ light = Fermat least-time paths in an effective optical metric (FLM09 light mode)
- **CAUSE⁴** ⇐ `ℓ_P` sets a refractive index that varies globally in cosmic time (aging glass)
- **ROOT** → **the cosmic redshift is a real relaxation of the medium's relay scale (metric-like)** — neither
  space-stretching (ΛCDM) nor energy-bleeding (tired light).

---

## Verdict — earned, but honestly degenerate

> **SDT recovers the Tolman `(1+z)⁻⁴`** (matches data; **discharges CR10 D1**) — **but it is degenerate.** The
> aging-glass optical metric is *metric-like* (it respects Etherington), so it **ties ΛCDM** on surface
> brightness rather than beating it. This is the same lesson as CR10's `(1+z)⁴`: the headline cosmological
> evidence does not separate SDT from expansion.

What the proof *did* buy, beyond the tie:
1. **Killed a wrong SDT branch.** SDT must **not** be path-local energy-bleed tired light (that gives `−2`, disfavoured). The proof tells SDT which redshift mechanism it is *not allowed* to be.
2. **Validated the optical metric independently** — `n_eff=(1−z)⁻²` reproduces the measured solar deflection (`1.75″`), so the medium used for reciprocity is the same one that already passes light-bending.
3. **Sharpened the standing debt.** The effective metric that delivers reciprocity here is the *same* one owed for **Lorentz-emergence** (CONDENSA §7 [OPEN]). One proof closes both or neither.

**The real discriminator is unchanged:** the **`d(z)` / number-count shape** (CR10 D2 / the CONDENSA Pantheon+
item), where SDT-static and ΛCDM genuinely differ. Surface brightness ties; counts decide.

## Ledger

**[EARNED]** L1 (surface-brightness theorem); L2 (`n_eff=(1−z)⁻²` reproduces `1.75″` deflection); L3
(Etherington on the optical metric → `(1+z)⁻⁴`).
**[IDENTIFICATION]** the cosmic redshift = time-global aging-glass relaxation (the metric that makes Etherington
apply) — leans on FLM09.
**[KILLED]** path-local energy-bleed tired-light for SDT (gives `−2`, disfavoured by Tolman).
**[OPEN]** the `d(z)`/number-count shape (the genuine discriminator); and the explicit derivation that the
aging-glass relaxation **is** a valid Lorentzian optical metric (= the shared Lorentz-emergence debt).

## Run it

```bat
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include ^
   Investigations\07_Cosmology_and_Redshift\CR11_Reciprocity_and_the_Tolman_Test\cr11_reciprocity.cpp
cr11_reciprocity.exe        :: → 4 PASS / 0 FAIL; prints the full recursion tree
```
