// NSEQ18 section 11: which D6 seats can be tritonised in 18O (contact-allowable builds only). Registration: NSEQ18_RESET_ASSESSMENT_2026-10-14.md section 11.
// Usage: node o18_enumerate.js <seatKinds engine dir>. The engine variant is derived from the live Release file; Release is not edited. Author: J. C. Harvey, Melbourne.
'use strict';
const fs = require('fs'), path = require('path');
const js = process.argv[2];
global.window = global;
require(path.join(js, 'nuclear-inputs.js'));
require(path.join(js, 'traction-gear-engine_seatKinds.js'));
const T = global.SDT_TRACTION_GEAR;
const out = [];
const log = s => { out.push(s); process.stdout.write(s + '\n'); };
const dot = (a, b) => a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
log(`NSEQ18 section 11, engine ${T.version} (seatKinds variant), R_p 0.8414`);
// seat directions of the full six-seat shell, and their symmetry classes (sorted multiset of pair angles per seat)
const probe = T.buildNuclide(8, 16, { Rp: 0.8414 });
const seats = probe.modules.filter(m => m.seat).map(m => m.seat);
const sig = seats.map((s, i) => seats.map((t, j) => i === j ? null : Math.acos(Math.max(-1, Math.min(1, dot(s, t)))).toFixed(4)).filter(x => x).sort().join(','));
const classes = [...new Set(sig)];
log(`seat directions (construction order): ${seats.map(s => '(' + s.map(x => x.toFixed(3)).join(',') + ')').join(' ')}`);
log(`seat symmetry classes by pair-angle signature: ${classes.length}; seat->class: ${sig.map(x => classes.indexOf(x)).join(' ')}`);
// control: all deuteron O-16
const c16 = T.buildNuclide(8, 16, { Rp: 0.8414, seatKinds: ['d', 'd', 'd', 'd', 'd', 'd'] }), e16 = T.evaluate(c16);
log(`[control] 16O all-deuteron seatKinds build: contacts ${e16.contactCount}, max degree ${e16.maxDegree}, tractionConsistent ${e16.tractionConsistent} (live engine 16O: contacts ${probe.contacts.length})`);
const rows = [];
for (let i = 0; i < 6; i++) for (let j = i + 1; j < 6; j++) {
  const kinds = ['d', 'd', 'd', 'd', 'd', 'd']; kinds[i] = 't'; kinds[j] = 't';
  const row = { i, j, kinds: kinds.join('') };
  try {
    const m = T.buildNuclide(8, 18, { Rp: 0.8414, seatKinds: kinds }), e = T.evaluate(m);
    const deg = m.nodes.map(() => 0); for (const c of m.contacts) { deg[c.a]++; deg[c.b]++; }
    const hist = {}; for (const d of deg) hist[d] = (hist[d] || 0) + 1;
    row.ok = e.nucleonCount === 18 && e.protonCount === 8 && e.tractionConsistent && e.unitsOverSlots === 0;
    row.note = `contacts ${e.contactCount}, degree ${JSON.stringify(hist)}, extras ${m.contacts.filter(c => c.kind === 'contact').length}, nodes ${e.nucleonCount}/${e.protonCount}p, consistent ${e.tractionConsistent}`;
  } catch (err) { row.ok = false; row.note = 'REFUSED: ' + err.message; }
  rows.push(row);
  log(`  tritons at seats ${i + 1},${j + 1} (${row.kinds}): ${row.ok ? 'BUILDS' : 'does not build'} | ${row.note}`);
}
const okRows = rows.filter(r => r.ok);
log(`\nassignments that build and satisfy the contact rule: ${okRows.length} of ${rows.length}`);
for (let s = 0; s < 6; s++) {
  const n = okRows.filter(r => r.i === s || r.j === s).length;
  log(`  seat ${s + 1} (class ${classes.indexOf(sig[s])}): tritonisable in ${n} of ${rows.filter(r => r.i === s || r.j === s).length} assignments -> ${n ? 'CAN be a triton' : 'cannot (in this construction order)'}`);
}
fs.writeFileSync(path.join(__dirname, 'o18_enumerate_results.txt'), out.join('\n') + '\n');
