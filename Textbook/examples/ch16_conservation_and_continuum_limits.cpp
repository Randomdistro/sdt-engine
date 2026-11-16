// Chapter 16 — conservation and continuum limits: worked-example instrument.
// Pre-registration: Textbook/validation/ch16_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch16_conservation_and_continuum_limits
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdint>
#include <numeric>
#include <vector>

namespace {

using cd = std::complex<double>;
constexpr double kPi = std::numbers::pi;

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

// Continuum telegraph eigenvalues and the solution factor for j(0)=0.
void mu_pm(double gamma, double k, cd& mp, cd& mm) {
    const cd r = std::sqrt(cd(gamma * gamma - k * k, 0.0));
    mp = -gamma + r;
    mm = -gamma - r;
}

cd F_factor(double gamma, double k, double t) {
    cd mp, mm;
    mu_pm(gamma, k, mp, mm);
    if (std::abs(mp - mm) < 1e-12) {  // critical damping
        return std::exp(mp * t) * (1.0 - mp * t);
    }
    return (mp * std::exp(mm * t) - mm * std::exp(mp * t)) / (mp - mm);
}

// Chain eigenvalue lambda_+ (principal root) for reversal fraction s and wavenumber kappa.
cd lambda_plus(double s, double kappa) {
    const double a = (1.0 - s) * std::cos(kappa);
    return a + std::sqrt(cd(a * a - (1.0 - 2.0 * s), 0.0));
}

// One chain count on a periodic ring.
void chain_step(std::vector<double>& R, std::vector<double>& L, double s) {
    const int n = static_cast<int>(R.size());
    std::vector<double> R2(n), L2(n);
    for (int i = 0; i < n; ++i) {
        const int ip = (i + 1) % n, im = (i + n - 1) % n;
        (void)im;
        R2[ip] = (1.0 - s) * R[i] + s * L[i];
        L2[im] = (1.0 - s) * L[i] + s * R[i];
    }
    R.swap(R2);
    L.swap(L2);
}

double sum(const std::vector<double>& v) { return std::accumulate(v.begin(), v.end(), 0.0); }

// Flux-form and expanded schemes for u_t = (D u_x)_x on a unit ring.
double Dfun(double x) { return 1.0 + 0.5 * std::sin(2.0 * kPi * x); }
double Dprime(double x) { return kPi * std::cos(2.0 * kPi * x); }

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    tb::validate_helpers();

    tb::heading("V1 conservative scheme on a single Fourier mode (constant D)");
    {
        const int n = 64;
        const double h = 1.0 / n, dt = 0.2 * h * h;
        std::vector<double> u(n), v(n);
        for (int i = 0; i < n; ++i) u[i] = std::cos(2.0 * kPi * i * h);
        for (int m = 0; m < 50; ++m) {
            for (int i = 0; i < n; ++i) v[i] = u[i] + dt / (h * h) * (u[(i + 1) % n] - 2.0 * u[i] + u[(i + n - 1) % n]);
            u.swap(v);
        }
        const double fac = std::pow(1.0 - 4.0 * (dt / (h * h)) * std::pow(std::sin(kPi * h), 2), 50);
        tb::check("V1", "amplitude after 50 steps equals the exact discrete factor", u[0], fac, 1e-10);
    }

    tb::heading("V2 continuum solution factor on known limits");
    {
        double worst = 0.0;
        worst = std::fmax(worst, std::abs(F_factor(1.0, 0.7, 0.0) - 1.0));
        worst = std::fmax(worst, std::abs(F_factor(1e-14, 1.3, 0.7) - std::cos(1.3 * 0.7)));
        worst = std::fmax(worst, std::abs(F_factor(1.0, 0.0, 2.0) - 1.0));
        tb::check("V2", "F(k,t): t=0, gamma->0 gives cos kt, k=0 gives 1; worst deviation", worst, 0.0, 1e-14, false);
    }

