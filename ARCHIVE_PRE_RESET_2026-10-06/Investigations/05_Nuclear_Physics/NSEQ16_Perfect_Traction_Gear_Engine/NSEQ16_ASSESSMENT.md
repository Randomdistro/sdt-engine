# NSEQ16 Assessment — Atomicus Contact Construction

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-16  
**Classification:** `ATOMICUS_CONTACT_CONSTRUCTION_CANDIDATE`  
**Canonical promotion:** None

## Result

The repaired browser instrument passed R0–R9 across H-1, H-2, H-3, He-4,
Li-7, Be-9, B-11, C-12, N-14 and O-16.

- Inventory, grammar and constitutional alpha/deuteron/triton module counts:
  pass.
- Alpha equatorial-plane and polar-axis checks: pass.
- Li through O select successive whole-atom valence stages; no nuclear module
  carries an element identity.
- Valence-stage spherical-code controls: maximum residual `0`.
- Realised constitutional module centres close on those seats to
  `1.57e-16`; the proton-centre control departs by as much as `0.3275`.
  The construction pattern is therefore not merely a proton-count seat label.
- Contact graph: connected, bipartite and entirely proton-neutron.
- Unlisted overlaps and like-like rim contacts: `0`.
- Maximum `2R_p` contact-distance residual: `4.440892099e-16`.
- Maximum normalized contact-point slip: `0`.
- Common-period closure residual: `2.449293598e-16`.
- Cyclic `(4,5)` four-lap closure residual: `3.955741861e-16 R_p`.
- Every lap contains one full local twist plus one-lane advance; the tour
  sequence is inner, under, outer, over.
- Möbius control: director reversed exactly at `2pi` and closed at `4pi`.
- Same-handed transverse rejection control: normalized slip `2`.
- Repeated whole-range construction: byte-stable fingerprints.

## Comparison with NSEQ05

NSEQ05 remains available as `LEGACY_GEOMETRIC_CONTROL`; it is not silently
deleted. The frozen comparison rejects it because its stored nearest-neighbour
links miss `2 R_p` by as much as `0.5827 R_p`, its generated tiers do not
supply an alpha-defined polar axis, and it records no construction order. It
cannot serve as the live Atomicus contact-construction engine.

## Public sequencer integration

The NSEQ16 construction is now the default route in
`nuclear-packing-sequencer.html` for the registered He-4, Li-7, Be-9, B-11,
C-12, N-14 and O-16 stages. The sequencer:

- reveals constitutional modules in NSEQ16 construction order;
- renders every nucleon as one continuous `(4,5)` filament split into four
  tail-to-adjacent-lane colour segments;
- closes every ring on one master period while retaining opposite p/n hand;
- shows the internal neutron electron as a `2pi` reversal / `4pi` closure
  Möbius director;
- reports construction, contact, slip, seam and local-speed diagnostics;
- marks all unregistered isotope routes as `NSEQ05-CONTROL-3` rather than
  silently substituting them for Atomicus contact geometry.

The dedicated public-sequencer validator passes S0–S7, including module syntax,
H→O engine metrics, load order, Release/docs parity, and a headless He-4/C-12/
Fe-56 route test.

## Scope

The `(4,5)` cyclic quadruple helix is a closed kinematic candidate with the
requested inner/under/outer/over sequence and adjacent-lane seam. It is not
identified with the canonical `(2,3)` trefoil; the latter remains a separate
topology control.

The displayed interleave count is a geometric ledger only. NSEQ16 supplies no
conversion from shared contact geometry to measured mass-defect energy, so
the page marks that conversion `PENDING` and reports no MeV prediction.

The internal Möbius director is likewise a kinematic orientation control. It
does not establish an electron force or authorize a change to the electronic
structure rules.

The selected internal module axes are deterministic maximum-clearance search
solutions, not measured angles. The proton-centre and module-centre routes are
two readings of the same contact graph and are shared-input, not independent.

Use NSEQ16 as the nuclear sequencer's contact-construction candidate. No
geometry, energy or mass-defect formula is promoted into
`Engine/include/sdt/laws.hpp`.

## Reproduction

```powershell
python .\Investigations\05_Nuclear_Physics\NSEQ16_Perfect_Traction_Gear_Engine\nseq16_traction_validate.py
python .\Investigations\05_Nuclear_Physics\NSEQ16_Perfect_Traction_Gear_Engine\nuclear_sequencer_validate.py
```
