"""Reproducible conditional carrier-speed inversion; no fitted pressure law.

SPARC velocities are reduced observables, not independent measurements of
physical speed under a variable-carrier hypothesis. Baryonic force profiles
remain conditional on standard photometric/gas calibrations.
"""
from __future__ import annotations

import csv
import hashlib
import io
import json
import math
import sys
from pathlib import Path
import urllib.request
import zipfile

import numpy as np

ROOT = Path(__file__).resolve().parent
DATA = ROOT / "source_data"
C0 = 299792.458  # km/s; comparison baseline
UD, UB = 0.5, 0.7  # fixed 3.6 micron mass-to-light choices, Msun/Lsun
URLS = {
    "Rotmod_LTG.zip": "https://astroweb.case.edu/SPARC/Rotmod_LTG.zip",
    "SPARC_Lelli2016c.mrt": "https://astroweb.case.edu/SPARC/SPARC_Lelli2016c.mrt",
}


def get_sources():
    DATA.mkdir(exist_ok=True)
    manifest = []
    for name, url in URLS.items():
        path = DATA / name
        if not path.exists():
            req = urllib.request.Request(url, headers={"User-Agent": "SDT-research-audit/1.0"})
            with urllib.request.urlopen(req, timeout=30) as response:
                payload = response.read()
            path.write_bytes(payload)
        payload = path.read_bytes()
        manifest.append({"name": name, "url": url, "bytes": len(payload),
                         "sha256": hashlib.sha256(payload).hexdigest(),
                         "md5": hashlib.md5(payload).hexdigest()})
    (ROOT / "source_manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    return manifest


def load_metadata():
    meta = {}
    for line in (DATA / "SPARC_Lelli2016c.mrt").read_text(encoding="utf-8").splitlines():
        try:
            fields = line.split()
            if len(fields) < 19:
                continue
            name = fields[0]
            item = {"distance_mpc": float(fields[2]), "inclination_deg": float(fields[5]),
                    "disk_scale_kpc": float(fields[11]), "quality": int(fields[17])}
        except (ValueError, IndexError):
            continue
        if name:
            meta[name] = item
    if len(meta) != 175:
        raise ValueError(f"Metadata parse: expected 175, obtained {len(meta)}")
    return meta


def load_rotmod():
    curves = {}
    with zipfile.ZipFile(DATA / "Rotmod_LTG.zip") as archive:
        for member in archive.namelist():
            if not member.endswith("_rotmod.dat"):
                continue
            name = Path(member).name.removesuffix("_rotmod.dat")
            curves[name] = np.loadtxt(io.BytesIO(archive.read(member)), comments="#", ndmin=2)
    if len(curves) != 175:
        raise ValueError(f"Rotmod parse: expected 175, obtained {len(curves)}")
    return curves


def write_csv(path, rows):
    if not rows:
        raise ValueError(f"Empty table: {path}")
    with path.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)


def regression(x, y):
    if len(x) < 4 or np.ptp(x) < 1e-9:
        return None
    return float(np.polyfit(x, y, 1)[0])


def algebra_checks():
    # Exact paired spectra with arbitrary common depth and transverse Doppler.
    rng = np.random.default_rng(10072026)
    common = np.exp(rng.uniform(-8, 8, 10000))
    beta_total = rng.uniform(1e-4, .8, 10000)
    sin_i = rng.uniform(.1, 1, 10000)
    beta_los = beta_total * sin_i
    gamma = 1 / np.sqrt(1 - beta_total**2)
    rec = common * gamma * (1 + beta_los)
    app = common * gamma * (1 - beta_los)
    recovered = (rec - app) / (rec + app)
    pair_error = float(np.max(np.abs(recovered - beta_los)))
    log_error = float(np.max(np.abs(np.tanh(.5*np.log(rec/app)) - beta_los)))
    assert pair_error < 1e-14 and log_error < 1e-14
    # Radius quadrupling: Kepler speed halves. Flat spectral beta requires c/2.
    speed = np.array([200., 100.])
    falling_carrier = C0 * np.array([1., .5])
    rising_carrier = C0 * np.array([1., 2.])
    assert np.allclose(C0*speed/falling_carrier, [200., 200.])
    assert np.allclose(C0*speed/rising_carrier, [200., 50.])
    # Exact incompressible cavity map: unit determinant of deformation gradient.
    a = np.geomspace(1e-3, 1e3, 1000)
    r = np.cbrt(a**3 + 1.)
    jacobian = (a/r)**2 * (r/a)**2
    assert np.max(np.abs(jacobian-1)) < 1e-14
    # Canonical reciprocal k vs transcript multiplicative coefficient.
    k = 686.3
    assert abs((1/k**2)*k*k - 1) < 1e-14
    assert abs(k**2 - 471007.69) < 1e-7
    return {"paired_spectral_max_absolute_error": pair_error,
            "log_ratio_max_absolute_error": log_error,
            "cavity_jacobian_max_error": float(np.max(np.abs(jacobian-1))),
            "kepler_speed_at_r_1_and_4_kms": speed.tolist(),
            "apparent_speed_with_rising_c_kms": (C0*speed/rising_carrier).tolist(),
            "apparent_speed_with_falling_c_kms": (C0*speed/falling_carrier).tolist()}


