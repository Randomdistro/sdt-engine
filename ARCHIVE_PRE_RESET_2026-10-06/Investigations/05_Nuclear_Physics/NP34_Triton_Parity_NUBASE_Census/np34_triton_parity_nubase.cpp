// NP34 — whole-range triton_parity_misfit vs frozen NUBASE2020 (pre-registered)
#include <sdt/laws.hpp>

#include <algorithm>
#include <cmath>
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

[[nodiscard]] auto field(const std::string& line, int one_based_start, int one_based_end)
    -> std::string {
    if (static_cast<int>(line.size()) < one_based_end) return {};
    return trim(line.substr(one_based_start - 1, one_based_end - one_based_start + 1));
}

[[nodiscard]] auto parse_abundance(const std::string& br) -> double {
    const auto pos = br.find("IS=");
    if (pos == std::string::npos) return -1.0;
    size_t i = pos + 3;
    while (i < br.size() && br[i] == ' ') ++i;
    try {
        size_t consumed = 0;
        const double v = std::stod(br.substr(i), &consumed);
        return v;
    } catch (...) {
        return -1.0;
    }
}

struct Nuclide {
    int Z = 0;
    int A = 0;
    bool isomer_m = false;
    bool primordial = false;
    bool misfit = false;
    std::string label;
};

struct ZA {
    int Z;
    int A;
};

constexpr ZA kExpectedMisfits[] = {
    {19, 40}, {23, 50}, {57, 138}, {71, 176}, {73, 180},
};
constexpr ZA kExpectedGrips[] = {
    {11, 23}, {13, 27}, {15, 31}, {21, 45}, {23, 51}, {25, 55}, {27, 59},
};

[[nodiscard]] auto find_za(const std::vector<Nuclide>& v, int Z, int A) -> const Nuclide* {
    for (const auto& n : v) {
        if (n.Z == Z && n.A == A) return &n;
    }
    return nullptr;
}

}  // namespace

int main() {
    std::printf("NP34 triton parity NUBASE census\n");
    std::printf("pre-reg: NP34_PRE_REGISTRATION.md\n");

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
        nuclear::triton_parity_misfit(2, 4)) {
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
    int rows = 0;
    int skipped = 0;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line.size() < 120) {
            ++skipped;
            continue;
        }
        try {
            const int A = std::stoi(field(line, 1, 3));
            const std::string zzzi = field(line, 5, 8);
            if (zzzi.size() < 4) {
                ++skipped;
                continue;
            }
            const int Z = std::stoi(zzzi.substr(0, 3));
            const int isomer_i = zzzi[3] - '0';
            const std::string s = field(line, 17, 17);
            const std::string T = field(line, 70, 78);
            const std::string br = line.size() >= 120 ? line.substr(119) : std::string{};
            const double ab = parse_abundance(br);
            const bool natural = (T == "stbl") || (ab > 0.0);
            if (!natural) {
                ++skipped;
                continue;
            }

            const bool ta180m = (Z == 73 && A == 180 && s == "m");
            if (Z == 73 && A == 180) {
                if (!ta180m) {
                    ++skipped;
                    continue;
                }
            } else if (isomer_i != 0) {
                ++skipped;
                continue;
            }

            ++rows;
            if (Z % 2 == 0) continue;  // even-Z primordial not in adjudication set

            Nuclide n;
            n.Z = Z;
            n.A = A;
            n.isomer_m = (s == "m");
            n.primordial = true;
            n.misfit = nuclear::triton_parity_misfit(Z, A);
            n.label = field(line, 12, 16) + s;
            primordial_odd.push_back(n);
        } catch (...) {
            ++skipped;
        }
    }

    std::printf("primordial_rows_kept_for_scan=%d skipped_or_nonnatural=%d\n", rows,
                skipped);
    std::printf("primordial_oddZ_count=%zu\n", primordial_odd.size());

    int missing_misfit = 0;
    int bad_misfit_flag = 0;
    for (const auto& e : kExpectedMisfits) {
        const Nuclide* n = find_za(primordial_odd, e.Z, e.A);
        if (!n) {
            std::printf("MISSING_EXPECTED_MISFIT Z=%d A=%d\n", e.Z, e.A);
            ++missing_misfit;
        } else if (!n->misfit) {
            std::printf("EXPECTED_MISFIT_FALSE Z=%d A=%d label=%s\n", e.Z, e.A,
                        n->label.c_str());
            ++bad_misfit_flag;
        } else {
            std::printf("OK_MISFIT Z=%d A=%d label=%s\n", e.Z, e.A, n->label.c_str());
        }
    }

    int missing_grip = 0;
    int bad_grip = 0;
    for (const auto& e : kExpectedGrips) {
        const Nuclide* n = find_za(primordial_odd, e.Z, e.A);
        if (!n) {
            std::printf("MISSING_GRIP Z=%d A=%d\n", e.Z, e.A);
            ++missing_grip;
        } else if (n->misfit) {
            std::printf("GRIP_FALSELY_MISFIT Z=%d A=%d label=%s\n", e.Z, e.A,
                        n->label.c_str());
            ++bad_grip;
        } else {
            std::printf("OK_GRIP Z=%d A=%d label=%s\n", e.Z, e.A, n->label.c_str());
        }
    }

    int extra = 0;
    for (const auto& n : primordial_odd) {
        if (!n.misfit) continue;
        bool expected = false;
        for (const auto& e : kExpectedMisfits) {
            if (e.Z == n.Z && e.A == n.A) {
                expected = true;
                break;
            }
        }
        if (!expected) {
            std::printf("EXTRA_PRIMORDIAL_MISFIT Z=%d A=%d label=%s\n", n.Z, n.A,
                        n.label.c_str());
            ++extra;
        }
    }

    std::printf("missing_misfit=%d bad_misfit_flag=%d missing_grip=%d bad_grip=%d "
                "extra=%d\n",
                missing_misfit, bad_misfit_flag, missing_grip, bad_grip, extra);

    if (missing_misfit || bad_misfit_flag || missing_grip || bad_grip || extra) {
        std::printf("STATUS TRITON_PARITY_EXCLUDED\n");
        return 1;
    }
    std::printf("STATUS TRITON_PARITY_SURVIVES_WHOLE_RANGE\n");
    return 0;
}
