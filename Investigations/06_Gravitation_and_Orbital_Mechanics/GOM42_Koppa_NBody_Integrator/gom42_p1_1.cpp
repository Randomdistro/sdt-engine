// GOM42 P1 (2026-10-14): Sun-Jupiter-Saturn with native kappa inputs; the long-period (great-inequality) term in the osculating mean longitudes.
// Registration: GOM42_P1_REGISTRATION_2026-10-14.md sections 1-5 (written before this file existed). Sources: Datasets/solar_system/GOM42_P1_SOURCES_2026-10-14.md.
// Integrator: velocity Verlet as in gom42_reset_1.cpp (a_i = c^2 sum k_j (r_j - r_i)/r^3).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <vector>
using V = std::array<double, 3>;
namespace M = sdt::laws::measured;
static const double PI_ = 3.14159265358979323846, DEG = PI_ / 180.0, AU = 149597870700.0, DAY = 86400.0, YR = 365.25 * 86400.0;
struct Body { double k; V r, v; };
static V sub(V a, V b) { return {a[0] - b[0], a[1] - b[1], a[2] - b[2]}; }
static double dot(V a, V b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
static V cross(V a, V b) { return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]}; }
static double nrm(V a) { return std::sqrt(dot(a, a)); }
static void accel(const std::vector<Body>& B, double c2, std::vector<V>& a) {
    a.assign(B.size(), V{0, 0, 0});
    for (size_t i = 0; i < B.size(); ++i) for (size_t j = i + 1; j < B.size(); ++j) { V d = sub(B[j].r, B[i].r); double r = nrm(d), s = c2 / (r * r * r); for (int q = 0; q < 3; ++q) { a[i][q] += s * B[j].k * d[q]; a[j][q] -= s * B[i].k * d[q]; } } }
static void step(std::vector<Body>& B, double dt, double c2, std::vector<V>& a) {
    for (size_t i = 0; i < B.size(); ++i) for (int q = 0; q < 3; ++q) { B[i].v[q] += 0.5 * dt * a[i][q]; B[i].r[q] += dt * B[i].v[q]; }
    accel(B, c2, a); for (size_t i = 0; i < B.size(); ++i) for (int q = 0; q < 3; ++q) B[i].v[q] += 0.5 * dt * a[i][q]; }
// Kepler: elements -> state (heliocentric)
struct El { double a, e, I, Om, w, M; };
static double solveE(double M, double e) { M = std::fmod(M, 2 * PI_); if (M < 0) M += 2 * PI_; double E = M + e * std::sin(M); for (int i = 0; i < 100; ++i) { double d = (E - e * std::sin(E) - M) / (1 - e * std::cos(E)); E -= d; if (std::fabs(d) < 1e-15) break; } return E; }
static void toState(const El& el, double mu, V& r, V& v) {
    double E = solveE(el.M, el.e), n = std::sqrt(mu / (el.a * el.a * el.a)), b = std::sqrt(1 - el.e * el.e);
    double x = el.a * (std::cos(E) - el.e), y = el.a * b * std::sin(E), den = 1 - el.e * std::cos(E), vx = -n * el.a * std::sin(E) / den, vy = n * el.a * b * std::cos(E) / den;
    double cO = std::cos(el.Om), sO = std::sin(el.Om), ci = std::cos(el.I), si = std::sin(el.I), cw = std::cos(el.w), sw = std::sin(el.w);
    auto rot = [&](double px, double py) { V o; o[0] = (cO * cw - sO * sw * ci) * px + (-cO * sw - sO * cw * ci) * py; o[1] = (sO * cw + cO * sw * ci) * px + (-sO * sw + cO * cw * ci) * py; o[2] = (sw * si) * px + (cw * si) * py; return o; };
    r = rot(x, y); v = rot(vx, vy); }
