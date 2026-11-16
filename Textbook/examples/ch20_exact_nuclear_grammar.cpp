// Chapter 20 — exact nuclear grammar: worked-example instrument.
// Pre-registration: Textbook/validation/ch20_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch20_exact_nuclear_grammar
#include <sdt/laws.hpp>
#include <sdt/nuclear.hpp>

#include "tb_common.hpp"

#include <cstdint>
#include <cstdio>

namespace {

namespace Nu = sdt::nuclear;

// Independent integer solve of (Z,A) = (2,4) + nd (1,2) + nt (1,3) by Cramer's rule (determinant 1).
struct Cnt { long nd, nt; };
Cnt solve(long Z, long A, long Z0, long A0) {
    const long dz = Z - Z0, da = A - A0;
    // [1 1; 2 3] (nd, nt)^T = (dz, da)^T ; det = 1
    return {3 * dz - da, -2 * dz + da};
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 hand-derived compositions by an independent integer solve");
    {
        struct K { long Z, A, nd, nt; const char* name; };
        const K ks[] = {{2, 4, 0, 0, "He-4"}, {3, 6, 1, 0, "Li-6"}, {3, 7, 0, 1, "Li-7"}, {4, 9, 1, 1, "Be-9"}, {5, 10, 3, 0, "B-10"}, {6, 12, 4, 0, "C-12"}};
        bool ok = true;
        for (const auto& k : ks) {
            const Cnt c = solve(k.Z, k.A, 2, 4);
            ok = ok && c.nd == k.nd && c.nt == k.nt;
        }
        tb::check_true("V1", "six compositions (alpha base) match the hand-derived counts", ok);
        const Cnt h = solve(2, 3, 2, 3);
        tb::check_true("V1", "He-3 on the helion base is (0, 0)", h.nd == 0 && h.nt == 0);
    }

    tb::heading("T1 unimodular inversion, exhaustive");
    {
        const int det = 1 * 3 - 1 * 2;
        const int inv[2][2] = {{3, -1}, {-2, 1}};
        const int mat[2][2] = {{1, 1}, {2, 3}};
        bool id_ok = true;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) {
                int s = 0;
                for (int k = 0; k < 2; ++k) s += inv[i][k] * mat[k][j];
                id_ok = id_ok && (s == (i == j ? 1 : 0));
            }
        tb::check_true("T1", "matrix determinant is 1 and the integer inverse times the matrix is the identity", det == 1 && id_ok);
        long bad1 = 0, n1 = 0, bad2 = 0, n2 = 0;
        for (int nd = 0; nd <= 200; ++nd)
            for (int nt = 0; nt <= 200; ++nt) {
                const auto raw = Nu::inverse_alpha(nd, nt);
                const auto g = Nu::alpha_grammar(raw.Z, raw.A);
                ++n1;
                if (!(g.valid && g.n_d == nd && g.n_t == nt)) ++bad1;
            }
        for (int Z = 1; Z <= 120; ++Z)
            for (int A = 1; A <= 400; ++A) {
                const auto g = Nu::alpha_grammar(Z, A);
                if (!g.valid) continue;
                const auto raw = Nu::inverse_alpha(g.n_d, g.n_t);
                ++n2;
                if (!(raw.Z == Z && raw.A == A)) ++bad2;
            }
        tb::note("(n_d, n_t) -> (Z, A) -> (n_d, n_t): %ld points, %ld mismatches ; (Z, A) -> counts -> (Z, A): %ld points, %ld mismatches", n1, bad1, n2, bad2);
        tb::check_true("T1", "no mismatch in either direction", bad1 == 0 && bad2 == 0);
    }

    tb::heading("T2 wedge equivalence, exhaustive");
    {
        long bad = 0, n = 0, bad3 = 0, wedge = 0;
        for (int Z = 1; Z <= 120; ++Z)
            for (int A = 1; A <= 400; ++A) {
                const int N = A - Z;
                const auto g = Nu::alpha_grammar(Z, A);
                const bool a = g.valid, b = (2 * Z <= A && A <= 3 * Z - 2), c = (Z <= N && N <= 2 * Z - 2);
                const bool d = (g.n_t == N - Z) && (g.n_d == 2 * Z - 2 - N);
                ++n;
                if (a) ++wedge;
                if (!(a == b && b == c && d)) ++bad;
                const auto h = Nu::h3_grammar(Z, A);
                if (h.valid != ((A - 2 * Z + 1 >= 0) && (3 * Z - A - 3 >= 0))) ++bad3;
            }
        tb::note("%ld (Z, A) points ; %ld in the alpha wedge ; mismatches %ld ; helion-base mismatches %ld", n, wedge, bad, bad3);
        tb::check_true("T2", "alpha validity equals the wedge equals Z <= N <= 2Z-2 everywhere", bad == 0);
        tb::check_true("T2", "helion-base validity equals its two inequalities everywhere", bad3 == 0);
    }

