"""Static and engine-level validation for the NSEQ16 public sequencer."""

from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]
RELEASE = ROOT / "Release" / "HTML_SDT_Website"
DOCS = ROOT / "docs"
HTML = RELEASE / "nuclear-packing-sequencer.html"
PACKER = RELEASE / "js" / "pack-nucleus.js"
NUCLEAR_INPUTS = RELEASE / "js" / "nuclear-inputs.js"
GEAR = RELEASE / "js" / "traction-gear-engine.js"


NODE_RUNNER = r"""
require(process.argv[1]);
require(process.argv[2]);
require(process.argv[3]);
const gear = globalThis.SDT_TRACTION_GEAR;
const keys = ['He4','Li7','Be9','B11','C12','N14','O16'];
const rows = {};
for (const key of keys) {
  const model = gear.build(key);
  rows[key] = {
    version: model.version,
    A: model.metrics.nucleonCount,
    Z: model.metrics.protonCount,
    contacts: model.metrics.contactCount,
    unlike: model.metrics.unlikeContacts,
    slip: model.metrics.maxSlip,
    rim: model.metrics.maxContactResidual,
    seat: model.metrics.maxModuleSeatResidual,
    braid: model.braid
  };
}
const light = {};
for (const key of ['H2','H3','He3']) {
  light[key] = gear.fitLightNucleus(key);
}
console.log(JSON.stringify({
  rows,
  light,
  neutron: gear.neutronMagneticCalibration(),
  self: gear.selfTest()
}));
"""

DOM_HARNESS = r"""
globalThis.window = globalThis;
globalThis.location = { hash: '' };
globalThis.addEventListener = () => {};
globalThis.requestAnimationFrame = () => 1;
globalThis.cancelAnimationFrame = () => {};
globalThis.matchMedia = () => ({ matches: false, addEventListener() {} });

const elements = new Map();
function canvasContext() {
  return new Proxy({}, {
    get(target, key) {
      if (!(key in target)) target[key] = () => {};
      return target[key];
    },
    set(target, key, value) {
      target[key] = value;
      return true;
    }
  });
}
function element(id = '') {
  if (!elements.has(id)) {
    const context = canvasContext();
    elements.set(id, {
      id,
      innerHTML: '',
      textContent: '',
      value: '',
      checked: false,
      disabled: false,
      title: '',
      className: '',
      style: {},
      children: [],
      width: 300,
      height: 42,
      clientWidth: 300,
      appendChild(child) { this.children.push(child); return child; },
      addEventListener() {},
      getContext() { return context; },
      getBoundingClientRect() {
        return { left: 0, top: 0, right: 300, bottom: 42, width: 300, height: 42 };
      }
    });
  }
  return elements.get(id);
}
globalThis.document = {
  hidden: false,
  documentElement: { getAttribute() { return null; } },
  getElementById(id) { return element(id); },
  createElement(tag) { return element(`created-${tag}-${elements.size}`); },
  addEventListener() {}
};
"""


def report(name: str, passed: bool, detail: str) -> bool:
    print(f"{name:<5} {'PASS' if passed else 'FAIL'}  {detail}")
    return passed


