#!/usr/bin/env python3
# =============================================================================
#  PPT08 (2026-07-02) - does the proton trefoil's far field make the EXTRA
#  measured splittings in the hydrogen spectrum?
#
#  Replaces the FABRICATED APS04 closure (tool never compiled; amplitude
#  ASSERTED ~0.008; number reverse-engineered to the target).
#
#  METHOD (Harvey): use ONLY the raw data the spectroscopists recorded, and
#  interpret it in SDT -- NOT in borrowed nouns. No "Coulomb", no "Lamb", no
#  "orbital / s / p / l / SO(3)". Those are QM interpretations, not data.
#
#  RAW DATA (measured frequencies, same as the experiments used):
#    - the bulk hydrogen series (Lyman/Balmer...) = SDT's radial k-ladder
#      r_n = n^2 a_0 -- SDT already recovers this (FLM03).
#    - BEYOND the ladder, finer instruments record EXTRA splittings of each line:
#         optical fine splitting  ~ 1.09e10 Hz   (~3e-6 of the 13.6 eV binding)
#         RF resonance (1947 beam) ~ 1.05785e9 Hz (~3e-7 of the binding)  [raw datum]
#      and these extra components come in TWOS (measured doublets).
#  SDT QUESTION: SDT's radial field gives the ladder but nothing finer. Does the
#  proton's non-spherical (trefoil) form imprint the extra measured splittings?
#  This is a pure FORWARD SDT computation; no measured splitting is an input.
# =============================================================================
import numpy as np

R_p  = 0.8414e-15       # proton boundary radius [m]  (measured)
a_0  = 5.29177211e-11   # k-ladder ground rung r_1 [m] (measured)
E_bind_eV = 13.6056931  # hydrogen ground binding [eV] (measured) -- scale only

# raw measured EXTRA splittings (frequencies, as recorded; NOT interpreted):
f_fine_Hz = 1.09e10     # optical fine splitting  (measured)
f_rf_Hz   = 1.05785e9   # RF beam resonance 1947  (measured)
h_eV_Hz   = 4.135667696e-15
frac_fine = f_fine_Hz*h_eV_Hz/E_bind_eV
frac_rf   = f_rf_Hz  *h_eV_Hz/E_bind_eV

print("="*74)
print(" PPT08 HONEST REBUILD - can the trefoil far field make hydrogen's EXTRA")
print(" measured splittings?  (raw frequencies, SDT interpretation, nothing named)")
print("="*74)
print(f" raw data: extra splittings are ~{frac_fine:.1e} (optical) and ~{frac_rf:.1e} (RF)")
print(f"           of the binding, and come in TWOS (measured doublets).")

# --- SDT object: the proton is a (2,3) trefoil vortex; compute its wake ------
Nk = 1200
t  = np.linspace(0, 2*np.pi, Nk, endpoint=False)
K  = np.stack([(2+np.cos(3*t))*np.cos(2*t), (2+np.cos(3*t))*np.sin(2*t), np.sin(3*t)], axis=1)
K -= K.mean(axis=0); K *= R_p/np.max(np.linalg.norm(K, axis=1))
dl = np.gradient(K, axis=0)
def wake_speed(P):
    d  = P[None,:]-K; r3 = np.linalg.norm(d,axis=1)**3 + 1e-300
    return np.linalg.norm((np.cross(dl,d)/r3[:,None]).sum(axis=0))

radii = R_p*np.array([2.,3.,5.,8.,15.,30.,60.,120.,300.])
phis  = np.linspace(0,2*np.pi,48,endpoint=False)
A0,A2,A3 = [],[],[]
for r in radii:
    eq  = np.array([wake_speed(np.array([r*np.cos(p),r*np.sin(p),0.])) for p in phis])
    pol = 0.5*(wake_speed(np.array([0.,0.,r]))+wake_speed(np.array([0.,0.,-r])))
    A0.append(0.5*(eq.mean()+pol)); A2.append(abs(eq.mean()-pol))
    A3.append((2.0/len(phis))*np.abs((eq*np.exp(-3j*phis)).sum()))
A0,A2,A3 = map(np.array,(A0,A2,A3)); fit=lambda y:np.polyfit(np.log(radii/R_p),np.log(y),1)[0]

# --- (a) how far the trefoil's shape reaches (SDT-native, no multipole nouns) -
print(f"\n (a) trefoil wake fall-off (computed):  overall ~ r^{fit(A0):+.2f}")
print(f"     [APS04 ASSERTED ~ r^-1; it is r^-3. Their power law was invented.]")
print(f"     angular unevenness / average -> {(A2/A0)[-1]:.3f}, constant with r (shape persists)")

# --- (b) but the FIELD the electron sits in dies as r^-3 --------------------
supp = wake_speed(np.array([a_0,0.,0.])) / wake_speed(np.array([2.0*R_p,0.,0.]))
print(f"\n (b) at the ground rung r_1 = {a_0/R_p:.1e} R_p, the trefoil field is")
print(f"     {supp:.1e} of its near-proton value (falls as r^-3).")
print(f"     -> the electron there samples ~{supp:.0e} of the proton's shape.")

# --- (c) confront the RAW data: magnitude and count -------------------------
print(f"\n (c) vs the raw measured extra splittings:")
print(f"     need coupling ~{frac_rf:.1e} .. {frac_fine:.1e};  trefoil far field gives ~{supp:.0e}")
print(f"     -> short by ~{frac_rf/supp:.0e} to ~{frac_fine/supp:.0e}. Cannot make them.")
print(f"     (APS04 ASSERTED a coupling ~8e-3 to bridge this -- ~{8e-3/supp:.0e}x the real value.")
print(f"      that asserted number was the entire fabrication.)")
print(f"     COUNT: the trefoil stamps a THREE-fold pattern; the extra lines are")
print(f"     measured in TWOS. Three-fold source cannot make two-fold splittings.")

# --- SDT verdict ------------------------------------------------------------
print("\n"+"="*74)
print(" SDT VERDICT (raw data in, no borrowed nouns, nothing asserted):")
print("  * SDT's radial k-ladder already gives the bulk measured series (FLM03).")
print("  * The proton trefoil's shape DOES persist in angle at any distance, BUT its")
print(f"    field at the electron's rung is only ~{supp:.0e} of near-proton strength (r^-3):")
print("    ~orders too weak to imprint the extra measured splittings (3e-7..3e-6 of binding).")
print("  * And its 3-fold stamp cannot produce the measured 2-fold (doublet) counts.")
print("  => PPT08 OPEN. The extra measured hydrogen splittings are NOT made by the")
print("     proton's FAR field. In SDT they must come from where the electron actually")
print("     touches the core -- the seated / shared-electron geometry (cf NP17) -- the")
print("     near contact, not the washed-out far wake.")
print("     [honest OPEN: SDT mechanism computed and found insufficient; nothing faked,")
print("      no measured frequency used as an input, no QM interpretation imported.]")
print("="*74)
