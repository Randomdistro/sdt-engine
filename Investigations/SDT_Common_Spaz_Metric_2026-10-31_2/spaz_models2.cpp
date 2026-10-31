// ============================================================================
//  spaz_models2.cpp — Common Spaz Metric run 2, workstreams W5, W6, W9
//  Author: James Christopher Tyndall, Melbourne.
//
//  W5  Exponent (Spaz) algebra for varying-c candidates. Each candidate gives
//      the exponents of N for the primitives {c, hbar, m, k_e e^2} in
//      far-frame units plus a transit rule; observables follow by algebra.
//      The constraint matrix from the observables is reduced to exact rank.
//  W6  Ground state per epoch and the release epoch by two routes
//      (E1/kT = 53 rule; full Saha x_e = 0.5).
//  W9  Depth rate law dN/dt = -H0 N^p with transit speed c0 N^-q, fitted in
//      shape to Pantheon+ (Datasets/cosmology), flat LCDM as comparator.
//
//  Build: g++ -std=c++20 -O2 -IEngine/include spaz_models2.cpp
//  Run:   ./a.out <path to PantheonPlusSH0ES.dat> <output dir>
// ============================================================================

#include <sdt/laws.hpp>

#include <array>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <numbers>
#include <sstream>
#include <string>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
namespace Br = sdt::laws::bridge;
constexpr double PI = std::numbers::pi;

// ── W5 ──────────────────────────────────────────────────────────────────────
// exponent vector over primitives {c, hbar, m, kee}
using Ex = std::array<double, 4>;
Ex operator+(Ex a, Ex b) { for (int i = 0; i < 4; ++i) a[i] += b[i]; return a; }
Ex operator*(double k, Ex a) { for (auto& x : a) x *= k; return a; }
constexpr Ex C{1, 0, 0, 0}, H{0, 1, 0, 0}, Mm{0, 0, 1, 0}, K{0, 0, 0, 1};

struct Candidate {
    const char* name;
    Ex prim;              // exponents of N for c, hbar, m, kee
    bool tick_transit;    // true: arrival rate = emission rate (frequency kept)
};

double dot(Ex a, Ex b) { double s = 0; for (int i = 0; i < 4; ++i) s += a[i] * b[i]; return s; }

