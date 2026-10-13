#!/usr/bin/env python3
"""
parse_sparc_mrt.py — Reproducible fetch + parse of the REAL SPARC master table.

SPARC: Lelli, McGaugh & Schombert (2016), AJ 152, 157 — "SPARC: Mass Models
for 175 Disk Galaxies with Spitzer Photometry and Accurate Rotation Curves."

This script fetches the published master table and writes:
    sparc_175.csv  with columns:  name,M_bar_Msun,h_R_kpc,v_flat_kms,quality

Baryonic mass (standard SPARC convention):
    M_bar = 0.5 * L[3.6]*1e9  +  1.33 * MHI*1e9
      0.5  = stellar mass-to-light ratio at 3.6um (Lelli 2016 / McGaugh)
      1.33 = helium correction on the HI gas mass

Filtering:
    keep rows with Vflat > 0 AND Rdisk > 0 ; keep all quality flags (1,2,3).

Data sources tried in order:
    1. astroweb (original MRT, fixed-width)        http://astroweb.cwru.edu/SPARC/SPARC_Lelli2016c.mrt
    2. Vizier TSV mirror (J/AJ/152/157, table1)    https://vizier.cds.unistra.fr/viz-bin/asu-tsv?...
The Vizier mirror is byte-for-byte the same catalogue, just delivered as TSV.
"""
import sys, os, io, urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
OUT_CSV   = os.path.join(HERE, "sparc_175.csv")
RAW_MRT   = os.path.join(HERE, "sparc_master.mrt")
RAW_TSV   = os.path.join(HERE, "sparc_table1.tsv")

UA = {"User-Agent": "Mozilla/5.0"}

ASTROWEB_URL = "http://astroweb.cwru.edu/SPARC/SPARC_Lelli2016c.mrt"
VIZIER_URL   = ("https://vizier.cds.unistra.fr/viz-bin/asu-tsv?"
                "-source=J/AJ/152/157/table1&-out.max=unlimited&-out.all")

# --- Byte-by-byte description of the SPARC master table (SPARC_Lelli2016c.mrt) ---
# These are the 1-indexed inclusive byte ranges from the MRT's own header.
# (Verified against the MRT "Byte-by-byte Description of file" section.)
MRT_COLS = {
    "Galaxy": (1, 11),     # A11   --      Galaxy name
    "T":      (13, 14),    # I2    --      Hubble type
    "D":      (16, 21),    # F6.2  Mpc     Distance
    "e_D":    (23, 27),    # F5.2  Mpc     Distance error
    "f_D":    (29, 29),    # I1    --      Distance method flag
    "Inc":    (31, 34),    # F4.1  deg     Inclination
    "e_Inc":  (36, 39),    # F4.1  deg     Inclination error
    "L[3.6]": (41, 47),    # F7.3  10+9solLum  Total 3.6um luminosity
    "e_L[3.6]":(49,55),    # F7.3  10+9solLum  err
    "Reff":   (57, 61),    # F5.2  kpc     Effective radius
    "SBeff":  (63, 70),    # F8.2          Eff. surface brightness
    "Rdisk":  (72, 76),    # F5.2  kpc     Disk scale length  -> h_R_kpc
    "SBdisk": (78, 85),    # F8.2          Disk central surface brightness
    "MHI":    (87, 93),    # F7.3  10+9solMass Total HI mass
    "RHI":    (95, 99),    # F5.2  kpc     HI radius
    "Vflat":  (101,105),   # F5.1  km/s    Asympt. flat rotation velocity -> v_flat_kms
    "e_Vflat":(107,111),   # F5.1  km/s    err
    "Q":      (113,113),   # I1    --      Quality flag (1,2,3)  -> quality
    "Ref":    (115,141),   # A27           Reference
}


def fetch(url, dest):
    req = urllib.request.Request(url, headers=UA)
    data = urllib.request.urlopen(req, timeout=90).read()
    with open(dest, "wb") as f:
        f.write(data)
    return data.decode("utf-8", "replace")


def parse_mrt_fixedwidth(text):
    """Parse the original fixed-width MRT using byte ranges. Returns list of dicts."""
    lines = text.splitlines()
    # Find the start of the data: after the second '------' separator following
    # the byte-by-byte block. Robust approach: a data line begins with a galaxy
    # name (non-space in col 1) and has a parseable Vflat field.
    rows = []
    for ln in lines:
        if len(ln) < 113:
            continue
        name = ln[0:11].strip()
        if not name or name.startswith("-") or name.startswith("#"):
            continue
        if name in ("Galaxy",):
            continue

        def cut(key):
            a, b = MRT_COLS[key]
            return ln[a-1:b].strip()
        try:
            L36   = cut("L[3.6]")
            MHI   = cut("MHI")
            Rdisk = cut("Rdisk")
            Vflat = cut("Vflat")
            Q     = cut("Q")
            # must look numeric to be a real data row
            float(Rdisk); float(Vflat)
        except Exception:
            continue
        rows.append({
            "name": name,
            "L36": _f(L36), "MHI": _f(MHI),
            "Rdisk": _f(Rdisk), "Vflat": _f(Vflat),
            "Q": Q,
        })
    return rows


