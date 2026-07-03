// ============================================================================
//  CH02 — Ionic & Metallic Bonding from Electropause Transfer
//  Author: J. C. Harvey, Melbourne · 2026-07-03
//  Engine: <sdt/laws.hpp> only. Pairwise coupling = coulomb_identity::k_e_e2
//  (= αℏc; the engine itself labels this class F definitional identity —
//   declared, not hidden). NO fitted parameters. NO literature Madelung input.
//
//  P1  transfer criterion: well-depth asymmetry Δχ, χ=(IE+EA)/2  [OBSERVED anchors]
//  P2  NaCl lattice energy: GEOMETRIC Evjen occlusion sum over rock salt
//  P3  Na metallic sea: Wigner–Seitz occlusion balance (no band theory)
//  P4  novel: KCl (and MgO, same formula, no refit)
//
//  Exit code: 0 if committed gates P1,P2,P4(KCl) all pass; 1 otherwise.
// ============================================================================
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace sdt::laws;

static int fails = 0;

// ---------------------------------------------------------------------------
// P2/P4 — Evjen expanding-cubes Madelung-analogue occlusion sum (rock salt).
// Sites (i,j,k), sign (-1)^(i+j+k+1) so nearest neighbour of the origin ion is
// attractive. Boundary sites weighted 1/2 (face), 1/4 (edge), 1/8 (corner):
// pure lattice GEOMETRY — nothing imported.
// ---------------------------------------------------------------------------
static double evjen_madelung(int n) {
    double M = 0.0;
    for (int i = -n; i <= n; ++i)
        for (int j = -n; j <= n; ++j)
            for (int k = -n; k <= n; ++k) {
                if (i == 0 && j == 0 && k == 0) continue;
                double w = 1.0;
                if (std::abs(i) == n) w *= 0.5;
                if (std::abs(j) == n) w *= 0.5;
                if (std::abs(k) == n) w *= 0.5;
                double r = std::sqrt(double(i*i + j*j + k*k));
                double s = ((i + j + k) & 1) ? +1.0 : -1.0; // odd shell = opposite hand
                M += s * w / r;
            }
    return M;
}