def plot_examples(curves):
    # Standard ReportLab line-plot primitives; standalone vector artifact.
    from reportlab.graphics.shapes import Drawing, String, Line
    from reportlab.graphics.charts.lineplots import LinePlot
    from reportlab.lib.colors import HexColor
    from reportlab.graphics import renderSVG
    width, height = 1080, 780
    drawing = Drawing(width, height)
    drawing.add(String(35, height-28, "SPARC: conditional carrier speed required by baryon-only motion", fontSize=18))
    drawing.add(String(35, height-48, "Fixed stellar M/L: disk 0.5, bulge 0.7. Ratios are inverse constructions, not predictions.", fontSize=11))
    examples = ["NGC2403", "NGC3198", "DDO154"]
    blue, orange = HexColor("#155e91"), HexColor("#b45309")
    for column, name in enumerate(examples):
        table = curves[name]
        r, obs = table[:, 0], table[:, 1]
        bar2 = table[:, 3]*np.abs(table[:, 3]) + UD*table[:, 4]*np.abs(table[:, 4]) + UB*table[:, 5]*np.abs(table[:, 5])
        good = (r > 0) & (obs > 0) & (bar2 > 0)
        r, obs, bar = r[good], obs[good], np.sqrt(bar2[good])
        for row in range(2):
            left, bottom = 58+350*column, 425-340*row
            chart = LinePlot()
            chart.x, chart.y, chart.width, chart.height = left, bottom, 282, 240
            chart.xValueAxis.valueMin = 0
            chart.xValueAxis.valueMax = float(np.max(r)*1.04)
            chart.xValueAxis.labels.fontSize = 8
            chart.yValueAxis.labels.fontSize = 8
            if row == 0:
                chart.data = [list(zip(r.tolist(), obs.tolist())), list(zip(r.tolist(), bar.tolist()))]
                chart.yValueAxis.valueMin = 0
                chart.yValueAxis.valueMax = float(max(np.max(obs),np.max(bar))*1.12)
                chart.lines[0].strokeColor, chart.lines[1].strokeColor = blue, orange
                title, label = name, "Speed (km/s)"
            else:
                ratio = bar/obs
                chart.data = [list(zip(r.tolist(), ratio.tolist()))]
                chart.yValueAxis.valueMin = 0
                chart.yValueAxis.valueMax = float(max(1.1,np.max(ratio)*1.12))
                chart.lines[0].strokeColor = orange
                title, label = "Required c_phase / c0", "Dimensionless ratio"
            for line in chart.lines:
                line.strokeWidth = 1.8
            drawing.add(chart)
            drawing.add(String(left+141, bottom+260, title, textAnchor="middle", fontSize=13))
            drawing.add(String(left+141, bottom-30, "Radius (kpc)", textAnchor="middle", fontSize=10))
            drawing.add(String(left, bottom+244, label, fontSize=9))
    drawing.add(Line(65, 728, 93, 728, strokeColor=blue, strokeWidth=2))
    drawing.add(String(100, 723, "Published Vobs", fontSize=10))
    drawing.add(Line(240, 728, 268, 728, strokeColor=orange, strokeWidth=2))
    drawing.add(String(275, 723, "Baryonic Vbar", fontSize=10))
    renderSVG.drawToFile(drawing, str(ROOT / "carrier_speed_examples.svg"))
    try:
        from reportlab.graphics import renderPM
        renderPM.drawToFile(drawing, str(ROOT / "carrier_speed_examples.png"), fmt="PNG", dpi=120)
        return "SVG and PNG"
    except Exception as exc:
        return f"SVG saved; PNG renderer unavailable: {type(exc).__name__}"


