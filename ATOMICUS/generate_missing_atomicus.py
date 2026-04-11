#!/usr/bin/env python3
"""
Generate missing ATOMICUS element markdown files (Z=1..118) using a minimal,
consistent template.

Design goals:
- Do NOT overwrite existing element files.
- Avoid guessing isotope neutron counts in filenames (some existing files include N, others don't).
- Provide a stable filename scheme for new files: NNN_Element_Symbol_Z.md
- Generate/refresh an index: ATOMICUS_INDEX.md
- Generate/refresh a master table scaffold: SDT_Master_Geometric_Table.md (preserve existing content if desired)
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import re


@dataclass(frozen=True)
class Element:
    Z: int
    name: str
    symbol: str


ELEMENTS: dict[int, Element] = {
    1: Element(1, "Hydrogen", "H"),
    2: Element(2, "Helium", "He"),
    3: Element(3, "Lithium", "Li"),
    4: Element(4, "Beryllium", "Be"),
    5: Element(5, "Boron", "B"),
    6: Element(6, "Carbon", "C"),
    7: Element(7, "Nitrogen", "N"),
    8: Element(8, "Oxygen", "O"),
    9: Element(9, "Fluorine", "F"),
    10: Element(10, "Neon", "Ne"),
    11: Element(11, "Sodium", "Na"),
    12: Element(12, "Magnesium", "Mg"),
    13: Element(13, "Aluminum", "Al"),
    14: Element(14, "Silicon", "Si"),
    15: Element(15, "Phosphorus", "P"),
    16: Element(16, "Sulfur", "S"),
    17: Element(17, "Chlorine", "Cl"),
    18: Element(18, "Argon", "Ar"),
    19: Element(19, "Potassium", "K"),
    20: Element(20, "Calcium", "Ca"),
    21: Element(21, "Scandium", "Sc"),
    22: Element(22, "Titanium", "Ti"),
    23: Element(23, "Vanadium", "V"),
    24: Element(24, "Chromium", "Cr"),
    25: Element(25, "Manganese", "Mn"),
    26: Element(26, "Iron", "Fe"),
    27: Element(27, "Cobalt", "Co"),
    28: Element(28, "Nickel", "Ni"),
    29: Element(29, "Copper", "Cu"),
    30: Element(30, "Zinc", "Zn"),
    31: Element(31, "Gallium", "Ga"),
    32: Element(32, "Germanium", "Ge"),
    33: Element(33, "Arsenic", "As"),
    34: Element(34, "Selenium", "Se"),
    35: Element(35, "Bromine", "Br"),
    36: Element(36, "Krypton", "Kr"),
    37: Element(37, "Rubidium", "Rb"),
    38: Element(38, "Strontium", "Sr"),
    39: Element(39, "Yttrium", "Y"),
    40: Element(40, "Zirconium", "Zr"),
    41: Element(41, "Niobium", "Nb"),
    42: Element(42, "Molybdenum", "Mo"),
    43: Element(43, "Technetium", "Tc"),
    44: Element(44, "Ruthenium", "Ru"),
    45: Element(45, "Rhodium", "Rh"),
    46: Element(46, "Palladium", "Pd"),
    47: Element(47, "Silver", "Ag"),
    48: Element(48, "Cadmium", "Cd"),
    49: Element(49, "Indium", "In"),
    50: Element(50, "Tin", "Sn"),
    51: Element(51, "Antimony", "Sb"),
    52: Element(52, "Tellurium", "Te"),
    53: Element(53, "Iodine", "I"),
    54: Element(54, "Xenon", "Xe"),
    55: Element(55, "Cesium", "Cs"),
    56: Element(56, "Barium", "Ba"),
    57: Element(57, "Lanthanum", "La"),
    58: Element(58, "Cerium", "Ce"),
    59: Element(59, "Praseodymium", "Pr"),
    60: Element(60, "Neodymium", "Nd"),
    61: Element(61, "Promethium", "Pm"),
    62: Element(62, "Samarium", "Sm"),
    63: Element(63, "Europium", "Eu"),
    64: Element(64, "Gadolinium", "Gd"),
    65: Element(65, "Terbium", "Tb"),
    66: Element(66, "Dysprosium", "Dy"),
    67: Element(67, "Holmium", "Ho"),
    68: Element(68, "Erbium", "Er"),
    69: Element(69, "Thulium", "Tm"),
    70: Element(70, "Ytterbium", "Yb"),
    71: Element(71, "Lutetium", "Lu"),
    72: Element(72, "Hafnium", "Hf"),
    73: Element(73, "Tantalum", "Ta"),
    74: Element(74, "Tungsten", "W"),
    75: Element(75, "Rhenium", "Re"),
    76: Element(76, "Osmium", "Os"),
    77: Element(77, "Iridium", "Ir"),
    78: Element(78, "Platinum", "Pt"),
    79: Element(79, "Gold", "Au"),
    80: Element(80, "Mercury", "Hg"),
    81: Element(81, "Thallium", "Tl"),
    82: Element(82, "Lead", "Pb"),
    83: Element(83, "Bismuth", "Bi"),
    84: Element(84, "Polonium", "Po"),
    85: Element(85, "Astatine", "At"),
    86: Element(86, "Radon", "Rn"),
    87: Element(87, "Francium", "Fr"),
    88: Element(88, "Radium", "Ra"),
    89: Element(89, "Actinium", "Ac"),
    90: Element(90, "Thorium", "Th"),
    91: Element(91, "Protactinium", "Pa"),
    92: Element(92, "Uranium", "U"),
    93: Element(93, "Neptunium", "Np"),
    94: Element(94, "Plutonium", "Pu"),
    95: Element(95, "Americium", "Am"),
    96: Element(96, "Curium", "Cm"),
    97: Element(97, "Berkelium", "Bk"),
    98: Element(98, "Californium", "Cf"),
    99: Element(99, "Einsteinium", "Es"),
    100: Element(100, "Fermium", "Fm"),
    101: Element(101, "Mendelevium", "Md"),
    102: Element(102, "Nobelium", "No"),
    103: Element(103, "Lawrencium", "Lr"),
    104: Element(104, "Rutherfordium", "Rf"),
    105: Element(105, "Dubnium", "Db"),
    106: Element(106, "Seaborgium", "Sg"),
    107: Element(107, "Bohrium", "Bh"),
    108: Element(108, "Hassium", "Hs"),
    109: Element(109, "Meitnerium", "Mt"),
    110: Element(110, "Darmstadtium", "Ds"),
    111: Element(111, "Roentgenium", "Rg"),
    112: Element(112, "Copernicium", "Cn"),
    113: Element(113, "Nihonium", "Nh"),
    114: Element(114, "Flerovium", "Fl"),
    115: Element(115, "Moscovium", "Mc"),
    116: Element(116, "Livermorium", "Lv"),
    117: Element(117, "Tennessine", "Ts"),
    118: Element(118, "Oganesson", "Og"),
}


FILENAME_Z_RE = re.compile(r"^(?P<z>\d{3})_")


def existing_Zs(atomicus_dir: Path) -> set[int]:
    zs: set[int] = set()
    for p in atomicus_dir.glob("*.md"):
        m = FILENAME_Z_RE.match(p.name)
        if not m:
            continue
        try:
            z = int(m.group("z"))
        except ValueError:
            continue
        zs.add(z)
    return zs


def element_template(e: Element) -> str:
    # Keep template intentionally minimal and honest (no invented experimental values).
    return f"""# Chapter {e.Z}: On the Nature of {e.name} ({e.Z}{e.symbol})

