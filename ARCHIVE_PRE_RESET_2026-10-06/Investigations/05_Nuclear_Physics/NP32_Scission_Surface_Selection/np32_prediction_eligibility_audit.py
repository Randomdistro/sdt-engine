"""Independent, source-gated eligibility audit for the historical NP32 yield analysis."""

from __future__ import annotations

import argparse
import ast
import csv
import hashlib
import json
import math
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[3]
AUDIT_DIRECTORY = Path(__file__).resolve().parent

STATIC_INPUTS = {
    "prompt": (
        AUDIT_DIRECTORY / "PROMPT.md",
        9743,
        "ccf81f26efd301c968a3a50b386061bd2b9583e96c45cef4a68a3d582ec1197b",
    ),
    "precommit": (
        AUDIT_DIRECTORY / "NP32_PREDICT_PRECOMMIT_2026-07-25.md",
        3641,
        "9246b48fe0b5959bd2b0c4c44057eebf4d8060e3afe66fe5239fefbe8fb72b7b",
    ),
    "historical_script": (
        AUDIT_DIRECTORY / "np32_predict_check.py",
        3072,
        "6f995b81b405ad5764e68cc93aeefa3bb403c19626d67e482aef783a41d7fc3c",
    ),
    "historical_results": (
        AUDIT_DIRECTORY / "NP32_PREDICT_RESULTS_2026-07-25.md",
        6632,
        "cef9ccb53a6acabe7f2126def2a2ac987ef4bffe4799e4d73ecef5960963fc5d",
    ),
}

SYSTEMS = (
    (
        "U-235",
        ROOT / "Datasets/nuclear/IAEA_U235_independent_FY.csv",
        236,
        "thermal",
        121193,
        "87fcd49503a56b57f98eb785183d778dbfa72551b89f2112a8898fbe0aad6c78",
    ),
    (
        "U-233",
        ROOT / "Datasets/nuclear/fission_yields/IAEA_233U_independent_FY.csv",
        234,
        "thermal",
        128347,
        "878e4e6c1f39fa781cc903006506f66331a4ef0ebd6a9613be30093664daca62",
    ),
    (
        "Pu-239",
        ROOT / "Datasets/nuclear/fission_yields/IAEA_239Pu_independent_FY.csv",
        240,
        "thermal",
        98073,
        "8e9272960f5405f15ac1191ad70bef338b7cdef4b65a451d3cf4426a85dcc425",
    ),
    (
        "Pu-241",
        ROOT / "Datasets/nuclear/fission_yields/IAEA_241Pu_independent_FY.csv",
        242,
        "thermal",
        93869,
        "52bbb5be8087bf6145aee289c6558e18a6a32e3bd7389fa0f9c0f7d30a383732",
    ),
    (
        "Np-237",
        ROOT / "Datasets/nuclear/fission_yields/IAEA_237Np_independent_FY.csv",
        238,
        "fast",
        88035,
        "a14c5e3540fef662d341e4f9e026fb0edf0a462946444379f3478c186fc220bc",
    ),
    (
        "Am-241",
        ROOT / "Datasets/nuclear/fission_yields/IAEA_241Am_independent_FY.csv",
        242,
        "fast",
        100715,
        "a75a4ecd510939227d4502b3b41144f557427af0905bf343eab2174e54740e6c",
    ),
    (
        "U-238",
        ROOT / "Datasets/nuclear/fission_yields/IAEA_238U_independent_FY.csv",
        239,
        "fast",
        90478,
        "e602f666aeb3d9957655774be2deef05534db6d6a464de7ee4da166a8452aa4a",
    ),
    (
        "Th-232",
        ROOT / "Datasets/nuclear/fission_yields/IAEA_232Th_independent_FY.csv",
        233,
        "fast",
        85712,
        "6641d35d4f2c9bc66b86980fc1a6e9c37c6d16137dd3157550a8aa97f7540bc8",
    ),
)


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def verify_file(path: Path, expected_bytes: int, expected_sha256: str) -> dict[str, Any]:
    observed_bytes = path.stat().st_size
    observed_sha256 = sha256(path)
    passed = observed_bytes == expected_bytes and observed_sha256 == expected_sha256
    return {
        "path": path.relative_to(ROOT).as_posix(),
        "expected_bytes": expected_bytes,
        "observed_bytes": observed_bytes,
        "expected_sha256": expected_sha256,
        "observed_sha256": observed_sha256,
        "passed": passed,
    }


def verify_inputs() -> tuple[dict[str, Any], list[dict[str, Any]]]:
    static_records = {
        name: verify_file(path, expected_bytes, expected_sha256)
        for name, (path, expected_bytes, expected_sha256) in STATIC_INPUTS.items()
    }
    observation_records = [
        verify_file(path, expected_bytes, expected_sha256)
        for _, path, _, _, expected_bytes, expected_sha256 in SYSTEMS
    ]
    return static_records, observation_records


