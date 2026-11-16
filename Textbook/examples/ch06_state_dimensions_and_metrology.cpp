// Chapter 6 — state dimensions and metrology: worked-example instrument.
// Pre-registration: Textbook/validation/ch06_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch06_state_dimensions_and_metrology
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <fstream>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
constexpr double kPi = std::numbers::pi;

// ---- dimension algebra (exponents stored in half units so that square roots of lengths are representable) -------
struct Dim {
    int M = 0, L = 0, T = 0, K = 0;  // twice the exponent
};
Dim operator*(Dim a, Dim b) { return {a.M + b.M, a.L + b.L, a.T + b.T, a.K + b.K}; }
Dim operator/(Dim a, Dim b) { return {a.M - b.M, a.L - b.L, a.T - b.T, a.K - b.K}; }
Dim dpow(Dim a, int n) { return {a.M * n, a.L * n, a.T * n, a.K * n}; }
Dim dsqrt(Dim a) {
    if ((a.M | a.L | a.T | a.K) & 1) throw std::domain_error("square root of a half-integer exponent");
    return {a.M / 2, a.L / 2, a.T / 2, a.K / 2};
}
bool same(Dim a, Dim b) { return a.M == b.M && a.L == b.L && a.T == b.T && a.K == b.K; }

const Dim one{}, kg{2, 0, 0, 0}, m{0, 2, 0, 0}, s{0, 0, 2, 0}, Kel{0, 0, 0, 2};

struct Rel {
    const char* name;
    Dim lhs, rhs;
};

// ---- Wien and Planck helpers -----------------------------------------------------------------------------
double golden_max(const std::function<double(double)>& f, double a, double b) {
    const double g = (std::sqrt(5.0) - 1.0) / 2.0;
    double c = b - g * (b - a), d = a + g * (b - a);
    double fc = f(c), fd = f(d);
    for (int i = 0; i < 200; ++i) {
        if (fc > fd) {
            b = d; d = c; fd = fc; c = b - g * (b - a); fc = f(c);
        } else {
            a = c; c = d; fc = fd; d = a + g * (b - a); fd = f(d);
        }
    }
    return 0.5 * (a + b);
}

std::string slurp(const char* path) {
    std::ifstream in(path, std::ios::binary);
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

}  // namespace

