# GD13 — Layered displacement by object: lockstep layers, contact, engulfment

Pre-registration, 2026-10-16. Written before the tool exists and before any field is computed.
Operator method (2026-10-16). The pasted master specification binds the work; repository gateways govern register.

## NO TWEAKING (binding)

No parameter is set, changed or implied after a result. No observed value is a target or calibration. A validation
fault is repaired by dated amendment before any result is reported. Results are reported as computed.

## The Operator's method (verbatim substance)

Forget the Sun: there are hundreds of billions of stars, so the only fair method is by object. For each object
calculate the volume of the stars, and lay that volume through the centre of the object. Displace 100 times that volume
around the centreline, then that volume around the last, each layer on every object put down at the same time (the
first layer everywhere, then the second, then the third) until contact. Contact is when one object's volume and
another's cross over; 50% of each one along the crossover is shunted away to increase the volume in that same shell.
At the next shell everywhere the same crossover is additionally displaced back into that object's layer. Eventually
the spiral arms envelop each other and are engulfed by the bulge's displacement; that squeezes displacement along the
spiral arms as the bulge shares more of the galaxy's displaced volume with the other parts. The arms should dominate:
the bulge radiates away spherically, but an arm is linear and angular and the displacement follows a plate, not a sphere.

## Reading used (decisions the Operator may correct)

R1 Object volume: V_i = N_i V_p, the displaced volume (canon exclusion volume) of the baryons assigned to object i.
   Counts are the GD09b allotment: Sgr A* 5.0×10⁶³ (mass-equivalent), bulge region 1.974×10⁶⁷, long bar 1.225×10⁶⁷, and
   each arm's ±2σ footprint (measured + near-extended ridge). The unallocated 45% of thin-disc and gas baryons, and the thick
   disc, belong to no object and do not displace in this method. They are reported, not hidden.
R2 Layers: layer 0 is V_i laid on the centreline; layer k adds W_i = 100 V_i around the previous layer, outward by
   distance from the centreline; every object advances one layer per step together. After k layers object i has displaced
   B_i(k) = V_i + k W_i.
R3 Geometry (a plane, z-integrated). Each cell has a volume cost (column height × area).
   - Sgr A* and the bulge: point objects at the Galactic centre; spherical layers (cost per plane cell 2d, d the distance).
   - Long bar: plate on the centreline segment, half-length 5.0 kpc at 30.5° from the Sun–centre line toward +x, height 0.36 kpc
     (twice the 180 pc thin-bar scale height).
   - Each arm: plate on the GD08 ridge (flags 1 and 0), height 2σ_z(R) of the nearest ridge node (Reid 2019 rms).
   Plates grow in plane at fixed height. Self-overlap on the inside of a spiral is automatic: each cell is counted once.
R4 Volume depth ψ_i(d) is the cumulative cost of cells within distance d of object i's centreline. The layer surface is
   S_i(d) = dψ_i/dd. Free growth: object i reaches a cell at layer κ_i(x) = max(0, (ψ_i(d_i(x)) − V_i)/W_i).
R5 Contact between objects i and j first occurs at k_c = min over cells of max(κ_i, κ_j), at the cell that attains it.
   Beyond contact the crossover is shared 50/50 and the other 50% of each object's crossover volume is shunted into its own
   layer (thickening the free parts). The crossover volume of object i at layer K is the cost of cells it has reached that
   another object has also reached; its shunt is 50% of that.
R6 Pressure by volume is the shell shift in pitches: f_i(x) = V_i/(S_i(d_i(x)) ℓ_P). Equal volume depth means equal f.
   Where two objects both reach a cell, the one with the larger f takes it (it pushes the other out of the way); the other's
   displaced volume at that cell is shunted into its own free layer. At the end the cell is owned by the object with the
   largest f among the objects that reach it.
R7 End of the process: layer K_end at which every plane cell within 17 kpc of the centre has been reached by at least one
   object, K_end = max over those cells of min_i κ_i. The partition and pressure are read at K_end.

## Observables

O1 Contact timeline: every pair, its k_c, the contact cell and the reach of each object there. The order of contacts
   (arms with arms, bar and bulge with arms) and when each arm is first reached by the bulge or the bar.
