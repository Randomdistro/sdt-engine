# Cassini SCE1 fetch status — 2026-08-09

**Script:** `fetch_cassini_sce1.ps1` (resume-safe; skips complete files; rejects truncated product binaries)  
**Log:** `FETCH_LOG_RESUME_2026-08-07.txt` (overwritten each resume)  
**Terminal job:** background PID from resume at 2026-08-08 ~19:56 local

## Complete (science path for GOM25 D4)

| Class | Location | Status |
|---|---|---|
| Volume indexes / aareadme / catalog / document / ancillary | `raw/cassini_sce1/cors_0021–0028/` | Present |
| TDF + labels | `raw/cassini_sce1/.../tdf/` | **Complete for DOY 157–185** (DOY 186 has no TDF in PDS index) |
| ODF + labels | `raw/cassini_sce1/.../odf/` | **Complete for DOY 157–185** (DOY 186 has no ODF in PDS index) |
| PD1/PD2, 158, 515 (non-large) | under day dirs | Fetched in main pass; two DOY-182 `.515` failures re-downloaded 2026-08-09 |
| Truncated DOY-160 `k252v0.tdf` | repaired | Re-fetched 32,643,072 B |

Sparse days with one TDF/ODF pair (165, 168–171, 179, 182) match the cumulative index (one station product).

## In progress

| Class | Location | Notes |
|---|---|---|
| RSR binaries | `C:\sdt-data\cassini_sce1\...\rsr\` | Large; labels in-repo under `raw/.../rsr/` |
| TLM binaries | `C:\sdt-data\cassini_sce1\...\tlm\` | Same routing |

As of last check (~2026-08-09 03:41): RSR through DOY **160**, ~2.0 GB external. Pace ≈ 1 DOY / 40–50 min → remaining DOY 161–186 estimated **many hours**.

## Other solar_propagation raw products

Already frozen under `raw/` (Horizons 2024/2025, HARPS, IAU/Haberreiter, Fomalont, NRAO BF080 metadata, TRK-2-25 unpack). See `MANIFEST.md` (to be regenerated with SHA-256 after RSR pass completes).
