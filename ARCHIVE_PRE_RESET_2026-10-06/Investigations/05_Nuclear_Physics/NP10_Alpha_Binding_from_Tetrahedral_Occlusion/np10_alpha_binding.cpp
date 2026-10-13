// ═══════════════════════════════════════════════════════════════════════
// NP10 — Alpha Binding from Tetrahedral Geometry (NP17 shared-electron premise)
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
// Premise corrected per 2026-07-03 PROMPT note: NP09 occlusion FAILED (-97.3%),
// FLM12-D1 killed the linear volume price. Mechanism here = NP17 shared-electron
// Coulomb well: E = -sum q_i q_j (alpha hbar c)/r_ij, q=+1 proton, -1 electron.
// Configurations + gates pre-committed in RUN_LOG.md BEFORE this file.
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>

namespace M = sdt::laws::measured;

struct Pt { double x, y, z; int q; };

static const double HBARC = (M::hbar * M::c / M::MeV_to_J) * 1e15;  // MeV*fm
static const double AHC   = M::alpha * HBARC;                       // k_e e^2 [MeV*fm]
static const double R_p   = M::R_p * 1e15;                          // fm

static double binding(const std::vector<Pt>& s) {
    double U = 0.0;
    for (size_t i = 0; i < s.size(); ++i)
        for (size_t j = i + 1; j < s.size(); ++j) {
            const double dx = s[i].x-s[j].x, dy = s[i].y-s[j].y, dz = s[i].z-s[j].z;
            const double r = std::sqrt(dx*dx + dy*dy + dz*dz);
            if (r < 1e-12) continue;
            U += double(s[i].q * s[j].q) * AHC / r;
        }
    return -U;   // positive = bound
}

// Alpha: 4p tetrahedron edge a, 2e at midpoints of two opposite edges (NP17-exact)
static double E_alpha(double a) {
    const double s = a / (2.0 * std::sqrt(2.0));
    std::vector<Pt> v = {
        { s,  s,  s, +1}, { s, -s, -s, +1},
        {-s,  s, -s, +1}, {-s, -s,  s, +1},
        { s,  0,  0, -1}, {-s,  0,  0, -1},
    };
    return binding(v);
}

// Triton chain: p-e-p-e-p collinear, adjacent p-p spacing Dsp, e at bond midpoints
static double E_triton_chain(double Dsp) {
    std::vector<Pt> v = {
        {0,0,0,+1}, {Dsp,0,0,+1}, {2*Dsp,0,0,+1},
        {Dsp/2,0,0,-1}, {1.5*Dsp,0,0,-1},
    };
    return binding(v);
}

// Triton triangle: 3p equilateral edge Dsp, e at midpoints of two edges
static double E_triton_tri(double Dsp) {
    const double h = Dsp * std::sqrt(3.0) / 2.0;
    std::vector<Pt> v = {
        {0,0,0,+1}, {Dsp,0,0,+1}, {Dsp/2,h,0,+1},
        {Dsp/2,0,0,-1},                     // mid(p0,p1)
        {0.75*Dsp, h/2, 0, -1},             // mid(p1,p2)
    };
    return binding(v);
}

