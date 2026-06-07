#pragma once

/**
 * @file nuclear.hpp
 * @brief SDT Atomicus Nuclear Grammar — Exact Integer Coordinate Transform Engine
 *
 * Formalises the Atomicus "alpha grammar" as an exact, invertible integer coordinate
 * transform from standard nuclear chart coordinates (Z, A) to the SDT-native
 * deuteron/triton basis (n_d, n_t):
 *
 *   α-grammar:   n_t = A − 2Z        n_d = 3Z − A − 2
 *   H3-grammar:  n_t = A − 2Z + 1    n_d = 3Z − A − 3
 *   Inverse:     Z   = 2 + n_d + n_t   A = 4 + 2n_d + 3n_t
 *   Valid wedge: 2Z ≤ A ≤ 3Z − 2     (n_d ≥ 0 and n_t ≥ 0)
 *
 * The transform is mathematically exact — not empirical. Every alpha-valid nuclide
 * (Z, A) can be written exactly as an alpha particle plus n_d deuterons plus n_t tritons.
 *
 * Binary fission snap identities (for any ν-neutron binary split P → L + H + ν·n):
 *   ΔD = (n_d,L + n_d,H) − n_d,P = ν − 2      (algebraically exact)
 *   ΔT = (n_t,L + n_t,H) − n_t,P = −ν          (algebraically exact)
 *
 *   Clean 2n snap:    (ΔD, ΔT) = ( 0, −2)  ↔  ν = 2
 *   Adjacent 4n snap: (ΔD, ΔT) = (+2, −4)  ↔  ν = 4
 *
 * Visual overlay proxies (exact algebraic identities):
 *   Triton load  (neutron excess):   n_t = A − 2Z = N − Z
 *   Deuteron load:                   n_d = 3Z − A − 2 = 2Z − N − 2
 *   Y coordinate (element chain):    n_d + n_t = Z − 2
 *   X coordinate (horiz. displ.):    n_d − n_t = 5Z − 2A − 2
 *   Golden boundary (n_d = n_t):     A = (5Z − 2) / 2
 *   Office-pop map:                  n_t mod 2  =  A mod 2  (odd-A nuclides)
 *
 * The 287-nuclide natural isotope basis (CIAAW reconstruction) is embedded as a
 * constexpr array. Seven aggregate totals are enforced by static_assert:
 *   total_records = 287,  alpha_valid = 284,  alpha_invalid = 3 (H-1, H-2, He-3)
 *   Σ n_d = 7658,  Σ n_t = 5228,  snap_pairs = 2560,  odd_valence = 108
 *
 * DESIGN:
 *   — Pure constexpr coordinate transform. Zero physics assumptions.
 *   — No mass, no binding energy, no shell model, no empirical fitting.
 *   — Zero heap allocation. All tables are constexpr arrays.
 *   — C++20 throughout. No open-source dependencies.
 *
 * @author SDT Canonical Engine
 * @date May 2026
 */

#include <cstdio>
#include <cstring>

