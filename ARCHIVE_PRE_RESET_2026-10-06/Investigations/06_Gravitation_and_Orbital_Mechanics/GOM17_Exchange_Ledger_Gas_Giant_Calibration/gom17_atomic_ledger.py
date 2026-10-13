# GOM17 PART D - the SAME exchange ledger against the atoms H..Ne (Harvey's order, 2026-07-06).
# RUN_LOG ADJ-2 committed BEFORE this file. No G/M; NO QM machinery (no psi, no orbitals, no
# imported closed forms). Dependents = measured IONIZATION ENERGIES (NIST ASD, reference-memory,
# 4-7 s.f., declared). Chain: v_n = sqrt(2 IE_n / m_e), k_n = c/v_n, z_n = v_n^2/c^2.
# IDENTITY FLAG (committed): the virial route re-expresses what spectroscopy encodes - earned
# content = the cross-scale ledger parallel + drift/screening structure, not the IE values.
import math
c      = 299792458.0
RY     = 13.605693123          # eV  - measured spectroscopic anchor (R_inf * hc)
MEC2   = 510998.950            # eV  - the m_e seat (FLM13)
ALPHA  = 7.2973525693e-3       # measured; PPT02 role: k = 137.036 at H ground
U_ME   = 1822.888486           # u / m_e (measured mass-ratio anchor)
# NIST ASD ionization energies, eV, stages in removal order (neutral -> bare). Reference-memory.
IE = {
 "H" : [13.598434599702],
 "He": [24.587389011, 54.417765486],
 "Li": [5.391714996, 75.640097, 122.45435913],
 "Be": [9.322699, 18.211153, 153.896205, 217.71858459],
 "B" : [8.298019, 25.15483, 37.93058, 259.3715, 340.2260225],
 "C" : [11.2602880, 24.383154, 47.88778, 64.49352, 392.090518, 489.993198],
 "N" : [14.53413, 29.60125, 47.4453, 77.4735, 97.8901, 552.06733, 667.046121],
 "O" : [13.618055, 35.12112, 54.93554, 77.41350, 113.8990, 138.1189, 739.32683, 871.409898],
 "F" : [17.42282, 34.97081, 62.70798, 87.175, 114.249, 157.16311, 185.1868, 953.89805, 1103.11748],
 "Ne": [21.564540, 40.96297, 63.4233, 97.1900, 126.247, 157.934, 207.271, 239.0970, 1195.80784, 1362.19916]}
ZS = {"H":1,"He":2,"Li":3,"Be":4,"B":5,"C":6,"N":7,"O":8,"F":9,"Ne":10}
# nuclear mass / m_e: measured atomic masses (u) minus Z electrons (binding negligible, declared)
AMU = {"H":1.00782503207,"He":4.002602,"Li":7.0160034,"Be":9.0121831,"B":11.0093054,
       "C":12.0,"N":14.0030740,"O":15.9949146,"F":18.99840316,"Ne":19.99244018}
MNUC = {el: AMU[el]*U_ME - ZS[el] for el in IE}
print("="*100)
print(" GOM17 PART D - ATOMIC EXCHANGE LEDGER (H..Ne). Same ledger, twenty orders down.")
print(" v_n = sqrt(2 IE_n/m_e); k = c/v; z = v^2/c^2. No QM machinery; measured numbers only.")
print("="*100)

# ---------- D1: hydrogenic anchor - final stage vs Z^2 Ry; the drift curve ----------
print("\n--- D1. hydrogenic anchor: drift(Z) = IE_final/(Z^2*Ry) - 1  [units e-4] ---")
print(f" {'el':3s} {'Z':>2s} {'IE_final eV':>12s} {'drift e4':>9s} {'depth (Za)^2/4':>14s} {'-me/M_nuc':>10s} {'pred e4':>8s} {'resid e4':>9s}")
resids=[]
for el,Z in ZS.items():
    drift = IE[el][-1]/(Z*Z*RY) - 1.0
    depth = (Z*ALPHA)**2/4.0
    selfp = -1.0/MNUC[el]
    pred  = depth + selfp
    resids.append((el,Z,drift,depth,selfp,pred,drift-pred))
    print(f" {el:3s} {Z:2d} {IE[el][-1]:12.5f} {drift*1e4:9.3f} {depth*1e4:14.3f} {selfp*1e4:10.3f}"
          f" {pred*1e4:8.3f} {(drift-pred)*1e4:9.3f}")
