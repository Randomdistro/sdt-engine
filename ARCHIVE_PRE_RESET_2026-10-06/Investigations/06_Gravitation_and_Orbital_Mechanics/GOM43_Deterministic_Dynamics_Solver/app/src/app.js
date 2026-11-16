import { createEntity, createMinimalCase, createPreset } from "./cases.js";
import {
  caseFromLocationHash, downloadText, encodeSharePayload, parseCaseJson,
  resultToCsv, validateCase,
} from "./case-io.js";
import { buildDiagnosticSeries, drawDiagnosticChart, formatMetric } from "./diagnostics.js";
import { applyLayoutVelocitiesToCase } from "./layout-velocity.js";
import { DynamicsRenderer } from "./renderer.js";
import { SolverWorkerClient } from "./worker-client.js";

const $ = (selector) => document.querySelector(selector);
const $$ = (selector) => [...document.querySelectorAll(selector)];

const elements = {
  solverLamp: $("#solverLamp"), solverStatus: $("#solverStatus"), solverBuild: $("#solverBuild"),
  runButton: $("#runButton"), cancelButton: $("#cancelButton"), runProgress: $("#runProgress"),
  presetSelect: $("#presetSelect"), importInput: $("#importInput"), sceneTree: $("#sceneTree"),
  inspector: $("#entityInspector"), removeEntityButton: $("#removeEntityButton"),
  referenceBody: $("#referenceBody"), viewportEmpty: $("#viewportEmpty"),
  timeline: $("#timelineSlider"), playButton: $("#playButton"), timeReadout: $("#timeReadout"),
  eventMarkers: $("#eventMarkers"), classification: $("#classificationBanner"),
  metricCards: $("#metricCards"), chartMetric: $("#chartMetric"), chart: $("#diagnosticChart"),
  chartName: $("#chartName"), chartValue: $("#chartValue"), gateList: $("#gateList"),
  eventList: $("#eventList"), caseForm: $("#caseForm"), rawPanel: $("#rawEditorPanel"),
  rawEditor: $("#rawCaseEditor"), validation: $("#caseValidation"), resultJson: $("#resultJson"),
  provenance: $("#provenanceList"), exportResult: $("#exportResultButton"),
  exportCsv: $("#exportCsvButton"), toast: $("#toast"),
  chunkSteps: $("#chunkStepsInput"), pairSelector: $("#pairSelector"), pairMatrix: $("#pairMatrix"),
  checkpointButton: $("#checkpointButton"), resumeButton: $("#resumeButton"), resumeInput: $("#resumeInput"),
};

const state = {
  caseDefinition: createPreset("circular-pair"),
  result: null,
  diagnosticSeries: {},
  selected: null,
  frameIndex: 0,
  running: false,
  playing: false,
  playbackStartedAt: 0,
  playbackStartFrame: 0,
  toastTimer: 0,
  sessionStarted: false,
  layoutRunTimer: 0,
};

let renderer;
try {
  renderer = new DynamicsRenderer($("#sceneCanvas"));
  document.documentElement.dataset.renderer = `${renderer.startupInfo.renderer}-${renderer.startupInfo.revision}`;
} catch (error) {
  elements.viewportEmpty.innerHTML = `<strong>Renderer unavailable</strong><span></span>`;
  elements.viewportEmpty.querySelector("span").textContent = error.message;
}

const worker = new SolverWorkerClient();
worker.addEventListener("status", ({ detail }) => {
  setSolverState("running", detail.phase.replaceAll("-", " "));
  setProgress(detail.progress);
});
worker.addEventListener("cancelled", () => {
  setSolverState("pending", "Worker stopped; ready to reinitialize.");
});

function toast(message, error = false) {
  clearTimeout(state.toastTimer);
  elements.toast.textContent = message;
  elements.toast.className = `toast show${error ? " error" : ""}`;
  state.toastTimer = setTimeout(() => { elements.toast.className = "toast"; }, 3500);
}

function setSolverState(kind, message, build = "") {
  elements.solverLamp.className = `state-lamp ${kind}`;
  elements.solverStatus.textContent = message;
  if (build) elements.solverBuild.textContent = build;
}

function setProgress(value) {
  elements.runProgress.classList.toggle("indeterminate", value === null);
  elements.runProgress.style.width = value === null ? "" : `${value ?? 0}%`;
}

function currentEntities() {
  return ["point_nbody", "sdt_occlusion_nbody"].includes(state.caseDefinition.problem_class)
    ? [{ kind: "body", label: "Bodies", values: state.caseDefinition.bodies ?? [] }]
    : [
      { kind: "link", label: "Rigid links", values: state.caseDefinition.links ?? [] },
      { kind: "joint", label: "Revolute joints", values: state.caseDefinition.joints ?? [] },
    ];
}

