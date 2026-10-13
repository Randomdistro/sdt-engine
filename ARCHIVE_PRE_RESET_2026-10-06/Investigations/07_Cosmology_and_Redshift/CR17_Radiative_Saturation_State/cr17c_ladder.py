#!/usr/bin/env python3
"""
CR17c - The ladder read from where the observer actually stands.

Narrative correction (Harvey, 2026-07-31): the earlier "one step past red" wording put the
reader IN COLOUR and stepped outward. The reader is not in colour. The reader is in the
MICROWAVE - 2.7255 K, peak 1.063 mm - and travelling into the past means going UP the
spectrum toward shorter wavelengths. The Clearing is what you meet coming up. Everything
shorter than it is behind the wall.

Each rung: lambda_peak -> T = b/lambda -> N = T/T_0 -> v = c/N -> P = N^4 P_0 -> R = obstacle
loading. No epoch is imported. The rungs are wavelengths; everything else is forced.
"""
import math

c        = 2.99792458e8
sigma_SB = 5.670374419e-8
b_wien   = 2.897771955e-3
T_0      = 2.7255
k_B      = 1.380649e-23
h_pl     = 6.62607015e-34
m_p      = 1.67262192369e-27
eta_BBN  = 6.1e-10
zeta3    = 1.2020569031595943

a_rad  = 4.0 * sigma_SB / c
P_0    = a_rad * T_0 ** 4 / 3.0
n_gam0 = 16.0 * math.pi * zeta3 * (k_B * T_0 / (h_pl * c)) ** 3
rho_g0 = a_rad * T_0 ** 4 / c ** 2
rho_b0 = eta_BBN * n_gam0 * m_p
R_coef = 0.75 * rho_b0 / rho_g0          # R(N) = R_coef / N ; R = 1 is the depinning point
N_clear = R_coef
lam_clear = b_wien / (T_0 * N_clear)

out = []
def p(s=""):
    out.append(s); print(s)

p("=" * 100)
p("CR17c - THE LADDER FROM WHERE WE STAND: MICROWAVE, LOOKING UP")
p("=" * 100)
p()
p("  You are here:  T = %.4f K ,  peak wavelength = %.4f mm  (microwave) ,  N = 1"
  % (T_0, b_wien / T_0 * 1e3))
p("  Into the past = UP the spectrum: shorter wavelength, hotter, denser, slower light.")
p("  Depinning (obstacle loading R = 1) at N = %.1f , peak = %.0f nm."
  % (N_clear, lam_clear * 1e9))
p("  Rungs at or beyond that N are BEHIND THE WALL - jammed, never received.")
p()

rungs = [
    (b_wien / T_0, "microwave - here, now"),
    (300e-6,  "sub-millimetre"),
    (100e-6,  "far infrared"),
    (30e-6,   "far infrared"),
    (10e-6,   "mid infrared"),
    (3e-6,    "short-wave infrared"),
    (2500e-9, "short-wave infrared"),
    (2000e-9, "short-wave infrared"),
    (lam_clear, ">>> THE CLEARING  (R = 1) <<<"),
    (1400e-9, "near infrared"),
    (1179e-9, "near infrared   (rho_b = rho_gamma)"),
    (1000e-9, "near infrared"),
    (975e-9,  "near infrared"),
    (900e-9,  "near infrared"),
    (780e-9,  "near infrared onset"),
    (750e-9,  "RED  - the visible edge"),
    (700e-9,  "red"),
    (625e-9,  "red / orange"),
    (590e-9,  "orange / yellow"),
    (565e-9,  "yellow / green"),
    (500e-9,  "green / cyan"),
    (485e-9,  "cyan / blue"),
    (450e-9,  "blue / violet"),
    (380e-9,  "violet - the far visible edge"),
    (100e-9,  "ultraviolet"),
    (10e-9,   "extreme ultraviolet"),
    (1e-9,    "X-ray"),
    (1e-12,   "gamma"),
]

p("  %-11s %-34s %-11s %-11s %-11s %-11s %-8s %s"
  % ("lambda", "band", "T [K]", "N", "v [m/s]", "P [Pa]", "R", "received?"))
