import { copyFile, mkdir, readFile, writeFile } from "node:fs/promises";
import { dirname, resolve } from "node:path";
import { fileURLToPath } from "node:url";

const root = resolve(dirname(fileURLToPath(import.meta.url)), "..");
const threeRoot = resolve(root, "node_modules", "three");
const metadata = JSON.parse(await readFile(resolve(threeRoot, "package.json"), "utf8"));
const vendor = resolve(root, "vendor");

await mkdir(vendor, { recursive: true });
await copyFile(resolve(threeRoot, "build", "three.module.js"), resolve(vendor, "three.module.js"));
await copyFile(resolve(threeRoot, "build", "three.core.js"), resolve(vendor, "three.core.js"));
await copyFile(resolve(threeRoot, "LICENSE"), resolve(vendor, "THREE-LICENSE.txt"));
await writeFile(resolve(vendor, "VERSIONS.json"), `${JSON.stringify({
  renderer: {
    package: "three",
    version: metadata.version,
    source: "npm",
    license: metadata.license,
    artifacts: ["three.module.js", "three.core.js"],
  },
}, null, 2)}\n`);

console.log(`Vendored three ${metadata.version} (${metadata.license}).`);
