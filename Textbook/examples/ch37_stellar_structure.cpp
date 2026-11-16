// Chapter 37 — stellar structure: worked-example instrument.
// Pre-registration: Textbook/validation/ch37_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>
#include <sdt/neutrino.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <fstream>
#include <string>
#include <vector>

namespace {

constexpr double kPi = std::numbers::pi;

struct LE {
    std::vector<double> xi, th, dth;
    double xi1 = 0.0, w1 = 0.0;
};

LE lane_emden(double n) {
    LE r;
    const double h = 1e-4;
    double x = 1e-6, th = 1.0 - x * x / 6.0 + n * std::pow(x, 4) / 120.0, p = -x / 3.0 + n * std::pow(x, 3) / 30.0;
    auto f = [&](double X, double T, double P, double& dT, double& dP) {
        dT = P;
        dP = -(T > 0 ? std::pow(T, n) : 0.0) - 2.0 * P / X;
    };
    r.xi.push_back(x); r.th.push_back(th); r.dth.push_back(p);
    while (th > 0.0) {
        double k1T, k1P, k2T, k2P, k3T, k3P, k4T, k4P;
        f(x, th, p, k1T, k1P);
        f(x + 0.5 * h, th + 0.5 * h * k1T, p + 0.5 * h * k1P, k2T, k2P);
        f(x + 0.5 * h, th + 0.5 * h * k2T, p + 0.5 * h * k2P, k3T, k3P);
        f(x + h, th + h * k3T, p + h * k3P, k4T, k4P);
        const double thn = th + h / 6.0 * (k1T + 2 * k2T + 2 * k3T + k4T), pn = p + h / 6.0 * (k1P + 2 * k2P + 2 * k3P + k4P);
        if (thn <= 0.0) {
            const double fr = th / (th - thn);
            r.xi1 = x + fr * h;
            const double pe = p + fr * (pn - p);
            r.w1 = -r.xi1 * r.xi1 * pe;
            break;
        }
        x += h; th = thn; p = pn;
        r.xi.push_back(x); r.th.push_back(th); r.dth.push_back(p);
    }
    return r;
}

double interp(const LE& le, const std::vector<double>& arr, double x) {
    const double h = 1e-4;
    const std::size_t i = static_cast<std::size_t>((x - le.xi[0]) / h);
    const double fr = (x - le.xi[i]) / h;
    return arr[i] * (1.0 - fr) + arr[i + 1] * fr;
}

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    namespace L1 = sdt::laws::law_I;
    namespace L2 = sdt::laws::law_II;
    tb::validate_helpers();
    const double c = M::c;

    tb::heading("V1 Lane-Emden solver on known solutions");
    {
        const double ns[4] = {0.0, 1.0, 1.5, 3.0};
        const double xi_want[4] = {std::sqrt(6.0), kPi, 3.65375, 6.89685};
        const double w_want[4] = {2.0 * std::sqrt(6.0), kPi, 2.71406, 2.01824};
        const double tol[4] = {1e-4, 1e-6, 1e-5, 1e-5};
        for (int i = 0; i < 4; ++i) {
            const LE le = lane_emden(ns[i]);
            char lab[96];
            std::snprintf(lab, sizeof lab, "n = %.1f: xi_1", ns[i]);
            tb::check("V1", lab, le.xi1, xi_want[i], tol[i]);
            std::snprintf(lab, sizeof lab, "n = %.1f: -xi_1^2 theta'(xi_1)", ns[i]);
            tb::check("V1", lab, le.w1, w_want[i], tol[i]);
        }
    }

    tb::heading("T1 convergence pressure is an energy density, not a power");
    {
        const double area = 4.0 * kPi * M::R_Sun * M::R_Sun;
        const double force = L1::P_conv * area, power = force * c;
        tb::note("P_conv = %.4e Pa ; P_conv x 4 pi R_sun^2 = %.4e N ; x c = %.4e W ; L_sun = %.4e W ; ratio %.3e", L1::P_conv, force, power, L2::L_Sun, power / L2::L_Sun);
        tb::check_true("T1", "inserting c into P_conv x area gives more than 1e40 times L_sun", power / L2::L_Sun > 1e40);
    }

    tb::heading("T2 reference domain radius");
    {
        const double F = c * L1::u_CMB / 4.0;
        const double rd = std::sqrt(L2::L_Sun / (4.0 * kPi * F));
        tb::check("T2", "pressure_domain(L_Sun) equals sqrt(L/(4 pi F_CMB))", L2::pressure_domain(L2::L_Sun), rd, 1e-12);
        tb::check("T2", "stored r_domain_Sun agrees within 2e-3", L2::r_domain_Sun, rd, 2e-3);
        tb::note("F_CMB = %.4e W/m^2 ; r_domain = %.5e m = %.1f AU", F, rd, rd / M::AU);
    }

