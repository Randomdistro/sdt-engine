# Canon proposals — origin-rule sweep (2026-10-03)

> **Propose-and-wait** (gateway procedural §1.3). `Engine/include/sdt/` is canon: nothing below has
> been applied. Each item quotes the current text, the proposed text, and the reason under gateway
> behavioural §3.8 / procedural §3.8. Apply item by item on Harvey's word.

## P1 — `coulomb_identity::k_e_e2` is class A (CONSTRUCTION), not class F

`laws.hpp:2198-2204` (current)

```cpp
    // provenance_status:     unresolved
    // correspondence_status: known-match
    // input_dependency:      definitional-identity  // α ≡ k_e e²/(ℏ c): this line is a tautology
    // class:                 F
    // circularity_assertion: FAILS delete-test — vanishes; supply an SDT path NOT using α's definition
    // risk_flag:             relabel from "Derived (exact, no free parameters)" — it is an identity
```

proposed

```cpp
    // provenance_status:     SDT-first (bridge definition)
    // correspondence_status: known-match
    // input_dependency:      unit bridge — α is the hydrogen koppa rung (PPT02/APS05); e is the SI bridge (EMC02)
    // class:                 A   (label CONSTRUCTION — true by construction, outside the earned tally)
    // circularity_assertion: by construction; carries no evidential weight and claims none
    // risk_flag:             none — load-bearing bridge (gateway behavioural §1, IDENTITY → CONSTRUCTION)
```

Reason: `Theory/05` §2 reserves class F for pending / unverified / failed. A bridge equation that
fixes the coulomb unit from α is a definition (class A), and the gateway already names
`k_e e² = αℏc` as a load-bearing bridge "not to be waved away". Downstream tools (CH02, CH06, PM04)
were relabelled on 2026-10-03 to point here.

`laws.hpp:118-121` (current comment): "the Coulomb route e=√(αℏc/k_e) is a definitional tautology
(class F)" → proposed: "the Coulomb route e=√(αℏc/k_e) is the bridge definition read backwards
(class A, CONSTRUCTION)".

## P2 — `law_VI` `g_electron = α`: class A (CONSTRUCTION), not F

`laws.hpp:2297-2302`: same change as P1 — `class: F` → `class: A (CONSTRUCTION)`; keep the risk
note that the non-trivial claim is g(3) = 4.

## P3 — `F_occlusion` comment contradicts `P_eff`'s current class

`laws.hpp:493-496` says "the coefficient P_eff is class E … coefficient calibrated (see P_eff)", but
`P_eff` itself (`laws.hpp:454-461`) is now `class: C`, `SDT-derived`, "measured R_p, k_e and e absent
from forward form". Proposed:

```cpp
    // input_dependency:      primitive-derivation basis    // structure; coefficient P_eff is class C (EMC04 electropause)
    // class:                 C
    // circularity_assertion: 1/r² structure passes delete-test; P_eff passes (no measured R_p, k_e, e)
    // risk_flag:             P_eff inherits the FLM07 minimum-resistance-path premise
```

Reason: stale label. Agreement of the hydrogen force with the Coulomb form is convergence; no
contaminating input is named.

## Not proposed

`laws.hpp:981` already reads "= GM/c² as a consequence, not an input" — the correct direction.
