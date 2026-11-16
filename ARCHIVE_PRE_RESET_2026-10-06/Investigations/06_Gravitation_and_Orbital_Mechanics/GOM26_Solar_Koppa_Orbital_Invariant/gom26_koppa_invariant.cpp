// GOM26 — Solar Koppa Orbital Invariant (GOM25 repair re-audit)
// Pre-registered: PROMPT.md (2026-08-07). No post-hoc coefficient retuning.
//
// Build (MSVC, from repo root):
//   cl /nologo /std:c++20 /EHsc /O2 /I Engine\include ^
//      /Fe:.audit-tmp\gom26.exe ^
//      Investigations\06_Gravitation_and_Orbital_Mechanics\GOM26_Solar_Koppa_Orbital_Invariant\gom26_koppa_invariant.cpp

#include <sdt/laws.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace sdt::laws;

namespace {

struct VecRow {
    double jd = 0;
    double r_m = 0;
    double v_ms = 0;
    double koppa_inst = 0; // v^2 r / c^2 instantaneous
};

[[nodiscard]] auto split_csv(const std::string& line) -> std::vector<std::string> {
    std::vector<std::string> out;
    std::string cur;
    std::istringstream ss(line);
    while (std::getline(ss, cur, ',')) {
        auto a = cur.find_first_not_of(" \t\r\n");
        auto b = cur.find_last_not_of(" \t\r\n");
        if (a == std::string::npos) out.emplace_back();
        else out.push_back(cur.substr(a, b - a + 1));
    }
    return out;
}

[[nodiscard]] auto load_horizons(const std::string& path, int& n_skip) -> std::vector<VecRow> {
    std::ifstream in(path);
    if (!in) {
        std::fprintf(stderr, "FAIL open Horizons: %s\n", path.c_str());
        return {};
    }
    std::string line;
    bool in_soe = false;
    std::vector<VecRow> rows;
    n_skip = 0;
    while (std::getline(in, line)) {
        if (line.rfind("$$SOE", 0) == 0) { in_soe = true; continue; }
        if (line.rfind("$$EOE", 0) == 0) break;
        if (!in_soe) continue;
        auto cols = split_csv(line);
        if (cols.size() < 8) { ++n_skip; continue; }
        try {
            VecRow row;
            row.jd = std::stod(cols[0]);
            const double x = std::stod(cols[2]);
            const double y = std::stod(cols[3]);
            const double z = std::stod(cols[4]);
            const double vx = std::stod(cols[5]);
            const double vy = std::stod(cols[6]);
            const double vz = std::stod(cols[7]);
            const double r_km = std::sqrt(x * x + y * y + z * z);
            const double v_kms = std::sqrt(vx * vx + vy * vy + vz * vz);
            if (!(r_km > 0.0) || !(v_kms > 0.0) || !std::isfinite(r_km) || !std::isfinite(v_kms)) {
                ++n_skip;
                continue;
            }
            row.r_m = r_km * 1000.0;
            row.v_ms = v_kms * 1000.0;
            row.koppa_inst = (row.v_ms * row.v_ms * row.r_m) / (measured::c * measured::c);
            rows.push_back(row);
        } catch (...) {
            ++n_skip;
        }
    }
    return rows;
}

struct Stats {
    double mean = 0;
    double stdev = 0;
    double minv = 0;
    double maxv = 0;
    double cv = 0;
    double median = 0;
    double mad = 0;
};

[[nodiscard]] auto stats(std::vector<double> x) -> Stats {
    Stats s;
    if (x.empty()) return s;
    double sum = 0, sum2 = 0;
    s.minv = x.front();
    s.maxv = x.front();
    for (double v : x) {
        sum += v;
        sum2 += v * v;
        s.minv = std::min(s.minv, v);
        s.maxv = std::max(s.maxv, v);
    }
    const double n = static_cast<double>(x.size());
    s.mean = sum / n;
    s.stdev = std::sqrt(std::max(0.0, sum2 / n - s.mean * s.mean));
    s.cv = (s.mean != 0.0) ? s.stdev / std::abs(s.mean) : 0.0;
    std::sort(x.begin(), x.end());
    s.median = x[x.size() / 2];
    std::vector<double> dev;
    dev.reserve(x.size());
    for (double v : x) dev.push_back(std::abs(v - s.median));
    std::sort(dev.begin(), dev.end());
    s.mad = dev[dev.size() / 2];
    return s;
}

struct MuResult {
    double mu = 0;
    double sigma_mu = 0;
    double a = 0;
    double koppa = 0;
    double sigma_koppa = 0;
    int n_pairs = 0;
    int n_pair_candidates = 0;
    Stats koppa_recon;
    Stats koppa_inst;
};

[[nodiscard]] auto estimate_invariant(const std::vector<VecRow>& rows, double eps_inv_r)
    -> MuResult {
    MuResult out;
    out.koppa_inst = [&] {
        std::vector<double> k;
        for (const auto& r : rows) k.push_back(r.koppa_inst);
        return stats(k);
    }();

    std::vector<double> mus;
    const std::size_t n = rows.size();
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i + 1; j < n; ++j) {
            const double dinv = 1.0 / rows[j].r_m - 1.0 / rows[i].r_m;
            if (std::abs(dinv) <= eps_inv_r) continue;
            ++out.n_pair_candidates;
            const double mu = (rows[j].v_ms * rows[j].v_ms - rows[i].v_ms * rows[i].v_ms)
                            / (2.0 * dinv);
            if (std::isfinite(mu) && mu > 0.0) {
                mus.push_back(mu);
                ++out.n_pairs;
            }
        }
    }
    if (mus.empty()) return out;
    auto sm = stats(mus);
    out.mu = sm.median;
    // Robust SE proxy per PROMPT: 1.4826 * MAD / sqrt(N_eff)
    const double neff = static_cast<double>(mus.size());
    out.sigma_mu = (neff > 0.0) ? (1.4826 * sm.mad / std::sqrt(neff)) : 0.0;
    out.koppa = out.mu / (measured::c * measured::c);
    out.sigma_koppa = out.sigma_mu / (measured::c * measured::c);

    // Mean specific energy → a
    double e_sum = 0.0;
    for (const auto& r : rows) {
        e_sum += 0.5 * r.v_ms * r.v_ms - out.mu / r.r_m;
    }
    const double e_mean = e_sum / static_cast<double>(rows.size());
    out.a = -out.mu / (2.0 * e_mean);

    std::vector<double> krec;
    for (const auto& r : rows) {
        const double denom = (2.0 / r.r_m - 1.0 / out.a);
        if (!(denom > 0.0)) continue;
        krec.push_back((r.v_ms * r.v_ms) / (measured::c * measured::c * denom));
    }
    out.koppa_recon = stats(krec);
    return out;
}

