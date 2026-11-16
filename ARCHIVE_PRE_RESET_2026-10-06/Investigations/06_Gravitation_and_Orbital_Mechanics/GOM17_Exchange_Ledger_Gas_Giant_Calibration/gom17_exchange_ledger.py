# GOM17 - Energy-Is-Movement Exchange Ledger: gas-giant calibration + removal test.
# J. C. Harvey directive, executed 2026-07-06. RUN_LOG.md committed BEFORE this file.
# STANDING RULE: no G, no M, no GM anywhere in-chain. koppa = 4*pi^2*a^3/(T^2*c^2) - kinematic.
# Rival values appear ONLY in columns labelled INFORMATIONAL-RIVAL (never load-bearing).
import math
PI  = math.pi
c   = 299792458.0            # m/s, SI exact
AU  = 1.495978707e11         # m, IAU 2012 exact
DAY = 86400.0
CY  = 36525.0                # days per Julian century

def kop_aT(a_m, T_s): return 4*PI*PI*a_m**3/(T_s*T_s*c*c)

# ---------------- SET-A planets: Standish mean elements 1800-2050 (a AU, Ldot deg/cy) --------
SETA = [  # name, a_AU, Ldot, e (e used only in Part A quadrature/aberration)
 ("Mercury", 0.38709927, 149472.67411175, 0.20563593),
 ("Venus",   0.72333566,  58517.81538729, 0.00677672),
 ("EMB",     1.00000261,  35999.37244981, 0.01671123),
 ("Mars",    1.52371034,  19140.30268499, 0.09339410),
 ("Jupiter", 5.20288700,   3034.74612775, 0.04838624),
 ("Saturn",  9.53667594,   1222.49362201, 0.05386179),
 ("Uranus", 19.18916464,    428.48202785, 0.04725744),
 ("Neptune",30.06992276,    218.45945325, 0.00859048)]
# ---------------- SET-B planets: classic J2000 elements + quoted sidereal periods ------------
SETB = [ ("Mercury",0.38709893,87.9691),("Venus",0.72333199,224.701),
 ("EMB",1.00000011,365.25636),("Mars",1.52366231,686.980),("Jupiter",5.20336301,4332.589),
 ("Saturn",9.53707032,10759.22),("Uranus",19.19126393,30685.4),("Neptune",30.06896348,60189.0)]

rowsA = {n: kop_aT(a*AU, (360.0/Ld)*CY*DAY) for n,a,Ld,e in SETA}
rowsB = {n: kop_aT(a*AU, T*DAY)             for n,a,T   in SETB}

# ---------------- moons: (name, a_km, T_d, R_km, locked) -------------------------------------
JUP_M = [("Amalthea",181366.,0.498179,  83.5,True),("Io",421769.,1.769138,1821.6,True),
         ("Europa",671079.,3.551181,1560.8,True),("Ganymede",1070412.,7.154553,2634.1,True),
         ("Callisto",1882709.,16.689018,2410.3,True)]
SAT_M = [("Mimas",185539.,0.942422,198.2,True),("Enceladus",237948.,1.370218,252.1,True),
         ("Tethys",294619.,1.887802,531.1,True),("Dione",377396.,2.736915,561.4,True),
         ("Rhea",527108.,4.518212,763.8,True),("Titan",1221870.,15.945421,2574.7,True),
         ("Hyperion",1481010.,21.276609,135.0,False),("Iapetus",3560820.,79.321500,734.5,True)]
OTHER_M = {"EMB":("Moon",384399.,27.321661,1737.4,True),
           "Mars":("Deimos",23463.2,1.262441,6.2,True),
           "Uranus":("Titania",435910.,8.706234,788.4,True),
           "Neptune":("Triton",354759.,5.876854,1353.4,True)}
R_JUP, R_SAT, R_SUN = 7.1492e7, 6.0268e7, 6.957e8   # m, IAU nominal
PLANET_R = {"Mercury":2.4397e6,"Venus":6.0518e6,"EMB":6.378137e6,"Mars":3.3962e6,
            "Jupiter":R_JUP,"Saturn":R_SAT,"Uranus":2.5559e7,"Neptune":2.4764e7}
PLANET_SPIN = {"Mercury":58.6462*DAY,"Venus":243.018*DAY,"EMB":86164.0905,"Mars":88642.66,
               "Jupiter":35729.71,"Saturn":38018.0,"Uranus":62064.0,"Neptune":57996.0}
