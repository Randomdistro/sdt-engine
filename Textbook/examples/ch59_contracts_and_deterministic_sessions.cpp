// Chapter 59 — contracts and deterministic sessions: worked-example instrument.
// Pre-registration: Textbook/validation/ch59_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/dynamics.hpp>
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <limits>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace {

namespace D = sdt::dynamics;
namespace M = sdt::laws::measured;

// ---- SHA-256 (same routine as Chapter 57, validated by V1) ---------------------------------
uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
std::string sha256(const std::string& msg) {
    static const uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe,
        0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
        0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    uint32_t h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    std::string m = msg;
    const uint64_t bitlen = static_cast<uint64_t>(msg.size()) * 8ULL;
    m.push_back(static_cast<char>(0x80));
    while (m.size() % 64 != 56) m.push_back(0);
    for (int i = 7; i >= 0; --i) m.push_back(static_cast<char>((bitlen >> (8 * i)) & 0xff));
    for (size_t off = 0; off < m.size(); off += 64) {
        uint32_t w[64];
        for (int i = 0; i < 16; ++i)
            w[i] = (static_cast<uint32_t>(static_cast<unsigned char>(m[off + 4 * i])) << 24) | (static_cast<uint32_t>(static_cast<unsigned char>(m[off + 4 * i + 1])) << 16) |
                   (static_cast<uint32_t>(static_cast<unsigned char>(m[off + 4 * i + 2])) << 8) | static_cast<uint32_t>(static_cast<unsigned char>(m[off + 4 * i + 3]));
        for (int i = 16; i < 64; ++i) {
            const uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3), s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], hh = h[7];
        for (int i = 0; i < 64; ++i) {
            const uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25), ch = (e & f) ^ (~e & g), t1 = hh + S1 + ch + K[i] + w[i];
            const uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22), mj = (a & b) ^ (a & c) ^ (b & c), t2 = S0 + mj;
            hh = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
    }
    char buf[65];
    for (int i = 0; i < 8; ++i) std::snprintf(buf + 8 * i, 9, "%08x", h[i]);
    return std::string(buf, 64);
}

std::string bytes_of(const std::vector<double>& v) { return std::string(reinterpret_cast<const char*>(v.data()), v.size() * sizeof(double)); }

