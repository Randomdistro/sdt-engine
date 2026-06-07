/* ── Derived constants from ISO ── */

/* Sole elements in Z order (for chain drawing) */
const SOLE_Z = [...new Set(ISO.filter(e => e.isSole && e.stable).map(e => e.Z))].sort((a,b) => a-b);

/* Magic numbers — proton shell closures */
const MAGIC_Z = [2, 8, 20, 28, 50, 82];
const MAGIC_N = [2, 8, 20, 28, 50, 82, 126];

/* Elements that don't exist naturally (gaps) */
const GAP_Z = new Set([43, 61, 84, 85, 86, 87, 88, 89]); // Tc, Pm, Po-Ac

/* ── Build lookup set for occupied He-4 positions ── */
const occupiedAlpha = new Set();
ISO.forEach(iso => occupiedAlpha.add(iso.nd + "," + iso.nt));

/* ── Generate MISSING He-4 structures ── */
const maxNd = Math.max(...ISO.map(e => e.nd));
const maxNt = Math.max(...ISO.map(e => e.nt));
const MISSING_ALPHA = [];
for (let nd = 0; nd <= maxNd; nd++) {
  for (let nt = 0; nt <= maxNt; nt++) {
    if (occupiedAlpha.has(nd + "," + nt)) continue;
    const Z = 2 + nd + nt;
    const A = 4 + 2*nd + 3*nt;
    const N = A - Z;
    if (Z < 2 || Z > 92) continue;
    const oddZ = Z % 2 === 1;
    const oddN = N % 2 === 1;
    const isMagicZ = MAGIC_Z.includes(Z);
    const isMagicN = MAGIC_N.includes(N);
    const isGap = GAP_Z.has(Z);
    let mtype = "even-even";
    if (isGap) mtype = "gap";
    else if (isMagicZ || isMagicN) mtype = "magic";
    else if (oddZ && oddN) mtype = "odd-odd";
    else if (oddZ || oddN) mtype = "mixed";
    MISSING_ALPHA.push({ nd, nt, Z, A, N, mtype });
  }
}

/* ── He-3 grammar for existing isotopes ── */
const HE3_EXISTING = [];
const occupiedHe3 = new Set();
ISO.forEach(iso => {
  const nd3 = 3*iso.Z - iso.A - 3;
  const nt3 = iso.A - 2*iso.Z + 1;
  if (nd3 >= 0 && nt3 >= 0) {
    HE3_EXISTING.push({ ...iso, nd3, nt3 });
    occupiedHe3.add(nd3 + "," + nt3);
  }
});

/* ── Missing He-3 structures ── */
const maxNd3 = HE3_EXISTING.length > 0 ? Math.max(...HE3_EXISTING.map(e => e.nd3)) : 0;
const maxNt3 = HE3_EXISTING.length > 0 ? Math.max(...HE3_EXISTING.map(e => e.nt3)) : 0;
const MISSING_HE3 = [];
for (let nd = 0; nd <= maxNd3; nd++) {
  for (let nt = 0; nt <= maxNt3; nt++) {
    if (occupiedHe3.has(nd + "," + nt)) continue;
    const Z = 2 + nd + nt;
    const A = 3 + 2*nd + 3*nt;
    const N = A - Z;
    if (Z < 2 || Z > 92) continue;
    const oddZ = Z % 2 === 1;
    const oddN = N % 2 === 1;
    const isMagicZ = MAGIC_Z.includes(Z);
    const isMagicN = MAGIC_N.includes(N);
    const isGap = GAP_Z.has(Z);
    let mtype = "even-even";
    if (isGap) mtype = "gap";
    else if (isMagicZ || isMagicN) mtype = "magic";
    else if (oddZ && oddN) mtype = "odd-odd";
    else if (oddZ || oddN) mtype = "mixed";
    MISSING_HE3.push({ nd, nt, Z, A, N, mtype });
  }
}

/* ── Missing isotopes by half-life tier ──
   [Z, A, sym, half-life, decay, n_d, n_t, tier]
   tier: 3 = >10ky, 2 = 1k-10ky, 1 = 100-1ky */
