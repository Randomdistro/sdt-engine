// Cascade run C2 (2026-10-11): the live sequencer's zero-fit mass-defect ledger (NSEQ18-WEB-1) over every
// NUBASE2020 stable ground state the grammar admits, single pass. Registration: CASCADE_PRE_REGISTRATION_2026-10-11.md.
// Usage: node nseq_cascade_1.js <repo root>. Release is read, never edited. Author: J. C. Harvey, Melbourne.
'use strict';
const fs = require('fs'), path = require('path');
const root = process.argv[2];
const js = path.join(root, 'Release', 'HTML_SDT_Website', 'js');
global.window = global;
require(path.join(js, 'nuclear-inputs.js'));
require(path.join(js, 'traction-gear-engine.js'));
const T = global.SDT_TRACTION_GEAR;

// masses in u, one conversion (np17_reset_1 attempt-2 convention)
const u_kg = 1.66053906892e-27, u_MeV22 = 931.49410372, u_keV_ame = 931494.10242;     // [MEASURED-INPUT] CODATA 2022 / AME2020
const mp = 1.67262192595e-27 / u_kg * u_MeV22, me = 9.1093837015e-31 / u_kg * u_MeV22, mn = 1.67492750056e-27 / u_kg * u_MeV22; // laws.hpp measured::
const muP = 2.79284734463;                                                                // measured proton moment, nucleon scale for a measured zero

const ame = new Map();
for (const L of fs.readFileSync(path.join(root, 'Datasets', 'nuclear', 'AME2020_mass_excess.txt'), 'latin1').split(/\r?\n/)) {
  if (L.length < 42 || !L.substring(4, 9).trim()) continue;
  const Z = parseInt(L.substring(9, 14)), A = parseInt(L.substring(14, 19)), ex = L.substring(28, 42);
  if (Number.isFinite(Z) && Number.isFinite(A) && /\d/.test(ex) && !ex.includes('#')) ame.set(`${Z}:${A}`, parseFloat(ex));
}
const Matom = (Z, A) => (A + ame.get(`${Z}:${A}`) / u_keV_ame) * u_MeV22;
const Bnative = (Z, A) => A * (mp + me) - Matom(Z, A);                     // {A p, A e} ~ {A p, N e} + fielded binding (eV-keV)
const Bpn = (Z, A) => Z * (mp + me) + (A - Z) * mn - Matom(Z, A);          // {Z H-atoms, N n}: the engine preset's list

const set = [];
for (const L of fs.readFileSync(path.join(root, 'Datasets', 'nuclear', 'NUBASE2020.txt'), 'latin1').split(/\r?\n/)) {
  if (!/^\d{3} \d{4}/.test(L) || L[7] !== '0' || !L.includes('stbl')) continue;
  const A = parseInt(L.substring(0, 3)), Z = parseInt(L.substring(4, 7));
  if (A < 2) continue;
  if (!T.grammar(A, Z).valid) continue;
  set.push([Z, A]);
}
for (const s of [[1, 3]]) if (!set.some(x => x[0] === s[0] && x[1] === s[1])) set.push(s);   // registered seed (3H, not stable)
set.sort((a, b) => a[1] - b[1] || a[0] - b[0]);

