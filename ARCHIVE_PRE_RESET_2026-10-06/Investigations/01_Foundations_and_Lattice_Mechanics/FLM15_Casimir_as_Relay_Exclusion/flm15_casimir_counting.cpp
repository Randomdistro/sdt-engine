// FLM15 — Casimir pressure from gap-mode counting between ideal plates.
// Pre-registration: PROMPT.md, section "Pre-registration (2026-10-03)".
// Build: cl /std:c++20 /EHsc /O2 /I Engine\include flm15_casimir_counting.cpp
#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <vector>

namespace {
namespace m = sdt::laws::measured;
constexpr double pi = 3.14159265358979323846;
const double hbar_c = m::hbar * m::c;

bool near(double a, double b, double rel) { return std::fabs(a - b) <= rel * std::fabs(b); }

// Composite Simpson on [a,b] with n (even) intervals.
template <class F> double simpson(F f, double a, double b, int n) {
    const double h = (b - a) / n;
    double s = f(a) + f(b);
    for (int i = 1; i < n; ++i) s += f(a + i * h) * (i % 2 ? 4.0 : 2.0);
    return s * h / 3.0;
}

// Per-area scale-free energy kernel: g(q) = (1/2pi) * integral_q^inf s^2 exp(-lambda s) ds.
double g_closed(double q, double lam) {
    return std::exp(-lam * q) * (q * q / lam + 2.0 * q / (lam * lam) + 2.0 / (lam * lam * lam)) / (2.0 * pi);
}

// Kahan-compensated sum of g over n = -N..N.
double sum_modes(double d, double lam, double cut = 60.0) {
    const int N = static_cast<int>(cut * d / (pi * lam)) + 2;
    double s = 0.0, comp = 0.0;
    for (int n = -N; n <= N; ++n) {
        const double term = g_closed(std::fabs(n) * pi / d, lam);
        const double y = term - comp;
        const double t = s + y;
        comp = (t - s) - y;
        s = t;
    }
    return s;
}

// Free-space counting over the same region: integral dn g = 6 d / (pi^2 lambda^4), exact.
double free_modes(double d, double lam) { return 6.0 * d / (pi * pi * lam * lam * lam * lam); }

// D(lambda; d) = [sum - integral] in units of hbar*c per unit price a; dimensionally D = Dhat(lam/d)/d^3.
double D_energy(double d, double lam) { return sum_modes(d, lam) - free_modes(d, lam); }

// Cancellation-free second route: Poisson-dual series of the same sum-minus-integral.
// D = (4d/pi^2) * sum_{k>=1} (3 lam^2 - b^2)/(lam^2 + b^2)^3, b = 2 k d.  (lam -> 0 gives -pi^2/(360 d^3).)
double D_dual(double d, double lam, int K = 200000) {
    double s = 0.0;
    for (int k = K; k >= 1; --k) {
        const double b = 2.0 * k * d, l2 = lam * lam, b2 = b * b;
        s += (3.0 * l2 - b2) / std::pow(l2 + b2, 3);
    }
    return 4.0 * d / (pi * pi) * s;
}

int validate() {
    int fail = 0;
    auto check = [&](const char* what, bool ok) {
        std::printf("  [%s] %s\n", ok ? "ok" : "FAIL", what);
        if (!ok) ++fail;
    };
    std::printf("INSTRUMENT VALIDATION (known answers; physics rounds not yet run)\n");
    for (double t : {0.7, 1.3}) {
        double lhs = 0.0, rhs = 0.0;
        for (int n = -60; n <= 60; ++n) lhs += std::exp(-pi * n * n * t);
        for (int k = -60; k <= 60; ++k) rhs += std::exp(-pi * k * k / t);
        rhs /= std::sqrt(t);
        char buf[96];
        std::snprintf(buf, sizeof buf, "V1 Poisson summation at t=%.1f: %.15f vs %.15f", t, lhs, rhs);
        check(buf, near(lhs, rhs, 1e-13));
    }
    for (double q : {0.0, 2.0, 7.5}) {
        const double lam = 0.5;
        const double quad = simpson([&](double s) { return s * s * std::exp(-lam * s); }, q, q + 120.0 / lam, 400000) / (2.0 * pi);
        char buf[96];
        std::snprintf(buf, sizeof buf, "V2 g(q=%.1f) closed %.12g vs quadrature %.12g", q, g_closed(q, lam), quad);
        check(buf, near(g_closed(q, lam), quad, 1e-9));
    }
    {
        const double quad = simpson([](double s) { return s < 1e-12 ? 0.0 : s * s * s / std::expm1(s); }, 0.0, 80.0, 800000);
        const double exact = std::pow(pi, 4) / 15.0;
        char buf[96];
        std::snprintf(buf, sizeof buf, "V3 Bose integral %.12g vs pi^4/15 %.12g", quad, exact);
        check(buf, near(quad, exact, 1e-8));
    }
    for (double r : {0.3, 0.1, 0.05}) {
        const double a = D_energy(1.0, r), b = D_dual(1.0, r);
        char buf[112];
        std::snprintf(buf, sizeof buf, "V4 direct sum-minus-integral vs Poisson-dual series at lam/d=%.2f: %.12f vs %.12f", r, a, b);
        check(buf, near(a, b, 1e-8));
    }
    return fail;
}

// Round 1: counted occupation at T_CMB, free energy per mode kT ln(1 - e^{-s/sT}).
void round1() {
    const double kT = m::k_B * m::T_CMB;
    const double sT = kT / hbar_c;  // thermal wavenumber [1/m]
    std::printf("\nROUND 1 - literal seed: counted occupation at T_CMB = %.4f K, price eps = h nu\n", m::T_CMB);
    std::printf("kT = %.4e J = %.4e eV; thermal wavenumber s_T = %.4e 1/m (thermal wavelength 2pi/s_T = %.3e m)\n",
                kT, kT / 1.602176634e-19, sT, 2.0 * pi / sT);

    // d-independent n=0 mode and the free-space reference, by quadrature.
    const double G0 = simpson([&](double x) { return x < 1e-12 ? 0.0 : x * std::log(-std::expm1(-x)); }, 0.0, 80.0, 800000) * sT * sT / (2.0 * pi);
    const double Gint = simpson([&](double x) { return x < 1e-12 ? 0.0 : x * x * std::log(-std::expm1(-x)); }, 0.0, 80.0, 800000) * sT * sT * sT / (2.0 * pi);
    const double f_free_num = (2.0 * kT / pi) * Gint;                       // free energy per volume, J/m^3
    const double f_free_ana = -(pi * pi / 45.0) * std::pow(kT, 4) / std::pow(hbar_c, 3);
    std::printf("free-space free-energy density: quadrature %.6e, analytic -(pi^2/45)(kT)^4/(hc)^3 %.6e (agree %s)\n",
                f_free_num, f_free_ana, near(f_free_num, f_free_ana, 1e-8) ? "to 1e-8" : "NO");
    std::printf("n=0 mode free energy per area (d-independent): %.4e J/m^2\n", kT * G0);

    std::printf("\n%8s %12s %14s %14s %12s %16s\n", "d (um)", "mode n=1 s/sT", "log10 |occup.|", "|P| (Pa)", "P_ideal (Pa)", "|P|/P_ideal");
    std::vector<double> ds = {0.1e-6, 0.5e-6, 1.0e-6, 3.0e-6, 6.0e-6}, lnd, lnP;
    for (double d : ds) {
        const double q1 = pi / d;
        const double log10_occ = -(q1 / sT) / std::log(10.0);        // n=1 mode occupation e^{-q/sT}
        const double P = -f_free_num;                                 // magnitude; gap terms n>=1 contribute < 10^{log10_occ}
        const double Pid = pi * pi * hbar_c / (240.0 * std::pow(d, 4));
        std::printf("%8.2f %12.3e %14.1f %14.4e %12.4e %16.3e\n", d * 1e6, q1 / sT, log10_occ, P, Pid, P / Pid);
        lnd.push_back(std::log(d));
        lnP.push_back(std::log(P));
    }
    double sxx = 0, sxy = 0, mx = 0, my = 0;
    for (size_t i = 0; i < lnd.size(); ++i) { mx += lnd[i]; my += lnP[i]; }
    mx /= lnd.size(); my /= lnP.size();
    for (size_t i = 0; i < lnd.size(); ++i) { sxx += (lnd[i] - mx) * (lnd[i] - mx); sxy += (lnd[i] - mx) * (lnP[i] - my); }
    const double slope = sxy / sxx;
    const double uCMB3 = (pi * pi / 45.0) * std::pow(kT, 4) / std::pow(hbar_c, 3);
    std::printf("\nfitted exponent: P ~ d^%.6f   (registered prediction: 0 +/- 0.001)\n", slope);
    std::printf("|P| = %.4e Pa vs registered u_CMB/3 = %.4e Pa\n", -f_free_num, uCMB3);
    const bool coeff_met = std::fabs(slope - (-4.0)) > 0.0;   // exponent != -4 for every d
    std::printf("rejection criterion (exponent != 4 or coefficient outside +/-5%% of pi^2 hbar c/240): %s\n",
                coeff_met ? "MET" : "not met");
}

// Round 2: scale-free price a*hbar*omega per mode, exponential regulator, Richardson to lambda->0.
void round2() {
    std::printf("\nROUND 2 - scale-free floor: price a*hbar*omega per mode (a independent of omega)\n");
    const double target = -pi * pi / 360.0;  // per unit a, in hbar*c/d^3
    const double ratios[] = {0.08, 0.06, 0.04, 0.03, 0.02};
    std::vector<double> x, y;
    std::printf("%8s %20s %20s %12s\n", "lam/d", "D direct sum [hbar c/d^3]", "D dual series", "D - target");
    for (double r : ratios) {
        const double D = D_energy(1.0, r);
        std::printf("%8.3f %20.12f %20.12f %12.3e\n", r, D, D_dual(1.0, r), D - target);
        x.push_back(r * r);   // error series is in lam^2 (odd q-powers of g: -q^3/3 - lam^2 q^5/10 - ...)
        y.push_back(D);
    }
    // Neville extrapolation of D(x) to x = 0 with x = (lam/d)^2.
    const int n = static_cast<int>(x.size());
    std::vector<std::vector<double>> P(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) P[i][0] = y[i];
    for (int j = 1; j < n; ++j)
        for (int i = 0; i + j < n; ++i)
            P[i][j] = (x[i + j] * P[i][j - 1] - x[i] * P[i + 1][j - 1]) / (x[i + j] - x[i]);
    const double D0 = P[0][n - 1];
    const double D0_lower = P[1][n - 2];
    std::printf("extrapolated D(0) = %.12f  (order-%d), order-%d: %.12f;  -pi^2/360 = %.12f\n", D0, n - 1, n - 2, D0_lower, target);
    const double rel = std::fabs(D0 - target) / std::fabs(target);
    std::printf("relative departure from -pi^2/360: %.3e   (registered instrument gate 1e-6): %s\n", rel, rel <= 1e-6 ? "inside" : "OUTSIDE");

    // Pressure per unit a and the coefficient table.
    std::printf("\nP = -a * pi^2 hbar c /(120 d^4) per the extrapolated energy; coefficient relative to the ideal-plate value pi^2 hbar c/240:\n");
    for (double a : {0.25, 0.5, 1.0}) std::printf("  a = %.2f  ->  P/P_ideal = %.3f\n", a, 2.0 * a);
    std::printf("exponent from the scale-free premise: 4 exactly (energy per area scales as d^-3 for a price independent of omega);\n");
    std::printf("a price proportional to omega^(1+s) scales as d^-(4+s) by dimensional analysis.\n");

    // Finite-cutoff report: plate transparency near the skin depth of gold (~22 nm).
    const double lam_p = 22e-9;
    std::printf("\nreport-only: local exponent with a physical cutoff lambda = %.0f nm (skin-depth scale), a = 1/2\n", lam_p * 1e9);
    std::printf("%8s %14s %14s\n", "d (um)", "|P| (Pa)", "n_eff");
    for (double d : {0.1e-6, 0.3e-6, 1.0e-6, 3.0e-6}) {
        auto E = [&](double dd) { return 0.5 * hbar_c * (D_dual(dd, lam_p)); };  // J/m^2, cancellation-free route
        const double h = d * 1e-4;
        const double P = -(E(d + h) - E(d - h)) / (2.0 * h);   // force per area, positive = attractive when dE/dd > 0
        const double Pm = std::fabs(P);
        const double P2 = std::fabs((E(d * 1.01 + h) - E(d * 1.01 - h)) / (2.0 * h));
        const double neff = -(std::log(P2) - std::log(Pm)) / std::log(1.01);
        std::printf("%8.2f %14.4e %14.4f\n", d * 1e6, Pm, neff);
    }

    // Floor energy density if extended only to the plates' transparency frequency vs Law I.
    const double nu_p = 3e15;
    const double u_floor = pi * m::h * std::pow(nu_p, 4) / std::pow(m::c, 3);
    std::printf("\nreport-only: a=1/2 floor up to nu_p = %.1e Hz has energy density pi h nu^4/c^3 = %.3e J/m^3;\n", nu_p, u_floor);
    std::printf("Law I P_conv = %.3e Pa; ratio floor/P_conv = %.3e\n", sdt::laws::law_I::P_conv, u_floor / sdt::laws::law_I::P_conv);
}
}  // namespace

int main() {
    std::printf("FLM15 Casimir pressure from gap-mode counting\n");
    std::printf("pre-registration: PROMPT.md (2026-10-03)\n\n");
    if (validate() != 0) {
        std::printf("\nVALIDATION FAILED: instrument fault, no result reported.\n");
        return 2;
    }
    std::printf("VALIDATION PASS\n");
    round1();
    round2();
    return 0;
}