    tb::heading("T1 exact conservation on a ring (content, and P = (1-2s)^m P0)");
    {
        for (double s : {0.1, 0.3}) {
            const int n = 200;
            Rng g{20261109};
            std::vector<double> R(n), L(n);
            for (int i = 0; i < n; ++i) { R[i] = g.next(); L[i] = g.next(); }
            const double U0 = sum(R) + sum(L);
            const double P0 = sum(R) - sum(L);
            double worst_u = 0.0, worst_p = 0.0;
            for (int m = 1; m <= 200; ++m) {
                chain_step(R, L, s);
                worst_u = std::fmax(worst_u, std::fabs(sum(R) + sum(L) - U0) / U0);
                worst_p = std::fmax(worst_p, std::fabs((sum(R) - sum(L)) - std::pow(1.0 - 2.0 * s, m) * P0) / std::fabs(P0));
            }
            char label[128];
            std::snprintf(label, sizeof label, "s=%.1f content relative change, worst over 200 counts", s);
            tb::check("T1", label, worst_u, 0.0, 1e-13, false);
            std::snprintf(label, sizeof label, "s=%.1f momentum content vs (1-2s)^m P0, relative to |P0|", s);
            tb::check("T1", label, worst_p, 0.0, 1e-12, false);
            tb::note("s = %.1f : P0 = %.6f, P(200) = %.3e", s, P0, sum(R) - sum(L));
        }
    }

    tb::heading("T2 scaling limit of the dispersion relation (gamma = 1)");
    {
        const double eps[4] = {0.1, 0.05, 0.025, 0.0125};
        for (double k : {0.5, 2.0}) {
            cd mp, mm;
            mu_pm(1.0, k, mp, mm);
            double e[4];
            for (int q = 0; q < 4; ++q) {
                const cd lam = lambda_plus(1.0 * eps[q], k * eps[q]);
                e[q] = std::abs(std::log(lam) / eps[q] - mp);
            }
            double ord[3];
            bool in = true, shrinks = true;
            for (int q = 0; q < 3; ++q) {
                ord[q] = std::log2(e[q] / e[q + 1]);
                in = in && ord[q] > 0.8 && ord[q] < 1.2;
                shrinks = shrinks && e[q + 1] < e[q];
            }
            tb::note("k = %.1f : mu_+ = (%.6f, %.6f) ; errors %.3e %.3e %.3e %.3e ; orders %.3f %.3f %.3f", k, mp.real(), mp.imag(), e[0], e[1], e[2], e[3], ord[0], ord[1], ord[2]);
            char label[128];
            std::snprintf(label, sizeof label, "k=%.1f: error shrinks at each halving of eps", k);
            tb::check_true("T2", label, shrinks);
            std::snprintf(label, sizeof label, "k=%.1f: observed orders in [0.8, 1.2]", k);
            tb::check_true("T2", label, in);
        }
        // diffusion coefficient of the chain and of its limit
        const double s = 0.05;
        tb::note("chain D = (1-s)/(2s) at s=%.2f : %.6f (hop units); limit 1/(2 gamma) = 0.5 in scaled units", s, (1.0 - s) / (2.0 * s));
    }

    tb::heading("T3 real-space limit: Gaussian on a ring of length 40, scaled count t = 2");
    {
        const double Lr = 40.0, gamma = 1.0, t = 2.0, x0 = 20.0;
        const int Nmode = 120;
        const double epsv[3] = {0.1, 0.05, 0.025};
        double err[3];
        for (int q = 0; q < 3; ++q) {
            const double eps = epsv[q];
            const int n = static_cast<int>(std::lround(Lr / eps)), steps = static_cast<int>(std::lround(t / eps));
            std::vector<double> R(n), L(n);
            for (int i = 0; i < n; ++i) {
                const double x = i * eps;
                R[i] = L[i] = 0.5 * std::exp(-0.5 * (x - x0) * (x - x0));
            }
            for (int m = 0; m < steps; ++m) chain_step(R, L, gamma * eps);
            double num = 0.0, den = 0.0;
            for (int i = 0; i < n; ++i) {
                const double x = i * eps;
                cd u = 0.0;
                for (int j = -Nmode; j <= Nmode; ++j) {
                    const double k = 2.0 * kPi * j / Lr;
                    const cd cj = std::sqrt(2.0 * kPi) / Lr * std::exp(-0.5 * k * k) * std::exp(cd(0.0, -k * x0));
                    u += cj * F_factor(gamma, k, t) * std::exp(cd(0.0, k * x));
                }
                const double diff = R[i] + L[i] - u.real();
                num += diff * diff;
                den += u.real() * u.real();
            }
            err[q] = std::sqrt(num / den);
        }
        const double o1 = std::log2(err[0] / err[1]), o2 = std::log2(err[1] / err[2]);
        tb::note("relative L2 error, eps = 0.1/0.05/0.025: %.3e %.3e %.3e ; observed orders %.3f %.3f", err[0], err[1], err[2], o1, o2);
        tb::check_true("T3", "error decreases at each halving", err[1] < err[0] && err[2] < err[1]);
        tb::check_true("T3", "observed orders in [0.8, 1.3]", o1 > 0.8 && o1 < 1.3 && o2 > 0.8 && o2 < 1.3);
    }

