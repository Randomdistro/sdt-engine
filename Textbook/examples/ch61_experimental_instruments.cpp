// Chapter 61 — experimental instruments: worked-example instrument (constructed apparatus; no measured input).
// Pre-registration: Textbook/validation/ch61_PRE_REGISTRATION.md (registered before this file existed).
#include "tb_common.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <numbers>
#include <random>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

constexpr double PI = std::numbers::pi;

// ---- SHA-256 (same routine as Chapter 57) -------------------------------------------------------
uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
std::string sha256(const std::string& msg) {
    static const uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe,
        0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
        0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    uint32_t h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    std::string m = msg;
    const uint64_t bitlen = static_cast<uint64_t>(msg.size()) * 8ULL;
    m.push_back(static_cast<char>(0x80));
    while (m.size() % 64 != 56) m.push_back(0);
    for (int i = 7; i >= 0; --i) m.push_back(static_cast<char>((bitlen >> (8 * i)) & 0xff));
    for (size_t off = 0; off < m.size(); off += 64) {
        uint32_t w[64];
        for (int i = 0; i < 16; ++i)
            w[i] = (static_cast<uint32_t>(static_cast<unsigned char>(m[off + 4 * i])) << 24) | (static_cast<uint32_t>(static_cast<unsigned char>(m[off + 4 * i + 1])) << 16) |
                   (static_cast<uint32_t>(static_cast<unsigned char>(m[off + 4 * i + 2])) << 8) | static_cast<uint32_t>(static_cast<unsigned char>(m[off + 4 * i + 3]));
        for (int i = 16; i < 64; ++i) {
            const uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3), s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], hh = h[7];
        for (int i = 0; i < 64; ++i) {
            const uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25), ch = (e & f) ^ (~e & g), t1 = hh + S1 + ch + K[i] + w[i];
            const uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22), mj = (a & b) ^ (a & c) ^ (b & c), t2 = S0 + mj;
            hh = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
    }
    char buf[65];
    for (int i = 0; i < 8; ++i) std::snprintf(buf + 8 * i, 9, "%08x", h[i]);
    return std::string(buf, 64);
}

// ---- small dense least squares via normal equations (Gaussian elimination), n columns --------
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
Mat inverse(const Mat& A) {
    const int n = static_cast<int>(A.size());
    Mat inv(n, std::vector<double>(n, 0.0));
    for (int j = 0; j < n; ++j) {
        std::vector<double> e(n, 0.0);
        e[j] = 1.0;
        const auto col = solve(A, e);
        for (int i = 0; i < n; ++i) inv[i][j] = col[i];
    }
    return inv;
}
struct Fit {
    std::vector<double> coef;
    Mat XtXinv;
};
Fit lsq(const std::vector<std::vector<double>>& X, const std::vector<double>& y) {
    const int m = static_cast<int>(X.size()), n = static_cast<int>(X[0].size());
    Mat A(n, std::vector<double>(n, 0.0));
    std::vector<double> b(n, 0.0);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            b[j] += X[i][j] * y[i];
            for (int k = 0; k < n; ++k) A[j][k] += X[i][j] * X[i][k];
        }
    return {solve(A, b), inverse(A)};
}

