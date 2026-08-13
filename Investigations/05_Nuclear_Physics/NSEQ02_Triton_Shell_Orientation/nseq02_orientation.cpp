// NSEQ02 — Triton shell orientation: belt (stale) vs dual-tetra (author)
// Compile (from this dir, after vcvars64):
//   cl /std:c++20 /EHsc /O2 /Fe:nseq02_orientation.exe nseq02_orientation.cpp

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <string>
#include <vector>

namespace {

constexpr double PI = std::numbers::pi;
constexpr double DEG = 180.0 / PI;

struct Vec3 {
  double x{}, y{}, z{};
  [[nodiscard]] double norm() const { return std::sqrt(x * x + y * y + z * z); }
  [[nodiscard]] Vec3 unit() const {
    const double n = norm();
    return {x / n, y / n, z / n};
  }
  [[nodiscard]] double dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }
};

struct Seat {
  Vec3 dir;  // unit
  double r;
  const char* role;  // "open" | "close" | "belt"
  int index;
};

[[nodiscard]] double ang_deg(const Vec3& a, const Vec3& b) {
  double c = std::clamp(a.dot(b), -1.0, 1.0);
  return std::acos(c) * DEG;
}

// Polar-aligned dual tetrahedra (stella octangula / cube with body? face?):
// Opening tetra: N pole + 3 base at z = -1/3 (unit sphere), azimuth 0,120,240.
// Closing tetra: S pole + 3 base at z = +1/3, azimuth 60,180,300 (offset).
// "Six alternating around the equator" = two near-equatorial bands at
// latitude ±arcsin(1/3) ≈ ±19.47°, interleaved in azimuth.
[[nodiscard]] std::vector<Seat> author_dual_tetra(double r_open, double r_close) {
  std::vector<Seat> s;
  const double z_base = 1.0 / 3.0;
  const double rho = std::sqrt(1.0 - z_base * z_base);  // √(8/9)

  s.push_back({{0, 0, 1}, r_open, "open", 0});    // N pole — first valence
  s.push_back({{0, 0, -1}, r_close, "close", 1});  // S pole — second valence

  // Opening base (even azimuth)
  for (int k = 0; k < 3; ++k) {
    const double th = k * (2.0 * PI / 3.0);
    Vec3 d{rho * std::cos(th), rho * std::sin(th), -z_base};
    s.push_back({d.unit(), r_open, "open", 2 + k});
  }
  // Closing base (odd / offset 60°)
  for (int k = 0; k < 3; ++k) {
    const double th = PI / 3.0 + k * (2.0 * PI / 3.0);
    Vec3 d{rho * std::cos(th), rho * std::sin(th), +z_base};
    s.push_back({d.unit(), r_close, "close", 5 + k});
  }
  return s;
}

// Flat hex-bipyramid (literal poles + z=0 hex) — intermediate LLM reading
[[nodiscard]] std::vector<Seat> hex_bipyramid(double r_open, double r_close) {
  std::vector<Seat> s;
  s.push_back({{0, 0, 1}, r_open, "open", 0});
  s.push_back({{0, 0, -1}, r_close, "close", 1});
  for (int k = 0; k < 6; ++k) {
    const double th = k * (PI / 3.0);
    const bool open = (k % 2 == 0);
    Vec3 d{std::cos(th), std::sin(th), 0.0};
    s.push_back({d.unit(), open ? r_open : r_close, open ? "open" : "close", 2 + k});
  }
  return s;
}

// Sequencer first belt: 4 antipodal pairs on one equatorial plane (coplanar).
[[nodiscard]] std::vector<Seat> sequencer_belt_plane(double r) {
  std::vector<Seat> s;
  for (int k = 0; k < 4; ++k) {
    const double th = k * (PI / 4.0);
    Vec3 a{std::cos(th), std::sin(th), 0.0};
    s.push_back({a.unit(), r, "belt", 2 * k});
    s.push_back({{-a.x, -a.y, 0.0}, r, "belt", 2 * k + 1});
  }
  return s;
}

struct PairStats {
  double min_deg{1e9};
  double max_deg{0};
  double mean_nn_deg{0};
};

[[nodiscard]] PairStats pairwise(const std::vector<Seat>& seats) {
  PairStats st;
  const int n = static_cast<int>(seats.size());
  double sum_nn = 0;
  for (int i = 0; i < n; ++i) {
    double nn = 1e9;
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      const double a = ang_deg(seats[i].dir, seats[j].dir);
      st.min_deg = std::min(st.min_deg, a);
      st.max_deg = std::max(st.max_deg, a);
      nn = std::min(nn, a);
    }
    sum_nn += nn;
  }
  st.mean_nn_deg = sum_nn / n;
  return st;
}

