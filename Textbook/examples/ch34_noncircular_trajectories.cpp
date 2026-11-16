// Chapter 34 — noncircular trajectories: worked-example instrument.
// Pre-registration: Textbook/validation/ch34_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <vector>

namespace {

constexpr double kPi = std::numbers::pi;

struct S {
    double x, y, vx, vy;
};

S deriv(const S& s, double kappa) {
    const double r2 = s.x * s.x + s.y * s.y, r = std::sqrt(r2);
    const double k = -(1.0 / (r2 * r) + kappa / (r2 * r2));  // a = -(1/r^2 + kappa/r^3) rhat ; components a_x = k x with k = -(1/r^3 + kappa/r^4)
    return {s.vx, s.vy, k * s.x, k * s.y};
}

S step(const S& s, double h, double kappa) {
    auto add = [](const S& a, const S& d, double f) { return S{a.x + f * d.x, a.y + f * d.y, a.vx + f * d.vx, a.vy + f * d.vy}; };
    const S k1 = deriv(s, kappa), k2 = deriv(add(s, k1, 0.5 * h), kappa), k3 = deriv(add(s, k2, 0.5 * h), kappa), k4 = deriv(add(s, k3, h), kappa);
    return {s.x + h / 6.0 * (k1.x + 2 * k2.x + 2 * k3.x + k4.x), s.y + h / 6.0 * (k1.y + 2 * k2.y + 2 * k3.y + k4.y), s.vx + h / 6.0 * (k1.vx + 2 * k2.vx + 2 * k3.vx + k4.vx), s.vy + h / 6.0 * (k1.vy + 2 * k2.vy + 2 * k3.vy + k4.vy)};
}

double rad(const S& s) { return std::hypot(s.x, s.y); }
double rdot(const S& s) { return (s.x * s.vx + s.y * s.vy) / rad(s); }
double Lz(const S& s) { return s.x * s.vy - s.y * s.vx; }
double energy(const S& s) { return 0.5 * (s.vx * s.vx + s.vy * s.vy) - 1.0 / rad(s); }

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 elements from apoapsis data");
    {
        const double ra = 1.51, va = std::sqrt(2.0 / ra - 1.0);
        const double eps = 0.5 * va * va - 1.0 / ra, L = ra * va;
        tb::check("V1", "energy = -1/2 (a = 1)", eps, -0.5, 1e-14);
        tb::check("V1", "e = sqrt(1 + 2 eps L^2) = 0.51", std::sqrt(1.0 + 2.0 * eps * L * L), 0.51, 1e-14);
    }

    tb::heading("T1 eccentric orbits: turning points, period, conservation, radial equation");
    for (double e : {0.3, 0.6, 0.9}) {
        const double ra = 1.0 + e, va = std::sqrt(2.0 / ra - 1.0);
        S s{ra, 0.0, 0.0, va};
        const double T = 2.0 * kPi;
        const int N = 200000, steps = 3 * N;
        const double h = T / N, E0 = energy(s), L0 = Lz(s);
        double rmin = 1e300, rmax = 0.0, dE = 0.0, dL = 0.0, worst_rad = 0.0;
        std::vector<double> apo;
        double prev_rd = 0.0, tprev = 0.0;
        double r_m1 = rad(s), r_0 = r_m1, r_p1 = 0.0;
        double rprev2 = rad(s), rprev = rad(s);
        int sample_every = steps / 1000;
        for (int i = 1; i <= steps; ++i) {
            const S n = step(s, h, 0.0);
            const double rd_prev = rdot(s), rd_new = rdot(n);
            if (i > 1 && rd_prev > 0.0 && rd_new <= 0.0) apo.push_back((i - 1 + rd_prev / (rd_prev - rd_new)) * h);
            s = n;
            const double r = rad(s);
            // parabolic extreme detection
            if (i >= 2) {
                if (rprev < rprev2 && rprev < r) {
                    const double den = rprev2 - 2.0 * rprev + r;
                    rmin = std::fmin(rmin, rprev - 0.125 * (r - rprev2) * (r - rprev2) / den);
                }
                if (rprev > rprev2 && rprev > r) {
                    const double den = rprev2 - 2.0 * rprev + r;
                    rmax = std::fmax(rmax, rprev - 0.125 * (r - rprev2) * (r - rprev2) / den);
                }
            }
            rprev2 = rprev;
            rprev = r;
            dE = std::fmax(dE, std::fabs(energy(s) / E0 - 1.0));
            dL = std::fmax(dL, std::fabs(Lz(s) / L0 - 1.0));
            if (i % sample_every == 0) {
                const double rd = rdot(s);
                worst_rad = std::fmax(worst_rad, std::fabs(rd * rd - (2.0 * (E0 + 1.0 / r) - L0 * L0 / (r * r))));
            }
            (void)prev_rd; (void)tprev; (void)r_m1; (void)r_0; (void)r_p1;
        }
        char lab[128];
        std::snprintf(lab, sizeof lab, "e=%.1f: r_min = 1 - e", e);
        tb::check("T1", lab, rmin, 1.0 - e, 1e-8);
        std::snprintf(lab, sizeof lab, "e=%.1f: r_max = 1 + e", e);
        tb::check("T1", lab, rmax, 1.0 + e, 1e-8);
        double Tm = 0.0;
        if (apo.size() >= 2) Tm = (apo.back() - apo.front()) / double(apo.size() - 1);
        std::snprintf(lab, sizeof lab, "e=%.1f: period between apoapsis passages = 2 pi (%zu passages)", e, apo.size());
        tb::check("T1", lab, Tm, T, 1e-8);
        std::snprintf(lab, sizeof lab, "e=%.1f: energy drift %.1e, L drift %.1e (limit 1e-9)", e, dE, dL);
        tb::check_true("T1", lab, dE <= 1e-9 && dL <= 1e-9);
        std::snprintf(lab, sizeof lab, "e=%.1f: radial equation residual %.1e (limit 1e-7)", e, worst_rad);
        tb::check_true("T1", lab, worst_rad <= 1e-7);
    }

