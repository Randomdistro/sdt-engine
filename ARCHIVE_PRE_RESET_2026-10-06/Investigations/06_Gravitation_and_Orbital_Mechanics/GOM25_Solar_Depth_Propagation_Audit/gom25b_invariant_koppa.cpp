// GOM25b — orbital-invariant solar koppa reformulation (pre-registered PROMPT_B)
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

[[nodiscard]] auto load_horizons(const std::string& path) -> std::vector<VecRow> {
    std::ifstream in(path);
    if (!in) {
        std::fprintf(stderr, "FAIL open %s\n", path.c_str());
        return {};
    }
    std::string line;
    bool in_soe = false;
    std::vector<VecRow> rows;
    while (std::getline(in, line)) {
        if (line.rfind("$$SOE", 0) == 0) { in_soe = true; continue; }
        if (line.rfind("$$EOE", 0) == 0) break;
        if (!in_soe) continue;
        auto cols = split_csv(line);
        if (cols.size() < 8) continue;
        VecRow row;
        row.jd = std::stod(cols[0]);
        const double x = std::stod(cols[2]);
        const double y = std::stod(cols[3]);
        const double z = std::stod(cols[4]);
        const double vx = std::stod(cols[5]);
        const double vy = std::stod(cols[6]);
        const double vz = std::stod(cols[7]);
        row.r_m = 1000.0 * std::sqrt(x * x + y * y + z * z);
        row.v_ms = 1000.0 * std::sqrt(vx * vx + vy * vy + vz * vz);
        if (row.r_m > 0.0 && row.v_ms > 0.0) rows.push_back(row);
    }
    return rows;
}

struct Series {
    double mean = 0;
    double stdev = 0;
    double cv = 0;
    double minv = 0;
    double maxv = 0;
    int n = 0;
};

[[nodiscard]] auto series_stats(const std::vector<double>& x) -> Series {
    Series s;
    s.n = static_cast<int>(x.size());
    if (x.empty()) return s;
    double sum = 0, sum2 = 0;
    s.minv = x.front();
    s.maxv = x.front();
    for (double v : x) {
        sum += v; sum2 += v * v;
        s.minv = std::min(s.minv, v);
        s.maxv = std::max(s.maxv, v);
    }
    const double n = static_cast<double>(s.n);
    s.mean = sum / n;
    s.stdev = std::sqrt(std::max(0.0, sum2 / n - s.mean * s.mean));
    s.cv = (s.mean != 0.0) ? s.stdev / std::abs(s.mean) : 0.0;
    return s;
}

struct KoppaPack {
    double a_m = 0;
    Series inst;
    Series vv;
    double r_mean = 0;
};

[[nodiscard]] auto compute_koppas(const std::vector<VecRow>& rows,
                                  double a_override = -1.0) -> KoppaPack {
    KoppaPack p;
    if (rows.empty()) return p;
    double rmin = rows.front().r_m, rmax = rows.front().r_m, rsum = 0;
    for (const auto& r : rows) {
        rmin = std::min(rmin, r.r_m);
        rmax = std::max(rmax, r.r_m);
        rsum += r.r_m;
    }
    p.a_m = (a_override > 0.0) ? a_override : 0.5 * (rmin + rmax);
    p.r_mean = rsum / static_cast<double>(rows.size());
    std::vector<double> inst, vv;
    for (const auto& r : rows) {
        inst.push_back(r.v_ms * r.v_ms * r.r_m / (measured::c * measured::c));
        const double denom = 2.0 / r.r_m - 1.0 / p.a_m;
        if (denom > 0.0) {
            vv.push_back(r.v_ms * r.v_ms / (measured::c * measured::c * denom));
        }
    }
    p.inst = series_stats(inst);
    p.vv = series_stats(vv);
    return p;
}

[[nodiscard]] auto half_year(const std::vector<VecRow>& rows, bool first_half)
    -> std::vector<VecRow>
{
    std::vector<VecRow> out;
    if (rows.empty()) return out;
    std::vector<double> jds;
    for (const auto& r : rows) jds.push_back(r.jd);
    std::sort(jds.begin(), jds.end());
    const double mid = jds[jds.size() / 2];
    for (const auto& r : rows) {
        if (first_half ? (r.jd < mid) : (r.jd >= mid)) out.push_back(r);
    }
    return out;
}

