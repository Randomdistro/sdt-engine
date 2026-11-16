// APS08 — Zeeman splitting from route orientation: normal pattern (Round 1) and the
// anomalous pattern on the 8-state s/p route basis (Round 2).
// Pre-registration: PROMPT.md, section "Pre-registration (2026-10-03)".
// The vector spin-orbit model M_vec is the standard account's angular-momentum algebra,
// used ONLY as a reference to compute the target pattern; it is not offered as SDT.
// Build: cl /std:c++20 /EHsc /O2 /I Engine\include aps08_zeeman_routes.cpp
#include <sdt/laws.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <set>
#include <utility>
#include <vector>

namespace {
namespace m = sdt::laws::measured;
constexpr double pi = 3.14159265358979323846;
using V = std::array<double, 3>;

V operator+(const V& a, const V& b) { return {a[0] + b[0], a[1] + b[1], a[2] + b[2]}; }
V operator*(double s, const V& a) { return {s * a[0], s * a[1], s * a[2]}; }
double dot(const V& a, const V& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
V cross(const V& a, const V& b) { return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]}; }
double norm(const V& a) { return std::sqrt(dot(a, a)); }
bool near(double a, double b, double rel) { return std::fabs(a - b) <= rel * std::fabs(b); }

// ---------- V1: Larmor equivalence by direct integration (a.u., force -v x B on the circulating boundary, B along z) ----------
struct PS { V r, v; };
V accel(const PS& s, double B) {
    const double rr = norm(s.r);
    return (-1.0 / (rr * rr * rr)) * s.r + (-1.0) * cross(s.v, {0.0, 0.0, B});
}
void rk4(PS& s, double dt, double B) {
    auto f = [&](const PS& x) { return PS{x.v, accel(x, B)}; };
    const PS k1 = f(s), k2 = f({s.r + 0.5 * dt * k1.r, s.v + 0.5 * dt * k1.v});
    const PS k3 = f({s.r + 0.5 * dt * k2.r, s.v + 0.5 * dt * k2.v}), k4 = f({s.r + dt * k3.r, s.v + dt * k3.v});
    s.r = s.r + (dt / 6.0) * (k1.r + 2.0 * k2.r + 2.0 * k3.r + k4.r);
    s.v = s.v + (dt / 6.0) * (k1.v + 2.0 * k2.v + 2.0 * k3.v + k4.v);
}
// Precession rate of L about z (rad per a.u. time), from the azimuth of (L_x, L_y) over whole orbits.
double precession_rate(double B, int orbits) {
    const double a = 4.0, eps = 0.3, T = 2.0 * pi * std::pow(a, 1.5);
    const double c60 = 0.5, s60 = std::sqrt(0.75);
    const V e{1.0, 0.0, 0.0}, h{0.0, s60, c60};          // L tilted 60 degrees from the field
    const V phat = cross(h, e);
    const double nm = std::pow(a, -1.5), speed = a * std::sqrt(1.0 - eps * eps) * nm / (1.0 - eps);
    PS s{a * (1.0 - eps) * e, speed * phat};
    const int per = 8000;
    std::vector<double> t, phi;
    for (int orb = 0; orb <= orbits; ++orb) {
        if (orb % 20 == 0) {
            const V L = cross(s.r, s.v);
            t.push_back(orb * T);
            phi.push_back(std::atan2(L[1], L[0]));
        }
        for (int i = 0; i < per && orb < orbits; ++i) rk4(s, T / per, B);
    }
    for (size_t i = 1; i < phi.size(); ++i)   // unwrap
        while (phi[i] - phi[i - 1] > pi) phi[i] -= 2.0 * pi;
    for (size_t i = 1; i < phi.size(); ++i)
        while (phi[i] - phi[i - 1] < -pi) phi[i] += 2.0 * pi;
    double mt = 0, mp = 0, stt = 0, stp = 0;
    for (size_t i = 0; i < t.size(); ++i) { mt += t[i]; mp += phi[i]; }
    mt /= t.size(); mp /= phi.size();
    for (size_t i = 0; i < t.size(); ++i) { stt += (t[i] - mt) * (t[i] - mt); stp += (t[i] - mt) * (phi[i] - mp); }
    return stp / stt;
}

