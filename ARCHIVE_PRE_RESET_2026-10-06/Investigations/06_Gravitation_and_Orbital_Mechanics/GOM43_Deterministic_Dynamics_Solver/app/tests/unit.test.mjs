import assert from "node:assert/strict";
import { createHash } from "node:crypto";
import { readFile } from "node:fs/promises";
import test from "node:test";
import { createPreset, presetNames } from "../src/cases.js";
import {
  decodeSharePayload, encodeSharePayload, parseCaseJson, resultToCsv, validateCase,
} from "../src/case-io.js";
import { buildDiagnosticSeries } from "../src/diagnostics.js";
import {
  buildCoFacingCrossSection,
  buildPairChannelLayout,
  channelDiscRadius,
  channelOffset,
  coFacingCrossSectionRadius,
  pairFrame,
} from "../src/occlusion-graphics.js";
import { applyLayoutVelocities, circularPairCheck, koppaFromBody } from "../src/layout-velocity.js";
import { makeRequest, validateResponse, WORKER_PROTOCOL_VERSION } from "../src/worker-protocol.js";

test("all seven laboratory presets satisfy dimensional case validation", () => {
  assert.equal(presetNames.length, 7);
  for (const name of presetNames) {
    const preset = createPreset(name);
    const validation = validateCase(preset);
    assert.equal(validation.valid, true, `${name}: ${validation.errors.join("; ")}`);
    assert.ok(validation.steps > 0);
    if (preset.bodies) {
      assert.equal(preset.contract_version, "3.0.0");
      assert.equal(preset.problem_class, "sdt_occlusion_nbody");
      assert.ok(preset.bodies.every((body) => /^[1-9][0-9]*$/.test(body.baryon_count)));
    }
  }
});

test("portable share payload round-trips UTF-8 case JSON", () => {
  const original = createPreset("double-pendulum");
  original.forces[0].provenance.description += " μ-safe";
  const restored = decodeSharePayload(encodeSharePayload(original));
  assert.deepEqual(restored, original);
});

test("malformed and dimensionally invalid imports are rejected", () => {
  assert.throws(() => parseCaseJson("{"));
  const invalid = createPreset("circular-pair");
  invalid.duration_s = invalid.timestep_s * 1.5;
  assert.throws(() => parseCaseJson(JSON.stringify(invalid)), /integral step count/);
});

test("worker protocol rejects unknown or mismatched messages", () => {
  assert.deepEqual(makeRequest("run", 7, { caseJson: "{}" }), {
    protocol: WORKER_PROTOCOL_VERSION, type: "run", requestId: 7, caseJson: "{}",
  });
  assert.equal(makeRequest("advance", 8, { steps: 16 }).type, "advance");
  assert.equal(makeRequest("checkpoint", 9).type, "checkpoint");
  assert.match(validateResponse({ protocol: "0", type: "ready", requestId: 1 }), /version mismatch/);
  assert.match(validateResponse({ protocol: WORKER_PROTOCOL_VERSION, type: "fallback", requestId: 1 }), /Unknown/);
});

test("UI-only fixture drives diagnostics and CSV without becoming a solver path", async () => {
  const fixture = JSON.parse(await readFile(new URL("./fixtures/ui-only-result.json", import.meta.url), "utf8"));
  assert.equal(fixture.fixture_scope, "UI_TEST_ONLY_NEVER_SOLVER_FALLBACK");
  const series = buildDiagnosticSeries(fixture.result);
  assert.equal(series.separation.values.length, 2);
  assert.ok(series.separation.values[1] > series.separation.values[0]);
  const csv = resultToCsv(fixture.result);
  assert.match(csv, /position_x_m/);
  assert.equal(csv.trim().split("\n").length, 5);
});

test("seven-circle channel layout matches the engine kernel", () => {
  const target = [0, 0, 0];
  const source = [10, 0, 0];
  const radius = 9;
  const facing = buildCoFacingCrossSection(target, source, radius);
  assert.equal(facing.channels.length, 7);
  assert.equal(coFacingCrossSectionRadius(radius), radius);
  assert.equal(channelDiscRadius(radius), 3);
  assert.deepEqual(facing.channels[0].centre_m, target);
  const frame = pairFrame([10, 0, 0]);
  const outer = channelOffset(1, radius, frame);
  assert.ok(Math.abs(Math.hypot(...outer) - 6) < 1e-9);
  assert.ok(Math.abs(Math.hypot(...outer) + channelDiscRadius(radius) - radius) < 1e-9);
});

test("every body gets one co-facing section per neighbour", () => {
  const layout = buildPairChannelLayout([0, 0, 0], [10, 0, 0], 9, 6);
  assert.equal(layout.targetChannels.length, 7);
  assert.equal(layout.sourceChannels.length, 7);
});

test("layout velocities follow SDT circular-orbit scaling for a two-body pair", () => {
  const preset = createPreset("circular-pair");
  applyLayoutVelocities(preset.bodies);
  const [a, b] = preset.bodies;
  const sep = Math.hypot(a.position_m[0] - b.position_m[0], a.position_m[1] - b.position_m[1]);
  const expected = circularPairCheck(sep, koppaFromBody(a), koppaFromBody(b));
  assert.ok(Math.abs(Math.hypot(...a.velocity_m_s) - expected.vA) / expected.vA < 1e-6);
  assert.ok(Math.hypot(...b.velocity_m_s) > 0);
});

test("deployed WASM assets match the pinned build manifest", async () => {
  const manifest = JSON.parse(await readFile(new URL("../wasm/BUILD-MANIFEST.json", import.meta.url), "utf8"));
  assert.equal(manifest.emscripten.version, "6.0.6");
  for (const [filename, expected] of Object.entries(manifest.assets)) {
    const asset = await readFile(new URL(`../wasm/${filename}`, import.meta.url));
    assert.equal(asset.byteLength, expected.bytes, `${filename} byte size`);
    assert.equal(createHash("sha256").update(asset).digest("hex"), expected.sha256, `${filename} SHA-256`);
  }
});
