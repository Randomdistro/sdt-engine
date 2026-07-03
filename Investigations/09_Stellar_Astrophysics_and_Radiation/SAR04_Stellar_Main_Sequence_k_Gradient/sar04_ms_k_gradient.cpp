// ============================================================================
// SAR04 — Stellar Main Sequence from k-Gradient
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
//
// k = c / v_circ(surface), engine convention (k_Sun = 686.3, bridge::).
// Native form used: v_circ = v_circ_Sun * sqrt((M/Msun)/(R/Rsun)) — NO G anywhere.
// Data: 16 canonical MS spectral-type bins (ADJ-001 in RUN_LOG.md; OBSERVED,
// memory-transcribed calibration values, +-10-20%). Gates pre-committed:
// T1 Spearman |rho|>=0.90; T2 R^2>=0.90 (slope MEASURED, not derived);
// T3 solar k within 3%; T4 L~M^3.5 must emerge WITHOUT importing R(M).
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

using namespace sdt::laws;

struct Star { const char* sp; double M, R, L, Teff; };

// Canonical MS calibration bins (solar units; OBSERVED anchors, see ADJ-001)
static const std::vector<Star> MS = {
    {"O5V", 60.0, 13.4, 7.9e5, 44500},
    {"O8V", 23.0,  8.5, 1.7e5, 35800},
    {"B0V", 17.5,  7.4, 5.2e4, 30000},
    {"B5V",  5.9,  3.9, 8.3e2, 15200},
    {"A0V",  2.9,  2.4, 5.4e1,  9800},
    {"A5V",  2.0,  1.7, 1.4e1,  8190},
    {"F0V",  1.6,  1.5, 6.5e0,  7300},
    {"F5V",  1.4,  1.3, 3.2e0,  6650},
    {"G0V",  1.05, 1.10, 1.35,  5940},
    {"G2V",  1.00, 1.00, 1.00,  5778},
    {"G8V",  0.91, 0.88, 0.66,  5490},
    {"K0V",  0.79, 0.85, 0.42,  5240},
    {"K5V",  0.67, 0.72, 0.15,  4410},
    {"M0V",  0.51, 0.60, 0.077, 3840},
    {"M2V",  0.40, 0.50, 0.045, 3520},
    {"M5V",  0.21, 0.27, 0.0079,3170},
};

static double spearman(const std::vector<double>& a, const std::vector<double>& b) {
    auto rank = [](const std::vector<double>& v) {
        std::vector<size_t> idx(v.size());
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [&](size_t i, size_t j){ return v[i] < v[j]; });
        std::vector<double> r(v.size());
        for (size_t p = 0; p < idx.size(); ++p) r[idx[p]] = double(p);
        return r;
    };
    auto ra = rank(a), rb = rank(b);
    const double n = double(a.size());
    double ma = (n-1)/2.0, cov = 0, va = 0, vb = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        cov += (ra[i]-ma)*(rb[i]-ma); va += (ra[i]-ma)*(ra[i]-ma); vb += (rb[i]-ma)*(rb[i]-ma);
    }
    return cov / std::sqrt(va*vb);
}

