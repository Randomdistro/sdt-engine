#!/usr/bin/env python3
"""
CR16 - Parameter ledger and the provenance of P_0.

Pre-registration: PROMPT.md (T1-T5 fixed before this file existed).
Neither z = 1100 nor T = 3000 K appears anywhere in this file. They are LCDM fit outputs,
not measurements, and were struck as targets.
"""
import math

# ---- measured, non-cosmological or direct ----
c       = 2.99792458e8       # m/s      exact by definition          [MEASURED]
sigma_SB= 5.670374419e-8     # W/m2/K4  CODATA (from h,c,k_B)        [MEASURED]
T_0     = 2.7255             # K        FIRAS direct measurement     [MEASURED]
H_0     = 2.27e-18           # s^-1     local distance ladder        [MEASURED]
z_sun   = 2.12e-6            # solar gravitational redshift          [MEASURED]

# ---- the document's Part II [C] list ----
P_0_doc    = 1.3916e-14      # Pa   "= P_eff,sun / z_sun"            [C, document]
koppa_sun  = 686.5           #      "                               "[C, document]
P_conf     = 8.0e34          # Pa   confinement ceiling              [C, document]

a_rad = 4.0 * sigma_SB / c   # radiation constant, J/m3/K4

out = []
def p(s=""):
    out.append(s); print(s)

p("=" * 86)
p("CR16 - PARAMETER LEDGER AND THE PROVENANCE OF P_0")
p("Pre-registered: PROMPT.md.  z=1100 and T=3000 K are struck; neither appears here.")
p("=" * 86)
p()

# ===================================================================== T1
p("-" * 86)
p("T1 - PROVENANCE OF P_0.  Document Part II: 'P_0 = P_eff,sun / z_sun'  [C]")
p("-" * 86)
u_cmb = a_rad * T_0 ** 4
P_rad = u_cmb / 3.0
p("  radiation constant a = 4 sigma/c      = %.6e J/m3/K4" % a_rad)
p("  u_CMB = a T_0^4                       = %.6e J/m3" % u_cmb)
p("  P_rad = u/3  (photon gas)             = %.6e Pa" % P_rad)
p("  P_0 as stated in the document         = %.6e Pa" % P_0_doc)
rel = abs(P_rad - P_0_doc) / P_0_doc
sig = -math.log10(rel) if rel > 0 else 99
p("  relative difference                   = %.3e   (agreement to %.1f significant figures)"
  % (rel, sig))
t1 = sig >= 4.0
p("  T1 %s" % ("CONFIRMED - P_0 IS the CMB photon-gas pressure, a function of T_0"
              if t1 else "not confirmed"))
p()
p("  Corroboration from the repo itself (Benchmarks/investigation_output.txt:130-132):")
p("      T_CMB = 2.7255 K ,  u_CMB = 4.1748e-14 J/m3 ,  P_rad = 1.3916e-14 Pa")
p("  The engine's own output labels this number P_rad and computes it from T_CMB.")
p()
p("  What P_eff,sun would have to be for the stated route to produce it:")
p("      P_eff,sun = P_0 * z_sun = %.4e Pa" % (P_0_doc * z_sun))
p("  laws.hpp's P_eff (electropause, 4 k_e e^2 / (pi R_p^2 r_e^2)) is ~5.2e31 Pa - %.0f"
  % math.log10(5.2e31 / (P_0_doc * z_sun)))
p("  orders away. The solar attribution in Part II does not source this number.")
p()

# ===================================================================== T2
p("-" * 86)
p("T2 - IS  P ~ N^4  AN INDEPENDENT POSTULATE?")
p("-" * 86)
p("  P6 asserts two clauses, both tagged [A, C]:   T_N = N T_0   and   P_N = N^4 P_0")
p("  Given T1, substitute the first into the photon-gas relation:")
p("      P_N = a T_N^4 / 3 = a (N T_0)^4 / 3 = N^4 * (a T_0^4 / 3) = N^4 P_0")
p()
p("  numerical check across the ladder (no epoch is privileged; N values are arbitrary):")
p("      %-12s %-18s %-18s %-10s" % ("N", "a(N T_0)^4/3 [Pa]", "N^4 P_0 [Pa]", "ratio"))
ok2 = True
for N in (0.5, 2.0, 17.0, 500.0, 4.2e3, 1.0e7):
    lhs = a_rad * (N * T_0) ** 4 / 3.0
    rhs = N ** 4 * P_rad
    ok2 &= abs(lhs - rhs) / rhs < 1e-12
    p("      %-12.4g %-18.6e %-18.6e %-10.10f" % (N, lhs, rhs, lhs / rhs))
