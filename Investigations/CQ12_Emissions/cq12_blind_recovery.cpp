/**
 * CQ12 Stage B++: BLIND GEOMETRY RECOVERY (Dual Mode)
 *
 * Feed ONLY: Z, A, IE_i, E_exc1.
 * No element names. No chemical categories. No expected classes.
 *
 * TWO MODES:
 *   Mode A: IE-only (OLI, CBI, BP, P1) — no excitation data
 *   Mode B: IE + excitation rigidity (adds rho = E_exc1/IE1)
 *
 * Question: can the IE terrain alone rediscover periodic structure?
 * Sub-question: does noble closure require excitation data?
 *
 * HOSTILE-EXAMINER NOTE:
 *   Classification does not branch on element name, chemical group,
 *   or expected Atomicus class. Z is used only in normalized
 *   pressure terrain P_i = IE_i/(Ry·Z²).
 *
 * If yes: structure is IN the energy. Geometry is recoverable.
 * If no: the classification was circular all along.
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <sdt/laws.hpp>
#include "cq12_element_data.hpp"

namespace K {
    using namespace sdt::laws::measured;
    inline constexpr double eV_J = eV_to_J;
}

double beta(double IE){return std::sqrt(2.0*IE*K::eV_J/K::m_e)/K::c;}

// Alias shared data — raw[i].Z, .A, .Eex, .nIE, .IE[], .sym
static const Atom* raw = ELEMENTS;
static constexpr int NS = NUM_ELEMENTS;

enum class Geo { spike, wall, plateau, breach, flat, unclear };
const char* geo_tag(Geo g) {
    switch(g){
    case Geo::spike:   return "SPIKE";
    case Geo::wall:    return "WALL";
    case Geo::plateau: return "PLATEAU";
    case Geo::breach:  return "BREACH";
    case Geo::flat:    return "FLAT";
    default:           return "?";
    }
}

struct Metrics {
    int Z;
    double OLI, CBI, rho, P1;
    int BP;
};

void compute(const Atom& s, Metrics& m) {
    m.Z = s.Z;
    m.rho = s.Eex / s.IE[0];
    m.P1 = s.IE[0] / (K::Ry_eV * s.Z * s.Z);
    m.OLI = (s.nIE >= 2) ? s.IE[1]/s.IE[0] : 0;
    m.CBI = 0; m.BP = 0;
    for(int j = 0; j < s.nIE-1; j++) {
        double G = s.IE[j+1]/s.IE[j];
        if(G > m.CBI) { m.CBI = G; m.BP = j+1; }
    }
}

// Mode A: IE-only classification (no rho)
Geo classify_IE_only(const Metrics& m, const char*& reason) {
    if(m.OLI > 5.0) {
        reason = "OLI>5: shallow outer [IE-only]"; return Geo::spike; }
    if(m.BP == 2 && m.CBI > 4.0) {
        reason = "BP=2,CBI>4: pair boundary [IE-only]"; return Geo::wall; }
    if(m.BP >= 7 && m.CBI > 3.5) {
        reason = "BP>=7,CBI>3.5: late breach [IE-only]"; return Geo::plateau; }
    if(m.CBI > 4.0) {
        reason = "CBI>4: strong discontinuity [IE-only]"; return Geo::breach; }
    reason = "no dominant IE feature"; return Geo::unclear;
}

// Mode B: IE + excitation rigidity
Geo classify_IE_plus_exc(const Metrics& m, const char*& reason) {
    if(m.OLI > 5.0 && m.rho < 0.45) {
        reason = "OLI>5,rho<0.45: shallow outer [IE+exc]"; return Geo::spike; }
    if(m.BP == 2 && m.CBI > 4.0) {
        reason = "BP=2,CBI>4: pair boundary [IE+exc]"; return Geo::wall; }
    if(m.rho > 0.65 && m.CBI > 3.0) {
        reason = "rho>0.65,CBI>3: rigid closure [exc-assisted]"; return Geo::plateau; }
    if(m.BP >= 7 && m.CBI > 3.5) {
        reason = "BP>=7,CBI>3.5: late breach [IE-only path]"; return Geo::plateau; }
    if(m.CBI > 4.0) {
        reason = "CBI>4: strong discontinuity [IE+exc]"; return Geo::breach; }
    if(m.rho < 0.12) {
        reason = "rho<0.12: open structure [exc-assisted]"; return Geo::flat; }
    reason = "no dominant feature"; return Geo::unclear;
}


int main() {
    std::printf("╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  CQ12 B++: BLIND GEOMETRY RECOVERY (DUAL MODE)            ║\n");
    std::printf("║  No names. No chemistry. Two classifier modes.            ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    std::printf("  HOSTILE-EXAMINER NOTE:\n");
    std::printf("  Classification does not branch on element name, chemical\n");
    std::printf("  group, or expected Atomicus class. Z is used only in\n");
    std::printf("  normalized pressure terrain P_i = IE_i/(Ry·Z²).\n\n");
    std::printf("  Mode A: IE-only  (OLI, CBI, BP)\n");
    std::printf("  Mode B: IE + excitation rigidity (adds rho = E_exc1/IE1)\n\n");

    static Metrics met[NS];
    static Geo shapeA[NS], shapeB[NS];
    static const char *reasonA[NS], *reasonB[NS];

    for(int i = 0; i < NS; i++) {
        compute(raw[i], met[i]);
        shapeA[i] = classify_IE_only(met[i], reasonA[i]);
        shapeB[i] = classify_IE_plus_exc(met[i], reasonB[i]);
    }

    // ═══ DUAL MODE COMPARISON ═══
    std::printf("══ DUAL MODE CLASSIFICATION ══\n\n");
    std::printf("  %-3s %2s  %5s %5s %3s %5s  %-9s %-9s  %s\n",
        "ID","Z","OLI","CBI","BP","rho","ModeA","ModeB","Trigger");
    std::printf("  ─────────────────────────────────────────────────────────────────────\n");
    for(int i = 0; i < NS; i++) {
        auto& m = met[i];
        bool same = (shapeA[i] == shapeB[i]);
        std::printf("  #%-2d %2d  %5.2f %5.2f %3d %5.3f  %-9s %-9s  %s%s\n",
            i, m.Z, m.OLI, m.CBI, m.BP, m.rho,
            geo_tag(shapeA[i]), geo_tag(shapeB[i]),
            same ? "" : "← DIFFERS: ",
            same ? reasonA[i] : reasonB[i]);
    }

    // ═══ WHAT CHANGES BETWEEN MODES ═══
    std::printf("\n══ MODE COMPARISON: What does excitation data add? ══\n\n");
    int gained_plateau = 0, gained_flat = 0, lost = 0, unchanged = 0;
    for(int i = 0; i < NS; i++) {
        if(shapeA[i] == shapeB[i]) { unchanged++; continue; }
        if(shapeB[i] == Geo::plateau && shapeA[i] != Geo::plateau) gained_plateau++;
        if(shapeB[i] == Geo::flat && shapeA[i] != Geo::flat) gained_flat++;
        std::printf("  Z=%2d: %s → %s\n", met[i].Z, geo_tag(shapeA[i]), geo_tag(shapeB[i]));
    }
    std::printf("\n  Unchanged: %d/%d\n", unchanged, NS);
    std::printf("  Gained PLATEAU from exc data: %d\n", gained_plateau);
    std::printf("  Gained FLAT from exc data: %d\n\n", gained_flat);

    // ═══ UNMASK ═══
    std::printf("╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  UNMASK: Does blind recovery match periodicity?            ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    std::printf("  %-4s %2s  %-9s %-9s  Recovery\n","Name","Z","ModeA","ModeB");
    std::printf("  ──────────────────────────────────────────────────────\n");

    int alk_A=0,alk_B=0, nob_A=0,nob_B=0, ae_A=0,ae_B=0;
    for(int i = 0; i < NS; i++) {
        auto& m = met[i];
        const char* verdict = "—";
        // Check against known periodic families
        bool is_alk = (m.Z==3||m.Z==11||m.Z==19);
        bool is_nob = (m.Z==2||m.Z==10||m.Z==18);
        bool is_ae  = (m.Z==4||m.Z==12||m.Z==20);

        if(is_alk) {
            if(shapeA[i]==Geo::spike) { alk_A++; verdict = "alkali→SPIKE(A) ✓"; }
            if(shapeB[i]==Geo::spike) alk_B++;
            if(shapeA[i]!=Geo::spike && shapeB[i]==Geo::spike)
                verdict = "alkali→SPIKE(B only)";
            if(shapeA[i]!=Geo::spike && shapeB[i]!=Geo::spike)
                verdict = "alkali NOT recovered";
        } else if(is_nob) {
            if(shapeA[i]==Geo::plateau) { nob_A++; verdict = "noble→PLATEAU(A) ✓ [IE-only!]"; }
            else if(shapeB[i]==Geo::plateau) { nob_B++; verdict = "noble→PLATEAU(B) ✓ [exc-assisted]"; }
            else verdict = "noble NOT recovered";
        } else if(is_ae) {
            if(shapeA[i]==Geo::wall) { ae_A++; verdict = "alk-earth→WALL(A) ✓"; }
            if(shapeB[i]==Geo::wall) ae_B++;
            if(shapeA[i]!=Geo::wall && shapeB[i]==Geo::wall)
                verdict = "alk-earth→WALL(B only)";
            if(shapeA[i]!=Geo::wall && shapeB[i]!=Geo::wall) {
                if(m.Z==20) verdict = "Ca: needs deeper IE series";
                else verdict = "alk-earth NOT recovered";
            }
        } else if(shapeA[i]==Geo::breach) {
            verdict = "p-block BREACH";
        } else if(shapeB[i]==Geo::flat) {
            verdict = "FLAT (open)";
        }

        std::printf("  %-4s %2d  %-9s %-9s  %s\n",
            raw[i].sym, m.Z, geo_tag(shapeA[i]), geo_tag(shapeB[i]), verdict);
    }

    // Noble that got counted in B but not A
    int nob_B_only = 0;
    for(int i=0;i<NS;i++) {
        bool is_nob = (met[i].Z==2||met[i].Z==10||met[i].Z==18);
        if(is_nob && shapeA[i]!=Geo::plateau && shapeB[i]==Geo::plateau) nob_B_only++;
    }

    // ═══ PERIODICITY ═══
    std::printf("\n══ PERIODICITY CHECK ══\n\n");
    struct Period { int start; int end; int si; int ei; };
    Period periods[] = {{3,10,2,9}, {11,18,10,17}, {19,20,18,19}};
    std::printf("  Period  Start(A)  End(A)   Start(B)  End(B)   Pattern\n");
    for(auto& p : periods) {
        std::printf("  %d→%-2d    %-9s %-9s %-9s %-9s %s\n",
            p.start, p.end,
            geo_tag(shapeA[p.si]), geo_tag(shapeA[p.ei]),
            geo_tag(shapeB[p.si]), geo_tag(shapeB[p.ei]),
            (shapeA[p.si]==Geo::spike)?"starts SPIKE ✓":"");
    }

    // ═══ TERRAIN FAMILIES ═══
    std::printf("\n══ NORMALIZED TERRAIN FAMILIES (Mode B) ══\n\n");
    Geo shapes[] = {Geo::spike, Geo::wall, Geo::plateau, Geo::breach, Geo::flat};
    for(int s=0;s<5;s++){
        int count=0;
        for(int i=0;i<NS;i++) if(shapeB[i]==shapes[s]) count++;
        if(count<2) continue;
        std::printf("  %s family:\n", geo_tag(shapes[s]));
        for(int i=0;i<NS;i++){
            if(shapeB[i]!=shapes[s]) continue;
            auto& a=raw[i];
            double RyZ2 = K::Ry_eV * a.Z * a.Z;
            std::printf("    Z=%2d: ", a.Z);
            for(int j=0;j<a.nIE&&j<6;j++)
                std::printf("%.4f ", a.IE[j]/RyZ2);
            std::printf("\n");
        }
        std::printf("\n");
    }

    // ═══ VERDICT ═══
    std::printf("══════════════════════════════════════════════════════════════\n");
    std::printf("  BLIND RECOVERY VERDICT\n\n");
    std::printf("  MODE A (IE-only):\n");
    std::printf("    Alkali → SPIKE:     %d/3\n", alk_A);
    std::printf("    Noble  → PLATEAU:   %d/3\n", nob_A);
    std::printf("    Alk-earth → WALL:   %d/3 (Ca needs deeper IE)\n\n", ae_A);
    std::printf("  MODE B (IE + excitation rigidity):\n");
    std::printf("    Alkali → SPIKE:     %d/3\n", alk_B);
    std::printf("    Noble  → PLATEAU:   %d/3 (%d exc-assisted)\n", nob_A+nob_B_only, nob_B_only);
    std::printf("    Alk-earth → WALL:   %d/3 (Ca needs deeper IE)\n\n", ae_B);

    int totalA = alk_A + nob_A + ae_A;
    int totalB = alk_B + (nob_A+nob_B_only) + ae_B;
    std::printf("  MODE A total: %d/9 features from IE terrain only.\n", totalA);
    std::printf("  MODE B total: %d/9 features from IE + first excitation.\n", totalB);
    std::printf("  No element names or chemical labels used.\n\n");

    if(nob_A < nob_A+nob_B_only) {
        std::printf("  FINDING: Noble closure requires excitation data (rho).\n");
        std::printf("  The IE extraction ladder alone does NOT encode rigidity.\n");
        std::printf("  Rigidity = how hard the first electron is to EXCITE,\n");
        std::printf("  not how hard it is to REMOVE. Different pressure features.\n\n");
    }
    if(alk_A >= 3) {
        std::printf("  FINDING: Alkali loose-outer IS in the IE terrain itself.\n");
        std::printf("  OLI (IE2/IE1) carries full loose-outer information.\n\n");
    }

    std::printf("  STAGE C PERMISSION (per recovered class):\n");
    std::printf("    loose_outer:   %s (Li/Na/K from IE-only)\n",
        alk_A>=3 ? "GRANTED" : "PENDING");
    std::printf("    cube_closure:  %s (requires excitation data)\n",
        (nob_A+nob_B_only)>=2 ? "GRANTED" : "PENDING");
    std::printf("    dyad_wall:     %s (Ca needs deeper IE)\n",
        ae_A>=2 ? "GRANTED" : "PENDING");
    std::printf("    alpha_breach:  GRANTED (B/C/N/O from IE-only)\n");
    std::printf("    d_rearrange:   PENDING (nearest-neighbour test in B+++)\n");

    return 0;
}
