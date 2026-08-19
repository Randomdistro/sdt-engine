const C2 = 299792458 ** 2;

const add = (a, b) => a.map((value, index) => value + b[index]);
const subtract = (a, b) => a.map((value, index) => value - b[index]);
const scale = (vector, factor) => vector.map((value) => value * factor);
const magnitude = (vector) => Math.hypot(...vector);
const cross = (a, b) => [
  a[1] * b[2] - a[2] * b[1],
  a[2] * b[0] - a[0] * b[2],
  a[0] * b[1] - a[1] * b[0],
];

function rotateByQuaternion(vector, [w, x, y, z]) {
  const qv = [x, y, z];
  const uv = cross(qv, vector);
  const uuv = cross(qv, uv);
  return add(vector, add(scale(uv, 2 * w), scale(uuv, 2)));
}

function stateMap(frame) {
  return new Map(frame.states.map((state) => [state.id, state]));
}

function bodyWeight(definition) {
  if (definition?.baryon_count) return Number(definition.baryon_count);
  return definition?.koppa_m ?? definition?.inertial_mass_kg ?? 1;
}

export function barycentre(frame, caseDefinition) {
  const definitions = caseDefinition.bodies ?? caseDefinition.links ?? [];
  const byId = new Map(definitions.map((entry) => [entry.id, entry]));
  let total = 0;
  let weighted = [0, 0, 0];
  for (const state of frame.states) {
    const definition = byId.get(state.id);
    const weight = bodyWeight(definition);
    total += weight;
    weighted = add(weighted, scale(state.position_m, weight));
  }
  return total > 0 ? scale(weighted, 1 / total) : [0, 0, 0];
}

function pointEnergy(frame, caseDefinition) {
  const byId = new Map(caseDefinition.bodies.map((body) => [body.id, body]));
  let energy = 0;
  for (const state of frame.states) {
    const definition = byId.get(state.id);
    const weight = bodyWeight(definition);
    energy += 0.5 * weight * magnitude(state.velocity_m_s) ** 2;
  }
  if (caseDefinition.problem_class === "sdt_occlusion_nbody") return energy;
  for (let left = 0; left < frame.states.length; left += 1) {
    for (let right = left + 1; right < frame.states.length; right += 1) {
      const a = frame.states[left];
      const b = frame.states[right];
      const distance = magnitude(subtract(a.position_m, b.position_m));
      energy -= C2 * (byId.get(a.id)?.koppa_m ?? 0) * (byId.get(b.id)?.koppa_m ?? 0) / distance;
    }
  }
  return energy;
}

function rigidEnergy(frame, caseDefinition) {
  const byId = new Map(caseDefinition.links.map((link) => [link.id, link]));
  const acceleration = caseDefinition.forces.find(({ type }) => type === "uniform_acceleration")?.acceleration_m_s2 ?? [0, 0, 0];
  let energy = 0;
  for (const state of frame.states) {
    const link = byId.get(state.id);
    const mass = link?.inertial_mass_kg ?? 1;
    energy += 0.5 * mass * magnitude(state.velocity_m_s) ** 2;
    energy -= mass * acceleration.reduce((sum, value, index) => sum + value * state.position_m[index], 0);
    const omega = state.angular_velocity_rad_s ?? [0, 0, 0];
    energy += 0.5 * omega.reduce((sum, value, index) => sum + value * value * (link?.inertia_diagonal_kg_m2?.[index] ?? 0), 0);
  }
  return energy;
}

function weightedVector(frame, definitions, property) {
  const byId = new Map(definitions.map((entry) => [entry.id, entry]));
  return frame.states.reduce((sum, state) => {
    const definition = byId.get(state.id);
    const weight = bodyWeight(definition);
    const value = property === "momentum"
      ? state.velocity_m_s
      : cross(state.position_m, state.velocity_m_s);
    return add(sum, scale(value, weight));
  }, [0, 0, 0]);
}

function maximumConstraintResidual(frame, caseDefinition) {
  if (!caseDefinition.joints) return 0;
  const states = stateMap(frame);
  let maximum = 0;
  for (const joint of caseDefinition.joints) {
    const child = states.get(joint.child);
    const parent = joint.parent === null ? null : states.get(joint.parent);
    if (!child || (joint.parent !== null && !parent)) continue;
    const childAnchor = add(child.position_m, rotateByQuaternion(joint.child_anchor_m, child.quaternion_wxyz));
    const parentAnchor = parent
      ? add(parent.position_m, rotateByQuaternion(joint.parent_anchor_m, parent.quaternion_wxyz))
      : joint.parent_anchor_m;
    maximum = Math.max(maximum, magnitude(subtract(childAnchor, parentAnchor)));
  }
  return maximum;
}

