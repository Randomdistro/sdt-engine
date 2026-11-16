// Chapter 30 — atomic-nuclear correspondence: worked-example instrument.
// Pre-registration: Textbook/validation/ch30_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

namespace {

constexpr double kPi = std::numbers::pi;
using V3 = std::array<double, 3>;
using Pts = std::vector<V3>;

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

// Jacobi eigen decomposition of a symmetric 4x4 matrix.
void jacobi4(double A[4][4], double V[4][4], double w[4]) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) V[i][j] = (i == j);
    for (int sweep = 0; sweep < 100; ++sweep) {
        double off = 0.0;
        for (int i = 0; i < 4; ++i) for (int j = i + 1; j < 4; ++j) off += A[i][j] * A[i][j];
        if (off < 1e-30) break;
        for (int p = 0; p < 4; ++p)
            for (int q = p + 1; q < 4; ++q) {
                if (std::fabs(A[p][q]) < 1e-300) continue;
                const double th = (A[q][q] - A[p][p]) / (2.0 * A[p][q]);
                const double t = (th >= 0 ? 1.0 : -1.0) / (std::fabs(th) + std::sqrt(th * th + 1.0));
                const double c = 1.0 / std::sqrt(t * t + 1.0), s = t * c;
                for (int k = 0; k < 4; ++k) {
                    const double akp = A[k][p], akq = A[k][q];
                    A[k][p] = c * akp - s * akq;
                    A[k][q] = s * akp + c * akq;
                }
                for (int k = 0; k < 4; ++k) {
                    const double apk = A[p][k], aqk = A[q][k];
                    A[p][k] = c * apk - s * aqk;
                    A[q][k] = s * apk + c * aqk;
                }
                for (int k = 0; k < 4; ++k) {
                    const double vkp = V[k][p], vkq = V[k][q];
                    V[k][p] = c * vkp - s * vkq;
                    V[k][q] = s * vkp + c * vkq;
                }
            }
    }
    for (int i = 0; i < 4; ++i) w[i] = A[i][i];
}

// Best similarity (scale, rotation, translation) mapping P onto Q (Horn); returns relative RMS residual and scale.
double similarity(const Pts& P, const Pts& Q, double* scale) {
    const int n = static_cast<int>(P.size());
    V3 cp{}, cq{};
    for (int i = 0; i < n; ++i) for (int k = 0; k < 3; ++k) { cp[k] += P[i][k] / n; cq[k] += Q[i][k] / n; }
    double S[3][3] = {};
    double sp2 = 0.0, sq2 = 0.0;
    for (int i = 0; i < n; ++i) {
        V3 p, q;
        for (int k = 0; k < 3; ++k) { p[k] = P[i][k] - cp[k]; q[k] = Q[i][k] - cq[k]; }
        for (int a = 0; a < 3; ++a) for (int b = 0; b < 3; ++b) S[a][b] += p[a] * q[b];
        sp2 += p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
        sq2 += q[0] * q[0] + q[1] * q[1] + q[2] * q[2];
    }
    double N4[4][4] = {{S[0][0] + S[1][1] + S[2][2], S[1][2] - S[2][1], S[2][0] - S[0][2], S[0][1] - S[1][0]},
                       {S[1][2] - S[2][1], S[0][0] - S[1][1] - S[2][2], S[0][1] + S[1][0], S[2][0] + S[0][2]},
                       {S[2][0] - S[0][2], S[0][1] + S[1][0], -S[0][0] + S[1][1] - S[2][2], S[1][2] + S[2][1]},
                       {S[0][1] - S[1][0], S[2][0] + S[0][2], S[1][2] + S[2][1], -S[0][0] - S[1][1] + S[2][2]}};
    double V[4][4], w[4];
    jacobi4(N4, V, w);
    int best = 0;
    for (int i = 1; i < 4; ++i) if (w[i] > w[best]) best = i;
    const double q0 = V[0][best], q1 = V[1][best], q2 = V[2][best], q3 = V[3][best];
    const double R[3][3] = {{q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3, 2 * (q1 * q2 - q0 * q3), 2 * (q1 * q3 + q0 * q2)},
                            {2 * (q1 * q2 + q0 * q3), q0 * q0 - q1 * q1 + q2 * q2 - q3 * q3, 2 * (q2 * q3 - q0 * q1)},
                            {2 * (q1 * q3 - q0 * q2), 2 * (q2 * q3 + q0 * q1), q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3}};
    double num = 0.0;
    for (int i = 0; i < n; ++i) {
        V3 p, q;
        for (int k = 0; k < 3; ++k) { p[k] = P[i][k] - cp[k]; q[k] = Q[i][k] - cq[k]; }
        for (int a = 0; a < 3; ++a) {
            double rp = 0.0;
            for (int b = 0; b < 3; ++b) rp += R[a][b] * p[b];
            num += q[a] * rp;
        }
    }
    const double s = num / sp2;
    if (scale) *scale = s;
    double res = 0.0;
    for (int i = 0; i < n; ++i) {
        V3 p, q;
        for (int k = 0; k < 3; ++k) { p[k] = P[i][k] - cp[k]; q[k] = Q[i][k] - cq[k]; }
        for (int a = 0; a < 3; ++a) {
            double rp = 0.0;
            for (int b = 0; b < 3; ++b) rp += R[a][b] * p[b];
            res += (q[a] - s * rp) * (q[a] - s * rp);
        }
    }
    return std::sqrt(res / sq2);
}

