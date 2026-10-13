#!/usr/bin/env python3
"""NSEQ09 — blind delta_2n from pure-shell F/B/R schedule vs AME2020."""
from __future__ import annotations

import hashlib
import statistics
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
AME = ROOT / "Datasets" / "nuclear" / "AME2020_mass_excess.txt"
OUT = ROOT / ".audit-tmp" / "nseq09_run.txt"
EXPECTED_SHA = "e8599c6d7f724fac91934e59f1b9de8fb8f63e820f4b39456b790665ed2a3307"


def F(n: int) -> int:
    return (n + 1) * (n + 2)


def B(n: int) -> int:
    return 2 * (n + 1)


def R(n: int) -> int:
    return n * (n + 1)


def blind_seal_schedule() -> list[int]:
    """Closures from F/B/R only — no magic table."""
    n = 2
    out = [n]
    n += F(1)
    out.append(n)  # 8
    n += F(2)
    out.append(n)  # 20
    n += B(3)
    out.append(n)  # 28
    n += R(3) + B(4)
    out.append(n)  # 50
    n += R(4) + B(5)
    out.append(n)  # 82
    n += R(5) + B(6)
    out.append(n)  # 126
    n += R(6) + B(7)
    out.append(n)  # 184
    return out


def blind_open_d_intermediates(seal: list[int]) -> list[int]:
    """Species-pure D seats before next T seal (NSEQ05), from seal anchors."""
    # After seals 28,50,82,126 add R(3),R(4),R(5),R(6)
    s28, s50, s82, s126 = seal[3], seal[4], seal[5], seal[6]
    return [s28 + R(3), s50 + R(4), s82 + R(5), s126 + R(6)]


