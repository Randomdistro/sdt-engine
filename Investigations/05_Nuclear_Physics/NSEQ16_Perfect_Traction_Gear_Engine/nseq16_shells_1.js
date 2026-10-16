// NSEQ16 triton-shell opening/closing geometry (2026-10-15). Registration: NSEQ16_RESET_ASSESSMENT_2026-10-14.md section 11 (written before this file existed).
// Usage: node nseq16_shells_1.js <repo root>. Live engine, read only. Author: J. C. Harvey, Melbourne.
'use strict';
const fs = require('fs'), path = require('path');
const root = process.argv[2];
const js = path.join(root, 'Release', 'HTML_SDT_Website', 'js');
global.window = global;
require(path.join(js, 'nuclear-inputs.js'));
require(path.join(js, 'traction-gear-engine.js'));
const T = global.SDT_TRACTION_GEAR;
const Rp = 0.8414, out = [];
const log = s => { out.push(s); process.stdout.write(s + '\n'); };
log(`NSEQ16 section 11 (2026-10-15), engine ${T.version}. Extent E = max(|pos|)/Rp + 1 (envelope = Rp); rms = rms unit radius / Rp; centroid offset removed.`);
function geom(Z, A) {
  const m = T.buildNuclide(Z, A, { Rp });
  const n = m.nodes.length, c = [0, 0, 0];
  for (const nd of m.nodes) for (let k = 0; k < 3; k++) c[k] += nd.pos[k] / n;
  let maxr = 0, s2 = 0;
  for (const nd of m.nodes) { const r = Math.hypot(nd.pos[0] - c[0], nd.pos[1] - c[1], nd.pos[2] - c[2]); maxr = Math.max(maxr, r); s2 += r * r; }
  return { E: maxr / Rp + 1, rms: Math.sqrt(s2 / n) / Rp, scale: m.contractionScale, full: m.fullTritonClosures, n };
}
for (const [label, nd, zBase, aBase, nts] of [['n_d = 18 (D6 + D12-pre full); T8 opens at n_t = 1 and closes at 8', 18, 20, 40, 9], ['n_d = 30 (D6, D12-pre, D12-cuboct full); T8 closes at 8, T10 opens at 9 and closes at 18', 30, 32, 64, 19]]) {
  log(`\n${label}`);
  log('n_t, Z, A, nucleons, E (R_p), rms (R_p), engine contractionScale (not used in E), full triton closures');
  const rows = [];
  for (let nt = 0; nt < nts; nt++) {
    const Z = zBase + nt, A = aBase + 3 * nt;
    let g; try { g = geom(Z, A); } catch (e) { log(`${nt}, ${Z}, ${A}, REFUSED: ${e.message}`); continue; }
    rows.push({ nt, ...g });
    log(`${nt}, ${Z}, ${A}, ${g.n}, ${g.E.toFixed(4)}, ${g.rms.toFixed(4)}, ${g.scale.toFixed(4)}, ${g.full}`);
  }
  const E0 = rows[0].E;
  const open1 = rows.find(r => r.nt === 1);
  log(`reading: E(n_t=0) = ${E0.toFixed(4)}; opening (n_t=1) ${open1 ? (open1.E > E0 + 1e-9 ? 'EXPANDS' : 'does not expand') : 'n/a'} (${open1 ? (open1.E - E0).toFixed(4) : ''}); T8 closure (n_t=8) ${(() => { const r = rows.find(x => x.nt === 8); return r ? (r.E <= E0 + 1e-9 ? 'back or tighter' : 'LOOSER than before opening') + ` (${(r.E - E0).toFixed(4)})` : 'n/a'; })()}`);
  if (nd === 30) {
    const E8 = rows.find(r => r.nt === 8)?.E, E9 = rows.find(r => r.nt === 9)?.E, E18 = rows.find(r => r.nt === 18)?.E;
    if (E8 != null && E9 != null) log(`reading: T10 opening (8 -> 9): ${(E9 - E8).toFixed(4)} (${E9 > E8 ? 'expands' : 'does not expand'}); T10 closure (n_t=18) vs E(n_t=8): ${E18 != null ? (E18 - E8).toFixed(4) + (E18 <= E8 + 1e-9 ? ' back or tighter' : ' looser') : 'n/a'}`);
  }
}
fs.writeFileSync(path.join(__dirname, 'nseq16_shells_1_results.txt'), out.join('\n') + '\n');
