"""
PPT02 — Guess-and-refine: can we DISCOVER koppa_H (k = 137) WITHOUT the fine-structure constant?
Author: J.C. Harvey, Melbourne.  SDT.

THE TEST. The electropause balance (EMC04) is:  occlusion push = circulation (centripetal),
with ground-state quantization  m_e v r = hbar.  That fixes the electron's radius and hence
    k = c/v ,   koppa = v^2 r / c^2 .
Normally v = alpha c is put in by hand. Here we REFUSE alpha and feed ONLY alpha-free inputs,
then guess-and-refine r to balance. If k -> 137.036 falls out, alpha is DERIVED. If not, the
gap tells us exactly what is missing.

DISCIPLINE — every input below is alpha-free:
    hbar, c, m_e, m_p              : measured, no alpha
    P_conv                         : Law I convergence pressure = Phi/l_P^3 (CMB + l_P; NO alpha)
    R_p   = 4 hbar/(m_p c)         : proton wake radius, W+1=4 topology (NO alpha)
    lam_e = hbar/(m_e c)           : electron REDUCED COMPTON length (NO alpha)
  *** We must NOT use r_e: r_e = alpha * lam_e, so r_e would smuggle alpha back in. ***
"""
import math
hbar = 1.054571817e-34
c    = 299792458.0
m_e  = 9.1093837015e-31
m_p  = 1.67262192369e-27
P_conv = 2.460822e48                      # Pa, engine Law I (alpha-free: Phi/l_P^3)
R_p   = 4.0 * hbar / (m_p * c)            # alpha-free proton wake radius
lam_e = hbar / (m_e * c)                  # alpha-free electron Compton length

# --- The occlusion coupling, built ALPHA-FREE from pure geometry + convergence pressure ---
#     F_occ(r) = (pi/4) P_conv R_p^2 lam_e^2 / r^2  ==  G_geo / r^2
G_geo = (math.pi / 4.0) * P_conv * R_p*R_p * lam_e*lam_e
print(f"alpha-free occlusion coupling  G_geo = (pi/4) P_conv R_p^2 lam_e^2 = {G_geo:.4e} N.m^2\n")

# --- GUESS AND REFINE the electropause radius r (bisection on the balance) ---
# balance: F_occ = G/r^2  ==  F_cen = m_e v^2/r = hbar^2/(m_e r^3)   (v = hbar/(m_e r)).
# overflow-safe ratio:  F_occ/F_cen = (G/r^2)/(hbar^2/(m_e r^3)) = G m_e r / hbar^2  (linear in r).
def ratio(r):                                   # >1 occlusion too strong, <1 too weak, =1 balance
    return G_geo * m_e * r / (hbar*hbar)
lo, hi = 1.0e-40, 1.0e-8                         # bracket the electropause radius
print("  iter        r (m)         F_occ/F_cen")
for it in range(1, 61):
    r = math.sqrt(lo*hi)                         # geometric-mean bisection
    rr = ratio(r)
    if it <= 6 or it % 10 == 0:
        print(f"  {it:4d}   {r:.6e}   {rr:.6e}")
    if rr > 1.0: hi = r
    else:        lo = r

r_eq = hbar*hbar / (m_e * G_geo)                # exact electropause fixed point
v_eq = hbar / (m_e * r_eq)
k_disc    = c / v_eq
koppa_disc = v_eq*v_eq*r_eq / (c*c)

print(f"\nDISCOVERED (alpha-free):")
print(f"  r_eq   = {r_eq:.4e} m       v_eq = {v_eq:.4e} m/s   (v/c = {v_eq/c:.4e})")
print(f"  k      = c/v   = {k_disc:.4e}")
print(f"  koppa  = v^2 r/c^2 = {koppa_disc:.4e} m")