int main() {
    const double B_a_meas = M::B_alpha;    // 28.296 (engine)
    const double B_t_meas = M::B_triton;   // 8.482  (engine)
    const double D = 2.0*R_p + R_p/3.0;    // NP17 deuteron bond length

    std::printf("NP10 — Alpha Binding, NP17 shared-electron premise (J. C. Harvey, 2026-07-03)\n");
    std::printf("E = -sum q_i q_j (alpha hbar c)/r_ij | alpha-hbar-c = %.4f MeV*fm | R_p = %.4f fm\n",
                AHC, R_p);
    std::printf("====================================================================\n\n");

    // ---------- G2: size (blind 1% gate) ----------
    const double R_He_pred = 2.0 * R_p;                  // = nuclear::R_He_predicted
    const double R_He_meas = M::R_He * 1e15;
    const double g2 = (R_He_pred - R_He_meas) / R_He_meas * 100.0;
    std::printf("[G2] R_He = 2 R_p = %.4f fm  vs meas %.4f fm  (%+.2f%%)  %s\n",
                R_He_pred, R_He_meas, g2, std::fabs(g2) <= 1.0 ? "PASS(1%)" : "FAIL(1%)");
    std::printf("     NOTE: existing laws.hpp result (nuclear::R_He_predicted, class C-flagged)\n");
    std::printf("     — re-verified here, NOT claimed as a new NP10 discovery.\n\n");

    // ---------- G1: headline alpha binding (committed config 1) ----------
    const double Ea1 = E_alpha(2.0 * R_p);   // NP17-exact
    const double Ea2 = E_alpha(D);           // D-spaced variant
    const double g1 = (Ea1 - B_a_meas) / B_a_meas * 100.0;
    std::printf("[G1] alpha (config 1, NP17-exact, a = 2R_p = %.4f fm): E = %.3f MeV\n",
                2.0*R_p, Ea1);
    std::printf("     vs 28.296 MeV: %+.1f%%  -> %s\n", g1,
                std::fabs(g1) <= 20.0 ? "PASS(20%)" : "FAIL(20%) -> OPEN");
    std::printf("     alpha (config 2, a = D = %.4f fm): E = %.3f MeV (%+.1f%%)\n",
                D, Ea2, (Ea2 - B_a_meas)/B_a_meas*100.0);
    const double R_lock = B_a_meas - Ea1;
    std::printf("     LOCK REMAINDER (what the tetrahedral lock must supply):\n");
    std::printf("       R_lock = 28.296 - %.3f = %.3f MeV  (%.1f%% of the total;\n",
                Ea1, R_lock, R_lock / B_a_meas * 100.0);
    std::printf("       boost factor needed on electrostatics: x%.2f)\n\n", B_a_meas / Ea1);

    // ---------- G5: inversion (record) ----------
    {
        double lo = 0.05, hi = 4.0;
        for (int it = 0; it < 80; ++it) { double m = (lo+hi)/2; (E_alpha(m) > B_a_meas ? lo : hi) = m; }
        const double a_req = (lo + hi) / 2;
        std::printf("[G5] edge required for 28.296 MeV electrostatically: a = %.3f fm", a_req);
        std::printf("  (%s 2R_p = %.3f fm -> %s)\n\n", a_req < 2.0*R_p ? "<" : ">=", 2.0*R_p,
                    a_req < 2.0*R_p ? "UNPHYSICAL: lock remainder is real, not a spacing choice"
                                    : "physical");
    }

    // ---------- G3: ratio structure test ----------
    const double Et_chain = E_triton_chain(D);
    const double Et_tri   = E_triton_tri(D);
    const double ratio_meas = B_a_meas / B_t_meas;
    std::printf("[G3] triton (chain p-e-p-e-p, spacing D): E = %.3f MeV (meas %.3f, %+.1f%%)\n",
                Et_chain, B_t_meas, (Et_chain - B_t_meas)/B_t_meas*100.0);
    std::printf("     triton (triangle variant):           E = %.3f MeV (%+.1f%%)\n",
                Et_tri, (Et_tri - B_t_meas)/B_t_meas*100.0);
    struct RatioRow { const char* name; double pred; };
    const RatioRow rr[] = {
        {"config1/chain (2R_p vs D)", Ea1 / Et_chain},
        {"config2/chain (D vs D)   ", Ea2 / Et_chain},
        {"config2/triangle (D vs D)", Ea2 / Et_tri},
    };
    std::printf("     ratio B_alpha/B_triton: measured = %.3f, gate +/-20%%\n", ratio_meas);
    bool anyRatioPass = false;
    for (const auto& r : rr) {
        const double e = (r.pred - ratio_meas) / ratio_meas * 100.0;
        const bool p = std::fabs(e) <= 20.0;
        anyRatioPass = anyRatioPass || p;
        std::printf("       %s = %.3f  (%+.1f%%)  %s\n", r.name, r.pred, e, p ? "PASS" : "FAIL");
    }
    std::printf("     -> %s\n\n", anyRatioPass
        ? "ratio survives: lock term may be a common factor"
        : "ALL ratio pairings FAIL: the missing lock term is NOT a common\n"
          "        multiplicative factor — it grows with coordination/interlock number.\n"
          "        (alpha needs a much larger boost than the triton.)");

    // implied per-nucleus boost factors (diagnostic for the lock's scaling)
    std::printf("     implied boost factors: alpha x%.2f (cfg1), triton x%.2f (chain),\n",
                B_a_meas / Ea1, B_t_meas / Et_chain);
    std::printf("     deuteron x%.3f (NP17: 2.200 vs 2.224) -> lock grows super-linearly\n",
                2.224 / 2.200);
    std::printf("     with interleave count (d:1.01, t:%.2f, a:%.2f).\n\n",
                B_t_meas / Et_chain, B_a_meas / Ea1);

    // ---------- G4: mu_alpha = 0 ----------
    std::printf("[G4] mu_alpha = 0: two interlocked deuteron units with opposed circulation\n");
    std::printf("     -> moments cancel pairwise. Consistent, but DEGENERATE (declared in\n");
    std::printf("     RUN_LOG: every model predicts 0 for spin-0). No SDT-discriminating content.\n\n");

    // ---------- Verdict ----------
    std::printf("====================================================================\n");
    std::printf("VERDICT (numeric):\n");
    std::printf("  G1 headline 28.296 : E_es = %.3f MeV (%+.1f%%) FAIL -> OPEN;\n", Ea1, g1);
    std::printf("                       lock remainder = %.2f MeV (%.0f%% of total)\n",
                R_lock, R_lock / B_a_meas * 100.0);
    std::printf("  G2 R_He = 2R_p     : %+.2f%% PASS(1%%) — pre-existing engine result, re-verified\n", g2);
    std::printf("  G3 ratio 3.336     : %s\n", anyRatioPass ? "at least one pairing PASS"
                : "ALL FAIL -> lock is coordination-dependent (new constraint)");
    std::printf("  G4 mu_alpha = 0    : consistent — DEGENERATE\n");
    std::printf("  G5 inversion       : required edge < 2R_p -> unphysical -> remainder real\n");
    return 0;
}
