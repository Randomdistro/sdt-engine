// Chapter 48 — elapsed recurrence and cosmic dynamics: worked-example instrument.
// Pre-registration: Textbook/validation/ch48_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/cosmology.hpp>
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <functional>
#include <limits>

namespace {

namespace M = sdt::laws::measured;
namespace RA = sdt::laws::bridge::release_acoustics;
constexpr double PI = 3.14159265358979323846;

// Elapsed duration  integral dS / (C F).  Refuses (NaN) when C*F changes sign or vanishes on the route.
double elapsed(const std::function<double(double)>& C, const std::function<double(double)>& F, double S0, double S1, int panels = 400) {
    const int scan = 20000;
    double prev = C(S0) * F(S0);
    for (int i = 1; i <= scan; ++i) {
        const double S = S0 + (S1 - S0) * i / scan;
        const double cur = C(S) * F(S);
        if (cur * prev <= 0.0) return std::numeric_limits<double>::quiet_NaN();
        prev = cur;
    }
    return tb::integrate([&](double S) { return 1.0 / (C(S) * F(S)); }, S0, S1, 32, panels);
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    {
        const double d = elapsed([](double S) { return 1.0 - 0.5 * S; }, [](double) { return 1.0; }, 0.0, 1.0);
        tb::check("V1", "int_0^1 dS/(1 - S/2) = 2 ln 2", d, 2.0 * std::log(2.0), 1e-10);
        const double e = elapsed([](double) { return 1.0; }, [](double S) { return 1.0 - 2.0 * S; }, 0.0, 0.25);
        tb::check("V1", "int_0^0.25 dS/(1 - 2S) = (1/2) ln 2", e, 0.5 * std::log(2.0), 1e-10);
        tb::check("V1", "c_s = c/sqrt(5.25)", RA::sound_speed(RA::equality_loading), M::c / std::sqrt(5.25), 1e-12);
    }

    tb::heading("T1 elapsed duration from a route and a rate");
    {
        tb::check("T1", "C = 0.8, F = 2: 0.625", elapsed([](double) { return 0.8; }, [](double) { return 2.0; }, 0.0, 1.0), 0.625, 1e-12);
        tb::check("T1", "C = 1 - S/2, F = 1: 2 ln 2", elapsed([](double S) { return 1.0 - 0.5 * S; }, [](double) { return 1.0; }, 0.0, 1.0), 2.0 * std::log(2.0), 1e-10);
        double prev = 0.0;
        bool inc = true;
        for (double eps : {1e-2, 1e-4}) {
            const double d = elapsed([](double S) { return 1.0 - S; }, [](double) { return 1.0; }, 0.0, 1.0 - eps, 4000);
            char lab[96];
            std::snprintf(lab, sizeof lab, "C = 1 - S, F = 1 up to 1 - eps, eps = %g: ln(1/eps)", eps);
            tb::check("T1", lab, d, std::log(1.0 / eps), 1e-8);
            inc = inc && d > prev;
            prev = d;
        }
        tb::check_true("T1", "the duration increases as the route approaches the zero of C (no finite limit at S = 1)", inc);
        const double eps = 1e-3;
        tb::check("T1", "C = 1, F = 1 - 2S up to 0.5 - eps/2: -(1/2) ln eps", elapsed([](double) { return 1.0; }, [](double S) { return 1.0 - 2.0 * S; }, 0.0, 0.5 - 0.5 * eps, 4000), -0.5 * std::log(eps), 1e-8);
        const double across = elapsed([](double) { return 1.0; }, [](double S) { return 1.0 - 2.0 * S; }, 0.0, 0.7);
        tb::check_true("T1", "a route that crosses a zero of F is refused (not defined)", std::isnan(across));
    }

    tb::heading("T2 local relay cycle counts and the tick-rate ratio");
    {
        const double C = 0.9, dtau = 1e-15, Tr = 1e-6;
        const double dt_hop = dtau / C;
        const double N_remote = Tr / dt_hop;
        const double N_local = (C * Tr) / dtau;
        tb::note("N (remote convention) = %.9e ; N (local convention) = %.9e", N_remote, N_local);
        tb::check("T2", "the two consistent conventions agree", N_remote, N_local, 1e-12);
        const double N_mix1 = Tr / dtau;           // remote duration with the local hop
        const double N_mix2 = (C * Tr) / dt_hop;   // local duration with the remote hop
        tb::note("mixed: remote duration / local hop = %.9e (x%.6f) ; local duration / remote hop = %.9e (x%.6f)", N_mix1, N_mix1 / N_remote, N_mix2, N_mix2 / N_remote);
        tb::check("T2", "remote duration with the local hop is high by 1/C", N_mix1 / N_remote, 1.0 / C, 1e-12);
        tb::check("T2", "local duration with the remote hop is low by C", N_mix2 / N_remote, C, 1e-12);
    }

    tb::heading("T3 a relation traversed either way; the law selects the progression");
    {
        const double T10 = 400.0, T20 = 300.0;
        for (double k : {0.7, -0.7}) {
            double T1 = T10, T2 = T20;
            const double tau_max = (k > 0) ? 2.0 : 1.0;  // k < 0 leaves the positive-temperature domain at ln7/(2|k|) = 1.3899
            const int n = 200000;
            const double h = tau_max / n;
            double worst_sum = 0.0;
            auto rate = [&](double a, double b) { return -k * (a - b); };
            for (int i = 0; i < n; ++i) {
                const double k1 = rate(T1, T2);
                const double k2 = rate(T1 + 0.5 * h * k1, T2 - 0.5 * h * k1);
                const double k3 = rate(T1 + 0.5 * h * k2, T2 - 0.5 * h * k2);
                const double k4 = rate(T1 + h * k3, T2 - h * k3);
                const double d = h * (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
                T1 += d;
                T2 -= d;
                worst_sum = std::fmax(worst_sum, std::fabs((T1 + T2) / (T10 + T20) - 1.0));
            }
            const double sep = T1 - T2, sep_exact = (T10 - T20) * std::exp(-2.0 * k * tau_max);
            const double S0 = std::log(T10) + std::log(T20), S1 = std::log(T1) + std::log(T2);
            char lab[128];
            std::snprintf(lab, sizeof lab, "k = %+.1f: T1 + T2 conserved (worst relative deviation)", k);
            tb::check("T3", lab, worst_sum, 0.0, 1e-12, false);
            std::snprintf(lab, sizeof lab, "k = %+.1f: separation equals Delta_0 exp(-2 k tau)", k);
            tb::check("T3", lab, sep, sep_exact, 1e-9);
            tb::note("k = %+.1f: separation %.6f -> %.6f ; ln T1 + ln T2: %.8f -> %.8f", k, T10 - T20, sep, S0, S1);
            if (k > 0) tb::check_true("T3", "k > 0: the entropy-like function increases", S1 > S0);
            else {
                tb::check_true("T3", "k < 0 (tau in [0,1], inside the domain): the entropy-like function decreases", S1 < S0);
                const double tau_exit = std::log(0.5 * (T10 + T20) / (0.5 * (T10 - T20))) / (2.0 * std::fabs(k));
                tb::note("POST-RUN clause: the law with k < 0 reaches T2 = 0 at tau = ln(7)/(2|k|) = %.6f", tau_exit);
                tb::check("T3", "POST-RUN clause: exit time from the positive-temperature domain is ln 7/(2|k|)", tau_exit, std::log(7.0) / 1.4, 1e-9);
            }
            // rate check at the start by central difference on the analytic solution
            const double eps = 1e-6;
            auto Sf = [&](double tau) {
                const double m = 0.5 * (T10 + T20), s = 0.5 * (T10 - T20) * std::exp(-2.0 * k * tau);
                return std::log(m + s) + std::log(m - s);
            };
            const double dS = (Sf(eps) - Sf(-eps)) / (2 * eps);
            tb::check("T3", "dS/dtau = k (T1 - T2)^2 / (T1 T2) at tau = 0", dS, k * (T10 - T20) * (T10 - T20) / (T10 * T20), 1e-6);
        }
    }

    tb::heading("T4 coupled acoustic history");
    {
        const double zeta3 = RA::zeta3;
        const double kw = M::k_B * M::T_CMB / (M::h * M::c);
        const double n_gamma = 16.0 * PI * zeta3 * kw * kw * kw;
        const double n_b0 = RA::eta_bbn_deuterium * n_gamma;
        const double rho_rad = M::a_rad * std::pow(M::T_CMB, 4) / (M::c * M::c);
        const double N = (n_b0 * M::m_p) / rho_rad;
        const double n_b = n_b0 * N * N * N;
        const double cs = M::c / std::sqrt(3.0 * (1.0 + 0.75));
        const double Gamma = M::c * std::sqrt((8.0 * PI / 3.0) * sdt::laws::bridge::koppa_per_baryon * n_b);
        const double Leq = cs / (2.0 * Gamma);
        const double present = N * Leq;
        constexpr double Mpc = 3.0856775814913673e22;
        tb::note("photon count %.6e m^-3 ; present baryon count %.6e m^-3 ; epoch index N = %.6f", n_gamma, n_b0, N);
        tb::note("escape rate %.6e s^-1 ; standing radius %.6e m ; present-equivalent scale %.6e m = %.4f Mpc", Gamma, Leq, present, present / Mpc);
        tb::check("T4", "independent recomputation equals the engine's present-equivalent scale", present, RA::present_equivalent_scale_m, 1e-9);
        const double Mpc_native = present / Mpc;
        tb::check_true("T4", "the native value lies in the registered window [14.7, 1470] Mpc", Mpc_native >= 14.7 && Mpc_native <= 1470.0);
        // Measured BAO scale read only now.
        const double BAO = sdt::cosmology::pre_clearing::BAO_scale;
        tb::note("read now: BAO scale 147 Mpc = %.6e m ; ratio present-equivalent / 147 Mpc = %.4f", BAO, present / BAO);
        const double t_coupled = BAO / cs;
        tb::note("compatibility duration 147 Mpc / c_s = %.6e s = %.1f Myr", t_coupled, t_coupled / (3.15576e7 * 1e6));
        const double Myr_loaded = t_coupled / (3.15576e7 * 1e6);
        tb::note("RECORDED REJECTION (run 1 criterion kept): the registration applied the release_acoustics speed to the pre_clearing statement; duration %.2f Myr", Myr_loaded);
        tb::check_true("T4", "the registered statement (147 Mpc / c_s of release_acoustics = 830 Myr to 1 per cent) is rejected", !(std::fabs(Myr_loaded / 830.0 - 1.0) <= 1e-2));
        const double t_relay = BAO / sdt::cosmology::pre_clearing::c_s;
        const double Myr_relay = t_relay / (3.15576e7 * 1e6);
        tb::note("POST-RUN clause: 147 Mpc / (c/sqrt3) = %.2f Myr ; ratio of the two durations %.9f (sqrt 1.75 = %.9f)", Myr_relay, Myr_loaded / Myr_relay, std::sqrt(1.75));
        tb::check("T4", "POST-RUN clause: with pre_clearing::c_s the duration reproduces 830 Myr to 1 per cent", Myr_relay, 830.0, 1e-2);
        tb::check("T4", "POST-RUN clause: the two durations differ by sqrt(1.75)", Myr_loaded / Myr_relay, std::sqrt(1.75), 1e-12);
        tb::check("T4", "doubling the assumed scale doubles the compatibility duration", (2.0 * BAO / cs) / t_coupled, 2.0, 1e-12);
    }

    return tb::finish();
}
