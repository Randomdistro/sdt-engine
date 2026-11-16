// NSEQ18 Round 2 (2026-10-14): acceptance A1-A6, O1 (binding increments), O2 (mu of even-even) on the live sequencer.
// Registration: NSEQ18_RESET_ASSESSMENT_2026-10-14.md sections 0-3 (written before this file existed).
// Usage: node nseq18_reset_2.js <repo root>. Release is read, never edited. Author: J. C. Harvey, Melbourne.
'use strict';
const fs = require('fs'), path = require('path');
const root = process.argv[2];
const js = path.join(root, 'Release', 'HTML_SDT_Website', 'js');
global.window = global;
require(path.join(js, 'nuclear-inputs.js'));
require(path.join(js, 'traction-gear-engine.js'));
const T = global.SDT_TRACTION_GEAR;
const muP = 2.79284734463;
const out = [];
const log = s => { out.push(s); process.stdout.write(s + '\n'); };

// set S (the nseq_cascade_1.js construction)
const set = [];
for (const L of fs.readFileSync(path.join(root, 'Datasets', 'nuclear', 'NUBASE2020.txt'), 'latin1').split(/\r?\n/)) {
  if (!/^\d{3} \d{4}/.test(L) || L[7] !== '0' || !L.includes('stbl')) continue;
  const A = parseInt(L.substring(0, 3)), Z = parseInt(L.substring(4, 7));
  if (A < 2 || !T.grammar(A, Z).valid) continue;
  set.push([Z, A]);
}
if (!set.some(x => x[0] === 1 && x[1] === 3)) set.push([1, 3]);
set.sort((a, b) => a[1] - b[1] || a[0] - b[0]);
log(`NSEQ18 Round 2 (2026-10-14) engine ${T.version}; set S: ${set.length} nuclides (NUBASE2020 stable, grammar-valid, plus 3H)`);

// A6 mirrors
const sameFile = f => Buffer.compare(fs.readFileSync(path.join(root, 'Release', 'HTML_SDT_Website', 'js', f)), fs.readFileSync(path.join(root, 'docs', 'js', f))) === 0;
const a6 = ['traction-gear-engine.js', 'nuclear-inputs.js'].map(f => [f, sameFile(f)]);
log(`[A6] Release vs docs byte-identical: ${a6.map(x => x[0] + '=' + x[1]).join(', ')} -> ${a6.every(x => x[1]) ? 'met' : 'NOT MET'}`);

const fail = { A1: [], A2: [], A3: [], A4: [], A5: [] };
const rows = []; const wakeMax = { split: 0, rejoin: 0, paired: 0, div: 0 };
for (const [Z, A] of set) {
  let m, m2;
  try { m = T.buildNuclide(Z, A, { Rp: 0.8414 }); m2 = T.buildNuclide(Z, A, { Rp: 0.8414 }); } catch (e) { fail.A1.push(`${Z}-${A}:${e.message}`); continue; }
  if (m.fingerprint !== m2.fingerprint) fail.A1.push(`${Z}-${A}:fingerprint`);
  const e = T.evaluate(m);
  if (e.nucleonCount !== A || e.protonCount !== Z) fail.A2.push(`${Z}-${A}:${e.nucleonCount}/${e.protonCount}`);
  const g = m.grammar;
  if (!g.seed && A >= 4 && (g.nt !== A - 2 * Z || g.nd !== 3 * Z - A - 2)) fail.A3.push(`${Z}-${A}:nt${g.nt} nd${g.nd}`);
  if (!e.tractionConsistent) fail.A4.push(`${Z}-${A}`);
  const L = m.observableLedger;
  if (L) {
    const w = L.wake; wakeMax.split = Math.max(wakeMax.split, w.splitResidual); wakeMax.rejoin = Math.max(wakeMax.rejoin, w.rejoinResidual);
    wakeMax.paired = Math.max(wakeMax.paired, w.pairedFluxResidual); wakeMax.div = Math.max(wakeMax.div, w.maximumRelativeDivergence);
    if (w.splitResidual > 1e-3 || w.rejoinResidual > 1e-3 || w.pairedFluxResidual > 1e-3 || w.maximumRelativeDivergence > 1e-2) fail.A5.push(`${Z}-${A}`);
  }
  rows.push({ Z, A, N: A - Z, B: L ? L.massDefect.calculatedBindingMeV : null, mu: L ? L.magnetic.integralMuN : null, contacts: e.contactCount, ledger: !!L });
}
for (const k of Object.keys(fail)) log(`[${k}] ${fail[k].length === 0 ? 'met for all ' + rows.length + ' builds' : 'NOT MET for ' + fail[k].length + ': ' + fail[k].slice(0, 12).join(' ')}`);
log(`     wake maxima over the set: split ${wakeMax.split.toExponential(2)}, rejoin ${wakeMax.rejoin.toExponential(2)}, paired-flux ${wakeMax.paired.toExponential(2)}, max relative divergence ${wakeMax.div.toExponential(3)} (tolerances 1e-3, 1e-3, 1e-3, 1e-2)`);
log(`     members without a zero-fit ledger (calibrated seeds): ${rows.filter(r => !r.ledger).map(r => r.Z + '-' + r.A).join(' ') || 'none'}`);

