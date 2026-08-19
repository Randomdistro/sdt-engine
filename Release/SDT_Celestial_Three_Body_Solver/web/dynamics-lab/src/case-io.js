const CASE_VERSIONS = new Set(["1.0.0", "3.0.0"]);
const ID_PATTERN = /^[A-Za-z0-9][A-Za-z0-9._-]*$/;
const PROBLEM_CLASSES = new Set(["point_nbody", "articulated_rigid", "sdt_occlusion_nbody"]);
const GATE_METRICS = new Set([
  "relative_energy_drift",
  "momentum_drift",
  "angular_momentum_drift",
  "max_position_constraint_m",
  "max_velocity_constraint_m_s",
  "max_quaternion_norm_error",
]);

function assert(condition, message, errors) {
  if (!condition) errors.push(message);
}

function finiteNumber(value) {
  return typeof value === "number" && Number.isFinite(value);
}

function positive(value) {
  return finiteNumber(value) && value > 0;
}

function vec(value, size) {
  return Array.isArray(value) && value.length === size && value.every(finiteNumber);
}

function uniqueIds(items = []) {
  return new Set(items.map(({ id }) => id)).size === items.length;
}

export function validateCase(value) {
  const errors = [];
  assert(value && typeof value === "object" && !Array.isArray(value), "Case must be a JSON object.", errors);
  if (errors.length) return { valid: false, errors };
  const occlusionNbody = value.contract_version === "3.0.0";
  assert(CASE_VERSIONS.has(value.contract_version), "contract_version must be 1.0.0 or 3.0.0.", errors);
  assert(typeof value.case_id === "string" && ID_PATTERN.test(value.case_id), "case_id must use letters, numbers, dot, underscore or hyphen.", errors);
  assert(PROBLEM_CLASSES.has(value.problem_class), "problem_class must be point_nbody, articulated_rigid or sdt_occlusion_nbody.", errors);
  assert(!occlusionNbody || value.problem_class === "sdt_occlusion_nbody", "Contract 3.0.0 requires sdt_occlusion_nbody.", errors);
  assert(occlusionNbody || value.problem_class !== "sdt_occlusion_nbody", "sdt_occlusion_nbody requires contract 3.0.0.", errors);
  assert(value.frame?.type === "inertial_cartesian" && value.frame?.units === "SI", "frame must be inertial_cartesian in SI units.", errors);
  assert(Array.isArray(value.forces) && value.forces.length > 0, "At least one force provider is required.", errors);
  assert(positive(value.timestep_s), "timestep_s must be finite and greater than zero.", errors);
  assert(positive(value.duration_s), "duration_s must be finite and greater than zero.", errors);
  assert(Number.isInteger(value.record_every_steps) && value.record_every_steps >= 1, "record_every_steps must be a positive integer.", errors);
  const steps = value.duration_s / value.timestep_s;
  assert(Number.isFinite(steps) && Math.abs(steps - Math.round(steps)) <= 1e-9 * Math.max(1, steps), "duration_s / timestep_s must be an integral step count.", errors);
  assert(steps <= (occlusionNbody ? 1e12 : 5e7), `Case exceeds the ${occlusionNbody ? "v3 session" : "UI"} step ceiling.`, errors);
  const tolerances = value.tolerances;
  if (occlusionNbody) {
    assert(tolerances && positive(tolerances.retarded_time_s), "Retarded-time tolerance must be positive.", errors);
    assert(Number.isInteger(tolerances?.max_retarded_iterations) && tolerances.max_retarded_iterations >= 2 && tolerances.max_retarded_iterations <= 128, "Retarded iteration budget must be from 2 to 128.", errors);
  } else {
    assert(tolerances && positive(tolerances.position_m), "Position tolerance must be positive.", errors);
    assert(tolerances && positive(tolerances.velocity_m_s), "Velocity tolerance must be positive.", errors);
    assert(tolerances && positive(tolerances.quaternion_norm), "Quaternion tolerance must be positive.", errors);
    assert(Number.isInteger(tolerances?.max_constraint_iterations) && tolerances.max_constraint_iterations >= 1 && tolerances.max_constraint_iterations <= 256, "Constraint iteration budget must be from 1 to 256.", errors);
  }
  assert(Array.isArray(value.gates), "gates must be an array.", errors);
  for (const [index, gate] of (value.gates ?? []).entries()) {
    assert(typeof gate.id === "string" && gate.id.length > 0, `Gate ${index + 1} requires an ID.`, errors);
    if (occlusionNbody) {
      assert(/^M(?:[0-9]|1[0-2])$/.test(gate.id), `Gate ${gate.id ?? index + 1} is not a registered M0-M12 gate.`, errors);
    } else {
      assert(GATE_METRICS.has(gate.metric), `Gate ${gate.id ?? index + 1} uses an unsupported metric.`, errors);
      assert(gate.relation === "<=" || gate.relation === ">=", `Gate ${gate.id ?? index + 1} relation must be <= or >=.`, errors);
      assert(finiteNumber(gate.limit), `Gate ${gate.id ?? index + 1} limit must be finite.`, errors);
    }
  }

  for (const [index, force] of (value.forces ?? []).entries()) {
    if (force.type === "retarded_seven_circle_occlusion") {
      assert(occlusionNbody, "Seven-circle occlusion requires contract 3.0.0.", errors);
      assert(force.pressure_source === "sdt_law_I_P_conv", "Seven-circle pressure_source must be sdt_law_I_P_conv.", errors);
      assert(force.propagation_speed === "c", "Seven-circle propagation_speed must be c.", errors);
      continue;
    }
    if (force.type === "koppa_pairwise") continue;
    assert(force.type === "uniform_acceleration", `Force ${index + 1} has an unsupported type.`, errors);
    if (force.type === "uniform_acceleration") {
      assert(vec(force.acceleration_m_s2, 3), `Force ${index + 1} acceleration must be a finite 3-vector in m/s².`, errors);
      assert(typeof force.provenance?.description === "string" && force.provenance.description.length > 0, `Force ${index + 1} requires provenance.`, errors);
    }
  }

  if (occlusionNbody) {
    assert(["velocity_verlet", "fixed_rk4"].includes(value.integrator), "Occlusion cases require velocity_verlet or fixed_rk4.", errors);
    assert(Array.isArray(value.bodies) && value.bodies.length >= 2 && value.bodies.length <= 10000, "Occlusion cases require 2 to 10,000 bodies.", errors);
    assert(value.forces?.length === 1 && value.forces[0]?.type === "retarded_seven_circle_occlusion", "Occlusion cases require exactly one seven-circle force.", errors);
    assert(uniqueIds(value.bodies), "Body IDs must be unique.", errors);
    for (const [index, body] of (value.bodies ?? []).entries()) {
      const name = body.id || `#${index + 1}`;
      assert(typeof body.id === "string" && ID_PATTERN.test(body.id), `Body ${index + 1} requires a valid ID.`, errors);
      assert(typeof body.baryon_count === "string" && /^[1-9][0-9]*$/.test(body.baryon_count), `Body ${name} baryon_count must be a positive decimal string.`, errors);
      assert(positive(body.radius_m), `Body ${name} radius_m must be positive.`, errors);
      assert(finiteNumber(body.collision_radius_m) && body.collision_radius_m >= 0, `Body ${name} collision radius must be non-negative.`, errors);
      assert(vec(body.position_m, 3), `Body ${name} position_m must be a finite 3-vector.`, errors);
      assert(vec(body.velocity_m_s, 3), `Body ${name} velocity_m_s must be a finite 3-vector.`, errors);
      assert(Math.hypot(...(body.velocity_m_s ?? [Infinity])) < 299792458, `Body ${name} speed must be below c.`, errors);
    }
    return { valid: errors.length === 0, errors, steps: Math.round(steps) };
  }

  if (value.problem_class === "point_nbody") {
    assert(["velocity_verlet", "fixed_rk4"].includes(value.integrator), "Point cases require velocity_verlet or fixed_rk4.", errors);
    assert(Array.isArray(value.bodies) && value.bodies.length > 0, "Point cases require one or more bodies.", errors);
    assert(value.links === undefined && value.joints === undefined, "Point cases cannot contain links or joints.", errors);
    assert(uniqueIds(value.bodies), "Body IDs must be unique.", errors);
    for (const [index, body] of (value.bodies ?? []).entries()) {
      const name = body.id || `#${index + 1}`;
      assert(typeof body.id === "string" && body.id.length > 0, `Body ${index + 1} requires an ID.`, errors);
      assert(vec(body.position_m, 3), `Body ${name} position_m must be a finite 3-vector.`, errors);
      assert(vec(body.velocity_m_s, 3), `Body ${name} velocity_m_s must be a finite 3-vector.`, errors);
      assert(positive(body.koppa_m), `Body ${name} koppa_m must be positive.`, errors);
      assert(finiteNumber(body.collision_radius_m) && body.collision_radius_m >= 0, `Body ${name} collision radius must be non-negative.`, errors);
    }
  }

  if (value.problem_class === "articulated_rigid") {
    assert(value.integrator === "rattle", "Articulated cases require the rattle integrator.", errors);
    assert(Array.isArray(value.links) && value.links.length > 0, "Articulated cases require links.", errors);
    assert(Array.isArray(value.joints) && value.joints.length > 0, "Articulated cases require joints.", errors);
    assert(value.bodies === undefined, "Articulated cases cannot contain point bodies.", errors);
    assert(uniqueIds(value.links), "Link IDs must be unique.", errors);
    assert(uniqueIds(value.joints), "Joint IDs must be unique.", errors);
    const linkIds = new Set((value.links ?? []).map(({ id }) => id));
    for (const link of value.links ?? []) {
      assert(vec(link.position_m, 3) && vec(link.velocity_m_s, 3), `Link ${link.id} position and velocity must be finite 3-vectors.`, errors);
      assert(vec(link.quaternion_wxyz, 4), `Link ${link.id} quaternion must have four finite components.`, errors);
      assert(vec(link.angular_velocity_rad_s, 3), `Link ${link.id} angular velocity must be a finite 3-vector.`, errors);
      assert(positive(link.inertial_mass_kg) && positive(link.length_m), `Link ${link.id} mass and length must be positive.`, errors);
      assert(vec(link.inertia_diagonal_kg_m2, 3) && link.inertia_diagonal_kg_m2.every((entry) => entry > 0), `Link ${link.id} inertia diagonal must be positive.`, errors);
    }
    for (const joint of value.joints ?? []) {
      assert(joint.parent === null || linkIds.has(joint.parent), `Joint ${joint.id} parent does not identify a link or world.`, errors);
      assert(linkIds.has(joint.child), `Joint ${joint.id} child does not identify a link.`, errors);
      assert(vec(joint.parent_anchor_m, 3) && vec(joint.child_anchor_m, 3), `Joint ${joint.id} anchors must be finite 3-vectors.`, errors);
      assert(vec(joint.axis_world, 3) && Math.hypot(...joint.axis_world) > 0, `Joint ${joint.id} axis must be non-zero.`, errors);
    }
  }
  return { valid: errors.length === 0, errors, steps: Math.round(steps) };
}

