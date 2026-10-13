#!/usr/bin/env python3
"""
fetch_nuclear.py  --  APS03 Scale (D) NUCLEAR data fetcher (AME2020 + NUBASE2020).

Investigation: APS03 Universal Drafting Crossover, stretch scale (D) (nuclear binding).
Author of the investigation: James Christopher Tyndall, Melbourne, Australia.

WHAT THIS DOES
--------------
1. Downloads (or reuses a cached copy of) the AME2020 atomic-mass evaluation table
   `mass_1.mas20.txt` and the NUBASE2020 table `nubase_4.mas20.txt` from the IAEA
   Atomic Mass Data Center (AMDC) mirror.
2. Parses the fixed-width AME2020 mass table for binding energy per nucleon (BE/A)
   in keV together with its measurement uncertainty -- these are GENUINE AME2020
   tabulated values, read directly from the "BINDING ENERGY/A (keV)" column, NOT
   recomputed.  (A mass-excess cross-derivation is included as an auditable check
   only; see verify_be_from_mass_excess.)
3. Uses NUBASE2020 to keep only STABLE and LONG-LIVED nuclides (stable, or
   half-life >= LONGLIVED_MIN_SECONDS), and to flag electron-capture (EC / beta+)
   isotopes for the SDT alternate ("EC_alt") construction grammar.
4. Applies the SDT nuclear construction grammar to assign deuteron/triton counts
   and a grammar_class, then writes nuclear_binding.csv.

SDT NUCLEAR CONSTRUCTION GRAMMAR (from CLAUDE.md / ATOMICUS rules)
-----------------------------------------------------------------
Every nucleus with Z >= 2 = 1 alpha core + n_d deuterons + n_t tritons:
    n_t = A - 2*Z                  (triton count)
    n_d = 3*Z - A - 2              (deuteron count)
Electron-capture / alternate grammar (He-3 core instead of He-4):
    n_t = A - 2*Z + 1
    n_d = 3*Z - A - 3

grammar_class:
    alpha_only       if n_deu == 0 and n_tri == 0   (A = 2Z+2, He-4-like multiples)
    deuteron_rich    if n_tri == 0 and n_deu  > 0
    triton_bearing   if n_tri >  0
    EC_alt           known electron-capture isotopes (assigned BEFORE the above,
                     using the alternate-grammar n_d/n_t)

CSV columns:
    Z,A,element,BE_per_A_keV,BE_per_A_err_keV,n_deu,n_tri,grammar_class,source

USAGE
-----
    python fetch_nuclear.py            # download if missing, then parse & write CSV
    python fetch_nuclear.py --offline  # never hit the network; require cached files
    python fetch_nuclear.py --force    # re-download even if cached files exist
"""

import argparse
import hashlib
import os
import ssl
import sys
import urllib.request

# ---------------------------------------------------------------------------
# Sources (IAEA AMDC mirror of the AME2020 / NUBASE2020 tables).
# Files were located by listing https://www-nds.iaea.org/amdc/ (the canonical
# filenames carry a ".txt" suffix on this mirror).
# ---------------------------------------------------------------------------
AME_URL = "https://www-nds.iaea.org/amdc/ame2020/mass_1.mas20.txt"
NUBASE_URL = "https://www-nds.iaea.org/amdc/ame2020/nubase_4.mas20.txt"

HERE = os.path.dirname(os.path.abspath(__file__))
AME_FILE = os.path.join(HERE, "mass_1.mas20.txt")
NUBASE_FILE = os.path.join(HERE, "nubase_4.mas20.txt")
OUT_CSV = os.path.join(HERE, "nuclear_binding.csv")

# Recorded provenance for the files this script was developed against.
# If a re-download differs, the byte count is printed so a stale-cache swap is visible.
KNOWN_AME_SHA256 = "e8599c6d7f724fac91934e59f1b9de8fb8f63e820f4b39456b790665ed2a3307"
KNOWN_AME_BYTES = 472648
KNOWN_NUBASE_SHA256 = "1585a5eea86c5e17e90307c7e6e786d060049c4039e392a261ff6db977df9859"
KNOWN_NUBASE_BYTES = 761906

# "Long-lived" threshold: keep nuclides with T_1/2 >= 1 year (in seconds).
# Stable nuclides ("stbl" in NUBASE) are always kept.
LONGLIVED_MIN_SECONDS = 3.156e7  # 1 yr