function getSelectedEntity() {
  if (!state.selected) return null;
  const group = currentEntities().find(({ kind }) => kind === state.selected.kind);
  return group?.values.find(({ id }) => id === state.selected.id) ?? null;
}

function invalidateResult() {
  state.result = null;
  state.diagnosticSeries = {};
  state.frameIndex = 0;
  state.playing = false;
  state.sessionStarted = false;
  renderer?.setResult(null);
  renderer?.setCaseDefinition(state.caseDefinition, { selectedId: state.selected?.id ?? "" });
  renderer?.setEditVisible(true);
  elements.viewportEmpty.classList.add("hidden");
  $("#editHint")?.classList.remove("hidden");
  elements.timeline.disabled = true;
  elements.timeline.max = "0";
  elements.timeline.value = "0";
  elements.playButton.disabled = true;
  elements.exportResult.disabled = true;
  elements.exportCsv.disabled = true;
  elements.checkpointButton.disabled = true;
  elements.resultJson.textContent = "No result loaded.";
  renderResultSummary();
  drawChart();
}

function caseChanged({ preserveSelection = true } = {}) {
  if (!preserveSelection) state.selected = null;
  invalidateResult();
  renderCase();
}

function renderCase() {
  applyLayoutVelocitiesToCase(state.caseDefinition);
  renderSceneTree();
  renderInspector();
  renderCaseForm();
  elements.rawEditor.value = JSON.stringify(state.caseDefinition, null, 2);
  renderValidation();
  renderReferenceOptions();
  renderer?.setCaseDefinition(state.caseDefinition, { selectedId: state.selected?.id ?? "" });
  if (!state.result) $("#editHint")?.classList.remove("hidden");
}

function renderSceneTree() {
  elements.sceneTree.replaceChildren();
  for (const group of currentEntities()) {
    const section = document.createElement("div");
    section.className = "tree-group";
    const heading = document.createElement("div");
    heading.className = "tree-group-title";
    heading.textContent = `${group.label} · ${group.values.length}`;
    section.append(heading);
    for (const entity of group.values) {
      const button = document.createElement("button");
      button.type = "button";
      button.className = `tree-item${state.selected?.kind === group.kind && state.selected.id === entity.id ? " selected" : ""}`;
      button.setAttribute("role", "treeitem");
      button.innerHTML = `<span class="tree-icon ${group.kind}"></span><span></span>`;
      button.lastElementChild.textContent = entity.id;
      button.addEventListener("click", () => {
        state.selected = { kind: group.kind, id: entity.id };
        renderSceneTree();
        renderInspector();
        renderer?.setEditorSelection(entity.id);
      });
      section.append(button);
    }
    elements.sceneTree.append(section);
  }
}

function inspectorField(labelText, key, value, options = null) {
  const label = document.createElement("label");
  label.textContent = labelText;
  let input;
  if (options) {
    input = document.createElement("select");
    for (const { value: optionValue, label: optionLabel } of options) {
      const option = document.createElement("option");
      option.value = optionValue ?? "";
      option.textContent = optionLabel;
      option.selected = (value ?? "") === optionValue;
      input.append(option);
    }
  } else {
    input = document.createElement("input");
    input.value = value;
    if (typeof value === "number") { input.type = "number"; input.step = "any"; }
  }
  input.dataset.key = key;
  label.append(input);
  return label;
}

function vectorField(labelText, key, values) {
  const label = document.createElement("label");
  label.textContent = labelText;
  const row = document.createElement("div");
  row.className = "vector-fields";
  values.forEach((value, index) => {
    const input = document.createElement("input");
    input.type = "number";
    input.step = "any";
    input.value = value;
    input.dataset.key = key;
    input.dataset.index = String(index);
    input.setAttribute("aria-label", `${labelText} ${["x", "y", "z", "w"][index] ?? index}`);
    row.append(input);
  });
  label.append(row);
  return label;
}

