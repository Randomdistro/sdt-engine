#!/usr/bin/env python3
"""APS12 — nuclear gravitation and emission (Δz). Direct execution 2026-08-13.

Writes hold-outs first, SHA256, then instrument checks, then one-pass tables.
Constants cited from Engine/include/sdt/laws.hpp. CALIBRATED budget 0.
"""
from __future__ import annotations

import csv
import hashlib
import json
import math
import os
import sys

# ── laws.hpp (measured / atomic / nuclear) ────────────────────────────────
# Engine/include/sdt/laws.hpp lines as of 2026-08-13
c = 299_792_458.0                          # :110
h = 6.626_070_15e-34                       # :129
hbar = 1.054_571_817e-34                   # :111
e_charge = 1.602_176_634e-19               # :131
alpha = 7.297_352_5693e-3                  # :126
a_0 = 5.291_772_109_03e-11                 # :143
r_e = 2.817_940_3262e-15                   # :144
R_p = 8.414e-16                            # :145
m_e = 9.109_383_7015e-31                   # :147
m_p = 1.672_621_923_69e-27                 # :148
m_n = 1.674_927_498_04e-27                 # :149
Ry_eV = 13.605_693_122_994                 # :151
R_inf = 1.097_373_156_8160e7               # :150
B_deuteron_MeV = 2.224                     # :227
B_triton_MeV = 8.482                       # :228
B_alpha_MeV = 28.296                       # :230
PI = math.pi

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", "..", ".."))
HOLDOUT = os.path.join(HERE, "aps12_holdouts.csv")
JSON_IE = os.path.join(ROOT, "Datasets", "nuclear", "ionisation_energies.json")

HC_EV_NM = (h * c / e_charge) * 1e9        # eV·nm
ME_C2_EV = m_e * c * c / e_charge
R_INF_DERIVED = m_e * c * alpha * alpha / (2.0 * h)


def mev_mass_kg(MeV: float) -> float:
    return (MeV * 1e6 * e_charge) / (c * c)


m_d = m_p + m_n - mev_mass_kg(B_deuteron_MeV)
m_t = m_p + 2.0 * m_n - mev_mass_kg(B_triton_MeV)
m_He4 = 2.0 * m_p + 2.0 * m_n - mev_mass_kg(B_alpha_MeV)
m_He3 = 2.0 * m_p + m_n - mev_mass_kg(7.718)  # He-3 binding ~7.718 MeV; MEASURED-INPUT approx — see holdout note


def mu_over_me(m_nuc: float) -> float:
    return m_nuc / (m_e + m_nuc)


def nuclear_boundary_radius(A: int) -> float:
    eta = PI / math.sqrt(18.0)
    return R_p * (A / eta) ** (1.0 / 3.0)


def alpha_grammar(Z: int, A: int) -> tuple[int, int, bool]:
    n_t = A - 2 * Z
    n_d = 3 * Z - A - 2
    return n_d, n_t, (n_d >= 0 and n_t >= 0)


def n_of_outermost(N: int) -> int:
    """Frozen principal n of the outermost electron in an N-electron ground config.
    Madelung filling: 1s | 2s2p | 3s3p | 4s | 3d | 4p | 5s | 4d ...
    Written into hold-outs in Phase 0; not fitted.
    """
    if N <= 0:
        return 1
    if N <= 2:
        return 1
    if N <= 10:
        return 2
    if N <= 18:
        return 3
    if N <= 20:
        return 4
    if N <= 30:
        return 3
    if N <= 36:
        return 4
    if N <= 38:
        return 5
    if N <= 48:
        return 4
    if N <= 54:
        return 5
    if N <= 56:
        return 6
    if N <= 80:
        return 4 if N <= 70 else 5
    return 6


def n_valence_IE(Z: int, k: int) -> int:
    N_before = Z - k + 1
    return n_of_outermost(N_before)


def z_seat(Z: float, n: int) -> float:
    return (Z * alpha / n) ** 2


def E_lead_eV(z_lo: float, z_hi: float, mu_frac: float) -> float:
    return 0.5 * ME_C2_EV * (z_lo - z_hi) * mu_frac


def E_LV_eV(z_lo: float, z_hi: float, mu_frac: float) -> float:
    def bind(z):
        if z >= 1.0:
            return float("nan")
        return ME_C2_EV * (1.0 - math.sqrt(1.0 - z))
    return (bind(z_lo) - bind(z_hi)) * mu_frac


def emission_wavelength_m(Z: int, n_low: int, n_high: int, m_nuc: float) -> float:
    Rn = R_INF_DERIVED * mu_over_me(m_nuc)
    inv = (Z * Z) * (1.0 / (n_low * n_low) - 1.0 / (n_high * n_high))
    return 1.0 / (Rn * inv)


def ppm(pred: float, obs: float) -> float:
    if obs == 0 or obs is None:
        return float("nan")
    return 1e6 * (pred - obs) / obs


def rel_err(pred: float, obs: float) -> float:
    if obs == 0 or obs is None:
        return float("nan")
    return abs(pred - obs) / abs(obs)


# ═══════════════════════════════════════════════════════════════════════════
# Phase 0 — freeze hold-outs (OBSERVED literals only)
# ═══════════════════════════════════════════════════════════════════════════

def load_ie_json() -> dict[int, list[float]]:
    with open(JSON_IE, encoding="utf-8") as f:
        raw = json.load(f)
    return {int(k): [float(x) for x in v] for k, v in raw.items()}


