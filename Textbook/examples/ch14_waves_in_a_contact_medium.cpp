// Chapter 14 — waves in a contact medium: worked-example instrument (TOY relay chain with reversal fraction s).
// Pre-registration: Textbook/validation/ch14_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch14_waves_in_a_contact_medium
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <complex>
#include <numeric>
#include <vector>

namespace {

using cd = std::complex<double>;
constexpr double kPi = std::numbers::pi;

struct Chain {
    int half;  // cells -half..half
    std::vector<double> R, L;
    explicit Chain(int h) : half(h), R(2 * h + 1, 0.0), L(2 * h + 1, 0.0) {}
    double& r(int i) { return R[i + half]; }
    double& l(int i) { return L[i + half]; }
    void step(double s) {
        std::vector<double> R2(R.size(), 0.0), L2(L.size(), 0.0);
        const int n = static_cast<int>(R.size());
        for (int j = 0; j < n; ++j) {
            if (j + 1 < n) R2[j + 1] += (1.0 - s) * R[j] + s * L[j];
            if (j - 1 >= 0) L2[j - 1] += (1.0 - s) * L[j] + s * R[j];
        }
        R.swap(R2);
        L.swap(L2);
    }
    double total() const { return std::accumulate(R.begin(), R.end(), 0.0) + std::accumulate(L.begin(), L.end(), 0.0); }
};

void eig(double s, double kappa, cd& lp, cd& lm) {
    const double a = (1.0 - s) * std::cos(kappa);
    const cd disc = std::sqrt(cd(a * a - (1.0 - 2.0 * s), 0.0));
    lp = a + disc;
    lm = a - disc;
}

// Periodic evolution of a complex two-component plane wave; returns the state after `steps` counts.
void evolve_plane(std::vector<cd>& R, std::vector<cd>& L, double s, int steps) {
    const int n = static_cast<int>(R.size());
    for (int m = 0; m < steps; ++m) {
        std::vector<cd> R2(n), L2(n);
        for (int j = 0; j < n; ++j) {
            R2[(j + 1) % n] += (1.0 - s) * R[j] + s * L[j];
            L2[(j - 1 + n) % n] += (1.0 - s) * L[j] + s * R[j];
        }
        R.swap(R2);
        L.swap(L2);
    }
}

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    tb::validate_helpers();

    tb::heading("V1 limiting cases of the chain");
    {
        Chain a(20);
        a.r(0) = 1.0;
        for (int m = 0; m < 7; ++m) a.step(0.0);
        bool ok = std::fabs(a.r(7) - 1.0) < 1e-15;
        for (int i = -20; i <= 20; ++i) {
            if (i != 7) ok = ok && a.r(i) == 0.0;
            ok = ok && a.l(i) == 0.0;
        }
        tb::check_true("V1", "s = 0: after 7 counts all content is at cell +7 moving right", ok);
        Chain b(20);
        b.r(0) = 1.0;
        bool alt = true;
        for (int m = 1; m <= 9; ++m) {
            b.step(1.0);
            alt = alt && (m % 2 == 1 ? std::fabs(b.l(-1) - 1.0) < 1e-15 : std::fabs(b.r(0) - 1.0) < 1e-15);
        }
        tb::check_true("V1", "s = 1: the content alternates between cells 0 and -1 and never advances", alt);
    }
    tb::heading("V2 eigenvalue formula in the limits");
    {
        cd lp, lm;
        eig(0.0, 0.7, lp, lm);
        tb::check("V2", "s = 0: lambda_+ = exp(+- i kappa) (distance of the pair from {e^{i k}, e^{-i k}})",
                  std::min(std::abs(lp - std::polar(1.0, 0.7)), std::abs(lp - std::polar(1.0, -0.7))) + std::min(std::abs(lm - std::polar(1.0, 0.7)), std::abs(lm - std::polar(1.0, -0.7))), 0.0, 1e-14, false);
        eig(1.0, 0.7, lp, lm);
        tb::check("V2", "s = 1: lambda = +-1", std::fabs(std::fabs(lp.real()) - 1.0) + std::fabs(std::fabs(lm.real()) - 1.0), 0.0, 1e-14, false);
    }