static El toEl(V r, V v, double mu) {
    El el; double rn = nrm(r); V h = cross(r, v); double hn = nrm(h); double en = 0.5 * dot(v, v) - mu / rn; el.a = -mu / (2 * en);
    V ev = sub({dot(v, v) * r[0] / mu - dot(r, v) * v[0] / mu, dot(v, v) * r[1] / mu - dot(r, v) * v[1] / mu, dot(v, v) * r[2] / mu - dot(r, v) * v[2] / mu}, {r[0] / rn, r[1] / rn, r[2] / rn}); el.e = nrm(ev);
    el.I = std::acos(h[2] / hn); V nv = {-h[1], h[0], 0}; double nn = nrm(nv); el.Om = std::atan2(nv[1], nv[0]); if (el.Om < 0) el.Om += 2 * PI_;
    double cw = dot(nv, ev) / (nn * el.e); cw = std::max(-1.0, std::min(1.0, cw)); el.w = std::acos(cw); if (ev[2] < 0) el.w = 2 * PI_ - el.w;
    double cn = dot(ev, r) / (el.e * rn); cn = std::max(-1.0, std::min(1.0, cn)); double nu = std::acos(cn); if (dot(r, v) < 0) nu = 2 * PI_ - nu;
    double E = 2 * std::atan2(std::sqrt(1 - el.e) * std::sin(nu / 2), std::sqrt(1 + el.e) * std::cos(nu / 2)); el.M = E - el.e * std::sin(E); return el; }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); return v[v.size() / 2]; }
// least squares: y = p0 + p1 t + p2 t^2 + A cos(w t) + B sin(w t); returns RSS reduction fraction and fills A, B
static bool lsq(const std::vector<double>& t, const std::vector<double>& y, double w, double& A, double& B, double& rss, bool trig = true) {
    const int n = trig ? 5 : 3; double M_[5][6] = {{0}};
    for (size_t k = 0; k < t.size(); ++k) { double x = t[k], u = (x - 3000.0) / 3000.0, f[5] = {1, u, u * u, trig ? std::cos(w * x) : 0, trig ? std::sin(w * x) : 0}; /* Amendment 1: scaled time for the polynomial terms */ for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) M_[i][j] += f[i] * f[j]; M_[i][n] += f[i] * y[k]; } }
    for (int i = 0; i < n; ++i) { int p = i; for (int r = i + 1; r < n; ++r) if (std::fabs(M_[r][i]) > std::fabs(M_[p][i])) p = r; if (std::fabs(M_[p][i]) < 1e-300) return false; for (int c = 0; c <= n; ++c) std::swap(M_[i][c], M_[p][c]); for (int r = i + 1; r < n; ++r) { double f = M_[r][i] / M_[i][i]; for (int c = i; c <= n; ++c) M_[r][c] -= f * M_[i][c]; } }
    double sol[5] = {0}; for (int i = n - 1; i >= 0; --i) { double s = M_[i][n]; for (int j = i + 1; j < n; ++j) s -= M_[i][j] * sol[j]; sol[i] = s / M_[i][i]; }
    rss = 0; for (size_t k = 0; k < t.size(); ++k) { double x = t[k], u = (x - 3000.0) / 3000.0, m = sol[0] + sol[1] * u + sol[2] * u * u + (trig ? sol[3] * std::cos(w * x) + sol[4] * std::sin(w * x) : 0); rss += (y[k] - m) * (y[k] - m); } A = sol[3]; B = sol[4]; return true; }
static void scan(const std::vector<double>& t, const std::vector<double>& y, double& bestP, double& amp, double& phaseDeg) {
    double A, B, rss0; lsq(t, y, 1, A, B, rss0, false); double best = 1e300; bestP = 0; amp = 0;
    auto test = [&](double P) { double w = 2 * PI_ / P, rss; if (!lsq(t, y, w, A, B, rss)) return; if (rss < best) { best = rss; bestP = P; amp = std::sqrt(A * A + B * B); phaseDeg = std::atan2(-B, A) / DEG; } };
    for (double P = 400; P <= 2000; P += 1.0) test(P);
    double c = bestP; for (double P = c - 3; P <= c + 3; P += 0.05) test(P); }
