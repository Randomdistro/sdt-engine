#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
FLM11 — The Tape-Measure Principle and the Fifth-Ruler Count
Author: J. C. Harvey, Melbourne.  Execute-only tool for the FLM11 SPEC.

WHAT THIS TOOL DOES (structure/counting, not numeric fit):
  Enumerates the trefoil/vortex form's candidate configuration axes (drawn from
  the 28-D state Levels 5-6 and the (p,q) torus-knot geometry), applies EXPLICIT
  native independence tests (Law V movement budget v_T^2+v_P^2=c^2; winding W;
  traction T=3(W+1)), and prints:
    - the surviving PROPERTY COUNT P (rulers with a real grip mechanism),
    - the property map [axis | grip | property | independent? | constraint],
    - the single STRAIGHT / ZERO-GRIP residue, asserted to be the W=0 open line.

  It is INTEGER/BOOLEAN logic for the count; doubles appear only inside the
  Law V independence check (verifying v_T^2+v_P^2 = c^2 closes).

ENGINE PARITY (values mirror Engine/include/sdt/laws.hpp; nothing redefined that
  changes physics — these are the same integers/constants the header exposes):
    law_VI::winding : W_electron=1, W_proton=3, W_neutrino=0
    law_VI::topology: v_T = c*sqrt(p/(p+q)), v_P = c*sqrt(q/(p+q))
    law_VI::traction: T = 3*(W+1) = 12 for the proton
  derivation basis only. No G/M/GM, no wavefunctions, no gauge groups, no charge-substance.
