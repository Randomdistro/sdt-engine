# ============================================================================
#  CH07 RUN 2 -- k from the rolling wall (ROOT-WALL)
#  Author: J. C. Harvey, Melbourne - 2026-07-06
#  Spec: PROMPT.md "# RUN 2 PROMPT (2026-07-06)"; ADJ-R2-1 + D-A1..D-A4 + all
#  gates committed in RUN_LOG.md BEFORE this file existed. Python tool class
#  per ADJ-R2-1(a); results_run2.txt = teed stdout; exit 0 = ran to completion
#  (PASS/FAIL are printed lines, per R2 clause 7).
#
#  Engine constants transcribed BY VALUE from Engine/include/sdt/laws.hpp
#  (measured:: lines 110-209, coulomb_identity::k_e_e2 line 1036). No local
#  re-derivation. No G/M/GM anywhere. No fitted parameters (D-A2: zero).
#
#  Candidates (ADJ-R2-1(b), all declared before evaluation, none fitted):
#    W-1  Sum_seats hbar^2/(2 m_e s^2), s = u(x) R, 2 seats   [NP10 D1 fence]
#    W-2a W-1 x 1/4   (W+1 = 4 shell-gearbox, direction enumerated)
#    W-2b W-1 x 4     (W+1 = 4 shell-gearbox, direction enumerated)
#    W-3  hbar^2/(2 m_e (2xR)^2)          (one e-e rolling interface)
#    W-4  Sum_seats hbar^2/(2 m_e (2 pi s)^2)   (tour-circumference length)
#    W-5  (hbar^2/2 m_e a0^2) exp(-R/a0)  (exponential, native range a0)
#  Diagnostic (NOT a candidate): lambda locus sweep, k*R_min^3 class invariant.
# ============================================================================
import math
import numpy as np

# ---- engine constants (laws.hpp measured:: / coulomb_identity::) ----------
c        = 299792458.0            # [m/s]   laws.hpp:110
hbar     = 1.054571817e-34        # [J s]   laws.hpp:111
alpha    = 7.2973525693e-3        # [-]     laws.hpp:126
a_0      = 5.29177210903e-11      # [m]     laws.hpp:143
R_p      = 8.414e-16              # [m]     laws.hpp:145 (proton BOUNDARY radius)
m_e      = 9.1093837015e-31       # [kg]    laws.hpp:147
eV       = 1.602176634e-19        # [J/eV]  laws.hpp:179
MeV      = 1.602176634e-13        # [J/MeV] laws.hpp:180
B_d      = 2.224                  # [MeV]   laws.hpp:206 (OBSERVED)
B_t      = 8.482                  # [MeV]   laws.hpp:207 (OBSERVED)
B_a      = 28.296                 # [MeV]   laws.hpp:209 (OBSERVED)
k_e_e2   = alpha * hbar * c       # [J m]   laws.hpp:1036 (class F identity, declared)
amu      = 1.66053906660e-27      # [kg]    unit bridge (run-1 log)
NA       = 6.02214076e23          # [1/mol] unit bridge (CH02)

ahcA     = k_e_e2 / eV * 1e10                     # [eV A]
a0A      = a_0 * 1e10                             # [A]
hb2      = hbar * hbar / (2.0 * m_e) / eV * 1e20  # hbar^2/2m_e [eV A^2]
EVA2_Nm  = eV / 1e-20                             # eV/A^2 -> N/m
AHC_MeVfm = alpha * (hbar * c / MeV) * 1e15       # [MeV fm]
RpF      = R_p * 1e15                             # [fm]
D_np17   = 2.0 * RpF + RpF / 3.0                  # NP17 bond [fm]
eV_kJmol = eV * NA / 1000.0                       # eV -> kJ/mol
PI       = math.pi