const band = r => !Number.isFinite(r) ? 'B7' : r <= 1e-3 ? 'B1' : r <= 1e-2 ? 'B2' : r <= 3e-2 ? 'B3' : r <= 0.10 ? 'B4' : r <= 0.30 ? 'B5' : r <= 2 ? 'B6' : 'B7';
const out = [];
const log = s => { out.push(s); process.stdout.write(s + '\n'); };
log('NSEQ cascade C2 (2026-10-11) engine ' + T.version + ' ; nuclides in set: ' + set.length);
// validation: 1H defect against {p,e} (13.598 eV) and deuteron native list (1.442246 MeV, NP17 reset V4)
const vH = Bnative(1, 1) * 1e6, vD = Bnative(1, 2);
log(`[V1] 1H defect {p,e} = ${vH.toFixed(3)} eV -> ${Math.abs(vH - 13.598) < 0.5 ? 'met' : 'NOT MET'} ; [V2] d {2p,1e} = ${vD.toFixed(6)} MeV -> ${Math.abs(vD - 1.442246) < 1e-5 ? 'met' : 'NOT MET'}`);
if (Math.abs(vH - 13.598) >= 0.5 || Math.abs(vD - 1.442246) >= 1e-5) process.exit(1);
log('Z,A,N,status,calc_MeV,B_native,ratio_native,band_native,B_pn,ratio_pn,band_pn,contacts');
const rows = [];
for (const [Z, A] of set) {
  let m;
  try { m = T.buildNuclide(Z, A, { Rp: 0.8414 }); } catch (e) { log(`${Z},${A},${A - Z},ERROR ${e.message}`); continue; }
  const L = m.observableLedger, bn = Bnative(Z, A), bp = Bpn(Z, A);
  if (!L) { log(`${Z},${A},${A - Z},FIT (calibrated seed; no zero-fit ledger),,${bn.toFixed(6)},,FIT,${bp.toFixed(6)},,FIT,${m.contacts.length}`); continue; }
  const c = L.massDefect.calculatedBindingMeV, rn = c / bn, rp = c / bp;
  rows.push({ Z, A, c, rn, rp, bn: band(Math.abs(rn - 1)), bp: band(Math.abs(rp - 1)) });
  log(`${Z},${A},${A - Z},zero-fit,${c.toFixed(4)},${bn.toFixed(4)},${rn.toFixed(5)},${band(Math.abs(rn - 1))},${bp.toFixed(4)},${rp.toFixed(5)},${band(Math.abs(rp - 1))},${m.contacts.length}`);
  if (Z === 2 && A === 4) log(`NP10-C3 mu(4He) = ${L.magnetic.integralMuN.toFixed(4)} muN vs 0 ; rho = |mu|/mu_p = ${(Math.abs(L.magnetic.integralMuN) / muP).toFixed(4)} -> ${band(Math.abs(L.magnetic.integralMuN) / muP)}`);
}
const stats = key => {
  const v = rows.map(r => r[key]); const n = v.length, mean = v.reduce((a, b) => a + b, 0) / n;
  const sd = Math.sqrt(v.reduce((a, b) => a + (b - mean) ** 2, 0) / (n - 1)), s = [...v].sort((a, b) => a - b);
  const q = Math.max(1, Math.floor(n / 5)), first = rows.slice(0, q).map(r => r[key]), last = rows.slice(-q).map(r => r[key]);
  const avg = a => a.reduce((x, y) => x + y, 0) / a.length;
  return { n, median: s[Math.floor(n / 2)], mean, cv: sd / mean, firstQ: avg(first), lastQ: avg(last) };
};
const hist = key => { const h = {}; for (const r of rows) h[r[key]] = (h[r[key]] || 0) + 1; return JSON.stringify(h); };
const cvBand = cv => cv <= 0.01 ? 'B2' : cv <= 0.03 ? 'B3' : cv <= 0.10 ? 'B4' : cv <= 0.30 ? 'B5' : 'B6';
for (const [key, bkey, name] of [['rn', 'bn', 'native {A p, N e}'], ['rp', 'bp', '{Z p, N n} (owed neutron term)']]) {
  const s = stats(key);
  log(`SUMMARY ${name}: n=${s.n} bands ${hist(bkey)} ; ratio median ${s.median.toFixed(4)} mean ${s.mean.toFixed(4)} ; CV ${(100 * s.cv).toFixed(2)}% -> shape ${cvBand(s.cv)} ; first A-quintile ${s.firstQ.toFixed(4)} last ${s.lastQ.toFixed(4)}`);
}
fs.writeFileSync(path.join(__dirname, 'nseq_cascade_1_results.txt'), out.join('\n') + '\n');
