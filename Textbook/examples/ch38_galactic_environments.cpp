// Chapter 38 — galactic environments: worked-example instrument.
// Pre-registration: Textbook/validation/ch38_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>
#include <sdt/galactic.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

namespace {

constexpr double kPi = std::numbers::pi;

double I_nu(int nu, double x) {
    const int N = 400;
    double s = 0.0;
    for (int k = 0; k < N; ++k) {
        const double th = kPi * (k + 0.5) / N;
        s += std::exp(x * std::cos(th)) * std::cos(nu * th);
    }
    return s / N;
}

double K_nu(int nu, double x) {
    const double h = 0.01;
    double s = 0.5 * std::exp(-x);
    for (int k = 1; k < 3000; ++k) {
        const double t = k * h, e = std::exp(-x * std::cosh(t));
        if (e < 1e-300) break;
        s += e * std::cosh(nu * t);
    }
    return s * h;
}

// Disc circular speed squared in units of c^2 varpi_d / h_R:  2 y^2 [I0 K0 - I1 K1], y = R/(2 h_R)
double disc_v2(double R_over_h) {
    const double y = 0.5 * R_over_h;
    return 2.0 * y * y * (I_nu(0, y) * K_nu(0, y) - I_nu(1, y) * K_nu(1, y));
}

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

}  // namespace

