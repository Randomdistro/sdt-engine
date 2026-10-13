// TD01 blank-slate run 3 (2026-10-09): E1b and E3b. Registration: TD01_EXPANSION_2026-10-09.md section 6 (written before this file existed).
//  E1b: N = 9, E = 12 (125970 states), open chain; layer A bonds (0,1),(2,3),(4,5),(6,7); layer B bonds (1,2),(3,4),(5,6),(7,8); rules S (swap), Q1 (k = 1), Q2 (k = max(1, s/2)), a' = (a + k) mod (s+1).
//       Starts A: all 12 quanta in cell 0; B: all in cell 4. Partitions P1' {(0,1),(2,3),(4,5),(6,7),(8)}, P2' {(0,1,2),(3,4,5),(6,7,8)}, P3' {(0),(1,2),(3,4),(5,6),(7,8)}.
//       S_ref = mean macro-entropy over all states. Criterion: orbit mean S >= 0.95 S_ref AND first layer with S >= 0.9 S_ref is <= 3N = 27. H-B' supported iff Q2 meets it for both starts and all partitions.
//       Prediction (fixed before the run): Q2 meets; S and Q1 do not. V6: F is a bijection and conserves E; enumerated ensemble mean equals the closed-form block-sum expectation (1e-9).
//  E3b: late-time relaxation time of R1 (ring) for (N,E) = (4,6),(5,7),(6,9),(7,10),(8,12): evolve until max|p - 1/n| <= 1e-6/n; tau_rel = 50 / ln(d(t-50)/d(t)); slope of ln tau_rel against ln N over the five pairs and
//       over the fixed-density subset N = 4, 6, 8 (E = 1.5 N); supported if the fixed-density slope is in [1.5, 2.5]. Prediction: near 2; t99/tau_rel grows with N.
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <vector>

using St = std::array<int, 12>;
static double lnW(double E, double N) { return std::lgamma(E + N) - std::lgamma(E + 1) - std::lgamma(N); }
static void enumGo(int i, int left, int N, St& s, std::vector<St>& o) { if (i == N - 1) { s[i] = left; o.push_back(s); return; } for (int k = 0; k <= left; ++k) { s[i] = k; enumGo(i + 1, left - k, N, s, o); } }
static std::vector<St> enumerate(int N, int E) { St s{}; std::vector<St> o; enumGo(0, E, N, s, o); return o; }
static long long code(const St& s, int N) { long long c = 0; for (int i = 0; i < N; ++i) c = c * 17 + s[i]; return c; }

struct Part { const char* nm; std::vector<std::vector<int>> blocks; };
static double macro(const St& s, const Part& p) { double r = 0; for (auto& b : p.blocks) { int sum = 0; for (int i : b) sum += s[i]; r += lnW(sum, (double)b.size()); } return r; }
static St layer(const St& x, int parity, int rule, int N) {
    St y = x;
    for (int i = parity; i + 1 < N; i += 2) { int a = x[i], b = x[i + 1], s = a + b, a2; if (rule == 0) a2 = b; else if (rule == 1) a2 = (a + 1) % (s + 1); else a2 = (a + std::max(1, s / 2)) % (s + 1); y[i] = a2; y[i + 1] = s - a2; }
    return y;
}

