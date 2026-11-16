// NP13 blank-slate run 1 (2026-10-10). Registration: NP13_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
// Constitutional grammar: one alpha core + n_d deuterons + n_t tritons, n_t = A - 2Z, n_d = 3Z - A - 2. s = |n_d - n_t| / (n_d + n_t).
// Data: AME2020 mass excess (experimental rows, parsed as in NSEQ05 amended); NUBASE2020 ground-state isotopic abundances (IS=).
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Nuc { int Z, N, A; double me, bea; };
static double spearman(std::vector<double> x, std::vector<double> y) {
    auto rk = [](std::vector<double> v) { size_t n = v.size(); std::vector<size_t> id(n); for (size_t i = 0; i < n; ++i) id[i] = i; std::sort(id.begin(), id.end(), [&](size_t a, size_t b) { return v[a] < v[b]; }); std::vector<double> r(n); size_t i = 0; while (i < n) { size_t j = i; while (j + 1 < n && v[id[j + 1]] == v[id[i]]) ++j; double m = 0.5 * (i + j) + 1; for (size_t k = i; k <= j; ++k) r[id[k]] = m; i = j + 1; } return r; };
    auto a = rk(x), b = rk(y); size_t n = a.size(); double ma = 0, mb = 0; for (size_t i = 0; i < n; ++i) { ma += a[i]; mb += b[i]; } ma /= n; mb /= n; double sab = 0, saa = 0, sbb = 0; for (size_t i = 0; i < n; ++i) { sab += (a[i] - ma) * (b[i] - mb); saa += (a[i] - ma) * (a[i] - ma); sbb += (b[i] - mb) * (b[i] - mb); } return sab / std::sqrt(saa * sbb);
}
static bool grammar(int Z, int A, int& nd, int& nt) { nt = A - 2 * Z; nd = 3 * Z - A - 2; return Z >= 2 && nd >= 0 && nt >= 0; }
static double symm(int nd, int nt) { return nd + nt > 0 ? std::fabs(double(nd - nt)) / double(nd + nt) : 0.0; }

