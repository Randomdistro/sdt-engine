// NP34b — complete natural misfit census L∪H vs NUBASE2020 (pre-registered)
#include <sdt/laws.hpp>

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <wincrypt.h>

#pragma comment(lib, "advapi32.lib")

using namespace sdt::laws;

namespace {

constexpr char kNubase[] = "Datasets/nuclear/NUBASE2020.txt";
constexpr char kLaws[] = "Engine/include/sdt/laws.hpp";
constexpr char kNubaseSha[] =
    "1585a5eea86c5e17e90307c7e6e786d060049c4039e392a261ff6db977df9859";
constexpr char kLawsSha[] =
    "ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b";

[[nodiscard]] auto sha256_file(const char* path) -> std::string {
    std::ifstream in(path, std::ios::binary);
    if (!in) return {};
    HCRYPTPROV prov = 0;
    HCRYPTHASH hash = 0;
    if (!CryptAcquireContextW(&prov, nullptr, nullptr, PROV_RSA_AES,
                              CRYPT_VERIFYCONTEXT))
        return {};
    if (!CryptCreateHash(prov, CALG_SHA_256, 0, 0, &hash)) {
        CryptReleaseContext(prov, 0);
        return {};
    }
    char buf[1 << 16];
    while (in) {
        in.read(buf, sizeof(buf));
        const auto n = static_cast<DWORD>(in.gcount());
        if (n && !CryptHashData(hash, reinterpret_cast<BYTE*>(buf), n, 0)) {
            CryptDestroyHash(hash);
            CryptReleaseContext(prov, 0);
            return {};
        }
    }
    DWORD len = 32;
    BYTE digest[32];
    if (!CryptGetHashParam(hash, HP_HASHVAL, digest, &len, 0)) {
        CryptDestroyHash(hash);
        CryptReleaseContext(prov, 0);
        return {};
    }
    CryptDestroyHash(hash);
    CryptReleaseContext(prov, 0);
    static constexpr char hex[] = "0123456789abcdef";
    std::string out(64, '0');
    for (int i = 0; i < 32; ++i) {
        out[2 * i] = hex[digest[i] >> 4];
        out[2 * i + 1] = hex[digest[i] & 0xf];
    }
    return out;
}

[[nodiscard]] auto file_bytes(const char* path) -> long long {
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in) return -1;
    return static_cast<long long>(in.tellg());
}

[[nodiscard]] auto trim(std::string s) -> std::string {
    while (!s.empty() && (s.back() == ' ' || s.back() == '\r' || s.back() == '\n'))
        s.pop_back();
    size_t i = 0;
    while (i < s.size() && s[i] == ' ') ++i;
    return s.substr(i);
}

[[nodiscard]] auto field(const std::string& line, int a, int b) -> std::string {
    if (static_cast<int>(line.size()) < b) return {};
    return trim(line.substr(a - 1, b - a + 1));
}

[[nodiscard]] auto parse_abundance(const std::string& br) -> double {
    const auto pos = br.find("IS=");
    if (pos == std::string::npos) return -1.0;
    size_t i = pos + 3;
    while (i < br.size() && br[i] == ' ') ++i;
    try {
        size_t c = 0;
        return std::stod(br.substr(i), &c);
    } catch (...) {
        return -1.0;
    }
}

struct Nuclide {
    int Z = 0;
    int A = 0;
    bool misfit = false;
    std::string label;
};

struct ZA {
    int Z;
    int A;
};

// L ∪ H
constexpr ZA kExpectedMisfits[] = {
    {1, 2},   {3, 6},   {5, 10},  {7, 14},   // L
    {19, 40}, {23, 50}, {57, 138}, {71, 176}, {73, 180},  // H
};
constexpr ZA kExpectedGrips[] = {
    {11, 23}, {13, 27}, {15, 31}, {21, 45}, {23, 51}, {25, 55}, {27, 59},
};

[[nodiscard]] auto find_za(const std::vector<Nuclide>& v, int Z, int A) -> const Nuclide* {
    for (const auto& n : v)
        if (n.Z == Z && n.A == A) return &n;
    return nullptr;
}

[[nodiscard]] auto in_expected(int Z, int A) -> bool {
    for (const auto& e : kExpectedMisfits)
        if (e.Z == Z && e.A == A) return true;
    return false;
}

}  // namespace

