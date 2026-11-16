"""Direct validator for the NSEQ16 browser traction engine."""

from __future__ import annotations

import json
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

CASES = {
    "H1": (1, 1),
    "H2": (2, 1),
    "H3": (3, 1),
    "He4": (4, 2),
    "Li7": (7, 3),
    "Be9": (9, 4),
    "B11": (11, 5),
    "C12": (12, 6),
    "N14": (14, 7),
    "O16": (16, 8),
}


NODE_RUNNER = r"""
require(process.argv[1]);
require(process.argv[2]);
require(process.argv[3]);
const gear = globalThis.SDT_TRACTION_GEAR;
const rows = {};
const baseline = {};
for (const key of ['H1','H2','H3','He4','Li7','Be9','B11','C12','N14','O16']) {
  const preset = gear.presets[key];
  const first = gear.build(key);
  const second = gear.build(key);
  rows[key] = {
    A: preset.A,
    Z: preset.Z,
    grammar: first.grammar,
    metrics: first.metrics,
    seatModel: first.seatModel,
    poleAxis: first.poleAxis,
    seatLedger: first.seatLedger,
    modules: first.modules,
    routes: first.routes,
    routeComparison: first.routeComparison,
    constructionTransition: first.constructionTransition,
    fingerprint: first.fingerprint,
    repeatFingerprint: second.fingerprint,
    topology: first.topology
  };
  if (preset.Z >= 2 && !(preset.Z === 2 && preset.A === 3)) {
    const packed = globalThis.packNucleus(preset.A, preset.Z);
    baseline[key] = gear.evaluateNseq05(packed, first.Rp);
  }
}
function sampledClosure(segments) {
  const Rp = globalThis.SDT_NUCLEAR_PACKING.R_p;
  const a = gear.fourTourPoint(0, Rp);
  const b = gear.fourTourPoint(2 * Math.PI * segments / segments, Rp);
  return Math.hypot(b[0]-a[0], b[1]-a[1], b[2]-a[2]) / Rp;
}
console.log(JSON.stringify({
  version: gear.version,
  rows,
  baseline,
  self: gear.selfTest(),
  resolution: {
    n128: sampledClosure(128),
    n256: sampledClosure(256)
  }
}));
"""


def run_node() -> dict:
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
    return json.loads(output)


def report(name: str, passed: bool, detail: str) -> bool:
    print(f"{name:<5} {'PASS' if passed else 'FAIL'}  {detail}")
    return passed


