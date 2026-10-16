// =====================================================================
//  GD08 : Milky Way arm topology — measured arm positions and thicknesses
//  ---------------------------------------------------------------------
//  Observed-structure layer. Inputs: Reid et al. 2019 (ApJ 885, 131),
//  Table 2 and Sec. 3, R0 = 8.15 kpc. No SDT mechanism, no fitted value.
//  Pre-registration: PROMPT.md (same folder).
//
//  Centre line  : ln(R/Rk) = -(beta - beta_k) tan(psi)      [Reid Eq. 1]
//  In-plane 1s  : w(R) = w_k + 0.042 (R - Rk)  kpc          [Reid Sec. 3]
//  Vertical rms : sz(R) = 0.020 + 0.036 (R - 7.0) kpc, R>7; 0.020 inside
//  Plan coords  : x = R sin(beta), y = R cos(beta); centre (0,0), Sun (0,R0)
//
//  Context bodies (PROMPT.md Addendum 1): Bland-Hawthorn & Gerhard 2016 (ARA&A 54, 529)
//    thin disc  R_t 2.6 kpc, z_t 0.30 kpc ; thick disc R_T 2.0 kpc, z_T 0.90 kpc
//    b/p bulge  27 deg, face-on 1:2.1 to ~2 kpc, edge-on c/a 0.26
//
//  Build (standalone):  cl /std:c++20 /EHsc /O2 gd08_mw_arm_topology.cpp
//  Run:                 gd08_mw_arm_topology.exe
//  Writes: mw_arms_data.js  (viewer data)   mw_arm_topology.obj  (1-sigma mesh)
//
//  Author: SDT Canonical Engine — J. C. Harvey, Melbourne
// =====================================================================

#include <cstdio>
#include <cmath>
#include <numbers>
#include <vector>
#include <string>
#include <algorithm>
#include <array>

