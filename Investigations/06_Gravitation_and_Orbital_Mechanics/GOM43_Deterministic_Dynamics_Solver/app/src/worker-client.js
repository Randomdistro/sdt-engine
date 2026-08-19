import { makeRequest, validateResponse } from "./worker-protocol.js";

export class SolverWorkerClient extends EventTarget {
  #workerUrl;
  #worker;
  #nextRequestId = 1;
  #pending = new Map();
  #generation = 0;

  constructor(workerUrl = new URL("../worker/solver-worker.js", import.meta.url)) {
    super();
    this.#workerUrl = workerUrl;
  }

  async initialize() {
    if (this.#worker) return;
    const generation = ++this.#generation;
    this.#worker = new Worker(this.#workerUrl);
    this.#worker.addEventListener("message", (event) => {
      if (generation === this.#generation) this.#handleMessage(event.data);
    });
    this.#worker.addEventListener("error", (event) => {
      this.#failAll(new Error(event.message || "WebAssembly worker failed."));
      this.dispatchEvent(new CustomEvent("worker-error", { detail: event }));
    });
    return this.#request("initialize");
  }

  async run(caseDefinition, { steps = 1, full = false } = {}) {
    await this.initialize();
    return this.#request("run", {
      caseJson: JSON.stringify(caseDefinition),
      steps,
      full: Boolean(full),
    });
  }

  async advance(steps = 1) {
    await this.initialize();
    return this.#request("advance", { steps });
  }

  async checkpoint() {
    await this.initialize();
    return this.#request("checkpoint");
  }

  async resume(caseDefinition, checkpoint) {
    await this.initialize();
    return this.#request("resume", {
      caseJson: JSON.stringify(caseDefinition),
      checkpointJson: JSON.stringify(checkpoint),
    });
  }

  async selfTest() {
    await this.initialize();
    return this.#request("self-test");
  }

  cancel(reason = "Run cancelled by operator.") {
    if (!this.#worker) return;
    this.#worker.terminate();
    this.#worker = undefined;
    this.#generation += 1;
    this.#failAll(new DOMException(reason, "AbortError"));
    this.dispatchEvent(new CustomEvent("cancelled"));
  }

  destroy() {
    this.cancel("Solver worker destroyed.");
  }

  #request(type, payload = {}) {
    const requestId = this.#nextRequestId++;
    const request = makeRequest(type, requestId, payload);
    return new Promise((resolve, reject) => {
      this.#pending.set(requestId, { type, resolve, reject });
      this.#worker.postMessage(request);
    });
  }

  #handleMessage(message) {
    const protocolError = validateResponse(message);
    if (protocolError) {
      this.#failAll(new Error(protocolError));
      return;
    }
    if (message.type === "status") {
      this.dispatchEvent(new CustomEvent("status", { detail: message }));
      return;
    }
    const pending = this.#pending.get(message.requestId);
    if (!pending) return;
    if (message.type === "error") {
      this.#pending.delete(message.requestId);
      pending.reject(new Error(message.message));
      return;
    }
    const expected = {
      initialize: "ready",
      run: "result",
      advance: "result",
      checkpoint: "checkpoint-result",
      resume: "resume-result",
      "self-test": "self-test-result",
    }[pending.type];
    if (message.type !== expected) return;
    this.#pending.delete(message.requestId);
    pending.resolve(message.result ?? message.manifest);
  }

  #failAll(error) {
    for (const pending of this.#pending.values()) pending.reject(error);
    this.#pending.clear();
  }
}