void w5() {
    std::printf("\nW5  Spaz exponent algebra (exponent of N, far-frame units)\n");
    // derived combinations
    const Ex alpha = K + (-1.0) * H + (-1.0) * C;             // kee / (hbar c)
    const Ex nu    = 2.0 * K + Mm + (-3.0) * H;                // alpha^2 m c^2 / hbar
    const Ex a0    = H + (-1.0) * Mm + (-1.0) * C + (-1.0) * alpha;
    std::printf("  identity check: nu = alpha^2 m c^2/hbar -> 2*alpha + m + 2c - hbar = "
        "{%.0f %.0f %.0f %.0f} vs {%.0f %.0f %.0f %.0f}\n",
        (2.0 * alpha + Mm + 2.0 * C + (-1.0) * H)[0], (2.0 * alpha + Mm + 2.0 * C + (-1.0) * H)[1],
        (2.0 * alpha + Mm + 2.0 * C + (-1.0) * H)[2], (2.0 * alpha + Mm + 2.0 * C + (-1.0) * H)[3],
        nu[0], nu[1], nu[2], nu[3]);

    const Candidate cands[] = {
        {"A  ladder: c~N^-1, atoms fixed", {-1, 0, 0, 0}, true},
        {"B  c~N^-1, alpha fixed, m~N^2", {-1, 0, 2, -1}, true},
        {"C  hop-tick static, c~N^-2", {-2, 0, 3, -2}, true},
        {"D  emission-depth, c~N^-2 rising", {-2, 0, 3, -2}, true},
        {"A' ladder with wavelength kept", {-1, 0, 0, 0}, false},
    };
    std::printf("  %-34s %6s %6s %6s %6s %6s %6s %6s %6s\n", "candidate", "alpha",
        "nu", "a0", "c_loc", "1+z", "SN", "Shap", "beta");
    for (const auto& cd : cands) {
        const double ea = dot(alpha, cd.prim), en = dot(nu, cd.prim), er = dot(a0, cd.prim);
        const double ec = cd.prim[0];
        const double c_loc = ec - en - er;     // c x T_tick / L_ruler, T_tick ~ N^-en
        // observed line redshift: tick transit -> 1+z = nu_lab/nu_emit -> -en;
        // wavelength transit -> lambda_obs = c_e/nu_e -> ec - en
        const double ez = cd.tick_transit ? -en : ec - en;
        const double esn = cd.tick_transit ? -en : -en + ec;   // spacing as for crests
        const double shap = -ec;                                 // delay factor (2 = full)
        // CMB T(z) = T0 (1+z)^(1-beta): the bath arrives at T0; its far-frame frequency
        // at emission has exponent 0 (tick transit) or ec (wavelength kept); a local
        // thermometer divides by the local clock rate (exponent en)
        const double eTloc = (cd.tick_transit ? 0.0 : ec) - en;
        const bool zdef = std::abs(ez) > 1e-12;
        const double beta = zdef ? 1.0 - eTloc / ez : NAN;
        std::printf("  %-34s %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.2f\n",
            cd.name, ea, en, er, c_loc, ez, esn, shap, beta);
    }
    std::printf("  required: alpha 0 (quasar, Law V), 1+z 1, SN 1, Shapiro 2, beta 0.004+-0.016, c_loc 0\n");

    // rank of the constraint system on (c, hbar, m, kee)
    struct Row { const char* obs; Ex a; double rhs; };
    const Row rows[] = {
        {"Shapiro factor 2 (static)", C, -2},
        {"solar redshift z = koppa/R", nu, -1},
        {"alpha fixed (quasar)", alpha, 0},
        {"Law V k_H >= 1 (alpha <= 1)", alpha, 0},
        {"cosmological 1+z (tick transit)", nu, -1},
        {"SN stretch exponent 1", nu, -1},
        {"CMB T(z) beta = 0", nu, -1},
        {"Sirius B redshift", nu, -1},
    };
    constexpr int nr = sizeof(rows) / sizeof(rows[0]);
    double A[nr][5];
    for (int i = 0; i < nr; ++i) { for (int j = 0; j < 4; ++j) A[i][j] = rows[i].a[j]; A[i][4] = rows[i].rhs; }
    int rank = 0;
    for (int col = 0; col < 4 && rank < nr; ++col) {
        int piv = -1;
        for (int i = rank; i < nr; ++i) if (std::abs(A[i][col]) > 1e-12) { piv = i; break; }
        if (piv < 0) continue;
        for (int j = 0; j < 5; ++j) std::swap(A[rank][j], A[piv][j]);
        for (int i = 0; i < nr; ++i) if (i != rank) {
            const double f = A[i][col] / A[rank][col];
            for (int j = 0; j < 5; ++j) A[i][j] -= f * A[rank][j];
        }
        ++rank;
    }
    bool consistent = true;
    for (int i = rank; i < nr; ++i) if (std::abs(A[i][4]) > 1e-12) consistent = false;
    std::printf("  constraint system: %d observables, exact rank %d, unknowns 4 -> %d free "
        "exponent(s); consistent: %s\n", nr, rank, 4 - rank, consistent ? "yes" : "no");
    std::printf("  solution family (a = hbar exponent): c -2, hbar a, m 3+a, kee a-2\n");
    for (double a : {-2.0, -1.0, 0.0, 1.0}) {
        const Ex p{-2, a, 3 + a, a - 2};
        std::printf("    a=%+.0f: alpha %.1f  nu %.1f  a0 %.1f  a0/hop(hop~N^-1) %.1f  -> %s\n",
            a, dot(alpha, p), dot(nu, p), dot(a0, p), dot(a0, p) + 1.0,
            std::abs(dot(alpha, p)) < 1e-12 && std::abs(dot(a0, p) + 1.0) < 1e-12
                ? "pure unit change" : "physical change");
    }
    std::printf("  hop held fixed (physical widening): tick must carry N^-2 -> solar "
        "redshift 2 x koppa/R: excluded by C1\n");
}

