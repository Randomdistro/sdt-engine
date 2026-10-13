// NP12f round 2 (2026-10-11): proton point-RMS of the LIVE construction (NSEQ18-WEB-1) folded with R_p,
// against IAEA boundary radii, whole range, single pass. Registration: PROMPT.md §4 (rewritten 2026-10-11).
// Usage: node np12f_round2_live.js <repo root>. Release is read, never edited. Author: J. C. Harvey, Melbourne.
'use strict';
const fs = require('fs'), path = require('path');
const root = process.argv[2];
const js = path.join(root, 'Release', 'HTML_SDT_Website', 'js');
global.window = global;
require(path.join(js, 'nuclear-inputs.js'));
require(path.join(js, 'traction-gear-engine.js'));
const T = global.SDT_TRACTION_GEAR, Rp = 0.8414;
const out = []; const log = s => { out.push(s); process.stdout.write(s + '\n'); };
const band = r => r <= 1e-3 ? 'B1' : r <= 1e-2 ? 'B2' : r <= 3e-2 ? 'B3' : r <= 0.10 ? 'B4' : r <= 0.30 ? 'B5' : r <= 2 ? 'B6' : 'B7';
const rms = pts => { const c = [0, 1, 2].map(k => pts.reduce((s, p) => s + p[k], 0) / pts.length); return Math.sqrt(pts.reduce((s, p) => s + (p[0] - c[0]) ** 2 + (p[1] - c[1]) ** 2 + (p[2] - c[2]) ** 2, 0) / pts.length); };

// IAEA radii
const lines = fs.readFileSync(path.join(root, 'Datasets', 'nuclear', 'IAEA_ground_states_radii.csv'), 'utf8').split(/\r?\n/);
const hdr = lines[0].split(','), iZ = hdr.indexOf('z'), iN = hdr.indexOf('n'), iR = hdr.indexOf('radius');
const meas = [];
for (const L of lines.slice(1)) { const f = L.split(','); if (f.length < 4 || f[iR] === '') continue; const Z = +f[iZ], N = +f[iN], r = +f[iR]; if (Z >= 1 && r > 0) meas.push([Z, Z + N, r]); }

// validations
const s = 1 / Math.sqrt(3), tet = [[s, s, s], [s, -s, -s], [-s, s, -s], [-s, -s, s]];
const v1 = Math.abs(rms(tet) - 1) < 1e-12;
const pb = meas.find(m => m[0] === 82 && m[1] === 208), v3 = pb && Math.abs(pb[2] - 5.5012) < 1e-4;
log(`NP12f round 2 (2026-10-11) engine ${T.version}; IAEA rows with radius: ${meas.length}`);
log(`[V1] synthetic tetrahedron RMS = ${rms(tet).toFixed(12)} -> ${v1 ? 'met' : 'NOT MET'} ; [V3] IAEA 208Pb radius = ${pb && pb[2]} -> ${v3 ? 'met' : 'NOT MET'}`);
if (!v1 || !v3) process.exit(1);
log('Z,A,R_pt_fm,R_pred_fm,R_meas_fm,ratio,band');
const rows = []; let v2bad = 0, skipped = 0;
for (const [Z, A, r] of meas.sort((a, b) => a[1] - b[1] || a[0] - b[0])) {
  if (!T.grammar(A, Z).valid || A < 2) { skipped++; continue; }
  let m; try { m = T.buildNuclide(Z, A, { Rp }); } catch (e) { log(`${Z},${A},ERROR ${e.message}`); continue; }
  const k = m.contractionScale || 1, protons = m.nodes.filter(n => n.type === 'p').map(n => n.pos.map(x => x * k));
  if (protons.length !== Z || m.nodes.length !== A) v2bad++;
  const Rpt = rms(protons), Rpred = Math.sqrt(Rpt * Rpt + Rp * Rp), rho = Math.abs(Rpred / r - 1);
  rows.push({ Z, A, rho, ratio: Rpred / r });
  log(`${Z},${A},${Rpt.toFixed(4)},${Rpred.toFixed(4)},${r.toFixed(4)},${(Rpred / r).toFixed(4)},${band(rho)}`);
}
log(`[V2] builds with n_p != Z or n != A: ${v2bad} -> ${v2bad === 0 ? 'met' : 'NOT MET'} ; grammar-excluded rows skipped: ${skipped}`);
const med = a => { const s = [...a].sort((x, y) => x - y); return s.length ? s[Math.floor(s.length / 2)] : NaN; };
const hist = rs => { const h = {}; for (const r of rs) { const b = band(r.rho); h[b] = (h[b] || 0) + 1; } return JSON.stringify(h); };
for (const [lo, hi, name] of [[2, 6, 'A<=6'], [7, 39, '7<=A<=39'], [40, 999, 'A>=40'], [2, 999, 'all']]) {
  const sel = rows.filter(r => r.A >= lo && r.A <= hi);
  log(`SUMMARY ${name}: n=${sel.length} median rho ${(100 * med(sel.map(r => r.rho))).toFixed(2)}% median ratio ${med(sel.map(r => r.ratio)).toFixed(4)} bands ${hist(sel)}`);
}
const heavy = rows.filter(r => r.A >= 40), mh = med(heavy.map(r => r.rho));
log(`GATE (median rho over A>=40): ${(100 * mh).toFixed(2)}% -> ${mh <= 0.03 ? 'construction carries size (B3 or better)' : mh > 0.10 ? 'EXCLUDED (median > 10%)' : 'between 3% and 10%: order-correct, structure missing (B4)'}`);
// zero-parameter control: close-pack law R = R_p (A/eta)^(1/3), eta = pi/sqrt(18), folded the same way? reported as stated in NP30 (bulk radius)
const eta = Math.PI / Math.sqrt(18), ctl = heavy.map(r => { const m = meas.find(x => x[0] === r.Z && x[1] === r.A); return Math.abs(Rp * Math.cbrt(r.A / eta) / m[2] - 1); });
log(`CONTROL close-pack law R = R_p (A/eta)^(1/3) read directly against the measured radius (NP30 section 6), A>=40: median rho ${(100 * med(ctl)).toFixed(2)}%`);
fs.writeFileSync(path.join(__dirname, 'np12f_round2_live_results.txt'), out.join('\n') + '\n');