namespace sdt::nuclear {

// ═══════════════════════════════════════════════════════════════════════════════
//  SECTION I — TYPES
// ═══════════════════════════════════════════════════════════════════════════════

/// Result of the alpha grammar transform: (Z, A) → (n_d, n_t).
struct AlphaGrammar {
    int  n_d;     ///< deuteron count = 3Z − A − 2
    int  n_t;     ///< triton count   = A − 2Z
    bool valid;   ///< n_d ≥ 0 AND n_t ≥ 0  (lies in the alpha wedge)
};

/// Result of the H3 grammar transform (shifted: one extra triton, one fewer deuteron).
struct H3Grammar {
    int  n_d;     ///< deuteron count = 3Z − A − 3
    int  n_t;     ///< triton count   = A − 2Z + 1
    bool valid;
};

/// Compact raw entry for the natural basis table — only the nuclear chart coordinates.
struct NuclideRaw {
    int Z;   ///< atomic number
    int A;   ///< mass number
};

/// Full computed record for a single nuclide.
struct NuclideRecord {
    int         Z;
    int         A;
    const char* elem_sym;     ///< pointer into element_symbols[]
    int         n_d;          ///< alpha-grammar deuterons
    int         n_t;          ///< alpha-grammar tritons
    bool        alpha_valid;
    int         snap_pairs;   ///< ⌊n_t / 2⌋  (meaningful iff alpha_valid)
    int         odd_valence;  ///< n_t mod 2  = A mod 2  (1 = office-pop active)
    int         h3_n_d;       ///< H3-grammar deuterons
    int         h3_n_t;       ///< H3-grammar tritons
    bool        h3_valid;
};

/// Aggregate statistics across the natural basis table.
struct BasisStats {
    int total_records = 0;
    int alpha_valid   = 0;
    int alpha_invalid = 0;
    int sum_nd        = 0;    ///< Σ n_d over alpha-valid entries
    int sum_nt        = 0;    ///< Σ n_t over alpha-valid entries
    int snap_pairs    = 0;    ///< Σ ⌊n_t/2⌋ over alpha-valid entries
    int odd_valence   = 0;    ///< Σ (n_t mod 2) = count of odd-A alpha-valid nuclides
};

/// Fission snap class — determined exclusively by ν (neutron multiplicity).
enum class SnapClass : int {
    clean_2n_snap,  ///< (ΔD, ΔT) = (0, −2)   ↔  ν = 2
    adjacent_4n,    ///< (ΔD, ΔT) = (+2, −4)  ↔  ν = 4
    nu3_mixed,      ///< (ΔD, ΔT) = (+1, −3)  ↔  ν = 3
    other           ///< any other ν
};

/// Result of classifying a binary fission split.
struct SplitResult {
    int Zp, Ap;           ///< parent nuclide
    int Zl, Al;           ///< light fragment
    int Zh, Ah;           ///< heavy fragment
    int nu;               ///< prompt neutron multiplicity
    int delta_D;          ///< ΔD = ν − 2  (computed from grammar; matches by identity)
    int delta_T;          ///< ΔT = −ν     (computed from grammar; matches by identity)
    SnapClass snap_class;
};


// ═══════════════════════════════════════════════════════════════════════════════
//  SECTION II — GRAMMAR FUNCTIONS
// ═══════════════════════════════════════════════════════════════════════════════

/// Alpha grammar: (Z, A) → (n_d, n_t).
/// n_d = 3Z − A − 2,   n_t = A − 2Z.
/// Valid iff 2Z ≤ A ≤ 3Z − 2  (equivalently n_d ≥ 0 and n_t ≥ 0).
[[nodiscard]] constexpr AlphaGrammar alpha_grammar(int Z, int A) noexcept {
    const int nd = 3 * Z - A - 2;
    const int nt = A - 2 * Z;
    return {nd, nt, (nd >= 0 && nt >= 0)};
}

/// H3 grammar: shifted frame with one extra triton.
/// n_d = 3Z − A − 3,   n_t = A − 2Z + 1.
[[nodiscard]] constexpr H3Grammar h3_grammar(int Z, int A) noexcept {
    const int nd = 3 * Z - A - 3;
    const int nt = A - 2 * Z + 1;
    return {nd, nt, (nd >= 0 && nt >= 0)};
}

/// Inverse alpha grammar: (n_d, n_t) → (Z, A).
/// Z = 2 + n_d + n_t,   A = 4 + 2n_d + 3n_t.
[[nodiscard]] constexpr NuclideRaw inverse_alpha(int nd, int nt) noexcept {
    return {2 + nd + nt, 4 + 2 * nd + 3 * nt};
}

/// Compute the full NuclideRecord for any (Z, A) pair.
[[nodiscard]] constexpr NuclideRecord make_record(int Z, int A,
                                                   const char* sym) noexcept {
    const auto ag = alpha_grammar(Z, A);
    const auto h3 = h3_grammar(Z, A);
    return NuclideRecord{
        Z, A, sym,
        ag.n_d, ag.n_t, ag.valid,
        ag.valid ? ag.n_t / 2 : 0,
        ag.valid ? ag.n_t % 2 : 0,
        h3.n_d, h3.n_t, h3.valid
    };
}


// ═══════════════════════════════════════════════════════════════════════════════
//  SECTION III — ELEMENT SYMBOL TABLE
// ═══════════════════════════════════════════════════════════════════════════════

/// Element symbols indexed by Z (1 = H … 92 = U). Index 0 is unused.
inline constexpr const char* element_symbols[93] = {
    "",                                                               // 0 unused
    "H",  "He", "Li", "Be", "B",  "C",  "N",  "O",  "F",  "Ne",   // 1–10
    "Na", "Mg", "Al", "Si", "P",  "S",  "Cl", "Ar", "K",  "Ca",   // 11–20
    "Sc", "Ti", "V",  "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",   // 21–30
    "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y",  "Zr",   // 31–40
    "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn",   // 41–50
    "Sb", "Te", "I",  "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd",   // 51–60
    "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb",   // 61–70
    "Lu", "Hf", "Ta", "W",  "Re", "Os", "Ir", "Pt", "Au", "Hg",   // 71–80
    "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th",   // 81–90
    "Pa", "U",                                                        // 91–92
};

/// Return the element symbol for Z in [1..92]. Returns "" for out-of-range.
[[nodiscard]] constexpr const char* element_symbol(int Z) noexcept {
    if (Z < 1 || Z > 92) return "";
    return element_symbols[Z];
}

/// Format "El-NNN" into a caller-supplied buffer (runtime helper).
inline void nuclide_name(int Z, int A, char* buf, int buf_size) noexcept {
    std::snprintf(buf, static_cast<std::size_t>(buf_size),
                  "%s-%d", element_symbol(Z), A);
}


// ═══════════════════════════════════════════════════════════════════════════════
//  SECTION IV — NATURAL BASIS TABLE  (287 entries, CIAAW reconstruction)
//
//  Reconstructed Atomicus natural-isotope basis (CIAAW 2024):
//    — Natural-abundance entries only; bracket-only placeholders excluded
//    — Elements with no natural isotopes omitted (Tc, Pm, Po, At, Rn, Fr, Ra, Ac)
//    — Th-230 and Pa-231 excluded; U-234 retained (per reconstruction spec)
//    — Result: 287 raw records, of which 284 are alpha-valid
//    — The three exceptions: H-1, H-2, He-3 (all have n_t < 0 or n_d < 0)
//
//  AGGREGATE VERIFICATION (enforced by static_assert below):
//    total_records = 287   alpha_valid = 284   alpha_invalid = 3
//    Σ n_d = 7658          Σ n_t = 5228
//    snap_pairs = 2560     odd_valence = 108
// ═══════════════════════════════════════════════════════════════════════════════

inline constexpr NuclideRaw natural_basis[287] = {
    // ── H  (Z=1)  2 entries ───────────────────────────────────────────────────
    {1,  1},  // H-1   nd=0,  nt=-1  ← ALPHA INVALID
    {1,  2},  // H-2   nd=-1, nt=0   ← ALPHA INVALID
    // ── He (Z=2)  2 entries ───────────────────────────────────────────────────
    {2,  3},  // He-3  nd=1,  nt=-1  ← ALPHA INVALID
    {2,  4},  // He-4  (0,0)
    // ── Li (Z=3)  2 entries ───────────────────────────────────────────────────
    {3,  6},  // Li-6  (1,0)
    {3,  7},  // Li-7  (0,1)
    // ── Be (Z=4)  1 entry ─────────────────────────────────────────────────────
    {4,  9},  // Be-9  (1,1)
    // ── B  (Z=5)  2 entries ───────────────────────────────────────────────────
    {5, 10},  // B-10  (3,0)
    {5, 11},  // B-11  (2,1)
    // ── C  (Z=6)  2 entries ───────────────────────────────────────────────────
    {6, 12},  // C-12  (4,0)
    {6, 13},  // C-13  (3,1)
    // ── N  (Z=7)  2 entries ───────────────────────────────────────────────────
    {7, 14},  // N-14  (5,0)
    {7, 15},  // N-15  (4,1)
    // ── O  (Z=8)  3 entries ───────────────────────────────────────────────────
    {8, 16},  // O-16  (6,0)
    {8, 17},  // O-17  (5,1)
    {8, 18},  // O-18  (4,2)
    // ── F  (Z=9)  1 entry ─────────────────────────────────────────────────────
    {9, 19},  // F-19  (6,1)
    // ── Ne (Z=10)  3 entries ──────────────────────────────────────────────────
    {10, 20}, // Ne-20 (8,0)
    {10, 21}, // Ne-21 (7,1)
    {10, 22}, // Ne-22 (6,2)
    // ── Na (Z=11)  1 entry ────────────────────────────────────────────────────
    {11, 23}, // Na-23 (8,1)
    // ── Mg (Z=12)  3 entries ──────────────────────────────────────────────────
    {12, 24}, // Mg-24 (10,0)
    {12, 25}, // Mg-25 (9,1)
    {12, 26}, // Mg-26 (8,2)
    // ── Al (Z=13)  1 entry ────────────────────────────────────────────────────
    {13, 27}, // Al-27 (10,1)
    // ── Si (Z=14)  3 entries ──────────────────────────────────────────────────
    {14, 28}, // Si-28 (12,0)
    {14, 29}, // Si-29 (11,1)
    {14, 30}, // Si-30 (10,2)
    // ── P  (Z=15)  1 entry ────────────────────────────────────────────────────
    {15, 31}, // P-31  (12,1)
    // ── S  (Z=16)  4 entries ──────────────────────────────────────────────────
    {16, 32}, // S-32  (14,0)
    {16, 33}, // S-33  (13,1)
    {16, 34}, // S-34  (12,2)
    {16, 36}, // S-36  (10,4)
    // ── Cl (Z=17)  2 entries ──────────────────────────────────────────────────
    {17, 35}, // Cl-35 (14,1)
    {17, 37}, // Cl-37 (12,3)
    // ── Ar (Z=18)  3 entries ──────────────────────────────────────────────────
    {18, 36}, // Ar-36 (16,0)
    {18, 38}, // Ar-38 (14,2)
    {18, 40}, // Ar-40 (12,4)
    // ── K  (Z=19)  3 entries ──────────────────────────────────────────────────
    {19, 39}, // K-39  (16,1)
    {19, 40}, // K-40  (15,2)
    {19, 41}, // K-41  (14,3)
    // ── Ca (Z=20)  6 entries ──────────────────────────────────────────────────
    {20, 40}, // Ca-40 (18,0)
    {20, 42}, // Ca-42 (16,2)
    {20, 43}, // Ca-43 (15,3)
    {20, 44}, // Ca-44 (14,4)
    {20, 46}, // Ca-46 (12,6)
    {20, 48}, // Ca-48 (10,8)
    // ── Sc (Z=21)  1 entry ────────────────────────────────────────────────────
    {21, 45}, // Sc-45 (16,3)
    // ── Ti (Z=22)  5 entries ──────────────────────────────────────────────────
    {22, 46}, // Ti-46 (18,2)
    {22, 47}, // Ti-47 (17,3)
    {22, 48}, // Ti-48 (16,4)
    {22, 49}, // Ti-49 (15,5)
    {22, 50}, // Ti-50 (14,6)
    // ── V  (Z=23)  2 entries ──────────────────────────────────────────────────
    {23, 50}, // V-50  (17,4)
    {23, 51}, // V-51  (16,5)
    // ── Cr (Z=24)  4 entries ──────────────────────────────────────────────────
    {24, 50}, // Cr-50 (20,2)
    {24, 52}, // Cr-52 (18,4)
    {24, 53}, // Cr-53 (17,5)
    {24, 54}, // Cr-54 (16,6)
    // ── Mn (Z=25)  1 entry ────────────────────────────────────────────────────
    {25, 55}, // Mn-55 (18,5)
    // ── Fe (Z=26)  4 entries ──────────────────────────────────────────────────
    {26, 54}, // Fe-54 (22,2)
    {26, 56}, // Fe-56 (20,4)
    {26, 57}, // Fe-57 (19,5)
    {26, 58}, // Fe-58 (18,6)
    // ── Co (Z=27)  1 entry ────────────────────────────────────────────────────
    {27, 59}, // Co-59 (20,5)
    // ── Ni (Z=28)  5 entries ──────────────────────────────────────────────────
    {28, 58}, // Ni-58 (24,2)
    {28, 60}, // Ni-60 (22,4)
    {28, 61}, // Ni-61 (21,5)
    {28, 62}, // Ni-62 (20,6)
    {28, 64}, // Ni-64 (18,8)
    // ── Cu (Z=29)  2 entries ──────────────────────────────────────────────────
    {29, 63}, // Cu-63 (22,5)
    {29, 65}, // Cu-65 (20,7)
    // ── Zn (Z=30)  5 entries ──────────────────────────────────────────────────
    {30, 64}, // Zn-64 (24,4)
    {30, 66}, // Zn-66 (22,6)
    {30, 67}, // Zn-67 (21,7)
    {30, 68}, // Zn-68 (20,8)
    {30, 70}, // Zn-70 (18,10)
    // ── Ga (Z=31)  2 entries ──────────────────────────────────────────────────
    {31, 69}, // Ga-69 (22,7)
    {31, 71}, // Ga-71 (20,9)
    // ── Ge (Z=32)  5 entries ──────────────────────────────────────────────────
    {32, 70}, // Ge-70 (24,6)
    {32, 72}, // Ge-72 (22,8)
    {32, 73}, // Ge-73 (21,9)
    {32, 74}, // Ge-74 (20,10)
    {32, 76}, // Ge-76 (18,12)
    // ── As (Z=33)  1 entry ────────────────────────────────────────────────────
    {33, 75}, // As-75 (22,9)
    // ── Se (Z=34)  6 entries ──────────────────────────────────────────────────
    {34, 74}, // Se-74 (26,6)
    {34, 76}, // Se-76 (24,8)
    {34, 77}, // Se-77 (23,9)
    {34, 78}, // Se-78 (22,10)
    {34, 80}, // Se-80 (20,12)
    {34, 82}, // Se-82 (18,14)
    // ── Br (Z=35)  2 entries ──────────────────────────────────────────────────
    {35, 79}, // Br-79 (26,9)
    {35, 81}, // Br-81 (24,11)
    // ── Kr (Z=36)  6 entries ──────────────────────────────────────────────────
    {36, 78}, // Kr-78 (28,6)
    {36, 80}, // Kr-80 (26,8)
    {36, 82}, // Kr-82 (24,10)
    {36, 83}, // Kr-83 (23,11)
    {36, 84}, // Kr-84 (22,12)  — GSI spallation corridor
    {36, 86}, // Kr-86 (20,14)
    // ── Rb (Z=37)  2 entries ──────────────────────────────────────────────────
    {37, 85}, // Rb-85 (24,11)
    {37, 87}, // Rb-87 (22,13)  — GSI spallation corridor
    // ── Sr (Z=38)  4 entries ──────────────────────────────────────────────────
    {38, 84}, // Sr-84 (28,8)
    {38, 86}, // Sr-86 (26,10)
    {38, 87}, // Sr-87 (25,11)
    {38, 88}, // Sr-88 (24,12)
    // ── Y  (Z=39)  1 entry ────────────────────────────────────────────────────
    {39, 89}, // Y-89  (26,11)
    // ── Zr (Z=40)  5 entries ──────────────────────────────────────────────────
    {40, 90}, // Zr-90 (28,10)
    {40, 91}, // Zr-91 (27,11)
    {40, 92}, // Zr-92 (26,12)
    {40, 94}, // Zr-94 (24,14)
    {40, 96}, // Zr-96 (22,16)
    // ── Nb (Z=41)  1 entry ────────────────────────────────────────────────────
    {41, 93}, // Nb-93 (28,11)
    // ── Mo (Z=42)  7 entries ──────────────────────────────────────────────────
    {42,  92}, // Mo-92  (32,8)
    {42,  94}, // Mo-94  (30,10)
    {42,  95}, // Mo-95  (29,11)  — major fission product
    {42,  96}, // Mo-96  (28,12)
    {42,  97}, // Mo-97  (27,13)
    {42,  98}, // Mo-98  (26,14)
    {42, 100}, // Mo-100 (24,16)
    // ── Tc (Z=43): no natural isotopes (all bracket-only) ─────────────────────
    // ── Ru (Z=44)  7 entries ──────────────────────────────────────────────────
    {44,  96}, // Ru-96  (34,8)
    {44,  98}, // Ru-98  (32,10)
    {44,  99}, // Ru-99  (31,11)
    {44, 100}, // Ru-100 (30,12)
    {44, 101}, // Ru-101 (29,13)  — major fission product
    {44, 102}, // Ru-102 (28,14)
    {44, 104}, // Ru-104 (26,16)
    // ── Rh (Z=45)  1 entry ────────────────────────────────────────────────────
    {45, 103}, // Rh-103 (31,13)
    // ── Pd (Z=46)  6 entries ──────────────────────────────────────────────────
    {46, 102}, // Pd-102 (34,10)
    {46, 104}, // Pd-104 (32,12)
    {46, 105}, // Pd-105 (31,13)
    {46, 106}, // Pd-106 (30,14)
    {46, 108}, // Pd-108 (28,16)
    {46, 110}, // Pd-110 (26,18)
    // ── Ag (Z=47)  2 entries ──────────────────────────────────────────────────
    {47, 107}, // Ag-107 (32,13)
    {47, 109}, // Ag-109 (30,15)
    // ── Cd (Z=48)  8 entries ──────────────────────────────────────────────────
    {48, 106}, // Cd-106 (36,10)
    {48, 108}, // Cd-108 (34,12)
    {48, 110}, // Cd-110 (32,14)
    {48, 111}, // Cd-111 (31,15)
    {48, 112}, // Cd-112 (30,16)
    {48, 113}, // Cd-113 (29,17)
    {48, 114}, // Cd-114 (28,18)
    {48, 116}, // Cd-116 (26,20)
    // ── In (Z=49)  2 entries ──────────────────────────────────────────────────
    {49, 113}, // In-113 (32,15)
    {49, 115}, // In-115 (30,17)
    // ── Sn (Z=50)  10 entries ─────────────────────────────────────────────────
    {50, 112}, // Sn-112 (36,12)
    {50, 114}, // Sn-114 (34,14)
    {50, 115}, // Sn-115 (33,15)
    {50, 116}, // Sn-116 (32,16)
    {50, 117}, // Sn-117 (31,17)
    {50, 118}, // Sn-118 (30,18)
    {50, 119}, // Sn-119 (29,19)
    {50, 120}, // Sn-120 (28,20)
    {50, 122}, // Sn-122 (26,22)
    {50, 124}, // Sn-124 (24,24)
    // ── Sb (Z=51)  2 entries ──────────────────────────────────────────────────
    {51, 121}, // Sb-121 (30,19)
    {51, 123}, // Sb-123 (28,21)
    // ── Te (Z=52)  8 entries ──────────────────────────────────────────────────
    {52, 120}, // Te-120 (34,16)
    {52, 122}, // Te-122 (32,18)
    {52, 123}, // Te-123 (31,19)
    {52, 124}, // Te-124 (30,20)
    {52, 125}, // Te-125 (29,21)
    {52, 126}, // Te-126 (28,22)
    {52, 128}, // Te-128 (26,24)
    {52, 130}, // Te-130 (24,26)  — major fission product
    // ── I  (Z=53)  1 entry ────────────────────────────────────────────────────
    {53, 127}, // I-127  (32,21)
    // ── Xe (Z=54)  9 entries ──────────────────────────────────────────────────
    {54, 124}, // Xe-124 (36,16)
    {54, 126}, // Xe-126 (34,18)
    {54, 128}, // Xe-128 (32,20)
    {54, 129}, // Xe-129 (31,21)
    {54, 130}, // Xe-130 (30,22)
    {54, 131}, // Xe-131 (29,23)
    {54, 132}, // Xe-132 (28,24)  — major fission product
    {54, 134}, // Xe-134 (26,26)  — golden boundary: nd=nt=26
    {54, 136}, // Xe-136 (24,28)  — major fission product
    // ── Cs (Z=55)  1 entry ────────────────────────────────────────────────────
    {55, 133}, // Cs-133 (32,23)  — major fission product
    // ── Ba (Z=56)  7 entries ──────────────────────────────────────────────────
    {56, 130}, // Ba-130 (36,18)
    {56, 132}, // Ba-132 (34,20)
    {56, 134}, // Ba-134 (32,22)
    {56, 135}, // Ba-135 (31,23)
    {56, 136}, // Ba-136 (30,24)
    {56, 137}, // Ba-137 (29,25)
    {56, 138}, // Ba-138 (28,26)  — major fission product
    // ── La (Z=57)  2 entries ──────────────────────────────────────────────────
    {57, 138}, // La-138 (33,24)
    {57, 139}, // La-139 (32,25)
    // ── Ce (Z=58)  4 entries ──────────────────────────────────────────────────
    {58, 136}, // Ce-136 (36,20)
    {58, 138}, // Ce-138 (34,22)
    {58, 140}, // Ce-140 (32,24)
    {58, 142}, // Ce-142 (30,26)
    // ── Pr (Z=59)  1 entry ────────────────────────────────────────────────────
    {59, 141}, // Pr-141 (34,23)
    // ── Nd (Z=60)  7 entries ──────────────────────────────────────────────────
    {60, 142}, // Nd-142 (34,22)  — wait: 3*60-142-2=180-144=36, 142-120=22 → (36,22)
    {60, 143}, // Nd-143 (35,23)
    {60, 144}, // Nd-144 (34,24)
    {60, 145}, // Nd-145 (33,25)
    {60, 146}, // Nd-146 (32,26)
    {60, 148}, // Nd-148 (30,28)
    {60, 150}, // Nd-150 (28,30)
    // ── Pm (Z=61): no natural isotopes (all bracket-only) ─────────────────────
    // ── Sm (Z=62)  7 entries ──────────────────────────────────────────────────
    {62, 144}, // Sm-144 (40,20)
    {62, 147}, // Sm-147 (37,23)
    {62, 148}, // Sm-148 (36,24)
    {62, 149}, // Sm-149 (35,25)
    {62, 150}, // Sm-150 (34,26)
    {62, 152}, // Sm-152 (32,28)
    {62, 154}, // Sm-154 (30,30)
    // ── Eu (Z=63)  2 entries ──────────────────────────────────────────────────
    {63, 151}, // Eu-151 (36,25)
    {63, 153}, // Eu-153 (34,27)
    // ── Gd (Z=64)  7 entries ──────────────────────────────────────────────────
    {64, 152}, // Gd-152 (40,24)
    {64, 154}, // Gd-154 (38,26)
    {64, 155}, // Gd-155 (37,27)
    {64, 156}, // Gd-156 (36,28)
    {64, 157}, // Gd-157 (35,29)
    {64, 158}, // Gd-158 (34,30)
    {64, 160}, // Gd-160 (32,32)
    // ── Tb (Z=65)  1 entry ────────────────────────────────────────────────────
    {65, 159}, // Tb-159 (36,29)
    // ── Dy (Z=66)  7 entries ──────────────────────────────────────────────────
    {66, 156}, // Dy-156 (42,24)
    {66, 158}, // Dy-158 (40,26)
    {66, 160}, // Dy-160 (38,28)
    {66, 161}, // Dy-161 (37,29)
    {66, 162}, // Dy-162 (36,30)
    {66, 163}, // Dy-163 (35,31)
    {66, 164}, // Dy-164 (34,32)
    // ── Ho (Z=67)  1 entry ────────────────────────────────────────────────────
    {67, 165}, // Ho-165 (36,31)
    // ── Er (Z=68)  6 entries ──────────────────────────────────────────────────
    {68, 162}, // Er-162 (40,26)
    {68, 164}, // Er-164 (38,28)
    {68, 166}, // Er-166 (36,30)
    {68, 167}, // Er-167 (35,31)
    {68, 168}, // Er-168 (34,32)
    {68, 170}, // Er-170 (32,34)
    // ── Tm (Z=69)  1 entry ────────────────────────────────────────────────────
    {69, 169}, // Tm-169 (36,31)
    // ── Yb (Z=70)  7 entries ──────────────────────────────────────────────────
    {70, 168}, // Yb-168 (40,28)
    {70, 170}, // Yb-170 (38,30)
    {70, 171}, // Yb-171 (37,31)
    {70, 172}, // Yb-172 (36,32)
    {70, 173}, // Yb-173 (35,33)
    {70, 174}, // Yb-174 (34,34)  — golden boundary: nd=nt=34
    {70, 176}, // Yb-176 (32,36)
    // ── Lu (Z=71)  2 entries ──────────────────────────────────────────────────
    {71, 175}, // Lu-175 (36,33)
    {71, 176}, // Lu-176 (35,34)
    // ── Hf (Z=72)  6 entries ──────────────────────────────────────────────────
    {72, 174}, // Hf-174 (42,30)
    {72, 176}, // Hf-176 (40,32)
    {72, 177}, // Hf-177 (39,33)
    {72, 178}, // Hf-178 (38,34)
    {72, 179}, // Hf-179 (37,35)
    {72, 180}, // Hf-180 (36,36)  — golden boundary: nd=nt=36
    // ── Ta (Z=73)  2 entries ──────────────────────────────────────────────────
    {73, 180}, // Ta-180 (39,34)
    {73, 181}, // Ta-181 (38,35)
    // ── W  (Z=74)  5 entries ──────────────────────────────────────────────────
    {74, 180}, // W-180  (42,32)
    {74, 182}, // W-182  (40,34)
    {74, 183}, // W-183  (39,35)
    {74, 184}, // W-184  (38,36)
    {74, 186}, // W-186  (36,38)
    // ── Re (Z=75)  2 entries ──────────────────────────────────────────────────
    {75, 185}, // Re-185 (40,35)
    {75, 187}, // Re-187 (38,37)  — bound-state β decay demonstrated
    // ── Os (Z=76)  7 entries ──────────────────────────────────────────────────
    {76, 184}, // Os-184 (44,32)
    {76, 186}, // Os-186 (42,34)
    {76, 187}, // Os-187 (41,35)
    {76, 188}, // Os-188 (40,36)
    {76, 189}, // Os-189 (39,37)
    {76, 190}, // Os-190 (38,38)  — golden boundary: nd=nt=38
    {76, 192}, // Os-192 (36,40)
    // ── Ir (Z=77)  2 entries ──────────────────────────────────────────────────
    {77, 191}, // Ir-191 (40,37)
    {77, 193}, // Ir-193 (38,39)
    // ── Pt (Z=78)  6 entries ──────────────────────────────────────────────────
    {78, 190}, // Pt-190 (44,34)
    {78, 192}, // Pt-192 (42,36)
    {78, 194}, // Pt-194 (40,38)
    {78, 195}, // Pt-195 (39,39)  — golden boundary: nd=nt=39
    {78, 196}, // Pt-196 (38,40)
    {78, 198}, // Pt-198 (36,42)
    // ── Au (Z=79)  1 entry ────────────────────────────────────────────────────
    {79, 197}, // Au-197 (40,39)
    // ── Hg (Z=80)  7 entries ──────────────────────────────────────────────────
    {80, 196}, // Hg-196 (44,36)
    {80, 198}, // Hg-198 (42,38)
    {80, 199}, // Hg-199 (41,39)
    {80, 200}, // Hg-200 (40,40)  — golden boundary: nd=nt=40
    {80, 201}, // Hg-201 (39,41)
    {80, 202}, // Hg-202 (38,42)
    {80, 204}, // Hg-204 (36,44)
    // ── Tl (Z=81)  2 entries ──────────────────────────────────────────────────
    {81, 203}, // Tl-203 (40,41)
    {81, 205}, // Tl-205 (38,43)  — EC/bound-β gate experiment (2024)
    // ── Pb (Z=82)  4 entries ──────────────────────────────────────────────────
    {82, 204}, // Pb-204 (42,40)
    {82, 206}, // Pb-206 (40,42)
    {82, 207}, // Pb-207 (39,43)
    {82, 208}, // Pb-208 (38,44)
    // ── Bi (Z=83)  1 entry ────────────────────────────────────────────────────
    {83, 209}, // Bi-209 (40,43)
    // ── Po–Ac (Z=84–89): all bracket-only, no natural isotopes ────────────────
    // ── Th (Z=90)  1 entry  [Th-230 excluded per reconstruction] ──────────────
    {90, 232}, // Th-232 (36,52)
    // ── Pa (Z=91): excluded per reconstruction ────────────────────────────────
    // ── U  (Z=92)  3 entries ──────────────────────────────────────────────────
    {92, 234}, // U-234  (40,50)
    {92, 235}, // U-235  (39,51)  — primary fission fuel, ν=2.43 avg
    {92, 238}, // U-238  (36,54)  — fertile, fast fission threshold
};

/// Total entries in the natural basis table.
inline constexpr int NATURAL_BASIS_SIZE = 287;


// ═══════════════════════════════════════════════════════════════════════════════
//  SECTION V — AGGREGATE STATISTICS  (constexpr verified)
// ═══════════════════════════════════════════════════════════════════════════════

/// Compute aggregate statistics over the full 287-entry natural basis.
/// This is a constexpr reduction — evaluated at compile time.
[[nodiscard]] constexpr BasisStats compute_basis_stats() noexcept {
    BasisStats s{};
    for (const auto& raw : natural_basis) {
        ++s.total_records;
        const auto g = alpha_grammar(raw.Z, raw.A);
        if (g.valid) {
            ++s.alpha_valid;
            s.sum_nd     += g.n_d;
            s.sum_nt     += g.n_t;
            s.snap_pairs += g.n_t / 2;
            s.odd_valence+= g.n_t % 2;
        } else {
            ++s.alpha_invalid;
        }
    }
    return s;
}

/// Compile-time aggregate statistics instance.
inline constexpr BasisStats basis_stats = compute_basis_stats();

// ──────────────────────────────────────────────────────────────────────────────
// SEVEN MANDATORY COMPILE-TIME ASSERTIONS — all must pass on first build.
// If any fails, the natural_basis table contains an error in (Z, A).
// ──────────────────────────────────────────────────────────────────────────────
static_assert(basis_stats.total_records == 287,
    "natural_basis must contain exactly 287 entries (CIAAW reconstruction)");
static_assert(basis_stats.alpha_valid   == 284,
    "Exactly 284 of 287 natural isotopes must be alpha-valid");
static_assert(basis_stats.alpha_invalid ==   3,
    "Exactly 3 exceptions expected: H-1, H-2, He-3");
static_assert(basis_stats.sum_nd        == 7658,
    "Σ n_d over alpha-valid entries must equal 7658");
static_assert(basis_stats.sum_nt        == 5228,
    "Σ n_t over alpha-valid entries must equal 5228");
static_assert(basis_stats.snap_pairs    == 2560,
    "Σ ⌊n_t/2⌋ over alpha-valid entries must equal 2560");
static_assert(basis_stats.odd_valence   ==  108,
    "Count of odd-A alpha-valid entries must equal 108");


// ═══════════════════════════════════════════════════════════════════════════════
//  SECTION VI — BINARY FISSION SNAP CLASSIFIER
// ═══════════════════════════════════════════════════════════════════════════════

/// Classify a ν-neutron binary split P → L + H + ν·n using the alpha grammar.
///
/// The snap identities are algebraically exact for any valid binary split:
///   ΔD = (n_d,L + n_d,H) − n_d,P = ν − 2   (always)
///   ΔT = (n_t,L + n_t,H) − n_t,P = −ν       (always)
///
/// Classification:
///   (ΔD=0,  ΔT=−2) → clean_2n_snap  (ν=2)
///   (ΔD=+2, ΔT=−4) → adjacent_4n    (ν=4)
///   (ΔD=+1, ΔT=−3) → nu3_mixed      (ν=3)
///   otherwise       → other
///
/// @pre  Zp == Zl + Zh  (charge conservation)
/// @pre  Ap == Al + Ah + nu  (mass-energy conservation)
[[nodiscard]] constexpr SplitResult binary_split(
    int Zp, int Ap,
    int Zl, int Al,
    int Zh, int Ah,
    int nu) noexcept
{
    const auto gp = alpha_grammar(Zp, Ap);
    const auto gl = alpha_grammar(Zl, Al);
    const auto gh = alpha_grammar(Zh, Ah);

    const int dD = (gl.n_d + gh.n_d) - gp.n_d;   // must equal  nu − 2
    const int dT = (gl.n_t + gh.n_t) - gp.n_t;   // must equal −nu

    SnapClass cls;
    if      (dD ==  0 && dT == -2) cls = SnapClass::clean_2n_snap;
    else if (dD ==  2 && dT == -4) cls = SnapClass::adjacent_4n;
    else if (dD ==  1 && dT == -3) cls = SnapClass::nu3_mixed;
    else                           cls = SnapClass::other;

    return {Zp, Ap, Zl, Al, Zh, Ah, nu, dD, dT, cls};
}

/// String label for a SnapClass value.
[[nodiscard]] constexpr const char* snap_class_name(SnapClass c) noexcept {
    switch (c) {
        case SnapClass::clean_2n_snap: return "clean_2n_snap";
        case SnapClass::adjacent_4n:   return "adjacent_4n";
        case SnapClass::nu3_mixed:     return "nu3_mixed";
        default:                       return "other";
    }
}


// ═══════════════════════════════════════════════════════════════════════════════
//  SECTION VII — VISUAL OVERLAY PROXIES
// ═══════════════════════════════════════════════════════════════════════════════

namespace overlays {

/// Triton load = neutron excess = N − Z = A − 2Z.
/// This IS n_t. Heatmap: high value → neutron-rich, right half of chart.
[[nodiscard]] constexpr int triton_load(int Z, int A) noexcept {
    return A - 2 * Z;
}

/// Deuteron load = 2Z − N − 2 = 3Z − A − 2.
/// This IS n_d. Heatmap: high value → proton-rich, left half of chart.
[[nodiscard]] constexpr int deuteron_load(int Z, int A) noexcept {
    return 3 * Z - A - 2;
}

/// Y coordinate in the (x,y) = (n_d−n_t, n_d+n_t) display space.
/// y = Z − 2. Each element occupies exactly one horizontal row.
[[nodiscard]] constexpr int y_coord(int Z) noexcept {
    return Z - 2;
}

/// X coordinate in the (x,y) = (n_d−n_t, n_d+n_t) display space.
/// x = 5Z − 2A − 2. The golden boundary (n_d=n_t) lies at x=0.
[[nodiscard]] constexpr int x_coord(int Z, int A) noexcept {
    return 5 * Z - 2 * A - 2;
}

/// True iff the nuclide lies on the golden boundary n_d = n_t.
/// Equivalently: A = (5Z − 2) / 2, i.e. 2A = 5Z − 2.
[[nodiscard]] constexpr bool on_golden_boundary(int Z, int A) noexcept {
    return (3 * Z - A - 2) == (A - 2 * Z);   // n_d == n_t
}

/// Primary snap map value: ⌊n_t / 2⌋ = number of triton pairs.
[[nodiscard]] constexpr int snap_pair_count(int Z, int A) noexcept {
    const int nt = A - 2 * Z;
    return (nt >= 0) ? nt / 2 : 0;
}

/// Office-pop risk map: 1 if A is odd (odd triton valence), 0 if even.
/// The "office-pop" nuclides form the odd-A subset of the alpha-valid sheet.
[[nodiscard]] constexpr int office_pop(int Z, int A) noexcept {
    return A % 2;  // = n_t % 2  (since 2Z is always even)
}

} // namespace overlays


// ═══════════════════════════════════════════════════════════════════════════════
//  SECTION VIII — CONVENIENCE UTILITIES
// ═══════════════════════════════════════════════════════════════════════════════

/// Find an entry in natural_basis[] by (Z, A). Returns nullptr if not found.
[[nodiscard]] constexpr const NuclideRaw* lookup_basis(int Z, int A) noexcept {
    for (const auto& raw : natural_basis) {
        if (raw.Z == Z && raw.A == A) return &raw;
    }
    return nullptr;
}

/// True iff (Z, A) appears in the natural basis table.
[[nodiscard]] constexpr bool is_natural(int Z, int A) noexcept {
    return lookup_basis(Z, A) != nullptr;
}

/// Print a formatted table header for nuclide records.
inline void print_record_header() noexcept {
    std::printf("  %-8s %3s %4s  %4s %4s  %-6s  %5s %5s  h3_valid\n",
        "Nuclide", "Z", "A", "n_d", "n_t", "alpha?",
        "snap", "o-pop");
    std::printf("  %-8s %3s %4s  %4s %4s  %-6s  %5s %5s  --------\n",
        "───────", "──", "──", "────", "────", "──────",
        "─────", "─────");
}

/// Print one full NuclideRecord row.
inline void print_record(const NuclideRecord& rec) noexcept {
    char name[12];
    nuclide_name(rec.Z, rec.A, name, sizeof(name));
    std::printf("  %-8s %3d %4d  %4d %4d  %-6s  %5d %5d  %s\n",
        name, rec.Z, rec.A,
        rec.n_d, rec.n_t,
        rec.alpha_valid ? "yes" : "NO",
        rec.snap_pairs, rec.odd_valence,
        rec.h3_valid   ? "yes" : "no");
}

/// Print a full SplitResult row.
inline void print_split(const SplitResult& r) noexcept {
    char pname[12], lname[12], hname[12];
    nuclide_name(r.Zp, r.Ap, pname, sizeof(pname));
    nuclide_name(r.Zl, r.Al, lname, sizeof(lname));
    nuclide_name(r.Zh, r.Ah, hname, sizeof(hname));
    std::printf("  %-8s → %-8s + %-8s + %dn   ΔD=%+d  ΔT=%+d  [%s]\n",
        pname, lname, hname, r.nu,
        r.delta_D, r.delta_T,
        snap_class_name(r.snap_class));
}

} // namespace sdt::nuclear
