// ============================================================================
//  NP10 RUN 2 — ROOT-CONTACT: the shared-seat contact wall
//  Author: J. C. Harvey, Melbourne · 2026-07-05
//  Registered three-field cross-check (STACK 3b / CH07 D7): ONE wall mechanism,
//  ONE constant set {alpha*hbar*c, a_0, R_p} (laws.hpp only), three targets:
//    (a) k(H2) ~ 575 N/m   (b) NaCl 861 -> 787 kJ/mol (-74)   (c) alpha lock x6.35
//  Mechanism committed in RUN_LOG.md BEFORE this file:
//    Face R — saturated-occlusion ledger: deficit pairs get the EXACT solid-angle
//             energy  E(r) = -(ahc/Rh)*2A(Rh/r),  A(s)=(sqrt(1-s^2)-1)/s+asin(s);
//             below the seat boundary the force holds at the half-sky ceiling
//             2*ahc/Rh^2 (linear energy). Surplus (like-charge) pairs stay 1/r.
//             Cage rule: Rh = a_0 (molecular/ionic seats), Rh = R_p/6 (nuclear).
//    Face T — angular-window allocation: sequential seat tours (FLM14), lock
//             multiplicity = (Z-1)!  (closed tours of Z destinations).
//  Gates (25% each) + expectations pre-committed. Exit 0 only if ALL gates pass.
// ============================================================================
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace sdt::laws;
namespace M = sdt::laws::measured;

static int gate_fails = 0;

// ---------------------------------------------------------------------------
// Face R — exact solid-angle occlusion ledger (deficit channel), unit charges.
// Energy per pair in units where ahc, Rh carry the dimensions.
//   r >= Rh :  E = -(ahc/Rh) * 2*A(Rh/r)
//   r <  Rh :  E = -(ahc/Rh) * [ (pi-2) + 2*(1 - r/Rh) ]   (ceiling-force linear)
// A(s) = (sqrt(1-s^2)-1)/s + asin(s)  — exact integral of F=(ahc/r^2)*G((Rh/r)^2),
// G(x) = 2(1-sqrt(1-x))/x (the canonical two-regime saturation, E105/GOM13).
// ---------------------------------------------------------------------------
static double ledgerA(double s) {
    return (std::sqrt(1.0 - s * s) - 1.0) / s + std::asin(s);
}
static double E_deficit(double r, double Rh, double ahc) {   // < 0 (binding)
    const double pi = 3.14159265358979323846;
    if (r >= Rh) return -(ahc / Rh) * 2.0 * ledgerA(Rh / r);
    return -(ahc / Rh) * ((pi - 2.0) + 2.0 * (1.0 - r / Rh));
}

