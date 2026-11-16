// TD01 blank-slate run 2 (2026-10-09): expansion experiments E1-E4. Registration: TD01_EXPANSION_2026-10-09.md section 4 (fixed before this file existed).
//  Lattice N = 7, E = 10, 8008 microstates; hot start: all quanta in cell 0 (E3, E4 as registered).
//  E1 (H-B): open chain, layers alternate bond sets {(0,1),(2,3),(4,5)} and {(1,2),(3,4),(5,6)}; bond (a, s-a) -> (a', s-a'), a' = (a + k_s) mod (s+1);
//       Q1: k_s = 1; Q2: k_s = max(1, floor(s/2)); control S: swap. F = (odd layer) o (even layer) acts as a permutation of the 8008 states.
//       Partitions P1 {(0,1),(2,3),(4,5),(6)}, P2 {(0,1,2),(3,4,5),(6)}, P3 {(0),(1,2),(3,4),(5,6)}; macro-entropy sum over blocks of ln C(s_b + |b| - 1, |b| - 1); S_max over all states.
//       Arrow criterion per (rule, partition): mean over the hot-start orbit (layer by layer) of S/S_max >= 0.9 AND S first reaches 0.9 S_max within L/10 layers (L = orbit length of F in periods).
//       H-B supported iff Q1 or Q2 meets it for all three partitions. V3: F is a bijection of the 8008 states and conserves E.
//  E2 (H-C): ring Metropolis exchange, 14 (bond, direction) options chosen uniformly, accept min(1, pi(y)/pi(x)), pi ~ exp(beta sum x^2 / E), beta in {0, 0.05, 0.2, 0.5}; 2000 ticks of the exact
//       distribution from the uniform and the hot start. Criterion: KL(p_t || pi) never increases by more than 1e-12; for beta > 0 from the uniform start S(2000) < S(0) and S_stat < ln 8008.
//       V4: detailed balance to 1e-14 (relative to pi_s/14), and max |p - pi| < 1e-6 at 2000 ticks for beta = 0.5 from the hot start.
//  E3 (H-A): R1 (ring, 2N options, 1/(2N) each) exact for (N,E) = (4,6),(5,7),(6,9),(7,10),(8,12) from the hot start; t99 = first tick with S >= 0.99 S_eq; slope of ln t99 against ln N in [1.5, 2.5] supports N^2 scaling.
//  E4 (H-D): arithmetic for V = 1 m^3 of CMB with N = E = V / l_P^3 (eps = u l_P^3): S_sb, T_sb, S_th = 4u/(3T), T_CMB, ratios, n_gamma, entropy per photon, N_eff. Consistent iff S_sb / S_th <= 10.
//       V5: S_th / (k n_gamma) equals 2 pi^4 / (45 zeta(3)) to 1e-3.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <numbers>
#include <unordered_map>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

using St = std::array<int, 8>;
static double lnW(double E, double N) { return std::lgamma(E + N) - std::lgamma(E + 1) - std::lgamma(N); }
static void enumGo(int i, int left, int N, St& s, std::vector<St>& o) { if (i == N - 1) { s[i] = left; o.push_back(s); return; } for (int k = 0; k <= left; ++k) { s[i] = k; enumGo(i + 1, left - k, N, s, o); } }
static std::vector<St> enumerate(int N, int E) { St s{}; std::vector<St> o; enumGo(0, E, N, s, o); return o; }
static long long code(const St& s, int N) { long long c = 0; for (int i = 0; i < N; ++i) c = c * 17 + s[i]; return c; }

// ---------------- E1 machinery
struct Part { const char* nm; std::vector<std::vector<int>> blocks; };
static double macro(const St& s, const Part& p) { double r = 0; for (auto& b : p.blocks) { int sum = 0; for (int i : b) sum += s[i]; r += lnW(sum, (double)b.size()); } return r; }
static St layer(const St& x, int parity, int rule) {
    St y = x;
    for (int i = parity; i + 1 < 7; i += 2) {
        int a = x[i], b = x[i + 1], s = a + b, a2;
        if (rule == 0) a2 = b; else if (rule == 1) a2 = (a + 1) % (s + 1); else a2 = (a + std::max(1, s / 2)) % (s + 1);
        y[i] = a2; y[i + 1] = s - a2;
    }
    return y;
}

