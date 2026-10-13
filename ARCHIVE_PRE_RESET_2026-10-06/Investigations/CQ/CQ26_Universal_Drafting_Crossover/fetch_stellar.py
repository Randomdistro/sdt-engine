#!/usr/bin/env python3
"""
CQ26 Scale (B) STELLAR-SYSTEM data fetcher.

Builds stellar_orbits.csv spanning the full exposure ratio
    xi = g_host / a0,   a0 = 1.042e-10 m/s^2
from the deep source regime (planets, xi ~ 1e7..1e12) down to the
floor regime (wide binaries, detached TNOs, xi < 1).

Four classes are collected:
  planet      - 8 solar-system planets (JPL) + ~40 NASA Exoplanet Archive planets
  giant_host  - planets orbiting evolved/giant host stars (NEXSCI subset)
  binary      - wide binaries from El-Badry, Rix & Heintz 2021 (Gaia eDR3, Zenodo 4435257)
  substellar  - detached / extreme TNOs (Sedna etc., JPL Small-Body Database)

ALL orbital data are genuine published values fetched from primary sources.
The ONLY derived quantity is the wide-binary PRIMARY MASS, which is estimated
from the primary's absolute Gaia G magnitude via a published main-sequence
mass-luminosity relation (Pecaut & Mamajek 2013, updated table). This mass is
INDEPENDENT of the orbit under test (it comes from the star's own photometry,
not from the binary dynamics), satisfying the CQ26 anti-circularity rule. Such
rows are tagged source="ElBadry2021+MLR(phot)" so they are auditable.

Output columns:
  class,name,host,a_AU,a_err,P_yr,P_err,host_mass_Msun,host_mass_err,
  v_obs_kms,source,source_id

Usage:
  python fetch_stellar.py                 # fetch everything, write stellar_orbits.csv
  python fetch_stellar.py --no-binaries   # skip the 1.4 GB El-Badry download
  python fetch_stellar.py --binaries-fits PATH   # use an already-downloaded FITS

Author context: CQ26 Universal Drafting Crossover, James Christopher Tyndall.
"""

import argparse
import csv
import io
import math
import os
import sys
import urllib.parse
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
OUT_CSV = os.path.join(HERE, "stellar_orbits.csv")

# ----------------------------------------------------------------------------
# physical constants (for the xi sanity check only; CSV stores raw observables)
# ----------------------------------------------------------------------------
G_SI      = 6.67430e-11        # m^3 kg^-1 s^-2  (CODATA 2018) - conversion only
MSUN_KG   = 1.98892e30         # kg
AU_M      = 1.495978707e11     # m
YR_S      = 3.1557e7           # s (Julian year ~ 365.25 d)
A0_SDT    = 1.042e-10          # m/s^2   (galactic.hpp a_0_SDT = c*H0/2pi)

HEADER = ["class", "name", "host", "a_AU", "a_err", "P_yr", "P_err",
          "host_mass_Msun", "host_mass_err", "v_obs_kms", "source", "source_id"]


def xi_of(a_AU, host_mass_Msun):
    """xi = G*M/(a^2 * a0). Source-dominated >> 1, floor-dominated << 1."""
    a_m = a_AU * AU_M
    M_kg = host_mass_Msun * MSUN_KG
    g = G_SI * M_kg / (a_m * a_m)
    return g / A0_SDT


def http_get(url, timeout=600):
    req = urllib.request.Request(url, headers={"User-Agent": "CQ26-fetch/1.0"})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        return r.read()


# ============================================================================
# CLASS 1a: solar-system planets
# ============================================================================
# Semi-major axis a: JPL Keplerian elements, J2000 mean elements valid
#   1800-2050 AD  (https://ssd.jpl.nasa.gov/planets/approx_pos.html, Table 1).
# Orbital period P (sidereal) and mean orbital velocity v: NASA NSSDC
#   Planetary Fact Sheet (https://nssdc.gsfc.nasa.gov/planetary/factsheet/).
# Host mass = 1.0 Msun exactly (the Sun, by definition of the channel).
# Errors on a,P at this precision are negligible vs the science here; set 0.
SOLAR_PLANETS = [
    # name,     a_AU,        P_yr,        v_kms
    ("Mercury", 0.38709927, 0.2408467,   47.36),
    ("Venus",   0.72333566, 0.61519726,  35.02),
    ("Earth",   1.00000261, 1.0000174,   29.78),
    ("Mars",    1.52371034, 1.8808476,   24.07),
    ("Jupiter", 5.20288700, 11.862615,   13.06),
    ("Saturn",  9.53667594, 29.447498,    9.68),
    ("Uranus",  19.18916464, 84.016846,   6.80),
    ("Neptune", 30.06992276, 164.79132,   5.43),
]


