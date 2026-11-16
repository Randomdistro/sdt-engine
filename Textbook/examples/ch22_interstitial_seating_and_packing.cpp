// Chapter 22 — interstitial seating and packing: worked-example instrument.
// Pre-registration: Textbook/validation/ch22_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch22_interstitial_seating_and_packing
#include <sdt/laws.hpp>
#include <sdt/nuclear.hpp>

#include "tb_common.hpp"

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace {

namespace NL = sdt::laws::nuclear;

int layer_points(int n) {
    int c = 0;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            if (i + j <= n) ++c;
    return c;
}
int F(int n) { return (n + 1) * (n + 2); }
int B(int n) { return 2 * (n + 1); }
int R(int n) { return n * (n + 1); }

// Closure list for a schedule whose triton shells enter from onset n0.
// Deuteron tiers fill F(0..n0-1); from n0 the pattern is +B(n0), then +R(n)+B(n+1) for each further closure.
std::vector<int> schedule(int n0, int count) {
    std::vector<int> out;
    int total = 0;
    for (int n = 0; n < n0; ++n) {
        total += F(n);
        out.push_back(total);
    }
    total += B(n0);
    out.push_back(total);
    for (int n = n0; static_cast<int>(out.size()) < count; ++n) {
        total += R(n) + B(n + 1);
        out.push_back(total);
    }
    out.resize(count);
    return out;
}

}  // namespace