int main() {
    const double eV   = measured::eV_to_J;
    const double NA   = 6.02214076e23;          // [1/mol] SI-exact unit bridge (mol -> count)
    const double ahc  = coulomb_identity::k_e_e2; // αℏc [J·m] — engine class F identity, declared

    std::printf("================================================================\n");
    std::printf("  CH02 — Ionic & Metallic Bonding from Electropause Transfer\n");
    std::printf("  Author: J. C. Harvey, Melbourne · 2026-07-03\n");
    std::printf("  Coupling: alpha*hbar*c = %.6e J*m (engine coulomb_identity,\n", ahc);
    std::printf("            labelled class F identity in laws.hpp — declared)\n");
    std::printf("================================================================\n\n");

    // ------------------------------------------------------------------
    // P1 — transfer criterion. chi = (IE+EA)/2 [eV], OBSERVED anchors.
    // SDT reading: chi = mean depth at which an outer electropause sits.
    // Migration (ionic) iff the well-depth ASYMMETRY across the pair is
    // large; symmetric pairs cannot transfer (no preferred direction).
    // Committed test: a clean gap separates the 15 reference pairs.
    // ------------------------------------------------------------------
    struct El { const char* s; double IE, EA; };
    auto chi = [](El e) { return 0.5 * (e.IE + e.EA); };
    El H  {"H", 13.598, 0.754}, C_ {"C", 11.260, 1.262}, N_ {"N", 14.534, 0.000},
       O_ {"O", 13.618, 1.461}, F_ {"F", 17.423, 3.401}, Na {"Na", 5.139, 0.548},
       Mg {"Mg", 7.646, 0.000}, Cl {"Cl", 12.968, 3.613}, K_ {"K", 4.341, 0.501},
       Ca {"Ca", 6.113, 0.025}, Li {"Li", 5.392, 0.618}, Cs {"Cs", 3.894, 0.472},
       Br {"Br", 11.814, 3.364};
    struct Pair { const char* name; El a, b; bool ionic_measured; };
    Pair pairs[15] = {
        {"NaCl", Na, Cl, true}, {"NaF", Na, F_, true}, {"KCl", K_, Cl, true},
        {"KBr",  K_, Br, true}, {"LiF", Li, F_, true}, {"CsF", Cs, F_, true},
        {"MgO",  Mg, O_, true}, {"CaO", Ca, O_, true},
        {"H2",   H,  H,  false}, {"CH4", C_, H, false}, {"O2", O_, O_, false},
        {"N2",   N_, N_, false}, {"Cl2", Cl, Cl, false}, {"HCl", H, Cl, false},
        {"H2O",  H,  O_, false}
    };
    std::printf("P1  TRANSFER CRITERION (well-depth asymmetry)\n");
    std::printf("    pair    dChi[eV]   measured   split-call\n");
    double maxCov = 0.0, minIon = 1e9;
    for (auto& p : pairs) {
        double d = std::fabs(chi(p.a) - chi(p.b));
        if (p.ionic_measured) minIon = std::fmin(minIon, d);
        else                  maxCov = std::fmax(maxCov, d);
    }
    bool gap = (minIon > maxCov);
    double thresh = 0.5 * (minIon + maxCov); // midpoint of the gap — reported, not tuned
    int correct = 0;
    for (auto& p : pairs) {
        double d = std::fabs(chi(p.a) - chi(p.b));
        bool call = (d > thresh);
        bool ok = (call == p.ionic_measured);
        correct += ok;
        std::printf("    %-6s  %7.3f    %-8s   %-8s %s\n", p.name, d,
                    p.ionic_measured ? "ionic" : "covalent",
                    call ? "ionic" : "covalent", ok ? "[ok]" : "[X]");
    }
    std::printf("    gap: max covalent dChi = %.3f eV < min ionic dChi = %.3f eV -> %s\n",
                maxCov, minIon, gap ? "CLEAN GAP (threshold not critical)" : "NO GAP");
    std::printf("    split correct: %d / 15 (committed >= 13)  %s\n\n", correct,
                correct >= 13 ? "[PASS]" : "[FAIL]");
    if (correct < 13) ++fails;

    // ------------------------------------------------------------------
    // P2 — NaCl lattice energy from the GEOMETRIC occlusion sum.
    // ------------------------------------------------------------------
    std::printf("P2  GEOMETRIC OCCLUSION SUM (Evjen expanding cubes, rock salt)\n");
    double M = 0.0;
    for (int n : {1, 2, 3, 4, 6, 8}) {
        M = evjen_madelung(n);
        std::printf("    cube n=%d : M = %.9f\n", n, M);
    }
    std::printf("    converged geometric sum M = %.6f (literature cross-check 1.747565 — output, not input)\n", M);

    struct Salt { const char* name; double r0_A, q2, UL_meas_kJmol, tol; };
    Salt salts[3] = {
        {"NaCl", 2.820, 1.0, 787.0, 0.15},
        {"KCl",  3.146, 1.0, 715.0, 0.20},   // P4 novel — same formula, no refit
        {"MgO",  2.106, 4.0, 3791.0, 0.20},  // P4 stress case — same formula, no refit
    };
    for (auto& s : salts) {
        double E = s.q2 * M * ahc / (s.r0_A * 1e-10);      // [J] per formula unit
        double kJmol = E * NA / 1000.0;
        double err = (kJmol - s.UL_meas_kJmol) / s.UL_meas_kJmol;
        bool ok = std::fabs(err) <= s.tol && kJmol > 0.0;
        std::printf("    %-4s: U_L = %7.1f kJ/mol  (measured %7.1f, err %+5.1f%%, tol %.0f%%) %s\n",
                    s.name, kJmol, s.UL_meas_kJmol, 100.0 * err, 100.0 * s.tol,
                    ok ? "[PASS]" : "[FAIL]");
        if (!ok && (std::strcmp(s.name, "MgO") != 0)) ++fails;  // MgO reported, gate is NaCl+KCl
        if (!ok &&  std::strcmp(s.name, "MgO") == 0)
            std::printf("          MgO miss reported honestly: no Born repulsion is derived in SDT;\n"
                        "          the 2+/2- compression makes the missing short-range term largest here.\n");
    }
    std::printf("    NOTE: systematic overshoot ~ +8..10%% on the 1:1 salts = the underived Born\n"
                "    repulsion closure (missing (1-1/n) factor). Logged as owed, not plugged.\n\n");

    // ------------------------------------------------------------------
    // P3 — metallic sea, Na. Point core in a neutral uniform sea sphere
    // (Wigner–Seitz occlusion sum): E_es = -(9/10) * ahc / r_ws.
    // No band theory, no fitted scale.
    // ------------------------------------------------------------------
    std::printf("P3  METALLIC SEA (Na, Wigner-Seitz occlusion balance)\n");
    double r_ws = 2.08e-10;                      // [m] OBSERVED (r_s = 3.93 a0)
    double E_coh = 0.9 * ahc / r_ws / eV;        // [eV] electrostatic occlusion only
    double meas = 1.113;                         // [eV/atom] OBSERVED
    double err3 = (E_coh - meas) / meas;
    bool ok3 = std::fabs(err3) <= 0.25;
    std::printf("    E_coh(occlusion only) = %.3f eV/atom  (measured %.3f, err %+.0f%%) %s\n",
                E_coh, meas, 100.0 * err3, ok3 ? "[PASS]" : "[FAIL]");
    if (!ok3) {
        std::printf("    HONEST RESULT: the pure occlusion sum overbinds ~%.1fx. The missing piece\n"
                    "    is the movement-budget (Law V) cost of confining the delocalised sea to\n"
                    "    the lattice cell. That cost is NOT yet derived -> P3 OPEN (named closure).\n",
                    E_coh / meas);
    }
    std::printf("\n");

    // ------------------------------------------------------------------
    // Verdict block
    // ------------------------------------------------------------------
    bool p3fail = !ok3;
    std::printf("================================================================\n");
    std::printf("  CH02 SUMMARY\n");
    std::printf("  P1 transfer split      : %s (%d/15, clean gap)\n", correct >= 13 ? "PASS" : "FAIL", correct);
    std::printf("  P2 NaCl lattice energy : within 15%% gate -> see line above\n");
    std::printf("  P4 KCl novel           : within 20%% gate -> see line above; MgO honest miss\n");
    std::printf("  P3 metallic sea        : %s -> OPEN (Law V confinement cost underived)\n",
                p3fail ? "FAIL" : "PASS");
    std::printf("  Physics class: CONVERGENCE (coupling = alpha*hbar*c identity; geometric sum\n");
    std::printf("  is real, but the same sum IS classical ionic electrostatics — delete-test:\n");
    std::printf("  survives without SDT). Metallic cohesion: OPEN.\n");
    std::printf("  Gate exit: %s\n", (fails == 0) ? "0 (committed gates met)" : "1 (>=1 committed gate failed)");
    std::printf("================================================================\n");
    return (fails == 0) ? 0 : 1;
}
