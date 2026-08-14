"""APS14 driver: diagnostics, nested calibration, hold-out scoring."""

from __future__ import annotations

import csv
import json
import math
import sys
from pathlib import Path

import numpy as np

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

from aps14.calibration import fit_model, load_tables
from aps14.validation import (
    fit_zeff_sigma, hlike_recovery_tests, score_baselines,
    score_ionisation, score_resonance,
)


def write_csv(path: Path, rows: list[dict]) -> None:
    if not rows:
        return
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)


def measured_ie(rows: list[dict], split: str | None = None) -> list[dict]:
    return [
        row for row in rows
        if row["status"] == "MEASURED"
        and (split is None or row["split"] == split)
    ]


def bootstrap_m1(cal_rows, configs, masses, n_draw=8) -> list[float]:
    rng = np.random.default_rng(14)
    zs = sorted({int(row["Z"]) for row in cal_rows})
    values = []
    for _ in range(n_draw):
        chosen = set(rng.choice(zs, size=max(4, len(zs) // 2), replace=False))
        subset = [row for row in cal_rows if int(row["Z"]) in chosen]
        values.append(
            fit_model("M1_MEAN_OCCLUSION", subset, configs, masses).parameters.g_same
        )
    return values


def loo_m1(cal_rows, configs, masses) -> list[dict]:
    zs = sorted({int(row["Z"]) for row in cal_rows})
    probes = [z for z in zs if z in {1, 3, 6, 9, 12, 15, 20, 25, 30}]
    rows = []
    for left in probes:
        subset = [row for row in cal_rows if int(row["Z"]) != left]
        fit = fit_model("M1_MEAN_OCCLUSION", subset, configs, masses)
        rows.append({
            "left_out_Z": left, "g": fit.parameters.g_same,
            "rss": fit.rss, "n": fit.n_rows,
        })
    return rows


def statistics_median(values: list[float]) -> float:
    ordered = sorted(values)
    count = len(ordered)
    if not count:
        return math.nan
    if count % 2:
        return ordered[count // 2]
    return 0.5 * (ordered[count // 2 - 1] + ordered[count // 2])


def main() -> int:
    data = HERE / "data"
    elements, ionisation, resonance, configs, masses, _ = load_tables(data)
    calibration_ie = measured_ie(ionisation, "CALIBRATION")
    holdout_ie = measured_ie(ionisation, "HOLDOUT")
    all_ie = measured_ie(ionisation)

    print("APS14 nuclear-z celestial atom")
    print(
        f"  elements={len(elements)} IE measured={len(all_ie)} "
        f"cal={len(calibration_ie)} hold={len(holdout_ie)}"
    )
    print("\nH-LIKE RECOVERY")
    recovery = hlike_recovery_tests()
    write_csv(HERE / "aps14_hlike_recovery.csv", recovery)
    for row in recovery:
        print(" ", {
            key: (f"{value:.3e}" if isinstance(value, float) else value)
            for key, value in row.items()
        })

    print("\nCALIBRATION")
    fits = {}
    m3_rows = []
    by_z: dict[int, list] = {}
    for row in calibration_ie:
        by_z.setdefault(int(row["Z"]), []).append(row)
    for group in by_z.values():
        group = sorted(group, key=lambda row: int(row["step"]))
        keep = {0, len(group) - 1}
        if len(group) > 3:
            keep.add(len(group) // 2)
        if len(group) > 1:
            keep.add(1)
        m3_rows.extend(group[index] for index in sorted(keep))

    for name in (
        "M0_HLIKE", "M1_MEAN_OCCLUSION",
        "M2_TYPED_OCCLUSION", "M3_RELAXED_STATE",
    ):
        train = m3_rows if name == "M3_RELAXED_STATE" else calibration_ie
        print(f"  fitting {name} on {len(train)} rows ...", flush=True)
        fit = fit_model(name, train, configs, masses)
        fits[name] = fit
        p = fit.parameters
        print(
            f"    success={fit.success} n={fit.n_rows} k={fit.n_params} "
            f"rss={fit.rss:.4g} AICc={fit.aicc:.3f} BIC={fit.bic:.3f}"
        )
        print(
            f"    g_same={p.g_same:.5f} g_cross={p.g_cross:.5f} "
            f"d_s={p.delta_s:.5f} d_p={p.delta_p:.5f} d_d={p.delta_d:.5f}"
        )

    sigma = fit_zeff_sigma(calibration_ie, configs)
    print(f"  Zeff comparator sigma={sigma:.5f} CALIBRATED(1)")

    print("\nIONISATION SCORES")
    ie_summaries = {}
    for name, fit in fits.items():
        relaxed = name == "M3_RELAXED_STATE"
        cal_ledger, cal_summary = score_ionisation(
            calibration_ie, configs, masses, fit.parameters, relaxed
        )
        hold_ledger, hold_summary = score_ionisation(
            holdout_ie, configs, masses, fit.parameters, relaxed
        )
        ie_summaries[name] = {"cal": cal_summary, "hold": hold_summary}
        write_csv(
            HERE / f"aps14_ie_{name.lower()}.csv",
            cal_ledger + hold_ledger,
        )
        print(
            f"  {name}: hold n={hold_summary['n']} "
            f"median={100 * hold_summary['median']:.2f}% "
            f"<10%={hold_summary['frac10']:.3f}"
        )

    baseline_hold = score_baselines(holdout_ie, configs, sigma)
    baseline_cal = score_baselines(calibration_ie, configs, sigma)
    print("  comparators (hold-out)")
    for name, summary in baseline_hold.items():
        print(
            f"    {name}: median={100 * summary['median']:.2f}% "
            f"<10%={summary['frac10']:.3f}"
        )

    print("\nRESONANCE / H-LIKE LINES")
    line_summaries = {}
    for name, fit in fits.items():
        ledger, untouched, hlike = score_resonance(
            resonance, configs, masses, fit.parameters
        )
        write_csv(HERE / f"aps14_lines_{name.lower()}.csv", ledger)
        line_summaries[name] = {"untouched": untouched, "hlike": hlike}
        print(
            f"  {name}: H-like median={100 * hlike['median']:.4f}% "
            f"untouched median={100 * untouched['median']:.2f}%"
        )

    loo = loo_m1(calibration_ie, configs, masses)
    write_csv(HERE / "aps14_m1_loo.csv", loo)
    bootstrap = bootstrap_m1(calibration_ie, configs, masses)
    write_csv(
        HERE / "aps14_m1_bootstrap.csv",
        [{"draw": index, "g": value} for index, value in enumerate(bootstrap)],
    )

    best = min(
        ("M1_MEAN_OCCLUSION", "M2_TYPED_OCCLUSION", "M3_RELAXED_STATE"),
        key=lambda name: ie_summaries[name]["hold"]["median"],
    )
    best_hold = ie_summaries[best]["hold"]["median"]
    zeff_hold = baseline_hold["zeff"]["median"]
    promote = best_hold < 0.85 * zeff_hold
    print("\nPROMOTION GATE")
    print(f"  best={best} median={100 * best_hold:.2f}%")
    print(f"  Zeff median={100 * zeff_hold:.2f}%")
    print(f"  materially better={promote}")
    print("  laws.hpp edit: none")

    payload = {
        "fits": {
            name: {
                "g_same": fit.parameters.g_same,
                "g_cross": fit.parameters.g_cross,
                "delta_s": fit.parameters.delta_s,
                "delta_p": fit.parameters.delta_p,
                "delta_d": fit.parameters.delta_d,
                "n_params": fit.n_params,
                "rss": fit.rss,
                "aicc": fit.aicc,
                "bic": fit.bic,
                "success": fit.success,
            }
            for name, fit in fits.items()
        },
        "ie": ie_summaries,
        "baselines_hold": baseline_hold,
        "baselines_cal": baseline_cal,
        "lines": line_summaries,
        "sigma_zeff": sigma,
        "promote": promote,
        "best": best,
    }
    (HERE / "aps14_summary.json").write_text(
        json.dumps(payload, indent=2, default=float), encoding="utf-8"
    )
    print("END APS14")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
