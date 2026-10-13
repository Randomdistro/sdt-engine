#!/usr/bin/env python3
"""
Batch-upgrade Investigations/**/PROMPT.md to PERFECT_PROMPT_TEMPLATE v2026-06-27.

- Adds standard inheritance header
- Appends §⑩ Adaptive Execution Protocol if missing
- Adds dual-verdict note + RUN_LOG to outputs if missing
- Preserves existing body content (non-destructive append/merge)

Usage (from repo root):
  python Investigations/tools/prompt_upgrade.py
  python Investigations/tools/prompt_upgrade.py --dry-run
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
INV = ROOT / "Investigations"

STANDARD_HEADER = """> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩)."""

SECTION_10_MARKER = "## ⑩ Adaptive Execution Protocol"
DUAL_VERDICT_MARKER = "dual verdict"
RUN_LOG_MARKER = "RUN_LOG.md"

DOMAIN_ENGINE_HINTS = {
    "01_Foundations": "FLM08 `lattice_structure.hpp`, FLM02/FLM05 relay mechanics",
    "02_Particle": "law_VI winding, bridge::k_*, PPT01 equilibrium",
    "03_Electromagnetism": "law_III occlusion, coulomb_identity, EMC01 transfer",
    "04_Atomic": "atomic::, measured::R_inf, electropause / APS01",
    "05_Nuclear": "NP01 grammar, law_III nuclear occlusion, ATOMICUS rules",
    "06_Gravitation": "bridge::koppa_*, depth_closure::, no G/M",
    "07_Cosmology": "cosmology.hpp, z_spectral, CR10 cubic rung",
    "08_Galactic": "galactic.hpp, GD01 eclipse saturation",
    "09_Stellar": "law_I luminosity, SAR02 mode counting",
    "10_Fluid": "FLM02 GPI, law_I P_conv, FD02 viscosity handoff",
    "11_Thermodynamics": "measured::k_B, TD01 microstate counting",
    "12_Condensed": "Law III drag, CM06 R_K = h/e²",
    "13_Quantum": "standing wakes, no ψ; compare atomic:: only after native phase",
    "14_Plasma": "PM01 circulation, c = l_P/t_P, transverse relay",
    "15_Optics": "depth_closure:: n=1/(1-z), Fermat least relay-time",
    "16_Chemistry": "EMC04 electropause, CH01 wake balance, no MO/LCAO",
}


def investigation_id(path: Path) -> str:
    name = path.parent.name
    m = re.match(r"^([A-Z]{2,4}\d+[A-Z]?)", name)
    return m.group(1) if m else name.split("_")[0]


def domain_key(path: Path) -> str:
    parts = path.relative_to(INV).parts
    if not parts:
        return "unknown"
    top = parts[0]
    for k in DOMAIN_ENGINE_HINTS:
        if k.split("_")[0] in top or k in top:
            return k
    return top


def extract_title(text: str) -> str:
    for line in text.splitlines():
        if line.startswith("# "):
            return line[2:].strip()
    return "Investigation"


def has_section_10(text: str) -> bool:
    return SECTION_10_MARKER in text or "### ⑩" in text


def has_dual_verdict(text: str) -> bool:
    return DUAL_VERDICT_MARKER.lower() in text.lower()


def has_run_log_output(text: str) -> bool:
    return RUN_LOG_MARKER in text


def strip_old_inherit_header(text: str) -> str:
    lines = text.splitlines()
    out = []
    i = 0
    if i < len(lines) and lines[i].startswith("# "):
        out.append(lines[i])
        i += 1
    while i < len(lines) and (
        lines[i].strip() == ""
        or lines[i].startswith(">")
        or "Inherits the §0" in lines[i]
        or "inherits the §0" in lines[i]
    ):
        if lines[i].startswith("# "):
            out.append(lines[i])
        i += 1
    return "\n".join(out + lines[i:]).lstrip("\n")


def golden_rule_block(title: str, inv_id: str) -> str:
    return f"""---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [{inv_id}] {title}: state the single measurable gap (one sentence).
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