    tb::heading("T2 apsidal motion");
    {
        const double ra = 1.3, va = std::sqrt(2.0 / ra - 1.0), L = ra * va;
        for (double kappa : {0.0, 0.002}) {
            S s{ra, 0.0, 0.0, va};
            const int N = 100000;
            const double h = 2.0 * kPi / N;
            double phi_prev = 0.0, phi_unwrapped = 0.0, phi_start = 0.0;
            double phi_apo = -1.0;
            bool found = false;
            for (int i = 1; i <= 3 * N && !found; ++i) {
                const double rd_prev = rdot(s);
                const S n = step(s, h, kappa);
                const double rd_new = rdot(n);
                const double ph_new = std::atan2(n.y, n.x), ph_old = std::atan2(s.y, s.x);
                double dphi = ph_new - ph_old;
                if (dphi < -kPi) dphi += 2.0 * kPi;
                if (dphi > kPi) dphi -= 2.0 * kPi;
                const double up_old = phi_unwrapped;
                phi_unwrapped += dphi;
                if (i > 100 && rd_prev > 0.0 && rd_new <= 0.0) {
                    const double f = rd_prev / (rd_prev - rd_new);
                    phi_apo = up_old + f * dphi;
                    found = true;
                }
                s = n;
                (void)phi_prev; (void)phi_start;
            }
            const double shift = phi_apo - 2.0 * kPi;
            if (kappa == 0.0) {
                tb::note("kappa = 0: advance per orbit = %.3e rad", shift);
                tb::check("T2", "kappa = 0: advance per orbit is zero", shift, 0.0, 1e-7, false);
            } else {
                const double want = 2.0 * kPi * (1.0 / std::sqrt(1.0 - kappa / (L * L)) - 1.0);
                tb::note("kappa = %.3f: L^2 = %.6f ; advance %.6e rad ; exact form %.6e rad ; relative difference %.2e", kappa, L * L, shift, want, shift / want - 1.0);
                tb::check("T2", "kappa = 0.002: advance equals 2 pi (1/sqrt(1 - kappa/L^2) - 1)", shift, want, 2e-4);
            }
        }
    }

    tb::heading("T3 open trajectory: periapsis and deflection");
    {
        const double r0 = std::sqrt(2000.0 * 2000.0 + 1.0);
        S s{-2000.0, 1.0, 1.0, 0.0};
        const double eps = 0.5 - 1.0 / r0, L = std::fabs(Lz(s));
        const double e = std::sqrt(1.0 + 2.0 * eps * L * L), p = L * L;
        const double h = 2e-3;
        double rmin = 1e300, rprev2 = rad(s), rprev = rad(s);
        bool left = false;
        long it = 0;
        while (it < 5000000) {
            s = step(s, h, 0.0);
            const double r = rad(s);
            if (rprev < rprev2 && rprev < r) {
                const double den = rprev2 - 2.0 * rprev + r;
                rmin = rprev - 0.125 * (r - rprev2) * (r - rprev2) / den;
            }
            rprev2 = rprev;
            rprev = r;
            ++it;
            if (r < 1500.0) left = true;
            if (left && r >= 2000.0) break;
        }
        const double vin = std::atan2(0.0, 1.0), vout = std::atan2(s.vy, s.vx);
        const double defl = std::fabs(vout - vin);
        const double want = 2.0 * std::asin(1.0 / e);
        tb::note("e = %.8f ; p = %.6f ; periapsis %.10f (p/(1+e) = %.10f) ; deflection %.8f rad (2 arcsin(1/e) = %.8f) ; steps %ld", e, p, rmin, p / (1.0 + e), defl, want, it);
        tb::check("T3", "periapsis radius equals p/(1+e)", rmin, p / (1.0 + e), 1e-8);
        tb::check("T3", "deflection equals 2 arcsin(1/e)", defl, want, 1e-5, false);
    }

    return tb::finish();
}
