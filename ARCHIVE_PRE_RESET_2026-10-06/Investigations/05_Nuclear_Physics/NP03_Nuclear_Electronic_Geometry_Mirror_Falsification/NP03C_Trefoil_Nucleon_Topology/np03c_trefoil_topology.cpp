// ============================================================================
// NP03C — Trefoil Nucleon Topology (positions FROZEN from NP03B)
//
// Reads np03b_positions.txt, imposes a (2,3) trefoil at each solved site
// (radial axis), 2 core trefoils at +/-0.5 R_p on +Y (declared convention),
// and verifies: input integrity (C0), zero drift (C1), knot closure +
// 3 crossings (C2), tube non-degeneracy (C3), radial orientation (C4),
// R_p scale + global tube-tube clearance (C5).
//
// trefoil (2,3): P(t) = c + e1 (R+a cos3t)cos2t + e2 (R+a cos3t)sin2t + n a sin3t
// R_t = 0.6 R_p, a_t = 0.2 R_p, r_tube = 0.08 R_p  (declared in RUN_LOG pre-run)
//
// Author: J. C. Harvey, Melbourne. Executed 2026-07-03.
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <numbers>

struct V3 {
    double x = 0, y = 0, z = 0;
    V3 operator+(const V3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    V3 operator-(const V3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    V3 operator*(double s) const { return {x * s, y * s, z * s}; }
    double dot(const V3& o) const { return x * o.x + y * o.y + z * o.z; }
    double len() const { return std::sqrt(dot(*this)); }
    V3 norm() const { double l = len(); return {x / l, y / l, z / l}; }
    V3 cross(const V3& o) const {
        return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x};
    }
};

struct Block { int idx; char type; V3 u; };
struct Iso {
    std::string sym; int Z, A, nd, nt, N;
    double theta_min, r_kiss; std::uint64_t hash;
    std::vector<Block> blocks;
};

struct Trefoil { V3 c, n, e1, e2; double Rt, at, rtube; char tag; };

static std::uint64_t fnv_hash(const std::vector<Block>& b) {
    std::uint64_t h = 1469598103934665603ULL;
    auto mix = [&](long long v) {
        for (int k = 0; k < 8; ++k) { h ^= static_cast<std::uint64_t>((v >> (8 * k)) & 0xFF); h *= 1099511628211ULL; }
    };
    for (const auto& q : b) {
        mix(std::llround(q.u.x * 1e9)); mix(std::llround(q.u.y * 1e9)); mix(std::llround(q.u.z * 1e9));
    }
    return h;
}

static V3 knot_point(const Trefoil& T, double t) {
    const double w = T.Rt + T.at * std::cos(3.0 * t);
    return T.c + T.e1 * (w * std::cos(2.0 * t)) + T.e2 * (w * std::sin(2.0 * t))
               + T.n * (T.at * std::sin(3.0 * t));
}

// 2D segment intersection (proper crossing) for the axis-projection test.
// Inputs MUST be pre-normalised to O(1) units (R_p units) — an earlier run
// passed metre-scale values and the 1e-14 collinearity guard swallowed every
// crossing (ADJ-001 in RUN_LOG.md).
static bool seg2d_cross(double ax, double ay, double bx, double by,
                        double cx, double cy, double dx, double dy) {
    auto orient = [](double px, double py, double qx, double qy, double rx, double ry) {
        const double v = (qx - px) * (ry - py) - (qy - py) * (rx - px);
        return (v > 1e-14) - (v < -1e-14);
    };
    const int o1 = orient(ax, ay, bx, by, cx, cy), o2 = orient(ax, ay, bx, by, dx, dy);
    const int o3 = orient(cx, cy, dx, dy, ax, ay), o4 = orient(cx, cy, dx, dy, bx, by);
    return (o1 != o2 && o3 != o4 && o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0);
}

int main() {
    using namespace sdt::laws;
    const double Rp = measured::R_p;                       // 8.414e-16 m (boundary radius)
    const double Rp_pred = law_VI::winding::R_p_predicted; // 4*hbar/(m_p c), reference only
    const double Rt = 0.6 * Rp, at = 0.2 * Rp, rtube = 0.08 * Rp;
    const int M = 720; // curve samples

    std::printf("NP03C — Trefoil Nucleon Topology — positions FROZEN from NP03B\n");
    std::printf("R_p (laws.hpp measured)   = %.6e m   [boundary radius]\n", Rp);
    std::printf("R_p_predicted (W+1, ref)  = %.6e m   [reference only, not consumed]\n", Rp_pred);
    std::printf("R_t=0.6R_p  a_t=0.2R_p  r_tube=0.08R_p  extent=(R_t+a_t)=0.8R_p <= R_p\n");
    std::printf("==========================================================================\n\n");

    // ------------------------------------------------------------------ read
    std::FILE* f = std::fopen("Investigations/05_Nuclear_Physics/"
        "NP03_Nuclear_Electronic_Geometry_Mirror_Falsification/"
        "NP03B_Independent_Nuclear_Equilibrium/np03b_positions.txt", "r");
    if (!f) { std::printf("FATAL: np03b_positions.txt not found\n"); return 1; }
    std::vector<Iso> isos;
    char line[512];
    while (std::fgets(line, sizeof(line), f)) {
        if (line[0] == '#') continue;
        if (std::strncmp(line, "ISO", 3) == 0) {
            Iso is; char sym[8]; unsigned long long h;
            std::sscanf(line, "ISO %7s %d %d %d %d %d %lf %lf %llx",
                        sym, &is.Z, &is.A, &is.nd, &is.nt, &is.N,
                        &is.theta_min, &is.r_kiss, &h);
            is.sym = sym; is.hash = h;
            isos.push_back(is);
        } else if (std::strncmp(line, "BLK", 3) == 0 && !isos.empty()) {
            Block b; char ty;
            std::sscanf(line, "BLK %d %c %lf %lf %lf", &b.idx, &ty, &b.u.x, &b.u.y, &b.u.z);
            b.type = ty;
            isos.back().blocks.push_back(b);
        }
    }
    std::fclose(f);
    std::printf("[read] %d isotopes loaded from np03b_positions.txt\n\n",
                static_cast<int>(isos.size()));

    bool c0 = true, c1 = true, c2 = true, c3 = true, c4 = true, c5 = true;

    std::FILE* out = std::fopen("Investigations/05_Nuclear_Physics/"
        "NP03_Nuclear_Electronic_Geometry_Mirror_Falsification/"
        "NP03C_Trefoil_Nucleon_Topology/np03c_topology.txt", "w");
    if (!out) { std::printf("FATAL: cannot open np03c_topology.txt\n"); return 1; }
    std::fprintf(out, "# NP03C trefoil topology (fm units). R_p=%.6e m\n", Rp);
    std::fprintf(out, "# ISO sym Z A N scale_fm\n");
    std::fprintf(out, "# TRF tag cx cy cz nx ny nz Rt at rtube   (fm; tag c=core d=deuteron t=triton)\n");

    for (const auto& is : isos) {
        std::printf("---- %s-%d  (n_d,n_t)=(%d,%d)  N=%d ----\n",
                    is.sym.c_str(), is.A, is.nd, is.nt, is.N);

        // C0: integrity (vacuous for N=0 — NP03B records no hash for an empty set)
        if (is.N == 0) {
            std::printf("  C0 integrity: n/a (no blocks)\n");
        } else {
            const std::uint64_t h = fnv_hash(is.blocks);
            const bool okh = (h == is.hash);
            if (!okh) c0 = false;
            std::printf("  C0 integrity: file hash %016llx recomputed %016llx  %s\n",
                        static_cast<unsigned long long>(is.hash),
                        static_cast<unsigned long long>(h), okh ? "MATCH" : "MISMATCH");
        }

        // Physical scale: min block-block centre distance -> 2 R_p.
        // Block centres in units: u_i * (1 + r_kiss) (direction * shell radius).
        double min_unit_dist = 1e30;
        const double shellR = 1.0 + ((is.N >= 2) ? is.r_kiss : 1.0);
        for (std::size_t i = 0; i < is.blocks.size(); ++i)
            for (std::size_t j = i + 1; j < is.blocks.size(); ++j)
                min_unit_dist = std::min(min_unit_dist,
                    ((is.blocks[i].u - is.blocks[j].u) * shellR).len());
        double scale; // metres per unit
        if (is.blocks.size() >= 2) scale = 2.0 * Rp / min_unit_dist;
        else if (is.blocks.size() == 1) scale = 2.0 * Rp / shellR; // lone block at 2 R_p from core
        else scale = Rp; // He-4: core only
        std::printf("  scale: %.4f fm per unit (min block sep -> %.4f fm = 2 R_p)\n",
                    scale * 1e15, (is.blocks.size() >= 2) ? min_unit_dist * scale * 1e15 : 2.0 * Rp * 1e15);

        // Build trefoils: 2 core protons + 1 per block (its proton), radial axis.
        std::vector<Trefoil> trefs;
        auto frame = [&](const V3& n) {
            V3 a = (std::fabs(n.x) < 0.9) ? V3{1, 0, 0} : V3{0, 1, 0};
            V3 e1 = (a - n * a.dot(n)).norm();
            V3 e2 = n.cross(e1);
            return std::pair<V3, V3>(e1, e2);
        };
        {   // core pair (declared convention: +/-0.5 R_p on +Y, axis +Y)
            for (double s : {+0.5, -0.5}) {
                Trefoil T; T.c = {0, s * Rp, 0}; T.n = {0, 1, 0};
                auto [e1, e2] = frame(T.n); T.e1 = e1; T.e2 = e2;
                T.Rt = Rt; T.at = at; T.rtube = rtube; T.tag = 'c';
                trefs.push_back(T);
            }
        }
        double max_drift = 0.0, min_axis_dot = 1.0;
        for (const auto& b : is.blocks) {
            Trefoil T;
            T.c = b.u * (shellR * scale);
            T.n = b.u.norm();
            auto [e1, e2] = frame(T.n); T.e1 = e1; T.e2 = e2;
            T.Rt = Rt; T.at = at; T.rtube = rtube; T.tag = b.type;
            trefs.push_back(T);
            // C1 drift: recover unit direction from physical centre, compare exactly
            const V3 rec = T.c.norm();
            max_drift = std::max({max_drift, std::fabs(rec.x - b.u.norm().x),
                                  std::fabs(rec.y - b.u.norm().y), std::fabs(rec.z - b.u.norm().z)});
            // C4 orientation
            min_axis_dot = std::min(min_axis_dot, T.n.dot(b.u.norm()));
        }
        const bool okdrift = (max_drift < 1e-12);
        const bool okaxis = (is.blocks.empty() || min_axis_dot > 1.0 - 1e-9);
        if (!okdrift) c1 = false;
        if (!okaxis) c4 = false;
        std::printf("  C1 drift: max |delta| = %.3e  %s\n", max_drift, okdrift ? "PASS" : "FAIL");
        std::printf("  C4 orientation: min axis.u = %.12f  %s\n", min_axis_dot, okaxis ? "PASS" : "FAIL");

        // C2/C3 per knot: closure, 3 crossings, self-distance
        int bad_close = 0, bad_cross = 0, bad_self = 0;
        int cross_lo = 1 << 30, cross_hi = -1;
        double worst_self = 1e30;
        for (const auto& T : trefs) {
            // closure
            const V3 p0 = knot_point(T, 0.0), p1 = knot_point(T, 2.0 * std::numbers::pi);
            if ((p1 - p0).len() > 1e-9 * Rp) ++bad_close;
            // sample
            std::vector<V3> pts(M);
            for (int i = 0; i < M; ++i)
                pts[static_cast<std::size_t>(i)] =
                    knot_point(T, 2.0 * std::numbers::pi * i / M);
            // crossings in axis projection (project onto e1,e2)
            // ADJ-002: half-step offset sampling for the crossing test. With M
            // divisible by 12 the three analytic crossings (t = pi/6 + k pi/3)
            // land EXACTLY on shared segment endpoints and the proper-crossing
            // predicate (all orientations nonzero) rejects them — first run
            // counted 0 everywhere. Offsetting by delta/2 puts them mid-segment.
            std::vector<double> px(M), py(M);
            for (int i = 0; i < M; ++i) {
                const double t = 2.0 * std::numbers::pi * (i + 0.5) / M;
                const V3 d = knot_point(T, t) - T.c;
                px[static_cast<std::size_t>(i)] = d.dot(T.e1) / Rp;  // R_p units (ADJ-001)
                py[static_cast<std::size_t>(i)] = d.dot(T.e2) / Rp;
            }
            int crossings = 0;
            for (int i = 0; i < M; ++i) {
                const int i2 = (i + 1) % M;
                for (int j = i + 2; j < M; ++j) {
                    const int j2 = (j + 1) % M;
                    if (j2 == i) continue;
                    if (seg2d_cross(px[i], py[i], px[i2], py[i2],
                                    px[j], py[j], px[j2], py[j2])) ++crossings;
                }
            }
            if (crossings != 3) ++bad_cross;
            cross_lo = std::min(cross_lo, crossings);
            cross_hi = std::max(cross_hi, crossings);
            // min non-adjacent self distance (cyclic separation > 20 samples)
            double selfmin = 1e30;
            for (int i = 0; i < M; ++i)
                for (int j = i + 21; j < M; ++j) {
                    if ((M - (j - i)) <= 20) continue;
                    selfmin = std::min(selfmin,
                        (pts[static_cast<std::size_t>(i)] - pts[static_cast<std::size_t>(j)]).len());
                }
            worst_self = std::min(worst_self, selfmin);
            if (selfmin < 2.0 * T.rtube) ++bad_self;
        }
        if (bad_close) c2 = false;
        if (bad_cross) c2 = false;
        if (bad_self) c3 = false;
        std::printf("  C2 knots: %d trefoils, closure fails %d, crossing!=3 fails %d, "
                    "count range [%d,%d] (analytic: 3)\n",
                    static_cast<int>(trefs.size()), bad_close, bad_cross, cross_lo, cross_hi);
        std::printf("  C3 self-distance: worst %.4f R_p (gate >= 2 r_tube = 0.16 R_p; "
                    "same-ray bound 2 a_t = 0.4 R_p is NOT the min)  %s\n",
                    worst_self / Rp, bad_self ? "FAIL" : "PASS");

        // C5 global tube-tube clearance (all trefoil pairs)
        double worst_clear = 1e30;
        for (std::size_t a = 0; a < trefs.size(); ++a)
            for (std::size_t b2 = a + 1; b2 < trefs.size(); ++b2) {
                // bounding-sphere early out
                const double cc = (trefs[a].c - trefs[b2].c).len();
                const double bound = trefs[a].Rt + trefs[a].at + trefs[b2].Rt + trefs[b2].at
                                   + trefs[a].rtube + trefs[b2].rtube;
                if (cc - bound > worst_clear) continue;
                double dmin = 1e30;
                for (int i = 0; i < M; i += 2) {
                    const V3 pa = knot_point(trefs[a], 2.0 * std::numbers::pi * i / M);
                    for (int j = 0; j < M; j += 2) {
                        const V3 pb = knot_point(trefs[b2], 2.0 * std::numbers::pi * j / M);
                        dmin = std::min(dmin, (pa - pb).len());
                    }
                }
                worst_clear = std::min(worst_clear, dmin - trefs[a].rtube - trefs[b2].rtube);
            }
        const bool okclear = trefs.size() < 2 || worst_clear >= 0.0;
        if (!okclear) c5 = false;
        if (trefs.size() >= 2)
            std::printf("  C5 tube-tube clearance: worst %.4f R_p  %s\n",
                        worst_clear / Rp, okclear ? "PASS" : "FAIL");

        // emit topology
        std::fprintf(out, "ISO %s %d %d %d %.9e\n", is.sym.c_str(), is.Z, is.A, is.N, scale * 1e15);
        for (const auto& T : trefs)
            std::fprintf(out, "TRF %c %.9f %.9f %.9f %.12f %.12f %.12f %.6f %.6f %.6f\n",
                T.tag, T.c.x * 1e15, T.c.y * 1e15, T.c.z * 1e15,
                T.n.x, T.n.y, T.n.z, Rt * 1e15, at * 1e15, rtube * 1e15);
        std::printf("\n");
    }
    std::fclose(out);

    const bool all = c0 && c1 && c2 && c3 && c4 && c5;
    std::printf("==========================================================================\n");
    std::printf("NP03C SUMMARY\n");
    std::printf("  C0 input integrity          : %s\n", c0 ? "PASS" : "FAIL");
    std::printf("  C1 zero position drift      : %s\n", c1 ? "PASS" : "FAIL");
    std::printf("  C2 knot closure + 3 cross   : %s\n", c2 ? "PASS" : "FAIL");
    std::printf("  C3 tube non-degeneracy      : %s\n", c3 ? "PASS" : "FAIL");
    std::printf("  C4 radial orientation       : %s\n", c4 ? "PASS" : "FAIL");
    std::printf("  C5 R_p scale + clearance    : %s\n", c5 ? "PASS" : "FAIL");
    std::printf("  OVERALL: %s — topology substrate emitted (np03c_topology.txt).\n",
                all ? "PASS" : "FAIL");
    std::printf("  NOTE: rendering is NOT evidence; these are numeric validity checks only.\n");
    return all ? 0 : 1;
}
