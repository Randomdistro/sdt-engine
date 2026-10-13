#!/usr/bin/env python3
"""
CR15 - The ionisation trilemma and the cold dense past.

Pre-registration: PROMPT.md (tests T1-T5, thresholds fixed before this file existed).
Object: SDT Cosmological Sector formulation (Harvey 2026-07-30), Props 4/5/11/13, P5/P6.
Predecessor: CR14 (same validated Saha solver; gates re-run here).

Constants mirror sdt::laws::measured. No new physics constant is defined here.
"""
import math

# ---- inputs, tagged (mirror sdt::laws::measured) ----
hbar  = 1.054571817e-34     # J s    laws.hpp:111                      [MEASURED-INPUT]
k_B   = 1.380649e-23        # J/K    laws.hpp:130                      [MEASURED-INPUT]
m_e   = 9.1093837015e-31    # kg     laws.hpp:147                      [MEASURED-INPUT]
Ry_eV = 13.605693122994     # eV     laws.hpp:151                      [MEASURED-INPUT]
T0    = 2.7255              # K      laws.hpp:165 (FIRAS)              [MEASURED-INPUT]
eV_J  = 1.602176634e-19     # J/eV   laws.hpp:179                      [MEASURED-INPUT]
c     = 299792458.0         # m/s    laws.hpp                          [MEASURED-INPUT]
sigma_T = 6.6524587321e-29  # m^2    Thomson cross-section             [MEASURED-INPUT]
R_CMB = 9.527e26            # m      laws.hpp:176 (observed)           [MEASURED-INPUT]
n_b0  = 0.2512              # m^-3   Planck Omega_b h^2 (comparator)   [MEASURED-INPUT]
Mpc   = 3.0857e22           # m                                        [MEASURED-INPUT]

# ---- the document's own calibrated inputs (Parts I-II) ----
d_s      = 1.1e-35          # m      A1 spation diameter               [C, document]
P_conf   = 8.0e34           # Pa     A2 confinement ceiling            [C, document]
P_0      = 1.3916e-14       # Pa     Part II                           [C, document]
H_0      = 2.27e-18         # s^-1   Part II (~70 km/s/Mpc)            [C, document]
z_rec_id = 1100.0           #        the epoch identified with the CMB - UNDER TEST

B_J   = Ry_eV * eV_J
theta = B_J / k_B                                       # 157,887 K
A_pre = (m_e * k_B / (2.0 * math.pi * hbar * hbar)) ** 1.5
yr    = 3.15576e7
Gyr   = 1.0e9 * yr

out = []
def p(s=""):
    out.append(s)
    print(s)

def S_of(T, B_over_kT):
    """Saha RHS with the Boltzmann argument supplied explicitly (m^-3)."""
    if T <= 0.0 or B_over_kT > 700.0:
        return 0.0
    return A_pre * T ** 1.5 * math.exp(-B_over_kT)

def x_from_ratio(r):
    """x^2/(1-x) = r  ->  x."""
    if r <= 0.0:
        return 0.0
    if r > 1.0e12:
        return 1.0
    return 0.5 * (-r + math.sqrt(r * r + 4.0 * r))

def bisect(f, lo, hi, it=300):
    flo, fhi = f(lo), f(hi)
    if flo * fhi > 0.0:
        return None
    for _ in range(it):
        mid = 0.5 * (lo + hi)
        fm = f(mid)
        if flo * fm < 0.0:
            hi, fhi = mid, fm
        else:
            lo, flo = mid, fm
    return 0.5 * (lo + hi)

def chk(label, got, want, tol_pct, unit=""):
    """T1 helper: compare recomputed value against the document's stated value."""
    dev = abs(got - want) / abs(want) * 100.0
    ok = dev <= tol_pct
    p("    %-28s recomputed %-12.4g  stated %-10.4g %-8s dev %7.2f %%  %s"
      % (label, got, want, unit, dev, "OK" if ok else "** MISMATCH **"))
    return ok

p("=" * 84)
p("CR15 - IONISATION TRILEMMA AND THE COLD DENSE PAST")
p("Pre-registered: PROMPT.md.  Tests T1-T5.")
p("=" * 84)
p()
p("theta = B/k_B = %.1f K      B_0/(k_B T_0) = %.1f  (today's Boltzmann argument)"
  % (theta, theta / T0))
p()

# ============================================================ gates (CR14 V1-V3)
p("-" * 84)
p("VALIDATION GATES (re-run from CR14; no result reportable if any fails)")
p("-" * 84)

