const FRAME = { type: "inertial_cartesian", units: "SI" };
const TOLERANCES = {
  position_m: 1e-10,
  velocity_m_s: 1e-10,
  quaternion_norm: 1e-12,
  max_constraint_iterations: 96,
};

function pointCase(caseId, bodies, timestep_s, duration_s, gates = []) {
  return {
    contract_version: "3.0.0",
    case_id: caseId,
    problem_class: "sdt_occlusion_nbody",
    frame: { ...FRAME },
    forces: [{
      type: "retarded_seven_circle_occlusion",
      pressure_source: "sdt_law_I_P_conv",
      propagation_speed: "c",
    }],
    bodies,
    integrator: "velocity_verlet",
    timestep_s,
    duration_s,
    record_every_steps: Math.max(1, Math.round(duration_s / timestep_s / 500)),
    tolerances: { retarded_time_s: 1e-12, max_retarded_iterations: 32 },
    gates: ["M0", "M1", "M3", "M6", "M8", "M9", "M12"].map((id) => ({ id })),
  };
}

const BARYONS_BY_KOPPA = new Map([
  ["0.001", "805077908211484772344991472376387066905923727158567"],
  ["0.002", "1610155816422969544689982944752774133811847454317134"],
  ["0.000002", "1610155816422969544689982944752774133811847454317"],
  ["1e-24", "805077908211484772344991472376"],
  ["1e-18", "805077908211484772344991472376387066"],
]);

function body(id, position_m, velocity_m_s, koppa_m, collision_radius_m = 0) {
  const baryon_count = BARYONS_BY_KOPPA.get(String(koppa_m));
  if (!baryon_count) throw new Error(`No laws-derived preset baryon ledger for koppa ${koppa_m}.`);
  const radius_m = collision_radius_m > 0 ? collision_radius_m : 1e5;
  return {
    id,
    position_m,
    velocity_m_s,
    baryon_count,
    radius_m,
    collision_radius_m: radius_m,
    provenance: {
      classification: "CONDITIONAL",
      description: "Synthetic geometry; baryon count calculated from the declared legacy koppa through laws.hpp.",
    },
  };
}

function pendulumCase(caseId, count) {
  const length = 1 / count;
  const angle = 0.34;
  const links = [];
  const joints = [];
  let pivot = [0, 0, 0];
  for (let index = 0; index < count; index += 1) {
    const id = `link-${String(index + 1).padStart(2, "0")}`;
    const centre = [
      pivot[0] + 0.5 * length * Math.sin(angle),
      pivot[1] - 0.5 * length * Math.cos(angle),
      0,
    ];
    links.push({
      id,
      position_m: centre,
      quaternion_wxyz: [Math.cos(angle / 2), 0, 0, Math.sin(angle / 2)],
      velocity_m_s: [0, 0, 0],
      angular_velocity_rad_s: [0, 0, 0],
      inertial_mass_kg: 1 / count,
      inertia_diagonal_kg_m2: [
        (length * length) / (12 * count),
        1e-8,
        (length * length) / (12 * count),
      ],
      length_m: length,
    });
    joints.push({
      id: `joint-${String(index + 1).padStart(2, "0")}`,
      parent: index === 0 ? null : links[index - 1].id,
      child: id,
      parent_anchor_m: index === 0 ? [0, 0, 0] : [0, -length / 2, 0],
      child_anchor_m: [0, length / 2, 0],
      axis_world: [0, 0, 1],
    });
    pivot = [
      pivot[0] + length * Math.sin(angle),
      pivot[1] - length * Math.cos(angle),
      0,
    ];
  }
  return {
    contract_version: "1.0.0",
    case_id: caseId,
    problem_class: "articulated_rigid",
    frame: { ...FRAME },
    forces: [{
      type: "uniform_acceleration",
      acceleration_m_s2: [0, -9.80665, 0],
      provenance: {
        classification: "MEASURED-INPUT",
        description: "Declared standard laboratory acceleration for a conditional local-uniform case.",
      },
    }],
    links,
    joints,
    integrator: "rattle",
    timestep_s: 0.0005,
    duration_s: count > 2 ? 3 : 6,
    record_every_steps: count > 2 ? 15 : 20,
    tolerances: { ...TOLERANCES },
    gates: [
      { id: "position", metric: "max_position_constraint_m", relation: "<=", limit: 2e-8 },
      { id: "velocity", metric: "max_velocity_constraint_m_s", relation: "<=", limit: 2e-8 },
      { id: "quaternion", metric: "max_quaternion_norm_error", relation: "<=", limit: 1e-10 },
    ],
  };
}

