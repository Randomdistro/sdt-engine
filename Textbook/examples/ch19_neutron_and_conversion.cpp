// Chapter 19 — neutron and conversion: worked-example instrument.
// Pre-registration: Textbook/validation/ch19_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch19_neutron_and_conversion
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <queue>
#include <utility>
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

// Max-flow (Edmonds-Karp) on a small dense graph.
struct Flow {
    int n;
    std::vector<std::vector<int>> cap;
    explicit Flow(int n_) : n(n_), cap(n_, std::vector<int>(n_, 0)) {}
    int run(int s, int t) {
        int total = 0;
        while (true) {
            std::vector<int> par(n, -1);
            par[s] = s;
            std::queue<int> q;
            q.push(s);
            while (!q.empty() && par[t] < 0) {
                const int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v)
                    if (par[v] < 0 && cap[u][v] > 0) {
                        par[v] = u;
                        q.push(v);
                    }
            }
            if (par[t] < 0) break;
            int b = 1 << 30;
            for (int v = t; v != s; v = par[v]) b = std::min(b, cap[par[v]][v]);
            for (int v = t; v != s; v = par[v]) {
                cap[par[v]][v] -= b;
                cap[v][par[v]] += b;
            }
            total += b;
        }
        return total;
    }
};

// Maximum number of NEW contacts in a bipartite p-n graph with degree cap 3, given existing edges
// (which occupy slots and cannot be duplicated).
int max_new_contacts(int Z, int N, const std::vector<std::pair<int, int>>& existing) {
    std::vector<int> dp(Z, 3), dn(N, 3);
    std::vector<std::vector<int>> used(Z, std::vector<int>(N, 0));
    for (auto [p, n] : existing) {
        --dp[p];
        --dn[n];
        used[p][n] = 1;
    }
    const int S = Z + N, T = Z + N + 1;
    Flow f(Z + N + 2);
    for (int p = 0; p < Z; ++p) f.cap[S][p] = dp[p];
    for (int n = 0; n < N; ++n) f.cap[Z + n][T] = dn[n];
    for (int p = 0; p < Z; ++p)
        for (int n = 0; n < N; ++n)
            if (!used[p][n]) f.cap[p][Z + n] = 1;
    return f.run(S, T);
}

int exact_capacity(int Z, int N) { return std::min({3 * Z, 3 * N, Z * N}); }

struct Conv {
    int lost, surviving, daughter_max, reformed;
};