double legendre(int l, double x) {
    double p0 = 1.0, p1 = x;
    if (l == 0) return 1.0;
    for (int k = 2; k <= l; ++k) {
        const double p2 = ((2 * k - 1) * x * p1 - (k - 1) * p0) / k;
        p0 = p1;
        p1 = p2;
    }
    return p1;
}

double invariant(const Pts& pts, int l) {
    const int n = static_cast<int>(pts.size());
    V3 c{};
    for (const auto& p : pts) for (int k = 0; k < 3; ++k) c[k] += p[k] / n;
    Pts s = pts;
    for (auto& p : s) for (int k = 0; k < 3; ++k) p[k] -= c[k];
    double num = 0.0, norm = 0.0;
    auto rr = [](const V3& v) { return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); };
    for (const auto& a : s) norm += std::pow(rr(a), l);
    for (const auto& a : s)
        for (const auto& b : s) {
            const double ra = rr(a), rb = rr(b);
            if (ra < 1e-14 || rb < 1e-14) continue;
            const double cg = (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]) / (ra * rb);
            num += std::pow(ra, l) * std::pow(rb, l) * legendre(l, std::fmax(-1.0, std::fmin(1.0, cg)));
        }
    return norm > 0 ? num / (norm * norm) : 0.0;
}

}  // namespace

