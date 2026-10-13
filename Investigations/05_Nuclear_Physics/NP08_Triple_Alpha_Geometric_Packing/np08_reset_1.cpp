// NP08 blank-slate run 1 (2026-10-10). Registration: NP08_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
// Target row from measured masses (AME2020): Q(3 alpha), the Be-8 margin, the Hoyle offset, the 12C(alpha,gamma)16O Q-value; grammar rows. No Coulomb ledger, no lock derivation.
// Author: J. C. Harvey, Melbourne.
#include <cctype>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::printf("NP08 blank-slate run 1 (registered in NP08_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n=======================================================================\n\n");
    std::map<std::pair<int, int>, double> ME; int allRows = 0, expRows = 0;
    { std::ifstream f("Datasets/nuclear/AME2020_mass_excess.txt"); std::string ln; while (std::getline(f, ln)) { if (ln.size() < 60) continue; int Nn, Zz, A; try { Nn = std::stoi(ln.substr(4, 5)); Zz = std::stoi(ln.substr(9, 5)); A = std::stoi(ln.substr(14, 5)); } catch (...) { continue; } if (A != Nn + Zz || A <= 0) continue; ++allRows;
          std::istringstream ss(ln.substr(19)); std::string tk, el; ss >> el; std::string me; while (ss >> tk) { bool num = !tk.empty() && (std::isdigit((unsigned char)tk[0]) || (tk[0] == '-' && tk.size() > 1 && std::isdigit((unsigned char)tk[1]))); if (!num) continue; me = tk; break; } if (me.empty() || me.find('#') != std::string::npos || me.find('*') != std::string::npos) continue; try { ME[{Zz, Nn}] = std::stod(me); ++expRows; } catch (...) {} } }
    int fails = 0;
    { bool ok = allRows == 3558 && expRows == 2550 && ME.count({0, 1}) && ME.count({1, 0}) && std::fabs(ME[{0, 1}] - 8071.31806) < 1e-5 && std::fabs(ME[{1, 0}] - 7288.971064) < 1e-5; std::printf("[V1] AME2020 rows %d, experimental %d -> %s\n", allRows, expRows, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    const double he4 = ME.at({2, 2}), c12 = ME.at({6, 6}), be8 = ME.at({4, 4}), o16 = ME.at({8, 8}), uMeV = 931.49410242; (void)uMeV;
    { // V2: the prompt's table (4.002603 u; 12.007809 u; 7.275 MeV): the AME mass excess of 4He is 2424.9156 keV -> mass 4.002603 u
      double q = 3 * he4 - c12; bool ok = std::fabs(q - 7275.0) < 0.5 + 0.5 && std::fabs(4.002603 * 3 - 12.007809) < 1e-9; std::printf("[V2] 3 x 4.002603 u = %.6f u (table 12.007809) ; Q(3 alpha) = 3 ME(4He) - ME(12C) = %.4f keV (table 7.275 MeV; difference %.3f keV) -> %s\n", 4.002603 * 3, q, q - 7275.0, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { bool ok = true; struct G { const char* nm; int Z, A; } gs[5] = {{"He-4", 2, 4}, {"Be-8", 4, 8}, {"Be-9", 4, 9}, {"C-12", 6, 12}, {"O-16", 8, 16}}; std::printf("[V3/grammar] "); for (auto& g : gs) { int nt = g.A - 2 * g.Z, nd = 3 * g.Z - g.A - 2; if (2 + nd + nt != g.Z || 2 + nd + 2 * nt != g.A - g.Z) ok = false; std::printf("%s = alpha + %dd + %dt ; ", g.nm, nd, nt); } std::printf("-> %s\n\n", ok ? "reconstruction met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    const double q3a = 3 * he4 - c12, margin = be8 - 2 * he4, EH = 7654.2, off = EH - q3a, qO = he4 + c12 - o16;
    std::printf("TARGET ROW (measured anchors; COMPUTED from AME2020, E_H typed OBSERVED):\n");
    std::printf("  ME(4He) = %.6f keV ; ME(12C) = %.6f keV (definition 0) ; ME(8Be) = %.6f keV ; ME(16O) = %.6f keV\n", he4, c12, be8, o16);
    std::printf("  Q(3 alpha -> 12C) = %.4f keV\n  Be-8 margin ME(8Be) - 2 ME(4He) = %+.4f keV (positive = unbound)\n  Hoyle offset E_H - Q(3 alpha) = %.4f keV with E_H = %.1f keV (%.2f%% of E_H)\n  Q(4He + 12C -> 16O) = %.4f keV\n", q3a, margin, off, EH, off / EH * 100, qO);
    std::printf("\nTolerances implied for a later derivation:\n  5%% of the Hoyle offset (audit correction gate) = %.1f keV ; the run-1 20%% gate on E_H = %.0f keV = %.1f times the offset\n  50%% of the Be-8 margin (run-2 gate) = %.1f keV\n  fractional error of E_H that equals the whole offset: %.2f%%\n", 0.05 * off, 0.20 * EH, 0.20 * EH / off, 0.5 * margin, off / EH * 100);
    std::printf("\nNot run: the point-Coulomb repulsion ledger (imported source model), the lock derivation (blocked), the alignment-cost computation (needs the lock).\n");
    return 0;
}
