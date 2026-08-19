#!/usr/bin/env python3
"""Build the editable JSON cases used by the celestial web instrument."""

from __future__ import annotations

import copy
import json
import math
from pathlib import Path
from typing import Callable


ROOT = Path(__file__).resolve().parent
CASES = ROOT / "examples" / "celestial"


def load(name: str) -> dict:
    return json.loads((CASES / name).read_text(encoding="utf-8"))


def write(name: str, value: dict) -> None:
    (CASES / name).write_text(
        json.dumps(value, indent=2) + "\n",
        encoding="utf-8",
        newline="\n",
    )


def rotate_x(vector: list[float], angle: float) -> list[float]:
    x, y, z = vector
    cosine, sine = math.cos(angle), math.sin(angle)
    return [x, cosine * y - sine * z, sine * y + cosine * z]


def rotate_z(vector: list[float], angle: float) -> list[float]:
    x, y, z = vector
    cosine, sine = math.cos(angle), math.sin(angle)
    return [cosine * x - sine * y, sine * x + cosine * y, z]


def transform_vectors(
    case: dict,
    transform: Callable[[list[float]], list[float]],
) -> None:
    for body in case["bodies"]:
        body["position_m"] = transform(body["position_m"])
        body["velocity_m_s"] = transform(body["velocity_m_s"])


def make_case(
    base: dict,
    case_id: str,
    description: str,
    source: str,
) -> dict:
    case = copy.deepcopy(base)
    case["case_id"] = case_id
    case["provenance"] = {
        "classification": "COMPUTED",
        "description": description,
        "sources": [source],
    }
    for body in case["bodies"]:
        body["provenance"]["state"] += f"; transformed for {case_id}"
    return case


def reverse(case: dict) -> None:
    for body in case["bodies"]:
        body["velocity_m_s"] = [-value for value in body["velocity_m_s"]]


def scale_similarity(case: dict, factor: float) -> None:
    velocity_factor = 1 / math.sqrt(factor)
    for body in case["bodies"]:
        body["position_m"] = [factor * value for value in body["position_m"]]
        body["velocity_m_s"] = [
            velocity_factor * value for value in body["velocity_m_s"]
        ]
        body["radius_m"] *= factor
    case["timestep_s"] *= factor**1.5


def mirror_y(case: dict) -> None:
    for body in case["bodies"]:
        body["position_m"][1] *= -1
        body["velocity_m_s"][1] *= -1


def set_hierarchical_runner(
    case: dict,
    position: list[float],
    velocity: list[float],
) -> None:
    runner = case["bodies"][2]
    runner["id"] = "tertiary"
    runner["position_m"] = position
    runner["velocity_m_s"] = velocity
    runner["radius_m"] = 100000
    case["timestep_s"] = 600
    case["record_every_steps"] = 10
    case["max_steps"] = 20000


def set_collinear_eclipse(case: dict, middle_offset_m: float) -> None:
    positions = [
        [-4.0e9, 0, 0],
        [0, middle_offset_m, 0],
        [4.0e9, 0, 0],
    ]
    radii = [4.0e8, 2.0e8, 1.0e8]
    for body, position, radius in zip(case["bodies"], positions, radii):
        body["position_m"] = position
        body["velocity_m_s"] = [0, 0, 0]
        body["radius_m"] = radius
    case["frame"] = {
        "type": "inertial_cartesian",
        "units": "SI",
        "epoch": "t=0",
        "description": "Collinear eclipse-limiting geometry",
    }
    case["timestep_s"] = 10
    case["record_every_steps"] = 1
    case["max_steps"] = 4000


def set_controlled_flyby(
    case: dict,
    relative_position: list[float],
    relative_velocity: list[float],
) -> None:
    earth = case["bodies"][1]
    runner = case["bodies"][2]
    runner["position_m"] = [
        earth["position_m"][axis] + relative_position[axis]
        for axis in range(3)
    ]
    runner["velocity_m_s"] = [
        earth["velocity_m_s"][axis] + relative_velocity[axis]
        for axis in range(3)
    ]
    case["slingshot"]["reference_radius_m"] = math.sqrt(
        sum(value * value for value in relative_position)
    )
    case["slingshot"]["equal_radius_tolerance_m"] = 2.0e7
    case["max_steps"] = 6212


