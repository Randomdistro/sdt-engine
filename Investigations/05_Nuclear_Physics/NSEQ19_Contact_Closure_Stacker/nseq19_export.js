// NSEQ19 exporter: module order and seat directions from the live engine's shell allocation, for the natural set and the triton-shell series.
// Registration: NSEQ19_REGISTRATION_2026-10-15.md. Usage: node nseq19_export.js <repo root>. Engine read only. Author: J. C. Harvey, Melbourne.
'use strict';
const fs = require('fs'), path = require('path');
const root = process.argv[2];
const js = path.join(root, 'Release', 'HTML_SDT_Website', 'js');
global.window = global;
require(path.join(js, 'nuclear-inputs.js'));
require(path.join(js, 'traction-gear-engine.js'));
const T = global.SDT_TRACTION_GEAR;
const mult = { Gy: 1e9, Ty: 1e12, Py: 1e15, Ey: 1e18, Zy: 1e21, Yy: 1e24, My: 1e6 };
const wanted = new Map();   // key -> {Z, A, tag}
const add = (Z, A, tag) => { const k = Z + ':' + A; if (!wanted.has(k)) wanted.set(k, { Z, A, tags: new Set() }); wanted.get(k).tags.add(tag); };
for (const L of fs.readFileSync(path.join(root, 'Datasets', 'nuclear', 'NUBASE2020.txt'), 'latin1').split(/\r?\n/)) {
  if (!/^\d{3} \d{4}/.test(L) || L[7] !== '0') continue;
  const A = parseInt(L.substring(0, 3)), Z = parseInt(L.substring(4, 7));
  if (A < 2) continue;
  if (L.includes('stbl')) { add(Z, A, 'stable'); continue; }
  const unit = L.substring(78, 80).trim(), v = parseFloat(L.substring(69, 78).replace(/[#<>~]/g, ''));
  if (mult[unit] && Number.isFinite(v) && v * mult[unit] >= 7.0e8) add(Z, A, 'primordial');
}
for (let nt = 0; nt <= 8; nt++) add(20 + nt, 40 + 3 * nt, 'seriesT8');
for (let nt = 0; nt <= 18; nt++) add(32 + nt, 64 + 3 * nt, 'seriesT10');
const out = [];
let n = 0;
const list = [...wanted.values()].sort((a, b) => a.A - b.A || a.Z - b.Z);
for (const { Z, A, tags } of list) {
  const g = T.grammar(A, Z);
  if (!g.valid) { out.push(`NUC ${Z} ${A} REFUSED`); out.push('END'); continue; }
  out.push(`NUC ${Z} ${A} ${g.nd} ${g.nt} ${[...tags].join(',')}`);
  if (A >= 4) {
    const al = T.universalShellAllocation(g.nd, g.nt);
    for (const sh of al.shells) {
      out.push(`SHELL ${sh.label} ${sh.species} ${sh.full ? 1 : 0} ${sh.occupancy}`);
      for (const d of sh.directions) out.push(`MOD ${sh.species} ${d[0].toFixed(9)} ${d[1].toFixed(9)} ${d[2].toFixed(9)}`);
    }
  }
  out.push('END'); n++;
}
fs.writeFileSync(path.join(__dirname, 'nseq19_nuclides.txt'), out.join('\n') + '\n');
console.log(`exported ${n} nuclides (${list.length} requested) to nseq19_nuclides.txt`);
