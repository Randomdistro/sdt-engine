# GOM15 — Term Readjustment: the drive chain, twelfths, and octaves.
# J. C. Harvey directive, executed 2026-07-05. RUN_LOG committed before this file.
# STANDING RULE: no GM/G/M anywhere in-chain. koppa = 4*pi^2*a^3/(T^2*c^2) — kinematic only.
import math
PI = math.pi
c  = 299792458.0                       # m/s, SI exact
DAY = 86400.0

# ---------- dependents: (name, a [m], T [days]) — JPL/IAU reference values (declared) ------
SOL_DEPS = [("Mercury",5.7909e10,87.9691),("Venus",1.08209e11,224.701),
    ("Earth",1.49598e11,365.25636),("Mars",2.27939e11,686.980),
    ("Jupiter",7.7857e11,4332.589),("Saturn",1.43353e12,10759.22),
    ("Uranus",2.87246e12,30688.5),("Neptune",4.49506e12,60182.0)]
JUP_DEPS = [("Amalthea",1.8140e8,0.49818),("Io",4.2170e8,1.769138),
    ("Europa",6.7090e8,3.551181),("Ganymede",1.07040e9,7.154553),("Callisto",1.88270e9,16.689018)]
SAT_DEPS = [("Mimas",1.8552e8,0.942422),("Enceladus",2.3802e8,1.370218),
    ("Tethys",2.9466e8,1.887802),("Dione",3.7740e8,2.736915),("Rhea",5.2704e8,4.517500),
    ("Titan",1.221870e9,15.945421),("Iapetus",3.56130e9,79.3215)]
SAT_RINGS = [("B-ring inner",9.2000e7),("A-ring outer",1.36775e8)]  # ring edge radii [m]

def koppa(a,Td): return 4*PI*PI*a**3/((Td*DAY)**2*c*c)

BODIES = {
 "Sol":    dict(R=6.957e8,  rot=[("Carrington",25.38*DAY),("equatorial",24.47*DAY)],
                kop_src="Earth", deps=SOL_DEPS, extra=[]),
 "Jupiter":dict(R=7.1492e7, rot=[("SystemIII",35729.71)],
                kop_src="Io", deps=JUP_DEPS, extra=[]),
 "Saturn": dict(R=6.0268e7, rot=[("Voyager",38362.4),("Cassini",38018.0)],
                kop_src="Titan", deps=SAT_DEPS, extra=SAT_RINGS),
}

def near_octave(X, d):
    """nearest rung of ladder X*2^n to distance d: returns (n, rung, dev)"""
    n = round(math.log2(d/X)); rung = X*2**n
    return n, rung, (d-rung)/rung

print("="*100)
print(" GOM15 - drive chain / twelfths / octaves.  koppa KINEMATIC (4pi^2 a^3 / T^2 c^2). No GM anywhere.")
print("="*100)

