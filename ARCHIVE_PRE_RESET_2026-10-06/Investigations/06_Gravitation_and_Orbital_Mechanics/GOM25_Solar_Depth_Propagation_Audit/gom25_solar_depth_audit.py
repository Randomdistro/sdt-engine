#!/usr/bin/env python3
"""Pre-registered GOM25 solar-depth audit using frozen observational inputs only."""

from __future__ import annotations

import math
import re
import statistics
from dataclasses import dataclass
from pathlib import Path


C_METERS_PER_SECOND = 299_792_458.0
AU_METERS = 149_597_870_700.0
NOMINAL_SOLAR_RADIUS_METERS = 695_700_000.0
PHOTOSPHERIC_SOLAR_RADIUS_METERS = 695_658_000.0
PHOTOSPHERIC_SOLAR_RADIUS_SIGMA_METERS = 140_000.0
PUBLISHED_GLOBAL_SHIFT_METERS_PER_SECOND = 638.0
PUBLISHED_GLOBAL_SHIFT_SIGMA_METERS_PER_SECOND = 6.0

RAW_DIRECTORY = Path("Datasets/solar_propagation_2026-08/raw")

EXPECTED_SHA256 = {
    "cassini_sce1_157_tdf.lbl": "b64981fb2c4b2e39d4fdd936753ff0fc11ece50e49c4083756fb620bf6e45081",
    "cassini_sce1_157_tdf.tdf": "354d6904bc19431894a921df4a9f9b8ca95fca7d490a8cb03dd8819f0164be30",
    "cassini_sce1_aareadme.txt": "c90ce316b64d3245d26279b1e371351e3042e7f34f76648d3b934388e976cc15",
    "cassini_sce1_cors0021_cumindex.tab": "25db333fb215c549360af3ac420f22b24b84d05f758fc5419a6edf1810399a00",
    "haberreiter_solar_radius_2008.pdf": "e7251f224e02286bcdce682e820a74d67ba9e0b8590957d156825c7de08c6be8",
    "harps_lfc_cds_ReadMe.txt": "bb134a95206bc832a313cc4eb2e18bea5c43a1d884bb0955b3797fe71fe52372",
    "harps_lfc_solar_redshift_2020.pdf": "3141bb0c56d9c26eb7f540447538a49c1cbe6f030593b145572271fb7a67ca50",
    "harps_lfc_tablea1.dat": "1b662d02add6dcec4457aaa677e42ef567c18ab8ff72b3e07a3b09bdff199a14",
    "harps_lfc_tablea2.dat": "70be075001f8ae8401b5be994eebf42b4c8cac791338d856d957a8531a96ebca",
    "iau_2015_resolution_b3.pdf": "a4a38ecf4ab6ac71a38780456beffbc43c17c98ed320e82585a127057e498417",
    "jpl_horizons_emb_sun_vectors_2025.csv": "99570b90b814143af450892f7ee960ab26baf125f3dde63ab4ff28fd44adc47e",
}


@dataclass(frozen=True)
class StateVector:
    epoch: str
    radius_meters: float
    speed_meters_per_second: float

    @property
    def koppa_meters(self) -> float:
        return self.speed_meters_per_second**2 * self.radius_meters / C_METERS_PER_SECOND**2


@dataclass(frozen=True)
class SpectralLine:
    equivalent_width_milliangstrom: float
    shift_meters_per_second: float
    uncertainty_meters_per_second: float


def verify_frozen_hashes() -> None:
    import hashlib

    missing_or_changed: list[str] = []
    for filename, expected_hash in EXPECTED_SHA256.items():
        path = RAW_DIRECTORY / filename
        if not path.is_file():
            missing_or_changed.append(f"missing {filename}")
            continue
        actual_hash = hashlib.sha256(path.read_bytes()).hexdigest()
        if actual_hash != expected_hash:
            missing_or_changed.append(f"hash mismatch {filename}")
    if missing_or_changed:
        raise RuntimeError("Frozen-input validation failed: " + "; ".join(missing_or_changed))


