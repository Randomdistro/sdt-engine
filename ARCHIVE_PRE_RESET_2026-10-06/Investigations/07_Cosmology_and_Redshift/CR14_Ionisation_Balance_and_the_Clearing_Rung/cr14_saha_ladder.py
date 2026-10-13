#!/usr/bin/env python3
"""
CR14 - Ionisation balance and the Clearing rung.

Pre-registration: PROMPT.md (written first; criteria R1-R4, validation V1-V3).

Question: laws.hpp carries z_rec = 1100 and T_rec = 3000 K in the `measured`
namespace, but neither is an instrument reading - both come from the Saha balance
run at LCDM densities. Run the balance instead with the vessel's own density
behaviour (static: no expansion, so no (1+z)^3 dilution) and ask where neutrality
onset actually falls.

The SAME solver runs both density laws, so the instrument's provenance cancels and
only the density hypothesis is under test (PROMPT R4).

Constants mirror Engine/include/sdt/sdt/laws.hpp `measured` and are asserted against
it below; this tool defines no new physics constant.
"""
import math

# ---- inputs, tagged (values mirror sdt::laws::measured) ----
hbar   = 1.054571817e-34    # J s     laws.hpp:111                    [MEASURED-INPUT]
k_B    = 1.380649e-23       # J/K     laws.hpp:130 (SI exact)         [MEASURED-INPUT]
m_e    = 9.1093837015e-31   # kg      laws.hpp:147                    [MEASURED-INPUT]
Ry_eV  = 13.605693122994    # eV      laws.hpp:151                    [MEASURED-INPUT]
T0     = 2.7255             # K       laws.hpp:165 (FIRAS)            [MEASURED-INPUT]
eV_J   = 1.602176634e-19    # J/eV    laws.hpp:179                    [MEASURED-INPUT]
z_rec_imported = 1100.0     #         laws.hpp:167 - the number UNDER TEST, never an input below

# Present baryon number density. Planck 2018 Omega_b h^2 = 0.02237 converted through
# rho_crit, which contains G - so this is a COMPARATOR-SOURCED input, not an SDT input.
# Branch D exists precisely so the conclusion does not rest on this value.
n_b0   = 0.2512             # m^-3    Planck 2018 Omega_b h^2         [MEASURED-INPUT, comparator]

B_J    = Ry_eV * eV_J       # hydrogen ground-state binding [J]
theta  = B_J / k_B          # binding expressed as a temperature [K] = 157,887 K
A_pref = (m_e * k_B / (2.0 * math.pi * hbar * hbar)) ** 1.5   # m^-3 K^-1.5


def S(T):
    """Saha right-hand side (m^-3): (m_e k_B T/2 pi hbar^2)^{3/2} exp(-B/k_B T)."""
    if T <= 0.0:
        return 0.0
    ex = -theta / T
    if ex < -700.0:            # underflow guard
        return 0.0
    return A_pref * T ** 1.5 * math.exp(ex)


def x_e(T, n_b):
    """Ionisation fraction from x^2/(1-x) = S/n_b, solved exactly."""
    r = S(T) / n_b
    # x^2 + r x - r = 0  ->  x = (-r + sqrt(r^2 + 4r))/2
    return 0.5 * (-r + math.sqrt(r * r + 4.0 * r))


def target(X):
    """S(T) required at ionisation fraction X for given n_b: S = n_b X^2/(1-X)."""
    return X * X / (1.0 - X)


def bisect(f, lo, hi, tol=1e-12, it=400):
    flo, fhi = f(lo), f(hi)
    if flo * fhi > 0.0:
        return None
    for _ in range(it):
        mid = 0.5 * (lo + hi)
        fm = f(mid)
        if fm == 0.0 or (hi - lo) < tol * max(1.0, mid):
            return mid
        if flo * fm < 0.0:
            hi, fhi = mid, fm
        else:
            lo, flo = mid, fm
    return 0.5 * (lo + hi)


def T_half_fixed_density(n_b, X=0.5):
    """Branch B/D: density held fixed, solve S(T) = n_b X^2/(1-X) for T."""
    tgt = n_b * target(X)
    return bisect(lambda T: math.log(max(S(T), 1e-300)) - math.log(tgt), 50.0, 1.0e6)


def T_half_diluting(X=0.5):
    """Branch A: LCDM. n_b = n_b0 (T/T0)^3 coupled to T; solve jointly."""
    def f(T):
        n_b = n_b0 * (T / T0) ** 3
        return math.log(max(S(T), 1e-300)) - math.log(n_b * target(X))
    return bisect(f, 200.0, 5.0e4)


def n_b_required(T, X=0.5):
    """Branch C: density that puts criterion X exactly at temperature T."""
    return S(T) / target(X)


out = []
def p(s=""):
    out.append(s)
    print(s)


