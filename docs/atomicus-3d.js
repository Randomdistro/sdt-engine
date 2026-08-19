(() => {
  'use strict';
  window.__SDT_LOCAL_MOTION_CONTROL__ = true;

  const canvas = document.getElementById('scene');
  const ctx = canvas.getContext('2d');
  const readout = document.getElementById('readout');
  const stepCopy = document.getElementById('stepCopy');
  const sceneNote = document.getElementById('sceneNote');
  const playBtn = document.getElementById('playBtn');
  const resetBtn = document.getElementById('resetBtn');
  const elementSelect = document.getElementById('elementSelect');
  const nbodySelect = document.getElementById('nbodySelect');
  const tractionSelect = document.getElementById('tractionSelect');
  const topologySelect = document.getElementById('topologySelect');
  const rule18Btn = document.getElementById('rule18Btn');
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
    Be9: { symbol: 'Be', name: 'Beryllium-9', Z: 4, A: 9, nd: 1, nt: 1, shells: [2, 2] },
    B11: { symbol: 'B', name: 'Boron-11', Z: 5, A: 11, nd: 2, nt: 1, shells: [2, 3] },
    C12: { symbol: 'C', name: 'Carbon-12', Z: 6, A: 12, nd: 4, nt: 0, shells: [2, 4] },
    N14: { symbol: 'N', name: 'Nitrogen-14', Z: 7, A: 14, nd: 5, nt: 0, shells: [2, 5] },
    O16: { symbol: 'O', name: 'Oxygen-16', Z: 8, A: 16, nd: 6, nt: 0, shells: [2, 6] },
    Fe56: { symbol: 'Fe', name: 'Iron-56', Z: 26, A: 56, nd: 20, nt: 4, shells: [2, 8, 14, 2] },
    U238: { symbol: 'U', name: 'Uranium-238', Z: 92, A: 238, nd: 36, nt: 54, shells: [2, 8, 18, 32, 21, 9, 2] }
  };

  const copy = {
    rotor: `
      <span class="tag tag--d">DERIVED</span>
      <p>The canonical proton mode is a (2,3) trefoil with W=3. Its toroidal and poloidal speeds close the movement budget. The rendered tube is a topology diagram, not a measured proton-density map.</p>`,
    mesh: `
      <span class="tag tag--d">CONSTITUTIONAL GRAMMAR</span>
      <span class="tag tag--h">LEGACY GEOMETRIC CONTROL</span>
      <p>For Z≥2, one α core plus n<sub>d</sub> deuterons and n<sub>t</sub> tritons fixes the component count. This comparison view renders NSEQ05’s old tier layout; it is not the Atomicus contact construction because its links do not enforce touching rims, poles or construction order.</p>`,
    traction: `
      <span class="tag tag--d">CONTACT CONSTRUCTION</span>
      <span class="tag tag--h">CANDIDATE</span>
      <span class="tag tag--o">NO ENERGY LAW</span>
      <p>NSEQ16 builds only α, deuteron and triton modules through the whole-atom H→O valence stages. Every nucleon is drawn as an explicit four-lane (4,5) braid: each ring lap makes one complete local helix turn and then joins one lane over, so one filament closes after four laps. Every declared rim contact is p↔n at 2R<sub>p</sub>; equal and opposite local rotation gives zero contact-point slip. No contact energy is assigned.</p>`,
    gear: `
      <span class="tag tag--d">DERIVED TRACTION</span>
      <span class="tag tag--i">RATIO IDENTITY</span>
      <p>The W=3 rotor demands a traction ratio 12 at its boundary. The nuclear-to-atomic frequency ratio is exact arithmetic on the current seats. A physical transmission must still distinguish itself through re-locking dynamics.</p>`,
    electron: `
      <span class="tag tag--h">SEAT GUIDE</span>
      <span class="tag tag--h">RULE 18 SEPARATE</span>
      <p>The display lays out a polar 1s dyad, polar 2s dyad and six-seat equatorial 2p ring as deterministic guides, not measured electron trajectories. Schematic centre guides remain behind the separately named Rule 18 — under test toggle.</p>`,
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
      <p>The original A/B/C presets remain intact. A separate material-aware Li/U option uses the same GOM42 velocity-Verlet kernel with CM08 total koppa and physical contact radii. Wake and flux remain diagnostic overlays and do not enter the trajectory acceleration.</p>`
  };

  const notes = {
    rotor: 'W=3 · (p,q)=(2,3) · drag to inspect the six alternating arcs',
    mesh: 'NSEQ05-CONTROL-3 · legacy geometric control · link lines are nearest-neighbour diagnostics, not rim contacts or binding energy.',
    traction: 'CYCLIC_QUADRUPLE_HELIX_CANDIDATE under test · (4,5) braid · one local twist plus one-lane advance per lap · interleave-to-MeV conversion is pending.',
    gear: 'Nuclear and atomic scales are compressed. The displayed ratio comes from the executable engine dataset.',
    electron: '1s/2s polar dyads and six-seat 2p ring are display guides. The optional Rule 18 centre-line schematic is isolated and supplies no force.',
    atom: 'Log-compressed scale view. Electron paths are deterministic seat guides, not measured trajectories.',
    materials: 'Measured density inputs: Li 534 kg/m³; U 19,100 kg/m³. Wake brightness and Φ readouts are declared alignment/count controls, not bulk-magnetism predictions.',
    nbody: 'Velocity Verlet · central koppa kernel · no softening. Choose an A/B/C preset or the separate CM08 material instrument.'
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
    traction: null,
    rule18: false,
    nbody: null,
    renderRequested: true,
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
    state.renderRequested = true;
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

  function makeNucleus(preset, key, source = 'legacy') {
    if (
      source === 'atomicus'
      && window.SDT_TRACTION_GEAR?.presets?.[key]
    ) {
      const model = window.SDT_TRACTION_GEAR.build(key);
      const maximumRadius = Math.max(
        model.Rp,
        ...model.nodes.map(node => Math.hypot(...node.pos) + model.Rp)
      );
      const visualScale = 3.4 / maximumRadius;
      return {
        version: model.version,
        classification: 'ATOMICUS_CONTACT_CONSTRUCTION_CANDIDATE',
        valenceStage: model.constructionTransition,
        nodes: model.nodes.map((node, index) => ({
          type: node.type === 'p' ? 'proton' : 'neutron',
          layer: node.tier || 0,
          base: v(
            node.pos[0] * visualScale,
            node.pos[1] * visualScale,
            node.pos[2] * visualScale
          ),
          angles: v(
            deterministic(index, 1) * Math.PI,
            deterministic(index, 2) * Math.PI,
            deterministic(index, 3) * Math.PI
          )
        })),
        bonds: model.contacts.map(edge => [edge.a, edge.b]),
        shells: []
      };
    }
    if (preset.A === 1) {
      return {
        version: 'hydrogen-seed',
        classification: 'LEGACY_GEOMETRIC_CONTROL',
        nodes: [{
          type: 'proton',
          layer: 0,
          base: v(),
          angles: v(.3, .5, .1)
        }],
        bonds: [],
        shells: []
      };
    }
    if (typeof window.packNucleus !== 'function') {
      throw new Error('Atomicus 3D requires js/pack-nucleus.js');
    }
    const packed = window.packNucleus(preset.A, preset.Z);
    const maximumRadius = Math.max(
      window.SDT_NUCLEAR_PACKING?.R_p || 1,
      ...packed.map(node => Math.hypot(...node.pos))
    );
    const maximumTier = Math.max(0, ...packed.map(node => node.tier || 0));
    const visualExtent = 1.35 + Math.min(4.8, maximumTier * .62);
    const visualScale = visualExtent / maximumRadius;
    const nodes = packed.map((node, index) => ({
      type: node.type === 'p' ? 'proton' : 'neutron',
      layer: node.tier || 0,
      base: v(
        node.pos[0] * visualScale,
        node.pos[1] * visualScale,
        node.pos[2] * visualScale
      ),
      angles: v(
        deterministic(index, 1) * Math.PI,
        deterministic(index, 2) * Math.PI,
        deterministic(index, 3) * Math.PI
      )
    }));
    return {
      version: packed.version || window.SDT_NUCLEAR_PACKING?.version,
      classification: packed.classification || 'LEGACY_GEOMETRIC_CONTROL',
      nodes,
      bonds: (packed.contacts || []).map(edge => [edge[0], edge[1]]),
      shells: packed.shells || []
    };
  }

  function ensureNucleus() {
    const preset = presets[elementSelect.value];
    const source = state.step === 'atom' ? 'atomicus' : 'legacy';
    if (
      !state.nucleus
      || state.nucleus.key !== elementSelect.value
      || state.nucleus.source !== source
    ) {
      state.nucleus = {
        key: elementSelect.value,
        source,
        ...makeNucleus(preset, elementSelect.value, source)
      };
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
    renderNucleus(
      preset.A > 80 ? .78 : preset.A > 20 ? .92 : 1.15,
      v(),
      preset.A <= 80
    );
    const model = ensureNucleus();
    addLabel(
      v(0, 4.5, 0),
      `${preset.name} · ${preset.A} nucleons · ${model.version || 'NSEQ05'} legacy control`
    );
  }

  function ensureTraction() {
    if (!window.SDT_TRACTION_GEAR) {
      throw new Error('Atomicus 3D requires js/traction-gear-engine.js');
    }
    if (!state.traction || state.traction.key !== tractionSelect.value) {
      state.traction = window.SDT_TRACTION_GEAR.build(tractionSelect.value);
    }
    return state.traction;
  }

  function buildTraction() {
    const gear = window.SDT_TRACTION_GEAR;
    const model = ensureTraction();
    const topology = topologySelect.value;
    const maximumRadius = Math.max(
      model.Rp,
      ...model.nodes.map(node => Math.hypot(...node.pos) + model.Rp)
    );
    const visualScale = 3.35 / maximumRadius;
    const assemblyPhase = state.time * .22;
    const centres = model.nodes.map(node => rotateZ(v(
      node.pos[0] * visualScale,
      node.pos[1] * visualScale,
      node.pos[2] * visualScale
    ), assemblyPhase));
    const rimRadius = model.Rp * visualScale;

    for (const edge of model.contacts) {
      const a = centres[edge.a];
      const b = centres[edge.b];
      addLine(a, b, colours.mesh, edge.kind === 'dock' ? 2 : 1.25, .52);
      const midpoint = mul(add(a, b), .5);
      const normal = sub(b, a);
      let tangent = cross(normal, v(0, 0, 1));
      if (len(tangent) < 1e-10) tangent = v(1, 0, 0);
      tangent = mul(tangent, .08 / len(tangent));
      for (let tour = 0; tour < 4; tour++) {
        const offset = mul(tangent, tour - 1.5);
        addLine(
          add(midpoint, add(offset, v(0, 0, -.12))),
          add(midpoint, add(mul(offset, -1), v(0, 0, .12))),
          tour % 2 ? colours.wake : colours.electron,
          1,
          .58
        );
      }
    }

    model.nodes.forEach((node, index) => {
      const colour = node.type === 'p' ? colours.proton : colours.neutron;
      const base = v(
        node.pos[0] * visualScale,
        node.pos[1] * visualScale,
        node.pos[2] * visualScale
      );
      if (topology === 'trefoil') {
        const detail = model.nodes.length > 12 ? 34 : 64;
        const points = [];
        for (let i = 0; i <= detail; i++) {
          const u = TAU * i / detail;
          const local = gear.trefoilPoint(u, model.Rp);
          const spun = rotateZ(
            v(
              local[0] * visualScale,
              local[1] * visualScale,
              local[2] * visualScale
            ),
            node.spin * state.time * 1.15
          );
          points.push(rotateZ(add(base, spun), assemblyPhase));
        }
        polyline(points, colour, model.nodes.length > 12 ? 1 : 1.6, .88);
      } else {
        const palette = node.type === 'p'
          ? ['#ffd0ad', '#ef9d62', '#c96d43', '#ffb77f']
          : ['#c7e5ff', '#77bfff', '#477fab', '#9dd1ff'];
        const detail = model.nodes.length > 12 ? 28 : 44;
        for (let strand = 0; strand < 4; strand++) {
          const points = [];
          for (let i = 0; i <= detail; i++) {
            const theta = TAU * i / detail;
            const local = gear.braidStrandPoint(
              strand,
              theta,
              model.Rp
            );
            const spun = rotateZ(
              v(
                local[0] * visualScale,
                local[1] * visualScale,
                local[2] * visualScale
              ),
              node.spin * state.time * 1.15
            );
            points.push(rotateZ(add(base, spun), assemblyPhase));
          }
          polyline(
            points,
            palette[strand],
            model.nodes.length > 12 ? .85 : 1.25,
            .92
          );
        }
      }
      wireSphere(centres[index], rimRadius, colour, .08);

      const markerU = (
        node.spin * state.time * .42 % TAU + TAU
      ) % TAU;
      const marker = gear.curvePoint(topology, markerU, model.Rp);
      const markerWorld = rotateZ(add(v(
        node.pos[0] * visualScale,
        node.pos[1] * visualScale,
        node.pos[2] * visualScale
      ), rotateZ(v(
        marker[0] * visualScale,
        marker[1] * visualScale,
        marker[2] * visualScale
      ), node.spin * state.time * 1.15)), assemblyPhase);
      addDot(markerWorld, 2.1, colour, 1, 5);

      if (node.type === 'n') {
        const pose = gear.mobiusPose(state.time * 2, model.Rp);
        const base = v(
          node.pos[0] * visualScale,
          node.pos[1] * visualScale,
          node.pos[2] * visualScale
        );
        const electron = rotateZ(add(base, v(
          pose.position[0] * visualScale,
          pose.position[1] * visualScale,
          pose.position[2] * visualScale
        )), assemblyPhase);
        const director = v(
          pose.director[0] * rimRadius * .32,
          pose.director[1] * rimRadius * .32,
          pose.director[2] * rimRadius * .32
        );
        addDot(electron, 1.8, colours.electron, .95, 5);
        addLine(sub(electron, director), add(electron, director), colours.electron, 1, .62);
      }
    });
    addLabel(v(0, 4.7, 0), `${model.preset.name} · whole-atom valence stage · ${topology === 'trefoil' ? '(2,3) control' : '(4,5) cyclic quadruple helix'}`);
    if (topology !== 'trefoil') {
      addLabel(
        v(0, 4.35, 0),
        'one full local twist + one-lane seam advance per ring lap'
      );
    }
    addLabel(v(0, -4.45, 0), `${model.metrics.contactCount} declared rim contacts · geometric interleave ledger · no MeV map`);
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

  function electronSeatLayout(count) {
    const seats = [];
    let remaining = Math.max(0, count);
    const addPolarDyad = (name, n, radius, tilt) => {
      const occupancy = Math.min(2, remaining);
      const phase = state.time * .9 / (n * n * n);
      const axis = v(
        Math.sin(tilt) * Math.cos(phase),
        Math.cos(tilt),
        Math.sin(tilt) * Math.sin(phase)
      );
      for (let i = 0; i < occupancy; i++) {
        seats.push({
          name,
          n,
          position: mul(axis, radius * (i === 0 ? 1 : -1))
        });
      }
      remaining -= occupancy;
    };
    addPolarDyad('1s polar', 1, 1.55 * state.layerScale, .12);
    addPolarDyad('2s polar', 2, 2.35 * state.layerScale, .2);

    const pOccupancy = Math.min(6, remaining);
    const pRadius = 3.12 * state.layerScale;
    for (let i = 0; i < pOccupancy; i++) {
      const angle = state.time / 8 + TAU * i / 6;
      seats.push({
        name: '2p equatorial',
        n: 2,
        position: v(pRadius * Math.cos(angle), 0, pRadius * Math.sin(angle))
      });
    }
    remaining -= pOccupancy;

    let n = 3;
    while (remaining > 0) {
      const occupancy = Math.min(2 * n * n, remaining);
      const radius = (3.15 + .82 * Math.log1p(n * n)) * state.layerScale;
      const tilt = .34 + n * .31;
      for (let i = 0; i < occupancy; i++) {
        const angle = state.time * .9 / (n * n * n) + TAU * i / occupancy;
        seats.push({
          name: `${n} shell`,
          n,
          position: orient(
            v(radius * Math.cos(angle), radius * Math.sin(angle), 0),
            tilt,
            tilt * .35,
            n * .7
          )
        });
      }
      remaining -= occupancy;
      n++;
    }
    return seats;
  }

  function drawElectronSeatGuides(includeHigher = false) {
    for (const [radius, tilt, label] of [
      [1.55 * state.layerScale, .12, '1s polar dyad'],
      [2.35 * state.layerScale, .2, '2s polar dyad']
    ]) {
      const guide = [];
      for (let i = 0; i <= 80; i++) {
        const angle = TAU * i / 80;
        guide.push(orient(v(0, radius * Math.cos(angle), radius * Math.sin(angle)), tilt, 0, 0));
      }
      polyline(guide, colours.electron, 1, .25);
      addLabel(v(0, radius + .2, 0), label);
    }
    const pRing = [];
    const pRadius = 3.12 * state.layerScale;
    for (let i = 0; i <= 96; i++) {
      const angle = TAU * i / 96;
      pRing.push(v(pRadius * Math.cos(angle), 0, pRadius * Math.sin(angle)));
    }
    polyline(pRing, colours.electron, 1.4, .34);
    addLabel(v(pRadius, .28, 0), 'six-seat 2p ring');
    if (includeHigher) {
      wireSphere(v(), 4.35 * state.layerScale, colours.electron, .04);
    }
  }

  function buildElectron() {
    wireSphere(v(), .72, colours.mesh, .22);
    drawElectronSeatGuides(false);
    const seats = electronSeatLayout(10);
    seats.forEach(seat => addDot(seat.position, 3, colours.electron, .96, 8));
    addLabel(v(0, -4.2, 0), 'deterministic seat guide · Rule 18 kept separate');
  }

  function buildAtom() {
    const preset = presets[elementSelect.value];
    renderNucleus(preset.A > 80 ? .22 : .34, v(), false);
    const seats = electronSeatLayout(preset.Z);
    drawElectronSeatGuides(preset.Z > 10);
    if (state.rule18) {
      seats.forEach(seat => addLine(v(), seat.position, colours.wake, .8, .18));
      addLabel(v(0, -4.55, 0), 'Rule 18 — under test · schematic centre guides only');
    }
    seats.forEach(seat => addDot(seat.position, 2.4, colours.electron, .9, 6));
    const counts = new Map();
    seats.forEach(seat => counts.set(seat.name, (counts.get(seat.name) || 0) + 1));
    let labelY = 4.45;
    for (const [name, count] of counts) {
      addLabel(v(-4.5, labelY, 0), `${name} · ${count}e`);
      labelY -= .28;
    }
    const model = ensureNucleus();
    addLabel(
      v(0, 1.1, 0),
      model.valenceStage
        ? `${preset.symbol} atom · ${model.valenceStage}`
        : `${preset.symbol} nucleus · legacy control fallback`
    );
  }

  function engineMaterials() {
    return state.engine?.materials || {
      equal_resistance_1kg: {
        resistance_kg: 1,
        lithium_radius_m: .07646394684,
        uranium_radius_m: .02320737435,
        common_baryon_count: 5.9786374066e26,
        common_koppa_m: 7.426160049e-28,
        density_ratio_u_li: 35.76779026,
        surface_response_ratio_u_li: 10.85578933,
        far_response_ratio_u_li: 1
      },
      equal_radius_0_05m: {
        radius_m: .05,
        lithium_resistance_kg: .2796017462,
        uranium_resistance_kg: 10.00073661,
        lithium_baryon_count: 1.6716374586e26,
        uranium_baryon_count: 5.9790778013e27,
        lithium_koppa_m: 2.0763673171e-28,
        uranium_koppa_m: 7.4267070705e-27,
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

  function addWake(center, radius, colour, handedness, time = state.time) {
    const strands = 3;
    for (let strand = 0; strand < strands; strand++) {
      const points = [];
      for (let i = 0; i <= 80; i++) {
        const z = -4 + i * .1;
        const taper = radius * (1.1 + .08 * Math.abs(z));
        const phase = handedness * (z * 2.2 - time * 1.5) + strand * TAU / strands;
        points.push(add(center, v(taper * Math.cos(phase), taper * Math.sin(phase), z)));
      }
      polyline(points, colour, 1.1, .12 + .5 * state.alignment);
    }
  }

  function addFluxLoop(center, radius, colour, handedness, time = state.time) {
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
    const markerPhase = handedness * time;
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
        const contact = (bodies[i].radius || 0) + (bodies[j].radius || 0);
        if (!Number.isFinite(r2) || r2 <= contact * contact || r2 === 0) return null;
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

  function minimumClearance(bodies) {
    let clearance = Infinity;
    for (let i = 0; i < bodies.length; i++) {
      for (let j = i + 1; j < bodies.length; j++) {
        clearance = Math.min(
          clearance,
          len(sub(bodies[j].p, bodies[i].p))
            - (bodies[i].radius || 0)
            - (bodies[j].radius || 0)
        );
      }
    }
    return clearance;
  }

  function materialPair() {
    const data = engineMaterials();
    const sameMass = materialMode.value === 'mass';
    const mass = data.equal_resistance_1kg;
    const size = data.equal_radius_0_05m;
    const c = state.engine?.laws?.speed_of_light_m_s || 299792458;
    const liRadius = sameMass ? mass.lithium_radius_m : size.radius_m;
    const uRadius = sameMass ? mass.uranium_radius_m : size.radius_m;
    const liKoppa = sameMass ? mass.common_koppa_m : size.lithium_koppa_m;
    const uKoppa = sameMass ? mass.common_koppa_m : size.uranium_koppa_m;
    const liResistance = sameMass ? mass.resistance_kg : size.lithium_resistance_kg;
    const uResistance = sameMass ? mass.resistance_kg : size.uranium_resistance_kg;
    const physicalSeparation = 10 * (liRadius + uRadius);
    const displaySeparation = 2.8;
    const lengthScale = physicalSeparation / displaySeparation;
    const koppaScale = liKoppa;
    const ks = [liKoppa / koppaScale, uKoppa / koppaScale];
    const total = ks[0] + ks[1];
    const omega = Math.sqrt(total / Math.pow(displaySeparation, 3));
    const liOrbit = displaySeparation * ks[1] / total;
    const uOrbit = displaySeparation * ks[0] / total;
    const timeScale = Math.sqrt(
      Math.pow(lengthScale, 3) / (c * c * koppaScale)
    );
    const bodies = [
      {
        p: v(-liOrbit, 0, 0),
        vel: v(0, -omega * liOrbit, 0),
        k: ks[0],
        radius: liRadius / lengthScale,
        colour: colours.li,
        label: 'Li'
      },
      {
        p: v(uOrbit, 0, 0),
        vel: v(0, omega * uOrbit, 0),
        k: ks[1],
        radius: uRadius / lengthScale,
        colour: colours.u,
        label: 'U'
      }
    ];
    const period = TAU * Math.sqrt(
      Math.pow(physicalSeparation, 3)
        / (c * c * (liKoppa + uKoppa))
    );
    return {
      bodies,
      material: {
        mode: sameMass ? 'same total resistance' : 'same radius',
        liRadius,
        uRadius,
        liKoppa,
        uKoppa,
        liResistance,
        uResistance,
        physicalSeparation,
        lengthScale,
        timeScale,
        period,
        farRatio: sameMass
          ? mass.far_response_ratio_u_li
          : size.far_response_ratio_u_li,
        surfaceRatio: sameMass ? mass.surface_response_ratio_u_li : null
      }
    };
  }

  function initialiseNBody(kind) {
    let bodies;
    let material = null;
    if (kind === 'material') {
      const pair = materialPair();
      bodies = pair.bodies;
      material = pair.material;
    } else if (kind === 'binary') {
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
    } else if (kind === 'figure8') {
      bodies = [
        { p: v(-.97000436, .24308753, 0), vel: v(.466203685, .43236573, 0), k: 1, colour: colours.proton },
        { p: v(.97000436, -.24308753, 0), vel: v(.466203685, .43236573, 0), k: 1, colour: colours.blue },
        { p: v(0, 0, 0), vel: v(-.93240737, -.86473146, 0), k: 1, colour: colours.electron }
      ];
    } else {
      throw new RangeError(`unknown N-body scene: ${kind}`);
    }
    const inv = invariant(bodies);
    state.nbody = {
      kind,
      bodies,
      material,
      trails: bodies.map(() => []),
      initialEnergy: inv.energy,
      initialMomentum: inv.momentum,
      energyDrift: 0,
      momentumDrift: 0,
      minimumClearance: minimumClearance(bodies),
      stepBudget: 0,
      collision: false,
      visualTime: 0,
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
      return;
    }
    const predicted = sim.bodies.map((body, i) => ({
      ...body,
      p: add(body.p, add(mul(body.vel, dt), mul(a0[i], .5 * dt * dt)))
    }));
    const a1 = acceleration(predicted);
    if (!a1) {
      sim.collision = true;
      return;
    }
    sim.bodies.forEach((body, i) => {
      body.p = predicted[i].p;
      body.vel = add(body.vel, mul(add(a0[i], a1[i]), .5 * dt));
    });
    sim.minimumClearance = Math.min(
      sim.minimumClearance,
      minimumClearance(sim.bodies)
    );
    sim.visualTime += dt;
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
      const centre = mul(body.p, display);
      if (sim.material) {
        const visualRadius = Math.max(.08, body.radius * display);
        wireSphere(centre, visualRadius, body.colour, .62);
        addDot(centre, 3.2, body.colour, 1, 10);
        addWake(centre, visualRadius, body.colour, i === 0 ? 1 : -1, sim.visualTime);
        addFluxLoop(centre, visualRadius, colours.wake, i === 0 ? 1 : -1, sim.visualTime);
        addLabel(add(centre, v(0, visualRadius + .25, 0)), body.label);
      } else {
        const radius = 3.5 + Math.min(5, Math.cbrt(body.k) * 3);
        addDot(centre, radius, body.colour, 1, 12);
        addLabel(add(centre, v(0, .22, 0)), String.fromCharCode(65 + i));
      }
    });
  }

  function renderScene() {
    clearScene();
    if (state.step === 'rotor') buildRotor();
    else if (state.step === 'mesh') buildMesh();
    else if (state.step === 'traction') buildTraction();
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
    state.renderRequested = true;
    const preset = presets[elementSelect.value];
    const laws = state.engine?.laws || {};
    if (state.step === 'traction') {
      const model = ensureTraction();
      const calibration = model.canonicalNucleon?.calibration;
      const braidResidual = model.braid.maximumSeamResidual
        ?? model.braid.maximumLaneSeamResidual
        ?? model.braid.frameSeamResidual;
      const nd = model.grammar.seed ? 'seed' : model.grammar.nd;
      const nt = model.grammar.seed ? 'seed' : model.grammar.nt;
      readout.innerHTML = `
        <div class="row"><span>contact instrument</span><strong>${model.version}</strong></div>
        <div class="row"><span>isotope</span><strong>${model.preset.name}</strong></div>
        <div class="row"><span>valence stage</span><strong>${model.constructionTransition}</strong></div>
        <div class="row"><span>grammar d / t</span><strong>${nd} / ${nt}</strong></div>
        <div class="row"><span>modules</span><strong>${model.modules.map(module => module.kind === 'alpha' ? 'α' : module.kind[0]).join('+')}</strong></div>
        <div class="row"><span>nucleons / contacts</span><strong>${model.metrics.nucleonCount} / ${model.metrics.contactCount}</strong></div>
        <div class="row"><span>maximum rim residual</span><strong>${model.metrics.maxContactResidual.toExponential(2)}</strong></div>
        <div class="row"><span>maximum traction slip</span><strong>${model.metrics.maxSlip.toExponential(2)}</strong></div>
        <div class="row"><span>module-centre seat residual</span><strong>${model.metrics.maxModuleSeatResidual.toExponential(2)}</strong></div>
        <div class="row"><span>proton-centre control residual</span><strong>${model.metrics.maxProtonSeatResidual.toExponential(2)}</strong></div>
        <div class="row"><span>contact graph</span><strong>${model.metrics.unlikeContacts ? 'p↔n bipartite' : 'rejected'}</strong></div>
        <div class="row"><span>topology view</span><strong>${calibration ? `${calibration.poses.length}-unit conserved wake mesh` : (topologySelect.value === 'trefoil' ? '(2,3) canonical control' : '(4,5) cyclic quadruple-helix candidate')}</strong></div>
        ${topologySelect.value !== 'trefoil' ? `
        <div class="row"><span>braid splice</span><strong>0→1→2→3→0 · residual ${scientific(braidResidual)}</strong></div>
        <div class="row"><span>local twist / lane advance</span><strong>${number(model.braid.localTwistsPerLap ?? 1)} turn / ${model.braid.seamLaneAdvance ?? 1} lane</strong></div>
        <div class="row"><span>circulation</span><strong>${calibration ? 'phase-locked mesh · 1.830c model speed' : `${number(model.braid.analyticSpeedRatio)}× on one common period`}</strong></div>` : ''}
        <div class="row"><span>NSEQ05 comparison</span><strong>${model.nseq05?.tractionConsistent ? 'unexpected pass' : 'rejected legacy geometric control'}</strong></div>
        <div class="row"><span>classification</span><strong>${calibration?.classification || 'ATOMICUS_CONTACT_CONSTRUCTION_CANDIDATE'}</strong></div>
        <div class="row"><span>interleave → mass defect</span><strong>${calibration ? `${number(calibration.model.bindingEnergyMeV,8)} MeV` : 'PENDING · no MeV map'}</strong></div>`;
    } else if (state.step === 'materials') {
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
      if (nbodySelect.value === 'material') {
        const material = sim?.material;
        const clearance = material && sim
          ? sim.minimumClearance * material.lengthScale
          : NaN;
        readout.innerHTML = `
        <div class="row"><span>scenario</span><strong>Material-aware SDT · Li/U</strong></div>
        <div class="row"><span>comparison</span><strong>${material?.mode || (materialMode.value === 'mass' ? 'same total resistance' : 'same radius')}</strong></div>
        <div class="row"><span>Li / U radius</span><strong>${material ? `${number(material.liRadius)} / ${number(material.uRadius)} m` : '—'}</strong></div>
        <div class="row"><span>Li / U resistance</span><strong>${material ? `${number(material.liResistance)} / ${number(material.uResistance)} kg` : '—'}</strong></div>
        <div class="row"><span>koppa U/Li</span><strong>${material ? number(material.uKoppa / material.liKoppa) : '—'}</strong></div>
        <div class="row"><span>far response U/Li</span><strong>${material ? number(material.farRatio) : '—'}</strong></div>
        <div class="row"><span>minimum clearance</span><strong>${scientific(clearance)} m</strong></div>
        <div class="row"><span>physical orbit period</span><strong>${material ? scientific(material.period) : '—'} s</strong></div>
        <div class="row"><span>simulation time unit</span><strong>${material ? scientific(material.timeScale) : '—'} s</strong></div>
        <div class="row"><span>energy / momentum drift</span><strong>${sim ? `${sim.energyDrift.toExponential(2)} / ${sim.momentumDrift.toExponential(2)}` : '—'}</strong></div>
        <div class="row"><span>wake / flux force</span><strong>off · diagnostic only</strong></div>`;
      } else {
        readout.innerHTML = `
        <div class="row"><span>scenario</span><strong>${nbodySelect.options[nbodySelect.selectedIndex].text}</strong></div>
        <div class="row"><span>integrator</span><strong>velocity Verlet</strong></div>
        <div class="row"><span>energy drift</span><strong>${sim ? sim.energyDrift.toExponential(3) : '—'}</strong></div>
        <div class="row"><span>momentum drift</span><strong>${sim ? sim.momentumDrift.toExponential(3) : '—'}</strong></div>
        <div class="row"><span>softening</span><strong>none</strong></div>`;
      }
    } else {
      const nucleusModel = state.step === 'mesh' || state.step === 'atom'
        ? ensureNucleus()
        : null;
      readout.innerHTML = `
        <div class="row"><span>preset</span><strong>${preset.name}</strong></div>
        <div class="row"><span>Z / A</span><strong>${preset.Z} / ${preset.A}</strong></div>
        <div class="row"><span>grammar</span><strong>${preset.A === 1 ? 'hydrogen seed' : `1α + ${preset.nd}d + ${preset.nt}t`}</strong></div>
        ${nucleusModel ? `<div class="row"><span>nuclear rendering</span><strong>${nucleusModel.classification} · ${nucleusModel.version}</strong></div>` : ''}
        ${nucleusModel?.valenceStage ? `<div class="row"><span>whole-atom valence stage</span><strong>${nucleusModel.valenceStage}</strong></div>` : ''}
        ${state.step === 'atom' ? `<div class="row"><span>Rule 18 layer</span><strong>${state.rule18 ? 'UNDER TEST · on' : 'UNDER TEST · off'}</strong></div>` : ''}
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
    tractionSelect.style.display = step === 'traction' ? '' : 'none';
    topologySelect.style.display = step === 'traction' ? '' : 'none';
    rule18Btn.style.display = step === 'atom' ? '' : 'none';
    materialMode.closest('.control').style.display =
      step === 'materials'
      || (step === 'nbody' && nbodySelect.value === 'material')
        ? ''
        : 'none';
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
    state.renderRequested = true;
  });
  elementSelect.addEventListener('change', () => {
    state.nucleus = null;
    updateReadout();
  });
  tractionSelect.addEventListener('change', () => {
    state.traction = null;
    updateReadout();
  });
  topologySelect.addEventListener('change', updateReadout);
  rule18Btn.addEventListener('click', () => {
    state.rule18 = !state.rule18;
    rule18Btn.setAttribute('aria-pressed', String(state.rule18));
    rule18Btn.textContent = `Rule 18 — under test: ${state.rule18 ? 'on' : 'off'}`;
    rule18Btn.classList.toggle('active', state.rule18);
    updateReadout();
  });
  nbodySelect.addEventListener('change', () => {
    state.nbody = null;
    setStep(state.step);
  });
  materialMode.addEventListener('change', () => {
    if (state.step === 'nbody' && nbodySelect.value === 'material') {
      state.nbody = null;
    }
    updateReadout();
  });
  speed.addEventListener('input', () => {
    state.speed = Number(speed.value);
    document.getElementById('speedOut').textContent = `${state.speed.toFixed(1)}×`;
  });
  layers.addEventListener('input', () => {
    state.layerScale = Number(layers.value);
    document.getElementById('layerOut').textContent = `${state.layerScale.toFixed(1)}×`;
    state.renderRequested = true;
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
    state.renderRequested = true;
  });
  canvas.addEventListener('pointerup', event => {
    dragging = false;
    canvas.releasePointerCapture(event.pointerId);
  });
  canvas.addEventListener('wheel', event => {
    event.preventDefault();
    state.zoom = Math.max(.45, Math.min(2.5, state.zoom * Math.exp(-event.deltaY * .001)));
    state.renderRequested = true;
  }, { passive: false });

  document.addEventListener('sdt-engine-data', event => {
    state.engine = event.detail;
    if (state.nbody?.kind === 'material') state.nbody = null;
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
    const rect = canvas.getBoundingClientRect();
    const top = Number.isFinite(rect.top) ? rect.top : 0;
    const left = Number.isFinite(rect.left) ? rect.left : 0;
    const bottom = Number.isFinite(rect.bottom) ? rect.bottom : top + rect.height;
    const right = Number.isFinite(rect.right) ? rect.right : left + rect.width;
    const viewportHeight = window.innerHeight || state.height;
    const viewportWidth = window.innerWidth || state.width;
    const visible =
      bottom >= 0
      && top <= viewportHeight
      && right >= 0
      && left <= viewportWidth;
    const root = document.documentElement;
    const motionSetting = root?.getAttribute?.('data-sdt-motion');
    const motionOff =
      motionSetting === 'off'
      || (
        motionSetting == null
        && window.matchMedia?.('(prefers-reduced-motion: reduce)')?.matches
      );
    const animate =
      state.playing
      && !motionOff
      && !document.hidden
      && visible
      && !(state.step === 'nbody' && state.nbody?.collision);
    if (!document.hidden && visible && (animate || state.renderRequested)) {
      state.frameDt = animate ? dt : 0;
      if (animate && state.step !== 'nbody') state.time += dt * state.speed;
      renderScene();
      draw();
      state.renderRequested = false;
      if (
        animate
        && state.step === 'nbody'
        && state.nbody
        && state.nbody.tick % 12 === 0
      ) updateReadout();
    }
    requestAnimationFrame(frame);
  }
  renderScene();
  draw();
  state.renderRequested = false;
  requestAnimationFrame(frame);
})();