int main() {
    namespace L = sdt::laws;
    tb::validate_helpers();
    tb::validate_rational();

    const double x3 = 2.821439372122079, x5 = 4.965114231744276;

    tb::heading("V1 Wien roots and maximiser");
    tb::check("V1", "root of (3-x)e^x = 3", tb::root([](double x) { return (3.0 - x) * std::exp(x) - 3.0; }, 1.0, 4.0), x3, 1e-12);
    tb::check("V1", "root of (5-x)e^x = 5", tb::root([](double x) { return (5.0 - x) * std::exp(x) - 5.0; }, 3.0, 6.0), x5, 1e-12);
    tb::check("V1", "golden-section maximum of x e^-x is 1", golden_max([](double x) { return x * std::exp(-x); }, 0.1, 5.0), 1.0, 1e-7);

    tb::heading("V2 dimension algebra");
    {
        const Dim accel = m / (s * s), force = kg * accel, pressure = force / (m * m);
        tb::check_true("V2", "force = M L T^-2", same(force, Dim{2, 2, -4, 0}));
        tb::check_true("V2", "pressure = M L^-1 T^-2", same(pressure, Dim{2, -2, -4, 0}));
        tb::check_true("V2", "sqrt(L^2) = L", same(dsqrt(m * m), m));
        tb::check_true("V2", "sqrt(L) is represented as the half-unit exponent L^(1/2)", same(dsqrt(m), Dim{0, 1, 0, 0}));
        bool threw = false;
        try { (void)dsqrt(dsqrt(m)); } catch (const std::domain_error&) { threw = true; }
        tb::check_true("V2", "sqrt of L^(1/2) is refused (a quarter exponent is not represented)", threw);
        tb::check_true("V2", "the checker reports L versus T as a mismatch", !same(m, s));
    }

    tb::heading("V3 Planck integral and the Wien displacement constant");
    const double planck_int = tb::integrate([](double x) { return x * x * x / std::expm1(x); }, 1e-12, 80.0, 48, 40);
    tb::check("V3", "int x^3/(e^x-1) dx over [0,80] = pi^4/15", planck_int, std::pow(kPi, 4) / 15.0, 1e-12);
    const double b_wien = M::h * M::c / (x5 * M::k_B);
    tb::check("V3", "Wien constant b = hc/(4.965114 k_B) vs 2.897771955e-3 m K", b_wien, 2.897771955e-3, 1e-9);

    // ----------------------------------------------------------------------------------------------------------
    tb::heading("T1 dimensional homogeneity of the relations of Chapters 1-9 and the seed relations");
    {
        const Dim speed = m / s, accel = m / (s * s), energy = kg * m * m / (s * s), force = kg * m / (s * s);
        const Dim pressure = force / (m * m), hbar = energy * s, kB = energy / Kel;
        const Dim aRad = energy / (m * m * m * Kel * Kel * Kel * Kel);
        const Dim Phi = energy, eps = energy, uD = pressure, Pconv = pressure, Vdisp = m * m * m, l3 = m * m * m;
        const std::vector<Rel> rels = {
            {"1.8  m c^2 = P_conv V_disp / 3", kg * speed * speed, Pconv * Vdisp},
            {"1.8' m = Phi V_disp / (3 l_P^3 c^2)", kg, Phi * Vdisp / (l3 * speed * speed)},
            {"4.5  Phi = N eps", Phi, one * eps},
            {"eps = u l_P^3", eps, uD * l3},
            {"u = a_rad T^4", uD, aRad * dpow(Kel, 4)},
            {"P_conv = Phi / l_P^3", Pconv, Phi / l3},
            {"R_p = 4 hbar / (m_p c)", m, hbar / (kg * speed)},
            {"V_disp = 3 m l_P^3 c^2 / Phi", Vdisp, kg * l3 * speed * speed / Phi},
            {"2.2  d^2 = (r2-r1)^2 + 4 r1 r2 sin^2", m * m, m * m},
            {"2.7  v_phi = rho dphi/dm", speed, m / s},
            {"2.9  beta_dot = c sqrt(Om) r^-3/2", one / s, speed * dsqrt(m) * dsqrt(dpow(m, -3))},
            {"v_circ = c sqrt(Om / r)", speed, speed * dsqrt(m / m)},
            {"Om = v^2 R / c^2", m, speed * speed * m / (speed * speed)},
            {"a = c^2 Om / r^2", accel, speed * speed * m / (m * m)},
            {"3.1  c_relay = P_l / P_t", speed, m / s},
            {"3.2  n_orb = 2 pi k r / l_P", one, one * m / m},
            {"3.3  Gamma = 2 pi c_b Om", m * m / s, speed * m},
            {"3.7  1/c_far - 1/c", s / m, one / speed},
            {"3.8  Delta = (2 Om / c) ln(...)", s, m / speed},
            {"4.13 |grad P| = P_conv / (3R)", pressure / m, Pconv / m},
            {"4.6  F = (kappa eps / l) <L n>", energy, energy / m * m},
            {"9.10 F = (pi/4) U R1^2 R2^2 / r^2", force, pressure * m * m * m * m / (m * m)},
            {"9.5  t_abs = U / 6", pressure, pressure},
            {"9.1  q = U / 4 pi per steradian", pressure, pressure * one},
            {"9.3  Pi_ij = oint phi n_i n_j dOmega", energy, energy * one},
            {"P_eff = 4 alpha hbar c / (pi R_p^2 r_e^2)", pressure, hbar * speed / (m * m * m * m)},
            {"r_e = alpha hbar / (m_e c)", m, hbar / (kg * speed)},
            {"a_0 = hbar / (alpha m_e c)", m, hbar / (kg * speed)},
            {"R_inf = alpha^2 m_e c / (2 h)", one / m, kg * speed / hbar},
            {"a_rad = 8 pi^5 k_B^4 / (15 h^3 c^3)", aRad, dpow(kB, 4) / (dpow(hbar, 3) * dpow(speed, 3))},
            {"Wien: lambda_peak T = h c / (x k_B)", m * Kel, hbar * speed / kB},
            {"theta = k_B T l_P / (hbar c)", one, kB * Kel * m / (hbar * speed)},
        };
        int bad = 0;
        for (const Rel& r : rels)
            if (!same(r.lhs, r.rhs)) {
                ++bad;
                tb::note("dimension mismatch: %s", r.name);
            }
        tb::check_true("T1", "all 32 relations have equal dimensions on both sides", rels.size() == 32 && bad == 0);
        // rejection-class check: three wrong relations must be flagged
        const Dim wrong1 = force, wrong1r = pressure * m;                       // F = P R
        const Dim wrong2 = energy, wrong2r = kg * speed;                        // E = m c
        const Dim wrong3 = Pconv, wrong3r = Phi / m;                            // P_conv = Phi / l_P
        tb::check_true("T1", "three deliberately wrong relations (F=PR, E=mc, P=Phi/l) are flagged",
                       !same(wrong1, wrong1r) && !same(wrong2, wrong2r) && !same(wrong3, wrong3r));
    }

    tb::heading("T2 dimension matrix of the seed constants: rank and independent dimensionless numbers");
    {
        struct Q {
            const char* name;
            double value;
            long long M, L, T, K;
        };
        const Q lP{"l_P", M::l_P, 0, 1, 0, 0}, c{"c", M::c, 0, 1, -1, 0}, hbar{"hbar", M::hbar, 1, 2, -1, 0},
            kB{"k_B", M::k_B, 1, 2, -2, -1}, T{"T_CMB", M::T_CMB, 0, 0, 0, 1}, RC{"R_CMB", M::R_CMB, 0, 1, 0, 0},
            me{"m_e", M::m_e, 1, 0, 0, 0}, mp{"m_p", M::m_p, 1, 0, 0, 0}, a0{"a_0", M::a_0, 0, 1, 0, 0},
            Rp{"R_p", M::R_p, 0, 1, 0, 0};
        auto analyse = [&](const char* label, const std::vector<Q>& qs, int want_rank, int want_null) {
            std::vector<std::vector<long long>> rows(4, std::vector<long long>(qs.size()));
            for (std::size_t j = 0; j < qs.size(); ++j) {
                rows[0][j] = qs[j].M; rows[1][j] = qs[j].L; rows[2][j] = qs[j].T; rows[3][j] = qs[j].K;
            }
            tb::rat::overflow = false;
            const int rk = tb::rat::rank(tb::rat::from_ints(rows));
            const auto ns = tb::rat::nullspace(tb::rat::from_ints(rows));
            tb::check_true("T2", (std::string(label) + ": rank " + std::to_string(want_rank) + ", null space dimension " +
                                  std::to_string(want_null)).c_str(),
                           rk == want_rank && static_cast<int>(ns.size()) == want_null && !tb::rat::overflow);
            for (const auto& w : ns) {
                double val = 1.0;
                std::string txt;
                for (std::size_t j = 0; j < qs.size(); ++j) {
                    if (w[j] == 0) continue;
                    val *= std::pow(qs[j].value, double(w[j]));
                    txt += std::string(qs[j].name) + "^" + std::to_string(w[j]) + " ";
                }
                tb::note("dimensionless product: %s= %.6e", txt.c_str(), val);
            }
            return ns;
        };
        const auto n1 = analyse("S1 {l_P, c, hbar, k_B, T_CMB}", {lP, c, hbar, kB, T}, 4, 1);
        {
            const auto& w = n1[0];
            const bool vec = (w == std::vector<long long>{1, -1, -1, 1, 1}) || (w == std::vector<long long>{-1, 1, 1, -1, -1});
            tb::check_true("T2", "S1 null space spanned by +-(1,-1,-1,1,1)", vec);
            const double theta = M::l_P * M::k_B * M::T_CMB / (M::hbar * M::c);
            tb::check("T2", "theta = l_P k_B T_CMB / (hbar c) = 1.9236e-32", theta, 1.9236e-32, 1e-3);
        }
        const auto n2 = analyse("S2 S1 + {R_CMB}", {lP, c, hbar, kB, T, RC}, 4, 2);
        {
            // N = R_CMB / l_P and theta lie in the null space: D w = 0 and rank of [basis; N; theta] stays 2
            tb::rat::Matrix mat;
            for (const auto& w : n2) { std::vector<tb::rat::Fr> r; for (long long v : w) r.push_back(tb::rat::make(v)); mat.push_back(r); }
            const std::vector<long long> Nv{-1, 0, 0, 0, 0, 1}, thv{1, -1, -1, 1, 1, 0};
            for (const auto* w : {&Nv, &thv}) { std::vector<tb::rat::Fr> r; for (long long v : *w) r.push_back(tb::rat::make(v)); mat.push_back(r); }
            tb::check_true("T2", "S2: N = R_CMB/l_P and theta both lie in the null space", tb::rat::rank(mat) == 2);
        }
        const auto n3 = analyse("S3 {c, hbar, m_e, l_P, m_p}", {c, hbar, me, lP, mp}, 3, 2);
        {
            tb::rat::Matrix mat;
            for (const auto& w : n3) { std::vector<tb::rat::Fr> r; for (long long v : w) r.push_back(tb::rat::make(v)); mat.push_back(r); }
            const std::vector<long long> mr{0, 0, -1, 0, 1}, lr{1, -1, 1, 1, 0};
            for (const auto* w : {&mr, &lr}) { std::vector<tb::rat::Fr> r; for (long long v : *w) r.push_back(tb::rat::make(v)); mat.push_back(r); }
            tb::check_true("T2", "S3: m_p/m_e and l_P m_e c/hbar both lie in the null space", tb::rat::rank(mat) == 2);
            tb::check("T2", "m_p/m_e vs 1836.152673426 (CODATA 2022)", M::m_p / M::m_e, 1836.152673426, 1e-8);
        }
        analyse("S4 {l_P, c, hbar, k_B, T_CMB, m_e, m_p, R_CMB, a_0, R_p}", {lP, c, hbar, kB, T, me, mp, RC, a0, Rp}, 4, 6);
    }

    tb::heading("T3 redundancies among the stored constants");
    {
        tb::check("T3", "h = 2 pi hbar", M::h, 2.0 * kPi * M::hbar, 1e-14);
        tb::check("T3", "r_e (engine, alpha^2 a_0) vs alpha hbar / (m_e c)", M::r_e, M::alpha * M::hbar / (M::m_e * M::c), 1e-9);
        tb::check("T3", "R_inf vs alpha^2 m_e c / (2 h)", M::R_inf, M::alpha * M::alpha * M::m_e * M::c / (2.0 * M::h), 1e-9);
        tb::check("T3", "Ry_eV vs h c R_inf / e", M::Ry_eV, M::h * M::c * M::R_inf / M::eV_to_J, 1e-9);
        tb::check("T3", "k_e e^2 (CODATA) vs alpha hbar c", L::coulomb_identity::k_e_e2_codata, L::coulomb_identity::k_e_e2, 1e-9);
        const double a_calc = 8.0 * std::pow(kPi, 5) * std::pow(M::k_B, 4) / (15.0 * std::pow(M::h, 3) * std::pow(M::c, 3));
        tb::check("T3", "a_rad (stored, five digits) vs 8 pi^5 k_B^4 / (15 h^3 c^3)", M::a_rad, a_calc, 1e-5);
        tb::note("a_rad computed = %.6e ; stored = %.6e ; relative difference %.2e", a_calc, M::a_rad, (M::a_rad - a_calc) / a_calc);
    }

    tb::heading("T4 thermal and spectral chain at T_CMB");
    {
        const double T = M::T_CMB;
        const double gm3 = golden_max([](double x) { return x * x * x / std::expm1(x); }, 0.5, 10.0);
        const double gm5 = golden_max([](double x) { return std::pow(x, 5) / std::expm1(x); }, 0.5, 12.0);
        tb::check("T4", "maximiser of x^3/(e^x-1) vs root of V1", gm3, x3, 1e-7);
        tb::check("T4", "maximiser of x^5/(e^x-1) vs root of V1", gm5, x5, 1e-7);
        const double lam = b_wien / T;                                   // wavelength maximum
        const double nu = x3 * M::k_B * T / M::h;                        // frequency maximum
        tb::check("T4", "c / (nu_peak lambda_peak) = x5/x3", M::c / (nu * lam), x5 / x3, 1e-12);
        tb::note("T = %.4f K: lambda_peak = %.6e m ; nu_peak = %.6e Hz (SI bridge) ; c/nu_peak = %.6e m ; ratio %.4f", T, lam, nu,
                 M::c / nu, M::c / (nu * lam));
        const double u_planck = 8.0 * kPi * std::pow(M::k_B * T, 4) / (std::pow(M::h * M::c, 3)) * planck_int;
        tb::check("T4", "u_CMB (engine, a_rad T^4) vs Planck energy density", L::law_I::u_CMB, u_planck, 1e-5);
        tb::note("u_CMB = %.6e J/m^3 (engine) ; Planck integral %.6e ; P_rad = u/3 = %.6e Pa ; P_conv = N u = %.6e Pa",
                 L::law_I::u_CMB, u_planck, L::law_I::u_CMB / 3.0, L::law_I::P_conv);
    }

    tb::heading("T5 coverage of the measured-namespace classification");
    {
        const std::string laws = slurp("Engine/include/sdt/laws.hpp");
        const std::size_t a = laws.find("namespace measured {");
        std::set<std::string> in_engine, in_table;
        if (a != std::string::npos) {
            std::size_t b = laws.find("\n}", a);
            const std::string block = laws.substr(a, b - a);
            const std::regex re(R"(inline\s+(?:constexpr\s+|const\s+)?double\s+(\w+)\s*=)");
            for (std::sregex_iterator it(block.begin(), block.end(), re), end; it != end; ++it) in_engine.insert((*it)[1]);
        }
        const std::string tab = slurp("Textbook/sources/MEASURED_CLASSIFICATION.md");
        {
            std::istringstream ss(tab);
            std::string line;
            const std::regex re(R"(^\| `(\w+)` \|)");
            while (std::getline(ss, line)) {
                std::smatch mm;
                if (std::regex_search(line, mm, re)) in_table.insert(mm[1]);
            }
        }
        std::vector<std::string> missing, extra;
        for (const auto& n : in_engine) if (!in_table.count(n)) missing.push_back(n);
        for (const auto& n : in_table) if (!in_engine.count(n)) extra.push_back(n);
        for (const auto& n : missing) tb::note("missing from the table: %s", n.c_str());
        for (const auto& n : extra) tb::note("not in the engine: %s", n.c_str());
        tb::check_true("T5", ("the sets are equal (engine " + std::to_string(in_engine.size()) + " identifiers, table " +
                              std::to_string(in_table.size()) + ")").c_str(),
                       !in_engine.empty() && missing.empty() && extra.empty());
    }

    return tb::finish();
}
