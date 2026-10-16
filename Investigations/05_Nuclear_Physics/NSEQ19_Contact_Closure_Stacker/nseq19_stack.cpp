// NSEQ19 contact-closure stacker. Registration: NSEQ19_REGISTRATION_2026-10-15.md (written before this file existed).
// Build (MSVC): cl /std:c++20 /EHsc /O2 /utf-8 /nologo nseq19_stack.cpp ; run: nseq19_stack nseq19_nuclides.txt out.txt [seeds] [filterTag]
// Units of R_p; every unit a hard sphere of radius 1. Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

struct V { double x, y, z; };
static inline V operator+(V a, V b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
static inline V operator-(V a, V b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
static inline V operator*(V a, double s) { return {a.x * s, a.y * s, a.z * s}; }
static inline double dot(V a, V b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline double len(V a) { return std::sqrt(dot(a, a)); }
static inline V unitv(V a) { double l = len(a); return l > 0 ? a * (1.0 / l) : V{0, 0, 1}; }
struct M3 { double m[3][3]; };
static M3 ident() { M3 r{}; for (int i = 0; i < 3; i++) r.m[i][i] = 1; return r; }
static V mul(const M3& a, V v) { return {a.m[0][0] * v.x + a.m[0][1] * v.y + a.m[0][2] * v.z, a.m[1][0] * v.x + a.m[1][1] * v.y + a.m[1][2] * v.z, a.m[2][0] * v.x + a.m[2][1] * v.y + a.m[2][2] * v.z}; }
static M3 mul(const M3& a, const M3& b) { M3 r{}; for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) r.m[i][j] += a.m[i][k] * b.m[k][j]; return r; }
static M3 axisAngle(V ax, double th) {
  ax = unitv(ax); double c = std::cos(th), s = std::sin(th), t = 1 - c; M3 r;
  r.m[0][0] = t * ax.x * ax.x + c; r.m[0][1] = t * ax.x * ax.y - s * ax.z; r.m[0][2] = t * ax.x * ax.z + s * ax.y;
  r.m[1][0] = t * ax.x * ax.y + s * ax.z; r.m[1][1] = t * ax.y * ax.y + c; r.m[1][2] = t * ax.y * ax.z - s * ax.x;
  r.m[2][0] = t * ax.x * ax.z - s * ax.y; r.m[2][1] = t * ax.y * ax.z + s * ax.x; r.m[2][2] = t * ax.z * ax.z + c; return r;
}

static const double TAU_C = 0.01;             // contact tolerance tau
static const double OVER = 2.0 - 1e-9;        // minimum centre distance
static const double CONT = 2.0 + TAU_C;       // contact / like-exclusion distance
static const int SLOTS = 3;
static bool g_likeFree = false; // CONTROL ONLY: like pairs may touch (registered rule: false)
static long g_closureMult = 1; // closureMult: multiplier on the closure relaxation moves (registered value 1 = 300 N)

struct Mod {
  int kind;                 // 0 alpha, 1 deuteron, 2 triton
  std::vector<V> local; std::vector<int> types; std::vector<int> idx; std::vector<int> internalDeg;
  V c{0, 0, 0}; M3 R = ident(); V seat{0, 0, 1};
  bool fixedCore = false;
};

struct State {
  std::vector<V> pos; std::vector<int> type; std::vector<int> mod; std::vector<Mod> mods;
  int placedUnits() const { return (int)pos.size(); }
};

static Mod makeModule(int kind) {
  Mod m; m.kind = kind;
  if (kind == 0) { double r = std::sqrt(2.0); m.local = {{r, 0, 0}, {0, r, 0}, {-r, 0, 0}, {0, -r, 0}}; m.types = {0, 1, 0, 1}; m.fixedCore = true; }
  else if (kind == 1) { m.local = {{-1, 0, 0}, {1, 0, 0}}; m.types = {0, 1}; }
  else { m.local = {{-2, 0, 0}, {0, 0, 0}, {2, 0, 0}}; m.types = {1, 0, 1}; }
  int n = (int)m.local.size(); m.internalDeg.assign(n, 0);
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j && m.types[i] != m.types[j]) {
    double d = len(m.local[i] - m.local[j]); if (d < CONT) m.internalDeg[i]++;
  }
  return m;
}

static std::vector<V> worldPos(const Mod& m, V c, const M3& R) { std::vector<V> w; for (auto& l : m.local) w.push_back(c + mul(R, l)); return w; }

// validity of module mi at pose (c,R) against all other placed units. seatCos < -1 disables the seat cone. needContact: require >= 1 external contact.
static bool validPose(const State& S, int mi, V c, const M3& R, V centroid, double seatCos, bool needContact) {
  const Mod& m = S.mods[mi]; auto w = worldPos(m, c, R); int n = (int)w.size();
  if (seatCos > -1.5 && dot(unitv(c - centroid), m.seat) < seatCos) return false;
  std::vector<int> touchedUnit; std::vector<int> touchCount;           // external units touched by this module and how many times
  int ext = 0;
  for (int k = 0; k < n; k++) {
    int cnt = 0;
    for (int j = 0; j < (int)S.pos.size(); j++) {
      if (S.mod[j] == mi) continue;
      V d = w[k] - S.pos[j]; double d2 = dot(d, d);
      if (d2 >= CONT * CONT) continue;
      if (d2 < OVER * OVER) return false;
      if (S.type[j] == m.types[k]) { if (g_likeFree) continue; return false; }  // like contact or like overlap (control: ignored)
      cnt++; ext++;
      auto it = std::find(touchedUnit.begin(), touchedUnit.end(), j);
      if (it == touchedUnit.end()) { touchedUnit.push_back(j); touchCount.push_back(1); } else touchCount[it - touchedUnit.begin()]++;
    }
    if (m.internalDeg[k] + cnt > SLOTS) return false;
  }
  for (size_t t = 0; t < touchedUnit.size(); t++) {
    int j = touchedUnit[t], deg = 0;
    for (int u = 0; u < (int)S.pos.size(); u++) {
      if (u == j || S.mod[u] == mi) continue;
      if (S.type[u] == S.type[j]) continue;
      V d = S.pos[j] - S.pos[u]; if (dot(d, d) < CONT * CONT) deg++;
    }
    if (deg + touchCount[t] > SLOTS) return false;
  }
  if (needContact && ext == 0) return false;
  return true;
}

static V centroidOf(const State& S) { V c{0, 0, 0}; for (auto& p : S.pos) c = c + p; return S.pos.empty() ? c : c * (1.0 / S.pos.size()); }

static void commit(State& S, int mi, V c, const M3& R) {
  Mod& m = S.mods[mi]; m.c = c; m.R = R; auto w = worldPos(m, c, R);
  for (size_t k = 0; k < w.size(); k++) S.pos[m.idx[k]] = w[k];
}

static double modEnergy(const Mod& m, V c, const M3& R, V centroid) { double e = 0; for (auto& l : m.local) { V p = c + mul(R, l) - centroid; e += dot(p, p); } return e; }

struct Rng { std::mt19937_64 g; double u() { return std::uniform_real_distribution<double>(0, 1)(g); } double s() { return 2 * u() - 1; }
  V ball() { while (true) { V v{s(), s(), s()}; if (dot(v, v) <= 1) return v; } }
  V sphere() { while (true) { V v{s(), s(), s()}; double l = dot(v, v); if (l > 1e-6 && l <= 1) return v * (1.0 / std::sqrt(l)); } }
  M3 randRot() { return axisAngle(sphere(), u() * 6.283185307179586); } };

// downhill rigid-body relaxation of the listed modules; returns accepted moves
static long relax(State& S, const std::vector<int>& which, long moves, Rng& rg, double seatCos, bool needContact, V centroid, double step0 = 0.15) {
  double sT = step0, sR = step0; long acc = 0, win = 0, winAcc = 0;
  for (long it = 0; it < moves; it++) {
    int mi = which[(size_t)(rg.u() * which.size()) % which.size()];
    Mod& m = S.mods[mi];
    V dc = rg.ball() * sT; M3 R2 = mul(axisAngle(rg.sphere(), rg.s() * sR), m.R); V c2 = m.c + dc;
    win++;
    if (modEnergy(m, c2, R2, centroid) <= modEnergy(m, m.c, m.R, centroid) + 1e-12 && validPose(S, mi, c2, R2, centroid, seatCos, needContact)) { commit(S, mi, c2, R2); acc++; winAcc++; }
    if (win == 200) { double r = (double)winAcc / win; if (r < 0.05) { sT = std::max(sT * 0.5, 1e-4); sR = std::max(sR * 0.5, 1e-4); } else if (r > 0.3) { sT = std::min(sT * 1.5, step0); sR = std::min(sR * 1.5, step0); } win = winAcc = 0; }
  }
  return acc;
}

static double extentOf(const State& S, double& rms) {
  V c = centroidOf(S); double mx = 0, s2 = 0;
  for (auto& p : S.pos) { double r = len(p - c); mx = std::max(mx, r); s2 += r * r; }
  rms = std::sqrt(s2 / std::max<size_t>(1, S.pos.size())); return mx + 1.0;
}

// independent checker written separately from validPose
struct Check { bool ok; std::string why; int contacts; int maxDeg; int n3; bool connected; };
static Check checkAll(const State& S) {
  int n = (int)S.pos.size(); std::vector<std::vector<int>> adj(n); Check c{true, "", 0, 0, 0, false};
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    double d = std::sqrt((S.pos[i].x - S.pos[j].x) * (S.pos[i].x - S.pos[j].x) + (S.pos[i].y - S.pos[j].y) * (S.pos[i].y - S.pos[j].y) + (S.pos[i].z - S.pos[j].z) * (S.pos[i].z - S.pos[j].z));
    if (d < 2.0 - 1e-6) { c.ok = false; c.why = "overlap"; }
    if (!g_likeFree && S.type[i] == S.type[j] && d < 2.0 + TAU_C - 1e-9) { c.ok = false; c.why = "like contact"; }
    if (S.type[i] != S.type[j] && d < 2.0 + TAU_C) { adj[i].push_back(j); adj[j].push_back(i); c.contacts++; }
  }
  for (int i = 0; i < n; i++) { c.maxDeg = std::max(c.maxDeg, (int)adj[i].size()); if (adj[i].size() == 3) c.n3++; if ((int)adj[i].size() > SLOTS) { c.ok = false; c.why = "degree"; } }
  std::vector<char> seen(n, 0); std::vector<int> st; if (n) { st.push_back(0); seen[0] = 1; }
  int cnt = 0; while (!st.empty()) { int u = st.back(); st.pop_back(); cnt++; for (int v : adj[u]) if (!seen[v]) { seen[v] = 1; st.push_back(v); } }
  c.connected = (cnt == n); if (!c.connected) { c.ok = false; c.why = "disconnected"; }
  return c;
}