int main() {
    const double pi   = 3.14159265358979323846;
    const double ahcJ = coulomb_identity::k_e_e2;              // alpha*hbar*c [J*m]
    const double eV   = M::eV_to_J;
    const double ahcA = ahcJ / eV * 1e10;                      // [eV*Angstrom]
    const double a0A  = M::a_0 * 1e10;                         // [Angstrom]
    const double NA   = 6.02214076e23;                         // unit bridge, mol
    const double EVA2_to_Nm = eV / 1e-20;                      // eV/A^2 -> N/m
    const double HBARC_MeVfm = (M::hbar * M::c / M::MeV_to_J) * 1e15;
    const double AHC_MeVfm   = M::alpha * HBARC_MeVfm;         // [MeV*fm]
    const double RpF  = M::R_p * 1e15;                         // [fm]
    const double D    = 2.0 * RpF + RpF / 3.0;                 // NP17 bond [fm]

    std::printf("=======================================================================\n");
    std::printf(" NP10 RUN 2 — ROOT-CONTACT: shared-seat contact wall (J.C. Harvey 2026-07-05)\n");
    std::printf(" One constant set: ahc = %.4f eV*A = %.4f MeV*fm | a_0 = %.6f A | R_p = %.4f fm\n",
                ahcA, AHC_MeVfm, a0A, RpF);
    std::printf(" Zero fitted parameters. Gates (25%%) committed in RUN_LOG before coding.\n");
    std::printf("=======================================================================\n\n");

    // ==================================================================
    // GA — k(H2): Face-R-corrected CH07 shared-seat energy, joint (R,x) min.
    // Geometry (CH07, byte-identical): protons +-R/2 on axis; seats at +-xR
    // on the perpendicular bisector. p-p: +ahc/R (surplus, point).
    // e-e: +ahc/(2xR) (surplus, point). p-e (x4): deficit ledger, r = R*sqrt(1/4+x^2).
    // ==================================================================
    std::printf("GA  k(H2) — Face-R wall under the CH07 shared-seat well  [anchor: 575 N/m OBSERVED]\n");
    auto E_H2 = [&](double R, double x) {
        const double u = std::sqrt(0.25 + x * x);
        return ahcA / R + ahcA / (2.0 * x * R) + 4.0 * E_deficit(u * R, a0A, ahcA);
    };
    auto E_H2_env = [&](double R, double* xbest) {  // minimise over seat radius x
        double best = 1e300, xb = 0.0;
        for (double x = 0.02; x <= 5.0; x += 2e-4) {
            const double e = E_H2(R, x);
            if (e < best) { best = e; xb = x; }
        }
        if (xbest) *xbest = xb;
        return best;
    };
    double Rmin = 0.0, Emin = 1e300, xAtMin = 0.0;
    for (double R = 0.06; R <= 4.0; R += 1e-3) {
        double xb; const double e = E_H2_env(R, &xb);
        if (e < Emin) { Emin = e; Rmin = R; xAtMin = xb; }
    }
    // refine around Rmin
    for (double R = Rmin - 2e-3; R <= Rmin + 2e-3; R += 5e-5) {
        double xb; const double e = E_H2_env(R, &xb);
        if (e < Emin) { Emin = e; Rmin = R; xAtMin = xb; }
    }
    const double h = 1.5e-3;
    const double kA = (E_H2_env(Rmin + h, nullptr) - 2.0 * E_H2_env(Rmin, nullptr)
                       + E_H2_env(Rmin - h, nullptr)) / (h * h);      // eV/A^2
    const double k_Nm = kA * EVA2_to_Nm;
    const double kerr = (k_Nm - 575.0) / 575.0 * 100.0;
    const double Rerr = (Rmin - 0.7414) / 0.7414 * 100.0;
    const bool gaMin = (Rmin > 0.062 && Rmin < 3.9);
    const bool gaK   = gaMin && std::fabs(kerr) <= 25.0;
    std::printf("    interior minimum: %s at R_min = %.4f A (meas Re 0.7414, %+.1f%%), seat x = %.4f\n",
                gaMin ? "EXISTS" : "NONE", Rmin, Rerr, xAtMin);
    std::printf("    well depth at minimum: %.2f eV (vs 2p+2e at infinity)\n", Emin);
    std::printf("    k = d2E/dR2 = %.1f N/m  vs 575 N/m  (%+.1f%%)   GA(25%%): %s\n",
                k_Nm, kerr, gaK ? "PASS" : "FAIL");
    if (!gaK) ++gate_fails;
    std::printf("\n");

    // ==================================================================
    // GB — NaCl wall correction: sum of (ledger - point) over unlike pairs,
    // rock salt, r0 = 2.820 A (CH02 framework; M = 1.747574 untouched).
    // Required: -74.0 kJ/mol (861.0 -> 787). Like pairs unchanged (surplus).
    // The DIFFERENCE series converges absolutely (s^2 tail) — plain sum, cutoff n=40.
    // ==================================================================
    std::printf("GB  NaCl — Face-R correction to the Evjen sum  [anchors: 861.0 -> 787 kJ/mol OBSERVED]\n");
    const double r0 = 2.820;                                   // [A] OBSERVED (CH02 input)
    double dU_eV = 0.0;                                        // per formula unit
    const int NC = 40;
    for (int i = -NC; i <= NC; ++i)
        for (int j = -NC; j <= NC; ++j)
            for (int k2 = -NC; k2 <= NC; ++k2) {
                if (i == 0 && j == 0 && k2 == 0) continue;
                if (!((i + j + k2) & 1)) continue;             // unlike (deficit) pairs only
                const double r = r0 * std::sqrt(double(i * i + j * j + k2 * k2));
                dU_eV += E_deficit(r, a0A, ahcA) - (-ahcA / r);
            }
    // dU_eV < 0 means MORE binding (ledger deeper than point). Correction to the
    // binding magnitude U_L (positive convention, CH02): dU_L = -dU_eV.
    const double dU_kJ = -dU_eV * eV * NA / 1000.0;            // [kJ/mol] change in U_L
    const double needed = -74.0;
    const double gberr = (dU_kJ - needed) / std::fabs(needed) * 100.0;
    const bool gbSign = (dU_kJ < 0.0);
    const bool gbOK = gbSign && std::fabs(gberr) <= 25.0;
    const double NNenh = (E_deficit(r0, a0A, ahcA) / (-ahcA / r0) - 1.0) * 100.0;
    std::printf("    D3: NN pair ledger/point enhancement at r0: %+.3f%% (exact ledger DEEPENS attraction)\n", NNenh);
    std::printf("    wall correction to U_L: %+.2f kJ/mol  (required %+.1f)  sign %s\n",
                dU_kJ, needed, gbSign ? "binding-reducing (as required)" : "WRONG — adds binding");
    std::printf("    GB(25%% + sign): %s  (err vs required: %+.1f%%)\n", gbOK ? "PASS" : "FAIL", gberr);
    if (!gbOK) ++gate_fails;
    std::printf("\n");

    // ==================================================================
    // GC — alpha lock: Face T, (Z-1)! sequential-tour multiplicity.
    // E_es recomputed from run-1's committed configs (byte-identical geometry).
    // ==================================================================
    std::printf("GC  ALPHA LOCK — Face T: (Z-1)! tour multiplicity  [anchors: 2.224/8.482/28.296 MeV OBSERVED]\n");
    struct Pt { double x, y, z; int q; };
    auto binding = [&](const std::vector<Pt>& s) {
        double U = 0.0;
        for (size_t a = 0; a < s.size(); ++a)
            for (size_t b = a + 1; b < s.size(); ++b) {
                const double dx = s[a].x - s[b].x, dy = s[a].y - s[b].y, dz = s[a].z - s[b].z;
                const double r = std::sqrt(dx * dx + dy * dy + dz * dz);
                if (r < 1e-12) continue;
                U += double(s[a].q * s[b].q) * AHC_MeVfm / r;
            }
        return -U;                                             // positive = bound
    };
    // deuteron: p-e-p, e at midpoint of D  (NP17)
    const std::vector<Pt> vd = { {0,0,0,+1}, {D,0,0,+1}, {D/2,0,0,-1} };
    // triton chain: p-e-p-e-p, spacing D (run-1 config 3)
    const std::vector<Pt> vt = { {0,0,0,+1}, {D,0,0,+1}, {2*D,0,0,+1}, {D/2,0,0,-1}, {1.5*D,0,0,-1} };
    // alpha: 4p tetrahedron edge 2R_p, 2e at midpoints of opposite edges (run-1 config 1)
    const double sa = 2.0 * RpF / (2.0 * std::sqrt(2.0));
    const std::vector<Pt> va = { { sa, sa, sa,+1}, { sa,-sa,-sa,+1}, {-sa, sa,-sa,+1},
                                 {-sa,-sa, sa,+1}, { sa,0,0,-1}, {-sa,0,0,-1} };
    const double Ed = binding(vd), Et = binding(vt), Ea = binding(va);
    const double lock_req = M::B_alpha / Ea;
    const double L[3] = {1.0, 2.0, 6.0};                       // (Z-1)! for Z = 2,3,4
    const double Bm[3] = {M::B_deuteron, M::B_triton, M::B_alpha};
    const double Ees[3] = {Ed, Et, Ea};
    const int    Zs[3] = {2, 3, 4};
    const char*  nm[3] = {"deuteron", "triton  ", "alpha   "};
    const double lockerr = (6.0 - lock_req) / lock_req * 100.0;
    const bool gcLock = std::fabs(lockerr) <= 25.0;
    std::printf("    required alpha boost = B_alpha/E_es = 28.296/%.3f = x%.3f | (Z-1)! at Z=4: x6  (%+.2f%%)\n",
                Ea, lock_req, lockerr);
    bool gcRows = true;
    for (int t = 0; t < 3; ++t) {
        const double Bp = L[t] * Ees[t];
        const double e = (Bp - Bm[t]) / Bm[t] * 100.0;
        const bool ok = std::fabs(e) <= 25.0;
        gcRows = gcRows && ok;
        std::printf("    %s Z=%d: B = (Z-1)! * E_es = %.0f * %.3f = %6.3f MeV  (meas %6.3f, %+.2f%%) %s\n",
                    nm[t], Zs[t], L[t], Ees[t], Bp, Bm[t], e, ok ? "[PASS]" : "[FAIL]");
    }
    const bool gcOK = gcLock && gcRows;
    std::printf("    GC(25%%): %s   (declared POST-DICTION of the run-1 ladder; look-elsewhere\n", gcOK ? "PASS" : "FAIL");
    std::printf("    logged in RUN_LOG; falsifier: Z=5 seat-tour lock must be x24)\n");
    if (!gcOK) ++gate_fails;
    std::printf("\n");

    // ==================================================================
    // D1 — budget-wall rival (NOT gated, FLAGGED formally degenerate with the
    // QM zero-point form): E_wall = sum_seats (hbar^2/2m_e)/s^2, s = p-e distance.
    // ==================================================================
    const double hb2_2me = (M::hbar * M::c) * (M::hbar * M::c)
                         / (2.0 * M::m_e * M::c * M::c) / eV * 1e20;   // [eV*A^2]
    std::printf("D1  BUDGET-WALL RIVAL (diagnostic only; FLM12 confinement hbar/dx, Law-IV/V\n");
    std::printf("    reading; formally degenerate with QM zero-point — capped CONVERGENCE)\n");
    std::printf("    hbar^2/2m_e = %.5f eV*A^2 (engine hbar, m_e)\n", hb2_2me);
    auto E_H2b = [&](double R, double x) {
        const double u = std::sqrt(0.25 + x * x);
        return ahcA * (1.0 + 1.0 / (2.0 * x)) / R - 4.0 * ahcA / (u * R)
             + 2.0 * hb2_2me / (u * R * u * R);
    };
    auto E_H2b_env = [&](double R) {
        double best = 1e300;
        for (double x = 0.02; x <= 5.0; x += 2e-4) {
            const double e = E_H2b(R, x);
            if (e < best) best = e;
        }
        return best;
    };
    double Rb = 0.0, Eb = 1e300;
    for (double R = 0.06; R <= 4.0; R += 1e-3) {
        const double e = E_H2b_env(R);
        if (e < Eb) { Eb = e; Rb = R; }
    }
    const double kb = (E_H2b_env(Rb + h) - 2.0 * E_H2b_env(Rb) + E_H2b_env(Rb - h)) / (h * h) * EVA2_to_Nm;
    std::printf("    H2: R_min = %.4f A (%+.1f%% vs 0.7414), depth %.2f eV, k = %.0f N/m (%+.0f%% vs 575)\n",
                Rb, (Rb - 0.7414) / 0.7414 * 100.0, Eb, kb, (kb - 575.0) / 575.0 * 100.0);
    std::printf("    -> fences the wall's true scale for ROOT-BUDGET; earns nothing here.\n\n");

    // ==================================================================
    // D2 — deuteron anchor consistency: Face R at nuclear scale, Rh = R_p/6.
    // ==================================================================
    const double RhN = RpF / 6.0;                               // cage half-gap [fm]
    const double Ed_ledger = -(2.0 * E_deficit(D / 2.0, RhN, AHC_MeVfm)) - AHC_MeVfm / D;
    const double d2err = (Ed_ledger - M::B_deuteron) / M::B_deuteron * 100.0;
    const double d2shift = (Ed_ledger - Ed) / Ed * 100.0;
    std::printf("D2  DEUTERON ANCHOR (Face R nuclear, cage Rh = R_p/6 = %.4f fm)\n", RhN);
    std::printf("    E_d(ledger) = %.4f MeV (point %.4f; ledger shift %+.2f%%; vs meas 2.224: %+.2f%%)\n",
                Ed_ledger, Ed, d2shift, d2err);
    std::printf("    committed band: ledger must stay within 2%% of the point anchor -> %s\n\n",
                std::fabs(d2shift) <= 2.0 ? "HOLDS" : "BROKEN (cage rule falsified)");

    // ==================================================================
    // Verdict block
    // ==================================================================
    std::printf("=======================================================================\n");
    std::printf(" NP10 RUN 2 — REGISTERED THREE-FIELD CROSS-CHECK SCORE\n");
    std::printf("   target                     predicted        anchor        gate(25%%)\n");
    std::printf("   (a) k(H2)                  %8.1f N/m    575 N/m       %s (%+.1f%%)\n",
                k_Nm, gaK ? "PASS" : "FAIL", kerr);
    std::printf("   (b) NaCl correction        %+8.2f kJ/mol  -74.0 kJ/mol  %s (sign %s)\n",
                dU_kJ, gbOK ? "PASS" : "FAIL", gbSign ? "ok" : "WRONG");
    std::printf("   (c) alpha lock             x6 = (Z-1)!      x%.3f        %s (%+.2f%%)\n",
                lock_req, gcOK ? "PASS" : "FAIL", lockerr);
    std::printf("   CONJUNCTION (GA^GB^GC): %s\n", gate_fails == 0 ? "PASS" : "FAIL");
    std::printf("   committed-gate failures: %d | exit: %d\n", gate_fails, gate_fails == 0 ? 0 : 1);
    std::printf("=======================================================================\n");
    return gate_fails == 0 ? 0 : 1;
}
