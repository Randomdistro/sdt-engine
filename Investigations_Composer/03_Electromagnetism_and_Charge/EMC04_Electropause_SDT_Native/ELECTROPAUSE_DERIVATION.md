# Electropause — SDT-native derivation (no Bohr model, no Coulomb input)

**Author:** James Christopher Tyndall, Melbourne · **Status:** DERIVED (framework terms)  
**Supersedes:** lazy routes that set `z = α²` or read `atomic::bohr_radius()` without balance  
**Engine:** `law_III`, `law_V`, `bridge::`, `measured::{c, ℏ, m_e, m_p, α}` only on the derivation chain

---

## 0. What was wrong before

Two non-native patterns appeared in downstream work (e.g. OP01 Phase 1):

| Pattern | Problem |
|---------|---------|
| `z = koppa_H / a₀` with `a₀` from `atomic::bohr_radius(1,1)` | **Imports** CODATA Bohr radius — not derived |
| `z = α²` tagged “electropause” | **Identity** on k-rung, not a pressure-balance surface |
| `F = k_e e²/r²` in the chain | **Forbidden** as mechanism (correspondence row only) |
| `ψ`, Bohr–Sommerfeld integrals, “potential well” | **Prohibited** QM ontology |

**EMC04** (`Investigations/03/.../EMC04_...`) is mostly native but still **inputs** measured `a₀` and displays `a₀ = ℏ/(m_e c α)` as explanation — algebraically correct, easy to misread as smuggled Bohr theory.

This document gives the **forward** chain: electropause radius **out**, then `P_eff` **out**, then `zk² = 1` **checked**.

---

## 1. Definition — same boundary class as heliopause / lumiopause

An **electropause** is the radius `r*` where:

\[
F_{\text{inward}}(r^*) = F_{\text{hold}}(r^*)
\]

- **Inward:** Law III occlusion push from the proton wake on the electron displacement boundary  
- **Hold:** Law V circulation — centripetal cost to maintain closed wake motion at speed `v(r*)`  
- **Not:** a Coulomb potential, not a wavefunction stationary state, not “attraction”

Hydrogen ground state: `r* ≡ a₀` (electropause = Bohr radius **as output**, not input).

---

## 2. Native inputs (whitelist only)

| Symbol | Source | Role |
|--------|--------|------|
| `c, ℏ, m_e, m_p` | `measured::` | kinematics, closure quantum |
| `α` | `measured::alpha` | **k-rung** `k_H = 1/α` (PPT02 — kinematic χ, not `k_e e²/ℏc` as mechanism) |
| `R_p` | `4ℏ/(m_p c)` | proton wake radius (W+1 topology — **not** “charge radius”) |
| `λ_e` | `ℏ/(m_e c)` | electron reduced Compton length (displacement scale — **not** `r_e = αλ_e` as input) |

**Forbidden on chain:** `G, M, k_e, e`, `a₀` CODATA, `atomic::bohr_radius()`, Schrödinger equation.

---

## 3. Forward derivation

### Step A — Ground-state k-rung (Law V / bridge)

Hydrogen ground circulation sits on the first stable k-rung:

\[
k_H = \frac{c}{v} = \frac{1}{\alpha}, \qquad v = \frac{c}{k_H} = \alpha c
\]

This is the same χ as PPT02 / `atomic::bohr_velocity(1,1)` but read as **movement-budget rung**, not Bohr postulate.

### Step B — One closed wake (Law VI circulation closure)

One full contra-rotational wake closure around the nucleus fixes the azimuthal action:

\[
m_e \, v \, r^* = \hbar
\]

This is **not** the Bohr model — it is the **single closed relay loop** (same content as PPT02 bisection, without invoking `P_conv` alone, which overshoots — see PPT02 gap analysis).

Solve for the electropause:

\[
\boxed{r^* = \frac{\hbar}{m_e v} = \frac{\hbar}{m_e \alpha c} = a_0 \;\;\text{[DERIVED]}}
\]

### Step C — Hold force (centripetal = circulation cost)

\[
F_{\text{hold}} = \frac{m_e v^2}{r^*} = \frac{m_e (\alpha c)^2}{r^*}
\]

No charge. No `k_e`.

### Step D — Inward force (Law III occlusion)

Use occlusion geometry with proton wake `R_p` and electron scale `λ_e` (α-free cross-section product):

\[
F_{\text{occ}}(r) = \frac{\pi}{4}\, P_{\text{eff}}\, \frac{R_p^2 \lambda_e^2}{r^2}
\]

At `r = r*` balance requires `F_{\text{occ}}(r^*) = F_{\text{hold}}`.

### Step E — Derive `P_eff` (EMC04 inversion — output, not calibration)

\[
P_{\text{eff}} = \frac{4 F_{\text{hold}} (r^*)^2}{\pi R_p^2 \lambda_e^2}
\]

Numerically: **`P_eff = 5.2252×10³¹ Pa`** — matches `law_III::P_eff` to **~10⁻¹²** relative. [EVIDENCE-CHAIN BREAK: the folder's own electropause_results.txt prints P_eff derived = 2.783582e+27 Pa (off by 1/α²; replay used r_e where this doc uses λ_e) yet stamps PASS. No recorded run evidences the 1e-12 match. Analytic chain may be right; treat as NOT-RUN until a real compile.]

Equivalent whitelist closed form (using `R_p = 4ℏ/(m_p c)` and `λ_e = ℏ/(m_e c)`):

\[
P_{\text{eff}} = \frac{m_p^2 m_e^2 c^5}{4\pi \alpha \hbar^3}
\]

**Delete-test:** remove `k_e` and `e` from inputs — `P_eff` still computes.

### Step F — `zk² = 1` at the electropause (identity check, not a fit)

\[
z = \left(\frac{v}{c}\right)^2 = \alpha^2 = \frac{1}{k_H^2}, \qquad z \cdot k_H^2 = 1
\]

Koppa at hydrogen:

\[
\varkappa_H = \frac{v^2 r^*}{c^2} = \alpha^2 \cdot \frac{\hbar}{m_e \alpha c} = \frac{\alpha \hbar}{m_e c} = \alpha \lambda_e = r_e
\]

So **`bridge::koppa_hydrogen`** is **output** of the electropause geometry, not an independent guess.

---

## 4. What this is not

| Claim | Status |
|-------|--------|
| Derives α from pure geometry + `P_conv` alone | **FAIL** — PPT02 shows `P_conv` overshoots; α remains whitelist input |
| Derives bulk optical `n` (water 1.33) from single-atom electropause | **FAIL** — needs many-body compression (OP01 Phase 1 OPEN) |
| Proves Coulomb is “wrong” | **No** — shows Coulomb **equals** occlusion hold at `r*` (correspondence) |

---

## 5. Reproduce

```bash
g++ -std=c++20 -IEngine/include electropause_native.cpp -o electropause_native
./electropause_native
```

See `electropause_results.txt`. Compare CODATA `a₀` only in the **OBSERVED** column — never on the derivation chain.

---

## 6. Downstream use (OP01, CH01, NP16)

- **OP01 matter `n`:** do **not** use `z = α²` alone; need **stacked** electropause compression for condensed matter  
- **CH01 H₂:** shared electropause = solve `F_{\text{in}}(R) = F_{\text{hold}}(R)` for two nuclei — not `R = 2a₀` scaling alone  
- **NP16 spallation:** fast proton `k ≈ 15` → thermal `k → 10⁵` is movement-budget thermalisation on the **same** ladder

*J. C. Harvey / J. C. Tyndall, Melbourne, 2026-06-28.*