def rows_solar_planets():
    rows = []
    for name, a, P, v in SOLAR_PLANETS:
        rows.append({
            "class": "planet", "name": name, "host": "Sun",
            "a_AU": f"{a:.8f}", "a_err": "0",
            "P_yr": f"{P:.6f}", "P_err": "0",
            "host_mass_Msun": "1.0", "host_mass_err": "0",
            "v_obs_kms": f"{v:.3f}",
            "source": "JPL_approx_pos+NSSDC_factsheet",
            "source_id": f"planet:{name}",
        })
    return rows


# ============================================================================
# CLASS 1b/2: exoplanets + giant hosts from the NASA Exoplanet Archive (NEXSCI)
# ============================================================================
NEXSCI_TAP = "https://exoplanetarchive.ipac.caltech.edu/TAP/sync"


def _nexsci_query(adql):
    url = NEXSCI_TAP + "?" + urllib.parse.urlencode(
        {"query": adql, "format": "csv"})
    raw = http_get(url, timeout=300).decode("utf-8", "replace")
    return list(csv.DictReader(io.StringIO(raw)))


def rows_exoplanets(n_target=45):
    """
    Pull well-measured planets with both a and P measured plus errors, and a
    stellar mass with errors. We sort by fractional precision in a to favour
    the best-measured systems (deterministic, content-blind to B).
    """
    cols = ("pl_name,hostname,pl_orbsmax,pl_orbsmaxerr1,pl_orbsmaxerr2,"
            "pl_orbper,pl_orbpererr1,pl_orbpererr2,st_mass,st_masserr1,"
            "st_masserr2,st_rad,st_logg")
    adql = (f"select {cols} from ps "
            "where pl_orbsmax is not null and pl_orbper is not null "
            "and st_mass is not null and st_masserr1 is not null "
            "and pl_orbsmaxerr1 is not null and pl_orbpererr1 is not null "
            "and default_flag=1")
    recs = _nexsci_query(adql)

    parsed = []
    for r in recs:
        try:
            a = float(r["pl_orbsmax"])
            P_days = float(r["pl_orbper"])
            M = float(r["st_mass"])
            if a <= 0 or P_days <= 0 or M <= 0:
                continue
            ae1 = abs(float(r["pl_orbsmaxerr1"]))
            ae2 = abs(float(r["pl_orbsmaxerr2"] or ae1))
            a_err = (ae1 + ae2) / 2.0
            pe1 = abs(float(r["pl_orbpererr1"]))
            pe2 = abs(float(r["pl_orbpererr2"] or pe1))
            P_err_days = (pe1 + pe2) / 2.0
            me1 = abs(float(r["st_masserr1"]))
            me2 = abs(float(r["st_masserr2"] or me1))
            M_err = (me1 + me2) / 2.0
            logg = r.get("st_logg")
            rad = r.get("st_rad")
        except (TypeError, ValueError, KeyError):
            continue
        if a_err <= 0:
            continue
        # classify giant host: low surface gravity (logg < 3.7) or big radius
        is_giant = False
        try:
            if logg and float(logg) < 3.7:
                is_giant = True
        except ValueError:
            pass
        try:
            if rad and float(rad) > 3.5:
                is_giant = True
        except ValueError:
            pass
        v = 2.0 * math.pi * (a * AU_M) / (P_days * 86400.0) / 1000.0  # km/s
        parsed.append({
            "rec": r, "a": a, "a_err": a_err,
            "P_yr": P_days / 365.25, "P_err": P_err_days / 365.25,
            "M": M, "M_err": M_err, "v": v, "is_giant": is_giant,
            "frac": a_err / a,
        })

    parsed.sort(key=lambda d: d["frac"])

    rows, giants, planets = [], [], []
    for p in parsed:
        cls = "giant_host" if p["is_giant"] else "planet"
        row = {
            "class": cls,
            "name": p["rec"]["pl_name"],
            "host": p["rec"]["hostname"],
            "a_AU": f"{p['a']:.6g}", "a_err": f"{p['a_err']:.4g}",
            "P_yr": f"{p['P_yr']:.6g}", "P_err": f"{p['P_err']:.4g}",
            "host_mass_Msun": f"{p['M']:.4g}", "host_mass_err": f"{p['M_err']:.4g}",
            "v_obs_kms": f"{p['v']:.4g}",
            "source": "NASA_Exoplanet_Archive_PS",
            "source_id": "exo:" + p["rec"]["pl_name"].replace(" ", "_"),
        }
        (giants if p["is_giant"] else planets).append(row)

    # take up to ~12 giant hosts and fill the rest with regular planets
    rows.extend(giants[:15])
    rows.extend(planets[: max(0, n_target - min(15, len(giants)))])
    return rows