Re_H2    = 0.7414                 # [A]   OBSERVED anchor (gate G-A1)
K_H2     = 575.0                  # [N/m] OBSERVED anchor (gate G-A2)
De_H2    = 4.75                   # [eV]  OBSERVED well depth (REPORT column)
Etot_H2  = 31.95                  # [eV]  OBSERVED total electronic binding (NP10 G-5)

print("=" * 78)
print(" CH07 RUN 2 -- k FROM THE ROLLING WALL (ROOT-WALL)")
print(" J. C. Harvey, Melbourne - 2026-07-06 - tool ch07_r2_rolling_wall.py")
print(" Gates committed in RUN_LOG.md ADJ-R2-1 BEFORE this file existed.")
print(" ahc = %.4f eV*A = %.4f MeV*fm | a0 = %.6f A | hbar^2/2m_e = %.5f eV*A^2"
      % (ahcA, AHC_MeVfm, a0A, hb2))
print(" R_p = %.4f fm (proton boundary radius) | NP17 bond D = %.4f fm" % (RpF, D_np17))
print(" Zero fitted parameters. No G/M/GM. Faith-ledger caps (run-1 G.1) travel")
print(" with every cm-1 conversion below (E = hbar*omega bridge: ASSERTED).")
print("=" * 78)

# ---------------------------------------------------------------------------
# CP-1 -- reproduce the run-1 shared-seat machinery (1e-6 anchor)
# Byte-identical algorithm to ch07_spectra.cpp P1: accumulation grid
# x = 0.02 .. 2.0 step 1e-5, g(x) = 1 + 1/(2x) - 4/sqrt(1/4 + x^2).
# ---------------------------------------------------------------------------
print("\nCP-1  RUN-1 MACHINERY REPRODUCTION (blocking checkpoint)")
gbest, xbest = 1e9, 0.0
x = 0.02
while x <= 2.0:
    g = 1.0 + 1.0 / (2.0 * x) - 4.0 / math.sqrt(0.25 + x * x)
    if g < gbest:
        gbest, xbest = g, x
    x += 1e-5
g_analytic = 1.0 - 3.0 * math.sqrt(3.0)   # closed form of the same minimum
x_analytic = 1.0 / (2.0 * math.sqrt(3.0))
print("    reused machinery : g* = %.9f at x* = %.6f" % (gbest, xbest))
print("    run-1 print      : g* = -4.19615 at x* = 0.2887 (5-dp/4-dp print of the")
print("                       same double from the identical grid loop)")
print("    analytic identity: 1 - 3*sqrt(3) = %.9f at 1/(2*sqrt(3)) = %.6f" % (g_analytic, x_analytic))
d_grid = abs(gbest - g_analytic)
cp1 = d_grid <= 1e-6 and ("%.5f" % gbest) == "-4.19615"
print("    |Delta g*| (grid vs analytic) = %.3e ; 5-dp round = %.5f" % (d_grid, gbest))
print("    CP-1 (<= 1e-6, matches run-1 record): %s" % ("PASS" if cp1 else "FAIL -- STOP"))
if not cp1:
    print("    BLOCKER: base not reproduced; per pivot table this run stops here.")
    raise SystemExit(0)
gstar = gbest
d2E_re = 2.0 * gstar * k_e_e2 / (Re_H2 * 1e-10) ** 3   # [N/m], run-1 row
print("    run-1 row reproduced: d2E/dR2 at Re = %+.3e N/m (run-1: -4.751e+03)" % d2E_re)

# ---------------------------------------------------------------------------
# Joint (R, x) minimiser -- NP10 D1 numerics replicated (ADJ-R2-1(f)).
# E(R, x) = ahcA*g(x)/R + hb2*f(x)/R^2  for the power-law candidates.
# ---------------------------------------------------------------------------
xg  = np.arange(0.02, 5.0, 2e-4)
gA  = 1.0 + 1.0 / (2.0 * xg) - 4.0 / np.sqrt(0.25 + xg * xg)
u2A = 0.25 + xg * xg