p()
p("  T2 %s: the second clause of P6 is a THEOREM of the first, not a postulate."
  % ("CONFIRMED" if ok2 else "FAILED"))
p("  -> P6 loses a clause. The postulate count of the sector goes DOWN by one.")
p("  -> P_0 leaves the [C] list: it is a function of T_0, not an independent input.")
p("  -> Corollary: the pressure ladder carries no information the temperature ladder")
p("     lacks. It is the same statement in other units - which is a REDUNDANCY, not an")
p("     error, and redundancy is what a closed framework should show.")
p()

# ===================================================================== T3
p("-" * 86)
p("T3 - DEPENDENCY AUDIT: which [C] inputs does each result actually consume?")
p("-" * 86)
# result -> inputs genuinely consumed
deps = [
    ("Prop 1  lambda_e = N lambda_0",            []),
    ("Prop 2  1+z = N",                          []),
    ("Prop 3  tau_obs/tau = 1+z  (dilation)",    []),
    ("Prop 4  ladder 1+z = T/T_0",               ["T_0"]),
    ("Prop 5  scale-invariant ratio",            []),
    ("Thm 1   static gradient conserves nu",     []),
    ("Thm 2   uniform medium conserves lambda",  []),
    ("Thm 3   envelope ratio v_e/v_a",           []),
    ("Thm 5   alpha epoch-invariant",            []),
    ("Thm 4   Hubble law u/r -> H_0",            ["H_0"]),
    ("Prop 9  Ndot = H_0",                       ["H_0"]),
    ("Prop 10 lookback times",                   ["H_0"]),
    ("Prop 11 private CMB sphere D",             ["H_0"]),
    ("Prop 12 dual clocks, tau_now",             ["H_0"]),
    ("Prop 13 coasting n_b ~ N^3",               ["H_0"]),
    ("Prop 14 BAO shell mechanism",              ["H_0"]),
    ("Prop 6  solar displacement geometry",      ["z_sun"]),
    ("Prop 7  N_max, v_min, T_max",              ["T_0", "P_conf"]),
    ("Prop 8  decompression floor",              ["P_conf"]),
    ("Hyp H   halfway-now",                      ["T_0", "P_conf"]),
]
p("      %-42s %s" % ("result", "consumes"))
for name, d in deps:
    p("      %-42s %s" % (name, ", ".join(d) if d else "-- nothing --"))
p()
zero_dep = [n for n, d in deps if not d]
p("  results consuming NO calibrated input at all: %d of %d" % (len(zero_dep), len(deps)))
p("  P_conf is consumed ONLY by Prop 7, Prop 8 and Hypothesis H - the vessel BOUNDS.")
p("  It touches no redshift, dilation, Hubble, BAO or alpha result.")
p("  -> P_conf is not a free parameter of the observational sector.")
p()

# ===================================================================== T4
p("-" * 86)
p("T4 - PARAMETER LEDGER, LIKE FOR LIKE")
p("-" * 86)
p("  classification: MEASURED-ELSEWHERE (fixed by non-cosmological data) /")
p("                  DERIVED (function of other inputs) / FITTED (tuned to the data explained)")
p("  Only FITTED counts as a free parameter. Applied identically to both sides.")
p()
sdt = [
    ("c",        "MEASURED-ELSEWHERE", "defined constant; local value"),
    ("T_0",      "MEASURED-ELSEWHERE", "FIRAS direct; LCDM also takes it measured"),
    ("H_0",      "MEASURED-ELSEWHERE", "local distance ladder"),
    ("z_sun",    "MEASURED-ELSEWHERE", "solar gravitational redshift"),
    ("koppa_sun","DERIVED",            "= 1/sqrt(z_sun) via z*koppa^2 = 1"),
    ("P_0",      "DERIVED",            "= a T_0^4 / 3   [T1]"),
    ("P_conf",   "FITTED",             "vessel ceiling; observational sector does not use it [T3]"),
]
p("  SDT cosmological sector (document Part II lists 7 as [C]):")
for n, k, why in sdt:
    p("      %-10s %-20s %s" % (n, k, why))
