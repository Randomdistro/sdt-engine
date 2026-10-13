export const WORKER_PROTOCOL_VERSION = "1.1.0";
export const REQUEST_TYPES = Object.freeze(["initialize", "run", "advance", "checkpoint", "resume", "self-test"]);
export const RESPONSE_TYPES = Object.freeze(["ready", "status", "result", "checkpoint-result", "resume-result", "self-test-result", "error"]);

export function makeRequest(type, requestId, payload = {}) {
  if (!REQUEST_TYPES.includes(type)) throw new Error(`Unsupported worker request: ${type}`);
  if (!Number.isInteger(requestId) || requestId < 1) throw new Error("Worker requestId must be a positive integer.");
  return { protocol: WORKER_PROTOCOL_VERSION, type, requestId, ...payload };
}

export function validateResponse(message) {
  if (!message || typeof message !== "object") return "Worker response is not an object.";
  if (message.protocol !== WORKER_PROTOCOL_VERSION) return "Worker protocol version mismatch.";
  if (!RESPONSE_TYPES.includes(message.type)) return `Unknown worker response type: ${message.type}`;
  if (!Number.isInteger(message.requestId) || message.requestId < 0) return "Worker response has an invalid requestId.";
  return null;
}
