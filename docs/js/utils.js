/* ── Canvas setup ── */
const canvas = document.getElementById("c");
const ctx = canvas.getContext("2d");
const dpr = window.devicePixelRatio || 1;
let W, H;

let morphT = 0;
let panX = 0, panY = 0, zoom = 0.75;
let gridScale  = 5; // y px per grid unit — updated each frame
let gridScaleX = 10; // x px per grid unit (2 × gridScale for 2:1 stretch)

let hoveredIso = null;
let hoveredZ = null;
let selectedIso = ISO.find(e => e.Z === 26 && e.A === 56);

const LEFT_W  = 230;  // left column width px
const RIGHT_W = 260;  // right column width px

// Checkbox bindings
const cbLabels      = document.getElementById("showLabels");
const cbConn        = document.getElementById("showConnections");
const cbFam         = document.getElementById("showFamilies");
const cbMag         = document.getElementById("showMagnetic");
const cbBE          = document.getElementById("showBE");
const cbSS          = document.getElementById("showSoleSpread");
const cbSC          = document.getElementById("showSoleChain");
const cbShells      = document.getElementById("showShells");
const cbUnp         = document.getElementById("showUnpaired");
const cbOddEven     = document.getElementById("showOddEven");
const cbDeut        = document.getElementById("showDeutChain");
const cbMissing     = document.getElementById("showMissing");
const cbHe3         = document.getElementById("showHe3");
const cbHe3Miss     = document.getElementById("showHe3Missing");
const cbLongLived   = document.getElementById("showLongLived");
const cbMid         = document.getElementById("showMid");
const cbShort       = document.getElementById("showShort");
const cbDecade      = document.getElementById("showDecade");
const cbTier4       = document.getElementById("showTier4");
const cbTier5       = document.getElementById("showTier5");
const cbTier6       = document.getElementById("showTier6");
const cbTier7       = document.getElementById("showTier7");
const cbTier8       = document.getElementById("showTier8");
const cbTier9       = document.getElementById("showTier9");
const cbDecayVec    = document.getElementById("showDecayVec");
const cbGoldenLine  = document.getElementById("showGoldenLine");
const cbUnstPos     = document.getElementById("showUnstPos");
const cbEnergySpine = document.getElementById('showEnergySpine');
const cbMonoSpineOv = document.getElementById('showMonoSpine');
const cbHighestGS   = document.getElementById('showHighestGS');
const cbLowestGS    = document.getElementById('showLowestGS');
const cbDeltaUE     = document.getElementById('showDeltaUE');

[cbLabels,cbConn,cbFam,cbMag,cbBE,cbSS,cbSC,cbShells,cbUnp,cbOddEven,cbDeut,cbMissing,cbHe3,cbHe3Miss,
 cbLongLived,cbMid,cbShort,cbDecade,cbTier4,cbTier5,cbTier6,cbTier7,cbTier8,cbTier9,cbDecayVec,
 cbGoldenLine, cbUnstPos
].forEach(cb => cb && cb.addEventListener("change", draw));

[cbEnergySpine, cbMonoSpineOv, cbHighestGS, cbLowestGS, cbDeltaUE]
  .forEach(cb => cb && cb.addEventListener('change', draw));

// Pan & zoom events
let dragging = false, lastX, lastY;
canvas.addEventListener("mousedown",e=>{dragging=true;lastX=e.clientX;lastY=e.clientY;});
window.addEventListener("mouseup",()=>dragging=false);
canvas.addEventListener("mousemove",e=>{
  if(dragging){panX+=e.clientX-lastX;panY+=e.clientY-lastY;lastX=e.clientX;lastY=e.clientY;draw();}
});
canvas.addEventListener("wheel",e=>{
  const f = e.deltaY > 0 ? 0.92 : 1.08;
  const mouseX = e.clientX - LEFT_W;
  const mouseY = e.clientY;
  panX += (mouseX - W/2) * (1 - f) / (zoom * f);
  panY += (mouseY - H/2) * (1 - f) / (zoom * f);
  zoom *= f;
  draw();
  e.preventDefault();
},{passive:false});