    tb::heading("T3 reduced stationary structure under the native source-length acceleration");
    {
        const double Gleg = M::l_P * M::l_P * c * c * c / M::hbar;
        const double Geff = c * c * sdt::laws::bridge::koppa_per_baryon / M::m_p;
        const double Cg = M::R_p / sdt::laws::law_III::R_p_lock;
        tb::check("T3a", "G_eff / (l_P^2 c^3/hbar) = 1/C_g", Geff / Gleg, 1.0 / Cg, 1e-14);
        // Sun's source strength from the ephemeris constants (Horizons object data), km^3/s^2 -> m
        double GMsun = 0.0;
        {
            std::ifstream f("C:/Users/Jimmi/OneDrive/Desktop/sdt-engine/Textbook/data/horizons/gm.csv");
            std::string line;
            std::getline(f, line);
            while (std::getline(f, line)) if (line.rfind("Sun,", 0) == 0) GMsun = std::stod(line.substr(4));
        }
        const double varpi_sun = GMsun * 1e9 / (c * c);
        const double Nb = varpi_sun / sdt::laws::bridge::koppa_per_baryon, Mass = Nb * M::m_p;
        tb::note("varpi_sun = %.6f m ; N_b = %.6e baryons ; M = N_b m_p = %.6e kg (printed, not compared)", varpi_sun, Nb, Mass);
        auto model = [&](double Mt, double R, double* rhoc, double* Pc, double* K, double* a_out) {
            const LE le = lane_emden(3.0);
            const double a = R / le.xi1;
            *rhoc = Mt * std::pow(le.xi1, 3) / (4.0 * kPi * R * R * R * le.w1);
            *K = 4.0 * kPi * Geff * a * a * std::pow(*rhoc, 1.0 - 1.0 / 3.0) / 4.0;
            *Pc = *K * std::pow(*rhoc, 1.0 + 1.0 / 3.0);
            *a_out = a;
        };
        double rhoc, Pc, K, a;
        model(Mass, M::R_Sun, &rhoc, &Pc, &K, &a);
        const double rbar = Mass / (4.0 * kPi / 3.0 * std::pow(M::R_Sun, 3));
        tb::note("n = 3 polytrope: mean density %.4e kg/m^3 ; central density %.4e kg/m^3 ; central pressure %.4e Pa (printed, not compared with any solar model)", rbar, rhoc, Pc);
        // hydrostatic consistency
        const LE le = lane_emden(3.0);
        double worst = 0.0;
        for (double fr : {0.3, 0.6, 0.9}) {
            const double r = fr * M::R_Sun, xi = r / a;
            const double th = interp(le, le.th, xi), dth = interp(le, le.dth, xi);
            const double P = Pc * std::pow(th, 4.0), rho = rhoc * std::pow(th, 3.0);
            const double dPdr = Pc * 4.0 * std::pow(th, 3.0) * dth / a;
            const double Menc = 4.0 * kPi * a * a * a * rhoc * (-xi * xi * dth);
            const double varpi_enc = (Menc / M::m_p) * sdt::laws::bridge::koppa_per_baryon;
            const double g = c * c * varpi_enc / (r * r);
            worst = std::fmax(worst, std::fabs(dPdr / (-rho * g) - 1.0));
            (void)P;
        }
        tb::check("T3d", "dP/dr = -rho g with g = c^2 varpi_enc/r^2 at r/R = 0.3, 0.6, 0.9, worst relative", worst, 0.0, 1e-5, false);
        double rc2, Pc2, K2, a2, rc3, Pc3, K3, a3;
        model(Mass, 2.0 * M::R_Sun, &rc2, &Pc2, &K2, &a2);
        model(2.0 * Mass, M::R_Sun, &rc3, &Pc3, &K3, &a3);
        tb::check("T3e", "P_c(2R)/P_c(R) = 1/16", Pc2 / Pc, 1.0 / 16.0, 1e-12);
        tb::check("T3e", "P_c(2M)/P_c(M) = 4", Pc3 / Pc, 4.0, 1e-12);
    }

    tb::heading("T4 energy-chain accounting (anchored on L_sun)");
    {
        namespace S = sdt::neutrino::solar;
        const double Echain = 26.7e6 * M::eV_to_J;
        tb::check("T4", "solar::nu_rate = 2 L_sun/(26.7 MeV)", S::nu_rate, 2.0 * L2::L_Sun / Echain, 1e-12);
        tb::check("T4", "solar::flux_1AU = nu_rate/(4 pi AU^2)", S::flux_1AU, S::nu_rate / (4.0 * kPi * M::AU * M::AU), 1e-12);
        double GMsun = 0.0;
        {
            std::ifstream f("C:/Users/Jimmi/OneDrive/Desktop/sdt-engine/Textbook/data/horizons/gm.csv");
            std::string line;
            std::getline(f, line);
            while (std::getline(f, line)) if (line.rfind("Sun,", 0) == 0) GMsun = std::stod(line.substr(4));
        }
        const double Nb = (GMsun * 1e9 / (c * c)) / sdt::laws::bridge::koppa_per_baryon, Mc2 = Nb * M::m_p * c * c;
        tb::note("chain rate L/E_chain = %.4e per s ; nu rate %.4e per s ; flux at 1 AU %.4e per m^2 s", L2::L_Sun / Echain, S::nu_rate, S::flux_1AU);
        tb::note("mass-energy time M c^2/L_sun = %.4e yr ; fraction released by one chain per four protons = %.5f", Mc2 / L2::L_Sun / (365.25 * 86400.0), 26.7e6 * M::eV_to_J / (4.0 * M::m_p * c * c));
    }

    return tb::finish();
}