[[nodiscard]] auto validate_circular_mock() -> bool {
    const double r = measured::AU;
    const double v = 29780.0;
    std::vector<VecRow> rows(12);
    for (int i = 0; i < 12; ++i) {
        rows[i].r_m = r;
        rows[i].v_ms = v;
        rows[i].koppa_inst = v * v * r / (measured::c * measured::c);
    }
    // Circular: all r equal ⇒ no pairwise μ. Inject tiny radial spread preserving circular μ=v²r.
    const double mu_true = v * v * r;
    for (int i = 0; i < 12; ++i) {
        const double ri = r * (1.0 + 1e-4 * std::sin(0.5 * i));
        // Keep energy constant: v^2/2 - μ/r = -μ/(2a) with a=r for circular ⇒ v^2 = μ(2/r - 1/a)
        const double a = r;
        const double vi2 = mu_true * (2.0 / ri - 1.0 / a);
        rows[i].r_m = ri;
        rows[i].v_ms = std::sqrt(vi2);
        rows[i].koppa_inst = rows[i].v_ms * rows[i].v_ms * ri / (measured::c * measured::c);
    }
    auto res = estimate_invariant(rows, 1e-15);
    const double rel = std::abs(res.mu - mu_true) / mu_true;
    const bool ok = rel < 1e-8 && res.koppa_recon.cv < 1e-6;
    std::printf("VALIDATION A — near-circular Kepler mock\n");
    std::printf("  mu_true = %.9e  mu_est = %.9e  rel=%.3e  %s\n",
                mu_true, res.mu, rel, rel < 1e-8 ? "PASS" : "FAIL");
    std::printf("  CV(koppa_i recon) = %.3e  %s\n\n",
                res.koppa_recon.cv, res.koppa_recon.cv < 1e-6 ? "PASS" : "FAIL");
    return ok;
}