function gridPos(nd, nt) {
  const pad = 80;
  const actualU = nd - nt;
  const v = nd + nt;

  // morphT range [-1, +1]; 0 = actual/golden
  // t = -1  → Mono: shift each row by u_mono(v) → monoisotope spine is vertical
  // t = +1  → Energy: shift each row by u_E(v)  → BE/A ridge is vertical
  const fitU = getUFit(v);

  let u;
  if (morphT < 0) {
    // toward mono spine
    const uMono = fitU;
    const monoTarget = actualU - uMono;
    u = actualU + (monoTarget - actualU) * (-morphT);
  } else if (morphT > 0) {
    // toward energy spine
    const uEnergy = energySpineByV[v] ? energySpineByV[v].u : fitU;
    const energyTarget = actualU - uEnergy;
    u = actualU + (energyTarget - actualU) * morphT;
  } else {
    u = actualU;
  }

  // Use same pixel scale for both axes so columns are as tight as rows.
  const vRange = (vMax - vMin) || 1;
  const scale  = (H - pad*2) / vRange;
  const scaleX = scale * 2;
  gridScale  = scale;
  gridScaleX = scaleX;

  // Centre the u axis on screen
  const uMid = (uMax + uMin) / 2;
  const bx = W/2 + (u - uMid) * scaleX;
  const by = pad + (v - vMin) * scale;

  return {
    x: W/2 + (bx - W/2 + panX) * zoom,
    y: H/2 + (by - H/2 + panY) * zoom
  };
}

function isoPos(iso) {
  return gridPos(iso.nd, iso.nt);
}

// Helper: hex color to "r,g,b" string
function hexToRgb(hex) {
  const h = hex.replace("#","");
  return `${parseInt(h.substring(0,2),16)},${parseInt(h.substring(2,4),16)},${parseInt(h.substring(4,6),16)}`;
}

// ── Hexagon geometry helpers ─────────────────────────────────────────────────
function hexPath(ctx, cx, cy, Rx, Ry) {
  if (Ry === undefined) Ry = Rx;
  ctx.beginPath();
  for (let i = 0; i < 6; i++) {
    const a = (i * Math.PI) / 3;
    const x = cx + Rx * Math.cos(a);
    const y = cy + Ry * Math.sin(a);
    i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
  }
  ctx.closePath();
}

// Palette defined by user request
const Z_PALETTE = [
  "160,208,255", // pale blue
  "255,105,180", // hot pink
  "16,64,128",   // dark blue
  "57,255,20",   // electric green
  "255,255,255", // white
  "208,160,255", // light purple
  "255,250,205", // lemon
  "0,128,128",   // teal
  "75,0,130",    // dark purple
  "255,215,0",   // gold
  "255,64,64",   // red
  "255,140,0",   // orange
  "144,238,144", // light green
  "0,100,0",     // dark green
  "85,107,47",   // monument (dark olive)
  "255,218,185", // peach
  "251,206,177", // apricot
  "143,188,143", // grey-green
];

function isoColor(iso, alpha) {
  // Sole/Spread mode overrides
  if (cbSS.checked) {
    if (iso.isSole && iso.stable) return `rgba(230,180,70,${alpha})`;
    if (!iso.stable) return `rgba(120,80,70,${alpha})`;
    return `rgba(90,120,150,${alpha})`;
  }
  // Odd/Even A mode
  if (cbOddEven.checked) {
    if (iso.oddA) return `rgba(200,140,80,${alpha})`;
    return `rgba(80,130,170,${alpha})`;
  }
  // Unpaired electron mode
  if (cbUnp.checked && iso.unpaired >= 0) {
    const u = iso.unpaired;
    if (u === 0) return `rgba(80,130,170,${alpha})`;
    const t = Math.min(u / 7, 1);
    const r = Math.round(80 + t * 160);
    const g = Math.round(130 - t * 60);
    const b = Math.round(170 - t * 130);
    return `rgba(${r},${g},${b},${alpha})`;
  }
  // Single isotope elements are dark
  if (iso.isSole && iso.stable) {
    return `rgba(30,30,35,${alpha})`;
  }
  // Assign color from rotating palette based on Z
  const rgb = Z_PALETTE[iso.Z % Z_PALETTE.length];
  return `rgba(${rgb},${alpha})`;
}