int main() {
    std::printf("NP34b complete natural misfit census\n");
    std::printf("pre-reg: NP34b_PRE_REGISTRATION.md\n");

    const auto sha_n = sha256_file(kNubase);
    const auto sha_l = sha256_file(kLaws);
    std::printf("NUBASE sha=%s bytes=%lld\n", sha_n.c_str(), file_bytes(kNubase));
    std::printf("laws.hpp sha=%s bytes=%lld\n", sha_l.c_str(), file_bytes(kLaws));
    if (sha_n != kNubaseSha || sha_l != kLawsSha) {
        std::printf("STATUS PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION\n");
        return 2;
    }
    std::printf("PROVENANCE_PASS\n");

    if (!nuclear::triton_parity_misfit(19, 40) || nuclear::triton_parity_misfit(11, 23) ||
        nuclear::triton_parity_misfit(2, 4) || !nuclear::triton_parity_misfit(1, 2)) {
        std::printf("STATUS INSTRUMENT_OR_DOMAIN_FAILURE (validate)\n");
        return 3;
    }
    std::printf("VALIDATE_PASS\n");

    std::ifstream in(kNubase);
    if (!in) {
        std::printf("STATUS INSTRUMENT_OR_DOMAIN_FAILURE (open)\n");
        return 3;
    }

    std::vector<Nuclide> primordial_odd;
    int natural_rows = 0;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line.size() < 120) continue;
        try {
            const int A = std::stoi(field(line, 1, 3));
            const std::string zzzi = field(line, 5, 8);
            if (zzzi.size() < 4) continue;
            const int Z = std::stoi(zzzi.substr(0, 3));
            const int isomer_i = zzzi[3] - '0';
            const std::string s = field(line, 17, 17);
            const std::string T = field(line, 70, 78);
            const std::string br = line.substr(119);
            const double ab = parse_abundance(br);
            if (!(T == "stbl" || ab > 0.0)) continue;

            const bool ta180m = (Z == 73 && A == 180 && s == "m");
            if (Z == 73 && A == 180) {
                if (!ta180m) continue;
            } else if (isomer_i != 0) {
                continue;
            }

            ++natural_rows;
            if (Z % 2 == 0) continue;

            Nuclide n;
            n.Z = Z;
            n.A = A;
            n.misfit = nuclear::triton_parity_misfit(Z, A);
            n.label = field(line, 12, 16) + s;
            primordial_odd.push_back(n);
        } catch (...) {
        }
    }

    std::printf("natural_rows=%d primordial_oddZ=%zu\n", natural_rows,
                primordial_odd.size());

    int missing = 0, bad_flag = 0;
    for (const auto& e : kExpectedMisfits) {
        const Nuclide* n = find_za(primordial_odd, e.Z, e.A);
        if (!n) {
            std::printf("MISSING Z=%d A=%d\n", e.Z, e.A);
            ++missing;
        } else if (!n->misfit) {
            std::printf("EXPECTED_FALSE Z=%d A=%d %s\n", e.Z, e.A, n->label.c_str());
            ++bad_flag;
        } else {
            std::printf("OK_MISFIT Z=%d A=%d %s\n", e.Z, e.A, n->label.c_str());
        }
    }

    int missing_grip = 0, bad_grip = 0;
    for (const auto& e : kExpectedGrips) {
        const Nuclide* n = find_za(primordial_odd, e.Z, e.A);
        if (!n) {
            std::printf("MISSING_GRIP Z=%d A=%d\n", e.Z, e.A);
            ++missing_grip;
        } else if (n->misfit) {
            std::printf("GRIP_MISFIT Z=%d A=%d %s\n", e.Z, e.A, n->label.c_str());
            ++bad_grip;
        } else {
            std::printf("OK_GRIP Z=%d A=%d %s\n", e.Z, e.A, n->label.c_str());
        }
    }

    int extra = 0;
    for (const auto& n : primordial_odd) {
        if (!n.misfit) continue;
        if (!in_expected(n.Z, n.A)) {
            std::printf("EXTRA Z=%d A=%d %s\n", n.Z, n.A, n.label.c_str());
            ++extra;
        }
    }

    std::printf("missing=%d bad_flag=%d missing_grip=%d bad_grip=%d extra=%d\n",
                missing, bad_flag, missing_grip, bad_grip, extra);

    if (missing || bad_flag || missing_grip || bad_grip || extra) {
        std::printf("STATUS COMPLETE_NATURAL_MISFIT_CENSUS_EXCLUDED\n");
        return 1;
    }
    std::printf("STATUS COMPLETE_NATURAL_MISFIT_CENSUS_SURVIVES\n");
    return 0;
}