int main() {
    std::printf("NP13 blank-slate run 1 (registered in NP13_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n====================================================================\n\n");
    int fails = 0;
    // ---- AME2020
    std::map<std::pair<int, int>, Nuc> AME; int allRows = 0, expRows = 0; double MEn = 0, MEH = 0;
    { std::ifstream f("Datasets/nuclear/AME2020_mass_excess.txt"); std::string ln; while (std::getline(f, ln)) { if (ln.size() < 60) continue; int Nn, Zz, A; try { Nn = std::stoi(ln.substr(4, 5)); Zz = std::stoi(ln.substr(9, 5)); A = std::stoi(ln.substr(14, 5)); } catch (...) { continue; } if (A != Nn + Zz || A <= 0) continue; ++allRows;
          std::istringstream ss(ln.substr(19)); std::vector<std::string> tk; std::string t; while (ss >> t) tk.push_back(t); int idx = -1; for (size_t i = 1; i < tk.size(); ++i) { const std::string& q = tk[i]; if (!q.empty() && (std::isdigit((unsigned char)q[0]) || (q[0] == '-' && q.size() > 1 && std::isdigit((unsigned char)q[1])))) { idx = (int)i; break; } }
          if (idx < 0 || tk[idx].find('#') != std::string::npos || tk[idx].find('*') != std::string::npos) continue; if (idx + 2 >= (int)tk.size()) continue; double me, bea; try { me = std::stod(tk[idx]); bea = std::stod(tk[idx + 2]); } catch (...) { continue; } ++expRows; AME[{Zz, Nn}] = {Zz, Nn, A, me, bea}; if (Zz == 0 && Nn == 1) MEn = me; if (Zz == 1 && Nn == 0) MEH = me; } }
    auto BEA = [&](int Z, int N) { const Nuc& n = AME.at({Z, N}); return (Z * MEH + N * MEn - n.me) / double(n.A); };
    { bool ok = allRows == 3558 && expRows == 2550 && std::fabs(MEn - 8071.31806) < 1e-5 && std::fabs(MEH - 7288.971064) < 1e-5; std::printf("[V1] AME2020 rows %d, experimental %d ; ME(n) %.5f, ME(1H) %.6f keV -> %s\n", allRows, expRows, MEn, MEH, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { double w = 0; struct Q { int Z, N; } qs[5] = {{1, 1}, {2, 2}, {26, 30}, {28, 34}, {82, 126}}; for (auto& q : qs) if (AME.count({q.Z, q.N})) w = std::max(w, std::fabs(BEA(q.Z, q.N) - AME.at({q.Z, q.N}).bea)); else w = 1e9; bool ok = w < 0.01; std::printf("[V2] computed B/A against the file's binding-energy column for 2H, 4He, 56Fe, 62Ni, 208Pb: worst %.5f keV -> %s\n", w, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // ---- NUBASE abundances
    std::map<std::pair<int, int>, double> AB; std::map<int, double> sumZ; std::map<int, int> cntZ;
    { std::ifstream f("Datasets/nuclear/NUBASE2020.txt"); std::string ln; while (std::getline(f, ln)) { if (ln.size() < 40 || !std::isdigit((unsigned char)ln[0])) continue; int A, Z, iso; try { A = std::stoi(ln.substr(0, 3)); Z = std::stoi(ln.substr(4, 3)); iso = ln[7] - '0'; } catch (...) { continue; } if (iso != 0) continue; size_t p = ln.find("IS="); if (p == std::string::npos) continue; double v; try { v = std::stod(ln.substr(p + 3, 12)); } catch (...) { continue; } AB[{Z, A - Z}] = v; sumZ[Z] += v; ++cntZ[Z]; } }
    { bool ok = AB.count({1, 0}) && AB.count({1, 1}) && std::fabs(AB[{1, 0}] - 99.9855) < 1e-6 && std::fabs(AB[{1, 1}] - 0.0145) < 1e-6; double worst = 0; int badEl = 0; for (auto& kv : sumZ) { double d = std::fabs(kv.second - 100.0); worst = std::max(worst, d); if (d > 0.5) ++badEl; }
      std::printf("[V3] NUBASE ground states with IS=: %zu nuclides in %zu elements ; 1H %.4f, 2H %.4f ; worst |sum - 100| over elements %.4f (elements beyond 0.5: %d) -> %s\n", AB.size(), sumZ.size(), AB[{1, 0}], AB[{1, 1}], worst, badEl, (ok && badEl == 0) ? "met" : "NOT MET"); if (!(ok && badEl == 0)) ++fails; }
    { bool ok = true; for (auto& kv : AME) { int Z = kv.first.first, A = kv.second.A, nd, nt; if (!grammar(Z, A, nd, nt)) continue; if (2 + nd + nt != Z || 2 + nd + 2 * nt != kv.first.second) ok = false; } std::printf("[V4] grammar reconstruction (alpha + n_d d + n_t t = (Z,N)) for every grammar nuclide: %s\n\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    // ---- T1
    std::printf("[T1] The pair\n  prompt's table: Fe-56 5a+6d+6t -> Z = %d, N = %d (stated 26, 30) ; Ni-62 5a+6d+9t -> Z = %d, N = %d (stated 28, 34)\n", 5 * 2 + 6 + 6, 5 * 2 + 6 + 12, 5 * 2 + 6 + 9, 5 * 2 + 6 + 18);
    for (auto zn : {std::make_pair(26, 30), std::make_pair(28, 34)}) { int Z = zn.first, N = zn.second, A = Z + N, nd, nt; grammar(Z, A, nd, nt); std::printf("  constitutional: Z = %d, A = %d : n_d = %d, n_t = %d, triton fraction %.4f, s = %.4f ; B/A = %.4f keV ; abundance within element %.4f %%\n", Z, A, nd, nt, double(nt) / (nd + nt), symm(nd, nt), BEA(Z, N), AB.count({Z, N}) ? AB[{Z, N}] : -1.0); }
    { std::vector<std::pair<double, std::pair<int, int>>> v; for (auto& kv : AME) { if (kv.first.first < 1 || kv.second.A < 2) continue; v.push_back({BEA(kv.first.first, kv.first.second), kv.first}); } std::sort(v.rbegin(), v.rend()); std::printf("  top five by B/A (keV):"); for (int i = 0; i < 5; ++i) std::printf(" Z=%d A=%d %.3f;", v[i].second.first, v[i].second.first + v[i].second.second, v[i].first); std::printf("\n\n"); }
    // ---- T2
    { double w = 0; int n = 0; for (auto& kv : AME) { int Z = kv.first.first, N = kv.first.second, nd, nt; if (!grammar(Z, Z + N, nd, nt) || Z < 3) continue; double s1 = symm(nd, nt), s2 = std::fabs(3.0 * Z - 2.0 * N - 2.0) / (Z - 2.0); w = std::max(w, std::fabs(s1 - s2)); ++n; } std::printf("[T2] s = |3Z - 2N - 2|/(Z - 2): identity over %d grammar nuclides, worst difference %.2e ; zero at N = (3Z - 2)/2 (N/Z -> 1.5)\n\n", n, w); }
    // ---- T3
    std::vector<double> sx, ab, ba; int outside = 0; std::map<int, std::vector<std::pair<int, double>>> byZ; // Z -> (A, abundance)
    for (auto& kv : AB) { int Z = kv.first.first, N = kv.first.second, A = Z + N, nd, nt; if (Z < 2 || Z > 83 || kv.second <= 0) continue; if (!grammar(Z, A, nd, nt)) { ++outside; continue; } if (!AME.count({Z, N})) continue; sx.push_back(symm(nd, nt)); ab.push_back(kv.second); ba.push_back(BEA(Z, N)); byZ[Z].push_back({A, kv.second}); }
    std::printf("[T3] isotopes with abundance, Z = 2..83, inside the grammar: %zu (outside, n_d or n_t < 0: %d)\n  Spearman(s, abundance) = %+.4f ; Spearman(s, B/A) = %+.4f\n", sx.size(), outside, spearman(sx, ab), spearman(sx, ba));
    { int el = 0, hit = 0, heavy = 0, light = 0; double chance = 0, var = 0; for (auto& kv : byZ) { auto& v = kv.second; if (v.size() < 2) continue; ++el; int Z = kv.first; double bestS = 1e9; int bestA = 0, maxAb = 0; double maxv = -1; int hA = 0, lA = 1000; for (auto& p : v) { int nd, nt; grammar(Z, p.first, nd, nt); double s = symm(nd, nt); if (s < bestS - 1e-12) { bestS = s; bestA = p.first; } if (p.second > maxv) { maxv = p.second; maxAb = p.first; } hA = std::max(hA, p.first); lA = std::min(lA, p.first); }
            if (bestA == maxAb) ++hit; if (maxAb == hA) ++heavy; if (maxAb == lA) ++light; double pk = 1.0 / v.size(); chance += pk; var += pk * (1 - pk); }
      std::printf("  elements with >= 2 isotopes: %d ; most abundant = most symmetric (smallest s): %d (chance %.2f +- %.2f) ; most abundant = heaviest: %d ; = lightest: %d\n", el, hit, chance, std::sqrt(var), heavy, light);
      std::printf("  reading 'most abundant = most symmetric': %s\n\n", (hit - chance > 2 * std::sqrt(var)) ? "SUPPORTED (> 2 sigma above chance)" : "NOT supported"); }
    // ---- T4
    { std::map<int, double> sstar; for (auto& kv : byZ) { double best = -1; int bestA = 0; for (auto& p : kv.second) if (p.second > best) { best = p.second; bestA = p.first; } int nd, nt; grammar(kv.first, bestA, nd, nt); sstar[kv.first] = symm(nd, nt); }
      std::printf("[T4] s* (s of the most abundant isotope) at the magic Z, rank among Z-2..Z+2 (1 = smallest s):\n"); for (int Z : {2, 8, 20, 28, 50, 82}) { if (!sstar.count(Z)) { std::printf("  Z = %2d: no data\n", Z); continue; } int r = 1, have = 0; for (int k = -2; k <= 2; ++k) { int u = Z + k; if (!sstar.count(u)) continue; ++have; if (u != Z && sstar[u] < sstar[Z]) ++r; } std::printf("  Z = %2d: s* = %.4f, window values %d, rank %d\n", Z, sstar[Z], have, r); } }
    std::printf("\n[T5] B/A gate (audit correction): OWED, no native B/A model in the prompt (D5)\n");
    return 0;
}
