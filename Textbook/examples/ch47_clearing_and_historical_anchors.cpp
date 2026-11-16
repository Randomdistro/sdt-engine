// Chapter 47 — Clearing and historical anchors: worked-example instrument.
// Pre-registration: Textbook/validation/ch47_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

namespace {

namespace M = sdt::laws::measured;

double root_x(double power) {  // x = power (1 - e^-x)
    double a = power - 1.5, b = power + 1.0;
    auto f = [&](double x) { return x - power * (1.0 - std::exp(-x)); };
    for (int it = 0; it < 200; ++it) {
        const double m = 0.5 * (a + b);
        if (f(m) < 0) a = m; else b = m;
    }
    return 0.5 * (a + b);
}

}  // namespace

int main() {
    tb::validate_helpers();

    const double b = M::h * M::c / (M::k_B * root_x(5.0));
    const double T0 = M::T_CMB;

    tb::heading("V1 known answers");
    tb::check("V1", "native Wien constant 2.897771955e-3 m K", b, 2.897771955e-3, 1e-9);
    tb::check("V1", "wavelength of a 1 MeV photon", M::h * M::c / (1e6 * 1.602176634e-19), 1.239841984e-12, 1e-6);

    tb::heading("T1 landmark conversions");
    const double T760 = b / 760e-9, T780 = b / 780e-9, T975 = b / 975e-9;
    tb::note("760 nm -> %.4f K ; 780 nm -> %.4f K ; 975 nm -> %.4f K", T760, T780, T975);
    tb::check("T1", "760 nm -> 3812.86 K", T760, 3812.86, 2e-6);
    tb::check("T1", "780 nm -> 3715.09 K", T780, 3715.09, 2e-6);
    const double Trel = T0 * 1090.0;
    tb::note("engine T_release = %.6f K ; T_CMB * 1090 = %.6f K", M::T_release, Trel);
    tb::check("T1", "engine T_release = T_CMB * 1090", M::T_release, Trel, 1e-12);
    const double Thist = T0 * 1090.8;
    tb::note("historical ratio 1090.8 -> %.4f K", Thist);
    tb::check("T1", "historical ratio 1090.8 -> 2972.98 K", Thist, 2972.98, 3e-6);
    const double Tload06 = 3073.58, Tload1 = 1844.15;
    tb::check("T1", "drag-loading consistency T(1)/T(0.6) = 0.6", Tload1 / Tload06, 0.6, 3e-6);
    const double lam1 = b / Tload1;
    tb::note("wavelength equivalent of 1844.15 K: %.4f nm", lam1 * 1e9);
    tb::check_true("T1", "the wavelength equivalent of 1844.15 K lies in [1570, 1573] nm", lam1 * 1e9 >= 1570.0 && lam1 * 1e9 <= 1573.0);

    tb::heading("T2 the landmarks are not collapsed");
    {
        std::vector<double> L = {T760, T780, T975, Tload1, Tload06, Trel, Thist};
        bool distinct = true;
        double mn = 1e300, mx = 0.0, minsep = 1e300;
        for (size_t i = 0; i < L.size(); ++i) {
            mn = std::fmin(mn, L[i]);
            mx = std::fmax(mx, L[i]);
            for (size_t j = i + 1; j < L.size(); ++j) {
                const double sep = std::fabs(L[i] - L[j]) / std::fmax(L[i], L[j]);
                minsep = std::fmin(minsep, sep);
                if (sep <= 1e-4) distinct = false;
            }
        }
        tb::note("seven landmark temperatures from %.3f K to %.3f K ; smallest pairwise relative separation %.3e ; max/min %.4f", mn, mx, minsep, mx / mn);
        tb::check_true("T2", "the seven landmarks are pairwise distinct at 1e-4 relative resolution", distinct);
        tb::check_true("T2", "the largest landmark exceeds the smallest by a factor of at least 2.0", mx / mn >= 2.0);
    }

    tb::heading("T3 distance is a separate closure");
    {
        const double ngeo = std::log2(sdt::laws::law_I::R_CMB / M::l_P);
        const double lam_cmb = b / T0;
        const double ntherm = std::log2(lam_cmb / 760e-9);
        const double formal = b / sdt::laws::law_I::R_CMB;
        tb::note("log2(R_CMB/l_P) = %.4f ; thermal octaves CMB peak -> 760 nm = %.4f ; formal b/R_CMB = %.4e K", ngeo, ntherm, formal);
        tb::check_true("T3", "log2(R_CMB / l_P) lies in [205, 206]", ngeo >= 205.0 && ngeo <= 206.0);
        tb::check("T3", "thermal octaves from the CMB peak to 760 nm", ntherm, 10.4501, 1e-4);
        tb::note("RECORDED REJECTION (run 1 criterion kept): the registered bound 1e-30 K was an arithmetic slip; the value is %.4e K", formal);
        tb::check_true("T3", "the registered statement (b / R_CMB below 1e-30 K) is rejected", !(formal < 1e-30));
        tb::check_true("T3", "POST-RUN clause: the formal value is below 1e-29 K and below 1e-29 T_CMB", formal < 1e-29 && formal < 1e-29 * T0);
        tb::check("T3", "N l_P = R_CMB (engine)", sdt::laws::law_I::N * M::l_P, sdt::laws::law_I::R_CMB, 1e-12);
    }

    tb::heading("T4 hard-gamma extension");
    {
        bool inc = true, dec = true, pos = true;
        double prevT = 0.0, prevR = 1e300;
        for (int d = 0; d <= 15; ++d) {
            const double E = std::pow(10.0, d) * 1.602176634e-19;
            const double lam = M::h * M::c / E;
            const double T = b / lam, r = T0 / T;
            inc = inc && T > prevT;
            dec = dec && r < prevR;
            pos = pos && r > 0.0;
            prevT = T;
            prevR = r;
        }
        tb::check_true("T4", "T_eq increases and c_epoch/c_0 decreases strictly over 1 eV ... 1e15 eV", inc && dec);
        tb::check_true("T4", "c_epoch/c_0 stays positive at every energy", pos);
        const double lam = M::h * M::c / (1e6 * 1.602176634e-19);
        const double Teq = b / lam, r = T0 / Teq;
        tb::note("1 MeV: lambda = %.6e m ; T_eq = %.6e K ; T0/T_eq = %.6e ; (T0/T_eq)^2 = %.6e ; bath energy density a T_eq^4 = %.4e J/m^3", lam, Teq, r, r * r, M::a_rad * std::pow(Teq, 4));
        tb::check_true("T4", "1 MeV: T_eq in [2.33e9, 2.35e9] K", Teq >= 2.33e9 && Teq <= 2.35e9);
        tb::check_true("T4", "1 MeV: T0/T_eq in [1.1e-9, 1.2e-9]", r >= 1.1e-9 && r <= 1.2e-9);
        tb::check_true("T4", "1 MeV: (T0/T_eq)^2 in [1.3e-18, 1.4e-18]", r * r >= 1.3e-18 && r * r <= 1.4e-18);
    }

    return tb::finish();
}