O2 End-state ownership by object over R < 17 kpc: plane area, volume cost, and share of the displaced volume.
O3 Radial profile of the owner by class (bulge/Sgr A*, bar, arms) at R = 1…16 kpc and the radius at which the arms'
   combined owned area overtakes the bulge's.
O4 Pressure: f of the owner at each cell. Free pressure of each object along its own centreline; how f falls with distance
   for a sphere (1/d²) and for a plate (constant), measured from ψ.
O5 Crossover and shunt: per object, crossover cost fraction at K_end, shunt volume = 50% of the crossover, and, per arm,
   the crossover fraction on the inner, middle and outer thirds of its ridge (where the squeeze goes).
O6 Superposition comparison: f_total = Σ f_i against the owner's f.

## Classification (pre-registered; every class populated)

"The spiral arms dominate": over owned plane cells with 3 < R < 17 kpc, the arms' combined share of owned area.
Supported if ≥ 50%; marginal if 25–50%; not supported if < 25%.
"Spiral arms are engulfed by the bulge": the fraction of arm ridge nodes whose cell is owned by the bulge at K_end.
Reported for all arms and per arm; no threshold.

## Instrument validation (before use, known answers)

V1 sphere: numerical ψ(d) against 4π d³/3 and S against 4π d² (2%). V2 straight plate segment of length L, height H:
ψ(d) against 2H(2 d L + π d²) (2%), S constant for d ≪ L. V3 two spheres on one axis with volumes V_a, V_b: contact
layer and cell against the analytic arrival condition; equal-f meeting point against the closed form √(V_a/V_b) (2%).
V4 cell partition: owned plane area sums to the region area (1e-9). V5 shell shift: f of the sphere equals V/(4π r² ℓ_P)
(GD12) to 2%.

## Scope

The reading R1–R7 is mine; it fixes what the numbers mean. The layer index is analytic (the closed form), not an
enumeration of ~10⁴⁹ layers; at the cell scale one layer is about 10⁴⁴ times smaller than a cell. Baryons not assigned to an
object do not displace here. The map from pressure to emission position remains open and is not supplied.

## Amendment 1 (2026-10-16, before the tool exists; test formula only)

V2 stated ψ(d) = 2H(2dL + πd²). The plate cost is the full column height H per unit plane area, so the volume depth
of a straight plate of length L is ψ(d) = H (2dL + πd²) and its layer surface is S = H (2L + 2πd) (2HL is the
two-sided limit for d ≪ L). V2 is restated with these. No rule, input or classification changes.

## Amendment 2 (2026-10-16, before any result; numerical resolution only)

The first run stopped at validation. V1 (sphere ψ, S) 2.3%, V5 (shell shift) 3.6%, V2 (plate ψ) 9.2% and (plate S) 34%.
Cause: at 0.1 kpc cells the finite-difference layer surface S = dψ/dd over a ±0.1 kpc band is noisy at the small test
distances (the plate was tested at d = 0.5 kpc, five cells). V3 passed (1.0% and 0.05 kpc). Restated, with no model rule,
input or classification changed: grid 0.05 kpc; differencing band ±0.15 kpc; test distances 2, 4, 8 kpc (sphere) and 1, 2, 3 kpc
(plate, L = 6, H = 0.2); tolerances unchanged (2%; plate S 3%). The reported S, f and ownership are differences over a 0.3 kpc
band, so an object's own pressure is resolved only beyond about 0.15 kpc from its centreline.

## Amendment 3 (2026-10-16, before any result; test geometry only)

After Amendment 2 the sphere and two-sphere tests pass (V1 0.4%, V5 0.5%, V3 1.5% and 0.025 kpc). V2 (plate) ψ is 2.0% and S 16%.
Cause: the straight test plate lay along a grid axis, so its boundaries at d = 1, 2, 3 kpc coincided with cell-centre rows;
the "cells within d" count then includes half a row of cells too many (about +2% of ψ), and the differencing amplifies it into S.
The arms are curved and carry no such alignment. V2 is restated with the plate rotated by 17° from the grid axis; tolerances
(2% for ψ, 3% for S) and distances unchanged.

