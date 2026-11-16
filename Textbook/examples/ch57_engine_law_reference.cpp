// Chapter 57 — engine law reference: worked-example instrument (traceability, citations, domains, inventory).
// Pre-registration: Textbook/validation/ch57_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

// ---- SHA-256 ------------------------------------------------------------------------------
struct Sha256 {
    static inline const uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe,
        0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
        0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    static uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
    static std::string hash(const std::string& msg) {
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
                const uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
                const uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
                w[i] = w[i - 16] + s0 + w[i - 7] + s1;
            }
            uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], hh = h[7];
            for (int i = 0; i < 64; ++i) {
                const uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25), ch = (e & f) ^ (~e & g);
                const uint32_t t1 = hh + S1 + ch + K[i] + w[i];
                const uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22), mj = (a & b) ^ (a & c) ^ (b & c);
                const uint32_t t2 = S0 + mj;
                hh = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
            }
            h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
        }
        char buf[65];
        for (int i = 0; i < 8; ++i) std::snprintf(buf + 8 * i, 9, "%08x", h[i]);
        return std::string(buf, 64);
    }
};

std::string slurp(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

int count_lines(const std::string& s) {
    int n = 0;
    for (char ch : s) if (ch == '\n') ++n;
    if (!s.empty() && s.back() != '\n') ++n;
    return n;
}

std::vector<std::string> split_lines(const std::string& s) {
    std::vector<std::string> out;
    std::string cur;
    for (char ch : s) {
        if (ch == '\n') { out.push_back(cur); cur.clear(); } else if (ch != '\r') cur.push_back(ch);
    }
    if (!cur.empty()) out.push_back(cur);
    return out;
}

}  // namespace

