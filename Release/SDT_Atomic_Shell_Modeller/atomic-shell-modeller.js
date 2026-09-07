(() => {
  'use strict';

  const NIST_CODATA_2022 = Object.freeze({
    alpha: 7.2973525643e-3,
    c: 299792458,
    bohrRadiusM: 5.29177210544e-11,
    classicalElectronRadiusM: 2.8179403205e-15,
    protonRmsChargeRadiusM: 8.4075e-16,
    deuteronRmsChargeRadiusM: 2.12778e-15,
    alphaParticleRmsChargeRadiusM: 1.6785e-15,
  });
  const SDT = Object.freeze({
    alpha: NIST_CODATA_2022.alpha,
    c: NIST_CODATA_2022.c,
    hbar: 1.054571817e-34,
    protonMass: 1.67262192595e-27,
    electronMass: 9.1093837015e-31,
    a0: NIST_CODATA_2022.bohrRadiusM,
    protonBoundary: 8.414e-16,
    lockCoordination: 4,
    viewSecondsToPhysicalSeconds: 1e-18,
  });
  const H_HE_AXIS = Object.freeze({ x: 0, y: 0, z: 1 });
  const LETTER_TO_L = Object.freeze({ s: 0, p: 1, d: 2, f: 3 });
  const MODE_LABELS = Object.freeze({
    s: ['s'],
    p: ['p_x', 'p_y', 'p_z'],
    d: ['d_xy', 'd_xz', 'd_yz', 'd_x2-y2', 'd_z2'],
    f: ['f_z3', 'f_xz2', 'f_yz2', 'f_xyz', 'f_x3-3xy2', 'f_3x2y-y3', 'f_zx2-y2'],
  });
  const COLOUR = Object.freeze({ s: '#67d9ff', p: '#8c9dff', d: '#c584ff', f: '#ff86cb' });
  const TOUR_ENVELOPE = Object.freeze({
    s: { offset: 0, axial: 1, transverse: 1 },
    p: { offset: 0.58, axial: 0.34, transverse: 0.25 },
    d: { offset: 0.62, axial: 0.30, transverse: 0.22 },
    f: { offset: 0.65, axial: 0.27, transverse: 0.20 },
  });
  const IAEA_GROUND_STATE_PATH = '../../ATOMICUS/tools/_iaea_ground_states.csv';
  const NIST_CODATA_PATH = './data/nist-codata-2022-hydrogen-boundary.json';
  const EXCITATION_MAP_PATH = './data/nist-neutral-excitation-map.json';
  const TIME_RATIO_OPTIONS = Object.freeze([
    { ratio: 0.001, label: '0.001x â€” 1000x slower' },
    { ratio: 0.01, label: '0.01x â€” 100x slower' },
    { ratio: 0.1, label: '0.1x â€” 10x slower' },
    { ratio: 0.25, label: '0.25x â€” 4x slower' },
    { ratio: 0.5, label: '0.5x â€” half speed' },
    { ratio: 1, label: '1x â€” reference rate' },
    { ratio: 2, label: '2x â€” double speed' },
  ]);
  const CLOSURE_ATOMIC_NUMBERS = new Set([2, 10, 18, 36, 54, 86]);
  const NUCLEAR_CLOSE_PACKING_FRACTION = Math.PI / Math.sqrt(18);
  const NUCLEAR_MEASUREMENT_ANCHORS = Object.freeze({
    'H-1': { radiusM: NIST_CODATA_2022.protonRmsChargeRadiusM, uncertaintyM: 6.4e-19, label: 'NIST/CODATA 2022 proton rms charge radius' },
    'H-2': { radiusM: NIST_CODATA_2022.deuteronRmsChargeRadiusM, uncertaintyM: 2.7e-19, label: 'NIST/CODATA 2022 deuteron rms charge radius' },
    'He-4': { radiusM: NIST_CODATA_2022.alphaParticleRmsChargeRadiusM, uncertaintyM: 2.1e-18, label: 'NIST/CODATA 2022 alpha-particle rms charge radius' },
  });
  const NUCLEAR_PACKING = Object.freeze({
    goldenRatio: (1 + Math.sqrt(5)) / 2,
    moduleSpacing: 1.45 * 0.8414 * 1.5,
    internalRadius: 1.45 * 0.8414 * 0.65,
    coulombSpread: 0.30,
  });

  const $ = (id) => document.getElementById(id);
  const canvas = $('scene');
  const context = canvas.getContext('2d');
  const ui = {
    nuclide: $('nuclide'), reset: $('resetView'), pause: $('pause'), drive: $('drive'), tracks: $('tracks'),
    play: $('play'), previousIsotope: $('previousIsotope'), nextIsotope: $('nextIsotope'),
    previousClosure: $('previousClosure'), nextClosure: $('nextClosure'),
    timeRatio: $('timeRatio'), timeRatioValue: $('timeRatioValue'), contacts: $('contacts'),
    status: $('status'), composition: $('composition'), centre: $('centreReadout'), groundState: $('groundState'),
    driveAudit: $('driveAudit'), subshells: $('subshells'), falsification: $('falsification'),
    excitationMapSection: $('excitationMapSection'), excitationMap: $('excitationMap'),
  };

  const hydrogenCircularVelocityMps = SDT.alpha * SDT.c;
  const hydrogenBoundaryVelocityMps = hydrogenCircularVelocityMps;
  const protonLock = SDT.lockCoordination * SDT.hbar / (SDT.protonMass * SDT.c);
  const VALENCE_SPEED_FACTOR_BY_Z = Object.freeze({
    1: 137.035999177, 2: 101.94, 3: 217.68, 4: 165.55, 5: 175.47,
    6: 150.63, 7: 132.59, 8: 136.97, 9: 121.10, 10: 108.85,
    11: 222.97, 12: 182.80, 13: 206.60, 14: 177.04, 15: 156.09,
    16: 157.04, 17: 140.37, 18: 127.33, 19: 242.61, 20: 204.44,
    21: 197.34, 22: 193.44, 23: 194.61, 24: 194.33, 25: 185.39,
    26: 179.82, 27: 180.05, 28: 182.87, 29: 137.00, 92: 137.00,
  });
  const LAW_IV_RADII = Object.freeze({
    electronDisplacedVolumeM3: 9.980911e-62,
    protonDisplacedVolumeM3: 1.832648e-58,
    electronExclusionRadiusM: 2.877579e-21,
    protonExclusionRadiusM: 3.523683e-20,
    electronWakeRadiusM: NIST_CODATA_2022.classicalElectronRadiusM,
    protonWakeRadiusM: SDT.protonBoundary,
    protonMatterBoundaryM: SDT.protonBoundary,
    electronQuantumRadiusM: SDT.hbar / (SDT.electronMass * SDT.c),
    protonQuantumRadiusM: SDT.hbar / (SDT.protonMass * SDT.c),
  });
  const CONTACT_TORUS = Object.freeze({
    majorDiameterM: 2 * SDT.protonBoundary,
    majorRadiusM: SDT.protonBoundary,
    electronBodyRadiusM: Math.sqrt(LAW_IV_RADII.electronDisplacedVolumeM3 / (2 * Math.PI ** 2 * SDT.a0)),
    packingCount: LAW_IV_RADII.protonDisplacedVolumeM3 / LAW_IV_RADII.electronDisplacedVolumeM3,
    sixPiFifthComparison: 6 * Math.PI ** 5,
    electronClosureLengthM: 2 * Math.PI * SDT.a0,
  });

  function torusEnvelopeVolume(majorRadiusM, tubeRadiusM) {
    return 2 * Math.PI ** 2 * majorRadiusM * tubeRadiusM ** 2;
  }

  function protonTubeRadiusFromPacking(electronBodyRadiusM, packingCount = CONTACT_TORUS.packingCount) {
    return electronBodyRadiusM * Math.sqrt(
      packingCount * CONTACT_TORUS.electronClosureLengthM / (2 * Math.PI * SDT.protonBoundary),
    );
  }

  const contactTorusTubeRadiusM = protonTubeRadiusFromPacking(CONTACT_TORUS.electronBodyRadiusM);
  const contactTorusEnvelopeVolumeM3 = torusEnvelopeVolume(CONTACT_TORUS.majorRadiusM, contactTorusTubeRadiusM);

  function cBoundaryFromRadiusAndVelocity(radiusM, velocityMps) {
    return radiusM * (velocityMps / SDT.c) ** 2;
  }

  const hydrogenEventHorizonM = cBoundaryFromRadiusAndVelocity(SDT.a0, hydrogenBoundaryVelocityMps);
  const horizonReferenceResidual = hydrogenEventHorizonM - NIST_CODATA_2022.classicalElectronRadiusM;

  if (Math.abs(horizonReferenceResidual / NIST_CODATA_2022.classicalElectronRadiusM) > 5e-10) {
    throw new Error('Hydrogen c-boundary disagrees with the classical-electron-radius identity.');
  }

  function nuclearComponentEnvelopeRadius(packing) {
    const particleEnvelopeM = Math.max(
      ...packing.particles.map((particle) => magnitude(particle.point) * SDT.protonBoundary + SDT.protonBoundary),
    );
    const torusEnvelopeM = packing.modules
      .filter((module) => module.type === 'deuteron' || module.type === 'triton')
      .reduce((largest, module) => Math.max(
        largest,
        magnitude(module.centre) * SDT.protonBoundary + LAW_IV_RADII.protonMatterBoundaryM,
      ), 0);
    return Math.max(particleEnvelopeM, torusEnvelopeM);
  }

  function sdtNuclearRadius(massNumber) {
    if (massNumber === 1) return SDT.protonBoundary;
    return SDT.protonBoundary * Math.cbrt(massNumber / NUCLEAR_CLOSE_PACKING_FRACTION);
  }

  function sdtNuclearGeometryAudit(packing, preset) {
    const radiusM = sdtNuclearRadius(preset.mass_number);
    const constructedEnvelopeM = nuclearComponentEnvelopeRadius(packing);
    const measurement = NUCLEAR_MEASUREMENT_ANCHORS[preset.id] || null;
    return {
      radiusM,
      constructedEnvelopeM,
      residualM: radiusM - constructedEnvelopeM,
      fits: constructedEnvelopeM <= radiusM,
      measurement,
      measurementResidualM: measurement ? radiusM - measurement.radiusM : null,
    };
  }

  function eventHorizonContainmentAudit(packing, boundaryM) {
    const constructedEnvelopeM = nuclearComponentEnvelopeRadius(packing);
    return {
      constructedEnvelopeM,
      boundaryM,
      residualM: boundaryM - constructedEnvelopeM,
      fits: constructedEnvelopeM <= boundaryM,
    };
  }

  const state = {
    dataset: null,
    excitationMapData: null,
    model: null,
    width: 1,
    height: 1,
    zoom: 1,
    cameraYaw: -0.52,
    cameraPitch: 0.28,
    structureAngles: { x: 0, y: 0, z: 0 },
    angularVelocity: { x: 0, y: 0, z: 0 },
    phaseLockRotation: 0,
    dragging: false,
    pointerX: 0,
    pointerY: 0,
    timeRatio: 1,
    running: true,
    previousTime: performance.now(),
    lastAuditTime: 0,
    audit: null,
  };

  const vector = (x = 0, y = 0, z = 0) => ({ x, y, z });
  const add = (a, b) => vector(a.x + b.x, a.y + b.y, a.z + b.z);
  const subtract = (a, b) => vector(a.x - b.x, a.y - b.y, a.z - b.z);
  const multiply = (a, scalar) => vector(a.x * scalar, a.y * scalar, a.z * scalar);
  const dot = (a, b) => a.x * b.x + a.y * b.y + a.z * b.z;
  const cross = (a, b) => vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
  const magnitude = (a) => Math.sqrt(dot(a, a));
  const unit = (a) => {
    const size = magnitude(a);
    return size > 1e-300 ? multiply(a, 1 / size) : vector(0, 0, 1);
  };
  const clamp = (value, low, high) => Math.max(low, Math.min(high, value));
  const scientific = (value, digits = 5) => value.toExponential(digits).replace('e+', 'e');
  const decimal = (value, digits = 6) => new Intl.NumberFormat('en-AU', { maximumFractionDigits: digits }).format(value);
  const tau = Math.PI * 2;
  const TETRAHEDRON_DIRECTIONS = Object.freeze([
    unit(vector(1, 1, 1)), unit(vector(1, -1, -1)),
    unit(vector(-1, 1, -1)), unit(vector(-1, -1, 1)),
  ]);
  const AUFBAU_SEQUENCE = Object.freeze([
    ['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6],
    ['5s', 2], ['4d', 10], ['5p', 6], ['6s', 2], ['4f', 14], ['5d', 10], ['6p', 6], ['7s', 2],
    ['5f', 14], ['6d', 10], ['7p', 6],
  ]);
  const OCCUPATION_OVERRIDES = Object.freeze({
    24: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['3d', 5], ['4s', 1]],
    29: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['3d', 10], ['4s', 1]],
    41: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['4d', 4], ['5s', 1]],
    42: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['4d', 5], ['5s', 1]],
    44: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['4d', 7], ['5s', 1]],
    45: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['4d', 8], ['5s', 1]],
    46: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['4d', 10]],
    47: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['4d', 10], ['5s', 1]],
    57: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['5s', 2], ['4d', 10], ['5p', 6], ['5d', 1], ['6s', 2]],
    58: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['5s', 2], ['4d', 10], ['5p', 6], ['4f', 1], ['5d', 1], ['6s', 2]],
    64: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['5s', 2], ['4d', 10], ['5p', 6], ['6s', 2], ['4f', 7], ['5d', 1]],
    78: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['5s', 2], ['4d', 10], ['5p', 6], ['6s', 1], ['4f', 14], ['5d', 9]],
    79: [['1s', 2], ['2s', 2], ['2p', 6], ['3s', 2], ['3p', 6], ['4s', 2], ['3d', 10], ['4p', 6], ['5s', 2], ['4d', 10], ['5p', 6], ['6s', 1], ['4f', 14], ['5d', 10]],
  });
  const COMPOSITION_OVERRIDES = Object.freeze({
    'Li-6': { percent: '7.59(4)', source: 'NIST representative terrestrial composition' },
    'Li-7': { percent: '92.41(4)', source: 'NIST representative terrestrial composition' },
  });
  const LITHIUM_NUCLEAR_CONTROLS = Object.freeze({
    'Li-6': { spin: '1', magneticMoment: '+0.822056 nuclear magnetons' },
    'Li-7': { spin: '3/2', magneticMoment: '+3.25644 nuclear magnetons' },
  });

  function rotateX(a, angle) {
    const cosine = Math.cos(angle);
    const sine = Math.sin(angle);
    return vector(a.x, cosine * a.y - sine * a.z, sine * a.y + cosine * a.z);
  }

  function rotateY(a, angle) {
    const cosine = Math.cos(angle);
    const sine = Math.sin(angle);
    return vector(cosine * a.x + sine * a.z, a.y, -sine * a.x + cosine * a.z);
  }

  function rotateZ(a, angle) {
    const cosine = Math.cos(angle);
    const sine = Math.sin(angle);
    return vector(cosine * a.x - sine * a.y, sine * a.x + cosine * a.y, a.z);
  }

  function basisFor(axis) {
    const primary = unit(axis);
    const seed = Math.abs(primary.z) < 0.82 ? vector(0, 0, 1) : vector(0, 1, 0);
    const secondary = unit(cross(primary, seed));
    return { primary, secondary, tertiary: unit(cross(primary, secondary)) };
  }

  function crossingPolarTourBasis(nuclearAxis, branch) {
    const basis = basisFor(nuclearAxis);
    if (branch === 0) return basis;
    return { primary: basis.primary, secondary: basis.tertiary, tertiary: multiply(basis.secondary, -1) };
  }

  function directionInNuclearFrame(frame, localDirection) {
    return unit(add(
      add(multiply(frame.secondary, localDirection.x), multiply(frame.tertiary, localDirection.y)),
      multiply(frame.primary, localDirection.z),
    ));
  }

  function tropicallyOffsetTetrahedronDirections(frame) {
    const rotation = Math.PI / 4;
    return TETRAHEDRON_DIRECTIONS.map((direction) => {
      const localDirection = vector(
        direction.x * Math.cos(rotation) - direction.y * Math.sin(rotation),
        direction.x * Math.sin(rotation) + direction.y * Math.cos(rotation),
        direction.z,
      );
      return directionInNuclearFrame(frame, localDirection);
    });
  }

  function staggeredRingDirections(frame, count, height, phaseOffset = Math.PI / count) {
    const transverse = Math.sqrt(1 - height ** 2);
    const ring = (polarComponent, offset) => Array.from({ length: count }, (_, index) => {
      const phase = offset + index * tau / count;
      return unit(add(
        multiply(frame.primary, polarComponent),
        add(multiply(frame.secondary, transverse * Math.cos(phase)), multiply(frame.tertiary, transverse * Math.sin(phase))),
      ));
    });
    return [...ring(height, 0), ...ring(-height, phaseOffset)];
  }

  function equatorialRingDirections(frame, count, phaseOffset = 0) {
    return Array.from({ length: count }, (_, index) => {
      const phase = phaseOffset + index * tau / count;
      return unit(add(multiply(frame.secondary, Math.cos(phase)), multiply(frame.tertiary, Math.sin(phase))));
    });
  }

  function alternatingLatitudeDirections(frame, count, latitudeRad, phaseOffset = 0) {
    const equatorialComponent = Math.cos(latitudeRad);
    const polarComponent = Math.sin(latitudeRad);
    return Array.from({ length: count }, (_, index) => {
      const phase = phaseOffset + index * tau / count;
      const equatorialDirection = add(multiply(frame.secondary, Math.cos(phase)), multiply(frame.tertiary, Math.sin(phase)));
      const hemisphere = index % 2 === 0 ? 1 : -1;
      return unit(add(multiply(equatorialDirection, equatorialComponent), multiply(frame.primary, hemisphere * polarComponent)));
    });
  }

  function fibonacciSphereDirections(count) {
    const goldenAngle = Math.PI * (3 - Math.sqrt(5));
    return Array.from({ length: count }, (_, index) => {
      const height = 1 - 2 * (index + 0.5) / count;
      const radius = Math.sqrt(Math.max(0, 1 - height * height));
      const phase = index * goldenAngle;
      return vector(radius * Math.cos(phase), radius * Math.sin(phase), height);
    });
  }

  function relaxApogeeDirections(directions) {
    const relaxed = directions.map((direction) => unit(direction));
    for (let iteration = 0; iteration < 36; iteration += 1) {
      const next = relaxed.map((direction, index) => {
        let force = vector();
        for (let otherIndex = 0; otherIndex < relaxed.length; otherIndex += 1) {
          if (otherIndex === index) continue;
          const separation = subtract(direction, relaxed[otherIndex]);
          const distanceSquared = Math.max(dot(separation, separation), 1e-12);
          force = add(force, multiply(separation, 1 / (distanceSquared * Math.sqrt(distanceSquared))));
        }
        const tangentialForce = subtract(force, multiply(direction, dot(force, direction)));
        return unit(add(direction, multiply(tangentialForce, 0.075 / (1 + iteration * 0.06))));
      });
      relaxed.splice(0, relaxed.length, ...next);
    }
    return relaxed;
  }

  function maximumApogeeDirections(count, nuclearAxis) {
    const frame = basisFor(nuclearAxis);
    if (count === 1) return [frame.secondary];
    if (count === 2) return [frame.secondary, multiply(frame.secondary, -1)];
    if (count === 3) return equatorialRingDirections(frame, 3);
    if (count === 4) return TETRAHEDRON_DIRECTIONS.map((direction) => directionInNuclearFrame(frame, direction));
    if (count === 5) return [frame.primary, multiply(frame.primary, -1), ...equatorialRingDirections(frame, 3)];
    if (count === 6) return [frame.primary, multiply(frame.primary, -1), frame.secondary, multiply(frame.secondary, -1), frame.tertiary, multiply(frame.tertiary, -1)];
    return relaxApogeeDirections(fibonacciSphereDirections(count)).map((direction) => directionInNuclearFrame(frame, direction));
  }

  function assignMaximumApogeeGeometry(markers, nuclearAxis) {
    const ellipseMarkers = markers.filter((marker) => marker.nuclearEllipse);
    const apogeeDirections = maximumApogeeDirections(ellipseMarkers.length, nuclearAxis);
    ellipseMarkers.forEach((marker, index) => {
      const apogeeDirection = apogeeDirections[index];
      marker.apogeeDirection = apogeeDirection;
      marker.nuclearEllipse = createNucleusCentredEllipse(
        multiply(apogeeDirection, -1),
        nuclearAxis,
        marker.orbital.letter,
        marker.orbital.radiusM,
        marker.seatEngagement,
        marker.ellipseThreadSign,
      );
    });
  }

  function hopfRawPoint(parameter, phase) {
    const modulusSquared = parameter.x * parameter.x + parameter.y * parameter.y;
    const normalisation = Math.sqrt(1 + modulusSquared);
    const cosine = Math.cos(phase);
    const sine = Math.sin(phase);
    const z1Real = (parameter.x * cosine - parameter.y * sine) / normalisation;
    const z1Imaginary = (parameter.x * sine + parameter.y * cosine) / normalisation;
    const z2Real = cosine / normalisation;
    const z2Imaginary = sine / normalisation;
    const denominator = Math.max(1 - z2Imaginary, 1e-9);
    return vector(z1Real / denominator, z1Imaginary / denominator, z2Real / denominator);
  }

  function assignProtonSeededHopfFibres(markers, packing) {
    const protons = packing.particles
      .map((particle, index) => ({ particle, index }))
      .filter((entry) => entry.particle.proton);
    if (protons.length !== markers.length) throw new Error('Neutral proton-electron pairing requires one proton seed per electron tour.');
    const frame = basisFor(packing.axis);
    const groups = new Map();
    markers.forEach((marker, index) => {
      const proton = protons[index];
      const protonDirection = magnitude(proton.particle.point) > 1e-12
        ? unit(proton.particle.point)
        : maximumApogeeDirections(markers.length, packing.axis)[index];
      const localX = dot(protonDirection, frame.secondary);
      const localY = dot(protonDirection, frame.tertiary);
      const azimuth = Math.atan2(localY, localX) + index * Math.PI * (3 - Math.sqrt(5));
      const parameterRadius = 0.48 + 0.11 * ((index % 5) + 1) + 0.035 * marker.orbital.n;
      marker.protonPair = {
        protonIndex: proton.index,
        protonLabel: proton.particle.label,
      };
      marker.hopfParameter = vector(parameterRadius * Math.cos(azimuth), parameterRadius * Math.sin(azimuth), 0);
      const key = marker.orbital.n;
      if (!groups.has(key)) groups.set(key, []);
      groups.get(key).push(marker);
    });

    for (const group of groups.values()) {
      const samples = group.flatMap((marker) => Array.from({ length: 192 }, (_, sample) => hopfRawPoint(marker.hopfParameter, tau * sample / 192)));
      const centre = multiply(samples.reduce((sum, point) => add(sum, point), vector()), 1 / samples.length);
      const rawExtent = Math.max(...samples.map((point) => magnitude(subtract(point, centre))));
      const targetExtent = Math.max(...group.map((marker) => marker.orbital.radiusM));
      const scale = targetExtent / rawExtent;
      group.forEach((marker, index) => {
        marker.hopfFiber = { centre, scale, frame };
        marker.orientation = index % 2 === 0 ? 1 : -1;
        let extremePhase = 0;
        let extremeRadius = -Infinity;
        for (let sample = 0; sample < 720; sample += 1) {
          const phase = tau * sample / 720;
          const radius = magnitude(markerPosition(marker, phase));
          if (radius > extremeRadius) {
            extremeRadius = radius;
            extremePhase = phase;
          }
        }
        marker.phase = extremePhase;
        marker.apogeeDirection = unit(markerPosition(marker, extremePhase));
      });
    }
  }

  function minimumTourSeparation(markers) {
    if (markers.length < 2) return Number.POSITIVE_INFINITY;
    const sampleCount = 48;
    const loops = markers.map((marker) => Array.from({ length: sampleCount }, (_, index) => markerPosition(marker, tau * index / sampleCount)));
    let minimum = Number.POSITIVE_INFINITY;
    for (let first = 0; first < loops.length; first += 1) {
      for (let second = first + 1; second < loops.length; second += 1) {
        for (const firstPoint of loops[first]) {
          for (const secondPoint of loops[second]) minimum = Math.min(minimum, magnitude(subtract(firstPoint, secondPoint)));
        }
      }
    }
    return minimum;
  }

  function minimumApogeeSeparationRad(markers) {
    if (markers.length < 2) return null;
    let minimumAngle = Math.PI;
    for (let first = 0; first < markers.length; first += 1) {
      for (let second = first + 1; second < markers.length; second += 1) {
        minimumAngle = Math.min(minimumAngle, Math.acos(clamp(dot(markers[first].apogeeDirection, markers[second].apogeeDirection), -1, 1)));
      }
    }
    return minimumAngle;
  }

  function buildValenceSeatTopology(preset, nuclearAxis) {
    const principal = Math.max(...preset.subshells.map(([value]) => value));
    const carrierCount = preset.subshells
      .filter(([value]) => value === principal)
      .reduce((total, [, , occupancy]) => total + occupancy, 0);
    if (carrierCount < 3) return null;
    const frame = basisFor(nuclearAxis);
    let directions;
    let label;
    if (preset.atomic_number === 6 && carrierCount === 4) {
      directions = alternatingLatitudeDirections(frame, 4, Math.PI / 3);
      label = 'Carbon condition â€” four outer carriers alternate 60 degrees above and below the equator';
    } else if (carrierCount === 3) {
      directions = equatorialRingDirections(frame, 3);
      label = 'Boron condition â€” three outer carriers equally spaced around the equator (120 degrees)';
    } else if (carrierCount === 4) {
      directions = tropicallyOffsetTetrahedronDirections(frame);
      label = 'Stage 4 â€” atomic tetrahedron: tropically offset outer seats';
    } else if (carrierCount === 5) {
      directions = [frame.primary, multiply(frame.primary, -1), ...canonicalShellDirections(3).map((direction) => directionInNuclearFrame(frame, vector(direction.x, direction.y, 0)))];
      label = 'five-carrier interim frame: no supplied cycle-stage map';
    } else if (carrierCount === 6) {
      directions = staggeredRingDirections(frame, 3, 0.42);
      label = 'Stage 5 â€” offset triangles: three above / three below';
    } else if (carrierCount === 7) {
      directions = [frame.primary, multiply(frame.primary, -1), ...Array.from({ length: 5 }, (_, index) => {
        const phase = Math.PI / 10 + index * tau / 5;
        return unit(add(multiply(frame.secondary, Math.cos(phase)), multiply(frame.tertiary, Math.sin(phase))));
      })];
      label = 'seven-carrier interim frame: no supplied cycle-stage map';
    } else if (carrierCount === 8) {
      directions = staggeredRingDirections(frame, 4, 0.42, Math.PI / 4);
      label = 'Stage 6 â€” noble-gas closure: four above / four below';
    } else {
      directions = canonicalShellDirections(carrierCount).map((direction) => directionInNuclearFrame(frame, direction));
      label = `${carrierCount}-seat non-coplanar shell convention`;
    }
    return {
      principal,
      label,
      seats: directions.map((direction, index) => ({ direction, phase: 0, index })),
    };
  }

  function tourBasisAtSeat(seatDirection, nuclearAxis) {
    const primary = unit(seatDirection);
    const tangential = cross(nuclearAxis, primary);
    if (magnitude(tangential) < 1e-12) return basisFor(primary);
    const secondary = unit(tangential);
    return { primary, secondary, tertiary: unit(cross(primary, secondary)) };
  }

  function capacity(letter) {
    return MODE_LABELS[letter].length * 2;
  }

  function targetDisplacement(n, atomicNumber) {
    return (SDT.alpha * atomicNumber / n) ** 2;
  }

  function tourRadius(n, atomicNumber, kappaM) {
    return kappaM / targetDisplacement(n, atomicNumber);
  }

  function engineBohrSeat(n, atomicNumber) {
    return SDT.a0 * n * n / atomicNumber;
  }

  function carrierSpeed(radiusM, kappaM) {
    return SDT.c * Math.sqrt(kappaM / radiusM);
  }

  function solidAngle(radiusM, distanceM) {
    return Math.PI * radiusM ** 2 / distanceM ** 2;
  }

  function occlusionForce(radiusOne, radiusTwo, distanceM, pressureEffective) {
    return (Math.PI / 4) * pressureEffective * radiusOne ** 2 * radiusTwo ** 2 / distanceM ** 2;
  }

  function buildElementCalibration(preset) {
    const outerPrincipal = Math.max(...preset.subshells.map(([principal]) => principal));
    const atomRadiusM = engineBohrSeat(outerPrincipal, preset.atomic_number);
    const suppliedSpeedFactor = VALENCE_SPEED_FACTOR_BY_Z[preset.atomic_number];
    const circularSpeedFactor = suppliedSpeedFactor || outerPrincipal / (SDT.alpha * preset.atomic_number);
    const circularVelocityMps = SDT.c / circularSpeedFactor;
    const valenceVelocityMps = circularVelocityMps;
    const speedFactor = circularSpeedFactor;
    const kappaM = atomRadiusM / speedFactor ** 2;
    const hydrogenReference = preset.atomic_number === 1;
    return {
      atomRadiusM,
      outerPrincipal,
      circularVelocityMps,
      circularSpeedFactor,
      speedFactor,
      valenceVelocityMps,
      kappaM,
      eventHorizonM: kappaM,
      pressureEffective: 4 * SDT.alpha * SDT.hbar * SDT.c / (Math.PI * protonLock ** 2 * kappaM ** 2),
      chargeRadiusM: Math.sqrt(protonLock * kappaM),
      source: suppliedSpeedFactor
        ? (hydrogenReference ? 'NIST/CODATA hydrogen circular relation v = alpha c' : 'Atomicus first-ionization circular-equivalent ledger')
        : 'SDT hydrogenic fallback; no supplied element speed datum',
      observedVelocity: false,
    };
  }

  function orientByNuclearAxis(localDirection, nuclearAxis) {
    const basis = basisFor(nuclearAxis);
    return add(
      add(multiply(basis.secondary, localDirection.x), multiply(basis.tertiary, localDirection.y)),
      multiply(basis.primary, localDirection.z),
    );
  }

  function modeAxis(letter, mode, nuclearAxis) {
    let localDirection = H_HE_AXIS;
    if (letter === 'p') localDirection = [vector(1, 0, 0), vector(0, 1, 0), vector(0, 0, 1)][mode];
    else if (letter === 'd') localDirection = [vector(1, 1, 0), vector(1, 0, 1), vector(0, 1, 1), vector(1, 0, 0), vector(0, 0, 1)][mode];
    else if (letter === 'f') localDirection = [vector(0, 0, 1), vector(1, 0, 1), vector(0, 1, 1), vector(1, 1, 1), vector(1, 0.3, 0), vector(0.3, 1, 0), vector(1, -1, 1)][mode];
    return orientByNuclearAxis(localDirection, nuclearAxis);
  }

  function lobeDirections(letter, mode, nuclearAxis) {
    const axis = unit(modeAxis(letter, mode, nuclearAxis));
    if (letter === 's') return [axis];
    if (letter === 'p') return [axis, multiply(axis, -1)];
    if (letter === 'd') {
      if (mode === 4) return [axis, multiply(axis, -1)];
      const basis = basisFor(axis);
      return [unit(add(axis, basis.secondary)), unit(subtract(axis, basis.secondary)), unit(add(multiply(axis, -1), basis.secondary)), unit(subtract(multiply(axis, -1), basis.secondary))];
    }
    const basis = basisFor(axis);
    return [
      axis,
      multiply(axis, -1),
      unit(add(axis, basis.secondary)),
      unit(subtract(axis, basis.secondary)),
      unit(add(multiply(axis, -1), basis.tertiary)),
      unit(subtract(multiply(axis, -1), basis.tertiary)),
    ];
  }

  function lobeShape(letter, radiusM) {
    const shape = TOUR_ENVELOPE[letter];
    return { offset: radiusM * shape.offset, axial: radiusM * shape.axial, transverse: radiusM * shape.transverse };
  }

  function excitationSeat(level, calibration, elementData) {
    const bindingEnergyEv = elementData.ionization_limit_ev - level.excitation_ev;
    if (!(bindingEnergyEv > 0)) throw new Error(`${elementData.spectrum} level ${level.index} is not below the ionization limit.`);
    const bindingEnergyJ = bindingEnergyEv * 1.602176634e-19;
    const circularVelocityMps = Math.sqrt(2 * bindingEnergyJ / SDT.electronMass);
    const velocityMps = circularVelocityMps;
    const speedFactor = SDT.c / velocityMps;
    return {
      ...level,
      bindingEnergyEv,
      circularVelocityMps,
      velocityMps,
      speedFactor,
      radiusM: calibration.kappaM * speedFactor ** 2,
    };
  }

  function validateExcitationMap(data) {
    if (!data || !data.elements || !Number.isInteger(data.level_count_per_element)) throw new Error('Excitation map has no element ledger.');
    for (const [symbol, elementData] of Object.entries(data.elements)) {
      if (!Number.isFinite(elementData.ionization_limit_ev) || !Array.isArray(elementData.levels)
        || elementData.levels.length !== data.level_count_per_element) throw new Error(`${symbol} excitation ledger has the wrong size.`);
      let previousEnergy = 0;
      for (const level of elementData.levels) {
        if (!Number.isInteger(level.index) || !Number.isFinite(level.excitation_ev)
          || level.excitation_ev < previousEnergy || level.excitation_ev >= elementData.ionization_limit_ev) {
          throw new Error(`${symbol} excitation ledger is invalid or unordered.`);
        }
        previousEnergy = level.excitation_ev;
      }
    }
  }

  function createNucleusCentredEllipse(direction, nuclearAxis, letter, radiusM, seatEngagement, threadSign) {
    const shape = lobeShape(letter, radiusM);
    const majorDirection = unit(direction);
    const unthreadedMinor = magnitude(cross(nuclearAxis, majorDirection)) < 1e-12
      ? basisFor(majorDirection).secondary
      : unit(cross(nuclearAxis, majorDirection));
    const planeNormal = unit(cross(majorDirection, unthreadedMinor));
    const threadingTiltRad = threadSign === 0 ? 0 : threadSign * Math.PI / (2 * (seatEngagement + 1));
    const minorDirection = unit(add(
      multiply(unthreadedMinor, Math.cos(threadingTiltRad)),
      multiply(planeNormal, Math.sin(threadingTiltRad)),
    ));
    const majorRadiusM = radiusM + shape.offset;
    const eccentricity = Math.sqrt(seatEngagement / (seatEngagement + 1));
    return {
      majorDirection,
      minorDirection,
      majorRadiusM,
      minorRadiusM: majorRadiusM * Math.sqrt(1 - eccentricity ** 2),
      eccentricity,
      periapsisM: majorRadiusM * (1 - eccentricity),
      seatEngagement,
      threadingTiltRad,
    };
  }

  function edgePoint(orbital, direction, phase, plane = 0, tourBasis = null) {
    const shape = lobeShape(orbital.letter, orbital.radiusM);
    const basis = tourBasis || basisFor(direction);
    const center = orbital.letter === 's' ? vector() : multiply(basis.primary, shape.offset);
    const side = plane === 0 ? basis.secondary : plane === 1 ? basis.tertiary : basis.secondary;
    const other = plane === 2 ? basis.tertiary : basis.primary;
    if (plane === 2) {
      return add(center, add(multiply(side, shape.transverse * Math.cos(phase)), multiply(other, shape.transverse * Math.sin(phase))));
    }
    return add(center, add(multiply(basis.primary, shape.axial * Math.cos(phase)), multiply(side, shape.transverse * Math.sin(phase))));
  }

  function markerPosition(marker, phase = marker.phase) {
    if (marker.hopfFiber) {
      const raw = multiply(subtract(hopfRawPoint(marker.hopfParameter, phase), marker.hopfFiber.centre), marker.hopfFiber.scale);
      return add(
        add(multiply(marker.hopfFiber.frame.secondary, raw.x), multiply(marker.hopfFiber.frame.tertiary, raw.y)),
        multiply(marker.hopfFiber.frame.primary, raw.z),
      );
    }
    if (marker.nuclearEllipse) {
      return add(
        multiply(marker.nuclearEllipse.majorDirection, marker.nuclearEllipse.majorRadiusM * (Math.cos(phase) - marker.nuclearEllipse.eccentricity)),
        multiply(marker.nuclearEllipse.minorDirection, marker.nuclearEllipse.minorRadiusM * Math.sin(phase)),
      );
    }
    return edgePoint(marker.orbital, marker.direction, phase, 0, marker.tourBasis);
  }

  function markerArcScale(marker) {
    const phaseStep = 1e-5;
    const plus = markerPosition(marker, marker.phase + phaseStep);
    const minus = markerPosition(marker, marker.phase - phaseStep);
    return magnitude(subtract(plus, minus)) / (2 * phaseStep);
  }

  function minimumCoreClearance(marker) {
    let minimumRadiusM = Number.POSITIVE_INFINITY;
    for (let index = 0; index < 193; index += 1) {
      minimumRadiusM = Math.min(minimumRadiusM, magnitude(markerPosition(marker, tau * index / 192)));
    }
    return minimumRadiusM - marker.nuclearExclusionBoundaryM;
  }

  function assertCoreExclusion(markers, preset) {
    const crossingMarker = markers.find((marker) => minimumCoreClearance(marker) < -Math.max(marker.nuclearExclusionBoundaryM * 1e-12, 1e-30));
    if (crossingMarker) throw new Error(`${preset.id}: ${crossingMarker.orbital.label} crosses the selected element's exclusion boundary.`);
  }

  function normalisePhase(phase) {
    return ((phase % tau) + tau) % tau;
  }

  function assertRelativeAgreement(actual, expected, label, tolerance = 5e-10) {
    if (!Number.isFinite(actual) || Math.abs(actual - expected) / Math.abs(expected) > tolerance) {
      throw new Error(`NIST/CODATA calibration mismatch for ${label}.`);
    }
  }

  function validateNistBoundaryData(data) {
    const constants = data && data.constants;
    const derived = data && data.derived_hydrogen_anchor;
    if (!constants || !derived) throw new Error('NIST/CODATA boundary ledger has no constants or hydrogen anchor.');
    assertRelativeAgreement(constants.fine_structure_constant, NIST_CODATA_2022.alpha, 'alpha');
    assertRelativeAgreement(constants.speed_of_light_m_s, SDT.c, 'c', 0);
    assertRelativeAgreement(constants.bohr_radius_m, SDT.a0, 'Bohr radius');
    assertRelativeAgreement(constants.classical_electron_radius_m, NIST_CODATA_2022.classicalElectronRadiusM, 'classical electron radius');
    assertRelativeAgreement(constants.proton_rms_charge_radius_m, NIST_CODATA_2022.protonRmsChargeRadiusM, 'proton rms charge radius');
    assertRelativeAgreement(constants.deuteron_rms_charge_radius_m, NIST_CODATA_2022.deuteronRmsChargeRadiusM, 'deuteron rms charge radius');
    assertRelativeAgreement(constants.alpha_particle_rms_charge_radius_m, NIST_CODATA_2022.alphaParticleRmsChargeRadiusM, 'alpha-particle rms charge radius');
    assertRelativeAgreement(derived.circular_velocity_m_s, hydrogenCircularVelocityMps, 'hydrogen circular velocity');
    assertRelativeAgreement(derived.boundary_velocity_m_s, hydrogenBoundaryVelocityMps, 'hydrogen boundary velocity');
    assertRelativeAgreement(derived.calculated_boundary_m, hydrogenEventHorizonM, 'hydrogen boundary');
  }

  function validateDataset(data) {
    if (!data || !Array.isArray(data.presets) || data.presets.length === 0) throw new Error('Dataset has no presets.');
    for (const preset of data.presets) {
      if (!Number.isInteger(preset.atomic_number) || !Number.isInteger(preset.mass_number) || preset.mass_number < preset.atomic_number) {
        throw new Error(`${preset.id}: invalid nuclear integers.`);
      }
      let electrons = 0;
      for (const [n, letter, occupancy] of preset.subshells) {
        const l = LETTER_TO_L[letter];
        if (!Number.isInteger(n) || l === undefined || n < l + 1 || !Number.isInteger(occupancy) || occupancy < 1 || occupancy > capacity(letter)) {
          throw new Error(`${preset.id}: invalid ${n}${letter} occupancy.`);
        }
        electrons += occupancy;
      }
      if (electrons !== preset.atomic_number) throw new Error(`${preset.id}: electron total ${electrons} differs from Z ${preset.atomic_number}.`);
    }
  }

  function parseCsvRecords(csvText) {
    const rows = [];
    let row = [];
    let field = '';
    let quoted = false;
    for (let index = 0; index < csvText.length; index += 1) {
      const character = csvText[index];
      if (quoted) {
        if (character === '"' && csvText[index + 1] === '"') {
          field += '"';
          index += 1;
        } else if (character === '"') quoted = false;
        else field += character;
        continue;
      }
      if (character === '"') quoted = true;
      else if (character === ',') {
        row.push(field);
        field = '';
      } else if (character === '\n') {
        row.push(field);
        rows.push(row);
        row = [];
        field = '';
      } else if (character !== '\r') field += character;
    }
    if (field.length > 0 || row.length > 0) {
      row.push(field);
      rows.push(row);
    }
    const headers = rows.shift()?.map((header) => header.trim().replace(/^\uFEFF/, '')) || [];
    return rows.filter((values) => values.length === headers.length).map((values) => Object.fromEntries(headers.map((header, index) => [header, values[index].trim()])));
  }

  function getNeutralOccupation(atomicNumber, curatedByAtomicNumber) {
    const curated = curatedByAtomicNumber.get(atomicNumber);
    if (curated) return { subshells: curated.subshells.map((subshell) => [...subshell]), source: `curated local occupation record (${curated.source || 'source label not supplied'})` };
    const override = OCCUPATION_OVERRIDES[atomicNumber];
    const sequence = override || AUFBAU_SEQUENCE;
    let remainingElectrons = atomicNumber;
    const subshells = [];
    for (const [subshellName, maximumOccupancy] of sequence) {
      if (remainingElectrons <= 0) break;
      const match = /^(\d)([spdf])$/.exec(subshellName);
      if (!match) throw new Error(`Unsupported subshell name ${subshellName}.`);
      const occupancy = Math.min(remainingElectrons, maximumOccupancy);
      subshells.push([Number(match[1]), match[2], occupancy]);
      remainingElectrons -= occupancy;
    }
    if (remainingElectrons !== 0) throw new Error(`Occupation sequence stops before Z=${atomicNumber}.`);
    return { subshells, source: override ? 'repository closure-gate occupation input' : 'repository aufbau occupation input' };
  }

  function formatConfiguration(subshells) {
    return subshells.map(([principal, letter, occupancy]) => `${principal}${letter}${occupancy}`).join(' ');
  }

  function buildCuratedOccupationMap(data) {
    const curated = new Map();
    for (const preset of data.presets || []) curated.set(preset.atomic_number, preset);
    return curated;
  }

  function buildNaturalDataset(iaeaRecords, curatedOccupations) {
    const presets = iaeaRecords
      .filter((record) => {
        const atomicNumber = Number(record.z);
        const neutronNumber = Number(record.n);
        const abundance = Number(record.abundance);
        return Number.isInteger(atomicNumber) && atomicNumber >= 1 && atomicNumber <= 92
          && Number.isInteger(neutronNumber) && neutronNumber >= 0 && Number.isFinite(abundance) && abundance > 0;
      })
      .map((record) => {
        const atomicNumber = Number(record.z);
        const neutronNumber = Number(record.n);
        const massNumber = atomicNumber + neutronNumber;
        const occupation = getNeutralOccupation(atomicNumber, curatedOccupations);
        const id = `${record.symbol}-${massNumber}`;
        const composition = COMPOSITION_OVERRIDES[id];
        return {
          id,
          name: `natural ${record.symbol} isotope`,
          symbol: record.symbol,
          atomic_number: atomicNumber,
          mass_number: massNumber,
          naturalAbundance: composition?.percent || record.abundance,
          abundanceSource: composition?.source || 'supplied local catalogue abundance field',
          halfLife: record.half_life,
          subshells: occupation.subshells,
          configuration: formatConfiguration(occupation.subshells),
          occupationSource: occupation.source,
        };
      })
      .sort((first, second) => first.atomic_number - second.atomic_number || first.mass_number - second.mass_number);
    return { presets };
  }

  function grammarCounts(preset) {
    const neutronCount = preset.mass_number - preset.atomic_number;
    return {
      deuteronCount: 2 * preset.atomic_number - neutronCount - 2,
      tritonCount: neutronCount - preset.atomic_number,
    };
  }

  function canonicalShellDirections(count) {
    const directions = {
      1: [[0, 0, 1]],
      2: [[0, 0, 1], [0, 0, -1]],
      3: [[1, 0, 0], [-0.5, 0.8660254, 0], [-0.5, -0.8660254, 0]],
      4: [[1, 1, 1], [1, -1, -1], [-1, 1, -1], [-1, -1, 1]],
      5: [[0, 0, 1], [0, 0, -1], [1, 0, 0], [-0.5, 0.8660254, 0], [-0.5, -0.8660254, 0]],
      6: [[1, 0, 0], [-1, 0, 0], [0, 1, 0], [0, -1, 0], [0, 0, 1], [0, 0, -1]],
      12: [[0, 1, NUCLEAR_PACKING.goldenRatio], [0, -1, NUCLEAR_PACKING.goldenRatio], [0, 1, -NUCLEAR_PACKING.goldenRatio], [0, -1, -NUCLEAR_PACKING.goldenRatio], [1, NUCLEAR_PACKING.goldenRatio, 0], [-1, NUCLEAR_PACKING.goldenRatio, 0], [1, -NUCLEAR_PACKING.goldenRatio, 0], [-1, -NUCLEAR_PACKING.goldenRatio, 0], [NUCLEAR_PACKING.goldenRatio, 0, 1], [-NUCLEAR_PACKING.goldenRatio, 0, 1], [NUCLEAR_PACKING.goldenRatio, 0, -1], [-NUCLEAR_PACKING.goldenRatio, 0, -1]],
    };
    if (directions[count]) return directions[count].map(([x, y, z]) => unit(vector(x, y, z)));
    return Array.from({ length: count }, (_, index) => {
      const height = 1 - (2 * index + 1) / count;
      const radius = Math.sqrt(Math.max(0, 1 - height * height));
      const phase = tau * index / (NUCLEAR_PACKING.goldenRatio ** 2);
      return vector(radius * Math.cos(phase), radius * Math.sin(phase), height);
    });
  }

  function createPacking() {
    return { particles: [], links: [], modules: [], axis: H_HE_AXIS, axisSource: 'symmetric base; initial z-axis', construction: '', deuteronCount: 0, tritonCount: 0 };
  }

  function addParticle(packing, point, proton, group, label) {
    const index = packing.particles.length;
    packing.particles.push({ point, proton, group, label });
    return index;
  }

  function addModuleLink(packing, first, second, group) {
    packing.links.push({ first, second, group });
  }

  function addUnlikeNucleonContact(packing, first, second, group) {
    if (packing.particles[first].proton === packing.particles[second].proton) return false;
    addModuleLink(packing, first, second, group);
    return true;
  }

  function assertUnlikeNucleonContacts(packing, preset) {
    const invalidLink = packing.links.find((link) => packing.particles[link.first].proton === packing.particles[link.second].proton);
    if (invalidLink) throw new Error(`${preset.id}: same-type nucleon contact is not permitted.`);
  }

  function addAlphaModule(packing, centre = vector()) {
    const nucleonTypes = [true, false, true, false];
    const indexes = TETRAHEDRON_DIRECTIONS.map((direction, index) => addParticle(
      packing,
      add(centre, multiply(direction, NUCLEAR_PACKING.internalRadius)),
      nucleonTypes[index],
      'alpha',
      `alpha-${index + 1}`,
    ));
    for (let first = 0; first < indexes.length; first += 1) {
      for (let second = first + 1; second < indexes.length; second += 1) addUnlikeNucleonContact(packing, indexes[first], indexes[second], 'alpha');
    }
    packing.modules.push({ type: 'alpha', centre, axis: H_HE_AXIS, indexes });
  }

  function addDeuteronModule(packing, centre, axis, label) {
    const direction = unit(axis);
    const protonIndex = addParticle(packing, add(centre, multiply(direction, NUCLEAR_PACKING.internalRadius)), true, 'deuteron', `${label}-p`);
    const neutronIndex = addParticle(packing, add(centre, multiply(direction, -NUCLEAR_PACKING.internalRadius)), false, 'deuteron', `${label}-n`);
    addUnlikeNucleonContact(packing, protonIndex, neutronIndex, 'deuteron');
    packing.modules.push({ type: 'deuteron', centre, axis: direction, indexes: [protonIndex, neutronIndex] });
  }

  function addThreeNucleonModule(packing, centre, firstAxis, secondAxis, protonTypes, group, label) {
    const firstDirection = unit(firstAxis);
    const secondDirection = unit(secondAxis);
    const triangleDirections = [
      firstDirection,
      unit(add(multiply(firstDirection, -0.5), multiply(secondDirection, Math.sqrt(3) / 2))),
      unit(add(multiply(firstDirection, -0.5), multiply(secondDirection, -Math.sqrt(3) / 2))),
    ];
    const indexes = triangleDirections.map((direction, index) => addParticle(
      packing,
      add(centre, multiply(direction, NUCLEAR_PACKING.internalRadius)),
      protonTypes[index],
      group,
      `${label}-${index + 1}`,
    ));
    addUnlikeNucleonContact(packing, indexes[0], indexes[1], group);
    addUnlikeNucleonContact(packing, indexes[1], indexes[2], group);
    addUnlikeNucleonContact(packing, indexes[2], indexes[0], group);
    packing.modules.push({ type: group, centre, axis: unit(cross(firstDirection, secondDirection)), indexes });
  }

  function canonicalModuleCentres(moduleCount, atomicNumber, massNumber) {
    const centres = [];
    const spread = 1 + NUCLEAR_PACKING.coulombSpread * atomicNumber ** 2 / massNumber ** (4 / 3);
    const moduleDistance = NUCLEAR_PACKING.moduleSpacing * spread;
    let remainingModules = moduleCount;
    let shellIndex = 0;
    while (remainingModules > 0) {
      const shellCapacity = shellIndex === 0 ? 12 : 12 + 8 * shellIndex;
      const placedHere = Math.min(remainingModules, shellCapacity);
      const shellRadius = moduleDistance * (1 + 0.9 * shellIndex);
      canonicalShellDirections(placedHere).forEach((direction) => centres.push(multiply(direction, shellRadius)));
      remainingModules -= placedHere;
      shellIndex += 1;
    }
    return centres;
  }

  function principalPackingAxis(modules) {
    const positionedModules = modules.filter((module) => magnitude(module.centre) > 1e-12);
    if (positionedModules.length === 0) return H_HE_AXIS;
    const tensor = [[0, 0, 0], [0, 0, 0], [0, 0, 0]];
    let centreSum = vector();
    for (const module of positionedModules) {
      const direction = unit(module.centre);
      const weight = magnitude(module.centre) ** 2;
      tensor[0][0] += weight * direction.x * direction.x; tensor[0][1] += weight * direction.x * direction.y; tensor[0][2] += weight * direction.x * direction.z;
      tensor[1][0] += weight * direction.y * direction.x; tensor[1][1] += weight * direction.y * direction.y; tensor[1][2] += weight * direction.y * direction.z;
      tensor[2][0] += weight * direction.z * direction.x; tensor[2][1] += weight * direction.z * direction.y; tensor[2][2] += weight * direction.z * direction.z;
      centreSum = add(centreSum, module.centre);
    }
    let axis = unit(vector(0.41, 0.63, 0.65));
    for (let iteration = 0; iteration < 12; iteration += 1) axis = unit(vector(
      tensor[0][0] * axis.x + tensor[0][1] * axis.y + tensor[0][2] * axis.z,
      tensor[1][0] * axis.x + tensor[1][1] * axis.y + tensor[1][2] * axis.z,
      tensor[2][0] * axis.x + tensor[2][1] * axis.y + tensor[2][2] * axis.z,
    ));
    return magnitude(centreSum) > 1e-12 && dot(axis, centreSum) < 0 ? multiply(axis, -1) : axis;
  }

  function sourceDeuteronAxis(moduleIndex) {
    const phase = moduleIndex * 2.399963;
    return unit(vector(Math.cos(phase), Math.sin(phase) * 0.8, Math.sin(phase * 1.7)));
  }

  function sourceTritonAxes(moduleIndex) {
    const phase = moduleIndex * 2.399963;
    return {
      first: unit(vector(Math.cos(phase), 0, Math.sin(phase))),
      second: unit(vector(Math.sin(phase) * 0.3, 1, Math.cos(phase) * 0.3)),
    };
  }

  function buildLithiumPacking(preset, tritonCap) {
    const packing = createPacking();
    addAlphaModule(packing);
    const capAxis = multiply(TETRAHEDRON_DIRECTIONS[0], -1);
    const spread = 1 + NUCLEAR_PACKING.coulombSpread * preset.atomic_number ** 2 / preset.mass_number ** (4 / 3);
    const capCentre = multiply(capAxis, NUCLEAR_PACKING.moduleSpacing * spread);
    if (tritonCap) {
      const capBasis = basisFor(capAxis);
      addThreeNucleonModule(packing, capCentre, capBasis.secondary, capBasis.tertiary, [true, false, false], 'triton', 't1');
      packing.tritonCount = 1;
      packing.construction = 'alpha core -> one face-capping triton (alpha + t)';
    } else {
      addDeuteronModule(packing, capCentre, capAxis, 'd1');
      packing.deuteronCount = 1;
      packing.construction = 'alpha core -> one face-capping deuteron (alpha + d)';
    }
    packing.axis = capAxis;
    packing.axisSource = 'Li cap normal from the alpha face';
    return packing;
  }

  function buildGrammarPacking(preset) {
    if (preset.atomic_number === 1 && preset.mass_number === 1) {
      const packing = createPacking();
      addParticle(packing, vector(), true, 'proton', 'p');
      packing.construction = 'proton primitive (1H)';
      return packing;
    }
    if (preset.atomic_number === 1 && preset.mass_number === 2) {
      const packing = createPacking();
      addDeuteronModule(packing, vector(), H_HE_AXIS, 'd1');
      packing.deuteronCount = 1;
      packing.construction = 'deuteron primitive (2H)';
      return packing;
    }
    if (preset.atomic_number === 1 && preset.mass_number === 3) {
      const packing = createPacking();
      const basis = basisFor(H_HE_AXIS);
      addThreeNucleonModule(packing, vector(), basis.secondary, basis.tertiary, [true, false, false], 'triton', 't1');
      packing.tritonCount = 1;
      packing.construction = 'triton primitive (3H)';
      return packing;
    }
    if (preset.atomic_number === 2 && preset.mass_number === 3) {
      const packing = createPacking();
      const basis = basisFor(H_HE_AXIS);
      addThreeNucleonModule(packing, vector(), basis.secondary, basis.tertiary, [true, true, false], 'helion', 'h1');
      packing.construction = 'helion mirror base (3He: p-p-n)';
      return packing;
    }
    if (preset.atomic_number === 2 && preset.mass_number === 4) {
      const packing = createPacking();
      addAlphaModule(packing);
      packing.construction = 'alpha core base (4He)';
      return packing;
    }
    if (preset.atomic_number === 3 && preset.mass_number === 6) return buildLithiumPacking(preset, false);
    if (preset.atomic_number === 3 && preset.mass_number === 7) return buildLithiumPacking(preset, true);

    const counts = grammarCounts(preset);
    if (preset.atomic_number < 3 || counts.deuteronCount < 0 || counts.tritonCount < 0) {
      throw new Error(`${preset.id}: outside the declared alpha/deuteron/triton grammar scope.`);
    }
    const packing = createPacking();
    addAlphaModule(packing);
    const moduleTypes = [
      ...Array.from({ length: counts.deuteronCount }, () => 'deuteron'),
      ...Array.from({ length: counts.tritonCount }, () => 'triton'),
    ];
    const centres = canonicalModuleCentres(moduleTypes.length, preset.atomic_number, preset.mass_number);
    moduleTypes.forEach((moduleType, moduleOffset) => {
      const sourceIndex = moduleOffset + 1;
      if (moduleType === 'deuteron') addDeuteronModule(packing, centres[moduleOffset], sourceDeuteronAxis(sourceIndex), `d${moduleOffset + 1}`);
      else {
        const axes = sourceTritonAxes(sourceIndex);
        addThreeNucleonModule(packing, centres[moduleOffset], axes.first, axes.second, [true, false, false], 'triton', `t${moduleOffset - counts.deuteronCount + 1}`);
      }
    });
    packing.deuteronCount = counts.deuteronCount;
    packing.tritonCount = counts.tritonCount;
    packing.axis = principalPackingAxis(packing.modules);
    packing.axisSource = 'principal axis of canonical ordered module packing';
    packing.construction = `alpha core -> ${counts.deuteronCount} deuteron module(s) -> ${counts.tritonCount} triton module(s)`;
    return packing;
  }

  function minimumElectronRadius(markers) {
    return Math.min(...markers.flatMap((marker) => Array.from(
      { length: 192 },
      (_, index) => magnitude(markerPosition(marker, tau * index / 192)),
    )));
  }

  function nuclearDisplayGeometry(packing, displayExtentM, electronClearanceM) {
    const packedEnvelopeUnits = Math.max(
      ...packing.particles.map((particle) => magnitude(particle.point) + 1),
      1,
    );
    const envelopeRadiusM = Math.min(displayExtentM * 0.028, electronClearanceM * 0.22);
    return {
      scale: envelopeRadiusM / packedEnvelopeUnits,
      envelopeRadiusM,
      electronClearanceM,
    };
  }

  function createDisplayNucleus(packing, displayGeometry) {
    const displayScale = displayGeometry.scale;
    return packing.particles.map((particle) => ({ ...particle, point: multiply(particle.point, displayScale) }));
  }

  function createDisplayContactTori(packing, displayGeometry) {
    const displayScale = displayGeometry.scale;
    const majorRadius = CONTACT_TORUS.majorRadiusM / SDT.protonBoundary * displayScale;
    const physicalTubeRadius = contactTorusTubeRadiusM / SDT.protonBoundary * displayScale;
    const tubeRadius = Math.max(physicalTubeRadius, displayScale * 0.035);
    return packing.modules
      .filter((module) => module.type === 'deuteron' || module.type === 'triton')
      .map((module) => ({
        type: module.type,
        centre: multiply(module.centre, displayScale),
        axis: module.axis,
        majorRadius,
        tubeRadius,
        physicalTubeRadius,
      }));
  }

  function regularTetrahedronVolume(circumradiusM) {
    return 8 * circumradiusM ** 3 / (9 * Math.sqrt(3));
  }

  function buildContactGeometry(packing, preset, displayGeometry) {
    const alphaModules = packing.modules.filter((module) => module.type === 'alpha');
    const trefoilModules = createDisplayContactTori(packing, displayGeometry);
    if (alphaModules.length === 0 && trefoilModules.length === 0) return null;
    const contactCircumradiusM = NUCLEAR_PACKING.internalRadius * SDT.protonBoundary;
    const alphaContactVolumeM3 = regularTetrahedronVolume(contactCircumradiusM);
    const effectiveRadiusM = Math.sqrt(preset.atomic_number) * protonLock;
    return {
      alphaModules,
      trefoilModules,
      contactCircumradiusM,
      alphaContactVolumeM3,
      totalContactVolumeM3: alphaModules.length * alphaContactVolumeM3,
      effectiveRadiusM,
      effectiveVolumeM3: 4 * Math.PI * effectiveRadiusM ** 3 / 3,
      volumeForceExponent: 2 / 3,
      torusMajorDiameterM: CONTACT_TORUS.majorDiameterM,
      torusTubeRadiusM: contactTorusTubeRadiusM,
      torusEnvelopeVolumeM3: contactTorusEnvelopeVolumeM3,
      electronDisplacedVolumeM3: LAW_IV_RADII.electronDisplacedVolumeM3,
      protonDisplacedVolumeM3: LAW_IV_RADII.protonDisplacedVolumeM3,
      electronExclusionRadiusM: LAW_IV_RADII.electronExclusionRadiusM,
      protonExclusionRadiusM: LAW_IV_RADII.protonExclusionRadiusM,
      electronWakeRadiusM: LAW_IV_RADII.electronWakeRadiusM,
      protonWakeRadiusM: LAW_IV_RADII.protonWakeRadiusM,
      electronQuantumRadiusM: LAW_IV_RADII.electronQuantumRadiusM,
      protonQuantumRadiusM: LAW_IV_RADII.protonQuantumRadiusM,
      packingCount: CONTACT_TORUS.packingCount,
      sixPiFifthComparison: CONTACT_TORUS.sixPiFifthComparison,
    };
  }

  function buildModel(preset) {
    const calibration = buildElementCalibration(preset);
    const nuclearPacking = buildGrammarPacking(preset);
    assertUnlikeNucleonContacts(nuclearPacking, preset);
    const nuclearExclusionBoundaryM = calibration.eventHorizonM;
    const nuclearGeometry = sdtNuclearGeometryAudit(nuclearPacking, preset);
    const eventHorizonContainment = eventHorizonContainmentAudit(nuclearPacking, nuclearExclusionBoundaryM);
    const transverse2sAxis = (preset.atomic_number === 3 || preset.atomic_number === 4)
      && preset.subshells.some(([principal, letter]) => principal === 2 && letter === 's')
      ? basisFor(nuclearPacking.axis).secondary
      : null;
    const transverse2sReferencePhase = preset.atomic_number === 4 ? Math.PI : 0;
    const carbonPolar1sTours = preset.atomic_number === 6
      && preset.subshells.some(([principal, letter, occupancy]) => principal === 1 && letter === 's' && occupancy === 2);
    const valenceTopology = buildValenceSeatTopology(preset, nuclearPacking.axis);
    const orbitals = [];
    const markers = [];
    const isHeliumDyad = preset.atomic_number === 2
      && preset.subshells.length === 1
      && preset.subshells[0][0] === 1
      && preset.subshells[0][1] === 's'
      && preset.subshells[0][2] === 2;
    let orbitalId = 0;
    let markerId = 0;
    let outerRadiusM = 0;
    let valenceSeatIndex = 0;
    for (const [n, letter, occupancy] of preset.subshells) {
      const modeCount = MODE_LABELS[letter].length;
      for (let mode = 0; mode < modeCount; mode += 1) {
        const electronCount = mode < occupancy ? 1 + (mode + modeCount < occupancy ? 1 : 0) : 0;
        if (electronCount === 0) continue;
        const transverse2sTour = transverse2sAxis && n === 2 && letter === 's';
        const carbonPolarTour = carbonPolar1sTours && n === 1 && letter === 's' && electronCount === 2;
        const valenceTopologyTour = valenceTopology && n === valenceTopology.principal;
        const nucleusCentredEllipseTour = n > 1;
        const closureRadiusM = tourRadius(n, preset.atomic_number, calibration.kappaM);
        const seatEngagement = electronCount === 2 ? 2 : 1;
        const radiusM = closureRadiusM;
        const baseLayout = carbonPolarTour ? 'crossed polar 1s tour planes' : valenceTopologyTour ? valenceTopology.label : transverse2sTour ? 'transverse 2s initial tour axis' : 'canonical lobe axis';
        const orbital = {
          id: orbitalId,
          n,
          letter,
          mode,
          label: `${n}${MODE_LABELS[letter][mode]}`,
          radiusM,
          closureRadiusM,
          speedMps: carrierSpeed(radiusM, calibration.kappaM),
          displacement: calibration.kappaM / radiusM,
          directions: transverse2sTour ? [transverse2sAxis] : lobeDirections(letter, mode, nuclearPacking.axis),
          layout: nucleusCentredEllipseTour ? `${baseLayout}; post-1s nucleus-centred elliptical tour` : baseLayout,
          customMarkerTours: carbonPolarTour || valenceTopologyTour,
          nucleusCentredEllipseTours: nucleusCentredEllipseTour,
          colour: COLOUR[letter],
        };
        orbitalId += 1;
        orbitals.push(orbital);
        outerRadiusM = Math.max(outerRadiusM, radiusM);
        for (let electron = 0; electron < electronCount; electron += 1) {
          const valenceSeat = valenceTopologyTour ? valenceTopology.seats[valenceSeatIndex++] : null;
          const tourBasis = carbonPolarTour ? crossingPolarTourBasis(nuclearPacking.axis, electron) : valenceSeat ? tourBasisAtSeat(valenceSeat.direction, nuclearPacking.axis) : null;
          const direction = tourBasis ? tourBasis.primary : orbital.directions[markerId % orbital.directions.length];
          const opposedSPair = letter === 's' && electronCount === 2;
          const focusOpposedPair = preset.atomic_number === 4 && n === 2 && letter === 's' && electronCount === 2;
          const ellipseDirection = focusOpposedPair && electron === 1 ? multiply(direction, -1) : direction;
          const threadSign = electronCount === 2 ? (electron === 0 ? 1 : -1) : 0;
          const ellipseThreadSign = focusOpposedPair ? 1 : threadSign;
          const initialPhase = focusOpposedPair
            ? transverse2sReferencePhase
            : carbonPolarTour ? electron * Math.PI : valenceSeat ? valenceSeat.phase : transverse2sTour ? transverse2sReferencePhase + (opposedSPair ? electron * Math.PI : 0) : opposedSPair ? electron * Math.PI : normalisePhase(markerId * Math.PI * 0.61803398875);
          const marker = {
            id: markerId,
            orbital,
            direction,
            phase: initialPhase,
            orientation: carbonPolarTour || valenceSeat || opposedSPair ? 1 : (electron % 2 === 0 ? 1 : -1),
            tourBasis,
            seatEngagement,
            nuclearExclusionBoundaryM,
            nuclearEllipse: nucleusCentredEllipseTour
              ? createNucleusCentredEllipse(ellipseDirection, nuclearPacking.axis, letter, radiusM, seatEngagement, ellipseThreadSign)
              : null,
            focusOpposedPair,
            ellipseThreadSign,
            trail: [],
            phaseRateRadps: null,
            phaseAccelerationRadps2: 0,
            tangentialForceN: 0,
            instantaneousSpeedMps: orbital.speedMps,
            forceN: 0,
            solidAngleSr: 0,
          };
          markers.push(marker);
          markerId += 1;
        }
      }
    }
    assignMaximumApogeeGeometry(markers, nuclearPacking.axis);
    assignProtonSeededHopfFibres(markers, nuclearPacking);
    const displayExtentM = Math.max(outerRadiusM * 1.55, SDT.a0 * 1.4 / preset.atomic_number);
    const electronClearanceM = minimumElectronRadius(markers);
    const nucleusDisplay = nuclearDisplayGeometry(nuclearPacking, displayExtentM, electronClearanceM);
    assertCoreExclusion(markers, preset);
    const minimumElectronTourSeparationM = minimumTourSeparation(markers);
    if (minimumElectronTourSeparationM <= 2 * LAW_IV_RADII.electronExclusionRadiusM) {
      throw new Error(`${preset.id}: proton-seeded electron fibres overlap at the electron exclusion scale.`);
    }
    return {
      preset,
      calibration,
      orbitals,
      markers,
      displayExtentM,
      nuclearExclusionBoundaryM,
      nuclearHorizonDisplayRadiusM: nucleusDisplay.envelopeRadiusM * 1.12,
      nucleusDisplay,
      nuclearGeometry,
      eventHorizonContainment,
      nuclearPacking,
      transverse2sAxis,
      transverse2sReferencePhase,
      carbonPolar1sTours,
      valenceTopology,
      minimumElectronTourSeparationM,
      nucleus: createDisplayNucleus(nuclearPacking, nucleusDisplay),
      contactGeometry: buildContactGeometry(nuclearPacking, preset, nucleusDisplay),
      isHeliumDyad,
      phaseClock: 0,
    };
  }

  function wrappedDifference(start, end) {
    let difference = end - start;
    while (difference > Math.PI) difference -= tau;
    while (difference < -Math.PI) difference += tau;
    return difference;
  }

  function phaseObservables(marker) {
    const phaseStep = 1e-5;
    const plus = markerPosition(marker, marker.phase + phaseStep);
    const minus = markerPosition(marker, marker.phase - phaseStep);
    const derivative = multiply(subtract(plus, minus), 1 / (2 * phaseStep));
    const phaseRate = Number.isFinite(marker.phaseRateRadps)
      ? marker.phaseRateRadps
      : marker.orientation * marker.orbital.speedMps / Math.max(markerArcScale(marker), SDT.a0 * 1e-12);
    const velocity = multiply(derivative, phaseRate);
    const current = markerPosition(marker);
    const latitude = (position) => Math.asin(clamp(position.z / Math.max(magnitude(position), SDT.a0 * 1e-12), -1, 1));
    const latitudeRate = wrappedDifference(latitude(minus), latitude(plus)) * phaseRate / (2 * phaseStep);
    return {
      phaseRate,
      latitudeRateRadps: latitudeRate,
      topDownSpeedMps: Math.hypot(velocity.x, velocity.y),
      currentPosition: current,
    };
  }

  function updateSDT(deltaViewSeconds) {
    if (!ui.drive.checked) return;
    const model = state.model;
    const deltaPhysicalSeconds = deltaViewSeconds * SDT.viewSecondsToPhysicalSeconds * state.timeRatio;
    const positions = model.markers.map((marker) => markerPosition(marker));
    const effectiveNuclearRadius = model.nuclearGeometry.radiusM;
    let totalTorque = vector();
    let momentOfInertia = 0;
    let totalForce = 0;
    let totalSolidAngle = 0;
    let maximumSolidAngle = 0;
    let minimumSpeed = Number.POSITIVE_INFINITY;
    let maximumSpeed = 0;
    let referencePhaseRate = 0;
    let totalTangentialForce = 0;
    let totalPhaseAcceleration = 0;
    const forceVectors = [];

    for (let index = 0; index < model.markers.length; index += 1) {
      const marker = model.markers[index];
      const position = positions[index];
      const radiusToNucleus = Math.max(magnitude(position), SDT.a0 * 1e-12);
      let force = multiply(unit(position), -occlusionForce(effectiveNuclearRadius, model.calibration.eventHorizonM, radiusToNucleus, model.calibration.pressureEffective));
      let omega = solidAngle(effectiveNuclearRadius, radiusToNucleus);
      for (let other = 0; other < model.markers.length; other += 1) {
        if (other === index) continue;
        const separation = subtract(position, positions[other]);
        const distance = Math.max(magnitude(separation), SDT.a0 * 1e-12);
        force = add(force, multiply(unit(separation), occlusionForce(LAW_IV_RADII.electronExclusionRadiusM, LAW_IV_RADII.electronExclusionRadiusM, distance, model.calibration.pressureEffective)));
        omega += solidAngle(LAW_IV_RADII.electronExclusionRadiusM, distance);
      }
      forceVectors[index] = force;
      marker.forceN = magnitude(force);
      marker.solidAngleSr = omega;
      totalTorque = add(totalTorque, cross(position, force));
      momentOfInertia += SDT.electronMass * radiusToNucleus ** 2;
      totalForce += marker.forceN;
      totalSolidAngle += omega;
      maximumSolidAngle = Math.max(maximumSolidAngle, omega);
    }

    for (let index = 0; index < model.markers.length; index += 1) {
      const marker = model.markers[index];
      const phaseStep = 1e-5;
      const plus = markerPosition(marker, marker.phase + phaseStep);
      const minus = markerPosition(marker, marker.phase - phaseStep);
      const derivative = multiply(subtract(plus, minus), 1 / (2 * phaseStep));
      const arcScale = Math.max(magnitude(derivative), SDT.a0 * 1e-12);
      const tangent = unit(derivative);
      if (!Number.isFinite(marker.phaseRateRadps)) marker.phaseRateRadps = marker.orientation * marker.orbital.speedMps / arcScale;
      marker.tangentialForceN = dot(forceVectors[index], tangent);
      marker.phaseAccelerationRadps2 = marker.tangentialForceN / (SDT.electronMass * arcScale);
      marker.phaseRateRadps += marker.phaseAccelerationRadps2 * deltaPhysicalSeconds;
      marker.phase = normalisePhase(marker.phase + marker.phaseRateRadps * deltaPhysicalSeconds);
      marker.instantaneousSpeedMps = Math.abs(marker.phaseRateRadps) * arcScale;
      marker.trail.push(markerPosition(marker));
      if (marker.trail.length > 132) marker.trail.shift();
      if (index === 0) referencePhaseRate = marker.phaseRateRadps;
      totalTangentialForce += Math.abs(marker.tangentialForceN);
      totalPhaseAcceleration += Math.abs(marker.phaseAccelerationRadps2);
      minimumSpeed = Math.min(minimumSpeed, marker.instantaneousSpeedMps);
      maximumSpeed = Math.max(maximumSpeed, marker.instantaneousSpeedMps);
    }

    const angularAcceleration = multiply(totalTorque, 1 / Math.max(momentOfInertia, 1e-300));
    state.angularVelocity = add(state.angularVelocity, multiply(angularAcceleration, deltaPhysicalSeconds));
    state.structureAngles.x += state.angularVelocity.x * deltaPhysicalSeconds;
    state.structureAngles.y += state.angularVelocity.y * deltaPhysicalSeconds;
    state.structureAngles.z += state.angularVelocity.z * deltaPhysicalSeconds;
    model.phaseClock = normalisePhase(model.phaseClock + referencePhaseRate * deltaPhysicalSeconds);
    state.phaseLockRotation += referencePhaseRate * deltaPhysicalSeconds / 4;
    const referenceObservation = phaseObservables(model.markers[0]);
    let oppositionErrorRad = null;
    if (model.isHeliumDyad) {
      const first = unit(markerPosition(model.markers[0]));
      const second = unit(markerPosition(model.markers[1]));
      oppositionErrorRad = Math.abs(Math.PI - Math.acos(clamp(dot(first, second), -1, 1)));
    }
    state.audit = {
      meanForceN: totalForce / model.markers.length,
      meanSolidAngleSr: totalSolidAngle / model.markers.length,
      maximumSolidAngleSr: maximumSolidAngle,
      torqueNm: magnitude(totalTorque),
      angularAccelerationRadps2: magnitude(angularAcceleration),
      angularVelocityRadps: magnitude(state.angularVelocity),
      minimumSpeedMps: minimumSpeed,
      maximumSpeedMps: maximumSpeed,
      meanTangentialForceN: totalTangentialForce / model.markers.length,
      meanPhaseAccelerationRadps2: totalPhaseAcceleration / model.markers.length,
      carrierCount: model.markers.length,
      phaseSlot: Math.floor(model.phaseClock / (Math.PI / 2)) + 1,
      phaseClockRad: model.phaseClock,
      latitudeRateRadps: referenceObservation.latitudeRateRadps,
      topDownSpeedMps: referenceObservation.topDownSpeedMps,
      oppositionErrorRad,
    };
  }

  function transformForView(point) {
    let result = rotateX(point, state.structureAngles.x);
    result = rotateY(result, state.structureAngles.y);
    result = rotateZ(result, state.structureAngles.z + state.phaseLockRotation);
    result = rotateY(result, state.cameraYaw);
    return rotateX(result, state.cameraPitch);
  }

  function project(point) {
    const transformed = transformForView(multiply(point, 1 / state.model.displayExtentM));
    const perspective = 1 / Math.max(0.50, 1 + transformed.z * 0.24);
    const scaleValue = Math.min(state.width, state.height) * 0.40 * state.zoom * perspective;
    return { x: state.width / 2 + transformed.x * scaleValue, y: state.height / 2 - transformed.y * scaleValue, z: transformed.z, perspective };
  }

  function drawBackground() {
    const gradient = context.createRadialGradient(state.width * 0.5, state.height * 0.48, 0, state.width * 0.5, state.height * 0.5, Math.max(state.width, state.height) * 0.75);
    gradient.addColorStop(0, '#17334b');
    gradient.addColorStop(0.48, '#091929');
    gradient.addColorStop(1, '#030912');
    context.fillStyle = gradient;
    context.fillRect(0, 0, state.width, state.height);
  }

  function drawNuclearEventHorizon() {
    const centre = project(vector());
    const viewportScale = Math.min(state.width, state.height) * 0.40 * state.zoom;
    const radius = Math.max(1, viewportScale * state.model.nuclearHorizonDisplayRadiusM / state.model.displayExtentM);
    const gradient = context.createRadialGradient(centre.x - radius * 0.2, centre.y - radius * 0.2, radius * 0.05, centre.x, centre.y, radius);
    gradient.addColorStop(0, '#05080e');
    gradient.addColorStop(0.56, '#000104');
    gradient.addColorStop(0.88, '#000000');
    gradient.addColorStop(1, 'rgba(30, 129, 181, 0.72)');
    context.save();
    context.fillStyle = gradient;
    context.beginPath();
    context.arc(centre.x, centre.y, radius, 0, tau);
    context.fill();
    context.strokeStyle = 'rgba(150, 231, 255, 0.86)';
    context.lineWidth = 1.35;
    context.beginPath();
    context.arc(centre.x, centre.y, radius, 0, tau);
    context.stroke();
    context.restore();
  }

  function drawPath(points, colour, alpha, width) {
    if (points.length < 2) return;
    context.save();
    context.strokeStyle = colour;
    context.globalAlpha = alpha;
    context.lineWidth = width;
    context.beginPath();
    points.forEach((point, index) => {
      const screen = project(point);
      if (index === 0) context.moveTo(screen.x, screen.y);
      else context.lineTo(screen.x, screen.y);
    });
    context.stroke();
    context.restore();
  }

  function edgeLoop(orbital, direction, plane, tourBasis = null) {
    const points = [];
    for (let index = 0; index <= 42; index += 1) points.push(edgePoint(orbital, direction, tau * index / 42, plane, tourBasis));
    return points;
  }

  function markerTourLoop(marker) {
    return Array.from({ length: 73 }, (_, index) => markerPosition(marker, tau * index / 72));
  }

  function quadraticBezier(start, control, end, fraction) {
    const inverse = 1 - fraction;
    return add(
      add(multiply(start, inverse * inverse), multiply(control, 2 * inverse * fraction)),
      multiply(end, fraction * fraction),
    );
  }

  function nucleonThreadedTourLoop(marker) {
    const proton = state.model.nucleus[marker.protonPair.protonIndex].point;
    let outer = markerPosition(marker, 0);
    let nearestDistance = magnitude(subtract(outer, proton));
    for (let index = 1; index < 192; index += 1) {
      const candidate = markerPosition(marker, tau * index / 192);
      const distance = magnitude(subtract(candidate, proton));
      if (distance < nearestDistance) {
        outer = candidate;
        nearestDistance = distance;
      }
    }
    const axis = unit(subtract(outer, proton));
    const frame = basisFor(axis);
    const nucleonRadius = state.model.nucleusDisplay.scale;
    const majorRadius = nucleonRadius * 0.46;
    const tubeRadius = nucleonRadius * 0.38;
    const firstAnchor = add(proton, multiply(frame.secondary, majorRadius + tubeRadius));
    const lane = nucleonRadius * (1.4 + 0.08 * (marker.id % 5));
    const firstControl = add(multiply(add(outer, firstAnchor), 0.5), multiply(frame.tertiary, lane));
    const inbound = Array.from({ length: 33 }, (_, index) => quadraticBezier(outer, firstControl, firstAnchor, index / 32));
    const winding = Array.from({ length: 129 }, (_, index) => {
      const phase = tau * index / 128;
      const toroidalDirection = add(
        multiply(frame.secondary, Math.cos(phase)),
        multiply(frame.tertiary, Math.sin(phase)),
      );
      return add(proton, add(
        multiply(toroidalDirection, majorRadius + tubeRadius * Math.cos(4 * phase)),
        multiply(axis, tubeRadius * Math.sin(4 * phase)),
      ));
    });
    return [...inbound, ...winding.slice(1), ...inbound.slice(0, -1).reverse()];
  }

  function drawNucleonThreadedTours() {
    for (const marker of state.model.markers) {
      const colour = marker.orbital.colour;
      const points = nucleonThreadedTourLoop(marker);
      drawPath(points, '#fff0b0', 0.16, 3.0);
      drawPath(points, colour, 0.74, 1.05);
    }
  }

  function drawPeriapsisMarker(marker, colour) {
    const periapsis = project(markerPosition(marker, 0));
    context.save();
    context.fillStyle = colour;
    context.globalAlpha = 0.95;
    context.beginPath();
    context.arc(periapsis.x, periapsis.y, 2.2 * periapsis.perspective, 0, tau);
    context.fill();
    context.strokeStyle = '#fff1b2';
    context.globalAlpha = 0.78;
    context.lineWidth = 0.85;
    context.beginPath();
    context.arc(periapsis.x, periapsis.y, 3.8 * periapsis.perspective, 0, tau);
    context.stroke();
    context.restore();
  }

  function drawLobeEdges() {
    for (const orbital of state.model.orbitals) {
      if (orbital.nucleusCentredEllipseTours) {
        const markers = state.model.markers.filter((marker) => marker.orbital === orbital);
        for (const marker of markers) {
          drawPath(markerTourLoop(marker), orbital.colour, 0.50, 1.35);
          if (marker.nuclearEllipse.seatEngagement > 1) drawPath(markerTourLoop(marker), '#fff0b0', 0.18, 2.9);
          drawPeriapsisMarker(marker, orbital.colour);
        }
        continue;
      }
      if (orbital.customMarkerTours) {
        const markers = state.model.markers.filter((marker) => marker.orbital === orbital);
        for (const marker of markers) {
          drawPath(edgeLoop(orbital, marker.direction, 0, marker.tourBasis), orbital.colour, 0.46, 1.15);
          drawPath(edgeLoop(orbital, marker.direction, 1, marker.tourBasis), orbital.colour, 0.28, 0.8);
          drawPath(edgeLoop(orbital, marker.direction, 2, marker.tourBasis), orbital.colour, 0.18, 0.65);
        }
        continue;
      }
      for (const direction of orbital.directions) {
        drawPath(edgeLoop(orbital, direction, 0), orbital.colour, 0.40, 0.9);
        drawPath(edgeLoop(orbital, direction, 1), orbital.colour, 0.26, 0.7);
        drawPath(edgeLoop(orbital, direction, 2), orbital.colour, 0.18, 0.6);
      }
    }
  }

  function drawAxis() {
    const extent = state.model.displayExtentM * 0.98;
    const nuclearAxis = state.model.nuclearPacking.axis;
    const start = project(multiply(nuclearAxis, -extent));
    const end = project(multiply(nuclearAxis, extent));
    context.save();
    context.strokeStyle = '#ffe49a';
    context.globalAlpha = 0.5;
    context.setLineDash([5, 6]);
    context.lineWidth = 1;
    context.beginPath();
    context.moveTo(start.x, start.y);
    context.lineTo(end.x, end.y);
    context.stroke();
    context.setLineDash([]);
    context.fillStyle = '#ffe49a';
    context.font = '600 11px system-ui, sans-serif';
    context.fillText('nuclear packing / 1s axis', end.x + 7, end.y - 5);
    context.restore();
  }

  function drawTransverse2sAxis() {
    const axis = state.model.transverse2sAxis;
    if (!axis) return;
    const extent = state.model.displayExtentM * 0.72;
    const start = project(multiply(axis, -extent));
    const end = project(multiply(axis, extent));
    context.save();
    context.strokeStyle = '#62e7bf';
    context.globalAlpha = 0.62;
    context.setLineDash([3, 5]);
    context.lineWidth = 1.3;
    context.beginPath();
    context.moveTo(start.x, start.y);
    context.lineTo(end.x, end.y);
    context.stroke();
    context.setLineDash([]);
    context.fillStyle = '#62e7bf';
    context.font = '600 11px system-ui, sans-serif';
    context.fillText('declared transverse 2s tour axis', end.x + 7, end.y - 5);
    context.restore();
  }

  function drawFourPhaseGuide() {
    if (!state.model.isHeliumDyad) return;
    const orbital = state.model.orbitals[0];
    const direction = orbital.directions[0];
    const colours = ['#ffe49a', '#73e0ff', '#d59aff', '#ff9acb'];
    const labels = ['I', 'II', 'III', 'IV'];
    for (let phase = 0; phase < 4; phase += 1) {
      const points = [];
      const start = phase * Math.PI / 2;
      const end = (phase + 1) * Math.PI / 2;
      for (let index = 0; index <= 14; index += 1) points.push(edgePoint(orbital, direction, start + (end - start) * index / 14));
      drawPath(points, colours[phase], 0.86, 2.25);
      const labelPoint = project(edgePoint(orbital, direction, (start + end) / 2));
      context.save();
      context.fillStyle = colours[phase];
      context.font = '700 11px system-ui, sans-serif';
      context.fillText(labels[phase], labelPoint.x + 5, labelPoint.y - 5);
      context.restore();
    }
  }

  function drawContactGeometry() {
    const geometry = state.model.contactGeometry;
    if (!ui.contacts.checked || !geometry) return;
    for (const module of geometry.trefoilModules) {
      const basis = basisFor(module.axis);
      const points = Array.from({ length: 97 }, (_, index) => {
        const phase = tau * index / 96;
        const toroidalDirection = add(
          multiply(basis.secondary, Math.cos(2 * phase)),
          multiply(basis.tertiary, Math.sin(2 * phase)),
        );
        return add(module.centre, add(
          multiply(toroidalDirection, module.majorRadius + module.tubeRadius * Math.cos(3 * phase)),
          multiply(basis.primary, module.tubeRadius * Math.sin(3 * phase)),
        ));
      });
      const colour = module.type === 'deuteron' ? '#62e7bf' : '#ff86cb';
      drawPath(points, colour, 0.18, 4.5);
      drawPath(points, colour, 0.92, 1.35);
    }
    const tetrahedronFaces = [[0, 1, 2], [0, 1, 3], [0, 2, 3], [1, 2, 3]];
    for (const module of geometry.alphaModules) {
      const particles = module.indexes.map((index) => state.model.nucleus[index]);
      if (particles.length !== 4) continue;
      const centre = particles.reduce((sum, particle) => add(sum, particle.point), vector());
      const contactCentre = multiply(centre, 1 / particles.length);
      const contactRadius = particles.reduce((sum, particle) => sum + magnitude(subtract(particle.point, contactCentre)), 0) / particles.length;
      context.save();
      context.fillStyle = '#62e7bf';
      context.strokeStyle = '#76f3ce';
      context.globalAlpha = 0.10;
      for (const face of tetrahedronFaces) {
        const first = project(particles[face[0]].point);
        context.beginPath();
        context.moveTo(first.x, first.y);
        for (const index of face.slice(1)) {
          const point = project(particles[index].point);
          context.lineTo(point.x, point.y);
        }
        context.closePath();
        context.fill();
      }
      context.globalAlpha = 0.82;
      context.lineWidth = 1.2;
      context.setLineDash([3, 3]);
      const basis = basisFor(module.axis);
      const poloidalPoints = Array.from({ length: 57 }, (_, index) => {
        const angle = tau * index / 56;
        return add(contactCentre, add(
          multiply(basis.primary, Math.cos(angle) * contactRadius * 1.18),
          multiply(basis.secondary, Math.sin(angle) * contactRadius * 1.18),
        ));
      });
      drawPath(poloidalPoints, '#76f3ce', 0.82, 1.25);
      context.setLineDash([]);
      const labelPoint = project(add(contactCentre, multiply(basis.primary, contactRadius * 1.35)));
      context.fillStyle = '#9affdd';
      context.font = '600 10px Consolas, ui-monospace, monospace';
      context.fillText('4N contact tetra / 1 poloidal reference loop', labelPoint.x + 5, labelPoint.y - 7);
      context.fillStyle = '#7fd7be';
      context.fillText('fixed r: Omega, F scale as V^(2/3); z has no V term', labelPoint.x + 5, labelPoint.y + 7);
      context.restore();
    }
  }

  function drawNucleus() {
    const particles = state.model.nucleus.map((particle, index) => ({ ...particle, index, screen: project(particle.point) })).sort((first, second) => first.screen.z - second.screen.z);
    const byIndex = new Map(particles.map((particle) => [particle.index, particle]));
    const linkColours = { alpha: '#c584ff', deuteron: '#62e7bf', triton: '#ff86cb', helion: '#8c9dff' };
    for (const link of state.model.nuclearPacking.links) {
      const first = byIndex.get(link.first);
      const second = byIndex.get(link.second);
      if (!first || !second) continue;
      context.save();
      context.strokeStyle = linkColours[link.group] || '#9db2c9';
      context.globalAlpha = 0.55;
      context.lineWidth = link.group === 'alpha' ? 1.35 : 1.75;
      context.beginPath();
      context.moveTo(first.screen.x, first.screen.y);
      context.lineTo(second.screen.x, second.screen.y);
      context.stroke();
      context.restore();
    }
    const baseRadius = clamp(6.5 / Math.sqrt(Math.sqrt(state.model.preset.mass_number)), 2.2, 5.2);
    for (const particle of particles) {
      const radius = baseRadius * particle.screen.perspective;
      const gradient = context.createRadialGradient(particle.screen.x - radius * 0.3, particle.screen.y - radius * 0.3, 0, particle.screen.x, particle.screen.y, radius);
      if (particle.proton) {
        gradient.addColorStop(0, '#fff4b5'); gradient.addColorStop(0.42, '#ffb14d'); gradient.addColorStop(1, '#bd4c39');
      } else {
        gradient.addColorStop(0, '#dcf7ff'); gradient.addColorStop(0.42, '#75bdf0'); gradient.addColorStop(1, '#285f8b');
      }
      context.fillStyle = gradient;
      context.beginPath();
      context.arc(particle.screen.x, particle.screen.y, radius, 0, tau);
      context.fill();
    }
  }

  function drawMarkersAndTours() {
    for (const marker of state.model.markers) {
      const wakeColour = state.model.isHeliumDyad ? (marker.id % 2 === 0 ? '#73e0ff' : '#ff9acb') : marker.orbital.colour;
      if (ui.tracks.checked) drawPath(marker.trail, wakeColour, 0.57, 1.25);
    }
    const markers = state.model.markers.map((marker) => ({ marker, screen: project(markerPosition(marker)) })).sort((a, b) => a.screen.z - b.screen.z);
    for (const entry of markers) {
      const radius = clamp(3.4 * entry.screen.perspective, 1.7, 4.6);
      const glow = context.createRadialGradient(entry.screen.x, entry.screen.y, 0, entry.screen.x, entry.screen.y, radius * 4);
      glow.addColorStop(0, 'rgba(255,255,255,1)');
      glow.addColorStop(0.28, 'rgba(255,224,151,.98)');
      glow.addColorStop(0.58, 'rgba(255,125,135,.32)');
      glow.addColorStop(1, 'rgba(255,125,135,0)');
      context.fillStyle = glow;
      context.beginPath();
      context.arc(entry.screen.x, entry.screen.y, radius * 4, 0, tau);
      context.fill();
      context.fillStyle = '#fff5c6';
      context.beginPath();
      context.arc(entry.screen.x, entry.screen.y, radius, 0, tau);
      context.fill();
    }
  }

  function render() {
    if (!state.model) return;
    drawBackground();
    drawAxis();
    drawNuclearEventHorizon();
    drawTransverse2sAxis();
    drawLobeEdges();
    drawNucleonThreadedTours();
    drawFourPhaseGuide();
    drawContactGeometry();
    drawNucleus();
    drawMarkersAndTours();
    context.fillStyle = 'rgba(201, 226, 241, 0.78)';
    context.font = '600 12px system-ui, sans-serif';
    context.fillText('Angular lobe outlines are geometry only. All finite radii and motion use the SDT closure shown at right.', 18, state.height - 23);
  }

  function updateStaticLedger() {
    const model = state.model;
    const preset = model.preset;
    const calibration = model.calibration;
    const packing = model.nuclearPacking;
    const electrons = preset.subshells.reduce((sum, row) => sum + row[2], 0);
    const neutrons = preset.mass_number - preset.atomic_number;
    const outer = model.orbitals.reduce((current, orbital) => orbital.radiusM > current.radiusM ? orbital : current, model.orbitals[0]);
    const zOuter = outer.displacement;
    const rBohr = engineBohrSeat(outer.n, preset.atomic_number);
    const closureRatio = outer.closureRadiusM / rBohr;
    const heliumDyad = model.isHeliumDyad
      ? '<div><dt>He ground tour</dt><dd>one circular path; 2 carriers at Delta-phi = pi; same sense</dd></div><div><dt>pair engagement</dt><dd>2; existing polar pi lock retained</dd></div><div><dt>field interaction</dt><dd>electron wakes may mesh/encase; electron bodies do not mesh</dd></div><div><dt>mesh loci</dt><dd>nuclear vortices + paired electron wakes</dd></div>'
      : '';
    const transverse2sLayout = model.transverse2sAxis
      ? `<div><dt>Li / Be 2s layout</dt><dd>tour axis is perpendicular to the displayed 1s polar axis; Li retains one post-1s oval. Be's two ovals receive antipodal apoapsides in the maximin layout and begin at their matched apoapsis phase.</dd></div>`
      : '';
    const carbonPolarLayout = model.carbonPolar1sTours
      ? '<div><dt>Carbon 1s layout</dt><dd>two polar great-ellipse tours share the nuclear-packing poles and cross there; their equatorial planes are perpendicular and the carriers begin pi-separated</dd></div>'
      : '';
    const valenceTopologyLayout = model.valenceTopology
      ? `<div><dt>Outer-seat frame</dt><dd>n = ${model.valenceTopology.principal}; ${model.valenceTopology.label}. This supplies only the lobe-frame input; post-1s apoapsides use the maximin redistribution shown below.</dd></div>`
      : '';
    const post1sEllipseMarkers = model.markers.filter((marker) => marker.nuclearEllipse);
    const pairedSeatMarkers = model.markers.filter((marker) => marker.seatEngagement > 1);
    const pairedEllipseMarkers = post1sEllipseMarkers.filter((marker) => marker.nuclearEllipse.seatEngagement > 1);
    const apogeeSeparationRad = minimumApogeeSeparationRad(post1sEllipseMarkers);
    const boronP1Marker = preset.atomic_number === 5
      ? post1sEllipseMarkers.find((marker) => marker.orbital.n === 2 && marker.orbital.letter === 'p')
      : null;
    const post1sEllipseLayout = post1sEllipseMarkers.length > 0
      ? `<div><dt>Post-1s core orbit</dt><dd>${post1sEllipseMarkers.length} ovoid carrier orbit(s) hold the declared event horizon at one focus.<br>a = r_tour + lobe offset; e = sqrt(engagement / (engagement + 1)); the ringed point is the single periapsis side. ${pairedSeatMarkers.length} paired carrier(s) carry engagement 2; ${pairedEllipseMarkers.length} post-1s members use conjugate threaded planes.</dd></div>${boronP1Marker ? `<div><dt>Boron 2p1 enclosure</dt><dd>a_p1 = ${decimal(boronP1Marker.nuclearEllipse.majorRadiusM * 1e12, 8)} pm; it encloses the 2s pair's a = ${decimal(model.markers.find((marker) => marker.orbital.n === 2 && marker.orbital.letter === 's').nuclearEllipse.majorRadiusM * 1e12, 8)} pm.</dd></div>` : ''}`
      : '';
    const nuclearGeometry = model.nuclearGeometry;
    const horizonContainment = model.eventHorizonContainment;
    const nuclearMeasurement = nuclearGeometry.measurement;
    const nuclearMeasurementUncertainty = nuclearMeasurement && Number.isFinite(nuclearMeasurement.uncertaintyM)
      ? ` +/- ${decimal(nuclearMeasurement.uncertaintyM * 1e15, 6)} fm`
      : '';
    const nuclearMeasurementLayout = nuclearMeasurement
      ? `<div><dt>NIST/CODATA comparison</dt><dd>r_rms = ${decimal(nuclearMeasurement.radiusM * 1e15, 6)}${nuclearMeasurementUncertainty}<br>R_SDT - r_rms = ${scientific(nuclearGeometry.measurementResidualM)} m; comparison only</dd></div><div><dt>Boundary / measured rms</dt><dd>K/r_rms = ${decimal(calibration.eventHorizonM / nuclearMeasurement.radiusM, 8)}<br>K is derived; r_rms is measured. This ratio does not measure an electron turning point.</dd></div>`
      : '<div><dt>NIST/CODATA comparison</dt><dd>No light-nucleus rms anchor is loaded for this isotope.</dd></div>';
    const nuclearGeometryLayout = `<div><dt>SDT nuclear radius</dt><dd>R_SDT = ${decimal(nuclearGeometry.radiusM * 1e15, 6)} fm<br>R_p(A/eta)^(1/3), eta = pi/sqrt(18); A = 1 uses R_p</dd></div><div><dt>Packing geometry audit</dt><dd>constructed envelope = ${decimal(nuclearGeometry.constructedEnvelopeM * 1e15, 6)} fm<br>${nuclearGeometry.fits ? 'within R_SDT; no coordinate rescaling applied' : `exceeds R_SDT by ${decimal(-nuclearGeometry.residualM * 1e15, 6)} fm; discrepancy retained`}</dd></div>${nuclearMeasurementLayout}`;
    const radiusTaxonomyLayout = `<div><dt>Electron length taxonomy</dt><dd>R_excl = ${scientific(LAW_IV_RADII.electronExclusionRadiusM)} m (actual displaced volume)<br>K_H = ${scientific(LAW_IV_RADII.electronWakeRadiusM)} m (c-boundary scale)<br>R_wake describes rapidly circulating displaced spations; it is not a material surface or containment radius<br>R_quantum = hbar/(m_e c) = ${scientific(LAW_IV_RADII.electronQuantumRadiusM)} m</dd></div><div><dt>Proton length taxonomy</dt><dd>R_excl = ${scientific(LAW_IV_RADII.protonExclusionRadiusM)} m (Law IV displaced volume)<br>matter/contact boundary = ${scientific(LAW_IV_RADII.protonMatterBoundaryM)} m<br>R_wake = ${scientific(LAW_IV_RADII.protonWakeRadiusM)} m (rotation/pressure perturbation only; no containment role)<br>R_quantum = hbar/(m_p c) = ${scientific(LAW_IV_RADII.protonQuantumRadiusM)} m</dd></div>`;
    const horizonCalibrationLayout = `<div><dt>${preset.atomic_number === 1 ? 'Hydrogen proposed boundary' : 'Element-specific proposed boundary'}</dt><dd>K = r_atom/k^2 = r_S/2 = ${decimal(calibration.eventHorizonM * 1e15, 10)} fm<br>r_atom = ${decimal(calibration.atomRadiusM * 1e12, 8)} pm; k = c/v = ${decimal(calibration.speedFactor, 9)}<br>v = ${scientific(calibration.valenceVelocityMps)} m/s; z = K/r; zk^2 = 1<br>${calibration.source}${preset.atomic_number === 1 ? `<br>identity check: K = r_e = ${decimal(NIST_CODATA_2022.classicalElectronRadiusM * 1e15, 10)} fm; residual = ${scientific(horizonReferenceResidual)} m` : ''}</dd></div><div><dt>Separate containment audit</dt><dd>SDT packing envelope = ${decimal(horizonContainment.constructedEnvelopeM * 1e15, 6)} fm<br>${horizonContainment.fits ? 'inside the selected element boundary' : `exceeds it by ${decimal(-horizonContainment.residualM * 1e15, 6)} fm; no radius override`}<br>At r = K, z = 1 and circulation reaches c; r &lt; K is the declared superluminal interior.</dd></div>`;
    const apogeeLayout = apogeeSeparationRad !== null
      ? `<div><dt>Apoapsis layout</dt><dd>all ${post1sEllipseMarkers.length} post-1s apogee directions are redistributed at each addition to maximise their minimum angular separation.<br>current minimum separation = ${decimal(apogeeSeparationRad * 180 / Math.PI, 6)} degrees.</dd></div>`
      : '';
    const protonFibreLayout = `<div><dt>Nucleon-threaded electron tours</dt><dd>${model.markers.length} neutral one-to-one proton/electron assignments.<br>Each closed displayed tour follows its original strand into the assigned proton geometry, completes four poloidal windings, and returns along that same strand. The proton is part of the tour geometry, not merely a coordinate label.<br>outer-fibre sampled minimum centreline separation = ${scientific(model.minimumElectronTourSeparationM)} m; electron exclusion diameter = ${scientific(2 * LAW_IV_RADII.electronExclusionRadiusM)} m.</dd></div>`;
    const contactVolumeLayout = model.contactGeometry
      ? `${model.contactGeometry.alphaModules.length > 0 ? `<div><dt>4N contact proxy</dt><dd>one alpha tetrahedron; r_contact = ${decimal(model.contactGeometry.contactCircumradiusM * 1e15, 6)} fm<br>V_alpha = ${scientific(model.contactGeometry.alphaContactVolumeM3)} m^3</dd></div>` : ''}${model.contactGeometry.trefoilModules.length > 0 ? `<div><dt>Law IV volume tube</dt><dd>${model.contactGeometry.trefoilModules.length} D/T path(s); centreline diameter = ${decimal(model.contactGeometry.torusMajorDiameterM * 1e15, 6)} fm<br>L_e = 2 pi a0; b_e = ${scientific(CONTACT_TORUS.electronBodyRadiusM)} m<br>b_p = ${scientific(model.contactGeometry.torusTubeRadiusM)} m; V_torus = ${scientific(model.contactGeometry.torusEnvelopeVolumeM3)} m^3<br>V_p input = ${scientific(model.contactGeometry.protonDisplacedVolumeM3)} m^3; residual = ${scientific(model.contactGeometry.torusEnvelopeVolumeM3 - model.contactGeometry.protonDisplacedVolumeM3)} m^3<br>display tube is exaggerated; geometric containment uses the physical matter/contact boundary, never R_wake or b_p</dd></div><div><dt>Packing-count audit</dt><dd>V_p/V_e = ${decimal(model.contactGeometry.packingCount, 9)}<br>6 pi^5 = ${decimal(model.contactGeometry.sixPiFifthComparison, 9)}; comparison only</dd></div>` : ''}<div><dt>volume drive audit</dt><dd>V_eff = ${scientific(model.contactGeometry.effectiveVolumeM3)} m^3<br>at fixed separation, Omega and F scale as V^${decimal(model.contactGeometry.volumeForceExponent, 6)}; z = kappa/r has no volume term</dd></div>`
      : '';
    ui.composition.innerHTML = `<dl>
      <div><dt>Nuclide</dt><dd><strong>${preset.name}</strong> (${preset.symbol}-${preset.mass_number})</dd></div>
      <div><dt>Protons, Z</dt><dd>${preset.atomic_number}</dd></div>
      <div><dt>Neutrons, A - Z</dt><dd>${neutrons}</dd></div>
      <div><dt>Composition record</dt><dd>${preset.naturalAbundance}%<br>${preset.abundanceSource}</dd></div>
      <div><dt>Nuclear order</dt><dd>${packing.construction}</dd></div>
      <div><dt>Module ledger</dt><dd>${packing.deuteronCount} d | ${packing.tritonCount} t | ${packing.modules.filter((module) => module.type === 'alpha').length} alpha</dd></div>
      <div><dt>Axis input</dt><dd>${packing.axisSource}</dd></div>
      <div><dt>Neutral electrons</dt><dd>${electrons} (ledger equals Z)</dd></div>
      <div><dt>Tour carriers</dt><dd>${model.markers.length}</dd></div>
    </dl>`;
    ui.centre.innerHTML = `<strong><sup>${preset.mass_number}</sup>${preset.symbol}</strong><span>${preset.atomic_number} p+ | ${neutrons} n0 | ${electrons} e-</span><span>SDT nuclear radius: ${decimal(nuclearGeometry.radiusM * 1e15, 6)} fm | element boundary: ${decimal(calibration.eventHorizonM * 1e15, 10)} fm</span><span>${horizonContainment.fits ? 'SDT packing lies inside the selected boundary' : 'SDT packing exceeds the selected boundary: audit failure retained'}</span>`;
    ui.groundState.innerHTML = `<dl>
      <div><dt>Occupation label</dt><dd>${preset.configuration}<br>${preset.occupationSource}</dd></div>
      <div><dt>Selected circular-speed input</dt><dd>v = ${scientific(calibration.valenceVelocityMps)} m/s<br>k = c/v = ${decimal(calibration.speedFactor, 9)}; z k^2 = 1<br>${calibration.source}</dd></div>
      <div><dt>K = r_atom/k^2</dt><dd>${scientific(calibration.kappaM)} m = ${decimal(calibration.kappaM * 1e15, 10)} fm</dd></div>
      <div><dt>outer z = K/r_orbit</dt><dd>${scientific(zOuter)}</dd></div>
      <div><dt>outer r_orbit</dt><dd>${scientific(outer.radiusM)} m<br>${decimal(outer.radiusM * 1e12, 8)} pm (${outer.label})</dd></div>
      <div><dt>closure r_tour / r_atom</dt><dd>${scientific(closureRatio)}</dd></div>
      ${heliumDyad}
      ${transverse2sLayout}
      ${carbonPolarLayout}
      ${valenceTopologyLayout}
      ${post1sEllipseLayout}
      ${apogeeLayout}
      ${protonFibreLayout}
      ${nuclearGeometryLayout}
      ${radiusTaxonomyLayout}
      ${horizonCalibrationLayout}
      ${contactVolumeLayout}
    </dl>`;
    ui.subshells.innerHTML = preset.subshells.map(([n, letter, occupancy]) => {
      const radiusPm = tourRadius(n, preset.atomic_number, calibration.kappaM) * 1e12;
      return `<tr><th>${n}${letter}<sup>${occupancy}</sup></th><td>${occupancy}</td><td>${MODE_LABELS[letter].length}-mode ${letter}</td><td>${decimal(radiusPm, 8)} pm</td></tr>`;
    }).join('');
    const elementExcitations = state.excitationMapData && state.excitationMapData.elements[preset.symbol];
    ui.excitationMapSection.hidden = !elementExcitations;
    ui.excitationMap.innerHTML = elementExcitations
      ? elementExcitations.levels.map((level) => {
        const seat = excitationSeat(level, calibration, elementExcitations);
        const status = seat.evaluation_status === 'bracketed_evaluated' ? ' [evaluated]' : '';
        return `<tr><th>${seat.index}. ${seat.configuration} ${seat.term}<sub>${seat.j}</sub>${status}</th><td>${decimal(seat.excitation_ev, 9)} eV</td><td>${decimal(seat.bindingEnergyEv, 9)} eV</td><td>${scientific(seat.velocityMps)} m/s</td><td>${decimal(seat.speedFactor, 8)}</td><td>${decimal(seat.radiusM * 1e12, 8)} pm</td></tr>`;
      }).join('')
      : '';
    const conflict = preset.atomic_number === 1
      ? '<strong>Hydrogen closure agrees.</strong> Here r_tour = r_bohr because Z = 1.'
      : `<strong>Element-specific closure active.</strong> K, event horizon, displacement, speed, and force all use r_atom/k^2 for the selected element. The displayed r_tour/r_bohr value is ${scientific(closureRatio)}.`;
    const lithiumControl = LITHIUM_NUCLEAR_CONTROLS[preset.id]
      ? `<br><strong>Li isotope control:</strong> ${preset.id} is recorded stable, has nuclear spin ${LITHIUM_NUCLEAR_CONTROLS[preset.id].spin}, and magnetic moment ${LITHIUM_NUCLEAR_CONTROLS[preset.id].magneticMoment}. Both lithium isotopes use the same neutral ${preset.configuration} occupation input. A larger Li-6 magnetic signal cannot be assigned to an isotope-specific valence drive without a separately measured coupling.`
      : '';
    const transverse2sAudit = model.transverse2sAxis
      ? '<br><strong>Li / Be geometry condition:</strong> the perpendicular 2s axis is derived from each selected nucleus. Li has one post-1s oval; Be receives the two antipodal apoapsides of the maximin two-carrier layout and begins with matched apoapsis phase. Separate atoms are not simultaneously simulated, so this is a shared frame convention, not a measured Li-Be dynamical relation or force term.'
      : '';
    const carbonPolarAudit = model.carbonPolar1sTours
      ? '<br><strong>Carbon geometry condition:</strong> crossed polar 1s tours are derived from the carbon nuclear-packing axis as a declared initial condition. No observed directional electron-track dataset validates the crossing.'
      : '';
    const carbonOuterSeatAudit = preset.atomic_number === 6
      ? '<br><strong>Carbon outer-seat condition:</strong> the supplied quarter-turn / alternating-latitude frame remains a lobe-frame input only. Its four post-1s apoapses are reset to the maximin tetrahedral layout; the engine does not claim a measured pressure equilibrium producing either construction.'
      : '';
    const valenceTopologyAudit = model.valenceTopology
      ? '<br><strong>Outer-seat audit:</strong> the supplied placement is an initial lobe-frame condition keyed to outer-shell occupancy and the displayed nuclear frame. It does not set the core-orbit apoapses, which are recomputed by the maximin layout. No resistance anisotropy, probability density, force law, or validation claim is added.'
      : '';
    const post1sEllipseAudit = post1sEllipseMarkers.length > 0
      ? `<br><strong>Post-1s ellipse condition:</strong> every n > 1 carrier follows an ovoid ellipse with the selected element's ${decimal(calibration.eventHorizonM * 1e15, 10)} fm event horizon at one focus: a = r_tour + existing lobe offset, e = sqrt(engagement/(engagement + 1)), and r_peri = a(1-e). The periapsis marker shows the one-sided closest approach. Every paired marker carries engagement 2: 1s retains its existing pi-locked polar relation, while a post-1s pair also receives phase-conjugate +/-30 degree plane tilts, making the two displayed ellipses thread. Every tour is checked against that boundary and rejected if it crosses. The existing occlusion calculation treats this core as the central parent of the orbit; engagement and the event-horizon interpretation remain model conditions, not observed electron trajectories.${boronP1Marker ? ' Boron 2p1 is the first p path and is geometrically outside the 2s pair under this declared construction.' : ''}`
      : '';
    const nuclearRadiusAudit = nuclearGeometry.fits
      ? `<br><strong>SDT nuclear-geometry audit:</strong> the unscaled packing envelope is ${decimal(nuclearGeometry.constructedEnvelopeM * 1e15, 6)} fm and lies within R_SDT = ${decimal(nuclearGeometry.radiusM * 1e15, 6)} fm. The renderer does not rescale positions or impose an experimental cap.`
      : `<br><strong>SDT nuclear-geometry finding:</strong> the unscaled packing envelope is ${decimal(nuclearGeometry.constructedEnvelopeM * 1e15, 6)} fm and exceeds R_SDT = ${decimal(nuclearGeometry.radiusM * 1e15, 6)} fm by ${decimal(-nuclearGeometry.residualM * 1e15, 6)} fm. The discrepancy remains visible; the renderer does not rescale positions or impose an experimental cap.`;
    const nuclearMeasurementAudit = nuclearMeasurement
      ? `<br><strong>NIST/CODATA measurement comparison:</strong> ${nuclearMeasurement.label} is r_rms = ${decimal(nuclearMeasurement.radiusM * 1e15, 6)}${nuclearMeasurementUncertainty}. The SDT radius differs by ${scientific(nuclearGeometry.measurementResidualM)} m. An rms radius is neither a hard surface nor a coordinate constraint in this renderer.`
      : '<br><strong>NIST/CODATA measurement scope:</strong> a light-nucleus rms comparison is loaded only for 1H, 2H, and 4He. No value is fabricated for this isotope.';
    const horizonContainmentAudit = horizonContainment.fits
      ? `<br><strong>Derived-boundary containment audit:</strong> the SDT packing envelope is ${decimal(horizonContainment.constructedEnvelopeM * 1e15, 6)} fm and lies inside K = ${decimal(calibration.eventHorizonM * 1e15, 10)} fm. This is an internal geometry result, not a measured electron turning point.`
      : `<br><strong>Derived-boundary internal failure:</strong> the SDT ${decimal(horizonContainment.constructedEnvelopeM * 1e15, 6)} fm packing envelope exceeds K = ${decimal(calibration.eventHorizonM * 1e15, 10)} fm by ${decimal(-horizonContainment.residualM * 1e15, 6)} fm. The conflict remains visible.`;
    const apogeeAudit = apogeeSeparationRad !== null
      ? `<br><strong>Apoapsis geometry condition:</strong> after each carrier addition, all post-1s apoapsis directions are recomputed as a maximin spherical layout. Counts 2 through 6 use antipodal, triangular, tetrahedral, triangular-bipyramidal, and octahedral constructions; larger counts use deterministic repulsive relaxation from a Fibonacci seed. This maximises angular separation numerically, not a measured electron configuration or added force.`
      : '';
    const contactGeometryAudit = model.contactGeometry
      ? `${model.contactGeometry.alphaModules.length > 0 ? '<br><strong>4-nucleon contact audit:</strong> the tetrahedron and poloidal loop are drawn from a declared packing proxy.' : ''}${model.contactGeometry.trefoilModules.length > 0 ? `<br><strong>D/T volume-tube audit:</strong> Law IV supplies V_disp,e and V_disp,p. Smearing V_disp,e over L=2 pi a0 gives b_e=${scientific(CONTACT_TORUS.electronBodyRadiusM)} m; conserving V_p/V_e along the proton path gives b_p=${scientific(contactTorusTubeRadiusM)} m. The rendered tube is exaggerated. R_wake represents rapidly rotating displaced spations and contributes no geometric containment. The containment boundary is the declared physical proton matter/contact radius ${scientific(LAW_IV_RADII.protonMatterBoundaryM)} m. The contact graph permits proton-neutron links only.</strong>` : ''}<br><strong>Displacement cascade:</strong> excluded physical volume cascades displacement into surrounding shells; shell loading supplies the pressure boundary against matter. Wake rotation is tracked separately, and no direct optical blocking is assigned absent a coherent polarising flux.`
      : '';
    ui.falsification.innerHTML = `${conflict}<br><strong>K-convention correction:</strong> K now uses the circular convention without a sqrt(2) conversion. For hydrogen, v=alpha c, k=1/alpha, and K=alpha^2 a0=2.8179403204 fm=r_e=r_S/2. The previous K=2r_e branch computed r_S while labelling it r_S/2. With z=K/r and k=c/v, v=c sqrt(K/r) gives zk^2=1 and v(K)=c; the model permits superluminal circulation for r&lt;K.<br><strong>Recoil scope:</strong> nuclear reduced mass belongs in the spectroscopic seat conversion, not in the invariant definition K_H=alpha^2 a0. No recoil factor silently rescales K in this build.<br><strong>Measurement verdict:</strong> no experiment loaded here measures a hard electron periapsis at K. Electron-capture and finite-size spectroscopy remain quantitative mechanism tests rather than classical trajectory measurements.<br><strong>Nuclear audit boundary:</strong> rms charge radii are measured distribution parameters, not hard surfaces. A K/r_rms ratio is comparison only.${lithiumControl}${transverse2sAudit}${carbonPolarAudit}${carbonOuterSeatAudit}${valenceTopologyAudit}${post1sEllipseAudit}${apogeeAudit}${nuclearRadiusAudit}${nuclearMeasurementAudit}${horizonContainmentAudit}${contactGeometryAudit}<br>${model.isHeliumDyad ? 'The dyad opposition is enforced as an initial condition and audited numerically; it is not an experimental fit.' : 'No observed finite lobe edge or trajectory dataset is loaded; the displayed closure result is not a validation claim.'}`;
  }

  function updateDriveLedger() {
    if (!state.audit) return;
    const enabled = ui.drive.checked ? 'enabled' : 'paused (no non-SDT substitute)';
    const heliumRows = state.model.isHeliumDyad ? `<div><dt>He pair separation</dt><dd>error from pi = ${scientific(state.audit.oppositionErrorRad)} rad</dd></div><div><dt>He wake condition</dt><dd>encased paired wake activity; no electron-body contact</dd></div>` : '';
    ui.driveAudit.innerHTML = `<dl>
      <div><dt>SDT drive</dt><dd>${enabled}</dd></div>
      <div><dt>display-time ratio</dt><dd>${decimal(state.timeRatio, 2)}x reference<br>presentation conversion only</dd></div>
      <div><dt>view clock</dt><dd>1 screen s = ${scientific(SDT.viewSecondsToPhysicalSeconds * state.timeRatio)} physical s<br>base ${scientific(SDT.viewSecondsToPhysicalSeconds)} s x ${decimal(state.timeRatio, 2)}</dd></div>
      <div><dt>carrier count</dt><dd>${state.audit.carrierCount}</dd></div>
      <div><dt>electron body occlusion</dt><dd>R_excl,e = ${scientific(LAW_IV_RADII.electronExclusionRadiusM)} m<br>geometric-mean charge radius is not a body cross-section</dd></div>
      <div><dt>four-phase slot</dt><dd>${state.audit.phaseSlot} / 4<br>phi = ${scientific(state.audit.phaseClockRad)} rad</dd></div>
      <div><dt>phase-locked rotation</dt><dd>atom angle = carrier phase / 4</dd></div>
      <div><dt>carrier speed range</dt><dd>${scientific(state.audit.minimumSpeedMps)} to ${scientific(state.audit.maximumSpeedMps)} m/s<br>v = c sqrt(K/r); z = K/r; k = c/v; z k^2 = 1</dd></div>
      <div><dt>mean tangential force</dt><dd>${scientific(state.audit.meanTangentialForceN)} N<br>projected from F_occlusion onto each tour</dd></div>
      <div><dt>mean phase acceleration</dt><dd>${scientific(state.audit.meanPhaseAccelerationRadps2)} rad/s^2<br>domega/dt = F_tangent / (m ds/dphi)</dd></div>
      <div><dt>3D latitude rate</dt><dd>${scientific(state.audit.latitudeRateRadps)} rad/s<br>observer metric, not a force</dd></div>
      <div><dt>top-down speed</dt><dd>${scientific(state.audit.topDownSpeedMps)} m/s<br>observer metric, not a force</dd></div>
      <div><dt>mean solid angle</dt><dd>${scientific(state.audit.meanSolidAngleSr)} sr</dd></div>
      <div><dt>max solid angle</dt><dd>${scientific(state.audit.maximumSolidAngleSr)} sr</dd></div>
      <div><dt>mean |F_occlusion|</dt><dd>${scientific(state.audit.meanForceN)} N</dd></div>
      <div><dt>net torque</dt><dd>${scientific(state.audit.torqueNm)} N m</dd></div>
      <div><dt>angular response</dt><dd>${scientific(state.audit.angularAccelerationRadps2)} rad/s^2<br>omega = ${scientific(state.audit.angularVelocityRadps)} rad/s</dd></div>
      ${heliumRows}
    </dl><p class="note">Fixed calibration: <code>r_H=a0(v_H/c)^2</code>. Direct electron-body terms use <code>R_excl,e</code>. Dynamic path: <code>z=kappa/r</code>, <code>v0=c sqrt(kappa/r)</code>, <code>Omega=pi R^2/r^2</code>, <code>F=(pi/4)P R1^2 R2^2/r^2</code>, <code>domega/dt=F_tangent/(m ds/dphi)</code>, and <code>tau=sum(r x F)</code>. Wake coupling is not replaced by a body collision term.</p>`;
    ui.status.textContent = `${state.model.preset.name}: ${state.audit.carrierCount} SDT tour carriers; displacement/occlusion drive ${ui.drive.checked ? 'active' : 'frozen'}.`;
  }

  function isOccupationClosure(preset) {
    return CLOSURE_ATOMIC_NUMBERS.has(preset.atomic_number);
  }

  function currentPresetIndex() {
    if (!state.dataset || !state.model) return -1;
    return state.dataset.presets.findIndex((preset) => preset.id === state.model.preset.id);
  }

  function closureTarget(direction) {
    if (!state.dataset || !state.model) return null;
    const atomicNumber = state.model.preset.atomic_number;
    const candidates = state.dataset.presets.filter((preset) => isOccupationClosure(preset)
      && (direction > 0 ? preset.atomic_number > atomicNumber : preset.atomic_number < atomicNumber));
    return direction > 0 ? candidates[0] : candidates[candidates.length - 1];
  }

  function updatePlaybackControls() {
    const ready = Boolean(state.model);
    ui.play.disabled = !ready || state.running;
    ui.pause.disabled = !ready || !state.running;
  }

  function updateNavigationControls() {
    const index = currentPresetIndex();
    const ready = index >= 0;
    ui.previousIsotope.disabled = !ready || index === 0;
    ui.nextIsotope.disabled = !ready || index === state.dataset.presets.length - 1;
    ui.previousClosure.disabled = !closureTarget(-1);
    ui.nextClosure.disabled = !closureTarget(1);
    updatePlaybackControls();
  }

  function setPlayback(running) {
    state.running = running;
    updatePlaybackControls();
  }

  function setTimeRatio(sliderValue) {
    const index = clamp(Math.round(Number(sliderValue)), 0, TIME_RATIO_OPTIONS.length - 1);
    const option = TIME_RATIO_OPTIONS[index];
    state.timeRatio = option.ratio;
    ui.timeRatio.value = String(index);
    ui.timeRatioValue.textContent = option.label;
    updateDriveLedger();
  }

  function selectNavigationTarget(target) {
    if (!target) return;
    ui.nuclide.value = target.id;
    selectPreset(target.id);
  }

  function navigateIsotope(direction) {
    const index = currentPresetIndex();
    if (index < 0) return;
    selectNavigationTarget(state.dataset.presets[index + direction]);
  }

  function navigateClosure(direction) {
    selectNavigationTarget(closureTarget(direction));
  }

  function selectPreset(id) {
    const preset = state.dataset.presets.find((item) => item.id === id);
    if (!preset) return;
    state.model = buildModel(preset);
    state.structureAngles = { x: 0, y: 0, z: 0 };
    state.angularVelocity = { x: 0, y: 0, z: 0 };
    state.phaseLockRotation = 0;
    state.audit = null;
    updateStaticLedger();
    updateSDT(0);
    updateDriveLedger();
    updateNavigationControls();
    render();
  }

  function resetView() {
    state.zoom = 1;
    state.cameraYaw = -0.52;
    state.cameraPitch = 0.28;
    state.structureAngles = { x: 0, y: 0, z: 0 };
    state.angularVelocity = { x: 0, y: 0, z: 0 };
    state.phaseLockRotation = 0;
    if (state.model) state.model.markers.forEach((marker) => { marker.trail = []; });
    render();
  }

  function resizeCanvas() {
    const bounds = canvas.getBoundingClientRect();
    const pixelRatio = Math.min(window.devicePixelRatio || 1, 2);
    canvas.width = Math.max(1, Math.round(bounds.width * pixelRatio));
    canvas.height = Math.max(1, Math.round(bounds.height * pixelRatio));
    context.setTransform(pixelRatio, 0, 0, pixelRatio, 0, 0);
    state.width = bounds.width;
    state.height = bounds.height;
  }

  function pointFromEvent(event) {
    const bounds = canvas.getBoundingClientRect();
    return { x: event.clientX - bounds.left, y: event.clientY - bounds.top };
  }

  function attachEvents() {
    ui.nuclide.addEventListener('change', (event) => selectPreset(event.target.value));
    ui.reset.addEventListener('click', resetView);
    ui.play.addEventListener('click', () => setPlayback(true));
    ui.pause.addEventListener('click', () => setPlayback(false));
    ui.previousIsotope.addEventListener('click', () => navigateIsotope(-1));
    ui.nextIsotope.addEventListener('click', () => navigateIsotope(1));
    ui.previousClosure.addEventListener('click', () => navigateClosure(-1));
    ui.nextClosure.addEventListener('click', () => navigateClosure(1));
    ui.timeRatio.addEventListener('input', (event) => setTimeRatio(event.target.value));
    ui.drive.addEventListener('change', () => updateDriveLedger());
    ui.contacts.addEventListener('change', () => render());
    canvas.addEventListener('wheel', (event) => {
      event.preventDefault();
      state.zoom = clamp(state.zoom * (event.deltaY < 0 ? 1.12 : 1 / 1.12), 0.35, 6);
      render();
    }, { passive: false });
    canvas.addEventListener('pointerdown', (event) => {
      const point = pointFromEvent(event);
      state.dragging = true;
      state.pointerX = point.x;
      state.pointerY = point.y;
      canvas.setPointerCapture(event.pointerId);
    });
    canvas.addEventListener('pointermove', (event) => {
      if (!state.dragging) return;
      const point = pointFromEvent(event);
      state.cameraYaw += (point.x - state.pointerX) * 0.008;
      state.cameraPitch = clamp(state.cameraPitch + (point.y - state.pointerY) * 0.008, -1.35, 1.35);
      state.pointerX = point.x;
      state.pointerY = point.y;
      render();
    });
    const finishPointer = (event) => {
      state.dragging = false;
      if (canvas.hasPointerCapture(event.pointerId)) canvas.releasePointerCapture(event.pointerId);
    };
    canvas.addEventListener('pointerup', finishPointer);
    canvas.addEventListener('pointercancel', finishPointer);
    new ResizeObserver(() => { resizeCanvas(); render(); }).observe(canvas);
    setTimeRatio(ui.timeRatio.value);
    updateNavigationControls();
  }

  function frame(timestamp) {
    const deltaSeconds = Math.min(0.05, (timestamp - state.previousTime) / 1000);
    state.previousTime = timestamp;
    if (state.model && state.running) updateSDT(deltaSeconds);
    if (state.model) {
      render();
      if (timestamp - state.lastAuditTime > 180) {
        updateDriveLedger();
        state.lastAuditTime = timestamp;
      }
    }
    requestAnimationFrame(frame);
  }

  async function boot() {
    resizeCanvas();
    attachEvents();
    requestAnimationFrame(frame);
    try {
      const [curatedResponse, iaeaResponse, nistResponse, excitationMapResponse] = await Promise.all([
        fetch('./data/nist-neutral-ground-state-configurations.json', { cache: 'no-store' }),
        fetch(IAEA_GROUND_STATE_PATH, { cache: 'no-store' }),
        fetch(NIST_CODATA_PATH, { cache: 'no-store' }),
        fetch(EXCITATION_MAP_PATH, { cache: 'no-store' }),
      ]);
      if (!curatedResponse.ok) throw new Error(`occupation request failed (${curatedResponse.status})`);
      if (!iaeaResponse.ok) throw new Error(`IAEA request failed (${iaeaResponse.status}); run the supplied PowerShell server from the workspace root.`);
      if (!nistResponse.ok) throw new Error(`NIST/CODATA calibration request failed (${nistResponse.status})`);
      if (!excitationMapResponse.ok) throw new Error(`NIST excitation-map request failed (${excitationMapResponse.status})`);
      const curatedData = await curatedResponse.json();
      validateNistBoundaryData(await nistResponse.json());
      state.excitationMapData = await excitationMapResponse.json();
      validateExcitationMap(state.excitationMapData);
      const iaeaRecords = parseCsvRecords(await iaeaResponse.text());
      const data = buildNaturalDataset(iaeaRecords, buildCuratedOccupationMap(curatedData));
      validateDataset(data);
      state.dataset = data;
      ui.nuclide.replaceChildren();
      const optionsBySymbol = new Map();
      for (const preset of data.presets) {
        if (!optionsBySymbol.has(preset.symbol)) optionsBySymbol.set(preset.symbol, []);
        optionsBySymbol.get(preset.symbol).push(preset);
      }
      for (const [symbol, presets] of optionsBySymbol) {
        const group = document.createElement('optgroup');
        group.label = symbol;
        for (const preset of presets) {
          const option = document.createElement('option');
          option.value = preset.id;
          option.textContent = `${preset.symbol}-${preset.mass_number} | ${preset.naturalAbundance}% natural abundance`;
          group.append(option);
        }
        ui.nuclide.append(group);
      }
      ui.nuclide.disabled = false;
      ui.nuclide.value = data.presets.some((preset) => preset.id === 'He-4') ? 'He-4' : data.presets[0].id;
      selectPreset(ui.nuclide.value);
    } catch (error) {
      ui.status.textContent = `Dataset error: ${error.message}. Run the supplied PowerShell server.`;
      ui.falsification.textContent = 'The occupation dataset did not load, so no lobe-tour model is running.';
    }
  }

  boot();
})();

