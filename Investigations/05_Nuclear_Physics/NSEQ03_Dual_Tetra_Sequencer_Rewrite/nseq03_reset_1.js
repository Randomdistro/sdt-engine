// NSEQ03 blank-slate run 1 (2026-10-11). Registration: NSEQ03_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Read-only unit tests of Release/HTML_SDT_Website/js/pack-nucleus.js (legacy NSEQ05 control) run unmodified under node.
// Author: J. C. Harvey, Melbourne.
const fs = require('fs'), path = require('path'), crypto = require('crypto'), cp = require('child_process');
const root = path.resolve(__dirname, '..', '..', '..');
const rel = p => path.join(root, p);
let fails = 0; const ok = (name, cond, extra) => { console.log(`${cond ? 'met    ' : 'NOT MET'}  ${name}${extra ? ' : ' + extra : ''}`); if (!cond) fails++; };
const md5 = f => crypto.createHash('md5').update(fs.readFileSync(f)).digest('hex');

console.log('NSEQ03 blank-slate run 1 (registered in NSEQ03_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=====================================================================\n');
// ---- V1, V2
require(rel('Release/HTML_SDT_Website/js/pack-nucleus.js'));
ok('[V1] module loads under node and attaches packNucleus and SDT_NUCLEAR_PACKING to globalThis', typeof globalThis.packNucleus === 'function' && !!globalThis.SDT_NUCLEAR_PACKING);
{ const n = globalThis.packNucleus(4, 2); const np = n.filter(x => x.type === 'p').length, nn = n.filter(x => x.type === 'n').length; ok('[V2] He-4: 4 nodes, 2 p and 2 n', n.length === 4 && np === 2 && nn === 2, `${n.length} nodes, ${np} p, ${nn} n`); }
const info = globalThis.SDT_NUCLEAR_PACKING; console.log(`module: version ${info.version}, classification ${info.classification}, contactGeometry ${info.contactGeometry}\n`);

// ---- T1
{ const a = rel('Release/HTML_SDT_Website/nuclear-packing-sequencer.html'), b = rel('docs/nuclear-packing-sequencer.html');
  ok('[T1] Release and docs sequencer files identical (MD5)', md5(a) === md5(b), md5(a));
  const html = fs.readFileSync(a, 'utf8'); ok('[T1] sequencer HTML loads js/pack-nucleus.js', /src="js\/pack-nucleus\.js"/.test(html));
  const files = ['Release/HTML_SDT_Website/nuclear-packing-sequencer.html', 'Release/HTML_SDT_Website/js/pack-nucleus.js', 'Release/HTML_SDT_Website/js/nuclear-inputs.js', 'Release/HTML_SDT_Website/js/traction-gear-engine.js'];
  const hits = {}; for (const f of files) { const t = fs.readFileSync(rel(f), 'utf8'); hits[path.basename(f)] = ['BELT_PAIRS', 'beltPlane', 'belt'].map(k => `${k}:${(t.match(new RegExp(k, 'gi')) || []).length}`).join(' '); }
  console.log('     vocabulary scan (case-insensitive counts):', JSON.stringify(hits));
  const stellaIn = {}; for (const f of files) { const t = fs.readFileSync(rel(f), 'utf8'); stellaIn[path.basename(f)] = (t.match(/stella/gi) || []).length; } console.log('     occurrences of "stella":', JSON.stringify(stellaIn)); }

// ---- T2
console.log('');
for (const [nm, A, Z] of [['He-4', 4, 2], ['C-12', 12, 6], ['O-16', 16, 8], ['Ca-48', 48, 20], ['Fe-56', 56, 26], ['U-238', 238, 92]]) {
  const n = globalThis.packNucleus(A, Z); const np = n.filter(x => x.type === 'p').length; const g = n.grammar;
  ok(`[T2] ${nm}: nodes = A and protons = Z, grammar n_d = 3Z-A-2, n_t = A-2Z`, n.length === A && np === Z && g.nd === 3 * Z - A - 2 && g.nt === A - 2 * Z, `nodes ${n.length} (A ${A}), p ${np} (Z ${Z}), n_d ${g.nd}, n_t ${g.nt}`); }