def write_holdouts() -> list[dict]:
    ie = load_ie_json()
    rows: list[dict] = []

    def add(**kw):
        rows.append(kw)

    # C-EXC-H — APS01_Emissions/aps01_emissions_rerun_2026-07-23.txt NIST column
    h_ly = [(2, 121.5670), (3, 102.5722), (4, 97.2537), (5, 94.9743), (6, 93.7803)]
    h_ba = [(3, 656.4614), (4, 486.2712), (5, 434.1692), (6, 410.2892), (7, 397.1233)]
    h_pa = [(4, 1875.6200), (5, 1282.1700), (6, 1094.1200), (7, 1005.2200)]
    for n, lam in h_ly:
        add(corpus_id="C-EXC-H", species="H I", Z=1, A=1, ion_stage="I",
            transition=f"{n}->1", quantity="lambda_nm", value=lam, unit="nm",
            source="APS01 stdout NIST column", citation="NIST ASD via APS01 2026-07-23")
    for n, lam in h_ba:
        add(corpus_id="C-EXC-H", species="H I", Z=1, A=1, ion_stage="I",
            transition=f"{n}->2", quantity="lambda_nm", value=lam, unit="nm",
            source="APS01 stdout NIST column", citation="NIST ASD via APS01 2026-07-23")
    for n, lam in h_pa:
        add(corpus_id="C-EXC-H", species="H I", Z=1, A=1, ion_stage="I",
            transition=f"{n}->3", quantity="lambda_nm", value=lam, unit="nm",
            source="APS01 stdout NIST column", citation="NIST ASD via APS01 2026-07-23")

    # C-EXC-He
    for n, lam in [(2, 30.3785), (3, 25.6317), (4, 24.3034)]:
        add(corpus_id="C-EXC-He", species="He II", Z=2, A=4, ion_stage="II",
            transition=f"{n}->1", quantity="lambda_nm", value=lam, unit="nm",
            source="APS01 stdout NIST column", citation="NIST ASD via APS01 2026-07-23")

    # Li III (extra observed, used for C-EXC-Z Z=3)
    for n, lam in [(2, 13.5006), (3, 11.3921), (4, 10.7982)]:
        add(corpus_id="C-EXC-Z", species="Li III", Z=3, A=7, ion_stage="III",
            transition=f"{n}->1", quantity="lambda_nm", value=lam, unit="nm",
            source="APS01 stdout NIST column", citation="NIST ASD via APS01 2026-07-23")

    # C-EXC-Z Lyα Z=1..26 — OBSERVED only where NIST is in-repo or named literature
    add(corpus_id="C-EXC-Z", species="H I", Z=1, A=1, ion_stage="I",
        transition="2->1", quantity="lambda_nm", value=121.5670, unit="nm",
        source="pre-registration V0", citation="NIST ASD 121.5670 nm")
    add(corpus_id="C-EXC-Z", species="He II", Z=2, A=4, ion_stage="II",
        transition="2->1", quantity="lambda_nm", value=30.3785, unit="nm",
        source="APS01 NIST", citation="NIST ASD via APS01")
    # Z=4..25: NO_DATA (no independent NIST column in repo)
    for Z in range(4, 26):
        add(corpus_id="C-EXC-Z", species=f"Z={Z} H-like", Z=Z, A=2 * Z, ion_stage="H-like",
            transition="2->1", quantity="lambda_nm", value="", unit="nm",
            source="NO_DATA", citation="no in-repo NIST Lyα for this Z")

    # C-EXC-deep — Fe XXVI centroid 6.9625 keV (Lyα1 6.973 + Lyα2 6.952)/2
    # C VI / O VIII / Si XIV: NO_DATA unless listed
    add(corpus_id="C-EXC-deep", species="Fe XXVI", Z=26, A=56, ion_stage="XXVI",
        transition="2->1", quantity="E_keV", value=6.9625, unit="keV",
        source="literature doublet centroid",
        citation="Fe XXVI Lyα1 6.973 keV, Lyα2 6.952 keV (Tomaru/MNRAS compilation)")
    add(corpus_id="C-EXC-deep", species="Fe XXVI", Z=26, A=56, ion_stage="XXVI",
        transition="2->1", quantity="lambda_nm", value=HC_EV_NM / 6962.5, unit="nm",
        source="from 6.9625 keV centroid", citation="derived from E_keV hold-out")
    for spec, Z, A, ion in [("C VI", 6, 12, "VI"), ("O VIII", 8, 16, "VIII"),
                            ("Si XIV", 14, 28, "XIV")]:
        for tr in ("2->1", "3->1", "3->2"):
            add(corpus_id="C-EXC-deep", species=spec, Z=Z, A=A, ion_stage=ion,
                transition=tr, quantity="lambda_nm", value="", unit="nm",
                source="NO_DATA", citation="no in-repo NIST")

    # C-ISO-H D Lyα — Reader (2004) / Erickson binding; blend ~0.033 nm from H
    # Frozen as OBSERVED 121.5339 nm (vacuum 2p blend, NIST H-D reference scale)
    add(corpus_id="C-ISO-H", species="D I", Z=1, A=2, ion_stage="I",
        transition="2->1", quantity="lambda_nm", value=121.5339, unit="nm",
        source="NIST H-D reference scale (Reader 2004 / Erickson 1977 blend)",
        citation="D Lyα unresolved 2p blend ~121.534 nm vacuum")
    add(corpus_id="C-ISO-H", species="T I", Z=1, A=3, ion_stage="I",
        transition="2->1", quantity="lambda_nm", value="", unit="nm",
        source="NO_DATA", citation="no in-repo T Lyα")

    # C-ISO-He
    add(corpus_id="C-ISO-He", species="He-4 II", Z=2, A=4, ion_stage="II",
        transition="2->1", quantity="lambda_nm", value=30.3785, unit="nm",
        source="APS01 NIST", citation="NIST ASD")
    add(corpus_id="C-ISO-He", species="He-3 II", Z=2, A=3, ion_stage="II",
        transition="2->1", quantity="lambda_nm", value="", unit="nm",
        source="NO_DATA", citation="no in-repo 3He II Lyα")

    # C-ION from json
    for Z in range(2, 31):
        series = ie.get(Z, [])
        if len(series) >= Z and series[Z - 1] > 0:
            add(corpus_id="C-ION-last", species=f"Z={Z}", Z=Z, A=0, ion_stage=str(Z),
                transition=f"IE_{Z}", quantity="IE_eV", value=series[Z - 1], unit="eV",
                source="Datasets/nuclear/ionisation_energies.json", citation="NIST/CRC compilation")
        else:
            add(corpus_id="C-ION-last", species=f"Z={Z}", Z=Z, A=0, ion_stage=str(Z),
                transition=f"IE_{Z}", quantity="IE_eV", value="", unit="eV",
                source="NO_DATA", citation="json missing last IE")

    for Z in (2, 4, 6, 8, 10, 12, 18, 20, 26):
        series = ie.get(Z, [])
        for k in range(1, Z + 1):
            nfr = n_valence_IE(Z, k)
            val = series[k - 1] if k <= len(series) and series[k - 1] > 0 else ""
            add(corpus_id="C-ION-full", species=f"Z={Z}", Z=Z, A=0, ion_stage=str(k),
                transition=f"IE_{k}", quantity="IE_eV", value=val, unit="eV",
                source="ionisation_energies.json" if val != "" else "NO_DATA",
                citation="NIST/CRC")
            add(corpus_id="C-ION-n", species=f"Z={Z}", Z=Z, A=0, ion_stage=str(k),
                transition=f"IE_{k}", quantity="n_valence", value=nfr, unit="1",
                source="frozen Madelung outermost of N=Z-k+1", citation="APS12 Phase 0 freeze")

    # C-ION-breach labels (location only)
    for name, Z, k in [("Be IE3", 4, 3), ("Ne IE9", 10, 9), ("Ar IE8", 18, 8),
                       ("Ca IE3", 20, 3), ("Fe IE9", 26, 9)]:
        series = ie.get(Z, [])
        val = series[k - 1] if k <= len(series) else ""
        prev = series[k - 2] if k >= 2 and k - 1 <= len(series) else ""
        add(corpus_id="C-ION-breach", species=name, Z=Z, A=0, ion_stage=str(k),
            transition=f"IE_{k}", quantity="IE_eV", value=val, unit="eV",
            source="ionisation_energies.json", citation="ATOMICUS 04_Ionisation_Series.md label")
        add(corpus_id="C-ION-breach", species=name, Z=Z, A=0, ion_stage=str(k),
            transition=f"IE_{k}/IE_{k-1}", quantity="ratio_obs",
            value=(float(val) / float(prev) if val != "" and prev != "" else ""),
            unit="1", source="json ratio", citation="ATOMICUS breach step")

    # C-ISO-Ca OBSERVED δ⟨r²⟩ and King residuals — APS07
    ca_r2 = {(40, 42): 0.213, (42, 44): 0.069, (44, 46): -0.158, (46, 48): -0.127}
    ca_king = {(40, 42): 96.0, (42, 44): -236.0, (44, 46): -1653.0, (46, 48): 1641.0}
    for (A, Ap), dr2 in ca_r2.items():
        add(corpus_id="C-ISO-Ca", species=f"Ca-{A},{Ap}", Z=20, A=A, ion_stage="Ca+",
            transition=f"{A}->{Ap}", quantity="delta_r2_fm2", value=dr2, unit="fm^2",
            source="APS07_VERDICT PTB/MPIK 2025", citation="APS07_VERDICT_DIRECT_2026-07-25.md")
        add(corpus_id="C-ISO-Ca", species=f"Ca-{A},{Ap}", Z=20, A=A, ion_stage="Ca+",
            transition=f"{A}->{Ap}", quantity="King_residual_Hz", value=ca_king[(A, Ap)],
            unit="Hz", source="APS07_VERDICT", citation="same")

    # C-ISO-Yb δ⟨r²⟩ Counts 2020
    yb_r2 = {(168, 170): -0.156, (170, 172): -0.146, (172, 174): -0.115, (174, 176): -0.110}
    yb_nu_a = {(168, 170): 2179098.93, (170, 172): 2044854.78,
               (172, 174): 1583068.42, (174, 176): 1509055.29}
    for (A, Ap), dr2 in yb_r2.items():
        add(corpus_id="C-ISO-Yb", species=f"Yb-{A},{Ap}", Z=70, A=A, ion_stage="Yb+",
            transition=f"{A}->{Ap}", quantity="delta_r2_fm2", value=dr2, unit="fm^2",
            source="Counts 2020 via APS07 DATA_COLLECTION", citation="PRL 125, 123002")
        add(corpus_id="C-ISO-Yb", species=f"Yb-{A},{Ap}", Z=70, A=A, ion_stage="Yb+",
            transition=f"{A}->{Ap}", quantity="nu_alpha_kHz", value=yb_nu_a[(A, Ap)],
            unit="kHz", source="Counts 2020", citation="same")

    # C-MULTI
    add(corpus_id="C-MULTI", species="He I", Z=2, A=4, ion_stage="I",
        transition="1s2-1s2p 1P", quantity="lambda_nm", value=58.433, unit="nm",
        source="pre-registration", citation="APS01 / NIST 58.433 nm")
    add(corpus_id="C-MULTI", species="He I", Z=2, A=4, ion_stage="I",
        transition="1s2-1s2p 1P", quantity="E_eV", value=21.218, unit="eV",
        source="pre-registration", citation="same")
    add(corpus_id="C-MULTI", species="Na I", Z=11, A=23, ion_stage="I",
        transition="3s-3p", quantity="lambda_nm", value=588.995, unit="nm",
        source="pre-registration", citation="APS01 588.995 nm")
    add(corpus_id="C-MULTI", species="Na I", Z=11, A=23, ion_stage="I",
        transition="3s-3p", quantity="E_eV", value=2.105, unit="eV",
        source="pre-registration", citation="same")
    add(corpus_id="C-MULTI", species="Fe XXV", Z=26, A=56, ion_stage="XXV",
        transition="1s2-1s2p 1P w", quantity="E_keV", value=6.700, unit="keV",
        source="pre-registration freeze", citation="APS12_PRE_REGISTRATION.md")
    add(corpus_id="C-MULTI", species="Be I", Z=4, A=9, ion_stage="I",
        transition="2s2-2s2p 1P", quantity="lambda_nm", value=234.861, unit="nm",
        source="pre-registration", citation="APS01 234.861 nm")
    add(corpus_id="C-MULTI", species="Be I", Z=4, A=9, ion_stage="I",
        transition="2s2-2s2p 1P", quantity="E_eV", value=5.279, unit="eV",
        source="pre-registration", citation="same")

    fields = ["corpus_id", "species", "Z", "A", "ion_stage", "transition",
              "quantity", "value", "unit", "source", "citation"]
    with open(HOLDOUT, "w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fields)
        w.writeheader()
        for r in rows:
            w.writerow({k: r.get(k, "") for k in fields})
    return rows


def sha256_file(path: str) -> str:
    hsh = hashlib.sha256()
    with open(path, "rb") as f:
        hsh.update(f.read())
    return hsh.hexdigest()


def fnum(x):
    if x is None or x == "":
        return None
    try:
        return float(x)
    except (TypeError, ValueError):
        return None


def index_holdouts(rows):
    by = {}
    for r in rows:
        key = (r["corpus_id"], r["species"], r["transition"], r["quantity"])
        by[key] = r
    return by


def mass_for(Z, A):
    if Z == 1 and A == 1:
        return m_p, "m_p"
    if Z == 1 and A == 2:
        return m_d, "m_p+m_n-B_d/c^2"
    if Z == 1 and A == 3:
        return m_t, "m_p+2m_n-B_t/c^2"
    if Z == 2 and A == 4:
        return m_He4, "2mp+2mn-B_alpha/c^2"
    if Z == 2 and A == 3:
        return m_He3, "2mp+mn-7.718 MeV/c^2"
    return A * m_p, "A*m_p"


# ═══════════════════════════════════════════════════════════════════════════
def main():
    os.makedirs(os.path.join(ROOT, ".audit-tmp"), exist_ok=True)
    print("=" * 72)
    print("APS12 nuclear gravitation dZ -- direct execution 2026-08-13")
    print("CALIBRATED budget: 0. Canon edits: none.")
    print("=" * 72)

    rows = write_holdouts()
    digest = sha256_file(HOLDOUT)
    print(f"\n[P0] hold-outs written: {HOLDOUT}")
    print(f"[P0] N_rows={len(rows)}  sha256={digest}")

    # ── instrument checks ──
    koppa_H = alpha * alpha * a_0
    rel_koppa = abs(koppa_H - r_e) / r_e
    z1 = alpha ** 2
    E1 = 0.5 * ME_C2_EV * z1
    rel_Ry = abs(E1 - Ry_eV) / Ry_eV
    lam_V0 = emission_wavelength_m(1, 1, 2, m_p) * 1e9
    ppm_V0 = ppm(lam_V0, 121.5670)
    print(f"\n[P0] koppa_H vs r_e  rel={rel_koppa:.3e}  tag=IDENTITY")
    print(f"[P0] 0.5 me c^2 α^2 vs Ry_eV  rel={rel_Ry:.3e}  tag=IDENTITY")
    print(f"[P0] V0 λ(H 2→1)={lam_V0:.6f} nm  NIST=121.5670  Δppm={ppm_V0:.2f}")
    print(f"[P0] R_inf_derived={R_INF_DERIVED:.10e}  laws.hpp R_inf={R_inf:.10e}  "
          f"rel={abs(R_INF_DERIVED-R_inf)/R_inf:.3e}")

    v0_id_ok = rel_koppa < 1e-11 and rel_Ry < 1e-11
    v0_pass = abs(ppm_V0) <= 15.0 and v0_id_ok
    zk2_ok = True
    print("\n[P0] zk² on H n=1..7 (identity; not scored as physics):")
    for n in range(1, 8):
        z = z_seat(1, n)
        k = 1.0 / math.sqrt(z)
        prod = z * k * k
        if abs(prod - 1.0) > 1e-12:
            zk2_ok = False
        print(f"     n={n}  z={z:.9e}  k={k:.6f}  zk²={prod:.12f}")
    v0_pass = v0_pass and zk2_ok
    print(f"[P0] V0 {'PASS-GATE' if v0_pass else 'INSTRUMENT FAIL'}")
    if not v0_pass:
        print("Instrument fault. Physics tables not opened.")
        sys.exit(1)

    H = index_holdouts(rows)

    def obs_lambda(corpus, species, trans):
        r = H.get((corpus, species, trans, "lambda_nm"))
        if r is None or r["source"] == "NO_DATA" or r["value"] == "":
            return None
        return float(r["value"])

    def obs_IE(Z, k):
        r = H.get(("C-ION-full", f"Z={Z}", f"IE_{k}", "IE_eV"))
        if r is None:
            r = H.get(("C-ION-last", f"Z={Z}", f"IE_{k}", "IE_eV"))
        if r is None or r["source"] == "NO_DATA" or r["value"] == "":
            return None
        return float(r["value"])

    def obs_n(Z, k):
        r = H.get(("C-ION-n", f"Z={Z}", f"IE_{k}", "n_valence"))
        return int(float(r["value"])) if r else n_valence_IE(Z, k)

    # ── Phase 1 ──
    print("\n" + "=" * 72)
    print("PHASE 1 — excitation for excitation (H-like Δz)")
    print("=" * 72)
    t1 = []

    def t1_row(corpus, species, Z, A, n_hi, n_lo, lam_obs):
        m_nuc, msrc = mass_for(Z, A)
        mf = mu_over_me(m_nuc)
        z_lo = z_seat(Z, n_lo)
        z_hi = z_seat(Z, n_hi)
        if z_lo >= 1.0:
            tag = "Z_GT_ONE"
        else:
            tag = "COMPUTED"
        dZ = z_lo - z_hi
        E_l = E_lead_eV(z_lo, z_hi, mf)
        E_v = E_LV_eV(z_lo, z_hi, mf)
        drel = (E_v - E_l) / E_l if E_l else float("nan")
        lam_dz = HC_EV_NM / E_l
        lam_eng = emission_wavelength_m(Z, n_lo, n_hi, m_nuc) * 1e9
        two = abs(lam_dz - lam_eng) / lam_eng
        r_lo = n_lo * n_lo / Z
        r_hi = n_hi * n_hi / Z
        koppa_fm = (Z * r_e) * 1e15
        p = ppm(lam_eng, lam_obs) if lam_obs is not None else float("nan")
        k_lo = 1.0 / math.sqrt(z_lo)
        rec = dict(corpus=corpus, species=species, Z=Z, A=A, n_high=n_hi, n_low=n_lo,
                   koppa_fm=koppa_fm, r_high_a0=r_hi, r_low_a0=r_lo, z_high=z_hi, z_low=z_lo,
                   dZ=dZ, k_low=k_lo, E_lead_eV=E_l, E_LV_eV=E_v, dLV_over_E=drel,
                   lam_pred_nm=lam_eng, lam_dz_nm=lam_dz, two_route_rel=two,
                   lam_obs_nm=lam_obs if lam_obs is not None else "",
                   dppm=p, zk2=z_lo * k_lo * k_lo, mu_me=mf, msrc=msrc, tag=tag)
        t1.append(rec)
        obs_s = f"{lam_obs:.6f}" if lam_obs is not None else "NO_DATA"
        p_s = f"{p:+.1f}" if lam_obs is not None else "—"
        print(f"  {species:12s} {n_hi}->{n_lo}  λ_pred={lam_eng:.6f}  obs={obs_s}  "
              f"Δppm={p_s}  two-route={two:.2e}  δLV/E={drel:.4e}")
        return rec

    # C-EXC-H
    for n in range(2, 7):
        t1_row("C-EXC-H", "H I", 1, 1, n, 1, obs_lambda("C-EXC-H", "H I", f"{n}->1"))
    for n in range(3, 8):
        t1_row("C-EXC-H", "H I", 1, 1, n, 2, obs_lambda("C-EXC-H", "H I", f"{n}->2"))
    for n in range(4, 8):
        t1_row("C-EXC-H", "H I", 1, 1, n, 3, obs_lambda("C-EXC-H", "H I", f"{n}->3"))
    for n in (2, 3, 4):
        t1_row("C-EXC-He", "He II", 2, 4, n, 1, obs_lambda("C-EXC-He", "He II", f"{n}->1"))
    for n in (2, 3, 4):
        t1_row("C-EXC-Z", "Li III", 3, 7, n, 1, obs_lambda("C-EXC-Z", "Li III", f"{n}->1"))

    A_typical = {1: 1, 2: 4, 3: 7, 6: 12, 8: 16, 14: 28, 26: 56}
    for Z in range(1, 27):
        A = A_typical.get(Z, 2 * Z)
        spec = {1: "H I", 2: "He II", 3: "Li III"}.get(Z, f"Z={Z} H-like")
        if Z == 1:
            lam = 121.5670
        elif Z == 2:
            lam = 30.3785
        elif Z == 3:
            lam = 13.5006
        elif Z == 26:
            lam = obs_lambda("C-EXC-deep", "Fe XXVI", "2->1")
        else:
            lam = None
        # skip duplicate H/He/Li 2->1 already printed in series? still need C-EXC-Z set
        t1_row("C-EXC-Z", spec, Z, A, 2, 1, lam)

    rec_fe = [r for r in t1 if r["Z"] == 26 and r["n_high"] == 2 and r["n_low"] == 1][-1]
    h_ppms = [r["dppm"] for r in t1 if r["corpus"] == "C-EXC-H" and r["lam_obs_nm"] != ""]
    z_ppms = [r["dppm"] for r in t1 if r["corpus"] == "C-EXC-Z" and r["lam_obs_nm"] != ""
              and not (isinstance(r["dppm"], float) and math.isnan(r["dppm"]))]
    max_h = max(abs(x) for x in h_ppms)
    max_z = max(abs(x) for x in z_ppms) if z_ppms else float("nan")
    two_max = max(r["two_route_rel"] for r in t1)
    g_exc_h = max_h <= 15.0
    g_exc_z = max_z <= 1000.0
    fe_rel = rel_err(rec_fe["lam_pred_nm"], rec_fe["lam_obs_nm"]) if rec_fe["lam_obs_nm"] != "" else float("nan")
    g_exc_fe = fe_rel <= 0.005
    print(f"\n  two-route max rel={two_max:.3e}  (gate 1e-9: {'PASS' if two_max < 1e-9 else 'NOTE — see Δz vs R∞ units'})")
    print(f"  G_EXC H max|ppm|={max_h:.2f}  {'MATCH' if g_exc_h else 'INCONSISTENT'}")
    print(f"  G_EXC Z (observed rows only) max|ppm|={max_z:.2f}  N_obs={len(z_ppms)}  "
          f"{'MATCH' if g_exc_z else 'INCONSISTENT'}")
    print(f"  G_EXC_Fe Fe XXVI 2→1 rel={fe_rel:.4e}  λ_pred={rec_fe['lam_pred_nm']:.6f}  "
          f"obs={rec_fe['lam_obs_nm']}  δLV/E={rec_fe['dLV_over_E']:.4e}  "
          f"{'MATCH' if g_exc_fe else 'INCONSISTENT'}")

    # ── Phase 2 ──
    print("\n" + "=" * 72)
    print("PHASE 2 — ionisation for ionisation")
    print("=" * 72)
    t2_last, t2_full = [], []
    last_ok_lo, last_ok_hi = True, True
    print("\n  T2-last (H-like last electron):")
    for Z in range(2, 31):
        series_last = H.get(("C-ION-last", f"Z={Z}", f"IE_{Z}", "IE_eV"))
        obs = fnum(series_last["value"]) if series_last and series_last["source"] != "NO_DATA" else None
        A = A_typical.get(Z, 2 * Z)
        m_nuc, msrc = mass_for(Z, A)
        mf = mu_over_me(m_nuc)
        z1z = z_seat(Z, 1)
        pred = Ry_eV * mf * Z * Z
        # also Δz path: upper at infinity z=0
        pred_dz = E_lead_eV(z1z, 0.0, mf)
        re = rel_err(pred, obs) if obs else float("nan")
        tag = "COMPUTED"
        rec = dict(Z=Z, A=A, mu_me=mf, z_1=z1z, IE_pred=pred, IE_pred_dz=pred_dz,
                   IE_obs=obs if obs else "", rel=re, ppm=1e6 * (pred - obs) / obs if obs else "",
                   tag=tag, msrc=msrc)
        t2_last.append(rec)
        if obs:
            band = "≤20" if Z <= 20 else "21–30"
            gate = 0.01 if Z <= 20 else 0.02
            ok = re <= gate
            if Z <= 20 and not ok:
                last_ok_lo = False
            if Z > 20 and not ok:
                last_ok_hi = False
            print(f"    Z={Z:2d}  pred={pred:10.3f}  obs={obs:10.3f}  rel={re:.4e}  "
                  f"{'MATCH' if ok else 'OUT'} ({band})")
        else:
            print(f"    Z={Z:2d}  pred={pred:10.3f}  obs=NO_DATA")

    g_ion_last = last_ok_lo and last_ok_hi
    print(f"  G_ION_last {'MATCH' if g_ion_last else 'INCONSISTENT'}")

    print("\n  T2-full S_bare vs S_ion (intermediate k < Z scored for G_ION_S):")
    n_inter = 0
    hit_bare = 0
    hit_ion = 0
    for Z in (2, 4, 6, 8, 10, 12, 18, 20, 26):
        for k in range(1, Z + 1):
            obs = obs_IE(Z, k)
            nfr = obs_n(Z, k)
            A = A_typical.get(Z, 2 * Z)
            mf = mu_over_me(mass_for(Z, A)[0])
            E_bare = Ry_eV * mf * (Z ** 2) / (nfr ** 2)
            E_ion = Ry_eV * mf * (k ** 2) / (nfr ** 2)
            rb = rel_err(E_bare, obs) if obs else float("nan")
            ri = rel_err(E_ion, obs) if obs else float("nan")
            closer = "bare" if (obs and rb <= ri) else ("ion" if obs else "")
            jump = ""
            if k >= 2:
                prev = obs_IE(Z, k - 1)
                if obs and prev and prev > 0 and obs / prev > 3.0:
                    jump = "JUMP"
            rec = dict(Z=Z, k=k, N_e_before=Z - k + 1, n_frozen=nfr,
                       Zeff_bare=Z, Zeff_ion=k, E_bare=E_bare, E_ion=E_ion,
                       E_obs=obs if obs else "", rel_bare=rb, rel_ion=ri,
                       jump_flag=jump, rule_closer=closer, tag="COMPUTED")
            t2_full.append(rec)
            if obs and k < Z:
                n_inter += 1
                if rb < 0.10:
                    hit_bare += 1
                if ri < 0.10:
                    hit_ion += 1
            if k == 1 or k == Z or jump:
                obs_s = f"{obs:.3f}" if obs else "NO_DATA"
                print(f"    Z={Z:2d} k={k:2d} n={nfr}  bare={E_bare:10.2f}  ion={E_ion:10.2f}  "
                      f"obs={obs_s:10s}  rel_b={rb if obs else float('nan'):.3f}  "
                      f"rel_i={ri if obs else float('nan'):.3f}  {jump}")

    frac_b = hit_bare / n_inter if n_inter else 0
    frac_i = hit_ion / n_inter if n_inter else 0
    g_ion_s = frac_b >= 0.80 or frac_i >= 0.80
    print(f"\n  intermediate rows N={n_inter}  S_bare rel<0.10: {hit_bare}/{n_inter}={frac_b:.3f}  "
          f"S_ion: {hit_ion}/{n_inter}={frac_i:.3f}")
    print(f"  G_ION_S {'MATCH' if g_ion_s else 'OPEN (neither rule ≥80%)'}")

    print("\n  T2-breach:")
    for name, Z, k in [("Be IE3", 4, 3), ("Ne IE9", 10, 9), ("Ar IE8", 18, 8),
                       ("Ca IE3", 20, 3), ("Fe IE9", 26, 9)]:
        recs = [r for r in t2_full if r["Z"] == Z and r["k"] == k]
        rec = recs[0] if recs else None
        ratio_r = H.get(("C-ION-breach", name, f"IE_{k}/IE_{k-1}", "ratio_obs"))
        ratio = fnum(ratio_r["value"]) if ratio_r else None
        n_now = obs_n(Z, k)
        n_prev = obs_n(Z, k - 1)
        loc = "n-drop" if n_now < n_prev else "same-n"
        print(f"    {name}: k={k} n {n_prev}->{n_now} ({loc})  obs ratio={ratio}  "
              f"S_ion pred {rec['E_ion']:.1f} vs obs {rec['E_obs']}")

    # ── Phase 3 ──
    print("\n" + "=" * 72)
    print("PHASE 3 — isotope for isotope")
    print("=" * 72)
    t3_mass, t3_size, t3_gram = [], [], []

    lam_H = emission_wavelength_m(1, 1, 2, m_p) * 1e9
    lam_D = emission_wavelength_m(1, 1, 2, m_d) * 1e9
    lam_T = emission_wavelength_m(1, 1, 2, m_t) * 1e9
    obs_H = 121.5670
    obs_D = 121.5339
    dnu_pred = (c / (lam_D * 1e-9) - c / (lam_H * 1e-9))  # Hz, sign D bluer
    dlam_pred = lam_H - lam_D
    dlam_obs = obs_H - obs_D
    iso_rel = abs(dlam_pred - dlam_obs) / abs(dlam_obs)
    g_iso_mass = iso_rel <= 0.05
    print(f"  H Lyα pred={lam_H:.6f} obs={obs_H:.6f}")
    print(f"  D Lyα pred={lam_D:.6f} obs={obs_D:.6f}")
    print(f"  T Lyα pred={lam_T:.6f} obs=NO_DATA")
    print(f"  I_mass H–D Δλ pred={dlam_pred:.6f} nm  obs={dlam_obs:.6f} nm  "
          f"rel_on_shift={iso_rel:.4e}  {'MATCH' if g_iso_mass else 'INCONSISTENT'}")
    t3_mass.append(dict(pair="H-D", Z=1, A=1, Ap=2, line="Lyα",
                        mu=mu_over_me(m_p), mup=mu_over_me(m_d),
                        lam_pred_A=lam_H, lam_pred_Ap=lam_D,
                        dlam_pred=dlam_pred, dlam_obs=dlam_obs, rel_on_shift=iso_rel,
                        tag="COMPUTED"))
    lam_He4 = emission_wavelength_m(2, 1, 2, m_He4) * 1e9
    lam_He3 = emission_wavelength_m(2, 1, 2, m_He3) * 1e9
    print(f"  He-4 II 2→1 pred={lam_He4:.6f} obs=30.3785")
    print(f"  He-3 II 2→1 pred={lam_He3:.6f} obs=NO_DATA  Δλ_pred={lam_He4-lam_He3:.6f} nm")
    t3_mass.append(dict(pair="He4-He3", Z=2, A=4, Ap=3, line="2->1",
                        mu=mu_over_me(m_He4), mup=mu_over_me(m_He3),
                        lam_pred_A=lam_He4, lam_pred_Ap=lam_He3,
                        dlam_pred=lam_He4 - lam_He3, dlam_obs="", rel_on_shift="",
                        tag="COMPUTED"))

    print("\n  I_size Ca (n=4, r_n = a0 n²/Z with Z=20 as frozen; sign vs δ⟨r²⟩):")
    ca_pairs = [(40, 42, 0.213), (42, 44, 0.069), (44, 46, -0.158), (46, 48, -0.127)]
    n_ca, Z_ca = 4, 20
    r_n_ca = a_0 * n_ca * n_ca / Z_ca
    agrees = 0
    for A, Ap, dr2 in ca_pairs:
        RA = nuclear_boundary_radius(A)
        RAp = nuclear_boundary_radius(Ap)
        Th = 0.25 * (RA / r_n_ca) ** 2
        Thp = 0.25 * (RAp / r_n_ca) ** 2
        dTh = Thp - Th
        sgn_th = 1 if dTh > 0 else (-1 if dTh < 0 else 0)
        sgn_r2 = 1 if dr2 > 0 else (-1 if dr2 < 0 else 0)
        ag = int(sgn_th == sgn_r2)
        agrees += ag
        nd, nt, ok = alpha_grammar(20, A)
        ndp, ntp, _ = alpha_grammar(20, Ap)
        print(f"    {A}->{Ap}  R={RA*1e15:.4f}->{RAp*1e15:.4f} fm  δΘ={dTh:.4e}  "
              f"signΘ={sgn_th:+d}  sign_δr²={sgn_r2:+d}  agree={ag}  "
              f"n_t {nt}->{ntp}")
        t3_size.append(dict(pair=f"{A}-{Ap}", Z=20, RA_fm=RA * 1e15, RAp_fm=RAp * 1e15,
                            Theta=Th, Thetap=Thp, dTheta=dTh, sign_dTheta=sgn_th,
                            sign_dr2=sgn_r2, agree=ag, tag="COMPUTED"))
    n_steps = len(ca_pairs)
    g_iso_size = agrees == n_steps
    print(f"  G_ISO_size sign {agrees}/{n_steps}  "
          f"{'MATCH' if g_iso_size else ('OPEN' if agrees > 2 else 'INCONSISTENT (≤2)')}")
    if agrees <= 2:
        g_iso_size_class = "INCONSISTENT"
    elif agrees == n_steps:
        g_iso_size_class = "MATCH"
    else:
        g_iso_size_class = "OPEN"
    # pre-reg: MATCH = 4/4 or 5/5; inconsistent if ≤2. 2/4 is INCONSISTENT.

    print("\n  I_grammar (report only; no MATCH on kHz):")
    print("    Ca even chain:")
    for A in (40, 42, 44, 46, 48):
        nd, nt, ok = alpha_grammar(20, A)
        lm = "nt0" if nt == 0 else ("ntd" if nt == nd else "none")
        print(f"      Ca-{A}  n_d={nd} n_t={nt}  landmark={lm}  valid={ok}")
        t3_gram.append(dict(species="Ca", A=A, Z=20, n_d=nd, n_t=nt,
                            n_t_minus_n_d=nt - nd, landmark=lm, valid=ok))
    print("      2A=5Z-2 crossing for Z=20 is A=49 (off the even chain).")
    print("    Yb even chain:")
    for A in (168, 170, 172, 174, 176):
        nd, nt, ok = alpha_grammar(70, A)
        lm = "ntd" if nt == nd else "none"
        print(f"      Yb-{A}  n_d={nd} n_t={nt}  landmark={lm}  valid={ok}")
        t3_gram.append(dict(species="Yb", A=A, Z=70, n_d=nd, n_t=nt,
                            n_t_minus_n_d=nt - nd, landmark=lm, valid=ok))
    print("    G_GRAM: landmarks reported. Re-sort by n_t was not used as evidence.")
    print("    Ca-40 n_t=0 (first triton entry 40→42). Yb-174 n_t=n_d.")
    print("    Ca King residual sign-change sits on 44→46 / 46→48 (n_t=6→8), not on 40→42.")
    print("    That coincidence is a report, not a kHz MATCH.")

    # ── Phase 4 ──
    print("\n" + "=" * 72)
    print("PHASE 4 — remaining electrons (S_bare / S_ion only; no new rule)")
    print("=" * 72)
    t4 = []

    def multi_line(name, Z, A, n_lo, n_hi, E_obs_eV, same_n=False):
        mf = mu_over_me(mass_for(Z, A)[0])
        # S_bare: Z_eff=Z; S_ion for a resonance of a neutral: k=1 → Z_eff=1
        z_lo_b = z_seat(Z, n_lo)
        z_hi_b = z_seat(Z, n_hi) if n_hi != n_lo else z_lo_b
        z_lo_i = z_seat(1, n_lo)
        z_hi_i = z_seat(1, n_hi) if n_hi != n_lo else z_lo_i
        if same_n:
            E_b = 0.0
            E_i = 0.0
            sn = "SAME_N_NULL"
        else:
            E_b = E_lead_eV(z_lo_b, z_hi_b, mf)
            E_i = E_lead_eV(z_lo_i, z_hi_i, mf)
            sn = ""
        rb = rel_err(E_b, E_obs_eV)
        ri = rel_err(E_i, E_obs_eV)
        print(f"  {name:12s} n {n_hi}->{n_lo}  E_obs={E_obs_eV:.4f} eV  "
              f"S_bare={E_b:.4f} rel={rb:.3f}  S_ion={E_i:.4f} rel={ri:.3f}  {sn}")
        t4.append(dict(id=name, E_obs=E_obs_eV, n_lo=n_lo, n_hi=n_hi,
                       E_S_bare=E_b, E_S_ion=E_i, rel_bare=rb, rel_ion=ri,
                       SAME_N_NULL=sn, tag="COMPUTED"))

    multi_line("He I res", 2, 4, 1, 2, 21.218, same_n=False)
    multi_line("Na D", 11, 23, 3, 3, 2.105, same_n=True)
    multi_line("Be I res", 4, 9, 2, 2, 5.279, same_n=True)  # 2s2-2s2p same n=2
    # Fe XXV He-like 1s²-1s2p: n=1→2, leftover ion charge 25 after? Neutral Fe has 26e;
    # Fe XXV has 2 electrons. Line is 1s-2p of the He-like ion.
    # S_bare Z=26; S_ion: treating as k=25 remaining-ion? Pre-reg: apply S_bare and S_ion
    # to line energies. For He-like, S_ion Z_eff = 25 (one companion screens by 1) is a
    # common reading — FROZEN as Z_eff=k with k=Z-1=25 for the two-electron ion's Kα.
    mf = mu_over_me(mass_for(26, 56)[0])
    E_b = E_lead_eV(z_seat(26, 1), z_seat(26, 2), mf)
    E_i = E_lead_eV(z_seat(25, 1), z_seat(25, 2), mf)
    E_obs = 6700.0  # eV
    print(f"  {'Fe XXV w':12s} n 2->1  E_obs={E_obs:.1f} eV  "
          f"S_bare={E_b:.1f} rel={rel_err(E_b,E_obs):.3f}  "
          f"S_ion(Zeff=25)={E_i:.1f} rel={rel_err(E_i,E_obs):.3f}")
    t4.append(dict(id="Fe XXV w", E_obs=E_obs, n_lo=1, n_hi=2,
                   E_S_bare=E_b, E_S_ion=E_i, rel_bare=rel_err(E_b, E_obs),
                   rel_ion=rel_err(E_i, E_obs), SAME_N_NULL="", tag="COMPUTED"))
    print("  G_MULTI: table complete. No MATCH claimed. No new coefficient.")

    # ── write CSVs ──
    def dump_csv(name, recs):
        if not recs:
            return
        path = os.path.join(HERE, name)
        keys = list(recs[0].keys())
        with open(path, "w", newline="", encoding="utf-8") as f:
            w = csv.DictWriter(f, fieldnames=keys)
            w.writeheader()
            for r in recs:
                w.writerow(r)
        print(f"  wrote {name}  N={len(recs)}")

    print("\n" + "=" * 72)
    print("PHASE 5 — ledger files")
    dump_csv("aps12_T1_excitation.csv", t1)
    dump_csv("aps12_T2_ionisation.csv", t2_full)
    dump_csv("aps12_T2_last.csv", t2_last)
    dump_csv("aps12_T3_isotope.csv", t3_mass)
    dump_csv("aps12_T3_size.csv", t3_size)
    dump_csv("aps12_T3_grammar.csv", t3_gram)
    dump_csv("aps12_T4_multi.csv", t4)

    # ── gate summary ──
    print("\n" + "=" * 72)
    print("GATE TABLE")
    print("=" * 72)
    gates = [
        ("V0", "MATCH" if v0_pass else "INCONSISTENT", f"Δppm={ppm_V0:.2f}"),
        ("G_EXC H", "MATCH" if g_exc_h else "INCONSISTENT", f"max|ppm|={max_h:.2f}"),
        ("G_EXC Z obs", "MATCH" if g_exc_z else "INCONSISTENT", f"max|ppm|={max_z:.2f} N={len(z_ppms)}"),
        ("G_EXC_Fe", "MATCH" if g_exc_fe else "INCONSISTENT", f"rel={fe_rel:.4e} δLV/E={rec_fe['dLV_over_E']:.3e}"),
        ("G_ION_last", "MATCH" if g_ion_last else "INCONSISTENT", f"Z≤20 {last_ok_lo} Z>20 {last_ok_hi}"),
        ("G_ION_S", "MATCH" if g_ion_s else "OPEN", f"bare {hit_bare}/{n_inter} ion {hit_ion}/{n_inter}"),
        ("G_ISO_mass", "MATCH" if g_iso_mass else "INCONSISTENT", f"rel_on_shift={iso_rel:.4e}"),
        ("G_ISO_size", g_iso_size_class, f"sign {agrees}/{n_steps}"),
        ("G_GRAM", "report only", "no kHz MATCH; re-sort not used"),
        ("G_MULTI", "table only", "no MATCH required"),
    ]
    for g, st, det in gates:
        print(f"  {g:16s} {st:16s} {det}")

    native = (g_exc_h and g_exc_z) and (g_ion_s or g_iso_size)
    spine = g_exc_h and g_exc_z and g_ion_last
    print("\nPHYSICS CLASS")
    print("  excitation axis:  native origin (Δz); algebra shared — number cannot discriminate"
          if (g_exc_h and g_exc_z) else "  excitation axis: EXCLUDED")
    if g_exc_fe:
        print("  Fe XXVI leading Δz: MATCH within 0.5%")
    else:
        print("  Fe XXVI leading Δz: INCONSISTENT vs 0.5% (Law V remainder logged, not fitted)")
    print("  last-electron IE: native origin (z_1); algebra shared"
          if g_ion_last else "  last-electron IE: EXCLUDED")
    print("  occupancy S_bare/S_ion: OPEN" if not g_ion_s else "  occupancy: MATCH on a frozen rule")
    print(f"  I_size Ca signs: {g_iso_size_class}")
    print("  I_mass H–D: IDENTITY (two-body)" if g_iso_mass else "  I_mass H–D: EXCLUDED")
    print("  parent: native Δz origin, not Coulomb; hydrogenic number unpaid as discriminator; occupancy and NP12 size unpaid"
          if spine and not native else
          ("  parent: NATIVE-distinct" if native else "  parent: see gates"))
    print(f"\nsha256 holdouts={digest}")
    print("END APS12")


if __name__ == "__main__":
    main()
