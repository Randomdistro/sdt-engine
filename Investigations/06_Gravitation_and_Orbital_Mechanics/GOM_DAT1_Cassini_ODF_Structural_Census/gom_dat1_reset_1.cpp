// GOM_DAT1 blank-slate run 1 (2026-10-11). Registration: GOM_DAT1_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Structural census of the Cassini SCE1 day-157 ODF against its paired PDS3 label. VERIFICATION only: no delay, Doppler or residual is computed.
// Author: J. C. Harvey, Melbourne.
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

static const std::string RAW = "Datasets/solar_propagation_2026-08/raw/";
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
// --- SHA-256 ---
struct Sha { uint32_t h[8]; uint64_t len; uint8_t buf[64]; size_t n; };
static const uint32_t K256[64] = {0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2};
static uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
static void block(Sha& s, const uint8_t* p) { uint32_t w[64]; for (int i = 0; i < 16; ++i) w[i] = be32(p + 4 * i); for (int i = 16; i < 64; ++i) { uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3), s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10); w[i] = w[i - 16] + s0 + w[i - 7] + s1; }
    uint32_t a = s.h[0], b = s.h[1], c = s.h[2], d = s.h[3], e = s.h[4], f = s.h[5], g = s.h[6], h = s.h[7]; for (int i = 0; i < 64; ++i) { uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25), ch = (e & f) ^ (~e & g), t1 = h + S1 + ch + K256[i] + w[i], S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22), mj = (a & b) ^ (a & c) ^ (b & c), t2 = S0 + mj; h = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2; }
    s.h[0] += a; s.h[1] += b; s.h[2] += c; s.h[3] += d; s.h[4] += e; s.h[5] += f; s.h[6] += g; s.h[7] += h; }
static std::string sha256(const uint8_t* d, size_t n) { Sha s; uint32_t iv[8] = {0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19}; std::memcpy(s.h, iv, sizeof iv); size_t i = 0; for (; i + 64 <= n; i += 64) block(s, d + i); uint8_t t[128] = {0}; size_t r = n - i; std::memcpy(t, d + i, r); t[r] = 0x80; size_t tl = (r + 1 + 8 <= 64) ? 64 : 128; uint64_t bl = uint64_t(n) * 8; for (int k = 0; k < 8; ++k) t[tl - 1 - k] = uint8_t(bl >> (8 * k)); block(s, t); if (tl == 128) block(s, t + 64); char o[65]; for (int k = 0; k < 8; ++k) std::snprintf(o + 8 * k, 9, "%08x", s.h[k]); return o; }
static std::vector<uint8_t> readAll(const std::string& p) { std::ifstream f(p, std::ios::binary); return std::vector<uint8_t>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); }
static std::string readTxt(const std::string& p) { std::ifstream f(p, std::ios::binary); return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); }
static long labelInt(const std::string& L, const std::string& key) { size_t p = L.find("\n" + key); if (p == std::string::npos) return -1; p = L.find('=', p); return std::stol(L.substr(p + 1)); }
static bool c1Rule(size_t bytes, long recBytes, long fileRecords) { return (long)bytes == recBytes * fileRecords; }