# INFORMATIONAL-RIVAL system-shares (ephemeris GM ratios to Sun) - comparison column ONLY:
RIVAL_SHARE = {"Mercury":1.66e-7,"Venus":2.45e-6,"EMB":3.04e-6,"Mars":3.23e-7,
               "Jupiter":9.548e-4,"Saturn":2.859e-4,"Uranus":4.37e-5,"Neptune":5.15e-5}

def gearing(R,r):  # dependent influx share = its solid angle from the parent, /4pi
    return 0.5*(1.0-math.sqrt(max(0.0,1.0-(R/r)**2)))

print("="*100)
print(" GOM17 - EXCHANGE LEDGER (energy = movement; every term a z-account; zk^2 = 1).")
print(" koppa KINEMATIC (4pi^2 a^3/T^2 c^2) throughout. No G/M/GM in-chain. Rival = labelled column only.")
print("="*100)

# ============================ PART A1: which closure does the data support? ==================
print("\n--- A1. vis-viva time-average theorem (quadrature, Mercury e=0.2056, uniform-in-time grid) ---")
name,aAU,Ld,e = SETA[0]
a = aAU*AU; T = (360.0/Ld)*CY*DAY; kv = kop_aT(a,T)
N = 200000; s_zt = 0.0; s_inv_r = 0.0
for i in range(N):
    M = 2*PI*(i+0.5)/N
    E = M
    for _ in range(12): E -= (E-e*math.sin(E)-M)/(1-e*math.cos(E))
    r = a*(1-e*math.cos(E))
    s_zt += kv*(2.0/r - 1.0/a); s_inv_r += 1.0/r
zt_mean = s_zt/N; zd_a = kv/a
print(f"  <z_t>_time = {zt_mean:.9e}   z_d(a) = {zd_a:.9e}   ratio = {zt_mean/zd_a:.9f}")
print(f"  <1/r>_time*a = {(s_inv_r/N)*a:.9f}  (theorem: =1 exactly)")
print("  conserved ledger line z_t(t) - 2*z_d(r(t)) = -z_d(a) at 3 sample points:")
for M in (0.5, 2.0, 4.5):
    E = M
    for _ in range(20): E -= (E-e*math.sin(E)-M)/(1-e*math.cos(E))
    r = a*(1-e*math.cos(E)); zt = kv*(2/r-1/a)
    print(f"    M={M:.1f}: z_t - 2*z_d(r) = {zt-2*kv/r:.6e}   -z_d(a) = {-zd_a:.6e}")
print("  => closure supported: factor-1 (residence): <z_t> = z_d(a). The 1/2 is NOT in the exchange")
print("     rate; see A3 (release). NOTE: with v=2pi*a/T this is Kepler-III restated (IDENTITY flag");
print("     per RUN_LOG) - the independent license is A2.")

# ============================ PART A2: aberration license (measured ANGLE, (a,T)-independent) =
print("\n--- A2. aberration constant: kappa^2*(1-e^2) vs z_d(a_EMB) - factor-1 predicts 1, factor-1/2 predicts 2 ---")
e_E = 0.01671123; a_E = 1.00000261*AU
# clean sun koppa estimate for z_d: EMB row minus EM self-term (computed below, tiny) - use row.
zd_E = rowsA["EMB"]/a_E
for label,arc,flag in [("Struve 1843 (measured)",20.445,""),("Newcomb adopted (measured-era)",20.47,""),
                       ("Nyren 1882 (measured)",20.492,""),("IAU defined (COMPUTED - circularity flagged)",20.49552," [consistency only]")]:
    k_rad = arc*PI/(180*3600); ratio = k_rad*k_rad*(1-e_E*e_E)/zd_E
    print(f"  {label:42s} {arc:8.5f}\"  kappa^2(1-e^2)/z_d = {ratio:.5f}{flag}")
print("  => measured band gives 0.995-1.000: factor-1 closure LICENSED by a telescope angle;")
print("     factor-1/2 (ratio 2.0) excluded by ~400x the band width.")