[[nodiscard]] auto kepler_E(double M, double e) -> double {
    double E = M;
    for (int i = 0; i < 12; ++i) {
        const double f = E - e * std::sin(E) - M;
        const double fp = 1.0 - e * std::cos(E);
        E -= f / fp;
    }
    return E;
}

[[nodiscard]] auto validate_eccentric_mock() -> bool {
    const double mu_true = 1.3271244e20; // synthetic scale only; not an observational input
    const double a = measured::AU;
    const double e = 0.0167;
    std::vector<VecRow> rows;
    for (int k = 0; k < 36; ++k) {
        const double M = 2.0 * std::numbers::pi * k / 36.0;
        const double E = kepler_E(M, e);
        const double r = a * (1.0 - e * std::cos(E));
        const double v2 = mu_true * (2.0 / r - 1.0 / a);
        VecRow row;
        row.r_m = r;
        row.v_ms = std::sqrt(v2);
        row.koppa_inst = row.v_ms * row.v_ms * r / (measured::c * measured::c);
        rows.push_back(row);
    }
    auto res = estimate_invariant(rows, 1e-15);
    const double rel = std::abs(res.mu - mu_true) / mu_true;
    // Amendment 01: CV floor 1e-6 (fp chain); empirical gate remains 1e-3.
    const bool ok = rel < 1e-6 && res.koppa_recon.cv < 1e-6;
    std::printf("VALIDATION B — eccentric Kepler mock (e=0.0167, exact E)\n");
    std::printf("  mu_true = %.9e  mu_est = %.9e  rel=%.3e  %s\n",
                mu_true, res.mu, rel, rel < 1e-6 ? "PASS" : "FAIL");
    std::printf("  a_est = %.6e m (true a=%.6e)\n", res.a, a);
    std::printf("  CV(koppa_i recon) = %.3e  %s\n",
                res.koppa_recon.cv, res.koppa_recon.cv < 1e-6 ? "PASS" : "FAIL");
    std::printf("  CV(koppa_inst)    = %.3e (expect O(e))\n\n", res.koppa_inst.cv);
    return ok;
}

[[nodiscard]] auto atdf_record_census(const std::string& path) -> bool {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::printf("D4 PROBE — cannot open TDF: %s\n", path.c_str());
        return false;
    }
    constexpr std::size_t REC = 288;
    std::vector<char> buf(REC);
    std::size_t nrec = 0;
    // TRK-2-25: first 9 bytes encode format/type as bitfields; without the
    // full bit-unpack table we only census file integrity + first-byte histogram.
    std::vector<std::uint64_t> first_byte(256, 0);
    while (in.read(buf.data(), static_cast<std::streamsize>(REC))) {
        ++nrec;
        first_byte[static_cast<unsigned char>(buf[0])]++;
    }
    std::printf("D4 PROBE — ATDF integrity census (NOT a delay residual)\n");
    std::printf("  path: %s\n", path.c_str());
    std::printf("  records read (288 B): %zu  (label claims 64820)\n", nrec);
    std::printf("  STATUS: PENDING_DATA for Shapiro-like marker — decode/geometry/clock absent\n");
    std::printf("  NOTE: first-byte histogram is not a physical observable\n\n");
    return nrec == 64820;
}

} // namespace

