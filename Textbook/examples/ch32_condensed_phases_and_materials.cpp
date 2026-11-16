// Chapter 32 — condensed phases and materials: worked-example instrument (TOY stand-ins).
// Pre-registration: Textbook/validation/ch32_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <vector>

namespace {

constexpr double kPi = std::numbers::pi;

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

bool cholesky6(double C[6][6]) {
    double L[6][6] = {};
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j <= i; ++j) {
            double s = C[i][j];
            for (int k = 0; k < j; ++k) s -= L[i][k] * L[j][k];
            if (i == j) {
                if (s <= 1e-12) return false;
                L[i][i] = std::sqrt(s);
            } else L[i][j] = s / L[j][j];
        }
    return true;
}

void voigt(double c11, double c12, double c44, double C[6][6]) {
    for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) C[i][j] = 0.0;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) C[i][j] = (i == j) ? c11 : c12;
    for (int i = 3; i < 6; ++i) C[i][i] = c44;
}

// Smallest eigenvalue of the cubic Christoffel matrix for direction n (symmetric 3x3, Jacobi).
double min_christoffel(double c11, double c12, double c44, const std::array<double, 3>& n) {
    double A[3][3];
    for (int i = 0; i < 3; ++i)
        for (int k = 0; k < 3; ++k) {
            if (i == k) A[i][k] = c11 * n[i] * n[i] + c44 * (1.0 - n[i] * n[i]);
            else A[i][k] = (c12 + c44) * n[i] * n[k];
        }
    for (int sweep = 0; sweep < 60; ++sweep) {
        double off = A[0][1] * A[0][1] + A[0][2] * A[0][2] + A[1][2] * A[1][2];
        if (off < 1e-28) break;
        for (int p = 0; p < 3; ++p)
            for (int q = p + 1; q < 3; ++q) {
                if (std::fabs(A[p][q]) < 1e-300) continue;
                const double th = (A[q][q] - A[p][p]) / (2.0 * A[p][q]);
                const double t = (th >= 0 ? 1.0 : -1.0) / (std::fabs(th) + std::sqrt(th * th + 1.0));
                const double c = 1.0 / std::sqrt(t * t + 1.0), s = t * c;
                for (int k = 0; k < 3; ++k) { const double a = A[k][p], b = A[k][q]; A[k][p] = c * a - s * b; A[k][q] = s * a + c * b; }
                for (int k = 0; k < 3; ++k) { const double a = A[p][k], b = A[q][k]; A[p][k] = c * a - s * b; A[q][k] = s * a + c * b; }
            }
    }
    return std::fmin(A[0][0], std::fmin(A[1][1], A[2][2]));
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 isotropic constants");
    {
        const double lam = 2.0, G = 1.0, c11 = lam + 2 * G, c12 = lam, c44 = G;
        const double A = 2.0 * c44 / (c11 - c12);
        const double K = (c11 + 2 * c12) / 3.0, GV = (c11 - c12 + 3 * c44) / 5.0, GR = 5.0 * (c11 - c12) * c44 / (4.0 * c44 + 3.0 * (c11 - c12));
        tb::check("V1", "Zener ratio A = 1", A, 1.0, 1e-14);
        tb::check("V1", "bulk modulus = lambda + 2G/3", K, lam + 2.0 * G / 3.0, 1e-14);
        tb::check("V1", "G_V = G and G_R = G", GV + GR, 2.0 * G, 1e-14);
    }

    tb::heading("T1 elastic stability, wave speeds and anisotropy");
    {
        Rng g{20261110};
        long n = 0, bad_chol = 0, stable = 0, bad_wave = 0, bad_vr = 0;
        double maxspread = 0.0;
        for (int i = 0; i < 20000; ++i) {
            const double c11 = -2.0 + 12.0 * g.next(), c12 = -4.0 + 10.0 * g.next(), c44 = -2.0 + 7.0 * g.next();
            double C[6][6];
            voigt(c11, c12, c44, C);
            const bool pd = cholesky6(C);
            const bool ineq = (c11 > std::fabs(c12)) && (c11 + 2.0 * c12 > 0.0) && (c44 > 0.0);
            ++n;
            if (pd != ineq) ++bad_chol;
            if (!ineq) continue;
            ++stable;
            double mn = 1e300;
            for (int r = 0; r < 50; ++r) {
                std::array<double, 3> v{g.next() - 0.5, g.next() - 0.5, g.next() - 0.5};
                const double nn = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
                for (auto& x : v) x /= nn;
                mn = std::fmin(mn, min_christoffel(c11, c12, c44, v));
            }
            if (!(mn > 0.0)) ++bad_wave;
            const double d = c11 - c12;
            const double GV = (d + 3.0 * c44) / 5.0, GR = 5.0 * d * c44 / (4.0 * c44 + 3.0 * d);
            const double K = (c11 + 2.0 * c12) / 3.0, GH = 0.5 * (GV + GR);
            (void)K;
            if (GR > GV * (1.0 + 1e-12)) ++bad_vr;
            maxspread = std::fmax(maxspread, (GV - GR) / GH);
        }
        tb::note("%ld triples ; %ld stable ; max (G_V - G_R)/G_H = %.4f", n, stable, maxspread);
        tb::check_true("T1a", "Cholesky of the Voigt matrix equals the three inequalities for every triple", bad_chol == 0);
        tb::check_true("T1b", "every stable triple has a positive smallest Christoffel eigenvalue in 50 directions", bad_wave == 0 && stable > 1000);
        const double e100 = min_christoffel(3.0, 1.0, -1.0, {1.0, 0.0, 0.0});
        tb::check("T1b", "unstable triple (3,1,-1): the [100] shear eigenvalue is -1", e100, -1.0, 1e-12);
        tb::check_true("T1c", "G_R <= G_V for every stable triple", bad_vr == 0);
        double worst_iso = 0.0;
        for (int i = 0; i < 200; ++i) {
            const double lam = 0.2 + 5.0 * g.next(), G = 0.2 + 5.0 * g.next();
            const double c11 = lam + 2 * G, c12 = lam, c44 = G, d = c11 - c12;
            const double GV = (d + 3.0 * c44) / 5.0, GR = 5.0 * d * c44 / (4.0 * c44 + 3.0 * d);
            worst_iso = std::fmax(worst_iso, (GV - GR) / (0.5 * (GV + GR)));
        }
        tb::check("T1c", "spread (G_V - G_R)/G_H at A = 1 over 200 isotropic triples", worst_iso, 0.0, 1e-12, false);
    }

    tb::heading("T2 coexistence slope");
    {
        const double T0 = 1.0, s[2] = {1.0, 1.5}, c[2] = {2.0, 3.0}, v[2] = {1.0, 1.2}, kap[2] = {0.10, 0.12};
        auto gfun = [&](int i, double T, double P) { const double th = T - T0; return -s[i] * th - c[i] / (2.0 * T0) * th * th + v[i] * P - 0.5 * kap[i] * v[i] * P * P; };
        auto Pc = [&](double T) {
            double P = 0.0;
            for (int it = 0; it < 100; ++it) {
                const double f = gfun(0, T, P) - gfun(1, T, P);
                const double h = 1e-7;
                const double df = ((gfun(0, T, P + h) - gfun(1, T, P + h)) - (gfun(0, T, P - h) - gfun(1, T, P - h))) / (2 * h);
                const double step = f / df;
                P -= step;
                if (std::fabs(step) < 1e-14) break;
            }
            return P;
        };
        double worst = 0.0, worst2 = 0.0;
        for (int i = 0; i < 20; ++i) {
            const double T = 0.9 + 0.2 * i / 19.0;
            const double P = Pc(T), h = 1e-4;
            const double num = (Pc(T + h) - Pc(T - h)) / (2.0 * h);
            const double th = T - T0;
            double si[2], vi[2];
            for (int k = 0; k < 2; ++k) {
                si[k] = s[k] + c[k] / T0 * th;
                vi[k] = v[k] * (1.0 - kap[k] * P);
            }
            const double ds = si[1] - si[0], dv = vi[1] - vi[0];
            const double L = T * ds;
            worst = std::fmax(worst, std::fabs(num / (ds / dv) - 1.0));
            worst2 = std::fmax(worst2, std::fabs(num / (L / (T * dv)) - 1.0));
            if (i == 0 || i == 19) tb::note("T = %.3f : P_c = %.6f ; dP/dT = %.6f ; Delta s = %.4f ; Delta v = %.5f", T, P, num, ds, dv);
        }
        tb::check("T2", "dP_c/dT = Delta s/Delta v, worst relative over 20 temperatures", worst, 0.0, 1e-6, false);
        tb::check("T2", "dP_c/dT = L/(T Delta v) with L = T Delta s, worst relative", worst2, 0.0, 1e-6, false);
    }

    tb::heading("T3 periodic thermal forcing");
    {
        const double alpha = 1.0, omega = 2.0, Lx = 8.0, dx = 0.01, dt = 0.005;
        const int N = static_cast<int>(std::lround(Lx / dx));
        const double r = alpha * dt / (dx * dx);
        std::vector<double> T(N + 1, 0.0), a(N - 1), b(N - 1), cc(N - 1), d(N - 1), cp(N - 1), dp(N - 1);
        const int steps = static_cast<int>(std::lround(30.0 * 2.0 * kPi / omega / dt));
        const int per = static_cast<int>(std::lround(2.0 * kPi / omega / dt));
        const int i1 = static_cast<int>(std::lround(1.0 / dx)), i2 = static_cast<int>(std::lround(2.0 / dx));
        double s1c = 0, s1s = 0, s2c = 0, s2s = 0;
        double tcur = 0.0;
        for (int st = 1; st <= steps; ++st) {
            const double tn = st * dt;
            const double bl_old = std::cos(omega * tcur), bl_new = std::cos(omega * tn);
            for (int i = 1; i < N; ++i) {
                const double lap = T[i - 1] - 2.0 * T[i] + T[i + 1];
                d[i - 1] = T[i] + 0.5 * r * lap;
                a[i - 1] = -0.5 * r;
                b[i - 1] = 1.0 + r;
                cc[i - 1] = -0.5 * r;
            }
            d[0] += 0.5 * r * bl_new;
            // Thomas algorithm
            cp[0] = cc[0] / b[0];
            dp[0] = d[0] / b[0];
            for (int i = 1; i < N - 1; ++i) {
                const double m = b[i] - a[i] * cp[i - 1];
                cp[i] = cc[i] / m;
                dp[i] = (d[i] - a[i] * dp[i - 1]) / m;
            }
            std::vector<double> Tn(N + 1, 0.0);
            Tn[N - 1] = dp[N - 2];
            for (int i = N - 3; i >= 0; --i) Tn[i + 1] = dp[i] - cp[i] * Tn[i + 2];
            Tn[0] = bl_new;
            Tn[N] = 0.0;
            (void)bl_old;
            T = Tn;
            tcur = tn;
            if (st > steps - per) {
                s1c += T[i1] * std::cos(omega * tn) * dt;
                s1s += T[i1] * std::sin(omega * tn) * dt;
                s2c += T[i2] * std::cos(omega * tn) * dt;
                s2s += T[i2] * std::sin(omega * tn) * dt;
            }
        }
        const double P = kPi / omega;  // (period/2): integral of cos^2 over one period = period/2
        const double A1 = 2.0 * std::hypot(s1c, s1s) / (2.0 * P), A2 = 2.0 * std::hypot(s2c, s2s) / (2.0 * P);
        // T = A cos(omega t - phi): s_c = A P cos(phi)... , s_s = A P sin(phi)
        const double ph1 = std::atan2(s1s, s1c), ph2 = std::atan2(s2s, s2c);
        const double a1 = std::hypot(s1c, s1s) / P, a2 = std::hypot(s2c, s2s) / P;
        (void)A1; (void)A2;
        tb::note("amplitude at x = delta: %.6f (e^-1 = %.6f) ; at 2 delta: %.6f (e^-2 = %.6f) ; phase lag %.5f, %.5f rad", a1, std::exp(-1.0), a2, std::exp(-2.0), ph1, ph2);
        tb::check("T3", "amplitude at x = delta equals e^-1", a1, std::exp(-1.0), 3e-3);
        tb::check("T3", "amplitude at x = 2 delta equals e^-2", a2, std::exp(-2.0), 3e-3);
        tb::check("T3", "phase lag at x = delta equals 1 rad", ph1, 1.0, 5e-3, false);
        tb::check("T3", "phase lag at x = 2 delta equals 2 rad", ph2, 2.0, 5e-3, false);
    }

    return tb::finish();
}
