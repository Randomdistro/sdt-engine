#!/usr/bin/env python3
"""No-fit local-K robustness rerun of GOM37's Cassini amplitude gate."""

from __future__ import annotations

import hashlib
import importlib.util
import json
import math
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]
GOM37_INSTRUMENT = ROOT / (
    "Investigations/06_Gravitation_and_Orbital_Mechanics/"
    "GOM37_Multiday_Detrended_Solar_K_Residual/gom37_multiday_detrended.py"
)
GOM39_ASSESSMENT = ROOT / (
    "Investigations/06_Gravitation_and_Orbital_Mechanics/"
    "GOM39_Local_k_Solar_K_Definition/GOM39_ASSESSMENT.md"
)
OUTPUT = ROOT / (
    "Investigations/06_Gravitation_and_Orbital_Mechanics/"
    "GOM40_Local_K_Amplitude_Robustness/gom40_results.json"
)

FROZEN_HASHES = {
    "gom37_instrument": (
        GOM37_INSTRUMENT,
        "c805f0bec605c59aa6ba875771493d3efe582991f297b51471dae8322e199da6",
        "FROZEN_ANALYSIS_INSTRUMENT",
    ),
    "gom39_assessment": (
        GOM39_ASSESSMENT,
        "fb7292f298a86c395bacb46c1d7fa1f871bfe6aa3c84f400ff49f27f5d2d76bc",
        "FROZEN_LOCAL_K_SOURCE",
    ),
    "odf_157": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/sce1_157/odf/c32easc2002_157_0000k252v0.odf",
        "c2ea51d9b5e795bd3eb9b4f1c5174cc44325080623188dce5e01c0ea914bfaf7",
        "PRIMARY_TRACKING_BYTES",
    ),
    "label_157": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/sce1_157/odf/c32easc2002_157_0000k252v0.lbl",
        "b27da74ca62187475860e8214c2b76b8b69af760bbe44d27aac93d1c1a5593bf",
        "PRODUCT_LABEL",
    ),
    "odf_158": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/sce1_158/odf/c32easc2002_158_0000k252v0.odf",
        "9393717f29f5853cb65cd2b1b40b2e411a0d114e326e9d3c3fa1b1b359bc93a4",
        "PRIMARY_TRACKING_BYTES",
    ),
    "label_158": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/sce1_158/odf/c32easc2002_158_0000k252v0.lbl",
        "3ec4a042de7313524674563723c35526bb9eede27153d4ba060172d2a57d4bf7",
        "PRODUCT_LABEL",
    ),
    "odf_159": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/sce1_159/odf/c32easc2002_159_0000k252v0.odf",
        "cfcba02622502887d48dea3e4079d8b9d6fd0a4120b069e8ddeccc9be7683288",
        "PRIMARY_TRACKING_BYTES",
    ),
    "label_159": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/sce1_159/odf/c32easc2002_159_0000k252v0.lbl",
        "446621ccba2c0064b0c5fac4d9d8885eddedd41867b6149ac429220f74a3cba6",
        "PRODUCT_LABEL",
    ),
    "odf_160": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/sce1_160/odf/c32easc2002_160_0000k252v0.odf",
        "7f447ba5952d6ae85d33ed74f16458a2319e2e88dca38912d5f4d99b6a344ab9",
        "PRIMARY_TRACKING_BYTES",
    ),
    "label_160": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/sce1_160/odf/c32easc2002_160_0000k252v0.lbl",
        "63c3de17bade5b4a5a8fd6c7dc25d2c1c61c347444f2062d4c81653a0662077b",
        "PRODUCT_LABEL",
    ),
    "dss25_range_rate": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157_160.csv",
        "658021f99e35f77679c9227302c2fabe7a5150b2197aed8f42870536df1fa4ac",
        "PROCESSED_GEOMETRY",
    ),
    "cassini_heliocentric": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_heliocentric_2002_157_160.csv",
        "948c46b6c7447c97739134990c034e97aaf69afc5d8d1b94bb55f6e4d49a0e06",
        "PROCESSED_GEOMETRY",
    ),
    "earth_heliocentric": (
        ROOT
        / "Datasets/solar_propagation_2026-08/raw/jpl_horizons_earth_heliocentric_2002_157_160.csv",
        "3950bf02bdcb9f8d471a8a389dae8fd169db2966f281e784073e3be5b65b734c",
        "PROCESSED_GEOMETRY",
    ),
}
K_CASES_M = {
    "GOM37_FROZEN": 1476.350,
    "GOM39_LOCAL_EARTH_PROXY": 1455.637,
}
AMPLITUDE_LIMIT = 100.0
CONFOUND_MARGIN = 0.05


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def verified_sources() -> dict[str, dict[str, str | bool]]:
    results = {}
    for name, (path, expected_hash, evidence_class) in FROZEN_HASHES.items():
        actual_hash = sha256(path)
        results[name] = {
            "path": str(path.relative_to(ROOT)).replace("\\", "/"),
            "sha256": actual_hash,
            "hash_matches_pre_registration": actual_hash == expected_hash,
            "evidence_class": evidence_class,
        }
    return results


