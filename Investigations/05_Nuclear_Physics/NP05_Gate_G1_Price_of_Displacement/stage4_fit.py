"""CQ-32 Stage 4 — declared fallback gate G4.  Q = -(P*dV + sigma*dA).
Calibrate (P, sigma) by least squares on R1-R4 [CALIBRATED(2)]; PREDICT R5-R8 blind; G4 if all |err|<=15%.
Reads sealed answers (R1) only here."""
import json, os
HERE=os.path.dirname(os.path.abspath(__file__))
ga=json.load(open(os.path.join(HERE,'volumes_areas.json')))
Q=json.load(open(os.path.join(HERE,'sealed','answers.json')))['Q_values_MeV']
V={k:ga[k]['V'] for k in ga}; A={k:ga[k]['A'] for k in ga}

reactions={'R1_dd_to_a':(['d','d'],['a']),'R2_tp_to_a':(['t','p'],['a']),
 'R3_hn_to_a':(['h','n'],['a']),'R4_dt_to_an':(['d','t'],['a','n']),
 'R5_dd_to_tp':(['d','d'],['t','p']),'R6_dd_to_hn':(['d','d'],['h','n']),
 'R7_ad_to_Li6':(['a','d'],['Li6']),'R8_2an_to_Be9':(['a','a','n'],['Be9'])}
def d(prop,L,R): return sum(prop[x] for x in R)-sum(prop[x] for x in L)
dV={k:d(V,*reactions[k]) for k in reactions}; dA={k:d(A,*reactions[k]) for k in reactions}

# least squares on calibration set: minimize sum (Q_i + P*dV_i + sigma*dA_i)^2
cal=['R1_dd_to_a','R2_tp_to_a','R3_hn_to_a','R4_dt_to_an']
# design: x=[P,sigma]; rows m_i=[dV_i,dA_i]; target b_i=-Q_i
Sxx=Sxy=Syy=Sxb=Syb=0.0
for k in cal:
    x,y,b=dV[k],dA[k],-Q[k]
    Sxx+=x*x; Sxy+=x*y; Syy+=y*y; Sxb+=x*b; Syb+=y*b
det=Sxx*Syy-Sxy*Sxy
P=(Sxb*Syy-Syb*Sxy)/det; sigma=(Sxx*Syb-Sxy*Sxb)/det
print(f"calibrated on R1-R4:  P={P:.5f} MeV/fm^3   sigma={sigma:.5f} MeV/fm^2")
print(f"{'reaction':14s} {'Q_act':>8s} {'Q_pred':>8s} {'err%':>8s}  set")
ok=True
for k in reactions:
    qp=-(P*dV[k]+sigma*dA[k]); err=100*(qp-Q[k])/Q[k]
    tag='cal' if k in cal else 'PREDICT'
    if tag=='PREDICT' and abs(err)>15: ok=False
    print(f"{k:14s} {Q[k]:8.3f} {qp:8.3f} {err:+8.1f}  {tag}")
print(f"\nGATE G4 (R5-R8 within +-15%): {'PASS' if ok else 'FAIL'}")
