/**
 * Walk every preset, pair, section scale, and chart metric; report UI state.
 * Run: node tests/walk-all-selections.mjs
 */
import { spawn } from "node:child_process";
import { setTimeout as sleep } from "node:timers/promises";
import { fileURLToPath } from "node:url";
import { chromium } from "@playwright/test";

const PORT = Number(process.env.WALK_PORT || 4188);
const BASE = `http://127.0.0.1:${PORT}`;
const PRESETS = [
  "circular-pair",
  "stable-triangle",
  "figure-eight",
  "restricted-lagrange",
  "single-pendulum",
  "double-pendulum",
  "sectioned-pendulum",
];
const SECTION_SCALES = ["1", "10", "100", "1000"];
const CHART_METRICS = [
  "separation",
  "energy",
  "momentum",
  "angularMomentum",
  "jointAngle",
  "angularRate",
  "constraint",
];

function startServer(cwdPath) {
  return new Promise((resolve, reject) => {
    const child = spawn(process.execPath, ["tests/server.mjs"], {
      cwd: cwdPath,
      env: { ...process.env, PORT: String(PORT) },
      stdio: ["ignore", "pipe", "pipe"],
    });
    let settled = false;
    child.stdout.on("data", (c) => {
      if (!settled && String(c).includes("ready")) {
        settled = true;
        resolve(child);
      }
    });
    child.stderr.on("data", (c) => {
      if (!settled) {
        settled = true;
        reject(new Error(String(c)));
      }
    });
    sleep(15000).then(() => {
      if (!settled) {
        settled = true;
        reject(new Error("server timeout"));
      }
    });
  });
}

async function readState(page) {
  return page.evaluate(() => {
    const optionTexts = (sel) => [...document.querySelectorAll(`#${sel} option`)].map((o) => o.textContent);
    const optionValues = (sel) => [...document.querySelectorAll(`#${sel} option`)].map((o) => o.value);
    return {
      solverStatus: document.querySelector("#solverStatus")?.textContent ?? "",
      classification: document.querySelector("#classificationBanner strong")?.textContent ?? "",
      bodyCount: document.querySelectorAll("#sceneTree .tree-item").length,
      pairOptions: optionValues("pairSelector"),
      pairLabels: optionTexts("pairSelector"),
      pairCells: document.querySelectorAll("#pairMatrix .pair-cell").length,
      pairMatrixText: document.querySelector("#pairMatrix")?.textContent?.slice(0, 120) ?? "",
      timelineEnabled: !document.querySelector("#timelineSlider")?.disabled,
      timelineMax: document.querySelector("#timelineSlider")?.max ?? "0",
      playLabel: document.querySelector("#playButton")?.textContent ?? "",
      validation: document.querySelector("#caseValidation")?.textContent?.slice(0, 100) ?? "",
      problemClass: document.querySelector("#problemClassInput")?.value ?? "",
      occlusionOverlay: document.querySelector('[data-overlay="occlusion"]')?.checked ?? false,
      sectionScale: document.querySelector("#sectionDisplayScale")?.value ?? "",
      canvasSize: {
        w: document.querySelector("#sceneCanvas")?.clientWidth ?? 0,
        h: document.querySelector("#sceneCanvas")?.clientHeight ?? 0,
      },
      hasResultInteractions: document.querySelector("#resultJson")?.textContent?.includes('"interactions"') ?? false,
      errors: window.__walkErrors ?? [],
    };
  });
}

async function waitForRun(page, timeoutMs = 180000) {
  const start = Date.now();
  while (Date.now() - start < timeoutMs) {
    const status = await page.locator("#solverStatus").textContent();
    if (/completed|running: paused|error/i.test(status)) {
      const timelineEnabled = await page.locator("#timelineSlider").isEnabled().catch(() => false);
      if (/completed/i.test(status) || timelineEnabled) return status;
    }
    await sleep(500);
  }
  return await page.locator("#solverStatus").textContent();
}

