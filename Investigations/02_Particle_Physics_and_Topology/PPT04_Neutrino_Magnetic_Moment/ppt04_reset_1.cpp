// PPT04 blank-slate run 1 (2026-10-10). Registration: PPT04_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
// The topology table is a CLASSIFICATION (no moment is computed); the only literals are the labelled external limits and the SM coefficient (OBSERVED, verified by search 2026-10-10).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;

int main() {
    std::printf("PPT04 blank-slate run 1 (registered in PPT04_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n=======================================================================\n\n");
    std::printf("Topology table (CLASSIFICATION; no moment computed; D1, D5):\n  e-  W = %d  response class: non-zero (circulating)\n  p   W = %d  response class: non-zero (circulating)\n  nu  W = 0   response class: none (open winding; carried as a comment in laws.hpp, no constant)\n\n", law_VI::winding::W_electron, law_VI::winding::W_proton);
    // OBSERVED block (external, in Bohr magnetons, 90% CL)
    const double coef = 3.2e-19, m_nu_eV = 0.06, sm = coef * m_nu_eV;
    struct L { const char* nm; double v; } lim[5] = {{"Borexino Phase-II", 2.8e-11}, {"GEMMA (3-yr, no ionisation mechanism)", 3.2e-11}, {"GEMMA (global-analysis citation)", 2.9e-11}, {"XENONnT (2025 reanalysis, flavour-universal)", 7.2e-12}, {"XENONnT (collaboration 2022, unconfirmed)", 6.3e-12}};
    std::printf("SM column (OBSERVED-TARGET): mu_nu = 3.2e-19 (m_nu/eV) mu_B at m_nu = %.2f eV = %.3e mu_B\n\nDiscriminant against the current upper limits:\n", m_nu_eV, sm);
    double mnGap = 1e99, mxGap = 0; for (auto& l : lim) { double gap = l.v / sm; mnGap = std::fmin(mnGap, gap); mxGap = std::fmax(mxGap, gap); std::printf("  %-48s limit %.2e mu_B : limit / SM = %.3e (%.2f orders)\n", l.nm, l.v, gap, std::log10(gap)); }
    std::printf("\nGap range %.2f to %.2f orders; threshold for 'untestable now' (registered): > 6 orders -> %s\n", std::log10(mnGap), std::log10(mxGap), std::log10(mnGap) > 6 ? "UNTESTABLE NOW" : "testable");
    std::printf("Sensitivity improvement needed to reach the SM value from the best limit: x %.2e\n", mnGap);
    std::printf("One-sided statement: an observed moment at or above the limit (~1e-11 mu_B) would exclude both mu_nu = 0 (W = 0 reading) and the minimal-extension value 1.9e-20 mu_B (shared exclusion class); a null result is consistent with both.\n");
    return 0;
}