def main() -> int:
    sys.stdout.reconfigure(encoding="utf-8")
    source = HTML.read_text(encoding="utf-8")
    module_match = re.search(
        r'<script type="module">(.*?)</script>',
        source,
        flags=re.DOTALL,
    )
    module_source = module_match.group(1) if module_match else ""
    syntax = subprocess.run(
        ["node", "--check", "-"],
        input=module_source,
        text=True,
        encoding="utf-8",
        capture_output=True,
        cwd=ROOT,
    )
    s0 = bool(module_match) and syntax.returncode == 0

    engine_output = subprocess.check_output(
        [
            "node",
            "-e",
            NODE_RUNNER,
            str(PACKER),
            str(NUCLEAR_INPUTS),
            str(GEAR),
        ],
        cwd=ROOT,
        text=True,
        encoding="utf-8",
    )
    data = json.loads(engine_output)
    s1 = all(
        row["unlike"]
        and row["slip"] <= 1e-10
        and row["rim"] <= 1e-10
        and row["seat"] <= 1e-10
        for row in data["rows"].values()
    )

    braid = data["self"]["braid"]
    s2 = (
        braid["majorTours"] == 4
        and braid["poloidalTurns"] == 5
        and braid["strandCount"] == 4
        and abs(braid["localTwistsPerLap"] - 1) <= 1e-12
        and braid["seamLaneTargets"] == [1, 2, 3, 0]
        and braid["maximumSeamResidual"] <= 1e-10
    )

    order = [
        source.find('src="js/pack-nucleus.js"'),
        source.find('src="js/traction-gear-engine.js"'),
        source.find('<script type="module">'),
    ]
    s3 = all(position >= 0 for position in order) and order == sorted(order)

    required = (
        "CONTACT_PRESET",
        "adaptContactModel",
        "gear.braidStrandPoint",
        "mobiusReg",
        "buildCanonicalComposite",
        "gear.operatingWakeSegments",
        "gear.speciesMagneticSegments",
        "deformable wake mesh",
        "NSEQ16 contact candidate",
        "NSEQ05 legacy control",
    )
    s4 = all(token in source for token in required)

    removed = (
        "fitR2tot",
        "dfKappa",
        "read the mass defect",
        "mass defect from the shadow",
        "trefoil topology",
    )
    s5 = all(token not in source for token in removed)

    docs_html = DOCS / "nuclear-packing-sequencer.html"
    docs_gear = DOCS / "js" / "traction-gear-engine.js"
    docs_nuclear_inputs = DOCS / "js" / "nuclear-inputs.js"
    s6 = (
        docs_html.exists()
        and docs_gear.exists()
        and docs_nuclear_inputs.exists()
        and HTML.read_bytes() == docs_html.read_bytes()
        and GEAR.read_bytes() == docs_gear.read_bytes()
        and NUCLEAR_INPUTS.read_bytes() == docs_nuclear_inputs.read_bytes()
    )

    inline_scripts = re.findall(
        r"<script(?:\s+[^>]*)?>(.*?)</script>",
        source,
        flags=re.DOTALL,
    )
    data_script = next(
        (script for script in inline_scripts if "const RAW =" in script),
        "",
    )
    ledger_script = next(
        (script for script in inline_scripts if "function subunitCount" in script),
        "",
    )
    runtime_module = module_source.replace("\ninitThree();", "\n", 1)
    runtime_probe = r"""
function capture() {
  return {
    symbol: state.iso.sym,
    A: state.iso.A,
    shown: state.nucShown.length,
    status: $('ctStatus').textContent,
    engine: $('ctEngine').textContent,
    stage: $('ctStage').textContent,
    contacts: $('trContacts').textContent,
    splice: $('brSplice').textContent,
    fixedContact: $('rTight').disabled,
    route: $('ctRoute').textContent
  };
}
selectIso(ISO.find(row => row.sym === 'H' && row.A === 2));
const h2 = capture();
selectIso(ISO.find(row => row.sym === 'H' && row.A === 3));
const h3 = capture();
selectIso(ISO.find(row => row.sym === 'He' && row.A === 3));
const he3 = capture();
selectIso(ISO.find(row => row.sym === 'C' && row.A === 12));
const c12 = capture();
selectIso(ISO.find(row => row.sym === 'Fe' && row.A === 56));
const fe56 = capture();
console.log(JSON.stringify({h2, h3, he3, c12, fe56}));
"""
    runtime = subprocess.run(
        ["node", "-"],
        input="\n".join(
            (
                DOM_HARNESS,
                "require('./Release/HTML_SDT_Website/js/pack-nucleus.js');",
                "require('./Release/HTML_SDT_Website/js/nuclear-inputs.js');",
                "require('./Release/HTML_SDT_Website/js/traction-gear-engine.js');",
                data_script,
                ledger_script,
                runtime_module,
                runtime_probe,
            )
        ),
        text=True,
        encoding="utf-8",
        capture_output=True,
        cwd=ROOT,
    )
    runtime_data = (
        json.loads(runtime.stdout.strip().splitlines()[-1])
        if runtime.returncode == 0 and runtime.stdout.strip()
        else {}
    )
    h2 = runtime_data.get("h2", {})
    h3 = runtime_data.get("h3", {})
    he3 = runtime_data.get("he3", {})
    c12 = runtime_data.get("c12", {})
    fe56 = runtime_data.get("fe56", {})
    s7 = (
        h2.get("status") == "CALIBRATED(8)"
        and h2.get("engine") == "NSEQ18-WEB-1"
        and h2.get("shown") == 2
        and h2.get("fixedContact") is True
        and h3.get("status") == "CALIBRATED(9)"
        and h3.get("shown") == 3
        and he3.get("status") == "CALIBRATED(9)"
        and he3.get("shown") == 3
        and c12.get("status") == "NSEQ18 interstitial"
        and c12.get("shown") == 12
        and c12.get("fixedContact") is True
        and fe56.get("status") == "NSEQ18 interstitial"
        and fe56.get("engine") == "NSEQ18-WEB-1"
        and fe56.get("shown") == 56
        and fe56.get("fixedContact") is True
    )
    light = data["light"]
    neutron = data["neutron"]
    s8 = all(
        row["coefficientBoundsSatisfied"]
        and row["mesh"]["circuitCount"]
        == row["mesh"]["closedCircuitCount"]
        and row["mesh"]["maximumRelativeDivergence"] <= 0.01
        and row["magneticRoutes"]["relativeResidual"] <= 0.05
        and abs(row["residuals"]["binding"]) <= 1e-4
        and abs(row["residuals"]["magnetic"]) <= 1e-4
        and (
            row["residuals"]["quadrupole"] is None
            or abs(row["residuals"]["quadrupole"]) <= 1e-4
        )
        and any(
            item["wakeCompliance"] > 0.01
            for item in row["mesh"]["deformationLedger"]
        )
        and all(
            abs(item["throatFraction"] + item["poloidalFraction"] - 1)
            <= 1e-12
            for item in row["mesh"]["deformationLedger"]
        )
        and abs(
            row["mesh"]["neutronCalibration"][
                "seatedElectronCoefficientMuNPerGeometricMoment"
            ]
            - neutron["seatedElectronCoefficientMuNPerGeometricMoment"]
        ) <= 1e-12
        for row in light.values()
    ) and light["H3"]["neutronNeutronContactExcluded"] and (
        neutron["classification"] == "CALIBRATED(1)"
        and neutron["protonContributionMuN"] > 0
        and neutron["seatedElectronContributionMuN"] < 0
        and abs(neutron["residualMuN"]) <= 1e-12
        and neutron["suppressionRatio"] < 0.30
    )

    print("NSEQ16 — public nuclear sequencer")
    print()
    passed = [
        report("S0", s0, syntax.stderr.strip() or "module syntax"),
        report("S1", s1, "H→O p-n contact construction metrics"),
        report("S2", s2, "(4,5) cyclic lane splice"),
        report("S3", s3, "packer → traction engine → module load order"),
        report("S4", s4, "contact, braid and Möbius renderer wiring"),
        report("S5", s5, "withdrawn overlap/trefoil UI removed"),
        report("S6", s6, "Release/docs byte parity"),
        report(
            "S7",
            s7,
            "headless H-2/H-3/He-3/C-12/Fe-56 UI route"
            if runtime.returncode == 0
            else runtime.stderr.strip(),
        ),
        report(
            "S8",
            s8,
            "neutron counter-circulation + deformable wake calibration gates",
        ),
    ]
    print()
    if all(passed):
        print("ASSESSMENT: NSEQ16_SEQUENCER_READY")
        return 0
    print("ASSESSMENT: NSEQ16_SEQUENCER_NOT_READY")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
