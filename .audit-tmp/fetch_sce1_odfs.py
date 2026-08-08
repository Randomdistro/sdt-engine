"""Attempt to fetch priority SCE1 ODF products from common PDS mirrors."""
from __future__ import annotations

import hashlib
import pathlib
import urllib.request

TARGETS = [
    "SCE1_157/ODF/C32EASC2002_157_0000XMMMV0.ODF",
    "SCE1_157/ODF/C32EASC2002_157_0000XMMMV0.LBL",
    "SCE1_158/ODF/C32EASC2002_158_0000K252V0.ODF",
    "SCE1_158/ODF/C32EASC2002_158_0000K252V0.LBL",
]
BASES = [
    "https://atmos.nmsu.edu/pdsd/archive/data/co-ss-rss-1-sce1-v1.0/cors_0021/",
    "https://atmos.nmsu.edu/pdsd/archive/data/co-ss-rss-1-sce1-v1.0/CORS_0021/",
    "https://pds-geosciences.wustl.edu/cassini/cors_0021/",
    "https://pds-geosciences.wustl.edu/cassini/CO-SS-RSS-1-SCE1-V1.0/cors_0021/",
]
OUT = pathlib.Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1_multiday")
OUT.mkdir(parents=True, exist_ok=True)


def main() -> int:
    saved = 0
    for base in BASES:
        print("BASE", base)
        for rel in TARGETS:
            url = base + rel
            out = OUT / rel.replace("/", "_")
            try:
                with urllib.request.urlopen(url, timeout=60) as resp:
                    data = resp.read()
                if len(data) < 1000:
                    print("  tiny", rel, len(data))
                    continue
                out.write_bytes(data)
                print(
                    "  SAVED",
                    out.name,
                    len(data),
                    hashlib.sha256(data).hexdigest()[:16],
                )
                saved += 1
            except Exception as exc:
                print("  FAIL", rel, type(exc).__name__, str(exc)[:100])
        if saved:
            break
    print("saved_count", saved)
    return 0 if saved else 1


if __name__ == "__main__":
    raise SystemExit(main())