// ---- T3 (Ca-48, T8 shell)
console.log('');
{ const n = globalThis.packNucleus(48, 20); const t8 = n.subSeq.filter(s => s.group === 'triton' && s.name === 'T8');
  console.log(`     Ca-48 shells: ${n.shells.map(s => `${s.label} ${s.occupancy}/${s.capacity}`).join(' | ')}`);
  ok('[T3] Ca-48 has a full T8 shell (8 triton seats)', t8.length === 8 && n.shells.some(s => s.label === 'T8' && s.full), `${t8.length} seats`);
  const seats = t8.map(s => { const p = n.find(x => x.group === 'triton' && x.sub === s.sub && x.type === 'p'); const r = Math.hypot(...p.pos); return { seat: s.seat, dir: p.pos.map(c => c / r), r }; }).sort((x, y) => x.seat - y.seat);
  // second-moment tensor eigenvalues (Jacobi)
  const T = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]; for (const s of seats) for (let i = 0; i < 3; i++) for (let j = 0; j < 3; j++) T[i][j] += s.dir[i] * s.dir[j];
  const eig = A => { const a = A.map(r => r.slice()); for (let it = 0; it < 60; it++) { let p = 0, q = 1, m = Math.abs(a[0][1]); if (Math.abs(a[0][2]) > m) { p = 0; q = 2; m = Math.abs(a[0][2]); } if (Math.abs(a[1][2]) > m) { p = 1; q = 2; m = Math.abs(a[1][2]); } if (m < 1e-15) break; const th = 0.5 * Math.atan2(2 * a[p][q], a[q][q] - a[p][p]), c = Math.cos(th), s = Math.sin(th); for (let k = 0; k < 3; k++) { const x = a[k][p], y = a[k][q]; a[k][p] = c * x - s * y; a[k][q] = s * x + c * y; } for (let k = 0; k < 3; k++) { const x = a[p][k], y = a[q][k]; a[p][k] = c * x - s * y; a[q][k] = s * x + c * y; } } return [a[0][0], a[1][1], a[2][2]].sort((x, y) => x - y); };
  const e = eig(T); ok('[T3a] T8 seats non-coplanar: second-moment eigenvalues all non-zero and isotropic (8/3 each)', e[0] > 1e-9 && Math.abs(e[0] - 8 / 3) < 1e-9 && Math.abs(e[2] - 8 / 3) < 1e-9, e.map(x => x.toFixed(6)).join(', '));
  const has = (z) => seats.some(s => Math.abs(s.dir[0]) < 1e-9 && Math.abs(s.dir[1]) < 1e-9 && Math.abs(s.dir[2] - z) < 1e-9);
  ok('[T3b] both poles present among the T8 seats', has(1) && has(-1));
  const ang = (a, b) => Math.acos(Math.max(-1, Math.min(1, a[0] * b[0] + a[1] * b[1] + a[2] * b[2]))) * 180 / Math.PI; let h70 = 0, h109 = 0, h180 = 0, other = 0;
  for (let i = 0; i < 8; i++) for (let j = i + 1; j < 8; j++) { const a = ang(seats[i].dir, seats[j].dir); if (Math.abs(a - 70.528779) < 1e-4) h70++; else if (Math.abs(a - 109.471221) < 1e-4) h109++; else if (Math.abs(a - 180) < 1e-4) h180++; else other++; }
  ok('[T3c] pair-angle histogram of the T8 seats = 12 x 70.5288, 12 x 109.4712, 4 x 180 (the NSEQ02 layout)', h70 === 12 && h109 === 12 && h180 === 4 && other === 0, `${h70}/${h109}/${h180} (other ${other})`);
  const open = seats.filter(s => s.seat % 2 === 0), close = seats.filter(s => s.seat % 2 === 1); const mo = open.reduce((a, s) => a + s.r, 0) / open.length, mc = close.reduce((a, s) => a + s.r, 0) / close.length;
  ok('[T3d] mean radius of opening (even) seats exceeds closing (odd) seats; ratio = 1.05/0.95', mo > mc && Math.abs(mo / mc - 1.05 / 0.95) < 1e-12, `${mo.toFixed(5)} > ${mc.toFixed(5)}, ratio ${(mo / mc).toFixed(9)} (1.05/0.95 = ${(1.05 / 0.95).toFixed(9)})`);
  const zs = o => o.map(s => s.dir[2]).sort((x, y) => x - y).map(z => z.toFixed(4)).join(' ');
  const openOK = open.filter(s => Math.abs(s.dir[2] + 1 / 3) < 1e-9).length === 3 && open.filter(s => Math.abs(s.dir[2] - 1) < 1e-9).length === 1;
  const closeOK = close.filter(s => Math.abs(s.dir[2] - 1 / 3) < 1e-9).length === 3 && close.filter(s => Math.abs(s.dir[2] + 1) < 1e-9).length === 1;
  ok('[T3e] opening tetrahedron = north pole + 3 seats at z = -1/3; closing = south pole + 3 seats at z = +1/3', openOK && closeOK, `open z: ${zs(open)} ; close z: ${zs(close)}`);
  // nearest opening-closing distance and edge distances (relative units from the module's radii)
  const D = (a, b) => Math.hypot(...[0, 1, 2].map(k => a.dir[k] * a.r - b.dir[k] * b.r)); let oo = [], cc = [], oc = [];
  for (let i = 0; i < 8; i++) for (let j = i + 1; j < 8; j++) { const a = seats[i], b = seats[j], d = D(a, b); const ao = a.seat % 2 === 0, bo = b.seat % 2 === 0; (ao && bo ? oo : (!ao && !bo ? cc : oc)).push(d); }
  const mm = v => `${Math.min(...v).toFixed(4)}..${Math.max(...v).toFixed(4)}`; console.log(`     seat distances at rTier (fm): opening-opening ${mm(oo)} ; closing-closing ${mm(cc)} ; opening-closing ${mm(oc)} ; ratio nearest cross / opening edge = ${(Math.min(...oc) / Math.min(...oo)).toFixed(4)}`); }

