/* global createSdtDynamicsModule */
"use strict";

const PROTOCOL = "1.1.0";
let modulePromise;
let wasmModule;
let activeHandle = "";

function respond(type, requestId, detail = {}) {
  self.postMessage({ protocol: PROTOCOL, type, requestId, ...detail });
}

function wasmUrl(filename) {
  return new URL(`../wasm/${filename}`, self.location.href).href;
}

async function initialize(requestId) {
  if (!modulePromise) {
    importScripts(wasmUrl("sdt-dynamics-core.js"));
    if (typeof createSdtDynamicsModule !== "function") {
      throw new Error("The pinned GOM43 Emscripten loader did not expose createSdtDynamicsModule.");
    }
    modulePromise = createSdtDynamicsModule({
      locateFile: (path) => wasmUrl(path),
      noInitialRun: true,
    });
  }
  wasmModule = await modulePromise;
  const manifest = callNoArg("_solver_manifest");
  respond("ready", requestId, { manifest });
}

function readUtf8(pointer) {
  if (!pointer) throw new Error("GOM43 C ABI returned a null result allocation.");
  const heap = wasmModule.HEAPU8;
  let end = pointer;
  while (heap[end] !== 0) end += 1;
  return new TextDecoder().decode(heap.subarray(pointer, end));
}

function callNoArg(exportName) {
  const pointer = wasmModule[exportName]();
  try {
    return JSON.parse(readUtf8(pointer));
  } finally {
    if (pointer) wasmModule._solver_free(pointer);
  }
}

function callRun(caseJson) {
  const encoded = new TextEncoder().encode(`${caseJson}\0`);
  const inputPointer = wasmModule._malloc(encoded.length);
  if (!inputPointer) throw new Error("Unable to allocate WebAssembly input memory.");
  wasmModule.HEAPU8.set(encoded, inputPointer);
  let resultPointer = 0;
  try {
    resultPointer = wasmModule._run_case(inputPointer);
    return JSON.parse(readUtf8(resultPointer));
  } finally {
    if (resultPointer) wasmModule._solver_free(resultPointer);
    wasmModule._free(inputPointer);
  }
}

function callWithStrings(exportName, values) {
  const allocations = values.map((value) => {
    const encoded = new TextEncoder().encode(`${value}\0`);
    const pointer = wasmModule._malloc(encoded.length);
    if (!pointer) throw new Error("Unable to allocate WebAssembly session input.");
    wasmModule.HEAPU8.set(encoded, pointer);
    return pointer;
  });
  let resultPointer = 0;
  try {
    resultPointer = wasmModule[exportName](...allocations);
    return JSON.parse(readUtf8(resultPointer));
  } finally {
    if (resultPointer) wasmModule._solver_free(resultPointer);
    allocations.forEach((pointer) => wasmModule._free(pointer));
  }
}

function destroyActiveSession() {
  if (!activeHandle) return;
  callWithStrings("_session_destroy", [activeHandle]);
  activeHandle = "";
}

function createAndAdvance(caseJson, steps) {
  destroyActiveSession();
  const created = callWithStrings("_session_create", [caseJson]);
  if (created.status !== "created") {
    throw new Error(created.message ?? "Unable to create multibody session.");
  }
  activeHandle = created.handle;
  const result = callWithStrings("_session_advance", [activeHandle, String(steps)]);
  if (result.status !== "running") destroyActiveSession();
  return result;
}

function advanceActive(steps) {
  if (!activeHandle) throw new Error("No paused multibody session is available.");
  const result = callWithStrings("_session_advance", [activeHandle, String(steps)]);
  if (result.status !== "running") destroyActiveSession();
  return result;
}

self.addEventListener("message", async ({ data }) => {
  const requestId = data?.requestId ?? 0;
  try {
    if (data?.protocol !== PROTOCOL) throw new Error("Worker protocol version mismatch.");
    if (data.type === "initialize") {
      await initialize(requestId);
      return;
    }
    if (!wasmModule) await initialize(requestId);
    if (data.type === "self-test") {
      respond("status", requestId, { phase: "self-test", progress: null });
      respond("self-test-result", requestId, { result: callNoArg("_self_test") });
      return;
    }
    if (data.type === "run") {
      if (typeof data.caseJson !== "string") throw new Error("Run request requires UTF-8 case JSON.");
      respond("status", requestId, { phase: "executing-fixed-steps", progress: null });
      const definition = JSON.parse(data.caseJson);
      const result = definition.contract_version === "3.0.0"
        ? createAndAdvance(data.caseJson, Math.max(1, Math.floor(data.steps ?? 1)))
        : callRun(data.caseJson);
      respond("status", requestId, { phase: "verifying-result", progress: 95 });
      respond("result", requestId, { result });
      return;
    }
    if (data.type === "advance") {
      respond("status", requestId, { phase: "advancing-seven-circle-session", progress: null });
      const result = advanceActive(Math.max(1, Math.floor(data.steps ?? 1)));
      respond("result", requestId, { result });
      return;
    }
    if (data.type === "checkpoint") {
      if (!activeHandle) throw new Error("No paused multibody session is available.");
      respond("checkpoint-result", requestId, {
        result: callWithStrings("_session_checkpoint", [activeHandle]),
      });
      return;
    }
    if (data.type === "resume") {
      if (typeof data.caseJson !== "string" || typeof data.checkpointJson !== "string") {
        throw new Error("Resume requires case and checkpoint JSON.");
      }
      destroyActiveSession();
      const resumed = callWithStrings("_session_resume", [data.caseJson, data.checkpointJson]);
      if (resumed.status !== "resumed") {
        throw new Error(resumed.message ?? "Unable to resume multibody session.");
      }
      activeHandle = resumed.handle;
      respond("resume-result", requestId, { result: resumed });
      return;
    }
    throw new Error(`Unsupported worker request: ${data?.type}`);
  } catch (error) {
    respond("error", requestId, {
      message: error instanceof Error ? error.message : String(error),
      stack: error instanceof Error ? error.stack : "",
    });
  }
});
