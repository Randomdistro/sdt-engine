import { expect, test } from "@playwright/test";
import { fileURLToPath } from "node:url";

async function waitForMotion(page) {
  await expect(page.locator("#timelineSlider")).toBeEnabled({ timeout: 120000 });
  await expect(page.locator("#playButton")).toContainText(/Play|Pause/);
}

test("renderer, worker ABI and circular example run as one browser instrument", async ({ page }) => {
  const errors = [];
  page.on("pageerror", (error) => errors.push(error.message));
  await page.goto("/");
  await expect(page.locator("html")).toHaveAttribute("data-renderer", /^three-/);
  await waitForMotion(page);
  const example = fileURLToPath(new URL("../../examples/circular-pair.sdtcase.json", import.meta.url));
  await page.locator("#importInput").setInputFiles(example);
  await expect(page.locator("#sceneTree .tree-item")).toHaveCount(2);
  await expect(page.locator("#solverStatus")).toContainText("completed", { timeout: 120000 });
  await expect(page.locator("#classificationBanner strong")).toHaveText("VALIDATED");
  await expect(page.locator("#gateList .gate.pass")).toHaveCount(1);
  await expect(page.locator("#timelineSlider")).toBeEnabled();
  await expect(page.locator("#provenanceList")).toContainText("gom43-solver-1.0.0");
  await expect(page.locator("#provenanceList dd").nth(6)).toHaveText(/^[0-9a-f]{64}$/);
  expect(errors).toEqual([]);
});

test("case composition, raw validation and local export controls stay synchronized", async ({ page }) => {
  await page.goto("/");
  await waitForMotion(page);
  await page.locator("#addEntityButton").click();
  await expect(page.locator("#sceneTree .tree-item")).toHaveCount(3);
  await page.locator('[data-tab="case"]').click();
  await page.locator('[data-editor-mode="raw"]').click();
  const raw = page.locator("#rawCaseEditor");
  const definition = JSON.parse(await raw.inputValue());
  expect(definition.bodies).toHaveLength(3);
  definition.case_id = "browser-edited-case";
  await raw.fill(JSON.stringify(definition));
  await page.locator("#applyJsonButton").click();
  await expect(page.locator("#caseValidation")).toContainText("Dimensionally valid");
  await page.locator('[data-editor-mode="form"]').click();
  await expect(page.locator("#caseIdInput")).toHaveValue("browser-edited-case");
  await expect(page.locator("#exportCaseButton")).toBeEnabled();
});

test("articulated example imports and runs through the same WASM ABI", async ({ page }) => {
  await page.goto("/");
  await waitForMotion(page);
  const example = fileURLToPath(new URL("../../examples/simple-pendulum.sdtcase.json", import.meta.url));
  await page.locator("#importInput").setInputFiles(example);
  await expect(page.locator("#caseValidation")).toContainText("Dimensionally valid");
  await expect(page.locator("#solverStatus")).toContainText("completed", { timeout: 120000 });
  await expect(page.locator("#classificationBanner strong")).toHaveText("CONDITIONAL");
  await expect(page.locator("#gateList .gate.pass")).toHaveCount(2);
  await expect(page.locator("#provenanceList dd").nth(8)).toHaveText(/^[0-9a-f]{64}$/);
});

test("full selected 7x7 occlusion matrix is computed and rendered", async ({ page }) => {
  const errors = [];
  page.on("pageerror", (error) => errors.push(error.message));
  await page.goto("/");
  await waitForMotion(page);
  await expect(page.locator("#playButton")).toContainText(/Play|Pause/);
  await expect(page.locator("#pairSelector option")).toHaveCount(2);
  await expect(page.locator("#pairMatrix .pair-cell")).toHaveCount(49);
  await expect(page.locator("#resultJson")).toContainText('"interactions"');
  await expect(page.locator("#resultJson")).toContainText('"target_channel": 6');
  expect(errors).toEqual([]);
});

test("loading a preset immediately places motion on the timeline", async ({ page }) => {
  await page.goto("/");
  await waitForMotion(page);
  await page.locator("#presetSelect").selectOption("figure-eight");
  await page.locator("#loadPresetButton").click();
  await expect(page.locator("#solverStatus")).toContainText("completed", { timeout: 180000 });
  await expect(page.locator("#timelineSlider")).toBeEnabled();
  await expect(page.locator("#playButton")).toContainText(/Play|Pause/);
  const frames = Number(await page.locator("#timelineSlider").getAttribute("max"));
  expect(frames).toBeGreaterThan(10);
});
