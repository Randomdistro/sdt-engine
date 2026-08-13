#!/usr/bin/env python3
"""Independent formal audit of the proposed stella/cuboct shell relations."""

from __future__ import annotations

import hashlib
import itertools
import json
import math
import re
from collections import Counter, deque
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[3]
ATTACHMENT = Path(
    r"C:\Users\Jimmi\.codex\attachments\2c334dbd-6f69-4b65-8bd9-ac0cc2256307\pasted-text.txt"
)
OUTPUT = Path(__file__).with_name("nseq06_independent_replication_results.json")
AXES = ("x", "y", "z")

SOURCE_SPECS = (
    (
        "external_attached_transcript",
        ATTACHMENT,
        "2827ab8689215237f2eca0e28999b40492bf0e3bf1c59c278feed0551ded053c",
    ),
    (
        "laws_hpp",
        ROOT / "Engine/include/sdt/laws.hpp",
        "64fdb5c17c34138c63426134e96f12cb716085255e300b5a79ebd98ca296d504",
    ),
    (
        "nseq01_assessment",
        ROOT
        / "Investigations/05_Nuclear_Physics/NSEQ01_Sequencer_Rules_Freeze/NSEQ01_ASSESSMENT.md",
        "6c6b6bb628868bfa4b1a6c0f7fc3c99951f9d8618b1008b9c63e433eba2c4541",
    ),
    (
        "nseq02_assessment",
        ROOT
        / "Investigations/05_Nuclear_Physics/NSEQ02_Triton_Shell_Orientation/NSEQ02_ASSESSMENT.md",
        "b6de778bbab32bf299242def8ac5f515cc6fb07d5d98674102e3a2e1c839f467",
    ),
    (
        "nseq03_assessment",
        ROOT
        / "Investigations/05_Nuclear_Physics/NSEQ03_Dual_Tetra_Sequencer_Rewrite/NSEQ03_ASSESSMENT.md",
        "858ffaaaaa1330f792d9fec572b7d607bfb350759ad16abe601ab24c86539fb8",
    ),
    (
        "nseq04_assessment",
        ROOT
        / "Investigations/05_Nuclear_Physics/NSEQ04_Shadow_Union_Kappa/NSEQ04_ASSESSMENT.md",
        "1c438785d305808205c690df0f2afe7440c07ac8b60f39f985e131f51d7be8c0",
    ),
    (
        "nseq05_incidence_script",
        ROOT
        / "Investigations/05_Nuclear_Physics/NSEQ05_Pure_Shell_Incidence/nseq05_pure_shell_incidence.py",
        "953c34bb50e44eb2dfec64eb00189644b7360a72770b451f00bd6b2c79ce3632",
    ),
    (
        "nseq05_stella_script",
        ROOT
        / "Investigations/05_Nuclear_Physics/NSEQ05_Pure_Shell_Stella_Cuboct_Relations/nseq05_pure_shell_stella_cuboct.py",
        "4a91adfc6262876e7902a50554fdb56b12bb676a38aa9af617e7d961db992e92",
    ),
    (
        "np30_results",
        ROOT
        / "Investigations/05_Nuclear_Physics/NP30_Interleaved_Trefoil_Complete/NP30_CONTRACTION_ROOT_AUDIT_RESULTS_2026-08-09.md",
        "ea0967122223f07ebb4565826d193607c499ef943418aa3d68735c0ac0e7aa6b",
    ),
    (
        "np32_results",
        ROOT
        / "Investigations/05_Nuclear_Physics/NP32_Scission_Surface_Selection/NP32_PREDICTION_ELIGIBILITY_AUDIT_RESULTS_2026-08-09.md",
        "493b5b6aef0caffe43e52de786123da81bbffdecfa2672f5255a45ffafe0790a",
    ),
)


