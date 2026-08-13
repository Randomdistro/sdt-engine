# NSEQ01 — Nuclear Packing Sequencer rules freeze

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Class:** SDT claim investigation (rule ledger / source of truth for packing).  
> **Upstream:** NP12c–e parked — “charge radius” is a QED measurement formulation;
> sequencer physics is **boundary / enmeshment**, not that observable.  
> **Canon edits:** none.  
> **Source of record:** `Release/HTML_SDT_Website/nuclear-packing-sequencer.html`
> (mirror: `docs/nuclear-packing-sequencer.html`). Walkthrough:
> `docs/nuclear-packing-walkthrough.html`.

## 0. Objective

Freeze the **executable rule set** already implemented in the Nuclear Packing
Sequencer — grammar, spherical-tier packing, p↔n contact graph, shadow-union
mass defect — as the native nuclear construction ledger for subsequent tests.

This loop does **not** re-open IAEA RMS charge-radius adjudication. Neutrons
enter as mesh / stability structure (internal e⁻ seats), not as a conversion
factor from boundary length to a QED charge radius.

## 1. Rules to freeze (from sequencer source)

| ID | Rule |
|---|---|
| R1 | **α-grammar:** `n_t = A − 2Z`, `n_d = 3Z − A − 2`; valid when `n_d≥0`, `n_t≥0`. One α core. |
| R2 | **Boundary scale:** `R_p = 0.8414 fm` (W+1 proton boundary). Occlusion area `A₁ = π R_p²`. |
| R3 | **α core:** contact-rotation tetrahedron; rings at face circumcentres; ring radius ≡ `R_p`; contacts p↔n only on mixed edges. |
| R4 | **Deuteron tiers:** radial rods (n inward, p outward); capacities `6,12,12,20,30,…`; bond length `D < 2 R_p` ⇒ interlacing. |
| R5 | **Triton shells:** coherent radial n–p–n rods on dual-tetrahedra shells (caps 8,10,12…; `r_open>r_close`). Planar “belt” orientation withdrawn (NSEQ02/03). |
| R6 | **Contacts:** explicit p↔n list (`nuc.contacts`); bipartite by construction. |
| R7 | **Mass defect:** `ΔA = Σ A_i − A_∪` (shadow union); `E_bind ≈ κ·ΔA` (one scale; fit reported separately, not this freeze). |
| R8 | **Enmeshment reading:** meshing / shared occlusion **is** the defect; interleaved region is not attributable to either form alone (dissolves “proton radius changes in nuclei” as a charge-radius puzzle). |

## 2. Procedure

1. Extract R1–R8 with file/line anchors from the sequencer HTML.  
2. Validate R1 algebraically on the sequencer’s isotope table (every kept row:
   `n_d,n_t ≥ 0` and inverse `Z = 2+n_d+n_t`, `A = 4+2n_d+3n_t`).  
3. Validate R2 numeric identity `A₁ = π R_p²`.  
4. Smoke-check packing: for He-4 / C-12 / O-16 / Fe-56, `packNucleus` nucleon
   count = `A` and proton count = `Z` (Node or extracted JS).  
5. Publish rule ledger; park NP12 RMS path as **WRONG_OBSERVABLE** for this
   construction (QED charge radius ≠ sequencer boundary/enmeshment).

## 3. Claims

| ID | Claim |
|---|---|
| NSEQ01-C1 | R1–R8 ledger published with source anchors. |
| NSEQ01-C2 | Grammar identity PASS on all sequencer isotope rows. |
| NSEQ01-C3 | `A₁ = π R_p²` PASS. |
| NSEQ01-C4 | Packing smoke: nucleon/proton counts match `A`/`Z` on stated set. |
| NSEQ01-C5 | NP12 IAEA-RMS path labelled **WRONG_OBSERVABLE** relative to sequencer physics (not EXCLUDED for packing). |
| NSEQ01-C6 | No κ fit; no IAEA RMS gate; no `laws.hpp` edit. |

## 4. Next after freeze

Shadow-union BE reproduction against AME (or sequencer’s own BE column) as a
**separate** investigation with κ policy pre-registered — not this loop.