export function parseCaseJson(source) {
  let value;
  try {
    value = JSON.parse(source);
  } catch (error) {
    throw new Error(`Malformed JSON: ${error.message}`);
  }
  const validation = validateCase(value);
  if (!validation.valid) throw new Error(validation.errors.join("\n"));
  return value;
}

function encodeBytes(text) {
  const bytes = new TextEncoder().encode(text);
  let binary = "";
  for (const byte of bytes) binary += String.fromCharCode(byte);
  const encoded = typeof btoa === "function"
    ? btoa(binary)
    : Buffer.from(bytes).toString("base64");
  return encoded.replaceAll("+", "-").replaceAll("/", "_").replace(/=+$/, "");
}

function decodeBytes(encoded) {
  const base64 = encoded.replaceAll("-", "+").replaceAll("_", "/")
    + "=".repeat((4 - (encoded.length % 4)) % 4);
  const binary = typeof atob === "function"
    ? atob(base64)
    : Buffer.from(base64, "base64").toString("binary");
  return new TextDecoder().decode(Uint8Array.from(binary, (character) => character.charCodeAt(0)));
}

export function encodeSharePayload(caseDefinition) {
  const validation = validateCase(caseDefinition);
  if (!validation.valid) throw new Error(validation.errors.join("\n"));
  return encodeBytes(JSON.stringify(caseDefinition));
}

