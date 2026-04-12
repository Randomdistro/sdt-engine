#pragma once
// ═══════════════════════════════════════════════════════════════════════
// CRUMPILER — Format Registry
// ═══════════════════════════════════════════════════════════════════════
// Central definition of all .crm* format identifiers and magics.
// Every format handler references this file — nothing else.
// ═══════════════════════════════════════════════════════════════════════

#include <cstdint>

namespace crumpiler {

// ── Crumple Format IDs ─────────────────────────────────────────────────
// Each format has a unique magic, extension, and handler.
enum class CrumpleFormat : uint8_t {
    Code    = 0,  // .crm + .crk  — semantic code compression
    Binary  = 1,  // .crb         — format-agnostic byte-string
    DocXml  = 2,  // .crmox       — OOXML (DOCX) via XML ring table
    Sheet   = 3,  // .crmxls      — OOXML (XLSX) via XML ring table
    Image   = 4,  // .crmpg       — image pixel/palette compression
    Audio   = 5,  // .crmp3       — spectral coefficient compression
    Video   = 6,  // .crmp4       — motion block compression
};

// ── Magic Numbers ──────────────────────────────────────────────────────
// 4-byte headers for each file produced by the crumpiler.

// Code-mode (semantic tokenization)
static constexpr uint32_t CRM_MAGIC  = 0x43524D31; // "CRM1" — bitstream
static constexpr uint32_t CRK_MAGIC  = 0x43524B31; // "CRK1" — legend/key

// Binary-mode (format-agnostic byte-string)
static constexpr uint32_t CRB_MAGIC  = 0x31425243; // "CRB1" — single pass
static constexpr uint32_t CRBR_MAGIC = 0x52435243; // "CRCR" — recursive wrapper

// ── Extensions ─────────────────────────────────────────────────────────
// Each format has a canonical file extension.
namespace ext {
    static constexpr const char* CRM     = ".crm";    // code bitstream
    static constexpr const char* CRK     = ".crk";    // code legend
    static constexpr const char* CRB     = ".crb";    // binary crumple
    static constexpr const char* CRMOX   = ".crmox";  // crumpled DOCX
    static constexpr const char* CRMXLS  = ".crmxls"; // crumpled XLSX
    static constexpr const char* CRMPG   = ".crmpg";  // crumpled image
    static constexpr const char* CRMP3   = ".crmp3";  // crumpled audio
    static constexpr const char* CRMP4   = ".crmp4";  // crumpled video
}

// ── Version ────────────────────────────────────────────────────────────
static constexpr uint16_t FORMAT_VERSION = 3; // v0.3.0

} // namespace crumpiler
