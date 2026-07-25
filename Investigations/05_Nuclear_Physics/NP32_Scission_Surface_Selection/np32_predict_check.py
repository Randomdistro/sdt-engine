import csv, math, statistics as st
FYDIR="Datasets/nuclear/fission_yields"
SYS=[
 ("U-235","Datasets/nuclear/IAEA_U235_independent_FY.csv",236,"thermal",2.42),
 ("U-233",f"{FYDIR}/IAEA_233U_independent_FY.csv",234,"thermal",2.49),
 ("Pu-239",f"{FYDIR}/IAEA_239Pu_independent_FY.csv",240,"thermal",2.88),
 ("Pu-241",f"{FYDIR}/IAEA_241Pu_independent_FY.csv",242,"thermal",2.94),
 ("Np-237",f"{FYDIR}/IAEA_237Np_independent_FY.csv",238,"fast",2.6),
 ("Am-241",f"{FYDIR}/IAEA_241Am_independent_FY.csv",242,"fast",3.2),
 ("U-238", f"{FYDIR}/IAEA_238U_independent_FY.csv",239,"fast",2.5),
 ("Th-232",f"{FYDIR}/IAEA_232Th_independent_FY.csv",233,"fast",2.3),
]
def massyield(path,energy):
    col=f"independent_{energy}_fy"; Y={}
    with open(path) as f:
        for row in csv.DictReader(f):
            a=int(row["a_daughter"]); v=row.get(col,"").strip()
            if v: Y[a]=Y.get(a,0.0)+float(v)
    return Y
def hump_centroid(Y,lo,hi):
    # mode in window, then yield-weighted centroid over mode +/-8 (smooths odd-even sawtooth)
    w={a:Y.get(a,0) for a in range(lo,hi+1)}
    mode=max(w,key=w.get)
    lo2,hi2=mode-8,mode+8
    num=sum(a*Y.get(a,0) for a in range(lo2,hi2+1)); den=sum(Y.get(a,0) for a in range(lo2,hi2+1))
    return num/den, mode
print(f"{'sys':>7} {'Afiss':>5} {'A_L':>6} {'A_H':>6} {'sum':>6} {'nu_bc':>5} {'nu_lit':>6} {'valley':>7} {'PV':>6}")
rows=[]
for lab,path,Afiss,energy,nulit in SYS:
    Y=massyield(path,energy); mid=Afiss/2.0
    AL,Lm=hump_centroid(Y,70,int(mid)); AH,Hm=hump_centroid(Y,int(mid)+1,175)
    nu_bc=Afiss-(AL+AH)
    valley=sum(Y.get(a,0) for a in (math.floor(mid),math.ceil(mid)))/2
    pv=max(Y.values())/valley if valley else 0
    rows.append((lab,Afiss,AL,AH,nu_bc,nulit,valley,pv))
    print(f"{lab:>7} {Afiss:>5} {AL:>6.1f} {AH:>6.1f} {AL+AH:>6.1f} {nu_bc:>5.1f} {nulit:>6.2f} {valley:>7.4f} {pv:>6.0f}")
def slope(xs,ys):
    n=len(xs);mx=sum(xs)/n;my=sum(ys)/n
    return sum((x-mx)*(y-my) for x,y in zip(xs,ys))/sum((x-mx)**2 for x in xs)
def report(tag,rs):
    xs=[r[1] for r in rs];AH=[r[3] for r in rs];AL=[r[2] for r in rs];NU=[r[4] for r in rs]
    print(f"\n[{tag}] n={len(rs)}")
    print(f"  P1 heavy slope vs A_fiss = {slope(xs,AH):+.3f} (gate<0.25)  A_H {min(AH):.1f}-{max(AH):.1f}")
    print(f"  P2 light slope vs A_fiss = {slope(xs,AL):+.3f} (gate 0.7-1.3)  A_L {min(AL):.1f}-{max(AL):.1f}")
    print(f"  P3 nu_bc range = {min(NU):.1f}-{max(NU):.1f} (gate 1.5-4.0); mean |nu_bc - nu_lit| = {st.mean(abs(r[4]-r[5]) for r in rs):.2f}")
report("ALL 8",rows)
report("excl Th-232 (pre-called P4 outlier)",[r for r in rows if r[0]!="Th-232"])
# P4 check: is Th the shallowest valley / lowest PV?
th=[r for r in rows if r[0]=="Th-232"][0]
fastonly=[r for r in rows if r[0] in ("Th-232","U-238","Np-237","Am-241")]
print(f"\n  P4: Th-232 valley={th[6]:.4f} PV={th[7]:.0f}; fast-set valleys={[round(r[6],4) for r in fastonly]} PV={[round(r[7]) for r in fastonly]}")
print(f"      Th shallowest valley among fast set? {th[6]==max(r[6] for r in fastonly)}  lowest PV? {th[7]==min(r[7] for r in fastonly)}")
