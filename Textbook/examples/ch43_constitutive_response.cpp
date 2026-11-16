// Chapter 43 — constitutive response: worked-example instrument (generic stand-ins).
// Pre-registration: Textbook/validation/ch43_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

namespace {

using Mat = std::vector<std::vector<double>>;

std::vector<double> solve(Mat A, std::vector<double> b) {
    const int n = static_cast<int>(b.size());
    for (int c = 0; c < n; ++c) {
        int p = c;
        for (int r = c + 1; r < n; ++r) if (std::fabs(A[r][c]) > std::fabs(A[p][c])) p = r;
        std::swap(A[c], A[p]);
        std::swap(b[c], b[p]);
        for (int r = c + 1; r < n; ++r) {
            const double f = A[r][c] / A[c][c];
            for (int k = c; k < n; ++k) A[r][k] -= f * A[c][k];
            b[r] -= f * b[c];
        }
    }
    std::vector<double> x(n);
    for (int r = n - 1; r >= 0; --r) {
        double v = b[r];
        for (int k = r + 1; k < n; ++k) v -= A[r][k] * x[k];
        x[r] = v / A[r][r];
    }
    return x;
}

struct Kkt {
    std::vector<double> J, lam;
    double Fstar;
};

// minimise 1/2 J'QJ + c'J subject to C J = b ; L = F + lambda'(C J - b)
Kkt solve_kkt(const Mat& Q, const std::vector<double>& c, const Mat& C, const std::vector<double>& b) {
    const int n = static_cast<int>(c.size()), m = static_cast<int>(b.size());
    Mat K(n + m, std::vector<double>(n + m, 0.0));
    std::vector<double> rhs(n + m, 0.0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) K[i][j] = Q[i][j];
        for (int k = 0; k < m; ++k) K[i][n + k] = C[k][i];
        rhs[i] = -c[i];
    }
    for (int k = 0; k < m; ++k) {
        for (int j = 0; j < n; ++j) K[n + k][j] = C[k][j];
        rhs[n + k] = b[k];
    }
    const auto sol = solve(K, rhs);
    Kkt r;
    r.J.assign(sol.begin(), sol.begin() + n);
    r.lam.assign(sol.begin() + n, sol.end());
    double F = 0.0;
    for (int i = 0; i < n; ++i) {
        F += c[i] * r.J[i];
        for (int j = 0; j < n; ++j) F += 0.5 * r.J[i] * Q[i][j] * r.J[j];
    }
    r.Fstar = F;
    return r;
}

// Symmetric Jacobi eigenvalues (n x n)
std::vector<double> jacobi_eigs(Mat A) {
    const int n = static_cast<int>(A.size());
    for (int sweep = 0; sweep < 100; ++sweep) {
        double off = 0.0;
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) off += A[i][j] * A[i][j];
        if (off < 1e-30) break;
        for (int p = 0; p < n; ++p)
            for (int q = p + 1; q < n; ++q) {
                if (std::fabs(A[p][q]) < 1e-300) continue;
                const double th = (A[q][q] - A[p][p]) / (2.0 * A[p][q]);
                const double t = (th >= 0 ? 1.0 : -1.0) / (std::fabs(th) + std::sqrt(th * th + 1.0));
                const double c = 1.0 / std::sqrt(t * t + 1.0), s = t * c;
                for (int k = 0; k < n; ++k) { const double a = A[k][p], b = A[k][q]; A[k][p] = c * a - s * b; A[k][q] = s * a + c * b; }
                for (int k = 0; k < n; ++k) { const double a = A[p][k], b = A[q][k]; A[p][k] = c * a - s * b; A[q][k] = s * a + c * b; }
            }
    }
    std::vector<double> e(n);
    for (int i = 0; i < n; ++i) e[i] = A[i][i];
    std::sort(e.begin(), e.end());
    return e;
}

