#!/usr/bin/env python3
"""Run Iteration 44 reopen-condition instruments; concatenate stdout."""
from __future__ import annotations

import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
JOBS = [
    ROOT / "09_Particle_Physics_and_Topology/NU02_Ergodic_Three_Pitch_Appearance/nu02_ergodic_pitch.py",
    ROOT / "15_Optics_and_Photonics/CK02_Packing_Bulk_Index/ck02_packing_n.py",
    ROOT / "05_Nuclear_Physics/NSEQ14_LawIII_Contact_Energy/nseq14_contact_energy.py",
    ROOT / "06_Gravitation_and_Orbital_Mechanics/OM04_Cassini_RSR_Payload_Census/om04_rsr_census.py",
]


def main() -> int:
    print("ITERATION 44 reopen-condition batch")
    print("pre-reg: OUTSTANDING_CLOSURE_44_PRE_REGISTRATION.md")
    rc = 0
    for p in JOBS:
        print("\n" + "=" * 60)
        print(p.name)
        print("=" * 60)
        r = subprocess.run([sys.executable, str(p)], check=False)
        rc = rc or r.returncode
    return rc


if __name__ == "__main__":
    sys.exit(main())
