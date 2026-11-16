#!/usr/bin/env python3
"""He / He-like leftover after subtracting H / H-like Keplerian seats.

H-like well at Z, n=1 is the body:
  R = a0/Z,  k = 1/(Z α),  v = (c/k) √(R/r) = Z α c at r=R.
He-like IE is the two-electron leftover. k and R stay those of the H-like ion.
"""
from __future__ import annotations

import csv
import json
import math
from pathlib import Path

C = 299_792_458.0
ALPHA = 7.297_352_5693e-3
A0 = 5.291_772_109_03e-11
M_E = 9.109_383_7015e-31
E_CHARGE = 1.602_176_634e-19
RY_EV = 13.605_693_122_994
ME_C2 = M_E * C * C / E_CHARGE

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
IE = json.loads((ROOT / "Datasets/nuclear/ionisation_energies.json").read_text(encoding="utf-8"))

SYMBOL = {
    1: "H", 2: "He", 3: "Li", 4: "Be", 5: "B", 6: "C", 7: "N", 8: "O", 9: "F",
    10: "Ne", 11: "Na", 12: "Mg", 13: "Al", 14: "Si", 15: "P", 16: "S", 17: "Cl",
    18: "Ar", 19: "K", 20: "Ca", 26: "Fe",
}


def z_from_ie(e_ev: float) -> float:
    return 2.0 * e_ev / ME_C2


def main() -> None:
    z_H = ALPHA * ALPHA
    v_H = ALPHA * C
    k_H = 1.0 / ALPHA
    e_H = RY_EV
    print("H n=1 seat (subtract this family first)")
    print(f"  z_H={z_H:.6e}  k_H={k_H:.4f}  v_H/c={ALPHA:.6e}  E={e_H:.6f} eV  R=a0")
    print()
    print("He-like leftover. H-like well frozen: R=a0/Z, k=1/(Zα), v=(c/k)√(R/r)")
    print(f"{'Z':>3} {'ion':<8} {'E_Hlike':>10} {'E_Helike':>10} {'ratio':>7} "
          f"{'z_Hlike':>10} {'z_He':>10} {'z_pair':>10} {'k_He/k_Hlike':>12} "
          f"{'r/R Kepler':>11} {'1-ratio':>8}")
    rows = []
    for Z in range(2, 31):
        seq = IE.get(str(Z), [])
        if len(seq) < Z or len(seq) < Z - 1:
            continue
        e_hlike = seq[Z - 1]   # last electron: H-like
        e_helike = seq[Z - 2]  # second-to-last: He-like
        if not e_hlike or not e_helike:
            continue
        z_hl = z_from_ie(e_hlike)
        z_he = z_from_ie(e_helike)
        z_pair = z_hl - z_he          # depth the companion occludes
        ratio = e_helike / e_hlike
        v_hl = C * math.sqrt(z_hl)
        v_he = C * math.sqrt(z_he)
        k_hl = 1.0 / (Z * ALPHA)     # H-like n=1
        k_he = C / v_he              # from measured He-like IE
        # Freeze H-like (k,R). Observed v_he ⇒ Kepler radius of the pair seat.
        # v = (c/k) √(R/r) = v_hl √(R/r)  ⇒  r/R = (v_hl/v_he)² = 1/ratio
        r_over_R = (v_hl / v_he) ** 2
        # Hydrogen subtracted in Z-units: He-like vs Z²×H
        e_h_scaled = e_H * Z * Z
        print(
            f"{Z:3d} {SYMBOL.get(Z,'?'):<2} {Z-2}+{'':<3} "
            f"{e_hlike:10.3f} {e_helike:10.3f} {ratio:7.4f} "
            f"{z_hl:10.3e} {z_he:10.3e} {z_pair:10.3e} "
            f"{k_he/k_hl:12.4f} {r_over_R:11.4f} {1-ratio:8.4f}"
        )
        rows.append({
            "Z": Z, "symbol": SYMBOL.get(Z, ""),
            "E_Hlike_eV": e_hlike, "E_Helike_eV": e_helike,
            "E_H_times_Z2": e_h_scaled,
            "ratio_He_over_Hlike": ratio,
            "z_Hlike": z_hl, "z_Helike": z_he, "z_pair": z_pair,
            "z_pair_over_z_Hlike": z_pair / z_hl,
            "k_Hlike": k_hl, "k_Helike": k_he, "k_ratio": k_he / k_hl,
            "r_over_R_kepler": r_over_R,
            "v_Helike_over_v_Hlike": v_he / v_hl,
        })

    out = HERE / "aps14_he_like_after_Hlike.csv"
    with out.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0].keys()))
        writer.writeheader()
        writer.writerows(rows)

    print()
    print("He I vs H I (neutral helium after subtracting hydrogen, not Z-scaled)")
    e_HeI = IE["2"][0]
    e_HeII = IE["2"][1]
    print(f"  H I  IE={e_H:.4f}  z={z_H:.6e}  k={k_H:.4f}")
    print(f"  He II (H-like Z=2) IE={e_HeII:.4f}  / (4 E_H) = {e_HeII/(4*e_H):.6f}")
    print(f"  He I  IE={e_HeI:.4f}  z={z_from_ie(e_HeI):.6e}  k={C/math.sqrt(2*e_HeI/ME_C2 * C*C):.4f}"
          if False else f"  He I  IE={e_HeI:.4f}")
    z_HeI = z_from_ie(e_HeI)
    v_HeI = C * math.sqrt(z_HeI)
    k_HeI = C / v_HeI
    print(f"  He I  z={z_HeI:.6e}  k={k_HeI:.4f}  v/c={v_HeI/C:.6e}")
    print(f"  leftover depth z_HeII - z_HeI = {z_from_ie(e_HeII)-z_HeI:.6e}  "
          f"({(z_from_ie(e_HeII)-z_HeI)/z_from_ie(e_HeII):.4f} of the H-like well)")
    print(f"  leftover vs hydrogen: z_HeI / z_H = {z_HeI/z_H:.4f}  "
          f"(not 4; companion killed most of the Z² climb)")
    print(f"  Kepler r/R at frozen He II (k,R): {(math.sqrt(z_from_ie(e_HeII))/math.sqrt(z_HeI))**2:.4f}")
    print()
    # Does z_pair / Z track a constant occlusion of one companion?
    print("z_pair / z_Hlike  should fall ~ 1/Z if one companion hides a fixed fraction of nuclear koppa:")
    for row in rows[:12]:
        print(f"  Z={row['Z']:2d}  z_pair/z_Hlike={row['z_pair_over_z_Hlike']:.4f}  "
              f"r/R={row['r_over_R_kepler']:.4f}  k_He/k_Hlike={row['k_ratio']:.4f}")
    print(f"wrote {out}")


if __name__ == "__main__":
    main()
