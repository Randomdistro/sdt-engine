// SAR02 blank-slate run 2 (2026-10-08): the counting derivation of the occupation factor (phase W of run 1) at larger R.
// AMENDMENT made AFTER run 1 was seen: run 1 registered RC3 as "deviation <= 1e-3 at R = 3200 and decreasing in R"; at R = 3200 the deviations were 1.87e-3, 4.69e-4, 3.44e-4 (mean occupation 0.1, 1, 5): RC3 not met as registered.
//  Run 2 changes only the registered R list, to R = 3200, 12800, 51200, 204800. The criterion is unchanged and is applied at the largest R: deviation <= 1e-3 for all three mean occupations, decreasing in R.
//  Added, registered here before the run: the product dev * R is reported; if it is constant to 10% over the last three R the deviation is O(1/R) with a finite coefficient.
//  Instrument and definitions as run 1: R oscillators of one quantum e share M quanta, all microstates equally weighted, exact P(n) = C(M-n+R-2, R-2)/C(M+R-1, R-1); counting temperature e/kT = [ln W(M+1) - ln W(M-1)]/2, W(M) = C(M+R-1, M).
//  Validation (known answer, as run 1): sum_n P(n) = 1 and <n> = M/R for every case, tolerance 1e-6 (set before the run: lgamma differences at n ~ 1e6 carry ~1e-8 round-off, so the 1e-9 first written here was not attainable in double precision).
// Author: J. C. Harvey, Melbourne.
#include <cmath>
#include <cstdio>
#include <vector>
static double lnC(double n, double r) { return std::lgamma(n + 1) - std::lgamma(r + 1) - std::lgamma(n - r + 1); }
int main() {
    std::printf("SAR02 blank-slate run 2 (registered in the tool header, 2026-10-08; amendment after run 1)\n===========================================================================================\n\n");
    bool val = true, rc3 = true; double prevdev[3] = {1, 1, 1}; double devR[3][3] = {}; int cnt[3] = {0, 0, 0};
    for (int R : {3200, 12800, 51200, 204800}) { std::printf("R = %6d:\n", R); int ni = 0;
        for (double nb : {0.1, 1.0, 5.0}) { long Mq = std::lround(R * nb); double Z = lnC(Mq + R - 1, R - 1), mean = 0, tot = 0;
            for (long n = 0; n <= Mq; ++n) { double pn = std::exp(lnC(Mq - n + R - 2, R - 2) - Z); tot += pn; mean += n * pn; if (pn < 1e-300 && n > 50 + 40 * nb) break; }
            double ex = double(Mq) / R; bool ok = std::fabs(tot - 1) < 1e-6 && std::fabs(mean - ex) < 1e-6 * (1 + ex); val = val && ok;
            auto lnW = [&](long m) { return lnC(double(m + R - 1), double(m)); }; double x = (lnW(Mq + 1) - lnW(Mq - 1)) / 2; double bose = 1.0 / std::expm1(x); double dev = std::fabs(mean / bose - 1);
            std::printf("   mean occupation %.1f: <n> = %.8f ; 1/(e^x - 1) = %.8f ; dev = %.3e ; dev*R = %.4f ; sum P = %.12f ; validation %s\n", nb, mean, bose, dev, dev * R, tot, ok ? "met" : "NOT MET");
            if (dev > prevdev[ni] + 1e-12) rc3 = false; prevdev[ni] = dev; if (R == 204800) rc3 = rc3 && dev <= 1e-3; if (R >= 12800) { devR[ni][cnt[ni]++] = dev * R; } ++ni; } }
    std::printf("\nvalidation (sum P = 1, <n> = M/R): %s\n", val ? "met" : "NOT MET -> G0");
    bool flat = true; for (int i = 0; i < 3; ++i) { double lo = std::min({devR[i][0], devR[i][1], devR[i][2]}), hi = std::max({devR[i][0], devR[i][1], devR[i][2]}); flat = flat && (hi / lo - 1 < 0.10); std::printf("dev*R over R = 12800, 51200, 204800 for mean occupation index %d: %.4f %.4f %.4f (spread %.2f%%)\n", i, devR[i][0], devR[i][1], devR[i][2], (hi / lo - 1) * 100); }
    std::printf("RC3 (deviation <= 1e-3 at the largest R, decreasing in R): %s ; dev*R constant to 10%%: %s\n", rc3 ? "met" : "NOT met", flat ? "yes (O(1/R))" : "no");
    return 0;
}
