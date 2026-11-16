// ═══════════════════════════════════════════════════════════════════════
//  NP22 — β-Spectrum SHAPE from Partition Geometry
//  Author: J. C. Harvey, Melbourne. Run: 2026-07-04.
//  Engine: <sdt/laws.hpp> ONLY. Gates pre-committed in RUN_LOG.md BEFORE
//  this file was written; nothing here may widen or reweight them.
//
//  Question (NP14 VERDICT 2026-07-04 appendix, the named test):
//    does the geometric partition of ONE fixed internal speed — the 0.9186c
//    seat electron unwinding, the neutrino taking the Law-V complement
//    (v_e² + v_ν² = c²) — reproduce the SHAPE of the free-neutron β spectrum?
//
//  Anchor (OBSERVED column ONLY, never in the chain):
//    dN/dT ∝ p_e E_e (Q−T)²,  Q = 0.782333 MeV  (standard allowed/Kurie shape;
//    Coulomb, recoil-order, radiative corrections omitted — declared v1).
//
//  IDENTITY ledger: Q from engine masses; β₀ from (γ₀−1)m_ec² = Q. The
//  endpoint T_max = Q therefore lands BY CONSTRUCTION and earns nothing.
//  The SHAPE on (0,Q) is the only earnable content.
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

using namespace sdt::laws;

namespace {

constexpr int      NGRID = 200001;   // fine grid on [0,Q]
constexpr int      NBINS = 50;       // total-variation bins
constexpr long     NMC   = 10000000; // Monte-Carlo cross-check samples
constexpr unsigned SEED  = 20260704;

// electron speed fraction β for kinetic energy T [MeV], electron mass me [MeV]
double beta_of_T(double T, double me) {
    const double g = 1.0 + T / me;
    return std::sqrt(std::max(0.0, 1.0 - 1.0 / (g * g)));
}

// least-squares log-log slope of pdf(x) sampled on [xlo, xhi]
template <typename PdfFn>
double loglog_slope(PdfFn pdf, double xlo, double xhi) {
    double sx = 0, sy = 0, sxx = 0, sxy = 0; int n = 0;
    const int NP = 2000;
    for (int i = 0; i <= NP; ++i) {
        const double x = xlo * std::pow(xhi / xlo, (double)i / NP); // log-spaced
        const double y = pdf(x);
        if (y <= 0.0 || !std::isfinite(y)) continue;
        const double lx = std::log(x), ly = std::log(y);
        sx += lx; sy += ly; sxx += lx * lx; sxy += lx * ly; ++n;
    }
    if (n < 2) return std::nan("");
    return (n * sxy - sx * sy) / (n * sxx - sx * sx);
}

struct ShapeStats {
    double KS, TV, mean;
    double m_low10, m_third1, m_third2, m_third3, m_top10; // zone masses
};

// grade a model CDF F(T) against the anchor CDF (uniform grid on [0,Q])
template <typename CdfFn>
ShapeStats grade(CdfFn F, const std::vector<double>& T,
                 const std::vector<double>& cdfA, double Q) {
    ShapeStats s{};
    double D = 0.0;
    for (size_t i = 0; i < T.size(); ++i)
        D = std::max(D, std::fabs(F(T[i]) - cdfA[i]));
    s.KS = D;
    auto idx = [&](double t) {
        return (size_t)std::llround(std::clamp(t / Q, 0.0, 1.0) * (NGRID - 1));
    };
    double tv = 0.0;
    for (int b = 0; b < NBINS; ++b) {
        const double tlo = Q * b / NBINS, thi = Q * (b + 1) / NBINS;
        const double pm = F(thi) - F(tlo);
        const double pa = cdfA[idx(thi)] - cdfA[idx(tlo)];
        tv += std::fabs(pm - pa);
    }
    s.TV = 0.5 * tv;
    double m = 0.0;
    const double dT = Q / (NGRID - 1);
    for (size_t i = 0; i + 1 < T.size(); ++i)
        m += 0.5 * ((1.0 - F(T[i])) + (1.0 - F(T[i + 1]))) * dT;  // mean = ∫(1−F)dT
    s.mean = m;
    s.m_low10  = F(0.1 * Q);
    s.m_third1 = F(Q / 3.0);
    s.m_third2 = F(2.0 * Q / 3.0) - F(Q / 3.0);
    s.m_third3 = 1.0 - F(2.0 * Q / 3.0);
    s.m_top10  = 1.0 - F(0.9 * Q);
    return s;
}

} // namespace

