// NP10 reset, instrument 1 (2026-10-09). Pre-registration: NP10_RESET_ASSESSMENT_2026-10-09.md sections 3-5.
// H-W angular-window allocation: per-contact binding bounded by the deuteron's; ray-engagement instance on the rank4 channels.
// Constants from sdt::laws; measured bindings loaded only in the final comparison block.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <numbers>
#include <random>
#include <string_view>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
using V3 = std::array<double, 3>;
static const double PI = std::numbers::pi;

static double dot(const V3& a, const V3& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
static V3 unit(V3 a) { double n = std::sqrt(dot(a, a)); return {a[0] / n, a[1] / n, a[2] / n}; }
static std::mt19937_64 rng(20261009);                       // output sequence is specified by the standard
static double u01() { return (rng() >> 11) * (1.0 / 9007199254740992.0); }  // portable, not uniform_real_distribution
struct Rot { double m[3][3]; V3 apply(const V3& v) const { return {m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2], m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2], m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2]}; } };
static Rot random_rotation() {                              // uniform quaternion (Shoemake)
    double u1 = u01(), u2 = u01(), u3 = u01(), a = std::sqrt(1 - u1), b = std::sqrt(u1);
    double w = a * std::sin(2 * PI * u2), x = a * std::cos(2 * PI * u2), y = b * std::sin(2 * PI * u3), z = b * std::cos(2 * PI * u3);
    return {{{1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)}, {2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)}, {2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)}}};
}
static std::array<V3, 4> channels() { std::array<V3, 4> ch; for (int i = 0; i < 4; ++i) ch[i] = unit({lock_geometry::rank4::channels[i][0], lock_geometry::rank4::channels[i][1], lock_geometry::rank4::channels[i][2]}); return ch; }

// best number of neighbour directions engaged (some channel within thc) over random orientations; also the best worst-case angle to engage all
struct Best { int count; double worst_all_deg; };
static Best best_engagement(const std::vector<V3>& nb, double thc, long n_rot) {
    const auto ch = channels(); Best b{0, 180.0}; const double cth = std::cos(thc);
    for (long it = 0; it < n_rot; ++it) {
        Rot R = random_rotation(); std::array<V3, 4> rc; for (int i = 0; i < 4; ++i) rc[i] = R.apply(ch[i]);
        int cnt = 0; double worst = 0;
        for (const auto& d : nb) { double mx = -2; for (const auto& c : rc) mx = std::max(mx, dot(c, d)); if (mx >= cth) ++cnt; worst = std::max(worst, std::acos(std::min(1.0, mx)) * 180 / PI); }
        b.count = std::max(b.count, cnt); b.worst_all_deg = std::min(b.worst_all_deg, worst);
    }
    return b;
}
struct Cluster { const char* name; std::vector<V3> pos; };

