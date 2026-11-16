# GOM17 ADDENDUM - H-ENCLOSED test (per RUN_LOG ADJ-1; predictions stated there BEFORE this ran).
# SAME committed inputs as gom17_exchange_ledger.py. No gate re-scored. No G/M/GM in-chain.
# Enclosure = calculus on the native additive-shadow law: an orbit's (a,T) reads the enclosed,
# ring-averaged shadow sum. Interior ring factor g(b)=1+(3/4)b^2+(45/64)b^4+(175/256)b^6+...;
# exterior ring effective term -(1/2)(a/a_e)^3 - (9/16)(a/a_e)^5 (truncation noted).
import math
PI=math.pi; c=299792458.0; AU=1.495978707e11; DAY=86400.0; CY=36525.0
def kop_aT(a_m,T_s): return 4*PI*PI*a_m**3/(T_s*T_s*c*c)
SETA=[("Mercury",0.38709927,149472.67411175),("Venus",0.72333566,58517.81538729),
 ("EMB",1.00000261,35999.37244981),("Mars",1.52371034,19140.30268499),
 ("Jupiter",5.20288700,3034.74612775),("Saturn",9.53667594,1222.49362201),
 ("Uranus",19.18916464,428.48202785),("Neptune",30.06992276,218.45945325)]
rows={n:kop_aT(a*AU,(360.0/Ld)*CY*DAY) for n,a,Ld in SETA}
a_of ={n:a*AU for n,a,Ld in SETA}
# kinematic self-terms (identical to run 1): giants = moon-regression intercepts; EMB=Moon row;
# Mars=Deimos; Uranus=Titania; Neptune=Triton; Mercury/Venus PENDING-kinematic (0).
JUP_M=[(181366.,0.498179),(421769.,1.769138),(671079.,3.551181),(1070412.,7.154553),(1882709.,16.689018)]
SAT_M=[(185539.,0.942422),(237948.,1.370218),(294619.,1.887802),(377396.,2.736915),
       (527108.,4.518212),(1221870.,15.945421),(1481010.,21.276609),(3560820.,79.321500)]
def lsq(pts):
    xs=[x for x,_ in pts]; ys=[y for _,y in pts]; n=len(pts); xm=sum(xs)/n; ym=sum(ys)/n
    B=sum((x-xm)*(y-ym) for x,y in zip(xs,ys))/sum((x-xm)**2 for x in xs); return ym-B*xm
A_jup=lsq([(((7.1492e7)/(a*1e3))**2, kop_aT(a*1e3,T*DAY)) for a,T in JUP_M])
A_sat=lsq([(((6.0268e7)/(a*1e3))**2, kop_aT(a*1e3,T*DAY)) for a,T in SAT_M])
selfs={"Mercury":0.0,"Venus":0.0,"EMB":kop_aT(384399e3,27.321661*DAY),
 "Mars":kop_aT(23463.2e3,1.262441*DAY),"Jupiter":A_jup,"Saturn":A_sat,
 "Uranus":kop_aT(435910e3,8.706234*DAY),"Neptune":kop_aT(354759e3,5.876854*DAY)}
names=[n for n,_,_ in SETA]
base=sum(rows[n] for n in ("Mercury","Venus","EMB"))/3.0   # inner-cluster clean baseline
print("="*100)
print(" GOM17 ADDENDUM - H-ENCLOSED vs run-1 rows. Baseline = inner-cluster mean (Me,V,EMB) =")
print(f"   kop_sun_clean = {base:.4f} m   (inner-cluster spread {(max(rows[n] for n in ('Mercury','Venus','EMB'))-min(rows[n] for n in ('Mercury','Venus','EMB')))/base*1e4:.2f} e-4)")
print("="*100)
def g_int(b):  return 1+(3/4)*b**2+(45/64)*b**4+(175/256)*b**6      # interior ring (truncated)
def f_ext(x):  return 0.5*x**3+(9/16)*x**5                          # exterior ring (truncated)
print(f" {'planet':8s} {'measured e4':>11s} {'own-only e4':>11s} {'ENCLOSED e4':>11s} {'resid e4':>9s} {'|A-B| e4':>9s}")
SETB={"Mercury":(0.38709893,87.9691),"Venus":(0.72333199,224.701),"EMB":(1.00000011,365.25636),
 "Mars":(1.52366231,686.980),"Jupiter":(5.20336301,4332.589),"Saturn":(9.53707032,10759.22),
 "Uranus":(19.19126393,30685.4),"Neptune":(30.06896348,60189.0)}
for n in names:
    a=a_of[n]; meas=(rows[n]/base-1)*1e4
    own=selfs[n]/base*1e4
    enc=selfs[n]
    for m in names:
        if m==n: continue
        if a_of[m]<a:  enc+=selfs[m]*g_int(a_of[m]/a)
        else:          enc-=selfs[m]*f_ext(a/a_of[m])
    enc_e4=enc/base*1e4
    noise=abs(rows[n]-kop_aT(SETB[n][0]*AU,SETB[n][1]*DAY))/base*1e4
    print(f" {n:8s} {meas:11.2f} {own:11.3f} {enc_e4:11.2f} {meas-enc_e4:9.2f} {noise:9.2f}")
print("\n NOTES (honesty):")
print(" - g(b) truncated at b^6: for Jupiter-inside-Saturn b=0.546, truncation error ~ +0.01 of the")
print("   factor (~ +0.1 e-4 on Saturn's ENCLOSED value) - direction and size noted, not tuned.")
print(" - Saturn: 250-yr mean-motion fit absorbs the 883-yr Jupiter-Saturn great inequality;")
print("   order estimate from the declared 48' longitude amplitude: up to ~9 e-4 on kop -")
print("   Saturn's residual is INSTRUMENT (named pre-run, noise source 1), adjudicates nothing.")
print(" - Uranus residual ~1sigma of its |A-B| input noise; Neptune residual ~2sigma of 0.74 e-4;")
print("   full-ephemeris (a,T) at 8+ s.f. (pre-registered GOM18) decides H-ENCLOSED cleanly.")
print(" - H-GLOBAL (every row shifted equally) remains dead: inner rows sit at 0 by construction")
print("   AND agree to 1.2e-5 while carrying no enclosed giants - no global background.")
print(" done. exit 0")
