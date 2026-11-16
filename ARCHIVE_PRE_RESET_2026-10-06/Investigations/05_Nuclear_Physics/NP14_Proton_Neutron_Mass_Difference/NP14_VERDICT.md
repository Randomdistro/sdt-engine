# NP14 — VERDICT: Proton-Neutron Mass Difference

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-03. **Engine:** `sdt/laws.hpp` only.
> Tool: `np14_mass_difference.cpp` (MSVC exit 0) → `np14_results.txt` (redirected stdout).

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **B** | All phases run and gated under the corrected NP17 premise; legacy Hypotheses A/B/C dispositioned; no gate widened, no knob taken. |
| **Physics class** | **OPEN** (mechanism/sign EARNED; magnitude OWED; legacy Hyp A KILLED) | The neutron is heavier because it *contains* an extra electron (+0.511, structural) plus a positive seat surplus; the surplus magnitude is not paid natively (−23.3%). |

## Numbers

| Quantity | Value | Anchor | Error | Label |
|---|---|---|---|---|
| Δm = (m_n−m_p)c² | — | 1.293332 MeV | — | OBSERVED |
| m_e c² containment piece | 0.510999 MeV | — | — | STRUCTURAL (by construction, not a prediction) |
| S_meas = Δm − m_e c² | 0.782333 MeV | ≡ Q_β | — | IDENTITY (target definition only) |
| S_native = ½(z−1)m_e c², z = r_e/R_p = 3.34911 | 0.600196 MeV | 0.782333 | **−23.28%** | COMPUTED · **FAIL G1 (±15%) → OPEN** |
| Seat speed cross-check | 1.83006c (depth) vs 1.83016c (traction) | — | 0.006% | DERIVED (NP20 P1, reconfirmed) |
| Composite Δm_pred = m_e + S_native | 1.111195 MeV | 1.293332 | −14.08% | **DILUTED — informational only** (m_e piece dilutes the surplus miss; refused as a pass even though it clears the PROMPT's naive 20%) |
| Legacy Hyp A: E_em = αℏc/R_p | 1.711391 MeV | 1.293332 | +32.3% | **KILLED** (premise-dead under NP17; required fraction 0.7557 has no prior derivation — logged as inadmissible in RUN_LOG before computing) |

## What is earned vs owed

**Earned:**
1. **The sign, twice over, with no sign knob.** Containment forces +m_e; z = r_e/R_p > 1 forces
   S > 0. The neutron is heavier because it holds an extra particle on a seat *above* the free
   p+e ground — which is exactly why β decay is downhill and releases S (SCT regime II).
2. **The correct decomposition.** Δm splits cleanly into 0.511 (containment) + 0.782 (seat),
   and the 0.782 is Q_β — the NP17 picture is internally consistent with the decay ledger.
3. **Hypothesis A/B/C cleanly killed** — the prompt's original uncharged-trefoil premise is dead
   (2026-07-03 note); its number misses at +32.3% and the "0.756 ≈ 3/4" temptation was
   pre-declared inadmissible before the number was computed.

**Owed (cascade root):**
- The **surplus magnitude**: the committed native route (NP20's ½(z−1)m_e c²) misses at −23.3%;
  the knob that would land it (×1.3035, CALIBRATED(1)) was printed and **refused**. Root:
  the missing native resistance-magnitude law (**NP19/NP21**, same blocker as NP20-T2).
  Until it exists, NP14's mass difference is *explained in structure, not paid in magnitude*.

## Success criteria scoring (from PROMPT §4)

- [x] Specific mechanism identified — containment + metastable seat (NP17/NP20 framing)
- [~] Δm within 20% — arithmetically yes (−14.08%) but **refused**: the composite is diluted by
  the by-construction m_e piece; the honest per-prediction gate (surplus ±15%) FAILS at −23.3%
- [x] Explains why the neutral particle is heavier (sign forced, not assumed)
- [x] Consistent with W+1 (R_p = 4ℏ/m_p c used throughout; seat depth z = r_e/R_p)

## Stress-test self-audit

1. **Identity/circularity:** S_meas = Q_β is algebra, labelled IDENTITY and never sold as a
   prediction. S_native is independent of the target (delete-test: remove m_n from the engine
   and S_native is unchanged). The composite pass was identified as DILUTION and refused.
2. **Fished factors:** none. The only proximity temptation (0.7557 ≈ 3/4) was pre-blocked in
   RUN_LOG G2 before computation. The ×1.3035 knob is reported as a knob, not taken.
3. **Dimensions:** all energies via `MeV_to_J`; z dimensionless; v_seat > c handled as depth
   z = (v/c)², not SR γ.
4. **Class: OPEN.** No RETRO-PASS, no PLUG, no tolerance widening.

## §D Seven questions (HUNTER_PROTOCOL, on the G1 FAIL→OPEN)

1. **Why exactly?** Magnitude: S_native = 0.600196 MeV vs 0.782333 (−23.28%). Sign and structure correct; the number is short by exactly ×1.3035.
2. **Recoverable?** Plausibly — the seat *depth* (z = 3.34911) is solid to 0.006% by two independent routes, so the error lives in the depth→energy map, not the geometry.
3. **What did the target fail to account for?** The ½(z−1)m_e c² map treats the surplus as a pure two-body kinetic partition; it ignores the field-reorganisation cost (FLM12: mass = relay-Doppler imbalance) of *holding* the 1.83c seat.
4. **Which premise erred?** "Surplus = half the excess depth × m_e c²" — both the ½ split and the linear (z−1) form are assumed, not derived from the influx/engagement profile.
5. **What freedom corrects it?** A native resistance-magnitude law E(z); the required 1.303 must fall out of it, not be inserted.
6. **Native or knob?** Today a knob (×1.3035, printed and refused). Native only if NP19/NP21's resistance landscape emits it.
7. **Cascades?** Yes — shared root with NP20-T2, FLM12-D1, NP21: the un-derived resistance-magnitude / engagement profile (FLM10 lineage). Not an independent failure.

**Recovery grade: PARTIAL** (route and premise error named; freedom identified, not yet justified natively).

---

> **Prompt completion B · Physics class OPEN (sign EARNED; legacy Hyp-A KILLED) · Recovery PARTIAL · Cascade root: NP19/NP21 resistance-magnitude law (FLM10/FLM12 lineage; shared with NP20-T2)**

*NP14 · executed 2026-07-03 · honest OPEN · sign earned, magnitude owed to NP19/NP21.*

---

## CANDIDATE APPENDED (2026-07-04, Harvey's scan, run verbatim — [OPEN], look-elsewhere applies)

The 0.782 MeV surplus this verdict FAILED to produce natively (−23.3%) is exactly the
relativistic kinetic energy of the internal electron at **v = 0.91859c**:
(γ−1)·m_ec² = 0.7820 MeV. Geometric-origin candidates for that speed, measured against it:

| candidate | speed | dev (speed) | KE | dev vs Q_β |
|---|---|---|---|---|
| (m_p/m_e)/2000 — "half of 1836" | 0.91808c | −0.06% | 0.7781 MeV | −0.50% |
| seat/2 (1.8302c/2, derived NP20) | 0.91511c | −0.38% | 0.7563 MeV | −3.29% |
| 0.9c flat | 0.90000c | −2.02% | 0.6613 MeV | −15.4% |

**Discipline:** the inversion Q_β → v is an identity and earns nothing. The seat-half (the
derived quantity) MISSES by 3.3% in energy; the near-match belongs to the mass-ratio echo —
which has no right to appear as a speed unless the rotation ontology puts it there (a geared
internal electron pacing against the proton's count). Cashable only by a mechanism that
FORCES v ≈ 0.918c natively (FLM14 gearing is the candidate instrument); until then this is
a privileged, unexplained near-match, same ledger class as the R_p/3 cluster
(PPT08_KOPPA_TARGET). If forced, this verdict's FAIL recovers on the spot.

**Extension (Harvey, same day): "the neutrino takes the other side of the speed."** Law V's
movement budget (v_circ² + v_trans² = c²) partitions the unbinding: the electron's side is
0.91859c, the complementary side is √(1−0.91859²) = **0.39522c** — and at decay the split
between the freed electron and the neutrino varies with release geometry. What this buys
natively, if it holds: (a) the CONTINUOUS β spectrum = the variable partition of one fixed
internal speed; (b) the endpoint = the electron taking the whole 0.782 MeV (neutrino → 0);
(c) neutrino near-masslessness = the unwound remainder travelling straight (PPT10: W=0,
no grip, no mass-cost); (d) ν̄ handedness = the released gear sense. **The named test (real
data exists):** derive the β-spectrum SHAPE from the partition geometry of a 0.9186c seat
unwinding and grade it against the measured Kurie plot — the rival gets that shape from
phase-space integrals; a geared-release geometry that reproduces it would be NATIVE class.
[OPEN — same ledger discipline as above; nothing promoted until the shape test runs.]

**⟐ 2026-07-04 — the shape test RAN: `NP22_Beta_Spectrum_from_Partition_Geometry` — FAIL→OPEN,
and the whole 1-DOF release-measure class is KILLED** (committed isotropic measure KS D = 0.49
vs gate 0.15; the anchor's endpoint (Q−T)² and low-E √T zeros are per-particle 3D state-count
fingerprints no single release angle can produce — knob-proof). Nothing here is promoted; the
partition continuum survives, the shape is owed to a native 3D exit-channel count (FLM14
lineage). See `../NP22_Beta_Spectrum_from_Partition_Geometry/NP22_VERDICT.md`.