// Parent: Z protons (ids 0..Z-1), N neutrons (ids 0..N-1), edges (p,n). Convert neutron `v` to a proton.
Conv convert(int Z, int N, const std::vector<std::pair<int, int>>& edges, int v) {
    std::vector<std::pair<int, int>> survive;
    int lost = 0;
    for (auto [p, n] : edges) {
        if (n == v) { ++lost; continue; }
        survive.push_back({p, n > v ? n - 1 : n});  // neutron ids shift down after removing v
    }
    // daughter: Z+1 protons (new proton id Z), N-1 neutrons
    const int add = max_new_contacts(Z + 1, N - 1, survive);
    return {lost, static_cast<int>(survive.size()), static_cast<int>(survive.size()) + add, add};
}

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    tb::validate_helpers();

    const double MeV = M::MeV_to_J, c2 = M::c * M::c;
    const double mn = M::m_n * c2 / MeV, mp = M::m_p * c2 / MeV, me = M::m_e * c2 / MeV;

    tb::heading("V1 unit bridge kg -> MeV");
    tb::check("V1", "m_n c^2 = 939.56542194 MeV", mn, 939.56542194, 1e-8);
    tb::check("V1", "m_p c^2 = 938.27208943 MeV", mp, 938.27208943, 1e-8);
    tb::check("V1", "m_e c^2 = 0.51099895069 MeV", me, 0.51099895069, 1e-8);

    tb::heading("V2 max-flow solver vs exact bipartite capacity min(3Z, 3N, ZN)");
    {
        bool all = true;
        for (int Z = 1; Z <= 12; ++Z)
            for (int N = 1; N <= 12; ++N) all = all && (max_new_contacts(Z, N, {}) == exact_capacity(Z, N));
        tb::check_true("V2", "solver equals min(3Z, 3N, ZN) for 1 <= Z, N <= 12", all);
    }

    tb::heading("T1 free conversion: energy released and electron endpoint (massless channel)");
    {
        const double Q = mn - mp - me;
        const double Emax = (mn * mn + me * me - mp * mp) / (2.0 * mn);
        const double pmax = std::sqrt(Emax * Emax - me * me);
        const double Tp_end = std::sqrt(mp * mp + pmax * pmax) - mp;  // recoil with zero channel energy
        tb::note("Q = %.9f MeV ; E_e,max = %.9f MeV ; T_e,max = %.9f MeV ; proton recoil at endpoint = %.9f MeV", Q, Emax, Emax - me, Tp_end);
        tb::note("check: T_e,max + T_p(recoil) = %.9f MeV (= Q)", Emax - me + Tp_end);
        Rng g{20261109};
        const int draws = 2000000;
        long accepted = 0, rejected = 0, bad_above = 0, bad_below = 0;
        double worst_res = 0.0, max_acc = 0.0, minE = 1e300, maxE = 0.0;
        for (int i = 0; i < draws; ++i) {
            const double pe = g.next() * 1.1 * pmax;
            const double Ee = std::sqrt(me * me + pe * pe);
            const double ct = 2.0 * g.next() - 1.0, ph = 2.0 * kPi * g.next();
            const double st = std::sqrt(1.0 - ct * ct);
            const double ex = pe * st * std::cos(ph), ey = pe * st * std::sin(ph), ez = pe * ct;
            const double ct2 = 2.0 * g.next() - 1.0, ph2 = 2.0 * kPi * g.next();
            const double st2 = std::sqrt(1.0 - ct2 * ct2);
            const double nx = st2 * std::cos(ph2), ny = st2 * std::sin(ph2), nz = ct2;
            auto f = [&](double Enu) {
                const double qx = ex + Enu * nx, qy = ey + Enu * ny, qz = ez + Enu * nz;
                return Ee + Enu + std::sqrt(mp * mp + qx * qx + qy * qy + qz * qz) - mn;
            };
            if (f(0.0) >= 0.0) {
                ++rejected;
                if (Ee < Emax) ++bad_below;
                continue;
            }
            double lo = 0.0, hi = mn;
            for (int it = 0; it < 200; ++it) {
                const double mid = 0.5 * (lo + hi);
                (f(mid) < 0.0 ? lo : hi) = mid;
            }
            const double Enu = 0.5 * (lo + hi);
            ++accepted;
            worst_res = std::fmax(worst_res, std::fabs(f(Enu)));
            if (Ee > Emax) ++bad_above;
            max_acc = std::fmax(max_acc, Ee);
            minE = std::fmin(minE, Enu);
            maxE = std::fmax(maxE, Enu);
        }
        tb::note("draws %d : accepted %ld, rejected %ld ; channel energy range [%.3e, %.6f] MeV ; largest accepted E_e %.9f MeV", draws, accepted, rejected, minE, maxE, max_acc);
        tb::check("T1", "energy-conservation residual of accepted draws (MeV), worst", worst_res, 0.0, 1e-12, false);
        tb::check_true("T1", "no accepted draw has E_e above the closed-form endpoint", bad_above == 0);
        tb::check_true("T1", "no rejected draw has E_e below the closed-form endpoint", bad_below == 0);
        tb::check_true("T1", "largest accepted E_e within 1e-4 MeV below the endpoint", Emax - max_acc >= 0.0 && Emax - max_acc < 1e-4);
        tb::check_true("T1", "both accepted and rejected draws occurred", accepted > 0 && rejected > 0);
    }

    tb::heading("T2 endpoint sensitivity to the channel mass (engine convention values)");
    {
        const double Q = mn - mp - me;
        // endpoint with proton and channel moving together as one system of mass mX = mp + mnu, in kinetic energies
        // (nothing of size m_p is subtracted): T_e + mnu + p_e^2/(sqrt(mX^2 + p_e^2) + mX) = Q, p_e^2 = T_e (T_e + 2 me).
        auto endpoint = [&](double mnu) {
            const double mX = mp + mnu;
            double lo = 0.0, hi = Q;
            for (int it = 0; it < 200; ++it) {
                const double mid = 0.5 * (lo + hi);
                const double pe2 = mid * (mid + 2.0 * me);
                const double f = mid + mnu + pe2 / (std::sqrt(mX * mX + pe2) + mX) - Q;
                (f < 0.0 ? lo : hi) = mid;
            }
            return 0.5 * (lo + hi);
        };
        const double E0 = endpoint(0.0);
        double worst = 0.0;
        bool small = true;
        for (double meV : {0.02, 0.029, 0.06}) {
            const double mnu = meV * 1e-6;  // MeV
            const double E = endpoint(mnu);
            const double predicted = -(mp * mnu + 0.5 * mnu * mnu) / mn;
            worst = std::fmax(worst, std::fabs((E - E0) - predicted) / std::fabs(predicted));
            small = small && std::fabs(E - E0) < 1e-7 * Q;
            tb::note("m_nu = %.3f eV : endpoint shift %.4e eV (relative to Q: %.2e)", meV, (E - E0) * 1e6, std::fabs(E - E0) / Q);
        }
        tb::check("T2", "shift (direct root) equals -(m_p m_nu + m_nu^2/2)/m_n, worst relative", worst, 0.0, 1e-7, false);
        tb::check_true("T2", "each shift is below 1e-7 of Q", small);
    }

    tb::heading("T3 contact ledger of in-place conversion");
    {
        struct Case { const char* name; int Z, N; std::vector<std::pair<int, int>> edges; Conv want; };
        const Case cases[] = {
            {"free neutron", 0, 1, {}, {0, 0, 0, 0}},
            {"deuteron p-n", 1, 1, {{0, 0}}, {1, 0, 0, 0}},
            {"triton n-p-n", 1, 2, {{0, 0}, {0, 1}}, {1, 1, 2, 1}},
            {"alpha ring p-n-p-n", 2, 2, {{0, 0}, {1, 0}, {1, 1}, {0, 1}}, {2, 2, 3, 1}},
        };
        for (const auto& cs : cases) {
            const Conv got = convert(cs.Z, cs.N, cs.edges, 0);
            char label[160];
            std::snprintf(label, sizeof label, "%s: (lost, surviving, daughter max, re-formed) = (%d,%d,%d,%d) ; registered (%d,%d,%d,%d)", cs.name, got.lost, got.surviving, got.daughter_max, got.reformed, cs.want.lost, cs.want.surviving, cs.want.daughter_max, cs.want.reformed);
            tb::check_true("T3", label, got.lost == cs.want.lost && got.surviving == cs.want.surviving && got.daughter_max == cs.want.daughter_max && got.reformed == cs.want.reformed);
        }
    }

    tb::heading("T4 engine contact_capacity against the exact maximum");
    {
        namespace Nu = sdt::laws::nuclear;
        bool eq_ok = true, ne_ok = true;
        int mismatches = 0;
        for (int Z = 1; Z <= 12; ++Z)
            for (int N = 1; N <= 12; ++N) {
                const int eng = Nu::contact_capacity(Z, N), ex = exact_capacity(Z, N);
                if (std::max(Z, N) >= 3) eq_ok = eq_ok && (eng == ex);
                else {
                    ne_ok = ne_ok && (eng > ex);
                    ++mismatches;
                    tb::note("(Z,N) = (%d,%d): engine %d ; exact %d", Z, N, eng, ex);
                }
            }
        tb::check_true("T4", "engine equals exact whenever max(Z, N) >= 3", eq_ok);
        tb::check_true("T4", "engine exceeds exact for exactly (1,1), (1,2), (2,1), (2,2)", ne_ok && mismatches == 4);
    }

    return tb::finish();
}
