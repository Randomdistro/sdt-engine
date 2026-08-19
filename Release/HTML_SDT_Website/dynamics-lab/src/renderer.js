import * as THREE from "../vendor/three.module.js";
import { barycentre, finiteDifferenceAccelerations } from "./diagnostics.js";

const COLORS = [0x54d3c2, 0x8cb4ff, 0xf4be58, 0xcf8cff, 0xff7d88, 0x7fe08c, 0xf09ed3];
const DEFAULT_OVERLAYS = {
  trails: true, velocity: false, acceleration: false, barycentre: false,
  joints: true, constraints: false, influx: false, occlusion: false,
};

function vector(values) {
  return new THREE.Vector3(values[0], values[1], values[2]);
}

function quaternion(values = [1, 0, 0, 0]) {
  return new THREE.Quaternion(values[1], values[2], values[3], values[0]);
}

function disposeObject(object) {
  object.traverse((child) => {
    child.geometry?.dispose();
    if (Array.isArray(child.material)) child.material.forEach((material) => material.dispose());
    else child.material?.dispose();
  });
}

export class DynamicsRenderer extends EventTarget {
  #canvas;
  #renderer;
  #scene;
  #camera;
  #root;
  #grid;
  #result;
  #case;
  #frameIndex = 0;
  #scale = 1;
  #entities = new Map();
  #overlays = { ...DEFAULT_OVERLAYS };
  #frameMode = "inertial";
  #referenceId = "";
  #interactionPair = { target: "", source: "" };
  #drag = null;
  #orbit = { yaw: 0.55, pitch: 0.42, distance: 7, target: new THREE.Vector3() };
  #resizeObserver;

  constructor(canvas) {
    super();
    this.#canvas = canvas;
    this.#renderer = new THREE.WebGLRenderer({ canvas, antialias: true, alpha: false, powerPreference: "high-performance" });
    this.#renderer.setPixelRatio(Math.min(window.devicePixelRatio || 1, 2));
    this.#renderer.setClearColor(0x05090e, 1);
    this.#renderer.outputColorSpace = THREE.SRGBColorSpace;
    this.#scene = new THREE.Scene();
    this.#scene.fog = new THREE.FogExp2(0x05090e, 0.022);
    this.#camera = new THREE.PerspectiveCamera(42, 1, 0.01, 1000);
    this.#root = new THREE.Group();
    this.#scene.add(this.#root);
    this.#scene.add(new THREE.HemisphereLight(0xb8dbff, 0x172334, 1.8));
    const key = new THREE.DirectionalLight(0xffffff, 2.6);
    key.position.set(4, 7, 5);
    this.#scene.add(key);
    this.#grid = new THREE.GridHelper(20, 20, 0x294459, 0x17283a);
    this.#grid.material.transparent = true;
    this.#grid.material.opacity = 0.55;
    this.#scene.add(this.#grid);
    this.#scene.add(new THREE.AxesHelper(1.2));
    this.#bindControls();
    this.#resizeObserver = new ResizeObserver(() => this.resize());
    this.#resizeObserver.observe(canvas);
    this.resize();
    this.#render();
  }

  get startupInfo() {
    return {
      renderer: "three",
      revision: THREE.REVISION,
      webgl: this.#renderer.capabilities.isWebGL2 ? "WebGL2" : "WebGL1",
    };
  }

  setResult(result) {
    this.#result = result;
    this.#case = result?.normalized_case;
    this.#frameIndex = 0;
    this.#referenceId = result?.trajectory?.[0]?.states?.[0]?.id ?? "";
    this.#rebuildEntities();
    this.fit();
    this.setFrame(0);
  }

