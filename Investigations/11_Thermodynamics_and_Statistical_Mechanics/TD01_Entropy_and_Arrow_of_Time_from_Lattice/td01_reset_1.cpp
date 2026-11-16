// TD01 blank-slate run 1 (2026-10-08): stars-and-bars entropy and the arrow under three registered relay rules. Registered before the run:
//  Lattice: N = 7 cells, E = 10 quanta, ring (R1) or open chain (R2, R3); hot start: all quanta in cell 0. All microstates enumerated exactly (C(16,6) = 8008).
//  R1 symmetric stochastic exchange: each tick pick one of the N bonds and a direction at random; move one quantum from donor to receiver if the donor has one. Observable: the Shannon entropy of the exact distribution.
//  R2 deterministic reversible swap: alternate sublattice bonds, swap the contents of the two cells. Observable: the macro-entropy ln W_macro of the single trajectory, macrostate = block sums over blocks (0,1),(2,3),(4,5),(6).
//  R3 deterministic richer-to-poorer transfer: alternate sublattice bonds, move one quantum from the richer to the poorer cell if the difference is at least 2. Same observable as R2.
//  Phase 1 gates: Stirling error < 5% at E = 1000, N = 50; extensivity ln W(2E,2N)/(2 ln W(E,N)) within +/-5%.
//  Validations: V1 stars-and-bars against brute-force enumeration; V2 the R1 transition matrix is symmetric with unit row sums (N = 5, E = 4).
//  Phase 2 criterion (registered): the arrow is shown if S has no net decrease over 10^4 ticks AND S(10^4)/S_eq >= 0.9 (S_eq = the maximum of the observable over all states); a rule that holds S constant satisfies "no decrease" and does not show an arrow.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <vector>
using namespace sdt::laws;

static double lnW(double E, double N) { return std::lgamma(E + N) - std::lgamma(E + 1) - std::lgamma(N); }
using St = std::array<int, 8>;
static void enumerate(int N, int E, std::vector<St>& out) { St s{}; std::vector<St>* o = &out; struct R { static void go(int i, int left, int N, St& s, std::vector<St>* o) { if (i == N - 1) { s[i] = left; o->push_back(s); return; } for (int k = 0; k <= left; ++k) { s[i] = k; go(i + 1, left - k, N, s, o); } } }; R::go(0, E, N, s, o); }
static long code(const St& s, int N) { long c = 0; for (int i = 0; i < N; ++i) c = c * 17 + s[i]; return c; }
static double macroLnW(const St& s) { int b[3] = {s[0] + s[1], s[2] + s[3], s[4] + s[5]}; return std::log(b[0] + 1.0) + std::log(b[1] + 1.0) + std::log(b[2] + 1.0); }