def parse_vizier_tsv(text):
    """Parse the Vizier TSV mirror by column label. Returns list of dicts.

    Vizier TSV layout for J/AJ/152/157/table1 (verified against the served file):
      - leading '#'-prefixed comment/meta/Column-description lines
      - one tab-separated HEADER row whose labels are:
          recno Name Nvel Type Dist e_Dist f_Dist i e_i L3.6 e_L3.6 Reff SBeff
          Rdisk SBdisk MHI RHI Vflat e_Vflat Qual Ref ... _RA _DE
        Units (L3.6=GLsun=1e9 Lsun, MHI=GMsun=1e9 Msun, Rdisk=kpc, Vflat=km/s).
      - one UNITS row, then one '----' SEPARATOR row, then the 175 data rows.
    """
    lines = text.splitlines()
    body = [l for l in lines if not l.startswith("#") and l.strip() != ""]
    # header row = first body line whose tab-split contains 'Name' and 'Vflat'
    hidx = None
    for i, l in enumerate(body):
        cells = l.split("\t")
        if "Name" in cells and "Vflat" in cells:
            hidx = i
            break
    if hidx is None:
        raise RuntimeError("Vizier TSV: header row (Name/Vflat) not found")
    header = body[hidx].split("\t")

    # Map the SPARC labels we need to the Vizier column labels actually present.
    label = {"name": "Name", "L36": "L3.6", "MHI": "MHI",
             "Rdisk": "Rdisk", "Vflat": "Vflat", "Q": "Qual"}
    ci = {k: header.index(v) for k, v in label.items()}

    rows = []
    for l in body[hidx+1:]:
        cells = l.split("\t")
        if len(cells) != len(header):
            continue
        first = cells[0].strip()
        # skip the units row (recno cell blank) and the '----' separator row
        if first == "" or set(first) <= set("-"):
            continue
        if not first.lstrip("-").isdigit():  # recno is an integer for data rows
            continue
        rows.append({
            "name":  cells[ci["name"]].strip(),
            "L36":   _f(cells[ci["L36"]]),
            "MHI":   _f(cells[ci["MHI"]]),
            "Rdisk": _f(cells[ci["Rdisk"]]),
            "Vflat": _f(cells[ci["Vflat"]]),
            "Q":     cells[ci["Q"]].strip(),
        })
    return rows


def _f(s):
    s = (s or "").strip()
    if s == "" or s.lower() in ("nan", "---", "--"):
        return None
    try:
        return float(s)
    except ValueError:
        return None


def build(rows, source_label):
    kept = []
    for r in rows:
        if r["Vflat"] is None or r["Vflat"] <= 0:
            continue
        if r["Rdisk"] is None or r["Rdisk"] <= 0:
            continue
        L36 = r["L36"] if r["L36"] is not None else 0.0
        MHI = r["MHI"] if r["MHI"] is not None else 0.0
        M_bar = 0.5 * L36 * 1e9 + 1.33 * MHI * 1e9
        kept.append((r["name"], M_bar, r["Rdisk"], r["Vflat"], r["Q"]))

    with open(OUT_CSV, "w", newline="") as f:
        f.write("name,M_bar_Msun,h_R_kpc,v_flat_kms,quality\n")
        for name, M_bar, h_R, vflat, q in kept:
            f.write(f"{name},{M_bar:.6e},{h_R:.4g},{vflat:.4g},{q}\n")

    print(f"SOURCE       : {source_label}")
    print(f"PARSED ROWS  : {len(rows)}")
    print(f"KEPT (Vflat>0, Rdisk>0): {len(kept)}")
    print(f"WROTE        : {OUT_CSV}")
    return kept


def main():
    rows = None
    label = None
    # 1) try original astroweb MRT (fixed-width, byte ranges)
    try:
        print("Trying astroweb MRT ...")
        txt = fetch(ASTROWEB_URL, RAW_MRT)
        rows = parse_mrt_fixedwidth(txt)
        if len(rows) > 100:
            label = "astroweb MRT (fixed-width, byte-ranges) — " + ASTROWEB_URL
        else:
            rows = None
    except Exception as e:
        print(f"  astroweb failed: {e}")

    # 2) fall back to Vizier TSV mirror (same catalogue, TSV by column label)
    if rows is None:
        print("Trying Vizier TSV mirror ...")
        txt = fetch(VIZIER_URL, RAW_TSV)
        rows = parse_vizier_tsv(txt)
        label = "Vizier mirror J/AJ/152/157 table1 (TSV) — " + VIZIER_URL

    kept = build(rows, label)

    # preview
    with open(OUT_CSV) as f:
        out = f.read().splitlines()
    print("\n--- FIRST 6 LINES (incl header) ---")
    for l in out[:6]:
        print(l)
    print("--- LAST 5 LINES ---")
    for l in out[-5:]:
        print(l)


if __name__ == "__main__":
    main()
