# GOM41 Round 2 post-seen diagnostic (2026-10-14), run after stage 2. Not gated.
# Purpose: V1 missed its 1.5% gate for Jupiter (1.518%). How much does the choice of satellite move Q1 J2 for each body, in units of the 3% / 10% gates?
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
import gom41_reset_2 as g
sats = g.sat_rows(); phys = g.jpl_phys()
meas = {'Earth': 1082.63e-6, 'Mars': 1960.45e-6, 'Jupiter': 14736e-6, 'Saturn': 16298e-6, 'Uranus': 3343.43e-6, 'Neptune': 3411e-6}   # as unsealed in stage 2
print('Q1 J2 and residual by choice of satellite (primary marked *)')
for b in g.BODIES:
    ae, ap, rv, ph = g.nasa_geom(b); Pspin = phys[b]['prot_d']
    for s in (g.VALID.get(b) or [g.PRIMARY[b]]):
        a, P = sats[s]; q = g.qpar(ae, Pspin, a, P); j = g.J2_Q1(ae, ap, q)
        print(f'  {b:8s} {s:9s}{"*" if s == g.PRIMARY[b] else " "} q {q:.6e}  Q1 J2 {j:.6e}  residual {100*(j-meas[b])/meas[b]:+7.2f} %')
