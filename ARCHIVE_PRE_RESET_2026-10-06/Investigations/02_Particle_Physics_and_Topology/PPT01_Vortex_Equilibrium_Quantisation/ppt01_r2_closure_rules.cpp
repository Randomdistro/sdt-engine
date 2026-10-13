// PPT01 R2 (2026-10-05) — closure-rule family for the (p,q) torus-knot equilibrium.
// Pre-registered in R2_REOPEN_2026-10-05.md §4 before this file existed.
// Author: J. C. Harvey, Melbourne.
//
// Conditions (x = R/a):  budget  vT^2 + vP^2 = 1 (units of c)
//                        helix   vP/vT = (q/p)/x
//                        closure R vT/(a vP) = nT/nP   (one action quantum per strand-count nT, nP)
// Closed form:           x^2 = (q nT)/(p nP)
//
// Constants come from sdt/laws.hpp only. mu_N is a BORROWED comparison unit (T3 only).

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace sdt::laws;
namespace M = sdt::laws::measured;

struct Sol { double vT, vP, x; bool ok; };

static Sol closed_form(int p, int q, int nT, int nP) {
    const double x = std::sqrt(double(q) * nT / (double(p) * nP));
    const double r = (double(q) / p) / x;            // vP/vT
    const double vT = 1.0 / std::sqrt(1.0 + r * r);
    return {vT, r * vT, x, true};
}

// Independent numerical solver: damped Newton on F(vT,vP,x) = 0, finite-difference Jacobian.
static void F(const double* u, int p, int q, int nT, int nP, double* f) {
    f[0] = u[0] * u[0] + u[1] * u[1] - 1.0;
    f[1] = u[1] * p * u[2] - u[0] * q;
    f[2] = u[2] * u[0] * nP - nT * u[1];
}
static bool solve3(double A[3][3], const double* b, double* x) {
    double d = A[0][0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1]) - A[0][1]*(A[1][0]*A[2][2]-A[1][2]*A[2][0]) + A[0][2]*(A[1][0]*A[2][1]-A[1][1]*A[2][0]);
    if (std::fabs(d) < 1e-300) return false;
    for (int k = 0; k < 3; ++k) {
        double B[3][3]; for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) B[i][j] = (j == k) ? b[i] : A[i][j];
        x[k] = (B[0][0]*(B[1][1]*B[2][2]-B[1][2]*B[2][1]) - B[0][1]*(B[1][0]*B[2][2]-B[1][2]*B[2][0]) + B[0][2]*(B[1][0]*B[2][1]-B[1][1]*B[2][0])) / d;
    }
    return true;
}
static Sol newton(int p, int q, int nT, int nP, double vT0, double x0) {
    double u[3] = {vT0, std::sqrt(std::max(1e-12, 1.0 - vT0 * vT0)), x0};
    for (int it = 0; it < 200; ++it) {
        double f[3]; F(u, p, q, nT, nP, f);
        double nrm = std::sqrt(f[0]*f[0] + f[1]*f[1] + f[2]*f[2]);
        if (nrm < 1e-14) return {u[0], u[1], u[2], u[0] > 0 && u[1] > 0 && u[2] > 0};
        double J[3][3];
        for (int j = 0; j < 3; ++j) {
            double h = 1e-7, up[3] = {u[0], u[1], u[2]}, um[3] = {u[0], u[1], u[2]}; up[j] += h; um[j] -= h;
            double fp[3], fm[3]; F(up, p, q, nT, nP, fp); F(um, p, q, nT, nP, fm);
            for (int i = 0; i < 3; ++i) J[i][j] = (fp[i] - fm[i]) / (2 * h);
        }
        double rhs[3] = {-f[0], -f[1], -f[2]}, d[3];
        if (!solve3(J, rhs, d)) return {0, 0, 0, false};
        double lam = 1.0;
        for (int bt = 0; bt < 30; ++bt) {
            double un[3] = {u[0] + lam * d[0], u[1] + lam * d[1], u[2] + lam * d[2]};
            double fn[3]; F(un, p, q, nT, nP, fn);
            if (std::sqrt(fn[0]*fn[0] + fn[1]*fn[1] + fn[2]*fn[2]) < nrm) { for (int i = 0; i < 3; ++i) u[i] = un[i]; break; }
            lam *= 0.5;
        }
    }
    return {0, 0, 0, false};
}

static int crossing(int p, int q) { return std::min(p * (q - 1), q * (p - 1)); }

