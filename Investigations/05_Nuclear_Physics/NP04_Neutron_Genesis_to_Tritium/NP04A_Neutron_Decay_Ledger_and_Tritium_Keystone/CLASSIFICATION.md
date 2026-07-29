# NP04A — Provenance Classification *(corrected)*

Per `Audits/FORMULATIONS_PROVENANCE_AUDIT.md`: `provenance` · `correspondence` · `input_dependency` · `class`. The delete-test (§4) was applied to every C/D claim. **Two corrections vs the first draft:** (1) the keystone **H1 is split** into the *arithmetic* (pure mass-energy accounting, not uniquely SDT) and the *interpretation* (the SDT mechanism claim); (2) the mass-ratio **D1 is downgraded** — the *form* is at best C-flagged, and the **full ratio is F** until the lever `a_p/a_e` is derived.

| # | result | provenance | correspondence | input_dependency | class |
|---|---|---|---|---|---|
| A0 | topological dictionary: charge = signed winding handedness; baryon = trefoil persistence; ν̄ = winding receipt | SDT-posited (axioms) | internal | — | **A** |
| A1 | `ε_link = Q_n = m_n−m_p−m_e = 0.782 MeV` (value) | conservation-derived | known-match | measured-observable | **C** |
| A2 | `μ_n/μ_p = −2/3` (unknot-loaded vs bare trefoil current) | SDT-derived | known-match (−0.685, 1.9%) | measured moments | **C-flagged** |
| B1 | charge/baryon/lepton/winding closure of `n→p+e+ν̄` | SDT-posited (via A0) | known-match | — | **A** |
| C1 | `τ_n` from unlink barrier `Γ = f_circ·e^(−B/ε)` | SDT-derived (form) | pending | barrier inferred from `τ` | **F** |
| C2 | beam–bottle gap = ~1.13% topological branching | SDT-derived | novel-prediction | measured τ split | **D** |
| **D1** | `m_p/m_e = √(3/2)·(a_p/a_e)³` — the **form** | SDT-derived | known-match | primitive-whitelist | **C-flagged** |
| **D1+D2** | the **full proton/electron mass ratio** | unresolved | known-match | depends on D2 | **F** *(NOT C until the lever is derived)* |
| D2 | `a_p/a_e = 11.445` — the lever | unresolved | known-match | — | **F** *(derive from knot geometry → upgrades D1+D2 to C; retires `(3/2)^{3/2}·10³−1`)* |
| D3 | `R_excl,p/R_excl,e = 1836^{1/3} = 12.25` (constant density) | SDT-derived | known-match | `law_IV` literals (12.248) | **C** |
| D4 | `1836π ⟹ R_p = 193 fm` — the falsification | SDT-derived | known-match | primitive-whitelist | **C (negative result)** |
| E | `R_p, W_eff, g_proton` re-emitted from `laws.hpp::winding` | frozen-engine gate | known-match | — | **A (gate)** |
| F1 | triton `B_occ ~ 3·k_occ = 6.67 MeV` (vs meas 8.482) | calibrated | known-match | calibrated-target (`k_occ`) | **E** |
| F2 | di-neutron unbound; proton is the occlusion keystone | SDT-derived | known-match (²n unbound) | grammar | **C** |
| F3 | triton is an alpha-invalid primitive (`alpha_grammar(1,3)→n_d=−2`) | SDT-derived | known-match | isotope integers | **C** |
| G1 | `a₀ = r_e/α² = 5.2918e-11 m` (β-electron re-links at atomic radius) | SDT-derived | known-match | primitive-whitelist | **C** |
| G2 | free-neutron and ground-state H = one topology at two link-radii | SDT-derived | novel-prediction | — | **D** |
| **H1-arith** | **`Q_β(³H) = Q_n − [B(t)−B(³He)] = 18.3 keV`** (the *arithmetic*) | conservation-derived | known-match | measured-observable | **C** |
| **H1-interp** | mechanism: *the free-neutron link strain is mostly absorbed/cancelled by the triton→helion binding difference* | SDT-posited (mechanism) | known-match | measured-observable | **C-flagged** |
| H2 | `Q⁵` Sargent scaling of the τ ratio (residual = super-allowed matrix element) | SDT-derived | known-match (order-of-mag) | measured Q | **C-flagged** |

**Tally (NP04A):** **A 3 · C 7 · C-flagged 4 · D 2 · E 1 · F 3.**
*(C-flagged = A2, D1-form, H1-interp, H2. The 3 F = C1 τ_n, D2 lever, D1+D2 full ratio. The 3n-genesis kinetics F lives in NP04B, not counted here.)*

## The keystone, stated honestly (doctrinal wording)

> NP04A proves that the **free-neutron β-decay ledger** and the **tritium β-decay ledger** are the *same energetic spine* viewed through different binding environments.
> - The free neutron releases `Q_n ≈ 782.3 keV`.
> - Bound inside tritium, almost all of that available decay energy is **cancelled by the triton→helion binding-energy difference**, leaving `Q_β(³H) ≈ 18.6 keV`.
>
> **This is the keystone.** It does *not* prove the rate or likelihood of `3n → t` formation; it proves that, **once proton-keystone capture is available, the energy ledger closes.**

**Why the H1 split matters.** Without separating the rows, a hostile examiner says *"you rediscovered nuclear mass accounting and called it SDT."* They would be partly right. The **arithmetic** (`Q_β = Q_n − ΔB`) is standard and exact (class C, conservation-derived); the **SDT content** is only the *mechanistic reading* of `ε_link` as a Hopf-link strain absorbed by the binding difference (class C-flagged). The ledger is solid; the mechanism is a flagged interpretation.

**The two locked results:**
1. **`1836π` is falsified** (`R_p → 193 fm`); 1836 belongs to the **displaced-volume / exclusion partition** at constant density.
2. **`Q_β(³H) = Q_n − [B(t)−B(³He)]`** — tritium's β-Q follows from the free-neutron Q minus the triton/helion binding difference.

The positive *replacement* for the numerology (deriving `a_p/a_e = 11.445`) is **not yet earned** — D1+D2 stays **F**.
