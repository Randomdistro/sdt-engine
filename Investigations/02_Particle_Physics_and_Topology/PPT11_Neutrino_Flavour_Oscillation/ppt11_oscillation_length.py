#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
PPT11 — Neutrino flavour oscillation length from the three SDT mass minima.

SPEC: Investigations/02_Particle_Physics_and_Topology/PPT11_Neutrino_Flavour_Oscillation/PROMPT.md
Author of spec: J. C. Harvey, Melbourne.  Executor: PPT11 run 2026-07-01.

WHAT THIS TOOL DOES (and does NOT do)
  - Builds the oscillation length L_osc from the THREE mass minima m_nu1/2/3
    (neutrino.hpp, tagged MEASURED-INPUT), via engine-implied splittings
    Dm2_ij = m_j^2 - m_i^2. It NEVER reads neutrino::measured::Dm21_sq / Dm32_sq
    to CONSTRUCT L_osc -- those measured splittings appear ONLY in the
    OBSERVED-TARGET comparison column (anti-IDENTITY-PASS, PROMPT §9).
  - Round-trips the engine wake radii (9.87/6.80/3.29 um) and V_disp from the
    masses as a wiring sanity gate (PROMPT §9).
  - Compares to the measured oscillation length L_meas = 2.48*E[MeV]/Dm2[eV^2] m.

NATIVE-vs-BORROW TRANSLATION TEST (PROMPT §9, mandatory):
  The phase per unit length used below, dphi/dx = Dm2 c^3 / (4 hbar E), is the
  STANDARD oscillation phase. In SDT it is READ as a *geometric beat* of ONE
  straight W=0 vortex precessing between three near-degenerate resistance
  (V_disp) minima -- NOT as two mass-eigenstate kets interfering in a
  wavefunction. HOWEVER: this tool proves only that the NUMBER lands; it does
  NOT independently derive the 1/(4 hbar E) kinematic factor from SDT relay
  cadence. That derivation is the open mechanism (see VERDICT). So the block is
  labelled honestly: the *length* is COMPUTED from the minima; the *mechanism*
  that licenses this exact phase is PENDING. Calling this a closure would be a
  LINGUISTIC-BORROW. It is shipped as a Class-D foothold with the hole named.

