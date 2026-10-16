// NSEQ18 natural-isotope construction check (2026-10-14). Registration: NSEQ18_RESET_ASSESSMENT_2026-10-14.md section 10 (written before this file existed).
// Usage: node nseq18_natural_1.js <repo root>. Release is read, never edited. Author: J. C. Harvey, Melbourne.
'use strict';
const fs = require('fs'), path = require('path');
const root = process.argv[2];
const js = path.join(root, 'Release', 'HTML_SDT_Website', 'js');
global.window = global;
require(path.join(js, 'nuclear-inputs.js'));
require(path.join(js, 'traction-gear-engine.js'));
const T = global.SDT_TRACTION_GEAR;
const out = [];
const log = s => { out.push(s); process.stdout.write(s + '\n'); };
const mult = { Gy: 1e9, Ty: 1e12, Py: 1e15, Ey: 1e18, Zy: 1e21, Yy: 1e24, My: 1e6 };
const stable = [], primordial = [];
for (const L of fs.readFileSync(path.join(root, 'Datasets', 'nuclear', 'NUBASE2020.txt'), 'latin1').split(/\r?\n/)) {
  if (!/^\d{3} \d{4}/.test(L) || L[7] !== '0') continue;
  const A = parseInt(L.substring(0, 3)), Z = parseInt(L.substring(4, 7));
  if (A < 2) continue;
  if (L.includes('stbl')) { stable.push([Z, A]); continue; }
  const unit = L.substring(78, 80).trim(), v = parseFloat(L.substring(69, 78).replace(/[#<>~]/g, ''));
  if (mult[unit] && Number.isFinite(v) && v * mult[unit] >= 7.0e8) primordial.push([Z, A]);
}
const byA = (a, b) => a[1] - b[1] || a[0] - b[0];
stable.sort(byA); primordial.sort(byA);
log(`NSEQ18 natural-isotope construction check (2026-10-14), engine ${T.version}; stable ground states ${stable.length}, primordial radionuclides ${primordial.length}`);
const results = [];
for (const [set, name] of [[stable, 'stable'], [primordial, 'primordial']]) {
  for (const [Z, A] of set) {
    const row = { Z, A, N: A - Z, set: name, status: '', contacts: null, maxDegree: null };
    if (!T.grammar(A, Z).valid) { row.status = 'refused: grammar'; results.push(row); continue; }
    try {
      const m = T.buildNuclide(Z, A, { Rp: 0.8414 }), e = T.evaluate(m);
      row.contacts = e.contactCount; row.maxDegree = e.maxDegree;
      const ok = e.nucleonCount === A && e.protonCount === Z && e.tractionConsistent && e.unitsOverSlots === 0;
      row.status = ok ? 'builds' : 'FAILS: ' + JSON.stringify({ n: e.nucleonCount, z: e.protonCount, t: e.tractionConsistent, over: e.unitsOverSlots });
    } catch (err) { row.status = 'refused: ' + err.message; }
    results.push(row);
  }
}
for (const name of ['stable', 'primordial']) {
  const r = results.filter(x => x.set === name), ok = r.filter(x => x.status === 'builds'), bad = r.filter(x => x.status !== 'builds');
  log(`[${name}] members ${r.length}; build and satisfy the contact rule ${ok.length}; not ${bad.length}`);
  for (const b of bad) log(`   ${b.Z},${b.A} (N=${b.N}): ${b.status}`);
  if (ok.length) log(`   contacts - A: min ${Math.min(...ok.map(x => x.contacts - x.A))}, max ${Math.max(...ok.map(x => x.contacts - x.A))}; max degree over all: ${Math.max(...ok.map(x => x.maxDegree))}`);
}
fs.writeFileSync(path.join(__dirname, 'nseq18_natural_1_rows.csv'), 'Z,A,N,set,status,contacts,maxDegree\n' + results.map(r => `${r.Z},${r.A},${r.N},${r.set},"${r.status}",${r.contacts},${r.maxDegree}`).join('\n') + '\n');
fs.writeFileSync(path.join(__dirname, 'nseq18_natural_1_results.txt'), out.join('\n') + '\n');
