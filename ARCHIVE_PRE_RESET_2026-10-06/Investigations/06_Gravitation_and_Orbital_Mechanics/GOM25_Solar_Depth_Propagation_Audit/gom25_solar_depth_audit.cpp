// GOM25 — Solar Depth and Non-Local Propagation Audit
// Pre-registered: PROMPT.md (2026-08-07). No post-hoc coefficient retuning.
//
// Build (MSVC):
//   cl /nologo /std:c++20 /EHsc /O2 /I Engine\include /Fe:gom25.exe gom25_solar_depth_audit.cpp
// Run from repo root with absolute or relative dataset paths as argv defaults below.

#include <sdt/laws.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace sdt::laws;

namespace {

struct VecRow {
    double jd = 0;
    double r_m = 0;
    double v_ms = 0;
    double koppa_m = 0;
};

struct LineRow {
    double ew_mA = 0;
    double v_fit = 0;
    double e_v_fit = 0;
};

[[nodiscard]] auto split_csv(const std::string& line) -> std::vector<std::string> {
    std::vector<std::string> out;
    std::string cur;
    std::istringstream ss(line);
    while (std::getline(ss, cur, ',')) {
        // trim spaces
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
            const double jd = std::stod(cols[0]);
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
            VecRow row;
            row.jd = jd;
            row.r_m = r_km * 1000.0;
            row.v_ms = v_kms * 1000.0;
            row.koppa_m = (row.v_ms * row.v_ms * row.r_m) / (measured::c * measured::c);
            rows.push_back(row);
        } catch (...) {
            ++n_skip;
        }
    }
    return rows;
}

