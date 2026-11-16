// Chapter 40 — compact objects and singularity tests: worked-example instrument.
// Pre-registration: Textbook/validation/ch40_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>
#include <sdt/galactic.hpp>

#include "tb_common.hpp"

#include <cmath>

namespace {
constexpr double kPi = std::numbers::pi;
double F(double r) { return r + 2.0 * std::log(r - 1.0) - 1.0 / (r - 1.0); }   // Om = 1, c = 1: c t = F(r_start) - F(r)
double G(double d) { return std::log(d) + d; }
}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    namespace DC = sdt::laws::depth_closure;
    tb::validate_helpers();
    const double c = M::c;

    tb::heading("V1 antiderivatives");
    {
        double w = 0.0;
        for (double r : {1.01, 1.5, 3.0, 10.0}) {
            const double h = 1e-4 * (r - 1.0);  // step scaled with the distance to the singularity
            const double d = (F(r + h) - F(r - h)) / (2.0 * h);
            w = std::fmax(w, std::fabs(d / (r * r / ((r - 1.0) * (r - 1.0))) - 1.0));
        }
        tb::check("V1", "d/dr [r + 2 ln(r-1) - 1/(r-1)] = r^2/(r-1)^2, worst relative", w, 0.0, 1e-7, false);
        double w2 = 0.0;
        for (double dl : {0.01, 0.1, 1.0}) {
            const double h = 1e-6 * dl;
            w2 = std::fmax(w2, std::fabs((G(dl + h) - G(dl - h)) / (2.0 * h) / ((1.0 + dl) / dl) - 1.0));
        }
        tb::check("V1", "d/d delta [ln delta + delta] = (1 + delta)/delta, worst relative", w2, 0.0, 1e-7, false);
    }

    tb::heading("T1 the circular branch reaches c at r = Om");
    {
        const double Om = 1476.625;
        double w = std::fabs(DC::v_bound(Om, Om) / c - 1.0);
        w = std::fmax(w, std::fabs(DC::v_bound(Om, Om / 4.0) / c - 2.0));
        bool exceeds = true;
        for (double f : {0.9, 0.5, 0.1, 0.01}) exceeds = exceeds && DC::v_bound(Om, f * Om) > c;
        double w2 = 0.0;
        for (double f : {0.9, 0.5, 2.0, 10.0}) w2 = std::fmax(w2, std::fabs(DC::v_bound(Om, f * Om) / c - std::sqrt(1.0 / f)));
        tb::check("T1", "v/c = 1 at r = Om and 2 at r = Om/4, worst deviation", w, 0.0, 1e-14, false);
        tb::check_true("T1", "v/c exceeds 1 for r/Om = 0.9, 0.5, 0.1, 0.01", exceeds);
        tb::check("T1", "v_bound equals c sqrt(Om/r), worst relative", w2, 0.0, 1e-14, false);
    }

    tb::heading("T2 uniform-density interior is regular");
    {
        const double R = 1.0, om2 = 1.0;  // omega^2 = c^2 varpi / R^3 = 1
        double x = R, v = 0.0;
        const double T = 2.0 * kPi, dt = T / 20000.0;
        int crossings = 0;
        double t = 0.0, last_cross = -1.0, period_est = 0.0, vcentre = 0.0;
        auto acc = [&](double X) { return -om2 * X; };
        for (long i = 0; i < 3 * 20000; ++i) {
            const double k1x = v, k1v = acc(x);
            const double k2x = v + 0.5 * dt * k1v, k2v = acc(x + 0.5 * dt * k1x);
            const double k3x = v + 0.5 * dt * k2v, k3v = acc(x + 0.5 * dt * k2x);
            const double k4x = v + dt * k3v, k4v = acc(x + dt * k3x);
            const double xn = x + dt / 6.0 * (k1x + 2 * k2x + 2 * k3x + k4x), vn = v + dt / 6.0 * (k1v + 2 * k2v + 2 * k3v + k4v);
            if (x > 0.0 && xn <= 0.0) {
                const double tc = t + dt * x / (x - xn);
                ++crossings;
                if (last_cross >= 0.0) period_est = tc - last_cross;
                last_cross = tc;
                vcentre = std::fabs(v + (vn - v) * x / (x - xn));
            }
            x = xn; v = vn; t += dt;
        }
        tb::check("T2", "oscillation period through the centre equals 2 pi/omega", period_est, T, 1e-9);
        tb::check("T2", "speed at the centre equals omega R", vcentre, 1.0, 1e-9);
        const double r = 1e-2;
        tb::check("T2", "uniform sphere acceleration at r = 0.01 R over the point-source value = 1e-6", (om2 * r) / (1.0 / (r * r)), 1e-6, 1e-12);
        tb::note("crossings of the centre in 3 periods: %d ; the acceleration is finite (zero) at the centre, while the point-source value diverges as 1/r^2", crossings);
    }

    tb::heading("T3 coordinate arrest and local duration");
    {
        // delta' = -(delta/(1+delta))^2  (c = Om = 1)
        auto rhs = [](double d) { const double q = d / (1.0 + d); return -q * q; };
        double d = 0.5, t = 0.0;
        const double d0 = 0.5, dstop = 1e-3;
        // adaptive step: h = 1e-3 * (1+d)^2 / d^... choose small relative step
        double tau = 0.0;  // local duration by integrating C dt, C = delta/(1+delta)
        double t_stop = -1.0, tau_stop = -1.0;
        double late[3] = {0, 0, 0};
        const double marks[3] = {1e2, 1e3, 1e4};
        int mi = 0;
        while (t < 1.0e4 + 1.0) {
            const double h = std::fmin(1e-2 * d * d / 1.0 + 1e-6, 0.05) * (d < 0.05 ? 1.0 : 5.0);
            const double k1 = rhs(d), k2 = rhs(d + 0.5 * h * k1), k3 = rhs(d + 0.5 * h * k2), k4 = rhs(d + h * k3);
            const double dn = d + h / 6.0 * (k1 + 2 * k2 + 2 * k3 + k4);
            const double C = d / (1.0 + d), Cn = dn / (1.0 + dn);
            const double dtau = 0.5 * h * (C + Cn);
            if (t_stop < 0.0 && dn <= dstop) {
                const double f = (d - dstop) / (d - dn);
                t_stop = t + f * h;
                tau_stop = tau + f * dtau;
            }
            tau += dtau;
            t += h;
            d = dn;
            while (mi < 3 && t >= marks[mi]) { late[mi] = d * marks[mi]; ++mi; }
        }
        const double t_exact = F(1.0 + d0) - F(1.0 + dstop);
        tb::check("T3", "time to reach delta = 1e-3 equals F(1 + d0) - F(1 + 1e-3)", t_stop, t_exact, 1e-6);
        tb::note("delta c t/Om^2 at c t/Om = 1e2, 1e3, 1e4: %.5f %.5f %.5f", late[0], late[1], late[2]);
        tb::check_true("T3", "delta c t/Om^2 within 5e-3 of 1 at c t/Om = 1e4", std::fabs(late[2] - 1.0) <= 5e-3);
        const double tau_exact = G(d0) - G(dstop);
        tb::check("T3", "local duration to delta = 1e-3 equals G(d0) - G(1e-3)", tau_stop, tau_exact, 1e-6);
        const double dec = G(1e-4) - G(1e-5);
        tb::check("T3", "increment of G per decade of delta at small delta = ln 10", dec, std::log(10.0), 1e-2);
        tb::note("local duration to delta = 1e-3: %.6f Om/c ; coordinate time %.4f Om/c ; the coordinate time to delta = 1e-6 would be %.4e Om/c", tau_stop, t_stop, F(1.5) - F(1.0 + 1e-6));
    }

    tb::heading("T4 angular-impulse ledger scale (printed)");
    {
        const double Om_sun = sdt::laws::bridge::koppa_Sun, Om_mw = sdt::galactic::milky_way::koppa_mw_m;
        tb::note("h = c Om at r = Om: Sun %.4e m^2/s ; Milky Way baryonic total %.4e m^2/s (specific angular momentum the continuation would have to transfer)", c * Om_sun, c * Om_mw);
    }

    return tb::finish();
}