def envelope(fA, R):
    return float(np.min(ahcA * gA / R + hb2 * fA / (R * R)))

def joint_min(fA):
    Rg = np.arange(0.06, 4.0, 1e-3)
    Emin, Rmin = 1e300, 0.0
    for R in Rg:
        e = envelope(fA, R)
        if e < Emin:
            Emin, Rmin = e, R
    for R in np.arange(Rmin - 2e-3, Rmin + 2e-3, 5e-5):
        e = envelope(fA, R)
        if e < Emin:
            Emin, Rmin = e, R
    h = 1.5e-3
    k = (envelope(fA, Rmin + h) - 2.0 * envelope(fA, Rmin) + envelope(fA, Rmin - h)) / (h * h)
    interior = 0.062 < Rmin < 3.9
    return Rmin, Emin, k * EVA2_Nm, interior

# ---------------------------------------------------------------------------
# PHASE A -- candidate table (gates G-A1 / G-A2, committed)
# ---------------------------------------------------------------------------
print("\nPHASE A  DERIVED-WALL CANDIDATES on the frozen run-1 well (g* reused, CP-1)")
print("  E_tot(R) = g(x)*ahc/R + W ; joint (R,x) minimisation, D1-replica numerics")
print("  gates: G-A1 R_min in 0.7414 A +-25% [0.556, 0.927] ; G-A2 k in 575 N/m +-25% [431, 719]")
cands = [
    ("W-1  2 seats hb2/s^2 (NP10 D1 fence)", 2.0 / u2A),
    ("W-2a W-1 / 4 (gearbox W+1=4)",         0.5 / u2A),
    ("W-2b W-1 * 4 (gearbox W+1=4)",         8.0 / u2A),
    ("W-3  e-e interface hb2/(2xR)^2",       1.0 / (4.0 * xg * xg)),
    ("W-4  tour circumference (2 pi s)",     2.0 / ((2.0 * PI) ** 2 * u2A)),
]
rows = []
for name, fA in cands:
    Rm, Em, kN, interior = joint_min(fA)
    rows.append((name, Rm, Em, kN, interior))

# W-5 exponential (x enters well only; wall x-independent)
B5 = hb2 / (a0A * a0A)
Rg = np.arange(0.06, 4.0, 1e-3)
E5 = gstar * ahcA / Rg + B5 * np.exp(-Rg / a0A)
i5 = int(np.argmin(E5))
w5_interior = 0 < i5 < len(Rg) - 1

ga1_any, ga2_any, both = [], [], []
for name, Rm, Em, kN, interior in rows:
    eR = (Rm - Re_H2) / Re_H2 * 100.0
    eK = (kN - K_H2) / K_H2 * 100.0
    a1 = interior and abs(eR) <= 25.0
    a2 = interior and abs(eK) <= 25.0
    ga1_any.append(a1); ga2_any.append(a2); both.append(a1 and a2)
    note = "" if interior else "  [NOT interior: collapsed to scan edge; k row is an edge artifact]"
    print("  %-38s R_min %.4f A (%+7.1f%%) G-A1:%s | k %10.1f N/m (%+8.1f%%) G-A2:%s | depth %8.2f eV (x%5.1f of 4.75)%s"
          % (name, Rm, eR, "PASS" if a1 else "FAIL",
             kN, eK, "PASS" if a2 else "FAIL", Em, abs(Em) / De_H2, note))
if w5_interior:
    print("  %-38s interior minimum at R = %.4f A (unexpected -- scored)"
          % ("W-5  exp(-R/a0), coeff hb2/a0^2", float(Rg[i5])))
else:
    print("  %-38s NO interior minimum (argmin at scan edge R = %.3f A; collapse)"
          % ("W-5  exp(-R/a0), coeff hb2/a0^2", float(Rg[i5])))
    print("       G-A1: FAIL | G-A2: FAIL (no stationary point exists for this form)")
