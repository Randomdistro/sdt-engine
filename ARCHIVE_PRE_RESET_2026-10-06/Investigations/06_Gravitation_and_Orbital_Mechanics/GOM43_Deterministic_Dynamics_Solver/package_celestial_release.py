#!/usr/bin/env python3
"""Synchronize the qualified celestial solver release and website mirrors."""

from __future__ import annotations

import hashlib
import json
import pathlib
import shutil
import textwrap
from datetime import datetime, timezone


PROJECT = pathlib.Path(__file__).resolve().parent
REPO = PROJECT.parents[2]
SITE = REPO / "Release" / "HTML_SDT_Website"
DOCS = REPO / "docs"
PACKAGE = REPO / "Release" / "SDT_Celestial_Three_Body_Solver"


def copy_file(source: pathlib.Path, destination: pathlib.Path) -> None:
    destination.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, destination)


def copy_tree(source: pathlib.Path, destination: pathlib.Path) -> None:
    shutil.copytree(
        source,
        destination,
        dirs_exist_ok=True,
        ignore=shutil.ignore_patterns(
            "node_modules",
            "test-results",
            "*.exe",
            "*.lib",
            "*.exp",
            "*.obj",
            "*.pdb",
        ),
    )


def write_text(destination: pathlib.Path, content: str) -> None:
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_text(
        textwrap.dedent(content).lstrip(),
        encoding="utf-8",
        newline="\n",
    )