def parse_horizons_vectors(path: Path) -> list[StateVector]:
    vectors: list[StateVector] = []
    in_data_block = False
    for raw_line in path.read_text(encoding="utf-8").splitlines():
        line = raw_line.strip()
        if line == "$$SOE":
            in_data_block = True
            continue
        if line == "$$EOE":
            break
        if not in_data_block or not line:
            continue
        fields = [field.strip() for field in raw_line.split(",")]
        if len(fields) < 8:
            raise ValueError(f"Unexpected Horizons vector record: {raw_line}")
        coordinates_kilometers = [float(field) for field in fields[2:5]]
        velocities_kilometers_per_second = [float(field) for field in fields[5:8]]
        radius_meters = 1_000.0 * math.sqrt(sum(value**2 for value in coordinates_kilometers))
        speed_meters_per_second = 1_000.0 * math.sqrt(
            sum(value**2 for value in velocities_kilometers_per_second)
        )
        vectors.append(StateVector(fields[1], radius_meters, speed_meters_per_second))
    if len(vectors) < 2:
        raise ValueError("Horizons response has too few vector records")
    return vectors


def parse_harps_strong_lines(path: Path) -> list[SpectralLine]:
    lines: list[SpectralLine] = []
    for raw_line in path.read_text(encoding="utf-8").splitlines():
        if not raw_line.strip():
            continue
        laboratory_wavelength = float(raw_line[0:9])
        nist_wavelength = float(raw_line[10:19])
        equivalent_width = float(raw_line[54:59])
        original_shift = float(raw_line[65:70])
        original_uncertainty = float(raw_line[71:75])
        recalibrated_shift = C_METERS_PER_SECOND * (
            laboratory_wavelength / nist_wavelength
            * (1.0 + original_shift / C_METERS_PER_SECOND)
            - 1.0
        )
        if 150.0 < equivalent_width < 550.0:
            lines.append(
                SpectralLine(equivalent_width, recalibrated_shift, original_uncertainty)
            )
    if len(lines) != 15:
        raise ValueError(f"Expected 15 strong HARPS lines, found {len(lines)}")
    return lines


def parse_harps_global_lines(path: Path) -> list[SpectralLine]:
    lines: list[SpectralLine] = []
    for raw_line in path.read_text(encoding="utf-8").splitlines():
        if not raw_line.strip():
            continue
        equivalent_width = float(raw_line[36:41])
        global_shift = float(raw_line[64:69])
        global_uncertainty = float(raw_line[70:74])
        lines.append(SpectralLine(equivalent_width, global_shift, global_uncertainty))
    if len(lines) != 97:
        raise ValueError(f"Expected 97 global HARPS lines, found {len(lines)}")
    return lines


def arithmetic_summary(values: list[float]) -> tuple[float, float, float]:
    mean_value = statistics.fmean(values)
    sample_standard_deviation = statistics.stdev(values)
    standard_error = sample_standard_deviation / math.sqrt(len(values))
    return mean_value, sample_standard_deviation, standard_error


def weighted_mean(lines: list[SpectralLine]) -> tuple[float, float]:
    weights = [1.0 / line.uncertainty_meters_per_second**2 for line in lines]
    mean_value = sum(weight * line.shift_meters_per_second for weight, line in zip(weights, lines)) / sum(weights)
    return mean_value, math.sqrt(1.0 / sum(weights))


def spectral_prediction(koppa_meters: float, observer_radius_meters: float, solar_radius_meters: float) -> float:
    return C_METERS_PER_SECOND * koppa_meters * (
        1.0 / solar_radius_meters - 1.0 / observer_radius_meters
    )


def delay_integrand(path_coordinate_meters: float, koppa_meters: float, impact_parameter_meters: float) -> float:
    radius_meters = math.hypot(impact_parameter_meters, path_coordinate_meters)
    depth = koppa_meters / radius_meters
    if not 0.0 <= depth < 1.0:
        raise ValueError(f"Profile evaluated outside declared domain: z={depth}")
    return (1.0 / (C_METERS_PER_SECOND * (1.0 - depth) ** 2)) - 1.0 / C_METERS_PER_SECOND


def simpson_delay(
    koppa_meters: float,
    endpoint_one_meters: float,
    endpoint_two_meters: float,
    impact_parameter_meters: float,
    intervals: int,
) -> float:
    if intervals % 2:
        raise ValueError("Simpson integration needs an even interval count")
    path_start = -math.sqrt(endpoint_one_meters**2 - impact_parameter_meters**2)
    path_stop = math.sqrt(endpoint_two_meters**2 - impact_parameter_meters**2)
    spacing = (path_stop - path_start) / intervals
    integral = delay_integrand(path_start, koppa_meters, impact_parameter_meters)
    integral += delay_integrand(path_stop, koppa_meters, impact_parameter_meters)
    for index in range(1, intervals):
        coordinate = path_start + index * spacing
        multiplier = 4.0 if index % 2 else 2.0
        integral += multiplier * delay_integrand(coordinate, koppa_meters, impact_parameter_meters)
    return integral * spacing / 3.0


