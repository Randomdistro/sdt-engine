'use strict';

const fs = require('node:fs');
const path = require('node:path');

const ROOT = path.resolve(__dirname, '..', '..', '..');
require(path.join(
  ROOT,
  'Release',
  'HTML_SDT_Website',
  'js',
  'pack-nucleus.js'
));
require(path.join(
  ROOT,
  'Release',
  'HTML_SDT_Website',
  'js',
  'nuclear-inputs.js'
));
const GEAR_PATH = path.join(
  ROOT,
  'Release',
  'HTML_SDT_Website',
  'js',
  'traction-gear-engine.js'
);
require(GEAR_PATH);

const gear = globalThis.SDT_TRACTION_GEAR;
const gearSource = fs.readFileSync(GEAR_PATH, 'utf8');
const keys = ['H2', 'H3', 'He3'];
const relative = (a, b) =>
  Math.abs(a - b) / Math.max(Math.abs(b), Number.EPSILON);

function circularLoopCheck() {
  const count = 4096;
  const segments = [];
  for (let index = 0; index < count; index++) {
    const a = 2 * Math.PI * index / count;
    const b = 2 * Math.PI * (index + 1) / count;
    segments.push({
      a: [Math.cos(a), Math.sin(a), 0],
      b: [Math.cos(b), Math.sin(b), 0],
      weight: 1
    });
  }
  const moment = gear.segmentMoment(segments);
  return {
    expected: Math.PI,
    actual: moment[2],
    relativeResidual: relative(moment[2], Math.PI)
  };
}

function translationCheck() {
  const parameters = {
    separationRp: 2,
    tiltRadians: Math.PI / 2,
    toroidalPhase: Math.PI,
    poloidalPhase: Math.PI / 2
  };
  const poses = gear.lightNucleusPoses('H2', parameters);
  const translated = poses.map(pose => ({
    ...pose,
    centreRp: pose.centreRp.map((value, axis) =>
      value + [3.25, -1.5, 2.75][axis])
  }));
  const base = gear.wakeMeshPairMetrics(poses[0], poses[1]);
  const moved = gear.wakeMeshPairMetrics(translated[0], translated[1]);
  return {
    base: base.coupling,
    translated: moved.coupling,
    relativeResidual: relative(base.coupling, moved.coupling)
  };
}

function separatedCheck() {
  const poses = gear.lightNucleusPoses('H2', {
    separationRp: 2,
    tiltRadians: Math.PI / 2,
    toroidalPhase: Math.PI,
    poloidalPhase: Math.PI / 2
  });
  const distant = {
    ...poses[1],
    centreRp: [50, 0, 0]
  };
  return gear.wakeMeshPairMetrics(poses[0], distant).coupling;
}

const first = Object.fromEntries(keys.map(key => [
  key,
  gear.fitLightNucleus(key)
]));
const second = Object.fromEntries(keys.map(key => [
  key,
  gear.fitLightNucleus(key)
]));
const deterministicResidual = Math.max(...keys.flatMap(key =>
  Object.keys(first[key].parameters).map(name =>
    Math.abs(
      first[key].parameters[name] - second[key].parameters[name]
    ))));
const circle = circularLoopCheck();
const translation = translationCheck();
const separatedOverlap = separatedCheck();
const neutron = gear.neutronMagneticCalibration();