int main() {
    int fails = 0;
    std::printf("PPT01 R2 — closure-rule family (pre-registered 2026-10-05)\n");
    std::printf("==========================================================\n\n");

    // ---- V1 ----
    std::printf("[V1] independent Newton solver vs closed form, 25 starts per case, tolerance 1e-9\n");
    const int PQ[6][2] = {{1,1},{1,2},{2,3},{2,5},{3,4},{3,5}};
    const char* RN[3] = {"A (1,1)", "B (p,q)", "C (q,p)"};
    double worst = 0; int cases = 0, unique_bad = 0;
    for (auto& pq : PQ) for (int r = 0; r < 3; ++r) {
        int p = pq[0], q = pq[1], nT = (r == 0) ? 1 : (r == 1 ? p : q), nP = (r == 0) ? 1 : (r == 1 ? q : p);
        Sol c = closed_form(p, q, nT, nP);
        int conv = 0;
        for (double vt0 : {0.1, 0.3, 0.5, 0.8, 0.95}) for (double x0 : {0.3, 0.8, 1.2, 2.0, 3.5}) {
            Sol s = newton(p, q, nT, nP, vt0, x0);
            if (!s.ok) continue;
            ++conv;
            double e = std::max({std::fabs(s.vT - c.vT), std::fabs(s.vP - c.vP), std::fabs(s.x - c.x)});
            worst = std::max(worst, e);
            if (e > 1e-9) ++unique_bad;
        }
        ++cases;
        if (conv == 0) { ++fails; std::printf("   no convergence: (%d,%d) rule %s\n", p, q, RN[r]); }
    }
    bool v1 = (worst < 1e-9) && unique_bad == 0 && fails == 0;
    std::printf("     cases %d, worst |Newton - closed form| = %.3e, starts landing on another positive root = %d  -> %s\n\n", cases, worst, unique_bad, v1 ? "PASS" : "FAIL");
    if (!v1) ++fails;

    // ---- V2 ----
    std::printf("[V2] torus-knot crossing number min(p(q-1), q(p-1)) against known values\n");
    struct K { int p, q, c; const char* nm; } known[] = {{2,3,3,"trefoil 3_1"},{2,5,5,"5_1"},{3,4,8,"8_19"},{3,5,10,"10_124"},{1,2,0,"unknot"},{1,3,0,"unknot"}};
    bool v2 = true;
    for (auto& k : known) { int c = crossing(k.p, k.q); bool ok = (c == k.c); v2 = v2 && ok; std::printf("     (%d,%d) %-12s computed %2d known %2d %s\n", k.p, k.q, k.nm, c, k.c, ok ? "ok" : "MISMATCH"); }
    for (auto& pq : PQ) { bool kn = pq[0] >= 2 && pq[1] >= 2 && std::gcd(pq[0], pq[1]) == 1; bool cc = crossing(pq[0], pq[1]) > 0; if (kn != cc) v2 = false; }
    std::printf("     nontriviality rule (p,q>=2, gcd=1) agrees with crossing number > 0 for all six -> %s\n\n", v2 ? "PASS" : "FAIL");
    if (!v2) ++fails;

    // ---- V3 ----
    std::printf("[V3] regression against the 2026-04 tool's printed values\n");
    const double hb = M::hbar, c = M::c, me = M::m_e, mp = M::m_p;
    Sol e11 = closed_form(1, 1, 1, 1);
    double a_e = hb / (me * e11.vP * c);
    Sol w3 = closed_form(1, 3, 1, 1);
    double a_p13 = hb / (mp * w3.vP * c), R13 = w3.x * a_p13;
    Sol t23 = closed_form(2, 3, 1, 1);
    double a_p23 = hb / (mp * t23.vP * c);
    double ratio23 = a_e / a_p23;
    bool r1 = std::fabs(a_e - 5.4611e-13) / 5.4611e-13 < 1e-4, r2 = std::fabs(a_p13 - 2.4284e-16) / 2.4284e-16 < 1e-4,
         r3 = std::fabs(R13 - 4.2062e-16) / 4.2062e-16 < 1e-4, r4 = std::fabs(ratio23 - 2011.40) / 2011.40 < 1e-5;
    std::printf("     a_e = %.4e m (5.4611e-13) %s | (1,3) a_p = %.4e (2.4284e-16) %s | (1,3) R_major = %.4e (4.2062e-16) %s | (2,3) a_e/a_p = %.3f (2011.40) %s\n\n",
                a_e, r1 ? "ok" : "X", a_p13, r2 ? "ok" : "X", R13, r3 ? "ok" : "X", ratio23, r4 ? "ok" : "X");
    bool v3 = r1 && r2 && r3 && r4; if (!v3) ++fails;

    std::printf("VALIDATIONS: %s\n\n", (v1 && v2 && v3) ? "all met" : "NOT MET -> G0, object not assessed");
    if (!(v1 && v2 && v3)) return 1;

    // ---- T1 ----
    std::printf("[T1] budget + helix alone (no closure): one-parameter family, proton (p,q)=(2,3)\n");
    int distinct = 0; double lastvT = -1;
    for (double x : {0.5, 1.0, std::sqrt(1.5), 2.0}) {
        double r = (3.0 / 2.0) / x, vT = 1.0 / std::sqrt(1 + r * r), vP = r * vT;
        double res = std::fabs(vT * vT + vP * vP - 1.0) + std::fabs(vP / vT - r);
        std::printf("     x = %.4f  vT/c = %.5f  vP/c = %.5f  residual %.1e\n", x, vT, vP, res);
        if (std::fabs(vT - lastvT) > 1e-6) ++distinct; lastvT = vT;
    }
    std::printf("     distinct solutions: %d  -> RC2 %s\n\n", distinct, distinct >= 2 ? "not met (family confirmed; closure carries the unique answer)" : "MET");

    // ---- T2 ----
    std::printf("[T2] proton (2,3) geometry under the three closure rules; electron (1,1) invariance\n");
    std::printf("     rule      nT nP |    x=R/a   vT/c     vP/c  |  a_p (m)      R_major (m)   R+a (m)\n");
    for (int r = 0; r < 3; ++r) {
        int nT = (r == 0) ? 1 : (r == 1 ? 2 : 3), nP = (r == 0) ? 1 : (r == 1 ? 3 : 2);
        Sol s = closed_form(2, 3, nT, nP);
        double a = hb / (mp * s.vP * c);
        std::printf("     %-8s %2d %2d | %8.5f %8.5f %8.5f | %.4e  %.4e  %.4e\n", RN[r], nT, nP, s.x, s.vT, s.vP, a, s.x * a, s.x * a + a);
    }
    bool inv = true;
    for (int r = 0; r < 3; ++r) {
        const int p = 1, q = 1, nT = (r == 0) ? 1 : (r == 1 ? p : q), nP = (r == 0) ? 1 : (r == 1 ? q : p);
        Sol s = closed_form(p, q, nT, nP);
        inv = inv && std::fabs(s.x - 1) < 1e-15 && std::fabs(s.vT - s.vP) < 1e-15;
    }
    std::printf("     electron (1,1): x = 1, vT = vP = c/sqrt(2) under A, B and C. Note: B and C are defined by (p,q), so at p = q = 1 they equal A by definition;\n"
                "     RC1 is not populated for these three rules (recorded in the run record) -> %s\n\n", inv ? "invariant" : "NOT invariant");

    // ---- T3 ----
    std::printf("[T3] consumer numbers under A, B, C — REPORT ONLY, no rule is selected from this table\n");
    const double gp = law_VI::winding::g_proton, mu = M::mu_P;
    std::printf("     g_proton = %.5f ; mu_p = %.6f mu_N (OBSERVED; mu_N is a BORROWED unit, comparison only)\n", gp, mu);
    std::printf("     NP15 candidates vs mu_p:  rule | C2=gp*vT  (dev)   | C3=gp*vP  (dev)   | C4=C2*x/(1+x) (dev)\n");
    for (int r = 0; r < 3; ++r) {
        int nT = (r == 0) ? 1 : (r == 1 ? 2 : 3), nP = (r == 0) ? 1 : (r == 1 ? 3 : 2);
        Sol s = closed_form(2, 3, nT, nP);
        double C2 = gp * s.vT, C3 = gp * s.vP, C4 = C2 * s.x / (1 + s.x);
        std::printf("                               %-8s| %7.4f (%+6.2f%%) | %7.4f (%+6.2f%%) | %7.4f (%+6.2f%%)\n", RN[r], C2, (C2 - mu) / mu * 100, C3, (C3 - mu) / mu * 100, C4, (C4 - mu) / mu * 100);
    }
    const double ratio = mp / me;
    std::printf("     NP04A a_p/a_e = (m_p/m_e / x)^(1/3):");
    for (int r = 0; r < 3; ++r) { int nT = (r == 0) ? 1 : (r == 1 ? 2 : 3), nP = (r == 0) ? 1 : (r == 1 ? 3 : 2); Sol s = closed_form(2, 3, nT, nP); std::printf("  %s %.4f", RN[r], std::cbrt(ratio / s.x)); }
    std::printf("\n     look-elsewhere register: 3 rules x 3 candidates = 9 combinations added to NP15's 5 design-time candidates (14)\n\n");

    std::printf("SUMMARY: validations met; RC1 not met; RC2 not met; closure rule is not fixed by budget + helix; rule choice changes the proton geometry\n");
    return 0;
}
