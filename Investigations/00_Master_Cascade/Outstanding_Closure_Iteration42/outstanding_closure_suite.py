#!/usr/bin/env python3
"""
Outstanding-closure suite (Iteration 42).
Adjudicate every remaining OPEN / FAILED row from OUTSTANDING ledger.
Statuses: EXCLUDED | CONDITIONAL | IDENTITY | PARKED_PERMANENT | PARKED_DATA | UNDERDETERMINED
ASCII-only stdout for Windows consoles.
"""
from __future__ import annotations

import math
import os
import sys
from pathlib import Path

C = 299792458.0
HBAR = 1.054571817e-34
G = 6.67430e-11
M_E = 9.1093837015e-31
M_P = 1.67262192369e-27
ALPHA = 7.2973525693e-3
A0 = 5.29177210903e-11
R_E = 2.8179403262e-15
L_P = 1.616255e-35

ROOT = Path(__file__).resolve().parents[3]


def rel(a, b):
    return abs(a - b) / abs(b) if b else float("inf")


def section(title: str):
    print(f"\n=== {title} ===")


def main() -> int:
    print("OUTSTANDING CLOSURE SUITE — Iteration 42")
    print("pre-reg: OUTSTANDING_CLOSURE_PRE_REGISTRATION.md")
    results = {}

    # ------------------------------------------------------------------
    # CLM-14 Jovian heat (broken script pattern)
    # ------------------------------------------------------------------
    section("CLM-14 Jovian heat")
    # Naive broken patterns seen in corrected-proofs notes:
    #  (a) energy mistaken for power; (b) fitted eta; (c) wrong Phi units
    R_j = 6.9911e7
    v_j = 42000.0  # order surface/escape scale placeholder for broken script
    om_j = v_j * v_j * R_j / (C * C)
    # Wrong: treat om*c^3 or similar as watts without area/time
    bogus_W = om_j * C * C * C  # joules * m/s — not watts
    target_W = 3.5e17  # order of Jupiter internal heat (W)
    print(f"  bogus scalar ~ {bogus_W:.3e} (not watts); target ~ {target_W:.3e} W")
    print(f"  ratio bogus/target = {bogus_W/target_W:.3e}")
    # Fitted eta would be required to force match — EXCLUDE as method
    eta_needed = target_W / bogus_W if bogus_W else float("inf")
    print(f"  eta needed to force match = {eta_needed:.3e} (fitted knob)")
    results["CLM-14"] = "EXCLUDED"
    print("  STATUS EXCLUDED (units + would-be fitted eta)")

    # ------------------------------------------------------------------
    # CLM-24 electron g-2 as SDT derivation
    # ------------------------------------------------------------------
    section("CLM-24 electron g-2")
    # Schwinger term alpha/pi is QED; SDT importing it is circular as derivation
    a_schwinger = ALPHA / math.pi
    a_codata = 1.15965218046e-3  # CODATA ae approx
    print(f"  Schwinger alpha/pi = {a_schwinger:.10e}")
    print(f"  CODATA a_e ~ {a_codata:.10e}")
    print(f"  rel first-order = {rel(a_schwinger, a_codata):.3e}")
    print("  higher QED coeffs are IMPORTED — not SDT-derived")
    results["CLM-24"] = "EXCLUDED_CIRCULAR"
    print("  STATUS EXCLUDED as SDT derivation (IDENTITY/import of QED series)")

    # ------------------------------------------------------------------
    # MM03 accept permanent park + public-claim ban
    # ------------------------------------------------------------------
    section("MM03 koppa origin")
    k0 = L_P * L_P * C * M_P / HBAR
    print(f"  koppa_per_baryon = {k0:.6e} m  (engine IDENTITY with l_P risk)")
    results["MM03"] = "PARKED_PERMANENT"
    print("  STATUS PARKED_PERMANENT — public claims must disclose l_P<->G risk")
    print("  BAN: 'koppa derived from Law III occlusion' without new lattice proof")

    # ------------------------------------------------------------------
    # AS02 native action A_s screen
    # ------------------------------------------------------------------
    section("AS02 native A_s")
    # Candidates that avoid importing hbar explicitly but recover hbar
    # from (a0, alpha, m_e, c) — that is STILL shared-input Bohr closure
    A_bohr = M_E * C * A0 * ALPHA  # = hbar because a0 = hbar/(m_e c alpha)
    print(f"  A_bohr = m_e*c*a0*alpha = {A_bohr:.10e}")
    print(f"  hbar                  = {HBAR:.10e}")
    print(f"  match: {'PASS' if rel(A_bohr, HBAR) < 1e-6 else 'FAIL'} (IDENTITY via Bohr)")
    # Without m_e: cannot form J*s from (a0, alpha, c) alone dimensionally
    # [a0]=L, [c]=L/T, [alpha]=1 -> no M -> no action
    print("  delete-test m_e: no action dimension from (a0,alpha,c) alone")
    results["AS02"] = "PARKED_PERMANENT"
    print("  STATUS PARKED_PERMANENT — A_s=hbar is Bohr IDENTITY; native A_s underived")
    print("  BAN: claiming A_s derived independent of mass/hbar anchor")

    # ------------------------------------------------------------------
    # CR01 Cherenkov constitutive n(omega)
    # ------------------------------------------------------------------
    section("CR01 Cherenkov n(omega)")
    n_water = 1.333
    theta = math.degrees(math.acos(1.0 / n_water))
    print(f"  threshold angle from OBSERVED n_water: {theta:.2f} deg (B32 COMPUTED)")
    print("  constitutive n(omega) from relay law: no closed formula in engine")
    # Frank-Tamm spectral yield uses mu,c,e,z,v,n — imports EM constants
    print("  Frank-Tamm yield: IMPORTED EM formula if used as SDT derivation")
    results["CR01"] = "UNDERDETERMINED"
    print("  STATUS UNDERDETERMINED — cone with observed n CONDITIONAL;")
    print("  constitutive dispersion + Frank-Tamm norm not SDT-derived")

    # ------------------------------------------------------------------
    # NU01 SNO-shaped neutrino conversion
    # ------------------------------------------------------------------
    section("NU01 SNO neutrino")
    # Scalar disappearance model (broken): survival ~ 1/3 hard-coded
    p_survive_broken = 1.0 / 3.0
    print(f"  broken scalar survival hard-code = {p_survive_broken}")
    print("  SNO measured NC/CC flavor appearance — not mere disappearance")
    print("  conserved ||q|| conversion: no executable SDT state machine in tree")
    results["NU01"] = "EXCLUDED_MODEL__MECH_UNDERDETERMINED"
    print("  STATUS scalar-loss EXCLUDED; conversion mechanism UNDERDETERMINED")

    # ------------------------------------------------------------------
    # NSEQ13 occupation / emission energy proxy
    # ------------------------------------------------------------------
    section("NSEQ13 occupation energy")
    # Geometric-only proxy: Shared contacts vs private matching count
    # Cannot produce MeV without an energy quantum — delete-test
    shared, priv = 4, 2
    print(f"  Shared={shared} private_matching={priv} (NSEQ11 counts)")
    print("  no MeV map without A_s or occlusion energy scale")
    print("  NSEQ09: gap heights OBSERVED not predicted")
    results["NSEQ13"] = "UNDERDETERMINED"
    print("  STATUS UNDERDETERMINED — seating rule exists; energy map absent")

    # ------------------------------------------------------------------
    # GW01 chirp detox
    # ------------------------------------------------------------------
    section("GW01 chirp without GR M_c")
    koppa_sun = G * 1.98847e30 / (C * C)  # uses G — known-match path
    # Prefer GM measured: 
    GM_sun = 1.32712440018e20
    koppa_sun = GM_sun / (C * C)
    koppa_tot = 65.0 * koppa_sun
    f_isco = C / (math.pi * 6.0 * math.sqrt(6.0) * koppa_tot)
    print(f"  f_GW,isco from length = {f_isco:.2f} Hz (target ~68)")
    print("  CLASS: ALGEBRAIC IDENTITY of koppa bridge + GR ISCO form (disclosed)")
    print("  radiation coeff 96/5: CONVERGENCE-PENDING / UNDERDETERMINED in SDT")
    results["GW01"] = "IDENTITY_DISCLOSED__RAD_COEFF_UNDERDETERMINED"
    print("  STATUS identity disclosed; full GW law without GR coeff UNDERDETERMINED")

    # ------------------------------------------------------------------
    # OM02 Cassini / published delay marker under shared om
    # ------------------------------------------------------------------
    section("OM02 Cassini shared-om delay")
    cassini = ROOT / "Datasets" / "solar_propagation_2026-08"
    status_f = cassini / "FETCH_STATUS_DISK_FULL_2026-08-09.md"
    nfiles = 0
    nbytes = 0
    has_odf = False
    if cassini.exists():
        for p in cassini.rglob("*"):
            if p.is_file():
                nfiles += 1
                try:
                    nbytes += p.stat().st_size
                except OSError:
                    pass
                if p.suffix.lower() in {".odf", ".tdf"}:
                    has_odf = True
    print(f"  dataset path exists: {cassini.exists()}")
    print(f"  files={nfiles} bytes={nbytes} has_odf/tdf={has_odf}")
    print(f"  disk-full note present: {status_f.exists()}")

    # Shared-om analytic two-way logarithmic marker (OM01), limb impact
    R_SUN = 6.957e8
    V_SURF = 436762.0
    AU = 1.495978707e11
    om = V_SURF * V_SURF * R_SUN / (C * C)
    b = R_SUN
    dt = (2.0 / C) * 2.0 * om * math.log(4.0 * AU * AU / (b * b))
    # Published Cassini SCE order ~1e-4 s (Bertotti et al. 2003 gamma test)
    published_order = 1e-4
    print(f"  shared-om delay marker = {dt:.6e} s")
    print(f"  published Cassini order ~ {published_order:.1e} s")
    print(f"  order agreement (factor): {dt/published_order:.2f}")

    if has_odf and nbytes > 100_000:
        results["OM02"] = "PARKED_PARTIAL_FETCH__ORDER_CONDITIONAL"
        print("  STATUS PARKED_PARTIAL_FETCH — literature order CONDITIONAL;")
        print("  EMPIRICALLY SURVIVES path-integral WITHDRAWN until full decode")
    elif status_f.exists() or nfiles < 5:
        results["OM02"] = "PARKED_DATA_INCOMPLETE"
        print("  STATUS PARKED_DATA_INCOMPLETE")
    else:
        results["OM02"] = "PARKED_DATA_UNAVAILABLE"
        print("  STATUS PARKED_DATA_UNAVAILABLE")

    # ------------------------------------------------------------------
    # Summary
    # ------------------------------------------------------------------
    section("SUMMARY")
    openish = 0
    for k, v in results.items():
        print(f"  {k}: {v}")
        if "UNDERDETERMINED" in v or v.endswith("OPEN"):
            openish += 1
    print("---")
    print("All outstanding rows adjudicated (no unlabeled OPEN).")
    print(f"Underdetermined/parked mechanism count = {openish}")
    print("STATUS OUTSTANDING_CLOSURE_COMPLETE")
    return 0


if __name__ == "__main__":
    sys.exit(main())
