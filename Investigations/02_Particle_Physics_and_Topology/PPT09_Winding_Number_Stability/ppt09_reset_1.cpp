// PPT09 blank-slate run 1 (2026-10-06): torus-knot classification, envelope volume ratios, reconnection enumeration.
// Pre-registered in PPT09_RESET_ASSESSMENT_2026-10-06.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <numbers>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

// ---------- Laurent polynomials over Z ----------
struct LP {
    std::map<int, long long> c;
    void clean() { for (auto it = c.begin(); it != c.end();) it = it->second == 0 ? c.erase(it) : std::next(it); }
    bool zero() const { return c.empty(); }
};
static LP mono(int e, long long k) { LP r; if (k) r.c[e] = k; return r; }
static LP operator+(const LP& a, const LP& b) { LP r = a; for (auto& [e, k] : b.c) r.c[e] += k; r.clean(); return r; }
static LP operator-(const LP& a, const LP& b) { LP r = a; for (auto& [e, k] : b.c) r.c[e] -= k; r.clean(); return r; }
static LP operator*(const LP& a, const LP& b) { LP r; for (auto& [e1, k1] : a.c) for (auto& [e2, k2] : b.c) r.c[e1 + e2] += k1 * k2; r.clean(); return r; }
static bool operator==(const LP& a, const LP& b) { return a.c == b.c; }
using Mat = std::vector<std::vector<LP>>;
static Mat ident(int n) { Mat m(n, std::vector<LP>(n)); for (int i = 0; i < n; ++i) m[i][i] = mono(0, 1); return m; }
static Mat mul(const Mat& a, const Mat& b) { int n = (int)a.size(); Mat r(n, std::vector<LP>(n)); for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) { LP s; for (int k = 0; k < n; ++k) s = s + a[i][k] * b[k][j]; r[i][j] = s; } return r; }
static bool isIdent(const Mat& m) { int n = (int)m.size(); Mat I = ident(n); for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (!(m[i][j] == I[i][j])) return false; return true; }
static LP det(const Mat& m) {
    int n = (int)m.size(); if (n == 0) return mono(0, 1); if (n == 1) return m[0][0];
    LP s;
    for (int j = 0; j < n; ++j) {
        Mat mi(n - 1, std::vector<LP>(n - 1));
        for (int r = 1; r < n; ++r) { int cc = 0; for (int k = 0; k < n; ++k) if (k != j) mi[r - 1][cc++] = m[r][k]; }
        LP t = m[0][j] * det(mi); s = (j % 2 == 0) ? s + t : s - t;
    }
    return s;
}
// reduced Burau matrices (n = p-1); letter +i / -i, i = 1..p-1
static Mat gen(int p, int letter) {
    int n = p - 1, i = std::abs(letter), r = i - 1; Mat m = ident(n);
    for (int j = 0; j < n; ++j) m[r][j] = LP();
    if (letter > 0) { if (r - 1 >= 0) m[r][r - 1] = mono(1, 1); m[r][r] = mono(1, -1); if (r + 1 < n) m[r][r + 1] = mono(0, 1); }
    else { if (r - 1 >= 0) m[r][r - 1] = mono(0, 1); m[r][r] = mono(-1, -1); if (r + 1 < n) m[r][r + 1] = mono(-1, 1); }
    return m;
}
static Mat rep(int p, const std::vector<int>& w) { Mat m = ident(p - 1); for (int l : w) m = mul(m, gen(p, l)); return m; }
// exact division of a Laurent polynomial by 1 + t + ... + t^(p-1)
static LP divideByGeom(const LP& num, int p, bool& exact) {
    exact = true; if (num.zero()) return num;
    int mn = num.c.begin()->first, mx = num.c.rbegin()->first; std::vector<long long> a(mx - mn + 1, 0);
    for (auto& [e, k] : num.c) a[e - mn] = k;
    int d = p - 1, deg = (int)a.size() - 1; std::vector<long long> q(std::max(0, deg - d + 1), 0);
    for (int k = deg; k >= d; --k) { long long cq = a[k]; q[k - d] = cq; for (int j = 0; j <= d; ++j) a[k - d + j] -= cq; }
    for (int k = 0; k < d && k < (int)a.size(); ++k) if (a[k] != 0) exact = false;
    LP r; for (int k = 0; k < (int)q.size(); ++k) if (q[k]) r.c[k + mn] = q[k]; return r;
}
static LP normalise(const LP& x) {
    if (x.zero()) return x; int mn = x.c.begin()->first; LP r; for (auto& [e, k] : x.c) r.c[e - mn] = k;
    long long s1 = 0; for (auto& [e, k] : r.c) s1 += k;
    long long sg = s1 != 0 ? (s1 > 0 ? 1 : -1) : (r.c.rbegin()->second > 0 ? 1 : -1);
    if (sg < 0) for (auto& [e, k] : r.c) k = -k; return r;
}
static LP alexander(int p, const std::vector<int>& w, bool* ok = nullptr) {
    Mat psi = rep(p, w), A = ident(p - 1);
    for (int i = 0; i < p - 1; ++i) for (int j = 0; j < p - 1; ++j) A[i][j] = A[i][j] - psi[i][j];
    bool ex; LP d = divideByGeom(det(A), p, ex); if (ok) *ok = ex; return normalise(d);
}
static std::string str(const LP& x) {
    if (x.zero()) return "0"; std::string s; bool first = true;
    for (auto& [e, k] : x.c) {
        long long a = std::llabs(k); std::string term = (e == 0) ? std::to_string(a) : ((a == 1 ? "" : std::to_string(a)) + "t" + (e == 1 ? "" : "^" + std::to_string(e)));
        if (e == 0 && false) term = "";
        s += first ? (k < 0 ? "-" : "") : (k < 0 ? " - " : " + "); s += term; first = false;
    }
    return s;
}
static long long evalAt(const LP& x, long long t) { double s = 0; for (auto& [e, k] : x.c) s += k * std::pow((double)t, e); return std::llround(s); }
// closed formula route for T(p,q): (t^{pq}-1)(t-1) / ((t^p-1)(t^q-1)), exact
static LP torusClosed(int p, int q, bool& exact) {
    LP N = (mono(p * q, 1) - mono(0, 1)) * (mono(1, 1) - mono(0, 1)), D = (mono(p, 1) - mono(0, 1)) * (mono(q, 1) - mono(0, 1));
    int dd = D.c.rbegin()->first, nd = N.c.rbegin()->first; std::vector<long long> a(nd + 1, 0), b(dd + 1, 0), qv(std::max(0, nd - dd + 1), 0);
    for (auto& [e, k] : N.c) a[e] = k; for (auto& [e, k] : D.c) b[e] = k;
    for (int k = nd; k >= dd; --k) { long long cq = a[k] / b[dd]; qv[k - dd] = cq; for (int j = 0; j <= dd; ++j) a[k - dd + j] -= cq * b[j]; }
    exact = true; for (long long v : a) if (v != 0) exact = false;
    LP r; for (int k = 0; k < (int)qv.size(); ++k) if (qv[k]) r.c[k] = qv[k]; return normalise(r);
}
// components and linking numbers of a braid closure
struct Link { int comps; std::vector<int> compOf; std::map<std::pair<int, int>, int> lk2; };   // lk2 = 2 x linking number
static Link topology(int p, const std::vector<int>& w) {
    std::vector<int> occ(p), pos(p); std::iota(occ.begin(), occ.end(), 0); std::iota(pos.begin(), pos.end(), 0);
    struct X { int a, b, s; }; std::vector<X> xs;
    for (int l : w) { int i = std::abs(l) - 1; xs.push_back({occ[i], occ[i + 1], l > 0 ? 1 : -1}); std::swap(occ[i], occ[i + 1]); }
    std::vector<int> perm(p); for (int pp = 0; pp < p; ++pp) perm[occ[pp]] = pp;   // strand starting at occ[pp] ends at pp
    Link L; L.compOf.assign(p, -1); L.comps = 0;
    for (int k = 0; k < p; ++k) if (L.compOf[k] < 0) { int x = k; while (L.compOf[x] < 0) { L.compOf[x] = L.comps; x = perm[x]; } ++L.comps; }
    for (auto& x : xs) { int ca = L.compOf[x.a], cb = L.compOf[x.b]; if (ca != cb) L.lk2[{std::min(ca, cb), std::max(ca, cb)}] += x.s; }
    return L;
}
static std::string lkStr(const Link& L) { if (L.lk2.empty()) return "-"; std::string s; for (auto& [k, v] : L.lk2) s += "lk(" + std::to_string(k.first) + "," + std::to_string(k.second) + ")=" + std::to_string(v / 2.0).substr(0, 4) + " "; return s; }
static std::vector<int> torusWord(int p, int q) { std::vector<int> w; for (int k = 0; k < q; ++k) for (int i = 1; i < p; ++i) w.push_back(i); return w; }
static std::vector<int> sigmaPow(int n) { return std::vector<int>(std::abs(n), n > 0 ? 1 : -1); }

