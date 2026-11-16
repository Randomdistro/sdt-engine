// Chapter 27 — fine and hyperfine structure: worked-example instrument.
// Pre-registration: Textbook/validation/ch27_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>

int main() {
    namespace M = sdt::laws::measured;
    namespace A = sdt::laws::atomic;
    tb::validate_helpers();
    const double alpha = M::alpha, Ry = M::Ry_eV;

    tb::heading("V1 arithmetic of the comparison formula");
    tb::check("V1", "Ry alpha^2/16 = 4.5283e-5 eV (corrected known answer)", Ry * alpha * alpha / 16.0, 4.5283e-5, 1e-4);

    tb::heading("T1 the engine's fine_structure_eV is a scale");
    {
        double w = 0.0;
        for (int Z = 1; Z <= 5; ++Z)
            for (int n = 1; n <= 6; ++n) w = std::fmax(w, std::fabs(A::fine_structure_eV(Z, n) / (Ry * alpha * alpha * std::pow(double(Z), 4) / std::pow(double(n), 3)) - 1.0));
        tb::check("T1", "fine_structure_eV = Ry alpha^2 Z^4/n^3, worst relative", w, 0.0, 1e-14, false);
        tb::note("fine_structure_eV(1,2) = %.4e eV", A::fine_structure_eV(1, 2));
    }

    tb::heading("T2 ratio to the l-dependent comparison splitting");
    {
        double w = 0.0;
        for (int Z = 1; Z <= 5; ++Z)
            for (int l = 1; l <= 3; ++l)
                for (int n = l + 1; n <= 8; ++n) {
                    const double comp = Ry * alpha * alpha * std::pow(double(Z), 4) / (std::pow(double(n), 3) * l * (l + 1));
                    w = std::fmax(w, std::fabs(A::fine_structure_eV(Z, n) / comp / (l * (l + 1.0)) - 1.0));
                }
        tb::check("T2", "engine scale / comparison splitting = l(l+1), worst relative", w, 0.0, 1e-14, false);
        tb::note("n=2 P pair: engine scale %.4e eV ; comparison splitting %.4e eV ; ratio %.6f", A::fine_structure_eV(1, 2), Ry * alpha * alpha / 16.0, A::fine_structure_eV(1, 2) / (Ry * alpha * alpha / 16.0));
    }

    tb::heading("T3 separation of orders (hydrogen, n = 1)");
    {
        const double fine = alpha * alpha, hyper = alpha * alpha * M::m_e / M::m_p, size = std::pow(M::R_p / M::a_0, 2);
        tb::note("orders relative to the leading ladder: fine %.3e ; hyperfine order %.3e ; finite size %.3e", fine, hyper, size);
        tb::note("energies (eV) with Ry = %.6f: fine %.3e ; hyperfine order %.3e ; finite size %.3e", Ry, Ry * fine, Ry * hyper, Ry * size);
        tb::check_true("T3", "leading/fine and fine/hyperfine ratios each exceed 1e3", (1.0 / fine > 1e3) && (fine / hyper > 1e3));
        tb::note("RECORDED REJECTION (run 1 criterion kept): hyperfine/finite-size ratio = %.1f, not above 1e3 ; no ordering claimed between them", hyper / size);
        tb::check_true("T3", "the hyperfine/finite-size ratio is recorded as below 1e3 (registered rejection of the 1e3 separation)", hyper / size < 1e3);
        tb::note("beta^2 = (Z alpha/n)^2: (1,1) %.3e ; (1,2) %.3e ; (30,1) %.3e", std::pow(alpha, 2), std::pow(alpha / 2, 2), std::pow(30 * alpha, 2));
    }

    return tb::finish();
}
