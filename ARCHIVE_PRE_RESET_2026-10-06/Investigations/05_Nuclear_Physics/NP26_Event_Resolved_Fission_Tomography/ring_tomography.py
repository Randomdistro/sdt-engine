"""Exact circular-window tomography for the U-236 Atomicus block order.

No yield fitting is performed here.  The module defines the lossless transform
between a proposed cyclic d/t order and its primary-fragment (A,Z) fingerprint.
Measured *pre-neutron, independent, coincidence* yields can be supplied as a CSV
with columns Z,A,count.  The checker then makes exact integer histogram comparisons.

The inverse relation is:
    q = Z - 2                      number of d/t blocks in the fragment
    t = A - 2*Z                    tritons in that q-window
    d = q - t = 3*Z - A - 2       deuterons in that q-window

For U-236*: 38 zeros (d) and 52 ones (t), length 90.
"""

from __future__ import annotations

import argparse
import csv
from collections import Counter, defaultdict
from pathlib import Path


PARENT_D = 38
PARENT_T = 52
N = PARENT_D + PARENT_T


def canonical_rotation(bits: tuple[int, ...]) -> tuple[int, ...]:
    """Remove the unavoidable rotation/reflection degeneracy."""
    variants = []
    for word in (bits, tuple(reversed(bits))):
        variants.extend(word[i:] + word[:i] for i in range(len(word)))
    return min(variants)


def window_histograms(bits: tuple[int, ...]) -> dict[int, Counter[int]]:
    """Return H[q][t] = number of cyclic q-windows containing t tritons."""
    if len(bits) != N or sum(bits) != PARENT_T:
        raise ValueError(f"U-236 word must contain {PARENT_D} d and {PARENT_T} t")
    doubled = bits + bits
    prefix = [0]
    for bit in doubled:
        prefix.append(prefix[-1] + bit)
    out: dict[int, Counter[int]] = {}
    for q in range(1, N):
        out[q] = Counter(prefix[i + q] - prefix[i] for i in range(N))
    return out


def fragment_fingerprint(bits: tuple[int, ...]) -> Counter[tuple[int, int]]:
    """Map all oriented circular windows to their exact alpha-grammar (A,Z)."""
    fp: Counter[tuple[int, int]] = Counter()
    for q, hist in window_histograms(bits).items():
        z = 2 + q
        for t, count in hist.items():
            a = 2 * z + t
            fp[(z, a)] += count
    return fp


def load_measured_histograms(path: Path) -> dict[int, Counter[int]]:
    """Load integer event counts; evaluated percentages are deliberately rejected."""
    out: dict[int, Counter[int]] = defaultdict(Counter)
    with path.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            z, a = int(row["Z"]), int(row["A"])
            raw = row["count"]
            count = int(raw)
            if str(count) != raw.strip() and float(raw) != count:
                raise ValueError("counts must be raw integer events, not evaluated yields")
            q, t = z - 2, a - 2 * z
            if not (1 <= q < N and 0 <= t <= q):
                raise ValueError(f"invalid alpha-grammar row: Z={z}, A={a}")
            out[q][t] += count
    return dict(out)


def exact_check(bits: tuple[int, ...], measured: dict[int, Counter[int]]) -> list[str]:
    """Compare normalized integer histograms without tolerances or substitutions."""
    predicted = window_histograms(bits)
    errors = []
    for q, observed in sorted(measured.items()):
        # Each start point must be sampled equally for a phase-uniform ring.  Raw
        # exposures may repeat the N-window fingerprint by an integer factor.
        total = sum(observed.values())
        if total % N:
            errors.append(f"q={q}: {total} events is not an integer multiple of {N}")
            continue
        repeats = total // N
        expected = Counter({t: repeats * n for t, n in predicted[q].items()})
        if observed != expected:
            errors.append(f"q={q}: observed {dict(observed)} != expected {dict(expected)}")
    return errors


def demo_word() -> tuple[int, ...]:
    """A deliberately non-physical word used only to self-test the transform."""
    return tuple([0, 1] * 38 + [1] * 14)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--events", type=Path, help="CSV columns Z,A,count")
    args = parser.parse_args()
    bits = canonical_rotation(demo_word())
    fp = fragment_fingerprint(bits)
    assert sum(fp.values()) == N * (N - 1)
    print(f"U-236 ring self-test: {len(bits)} blocks, d={bits.count(0)}, t={sum(bits)}")
    print(f"all oriented proper windows: {sum(fp.values())}; distinct (Z,A): {len(fp)}")
    if args.events:
        failures = exact_check(bits, load_measured_histograms(args.events))
        print("EXACT PASS" if not failures else "EXACT FAIL")
        for failure in failures:
            print(f"  {failure}")
    else:
        print("No event CSV supplied; transform verified, physical inversion not claimed.")


if __name__ == "__main__":
    main()