def load_gom37_instrument():
    module_spec = importlib.util.spec_from_file_location("gom37_frozen", GOM37_INSTRUMENT)
    if module_spec is None or module_spec.loader is None:
        raise RuntimeError("unable to load frozen GOM37 instrument")
    module = importlib.util.module_from_spec(module_spec)
    module_spec.loader.exec_module(module)
    return module


def derivative_per_meter(series: list[dict]) -> None:
    for point_index, point in enumerate(series):
        if 0 < point_index < len(series) - 1:
            prior_point = series[point_index - 1]
            next_point = series[point_index + 1]
        elif point_index == 0:
            prior_point = series[0]
            next_point = series[1]
        else:
            prior_point = series[-2]
            next_point = series[-1]
        elapsed_s = (next_point["time"] - prior_point["time"]).total_seconds()
        point["delay_rate_per_meter"] = (
            (next_point["delay_per_meter"] - prior_point["delay_per_meter"])
            / elapsed_s
            if elapsed_s
            else 0.0
        )


def case_metrics(
    instrument, test_series: list[dict], residual: list[float], solar_k_m: float
) -> dict[str, float | bool]:
    delay_rates = [point["delay_rate_per_meter"] * solar_k_m for point in test_series]
    proxy_hz = [
        point["reference_frequency_hz"] * delay_rates[index]
        for index, point in enumerate(test_series)
    ]
    median_proxy_hz = instrument.median([abs(value) for value in proxy_hz])
    amplitude_ratio = instrument.stdev(residual) / max(median_proxy_hz, 1e-30)
    correlation_delay_rate = instrument.corr(residual, delay_rates)
    time_s = [point["time_s"] for point in test_series]
    correlation_time = instrument.corr(residual, time_s)
    time_confounded = abs(correlation_time) >= abs(correlation_delay_rate) - CONFOUND_MARGIN
    amplitude_pass = amplitude_ratio < AMPLITUDE_LIMIT
    return {
        "solar_k_m": solar_k_m,
        "median_abs_proxy_hz": median_proxy_hz,
        "amplitude_ratio": amplitude_ratio,
        "correlation_residual_delay_rate": correlation_delay_rate,
        "correlation_residual_time": correlation_time,
        "time_confounded": time_confounded,
        "amplitude_gate_pass": amplitude_pass,
        "clears_both_gates": amplitude_pass and not time_confounded,
    }


