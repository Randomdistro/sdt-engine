# RUN_LOG — NP14: Proton-Neutron Mass Difference

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Written BEFORE any tool code.**
> Engine: `#include <sdt/laws.hpp>` only.

## Pre-Run Commitments — NP14

- Prompt completion target: B
- Physics class hoped: NATIVE; honest floor accepted: OPEN
- CALIBRATED budget: **0** (any required knob is reported as a knob and fails the gate)
- Engine namespaces: `measured`, `coulomb_identity`, `law_VI::winding`, `bridge`
- Premise (binding, per 2026-07-03 PROMPT note): **neutron = proton + one internal electron (NP17)**,
  NOT a bare uncharged W=3 trefoil. The prompt's Hypotheses A/B/C predate NP17 and are tested
  only for the record under the legacy premise.

## Decision rule (committed now, before any number is computed)

Ledger under NP17: `Δm ≡ (m_n − m_p)c² = m_e c² + S`, where
- `m_e c²` is a **STRUCTURAL/containment** term (the neutron literally contains an electron;
  this piece is by construction, NOT a prediction), and
- `S = Δm − m_e c² = 0.782 MeV` is the **seat surplus** (algebraically ≡ Q_β; the target).

**PRIMARY GATE G1 (the only gate that can produce a PASS):**
native seat surplus `S_native` (knob-free, from engine geometry only) must satisfy
`|S_native − S_meas| / S_meas ≤ 15%`.
The 15% is inherited from NP20's committed T2 bar for the *same* quantity. We do **not** adopt
the PROMPT's 20% on the composite Δm as the primary gate, because the composite contains the
by-construction m_e piece: quoting error on `m_e + S_native` **dilutes** a surplus miss.
The composite number will be printed, labelled **DILUTED — informational only**.
Committed native route for `S_native` (declared now): NP20's seat route,
`S_native = ½ (z − 1) m_e c²` with `z = r_e / R_p` (measured R_p, muonic-H). No alternates
will be fished after seeing the miss; if G1 fails → **OPEN**, cascade root NP20/NP19/NP21.

**GATE G2 (legacy Hypothesis A, record only):** `E_em = αℏc / R_p` compared to Δm.
Admissible only if a fraction `f` with a **prior geometric derivation** is written HERE before
computing. **We declare: no such derivation exists.** Therefore Hypothesis A cannot pass on
numerical proximity of Δm/E_em to any nice fraction (3/4, π/4, …) — any such proximity is
logged as unexplained numerology and the hypothesis is dispositioned PREMISE-DEAD (NP17)
regardless.

**GATE G3 (sign/mechanism, qualitative):** the mechanism must give heavier-not-lighter with no
sign choice: under NP17 the neutron carries (i) one extra particle (+m_e) and (ii) a seat
surplus S > 0 (metastable seat above the free p+e ground, SCT regime II). If either sign has
to be assumed, G3 is reported as assumed, not earned.

## Forbidden retroactive changes
- Widen 15%; adopt the 20% composite gate after seeing the surplus miss; introduce any
  fraction for Hypothesis A after seeing 0.755…; IDENTITY-PASS (reporting S_meas = Q_β as a
  "prediction"); local constant namespaces.

## Planned outputs
`np14_mass_difference.cpp` → compile (MSVC, /std:c++20 /utf-8) → `np14_results.txt`
(redirected stdout) → `NP14_VERDICT.md` (dual verdict).
