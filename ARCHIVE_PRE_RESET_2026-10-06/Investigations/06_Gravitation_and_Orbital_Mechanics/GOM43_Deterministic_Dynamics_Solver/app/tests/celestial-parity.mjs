import assert from "node:assert/strict";
import { execFile } from "node:child_process";
import { createReadStream, readFileSync, statSync } from "node:fs";
import http from "node:http";
import { extname, join, normalize, resolve } from "node:path";
import { promisify } from "node:util";
import { fileURLToPath } from "node:url";
import { chromium } from "playwright";

const execute = promisify(execFile);
const appRoot = resolve(fileURLToPath(new URL("..", import.meta.url)));
const repository = resolve(appRoot, "../../../..");
const siteRoot = join(repository, "Release", "HTML_SDT_Website");
const fixtureRoot = join(
  repository,
  "Investigations",
  "06_Gravitation_and_Orbital_Mechanics",
  "GOM43_Deterministic_Dynamics_Solver",
  "examples",
  "celestial",
);
const fixtures = [
  join(fixtureRoot, "jpl-sun-earth-moon-j2000.sdtcase.json"),
  join(fixtureRoot, "earth-tail-stage-scan.sdtcase.json"),
];
const solver = process.argv[2] || process.env.SDT_NATIVE_SOLVER;
if (!solver) throw new Error("Pass the native solver executable path.");

const mime = new Map([
  [".html", "text/html; charset=utf-8"],
  [".js", "text/javascript; charset=utf-8"],
  [".wasm", "application/wasm"],
  [".css", "text/css; charset=utf-8"],
  [".json", "application/json; charset=utf-8"],
]);
const server = http.createServer((request, response) => {
  const relative = decodeURIComponent(
    new URL(request.url, "http://127.0.0.1").pathname,
  ).replace(/^\/+/, "");
  const path = normalize(join(siteRoot, relative || "index.html"));
  if (!path.startsWith(siteRoot) || !statSafe(path)) {
    response.writeHead(404).end("not found");
    return;
  }
  response.writeHead(200, {
    "Content-Type": mime.get(extname(path)) || "application/octet-stream",
    "Cache-Control": "no-store",
  });
  createReadStream(path).pipe(response);
});
function statSafe(path) {
  try {
    return statSync(path).isFile();
  } catch {
    return false;
  }
}
await new Promise(resolveServer => server.listen(4178, "127.0.0.1", resolveServer));

function compareNumbers(left, right) {
  let maximumRelative = 0;
  const visit = (first, second, path) => {
    if (typeof first === "number" && typeof second === "number") {
      const relative = Math.abs(first - second)
        / Math.max(1, Math.abs(first), Math.abs(second));
      maximumRelative = Math.max(maximumRelative, relative);
      return;
    }
    if (Array.isArray(first)) {
      assert.equal(second.length, first.length, `${path} length`);
      first.forEach((value, index) => visit(value, second[index], `${path}[${index}]`));
      return;
    }
    if (first && typeof first === "object") {
      for (const key of Object.keys(first)) {
        if (["compiler", "trajectory_sha256"].includes(key)) continue;
        visit(first[key], second[key], `${path}.${key}`);
      }
      return;
    }
    assert.deepEqual(second, first, path);
  };
  visit(left, right, "result");
  return maximumRelative;
}

const browser = await chromium.launch({ headless: true });
try {
  const page = await browser.newPage();
  await page.goto("http://127.0.0.1:4178/celestial-three-body-solver.html");
  await page.waitForFunction(
    () => document.querySelector("#status")?.textContent.includes("WASM ready"),
  );
  assert.equal(
    await page.locator("#preset option").count(),
    25,
    "published celestial catalog must expose exactly twenty-five simulations",
  );
  for (const fixture of fixtures) {
    const { stdout } = await execute(resolve(solver), [fixture], {
      maxBuffer: 64 * 1024 * 1024,
    });
    const nativeResult = JSON.parse(stdout);
    await page.locator("#caseJson").fill(readFileSync(fixture, "utf8"));
    await page.locator("#chunk").fill("1");
    await page.locator("#create").click();
    await page.waitForFunction(
      expected => window.__sdtCelestialLastResult?.provenance?.input_sha256 === expected,
      nativeResult.provenance.input_sha256,
    );
    const wasmResult = await page.evaluate(() => window.__sdtCelestialLastResult);
    assert.equal(wasmResult.status, nativeResult.status);
    assert.equal(wasmResult.executed_steps, nativeResult.executed_steps);
    assert.equal(
      wasmResult.provenance.input_sha256,
      nativeResult.provenance.input_sha256,
    );
    assert.equal(
      wasmResult.provenance.laws_sha256,
      nativeResult.provenance.laws_sha256,
    );
    const maximumRelative = compareNumbers(nativeResult, wasmResult);
    assert.ok(
      maximumRelative <= 2e-11,
      `celestial native/WASM relative residual ${maximumRelative}`,
    );
    console.log(
      `celestial-three-body ${nativeResult.contract_version}: PASS `
      + `max_rel=${maximumRelative.toExponential(6)} `
      + `native_hash=${nativeResult.trajectory_sha256} `
      + `wasm_hash=${wasmResult.trajectory_sha256}`,
    );
  }
} finally {
  await browser.close();
  await new Promise(resolveServer => server.close(resolveServer));
}

