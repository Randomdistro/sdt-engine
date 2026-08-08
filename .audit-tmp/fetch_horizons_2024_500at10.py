import hashlib
import pathlib
import urllib.parse
import urllib.request

q = {
    "format": "text",
    "COMMAND": "3",
    "OBJ_DATA": "YES",
    "MAKE_EPHEM": "YES",
    "EPHEM_TYPE": "VECTORS",
    "CENTER": "500@10",
    "START_TIME": "2024-01-01",
    "STOP_TIME": "2025-01-01",
    "STEP_SIZE": "14 days",
    "VEC_TABLE": "2",
    "OUT_UNITS": "KM-S",
    "CSV_FORMAT": "YES",
    "REF_PLANE": "ECLIPTIC",
}
url = "https://ssd.jpl.nasa.gov/api/horizons.api?" + urllib.parse.urlencode(q)
print("URL", url)
data = urllib.request.urlopen(url, timeout=120).read()
text = data.decode("utf-8", "replace")
for line in text.splitlines():
    if "Center body" in line or "Target body" in line or "INPUT ERROR" in line:
        print(line.strip())
out = pathlib.Path("Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2024.csv")
# Preserve any non-error prior content by writing only on success
if "Sun (10)" in text and "$$SOE" in text and len(data) > 1000:
    out.write_bytes(data)
    print("SAVED bytes", len(data), "sha256", hashlib.sha256(data).hexdigest())
else:
    err = pathlib.Path("Datasets/solar_propagation_2026-08/raw/jpl_horizons_API_ERROR_2024_latest.txt")
    err.write_bytes(data)
    print("NOT SAVED to science path; wrote error stub", err, "bytes", len(data))
    print(text[:400])