int main(int argc, char** argv) {
    const int T2 = argc > 1 ? std::atoi(argv[1]) : 2000;   // Amendment 1 (2026-10-09): E2 tick count is an argument; registered default 2000; gates unchanged
    std::printf("TD01 blank-slate run 2 (registered in TD01_EXPANSION_2026-10-09.md section 4)\n=====================================================================\n\n");
    const int N = 7, E = 10;
    std::vector<St> v = enumerate(N, E); const int n = (int)v.size();
    std::unordered_map<long long, int> id; for (int i = 0; i < n; ++i) id[code(v[i], N)] = i;
    St hot{}; hot[0] = E; const int hotId = id[code(hot, N)];
    const double lnn = std::log((double)n);
    int fails = 0;

    // ======== V3 and E1
    const char* rn[3] = {"S (swap, control)", "Q1 (k = 1)", "Q2 (k = max(1, s/2))"};
    std::vector<int> perm[3];
    { bool ok = true;
      for (int r = 0; r < 3; ++r) { perm[r].assign(n, -1); std::vector<char> hit(n, 0); bool bij = true, cons = true;
          for (int i = 0; i < n; ++i) { St y = layer(layer(v[i], 0, r), 1, r); int sum = 0; for (int k = 0; k < N; ++k) sum += y[k]; if (sum != E) cons = false; auto it = id.find(code(y, N)); if (it == id.end()) { bij = false; continue; } perm[r][i] = it->second; if (hit[it->second]) bij = false; hit[it->second] = 1; }
          std::printf("[V3] rule %-22s: F bijective on %d states: %s ; conserves E: %s\n", rn[r], n, bij ? "yes" : "NO", cons ? "yes" : "NO"); ok = ok && bij && cons; }
      std::printf("[V3] -> %s\n\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }

    // ======== V4 (needs E2 machinery) -- build ring targets once
    std::vector<std::array<int, 14>> tgt(n);
    for (int s = 0; s < n; ++s) { int k = 0; for (int b = 0; b < N; ++b) for (int d = 0; d < 2; ++d, ++k) { St x = v[s]; int from = d ? (b + 1) % N : b, to = d ? b : (b + 1) % N; int t = -1; if (x[from] > 0) { --x[from]; ++x[to]; t = id[code(x, N)]; } tgt[s][k] = t; } }
    const double betas[4] = {0.0, 0.05, 0.2, 0.5};
    std::vector<double> pis[4];
    for (int bi = 0; bi < 4; ++bi) { pis[bi].assign(n, 0.0); double Z = 0; for (int s = 0; s < n; ++s) { double q = 0; for (int i = 0; i < N; ++i) q += (double)v[s][i] * v[s][i]; pis[bi][s] = std::exp(betas[bi] * q / E); Z += pis[bi][s]; } for (int s = 0; s < n; ++s) pis[bi][s] /= Z; }
    { double dbmax = 0; for (int bi = 0; bi < 4; ++bi) for (int s = 0; s < n; ++s) for (int k = 0; k < 14; ++k) { int t = tgt[s][k]; if (t < 0) continue; double Pst = std::min(1.0, pis[bi][t] / pis[bi][s]) / 14.0, Pts = std::min(1.0, pis[bi][s] / pis[bi][t]) / 14.0; double d = std::fabs(pis[bi][s] * Pst - pis[bi][t] * Pts) / (pis[bi][s] / 14.0); dbmax = std::max(dbmax, d); }
      bool ok = dbmax < 1e-14; std::printf("[V4a] detailed balance, max relative violation over all beta, states, options: %.2e -> %s\n", dbmax, ok ? "met" : "NOT MET"); if (!ok) ++fails; }

    // ======== V5 (E4 validation)
    const double PI = std::numbers::pi, zeta3 = 1.2020569031595943;
    const double T = M::T_CMB, u = law_I::u_CMB, kB = M::k_B;
    const double S_th = 4.0 * u / (3.0 * T);                                        // J/K per m^3
    const double n_gam = (2.0 * zeta3 / (PI * PI)) * std::pow(kB * T / (M::hbar * M::c), 3.0);
    const double sph = S_th / (kB * n_gam), sph_formula = 2.0 * std::pow(PI, 4.0) / (45.0 * zeta3);
    { bool ok = std::fabs(sph / sph_formula - 1) < 1e-3; std::printf("[V5] entropy per photon from the engine's u_CMB and T_CMB: %.5f ; 2 pi^4/(45 zeta3) = %.5f ; relative %.2e -> %s\n\n", sph, sph_formula, sph / sph_formula - 1, ok ? "met" : "NOT MET"); if (!ok) ++fails; }

    // ======== E1
    std::printf("---- E1 (H-B): reversible deterministic layers, coarse-grained arrow ----\n");
    Part parts[3] = {{"P1 {(0,1),(2,3),(4,5),(6)}", {{0, 1}, {2, 3}, {4, 5}, {6}}}, {"P2 {(0,1,2),(3,4,5),(6)}", {{0, 1, 2}, {3, 4, 5}, {6}}}, {"P3 {(0),(1,2),(3,4),(5,6)}", {{0}, {1, 2}, {3, 4}, {5, 6}}}};
    double Smax[3]; double Seqmean[3];
    for (int p = 0; p < 3; ++p) { Smax[p] = 0; Seqmean[p] = 0; for (auto& s : v) { double m = macro(s, parts[p]); Smax[p] = std::max(Smax[p], m); Seqmean[p] += m; } Seqmean[p] /= n; std::printf("  %s: S_max = %.4f ; uniform-ensemble mean S = %.4f (ratio %.4f)\n", parts[p].nm, Smax[p], Seqmean[p], Seqmean[p] / Smax[p]); }
    bool meets[3][3] = {};
    for (int r = 0; r < 3; ++r) {
        std::vector<int> cyc(n, -1); int ncyc = 0, longest = 0, fixed = 0; for (int i = 0; i < n; ++i) if (cyc[i] < 0) { int len = 0, j = i; while (cyc[j] < 0) { cyc[j] = ncyc; j = perm[r][j]; ++len; } ++ncyc; longest = std::max(longest, len); if (len == 1) ++fixed; }
        int L = 0; { int j = hotId; do { j = perm[r][j]; ++L; } while (j != hotId); }
        std::printf("\n  rule %s: cycles of F = %d, longest = %d, fixed points = %d ; hot-start orbit length L = %d periods (%d layers)\n", rn[r], ncyc, longest, fixed, L, 2 * L);
        // orbit states layer by layer
        std::vector<St> orb; St x = hot; orb.push_back(x); for (int k = 0; k < L; ++k) { x = layer(x, 0, r); orb.push_back(x); x = layer(x, 1, r); orb.push_back(x); } orb.pop_back();   // last state equals the start
        for (int p = 0; p < 3; ++p) { double sum = 0, mx = 0; int tfirst = -1; for (size_t t = 0; t < orb.size(); ++t) { double m = macro(orb[t], parts[p]); sum += m; mx = std::max(mx, m); if (tfirst < 0 && m >= 0.9 * Smax[p]) tfirst = (int)t; }
            double mr = sum / orb.size() / Smax[p]; bool ok = mr >= 0.9 && tfirst >= 0 && tfirst <= L / 10.0; meets[r][p] = ok;
            std::printf("    %-28s: start S = %.4f ; orbit mean S/S_max = %.4f ; max S/S_max = %.4f ; first layer with S >= 0.9 S_max: %d ; L/10 = %.1f -> %s\n", parts[p].nm, macro(hot, parts[p]), mr, mx / Smax[p], tfirst, L / 10.0, ok ? "criterion met" : "criterion NOT met"); }
    }
    bool HB = false; for (int r = 1; r <= 2; ++r) if (meets[r][0] && meets[r][1] && meets[r][2]) HB = true;
    std::printf("\n  H-B (Q1 or Q2 meets the criterion for all three partitions): %s\n\n", HB ? "SUPPORTED" : "NOT supported");

    // ======== E2
    std::printf("---- E2 (H-C): Metropolis exchange with a non-uniform stationary measure ----\n");
    bool HC = true; double v4b = -1;
    for (int bi = 0; bi < 4; ++bi) for (int st = 0; st < 2; ++st) {
        const std::vector<double>& pi = pis[bi]; std::vector<double> p(n, 0.0), q(n);
        if (st == 0) std::fill(p.begin(), p.end(), 1.0 / n); else p[hotId] = 1.0;
        auto Sof = [&](const std::vector<double>& d) { double s = 0; for (double a : d) if (a > 0) s -= a * std::log(a); return s; };
        auto KLof = [&](const std::vector<double>& d) { double s = 0; for (int i = 0; i < n; ++i) if (d[i] > 0) s += d[i] * std::log(d[i] / pi[i]); return s; };
        double S0 = Sof(p), KL0 = KLof(p), Sprev = S0, KLprev = KL0, Smin = S0, Smax_ = S0; int tmin = 0, klviol = 0, sdec = 0; double worst = 0, mass = 0;
        for (int t = 1; t <= T2; ++t) { std::fill(q.begin(), q.end(), 0.0);
            for (int s = 0; s < n; ++s) { double w = p[s] / 14.0; if (w == 0) continue; for (int k = 0; k < 14; ++k) { int tt = tgt[s][k]; if (tt < 0) { q[s] += w; continue; } double acc = std::min(1.0, pi[tt] / pi[s]); q[tt] += w * acc; q[s] += w * (1 - acc); } }
            p.swap(q); double Sx = Sof(p), KL = KLof(p); if (KL > KLprev + 1e-12) { ++klviol; worst = std::max(worst, KL - KLprev); } if (Sx < Sprev - 1e-12) ++sdec; if (Sx < Smin) { Smin = Sx; tmin = t; } Smax_ = std::max(Smax_, Sx); Sprev = Sx; KLprev = KL; }
        double tot = 0; for (double a : p) tot += a; mass = tot - 1;
        double Sstat = Sof(pi), dmax = 0; for (int i = 0; i < n; ++i) dmax = std::max(dmax, std::fabs(p[i] - pi[i]));
        if (bi == 3 && st == 1) v4b = dmax;
        bool okKL = klviol == 0, okS = (betas[bi] == 0.0) || st == 1 || (Sprev < S0 && Sstat < lnn);
        if (!(okKL && okS)) HC = false;
        std::printf("  [T = %d] beta = %.2f, %-7s start: S(0) = %.4f, S(T) = %.4f, S_stat = %.4f (ln 8008 = %.4f) ; S min %.4f at t = %d, max %.4f ; KL(0) = %.4e, KL(T) = %.3e ; KL increases > 1e-12: %d (worst %.1e) ; S decreasing ticks: %d ; max|p-pi| = %.2e ; mass err %.1e -> %s\n",
                    T2, betas[bi], st == 0 ? "uniform" : "hot", S0, Sprev, Sstat, lnn, Smin, tmin, Smax_, KL0, KLprev, klviol, worst, sdec, dmax, mass, (okKL && okS) ? "criterion met" : "criterion NOT met");
    }
    { bool ok = v4b < 1e-6; std::printf("[V4b] beta = 0.5, hot start, max |p - pi| at T = %d ticks = %.2e (gate 1e-6) -> %s\n", T2, v4b, ok ? "met" : "NOT MET"); if (!ok) { ++fails; HC = false; } }
    std::printf("  H-C: %s\n\n", HC ? "SUPPORTED (given V4)" : "NOT supported / validation unmet");

    // ======== E3
    std::printf("---- E3 (H-A): relaxation time of the symmetric stochastic relay on a ring ----\n");
    struct NE { int N, E; } cases[5] = {{4, 6}, {5, 7}, {6, 9}, {7, 10}, {8, 12}};
    double lx[5], ly[5];
    for (int c = 0; c < 5; ++c) {
        int Nn = cases[c].N, En = cases[c].E; std::vector<St> w = enumerate(Nn, En); int m = (int)w.size(); std::unordered_map<long long, int> idw; for (int i = 0; i < m; ++i) idw[code(w[i], Nn)] = i;
        int K = 2 * Nn; std::vector<int> tg((size_t)m * K);
        for (int s = 0; s < m; ++s) { int k = 0; for (int b = 0; b < Nn; ++b) for (int d = 0; d < 2; ++d, ++k) { St x = w[s]; int from = d ? (b + 1) % Nn : b, to = d ? b : (b + 1) % Nn; int t = s; if (x[from] > 0) { --x[from]; ++x[to]; t = idw[code(x, Nn)]; } tg[(size_t)s * K + k] = t; } }
        St h{}; h[0] = En; std::vector<double> p(m, 0.0), q(m); p[idw[code(h, Nn)]] = 1.0; double Seq = std::log((double)m); int t99 = -1;
        for (int t = 1; t <= 200000 && t99 < 0; ++t) { std::fill(q.begin(), q.end(), 0.0); for (int s = 0; s < m; ++s) { double ww = p[s] / K; if (ww == 0) continue; for (int k = 0; k < K; ++k) q[tg[(size_t)s * K + k]] += ww; } p.swap(q); double Sx = 0; for (double a : p) if (a > 0) Sx -= a * std::log(a); if (Sx >= 0.99 * Seq) t99 = t; }
        std::printf("  N = %d, E = %2d, %5d states: t99 = %d\n", Nn, En, m, t99); lx[c] = std::log((double)Nn); ly[c] = std::log((double)t99);
    }
    double mx = 0, my = 0; for (int c = 0; c < 5; ++c) { mx += lx[c]; my += ly[c]; } mx /= 5; my /= 5; double sxy = 0, sxx = 0; for (int c = 0; c < 5; ++c) { sxy += (lx[c] - mx) * (ly[c] - my); sxx += (lx[c] - mx) * (lx[c] - mx); }
    double slope = sxy / sxx; std::printf("  least-squares slope of ln t99 against ln N = %.3f ; pairwise exponents:", slope); for (int c = 1; c < 5; ++c) std::printf(" %.2f", (ly[c] - ly[c - 1]) / (lx[c] - lx[c - 1])); std::printf("\n  H-A time scale (slope in [1.5, 2.5]): %s\n\n", (slope >= 1.5 && slope <= 2.5) ? "SUPPORTED" : "EXCLUDED");

    // ======== E4
    std::printf("---- E4 (H-D): Planck-cell stars-and-bars lattice against the thermodynamic entropy of 1 m^3 of CMB ----\n");
    const double V = 1.0, lP3 = M::l_P * M::l_P * M::l_P, Ncell = V / lP3, eps = law_I::epsilon, Equanta = u * V / eps;
    const double S_sb = 2.0 * Ncell * std::log(2.0);                                  // in units of k_B (leading term, occupancy 1)
    const double T_sb = eps / (kB * std::log(2.0));
    const double S_th_kB = S_th / kB, Neff = S_th_kB / (2.0 * std::log(2.0));
    std::printf("  eps = u l_P^3 = %.4e J (engine law_I::epsilon %.4e) ; N = V/l_P^3 = %.4e cells ; E = uV/eps = %.4e quanta (E/N = %.4f)\n", u * lP3, eps, Ncell, Equanta, Equanta / Ncell);
    std::printf("  S_sb = 2 N ln2 = %.4e k_B ; T_sb = eps/(k_B ln2) = %.4e K\n", S_sb, T_sb);
    std::printf("  S_th = 4u/(3T) = %.4e J/K = %.4e k_B ; T_CMB = %.4f K ; n_gamma = %.4e m^-3 ; entropy per photon = %.4f k_B\n", S_th, S_th_kB, T, n_gam, sph);
    std::printf("  ratios: S_sb / S_th = %.4e ; T_CMB / T_sb = %.4e ; S_sb T_sb = %.4e J (2E eps = %.4e) ; S_th T = %.4e J (4/3 E_tot = %.4e)\n", S_sb / S_th_kB, T / T_sb, S_sb * kB * T_sb, 2.0 * Equanta * eps, S_th * T, 4.0 / 3.0 * u * V);
    std::printf("  requirement: N_eff with E = N_eff matching S_th: %.4e per m^3 ; cell side %.4e m ; photon density gives %.4e per m^3\n", Neff, std::cbrt(1.0 / Neff), n_gam);
    std::printf("  consistent within a factor 10 (S_sb/S_th <= 10): %s\n\n", S_sb / S_th_kB <= 10.0 ? "YES" : "NO -- the overcount is reported");

    std::printf("VALIDATIONS: %s\n", fails == 0 ? "all met" : "NOT ALL MET -> G0 for the affected experiment");
    return 0;
}