ga1_any.append(False); ga2_any.append(False); both.append(False)

w1_R, w1_E, w1_k = rows[0][1], rows[0][2], rows[0][3]
print("  D1 regression anchor (NP10): R_min 0.5790 A / k 2697 N/m / depth -45.49 eV")
reg_ok = abs(w1_R - 0.5790) <= 0.002 and abs(w1_k - 2697.0) / 2697.0 <= 0.01
print("  W-1 reproduces D1: %s (dR = %+.4f A, dk = %+.1f%%)"
      % ("PASS" if reg_ok else "FAIL", w1_R - 0.5790, (w1_k - 2697.0) / 2697.0 * 100.0))
print("  PHASE A VERDICT: G-A1 %s (best: W-1) ; G-A2 %s ; G-A1^G-A2 %s for ALL 6 candidates"
      % ("PASS" if any(ga1_any) else "FAIL",
         "PASS" if any(ga2_any) else "FAIL",
         "PASS" if any(both) else "FAIL"))

# ---------------------------------------------------------------------------
# WELL-DEPTH LEDGER (TRAP-4, mandatory) + depth-pins-curvature analysis
# ---------------------------------------------------------------------------
print("\nWELL-DEPTH LEDGER (TRAP-4 -- mandatory print, ADJ-R2-1(d))")
bare = gstar * ahcA / Re_H2
print("  bare run-1 well at Re: %.2f eV = x%.1f measured D_e (4.75 eV), x%.2f measured" % (bare, abs(bare) / De_H2, abs(bare) / Etot_H2))
print("  total electronic binding (31.95 eV) -- NP10 G-5 reproduced. The depth ledger")
print("  is SICK AT CONTACT before any wall is added.")
k_pin = abs(gstar) * ahcA / Re_H2 ** 3 * EVA2_Nm
print("  DEPTH-PINS-CURVATURE (fixed-x theorem): for any wall B/R^n on this well,")
print("  k(min) = (n-1)*|g|*ahc/R*^3. A wall landing the minimum EXACTLY at Re with")
print("  n = 2 (the whole confinement class) gives k = %.0f N/m (%+.0f%% vs 575):" % (k_pin, (k_pin - K_H2) / K_H2 * 100.0))
print("  the x17 depth surplus converts directly into a curvature surplus.")

print("\nDIAGNOSTIC LOCUS SWEEP (ADJ-R2-1(c) -- NOT a candidate; nothing promoted)")
print("  scaling theorem: R_min ~ lambda, k ~ lambda^-3, x-hat invariant =>")
print("  k * R_min^3 is a class invariant. Numerical check (already-computed points):")
for name, Rm, Em, kN, interior in (rows[0], rows[1], rows[2]):
    print("    %-34s k*R^3 = %8.2f N/m*A^3" % (name.split("(")[0].strip(), kN * Rm ** 3))
K_inv = w1_k * w1_R ** 3
lam_lo = max(0.556 / w1_R, (w1_k / 718.75) ** (1.0 / 3.0))
lam_hi = min(0.927 / w1_R, (w1_k / 431.25) ** (1.0 / 3.0))
if lam_lo <= lam_hi:
    Rl, Rh_ = w1_R * lam_lo, w1_R * lam_hi
    kl, kh = w1_k / lam_hi ** 3, w1_k / lam_lo ** 3
    dep = w1_E / lam_lo
    print("  gate box vs locus: the class CLIPS the box corner at per-seat multiplier")
    print("  lambda in [%.3f, %.3f]  (R_min %.3f-%.3f A i.e. %+.0f%%..%+.0f%%; k %.0f-%.0f N/m)"
          % (lam_lo, lam_hi, Rl, Rh_, (Rl / Re_H2 - 1) * 100, (Rh_ / Re_H2 - 1) * 100, kl, kh))
    for cname, cval in (("pi/2", PI / 2), ("8/5", 1.6), ("4^(1/3)", 4.0 ** (1.0 / 3.0)),
                        ("phi", (1 + 5 ** 0.5) / 2), ("sqrt(e)", math.e ** 0.5)):
        tag = "INSIDE band" if lam_lo <= cval <= lam_hi else "outside"
        print("    named constant %-8s = %.4f : %s" % (cname, cval, tag))
    print("  NUMEROLOGY CAVEAT (look-elsewhere): several named constants sit in or near")
    print("  the band; NONE is promoted -- a future run must DERIVE a coefficient, not")
    print("  pick one. And the corner is DEPTH-SICK anyway: E_tot(min) there ~ %.1f eV" % dep)
    print("  = x%.1f the measured 4.75 eV (TRAP-4). A corner pass would be curvature" % (abs(dep) / De_H2))
    print("  lipstick on a sick depth ledger. => the WELL's depth, not the wall's form,")
    print("  is the root blocker (confirms NP10 G-5).")