int main() {
    std::printf("NP10 reset instrument 1 (2026-10-09)\n====================================\n\n");
    const double thc = std::asin(0.5);   // contact cone half-angle: sin = R/(2R)
    const long NROT = 3000000;
    int bad = 0;
    // ---- validations
    { auto ch = channels(); double worst = 0; for (int i = 0; i < 4; ++i) for (int j = i + 1; j < 4; ++j) worst = std::max(worst, std::fabs(dot(ch[i], ch[j]) + 1.0 / 3)); bool ok = worst < 1e-12;
      std::printf("[V1] channel cosines against -1/3: worst %.1e -> %s\n", worst, ok ? "met" : "NOT MET"); bad += !ok; }
    { double deg = thc * 180 / PI; bool ok = std::fabs(deg - 30) < 1e-12; std::printf("[V2] contact cone half-angle %.12f deg -> %s\n", deg, ok ? "met" : "NOT MET"); bad += !ok; }
    { Best b = best_engagement({{1, 0, 0}}, thc, 200000); bool ok = b.count == 1; std::printf("[V3] pair: engagements per nucleon %d (known 1) -> %s\n", b.count, ok ? "met" : "NOT MET"); bad += !ok; }
    { auto ch = channels(); Best b = best_engagement({ch[0], ch[1], ch[2]}, thc, NROT); bool ok = b.count == 3; std::printf("[V4] synthetic star along 3 channels: %d (known 3), best worst-angle %.3f deg -> %s\n\n", b.count, b.worst_all_deg, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET: no evaluation\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");

    // ---- P4 registration scale (motivation, not the test)
    { double R = law_III::R_p_lock, E = (PI / 4) * law_III::P_eff * std::pow(R, 4) / (2 * R) / M::MeV_to_J, cap = 2 * PI * (1 - std::cos(thc)) / (PI / 4);
      std::printf("[P4] far-field Law III between two R_p_lock boundaries, integrated to contact: %.4f MeV ; exact cap / small-angle at contact = %.4f\n\n", E, cap); }

    // ---- instance over the admissible clusters
    const double s3 = std::sqrt(3.0), s23 = std::sqrt(2.0 / 3.0);
    const Cluster cl[] = {
        {"pair (d)", {{0, 0, 0}, {2, 0, 0}}},
        {"rod-3", {{-2, 0, 0}, {0, 0, 0}, {2, 0, 0}}},
        {"triangle", {{0, 0, 0}, {2, 0, 0}, {1, s3, 0}}},
        {"square ring", {{0, 0, 0}, {2, 0, 0}, {2, 2, 0}, {0, 2, 0}}},
        {"tetrahedron", {{0, 0, 0}, {2, 0, 0}, {1, s3, 0}, {1, s3 / 3, 2 * s23}}},
    };
    std::printf("%-12s %3s %4s %10s %14s %22s %s\n", "cluster", "N", "E", "engaged", "per contact", "worst-angle all (deg)", "bound (<= 2)");
    int instance_bad = 0;
    for (const auto& c : cl) {
        int N = (int)c.pos.size(), E = 0, eng = 0; double worst_all = 0;
        for (int i = 0; i < N; ++i) {
            std::vector<V3> nb;
            for (int j = 0; j < N; ++j) if (j != i) { V3 d = {c.pos[j][0] - c.pos[i][0], c.pos[j][1] - c.pos[i][1], c.pos[j][2] - c.pos[i][2]}; if (std::fabs(std::sqrt(dot(d, d)) - 2) < 1e-9) { nb.push_back(unit(d)); if (j > i) ++E; } }
            Best b = best_engagement(nb, thc, NROT); eng += b.count; worst_all = std::max(worst_all, b.worst_all_deg);
        }
        double pc = (double)eng / E; bool ok = pc <= 2 + 1e-12; instance_bad += !ok;
        std::printf("%-12s %3d %4d %10d %14.4f %22.3f %s\n", c.name, N, E, eng, pc, worst_all, ok ? "satisfied" : "VIOLATED (instrument fault)");
    }
    std::printf("\nR2 (instance satisfies the bound): %s\n\n", instance_bad ? "NOT MET -> G0" : "met");

    // ---- comparison (measured values enter here only) [MEASURED-INPUT, AME2020 via DATA_REQUIREMENTS.md]
    const double Bd = 2.224, Bt = 8.482, Bh = 7.718, Ba = 28.296;
    struct G { const char* nuc; const char* graph; double B; int E; };
    const G gs[] = {{"H-3", "rod", Bt, 2}, {"H-3", "triangle", Bt, 3}, {"He-3", "rod", Bh, 2}, {"He-3", "triangle", Bh, 3}, {"He-4", "ring", Ba, 4}, {"He-4", "tetrahedron", Ba, 6}};
    bool t_all_above = true, a_all_above = true;
    std::printf("r = (B/E)/B_d   (H-W requires r <= 1)\n");
    for (const auto& g : gs) { double r = (g.B / g.E) / Bd; std::printf("  %-5s %-12s E = %d : B/E = %.4f MeV, r = %.4f\n", g.nuc, g.graph, g.E, g.B / g.E, r);
        if ((std::string_view(g.nuc) == "H-3") && r <= 1) t_all_above = false; if ((std::string_view(g.nuc) == "He-4") && r <= 1) a_all_above = false; }
    std::printf("R1: triton r > 1 under every admissible graph: %s ; alpha r > 1 under every admissible graph: %s -> H-W %s\n\n", t_all_above ? "yes" : "no", a_all_above ? "yes" : "no", (t_all_above && a_all_above) ? "EXCLUDED (G1)" : "open (G2)");

    // ---- R3: contact diameter against the He-4 boundary radius
    { double pred = 2 * law_III::R_p_lock, rel = pred / M::R_He - 1; std::printf("R3: 2 R_p_lock = %.5f fm ; R_He (measured) = %.5f fm ; relative %+.3f%% -> %s\n", pred * 1e15, M::R_He * 1e15, rel * 100, std::fabs(rel) <= 0.01 ? "within 1% (G4)" : "outside 1%"); }
    return 0;
}