[[nodiscard]] bool validate_synthetic() {
    std::puts("VALIDATION — synthetic circular and elliptic mocks");
    // Circular: v^2 = μ/r ⇒ ϟ_inst = μ/c^2 = ϟ_vv
    const double mu = 1.32712440018e20; // mock two-body parameter [m^3/s^2] for fixture only
    const double r = measured::AU;
    const double v = std::sqrt(mu / r);
    const double k_inst = v * v * r / (measured::c * measured::c);
    const double a = r;
    const double k_vv = v * v / (measured::c * measured::c * (2.0 / r - 1.0 / a));
    const bool circ_ok = std::abs(k_inst - k_vv) / k_inst < 1e-12;
    std::printf("  circular mock |ϟ_inst-ϟ_vv|/ϟ = %.3e  %s\n",
                std::abs(k_inst - k_vv) / k_inst, circ_ok ? "PASS" : "FAIL");

    // Ellipse fixture: sample true anomaly, check CV(ϟ_vv) << CV(ϟ_inst)
    const double e = 0.0167;
    const double a_e = measured::AU;
    std::vector<double> inst, vv;
    for (int i = 0; i < 360; ++i) {
        const double nu = (2.0 * std::numbers::pi * i) / 360.0;
        const double rm = a_e * (1.0 - e * e) / (1.0 + e * std::cos(nu));
        const double vm = std::sqrt(mu * (2.0 / rm - 1.0 / a_e));
        inst.push_back(vm * vm * rm / (measured::c * measured::c));
        const double denom = 2.0 / rm - 1.0 / a_e;
        vv.push_back(vm * vm / (measured::c * measured::c * denom));
    }
    const auto si = series_stats(inst);
    const auto sv = series_stats(vv);
    const bool ell_ok = sv.cv < 0.1 * si.cv && sv.cv < 1e-10;
    std::printf("  elliptic mock CV_inst=%.6e CV_vv=%.6e  %s\n\n",
                si.cv, sv.cv, ell_ok ? "PASS" : "FAIL");
    return circ_ok && ell_ok;
}

void report_pack(const char* name, const KoppaPack& p) {
    std::printf("%s\n", name);
    std::printf("  N_inst=%d  N_vv=%d  a=(r_min+r_max)/2 = %.6e m\n",
                p.inst.n, p.vv.n, p.a_m);
    std::printf("  ϟ_inst mean=%.6f m  CV=%.6e\n", p.inst.mean, p.inst.cv);
    std::printf("  ϟ_vv   mean=%.6f m  CV=%.6e  min=%.6f max=%.6f\n",
                p.vv.mean, p.vv.cv, p.vv.minv, p.vv.maxv);
    std::printf("  ⟨r⟩ = %.6e m\n", p.r_mean);
}

} // namespace