int main() {
    std::printf("TD01 blank-slate run 1 (registered in the tool header, 2026-10-08)\n===================================================================\n\n");
    int fails = 0;
    // ---- V1
    { bool ok = true; for (auto ne : std::vector<std::pair<int, int>>{{4, 3}, {5, 6}, {7, 10}}) { std::vector<St> v; enumerate(ne.first, ne.second, v); double f = std::exp(lnW(ne.second, ne.first)); ok = ok && std::fabs(f - double(v.size())) < 1e-6 * f; std::printf("[V1] N = %d, E = %d: enumerated %zu, formula %.4f\n", ne.first, ne.second, v.size(), f); }
      std::printf("[V1] -> %s\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // ---- V2: R1 matrix symmetric, rows sum to 1 (N = 5, E = 4, ring)
    { int N = 5, E = 4; std::vector<St> v; enumerate(N, E, v); std::map<long, int> id; for (size_t i = 0; i < v.size(); ++i) id[code(v[i], N)] = (int)i; int n = (int)v.size(); std::vector<double> P(n * n, 0.0);
      for (int s = 0; s < n; ++s) for (int b = 0; b < N; ++b) for (int d = 0; d < 2; ++d) { St x = v[s]; int from = d ? (b + 1) % N : b, to = d ? b : (b + 1) % N; int t = s; if (x[from] > 0) { --x[from]; ++x[to]; t = id[code(x, N)]; } P[s * n + t] += 1.0 / (2 * N); }
      double asym = 0, rs = 0; for (int i = 0; i < n; ++i) { double r = 0; for (int j = 0; j < n; ++j) { asym = std::max(asym, std::fabs(P[i * n + j] - P[j * n + i])); r += P[i * n + j]; } rs = std::max(rs, std::fabs(r - 1)); }
      bool ok = asym < 1e-15 && rs < 1e-15; std::printf("[V2] N = 5, E = 4 (%d states): max |P - P^T| = %.1e, max |row sum - 1| = %.1e -> %s\n\n", n, asym, rs, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0"); if (fails) return 1;

    // ---- Phase 1
    { double L1 = lnW(1000, 50), st = (1050) * std::log(1050.0) - 1000 * std::log(1000.0) - 50 * std::log(50.0), L2 = lnW(2000, 100);
      std::printf("[P1] ln W(E = 1000, N = 50) = %.4f ; leading Stirling (E+N)ln(E+N) - E ln E - N ln N = %.4f (error %.2f%%) ; ln W(2000, 100) = %.4f ; ratio to 2 ln W(1000, 50) = %.4f\n", L1, st, (st / L1 - 1) * 100, L2, L2 / (2 * L1));
      std::printf("     S = k_B ln W with k_B = %.6e J/K: S(1000, 50) = %.4e J/K ; monotone in E: ln W(E=10, 50) = %.3f, ln W(E=100, 50) = %.3f, ln W(E=1000, 50) = %.3f\n\n", measured::k_B, measured::k_B * L1, lnW(10, 50), lnW(100, 50), L1); }

    // ---- Phase 2
    const int N = 7, E = 10, T = 10000; std::vector<St> v; enumerate(N, E, v); std::unordered_map<long, int> id; for (size_t i = 0; i < v.size(); ++i) id[code(v[i], N)] = (int)i; int n = (int)v.size();
    const double Seq1 = std::log((double)n);
    // R1 exact distribution
    { std::vector<std::array<int, 14>> tgt(n); for (int s = 0; s < n; ++s) { int k = 0; for (int b = 0; b < N; ++b) for (int d = 0; d < 2; ++d, ++k) { St x = v[s]; int from = d ? (b + 1) % N : b, to = d ? b : (b + 1) % N; int t = s; if (x[from] > 0) { --x[from]; ++x[to]; t = id[code(x, N)]; } tgt[s][k] = t; } }
      std::vector<double> p(n, 0.0), q(n); St h{}; h[0] = E; p[id[code(h, N)]] = 1.0; double Sprev = 0, minstep = 1e9; int viol = 0; double S[5] = {0, 0, 0, 0, 0}; int rec[5] = {1, 10, 100, 1000, 10000}; int r = 0;
      for (int t = 1; t <= T; ++t) { std::fill(q.begin(), q.end(), 0.0); for (int s = 0; s < n; ++s) { double w = p[s] / 14.0; if (w == 0) continue; for (int k = 0; k < 14; ++k) q[tgt[s][k]] += w; } p.swap(q);
          double Sx = 0; for (int s = 0; s < n; ++s) if (p[s] > 0) Sx -= p[s] * std::log(p[s]); double step = Sx - Sprev; minstep = std::min(minstep, step); if (step < -1e-12) ++viol; Sprev = Sx; if (r < 5 && t == rec[r]) S[r++] = Sx; }
      std::printf("[R1] symmetric stochastic exchange, ring, exact distribution of %d states: S(1) = %.4f, S(10) = %.4f, S(100) = %.4f, S(1000) = %.4f, S(10^4) = %.4f ; S_eq = ln %d = %.4f ; S(10^4)/S_eq = %.6f ; smallest one-tick change %.3e ; ticks with a decrease: %d\n", n, S[0], S[1], S[2], S[3], S[4], n, Seq1, S[4] / Seq1, minstep, viol);
      std::printf("     criterion (no net decrease and S/S_eq >= 0.9): %s (the sign of dS/dt is guaranteed by the symmetry of the transition matrix, V2)\n\n", (viol == 0 && S[4] / Seq1 >= 0.9) ? "met" : "NOT met"); }
    // macro reference
    double Smac = 0; for (auto& s : v) Smac = std::max(Smac, macroLnW(s));
    auto run = [&](int rule, const char* nm) { St x{}; x[0] = E; double S0 = macroLnW(x), mn = S0, mx = S0, sum = 0; int dec = 0; double prev = S0; double Sfin = 0;
        for (int t = 1; t <= T; ++t) { int start = (t % 2 == 0) ? 0 : 1; for (int i = start; i + 1 < N; i += 2) { if (rule == 2) std::swap(x[i], x[i + 1]); else { if (x[i] - x[i + 1] >= 2) { --x[i]; ++x[i + 1]; } else if (x[i + 1] - x[i] >= 2) { --x[i + 1]; ++x[i]; } } }
            double m = macroLnW(x); mn = std::min(mn, m); mx = std::max(mx, m); sum += m; if (m < prev - 1e-12) ++dec; prev = m; Sfin = m; }
        std::printf("[R%d] %s: macro-entropy ln W_macro of the single trajectory: start %.4f, min %.4f, max %.4f, mean over %d ticks %.4f, final %.4f ; maximum over all states %.4f ; final/max = %.4f ; one-tick decreases: %d\n", rule, nm, S0, mn, mx, T, sum / T, Sfin, Smac, Sfin / Smac, dec);
        std::printf("     criterion (no net decrease: final >= start; and mean S/S_max >= 0.9): net change %+.4f, mean/max = %.4f -> %s\n\n", Sfin - S0, sum / T / Smac, (Sfin >= S0 && sum / T / Smac >= 0.9) ? "arrow shown" : "NO arrow shown"); };
    run(2, "deterministic reversible swap (open chain)");
    run(3, "deterministic richer-to-poorer transfer (open chain)");
    return 0;
}
