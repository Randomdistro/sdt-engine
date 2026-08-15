(() => {
  'use strict';

  const canvas = document.getElementById('scene');
  const ctx = canvas.getContext('2d');
  const readout = document.getElementById('readout');
  const stepCopy = document.getElementById('stepCopy');
  const sceneNote = document.getElementById('sceneNote');
  const playBtn = document.getElementById('playBtn');
  const resetBtn = document.getElementById('resetBtn');
  const elementSelect = document.getElementById('elementSelect');
  const nbodySelect = document.getElementById('nbodySelect');
  const materialMode = document.getElementById('materialMode');
  const speed = document.getElementById('speed');
  const layers = document.getElementById('layers');
  const alignment = document.getElementById('alignment');

  const TAU = Math.PI * 2;
  const colours = {
    proton: '#ef9d62',
    neutron: '#77bfff',
    electron: '#6df0cd',
    wake: '#b59cff',
    mesh: '#617789',
    blue: '#75b8ff',
    copper: '#d79a5a',
    li: '#75b8ff',
    u: '#d79a5a',
    white: '#edf4f5'
  };

  const presets = {
    H1: { symbol: 'H', name: 'Hydrogen-1', Z: 1, A: 1, nd: 0, nt: 0, shells: [1] },
    He4: { symbol: 'He', name: 'Helium-4', Z: 2, A: 4, nd: 0, nt: 0, shells: [2] },
    Li7: { symbol: 'Li', name: 'Lithium-7', Z: 3, A: 7, nd: 0, nt: 1, shells: [2, 1] },
    C12: { symbol: 'C', name: 'Carbon-12', Z: 6, A: 12, nd: 4, nt: 0, shells: [2, 4] },
    Fe56: { symbol: 'Fe', name: 'Iron-56', Z: 26, A: 56, nd: 20, nt: 4, shells: [2, 8, 14, 2] },
    U238: { symbol: 'U', name: 'Uranium-238', Z: 92, A: 238, nd: 36, nt: 54, shells: [2, 8, 18, 32, 21, 9, 2] }
  };

  const copy = {
    rotor: `
      <span class="tag tag--d">DERIVED</span>
      <p>The canonical proton mode is a (2,3) trefoil with W=3. Its toroidal and poloidal speeds close the movement budget. The rendered tube is a topology diagram, not a measured proton-density map.</p>`,
    mesh: `
      <span class="tag tag--d">CONSTITUTIONAL GRAMMAR</span>
      <span class="tag tag--h">LAYER LAYOUT</span>
      <p>For Z≥2, one α core plus n<sub>d</sub> deuterons and n<sub>t</sub> tritons fixes the component count. Complementary trefoil rotation and shared corotation are the working machine model; the displayed shell placement is an explicit visual hypothesis.</p>`,
    gear: `
      <span class="tag tag--d">DERIVED TRACTION</span>
      <span class="tag tag--i">RATIO IDENTITY</span>
      <p>The W=3 rotor demands a traction ratio 12 at its boundary. The nuclear-to-atomic frequency ratio is exact arithmetic on the current seats. A physical transmission must still distinguish itself through re-locking dynamics.</p>`,
    electron: `
      <span class="tag tag--h">ACTIVE HYPOTHESIS</span>
      <span class="tag tag--o">MASS SOLVE OPEN</span>
      <p>The forced-gap view starts with unequal contact paths, then tests whether the lowest persistent reset is π or 2π. The opening, forward hand-off and trailing pinch are rendered separately. The shape is not imposed as evidence that a helix emerges.</p>`,
    atom: `
      <span class="tag tag--i">LEVEL IDENTITIES</span>
      <span class="tag tag--h">PHYSICAL GEARING</span>
      <p>Atomic seats use r<sub>n</sub>=n²a₀ and ω<sub>n</sub>∝n⁻³. The shared phase clock is exact at the level of these identities; mechanical lock and pull-in after perturbation are the discriminating hypothesis.</p>`,
    materials: `
      <span class="tag tag--d">COMPUTED CONTROL</span>
      <p>Equal total baryon count gives the same far monopole. Density changes radius, surface response and the normalized rotational wake. Equal volume instead puts the 35.77× density ratio directly into the total source. Magnetic alignment remains a separate control.</p>`,
    nbody: `
      <span class="tag tag--d">VALIDATED INSTRUMENT</span>
      <span class="tag tag--o">NOT CLOSED FORM</span>
      <p>The A/B/C scene ports the same central acceleration used by GOM42 into a velocity-Verlet browser solver. It integrates initial states without G, M, GM or softening. This is a numerical trajectory solution, not a closed-form solution of the unrestricted three-body problem.</p>`
  };

  const notes = {
    rotor: 'W=3 · (p,q)=(2,3) · drag to inspect the six alternating arcs',
    mesh: 'All nuclear components corotate on one clock; colour shows proton/neutron role. Layer phase offsets are a testable layout hypothesis.',
    gear: 'Nuclear and atomic scales are compressed. The displayed ratio comes from the executable engine dataset.',
    electron: 'π and 2π sectors remain alternatives until a contact-lattice run selects one. The downloaded rod-unfurling account is not current canon.',
    atom: 'Log-compressed scale view. Electron paths are deterministic seat guides, not measured trajectories.',
    materials: 'Measured density inputs: Li 534 kg/m³; U 19,100 kg/m³. Wake brightness and Φ readouts are declared alignment/count controls, not bulk-magnetism predictions.',
    nbody: 'Velocity Verlet · central koppa kernel · no softening. Trail closure and invariant drift are numerical diagnostics.'
  };

  const state = {
    step: 'rotor',
    playing: true,
    time: 0,
    speed: 1,
    layerScale: 1,
    alignment: .65,
    yaw: -.58,
    pitch: .28,
    zoom: 1,
    width: 1,
    height: 1,
    dpr: 1,
    frameDt: 0,
    engine: window.SDT_ENGINE_DATA || null,
    nucleus: null,
    nbody: null,
    last: performance.now()
  };

  const v = (x = 0, y = 0, z = 0) => ({ x, y, z });
  const add = (a, b) => v(a.x + b.x, a.y + b.y, a.z + b.z);
  const sub = (a, b) => v(a.x - b.x, a.y - b.y, a.z - b.z);
  const mul = (a, s) => v(a.x * s, a.y * s, a.z * s);
  const dot = (a, b) => a.x * b.x + a.y * b.y + a.z * b.z;
  const len = a => Math.sqrt(dot(a, a));
  const cross = (a, b) => v(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );

  function rotate(p, yaw = state.yaw, pitch = state.pitch) {
    const cy = Math.cos(yaw), sy = Math.sin(yaw);
    const x1 = cy * p.x + sy * p.z;
    const z1 = -sy * p.x + cy * p.z;
    const cp = Math.cos(pitch), sp = Math.sin(pitch);
    return v(x1, cp * p.y - sp * z1, sp * p.y + cp * z1);
  }

  function rotateZ(p, angle) {
    const c = Math.cos(angle), s = Math.sin(angle);
    return v(c * p.x - s * p.y, s * p.x + c * p.y, p.z);
  }

  function orient(p, ax, ay, az) {
    let q = rotateZ(p, az);
    const cx = Math.cos(ax), sx = Math.sin(ax);
    q = v(q.x, cx * q.y - sx * q.z, sx * q.y + cx * q.z);
    const cy = Math.cos(ay), sy = Math.sin(ay);
    return v(cy * q.x + sy * q.z, q.y, -sy * q.x + cy * q.z);
  }

  function project(p) {
    const q = rotate(p);
    const perspective = Math.max(.28, 1 + q.z / 20);
    const scale = Math.min(state.width, state.height) * .075 * state.zoom / perspective;
    return {
      x: state.width / 2 + q.x * scale,
      y: state.height / 2 - q.y * scale,
      z: q.z,
      scale
    };
  }

  function resize() {
    const box = canvas.getBoundingClientRect();
    state.dpr = Math.min(2, window.devicePixelRatio || 1);
    state.width = Math.max(1, box.width);
    state.height = Math.max(1, box.height);
    canvas.width = Math.round(state.width * state.dpr);
    canvas.height = Math.round(state.height * state.dpr);
    ctx.setTransform(state.dpr, 0, 0, state.dpr, 0, 0);
  }

  const scene = { lines: [], dots: [], labels: [] };
  function clearScene() {
    scene.lines.length = 0;
    scene.dots.length = 0;
    scene.labels.length = 0;
  }
  function addLine(a, b, colour, width = 1, alpha = 1) {
    scene.lines.push({ a, b, colour, width, alpha });
  }
  function addDot(position, radius, colour, alpha = 1, glow = 0) {
    scene.dots.push({ position, radius, colour, alpha, glow });
  }
  function addLabel(position, text, colour = colours.white) {
    scene.labels.push({ position, text, colour });
  }
  function polyline(points, colour, width = 1, alpha = 1, closed = false) {
    for (let i = 1; i < points.length; i++) {
      addLine(points[i - 1], points[i], colour, width, alpha);
    }
    if (closed && points.length > 2) {
      addLine(points[points.length - 1], points[0], colour, width, alpha);
    }
  }

  function trefoilPoint(t) {
    const a = TAU * t;
    return v(
      (2 + Math.cos(3 * a)) * Math.cos(2 * a),
      (2 + Math.cos(3 * a)) * Math.sin(2 * a),
      Math.sin(3 * a)
    );
  }

  function addTrefoil(center, scale, colour, phase, angles, detail = 42, alpha = 1) {
    const points = [];
    for (let i = 0; i <= detail; i++) {
      const p = trefoilPoint((i / detail + phase / TAU) % 1);
      points.push(add(center, orient(mul(p, scale), angles.x, angles.y, angles.z)));
    }
    polyline(points, colour, Math.max(1, scale * 2.4), alpha);
  }

  function wireSphere(center, radius, colour, alpha = .35) {
    for (let band = -2; band <= 2; band++) {
      const latitude = band * Math.PI / 6;
      const ring = [];
      const rr = radius * Math.cos(latitude);
      const z = radius * Math.sin(latitude);
      for (let i = 0; i <= 36; i++) {
        const a = TAU * i / 36;
        ring.push(add(center, v(rr * Math.cos(a), rr * Math.sin(a), z)));
      }
      polyline(ring, colour, 1, alpha);
    }
    for (let band = 0; band < 8; band++) {
      const ring = [];
      const phi = TAU * band / 8;
      for (let i = 0; i <= 24; i++) {
        const a = -Math.PI / 2 + Math.PI * i / 24;
        ring.push(add(center, v(
          radius * Math.cos(a) * Math.cos(phi),
          radius * Math.cos(a) * Math.sin(phi),
          radius * Math.sin(a)
        )));
      }
      polyline(ring, colour, 1, alpha);
    }
  }

  function deterministic(index, salt = 0) {
    const x = Math.sin((index + 1) * 12.9898 + salt * 78.233) * 43758.5453;
    return x - Math.floor(x);
  }

  function makeNucleus(preset) {
    const types = [];
    if (preset.A === 1) {
      types.push('proton');
    } else {
      types.push('proton', 'neutron', 'proton', 'neutron');
      for (let i = 0; i < preset.nd; i++) types.push('proton', 'neutron');
      for (let i = 0; i < preset.nt; i++) types.push('proton', 'neutron', 'neutron');
    }
    while (types.length < preset.A) {
      types.push(types.filter(x => x === 'proton').length < preset.Z ? 'proton' : 'neutron');
    }

    const nodes = [];
    const tetra = [
      v(1, 1, 1), v(-1, -1, 1), v(-1, 1, -1), v(1, -1, -1)
    ];
    const capacities = [4, 12, 20, 32, 48, 64, 80];
    let cursor = 0;
    for (let layer = 0; cursor < types.length; layer++) {
      const count = Math.min(capacities[Math.min(layer, capacities.length - 1)], types.length - cursor);
      for (let j = 0; j < count; j++, cursor++) {
        let position;
        if (layer === 0 && j < 4) {
          position = mul(tetra[j], .46);
        } else {
          const golden = Math.PI * (3 - Math.sqrt(5));
          const y = 1 - 2 * (j + .5) / count;
          const rr = Math.sqrt(Math.max(0, 1 - y * y));
          const theta = golden * j + layer * .47;
          const radius = 1.25 + layer * .78;
          position = v(radius * rr * Math.cos(theta), radius * rr * Math.sin(theta), radius * y);
        }
        nodes.push({
          type: types[cursor],
          layer,
          base: position,
          angles: v(
            deterministic(cursor, 1) * Math.PI,
            deterministic(cursor, 2) * Math.PI,
            deterministic(cursor, 3) * Math.PI
          )
        });
      }
    }

    const bonds = [];
    for (let i = 1; i < nodes.length; i++) {
      let best = 0, bestDistance = Infinity;
      for (let j = 0; j < i; j++) {
        const distance = len(sub(nodes[i].base, nodes[j].base));
        if (distance < bestDistance) {
          best = j;
          bestDistance = distance;
        }
      }
      bonds.push([i, best]);
    }
    return { nodes, bonds };
  }

  function ensureNucleus() {
    const preset = presets[elementSelect.value];
    if (!state.nucleus || state.nucleus.key !== elementSelect.value) {
      state.nucleus = { key: elementSelect.value, ...makeNucleus(preset) };
    }
    return state.nucleus;
  }

  function nucleusPositions(scale = 1, offset = v()) {
    const model = ensureNucleus();
    const phase = state.time * .48;
    return model.nodes.map((node, index) => {
      const layerPhase = node.layer * .18;
      const stretched = v(
        node.base.x * state.layerScale,
        node.base.y * state.layerScale,
        node.base.z * state.layerScale
      );
      return {
        ...node,
        index,
        position: add(offset, mul(rotateZ(stretched, phase + layerPhase), scale))
      };
    });
  }

  function renderNucleus(scale = 1, offset = v(), detailed = true) {
    const model = ensureNucleus();
    const nodes = nucleusPositions(scale, offset);
    const detail = nodes.length > 100 ? 11 : nodes.length > 30 ? 16 : 30;
    for (const [a, b] of model.bonds) {
      if (a < nodes.length && b < nodes.length) {
        addLine(nodes[a].position, nodes[b].position, colours.mesh, 1, .22);
      }
    }
    for (const node of nodes) {
      const colour = colours[node.type];
      if (detailed) {
        const direction = node.type === 'proton' ? 1 : -1;
        addTrefoil(
          node.position,
          .11 * scale,
          colour,
          direction * state.time * 1.2,
          node.angles,
          detail,
          .82
        );
      } else {
        addDot(node.position, 2.5 + scale, colour, .85, 6);
      }
    }
    return nodes;
  }

  function buildRotor() {
    addTrefoil(v(), 1.18, colours.proton, state.time * .5, v(.45, -.2, .1), 96, 1);
    wireSphere(v(), 3.7, colours.wake, .12);
    for (let i = 0; i < 12; i++) {
      const a = TAU * i / 12 + state.time * .3;
      const start = v(2.6 * Math.cos(a), 2.6 * Math.sin(a), .7 * Math.sin(3 * a));
      const end = mul(start, 1.55);
      addLine(start, end, colours.wake, 1.2, .24 * state.alignment);
    }
    addLabel(v(0, 3.3, 0), 'W=3 · (2,3) trefoil');
  }

  function buildMesh() {
    const preset = presets[elementSelect.value];
    renderNucleus(preset.A > 80 ? .78 : preset.A > 20 ? .92 : 1.15);
    addLabel(v(0, 4.5, 0), `${preset.name} · ${preset.A} trefoil forms`);
  }

  function buildGear() {
    addTrefoil(v(-3.5, 0, 0), .72, colours.proton, state.time, v(.5, .2, .2), 64, 1);
    wireSphere(v(-3.5, 0, 0), 2.25, colours.wake, .18);
    const ring = [];
    for (let i = 0; i <= 96; i++) {
      const a = TAU * i / 96;
      ring.push(v(3.2 + 2.45 * Math.cos(a), 2.45 * Math.sin(a), .3 * Math.sin(2 * a)));
    }
    polyline(ring, colours.electron, 1.8, .65);
    const eAngle = state.time * .72;
    const electron = v(3.2 + 2.45 * Math.cos(eAngle), 2.45 * Math.sin(eAngle), .3 * Math.sin(2 * eAngle));
    addDot(electron, 4, colours.electron, 1, 12);
    for (let i = 0; i < 22; i++) {
      const x = -1.6 + i * .18;
      const phase = i * .9 - state.time * 2;
      addLine(
        v(x, .35 * Math.sin(phase), .35 * Math.cos(phase)),
        v(x + .18, .35 * Math.sin(phase + .9), .35 * Math.cos(phase + .9)),
        colours.wake,
        1.2,
        .55 * state.alignment
      );
    }
    addLabel(v(-3.5, 3.05, 0), 'nuclear rotor');
    addLabel(v(3.2, 3.05, 0), 'W=1 atomic seat');
  }

  function gapCurve(turns, radius, centre = v()) {
    const points = [];
    const count = 150;
    for (let i = 0; i <= count; i++) {
      const t = turns * TAU * i / count;
      const kink = Math.exp(-Math.pow((t % TAU) - Math.PI, 2) / .11);
      points.push(add(centre, v(
        (radius + .18 * Math.cos(t / 2)) * Math.cos(t),
        (radius + .18 * Math.cos(t / 2)) * Math.sin(t),
        .36 * Math.sin(t / 2) + .45 * kink
      )));
    }
    return points;
  }

  function buildElectron() {
    const piPath = gapCurve(1, 2.4, v(-2.7, 0, 0));
    const twoPiPath = gapCurve(2, 2.4, v(2.7, 0, 0));
    polyline(piPath, colours.copper, 2, .7);
    polyline(twoPiPath, colours.electron, 2, .8);
    const gap = Math.floor((state.time * 45) % piPath.length);
    addDot(piPath[gap], 4, '#ef715b', 1, 12);
    const gap2 = Math.floor((state.time * 60) % twoPiPath.length);
    addDot(twoPiPath[gap2], 4, colours.electron, 1, 12);
    addLabel(v(-2.7, 3.25, 0), 'π director sector');
    addLabel(v(2.7, 3.25, 0), '2π directed-frame sector');
    addLine(v(-.3, -3.2, 0), v(.3, -3.2, 0), '#ef715b', 5, .9);
    addLabel(v(0, -3.6, 0), 'forced opening · hand-off · pinch');
  }

  function buildAtom() {
    const preset = presets[elementSelect.value];
    renderNucleus(preset.A > 80 ? .22 : .34, v(), false);
    const counts = preset.shells;
    counts.forEach((count, shellIndex) => {
      const n = shellIndex + 1;
      const radius = (2.15 + .8 * Math.log1p(n * n)) * state.layerScale;
      const ring = [];
      const tilt = .35 + shellIndex * .42;
      for (let i = 0; i <= 80; i++) {
        const a = TAU * i / 80;
        ring.push(orient(v(radius * Math.cos(a), radius * Math.sin(a), 0), tilt, tilt * .4, shellIndex * .8));
      }
      polyline(ring, colours.electron, 1, .18 + .08 * n);
      for (let i = 0; i < count; i++) {
        const rate = .9 / (n * n * n);
        const a = state.time * rate + TAU * i / count;
        const point = orient(v(radius * Math.cos(a), radius * Math.sin(a), 0), tilt, tilt * .4, shellIndex * .8);
        addDot(point, 2.4, colours.electron, .9, 6);
      }
      const labelAngle = .4 + shellIndex * 1.07;
      const labelPoint = orient(
        v(radius * Math.cos(labelAngle), radius * Math.sin(labelAngle), 0),
        tilt,
        tilt * .4,
        shellIndex * .8
      );
      addLabel(labelPoint, `n=${n} · ${count}e`);
    });
    addLabel(v(0, 1.1, 0), `${preset.symbol} nucleus`);
  }

  function engineMaterials() {
    return state.engine?.materials || {
      equal_resistance_1kg: {
        lithium_radius_m: .07646394684,
        uranium_radius_m: .02320737435,
        density_ratio_u_li: 35.76779026,
        surface_response_ratio_u_li: 10.85578933,
        far_response_ratio_u_li: 1
      },
      equal_radius_0_05m: {
        lithium_resistance_kg: .2796017462,
        uranium_resistance_kg: 10.00073661,
        koppa_ratio_u_li: 35.76779026,
        far_response_ratio_u_li: 35.76779026
      },
      flux_control_omega_1_full_alignment: {
        equal_resistance_1kg: {
          lithium_Wb: .3287162342,
          uranium_Wb: .002934347423
        },
        equal_radius_0_05m: {
          lithium_Wb: .06009997971,
          uranium_Wb: .06322480791
        }
      }
    };
  }

  function addWake(center, radius, colour, handedness) {
    const strands = 3;
    for (let strand = 0; strand < strands; strand++) {
      const points = [];
      for (let i = 0; i <= 80; i++) {
        const z = -4 + i * .1;
        const taper = radius * (1.1 + .08 * Math.abs(z));
        const phase = handedness * (z * 2.2 - state.time * 1.5) + strand * TAU / strands;
        points.push(add(center, v(taper * Math.cos(phase), taper * Math.sin(phase), z)));
      }
      polyline(points, colour, 1.1, .12 + .5 * state.alignment);
    }
  }

  function addFluxLoop(center, radius, colour, handedness) {
    const points = [];
    for (let i = 0; i <= 64; i++) {
      const phase = handedness * TAU * i / 64;
      points.push(add(center, v(
        radius * 1.35 * Math.cos(phase),
        0,
        radius * 1.35 * Math.sin(phase)
      )));
    }
    polyline(points, colour, 2, .18 + .62 * state.alignment);
    const markerPhase = handedness * state.time;
    addDot(add(center, v(
      radius * 1.35 * Math.cos(markerPhase),
      0,
      radius * 1.35 * Math.sin(markerPhase)
    )), 2.4, colour, state.alignment, 5);
  }

  function buildMaterials() {
    const data = engineMaterials();
    const sameMass = materialMode.value === 'mass';
    const liRadius = sameMass ? data.equal_resistance_1kg.lithium_radius_m : .05;
    const uRadius = sameMass ? data.equal_resistance_1kg.uranium_radius_m : .05;
    const visualMax = Math.max(liRadius, uRadius);
    const liVisual = 1.85 * liRadius / visualMax;
    const uVisual = 1.85 * uRadius / visualMax;
    const liCentre = v(-3.2, 0, 0);
    const uCentre = v(3.2, 0, 0);
    wireSphere(liCentre, liVisual, colours.li, .62);
    wireSphere(uCentre, uVisual, colours.u, .62);

    const liDots = sameMass ? 55 : 10;
    const uDots = sameMass ? 55 : 120;
    [[liCentre, liVisual, liDots, colours.li], [uCentre, uVisual, uDots, colours.u]].forEach(([centre, radius, count, colour], group) => {
      for (let i = 0; i < count; i++) {
        const zz = 2 * deterministic(i, group + 9) - 1;
        const rr = Math.cbrt(deterministic(i, group + 12)) * radius;
        const phi = TAU * deterministic(i, group + 15);
        const xy = Math.sqrt(Math.max(0, 1 - zz * zz));
        addDot(add(centre, v(rr * xy * Math.cos(phi), rr * xy * Math.sin(phi), rr * zz)), 1.4, colour, .5);
      }
    });
    addWake(liCentre, liVisual, colours.li, 1);
    addWake(uCentre, uVisual, colours.u, -1);
    addFluxLoop(liCentre, liVisual, colours.wake, 1);
    addFluxLoop(uCentre, uVisual, colours.wake, -1);
    addLabel(v(-3.2, 2.55, 0), `Li · ${sameMass ? '1 kg' : 'R=5 cm'}`);
    addLabel(v(3.2, 2.55, 0), `U · ${sameMass ? '1 kg' : 'R=5 cm'}`);
  }

  function acceleration(bodies) {
    const result = bodies.map(() => v());
    for (let i = 0; i < bodies.length; i++) {
      for (let j = i + 1; j < bodies.length; j++) {
        const d = sub(bodies[j].p, bodies[i].p);
        const r2 = dot(d, d);
        if (r2 === 0) return null;
        const kernel = mul(d, 1 / (r2 * Math.sqrt(r2)));
        result[i] = add(result[i], mul(kernel, bodies[j].k));
        result[j] = sub(result[j], mul(kernel, bodies[i].k));
      }
    }
    return result;
  }

  function invariant(bodies) {
    let energy = 0;
    let momentum = v();
    bodies.forEach(body => {
      energy += .5 * body.k * dot(body.vel, body.vel);
      momentum = add(momentum, mul(body.vel, body.k));
    });
    for (let i = 0; i < bodies.length; i++) {
      for (let j = i + 1; j < bodies.length; j++) {
        energy -= bodies[i].k * bodies[j].k / len(sub(bodies[j].p, bodies[i].p));
      }
    }
    return { energy, momentum };
  }

  function initialiseNBody(kind) {
    let bodies;
    if (kind === 'binary') {
      bodies = [
        { p: v(-2 / 3, 0, 0), vel: v(0, -2 * Math.sqrt(3) / 3, 0), k: 1, colour: colours.proton },
        { p: v(1 / 3, 0, 0), vel: v(0, Math.sqrt(3) / 3, 0), k: 2, colour: colours.blue }
      ];
    } else if (kind === 'lagrange') {
      const ks = [1, .02, .001];
      const side = 2.8, h = Math.sqrt(3) * side / 2;
      const raw = [v(-side / 2, -h / 3, 0), v(side / 2, -h / 3, 0), v(0, 2 * h / 3, 0)];
      const total = ks.reduce((a, b) => a + b, 0);
      const centre = raw.reduce((sum, p, i) => add(sum, mul(p, ks[i])), v());
      const bary = mul(centre, 1 / total);
      const omega = Math.sqrt(total / (side * side * side));
      bodies = raw.map((p, i) => {
        const q = sub(p, bary);
        return { p: q, vel: v(-omega * q.y, omega * q.x, 0), k: ks[i], colour: [colours.proton, colours.blue, colours.electron][i] };
      });
    } else {
      bodies = [
        { p: v(-.97000436, .24308753, 0), vel: v(.466203685, .43236573, 0), k: 1, colour: colours.proton },
        { p: v(.97000436, -.24308753, 0), vel: v(.466203685, .43236573, 0), k: 1, colour: colours.blue },
        { p: v(0, 0, 0), vel: v(-.93240737, -.86473146, 0), k: 1, colour: colours.electron }
      ];
    }
    const inv = invariant(bodies);
    state.nbody = {
      kind,
      bodies,
      trails: bodies.map(() => []),
      initialEnergy: inv.energy,
      initialMomentum: inv.momentum,
      energyDrift: 0,
      momentumDrift: 0,
      stepBudget: 0,
      collision: false,
      tick: 0
    };
  }

  function stepNBody() {
    if (!state.nbody || state.nbody.kind !== nbodySelect.value) initialiseNBody(nbodySelect.value);
    const sim = state.nbody;
    const dt = .0018;
    const a0 = acceleration(sim.bodies);
    if (!a0) {
      sim.collision = true;
      state.playing = false;
      return;
    }
    const predicted = sim.bodies.map((body, i) => ({
      ...body,
      p: add(body.p, add(mul(body.vel, dt), mul(a0[i], .5 * dt * dt)))
    }));
    const a1 = acceleration(predicted);
    if (!a1) {
      sim.collision = true;
      state.playing = false;
      return;
    }
    sim.bodies.forEach((body, i) => {
      body.p = predicted[i].p;
      body.vel = add(body.vel, mul(add(a0[i], a1[i]), .5 * dt));
    });
    sim.tick++;
    if (sim.tick % 4 === 0) {
      sim.bodies.forEach((body, i) => {
        sim.trails[i].push({ ...body.p });
        if (sim.trails[i].length > 700) sim.trails[i].shift();
      });
    }
    const inv = invariant(sim.bodies);
    sim.energyDrift = Math.abs(inv.energy / sim.initialEnergy - 1);
    const pScale = sim.bodies.reduce((sum, body) => sum + body.k * len(body.vel), 0);
    sim.momentumDrift = len(sub(inv.momentum, sim.initialMomentum)) / pScale;
  }

  function buildNBody() {
    if (!state.nbody || state.nbody.kind !== nbodySelect.value) initialiseNBody(nbodySelect.value);
    const sim = state.nbody;
    if (state.playing && state.speed > 0) {
      sim.stepBudget += 300 * state.speed * state.frameDt;
      const steps = Math.min(30, Math.floor(sim.stepBudget));
      sim.stepBudget -= steps;
      for (let i = 0; i < steps && !sim.collision; i++) stepNBody();
    }
    const display = 2.25;
    sim.trails.forEach((trail, i) => {
      polyline(trail.map(p => mul(p, display)), sim.bodies[i].colour, 1, .32);
    });
    sim.bodies.forEach((body, i) => {
      const radius = 3.5 + Math.min(5, Math.cbrt(body.k) * 3);
      addDot(mul(body.p, display), radius, body.colour, 1, 12);
      addLabel(add(mul(body.p, display), v(0, .22, 0)), String.fromCharCode(65 + i));
    });
  }

  function renderScene() {
    clearScene();
    if (state.step === 'rotor') buildRotor();
    else if (state.step === 'mesh') buildMesh();
    else if (state.step === 'gear') buildGear();
    else if (state.step === 'electron') buildElectron();
    else if (state.step === 'atom') buildAtom();
    else if (state.step === 'materials') buildMaterials();
    else if (state.step === 'nbody') buildNBody();
  }

  function draw() {
    ctx.clearRect(0, 0, state.width, state.height);
    const gradient = ctx.createRadialGradient(
      state.width * .5, state.height * .48, 0,
      state.width * .5, state.height * .48, Math.max(state.width, state.height) * .65
    );
    gradient.addColorStop(0, 'rgba(23,38,52,.68)');
    gradient.addColorStop(1, 'rgba(7,10,13,0)');
    ctx.fillStyle = gradient;
    ctx.fillRect(0, 0, state.width, state.height);

    scene.lines
      .map(line => ({ ...line, pa: project(line.a), pb: project(line.b) }))
      .sort((a, b) => a.pa.z + a.pb.z - b.pa.z - b.pb.z)
      .forEach(line => {
        ctx.globalAlpha = line.alpha;
        ctx.strokeStyle = line.colour;
        ctx.lineWidth = line.width;
        ctx.beginPath();
        ctx.moveTo(line.pa.x, line.pa.y);
        ctx.lineTo(line.pb.x, line.pb.y);
        ctx.stroke();
      });

    scene.dots
      .map(dotItem => ({ ...dotItem, projected: project(dotItem.position) }))
      .sort((a, b) => a.projected.z - b.projected.z)
      .forEach(dotItem => {
        const p = dotItem.projected;
        ctx.globalAlpha = dotItem.alpha;
        if (dotItem.glow) {
          const glow = ctx.createRadialGradient(p.x, p.y, 0, p.x, p.y, dotItem.glow);
          glow.addColorStop(0, dotItem.colour);
          glow.addColorStop(1, 'transparent');
          ctx.fillStyle = glow;
          ctx.beginPath();
          ctx.arc(p.x, p.y, dotItem.glow, 0, TAU);
          ctx.fill();
        }
        ctx.fillStyle = dotItem.colour;
        ctx.beginPath();
        ctx.arc(p.x, p.y, dotItem.radius, 0, TAU);
        ctx.fill();
      });

    ctx.globalAlpha = 1;
    ctx.font = '10px ui-monospace, Consolas, monospace';
    ctx.textAlign = 'center';
    scene.labels.forEach(label => {
      const p = project(label.position);
      ctx.fillStyle = label.colour;
      ctx.fillText(label.text, p.x, p.y);
    });
  }

  function number(value, digits = 4) {
    return Number.isFinite(value) ? value.toLocaleString('en-AU', { maximumSignificantDigits: digits }) : '—';
  }

  function scientific(value) {
    return Number.isFinite(value) ? value.toExponential(3) : '—';
  }

  function updateReadout() {
    const preset = presets[elementSelect.value];
    const laws = state.engine?.laws || {};
    if (state.step === 'materials') {
      const data = engineMaterials();
      const mass = materialMode.value === 'mass';
      const flux = mass
        ? data.flux_control_omega_1_full_alignment.equal_resistance_1kg
        : data.flux_control_omega_1_full_alignment.equal_radius_0_05m;
      readout.innerHTML = mass ? `
        <div class="row"><span>comparison</span><strong>1 kg each</strong></div>
        <div class="row"><span>Li radius</span><strong>${number(data.equal_resistance_1kg.lithium_radius_m)} m</strong></div>
        <div class="row"><span>U radius</span><strong>${number(data.equal_resistance_1kg.uranium_radius_m)} m</strong></div>
        <div class="row"><span>far response U/Li</span><strong>${number(data.equal_resistance_1kg.far_response_ratio_u_li)}</strong></div>
        <div class="row"><span>density U/Li</span><strong>${number(data.equal_resistance_1kg.density_ratio_u_li)}</strong></div>
        <div class="row"><span>surface U/Li</span><strong>${number(data.equal_resistance_1kg.surface_response_ratio_u_li)}</strong></div>
        <div class="row"><span>Φ control Li / U</span><strong>${scientific(flux.lithium_Wb * state.alignment)} / ${scientific(flux.uranium_Wb * state.alignment)} Wb</strong></div>` : `
        <div class="row"><span>comparison</span><strong>R = 0.05 m</strong></div>
        <div class="row"><span>Li resistance</span><strong>${number(data.equal_radius_0_05m.lithium_resistance_kg)} kg</strong></div>
        <div class="row"><span>U resistance</span><strong>${number(data.equal_radius_0_05m.uranium_resistance_kg)} kg</strong></div>
        <div class="row"><span>koppa U/Li</span><strong>${number(data.equal_radius_0_05m.koppa_ratio_u_li)}</strong></div>
        <div class="row"><span>far response U/Li</span><strong>${number(data.equal_radius_0_05m.far_response_ratio_u_li)}</strong></div>
        <div class="row"><span>Φ control Li / U</span><strong>${scientific(flux.lithium_Wb * state.alignment)} / ${scientific(flux.uranium_Wb * state.alignment)} Wb</strong></div>`;
    } else if (state.step === 'nbody') {
      const sim = state.nbody;
      readout.innerHTML = `
        <div class="row"><span>scenario</span><strong>${nbodySelect.options[nbodySelect.selectedIndex].text}</strong></div>
        <div class="row"><span>integrator</span><strong>velocity Verlet</strong></div>
        <div class="row"><span>energy drift</span><strong>${sim ? sim.energyDrift.toExponential(3) : '—'}</strong></div>
        <div class="row"><span>momentum drift</span><strong>${sim ? sim.momentumDrift.toExponential(3) : '—'}</strong></div>
        <div class="row"><span>softening</span><strong>none</strong></div>`;
    } else {
      readout.innerHTML = `
        <div class="row"><span>preset</span><strong>${preset.name}</strong></div>
        <div class="row"><span>Z / A</span><strong>${preset.Z} / ${preset.A}</strong></div>
        <div class="row"><span>grammar</span><strong>1α + ${preset.nd}d + ${preset.nt}t</strong></div>
        <div class="row"><span>proton mode</span><strong>W=${laws.proton_mode?.winding ?? 3}, (${laws.proton_mode?.p ?? 2},${laws.proton_mode?.q ?? 3})</strong></div>
        <div class="row"><span>traction ratio</span><strong>${number(laws.proton_traction_ratio ?? 12)}</strong></div>
        <div class="row"><span>gear ratio</span><strong>${number(laws.nuclear_atomic_gear_ratio ?? 1.034425898e8)}</strong></div>`;
    }
  }

  function setStep(step) {
    state.step = step;
    document.querySelectorAll('.step').forEach(button => {
      button.classList.toggle('active', button.dataset.step === step);
    });
    stepCopy.innerHTML = copy[step];
    sceneNote.textContent = notes[step];
    elementSelect.style.display = ['mesh', 'atom'].includes(step) ? '' : 'none';
    nbodySelect.style.display = step === 'nbody' ? '' : 'none';
    materialMode.closest('.control').style.display = step === 'materials' ? '' : 'none';
    updateReadout();
  }

  document.querySelectorAll('.step').forEach(button => {
    button.addEventListener('click', () => setStep(button.dataset.step));
  });
  playBtn.addEventListener('click', () => {
    state.playing = !state.playing;
    playBtn.textContent = state.playing ? 'Pause' : 'Play';
    playBtn.classList.toggle('active', state.playing);
  });
  resetBtn.addEventListener('click', () => {
    state.yaw = -.58;
    state.pitch = .28;
    state.zoom = 1;
  });
  elementSelect.addEventListener('change', () => {
    state.nucleus = null;
    updateReadout();
  });
  nbodySelect.addEventListener('change', () => {
    state.nbody = null;
    updateReadout();
  });
  materialMode.addEventListener('change', updateReadout);
  speed.addEventListener('input', () => {
    state.speed = Number(speed.value);
    document.getElementById('speedOut').textContent = `${state.speed.toFixed(1)}×`;
  });
  layers.addEventListener('input', () => {
    state.layerScale = Number(layers.value);
    document.getElementById('layerOut').textContent = `${state.layerScale.toFixed(1)}×`;
  });
  alignment.addEventListener('input', () => {
    state.alignment = Number(alignment.value);
    document.getElementById('alignOut').textContent = `${Math.round(state.alignment * 100)}%`;
    updateReadout();
  });

  let dragging = false, lastX = 0, lastY = 0;
  canvas.addEventListener('pointerdown', event => {
    dragging = true;
    lastX = event.clientX;
    lastY = event.clientY;
    canvas.setPointerCapture(event.pointerId);
  });
  canvas.addEventListener('pointermove', event => {
    if (!dragging) return;
    state.yaw += (event.clientX - lastX) * .008;
    state.pitch = Math.max(-1.35, Math.min(1.35, state.pitch + (event.clientY - lastY) * .008));
    lastX = event.clientX;
    lastY = event.clientY;
  });
  canvas.addEventListener('pointerup', event => {
    dragging = false;
    canvas.releasePointerCapture(event.pointerId);
  });
  canvas.addEventListener('wheel', event => {
    event.preventDefault();
    state.zoom = Math.max(.45, Math.min(2.5, state.zoom * Math.exp(-event.deltaY * .001)));
  }, { passive: false });

  document.addEventListener('sdt-engine-data', event => {
    state.engine = event.detail;
    const ratio = event.detail?.laws?.nuclear_atomic_gear_ratio;
    if (ratio) document.getElementById('gearValue').textContent = ratio.toExponential(5);
    updateReadout();
  });

  window.addEventListener('resize', resize);
  resize();
  setStep('rotor');

  function frame(now) {
    const dt = Math.min(.05, (now - state.last) / 1000);
    state.last = now;
    state.frameDt = dt;
    if (state.playing && state.step !== 'nbody') state.time += dt * state.speed;
    renderScene();
    draw();
    if (state.step === 'nbody' && state.nbody && state.nbody.tick % 12 === 0) updateReadout();
    requestAnimationFrame(frame);
  }
  requestAnimationFrame(frame);
})();