async function main() {
  const cwdPath = fileURLToPath(new URL("..", import.meta.url));
  const server = await startServer(cwdPath);

  const report = { startedAt: new Date().toISOString(), presets: [], pairWalks: [], sectionScales: [], chartMetrics: [], pageErrors: [] };

  const browser = await chromium.launch({ headless: true });
  const page = await browser.newPage({ viewport: { width: 1440, height: 900 } });
  page.on("pageerror", (err) => report.pageErrors.push(err.message));
  await page.addInitScript(() => { window.__walkErrors = []; });

  try {
    await page.goto(BASE, { waitUntil: "domcontentloaded" });
    await waitForRun(page, 120000);
    report.initial = await readState(page);

    for (const preset of PRESETS) {
      const entry = { preset, before: null, after: null, status: null, error: null };
      try {
        await page.locator("#presetSelect").selectOption(preset);
        await page.locator("#loadPresetButton").click();
        entry.status = await waitForRun(page, 180000);
        entry.after = await readState(page);
        report.presets.push(entry);
      } catch (error) {
        entry.error = error.message;
        report.presets.push(entry);
      }
    }

    // Pair walk on richest occlusion preset with most pairs
    await page.locator("#presetSelect").selectOption("restricted-lagrange");
    await page.locator("#loadPresetButton").click();
    await waitForRun(page, 180000);
    const pairOptions = await page.locator("#pairSelector option").allTextContents();
    const pairValues = await page.locator("#pairSelector option").evaluateAll((nodes) => nodes.map((n) => n.value));
    for (const value of pairValues) {
      await page.locator("#pairSelector").selectOption(value);
      await sleep(300);
      const state = await readState(page);
      report.pairWalks.push({ pair: value, label: pairOptions[pairValues.indexOf(value)], ...state });
    }

    // Section scales on circular pair
    await page.locator("#presetSelect").selectOption("circular-pair");
    await page.locator("#loadPresetButton").click();
    await waitForRun(page, 180000);
    for (const scale of SECTION_SCALES) {
      await page.locator("#sectionDisplayScale").selectOption(scale);
      await sleep(200);
      report.sectionScales.push({ scale, ...(await readState(page)) });
    }

    // Chart metrics on circular pair
    for (const metric of CHART_METRICS) {
      await page.locator("#chartMetric").selectOption(metric);
      await sleep(100);
      const name = await page.locator("#chartName").textContent();
      const value = await page.locator("#chartValue").textContent();
      report.chartMetrics.push({ metric, name, value });
    }

    // Frame modes and reference bodies on triangle
    await page.locator("#presetSelect").selectOption("stable-triangle");
    await page.locator("#loadPresetButton").click();
    await waitForRun(page, 180000);
    report.frameModes = [];
    for (const mode of ["inertial", "rotating"]) {
      await page.locator("#frameMode").selectOption(mode);
      await sleep(150);
      report.frameModes.push({ mode, ...(await readState(page)) });
    }
    const refOptions = await page.locator("#referenceBody option").allTextContents();
    report.referenceBodies = refOptions;

    // Scene tree selection walk on circular pair
    await page.locator("#presetSelect").selectOption("circular-pair");
    await page.locator("#loadPresetButton").click();
    await waitForRun(page, 180000);
    report.bodySelections = [];
    const bodies = await page.locator("#sceneTree .tree-item").all();
    for (let i = 0; i < bodies.length; i += 1) {
      await bodies[i].click();
      await sleep(150);
      const inspectorText = await page.locator("#entityInspector").textContent();
      report.bodySelections.push({
        index: i,
        label: await bodies[i].textContent(),
        inspectorHasComputedVelocity: inspectorText.includes("computed"),
        inspectorSnippet: inspectorText.slice(0, 160),
      });
    }

    report.summary = {
      presetCount: report.presets.length,
      presetsCompleted: report.presets.filter((p) => /completed/i.test(p.status ?? "")).length,
      presetsFailed: report.presets.filter((p) => p.error || /error/i.test(p.status ?? "")).length,
      pairWalkCount: report.pairWalks.length,
      pairCellsAlways49: report.pairWalks.every((p) => p.pairCells === 49),
      pageErrorCount: report.pageErrors.length,
    };
  } finally {
    await browser.close();
    server.kill();
  }

  console.log(JSON.stringify(report, null, 2));
}

main().catch((error) => {
  console.error(error);
  process.exit(1);
});
