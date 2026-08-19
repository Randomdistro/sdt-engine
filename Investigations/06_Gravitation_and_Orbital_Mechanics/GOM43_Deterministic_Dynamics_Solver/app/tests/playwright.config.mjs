import { defineConfig } from "@playwright/test";

export default defineConfig({
  testDir: ".",
  testMatch: "browser.spec.mjs",
  timeout: 60000,
  expect: { timeout: 15000 },
  use: {
    baseURL: "http://127.0.0.1:4174",
    headless: true,
    viewport: { width: 1440, height: 900 },
  },
  webServer: {
    command: "node server.mjs",
    url: "http://127.0.0.1:4174",
    env: { PORT: "4174" },
    timeout: 15000,
    reuseExistingServer: false,
  },
  reporter: [["list"]],
});