# ============================ PART A3: release closure (escape = factor 2) ===================
print("\n--- A3. release closure: z_esc = 2*z_d(surface); Earth, measured v_esc = 11.186 km/s (R_mean 6371 km) ---")
kop_EM = kop_aT(OTHER_M["EMB"][1]*1e3, OTHER_M["EMB"][2]*DAY)
bary = 4671.0/ (384399.0-4671.0)   # kinematic Moon/Earth share from measured barycentre offset (4671 km, declared)
kop_E = kop_EM/(1.0+bary)
z_esc_meas = (11186.0/c)**2; z_esc_pred = 2*kop_E/6.371e6
print(f"  kop(E+M) from Moon row = {kop_EM:.6e} m  [carries solar tide ~ -0.28%, declared]")
print(f"  kop(Earth) via barycentre split (4671 km, kinematic length ratio) = {kop_E:.6e} m")
print(f"  z_esc measured = {z_esc_meas:.6e}   2*z_d(surf) = {z_esc_pred:.6e}   ratio = {z_esc_meas/z_esc_pred:.4f}")
print("  => residence:release = 1:2; the celebrated 1/2 lives BETWEEN them (bound orbit holds half")
print("     its release requirement), not in the exchange rate. Residual ~ tide bias, labelled.")

# ============================ PART A4: planet z-accounts =====================================
print("\n--- A4. z-accounts, Sun's dependents (z_d = kop_sun/a; z_t = (2pi*a/T)^2/c^2 [row-identity];")
print("        z_rot = (2pi*R/T_spin)^2/c^2; gearing = dependent solid-angle share Omega/4pi) ---")
kop_sun_ref = rowsA["EMB"]
print(f"  {'body':8s} {'a [m]':>11s} {'z_d':>10s} {'k_d=1/sqrt':>10s} {'z_rot':>10s} {'gearing':>10s}")
for n,aAU_,Ld_,e_ in SETA:
    a_ = aAU_*AU; zd = kop_sun_ref/a_; zrot = (2*PI*PLANET_R[n]/PLANET_SPIN[n])**2/c**2
    print(f"  {n:8s} {a_:11.4e} {zd:10.3e} {1/math.sqrt(zd):10.4g} {zrot:10.3e} {gearing(PLANET_R[n],a_):10.3e}")
zrot_sun = (2*PI*R_SUN/(25.38*DAY))**2/c**2
print(f"  (Sun internal: z_rot(Carrington) = {zrot_sun:.3e}; Saturn spin CONTESTED - 38018 s used,")
print(f"   Voyager 38362.4 s gives z_rot = {(2*PI*R_SAT/38362.4)**2/c**2:.3e})")

# ============================ PART A5: tidal locking = rotation-position exchange ============
print("\n--- A5. locked moons: T_spin = T_orb  =>  z_rot = z_d*(R/a)^2 - rotation is a pure function")
print("        of position. 'Every tidally locked speck adds up to its position as rotation.' ---")
def moon_table(tag, moons, kop_parent):
    print(f"  [{tag}]  {'moon':10s} {'a [1e3 km]':>10s} {'z_d':>10s} {'z_rot':>11s} {'z_d*(R/a)^2':>11s} {'gearing':>10s}  lock")
    for n,a_km,T_d,R_km,locked in moons:
        a_ = a_km*1e3; R_ = R_km*1e3; T_ = T_d*DAY
        zd = kop_parent/a_; zrot = (2*PI*R_/T_)**2/c**2; pos = zd*(R_/a_)**2
        lk = "LOCKED" if locked else "NOT LOCKED (chaotic tumbler - z_rot column void)"
        if not locked: zrot = float('nan')
        print(f"           {n:10s} {a_km/1e3:10.2f} {zd:10.3e} {zrot:11.3e} {pos:11.3e} {gearing(R_,a_):10.3e}  {lk}")
# parent koppas: regression intercepts computed in B2; do a first pass with raw source rows,
# final intercepts printed in B2 (values differ at the form-term level only).
kj_rows = [(n, kop_aT(a*1e3, T*DAY), (R_JUP/(a*1e3))**2) for n,a,T,R,lk in JUP_M]
ks_rows = [(n, kop_aT(a*1e3, T*DAY), (R_SAT/(a*1e3))**2) for n,a,T,R,lk in SAT_M]
def lsq(rows):
    xs=[x for _,_,x in rows]; ys=[y for _,y,_ in rows]; n=len(rows)
    xm=sum(xs)/n; ym=sum(ys)/n
    B=sum((x-xm)*(y-ym) for x,y in zip(xs,ys))/sum((x-xm)**2 for x in xs); A=ym-B*xm
    return A,B
A_jup,B_jup = lsq(kj_rows); A_sat,B_sat = lsq(ks_rows)
moon_table("Jupiter", JUP_M, A_jup)
moon_table("Saturn ", SAT_M, A_sat)
print("  [others] locked single majors:")
for pl,(n,a_km,T_d,R_km,locked) in OTHER_M.items():
    a_=a_km*1e3; R_=R_km*1e3; T_=T_d*DAY; kp=kop_aT(a_,T_)
    print(f"           {n:10s} (of {pl:7s}) z_d = {kp/a_:.3e}  z_rot = {(2*PI*R_/T_)**2/c**2:.3e}"
          f"  = z_d*(R/a)^2 = {(kp/a_)*(R_/a_)**2:.3e}  gearing = {gearing(R_,a_):.3e}")