int main() {
    std::printf("PPT09 blank-slate run 1 (pre-registered 2026-10-06)\n====================================================\n\n");
    int fails = 0;
    // ---- V1
    bool v1 = true;
    for (int p = 2; p <= 4; ++p) for (int i = 1; i < p; ++i) v1 = v1 && isIdent(mul(gen(p, i), gen(p, -i))) && isIdent(mul(gen(p, -i), gen(p, i)));
    for (int i = 1; i <= 2; ++i) { Mat a = mul(mul(gen(4, i), gen(4, i + 1)), gen(4, i)), b = mul(mul(gen(4, i + 1), gen(4, i)), gen(4, i + 1)); for (int x = 0; x < 3; ++x) for (int y = 0; y < 3; ++y) v1 = v1 && (a[x][y] == b[x][y]); }
    { Mat a = mul(gen(4, 1), gen(4, 3)), b = mul(gen(4, 3), gen(4, 1)); for (int x = 0; x < 3; ++x) for (int y = 0; y < 3; ++y) v1 = v1 && (a[x][y] == b[x][y]); }
    std::printf("[V1] Burau inverses (p = 2..4), braid relations and far commutation (p = 4), exact: %s\n", v1 ? "met" : "NOT MET");
    if (!v1) ++fails;
    // ---- V2
    struct KA { const char* nm; int p; std::vector<int> w; const char* delta; int comps; long long det; } kas[] = {
        {"unknot sigma1 (2 strands)", 2, {1}, "1", 1, 1}, {"Hopf sigma1^2", 2, {1, 1}, "-1 + t", 2, 0}, {"trefoil sigma1^3", 2, {1, 1, 1}, "1 - t + t^2", 1, 3},
        {"cinquefoil sigma1^5", 2, sigmaPow(5), "1 - t + t^2 - t^3 + t^4", 1, 5}, {"2-unlink sigma1^0", 2, {}, "0", 2, 0},
        {"figure-eight (s1 s2^-1)^2", 3, {1, -2, 1, -2}, "-1 + 3t - t^2", 1, 5}};   // expected values in the registered normal form (amendment 1)
    bool v2 = true;
    for (auto& k : kas) {
        bool ok; LP d = alexander(k.p, k.w, &ok); Link L = topology(k.p, k.w); long long dm = std::llabs(evalAt(d, -1));
        bool good = ok && str(d) == k.delta && L.comps == k.comps && (k.det == 0 ? true : dm == k.det) && (k.comps == 2 && std::string(k.nm).find("Hopf") != std::string::npos ? L.lk2.begin()->second == 2 : true);
        if (std::string(k.nm).find("2-unlink") != std::string::npos) good = good && L.lk2.empty();
        std::printf("     %-28s Delta = %-26s comps %d det %lld %s\n", k.nm, str(d).c_str(), L.comps, dm, good ? "(as expected)" : "(MISMATCH)");
        v2 = v2 && good;
    }
    std::printf("[V2] known answers (unknot, Hopf lk = 1, trefoil, cinquefoil, 2-unlink, figure-eight; determinants 3, 5, 5): %s\n", v2 ? "met" : "NOT MET");
    if (!v2) ++fails;
    // ---- V3
    bool v3 = true;
    struct CB { int p; std::vector<int> w; } cbs[] = {{2, {1, 1, 1}}, {3, {1, -2, 1, -2}}, {2, sigmaPow(5)}};
    for (auto& cb : cbs) {
        LP d0 = alexander(cb.p, cb.w);
        for (int i = 1; i < cb.p; ++i) { std::vector<int> w = {i}; w.insert(w.end(), cb.w.begin(), cb.w.end()); w.push_back(-i); v3 = v3 && (alexander(cb.p, w) == d0); }
        for (int s : {1, -1}) { std::vector<int> w = cb.w; w.push_back(s * cb.p); v3 = v3 && (alexander(cb.p + 1, w) == d0); }
    }
    std::printf("[V3] Delta unchanged under conjugation and Markov stabilisation for the control braids: %s\n\n", v3 ? "met" : "NOT MET");
    if (!v3) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // ---- T1
    std::printf("[T1] torus knots T(p,q), Delta by Burau (route 1) and closed formula (route 2)\n");
    struct Nm { int p, q; const char* tab; } nms[] = {{1, 1, "1"}, {1, 2, "1"}, {2, 3, "1 - t + t^2"}, {2, 5, "1 - t + t^2 - t^3 + t^4"}, {3, 4, "1 - t + t^3 - t^5 + t^6"}};
    bool tab = true;
    for (auto& n : nms) { bool e1, e2; LP d1 = alexander(n.p, torusWord(n.p, n.q), &e1), d2 = torusClosed(n.p, n.q, e2); Link L = topology(n.p, torusWord(n.p, n.q));
        bool good = e1 && e2 && d1 == d2 && str(d1) == n.tab; tab = tab && good;
        std::printf("     (%d,%d): Delta = %-26s routes %s ; knot-table %s ; det %lld ; comps %d ; diagram crossings %zu\n", n.p, n.q, str(d1).c_str(), d1 == d2 ? "agree" : "DIFFER", good ? "consistent" : "INCONSISTENT", std::llabs(evalAt(d1, -1)), L.comps, torusWord(n.p, n.q).size()); }
    int viol = 0, nchk = 0, route_diff = 0;
    for (int p = 1; p <= 4; ++p) for (int q = 1; q <= 9; ++q) if (std::gcd(p, q) == 1) {
        bool e1, e2; LP d1 = alexander(p, torusWord(p, q), &e1), d2 = torusClosed(p, q, e2); ++nchk;
        if (!(e1 && e2 && d1 == d2)) ++route_diff;
        bool unk = (str(d1) == "1"), expectKnot = (std::min(p, q) >= 2); if (unk == expectKnot) ++viol; }
    std::printf("     all coprime (p,q), 1<=p<=4, 1<=q<=9: %d checked ; route disagreements %d ; violations of 'Delta != 1 iff min(p,q) >= 2': %d\n", nchk, route_diff, viol);
    std::printf("     non-coprime controls (components = gcd): ");
    bool gc = true; for (auto pq : std::vector<std::pair<int, int>>{{2, 2}, {2, 4}, {3, 3}, {3, 6}}) { int cmp = topology(pq.first, torusWord(pq.first, pq.second)).comps, g = std::gcd(pq.first, pq.second); gc = gc && cmp == g; std::printf("(%d,%d): %d/%d ", pq.first, pq.second, cmp, g); }
    std::printf("-> %s\n", gc ? "as expected" : "MISMATCH");
    std::printf("     R1 (H1 rejected if any violation or route disagreement): %s ; knot-table values for the five named pairs: %s\n\n", (viol || route_diff) ? "MET (rejected)" : "not met (H1 consistent)", tab ? "consistent" : "INCONSISTENT");

    // ---- T2
    auto geom = [&](int p, int q, double l, double& R, double& a, double& V) { double vT = std::sqrt(double(p) / (p + q)), vP = std::sqrt(double(q) / (p + q)); R = l / vT; a = l / vP; V = 2 * std::numbers::pi * std::numbers::pi * R * a * a; };
    std::printf("[T2] envelope volume V = 2 pi^2 R a^2 (R = l/(v_T/c), a = l/(v_P/c), l = hbar/(m c)), in units of l_(1,1)^3\n");
    double R11, a11, V11, R12, a12, V12; geom(1, 1, 1.0, R11, a11, V11); geom(1, 2, 1.0, R12, a12, V12);
    std::printf("     (1,1) at l = 1: R = %.5f a = %.5f R/a = %.5f V = %.5f ; (1,2) at l = 1: R = %.5f a = %.5f R/a = %.5f V = %.5f\n", R11, a11, R11 / a11, V11, R12, a12, R12 / a12, V12);
    double S1 = V12 / (2 * V11);
    double lS2 = 0.5; double R, a, V; geom(1, 2, lS2, R, a, V); double S2 = V / (2 * V11);
    double aTarget = a11; double lS3b = aTarget * std::sqrt(2.0 / 3.0); geom(1, 2, lS3b, R, a, V); double S3 = V / (2 * V11);
    std::printf("     V(1,2)/(2 V(1,1)):  S1 equal mass (l_2 = l_1) = %.5f ;  S2 mass conserved (l_2 = l_1/2) = %.5f [primary] ;  S3 equal minor radius (l_2 = %.5f l_1) = %.5f\n", S1, S2, lS3b, S3);
    const char* cls = S2 >= 1.05 ? "H2 supported (>= 1.05)" : (S2 >= 0.95 ? "equal within 5%" : "opposite sign (< 0.95)");
    std::printf("     R2 (H2 rejected if S2 ratio < 0.95): S2 = %.5f -> %s ; look-elsewhere count 3 ; any convention with ratio within 1e-6 of 1: %s\n", S2, cls, (std::fabs(S1 - 1) < 1e-6 || std::fabs(S2 - 1) < 1e-6 || std::fabs(S3 - 1) < 1e-6) ? "yes" : "none");
    double le = M::hbar / (M::m_e * M::c);
    std::printf("     report-only scale mismatch: P_eff = %.4e Pa ; electron-scale envelope V(1,1) = %.4e m^3 ; P_eff V = %.4e J (= %.4e MeV)\n\n", law_III::P_eff, V11 * le * le * le, law_III::P_eff * V11 * le * le * le, law_III::P_eff * V11 * le * le * le / 1.602176634e-13);

    // ---- T3
    std::printf("[T3] single reconnection events on braid diagrams: oriented smoothing (delete a letter), crossing change (invert a letter)\n");
    struct BD { const char* nm; int p; std::vector<int> w; } bds[] = {{"T(1,2) = T(2,1): sigma1", 2, {1}}, {"T(2,3): sigma1^3", 2, {1, 1, 1}}, {"T(2,5): sigma1^5", 2, sigmaPow(5)}, {"T(3,4): (s1 s2)^4", 3, torusWord(3, 4)}};
    for (auto& b : bds) {
        bool ok; LP d0 = alexander(b.p, b.w, &ok); Link L0 = topology(b.p, b.w);
        std::printf("   %s: Delta = %s ; comps %d\n", b.nm, str(d0).c_str(), L0.comps);
        std::set<std::string> seen;
        for (size_t j = 0; j < b.w.size(); ++j) {
            for (int op = 0; op < 2; ++op) {
                std::vector<int> w = b.w; if (op == 0) w.erase(w.begin() + j); else w[j] = -w[j];
                LP d = alexander(b.p, w); Link L = topology(b.p, w);
                std::string line = std::string(op == 0 ? "smoothing      " : "crossing change ") + " -> Delta = " + str(d) + " ; comps " + std::to_string(L.comps) + " ; " + lkStr(L);
                if (seen.insert(line).second) std::printf("      %s\n", line.c_str());
            }
        }
    }
    // breadth-first count of events in the 2-strand family, target n = 0 (2-unlink)
    std::printf("   2-strand family closures of sigma1^n, moves n -> n - sign(n) (smoothing) and n -> n - 2 sign(n) (crossing change); target n = 0\n");
    auto sg = [](int n) { return n > 0 ? 1 : -1; };
    int Nev[12] = {0}; bool consistent = true;
    for (int n0 = 0; n0 <= 9; ++n0) {
        std::map<int, int> dist; dist[n0] = 0; std::vector<int> q = {n0};
        for (size_t h = 0; h < q.size(); ++h) { int n = q[h]; if (n == 0) continue; for (int step : {1, 2}) { int m = n - step * sg(n); if (!dist.count(m)) { dist[m] = dist[n] + 1; q.push_back(m); } } }
        Nev[n0] = dist.count(0) ? dist[0] : -1;
    }
    // consistency of the moves with the actual braid words
    for (int n = 1; n <= 6; ++n) { std::vector<int> w = sigmaPow(n); std::vector<int> ws = w; ws.erase(ws.begin()); std::vector<int> wc = w; wc[0] = -wc[0];
        consistent = consistent && (alexander(2, ws) == alexander(2, sigmaPow(n - 1))) && (alexander(2, wc) == alexander(2, sigmaPow(n - 2))) && topology(2, ws).comps == topology(2, sigmaPow(n - 1)).comps && topology(2, wc).comps == topology(2, sigmaPow(n - 2)).comps; }
    std::printf("      N_ev(n -> 0): "); for (int n0 = 0; n0 <= 9; ++n0) std::printf("n=%d: %d  ", n0, Nev[n0]); std::printf("\n");
    std::printf("      move set consistent with Delta and component counts of the actual words (n = 1..6): %s\n", consistent ? "yes" : "NO");
    std::printf("      W=2 -> 2 x W=1 (n = 1): N_ev = %d ; trefoil (n = 3): N_ev = %d ; T(2,5) (n = 5): N_ev = %d\n", Nev[1], Nev[3], Nev[5]);
    std::printf("      R3 (H3 absolute protection rejected if N_ev(trefoil) finite): %s\n", Nev[3] >= 0 ? "MET (rejected)" : "not met");
    std::printf("\n[T4] Approach A: Delta invariant under isotopy moves (V3); Approach B: linking numbers exist only for the products listed in T3 (trefoil: 1 component, none defined); Approach C: needs the energy of the reconnection event -> DEFERRED (FLM10 barrier, EMC03 interaction sign)\n");
    return 0;
}