int main() {
    std::printf("GOM_DAT1 blank-slate run 1 (registered in GOM_DAT1_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0;
    // D: SHA-256 known answers
    { std::string e = sha256((const uint8_t*)"", 0), a = sha256((const uint8_t*)"abc", 3); bool ok = e == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855" && a == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"; std::printf("[VD] SHA-256 known digests (empty, abc): %s\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // A: synthetic record round trip
    { uint8_t r[36]; for (int i = 0; i < 9; ++i) { uint32_t v = 0x01020304u * (i + 1) + i; r[4 * i] = v >> 24; r[4 * i + 1] = v >> 16; r[4 * i + 2] = v >> 8; r[4 * i + 3] = v; } bool ok = true; for (int i = 0; i < 9; ++i) ok = ok && be32(r + 4 * i) == 0x01020304u * (i + 1) + i; std::printf("[VA] synthetic 36-byte record round trip: %s\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    auto odf = readAll(RAW + "cassini_sce1_157_odf.odf"); std::string lbl = readTxt(RAW + "cassini_sce1_157_odf.lbl"); long recBytes = labelInt(lbl, "RECORD_BYTES"), fileRecords = labelInt(lbl, "FILE_RECORDS");
    // B: truncated fixture rejected
    { bool rej = !c1Rule(odf.size() - 7, recBytes, fileRecords); std::printf("[VB] truncated fixture (-7 bytes) rejected by the C1 rule: %s\n", rej ? "met" : "NOT MET"); if (!rej) ++fails; }
    // C: flipped byte changes hash
    const std::string manifest = "c2ea51d9b5e795bd3eb9b4f1c5174cc44325080623188dce5e01c0ea914bfaf7", lblManifest = "b27da74ca62187475860e8214c2b76b8b69af760bbe44d27aac93d1c1a5593bf";
    { auto cp = odf; cp[1000] ^= 0x01; bool rej = sha256(cp.data(), cp.size()) != manifest; std::printf("[VC] one-byte flip changes the hash and the gate rejects it: %s\n", rej ? "met" : "NOT MET"); if (!rej) ++fails; }
    if (fails) { std::printf("\nINSTRUMENT VALIDATIONS NOT MET -> INSTRUMENT INVALID\n"); return 1; } std::printf("INSTRUMENT VALIDATIONS: met\n\n");
    // manifest gate before parse
    std::string h = sha256(odf.data(), odf.size()), hl = sha256((const uint8_t*)lbl.data(), lbl.size()); auto alt = readAll(RAW + "cassini_sce1/cors_0021/sce1_157/odf/c32easc2002_157_0000k252v0.odf");
    std::printf("MANIFEST GATE: odf %s (%s), lbl %s (%s) ; the cors_0021 copy hashes %s\n", h.c_str(), h == manifest ? "match" : "MISMATCH", hl.c_str(), hl == lblManifest ? "match" : "MISMATCH", sha256(alt.data(), alt.size()) == h ? "identical" : "differently");
    if (h != manifest || hl != lblManifest) { std::printf("INSTRUMENT INVALID (hash mismatch)\n"); return 1; }
    // C1, C2
    bool c1 = c1Rule(odf.size(), recBytes, fileRecords), c2 = odf.size() % 8064 == 0;
    std::printf("[C1] file bytes %zu = RECORD_BYTES %ld x FILE_RECORDS %ld = %ld : %s (VERIFICATION)\n[C2] file bytes / 8064 = %.6f : %s ; records per block %d, blocks %zu (VERIFICATION)\n\n", odf.size(), recBytes, fileRecords, recBytes * fileRecords, c1 ? "met" : "NOT MET", odf.size() / 8064.0, c2 ? "met" : "NOT MET", 8064 / 36, odf.size() / 8064);
    // C3: group sequence from the label
    struct Tb { std::string name, obj; long rows; }; std::vector<Tb> tabs; { size_t p = 0; while (true) { p = lbl.find("\nOBJECT", p); if (p == std::string::npos) break; size_t e = lbl.find('=', p), e2 = lbl.find('\n', e); std::string obj = lbl.substr(e + 1, e2 - e - 1); while (!obj.empty() && (obj[0] == ' ')) obj.erase(0, 1); while (!obj.empty() && (obj.back() == ' ' || obj.back() == '\r')) obj.pop_back(); if (obj.find("_TABLE") != std::string::npos) { size_t n1 = lbl.find("NAME", e2), n2 = lbl.find('"', n1), n3 = lbl.find('"', n2 + 1); size_t r1 = lbl.find("ROWS", e2), r2 = lbl.find('=', r1); tabs.push_back({lbl.substr(n2 + 1, n3 - n2 - 1), obj, std::stol(lbl.substr(r2 + 1))}); } p = e2; } }
    long sumRows = 0; for (auto& t : tabs) sumRows += t.rows; std::printf("[C3] label tables: %zu, sum of ROWS = %ld against FILE_RECORDS %ld (difference %ld)\n", tabs.size(), sumRows, fileRecords, fileRecords - sumRows);
    std::map<long, int> declared = {{101, 0}, {107, 0}, {109, 0}, {2030, 0}, {105, 0}, {-1, 0}}; long pos = 0; int hdrOK = 0, hdrN = 0;
    for (auto& t : tabs) { bool isHdr = t.name.find("HEADER") != std::string::npos; if (isHdr) { const uint8_t* r = odf.data() + 36 * pos; int32_t pk = (int32_t)be32(r), sk = (int32_t)be32(r + 4); ++hdrN; bool known = declared.count(pk) > 0; hdrOK += known; std::printf("  record %5ld: %-34s primary key %6d secondary key %3d length %u start packet %u : %s\n", pos + 1, t.name.c_str(), pk, sk, be32(r + 8), be32(r + 12), known ? "declared" : "UNDECLARED -> fail closed"); } pos += t.rows; }
    // independent scan: first words that are small integers (not time tags)
    { std::map<long, int> small; for (long i = 0; i < (long)(odf.size() / 36); ++i) { int32_t w = (int32_t)be32(odf.data() + 36 * i); if (w < 100000 && w > -2) small[w]++; } std::printf("  scan of all %zu records for small-integer first words (< 100000):", odf.size() / 36); for (auto& kv : small) std::printf(" %ld x%d", kv.first, kv.second); std::printf("\n"); bool allDecl = true; for (auto& kv : small) if (!declared.count(kv.first) && kv.first != 0) allDecl = false; std::printf("  every small-integer first word is a declared key (or zero padding): %s\n", allDecl ? "yes" : "NO"); }
    std::printf("[C3] header records at the positions the label implies: %d of %d declared\n\n", hdrOK, hdrN);
    // C4: file label data record = record 2
    { const uint8_t* r = odf.data() + 36 * 1; uint32_t sys = be32(r), prog = be32(r + 4), sc = be32(r + 16), cd = be32(r + 20), ct = be32(r + 24), rd = be32(r + 28), rt = be32(r + 32); (void)sys; (void)prog;
      std::printf("[C4] file label group data: spacecraft ID %u ; creation date %06u time %06u ; reference date %u time %u\n", sc, cd, ct, rd, rt);
      std::printf("  label PRODUCT_CREATION_TIME 2002-166T02:09:18 : 2002-06-15 (day 166) 02:09:18 -> expected YYMMDD 020615, HHMMSS 020918 : %s ; label gives no spacecraft ID number: UNADJUDICATED (82 is the DSN numbering for Cassini, not read from the label) ; reference date 19500101 = EME50 convention as the label states: %s\n", (cd == 20615 && ct == 20918) ? "creation fields match" : "creation fields DIFFER", rd == 19500101 ? "yes" : "NO"); }
    std::printf("\n[C5] ODF alone yields an admissible propagation residual: PENDING_DATA (this loop computes no residual).\n");
    return 0;
}