    tb::heading("T4 numerical conservation: flux-form and expanded schemes");
    {
        const int ns[3] = {64, 128, 256};
        double drift_nc[3];
        double worst_c = 0.0;
        for (int q = 0; q < 3; ++q) {
            const int n = ns[q];
            const double h = 1.0 / n, dt = 0.2 * h * h / 1.5;
            const int steps = static_cast<int>(std::lround(0.05 / dt));
            std::vector<double> uc(n), un(n), v(n);
            for (int i = 0; i < n; ++i) uc[i] = un[i] = std::exp(-0.5 * std::pow((i * h - 0.3) / 0.1, 2));
            const double S0 = sum(uc);
            for (int m = 0; m < steps; ++m) {
                for (int i = 0; i < n; ++i) {
                    const int ip = (i + 1) % n, im = (i + n - 1) % n;
                    const double Dp = Dfun((i + 0.5) * h), Dm = Dfun((i - 0.5) * h);
                    v[i] = uc[i] + dt / (h * h) * (Dp * (uc[ip] - uc[i]) - Dm * (uc[i] - uc[im]));
                }
                uc.swap(v);
                for (int i = 0; i < n; ++i) {
                    const int ip = (i + 1) % n, im = (i + n - 1) % n;
                    v[i] = un[i] + dt * (Dfun(i * h) * (un[ip] - 2.0 * un[i] + un[im]) / (h * h) + Dprime(i * h) * (un[ip] - un[im]) / (2.0 * h));
                }
                un.swap(v);
            }
            worst_c = std::fmax(worst_c, std::fabs(sum(uc) - S0) / S0);
            drift_nc[q] = std::fabs(sum(un) - S0) / S0;
            tb::note("n = %3d : steps %d ; flux-form drift %.3e ; expanded-form drift %.3e", n, steps, std::fabs(sum(uc) - S0) / S0, drift_nc[q]);
        }
        tb::check("T4a", "flux-form relative change of the sum, worst over n", worst_c, 0.0, 1e-13, false);
        bool big = true;
        for (double d : drift_nc) big = big && d > 1e-8;
        const double o1 = std::log2(drift_nc[0] / drift_nc[1]), o2 = std::log2(drift_nc[1] / drift_nc[2]);
        tb::note("expanded-form drift orders: %.3f %.3f", o1, o2);
        tb::check_true("T4b", "expanded-form drift exceeds 1e-8 at every n", big);
        tb::check_true("T4b", "expanded-form drift shrinks with order in [1.7, 2.3]", o1 > 1.7 && o1 < 2.3 && o2 > 1.7 && o2 < 2.3);
    }

