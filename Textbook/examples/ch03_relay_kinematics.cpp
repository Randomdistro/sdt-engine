// Chapter 3 — relay kinematics: worked-example instruments.
// Pre-registration: Textbook/validation/ch03_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch03_relay_kinematics
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <climits>
#include <cmath>
#include <cstdlib>

namespace {

// Exact rational arithmetic on 64-bit integers; `ok` turns false on overflow.
struct Fr {
    long long n, d;
};
long long gcdll(long long a, long long b) {
    while (b) {
        const long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}
Fr fr_norm(Fr f) {
    if (f.d < 0) {
        f.n = -f.n;
        f.d = -f.d;
    }
    const long long g = gcdll(std::llabs(f.n), f.d);
    if (g > 1) {
        f.n /= g;
        f.d /= g;
    }
    return f;
}
bool mul_ok(long long a, long long b) { return a == 0 || b == 0 || std::llabs(a) <= LLONG_MAX / std::llabs(b); }
Fr fr_mul(Fr a, Fr b, bool& ok) {
    ok = ok && mul_ok(a.n, b.n) && mul_ok(a.d, b.d);
    return ok ? fr_norm({a.n * b.n, a.d * b.d}) : Fr{0, 1};
}
Fr fr_add(Fr a, Fr b, bool& ok) {
    ok = ok && mul_ok(a.n, b.d) && mul_ok(b.n, a.d) && mul_ok(a.d, b.d);
    return ok ? fr_norm({a.n * b.d + b.n * a.d, a.d * b.d}) : Fr{0, 1};
}
Fr fr_neg(Fr a) { return {-a.n, a.d}; }
Fr fr_inv(Fr a) { return fr_norm({a.d, a.n}); }
bool fr_eq(Fr a, Fr b) {
    a = fr_norm(a);
    b = fr_norm(b);
    return a.n == b.n && a.d == b.d;
}

}  // namespace

int main() {
    namespace L = sdt::laws;
    namespace M = sdt::laws::measured;
    namespace DC = sdt::laws::depth_closure;
    constexpr double kPi = std::numbers::pi;
    tb::validate_helpers();

    tb::heading("V1 quadrature on the straight-ray integral (substituted variable, as used in T3)");
    for (double ratio : {3.0, 300.0, 3.0e4}) {
        const double b = 1.0, umax = std::asinh(ratio);
        // l = b sinh u: int dl (l^2+b^2)^(-3/2) = int b^-2 sech^2 u du = 2 L / (b^2 sqrt(L^2 + b^2))
        const double q = tb::integrate([&](double u) { return 1.0 / (b * b * std::cosh(u) * std::cosh(u)); }, -umax,
                                       umax, 32, 4);
        const double exact = 2.0 * ratio * b / (b * b * std::sqrt(ratio * ratio * b * b + b * b));
        tb::check("V1", ("int dl (l^2+b^2)^(-3/2) = 2L/(b^2 sqrt(L^2+b^2)), L/b = " + std::to_string(ratio)).c_str(), q,
                  exact, 1e-12);
    }
    tb::heading("V2 series of the relay-speed deficit");
    {
        const double z = 1e-3;
        const double direct = (1.0 / ((1.0 - z) * (1.0 - z)) - 1.0) / (2.0 * z);
        const double series = 1.0 + 1.5 * z + 2.0 * z * z + 2.5 * z * z * z;
        tb::check("V2", "[(1-z)^-2 - 1]/(2z) = 1 + 3z/2 + 2z^2 + 5z^3/2 + ... at z = 1e-3", direct, series, 1e-11);
    }

    tb::heading("T1 factorisation of the far-frame relay speed");
    {
        double worst_f = 0.0, worst_i = 0.0;
        for (int i = 0; i <= 9; ++i) {
            const double z = 0.1 * i;
            const double cf = DC::c_far(M::c, z);
            const double fac = M::c * DC::closure_local(1.0, z) * DC::clock_rate(z);
            worst_f = std::fmax(worst_f, std::fabs(cf - fac) / M::c);
            if (z > 0.0) worst_i = std::fmax(worst_i, std::fabs(DC::depth_from_c_far(cf, M::c) - z) / z);
        }
        tb::check("T1", "c_far = c x closure factor x oscillator-rate factor (worst relative, z = 0..0.9)", worst_f, 0.0,
                  1e-15, false);
        tb::check("T1", "depth_from_c_far(c_far(c, z), c) = z (worst relative, z = 0.1..0.9)", worst_i, 0.0, 1e-14, false);
    }

    tb::heading("T2 the two spectral forms (exact rational arithmetic)");
    {
        const long long ze_n[] = {3, 1, 1, 1, 1};
        const long long ze_d[] = {10, 10, 100, 10000, 1000000};
        for (int i = 0; i < 5; ++i) {
            bool ok = true;
            const Fr ze{ze_n[i], ze_d[i]}, zo{ze_n[i], 3 * ze_d[i]};
            const Fr one{1, 1};
            const Fr lhs = fr_add(fr_add(fr_mul(fr_add(one, fr_neg(zo), ok), fr_inv(fr_add(one, fr_neg(ze), ok)), ok),
                                         fr_neg(one), ok),
                                  fr_neg(fr_add(ze, fr_neg(zo), ok)), ok);
            const Fr rhs = fr_mul(fr_mul(ze, fr_add(ze, fr_neg(zo), ok), ok), fr_inv(fr_add(one, fr_neg(ze), ok)), ok);
            const bool same = ok && fr_eq(lhs, rhs);
            const double engine = DC::z_spectral(double(ze.n) / double(ze.d), double(zo.n) / double(zo.d));
            const double zed = double(ze.n) / double(ze.d);
            tb::check_true("T2", ("exact identity: ratio form - engine form = z_e (z_e - z_o)/(1 - z_e), z_e = " +
                                  std::to_string(ze.n) + "/" + std::to_string(ze.d))
                                     .c_str(),
                           same);
            tb::note("z_e = %.0e: engine z_spec = %.6e ; difference / z_e^2 = %.6f (from the exact form %.6f/%.6f)", zed,
                     engine, double(rhs.n) / double(rhs.d) / (zed * zed), double(lhs.n) / double(lhs.d), double(rhs.n) / double(rhs.d));
        }
    }

    tb::heading("T3 integrated relay-speed deficit (Earth-Mars grazing geometry)");
    {
        const double Om = L::bridge::koppa_Sun, b = M::R_Sun, r1 = M::AU, r2 = 1.523679 * M::AU;
        const double l1 = std::sqrt(r1 * r1 - b * b), l2 = std::sqrt(r2 * r2 - b * b);
        const double eng = DC::shapiro_delay(Om, r1, r2, b);
        const double asinh_form = (2.0 * Om / M::c) * (std::asinh(l1 / b) + std::asinh(l2 / b));
        // exact integrand 1/c_far - 1/c with z = Om / r along the straight ray (panelled quadrature, log-spaced via sinh)
        auto integrand = [&](double u) {  // l = b sinh(u): dl = b cosh(u) du, r = b cosh(u)
            const double r = b * std::cosh(u);
            const double z = Om / r;
            // 1/c_far - 1/c = z (2 - z) / (c (1 - z)^2), written without cancellation
            return (z * (2.0 - z) / (M::c * (1.0 - z) * (1.0 - z))) * b * std::cosh(u);
        };
        const double u1 = std::asinh(l1 / b), u2 = std::asinh(l2 / b);
        const double exact = tb::integrate(integrand, -u1, u2, 48, 16);
        tb::check("T3a", "shapiro_delay vs (2 Om/c)[asinh(l1/b) + asinh(l2/b)]", eng, asinh_form, 5e-5);
        tb::check("T3b", "shapiro_delay vs quadrature of the exact integrand 1/c_far - 1/c", eng, exact, 1e-5);
        tb::note("Om_Sun = %.4f m ; impact parameter b = R_Sun ; r1 = 1 AU ; r2 = 1.523679 AU", Om);
        tb::note("one-way excess path count (delay x c / l_P) = %.6e relay hops", eng * M::c / M::l_P);
        tb::note("one-way delay %.6e (SI seconds, unit bridge); round trip %.4f microseconds", eng, 2.0 * eng * 1e6);
        tb::note("log form / asinh form - 1 = %.3e ; exact / log form - 1 = %.3e", eng / asinh_form - 1.0,
                 exact / eng - 1.0);
    }

    tb::heading("T4 recurrence counts");
    {
        struct Case {
            const char* name;
            double r, v;
        };
        const double k_sun = L::bridge::k_Sun_from_precession;
        const Case cases[] = {{"hydrogen ground state (r = a0, v = alpha c)", M::a_0, M::alpha * M::c},
                              {"Earth about the Sun (r = 1 AU, v = (c/k) sqrt(R/r))", M::AU,
                               L::bridge::v_orbital(k_sun, M::R_Sun, M::AU)}};
        for (const Case& cs : cases) {
            const double k = M::c / cs.v;
            const double P = 2.0 * kPi * cs.r / cs.v;
            const double n1 = 2.0 * kPi * k * cs.r / M::l_P;
            const double n2 = P * M::c / M::l_P;
            tb::check("T4", (std::string("relay intervals per orbit, two routes: ") + cs.name).c_str(), n1, n2, 1e-14);
            const double rad_per_crossing = (cs.v / cs.r) * (cs.r / M::c);
            tb::check("T4", (std::string("radians per light-crossing of r = v/c: ") + cs.name).c_str(), rad_per_crossing,
                      cs.v / M::c, 1e-14);
            tb::note("%s: k = %.6f, relay intervals per orbit = %.6e, rad per light-crossing = %.6e", cs.name, k, n1,
                     rad_per_crossing);
        }
    }

    tb::heading("T5 engine consistency of the counts");
    {
        tb::check("T5", "law_I::N vs R_CMB / l_P", L::law_I::N, M::R_CMB / M::l_P, 1e-14);
        tb::check("T5", "Om_H = alpha^2 a0 vs r_e (bridge::koppa_hydrogen)", L::bridge::koppa_hydrogen, M::r_e, 1e-9);
    }

    tb::heading("Table 3.1 hop counts (length / l_P), tabulated, not criteria");
    {
        struct Row {
            const char* name;
            double len;
        };
        const Row rows[] = {{"proton boundary R_p", M::R_p},
                            {"electron wake radius r_e", M::r_e},
                            {"Bohr radius a_0", M::a_0},
                            {"one metre", 1.0},
                            {"Earth radius", L::bridge::R_Earth},
                            {"Sun radius", M::R_Sun},
                            {"one astronomical unit", M::AU},
                            {"R_CMB (= N hops)", M::R_CMB}};
        for (const Row& r : rows) tb::note("%-28s %.4e hops", r.name, r.len / M::l_P);
        tb::note("relay rate c / l_P = %.6e per SI second (unit bridge); relay interval l_P / c = %.6e SI seconds", M::c / M::l_P,
                 M::l_P / M::c);
    }

    tb::heading("Table 3.2 depth values z = Om / r, tabulated, not criteria");
    {
        const double zS = L::depth_closure::z_spectral_Sun;
        const double zS_AU = L::bridge::koppa_Sun / M::AU;
        tb::note("Sun surface (Om_Sun / R_Sun)           z = %.6e", zS);
        tb::note("Sun at 1 AU (Om_Sun / AU)              z = %.6e", zS_AU);
        tb::note("z_spec, emitter Sun surface, observer 1 AU = z_e - z_o = %.6e", DC::z_spectral(zS, zS_AU));
        tb::note("hydrogen at a0 (Om_H / a0 = alpha^2)   z = %.6e", L::bridge::koppa_hydrogen / M::a_0);
        tb::note("hydrogen at r = Om_H = r_e             z = 1 (c-boundary; clock rate 1 - z = 0)");
    }

    return tb::finish();
}
