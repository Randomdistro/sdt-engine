// Chapter 18 — proton topology and boundary: worked-example instrument.
// Pre-registration: Textbook/validation/ch18_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch18_proton_topology_and_boundary
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <array>
#include <cmath>
#include <cstdint>
#include <vector>

namespace {

constexpr double kPi = std::numbers::pi;
using V3 = std::array<double, 3>;

// Void ratio of a regular arrangement of touching unit spheres: all centres lie at one distance d
// from the origin and the nearest neighbours touch (edge 2). Returns d - 1 after asserting edge 2.
double void_ratio(const std::vector<V3>& pts, bool* ok_edge) {
    double edge = 1e300;
    for (std::size_t i = 0; i < pts.size(); ++i)
        for (std::size_t j = i + 1; j < pts.size(); ++j) {
            const double dx = pts[i][0] - pts[j][0], dy = pts[i][1] - pts[j][1], dz = pts[i][2] - pts[j][2];
            edge = std::fmin(edge, std::sqrt(dx * dx + dy * dy + dz * dz));
        }
    if (ok_edge) *ok_edge = std::fabs(edge - 2.0) < 1e-13;
    const double d = std::sqrt(pts[0][0] * pts[0][0] + pts[0][1] * pts[0][1] + pts[0][2] * pts[0][2]);
    return d - 1.0;
}

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    namespace LG = sdt::laws::lock_geometry;
    tb::validate_helpers();

    tb::heading("V1 void-radius routine on the simple-cubic cell");
    {
        std::vector<V3> cube;
        for (int a : {-1, 1})
            for (int b : {-1, 1})
                for (int c : {-1, 1}) cube.push_back({double(a), double(b), double(c)});
        bool ok = false;
        const double v = void_ratio(cube, &ok);
        tb::check("V1", "simple-cubic void ratio sqrt(3) - 1", v, std::sqrt(3.0) - 1.0, 1e-14);
        tb::check_true("V1", "nearest-neighbour distance is the sphere diameter", ok);
    }

    tb::heading("T1 void geometry from coordinates");
    {
        const double s = 1.0 / std::sqrt(2.0);
        std::vector<V3> tet{{s, s, s}, {s, -s, -s}, {-s, s, -s}, {-s, -s, s}};
        std::vector<V3> oct{{std::sqrt(2.0), 0, 0}, {-std::sqrt(2.0), 0, 0}, {0, std::sqrt(2.0), 0}, {0, -std::sqrt(2.0), 0}, {0, 0, std::sqrt(2.0)}, {0, 0, -std::sqrt(2.0)}};
        bool ok_t = false, ok_o = false;
        const double rt = void_ratio(tet, &ok_t), ro = void_ratio(oct, &ok_o);
        tb::check_true("T1", "tetrahedral and octahedral arrangements are touching (edge 2)", ok_t && ok_o);
        tb::check("T1", "tetrahedral void ratio equals the engine constant", rt, LG::tetrahedral_void_radius_ratio, 1e-14);
        tb::check("T1", "octahedral void ratio equals the engine constant", ro, LG::octahedral_void_radius_ratio, 1e-14);
        tb::check("T1", "tetrahedral price 4 rho^3 equals the engine's", 4.0 * rt * rt * rt, LG::tetrahedral_resistance_price, 1e-14);
        tb::check("T1", "octahedral price 6 rho^3 equals the engine's", 6.0 * ro * ro * ro, LG::octahedral_resistance_price, 1e-14);
        tb::check_true("T1", "lower price selects coordination 4", (4.0 * rt * rt * rt < 6.0 * ro * ro * ro) && LG::trefoil_lock_coordination == 4);
        tb::check_true("T1", "coordination equals W_proton + 1 (integers of different origin)", LG::trefoil_lock_coordination == sdt::laws::law_VI::winding::W_proton + 1);
        tb::note("void ratios: tetrahedral %.12f ; octahedral %.12f ; prices %.9f and %.9f (ratio %.4f)", rt, ro, 4 * rt * rt * rt, 6 * ro * ro * ro, (6 * ro * ro * ro) / (4 * rt * rt * rt));
    }

