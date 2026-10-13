# NP40 — Assessment, P0–P1 (2026-10-05)

**Classification:** `NP40_ACCESSIBILITY_DEFINED__ALT_GRAMMAR_GATE_NOT_MET_PROTON_RICH_LIGHT`<br>
**Run class:** direct. Tool `np40_accessibility.py`; output `np40_results.txt`. Pre-registered in `RUN_LOG.md` before the run. P2 (clock candidates) and P3 not run. **Canon edits:** none; **fitted parameters:** 0.

## P0 accessibility (NUBASE2020 ground states, mass excess in the file)
- 3558 ground-state rows; 1060 list EC or B+ with a ground-state daughter present; 927 have both masses measured (no systematics flag). **Q_EC > 0 for all 927** (as it must be for a listed EC/B+ mode; this checks the parse, not physics). Instrument checks: Be-7 861.9 keV, Na-22 2843.3 keV against literature-memory values 861.8 and 2842.0 (VERIFY).
- Correction to the continuation audit F3: "0 of 213 have Q_EC > 0" described the website table (stable and long-lived nuclides only). Against the full NUBASE2020 table accessibility is defined for 927 measured EC/B+ parents.

## P1 grammar test (alternate EC grammar n_t = A−2Z+1, n_d = 3Z−A−3, both ≥ 0)
| Set | n | alt valid | std valid |
|---|---|---|---|
| EC/B+ parents, Z ≥ 2, measured | 927 | 871 (94.0%) | 839 (90.5%) |
| All ground-state cells (null) | 3550 | 3237 (91.2%) | 3214 (90.5%) |

- **Gate (≤ 1% invalid): not met** — 56 invalid (6.0%). All 56 have N − Z between −4 and −2, Z = 5–30, A ≤ 58 (e.g. B-8, C-9, C-10, N-12, O-13, O-14). For Z < 20 only 45.3% of EC parents are valid (24 of 53); for Z ≥ 20, 96.9% (847 of 874).
- Shared-input note (registered in advance): validity reduces to inequalities on N − Z and Z. The 94% is mostly the chart's shape (91% of all cells are valid), so it is not independent evidence about EC.
- Reading: the grammar has no decomposition for proton-rich nuclei with N < Z − 1. This is a coverage limit of the grammar as written, not a failure of any one nuclide, and the first result NP40 reports.

## Next
- The 56 invalid cases lie outside the grammar's stated domain (N ≥ Z − 1); the ATOMICUS rules document no decomposition for them. Any extension (for example a proton remainder on a He-3 core) would be a new decomposition, and the grammar is constitutional: it is **propose-only** and is not tested here.
- P2 (clock ambiguity, following NP11's B_req census) needs a loading input that PM08 has not defined; it can run on supplied loadings and is the next executable step.