// ── W6 ──────────────────────────────────────────────────────────────────────
double saha_x(double T, double eta) {
    const double kT = M::k_B * T;
    const double E = M::Ry_eV * M::eV_to_J;
    const double ngam = 2.0 * 1.2020569031595942 / (PI * PI)
        * std::pow(kT / (M::hbar * M::c), 3);
    const double nb = eta * ngam;
    const double S = std::pow(M::m_e * kT / (2 * PI * M::hbar * M::hbar), 1.5)
        * std::exp(-E / kT) / nb;                  // x^2/(1-x) = S
    return (-S + std::sqrt(S * S + 4 * S)) / 2;
}

void w6(const std::string& out) {
    std::printf("\nW6  Ground state per epoch and release epoch\n");
    const double eta = 6.1e-10;   // shared-input (CMB/BBN fits), stated
    // validation: textbook equilibrium x=0.5 near T ~ 3700-3800 K
    double lo = 2000, hi = 6000;
    for (int i = 0; i < 200; ++i) { const double m = 0.5 * (lo + hi); (saha_x(m, eta) < 0.5 ? lo : hi) = m; }
    const double T_half = 0.5 * (lo + hi);
    std::printf("  validation: Saha x_e=0.5 at T = %.1f K (textbook 3700-3800 K)\n", T_half);
    const double kT0 = M::k_B * M::T_CMB / M::eV_to_J;
    const double N53 = M::Ry_eV / (53.0 * kT0);
    const double Nsaha = T_half / M::T_CMB;
    std::printf("  route (i)  E1/kT = 53 rule        : N = %.1f\n", N53);
    std::printf("  route (ii) Saha x_e = 0.5 (eta %.1e): N = %.1f\n", eta, Nsaha);
    std::printf("  observed z* + 1 = 1090.92; Saha x_e at N=1090.92: %.3e; "
        "at N=1060.94: %.3e\n", saha_x(M::T_CMB * 1090.92, eta), saha_x(M::T_CMB * 1060.94, eta));
    std::printf("  routes differ by %.1f %%: release at N~1090 is NOT an equilibrium "
        "ionisation epoch; it needs a rate comparison (W9 rate law)\n",
        100.0 * (Nsaha / N53 - 1.0));
    for (double et : {3e-10, 6.1e-10, 1.2e-9}) {
        double l = 2000, h = 6000;
        for (int i = 0; i < 200; ++i) { const double m = 0.5 * (l + h); (saha_x(m, et) < 0.5 ? l : h) = m; }
        std::printf("    eta %.1e -> Saha half-ionisation N = %.1f\n", et, 0.5 * (l + h) / M::T_CMB);
    }
    std::ofstream f(out + "/ground_state_epoch2.csv");
    f << "N,E1_arrival_eV,Lya_arrival_nm,a0_far_rel,E1_over_kTbath,saha_xe\n";
    for (double lN = 0; lN <= std::log10(3000.0) + 1e-9; lN += 0.01) {
        const double N = std::pow(10.0, lN);
        f << N << ',' << M::Ry_eV / N << ',' << 121.567 * N << ',' << N << ','
          << M::Ry_eV / (kT0 * N) << ',' << saha_x(M::T_CMB * N, eta) << '\n';
    }
    std::printf("  table: E1 = 13.6057/N eV on arrival; local E1 = 13.6057 eV at every N\n");
    for (double N : {1.0, 137.036, 1060.94, 1090.92, Nsaha})
        std::printf("    N %8.2f  E1_arr %9.5f eV  Lya_arr %10.1f nm  E1/kT %9.2f  x_e %.3e\n",
            N, M::Ry_eV / N, 121.567 * N, M::Ry_eV / (kT0 * N), saha_x(M::T_CMB * N, eta));
}

// ── W9 ──────────────────────────────────────────────────────────────────────
struct SN { double z, m, s; };

