# Chapter 1 — pre-registration of the worked-example instruments

Registered 2026-11-03, before `Textbook/examples/ch01_contact_boundary_continuity.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Scope of the instrument. Three kinds of statement are checked: (a) the exact lattice-geometry facts recorded in `sdt/lattice_structure.hpp` (class GEOMETRY, no physics input) by a second route, explicit vertex coordinates; (b) the engine's volume relations of Law IV and their cell counts, as an implementation-consistency check; (c) the directional reach of nearest-neighbour relay on three regular lattices, by breadth-first search. The identification of the physical medium with any of these networks is not tested (residual R1.3).

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers (quadrature, root finder, compensated sum) on known integrals and roots | as printed by `validate_helpers()` |
| V1 | polyhedron dihedral routine (from vertex coordinates, outward face normals) on the cube $=90^\circ$, octahedron $=\arccos(-1/3)=109.4712206^\circ$, icosahedron $=138.1896851^\circ$ | $10^{-9}$ degrees |
| V2 | breadth-first shell populations (cells at hop distance exactly $n$, $n=1\ldots6$): simple cubic $4n^2+2$, face-centred cubic $10n^2+2$, body-centred cubic $6n^2+2$ | exact |
| V3 | diamond-cubic cell: 8 atoms per cubic cell and nearest-neighbour count 4 found by brute-force search over the 27 neighbouring cells | exact |

If V1–V3 fail the instrument is faulty; no T-result is quoted until it is repaired and re-validated. A recalled reference value that is the suspect is re-derived by an independent route before the instrument is blamed.

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | regular-tetrahedron dihedral from vertex coordinates equals `lattice_structure::dihedral_rad` $=\arccos(1/3)$; its supplement equals `bond_angle_rad` | each within $10^{-14}$ rad | yes — $60^\circ$ or $109.47^\circ$ (the face-angle and supplement confusions) fail |
| T2 | five tetrahedra about an edge leave the deficit $2\pi-5\delta$ of `five_edge_deficit_rad`, and the deficit is positive | within $10^{-14}$ rad; sign positive | yes |
| T3 | twelve unit spheres touching a central unit sphere on an icosahedron: shell centres at circumradius 2, minimum shell-centre separation (by exhaustive search over the 66 pairs) exceeds 2 by `icosa_shell_gap_over_r` | gap within $10^{-13}$ of 0.1029244; gap $>0$ | yes — gap $\le0$ (a closed rigid shell) is the rejected outcome |
| T4 | Boerdijk–Coxeter helix: vertices $P_k=(\rho\cos k\vartheta,\ \rho\sin k\vartheta,\ kh)$ with `bc_radius_over_a`, `bc_twist_rad`, `bc_rise_over_a` give $|P_k-P_{k+j}|=1$ for $j=1,2,3$ and all $k$ tested ($k=0\ldots40$), and $|P_k-P_{k+4}|>1$ | each distance within $10^{-13}$; the $j=4$ distance exceeds 1 | yes — a wrong twist or rise breaks equal edges |
| T5 | diamond-cubic packing fraction by explicit geometry (8 spheres of radius half the nearest-neighbour distance per cubic cell) equals `packing_fraction_diamond` $=\pi\sqrt3/16$; the void fraction is its complement | within $10^{-14}$ | yes |
| T6 | Law IV volume relations agree with the closed forms: `V_disp_p` $=3m_p\ell_P^3c^2/\Phi$, `V_disp_e` likewise, `R_excl_*` $=(3V/4\pi)^{1/3}$, and `mass_from_V_disp(V_disp_p)` returns $m_p$ | each within $10^{-12}$ relative | yes |
| T7 | relay-front reach: after $n$ hops the farthest projection along $\hat u$ is $n\,h_P(\hat u)$ with $h_P$ the support function of the neighbour-vector polytope; the ratio of the largest to the smallest $h_P$ over the directions $[100],[110],[111]$ is $\sqrt3$ (simple cubic), $\sqrt2$ (face-centred), $\sqrt3$ (body-centred) | each ratio within $10^{-12}$ of the exact value; BFS values at $n=6$ equal $6\,h_P$ to $10^{-12}$ | yes — an isotropic front (ratio 1) is the rejected outcome |
| T8 | on the simple cubic lattice the hop distance equals $|x|+|y|+|z|$ for every cell within hop radius 6 | exact, all cells | yes |

T6 is an implementation-consistency check: it shows that the chapter's relations and the engine are the same expressions. The cell counts it prints carry the measured inputs $m_p$, $m_e$, $R_p$, $T_{\rm CMB}$, $R_{\rm CMB}$ and the stored $\ell_P$; its round trip of $m$ through $V_{\rm disp}$ is a relation whose two sides share one input and is labelled CONSTRUCTION in the chapter.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept on record with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch01_contact_boundary_continuity` (compiles with `cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /I Textbook\examples`).
