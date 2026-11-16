import datetime
import hashlib
import json
import os
import subprocess

repo = r"C:\Users\Jimmi\OneDrive\Desktop\sdt-engine"
out_dir = os.path.join(repo, "Investigations", "SDT_Loading_EC_Reseating_Neutrino_Coupling")


def run(*args):
    return subprocess.run(args, cwd=repo, capture_output=True, text=True, encoding="utf-8").stdout


def sha(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


audited = [
    "Engine/include/sdt/laws.hpp",
    "Engine/include/sdt/neutrino.hpp",
    "Release/SDT_Celestial_Three_Body_Solver/src/occlusion_nbody.cpp",
    "Release/SDT_Celestial_Three_Body_Solver/src/solver.cpp",
    "Release/SDT_Celestial_Three_Body_Solver/QUALIFICATION_MANIFEST.json",
    "Release/HTML_SDT_Website/js/traction-gear-engine.js",
    "Investigations/05_Nuclear_Physics/pack_nucleus.py",
    "Investigations/HUNTER_PROTOCOL.md",
    "Investigations/PROMPT_EXECUTION_PROTOCOL.md",
    "Investigations/PERFECT_PROMPT_TEMPLATE.md",
    "Audits/atomica_n82_fission_stocktake.md",
    "Investigations/05_Nuclear_Physics/NP18_Be7BEC_Flux_Resonator/NP18_VERDICT.md",
]
audited_dirs = [
    "Investigations/05_Nuclear_Physics/NSEQ16_Perfect_Traction_Gear_Engine",
    "Investigations/05_Nuclear_Physics/NSEQ17_Light_Nucleus_Wake_Mesh",
    "Investigations/05_Nuclear_Physics/NSEQ18_Universal_Interstitial_Sequencer",
    "Investigations/05_Nuclear_Physics/NP33_Traction_Assembly",
    "Investigations/05_Nuclear_Physics/NP04_Neutron_Genesis_to_Tritium",
    "Investigations/01_Foundations_and_Lattice_Mechanics/FLM15_Influx_Phase_Resistance_Ratio",
    "Investigations/01_Foundations_and_Lattice_Mechanics/FLM15_Casimir_as_Relay_Exclusion",
]
files = {}
for p in audited:
    full = os.path.join(repo, p)
    files[p] = {"sha256": sha(full), "bytes": os.path.getsize(full)}
for d in audited_dirs:
    full = os.path.join(repo, d)
    for root, dirs, names in os.walk(full):
        dirs[:] = [x for x in dirs if x != "__pycache__"]
        for n in sorted(names):
            fp = os.path.join(root, n)
            rel = os.path.relpath(fp, repo).replace("\\", "/")
            files[rel] = {"sha256": sha(fp), "bytes": os.path.getsize(fp)}

manifest = json.load(open(os.path.join(repo, "Release/SDT_Celestial_Three_Body_Solver/QUALIFICATION_MANIFEST.json"), encoding="utf-8"))
laws_now = files["Engine/include/sdt/laws.hpp"]["sha256"]
porcelain = [l for l in run("git", "status", "--porcelain").splitlines() if l.strip()]
dirty = [{"status": l[:2].strip(), "path": l[3:]} for l in porcelain]

freeze = {
    "schema": "sdt-source-freeze-1.0",
    "investigation": "SDT_Loading_EC_Reseating_Neutrino_Coupling",
    "frozen_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(timespec="seconds"),
    "repository": repo,
    "git": {
        "head": run("git", "rev-parse", "HEAD").strip(),
        "branch": run("git", "branch", "--show-current").strip(),
        "head_subject": run("git", "log", "-1", "--format=%s").strip(),
        "dirty_entry_count": len(dirty),
        "dirty_entries_note": "All dirty entries are uncommitted work of the 2026-10-03 session (PPT16, APS10, FLM15-Casimir, NP11, APS09, APS08 records and tools) plus this investigation's own directory; none is in an audited canonical source.",
        "dirty_entries": dirty,
        "engine_or_release_files_dirty": [d for d in dirty if d["path"].startswith(("Engine/", "Release/"))],
    },
    "toolchains": {
        "native": "MSVC 19.44.35223 x64 (VS 2022 Build Tools), /std:c++20 /EHsc /O2",
        "python": "3.13.3 (python) / 3.13.14 (python3)",
        "git": "2.46.0.windows.1",
    },
    "qualification_currency": {
        "manifest": "Release/SDT_Celestial_Three_Body_Solver/QUALIFICATION_MANIFEST.json",
        "manifest_generated_utc": manifest["generated_utc"],
        "manifest_native_toolchain": manifest["native_toolchain"],
        "manifest_laws_sha256": manifest["laws_sha256"],
        "current_laws_sha256": laws_now,
        "laws_hash_matches_manifest": manifest["laws_sha256"] == laws_now,
        "status": "CURRENT" if manifest["laws_sha256"] == laws_now else "STALE: laws.hpp has changed since the recorded qualification; historical runtime gates are not associated with current code until re-qualified",
    },
    "spec_sha256": sha(os.path.join(out_dir, "PROMPT.md")),
    "audited_files": files,
}
with open(os.path.join(out_dir, "SOURCE_FREEZE.json"), "w", encoding="utf-8") as f:
    json.dump(freeze, f, indent=2)
print("files hashed:", len(files))
print("dirty entries:", len(dirty), "| engine/release dirty:", len(freeze["git"]["engine_or_release_files_dirty"]))
print("qualification:", freeze["qualification_currency"]["status"][:60])