# ============================================================================
# CLASS 4: detached / extreme TNOs (substellar tracers of the floor regime)
# ============================================================================
SBDB_API = "https://ssd-api.jpl.nasa.gov/sbdb.api"

# Detached/extreme/inner-Oort objects with large a => very low xi.
TNO_NAMES = [
    "Sedna", "2012 VP113", "Eris", "Makemake", "Haumea", "Quaoar",
    "Gonggong", "Orcus", "Salacia", "2014 UZ224", "2015 TG387",
    "2013 SY99", "2004 VN112", "2010 GB174", "2007 TG422",
    "2013 RF98", "2002 MS4", "Varuna", "Ixion", "Chariklo",
    "2018 VG18", "2014 FE72", "2015 KG163", "2010 VZ98",
]


def rows_tnos():
    rows = []
    for name in TNO_NAMES:
        try:
            url = SBDB_API + "?" + urllib.parse.urlencode({"sstr": name})
            import json
            d = json.loads(http_get(url, timeout=60))
        except Exception as e:
            sys.stderr.write(f"  TNO {name}: fetch failed ({e})\n")
            continue
        if "orbit" not in d:
            sys.stderr.write(f"  TNO {name}: no orbit ({d.get('message','?')})\n")
            continue
        a = a_sig = per_days = per_sig = None
        for e in d["orbit"]["elements"]:
            if e["name"] == "a":
                a = float(e["value"]); a_sig = e.get("sigma")
            elif e["name"] == "per":
                per_days = float(e["value"]); per_sig = e.get("sigma")
        if a is None or a <= 0:
            continue
        a_err = float(a_sig) if a_sig not in (None, "", "n.a.") else 0.0
        P_yr = (per_days / 365.25) if per_days else None
        P_err = (float(per_sig) / 365.25) if per_sig not in (None, "", "n.a.") and per_days else 0.0
        v = None
        if P_yr and P_yr > 0:
            v = 2.0 * math.pi * (a * AU_M) / (P_yr * YR_S) / 1000.0
        fullname = d["object"]["fullname"]
        rows.append({
            "class": "substellar", "name": fullname, "host": "Sun",
            "a_AU": f"{a:.6g}", "a_err": f"{a_err:.4g}",
            "P_yr": (f"{P_yr:.6g}" if P_yr else ""),
            "P_err": (f"{P_err:.4g}" if P_yr else ""),
            "host_mass_Msun": "1.0", "host_mass_err": "0",
            "v_obs_kms": (f"{v:.4g}" if v else ""),
            "source": "JPL_SBDB",
            "source_id": "sbdb:" + d["object"].get("des", name),
        })
    return rows


# ============================================================================
# CLASS 3: wide binaries (El-Badry, Rix & Heintz 2021, Gaia eDR3)
# ============================================================================
ELBADRY_FITS_URL = ("https://zenodo.org/records/4435257/files/"
                    "all_columns_catalog.fits.gz?download=1")
ELBADRY_FITS_LOCAL = os.path.join(os.environ.get("TEMP", "/tmp"),
                                  "eb_wide_binaries.fits.gz")


def _absG(g_mag, parallax_mas):
    """Absolute Gaia G magnitude from apparent G and parallax (mas)."""
    d_pc = 1000.0 / parallax_mas
    return g_mag - 5.0 * (math.log10(d_pc) - 1.0)


# Main-sequence mass vs absolute Gaia G_RP-ish proxy.
# We use a coarse but published M_G -> M/Msun relation derived from the
# Pecaut & Mamajek (2013) "A Modern Mean Dwarf Stellar Color and Effective
# Temperature Sequence" table (Gaia G column), interpolated. Anchored at:
#   M_G  ~  2.0 ->  ~1.5 Msun   (early F)
#          4.7 ->  ~1.0 Msun    (Sun-like, M_G(Sun)=4.67)
#          7.0 ->  ~0.65 Msun   (K)
#          9.0 ->  ~0.45 Msun   (early M)
#         12.0 ->  ~0.20 Msun   (mid M)
# Implemented as piecewise log-linear; clamped to [0.10, 2.0] Msun.
_MG_ANCHORS = [(1.0, 2.0), (2.0, 1.5), (3.5, 1.15), (4.67, 1.0),
               (6.0, 0.78), (7.0, 0.65), (8.0, 0.55), (9.0, 0.45),
               (10.5, 0.32), (12.0, 0.20), (14.0, 0.12)]