    tb::heading("T1 conservation and positivity (500 counts, isotropic start)");
    for (double s : {0.0, 0.1, 0.3, 0.5}) {
        Chain c(520);
        c.r(0) = 0.5;
        c.l(0) = 0.5;
        for (int m = 0; m < 500; ++m) c.step(s);
        const double mn = std::min(*std::min_element(c.R.begin(), c.R.end()), *std::min_element(c.L.begin(), c.L.end()));
        tb::check("T1", ("total content, s = " + std::to_string(s)).c_str(), c.total(), 1.0, 1e-12);
        tb::check_true("T1", ("minimum content >= 0, s = " + std::to_string(s)).c_str(), mn >= 0.0);
    }

    tb::heading("T2 dispersion by direct simulation of plane waves");
    {
        double worst = 0.0;
        const int N = 128, steps = 10;
        for (double s : {0.1, 0.3})
            for (int j : {8, 16, 32, 48}) {
                const double kappa = 2.0 * kPi * j / N;
                cd lp, lm;
                eig(s, kappa, lp, lm);
                for (const cd lam : {lp, lm}) {
                    // eigenvector of M(kappa) = [[(1-s)e^{-ik}, s e^{-ik}],[s e^{ik}, (1-s)e^{ik}]] for eigenvalue lam
                    const cd m11 = (1.0 - s) * std::polar(1.0, -kappa), m12 = s * std::polar(1.0, -kappa);
                    cd r = m12, l = lam - m11;  // (M - lam) v = 0  =>  v = (m12, lam - m11)
                    const double nrm = std::sqrt(std::norm(r) + std::norm(l));
                    r /= nrm;
                    l /= nrm;
                    std::vector<cd> R(N), L(N);
                    for (int i = 0; i < N; ++i) {
                        R[i] = r * std::polar(1.0, kappa * i);
                        L[i] = l * std::polar(1.0, kappa * i);
                    }
                    evolve_plane(R, L, s, steps);
                    const cd want = std::pow(lam, steps);
                    worst = std::fmax(worst, std::abs(R[0] / r - want) / std::abs(want));
                    worst = std::fmax(worst, std::abs(L[0] / l - want) / std::abs(want));
                }
            }
        tb::check("T2", "amplitude after 10 counts / lambda^10 - 1, worst over 16 modes", worst, 0.0, 1e-10, false);
    }