const LONG_LIVED = [
  // Tier 3: > 10,000 years
  [4,  10, "Be", "1.39 My",  "β⁻",   0,  2,  3],
  [13, 26, "Al", "717 ky",   "EC",   11, 0,  3],
  [17, 36, "Cl", "301 ky",   "β/EC", 13, 2,  3],
  [20, 41, "Ca", "99.4 ky",  "EC",   17, 1,  3],
  [25, 53, "Mn", "3.7 My",   "EC",   20, 3,  3],
  [28, 59, "Ni", "76 ky",    "EC",   23, 3,  3],
  [26, 60, "Fe", "2.6 My",   "β⁻",   16, 8,  3],
  [34, 79, "Se", "327 ky",   "β⁻",   21, 11, 3],
  [36, 81, "Kr", "229 ky",   "EC",   25, 9,  3],
  [40, 93, "Zr", "1.61 My",  "β⁻",   25, 13, 3],
  [41, 92, "Nb", "34.7 My",  "EC",   29, 10, 3],
  [43, 97, "Tc", "4.21 My",  "EC",   30, 11, 3],
  [43, 98, "Tc", "4.2 My",   "β⁻",   29, 12, 3],
  [43, 99, "Tc", "211 ky",   "β⁻",   28, 13, 3],
  [46,107, "Pd", "6.5 My",   "β⁻",   29, 15, 3],
  [50,126, "Sn", "230 ky",   "β⁻",   22, 26, 3],
  [53,129, "I",  "15.7 My",  "β⁻",   28, 23, 3],
  [55,135, "Cs", "2.3 My",   "β⁻",   28, 25, 3],
  [62,146, "Sm", "103 My",   "α",    38, 22, 3],
  [82,205, "Pb", "17.3 My",  "EC",   39, 41, 3],
  [83,208, "Bi", "368 ky",   "EC",   39, 42, 3],
  [91,231, "Pa", "32.8 ky",  "α",    40, 49, 3],
  [92,233, "U",  "159 ky",   "α",    41, 49, 3],
  [92,236, "U",  "23.4 My",  "α",    38, 52, 3],
  // Tier 2: 1,000 - 10,000 years
  [6,  14, "C",  "5,730 y",  "β⁻",   2,  2,  2],
  [42, 93, "Mo", "4,000 y",  "EC",   31, 9,  2],
  [67,163, "Ho", "4,570 y",  "EC",   36, 29, 2],
  [67,166, "Ho", "1,200 y",  "β⁻",   33, 32, 2],
  [88,226, "Ra", "1,600 y",  "α",    36, 50, 2],
  [90,229, "Th", "7,917 y",  "α",    39, 49, 2],
  // Tier 1: 100 - 1,000 years
  [14, 32, "Si", "153 y",    "β⁻",   8,  4,  1],
  [18, 39, "Ar", "269 y",    "β⁻",   13, 3,  1],
  [28, 63, "Ni", "100 y",    "β⁻",   19, 7,  1],
  [41, 91, "Nb", "680 y",    "EC",   30, 9,  1],
  [47,108, "Ag", "418 y",    "EC",   31, 14, 1],
  [65,158, "Tb", "180 y",    "EC",   35, 28, 1],
  [77,192, "Ir", "241 y",    "IT",   37, 38, 1],
  [80,194, "Hg", "444 y",    "EC",   44, 34, 1],
  [84,209, "Po", "125 y",    "α",    41, 41, 1],
  // Tier 0: 10 - 100 years
  [18, 42, "Ar", "32.9 y",   "β⁻",   10, 6,  0],
  [22, 44, "Ti", "60 y",     "EC",   20, 0,  0],
  [36, 85, "Kr", "10.8 y",   "β⁻",   21, 13, 0],
  [38, 90, "Sr", "28.8 y",   "β⁻",   22, 14, 0],
  [41, 93, "Nb", "16.1 y",   "IT",   28, 11, 0],
  [48,113, "Cd", "14.1 y",   "β⁻",   29, 17, 0],
  [50,121, "Sn", "43.9 y",   "IT",   27, 21, 0],
  [55,137, "Cs", "30.2 y",   "β⁻",   26, 27, 0],
  [56,133, "Ba", "10.5 y",   "EC",   33, 21, 0],
  [61,145, "Pm", "17.7 y",   "EC",   36, 23, 0],
  [62,151, "Sm", "90 y",     "β⁻",   33, 27, 0],
  [63,150, "Eu", "36.9 y",   "EC",   37, 24, 0],
  [63,152, "Eu", "13.5 y",   "EC",   35, 26, 0],
  [64,148, "Gd", "75 y",     "α",    42, 20, 0],
  [65,157, "Tb", "71 y",     "EC",   36, 27, 0],
  [72,178, "Hf", "31 y",     "IT",   36, 34, 0],
  [78,193, "Pt", "50 y",     "EC",   39, 37, 0],
  [82,210, "Pb", "22.2 y",   "β⁻",   34, 46, 0],
  [83,207, "Bi", "31.6 y",   "EC",   40, 41, 0],
  [89,227, "Ac", "21.8 y",   "β⁻",   38, 49, 0],
  [92,232, "U",  "68.9 y",   "α",    42, 48, 0]
];