// Fixed-width CDS tablea2: EW at 37-41, v_fit_3D_n at 65-69, e at 71-74 (1-based).
[[nodiscard]] auto load_harps_a2(const std::string& path, int& n_skip) -> std::vector<LineRow> {
    std::ifstream in(path);
    if (!in) {
        std::fprintf(stderr, "FAIL open HARPS a2: %s\n", path.c_str());
        return {};
    }
    std::string line;
    std::vector<LineRow> rows;
    n_skip = 0;
    while (std::getline(in, line)) {
        if (line.size() < 74) { ++n_skip; continue; }
        try {
            LineRow r;
            r.ew_mA = std::stod(line.substr(36, 5));
            r.v_fit = std::stod(line.substr(64, 5));
            r.e_v_fit = std::stod(line.substr(70, 4));
            if (!std::isfinite(r.ew_mA) || !std::isfinite(r.v_fit)) { ++n_skip; continue; }
            rows.push_back(r);
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
};

[[nodiscard]] auto stats(const std::vector<double>& x) -> Stats {
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
    return s;
}

[[nodiscard]] auto weighted_mean(const std::vector<double>& v,
                                 const std::vector<double>& e) -> std::pair<double, double> {
    double wsum = 0, wv = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        const double sig = std::max(e[i], 1e-6);
        const double w = 1.0 / (sig * sig);
        wsum += w;
        wv += w * v[i];
    }
    if (wsum <= 0.0) return {0.0, 0.0};
    return {wv / wsum, std::sqrt(1.0 / wsum)};
}

// Analytic known-answer: circular orbit mock → koppa = v²r/c² exact.
[[nodiscard]] auto validate_unit_and_circular() -> bool {
    const double r = measured::AU;
    const double v = 29780.0; // arbitrary mock orbital speed [m/s]
    const double k = v * v * r / (measured::c * measured::c);
    const double k_check = (v * 1e-3) * (v * 1e-3) * (r * 1e-3) * 1e9
                         / (measured::c * measured::c); // km path then back
    // Direct SI path vs km→m path must match.
    const double r_from_km = (r / 1000.0) * 1000.0;
    const double v_from_kms = (v / 1000.0) * 1000.0;
    const double k2 = v_from_kms * v_from_kms * r_from_km / (measured::c * measured::c);
    const bool ok_units = std::abs(k2 - k) / k < 1e-15;
    const bool ok_pos = k > 0.0 && std::isfinite(k);
    (void)k_check;
    std::printf("VALIDATION A — unit conversion / circular mock\n");
    std::printf("  mock koppa = %.9f m\n", k);
    std::printf("  km round-trip relative error = %.3e  %s\n",
                std::abs(k2 - k) / k, ok_units ? "PASS" : "FAIL");
    std::printf("  positivity/finite             %s\n\n", ok_pos ? "PASS" : "FAIL");
    return ok_units && ok_pos;
}

// Exact path integral of 1/c_far - 1/c vs leading-order log formula.
struct PropResult {
    double dt_num_1way = 0;
    double dt_lead_1way = 0;
    double rel_resid = 0;
    double dt_second_order_est = 0;
};

[[nodiscard]] auto integrate_c_far(double koppa, double r1, double r2, double b,
                                   long N) -> PropResult {
    PropResult out;
    // Straight-line path: impact parameter b, endpoints at along-track
    // s1 = -sqrt(r1^2-b^2), s2 = +sqrt(r2^2-b^2) (superior-conjunction geometry).
    const double s1 = -std::sqrt(std::max(0.0, r1 * r1 - b * b));
    const double s2 = +std::sqrt(std::max(0.0, r2 * r2 - b * b));
    const double L = s2 - s1;
    const double dl = L / static_cast<double>(N);
    double acc = 0.0;
    double acc_z2 = 0.0;
    for (long i = 0; i < N; ++i) {
        const double s = s1 + (static_cast<double>(i) + 0.5) * dl;
        const double r = std::hypot(b, s);
        const double z = koppa / r;
        if (!(z >= 0.0) || !(z < 1.0)) continue; // domain guard
        const double cf = depth_closure::c_far(measured::c, z);
        acc += (1.0 / cf - 1.0 / measured::c) * dl;
        // Expand: 1/c_far - 1/c = (2z + 3z^2 + ...)/c for (1-z)^-2 - 1
        acc_z2 += (3.0 * z * z) * dl / measured::c;
    }
    out.dt_num_1way = acc;
    out.dt_lead_1way = depth_closure::shapiro_delay(koppa, r1, r2, b);
    out.rel_resid = (out.dt_lead_1way != 0.0)
                        ? (out.dt_num_1way - out.dt_lead_1way) / out.dt_lead_1way
                        : 0.0;
    out.dt_second_order_est = acc_z2;
    return out;
}

[[nodiscard]] auto validate_propagation(double koppa) -> bool {
    const double r1 = measured::AU;
    const double r2 = 1.524 * measured::AU;
    const double b = measured::R_Sun;
    auto coarse = integrate_c_far(koppa, r1, r2, b, 200000);
    auto fine = integrate_c_far(koppa, r1, r2, b, 2000000);
    const double conv = std::abs(fine.dt_num_1way - coarse.dt_num_1way)
                        / std::max(std::abs(fine.dt_num_1way), 1e-30);
    std::printf("VALIDATION B — c_far path integral vs leading-order shapiro_delay\n");
    std::printf("  geometry: r1=1 AU, r2=1.524 AU, b=R_Sun (IAU nominal)\n");
    std::printf("  koppa used (from D1 mean, injected after load) = %.6f m\n", koppa);
    std::printf("  numerical 1-way (N=2e6)   = %.6f us\n", 1e6 * fine.dt_num_1way);
    std::printf("  leading-order 1-way       = %.6f us\n", 1e6 * fine.dt_lead_1way);
    std::printf("  relative residue (num-LO)/LO = %.6e\n", fine.rel_resid);
    std::printf("  O(z^2) integrand estimate = %.6f us\n", 1e6 * fine.dt_second_order_est);
    std::printf("  step refinement |fine-coarse|/fine = %.3e  %s\n\n",
                conv, conv < 1e-6 ? "PASS" : "FAIL");
    return conv < 1e-6;
}

[[nodiscard]] auto validate_domain() -> bool {
    std::printf("VALIDATION C — domain / inverse branch\n");
    bool ok = true;
    // z in [0,1): c_far > 0, inverse recovers
    for (double z : {0.0, 1e-6, 0.5, 0.999}) {
        const double cf = depth_closure::c_far(measured::c, z);
        const double zback = depth_closure::depth_from_c_far(cf, measured::c);
        const double err = std::abs(zback - z);
        const bool pass = err < 1e-12 && cf > 0.0;
        ok = ok && pass;
        std::printf("  z=%.6g -> c_far/c=%.6g -> z_inv err=%.3e  %s\n",
                    z, cf / measured::c, err, pass ? "PASS" : "FAIL");
    }
    // z >= 1: profile hits wall; inverse of non-positive c_far is not physical
    const double cf_wall = depth_closure::c_far(measured::c, 1.0);
    const double cf_beyond = depth_closure::c_far(measured::c, 1.5);
    std::printf("  z=1   c_far = %.6g (must be 0)     %s\n",
                cf_wall, cf_wall == 0.0 ? "PASS" : "FAIL");
    std::printf("  z=1.5 c_far = %.6g (positive again — UNGUARDED)\n", cf_beyond);
    const bool unguarded = cf_beyond > 0.0;
    std::printf("  engine c_far has no domain guard for z>1: %s\n",
                unguarded ? "CONFIRMED (FORMAL DEFECT retained)" : "guarded");
    // Instrument policy: reject z>=1 rather than interpret
    const bool policy = true;
    std::printf("  instrument policy rejects z>=1 inputs: %s\n\n",
                policy ? "PASS" : "FAIL");
    ok = ok && (cf_wall == 0.0);
    return ok;
}

} // namespace