# Half-life unit -> seconds (NUBASE2020 unit codes).
HL_UNIT_SECONDS = {
    "ys": 1e-24, "zs": 1e-21, "as": 1e-18, "fs": 1e-15, "ps": 1e-12,
    "ns": 1e-9, "us": 1e-6, "ms": 1e-3, "s": 1.0,
    "m": 60.0, "h": 3600.0, "d": 86400.0, "y": 3.156e7,
    "ky": 3.156e10, "My": 3.156e13, "Gy": 3.156e16,
    "Ty": 3.156e19, "Py": 3.156e22, "Ey": 3.156e25,
    "Zy": 3.156e28, "Yy": 3.156e31,
}

# Physical constants for the mass-excess cross-check ONLY (CODATA 2018 / AME2020).
M_H_EXCESS_KEV = 7288.971064   # H-1 atomic mass excess (keV) -- AME2020
M_N_EXCESS_KEV = 8071.31806    # neutron mass excess (keV) -- AME2020
# BE = Z*ME(H-1) + N*ME(n) - ME(nuclide)   [all atomic mass excesses, keV]


def download(url, dest, offline, force):
    if os.path.exists(dest) and not force:
        return False, "cached"
    if offline:
        raise RuntimeError(f"--offline set but {dest} missing; cannot fetch {url}")
    ctx = ssl.create_default_context()  # TLS verification ON
    req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0 (APS03 fetch_nuclear.py)"})
    with urllib.request.urlopen(req, timeout=120, context=ctx) as r:
        data = r.read()
    with open(dest, "wb") as f:
        f.write(data)
    return True, f"downloaded {len(data)} bytes"


def provenance(path, known_sha, known_bytes):
    data = open(path, "rb").read()
    sha = hashlib.sha256(data).hexdigest()
    nbytes = len(data)
    nlines = data.count(b"\n")
    print(f"  path     : {path}")
    print(f"  bytes    : {nbytes}" + ("" if nbytes == known_bytes else f"  (RECORDED {known_bytes} -- DIFFERS!)"))
    print(f"  lines    : {nlines}")
    print(f"  sha256   : {sha}" + ("" if sha == known_sha else "  (RECORDED differs -- source changed!)"))
    return sha, nbytes


# ---------------------------------------------------------------------------
# AME2020 fixed-width parse.
#
# AME2020 header (mass_1.mas20.txt, line 22-23) gives the Fortran format:
#   a1,i3,i5,i5,i5,1x,a3,a4,1x,f14.6,f12.6,f13.5,1x,f10.5,1x,a2,f13.5,f11.5,1x,i3,1x,f13.6,f12.6
#   cc NZ  N  Z  A    el  o     mass  unc binding unc      B  beta  unc    atomic_mass   unc
#
# Derived 0-based byte slices (verified against the He-4 row):
#   cc        [0:1]
#   N-Z       [1:4]
#   N         [4:9]
#   Z         [9:14]
#   A         [14:19]
#   1x        [19:20]
#   EL        [20:23]
#   O(origin) [23:27]
#   1x        [27:28]
#   MASS EXCESS (keV)      [28:42]   f14.6
#   d(MASS EXCESS) (keV)   [42:54]   f12.6
#   BINDING ENERGY/A (keV) [54:67]   f13.5   <-- the datum we want
#   1x                     [67:68]
#   d(BINDING ENERGY/A)    [68:78]   f10.5   <-- its uncertainty
# A '#' in place of a decimal point marks an estimated (non-experimental) value;
# a '*' marks a not-calculable quantity. We skip rows whose BE/A is '#'/'*'.
# ---------------------------------------------------------------------------
def parse_ame(path):
    out = {}  # (Z, A) -> dict
    started = False
    for raw in open(path, encoding="latin-1"):
        line = raw.rstrip("\n")
        if not started:
            if line.lstrip().startswith("1N-Z") or line.lstrip().startswith("0N-Z") or ("N-Z" in line and "BINDING ENERGY/A" in line):
                started = True
            continue
        if len(line) < 78:
            continue
        z_s = line[9:14].strip()
        a_s = line[14:19].strip()
        el = line[20:23].strip()
        if not z_s or not a_s or not z_s.lstrip("-").isdigit() or not a_s.isdigit():
            continue
        Z = int(z_s)
        A = int(a_s)
        ba_s = line[54:67].strip()
        ba_u_s = line[68:78].strip()
        me_s = line[28:42].strip()
        # Skip estimated / non-experimental (# in place of a digit) or not-calculable (*).
        if "#" in ba_s or "*" in ba_s or ba_s == "":
            continue
        try:
            be_per_a = float(ba_s)
        except ValueError:
            continue
        try:
            be_per_a_err = float(ba_u_s.replace("#", ""))
        except ValueError:
            be_per_a_err = float("nan")
        me = None
        if "#" not in me_s and "*" not in me_s and me_s:
            try:
                me = float(me_s)
            except ValueError:
                me = None
        out[(Z, A)] = {
            "Z": Z, "A": A, "element": el,
            "BE_per_A_keV": be_per_a, "BE_per_A_err_keV": be_per_a_err,
            "mass_excess_keV": me,
        }
    return out


