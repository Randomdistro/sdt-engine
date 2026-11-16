# Chapter 5 — pre-registration of the worked-example instrument

Registered 2026-11-03, before `Textbook/examples/ch05_operator_law_map.py` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The map from the constitution's six operators, nine axioms and seventeen theorems (`Theory/00_Ruleset.md`) to the engine's six laws and its theorem numbering (`Engine/include/sdt/laws.hpp`), and the numbering of `Laws/SDT_Complete_Laws.md`. The instrument reads the three files and reports structure; it computes no physics. Its criteria are statements about the sources, registered as predictions before the files were scanned by the tool.

## Instrument validation

| id | known answer | tolerance |
|---|---|---|
| V1 | the token scanner applied to a fixed test string `"T1/T10 x T_CMB y NT2 T18, T3-T4 T5–T7"` finds the theorem tokens `T1`, `T10`, `T18`, `T3`, `T4`, `T5`, `T7` and no others (`T_CMB`, `NT2` excluded) | exact |
| V2 | the range parser applied to `"(Theorems T10–T17)"`, `"(Theorems T1-T2)"` and `"Theorem T18"` returns $(10,17)$, $(1,2)$ and $(18,18)$ | exact |

## Criteria (predictions about the sources)

| id | prediction | rejection class populated? |
|---|---|---|
| C1 | the Ruleset has exactly 6 operators, 9 axioms (R1–R6, M1–M3) and 17 theorems (T1–T17, consecutive) | yes — a different count rejects |
| C2 | the engine's header banner assigns theorem ranges Law I: T1–T2, Law III: T3–T4, Law IV: T5–T7, Law V: T10–T17, Law VI: T18, and states no theorem for Law II | yes |
| C3 | the namespaces `law_I`…`law_VI` and the banners `LAW I`…`LAW VI` appear in this order in `laws.hpp` | yes |
| C4 | `T18` occurs in `laws.hpp` and is absent from the Ruleset's theorem table | yes — a Ruleset row T18 rejects |
| C5 | no theorem number 8 or 9 lies inside any banner range of C2 (so T8 and T9 are carried outside the banners) | yes |
| C6 | `laws.hpp` defines no function named `gravitational_time_dilation` and defines `depth_closure::clock_rate`; the Ruleset's T16 row names the form with a square root | yes — a surviving square-root function would reject the supersession recorded in Chapter 3 |

Reported, not criteria: the number of `T<n>` tokens in `laws.hpp` per theorem number and per top-level namespace; the list of theorem headings of the Complete Laws paper; the theorem names of the Ruleset table.

## Single-pass rule

All criteria are evaluated in one run. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Run line

`bash Textbook/tools/py_run.sh ch05_operator_law_map` (isolated interpreter, output saved as the next numbered run)

## Record of run 1 (2026-11-03)

Run 1 (`ch05_run1_output.txt`) evaluated V1, V2 and C1–C6 (all consistent with the predictions) and then stopped in the reporting section with a `UnicodeEncodeError`: the isolated interpreter (`python -I`) ignores `PYTHONIOENCODING`, so standard output used the Windows code page and the arrow character in a Ruleset theorem name could not be written. This is an instrument fault in the output path, not a result. The script now sets standard output to UTF-8 itself. No criterion was changed. Run 2 is the run of record.