// ---- T4
console.log('');
{ const seq = info.shellSequence; const tcap = seq.filter(s => s.sp === 't').map(s => s.cap), dcap = seq.filter(s => s.sp === 'd').map(s => s.cap);
  ok('[T4] triton capacities 8,10,12,14,16,18', JSON.stringify(tcap) === JSON.stringify([8, 10, 12, 14, 16, 18]), tcap.join(','));
  ok('[T4] deuteron capacities 6,12,12,20,30,42,56', JSON.stringify(dcap) === JSON.stringify([6, 12, 12, 20, 30, 42, 56]), dcap.join(','));
  let c = 2; const cum = [2]; for (const s of seq) { c += s.cap; cum.push(c); } console.log('     cumulative totals (alpha core = 2):', cum.join(', ')); }

// ---- T5
console.log('');
{ let st = ''; try { st = cp.execSync('git status --porcelain -- Engine/include/sdt/laws.hpp', { cwd: root }).toString().trim(); } catch (e) { st = 'ERROR ' + e.message; }
  ok('[T5] laws.hpp has no working-tree modification', st === '', st === '' ? 'clean' : st);
  console.log('     nomenclature proposal file present:', fs.existsSync(path.join(__dirname, 'PROPOSE_LAWS_HPP_BELT_NOMENCLATURE.md'))); }
console.log(`\nSUMMARY: ${fails === 0 ? 'all registered checks met' : fails + ' check(s) NOT MET'}`);
process.exit(fails ? 1 : 0);