    tb::heading("T3 the embedded table, recomputed from the raw (Z, A) pairs");
    {
        long total = 0, valid = 0, invalid = 0, snd = 0, snt = 0, snap = 0, odd = 0, sz2 = 0;
        bool increasing = true, wedge_ok = true;
        bool inv_set_ok = true;
        int pz = 0, pa = 0;
        for (const auto& r : Nu::natural_basis) {
            ++total;
            if (!(r.Z > pz || (r.Z == pz && r.A > pa))) increasing = false;
            pz = r.Z;
            pa = r.A;
            const long N = r.A - r.Z, nt = N - r.Z, nd = 2L * r.Z - 2 - N;
            const bool v = nt >= 0 && nd >= 0;
            if (v) {
                ++valid;
                snd += nd;
                snt += nt;
                snap += nt / 2;
                odd += nt % 2;
                sz2 += r.Z - 2;
                wedge_ok = wedge_ok && (r.Z <= N && N <= 2L * r.Z - 2);
            } else {
                ++invalid;
                const bool is_h1 = (r.Z == 1 && r.A == 1), is_h2 = (r.Z == 1 && r.A == 2), is_he3 = (r.Z == 2 && r.A == 3);
                inv_set_ok = inv_set_ok && (is_h1 || is_h2 || is_he3);
                const auto h = Nu::h3_grammar(r.Z, r.A);
                if (is_h1 || is_h2) inv_set_ok = inv_set_ok && !h.valid;
                if (is_he3) inv_set_ok = inv_set_ok && h.valid && h.n_d == 0 && h.n_t == 0;
            }
        }
        tb::note("records %ld ; alpha-valid %ld ; alpha-invalid %ld ; sum n_d %ld ; sum n_t %ld ; sum floor(n_t/2) %ld ; odd %ld ; sum (Z-2) %ld", total, valid, invalid, snd, snt, snap, odd, sz2);
        tb::check_true("T3", "287 records, strictly increasing in (Z, A)", total == 287 && increasing);
        tb::check_true("T3", "alpha-valid 284 and alpha-invalid 3", valid == 284 && invalid == 3);
        tb::check_true("T3", "invalid set is exactly {H-1, H-2, He-3}; helion base: H-1, H-2 invalid, He-3 valid (0,0)", inv_set_ok && invalid == 3);
        tb::check_true("T3", "sum n_d = 7658 and sum n_t = 5228", snd == 7658 && snt == 5228);
        tb::check_true("T3", "sum floor(n_t/2) = 2560 and odd count = 108", snap == 2560 && odd == 108);
        tb::check_true("T3", "sum (n_d + n_t) equals sum (Z - 2) over valid records", snd + snt == sz2);
        tb::check_true("T3", "every valid record satisfies Z <= N <= 2Z - 2", wedge_ok);
        // Engine's stored aggregates agree with the independent recomputation
        tb::check_true("T3", "engine basis_stats equals the independent recomputation", Nu::basis_stats.total_records == total && Nu::basis_stats.alpha_valid == valid && Nu::basis_stats.sum_nd == snd && Nu::basis_stats.sum_nt == snt && Nu::basis_stats.snap_pairs == snap && Nu::basis_stats.odd_valence == odd);
    }

    tb::heading("T4 binary rearrangement identities, exhaustive");
    {
        long splits = 0, bad_id = 0, bad_cls = 0;
        long by_nu[7] = {0, 0, 0, 0, 0, 0, 0};
        for (int Zp = 3; Zp <= 92; ++Zp)
            for (int Ap = 2 * Zp; Ap <= 3 * Zp - 2; ++Ap)
                for (int Zl = 3; Zl <= Zp - 3; ++Zl) {
                    const int Zh = Zp - Zl;
                    for (int Al = 2 * Zl; Al <= 3 * Zl - 2; ++Al)
                        for (int nu = 0; nu <= 6; ++nu) {
                            const int Ah = Ap - nu - Al;
                            if (!(Ah >= 2 * Zh && Ah <= 3 * Zh - 2)) continue;
                            const auto r = Nu::binary_split(Zp, Ap, Zl, Al, Zh, Ah, nu);
                            ++splits;
                            ++by_nu[nu];
                            if (!(r.delta_D == nu - 2 && r.delta_T == -nu)) ++bad_id;
                            Nu::SnapClass want = (nu == 2) ? Nu::SnapClass::clean_2n_snap : (nu == 3) ? Nu::SnapClass::nu3_mixed : (nu == 4) ? Nu::SnapClass::adjacent_4n : Nu::SnapClass::other;
                            if (r.snap_class != want) ++bad_cls;
                        }
                }
        tb::note("splits enumerated: %ld (by nu = 0..6: %ld %ld %ld %ld %ld %ld %ld)", splits, by_nu[0], by_nu[1], by_nu[2], by_nu[3], by_nu[4], by_nu[5], by_nu[6]);
        tb::check_true("T4", "delta D = nu - 2 and delta T = -nu for every split", splits > 0 && bad_id == 0);
        tb::check_true("T4", "the snap class equals the class implied by nu alone for every split", bad_cls == 0);
    }

    tb::heading("T5 the counts are a unimodular relabelling of (Z, N)");
    {
        const int det = 2 * 1 - (-1) * (-1);  // matrix [[2,-1],[-1,1]]
        tb::check_true("T5", "determinant of (Z,N) -> (n_d, n_t) is 1", det == 1);
        long bad = 0, n = 0;
        for (int Z = 3; Z <= 120; ++Z)
            for (int N = Z; N <= 2 * Z - 2; ++N) {
                const int A = Z + N;
                const int nd = 2 * Z - 2 - N, nt = N - Z;
                ++n;
                const bool inv_ok = (Z == 2 + nd + nt) && (N == 2 + nd + 2 * nt);
                const bool ov = Nu::overlays::triton_load(Z, A) == nt && Nu::overlays::deuteron_load(Z, A) == nd && Nu::overlays::y_coord(Z) == Z - 2 && Nu::overlays::x_coord(Z, A) == nd - nt && (Nu::overlays::on_golden_boundary(Z, A) == (2 * A == 5 * Z - 2)) && Nu::overlays::office_pop(Z, A) == ((N - Z) % 2);
                if (!(inv_ok && ov)) ++bad;
            }
        tb::note("%ld wedge points (Z from 3 to 120)", n);
        tb::check_true("T5", "inverse and the six overlay identities hold on every wedge point", bad == 0);
    }

    return tb::finish();
}
