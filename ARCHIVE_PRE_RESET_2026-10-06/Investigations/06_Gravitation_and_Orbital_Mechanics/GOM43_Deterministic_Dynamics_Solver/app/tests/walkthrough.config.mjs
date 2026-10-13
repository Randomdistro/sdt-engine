import { defineConfig } from "@playwright/test";

export default defineConfig({
  testDir: ".",
  testMatch: "walkthrough.spec.mjs",
  timeout: 240000,
  expect: { timeout: 180000 },
  use: {
    baseURL: "http://127.0.0.1:4174",
    headless: true,
    viewport: { width: 1440, height: 900 },
    launchOptions: {
      args: ["--disable-gpu", "--use-gl=swiftshader"],
    },
  },
  webServer: {
    command: "node server.mjs",
    url: "http://127.0.0.1:4174",
    env: { PORT: "4174" },
    timeout: 20000,
    reuseExistingServer: true,
  },
  reporter: [["list"]],
});