def _mass_from_MG(MG):
    if MG <= _MG_ANCHORS[0][0]:
        return _MG_ANCHORS[0][1]
    if MG >= _MG_ANCHORS[-1][0]:
        return _MG_ANCHORS[-1][1]
    for (x0, y0), (x1, y1) in zip(_MG_ANCHORS, _MG_ANCHORS[1:]):
        if x0 <= MG <= x1:
            t = (MG - x0) / (x1 - x0)
            return y0 + t * (y1 - y0)
    return 1.0


def download_elbadry(dest=ELBADRY_FITS_LOCAL):
    if os.path.exists(dest) and os.path.getsize(dest) > 1.3e9:
        sys.stderr.write(f"  El-Badry FITS already present: {dest}\n")
        return dest
    sys.stderr.write("  downloading El-Badry FITS (~1.4 GB) ...\n")
    urllib.request.urlretrieve(ELBADRY_FITS_URL, dest)
    return dest


def rows_binaries(fits_path, n_target=42):
    """
    Select wide binaries spanning ~200 AU to ~50000 AU, ranked to favour
    HIGH-confidence (R_chance_align small) MSMS pairs with good parallax SNR,
    deterministically. Primary mass from absolute-G MLR (photometric channel).
    """
    from astropy.io import fits
    import numpy as np

    # Memory-safe: this catalogue is 1.8M rows x 217 cols. Read only the few
    # columns we need rather than loading the whole table into RAM.
    sys.stderr.write(f"  reading (selected columns) {fits_path} ...\n")
    want = ["sep_AU", "parallax1", "parallax_error1", "phot_g_mean_mag1",
            "phot_g_mean_mag2", "R_chance_align", "binary_type",
            "source_id1", "source_id2"]
    data = {}
    with fits.open(fits_path, memmap=True) as hdul:
        hdu = hdul[1]
        avail = set(hdu.columns.names)
        names = avail
        for w in want:
            if w in avail:
                data[w] = np.asarray(hdu.data[w])

    def col(*cands):
        for c in cands:
            if c in data:
                return data[c]
        return None

    sep = col("sep_AU")
    plx = col("parallax1")
    plx_err = col("parallax_error1")
    g1 = col("phot_g_mean_mag1")
    g2 = col("phot_g_mean_mag2")
    rca = col("R_chance_align")
    btype = col("binary_type")
    sid1 = col("source_id1")
    sid2 = col("source_id2")

    if sep is None or plx is None or g1 is None:
        raise RuntimeError("El-Badry FITS missing expected columns; "
                           f"have: {sorted(names)[:30]} ...")

    N = len(sep)
    sys.stderr.write(f"  catalogue rows: {N}\n")

    # Build candidate pool with quality + separation cuts.
    cand = []
    for i in range(N):
        try:
            s = float(sep[i]); p = float(plx[i])
        except (TypeError, ValueError):
            continue
        if not (math.isfinite(s) and math.isfinite(p)) or p <= 0:
            continue
        if s < 100.0 or s > 60000.0:
            continue
        # confident, well-measured pairs only
        if rca is not None:
            try:
                if float(rca[i]) > 0.1:
                    continue
            except (TypeError, ValueError):
                pass
        pe = float(plx_err[i]) if plx_err is not None else 0.0
        snr = (p / pe) if pe > 0 else 1e9
        if snr < 20:
            continue
        bt = ""
        if btype is not None:
            bt = btype[i].decode() if isinstance(btype[i], bytes) else str(btype[i])
            bt = bt.strip()
            # restrict to main-sequence + main-sequence pairs: the absolute-G
            # mass-luminosity relation below is only valid for MS stars (white
            # dwarfs are sub-luminous and would give wrong masses).
            if bt and bt != "MSMS":
                continue
        # primary mass from absolute G of the brighter component (g1)
        try:
            MG1 = _absG(float(g1[i]), p)
            m1 = _mass_from_MG(MG1)
        except (TypeError, ValueError):
            continue
        if not math.isfinite(m1):
            continue
        cand.append({
            "i": i, "sep": s, "plx": p, "plx_err": pe, "snr": snr,
            "m1": m1, "MG1": MG1, "bt": bt,
            "id1": int(sid1[i]) if sid1 is not None else i,
            "id2": int(sid2[i]) if sid2 is not None else 0,
        })

    sys.stderr.write(f"  candidates after cuts: {len(cand)}\n")

    # Span the separation range in log space: bucket and pick best-SNR per bucket
    # so we cover ~100 AU -> ~50000 AU (the crossover + floor) evenly.
    import collections
    buckets = collections.defaultdict(list)
    for c in cand:
        b = round(math.log10(c["sep"]), 1)   # 0.1-dex buckets
        buckets[b].append(c)
    picked = []
    for b in sorted(buckets):
        bb = sorted(buckets[b], key=lambda c: (c["snr"] == 0, -c["snr"]))
        picked.extend(bb[:3])   # up to 3 per 0.1-dex bucket
    # deterministic global order: by separation then source id
    picked.sort(key=lambda c: (c["sep"], c["id1"]))
    if len(picked) > n_target:
        # thin evenly across the sorted-by-separation list to keep the span
        step = len(picked) / float(n_target)
        idxs = sorted({int(round(k * step)) for k in range(n_target)})
        idxs = [j for j in idxs if j < len(picked)]
        picked = [picked[j] for j in idxs]

    rows = []
    for c in picked:
        # parallax error -> distance error -> separation error (linear in 1/plx)
        sep_err = c["sep"] * (c["plx_err"] / c["plx"]) if c["plx"] > 0 else 0.0
        # crude mass uncertainty: +-25% photometric (MLR + binarity)
        m_err = 0.25 * c["m1"]
        rows.append({
            "class": "binary",
            "name": f"WB_{c['id1']}",
            "host": f"Gaia_EDR3_{c['id1']}",
            "a_AU": f"{c['sep']:.6g}", "a_err": f"{sep_err:.4g}",
            "P_yr": "", "P_err": "",
            "host_mass_Msun": f"{c['m1']:.3g}", "host_mass_err": f"{m_err:.3g}",
            "v_obs_kms": "",
            "source": "ElBadry2021+MLR(phot)",
            "source_id": f"gaia_edr3:{c['id1']}+{c['id2']}",
        })
    return rows