// ---------- symmetric eigenproblem (cyclic Jacobi) ----------
template <int N>
void jacobi(std::array<std::array<double, N>, N> A, std::array<double, N>& w, std::array<std::array<double, N>, N>& Vec) {
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) Vec[i][j] = (i == j);
    for (int sweep = 0; sweep < 100; ++sweep) {
        double off = 0;
        for (int p = 0; p < N; ++p) for (int q = p + 1; q < N; ++q) off += A[p][q] * A[p][q];
        if (off < 1e-30) break;
        for (int p = 0; p < N; ++p)
            for (int q = p + 1; q < N; ++q) {
                if (std::fabs(A[p][q]) < 1e-300) continue;
                const double th = 0.5 * std::atan2(2.0 * A[p][q], A[q][q] - A[p][p]);
                const double c = std::cos(th), s = std::sin(th);
                for (int k = 0; k < N; ++k) { const double a = A[k][p], b = A[k][q]; A[k][p] = c * a - s * b; A[k][q] = s * a + c * b; }
                for (int k = 0; k < N; ++k) { const double a = A[p][k], b = A[q][k]; A[p][k] = c * a - s * b; A[q][k] = s * a + c * b; }
                for (int k = 0; k < N; ++k) { const double a = Vec[k][p], b = Vec[k][q]; Vec[k][p] = c * a - s * b; Vec[k][q] = s * a + c * b; }
            }
    }
    for (int i = 0; i < N; ++i) w[i] = A[i][i];
}

// ---------- s/p route basis ----------
// p index: (m = 1,0,-1) x (s = up, down): idx = 2*(1-m) + (s_up ? 0 : 1).
int pidx(int mm, bool up) { return 2 * (1 - mm) + (up ? 0 : 1); }
using M6 = std::array<std::array<double, 6>, 6>;

M6 p_hamiltonian(double xi, double wL, bool vector_coupling) {
    M6 H{};
    for (int mm = -1; mm <= 1; ++mm)
        for (int su = 0; su < 2; ++su) {
            const bool up = su == 0;
            const double s = up ? 0.5 : -0.5;
            const int i = pidx(mm, up);
            H[i][i] = xi * mm * s + wL * (mm + 2.0 * s);          // diagonal coupling + Zeeman (g_s = 2 input)
            if (vector_coupling && up && mm < 1) {                 // (xi/2) L+ S-: |m,up> -> |m+1,down>; hermitian partner by symmetry
                const double c = 0.5 * xi * std::sqrt(2.0 - mm * (mm + 1.0));
                const int j = pidx(mm + 1, false);
                H[i][j] += c;
                H[j][i] += c;
            }
        }
    return H;
}

struct Line { double shift, intensity; int cluster; };

// Lines from the two s states (m=0, spin +-1/2, energy 2 s wL) to the p eigenstates; shift measured from the
// zero-field cluster energy, in units of wL. Dipole: orbital m changes by q = m' (from 0), spin unchanged.
std::vector<Line> lines(double xi, double wL, bool vec, std::vector<double>& cluster_E, std::vector<int>& cluster_of) {
    std::array<double, 6> w0, w;
    std::array<std::array<double, 6>, 6> V0, Vc;
    jacobi<6>(p_hamiltonian(xi, 0.0, vec), w0, V0);
    jacobi<6>(p_hamiltonian(xi, wL, vec), w, Vc);
    // cluster eigenstates by zero-field energy
    std::vector<double> sorted(w0.begin(), w0.end());
    std::sort(sorted.begin(), sorted.end());
    cluster_E.clear();
    for (double e : sorted) if (cluster_E.empty() || std::fabs(e - cluster_E.back()) > 1e-6 * xi) cluster_E.push_back(e);
    // assign each field-on eigenstate to the cluster of nearest zero-field energy (weak field)
    std::vector<int> cl(6);
    for (int k = 0; k < 6; ++k) {
        int best = 0; double bd = 1e300;
        for (size_t c = 0; c < cluster_E.size(); ++c) if (std::fabs(w[k] - cluster_E[c]) < bd) { bd = std::fabs(w[k] - cluster_E[c]); best = static_cast<int>(c); }
        cl[k] = best;
    }
    cluster_of = cl;
    std::vector<Line> out;
    for (int su = 0; su < 2; ++su) {
        const bool up = su == 0;
        const double Es = 2.0 * (up ? 0.5 : -0.5) * wL;
        for (int k = 0; k < 6; ++k) {
            double I = 0;
            for (int mm = -1; mm <= 1; ++mm) { const double c = Vc[pidx(mm, up)][k]; I += c * c; }
            if (I < 1e-9) continue;
            out.push_back({((w[k] - Es) - cluster_E[cl[k]]) / wL, I, cl[k]});
        }
    }
    return out;
}

