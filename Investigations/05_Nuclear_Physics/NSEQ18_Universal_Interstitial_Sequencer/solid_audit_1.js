// NSEQ18 solid-body audit of what the contact test actually checks (2026-10-14). Exposure-only audit, no gate. Author: J. C. Harvey, Melbourne.
// Usage: node solid_audit_1.js <repo root>.  Read-only on the live engine.
'use strict';
const path = require('path');
const root = process.argv[2];
const js = path.join(root, 'Release', 'HTML_SDT_Website', 'js');
global.window = global;
require(path.join(js, 'nuclear-inputs.js'));
require(path.join(js, 'traction-gear-engine.js'));
const T = global.SDT_TRACTION_GEAR;
const out = [];
const log = s => { out.push(s); process.stdout.write(s + '\n'); };
const st = T.selfTest({ Rp: 0.8414 }), d = st.hydrogen.dimensions;
log(`engine ${T.version}. H1 nucleon (hydrogen spec): major radius ${(d.majorRadius / 0.8414).toFixed(4)} R_p, helix radius ${(d.helixRadius / 0.8414).toFixed(4)} R_p, strand radius ${(d.strandRadius / 0.8414).toFixed(4)} R_p, outer envelope ${(1 + d.outerEnvelopeResidual).toFixed(4)} R_p; engine contact distance 2.0000 R_p`);
log(`two flat rings of centreline radius ${(d.majorRadius / 0.8414).toFixed(4)} R_p, in plane, at centre distance 2 R_p: centreline gap ${(2 - 2 * d.majorRadius / 0.8414).toFixed(4)} R_p against a strand diameter of ${(2 * d.strandRadius / 0.8414).toFixed(4)} R_p (strands overlap unless the helices mesh)`);
for (const [Z, A] of [[8, 16], [20, 40], [26, 56], [82, 208]]) {
  const m = T.buildNuclide(Z, A, { Rp: 0.8414 });
  const L = m.observableLedger;
  const orient = new Set(L.poses.map(p => p.orientation.join(',')));
  const nz = m.contacts.map(c => { const a = m.nodes[c.a].pos, b = m.nodes[c.b].pos; const v = [b[0] - a[0], b[1] - a[1], b[2] - a[2]]; const n = Math.hypot(...v); return Math.abs(v[2] / n); });
  const bins = [0.05, 0.2, 0.5, 0.9].map(t => nz.filter(x => x > t).length);
  const slipAvg = m.contacts.map(c => T.contactSlip(m.nodes[c.a].type, m.nodes[c.b].type, [m.nodes[c.b].pos[0] - m.nodes[c.a].pos[0], m.nodes[c.b].pos[1] - m.nodes[c.a].pos[1], m.nodes[c.b].pos[2] - m.nodes[c.a].pos[2]], 0.8414));
  const flat = m.contacts.filter((c, i) => nz[i] < 0.05).length;
  log(`${Z}-${A}: ${m.contacts.length} contacts; distinct unit orientations in the ledger: ${orient.size} (${[...orient][0]}); contacts with |n_z| > 0.05 / 0.2 / 0.5 / 0.9: ${bins.join(' / ')}; contacts lying in the ring plane (|n_z| < 0.05): ${flat}; max slip ${Math.max(...slipAvg).toExponential(1)}`);
}