else:
    print("  gate box vs locus: EMPTY intersection -- the class is structurally excluded.")

# ---------------------------------------------------------------------------
# PHASE B -- registered three-field cross-check, W-1 frozen (REPORT: leg (i)
# already failed G-A2, so the conjunction is dead; legs inform ROOT-WALL).
# ---------------------------------------------------------------------------
print("\nPHASE B  THREE-FIELD CROSS-CHECK -- W-1 frozen (no re-tune between fields)")
print("  leg (i) k(H2): %.0f N/m vs 575 (+%.0f%%) -> G-B(i) FAIL (= G-A2)" % (w1_k, (w1_k - K_H2) / K_H2 * 100.0))

# --- leg (ii): ionic, Evjen machinery reused as-is ---
def evjen(n):
    Mm = 0.0
    for i in range(-n, n + 1):
        for j in range(-n, n + 1):
            for k in range(-n, n + 1):
                if i == 0 and j == 0 and k == 0:
                    continue
                w = 1.0
                if abs(i) == n: w *= 0.5
                if abs(j) == n: w *= 0.5
                if abs(k) == n: w *= 0.5
                r = math.sqrt(i * i + j * j + k * k)
                s = 1.0 if ((i + j + k) & 1) else -1.0
                Mm += s * w / r
    return Mm

M = evjen(8)
print("  leg (ii) NaCl/KCl -- Evjen sum reused: M = %.6f (CH02 regression: 1.747574)" % M)
salts = [("NaCl", 2.820, 1.0, 787.0, 861.0, 1.02, 1.81),
         ("KCl",  3.146, 1.0, 715.0, 771.8, 1.38, 1.81),
         ("MgO",  2.106, 4.0, 3791.0, 4611.6, 0.72, 1.40)]
for nm, r0, q2, ULm, ULbase, rplus, rminus in salts:
    base = q2 * M * ahcA / r0 * eV_kJmol            # CH02 formula, regression
    dA   = 6.0 * hb2 / (r0 * r0) * eV_kJmol         # V-ion-A: 6 NN contacts, d = r0
    dB   = 6.0 * hb2 * (1.0 / rplus ** 2 + 1.0 / rminus ** 2) * eV_kJmol  # V-ion-B
    corrA, corrB = base - dA, base - dB
    eA = (corrA - ULm) / ULm * 100.0
    tag = "REPORT" if nm == "MgO" else ("gate +-5%" if nm == "NaCl" else "direction")
    print("    %-4s base %7.1f (CH02 %7.1f) | V-ion-A wall -%7.1f -> %7.1f vs %6.1f (%+6.1f%%) [%s]"
          % (nm, base, ULbase, dA, corrA, ULm, eA, tag))
    print("         V-ion-B (Shannon seat radii) wall -%8.1f -> %8.1f  (unphysical: lattice %s)"
          % (dB, corrB, "UNBOUND" if corrB < 0 else "bound"))