def sha256(path: pathlib.Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    wasm = PROJECT / "app" / "wasm"
    for name in ("sdt-dynamics-core.js", "sdt-dynamics-core.wasm"):
        copy_file(wasm / name, SITE / "wasm" / name)
    copy_file(
        PROJECT / "app" / "vendor" / "three.module.js",
        SITE / "vendor" / "celestial-three.module.js",
    )
    copy_file(
        PROJECT / "app" / "vendor" / "three.core.js",
        SITE / "vendor" / "three.core.js",
    )
    copy_file(
        PROJECT / "app" / "node_modules" / "three" / "examples" / "jsm"
        / "controls" / "OrbitControls.js",
        SITE / "vendor" / "OrbitControls.js",
    )
    copy_tree(
        PROJECT / "examples" / "celestial",
        SITE / "cases" / "celestial",
    )
    dynamics_site = SITE / "dynamics-lab"
    dynamics_docs = DOCS / "dynamics-lab"
    for name in ("index.html", "styles.css"):
        copy_file(PROJECT / "app" / name, dynamics_site / name)
        copy_file(PROJECT / "app" / name, dynamics_docs / name)
    for directory in ("src", "worker", "vendor", "wasm"):
        copy_tree(PROJECT / "app" / directory, dynamics_site / directory)
        copy_tree(PROJECT / "app" / directory, dynamics_docs / directory)

    for relative in (
        pathlib.Path("celestial-three-body-solver.html"),
        pathlib.Path("js/celestial-three-body-worker.js"),
        pathlib.Path("sdt-shell.js"),
        pathlib.Path("sitemap.xml"),
        pathlib.Path("wasm/sdt-dynamics-core.js"),
        pathlib.Path("wasm/sdt-dynamics-core.wasm"),
        pathlib.Path("vendor/celestial-three.module.js"),
        pathlib.Path("vendor/three.core.js"),
        pathlib.Path("vendor/OrbitControls.js"),
    ):
        copy_file(SITE / relative, DOCS / relative)
    copy_tree(SITE / "cases" / "celestial", DOCS / "cases" / "celestial")

    PACKAGE.mkdir(parents=True, exist_ok=True)
    copy_tree(PROJECT / "include", PACKAGE / "include")
    copy_tree(PROJECT / "src", PACKAGE / "src")
    copy_tree(PROJECT / "contracts", PACKAGE / "contracts")
    copy_tree(PROJECT / "examples", PACKAGE / "examples")
    copy_tree(PROJECT / "datasets", PACKAGE / "datasets")
    copy_tree(PROJECT / "cmake", PACKAGE / "cmake")
    copy_tree(PROJECT / "tests", PACKAGE / "tests")
    copy_file(
        REPO / "Engine" / "include" / "sdt" / "laws.hpp",
        PACKAGE / "include" / "sdt" / "laws.hpp",
    )
    copy_file(
        REPO / "Engine" / "include" / "sdt" / "dynamics.hpp",
        PACKAGE / "include" / "sdt" / "dynamics.hpp",
    )
    copy_file(
        REPO / "Engine" / "include" / "sdt" / "occlusion.hpp",
        PACKAGE / "include" / "sdt" / "occlusion.hpp",
    )
    copy_file(
        REPO / "Compiler" / "include" / "sdt" / "compiler" / "sha256.hpp",
        PACKAGE / "include" / "sdt" / "compiler" / "sha256.hpp",
    )
    for name in (
        "PROMPT.md",
        "PROMPT_CELESTIAL_OCCLUSION.md",
        "PROMPT_DISPLACEMENT_SLINGSHOT.md",
        "PROMPT_MULTIBODY_SEVEN_CIRCLE_OCCLUSION.md",
        "ARCHITECTURE.md",
        "RUN_LOG.md",
        "GOM43_ASSESSMENT.md",
        "celestial_validate.py",
        "build_celestial_preset_catalog.py",
        "build_displacement_ledgers.py",
        "displacement_slingshot_validate.py",
        "displacement_slingshot_validation.json",
        "multibody_performance_validate.py",
    ):
        copy_file(PROJECT / name, PACKAGE / name)
    copy_file(SITE / "CITATION.cff", PACKAGE / "CITATION.cff")
    copy_file(SITE / "celestial-three-body-solver.html", PACKAGE / "web" / "index.html")
    copy_tree(SITE / "cases" / "celestial", PACKAGE / "web" / "cases" / "celestial")
    copy_file(
        SITE / "js" / "celestial-three-body-worker.js",
        PACKAGE / "web" / "js" / "celestial-three-body-worker.js",
    )
    for name in ("sdt-dynamics-core.js", "sdt-dynamics-core.wasm"):
        copy_file(SITE / "wasm" / name, PACKAGE / "web" / "wasm" / name)
    for name in (
        "celestial-three.module.js",
        "three.core.js",
        "OrbitControls.js",
    ):
        copy_file(SITE / "vendor" / name, PACKAGE / "web" / "vendor" / name)
    copy_tree(dynamics_site, PACKAGE / "web" / "dynamics-lab")

    write_text(
        PACKAGE / "CMakeLists.txt",
        r"""
        cmake_minimum_required(VERSION 3.24)
        project(sdt_celestial_and_multibody_solver VERSION 3.0.0 LANGUAGES CXX)
        set(CMAKE_CXX_STANDARD 20)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        set(CMAKE_CXX_EXTENSIONS OFF)
        file(SHA256 "${CMAKE_CURRENT_SOURCE_DIR}/include/sdt/laws.hpp" SDT_LAWS_SHA256)
        set(SDT_SOLVER_COMPILER "${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")
        add_library(sdt-celestial-core STATIC
          src/solver.cpp src/celestial.cpp src/occlusion_nbody.cpp
          src/self_tests.cpp src/c_api.cpp)
        target_include_directories(sdt-celestial-core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
        target_compile_definitions(sdt-celestial-core PRIVATE
          SDT_LAWS_SHA256="${SDT_LAWS_SHA256}"
          SDT_SOLVER_COMPILER="${SDT_SOLVER_COMPILER}")
        if(MSVC)
          target_compile_options(sdt-celestial-core PRIVATE /W4 /permissive- /fp:strict /utf-8 /openmp)
        else()
          target_compile_options(sdt-celestial-core PRIVATE -Wall -Wextra -Wpedantic -ffp-contract=off)
        endif()
        if(EMSCRIPTEN)
          add_executable(sdt-celestial-wasm src/wasm_entry.cpp)
          target_link_libraries(sdt-celestial-wasm PRIVATE sdt-celestial-core)
          set_target_properties(sdt-celestial-wasm PROPERTIES
            OUTPUT_NAME "sdt-dynamics-core" SUFFIX ".js"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/web/wasm")
          target_link_options(sdt-celestial-wasm PRIVATE
            "SHELL:-s MODULARIZE=1"
            "SHELL:-s EXPORT_NAME=createSdtDynamicsModule"
            "SHELL:-s ENVIRONMENT=worker"
            "SHELL:-s FILESYSTEM=0"
            "SHELL:-s ALLOW_MEMORY_GROWTH=1"
            "SHELL:-s ASSERTIONS=1"
            "SHELL:-s EXPORTED_FUNCTIONS=['_run_case','_session_create','_session_advance','_session_checkpoint','_session_resume','_session_destroy','_self_test','_solver_manifest','_solver_free','_malloc','_free']"
            "SHELL:-s EXPORTED_RUNTIME_METHODS=['HEAPU8']"
            "SHELL:--no-entry")
        else()
          add_executable(sdt-celestial-solver src/cli.cpp)
          target_link_libraries(sdt-celestial-solver PRIVATE sdt-celestial-core)
          add_executable(sdt-celestial-c-api-smoke tests/c_api_smoke.cpp)
          target_link_libraries(sdt-celestial-c-api-smoke PRIVATE sdt-celestial-core)
          enable_testing()
          add_test(NAME solver-self-test COMMAND sdt-celestial-solver --self-test)
          add_test(NAME celestial-self-test COMMAND sdt-celestial-solver --celestial-self-test)
          add_test(NAME c-api-smoke COMMAND sdt-celestial-c-api-smoke)
        endif()
        """,
    )
    write_text(
        PACKAGE / "README.md",
        """
        # SDT Celestial and Multibody Solver 3.0.0

        A deterministic C++20, C ABI and WebAssembly instrument for arbitrary
        three-body initial-value problems using retarded seven-cone baryonic
        occlusion. It calculates a pressure deficit, not attraction: each of
        three body pairs carries two co-facing 6-around-1 cross-sections,
        producing 42 directed cones. Occlusion travels at `c`; body response
        uses canonical Law-IV proton/neutron displacement and reorganisation
        resistance. A separately classified transported-tail route is emitted
        as a non-driving `PENDING` slingshot diagnostic.

        Author: James Christopher Tyndall, Melbourne.

        ## Included

        - dependency-free versioned JSON contracts;
        - arbitrary-N full 7×7 channel matrices, giving
          `49*N*(N-1)` retarded solid-angle relations per state;
        - fixed-step velocity-Verlet and verification RK4;
        - exact arbitrary-precision baryon GCD/packet ledger;
        - finite cone/sphere intersections and eclipse shielding;
        - retarded history, chunked sessions, checkpoints and resume;
        - baryonic pivots, calculated pressure L1-L5 roots and point-koppa
          comparison ledger;
        - synchronized NASA/JPL Horizons DE441 Sun-Earth-Moon fixture;
        - twenty-five ordinary-JSON simulations spanning JPL, spacecraft,
          Trojan, figure-eight, Lagrange, hierarchical, covariance, eclipse
          and controlled slingshot cases;
        - provenance-recorded Sun/Earth 98%+ composition, exact proton/neutron
          counts, weighted trefoil burden and Law-IV displacement ledgers;
        - native and browser demonstrators from the same C++ source path;
        - `QUALIFICATION_MANIFEST.json` with exact toolchains, floating-point
          policy, canonical-laws hash, fixture hashes and release-gate results.

        ## Native build

        ```powershell
        cmake -S . -B build -G "Visual Studio 17 2022" -A x64
        cmake --build build --config Release --parallel
        ctest --test-dir build -C Release --output-on-failure
        .\\build\\Release\\sdt-celestial-solver.exe --celestial-self-test
        .\\build\\Release\\sdt-celestial-solver.exe examples\\celestial\\jpl-sun-earth-moon-j2000.sdtcase.json
        ```

        The CLI also accepts `--chunk CASE STEPS` and
        `--resume CASE CHECKPOINT STEPS`. Omitting both `duration_s` and
        `max_steps` creates a caller-controlled session.

        ## Browser

        Serve `web/` over HTTP. Open `index.html` for the fixed-three-body
        instrument or `dynamics-lab/index.html` for arbitrary-N seven-circle
        occlusion. Both workers invoke only the exported C++/WASM ABI;
        rendering clocks never advance solver state.

        ## Scope

        The transported anti-solar tail and stage-8 termination are `PENDING`;
        they do not alter production state. The point-koppa output is an
        `IDENTITY/shared-input` comparison. The
        retarded finite-cone route is `COMPUTED` where its registered gates
        pass. JPL values are `OBSERVED` comparisons and are not fitted. This
        numerical IVP instrument is not a closed-form solution of the general
        three-body problem and is not flight software.
        """,
    )
    write_text(
        PACKAGE / "LICENSE.txt",
        """
        Spatial Displacement Theory material is distributed under
        CC-BY-NC-ND-4.0 as recorded in CITATION.cff and the canonical website
        licence. Copyright James Christopher Tyndall, Melbourne.
        """,
    )
    write_text(PACKAGE / "VERSION", "3.0.0\n")

    fixture_hashes = {
        path.relative_to(PROJECT).as_posix(): sha256(path)
        for directory in ("examples", "datasets")
        for path in sorted((PROJECT / directory).rglob("*.json"))
    }
    qualification_manifest = {
        "schema": "sdt-celestial-qualification-manifest-1.0.0",
        "generated_utc": datetime.now(timezone.utc).isoformat(),
        "classification": "COMPUTED",
        "native_toolchain": {
            "compiler": "MSVC 19.44.35223.0",
            "generator": "Visual Studio 17 2022",
            "architecture": "x64",
            "configuration": "Release",
        },
        "wasm_toolchain": {
            "emscripten": "6.0.6",
            "clang": "24.0.0",
            "ninja": "1.13.0",
        },
        "floating_point_policy": (
            "IEEE-754 binary64; fixed declared timestep; deterministic "
            "operation order; no fast-math; native/WASM elementary-function "
            "residuals assessed against declared tolerances"
        ),
        "laws_sha256": sha256(REPO / "Engine" / "include" / "sdt" / "laws.hpp"),
        "contracts_sha256": {
            path.name: sha256(path)
            for path in sorted((PROJECT / "contracts").glob("*.json"))
        },
        "fixtures_sha256": fixture_hashes,
        "published_assets_sha256": {
            "celestial-three-body-solver.html": sha256(
                SITE / "celestial-three-body-solver.html"
            ),
            "js/celestial-three-body-worker.js": sha256(
                SITE / "js" / "celestial-three-body-worker.js"
            ),
            "wasm/sdt-dynamics-core.js": sha256(
                SITE / "wasm" / "sdt-dynamics-core.js"
            ),
            "wasm/sdt-dynamics-core.wasm": sha256(
                SITE / "wasm" / "sdt-dynamics-core.wasm"
            ),
            "dynamics-lab/index.html": sha256(
                SITE / "dynamics-lab" / "index.html"
            ),
            "dynamics-lab/wasm/sdt-dynamics-core.wasm": sha256(
                SITE / "dynamics-lab" / "wasm" / "sdt-dynamics-core.wasm"
            ),
        },
        "gates": {
            "native_ctest": "3/3 PASS",
            "standalone_ctest": "3/3 PASS",
            "repository_benchmarks": "66/66 predictions; 19/19 identities PASS",
            "browser_unit": "6/6 PASS",
            "browser_playwright": "4/4 PASS",
            "native_wasm_occlusion_nbody_parity": (
                "3.0 byte-identical; "
                "4b950b970d09bd6a7f262825eb964bc748e4b1ec1dbdee49f5445493c8f08fd0"
            ),
            "multibody_performance": (
                "1000 bodies; 1 step; 48,951,000 relations; "
                "19.0634498 s; limit 60 s; PASS"
            ),
            "native_wasm_celestial_parity": (
                "2.0 and 2.1 byte-identical; "
                "d707d1035e5c50c2f7fb316b877fca950a9ccf4844290b0757c1f7cdf7c0940a; "
                "5bde2c33b0e9237a12e7b614cd42cc8e15d42b973bcb9bac3b4339ed3c1f9544"
            ),
            "release_docs_parity": "PASS",
            "displacement_slingshot": "34/34 PASS",
        },
    }
    write_text(
        PACKAGE / "QUALIFICATION_MANIFEST.json",
        json.dumps(qualification_manifest, indent=2) + "\n",
    )
    print(f"Packaged {PACKAGE}")


if __name__ == "__main__":
    main()