**Status:** DRAFT (auto-generated scaffold)  
**SDT Classification:** TBD  
**Geometric Archetype:** TBD  

---

## Part I: Ionization Series (SDT Targets)

- **1st Ionization Energy (NIST reference):** TBD eV
- **SDT Predicted (E_i1):** TBD eV
- **Derived kinematics:** TBD (v, v/c, k)

> Notes:
> - Populate using SDT occlusion + packing rules.
> - Validate against NIST only for reporting, not computation.

---

## Part II: Nuclear Cross-Reference

- **Nucleus:** Z={e.Z}, N=TBD
- **Packing structure:** TBD (D/T decomposition, alpha bricks, etc.)
- **SDT nuclear-chemistry linkage:** TBD

---

## Part III: SDT Utilization & Applications

TBD (derive from geometric stress/serenity, magnetics, bonding tendencies).

---

## Provenance / Sources

- NIST ASD / NIST Chemistry WebBook (for validation): TBD
- SDT papers (mechanism derivations): TBD

"""


def write_missing_files(atomicus_dir: Path) -> list[Path]:
    zs_existing = existing_Zs(atomicus_dir)
    written: list[Path] = []

    for z in range(1, 119):
        if z not in ELEMENTS:
            continue
        if z in zs_existing:
            continue

        e = ELEMENTS[z]
        filename = f"{z:03d}_{e.name}_{e.symbol}_{e.Z}.md"
        path = atomicus_dir / filename
        if path.exists():
            continue
        path.write_text(element_template(e), encoding="utf-8")
        written.append(path)

    return written


def write_index(atomicus_dir: Path) -> None:
    # Build a Z -> file mapping by scanning filenames.
    entries: dict[int, list[Path]] = {}
    for p in atomicus_dir.glob("*.md"):
        m = FILENAME_Z_RE.match(p.name)
        if not m:
            continue
        z = int(m.group("z"))
        entries.setdefault(z, []).append(p)

    lines: list[str] = []
    lines.append("# ATOMICUS Index (Z=1–118)\n")
    lines.append("Auto-generated index of element chapters.\n")
    lines.append("| Z | Element | Symbol | Files |\n")
    lines.append("|:--|:--------|:-------|:------|\n")
    for z in range(1, 119):
        e = ELEMENTS.get(z)
        if not e:
            continue
        files = entries.get(z, [])
        if files:
            file_links = ", ".join(f"`{p.name}`" for p in sorted(files, key=lambda x: x.name))
        else:
            file_links = "_MISSING_"
        lines.append(f"| {z} | {e.name} | {e.symbol} | {file_links} |\n")

    (atomicus_dir / "ATOMICUS_INDEX.md").write_text("".join(lines), encoding="utf-8")


def parse_master_table(master_path: Path) -> dict[int, tuple[str, str, str]]:
    """
    Parse existing SDT_Master_Geometric_Table.md rows, returning:
      Z -> (ionization_eV, v_over_c, k_factor)
    Missing values are preserved as '-' strings.
    """
    if not master_path.exists():
        return {}
    text = master_path.read_text(encoding="utf-8", errors="replace")
    rows: dict[int, tuple[str, str, str]] = {}
    for line in text.splitlines():
        line = line.strip()
        if not (line.startswith("|") and line.endswith("|")):
            continue
        parts = [p.strip() for p in line.strip("|").split("|")]
        if len(parts) != 6:
            continue
        if parts[0] in {"Z", ":--"}:
            continue
        try:
            z = int(parts[0])
        except ValueError:
            continue
        ion_eV = parts[3]
        v_over_c = parts[4]
        k_factor = parts[5]
        rows[z] = (ion_eV, v_over_c, k_factor)
    return rows


def write_master_table(atomicus_dir: Path) -> None:
    master_path = atomicus_dir / "SDT_Master_Geometric_Table.md"
    existing = parse_master_table(master_path)

    out: list[str] = []
    out.append("# SDT Master Geometric Table\n\n")
    out.append(
        "A consolidated reference of the kinematic and geometric properties of the elements as derived from Spatial Displacement Theory.\n\n"
    )
    out.append("| Z | Element | Symbol | Ionization Energy (eV) | Velocity Ratio (v/c) | Geometric k-factor |\n")
    out.append("|:--|:--------|:-------|:-----------------------|:---------------------|:-------------------|\n")

    for z in range(1, 119):
        e = ELEMENTS.get(z)
        if not e:
            continue
        ion_eV, v_over_c, k_factor = existing.get(z, ("-", "-", "-"))
        out.append(f"| {z} | {e.name} | {e.symbol} | {ion_eV} | {v_over_c} | {k_factor} |\n")

    master_path.write_text("".join(out), encoding="utf-8")


def write_website_exports(repo_root: Path, atomicus_dir: Path) -> None:
    """
    Create minimal machine-readable exports for the website:
      SDT/website/public/downloads/atomicus-complete.json
      SDT/website/public/downloads/atomicus-complete.csv
    These exports are intentionally conservative: they do not invent missing
    physical values. They primarily provide indexing/coverage.
    """
    website_dir = repo_root / "SDT" / "website"
    public_downloads = website_dir / "public" / "downloads"
    public_downloads.mkdir(parents=True, exist_ok=True)

    # Build Z -> files mapping
    files_by_z: dict[int, list[str]] = {}
    for p in atomicus_dir.glob("*.md"):
        m = FILENAME_Z_RE.match(p.name)
        if not m:
            continue
        z = int(m.group("z"))
        files_by_z.setdefault(z, []).append(p.name)
    for z in files_by_z:
        files_by_z[z].sort()

    # CSV export
    csv_lines = ["Z,name,symbol,files\n"]
    for z in range(1, 119):
        e = ELEMENTS.get(z)
        if not e:
            continue
        files = "|".join(files_by_z.get(z, []))
        csv_lines.append(f"{z},{e.name},{e.symbol},\"{files}\"\n")
    (public_downloads / "atomicus-complete.csv").write_text("".join(csv_lines), encoding="utf-8")

    # JSON export
    items = []
    for z in range(1, 119):
        e = ELEMENTS.get(z)
        if not e:
            continue
        items.append(
            {
                "Z": z,
                "name": e.name,
                "symbol": e.symbol,
                "files": files_by_z.get(z, []),
            }
        )
    import json

    payload = {
        "metadata": {
            "source": "SDT/ATOMICUS markdown library",
            "note": "This export is an index/coverage list. Physical values may be populated later.",
            "generated_by": str(atomicus_dir / "generate_missing_atomicus.py"),
        },
        "elements": items,
    }
    (public_downloads / "atomicus-complete.json").write_text(json.dumps(payload, indent=2), encoding="utf-8")


def main() -> None:
    atomicus_dir = Path(__file__).resolve().parent
    # Repo root: .../Spatial_Displacement_Theory
    repo_root = atomicus_dir.parent.parent
    written = write_missing_files(atomicus_dir)
    write_index(atomicus_dir)
    write_master_table(atomicus_dir)
    write_website_exports(repo_root=repo_root, atomicus_dir=atomicus_dir)
    print(f"Generated {len(written)} missing ATOMICUS file(s).")
    print("Wrote ATOMICUS_INDEX.md.")
    print("Wrote SDT_Master_Geometric_Table.md (normalized full 1–118 table).")
    print("Wrote website downloads: atomicus-complete.csv/json.")


if __name__ == "__main__":
    main()

