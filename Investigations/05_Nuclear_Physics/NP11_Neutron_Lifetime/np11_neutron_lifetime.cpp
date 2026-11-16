// NP11 — neutron lifetime: data audit (Part C), attempt-frequency ambiguity (A1),
// look-elsewhere census of natural constructions for the barrier depth (A2), and the
// Law V per-tick candidate (A3).
// Pre-registration: PROMPT.md, section "Pre-registration (2026-10-03)".
// Build: cl /std:c++20 /EHsc /O2 /I Engine\include np11_neutron_lifetime.cpp
#include <sdt/laws.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <random>
#include <string>
#include <vector>

namespace {
namespace m = sdt::laws::measured;
constexpr double pi = 3.14159265358979323846;

bool near(double a, double b, double rel) { return std::fabs(a - b) <= rel * std::fabs(b); }

struct Meas { const char* name; double tau, sigma; };
// MEASURED-INPUT, transcribed from secondary summaries (primary papers not retrieved).
constexpr Meas bottle{"bottle (world average)", 877.8, 0.3};
constexpr Meas beam_old{"earlier beams", 888.1, 2.0};
const Meas beam_jparc{"J-PARC beam (2024)", 877.2, std::sqrt(1.7 * 1.7 + 3.8 * 3.8)};

struct Diff { double d, s; };
Diff diff(const Meas& a, const Meas& b) { return {a.tau - b.tau, std::sqrt(a.sigma * a.sigma + b.sigma * b.sigma)}; }
Meas wmean(const Meas& a, const Meas& b, const char* name) {
    const double wa = 1.0 / (a.sigma * a.sigma), wb = 1.0 / (b.sigma * b.sigma);
    return {name, (wa * a.tau + wb * b.tau) / (wa + wb), std::sqrt(1.0 / (wa + wb))};
}

struct Clock { std::string name; double t; bool nuclear; };

// Analytic expected number of hits for nX independent ln X ~ U[lo,hi], k = 1..kmax, window |k lnX - B| <= w.
double analytic_expected(double B, double w, double lo, double hi, int kmax, int nX) {
    double s = 0.0;
    for (int k = 1; k <= kmax; ++k) {
        const double a = std::max(lo, (B - w) / k), b = std::min(hi, (B + w) / k);
        if (b > a) s += (b - a) / (hi - lo);
    }
    return nX * s;
}

int validate() {
    int fail = 0;
    auto check = [&](const char* what, bool ok) {
        std::printf("  [%s] %s\n", ok ? "ok" : "FAIL", what);
        if (!ok) ++fail;
    };
    std::printf("INSTRUMENT VALIDATION (known answers; physics parts not yet run)\n");
    char buf[160];
    {
        const Meas a{"a", 10.0, 1.0}, b{"b", 12.0, 2.0};
        const Meas w = wmean(a, b, "w");
        const Diff d = diff(b, a);
        std::snprintf(buf, sizeof buf, "V1 weighted mean %.6f (expect 10.4), sigma %.6f (expect 0.894427), difference %.3f +/- %.6f (expect 2 +/- 2.236068)", w.tau, w.sigma, d.d, d.s);
        check(buf, near(w.tau, 10.4, 1e-12) && near(w.sigma, std::sqrt(0.8), 1e-12) && near(d.d, 2.0, 1e-12) && near(d.s, std::sqrt(5.0), 1e-12));
    }
    {
        const double t_c = m::hbar / (m::m_e * m::c * m::c), t_p = m::R_p / m::c;
        std::snprintf(buf, sizeof buf, "V2 hbar/(m_e c^2) = %.4e s (expect 1.2880e-21), R_p/c = %.4e s (expect 2.807e-24)", t_c, t_p);
        check(buf, near(t_c, 1.2880e-21, 1e-4) && near(t_p, 2.807e-24, 1e-3));
    }
    {
        std::mt19937_64 rng(1234567ULL);
        std::uniform_real_distribution<double> u(0.5, 8.0);
        const double B = 20.0, w = 0.9;
        const int trials = 200000, nX = 7;
        double total = 0.0;
        for (int tr = 0; tr < trials; ++tr)
            for (int i = 0; i < nX; ++i) {
                const double lx = u(rng);
                for (int k = 1; k <= 16; ++k) if (std::fabs(k * lx - B) <= w) ++total;
            }
        const double mc = total / trials, an = analytic_expected(B, w, 0.5, 8.0, 16, nX);
        std::snprintf(buf, sizeof buf, "V3 census null: Monte Carlo %.4f vs analytic %.4f expected hits (B=20, w=0.9)", mc, an);
        check(buf, near(mc, an, 0.02));
    }
    return fail;
}
}  // namespace

