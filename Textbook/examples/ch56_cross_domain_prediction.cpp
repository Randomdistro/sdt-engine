// Chapter 56 — cross-domain prediction: worked-example instrument.
// Pre-registration: Textbook/validation/ch56_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <numbers>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
namespace TR = sdt::laws::law_IV::transport;
constexpr double PI = std::numbers::pi;
constexpr double AMU = 1.66053906660e-27;
const double MASS = 39.948 * AMU;

struct Ratios {
    double Pr, Sc, Le;
};

Ratios ratios(double T, double P, double b) {
    const auto s = TR::monatomic_state(T, P, MASS, b);
    const double n = P / (M::k_B * T), rho = n * MASS, cp = 2.5 * M::k_B / MASS;
    return {cp * s.dynamic_viscosity_Pa_s / s.thermal_conductivity_W_mK, s.dynamic_viscosity_Pa_s / (rho * s.self_diffusivity_m2_s),
            s.thermal_conductivity_W_mK / (rho * cp * s.self_diffusivity_m2_s)};
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    {
        const auto r = ratios(300.0, 1e5, 1.9e-10);
        tb::check("V1", "Pr = 2/3 for one state", r.Pr, 2.0 / 3.0, 1e-14);
        tb::check("V1", "Sc = 5/6 for one state", r.Sc, 5.0 / 6.0, 1e-14);
        tb::check("V1", "Le = 5/4 for one state", r.Le, 5.0 / 4.0, 1e-14);
        const double b = 2.0, L = 1e4 * b;
        const double q = tb::integrate([&](double l) { return 1.0 / (b * b + l * l); }, -L, L, 48, 4000);
        tb::check("V1", "int dl/(b^2+l^2) over |l| <= 1e4 b equals 2 atan(L/b)/b", q, 2.0 * std::atan(L / b) / b, 1e-9);
    }

    tb::heading("T1 one collision kernel, three transport coefficients");
    {
        double worst = 0.0, worstLe = 0.0;
        for (double T : {100.0, 300.0, 1000.0})
            for (double P : {1e3, 1e5, 1e7})
                for (double b : {1.0e-10, 1.9e-10, 2.5e-10}) {
                    const auto r = ratios(T, P, b);
                    worst = std::fmax(worst, std::fmax(std::fabs(r.Pr / (2.0 / 3.0) - 1.0), std::fmax(std::fabs(r.Sc / (5.0 / 6.0) - 1.0), std::fabs(r.Le / 1.25 - 1.0))));
                    worstLe = std::fmax(worstLe, std::fabs(r.Le / (r.Sc / r.Pr) - 1.0));
                }
        tb::check("T1", "Pr = 2/3, Sc = 5/6, Le = 5/4 over 27 states (worst relative deviation)", worst, 0.0, 1e-13, false);
        tb::check("T1", "Le = Sc/Pr over 27 states (worst relative deviation)", worstLe, 0.0, 1e-13, false);
        const double b = 1.9e-10, P = 1e5;
        const auto s1 = TR::monatomic_state(100.0, P, MASS, b), s2 = TR::monatomic_state(1000.0, P, MASS, b);
        const double dT = std::log(10.0);
        tb::check("T1", "viscosity slope against T at fixed P", std::log(s2.dynamic_viscosity_Pa_s / s1.dynamic_viscosity_Pa_s) / dT, 0.5, 1e-12);
        tb::check("T1", "conductivity slope against T at fixed P", std::log(s2.thermal_conductivity_W_mK / s1.thermal_conductivity_W_mK) / dT, 0.5, 1e-12);
        tb::check("T1", "self-diffusivity slope against T at fixed P", std::log(s2.self_diffusivity_m2_s / s1.self_diffusivity_m2_s) / dT, 1.5, 1e-12);
        const auto p1 = TR::monatomic_state(300.0, 1e3, MASS, b), p2 = TR::monatomic_state(300.0, 1e7, MASS, b);
        tb::check("T1", "self-diffusivity slope against P", std::log(p2.self_diffusivity_m2_s / p1.self_diffusivity_m2_s) / std::log(1e4), -1.0, 1e-12);
        tb::note("300 K, 1e5 Pa, b = 1.9e-10 m: eta = %.4e Pa s ; kappa = %.4e W/(m K) ; D = %.4e m^2/s", TR::monatomic_state(300.0, 1e5, MASS, b).dynamic_viscosity_Pa_s, TR::monatomic_state(300.0, 1e5, MASS, b).thermal_conductivity_W_mK, TR::monatomic_state(300.0, 1e5, MASS, b).self_diffusivity_m2_s);
    }

    tb::heading("T2 freeze the kernel on one observable, predict the others");
    {
        const double T = 300.0, P = 1e5, b = 1.9e-10;
        const auto s = TR::monatomic_state(T, P, MASS, b);
        const double sigma = 0.3125 * std::sqrt(MASS * M::k_B * T / PI) / s.dynamic_viscosity_Pa_s;
        tb::check("T2", "collision measure recovered from the viscosity alone", sigma, s.collision_measure_m2, 1e-12);
        const double kappa = (75.0 / 64.0) * M::k_B * std::sqrt(M::k_B * T / (PI * MASS)) / sigma;
        const double D = (3.0 / 8.0) * std::sqrt(M::k_B * T / (PI * MASS)) / ((P / (M::k_B * T)) * sigma);
        tb::check("T2", "conductivity predicted from the recovered measure", kappa, s.thermal_conductivity_W_mK, 1e-12);
        tb::check("T2", "diffusivity predicted from the recovered measure", D, s.self_diffusivity_m2_s, 1e-12);
        const auto s1000 = TR::monatomic_state(1000.0, P, MASS, b);
        const double kappa1000 = s.thermal_conductivity_W_mK * std::sqrt(1000.0 / 300.0);
        tb::check("T2", "conductivity at 1000 K from the 300 K value by T^(1/2)", kappa1000, s1000.thermal_conductivity_W_mK, 1e-12);
    }

    tb::heading("T3 optical-hydrodynamic invariant");
    {
        double worst = 0.0;
        const double Qs[4] = {1e20, 1e24, 1e28, 1e32}, vs[3] = {10.0, 500.0, 1e4};
        int n = 0;
        for (double Q : Qs)
            for (double v : vs) {
                const double sext = 1e-20 * (1.0 + 0.3 * n), scoll = 4e-21 * (1.0 + 0.1 * n);
                const double rph = Q * sext / (4.0 * PI * v);
                const double dens = Q / (4.0 * PI * v * rph * rph);
                const double Kn = (1.0 / (dens * scoll)) / rph;
                worst = std::fmax(worst, std::fabs(Kn / (sext / scoll) - 1.0));
                ++n;
            }
        tb::check("T3", "Kn(r_photo) = sigma_ext/sigma_coll for 12 combinations (worst relative deviation)", worst, 0.0, 1e-12, false);
        const double Q = 1e28, v = 500.0, sext = 1e-20;
        const double rph = Q * sext / (4.0 * PI * v);
        tb::note("generic outflow: r_photo = %.4e m", rph);
        tb::check_true("T3", "r_photo lies in [1.5e4, 1.7e4] m", rph >= 1.5e4 && rph <= 1.7e4);
        const double b = 2.0e4, L = 1e4 * b;
        const double pref = Q * sext / (4.0 * PI * v);
        const double tan_num = pref * tb::integrate([&](double l) { return 1.0 / (b * b + l * l); }, -L, L, 48, 4000);
        tb::check("T3", "tangent column by numerical integration equals the finite-L closed form", tan_num, pref * 2.0 * std::atan(L / b) / b, 1e-9);
        const double radial = pref / b;
        tb::note("tangent / radial column = %.6f (pi = %.6f)", tan_num / radial, PI);
        tb::check("T3", "tangent column over radial column is within 2e-4 of pi", tan_num / radial, PI, 2e-4);
    }

    tb::heading("T4 rotation, heat and appearance");
    {
        const double alpha = 1.3e-6, omega = 2.0 * PI / 86400.0;
        const double delta = std::sqrt(2.0 * alpha / omega);
        auto Tfun = [&](double x, double t) { return std::exp(-x / delta) * std::cos(omega * t - x / delta); };
        double worst = 0.0;
        for (double x : {0.3 * delta, 1.0 * delta, 2.1 * delta})
            for (double t : {1000.0, 30000.0}) {
                const double ht = 1.0, hx = 1e-3 * delta;
                const double dTdt = (Tfun(x, t + ht) - Tfun(x, t - ht)) / (2.0 * ht);
                const double d2 = (Tfun(x + hx, t) - 2.0 * Tfun(x, t) + Tfun(x - hx, t)) / (hx * hx);
                worst = std::fmax(worst, std::fabs(dTdt - alpha * d2) / (omega * std::exp(-x / delta)));  // normaliser: amplitude of dT/dt at this depth
            }
        tb::note("penetration depth delta = %.6e m (alpha = %.2e m^2/s, period 1 day)", delta, alpha);
        tb::check("T4", "the damped travelling solution satisfies the heat equation (worst relative residual)", worst, 0.0, 1e-6, false);
        for (double wt : {0.1, 1.0, 10.0}) {
            const double tth = 1.0, w = wt / tth;
            // RK4 for dT/dt = (sin(w t) - T)/tth, run 40 time constants, fit steady amplitude and phase over the last period
            double T = 0.0, t = 0.0;
            const double dt = 2.0 * PI / w / 4000.0;
            auto f = [&](double tt, double TT) { return (std::sin(w * tt) - TT) / tth; };
            const int steps_settle = static_cast<int>(40.0 * tth / dt) + 1;
            for (int i = 0; i < steps_settle; ++i) {
                const double k1 = f(t, T), k2 = f(t + 0.5 * dt, T + 0.5 * dt * k1), k3 = f(t + 0.5 * dt, T + 0.5 * dt * k2), k4 = f(t + dt, T + dt * k3);
                T += dt * (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
                t += dt;
            }
            double sc = 0.0, ss = 0.0;
            const int nper = 4000;
            for (int i = 0; i < nper; ++i) {
                const double k1 = f(t, T), k2 = f(t + 0.5 * dt, T + 0.5 * dt * k1), k3 = f(t + 0.5 * dt, T + 0.5 * dt * k2), k4 = f(t + dt, T + dt * k3);
                T += dt * (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
                t += dt;
                sc += T * std::cos(w * t) * dt;
                ss += T * std::sin(w * t) * dt;
            }
            // T ~ G sin(w t - phi) = G (sin cos phi - cos sin phi): ss -> G cos(phi) * (period/2), sc -> -G sin(phi) * (period/2)
            const double half = PI / w;
            const double Gc = ss / half, Gs = -sc / half;
            const double G = std::hypot(Gc, Gs), phi = std::atan2(Gs, Gc);
            char lab[128];
            std::snprintf(lab, sizeof lab, "omega t_th = %g: gain [1 + (omega t)^2]^(-1/2)", wt);
            tb::check("T4", lab, G, 1.0 / std::sqrt(1.0 + wt * wt), 1e-6);
            std::snprintf(lab, sizeof lab, "omega t_th = %g: lag atan(omega t)", wt);
            tb::check("T4", lab, phi, std::atan(wt), 1e-6);
        }
        tb::check("T4", "at omega t_th = 1 the gain is 2^(-1/2)", 1.0 / std::sqrt(2.0), 0.7071067811865476, 1e-15);
        tb::check("T4", "at omega t_th = 1 the lag is pi/4", std::atan(1.0), PI / 4.0, 1e-15);
    }

    return tb::finish();
}
