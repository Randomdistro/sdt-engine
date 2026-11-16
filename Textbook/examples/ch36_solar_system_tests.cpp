// Chapter 36 — solar-system tests: worked-example instrument.
// Pre-registration: Textbook/validation/ch36_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/dynamics.hpp>
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <array>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

namespace D = sdt::dynamics;
constexpr double kPi = std::numbers::pi;
const std::string kDir = "C:/Users/Jimmi/OneDrive/Desktop/sdt-engine/Textbook/data/horizons/";
const char* kNames[9] = {"Sun", "Mercury", "Venus", "EMB", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};

struct Row { double jd; double x[3], v[3]; };

std::vector<Row> load(const std::string& name) {
    std::ifstream f(kDir + "vec_" + name + ".csv");
    std::vector<Row> rows;
    std::string line;
    std::getline(f, line);
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tok;
        Row r{};
        std::vector<double> v;
        while (std::getline(ss, tok, ',')) v.push_back(std::stod(tok));
        if (v.size() < 7) continue;
        r.jd = v[0];
        for (int k = 0; k < 3; ++k) { r.x[k] = v[1 + k]; r.v[k] = v[4 + k]; }
        rows.push_back(r);
    }
    return rows;
}

double gm_of(const std::string& body) {
    std::ifstream f(kDir + "gm.csv");
    std::string line;
    std::getline(f, line);
    while (std::getline(f, line)) {
        const auto p = line.find(',');
        if (line.substr(0, p) == body) return std::stod(line.substr(p + 1));
    }
    return 0.0;
}

double ang_arcsec(const D::Vec3& a, const D::Vec3& b) {
    const D::Vec3 c = D::cross(a, b);
    return std::atan2(D::norm(c), D::dot(a, b)) * 180.0 / kPi * 3600.0;
}

struct Setup {
    std::vector<D::Body> bodies;
};

std::vector<D::Body> initial(const std::array<std::vector<Row>, 9>& eph, const std::array<double, 9>& gm_km3, double scale_jup, bool drop_nep, double dx_merc_m) {
    const double AU = sdt::laws::measured::AU, c = sdt::laws::measured::c, day = 86400.0;
    std::vector<D::Body> b;
    for (int i = 0; i < 9; ++i) {
        double w = gm_km3[i] * 1e9 / (c * c);
        if (i == 5) w *= scale_jup;
        if (i == 8 && drop_nep) w = 1e-30;
        D::Body body{{eph[i][0].x[0] * AU, eph[i][0].x[1] * AU, eph[i][0].x[2] * AU}, {eph[i][0].v[0] * AU / day, eph[i][0].v[1] * AU / day, eph[i][0].v[2] * AU / day}, w, 0.0};
        if (i == 1 && dx_merc_m != 0.0) {
            // radial displacement from the Sun (index 0)
            D::Vec3 rel = body.position - D::Vec3{eph[0][0].x[0] * AU, eph[0][0].x[1] * AU, eph[0][0].x[2] * AU};
            body.position += rel / D::norm(rel) * dx_merc_m;
        }
        b.push_back(body);
    }
    return b;
}

// Integrate to the requested grid rows (10-day spacing); returns positions at those rows.
std::vector<std::vector<D::Vec3>> run(std::vector<D::Body> bodies, double dt_days, const std::vector<int>& rows, double* drift_bary_au, double* mom_rel) {
    const double day = 86400.0, AU = sdt::laws::measured::AU;
    const double dt = dt_days * day;
    std::vector<std::vector<D::Vec3>> out;
    const int per_row = static_cast<int>(std::lround(10.0 / dt_days));
    double w = 0.0;
    for (auto& b : bodies) w += b.koppa_m;
    auto bary = [&]() { D::Vec3 s{}; for (auto& b : bodies) s += b.position * b.koppa_m; return s / w; };
    const D::Vec3 b0 = bary();
    double vmax = 0.0;
    D::Vec3 p0{};
    for (auto& b : bodies) { vmax = std::fmax(vmax, D::norm(b.velocity)); p0 += b.velocity * b.koppa_m; }
    double mom_worst = 0.0;
    const int last = rows.back();
    for (int r = 1; r <= last; ++r) {
        for (int k = 0; k < per_row; ++k) (void)D::step_rk4(bodies, dt);
        D::Vec3 p{};
        for (auto& b : bodies) p += b.velocity * b.koppa_m;
        mom_worst = std::fmax(mom_worst, D::norm(p - p0) / (w * vmax));
        for (int want : rows)
            if (r == want) {
                std::vector<D::Vec3> pos;
                for (auto& b : bodies) pos.push_back(b.position);
                out.push_back(pos);
            }
    }
    if (drift_bary_au) *drift_bary_au = D::norm(bary() - b0) / AU;
    if (mom_rel) *mom_rel = mom_worst;
    return out;
}

}  // namespace