function renderInspector() {
  elements.inspector.replaceChildren();
  const entity = getSelectedEntity();
  elements.removeEntityButton.disabled = !entity;
  if (!entity) {
    const message = document.createElement("p");
    message.className = "muted";
    message.textContent = "Select an entity to inspect its solver inputs.";
    elements.inspector.append(message);
    return;
  }
  elements.inspector.append(inspectorField("ID", "id", entity.id));
  const occlusion = state.caseDefinition.problem_class === "sdt_occlusion_nbody";
  const vectorKeys = {
    position_m: "Position (m)",
    ...(occlusion ? {} : { velocity_m_s: "Velocity (m/s)" }),
    quaternion_wxyz: "Quaternion (w,x,y,z)", angular_velocity_rad_s: "Angular velocity (rad/s)",
    inertia_diagonal_kg_m2: "Inertia diagonal (kg·m²)", parent_anchor_m: "Parent anchor (m)",
    child_anchor_m: "Child anchor (m)", axis_world: "World hinge axis",
  };
  for (const [key, label] of Object.entries(vectorKeys)) {
    if (Array.isArray(entity[key])) elements.inspector.append(vectorField(label, key, entity[key]));
  }
  if (occlusion && Array.isArray(entity.velocity_m_s)) {
    elements.inspector.append(readOnlyVectorField("Velocity (m/s, computed)", entity.velocity_m_s));
  }
  const scalarKeys = {
    koppa_m: "Koppa (m)", collision_radius_m: "Collision radius (m)",
    baryon_count: "Exact baryon count", radius_m: "Physical radius (m)",
    inertial_mass_kg: "Inertial mass (kg)", length_m: "Length (m)",
  };
  for (const [key, label] of Object.entries(scalarKeys)) {
    if (key in entity) elements.inspector.append(inspectorField(label, key, entity[key]));
  }
  if (state.selected.kind === "joint") {
    const linkOptions = [
      { value: null, label: "Fixed world" },
      ...(state.caseDefinition.links ?? []).map(({ id }) => ({ value: id, label: id })),
    ];
    elements.inspector.append(inspectorField("Parent", "parent", entity.parent, linkOptions));
    elements.inspector.append(inspectorField("Child", "child", entity.child, linkOptions.slice(1)));
  }
}

function readOnlyVectorField(labelText, values) {
  const label = document.createElement("label");
  label.textContent = labelText;
  const row = document.createElement("div");
  row.className = "vector-fields computed";
  values.forEach((value) => {
    const output = document.createElement("output");
    output.className = "mono";
    output.textContent = value;
    row.append(output);
  });
  label.append(row);
  return label;
}

function inspectorChange(event) {
  const entity = getSelectedEntity();
  const input = event.target.closest("[data-key]");
  if (!entity || !input) return;
  const key = input.dataset.key;
  const previousId = entity.id;
  let value = input.type === "number" ? Number(input.value) : input.value;
  if (key === "parent" && value === "") value = null;
  if (input.dataset.index !== undefined) entity[key][Number(input.dataset.index)] = value;
  else entity[key] = value;
  if (key === "id" && state.selected) {
    state.selected.id = value;
    if (state.selected.kind === "link") {
      for (const joint of state.caseDefinition.joints ?? []) {
        if (joint.parent === previousId) joint.parent = value;
        if (joint.child === previousId) joint.child = value;
      }
    }
  }
  if (["position_m", "radius_m", "collision_radius_m", "koppa_m", "baryon_count"].includes(key)) {
    applyLayoutVelocitiesToCase(state.caseDefinition);
  }
  caseChanged();
}

const formBindings = [
  ["#caseIdInput", "case_id", String],
  ["#problemClassInput", "problem_class", String],
  ["#integratorInput", "integrator", String],
  ["#timestepInput", "timestep_s", Number],
  ["#durationInput", "duration_s", Number],
  ["#recordEveryInput", "record_every_steps", Number],
];
const toleranceBindings = [
  ["#positionToleranceInput", "position_m", Number],
  ["#velocityToleranceInput", "velocity_m_s", Number],
  ["#quaternionToleranceInput", "quaternion_norm", Number],
  ["#constraintIterationsInput", "max_constraint_iterations", Number],
  ["#retardedToleranceInput", "retarded_time_s", Number],
  ["#retardedIterationsInput", "max_retarded_iterations", Number],
];

function renderCaseForm() {
  for (const [selector, key] of formBindings) $(selector).value = state.caseDefinition[key];
  for (const [selector, key] of toleranceBindings) {
    const input = $(selector);
    const value = state.caseDefinition.tolerances?.[key];
    input.value = value ?? "";
    input.disabled = value === undefined;
  }
}

function renderValidation() {
  const validation = validateCase(state.caseDefinition);
  elements.validation.className = `validation ${validation.valid ? "valid" : "invalid"}`;
  elements.validation.textContent = validation.valid
    ? `Dimensionally valid · ${validation.steps.toLocaleString()} fixed steps · ${Math.ceil((validation.steps + 1) / state.caseDefinition.record_every_steps).toLocaleString()} recorded frames maximum.`
    : validation.errors.join(" ");
  elements.runButton.disabled = !validation.valid || state.running;
  return validation;
}