int main() {
    namespace D = sdt::laws::atomic::dodecardinal;
    tb::validate_helpers();

    tb::heading("V1 exact mirror recovered by the similarity fit");
    {
        Rng g{5};
        Pts P;
        for (int i = 0; i < 12; ++i) P.push_back({g.next() - 0.5, g.next() - 0.5, g.next() - 0.5});
        const double a = 0.7, c = std::cos(a), s = std::sin(a);
        const double Rz[3][3] = {{c, -s, 0}, {s, c, 0}, {0, 0, 1}};
        const double b = 0.4, cb = std::cos(b), sb = std::sin(b);
        const double Rx[3][3] = {{1, 0, 0}, {0, cb, -sb}, {0, sb, cb}};
        Pts Q;
        for (const auto& p : P) {
            V3 t{};
            for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) t[i] += Rx[i][j] * (Rz[j][0] * p[0] + Rz[j][1] * p[1] + Rz[j][2] * p[2]);
            Q.push_back({2.7 * t[0] + 0.3, 2.7 * t[1] - 0.2, 2.7 * t[2] + 1.1});
        }
        double sc = 0.0;
        const double res = similarity(P, Q, &sc);
        tb::check("V1", "relative residual of an exact mirror", res, 0.0, 1e-12, false);
        tb::check("V1", "recovered scale 2.7", sc, 2.7, 1e-12);
    }

    tb::heading("T1 freedom census");
    {
        Rng g{12345};
        std::vector<double> res;
        int within = 0;
        for (int rep = 0; rep < 500; ++rep) {
            Pts P, Q;
            for (int i = 0; i < 12; ++i) {
                P.push_back({g.next() - 0.5, g.next() - 0.5, g.next() - 0.5});
                Q.push_back({g.next() - 0.5, g.next() - 0.5, g.next() - 0.5});
            }
            const double r = similarity(P, Q, nullptr);
            res.push_back(r);
            if (r <= 0.05) ++within;
        }
        std::sort(res.begin(), res.end());
        tb::note("independent 12-point sets, one global similarity: median residual %.3f ; minimum %.3f ; fraction within 5%%: %.2f%%", res[250], res[0], 100.0 * within / 500.0);
        tb::check_true("T1", "median residual >= 0.3 and at most 1% of pairs within 5%", res[250] >= 0.3 && within <= 5);
        for (int N : {3, 6, 12}) {
            std::vector<double> r;
            bool perobs_zero = true;
            for (int rep = 0; rep < 500; ++rep) {
                std::vector<double> a(N), b(N);
                double sab = 0, saa = 0, sbb = 0;
                for (int i = 0; i < N; ++i) {
                    a[i] = std::exp(4.0 * (g.next() - 0.5));
                    b[i] = std::exp(4.0 * (g.next() - 0.5));
                    sab += a[i] * b[i];
                    saa += a[i] * a[i];
                    sbb += b[i] * b[i];
                    perobs_zero = perobs_zero && std::fabs(b[i] - (b[i] / a[i]) * a[i]) < 1e-12 * b[i];
                }
                const double s = sab / saa;
                double ss = 0;
                for (int i = 0; i < N; ++i) ss += (b[i] - s * a[i]) * (b[i] - s * a[i]);
                r.push_back(std::sqrt(ss / sbb));
            }
            std::sort(r.begin(), r.end());
            int w5 = 0;
            for (double x : r) if (x <= 0.05) ++w5;
            tb::note("N = %2d random magnitudes, one global factor: median residual %.3f ; within 5%%: %.1f%% ; factor per observable: residual 0 for all", N, r[250], 100.0 * w5 / 500.0);
            char label[128];
            std::snprintf(label, sizeof label, "N=%d: single-factor median residual >= 0.3 and per-observable residual identically 0", N);
            tb::check_true("T1", label, r[250] >= 0.3 && perobs_zero);
        }
    }

    tb::heading("T2 rank content: atomic seat directions against nuclear shells");
    {
        auto unit = [](double x, double y, double z) { const double n = std::sqrt(x * x + y * y + z * z); return V3{x / n, y / n, z / n}; };
        Pts t8, t12, t14;
        for (int x : {-1, 1}) for (int y : {-1, 1}) for (int z : {-1, 1}) { t8.push_back(unit(x, y, z)); t14.push_back(unit(x, y, z)); }
        for (int s : {-1, 1}) { t14.push_back({double(s), 0, 0}); t14.push_back({0, double(s), 0}); t14.push_back({0, 0, double(s)}); }
        const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
        for (int a : {-1, 1}) for (int b : {-1, 1}) { t12.push_back(unit(0, a, b * phi)); t12.push_back(unit(a, b * phi, 0)); t12.push_back(unit(b * phi, 0, a)); }
        auto sig = [&](const char* name, const Pts& p) {
            std::string line;
            char buf[48];
            for (int l = 1; l <= 6; ++l) { std::snprintf(buf, sizeof buf, "I%d=%.3e ", l, invariant(p, l)); line += buf; }
            tb::note("%-14s %s", name, line.c_str());
        };
        sig("T8 (cube)", t8);
        sig("T12 (icosa)", t12);
        sig("T14 (cubocta)", t14);
        auto zero = [](double v) { return std::fabs(v) <= 1e-12; };
        tb::check_true("T2", "T8, T12, T14: I1 = I2 = I3 = 0", zero(invariant(t8, 1)) && zero(invariant(t8, 2)) && zero(invariant(t8, 3)) && zero(invariant(t12, 1)) && zero(invariant(t12, 2)) && zero(invariant(t12, 3)) && zero(invariant(t14, 1)) && zero(invariant(t14, 2)) && zero(invariant(t14, 3)));
        bool all_pos = true;
        for (int ne = 2; ne <= 10; ++ne) {
            std::array<D::Seat, 10> seats{};
            const int cnt = D::make_seats(ne, seats);
            Pts d;
            for (int i = 0; i < cnt; ++i) d.push_back({seats[i].direction[0], seats[i].direction[1], seats[i].direction[2]});
            char name[24];
            std::snprintf(name, sizeof name, "atomic Ne=%d", ne);
            sig(name, d);
            const double i2 = invariant(d, 2);
            if (!(i2 > 1e-6)) { all_pos = false; tb::note("  accidental zero at N_e = %d: I2 = %.3e", ne, i2); }
        }
        tb::check_true("T2", "atomic seat directions have I2 > 0 for every N_e = 2..10", all_pos);
    }

    return tb::finish();
}