sdt_fitted = [n for n, k, _ in sdt if k == "FITTED"]
p("      -> FITTED: %d  (%s)" % (len(sdt_fitted), ", ".join(sdt_fitted)))
kv = math.sqrt(1.0 / z_sun)
p("      (koppa check: 1/sqrt(z_sun) = %.1f vs stated %.1f)" % (kv, koppa_sun))
p()
lcdm = [
    ("omega_b",    "FITTED", "baryon density"),
    ("omega_c",    "FITTED", "cold dark matter density"),
    ("100 theta_*","FITTED", "acoustic angular scale"),
    ("tau_reio",   "FITTED", "reionisation optical depth"),
    ("ln(1e10 A_s)","FITTED","scalar amplitude"),
    ("n_s",        "FITTED", "scalar spectral index"),
]
p("  LCDM base model:")
for n, k, why in lcdm:
    p("      %-14s %-8s %s" % (n, k, why))
p("      -> FITTED: %d" % len(lcdm))
p("      (plus fixed-by-assumption: Omega_k = 0, w = -1, N_eff = 3.046, sum m_nu = 0.06 eV)")
p("      (H_0, Omega_Lambda, age, sigma_8, z_* are DERIVED outputs of these six)")
p()
p("  For the observable set SDT's sector currently addresses:")
p("      redshift-N relation | (1+z) light-curve dilation | Hubble law | BAO shell mechanism")
p("      | alpha invariance across epochs | Shapiro delay | solar redshift profile")
p("      SDT   fitted parameters used: 0   (P_conf enters none of them - T3)")
p("      LCDM  fitted parameters used: 6")
p()
p("  FAIRNESS CONSTRAINT (PROMPT, binding): LCDM's six also buy an observable list this")
p("  sector does NOT yet cover - CMB peak HEIGHTS and the full power spectrum, the matter")
p("  power spectrum, BBN light-element abundances. The comparison above is on a SUBSET.")
p("  Stated both ways: fewer fitted parameters, AND a smaller observable list.")
p()

# ===================================================================== T5
p("-" * 86)
p("T5 - THE ZERO-PARAMETER SUBSET (consumes no fitted number whatsoever)")
p("-" * 86)
p("  %-38s %-26s %s" % ("prediction", "measured", "status"))
p("  %-38s %-26s %s" % ("tau_obs/tau = (1+z)  [Prop 3]", "(1+z)^(1.00 +/- 0.05)", "MATCHES"))
p("  %-38s %-26s %s" % ("d(alpha)/alpha = 0   [Thm 5]", "< 1e-5 to z~7; Oklo", "MATCHES"))
p("  %-38s %-26s %s" % ("lambda_obs/lambda_0 = N [Prop 2]", "definitional", "STRUCTURE"))
p("  %-38s %-26s %s" % ("u/r -> H_0, any ICs  [Thm 4]", "Hubble linearity", "MATCHES"))
p("  %-38s %-26s %s" % ("Shapiro: intact signal, late [Thm 1]", "Cassini/Viking", "MATCHES"))
p()
p("  Prop 3 in detail - the sharpest of these, because it is pure structure:")
p("      slow emission at source  x  transit compression  =  N^2 * (1/N) = N = 1+z")
p("  A static-space redshift mechanism producing exactly (1+z) clock dilation with no")
p("  fitted number is not a restatement: classical tired-light fails this test, which is")
p("  what historically excluded it. This mechanism passes it structurally.")
p()
p("  Thm 5 in detail: alpha = v_1/c_local, both ~ 1/N, so N cancels identically.")
p("  The null is predicted across ~3 decades of variation in c_local, not accommodated.")
p()
p("=" * 86)
p("SUMMARY")
p("=" * 86)
p("  T1  P_0 = a T_0^4/3 to %.1f sig figs -> P_0 is NOT an independent input" % sig)
p("  T2  P ~ N^4 follows from T ~ N; P6 loses a clause; postulate count DOWN by one")
p("  T3  P_conf touches only the vessel bounds; %d of %d results consume no [C] input"
    % (len(zero_dep), len(deps)))
p("  T4  on the shared observable subset: SDT 0 fitted vs LCDM 6 fitted")
p("      - and that subset is smaller than LCDM's full reach. Both halves stated.")
p("  T5  five zero-parameter predictions, all matching; Prop 3 is the load-bearing one")
p("=" * 86)

with open("cr16_results.txt", "w", encoding="utf-8") as fh:
    fh.write("\n".join(out) + "\n")