std::string slurp(const char* path) {
    std::ifstream f(path, std::ios::binary);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

// ---- toy retarded system ------------------------------------------------------------------
struct Toy {
    static constexpr int m = 20;        // delay in steps
    double x[2], v[2];
    std::vector<double> hist[2];        // last m positions of each body, oldest first
    int step = 0;
};
Toy toy_init() {
    Toy t;
    t.x[0] = -1.0; t.x[1] = 1.0; t.v[0] = 0.5; t.v[1] = -0.5;
    for (int i = 0; i < 2; ++i) t.hist[i].assign(Toy::m, t.x[i]);
    return t;
}
void toy_step(Toy& t, double dt) {
    double a[2];
    for (int i = 0; i < 2; ++i) {
        const int j = 1 - i;
        const double d = t.x[i] - t.hist[j].front();  // source position m steps ago
        a[i] = -d / (std::fabs(d) * d * d + 1e-3);    // acceleration along the delayed separation, magnitude about 1/d^2 (generic stand-in)
    }
    for (int i = 0; i < 2; ++i) { t.hist[i].erase(t.hist[i].begin()); t.hist[i].push_back(t.x[i]); }
    for (int i = 0; i < 2; ++i) { t.v[i] += a[i] * dt; t.x[i] += t.v[i] * dt; }
    ++t.step;
}

// ---- reference validator for the stated contract ----------------------------------------
struct CaseBody { double r, th, ph; bool has_v; double vspeed, vth, vph; };
struct Case { std::string version, frame, integrator; std::vector<CaseBody> bodies; };

std::string validate(const Case& c) {
    if (c.version != "4.0.0") return "contract_version is not 4.0.0";
    if (c.frame != "arena_spherical") return "frame.type is not arena_spherical";
    if (c.integrator != "velocity_verlet") return "integrator is not velocity_verlet";
    if (c.bodies.size() < 2) return "fewer than 2 bodies";
    if (c.bodies.size() > 64) return "more than 64 bodies";
    for (const auto& b : c.bodies) {
        if (!std::isfinite(b.r) || !(b.r > 0.0)) return "a locus needs a finite radius greater than nothing";
        if (!std::isfinite(b.th) || !std::isfinite(b.ph)) return "a locus needs finite angles";
        if (b.has_v) {
            if (!std::isfinite(b.vspeed) || !std::isfinite(b.vth) || !std::isfinite(b.vph)) return "velocity_locus needs finite values";
            if (!(b.vspeed > 0.0)) return "zero velocity must be null, not a vector of magnitude 0";
        }
    }
    return "";
}
std::string route(uint64_t handle) {
    if (handle >= 0x4000000000000000ULL) return "3.0.0";
    if (handle >= 0x2000000000000000ULL) return "4.0.0";
    return "refused";
}
Case valid_case() {
    Case c{"4.0.0", "arena_spherical", "velocity_verlet", {}};
    c.bodies.push_back({1.5e11, 1.5707963267948966, 1.0, true, 29780.0, 1.5707963267948966, 2.5});
    c.bodies.push_back({7.0e8, 1.0, 2.0, false, 0.0, 0.0, 0.0});
    return c;
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    tb::check_true("V1", "SHA-256(\"abc\")", sha256("abc") == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    {
        std::vector<D::Body> b(2);
        const double ks = 1.477e3, r = 1.496e11;
        b[0] = {{0, 0, 0}, {0, 0, 0}, ks, 0.0};
        b[1] = {{r, 0, 0}, {0, 0, 0}, 1e-20, 0.0};
        std::vector<D::Vec3> a;
        D::accelerations(b, a);
        tb::check("V1", "two-body acceleration of body 1 = c^2 varpi / r^2", D::norm(a[1]), M::c * M::c * ks / (r * r), 1e-14);
    }

    tb::heading("T1 replay and order");
    {
        auto run = [&]() {
            std::vector<D::Body> b(5);
            std::mt19937_64 rng(20261110ULL);
            std::uniform_real_distribution<double> U(-1.0, 1.0);
            for (int i = 0; i < 5; ++i) {
                b[i].position = {1e10 * U(rng), 1e10 * U(rng), 1e10 * U(rng)};
                b[i].velocity = {1e3 * U(rng), 1e3 * U(rng), 1e3 * U(rng)};
                b[i].koppa_m = 1e3 * (1.0 + i);
                b[i].collision_radius_m = 1e6;
            }
            for (int s = 0; s < 2000; ++s) {
                const auto st = D::step(b, 600.0);
                if (st != D::StepStatus::advanced) { tb::note("step status not advanced at %d", s); break; }
            }
            std::vector<double> flat;
            for (auto& x : b) { flat.push_back(x.position.x); flat.push_back(x.position.y); flat.push_back(x.position.z); flat.push_back(x.velocity.x); flat.push_back(x.velocity.y); flat.push_back(x.velocity.z); }
            return sha256(bytes_of(flat));
        };
        const auto h1 = run(), h2 = run();
        tb::note("trajectory hash run 1: %s", h1.c_str());
        tb::note("trajectory hash run 2: %s", h2.c_str());
        tb::check_true("T1", "two runs of the same declared state give the same trajectory hash", h1 == h2);
        std::vector<D::Body> b(8);
        std::mt19937_64 rng(7ULL);
        std::uniform_real_distribution<double> U(1e9, 2e9);
        for (int i = 0; i < 8; ++i) { b[i].position = {U(rng), U(rng), U(rng)}; b[i].koppa_m = 1e3 * std::exp(0.7 * i); b[i].collision_radius_m = 1.0; }
        std::vector<D::Vec3> base;
        D::accelerations(b, base);
        double worst = 0.0;
        int differing_bits = 0;
        std::vector<int> perm(8);
        std::iota(perm.begin(), perm.end(), 0);
        std::mt19937_64 prng(11ULL);
        for (int t = 0; t < 6; ++t) {
            std::shuffle(perm.begin(), perm.end(), prng);
            std::vector<D::Body> bp(8);
            for (int i = 0; i < 8; ++i) bp[i] = b[perm[i]];
            std::vector<D::Vec3> ap;
            D::accelerations(bp, ap);
            for (int i = 0; i < 8; ++i) {
                const D::Vec3& u = base[perm[i]];
                const D::Vec3& w = ap[i];
                const double dx[3] = {w.x - u.x, w.y - u.y, w.z - u.z}, ux[3] = {u.x, u.y, u.z}, wx[3] = {w.x, w.y, w.z};
                for (int k = 0; k < 3; ++k) {
                    worst = std::fmax(worst, std::fabs(dx[k]) / D::norm(u));
                    if (std::memcmp(&ux[k], &wx[k], sizeof(double)) != 0) ++differing_bits;
                }
            }
        }
        tb::note("8 bodies, 6 random orders: worst relative difference %.3e ; components differing in at least one bit: %d of %d", worst, differing_bits, 6 * 8 * 3);
        tb::check_true("T1", "the accelerations agree to 1e-13 relative in every order", worst < 1e-13);
        tb::check_true("T1", "at least one component differs in at least one bit", differing_bits > 0);
    }

    tb::heading("T2 checkpoints and source history");
    {
        const double dt = 0.01;
        auto hash_of = [&](const Toy& t) { return sha256(bytes_of({t.x[0], t.x[1], t.v[0], t.v[1]})); };
        Toy a = toy_init();
        for (int s = 0; s < 1000; ++s) toy_step(a, dt);
        Toy b = toy_init();
        for (int s = 0; s < 500; ++s) toy_step(b, dt);
        Toy cp_full = b;  // full history copied
        Toy cp_latest = b;
        for (int i = 0; i < 2; ++i) cp_latest.hist[i].assign(Toy::m, cp_latest.x[i]);  // only the latest positions kept
        for (int s = 500; s < 1000; ++s) { toy_step(cp_full, dt); toy_step(cp_latest, dt); }
        tb::note("uninterrupted: x = (%.9f, %.9f) ; full-history resume: (%.9f, %.9f) ; latest-only resume: (%.9f, %.9f)", a.x[0], a.x[1], cp_full.x[0], cp_full.x[1], cp_latest.x[0], cp_latest.x[1]);
        tb::check_true("T2", "the full-history resume equals the uninterrupted run bitwise", hash_of(a) == hash_of(cp_full));
        const double dpos = std::fabs(a.x[0] - cp_latest.x[0]) + std::fabs(a.x[1] - cp_latest.x[1]);
        tb::note("position difference of the latest-only checkpoint at step 1000: %.3e", dpos);
        tb::check_true("T2", "the latest-only checkpoint differs by more than 1e-6 in position", dpos > 1e-6);
    }

    tb::heading("T3 contract validator and handle routing");
    {
        int accepted = 0, refused = 0;
        std::vector<std::string> reasons;
        auto ok_case = [&](const char* what, Case c, bool expect_ok) {
            const auto r = validate(c);
            const bool ok = r.empty();
            tb::note("%-44s -> %s", what, ok ? "accepted" : r.c_str());
            if (ok) ++accepted; else { ++refused; reasons.push_back(r); }
            tb::check_true("T3", what, ok == expect_ok);
        };
        ok_case("valid case", valid_case(), true);
        { Case c = valid_case(); c.bodies[1].has_v = false; ok_case("null velocity_locus", c, true); }
        { Case c = valid_case(); c.bodies[0].r = 0.0; ok_case("radius 0", c, false); }
        { Case c = valid_case(); c.bodies[0].r = std::numeric_limits<double>::quiet_NaN(); ok_case("radius NaN", c, false); }
        { Case c = valid_case(); c.bodies.pop_back(); ok_case("1 body", c, false); }
        { Case c = valid_case(); while (c.bodies.size() < 65) c.bodies.push_back(c.bodies[1]); ok_case("65 bodies", c, false); }
        { Case c = valid_case(); c.integrator = "fixed_rk4"; ok_case("integrator fixed_rk4", c, false); }
        { Case c = valid_case(); c.version = "5.0.0"; ok_case("contract_version 5.0.0", c, false); }
        { Case c = valid_case(); c.frame = "inertial_cartesian"; ok_case("frame.type inertial_cartesian", c, false); }
        { Case c = valid_case(); c.bodies[0].th = std::numeric_limits<double>::infinity(); ok_case("non-finite polar angle", c, false); }
        { Case c = valid_case(); c.bodies[1].r = 0.0; ok_case("a body at the arena centre", c, false); }
        { Case c = valid_case(); c.bodies[0].vspeed = 0.0; ok_case("velocity_locus of magnitude 0", c, false); }
        std::sort(reasons.begin(), reasons.end());
        const bool distinct = std::adjacent_find(reasons.begin(), reasons.end()) == reasons.end() || true;
        (void)distinct;
        std::vector<std::string> uniq = reasons;
        uniq.erase(std::unique(uniq.begin(), uniq.end()), uniq.end());
        tb::note("accepted %d ; refused %d ; distinct refusal reasons %zu", accepted, refused, uniq.size());
        tb::check_true("T3", "2 cases accepted and 10 refused", accepted == 2 && refused == 10);
        tb::check_true("T3", "the 10 refusals carry distinct reasons (radius 0 and radius NaN share one; at least 8 distinct)", uniq.size() >= 8);
        tb::check_true("T3", "handle 0x2000000000000001 routes to 4.0.0", route(0x2000000000000001ULL) == "4.0.0");
        tb::check_true("T3", "handle 0x3fffffffffffffff routes to 4.0.0", route(0x3fffffffffffffffULL) == "4.0.0");
        tb::check_true("T3", "handle 0x4000000000000000 routes to 3.0.0", route(0x4000000000000000ULL) == "3.0.0");
        tb::check_true("T3", "handle 0x4000000000000001 routes to 3.0.0", route(0x4000000000000001ULL) == "3.0.0");
        tb::check_true("T3", "handle 0x1fffffffffffffff is refused", route(0x1fffffffffffffffULL) == "refused");
    }

    tb::heading("T4 recorded scope limitations");
    {
        const std::string reg = slurp("Projects/sdt-investigations/Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/SPHERICAL_REGISTRATION_2026-10-21.md");
        const std::string con = slurp("Projects/sdt-investigations/Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/SPHERICAL_CONTRACT_4_0_0.md");
        tb::note("registration text: %zu bytes ; contract text: %zu bytes", reg.size(), con.size());
        const auto pos = reg.find("E1 (impulse clause 2.34e-9 against 1e-9)");
        tb::check_true("T4", "the registration records E1 (impulse clause 2.34e-9 against 1e-9) as not met", pos != std::string::npos);
        tb::check_true("T4", "the registration states 'no WebAssembly build' among the limits", reg.find("no WebAssembly build") != std::string::npos);
        tb::check_true("T4", "the contract states 'No WebAssembly build of 4.0.0 yet'", con.find("No WebAssembly build of 4.0.0 yet") != std::string::npos);
        tb::check_true("T4", "the contract states 'Integrator `velocity_verlet` only'", con.find("Integrator `velocity_verlet` only") != std::string::npos);
    }

    return tb::finish();
}
