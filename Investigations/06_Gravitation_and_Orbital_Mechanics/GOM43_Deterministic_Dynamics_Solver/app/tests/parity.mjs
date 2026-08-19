import assert from "node:assert/strict";
import { execFile, spawn } from "node:child_process";
import { once } from "node:events";
import { resolve } from "node:path";
import { promisify } from "node:util";
import { fileURLToPath } from "node:url";
import { chromium } from "playwright";

const execute = promisify(execFile);
const appRoot = resolve(fileURLToPath(new URL("..", import.meta.url)));
const solver = process.argv[2] || process.env.SDT_NATIVE_SOLVER;
if (!solver) {
  throw new Error("Pass the native sdt-dynamics-solver executable path as the first argument.");
}

const cases = [
  {
    name: "circular-pair",
    path: fileURLToPath(new URL("../../examples/circular-pair.sdtcase.json", import.meta.url)),
  },
  {
    name: "simple-pendulum",
    path: fileURLToPath(new URL("../../examples/simple-pendulum.sdtcase.json", import.meta.url)),
  },
  {
    name: "multibody-seven-circle-pair",
    path: fileURLToPath(new URL("../../examples/multibody-seven-circle-pair.sdtcase.json", import.meta.url)),
  },
];

function compareNumbers(nativeResult, wasmResult) {
  let maxAbsolute = 0;
  let maxRelative = 0;
  const visit = (left, right, path) => {
    if (typeof left === "number" && typeof right === "number") {
      const absolute = Math.abs(left - right);
      const relative = absolute / Math.max(1, Math.abs(left), Math.abs(right));
      maxAbsolute = Math.max(maxAbsolute, absolute);
      maxRelative = Math.max(maxRelative, relative);
      return;
    }
    if (Array.isArray(left)) {
      assert.equal(right.length, left.length, `${path} length`);
      left.forEach((value, index) => visit(value, right[index], `${path}[${index}]`));
      return;
    }
    if (left && typeof left === "object") {
      for (const key of Object.keys(left)) {
        if (["compiler", "trajectory_sha256"].includes(key)) continue;
        visit(left[key], right[key], `${path}.${key}`);
      }
      return;
    }
    assert.deepEqual(right, left, path);
  };
  visit(nativeResult, wasmResult, "result");
  return { maxAbsolute, maxRelative };
}

const server = spawn(process.execPath, ["tests/server.mjs"], {
  cwd: appRoot,
  env: { ...process.env, PORT: "4175" },
  stdio: ["ignore", "pipe", "inherit"],
});
await Promise.race([
  once(server.stdout, "data"),
  new Promise((_, reject) => setTimeout(() => reject(new Error("Parity server did not start.")), 10000)),
]);

const browser = await chromium.launch({ headless: true });
try {
  const page = await browser.newPage();
  await page.goto("http://127.0.0.1:4175");
  await page.waitForFunction(() => document.querySelector("#solverStatus")?.textContent.includes("WebAssembly worker ready"));
  for (const entry of cases) {
    const { stdout } = await execute(resolve(solver), [entry.path], { maxBuffer: 64 * 1024 * 1024 });
    const nativeResult = JSON.parse(stdout);
    await page.locator("#importInput").setInputFiles(entry.path);
    await page.locator("#runButton").click();
    await page.waitForFunction(() => document.querySelector("#solverStatus")?.textContent.includes("completed"));
    const wasmResult = JSON.parse(await page.locator("#resultJson").textContent());
    assert.equal(wasmResult.status, nativeResult.status, `${entry.name} status`);
    assert.equal(wasmResult.classification, nativeResult.classification, `${entry.name} classification`);
    assert.equal(wasmResult.executed_steps, nativeResult.executed_steps, `${entry.name} steps`);
    assert.equal(wasmResult.provenance.input_sha256, nativeResult.provenance.input_sha256, `${entry.name} input hash`);
    assert.equal(wasmResult.provenance.laws_sha256, nativeResult.provenance.laws_sha256, `${entry.name} laws hash`);
    const residuals = compareNumbers(nativeResult, wasmResult);
    assert.ok(residuals.maxRelative <= 2e-11, `${entry.name} relative residual ${residuals.maxRelative}`);
    console.log(`${entry.name}: PASS max_abs=${residuals.maxAbsolute.toExponential(6)} max_rel=${residuals.maxRelative.toExponential(6)} native_hash=${nativeResult.trajectory_sha256} wasm_hash=${wasmResult.trajectory_sha256}`);
  }
} finally {
  await browser.close();
  server.kill();
}