def build() -> None:
    figure_eight = load("figure-eight.sdtcase.json")
    stable = load("stable-lagrange.sdtcase.json")
    restricted = load("restricted-runner.sdtcase.json")
    flyby = load("earth-tail-flyby-controlled.sdtcase.json")

    generated: list[tuple[str, str, dict, str]] = []

    case = make_case(
        figure_eight,
        "mathematical-figure-eight-reversed",
        "Time-reversed equal-baryon figure-eight circulation control.",
        "figure-eight.sdtcase.json",
    )
    reverse(case)
    generated.append(
        ("figure-eight-reversed.sdtcase.json", "Figure-eight · reversed", case, "COMPUTED")
    )

    case = make_case(
        figure_eight,
        "mathematical-figure-eight-inclined-30",
        "Figure-eight rotated thirty degrees out of the reference plane.",
        "figure-eight.sdtcase.json",
    )
    transform_vectors(case, lambda value: rotate_x(value, math.radians(30)))
    generated.append(
        ("figure-eight-inclined-30.sdtcase.json", "Figure-eight · inclined 30°", case, "COMPUTED")
    )

    case = make_case(
        figure_eight,
        "mathematical-figure-eight-rk4",
        "Fixed-RK4 verification of the same retarded-pressure initial state.",
        "figure-eight.sdtcase.json",
    )
    case["integrator"] = "fixed_rk4"
    generated.append(
        ("figure-eight-rk4.sdtcase.json", "Figure-eight · RK4 verification", case, "COMPUTED")
    )

    case = make_case(
        figure_eight,
        "mathematical-figure-eight-translated",
        "Translated and uniformly boosted covariance control.",
        "figure-eight.sdtcase.json",
    )
    for body in case["bodies"]:
        body["position_m"] = [
            body["position_m"][0] + 4.0e9,
            body["position_m"][1] - 3.0e9,
            body["position_m"][2] + 2.0e9,
        ]
        body["velocity_m_s"] = [
            body["velocity_m_s"][0] + 12,
            body["velocity_m_s"][1] - 5,
            body["velocity_m_s"][2] + 3,
        ]
    generated.append(
        ("figure-eight-translated.sdtcase.json", "Figure-eight · translated frame", case, "COMPUTED")
    )

    case = make_case(
        figure_eight,
        "mathematical-figure-eight-rotated-90",
        "Ninety-degree rotational covariance control.",
        "figure-eight.sdtcase.json",
    )
    transform_vectors(case, lambda value: rotate_z(value, math.pi / 2))
    generated.append(
        ("figure-eight-rotated-90.sdtcase.json", "Figure-eight · rotated 90°", case, "COMPUTED")
    )

    case = make_case(
        stable,
        "mathematical-stable-lagrange-reversed",
        "Reversed unequal-baryon rotating-triangle control.",
        "stable-lagrange.sdtcase.json",
    )
    reverse(case)
    generated.append(
        ("stable-lagrange-reversed.sdtcase.json", "Lagrange triangle · reversed", case, "COMPUTED")
    )

    case = make_case(
        stable,
        "mathematical-stable-lagrange-inclined-45",
        "Unequal-baryon rotating triangle inclined forty-five degrees.",
        "stable-lagrange.sdtcase.json",
    )
    transform_vectors(case, lambda value: rotate_x(value, math.pi / 4))
    generated.append(
        ("stable-lagrange-inclined-45.sdtcase.json", "Lagrange triangle · inclined 45°", case, "COMPUTED")
    )

    case = make_case(
        stable,
        "mathematical-stable-lagrange-compact",
        "Half-scale similarity control with corresponding speed and timestep scaling.",
        "stable-lagrange.sdtcase.json",
    )
    scale_similarity(case, 0.5)
    generated.append(
        ("stable-lagrange-compact.sdtcase.json", "Lagrange triangle · compact", case, "COMPUTED")
    )

    case = make_case(
        restricted,
        "mathematical-restricted-l5-runner",
        "L5 mirror of the registered restricted L4 runner.",
        "restricted-runner.sdtcase.json",
    )
    mirror_y(case)
    generated.append(
        ("restricted-runner-l5.sdtcase.json", "Restricted L5 runner", case, "COMPUTED")
    )

    case = make_case(
        restricted,
        "mathematical-restricted-runner-inclined-30",
        "Restricted runner geometry inclined thirty degrees.",
        "restricted-runner.sdtcase.json",
    )
    transform_vectors(case, lambda value: rotate_x(value, math.radians(30)))
    generated.append(
        ("restricted-runner-inclined-30.sdtcase.json", "Restricted runner · inclined 30°", case, "COMPUTED")
    )

    case = make_case(
        stable,
        "mathematical-hierarchical-triple-compact",
        "Inner unequal binary with a computed compact tertiary state.",
        "stable-lagrange.sdtcase.json",
    )
    set_hierarchical_runner(case, [0, 6.0e9, 5.0e8], [-160, 0, 20])
    generated.append(
        ("hierarchical-triple-compact.sdtcase.json", "Hierarchical triple · compact", case, "COMPUTED")
    )

    case = make_case(
        stable,
        "mathematical-hierarchical-triple-wide",
        "Inner unequal binary with a computed wide tertiary state.",
        "stable-lagrange.sdtcase.json",
    )
    set_hierarchical_runner(case, [0, 2.0e10, 4.0e9], [-80, 0, 10])
    generated.append(
        ("hierarchical-triple-wide.sdtcase.json", "Hierarchical triple · wide", case, "COMPUTED")
    )

    case = make_case(
        stable,
        "mathematical-collinear-partial-eclipse",
        "Offset collinear geometry for partial eclipse attenuation.",
        "stable-lagrange.sdtcase.json",
    )
    set_collinear_eclipse(case, 5.0e8)
    generated.append(
        ("collinear-partial-eclipse.sdtcase.json", "Collinear eclipse · partial", case, "COMPUTED")
    )

    case = make_case(
        stable,
        "mathematical-collinear-total-eclipse",
        "Coaxial collinear geometry for total-eclipse limiting behaviour.",
        "stable-lagrange.sdtcase.json",
    )
    set_collinear_eclipse(case, 0)
    generated.append(
        ("collinear-total-eclipse.sdtcase.json", "Collinear eclipse · totality", case, "COMPUTED")
    )

    case = make_case(
        flyby,
        "earth-tail-flyby-down-tail",
        "Controlled runner enters from the anti-solar tail direction.",
        "earth-tail-flyby-controlled.sdtcase.json",
    )
    set_controlled_flyby(
        case,
        [318550000.0, 12742000.0, 0.0],
        [-10000.0, 0.0, 0.0],
    )
    generated.append(
        ("earth-tail-flyby-down-tail.sdtcase.json", "Earth flyby · down-tail", case, "PENDING")
    )

    case = make_case(
        flyby,
        "earth-tail-flyby-sunward",
        "Controlled runner enters from the sunward direction.",
        "earth-tail-flyby-controlled.sdtcase.json",
    )
    set_controlled_flyby(
        case,
        [-318550000.0, 12742000.0, 0.0],
        [10000.0, 0.0, 0.0],
    )
    generated.append(
        ("earth-tail-flyby-sunward.sdtcase.json", "Earth flyby · sunward", case, "PENDING")
    )

    case = make_case(
        flyby,
        "earth-tail-flyby-mirrored",
        "Sunward-offset mirror of the controlled transverse flyby.",
        "earth-tail-flyby-controlled.sdtcase.json",
    )
    set_controlled_flyby(
        case,
        [-12742000.0, -318550000.0, 0.0],
        [0.0, 10000.0, 0.0],
    )
    generated.append(
        ("earth-tail-flyby-mirrored.sdtcase.json", "Earth flyby · mirrored", case, "PENDING")
    )

    case = make_case(
        flyby,
        "earth-tail-stage-scan",
        "Single-step n=0 through n=8 conserved angular-concentration scan.",
        "earth-tail-flyby-controlled.sdtcase.json",
    )
    case["max_steps"] = 1
    case["record_every_steps"] = 1
    generated.append(
        ("earth-tail-stage-scan.sdtcase.json", "Earth tail · stage scan n=0…8", case, "PENDING")
    )

    for filename, _, value, _ in generated:
        write(filename, value)

    catalog = {
        "schema": "sdt-celestial-preset-catalog-1.0.0",
        "count": 25,
        "presets": [
            {
                "id": "jpl-sun-earth-moon",
                "label": "Sun · Earth · Moon (DE441 J2000)",
                "file": "jpl-sun-earth-moon-j2000.sdtcase.json",
                "classification": "OBSERVED comparison",
            },
            {
                "id": "sun-earth-spacecraft",
                "label": "Sun · Earth · L1 spacecraft",
                "file": "sun-earth-spacecraft.sdtcase.json",
                "classification": "COMPUTED",
            },
            {
                "id": "sun-jupiter-trojan",
                "label": "Sun · Jupiter · L4 Trojan",
                "file": "sun-jupiter-trojan.sdtcase.json",
                "classification": "COMPUTED",
            },
            {
                "id": "restricted-l4",
                "label": "Restricted L4 runner",
                "file": "restricted-runner.sdtcase.json",
                "classification": "DERIVED",
            },
            {
                "id": "stable-lagrange",
                "label": "Unequal Lagrange triangle",
                "file": "stable-lagrange.sdtcase.json",
                "classification": "DERIVED",
            },
            {
                "id": "figure-eight",
                "label": "Equal-baryon figure-eight",
                "file": "figure-eight.sdtcase.json",
                "classification": "DERIVED",
            },
            {
                "id": "earth-tail-flyby-controlled",
                "label": "Earth flyby · controlled transverse",
                "file": "earth-tail-flyby-controlled.sdtcase.json",
                "classification": "PENDING",
            },
        ]
        + [
            {
                "id": filename.removesuffix(".sdtcase.json"),
                "label": label,
                "file": filename,
                "classification": classification,
            }
            for filename, label, _, classification in generated
        ],
    }
    if len(catalog["presets"]) != catalog["count"]:
        raise RuntimeError("catalog count does not match generated presets")
    write("catalog.json", catalog)
    print(f"Generated {catalog['count']} celestial simulations in {CASES}")


if __name__ == "__main__":
    build()
