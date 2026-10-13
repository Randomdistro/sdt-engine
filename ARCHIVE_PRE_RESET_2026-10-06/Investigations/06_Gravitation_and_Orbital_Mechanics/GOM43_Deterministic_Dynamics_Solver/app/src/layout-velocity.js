const C = 299792458;
const C2 = C ** 2;

const KOPPA_BY_BARYON = new Map([
  ["805077908211484772344991472376387066905923727158567", 0.001],
  ["1610155816422969544689982944752774133811847454317134", 0.002],
  ["1610155816422969544689982944752774133811847454317", 0.000002],
  ["805077908211484772344991472376", 1e-24],
  ["805077908211484772344991472376387066", 1e-18],
]);

const add = (a, b) => a.map((value, index) => value + b[index]);
const subtract = (a, b) => a.map((value, index) => value - b[index]);
const scale = (vector, factor) => vector.map((value) => value * factor);
const magnitude = (vector) => Math.hypot(...vector);
const cross = (a, b) => [
  a[1] * b[2] - a[2] * b[1],
  a[2] * b[0] - a[0] * b[2],
  a[0] * b[1] - a[1] * b[0],
];

function normalize(vector) {
  const length = magnitude(vector);
  if (!Number.isFinite(length) || length === 0) return [0, 0, 0];
  return scale(vector, 1 / length);
}

export function koppaFromBody(body) {
  if (Number.isFinite(body?.koppa_m) && body.koppa_m > 0) return body.koppa_m;
  const fromLedger = KOPPA_BY_BARYON.get(body?.baryon_count);
  if (fromLedger) return fromLedger;
  if (typeof body?.baryon_count === "string" && /^[1-9][0-9]*$/.test(body.baryon_count)) {
    return Number(body.baryon_count) / 8.050779082114847e32;
  }
  return 1e-18;
}

export function bodyWeight(body) {
  return koppaFromBody(body);
}

export function computeBarycentre(bodies) {
  let total = 0;
  let weighted = [0, 0, 0];
  for (const body of bodies) {
    const weight = bodyWeight(body);
    total += weight;
    weighted = add(weighted, scale(body.position_m, weight));
  }
  return total > 0 ? scale(weighted, 1 / total) : [0, 0, 0];
}

function tangentDirection(relativePosition, orbitNormal, previousVelocity) {
  const tangent = cross(orbitNormal, relativePosition);
  const length = magnitude(tangent);
  if (!Number.isFinite(length) || length === 0) return [0, 0, 0];
  const unit = scale(tangent, 1 / length);
  if (previousVelocity && magnitude(previousVelocity) > 0) {
    const sign = previousVelocity.reduce((sum, value, index) => sum + value * unit[index], 0) >= 0 ? 1 : -1;
    return scale(unit, sign);
  }
  return unit;
}

export function computeCircularVelocities(bodies, options = {}) {
  if (!Array.isArray(bodies) || bodies.length === 0) return [];
  const koppas = bodies.map(koppaFromBody);
  const totalKoppa = koppas.reduce((sum, value) => sum + value, 0);
  const com = computeBarycentre(bodies);
  const orbitNormal = normalize(options.orbitNormal ?? [0, 0, 1]);

  if (bodies.length === 2) {
    const separation = magnitude(subtract(bodies[0].position_m, bodies[1].position_m));
    if (separation <= 0) return bodies.map(() => [0, 0, 0]);
    const omega = Math.sqrt(C2 * totalKoppa / (separation ** 3));
    return bodies.map((body, index) => {
      const relative = subtract(body.position_m, com);
      const radius = magnitude(relative);
      if (radius === 0) return [0, 0, 0];
      const direction = tangentDirection(relative, orbitNormal, body.velocity_m_s);
      return scale(direction, omega * radius);
    });
  }

  return bodies.map((body) => {
    const relative = subtract(body.position_m, com);
    const radius = magnitude(relative);
    if (radius === 0) return [0, 0, 0];
    const omega = Math.sqrt(C2 * totalKoppa / (radius ** 3));
    const direction = tangentDirection(relative, orbitNormal, body.velocity_m_s);
    return scale(direction, omega * radius);
  });
}

export function applyLayoutVelocities(bodies, options = {}) {
  const velocities = computeCircularVelocities(bodies, options);
  bodies.forEach((body, index) => {
    body.velocity_m_s = [...velocities[index]];
  });
  return velocities;
}

export function applyLayoutVelocitiesToCase(caseDefinition, options = {}) {
  if (!Array.isArray(caseDefinition?.bodies) || caseDefinition.bodies.length === 0) return caseDefinition;
  applyLayoutVelocities(caseDefinition.bodies, options);
  return caseDefinition;
}

export function circularPairCheck(separation, primaryKoppa, secondaryKoppa) {
  const total = primaryKoppa + secondaryKoppa;
  const omega = Math.sqrt(C2 * total / (separation ** 3));
  const rA = (secondaryKoppa / total) * separation;
  const rB = (primaryKoppa / total) * separation;
  return {
    omega,
    rA,
    rB,
    vA: rA * omega,
    vB: rB * omega,
  };
}