def T_half_lcdm(X=0.5):
    def f(T):
        nb = n_b0 * (T / T0) ** 3
        return math.log(max(S_of(T, theta / T), 1e-300)) - math.log(nb * X * X / (1.0 - X))
    return bisect(f, 200.0, 5.0e4)

v1_hi = x_from_ratio(S_of(1.0e5, theta / 1.0e5) / (n_b0 * (1.0e5 / T0) ** 3))
v1_lo = x_from_ratio(S_of(1.0e3, theta / 1.0e3) / (n_b0 * (1.0e3 / T0) ** 3))
v1 = v1_hi > 0.99 and v1_lo < 0.01
p("  V1  x_e(1e5 K) = %.6f ,  x_e(1e3 K) = %.6f   -> %s" % (v1_hi, v1_lo, "PASS" if v1 else "FAIL"))

TA = T_half_lcdm()
zA = TA / T0 - 1.0
v2 = 1250.0 <= zA <= 1450.0
p("  V2  LCDM Saha half-ionisation z = %.1f  (window 1250-1450) -> %s" % (zA, "PASS" if v2 else "FAIL"))

TB = bisect(lambda T: math.log(max(S_of(T, theta / T), 1e-300)) - math.log(n_b0 * 0.5), 50.0, 1e6)
ana = 1.0 / (1.5 + theta / TB)
eps = 1e-4
Tp = bisect(lambda T: math.log(max(S_of(T, theta / T), 1e-300)) - math.log(n_b0 * math.exp(eps) * 0.5), 50.0, 1e6)
Tm = bisect(lambda T: math.log(max(S_of(T, theta / T), 1e-300)) - math.log(n_b0 * math.exp(-eps) * 0.5), 50.0, 1e6)
num = (math.log(Tp) - math.log(Tm)) / (2.0 * eps)
v3 = abs(num - ana) / ana < 0.01
p("  V3  d lnT/d ln n_b  analytic %.6f  numerical %.6f  -> %s" % (ana, num, "PASS" if v3 else "FAIL"))
if not (v1 and v2 and v3):
    p("!! GATES FAILED - nothing reportable."); raise SystemExit(1)
p("  all gates PASS")
p()

# ============================================================ T1 arithmetic audit
p("=" * 84)
p("T1 - ARITHMETIC AUDIT of the document's [D]-tagged numbers")
p("=" * 84)
t1 = []
p("  Part VI - bounds of the vessel:")
N_max = (P_conf / P_0) ** 0.25
t1.append(chk("N_max = (P_conf/P_0)^1/4", N_max, 1.55e12, 1.0))
v_min = c / N_max
t1.append(chk("v_min = c/N_max", v_min, 1.9e-4, 5.0, "m/s"))
t1.append(chk("T_max = N_max T_0", N_max * T0, 4.2e12, 1.0, "K"))
rho_s = 2.0 * P_conf / (c * c)
t1.append(chk("rho_s = 2 P_conf/c^2", rho_s, 2.3e17, 5.0, "kg/m3"))
p("  Part IX / Hypothesis H:")
P_min = P_0 * P_0 / P_conf
t1.append(chk("P_min = P_0^2/P_conf", P_min, 2.4e-63, 2.0, "Pa"))
t1.append(chk("T_end = T_0/N_max", T0 / N_max, 1.8e-12, 5.0, "K"))
t1.append(chk("v_dec = c^2/v_min", c * c / v_min, 4.7e20, 5.0, "m/s"))
p("  Part VII - the clock:")
inv_H0 = 1.0 / H_0
t1.append(chk("1/H_0", inv_H0 / Gyr, 14.0, 1.0, "Gyr"))
t1.append(chk("t_lb(1100) = ln(1100)/H_0", math.log(1100.0) * inv_H0 / Gyr, 98.0, 1.5, "Gyr"))
t1.append(chk("t_lb(N_max)", math.log(N_max) * inv_H0 / Gyr, 390.0, 2.0, "Gyr"))
t1.append(chk("D_CMB = (c/H_0)(1-1/N_r)", (c * inv_H0 * (1.0 - 1.0 / 1100.0)) / (c * Gyr),
              14.0, 2.0, "Glyr"))