int main(int argc, char** argv)
{
    const std::string cal_path =
        (argc > 1) ? argv[1]
                   : "Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2025.csv";
    // Pre-registered fallback (PROMPT §3): if argv[2] is "INTRA_YEAR" or the
    // hold-out file is absent/invalid, split D1-cal odd/even indices.
    const std::string hold_arg =
        (argc > 2) ? argv[2]
                   : "INTRA_YEAR";
    const std::string tdf_path =
        (argc > 3) ? argv[3]
                   : "Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_tdf.tdf";

    std::puts("================================================================");
    std::puts("GOM26 — Solar Koppa Orbital Invariant (repair re-audit)");
    std::puts("Pre-registered 2026-08-07 · no post-hoc retuning");
    std::puts("================================================================\n");

    const bool vA = validate_circular_mock();
    const bool vB = validate_eccentric_mock();
    if (!vA || !vB) {
        std::puts("INSTRUMENT VALIDATION FAILED — no empirical adjudication.");
        return 2;
    }

    constexpr double eps = 1e-15; // m^-1

    int skip_cal = 0;
    auto all = load_horizons(cal_path, skip_cal);
    std::printf("DATA D1 source rows=%zu skip=%d  path=%s\n", all.size(), skip_cal, cal_path.c_str());
    if (all.size() < 10) {
        std::puts("insufficient rows — abort");
        return 3;
    }

    std::vector<VecRow> cal, hold;
    bool intra_year = (hold_arg == "INTRA_YEAR");
    if (!intra_year) {
        int skip_hold = 0;
        hold = load_horizons(hold_arg, skip_hold);
        // Reject non-heliocentric / nonsense orbits (PROMPT data integrity).
        auto probe = estimate_invariant(hold, eps);
        if (hold.size() < 10 || !(probe.mu > 1e19) || !(probe.a > 1e10)) {
            std::printf("DATA D1-hold REJECTED (mu=%.3e a=%.3e) — falling back to INTRA_YEAR\n",
                        probe.mu, probe.a);
            intra_year = true;
            hold.clear();
        } else {
            cal = all;
            std::printf("DATA D1-hold rows=%zu skip=%d  path=%s\n", hold.size(), skip_hold, hold_arg.c_str());
        }
    }
    if (intra_year) {
        std::puts("DATA D1-hold mode: INTRA_YEAR (odd indices calibrate; even hold out)");
        std::puts("  LABEL: pre-registered fallback — not multi-year independence");
        for (std::size_t i = 0; i < all.size(); ++i) {
            if ((i % 2) == 0) hold.push_back(all[i]);
            else cal.push_back(all[i]);
        }
    }
    std::printf("DATA D1-cal  rows=%zu\n", cal.size());
    std::printf("DATA D1-hold rows=%zu\n\n", hold.size());
    if (cal.size() < 5 || hold.size() < 5) {
        std::puts("insufficient split rows — abort");
        return 3;
    }

    // Delete-test before spectral: print engine koppa unused
    std::printf("DELETE / CIRCULARITY\n");
    std::printf("  bridge::koppa_Sun NOT USED = %.6f m\n", bridge::koppa_Sun);
    std::printf("  HARPS not read as input to mu/koppa\n\n");

    auto cal_res = estimate_invariant(cal, eps);
    auto hold_res = estimate_invariant(hold, eps);

    auto report = [](const char* tag, const MuResult& r, std::size_t nrows) {
        const double pair_frac = (r.n_pair_candidates > 0)
                                     ? static_cast<double>(r.n_pairs) / r.n_pair_candidates
                                     : 0.0;
        std::printf("INVARIANT — %s\n", tag);
        std::printf("  usable pairs = %d / %d  frac=%.4f\n",
                    r.n_pairs, r.n_pair_candidates, pair_frac);
        std::printf("  mu median = %.9e ± %.3e m^3/s^2   LABEL: DERIVED\n",
                    r.mu, r.sigma_mu);
        std::printf("  a from <E> = %.9e m\n", r.a);
        std::printf("  koppa = mu/c^2 = %.6f ± %.6f m   LABEL: DERIVED\n",
                    r.koppa, r.sigma_koppa);
        std::printf("  CV(koppa_inst = v^2 r/c^2) = %.6e\n", r.koppa_inst.cv);
        std::printf("  CV(koppa_i recon)          = %.6e\n", r.koppa_recon.cv);
        std::printf("  rows used for recon stats  = %zu (of %zu)\n\n",
                    nrows, nrows);
        return pair_frac;
    };

    const double frac_cal = report("D1-cal (2025)", cal_res, cal.size());
    std::printf("  recon n effective via CV fields above; inst mean=%.6f recon mean=%.6f\n\n",
                cal_res.koppa_inst.mean, cal_res.koppa_recon.mean);
    const double frac_hold = report("D1-hold (2024)", hold_res, hold.size());
    std::printf("  recon mean hold=%.6f\n\n", hold_res.koppa_recon.mean);

    // Gates C1/C2 — calibration sample only (PROMPT §4.1–4.2)
    const bool pairs_ok = frac_cal >= 0.50;
    const bool inv_ok = cal_res.koppa_recon.cv < 1e-3;
    std::printf("GATE C1/C2 — invariance (calibration)\n");
    std::printf("  pair fraction >= 50%%: %s (frac=%.4f)\n", pairs_ok ? "PASS" : "FAIL", frac_cal);
    std::printf("  CV(koppa_i) < 1e-3:    %s (CV=%.3e)\n",
                inv_ok ? "PASS" : "FAIL", cal_res.koppa_recon.cv);
    std::printf("  STATUS: %s\n\n",
                (pairs_ok && inv_ok)
                    ? "Keplerian invariant definition SURVIVES formal gate on calibration"
                    : "NO RECOVERY for this repair route / FORMAL DEFECT");

    // Gate C4 hold-out
    const bool hold_pairs_ok = frac_hold >= 0.50 && hold_res.mu > 1e19 && hold_res.a > 1e10;
    const double drel = (cal_res.koppa != 0.0)
                            ? std::abs(hold_res.koppa - cal_res.koppa) / cal_res.koppa
                            : 1.0;
    const bool hold_ok = hold_pairs_ok && drel < 1e-3;
    std::printf("GATE C4 — hold-out stability\n");
    std::printf("  hold pair frac=%.4f  mu=%.6e  a=%.6e  %s\n",
                frac_hold, hold_res.mu, hold_res.a,
                hold_pairs_ok ? "hold sample usable" : "hold sample UNUSABLE");
    std::printf("  koppa_cal  = %.6f m\n", cal_res.koppa);
    std::printf("  koppa_hold = %.6f m\n", hold_res.koppa);
    std::printf("  |Δ|/koppa  = %.6e  threshold=1e-3  %s\n",
                drel, (hold_pairs_ok && drel < 1e-3) ? "PASS" : "FAIL");
    std::printf("  STATUS: %s\n\n",
                hold_ok ? "COMPATIBLE with orbital-invariant claim on hold-out"
                        : (!hold_pairs_ok
                               ? "PENDING_DATA/INVALID hold sample — C4 not adjudicated"
                               : "EXCLUDED as invariant across samples"));

    // Gate C3 spectral — after koppa frozen
    const double R_iau = measured::R_Sun;
    const double R_phot = 695658e3;
    const double dR_phot = 140e3;
    const double v_pred = measured::c * cal_res.koppa / R_iau;
    const double sig_pred = measured::c * cal_res.sigma_koppa / R_iau;
    const double v_pred_phot = measured::c * cal_res.koppa / R_phot;
    const double sig_pred_phot =
        measured::c * std::sqrt(std::pow(cal_res.sigma_koppa / R_phot, 2)
                                + std::pow(cal_res.koppa * dR_phot / (R_phot * R_phot), 2));
    const double v_paper = 638.0;
    const double e_paper = 6.0;

    auto decide = [](const char* name, double vp, double sp, double vo, double so) {
        const double diff = std::abs(vp - vo);
        const double thresh = 2.0 * std::sqrt(sp * sp + so * so);
        const bool excl = diff > thresh;
        std::printf("COMPARISON — %s\n", name);
        std::printf("  v_pred = %.4f ± %.4f m/s\n", vp, sp);
        std::printf("  v_obs  = %.4f ± %.4f m/s\n", vo, so);
        std::printf("  |Δ| = %.4f   2σ = %.4f\n", diff, thresh);
        std::printf("  STATUS: %s\n",
                    excl ? "EXCLUDED"
                         : "COMPATIBLE (confirmation still UNADJUDICATED)");
        std::printf("  NOTE: σ_pred from mu uncertainty only — elliptic CV not added\n\n");
        return excl;
    };

    std::printf("GATE C3 — spectral (invariant koppa; elliptic CV not in σ)\n");
    decide("invariant surface depth @ IAU R vs 638±6",
           v_pred, std::max(sig_pred, 1e-6), v_paper, e_paper);
    decide("invariant surface depth @ phot R vs 638±6",
           v_pred_phot, sig_pred_phot, v_paper, e_paper);

    // Contrast with instantaneous mean (GOM25)
    std::printf("CONTRAST — GOM25 instantaneous mean\n");
    std::printf("  mean(v^2 r/c^2) cal = %.6f m  CV=%.6e\n",
                cal_res.koppa_inst.mean, cal_res.koppa_inst.cv);
    std::printf("  invariant koppa     = %.6f m  CV_recon=%.6e\n",
                cal_res.koppa, cal_res.koppa_recon.cv);
    std::printf("  relative (inv-inst)/inst = %.6e\n\n",
                (cal_res.koppa - cal_res.koppa_inst.mean) / cal_res.koppa_inst.mean);

    (void)atdf_record_census(tdf_path);

    std::puts("================================================================");
    std::puts("END GOM26 stdout — see GOM26_ASSESSMENT.md");
    std::puts("================================================================");
    return 0;
}