namespace {

constexpr double PI   = std::numbers::pi;
constexpr double DEG  = PI / 180.0;
constexpr double R0   = 8.15;        // kpc, Reid 2019 adopted
constexpr double Z_SUN = 0.0055;     // kpc, Sun above the plane (Reid 2019 Sec. 3.1)
constexpr double DWDR = 0.042;       // kpc per kpc, Reid 2019 Sec. 3
constexpr double EXT_DEG = 90.0;     // near extension beyond the measured range (PROMPT.md)
constexpr double EXT_FAR = 270.0;    // far-side continuation limit, tier 2 beyond EXT_DEG (Addendum 2)
constexpr double R_MIN = 3.0, R_MAX = 16.0;   // extension limits [kpc]
constexpr int    RING = 16;          // cross-section vertices
constexpr double STEP_DEG = 0.5;

struct Seg {
    const char* name;
    double Rk, bk, plt, pgt, wk, lo, hi;   // kpc, deg, deg, deg, kpc, deg, deg
    bool   extend;
    double tan_pub;                         // published Q4 tangency [deg], <0 if none
};

// Reid et al. 2019, Table 2 (OBSERVED).
const Seg SEG[] = {
    {"3-kpc(N)", 3.52, 15, -4.2, -4.2, 0.18,  15,  18, false, 337.0},
    {"Norma",    4.46, 18, -1.0, 19.5, 0.14,   5,  54, true,  327.5},
    {"Sct-Cen",  4.91, 23, 14.1, 12.1, 0.23,   0, 104, true,  306.1},
    {"Sgr-Car",  6.04, 24, 17.1,  1.0, 0.27,   2,  97, true,  285.6},
    {"Local",    8.26,  9, 11.4, 11.4, 0.31,  -8,  34, false, -1.0},
    {"Perseus",  8.87, 40, 10.3,  8.7, 0.35, -23, 115, true,  -1.0},
    {"Outer",   12.24, 18,  3.0,  9.4, 0.65, -16,  71, true,  -1.0},
};
constexpr int NSEG = sizeof(SEG) / sizeof(SEG[0]);

// Bar, reference only: Wegg, Gerhard & Portail 2015 (abstract).
constexpr double BAR_HALF_KPC = 5.0, BAR_ANG_LO = 28.0, BAR_ANG_HI = 33.0, BAR_THIN_Z = 0.18;

// ---- context bodies: BH&G 2016 (OBSERVED ratios; ellipsoid axes COMPUTED from them) ----
constexpr double THIN_RD = 2.6, THIN_ZD = 0.30, THICK_RD = 2.0, THICK_ZD = 0.90;
constexpr double DISC_RMAX = 15.0;                 // drawing limit, not a measured edge
constexpr double BULGE_A = 2.0, BULGE_FACEON = 2.1, BULGE_CA = 0.26, BULGE_ANG = 27.0;
constexpr double BULGE_BA_LO = 0.45, BULGE_BA_HI = 0.55;   // quoted 0.5 +- 0.05
constexpr double BULGE_B = BULGE_A / BULGE_FACEON, BULGE_C = BULGE_CA * BULGE_A;

struct Mesh { std::vector<std::array<double, 3>> v; std::vector<std::array<int, 3>> f; };

// Ellipsoid with major axis at ang_deg from the Sun-centre (+y) line toward +x.
Mesh ellipsoid(double a, double b, double c, double ang_deg, int nu = 96, int nv = 48) {
    Mesh m; double sa = std::sin(ang_deg * DEG), ca = std::cos(ang_deg * DEG);
    auto W = [&](double X, double Y, double Z) { return std::array<double, 3>{X * sa + Y * ca, X * ca - Y * sa, Z}; };
    m.v.push_back(W(0, 0, c)); m.v.push_back(W(0, 0, -c));              // poles: 0 top, 1 bottom
    for (int j = 1; j < nv; ++j) for (int i = 0; i < nu; ++i) {
        double th = PI * j / nv, ph = 2 * PI * i / nu;
        m.v.push_back(W(a * std::sin(th) * std::cos(ph), b * std::sin(th) * std::sin(ph), c * std::cos(th)));
    }
    auto id = [&](int j, int i) { return 2 + (j - 1) * nu + (i % nu); };
    for (int i = 0; i < nu; ++i) m.f.push_back({0, id(1, i), id(1, i + 1)});
    for (int j = 1; j + 1 < nv; ++j) for (int i = 0; i < nu; ++i) {
        m.f.push_back({id(j, i), id(j + 1, i), id(j + 1, i + 1)});
        m.f.push_back({id(j, i), id(j + 1, i + 1), id(j, i + 1)});
    }
    for (int i = 0; i < nu; ++i) m.f.push_back({1, id(nv - 1, i + 1), id(nv - 1, i)});
    return m;
}
// Closed cylinder slab, |z| <= h, radius R.
Mesh slab(double R, double h, int n = 180) {
    Mesh m; m.v.push_back({0, 0, h}); m.v.push_back({0, 0, -h});
    for (int i = 0; i < n; ++i) { double ph = 2 * PI * i / n; m.v.push_back({R * std::cos(ph), R * std::sin(ph), h}); }
    for (int i = 0; i < n; ++i) { double ph = 2 * PI * i / n; m.v.push_back({R * std::cos(ph), R * std::sin(ph), -h}); }
    for (int i = 0; i < n; ++i) {
        int a = 2 + i, b = 2 + (i + 1) % n, c = 2 + n + i, d = 2 + n + (i + 1) % n;
        m.f.push_back({0, a, b}); m.f.push_back({1, d, c});
        m.f.push_back({a, c, b}); m.f.push_back({b, c, d});
    }
    return m;
}
// Enclosed volume by the divergence theorem (orientation-independent: absolute value).
double mesh_volume(const Mesh& m) {
    double V = 0;
    for (auto& t : m.f) {
        auto &p = m.v[t[0]], &q = m.v[t[1]], &r = m.v[t[2]];
        V += p[0] * (q[1] * r[2] - q[2] * r[1]) - p[1] * (q[0] * r[2] - q[2] * r[0]) + p[2] * (q[0] * r[1] - q[1] * r[0]);
    }
    return std::fabs(V) / 6.0;
}

double ridge_R(const Seg& s, double b_deg, double Rk, double psi_lt, double psi_gt) {
    double psi = (b_deg <= s.bk ? psi_lt : psi_gt) * DEG;
    return Rk * std::exp(-(b_deg - s.bk) * DEG * std::tan(psi));
}
double ridge_R(const Seg& s, double b_deg) { return ridge_R(s, b_deg, s.Rk, s.plt, s.pgt); }

double sigma_in(const Seg& s, double R) { return s.wk + DWDR * (R - s.Rk); }
double sigma_z(double R) { return R > 7.0 ? 0.020 + 0.036 * (R - 7.0) : 0.020; }

// tier: 1 = measured azimuth range, 0 = extended (<= EXT_DEG beyond), 2 = continued (EXT_DEG..EXT_FAR beyond)
struct Pt { double x, y, sin, sz, R, beta; int measured; };

std::vector<Pt> sample(const Seg& s) {
    std::vector<Pt> out;
    auto push = [&](double b, int m) {
        double R = ridge_R(s, b);
        out.push_back({R * std::sin(b * DEG), R * std::cos(b * DEG), sigma_in(s, R), sigma_z(R), R, b, m});
    };
    std::vector<std::pair<double, int>> head, tail;
    if (s.extend) {
        for (double e = STEP_DEG; e <= EXT_FAR + 1e-9; e += STEP_DEG) {
            double R = ridge_R(s, s.lo - e);
            if (R < R_MIN || R > R_MAX) break;
            head.push_back({s.lo - e, e <= EXT_DEG + 1e-9 ? 0 : 2});
        }
        for (double e = STEP_DEG; e <= EXT_FAR + 1e-9; e += STEP_DEG) {
            double R = ridge_R(s, s.hi + e);
            if (R < R_MIN || R > R_MAX) break;
            tail.push_back({s.hi + e, e <= EXT_DEG + 1e-9 ? 0 : 2});
        }
    }
    for (auto it = head.rbegin(); it != head.rend(); ++it) push(it->first, it->second);
    for (double b = s.lo; b <= s.hi + 1e-9; b += STEP_DEG) push(b, 1);
    for (auto& t : tail) push(t.first, t.second);
    return out;
}

// Longitude (deg, signed) at which the Sun sees plan point (x,y).
double lon_deg(double x, double y) { return std::atan2(x, R0 - y) / DEG; }

// Q4 tangency: minimum of l(beta) over beta in [-120,0]; returns 360+l, or NaN if the
// minimum sits on the scan boundary (no interior extremum).
double q4_tangency(const Seg& s, double Rk, double plt, double pgt) {
    double best = 1e9, bb = 0;
    for (double b = -120.0; b <= 0.0; b += 0.001) {
        double R = ridge_R(s, b, Rk, plt, pgt);
        double l = lon_deg(R * std::sin(b * DEG), R * std::cos(b * DEG));
        if (l < best) { best = l; bb = b; }
    }
    if (bb <= -119.99 || bb >= -0.01) return std::nan("");
    return 360.0 + best;
}

int g_fail = 0;
void check(const char* id, const char* what, bool ok, double val) {
    std::printf("  [%s] %s : %s  (%.3e)\n", ok ? "PASS" : "FAIL", id, what, val);
    if (!ok) ++g_fail;
}

} // namespace