def validate_cassini_sample() -> tuple[int, int, int]:
    label_path = RAW_DIRECTORY / "cassini_sce1_157_tdf.lbl"
    data_path = RAW_DIRECTORY / "cassini_sce1_157_tdf.tdf"
    label_text = label_path.read_text(encoding="utf-8")
    record_bytes = int(re.search(r"RECORD_BYTES\s+=\s+(\d+)", label_text).group(1))
    file_records = int(re.search(r"FILE_RECORDS\s+=\s+(\d+)", label_text).group(1))
    actual_bytes = data_path.stat().st_size
    if record_bytes * file_records != actual_bytes:
        raise ValueError("Cassini TDF length disagrees with its PDS label")
    return record_bytes, file_records, actual_bytes


def main() -> None:
    verify_frozen_hashes()
    vectors = parse_horizons_vectors(RAW_DIRECTORY / "jpl_horizons_emb_sun_vectors_2025.csv")
    strong_lines = parse_harps_strong_lines(RAW_DIRECTORY / "harps_lfc_tablea1.dat")
    global_lines = parse_harps_global_lines(RAW_DIRECTORY / "harps_lfc_tablea2.dat")

    koppa_values = [vector.koppa_meters for vector in vectors]
    koppa_mean, koppa_standard_deviation, koppa_standard_error = arithmetic_summary(koppa_values)
    koppa_coefficient_of_variation = koppa_standard_deviation / koppa_mean
    predicted_velocities = [
        spectral_prediction(vector.koppa_meters, vector.radius_meters, NOMINAL_SOLAR_RADIUS_METERS)
        for vector in vectors
    ]
    predicted_mean, predicted_standard_deviation, _ = arithmetic_summary(predicted_velocities)
    direct_radius_prediction = statistics.fmean(
        spectral_prediction(vector.koppa_meters, vector.radius_meters, PHOTOSPHERIC_SOLAR_RADIUS_METERS)
        for vector in vectors
    )
    radius_sensitivity = abs(
        spectral_prediction(koppa_mean, statistics.fmean(vector.radius_meters for vector in vectors), PHOTOSPHERIC_SOLAR_RADIUS_METERS)
        - spectral_prediction(
            koppa_mean,
            statistics.fmean(vector.radius_meters for vector in vectors),
            PHOTOSPHERIC_SOLAR_RADIUS_METERS + PHOTOSPHERIC_SOLAR_RADIUS_SIGMA_METERS,
        )
    )

    strong_mean, strong_standard_deviation, strong_standard_error = arithmetic_summary(
        [line.shift_meters_per_second for line in strong_lines]
    )
    global_mean, global_standard_deviation, global_standard_error = arithmetic_summary(
        [line.shift_meters_per_second for line in global_lines]
    )
    global_weighted_mean, global_weighted_error = weighted_mean(global_lines)

    # Formal-only geometry copied from the prior GOM22 test geometry.  It is not an observed delay target.
    endpoint_one_meters = AU_METERS
    endpoint_two_meters = 1.524 * AU_METERS
    impact_parameter_meters = NOMINAL_SOLAR_RADIUS_METERS
    quadrature_values = [
        simpson_delay(koppa_mean, endpoint_one_meters, endpoint_two_meters, impact_parameter_meters, intervals)
        for intervals in (4_096, 16_384, 65_536)
    ]
    exact_one_way_delay = quadrature_values[-1]
    engine_leading_one_way_delay = (
        2.0
        * koppa_mean
        / C_METERS_PER_SECOND
        * math.log(4.0 * endpoint_one_meters * endpoint_two_meters / impact_parameter_meters**2)
    )
    finite_path_leading_one_way_delay = (
        2.0
        * koppa_mean
        / C_METERS_PER_SECOND
        * (
            math.asinh(math.sqrt(endpoint_one_meters**2 - impact_parameter_meters**2) / impact_parameter_meters)
            + math.asinh(math.sqrt(endpoint_two_meters**2 - impact_parameter_meters**2) / impact_parameter_meters)
        )
    )
    inverse_at_two = 1.0 - math.sqrt((1.0 - 2.0) ** 2)
    record_bytes, file_records, cassini_bytes = validate_cassini_sample()

    print("GOM25 — SOLAR DEPTH AND PROPAGATION AUDIT")
    print("===========================================")
    print("frozen inputs: 11/11 SHA-256 verified")
    print()
    print("[D1] JPL HORIZONS EMB-SUN STATE VECTORS")
    print(f"rows: {len(vectors)}; first: {vectors[0].epoch}; last: {vectors[-1].epoch}")
    print(f"koppa mean: {koppa_mean:.9f} m")
    print(f"koppa sample SD: {koppa_standard_deviation:.9f} m; SE: {koppa_standard_error:.9f} m")
    print(f"koppa coefficient of variation: {100.0 * koppa_coefficient_of_variation:.6f}%")
    print("domain finding: instantaneous v^2*r is not constant on this eccentric orbit;")
    print("the simple circular-orbit initial condition is therefore not satisfied by every row.")
    print()
    print("[D3] HARPS-LFC SPECTRAL COMPARATOR")
    print(f"strong-line reconstruction (n={len(strong_lines)}): {strong_mean:.3f} m/s; SD {strong_standard_deviation:.3f}; SE {strong_standard_error:.3f}")
    print(f"3D global table reconstruction (n={len(global_lines)}): {global_mean:.3f} m/s; SD {global_standard_deviation:.3f}; SE {global_standard_error:.3f}")
    print(f"3D global inverse-variance mean: {global_weighted_mean:.3f} +/- {global_weighted_error:.3f} m/s")
    print(f"published processed summary: {PUBLISHED_GLOBAL_SHIFT_METERS_PER_SECOND:.1f} +/- {PUBLISHED_GLOBAL_SHIFT_SIGMA_METERS_PER_SECOND:.1f} m/s")
    print("dependency: 3D photospheric model, laboratory wavelengths, lunar-motion correction, and line selection.")
    print()
    print("[C1] CONDITIONAL DEPTH-DIFFERENTIAL COMPARISON")
    print(f"prediction, nominal IAU radius: {predicted_mean:.3f} m/s; row SD {predicted_standard_deviation:.3f} m/s")
    print(f"prediction, photospheric radius: {direct_radius_prediction:.3f} m/s; +/-140 km radius sensitivity {radius_sensitivity:.3f} m/s")
    print(f"residual to published processed summary: {predicted_mean - PUBLISHED_GLOBAL_SHIFT_METERS_PER_SECOND:+.3f} m/s ({(predicted_mean - PUBLISHED_GLOBAL_SHIFT_METERS_PER_SECOND) / PUBLISHED_GLOBAL_SHIFT_SIGMA_METERS_PER_SECOND:+.3f} source-summary sigma)")
    print("status: UNADJUDICATED — D1 has no uncertainty covariance and violates the unqualified circular initial condition;")
    print("compatibility is reported, but it is not a successful independent prediction.")
    print()
    print("[C_FAR] EXACT-PROFILE MATHEMATICS (FORMAL ONLY)")
    print(f"Simpson one-way delays, 4096/16384/65536 intervals (us): {quadrature_values[0] * 1e6:.9f}, {quadrature_values[1] * 1e6:.9f}, {quadrature_values[2] * 1e6:.9f}")
    print(f"engine leading-order one-way delay (us): {engine_leading_one_way_delay * 1e6:.9f}")
    print(f"finite-path leading-order one-way delay (us): {finite_path_leading_one_way_delay * 1e6:.9f}")
    print(f"exact minus engine leading-order (ns): {(exact_one_way_delay - engine_leading_one_way_delay) * 1e9:+.6f}")
    print("result: c_far=c(1-z)^2 and shapiro_delay() are not exactly the same expression; the latter is leading order.")
    print(f"inverse branch check: depth_from_c_far(c_far(z=2)) returns {inverse_at_two:.1f}, not 2.0")
    print()
    print("[D4] CASSINI RAW TIMING READINESS")
    print(f"sample TDF: {file_records} records * {record_bytes} bytes = {cassini_bytes} bytes (label-consistent)")
    print("status: READY_FOR_DECODER, not a delay result — residual reconstruction still needs full conjunction coverage,")
    print("station clock/ramp calibration, solar-plasma handling, and independently recomputed geometry.")


if __name__ == "__main__":
    main()
