// Chapter 21 — three-slot contact capacity: worked-example instrument.
// Pre-registration: Textbook/validation/ch21_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch21_three_slot_contact_capacity
#include <sdt/laws.hpp>
#include <sdt/nuclear.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <queue>
#include <set>
#include <utility>
#include <vector>

namespace {

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

// Max contacts for Z protons and N neutrons with at most 3 contacts per unit; returns edges.
int max_graph(int Z, int N, std::vector<std::pair<int, int>>* edges) {
    const int S = Z + N, T = Z + N + 1;
    Flow f(Z + N + 2);
    for (int p = 0; p < Z; ++p) f.cap[S][p] = 3;
    for (int n = 0; n < N; ++n) f.cap[Z + n][T] = 3;
    for (int p = 0; p < Z; ++p)
        for (int n = 0; n < N; ++n) f.cap[p][Z + n] = 1;
    const int val = f.run(S, T);
    if (edges)
        for (int p = 0; p < Z; ++p)
            for (int n = 0; n < N; ++n)
                if (f.cap[Z + n][p] > 0) edges->push_back({p, n});
    return val;
}

int exact_capacity(int Z, int N) { return std::min({3 * Z, 3 * N, Z * N}); }

struct Sphere {
    double x, y, z;
    char kind;  // 'p' or 'n'
};

struct GeoReport {
    int unlike = 0, like = 0, overlaps = 0, max_degree = 0;
    double min_noncontact_gap = 1e300;  // smallest (distance - 2) among non-touching, non-overlapping pairs
};

GeoReport check(const std::vector<Sphere>& s) {
    GeoReport r;
    std::vector<int> deg(s.size(), 0);
    for (std::size_t i = 0; i < s.size(); ++i)
        for (std::size_t j = i + 1; j < s.size(); ++j) {
            const double d = std::sqrt((s[i].x - s[j].x) * (s[i].x - s[j].x) + (s[i].y - s[j].y) * (s[i].y - s[j].y) + (s[i].z - s[j].z) * (s[i].z - s[j].z));
            if (d < 2.0 - 1e-9) ++r.overlaps;
            else if (std::fabs(d - 2.0) <= 1e-9) {
                if (s[i].kind == s[j].kind) ++r.like;
                else {
                    ++r.unlike;
                    ++deg[i];
                    ++deg[j];
                }
            } else r.min_noncontact_gap = std::fmin(r.min_noncontact_gap, d - 2.0);
        }
    for (int d : deg) r.max_degree = std::max(r.max_degree, d);
    return r;
}

}  // namespace