    tb::heading("T3 closed forms of the wave and diffusive branches");
    {
        for (double s : {0.1, 0.3}) {
            const double rho2 = 1.0 - 2.0 * s;
            const double kc = std::acos(std::sqrt(rho2) / (1.0 - s));
            // (a) |lambda|^2 on the wave branch
            double worst_mod = 0.0;
            for (double kappa : {kc * 1.2, 0.5, kPi / 2, 2.5}) {
                cd lp, lm;
                eig(s, kappa, lp, lm);
                worst_mod = std::fmax(worst_mod, std::fabs(std::norm(lp) - rho2));
            }
            tb::check("T3", ("|lambda|^2 = 1 - 2s on the wave branch, s = " + std::to_string(s)).c_str(), worst_mod, 0.0, 1e-14, false);
            // (b) cutoff
            cd lp, lm;
            eig(s, kc * 0.9, lp, lm);
            const bool below_real = std::fabs(lp.imag()) < 1e-12;
            eig(s, kc * 1.1, lp, lm);
            const bool above_complex = std::fabs(lp.imag()) > 1e-6;
            tb::check_true("T3", ("cutoff kappa_c separates real from complex eigenvalues, s = " + std::to_string(s) + ", kappa_c = " + std::to_string(kc)).c_str(), below_real && above_complex);
            // (c) group velocity at pi/2
            auto phi = [&](double k) { cd a, b; eig(s, k, a, b); return std::fabs(std::arg(a)); };
            const double h = 1e-5;
            const double vg_num = (phi(kPi / 2 + h) - phi(kPi / 2 - h)) / (2.0 * h);
            const double vg_cl = (1.0 - s) / std::sqrt(rho2);
            tb::check("T3", ("v_g(pi/2) closed form vs central difference of phi(kappa), s = " + std::to_string(s)).c_str(), vg_num, vg_cl, 1e-8);
            tb::note("s = %.1f: kappa_c = %.5f, decay rate per count = %.6f, v_g(pi/2) = %.6f, sin(kappa_c) = %.6f, s/(1-s) = %.6f", s, kc, -0.5 * std::log(rho2), vg_cl, std::sin(kc), s / (1.0 - s));
            if (s == 0.1) tb::check_true("T3", "group velocity at pi/2 exceeds the hop speed 1 (s = 0.1)", vg_cl > 1.0);
            // (e) exact group velocity on the wave branch
            double worst_vg = 0.0;
            bool above_one = true;
            for (double k : {0.6, 1.0, kPi / 2, 2.0, 2.4}) {
                const double vg_num2 = (phi(k + h) - phi(k - h)) / (2.0 * h);
                const double vg_exact = 1.0 / std::sqrt(1.0 - std::pow(s / ((1.0 - s) * std::sin(k)), 2));
                worst_vg = std::fmax(worst_vg, std::fabs(vg_num2 / vg_exact - 1.0));
                above_one = above_one && vg_exact > 1.0;
                tb::note("s = %.1f, kappa = %.4f: phase speed %.6f, group velocity %.6f", s, k, phi(k) / k, vg_exact);
            }
            tb::check("T3e", ("v_g = 1/sqrt(1 - (s/((1-s) sin kappa))^2) vs central difference, worst relative, s = " + std::to_string(s)).c_str(), worst_vg, 0.0, 1e-8, false);
            tb::check("T3e", ("band edge sin(kappa_c) = s/(1-s), s = " + std::to_string(s)).c_str(), std::sin(kc), s / (1.0 - s), 1e-12);
            tb::check_true("T3e", ("v_g > 1 at every tested kappa, s = " + std::to_string(s)).c_str(), above_one);
            // (d) diffusive branch
            const double kap = 1e-3;
            eig(s, kap, lp, lm);
            const double D = (1.0 - s) / (2.0 * s);
            tb::check("T3", ("lambda_+ at kappa = 1e-3 vs 1 - D kappa^2, s = " + std::to_string(s)).c_str(), (1.0 - lp.real()) / (D * kap * kap), 1.0, 1e-3);
        }
    }

    tb::heading("T4 front: hop-causal support");
    for (double s : {0.0, 0.1, 0.5}) {
        const int m = 300;
        Chain c(m + 5);
        c.r(0) = 0.5;
        c.l(0) = 0.5;
        for (int k = 0; k < m; ++k) c.step(s);
        bool beyond_zero = true;
        for (int i = m + 1; i <= m + 5; ++i) beyond_zero = beyond_zero && c.r(i) == 0.0 && c.l(i) == 0.0 && c.r(-i) == 0.0 && c.l(-i) == 0.0;
        const double end = c.r(m), want = 0.5 * std::pow(1.0 - s, m - 1);
        tb::check_true("T4", ("no content beyond cell +-300 after 300 counts, s = " + std::to_string(s)).c_str(), beyond_zero);
        tb::check("T4", ("content at the front cell vs (1/2)(1-s)^299, s = " + std::to_string(s)).c_str(), end, want, 1e-12);
    }