// ---- RK4 torsion pendulum -------------------------------------------------------------------
struct Resp {
    double amp, lag;
};
Resp driven(double r, double Q, double dt, double tmax) {
    const double I = 1.0, kap = 1.0, w0 = 1.0, gam = I * w0 / Q, w = r * w0;
    double th = 0.0, om = 0.0, t = 0.0;
    auto f = [&](double tt, double x, double v, double& dx, double& dv) { dx = v; dv = (std::sin(w * tt) - gam * v - kap * x) / I; };
    const double period = 2.0 * PI / w;
    const long steps_per_period = static_cast<long>(std::ceil(period / dt));
    dt = period / static_cast<double>(steps_per_period);                       // run 2: an integer number of steps per period
    const long nsteps = static_cast<long>(std::ceil(tmax / period)) * steps_per_period;  // settling: a whole number of periods
    const long nper = 10 * steps_per_period;                                   // the extraction window: exactly 10 periods
    double sc = 0.0, ss = 0.0;
    for (long i = 0; i < nsteps + nper; ++i) {
        double k1x, k1v, k2x, k2v, k3x, k3v, k4x, k4v;
        f(t, th, om, k1x, k1v);
        f(t + 0.5 * dt, th + 0.5 * dt * k1x, om + 0.5 * dt * k1v, k2x, k2v);
        f(t + 0.5 * dt, th + 0.5 * dt * k2x, om + 0.5 * dt * k2v, k3x, k3v);
        f(t + dt, th + dt * k3x, om + dt * k3v, k4x, k4v);
        th += dt * (k1x + 2 * k2x + 2 * k3x + k4x) / 6.0;
        om += dt * (k1v + 2 * k2v + 2 * k3v + k4v) / 6.0;
        t += dt;
        if (i >= nsteps) { sc += th * std::cos(w * t) * dt; ss += th * std::sin(w * t) * dt; }
    }
    const double T = nper * dt;
    const double a_s = 2.0 * ss / T, a_c = 2.0 * sc / T;  // theta = a_s sin(wt) + a_c cos(wt) = A sin(wt - lag)
    return {std::hypot(a_s, a_c), std::atan2(-a_c, a_s)};
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    tb::check_true("V1", "SHA-256(\"abc\")", sha256("abc") == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    {
        std::vector<std::vector<double>> X;
        std::vector<double> y;
        for (int i = 0; i < 5; ++i) { X.push_back({1.0, static_cast<double>(i)}); y.push_back(2.0 - 3.0 * i); }
        const auto f = lsq(X, y);
        tb::check("V1", "least squares recovers c0 = 2", f.coef[0], 2.0, 1e-12);
        tb::check("V1", "least squares recovers c1 = -3", f.coef[1], -3.0, 1e-12);
        double th = 1.0, om = 0.0;
        const int n = 20000;
        const double dt = 2.0 * PI / n;
        for (int i = 0; i < n; ++i) {
            auto a = [](double x) { return -x; };
            const double k1x = om, k1v = a(th);
            const double k2x = om + 0.5 * dt * k1v, k2v = a(th + 0.5 * dt * k1x);
            const double k3x = om + 0.5 * dt * k2v, k3v = a(th + 0.5 * dt * k2x);
            const double k4x = om + dt * k3v, k4v = a(th + dt * k3x);
            th += dt * (k1x + 2 * k2x + 2 * k3x + k4x) / 6.0;
            om += dt * (k1v + 2 * k2v + 2 * k3v + k4v) / 6.0;
        }
        tb::check("V1", "RK4: theta(2 pi) = 1 for theta'' = -theta", th, 1.0, 1e-10);
    }

    tb::heading("T1 torsion response: the quasistatic relation and its limit");
    {
        const double Q = 50.0;
        for (double r : {0.01, 0.03, 0.1, 0.5, 0.9, 1.0, 2.0}) {
            const Resp a = driven(r, Q, 0.01, 3000.0);
            const double ampf = 1.0 / std::sqrt((1.0 - r * r) * (1.0 - r * r) + (r / Q) * (r / Q));
            const double lagf = std::atan2(r / Q, 1.0 - r * r);
            char lab[128];
            std::snprintf(lab, sizeof lab, "r = %g: amplitude kappa A / tau0 = %.6f (closed form)", r, ampf);
            tb::check("T1", lab, a.amp, ampf, 1e-5);
            std::snprintf(lab, sizeof lab, "r = %g: lag = %.6f rad (closed form)", r, lagf);
            tb::check("T1", lab, a.lag, lagf, 1e-5, false);
            if (r == 0.1) tb::check_true("T1", "the quasistatic error at r = 0.1 lies in [0.0095, 0.0107]", a.amp - 1.0 >= 0.0095 && a.amp - 1.0 <= 0.0107);
            if (r == 0.03) tb::check_true("T1", "the quasistatic error at r = 0.03 is below 1e-3", std::fabs(a.amp - 1.0) < 1e-3);
            if (r == 1.0) {
                tb::check_true("T1", "the resonance amplitude is 50 +/- 0.5", std::fabs(a.amp - 50.0) <= 0.5);
                tb::check("T1", "the resonance lag is pi/2", a.lag, PI / 2.0, 1e-4);
            }
        }
    }

    tb::heading("T2 harmonic controls over integer turns");
    {
        const int N = 4, M = 3600;
        auto project = [&](double A, double B, double d, double sign, double turns) {
            // signal s(phi) = A cos 2phi + B sin 2phi + d t with phi = sign * Omega t (Omega = 1); sampled uniformly in time
            double sc = 0.0, ss = 0.0;
            const int m = static_cast<int>(M * turns / N);
            const double T = 2.0 * PI * turns;
            for (int i = 0; i < m; ++i) {
                const double t = (i + 0.5) * T / m, phi = sign * t;
                const double s = A * std::cos(2 * phi) + B * std::sin(2 * phi) + d * t;
                sc += s * std::cos(2 * phi);
                ss += s * std::sin(2 * phi);
            }
            return std::array<double, 2>{2.0 * sc / m, 2.0 * ss / m};
        };
        const auto fw = project(0.7, 0.3, 0.05, +1.0, N);
        const auto rv = project(0.7, 0.3, 0.05, -1.0, N);
        tb::note("forward: cos2phi %.9f, sin2phi %.9f ; reversed: cos2phi %.9f, sin2phi %.9f", fw[0], fw[1], rv[0], rv[1]);
        tb::check("T2", "forward projection on cos 2phi is 0.7 (the drift does not leak)", fw[0], 0.7, 1e-6);
        tb::check("T2", "forward projection on sin 2phi is 0.3 - 0.05 = 0.25", fw[1], 0.25, 1e-5);
        // run 2: the projection of the reversed run onto sin 2phi(t) with phi = -t is already the projection in apparatus angle
        const double sin_rev = rv[1];
        tb::check("T2", "reversed run in apparatus angle: 0.3 + 0.05 = 0.35", sin_rev, 0.35, 1e-5);
        tb::check("T2", "half the sum recovers the geometric signal 0.3", 0.5 * (fw[1] + sin_rev), 0.3, 1e-5);
        tb::check("T2", "half the difference isolates the drift 0.05", 0.5 * (sin_rev - fw[1]), 0.05, 1e-5);
        const auto part = project(0.0, 0.0, 0.05, +1.0, 3.5);
        tb::note("drift projection on cos 2phi over 3.5 turns: %.6e", part[0]);
        tb::note("RECORDED REJECTION (run 1 criterion kept): 3.5 turns is 7 pi, an integer number of periods of cos 2phi");
        tb::check_true("T2", "the registered statement (over 3.5 turns the drift projects on cos 2phi by more than 1e-3) is rejected", !(std::fabs(part[0]) > 1e-3));
        const auto part33 = project(0.0, 0.0, 0.05, +1.0, 3.3);
        const double Tt = 2.0 * PI * 3.3;
        const double analytic = (2.0 * 0.05 / Tt) * (Tt * std::sin(2.0 * Tt) / 2.0 + (std::cos(2.0 * Tt) - 1.0) / 4.0);  // run 3: includes the T sin(2T)/2 term
        tb::note("POST-RUN clause: drift projection on cos 2phi over 3.3 turns: %.6e (analytic %.6e)", part33[0], analytic);
        tb::check_true("T2", "POST-RUN clause: over 3.3 turns the drift projects on cos 2phi by more than 1e-3 and matches the analytic value to 2 per cent", std::fabs(part33[0]) > 1e-3 && std::fabs(part33[0] / analytic - 1.0) < 0.02);
    }

    tb::heading("T3 blank runs quantify the apparatus response");
    {
        const int M = 3600, runs = 4000;
        std::mt19937_64 rng(20261110ULL);
        std::normal_distribution<double> G(0.0, 1.0);
        std::vector<double> blank, sig;
        for (int k = 0; k < runs; ++k) {
            double sb = 0.0, ssg = 0.0;
            for (int i = 0; i < M; ++i) {
                const double phi = 2.0 * PI * 4.0 * (i + 0.5) / M;
                const double n = G(rng);
                sb += n * std::cos(2 * phi);
                ssg += (0.1 * std::cos(2 * phi) + n) * std::cos(2 * phi);
            }
            blank.push_back(2.0 * sb / M);
            sig.push_back(2.0 * ssg / M);
        }
        double mean = 0.0, var = 0.0;
        for (double v : blank) mean += v;
        mean /= runs;
        for (double v : blank) var += (v - mean) * (v - mean);
        const double sd = std::sqrt(var / (runs - 1)), sA = std::sqrt(2.0 / M);
        int within = 0;
        for (double v : sig) if (std::fabs(v - 0.1) <= 5.0 * sA) ++within;
        tb::note("blank runs: standard deviation %.5f (sqrt(2/M) = %.5f) ; mean %.3e ; registered-signal runs within 5 sigma: %d of %d", sd, sA, mean, within, runs);
        tb::check_true("T3", "the blank standard deviation is within 5 per cent of sqrt(2/M)", std::fabs(sd / sA - 1.0) < 0.05);
        tb::check_true("T3", "the blank mean is within 3 sigma/sqrt(4000) of 0", std::fabs(mean) < 3.0 * sA / std::sqrt(static_cast<double>(runs)));
        tb::check_true("T3", "at least 99 per cent of signal runs lie within 5 sigma of the registered 0.1", within >= 0.99 * runs);
    }

    tb::heading("T4 data hashes and the covariance of the fit");
    {
        std::string blob(10000, 'x');
        for (size_t i = 0; i < blob.size(); ++i) blob[i] = static_cast<char>(33 + (i * 7) % 90);
        const auto h0 = sha256(blob);
        std::string b2 = blob;
        b2[5000] ^= 1;
        tb::check_true("T4", "an unchanged blob has an unchanged digest", sha256(blob) == h0);
        tb::check_true("T4", "a one-byte change changes the digest", sha256(b2) != h0);
        const int M = 3600;
        std::vector<std::vector<double>> X;
        for (int i = 0; i < M; ++i) {
            const double t = 2.0 * PI * 4.0 * (i + 0.5) / M;
            X.push_back({std::cos(2 * t), std::sin(2 * t), 1.0, t});
        }
        std::vector<double> y(M, 0.0);
        const auto f = lsq(X, y);
        const auto& C = f.XtXinv;
        const double rho_ct = C[0][3] / std::sqrt(C[0][0] * C[3][3]);
        const double rho_st = C[1][3] / std::sqrt(C[1][1] * C[3][3]);
        tb::note("rho(cos2phi, t) = %.3e ; rho(sin2phi, t) = %.4f ; [(X^T X)^-1]_00 = %.6e ; 2/M = %.6e", rho_ct, rho_st, C[0][0], 2.0 / M);
        tb::check("T4", "the cos 2phi coefficient is uncorrelated with the drift", rho_ct, 0.0, 1e-9, false);
        tb::note("RECORDED REJECTION (run 1 criterion kept): |rho(sin 2phi, t)| = %.4f (registered: in (0.3, 1))", std::fabs(rho_st));
        tb::check_true("T4", "the registered statement (|rho(sin 2phi, t)| in (0.3, 1)) is rejected", !(std::fabs(rho_st) > 0.3 && std::fabs(rho_st) < 1.0));
        tb::check_true("T4", "POST-RUN clause: the sin 2phi coefficient is correlated with the drift: 0.05 < |rho| < 0.2", std::fabs(rho_st) > 0.05 && std::fabs(rho_st) < 0.2);
        tb::check("T4", "the analytic standard-error factor sqrt(2/M) equals sqrt([(X^T X)^-1]_00)", std::sqrt(2.0 / M), std::sqrt(C[0][0]), 1e-6);
    }

    tb::heading("T5 the repository's apparatus folders");
    {
        const fs::path base = "Projects/sdt-investigations/Investigations";
        const fs::path g13 = base / "06_Gravitation_and_Orbital_Mechanics" / "GOM13_Occlusion_Altitude_Cavendish";
        const fs::path f15 = base / "01_Foundations_and_Lattice_Mechanics" / "FLM15_Casimir_as_Relay_Exclusion";
        tb::check_true("T5", "GOM13_Occlusion_Altitude_Cavendish exists", fs::is_directory(g13));
        tb::check_true("T5", "FLM15_Casimir_as_Relay_Exclusion exists", fs::is_directory(f15));
        tb::check_true("T5", "they are different directories", fs::weakly_canonical(g13) != fs::weakly_canonical(f15));
        tb::check_true("T5", "gom13_preflight.cpp is in the GOM13 folder", fs::exists(g13 / "gom13_preflight.cpp"));
    }

    return tb::finish();
}