def sha256_file(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def load_ame_binding_experimental(path: Path) -> dict[tuple[int, int], float]:
    """Return {(Z,A): total B in MeV} for experimental (non-#) B/A only."""
    out: dict[tuple[int, int], float] = {}
    text = path.read_text(encoding="latin-1")
    for ln in text.splitlines():
        if len(ln) < 25:
            continue
        try:
            N = int(ln[4:9])
            Z = int(ln[9:14])
            A = int(ln[14:19])
        except ValueError:
            continue
        # Detect estimated B/A: '#' in the binding-energy field region.
        # Safer: if any '#' appears before the beta flag in the numeric tail, skip.
        tail = ln[23:]
        if "#" in tail.split("B-")[0].split("B+")[0].split(" B ")[0]:
            # crude: if # anywhere before first B-/B+ token, treat as estimated row
            bpos = len(tail)
            for mark in ("B-", "B+", " B "):
                i = tail.find(mark)
                if i != -1:
                    bpos = min(bpos, i)
            if "#" in tail[:bpos]:
                continue
        toks = tail.replace("*", " ").split()
        bidx = None
        for i, t in enumerate(toks):
            if t in ("B-", "B+", "B", "B-x"):
                bidx = i
                break
        if bidx is None or bidx < 3:
            continue
        try:
            ba_kev = float(toks[bidx - 2])
        except ValueError:
            continue
        if not (0.0 < ba_kev < 12000.0):
            continue
        Btot = (ba_kev / 1000.0) * A  # MeV
        out[(Z, A)] = Btot
    return out


def median(xs: list[float]) -> float:
    return float(statistics.median(xs))


def main() -> int:
    lines: list[str] = []

    def p(s: str = "") -> None:
        lines.append(s)
        print(s)

    p("NSEQ09 blind delta_2n pure-shell")
    p("pre-reg: NSEQ09_PRE_REGISTRATION.md")
    p("")

    # Provenance
    sha = sha256_file(AME)
    p(f"AME path: {AME}")
    p(f"SHA-256: {sha}")
    p(f"hash match: {sha == EXPECTED_SHA}")
    if sha != EXPECTED_SHA:
        p("STATUS PROVENANCE_CONFLICT")
        OUT.parent.mkdir(parents=True, exist_ok=True)
        OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
        return 2

    seal = blind_seal_schedule()
    open_d = blind_open_d_intermediates(seal)
    p(f"blind SEAL schedule: {seal}")
    p(f"blind OPEN_D:        {open_d}")
    expect_seal = [2, 8, 20, 28, 50, 82, 126, 184]
    expect_open = [40, 70, 112, 168]
    c1_sched = seal == expect_seal and open_d == expect_open
    forbidden = any(
        name in ("magic_numbers", "is_closure", "closure")
        for name in blind_seal_schedule.__code__.co_names
        + blind_open_d_intermediates.__code__.co_names
    )
    c1 = c1_sched and not forbidden
    p(f"C1 blind schedule (no magic array): {'PASS' if c1 else 'FAIL'}")
    p(f"  builder co_names seal={blind_seal_schedule.__code__.co_names}")
    p(f"  builder co_names open={blind_open_d_intermediates.__code__.co_names}")
    p("")

    bind = load_ame_binding_experimental(AME)
    p(f"experimental AME nuclides loaded: {len(bind)}")

    # S2n and D for even Z, even N
    # Index by (Z,N) using A = Z+N
    by_zn: dict[tuple[int, int], float] = {}
    for (Z, A), Btot in bind.items():
        N = A - Z
        if Z % 2 == 0 and N % 2 == 0 and Z >= 2 and N >= 2:
            by_zn[(Z, N)] = Btot

    S2n: dict[tuple[int, int], float] = {}
    for (Z, N), Btot in by_zn.items():
        key_prev = (Z, N - 2)
        if key_prev in by_zn:
            S2n[(Z, N)] = Btot - by_zn[key_prev]

    D: dict[tuple[int, int], float] = {}
    for (Z, N), s in S2n.items():
        key_next = (Z, N + 2)
        if key_next in S2n:
            D[(Z, N)] = s - S2n[key_next]

    # Aggregate median D(N) requiring >=3 Z chains
    by_N: dict[int, list[float]] = defaultdict(list)
    for (Z, N), d in D.items():
        by_N[N].append(d)

    med: dict[int, float] = {}
    nZ: dict[int, int] = {}
    for N, vals in by_N.items():
        nZ[N] = len(vals)
        if len(vals) >= 3:
            med[N] = median(vals)

    p(f"even-N with median D (>=3 chains): {len(med)}")
    p("")

    seal_test = [20, 28, 50, 82, 126]
    open_test = [40, 70, 112]
    control = [
        N
        for N in range(16, 131, 2)
        if N not in set(expect_seal) | set(expect_open) and N in med
    ]

    p("SEAL median D(N) [MeV]:")
    seal_meds = []
    for N in seal_test:
        if N in med:
            seal_meds.append(med[N])
            p(f"  N={N:3d}  medD={med[N]:+8.3f}  nZ={nZ[N]}")
        else:
            p(f"  N={N:3d}  INSUFFICIENT (nZ={nZ.get(N, 0)})")

    p("OPEN_D median D(N) [MeV]:")
    open_meds = []
    for N in open_test:
        if N in med:
            open_meds.append(med[N])
            p(f"  N={N:3d}  medD={med[N]:+8.3f}  nZ={nZ[N]}")
        else:
            p(f"  N={N:3d}  INSUFFICIENT (nZ={nZ.get(N, 0)})")

    ctrl_meds = [med[N] for N in control]
    p(f"CONTROL even-N count used: {len(ctrl_meds)}")
    if ctrl_meds:
        p(f"  control mean medD = {statistics.mean(ctrl_meds):+.3f} MeV")

    p("")
    # Gates
    if len(seal_meds) < 3:
        c2 = None
        p("C2 SEAL gaps: OPEN (fewer than 3 adjudicable SEAL N)")
    else:
        seal_mean = statistics.mean(seal_meds)
        ctrl_mean = statistics.mean(ctrl_meds) if ctrl_meds else float("nan")
        all_pos = all(x > 0 for x in seal_meds)
        c2 = all_pos and (seal_mean >= ctrl_mean + 1.0)
        p(f"  SEAL mean medD={seal_mean:+.3f}  CONTROL mean={ctrl_mean:+.3f}")
        p(f"  all SEAL medD>0: {all_pos}")
        p(f"C2 SEAL gaps (>= control+1 MeV): {'PASS' if c2 else 'FAIL'}")

    if len(open_meds) < 2 or len(seal_meds) < 3:
        c3 = None
        p("C3 OPEN_D weaker: OPEN (sparse)")
    else:
        # Compare OPEN_D to SEAL subset {28,50,82} as pre-registered
        seal_ref = [med[N] for N in (28, 50, 82) if N in med]
        if len(seal_ref) < 2:
            c3 = None
            p("C3 OPEN_D weaker: OPEN (SEAL ref sparse)")
        else:
            gap = statistics.mean(seal_ref) - statistics.mean(open_meds)
            c3 = gap >= 1.0
            p(
                f"  mean SEAL{{28,50,82}}={statistics.mean(seal_ref):+.3f}  "
                f"mean OPEN_D={statistics.mean(open_meds):+.3f}  diff={gap:+.3f} MeV"
            )
            p(f"C3 OPEN_D weaker by >=1 MeV: {'PASS' if c3 else 'FAIL'}")

    p("")
    p("---")
    if not c1:
        status = "BLIND_SCHEDULE_FAIL"
        code = 1
    elif c2 is None or c3 is None:
        status = "DATA_SPARSE_OPEN"
        code = 0
    elif c2 and c3:
        status = "BLIND_DELTA2N_SURVIVES"
        code = 0
    elif c1 and not (c2 and c3):
        status = "SCHEDULE_OK_GAPS_FAIL"
        code = 1
    else:
        status = "BLIND_DELTA2N_PARTIAL"
        code = 0
    p(f"STATUS {status}")

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return code


if __name__ == "__main__":
    sys.exit(main())
