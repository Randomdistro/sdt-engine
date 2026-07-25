# FD11 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `FD11_VERDICT.md` and `results.txt`
> deleted 2026-07-26 (git-recoverable; `FD11_STAGGERED_GEOTHERMAL.md` and
> `MATERIALS_AND_PARTS.md` kept — design documents, not verdicts). Tool:
> `fd11_tesla_turbine.cpp`, g++ 15.2 -O2, exit **0**. Output: `fd11_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** Applied-engineering capstone of the FD series; drive mechanism from FD06/PPT06
traction; steam and material properties MEASURED-INPUT and labelled.

## What the direct run computed (engineering estimate — the tool's own label)

- Turbine design point: b_opt = 1.25 mm (form derived, K_B CALIBRATED(1); Tesla's measured
  ~0.4 mm the convergence target); rim speed capped by hoop stress at 27,918 rpm; operating
  point 16,711 rpm → 1.7× headroom (F5 satisfied, must be >1).
- Geothermal sweep (2 km closed loop): net-POSITIVE only from ≥50 °C/km (a normal 30 °C/km site
  is too cold to flash — honest negative); hot site (80 °C/km) ~+25 kW net.
- Pinhole sensitivity: pump friction ~1/d⁵ dominates; below ~40 mm bore the friction eats the
  output.

## Verdict

- **Prompt completion: A** for what it is — an applied design study.
- **Physics class: none claimed — APPLIED/engineering estimate**, per the tool's own closing
  line ("not a sealed SDT prediction"). The SDT content is inherited (FD06 traction drive);
  everything site-specific is measured-input or assumed efficiency, all labelled. The honest
  negative (cold sites don't pay) is recorded, not hidden.
- **Recovery:** n/a · **Cascade root:** none.