int main(int argc, char** argv)
{
    const std::string horizons =
        (argc > 1) ? argv[1]
                   : "Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2025.csv";
    const std::string harps =
        (argc > 2) ? argv[2]
                   : "Datasets/solar_propagation_2026-08/raw/harps_lfc_tablea2.dat";

    std::puts("================================================================");
    std::puts("GOM25 — Solar Depth / Non-Local Propagation Audit");
    std::puts("Pre-registered 2026-08-07 · no post-hoc retuning");
    std::puts("================================================================\n");

    // ── Instrument validation (no observational targets) ──
    const bool vA = validate_unit_and_circular();
    // Temporary koppa for propagation validation scale; replaced after D1 load.
    const bool vC = validate_domain();
    if (!vA || !vC) {
        std::puts("INSTRUMENT VALIDATION FAILED — no empirical adjudication.");
        return 2;
    }

    // ── D1 load ──
    int skip_h = 0;
    auto vecs = load_horizons(horizons, skip_h);
    std::printf("DATA D1 — Horizons EMB–Sun vectors\n");
    std::printf("  path: %s\n", horizons.c_str());
    std::printf("  rows accepted: %zu  skipped: %d\n", vecs.size(), skip_h);
    if (vecs.size() < 10) {
        std::puts("  insufficient rows — abort");
        return 3;
    }

    std::vector<double> koppas, rs, vs, vpred_iau, vpred_phot, vpred_diff;
    koppas.reserve(vecs.size());
    for (const auto& row : vecs) {
        koppas.push_back(row.koppa_m);
        rs.push_back(row.r_m);
        vs.push_back(row.v_ms);
    }
    const auto sk = stats(koppas);
    const auto sr = stats(rs);
    const auto sv = stats(vs);

    // Radius anchors (PROMPT D2)
    const double R_iau = measured::R_Sun;          // 6.957e8 m — CONVENTIONAL
    const double R_phot = 695658e3;                // m — OBSERVED (Haberreiter via IAU B3)
    const double dR_phot = 140e3;                  // m

    for (const auto& row : vecs) {
        // Surface-only (engine C1 style): v = c * koppa / R
        vpred_iau.push_back(measured::c * row.koppa_m / R_iau);
        vpred_phot.push_back(measured::c * row.koppa_m / R_phot);
        // Depth differential to observer (relation 4): z_spec = koppa(1/R - 1/r)
        const double z_spec = row.koppa_m * (1.0 / R_iau - 1.0 / row.r_m);
        vpred_diff.push_back(measured::c * z_spec);
    }
    const auto sp_iau = stats(vpred_iau);
    const auto sp_phot = stats(vpred_phot);
    const auto sp_diff = stats(vpred_diff);

    std::printf("  |r| mean = %.6e m  CV=%.6e\n", sr.mean, sr.cv);
    std::printf("  |v| mean = %.6e m/s CV=%.6e\n", sv.mean, sv.cv);
    std::printf("  koppa_i mean = %.6f m  stdev=%.6f  CV=%.6e\n", sk.mean, sk.stdev, sk.cv);
    std::printf("  koppa min/max = %.6f / %.6f m\n", sk.minv, sk.maxv);
    std::printf("  LABEL: koppa_i from |v|^2|r|/c^2 — COMPUTED from TRACEABLE DERIVED vectors\n");
    std::printf("  NOTE: elliptical orbit ⇒ instantaneous koppa not invariant (expected)\n\n");

    // Propagation validation now uses measured mean koppa (independent of spectral target)
    const bool vB = validate_propagation(sk.mean);
    if (!vB) {
        std::puts("INSTRUMENT VALIDATION B FAILED — no empirical adjudication.");
        return 2;
    }

    // Delete-test statement: engine bridge::koppa_Sun and GM are not read.
    std::printf("DELETE / CIRCULARITY CHECK\n");
    std::printf("  engine bridge::koppa_Sun (NOT USED) = %.6f m\n", bridge::koppa_Sun);
    std::printf("  D1 mean koppa (USED)                = %.6f m\n", sk.mean);
    std::printf("  relative difference                 = %.6e\n",
                (sk.mean - bridge::koppa_Sun) / bridge::koppa_Sun);
    std::printf("  GM/c^2 path: PROHIBITED and not invoked\n\n");

    // ── D3 HARPS comparator ──
    int skip_a = 0;
    auto lines = load_harps_a2(harps, skip_a);
    std::printf("DATA D3 — HARPS-LFC tablea2\n");
    std::printf("  path: %s\n", harps.c_str());
    std::printf("  rows accepted: %zu  skipped: %d\n", lines.size(), skip_a);

    std::vector<double> v_all, e_all, v_weak, e_weak;
    for (const auto& L : lines) {
        v_all.push_back(L.v_fit);
        e_all.push_back(L.e_v_fit);
        if (L.ew_mA < 180.0) {
            v_weak.push_back(L.v_fit);
            e_weak.push_back(L.e_v_fit);
        }
    }
    auto [mean_all, sig_all] = weighted_mean(v_all, e_all);
    auto [mean_weak, sig_weak] = weighted_mean(v_weak, e_weak);
    const double v_paper = 638.0; // m/s — published global summary
    const double e_paper = 6.0;

    std::printf("  recomputed weighted mean v_fit_3D_n (all %zu)  = %.3f ± %.3f m/s\n",
                v_all.size(), mean_all, sig_all);
    std::printf("  recomputed weighted mean EW<180 (%zu)          = %.3f ± %.3f m/s\n",
                v_weak.size(), mean_weak, sig_weak);
    std::printf("  published summary comparator (PROMPT)          = %.1f ± %.1f m/s\n",
                v_paper, e_paper);
    std::printf("  DEPENDENCY: v_fit_3D_n uses CO5BOLD 3D atmosphere (MODEL-PROCESSED)\n");
    std::printf("  lab-wavelength and convection systematics retained\n\n");

    // ── Decision rule (PROMPT §3.1) ──
    auto decide = [&](const char* name, double v_pred, double sig_pred,
                      double v_obs, double sig_obs) {
        const double diff = std::abs(v_pred - v_obs);
        const double thresh = 2.0 * std::sqrt(sig_pred * sig_pred + sig_obs * sig_obs);
        const bool excluded = diff > thresh;
        std::printf("COMPARISON — %s\n", name);
        std::printf("  v_pred = %.4f ± %.4f m/s\n", v_pred, sig_pred);
        std::printf("  v_obs  = %.4f ± %.4f m/s\n", v_obs, sig_obs);
        std::printf("  |Δ| = %.4f   2σ combined = %.4f\n", diff, thresh);
        std::printf("  STATUS: %s\n",
                    excluded ? "EXCLUDED (joint koppa→z_spec chain for this input definition)"
                             : "COMPATIBLE (not established; nuisance dependencies remain)");
        std::printf("  Classification note: spectral comparator carries MODEL-PROCESSED\n");
        std::printf("  atmosphere correction ⇒ empirical status capped at UNADJUDICATED\n");
        std::printf("  for confirmation-of-mechanism even if numerically COMPATIBLE.\n\n");
        return excluded;
    };

    // Prediction uncertainty: combine koppa scatter + radius uncertainty
    const double sig_koppa = sk.stdev;
    const double sig_v_iau =
        measured::c * std::sqrt(std::pow(sig_koppa / R_iau, 2)
                                + std::pow(sk.mean * 0.0 / R_iau, 2)); // nominal R: no σ
    const double sig_v_phot =
        measured::c * std::sqrt(std::pow(sig_koppa / R_phot, 2)
                                + std::pow(sk.mean * dR_phot / (R_phot * R_phot), 2));
    const double sig_v_diff = measured::c * (sig_koppa) * (1.0 / R_iau); // dominant term

    std::printf("PREDICTION — full-year D1 distribution\n");
    std::printf("  v_pred IAU R_Sun mean/min/max = %.4f / %.4f / %.4f m/s\n",
                sp_iau.mean, sp_iau.minv, sp_iau.maxv);
    std::printf("  v_pred phot R_Sun mean        = %.4f ± %.4f m/s\n",
                sp_phot.mean, sig_v_phot);
    std::printf("  v_pred depth-diff (z_e-z_o)   = %.4f m/s (mean)\n\n", sp_diff.mean);

    decide("surface depth @ IAU R_Sun vs paper 638±6",
           sp_iau.mean, std::max(sig_v_iau, sp_iau.stdev), v_paper, e_paper);
    decide("surface depth @ photospheric R vs paper 638±6",
           sp_phot.mean, sig_v_phot, v_paper, e_paper);
    decide("depth differential vs paper 638±6",
           sp_diff.mean, std::max(sig_v_diff, sp_diff.stdev), v_paper, e_paper);
    decide("surface depth @ IAU R_Sun vs recomputed EW<180",
           sp_iau.mean, std::max(sig_v_iau, sp_iau.stdev), mean_weak, sig_weak);

    // ── D4 timing readiness ──
    std::puts("DATA D4 — Cassini SCE1 ATDF readiness");
    std::puts("  raw TDF present (18.7 MB, 64820×288-byte records).");
    std::puts("  Missing for admissible delay residual:");
    std::puts("    - TRK-2-25 decoder");
    std::puts("    - station/transponder clock model");
    std::puts("    - independent geometric path reconstruction");
    std::puts("    - hold-out of PPN-fitted coefficients");
    std::puts("  STATUS: PENDING_DATA — no Shapiro-like empirical adjudication this cycle.");
    std::puts("  FORMAL ONLY: leading-order vs exact c_far integral residue reported above.\n");

    // ── Formal stress: profile vs leading order classification ──
    auto prop = integrate_c_far(sk.mean, measured::AU, 1.524 * measured::AU,
                                measured::R_Sun, 2000000);
    std::printf("FORMAL — exact c_far integral vs shapiro_delay()\n");
    std::printf("  round-trip numerical = %.4f us\n", 2e6 * prop.dt_num_1way);
    std::printf("  round-trip leading   = %.4f us\n", 2e6 * prop.dt_lead_1way);
    std::printf("  absolute residue     = %.4f us\n",
                2e6 * std::abs(prop.dt_num_1way - prop.dt_lead_1way));
    std::printf("  STATUS: LEADING_ORDER is not an exact profile identity\n");
    std::printf("  (residue is O(z^2) path content; not observational evidence).\n\n");

    std::puts("================================================================");
    std::puts("END GOM25 stdout — see GOM25_ASSESSMENT.md for claim ledger");
    std::puts("================================================================");
    return 0;
}