const checks = {
  instrumentCircularMoment: circle.relativeResidual <= 1e-6,
  instrumentTranslationInvariant:
    translation.relativeResidual <= 1e-12,
  instrumentSeparatedZero: separatedOverlap <= 1e-12,
  deterministic: deterministicResidual <= 1e-12,
  targetResiduals: keys.every(key => {
    const residuals = first[key].residuals;
    return Math.abs(residuals.binding) <= 1e-4
      && Math.abs(residuals.magnetic) <= 1e-4
      && (
        residuals.quadrupole == null
        || Math.abs(residuals.quadrupole) <= 1e-4
      );
  }),
  conservation: keys.every(key =>
    first[key].mesh.splitResidual <= 1e-12
    && first[key].mesh.rejoinResidual <= 1e-12
    && first[key].mesh.circuitCount
      === first[key].mesh.closedCircuitCount),
  divergence: keys.every(key =>
    first[key].mesh.maximumRelativeDivergence <= 0.01),
  magneticRoutes: keys.every(key =>
    first[key].magneticRoutes.relativeResidual <= 0.05),
  coefficientBounds: keys.every(key =>
    first[key].coefficientBoundsSatisfied
    && first[key].parameterBoundsSatisfied),
  fieldCrossTerm: keys.every(key =>
    first[key].mesh.pairLedger.every(pair =>
      pair.integration
      && pair.integration.representation
        === '-integral U_i dot U_j dV'
      && pair.integration.samples > 0
      && pair.integration.volumeElement > 0)),
  noContactMismatch: keys.every(key =>
    !first[key].contactMismatch),
  neutronNeutronContact: first.H3.neutronNeutronContactExcluded,
  neutronCounterCirculation:
    neutron.classification === 'CALIBRATED(1)'
    && neutron.protonContributionMuN > 0
    && neutron.seatedElectronContributionMuN < 0
    && Math.abs(neutron.residualMuN) <= 1e-12
    && neutron.suppressionRatio < 0.30,
  frozenNeutronLedger: keys.every(key => {
    const ledger = first[key].mesh.neutronCalibration;
    return ledger
      && Math.abs(
        ledger.seatedElectronCoefficientMuNPerGeometricMoment
        - neutron.seatedElectronCoefficientMuNPerGeometricMoment
      ) <= 1e-12;
  }),
  deformableWake: keys.every(key =>
    first[key].mesh.deformationLedger.some(
      row => row.wakeCompliance > 0.01
    )),
  conservativeRepartition: keys.every(key =>
    first[key].mesh.deformationLedger.every(row =>
      Math.abs(row.throatFraction + row.poloidalFraction - 1) <= 1e-12
    )),
  noDirectNeutronTargetScale:
    !gearSource.includes('targetMoment / (Math.abs(selfZ)')
    && !gearSource.includes("freeMoment = pose.type === 'p'"),
  noProximitySurrogate:
    !gearSource.includes('const sigma2 = 0.45 * 0.45')
    && !gearSource.includes('const proximity = Math.exp(')
};

const result = {
  schema: 'NSEQ17-WAKE-MESH-REPAIR-2',
  neutron,
  classification: {
    H2: first.H2.classification,
    H3: first.H3.classification,
    He3: first.He3.classification
  },
  instrumentValidation: {
    circularLoop: circle,
    translation,
    separatedOverlap
  },
  deterministicResidual,
  isotopes: first,
  checks,
  assessment: Object.values(checks).every(Boolean)
    ? 'NSEQ17_CALIBRATION_CONSISTENT'
    : 'NSEQ17_CALIBRATION_REJECTED'
};

const output = path.join(__dirname, 'nseq17_results.json');
fs.writeFileSync(output, `${JSON.stringify(result, null, 2)}\n`);
console.log(result.assessment);
for (const key of keys) {
  const row = first[key];
  console.log(
    `${key} ${row.classification} `
    + `B=${row.model.bindingEnergyMeV.toFixed(9)} MeV `
    + `mu=${row.model.magneticMomentMuN.toFixed(10)} mu_N `
    + `route=${(100 * row.magneticRoutes.relativeResidual).toFixed(3)}%`
  );
}
console.log(
  `N1 ${neutron.classification} `
  + `p=${neutron.protonContributionMuN.toFixed(10)} mu_N `
  + `e=${neutron.seatedElectronContributionMuN.toFixed(10)} mu_N `
  + `net=${neutron.netMomentMuN.toFixed(10)} mu_N `
  + `suppression=${(100 * neutron.suppressionRatio).toFixed(2)}%`
);