function renderReferenceOptions() {
  const previous = elements.referenceBody.value;
  elements.referenceBody.replaceChildren();
  for (const group of currentEntities().filter(({ kind }) => kind !== "joint")) {
    for (const entity of group.values) {
      const option = document.createElement("option");
      option.value = entity.id;
      option.textContent = entity.id;
      elements.referenceBody.append(option);
    }
  }
  if ([...elements.referenceBody.options].some(({ value }) => value === previous)) elements.referenceBody.value = previous;
}

function loadCase(caseDefinition, message = "") {
  state.caseDefinition = structuredClone(caseDefinition);
  state.selected = null;
  caseChanged({ preserveSelection: false });
  if (message) toast(message);
}

function startPlayback() {
  const frames = state.result?.trajectory ?? [];
  if (frames.length < 2) return;
  state.playing = true;
  renderer?.setEditVisible(false);
  setFrame(0);
  state.playbackStartedAt = performance.now();
  state.playbackStartFrame = 0;
  renderTimeline();
  requestAnimationFrame(playbackTick);
}

async function runCase({ full = false, autoplay = false } = {}) {
  const validation = renderValidation();
  if (!validation.valid || state.running) return;
  state.running = true;
  state.playing = false;
  elements.runButton.disabled = true;
  elements.cancelButton.disabled = false;
  setSolverState(
    "running",
    full
      ? "Executing the full declared case in WebAssembly…"
      : "Executing declared fixed steps in WebAssembly worker…",
  );
  setProgress(null);
  try {
    const chunkSteps = Math.max(1, Math.floor(Number(elements.chunkSteps.value) || 1));
    const continuing = !full
      && state.sessionStarted
      && state.result?.status === "running";
    const result = continuing
      ? await worker.advance(chunkSteps)
      : await worker.run(state.caseDefinition, { steps: chunkSteps, full });
    if (!["1.0.0", "3.0.0"].includes(result.contract_version) || !Array.isArray(result.trajectory)) {
      throw new Error("Solver returned an incompatible result contract.");
    }
    state.sessionStarted = result.contract_version === "3.0.0" && result.status === "running";
    elements.checkpointButton.disabled = !state.sessionStarted;
    state.result = result;
    state.diagnosticSeries = buildDiagnosticSeries(result);
    state.frameIndex = 0;
    renderer?.setResult(result);
    renderCompletedResult();
    const allPassed = (result.gates ?? []).every(({ passed }) => passed);
    setSolverState(["completed", "running"].includes(result.status) ? "ready" : "error", `${result.status}: ${result.message}`);
    setProgress(result.status === "running" ? null : 100);
    elements.runButton.textContent = result.status === "running" ? "Continue chunk" : "Run chunk";
    if (autoplay && result.trajectory.length > 1) startPlayback();
    toast(`Run ${result.status}; ${allPassed ? "all evaluated gates passed" : "one or more gates failed"}.`, !allPassed || !["completed", "running"].includes(result.status));
  } catch (error) {
    if (error.name !== "AbortError") {
      setSolverState("error", `Solver worker error: ${error.message}`);
      toast(error.message, true);
    }
  } finally {
    state.running = false;
    elements.cancelButton.disabled = true;
    renderValidation();
  }
}

async function loadPresetAndPlay(name, message = "Preset loaded; motion running.") {
  loadCase(createPreset(name), message);
  await runCase({ full: true, autoplay: true });
}

function renderCompletedResult() {
  const frames = state.result.trajectory;
  elements.viewportEmpty.classList.add("hidden");
  renderer?.setEditVisible(false);
  $("#editHint")?.classList.add("hidden");
  elements.timeline.disabled = frames.length < 2;
  elements.timeline.max = String(Math.max(0, frames.length - 1));
  elements.timeline.value = "0";
  elements.playButton.disabled = frames.length < 2;
  elements.exportResult.disabled = false;
  elements.exportCsv.disabled = frames.length === 0;
  elements.resultJson.textContent = JSON.stringify(state.result, null, 2);
  renderResultSummary();
  renderPairMatrix();
  renderEvents();
  renderTimeline();
  drawChart();
}

