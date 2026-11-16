# GOM43 Multibody Seven-Circle Laboratory

Production browser application for the GOM43 deterministic dynamics solver.
The package is self-contained below this directory and does not depend on a
mutable CDN.

## Execution boundary

- Certified computation occurs only in `worker/solver-worker.js`, which calls
  the exported GOM43 C ABI in `wasm/sdt-dynamics-core.{js,wasm}`.
- The main thread edits cases, renders recorded states, plots diagnostics and
  exports bundles. `requestAnimationFrame` advances playback and redraws the
  viewport; it never advances solver state.
- Contract 3.0 advances caller-selected chunks through the session ABI.
  Checkpoint/resume retains retarded history and exact ledgers; Pause
  terminates the worker and discards its WebAssembly memory.
- `tests/fixtures/ui-only-result.json` is marked and consumed only by unit
  tests. No application source imports it and it is never a solver fallback.
- Arbitrary-N seven-circle runs carry `COMPUTED` after their registered gates.
  Contract 1 point N-body runs remain `VALIDATED` comparison fixtures. The
  open-chain RATTLE path carries `CONDITIONAL` under its case-declared local
  acceleration and GOM43 scope.
- The solver accepts up to 10,000 bodies. Above 64 bodies it bounds returned
  pair/channel detail while still computing and reporting all
  `49*N*(N-1)` relations, preventing millions of browser render objects.

## Application contents

- `index.html`, `styles.css`: accessible three-column laboratory shell.
- `src/app.js`: scene tree, arbitrary entity editing, presets, timeline,
  diagnostics, provenance, gates, imports, exports and share payloads.
- `src/renderer.js`: Three.js scene playback, inertial/rotating views, trails,
  vectors, joint/constraint overlays and the calculated selected-pair
  fourteen-circle/forty-nine-link occlusion matrix.
- `src/case-io.js`: dimensional case checks, portable URL payload and CSV.
- `src/worker-client.js`, `src/worker-protocol.js`: versioned worker lifecycle,
  status, cancellation and response validation.
- `worker/solver-worker.js`: UTF-8 allocation and release across the GOM43 C ABI.
- `vendor/`: pinned renderer modules, version record and upstream license.
- `wasm/`: Emscripten loader and binary built from the shared C++ core.
- `tests/`: Node unit tests, Playwright browser tests and static test server.

## Pinned assets

- Emscripten **6.0.6**, SDK release
  `833aa203ba2283fc2b6adb504a79a3a0d692df81`, Apache-2.0 with LLVM
  exceptions. Provisioned outside the repository at
  `C:\Users\Jimmi\.cache\emsdk-sdt-gom43`.
- Ninja **1.13.2**, Apache-2.0. Provisioned in the same external SDK cache.
- Three.js **0.185.1**, MIT. The deployed `three.module.js` and
  `three.core.js` plus `THREE-LICENSE.txt` are vendored locally.
- Playwright Test **1.62.1**, Apache-2.0, development/test dependency only.

`package-lock.json` pins the JavaScript dependency graph. `vendor/VERSIONS.json`
records the deployed renderer version. The SDK cache and `node_modules` are not
part of the source package.

## Rebuild

From the repository root in PowerShell:

```powershell
cd C:\Users\Jimmi\.cache\emsdk-sdt-gom43
.\emsdk.bat install 6.0.6
.\emsdk.bat install ninja-1.13.2-64bit
.\emsdk.bat activate 6.0.6

$env:EMSDK = "C:/Users/Jimmi/.cache/emsdk-sdt-gom43"
$env:PATH = "$env:EMSDK/upstream/emscripten;$env:EMSDK/ninja/1.13.2_64bit;$env:PATH"
cd C:\Users\Jimmi\OneDrive\Desktop\sdt-engine
cmake -S Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver `
  -B build-gom43-wasm-606 -G Ninja -DCMAKE_BUILD_TYPE=Release `
  "-DCMAKE_MAKE_PROGRAM=$env:EMSDK/ninja/1.13.2_64bit/ninja.exe" `
  "-DCMAKE_TOOLCHAIN_FILE=$PWD/Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/cmake/emscripten-toolchain.cmake"
cmake --build build-gom43-wasm-606 --parallel

cd Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/app
npm ci
npm run vendor
npx playwright install chromium
npm test
npm run test:parity -- C:\path\to\sdt-dynamics-solver.exe
```

CMake writes the deployable loader and binary directly to `app/wasm/`.
The parity harness runs contract 1 mechanics and contract 3 full 7×7
occlusion through native and WebAssembly builds, requiring matching
contracts/hashes and a maximum numeric relative residual of `2e-11`.

## Local use

Run `npm run serve` and open `http://127.0.0.1:4173`. A web server is required
because workers and WebAssembly cannot be validated from a `file:` URL.

## Publishing hand-off

Publish these paths unchanged as one directory, for example
`/dynamics-lab/`:

```text
index.html
styles.css
src/
worker/
vendor/
wasm/
```

Do not publish `node_modules/`, `scripts/`, `tests/`, `package*.json` or this
README. The final publishing worker can copy that deployable subset into
`Release/HTML_SDT_Website/dynamics-lab/`, mirror it to `docs/dynamics-lab/`,
then add the route, shell/search/sitemap entries and Pages build gates. All
application URLs are relative, so no source rewrite is needed at that path.

The host must serve `.wasm` as `application/wasm`. Keep
`sdt-dynamics-core.js` and `sdt-dynamics-core.wasm` from the same build. A
service worker or immutable cache policy must version them together.