g1a = all(d<0 for el,Z,d,*_ in resids if Z<=2) and all(d>0 for el,Z,d,*_ in resids if Z>=3)
g1b = all(abs(r)<=0.25*abs(d) for el,Z,d,de,s,p,r in resids if Z>=4)
sgn = set(r<0 for el,Z,d,de,s,p,r in resids if Z>=4)
print(f" D-GATE-1(a) sign structure (Z<=2 neg, Z>=3 pos): {'PASS' if g1a else 'FAIL'}")
print(f" D-GATE-1(b) Z>=4 drift within 25% of [(Za)^2/4 - me/M]: {'PASS' if g1b else 'FAIL'}")
print(f" D-GATE-1(c) residual sign uniform Z>=4: {'PASS (all negative)' if sgn=={True} else ('PASS (all positive)' if sgn=={False} else 'FAIL (mixed)')}")
print(" Reading: the drift curve = movement-budget depth term (Zalpha)^2/4 (Law V class - the")
print(" atomic analog of the oblate-shadow form term, growing with depth) MINUS the dependent's")
print(" own shadow me/M. The uniform ~-10% residual = the measured radiative reduction (route-")
print(" geometry class, FLM14) - carried OPEN, not fitted.")

# ---------- D2: THE self-term parallel (one bookkeeping, twenty orders apart) ----------
print("\n--- D2. the self-term: same two-body ledger line at both scales ---")
print(" extracted self(Z) = drift - (Za)^2/4  vs  -me/M_nucleus:")
for el in ("H","He","Li"):
    Z=ZS[el]; drift=IE[el][-1]/(Z*Z*RY)-1.0; ext=drift-(Z*ALPHA)**2/4.0; tgt=-1.0/MNUC[el]
    print(f"  {el:3s} extracted {ext*1e4:8.3f} e-4   target -me/M = {tgt*1e4:8.3f} e-4   miss {abs(ext/tgt-1)*100:5.1f}%")
h_ok  = abs((IE['H'][-1]/RY-1-ALPHA**2/4)/(-1/MNUC['H'])-1)  <=0.05
he_ok = abs((IE['He'][-1]/(4*RY)-1-(2*ALPHA)**2/4)/(-1/MNUC['He'])-1)<=0.15
print(f" D-GATE-2: H within 5%: {'PASS' if h_ok else 'FAIL'};  He within 15%: {'PASS' if he_ok else 'FAIL'};  Li reported (unmodeled next order).")
print("\n  CROSS-SCALE PARALLEL TABLE (dependent's own shadow in the two-body closure):")
print(f"  {'pair':16s} {'dependent':10s} {'self-term':>12s}  ledger side")
print(f"  {'Sun-Jupiter':16s} {'Jupiter-sys':10s} {'+9.547e-4':>12s}  pair-SUM  (row above clean parent; GOM17 B/C)")
print(f"  {'Sun-Saturn':16s} {'Saturn-sys':10s} {'+2.859e-4':>12s}  pair-SUM  (kinematic, own moons)")
print(f"  {'Earth-Moon':16s} {'Moon':10s} {'+1.230e-2':>12s}  pair-SUM  (barycentre split 4671 km)")
for el in ("H","He","Li"):
    Z=ZS[el]; ext=IE[el][-1]/(Z*Z*RY)-1.0-(Z*ALPHA)**2/4.0
    lab={"H":"p-e","He":"alpha-e","Li":"Li7-e"}[el]
    print(f"  {lab:16s} {'electron':10s} {ext*1e4:+9.3f}e-4  pair-SHARE (measured line below the infinite-parent ideal)")