print("  NOTE: z_rot = z_d*(R/a)^2 is a definitional identity GIVEN the lock (RUN_LOG); the physics")
print("  is the measured lock itself. z_rot ~ 4*z_d*gearing (since (R/a)^2 ~ 4*Omega/4pi).")

# ============================ PART B2: giant-system decomposition (moons) ====================
print("\n--- B2. per-moon parent-koppa rows: row = kop_parent*(1 + q*(R_par/a)^2) + kop_moon ---")
print("        (the (R/a)^2 pattern = the parent's OBLATE-SHADOW form term, read kinematically)")
for tag, rows_, A, B, R_par, rival_q in (("Jupiter",kj_rows,A_jup,B_jup,R_JUP,0.022104),
                                          ("Saturn", ks_rows,A_sat,B_sat,R_SAT,0.024447)):
    print(f"  [{tag}] regression: intercept kop_clean = {A:.6f} m   slope/intercept q_kin = {B/A:.5f}")
    print(f"          INFORMATIONAL-RIVAL (3/2)*J2 = {rival_q:.6f}   sign gate (slope>0): {'PASS' if B>0 else 'FAIL'}")
    print(f"          {'moon':10s} {'row kop [m]':>12s} {'(row/A-1) e4':>12s} {'fit dev e4':>10s}")
    for n,y,x in rows_:
        fit = A + B*x
        print(f"          {n:10s} {y:12.6f} {(y/A-1)*1e4:12.2f} {(y-fit)/A*1e4:10.2f}")
    resid = [abs(y-(A+B*x))/A for n,y,x in rows_]
    print(f"          residual scatter about fit: median {sorted(resid)[len(resid)//2]*1e4:.2f} e-4,"
          f" max {max(resid)*1e4:.2f} e-4")
print("  Moon self-terms sought: Ganymede ~0.78 e-4, Titan ~2.37 e-4 (INFORMATIONAL-RIVAL sizes).")
print("  Verdict per RUN_LOG commitment: reachable only if scatter above < the self-term.")

# ============================ PART B3: the ring ledger line ==================================
print("\n--- B3. Saturn ring line: distributed annulus 74658-136775 km ---")
for lbl,r_km in (("inner edge",74658.0),("outer edge",136775.0)):
    print(f"  z_d({lbl} {r_km:.0f} km) = {A_sat/(r_km*1e3):.4e}")
print("  ring's OWN koppa: PENDING-kinematic (a ring has no dependent; no (a,T) route exists).")
print("  Named kinematic upgrade: spiral density-wave dispersion (wavelength-frequency-distance).")
print("  INFORMATIONAL-RIVAL class: ~1e-8 of kop_saturn - 4 orders below this run's floor. No rival")
print("  mass imported; the line is carried OPEN, not filled.")

# ============================ PART B1 + C: the Sun table, calibration, removal ===============
print("\n--- B1. per-planet kop_sun rows (SET-A primary; SET-B = declared input-noise probe) ---")
# kinematic self-terms (in-chain, per RUN_LOG):
selfs = {"Mercury":0.0,"Venus":0.0,
         "EMB":     kop_aT(OTHER_M["EMB"][1]*1e3,     OTHER_M["EMB"][2]*DAY),
         "Mars":    kop_aT(OTHER_M["Mars"][1]*1e3,    OTHER_M["Mars"][2]*DAY),
         "Jupiter": A_jup, "Saturn": A_sat,
         "Uranus":  kop_aT(OTHER_M["Uranus"][1]*1e3,  OTHER_M["Uranus"][2]*DAY),
         "Neptune": kop_aT(OTHER_M["Neptune"][1]*1e3, OTHER_M["Neptune"][2]*DAY)}