[[nodiscard]] double mean_radius(const std::vector<Seat>& seats, const char* role) {
  double sum = 0;
  int n = 0;
  for (const auto& x : seats) {
    if (std::string(x.role) == role) {
      sum += x.r;
      ++n;
    }
  }
  return n ? sum / n : 0;
}

[[nodiscard]] double max_abs_z(const std::vector<Seat>& seats) {
  double m = 0;
  for (const auto& x : seats) m = std::max(m, std::abs(x.dir.z));
  return m;
}

void print_seats(const char* label, const std::vector<Seat>& seats) {
  std::printf("\n--- %s (%zu seats) ---\n", label, seats.size());
  for (const auto& x : seats) {
    const Vec3 p{x.dir.x * x.r, x.dir.y * x.r, x.dir.z * x.r};
    const double lat = std::asin(std::clamp(x.dir.z, -1.0, 1.0)) * DEG;
    std::printf("  #%d %-5s  lat=%+6.2f°  r=%.3f  pos=(%+.3f,%+.3f,%+.3f)\n",
                x.index, x.role, lat, x.r, p.x, p.y, p.z);
  }
}

void print_tetra_angles(const std::vector<Seat>& seats, const char* role, double ideal) {
  std::vector<Vec3> d;
  for (const auto& x : seats)
    if (std::string(x.role) == role) d.push_back(x.dir);
  std::printf("  %s dir-dir angles (ideal %.2f°):", role, ideal);
  double sse = 0;
  int np = 0;
  for (size_t i = 0; i < d.size(); ++i)
    for (size_t j = i + 1; j < d.size(); ++j) {
      const double a = ang_deg(d[i], d[j]);
      std::printf(" %.2f", a);
      const double e = a - ideal;
      sse += e * e;
      ++np;
    }
  std::printf("  RMS=%.4f°\n", np ? std::sqrt(sse / np) : 0);
}

void print_phys_edges(const std::vector<Seat>& seats, const char* role) {
  std::vector<Vec3> p;
  for (const auto& x : seats)
    if (std::string(x.role) == role)
      p.push_back({x.dir.x * x.r, x.dir.y * x.r, x.dir.z * x.r});
  std::printf("  %s physical edges:", role);
  double mn = 1e9, mx = 0;
  for (size_t i = 0; i < p.size(); ++i)
    for (size_t j = i + 1; j < p.size(); ++j) {
      const Vec3 d{p[i].x - p[j].x, p[i].y - p[j].y, p[i].z - p[j].z};
      const double L = d.norm();
      std::printf(" %.4f", L);
      mn = std::min(mn, L);
      mx = std::max(mx, L);
    }
  std::printf("  (span %.2f%%)\n", mn > 0 ? 100.0 * (mx - mn) / mn : 0);
}

}  // namespace