    tb::heading("T5 variance and the transport coefficient");
    for (double s : {0.1, 0.3, 0.5}) {
        const int m = 1000;
        Chain c(m + 5);
        c.r(0) = 0.5;
        c.l(0) = 0.5;
        for (int k = 0; k < m; ++k) c.step(s);
        double var = 0.0;
        for (int i = -m; i <= m; ++i) var += static_cast<double>(i) * i * (c.r(i) + c.l(i));
        const double rho = 1.0 - 2.0 * s;
        const double closed = m * (1.0 + rho) / (1.0 - rho) - 2.0 * rho * (1.0 - std::pow(rho, m)) / ((1.0 - rho) * (1.0 - rho));
        tb::check("T5", ("sigma^2(1000) vs closed form, s = " + std::to_string(s)).c_str(), var, closed, 1e-10);
        const double D = (1.0 - s) / (2.0 * s);
        tb::note("s = %.1f: sigma^2/(2m) = %.6f ; D = (1-s)/(2s) = %.6f", s, var / (2.0 * m), D);
        if (s == 0.1) tb::check("T5", "sigma^2/(2m) within 2% of D for s = 0.1", var / (2.0 * m), D, 2e-2);
    }

    tb::heading("T6 eikonal ray in n(y) = 1/y");
    {
        double x = 0.0, y = 1.0, tx = 1.0, ty = 0.0, s = 0.0;
        const double ds = 1e-3;
        auto rhs = [](double /*x*/, double y, double tx, double ty, double* d) {
            // dt/ds = grad_perp ln n,  ln n = -ln y  =>  grad ln n = (0, -1/y)
            const double gx = 0.0, gy = -1.0 / y;
            const double dot = tx * gx + ty * gy;
            d[0] = tx; d[1] = ty; d[2] = gx - dot * tx; d[3] = gy - dot * ty;
        };
        double worst = 0.0;
        while (s < 1.2 - 1e-12) {
            double k1[4], k2[4], k3[4], k4[4];
            rhs(x, y, tx, ty, k1);
            rhs(x + 0.5 * ds * k1[0], y + 0.5 * ds * k1[1], tx + 0.5 * ds * k1[2], ty + 0.5 * ds * k1[3], k2);
            rhs(x + 0.5 * ds * k2[0], y + 0.5 * ds * k2[1], tx + 0.5 * ds * k2[2], ty + 0.5 * ds * k2[3], k3);
            rhs(x + ds * k3[0], y + ds * k3[1], tx + ds * k3[2], ty + ds * k3[3], k4);
            x += ds / 6.0 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]);
            y += ds / 6.0 * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]);
            tx += ds / 6.0 * (k1[2] + 2 * k2[2] + 2 * k3[2] + k4[2]);
            ty += ds / 6.0 * (k1[3] + 2 * k2[3] + 2 * k3[3] + k4[3]);
            const double nt = std::hypot(tx, ty);
            tx /= nt; ty /= nt;
            s += ds;
            worst = std::fmax(worst, std::hypot(x - std::sin(s), y - std::cos(s)));
        }
        tb::check("T6", "ray position vs (sin s, cos s), worst deviation to path length 1.2", worst, 0.0, 1e-9, false);
        tb::check("T6", "x^2 + y^2 - 1 at the end", x * x + y * y - 1.0, 0.0, 1e-9, false);
    }

    tb::heading("T7 engine acoustic relation");
    {
        namespace RA = sdt::laws::bridge::release_acoustics;
        tb::check("T7", "c_s/c at R = 0 is 1/sqrt3", RA::sound_speed(0.0) / M::c, 1.0 / std::sqrt(3.0), 1e-12);
        tb::check("T7", "c_s/c at R = 0.6 is 0.4564354646", RA::sound_speed(0.6) / M::c, 0.4564354646, 1e-9);
        tb::check("T7", "c_s/c at R = 3/4 is 1/sqrt(3 x 1.75)", RA::sound_speed(0.75) / M::c, 1.0 / std::sqrt(3.0 * 1.75), 1e-12);
        tb::check_true("T7", "c_s strictly decreasing in R", RA::sound_speed(0.2) > RA::sound_speed(0.6) && RA::sound_speed(0.6) > RA::sound_speed(1.5));
    }

    return tb::finish();
}
