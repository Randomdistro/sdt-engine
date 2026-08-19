(() => {
  'use strict';

  const AU_M = 149597870700;
  const CMB_TEMPERATURE_K = 2.7255;
  const RADIATION_CONSTANT = 7.5657e-16;
  const CMB_PRESSURE_PA = RADIATION_CONSTANT * CMB_TEMPERATURE_K ** 4 / 3;
  const DATASET_URL = '../../Datasets/solar_occlusion_2026-08-19/jpl_de441_ecliptic_j2000_mercury_orbit.json';
  const RUN = { stepSeconds: 3600, displayExtentAu: 35 };
  const FIELD = { sunDirections: 160, planetDirections: 36, minimumExtentAu: 0.28 };
  const BODY_META = [
    { name: 'Sun', color: '#ffcf70' },
    { name: 'Mercury', color: '#b6b2aa' },
    { name: 'Venus', color: '#e7b56a' },
    { name: 'Earth', color: '#5e9cf6' },
    { name: 'Mars', color: '#d27048' },
    { name: 'Jupiter', color: '#dfb36d' },
    { name: 'Saturn', color: '#ead38b', ring: true },
    { name: 'Uranus', color: '#83dce5' },
    { name: 'Neptune', color: '#7589f1' }
  ];
  const MAGNETOPAUSES = {
    Mercury: { minimumR: 1.45, maximumR: 1.45, referenceRadiusKm: 2439.4, reference: 'R_M', range: '1.45 R_M crossing value' },
    Earth: { minimumR: 6, maximumR: 10, referenceRadiusKm: 6371, reference: 'R_E', range: '6-10 R_E dayside span' },
    Jupiter: { minimumR: 63, maximumR: 92, referenceRadiusKm: 71492, reference: 'R_J', range: '63 and 92 R_J modes' },
    Saturn: { minimumR: 17, maximumR: 29, referenceRadiusKm: 60268, reference: 'R_S', range: '17-29 R_S near-noon range' },
    Uranus: { minimumR: 17, maximumR: 28, referenceRadiusKm: 25559, reference: 'R_U', range: '17-28 R_U Voyager span' },
    Neptune: { minimumR: 23, maximumR: 26.5, referenceRadiusKm: 24764, reference: 'R_N', range: '23-26.5 R_N Voyager crossings' }
  };
  const canvas = document.getElementById('solar');
  const context = canvas.getContext('2d');
  const controls = document.getElementById('controls');
  const readout = document.getElementById('readout');
  const state = {
    seconds: 0,
    daysPerSecond: 8,
    running: false,
    fields: true,
    forceArrows: true,
    magnetopauses: true,
    labels: true,
    markers: true,
    referenceMarker: true,
    yaw: -0.7,
    pitch: 0.56,
    zoom: 1,
    selectedName: 'Mercury'
  };
  let experiment = null;
  let loadFailure = '';
  let previous = 0;
  let dragging = false;
  let dragged = false;
  let lastPointer = null;
  let pauseButton = null;

  function vector(x = 0, y = 0, z = 0) { return { x, y, z }; }
  function add(left, right) { return vector(left.x + right.x, left.y + right.y, left.z + right.z); }
  function subtract(left, right) { return vector(left.x - right.x, left.y - right.y, left.z - right.z); }
  function multiply(point, amount) { return vector(point.x * amount, point.y * amount, point.z * amount); }
  function magnitude(point) { return Math.hypot(point.x, point.y, point.z); }
  function unit(point) { const length = magnitude(point); return length ? multiply(point, 1 / length) : vector(); }
  function dot(left, right) { return left.x * right.x + left.y * right.y + left.z * right.z; }
  function cross(left, right) { return vector(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x); }
  function planar(point) { return vector(point.x, point.y, 0); }
  function formatScientific(value) { return Number.isFinite(value) && value !== 0 ? value.toExponential(3) : '0'; }
  function clamp(value, low, high) { return Math.max(low, Math.min(high, value)); }

  function rotate(point) {
    const cosYaw = Math.cos(state.yaw);
    const sinYaw = Math.sin(state.yaw);
    const yawedX = point.x * cosYaw + point.y * sinYaw;
    const yawedY = -point.x * sinYaw + point.y * cosYaw;
    const cosPitch = Math.cos(state.pitch);
    const sinPitch = Math.sin(state.pitch);
    return vector(yawedX, yawedY * cosPitch - point.z * sinPitch, yawedY * sinPitch + point.z * cosPitch);
  }

  function project(point, width, height) {
    const rotated = rotate(point);
    const scaleFactor = Math.min(width, height) * 0.44 / RUN.displayExtentAu * state.zoom;
    const perspective = 4 / (4 - rotated.z / RUN.displayExtentAu * 0.65);
    return { x: width / 2 + rotated.x * scaleFactor * perspective, y: height / 2 - rotated.y * scaleFactor * perspective, depth: rotated.z, perspective };
  }

  function resize() {
    const bounds = canvas.getBoundingClientRect();
    const ratio = Math.min(window.devicePixelRatio || 1, 2);
    const width = Math.max(1, Math.round(bounds.width * ratio));
    const height = Math.max(1, Math.round(bounds.height * ratio));
    if (canvas.width !== width || canvas.height !== height) {
      canvas.width = width;
      canvas.height = height;
    }
    context.setTransform(ratio, 0, 0, ratio, 0, 0);
    return { width: bounds.width, height: bounds.height };
  }

  function solidAngle(radiusM, distanceM) {
    const ratio = clamp(radiusM / Math.max(distanceM, radiusM), 0, 1);
    return 2 * Math.PI * (1 - Math.sqrt(Math.max(0, 1 - ratio * ratio)));
  }

  function angularRadius(radiusM, distanceM) {
    return Math.asin(clamp(radiusM / Math.max(distanceM, radiusM), 0, 1));
  }

  function visibleSourceOmega(targetIndex, sourceIndex, positions, bodies) {
    const targetPosition = positions[targetIndex];
    const sourceSeparation = subtract(positions[sourceIndex], targetPosition);
    const sourceDistance = magnitude(sourceSeparation);
    const sourceDirection = unit(sourceSeparation);
    const sourceRadius = angularRadius(bodies[sourceIndex].radiusM, sourceDistance);
    const sourceOmega = solidAngle(bodies[sourceIndex].radiusM, sourceDistance);
    const blockers = [];
    for (let blockerIndex = 0; blockerIndex < bodies.length; blockerIndex += 1) {
      if (blockerIndex === targetIndex || blockerIndex === sourceIndex) continue;
      const blockerSeparation = subtract(positions[blockerIndex], targetPosition);
      const blockerDistance = magnitude(blockerSeparation);
      if (blockerDistance >= sourceDistance) continue;
      const blockerDirection = unit(blockerSeparation);
      const blockerRadius = angularRadius(bodies[blockerIndex].radiusM, blockerDistance);
      const separation = Math.acos(clamp(dot(sourceDirection, blockerDirection), -1, 1));
      if (separation < sourceRadius + blockerRadius) blockers.push({ direction: blockerDirection, cosineRadius: Math.cos(blockerRadius) });
    }
    if (!blockers.length) return { omegaSr: sourceOmega, overlapCount: 0, visibility: 1 };
    const helper = Math.abs(sourceDirection.z) < 0.9 ? vector(0, 0, 1) : vector(0, 1, 0);
    const lateral = unit(cross(sourceDirection, helper));
    const vertical = unit(cross(lateral, sourceDirection));
    const samples = 2048;
    let visible = 0;
    const capDepth = 1 - Math.cos(sourceRadius);
    for (let sample = 0; sample < samples; sample += 1) {
      const cosTheta = 1 - capDepth * (sample + 0.5) / samples;
      const sinTheta = Math.sqrt(Math.max(0, 1 - cosTheta * cosTheta));
      const azimuth = sample * Math.PI * (3 - Math.sqrt(5));
      const ray = add(multiply(sourceDirection, cosTheta), add(multiply(lateral, sinTheta * Math.cos(azimuth)), multiply(vertical, sinTheta * Math.sin(azimuth))));
      if (!blockers.some((blocker) => dot(ray, blocker.direction) >= blocker.cosineRadius)) visible += 1;
    }
    const visibility = visible / samples;
    return { omegaSr: sourceOmega * visibility, overlapCount: blockers.length, visibility };
  }

  function planarForces(positions, bodies) {
    const forces = bodies.map(() => vector());
    const perTarget = bodies.map(() => ({ top: null, totalOmega: 0 }));
    let apparentOverlaps = 0;
    for (let targetIndex = 0; targetIndex < bodies.length; targetIndex += 1) {
      const target = bodies[targetIndex];
      const targetAreaM2 = Math.PI * target.radiusM ** 2;
      for (let sourceIndex = 0; sourceIndex < bodies.length; sourceIndex += 1) {
        if (sourceIndex === targetIndex) continue;
        const separation = subtract(positions[sourceIndex], positions[targetIndex]);
        const distanceM = magnitude(separation);
        const direction = unit(planar(separation));
        if (!magnitude(direction)) continue;
        const visibleSource = visibleSourceOmega(targetIndex, sourceIndex, positions, bodies);
        const omegaSr = visibleSource.omegaSr;
        const forceN = CMB_PRESSURE_PA * targetAreaM2 * omegaSr / (4 * Math.PI);
        forces[targetIndex] = add(forces[targetIndex], multiply(direction, forceN));
        perTarget[targetIndex].totalOmega += omegaSr;
        apparentOverlaps += visibleSource.overlapCount;
        const candidate = { sourceIndex, forceN, omegaSr, distanceM, direction, visibility: visibleSource.visibility };
        if (!perTarget[targetIndex].top || candidate.forceN > perTarget[targetIndex].top.forceN) perTarget[targetIndex].top = candidate;
      }
    }
    const accelerations = forces.map((force, index) => multiply(force, 1 / bodies[index].massKg));
    const totalForce = forces.reduce((sum, force) => add(sum, force), vector());
    return { forces, accelerations, totalForce, perTarget, apparentOverlaps };
  }

  function storePosition(trajectory, index, point) {
    const offset = index * 3;
    trajectory[offset] = point.x;
    trajectory[offset + 1] = point.y;
    trajectory[offset + 2] = point.z;
  }

  function readPosition(trajectory, index) {
    const offset = index * 3;
    return vector(trajectory[offset], trajectory[offset + 1], trajectory[offset + 2]);
  }

  function simulate(dataset) {
    const metaByName = new Map(BODY_META.map((body) => [body.name, body]));
    const bodies = dataset.bodies.map((input) => {
      const meta = metaByName.get(input.name);
      if (!meta || input.states.length !== 2 || !(input.mass_kg > 0) || !(input.radius_km > 0)) throw new Error(`Invalid physical input for ${input.name}`);
      return { ...meta, radiusM: input.radius_km * 1000, radiusKm: input.radius_km, massKg: input.mass_kg, states: input.states };
    });
    const durationSeconds = dataset.duration_days * 86400;
    const steps = Math.ceil(durationSeconds / RUN.stepSeconds);
    const trajectories = bodies.map(() => new Float64Array((steps + 1) * 3));
    const times = new Float64Array(steps + 1);
    let positions = bodies.map((body) => vector(...body.states[0].position_m));
    let velocities = bodies.map((body) => vector(...body.states[0].velocity_m_s));
    let forceState = planarForces(positions, bodies);
    const mediumImpulse = vector();
    const diagnostics = {
      initial: forceState,
      peakMercuryAcceleration: magnitude(forceState.accelerations[bodies.findIndex((body) => body.name === 'Mercury')]),
      peakNetForceN: magnitude(forceState.totalForce),
      apparentOverlaps: forceState.apparentOverlaps,
      mediumImpulse
    };
    bodies.forEach((body, index) => storePosition(trajectories[index], 0, positions[index]));
    for (let step = 0, elapsed = 0; step < steps; step += 1) {
      const stepSeconds = Math.min(RUN.stepSeconds, durationSeconds - elapsed);
      const predicted = positions.map((position, index) => add(add(position, multiply(velocities[index], stepSeconds)), multiply(forceState.accelerations[index], 0.5 * stepSeconds ** 2)));
      const terminalForceState = planarForces(predicted, bodies);
      velocities = velocities.map((velocity, index) => add(velocity, multiply(add(forceState.accelerations[index], terminalForceState.accelerations[index]), 0.5 * stepSeconds)));
      positions = predicted;
      elapsed += stepSeconds;
      forceState = terminalForceState;
      times[step + 1] = elapsed;
      bodies.forEach((body, index) => storePosition(trajectories[index], step + 1, positions[index]));
      diagnostics.peakMercuryAcceleration = Math.max(diagnostics.peakMercuryAcceleration, magnitude(forceState.accelerations[bodies.findIndex((body) => body.name === 'Mercury')]));
      diagnostics.peakNetForceN = Math.max(diagnostics.peakNetForceN, magnitude(forceState.totalForce));
      diagnostics.apparentOverlaps += forceState.apparentOverlaps;
      diagnostics.mediumImpulse.x -= forceState.totalForce.x * stepSeconds;
      diagnostics.mediumImpulse.y -= forceState.totalForce.y * stepSeconds;
      diagnostics.mediumImpulse.z -= forceState.totalForce.z * stepSeconds;
    }
    const mercuryIndex = bodies.findIndex((body) => body.name === 'Mercury');
    const terminalJpl = vector(...bodies[mercuryIndex].states[1].position_m);
    const terminalModel = readPosition(trajectories[mercuryIndex], steps);
    diagnostics.mercuryTerminalErrorM = magnitude(subtract(terminalModel, terminalJpl));
    diagnostics.mercuryTerminalReferenceM = terminalJpl;
    diagnostics.mercuryTerminalModelM = terminalModel;
    diagnostics.final = forceState;
    return { dataset, bodies, durationSeconds, steps, trajectories, times, diagnostics };
  }

  function sampledPosition(bodyIndex, seconds) {
    const clampedSeconds = clamp(seconds, 0, experiment.durationSeconds);
    let low = Math.min(experiment.steps - 1, Math.floor(clampedSeconds / RUN.stepSeconds));
    while (low < experiment.steps - 1 && experiment.times[low + 1] < clampedSeconds) low += 1;
    const high = Math.min(experiment.steps, low + 1);
    if (low === high) return readPosition(experiment.trajectories[bodyIndex], low);
    const lowTime = experiment.times[low];
    const highTime = experiment.times[high];
    const fraction = highTime === lowTime ? 0 : (clampedSeconds - lowTime) / (highTime - lowTime);
    const first = readPosition(experiment.trajectories[bodyIndex], low);
    const second = readPosition(experiment.trajectories[bodyIndex], high);
    return add(multiply(first, 1 - fraction), multiply(second, fraction));
  }

  function systemAt(seconds) {
    return experiment.bodies.map((body, index) => {
      const positionM = sampledPosition(index, seconds);
      return { body, index, positionM, position: multiply(positionM, 1 / AU_M), count: body.name === 'Sun' ? FIELD.sunDirections : FIELD.planetDirections };
    });
  }

  function fibonacciDirection(index, count) {
    const y = 1 - 2 * (index + 0.5) / count;
    const radial = Math.sqrt(1 - y * y);
    const angle = index * Math.PI * (3 - Math.sqrt(5));
    return vector(Math.cos(angle) * radial, y, Math.sin(angle) * radial);
  }

  function fieldExtent(item) {
    const radialDistance = magnitude(item.position);
    return item.body.name === 'Sun' ? Math.max(2.5, Math.min(31, radialDistance + 0.8)) : Math.max(FIELD.minimumExtentAu, Math.min(2.1, 0.18 + 0.30 * Math.sqrt(Math.max(radialDistance, 0.01))));
  }

  function drawField(item, width, height) {
    if (!state.fields) return;
    const extent = fieldExtent(item);
    const innerRadius = Math.min(extent * 0.16, 0.09 + item.body.radiusKm * 1000 / AU_M * 2);
    context.save();
    context.strokeStyle = item.body.name === 'Sun' ? '#7fd8e2' : item.body.color;
    context.lineWidth = item.body.name === 'Sun' ? 0.65 : 0.5;
    for (let index = 0; index < item.count; index += 1) {
      const direction = fibonacciDirection(index, item.count);
      const outer = project(add(item.position, multiply(direction, extent)), width, height);
      const inner = project(add(item.position, multiply(direction, innerRadius)), width, height);
      context.globalAlpha = (item.body.name === 'Sun' ? 0.10 : 0.16) * (0.45 + 0.55 * ((rotate(direction).z + 1) / 2));
      context.beginPath();
      context.moveTo(outer.x, outer.y);
      context.lineTo(inner.x, inner.y);
      context.stroke();
    }
    context.restore();
  }

  function drawTrajectory(bodyIndex, body, width, height) {
    const stride = Math.max(1, Math.ceil(experiment.steps / 360));
    context.save();
    context.strokeStyle = body.color;
    context.globalAlpha = body.name === state.selectedName ? 0.8 : 0.22;
    context.lineWidth = body.name === state.selectedName ? 1.45 : 0.75;
    context.beginPath();
    for (let step = 0; step <= experiment.steps; step += stride) {
      const point = project(multiply(readPosition(experiment.trajectories[bodyIndex], step), 1 / AU_M), width, height);
      if (step) context.lineTo(point.x, point.y); else context.moveTo(point.x, point.y);
    }
    const endpoint = project(multiply(readPosition(experiment.trajectories[bodyIndex], experiment.steps), 1 / AU_M), width, height);
    context.lineTo(endpoint.x, endpoint.y);
    context.stroke();
    context.restore();
  }

  function magnetopauseFrame(item) {
    const sunward = unit(multiply(item.position, -1));
    const helper = Math.abs(sunward.z) < 0.9 ? vector(0, 0, 1) : vector(0, 1, 0);
    const lateral = unit(cross(sunward, helper));
    return { sunward, lateral, vertical: unit(cross(lateral, sunward)) };
  }

  function magnetopausePoint(item, frame, noseAu, tailFraction, angle) {
    const axialDistance = noseAu * (1 - tailFraction);
    const radialDistance = noseAu * 0.78 * Math.sqrt(tailFraction) * (1 + 0.12 * tailFraction);
    const radialDirection = add(multiply(frame.lateral, Math.cos(angle)), multiply(frame.vertical, Math.sin(angle)));
    return add(item.position, add(multiply(frame.sunward, axialDistance), multiply(radialDirection, radialDistance)));
  }

  function drawMagnetopause(item, noseAu, opacity, lineWidth, dashed, width, height) {
    const frame = magnetopauseFrame(item);
    context.save();
    context.strokeStyle = item.body.color;
    context.globalAlpha = opacity;
    context.lineWidth = lineWidth;
    context.setLineDash(dashed ? [3, 4] : []);
    for (let ring = 1; ring <= 12; ring += 1) {
      const tailFraction = 5.5 * ring / 12;
      context.beginPath();
      for (let side = 0; side <= 20; side += 1) {
        const point = project(magnetopausePoint(item, frame, noseAu, tailFraction, side / 20 * 2 * Math.PI), width, height);
        if (side) context.lineTo(point.x, point.y); else context.moveTo(point.x, point.y);
      }
      context.stroke();
    }
    for (let side = 0; side < 20; side += 3) {
      context.beginPath();
      for (let ring = 0; ring <= 12; ring += 1) {
        const point = project(magnetopausePoint(item, frame, noseAu, 5.5 * ring / 12, side / 20 * 2 * Math.PI), width, height);
        if (ring) context.lineTo(point.x, point.y); else context.moveTo(point.x, point.y);
      }
      context.stroke();
    }
    context.restore();
  }

  function drawMagnetopauses(items, width, height) {
    if (!state.magnetopauses) return;
    items.forEach((item) => {
      const measurement = MAGNETOPAUSES[item.body.name];
      if (!measurement) return;
      const selected = item.body.name === state.selectedName;
      const convert = (radiusCount) => radiusCount * measurement.referenceRadiusKm * 1000 / AU_M;
      if (measurement.minimumR !== measurement.maximumR) {
        drawMagnetopause(item, convert(measurement.minimumR), selected ? 0.28 : 0.12, 0.5, true, width, height);
        drawMagnetopause(item, convert(measurement.maximumR), selected ? 0.28 : 0.12, 0.5, true, width, height);
      }
      drawMagnetopause(item, convert((measurement.minimumR + measurement.maximumR) / 2), selected ? 0.84 : 0.40, selected ? 1.2 : 0.75, false, width, height);
    });
  }

  function displayRadius(body, scaleFactor) {
    const trueRadiusPixels = body.radiusM / AU_M * scaleFactor;
    if (!state.markers) return trueRadiusPixels;
    return Math.max(body.name === 'Sun' ? 1.8 : 1.2, Math.min(body.name === 'Sun' ? 4.8 : 3.6, trueRadiusPixels));
  }

  function drawBody(item, scaleFactor) {
    const radius = displayRadius(item.body, scaleFactor) * item.screen.perspective;
    item.radius = radius;
    context.save();
    if (item.body.name === 'Sun') {
      const glow = context.createRadialGradient(item.screen.x, item.screen.y, 0, item.screen.x, item.screen.y, radius * 6);
      glow.addColorStop(0, 'rgba(255,207,112,.72)');
      glow.addColorStop(1, 'rgba(255,207,112,0)');
      context.fillStyle = glow;
      context.beginPath();
      context.arc(item.screen.x, item.screen.y, radius * 6, 0, Math.PI * 2);
      context.fill();
    }
    context.fillStyle = item.body.color;
    context.globalAlpha = 0.96;
    context.beginPath();
    context.arc(item.screen.x, item.screen.y, radius, 0, Math.PI * 2);
    context.fill();
    context.strokeStyle = 'rgba(255,255,255,.55)';
    context.lineWidth = 0.6;
    context.stroke();
    if (item.body.ring) {
      context.save();
      context.translate(item.screen.x, item.screen.y);
      context.rotate(-0.32);
      context.scale(1, 0.34);
      context.strokeStyle = '#dfcd94';
      context.globalAlpha = 0.8;
      context.lineWidth = Math.max(1, radius * 0.55);
      context.beginPath();
      context.arc(0, 0, radius * 1.9, 0, Math.PI * 2);
      context.stroke();
      context.restore();
    }
    if (state.labels || item.body.name === state.selectedName) {
      context.fillStyle = '#e3f0f2';
      context.globalAlpha = item.body.name === state.selectedName ? 1 : 0.74;
      context.font = '11px ui-monospace, monospace';
      context.fillText(item.body.name, item.screen.x + radius + 4, item.screen.y - radius - 4);
    }
    context.restore();
  }

  function drawSelectedForce(selectedItem, forceState, width, height) {
    if (!state.forceArrows) return;
    const acceleration = forceState.accelerations[selectedItem.index];
    const direction = unit(planar(acceleration));
    if (!magnitude(direction)) return;
    const origin = selectedItem.screen;
    const tipReference = project(add(selectedItem.position, multiply(direction, 0.1)), width, height);
    const screenDirection = unit(vector(tipReference.x - origin.x, tipReference.y - origin.y));
    const length = 32;
    const tip = { x: origin.x + screenDirection.x * length, y: origin.y + screenDirection.y * length };
    context.save();
    context.strokeStyle = '#ff9b6f';
    context.fillStyle = '#ff9b6f';
    context.globalAlpha = 0.95;
    context.lineWidth = 1.8;
    context.beginPath();
    context.moveTo(origin.x, origin.y);
    context.lineTo(tip.x, tip.y);
    context.stroke();
    context.beginPath();
    context.moveTo(tip.x, tip.y);
    context.lineTo(tip.x - screenDirection.x * 8 - screenDirection.y * 5, tip.y - screenDirection.y * 8 + screenDirection.x * 5);
    context.lineTo(tip.x - screenDirection.x * 8 + screenDirection.y * 5, tip.y - screenDirection.y * 8 - screenDirection.x * 5);
    context.closePath();
    context.fill();
    context.restore();
  }

  function drawReferenceMarker(width, height) {
    if (!state.referenceMarker || !experiment) return;
    const marker = project(multiply(experiment.diagnostics.mercuryTerminalReferenceM, 1 / AU_M), width, height);
    context.save();
    context.strokeStyle = '#fff5d3';
    context.globalAlpha = 0.92;
    context.lineWidth = 1.4;
    context.setLineDash([4, 3]);
    context.beginPath();
    context.arc(marker.x, marker.y, 5, 0, Math.PI * 2);
    context.stroke();
    context.setLineDash([]);
    context.fillStyle = '#fff5d3';
    context.font = '10px ui-monospace, monospace';
    context.fillText('JPL Mercury end', marker.x + 8, marker.y - 7);
    context.restore();
  }

  function selectedMagnetopauseText(body) {
    const measurement = MAGNETOPAUSES[body.name];
    if (measurement) return `Magnetopause: solid midpoint, dotted ${measurement.range}.`;
    if (body.name === 'Venus' || body.name === 'Mars') return 'Induced magnetic boundary: no numerical shell rendered.';
    return 'No planetary magnetopause shell rendered.';
  }

  function updateReadout(selectedItem, forceState) {
    if (!experiment) return;
    const body = selectedItem.body;
    const selected = forceState.perTarget[selectedItem.index];
    const top = selected.top;
    const acceleration = magnitude(forceState.accelerations[selectedItem.index]);
    const durationDays = experiment.dataset.duration_days;
    const timeDays = state.seconds / 86400;
    const mercuryErrorAu = experiment.diagnostics.mercuryTerminalErrorM / AU_M;
    const completion = state.seconds >= experiment.durationSeconds;
    const pairText = top ? `<strong>Largest planar pressure deficit: ${experiment.bodies[top.sourceIndex].name} to ${body.name}</strong><br>exact apparent solid angle = ${formatScientific(top.omegaSr)} sr<br>pressure force = ${formatScientific(top.forceN)} N<br>planar acceleration = ${formatScientific(acceleration)} m/s²` : 'No non-zero planar force direction.';
    const auditText = `<strong>Mercury arc audit</strong><br>run = ${timeDays.toFixed(3)} / ${durationDays.toFixed(3)} d; terminal JPL comparison = ${mercuryErrorAu.toExponential(3)} AU<br>peak Mercury acceleration = ${formatScientific(experiment.diagnostics.peakMercuryAcceleration)} m/s²<br>peak body-system force imbalance = ${formatScientific(experiment.diagnostics.peakNetForceN)} N<br>medium impulse ledger = ${formatScientific(magnitude(experiment.diagnostics.mediumImpulse))} kg m/s`;
    const overlapText = experiment.diagnostics.apparentOverlaps ? `<span class="warn">${experiment.diagnostics.apparentOverlaps} foreground-cap overlaps were screened with deterministic 2,048-ray spherical quadrature; unblocked source solid angles remain analytic.</span>` : 'No apparent-disc overlaps were detected; every source contribution is an analytic solid angle over this arc.';
    const verdict = completion ? '<span class="fail">Completed: compare the orange model endpoint with the dotted JPL marker. No Keplerian or Newtonian force is included in this run.</span>' : '<span class="warn">Running only the stated planar CMB-pressure occlusion force; JPL is not driving motion.</span>';
    readout.innerHTML = `<strong>${body.name}: planar occlusion dynamics</strong><br>JPL DE441 barycentric J2000 start state; force projection z = 0.<br>Measured CMB pressure = ${formatScientific(CMB_PRESSURE_PA)} Pa at ${CMB_TEMPERATURE_K} K.<br><br>${pairText}<br><br>${auditText}<br><br>${overlapText}<br>${selectedMagnetopauseText(body)}<br><br>${verdict}`;
  }

  function drawLoading(width, height) {
    context.fillStyle = '#e4eff0';
    context.font = '14px ui-monospace, monospace';
    context.fillText(loadFailure || 'Loading JPL DE441 state vectors...', 22, height / 2);
  }

  function render(now) {
    requestAnimationFrame(render);
    const elapsed = Math.min(0.05, (now - previous) / 1000 || 0);
    previous = now;
    const { width, height } = resize();
    context.clearRect(0, 0, width, height);
    if (!experiment) {
      drawLoading(width, height);
      return;
    }
    if (state.running) {
      state.seconds = Math.min(experiment.durationSeconds, state.seconds + elapsed * state.daysPerSecond * 86400);
      if (state.seconds >= experiment.durationSeconds) {
        state.running = false;
        if (pauseButton) {
          pauseButton.textContent = 'run';
          pauseButton.setAttribute('aria-pressed', 'true');
        }
      }
    }
    const items = systemAt(state.seconds);
    const positions = items.map((item) => item.positionM);
    const forceState = planarForces(positions, experiment.bodies);
    const scaleFactor = Math.min(width, height) * 0.44 / RUN.displayExtentAu * state.zoom;
    experiment.bodies.forEach((body, index) => drawTrajectory(index, body, width, height));
    items.forEach((item) => drawField(item, width, height));
    drawMagnetopauses(items, width, height);
    const drawable = items.map((item) => ({ ...item, screen: project(item.position, width, height) })).sort((left, right) => left.screen.depth - right.screen.depth);
    const selectedItem = drawable.find((item) => item.body.name === state.selectedName) || drawable[0];
    drawable.forEach((item) => drawBody(item, scaleFactor));
    drawSelectedForce(selectedItem, forceState, width, height);
    drawReferenceMarker(width, height);
    canvas._items = drawable;
    updateReadout(selectedItem, forceState);
  }

  function addButton(label, action, pressed = false) {
    const button = document.createElement('button');
    button.type = 'button';
    button.textContent = label;
    button.setAttribute('aria-pressed', String(pressed));
    button.addEventListener('click', () => action(button));
    controls.appendChild(button);
    return button;
  }

  function buildControls() {
    pauseButton = addButton('run', (button) => {
      if (!experiment) return;
      if (state.seconds >= experiment.durationSeconds) state.seconds = 0;
      state.running = !state.running;
      button.textContent = state.running ? 'pause' : 'run';
      button.setAttribute('aria-pressed', String(!state.running));
    }, true);
    addButton('restart', () => { state.seconds = 0; state.running = true; pauseButton.textContent = 'pause'; pauseButton.setAttribute('aria-pressed', 'false'); });
    addButton('-', () => { state.zoom = Math.max(0.18, state.zoom / 1.45); });
    addButton('+', () => { state.zoom = Math.min(2500, state.zoom * 1.45); });
    addButton('fields', (button) => { state.fields = !state.fields; button.setAttribute('aria-pressed', String(state.fields)); }, true);
    addButton('force vector', (button) => { state.forceArrows = !state.forceArrows; button.setAttribute('aria-pressed', String(state.forceArrows)); }, true);
    addButton('magnetopauses', (button) => { state.magnetopauses = !state.magnetopauses; button.setAttribute('aria-pressed', String(state.magnetopauses)); }, true);
    addButton('JPL end marker', (button) => { state.referenceMarker = !state.referenceMarker; button.setAttribute('aria-pressed', String(state.referenceMarker)); }, true);
    addButton('labels', (button) => { state.labels = !state.labels; button.setAttribute('aria-pressed', String(state.labels)); }, true);
    addButton('markers', (button) => { state.markers = !state.markers; button.setAttribute('aria-pressed', String(state.markers)); }, true);
    const speedLabel = document.createElement('label');
    const speed = document.createElement('input');
    const output = document.createElement('output');
    speed.type = 'range'; speed.min = '0.25'; speed.max = '30'; speed.step = '0.25'; speed.value = String(state.daysPerSecond); speed.setAttribute('aria-label', 'Simulation days per second');
    output.textContent = `${state.daysPerSecond} d/s`;
    speed.addEventListener('input', () => { state.daysPerSecond = Number(speed.value); output.textContent = `${state.daysPerSecond} d/s`; });
    speedLabel.append('speed', speed, output);
    controls.appendChild(speedLabel);
  }

  function canvasPoint(event) {
    const bounds = canvas.getBoundingClientRect();
    return { x: event.clientX - bounds.left, y: event.clientY - bounds.top };
  }

  canvas.addEventListener('pointerdown', (event) => {
    dragging = true;
    dragged = false;
    lastPointer = canvasPoint(event);
    canvas.setPointerCapture?.(event.pointerId);
  });
  canvas.addEventListener('pointermove', (event) => {
    if (!dragging) return;
    const point = canvasPoint(event);
    const deltaX = point.x - lastPointer.x;
    const deltaY = point.y - lastPointer.y;
    if (Math.hypot(deltaX, deltaY) > 2) dragged = true;
    state.yaw += deltaX * 0.008;
    state.pitch = clamp(state.pitch + deltaY * 0.008, -1.45, 1.45);
    lastPointer = point;
  });
  canvas.addEventListener('pointerup', (event) => {
    if (!dragged && canvas._items) {
      const point = canvasPoint(event);
      const candidate = canvas._items.reduce((closest, item) => {
        const distance = Math.hypot(point.x - item.screen.x, point.y - item.screen.y);
        return distance < closest.distance ? { item, distance } : closest;
      }, { item: null, distance: 14 });
      if (candidate.item) state.selectedName = candidate.item.body.name;
    }
    dragging = false;
  });
  canvas.addEventListener('pointercancel', () => { dragging = false; });
  canvas.addEventListener('wheel', (event) => { event.preventDefault(); state.zoom = clamp(state.zoom * Math.exp(-event.deltaY * 0.0015), 0.18, 2500); }, { passive: false });

  async function loadExperiment() {
    try {
      const response = await fetch(DATASET_URL, { cache: 'no-store' });
      if (!response.ok) throw new Error(`Dataset request returned ${response.status}`);
      const dataset = await response.json();
      if (dataset.reference_frame !== 'Ecliptic of J2000.0' || dataset.ephemeris.indexOf('DE441') === -1) throw new Error('Dataset frame or ephemeris provenance does not match the run contract');
      experiment = simulate(dataset);
      state.running = true;
      pauseButton.textContent = 'pause';
      pauseButton.setAttribute('aria-pressed', 'false');
      console.info('Planar CMB solid-angle occlusion run ready', { pressurePa: CMB_PRESSURE_PA, terminalErrorM: experiment.diagnostics.mercuryTerminalErrorM });
    } catch (error) {
      loadFailure = `Run unavailable: ${error.message}`;
      readout.innerHTML = `<strong class="fail">${loadFailure}</strong><br>Serve the repository root so the JPL dataset path is available.`;
      console.error(error);
    }
  }

  buildControls();
  loadExperiment();
  requestAnimationFrame(render);
})();