int main() {
    tb::validate_helpers();
    namespace M = sdt::laws::measured;

    tb::heading("V1 known answers");
    tb::check_true("V1", "SHA-256(\"abc\")", Sha256::hash("abc") == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    tb::check_true("V1", "SHA-256(\"\")", Sha256::hash("") == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    tb::check_true("V1", "SHA-256 of the 56-character message across a block boundary", Sha256::hash("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") == "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
    tb::check_true("V1", "line counter returns 3 for \"a\\nb\\nc\\n\"", count_lines("a\nb\nc\n") == 3);

    const fs::path hdr = "Engine/include/sdt";

    tb::heading("T1 hashes of the consumed headers");
    std::vector<std::string> names;
    {
        std::vector<fs::path> files;
        for (auto& e : fs::directory_iterator(hdr)) if (e.path().extension() == ".hpp") files.push_back(e.path());
        std::sort(files.begin(), files.end());
        std::set<std::string> digests;
        bool det = true;
        for (auto& p : files) {
            const std::string s = slurp(p);
            const std::string d1 = Sha256::hash(s), d2 = Sha256::hash(slurp(p));
            det = det && d1 == d2;
            digests.insert(d1);
            names.push_back(p.filename().string());
            std::printf("       %-26s %6d lines  %s\n", p.filename().string().c_str(), count_lines(s), d1.c_str());
        }
        tb::check_true("T1", "14 headers hashed", files.size() == 14);
        tb::check_true("T1", "hashing the same file twice gives the same digest", det);
        tb::check_true("T1", "the 14 digests are pairwise distinct", digests.size() == files.size());
        std::printf("       repository revision: ");
        std::fflush(stdout);
        std::system("git rev-parse --short HEAD");
        std::printf("       working-tree state of Engine/include/sdt (git status --porcelain; empty = clean):\n");
        std::fflush(stdout);
        std::system("git status --porcelain -- Engine/include/sdt");
        std::printf("       (end of working-tree listing)\n");
    }

    tb::heading("T2 citations resolve");
    {
        std::regex re("([A-Za-z_]+\\.hpp):([0-9]+)");
        int total = 0, bad = 0, l99 = 0, l99bad = 0;
        std::set<std::string> valid(names.begin(), names.end());
        std::vector<std::string> cache_names;
        std::vector<std::vector<std::string>> cache_lines;
        auto lines_of = [&](const std::string& nm) -> const std::vector<std::string>& {
            for (size_t i = 0; i < cache_names.size(); ++i) if (cache_names[i] == nm) return cache_lines[i];
            cache_names.push_back(nm);
            cache_lines.push_back(split_lines(slurp(hdr / nm)));
            return cache_lines.back();
        };
        std::vector<fs::path> docs;
        for (auto& e : fs::recursive_directory_iterator("Textbook")) {
            const auto s = e.path().generic_string();
            if (e.is_regular_file() && e.path().extension() == ".md" && (s.find("Textbook/volume_") != std::string::npos || s.find("Textbook/equations/") != std::string::npos)) docs.push_back(e.path());
        }
        std::sort(docs.begin(), docs.end());
        for (auto& p : docs) {
            const std::string txt = slurp(p);
            for (std::sregex_iterator it(txt.begin(), txt.end(), re), end; it != end; ++it) {
                const std::string nm = (*it)[1].str();
                const int ln = std::atoi((*it)[2].str().c_str());
                if (!valid.count(nm)) continue;
                ++total;
                const auto& L = lines_of(nm);
                const bool ok = ln >= 1 && ln <= static_cast<int>(L.size()) && L[ln - 1].find_first_not_of(" \t") != std::string::npos;
                if (!ok) { ++bad; std::printf("       UNRESOLVED %s:%d in %s\n", nm.c_str(), ln, p.generic_string().c_str()); }
                if (nm == "laws.hpp" && ln == 99) {
                    ++l99;
                    if (!(ok && L[ln - 1].find("l_P") != std::string::npos)) ++l99bad;
                }
            }
        }
        tb::note("citations found: %d ; unresolved: %d ; laws.hpp:99 citations: %d (not on the l_P line: %d)", total, bad, l99, l99bad);
        tb::check_true("T2", "at least 25 citations are found", total >= 25);
        tb::check_true("T2", "every citation resolves to a non-blank line of the named header", bad == 0);
        tb::check_true("T2", "every laws.hpp:99 citation lands on the line defining l_P", l99bad == 0);
    }

    tb::heading("T3 function domains");
    {
        namespace D = sdt::laws::depth_closure;
        namespace V = sdt::laws::law_V;
        namespace B = sdt::laws::bridge;
        const double c = M::c;
        tb::note("clock_rate(1.5) = %g ; clock_rate(-0.1) = %g ; gamma(1.1c) = %g ; v_circ(1.2c) = %g", D::clock_rate(1.5), D::clock_rate(-0.1), V::gamma(1.1 * c), V::v_circ(1.2 * c));
        tb::check_true("T3", "clock_rate(1.5) is negative (z > 1 is not rejected)", D::clock_rate(1.5) < 0.0);
        tb::check_true("T3", "clock_rate(-0.1) exceeds 1 (z < 0 is not rejected)", D::clock_rate(-0.1) > 1.0);
        tb::check_true("T3", "gamma(1.1 c) is NaN", std::isnan(V::gamma(1.1 * c)));
        tb::check_true("T3", "v_circ(1.2 c) is NaN", std::isnan(V::v_circ(1.2 * c)));
        tb::note("RECORDED REJECTION (run 1 criterion kept): depth_from_c_far(1.5 c, c) = %g (finite, not NaN)", D::depth_from_c_far(1.5 * c, c));
        tb::check_true("T3", "the registered statement (depth_from_c_far(1.5 c, c) is NaN) is rejected", !std::isnan(D::depth_from_c_far(1.5 * c, c)));
        tb::check_true("T3", "POST-RUN clause: depth_from_c_far(1.5 c, c) is negative (a depth below zero, not rejected)", D::depth_from_c_far(1.5 * c, c) < 0.0);
        tb::check_true("T3", "POST-RUN clause: depth_from_c_far(-0.1 c, c) is NaN", std::isnan(D::depth_from_c_far(-0.1 * c, c)));
        tb::check_true("T3", "circular_speed_from_koppa(1, -1) is NaN", std::isnan(B::circular_speed_from_koppa(1.0, -1.0)));
        const double vE = B::v_Earth, RE = B::R_Earth;
        const double rin = 0.5, rout = 2.0;
        const double g_in = B::g_interior(vE, RE, rin, std::pow(rin / RE, 3.0));
        const double g_out = B::g_interior(vE, RE, rout, std::pow(rout / RE, 3.0));
        const double g_exact_in = vE * vE * RE * std::pow(rin / RE, 3.0) / (rin * rin);
        tb::note("g_interior at 0.5 m = %g ; at 2 m = %g ; the uniform-density value at 0.5 m would be %g", g_in, g_out, g_exact_in);
        tb::check_true("T3", "g_interior returns exactly 0 at r = 0.5 m (numerical cutoff below 1 m)", g_in == 0.0);
        tb::check_true("T3", "g_interior is nonzero at r = 2 m for the same uniform-density fraction", g_out > 0.0);
        tb::check_true("T3", "the value the cutoff replaces at 0.5 m is nonzero (an implementation choice, not an analytic limit)", g_exact_in > 0.0);
    }

    tb::heading("T4 inventory of laws.hpp");
    {
        const auto lines = split_lines(slurp(hdr / "laws.hpp"));
        std::regex ns("^namespace ([A-Za-z_0-9]+) \\{");
        std::set<std::string> top;
        int nodiscard = 0, constants = 0;
        for (const auto& ln : lines) {
            std::smatch m;
            if (std::regex_search(ln, m, ns)) top.insert(m[1].str());
            if (ln.find("[[nodiscard]]") != std::string::npos) ++nodiscard;
            if (ln.find("inline constexpr double") != std::string::npos) ++constants;
        }
        bool all = true;
        for (const char* nm : {"measured", "law_I", "law_II", "law_III", "law_IV", "law_V", "law_VI", "bridge", "atomic", "nuclear", "depth_closure"}) {
            const bool has = top.count(nm) > 0;
            if (!has) std::printf("       MISSING top-level namespace %s\n", nm);
            all = all && has;
        }
        tb::note("laws.hpp: %zu lines ; %zu top-level namespace names ; [[nodiscard]] occurrences %d ; inline constexpr double constants %d", lines.size(), top.size(), nodiscard, constants);
        tb::check_true("T4", "each of the 11 principal namespaces is a top-level namespace line of laws.hpp", all);
    }

    return tb::finish();
}