int main() {
    const double v_sun = bridge::v_surface_Sun;   // 436762 m/s (engine)
    const double k_eng = bridge::k_Sun;           // 686.3

    std::printf("SAR04 — MS k-gradient (J. C. Harvey, 2026-07-03). N=%zu canonical bins (ADJ-001).\n", MS.size());
    std::printf("k = c / v_circ,  v_circ = v_sun*sqrt((M/Ms)/(R/Rs))  [native, no G]\n\n");
    std::printf("  sp     M/Ms   R/Rs      L/Ls    Teff    v_circ[km/s]      k     r_domain[AU]\n");
    std::printf("  ----------------------------------------------------------------------------\n");

    std::vector<double> ks, Ls, Ms_, Teffs;
    for (const auto& s : MS) {
        const double v = v_sun * std::sqrt(s.M / s.R);
        const double k = measured::c / v;
        const double rdom_AU = law_II::pressure_domain(s.L * law_II::L_Sun) / measured::AU;
        ks.push_back(k); Ls.push_back(s.L); Ms_.push_back(s.M); Teffs.push_back(s.Teff);
        std::printf("  %-5s %6.2f %6.2f  %9.3g  %5.0f     %8.1f      %6.1f   %9.3g\n",
                    s.sp, s.M, s.R, s.L, s.Teff, v/1000.0, k, rdom_AU);
    }

    // T3: solar point
    const double k_G2 = ks[9];
    std::printf("\n[T3] k(G2V) = %.1f vs engine k_Sun = %.1f -> %.2f%% : %s\n",
                k_G2, k_eng, (k_G2/k_eng - 1.0)*100.0,
                std::fabs(k_G2/k_eng - 1.0) < 0.03 ? "PASS" : "FAIL");

    // T1: monotonicity (k vs Teff rank; strict count of inversions too)
    const double rho_kT = spearman(ks, Teffs);
    const double rho_kL = spearman(ks, Ls);
    const double rho_kM = spearman(ks, Ms_);
    int inversions = 0;
    for (size_t i = 1; i < ks.size(); ++i) if (ks[i] < ks[i-1]) ++inversions;  // expect k rising O->M
    std::printf("[T1] Spearman rho(k,Teff) = %.4f  rho(k,L) = %.4f  rho(k,M) = %.4f\n",
                rho_kT, rho_kL, rho_kM);
    std::printf("     strict inversions along O->M: %d of %zu steps\n", inversions, ks.size()-1);
    const bool T1 = std::fabs(rho_kT) >= 0.90;
    std::printf("     gate |rho|>=0.90: %s\n", T1 ? "PASS" : (std::fabs(rho_kT)>=0.7 ? "PARTIAL" : "KILLED"));

    // T2: log-log fit L = A k^n
    double sx=0, sy=0, sxx=0, sxy=0; const double n = double(ks.size());
    for (size_t i = 0; i < ks.size(); ++i) {
        const double x = std::log10(ks[i]), y = std::log10(Ls[i]);
        sx += x; sy += y; sxx += x*x; sxy += x*y;
    }
    const double slope = (n*sxy - sx*sy) / (n*sxx - sx*sx);
    const double icept = (sy - slope*sx) / n;
    double ss_res = 0, ss_tot = 0, ym = sy/n;
    for (size_t i = 0; i < ks.size(); ++i) {
        const double x = std::log10(ks[i]), y = std::log10(Ls[i]);
        const double f = icept + slope*x;
        ss_res += (y-f)*(y-f); ss_tot += (y-ym)*(y-ym);
    }
    const double R2 = 1.0 - ss_res/ss_tot;
    std::printf("[T2] log-log fit: L/Ls = 10^%.2f * k^(%.1f)   R^2 = %.3f  gate R^2>=0.90: %s\n",
                icept, slope, R2, R2 >= 0.90 ? "PASS (slope MEASURED, not derived)" : "FAIL");

    // T4: does L ~ M^3.5 EMERGE from k alone?
    // k encodes only M/R: k = k_sun*sqrt(R/M). Recovering L(M) from L(k) requires R(M):
    // fit R = M^beta on the same table, show the L-M slope decomposes as n_LM = n_Lk*(beta-1)/2.
    double sxm=0, sym=0, sxxm=0, sxym=0;
    for (size_t i = 0; i < ks.size(); ++i) {
        const double x = std::log10(Ms_[i]), y = std::log10(MS[i].R);
        sxm += x; sym += y; sxxm += x*x; sxym += x*y;
    }
    const double beta = (n*sxym - sxm*sym) / (n*sxxm - sxm*sxm);   // R ~ M^beta (empirical)
    // L ~ M^a fit:
    double sxl=0, syl=0, sxxl=0, sxyl=0;
    for (size_t i = 0; i < ks.size(); ++i) {
        const double x = std::log10(Ms_[i]), y = std::log10(Ls[i]);
        sxl += x; syl += y; sxxl += x*x; sxyl += x*y;
    }
    const double a_LM = (n*sxyl - sxl*syl) / (n*sxxl - sxl*sxl);
    const double a_implied = slope * (beta - 1.0) / 2.0;   // from L~k^n, k~sqrt(R/M)=M^{(beta-1)/2}
    std::printf("[T4] table M-L slope a = %.2f (vs canonical 3.5); empirical R~M^beta, beta = %.2f\n",
                a_LM, beta);
    std::printf("     k-route implied a = n*(beta-1)/2 = %.2f — reproduces a ONLY by importing\n", a_implied);
    std::printf("     the empirical R(M) (beta). k alone cannot fix L(M): NOT EMERGENT.\n");

    std::printf("\nVERDICT LINES\n");
    std::printf("  T1 monotonic k-sequence: rho = %.3f -> %s (k spans only %.0f-%.0f, x%.1f, while L spans 10^%.1f)\n",
                rho_kT, T1 ? "PASS" : "PARTIAL/KILLED",
                *std::min_element(ks.begin(), ks.end()), *std::max_element(ks.begin(), ks.end()),
                *std::max_element(ks.begin(), ks.end()) / *std::min_element(ks.begin(), ks.end()),
                std::log10(Ls.front()/Ls.back()));
    std::printf("  T2 L(k): slope %.1f, R^2 %.3f — MEASURED fit, no SDT derivation of the exponent\n", slope, R2);
    std::printf("  T3 solar point: %.2f%% off engine k_Sun\n", (k_G2/k_eng - 1.0)*100.0);
    std::printf("  T4 L~M^3.5 from k alone: NOT EMERGENT (needs empirical R(M))\n");
    return 0;
}