// ─── Electron sub-shell bands (Aufbau filling order) ────────────────────────
const SHELL_BANDS = [
  { name:"1s",   zMin:1,  zMax:2,  fill:"rgba(255, 80,  50,  0.10)", stroke:"rgba(255, 80,  50,  0.55)" },
  { name:"2s",   zMin:3,  zMax:4,  fill:"rgba(255, 145, 40,  0.09)", stroke:"rgba(255, 145, 40,  0.55)" },
  { name:"2p",   zMin:5,  zMax:10, fill:"rgba(210, 230, 45,  0.08)", stroke:"rgba(210, 230, 45,  0.55)" },
  { name:"3s",   zMin:11, zMax:12, fill:"rgba(255, 235, 55,  0.09)", stroke:"rgba(255, 235, 55,  0.55)" },
  { name:"3p",   zMin:13, zMax:18, fill:"rgba(140, 55,  240, 0.08)", stroke:"rgba(160, 80,  255, 0.55)" },
  { name:"4s",   zMin:19, zMax:20, fill:"rgba(60,  130, 255, 0.08)", stroke:"rgba(80,  155, 255, 0.55)" },
  { name:"3d",   zMin:21, zMax:30, fill:"rgba(255, 80,  160, 0.08)", stroke:"rgba(255, 100, 175, 0.55)" },
  { name:"4p",   zMin:31, zMax:36, fill:"rgba(40,  210, 120, 0.08)", stroke:"rgba(50,  220, 130, 0.55)" },
  { name:"5s",   zMin:37, zMax:38, fill:"rgba(255, 55,  55,  0.08)", stroke:"rgba(255, 70,  70,  0.55)" },
  { name:"4d",   zMin:39, zMax:48, fill:"rgba(165, 70,  255, 0.08)", stroke:"rgba(185, 90,  255, 0.55)" },
  { name:"5p",   zMin:49, zMax:54, fill:"rgba(35,  220, 230, 0.08)", stroke:"rgba(45,  230, 240, 0.55)" },
  { name:"6s",   zMin:55, zMax:56, fill:"rgba(35,  180, 160, 0.09)", stroke:"rgba(45,  200, 175, 0.55)" },
  { name:"4f",   zMin:57, zMax:71, fill:"rgba(255, 185, 35,  0.08)", stroke:"rgba(255, 200, 45,  0.55)" },
  { name:"5d",   zMin:72, zMax:80, fill:"rgba(190, 240, 90,  0.08)", stroke:"rgba(200, 245, 100, 0.55)" },
  { name:"6p",   zMin:81, zMax:86, fill:"rgba(255, 105, 35,  0.09)", stroke:"rgba(255, 115, 45,  0.55)" },
  { name:"7s",   zMin:87, zMax:88, fill:"rgba(210, 40,  210, 0.09)", stroke:"rgba(225, 60,  225, 0.55)" },
  { name:"5f/6d",zMin:89, zMax:103,fill:"rgba(180, 20,  40,  0.08)", stroke:"rgba(200, 40,  60,  0.55)" },
];

// Pre-build element centroid v (used for label y-position)
const ELEM_REF_V = {};
[...new Set(ISO.map(e => e.Z))].forEach(Z => {
  const stables = ISO.filter(e => e.Z === Z && e.stable);
  const ref = stables.length > 0
    ? stables.sort((a,b) => b.abd - a.abd)[0]
    : ISO.filter(e => e.Z === Z)[0];
  if (ref) ELEM_REF_V[Z] = ref.nd + ref.nt;
});