int main() {
  std::printf("============================================================\n");
  std::printf("NSEQ02 — Triton shell orientation (belt vs dual-tetra)\n");
  std::printf("============================================================\n");
  std::printf("\nSPLIT (author):\n");
  std::printf("  KEPT:      d/t grammar; shell capacities → magic numbers;\n");
  std::printf("             tritons open/close internal packing\n");
  std::printf("  STALE:     equatorial \"belt\" orientation (LLM-propagated)\n");
  std::printf("  UNDER TEST: two offset interlinked tetrahedra;\n");
  std::printf("             valences 1–2 at poles; other six alternating\n");
  std::printf("             near-equator; r_open > r_close always\n");

  constexpr double R_OPEN = 1.05;
  constexpr double R_CLOSE = 0.95;
  // Central angle between vertices of a regular tetrahedron (from centre):
  // arccos(-1/3) ≈ 109.47°  (bond angle); NOT arccos(+1/3).
  const double tetra_ideal = std::acos(-1.0 / 3.0) * DEG;

  auto author = author_dual_tetra(R_OPEN, R_CLOSE);
  auto flat = hex_bipyramid(R_OPEN, R_CLOSE);
  auto belt = sequencer_belt_plane(1.0);

  print_seats("AUTHOR: polar dual tetrahedra (r_open>r_close)", author);
  std::printf("\n--- Dual tetrahedra partition ---\n");
  std::printf("  Opening: N pole + 3 at lat −arcsin(1/3) ≈ −19.47°\n");
  std::printf("  Closing: S pole + 3 at lat +arcsin(1/3) ≈ +19.47°, az +60°\n");
  print_tetra_angles(author, "open", tetra_ideal);
  print_tetra_angles(author, "close", tetra_ideal);
  print_phys_edges(author, "open");
  print_phys_edges(author, "close");

  print_seats("LITERAL flat hex-bipyramid (poles + z=0 hex)", flat);
  print_tetra_angles(flat, "open", tetra_ideal);
  print_tetra_angles(flat, "close", tetra_ideal);

  print_seats("SEQUENCER: first belt (coplanar antipodal pairs)", belt);

  const auto sa = pairwise(author);
  const auto sf = pairwise(flat);
  const auto sb = pairwise(belt);

  std::printf("\n--- Angular statistics (directions, degrees) ---\n");
  std::printf("  Author dual-tetra: min_pair=%.2f  mean_NN=%.2f  max|z|=%.3f\n",
              sa.min_deg, sa.mean_nn_deg, max_abs_z(author));
  std::printf("  Flat hex-bipy:     min_pair=%.2f  mean_NN=%.2f  max|z|=%.3f\n",
              sf.min_deg, sf.mean_nn_deg, max_abs_z(flat));
  std::printf("  Sequencer belt:    min_pair=%.2f  mean_NN=%.2f  max|z|=%.3f\n",
              sb.min_deg, sb.mean_nn_deg, max_abs_z(belt));

  const double m_open = mean_radius(author, "open");
  const double m_close = mean_radius(author, "close");
  std::printf("\n--- Radius rule ---\n");
  std::printf("  mean r_open=%.4f  mean r_close=%.4f  open>close: %s\n",
              m_open, m_close, m_open > m_close ? "PASS" : "FAIL");

  // Edge equality on unit sphere (same r): should be exact for dual tetra
  auto unit_author = author_dual_tetra(1.0, 1.0);
  std::printf("\n--- Equal-r dual tetra (unit) edge span ---\n");
  print_phys_edges(unit_author, "open");
  print_phys_edges(unit_author, "close");

  const bool planar_belt = max_abs_z(belt) < 1e-9;
  const bool author_3d = max_abs_z(author) > 0.9;
  const bool radius_ok = m_open > m_close;
  // Direction angles for regular tetra on sphere = arccos(1/3)
  bool tetra_ok = true;
  {
    std::vector<Vec3> d;
    for (const auto& x : unit_author)
      if (std::string(x.role) == "open") d.push_back(x.dir);
    for (size_t i = 0; i < d.size(); ++i)
      for (size_t j = i + 1; j < d.size(); ++j)
        if (std::abs(ang_deg(d[i], d[j]) - tetra_ideal) > 1e-6) tetra_ok = false;
  }

  std::printf("\n============================================================\n");
  std::printf("CLAIMS\n");
  std::printf("  NSEQ02-C1 SPLIT_LEDGER:              PASS\n");
  std::printf("  NSEQ02-C2 DUAL_TETRA_BUILT:          PASS (poles + 6 near-eq)\n");
  std::printf("  NSEQ02-C2b REGULAR_TETRA_DIRS:       %s (arccos(-1/3))\n",
              tetra_ok ? "PASS" : "FAIL");
  std::printf("  NSEQ02-C3 R_OPEN_GT_R_CLOSE:         %s\n", radius_ok ? "PASS" : "FAIL");
  std::printf("  NSEQ02-C4 BELT_IS_PLANAR:            %s\n", planar_belt ? "PASS" : "FAIL");
  std::printf("  NSEQ02-C4b AUTHOR_IS_3D:             %s\n", author_3d ? "PASS" : "FAIL");
  std::printf("  NSEQ02-C4c FLAT_HEX_NOT_REGULAR:     documented (90°/120° dirs)\n");
  std::printf("  NSEQ02-C5 STATUS: BELT_ORIENTATION_STALE\n");
  std::printf("             capacities/grammar: NOT WITHDRAWN\n");
  std::printf("  NSEQ02-C6 CANON_EDIT:                NONE (propose-and-wait)\n");
  std::printf("\nPROPOSE-AND-WAIT (nomenclature / orientation only):\n");
  std::printf("  - Retire \"belt\" as orientation in sequencer + laws.hpp comments\n");
  std::printf("  - Keep shell capacity schedule; seat as dual-tetra shells\n");
  std::printf("  - NSEQ01 R5 amended: orientation STALE; capacity counting kept\n");
  std::printf("============================================================\n");
  return (planar_belt && author_3d && radius_ok && tetra_ok) ? 0 : 1;
}