names  = [n for n,_,_,_ in SETA]
corr   = {n: rowsA[n]-selfs[n] for n in names}
K0     = sum(corr.values())/8.0
meanB4 = sum(rowsA.values())/8.0
inner  = ["Mercury","Venus","EMB","Mars"]
noise  = {n: abs(rowsA[n]-rowsB[n])/K0 for n in names}
print(f"  clean estimate kop_sun = mean(corrected rows) = {K0:.4f} m")
print(f"  {'planet':8s} {'row A [m]':>10s} {'devA e4':>8s} {'devB e4':>8s} {'|A-B| e4':>8s} {'self_kin [m]':>12s} {'dev_corr e4':>11s} {'RIVAL-share e4':>14s}")
for n in names:
    print(f"  {n:8s} {rowsA[n]:10.4f} {(rowsA[n]/K0-1)*1e4:8.2f} {(rowsB[n]/K0-1)*1e4:8.2f}"
          f" {noise[n]*1e4:8.2f} {selfs[n]:12.6f} {(corr[n]/K0-1)*1e4:11.2f} {RIVAL_SHARE[n]*1e4:14.3f}")
print("  (Mercury/Venus self = 0: PENDING-kinematic, no dependent; rival column says <=0.025 e-4 - sub-floor.)")
print("  (EMB self via Moon row carries the solar tide ~ -0.28% of 4.5e-3 m = 1.2e-5 m - sub-floor at Sun rows.)")

print("\n--- C. GATES + REMOVAL TEST ---")
gA = rowsA["Jupiter"] > max(rowsA[n] for n in inner)
gB = rowsB["Jupiter"] > max(rowsB[n] for n in inner)
print(f"  GATE(i) sign (Jupiter row > all inner rows):  SET-A {'PASS' if gA else 'FAIL'}   SET-B {'PASS' if gB else 'FAIL'}")
gA_s = rowsA["Saturn"] > max(rowsA[n] for n in inner)
gB_s = rowsB["Saturn"] > max(rowsB[n] for n in inner)
print(f"          (same for Saturn, informational):     SET-A {'PASS' if gA_s else 'FAIL'}   SET-B {'PASS' if gB_s else 'FAIL'}")
rms  = lambda d: math.sqrt(sum(x*x for x in d)/len(d))
devB4  = [rowsA[n]/meanB4-1 for n in names]
devAf  = [corr[n]/K0-1     for n in names]
r_b4, r_af = rms(devB4), rms(devAf)
band = (min(corr[n] for n in inner), max(corr[n] for n in inner))
inband = band[0] <= corr["Jupiter"] <= band[1]
print(f"  GATE(ii) spread: RMS before = {r_b4*1e4:.2f} e-4 (predicted, perfect inputs: 3.1 e-4)")
print(f"                   RMS after  = {r_af*1e4:.2f} e-4   ratio after/before = {r_af/r_b4:.3f}  ({'PASS' if r_af/r_b4<0.5 else 'FAIL'} <0.5)")
print(f"                   max-min before = {(max(rowsA.values())-min(rowsA.values()))/meanB4*1e4:.2f} e-4"
      f",  after = {(max(corr.values())-min(corr.values()))/K0*1e4:.2f} e-4")
print(f"                   Jupiter corrected row in inner band [{(band[0]/K0-1)*1e4:+.2f},{(band[1]/K0-1)*1e4:+.2f}] e-4:"
      f" {'PASS' if inband else 'FAIL'} (dev {(corr['Jupiter']/K0-1)*1e4:+.2f} e-4)")
print(f"                   declared input-noise floor (mean |A-B|): {sum(noise.values())/8*1e4:.2f} e-4")
print("\n  H-GLOBAL kill line: if shadows summed globally every row would sit at "
      f"+{sum(selfs.values())/K0*1e4:.2f} e-4;")
print(f"  the inner rows actually sit at {[round((rowsA[n]/K0-1)*1e4,2) for n in inner]} e-4 -> H-GLOBAL vs H-LOCAL read off directly.")
print("\n  REMOVAL COUNTERFACTUAL - subtract the JUPITER-system shadow from EVERY row (dev e-4 vs K0):")
print(f"  {'planet':8s} {'before':>8s} {'minus Jup-sys':>13s} {'minus Sat-sys':>13s}   (ledger: only the OWNER row may land clean)")
for n in names:
    dj = (rowsA[n]-A_jup)/K0-1; ds = (rowsA[n]-A_sat)/K0-1
    tag = "<= owner (Jup)" if n=="Jupiter" else ("<= owner (Sat)" if n=="Saturn" else "")
    print(f"  {n:8s} {(rowsA[n]/K0-1)*1e4:8.2f} {dj*1e4:13.2f} {ds*1e4:13.2f}   {tag}")
print("\n  Reading: subtracting a shadow heals ONLY its owner's row and wounds every other row by the")
print("  same amount - additivity is row-local. A global background would heal/wound all rows equally.")
print("\n  done. exit 0")