int main() {
    namespace Nu = sdt::nuclear;
    namespace NL = sdt::laws::nuclear;
    tb::validate_helpers();

    tb::heading("V1 max-flow on hand-checkable cases");
    {
        tb::check_true("V1", "K_{3,3} = 9, (1,5) = 3, (2,2) = 4, (4,1) = 3, (2,7) = 6",
                       max_graph(3, 3, nullptr) == 9 && max_graph(1, 5, nullptr) == 3 && max_graph(2, 2, nullptr) == 4 && max_graph(4, 1, nullptr) == 3 && max_graph(2, 7, nullptr) == 6);
    }

    tb::heading("V2 geometric checker on pairs");
    {
        auto r1 = check({{0, 0, 0, 'p'}, {2, 0, 0, 'n'}});
        auto r2 = check({{0, 0, 0, 'p'}, {2, 0, 0, 'p'}});
        auto r3 = check({{0, 0, 0, 'p'}, {1.5, 0, 0, 'p'}});
        tb::check_true("V2", "touching unlike pair: 1 unlike, 0 like, 0 overlap", r1.unlike == 1 && r1.like == 0 && r1.overlaps == 0);
        tb::check_true("V2", "touching like pair: 1 like contact", r2.like == 1 && r2.unlike == 0);
        tb::check_true("V2", "pair at distance 1.5: 1 overlap", r3.overlaps == 1);
    }

    tb::heading("T1 exact capacity and the graph read back, 1 <= Z, N <= 40");
    {
        long cases = 0, bad_val = 0, bad_graph = 0;
        for (int Z = 1; Z <= 40; ++Z)
            for (int N = 1; N <= 40; ++N) {
                std::vector<std::pair<int, int>> e;
                const int v = max_graph(Z, N, &e);
                ++cases;
                if (v != exact_capacity(Z, N)) ++bad_val;
                std::vector<int> dp(Z, 0), dn(N, 0);
                std::set<std::pair<int, int>> seen;
                bool ok = (int)e.size() == v;
                for (auto [p, n] : e) {
                    ++dp[p];
                    ++dn[n];
                    ok = ok && seen.insert({p, n}).second;
                }
                for (int d : dp) ok = ok && d <= 3;
                for (int d : dn) ok = ok && d <= 3;
                if (!ok) ++bad_graph;
            }
        tb::note("%ld cases ; flow value mismatches %ld ; invalid read-back graphs %ld", cases, bad_val, bad_graph);
        tb::check_true("T1", "max-flow equals min(3Z, 3N, ZN) in every case", bad_val == 0);
        tb::check_true("T1", "every read-back graph has degrees <= 3, no repeated edge and the stated edge count", bad_graph == 0);
    }

    tb::heading("T2 module composition against the capacity");
    {
        long pts = 0, bad_E = 0, bad_fit = 0;
        for (int Z = 2; Z <= 120; ++Z)
            for (int N = Z; N <= 2 * Z - 2; ++N) {
                const int nd = 2 * Z - 2 - N, nt = N - Z;
                const int Eint = 4 + nd + 2 * nt;
                ++pts;
                if (Eint != N + 2) ++bad_E;
                if (Eint > exact_capacity(Z, N)) ++bad_fit;
            }
        tb::note("%ld wedge points (Z = 2..120)", pts);
        tb::check_true("T2", "E_int = 4 + n_d + 2 n_t equals N + 2 at every wedge point", bad_E == 0);
        tb::check_true("T2", "E_int does not exceed the exact capacity at any wedge point", bad_fit == 0);
        int minslack = 1 << 30, maxslack = -1, min_Z = 0, min_A = 0, max_Z = 0, max_A = 0, valid = 0, zero_count = 0;
        double sum = 0.0;
        for (const auto& r : Nu::natural_basis) {
            const auto g = Nu::alpha_grammar(r.Z, r.A);
            if (!g.valid) continue;
            ++valid;
            const int N = r.A - r.Z, slack = exact_capacity(r.Z, N) - (N + 2);
            sum += slack;
            if (slack == 0) ++zero_count;
            if (slack < minslack) { minslack = slack; min_Z = r.Z; min_A = r.A; }
            if (slack > maxslack) { maxslack = slack; max_Z = r.Z; max_A = r.A; }
        }
        tb::note("natural nuclides %d : slack min %d (Z=%d, A=%d) ; max %d (Z=%d, A=%d) ; mean %.2f ; zero-slack count %d", valid, minslack, min_Z, min_A, maxslack, max_Z, max_A, sum / valid, zero_count);
        tb::check_true("T2", "minimum slack over the natural table is 0 and occurs only at He-4", minslack == 0 && zero_count == 1 && min_Z == 2 && min_A == 4);
        struct Named { const char* n; int Z, A; };
        for (const Named& nm : {Named{"He-4", 2, 4}, Named{"C-12", 6, 12}, Named{"O-16", 8, 16}, Named{"Ca-40", 20, 40}, Named{"Fe-56", 26, 56}, Named{"Pb-208", 82, 208}}) {
            const int N = nm.A - nm.Z, cap = exact_capacity(nm.Z, N), E = N + 2;
            tb::note("%-7s Z=%2d N=%3d : capacity %3d ; E_int %3d ; slack %3d ; free proton slots %3d ; free neutron slots %3d", nm.n, nm.Z, N, cap, E, cap - E, 3 * nm.Z - E, 3 * N - E);
        }
    }

    tb::heading("T3 geometry of frozen configurations (unit radius, contact distance 2)");
    {
        const double s2 = std::sqrt(2.0);
        {
            auto r = check({{s2, 0, 0, 'p'}, {0, s2, 0, 'n'}, {-s2, 0, 0, 'p'}, {0, -s2, 0, 'n'}});
            tb::check_true("T3", "alpha ring (square): 4 unlike, 0 like, 0 overlaps", r.unlike == 4 && r.like == 0 && r.overlaps == 0);
            tb::note("alpha ring: like-pair spacing %.6f (contact 2)", 2.0 + r.min_noncontact_gap);
        }
        {
            // tetrahedron of 4 equal spheres, all edges 2: vertices (1,1,1),(1,-1,-1),(-1,1,-1),(-1,-1,1) * (2/(2*sqrt(2))) * sqrt(2)... edge = 2 sqrt(2) * a => a = 1/sqrt(2)
            const double a = 1.0 / s2;
            auto r = check({{a, a, a, 'p'}, {a, -a, -a, 'p'}, {-a, a, -a, 'n'}, {-a, -a, a, 'n'}});
            tb::check_true("T3", "equal-sphere tetrahedron (2 p, 2 n): 4 unlike and 2 like contacts (invalid)", r.unlike == 4 && r.like == 2 && r.overlaps == 0);
        }
        {
            const double th[3] = {90.0, 60.0, 50.0};
            const int want_like[3] = {0, 1, 0}, want_over[3] = {0, 0, 1};
            bool all = true;
            for (int i = 0; i < 3; ++i) {
                const double t = th[i] * std::numbers::pi / 180.0;
                auto r = check({{0, 0, 0, 'p'}, {2, 0, 0, 'n'}, {2 * std::cos(t), 2 * std::sin(t), 0, 'n'}});
                all = all && r.unlike == 2 && r.like == want_like[i] && r.overlaps == want_over[i];
            }
            tb::check_true("T3", "bent triton: 90 deg valid; 60 deg like contact; 50 deg overlap", all);
        }
        {
            const double d = 2.0 / std::sqrt(3.0);
            auto r = check({{0, 0, 0, 'p'}, {d, d, d, 'n'}, {d, -d, -d, 'n'}, {-d, d, -d, 'n'}, {-d, -d, d, 'n'}});
            tb::check_true("T3", "four-neighbour star: 4 unlike, 0 like, 0 overlaps, max degree 4 (placeable; excluded only by the cap)", r.unlike == 4 && r.like == 0 && r.overlaps == 0 && r.max_degree == 4);
            tb::note("star: neighbour spacing %.6f (contact 2)", 2.0 + r.min_noncontact_gap);
        }
        {
            const double phi = (1.0 + std::sqrt(5.0)) / 2.0, nrm = std::sqrt(1.0 + phi * phi);
            std::vector<Sphere> ico{{0, 0, 0, 'p'}};
            for (int a : {-1, 1})
                for (int b : {-1, 1}) {
                    ico.push_back({0, a * 1.0 / nrm * 2.0, b * phi / nrm * 2.0, 'n'});
                    ico.push_back({a * 1.0 / nrm * 2.0, b * phi / nrm * 2.0, 0, 'n'});
                    ico.push_back({b * phi / nrm * 2.0, 0, a * 1.0 / nrm * 2.0, 'n'});
                }
            auto r = check(ico);
            tb::check_true("T3", "twelve-around-one: 12 unlike contacts, 0 like, 0 overlaps, max degree 12", r.unlike == 12 && r.like == 0 && r.overlaps == 0 && r.max_degree == 12);
            tb::check("T3", "shell spacing = 2/sin(2 pi/5) = 2.102924", 2.0 + r.min_noncontact_gap, 2.0 / std::sin(2.0 * std::numbers::pi / 5.0), 1e-6);
            tb::note("icosahedral shell gap: %.6f (in units of the sphere radius)", r.min_noncontact_gap);
        }
    }

    tb::heading("T4 the engine's contact_capacity on 1 <= Z, N <= 40");
    {
        bool eq_iff = true;
        int unequal = 0;
        for (int Z = 1; Z <= 40; ++Z)
            for (int N = 1; N <= 40; ++N) {
                const bool equal = NL::contact_capacity(Z, N) == exact_capacity(Z, N);
                if (equal != (std::max(Z, N) >= 3)) eq_iff = false;
                if (!equal) ++unequal;
            }
        tb::note("unequal cases: %d", unequal);
        tb::check_true("T4", "engine equals exact if and only if max(Z, N) >= 3", eq_iff && unequal == 4);
        tb::check_true("T4", "contact_slots is 3 and a twelve-around-one shell exceeds the cap", NL::contact_slots == 3 && NL::kissing_exceeds_cap(12));
    }

    return tb::finish();
}