# --- The measured target ---
alpha_meas = 7.2973525693e-3
k_target   = 1.0/alpha_meas                      # 137.036
r_e        = alpha_meas * lam_e                   # classical electron radius = koppa_H
print(f"\nMEASURED target:  k = 1/alpha = {k_target:.4f} ,  koppa_H = r_e = {r_e:.4e} m ,  v/c = alpha = {alpha_meas:.4e}")

print(f"\n--- THE GAP ---")
print(f"  k_discovered / k_target = {k_disc/k_target:.4e}     (want 1.0)")
print(f"  v_eq/c is {v_eq/c/alpha_meas:.3e} x too large -> v >> c, UNPHYSICAL.")
G_star = hbar*c*alpha_meas                        # the coupling that DOES give k=137
print(f"\n  Coupling that yields k=137 exactly:  G* = alpha hbar c = {G_star:.4e} N.m^2")
print(f"  G_geo / G* = {G_geo/G_star:.4e}   <- the alpha-free geometry OVERSHOOTS the coupling by this factor.")
print(f"  Required 'transparency' tau = G*/G_geo = {G_star/G_geo:.4e}  (NOT a clean 1/137; an alpha-laden hierarchy).")

print(f"\n=== BOTH-DIRECTIONS SOLID ANGLE (did the one-sided form miss something?) ===")
# Solid angle each body subtends at the other (small-angle): Omega = pi R^2 / r^2.
# TWO-SIDED occlusion: net force = P * Omega_p * Omega_e * r^2/(4 pi)  (momentum flux through
# the mutual cone, both shadows). Test whether this differs from the one-sided G_geo/r^2.
def F_two_sided(r):
    Omega_p = math.pi * R_p*R_p / (r*r)         # proton's angular size at electron
    Omega_e = math.pi * lam_e*lam_e / (r*r)     # electron's angular size at proton
    return P_conv * Omega_p * Omega_e * r*r / (4.0*math.pi)
r_test = 5.0e-11
print(f"  at r={r_test:.1e}:  F_two_sided   = {F_two_sided(r_test):.6e} N")
print(f"               G_geo/r^2 (1-sided) = {G_geo/(r_test*r_test):.6e} N")
print(f"  ratio = {F_two_sided(r_test)/(G_geo/(r_test*r_test)):.6f}  ->  IDENTICAL.")
print(f"  => F = P*Omega_p*Omega_e*r^2/(4pi) == (pi/4) P R_p^2 lam_e^2 / r^2.  The R1^2 R2^2/r^2")
print(f"     occlusion law ALREADY IS the two-sided solid-angle product. No direction was missed.")

print(f"\n=== WHERE THE 8.8e20 OVERSHOOT ACTUALLY LIVES (not a solid angle) ===")
alpha = alpha_meas
# engine effective pressure vs convergence pressure: the relay 'transparency'
P_eff = m_p*m_p*m_e*m_e*c**5 / (4.0*math.pi*alpha*hbar**3)
f_transfer = P_eff / P_conv
print(f"  factor A  pressure:  P_conv / P_eff = 1/f_transfer = {1.0/f_transfer:.3e}   (relay transparency)")
print(f"  factor B  e-radius:  (lam_e/r_e)^2 = 1/alpha^2     = {1.0/(alpha*alpha):.3e}   (r_e = alpha*lam_e)")
print(f"  A * B = {(1.0/f_transfer)*(1.0/(alpha*alpha)):.3e}   vs overshoot G_geo/G* = {G_geo/G_star:.3e}  -> MATCH.")

print(f"\nVERDICT:")
print(f"  The two-sided solid angle is ALREADY in the law (R1^2 R2^2/r^2 = P*Omega1*Omega2*r^2/4pi);")
print(f"  trying it explicitly gives the IDENTICAL number. The overshoot is not a missing direction -")
print(f"  it is two ALPHA-laden factors: the relay transparency (P_conv->P_eff) and the electron")
print(f"  occlusion radius (lam_e -> r_e = alpha*lam_e). Neither is geometry; both encode alpha.")
print(f"  => koppa_H still NOT discoverable alpha-free. alpha is the coupling, in the pressure and r_e.")
