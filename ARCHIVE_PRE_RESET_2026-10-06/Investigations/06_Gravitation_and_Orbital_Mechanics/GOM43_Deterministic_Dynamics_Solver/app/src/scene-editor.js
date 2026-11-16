import * as THREE from "../vendor/three.module.js";
import { applyLayoutVelocities, computeBarycentre } from "./layout-velocity.js";

const HANDLE = {
  body: "edit-body",
  radius: "edit-radius",
  angle: "edit-angle",
  vector: "edit-vector",
  velocity: "edit-velocity",
};

function vector(values) {
  return new THREE.Vector3(values[0], values[1], values[2]);
}

function toArray(vec) {
  return [vec.x, vec.y, vec.z];
}

function addArray(a, b) {
  return [a[0] + b[0], a[1] + b[1], a[2] + b[2]];
}

function disposeObject(object) {
  object.traverse((child) => {
    child.geometry?.dispose();
    if (Array.isArray(child.material)) child.material.forEach((material) => material.dispose());
    else child.material?.dispose();
  });
}

export class SceneLayoutEditor {
  #root;
  #group;
  #cameraProvider;
  #canvas;
  #scale = 1;
  #case = null;
  #bodies = [];
  #selectedId = "";
  #visible = true;
  #callbacks;
  #raycaster = new THREE.Raycaster();
  #pointer = new THREE.Vector2();
  #drag = null;
  #orbitNormal = new THREE.Vector3(0, 0, 1);
  #velocities = new Map();

  constructor(root, cameraProvider, canvas, callbacks) {
    this.#root = root;
    this.#cameraProvider = cameraProvider;
    this.#canvas = canvas;
    this.#callbacks = callbacks;
    this.#group = new THREE.Group();
    this.#group.name = "layout-editor";
    this.#root.add(this.#group);
  }

  get group() {
    return this.#group;
  }

  setCase(caseDefinition, scale, selectedId = "") {
    this.#case = caseDefinition;
    this.#scale = scale;
    this.#selectedId = selectedId;
    this.#bodies = caseDefinition?.bodies ?? [];
    this.#rebuild();
  }

  setSelectedId(id) {
    this.#selectedId = id;
    this.#updateSelectionHighlight();
  }

  setVisible(visible) {
    this.#visible = Boolean(visible);
    this.#group.visible = this.#visible;
  }

  get visible() {
    return this.#visible;
  }