// Merge lines with equal shift (within tol, units of wL); returns (shift, summed intensity).
std::vector<std::pair<double, double>> merge(std::vector<std::pair<double, double>> v, double tol) {
    std::sort(v.begin(), v.end());
    std::vector<std::pair<double, double>> out;
    for (auto& p : v) {
        if (!out.empty() && std::fabs(p.first - out.back().first) < tol) out.back().second += p.second;
        else out.push_back(p);
    }
    return out;
}

int validate() {
    int fail = 0;
    auto check = [&](const char* what, bool ok) {
        std::printf("  [%s] %s\n", ok ? "ok" : "FAIL", what);
        if (!ok) ++fail;
    };
    std::printf("INSTRUMENT VALIDATION (known answers; physics rounds not yet run)\n");
    char buf[200];
    {
        const double r1 = std::fabs(precession_rate(1e-5, 2000)), r2 = std::fabs(precession_rate(2e-5, 2000));
        std::snprintf(buf, sizeof buf, "V1 Larmor: precession of L about B: %.4e at B=1e-5 (expect B/2 = 5e-6), %.4e at 2e-5 (expect 1e-5), ratio %.4f",
                      r1, r2, r2 / r1);
        check(buf, near(r1, 5e-6, 0.01) && near(r2, 1e-5, 0.01) && near(r2 / r1, 2.0, 0.01));
    }
    {
        std::array<double, 6> w; std::array<std::array<double, 6>, 6> Vv;
        jacobi<6>(p_hamiltonian(1.0, 0.0, true), w, Vv);
        std::vector<double> s(w.begin(), w.end()); std::sort(s.begin(), s.end());
        const bool z = near(s[0], -1.0, 1e-10) && near(s[1], -1.0, 1e-10) && near(s[2], 0.5, 1e-10) && near(s[5], 0.5, 1e-10);
        std::snprintf(buf, sizeof buf, "V2 M_vec zero-field eigenvalues: %.6f %.6f %.6f %.6f %.6f %.6f (expect -1 x2, +1/2 x4)", s[0], s[1], s[2], s[3], s[4], s[5]);
        check(buf, z);
        // first-order shifts g_J m_J wL: J=3/2: +-2, +-2/3; J=1/2: +-1/3 (in wL), g_s = 2
        const double wL = 1e-4;
        std::array<double, 6> wf; std::array<std::array<double, 6>, 6> Vf;
        jacobi<6>(p_hamiltonian(1.0, wL, true), wf, Vf);
        std::vector<double> hi, lo;
        for (double e : wf) { if (e > -0.5) hi.push_back((e - 0.5) / wL); else lo.push_back((e + 1.0) / wL); }
        std::sort(hi.begin(), hi.end()); std::sort(lo.begin(), lo.end());
        const double ehi[4] = {-2.0, -2.0 / 3.0, 2.0 / 3.0, 2.0}, elo[2] = {-1.0 / 3.0, 1.0 / 3.0};
        bool ok = hi.size() == 4 && lo.size() == 2;
        for (int i = 0; ok && i < 4; ++i) ok = std::fabs(hi[i] - ehi[i]) < 1e-3;
        for (int i = 0; ok && i < 2; ++i) ok = std::fabs(lo[i] - elo[i]) < 1e-3;
        std::snprintf(buf, sizeof buf, "V2 first-order shifts g_J m_J (units wL): J=3/2 %.4f %.4f %.4f %.4f; J=1/2 %.4f %.4f (expect +-2, +-2/3; +-1/3)",
                      hi[0], hi[1], hi[2], hi[3], lo[0], lo[1]);
        check(buf, ok);
    }
    {
        std::vector<std::pair<double, double>> lns;
        for (int mu = -2; mu <= 2; ++mu) for (int ml = -1; ml <= 1; ++ml) if (std::abs(mu - ml) <= 1) lns.push_back({static_cast<double>(mu - ml), 1.0});
        const auto g = merge(lns, 1e-6);
        std::snprintf(buf, sizeof buf, "V3 cluster-and-count on the singlet case returns %zu components (expect 3)", g.size());
        check(buf, g.size() == 3);
    }
    return fail;
}