int main() {
    std::printf("TD01 blank-slate run 3 (registered in TD01_EXPANSION_2026-10-09.md section 6)\n=====================================================================\n\n");
    int fails = 0;
    const int N = 9, E = 12;
    std::vector<St> v = enumerate(N, E); const int n = (int)v.size();
    std::unordered_map<long long, int> id; id.reserve(n * 2); for (int i = 0; i < n; ++i) id[code(v[i], N)] = i;
    std::printf("states: %d (C(20,8) = 125970)\n", n);
    const char* rn[3] = {"S (swap, control)", "Q1 (k = 1)", "Q2 (k = max(1, s/2))"};
    std::vector<int> perm[3];
    { bool ok = true; for (int r = 0; r < 3; ++r) { perm[r].assign(n, -1); std::vector<char> hit(n, 0); bool bij = true, cons = true;
          for (int i = 0; i < n; ++i) { St y = layer(layer(v[i], 0, r, N), 1, r, N); int sum = 0; for (int k = 0; k < N; ++k) sum += y[k]; if (sum != E) cons = false; auto it = id.find(code(y, N)); if (it == id.end()) { bij = false; continue; } perm[r][i] = it->second; if (hit[it->second]) bij = false; hit[it->second] = 1; }
          std::printf("[V6] rule %-22s: F bijective: %s ; conserves E: %s\n", rn[r], bij ? "yes" : "NO", cons ? "yes" : "NO"); ok = ok && bij && cons; }
      if (!ok) ++fails; }
    Part parts[3] = {{"P1' {(0,1),(2,3),(4,5),(6,7),(8)}", {{0, 1}, {2, 3}, {4, 5}, {6, 7}, {8}}}, {"P2' {(0,1,2),(3,4,5),(6,7,8)}", {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}}, {"P3' {(0),(1,2),(3,4),(5,6),(7,8)}", {{0}, {1, 2}, {3, 4}, {5, 6}, {7, 8}}}};
    double Sref[3], Smax[3];
    for (int p = 0; p < 3; ++p) { double sum = 0, mx = 0; for (auto& s : v) { double m = macro(s, parts[p]); sum += m; mx = std::max(mx, m); } Sref[p] = sum / n; Smax[p] = mx;
        // closed-form expectation of the block-sum entropy under the uniform measure over compositions
        double cf = 0; double lnTot = lnW(E, N); for (auto& b : parts[p].blocks) { int m = (int)b.size(); for (int s = 0; s <= E; ++s) { double ln = lnW(s, m) + (N - m > 0 ? lnW(E - s, N - m) : (E - s == 0 ? 0.0 : -1e300)) - lnTot; double pr = std::exp(ln); cf += pr * lnW(s, m); } }
        bool ok = std::fabs(cf - Sref[p]) < 1e-9; std::printf("[V6] %s: enumerated ensemble mean %.6f ; closed form %.6f -> %s ; S_max = %.4f ; S_ref/S_max = %.4f\n", parts[p].nm, Sref[p], cf, ok ? "met" : "NOT MET", Smax[p], Sref[p] / Smax[p]); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n---- E1b (H-B') ----\n");
    St starts[2]; starts[0] = St{}; starts[0][0] = E; starts[1] = St{}; starts[1][4] = E; const char* sn[2] = {"A (cell 0)", "B (cell 4)"};
    bool meets[3][2][3] = {};
    for (int r = 0; r < 3; ++r) {
        std::vector<int> seen(n, 0); int ncyc = 0, longest = 0; for (int i = 0; i < n; ++i) if (!seen[i]) { int len = 0, j = i; while (!seen[j]) { seen[j] = 1; j = perm[r][j]; ++len; } ++ncyc; longest = std::max(longest, len); }
        std::printf("\n  rule %s: cycles of F = %d, longest = %d\n", rn[r], ncyc, longest);
        for (int sidx = 0; sidx < 2; ++sidx) {
            int hid = id[code(starts[sidx], N)]; int L = 0; { int j = hid; do { j = perm[r][j]; ++L; } while (j != hid); }
            std::vector<St> orb; St x = starts[sidx]; orb.push_back(x); for (int k = 0; k < L; ++k) { x = layer(x, 0, r, N); orb.push_back(x); x = layer(x, 1, r, N); orb.push_back(x); } orb.pop_back();
            std::printf("    start %s: orbit length L = %d periods (%d layers)\n", sn[sidx], L, 2 * L);
            for (int p = 0; p < 3; ++p) { double sum = 0; int tfirst = -1; for (size_t t = 0; t < orb.size(); ++t) { double m = macro(orb[t], parts[p]); sum += m; if (tfirst < 0 && m >= 0.9 * Sref[p]) tfirst = (int)t; }
                double mr = sum / orb.size() / Sref[p]; bool ok = mr >= 0.95 && tfirst >= 0 && tfirst <= 3 * N; meets[r][sidx][p] = ok;
                std::printf("      %-34s: start S/S_ref = %.4f ; orbit mean S/S_ref = %.4f ; first layer with S >= 0.9 S_ref: %d (limit %d) -> %s\n", parts[p].nm, macro(starts[sidx], parts[p]) / Sref[p], mr, tfirst, 3 * N, ok ? "criterion met" : "criterion NOT met"); }
        }
    }
    bool HBp = true; for (int sidx = 0; sidx < 2; ++sidx) for (int p = 0; p < 3; ++p) if (!meets[2][sidx][p]) HBp = false;
    bool anyS = false, anyQ1 = false; for (int sidx = 0; sidx < 2; ++sidx) for (int p = 0; p < 3; ++p) { if (meets[0][sidx][p]) anyS = true; if (meets[1][sidx][p]) anyQ1 = true; }
    std::printf("\n  H-B' (Q2 meets for both starts and all partitions): %s ; control S meets in some case: %s ; Q1 meets in some case: %s\n\n", HBp ? "SUPPORTED" : "NOT supported", anyS ? "yes" : "no", anyQ1 ? "yes" : "no");

    // ---------------- E3b
    std::printf("---- E3b (H-A'): late-time relaxation time of the symmetric stochastic relay on a ring ----\n");
    struct NE { int N, E; } cases[5] = {{4, 6}, {5, 7}, {6, 9}, {7, 10}, {8, 12}};
    double tau[5], t99s[5], lx[5];
    for (int c = 0; c < 5; ++c) {
        int Nn = cases[c].N, En = cases[c].E; std::vector<St> w = enumerate(Nn, En); int m = (int)w.size(); std::unordered_map<long long, int> idw; idw.reserve(m * 2); for (int i = 0; i < m; ++i) idw[code(w[i], Nn)] = i;
        int K = 2 * Nn; std::vector<int> tg((size_t)m * K);
        for (int s = 0; s < m; ++s) { int k = 0; for (int b = 0; b < Nn; ++b) for (int d = 0; d < 2; ++d, ++k) { St x = w[s]; int from = d ? (b + 1) % Nn : b, to = d ? b : (b + 1) % Nn; int t = s; if (x[from] > 0) { --x[from]; ++x[to]; t = idw[code(x, Nn)]; } tg[(size_t)s * K + k] = t; } }
        St h{}; h[0] = En; std::vector<double> p(m, 0.0), q(m); p[idw[code(h, Nn)]] = 1.0; double Seq = std::log((double)m); int t99 = -1; std::vector<double> dh; dh.push_back(1.0); double u = 1.0 / m;
        for (int t = 1; t <= 400000; ++t) { std::fill(q.begin(), q.end(), 0.0); for (int s = 0; s < m; ++s) { double ww = p[s] / K; if (ww == 0) continue; for (int k = 0; k < K; ++k) q[tg[(size_t)s * K + k]] += ww; } p.swap(q);
            double Sx = 0, d = 0; for (double a : p) { if (a > 0) Sx -= a * std::log(a); d = std::max(d, std::fabs(a - u)); } if (t99 < 0 && Sx >= 0.99 * Seq) t99 = t; dh.push_back(d); if (d <= 1e-6 * u) break; }
        int T = (int)dh.size() - 1; tau[c] = 50.0 / std::log(dh[T - 50] / dh[T]); t99s[c] = t99; lx[c] = std::log((double)Nn);
        std::printf("  N = %d, E = %2d, %5d states: t99 = %d ; ticks to max|p - 1/n| <= 1e-6/n: %d ; tau_rel = %.2f ; t99/tau_rel = %.3f\n", Nn, En, m, t99, T, tau[c], t99 / tau[c]);
    }
    { double mx = 0, my = 0; for (int c = 0; c < 5; ++c) { mx += lx[c]; my += std::log(tau[c]); } mx /= 5; my /= 5; double sxy = 0, sxx = 0; for (int c = 0; c < 5; ++c) { sxy += (lx[c] - mx) * (std::log(tau[c]) - my); sxx += (lx[c] - mx) * (lx[c] - mx); }
      std::printf("  slope of ln tau_rel against ln N (all five pairs, density not fixed) = %.3f\n", sxy / sxx); }
    double e1 = std::log(tau[2] / tau[0]) / std::log(6.0 / 4.0), e2 = std::log(tau[4] / tau[2]) / std::log(8.0 / 6.0), ef = std::log(tau[4] / tau[0]) / std::log(2.0);
    std::printf("  fixed density E = 1.5 N (N = 4, 6, 8): exponents 4->6: %.3f ; 6->8: %.3f ; 4->8: %.3f\n", e1, e2, ef);
    std::printf("  H-A' (fixed-density exponent 4->8 in [1.5, 2.5]): %s\n", (ef >= 1.5 && ef <= 2.5) ? "SUPPORTED" : "EXCLUDED");
    return 0;
}
