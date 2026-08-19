/* SDT celestial solver worker: the numerical path is C++/WASM only. */
"use strict";

let modulePromise;
let moduleInstance;
let activeHandle = null;

function loadModule() {
  if (!modulePromise) {
    modulePromise = new Promise((resolve, reject) => {
      try {
        importScripts("../wasm/sdt-dynamics-core.js");
        createSdtDynamicsModule({
          locateFile: file => `../wasm/${file}`
        }).then(instance => {
          moduleInstance = instance;
          resolve(instance);
        }, reject);
      } catch (error) {
        reject(error);
      }
    });
  }
  return modulePromise;
}

function allocate(text) {
  const bytes = new TextEncoder().encode(`${text}\0`);
  const pointer = moduleInstance._malloc(bytes.length);
  moduleInstance.HEAPU8.set(bytes, pointer);
  return pointer;
}

function decodeAndFree(pointer) {
  if (!pointer) throw new Error("WASM returned a null buffer");
  let end = pointer;
  while (moduleInstance.HEAPU8[end] !== 0) end++;
  const text = new TextDecoder().decode(
    moduleInstance.HEAPU8.subarray(pointer, end)
  );
  moduleInstance._solver_free(pointer);
  return JSON.parse(text);
}

function callOne(functionName, value) {
  const pointer = allocate(value);
  try {
    return decodeAndFree(moduleInstance[functionName](pointer));
  } finally {
    moduleInstance._free(pointer);
  }
}

function callTwo(functionName, first, second) {
  const firstPointer = allocate(first);
  const secondPointer = allocate(second);
  try {
    return decodeAndFree(
      moduleInstance[functionName](firstPointer, secondPointer)
    );
  } finally {
    moduleInstance._free(firstPointer);
    moduleInstance._free(secondPointer);
  }
}

async function destroyActive() {
  if (activeHandle !== null) {
    callOne("_session_destroy", activeHandle);
    activeHandle = null;
  }
}

self.onmessage = async event => {
  const {id, type, payload = {}} = event.data;
  try {
    await loadModule();
    let result;
    if (type === "manifest") {
      result = decodeAndFree(moduleInstance._solver_manifest());
    } else if (type === "selfTest") {
      result = decodeAndFree(moduleInstance._self_test());
    } else if (type === "create") {
      await destroyActive();
      result = callOne("_session_create", payload.caseJson);
      if (result.status === "created") activeHandle = result.handle;
    } else if (type === "advance") {
      if (activeHandle === null) throw new Error("create a session first");
      result = callTwo(
        "_session_advance",
        activeHandle,
        String(payload.steps)
      );
    } else if (type === "checkpoint") {
      if (activeHandle === null) throw new Error("no active session");
      result = callOne("_session_checkpoint", activeHandle);
    } else if (type === "resume") {
      await destroyActive();
      result = callTwo(
        "_session_resume",
        payload.caseJson,
        payload.checkpointJson
      );
      if (result.status === "resumed") activeHandle = result.handle;
    } else if (type === "destroy") {
      await destroyActive();
      result = {status: "destroyed"};
    } else {
      throw new Error(`unknown worker operation: ${type}`);
    }
    self.postMessage({id, ok: true, result});
  } catch (error) {
    self.postMessage({
      id,
      ok: false,
      error: error instanceof Error ? error.message : String(error)
    });
  }
};

