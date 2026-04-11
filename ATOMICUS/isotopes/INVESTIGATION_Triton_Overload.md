# Triton Overload — Revised Mechanism (James's Micro-Chain)

## The Micro-Mechanism

James proposes the following step-by-step sequence for alpha decay within
the construction grammar. The key insight: the ejected alpha is ASSEMBLED
at the moment of ejection from one triton + one deuteron, with the triton's
extra neutron returned to the daughter.

### The Triton's Internal Topology

A triton (p+2n) within the nuclear scaffold has asymmetric neutron bonding:
- **Connecting neutron** (n_c): bonded to the scaffold — bridges to adjacent
  blocks, mediating the convergence contact that holds the triton in place
- **Open neutron** (n_o): dangling, unbonded to the scaffold — exposed to
  the nuclear surface. This open neutron is the source of the triton's
  **paramagnetic** property: it contributes an unpaired magnetic wake.

The instability from triton overload is NOT from the tritons being too
rigid — it is from too many structural connections having this one-legged
flexibility. Each triton's open neutron is a loose end. Too many loose
ends make the scaffold geometrically mobile, unable to maintain the
convergence lock that holds the construction together.

### Step-by-Step

Starting state: An overloaded triton (t₁ = p + n_c + n_o) is destabilising
the nucleus. It is connected to the scaffold through its one connecting
neutron (n_c). Its open neutron (n_o) dangles at the surface.
Nearby: deuteron d₁ (p+n) and another deuteron d₂ (p+n).

**Step 1 — Deuteron detachment**
d₁ (p+n) detaches from its position in the scaffold.

**Step 2 — Deuteron attachment to triton's open neutron**
The detached d₁ approaches the overloaded t₁ via the triton's
**open** neutron (n_o) — the dangling, paramagnetic one. They form
a 5-nucleon cluster:
t₁ + d₁ = (p + n_c + n_o) + (p + n) = 2p + 3n

This cluster is embedded in the larger nucleus — it is NOT an isolated
He-5. The connecting neutron (n_c) is still bonded to the scaffold,
tethering the cluster to the parent.

**Step 3 — Alpha creation (bend/fold)**
The 2p+3n cluster rearranges:
- The triton's proton, open neutron (n_o), and the deuteron's p+n
  form an alpha configuration (2p+2n — the tetrahedral lock)
- The connecting neutron (n_c) is NOT part of the alpha — it remains
  bonded to the scaffold on the parent side of the break

This step releases the alpha's binding energy (28.3 MeV internal)
minus the energy cost of the rearrangement. The net Q value
(typically 4–9 MeV for actinide alphas) is the kinetic energy
shared between the ejected alpha and the recoiling daughter.

**Step 4 — Alpha ejection**
The newly formed alpha (2p+2n) ejects from the nuclear surface,
carrying 4–9 MeV of kinetic energy. The break happens at the
connecting neutron's bond — the alpha detaches cleanly because n_c
was the only tether, and it stays behind.

**Step 5 — Connecting neutron tritonises an adjacent deuteron**
The connecting neutron (n_c), now orphaned on the daughter's surface
(its triton is gone, taken apart for the alpha), falls onto the
nearest adjacent deuteron d₂, converting it to a triton:
d₂ + n_c → t₂

This is energetically favourable: n_c was already bonded to the
scaffold at this position. It simply transfers its bridge bond from
the departed triton to the adjacent deuteron, tritonising it without
requiring emission or capture from outside.

---

## Grammar Accounting

| Entity | Before | After |
|--------|--------|-------|
| d₁ (detached deuteron) | present | consumed → in alpha |
| t₁ (overloaded triton) | present | consumed → in alpha + leftover n |
| d₂ (adjacent deuteron) | present | → t₂ (tritonised by leftover n) |
| alpha | — | ejected (2p+2n) |

**Net grammar change in daughter:**
- Lost: d₁ (−1d)
- Lost: t₁ (−1t)
- d₂ → t₂: (−1d, +1t)
- **TOTAL: −2d, −1t + 1t = −2d, 0t**

This is EXACTLY what the decay chain data shows: every alpha decay
removes −2d and 0t. James's micro-mechanism produces the same result
as the macro grammar analysis, but now we know HOW.

---

## Verification Against U-238 Chain

### Alpha Decay: U-238 → Th-234 + α

| | Z | A | d | t | Δd | Δt |
|---|---|---|---|---|----|----|
| U-238 (parent) | 92 | 238 | 36 | 54 | — | — |
| Th-234 (daughter) | 90 | 234 | 34 | 54 | −2 | 0 |
| Alpha (ejected) | 2 | 4 | — | — | — | — |

**Experimental products:**
- Alpha particle: 4.270 MeV kinetic energy ✓
- Gamma: 49.55 keV (Th-234 de-excitation, sometimes) ✓
- Neutrino: **NONE** ✓
- Electron: **NONE** ✓