// Short-lived isotope tiers (tiers 4-9)
const SHORT_LIVED = [
  // ── Tier 4: 1y – 10y ──────────────────────────────────────────────────────
  [11, 22,"Na","2.60 y", "EC",  9,  0, 4],
  [26, 55,"Fe","2.73 y", "EC", 21,  3, 4],
  [27, 60,"Co","5.27 y", "β⁻",19,  6, 4],
  [51,125,"Sb","2.76 y", "β⁻",26, 23, 4],
  [55,134,"Cs","2.07 y", "β⁻",29, 24, 4],
  [61,146,"Pm","5.53 y", "EC", 35, 24, 4],
  [61,147,"Pm","2.62 y", "β⁻",34, 25, 4],
  [63,154,"Eu","8.59 y", "β⁻",33, 28, 4],
  [63,155,"Eu","4.75 y", "β⁻",32, 29, 4],
  [69,171,"Tm","1.92 y", "β⁻",34, 33, 4],
  [71,173,"Lu","1.37 y", "EC", 38, 31, 4],
  [71,174,"Lu","3.31 y", "EC", 37, 32, 4],
  [72,172,"Hf","1.87 y", "EC", 42, 28, 4],
  [73,179,"Ta","1.82 y", "EC", 38, 33, 4],
  [81,204,"Tl","3.78 y", "β⁻",37, 42, 4],
  [84,208,"Po","2.90 y", "α",  42, 40, 4],
  [88,228,"Ra","5.75 y", "β⁻",34, 52, 4],
  [98,252,"Cf","2.65 y", "α",  40, 56, 4],
  // ── Tier 5: 36d – 1y ──────────────────────────────────────────────────────
  [16, 35,"S", "87.4 d", "β⁻",11,  3, 5],
  [27, 56,"Co","77.2 d", "EC", 25,  2, 5],
  [30, 65,"Zn","244 d",  "EC", 23,  5, 5],
  [32, 68,"Ge","271 d",  "EC", 26,  4, 5],
  [34, 75,"Se","120 d",  "EC", 25,  7, 5],
  [38, 85,"Sr","64.8 d", "EC", 27,  9, 5],
  [39, 88,"Y", "107 d",  "EC", 29, 10, 5],
  [44,106,"Ru","374 d",  "β⁻",24, 18, 5],
  [48,109,"Cd","462 d",  "EC", 33, 13, 5],
  [50,113,"Sn","115 d",  "EC", 35, 13, 5],
  [53,125,"I", "59.4 d", "EC", 32, 19, 5],
  [58,139,"Ce","138 d",  "EC", 33, 23, 5],
  [64,153,"Gd","241 d",  "EC", 37, 25, 5],
  [69,170,"Tm","129 d",  "β⁻",35, 32, 5],
  [74,181,"W", "121 d",  "EC", 39, 33, 5],
  [75,183,"Re","70.0 d", "EC", 40, 33, 5],
  [76,185,"Os","93.6 d", "EC", 41, 33, 5],
  [77,192,"Ir","73.8 d", "β⁻",37, 38, 5],
  [79,195,"Au","186 d",  "EC", 40, 37, 5],
  [84,210,"Po","138 d",  "α",  40, 42, 5],
  // ── Tier 6: 3.6d – 36d ────────────────────────────────────────────────────
  [15, 32,"P", "14.3 d", "β⁻",11,  2, 6],
  [15, 33,"P", "25.4 d", "β⁻",10,  3, 6],
  [24, 51,"Cr","27.7 d", "EC", 19,  3, 6],
  [25, 52,"Mn","5.59 d", "EC", 21,  2, 6],
  [53,131,"I", "8.02 d", "β⁻",26, 25, 6],
  [56,131,"Ba","11.5 d", "EC", 35, 19, 6],
  [58,141,"Ce","32.5 d", "β⁻",31, 25, 6],
  [60,147,"Nd","11.0 d", "β⁻",31, 27, 6],
  [68,169,"Er","9.39 d", "EC", 33, 33, 6],
  [70,169,"Yb","32.0 d", "EC", 39, 29, 6],
  [83,210,"Bi","5.01 d", "β⁻",37, 44, 6],
  [88,223,"Ra","11.4 d", "α",  39, 47, 6],
  [88,224,"Ra","3.66 d", "α",  38, 48, 6],
  [89,225,"Ac","9.92 d", "α",  40, 47, 6],
  [91,233,"Pa","27.0 d", "β⁻",38, 51, 6],
  [92,237,"U", "6.75 d", "β⁻",37, 53, 6],
  // ── Tier 7: 8.64h – 3.6d ──────────────────────────────────────────────────
  [11, 24,"Na","14.96 h","β⁻", 7,  2, 7],
  [19, 42,"K", "12.36 h","β⁻",13,  4, 7],
  [21, 48,"Sc","43.67 h","β⁻",13,  6, 7],
  [40, 89,"Zr","78.41 h","β⁻",29,  9, 7],
  [42, 99,"Mo","65.94 h","β⁻",25, 15, 7],
  [45,105,"Rh","35.36 h","β⁻",28, 15, 7],
  [52,131,"Te","33.25 h","β⁻",23, 27, 7],
  [55,129,"Cs","32.06 h","β⁻",34, 19, 7],
  [57,140,"La","40.28 h","β⁻",29, 26, 7],
  [62,153,"Sm","46.50 h","β⁻",31, 29, 7],
  [67,166,"Ho","26.82 h","β⁻",33, 32, 7],
  [75,186,"Re","90.76 h","β⁻",37, 36, 7],
  [77,194,"Ir","19.28 h","β⁻",35, 40, 7],
  [81,201,"Tl","72.91 h","EC", 40, 39, 7],
  [82,212,"Pb","10.64 h","β⁻",32, 48, 7],
  [89,226,"Ac","29.37 h","β⁻",39, 48, 7],
  [90,231,"Th","25.52 h","β⁻",37, 51, 7],
  [86,211,"Rn","14.6 h", "α",  47, 39, 7],
  // ── Tier 8: 51.8min – 8.64h ───────────────────────────────────────────────
  [ 9, 18,"F", "109.8 m","EC",  7,  0, 8],
  [26, 52,"Fe","8.28 h", "EC", 26,  0, 8],
  [43, 99,"Tc","6.01 h", "IT", 28, 13, 8],
  [47,112,"Ag","3.13 h", "β⁻",27, 18, 8],
  [49,113,"In","1.66 h", "IT", 32, 15, 8],
  [81,199,"Tl","7.42 h", "EC", 42, 37, 8],
  [83,213,"Bi","45.6 m", "α",  34, 47, 8],
  [91,234,"Pa","6.70 h", "β⁻",37, 52, 8],
  [94,243,"Pu","4.96 h", "β⁻",37, 55, 8],
  // ── Tier 9: < 51.8 min (grammar-edge, fast decay) ─────────────────────────
  [ 6, 11,"C", "20.3 m", "EC",  5, -1, 9],
  [ 7, 13,"N", "9.97 m", "EC",  6, -1, 9],
  [ 8, 15,"O", "2.04 m", "EC",  9, -1, 9],
  [10, 19,"Ne","17.3 s", "β⁻",11, -1, 9],
  [12, 27,"Mg","9.46 m", "β⁻", 7,  3, 9],
  [37, 79,"Rb","22.9 m", "EC", 30,  5, 9],
  [38, 82,"Sr","25.4 d", "EC", 28,  6, 9],
  [84,211,"Po","0.516 s","α",  41, 43, 9],
  [84,212,"Po","0.299 μs","α", 40, 44, 9],
  [84,213,"Po","3.72 μs","α",  39, 45, 9],
  [88,219,"Ra","10 ms",  "α",  43, 43, 9],
  [89,217,"Ac","69 ns",  "α",  44, 39, 9],
  [90,227,"Th","18.7 d", "β⁻",35, 49, 6],
];