Mat sens(double Delta, const std::vector<double>& t) {
    const double a = 1.0, b = 1.0, c = 1.0, d = 1.0 + Delta;
    Mat S;
    for (double tk : t) S.push_back({std::exp(-b * tk), -a * tk * std::exp(-b * tk), std::exp(-d * tk), -c * tk * std::exp(-d * tk)});
    return S;
}

// One-sided Jacobi (Hestenes) singular values: orthogonalise the columns; does not form S'S.
std::vector<double> singulars(Mat S) {
    const int m = static_cast<int>(S.size()), n = static_cast<int>(S[0].size());
    for (int sweep = 0; sweep < 200; ++sweep) {
        bool rotated = false;
        for (int p = 0; p < n; ++p)
            for (int q = p + 1; q < n; ++q) {
                double a = 0, b = 0, g = 0;
                for (int k = 0; k < m; ++k) { a += S[k][p] * S[k][p]; b += S[k][q] * S[k][q]; g += S[k][p] * S[k][q]; }
                if (std::fabs(g) <= 1e-15 * std::sqrt(a * b) || a == 0.0 || b == 0.0) continue;
                rotated = true;
                const double zeta = (b - a) / (2.0 * g);
                const double t = (zeta >= 0 ? 1.0 : -1.0) / (std::fabs(zeta) + std::sqrt(1.0 + zeta * zeta));
                const double c = 1.0 / std::sqrt(1.0 + t * t), s = c * t;
                for (int k = 0; k < m; ++k) {
                    const double sp = S[k][p], sq = S[k][q];
                    S[k][p] = c * sp - s * sq;
                    S[k][q] = s * sp + c * sq;
                }
            }
        if (!rotated) break;
    }
    std::vector<double> e(n);
    for (int j = 0; j < n; ++j) { double s = 0; for (int k = 0; k < m; ++k) s += S[k][j] * S[k][j]; e[j] = std::sqrt(s); }
    std::sort(e.begin(), e.end());
    return e;
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    {
        const auto r = solve_kkt({{1, 0}, {0, 1}}, {0, 0}, {{1, 1}}, {1.0});
        tb::check("V1", "J_1 = 1/2", r.J[0], 0.5, 1e-12);
        tb::check("V1", "lambda = -1/2", r.lam[0], -0.5, 1e-12);
        tb::check("V1", "F* = 1/4", r.Fstar, 0.25, 1e-12);
        // rotated diag(1,4,9,16)
        const double ca = std::cos(0.6), sa = std::sin(0.6), cb = std::cos(0.9), sb = std::sin(0.9);
        Mat R = {{ca, -sa, 0, 0}, {sa, ca, 0, 0}, {0, 0, cb, -sb}, {0, 0, sb, cb}};
        Mat D = {{1, 0, 0, 0}, {0, 4, 0, 0}, {0, 0, 9, 0}, {0, 0, 0, 16}};
        Mat T(4, std::vector<double>(4, 0)), A(4, std::vector<double>(4, 0));
        for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) for (int k = 0; k < 4; ++k) T[i][j] += R[i][k] * D[k][j];
        for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) for (int k = 0; k < 4; ++k) A[i][j] += T[i][k] * R[j][k];
        const auto e = jacobi_eigs(A);
        tb::check("V1", "Jacobi eigenvalues 1, 4, 9, 16 (worst absolute error)", std::fmax(std::fmax(std::fabs(e[0] - 1), std::fabs(e[1] - 4)), std::fmax(std::fabs(e[2] - 9), std::fabs(e[3] - 16))), 0.0, 1e-12, false);
    }

    tb::heading("T1 constrained allocation and its dual variables");
    {
        const Mat Q = {{2, .2, 0, 0}, {.2, 3, .1, 0}, {0, .1, 4, .3}, {0, 0, .3, 5}};
        const std::vector<double> c = {1, -2, .5, 1};
        const Mat C = {{1, 1, 1, 1}, {1, -1, 0, 2}};
        const std::vector<double> b = {1.0, 0.3};
        const auto r = solve_kkt(Q, c, C, b);
        double g = 0.0, cons = 0.0;
        for (int i = 0; i < 4; ++i) {
            double gi = c[i];
            for (int j = 0; j < 4; ++j) gi += Q[i][j] * r.J[j];
            for (int k = 0; k < 2; ++k) gi += C[k][i] * r.lam[k];
            g = std::fmax(g, std::fabs(gi));
        }
        for (int k = 0; k < 2; ++k) {
            double s = -b[k];
            for (int i = 0; i < 4; ++i) s += C[k][i] * r.J[i];
            cons = std::fmax(cons, std::fabs(s));
        }
        tb::check("T1", "stationarity residual |grad F + C' lambda|", g, 0.0, 1e-12, false);
        tb::check("T1", "constraint residual |C J - b|", cons, 0.0, 1e-12, false);
        tb::note("J = (%.6f, %.6f, %.6f, %.6f) ; lambda = (%.6f, %.6f) ; F* = %.8f", r.J[0], r.J[1], r.J[2], r.J[3], r.lam[0], r.lam[1], r.Fstar);
        for (int i = 0; i < 2; ++i) {
            auto bp = b, bm = b;
            bp[i] += 1e-4;
            bm[i] -= 1e-4;
            const double dF = (solve_kkt(Q, c, C, bp).Fstar - solve_kkt(Q, c, C, bm).Fstar) / 2e-4;
            char lab[96];
            std::snprintf(lab, sizeof lab, "dF*/db_%d (central difference) = -lambda_%d", i + 1, i + 1);
            tb::check("T1", lab, dF, -r.lam[i], 1e-8);
        }
    }

    tb::heading("T2 identifiability: rank and conditioning of the sensitivity matrix");
    {
        std::vector<double> t;
        for (int k = 1; k <= 10; ++k) t.push_back(0.2 * k);
        double kap[3];
        int idx = 0;
        for (double Dl : {1.0, 0.1, 0.01}) {
            const auto s = singulars(sens(Dl, t));
            kap[idx] = s[3] / s[0];
            tb::note("Delta = %-5g : singular values %.3e %.3e %.3e %.3e ; condition number %.3e", Dl, s[0], s[1], s[2], s[3], kap[idx]);
            ++idx;
        }
        tb::check_true("T2", "the condition number increases as Delta falls through 1, 0.1, 0.01", kap[0] < kap[1] && kap[1] < kap[2]);
        tb::check_true("T2", "the condition number at Delta = 0.01 is finite and at least 5 times that at Delta = 0.1", std::isfinite(kap[2]) && kap[2] >= 5.0 * kap[1]);
        const auto s0 = singulars(sens(0.0, t));
        tb::note("Delta = 0 : singular values %.3e %.3e %.3e %.3e", s0[0], s0[1], s0[2], s0[3]);
        tb::check_true("T2", "at Delta = 0 the smallest singular value is below 1e-6 of the largest", s0[0] < 1e-6 * s0[3]);
    }

    tb::heading("T3 which measurement helps (Delta = 0.1)");
    {
        std::vector<double> t;
        for (int k = 1; k <= 10; ++k) t.push_back(0.2 * k);
        const auto s = singulars(sens(0.1, t));
        const double k0 = s[3] / s[0];
        auto t2 = t;
        for (double x : t) t2.push_back(x);
        const auto sr = singulars(sens(0.1, t2));
        const double kr = sr[3] / sr[0];
        auto t3 = t;
        for (int k = 0; k < 10; ++k) t3.push_back(4.0 + 0.5 * k);
        const auto sl = singulars(sens(0.1, t3));
        const double kl = sl[3] / sl[0];
        tb::note("condition number: base %.4e ; repeated times %.4e ; added later times %.4e (reduction factor %.2f)", k0, kr, kl, k0 / kl);
        tb::check("T3", "repeating the same times leaves the condition number unchanged", kr, k0, 1e-12);
        tb::check_true("T3", "adding samples at t = 4 ... 8.5 reduces the condition number by at least a factor 2", k0 / kl >= 2.0);
    }

    return tb::finish();
}