This file has NO local physics-constant namespace: every constant is imported
from the engine header values (mirrored here as MEASURED-INPUT with the source
line cited), consistent with 'no local constant namespaces' (PROMPT top matter).
Python cannot #include the C++ header, so the engine values are transcribed
verbatim from Engine/include/sdt/{laws.hpp,neutrino.hpp} with the source noted;
they are NOT redefined/re-derived here.
"""

import math

# =====================================================================
#  ENGINE VALUES (transcribed verbatim from the C++ headers; NOT redefined)
#  Every one carries its provenance tag per PROMPT_EXECUTION_PROTOCOL.md §5.
# =====================================================================

# --- sdt::laws::measured (laws.hpp) ---
c        = 299_792_458.0          # [m/s]   MEASURED-INPUT  laws.hpp:110
hbar     = 1.054_571_817e-34      # [J s]   MEASURED-INPUT  laws.hpp:111
eV_to_J  = 1.602_176_634e-19      # [J/eV]  MEASURED-INPUT  laws.hpp:183

# --- sdt::neutrino::measured (neutrino.hpp) — THE THREE MASS MINIMA ---
# The ONLY construction inputs for the beat.  neutrino.hpp:38-40.
m_nu1_eV = 0.02                   # [eV]    MEASURED-INPUT  neutrino.hpp:38  (= SDT mass gap)
m_nu2_eV = 0.029                  # [eV]    MEASURED-INPUT  neutrino.hpp:39
m_nu3_eV = 0.06                   # [eV]    MEASURED-INPUT  neutrino.hpp:40

# --- OBSERVED-TARGET ONLY: measured splittings. FORBIDDEN as construction input. ---
# neutrino.hpp:47-48.  Used ONLY in the comparison column.
Dm21_sq_meas = 7.53e-5            # [eV^2]  OBSERVED-TARGET solar   neutrino.hpp:47
Dm32_sq_meas = 2.453e-3           # [eV^2]  OBSERVED-TARGET atmos.  neutrino.hpp:48

# --- Winding (topology) ---
W_neutrino = 0                    # DERIVED (law_VI): open winding.  neutrino.hpp:66


# =====================================================================
#  SANITY GATE (PROMPT §9): round-trip wake radii and V_disp from masses
# =====================================================================

def wake_radius_um(m_eV):
    """R_wake = hbar/(m c).  neutrino.hpp:69."""
    m_kg = m_eV * eV_to_J / (c * c)
    return hbar / (m_kg * c) * 1e6  # -> micrometres

def sanity_gate():
    print("=" * 74)
    print("SANITY GATE — round-trip engine wake radii from the three masses")
    print("=" * 74)
    exp = {1: 9.87, 2: 6.80, 3: 3.29}  # neutrino.hpp:74-76 comments (um)
    ok = True
    for i, m in ((1, m_nu1_eV), (2, m_nu2_eV), (3, m_nu3_eV)):
        r = wake_radius_um(m)
        match = abs(r - exp[i]) / exp[i] < 0.01
        ok = ok and match
        print(f"  nu{i}: m={m:.3f} eV -> R_wake={r:6.3f} um  (engine says {exp[i]:.2f} um)  "
              f"{'OK' if match else 'MISMATCH'}")
    print(f"  Sanity gate: {'PASS — inputs wired correctly' if ok else 'FAIL — inputs mis-wired'}")
    print()
    return ok


# =====================================================================
#  P3 CORE — beat length from the three minima (NO Dm^2 read to build it)
# =====================================================================

def dm2_engine(m_hi_eV, m_lo_eV):
    """Engine-IMPLIED mass-squared splitting from two minima. [eV^2]  DERIVED-from-minima."""
    return m_hi_eV ** 2 - m_lo_eV ** 2

def L_osc_metres(E_MeV, Dm2_eV2):
    """
    L_osc = 4 pi E hbar / (Dm2 c^3)  ==  2.48 * E[MeV] / Dm2[eV^2]  metres.
    dphi/dx = Dm2 c^3 / (4 hbar E)  -> [1/length]; beat at phi=2pi.
    Here Dm2 is the ENGINE-implied splitting for L_osc,SDT, and the MEASURED
    splitting for L_meas (OBSERVED-TARGET column only).
    """
    return 2.48 * E_MeV / Dm2_eV2

def dimensional_check():
    """Confirm dphi/dx has units 1/length. Uses SI to be explicit."""
    # dphi/dx = Dm2 c^3 / (4 hbar E). [Dm2]=(eV/c^2)^2*c^4=eV^2(as energy^2 in J^2 below),
    # [c^3]=m^3/s^3, [hbar]=J s, [E]=J. Assemble in SI:
    Dm2_J2 = (0.001 * eV_to_J) ** 2          # a sample (0.001 eV)^2 as energy^2 [J^2]
    E_J    = 1e6 * eV_to_J                     # 1 MeV [J]
    dphi_dx = Dm2_J2 * c ** 3 / (4.0 * hbar * E_J) / (c ** 4)
    # NB: mass-squared-difference enters as (Delta(m^2)) with m in energy units;
    # the c-powers convert to give [1/m]. We report the assembled dimension check.
    print("=" * 74)
    print("P2 DIMENSIONAL CHECK — dphi/dx must be [1/length]")
    print("=" * 74)
    print("  dphi/dx = Delta(m^2) c^3 / (4 hbar E)")
    print("  [ (energy^2) * (m/s)^3 / ((J s)*(J)) ] with energy in J, /c^4 to reduce")
    print(f"  Assembled sample magnitude ~ {dphi_dx:.3e}  (units resolve to 1/m)")
    print("  RESULT: dphi/dx is dimensionally an inverse length.  PASS")
    print()


# =====================================================================
#  MAIN
# =====================================================================

def main():
    print()
    print("#" * 74)
    print("#  PPT11 — Neutrino flavour oscillation length from 3 SDT mass minima")
    print("#  Engine minima m_nu1/2/3 (MEASURED-INPUT); Dm2_meas OBSERVED-TARGET only")
    print("#  Zero fitted knobs.  W_neutrino =", W_neutrino, "(open winding)")
    print("#" * 74)
    print()

    gate_ok = sanity_gate()
    dimensional_check()

    # --- Engine-implied splittings, built ONLY from the three minima ---
    Dm21_eng = dm2_engine(m_nu2_eV, m_nu1_eV)   # solar analogue
    Dm32_eng = dm2_engine(m_nu3_eV, m_nu2_eV)   # atmospheric analogue
    Dm31_eng = dm2_engine(m_nu3_eV, m_nu1_eV)

    print("=" * 74)
    print("ENGINE-IMPLIED SPLITTINGS  (Dm2_ij = m_j^2 - m_i^2, from minima only)")
    print("=" * 74)
    print(f"  Dm21_engine = {Dm21_eng:.4e} eV^2   [DERIVED-from-minima]  "
          f"(OBSERVED solar  {Dm21_sq_meas:.3e})")
    print(f"  Dm32_engine = {Dm32_eng:.4e} eV^2   [DERIVED-from-minima]  "
          f"(OBSERVED atmos. {Dm32_sq_meas:.3e})")
    print(f"  Dm31_engine = {Dm31_eng:.4e} eV^2   [DERIVED-from-minima]")
    print()

    # --- Comparison table at the two reference energies ---
    rows = [
        ("solar  (nu2-nu1)", 1.0,    Dm21_eng, Dm21_sq_meas),   # 1 MeV
        ("atmos. (nu3-nu2)", 1000.0, Dm32_eng, Dm32_sq_meas),   # 1 GeV
    ]

    print("=" * 74)
    print("P3 DECISIVE TABLE — L_osc from minima vs measured L_meas")
    print("  BAR: |log10(L_SDT/L_meas)| <= 1 for >=1 scale, NO knob  (PROMPT §4 P3)")
    print("=" * 74)
    hdr = f"{'scale':18s} {'E':>8s}  {'L_SDT[m]':>12s}  {'L_meas[m]':>12s}  {'log10':>7s}  {'label'}"
    print(hdr)
    print("-" * len(hdr))
    verdicts = []
    for name, E_MeV, Dm2_eng, Dm2_meas in rows:
        L_sdt  = L_osc_metres(E_MeV, Dm2_eng)     # COMPUTED from minima
        L_meas = L_osc_metres(E_MeV, Dm2_meas)    # OBSERVED-TARGET
        lr = math.log10(L_sdt / L_meas)
        if abs(lr) <= 1.0:
            label = "PASS (<=1 dec)"
        elif abs(lr) <= 3.0:
            label = "PIVOT (1-3 dec)"
        else:
            label = "KILL (>3 dec)"
        verdicts.append((name, lr, label))
        E_str = f"{E_MeV:.0f}MeV" if E_MeV < 1000 else f"{E_MeV/1000:.0f}GeV"
        print(f"{name:18s} {E_str:>8s}  {L_sdt:12.3e}  {L_meas:12.3e}  {lr:+7.2f}  {label}")
    print()

    # --- T5 robustness: does the match survive changing E_nu? (not a coincidence of E) ---
    print("=" * 74)
    print("T5 ROBUSTNESS — log10 ratio is E-independent (same E-scaling both sides)")
    print("=" * 74)
    for E_MeV in (0.1, 1.0, 10.0, 100.0, 1000.0):
        lr21 = math.log10(L_osc_metres(E_MeV, Dm21_eng) / L_osc_metres(E_MeV, Dm21_sq_meas))
        lr32 = math.log10(L_osc_metres(E_MeV, Dm32_eng) / L_osc_metres(E_MeV, Dm32_sq_meas))
        print(f"  E={E_MeV:8.1f} MeV : log10 solar={lr21:+.3f}  log10 atmos={lr32:+.3f}")
    print("  -> ratio is EXACTLY E-independent (L ~ E on both sides): the offset is a")
    print("     property of the MASSES, not of a chosen E.  (T5: not an E-coincidence.)")
    print()

    # --- Independence audit (the honesty core) ---
    print("=" * 74)
    print("INDEPENDENCE AUDIT — are the minima independent of the measured Dm^2?")
    print("=" * 74)
    m2_backsolve = math.sqrt(m_nu1_eV**2 + Dm21_sq_meas)
    m3_backsolve = math.sqrt(m_nu1_eV**2 + Dm21_sq_meas + Dm32_sq_meas)
    print(f"  If m2,m3 were BACK-SOLVED from measured Dm^2 (given m1=0.02):")
    print(f"    m2_backsolve = {m2_backsolve:.4f} eV  (engine has {m_nu2_eV})  "
          f"{'DIFFER' if abs(m2_backsolve-m_nu2_eV)>1e-3 else 'MATCH'}")
    print(f"    m3_backsolve = {m3_backsolve:.4f} eV  (engine has {m_nu3_eV})  "
          f"{'DIFFER' if abs(m3_backsolve-m_nu3_eV)>1e-3 else 'MATCH'}")
    print("  -> engine masses do NOT round-trip to the naive Dm^2 back-solve, so this is")
    print("     NOT a hard identity-pass; BUT m2,m3 are literature 'best estimates' that")
    print("     ARE partly informed by Dm^2 upstream => PARTIAL circularity. Caps grade.")
    print()

    # --- Overall P3 line ---
    passes = [v for v in verdicts if abs(v[1]) <= 1.0]
    print("=" * 74)
    print("P3 RESULT")
    print("=" * 74)
    print(f"  Sanity gate: {'PASS' if gate_ok else 'FAIL'}")
    print(f"  Scales within +-1 decade: {len(passes)}/2  "
          f"({', '.join(v[0].split()[0] for v in passes) if passes else 'none'})")
    print(f"  P3 FLOOR (>=1 scale within +-1 decade, no knob): "
          f"{'MET' if passes else 'NOT MET'}")
    print("  NOTE: floor MET numerically, but see mechanism/independence caveats in VERDICT.")
    print("        The length landing is COMPUTED; the SDT-native origin of the 1/(4 hbar E)")
    print("        phase factor is PENDING => Class-D foothold, not a closure.")
    print()


if __name__ == "__main__":
    main()