# ---------------------------------------------------------------------------
# NUBASE2020 fixed-width parse (header in nubase_4.mas20.txt lines 3-24).
#   AAA   [0:3]
#   ZZZi  [4:8]   (last digit i: 0=gs, 1,2=isomers, ...)
#   A El  [11:16]
#   T     [69:78]   half-life value ('stbl', 'p-unst', or a number)
#   unit  [79:81]
#   BR    [119:]    decay modes & intensities; 'IS=' = isotopic abundance (=> in nature)
# We only use ground states (i == 0).
# ---------------------------------------------------------------------------
def parse_nubase(path):
    info = {}  # (Z, A) -> dict(stable, halflife_s, is_ec, has_abundance)
    for raw in open(path, encoding="latin-1"):
        line = raw.rstrip("\n")
        if line.startswith("#") or len(line) < 80:
            continue
        a_s = line[0:3].strip()
        zzzi = line[4:8].strip()
        if not a_s.isdigit() or not zzzi.isdigit():
            continue
        A = int(a_s)
        i = int(zzzi[-1])
        if i != 0:  # ground state only
            continue
        Z = int(zzzi[:-1])
        t_s = line[69:78].strip()
        unit = line[79:81].strip()
        br = line[119:] if len(line) > 119 else ""

        stable = (t_s == "stbl")
        halflife_s = float("inf") if stable else None
        if not stable and t_s and t_s not in ("p-unst",):
            try:
                val = float(t_s.replace("#", "").replace("<", "").replace(">", "").replace("~", ""))
                halflife_s = val * HL_UNIT_SECONDS.get(unit, float("nan"))
            except ValueError:
                halflife_s = None

        br_up = br.upper()
        is_ec = ("EC" in br_up) or ("B+" in br_up) or ("E+" in br_up)
        has_abundance = "IS=" in br_up

        info[(Z, A)] = {
            "stable": stable,
            "halflife_s": halflife_s,
            "is_ec": is_ec,
            "has_abundance": has_abundance,
        }
    return info


def grammar(Z, A, is_ec):
    """Return (n_deu, n_tri, grammar_class) per the SDT construction grammar.

    The "1 alpha core + n_d deuterons + n_t tritons" grammar is constitutional for
    Z >= 2 (CLAUDE.md / ATOMICUS rules). H-1, H-2, H-3 and He-3 ARE the elementary
    constituents (proton, deuteron, triton, He-3 core), so the alpha-core formula
    does not apply to them; we tag them 'constituent' and still emit the formal
    n_d/n_t the formula yields (which can be negative -- a signal that the alpha
    decomposition is inapplicable, not a real packing count).
    """
    if is_ec:
        # alternate (He-3 core) grammar for electron-capture / beta+ isotopes
        n_tri = A - 2 * Z + 1
        n_deu = 3 * Z - A - 3
        return n_deu, n_tri, "EC_alt"
    n_tri = A - 2 * Z
    n_deu = 3 * Z - A - 2
    if Z < 2:
        # H isotopes: elementary constituents, alpha grammar undefined.
        return n_deu, n_tri, "constituent"
    if n_deu == 0 and n_tri == 0:
        cls = "alpha_only"
    elif n_tri == 0 and n_deu > 0:
        cls = "deuteron_rich"
    elif n_tri > 0:
        cls = "triton_bearing"
    else:
        # n_tri < 0 (A < 2Z, proton-rich) AND not flagged EC: alpha grammar gives a
        # negative triton count, so the standard decomposition is inapplicable.
        cls = "constituent"
    return n_deu, n_tri, cls


