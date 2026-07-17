# GOM18 - Sagittarius A*: the equilibrium seat. ADJ in RUN_LOG.md committed BEFORE this file.
# All-kinematic: koppa = 4*pi^2*a^3/(T^2*c^2) from dependents' (a,T). No G, no M, no GM in-chain
# (rival columns labelled informational). J. C. Harvey directive, 2026-07-07.
import math
PI = math.pi
c   = 299792458.0
YR  = 3.15576e7                      # Julian-ish year [s]
AU  = 1.495978707e11
PC  = 3.0856775814913673e16
R0  = 8277.0 * PC                    # GRAVITY distance to the GC [m]  (8.277 kpc, declared)
LSUN= 3.828e26                       # W (IAU nominal)
# CMB bath (engine Law I values)
u_CMB = 7.5657e-16 * 2.7255**4      # a_rad*T^4 [J/m^3]
F_CMB = c * u_CMB / 4.0             # [W/m^2]
# whitelisted particle constants (data boundary)
m_p = 1.67262192369e-27; sigma_T = 6.6524587321e-29
# ---- declared dependents: (name, a ["], T [yr])  Gillessen+ catalogue class ----
STARS = [("S2", 0.1255, 16.05), ("S38", 0.1416, 19.20), ("S55", 0.1078, 12.80)]
EHT_THETA, EHT_ERR = 51.8, 2.3       # muas (2022)
L_SGRA_LO, L_SGRA_MID, L_SGRA_HI = 1e35*1e-7, 10**35.5*1e-7, 1e36*1e-7   # erg/s -> W
L_MW_LO, L_MW_HI = 1.5e10*LSUN, 3.0e10*LSUN
V_CIRC = 233e3                       # m/s at R0 (kinematic)

def koppa(a_m, T_s): return 4*PI*PI*a_m**3/(T_s*T_s*c*c)

print("="*94)
print(" GOM18 - Sagittarius A*: the equilibrium seat.  koppa kinematic; no G/M/GM in-chain.")
print("="*94)

print("\n-- G1: the seat from three dependents (the GOM14 consistency test at the terminus) --")
kops=[]
for name, a_as, T_yr in STARS:
    a_m = a_as * (R0/PC) * AU        # arcsec x distance[pc] = AU
    k = koppa(a_m, T_yr*YR); kops.append(k)
    Msun_riv = (a_as*(R0/PC))**3 / T_yr**2   # [informational rival column: AU^3/yr^2 = M_sun]
    print(f"   {name:4s} a={a_as:.4f}\" ({a_as*(R0/PC):7.1f} AU)  T={T_yr:6.2f} yr"
          f"   kop = {k:.4e} m   [rival col: {Msun_riv:.3e} M_sun-equiv]")
kmean=sum(kops)/len(kops); spread=(max(kops)-min(kops))/kmean
print(f"   mean kop = {kmean:.4e} m   spread = {spread*100:.2f}%   G1 gate <=2%: {'PASS' if spread<=0.02 else 'FAIL'}")

print("\n-- G2: cross-ledger consistency - the light-capture rim from the STELLAR seat --")
theta = 2*math.sqrt(27)*kmean/R0 * (180/PI*3600*1e6)   # muas
diff = abs(theta - EHT_THETA)
print(f"   predicted ring = 2*sqrt(27)*kop/R0 = {theta:.2f} muas   EHT measured = {EHT_THETA} +- {EHT_ERR} muas")
print(f"   |diff| = {diff:.2f} muas   G2 gate (within meas. error {EHT_ERR} + 2% slack {0.02*theta:.2f}):"
      f" {'PASS' if diff <= EHT_ERR + 0.02*theta else 'FAIL'}")
print(f"   (one kop read at ~1000 AU by stars and at ~{math.sqrt(27)*kmean/AU:.2f} AU by light - radii ~{(0.1255*(R0/PC))/(math.sqrt(27)*kmean/AU):.0f}x apart)")

print("\n-- G3 report rows: the equilibrium placements --")
def r_eq(L): return math.sqrt(L/(4*PI*F_CMB))
print(f"   (a) Sgr A* radiative pressure-domain r_eq = sqrt(L/4piF_CMB):")
print(f"       L=1e35 erg/s -> {r_eq(L_SGRA_LO)/PC:.2f} pc | 10^35.5 -> {r_eq(L_SGRA_MID)/PC:.2f} pc | 1e36 -> {r_eq(L_SGRA_HI)/PC:.2f} pc")
print(f"       [compare: circumnuclear-disk inner edge ~1.5 pc; Bondi-class radius ~0.1 pc - the")
print(f"        quiet terminus's own bath-domain sits at the CND scale]")
print(f"   (b) the GALAXY's domain (scale-invariance row: Sun 20857 AU -> galaxy -> BAO 147 Mpc):")
print(f"       L_MW=1.5e10 Lsun -> {r_eq(L_MW_LO)/(1000*PC):.1f} kpc | 3.0e10 -> {r_eq(L_MW_HI)/(1000*PC):.1f} kpc   vs stellar disk ~15-20 kpc")
kop_enc = V_CIRC*V_CIRC*R0/(c*c)
print(f"   (c) column position: enclosed ledger at the solar circle kop_enc = v^2 R0/c^2 = {kop_enc:.4e} m")
print(f"       Sgr A* share = {kmean/kop_enc:.2e}  - the terminus holds ~{kmean/kop_enc*1e5:.1f} millionths x10 of the circle's ledger")
L_lift = 4*PI*c**3*kmean*(m_p/sigma_T)
print(f"   (d) native column-lift (discharge that would hold the whole column off):")
print(f"       L_lift = 4pi c^3 kop (m_p/sigma_T) = {L_lift:.3e} W   [rival col: this IS L_Eddington]")
print(f"       measured duty L/L_lift = {L_SGRA_MID/L_lift:.1e}  - the queue is ~10 orders below its own")
print(f"       lift ceiling: a terminus ACCUMULATING between discharges (Fermi/eROSITA bubbles =")
print(f"       the last discharge's relics - FRAME note, report-only)")
sig=105e3/ c
M_msigma = 1.9e8*( (105.0/200.0)**5.6 )
print(f"   (e) [rival column, informational]: M-sigma places the MW point at ~{M_msigma:.2e} M_sun vs")
print(f"       seat-equivalent ~4.35e6 - ON the relation within its scatter: Sgr A* sits AT its")
print(f"       host equilibrium position, not approaching it.")
print("\n   VERDICT LINE: G1/G2 printed above; G3 rows are placements (identities + measured inputs),")
print("   not derivations; precision honesty: inputs 3-5 s.f., nothing claimed under 1%.")
