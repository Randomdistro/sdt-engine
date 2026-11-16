// Chapter 46 — hydrogen-proton boundary crossing: worked-example instrument.
// Pre-registration: Textbook/validation/ch46_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <functional>

namespace {

namespace M = sdt::laws::measured;

// d(lnOm)/dS = aOm(S), d(lnRp)/dS = aRp(S); RK4 on (lnOm, lnRp); returns ln R(S) = lnOm - lnRp relative to start.
struct State {
    double lnOm, lnRp;
};

State rk4(const std::function<double(double)>& aOm, const std::function<double(double)>& aRp, double S, int n) {
    State s{0.0, 0.0};
    const double h = S / n;
    for (int i = 0; i < n; ++i) {
        const double t = i * h;
        const double k1o = aOm(t), k1p = aRp(t);
        const double k2o = aOm(t + 0.5 * h), k2p = aRp(t + 0.5 * h);
        const double k4o = aOm(t + h), k4p = aRp(t + h);
        s.lnOm += h * (k1o + 4.0 * k2o + k4o) / 6.0;
        s.lnRp += h * (k1p + 4.0 * k2p + k4p) / 6.0;
    }
    return s;
}

// First S >= 0 at which ln R0 + (lnOm - lnRp) = 0 for a monotonically falling ln R.
double crossing(double lnR0, const std::function<double(double)>& aOm, const std::function<double(double)>& aRp) {
    double lo = 0.0, hi = 50.0;
    for (int it = 0; it < 200; ++it) {
        const double mid = 0.5 * (lo + hi);
        const auto s = rk4(aOm, aRp, mid, 4000);
        const double lnR = lnR0 + s.lnOm - s.lnRp;
        if (lnR > 0.0) lo = mid; else hi = mid;
    }
    return 0.5 * (lo + hi);
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    tb::check("V1", "hbar/(m_p c) = 2.103089e-16 m", M::hbar / (M::m_p * M::c), 2.103089e-16, 1e-6);
    tb::check("V1", "r_e = alpha^2 a_0 = 2.8179403e-15 m", M::r_e, 2.8179403e-15, 1e-7);
    {
        const auto s = rk4([](double) { return 0.0; }, [](double) { return 1.0; }, 1.0, 1000);  // ln R changes by -1
        tb::check("V1", "RK4: R(1) = 3 e^-1 for r = -1", 3.0 * std::exp(s.lnOm - s.lnRp), 3.0 * std::exp(-1.0), 1e-12);
    }

    tb::heading("T1 the lock ratio, computed before the measured radius is read");
    const double R_lock_formula = 4.0 * M::hbar / (M::m_p * M::c);
    const double Rlock_ratio_direct = M::r_e / R_lock_formula;
    const double Rlock_ratio_closed = (M::alpha / 4.0) * (M::m_p / M::m_e);
    tb::note("Om_H = alpha^2 a_0 = %.9e m ; R_p,lock = 4 hbar/(m_p c) = %.9e m", M::r_e, R_lock_formula);
    tb::note("R_lock (direct) = %.9f ; (alpha/4)(m_p/m_e) = %.9f", Rlock_ratio_direct, Rlock_ratio_closed);
    tb::check("T1", "Om_H / R_p,lock equals (alpha/4)(m_p/m_e)", Rlock_ratio_direct, Rlock_ratio_closed, 1e-9);
    tb::check("T1", "R_lock = 3.34976", Rlock_ratio_direct, 3.34976, 1e-5);
    tb::check_true("T1", "trefoil_lock_coordination equals 4", sdt::laws::lock_geometry::trefoil_lock_coordination == 4);
    tb::check("T1", "engine R_p_lock equals 4 hbar/(m_p c)", sdt::laws::law_III::R_p_lock, R_lock_formula, 1e-14);
    const double Cg = M::R_p / R_lock_formula;
    tb::note("read now: R_p (stored measured) = %.4e m ; C_g = R_p/R_p,lock = %.6f ; R = Om_H/R_p = %.6f", M::R_p, Cg, M::r_e / M::R_p);
    tb::check_true("T1", "|C_g - 1| < 1e-3", std::fabs(Cg - 1.0) < 1e-3);

    tb::heading("T2 crossing condition");
    const double lnR0 = std::log(Rlock_ratio_direct);
    tb::note("ln R_lock = %.6f ; required log change %.6f", lnR0, -lnR0);
    tb::check_true("T2", "-ln R_lock lies in [-1.2095, -1.2085]", -lnR0 >= -1.2095 && -lnR0 <= -1.2085);
    {
        const double Sexp = lnR0;  // net r = -1
        const double Sc = crossing(lnR0, [](double) { return -2.0; }, [](double) { return -1.0; });
        const double Sf = crossing(lnR0, [](double) { return -1.0; }, [](double) { return 0.0; });
        tb::note("crossing S*: contemporaneous %.10f ; fixed-coordinate %.10f", Sc, Sf);
        tb::check("T2", "contemporaneous crossing equals -ln R_0 / r", Sc, Sexp, 1e-9);
        tb::check("T2", "fixed-coordinate crossing equals -ln R_0 / r", Sf, Sexp, 1e-9);
        const auto sc = rk4([](double) { return -2.0; }, [](double) { return -1.0; }, Sc, 4000);
        const auto sf = rk4([](double) { return -1.0; }, [](double) { return 0.0; }, Sf, 4000);
        const double RpC = std::exp(sc.lnRp), RpF = std::exp(sf.lnRp);
        tb::note("end-state R_p / R_p,0: contemporaneous %.9f ; fixed-coordinate %.9f", RpC, RpF);
        tb::check("T2", "end-state proton boundary radii differ by the factor R_0", RpF / RpC, Rlock_ratio_direct, 1e-9);
        const double Sn = crossing(lnR0, [](double S) { return -2.0 - 0.5 * S; }, [](double) { return -1.0; });
        const double Sn_exact = 2.0 * (std::sqrt(1.0 + lnR0) - 1.0);
        tb::note("non-constant net rate r(S) = -1 - S/2: S* = %.10f (exact %.10f)", Sn, Sn_exact);
        tb::check("T2", "non-constant rate crossing equals 2(sqrt(1 + ln R_0) - 1)", Sn, Sn_exact, 1e-9);
    }

    tb::heading("T3 rate and branch");
    {
        const double S1 = crossing(lnR0, [](double) { return -1.0; }, [](double) { return 0.0; });
        const double Sh = crossing(lnR0, [](double) { return -0.5; }, [](double) { return 0.0; });
        const double S2 = crossing(lnR0, [](double) { return -2.0; }, [](double) { return 0.0; });
        tb::note("S*(r = -0.5, -1, -2) = %.8f, %.8f, %.8f", Sh, S1, S2);
        tb::check("T3", "S*(r=-0.5) = 2 S*(r=-1)", Sh, 2.0 * S1, 1e-9);
        tb::check("T3", "S*(r=-2) = S*(r=-1)/2", S2, 0.5 * S1, 1e-9);
        const double lnCg = std::log(Cg);
        const double lnR_meas = std::log(M::r_e / M::R_p);
        tb::note("ln C_g = %+.6e ; log change required: lock branch %.6f, measured branch %.6f", lnCg, -lnR0, -lnR_meas);
        tb::check("T3", "the branches differ in the required log change by ln C_g", (-lnR_meas) - (-lnR0), lnCg, 1e-9);
        tb::check_true("T3", "|ln C_g| < 1e-3", std::fabs(lnCg) < 1e-3);
    }

    return tb::finish();
}
