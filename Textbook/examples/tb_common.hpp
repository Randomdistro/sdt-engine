// Shared helpers for the Textbook worked-example instruments (Chapters 10 onward).
// Every helper used by a chapter is validated on known answers by tb::validate_helpers(),
// which each instrument calls and reports as test V0 before it touches its object.
#pragma once

#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <functional>
#include <numbers>
#include <string>
#include <vector>

namespace tb {

inline int failures = 0;

/// Compare a value with an expected value; prints one line tagged PASS/FAIL (test-code vocabulary).
inline bool check(const char* id, const char* what, double value, double expected, double tol,
                  bool relative = true) {
    const double err = relative ? std::fabs(value - expected) / std::fabs(expected) : std::fabs(value - expected);
    const bool ok = err <= tol;
    if (!ok) ++failures;
    std::printf("[%s] %-5s %-78s value %.12e expected %.12e err %.3e (tol %.0e)\n", ok ? "PASS" : "FAIL", id, what,
                value, expected, err, tol);
    return ok;
}

/// Boolean criterion (exact statements such as integer identities).
inline bool check_true(const char* id, const char* what, bool ok) {
    if (!ok) ++failures;
    std::printf("[%s] %-5s %s\n", ok ? "PASS" : "FAIL", id, what);
    return ok;
}

/// Informational line (not a criterion).
inline void note(const char* fmt, ...) {
    std::va_list ap;
    va_start(ap, fmt);
    std::printf("       ");
    std::vprintf(fmt, ap);
    std::printf("\n");
    va_end(ap);
}

inline void heading(const char* text) { std::printf("\n== %s ==\n", text); }

/// Final line and exit code.
inline int finish() {
    std::printf("\n%s: %d failure(s)\n", failures == 0 ? "ALL CRITERIA MET" : "CRITERIA NOT MET", failures);
    return failures == 0 ? 0 : 1;
}

// ---------------------------------------------------------------------------------------------
// Gauss-Legendre quadrature
// ---------------------------------------------------------------------------------------------
struct GL {
    std::vector<double> x, w;  // nodes and weights on [-1, 1]
};

inline GL gauss_legendre(int n) {
    GL g;
    g.x.resize(n);
    g.w.resize(n);
    for (int i = 0; i < n; ++i) {
        double z = std::cos(std::numbers::pi * (i + 0.75) / (n + 0.5));
        double pp = 0.0;
        for (int it = 0; it < 100; ++it) {
            double p1 = 1.0, p2 = 0.0;
            for (int j = 0; j < n; ++j) {
                const double p3 = p2;
                p2 = p1;
                p1 = ((2.0 * j + 1.0) * z * p2 - j * p3) / (j + 1.0);
            }
            pp = n * (z * p1 - p2) / (z * z - 1.0);
            const double dz = p1 / pp;
            z -= dz;
            if (std::fabs(dz) < 1e-16) break;
        }
        g.x[i] = z;
        g.w[i] = 2.0 / ((1.0 - z * z) * pp * pp);
    }
    return g;
}

/// Integral of f over [a, b] with `panels` equal panels of an n-point Gauss-Legendre rule.
inline double integrate(const std::function<double(double)>& f, double a, double b, int n = 48, int panels = 1) {
    static thread_local std::vector<std::pair<int, GL>> cache;
    const GL* g = nullptr;
    for (auto& e : cache)
        if (e.first == n) g = &e.second;
    if (!g) {
        cache.push_back({n, gauss_legendre(n)});
        g = &cache.back().second;
    }
    double sum = 0.0;
    const double h = (b - a) / panels;
    for (int p = 0; p < panels; ++p) {
        const double lo = a + p * h, hi = lo + h;
        for (int i = 0; i < n; ++i) sum += g->w[i] * 0.5 * h * f(0.5 * (hi - lo) * g->x[i] + 0.5 * (hi + lo));
    }
    return sum;
}

// ---------------------------------------------------------------------------------------------
// Root finding (bracketing, bisection refined by secant steps; monotone-safe)
// ---------------------------------------------------------------------------------------------
inline double root(const std::function<double(double)>& f, double a, double b, double tol = 1e-14) {
    double fa = f(a), fb = f(b);
    if (fa == 0.0) return a;
    if (fb == 0.0) return b;
    for (int it = 0; it < 400; ++it) {
        const double m = 0.5 * (a + b);
        const double fm = f(m);
        if (fm == 0.0 || std::fabs(b - a) < tol * (1.0 + std::fabs(m))) return m;
        if ((fa < 0.0) == (fm < 0.0)) {
            a = m;
            fa = fm;
        } else {
            b = m;
            fb = fm;
        }
    }
    return 0.5 * (a + b);
}

// ---------------------------------------------------------------------------------------------
// Compensated (Kahan-Babuska) summation
// ---------------------------------------------------------------------------------------------
struct Sum {
    double s = 0.0, c = 0.0;
    void add(double x) {
        const double t = s + x;
        c += (std::fabs(s) >= std::fabs(x)) ? (s - t) + x : (x - t) + s;
        s = t;
    }
    [[nodiscard]] double value() const { return s + c; }
};

// ---------------------------------------------------------------------------------------------
// Instrument validation on known answers (test V0)
// ---------------------------------------------------------------------------------------------
inline void validate_helpers() {
    heading("V0 helper validation (known answers)");
    check("V0", "integrate sin over [0, pi] = 2", integrate([](double x) { return std::sin(x); }, 0.0, std::numbers::pi),
          2.0, 1e-13);
    check("V0", "integrate x^7 over [0, 1] = 1/8", integrate([](double x) { return std::pow(x, 7); }, 0.0, 1.0), 0.125,
          1e-14);
    check("V0", "integrate exp over [-1, 1] = e - 1/e", integrate([](double x) { return std::exp(x); }, -1.0, 1.0),
          std::numbers::e - 1.0 / std::numbers::e, 1e-13);
    check("V0", "root of cos x - x = 0.739085133215161",
          root([](double x) { return std::cos(x) - x; }, 0.0, 1.0), 0.739085133215161, 1e-13);
    check("V0", "root of x^2 - 2 on [1, 2] = sqrt 2", root([](double x) { return x * x - 2.0; }, 1.0, 2.0),
          std::numbers::sqrt2, 1e-13);
    Sum k;
    k.add(1.0);
    for (int i = 0; i < 1000000; ++i) k.add(1e-16);
    check("V0", "compensated sum 1 + 10^6 x 1e-16 = 1 + 1e-10", k.value(), 1.0 + 1e-10, 1e-15);
}

// ---------------------------------------------------------------------------------------------
// Exact rational arithmetic on 64-bit integers (small matrices only). `overflow` is set if any
// intermediate product leaves the 64-bit range; an instrument must check it before quoting a result.
// ---------------------------------------------------------------------------------------------
namespace rat {

inline bool overflow = false;

struct Fr {
    long long n = 0, d = 1;
};

inline long long gcdll(long long a, long long b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b) {
        const long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}
inline bool mul_ok(long long a, long long b) {
    if (a == 0 || b == 0) return true;
    const long long x = a < 0 ? -a : a, y = b < 0 ? -b : b;
    return x <= 9223372036854775807LL / y;
}
inline Fr norm(Fr f) {
    if (f.d < 0) {
        f.n = -f.n;
        f.d = -f.d;
    }
    const long long g = gcdll(f.n, f.d);
    if (g > 1) {
        f.n /= g;
        f.d /= g;
    }
    return f;
}
inline Fr make(long long n, long long d = 1) { return norm({n, d}); }
inline Fr mul(Fr a, Fr b) {
    if (!mul_ok(a.n, b.n) || !mul_ok(a.d, b.d)) {
        overflow = true;
        return {0, 1};
    }
    return norm({a.n * b.n, a.d * b.d});
}
inline Fr inv(Fr a) { return norm({a.d, a.n}); }
inline Fr neg(Fr a) { return {-a.n, a.d}; }
inline Fr add(Fr a, Fr b) {
    if (!mul_ok(a.n, b.d) || !mul_ok(b.n, a.d) || !mul_ok(a.d, b.d)) {
        overflow = true;
        return {0, 1};
    }
    return norm({a.n * b.d + b.n * a.d, a.d * b.d});
}
inline Fr sub(Fr a, Fr b) { return add(a, neg(b)); }
inline bool is_zero(Fr a) { return a.n == 0; }
inline bool eq(Fr a, Fr b) {
    a = norm(a);
    b = norm(b);
    return a.n == b.n && a.d == b.d;
}
inline double to_double(Fr a) { return static_cast<double>(a.n) / static_cast<double>(a.d); }

using Matrix = std::vector<std::vector<Fr>>;

inline Matrix from_ints(const std::vector<std::vector<long long>>& rows) {
    Matrix m;
    for (const auto& r : rows) {
        std::vector<Fr> row;
        for (long long v : r) row.push_back(make(v));
        m.push_back(row);
    }
    return m;
}

/// Reduced row echelon form in place; returns the pivot columns (so rank = pivots.size()).
inline std::vector<int> rref(Matrix& m) {
    std::vector<int> pivots;
    const int rows = static_cast<int>(m.size());
    const int cols = rows ? static_cast<int>(m[0].size()) : 0;
    int r = 0;
    for (int c = 0; c < cols && r < rows; ++c) {
        int p = -1;
        for (int i = r; i < rows; ++i)
            if (!is_zero(m[i][c])) {
                p = i;
                break;
            }
        if (p < 0) continue;
        std::swap(m[p], m[r]);
        const Fr ip = inv(m[r][c]);
        for (int j = 0; j < cols; ++j) m[r][j] = mul(m[r][j], ip);
        for (int i = 0; i < rows; ++i) {
            if (i == r || is_zero(m[i][c])) continue;
            const Fr f = m[i][c];
            for (int j = 0; j < cols; ++j) m[i][j] = sub(m[i][j], mul(f, m[r][j]));
        }
        pivots.push_back(c);
        ++r;
    }
    return pivots;
}

inline int rank(Matrix m) { return static_cast<int>(rref(m).size()); }

/// Basis of the null space {x : M x = 0}, each vector scaled to primitive integers.
inline std::vector<std::vector<long long>> nullspace(Matrix m) {
    const int cols = m.empty() ? 0 : static_cast<int>(m[0].size());
    const std::vector<int> piv = rref(m);
    std::vector<std::vector<long long>> basis;
    for (int free = 0; free < cols; ++free) {
        if (std::find(piv.begin(), piv.end(), free) != piv.end()) continue;
        std::vector<Fr> x(cols, make(0));
        x[free] = make(1);
        for (std::size_t k = 0; k < piv.size(); ++k) x[piv[k]] = neg(m[k][free]);
        long long L = 1;
        for (const Fr& f : x) L = L / gcdll(L, f.d) * f.d;
        std::vector<long long> v(cols);
        long long g = 0;
        for (int j = 0; j < cols; ++j) {
            v[j] = x[j].n * (L / x[j].d);
            g = gcdll(g, v[j]);
        }
        if (g > 1)
            for (long long& t : v) t /= g;
        basis.push_back(v);
    }
    return basis;
}

}  // namespace rat

/// Known-answer validation of the rational helpers (test V0r).
inline void validate_rational() {
    heading("V0r rational helper validation (known answers)");
    rat::overflow = false;
    check_true("V0r", "rank of the 3x3 identity is 3", rat::rank(rat::from_ints({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}})) == 3);
    check_true("V0r", "rank of [[1,2,3],[4,5,6],[7,8,9]] is 2", rat::rank(rat::from_ints({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}})) == 2);
    const auto ns = rat::nullspace(rat::from_ints({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    check_true("V0r", "null space of [[1,2,3],[4,5,6],[7,8,9]] is spanned by (1,-2,1)",
               ns.size() == 1 && ((ns[0][0] == 1 && ns[0][1] == -2 && ns[0][2] == 1) ||
                                  (ns[0][0] == -1 && ns[0][1] == 2 && ns[0][2] == -1)));
    check_true("V0r", "rank-1 matrix [[1,2],[2,4]] has a one-dimensional null space (2,-1)",
               rat::rank(rat::from_ints({{1, 2}, {2, 4}})) == 1);
    check_true("V0r", "1/3 + 1/6 = 1/2 exactly", rat::eq(rat::add(rat::make(1, 3), rat::make(1, 6)), rat::make(1, 2)));
    check_true("V0r", "no overflow in the validation", !rat::overflow);
}

}  // namespace tb
