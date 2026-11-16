// Chapter 29 — many-electron organisation: worked-example instrument.
// Pre-registration: Textbook/validation/ch29_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <array>
#include <cmath>
#include <cstdint>
#include <set>
#include <vector>

namespace {

namespace D = sdt::laws::atomic::dodecardinal;
using V3 = std::array<double, 3>;

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

// BFGS with Armijo backtracking on the engine's energy and gradient (log radii).
double descend(int Z, int ne, V3 x, V3* out) {
    const int n = D::group_count(ne);
    double Hinv[3][3] = {};
    for (int i = 0; i < n; ++i) Hinv[i][i] = 1.0;
    double E = D::state_energy_ry(Z, ne, x);
    V3 g = D::state_gradient(Z, ne, x);
    for (int it = 0; it < 600; ++it) {
        double gn = 0.0;
        for (int k = 0; k < n; ++k) gn = std::fmax(gn, std::fabs(g[k]));
        if (gn < 1e-9 * std::fmax(1.0, std::fabs(E))) break;
        V3 p{};
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) p[i] -= Hinv[i][j] * g[j];
        double dd = 0.0;
        for (int k = 0; k < n; ++k) dd += g[k] * p[k];
        if (dd >= 0.0) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) Hinv[i][j] = (i == j);
                p[i] = -g[i];
            }
            dd = 0.0;
            for (int k = 0; k < n; ++k) dd += g[k] * p[k];
        }
        double pmax = 0.0;
        for (int k = 0; k < n; ++k) pmax = std::fmax(pmax, std::fabs(p[k]));
        if (pmax > 1.0) for (int k = 0; k < n; ++k) p[k] /= pmax;
        dd = 0.0;
        for (int k = 0; k < n; ++k) dd += g[k] * p[k];
        double t = 1.0;
        bool ok = false;
        V3 y{};
        double Ey = 0.0;
        while (t > 1e-14) {
            for (int k = 0; k < n; ++k) y[k] = std::fmin(3.9, std::fmax(-6.9, x[k] + t * p[k]));
            Ey = D::state_energy_ry(Z, ne, y);
            if (Ey <= E + 1e-4 * t * dd) { ok = true; break; }
            t *= 0.5;
        }
        if (!ok) break;
        const V3 gy = D::state_gradient(Z, ne, y);
        V3 s{}, q{};
        double sq = 0.0;
        for (int k = 0; k < n; ++k) { s[k] = y[k] - x[k]; q[k] = gy[k] - g[k]; sq += s[k] * q[k]; }
        if (sq > 1e-14) {
            V3 Hq{};
            double qHq = 0.0;
            for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) Hq[i] += Hinv[i][j] * q[j];
            for (int k = 0; k < n; ++k) qHq += q[k] * Hq[k];
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j) Hinv[i][j] += (1.0 + qHq / sq) * s[i] * s[j] / sq - (Hq[i] * s[j] + s[i] * Hq[j]) / sq;
        }
        x = y; E = Ey; g = gy;
    }
    if (out) *out = x;
    return E;
}

