"""Electron-configuration parsing and deterministic ionisation order."""

from __future__ import annotations

import re
from dataclasses import dataclass

L_INDEX = {"s": 0, "p": 1, "d": 2, "f": 3}
CORE = {
    "He": "1s2",
    "Ne": "1s2 2s2 2p6",
    "Ar": "1s2 2s2 2p6 3s2 3p6",
}


@dataclass(frozen=True)
class SeatLabel:
    n: int
    kind: str
    index: int


def expand_configuration(text: str) -> list[SeatLabel]:
    text = text.strip()
    match = re.match(r"^\[([A-Za-z]+)\](.*)$", text)
    if match:
        core = CORE.get(match.group(1))
        if core is None:
            raise ValueError(f"unsupported core {match.group(1)}")
        text = f"{core} {match.group(2).strip()}"
    seats: list[SeatLabel] = []
    for n_text, kind, count_text in re.findall(r"(\d+)([spdf])(\d+)", text):
        n, count = int(n_text), int(count_text)
        seats.extend(SeatLabel(n, kind, index) for index in range(count))
    return seats


def ionisation_order(seats: list[SeatLabel]) -> list[int]:
    """Indices removed outer n first, then higher subshell letter."""
    return sorted(
        range(len(seats)),
        key=lambda i: (seats[i].n, L_INDEX[seats[i].kind], seats[i].index),
        reverse=True,
    )


def after_removals(seats: list[SeatLabel], count: int) -> list[SeatLabel]:
    removed = set(ionisation_order(seats)[:count])
    return [seat for index, seat in enumerate(seats) if index not in removed]


def promoted(seats: list[SeatLabel]) -> list[SeatLabel]:
    """Promote the outermost seat to the next principal seat of p character."""
    if not seats:
        return []
    order = ionisation_order(seats)
    active = order[0]
    result = list(seats)
    seat = result[active]
    if seat.kind == "s":
        result[active] = SeatLabel(seat.n, "p", seat.index)
    else:
        result[active] = SeatLabel(seat.n + 1, "s", seat.index)
    return result