No neutrino is filed because no p↔n conversion occurred. The 2p+3n
cluster simply shed its extra neutron mechanically — no beta process.

### Beta⁻ Decay: Th-234 → Pa-234 + e⁻ + ν̄

This is the SEPARATE step where the triton count is actually reduced:

| | Z | A | d | t | Δd | Δt |
|---|---|---|---|---|----|----|
| Th-234 | 90 | 234 | 34 | 54 | — | — |
| Pa-234 | 91 | 234 | 35 | 53 | +1 | −1 |

One triton converts a neutron to a proton internally: t(p+2n) → d(p+n) + [n→p].
The emitted electron and antineutrino are the receipts of this conversion.

**Experimental products:**
- Electron: 0.273 MeV maximum energy ✓
- Antineutrino: yes ✓
- Gamma: 63.29 keV, 92.38 keV (Pa-234 de-excitation) ✓

---

## Full Chain Verification (All 14 Steps)

| # | Reaction | Type | Δd | Δt | Products | Match? |
|---|----------|------|----|----|----------|--------|
| 1 | U-238 → Th-234 | α | −2 | 0 | α(4.27 MeV), no ν | ✓ |
| 2 | Th-234 → Pa-234 | β⁻ | +1 | −1 | e⁻(0.27 MeV), ν̄ₑ | ✓ |
| 3 | Pa-234 → U-234 | β⁻ | +1 | −1 | e⁻(2.27 MeV), ν̄ₑ | ✓ |
| 4 | U-234 → Th-230 | α | −2 | 0 | α(4.86 MeV), no ν | ✓ |
| 5 | Th-230 → Ra-226 | α | −2 | 0 | α(4.77 MeV), no ν | ✓ |
| 6 | Ra-226 → Rn-222 | α | −2 | 0 | α(4.87 MeV), no ν | ✓ |
| 7 | Rn-222 → Po-218 | α | −2 | 0 | α(5.59 MeV), no ν | ✓ |
| 8 | Po-218 → Pb-214 | α | −2 | 0 | α(6.11 MeV), no ν | ✓ |
| 9 | Pb-214 → Bi-214 | β⁻ | +1 | −1 | e⁻(1.02 MeV), ν̄ₑ | ✓ |
| 10 | Bi-214 → Po-214 | β⁻ | +1 | −1 | e⁻(3.27 MeV), ν̄ₑ | ✓ |
| 11 | Po-214 → Pb-210 | α | −2 | 0 | α(7.83 MeV), no ν | ✓ |
| 12 | Pb-210 → Bi-210 | β⁻ | +1 | −1 | e⁻(0.064 MeV), ν̄ₑ | ✓ |
| 13 | Bi-210 → Po-210 | β⁻ | +1 | −1 | e⁻(1.16 MeV), ν̄ₑ | ✓ |
| 14 | Po-210 → Pb-206 | α | −2 | 0 | α(5.41 MeV), no ν | ✓ |

**14/14 steps match. Zero exceptions.**

---

## The Alternating Pump

The chain reveals itself as a two-stroke engine:

**Stroke 1 (Alpha):** Triton overload destabilises scaffold →
detached deuteron attaches to triton's extra neutron →
alpha assembles from 2p+2n of the d+t pair →
alpha ejects → leftover neutron tritonises adjacent deuteron →
net: −2d, 0t. Triton fraction INCREASES.

**Stroke 2 (Beta):** Elevated triton fraction →
a triton internally converts n→p (beta⁻) →
triton becomes deuteron → files neutrino receipt →
net: +1d, −1t. Triton fraction DECREASES.

The pump runs until the triton fraction drops below the instability
threshold. For the U-238 series, this threshold is reached at Pb-206
(α + 26d + 48t, triton fraction = 48/74 = 64.9%).

---

## Summary

| Step | Grammar | Emissions | ν receipt? |
|------|---------|-----------|------------|
| Alpha decay | −2d, 0t | α + KE + (sometimes γ) | **No** |
| Beta⁻ decay | +1d, −1t | e⁻ + ν̄ₑ + (sometimes γ) | **Yes** |

The mechanism describes a single alpha decay event:
1. Deuteron detaches
2. Attaches to triton's bridge neutron (forms 2p+3n embedded cluster, NOT isolated He-5)
3. Cluster rearranges: alpha (2p+2n) forms, extra neutron squeezed out
4. Alpha ejects with Q-value energy
5. Extra neutron tritonises an adjacent deuteron

James's envisaged mechanism and the macro grammar analysis agree on
ALL outputs. Both approaches arrive at −2d, 0t per alpha decay, and
the alternating alpha-beta pump pattern matches the complete U-238 chain.
