// NP12b — close-pack nuclear_boundary_radius vs frozen IAEA radii (pre-registered)
#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <wincrypt.h>

#pragma comment(lib, "advapi32.lib")

using namespace sdt::laws;

namespace {

constexpr char kCsv[] =
    "Datasets/nuclear/IAEA_ground_states_radii.csv";
constexpr char kLaws[] = "Engine/include/sdt/laws.hpp";
constexpr char kCsvSha[] =
    "8aee5dc431af1e35fcb49746387b83e927b3c300e7787defbda621a08212c795";
constexpr char kLawsSha[] =
    "ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b";

[[nodiscard]] auto sha256_file(const char* path) -> std::string {
    std::ifstream in(path, std::ios::binary);
    if (!in) return {};
    HCRYPTPROV prov = 0;
    HCRYPTHASH hash = 0;
    if (!CryptAcquireContextW(&prov, nullptr, nullptr, PROV_RSA_AES,
                              CRYPT_VERIFYCONTEXT)) {
        return {};
    }
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

struct Row {
    int Z = 0;
    int N = 0;
    int A = 0;
    double R_meas_fm = 0;
};

[[nodiscard]] auto split_csv(const std::string& line) -> std::vector<std::string> {
    std::vector<std::string> out;
    std::string cur;
    std::istringstream ss(line);
    while (std::getline(ss, cur, ',')) out.push_back(cur);
    return out;
}

struct Stats {
    int n = 0;
    double sum_sq = 0;
    double sum_abs = 0;
    double max_abs = 0;
    void add(double rel) {
        ++n;
        sum_sq += rel * rel;
        const double a = std::fabs(rel);
        sum_abs += a;
        if (a > max_abs) max_abs = a;
    }
    [[nodiscard]] auto rms() const -> double {
        return n ? std::sqrt(sum_sq / n) : 0;
    }
    [[nodiscard]] auto mean_abs() const -> double {
        return n ? sum_abs / n : 0;
    }
};

}  // namespace

int main() {
    std::printf("NP12b close-pack radius audit\n");
    std::printf("pre-reg: NP12b_PRE_REGISTRATION.md\n");

    const auto sha_csv = sha256_file(kCsv);
    const auto sha_laws = sha256_file(kLaws);
    const auto bytes_csv = file_bytes(kCsv);
    const auto bytes_laws = file_bytes(kLaws);
    std::printf("CSV sha=%s bytes=%lld\n", sha_csv.c_str(), bytes_csv);
    std::printf("laws.hpp sha=%s bytes=%lld\n", sha_laws.c_str(), bytes_laws);
    if (sha_csv != kCsvSha || sha_laws != kLawsSha) {
        std::printf("STATUS PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION\n");
        return 2;
    }
    std::printf("PROVENANCE_PASS\n");

    // Instrument validation (synthetic)
    const double eta = std::numbers::pi / std::sqrt(18.0);
    const double hand_A1 = measured::R_p * 1e15 / std::cbrt(eta);
    const double hand_A4 = measured::R_p * 1e15 * std::cbrt(4.0 / eta);
    const double pred_A1 = nuclear::nuclear_boundary_radius(1) * 1e15;
    const double pred_A4 = nuclear::nuclear_boundary_radius(4) * 1e15;
    const double e1 = std::fabs(pred_A1 / hand_A1 - 1.0);
    const double e4 = std::fabs(pred_A4 / hand_A4 - 1.0);
    std::printf("VALIDATE A=1 pred=%.12f hand=%.12f rel=%.3e\n", pred_A1, hand_A1, e1);
    std::printf("VALIDATE A=4 pred=%.12f hand=%.12f rel=%.3e\n", pred_A4, hand_A4, e4);
    if (e1 > 1e-12 || e4 > 1e-12) {
        std::printf("STATUS INSTRUMENT_OR_DOMAIN_FAILURE\n");
        return 3;
    }
    std::printf("VALIDATE_PASS\n");

    std::ifstream in(kCsv);
    if (!in) {
        std::printf("STATUS INSTRUMENT_OR_DOMAIN_FAILURE (open csv)\n");
        return 3;
    }
    std::string line;
    if (!std::getline(in, line)) {
        std::printf("STATUS INSTRUMENT_OR_DOMAIN_FAILURE (empty csv)\n");
        return 3;
    }

    Stats all, a16, light, mid, heavy, zlin_a16;
    int parsed = 0;
    int skipped = 0;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto cols = split_csv(line);
        if (cols.size() < 4) {
            ++skipped;
            continue;
        }
        try {
            const int Z = std::stoi(cols[0]);
            const int N = std::stoi(cols[1]);
            if (cols[3].empty()) {
                ++skipped;
                continue;
            }
            const double R = std::stod(cols[3]);
            if (Z < 1 || N < 0 || !(R > 0.1) || !std::isfinite(R)) {
                ++skipped;
                continue;
            }
            const int A = Z + N;
            const double R_pred = nuclear::nuclear_boundary_radius(A) * 1e15;
            const double rel = R_pred / R - 1.0;
            all.add(rel);
            if (A < 16) light.add(rel);
            else if (A < 40) mid.add(rel);
            else heavy.add(rel);
            if (A >= 16) {
                a16.add(rel);
                const double Rz = static_cast<double>(Z) * measured::R_p * 1e15;
                zlin_a16.add(Rz / R - 1.0);
            }
            ++parsed;
        } catch (...) {
            ++skipped;
        }
    }

    std::printf("parsed=%d skipped=%d\n", parsed, skipped);
    std::printf("RMS_rel all=%g n=%d\n", all.rms(), all.n);
    std::printf("RMS_rel A<16=%g n=%d\n", light.rms(), light.n);
    std::printf("RMS_rel 16<=A<40=%g n=%d\n", mid.rms(), mid.n);
    std::printf("RMS_rel A>=40=%g n=%d\n", heavy.rms(), heavy.n);
    std::printf("RMS_rel A>=16=%g n=%d mean_abs=%g max_abs=%g\n", a16.rms(),
                a16.n, a16.mean_abs(), a16.max_abs);
    std::printf("DIAG retracted Z*R_p RMS_rel A>=16=%g n=%d\n", zlin_a16.rms(),
                zlin_a16.n);
    if (a16.n > 0 && zlin_a16.n > 0) {
        std::printf("DIAG Z*R_p / close-pack RMS ratio=%g\n",
                    zlin_a16.rms() / a16.rms());
    }

    if (a16.n < 50) {
        std::printf("STATUS INSTRUMENT_OR_DOMAIN_FAILURE (A>=16 n=%d)\n", a16.n);
        return 3;
    }

    const double rms = a16.rms();
    const char* status = "CLOSE_PACK_RADIUS_UNADJUDICATED";
    if (rms <= 0.08) status = "CLOSE_PACK_RADIUS_SURVIVES_THIS_REPRODUCTION";
    else if (rms > 0.20) status = "CLOSE_PACK_RADIUS_EXCLUDED";
    std::printf("STATUS %s\n", status);
    return 0;
}