def sha256_file(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def source_records() -> tuple[list[dict[str, str]], bool]:
    records: list[dict[str, str]] = []
    all_match = True
    for name, path, expected in SOURCE_SPECS:
        actual = sha256_file(path) if path.is_file() else "MISSING"
        match = actual == expected
        records.append(
            {
                "name": name,
                "path": str(path),
                "expected_sha256": expected,
                "actual_sha256": actual,
                "match": str(match).lower(),
            }
        )
        all_match = all_match and match
    return records, all_match


def parse_constant_array(source: str, identifier: str, length: int) -> list[int]:
    pattern = rf"inline constexpr int {re.escape(identifier)}\[{length}\]\s*=\s*\{{([^}}]+)\}}"
    match = re.search(pattern, source)
    if match is None:
        raise ValueError(f"Cannot find {identifier}[{length}] in laws.hpp")
    values = [int(value) for value in re.findall(r"\d+", match.group(1))]
    if len(values) != length:
        raise ValueError(f"Unexpected {identifier} length: {values}")
    return values


def canonical_edge(first: str, second: str) -> tuple[str, str]:
    return tuple(sorted((first, second)))


def label_triton(signs: tuple[int, int, int]) -> str:
    return "T" + "".join("+" if sign > 0 else "-" for sign in signs)


def label_square(axis_index: int, sign: int) -> str:
    return f"Q{'+' if sign > 0 else '-'}{AXES[axis_index]}"


def histogram(values: list[float]) -> list[dict[str, Any]]:
    counts = Counter(round(value, 12) for value in values)
    return [
        {"latitude_degrees": key, "count": counts[key]}
        for key in sorted(counts)
    ]


def formula_audit(laws_text: str) -> dict[str, Any]:
    deuteron_tiers = parse_constant_array(laws_text, "deuteron_tiers", 5)
    triton_pairs = parse_constant_array(laws_text, "triton_shell_pairs", 4)

    def belt_capacity(index: int) -> int:
        return 2 * (index + 1)

    def surface_remainder(index: int) -> int:
        return index * (index + 1)

    pre_20 = [2, 2 + deuteron_tiers[0], 2 + deuteron_tiers[0] + deuteron_tiers[1]]
    pure_steps = [
        ("T8", 2 * triton_pairs[0]),
        ("D12", deuteron_tiers[2]),
        ("T10", 2 * triton_pairs[1]),
        ("D20", deuteron_tiers[3]),
        ("T12", 2 * triton_pairs[2]),
        ("D30", deuteron_tiers[4]),
        ("T14", 2 * triton_pairs[3]),
        ("D42", surface_remainder(6)),
        ("T16", belt_capacity(7)),
    ]
    cumulative = [20]
    for _, increment in pure_steps:
        cumulative.append(cumulative[-1] + increment)

    grouped_closures = [
        pre_20[0],
        pre_20[1],
        pre_20[2],
        cumulative[1],
        cumulative[3],
        cumulative[5],
        cumulative[7],
    ]
    expected_engine_closures = [2, 8, 20, 28, 50, 82, 126]
    expected_intermediates = [40, 70, 112, 168]
    form_identities = {
        "deuteron_arrays_match_F_or_R": deuteron_tiers
        == [6, 12, surface_remainder(3), surface_remainder(4), surface_remainder(5)],
        "triton_arrays_match_B_3_to_6": [2 * pair for pair in triton_pairs]
        == [belt_capacity(index) for index in range(3, 7)],
        "engine_grouped_closures_match": grouped_closures == expected_engine_closures,
        "claimed_intermediates_match": [cumulative[index] for index in (2, 4, 6, 8)]
        == expected_intermediates,
        "forward_184_match": cumulative[-1] == 184,
    }
    return {
        "deuteron_tiers_from_laws_hpp": deuteron_tiers,
        "triton_pair_counts_from_laws_hpp": triton_pairs,
        "pure_steps_after_20": [{"shell": shell, "increment": increment} for shell, increment in pure_steps],
        "cumulative_after_20": cumulative,
        "engine_grouped_closures": grouped_closures,
        "checks": form_identities,
        "pass": all(form_identities.values()),
        "interpretation": "Algebraic expansion of literals/formulas already encoded in laws.hpp; not an independent observational prediction.",
    }


def stella_cuboct_audit() -> dict[str, Any]:
    cube_vertices = list(itertools.product((-1, 1), repeat=3))
    cube_edges = [
        (first, second)
        for first, second in itertools.combinations(cube_vertices, 2)
        if sum(a != b for a, b in zip(first, second, strict=True)) == 1
    ]
    midpoint_directions = {
        tuple((a + b) // 2 for a, b in zip(first, second, strict=True))
        for first, second in cube_edges
    }
    cuboct_directions: set[tuple[int, int, int]] = set()
    for zero_axis in range(3):
        nonzero_axes = [axis for axis in range(3) if axis != zero_axis]
        for signs in itertools.product((-1, 1), repeat=2):
            direction = [0, 0, 0]
            direction[nonzero_axes[0]] = signs[0]
            direction[nonzero_axes[1]] = signs[1]
            cuboct_directions.add(tuple(direction))
    midpoint_latitudes = [
        math.degrees(math.asin(sum(direction) / math.sqrt(6.0)))
        for direction in midpoint_directions
    ]
    midpoint_counts = Counter(round(value, 12) for value in midpoint_latitudes)
    midpoint_split = {
        "north": sum(count for latitude, count in midpoint_counts.items() if latitude > 0),
        "equator": midpoint_counts.get(0.0, 0),
        "south": sum(count for latitude, count in midpoint_counts.items() if latitude < 0),
    }

    triton_signs = list(itertools.product((-1, 1), repeat=3))
    triangle_normals = {label_triton(signs): signs for signs in triton_signs}
    square_normals = {
        label_square(axis, sign): (axis, sign)
        for axis in range(3)
        for sign in (-1, 1)
    }
    normal_latitudes: list[float] = []
    for signs in triangle_normals.values():
        normal_latitudes.append(math.degrees(math.asin(sum(signs) / 3.0)))
    for _, sign in square_normals.values():
        normal_latitudes.append(math.degrees(math.asin(sign / math.sqrt(3.0))))
    normal_counts = Counter(round(value, 12) for value in normal_latitudes)
    expected_midpoint_split = {"north": 3, "equator": 6, "south": 3}
    expected_normal_count = {
        round(90.0, 12): 1,
        round(-90.0, 12): 1,
        round(math.degrees(math.asin(1.0 / 3.0)), 12): 3,
        round(math.degrees(math.asin(-1.0 / 3.0)), 12): 3,
        round(math.degrees(math.asin(1.0 / math.sqrt(3.0))), 12): 3,
        round(math.degrees(math.asin(-1.0 / math.sqrt(3.0))), 12): 3,
    }
    return {
        "cube_vertex_count": len(cube_vertices),
        "nearest_cube_edge_count": len(cube_edges),
        "midpoint_direction_count": len(midpoint_directions),
        "midpoints_equal_cuboct_directions": midpoint_directions == cuboct_directions,
        "midpoint_latitude_census": histogram(midpoint_latitudes),
        "midpoint_polar_split": midpoint_split,
        "face_normal_count": len(triangle_normals) + len(square_normals),
        "triangle_normal_count": len(triangle_normals),
        "square_normal_count": len(square_normals),
        "face_normal_latitude_census": histogram(normal_latitudes),
        "checks": {
            "cube_has_twelve_nearest_links": len(cube_edges) == 12,
            "midpoint_directions_are_cuboctahedral": midpoint_directions == cuboct_directions,
            "midpoint_split_is_3_6_3": midpoint_split == expected_midpoint_split,
            "face_normals_have_fourteen_distinct_directions": len(triangle_normals) + len(square_normals) == 14,
            "face_normal_latitudes_match": normal_counts == Counter(expected_normal_count),
        },
        "triangle_normals": sorted(triangle_normals),
        "square_normals": sorted(square_normals),
    }


def connected_component_count(nodes: list[str], edges: tuple[tuple[str, str], ...]) -> int:
    neighbours = {node: set() for node in nodes}
    for first, second in edges:
        neighbours[first].add(second)
        neighbours[second].add(first)
    seen: set[str] = set()
    components = 0
    for start in nodes:
        if start in seen:
            continue
        components += 1
        pending = deque([start])
        seen.add(start)
        while pending:
            node = pending.popleft()
            for neighbour in neighbours[node]:
                if neighbour not in seen:
                    seen.add(neighbour)
                    pending.append(neighbour)
    return components


def incidence_graph_audit() -> dict[str, Any]:
    triton_keys = list(itertools.product((-1, 1), repeat=3))
    triton_nodes = {label_triton(signs): signs for signs in triton_keys}
    square_nodes = {
        label_square(axis, sign): (axis, sign)
        for axis in range(3)
        for sign in (-1, 1)
    }
    all_nodes = sorted((*triton_nodes, *square_nodes))
    tq_edges = tuple(
        sorted(
            canonical_edge(triton, label_square(axis, signs[axis]))
            for triton, signs in triton_nodes.items()
            for axis in range(3)
        )
    )
    tt_edges = tuple(
        sorted(
            canonical_edge(first, second)
            for first, first_signs in triton_nodes.items()
            for second, second_signs in triton_nodes.items()
            if first < second
            and sum(a != b for a, b in zip(first_signs, second_signs, strict=True)) == 1
        )
    )
    qq_candidates = tuple(
        sorted(
            canonical_edge(first, second)
            for first, (first_axis, _) in square_nodes.items()
            for second, (second_axis, _) in square_nodes.items()
            if first < second and first_axis != second_axis
        )
    )

    selections: list[tuple[tuple[str, str], ...]] = []
    square_labels = sorted(square_nodes)
    for candidate in itertools.combinations(qq_candidates, 6):
        degree = Counter(node for edge in candidate for node in edge)
        if all(degree[node] == 2 for node in square_labels):
            selections.append(candidate)

    square_lookup = {value: key for key, value in square_nodes.items()}

    def transform_square(label: str, turns: int, invert: bool) -> str:
        axis, sign = square_nodes[label]
        transformed_axis = (axis + turns) % 3
        transformed_sign = -sign if invert else sign
        return square_lookup[(transformed_axis, transformed_sign)]

    def transform_selection(
        selection: tuple[tuple[str, str], ...], turns: int, invert: bool
    ) -> tuple[tuple[str, str], ...]:
        return tuple(
            sorted(
                canonical_edge(
                    transform_square(first, turns, invert),
                    transform_square(second, turns, invert),
                )
                for first, second in selection
            )
        )

    invariant_selections = [
        selection
        for selection in selections
        if all(
            transform_selection(selection, turns, invert) == selection
            for turns in range(3)
            for invert in (False, True)
        )
    ]

    selection_rows = []
    all_full_graphs_valid = True
    for selection in selections:
        full_edges = tuple(sorted((*tq_edges, *tt_edges, *selection)))
        degree = Counter(node for edge in full_edges for node in edge)
        components = connected_component_count(all_nodes, full_edges)
        full_valid = len(full_edges) == 42 and all(degree[node] == 6 for node in all_nodes) and components == 1
        all_full_graphs_valid = all_full_graphs_valid and full_valid
        selection_rows.append(
            {
                "qq_edges": [list(edge) for edge in selection],
                "qq_component_count": connected_component_count(square_labels, selection),
                "qq_is_six_cycle": connected_component_count(square_labels, selection) == 1,
                "invariant_under_c3_times_inversion": selection in invariant_selections,
                "full_edge_count": len(full_edges),
                "full_degree_set": sorted(set(degree.values())),
                "full_component_count": components,
                "full_graph_valid": full_valid,
            }
        )

    invariant_rows = [
        row
        for row in selection_rows
        if row["invariant_under_c3_times_inversion"]
    ]
    six_cycle_invariant_rows = [row for row in invariant_rows if row["qq_is_six_cycle"]]
    invariant_component_counts = sorted(row["qq_component_count"] for row in invariant_rows)
    checks = {
        "tq_edge_count_is_24": len(tq_edges) == 24,
        "tt_edge_count_is_12": len(tt_edges) == 12,
        "qq_candidate_count_is_12": len(qq_candidates) == 12,
        "all_degree_two_qq_selections_enumerated": len(selections) > 0,
        "all_full_graphs_are_connected_six_regular_42_edge": all_full_graphs_valid,
        "c3_inversion_enumeration_complete": len(invariant_rows) > 0,
        "c3_inversion_has_two_branches": len(invariant_rows) == 2,
        "c3_inversion_branch_types_are_cycle_and_triangle_pair": invariant_component_counts == [1, 2],
    }
    return {
        "node_count": len(all_nodes),
        "tq_edges": [list(edge) for edge in tq_edges],
        "tt_edges": [list(edge) for edge in tt_edges],
        "qq_candidates": [list(edge) for edge in qq_candidates],
        "degree_two_qq_selection_count": len(selections),
        "c3_inversion_invariant_selection_count": len(invariant_rows),
        "c3_inversion_invariant_six_cycle_count": len(six_cycle_invariant_rows),
        "selection_rows": selection_rows,
        "checks": checks,
        "simple_surface_planarity_bound": {
            "vertices": len(all_nodes),
            "edges": 42,
            "maximum_planar_simple_edges": 3 * len(all_nodes) - 6,
            "exceeds_bound": 42 > 3 * len(all_nodes) - 6,
        },
        "interpretation": "Under the predeclared C3 times inversion group, exhaustive enumeration gives two Q-Q selections: one six-cycle and one pair of triangles. This is a formal count result, not a physical contact-selection rule.",
    }


def main() -> None:
    sources, sources_match = source_records()
    if not sources_match:
        raise SystemExit("Frozen input mismatch; refusing to produce an audit result.")
    laws_text = (ROOT / "Engine/include/sdt/laws.hpp").read_text(encoding="utf-8")
    formula = formula_audit(laws_text)
    geometry = stella_cuboct_audit()
    incidence = incidence_graph_audit()
    geometry_pass = all(geometry["checks"].values())
    incidence_pass = all(
        incidence["checks"][key]
        for key in (
            "tq_edge_count_is_24",
            "tt_edge_count_is_12",
            "qq_candidate_count_is_12",
            "all_degree_two_qq_selections_enumerated",
            "all_full_graphs_are_connected_six_regular_42_edge",
        )
    )
    result: dict[str, Any] = {
        "audit": "NSEQ06 independent stella/cuboct relation replication",
        "date": "2026-08-09",
        "formal_only": True,
        "script_sha256": sha256_file(Path(__file__)),
        "frozen_sources": sources,
        "formula_audit": formula,
        "geometry_audit": geometry,
        "incidence_graph_audit": incidence,
        "gates": {
            "F1_formula_expansion": "PASS" if formula["pass"] else "FAIL",
            "F2_stella_to_cuboct": "PASS" if all(
                geometry["checks"][key]
                for key in (
                    "cube_has_twelve_nearest_links",
                    "midpoint_directions_are_cuboctahedral",
                    "midpoint_split_is_3_6_3",
                )
            ) else "FAIL",
            "F3_cuboct_to_fourteen_normals": "PASS" if all(
                geometry["checks"][key]
                for key in (
                    "face_normals_have_fourteen_distinct_directions",
                    "face_normal_latitudes_match",
                )
            ) else "FAIL",
            "F4_incidence_enumeration": "PASS" if incidence_pass else "FAIL",
            "F5_d42_simple_surface_topology": "OPEN_NONPLANAR_TOPOLOGY_DEBT"
            if incidence["simple_surface_planarity_bound"]["exceeds_bound"]
            else "FAIL_BOUND_NOT_TRIGGERED",
            "two_branch_statement": "FORMALLY_REPRODUCED_UNDER_C3_X_INVERSION"
            if incidence["checks"]["c3_inversion_has_two_branches"]
            and incidence["checks"]["c3_inversion_branch_types_are_cycle_and_triangle_pair"]
            else "RECOMPUTE_REQUIRED",
        },
        "verdict": "FORMAL_RELATION_REPRODUCED_ONLY"
        if formula["pass"] and geometry_pass and incidence_pass
        else "FORMAL_RELATION_NOT_REPRODUCED",
        "non_conclusions": [
            "No force, occupation, formation, or energy mechanism is derived.",
            "No closure location is independently predicted; the ledger values are existing coded/imported values.",
            "No N184 prediction is established because D42 has a non-planar simple-surface-contact debt and no physical contact-selection rule.",
            "No NP12b boundary-to-RMS map, NP30 closure-root result, NP32 forward split mechanism, or NSEQ04 binding-energy failure is altered.",
            "Astrophysical and particle claims from the attached transcript remain EXTERNAL_TRANSCRIPT_UNVERIFIED without frozen local data and executable analyses.",
        ],
    }
    canonical = json.dumps(result, sort_keys=True, separators=(",", ":"), ensure_ascii=True)
    result["canonical_payload_sha256"] = hashlib.sha256(canonical.encode("utf-8")).hexdigest()
    OUTPUT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    print(json.dumps(result["gates"], sort_keys=True))
    print(result["verdict"])
    print(result["canonical_payload_sha256"])


if __name__ == "__main__":
    main()
