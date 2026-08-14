"""Parse measured term labels into complete lower and upper seat states."""

from __future__ import annotations

import re
from collections import Counter
from dataclasses import dataclass

from .configurations import L_INDEX, SeatLabel

SUPERSCRIPT_DIGITS = dict(zip("⁰¹²³⁴⁵⁶⁷⁸⁹", "0123456789"))


@dataclass(frozen=True)
class TransitionStates:
    lower: list[SeatLabel]
    upper: list[SeatLabel]
    lower_active_index: int
    upper_active_index: int
    removed_subshell: tuple[int, str]
    added_subshell: tuple[int, str]


def occupancy(seats: list[SeatLabel]) -> Counter[tuple[int, str]]:
    return Counter((seat.n, seat.kind) for seat in seats)


def parse_fragment(text: str) -> Counter[tuple[int, str]]:
    normal = "".join(
        f"^{SUPERSCRIPT_DIGITS[char]};" if char in SUPERSCRIPT_DIGITS else char
        for char in text
    )
    result: Counter[tuple[int, str]] = Counter()
    for n_text, kind, count_text in re.findall(
        r"(\d+)([spdf])(?:\^(\d+);)?", normal
    ):
        result[(int(n_text), kind)] += int(count_text) if count_text else 1
    if not result:
        raise ValueError(f"no occupied subshell in {text!r}")
    return result


def seats_from_occupancy(counts: Counter[tuple[int, str]]) -> list[SeatLabel]:
    seats = []
    for (n, kind), count in sorted(
        counts.items(), key=lambda item: (item[0][0], L_INDEX[item[0][1]])
    ):
        if count < 0:
            raise ValueError(f"negative occupancy for {n}{kind}")
        seats.extend(SeatLabel(n, kind, index) for index in range(count))
    return seats


def _changed_subshell(
    before: Counter[tuple[int, str]],
    after: Counter[tuple[int, str]],
    sign: int,
) -> tuple[int, str]:
    changes = []
    for key in set(before) | set(after):
        difference = after[key] - before[key]
        if difference * sign > 0:
            changes.extend([key] * abs(difference))
    if len(changes) != 1:
        raise ValueError(f"transition must move one seat, got {changes}")
    return changes[0]


def build_transition(
    ground: list[SeatLabel],
    transition: str,
) -> TransitionStates:
    if "→" not in transition:
        raise ValueError(f"missing transition arrow in {transition!r}")
    lower_text, upper_text = transition.split("→", 1)
    ground_counts = occupancy(ground)
    lower_fragment = parse_fragment(lower_text)
    upper_fragment = parse_fragment(upper_text)
    for key, count in lower_fragment.items():
        if count > ground_counts[key]:
            raise ValueError(
                f"lower fragment {lower_text!r} exceeds ground occupancy {key}"
            )
    upper_counts = ground_counts.copy()
    upper_counts.subtract(lower_fragment)
    upper_counts.update(upper_fragment)
    if sum(upper_counts.values()) != sum(ground_counts.values()):
        raise ValueError(f"electron count changed in {transition!r}")
    removed = _changed_subshell(ground_counts, upper_counts, -1)
    added = _changed_subshell(ground_counts, upper_counts, +1)
    lower = seats_from_occupancy(ground_counts)
    upper = seats_from_occupancy(upper_counts)
    lower_active = max(
        index for index, seat in enumerate(lower)
        if (seat.n, seat.kind) == removed
    )
    upper_active = max(
        index for index, seat in enumerate(upper)
        if (seat.n, seat.kind) == added
    )
    return TransitionStates(
        lower, upper, lower_active, upper_active, removed, added,
    )


def build_hlike(lower_n: int, upper_n: int) -> TransitionStates:
    lower = [SeatLabel(lower_n, "s", 0)]
    upper = [SeatLabel(upper_n, "p", 0)]
    return TransitionStates(
        lower, upper, 0, 0, (lower_n, "s"), (upper_n, "p"),
    )