function renderResultSummary() {
  const result = state.result;
  if (!result) {
    elements.classification.className = "classification not-executed";
    elements.classification.innerHTML = "<strong>NOT-EXECUTED</strong><span>No solver result is loaded.</span>";
    elements.metricCards.replaceChildren();
    elements.gateList.innerHTML = '<p class="muted">Run a case to evaluate gates.</p>';
    elements.provenance.innerHTML = "<div><dt>Status</dt><dd>Not executed</dd></div>";
    return;
  }
  const className = result.classification === "NOT-EXECUTED"
    ? "not-executed"
    : result.classification.toLowerCase();
  elements.classification.className = `classification ${className}`;
  elements.classification.innerHTML = "<strong></strong><span></span>";
  elements.classification.querySelector("strong").textContent = result.classification;
  elements.classification.querySelector("span").textContent = result.message;
  const metrics = result.contract_version === "3.0.0"
    ? {
      "Retarded residual": result.diagnostics.maximum_retarded_residual_s,
      "Resistance ratio": result.diagnostics.maximum_resistance_ratio,
      "Shield fraction": result.diagnostics.maximum_shield_fraction,
      "Speed / c": result.diagnostics.maximum_speed_fraction_c,
      "Medium closure": result.diagnostics.medium_closure_relative,
      "49 matrices": (result.interactions?.length ?? 0) / 49,
    }
    : {
      "Energy drift": result.diagnostics.relative_energy_drift,
      "Momentum drift": result.diagnostics.momentum_drift,
      "Angular drift": result.diagnostics.angular_momentum_drift,
      "Position residual": result.diagnostics.max_position_constraint_m,
      "Velocity residual": result.diagnostics.max_velocity_constraint_m_s,
      "Quaternion error": result.diagnostics.max_quaternion_norm_error,
    };
  elements.metricCards.replaceChildren();
  for (const [label, value] of Object.entries(metrics)) {
    const card = document.createElement("dl");
    card.className = "metric-card";
    card.innerHTML = "<dt></dt><dd></dd>";
    card.querySelector("dt").textContent = label;
    card.querySelector("dd").textContent = formatMetric(value);
    elements.metricCards.append(card);
  }
  elements.gateList.replaceChildren();
  if (!result.gates.length) elements.gateList.innerHTML = '<p class="muted">No pre-registered gates in this case.</p>';
  for (const gate of result.gates) {
    const row = document.createElement("div");
    row.className = `gate ${gate.passed ? "pass" : "fail"}`;
    row.innerHTML = '<span class="gate-status"></span><div><strong></strong><small></small></div><span class="mono"></span>';
    row.querySelector(".gate-status").textContent = gate.passed ? "✓" : "×";
    row.querySelector("strong").textContent = gate.id;
    row.querySelector("small").textContent = gate.metric
      ? `${gate.metric} ${gate.relation} ${formatMetric(gate.limit)}`
      : "registered GOM43-E gate";
    row.lastElementChild.textContent = formatMetric(gate.value);
    elements.gateList.append(row);
  }
  const provenance = [
    ["Status", result.status], ["Classification", result.classification],
    ["Build", result.solver.build_id], ["Compiler", result.solver.compiler],
    ["Contract", result.contract_version], ["Executed steps", result.executed_steps.toLocaleString()],
    ["Input SHA-256", result.provenance.input_sha256], ["Laws SHA-256", result.provenance.laws_sha256],
    ["Trajectory SHA-256", result.trajectory_sha256], ["Floating-point", result.solver.floating_point_policy],
  ];
  elements.provenance.replaceChildren();
  for (const [term, description] of provenance) {
    const row = document.createElement("div");
    row.innerHTML = "<dt></dt><dd></dd>";
    row.querySelector("dt").textContent = term;
    row.querySelector("dd").textContent = description;
    elements.provenance.append(row);
  }
}

function renderPairMatrix() {
  const interactions = state.result?.interactions ?? [];
  elements.pairSelector.replaceChildren();
  if (!interactions.length) {
    elements.pairMatrix.innerHTML = '<p class="muted">Run an occlusion case to inspect its 49 channel relations.</p>';
    renderer?.setInteractionPair("", "");
    return;
  }
  const keys = [...new Set(interactions.map(({ target, source }) => `${target}\u0000${source}`))];
  const previous = elements.pairSelector.value;
  for (const key of keys) {
    const [target, source] = key.split("\u0000");
    const option = document.createElement("option");
    option.value = key;
    option.textContent = `${target} ← ${source}`;
    elements.pairSelector.append(option);
  }
  elements.pairSelector.value = keys.includes(previous) ? previous : keys[0];
  const [target, source] = elements.pairSelector.value.split("\u0000");
  const selected = interactions
    .filter((entry) => entry.target === target && entry.source === source)
    .sort((left, right) => left.target_channel - right.target_channel || left.source_channel - right.source_channel);
  elements.pairMatrix.replaceChildren();
  for (const entry of selected) {
    const cell = document.createElement("div");
    cell.className = "pair-cell";
    const visible = entry.raw_solid_angle_sr > 0
      ? entry.visible_solid_angle_sr / entry.raw_solid_angle_sr
      : 0;
    cell.style.setProperty("--depth", String(Math.max(0, Math.min(1, visible))));
    cell.innerHTML = `<strong>T${entry.target_channel}·S${entry.source_channel}</strong><span></span><span></span><small></small>`;
    cell.children[1].textContent = `Ω ${formatMetric(entry.visible_solid_angle_sr)}`;
    cell.children[2].textContent = `shield ${formatMetric(entry.shield_fraction)}`;
    cell.children[3].textContent = `R/3 in R disc · offset ${entry.target_channel === 0 ? "0" : "2R/3"}`;
    elements.pairMatrix.append(cell);
  }
  renderer?.setInteractionPair(target, source);
}