int main() {
    namespace MW = sdt::galactic::milky_way;
    namespace B = sdt::laws::bridge;
    namespace M = sdt::laws::measured;
    tb::validate_helpers();
    const double c = M::c, kpc = sdt::galactic::kpc_m;

    tb::heading("V1 Bessel functions, Wronskian, spherical limit");
    {
        tb::check("V1", "I0(1) = 1.2660658777", I_nu(0, 1.0), 1.2660658777, 1e-9);
        tb::check("V1", "K0(1) = 0.4210244382", K_nu(0, 1.0), 0.4210244382, 1e-9);
        tb::check("V1", "I1(1) = 0.5651591040", I_nu(1, 1.0), 0.5651591040, 1e-9);
        tb::check("V1", "K1(1) = 0.6019072302", K_nu(1, 1.0), 0.6019072302, 1e-9);
        double w = 0.0;
        for (double x : {0.3, 1.0, 4.0, 10.0}) w = std::fmax(w, std::fabs((I_nu(0, x) * K_nu(1, x) + I_nu(1, x) * K_nu(0, x)) * x - 1.0));
        tb::check("V1", "Wronskian I0 K1 + I1 K0 = 1/x, worst relative", w, 0.0, 1e-12, false);
        const double R = 200.0;
        const double y = 0.5 * R;
        tb::check("V1", "disc speed^2 x R = 1 + 9/(8 y^2) at R = 200 h_R (spherical limit with its leading correction)", disc_v2(R) * R, 1.0 + 9.0 / (8.0 * y * y), 1e-6);
    }

    const double varpi_bar = MW::M_bar_Msun * B::koppa_Sun;

    tb::heading("T1 source length implied by the observed rotation curve");
    {
        std::vector<double> lx, ly;
        for (int i = 0; i < MW::N_RC; ++i) {
            const double r = MW::rc_table[i].r_pc * 3.085677581e16, v = MW::rc_table[i].v_kms * 1e3;
            const double om = v * v * r / (c * c);
            if (MW::rc_table[i].r_pc >= 5000.0 && MW::rc_table[i].r_pc <= 14000.0) { lx.push_back(std::log(r)); ly.push_back(std::log(om)); }
            if (i % 4 == 0 || i == MW::N_RC - 1) tb::note("r = %8.2f pc : v = %6.1f km/s ; Om_eff = %.4e m ; Om_eff/varpi_bar = %.3f", MW::rc_table[i].r_pc, MW::rc_table[i].v_kms, om, om / varpi_bar);
        }
        double sx = 0, sy = 0, sxx = 0, sxy = 0;
        const int n = static_cast<int>(lx.size());
        for (int i = 0; i < n; ++i) { sx += lx[i]; sy += ly[i]; sxx += lx[i] * lx[i]; sxy += lx[i] * ly[i]; }
        const double slope = (n * sxy - sx * sy) / (n * sxx - sx * sx);
        const double om8 = std::pow(MW::v_at_kpc(8.178) * 1e3, 2) * 8.178 * kpc / (c * c);
        tb::note("varpi_bar = M_bar x koppa_Sun = %.6e m ; slope of ln Om_eff against ln r over 5-14 kpc (%d points) = %.4f ; Om_eff(8.178 kpc)/varpi_bar = %.3f", varpi_bar, n, slope, om8 / varpi_bar);
        tb::check_true("T1", "slope over 5-14 kpc lies in [0.9, 1.1]", slope >= 0.9 && slope <= 1.1);
    }

    tb::heading("T2 reconstruction is an identity");
    {
        double w = 0.0;
        for (int i = 0; i < MW::N_RC; ++i) {
            const double r = MW::rc_table[i].r_pc * 3.085677581e16, v = MW::rc_table[i].v_kms * 1e3;
            const double om = v * v * r / (c * c);
            w = std::fmax(w, std::fabs(c * std::sqrt(om / r) / v - 1.0));
        }
        Rng g{38};
        for (int i = 0; i < 200; ++i) {
            const double r = 1e18 * std::exp(8.0 * g.next()), v = 1e4 + 4e5 * g.next();
            const double om = v * v * r / (c * c);
            w = std::fmax(w, std::fabs(c * std::sqrt(om / r) / v - 1.0));
        }
        tb::check("T2", "v_pred = c sqrt(Om_eff/r) against v, table and 200 random curves, worst relative", w, 0.0, 1e-14, false);
        double z = 0.0;
        for (int i = 0; i < 100; ++i) z = std::fmax(z, std::fabs(MW::zk2_at(0.05 + 24.9 * i / 99.0) - 1.0));
        tb::check("T2", "zk2_at = 1 at 100 radii, worst deviation", z, 0.0, 1e-14, false);
    }

    tb::heading("T3 extended-source geometry: exponential disc against the scalar enclosed value");
    {
        double rmax = 0.0, at = 0.0;
        for (int i = 0; i <= 600; ++i) {
            const double R = 0.1 + 29.9 * i / 600.0;
            const double m = 1.0 - std::exp(-R) * (1.0 + R);
            const double ratio = disc_v2(R) / (m / R);
            if (ratio > rmax) { rmax = ratio; at = R; }
        }
        std::string line;
        char buf[64];
        for (double R : {0.5, 1.0, 2.2, 5.0, 10.0, 20.0}) {
            const double m = 1.0 - std::exp(-R) * (1.0 + R);
            std::snprintf(buf, sizeof buf, "R/h=%.1f: %.4f  ", R, disc_v2(R) / (m / R));
            line += buf;
        }
        tb::note("disc/scalar-enclosed speed^2 ratio: %s", line.c_str());
        tb::note("maximum ratio %.4f at R/h_R = %.2f", rmax, at);
        const double m20 = 1.0 - std::exp(-20.0) * 21.0;
        tb::note("RECORDED REJECTION (run 1 criterion kept): the registered maximum 1.9-2.3 is not found; the computed maximum is %.4f at R/h_R = %.2f", rmax, at);
        tb::check_true("T3", "the registered statement (maximum between 1.9 and 2.3) is rejected", !(rmax > 1.9 && rmax < 2.3));
        tb::check_true("T3", "the maximum lies between 1.2 and 1.5 at R/h_R between 1.5 and 3.5 (corrected result, recorded)", rmax > 1.2 && rmax < 1.5 && at > 1.5 && at < 3.5);
        tb::check_true("T3", "ratio at R = 20 h_R within 2% of 1", std::fabs(disc_v2(20.0) / (m20 / 20.0) - 1.0) < 0.02);
    }

    tb::heading("T4 baryon-only exponential disc against the stored rotation curve");
    {
        const double hR = MW::h_R_kpc * kpc;
        std::printf("       radius (kpc)   v_disc (km/s)   v_obs (km/s)   ratio\n");
        double r8 = 0.0, r25 = 0.0, v8 = 0.0, v25 = 0.0;
        for (double Rk : {5.0, 8.178, 11.0, 16.0, 25.0}) {
            const double v2 = c * c * varpi_bar / hR * disc_v2(Rk / MW::h_R_kpc);
            const double v = std::sqrt(v2) / 1e3, vo = MW::v_at_kpc(Rk);
            std::printf("       %8.3f %14.1f %14.1f %9.3f\n", Rk, v, vo, v / vo);
            if (Rk == 8.178) { r8 = v / vo; v8 = v; }
            if (Rk == 25.0) { r25 = v / vo; v25 = v; }
        }
        tb::check_true("T4", "v_disc(8.178)/229 lies in [0.7, 0.9]", r8 >= 0.7 && r8 <= 0.9);
        tb::check_true("T4", "v_disc(25)/185 is below 0.6", r25 < 0.6);
        tb::check_true("T4", "v_disc(25 kpc) < v_disc(8.178 kpc): the baryon-only curve declines", v25 < v8);
    }

    return tb::finish();
}