std::vector<SN> load(const std::string& path) {
    std::ifstream f(path);
    std::string line;
    std::getline(f, line);
    std::vector<std::string> hdr;
    { std::istringstream h(line); std::string t; while (h >> t) hdr.push_back(t); }
    auto col = [&](const char* n) { for (size_t i = 0; i < hdr.size(); ++i) if (hdr[i] == n) return int(i); return -1; };
    const int iz = col("zHD"), im = col("m_b_corr"), is = col("m_b_corr_err_DIAG"), ic = col("IS_CALIBRATOR");
    std::vector<SN> v;
    while (std::getline(f, line)) {
        std::istringstream l(line); std::vector<std::string> t; std::string x;
        while (l >> x) t.push_back(x);
        if (int(t.size()) <= std::max({iz, im, is, ic})) continue;
        const double z = std::stod(t[iz]);
        if (z <= 0.01 || std::stoi(t[ic]) != 0) continue;
        v.push_back({z, std::stod(t[im]), std::stod(t[is])});
    }
    return v;
}

// dimensionless distance d H0/c for the rate-law family, shape s = p + q
double d_family(double N, double s) {
    if (std::abs(s - 1.0) < 1e-9) return std::log(N);
    return (std::pow(N, 1.0 - s) - 1.0) / (1.0 - s);
}

double d_lcdm(double z, double Om) {
    const int n = 400; double sum = 0;
    for (int i = 0; i < n; ++i) {
        const double zz = (i + 0.5) * z / n;
        sum += 1.0 / std::sqrt(Om * std::pow(1 + zz, 3) + 1 - Om);
    }
    return sum * z / n;
}

template <class F>
auto chi2(const std::vector<SN>& d, F dl) -> double {
    double sw = 0, swr = 0;
    std::vector<double> mu(d.size());
    for (size_t i = 0; i < d.size(); ++i) {
        mu[i] = 5 * std::log10(dl(d[i].z));
        const double w = 1 / (d[i].s * d[i].s);
        sw += w; swr += w * (d[i].m - mu[i]);
    }
    const double off = swr / sw;
    double c2 = 0;
    for (size_t i = 0; i < d.size(); ++i) {
        const double r = (d[i].m - mu[i] - off) / d[i].s;
        c2 += r * r;
    }
    return c2;
}

