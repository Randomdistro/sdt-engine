# NSEQ18 — Universal Interstitial Nuclear Sequencer

**Author:** James Christopher Tyndall, Melbourne  
**Registered:** 2026-08-16, before NSEQ18 instrumentation  
**Status:** PRE-REGISTERED

## Question

Can the existing Atomicus closure schedule construct every nuclide exposed by
the public sequencer as one connected, perfectly-tractioned proton-neutron
contact machine, while retaining the Hydrogen circulation and producing
unforced mass-defect and magnetic ledgers?

## Frozen inputs

The closure schedule is imported from `sdt::laws::nuclear`:

```text
2 → D6 → 8 → D12 → 20 → T8 → 28 → D12 → 40 → T10 → 50
  → D20 → 70 → T12 → 82 → D30 → 112 → T14 → 126
  → D42 → 168 → T16 → 184
```

The constitutional inventory remains:

```text
n_t = A - 2Z
n_d = 3Z - A - 2
```

No isotope name enters a seat coordinate.

## Seat construction

1. Partial spherical shells begin with the north/south pole dyad.
2. The next runner is equatorial.
3. Four occupied seats re-seat as a tetrahedral operating set.
4. Five occupied seats re-seat as a triangular bipyramid.
5. Six occupied seats close the alternating tropical/equatorial structure.
6. Completed shells are species-pure in the registered order.
7. Later shells occupy interstitial directions inherited from the preceding
   shell's faces or links. They are not independent point clouds.
8. The post-T8 D12 shell is the cuboctahedral edge-midpoint construction:
   three upper, six equatorial and three lower seats, azimuthally offset into
   triangles.
9. Deuteron remainders use the registered counts
   `R(n)=n(n+1)=12,20,30,42`; triton shells use
   `B(n)=2(n+1)=8,10,12,14,16`.
10. A full triton shell changes from the opening radius to the closing radius
    and contracts the structure it supports. Partial triton occupancy does not
    receive the full-shell contraction.

## Contact-rotation gates

- A nucleon is the complete four-tour toroidal circulation, never a point.
- Every listed contact is one physical rim coincidence.
- Contact-point velocity vectors must agree: normalized slip `< 1e-10`.
- Proton-proton and neutron-neutron contact are prohibited, including
  accidental unlisted touches.
- The contact graph must be connected and bipartite.
- Every non-seed unit touches a registered parent interstice.
- No arbitrary radial tier, Fibonacci fallback or post-placement bond is
  permitted.

## Wake and observable gates

Every nucleon uses Hydrogen's closed wake operation. A neutron adds the frozen
seated-electron counter-circulation. The proton and neutron electromagnetic
bridges are frozen before the isotope sweep. No continuous per-isotope
coefficient is permitted.

For each admissible orientation the instrument records:

- split/rejoin and paired-flux residuals;
- maximum relative divergence;
- signed centreline, throat, poloidal, tail, exterior, crown and skirt
  contributions;
- current-integral and far-field magnetic moments;
- wake-interaction work on the fixed `alpha*hbar*c/R_p` scale;
- measured mass defect, dipole moment and quadrupole moment when available;
- absolute and relative residuals.

An orientation that fails geometry or wake conservation is rejected before
observable comparison. All attempted orientations remain in the ledger. A
missing measured observable is reported as unavailable; it is not fabricated.

## Whole-range acceptance

The implementation passes only if:

1. every public sequencer isotope builds deterministically;
2. every build has exactly `A` nucleons and `Z` protons;
3. grammar and species-pure shell order are preserved;
4. the pole/tetrahedron/bipyramid/tropical partial sequence is exact;
5. D12 has the registered `3+6+3` triangular offset;
6. full triton closures contract and partial shells do not;
7. every contact is unlike-type, coincident and no-slip;
8. there are no unlisted touches or floating units;
9. wake conservation and route-agreement tolerances pass;
10. the 3D model contains no text labels;
11. the datasheet exposes calculated, measured and residual values;
12. Release and docs mirrors are byte-identical.

Mandatory spot checks are H-1, H-2, H-3, He-3, He-4, O-16, Ca-48, Fe-56,
Pb-208, U-238 and closures 2, 8, 20, 28, 50, 82, 126 and 184.

