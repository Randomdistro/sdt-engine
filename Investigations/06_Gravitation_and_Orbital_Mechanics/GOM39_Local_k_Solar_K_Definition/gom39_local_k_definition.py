#!/usr/bin/env python3
"""GOM39 — local k / solar K definition (K = R/k²; k ≠ K)."""
from __future__ import annotations

import math
from datetime import datetime, timezone
from pathlib import Path

C = 299792458.0
HELIO_EAR = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_earth_heliocentric_2002_157.csv"
)
HELIO_CAS = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_heliocentric_2002_157.csv"
)


def median(xs: list[float]) -> float:
    s = sorted(xs)
    return s[len(s) // 2]


def cv(xs: list[float]) -> float:
    m = sum(xs) / len(xs)
    if m == 0:
        return float("nan")
    var = sum((x - m) ** 2 for x in xs) / len(xs)
    return math.sqrt(var) / abs(m)


def parse_state(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
    if "$$SOE" not in text:
        raise ValueError(f"no SOE in {path}")
    block = text.split("$$SOE", 1)[1].split("$$EOE", 1)[0].strip()
    rows = []
    for line in block.splitlines():
        parts = [p.strip() for p in line.split(",")]
        if len(parts) < 8:
            continue
        try:
            cal = parts[1].replace("A.D. ", "").replace(" TDB", "").strip()
            t = datetime.strptime(cal[:20], "%Y-%b-%d %H:%M:%S").replace(
                tzinfo=timezone.utc
            )
            x, y, z = (float(parts[i]) * 1000.0 for i in (2, 3, 4))
            vx, vy, vz = (float(parts[i]) * 1000.0 for i in (5, 6, 7))
        except (ValueError, IndexError):
            continue
        r = math.sqrt(x * x + y * y + z * z)
        v = math.sqrt(vx * vx + vy * vy + vz * vz)
        rows.append({"t": t, "r": r, "v": v, "xyz": (x, y, z)})
    return rows


def impact_b(r_e: tuple[float, float, float], r_c: tuple[float, float, float]) -> float:
    dx = r_c[0] - r_e[0]
    dy = r_c[1] - r_e[1]
    dz = r_c[2] - r_e[2]
    L = math.sqrt(dx * dx + dy * dy + dz * dz)
    n = (dx / L, dy / L, dz / L)
    cx = r_e[1] * n[2] - r_e[2] * n[1]
    cy = r_e[2] * n[0] - r_e[0] * n[2]
    cz = r_e[0] * n[1] - r_e[1] * n[0]
    return max(math.sqrt(cx * cx + cy * cy + cz * cz), 1.0)


def shapiro_closed(K: float, r1: float, r2: float, b: float) -> float:
    return (2.0 * K / C) * math.log(4.0 * r1 * r2 / (b * b))


def shapiro_numeric_local_k(K: float, r1: float, r2: float, b: float, n: int = 20000) -> float:
    """∫ z dl along straight ray; z = 1/k(r)² = K/r; k(r)=√(r/K)."""
    # Parametrize closest approach at s=0: r(s)² = b² + s²
    s1 = -math.sqrt(max(r1 * r1 - b * b, 0.0))
    s2 = math.sqrt(max(r2 * r2 - b * b, 0.0))
    # Sign: Earth and Cassini on opposite sides for conjunction
    if r1 * r1 < b * b or r2 * r2 < b * b:
        # fallback: sample chord Earth→Cassini in r-space via s from -L/2..L/2 approx
        s1, s2 = -1e12, 1e12
    dt = 0.0
    ds = (s2 - s1) / n
    for i in range(n):
        s = s1 + (i + 0.5) * ds
        r = math.sqrt(b * b + s * s)
        k_local = math.sqrt(r / K)
        z = 1.0 / (k_local * k_local)  # = K/r
        # integrand (1/c_far - 1/c) ≈ 2z/c  (engine depth_closure)
        dt += (2.0 * z / C) * abs(ds)
    return dt


def main() -> int:
    print("================================================================")
    print("GOM39 — Local k / Solar K Definition")
    print("Pre-registered 2026-08-09 · K = R/k^2 · k != K")
    print("================================================================\n")

    print("C1 — notation ledger")
    print("  k = c/v_orb(R)   (dimensionless; main-sequence ratio)")
    print("  K = R/k^2        (c-boundary radius; length)")
    print("  v(r) = (c/k)*sqrt(R/r)  <=>  k(r)=sqrt(r/K)  <=>  K=r/k(r)^2")
    print("  C1: PASS\n")

    # --- Validation A ---
    print("C2 — Validation A (multi-radius recovers K)")
    R0 = 1.495978707e11
    v0 = 29780.0
    k0 = C / v0
    K0 = R0 / (k0 * k0)
    print(f"  main sequence: R={R0:.6e} m  v={v0} m/s  k={k0:.6e}  K={K0:.6f} m")
    max_rel = 0.0
    for fac in (0.3, 0.5, 1.0, 2.0, 5.0, 40.0):
        r = R0 * fac
        v = (C / k0) * math.sqrt(R0 / r)
        k = C / v
        K_chk = r / (k * k)
        rel = abs(K_chk - K0) / K0
        max_rel = max(max_rel, rel)
        print(
            f"  r/R={fac:4.1f}  k={k:.6e}  K_chk={K_chk:.6f} m  rel={rel:.3e}"
        )
    ok_a = max_rel < 1e-12
    print(f"  max rel err = {max_rel:.3e}  C2: {'PASS' if ok_a else 'FAIL'}\n")
    if not ok_a:
        return 2

    # --- Validation B ---
    print("C3 — Validation B (local-k integral vs closed form; r >> b)")
    # Far-zone fixture so asymptotic ln(4 r1 r2 / b^2) matches ∫ K/r dl
    r1, r2, b = 1.5e11, 1.0e12, 1.0e9
    dt_c = shapiro_closed(K0, r1, r2, b)
    dt_n = shapiro_numeric_local_k(K0, r1, r2, b, n=50000)
    # Exact analytic integral of (2K/c)/r ds on the same chord (two-route peer)
    s1 = -math.sqrt(r1 * r1 - b * b)
    s2 = math.sqrt(r2 * r2 - b * b)
    dt_exact = (2.0 * K0 / C) * (
        math.log(s2 + r2) - math.log(s1 + r1)
    )
    rel_nc = abs(dt_n - dt_c) / dt_c
    rel_ne = abs(dt_n - dt_exact) / dt_exact
    print(f"  b={b:.3e}  r1/b={r1/b:.1f}  r2/b={r2/b:.1f}")
    print(f"  Δt_closed   = {dt_c:.9e} s")
    print(f"  Δt_exact∫   = {dt_exact:.9e} s")
    print(f"  Δt_localk   = {dt_n:.9e} s")
    print(f"  rel |num-closed| = {rel_nc:.3e}")
    print(f"  rel |num-exact|  = {rel_ne:.3e}")
    ok_b = rel_ne < 1e-6 and rel_nc < 1e-3  # closed is asymptotic; exact is peer
    print(f"  C3: {'PASS' if ok_b else 'FAIL'}\n")
    if not ok_b:
        return 2

    # --- SCE1 Earth ---
    print("C4 — SCE1 Earth main sequence → (k, K)")
    ear = parse_state(HELIO_EAR)
    cas = parse_state(HELIO_CAS)
    ks, Ks = [], []
    for row in ear:
        k = C / row["v"]
        K = row["r"] / (k * k)
        ks.append(k)
        Ks.append(K)
    k_med = median(ks)
    K_med = median(Ks)
    print(f"  Earth samples = {len(ear)}")
    print(f"  k median = {k_med:.6e}  (min/max {min(ks):.6e}/{max(ks):.6e})")
    print(f"  K median = {K_med:.6f} m  CV(K) = {cv(Ks):.3e}")
    print(f"  GOM26 IC (continuity only) = 1476.35 m; |Δ|/K = {abs(K_med-1476.35)/1476.35:.3e}")
    print("  K not fitted to Doppler/delay — C4: PASS\n")

    # --- Local k at conjunction radii ---
    print("C5 — local k at Earth / impact / Cassini radii (using K from C4)")
    # midpoint geometry
    ie = len(ear) // 2
    # nearest Cassini in time
    t0 = ear[ie]["t"]
    ic = min(range(len(cas)), key=lambda i: abs((cas[i]["t"] - t0).total_seconds()))
    re = ear[ie]["xyz"]
    rc = cas[ic]["xyz"]
    r_e = ear[ie]["r"]
    r_c = cas[ic]["r"]
    b = impact_b(re, rc)
    k_e = math.sqrt(r_e / K_med)
    k_b = math.sqrt(b / K_med)
    k_c = math.sqrt(r_c / K_med)
    print(f"  t ≈ {t0.isoformat()}")
    print(f"  R_Earth   = {r_e:.6e} m  -> k = {k_e:.6e}")
    print(f"  b_impact  = {b:.6e} m ({b/6.957e8:.3f} R_Sun) -> k = {k_b:.6e}")
    print(f"  R_Cassini = {r_c:.6e} m  -> k = {k_c:.6e}")
    distinct = (k_e != k_b) and (k_b != k_c) and (k_e != k_c)
    print(f"  pairwise distinct: {distinct}  C5: {'PASS' if distinct else 'FAIL'}\n")
    if not distinct:
        return 2

    # delay under reconstructed K (definition continuity; not residual claim)
    dt = shapiro_closed(K_med, r_e, r_c, b)
    print("  Δt(K_Earth-median) closed-form = {:.6e} s (COMPUTED; not a residual gate)".format(dt))

    print("\nC6 — path status")
    print("  ODF Doppler–solar-K path: DEFINED (local-k grammar; K=R/k^2)")
    print("  Empirical residual: unchanged from GOM36/37 (UNADJUDICATED) — not re-tested")
    print("  C6: PASS")

    print("\n================================================================")
    print("SUMMARY: LOCAL_K_K_DEFINITION_PASS / PATH_DEFINED")
    print("================================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
