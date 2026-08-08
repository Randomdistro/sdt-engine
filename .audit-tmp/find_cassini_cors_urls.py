import re
import urllib.request

UA = {"User-Agent": "sdt-engine-research/1.0"}

urls = [
    "https://atmos.nmsu.edu/data_and_services/atmospheres_data/Cassini/rss.html",
    "https://atmos.nmsu.edu/PDS/data/",
    "https://pds-geosciences.wustl.edu/missions/cassini/",
    "https://pds-geosciences.wustl.edu/cassini/",
]

for u in urls:
    print("===", u)
    try:
        req = urllib.request.Request(u, headers=UA)
        with urllib.request.urlopen(req, timeout=40) as r:
            body = r.read(200_000).decode("utf-8", "replace")
        print("status ok bytes", len(body))
        hrefs = re.findall(r'href=["\']([^"\']+)["\']', body, re.I)
        keep = [
            h
            for h in hrefs
            if any(x in h.lower() for x in ("cors", "sce1", "rss", "odf", "raw"))
        ]
        for h in keep[:50]:
            print(" ", h)
        if "CORS_0021" in body:
            print("  contains CORS_0021")
    except Exception as e:
        print(type(e).__name__, e)