for bname, B in BODIES.items():
    deps = B["deps"]; R = B["R"]; D = 2*R; C = PI*D
    # koppa from every dependent; primary = declared source; spread reported
    kops = [(n, koppa(a,T)) for n,a,T in deps]
    kop_primary = dict((n,k) for n,k in kops)[B["kop_src"]]
    kvals=[k for _,k in kops]; kmean=sum(kvals)/len(kvals)
    spread = (max(kvals)-min(kvals))/kmean*100
    print(f"\n{'#'*100}\n# {bname}:  koppa({B['kop_src']}) = {kop_primary:.6g} m   "
          f"[all-dependent mean {kmean:.6g}, spread {spread:.3f}% - two-body/rounding residuals]")
    kop = kop_primary
    ut = kop/c
    print(f"#   unit length = kop = {kop:.6g} m   unit time = kop/c = {ut:.6e} s")
    print(f"#   sprocket rate w = c/kop = {c/kop:.6g} rad-equiv/s   sprocket turn = 2*pi*kop/c = {2*PI*kop/c:.6e} s")
    print(f"#   R = {R:.6g}  D = {D:.6g}  C = {C:.6g} m;   in kop units: R/kop = {R/kop:.6g}, D/kop = {D/kop:.6g}, C/kop = {C/kop:.6g}")
    print(f"#   gear ratio (surface circumf / sprocket circumf) = C/(2*pi*kop) = {C/(2*PI*kop):.6g} (= R/kop)")
    print(f"#   z_surf = kop/R = {kop/R:.6e}   k_surf = 1/sqrt(z) = {math.sqrt(R/kop):.6g}")
    print(f"#   light crossings: radial R/c = {R/c:.4f} s  diametric D/c = {D/c:.4f} s   (= {R/kop:.6g} / {D/kop:.6g} kop-times)")

    # rotation vs diameter
    print(f"#   --- rotation vs diameter (crossings per rotation N = T_rot*c/D; vs native dimensionless set) ---")
    for rname, T_rot in B["rot"]:
        N = T_rot*c/D
        cand = {"R/kop": R/kop, "k_surf": math.sqrt(R/kop), "2R/kop": D/kop, "C/kop": C/kop}
        best = min(cand.items(), key=lambda kv: abs(N/kv[1]-1))
        print(f"#   {rname:11s} T={T_rot:.6g} s  N_diam={N:.6g}  N_rad={2*N:.6g}"
              f"   nearest native: {best[0]} = {best[1]:.6g}  dev {100*(N/best[1]-1):+.2f}%")

    # twelfths
    print(f"#   --- chain twelfths (variant-a: k*2*pi*kop/12 chain per sprocket division; variant-b: k*D/12) ---")
    tw_a = [(k, k*2*PI*kop/12) for k in range(1,13)]
    tw_b = [(k, k*D/12)        for k in range(1,13)]
    for k,d in tw_a:
        print(f"#     a k={k:2d}: {d:.6g} m  ({d/kop:.4f} kop)")
    # Analysis I: octaves of R, D, C vs the twelfths (both variants)
    for label, X in (("R",R),("D",D),("C",C)):
        rowsA = [(k, d, *near_octave(X,d)) for k,d in tw_a]
        rowsB = [(k, d, *near_octave(X,d)) for k,d in tw_b]
        hitsA = [f"k={k}:2^{n}{dev*100:+.1f}%" for k,d,n,r,dev in rowsA if abs(dev)<=0.02]
        hitsB = [f"k={k}:2^{n}{dev*100:+.1f}%" for k,d,n,r,dev in rowsB if abs(dev)<=0.02]
        medA = sorted(abs(dev) for *_ ,dev in rowsA)[len(rowsA)//2]
        medB = sorted(abs(dev) for *_ ,dev in rowsB)[len(rowsB)//2]
        print(f"#   Analysis-I octaves of {label}: twelfths-a median|dev| {medA*100:.1f}%  hits<=2%: {hitsA or 'none'}")
        print(f"#                         : twelfths-b median|dev| {medB*100:.1f}%  hits<=2%: {hitsB or 'none'}")

    # Analysis II: octaves of R, D, C vs dependent orbits (+ring edges) — null median 19.05%
    targets = [(n, a) for n,a,_ in deps] + B["extra"]
    print(f"#   --- Analysis-II: octave rungs vs dependent distances (null: median|dev| ~19.05%) ---")
    for label, X in (("R",R),("D",D),("C",C)):
        rows = [(n, a, *near_octave(X,a)) for n,a in targets]
        med = sorted(abs(dev) for *_ ,dev in rows)[len(rows)//2]
        print(f"#   {label} as base: median|dev| = {med*100:.2f}%")
        for n,a,oct_n,rung,dev in rows:
            flag = "  <-- NOTABLE(<=2%)" if abs(dev)<=0.02 else ""
            print(f"#      {n:12s} a={a:.5g}  nearest {label}*2^{oct_n:+d}={rung:.5g}  dev {dev*100:+6.2f}%{flag}")

# informational comparison column ONLY (labelled): GR writes GM/c^2 for the same length.
print("\n# [informational comparison only - RIVAL COLUMN, not used above]: the kinematic koppas")
print("#  above numerically coincide with what GR calls GM/c^2; no G, M, or GM entered any line.")

# ---- ADJ-1 (pre-run): variant-c twelfths — the closure zk^2=1 cut into depth twelfths ----
print("\n" + "="*100)
print(" ADJ-1: depth twelfths per body — z = n/12  =>  r_n = kop/z = 12*kop/n = kop*k_n^2,  k_n = sqrt(12/n)")
print("="*100)
for bname, B in BODIES.items():
    deps=B["deps"]; R=B["R"]; D=2*R; C=PI*D
    kop = dict(((n, koppa(a,T)) for n,a,T in deps))[B["kop_src"]]
    rows=[(n, 12*kop/n, math.sqrt(12/n)) for n in range(1,13)]
    print(f"\n# {bname} (kop={kop:.6g} m):")
    for n,r,k in rows:
        print(f"#   z={n:2d}/12  r={r:.6g} m ({r/kop:.4f} kop)  k={k:.4f}")
    for label,X in (("R",R),("D",D),("C",C)):
        rr=[(n, r, *near_octave(X,r)) for n,r,_ in rows]
        med=sorted(abs(dev) for *_,dev in rr)[len(rr)//2]
        hits=[f"z={n}/12:2^{on}{dev*100:+.1f}%" for n,r,on,rg,dev in rr if abs(dev)<=0.02]
        print(f"#   Analysis-I(c) octaves of {label}: median|dev| {med*100:.1f}%  hits<=2%: {hits or 'none'}")