int main(int argc, char** argv)
{
    const std::string y2025 =
        (argc > 1) ? argv[1]
                   : "Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2025.csv";
    const std::string y2024 =
        (argc > 2) ? argv[2]
                   : "Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2024.csv";

    std::puts("================================================================");
    std::puts("GOM25b — Orbital-invariant solar koppa (PROMPT_B)");
    std::puts("================================================================\n");

    if (!validate_synthetic()) {
        std::puts("INSTRUMENT VALIDATION FAILED");
        return 2;
    }

    auto rows25 = load_horizons(y2025);
    auto rows24 = load_horizons(y2024);
    std::printf("DATA — 2025 rows=%zu  2024 rows=%zu\n\n", rows25.size(), rows24.size());
    if (rows25.size() < 10 || rows24.size() < 10) {
        std::puts("insufficient rows");
        return 3;
    }

    const auto full25 = compute_koppas(rows25);
    const auto full24 = compute_koppas(rows24);
    report_pack("2025 FULL YEAR", full25);
    report_pack("2024 HOLD-OUT YEAR", full24);
    std::puts("");

    // Quality gate: CV_vv < 0.1 * CV_inst
    const bool qgate = full25.vv.cv < 0.1 * full25.inst.cv;
    std::printf("QUALITY GATE  CV_vv < 0.1*CV_inst : %.6e < %.6e  %s\n",
                full25.vv.cv, 0.1 * full25.inst.cv, qgate ? "PASS" : "FAIL");

    // Within-year hold-out (single full-year a; compare half means)
    auto h1 = half_year(rows25, true);
    auto h2 = half_year(rows25, false);
    const auto p1 = compute_koppas(h1, full25.a_m);
    const auto p2 = compute_koppas(h2, full25.a_m);
    const double rel_half = std::abs(p1.vv.mean - p2.vv.mean) / full25.vv.mean;
    const bool half_ok = rel_half < 5e-4;
    std::printf("HOLD-OUT H1/H2  ϟ_H1=%.6f  ϟ_H2=%.6f  |Δ|/ϟ=%.6e  thresh=5e-4  %s\n",
                p1.vv.mean, p2.vv.mean, rel_half, half_ok ? "PASS" : "FAIL");

    // Cross-year hold-out
    const double rel_year = std::abs(full25.vv.mean - full24.vv.mean) / full25.vv.mean;
    const bool year_ok = rel_year < 5e-4;
    std::printf("HOLD-OUT 2024/2025 |Δ|/ϟ=%.6e  thresh=5e-4  %s\n\n",
                rel_year, year_ok ? "PASS" : "FAIL");

    // Spectral prediction with invariant ϟ (PROMPT amendment depth differential)
    const double koppa = full25.vv.mean;
    const double R_iau = measured::R_Sun;
    const double R_phot = 695658e3;
    const double dR = 140e3;
    const double r_obs = full25.r_mean;
    const double z_spec = koppa * (1.0 / R_iau - 1.0 / r_obs);
    const double v_pred = measured::c * z_spec;
    const double sig_koppa = std::max(std::abs(p1.vv.mean - p2.vv.mean) / std::sqrt(2.0),
                                      std::abs(full25.vv.mean - full24.vv.mean) / std::sqrt(2.0));
    const double sig_v = measured::c * std::sqrt(
        std::pow(sig_koppa * (1.0 / R_iau - 1.0 / r_obs), 2) +
        std::pow(koppa * dR / (R_phot * R_phot), 2)); // radius sys when phot used
    const double v_pred_phot = measured::c * koppa * (1.0 / R_phot - 1.0 / r_obs);
    const double v_obs = 638.0;
    const double e_obs = 6.0;
    const double diff = std::abs(v_pred - v_obs);
    const double thresh = 2.0 * std::sqrt(sig_v * sig_v + e_obs * e_obs);
    const bool compatible = diff <= thresh;

    std::puts("SPECTRAL — invariant ϟ, depth differential");
    std::printf("  ϟ_Sun (2025 vv mean) = %.6f m   LABEL: COMPUTED\n", koppa);
    std::printf("  σ_ϟ (hold-out)       = %.6f m\n", sig_koppa);
    std::printf("  v_pred (IAU R)       = %.4f ± %.4f m/s\n", v_pred, sig_v);
    std::printf("  v_pred (phot R)      = %.4f m/s\n", v_pred_phot);
    std::printf("  v_obs (paper)        = %.1f ± %.1f m/s\n", v_obs, e_obs);
    std::printf("  |Δ|=%.4f  2σ=%.4f  %s\n",
                diff, thresh, compatible ? "COMPATIBLE" : "EXCLUDED");
    std::puts("  confirmation still UNADJUDICATED (CO5BOLD / lab-λ nuisances)\n");

    // Delete test
    std::printf("DELETE TEST  engine koppa_Sun unused = %.6f m; Δrel to ϟ_vv = %.6e\n",
                bridge::koppa_Sun, (koppa - bridge::koppa_Sun) / bridge::koppa_Sun);

    std::puts("\nCLASSIFICATION");
    if (qgate && half_ok && year_ok) {
        std::puts("  IC debt: RECOVERED for investigation-level invariant definition");
        std::puts("  (held-out years pass; CV gate pass). Canon not updated.");
    } else if (qgate && (half_ok || year_ok)) {
        std::puts("  IC debt: PARTIAL — quality gate ok; hold-out incomplete/fail");
    } else {
        std::puts("  IC debt: NO RECOVERY for this invariant form");
    }
    std::puts("  Spectral: COMPATIBLE/UNADJUDICATED as gated above");
    std::puts("================================================================");
    return (qgate && half_ok && year_ok) ? 0 : 1;
}