V3 logs(const D::State& s, int groups) {
    V3 x{};
    for (int k = 0; k < groups; ++k) x[k] = std::log(s.radii_a0[k]);
    return x;
}

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    tb::validate_helpers();
    const double Ry = M::Ry_eV;

    tb::heading("V1 one-electron states");
    {
        double wr = 0, we = 0;
        for (int Z = 1; Z <= 10; ++Z) {
            const auto s = D::solve_state(Z, 1);
            wr = std::fmax(wr, std::fabs(s.radii_a0[0] * Z - 1.0));
            we = std::fmax(we, std::fabs(s.energy_ry / (-double(Z) * Z) - 1.0));
        }
        tb::check("V1", "r = 1/Z, worst relative", wr, 0.0, 1e-9, false);
        tb::check("V1", "E = -Z^2 Ry, worst relative", we, 0.0, 1e-9, false);
    }

    tb::heading("T1 analytic gradient against finite differences");
    {
        Rng g{2026};
        double worst = 0.0;
        int cases = 0;
        for (int Z = 1; Z <= 10; ++Z)
            for (int ne = 1; ne <= std::min(10, Z + 2); ++ne) {
                const int groups = D::group_count(ne);
                for (int rep = 0; rep < 5; ++rep) {
                    V3 x{};
                    for (int k = 0; k < groups; ++k) x[k] = std::log(0.3) + g.next() * (std::log(4.0) - std::log(0.3));
                    const V3 an = D::state_gradient(Z, ne, x);
                    const double E = D::state_energy_ry(Z, ne, x);
                    for (int k = 0; k < groups; ++k) {
                        auto cd = [&](double h) {
                            V3 p = x, m = x;
                            p[k] += h;
                            m[k] -= h;
                            return (D::state_energy_ry(Z, ne, p) - D::state_energy_ry(Z, ne, m)) / (2.0 * h);
                        };
                        const double fd = (4.0 * cd(0.5e-4) - cd(1e-4)) / 3.0;  // Richardson, truncation O(h^4)
                        worst = std::fmax(worst, std::fabs(an[k] - fd) / std::fmax(1.0, std::fabs(E)));
                    }
                    ++cases;
                }
            }
        tb::note("%d (Z, N_e, start) combinations", cases);
        tb::check("T1", "gradient vs finite difference, worst relative to max(1,|E|)", worst, 0.0, 1e-6, false);
    }

    tb::heading("T2 converged neutral states and independence of the start");
    std::array<D::State, 11> neutral{};
    {
        bool conv = true;
        double worst_lower = -1e300;
        bool enough = true;
        for (int Z = 1; Z <= 10; ++Z) {
            neutral[Z] = D::solve_state(Z, Z);
            conv = conv && neutral[Z].converged && neutral[Z].force_residual < 1e-8;
            const int groups = D::group_count(Z);
            Rng g{99u + Z};
            std::set<long> minima;
            double lowest = 1e300;
            int nconv = 0;
            for (int rep = 0; rep < 40; ++rep) {
                V3 x{};
                for (int k = 0; k < groups; ++k) x[k] = std::log(0.05) + g.next() * (std::log(6.0) - std::log(0.05));
                V3 xe{};
                const double E = descend(Z, Z, x, &xe);
                const V3 gr = D::state_gradient(Z, Z, xe);
                double gn = 0.0;
                for (int k = 0; k < groups; ++k) gn = std::fmax(gn, std::fabs(gr[k]));
                if (gn < 1e-6 * std::fmax(1.0, std::fabs(E)) && E < 1e50) {
                    minima.insert(std::lround(E * 1e6));
                    lowest = std::fmin(lowest, E);
                    ++nconv;
                }
            }
            enough = enough && nconv >= 5;
            worst_lower = std::fmax(worst_lower, neutral[Z].energy_ry - lowest);  // positive if the engine is above an independent minimum
            tb::note("Z=%2d : engine E = %.8f Ry ; lowest independent start %.8f Ry (%d of 40 converged) ; distinct minima %zu ; residual %.1e ; converged %d", Z, neutral[Z].energy_ry, lowest, nconv, minima.size(), neutral[Z].force_residual, int(neutral[Z].converged));
        }
        tb::check_true("T2", "at least 5 of 40 independent starts converged for every Z", enough);
        tb::check_true("T2", "every neutral state converged with force residual < 1e-8", conv);
        tb::check_true("T2", "no independent start reaches an energy below the engine's minimum by more than 1e-7 Ry", worst_lower <= 1e-7);
    }

    tb::heading("T3 positive-definite Hessian at the minima");
    {
        bool pd = true;
        for (int Z = 1; Z <= 10; ++Z) {
            const int groups = D::group_count(Z);
            const V3 x = logs(neutral[Z], groups);
            double H[3][3] = {};
            for (int c = 0; c < groups; ++c) {
                V3 p = x, m = x;
                p[c] += 1e-4;
                m[c] -= 1e-4;
                const V3 gp = D::state_gradient(Z, Z, p), gm = D::state_gradient(Z, Z, m);
                for (int r = 0; r < groups; ++r) H[r][c] = (gp[r] - gm[r]) / 2e-4;
            }
            for (int r = 0; r < groups; ++r)
                for (int c = r + 1; c < groups; ++c) H[r][c] = H[c][r] = 0.5 * (H[r][c] + H[c][r]);
            double m1 = H[0][0], m2 = groups > 1 ? H[0][0] * H[1][1] - H[0][1] * H[1][0] : 1.0, m3 = 1.0;
            if (groups == 3) m3 = H[0][0] * (H[1][1] * H[2][2] - H[1][2] * H[2][1]) - H[0][1] * (H[1][0] * H[2][2] - H[1][2] * H[2][0]) + H[0][2] * (H[1][0] * H[2][1] - H[1][1] * H[2][0]);
            const bool ok = m1 > 0 && m2 > 0 && m3 > 0;
            pd = pd && ok;
            tb::note("Z=%2d : minors %.4e %.4e %.4e", Z, m1, groups > 1 ? m2 : 0.0, groups == 3 ? m3 : 0.0);
        }
        tb::check_true("T3", "Hessian positive definite at all ten neutral minima", pd);
    }

    tb::heading("T4 first ionisation energies (computed values printed before the measured list)");
    std::array<double, 11> ie{};
    {
        tb::check("T4a", "hydrogen: first_ionisation_eV(1) = Ry", D::first_ionisation_eV(1), Ry, 1e-9);
        for (int Z = 1; Z <= 10; ++Z) ie[Z] = D::first_ionisation_eV(Z);
        std::printf("       COMPUTED (eV):");
        for (int Z = 1; Z <= 10; ++Z) std::printf(" %.4f", ie[Z]);
        std::printf("\n");
        // ---- the measured list is read below this line ----
        const double meas[11] = {0, 13.5984, 24.5874, 5.3917, 9.3227, 8.2980, 11.2603, 14.5341, 13.6181, 17.4228, 21.5645};
        const char* sym[11] = {"", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne"};
        double mean = 0.0, worst = 0.0;
        for (int Z = 1; Z <= 10; ++Z) {
            const double r = ie[Z] / meas[Z] - 1.0;
            mean += std::fabs(r) / 10.0;
            worst = std::fmax(worst, std::fabs(r));
            tb::note("%-2s : computed %8.4f eV ; measured %8.4f eV ; residual %+7.2f %%", sym[Z], ie[Z], meas[Z], 100.0 * r);
        }
        tb::note("mean absolute residual %.2f %% ; worst %.2f %%", 100.0 * mean, 100.0 * worst);
        tb::check_true("T4c", "every residual is within 10% (registered window)", worst <= 0.10);
    }

    tb::heading("T5 vertical against adiabatic ionisation");
    {
        bool ok = true;
        for (int Z = 2; Z <= 10; ++Z) {
            const int groups_n = D::group_count(Z);
            const V3 xn = logs(neutral[Z], groups_n);
            const double Evert = D::state_energy_ry(Z, Z - 1, xn);
            const auto ion = D::solve_state(Z, Z - 1);
            ok = ok && (Evert >= ion.energy_ry - 1e-9);
            tb::note("Z=%2d : vertical IE %.4f eV ; adiabatic IE %.4f eV ; relaxation %.4f eV", Z, (Evert - neutral[Z].energy_ry) * Ry, ie[Z], (Evert - ion.energy_ry) * Ry);
        }
        tb::check_true("T5", "vertical ion energy >= relaxed ion energy for Z = 2..10", ok);
    }

    return tb::finish();
}