## Amendment 4 (2026-10-16, after the first complete run; informational additions, nothing replaced)

First complete run (grid 0.05 kpc): all validations consistent; K_end = 3.03×10⁴⁹ layers; end-state ownership is dominated by
one arm (Sct-Cen, 92% of the owned area) because a plate's free pressure V/(S ℓ_P) scales as 1/(L H) and Sct-Cen has the thinnest
plate; O5 at K_end returns a crossover fraction of 1.0 for nearly every object because by K_end every object has reached
every other. Those results stand as computed. Two informational outputs are added, each reported beside the registered ones:
(a) for every ridge node, the layer at which another object first reaches the node's cell (and which object), and the layer at
which the bulge sphere's front reaches it, summarised on the inner, middle and outer thirds of each ridge;
(b) the crossover fraction of each object at the layer checkpoints 10⁴⁷, 10⁴⁸, 10⁴⁹ and K_end.
No rule, input, threshold or classification changes. No variant of the plate height is run.

## Amendment 5 (2026-10-16, domain extent only; both runs are kept and reported)

Run A (grid half-width 20 kpc, 0.05 kpc cells; kept as `*_domain20.*`) gave: K_end = 3.03×10⁴⁹; ownership over R < 17 kpc: Sct-Cen
92.2%, long bar 4.1%, Norma 3.3%, bulge 0.4%, 3-kpc 0.07%, all other objects 0; arms 95.5% of the owned area; classification
"arms dominate" 0.973 → supported; the bulge owns none of the 2640 ridge nodes; first contacts: bar–Norma 7.0×10⁴⁵, first arm–arm
(Norma–Sct-Cen) 2.6×10⁴⁷, bulge–Sct-Cen 1.4×10⁴⁸, bulge–Outer 5.8×10⁴⁹.
Artefact identified in that run: the plate layer surface S is the perimeter of the offset curve; the finite grid clips it at
distances beyond about 12–20 kpc from a ridge, which shrinks S and inflates f (Perseus and Outer show f rising with d, which a
physical perimeter cannot do). The ownership at large d, and Sct-Cen's share in particular, depend on that region.
Run B is the same program with the grid half-width raised to 40 kpc (cell 0.0625 kpc), so the offset curves are complete out to
R = 17 kpc plus ~23 kpc of margin. Nothing else changes: objects, rules R1–R7, thresholds, classification, region (R < 17 kpc).
Run B supersedes Run A for statements about large d; both are reported. No variant of plate height is run.

### Amendment 5, outcome (2026-10-16, after Run B)

Run B (grid 1281², cell 0.0625 kpc, half-width 40 kpc; validations V1–V5 all consistent): K_end = 3.249×10⁴⁹; ownership over R < 17 kpc:
Sct-Cen 92.2%, long bar 4.1%, Norma 3.3%, bulge 0.39%, 3-kpc 0.08%, all other objects 0; arms 95.5% of the owned area; "arms
dominate" 0.9728 → supported; 0 of 2640 ridge nodes owned by the bulge or Sgr A*. These match Run A to the quoted digits.
The grid-clipping hypothesis stated above is therefore NOT supported for the ownership: widening the domain left the partition
unchanged. It is supported for one object only: Outer's f at d = 8 kpc no longer rises (Run B 6.4×10²; falls with d). Perseus's f
still rises between d = 4 and 8 kpc (1.07×10³ → 1.13×10³) at 40 kpc half-width, so that rise is not a clipping effect; it follows from
the offset curve of a tightly wound spiral overlapping itself (the perimeter of the union shrinks). Run A is kept as `*_domain20.*`.
Run B is the registered output (`run_output.txt`, `gd13_contacts.csv`, `gd13_ridge_owner.csv`, `mw_layers.js`).
Process fault recorded: the executable terminated abnormally (exit code 0xC0000409) in 2 of 3 consecutive runs of the first Run B build, at differing
points (during validation and during object construction), and in one earlier run at 20 kpc. After adding stdout unbuffering and an exception
handler it completed in 12 of 12 runs with byte-identical output. Cause not identified (the handler caught nothing). Outputs are
reported only from completed runs; a crashed run produces no result.