// ─── Comprehensive unstable isotope positions ──────
const UNSTABLE_EXTRA = [
  [4,  [8,10]],
  [5,  [12,13]],
  [6,  [14,15,16]],
  [7,  [16,17,18,19]],
  [8,  [19,20,21,22]],
  [9,  [20,21,22]],
  [10, [23,24,25,26]],
  [11, [24,25,26]],
  [12, [27,28,29,30]],
  [13, [26,28,29,30]],
  [14, [31,33,34]],
  [15, [30,34,35]],
  [16, [37,38]],
  [17, [34,36,38,39,40]],
  [18, [37,41,42]],
  [19, [40,43,44,45]],
  [20, [45,47,49,50]],
  [21, [44,46,47,49]],
  [22, [45,51,52]],
  [23, [48,49,50,52,53]],
  [24, [48,55,56]],
  [25, [54,56,57]],
  [26, [52,59]],
  [27, [56,57,58,61,62]],
  [28, [57,65,66]],
  [29, [60,61,62,64,66,67]],
  [30, [62,63,69,71,72]],
  [31, [66,67,68,72,73]],
  [32, [67,71,75,77,78]],
  [33, [72,73,74,76,77,78]],
  [34, [72,73,83,84]],
  [35, [76,77,82,83,84]],
  [36, [76,79,87,88,89]],
  [37, [81,82,83,84,86,87]],
  [38, [83,84,87,89,91]],
  [39, [86,87,90,91]],
  [40, [86,87,88,95]],
  [41, [90,92,93,94,95,96]],
  [42, [90,91,92,95,99,101]],
  [43, [95,96,97,98]],
  [44, [97,103,105]],
  [45, [99,101,102,103]],
  [46, [100,101,103,107,109]],
  [47, [104,105,106,108,110,111]],
  [48, [107,111,115,117]],
  [49, [111,112,115,116]],
  [50, [110,111,117,119,121,123,125]],
  [51, [120,122,124,126,127]],
  [52, [118,119,121,127,129,132]],
  [53, [120,121,123,124,128,130,132]],
  [54, [122,123,125,127,131,133,135]],
  [55, [128,129,130,131,132,136]],
  [56, [128,129,130,135,137,139,140]],
  [57, [136,137,138,140,141]],
  [58, [134,135,137,141,143,144]],
  [59, [140,141,142,143,144]],
  [60, [141,144,145,149,151]],
  [61, [143,144,145,148,149,150,151]],
  [62, [144,145,147,153]],
  [63, [144,145,146,147,148,149,150,152,156]],
  [64, [146,148,150,151,152,153,159]],
  [65, [152,153,154,155,156,160,161]],
  [66, [154,155,156,157,158,159,161,162]],
  [67, [160,161,162,163,164]],
  [68, [160,161,162,163,165,166,167]],
  [69, [163,164,165,166,167,168,170,172]],
  [70, [162,163,164,165,166,167,168,175,176]],
  [71, [169,170,171,172,174,176,177,178,179]],
  [72, [170,171,172,173,174,175,176,177,178,179,180,181,182]],
  [73, [176,177,178,179,180,181,182,183]],
  [74, [176,177,178,179,180,181,182,183,184,185,186,187,188]],
  [75, [181,182,183,184,186,187,188]],
  [76, [182,183,184,186,187,188,189,190,191,192,193,194]],
  [77, [186,188,190,191,192,193,194,195]],
  [78, [188,189,190,191,192,193,195,197,198,199,200,201]],
  [79, [190,191,193,194,196,198,199,200,201]],
  [80, [190,191,192,193,194,195,196,197,199,200,203,205,206]],
  [81, [196,197,198,199,200,202,207,208]],
  [82, [195,196,197,198,199,200,201,202,203,205,209,210,212,214]],
  [83, [204,205,206,207,208,210,211,212,213,214]],
  [84, [207,208,210,211,212,213,214,216,218]],
  [85, [207,208,209,210,211]],
  [86, [210,211,212,218,219,220,222]],
  [87, [218,219,220,221,222,223,224]],
  [88, [220,221,222,223,224,225,226,227,230]],
  [89, [223,224,225,226,227,228,229,230]],
  [90, [226,227,228,229,230,231,232,233,234]],
  [91, [229,230,231,232,233,234,235]],
  [92, [229,230,231,232,233,234,235,236,237,240]],
  [93, [231,232,233,234,235,236,237,238,239,240]],
  [94, [231,232,233,234,235,236,237,238,239,240,241,242,243,244,246]],
  [95, [237,238,239,240,241,242,243,244,245,246]],
  [96, [238,239,240,241,242,243,244,245,246,247,248,250]],
  [97, [240,241,242,243,244,245,246,247,248,249,250,251]],
  [98, [240,241,242,243,244,245,246,247,248,249,250,251,253,254]],
  [99, [243,244,245,246,247,248,249,250,251,252,253,254,255]],
  [100,[244,245,246,247,248,249,250,251,252,253,254,255,256,257]],
  [101,[248,249,250,251,252,253,254,255,256,257,258,259,260]],
  [102,[250,251,252,253,254,255,256,257,258,259,260]],
  [103,[252,253,254,255,256,257,258,259,260,261,262]],
];
// Expand to flat [Z, A, nd, nt] array
const UNSTABLE_GRID = [];
UNSTABLE_EXTRA.forEach(([Z, As]) => {
  As.forEach(A => {
    const nd = 3*Z - A - 2;
    const nt = A - 2*Z;
    if (nd >= 0 && nt >= 0) UNSTABLE_GRID.push([Z, A, nd, nt]);
  });
});
// Also include all SHORT_LIVED and LONG_LIVED entries
[...SHORT_LIVED, ...LONG_LIVED].forEach(([Z, A,,,, nd, nt]) => {
  if (nd >= 0 && nt >= 0) UNSTABLE_GRID.push([Z, A, nd, nt]);
});