  setFrame(index) {
    const frames = this.#result?.trajectory ?? [];
    if (!frames.length) return;
    this.#frameIndex = Math.max(0, Math.min(frames.length - 1, index));
    this.#updateScene(frames[this.#frameIndex]);
    this.dispatchEvent(new CustomEvent("frame", { detail: { index: this.#frameIndex } }));
  }

  setOverlay(name, enabled) {
    if (!(name in this.#overlays)) return;
    this.#overlays[name] = Boolean(enabled);
    if (this.#result) this.#rebuildOverlays();
  }

  setInteractionPair(target, source) {
    this.#interactionPair = { target, source };
    if (this.#result) this.#rebuildOverlays();
  }

  setFrameMode(mode, referenceId = this.#referenceId) {
    this.#frameMode = mode === "rotating" ? "rotating" : "inertial";
    this.#referenceId = referenceId;
    if (this.#result) this.setFrame(this.#frameIndex);
  }

  fit() {
    const frames = this.#result?.trajectory ?? [];
    const positions = frames.flatMap((frame) => frame.states.map((state) => vector(state.position_m)));
    if (!positions.length) {
      this.#orbit.target.set(0, 0, 0);
      this.#orbit.distance = 7;
      return;
    }
    const box = new THREE.Box3().setFromPoints(positions);
    const size = box.getSize(new THREE.Vector3());
    const maxSize = Math.max(size.x, size.y, size.z, 1e-12);
    this.#scale = 6 / maxSize;
    this.#orbit.target.set(0, 0, 0);
    this.#orbit.distance = 9;
    this.#grid.scale.setScalar(1);
  }

  resize() {
    const width = Math.max(1, this.#canvas.clientWidth);
    const height = Math.max(1, this.#canvas.clientHeight);
    this.#renderer.setSize(width, height, false);
    this.#camera.aspect = width / height;
    this.#camera.updateProjectionMatrix();
  }

  destroy() {
    this.#resizeObserver.disconnect();
    disposeObject(this.#root);
    this.#renderer.dispose();
  }

  #rebuildEntities() {
    disposeObject(this.#root);
    this.#root.clear();
    this.#entities.clear();
    const definitions = this.#case?.bodies ?? this.#case?.links ?? [];
    definitions.forEach((definition, index) => {
      let object;
      if (this.#case.problem_class === "articulated_rigid") {
        const radius = Math.max(definition.length_m * 0.035 * this.#scale, 0.025);
        const length = Math.max(definition.length_m * this.#scale, 0.08);
        const geometry = new THREE.CapsuleGeometry(radius, Math.max(0.01, length - 2 * radius), 8, 16);
        geometry.rotateZ(Math.PI);
        object = new THREE.Mesh(geometry, new THREE.MeshStandardMaterial({
          color: COLORS[index % COLORS.length], roughness: 0.48, metalness: 0.16,
        }));
      } else {
        const physicalRadius = definition.radius_m ?? Math.cbrt(definition.koppa_m || 1) * 0.2;
        const radius = Math.max(0.055, Math.min(0.28, physicalRadius * this.#scale));
        object = new THREE.Mesh(
          new THREE.SphereGeometry(radius, 28, 18),
          new THREE.MeshStandardMaterial({ color: COLORS[index % COLORS.length], roughness: 0.4, metalness: 0.2 }),
        );
      }
      object.name = definition.id;
      const halo = new THREE.Mesh(
        new THREE.SphereGeometry(0.115, 16, 10),
        new THREE.MeshBasicMaterial({ color: COLORS[index % COLORS.length], transparent: true, opacity: 0.08, depthWrite: false }),
      );
      if (this.#case.problem_class !== "articulated_rigid") object.add(halo);
      this.#root.add(object);
      this.#entities.set(definition.id, object);
    });
    this.#rebuildOverlays();
  }

  #rebuildOverlays() {
    for (const child of [...this.#root.children]) {
      if (child.userData.overlay) {
        disposeObject(child);
        this.#root.remove(child);
      }
    }
    if (!this.#result?.trajectory?.length) return;
    if (this.#overlays.trails) this.#addTrails();
    if (this.#overlays.barycentre && this.#case.problem_class !== "sdt_occlusion_nbody") {
      const marker = new THREE.Mesh(
        new THREE.IcosahedronGeometry(0.07, 1),
        new THREE.MeshBasicMaterial({ color: 0xffffff, wireframe: true }),
      );
      marker.name = "barycentre";
      marker.userData.overlay = "barycentre";
      this.#root.add(marker);
    }
    this.setFrame(this.#frameIndex);
  }

  #addTrails() {
    const ids = this.#result.trajectory[0].states.map(({ id }) => id);
    ids.forEach((id, index) => {
      const points = this.#result.trajectory
        .map((frame) => frame.states.find((state) => state.id === id))
        .filter(Boolean)
        .map((state) => vector(state.position_m).multiplyScalar(this.#scale));
      const geometry = new THREE.BufferGeometry().setFromPoints(points);
      const material = new THREE.LineBasicMaterial({ color: COLORS[index % COLORS.length], transparent: true, opacity: 0.5 });
      const line = new THREE.Line(geometry, material);
      line.userData.overlay = "trail";
      line.userData.sourcePoints = points;
      line.name = `${id}-trail`;
      this.#root.add(line);
    });
  }

  #rotationForFrame(frame) {
    if (this.#frameMode !== "rotating") return { angle: 0, centre: new THREE.Vector3() };
    const first = this.#result.trajectory[0];
    const initialCentre = vector(barycentre(first, this.#case));
    const currentCentre = vector(barycentre(frame, this.#case));
    const initialReference = first.states.find(({ id }) => id === this.#referenceId)?.position_m;
    const currentReference = frame.states.find(({ id }) => id === this.#referenceId)?.position_m;
    if (!initialReference || !currentReference) return { angle: 0, centre: currentCentre };
    const initial = vector(initialReference).sub(initialCentre);
    const current = vector(currentReference).sub(currentCentre);
    return {
      angle: Math.atan2(initial.y, initial.x) - Math.atan2(current.y, current.x),
      centre: currentCentre,
    };
  }

  #displayPosition(values, transform) {
    return vector(values).sub(transform.centre).applyAxisAngle(new THREE.Vector3(0, 0, 1), transform.angle).multiplyScalar(this.#scale);
  }

  #updateScene(frame) {
    const transform = this.#rotationForFrame(frame);
    const accelerations = finiteDifferenceAccelerations(this.#result.trajectory, this.#frameIndex);
    for (const state of frame.states) {
      const object = this.#entities.get(state.id);
      if (!object) continue;
      object.position.copy(this.#displayPosition(state.position_m, transform));
      if (state.quaternion_wxyz) {
        object.quaternion.copy(quaternion(state.quaternion_wxyz));
        if (transform.angle) object.rotateOnWorldAxis(new THREE.Vector3(0, 0, 1), transform.angle);
      }
    }
    for (const child of [...this.#root.children]) {
      if (["dynamic-vector", "joint", "constraint", "influx", "occlusion"].includes(child.userData.overlay)) {
        disposeObject(child); this.#root.remove(child);
      }
    }
    if (this.#overlays.barycentre && this.#case.problem_class !== "sdt_occlusion_nbody") {
      const marker = this.#root.getObjectByName("barycentre");
      marker?.position.copy(this.#displayPosition(barycentre(frame, this.#case), transform));
    }
    if (this.#overlays.trails) this.#updateTrailTransforms(transform);
    if (this.#overlays.velocity || this.#overlays.acceleration) {
      this.#addVectors(frame, accelerations, transform);
    }
    if (this.#overlays.joints || this.#overlays.constraints) this.#addJointOverlays(frame, transform);
    if (this.#overlays.influx) this.#addInflux(frame, transform);
    if (this.#overlays.occlusion) this.#addOcclusion(frame, transform);
  }

  #updateTrailTransforms(transform) {
    for (const child of this.#root.children.filter(({ userData }) => userData.overlay === "trail")) {
      const points = this.#result.trajectory
        .map((frame) => frame.states.find(({ id }) => `${id}-trail` === child.name))
        .filter(Boolean)
        .map((state) => this.#displayPosition(state.position_m, transform));
      child.geometry.setFromPoints(points);
    }
  }

  #addVectors(frame, accelerations, transform) {
    const addArrow = (origin, values, color) => {
      const raw = vector(values);
      const length = raw.length();
      if (!Number.isFinite(length) || length === 0) return;
      const arrow = new THREE.ArrowHelper(raw.normalize(), origin, Math.min(1.5, Math.max(0.15, Math.log10(1 + length) * 0.12)), color, 0.1, 0.06);
      arrow.userData.overlay = "dynamic-vector";
      this.#root.add(arrow);
    };
    for (const state of frame.states) {
      const origin = this.#displayPosition(state.position_m, transform);
      if (this.#overlays.velocity) addArrow(origin, state.velocity_m_s, 0x8cb4ff);
      if (this.#overlays.acceleration) addArrow(origin, accelerations.get(state.id) ?? [0, 0, 0], 0xffb55f);
    }
  }

  #addJointOverlays(frame, transform) {
    if (!this.#case.joints) return;
    const states = new Map(frame.states.map((state) => [state.id, state]));
    for (const joint of this.#case.joints) {
      const child = states.get(joint.child);
      if (!child) continue;
      const childAnchorWorld = vector(child.position_m).add(
        vector(joint.child_anchor_m).applyQuaternion(quaternion(child.quaternion_wxyz)),
      );
      const parent = joint.parent === null ? null : states.get(joint.parent);
      const parentAnchorWorld = parent
        ? vector(parent.position_m).add(
          vector(joint.parent_anchor_m).applyQuaternion(quaternion(parent.quaternion_wxyz)),
        )
        : vector(joint.parent_anchor_m);
      const childPosition = this.#displayPosition(childAnchorWorld.toArray(), transform);
      const parentPosition = this.#displayPosition(parentAnchorWorld.toArray(), transform);
      if (this.#overlays.joints) {
        const axis = vector(joint.axis_world).normalize();
        const line = new THREE.Line(
          new THREE.BufferGeometry().setFromPoints([
            parentPosition.clone().addScaledVector(axis, -0.24),
            parentPosition.clone().addScaledVector(axis, 0.24),
          ]),
          new THREE.LineBasicMaterial({ color: 0xd59bff }),
        );
        line.userData.overlay = "joint";
        this.#root.add(line);
      }
      if (this.#overlays.constraints) {
        const line = new THREE.Line(
          new THREE.BufferGeometry().setFromPoints([parentPosition, childPosition]),
          new THREE.LineDashedMaterial({ color: 0xff6b78, dashSize: 0.04, gapSize: 0.025 }),
        );
        line.computeLineDistances();
        line.userData.overlay = "constraint";
        this.#root.add(line);
      }
    }
  }

  #addInflux(frame, transform) {
    for (const state of frame.states) {
      const centre = this.#displayPosition(state.position_m, transform);
      for (let index = 0; index < 8; index += 1) {
        const angle = index * Math.PI / 4;
        const outer = centre.clone().add(new THREE.Vector3(Math.cos(angle), Math.sin(angle), 0.3 * Math.sin(angle * 2)).multiplyScalar(0.55));
        const line = new THREE.Line(
          new THREE.BufferGeometry().setFromPoints([outer, centre]),
          new THREE.LineBasicMaterial({ color: 0x397a78, transparent: true, opacity: 0.4 }),
        );
        line.userData.overlay = "influx"; this.#root.add(line);
      }
    }
  }

  #addOcclusion(frame, transform) {
    const selected = (this.#result?.interactions ?? []).filter(({ target, source }) =>
      target === this.#interactionPair.target && source === this.#interactionPair.source);
    if (selected.length !== 49) return;
    const current = new Map(frame.states.map((state) => [state.id, state]));
    const terminal = new Map(this.#result.trajectory.at(-1).states.map((state) => [state.id, state]));
    const definitions = new Map((this.#case.bodies ?? []).map((body) => [body.id, body]));
    const projectCentre = (absolute, id) => {
      const terminalBody = terminal.get(id);
      const currentBody = current.get(id);
      if (!terminalBody || !currentBody) return this.#displayPosition(absolute, transform);
      const offset = vector(absolute).sub(vector(terminalBody.position_m));
      return this.#displayPosition(vector(currentBody.position_m).add(offset).toArray(), transform);
    };
    const points = [];
    const colors = [];
    for (const interaction of selected) {
      const from = projectCentre(interaction.target_centre_m, interaction.target);
      const to = projectCentre(interaction.source_centre_m, interaction.source);
      points.push(from, to);
      const visible = 1 - interaction.shield_fraction;
      const color = new THREE.Color().setRGB(0.25 + 0.65 * visible, 0.18 + 0.65 * visible, 0.12 + 0.25 * visible);
      colors.push(color.r, color.g, color.b, color.r, color.g, color.b);
    }
    const geometry = new THREE.BufferGeometry().setFromPoints(points);
    geometry.setAttribute("color", new THREE.Float32BufferAttribute(colors, 3));
    const matrix = new THREE.LineSegments(
      geometry,
      new THREE.LineBasicMaterial({ vertexColors: true, transparent: true, opacity: 0.62 }),
    );
    matrix.userData.overlay = "occlusion";
    matrix.name = "computed-49-channel-occlusion";
    this.#root.add(matrix);

    const addSection = (id, channel, absolute, color) => {
      const definition = definitions.get(id);
      const centre = projectCentre(absolute, id);
      const radius = Math.max(0.018, Math.min(0.22, (definition?.radius_m ?? 1) * this.#scale / 3));
      const ring = new THREE.Mesh(
        new THREE.RingGeometry(radius * 0.88, radius, 32),
        new THREE.MeshBasicMaterial({ color, transparent: true, opacity: 0.72, side: THREE.DoubleSide, depthWrite: false }),
      );
      const other = id === this.#interactionPair.target
        ? current.get(this.#interactionPair.source)
        : current.get(this.#interactionPair.target);
      const own = current.get(id);
      if (other && own) {
        const normal = vector(other.position_m).sub(vector(own.position_m)).normalize();
        ring.quaternion.setFromUnitVectors(new THREE.Vector3(0, 0, 1), normal);
      }
      ring.position.copy(centre);
      ring.userData.overlay = "occlusion";
      ring.name = `${id}-channel-${channel}`;
      this.#root.add(ring);
    };
    const byTargetChannel = new Map();
    const bySourceChannel = new Map();
    for (const interaction of selected) {
      byTargetChannel.set(interaction.target_channel, interaction.target_centre_m);
      bySourceChannel.set(interaction.source_channel, interaction.source_centre_m);
    }
    for (const [channel, centre] of byTargetChannel) {
      addSection(this.#interactionPair.target, channel, centre, 0x54d3c2);
    }
    for (const [channel, centre] of bySourceChannel) {
      addSection(this.#interactionPair.source, channel, centre, 0xf4be58);
    }
  }

  #bindControls() {
    this.#canvas.addEventListener("pointerdown", (event) => {
      this.#drag = { x: event.clientX, y: event.clientY, button: event.button };
      this.#canvas.setPointerCapture(event.pointerId);
    });
    this.#canvas.addEventListener("pointermove", (event) => {
      if (!this.#drag) return;
      const dx = event.clientX - this.#drag.x;
      const dy = event.clientY - this.#drag.y;
      this.#drag.x = event.clientX; this.#drag.y = event.clientY;
      if (this.#drag.button === 0) {
        this.#orbit.yaw -= dx * 0.006;
        this.#orbit.pitch = Math.max(-1.48, Math.min(1.48, this.#orbit.pitch + dy * 0.006));
      } else {
        this.#orbit.target.x -= dx * 0.005;
        this.#orbit.target.y += dy * 0.005;
      }
    });
    this.#canvas.addEventListener("pointerup", () => { this.#drag = null; });
    this.#canvas.addEventListener("wheel", (event) => {
      event.preventDefault();
      this.#orbit.distance = Math.max(1, Math.min(80, this.#orbit.distance * Math.exp(event.deltaY * 0.001)));
    }, { passive: false });
  }

  #render = () => {
    const { yaw, pitch, distance, target } = this.#orbit;
    this.#camera.position.set(
      target.x + distance * Math.cos(pitch) * Math.cos(yaw),
      target.y + distance * Math.sin(pitch),
      target.z + distance * Math.cos(pitch) * Math.sin(yaw),
    );
    this.#camera.lookAt(target);
    this.#renderer.render(this.#scene, this.#camera);
    requestAnimationFrame(this.#render);
  };
}