t1.append(chk("tau_now = 1/(2 H_0)", 0.5 * inv_H0 / Gyr, 7.0, 2.0, "Gyr"))
p("  Part VIII - BAO shell:")
u_r = H_0 * 150.0 * Mpc / 1100.0
t1.append(chk("u_r = H_0 r_com/N_r", u_r / 1000.0, 9.5, 3.0, "km/s"))
t1.append(chk("u_r / (c/N_r)", u_r / (c / 1100.0) * 100.0, 3.5, 5.0, "%"))
p()
p("  T1: %d/%d reproduce; %d MISMATCH" % (sum(t1), len(t1), len(t1) - sum(t1)))
if not t1[3]:
    need_P = 2.3e17 * c * c / 2.0
    p("  -> rho_s defect traced: rho = 2P/c^2 with P_conf = 8e34 Pa gives %.4g kg/m3," % rho_s)
    p("     a factor %.2f above the stated 2.3e17. To make the stated value true," % (rho_s / 2.3e17))
    p("     P_conf would have to be %.4g Pa, which moves N_max to %.4g (not 1.55e12)"
      % (need_P, (need_P / P_0) ** 0.25))
    p("     and rescales every Hypothesis-H prediction. P_conf is [C] and load-bearing.")
p()

# ============================================================ T2 trilemma (i)+(ii)
p("=" * 84)
p("T2 - TRILEMMA legs (i)+(ii):  B(N) = B_0/N^2 ,  T(N) = T_0 N ,  n_b(N) = n_b0 N^3")
p("=" * 84)
p("  Boltzmann argument runs as B/(k_B T) = (theta/T_0)/N^3 = %.4g / N^3" % (theta / T0))

def f_T2(N, X=0.5):
    T = T0 * N
    BkT = (theta / T0) / N ** 3
    nb = n_b0 * N ** 3
    return math.log(max(S_of(T, BkT), 1e-300)) - math.log(nb * X * X / (1.0 - X))

N_T2 = bisect(f_T2, 1.5, 5000.0)
p("  half-ionisation epoch  N = %.3f   (z = %.3f)" % (N_T2, N_T2 - 1.0))
dev_T2 = abs(N_T2 - z_rec_id) / z_rec_id * 100.0
p("  vs the CMB identification N = 1100:  %.1f %% off  (factor %.1f)" % (dev_T2, z_rec_id / N_T2))
t2_pass = dev_T2 <= 10.0
p("  T2 %s" % ("PASS - (i) and (ii) jointly consistent with the CMB identification"
              if t2_pass else "FAIL - the trilemma is REAL; exactly one leg must be withdrawn"))
p()
p("  ionisation history under (i)+(ii)   [N > 1 is the past]")
p("      %-10s %-12s %-14s %-12s" % ("N", "T_local [K]", "B/(k_B T)", "x_e"))
for N in (1.0, 3.0, 10.0, 30.0, 100.0, 1100.0, 1.0e4):
    T = T0 * N
    BkT = (theta / T0) / N ** 3
    nb = n_b0 * N ** 3
    p("      %-10.4g %-12.4g %-14.4g %-12.6g" % (N, T, BkT, x_from_ratio(S_of(T, BkT) / nb)))
p("  -> under (i)+(ii) the past is HOTTER and binding is WEAKER, so ionisation runs away:")
p("     the transition is pushed to N ~ 10, and at N = 1100 hydrogen is fully ionised with")
p("     B/(k_B T) = %.4g - there is no neutral epoch to identify with the CMB."
  % ((theta / T0) / 1100.0 ** 3))
p()
p("  NAMED TRAP (PROMPT): 1100^(1/3) = %.3f sits near the observed reionisation epoch."
  % (1100.0 ** (1.0 / 3.0)))
p("  This is the cube root of an imported number and is NOT reported as a match.")
p()

# ============================================================ T3 the Prop 5 reading
p("=" * 84)
p("T3 - PROP 5 TAKEN AT FACE VALUE: bath quanta track atoms, T_local ~ N^-2,")
p("     so B/(k_B T) is epoch-INVARIANT at its present value %.4g" % (theta / T0))
p("=" * 84)
BkT_inv = theta / T0
p("      %-10s %-14s %-14s %-14s %-12s" % ("N", "T_local [K]", "B/(k_B T)", "n_b [m^-3]", "x_e"))
xs = []
for N in (1.0e-3, 1.0, 10.0, 100.0, 1100.0, 1.0e6):
    T = T0 / N ** 2
    nb = n_b0 * N ** 3
    xe = x_from_ratio(S_of(T, BkT_inv) / nb)
    xs.append((N, xe))
    p("      %-10.4g %-14.4g %-14.4g %-14.4g %-12.6g" % (N, T, BkT_inv, nb, xe))
mono_down = all(xs[i][1] >= xs[i + 1][1] for i in range(len(xs) - 1))
p()
p("  x_e is monotonically %s toward the past: %s"
  % ("DECREASING" if mono_down else "increasing", mono_down))