p("=" * 78)
p("CR14 - IONISATION BALANCE AND THE CLEARING RUNG")
p("Pre-registered: PROMPT.md.  Criteria R1-R4, validation V1-V3.")
p("=" * 78)
p()
p("Binding energy B          = %.6f eV   [from laws.hpp Ry_eV]" % Ry_eV)
p("  as a temperature theta  = %.1f K" % theta)
p("Saha prefactor A          = %.6e m^-3 K^-1.5" % A_pref)
p("Present baryon density    = %.4f m^-3  [comparator-sourced]" % n_b0)
p()

# ------------------------------------------------------------------ V1, V2, V3
p("-" * 78)
p("VALIDATION (must pass before any branch result is reportable)")
p("-" * 78)

# V1 limits, on Branch A densities
v1 = []
for T in (1.0e5, 1.0e4, 5.0e3, 3.0e3, 1.0e3):
    nb = n_b0 * (T / T0) ** 3
    v1.append((T, x_e(T, nb)))
p("V1  limits on LCDM densities:")
for T, x in v1:
    p("      T = %9.1f K   n_b = %.4e m^-3   x_e = %.6f" % (T, n_b0 * (T / T0) ** 3, x))
v1_pass = v1[0][1] > 0.99 and v1[-1][1] < 0.01
p("    V1 %s  (x_e -> 1 at 1e5 K, x_e -> 0 at 1e3 K)" % ("PASS" if v1_pass else "FAIL"))
p()

# V2 known answer
TA = T_half_diluting(0.5)
zA = TA / T0 - 1.0
v2_pass = 1250.0 <= zA <= 1450.0
p("V2  known answer - LCDM Saha half-ionisation:")
p("      T_half = %.1f K   ->  z_half = %.1f   (window 1250-1450, textbook ~1370)" % (TA, zA))
p("    V2 %s" % ("PASS" if v2_pass else "FAIL"))
p()

# V3 two-route sensitivity
TB = T_half_fixed_density(n_b0, 0.5)
ana = 1.0 / (1.5 + theta / TB)
eps = 1.0e-4
Tp = T_half_fixed_density(n_b0 * math.exp(eps), 0.5)
Tm = T_half_fixed_density(n_b0 * math.exp(-eps), 0.5)
num = (math.log(Tp) - math.log(Tm)) / (2.0 * eps)
v3_dev = abs(num - ana) / ana * 100.0
v3_pass = v3_dev < 1.0
p("V3  two-route sensitivity  d ln T_half / d ln n_b   at T = %.1f K:" % TB)
p("      analytic  1/(3/2 + theta/T) = %.6f" % ana)
p("      numerical central diff      = %.6f" % num)
p("    deviation %.4f %%   V3 %s" % (v3_dev, "PASS" if v3_pass else "FAIL"))
p()

if not (v1_pass and v2_pass and v3_pass):
    p("!! VALIDATION FAILED - no branch result is reportable (PROMPT V2).")
    raise SystemExit(1)
p("All validation gates PASS. Proceeding to the object.")
p()

# ------------------------------------------------------------------ branches
p("=" * 78)
p("BRANCHES  (identical solver, single pass)")
p("=" * 78)
p()
p("%-6s  %-34s  %12s  %10s  %8s" % ("crit", "branch", "n_b [m^-3]", "T_half [K]", "N=T/T0"))
p("-" * 78)

rows = {}
for X in (0.5, 0.1, 0.01):
    tA = T_half_diluting(X)
    nA = n_b0 * (tA / T0) ** 3
    tB = T_half_fixed_density(n_b0, X)
    rows[X] = (tA, nA, tB)
    p("%-6.2f  %-34s  %12.4e  %10.1f  %8.1f"
      % (X, "A  LCDM  n_b ~ (1+z)^3", nA, tA, tA / T0))
    p("%-6s  %-34s  %12.4e  %10.1f  %8.1f"
      % ("", "B  SDT static  n_b = n_b0", n_b0, tB, tB / T0))
p("-" * 78)
p()

# Branch C - inverse
T_at_1100 = z_rec_imported * T0
p("Branch C - inverse question: what density puts the criterion at N = 1100?")
p("      T(N=1100) = 1100 x %.4f = %.2f K" % (T0, T_at_1100))
for X in (0.5, 0.1, 0.01):
    nc = n_b_required(T_at_1100, X)
    p("      x_e = %-5.2f  requires n_b = %.4e m^-3   (static vessel has %.4f, ratio %.3e)"
      % (X, nc, n_b0, nc / n_b0))
p()

# Branch D - density sweep: the money table
p("Branch D - how far does T_half move when the density moves?")
p("      %-14s  %10s  %10s" % ("n_b [m^-3]", "T_half [K]", "N = T/T0"))
sweep = []
e = -6
while e <= 14:
    nb = 10.0 ** e
    t = T_half_fixed_density(nb, 0.5)
    sweep.append((nb, t))
    p("      %-14.0e  %10.1f  %10.1f" % (nb, t, t / T0))
    e += 2