function renderEvents() {
  elements.eventList.replaceChildren();
  elements.eventMarkers.replaceChildren();
  const events = state.result?.events ?? [];
  if (!events.length) {
    const item = document.createElement("li"); item.className = "muted"; item.textContent = "No events recorded."; elements.eventList.append(item);
    return;
  }
  const duration = state.result.normalized_case.duration_s;
  for (const event of events) {
    const item = document.createElement("li");
    const time = document.createElement("time"); time.textContent = `${formatMetric(event.time_s)} s`;
    item.append(time, document.createTextNode(`${event.type}: ${event.detail}`));
    elements.eventList.append(item);
    const marker = document.createElement("i");
    marker.className = "event-marker";
    marker.style.left = `${Math.min(100, 100 * event.time_s / duration)}%`;
    marker.title = `${event.type} at ${event.time_s} s`;
    elements.eventMarkers.append(marker);
  }
}

function setFrame(index) {
  const frames = state.result?.trajectory ?? [];
  if (!frames.length) return;
  state.frameIndex = Math.max(0, Math.min(frames.length - 1, index));
  elements.timeline.value = String(state.frameIndex);
  renderer?.setFrame(state.frameIndex);
  renderTimeline();
  drawChart();
}

function renderTimeline() {
  const frames = state.result?.trajectory ?? [];
  const frame = frames[state.frameIndex];
  elements.timeReadout.textContent = frame
    ? `t = ${formatMetric(frame.time_s)} s · frame ${state.frameIndex + 1}/${frames.length}`
    : "t = 0 s · frame 0/0";
  elements.playButton.textContent = state.playing ? "Pause" : "Play";
}

function drawChart() {
  const series = state.diagnosticSeries[elements.chartMetric.value];
  drawDiagnosticChart(elements.chart, series, state.frameIndex);
  elements.chartName.textContent = series?.name ?? "No trace";
  elements.chartValue.textContent = series ? formatMetric(series.values[state.frameIndex]) : "—";
}

function playbackTick(timestamp) {
  if (!state.playing) return;
  const frames = state.result?.trajectory ?? [];
  const speed = Number($("#playbackSpeed").value);
  const frameDuration = 1000 / (30 * speed);
  const elapsedFrames = Math.floor((timestamp - state.playbackStartedAt) / frameDuration);
  const next = state.playbackStartFrame + elapsedFrames;
  if (next >= frames.length - 1) {
    setFrame(frames.length - 1);
    state.playing = false;
    syncLayoutFromFrame();
    renderer?.syncEditLayout(state.caseDefinition, state.selected?.id ?? "");
    renderTimeline();
    return;
  }
  setFrame(next);
  requestAnimationFrame(playbackTick);
}

function togglePlayback() {
  if (!state.result?.trajectory?.length) return;
  state.playing = !state.playing;
  if (state.playing) {
    renderer?.setEditVisible(false);
    if (state.frameIndex >= state.result.trajectory.length - 1) setFrame(0);
    state.playbackStartedAt = performance.now();
    state.playbackStartFrame = state.frameIndex;
    requestAnimationFrame(playbackTick);
  } else {
    syncLayoutFromFrame();
    renderer?.syncEditLayout(state.caseDefinition, state.selected?.id ?? "");
  }
  renderTimeline();
}

function syncLayoutFromFrame(frameIndex = state.frameIndex) {
  const frame = state.result?.trajectory?.[frameIndex];
  if (!frame) return;
  for (const snapshot of frame.states) {
    const body = state.caseDefinition.bodies?.find(({ id }) => id === snapshot.id);
    if (!body) continue;
    body.position_m = [...snapshot.position_m];
    body.velocity_m_s = [...snapshot.velocity_m_s];
  }
  applyLayoutVelocitiesToCase(state.caseDefinition);
}

function scheduleLayoutRun() {
  clearTimeout(state.layoutRunTimer);
  state.layoutRunTimer = setTimeout(() => {
    if (!validateCase(state.caseDefinition).valid || state.running) return;
    runCase({ full: true, autoplay: true });
  }, 450);
}