p("  the Boltzmann factor exp(-%.4g) = %s at EVERY epoch" % (BkT_inv, "0 (underflow)"))
p("  T3 REGISTERED OUTCOME: %s" % (
    "NO ionised era exists at any epoch - no recombination event, so the CMB cannot be a\n"
    "     last-scattering surface, and z_rec / T_rec must leave the `measured` namespace."
    if mono_down else "Prop 5 supports a conventional plasma era; leg passes."))
p()

# ============================================================ T4 CR14 correction
p("=" * 84)
p("T4 - CR14 CORRECTION: Branch B rerun with Prop 13's coasting dilution n_b ~ N^3")
p("=" * 84)
p("  Prop 13 gives r(t) ~ 1/N for coasting matter, so n_b ~ N^3 WITHOUT expanding space.")
p("  CR14 Branch B assumed n_b = const ('static, so no dilution'). That was the wrong law.")
p()
N_T4 = TA / T0                     # identical equations to the LCDM comparator
nb_T4 = n_b0 * N_T4 ** 3
tau_T4 = R_CMB * nb_T4 * sigma_T
p("  corrected Branch B half-ionisation:  T = %.1f K , N = %.1f" % (TA, N_T4))
p("  -> IDENTICAL to the LCDM comparator (same T(N), same n_b(N), same solver)")
p("  n_b at that epoch = %.4e m^-3 ;  tau = n_e sigma_T R_CMB = %.4e" % (nb_T4, tau_T4))
p()
p("  CR14 Branch E said: static vessel optically THIN by %.1f (tau = %.4g)."
  % (1.0 / (R_CMB * n_b0 * sigma_T), R_CMB * n_b0 * sigma_T))
withdrawn = tau_T4 > 1.0
p("  With Prop 13, tau = %.3e >> 1: optically THICK, a scattering surface DOES form." % tau_T4)
p("  T4 REGISTERED OUTCOME: CR14 Branch E objection %s"
  % ("WITHDRAWN" if withdrawn else "stands"))
p()

# ============================================================ T5 bridge exponent
p("=" * 84)
p("T5 - THE BRIDGE EXPONENT OWED (PENDING 1):  n ~ P^s = N^(4s)")
p("=" * 84)
p("  Only meaningful for the reading that survives T2/T3. Under T3 the Boltzmann factor is")
p("  epoch-invariant, so the transition is set purely by density - a genuine density trigger,")
p("  exactly as Prop 5 requires. Ask what n(N) a density trigger needs.")
p()
for name, n_need in (("optical depth tau = 1 at N=1100", 1.0 / (sigma_T * R_CMB)),
                     ("CR14 Branch C thermal rung", 1.0659e4)):
    ratio = n_need / n_b0
    four_s = math.log(ratio) / math.log(z_rec_id)
    p("  %-34s needs n = %.4e m^-3  (%.3e x today)" % (name, n_need, ratio))
    p("  %-34s -> n ~ N^%.4f , i.e. s = %.4f  (P^s)" % ("", four_s, four_s / 4.0))
p()
p("  Prop 13's coasting law gives n ~ N^3 exactly (s = 3/4), which OVERSHOOTS both targets:")
p("      n(1100) = %.4e m^-3 vs the ~1e4 m^-3 a density trigger would need" % nb_T4)
p("  So Prop 13 and a pure density trigger are not simultaneously satisfiable at N = 1100:")
p("      Prop 13 supplies %.3e times more density than the trigger wants."
  % (nb_T4 / 1.0659e4))
p()
p("=" * 84)
p("SUMMARY")
p("=" * 84)
p("  T1  %d/%d reproduce, %d mismatch (rho_s)" % (sum(t1), len(t1), len(t1) - sum(t1)))
p("  T2  %s - trigger at N = %.2f, not 1100 (factor %.0f)"
  % ("FAIL" if not t2_pass else "PASS", N_T2, z_rec_id / N_T2))
p("  T3  no ionised era at any epoch under Prop 5 -> CMB is not a recombination surface")
p("  T4  CR14 Branch E WITHDRAWN (Prop 13 restores optical thickness, tau = %.2e)" % tau_T4)
p("  T5  density trigger wants n ~ N^1.52 (s = 0.38); Prop 13 delivers N^3 (s = 0.75)")
p("=" * 84)

with open("cr15_results.txt", "w", encoding="utf-8") as fh:
    fh.write("\n".join(out) + "\n")
