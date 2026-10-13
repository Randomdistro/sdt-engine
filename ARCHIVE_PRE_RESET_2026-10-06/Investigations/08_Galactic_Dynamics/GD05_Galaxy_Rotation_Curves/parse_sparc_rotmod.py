#!/usr/bin/env python3
"""
parse_sparc_rotmod.py

Fetch and parse the SPARC per-galaxy rotation-curve decomposition
("_rotmod.dat" / Rotmod_LTG files) from Lelli, McGaugh & Schombert (2016),
AJ 152, 157, and emit a single tidy CSV with one row per (galaxy, radius).

Output columns:
  name,R_kpc,Vobs_kms,eVobs_kms,Vgas_kms,Vdisk_kms,Vbul_kms,SBdisk_Lsun_pc2,SBbul_Lsun_pc2

Each _rotmod.dat file uses the standard SPARC column order:
  Rad[kpc]  Vobs[km/s]  errV[km/s]  Vgas[km/s]  Vdisk[km/s]  Vbul[km/s]  SBdisk[L/pc2]  SBbul[L/pc2]
Vdisk / Vbul are the stellar contributions at the SPARC fiducial M/L = 1.
Vbul is identically 0 for bulgeless galaxies.

Data sources tried, in order:
  1. http://astroweb.cwru.edu/SPARC/Rotmod_LTG.zip   (canonical bundle)
  2. http://astroweb.cwru.edu/SPARC/BulgeDiskDec_LTG.zip
  3. GitHub mirrors of the Rotmod_LTG _rotmod.dat files
The script downloads a zip of *_rotmod.dat files, parses each, and concatenates.

Usage:
  python parse_sparc_rotmod.py            # fetch + parse -> sparc_rotmod.csv
  python parse_sparc_rotmod.py --zip path/to/Rotmod_LTG.zip   # parse a local zip
  python parse_sparc_rotmod.py --dir path/to/folder_of_dat    # parse a local folder
"""

import argparse
import io
import os
import re
import sys
import zipfile
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
OUT_CSV = os.path.join(HERE, "sparc_rotmod.csv")

HEADER = ["name", "R_kpc", "Vobs_kms", "eVobs_kms", "Vgas_kms",
          "Vdisk_kms", "Vbul_kms", "SBdisk_Lsun_pc2", "SBbul_Lsun_pc2"]

# Candidate zip bundles of *_rotmod.dat files (tried in order).
ZIP_URLS = [
    "http://astroweb.cwru.edu/SPARC/Rotmod_LTG.zip",
    "http://astroweb.cwru.edu/SPARC/BulgeDiskDec_LTG.zip",
    "https://astroweb.case.edu/SPARC/Rotmod_LTG.zip",
    # GitHub mirrors (raw zips committed to repos):
    "https://github.com/lufre1/SPARC/raw/main/Rotmod_LTG.zip",
    "https://github.com/lufre1/SPARC/raw/master/Rotmod_LTG.zip",
]

UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) python-urllib SPARC-fetch"


def fetch_bytes(url, timeout=60):
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        return r.read()


def download_zip():
    last_err = None
    for url in ZIP_URLS:
        try:
            sys.stderr.write(f"[fetch] trying {url}\n")
            data = fetch_bytes(url)
            # sanity: must be a zip
            if data[:2] == b"PK":
                sys.stderr.write(f"[fetch] OK {len(data)} bytes from {url}\n")
                return data, url
            else:
                sys.stderr.write(f"[fetch] not a zip ({data[:16]!r}) from {url}\n")
        except Exception as e:  # noqa: BLE001
            sys.stderr.write(f"[fetch] FAIL {url}: {e}\n")
            last_err = e
    raise RuntimeError(f"All zip URLs failed. Last error: {last_err}")


def galaxy_name_from_filename(fn):
    base = os.path.basename(fn)
    base = re.sub(r"_rotmod\.dat$", "", base, flags=re.IGNORECASE)
    base = re.sub(r"\.dat$", "", base, flags=re.IGNORECASE)
    return base


def parse_dat_text(name, text):
    """Parse one _rotmod.dat file's text. Returns list of row lists."""
    rows = []
    for raw in text.splitlines():
        line = raw.strip()
        if not line:
            continue
        if line.startswith("#") or line.startswith("!"):
            continue
        # first token must be numeric (radius); else it's a header/comment
        parts = line.split()
        if len(parts) < 3:
            continue
        try:
            float(parts[0])
        except ValueError:
            continue
        # Standard SPARC rotmod: Rad Vobs errV Vgas Vdisk Vbul SBdisk SBbul
        # Pad missing trailing columns with 0 (some files omit SBbul / Vbul).
        vals = parts[:8]
        while len(vals) < 8:
            vals.append("0")
        try:
            r, vobs, evobs, vgas, vdisk, vbul, sbdisk, sbbul = (float(x) for x in vals[:8])
        except ValueError:
            continue
        rows.append([name, r, vobs, evobs, vgas, vdisk, vbul, sbdisk, sbbul])
    return rows


def parse_zip_bytes(data):
    out = []
    with zipfile.ZipFile(io.BytesIO(data)) as zf:
        names = [n for n in zf.namelist() if n.lower().endswith(".dat")]
        names.sort()
        for n in names:
            txt = zf.read(n).decode("utf-8", errors="replace")
            gal = galaxy_name_from_filename(n)
            out.extend(parse_dat_text(gal, txt))
    return out


def parse_dir(path):
    out = []
    files = sorted(f for f in os.listdir(path) if f.lower().endswith(".dat"))
    for f in files:
        with open(os.path.join(path, f), "r", encoding="utf-8", errors="replace") as fh:
            txt = fh.read()
        gal = galaxy_name_from_filename(f)
        out.extend(parse_dat_text(gal, txt))
    return out


def fmt(x):
    if isinstance(x, float):
        # compact but lossless-ish
        s = f"{x:.6g}"
        return s
    return str(x)


def write_csv(rows, out_csv=OUT_CSV):
    with open(out_csv, "w", encoding="utf-8", newline="") as fh:
        fh.write(",".join(HEADER) + "\n")
        for row in rows:
            fh.write(",".join(fmt(v) for v in row) + "\n")


def summarize(rows):
    from collections import defaultdict
    by_gal = defaultdict(list)
    for r in rows:
        by_gal[r[0]].append(r)
    n_gal = len(by_gal)
    n_bulge = 0
    for g, rs in by_gal.items():
        if any(r[6] > 0.0 for r in rs):  # Vbul column index 6
            n_bulge += 1
    return n_gal, n_bulge, len(rows)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--zip", help="parse a local Rotmod zip instead of fetching")
    ap.add_argument("--dir", help="parse a local folder of _rotmod.dat files")
    ap.add_argument("--out", default=OUT_CSV)
    args = ap.parse_args()

    if args.dir:
        rows = parse_dir(args.dir)
        src = f"local dir: {args.dir}"
    elif args.zip:
        with open(args.zip, "rb") as fh:
            data = fh.read()
        rows = parse_zip_bytes(data)
        src = f"local zip: {args.zip}"
    else:
        data, url = download_zip()
        rows = parse_zip_bytes(data)
        src = url

    # sort by name then radius for stable output
    rows.sort(key=lambda r: (r[0], r[1]))
    write_csv(rows, args.out)
    n_gal, n_bulge, n_rows = summarize(rows)
    print(f"source: {src}")
    print(f"wrote: {args.out}")
    print(f"rows: {n_rows}  galaxies: {n_gal}  with_bulge: {n_bulge}  bulgeless: {n_gal - n_bulge}")


if __name__ == "__main__":
    main()