def main() -> None:
    source_results = verified_sources()
    if not all(item["hash_matches_pre_registration"] for item in source_results.values()):
        raise RuntimeError("frozen source hash mismatch; numeric fields were not parsed")
    if "1455.637 m" not in GOM39_ASSESSMENT.read_text(encoding="utf-8"):
        raise RuntimeError("frozen GOM39 assessment does not supply the registered local-K value")

    instrument = load_gom37_instrument()
    dss_rows = instrument.parse_dss(instrument.DSS_CSV)
    cassini_rows = instrument.parse_vectors(instrument.HELIO_CAS)
    earth_rows = instrument.parse_vectors(instrument.HELIO_EAR)
    series = []
    for day_directory, stem, day_of_year in instrument.K252:
        odf_path = instrument.VOLUME / day_directory / "odf" / f"{stem}.odf"
        label_path = instrument.VOLUME / day_directory / "odf" / f"{stem}.lbl"
        label_text = label_path.read_text(encoding="ascii", errors="replace")
        start_record, end_record = instrument.label_bounds(label_text)
        odf_bytes = odf_path.read_bytes()
        selected_records = []
        for record_index in range(start_record, end_record):
            record = instrument.parse_row(
                odf_bytes[
                    record_index * instrument.REC : (record_index + 1) * instrument.REC
                ]
            )
            if record["data_type"] != 12 or record["rx"] != 25:
                continue
            selected_records.append(record)
        for record in selected_records[::60]:
            station_range_rate = instrument.interp_rdot(dss_rows, record["time"])
            geometric_frequency = (
                -2.0
                * (station_range_rate / instrument.C)
                * record["f_ref_hz"]
            )
            earth_position = instrument.interp_vec(earth_rows, record["time"])
            cassini_position = instrument.interp_vec(cassini_rows, record["time"])
            impact_parameter_m, delay_per_meter = instrument.impact_delay(
                earth_position, cassini_position, 1.0
            )
            series.append(
                {
                    "time": record["time"],
                    "day_of_year": day_of_year,
                    "observable_hz": record["obs_hz"],
                    "geometric_frequency_hz": geometric_frequency,
                    "reference_frequency_hz": record["f_ref_hz"],
                    "impact_parameter_m": impact_parameter_m,
                    "delay_per_meter": delay_per_meter,
                }
            )

    series.sort(key=lambda point: point["time"])
    if len(series) < 20:
        raise RuntimeError("insufficient frozen K252 samples")
    derivative_per_meter(series)
    train_series = [point for point in series if point["day_of_year"] == 157]
    test_series = [
        point for point in series if point["day_of_year"] in (158, 159, 160)
    ]
    if len(train_series) < 10 or len(test_series) < 10:
        raise RuntimeError("registered train/test split is unavailable")

    geometric_scale = instrument.median(
        [
            point["observable_hz"] / point["geometric_frequency_hz"]
            for point in train_series
            if abs(point["geometric_frequency_hz"]) > 1.0
        ]
    )
    time_zero = train_series[0]["time"]
    train_residual = [
        point["observable_hz"]
        - geometric_scale * point["geometric_frequency_hz"]
        for point in train_series
    ]
    train_time_s = [
        (point["time"] - time_zero).total_seconds() for point in train_series
    ]
    trend_intercept, trend_slope = instrument.linfit(train_time_s, train_residual)
    residual = []
    for point in test_series:
        point["time_s"] = (point["time"] - time_zero).total_seconds()
        raw_residual = (
            point["observable_hz"]
            - geometric_scale * point["geometric_frequency_hz"]
        )
        residual.append(
            raw_residual - (trend_intercept + trend_slope * point["time_s"]))

    cases = {
        name: case_metrics(instrument, test_series, residual, solar_k_m)
        for name, solar_k_m in K_CASES_M.items()
    }
    baseline = cases["GOM37_FROZEN"]
    local_case = cases["GOM39_LOCAL_EARTH_PROXY"]
    expected_proxy_ratio = K_CASES_M["GOM39_LOCAL_EARTH_PROXY"] / K_CASES_M["GOM37_FROZEN"]
    observed_proxy_ratio = (
        local_case["median_abs_proxy_hz"] / baseline["median_abs_proxy_hz"]
    )
    linear_scaling_pass = math.isclose(
        expected_proxy_ratio, observed_proxy_ratio, rel_tol=1e-12, abs_tol=0.0
    )
    classification = (
        "REOPEN_FOR_DEFINED_OBSERVABLE"
        if any(case["clears_both_gates"] for case in cases.values())
        else "LOCAL_K_REPAIR_DOES_NOT_CLEAR_GOM37_GATES"
    )
    result = {
        "audit_date": "2026-08-09",
        "source_hashes_valid": True,
        "source_results": source_results,
        "sample_counts": {
            "total": len(series),
            "train_day_157": len(train_series),
            "test_days_158_to_160": len(test_series),
        },
        "fixed_residual_construction": {
            "geometric_scale_train_only": geometric_scale,
            "trend_intercept_hz": trend_intercept,
            "trend_slope_hz_per_s": trend_slope,
            "test_residual_stdev_hz": instrument.stdev(residual),
        },
        "cases": cases,
        "linear_k_scaling": {
            "expected_proxy_ratio": expected_proxy_ratio,
            "observed_proxy_ratio": observed_proxy_ratio,
            "exact_within_registered_tolerance": linear_scaling_pass,
        },
        "classification": classification,
        "observable_definition_status": "ODF_SCALE_AND_IF_UNRESOLVED",
        "empirical_sdt_verdict": "UNADJUDICATED",
        "no_fit_parameters": [
            "solar_k",
            "geometric_scale",
            "linear_detrend",
            "phase",
            "media",
            "ramp",
            "intermediate_frequency",
        ],
        "fail_closed_reason": (
            "The local-K sensitivity case does not itself validate the ODF observable "
            "definition or processed geometry; a physical verdict is prohibited."
        ),
    }
    OUTPUT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    print(json.dumps(result, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