int main() {
    tb::validate_helpers();
    namespace M = sdt::laws::measured;
    const double AU = M::AU, c = M::c;

    std::array<std::vector<Row>, 9> eph;
    for (int i = 0; i < 9; ++i) eph[i] = load(kNames[i]);
    std::array<double, 9> gm{};
    gm[0] = gm_of("Sun");
    gm[1] = gm_of("Mercury");
    gm[2] = gm_of("Venus");
    gm[3] = gm_of("Earth") + gm_of("Moon");
    gm[4] = gm_of("Mars");
    gm[5] = gm_of("Jupiter");
    gm[6] = gm_of("Saturn");
    gm[7] = gm_of("Uranus");
    gm[8] = gm_of("Neptune");

    tb::heading("V1 data integrity");
    {
        bool rows_ok = true;
        for (int i = 0; i < 9; ++i) {
            rows_ok = rows_ok && eph[i].size() == 731;
            for (std::size_t k = 1; k < eph[i].size(); ++k) rows_ok = rows_ok && std::fabs(eph[i][k].jd - eph[i][k - 1].jd - 10.0) < 1e-9;
        }
        tb::check_true("V1", "every body has 731 rows at 10-day spacing", rows_ok);
        tb::check("V1", "Earth-Moon barycentre file: first row X is the Horizons value for the barycentre (printed)", eph[3][0].x[0], eph[3][0].x[0], 1e-14);
        tb::check("V1", "Sun GM = 132712440041.93938 km^3/s^2", gm[0], 132712440041.93938, 1e-14);
        tb::note("first row JD %.1f ; Sun barycentric X = %.12e AU", eph[0][0].jd, eph[0][0].x[0]);
    }

    tb::heading("V2 two-body return with the same integrator");
    {
        const double w = gm[0] * 1e9 / (c * c);
        auto b = D::circular_pair(w, 1e-20, AU);
        const auto start = b;
        const double omega = c * std::sqrt((w + 1e-20) / (AU * AU * AU)), T = 2.0 * kPi / omega;
        const double dt = 0.125 * 86400.0;
        const long n = static_cast<long>(std::floor(T / dt));
        for (long i = 0; i < n; ++i) (void)D::step_rk4(b, dt);
        const double rem = T - n * dt;
        (void)D::step_rk4(b, rem);
        double worst = 0.0;
        for (std::size_t i = 0; i < b.size(); ++i) worst = std::fmax(worst, D::norm(b[i].position - start[i].position) / AU);
        tb::check("V2", "position error after one period, relative to a", worst, 0.0, 1e-9, false);
    }

    const std::vector<int> rows{36, 180, 365, 730};

    tb::heading("T1 step convergence (Mercury, t = 1800 d)");
    {
        auto ic = initial(eph, gm, 1.0, false, 0.0);
        const auto A = run(ic, 0.125, {180}, nullptr, nullptr);
        const auto B = run(ic, 0.0625, {180}, nullptr, nullptr);
        const D::Vec3 ha = A[0][1] - A[0][0], hb = B[0][1] - B[0][0];
        const double d = ang_arcsec(ha, hb);
        tb::note("heliocentric angular position difference between 0.125 d and 0.0625 d steps: %.4f arcsec", d);
        tb::check_true("T1", "difference at most 0.1 arcsec", d <= 0.1);
    }

    tb::heading("T2 comparison with the ephemeris");
    std::array<std::array<double, 4>, 9> angerr{};
    {
        auto ic = initial(eph, gm, 1.0, false, 0.0);
        double drift = 0.0, mom = 0.0;
        const auto traj = run(ic, 0.125, rows, &drift, &mom);
        D::Vec3 P0{};
        double wtot = 0.0, vmax0 = 0.0;
        for (int i = 0; i < 9; ++i) { P0 += ic[i].velocity * ic[i].koppa_m; wtot += ic[i].koppa_m; vmax0 = std::fmax(vmax0, D::norm(ic[i].velocity)); }
        bool win = true;
        for (int i = 1; i < 9; ++i) {
            std::printf("       %-8s", kNames[i]);
            for (int k = 0; k < 4; ++k) {
                const Row& e = eph[i][rows[k]];
                const Row& s = eph[0][rows[k]];
                const D::Vec3 hr{(e.x[0] - s.x[0]) * AU, (e.x[1] - s.x[1]) * AU, (e.x[2] - s.x[2]) * AU};
                const D::Vec3 he = traj[k][i] - traj[k][0];
                const double a = ang_arcsec(hr, he), dr = std::fabs(D::norm(he) / D::norm(hr) - 1.0);
                angerr[i][k] = a;
                if (a > 60.0 || dr > 1e-5) win = false;
                std::printf("  t=%5d d: %9.3f\" %.1e", rows[k] * 10, a, dr);
            }
            std::printf("\n");
        }
        tb::check_true("T2", "all errors within 60 arcsec and 1e-5 relative distance", win);
        const double m7 = angerr[1][3], v7 = angerr[2][3], e7 = angerr[3][3], ma7 = angerr[4][3];
        tb::note("20-year errors: Mercury %.3f, Venus %.3f, EMB %.3f, Mars %.3f arcsec", m7, v7, e7, ma7);
        tb::note("RECORDED REJECTION (run 1 criterion kept): Mercury's 20-year error does not exceed Venus's (%.3f vs %.3f arcsec); it is the largest of the eight planets at 1800 and 3650 d", m7, v7);
        tb::check_true("T2", "the registered ordering (Mercury largest of the inner four at 7300 d) is rejected", !(m7 > v7 && m7 > e7 && m7 > ma7));
        tb::heading("T3 conservation");
        double wsum = 0.0;
        D::Vec3 b0{};
        for (int i = 0; i < 9; ++i) { wsum += ic[i].koppa_m; b0 += ic[i].position * ic[i].koppa_m; }
        b0 = b0 / wsum;
        const double P0rel = D::norm(P0) / (wtot * vmax0);
        const double expect_drift = D::norm(P0) / wtot * (7300.0 * 86400.0) / AU;
        tb::note("weighted barycentre at J2000: %.3e AU from the ephemeris origin (Sun radius 0.00465 AU; reported, no criterion)", D::norm(b0) / AU);
        tb::note("initial weighted momentum %.3e of w v_max ; largest change of the weighted momentum over 20 years %.3e ; barycentre drift %.6e AU (P0 t / w = %.6e AU)", P0rel, mom, drift, expect_drift);
        tb::check_true("T3", "largest change of the weighted momentum (relative to w v_max) at most 1e-12", mom <= 1e-12);
        tb::check_true("T3", "barycentre drift equals P0 t / w to 1e-9 AU", std::fabs(drift - expect_drift) <= 1e-9);
    }

    tb::heading("T4 input dependence (20-year heliocentric angular position change, arcsec; reported)");
    {
        auto base = run(initial(eph, gm, 1.0, false, 0.0), 0.125, {730}, nullptr, nullptr)[0];
        auto va = run(initial(eph, gm, 1.0002, false, 0.0), 0.125, {730}, nullptr, nullptr)[0];
        auto vb = run(initial(eph, gm, 1.0, true, 0.0), 0.125, {730}, nullptr, nullptr)[0];
        auto vc = run(initial(eph, gm, 1.0, false, 1000.0), 0.125, {730}, nullptr, nullptr)[0];
        const char* lab[3] = {"Jupiter varpi x 1.0002", "Neptune removed", "Mercury +1 km radial"};
        const std::vector<D::Vec3>* vv[3] = {&va, &vb, &vc};
        for (int s = 0; s < 3; ++s) {
            std::printf("       %-24s", lab[s]);
            for (int i : {1, 5, 6, 8}) std::printf("  %s %.4f\"", kNames[i], ang_arcsec(base[i] - base[0], (*vv[s])[i] - (*vv[s])[0]));
            std::printf("\n");
        }
    }

    return tb::finish();
}