const presets = {
  "circular-pair": () => pointCase(
    "lab-circular-pair",
    [
      body("A", [-666666666.6666666, 0, 0], [0, -346.17051265463914, 0], 0.001),
      body("B", [333333333.3333333, 0, 0], [0, 173.08525632731957, 0], 0.002),
    ],
    10,
    20000,
    [{ id: "energy", metric: "relative_energy_drift", relation: "<=", limit: 1e-6 }],
  ),
  "stable-triangle": () => {
    const radius = 1e9;
    const koppa = 1e-3;
    const speed = Math.sqrt(299792458 ** 2 * koppa / (Math.sqrt(3) * radius));
    return pointCase(
      "lab-stable-lagrange-triangle",
      [0, 1, 2].map((index) => {
        const theta = (2 * Math.PI * index) / 3;
        return body(
          String.fromCharCode(65 + index),
          [radius * Math.cos(theta), radius * Math.sin(theta), 0],
          [-speed * Math.sin(theta), speed * Math.cos(theta), 0],
          koppa,
        );
      }),
      20,
      40000,
      [{ id: "energy", metric: "relative_energy_drift", relation: "<=", limit: 5e-6 }],
    );
  },
  "figure-eight": () => {
    const lengthScale = 1e9;
    const koppa = 1e-3;
    const velocityScale = Math.sqrt(299792458 ** 2 * koppa / lengthScale);
    return pointCase(
      "lab-figure-eight",
      [
        body("A", [-0.97000436 * lengthScale, 0.24308753 * lengthScale, 0], [0.466203685 * velocityScale, 0.43236573 * velocityScale, 0], koppa),
        body("B", [0.97000436 * lengthScale, -0.24308753 * lengthScale, 0], [0.466203685 * velocityScale, 0.43236573 * velocityScale, 0], koppa),
        body("C", [0, 0, 0], [-0.93240737 * velocityScale, -0.86473146 * velocityScale, 0], koppa),
      ],
      1000,
      21000000,
      [{ id: "energy", metric: "relative_energy_drift", relation: "<=", limit: 1e-5 }],
    );
  },
  "restricted-lagrange": () => {
    const separation = 1e9;
    const primaryKoppa = 0.002;
    const secondaryKoppa = 0.000002;
    const omega = Math.sqrt(299792458 ** 2 * (primaryKoppa + secondaryKoppa) / separation ** 3);
    const mu = secondaryKoppa / (primaryKoppa + secondaryKoppa);
    const points = [
      ["L1", 0.84, 0], ["L2", 1.16, 0], ["L3", -1.0, 0],
      ["L4", 0.5 - mu, Math.sqrt(3) / 2], ["L5", 0.5 - mu, -Math.sqrt(3) / 2],
    ];
    const bodies = [
      body("A", [-mu * separation, 0, 0], [0, -mu * separation * omega, 0], primaryKoppa),
      body("B", [(1 - mu) * separation, 0, 0], [0, (1 - mu) * separation * omega, 0], secondaryKoppa),
      ...points.map(([id, x, y]) => body(
        id,
        [x * separation, y * separation, 0],
        [-y * separation * omega, x * separation * omega, 0],
        1e-24,
      )),
    ];
    return pointCase("lab-restricted-lagrange-points", bodies, 20, 20000);
  },
  "single-pendulum": () => pendulumCase("lab-single-pendulum", 1),
  "double-pendulum": () => pendulumCase("lab-double-pendulum", 2),
  "sectioned-pendulum": () => pendulumCase("lab-sectioned-pendulum", 5),
};

export const presetNames = Object.freeze(Object.keys(presets));

export function createPreset(name) {
  const factory = presets[name];
  if (!factory) throw new Error(`Unknown dynamics preset: ${name}`);
  return structuredClone(factory());
}

export function createMinimalCase() {
  return pointCase(
    "untitled-point-case",
    [
      body("A", [-1, 0, 0], [0, -0.1, 0], 1e-18, 0.01),
      body("B", [1, 0, 0], [0, 0.1, 0], 1e-18, 0.01),
    ],
    0.001,
    1,
  );
}

export function createEntity(caseDefinition, kind) {
  if (kind === "body") {
    const index = (caseDefinition.bodies?.length ?? 0) + 1;
    return body(String.fromCharCode(64 + Math.min(index, 26)), [index, 0, 0], [0, 0, 0], 1e-18, 0.01);
  }
  if (kind === "link") {
    const index = (caseDefinition.links?.length ?? 0) + 1;
    return {
      id: `link-${index}`, position_m: [0, -index + 0.5, 0],
      quaternion_wxyz: [1, 0, 0, 0], velocity_m_s: [0, 0, 0],
      angular_velocity_rad_s: [0, 0, 0], inertial_mass_kg: 1,
      inertia_diagonal_kg_m2: [0.0833333333, 1e-6, 0.0833333333], length_m: 1,
    };
  }
  const links = caseDefinition.links ?? [];
  const index = (caseDefinition.joints?.length ?? 0) + 1;
  return {
    id: `joint-${index}`, parent: index === 1 ? null : links[index - 2]?.id ?? null,
    child: links[index - 1]?.id ?? links[0]?.id ?? "",
    parent_anchor_m: [0, -0.5, 0], child_anchor_m: [0, 0.5, 0], axis_world: [0, 0, 1],
  };
}