void w9(const std::string& path, const std::string& out) {
    std::printf("\nW9  Depth rate law, Pantheon+ shape fit (zHD > 0.01, non-calibrators, "
        "diagonal errors only)\n");
    // validation: numerical integral of n^-s vs closed form
    {
        const double s = 2.7, N = 3.0; const int n = 200000; double q = 0;
        for (int i = 0; i < n; ++i) q += std::pow(1 + (i + 0.5) * (N - 1) / n, -s);
        q *= (N - 1) / n;
        std::printf("  validation: distance integral numeric %.10f closed %.10f\n", q, d_family(N, s));
    }
    const auto d = load(path);
    std::printf("  supernovae used: %zu\n", d.size());
    double best_s = 0, best_c = 1e300;
    std::ofstream f(out + "/rate_law_chi2_2.csv");
    f << "s,chi2\n";
    for (double s = -1.0; s <= 4.0 + 1e-9; s += 0.005) {
        const double c = chi2(d, [&](double z) { return (1 + z) * d_family(1 + z, s); });
        f << s << ',' << c << '\n';
        if (c < best_c) { best_c = c; best_s = s; }
    }
    // 1-sigma interval on s
    double s_lo = best_s, s_hi = best_s;
    for (double s = best_s; s > -1; s -= 0.001)
        if (chi2(d, [&](double z) { return (1 + z) * d_family(1 + z, s); }) > best_c + 1) { s_lo = s; break; }
    for (double s = best_s; s < 4; s += 0.001)
        if (chi2(d, [&](double z) { return (1 + z) * d_family(1 + z, s); }) > best_c + 1) { s_hi = s; break; }
    double best_om = 0, best_cl = 1e300;
    for (double om = 0.0; om <= 1.0 + 1e-9; om += 0.002) {
        const double c = chi2(d, [&](double z) { return (1 + z) * d_lcdm(z, om); });
        if (c < best_cl) { best_cl = c; best_om = om; }
    }
    const double n = double(d.size());
    std::printf("  rate law  : s = p+q = %.3f (+%.3f/-%.3f)  chi2 = %.1f  BIC = %.1f   CALIBRATED(1)\n",
        best_s, s_hi - best_s, best_s - s_lo, best_c, best_c + 2 * std::log(n));
    std::printf("  flat LCDM : Om = %.3f                        chi2 = %.1f  BIC = %.1f   comparator\n",
        best_om, best_cl, best_cl + 2 * std::log(n));
    std::printf("  delta chi2 (rate law - LCDM) = %+.1f with equal parameter counts\n", best_c - best_cl);
    std::printf("  identifiability: distances fix only s = p + q. With q = 2 (full-Shapiro "
        "transit) p = %.3f; with q = 0, p = %.3f\n", best_s - 2, best_s);
    std::printf("  elapsed time N=1091 -> 1 in units of 1/H0, t = int dn / n^p:\n");
    for (double q : {0.0, 2.0}) {
        for (double s : {s_lo, best_s, s_hi}) {
            const double p = s - q;
            const double t = std::abs(p - 1) < 1e-9 ? std::log(1091.0)
                : (std::pow(1091.0, 1 - p) - 1) / (1 - p);
            std::printf("    q=%.0f s=%.3f p=%+.3f  t = %.4g / H0\n", q, s, p, t);
        }
    }
    // W6b: release epoch from the rate law. Local physics is unchanged under D,
    // local proper time is dt/N, so the Thomson optical depth from N back to 1 is
    //   tau(N) = int x_e n_b sigma_T c dN' / (H0 N'^(p+1)),
    // with x_e from Saha (equilibrium: every rate law here is slower than the
    // LCDM expansion rate at N ~ 1000). Release = tau reaching 1.
    std::printf("\n  W6b release epoch from the fitted rate law (tau_Thomson = 1, Saha x_e, "
        "eta 6.1e-10)\n");
    constexpr double sigma_T = 6.6524587321e-29;   // [m^2] Thomson cross-section (CODATA)
    constexpr double Mpc = 3.0856775814913673e22;
    for (double q : {2.0, 0.0}) {
        for (double H0k : {67.4, 70.0, 73.0}) {
            const double H0 = H0k * 1e3 / Mpc, p = best_s - q;
            double tau = 0, Nrel = 0;
            for (double N = 1.0; N < 3000.0 && Nrel == 0; N += 0.01) {
                const double T = M::T_CMB * N, kT = M::k_B * T;
                const double nb = 6.1e-10 * 2.0 * 1.2020569031595942 / (PI * PI)
                    * std::pow(kT / (M::hbar * M::c), 3);
                tau += saha_x(T, 6.1e-10) * nb * sigma_T * M::c * 0.01 / (H0 * std::pow(N, p + 1));
                if (tau >= 1.0) Nrel = N;
            }
            std::printf("    q=%.0f (p=%+.3f) H0=%.1f: release N = %.1f  (T_local %.0f K, x_e %.2e)\n",
                q, p, H0k, Nrel, M::T_CMB * Nrel, saha_x(M::T_CMB * Nrel, 6.1e-10));
        }
    }
    std::printf("    comparators: z*+1 = 1090.92, z_drag+1 = 1060.94 (Planck 2018, shared-input)\n");
    std::ofstream g(out + "/hubble_residuals2.csv");
    g << "z,m_minus_model_rate,m_minus_model_lcdm,sigma\n";
    auto offset = [&](auto dl) { double sw = 0, swr = 0;
        for (auto& x : d) { const double w = 1 / (x.s * x.s); sw += w; swr += w * (x.m - 5 * std::log10(dl(x.z))); }
        return swr / sw; };
    auto dr = [&](double z) { return (1 + z) * d_family(1 + z, best_s); };
    auto dc = [&](double z) { return (1 + z) * d_lcdm(z, best_om); };
    const double o1 = offset(dr), o2 = offset(dc);
    for (auto& x : d)
        g << x.z << ',' << x.m - 5 * std::log10(dr(x.z)) - o1 << ','
          << x.m - 5 * std::log10(dc(x.z)) - o2 << ',' << x.s << '\n';
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 3) { std::printf("usage: spaz_models2 <PantheonPlusSH0ES.dat> <outdir>\n"); return 1; }
    std::printf("spaz_models2 — Common Spaz Metric run 2 (W5 W6 W9)\n");
    w5();
    w6(argv[2]);
    w9(argv[1], argv[2]);
    return 0;
}
