// NSEQ16 Round 2 (2026-10-14): G0-G8 on the live engine. Registration: NSEQ16_RESET_ASSESSMENT_2026-10-14.md sections 0-2 (written before this file existed).
// Usage: node nseq16_reset_2.js <repo root>. Release is read, never edited. Author: J. C. Harvey, Melbourne.
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
const ok = b => b ? 'met' : 'NOT MET';
log(`NSEQ16 Round 2 (2026-10-14) engine ${T.version}, R_p ${Rp} fm`);

const st = T.selfTest({ Rp });
const cases = [[1, 1], [1, 2], [1, 3], [2, 4], [3, 7], [4, 9], [5, 11], [6, 12], [7, 14], [8, 16]];
let g0 = true, g2 = true, g3 = true, g4 = true, g7a = true;
const bip = (m) => {   // two-colouring of the contact graph by unit type: every edge must join unlike types
  return m.contacts.every(e => m.nodes[e.a].type !== m.nodes[e.b].type);
};
log('\ncase: A, Z, nd, nt | connected, bipartite(types), contacts, max residual, max slip, unlisted, clock residual | fingerprint repeat');
for (const [Z, A] of cases) {
  const m = T.buildNuclide(Z, A, { Rp }), m2 = T.buildNuclide(Z, A, { Rp }), e = T.evaluate(m);
  const gram = m.grammar;
  const inv = e.nucleonCount === A && e.protonCount === Z && (Z < 2 || A < 4 || (gram.nt === A - 2 * Z && gram.nd === 3 * Z - A - 2));
  const b = bip(m), rep = m.fingerprint === m2.fingerprint;
  g0 = g0 && inv; g2 = g2 && e.connected && e.allTouched && e.unlikeContacts && e.likeLikeTouches === 0 && b;
  g3 = g3 && e.maxContactResidual <= 1e-10 && e.maxSlip < 1e-10 && e.unlistedTouches === 0; g4 = g4 && e.commonClockResidual <= 1e-10; g7a = g7a && rep;
  log(`  ${Z}-${A}: ${A}, ${Z}, ${gram.nd}, ${gram.nt} | ${e.connected}, ${b}, ${e.contactCount}, ${e.maxContactResidual.toExponential(2)}, ${e.maxSlip.toExponential(2)}, ${e.unlistedTouches}, ${e.commonClockResidual.toExponential(2)} | ${rep}`);
}
log(`[G0] inventory: ${ok(g0)}`);
const seatMax = Math.max(...Object.values(st.seatErrors));
log(`[G1] seat angle errors for 2-6 seats: max ${seatMax.toExponential(2)} rad (<= 1e-10) -> ${ok(seatMax <= 1e-10)}`);
log(`[G2] connected, every unit touched, unlike contacts only, no like-like touch, two-colourable: ${ok(g2)}`);
log(`[G3] contact residual <= 1e-10, slip < 1e-10, no unlisted touch: ${ok(g3)}`);
log(`[G4] common clock residual <= 1e-10: ${ok(g4)}`);
const order = st.fourTourStages.join(',') === 'inner,under,outer,over';
log(`[G5] four-tour closure ${st.fourTourClosure.toExponential(2)} R_p (< 1e-10), stages ${st.fourTourStages.join(',')} -> ${ok(st.fourTourClosure < 1e-10 && order)}`);
const g6 = st.mobiusPosition2Pi <= 1e-10 && st.mobiusPosition4Pi <= 1e-10 && Math.abs(st.mobiusDirector2Pi + 1) <= 1e-10 && Math.abs(st.mobiusDirector4Pi - 1) <= 1e-10;
log(`[G6] Mobius: position 2pi ${st.mobiusPosition2Pi.toExponential(2)}, 4pi ${st.mobiusPosition4Pi.toExponential(2)}; director 2pi ${st.mobiusDirector2Pi}, 4pi ${st.mobiusDirector4Pi} -> ${ok(g6)}`);
const b1 = T.braidDiagnostics(Rp, 2048), b2 = T.braidDiagnostics(Rp, 4096);
const dres = ['fourTourClosure', 'maximumSeamResidual', 'maximumSeamTangentResidual'].map(k => [k, Math.abs(b1[k] - b2[k])]);
const g7b = dres.every(x => x[1] < 1e-12);
log(`[G7] fingerprint repeat for all ten cases: ${g7a}; resolution doubling 2048 vs 4096: ${dres.map(x => x[0] + ' ' + x[1].toExponential(2)).join(', ')} -> ${ok(g7a && g7b)}`);

// rejection controls
const o16 = T.buildNuclide(8, 16, { Rp });
const types = o16.nodes.map(n => n.type);
const swapped = o16.contacts.map(e => ({ a: e.a, b: e.b })); const e0 = swapped[0]; const tcopy = types.slice(); tcopy[e0.b] = tcopy[e0.a];   // make edge 0 like-like
const stillBip = swapped.every(e => tcopy[e.a] !== tcopy[e.b]);
log(`[control i] same-handed p-p contact slip ${st.likeSlipControl} (nonzero expected); unlike p-n slip ${st.unlikeSlipControl}`);
log(`[control ii] O-16 graph with one edge made like-like is still two-colourable by type: ${stillBip} (expected false)`);
log('[control iii, iv] not run: the engine exposes no switch to remove the Mobius half-twist, and (iv) is a labelling rule');

// G8
const env = 1 + st.hydrogen.dimensions.outerEnvelopeResidual;
log(`\n[G8a] H1 nucleon outer envelope = ${env.toFixed(4)} R_p (<= 1) -> ${ok(env <= 1)}`);
const d = st.hydrogen.dimensions, bs = T.braidSpec;
const cand = (q, p) => Math.sqrt(q / p);
log(`[G8b] aspect R/a against sqrt(q/p):`);
log(`   H1 spec (4 tours, 3 cross-section turns): R/a(helix radius) = ${(d.majorRadius / d.helixRadius).toFixed(3)}, R/a(strand radius) = ${(d.majorRadius / d.strandRadius).toFixed(3)}; sqrt(3/4) = ${cand(3, 4).toFixed(4)}, sqrt(5/4) = ${cand(5, 4).toFixed(4)}`);
log(`   braid spec (4,5): R/a = ${(bs.majorRadiusFraction / bs.helixRadiusFraction).toFixed(3)} against sqrt(5/4) = ${cand(5, 4).toFixed(4)} -> ${ok(Math.abs(bs.majorRadiusFraction / bs.helixRadiusFraction - cand(5, 4)) < 0.01)}`);
log(`   canon (2,3): sqrt(3/2) = ${cand(3, 2).toFixed(4)} (no engine object declares it)`);
log(`[G8c] size provenance: H1 straight helix length ${d.straightHelixLength} fm and strand diameter ${d.strandDiameter} fm; engine record of provenance: ${JSON.stringify(Object.keys(T.h1Spec).filter(k => /source|provenance|record|trace/i.test(k)))} -> ${ok(Object.keys(T.h1Spec).some(k => /source|provenance|record|trace/i.test(k)))}`);
fs.writeFileSync(path.join(__dirname, 'nseq16_reset_2_results.txt'), out.join('\n') + '\n');
