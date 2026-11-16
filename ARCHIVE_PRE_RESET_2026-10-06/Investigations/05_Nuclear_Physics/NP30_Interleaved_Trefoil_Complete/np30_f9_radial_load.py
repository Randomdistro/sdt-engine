import numpy as np, math
LAD=[("16O",8,16,6,2.711),("40Ca",20,40,11,3.48),("48Ca",20,48,12,3.46),("124Sn",50,124,15,4.677),("208Pb",82,208,18,5.503)]
r=[];cols={nm:[] for nm,*_ in LAD}
for ln in open("SOG_normalized_columns.dat"):
    if ln.startswith("#") or ln.startswith("Radius") or not ln.strip(): continue
    p=ln.split()
    if len(p)<18: continue
    try: rv=float(p[0])
    except: continue
    r.append(rv)
    for nm,Z,A,ci,_ in LAD:
        try: cols[nm].append(float(p[ci-1]))
        except: cols[nm].append(np.nan)
r=np.array(r)

print("== INTERIOR NUCLEON DENSITY (profiles normalized to A -> already matter density) ==")
print(f"{'nuc':>7} {'A':>4} {'rho(0)':>8} {'rho_int':>9} {'window(fm)':>12} {'mean rho':>9}")
res={}
for nm,Z,A,ci,Rrms in LAD:
    v=np.array(cols[nm]); m=~np.isnan(v)
    rr,vv=r[m],v[m]
    Rsharp=math.sqrt(5/3)*Rrms
    lo,hi=1.5,max(Rsharp-2.0,2.0)          # exclude central wiggle + surface (pre-committed)
    w=(rr>=lo)&(rr<=hi)
    rho_int=np.trapezoid(vv[w]*4*np.pi*rr[w]**2,rr[w])/np.trapezoid(4*np.pi*rr[w]**2,rr[w])
    mean=A/((4/3)*np.pi*Rsharp**3)
    res[nm]=(A,vv[0],rho_int,mean)
    print(f"{nm:>7} {A:>4} {vv[0]:>8.4f} {rho_int:>9.4f} {lo:>5.1f}-{hi:<5.1f} {mean:>9.4f}")

ints=[res[nm][2] for nm,*_ in LAD]; A_s=[res[nm][0] for nm,*_ in LAD]
spread=100*(max(ints)-min(ints))/np.mean(ints)
mono=all(ints[i]>ints[i-1] for i in range(1,len(ints)))
OtoPb=100*(res["208Pb"][2]-res["16O"][2])/res["16O"][2]
print(f"\n  spread across ladder: {spread:.1f}%   monotone rising? {mono}   O->Pb change: {OtoPb:+.1f}%")
print(f"  heaviest (208Pb) rho_int={res['208Pb'][2]:.4f} vs 48Ca={res['48Ca'][2]:.4f}  -> Pb denser? {res['208Pb'][2]>res['48Ca'][2]}")

print("\n== PRE-COMMITTED VERDICT ==")
if spread<=8: v="FLAT (<=8%) -> SATURATION confirmed; strong 'borne down' REFUTED"
elif mono and OtoPb>15: v="RISING monotone >15% -> FORK vs saturation; 'borne down' CONFIRMED"
else: v="NON-MONOTONE / in-band -> INCONCLUSIVE by the letter; but see direction below"
print("  "+v)
print(f"  DIRECTION (the physical question): does the interior get denser with mass? -> {'YES' if mono else 'NO'}")

r0=0.8414/((math.pi/math.sqrt(18))**(1/3)); Rs=math.sqrt(5/3)*r0
rho_cp=3/(4*np.pi*Rs**3)
print(f"\n== rho0 side-check (close-pack floor -> MEAN density, not central) ==")
print(f"  r0={r0:.4f} fm -> sharp r0={Rs:.4f} fm -> mean rho = {rho_cp:.4f} nucleons/fm^3")
print(f"  canonical sharp-radius constant r0~1.2 fm -> {3/(4*np.pi*1.2**3):.4f};  measured Pb mean = {res['208Pb'][3]:.4f}")
print(f"  NOTE: central density (~0.16) is a DIFFERENT quantity from mean (~0.138) - diffuse surface. Compare like with like.")