function bindRendererEvents() {
  if (!renderer) return;
  renderer.addEventListener("select", ({ detail: { id } }) => {
    state.selected = { kind: "body", id };
    renderSceneTree();
    renderInspector();
    renderer.setEditorSelection(id);
  });
  renderer.addEventListener("editbegin", () => {
    state.playing = false;
    if (state.result) {
      syncLayoutFromFrame();
      invalidateResult();
    }
  });
  renderer.addEventListener("layoutchange", ({ detail: { bodies } }) => {
    if (!state.caseDefinition.bodies) return;
    state.caseDefinition.bodies = bodies;
    applyLayoutVelocitiesToCase(state.caseDefinition);
    renderInspector();
    elements.rawEditor.value = JSON.stringify(state.caseDefinition, null, 2);
    renderValidation();
  });
  renderer.addEventListener("layoutcommit", () => {
    scheduleLayoutRun();
  });
}

function bindEvents() {
  elements.inspector.addEventListener("change", inspectorChange);
  $("#loadPresetButton").addEventListener("click", () => {
    loadPresetAndPlay(elements.presetSelect.value);
  });
  $("#newCaseButton").addEventListener("click", () => loadCase(createMinimalCase(), "New case created."));
  $("#importButton").addEventListener("click", () => elements.importInput.click());
  elements.importInput.addEventListener("change", async () => {
    const file = elements.importInput.files[0];
    if (!file) return;
    try {
      loadCase(parseCaseJson(await file.text()), `Imported ${file.name}.`);
      await runCase({ full: true, autoplay: true });
    } catch (error) { toast(error.message, true); }
    elements.importInput.value = "";
  });
  $("#exportCaseButton").addEventListener("click", () => downloadText(`${state.caseDefinition.case_id}.sdtcase.json`, JSON.stringify(state.caseDefinition, null, 2)));
  $("#shareButton").addEventListener("click", async () => {
    try {
      const payload = encodeSharePayload(state.caseDefinition);
      if (payload.length > 12000) throw new Error("Case is too large for a reliable URL fragment; export the case file instead.");
      const url = new URL(location.href);
      url.hash = `case=${payload}`;
      await navigator.clipboard.writeText(url.href);
      toast("Portable case link copied.");
    } catch (error) { toast(error.message, true); }
  });
  $("#addEntityButton").addEventListener("click", () => {
    if (["point_nbody", "sdt_occlusion_nbody"].includes(state.caseDefinition.problem_class)) {
      const entity = createEntity(state.caseDefinition, "body");
      state.caseDefinition.bodies.push(entity);
      state.selected = { kind: "body", id: entity.id };
    } else {
      const link = createEntity(state.caseDefinition, "link");
      state.caseDefinition.links.push(link);
      const joint = createEntity(state.caseDefinition, "joint");
      state.caseDefinition.joints.push(joint);
      state.selected = { kind: "link", id: link.id };
    }
    caseChanged();
  });
  elements.removeEntityButton.addEventListener("click", () => {
    if (!state.selected) return;
    const { kind, id } = state.selected;
    const key = `${kind}s`;
    state.caseDefinition[key] = state.caseDefinition[key].filter((entity) => entity.id !== id);
    if (kind === "link") state.caseDefinition.joints = state.caseDefinition.joints.filter((joint) => joint.parent !== id && joint.child !== id);
    state.selected = null;
    caseChanged();
  });
  for (const [selector, key, convert] of formBindings) {
    $(selector).addEventListener("change", (event) => {
      if (key === "problem_class") {
        loadCase(event.target.value === "articulated_rigid" ? createPreset("single-pendulum") : createMinimalCase(), "Problem class changed; compatible case structure applied.");
        runCase({ full: true, autoplay: true });
        return;
      }
      state.caseDefinition[key] = convert(event.target.value);
      caseChanged();
    });
  }
  for (const [selector, key, convert] of toleranceBindings) {
    $(selector).addEventListener("change", (event) => {
      state.caseDefinition.tolerances[key] = convert(event.target.value);
      caseChanged();
    });
  }
  $$(".tab").forEach((button) => button.addEventListener("click", () => {
    $$(".tab").forEach((tab) => tab.classList.toggle("active", tab === button));
    $$(".tab-panel").forEach((panel) => panel.classList.toggle("active", panel.id === `${button.dataset.tab}Tab`));
    if (button.dataset.tab === "diagnostics") requestAnimationFrame(drawChart);
  }));
  $$("[data-editor-mode]").forEach((button) => button.addEventListener("click", () => {
    $$("[data-editor-mode]").forEach((item) => item.classList.toggle("active", item === button));
    elements.caseForm.classList.toggle("hidden", button.dataset.editorMode !== "form");
    elements.rawPanel.classList.toggle("hidden", button.dataset.editorMode !== "raw");
    if (button.dataset.editorMode === "raw") elements.rawEditor.value = JSON.stringify(state.caseDefinition, null, 2);
  }));
  $("#formatJsonButton").addEventListener("click", () => {
    try { elements.rawEditor.value = JSON.stringify(JSON.parse(elements.rawEditor.value), null, 2); }
    catch (error) { toast(`Malformed JSON: ${error.message}`, true); }
  });
  $("#applyJsonButton").addEventListener("click", () => {
    try { loadCase(parseCaseJson(elements.rawEditor.value), "Raw case validated and applied."); }
    catch (error) { elements.validation.className = "validation invalid"; elements.validation.textContent = error.message; }
  });
  elements.runButton.addEventListener("click", () => runCase());
  elements.cancelButton.addEventListener("click", () => {
    worker.cancel();
    state.running = false;
    elements.cancelButton.disabled = true;
    setProgress(0);
    renderValidation();
    state.sessionStarted = false;
    elements.checkpointButton.disabled = true;
    elements.runButton.textContent = "Run chunk";
    toast("Run paused; worker memory was discarded.");
  });
  elements.checkpointButton.addEventListener("click", async () => {
    try {
      const checkpoint = await worker.checkpoint();
      downloadText(`${state.caseDefinition.case_id}.sdtcheckpoint.json`, JSON.stringify(checkpoint, null, 2));
      toast("Deterministic session checkpoint exported.");
    } catch (error) {
      toast(error.message, true);
    }
  });
  elements.resumeButton.addEventListener("click", () => elements.resumeInput.click());
  elements.resumeInput.addEventListener("change", async () => {
    const file = elements.resumeInput.files[0];
    if (!file) return;
    try {
      await worker.resume(state.caseDefinition, JSON.parse(await file.text()));
      state.sessionStarted = true;
      state.result = { ...(state.result ?? {}), status: "running" };
      elements.checkpointButton.disabled = false;
      elements.runButton.textContent = "Continue chunk";
      toast(`Resumed ${file.name}; advance the next chunk.`);
    } catch (error) {
      toast(error.message, true);
    }
    elements.resumeInput.value = "";
  });
  elements.pairSelector.addEventListener("change", renderPairMatrix);
  elements.timeline.addEventListener("input", () => { state.playing = false; setFrame(Number(elements.timeline.value)); });
  elements.playButton.addEventListener("click", togglePlayback);
  $("#jumpStartButton").addEventListener("click", () => { state.playing = false; setFrame(0); });
  $("#jumpEndButton").addEventListener("click", () => { state.playing = false; setFrame((state.result?.trajectory?.length ?? 1) - 1); });
  $("#stepBackButton").addEventListener("click", () => { state.playing = false; setFrame(state.frameIndex - 1); });
  $("#stepForwardButton").addEventListener("click", () => { state.playing = false; setFrame(state.frameIndex + 1); });
  elements.chartMetric.addEventListener("change", drawChart);
  $("#frameMode").addEventListener("change", (event) => renderer?.setFrameMode(event.target.value, elements.referenceBody.value));
  elements.referenceBody.addEventListener("change", () => renderer?.setFrameMode($("#frameMode").value, elements.referenceBody.value));
  $("#fitViewButton").addEventListener("click", () => renderer?.fit());
  $$("[data-overlay]").forEach((input) => input.addEventListener("change", () => renderer?.setOverlay(input.dataset.overlay, input.checked)));
  $("#sectionDisplayScale").addEventListener("change", (event) => renderer?.setSectionDisplayScale(event.target.value));
  elements.exportResult.addEventListener("click", () => downloadText(`${state.result.case_id}.sdtresult.json`, JSON.stringify(state.result, null, 2)));
  elements.exportCsv.addEventListener("click", () => downloadText(`${state.result.case_id}.trajectory.csv`, resultToCsv(state.result), "text/csv"));
  window.addEventListener("resize", drawChart);
}

async function initialize() {
  bindEvents();
  bindRendererEvents();
  let sharedCase = null;
  try {
    sharedCase = caseFromLocationHash(location.hash);
    if (sharedCase) state.caseDefinition = sharedCase;
  } catch (error) {
    toast(`Share payload rejected: ${error.message}`, true);
  }
  renderCase();
  renderer?.setSectionDisplayScale($("#sectionDisplayScale").value);
  renderResultSummary();
  drawChart();
  try {
    const manifest = await worker.initialize();
    setSolverState("ready", "WebAssembly worker ready.", `${manifest.build_id} · ${manifest.compiler}`);
    elements.runButton.disabled = !validateCase(state.caseDefinition).valid;
    if (validateCase(state.caseDefinition).valid) {
      await runCase({ full: true, autoplay: true });
      if (!sharedCase) toast("Default circular-pair preset is already in motion.");
    }
  } catch (error) {
    setSolverState("error", `WebAssembly initialization failed: ${error.message}`);
    toast("Certified solver assets could not be initialized.", true);
  }
}

initialize();