"""


def dual_verdict_addendum() -> str:
    return """
### Dual verdict (required in `*_VERDICT.md`)

| Axis | Grades | Notes |
|------|--------|-------|
| **Prompt completion** | A / B / C / D / F | Phase gates in §④ executed? |
| **Physics class** | NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN | Mechanism earned vs identity check |

"""


def run_log_output_line(tool_stem: str) -> str:
    return f"- **`RUN_LOG.md`** — pre-commit block, ADJ entries, gate decisions (mandatory)\n"


def section_10_block(inv_id: str, domain: str, text: str) -> str:
    hint = DOMAIN_ENGINE_HINTS.get(domain, "sdt::laws::measured + domain headers")

    # Try to extract numeric thresholds from existing success criteria
    thresholds = []
    for m in re.finditer(r"(\d+(?:\.\d+)?)\s*%", text):
        thresholds.append(m.group(0))
    thresh_note = ", ".join(thresholds[:5]) if thresholds else "[commit per phase in RUN_LOG]"

    return f"""
---

{SECTION_10_MARKER}

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — {inv_id}
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: {hint}
- Phase thresholds (committed before run): {thresh_note}
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*{inv_id} · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
"""


def upgrade_prompt(path: Path, dry_run: bool) -> str:
    original = path.read_text(encoding="utf-8")
    if "PERFECT_PROMPT_TEMPLATE" in original and has_section_10(original) and has_dual_verdict(original):
        return "skip_complete"

    inv_id = investigation_id(path)
    domain = domain_key(path)
    title = extract_title(original)
    body = strip_old_inherit_header(original)

    # Ensure title line only once at top
    if not body.startswith("# "):
        body = f"# {title}\n\n" + body

    parts = [body.split("\n", 1)[0], ""]  # title line
    rest = body.split("\n", 1)[1] if "\n" in body else ""

    out = parts[0] + "\n\n" + STANDARD_HEADER + "\n"

    if "## ⓪" not in rest and "Golden Rule" not in rest:
        out += golden_rule_block(title, inv_id)

    out += rest

    if not has_dual_verdict(out):
        # Append dual verdict before §⑩ or at end of success criteria area
        if "## ⑤" in out or "Success criteria" in out.lower():
            out += dual_verdict_addendum()
        else:
            out += "\n## ⑤ Success criteria — dual verdict\n" + dual_verdict_addendum()

    if not has_run_log_output(out):
        tool = re.sub(r"[^a-z0-9_]", "_", inv_id.lower())
        insert = run_log_output_line(tool)
        if "## ⑥" in out or "## 6 · Outputs" in out or "## 6." in out:
            out = re.sub(
                r"(## 6[·.]?\s*Outputs[^\n]*\n)",
                r"\1\n" + insert,
                out,
                count=1,
                flags=re.IGNORECASE,
            )
        else:
            out += "\n## ⑥ Outputs\n\n" + insert

    if not has_section_10(out):
        out += section_10_block(inv_id, domain, original)

    if out.rstrip() == original.rstrip():
        return "unchanged"

    if not dry_run:
        path.write_text(out if out.endswith("\n") else out + "\n", encoding="utf-8")
    return "upgraded"


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    prompts = sorted(INV.glob("**/PROMPT.md"))
    stats = {"upgraded": 0, "skip_complete": 0, "unchanged": 0}

    for p in prompts:
        if "tools" in p.parts:
            continue
        result = upgrade_prompt(p, args.dry_run)
        stats[result] = stats.get(result, 0) + 1
        if result == "upgraded":
            print(f"  UPGRADED: {p.relative_to(ROOT)}")

    print(f"\nTotal: {len(prompts)} prompts")
    for k, v in sorted(stats.items()):
        print(f"  {k}: {v}")
    if args.dry_run:
        print("(dry run — no files written)")


if __name__ == "__main__":
    main()