p("  " + "-" * 96)
for lam, name in rungs:
    T = b_wien / lam
    N = T / T_0
    v = c / N
    P = N ** 4 * P_0
    R = R_coef / N
    seen = "yes" if N < N_clear else ("--- WALL ---" if abs(N - N_clear) < 1e-6 else "behind wall")
    lam_s = ("%.4g mm" % (lam * 1e3)) if lam >= 1e-4 else (
            ("%.4g um" % (lam * 1e6)) if lam >= 1e-6 else (
            ("%.4g nm" % (lam * 1e9)) if lam >= 1e-11 else ("%.4g pm" % (lam * 1e12))))
    p("  %-11s %-34s %-11.4g %-11.4g %-11.4g %-11.4g %-8.3g %s"
      % (lam_s, name, T, N, v, P, R, seen))
p()

# ---------------------------------------------------------------- what the ladder says
T_red, lam_red = b_wien / 750e-9, 750e-9
N_red = T_red / T_0
p("-" * 100)
p("WHAT THE LADDER SAYS")
p("-" * 100)
p("  1. Distance from here to the wall, travelling up:")
p("       %.4f mm  ->  %.0f nm      = %.2f decades in wavelength, x%.0f in N"
  % (b_wien / T_0 * 1e3, lam_clear * 1e9, math.log10((b_wien / T_0) / lam_clear), N_clear))
p()
p("  2. Red is NOT reached. The visible edge sits at 750 nm, N = %.0f," % N_red)
p("     which is x%.2f BEYOND the wall at N = %.0f." % (N_red / N_clear, N_clear))
p("     Coming up from microwave you meet the Clearing in the near infrared and stop.")
p("     The whole visible spectrum - N = %.0f to %.0f - lies behind it, jammed."
  % (N_red, b_wien / 380e-9 / T_0))
p()
p("  3. So 'one step past red' had the reader starting in colour and stepping outward.")
p("     From the observer's actual position the step is the other way, and colour is on")
p("     the far side of the wall. Nothing in the visible was ever received directly.")
p()
p("  4. The visible spectrum is a narrow slice of the vessel: N = %.0f ... %.0f is only"
  % (N_red, b_wien / 380e-9 / T_0))
p("     %.2f decades, against %.2f decades from here to the P_eff ceiling."
  % (math.log10((b_wien / 380e-9 / T_0) / N_red), math.log10(2.4754e11)))
p()

# ---------------------------------------------------------------- the sweep, not a knife edge
p("-" * 100)
p("THE CLEARING IS A SWEEP, NOT A KNIFE EDGE")
p("-" * 100)
p("  Obstacle loading runs as R = %.1f / N, so the transition has width in R, not a step."
  % R_coef)
p("  %-28s %-10s %-12s %-11s %-11s" % ("loading", "N", "lambda [nm]", "T [K]", "v [m/s]"))
for lbl, R in (("R = 0.5  jam still winning", 0.5),
               ("R = 0.6  drag epoch (CR13)", 0.6),
               ("R = 1.0  depinning", 1.0),
               ("R = 2.0  obstacles dominant", 2.0)):
    N = R_coef / R
    p("  %-28s %-10.1f %-12.0f %-11.0f %-11.4g"
      % (lbl, N, b_wien / (T_0 * N) * 1e9, N * T_0, c / N))
p()
p("  The window R = 0.6 -> 1.0 runs %.0f nm -> %.0f nm, N = %.0f -> %.0f."
  % (b_wien / (T_0 * R_coef / 0.6) * 1e9, lam_clear * 1e9, R_coef / 0.6, N_clear))
p("  That is the gradual clearing - a swept band in the infrared, entirely short of red.")
p("  CR13's independently-used drag-epoch R = 0.6 lands inside it, which is a consistency")
p("  check on the loading law, not a second result.")
p()
p("=" * 100)
p("  Read it from the microwave upward and the ladder tells its own story: the bath was")
p("  infrared when it let go, and every colour is behind the wall.")
p("=" * 100)

with open("cr17c_results.txt", "w", encoding="utf-8") as fh:
    fh.write("\n".join(out) + "\n")
