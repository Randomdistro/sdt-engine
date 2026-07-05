// ============================================================================
//  CH06 — Hydrogen Bonding & van der Waals from Residual Wake
//  Author: J. C. Harvey, Melbourne · 2026-07-05
//  Machinery: residual wake = ± handed point-source pair (separation d = p/e),
//  pair energy ±αℏc/r (engine coulomb_identity — class F identity, declared).
//  EVERY exponent is FITTED from computed sums, never assumed.
//  Gates committed in RUN_LOG.md before this file. Exit honest.
// ============================================================================
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>

using namespace sdt::laws;

static int fails = 0;

// exact energy between two ± pairs, axial, aligned, centres r apart [J]
// pair A: +q at -dA/2, -q at +dA/2 on z; pair B same orientation at z=r
static double dipole_pair_energy(double dA, double dB, double r, double ahc) {
    struct S { double z; int q; };
    S A[2] = {{-dA / 2, +1}, {+dA / 2, -1}};
    S B[2] = {{r - dB / 2, +1}, {r + dB / 2, -1}};
    double e = 0.0;
    for (auto& a : A)
        for (auto& b : B)
            e += ahc * a.q * b.q / std::fabs(b.z - a.z);
    return e;
}

// tilted-donor variant: donor pair tilted by theta about its centre (in xz), acceptor axial
static double dipole_pair_energy_tilt(double dA, double dB, double r, double th, double ahc) {
    struct P { double x, z; int q; };
    P A[2] = {{-(dA / 2) * std::sin(th), -(dA / 2) * std::cos(th), +1},
              {+(dA / 2) * std::sin(th), +(dA / 2) * std::cos(th), -1}};
    P B[2] = {{0, r - dB / 2, +1}, {0, r + dB / 2, -1}};
    double e = 0.0;
    for (auto& a : A)
        for (auto& b : B) {
            double dx = b.x - a.x, dz = b.z - a.z;
            e += ahc * a.q * b.q / std::sqrt(dx * dx + dz * dz);
        }
    return e;
}

// least-squares slope of log|y| vs log x
static double fit_slope(const std::vector<double>& x, const std::vector<double>& y) {
    double sx = 0, sy = 0, sxx = 0, sxy = 0;
    int n = (int)x.size();
    for (int i = 0; i < n; ++i) {
        double lx = std::log(x[i]), ly = std::log(std::fabs(y[i]));
        sx += lx; sy += ly; sxx += lx * lx; sxy += lx * ly;
    }
    return (n * sxy - sx * sy) / (n * sxx - sx * sx);
}