def main() -> int:
    sys.stdout.reconfigure(encoding="utf-8")
    data = run_node()
    rows = data["rows"]
    self_test = data["self"]

    inventory_ok = all(
        rows[key]["metrics"]["nucleonCount"] == expected[0]
        and rows[key]["metrics"]["protonCount"] == expected[1]
        for key, expected in CASES.items()
    )
    grammar_ok = True
    module_ok = True
    for key, (A, Z) in CASES.items():
        row = rows[key]
        grammar = row["grammar"]
        grammar_ok = grammar_ok and grammar["valid"]
        if Z >= 2:
            nd = 3 * Z - A - 2
            nt = A - 2 * Z
            grammar_ok = (
                grammar_ok
                and grammar["nd"] == nd
                and grammar["nt"] == nt
                and nd + nt == Z - 2
            )
            kinds = [module["kind"] for module in row["modules"]]
            module_ok = (
                module_ok
                and kinds.count("alpha") == 1
                and kinds.count("deuteron") == nd
                and kinds.count("triton") == nt
            )
    r0 = inventory_ok and grammar_ok and module_ok

    alpha_rows = [row for key, row in rows.items() if CASES[key][1] >= 2]
    r1 = all(
        row["metrics"]["hasPolarAxis"]
        and row["metrics"]["alphaEquatorialResidual"] <= 1e-10
        and row["metrics"]["alphaLikeDiagonalRatio"] > 1.0 + 1e-10
        for row in alpha_rows
    )

    max_seat_error = max(float(value) for value in self_test["seatErrors"].values())
    valence = self_test["valenceSeats"]
    valence_ok = (
        max_seat_error <= 1e-10
        and valence["firstEquatorial"] <= 1e-10
        and valence["oppositionResidual"] <= 1e-10
        and valence["triangleEquatorial"] <= 1e-10
        and valence["tropicalLatitudeResidual"] <= 1e-10
        and valence["tropicalSigns"] == 2
        and valence["thirdSixthOpposition"] <= 1e-10
        and valence["sixthPairingMarker"] <= 1e-10
    )
    r2 = valence_ok and all(
        row["seatModel"] == "valence-position-spherical-code"
        and bool(row["constructionTransition"])
        for row in rows.values()
    )

    max_contact = max(row["metrics"]["maxContactResidual"] for row in rows.values())
    max_slip = max(row["metrics"]["maxSlip"] for row in rows.values())
    r3 = (
        max_contact <= 1e-10
        and max_slip < 1e-10
        and all(row["metrics"]["unlikeContacts"] for row in rows.values())
    )

    maximum_unlisted = max(
        row["metrics"]["unlistedTouches"] for row in rows.values()
    )
    maximum_like = max(row["metrics"]["likeLikeTouches"] for row in rows.values())
    r4 = maximum_unlisted == 0 and maximum_like == 0 and all(
        row["metrics"]["allTouched"] for row in rows.values()
    )

    r5 = all(
        row["metrics"]["tractionConsistent"]
        and row["metrics"]["connected"]
        and row["metrics"]["unlikeContacts"]
        and row["metrics"]["maxSlip"] < 1e-10
        for row in rows.values()
    )

    maximum_seat_norm = max(
        row["metrics"]["seatNormResidual"] for row in rows.values()
    )
    maximum_module_seat = max(
        row["metrics"]["maxModuleSeatResidual"] for row in rows.values()
    )
    r6 = (
        maximum_seat_norm <= 1e-12
        and maximum_module_seat <= 1e-10
        and all(
            row["seatModel"] == "valence-position-spherical-code"
            for row in rows.values()
        )
    )

    maximum_proton_route = max(
        row["routeComparison"]["maximumProtonResidual"]
        for row in rows.values()
    )
    r7 = True
    for key, row in rows.items():
        _, Z = CASES[key]
        if Z < 2:
            continue
        expected_seats = Z - 2
        proton_route = row["routes"]["protonByZ"]
        module_route = row["routes"]["constitutional"]
        r7 = (
            r7
            and len(proton_route) == expected_seats
            and len(module_route) == expected_seats
            and sum(item["kind"] == "triton" for item in module_route)
            == row["grammar"]["nt"]
            and all(item["residual"] <= 1e-10 for item in module_route)
            and row["routeComparison"]["geometricMatch"]
            == "constitutional-module-centres"
        )
    r7 = r7 and maximum_proton_route > 1e-3

    baseline = data["baseline"]
    baseline_rejected = all(
        not row["tractionConsistent"]
        and (
            row["maxContactResidual"] > 1e-10
            or row["unlistedTouches"] > 0
            or not row["hasPolarAxis"]
            or not row["hasConstructionOrder"]
        )
        for row in baseline.values()
    )
    r8 = baseline_rejected
    baseline_contact = max(
        row["maxContactResidual"] for row in baseline.values()
    )

    braid = self_test["braid"]
    stages = braid["fourTourStages"]
    topology_ok = (
        braid["majorTours"] == 4
        and braid["poloidalTurns"] == 5
        and braid["strandCount"] == 4
        and braid["componentCount"] == 1
        and abs(braid["localTwistsPerLap"] - 1.0) <= 1e-12
        and braid["seamLaneAdvance"] == 1
        and braid["seamLaneTargets"] == [1, 2, 3, 0]
        and braid["maximumSeamResidual"] <= 1e-10
        and braid["maximumSeamTangentResidual"] <= 1e-8
        and braid["minimumOneLapSelfGap"] > 1e-3
        and braid["fourTourClosure"] <= 1e-10
        and stages == ["inner", "under", "outer", "over"]
        and braid["outerEnvelopeResidual"] <= 1e-12
        and braid["innerEnvelopeRatio"] > 0
        and abs(
            braid["sampledSpeedRatio"] - braid["analyticSpeedRatio"]
        ) <= 1e-8
        and abs(braid["oldFourOneLocalTwistsPerLap"]) <= 1e-12
        and self_test["mobiusPosition2Pi"] <= 1e-10
        and abs(self_test["mobiusDirector2Pi"] + 1.0) <= 1e-10
        and self_test["mobiusPosition4Pi"] <= 1e-10
        and abs(self_test["mobiusDirector4Pi"] - 1.0) <= 1e-10
        and all(
        not row["topology"].get(
            "equivalent",
            row["topology"].get("equivalentToOrdinaryTrefoil", False),
        )
            for row in rows.values()
        )
    )
    repeat_ok = all(
        row["fingerprint"] == row["repeatFingerprint"] for row in rows.values()
    )
    resolution_delta = abs(
        data["resolution"]["n256"] - data["resolution"]["n128"]
    )
    docs_traction = ROOT / "docs" / "js" / "traction-gear-engine.js"
    mirror_ok = docs_traction.exists() and TRACTION.read_bytes() == docs_traction.read_bytes()
    r9 = repeat_ok and resolution_delta <= 1e-12 and topology_ok and mirror_ok

    controls_ok = (
        self_test["unlikeSlipControl"] <= 1e-10
        and self_test["likeSlipControl"] > 1.0
    )

    print("NSEQ16 — Atomicus Contact Construction Repair")
    print(f"Instrument: {data['version']}")
    print()
    passed = [
        report("R0", r0, "H–O inventory, grammar and alpha+d+t module counts"),
        report("R1", r1, "alpha equator defines poles; like diagonals remain open"),
        report("R2", r2, "one valence-stage spherical-code progression"),
        report(
            "R3",
            r3,
            f"contact residual={max_contact:.3e}; slip={max_slip:.3e}",
        ),
        report(
            "R4",
            r4,
            f"unlisted touches={maximum_unlisted}; like-like={maximum_like}",
        ),
        report("R5", r5, "connected bipartite p-n contact graph"),
        report(
            "R6",
            r6,
            f"seat unit={maximum_seat_norm:.3e}; "
            f"module-centre={maximum_module_seat:.3e}",
        ),
        report(
            "R7",
            r7,
            f"constitutional route closes; proton-centre control "
            f"residual={maximum_proton_route:.3e}",
        ),
        report(
            "R8",
            r8,
            f"NSEQ05 rejected; contact residual={baseline_contact:.3e}",
        ),
        report(
            "R9",
            r9,
            f"(4,5) braid deterministic; resolution delta="
            f"{resolution_delta:.3e}; mirror={mirror_ok}",
        ),
        report(
            "CTRL",
            controls_ok,
            f"p-n slip={self_test['unlikeSlipControl']:.3e}; "
            f"p-p slip={self_test['likeSlipControl']:.3e}",
        ),
    ]
    print()
    if all(passed):
        print("ASSESSMENT: ATOMICUS_CONTACT_CONSTRUCTION_CANDIDATE")
        print(
            "NSEQ05 is retained only as a legacy geometric control. "
            "No contact-energy or measured-geometry law is promoted."
        )
        return 0
    print("ASSESSMENT: ATOMICUS_CONTACT_CONSTRUCTION_REJECTED")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