/* Decay vector definitions in grammar space */
const DECAY_VECTORS = {
  "α":    { dnd: -2, dnt:  0, color: "#ffd040", label: "α (−2d)" },
  "β⁻":   { dnd: +3, dnt: -2, color: "#40c8ff", label: "β⁻ (+3d,−2t)" },
  "EC":   { dnd: -3, dnt: +2, color: "#ff40ff", label: "EC (−3d,+2t)" },
  "β⁺":   { dnd: -3, dnt: +2, color: "#ff80ff", label: "β⁺ (−3d,+2t)" },
  "β/EC": { dnd: -3, dnt: +2, color: "#80e0a0", label: "β/EC" },
  "IT":   { dnd:  0, dnt:  0, color: "#ffaa40", label: "IT (same pos)" },
  "n":    { dnd: +1, dnt: -1, color: "#ff6060", label: "n (+1d,−1t)" },
  "p":    { dnd: -2, dnt: +1, color: "#ff9900", label: "p (−2d,+1t)" },
  "SF":   { dnd:  0, dnt:  0, color: "#ff4444", label: "SF" },
};

/* Build fast decay lookup from existing tier tables */
const DECAY_LOOKUP = new Map();
[...LONG_LIVED, ...SHORT_LIVED].forEach(([Z,A,,,decay]) => {
  if (decay) DECAY_LOOKUP.set(`${Z},${A}`, decay);
});

