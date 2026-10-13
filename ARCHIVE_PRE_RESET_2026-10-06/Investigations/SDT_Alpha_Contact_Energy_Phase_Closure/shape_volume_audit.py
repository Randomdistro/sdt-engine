"""Conditional volume ledger; no claimed reconstruction of operator wire shape."""
import json, math
from pathlib import Path

HERE = Path(__file__).resolve().parent
a0 = 5.29177210903e-11
Rp = 0.8414e-15
de = 6e-20  # native OPEN body radius 3e-20 m, converted to diameter
Le = 4 * math.pi * a0
rows = []
for nsteps in (4096, 8192, 16384):
    # Existing H1 geometry only: four toroidal tours, cross-section count three.
    R = 5.28e-15 / (2 * math.pi)
    a = .06e-15 / math.sqrt(2)
    length = sum(math.sqrt(16*(R+a*math.cos(3*(i+.5)*2*math.pi/nsteps))**2+9*a*a)
                 for i in range(nsteps)) * 2 * math.pi / nsteps
    for name, L in [('H1_4_3_control', length), ('four_circular_major_tours_control', 8*math.pi*Rp)]:
        for species, N in [('proton',1836), ('neutron',1387)]:
            V = N * math.pi * de*de * Le / 4
            d = de * math.sqrt(N*Le/L)
            rebuilt = math.pi*d*d*L/4
            rows.append(dict(samples=nsteps, length_model=name, species=species,
                             multiplier=N, length_fm=L*1e15, volume_fm3=V*1e45,
                             equivalent_diameter_fm=d*1e15,
                             volume_relative_residual=abs(rebuilt/V-1)))
result = dict(status='CONDITIONAL_VOLUME_IDENTITY; specified double-trefoil length unresolved',
              point_electron_diameter_m=de, initial_orientation_closure_length_m=Le,
              initial_body_radius_status='native OPEN input, not independently derived',
              simultaneous_union_status='OPEN: 720-degree traversal may repeat spatial locus',
              equal_length_neutron_proton_diameter_ratio=math.sqrt(1387/1836),
              single_spatial_lap_diameter_factor=1/math.sqrt(2),
              diameter_3e_minus20_sensitivity_factor=.5,
              corrected_speed_record_c=[.395,1.84,2.23], rows=rows)
(HERE/'SHAPE_VOLUME_RESULTS.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result,indent=2))