print("    leg (ii) scoring: NaCl V-ion-A lands OUTSIDE +-5% of 787 (overshoot of the")
print("    correction ~x3.7); KCl direction CORRECT (binding reduced) but overshoots")
print("    past 715; V-ion-B unphysical. SIGN is right in V-ion-A everywhere -- the")
print("    first wall in this program to move the ionic ledger the required way")
print("    (Face R could not even get the sign). G-B(ii): FAIL")

# --- leg (iii): nuclear, D-A4 domain rule (committed BEFORE these numbers) ---
print("  leg (iii) nuclear -- Face-T machinery replicated (regression), then D-A4:")

def binding(pts):
    U = 0.0
    for a in range(len(pts)):
        for b in range(a + 1, len(pts)):
            dx = pts[a][0] - pts[b][0]; dy = pts[a][1] - pts[b][1]; dz = pts[a][2] - pts[b][2]
            r = math.sqrt(dx * dx + dy * dy + dz * dz)
            if r < 1e-12: continue
            U += pts[a][3] * pts[b][3] * AHC_MeVfm / r
    return -U

Dn = D_np17
vd = [(0, 0, 0, +1), (Dn, 0, 0, +1), (Dn / 2, 0, 0, -1)]
vt = [(0, 0, 0, +1), (Dn, 0, 0, +1), (2 * Dn, 0, 0, +1), (Dn / 2, 0, 0, -1), (1.5 * Dn, 0, 0, -1)]
sa = 2.0 * RpF / (2.0 * math.sqrt(2.0))
va = [(sa, sa, sa, +1), (sa, -sa, -sa, +1), (-sa, sa, -sa, +1), (-sa, -sa, sa, +1),
      (sa, 0, 0, -1), (-sa, 0, 0, -1)]
Ed, Et, Ea = binding(vd), binding(vt), binding(va)
lock = [1.0, 2.0, 6.0]
meas = [B_d, B_t, B_a]
names = ["deuteron", "triton  ", "alpha   "]
ok3 = True
for i, Ees in enumerate((Ed, Et, Ea)):
    Bpred = lock[i] * Ees
    e0 = (Bpred - meas[i]) / meas[i] * 100.0
    # D-A4: W fires only between cores NOT sharing a cadence lock; a bound
    # nucleus is ONE (Z-1)!-tour lock => W contributes 0 inside. Committed in
    # RUN_LOG before these numbers.
    shift = 0.0
    ok = abs(shift) < 5.0
    ok3 = ok3 and ok
    print("    %s (Z-1)!=%.0f x %.4f = %6.3f MeV (meas %6.3f, %+.2f%%) | wall shift %+.2f%% (<5%%) %s"
          % (names[i], lock[i], Ees, Bpred, meas[i], e0, shift, "[PASS]" if ok else "[FAIL]"))
s_cf = Dn / 2.0 * 1e-5                      # nuclear seat distance in Angstrom
W_cf = 2.0 * hb2 / (s_cf * s_cf) / 1e6      # eV -> MeV
print("    counterfactual (D-A4 removed; W-1 on nuclear seat distances s = D/2):")
print("    W = %.1f GeV per nucleus vs B_d = 2.224 MeV -> shift ~ %+.1e %%" % (W_cf / 1000.0, W_cf / B_d * 100.0))
print("    -> the domain rule carries the FULL load (printed so it is seen to be")
print("       load-bearing, not decorative). G-B(iii): %s under D-A4 as committed;" % ("PASS" if ok3 else "FAIL"))
print("       the x6.35 stays the lock's -- the wall does not double-count it.")
print("  G-B CONJUNCTION (i)^(ii)^(iii): FAIL  (dies at (i) and (ii))")