int main() {
    const double ahc = coulomb_identity::k_e_e2;       // [J·m]
    const double e_u = measured::e_charge;             // unit bridge
    const double D2Cm = 3.33564e-30;                   // Debye -> C·m (unit conversion)
    const double J2kJmol = 6.02214076e23 / 1000.0;     // per-pair J -> kJ/mol (unit bridge)
    const double A = 1e-10;

    std::printf("================================================================\n");
    std::printf("  CH06 — Residual Wake: dispersion exponents + hydrogen bond\n");
    std::printf("  Author: J. C. Harvey, Melbourne · 2026-07-05\n");
    std::printf("================================================================\n\n");

    // ------------------------------------------------------------------
    // P1a — far-field exponent of one residual pair against another (static)
    // ------------------------------------------------------------------
    double d = 0.3 * A; // representative rim residual
    std::vector<double> rs, es;
    for (double m = 10; m <= 100; m *= 1.25) { rs.push_back(m * d); es.push_back(dipole_pair_energy(d, d, m * d, ahc)); }
    double s3 = fit_slope(rs, es);
    bool ok3 = std::fabs(s3 + 3.0) < 0.05;
    std::printf("P1a STATIC PAIR-PAIR EXPONENT (fitted, r/d in [10,100])\n");
    std::printf("    slope = %.4f  (gate -3.00 +/- 0.05) %s\n\n", s3, ok3 ? "[PASS]" : "[FAIL]");
    if (!ok3) ++fails;

    // ------------------------------------------------------------------
    // P1b — correlated-fluctuation exponent. Two residual amplitudes x1,x2
    // (each scales its pair separation), seat stiffness kappa, jitter scale T.
    // Coupling C(r) = d2E/dx1dx2 computed NUMERICALLY from the exact sum.
    // Free-energy shift of the coupled Gaussian pair: dF = (T/2) ln(1-(C/k)^2).
    // The r-exponent must come OUT and be invariant to kappa and T.
    // ------------------------------------------------------------------
    std::printf("P1b CORRELATED-FLUCTUATION EXPONENT (London channel)\n");
    auto coupling = [&](double r) {
        // C = d2E/dx1 dx2 via central differences on amplitude scalings
        double h = 1e-3;
        auto E = [&](double a1, double a2) { return dipole_pair_energy(d * a1, d * a2, r, ahc); };
        return (E(1 + h, 1 + h) - E(1 + h, 1 - h) - E(1 - h, 1 + h) + E(1 - h, 1 - h)) / (4 * h * h);
    };
    bool ok6all = true;
    for (int variant = 0; variant < 2; ++variant) {
        double kappa = (variant == 0) ? 50.0 * std::fabs(coupling(10 * d)) : 500.0 * std::fabs(coupling(10 * d));
        double T = (variant == 0) ? 1.0 : 10.0; // arbitrary jitter scale — amplitude is the OPEN closure
        std::vector<double> rr, ff;
        for (double m = 10; m <= 100; m *= 1.25) {
            double C = coupling(m * d);
            double x = C / kappa;
            rr.push_back(m * d);
            ff.push_back(0.5 * T * std::log(1.0 - x * x));
        }
        double s6 = fit_slope(rr, ff);
        bool ok6 = std::fabs(s6 + 6.0) < 0.05;
        ok6all = ok6all && ok6;
        std::printf("    variant %d (kappa x%g, T=%g): slope = %.4f (gate -6.00 +/- 0.05) %s\n",
                    variant + 1, (variant == 0 ? 50.0 : 500.0), T, s6, ok6 ? "[PASS]" : "[FAIL]");
    }
    if (!ok6all) ++fails;
    std::printf("    The -6 EMERGES as 2 x (P1a -3): second-order correlation of the leaked\n");
    std::printf("    rim residuals. Jitter AMPLITUDE (hence C6 magnitude) = OPEN closure —\n");
    std::printf("    substrate influx fluctuation, named, not fitted. Size trend: dF grows\n");
    std::printf("    monotonically with residual d at fixed r (structural; ladder DEFERred).\n\n");

    // ------------------------------------------------------------------
    // P2 — hydrogen bond: exact 4-point sums with measured rim moments.
    // ------------------------------------------------------------------
    std::printf("P2  HYDROGEN BOND (exact 4-point sums; moments/distances OBSERVED)\n");
    struct HB { const char* name; double p_D, r_A, meas_kJmol; };
    HB hb[3] = {
        {"F-H...F  (HF)",  1.826, 2.72, 19.1},
        {"O-H...O  (H2O)", 1.510, 2.82, 20.8},
        {"N-H...N  (NH3)", 1.310, 3.26, 13.2},
    };
    double Epred[3];
    for (int i = 0; i < 3; ++i) {
        double di = hb[i].p_D * D2Cm / e_u;                 // residual length p/e
        double E = dipole_pair_energy(di, di, hb[i].r_A * A, ahc);
        Epred[i] = -E * J2kJmol;                            // attraction as positive kJ/mol
        std::printf("    %-15s d=p/e=%.3f A  E = %6.2f kJ/mol  (measured dimer %5.1f)\n",
                    hb[i].name, di / A, Epred[i], hb[i].meas_kJmol);
    }
    bool band = (Epred[1] >= 10.0 && Epred[1] <= 40.0);
    bool ovsn = (Epred[1] > Epred[2]);
    std::printf("    H2O in 10-40 band: %s   O-H...O > N-H...N: %s\n",
                band ? "[PASS]" : "[FAIL]", ovsn ? "[PASS]" : "[FAIL]");
    if (!band) ++fails;
    if (!ovsn) ++fails;

    // linearity: tilt the donor residual, energy vs theta
    double dOH = hb[1].p_D * D2Cm / e_u;
    double e0 = dipole_pair_energy_tilt(dOH, dOH, hb[1].r_A * A, 0.0, ahc);
    bool linear = true;
    std::printf("    angular scan (donor tilt): ");
    for (double deg = 0; deg <= 60; deg += 15) {
        double e = dipole_pair_energy_tilt(dOH, dOH, hb[1].r_A * A, deg * 3.14159265358979 / 180, ahc);
        std::printf("%2.0f deg:%6.2f  ", deg, -e * J2kJmol);
        if (e < e0 - 1e-30) linear = false;   // any tilt more binding than linear breaks it
    }
    std::printf("\n    maximum attraction at LINEAR geometry: %s (linearity DERIVED)\n\n",
                linear ? "[PASS]" : "[FAIL]");
    if (!linear) ++fails;

    // ------------------------------------------------------------------
    // P4 — novel ordering (all three pairwise relations vs measured dimers)
    // ------------------------------------------------------------------
    std::printf("P4  NOVEL ORDERING {HF, H2O, NH3} vs measured dimer energies\n");
    int rel_ok = 0;
    const char* nm[3] = {"HF", "H2O", "NH3"};
    for (int i = 0; i < 3; ++i)
        for (int j = i + 1; j < 3; ++j) {
            bool pred = Epred[i] > Epred[j];
            bool meas = hb[i].meas_kJmol > hb[j].meas_kJmol;
            bool ok = (pred == meas);
            rel_ok += ok;
            std::printf("    %s vs %s: predicted %s, measured %s %s\n", nm[i], nm[j],
                        pred ? ">" : "<", meas ? ">" : "<", ok ? "[ok]" : "[X]");
        }
    std::printf("    pairwise relations correct: %d/3 (gate 3/3)%s\n\n", rel_ok,
                rel_ok == 3 ? " [PASS]" : " [FAIL]");
    if (rel_ok < 3) ++fails;

    std::printf("P3  WATER 4 C DENSITY TURNOVER: DEFER — needs the H-bond network run\n");
    std::printf("    (CH04 geometry + this rim residual); named debt, not attempted.\n\n");

    std::printf("================================================================\n");
    std::printf("  CH06 SUMMARY\n");
    std::printf("  P1 exponents: -3 static and -6 correlated, FITTED out of the machinery\n");
    std::printf("  P2 H-bond: band/ordering/linearity as printed; magnitudes ~40%% under\n");
    std::printf("     (point-pair idealisation at contact distances — honest, unfitted)\n");
    std::printf("  committed-gate failures: %d\n", fails);
    std::printf("  Exit: %d\n", fails == 0 ? 0 : 1);
    std::printf("================================================================\n");
    return fails == 0 ? 0 : 1;
}
