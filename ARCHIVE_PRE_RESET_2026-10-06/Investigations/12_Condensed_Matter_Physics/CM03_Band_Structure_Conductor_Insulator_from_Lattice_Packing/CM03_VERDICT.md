# CM03 — Verdict: Band Structure / Conductor–Insulator from Lattice Packing

**Author:** J. C. Harvey, Melbourne · **Run:** 2026-07-04 · Tool `cm03_band_packing.cpp` →
`cm03_results.txt` (MSVC `/std:c++20 /O2 /utf-8`, real stdout; tree and gates pre-committed).

## Headline

**The conduction trichotomy is packing-sorted: 9/9, zero misclassifications, from a 3-rule tree
committed before scoring.** Grip saturation (U = z − bonds) splits metals from the gapped; network
dimensionality splits molecular insulators (vdW blockade) from bonded networks; the gap scale is
wake confinement E_g = f·ℏ²/(m_e d²) — the same Law VI/FD02 door as CM01's carrier speed. No Bloch
wave, no k-space object, no electron cloud anywhere in the chain.

- **Ordering E_g(C) > E_g(Si) > E_g(Ge): derived, f-independent** (pure 1/d²).
- **Magnitudes: Si 1.30 vs 1.12 eV (1.16×) · Ge 1.20 vs 0.66 (1.82×) · C 3.01 vs 5.47 (1.82×)** —
  all inside the committed 2× gate on ONE shared factor f = 0.944 (CALIBRATED(1), minimax,
  declared pre-run; max miss 1.815× — tight, reported exactly).
- Activation: the ½ in exp(−E_g/2k_BT) is **derived** (bridging creates a freed wake AND a mobile
  vacancy; balance kinetics), and dρ/dT < 0 for the gapped class. The P3 slope check is
  **COMPUTED-internal** (form demonstration, not a prediction) — labelled as such, not counted.

## Honest edges (printed, outside the committed gate)

- **Sn-grey: predicted 0.91 eV vs ~0.08 measured (11.4×).** Classification still lands
  ("semiconductor" class) but the magnitude law collapses at the zero-gap edge.
- **P-black: predicted 1.45 vs 0.33 eV (4.4×).** The 2-D layered network is misgraded by a
  nearest-neighbour-only d.

## §G mirror

- Faith ledger: the wake-confinement door (named, shared cluster-wide); the 2.0 eV
  semi/insulator line is a declared *convention* — it did no work in P1 beyond separating C from
  Si/Ge/Sn, which the 1/d² scale already ordered.
- No rival axiom in any gate; anchors are observed classes and measured gaps. The kill trigger
  (≥2 missorts) never fired.

## FAILURE RECOVERY (§D — the Sn-grey / P-black magnitude edge)

1. **Why:** magnitude misses of 11.4× (Sn) and 4.4× (P) — both OVER-predictions at the soft edge
   of the family, while C is UNDER-predicted 1.8×. The raw 1/d² law is too shallow: measured gaps
   fall faster than 1/d² along C→Si→Ge→Sn.
2. **Recoverable?** Possibly — the residual trend is monotone in d, suggesting one missing
   d-dependent mechanism, not noise.
3. **Unaccounted:** grip *quality* — the same coordination-4 network grips a wake harder when
   bond overlap is deeper; d alone carries only part of that.
4. **Errored premise:** "channel width d is the ONLY packing length that sets the blockade."
5. **Freedom:** a second native length (bond overlap depth / traction grip length, PPT06) making
   E_g = f·ℏ²/(m_e d²)·g(d/ℓ_grip).
6. **Accounted natively?** PPT06 traction is the right native home, but g() is unbuilt — until it
   is derived, adding it would be a FISHED exponent. Held OPEN. Re-open condition: PPT06 delivers
   a grip length; then the Sn/P edge is the falsification test waiting.
7. **Cascade:** independent of ROOT-A/ROOT-B — this is a missing second length in the packing
   grammar (local root, named: grip-depth closure).

**Recovery grade: PARTIAL.**

## Generative questions logged

1. Grey↔white tin sits exactly on the metal/semi line — is the transition a grip-saturation flip
   (U: 0 → >0 under the structure change)? Sharp test of rule 1.
2. Does pressure close gaps with the predicted sign (d shrinks → E_g grows as 1/d²? — measured Si
   dE_g/dP is NEGATIVE: the 1/d² law predicts the WRONG SIGN if d simply shrinks). Logged as a
   standing falsifier for the grip-depth closure above — the naive law already fails it, the
   g(d/ℓ_grip) correction must fix the sign or the gap law dies there.
3. Is the donor 1:1 carrier-per-dopant rule (P4) testable as a literal channel count vs Hall data?

---

> **Prompt completion B · Physics class CONVERGENCE (trichotomy native; magnitude on one
> CALIBRATED(1) factor; edge-of-family OPEN) · Recovery PARTIAL · Cascade root grip-depth closure
> (local; PPT06 owes the second length)**
