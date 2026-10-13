# CQ — legacy CQ-numbered corpus (recovered)

> **J. C. Harvey, Melbourne — 2026-07-30.** Recovered directly from git history in
> the main session. Holding folder for CQ-era investigation corpora, kept under
> their original CQ names (the CQ numbering scheme was retired in favour of domain
> codes; the *data* keeps its original identity — legacy files are not renamed).

## CQ26_Universal_Drafting_Crossover

The universal drafting-crossover corpus. Now continued under the domain code
**APS03** (`Investigations/04_Atomic_Physics_and_Spectroscopy/APS03_Universal_Drafting_Crossover/`).

**Recovery.** The folder was deleted in commit `2672d41` ("yep, the introduction of
the old de rerum") and never restored. Recovered byte-exact with
`git checkout 2672d41^ -- Investigations/CQ26_Universal_Drafting_Crossover`
(git's own checkout, not a shell re-write — a PowerShell `Out-File` restore was
tried first and rejected because it added a BOM and rewrote line endings).

**Contents (14 files):**

| File | Role |
| --- | --- |
| `INVESTIGATION.md` | the CQ26 methodology record — the file that had no surviving copy anywhere in the working tree |
| `PROMPT.md` | CQ26-era spec (25.5 kB; the APS03 folder carries a later 27.7 kB revision) |
| `cq26_corpus.csv` | **the corpus** — 3,521 rows, scales A/B/C/D |
| `cq26_output.txt` | original run output |
| `cq26_provenance.txt` | source provenance for the corpus rows |
| `cq26_drafting_crossover.cpp` | the CQ26-era tool |
| `fetch_nuclear.py`, `fetch_stellar.py` | corpus builders |
| `mass_1.mas20.txt`, `nubase_4.mas20.txt`, `nuclear_binding.csv` | AME/NUBASE nuclear inputs |
| `stellar_orbits.csv`, `stellar_fetch.log` | stellar inputs + fetch log |
| `__pycache__/fetch_nuclear.cpython-313.pyc` | generated Python bytecode (restored with the tree; deletable, left untouched pending your call) |

### Corpus continuity — verified, not assumed

The corpus data was **never lost**. Line-by-line comparison (`Compare-Object`,
2026-07-30):

```text
historical cq26_corpus.csv   3,521 rows   header: scale,class,type,id,xi,B,sigmaB
current    aps03_corpus.csv  3,521 rows   header: scale,class,type,id,xi,B,sigmaB
differing lines: 0
```

`aps03_corpus.csv` **is** the CQ26 corpus, renamed. Nothing was reconstructed or
re-fetched; the recovered file is the original.

### Open discrepancy — doc cites 3,443 rows, corpus has 3,520

`INVESTIGATION.md` §header states the corpus is 3,443 rows. The restored corpus
has **3,520 data rows** (A=37, B=77, C=3012, D=394). The 77-row difference
equals the B-scale count exactly, which suggested the B scale was appended after
the document was written — **that was tested against git and refuted**: the
earlier commit `5669a16` already carries all four scales at 3,520 rows
(A=37, B=77, C=3012, D=394), identical to the deletion-time state.

So the 3,443 figure corresponds to **no committed corpus state**. It is either a
pre-commit working state that was never versioned, or a stale number in the
document. Flagged, not reconciled — anyone re-running CQ26 should treat the
corpus (3,520 rows) as authoritative and the doc's row count as unverified.
Note also `INVESTIGATION.md` claims "EXECUTED (4 scales)" while 3,443 = A+C+D
(three scales), a second reason to trust the data over the header.

### `snapshot_509row_pre_classC/cq26_corpus.csv`

A second `cq26_corpus.csv` was found loose in the APS03 folder at 509 rows and
moved here (original filename preserved; the subfolder states its role). It is an
**earlier snapshot**, not a truncation: scales A=37, B=77, D=394 match the full
corpus exactly, and all 3,012 class-C rows are absent. Retained as a dated
intermediate state; superseded by the full corpus for any analysis.

## Scope note — what was NOT moved here

Other `cq*`-named files exist in the tree and were deliberately left in place:
they are **live tools in their working homes**, not CQ-era corpus material, and
relocating them would break their investigations or distribution bundles.

- `Investigations/01_.../FLM08_Lattice_Structure_Geometry/cq53_lattice_structure.cpp` / `.html` — FLM08's own tool
- `Investigations/02_.../PPT08A_.../cq35_results.txt` — PPT08A's own output
- `Hubble/tools/cq18a_solar_zdecomp.cpp` — part of the Hubble zk² suite
- `Release/JPL_SPHEREx_H0_Correction/`, `Release/JPL_SSD_Orbital_Ephemeris/`, `Release/NEXSCI_Exoplanet_Solver/` — self-contained distribution bundles
- `docs/cq06-eclipse.html`, `Release/HTML_SDT_Website/cq06-eclipse.html` — published website pages (`docs/` is a byte mirror)
- `Investigations/02_.../PPT08A_.../build_cq35/` — generated CMake/MSVC build output

Say the word if any of those should follow CQ26 into this folder.