  isDragging() {
    return Boolean(this.#drag);
  }

  destroy() {
    disposeObject(this.#group);
    this.#group.removeFromParent();
  }

  updateEntityPositions(getEntity) {
    for (const body of this.#bodies) {
      const object = getEntity(body.id);
      if (!object) continue;
      object.position.copy(vector(body.position_m).multiplyScalar(this.#scale));
    }
  }

  #updatePointer(event) {
    const rect = this.#canvas.getBoundingClientRect();
    this.#pointer.x = ((event.clientX - rect.left) / rect.width) * 2 - 1;
    this.#pointer.y = -((event.clientY - rect.top) / rect.height) * 2 + 1;
  }

  #pick(event) {
    if (!this.#visible || !this.#bodies.length) return null;
    this.#updatePointer(event);
    this.#raycaster.setFromCamera(this.#pointer, this.#cameraProvider());
    return this.#raycaster.intersectObjects(this.#group.children, true)
      .filter(({ object }) => object.userData.editKind)
      .sort((a, b) => a.distance - b.distance)[0] ?? null;
  }

  tryPointerDown(event) {
    if (!this.#visible || event.button !== 0) return false;
    const hit = this.#pick(event);
    if (!hit) return false;
    event.preventDefault();
    const bodyId = hit.object.userData.bodyId;
    const kind = hit.object.userData.editKind;
    if (bodyId && bodyId !== this.#selectedId) {
      this.#selectedId = bodyId;
      this.#callbacks.onSelect?.(bodyId);
      this.#updateSelectionHighlight();
    }
    const body = this.#bodies.find(({ id }) => id === bodyId);
    if (!body) return false;
    this.#callbacks.onEditBegin?.();
    const world = vector(body.position_m).multiplyScalar(this.#scale);
    const planeNormal = new THREE.Vector3();
    this.#cameraProvider().getWorldDirection(planeNormal);
    const plane = new THREE.Plane().setFromNormalAndCoplanarPoint(planeNormal, world);
    const com = vector(computeBarycentre(this.#bodies)).multiplyScalar(this.#scale);
    const comArray = computeBarycentre(this.#bodies);
    this.#drag = {
      kind,
      bodyId,
      pointerId: event.pointerId,
      moved: false,
      plane,
      com,
      startClient: { x: event.clientX, y: event.clientY },
      startPosition: vector(body.position_m),
      startRadius: body.radius_m,
      startDistance: Math.hypot(
        body.position_m[0] - comArray[0],
        body.position_m[1] - comArray[1],
        body.position_m[2] - comArray[2],
      ),
    };
    return true;
  }

  pointerMove(event) {
    if (!this.#drag || event.pointerId !== this.#drag.pointerId) return;
    const body = this.#bodies.find(({ id }) => id === this.#drag.bodyId);
    if (!body) return;
    if (Math.hypot(event.clientX - this.#drag.startClient.x, event.clientY - this.#drag.startClient.y) > 3) {
      this.#drag.moved = true;
    }
    this.#updatePointer(event);
    const com = vector(computeBarycentre(this.#bodies));

    if (this.#drag.kind === HANDLE.radius) {
      const currentWorld = vector(body.position_m).multiplyScalar(this.#scale);
      const hit = new THREE.Vector3();
      this.#raycaster.setFromCamera(this.#pointer, this.#cameraProvider());
      if (!this.#raycaster.ray.intersectPlane(this.#drag.plane, hit)) return;
      const delta = hit.distanceTo(currentWorld);
      const metersPerPixel = this.#drag.startRadius / Math.max(this.#visualRadius(body.radius_m), 0.04);
      body.radius_m = Math.max(0.5, this.#drag.startRadius + delta * metersPerPixel);
      body.collision_radius_m = body.radius_m;
      this.#syncLayout("radius");
      return;
    }

    if (this.#drag.kind === HANDLE.angle) {
      const hit = new THREE.Vector3();
      this.#raycaster.setFromCamera(this.#pointer, this.#cameraProvider());
      const orbitPlane = new THREE.Plane().setFromNormalAndCoplanarPoint(this.#orbitNormal, this.#drag.com);
      if (!this.#raycaster.ray.intersectPlane(orbitPlane, hit)) return;
      const relative = hit.sub(this.#drag.com);
      const radius = this.#drag.startDistance;
      if (radius <= 0) return;
      relative.normalize().multiplyScalar(radius / this.#scale);
      body.position_m = addArray(toArray(com), toArray(relative));
      this.#syncLayout("angle");
      return;
    }

    const hit = new THREE.Vector3();
    this.#raycaster.setFromCamera(this.#pointer, this.#cameraProvider());
    if (!this.#raycaster.ray.intersectPlane(this.#drag.plane, hit)) return;
    const next = hit.divideScalar(this.#scale);
    body.position_m = [next.x, next.y, next.z];
    this.#syncLayout(this.#drag.kind === HANDLE.velocity ? "velocity" : "position");
  }

  pointerUp(event) {
    if (!this.#drag || event.pointerId !== this.#drag.pointerId) return false;
    const { kind, moved } = this.#drag;
    this.#drag = null;
    if (moved) this.#callbacks.onLayoutCommit?.(kind);
    return moved;
  }

  #syncLayout(kind) {
    applyLayoutVelocities(this.#bodies, { orbitNormal: toArray(this.#orbitNormal) });
    this.#rebuild();
    this.#callbacks.onLayoutChange?.(this.#bodies, kind);
  }

  #visualRadius(radius_m) {
    return Math.max(0.055, Math.min(0.28, (radius_m ?? 1) * this.#scale));
  }

  #rebuild() {
    disposeObject(this.#group);
    this.#group.clear();
    if (!this.#case || this.#case.problem_class === "articulated_rigid" || !this.#bodies.length) return;

    const velocities = applyLayoutVelocities(this.#bodies, { orbitNormal: toArray(this.#orbitNormal) });
    this.#velocities = new Map(this.#bodies.map((body, index) => [body.id, velocities[index]]));

    const com = computeBarycentre(this.#bodies);
    const comWorld = vector(com).multiplyScalar(this.#scale);

    for (const [index, body] of this.#bodies.entries()) {
      const position = vector(body.position_m).multiplyScalar(this.#scale);
      const relative = position.clone().sub(comWorld);
      const orbitRadius = relative.length();

      const vectorLine = new THREE.Line(
        new THREE.BufferGeometry().setFromPoints([comWorld, position]),
        new THREE.LineBasicMaterial({ color: 0x6aa7ff, transparent: true, opacity: 0.75 }),
      );
      vectorLine.userData.editKind = HANDLE.vector;
      vectorLine.userData.bodyId = body.id;
      this.#group.add(vectorLine);

      const vectorTip = new THREE.Mesh(
        new THREE.SphereGeometry(0.055, 12, 10),
        new THREE.MeshBasicMaterial({ color: 0x6aa7ff }),
      );
      vectorTip.position.copy(position);
      vectorTip.userData.editKind = HANDLE.vector;
      vectorTip.userData.bodyId = body.id;
      this.#group.add(vectorTip);

      if (orbitRadius > 0.08) {
        const ring = new THREE.Mesh(
          new THREE.TorusGeometry(orbitRadius, 0.008, 8, 96),
          new THREE.MeshBasicMaterial({
            color: 0xcf8cff,
            transparent: true,
            opacity: body.id === this.#selectedId ? 0.85 : 0.35,
          }),
        );
        ring.position.copy(comWorld);
        ring.quaternion.setFromUnitVectors(new THREE.Vector3(0, 0, 1), this.#orbitNormal);
        ring.userData.editKind = HANDLE.angle;
        ring.userData.bodyId = body.id;
        this.#group.add(ring);
      }

      const visual = this.#visualRadius(body.radius_m);
      const radiusHandle = new THREE.Mesh(
        new THREE.SphereGeometry(0.05, 12, 10),
        new THREE.MeshBasicMaterial({ color: 0xf4be58 }),
      );
      radiusHandle.position.copy(position.clone().add(new THREE.Vector3(visual, 0, 0)));
      radiusHandle.userData.editKind = HANDLE.radius;
      radiusHandle.userData.bodyId = body.id;
      this.#group.add(radiusHandle);

      const velocity = this.#velocities.get(body.id) ?? body.velocity_m_s;
      const speed = Math.hypot(...velocity);
      if (speed > 0) {
        const direction = vector(velocity).normalize();
        const arrowLength = Math.min(1.4, Math.max(0.2, Math.log10(1 + speed) * 0.15));
        const arrow = new THREE.ArrowHelper(direction, position, arrowLength, 0x8cb4ff, 0.09, 0.05);
        arrow.userData.editKind = HANDLE.velocity;
        arrow.userData.bodyId = body.id;
        arrow.line.material.transparent = true;
        arrow.line.material.opacity = 0.85;
        this.#group.add(arrow);

        const velocityTip = new THREE.Mesh(
          new THREE.SphereGeometry(0.045, 10, 8),
          new THREE.MeshBasicMaterial({ color: 0x8cb4ff }),
        );
        velocityTip.position.copy(position.clone().addScaledVector(direction, arrowLength));
        velocityTip.userData.editKind = HANDLE.velocity;
        velocityTip.userData.bodyId = body.id;
        this.#group.add(velocityTip);
      }

      const pickShell = new THREE.Mesh(
        new THREE.SphereGeometry(Math.max(visual, 0.08), 16, 12),
        new THREE.MeshBasicMaterial({
          color: index % 2 === 0 ? 0x54d3c2 : 0x8cb4ff,
          transparent: true,
          opacity: body.id === this.#selectedId ? 0.18 : 0.05,
          depthWrite: false,
        }),
      );
      pickShell.position.copy(position);
      pickShell.userData.editKind = HANDLE.body;
      pickShell.userData.bodyId = body.id;
      this.#group.add(pickShell);
    }
    this.#updateSelectionHighlight();
  }

  #updateSelectionHighlight() {
    for (const child of this.#group.children) {
      if (child.material?.opacity !== undefined && child.userData.editKind === HANDLE.body) {
        child.material.opacity = child.userData.bodyId === this.#selectedId ? 0.18 : 0.05;
      }
      if (child.material?.opacity !== undefined && child.userData.editKind === HANDLE.angle) {
        child.material.opacity = child.userData.bodyId === this.#selectedId ? 0.85 : 0.35;
      }
    }
  }
}
