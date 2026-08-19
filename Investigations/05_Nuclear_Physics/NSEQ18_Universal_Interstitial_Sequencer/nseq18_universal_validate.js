'use strict';

const fs = require('fs');
const path = require('path');

const ROOT = path.resolve(__dirname, '..', '..', '..');
const RELEASE = path.join(ROOT, 'Release', 'HTML_SDT_Website');
const DOCS = path.join(ROOT, 'docs');
const PAGE = path.join(RELEASE, 'nuclear-packing-sequencer.html');

require(path.join(RELEASE, 'js', 'nuclear-inputs.js'));
require(path.join(RELEASE, 'js', 'traction-gear-engine.js'));

const gear = global.SDT_TRACTION_GEAR;
const html = fs.readFileSync(PAGE, 'utf8');
const rawMatch = html.match(/const RAW\s*=\s*(\[[\s\S]*?\n\]);/);
if (!rawMatch) throw new Error('isotope RAW dataset not found');
const raw = Function(`"use strict"; return ${rawMatch[1]}`)();
const isotopes = raw
  .map(([symbol, Z, A, abundance, stable, bindingEnergyMeV, spin]) => ({
    symbol,
    Z,
    A,
    abundance,
    stable,
    bindingEnergyMeV,
    spin,
    n_d: 3 * Z - A - 2,
    n_t: A - 2 * Z
  }))
  .filter(row =>
    (row.Z === 1 && row.A <= 3)
    || (row.Z === 2 && row.A === 3)
    || (row.n_d >= 0 && row.n_t >= 0 && row.bindingEnergyMeV > 0));

const failures = [];
const built = [];
const close = (a, b, tolerance = 1e-10) =>
  Math.abs(a - b) <= tolerance;

for (const isotope of isotopes) {
  let model;
  try {
    model = gear.buildNuclide(isotope.Z, isotope.A, {
      Rp: 0.8414,
      symbol: isotope.symbol,
      bindingEnergyMeV: isotope.bindingEnergyMeV,
      skipObservableLedger: true
    });
  } catch (error) {
    failures.push(`${isotope.symbol}-${isotope.A}: ${error.message}`);
    continue;
  }
  const protonCount = model.nodes.filter(node => node.type === 'p').length;
  const generic = !model.canonicalNucleon;
  const wrongSpecies = model.modules
    .filter(module => module.shellLabel)
    .filter(module =>
      (module.shellLabel.startsWith('D') && module.kind !== 'deuteron')
      || (module.shellLabel.startsWith('T') && module.kind !== 'triton'));
  const floating = generic && model.modules
    .filter(module => module.seat)
    .some(module =>
      !Number.isInteger(module.anchor)
      || !module.parentInterstitials
      || !module.parentInterstitials.length);
  const expectedContraction = model.shellLedger.length
    ? global.SDT_NUCLEAR_INPUTS.tritonOpeningScale
      - model.fullTritonClosures
        * (
          global.SDT_NUCLEAR_INPUTS.tritonOpeningScale
          - global.SDT_NUCLEAR_INPUTS.tritonClosingScale
        )
        / global.SDT_NUCLEAR_INPUTS.tritonShellCapacities.length
    : 1;
  const gates = {
    inventory: model.nodes.length === isotope.A && protonCount === isotope.Z,
    grammar:
      model.grammar.nd === (model.grammar.seed ? 0 : isotope.n_d)
      && model.grammar.nt === (model.grammar.seed ? 0 : isotope.n_t),
    speciesPure: wrongSpecies.length === 0,
    parentInterstitial: !model.shellLedger.length || !floating,
    connected: model.metrics.connected,
    bipartite: model.metrics.unlikeContacts,
    traction: model.metrics.tractionConsistent,
    noOverlap:
      model.metrics.unlistedTouches === 0
      && model.metrics.likeLikeTouches === 0,
    contraction: close(model.contractionScale, expectedContraction)
  };
  for (const [gate, passed] of Object.entries(gates)) {
    if (!passed) failures.push(`${isotope.symbol}-${isotope.A}: ${gate}`);
  }
  built.push({
    isotope: `${isotope.symbol}-${isotope.A}`,
    contacts: model.contacts.length,
    shells: model.shellLedger.map(shell =>
      `${shell.label}:${shell.occupancy}/${shell.capacity}`),
    fullTritonClosures: model.fullTritonClosures,
    contractionScale: model.contractionScale,
    fingerprint: model.fingerprint
  });
}

const d12 = gear.cuboctahedralThreeSixThree();
const d12Layers = {
  upper: d12.filter(point => point[2] > 1e-10).length,
  equatorial: d12.filter(point => Math.abs(point[2]) <= 1e-10).length,
  lower: d12.filter(point => point[2] < -1e-10).length
};
if (
  d12Layers.upper !== 3
  || d12Layers.equatorial !== 6
  || d12Layers.lower !== 3
) {
  failures.push('D12 is not the registered 3+6+3 construction');
}