struct ModSpec { int kind; V dir; int shell; };
struct ShellSpec { std::string label; char sp; bool full; int occ; };
struct Nuc { int Z, A, nd, nt; std::string tags; bool refused = false; std::vector<ShellSpec> shells; std::vector<ModSpec> mods; };

static void addModule(State& S, const Mod& proto, V centroid) { (void)centroid; }

static bool build(const Nuc& N, unsigned long long seed, State& S, std::string& failNote, std::vector<std::pair<std::string, double>>& closureLog, double seatCos, int K, long localMoves) {
  Rng rg; rg.g.seed(seed);
  S = State(); S.mods.push_back(makeModule(0));
  { Mod& a = S.mods[0]; a.idx.clear(); for (size_t k = 0; k < a.local.size(); k++) { a.idx.push_back((int)S.pos.size()); S.pos.push_back(a.c + mul(a.R, a.local[k])); S.type.push_back(a.types[k]); S.mod.push_back(0); } }
  size_t mi = 0, shellStart = 0; double rms;
  for (size_t si = 0; si < N.shells.size(); si++) {
    for (int q = 0; q < N.shells[si].occ; q++, mi++) {
      const ModSpec& ms = N.mods[mi];
      Mod proto = makeModule(ms.kind); proto.seat = unitv(ms.dir);
      V centroid = centroidOf(S); double Rmax = 0; for (auto& p : S.pos) Rmax = std::max(Rmax, len(p - centroid));
      bool have = false; double bestE = 1e300; V bestC{}; M3 bestR = ident();
      for (int r = 0; r < K; r++) {
        // add module temporarily at a far pose
        int id = (int)S.mods.size(); S.mods.push_back(proto); Mod& m = S.mods[id]; m.idx.clear();
        M3 R = rg.randRot(); V dirv = proto.seat; double dist = Rmax + 6.0; V c = centroid + dirv * dist;
        for (size_t k = 0; k < m.local.size(); k++) { m.idx.push_back((int)S.pos.size()); S.pos.push_back(c + mul(R, m.local[k])); S.type.push_back(m.types[k]); S.mod.push_back(id); }
        // fall along the seat line
        double lastOk = dist;
        while (dist > 0.5) { double nd = dist - 0.05; V c2 = centroid + dirv * nd; if (!validPose(S, id, c2, R, centroid, seatCos, false)) break; dist = nd; lastOk = nd; }
        c = centroid + dirv * lastOk; commit(S, id, c, R);
        // local relaxation, contact required
        bool contact = validPose(S, id, S.mods[id].c, S.mods[id].R, centroid, seatCos, true);
        std::vector<int> only{id};
        relax(S, only, localMoves, rg, seatCos, false, centroid);
        contact = validPose(S, id, S.mods[id].c, S.mods[id].R, centroid, seatCos, true);
        if (contact) { double e = modEnergy(S.mods[id], S.mods[id].c, S.mods[id].R, centroid); if (e < bestE) { bestE = e; bestC = S.mods[id].c; bestR = S.mods[id].R; have = true; } }
        // remove temp module
        for (size_t k = 0; k < m.local.size(); k++) { S.pos.pop_back(); S.type.pop_back(); S.mod.pop_back(); }
        S.mods.pop_back();
      }
      if (!have) { std::ostringstream o; o << "no valid contact pose for module " << mi + 1 << " (" << N.shells[si].label << ")"; failNote = o.str(); return false; }
      int id = (int)S.mods.size(); S.mods.push_back(proto); Mod& m = S.mods[id]; m.idx.clear();
      for (size_t k = 0; k < m.local.size(); k++) { m.idx.push_back((int)S.pos.size()); S.pos.push_back(bestC + mul(bestR, m.local[k])); S.type.push_back(m.types[k]); S.mod.push_back(id); }
      commit(S, id, bestC, bestR);
    }
    double e = extentOf(S, rms);
    bool closed = N.shells[si].full;
    if (closed) {
      std::vector<int> all; for (int i = 0; i < (int)S.mods.size(); i++) all.push_back(i);
      long moves = 300L * g_closureMult * (long)S.pos.size(); V cen = centroidOf(S);
      double before = e;
      relax(S, all, moves, rg, -2.0, false, cen);
      V c2 = centroidOf(S); for (int i = 0; i < (int)S.mods.size(); i++) { V cc = S.mods[i].c - c2; commit(S, i, cc, S.mods[i].R); }
      double after = extentOf(S, rms);
      closureLog.push_back({N.shells[si].label, after});
      (void)before;
    }
    shellStart = mi;
  }
  (void)shellStart;
  return true;
}

