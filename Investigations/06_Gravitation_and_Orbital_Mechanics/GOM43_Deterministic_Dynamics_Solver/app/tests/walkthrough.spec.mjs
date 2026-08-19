import { expect, test } from "@playwright/test";

async function waitForRun(page, timeoutMs = 180000) {
  const start = Date.now();
  while (Date.now() - start < timeoutMs) {
    const status = await page.locator("#solverStatus").textContent();
    if (/completed/i.test(status)) return status;
    if (/error/i.test(status)) return status;
    await page.waitForTimeout(500);
  }
  return page.locator("#solverStatus").textContent();
}

async function snapshot(page) {
  return {
    solverStatus: await page.locator("#solverStatus").textContent(),
    classification: await page.locator("#classificationBanner strong").textContent(),
    bodies: await page.locator("#sceneTree .tree-item").count(),
    pairCount: await page.locator("#pairSelector option").count(),
    pairCells: await page.locator("#pairMatrix .pair-cell").count(),
    timelineEnabled: await page.locator("#timelineSlider").isEnabled(),
    timelineMax: await page.locator("#timelineSlider").getAttribute("max"),
    problemClass: await page.locator("#problemClassInput").inputValue(),
  };
}

test.describe.configure({ mode: "serial", timeout: 240000 });

const PRESETS = [
  ["circular-pair", "sdt_occlusion_nbody", { bodies: 2 }],
  ["stable-triangle", "sdt_occlusion_nbody", { bodies: 3 }],
  ["figure-eight", "sdt_occlusion_nbody", { bodies: 3 }],
  ["restricted-lagrange", "sdt_occlusion_nbody", { bodies: 7 }],
  ["single-pendulum", "articulated_rigid", { links: 1, joints: 1 }],
  ["double-pendulum", "articulated_rigid", { links: 2, joints: 2 }],
  ["sectioned-pendulum", "articulated_rigid", { links: 5, joints: 5 }],
];

for (const [preset, problemClass, counts] of PRESETS) {
  test(`preset ${preset} loads and runs`, async ({ page }) => {
    const errors = [];
    page.on("pageerror", (error) => errors.push(error.message));
    await page.goto("/");
    if (preset !== "circular-pair") {
      await page.locator("#presetSelect").selectOption(preset);
      await page.locator("#loadPresetButton").click();
    }
    await waitForRun(page, 180000);
    const state = await snapshot(page);
    expect(state.problemClass).toBe(problemClass);
    const treeCount = await page.locator("#sceneTree .tree-item").count();
    if (counts.bodies) {
      expect(treeCount).toBe(counts.bodies);
    } else {
      expect(treeCount).toBe((counts.links ?? 0) + (counts.joints ?? 0));
    }
    expect(state.solverStatus).toMatch(/completed/i);
    if (problemClass === "sdt_occlusion_nbody") {
      expect(state.timelineEnabled).toBeTruthy();
      expect(Number(state.timelineMax)).toBeGreaterThan(5);
      expect(state.pairCount).toBe(counts.bodies * (counts.bodies - 1));
      expect(state.pairCells).toBe(49);
    }
    expect(errors).toEqual([]);
  });
}

test("walk every ordered pair on restricted-lagrange", async ({ page }) => {
  await page.goto("/");
  await waitForRun(page, 120000);
  await page.locator("#presetSelect").selectOption("restricted-lagrange");
  await page.locator("#loadPresetButton").click();
  await waitForRun(page, 180000);
  const values = await page.locator("#pairSelector option").evaluateAll((nodes) => nodes.map((n) => n.value));
  expect(values.length).toBe(42);
  for (const value of values) {
    await page.locator("#pairSelector").selectOption(value);
    await expect(page.locator("#pairMatrix .pair-cell")).toHaveCount(49);
    const first = await page.locator("#pairMatrix .pair-cell strong").first().textContent();
    expect(first).toMatch(/^T\d·S\d$/);
  }
});

test("section display scales and chart metrics on circular pair", async ({ page }) => {
  await page.goto("/");
  await waitForRun(page, 120000);
  for (const scale of ["1", "10", "100", "1000"]) {
    await page.locator("#sectionDisplayScale").selectOption(scale);
    await expect(page.locator("#pairMatrix .pair-cell")).toHaveCount(49);
  }
  for (const metric of ["separation", "energy", "momentum", "angularMomentum"]) {
    await page.locator("#chartMetric").selectOption(metric);
    await expect(page.locator("#chartValue")).not.toHaveText("—");
  }
});

test("frame mode and body inspector selection", async ({ page }) => {
  await page.goto("/");
  await waitForRun(page, 120000);
  await page.locator("#presetSelect").selectOption("stable-triangle");
  await page.locator("#loadPresetButton").click();
  await waitForRun(page, 180000);
  await page.locator("#frameMode").selectOption("rotating");
  await page.locator("#referenceBody").selectOption({ index: 0 });
  const items = page.locator("#sceneTree .tree-item");
  await items.nth(0).click();
  await expect(page.locator("#entityInspector")).toContainText("computed");
  await items.nth(1).click();
  await expect(page.locator("#entityInspector")).toContainText("Position (m)");
});