void round1() {
    const double e_bridge = m::e_charge;   // unit-bridge input
    std::printf("\nROUND 1 - normal pattern from route orientation (Cd 643.847 nm, singlet)\n");
    const double fL_per_T = e_bridge / (4.0 * pi * m::m_e);   // Hz per tesla = Omega_B/2pi per tesla
    const double lam = 643.847e-9;
    std::printf("Omega_B/2pi per tesla = e/(4 pi m_e) = %.5f GHz/T = %.5f cm^-1/T; Delta lambda at %.3f nm = %.5f nm/T\n",
                fL_per_T / 1e9, fL_per_T / (m::c * 100.0), lam * 1e9, lam * lam * fL_per_T / m::c * 1e9);
    std::set<int> shifts;
    int n_trans = 0;
    for (int mu = -2; mu <= 2; ++mu)
        for (int ml = -1; ml <= 1; ++ml)
            if (std::abs(mu - ml) <= 1) { shifts.insert(mu - ml); ++n_trans; }
    std::printf("route classes: upper d (m = -2..2, m3 = 3m), lower p (m = -1..1); allowed transitions (dm = 0, +-1): %d\n", n_trans);
    std::printf("distinct components (units Omega_B/2pi): ");
    for (int s : shifts) std::printf("%+d ", s);
    std::printf("  -> %zu components, spacing 1 (singlets: no spin term)\n", shifts.size());
    std::printf("round 1 rejection criterion (count != 3 or V1 fails): %s\n", shifts.size() == 3 ? "not met" : "MET");
}

void round2() {
    std::printf("\nROUND 2 - anomalous pattern on the 8-state s/p route basis (g_s = 2 input; xi = 1, wL = 1e-4 xi)\n");
    const double xi = 1.0, wL = 1e-4;
    struct Target { const char* name; std::vector<double> pos; };
    // Cluster order: lowest zero-field energy first. For M_vec the lowest cluster is J = 1/2 (D1), the upper J = 3/2 (D2).
    const std::vector<Target> targets = {{"D1 (J=1/2)", {-4.0 / 3, -2.0 / 3, 2.0 / 3, 4.0 / 3}}, {"D2 (J=3/2)", {-5.0 / 3, -1.0, -1.0 / 3, 1.0 / 3, 1.0, 5.0 / 3}}};
    for (int model = 0; model < 2; ++model) {
        const bool vec = model == 1;
        std::vector<double> cluster_E; std::vector<int> cl;
        const auto ls = lines(xi, wL, vec, cluster_E, cl);
        std::printf("\n%s\n", vec ? "M_vec (reference only: rotation-invariant coupling, angular-momentum algebra)" : "M_diag (APS04 diagonal route classes, coupling xi m s_z)");
        std::printf("zero-field p manifold: %zu levels at", cluster_E.size());
        for (double e : cluster_E) std::printf(" %+.3f", e);
        std::printf("  (observed Na: a doublet, 2 + 4 states)\n");
        for (size_t c = 0; c < cluster_E.size(); ++c) {
            std::vector<std::pair<double, double>> v;
            for (const Line& l : ls) if (l.cluster == static_cast<int>(c)) v.push_back({l.shift, l.intensity});
            const auto g = merge(v, 2e-3);
            std::printf("  cluster %zu (E0 = %+.3f): %zu components:", c, cluster_E[c], g.size());
            for (auto& p : g) std::printf(" %+.4f(I=%.3f)", p.first, p.second);
            std::printf("\n");
            if (vec && c < targets.size()) {
                const auto& t = targets[c];
                bool okc = g.size() == t.pos.size(), okp = okc;
                for (size_t i = 0; okc && i < g.size(); ++i) okp = okp && std::fabs(g[i].first - t.pos[i]) <= 0.01 * std::fabs(t.pos[i]);
                std::printf("    target %s: %zu components at", t.name, t.pos.size());
                for (double x : t.pos) std::printf(" %+.4f", x);
                std::printf("  -> count %s, positions within 1%% %s\n", okc ? "match" : "MISMATCH", okp ? "match" : "MISMATCH");
            }
        }
        if (!vec) {
            const bool doublet = cluster_E.size() == 2;
            std::printf("M_diag: p manifold doublet reproduced: %s; rejection criterion (count wrong or positions off): %s\n",
                        doublet ? "yes" : "NO", "evaluated against D1 = 4 / D2 = 6 above");
        }
    }
}
// ---------- Round 3: magnitude rules in the semiclassical vector model ----------
// g_J = 1 + (g_s - 1) (J^2 + S^2 - L^2) / (2 J^2) with g_s = 2; each rule supplies the squared magnitudes.
struct QS { const char* name; double l, j; };
double mag2(double q, int rule) {
    if (rule == 0) return q * q;                       // R1 integer magnitude
    if (rule == 1) return (q + 0.5) * (q + 0.5);       // R2 shifted by one half
    return q * (q + 1.0);                              // R3 quantum number x (quantum number + 1)
}
double g_rule(const QS& s, int rule) {
    const double L2 = mag2(s.l, rule), S2 = mag2(0.5, rule), J2 = mag2(s.j, rule);
    return 1.0 + (J2 + S2 - L2) / (2.0 * J2);
}
std::vector<double> pattern(double gS, double gP, double jP) {
    std::vector<std::pair<double, double>> v;
    for (double mP = -jP; mP <= jP + 1e-9; mP += 1.0)
        for (double mS : {-0.5, 0.5})
            if (std::fabs(mP - mS) <= 1.0 + 1e-9) v.push_back({gP * mP - gS * mS, 1.0});
    const auto g = merge(v, 1e-9);
    std::vector<double> out;
    for (auto& p : g) out.push_back(p.first);
    return out;
}