    tb::heading("T5 engine monatomic transport kernel (law_IV::transport)");
    {
        namespace Tr = sdt::laws::law_IV::transport;
        const double kB = M::k_B;
        const double T = 300.0, P = 101325.0, m = 6.6e-26, b = 1.8e-10;
        auto st = [&](double T_, double P_, double m_, double b_) { return Tr::monatomic_state(T_, P_, m_, b_); };
        const auto s0 = st(T, P, m, b);
        const double n = P / (kB * T), rho = n * m, cp = 2.5 * kB / m;
        tb::note("test point: eta = %.6e Pa s ; kappa = %.6e W/(m K) ; D = %.6e m^2/s ; collision measure %.6e m^2", s0.dynamic_viscosity_Pa_s, s0.thermal_conductivity_W_mK, s0.self_diffusivity_m2_s, s0.collision_measure_m2);
        const double Pr = cp * s0.dynamic_viscosity_Pa_s / s0.thermal_conductivity_W_mK;
        const double Sc = s0.dynamic_viscosity_Pa_s / (rho * s0.self_diffusivity_m2_s);
        tb::check("T5a", "Prandtl number = 2/3", Pr, 2.0 / 3.0, 1e-13);
        tb::check("T5a", "Schmidt number = 5/6", Sc, 5.0 / 6.0, 1e-13);
        tb::check("T5a", "Lewis number Sc/Pr = 5/4", Sc / Pr, 1.25, 1e-13);
        const auto sT = st(4.0 * T, P, m, b), sP = st(T, 2.0 * P, m, b), sb = st(T, P, m, 2.0 * b), sm = st(T, P, 4.0 * m, b);
        tb::check("T5b", "T x4: eta x2", sT.dynamic_viscosity_Pa_s / s0.dynamic_viscosity_Pa_s, 2.0, 1e-13);
        tb::check("T5b", "T x4: kappa x2", sT.thermal_conductivity_W_mK / s0.thermal_conductivity_W_mK, 2.0, 1e-13);
        tb::check("T5b", "T x4: D x8", sT.self_diffusivity_m2_s / s0.self_diffusivity_m2_s, 8.0, 1e-13);
        tb::check("T5b", "P x2: eta unchanged", sP.dynamic_viscosity_Pa_s / s0.dynamic_viscosity_Pa_s, 1.0, 1e-13);
        tb::check("T5b", "P x2: kappa unchanged", sP.thermal_conductivity_W_mK / s0.thermal_conductivity_W_mK, 1.0, 1e-13);
        tb::check("T5b", "P x2: D halves", sP.self_diffusivity_m2_s / s0.self_diffusivity_m2_s, 0.5, 1e-13);
        tb::check("T5b", "b x2: eta /4", sb.dynamic_viscosity_Pa_s / s0.dynamic_viscosity_Pa_s, 0.25, 1e-13);
        tb::check("T5b", "b x2: kappa /4", sb.thermal_conductivity_W_mK / s0.thermal_conductivity_W_mK, 0.25, 1e-13);
        tb::check("T5b", "b x2: D /4", sb.self_diffusivity_m2_s / s0.self_diffusivity_m2_s, 0.25, 1e-13);
        tb::check("T5b", "m x4: eta x2", sm.dynamic_viscosity_Pa_s / s0.dynamic_viscosity_Pa_s, 2.0, 1e-13);
        tb::check("T5b", "m x4: kappa x1/2", sm.thermal_conductivity_W_mK / s0.thermal_conductivity_W_mK, 0.5, 1e-13);
        tb::check("T5b", "m x4: D x1/2", sm.self_diffusivity_m2_s / s0.self_diffusivity_m2_s, 0.5, 1e-13);
        const double d = 2.0 * b;
        const double eta_hs = (5.0 / 16.0) * std::sqrt(m * kB * T / kPi) / (d * d);
        const double kap_hs = (75.0 / 64.0) * kB * std::sqrt(kB * T / (kPi * m)) / (d * d);
        const double D_hs = (3.0 / 8.0) * std::sqrt(kB * T / (kPi * m)) / (n * d * d);
        tb::check("T5c", "eta / eta_HS = 7/6", s0.dynamic_viscosity_Pa_s / eta_hs, 7.0 / 6.0, 1e-13);
        tb::check("T5c", "kappa / kappa_HS = 7/6", s0.thermal_conductivity_W_mK / kap_hs, 7.0 / 6.0, 1e-13);
        tb::check("T5c", "D / D_HS = 7/6", s0.self_diffusivity_m2_s / D_hs, 7.0 / 6.0, 1e-13);
    }

    return tb::finish();
}