    tb::heading("T2 directional moments of the four tetrahedral channels");
    {
        const double i3 = 1.0 / std::sqrt(3.0);
        const V3 ch[4] = {{i3, i3, i3}, {i3, -i3, -i3}, {-i3, i3, -i3}, {-i3, -i3, i3}};
        auto moment = [&](const V3& n, int rank) {
            const double n2 = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
            double sum = 0.0;
            for (const auto& q : ch) {
                const double pr = q[0] * n[0] + q[1] * n[1] + q[2] * n[2];
                sum += std::pow(pr * pr, rank / 2);
            }
            return sum / (4.0 * std::pow(n2, rank / 2));
        };
        Rng g{777};
        double w2 = 0.0, w4 = 0.0;
        for (int i = 0; i < 20000; ++i) {
            V3 n{g.next() - 0.5, g.next() - 0.5, g.next() - 0.5};
            const double n2 = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
            const double x2 = n[0] * n[0], y2 = n[1] * n[1], z2 = n[2] * n[2];
            const double analytic = (1.0 + 4.0 * (x2 * y2 + x2 * z2 + y2 * z2) / (n2 * n2)) / 9.0;
            w2 = std::fmax(w2, std::fabs(moment(n, 2) - 1.0 / 3.0));
            w4 = std::fmax(w4, std::fabs(moment(n, 4) - analytic));
        }
        tb::check("T2", "M2 = 1/3 over 20000 directions, worst deviation", w2, 0.0, 1e-14, false);
        tb::check("T2", "M4 channel sum equals the analytic form, worst deviation", w4, 0.0, 1e-14, false);
        tb::check("T2", "M4 on an axis = 1/9", moment({1, 0, 0}, 4), 1.0 / 9.0, 1e-15);
        tb::check("T2", "M4 on (1,1,1) = 7/27", moment({1, 1, 1}, 4), 7.0 / 27.0, 1e-15);
        // sphere average of M4: Gauss-Legendre in mu (24 points), uniform in phi (64 points)
        const int NG = 24, NP = 64;
        double avg = 0.0;
        // Gauss-Legendre nodes by Newton iteration
        for (int i = 0; i < NG; ++i) {
            double x = std::cos(kPi * (i + 0.75) / (NG + 0.5)), dp = 1.0;
            for (int it = 0; it < 100; ++it) {
                double p0 = 1.0, p1 = x;
                for (int k = 2; k <= NG; ++k) {
                    const double p2 = ((2 * k - 1) * x * p1 - (k - 1) * p0) / k;
                    p0 = p1;
                    p1 = p2;
                }
                dp = NG * (x * p1 - p0) / (x * x - 1.0);
                const double dx = p1 / dp;
                x -= dx;
                if (std::fabs(dx) < 1e-16) break;
            }
            double p0 = 1.0, p1 = x;
            for (int k = 2; k <= NG; ++k) {
                const double p2 = ((2 * k - 1) * x * p1 - (k - 1) * p0) / k;
                p0 = p1;
                p1 = p2;
            }
            dp = NG * (x * p1 - p0) / (x * x - 1.0);
            const double w = 2.0 / ((1.0 - x * x) * dp * dp);
            const double st = std::sqrt(1.0 - x * x);
            for (int j = 0; j < NP; ++j) {
                const double ph = 2.0 * kPi * (j + 0.5) / NP;
                avg += w * moment({st * std::cos(ph), st * std::sin(ph), x}, 4) / (2.0 * NP);
            }
        }
        tb::check("T2", "sphere average of M4 = 1/5 (isotropic value)", avg, 0.2, 1e-13);
        tb::note("M4 range [1/9, 7/27] = [%.6f, %.6f] ; isotropic 1/5 ; (max-min)/(1/5) = %.4f", 1.0 / 9.0, 7.0 / 27.0, (7.0 / 27.0 - 1.0 / 9.0) / 0.2);
    }

    tb::heading("T3 lock length: prediction printed before the stored R_p is read");
    {
        const double R_lock = 4.0 * M::hbar / (M::m_p * M::c);
        std::printf("       PREDICTION  R_p,lock = 4 hbar/(m_p c) = %.12e m = %.9f fm\n", R_lock, R_lock * 1e15);
        tb::check("T3", "engine R_p_lock equals 4 hbar/(m_p c)", sdt::laws::law_III::R_p_lock, R_lock, 1e-15);
        tb::check("T3", "engine R_p_predicted equals R_p_lock", sdt::laws::law_VI::winding::R_p_predicted, R_lock, 1e-15);
        // ---- the stored R_p is read below this line ----
        const double Cg = M::R_p / R_lock;
        const double Weff = M::R_p * M::m_p * M::c / M::hbar - 1.0;
        tb::note("stored R_p = %.6e m ; C_g = R_p/R_p,lock = %.6f ; W_eff = %.6f", M::R_p, Cg, Weff);
        tb::check("T3", "C_g within 1% of 1", Cg, 1.0, 1e-2);
        tb::check_true("T3", "W_eff in (2.99, 3.01)", Weff > 2.99 && Weff < 3.01);
        const double off = std::fabs(Weff + 1.0 - 4.0);
        tb::note("offset of R_p m_p c/hbar from 4: %.5f ; chance of landing this close to the one pre-selected integer: %.3f%% ; to any integer 1..10: %.2f%%", off, 200.0 * off, 100.0 * 10.0 * 2.0 * off / 9.0);
    }

    tb::heading("T4 wake closure and its legacy comparison");
    {
        const double lam = M::R_p / 4.0;
        const double koppa_b = M::l_P * M::l_P / lam;
        tb::check("T4", "engine koppa_per_baryon = l_P^2/(R_p/4)", sdt::laws::bridge::koppa_per_baryon, koppa_b, 1e-14);
        tb::check("T4", "sqrt(koppa_b R_p/4) returns the stored l_P (inverse evaluation)", std::sqrt(koppa_b * lam), M::l_P, 1e-14);
        const double legacy = M::l_P * M::l_P * M::m_p * M::c / M::hbar;
        const double Cg = M::R_p / (4.0 * M::hbar / (M::m_p * M::c));
        tb::check("T4", "koppa_b(engine)/koppa_b(legacy Compton wake) = 1/C_g", koppa_b / legacy, 1.0 / Cg, 1e-14);
        tb::note("koppa_b (engine) = %.9e m ; legacy value l_P^2 m_p c/hbar = %.9e m", koppa_b, legacy);
    }

    tb::heading("T5 interaction-volume identity");
    {
        const double Vint = 0.25 * kPi * sdt::laws::law_III::R_p_lock * sdt::laws::law_III::R_p_lock * M::r_e;
        tb::note("V_int = %.6e m^3 ; P_eff = %.6e Pa", Vint, sdt::laws::law_III::P_eff);
        tb::check("T5", "P_eff V_int / (m_e c^2) = 1", sdt::laws::law_III::P_eff * Vint / (M::m_e * M::c * M::c), 1.0, 1e-9);
        tb::check("T5", "alpha hbar c / (m_e c^2 r_e) = 1 (shared-input)", M::alpha * M::hbar * M::c / (M::m_e * M::c * M::c * M::r_e), 1.0, 1e-9);
    }

    return tb::finish();
}