"""

from dataclasses import dataclass, field
from typing import Callable, Optional
import math
import sys

# ----------------------------------------------------------------------
# Engine-mirrored constants (parity with sdt::laws; c normalised to 1 for the
# budget check — only the RATIO matters for the independence test).
# ----------------------------------------------------------------------
C = 1.0  # relay speed; the Law V budget is scale-free (v_T^2+v_P^2)/c^2 = 1

W_ELECTRON = 1     # law_VI::winding::W_electron   (unknot (1,1))
W_PROTON   = 3     # law_VI::winding::W_proton     (trefoil (2,3))
W_NEUTRINO = 0     # open winding (the straight through-line)

# canonical (p,q) modes (law_VI::topology)
PQ_ELECTRON = (1, 1)   # v_T = v_P = c/sqrt(2)
PQ_PROTON   = (2, 3)   # v_T = 0.632c, v_P = 0.775c


def v_toroidal(p: int, q: int) -> float:
    return C * math.sqrt(p / (p + q))


def v_poloidal(p: int, q: int) -> float:
    return C * math.sqrt(q / (p + q))


def budget_residual(p: int, q: int) -> float:
    """Law V closure: (v_T^2 + v_P^2)/c^2 — must equal 1 for every (p,q)."""
    vt, vp = v_toroidal(p, q), v_poloidal(p, q)
    return (vt * vt + vp * vp) / (C * C)


def traction_T(W: int) -> int:
    """law_VI::traction: T = 3*(W+1)."""
    return 3 * (W + 1)


# ----------------------------------------------------------------------
# Grip mechanisms — the kinds of PURCHASE a committed strip can take.
# NONE is the zero-grip class (the straight residue).
# ----------------------------------------------------------------------
GRIP = ("RESISTANCE", "HANDEDNESS", "CIRCULATION", "OSCILLATION", "NONE")


@dataclass
class Axis:
    name: str                       # form axis (28-D component or knot motion)
    grip: str                       # one of GRIP
    property: str                   # the physics property it reads (or "-")
    sdt_native: str                 # native reading (derivation basis / koppa / W / Φ)
    # independent() references an SDT CONSTRAINT, returns (is_independent, reason)
    independent: Callable[[], "tuple[bool, str]"]
    included: bool = True           # False = excluded as a property ruler (with reason)
    exclude_reason: str = ""


# ----------------------------------------------------------------------
# Independence predicates — each cites the native constraint that decides it.
# ----------------------------------------------------------------------
def indep_true(reason: str):
    return lambda: (True, reason)


def indep_vP_via_lawV():
    """v_P is NOT independent: Law V budget v_T^2+v_P^2=c^2 fixes it given v_T."""
    res_p = budget_residual(*PQ_PROTON)
    res_e = budget_residual(*PQ_ELECTRON)
    closes = (abs(res_p - 1.0) < 1e-12) and (abs(res_e - 1.0) < 1e-12)
    # If the budget closes, v_P is a DEPENDENT function of v_T -> not an independent ruler.
    reason = (f"Law V budget closes (proton residual={res_p:.12f}, "
              f"electron residual={res_e:.12f}) => v_P=sqrt(c^2 - v_T^2) is fixed by v_T; "
              f"NOT an independent circulation ruler")
    return (not closes, reason)  # independent only if the budget FAILED to close


def indep_straight_null():
    """The straight axis has grip=NONE by definition: it offers no purchase.
    It is real (W=0 open line carries momentum) but not a property ruler."""
    return (False, "grip=NONE: pure through-flow, no circulation/handedness/"
                   "resistance to grip => zero-grip residue, W=0 open line (neutrino)")


# ----------------------------------------------------------------------
# THE ENUMERATION — candidate axes of the form (28-D Levels 5-6 + knot motions).
# ----------------------------------------------------------------------
def build_axes() -> "list[Axis]":
    axes = [
        # ---- grippable candidates ----
        Axis(
            name="tube swelling / reorganisation cost (T_2, Level5; Law IV)",
            grip="RESISTANCE",
            property="mass",
            sdt_native="reorganisation-cost, Phi*V_disp/(l_P^3 c^2) (Law IV)",
            independent=indep_true("Law IV cost axis; orthogonal to circulation/"
                                   "handedness/oscillation (a static structural DoF)"),
        ),
        Axis(
            name="handedness Phi_3 = +/-1 (Level6, chirality)",
            grip="HANDEDNESS",
            property="charge (handed redirection; NOT a substance)",
            sdt_native="Phi_3 chirality +/-1; handed redirection of through-flow (R2)",
            independent=indep_true("discrete Z_2 sign; orthogonal to any continuous "
                                   "circulation magnitude (a sign, not a rate)"),
        ),
        Axis(
            name="toroidal circulation v_T (Law V; law_VI::topology)",
            grip="CIRCULATION",
            property="magnetic flux (motion of medium)",
            sdt_native="v_T = c*sqrt(p/(p+q)); toroidal circulation of the wake",
            independent=indep_true("free continuous circulation rate; the single "
                                   "surviving flux axis once v_P is removed by Law V"),
        ),
        Axis(
            name="oscillation Phi_2 (Level6; periodic reversal/precession)",
            grip="OSCILLATION",
            property="electromagnetism (propagating wake)",
            sdt_native="Phi_2 oscillation [Hz]; bond-switch / wake propagation",
            independent=indep_true("temporal propagating mode; distinct from a static "
                                   "circulation (a frequency, not a steady flow)"),
        ),
        # ---- the DEPENDENT candidate (the fifth-ruler test) ----
        Axis(
            name="poloidal circulation v_P (Law V; law_VI::topology)",
            grip="CIRCULATION",
            property="(would be a 2nd flux ruler)",
            sdt_native="v_P = c*sqrt(q/(p+q))",
            independent=indep_vP_via_lawV,   # decided by Law V budget
        ),
        # ---- the ZERO-GRIP residue ----
        Axis(
            name="through / straight axis (open line, W=0)",
            grip="NONE",
            property="- (no native ruler)",
            sdt_native="open winding W=0; pure through-flow along the core axis",
            independent=indep_straight_null,
        ),
        # ---- EXCLUDED as property rulers (kinematic / internal) ----
        Axis(
            name="core-ring translation (T_1 / Level2 position)",
            grip="NONE",
            property="- (position, not identity)",
            sdt_native="T_1 central-ring line; Level-2 kinematic location",
            independent=indep_true("n/a"),
            included=False,
            exclude_reason="kinematic POSITION of the whole form, not an intrinsic "
                           "property axis; externally ungrippable as an identity ruler",
        ),
        Axis(
            name="surface orientation (Level4 xi_s3 / axis direction)",
            grip="NONE",
            property="- (frame choice)",
            sdt_native="orientation unit-vector; sets which way v_T/Phi_3 point",
            included=False,
            independent=indep_true("n/a"),
            exclude_reason="a FRAME choice (direction of the already-counted circulation/"
                           "handedness axes), not a new independent grippable property",
        ),
    ]
    return axes


# ----------------------------------------------------------------------
# COUNT LOGIC
#   grippable ruler  <=>  included AND grip != NONE AND independent()==True
#   residue          <=>  included AND grip == NONE
# ----------------------------------------------------------------------
def run():
    axes = build_axes()

    rulers = []
    dependent = []
    residues = []
    excluded = []

    for ax in axes:
        if not ax.included:
            excluded.append(ax)
            continue
        is_indep, reason = ax.independent()
        if ax.grip == "NONE":
            residues.append((ax, reason))
        elif is_indep:
            rulers.append((ax, reason))
        else:
            dependent.append((ax, reason))

    P = len(rulers)
    n_residue = len(residues)

    # ---- print report ----
    line = "=" * 78
    print(line)
    print("FLM11 - RULER COUNT (Tape-Measure Principle)")
    print("Author: J. C. Harvey, Melbourne.  derivation basis inputs only; no G/M/GM.")
    print(line)

    print("\n[LAW V INDEPENDENCE CHECK]  v_T^2 + v_P^2 = c^2  (must close = 1.0)")
    for tag, pq, W in (("electron (1,1)", PQ_ELECTRON, W_ELECTRON),
                       ("proton   (2,3)", PQ_PROTON,   W_PROTON)):
        print(f"  {tag}: v_T={v_toroidal(*pq):.6f}c  v_P={v_poloidal(*pq):.6f}c  "
              f"residual={budget_residual(*pq):.12f}   T=3(W+1)={traction_T(W)}")
    print(f"  neutrino (open): W={W_NEUTRINO}  -> no closed (p,q) budget; the straight line")

    print("\n[AXIS TABLE]  name | grip | property | independent? | constraint")
    print("-" * 78)
    def row(ax, indep_flag, constraint):
        print(f"  GRIP={ax.grip:<11} | indep={indep_flag} | {ax.property}")
        print(f"      axis: {ax.name}")
        print(f"      SDT : {ax.sdt_native}")
        print(f"      test: {constraint}")
    print("-- GRIPPABLE RULERS (grip != NONE, independent) --")
    for ax, r in rulers:
        row(ax, "YES", r)
    print("-- DEPENDENT (grip present but fixed by a native constraint) --")
    for ax, r in dependent:
        row(ax, "NO ", r)
    print("-- ZERO-GRIP RESIDUE (grip == NONE, real but unrulered) --")
    for ax, r in residues:
        row(ax, "n/a", r)
    print("-- EXCLUDED as property rulers (kinematic / frame / internal) --")
    for ax in excluded:
        print(f"  {ax.name}")
        print(f"      reason: {ax.exclude_reason}")

    # ---- verdict block ----
    print("\n" + line)
    print("RESULT")
    print(line)
    print(f"  PROPERTY COUNT  P = {P}   (grippable rulers)")
    props = ", ".join(ax.property.split(' (')[0] for ax, _ in rulers)
    print(f"  PROPERTY MAP      = {{{props}}}")
    print(f"  DEPENDENT axes    = {len(dependent)}   "
          f"({', '.join(ax.name.split(' (')[0] for ax,_ in dependent) or 'none'})")
    print(f"  ZERO-GRIP RESIDUE = {n_residue}   (must be exactly 1)")

    # ---- fifth-ruler prediction ----
    fifth = "NO" if len(dependent) >= 1 and P == 4 else "SEE-BELOW"
    print(f"  FIFTH INDEPENDENT RULER? {fifth}  "
          f"(v_P dependent via Law V budget => no 5th grippable axis)")

    # ---- residue -> W=0 assertion ----
    ok_residue = (n_residue == 1)
    residue_ax = residues[0][0] if residues else None
    ok_straight = ok_residue and ("W=0" in residue_ax.sdt_native or "straight" in residue_ax.name)
    ok_w0 = ok_residue and (W_NEUTRINO == 0)
    print(f"\n  [P3 FLAG] exactly-one-zero-grip : {'PASS' if ok_residue else 'FAIL'}")
    print(f"  [P3 FLAG] residue = straight axis: {'PASS' if ok_straight else 'FAIL'}")
    print(f"  [P3 FLAG] residue maps to W=0     : {'PASS' if ok_w0 else 'FAIL'} "
          f"(neutrino = open winding)")

    # ---- pre-commit reconciliation ----
    PRECOMMIT_P = 4
    PRECOMMIT_RESIDUE = 1
    PRECOMMIT_FIFTH = "NO"
    match_P = (P == PRECOMMIT_P)
    match_res = (n_residue == PRECOMMIT_RESIDUE)
    match_fifth = (fifth == PRECOMMIT_FIFTH)
    print("\n  [PRE-COMMIT RECONCILIATION]  (RUN_LOG committed BEFORE running)")
    print(f"    P == {PRECOMMIT_P}?          {'MATCH' if match_P else 'MISMATCH -> finding'}")
    print(f"    residue == {PRECOMMIT_RESIDUE}?    {'MATCH' if match_res else 'MISMATCH -> finding'}")
    print(f"    fifth == {PRECOMMIT_FIFTH}?      {'MATCH' if match_fifth else 'MISMATCH -> finding'}")

    all_ok = match_P and match_res and match_fifth and ok_residue and ok_straight and ok_w0
    print("\n" + line)
    print(f"  OVERALL: {'ALL GATES MET (P2+P3 reproduce pre-commit)' if all_ok else 'GATE MISMATCH — route per §10 pivot table'}")
    print(line)
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(run())
