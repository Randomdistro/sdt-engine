// Chapter 58 — spherical numerical mechanics: worked-example instrument.
// Pre-registration: Textbook/validation/ch58_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/sphere_frame.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <numbers>
#include <random>
#include <stdexcept>
#include <vector>

namespace {

using sdt::sphere::Locus;
constexpr double PI = std::numbers::pi;

double haversine_angle(double th1, double ph1, double th2, double ph2) {
    const double dt = std::sin((th2 - th1) * 0.5), dp = std::sin((ph2 - ph1) * 0.5);
    const double h = dt * dt + std::sin(th1) * std::sin(th2) * dp * dp;
    return 2.0 * std::asin(std::sqrt(std::fmin(std::fmax(h, 0.0), 1.0)));
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    {
        const Locus a(1.0, PI / 2, 1.0), b(1.0, PI / 2, 1.0 + PI / 2);
        tb::check("V1", "perpendicular unit loci: sqrt 2", a.distance_to(b), std::sqrt(2.0), 1e-14);
        const Locus c(2.0, PI / 2, 1.0), d(3.0, PI / 2, 1.0 + PI);
        tb::check("V1", "antipodal loci of radii 2 and 3: 5", c.distance_to(d), 5.0, 1e-14);
        const Locus e(2.0, 1.0, 1.0), f(5.0, 1.0, 1.0);
        tb::check("V1", "one direction, radii 2 and 5: 3", e.distance_to(f), 3.0, 1e-14);
    }

    tb::heading("T1 stable differences");
    {
        const double ph1 = 1.0, ph2 = ph1 + 1e-9;
        const Locus a(1.0, PI / 2, ph1), b(1.0, PI / 2, ph2);
        const double psi = ph2 - ph1;  // stored values; exact subtraction
        const double naive_sq = 1.0 + 1.0 - 2.0 * std::cos(psi);
        const double d = a.distance_to(b), ref = 2.0 * std::sin(0.5 * psi);
        tb::note("psi (stored) = %.9e ; naive d^2 = %.3e ; distance_to = %.9e ; 2 sin(psi/2) = %.9e", psi, naive_sq, d, ref);
        tb::check_true("T1", "the law of cosines returns a value below 1e-17 (true value about 1e-18)", std::fabs(naive_sq) < 1e-17);
        tb::check("T1", "distance_to equals 2 sin(psi_stored/2)", d, ref, 1e-12);
        const Locus c(1.0, 1.0, 1.0), e(1.0 + 1e-9, 1.0, 1.0);
        tb::check("T1", "radii differing by 1e-9 at one direction", c.distance_to(e), (1.0 + 1e-9) - 1.0, 1e-6);
        const double delta = 1e-7, ph3 = 1.0 + PI - delta;
        const Locus p(1.0, PI / 2, 1.0), q(1.0, PI / 2, ph3);
        const double dstored = PI - (ph3 - 1.0);  // delta realised by the stored angles (pi from the library constant)
        const double eng = p.angular_distance(q), hav = haversine_angle(PI / 2, 1.0, PI / 2, ph3);
        const double eng_err = std::fabs((PI - eng) / dstored - 1.0), hav_err = std::fabs((PI - hav) / dstored - 1.0);
        tb::note("near-antipodal: delta (stored) = %.9e ; engine pi - psi = %.9e (relative error %.3e) ; haversine pi - psi = %.9e (relative error %.3e)", dstored, PI - eng, eng_err, PI - hav, hav_err);
        tb::check_true("T1", "the engine's angular distance has a relative error of delta below 1e-8", eng_err < 1e-8);
        tb::check_true("T1", "the haversine value has a relative error of delta above 1e-3", hav_err > 1e-3);
    }

    tb::heading("T2 resolution of the double-precision locus");
    {
        const double r = 1e7, ph1 = 1.2345;
        const double ph2 = std::nextafter(ph1, 10.0);
        const Locus a(r, PI / 2, ph1), b(r, PI / 2, ph2);
        const double d = a.distance_to(b);
        tb::note("one ulp in phi at 1.2345 = %.4e rad ; distance between the neighbours at r = 1e7 m = %.4e m", ph2 - ph1, d);
        tb::check_true("T2", "neighbouring representable azimuths are separated by 2.0e-9 to 2.4e-9 m", d >= 2.0e-9 && d <= 2.4e-9);
        const double half = ph1 + 0.4 * (ph2 - ph1);
        const Locus c(r, PI / 2, half);
        tb::check("T2", "a shift of 0.4 ulp is not representable (same locus)", a.distance_to(c), 0.0, 1e-30, false);
        std::mt19937_64 rng(20261110ULL);
        std::uniform_real_distribution<double> U(1.0, 2.0);
        const double s = 1e-3;
        double worst = 0.0;
        std::vector<double> errs;
        for (int i = 0; i < 200; ++i) {
            const double p1 = U(rng);
            const double p2 = p1 + s / r;
            const Locus x(r, PI / 2, p1), y(r, PI / 2, p2);
            const double err = std::fabs(x.distance_to(y) / s - 1.0);  // against the intended step s (run 1 compared with the stored step)
            errs.push_back(err);
            worst = std::fmax(worst, err);
        }
        std::sort(errs.begin(), errs.end());
        tb::note("step s = 1e-3 m at r = 1e7 m: maximum relative error over 200 azimuths %.3e ; median %.3e ; estimate eps r phi/s = %.3e", worst, errs[100], 1.11e-16 * r * 1.5 / s);
        tb::check_true("T2", "the maximum relative error is below 3e-6", worst < 3e-6);
        tb::check_true("T2", "the maximum relative error is above 1e-8 (order eps r phi/s)", worst > 1e-8);
    }

    tb::heading("T3 a regular centre-crossing chart");
    {
        const double b = 1000.0;
        double thmax = 0.0, rmin = 1e300, phimin = 1e300, phimax = -1e300;
        for (int k = 0; k <= 2000; ++k) {
            const double t = -1e5 + 2e5 * k / 2000.0;
            const double x = t, y = b, z = 0.0;
            const double r = std::sqrt(x * x + y * y + z * z);
            const double th = std::atan2(std::sqrt(x * x + y * y), z);
            const double ph = std::atan2(y, x);
            const Locus L(r, th, ph > 0 ? ph : ph + 2 * PI);
            thmax = std::fmax(thmax, std::fabs(L.theta() - PI / 2));
            rmin = std::fmin(rmin, L.radius());
            phimin = std::fmin(phimin, ph);
            phimax = std::fmax(phimax, ph);
        }
        tb::note("polar-angle deviation %.3e ; minimum radius %.6f m ; azimuth range %.6f", thmax, rmin, phimax - phimin);
        tb::check("T3", "polar angle equals pi/2 for every point (worst deviation)", thmax, 0.0, 1e-15, false);
        tb::check_true("T3", "the radius is at least 1000 m for every point", rmin >= 1000.0 - 1e-9);
        tb::check("T3", "the azimuth range is pi - 2 atan(0.01)", phimax - phimin, PI - 2.0 * std::atan(0.01), 1e-4);
        bool refused = false;
        try { Locus zero(0.0, PI / 2, 1.0); } catch (const std::domain_error&) { refused = true; }
        tb::check_true("T3", "the origin on the line: the locus at t = 0 (radius 0) is refused", refused);
        const double x = 1e-9, y = 0.0, z = 1.0, r = std::sqrt(x * x + y * y + z * z);
        const double th_acos = std::acos(z / r), th_atan = std::atan2(std::sqrt(x * x + y * y), z);
        tb::note("near the pole: acos route theta = %.3e ; atan2 route theta = %.3e (true 1e-9)", th_acos, th_atan);
        tb::check("T3", "the acos route returns theta = 0 at (1e-9, 0, 1) (error 100 per cent)", th_acos, 0.0, 1e-300, false);
        tb::check("T3", "the atan2 route returns 1e-9", th_atan, 1e-9, 1e-12);
        std::vector<double> raw, un;
        double prev = 0.0;
        for (int k = 0; k < 10; ++k) {
            double v = std::fmod(6.2 + 0.02 * k, 2.0 * PI);
            raw.push_back(v);
            double u = v;
            if (k > 0) { while (u - prev > PI) u -= 2.0 * PI; while (u - prev < -PI) u += 2.0 * PI; }
            un.push_back(u);
            prev = u;
        }
        double rawmax = 0.0, unmax = 0.0;
        for (int k = 1; k < 10; ++k) { rawmax = std::fmax(rawmax, std::fabs(raw[k] - raw[k - 1])); unmax = std::fmax(unmax, std::fabs(un[k] - un[k - 1])); }
        tb::note("azimuth path across the cut: raw maximum step %.4f ; unwrapped maximum step %.4f", rawmax, unmax);
        tb::check_true("T3", "the raw sequence jumps by more than 6", rawmax > 6.0);
        tb::check_true("T3", "the unwrapped sequence has a maximum step below 0.1", unmax < 0.1);
    }

    return tb::finish();
}