def main():
    manifest = get_sources()
    meta, curves = load_metadata(), load_rotmod()
    algebra = algebra_checks()
    points, galaxies = [], []
    for name in sorted(curves):
        table = curves[name]
        r, obs, err = table[:,0], table[:,1], table[:,2]
        bar2 = table[:,3]*np.abs(table[:,3]) + UD*table[:,4]*np.abs(table[:,4]) + UB*table[:,5]*np.abs(table[:,5])
        good = (r>0) & (obs>0) & (bar2>0)
        bar = np.sqrt(np.maximum(bar2,0))
        ratio = np.full(len(table),np.nan)
        ratio[good] = bar[good]/obs[good]
        outer_cut = max(2*meta[name]["disk_scale_kpc"], .5*float(np.max(r)))
        outer = good & (r>=outer_cut)
        slope = regression(np.log(r[outer]), np.log(ratio[outer]))
        qualified = meta[name]["quality"]<=2 and meta[name]["inclination_deg"]>=30 and slope is not None
        for j in range(len(table)):
            points.append({"galaxy": name, "radius_kpc": float(r[j]), "published_vobs_kms": float(obs[j]),
                           "vobs_error_kms": float(err[j]), "conditional_vbar_kms": float(bar[j]) if good[j] else "",
                           "required_cphase_over_c0": float(ratio[j]) if good[j] else "",
                           "outer_selected": bool(outer[j]), "quality": meta[name]["quality"],
                           "inclination_deg": meta[name]["inclination_deg"]})
        indices = np.where(good)[0]
        last = indices[-1] if len(indices) else None
        galaxies.append({"galaxy": name, "points": len(table), "valid_points": int(np.sum(good)),
                         "outer_cut_kpc": outer_cut, "outer_points": int(np.sum(outer)),
                         "outer_log_c_slope": slope, "quality_inclination_outer_selection": qualified,
                         "last_radius_kpc": float(r[last]) if last is not None else None,
                         "last_vobs_kms": float(obs[last]) if last is not None else None,
                         "last_vbar_kms": float(bar[last]) if last is not None else None,
                         "last_required_cphase_over_c0": float(ratio[last]) if last is not None else None,
                         **meta[name]})
    write_csv(ROOT/"pointwise_required_carrier_speed.csv", points)
    write_csv(ROOT/"galaxy_summary.csv", galaxies)
    selected = [g for g in galaxies if g["quality_inclination_outer_selection"]]
    slopes = np.array([g["outer_log_c_slope"] for g in selected])
    summary = {"dataset": "SPARC original Rotmod_LTG and metadata", "galaxies": len(curves),
               "radial_points": len(points), "valid_radial_points": sum(g["valid_points"] for g in galaxies),
               "disk_mass_to_light": UD, "bulge_mass_to_light": UB,
               "outer_rule": "r >= max(2*Rdisk, 0.5*rmax), >=4 valid points; Q<=2 and inclination>=30deg",
               "selected_galaxies": len(selected), "selected_negative_outer_slopes": int(np.sum(slopes<0)),
               "selected_slopes_below_minus_point_one": int(np.sum(slopes<-.1)),
               "selected_positive_outer_slopes": int(np.sum(slopes>0)),
               "median_selected_outer_log_c_slope": float(np.median(slopes)),
               "examples": [g for g in galaxies if g["galaxy"] in ["DDO154","NGC2403","NGC3198"]],
               "algebra_checks": algebra, "sources": manifest,
               "limitations": ["No raw approaching/receding line centroids in Rotmod data.",
                               "Required c profile is solved from observed Vobs and assumed Vbar, not independently predicted.",
                               "Photometric distance, inclination, gas calibration, stellar M/L and baryonic force law remain conditional.",
                               "Outer slopes are descriptive; no full nuisance covariance or model likelihood.",
                               "c_phase is a Doppler parameter; c_far from the native header is not automatically interchangeable."]}
    summary["figure_output"] = plot_examples(curves) if "--figure" in sys.argv else "Optional SVG figure: run with --figure"
    (ROOT/"results.json").write_text(json.dumps(summary,indent=2),encoding="utf-8")
    print(json.dumps(summary,indent=2))


if __name__ == "__main__":
    main()