static std::vector<double> g_t1, g_y1, g_t2, g_y2, g_aj, g_as, g_lj, g_ls, g_tt;
struct Run { double Pj, Aj, Ps, As, pdrift, ldrift, edrift; double kJ, kS; };
static double g_sJ = 1.0, g_sS = 1.0;   // Amendment 2: scale factors on Standish's a (calibrated so the simulated mean rates equal the sourced L-dot)
static Run integrate(double kSun, double fJ, double fS, double years, bool planetsOnly2 = false) {
    const double c = M::c, c2 = c * c;
    const double kJ = fJ * 4 * PI_ * PI_ * std::pow(421800e3, 3) / (c2 * std::pow(1.762732 * DAY, 2)), kS = fS * 4 * PI_ * PI_ * std::pow(1221900e3, 3) / (c2 * std::pow(15.945448 * DAY, 2));
    // Standish Table 2a, J2000, plus the Table 2b term c in M at T = 0
    El J{5.20248019 * AU * g_sJ, 0.04853590, 1.29861416 * DEG, 100.29282654 * DEG, (14.27495244 - 100.29282654) * DEG, (34.33479152 - 14.27495244 + 0.06064060) * DEG};
    El S{9.54149883 * AU * g_sS, 0.05550825, 2.49424102 * DEG, 113.63998702 * DEG, (92.86136063 - 113.63998702) * DEG, (50.07571329 - 92.86136063 - 0.13434469) * DEG};
    Body sun{kSun, {0, 0, 0}, {0, 0, 0}}, bj{kJ, {}, {}}, bs{kS, {}, {}};
    toState(J, c2 * (kSun + kJ), bj.r, bj.v); toState(S, c2 * (kSun + kS), bs.r, bs.v);
    std::vector<Body> B = planetsOnly2 ? std::vector<Body>{sun, bj} : std::vector<Body>{sun, bj, bs};
    double K = 0; V R{0, 0, 0}, Vv{0, 0, 0}; for (auto& b : B) { K += b.k; for (int q = 0; q < 3; ++q) { R[q] += b.k * b.r[q]; Vv[q] += b.k * b.v[q]; } } for (int q = 0; q < 3; ++q) { R[q] /= K; Vv[q] /= K; } for (auto& b : B) for (int q = 0; q < 3; ++q) { b.r[q] -= R[q]; b.v[q] -= Vv[q]; }
    const double dt = 2 * DAY; const long nsteps = (long)std::llround(years * 365.25 / 2.0); const int every = 15; // 30 days
    std::vector<V> a; accel(B, c2, a);
    V p0{0, 0, 0}, l0{0, 0, 0}; double np = 0, nl = 0; auto inv = [&](V& p, V& l) { p = {0, 0, 0}; l = {0, 0, 0}; for (auto& b : B) { V L = cross(b.r, b.v); for (int q = 0; q < 3; ++q) { p[q] += b.k * b.v[q]; l[q] += b.k * L[q]; } } };
    inv(p0, l0); for (auto& b : B) { np += b.k * nrm(b.v); nl += b.k * nrm(b.r) * nrm(b.v); }
    auto energy = [&]() { double e = 0; for (size_t i = 0; i < B.size(); ++i) { e += 0.5 * B[i].k * dot(B[i].v, B[i].v); for (size_t j = i + 1; j < B.size(); ++j) e -= c2 * B[i].k * B[j].k / nrm(sub(B[i].r, B[j].r)); } return e; };
    double e0 = energy(), edr = 0;
    std::vector<double> tj, lj, ts, ls; double prevJ = 0, prevS = 0; bool first = true; double offJ = 0, offS = 0;
    for (long i = 0; i <= nsteps; ++i) {
        if (i % every == 0) { El ej = toEl(sub(B[1].r, B[0].r), sub(B[1].v, B[0].v), c2 * (B[0].k + B[1].k)); double lamj = std::fmod(ej.Om + ej.w + ej.M, 2 * PI_);
            double lams = 0; if (!planetsOnly2) { El es = toEl(sub(B[2].r, B[0].r), sub(B[2].v, B[0].v), c2 * (B[0].k + B[2].k)); lams = std::fmod(es.Om + es.w + es.M, 2 * PI_); }
            if (first) { prevJ = lamj; prevS = lams; first = false; }
            while (lamj + offJ - prevJ > PI_) offJ -= 2 * PI_; while (lamj + offJ - prevJ < -PI_) offJ += 2 * PI_; while (lams + offS - prevS > PI_) offS -= 2 * PI_; while (lams + offS - prevS < -PI_) offS += 2 * PI_;
            prevJ = lamj + offJ; prevS = lams + offS; g_aj.push_back(ej.a / AU); g_lj.push_back(prevJ); g_ls.push_back(prevS); g_tt.push_back(i * 2.0 * DAY / YR); if (!planetsOnly2) { El es2 = toEl(sub(B[2].r, B[0].r), sub(B[2].v, B[0].v), c2 * (B[0].k + B[2].k)); g_as.push_back(es2.a / AU); } tj.push_back(i * 2.0 * DAY / YR); lj.push_back(prevJ); ts.push_back(i * 2.0 * DAY / YR); ls.push_back(prevS); }
        if (i % 20000 == 0) edr = std::max(edr, std::fabs(energy() / e0 - 1));
        if (i < nsteps) step(B, dt, c2, a); }
    V p1, l1; inv(p1, l1); Run out{}; out.pdrift = nrm(sub(p1, p0)) / np; out.ldrift = nrm(sub(l1, l0)) / nl; out.edrift = std::max(edr, std::fabs(energy() / e0 - 1)); out.kJ = kJ; out.kS = kS;
    // boxcar 725 samples (59.56 yr), then annual samples, convert to degrees
    auto proc = [&](const std::vector<double>& t, const std::vector<double>& l, std::vector<double>& to, std::vector<double>& yo) { const int W = 725; size_t n = l.size(); std::vector<double> cs(n + 1, 0.0); for (size_t i = 0; i < n; ++i) cs[i + 1] = cs[i] + l[i];
        for (size_t i = W / 2; i + W / 2 < n; i += 12) { double m = (cs[i + W / 2 + 1] - cs[i - W / 2]) / (W); to.push_back(t[i]); yo.push_back(m / DEG); } };
    std::vector<double> t1, y1, t2, y2; proc(tj, lj, t1, y1); if (!planetsOnly2) proc(ts, ls, t2, y2);
    g_t1 = t1; g_y1 = y1; g_t2 = t2; g_y2 = y2; double ph; scan(t1, y1, out.Pj, out.Aj, ph); if (!planetsOnly2) scan(t2, y2, out.Ps, out.As, ph);
    return out; }