int main() {
    namespace Nu = sdt::nuclear;
    tb::validate_helpers();

    tb::heading("V1 lattice enumeration and Euler on known polyhedra");
    {
        const int want[6] = {1, 3, 6, 10, 15, 21};
        bool ok = true;
        for (int n = 0; n <= 5; ++n) ok = ok && layer_points(n) == want[n];
        tb::check_true("V1", "triangular-lattice points for n = 0..5 are 1, 3, 6, 10, 15, 21", ok);
        tb::check_true("V1", "icosahedron and cube satisfy V - E + F = 2", 12 - 30 + 20 == 2 && 8 - 12 + 6 == 2);
    }

    tb::heading("T1 closed forms for the tier law, 0 <= n <= 40");
    {
        bool lat = true, dbl = true, split = true, fn = true;
        for (int n = 0; n <= 40; ++n) {
            lat = lat && layer_points(n) == (n + 1) * (n + 2) / 2;
            dbl = dbl && 2 * layer_points(n) == NL::tier_capacity(n);
            split = split && B(n) + R(n) == F(n);
            fn = fn && NL::triton_shell_capacity(n) == B(n) && NL::surface_remainder(n) == R(n);
        }
        tb::check_true("T1", "layer = (n+1)(n+2)/2 by enumeration", lat);
        tb::check_true("T1", "double layer equals tier_capacity(n)", dbl);
        tb::check_true("T1", "B(n) + R(n) = F(n)", split);
        tb::check_true("T1", "engine shell and link functions equal 2(n+1) and n(n+1)", fn);
    }

    tb::heading("T2 the schedule, built independently");
    {
        const int want_obs[7] = {2, 8, 20, 28, 50, 82, 126};
        int total = F(0) + F(1) + F(2);
        std::vector<int> mine{F(0), F(0) + F(1), total};
        total += B(3);
        mine.push_back(total);
        for (int n = 3; n <= 6; ++n) {
            total += R(n) + B(n + 1);
            mine.push_back(total);
        }
        std::string s;
        for (int v : mine) s += std::to_string(v) + " ";
        tb::note("independent closures: %s", s.c_str());
        bool eq = mine.size() == 8;
        for (int k = 0; k < 7; ++k) eq = eq && mine[k] == want_obs[k] && NL::closure(k) == want_obs[k] && NL::magic_numbers[k] == want_obs[k];
        tb::check_true("T2", "independent build, engine closure(k) and stored magic_numbers agree for k = 0..6", eq);
        tb::check_true("T2", "forward closure is 184", mine.back() == 184);
        // species-pure order from the header: 2 +6 +12 +8 +12 +10 +20 +12 +30 +14 +42 +16
        const int steps[11] = {6, 12, 8, 12, 10, 20, 12, 30, 14, 42, 16};
        const int sub_want[12] = {2, 8, 20, 28, 40, 50, 70, 82, 112, 126, 168, 184};
        int t = 2;
        bool sub = (t == sub_want[0]);
        for (int i = 0; i < 11; ++i) {
            t += steps[i];
            sub = sub && t == sub_want[i + 1];
        }
        tb::check_true("T2", "species-pure sub-shell sums 2, 8, 20, 28, 40, 50, 70, 82, 112, 126, 168, 184", sub);
        tb::check_true("T2", "the steps are the closed forms F(1), F(2), B(3), R(3), B(4), R(4), B(5), R(5), B(6), R(6), B(7)", steps[0] == F(1) && steps[1] == F(2) && steps[2] == B(3) && steps[3] == R(3) && steps[4] == B(4) && steps[5] == R(4) && steps[6] == B(5) && steps[7] == R(5) && steps[8] == B(6) && steps[9] == R(6) && steps[10] == B(7));
    }

    tb::heading("T3 onset selection");
    {
        bool sign = true;
        std::string s;
        for (int n = 0; n <= 8; ++n) {
            const int d = NL::triton_delta_resistance_units(n);
            s += std::to_string(d) + " ";
            sign = sign && ((n <= 2) ? d > 0 : d < 0);
        }
        tb::note("delta resistance units, n = 0..8: %s", s.c_str());
        tb::check_true("T3", "positive for n <= 2, negative for n >= 3", sign);
        tb::check_true("T3", "descent onset equals q - 1 = 3 with q = 4", NL::triton_descent_onset == 3 && NL::triton_lock_contacts == 4);
        const int want[7] = {2, 8, 20, 28, 50, 82, 126};
        int matching = 0, which = 0;
        for (int n0 = 1; n0 <= 6; ++n0) {
            const auto c = schedule(n0, 7);
            bool all = true;
            std::string line;
            for (int v : c) line += std::to_string(v) + " ";
            for (int k = 0; k < 7; ++k) all = all && c[k] == want[k];
            tb::note("onset %d : %s%s", n0, line.c_str(), all ? " <- reproduces the observed list" : "");
            if (all) {
                ++matching;
                which = n0;
            }
        }
        tb::check_true("T3", "exactly one onset in 1..6 (n0 = 3) reproduces the observed list", matching == 1 && which == 3);
    }

    tb::heading("T4 Euler consistency of the shell link counts");
    {
        bool ok345 = true, bad67 = true;
        int first_fail = -1;
        for (int n = 3; n <= 8; ++n) {
            const int V = B(n), E = R(n), Fc = 2 - V + E;
            const bool fits = E <= 3 * V - 6;
            tb::note("n = %d : V = %d, E = %d, F = 2 - V + E = %d, 3V - 6 = %d : %s", n, V, E, Fc, 3 * V - 6, fits ? "E <= 3V-6" : "E > 3V-6 (no convex polyhedron)");
            if (n <= 5) ok345 = ok345 && fits && (Fc == (n == 3 ? 6 : n == 4 ? 12 : 20));
            else {
                bad67 = bad67 && !fits;
                if (first_fail < 0 && !fits) first_fail = n;
            }
        }
        tb::check_true("T4", "n = 3, 4, 5 satisfy E <= 3V - 6 with F = 6, 12, 20", ok345);
        tb::check_true("T4", "n = 6, 7, 8 violate it; the first failure is at n = 6", bad67 && first_fail == 6);
    }

    tb::heading("T5 triton parity rule");
    {
        long bad = 0;
        for (int Z = 1; Z <= 120; ++Z)
            for (int A = 1; A <= 400; ++A) {
                const int N = A - Z;
                const bool rule = NL::triton_parity_misfit(Z, A);
                const bool odd_odd = (Z % 2 == 1) && (N % 2 == 1) && (N >= Z);
                if (rule != odd_odd) ++bad;
            }
        tb::check_true("T5", "misfit rule equals (Z odd, N odd, N >= Z) on the whole grid", bad == 0);
        std::set<std::pair<int, int>> found, expect = {{1, 2}, {3, 6}, {5, 10}, {7, 14}, {19, 40}, {23, 50}, {57, 138}, {71, 176}, {73, 180}};
        std::string s;
        for (const auto& r : Nu::natural_basis)
            if (NL::triton_parity_misfit(r.Z, r.A)) {
                found.insert({r.Z, r.A});
                s += std::string(Nu::element_symbol(r.Z)) + "-" + std::to_string(r.A) + " ";
            }
        tb::note("misfit set in the embedded table (%zu): %s", found.size(), s.c_str());
        tb::check_true("T5", "the misfit set equals the nine registered species", found == expect);
    }

    return tb::finish();
}