export function decodeSharePayload(payload) {
  if (!/^[A-Za-z0-9_-]+$/.test(payload)) throw new Error("Share payload contains invalid characters.");
  return parseCaseJson(decodeBytes(payload));
}

export function caseFromLocationHash(hash) {
  const parameters = new URLSearchParams(hash.replace(/^#/, ""));
  const payload = parameters.get("case");
  return payload ? decodeSharePayload(payload) : null;
}

export function resultToCsv(result) {
  const rows = [[
    "step", "time_s", "id", "position_x_m", "position_y_m", "position_z_m",
    "velocity_x_m_s", "velocity_y_m_s", "velocity_z_m_s", "quaternion_w",
    "quaternion_x", "quaternion_y", "quaternion_z", "angular_velocity_x_rad_s",
    "angular_velocity_y_rad_s", "angular_velocity_z_rad_s",
  ]];
  for (const frame of result.trajectory ?? []) {
    for (const state of frame.states ?? []) {
      rows.push([
        frame.step, frame.time_s, state.id, ...state.position_m, ...state.velocity_m_s,
        ...(state.quaternion_wxyz ?? ["", "", "", ""]),
        ...(state.angular_velocity_rad_s ?? ["", "", ""]),
      ]);
    }
  }
  return rows.map((row) => row.map((value) => {
    const text = String(value);
    return /[",\n]/.test(text) ? `"${text.replaceAll('"', '""')}"` : text;
  }).join(",")).join("\n");
}

export function downloadText(filename, text, type = "application/json") {
  const anchor = document.createElement("a");
  anchor.href = URL.createObjectURL(new Blob([text], { type }));
  anchor.download = filename;
  anchor.click();
  setTimeout(() => URL.revokeObjectURL(anchor.href), 0);
}
