// Chapter 49 — inertia and equivalence: worked-example instrument.
// Pre-registration: Textbook/validation/ch49_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/dynamics.hpp>
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
namespace L4 = sdt::laws::law_IV;
namespace D = sdt::dynamics;

constexpr double MeV_J = 1.602176634e-13;

double eta(double a1, double a2) { return 2.0 * (a1 - a2) / (a1 + a2); }

}  // namespace

int main() {
    tb::validate_helpers();

    const double Phi = sdt::laws::law_I::Phi;
    const double Pcf = Phi / (3.0 * M::l_P3);

    tb::heading("V1 known answers");
    for (double m : {M::m_e, M::m_p, M::m_d})
        tb::check("V1", "mass_from_V_disp(V_disp_from_mass(m)) = m", L4::mass_from_V_disp(L4::V_disp_from_mass(m)), m, 1e-12);
    tb::check("V1", "V_disp is additive in mass", L4::V_disp_from_mass(M::m_p + M::m_n), L4::V_disp_from_mass(M::m_p) + L4::V_disp_from_mass(M::m_n), 1e-13);
    tb::check("V1", "m c^2 = P_cf V_disp (proton)", M::m_p * M::c * M::c, Pcf * L4::V_disp_from_mass(M::m_p), 1e-12);
    tb::check("V1", "quadrature of mu^2 over [0,1] = 1/3", tb::integrate([](double mu) { return mu * mu; }, 0.0, 1.0), 1.0 / 3.0, 1e-13);

    tb::heading("T1 engaged volume as inertia");
    {
        const double Ve = L4::V_disp_from_mass(M::m_e), Vp = L4::V_disp_from_mass(M::m_p);
        tb::note("V_disp(e) = %.6e m^3 ; V_disp(p) = %.6e m^3 ; exclusion radii %.6e m, %.6e m", Ve, Vp, L4::exclusion_radius(Ve), L4::exclusion_radius(Vp));
        tb::check("T1", "V_disp(p)/V_disp(e) = m_p/m_e = 1836.15267343", Vp / Ve, 1836.15267343, 1e-10);
        tb::check("T1", "exclusion-radius ratio = (m_p/m_e)^(1/3)", L4::exclusion_radius(Vp) / L4::exclusion_radius(Ve), std::cbrt(M::m_p / M::m_e), 1e-12);
        // replace l_P by 2 l_P in both the forward and the inverse expression: the mass is returned unchanged
        const double l2 = 2.0 * M::l_P, l23 = l2 * l2 * l2;
        const double V2 = 3.0 * M::m_p * l23 * M::c * M::c / Phi;
        const double back = Phi * V2 / (3.0 * l23 * M::c * M::c);
        tb::check("T1", "with l_P replaced by 2 l_P the round trip still returns m_p", back, M::m_p, 1e-12);
        tb::check("T1", "the ratio V_p/V_e is unchanged under l_P -> 2 l_P", (3.0 * M::m_p * l23 * M::c * M::c / Phi) / (3.0 * M::m_e * l23 * M::c * M::c / Phi), Vp / Ve, 1e-12);
    }

    tb::heading("T2 Construction I and II");
    const double Bd = M::B_deuteron, Ba = M::B_alpha;
    const double m_alpha = 2.0 * M::m_p + 2.0 * M::m_n - Ba * MeV_J / (M::c * M::c);
    {
        const double masses[6] = {M::m_e, M::m_p, M::m_n, M::m_d, M::m_t, m_alpha};
        double worst = 0.0;
        for (int i = 0; i < 6; ++i)
            for (int j = i + 1; j < 6; ++j) {
                const double ai = L4::V_disp_from_mass(masses[i]) / masses[i];
                const double aj = L4::V_disp_from_mass(masses[j]) / masses[j];
                worst = std::fmax(worst, std::fabs(eta(ai, aj)));
            }
        tb::check("T2", "Construction I: eta = 0 for all pairs of six masses (worst |eta|)", worst, 0.0, 1e-15, false);
        const double fd = Bd * MeV_J / (M::m_d * M::c * M::c);
        const double ft = M::B_triton * MeV_J / (M::m_t * M::c * M::c);
        const double fh = M::B_helion * MeV_J / (M::m_He3 * M::c * M::c);
        const double fa = Ba * MeV_J / (m_alpha * M::c * M::c);
        tb::note("m_alpha = %.9e kg ; f = B/(M c^2): d %.6e, t %.6e, helion %.6e, alpha %.6e", m_alpha, fd, ft, fh, fa);
        auto etaII = [&](double f1, double f2) { return eta(1.0 + f1, 1.0 + f2); };
        const double eta_ap = etaII(fa, 0.0), eta_dp = etaII(fd, 0.0);
        tb::note("Construction II: eta(alpha, p) = %.6e ; eta(d, p) = %.6e ; eta(t, p) = %.6e ; eta(alpha, d) = %.6e", eta_ap, eta_dp, etaII(ft, 0.0), etaII(fa, fd));
        tb::check("T2", "eta(alpha, p) = 2 f/(2 + f)", eta_ap, 2.0 * fa / (2.0 + fa), 1e-12);
        tb::check_true("T2", "eta(alpha, p) lies in [7.0e-3, 8.0e-3]", eta_ap >= 7.0e-3 && eta_ap <= 8.0e-3);
        tb::check_true("T2", "eta(d, p) lies in [1.1e-3, 1.3e-3]", eta_dp >= 1.1e-3 && eta_dp <= 1.3e-3);
        const double track = 1e-13 / fa;
        tb::note("required tracking accuracy of the coupling for eta_target = 1e-13 against the alpha: %.4e", track);
        tb::check_true("T2", "the required tracking accuracy lies in [1.0e-11, 2.0e-11]", track >= 1.0e-11 && track <= 2.0e-11);
    }

    tb::heading("T3 tensor response of a directional body");
    {
        const double delta = 1e-3, g0 = 1.0;
        // orientation average over mu = cos(angle between body axis and D), uniform on [0,1]: <D.g.D> = g0 (1 + delta <mu^2>)
        const double avg = tb::integrate([&](double mu) { return g0 * (1.0 + delta * mu * mu); }, 0.0, 1.0);
        tb::check("T3", "orientation-averaged response = g0 (1 + delta/3)", avg, g0 * (1.0 + delta / 3.0), 1e-12);
        const double phi = std::acos(-1.0) / 4.0;
        // g = g0 (I + delta n n^T) with n along x: a = g D, D = (cos phi, sin phi)
        const double ax = g0 * (1.0 + delta) * std::cos(phi), ay = g0 * std::sin(phi);
        const double rot = std::atan2(ay, ax) - phi;
        tb::note("rotation of the acceleration from D at 45 degrees: %.9e rad ; -delta/2 = %.9e", rot, -0.5 * delta);
        tb::check_true("T3", "the rotation at 45 degrees is within delta^2 of -delta/2", std::fabs(rot + 0.5 * delta) <= delta * delta);
        const double rot0 = std::atan2(0.0, g0 * (1.0 + delta)) - 0.0;
        tb::check("T3", "along a principal axis the rotation is 0", rot0, 0.0, 1e-15, false);
        tb::check("T3", "magnitude ratio along the two principal axes is 1 + delta", (g0 * (1.0 + delta)) / g0, 1.0 + delta, 1e-15);
    }

    tb::heading("T4 engine implementation");
    {
        const double ks = sdt::laws::bridge::koppa_Sun, r = M::AU;
        double worst = 0.0;
        for (double kt : {1e-30, 1e-20, 1e-10}) {
            std::vector<D::Body> bodies(2);
            bodies[0] = {{0, 0, 0}, {0, 0, 0}, ks, 0.0};
            bodies[1] = {{r, 0, 0}, {0, 0, 0}, kt, 0.0};
            std::vector<D::Vec3> a;
            const auto st = D::accelerations(bodies, a);
            if (st != D::StepStatus::advanced) { tb::check_true("T4", "accelerations advanced", false); continue; }
            const double expect = M::c * M::c * ks / (r * r);
            worst = std::fmax(worst, std::fabs(D::norm(a[1]) / expect - 1.0));
        }
        tb::check("T4", "test-body acceleration = c^2 varpi_Sun / r^2 for test strengths 1e-30, 1e-20, 1e-10 m (worst deviation)", worst, 0.0, 1e-14, false);
        const double kA = D::koppa_from_baryons(3.0e50), kB = D::koppa_from_baryons(7.0e50), kAB = D::koppa_from_baryons(1.0e51);
        tb::check("T4", "koppa_from_baryons is additive in baryon count", kAB, kA + kB, 1e-14);
        const double k4 = D::koppa_from_baryons(4.0), kfree = 4.0 * D::koppa_from_baryons(1.0);
        tb::check("T4", "an alpha (4 baryons) and 4 free baryons have the same engine source strength", k4, kfree, 1e-14);
        const double mdiff = (4.0 * M::m_p - m_alpha) / m_alpha;
        tb::note("Law IV masses: 4 m_p = %.9e kg ; m_alpha = %.9e kg ; (4 m_p - m_alpha)/m_alpha = %.6e", 4.0 * M::m_p, m_alpha, mdiff);
        tb::check_true("T4", "the Law IV masses of 4 free protons and an alpha differ by 0.6 to 0.8 per cent", mdiff >= 0.6e-2 && mdiff <= 0.8e-2);
    }

    return tb::finish();
}