def node_label(node: ast.AST) -> str:
    return ast.unparse(node)


def audit_historical_script(script_text: str) -> dict[str, Any]:
    script_tree = ast.parse(script_text)
    imports = [
        node_label(node)
        for node in script_tree.body
        if isinstance(node, (ast.Import, ast.ImportFrom))
    ]
    functions = [
        node.name
        for node in script_tree.body
        if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef))
    ]
    calls = sorted(
        {
            node_label(node.func)
            for node in ast.walk(script_tree)
            if isinstance(node, ast.Call)
        }
    )
    lowercase_source = script_text.lower()
    capability_terms = {
        "contact_graph": ("graph", "network"),
        "edge_or_bond_cost": ("edge", "bond", "cost"),
        "partition_or_cut": ("partition", "mincut", "minimum_cut", "cut"),
    }
    capability_presence = {
        name: any(term in lowercase_source for term in terms)
        for name, terms in capability_terms.items()
    }
    yield_function_present = "massyield" in functions
    model_functions = [
        name
        for name in functions
        if name not in {"massyield", "hump_centroid", "slope", "report"}
    ]
    source_before_yield = script_text.split("def massyield", maxsplit=1)[0]
    forward_split_before_yield_load = any(
        term in source_before_yield.lower()
        for term in ("predict", "partition", "graph", "cut", "split")
    )
    return {
        "imports": imports,
        "declared_functions": functions,
        "called_functions": calls,
        "model_specific_functions": model_functions,
        "yield_loader_present": yield_function_present,
        "required_capability_term_presence": capability_presence,
        "forward_split_before_yield_load": forward_split_before_yield_load,
        "minimum_cut_mechanism_implemented": bool(
            all(capability_presence.values())
            and forward_split_before_yield_load
            and model_functions
        ),
    }


def build_mass_yield(path: Path, energy: str) -> dict[int, float]:
    yield_column = f"independent_{energy}_fy"
    mass_yield: dict[int, float] = {}
    with path.open(encoding="utf-8", newline="") as handle:
        reader = csv.DictReader(handle)
        required_columns = {"a_daughter", yield_column}
        if reader.fieldnames is None or not required_columns.issubset(reader.fieldnames):
            raise ValueError(f"{path}: missing required columns {sorted(required_columns)}")
        for row in reader:
            value = (row.get(yield_column) or "").strip()
            if not value:
                continue
            mass_number = int(row["a_daughter"])
            mass_yield[mass_number] = mass_yield.get(mass_number, 0.0) + float(value)
    return mass_yield


def centroid_around_mode(mass_yield: dict[int, float], lower: int, upper: int) -> tuple[float, int]:
    mode = max(range(lower, upper + 1), key=lambda mass_number: mass_yield.get(mass_number, 0.0))
    numerator = sum(
        mass_number * mass_yield.get(mass_number, 0.0)
        for mass_number in range(mode - 8, mode + 9)
    )
    denominator = sum(
        mass_yield.get(mass_number, 0.0)
        for mass_number in range(mode - 8, mode + 9)
    )
    if denominator == 0.0:
        raise ValueError(f"empty mode window {lower}-{upper}")
    return numerator / denominator, mode


def linear_slope(x_values: list[float], y_values: list[float]) -> float:
    x_mean = sum(x_values) / len(x_values)
    y_mean = sum(y_values) / len(y_values)
    denominator = sum((x_value - x_mean) ** 2 for x_value in x_values)
    if denominator == 0.0:
        raise ValueError("cannot calculate a slope from identical x values")
    return sum(
        (x_value - x_mean) * (y_value - y_mean)
        for x_value, y_value in zip(x_values, y_values)
    ) / denominator