const partial = [1, 2, 3, 4, 5, 6].map(count => gear.seatDirections(count));
if (!close(partial[1][0][2], 1) || !close(partial[1][1][2], -1)) {
  failures.push('partial sequence does not begin with the pole dyad');
}
if (
  partial[3].some(point =>
    !close(Math.abs(point[2]), 1 / Math.sqrt(3), 1e-12))
) {
  failures.push('four-seat partial shell is not tetrahedral');
}
if (
  partial[4].filter(point => Math.abs(point[2]) === 1).length !== 2
  || partial[4].filter(point => Math.abs(point[2]) < 1e-12).length !== 3
) {
  failures.push('five-seat partial shell is not a triangular bipyramid');
}

const spotKeys = new Set([
  'H-1', 'H-2', 'H-3', 'He-3', 'He-4', 'O-16',
  'Ca-48', 'Fe-56', 'Pb-208', 'U-238'
]);
const valueSpots = [];
for (const isotope of isotopes.filter(row =>
  spotKeys.has(`${row.symbol}-${row.A}`)
  && !['H-1', 'H-2', 'H-3', 'He-3'].includes(`${row.symbol}-${row.A}`))) {
  const model = gear.buildNuclide(isotope.Z, isotope.A, {
    Rp: 0.8414,
    symbol: isotope.symbol,
    bindingEnergyMeV: isotope.bindingEnergyMeV
  });
  const ledger = model.observableLedger;
  if (!ledger) continue;
  const gates = {
    finiteBinding: Number.isFinite(ledger.massDefect.calculatedBindingMeV),
    measuredBinding:
      close(ledger.massDefect.measuredBindingMeV, isotope.bindingEnergyMeV),
    finiteMagneticRoutes:
      Number.isFinite(ledger.magnetic.integralMuN)
      && Number.isFinite(ledger.magnetic.farFieldMuN),
    routeAgreement: ledger.magnetic.routeRelativeResidual <= 0.05,
    wakeDivergence: ledger.wake.maximumRelativeDivergence <= 0.01,
    wakeClosure:
      ledger.wake.splitResidual <= 1e-12
      && ledger.wake.rejoinResidual <= 1e-12
      && ledger.wake.pairedFluxResidual <= 1e-12,
    orientationLedger:
      ledger.orientationTrials.length
      === model.modules.filter(module => module.seat).length
  };
  for (const [gate, passed] of Object.entries(gates)) {
    if (!passed) failures.push(`${isotope.symbol}-${isotope.A}: ${gate}`);
  }
  valueSpots.push({
    isotope: `${isotope.symbol}-${isotope.A}`,
    contractionScale: model.contractionScale,
    calculatedBindingMeV: ledger.massDefect.calculatedBindingMeV,
    measuredBindingMeV: ledger.massDefect.measuredBindingMeV,
    bindingResidualMeV: ledger.massDefect.residualMeV,
    integralMuN: ledger.magnetic.integralMuN,
    farFieldMuN: ledger.magnetic.farFieldMuN,
    measuredMuN: ledger.magnetic.measuredMuN,
    routeRelativeResidual: ledger.magnetic.routeRelativeResidual,
    maximumRelativeDivergence: ledger.wake.maximumRelativeDivergence,
    alternateOrientationCount:
      ledger.orientationTrials.filter(row => row.selectedOrientationIndex > 0).length
  });
}

for (const relative of [
  'nuclear-packing-sequencer.html',
  path.join('js', 'nuclear-inputs.js'),
  path.join('js', 'traction-gear-engine.js'),
  path.join('dist', 'laws.hpp')
]) {
  const release = fs.readFileSync(path.join(RELEASE, relative));
  const docs = fs.readFileSync(path.join(DOCS, relative));
  if (!release.equals(docs)) failures.push(`${relative}: Release/docs mismatch`);
}
if (html.includes('makeLabelSprite')) {
  failures.push('Three.js label constructor remains in the sequencer');
}
const canonicalLaws = fs.readFileSync(
  path.join(ROOT, 'Engine', 'include', 'sdt', 'laws.hpp'),
  'utf8'
);
for (const token of [
  'magic_numbers[8]',
  'triton_opening_scale',
  'triton_closing_scale',
  'triton_closure_scale'
]) {
  if (!canonicalLaws.includes(token)) {
    failures.push(`canonical laws missing ${token}`);
  }
}
for (const token of [
  'buildNuclide',
  'cuboct-3-6-3',
  'fullTritonClosures',
  'observableLedger',
  'valMagRoutes',
  'valBinding'
]) {
  if (!html.includes(token) && !fs.readFileSync(
    path.join(RELEASE, 'js', 'traction-gear-engine.js'),
    'utf8'
  ).includes(token)) {
    failures.push(`public instrument missing ${token}`);
  }
}

const results = {
  schema: 'NSEQ18-UNIVERSAL-INTERSTITIAL-1',
  selectableIsotopes: isotopes.length,
  builtIsotopes: built.length,
  d12Layers,
  valueSpots,
  failures
};
fs.writeFileSync(
  path.join(__dirname, 'nseq18_results.json'),
  `${JSON.stringify(results, null, 2)}\n`
);
console.log(JSON.stringify(results, null, 2));
if (failures.length) process.exitCode = 1;