int main() {
    std::printf("=================================================================\n");
    std::printf(" GD08 MILKY WAY ARM TOPOLOGY   (Reid+2019 Table 2, R0=%.2f kpc)\n", R0);
    std::printf(" OBSERVED arm parameters ; COMPUTED mesh ; 0 fitted parameters\n");
    std::printf("=================================================================\n\n");

    // ---------------- instrument validation (PROMPT.md V1-V4) ----------------
    std::printf("== INSTRUMENT VALIDATION (known answers) ==\n");
    {
        Seg c = SEG[0];
        double maxdev = 0;
        for (double b = -200; b <= 200; b += 1.0) maxdev = std::max(maxdev, std::fabs(ridge_R(c, b, 3.52, 0.0, 0.0) - 3.52));
        check("V1", "psi=0 gives circle R=Rk", maxdev < 1e-12, maxdev);
    }
    {
        double md = 0;
        for (int i = 0; i < NSEG; ++i) md = std::max(md, std::fabs(ridge_R(SEG[i], SEG[i].bk) - SEG[i].Rk));
        check("V2", "every segment passes through (Rk, beta_k)", md < 1e-12, md);
    }
    {
        double circ = q4_tangency(SEG[0], 3.52, 0.0, 0.0);
        double ref  = 360.0 - std::asin(3.52 / R0) / DEG;
        check("V3", "circle tangency = 360 - asin(R/R0)", std::fabs(circ - ref) < 0.01, circ - ref);
    }
    {
        double md = 0;
        for (int i = 0; i < NSEG; ++i) {
            double e = 1e-9;
            md = std::max(md, std::fabs(ridge_R(SEG[i], SEG[i].bk - e) - ridge_R(SEG[i], SEG[i].bk + e)));
        }
        check("V4", "ridge continuous at the kink", md < 1e-8, md);
    }
    {
        Mesh e = ellipsoid(BULGE_A, BULGE_B, BULGE_C, BULGE_ANG);
        double an = 4.0 / 3.0 * PI * BULGE_A * BULGE_B * BULGE_C, rel = mesh_volume(e) / an - 1.0;
        check("V5", "ellipsoid mesh volume = 4/3 pi a b c (1%)", std::fabs(rel) < 0.01, rel);
        double ba = 1.0 / BULGE_FACEON;
        check("V6", "face-on axis ratio 1/2.1 inside quoted 0.5 +- 0.05", ba >= BULGE_BA_LO && ba <= BULGE_BA_HI, ba);
        Mesh sl = slab(DISC_RMAX, THIN_ZD);
        double rel2 = mesh_volume(sl) / (PI * DISC_RMAX * DISC_RMAX * 2 * THIN_ZD) - 1.0;
        check("V7", "slab mesh volume = pi R^2 h (1%)", std::fabs(rel2) < 0.01, rel2);
    }
    {
        // V8: samples are contiguous in azimuth (no gap at tier boundaries) and consecutive
        // positions are no further apart than the local arc step allows.
        // V9: every continued sample has R in [R_MIN, R_MAX] and positive in-plane sigma.
        double worst_gap = 0, worst_step = 0, minsig = 1e9, rlo = 1e9, rhi = 0; int ncont = 0;
        for (int i = 0; i < NSEG; ++i) {
            auto pts = sample(SEG[i]);
            for (size_t k = 1; k < pts.size(); ++k) {
                worst_gap = std::max(worst_gap, std::fabs(pts[k].beta - pts[k - 1].beta - STEP_DEG));
                double step = std::hypot(pts[k].x - pts[k - 1].x, pts[k].y - pts[k - 1].y);
                double bound = 1.3 * std::max(pts[k].R, pts[k - 1].R) * STEP_DEG * DEG / std::cos(25.0 * DEG);
                worst_step = std::max(worst_step, step / bound);
            }
            for (auto& q : pts) if (q.measured == 2) {
                ++ncont; minsig = std::min(minsig, q.sin); rlo = std::min(rlo, q.R); rhi = std::max(rhi, q.R);
            }
        }
        check("V8", "contiguous azimuth samples; step within the arc bound", worst_gap < 1e-9 && worst_step < 1.0, worst_step);
        check("V9", "continued samples: R in [3,16] kpc and sigma_in > 0", rlo >= R_MIN && rhi <= R_MAX && minsig > 0, minsig);
        std::printf("      (%d continued samples; R %.2f .. %.2f kpc)\n", ncont, rlo, rhi);
    }
    std::printf("  validation failures: %d\n\n", g_fail);
    if (g_fail) { std::printf("validation failed — model not used.\n"); return 1; }

    // ---------------- single-pass comparison: Q4 tangencies ----------------
    std::printf("== Q4 TANGENCY LONGITUDES: model vs Reid Table 2 (criterion |d| <= 3 deg) ==\n");
    std::printf("%-10s %9s %9s %8s\n", "arm", "model", "Table2", "diff");
    int tan_out = 0;
    for (int i = 0; i < NSEG; ++i) {
        if (SEG[i].tan_pub < 0) continue;
        double m = q4_tangency(SEG[i], SEG[i].Rk, SEG[i].plt, SEG[i].pgt);
        double d = m - SEG[i].tan_pub;
        bool in = std::isfinite(m) && std::fabs(d) <= 3.0;
        if (!in) ++tan_out;
        std::printf("%-10s %9.2f %9.1f %+8.2f   %s\n", SEG[i].name, m, SEG[i].tan_pub, d,
                    in ? "consistent" : "inconsistent");
    }
    std::printf("rejection criterion met for %d of 4 arms\n\n", tan_out);

    // ---------------- width law consistency (information) ----------------
    std::printf("== WIDTH LAW: tabulated w(Rk) vs global line 0.336 + 0.036 (R - 8.15) ==\n");
    std::printf("%-10s %6s %8s %8s %8s\n", "arm", "Rk", "w_tab", "w_line", "resid");
    for (int i = 0; i < NSEG; ++i) {
        double wl = 0.336 + 0.036 * (SEG[i].Rk - 8.15);
        std::printf("%-10s %6.2f %8.3f %8.3f %+8.3f\n", SEG[i].name, SEG[i].Rk, SEG[i].wk, wl, SEG[i].wk - wl);
    }

    // ---------------- geometry summary and mesh ----------------
    std::printf("\n== ARM GEOMETRY (1 sigma) ==\n");
    std::printf("%-10s %5s %7s %7s %7s %7s %9s %9s %9s %9s\n", "arm", "pts", "len_m", "len_x", "len_f", "Rmin", "Rmax",
                "sin@Rk", "sz@Rk", "sin_min");
    FILE* js = std::fopen("mw_arms_data.js", "w");
    FILE* ob = std::fopen("mw_arm_topology.obj", "w");
    if (!js || !ob) { std::printf("cannot open outputs\n"); return 1; }
    std::fprintf(js, "// Generated by gd08_mw_arm_topology.cpp. Units: kpc. Reid+2019 Table 2, R0=%.2f.\n", R0);
    std::fprintf(js, "window.MW_TOPOLOGY={R0:%.2f,zSun:%.4f,bar:{half:%.1f,angLo:%.1f,angHi:%.1f,thinZ:%.2f},arms:[\n",
                 R0, Z_SUN, BAR_HALF_KPC, BAR_ANG_LO, BAR_ANG_HI, BAR_THIN_Z);
    std::fprintf(ob, "# GD08 Milky Way arm topology — 1-sigma arm surfaces, true vertical scale\n");
    std::fprintf(ob, "# Units kpc. x,y plan (centre 0,0; Sun 0,%.2f; rotation clockwise from +z), z vertical.\n", R0);
    std::fprintf(ob, "# Source: Reid et al. 2019, Table 2 (arms, extension beyond the measured range included);\n# Bland-Hawthorn & Gerhard 2016 (bulge ellipsoid, +-1 scale-height disc slabs to R=15 kpc, a drawing limit).\n");

    long vbase = 0;
    double sin_floor = 1e9;
    for (int i = 0; i < NSEG; ++i) {
        const Seg& s = SEG[i];
        auto pts = sample(s);
        double lm = 0, lx = 0, lf = 0, rmin = 1e9, rmax = 0, smin = 1e9;
        for (size_t k = 0; k < pts.size(); ++k) {
            rmin = std::min(rmin, pts[k].R); rmax = std::max(rmax, pts[k].R); smin = std::min(smin, pts[k].sin);
            if (k) {
                double d = std::hypot(pts[k].x - pts[k - 1].x, pts[k].y - pts[k - 1].y);
                if (pts[k].measured == 1 && pts[k - 1].measured == 1) lm += d;
                else if (pts[k].measured == 2 || pts[k - 1].measured == 2) lf += d;
                else lx += d;
            }
        }
        sin_floor = std::min(sin_floor, smin);
        std::printf("%-10s %5zu %7.2f %7.2f %7.2f %7.2f %9.2f %9.3f %9.3f %9.3f\n", s.name, pts.size(), lm, lx, lf, rmin, rmax,
                    sigma_in(s, s.Rk), sigma_z(s.Rk), smin);

        std::fprintf(js, "{name:\"%s\",lo:%.1f,hi:%.1f,extend:%s,pts:[", s.name, s.lo, s.hi, s.extend ? "true" : "false");
        for (size_t k = 0; k < pts.size(); ++k)
            std::fprintf(js, "%s[%.4f,%.4f,%.4f,%.4f,%d]", k ? "," : "", pts[k].x, pts[k].y, pts[k].sin, pts[k].sz,
                         pts[k].measured);
        std::fprintf(js, "]}%s\n", i + 1 < NSEG ? "," : "");

        // OBJ tube, elliptical section: in-plane semi-axis = 1 sigma_in, vertical = 1 sigma_z.
        std::fprintf(ob, "o %s\n", s.name);
        size_t n = pts.size();
        for (size_t k = 0; k < n; ++k) {
            size_t a = k ? k - 1 : k, b = k + 1 < n ? k + 1 : k;
            double tx = pts[b].x - pts[a].x, ty = pts[b].y - pts[a].y, tl = std::hypot(tx, ty);
            double nx = -ty / tl, ny = tx / tl;
            for (int j = 0; j < RING; ++j) {
                double ph = 2 * PI * j / RING;
                std::fprintf(ob, "v %.5f %.5f %.5f\n", pts[k].x + pts[k].sin * std::cos(ph) * nx,
                             pts[k].y + pts[k].sin * std::cos(ph) * ny, pts[k].sz * std::sin(ph));
            }
        }
        for (size_t k = 0; k + 1 < n; ++k)
            for (int j = 0; j < RING; ++j) {
                long a = vbase + (long)k * RING + j + 1, b = vbase + (long)k * RING + (j + 1) % RING + 1;
                long c = a + RING, d = b + RING;
                std::fprintf(ob, "f %ld %ld %ld\nf %ld %ld %ld\n", a, b, c, b, d, c);
            }
        vbase += (long)n * RING;
    }
    std::fprintf(js, "],ctx:{thin:{Rd:%.2f,zd:%.2f},thick:{Rd:%.2f,zd:%.2f},rmax:%.1f,"
                     "bulge:{a:%.3f,b:%.3f,c:%.3f,ang:%.1f}}};\n",
                 THIN_RD, THIN_ZD, THICK_RD, THICK_ZD, DISC_RMAX, BULGE_A, BULGE_B, BULGE_C, BULGE_ANG);
    // context bodies into the OBJ (true scale)
    auto put = [&](const char* name, const Mesh& m) {
        std::fprintf(ob, "o %s\n", name);
        for (auto& p : m.v) std::fprintf(ob, "v %.5f %.5f %.5f\n", p[0], p[1], p[2]);
        for (auto& t : m.f) std::fprintf(ob, "f %ld %ld %ld\n", vbase + t[0] + 1, vbase + t[1] + 1, vbase + t[2] + 1);
        vbase += (long)m.v.size();
    };
    put("bulge_bp", ellipsoid(BULGE_A, BULGE_B, BULGE_C, BULGE_ANG));
    put("thin_disc_1h", slab(DISC_RMAX, THIN_ZD));
    put("thick_disc_1h", slab(DISC_RMAX, THICK_ZD));
    std::printf("\n== CONTEXT BODIES ==\n");
    std::printf("bulge ellipsoid a,b,c = %.3f, %.3f, %.3f kpc at %.0f deg ; V = %.3f kpc^3\n", BULGE_A, BULGE_B, BULGE_C, BULGE_ANG,
                4.0 / 3.0 * PI * BULGE_A * BULGE_B * BULGE_C);
    std::printf("thin disc  R_t %.1f kpc, z_t %.2f kpc ; thick disc R_T %.1f kpc, z_T %.2f kpc ; slabs drawn to R = %.0f kpc\n",
                THIN_RD, THIN_ZD, THICK_RD, THICK_ZD, DISC_RMAX);
    std::fclose(js); std::fclose(ob);

    std::printf("\nlen_m = measured-range ridge length [kpc]; len_x = extended (<=90 deg beyond); len_f = continued (90-270 deg beyond, unmeasured)\n");
    std::printf("minimum in-plane 1-sigma over all samples: %.3f kpc (%s)\n", sin_floor, sin_floor > 0 ? "positive" : "NON-POSITIVE");
    std::printf("vertical rms: 20 pc for R<=7 kpc ; %.0f pc at R=8.15 ; %.0f pc at R=12 ; %.0f pc at R=16\n",
                1000 * sigma_z(8.15), 1000 * sigma_z(12.0), 1000 * sigma_z(16.0));
    std::printf("\nwrote mw_arms_data.js, mw_arm_topology.obj\n");
    return sin_floor > 0 ? 0 : 1;
}