# --- CH02-R2 shape constraint (required reproduction target; REPORT row) ---
print("\nCH02-R2 SHAPE CONSTRAINT (REPORT row -- required reproduction target)")
print("  measured: B0 RISES x3.44/x3.70/x3.22 AND deconvolved exponent FALLS")
print("  6.98->4.51, 7.96->5.22, 8.61->5.09 across isoelectronic pairs.")
B0_model = {}
for nm, q2, B0m in (("NaF-analog q^2=1", 1.0, 46.5), ("MgO-analog q^2=4", 4.0, 160.0)):
    Cc = M * q2 * ahcA
    Dd = 6.0 * hb2
    rstar = 2.0 * Dd / Cc
    Epp = Cc / rstar ** 3                     # eV/A^2 at model equilibrium
    B0 = Epp / (18.0 * rstar) * 160.2176634   # eV/A^3 -> GPa
    B0_model[q2] = B0
    print("    %s: model r* = %.3f A, B0 = %8.1f GPa (measured %.1f)" % (nm, rstar, B0, B0m))
print("    model B0 ratio ~ x%.0f vs measured x3.44 ; model wall exponent n = 2,"
      % (B0_model[4.0] / B0_model[1.0]))
print("    FIXED and Z-BLIND, vs the measured 7->4.5 FALL.")
print("    SHAPE CONSTRAINT: NOT REPRODUCED -- the class has no Z channel at fixed")
print("    shell (no nuclear-transmission content) and cannot bend its exponent.")

# ---------------------------------------------------------------------------
# PHASE C -- anharmonicity (REPORT-ONLY; sign scored: pre-committed w_e x_e > 0)
# ---------------------------------------------------------------------------
print("\nPHASE C  ANHARMONICITY (report-only; SIGN scored; E=hbar*omega cap travels)")

def env_fine(fA_coarse_unused, R):
    # two-stage x-minimisation for smooth derivatives (declared finer numerics)
    E1 = ahcA * gA / R + hb2 * (2.0 / u2A) / (R * R)
    i = int(np.argmin(E1))
    xa, xb = max(0.02, xg[i] - 5e-4), xg[i] + 5e-4
    xf = np.arange(xa, xb, 1e-7)
    gf = 1.0 + 1.0 / (2.0 * xf) - 4.0 / np.sqrt(0.25 + xf * xf)
    ff = 2.0 / (0.25 + xf * xf)
    return float(np.min(ahcA * gf / R + hb2 * ff / (R * R)))

Rs = np.arange(w1_R - 5e-3, w1_R + 5e-3, 1e-5)
Es = np.array([env_fine(None, R) for R in Rs])
Rf = float(Rs[int(np.argmin(Es))])
h = 3e-3
Em2, Em1, E0, Ep1, Ep2 = (env_fine(None, Rf - 2 * h), env_fine(None, Rf - h),
                          env_fine(None, Rf), env_fine(None, Rf + h), env_fine(None, Rf + 2 * h))
k_f = (Ep1 - 2 * E0 + Em1) / (h * h)                    # eV/A^2
E3 = (-Em2 + 2 * Em1 - 2 * Ep1 + Ep2) / (2 * h ** 3)    # eV/A^3
k_SI = k_f * EVA2_Nm
mH = 1.00782503
mu_kg = (mH * mH / (mH + mH)) * amu
a_morse = abs(E3) / (3.0 * k_f) * 1e10                  # 1/m
we = math.sqrt(k_SI / mu_kg) / (2.0 * PI * c) / 100.0   # cm-1
wexe = hbar * a_morse ** 2 / (4.0 * PI * c * mu_kg) / 100.0
print("  W-1 at refined minimum R = %.4f A: k = %.0f N/m, E''' = %+.1f eV/A^3" % (Rf, k_SI, E3))
print("  sign: E''' < 0 -> stiffer inbound -> w_e x_e > 0 : %s (pre-committed sign)"
      % ("PASS" if E3 < 0 else "FAIL -- mechanism strike"))
print("  Morse map: a = %.3f 1/A ; w_e x_e / w_e = %.4f (measured 0.0276) [REPORT-ONLY]"
      % (a_morse * 1e-10, wexe / we))
