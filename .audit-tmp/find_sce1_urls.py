import re
import urllib.request

urls = [
    "https://atmos.nmsu.edu/data_and_services/atmospheres_data/Cassini/rss.html",
    "https://atmos.nmsu.edu/data_and_services/atmospheres_data/Cassini/rss-raw.html",
    "https://pds-atmospheres.nmsu.edu/data_and_services/atmospheres_data/Cassini/rss.html",
    "https://atmos.nmsu.edu/pdsd/archive/data/",
]
for u in urls:
    try:
        data = urllib.request.urlopen(u, timeout=45).read().decode("utf-8", "replace")
        print("OK", u, "len", len(data))
        links = re.findall(r'href=["\']([^"\']+)["\']', data, re.I)
        for m in links:
            low = m.lower()
            if "cors_0021" in low or "sce1" in low or "rss-1-sce1" in low:
                print(" ", m)
    except Exception as e:
        print("FAIL", u, type(e).__name__, e)