// Element name lookup
const ELEM_NAMES = {
  1:"Hydrogen",2:"Helium",3:"Lithium",4:"Beryllium",5:"Boron",6:"Carbon",7:"Nitrogen",8:"Oxygen",9:"Fluorine",10:"Neon",
  11:"Sodium",12:"Magnesium",13:"Aluminium",14:"Silicon",15:"Phosphorus",16:"Sulfur",17:"Chlorine",18:"Argon",19:"Potassium",20:"Calcium",
  21:"Scandium",22:"Titanium",23:"Vanadium",24:"Chromium",25:"Manganese",26:"Iron",27:"Cobalt",28:"Nickel",29:"Copper",30:"Zinc",
  31:"Gallium",32:"Germanium",33:"Arsenic",34:"Selenium",35:"Bromine",36:"Krypton",37:"Rubidium",38:"Strontium",39:"Yttrium",40:"Zirconium",
  41:"Niobium",42:"Molybdenum",43:"Technetium",44:"Ruthenium",45:"Rhodium",46:"Palladium",47:"Silver",48:"Cadmium",49:"Indium",50:"Tin",
  51:"Antimony",52:"Tellurium",53:"Iodine",54:"Xenon",55:"Caesium",56:"Barium",57:"Lanthanum",58:"Cerium",59:"Praseodymium",60:"Neodymium",
  61:"Promethium",62:"Samarium",63:"Europium",64:"Gadolinium",65:"Terbium",66:"Dysprosium",67:"Holmium",68:"Erbium",69:"Thulium",70:"Ytterbium",
  71:"Lutetium",72:"Hafnium",73:"Tantalum",74:"Tungsten",75:"Rhenium",76:"Osmium",77:"Iridium",78:"Platinum",79:"Gold",80:"Mercury",
  81:"Thallium",82:"Lead",83:"Bismuth",84:"Polonium",85:"Astatine",86:"Radon",87:"Francium",88:"Radium",89:"Actinium",90:"Thorium",
  91:"Protactinium",92:"Uranium",93:"Neptunium",94:"Plutonium"
};