int main() {
    std::printf("NP11 neutron lifetime audit\n");
    std::printf("pre-registration: PROMPT.md (2026-10-03)\n\n");
    if (validate() != 0) {
        std::printf("\nVALIDATION FAILED: instrument fault, no result reported.\n");
        return 2;
    }
    std::printf("VALIDATION PASS\n");

    // ---------------- Part C ----------------
    std::printf("\nPART C - beam/bottle (arithmetic on MEASURED-INPUT)\n");
    const Meas allbeam = wmean(beam_old, beam_jparc, "all beams combined");
    std::printf("%-26s %8.2f +/- %.2f s\n", bottle.name, bottle.tau, bottle.sigma);
    std::printf("%-26s %8.2f +/- %.2f s\n", beam_old.name, beam_old.tau, beam_old.sigma);
    std::printf("%-26s %8.2f +/- %.2f s\n", beam_jparc.name, beam_jparc.tau, beam_jparc.sigma);
    std::printf("%-26s %8.2f +/- %.2f s\n", allbeam.name, allbeam.tau, allbeam.sigma);
    struct Row { const char* label; Diff d; };
    const Row rows[] = {
        {"earlier beams - bottle", diff(beam_old, bottle)},
        {"J-PARC - bottle", diff(beam_jparc, bottle)},
        {"J-PARC - earlier beams", diff(beam_jparc, beam_old)},
        {"all beams - bottle", diff(allbeam, bottle)},
    };
    std::printf("\n%-26s %10s %10s %8s\n", "difference", "value (s)", "sigma (s)", "in sigma");
    for (const Row& r : rows) std::printf("%-26s %+10.2f %10.2f %+8.2f\n", r.label, r.d.d, r.d.s, r.d.d / r.d.s);
    const double bb = std::fabs(rows[2].d.d / rows[2].d.s);
    std::printf("\nrejection criterion (beam-type results disagree by more than 2 sigma): %s (%.2f sigma); 'excluded' reserved for > 3 sigma: %s\n",
                bb > 2.0 ? "MET - wall-coupling alone disfavoured" : "not met", bb, bb > 3.0 ? "yes" : "no");
    std::printf("size of the effect to be explained: ln(%.1f/%.1f) = %.4f (%.2f%% in rate)\n", beam_old.tau, bottle.tau,
                std::log(beam_old.tau / bottle.tau), 100.0 * (std::exp(std::log(beam_old.tau / bottle.tau)) - 1.0));
    std::printf("the seed's sign commitment (bottle faster) was set with 888 vs 878 in view: retrodiction.\n");

    // ---------------- Part A1 ----------------
    const double alpha = m::alpha, a0 = m::a_0;
    const double r_e = alpha * alpha * a0;
    const double v_seat = sdt::laws::law_VI::traction::v_phase_proton_surface;
    const double gamma0 = (m::m_n - m::m_p) / m::m_e;   // electron Lorentz factor at the Q_beta seat
    const double beta0 = std::sqrt(1.0 - 1.0 / (gamma0 * gamma0));
    std::printf("\nseat quantities (engine): v_phase/c = %.4f, gamma0 = (m_n-m_p)/m_e = %.5f, Q_beta/(m_e c^2) = gamma0 - 1 = %.5f, beta0 = %.5f, q = 1/gamma0 = %.5f\n",
                v_seat / m::c, gamma0, gamma0 - 1.0, beta0, 1.0 / gamma0);

    const std::vector<Clock> clocks = {
        {"R_p/c", m::R_p / m::c, true},
        {"2 pi R_p / v_seat", 2.0 * pi * m::R_p / v_seat, true},
        {"hbar/(m_p c^2)", m::hbar / (m::m_p * m::c * m::c), true},
        {"hbar/(m_e c^2)", m::hbar / (m::m_e * m::c * m::c), true},
        {"r_e/c", r_e / m::c, true},
        {"l_P/c", m::l_P / m::c, false},
        {"2 pi a0/(alpha c)", 2.0 * pi * a0 / (alpha * m::c), false},
    };
    std::printf("\nPART A1 - B_req = ln(tau/t) for tau = %.1f s (no fit)\n", bottle.tau);
    std::printf("%-22s %14s %10s %12s\n", "clock", "t (s)", "B_req", "nuclear-scale");
    std::vector<double> Breq;
    double bmin = 1e9, bmax = -1e9;
    for (const Clock& c : clocks) {
        const double B = std::log(bottle.tau / c.t);
        Breq.push_back(B);
        if (c.nuclear) { bmin = std::min(bmin, B); bmax = std::max(bmax, B); }
        std::printf("%-22s %14.4e %10.3f %12s\n", c.name.c_str(), c.t, B, c.nuclear ? "yes" : "no");
    }
    const double dB_bb = std::log(beam_old.tau / bottle.tau);
    std::printf("spread across the five nuclear-scale clocks: %.3f nats; beam-bottle difference in B: %.4f nats; ratio %.0f\n",
                bmax - bmin, dB_bb, (bmax - bmin) / dB_bb);

    // ---------------- Part A2 ----------------
    struct X { const char* name; double lnx; };
    const std::vector<X> Xs = {
        {"1/alpha", std::log(1.0 / alpha)}, {"m_p/m_e", std::log(m::m_p / m::m_e)}, {"4 pi", std::log(4.0 * pi)},
        {"2 pi", std::log(2.0 * pi)}, {"pi", std::log(pi)}, {"gamma0", std::log(gamma0)}, {"v_phase/c", std::log(v_seat / m::c)},
    };
    const double tolrel = 0.015;
    std::printf("\nPART A2 - census: B_c = k ln X, k = 1..16, 7 X values (112 constructions), hit = within %.1f%% of B_req\n", 100.0 * tolrel);
    std::vector<int> obs_hits(clocks.size(), 0);
    for (size_t ci = 0; ci < clocks.size(); ++ci) {
        std::printf("%-22s B_req %.3f  hits:", clocks[ci].name.c_str(), Breq[ci]);
        bool any = false;
        for (const X& x : Xs)
            for (int k = 1; k <= 16; ++k) {
                const double Bc = k * x.lnx;
                if (std::fabs(Bc - Breq[ci]) <= tolrel * Breq[ci]) {
                    std::printf("  %d ln(%s) = %.3f (%+.2f%%)", k, x.name, Bc, 100.0 * (Bc - Breq[ci]) / Breq[ci]);
                    ++obs_hits[ci];
                    any = true;
                }
            }
        if (!any) std::printf("  none");
        std::printf("\n");
    }
    // Report-only: nearest construction per clock and the lifetime it would imply (resolution check).
    std::printf("\nreport-only: nearest construction per clock and the lifetime it implies (a %.1f%% window in B is a factor %.2f in tau)\n",
                100.0 * tolrel, std::exp(tolrel * Breq[0]));
    double overall_best = 1e300;
    for (size_t ci = 0; ci < clocks.size(); ++ci) {
        double best = 1e300, bBc = 0; int bk = 0; const char* bn = "";
        for (const X& x : Xs)
            for (int k = 1; k <= 16; ++k) {
                const double d = std::fabs(k * x.lnx - Breq[ci]);
                if (d < best) { best = d; bBc = k * x.lnx; bk = k; bn = x.name; }
            }
        overall_best = std::min(overall_best, best);
        std::printf("%-22s nearest %2d ln(%s) = %.3f, |dB| = %.3f -> tau = %.4g s (x%.2f of %.1f s)\n", clocks[ci].name.c_str(), bk, bn, bBc, best,
                    clocks[ci].t * std::exp(bBc), std::exp(bBc - Breq[ci]), bottle.tau);
    }
    std::printf("resolution of the beam-bottle difference in B: %.4f nats; the best |dB| over all clocks (%.3f) is %.0fx larger\n", dB_bb, overall_best, overall_best / dB_bb);
    // Null: redraw the seven ln X uniformly from [0.5, 8], count hits per clock.
    std::mt19937_64 rng(20261003ULL);
    std::uniform_real_distribution<double> u(0.5, 8.0);
    const int trials = 100000;
    std::vector<std::vector<int>> null_counts(clocks.size());
    std::vector<int> null_nuclear_total;
    for (int tr = 0; tr < trials; ++tr) {
        double lx[7];
        for (double& v : lx) v = u(rng);
        int nuc = 0;
        for (size_t ci = 0; ci < clocks.size(); ++ci) {
            int c = 0;
            for (double v : lx) for (int k = 1; k <= 16; ++k) if (std::fabs(k * v - Breq[ci]) <= tolrel * Breq[ci]) ++c;
            null_counts[ci].push_back(c);
            if (clocks[ci].nuclear) nuc += c;
        }
        null_nuclear_total.push_back(nuc);
    }
    std::printf("\n%-22s %9s %14s %22s\n", "clock", "observed", "null mean", "P(null >= observed)");
    int obs_nuc = 0;
    bool any_distinguishable = false;
    for (size_t ci = 0; ci < clocks.size(); ++ci) {
        double mean = 0; int ge = 0;
        for (int c : null_counts[ci]) { mean += c; if (c >= obs_hits[ci]) ++ge; }
        mean /= trials;
        const double p = static_cast<double>(ge) / trials;
        std::printf("%-22s %9d %14.3f %22.3f\n", clocks[ci].name.c_str(), obs_hits[ci], mean, p);
        if (clocks[ci].nuclear) obs_nuc += obs_hits[ci];
        if (p < 0.05 && obs_hits[ci] > 0) any_distinguishable = true;
    }
    double nmean = 0; int nge = 0;
    for (int c : null_nuclear_total) { nmean += c; if (c >= obs_nuc) ++nge; }
    nmean /= trials;
    std::printf("five nuclear-scale clocks together: observed %d, null mean %.3f, P(null >= observed) = %.3f\n", obs_nuc, nmean, static_cast<double>(nge) / trials);
    std::printf("census criterion (a hit counts as distinguishable only if above the null's 95th percentile for its clock AND shared by two or more clocks): %s\n",
                any_distinguishable ? "see per-clock probabilities above" : "not met - no construction is distinguishable from chance");

    // ---------------- Part A3 ----------------
    std::printf("\nPART A3 - Law V per-tick candidate: tau(N) = t * gamma0^N, N = 50..80, hit = within %.1f%% of %.1f s\n", 100.0 * tolrel, bottle.tau);
    int hits3 = 0;
    for (const Clock& c : clocks) {
        std::printf("%-22s", c.name.c_str());
        bool any = false;
        for (int N = 50; N <= 80; ++N) {
            const double tau = c.t * std::pow(gamma0, N);
            if (std::fabs(tau - bottle.tau) <= tolrel * bottle.tau) { std::printf("  N=%d tau=%.1f s", N, tau); ++hits3; any = true; }
        }
        if (!any) {
            // nearest N for the record
            double best = 1e300; int bn = 0;
            for (int N = 50; N <= 80; ++N) { const double r = std::fabs(std::log(c.t * std::pow(gamma0, N) / bottle.tau)); if (r < best) { best = r; bn = N; } }
            std::printf("  none (nearest N=%d gives tau = %.1f s)", bn, c.t * std::pow(gamma0, bn));
        }
        std::printf("\n");
    }
    const double expect3 = clocks.size() * 2.0 * std::log(1.0 + tolrel) / std::log(gamma0);
    std::printf("hits: %d; expected by chance over %zu clocks: %.2f\n", hits3, clocks.size(), expect3);
    std::printf("N required for exact tau on R_p/c: %.3f (not an integer)\n", std::log(bottle.tau / clocks[0].t) / std::log(gamma0));
    return 0;
}
