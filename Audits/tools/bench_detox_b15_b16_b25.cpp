// BENCH_DETOX — classify B15/B16/B25 literal rows; recalculate earned totals
// Read-only w.r.t. canon and benchmark tolerances. Does not edit benchmarks_suite.cpp.
#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

using namespace sdt::laws;

namespace {

enum class Origin {
    IndependentMechanism,
    LiteralTargetEcho,
    IdentityClosure,
    BorrowedExternalNumber,
    EngineDerived
};

struct Row {
    const char* id;
    const char* name;
    double sdt;
    double exp;
    double tol_pct;
    const char* printed_cert;
    Origin origin;
    const char* note;
};

[[nodiscard]] auto abs_err_pct(double sdt, double exp) -> double {
    if (exp == 0.0) return std::abs(sdt) * 100.0;
    return std::abs(sdt - exp) / std::abs(exp) * 100.0;
}

} // namespace

int main()
{
    std::puts("================================================================");
    std::puts("BENCHMARK DETOX — B15 / B16 / B25 (and suite recount)");
    std::puts("Pre-registered: literal rows are not earned predictions");
    std::puts("================================================================\n");

    // DELETE TEST: replace every engine symbol with NaN-poison; literals still "pass".
    std::puts("DELETE / CIRCULARITY TESTS");
    {
        const double r_s_sdt = 147.0;
        const double target = 147.09;
        const bool pass = abs_err_pct(r_s_sdt, target) <= 3.0;
        std::printf("  B15 BAO: literal 147.0 vs 147.09  ERR=%.4f%%  TOL=3%%  %s\n",
                    abs_err_pct(r_s_sdt, target), pass ? "PASS-without-engine" : "FAIL");
        std::puts("    engine symbols consulted: NONE");
        std::puts("    STATUS: LITERAL TARGET ECHO — not COMPUTED");
    }
    {
        const double exponent_sdt = 0.5000;
        int npass = 0;
        for (double t : {0.5, 0.5, 0.5}) {
            if (abs_err_pct(exponent_sdt, t) <= 0.05) ++npass;
        }
        std::printf("  B16 transport: literal 0.5000 vs 0.5 x3  %d/3 pass without engine\n", npass);
        std::puts("    STATUS: LITERAL TARGET ECHO — not DERIVED");
    }
    {
        const double E_exact = -79.0052;
        const double target = -79.005;
        std::printf("  B25 exact NR: literal %.4f vs %.3f  ERR=%.4f%%\n",
                    E_exact, target, abs_err_pct(E_exact, target));
        std::puts("    note in source: Pekeris 1959 — borrowed external number");
        std::puts("    STATUS: BORROWED LITERAL — not COMPUTED");
    }
    {
        // B25 variational IS an expression — classify separately
        const double Z = 2.0;
        const double Z_eff = Z - 5.0 / 16.0;
        const double E_var = (2.0 * Z_eff * Z_eff - 4.0 * Z * Z_eff + 1.25 * Z_eff)
                           * measured::Ry_eV;
        std::printf("  B25 variational: expression uses Ry_eV => %.6f eV\n", E_var);
        std::puts("    STATUS: COMPUTED expression, but QM/Hylleraas form (not SDT-native amp)");
        std::puts("    detox label: SHARED-FORM / not independent SDT nuclear prediction");
    }
    std::puts("");

    // Live suite recount from last adversarial run numbers + detox reclass
    // From ADVERSARIAL_FALSIFICATION: RESULTS 56/67 earned, 11 identity, 2 calibrated, 11 PENDING
    const int suite_printed_earned_pass = 56;
    const int suite_printed_earned_denom = 67;
    const int identity_pass = 11;
    const int calibrated_pass = 2;
    const int pending_fail = 11;

    // Detox removals from earned numerator/denominator:
    // B15: 1 row COMPUTED literal
    // B16: 3 rows DERIVED literal
    // B25 exact NR: 1 row COMPUTED literal
    // B25 variational: keep in denom but reflag as SHARED-FORM note — for recount,
    //   treat as still "computed expression" OR move to note-only. Protocol: only
    //   earned if independent. Hylleraas is shared QM form → remove from earned.
    const int literal_rows = 1 + 3 + 1;       // B15 + B16x3 + B25 exact
    const int shared_form_rows = 1;           // B25 variational
    const int remove_from_earned = literal_rows + shared_form_rows;

    // Assume all five currently contribute to the 56 passes (they do: literals pass)
    const int detox_earned_pass = suite_printed_earned_pass - remove_from_earned;
    const int detox_earned_denom = suite_printed_earned_denom - remove_from_earned;

    std::puts("RECOUNTED HEADLINE (detox)");
    std::printf("  printed suite:  %d/%d earned (%.1f%%)\n",
                suite_printed_earned_pass, suite_printed_earned_denom,
                100.0 * suite_printed_earned_pass / suite_printed_earned_denom);
    std::printf("  after detox:    %d/%d earned (%.1f%%)\n",
                detox_earned_pass, detox_earned_denom,
                100.0 * detox_earned_pass / detox_earned_denom);
    std::printf("  removed rows:   %d literal + %d shared-form = %d\n",
                literal_rows, shared_form_rows, remove_from_earned);
    std::printf("  identities:     %d (unchanged; not earned)\n", identity_pass);
    std::printf("  calibrated:     %d (unchanged; not earned)\n", calibrated_pass);
    std::printf("  PENDING fails:  %d (unchanged)\n\n", pending_fail);

    std::puts("RECLASSIFICATION TABLE");
    std::puts("  ID    printed_cert   detox_status              action");
    std::puts("  B15   COMPUTED       LITERAL TARGET ECHO       exclude from earned; PENDING/note");
    std::puts("  B16x3 DERIVED        LITERAL TARGET ECHO       exclude from earned; PENDING/note");
    std::puts("  B25e  COMPUTED       BORROWED LITERAL          exclude from earned; PENDING/note");
    std::puts("  B25v  COMPUTED       SHARED-FORM COMPUTED      exclude from earned until SDT-native");
    std::puts("  B25r  DERIVED        engine R_He=2Rp           retain pending separate radius audit");
    std::puts("");

    std::puts("CANON / SUITE EDIT: not applied (propose-and-wait).");
    std::puts("This instrument documents the recount only.");
    std::puts("================================================================");
    return 0;
}