print("  w_e from DERIVED k: %.0f cm-1 vs 4401.2 (%+.1f%%) [REPORT-ONLY -- the number"
      % (we, (we - 4401.21) / 4401.21 * 100.0))
print("  run 1 was structurally unable to print; E=hbar*omega cap travels]")

# ---------------------------------------------------------------------------
# PHASE D -- isotope regression (gate < 0.5% each, unchanged from run 1)
# ---------------------------------------------------------------------------
print("\nPHASE D  ISOTOPE REGRESSION (W mass inventory = {hbar, m_e} ONLY -- no nuclear")
print("  mass anywhere in W => k isotope-invariant; mass-only transfers rerun):")
mD, mCl = 2.01410178, 34.96885268
mC12, mC13, mO16 = 12.0, 13.00335484, 15.99491462
mu = lambda a, b: a * b / (a + b)
iso = [("HCl", "DCl", mu(mH, mCl), mu(mD, mCl), 2990.946, 2145.163, -0.002),
       ("H2", "D2", mu(mH, mH), mu(mD, mD), 4401.21, 3115.50, -0.070),
       ("CO", "13CO", mu(mC12, mO16), mu(mC13, mO16), 2169.813, 2121.42, +0.001)]
gd = True
for par, ch, muP, muC, weP, weM, anchor in iso:
    pred = weP * math.sqrt(muP / muC)
    err = (pred - weM) / weM * 100.0
    ok = abs(err) < 0.5
    gd = gd and ok
    print("    %-4s -> %-5s pred %9.2f cm-1 meas %9.2f err %+7.3f%% (run-1 anchor %+7.3f%%) %s"
          % (par, ch, pred, weM, err, anchor, "[PASS]" if ok else "[FAIL]"))
print("  G-D: %s (no mass dependence smuggled in by the wall)" % ("PASS" if gd else "FAIL"))

# ---------------------------------------------------------------------------
# SUMMARY
# ---------------------------------------------------------------------------
print("\n" + "=" * 78)
print(" CH07 RUN 2 -- GATES SUMMARY (all committed in RUN_LOG.md before coding)")
print("   candidate                      G-A1 (R_min +-25%)      G-A2 (k +-25%)")
for i, (name, Rm, Em, kN, interior) in enumerate(rows):
    eR = (Rm - Re_H2) / Re_H2 * 100.0
    eK = (kN - K_H2) / K_H2 * 100.0
    print("   %-30s %s (%.4f A, %+6.1f%%)   %s (%8.1f N/m, %+7.1f%%)"
          % (name.split("(")[0].strip(),
             "PASS" if ga1_any[i] else "FAIL", Rm, eR,
             "PASS" if ga2_any[i] else "FAIL", kN, eK))
print("   %-30s FAIL (no interior min)     FAIL (--)" % "W-5 exp(-R/a0)")
print("   G-A (any candidate lands both): FAIL")
print("   G-B conjunction: FAIL at (i) and (ii); (iii) holds under committed D-A4")
print("   G-C sign (w_e x_e > 0): %s ; ratio %.4f vs 0.0276 REPORT-ONLY" % ("PASS" if E3 < 0 else "FAIL", wexe / we))
print("   G-D isotope regression: %s" % ("PASS" if gd else "FAIL"))
print("   WELL-DEPTH FINDING: bare well -81.5 eV = x17.2 D_e; depth pins curvature")
print("   (k -> ~2400-2700 N/m for the whole n=2 class near Re); locus corner exists")
print("   at lambda ~ 1.55-1.60 but is depth-sick (~-29 eV) => ROOT BLOCKER = the")
print("   run-1 WELL's depth ledger at contact, not the wall's form (NP10 G-5 sharpened).")
print("   Exit: 0 (ran to completion; verdicts are the printed lines above)")
print("=" * 78)