int main(int argc, char** argv) {
  if (argc < 3) { std::cerr << "usage: nseq19_stack nuclides.txt out.txt [seeds] [tagFilter] [seatConeCos] [K] [localMoves]\n"; return 1; }
  int seeds = argc > 3 ? std::atoi(argv[3]) : 1; std::string tag = argc > 4 ? argv[4] : ""; double seatCos = argc > 5 ? std::atof(argv[5]) : 0.0;
  int K = argc > 6 ? std::atoi(argv[6]) : 24; long localMoves = argc > 7 ? std::atol(argv[7]) : 6000; unsigned long long seedOffset = argc > 8 ? std::strtoull(argv[8], nullptr, 10) : 0ULL; g_closureMult = argc > 9 ? std::atol(argv[9]) : 1L; g_likeFree = (argc > 10 && std::atoi(argv[10]) == 1);
  std::ifstream in(argv[1]); std::ofstream out(argv[2]); std::string line; std::vector<Nuc> nucs; Nuc cur; bool open = false;
  while (std::getline(in, line)) {
    std::istringstream ss(line); std::string w; ss >> w;
    if (w == "NUC") { cur = Nuc(); open = true; ss >> cur.Z >> cur.A; std::string x; ss >> x; if (x == "REFUSED") cur.refused = true; else { cur.nd = std::stoi(x); ss >> cur.nt >> cur.tags; } }
    else if (w == "SHELL") { ShellSpec s; std::string sp; int full; ss >> s.label >> sp >> full >> s.occ; s.sp = sp[0]; s.full = full; cur.shells.push_back(s); }
    else if (w == "MOD") { std::string sp; V d; ss >> sp >> d.x >> d.y >> d.z; cur.mods.push_back({sp == "t" ? 2 : 1, d, (int)cur.shells.size() - 1}); }
    else if (w == "END" && open) { nucs.push_back(cur); open = false; }
  }
  out << "Z A nd nt tags seedsTried seedOK ok N E_ext rms closePackE contacts meanDeg n3 maxDeg connected seconds closures note\n";
  int total = 0, okc = 0;
  for (auto& N : nucs) {
    if (N.refused) continue; if (!tag.empty() && N.tags.find(tag) == std::string::npos) continue;
    if (N.A < 4) { out << N.Z << " " << N.A << " " << N.nd << " " << N.nt << " " << N.tags << " 0 0 TRIVIAL " << N.A << " - - - - - - - - 0 - -\n"; continue; }
    auto t0 = std::chrono::steady_clock::now(); total++;
    bool ok = false; int usedSeed = -1; State S; std::string note; std::vector<std::pair<std::string, double>> clog; Check ck{};
    for (int s = 0; s < seeds && !ok; s++) {
      State T; std::string fn; std::vector<std::pair<std::string, double>> cl;
      bool built = build(N, 20261015ULL + 1000ULL * N.A + 17ULL * N.Z + s + 100000ULL * seedOffset, T, fn, cl, seatCos, K, localMoves);
      if (!built) { note = fn; continue; }
      Check c = checkAll(T);
      if (!c.ok) { note = "checker: " + c.why; continue; }
      ok = true; usedSeed = s; S = T; clog = cl; ck = c; note = "-";
    }
    double secs = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    if (ok) { okc++; double rms; double E = extentOf(S, rms); double cp = std::cbrt(N.A / (3.14159265358979 / std::sqrt(18.0))) + 1.0;
      std::ostringstream cs; for (auto& p : clog) cs << p.first << "=" << p.second << ";";
      out << N.Z << " " << N.A << " " << N.nd << " " << N.nt << " " << N.tags << " " << seeds << " " << usedSeed << " OK " << S.pos.size() << " " << E << " " << rms << " " << cp << " " << ck.contacts << " " << (2.0 * ck.contacts / S.pos.size()) << " " << ck.n3 << " " << ck.maxDeg << " " << ck.connected << " " << secs << " " << (cs.str().empty() ? "-" : cs.str()) << " -\n"; }
    else out << N.Z << " " << N.A << " " << N.nd << " " << N.nt << " " << N.tags << " " << seeds << " -1 FAIL " << 0 << " - - - - - - - - " << secs << " - " << note << "\n";
    out.flush(); std::cerr << N.Z << "-" << N.A << (ok ? " ok " : " FAIL ") << secs << "s\n";
  }
  std::cerr << "packed " << okc << " of " << total << "\n";
  return 0;
}