def reproduce_observational_summaries() -> tuple[list[dict[str, Any]], dict[str, Any]]:
    rows: list[dict[str, Any]] = []
    for label, path, fission_mass, energy, _, _ in SYSTEMS:
        mass_yield = build_mass_yield(path, energy)
        midpoint = fission_mass / 2.0
        light_centroid, light_mode = centroid_around_mode(mass_yield, 70, int(midpoint))
        heavy_centroid, heavy_mode = centroid_around_mode(mass_yield, int(midpoint) + 1, 175)
        valley = sum(
            mass_yield.get(mass_number, 0.0)
            for mass_number in (math.floor(midpoint), math.ceil(midpoint))
        ) / 2.0
        peak_to_valley = max(mass_yield.values()) / valley if valley else 0.0
        rows.append(
            {
                "system": label,
                "fission_mass": fission_mass,
                "energy": energy,
                "light_mode": light_mode,
                "heavy_mode": heavy_mode,
                "light_centroid": light_centroid,
                "heavy_centroid": heavy_centroid,
                "peak_sum": light_centroid + heavy_centroid,
                "nu_back_computed": fission_mass - (light_centroid + heavy_centroid),
                "valley": valley,
                "peak_to_valley": peak_to_valley,
            }
        )
    fission_masses = [float(row["fission_mass"]) for row in rows]
    heavy_centroids = [float(row["heavy_centroid"]) for row in rows]
    light_centroids = [float(row["light_centroid"]) for row in rows]
    nu_values = [float(row["nu_back_computed"]) for row in rows]
    fast_rows = [row for row in rows if row["energy"] == "fast"]
    thorium_row = next(row for row in rows if row["system"] == "Th-232")
    p1_slope = linear_slope(fission_masses, heavy_centroids)
    p2_slope = linear_slope(fission_masses, light_centroids)
    p3_all_in_range = all(1.5 <= value <= 4.0 for value in nu_values)
    p4_shallowest_valley = thorium_row["valley"] == max(row["valley"] for row in fast_rows)
    p4_lowest_peak_to_valley = thorium_row["peak_to_valley"] == min(
        row["peak_to_valley"] for row in fast_rows
    )
    gates = {
        "p1_heavy_slope": p1_slope,
        "p1_pass": p1_slope < 0.25,
        "p2_light_slope": p2_slope,
        "p2_pass": 0.7 <= p2_slope <= 1.3,
        "p3_nu_min": min(nu_values),
        "p3_nu_max": max(nu_values),
        "p3_all_systems_in_1_5_to_4_0": p3_all_in_range,
        "p4_thorium_shallowest_fast_valley": p4_shallowest_valley,
        "p4_thorium_lowest_fast_peak_to_valley": p4_lowest_peak_to_valley,
        "p4_pass": p4_shallowest_valley and p4_lowest_peak_to_valley,
    }
    return rows, gates


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--output",
        type=Path,
        default=AUDIT_DIRECTORY / "np32_prediction_eligibility_audit_results.json",
    )
    arguments = parser.parse_args()

    static_records, observation_records = verify_inputs()
    source_gate_passed = all(record["passed"] for record in static_records.values()) and all(
        record["passed"] for record in observation_records
    )
    if not source_gate_passed:
        result = {
            "audit_status": "PROVENANCE_BLOCKED",
            "static_inputs": static_records,
            "observational_inputs": observation_records,
            "raw_csv_parsed": False,
        }
        arguments.output.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        return 2

    script_text = STATIC_INPUTS["historical_script"][0].read_text(encoding="utf-8")
    precommit_text = STATIC_INPUTS["precommit"][0].read_text(encoding="utf-8")
    mechanism_audit = audit_historical_script(script_text)
    rows, gates = reproduce_observational_summaries()
    anchor_empirically_imported = all(
        phrase in precommit_text
        for phrase in ("N=82", "Z=50", "measured this session")
    )
    result = {
        "audit_status": "COMPLETE",
        "source_gate": "PASS",
        "static_inputs": static_records,
        "observational_inputs": observation_records,
        "mechanism_audit": mechanism_audit,
        "anchor_audit": {
            "precommit_identifies_N82_Z50_lock_as_measured_this_session": anchor_empirically_imported,
            "anchor_location_status": "ANCHOR_EMPIRICALLY_IMPORTED"
            if anchor_empirically_imported
            else "ANCHOR_SOURCE_NOT_IDENTIFIED",
        },
        "observational_reconstruction": {"rows": rows, "literal_precommit_gates": gates},
        "historical_claim_audit": {
            "p3_historical_status": "PASS",
            "p3_literal_gate_pass": gates["p3_all_systems_in_1_5_to_4_0"],
            "p3_correction": "HISTORICAL_P3_PASS_IS_FALSE_UNDER_ITS_STATED_EVERY_SYSTEM_GATE"
            if not gates["p3_all_systems_in_1_5_to_4_0"]
            else "NO_P3_GATE_CONFLICT",
            "p4_historical_status": "REFUTED",
            "p4_literal_gate_pass": gates["p4_pass"],
        },
        "classification": {
            "predictor_classification": "EMPIRICAL_REGULARITY_SUMMARY_NOT_ZERO_FIT_SDT_PREDICTION",
            "mechanism_classification": "MINIMUM_CUT_MECHANISM_UNIMPLEMENTED",
            "data_feature_status": "IAEA_YIELD_REGULARITY_REPRODUCED",
            "empirical_sdt_verdict": "UNADJUDICATED",
        },
    }
    arguments.output.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
