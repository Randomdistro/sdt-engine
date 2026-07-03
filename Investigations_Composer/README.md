# Investigations — Composer (Cursor) executions

Parallel investigation tree for runs executed by **Cursor Composer**, kept separate from the canonical `Investigations/` tree (Claude Code and manual work).

Each folder mirrors the main investigations layout: `PROMPT.md`, tool `.cpp`, `RUN_LOG.md`, results, derivation, and article/verdict as produced by the run.

**Engine dependency:** all tools `#include <sdt/laws.hpp>` from `Engine/include/` (paths relative to repo root).

---

## Executions

| Section | Investigation | Status |
|---------|---------------|--------|
| 15 · Optics and Photonics | [OP01 — Refraction and Dispersion as Spation Gradient Index](15_Optics_and_Photonics/OP01_Refraction_and_Dispersion_as_Spation_Gradient_Index/) | Executed 2026-06-27 · Class C — analytic notes pending a real compile — no compiler was run |
| 03 · Electromagnetism and Charge | [EMC04 — Electropause SDT-Native](03_Electromagnetism_and_Charge/EMC04_Electropause_SDT_Native/) | analytic notes pending a real compile — no compiler was run |

---

## Build (standalone tool pattern)

From repo root, inside an investigation folder:

```bash
g++ -std=c++20 -IEngine/include Investigations_Composer/15_Optics_and_Photonics/OP01_Refraction_and_Dispersion_as_Spation_Gradient_Index/op01_gradient_index.cpp -o op01
```

Do not merge Composer verdicts into `Investigations/` without explicit review.
