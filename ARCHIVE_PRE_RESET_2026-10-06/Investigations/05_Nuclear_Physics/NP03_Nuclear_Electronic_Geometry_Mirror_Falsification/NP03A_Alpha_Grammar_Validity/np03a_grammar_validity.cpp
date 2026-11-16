// ============================================================================
// NP03A — Alpha-Grammar Validity (Claim 1: arithmetic only — proves NO geometry)
//
// Electron-blind by construction: no electron quantity appears in this file.
// Grammar source: sdt/nuclear.hpp (canonical, frozen). Engine: sdt/laws.hpp
// included for hygiene only (no constant consumed).
//
// Phases (thresholds pre-committed in RUN_LOG.md):
//   P0  compile-time: the 7 nuclear.hpp static_asserts (compiling == passing)
//   P1  natural basis: 284/287 alpha-valid, exceptions exactly {H-1,H-2,He-3}
//   P2  exhaustive inverse identity over the wedge 2Z<=A<=3Z-2, Z=2..92
//   P3  decay-vector closure: alpha(-2,0) beta-(+3,-2) EC(-3,+2) n(+1,-1)
//   P4  null control: random (n_d,n_t) must fail the inverse map
//
// HONESTY LABEL: P2 and P3 are algebraic IDENTITIES of the coordinate
// transform (nuclear.hpp header says so itself). Passing them certifies the
// implementation, it does not predict anything. The only empirical content is
// P1: nature's isotopes land in the wedge (OBSERVED consistency, CIAAW basis).
//
// Author: J. C. Harvey, Melbourne. Executed 2026-07-03.
// ============================================================================

#include <sdt/laws.hpp>
#include <sdt/nuclear.hpp>
#include <cstdio>
#include <cstdint>

using namespace sdt::nuclear;

// Fixed-seed LCG (deterministic null control) — MMIX constants.
struct Lcg {
    std::uint64_t s;
    explicit Lcg(std::uint64_t seed) : s(seed) {}
    std::uint64_t next() { s = s * 6364136223846793005ULL + 1442695040888963407ULL; return s; }
    int uniform(int lo, int hi) { // inclusive
        return lo + static_cast<int>(next() % static_cast<std::uint64_t>(hi - lo + 1));
    }
};