export function buildDiagnosticSeries(result) {
  const frames = result?.trajectory ?? [];
  const caseDefinition = result?.normalized_case ?? {};
  const definitions = caseDefinition.bodies ?? caseDefinition.links ?? [];
  if (!frames.length) return {};
  const energies = frames.map((frame) => ["point_nbody", "sdt_occlusion_nbody"].includes(caseDefinition.problem_class)
    ? pointEnergy(frame, caseDefinition)
    : rigidEnergy(frame, caseDefinition));
  const initialEnergy = Math.abs(energies[0]) || 1;
  return {
    separation: {
      name: "First-pair separation (m)",
      values: frames.map((frame) => frame.states.length > 1
        ? magnitude(subtract(frame.states[0].position_m, frame.states[1].position_m))
        : 0),
    },
    energy: {
      name: "Relative energy change",
      values: energies.map((value) => (value - energies[0]) / initialEnergy),
    },
    momentum: {
      name: "Koppa/mass-weighted momentum magnitude",
      values: frames.map((frame) => magnitude(weightedVector(frame, definitions, "momentum"))),
    },
    angularMomentum: {
      name: "Koppa/mass-weighted angular momentum magnitude",
      values: frames.map((frame) => magnitude(weightedVector(frame, definitions, "angularMomentum"))),
    },
    jointAngle: {
      name: "First-link joint angle (rad)",
      values: frames.map((frame) => {
        const quaternion = frame.states[0]?.quaternion_wxyz;
        return quaternion ? 2 * Math.atan2(quaternion[3], quaternion[0]) : 0;
      }),
    },
    angularRate: {
      name: "First-link angular rate (rad/s)",
      values: frames.map((frame) => magnitude(frame.states[0]?.angular_velocity_rad_s ?? [0, 0, 0])),
    },
    constraint: {
      name: "Maximum reconstructed joint residual (m)",
      values: frames.map((frame) => maximumConstraintResidual(frame, caseDefinition)),
    },
  };
}

export function finiteDifferenceAccelerations(frames, frameIndex) {
  if (frames.length < 2) return new Map();
  const beforeIndex = Math.max(0, frameIndex - 1);
  const afterIndex = Math.min(frames.length - 1, frameIndex + 1);
  const before = stateMap(frames[beforeIndex]);
  const after = stateMap(frames[afterIndex]);
  const elapsed = frames[afterIndex].time_s - frames[beforeIndex].time_s;
  const values = new Map();
  if (elapsed <= 0) return values;
  for (const [id, state] of after) {
    const earlier = before.get(id);
    if (earlier) values.set(id, scale(subtract(state.velocity_m_s, earlier.velocity_m_s), 1 / elapsed));
  }
  return values;
}

export function drawDiagnosticChart(canvas, series, frameIndex) {
  const context = canvas.getContext("2d");
  const dpr = window.devicePixelRatio || 1;
  const width = Math.max(1, canvas.clientWidth);
  const height = Math.max(1, canvas.clientHeight);
  canvas.width = Math.round(width * dpr);
  canvas.height = Math.round(height * dpr);
  context.scale(dpr, dpr);
  context.clearRect(0, 0, width, height);
  context.fillStyle = "#090f17";
  context.fillRect(0, 0, width, height);
  if (!series?.values?.length) return;
  const finite = series.values.filter(Number.isFinite);
  let minimum = Math.min(...finite);
  let maximum = Math.max(...finite);
  if (minimum === maximum) { minimum -= 1; maximum += 1; }
  const pad = 18;
  const x = (index) => pad + (index / Math.max(1, series.values.length - 1)) * (width - 2 * pad);
  const y = (value) => height - pad - ((value - minimum) / (maximum - minimum)) * (height - 2 * pad);
  context.strokeStyle = "#1c2c3c";
  context.lineWidth = 1;
  for (let index = 0; index <= 4; index += 1) {
    const gridY = pad + (index / 4) * (height - 2 * pad);
    context.beginPath(); context.moveTo(pad, gridY); context.lineTo(width - pad, gridY); context.stroke();
  }
  context.strokeStyle = "#54d3c2";
  context.lineWidth = 1.5;
  context.beginPath();
  series.values.forEach((value, index) => {
    if (!Number.isFinite(value)) return;
    if (index === 0) context.moveTo(x(index), y(value));
    else context.lineTo(x(index), y(value));
  });
  context.stroke();
  const selected = Math.min(frameIndex, series.values.length - 1);
  context.strokeStyle = "#f4be58";
  context.beginPath(); context.moveTo(x(selected), pad); context.lineTo(x(selected), height - pad); context.stroke();
  context.fillStyle = "#f4be58";
  context.beginPath(); context.arc(x(selected), y(series.values[selected]), 3, 0, Math.PI * 2); context.fill();
}

export function formatMetric(value) {
  if (!Number.isFinite(value)) return "—";
  if (value === 0) return "0";
  const absolute = Math.abs(value);
  return absolute >= 1e4 || absolute < 1e-3 ? value.toExponential(5) : value.toPrecision(6);
}