int main(int argc, char** argv) {
    if (argc > 1) { // POST-SEEN DIAGNOSTIC (not part of the registered gates): amplitude spectrum of the baseline series
        Run r = integrate(1476.351201, 1.0, 1.0, 6000.0); (void)r; std::printf("POST-SEEN DIAGNOSTIC: amplitude (deg) of the sinusoid fitted jointly with a quadratic, Jupiter lambda, baseline\n"); std::vector<std::pair<double,double>> pk; double prev2 = -1, prev1 = -1, A_, B_, rss;
        std::vector<double> amp; for (double P = 400; P <= 2000; P += 1.0) { lsq(g_t1, g_y1, 2 * PI_ / P, A_, B_, rss); amp.push_back(std::sqrt(A_ * A_ + B_ * B_)); }
        for (size_t i = 1; i + 1 < amp.size(); ++i) if (amp[i] > amp[i - 1] && amp[i] > amp[i + 1]) pk.push_back({amp[i], 400.0 + i}); std::sort(pk.rbegin(), pk.rend()); for (size_t i = 0; i < pk.size() && i < 8; ++i) std::printf("  peak %zu: period %.0f yr, amplitude %.4f deg\n", i + 1, pk[i].second, pk[i].first);
        for (double P : {440.0, 473.0, 700.0, 883.0, 900.0, 920.0, 938.0, 946.0, 960.0, 1000.0, 1200.0, 1500.0, 2000.0}) { lsq(g_t1, g_y1, 2 * PI_ / P, A_, B_, rss); std::printf("  amplitude at P = %6.0f yr: %.4f deg\n", P, std::sqrt(A_ * A_ + B_ * B_)); }
        double s0 = 0, s1 = 0; for (double v : g_y1) { s0 += v; } (void)s1; std::printf("  series: %zu annual points from t = %.1f to %.1f yr; first/last value %.4f / %.4f deg\n", g_t1.size(), g_t1.front(), g_t1.back(), g_y1.front(), g_y1.back());
        { std::vector<double> t, y; const int W = 725; size_t n = g_lj.size(); std::vector<double> ph(n); for (size_t i = 0; i < n; ++i) ph[i] = (2 * g_lj[i] - 5 * g_ls[i]) / DEG; double A_, B_, rss;
          lsq(g_tt, ph, 1, A_, B_, rss, false); std::printf("  resonance angle 2 lambda_J - 5 lambda_S: rms about a quadratic %.3f deg\n", std::sqrt(rss / n));
          double mean_rate = (ph.back() - ph.front()) / (g_tt.back() - g_tt.front()); std::printf("  mean rate of 2 lambda_J - 5 lambda_S: %.4f deg/cy (period 360/|rate| = %.1f yr)\n", mean_rate * 100, 360.0 / std::fabs(mean_rate));
          { double rj = (g_lj.back() - g_lj.front()) / DEG / (g_tt.back() - g_tt.front()) * 100, rs = (g_ls.back() - g_ls.front()) / DEG / (g_tt.back() - g_tt.front()) * 100; std::printf("  mean rates over the run: lambda_J %.4f deg/cy (Standish L-dot 3034.9037), lambda_S %.4f deg/cy (1222.1149) ; a_J first/last %.6f / %.6f AU, a_S first/last %.6f / %.6f AU\n", rj, rs, g_aj.front(), g_aj.back(), g_as.front(), g_as.back()); }
          auto spec = [&](const char* nm, const std::vector<double>& ser) { std::vector<double> to, yo; std::vector<double> cs(ser.size() + 1, 0.0); for (size_t i = 0; i < ser.size(); ++i) cs[i + 1] = cs[i] + ser[i]; for (size_t i = W / 2; i + W / 2 < ser.size(); i += 12) { to.push_back(g_tt[i]); yo.push_back((cs[i + W / 2 + 1] - cs[i - W / 2]) / W); }
            std::vector<double> amp; for (double P = 400; P <= 2000; P += 1.0) { lsq(to, yo, 2 * PI_ / P, A_, B_, rss); amp.push_back(std::sqrt(A_ * A_ + B_ * B_)); } std::vector<std::pair<double,double>> pk; for (size_t i = 1; i + 1 < amp.size(); ++i) if (amp[i] > amp[i - 1] && amp[i] > amp[i + 1]) pk.push_back({amp[i], 400.0 + i}); std::sort(pk.rbegin(), pk.rend()); std::printf("  %s spectrum (boxcar-smoothed):", nm); for (size_t i = 0; i < pk.size() && i < 5; ++i) std::printf(" [%.0f yr: %.3g]", pk[i].second, pk[i].first); std::printf("\n"); };
          spec("a_J (AU)", g_aj); spec("a_S (AU)", g_as); std::vector<double> lam_deg(n); for (size_t i = 0; i < n; ++i) lam_deg[i] = g_lj[i] / DEG; spec("lambda_J (deg)", lam_deg); }
        { const double c2 = M::c * M::c; struct Q { const char* nm; double fJ, fS; }; Q qs[3] = {{"Jupiter mass x1e-6 (Saturn effectively alone with the Sun)", 1e-6, 1.0}, {"Saturn mass x1e-6 (Jupiter effectively alone)", 1.0, 1e-6}, {"both planets x1e-6", 1e-6, 1e-6}};
          for (auto& q : qs) { integrate(1476.351201, q.fJ, q.fS, 600.0); double kJ = q.fJ * 4 * PI_ * PI_ * std::pow(421800e3, 3) / (c2 * std::pow(1.762732 * DAY, 2)), kS = q.fS * 4 * PI_ * PI_ * std::pow(1221900e3, 3) / (c2 * std::pow(15.945448 * DAY, 2));
            double nJ = std::sqrt(c2 * (1476.351201 + kJ) / std::pow(5.20248019 * AU, 3)) * 365.25 * 86400 * 100 / DEG, nS = std::sqrt(c2 * (1476.351201 + kS) / std::pow(9.54149883 * AU, 3)) * 365.25 * 86400 * 100 / DEG;
            double rj = (g_lj.back() - g_lj.front()) / DEG / (g_tt.back() - g_tt.front()) * 100, rs = (g_ls.back() - g_ls.front()) / DEG / (g_tt.back() - g_tt.front()) * 100;
            std::printf("  CHECK %s: lambda_J rate %.4f vs Kepler n_J %.4f (%+.3e) ; lambda_S rate %.4f vs Kepler n_S %.4f (%+.3e)\n", q.nm, rj, nJ, rj / nJ - 1, rs, nS, rs / nS - 1); } }
        return 0; }
    std::printf("GOM42 P1 (registered in GOM42_P1_REGISTRATION_2026-10-14.md)\n=======================================================================\n\n");
    int fails = 0; const double kSun = 1476.351201;
    // VP2: round trip
    { El J{5.20248019 * AU, 0.04853590, 1.29861416 * DEG, 100.29282654 * DEG, (14.27495244 - 100.29282654) * DEG, 0.4}; double mu = 1.3e20; V r, v; toState(J, mu, r, v); El b = toEl(r, v, mu);
      auto wrapd = [](double x) { x = std::fmod(x, 2 * PI_); if (x > PI_) x -= 2 * PI_; if (x < -PI_) x += 2 * PI_; return std::fabs(x); };
      double e1 = std::fabs(b.a / J.a - 1), e2 = std::fabs(b.e - J.e), e3 = std::max({wrapd(b.I - J.I), wrapd(b.Om - J.Om), wrapd(b.w - J.w), wrapd(b.M - J.M)}); bool ok = e1 < 1e-12 && e2 < 1e-12 && e3 < 1e-12;
      std::printf("[VP2] elements -> state -> elements: a %.1e, e %.1e, angles %.1e -> %s\n", e1, e2, e3, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // VP3: planted sinusoid recovery
    { std::vector<double> t, y; unsigned s = 12345; auto rnd = [&]() { s = s * 1664525u + 1013904223u; return ((s >> 8) / 16777216.0 - 0.5) * 0.0346; }; for (int i = 0; i < 5300; ++i) { double x = 380.0 + i; t.push_back(x); y.push_back(0.36 * std::cos(2 * PI_ * x / 938.68 + 0.7) + 30.349037 * (x - 3000) + 2e-4 * (x - 3000) * (x - 3000) + rnd()); }   /* Amendment 1: realistic linear and quadratic trend (the series reaches 1.8e5 deg) */
      double P, A, ph; scan(t, y, P, A, ph); bool ok = std::fabs(P - 938.68) <= 0.5 && std::fabs(A / 0.36 - 1) <= 0.05; std::printf("[VP3] planted 938.68 yr sinusoid (0.36 deg, noise 0.01 deg) on an annual grid: recovered %.2f yr, amplitude %.3f deg -> %s\n", P, A, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // VP1: Sun + Jupiter only, 600 yr
    { const double c2 = M::c * M::c; double kJ = 4 * PI_ * PI_ * std::pow(421800e3, 3) / (c2 * std::pow(1.762732 * DAY, 2)); El J{5.20248019 * AU, 0.04853590, 1.29861416 * DEG, 100.29282654 * DEG, (14.27495244 - 100.29282654) * DEG, 0.6};
      Body sun{kSun, {0, 0, 0}, {0, 0, 0}}, bj{kJ, {}, {}}; toState(J, c2 * (kSun + kJ), bj.r, bj.v); std::vector<Body> B = {sun, bj}; std::vector<V> a; accel(B, c2, a);
      double amax = 0, emax = 0; std::vector<double> tt, ll; double prev = 0, off = 0; bool first = true; double a0 = J.a, e0 = J.e; double n = std::sqrt(c2 * (kSun + kJ) / (a0 * a0 * a0)), tol = 3 * std::pow(n * 2 * DAY, 2);
      long ns = (long)(600 * 365.25 / 2.0); double aStart = 0, aEnd = 0; int cnt = 0;
      for (long i = 0; i <= ns; ++i) { if (i % 15 == 0) { El e = toEl(sub(B[1].r, B[0].r), sub(B[1].v, B[0].v), c2 * (B[0].k + B[1].k)); amax = std::max(amax, std::fabs(e.a / a0 - 1)); emax = std::max(emax, std::fabs(e.e - e0)); double lam = std::fmod(e.Om + e.w + e.M, 2 * PI_); if (first) { prev = lam; first = false; } while (lam + off - prev > PI_) off -= 2 * PI_; while (lam + off - prev < -PI_) off += 2 * PI_; prev = lam + off; tt.push_back(i * 2.0 * DAY / YR); ll.push_back(prev); if (cnt < 400) aStart += e.a / a0; ++cnt; } if (i < ns) step(B, 2 * DAY, c2, a); }
      for (size_t k = ll.size() - 400; k < ll.size(); ++k) { El dummy; (void)dummy; }
      double A_, B_, rss; lsq(tt, ll, 1, A_, B_, rss, false); double rms = std::sqrt(rss / tt.size());
      bool ok = amax <= tol && emax <= tol && rms < 1e-4; std::printf("[VP1] Sun + Jupiter, 600 yr: max |da/a| %.2e and max |de| %.2e (tolerance 3 (n dt)^2 = %.2e) ; lambda residual after a quadratic fit rms %.2e rad (gate 1e-4) -> %s\n", amax, emax, tol, rms, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; }
    std::printf("\nMAIN RUN (6000 yr, 3 bodies, dt = 2 d)\n");
    struct Var { const char* nm; double ks, fj, fs; }; Var vs[4] = {{"baseline (native kappa)", kSun, 1.0, 1.0}, {"kappa_Sun +1.85e-4 (GM-equivalent offset)", kSun * (1 + 1.85e-4), 1.0, 1.0}, {"kappa_J, kappa_S x 0.992 (satellite-period mismatch)", kSun, 0.992, 0.992}, {"both", kSun * (1 + 1.85e-4), 0.992, 0.992}};
    const double Ps = 938.68; bool gate = false;
    for (int i = 0; i < 4; ++i) { Run r = integrate(vs[i].ks, vs[i].fj, vs[i].fs, 6000.0); std::printf("%-56s kappa_J %.5f m kappa_S %.4f m | Jupiter: period %8.2f yr (%+.2f%% from %.2f), amplitude %.4f deg | Saturn: period %8.2f yr, amplitude %.4f deg, ratio S/J %.2f | drifts: P %.1e L %.1e E %.1e\n", vs[i].nm, r.kJ, r.kS, r.Pj, 100 * (r.Pj / Ps - 1), Ps, r.Aj, r.Ps, r.As, r.As / r.Aj, r.pdrift, r.ldrift, r.edrift); if (i == 0) gate = std::fabs(r.Pj / Ps - 1) <= 0.02; if (i == 0 && !(r.pdrift <= 1e-11 && r.ldrift <= 1e-10 && r.edrift <= 1e-8)) std::printf("   [VP4] invariants NOT MET\n"); else if (i == 0) std::printf("   [VP4] invariants met\n"); }
    std::printf("\nG-P1 (baseline Jupiter period within 2%% of 938.68 yr, i.e. [920.9, 957.5]): %s\nSourced amplitudes: Jupiter 0.3615 deg, Saturn 0.8835 deg (ratio 2.44).\n", gate ? "MET" : "NOT MET");
    // ---- AMENDMENT 2 (post-seen): initial semi-major axes calibrated to the sourced Standish mean longitude rates ----
    std::printf("\nAMENDMENT 2 (post-seen): osculating a at J2000 scaled so the simulated mean rates equal the sourced L-dot (J 3034.90371757, S 1222.11494724 deg/cy)\n");
    auto slope = [](const std::vector<double>& t, const std::vector<double>& y) { double mt = 0, my = 0; for (size_t i = 0; i < t.size(); ++i) { mt += t[i]; my += y[i]; } mt /= t.size(); my /= t.size(); double sxy = 0, sxx = 0; for (size_t i = 0; i < t.size(); ++i) { sxy += (t[i] - mt) * (y[i] - my); sxx += (t[i] - mt) * (t[i] - mt); } return sxy / sxx; };
    const double tJ = 3034.90371757, tS = 1222.11494724; bool gate2 = false;
    for (int i = 0; i < 4; ++i) {
        g_sJ = 1.0; g_sS = 1.0; double rj = 0, rs = 0; int it = 0;
        for (; it < 14; ++it) { integrate(vs[i].ks, vs[i].fj, vs[i].fs, 6000.0); rj = slope(g_tt, g_lj) / DEG * 100; rs = slope(g_tt, g_ls) / DEG * 100; if (std::fabs(rj / tJ - 1) < 2e-6 && std::fabs(rs / tS - 1) < 2e-6) break; g_sJ *= std::pow(rj / tJ, 2.0 / 3.0); g_sS *= std::pow(rs / tS, 2.0 / 3.0); }
        Run r = integrate(vs[i].ks, vs[i].fj, vs[i].fs, 6000.0); rj = slope(g_tt, g_lj) / DEG * 100; rs = slope(g_tt, g_ls) / DEG * 100;
        std::printf("%-56s scales s_J %.6f s_S %.6f (%d iterations) ; achieved rates J %.4f (%+.1e) S %.4f (%+.1e) | Jupiter: period %8.2f yr (%+.2f%%), amplitude %.4f deg | Saturn: period %8.2f yr, amplitude %.4f deg, ratio %.2f | drifts E %.1e\n", vs[i].nm, g_sJ, g_sS, it, rj, rj / tJ - 1, rs, rs / tS - 1, r.Pj, 100 * (r.Pj / Ps - 1), r.Aj, r.Ps, r.As, r.As / r.Aj, r.edrift);
        if (i == 0) gate2 = std::fabs(r.Pj / Ps - 1) <= 0.02; }
    std::printf("\nG-P1 under Amendment 2 (baseline Jupiter period within 2%% of 938.68 yr): %s\n", gate2 ? "MET" : "NOT MET");
    return 0;
}