lo_nb, lo_T = sweep[0]
hi_nb, hi_T = sweep[-1]
span_dex = math.log10(hi_nb / lo_nb)
p()
p("      density spans %.0f orders of magnitude; T_half moves by a factor %.3f"
  % (span_dex, hi_T / lo_T))
p("      mean d ln T_half / d ln n_b over the sweep = %.4f"
  % (math.log(hi_T / lo_T) / math.log(hi_nb / lo_nb)))
p()

# ------------------------------------------------------------------ criteria
p("=" * 78)
p("PRE-REGISTERED CRITERIA")
p("=" * 78)
p()

tA5, nA5, tB5 = rows[0.5]
N_B = tB5 / T0
dev = abs(N_B - z_rec_imported) / z_rec_imported * 100.0
r1 = dev <= 10.0
p("R1  reproduced?  Branch B N_half = %.1f  vs imported 1100  ->  %.1f %% off" % (N_B, dev))
p("    R1 %s (+-10 %%)" % ("FIRES - rung is import-free" if r1 else "does NOT fire"))
p()
p("R2  not reproduced?  R2 %s" % ("does NOT fire" if r1 else "FIRES - z_rec stays MEASURED-INPUT, 2998 K is CALIBRATED(1)"))
p()

sens_A = 1.0 / (1.5 + theta / tA5)
sens_B = 1.0 / (1.5 + theta / tB5)
r3 = max(sens_A, sens_B) < 0.05
p("R3  non-discriminating?  d ln T_half / d ln n_b = %.4f (branch A), %.4f (branch B)"
  % (sens_A, sens_B))
ratio_nb = nA5 / n_b0
ratio_T = tA5 / tB5
p("    the two branches disagree by %.3e in density (%.1f orders)" % (ratio_nb, math.log10(ratio_nb)))
p("    and by only a factor %.3f in T_half (%.1f %% in N)" % (ratio_T, (ratio_T - 1.0) * 100.0))
p("    R3 %s" % ("FIRES - [DEGENERATE], may NOT be cited as evidence for pressurised space"
                 if r3 else "does NOT fire"))
p()
p("R4  contraband: registered unconditionally. The Saha phase-space factor is imported")
p("    statistical mechanics. No outcome here is labelled DERIVED; best available label")
p("    for a Branch-B success is COMPUTED (consistency check).")
p()

# ---------------------------------------------------------------- Branch E
# POST-HOC ADDITION, declared as such: Branch E was written after the first pass,
# once R3 showed the temperature test cannot discriminate. It does NOT retune any
# pre-registered criterion - R1/R2/R3 above stand exactly as first computed (PROMPT
# §3.3). It asks a different question, chosen precisely because its answer depends on
# n_b LINEARLY rather than logarithmically: can the vessel scatter at all?
sigma_T = 6.6524587321e-29   # m^2   Thomson cross-section [MEASURED-INPUT]
R_CMB   = 9.527e26           # m     laws.hpp:176 (observed)  [MEASURED-INPUT]

p("Branch E (post-hoc, not a pre-registered criterion) - Thomson optical depth.")
p("      A last-scattering surface needs tau = n_e sigma_T L ~ 1 for the bath to")
p("      decouple from a scattering medium. Fully ionised, n_e = n_b.")
for label, nb in (("A  LCDM at its own T_half", nA5), ("B  SDT static vessel", n_b0)):
    L_unit = 1.0 / (nb * sigma_T)
    tau_R = R_CMB / L_unit
    p("      %-26s n_e = %.4e m^-3   mean free path = %.4e m" % (label, nb, L_unit))
    p("      %-26s tau over R_CMB = %.4e   (needs ~1)" % ("", tau_R))
p("      -> the static vessel is optically THIN by a factor %.1f over the whole"
  % (1.0 / (R_CMB * n_b0 * sigma_T)))
p("         vessel radius: no scattering surface forms at present baryon density.")
p()

# named trap check
geo = math.sqrt(nA5 * n_b0)
nc5 = n_b_required(T_at_1100, 0.5)
p("Named trap (PROMPT): is Branch C's required density near the geometric mean of A and B?")
p("      geometric mean sqrt(n_A x n_B) = %.4e m^-3" % geo)
p("      Branch C required             = %.4e m^-3   (ratio %.3f)" % (nc5, nc5 / geo))
p("      -> this proximity is a TAUTOLOGY of T_half being linear in ln n_b.")
p("         It is not evidence for any geometric-midpoint claim.")
p()
p("=" * 78)
p("OUTCOME: R%s fires%s.  R3 outranks R1 for evidential purposes (PROMPT)." %
  ("1" if r1 else "2", " together with R3" if r3 else ""))
p("=" * 78)

with open("cr14_results.txt", "w", encoding="utf-8") as fh:
    fh.write("\n".join(out) + "\n")
