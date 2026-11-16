"""Post-seal comparisons for FLM15.

This file is intentionally separate from the blind forward instrument.
"""

from __future__ import annotations

import hashlib
import json
import math
from pathlib import Path

import numpy as np


ROOT = Path(__file__).parent
BLIND = ROOT / "blind_ratio.txt"


def relative_error(value: float, target: float) -> float:
    return (value / target - 1.0) * 100.0


def main() -> None:
    # The sealing writer hashes canonical LF text before Windows newline
    # translation. Reconstruct that canonical byte sequence for verification.
    canonical_text = BLIND.read_text(encoding="utf-8")
    raw = canonical_text.encode("utf-8")
    sealed = (ROOT / "blind_ratio.txt.sha256").read_text(encoding="ascii").split()[0]
    actual = hashlib.sha256(raw).hexdigest()
    if actual != sealed:
        raise RuntimeError("blind result does not match its pre-reveal seal")
    blind = json.loads(canonical_text)
    ratio = float(blind["primary_ratio"])

    comparisons = {
        "six_pi_fifth": 6.0 * math.pi**5,
        "measured_particle_ratio": 1836.152673426,
        "winding_self_index": (3.0 / 2.0) ** 1.5 * 1000.0 - 1.0,
    }
    rows = []
    for name, target in comparisons.items():
        raw_error = relative_error(ratio, target)
        rows.append({
            "name": name,
            "target": target,
            "relative_error_percent": raw_error,
            "absolute_log_error": abs(math.log(ratio / target)),
            "look_elsewhere_family_size": len(comparisons),
            "interpretation": "comparison only; three post-seal targets inspected",
        })

    scans: dict[str, list[dict]] = {}
    reference_aspect = math.sqrt(2.0 / 3.0)
    selectors = {
        "segments": lambda r: (
            abs(r["aspect"] - reference_aspect) < 1e-12
            and r["samples"] == 65536 and r["core"] == 0.12
            and r["padding"] == 5.0 and r["orientation"] == 0
        ),
        "samples": lambda r: (
            abs(r["aspect"] - reference_aspect) < 1e-12
            and r["segments"] == 192 and r["core"] == 0.12
            and r["padding"] == 5.0 and r["orientation"] == 0
        ),
        "core": lambda r: (
            abs(r["aspect"] - reference_aspect) < 1e-12
            and r["segments"] == 192 and r["samples"] == 65536
            and r["padding"] == 5.0 and r["orientation"] == 0
        ),
        "padding": lambda r: (
            abs(r["aspect"] - reference_aspect) < 1e-12
            and r["segments"] == 192 and r["samples"] == 65536
            and r["core"] == 0.12 and r["orientation"] == 0
        ),
    }
    for key, selector in selectors.items():
        scans[key] = [
            {key: r[key], "ratio": r["ratio"]}
            for r in blind["rows"] if selector(r)
        ]
        scans[key].sort(key=lambda x: x[key])

    primary = [
        r for r in blind["rows"]
        if r["segments"] == 192 and r["samples"] == 65536
        and r["core"] == 0.12 and r["padding"] == 5.0
    ]
    length_ratios = [
        r["trefoil"]["length"] / r["circle"]["length"] for r in primary
    ]
    output = {
        "seal_verified": True,
        "sealed_sha256": sealed,
        "blind_ratio": ratio,
        "comparisons": rows,
        "convergence_scans": scans,
        "primary_tensor_ratio_range": blind["primary_range"],
        "bare_length_ratio_range": [
            float(np.min(length_ratios)), float(np.max(length_ratios))
        ],
        "conclusion": (
            "The converged simple phase-stiffness response is order unity and "
            "does not generate a large locked-wake ratio."
        ),
    }
    (ROOT / "revealed_comparisons.json").write_text(
        json.dumps(output, indent=2, sort_keys=True) + "\n", encoding="utf-8"
    )
    print(json.dumps(output, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