print("  One bookkeeping: the pair carries the dependent's own shadow at first order = the")
print("  mass/koppa ratio. Planetary (a,T) rows read the pair's SUMMED shadow (+); atomic energy")
print("  rows read the pair's SHARED movement (-). Twenty orders apart, same ledger line.")

# ---------- D3: enclosed-count / screening ledger ----------
print("\n--- D3. enclosed-count ledger: Z_eff,j = t*sqrt(IE_j/Ry); t = 1 if (Z-j+1)<=2 else 2 ---")
mono_all=True; zeff1={}
for el,Z in ZS.items():
    zs=[]
    for j,ie in enumerate(IE[el],start=1):
        t = 1 if (Z-j+1)<=2 else 2
        zs.append(t*math.sqrt(ie/RY))
    mono = all(b>a for a,b in zip(zs,zs[1:])); mono_all &= mono
    zeff1[el]=zs[0]
    print(f"  {el:3s} Z={Z:2d} Z_eff: " + " ".join(f"{z:6.3f}" for z in zs) + f"   monotone: {'PASS' if mono else 'FAIL'}")
print(f" D-GATE-3(a) monotone within every atom: {'PASS 10/10' if mono_all else 'FAIL'}")
row2=["Li","Be","B","C","N","O","F","Ne"]
mx = max(row2, key=lambda e: zeff1[e])
print(f" D-GATE-3(b1) absolute reach Z_eff,1 across row 2: " +
      " ".join(f"{e}:{zeff1[e]:.3f}" for e in row2))
print(f"              largest = {mx}: {'PASS (Ne shell closure = deepest outer seat)' if mx=='Ne' else 'FAIL'}")
print(f" D-GATE-3(b2) enclosure FRACTION Z_eff,1/Z (report line): " +
      " ".join(f"{e}:{zeff1[e]/ZS[e]:.3f}" for e in row2))
print("              The fraction FALLS along the row (each added same-tier electron shadows")
print("              at ~0.35 < 1, so absolute reach grows while the fraction of the full nuclear")
print("              shadow falls). Reported as found - no stretching.")
print(" Screening structure (found, native reading OPEN): dips in Z_eff,1 at B (1.562 < Be) and")
print(" at O (2.001 < N) - the subshell step and the pairing step, visible in the raw ledger.")

# ---------- D4: the exchange table for each neutral atom's outermost seat ----------
print("\n--- D4. exchange table, outermost seat of the neutral atom (the atomic gearing rungs) ---")
print(f"  {'el':3s} {'IE_1 eV':>9s} {'z_t = z_d':>11s} {'k = c/v':>9s}")
for el,Z in ZS.items():
    z1 = 2*IE[el][0]/MEC2
    print(f"  {el:3s} {IE[el][0]:9.4f} {z1:11.4e} {1/math.sqrt(z1):9.3f}")
k_meas = 1.0/math.sqrt(2*IE["H"][0]/MEC2)
k_pred = (1.0/ALPHA)*math.sqrt(1.0+1.0/MNUC["H"])/math.sqrt(1.0+ALPHA**2/4.0)
print(f"  D-GATE-4 anchor: k_seat(H) measured = {k_meas:.4f};  (1/alpha)*sqrt(1+me/mp)/sqrt(1+a^2/4) = {k_pred:.4f}")
print(f"           relative miss = {abs(k_meas/k_pred-1):.2e}  gate <=2e-5: {'PASS' if abs(k_meas/k_pred-1)<=2e-5 else 'FAIL'}")
print("           = the PPT02 anchor 137.036 carrying HALF the self-term + the depth term -")
print("           the same ledger line, third appearance. Residence:release = 1:2 holds here too")
print("           (IE is the release cost of a seat holding half its release requirement).")
print("\n done. exit 0")
