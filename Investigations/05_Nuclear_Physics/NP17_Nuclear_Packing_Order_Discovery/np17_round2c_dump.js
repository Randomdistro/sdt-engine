// NP17 round 2-C geometry dump (2026-10-13): per nuclide, sum of 1/d over contacts (fm^-1), loops, contact-type counts.
// Usage: node np17_round2c_dump.js <repo root>. Release is read, never edited. Author: J. C. Harvey, Melbourne.
'use strict';
const fs = require('fs'), path = require('path'), root = process.argv[2], js = path.join(root, 'Release', 'HTML_SDT_Website', 'js');
global.window = global; require(path.join(js, 'nuclear-inputs.js')); require(path.join(js, 'traction-gear-engine.js'));
const T = global.SDT_TRACTION_GEAR;
const set = [];
for (const L of fs.readFileSync(path.join(root, 'Datasets', 'nuclear', 'NUBASE2020.txt'), 'latin1').split(/\r?\n/)) {
  if (!/^\d{3} \d{4}/.test(L) || L[7] !== '0' || !L.includes('stbl')) continue;
  const A = parseInt(L.substring(0, 3)), Z = parseInt(L.substring(4, 7));
  if (A >= 4 && T.grammar(A, Z).valid) set.push([Z, A]);
}
set.sort((a, b) => a[1] - b[1] || a[0] - b[0]);
const out = ['Z,A,contacts,pn,pp,nn,loops,sum_inv_d_fm,min_d_fm,max_d_fm,contraction'];
for (const [Z, A] of set) {
  const m = T.buildNuclide(Z, A, { Rp: 0.8414 }), k = m.contractionScale || 1;
  let s = 0, pn = 0, pp = 0, nn = 0, dmin = Infinity, dmax = 0;
  for (const e of m.contacts) {
    const a = m.nodes[e.a], b = m.nodes[e.b], d = Math.hypot(a.pos[0] - b.pos[0], a.pos[1] - b.pos[1], a.pos[2] - b.pos[2]) * k;
    s += 1 / d; dmin = Math.min(dmin, d); dmax = Math.max(dmax, d);
    const t = [a.type, b.type].sort().join(''); if (t === 'np') pn++; else if (t === 'pp') pp++; else nn++;
  }
  const V = m.nodes.length, par = [...Array(V).keys()], f = x => par[x] === x ? x : (par[x] = f(par[x]));
  for (const e of m.contacts) par[f(e.a)] = f(e.b);
  const comps = new Set([...Array(V).keys()].map(f)).size, loops = m.contacts.length - V + comps;
  out.push([Z, A, m.contacts.length, pn, pp, nn, loops, s.toFixed(6), dmin.toFixed(5), dmax.toFixed(5), k].join(','));
}
fs.writeFileSync(path.join(__dirname, 'np17_round2c_geometry.csv'), out.join('\n') + '\n');
console.log('nuclides', set.length);
