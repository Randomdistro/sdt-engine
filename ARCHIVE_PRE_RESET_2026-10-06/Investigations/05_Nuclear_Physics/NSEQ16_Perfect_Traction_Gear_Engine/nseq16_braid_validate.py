"""Direct validator for the NSEQ16 cyclic quadruple-helix repair."""

from __future__ import annotations

import json
import math
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]
PACKER = ROOT / "Release" / "HTML_SDT_Website" / "js" / "pack-nucleus.js"
NUCLEAR_INPUTS = (
    ROOT / "Release" / "HTML_SDT_Website" / "js" / "nuclear-inputs.js"
)
TRACTION = (
    ROOT
    / "Release"
    / "HTML_SDT_Website"
    / "js"
    / "traction-gear-engine.js"
)
DOCS_TRACTION = ROOT / "docs" / "js" / "traction-gear-engine.js"
ATOMICUS_JS = ROOT / "Release" / "HTML_SDT_Website" / "atomicus-3d.js"
DOCS_ATOMICUS_JS = ROOT / "docs" / "atomicus-3d.js"
ATOMICUS_HTML = ROOT / "Release" / "HTML_SDT_Website" / "atomicus-3d.html"
DOCS_ATOMICUS_HTML = ROOT / "docs" / "atomicus-3d.html"
SMOKE = (
    ROOT
    / "Investigations"
    / "05_Nuclear_Physics"
    / "NSEQ16_Perfect_Traction_Gear_Engine"
    / "atomicus_browser_smoke.js"
)


NODE_RUNNER = r"""
require(process.argv[1]);
require(process.argv[2]);
require(process.argv[3]);
const gear = globalThis.SDT_TRACTION_GEAR;
const Rp = globalThis.SDT_NUCLEAR_PACKING.R_p;
const diagnostics = gear.braidDiagnostics(Rp, 4096);
const repeat = gear.braidDiagnostics(Rp, 4096);
const start = gear.quadrupleHelixPoint(0, Rp);
const tourGaps = [];
for (let tour = 1; tour <= 4; tour++) {
  const point = gear.quadrupleHelixPoint(
    2 * Math.PI * tour / gear.braidSpec.majorTours,
    Rp
  );
  tourGaps.push(
    Math.hypot(
      point[0] - start[0],
      point[1] - start[1],
      point[2] - start[2]
    ) / Rp
  );
}
console.log(JSON.stringify({
  version: gear.version,
  spec: gear.braidSpec,
  diagnostics,
  repeat,
  tourGaps
}));
"""


def report(name: str, passed: bool, detail: str) -> bool:
    print(f"{name:<4} {'PASS' if passed else 'FAIL'}  {detail}")
    return passed


def main() -> int:
    sys.stdout.reconfigure(encoding="utf-8")
    output = subprocess.check_output(
        [
            "node",
            "-e",
            NODE_RUNNER,
            str(PACKER),
            str(NUCLEAR_INPUTS),
            str(TRACTION),
        ],
        cwd=ROOT,
        text=True,
        encoding="utf-8",
    )
    data = json.loads(output)
    spec = data["spec"]
    braid = data["diagnostics"]

    b0 = (
        spec["majorTours"] == 4
        and spec["poloidalTurns"] == 5
        and spec["strandCount"] == 4
        and spec["localTwistsPerLap"] == 1
        and spec["seamLaneAdvance"] == 1
        and braid["componentCount"] == 1
    )

    expected_phase = 2 * math.pi + math.pi / 2
    phase_residual = abs(braid["oneLapPhaseAdvance"] - expected_phase)
    b1 = (
        phase_residual <= 1e-12
        and abs(braid["localTwistsPerLap"] - 1.0) <= 1e-12
    )

    b2 = (
        braid["seamLaneTargets"] == [1, 2, 3, 0]
        and braid["maximumSeamResidual"] <= 1e-10
        and braid["minimumOneLapSelfGap"] > 1e-3
    )

    b3 = braid["maximumSeamTangentResidual"] <= 1e-8

    tour_gaps = data["tourGaps"]
    b4 = all(gap > 1e-3 for gap in tour_gaps[:3]) and tour_gaps[3] <= 1e-10

    b5 = braid["fourTourStages"] == ["inner", "under", "outer", "over"]

    b6 = (
        braid["outerEnvelopeResidual"] <= 1e-12
        and braid["innerEnvelopeRatio"] > 0
    )

    speed_ratio_residual = abs(
        braid["sampledSpeedRatio"] - braid["analyticSpeedRatio"]
    )
    b7 = (
        braid["minimumLocalSpeed"] > 0
        and math.isfinite(braid["maximumLocalSpeed"])
        and speed_ratio_residual <= 1e-8
    )

    b8 = (
        abs(braid["oldFourOneLocalTwistsPerLap"]) <= 1e-12
        and abs(braid["oldFourOneLocalTwistsPerLap"] - 1.0) > 0.5
    )

    smoke_output = subprocess.check_output(
        ["node", str(SMOKE)],
        cwd=ROOT,
        text=True,
        encoding="utf-8",
    )
    atomicus_js = ATOMICUS_JS.read_text(encoding="utf-8")
    atomicus_html = ATOMICUS_HTML.read_text(encoding="utf-8")
    b9 = (
        braid == data["repeat"]
        and TRACTION.read_bytes() == DOCS_TRACTION.read_bytes()
        and ATOMICUS_JS.read_bytes() == DOCS_ATOMICUS_JS.read_bytes()
        and ATOMICUS_HTML.read_bytes() == DOCS_ATOMICUS_HTML.read_bytes()
        and "gear.braidStrandPoint" in atomicus_js
        and "(4,5) cyclic quadruple helix" in atomicus_js
        and 'option value="braid"' in atomicus_html
        and "cyclic (4,5) braid + trefoil control" in smoke_output
    )

    print("NSEQ16 — cyclic quadruple-helix repair")
    print(f"Instrument: {data['version']}")
    print()
    passed = [
        report("B0", b0, "P=4, Q=5, four lanes, gcd=1"),
        report(
            "B1",
            b1,
            f"one-lap phase=2π+π/2; residual={phase_residual:.3e}",
        ),
        report(
            "B2",
            b2,
            f"cyclic splice residual={braid['maximumSeamResidual']:.3e}",
        ),
        report(
            "B3",
            b3,
            f"seam tangent residual={braid['maximumSeamTangentResidual']:.3e}",
        ),
        report(
            "B4",
            b4,
            "first return after four major laps",
        ),
        report("B5", b5, "tour order inner → under → outer → over"),
        report(
            "B6",
            b6,
            f"rim envelope residual={braid['outerEnvelopeResidual']:.3e}",
        ),
        report(
            "B7",
            b7,
            f"outer/inner speed={braid['analyticSpeedRatio']:.6f}; "
            f"residual={speed_ratio_residual:.3e}",
        ),
        report("B8", b8, "withdrawn (4,1) control has zero full twists/lap"),
        report("B9", b9, "deterministic mirrors and 3D smoke"),
    ]
    print()
    if all(passed):
        print("ASSESSMENT: CYCLIC_QUADRUPLE_HELIX_CANDIDATE")
        print(
            "One filament makes four ring laps; every lap contains one full "
            "local twist and advances to the adjacent lane."
        )
        return 0
    print("ASSESSMENT: CYCLIC_QUADRUPLE_HELIX_REJECTED")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