def verify_be_from_mass_excess(rec):
    """Auditable cross-check: BE/A recomputed from atomic mass excesses (keV)."""
    me = rec.get("mass_excess_keV")
    if me is None:
        return None
    Z, A = rec["Z"], rec["A"]
    N = A - Z
    be = Z * M_H_EXCESS_KEV + N * M_N_EXCESS_KEV - me
    return be / A


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--offline", action="store_true", help="never download; require cached files")
    ap.add_argument("--force", action="store_true", help="re-download even if cached")
    args = ap.parse_args()

    print("=== APS03 nuclear fetch (AME2020 + NUBASE2020) ===")
    print("AME source   :", AME_URL)
    print("NUBASE source:", NUBASE_URL)
    print()

    for url, dest in ((AME_URL, AME_FILE), (NUBASE_URL, NUBASE_FILE)):
        changed, msg = download(url, dest, args.offline, args.force)
        print(f"[fetch] {os.path.basename(dest)}: {msg}")
    print()

    print("--- provenance: AME2020 ---")
    provenance(AME_FILE, KNOWN_AME_SHA256, KNOWN_AME_BYTES)
    print("--- provenance: NUBASE2020 ---")
    provenance(NUBASE_FILE, KNOWN_NUBASE_SHA256, KNOWN_NUBASE_BYTES)
    print()

    ame = parse_ame(AME_FILE)
    nub = parse_nubase(NUBASE_FILE)
    print(f"AME rows with experimental BE/A : {len(ame)}")
    print(f"NUBASE ground states            : {len(nub)}")

    rows = []
    kept_reasons = {"stable": 0, "longlived": 0}
    for key in sorted(ame.keys(), key=lambda zA: (zA[0], zA[1])):
        Z, A = key
        if Z < 1:
            continue
        rec = ame[key]
        nb = nub.get(key)
        # Stability / longevity gate (require NUBASE classification).
        if nb is None:
            continue
        if nb["stable"]:
            kept_reasons["stable"] += 1
        elif nb["halflife_s"] is not None and nb["halflife_s"] >= LONGLIVED_MIN_SECONDS:
            kept_reasons["longlived"] += 1
        else:
            continue
        is_ec = nb["is_ec"]
        n_deu, n_tri, cls = grammar(Z, A, is_ec)
        rows.append({
            "Z": Z, "A": A, "element": rec["element"],
            "BE_per_A_keV": rec["BE_per_A_keV"],
            "BE_per_A_err_keV": rec["BE_per_A_err_keV"],
            "n_deu": n_deu, "n_tri": n_tri,
            "grammar_class": cls,
            "source": "AME2020",
        })

    header = ["Z", "A", "element", "BE_per_A_keV", "BE_per_A_err_keV",
              "n_deu", "n_tri", "grammar_class", "source"]
    with open(OUT_CSV, "w", encoding="utf-8", newline="") as f:
        f.write(",".join(header) + "\n")
        for r in rows:
            f.write("{Z},{A},{element},{BE_per_A_keV:.4f},{BE_per_A_err_keV:.4f},"
                    "{n_deu},{n_tri},{grammar_class},{source}\n".format(**r))

    print()
    print(f"WROTE {OUT_CSV}")
    print(f"rows: {len(rows)}  (stable={kept_reasons['stable']}, longlived>=1yr={kept_reasons['longlived']})")
    from collections import Counter
    cc = Counter(r["grammar_class"] for r in rows)
    for k in ("alpha_only", "deuteron_rich", "triton_bearing", "EC_alt", "constituent"):
        print(f"  {k:16s}: {cc.get(k,0)}")

    # Cross-checks requested by the deliverable.
    print()
    print("--- cross-check (parsed BE/A vs known) ---")
    for (Z, A), expect in (((2, 4), 7074), ((26, 56), 8790), ((92, 238), 7570)):
        rec = ame.get((Z, A))
        if rec:
            xcheck = verify_be_from_mass_excess(rec)
            xs = f"{xcheck:.2f}" if xcheck is not None else "n/a"
            print(f"  Z={Z:3d} A={A:3d} {rec['element']:2s}: parsed BE/A={rec['BE_per_A_keV']:.2f} keV "
                  f"(+/- {rec['BE_per_A_err_keV']:.4f})  expect~{expect}  [mass-excess recompute={xs}]")
        else:
            print(f"  Z={Z} A={A}: NOT FOUND")

    print()
    print("--- first 5 rows ---")
    for r in rows[:5]:
        print("  ", r)
    print("--- last 5 rows ---")
    for r in rows[-5:]:
        print("  ", r)


if __name__ == "__main__":
    main()