/* Stability valley for decay mode inference */
function zStable(A) { return A / (2 + 0.0146 * Math.pow(A, 2/3)); }

/* Infer decay mode from N/Z when no measured data available */
function inferDecay(Z, A) {
  if (A < 4 || Z < 2) return 'β⁻';
  const Zs = zStable(A);
  const dz = Z - Zs;
  if (A > 210 && Z > 82) return 'α';
  if (A > 150 && dz < -1.5) return 'α';
  if (dz > 2.5 && A < 60)  return 'p';
  if (dz < -2.5 && A < 30) return 'n';
  if (dz > 0.8)  return 'EC';
  if (dz < -0.5) return 'β⁻';
  return 'stable';
}

/* Enrich ISO objects with .decay field */
ISO.forEach(iso => {
  if (iso.stable) { iso.decay = '-'; return; }
  const key = `${iso.Z},${iso.A}`;
  iso.decay = DECAY_LOOKUP.get(key) || inferDecay(iso.Z, iso.A);
});

/* ISO fast lookup by (nd, nt) */
const isoByGrammar = new Map();
ISO.forEach(iso => isoByGrammar.set(`${iso.nd},${iso.nt}`, iso));

/* Follow decay chain — returns array of {from, to, decay, color} steps */
function decayChain(startIso, maxSteps, backward) {
  if (maxSteps === undefined) maxSteps = 6;
  if (backward === undefined) backward = false;
  const steps = [];
  let cur = startIso;
  for (let i = 0; i < maxSteps; i++) {
    const dv = backward ? null : DECAY_VECTORS[cur.decay];
    if (!dv && !backward) break;
    if (backward) {
      const parent = ISO.find(iso => {
        if (iso.decay === '-' || iso.decay === 'stable') return false;
        const dv2 = DECAY_VECTORS[iso.decay];
        if (!dv2) return false;
        return iso.nd + dv2.dnd === cur.nd && iso.nt + dv2.dnt === cur.nt;
      });
      if (!parent) break;
      steps.push({ from: parent, to: cur, decay: parent.decay,
                   color: (DECAY_VECTORS[parent.decay]||{color:'#888'}).color });
      cur = parent;
    } else {
      if (cur.decay === '-' || cur.decay === 'stable') break;
      const nextNd = cur.nd + dv.dnd;
      const nextNt = cur.nt + dv.dnt;
      const next = isoByGrammar.get(`${nextNd},${nextNt}`);
      if (!next) break;
      steps.push({ from: cur, to: next, decay: cur.decay, color: dv.color });
      cur = next;
      if (next.stable) break;
    }
  }
  return steps;
}

// Find ranges
const allU = ISO.map(e => e.nd - e.nt);
const allV = ISO.map(e => e.nd + e.nt);
const uMin = Math.min(...allU), uMax = Math.max(...allU);
const vMin = Math.min(...allV), vMax = Math.max(...allV);

// vVals — sorted unique v values
const vVals = [...new Set(ISO.map(e => e.nd + e.nt))].sort((a,b)=>a-b);