void round3() {
    std::printf("\nROUND 3 - which magnitude rule makes the vector model reproduce the doublets? (g_s = 2)\n");
    const std::vector<QS> st = {{"2S1/2", 0, 0.5}, {"2P1/2", 1, 0.5}, {"2P3/2", 1, 1.5}, {"2D3/2", 2, 1.5}, {"2D5/2", 2, 2.5}, {"2F5/2", 3, 2.5}, {"2F7/2", 3, 3.5}};
    const char* rn[3] = {"R1 integer", "R2 shifted 1/2", "R3 q(q+1)"};
    std::printf("%-7s %-10s %9s", "state", "coupling", "g target");
    for (int r = 0; r < 3; ++r) std::printf(" %14s %8s", rn[r], "dev %");
    std::printf("\n");
    bool rule_ok[3] = {true, true, true};
    for (const QS& s : st) {
        const double target = g_rule(s, 2);
        const bool stretched = std::fabs(s.j - (s.l + 0.5)) < 1e-9;
        std::printf("%-7s %-10s %9.5f", s.name, s.l == 0 ? "-" : (stretched ? "stretched" : "anti-alig."), target);
        for (int r = 0; r < 3; ++r) {
            const double g = g_rule(s, r);
            const double dev = 100.0 * (g - target) / target;
            std::printf(" %14.5f %8.2f", g, dev);
            if (std::fabs(dev) > 1.0) rule_ok[r] = false;
        }
        std::printf("\n");
    }
    std::printf("\nNa D1 / D2 patterns (units omega_L), target from the standard g values:\n");
    const double gS_t = g_rule(st[0], 2);
    const auto t1 = pattern(gS_t, g_rule(st[1], 2), 0.5), t2 = pattern(gS_t, g_rule(st[2], 2), 1.5);
    for (int r = 0; r < 3; ++r) {
        const auto p1 = pattern(g_rule(st[0], r), g_rule(st[1], r), 0.5), p2 = pattern(g_rule(st[0], r), g_rule(st[2], r), 1.5);
        auto ok = [](const std::vector<double>& a, const std::vector<double>& b) {
            if (a.size() != b.size()) return false;
            for (size_t i = 0; i < a.size(); ++i) if (std::fabs(a[i] - b[i]) > 0.01 * std::fabs(b[i])) return false;
            return true;
        };
        const bool d1 = ok(p1, t1), d2 = ok(p2, t2);
        std::printf("%-15s D1: %zu components %s | D2: %zu components %s\n", rn[r], p1.size(), d1 ? "match" : "MISMATCH", p2.size(), d2 ? "match" : "MISMATCH");
        if (!d1 || !d2) rule_ok[r] = false;
    }
    std::printf("target D1: %zu components, D2: %zu components\n", t1.size(), t2.size());
    for (int r = 0; r < 3; ++r) std::printf("rejection criterion for %-15s : %s\n", rn[r], rule_ok[r] ? "not met (reproduces all registered targets)" : "MET (rejected)");
}
}  // namespace

int main() {
    std::printf("APS08 Zeeman splitting from route orientation\n");
    std::printf("pre-registration: PROMPT.md (2026-10-03)\n\n");
    if (validate() != 0) {
        std::printf("\nVALIDATION FAILED: instrument fault, no result reported.\n");
        return 2;
    }
    std::printf("VALIDATION PASS\n");
    round1();
    round2();
    round3();
    return 0;
}