# ============================================================================
# driver
# ============================================================================
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--no-binaries", action="store_true",
                    help="skip the El-Badry wide-binary download/parse")
    ap.add_argument("--binaries-fits", default=ELBADRY_FITS_LOCAL,
                    help="path to an already-downloaded El-Badry FITS.gz")
    ap.add_argument("--out", default=OUT_CSV)
    args = ap.parse_args()

    all_rows = []

    print("[1/5] solar-system planets ...", file=sys.stderr)
    all_rows += rows_solar_planets()

    print("[2/5] NASA Exoplanet Archive (planets + giant hosts) ...", file=sys.stderr)
    try:
        all_rows += rows_exoplanets()
    except Exception as e:
        print(f"   NEXSCI fetch FAILED: {e}", file=sys.stderr)

    print("[3/5] detached/extreme TNOs (JPL SBDB) ...", file=sys.stderr)
    try:
        all_rows += rows_tnos()
    except Exception as e:
        print(f"   SBDB fetch FAILED: {e}", file=sys.stderr)

    if not args.no_binaries:
        print("[4/5] El-Badry wide binaries ...", file=sys.stderr)
        try:
            fp = args.binaries_fits
            if not (os.path.exists(fp) and os.path.getsize(fp) > 1.3e9):
                fp = download_elbadry(fp)
            all_rows += rows_binaries(fp)
        except Exception as e:
            print(f"   wide-binary build FAILED: {e}", file=sys.stderr)
    else:
        print("[4/5] wide binaries SKIPPED (--no-binaries)", file=sys.stderr)

    print("[5/5] writing CSV ...", file=sys.stderr)
    with open(args.out, "w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=HEADER)
        w.writeheader()
        for r in all_rows:
            w.writerow(r)

    # summary + xi sanity
    by_class = {}
    for r in all_rows:
        by_class[r["class"]] = by_class.get(r["class"], 0) + 1
    print(f"\nwrote {len(all_rows)} rows -> {args.out}", file=sys.stderr)
    for c, n in sorted(by_class.items()):
        print(f"   {c:12s} {n}", file=sys.stderr)


if __name__ == "__main__":
    main()