// O1
const byZ = new Map(); for (const r of rows) if (r.ledger) { if (!byZ.has(r.Z)) byZ.set(r.Z, []); byZ.get(r.Z).push(r); }
let steps = 0, bad = 0, steps1 = 0, bad1 = 0; const badList = [];
for (const [Z, arr] of byZ) {
  arr.sort((a, b) => a.A - b.A);
  for (let i = 1; i < arr.length; i++) {
    const dB = arr[i].B - arr[i - 1].B, dN = arr[i].A - arr[i - 1].A; steps++; if (!(dB > 0)) { bad++; badList.push(`${Z}:${arr[i - 1].A}->${arr[i].A}(${dB.toFixed(3)})`); }
    if (dN === 1) { steps1++; if (!(dB > 0)) bad1++; }
  }
}
log(`\n[O1] binding increments along isotope chains of S (zero-fit ledgers only): consecutive-member steps ${steps}, non-positive ${bad}; DeltaA = 1 steps ${steps1}, non-positive ${bad1} -> ${bad === 0 ? 'met' : 'NOT MET'}`);
log(`     non-positive steps: ${badList.join(' ')}`);

// O2
const ee = rows.filter(r => r.ledger && r.Z % 2 === 0 && r.N % 2 === 0);
const rho = ee.map(r => ({ Z: r.Z, A: r.A, rho: Math.abs(r.mu) / muP, mu: r.mu }));
const nOk = rho.filter(r => r.rho <= 1e-3).length; const sr = [...rho].sort((a, b) => a.rho - b.rho);
log(`\n[O2] mu of even-even members with a zero-fit ledger: n = ${ee.length}; rho = |mu|/mu_p <= 1e-3 for ${nOk} of ${ee.length}; median rho ${sr[Math.floor(sr.length / 2)].rho.toExponential(3)}, min ${sr[0].rho.toExponential(2)}, max ${sr[sr.length - 1].rho.toExponential(3)} -> ${nOk === ee.length ? 'met' : 'NOT MET'}`);
log(`     largest five: ${sr.slice(-5).reverse().map(r => `${r.Z}-${r.A} ${r.mu.toFixed(3)}muN`).join('; ')}`);
const he4 = T.buildNuclide(2, 4, { Rp: 0.8414 }); log(`     4He: ledger ${!!he4.observableLedger}${he4.observableLedger ? ', mu = ' + he4.observableLedger.magnetic.integralMuN.toFixed(4) + ' muN' : ''}`);

// spot checks
log('\n[spot] Z,A: nucleons, protons, contacts, tractionConsistent, B_calc (MeV), mu_calc (muN)');
for (const [Z, A] of [[1, 1], [1, 2], [1, 3], [2, 3], [2, 4], [8, 16], [20, 48], [26, 56], [82, 208], [92, 238]]) {
  try {
    const m = T.buildNuclide(Z, A, { Rp: 0.8414 }), e = T.evaluate(m), L = m.observableLedger;
    log(`  ${Z},${A}: ${e.nucleonCount}, ${e.protonCount}, ${e.contactCount}, ${e.tractionConsistent}, ${L ? L.massDefect.calculatedBindingMeV.toFixed(3) : 'seed fit'}, ${L ? L.magnetic.integralMuN.toFixed(4) : 'n/a'}`);
  } catch (err) { log(`  ${Z},${A}: REFUSED ${err.message}`); }
}
// closures: nuclides with magic Z and N both in S
log('\n[closures] doubly-closure candidates present in S (Z,N in {2,8,20,28,50,82,126}):');
for (const r of rows) if ([2, 8, 20, 28, 50, 82, 126].includes(r.Z) && [2, 8, 20, 28, 50, 82, 126].includes(r.N)) log(`  ${r.Z},${r.A} N=${r.N} contacts ${r.contacts} B_calc ${r.B == null ? 'seed' : r.B.toFixed(3)} mu ${r.mu == null ? 'n/a' : r.mu.toFixed(4)}`);
fs.writeFileSync(path.join(__dirname, 'nseq18_reset_2_rows.csv'), 'Z,A,N,ledger,B_calc_MeV,mu_calc_muN,contacts\n' + rows.map(r => `${r.Z},${r.A},${r.N},${r.ledger},${r.B},${r.mu},${r.contacts}`).join('\n') + '\n');
fs.writeFileSync(path.join(__dirname, 'nseq18_reset_2_results.txt'), out.join('\n') + '\n');
