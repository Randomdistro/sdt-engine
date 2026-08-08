// GOM26b — SDT deflection at Fomalont 2009 solar elongations
// Empirically: published Table 4 is (γ−1) residual AFTER GR correlator model.
// Absolute measured differentials are not recoverable from the paper alone.
// This instrument publishes COMPUTED SDT δ(b) at the stated elongations and
// records PENDING_DATA / UNADJUDICATED for absolute adjudication.
#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <cstring>
#include <numbers>
#include <vector>

using namespace sdt::laws;

namespace {

constexpr double kKoppa = 1476.664437; // GOM25b freeze
constexpr double kArcsecPerRad = 206264.806247;
constexpr double kMasPerRad = kArcsecPerRad * 1000.0;

[[nodiscard]] constexpr auto n_of_r(double r) -> double {
    const double z = kKoppa / r;
    const double omz = 1.0 - z;
    return 1.0 / (omz * omz);
}

[[nodiscard]] auto turning_radius(double b) -> double {
    double r = b - 2.0 * kKoppa;
    if (r <= kKoppa * 1.01) r = b * 0.999;
    for (int k = 0; k < 80; ++k) {
        const double n = n_of_r(r);
        const double f = n * r - b;
        const double omz = 1.0 - kKoppa / r;
        const double np = -2.0 * std::pow(omz, -3.0) * (kKoppa / (r * r));
        const double df = n + r * np;
        const double step = f / df;
        r -= step;
        if (r <= kKoppa) r = kKoppa * 1.0000001;
        if (std::abs(step) < 1e-15 * b) break;
    }
    return r;
}

[[nodiscard]] auto deflection_rad(double b, long N = 600000) -> double {
    const double r0 = turning_radius(b);
    const double n0 = n_of_r(r0);
    double acc = 0.0;
    for (long i = 0; i < N; ++i) {
        const double t0 = static_cast<double>(i) / N;
        const double t1 = static_cast<double>(i + 1) / N;
        const double t = 0.5 * (t0 + t1);
        const double u = 1.0 - t * t;
        if (u <= 0.0) continue;
        const double r = r0 / u;
        const double n = n_of_r(r);
        const double inside = n * n - n0 * n0 * u * u;
        if (inside <= 0.0) continue;
        acc += (n0 * 2.0 * t * (t1 - t0)) / std::sqrt(inside);
    }
    return 2.0 * acc - std::numbers::pi;
}

struct Elong {
    const char* source;
    const char* date;
    double sun_deg;
};

} // namespace

int main()
{
    std::puts("================================================================");
    std::puts("GOM26b — SDT δ at Fomalont+2009 elongations (Table 3 SR⊙)");
    std::puts("================================================================\n");

    // Pre-registered geometry: b = AU * sin(θ), θ = solar elongation
    const double AU_over_R = measured::AU / measured::R_Sun;

    // Subset with usable SR⊙ from Fomalont Table 3 (43 GHz sessions with data)
    const std::vector<Elong> rows = {
        {"3C279", "Oct01", 6.6},
        {"3C279", "Oct10a", 2.2},
        {"3C279", "Oct10b", 2.4},
        {"3C279", "Oct11", 3.2},
        {"3C279", "Oct18", 10.2},
        {"J1246", "Oct01", 5.5},
        {"J1246", "Oct05", 2.6},
        {"J1246", "Oct09", 3.7},
        {"J1246", "Oct10", 4.5},
        {"J1246", "Oct11", 5.4},
        {"J1246", "Oct18", 12.1},
        {"J1248", "Oct01", 5.3},
        {"J1248", "Oct09", 3.0},
        {"J1248", "Oct10", 3.9},
        {"J1248", "Oct11", 4.9},
        {"J1248", "Oct18", 11.8},
    };

    // J1304 SR⊙ is not a separate column; paper uses it as reference.
    // For differential predictions we pair each source with J1304 using
    // published same-day source SR⊙ and an estimated J1304 elongation from
    // Fig.1 geometry. Without digitised Fig.1, use only source self δ(b)
    // and pairwise differentials where BOTH elongations are in Table 3.
    // Conservative: publish per-source δ only; mark J1304 pairing PENDING_GEOMETRY.

    std::puts("COMPUTED — per-source absolute deflection at published SR⊙");
    std::puts("  source   date    SR⊙[deg]  b/R_Sun   δ[arcsec]  δ[mas]   4ϟ/b[mas]");
    for (const auto& e : rows) {
        const double th = e.sun_deg * std::numbers::pi / 180.0;
        const double b = measured::AU * std::sin(th);
        const double bR = b / measured::R_Sun;
        const double d = deflection_rad(b);
        const double d_as = d * kArcsecPerRad;
        const double d_mas = d_as * 1000.0;
        const double wf_mas = (4.0 * kKoppa / b) * kMasPerRad;
        std::printf("  %-6s  %-6s  %6.1f  %8.3f  %9.5f  %8.2f  %8.2f\n",
                    e.source, e.date, e.sun_deg, bR, d_as, d_mas, wf_mas);
    }

    // Example differential cited in paper text (Oct11 3C279 vs J1304 ~100 mas E/W scale)
    // Without J1304 elongation, compute δ(3.2°) alone as scale check — NOT a residual test.
    const double th_ex = 3.2 * std::numbers::pi / 180.0;
    const double b_ex = measured::AU * std::sin(th_ex);
    const double d_ex_mas = deflection_rad(b_ex) * kMasPerRad;
    std::printf("\n  Scale note: SDT |δ| at 3.2° = %.1f mas (absolute, not differential)\n",
                d_ex_mas);
    std::puts("  Paper cites ~100 mas differential GR bending 3C279–J1304 on Oct11.");
    std::puts("  Absolute differential requires J1304 elongation (Fig.1) — not tabulated.\n");

    std::puts("DATA ADMISSIBILITY");
    std::puts("  Fomalont Table 4 = residual after correlator already applied γ=1 deflection.");
    std::puts("  Label: MODEL-PROCESSED (PPN correlator prior).");
    std::puts("  Cannot use Table 4 as absolute δ(b) observable.");
    std::puts("  STATUS: PENDING_DATA for absolute b-scan adjudication");
    std::puts("  STATUS: UNADJUDICATED for confirmation via γ-fit agreement");
    std::puts("  (γ agreement with GR is not an SDT rejection or survival gate).\n");

    std::puts("NEXT FETCH TO UNBLOCK");
    std::puts("  1. Digitise Fig.1 solar track → J1304 elongation per session");
    std::puts("  2. Or obtain correlator-free absolute differential angles");
    std::puts("  3. Then residual SDT Δδ vs measured Δδ without γ prior");
    std::puts("================================================================");
    return 0;
}