int main() {
    std::printf("NP22 — beta-spectrum SHAPE from partition geometry (2026-07-04)\n");
    std::printf("Engine: sdt/laws.hpp only. Gates: RUN_LOG.md (pre-committed).\n");
    std::printf("=================================================================\n\n");

    // ---- Phase 1: identities (engine masses only) --------------------------
    const double c   = measured::c;
    const double me  = measured::m_e * c * c / measured::MeV_to_J;   // [MeV]
    const double dm  = (measured::m_n - measured::m_p) * c * c / measured::MeV_to_J;
    const double Q   = dm - me;                                       // [MeV]
    const double g0  = 1.0 + Q / me;
    const double b0  = std::sqrt(1.0 - 1.0 / (g0 * g0));
    const double bnu = std::sqrt(1.0 - b0 * b0);

    std::printf("Phase 1 — identity ledger (earns NOTHING)\n");
    std::printf("  m_e c^2                 = %.6f MeV                  [engine]\n", me);
    std::printf("  (m_n - m_p) c^2         = %.6f MeV                  [engine]\n", dm);
    std::printf("  Q = dm - m_e c^2        = %.6f MeV                  [IDENTITY]\n", Q);
    std::printf("  beta_0: (g0-1)me = Q    = %.6f  (gamma_0 = %.6f)  [IDENTITY inversion]\n", b0, g0);
    std::printf("  Law-V complement        = %.6f c (symmetric point)  [IDENTITY]\n", bnu);
    const double dev_b0 = b0 / 0.91859 - 1.0, dev_bnu = bnu / 0.39522 - 1.0;
    std::printf("  vs NP14 appendix 0.91859c / 0.39522c: dev %+.4f%% / %+.4f%%   [%s bookkeeping gate 0.1%%]\n\n",
                100.0 * dev_b0, 100.0 * dev_bnu,
                (std::fabs(dev_b0) < 1e-3) ? "PASS" : "FAIL");

    // ---- Anchor: OBSERVED column only ---------------------------------------
    std::vector<double> T(NGRID), pdfA(NGRID), cdfA(NGRID);
    const double dT = Q / (NGRID - 1);
    for (int i = 0; i < NGRID; ++i) {
        const double t = i * dT;
        T[i] = t;
        const double E = t + me;
        const double p = std::sqrt(std::max(0.0, E * E - me * me));
        pdfA[i] = p * E * (Q - t) * (Q - t);
    }
    cdfA[0] = 0.0;
    for (int i = 1; i < NGRID; ++i)
        cdfA[i] = cdfA[i - 1] + 0.5 * (pdfA[i] + pdfA[i - 1]) * dT;
    const double normA = cdfA[NGRID - 1];
    for (int i = 0; i < NGRID; ++i) { cdfA[i] /= normA; pdfA[i] /= normA; }
    double meanA = 0.0, peakA = 0.0; int ipk = 0;
    for (int i = 0; i < NGRID; ++i) {
        meanA += T[i] * pdfA[i] * dT;
        if (pdfA[i] > peakA) { peakA = pdfA[i]; ipk = i; }
    }
    auto pdf_anchor = [&](double t) {
        const double E = t + me;
        const double p = std::sqrt(std::max(0.0, E * E - me * me));
        return p * E * (Q - t) * (Q - t) / normA;
    };
    std::printf("Anchor [OBSERVED column only — the rival's machinery, quarantined]\n");
    std::printf("  shape dN/dT = p E (Q-T)^2 on [0,Q];  <T> = %.4f MeV;  peak at T = %.4f MeV\n",
                meanA, T[ipk]);
    std::printf("  omissions (declared v1): Coulomb/Fermi-function, recoil-order, radiative\n\n");

    // ---- Model CDFs (chain = engine masses + declared geometry, closed form) ----
    auto F_M1 = [&](double t) {  // COMMITTED: isotropic release, speed projection
        return std::min(1.0, beta_of_T(std::min(t, Q), me) / b0);
    };
    auto F_M2 = [&](double t) {  // scan: energy projection T = Q cos^2(theta)
        return std::sqrt(std::clamp(t / Q, 0.0, 1.0));
    };
    auto F_M3 = [&](double t) {  // scan: planar seat phase u = |cos(phi)|
        const double u = std::clamp(beta_of_T(std::min(t, Q), me) / b0, 0.0, 1.0);
        return (2.0 / std::numbers::pi) * std::asin(u);
    };
    auto F_M0 = [&](double t) {  // scan: tangential/slingshot limit -> line at Q
        return (t >= Q * (1.0 - 1e-12)) ? 1.0 : 0.0;
    };

    // analytic pdfs for the limit-fingerprint probes
    auto pdf_M1 = [&](double t) {          // dF1/dT = 1/(b0 * beta * gamma^3 * me)
        const double g = 1.0 + t / me, be = beta_of_T(t, me);
        return (be > 0.0) ? 1.0 / (b0 * be * g * g * g * me) : 0.0;
    };
    auto pdf_M2 = [&](double t) { return (t > 0.0) ? 0.5 / std::sqrt(t * Q) : 0.0; };
    auto pdf_M3 = [&](double t) {          // dF3/dT = (2/pi) * pdf_M1 / sqrt(1-u^2)
        const double u = beta_of_T(t, me) / b0;
        if (u <= 0.0 || u >= 1.0) return 0.0;
        return (2.0 / std::numbers::pi) * pdf_M1(t) / std::sqrt(1.0 - u * u);
    };

    // ---- G4: Monte-Carlo numerics cross-check for M1 ------------------------
    {
        std::mt19937_64 rng(SEED);
        std::uniform_real_distribution<double> uni(0.0, 1.0);
        std::vector<double> Ts; Ts.reserve(NMC);
        for (long k = 0; k < NMC; ++k) {
            const double u = uni(rng);              // |cos(theta)| ~ U(0,1): isotropic
            const double be = b0 * u;               // retained speed fraction
            const double g = 1.0 / std::sqrt(1.0 - be * be);
            Ts.push_back((g - 1.0) * me);
        }
        std::sort(Ts.begin(), Ts.end());
        double dmax = 0.0;
        for (long k = 0; k < NMC; ++k) {
            const double Fk = F_M1(Ts[k]);
            dmax = std::max(dmax, std::max(std::fabs((double)(k + 1) / NMC - Fk),
                                           std::fabs((double)k / NMC - Fk)));
        }
        std::printf("G4 numerics — M1 MC (1e7 samples, seed %u) vs analytic CDF: max dev = %.2e  [%s < 1e-3]\n\n",
                    SEED, dmax, (dmax < 1e-3) ? "PASS" : "FAIL");
    }

    // ---- Phase 2/3: grade committed measure + declared scan -----------------
    struct Row { const char* name; ShapeStats s; };
    Row rows[] = {
        { "M1 isotropic-projection (COMMITTED)", grade(F_M1, T, cdfA, Q) },
        { "M0 tangential line at Q (scan)     ", grade(F_M0, T, cdfA, Q) },
        { "M2 energy-projection (scan)        ", grade(F_M2, T, cdfA, Q) },
        { "M3 planar seat phase (scan)        ", grade(F_M3, T, cdfA, Q) },
    };
    auto F_anchor = [&](double t) {
        return cdfA[(size_t)std::llround(std::clamp(t / Q, 0.0, 1.0) * (NGRID - 1))];
    };
    const ShapeStats sa = grade(F_anchor, T, cdfA, Q);

    std::printf("Phase 2/3 — shape comparison (all rows vs OBSERVED anchor; zone = probability mass)\n");
    std::printf("  %-37s %7s %7s %8s | %7s %6s %6s %6s %7s\n",
                "measure", "KS D", "TV", "<T> MeV", "[0,.1Q]", "1st/3", "2nd/3", "3rd/3", "[.9Q,Q]");
    std::printf("  %-37s %7s %7s %8.4f | %7.4f %6.3f %6.3f %6.3f %7.4f   [OBSERVED]\n",
                "anchor p E (Q-T)^2", "--", "--", meanA,
                sa.m_low10, sa.m_third1, sa.m_third2, sa.m_third3, sa.m_top10);
    for (const Row& r : rows)
        std::printf("  %-37s %7.4f %7.4f %8.4f | %7.4f %6.3f %6.3f %6.3f %7.4f\n",
                    r.name, r.s.KS, r.s.TV, r.s.mean,
                    r.s.m_low10, r.s.m_third1, r.s.m_third2, r.s.m_third3, r.s.m_top10);

    // ---- G1 verdict on the committed measure ---------------------------------
    const double D1 = rows[0].s.KS;
    const char* g1 = (D1 <= 0.05) ? "PASS (NATIVE)"
                   : (D1 <= 0.15) ? "QUALIFIED (Class C)"
                   : "FAIL -> OPEN (cascade root: release-measure geometry -> FLM14 lineage)";
    std::printf("\nG1 (SHAPE, committed M1): KS D = %.4f  =>  %s\n", D1, g1);
    std::printf("G2 (ENDPOINT): T_max = Q = %.6f MeV BY CONSTRUCTION — IDENTITY, not gradable, never sold.\n\n", Q);

    // ---- Phase 4: limit-behaviour fingerprints (class-kill check) ------------
    const double lo1 = 1e-4 * Q, lo2 = 1e-2 * Q;   // low-E window (x = T)
    const double ep1 = 1e-3 * Q, ep2 = 3e-2 * Q;   // endpoint window (x = Q-T)
    auto ep = [&](auto pdf) {                       // pdf as function of x = Q-T
        return [&, pdf](double x) { return pdf(Q - x); };
    };
    std::printf("Phase 4 — limit fingerprints (pdf ~ x^n on declared windows, RUN_LOG G3)\n");
    std::printf("  %-37s %14s %18s\n", "measure", "low-E n (x=T)", "endpoint n (x=Q-T)");
    std::printf("  %-37s %14.3f %18.3f   [OBSERVED: +1/2, +2 = 3D state-count fingerprints]\n",
                "anchor p E (Q-T)^2",
                loglog_slope(pdf_anchor, lo1, lo2), loglog_slope(ep(pdf_anchor), ep1, ep2));
    std::printf("  %-37s %14.3f %18.3f\n", "M1 isotropic-projection (COMMITTED)",
                loglog_slope(pdf_M1, lo1, lo2), loglog_slope(ep(pdf_M1), ep1, ep2));
    std::printf("  %-37s %14.3f %18.3f\n", "M2 energy-projection (scan)",
                loglog_slope(pdf_M2, lo1, lo2), loglog_slope(ep(pdf_M2), ep1, ep2));
    std::printf("  %-37s %14.3f %18.3f\n", "M3 planar seat phase (scan)",
                loglog_slope(pdf_M3, lo1, lo2), loglog_slope(ep(pdf_M3), ep1, ep2));
    std::printf("  M0 tangential (scan): delta-line at Q — no shape at all (the two-body line problem).\n\n");

    std::printf("Class-kill lemma (stated in RUN_LOG before running): an analytic 1-DOF release\n");
    std::printf("map with bounded non-vanishing measure density has endpoint exponent in\n");
    std::printf("{0, -1/2, -2/3, ...} — NEVER +2. The anchor demands +2 at the endpoint (nu-side\n");
    std::printf("3D state count) and +1/2 at low E (e-side 3D count). The table above decides\n");
    std::printf("whether the whole 1-DOF class is killed, not just the committed member.\n\n");

    // ---- Ledger column: Law-V complement speed (reported, not used) ----------
    std::printf("Law-V complement column (reported only; E_nu = Q - T_e closes the energy ledger):\n");
    std::printf("  %8s %10s %12s %12s %16s\n", "u=|cos|", "v_e/c", "T_e [MeV]", "E_nu [MeV]", "v_nu_LawV/c");
    for (double u : { 1.0, 0.75, 0.5, 0.25, 0.0 }) {
        const double be = b0 * u, g = 1.0 / std::sqrt(1.0 - be * be);
        const double Te = (g - 1.0) * me;
        std::printf("  %8.2f %10.5f %12.5f %12.5f %16.5f\n",
                    u, be, Te, Q - Te, std::sqrt(1.0 - be * be));
    }
    std::printf("  (declared ontology debt: no native budget-speed -> E_nu map; conservation does that work)\n");

    return 0;
}