int main() {
    std::printf("NP03A — Alpha-Grammar Validity — electron-blind arithmetic audit\n");
    std::printf("Grammar: n_t = A-2Z, n_d = 3Z-A-2; inverse Z = 2+n_d+n_t, A = 4+2n_d+3n_t\n");
    std::printf("============================================================================\n\n");

    // ------------------------------------------------------------------ P0
    std::printf("[P0] compile-time aggregate static_asserts (7) — this binary exists,\n");
    std::printf("     therefore they passed. Runtime echo of the same reduction:\n");
    const auto s = basis_stats;
    std::printf("     total_records=%d  alpha_valid=%d  alpha_invalid=%d\n",
                s.total_records, s.alpha_valid, s.alpha_invalid);
    std::printf("     sum_nd=%d  sum_nt=%d  snap_pairs=%d  odd_valence=%d\n",
                s.sum_nd, s.sum_nt, s.snap_pairs, s.odd_valence);
    const bool p0 = (s.total_records == 287 && s.alpha_valid == 284 && s.alpha_invalid == 3
                  && s.sum_nd == 7658 && s.sum_nt == 5228 && s.snap_pairs == 2560
                  && s.odd_valence == 108);
    std::printf("     P0 gate: %s\n\n", p0 ? "PASS" : "FAIL");

    // ------------------------------------------------------------------ P1
    std::printf("[P1] natural basis (287 CIAAW nuclides): validity + inverse-exactness\n");
    int n_valid = 0, n_invalid = 0, n_inverse_fail = 0;
    int exc_count = 0; bool exc_ok = true;
    for (const auto& raw : natural_basis) {
        const auto g = alpha_grammar(raw.Z, raw.A);
        if (g.valid) {
            ++n_valid;
            const auto inv = inverse_alpha(g.n_d, g.n_t);
            if (inv.Z != raw.Z || inv.A != raw.A) ++n_inverse_fail;
        } else {
            ++n_invalid; ++exc_count;
            char name[12]; nuclide_name(raw.Z, raw.A, name, sizeof(name));
            const bool named = (raw.Z == 1 && raw.A == 1) || (raw.Z == 1 && raw.A == 2)
                            || (raw.Z == 2 && raw.A == 3);
            if (!named) exc_ok = false;
            const auto h = h3_grammar(raw.Z, raw.A);
            std::printf("     exception: %-6s (n_d,n_t)=(%d,%d)  h3=(%d,%d) h3_valid=%s%s\n",
                        name, g.n_d, g.n_t, h.n_d, h.n_t, h.valid ? "yes" : "no",
                        named ? "  [expected]" : "  [UNEXPECTED — FAIL]");
        }
    }
    const bool p1 = (n_valid == 284 && n_invalid == 3 && n_inverse_fail == 0 && exc_ok);
    std::printf("     alpha-valid: %d/287   inverse failures: %d   exceptions as named: %s\n",
                n_valid, n_inverse_fail, exc_ok ? "yes" : "NO");
    std::printf("     P1 gate: %s\n\n", p1 ? "PASS" : "FAIL");

    // ------------------------------------------------------------------ P2
    std::printf("[P2] exhaustive inverse identity over the wedge, Z=2..92  [IDENTITY]\n");
    long wedge_points = 0, inv_fail = 0;
    for (int Z = 2; Z <= 92; ++Z) {
        for (int A = 2 * Z; A <= 3 * Z - 2; ++A) {
            ++wedge_points;
            const auto g = alpha_grammar(Z, A);
            if (!g.valid) { ++inv_fail; continue; }
            const auto inv = inverse_alpha(g.n_d, g.n_t);
            if (inv.Z != Z || inv.A != A) ++inv_fail;
        }
    }
    const bool p2 = (inv_fail == 0);
    std::printf("     wedge points: %ld   failures: %ld\n", wedge_points, inv_fail);
    std::printf("     P2 gate: %s (algebraic identity — certifies code, predicts nothing)\n\n",
                p2 ? "PASS" : "FAIL");

    // ------------------------------------------------------------------ P3
    std::printf("[P3] decay-vector closure over the wedge  [IDENTITY]\n");
    std::printf("     vectors in (n_d,n_t): alpha(-2,0)  beta-(+3,-2)  EC(-3,+2)  n(+1,-1)\n");
    // Each vector must reproduce the physical (Z,A) arithmetic:
    //   alpha: (Z-2, A-4)   beta-: (Z+1, A)   EC: (Z-1, A)   n-emission: (Z, A-1)
    struct Vec { const char* name; int dd, dt, dZ, dA; };
    const Vec vecs[4] = {
        {"alpha", -2,  0, -2, -4},
        {"beta-", +3, -2, +1,  0},
        {"EC   ", -3, +2, -1,  0},
        {"n    ", +1, -1,  0, -1},
    };
    long total_checks = 0, closure_fail = 0;
    for (const auto& v : vecs) {
        long fails = 0;
        for (int Z = 2; Z <= 92; ++Z) {
            for (int A = 2 * Z; A <= 3 * Z - 2; ++A) {
                const auto g = alpha_grammar(Z, A);
                const auto inv = inverse_alpha(g.n_d + v.dd, g.n_t + v.dt);
                ++total_checks;
                // charge/baryon conservation of the physical transition target:
                if (inv.Z != Z + v.dZ || inv.A != A + v.dA) ++fails;
            }
        }
        closure_fail += fails;
        std::printf("     %s : %ld checks, %ld mismatches\n", v.name, wedge_points, fails);
    }
    const bool p3 = (closure_fail == 0);
    std::printf("     total: %ld checks, %ld mismatches\n", total_checks, closure_fail);
    std::printf("     P3 gate: %s (identity; emitted for NP03E count/closure metric)\n\n",
                p3 ? "PASS" : "FAIL");

    // Emit the decay-vector table for NP03E (per-natural-isotope transitions).
    {
        std::FILE* f = std::fopen("Investigations/05_Nuclear_Physics/"
            "NP03_Nuclear_Electronic_Geometry_Mirror_Falsification/"
            "NP03A_Alpha_Grammar_Validity/np03a_decay_vectors.csv", "w");
        if (f) {
            std::fprintf(f, "elem,Z,A,n_d,n_t,alpha_Z,alpha_A,betaM_Z,betaM_A,EC_Z,EC_A,n_Z,n_A\n");
            for (const auto& raw : natural_basis) {
                const auto g = alpha_grammar(raw.Z, raw.A);
                if (!g.valid) continue;
                std::fprintf(f, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                    element_symbol(raw.Z), raw.Z, raw.A, g.n_d, g.n_t,
                    raw.Z - 2, raw.A - 4, raw.Z + 1, raw.A, raw.Z - 1, raw.A, raw.Z, raw.A - 1);
            }
            std::fclose(f);
            std::printf("     wrote np03a_decay_vectors.csv (284 rows)\n\n");
        } else {
            std::printf("     WARNING: could not open np03a_decay_vectors.csv for writing\n\n");
        }
    }

    // ------------------------------------------------------------------ P4
    std::printf("[P4] null control: random (n_d,n_t) vs the inverse map (fixed seed 20260703)\n");
    Lcg rng(20260703ULL);
    const long draws_per = 100000;
    long total_draws = 0, accidental_hits = 0;
    for (const auto& raw : natural_basis) {
        for (long k = 0; k < draws_per; ++k) {
            const int nd = rng.uniform(0, 60);
            const int nt = rng.uniform(0, 60);
            ++total_draws;
            const auto inv = inverse_alpha(nd, nt);
            if (inv.Z == raw.Z && inv.A == raw.A) ++accidental_hits;
        }
    }
    const double hit_frac = static_cast<double>(accidental_hits)
                          / static_cast<double>(total_draws);
    const bool p4 = (hit_frac < 1e-3);
    std::printf("     draws: %ld   accidental inverse hits: %ld   fraction: %.3e\n",
                total_draws, accidental_hits, hit_frac);
    std::printf("     (a priori: exactly one lattice point per (Z,A) in a 61x61 box -> ~2.7e-4)\n");
    std::printf("     P4 gate (< 1e-3): %s — the map carries information\n\n", p4 ? "PASS" : "FAIL");

    // ------------------------------------------------------------------ verdict
    const bool all = p0 && p1 && p2 && p3 && p4;
    std::printf("============================================================================\n");
    std::printf("NP03A SUMMARY\n");
    std::printf("  P0 static_asserts      : %s\n", p0 ? "PASS" : "FAIL");
    std::printf("  P1 natural basis       : %s (284/287, exceptions H-1,H-2,He-3)\n", p1 ? "PASS" : "FAIL");
    std::printf("  P2 inverse identity    : %s [IDENTITY — not a prediction]\n", p2 ? "PASS" : "FAIL");
    std::printf("  P3 decay closure       : %s [IDENTITY — not a prediction]\n", p3 ? "PASS" : "FAIL");
    std::printf("  P4 null control        : %s\n", p4 ? "PASS" : "FAIL");
    std::printf("  OVERALL: %s — Claim 1 certified. NO geometric claim made or implied.\n",
                all ? "PASS" : "FAIL");
    return all ? 0 : 1;
}
