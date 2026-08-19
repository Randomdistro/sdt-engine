# Public Site Route and Deletion-Approval Ledger

Date: 2026-08-16  
Authoring tree: `Release/HTML_SDT_Website/`  
Published mirror: `docs/`

## Baseline

The pre-change public-site audit reported:

```text
SITE AUDIT FAILED: 76 errors, 0 warnings
```

The 76 errors decomposed exactly as follows:

- 34 legacy Atlas fragments in the authoring tree and the same 34 in `docs/`.
- Four additional legacy `index.html#irreducibles` fragments in the older `docs/welcome.html`.
- One obsolete attribution in the older `docs/welcome.html`.
- Three mirror drifts: `index.html`, `walk.js`, and `welcome.html`.

The 34 authoring-tree fragment repairs were:

- `atomicus-3d.html`: `index.html#atomicus` → `atlas.html#atomicus`
- `atomicus-lab-subdued.html`: `index.html#lab` → `atlas.html#lab`
- `atomicus-lab.html`: `index.html#lab` → `atlas.html#lab`
- `atomicus-stick.html`: `index.html#lab` → `atlas.html#lab`
- `cq06-eclipse.html`: `index.html#cosmology` → `atlas.html#cosmology`
- `laws_scroller.html`: `index.html#irreducibles` → `atlas.html#irreducibles`
- `paper-01-foundations.html`: `index.html#medium` → `atlas.html#medium`
- `paper-02-particle-topology.html`: `index.html#topology` → `atlas.html#topology`
- `paper-03-electromagnetism.html`: `index.html#laws` → `atlas.html#laws`
- `paper-04-atomic-spectroscopy.html`: `index.html#lab` → `atlas.html#lab`
- `paper-05-nuclear.html`: `index.html#atomicus` → `atlas.html#atomicus`
- `paper-06-gravitation.html`: `index.html#cosmology` → `atlas.html#cosmology`
- `paper-07-cosmology.html`: `index.html#cosmology` → `atlas.html#cosmology`
- `paper-08-galactic.html`: `index.html#cosmology` → `atlas.html#cosmology`
- `paper-09-stellar.html`: `index.html#cosmology` → `atlas.html#cosmology`
- `paper-10-fluid.html`: `index.html#medium` → `atlas.html#medium`
- `paper-11-thermodynamics.html`: `index.html#laws` → `atlas.html#laws`
- `paper-12-condensed-matter.html`: `index.html#medium` → `atlas.html#medium`
- `paper-13-quantum-foundations.html`: `index.html#laws` → `atlas.html#laws`
- `paper-14-plasma-magnetism.html`: `index.html#topology` → `atlas.html#topology`
- `paper-15-optics.html`: `index.html#experiments` → `atlas.html#experiments`
- `paper-16-chemistry.html`: `index.html#atomicus` → `atlas.html#atomicus`
- `paper-atomicus.html`: `index.html#atomicus` → `atlas.html#atomicus`
- `paper-cosmology.html`: `index.html#cosmology` → `atlas.html#cosmology`
- `paper-engine.html`: `index.html#engine` → `atlas.html#engine`
- `paper-experiments.html`: `index.html#experiments` → `atlas.html#experiments`
- `paper-glossary.html`: `index.html#glossary` → `atlas.html#glossary`
- `paper-lab.html`: `index.html#lab` → `atlas.html#lab`
- `paper-laws.html`: `index.html#laws` → `atlas.html#laws`
- `paper-medium.html`: `index.html#medium` → `atlas.html#medium`
- `paper-topology.html`: `index.html#topology` → `atlas.html#topology`
- `sdt-for-people.html`: `index.html#irreducibles` → `atlas.html#irreducibles`
- `st_00_primitives.html`: `index.html#irreducibles` → `atlas.html#irreducibles`
- `st_gom_gravity.html`: `index.html#topology` → `atlas.html#topology`

Links that meant “start or continue the path,” rather than “open the Atlas,” now use the appropriate `index.html#ix-*` anchor. This includes the former `welcome.html` and `sdt_walkthrough.html` inbound links.

## Current route inventory

There are 83 top-level HTML files in each public tree:

- 71 active/indexed routes.
- 11 retained compatibility routes, all `noindex`, canonicalized, redirected, and excluded from search and sitemap.
- One `noindex` error route: `404.html`.

Canonical front door:

- `index.html`

Labelled reference room:

- `atlas.html`

Other active/indexed routes:

- `aps01_scroller.html`
- `aps02_scroller.html`
- `atomicus-3d.html`
- `atomicus-fission-impact.html`
- `atomicus-lab.html`
- `benchmarks.html`
- `benchmarks_scroller.html`
- `causal-chain-simple.html`
- `causal-chain-technical.html`
- `causal-chain.html`
- `clearing-ladder.html`
- `cq06-eclipse.html`
- `depth_closure_scroller.html`
- `downloads.html`
- `emc01_scroller.html`
- `experiments.html`
- `flm01_scroller.html`
- `flm02_scroller.html`
- `inputs.html`
- `investigations.html`
- `koppa-ladder.html`
- `laws_scroller.html`
- `licence.html`
- `nuclear-packing-sequencer.html`
- `nuclear-packing-walkthrough.html`
- `paper-01-foundations.html`
- `paper-02-particle-topology.html`
- `paper-03-electromagnetism.html`
- `paper-04-atomic-spectroscopy.html`
- `paper-05-nuclear.html`
- `paper-06-gravitation.html`
- `paper-07-cosmology.html`
- `paper-08-galactic.html`
- `paper-09-stellar.html`
- `paper-10-fluid.html`
- `paper-11-thermodynamics.html`
- `paper-12-condensed-matter.html`
- `paper-13-quantum-foundations.html`
- `paper-14-plasma-magnetism.html`
- `paper-15-optics.html`
- `paper-16-chemistry.html`
- `paper-atomicus.html`
- `paper-cosmology.html`
- `paper-engine.html`
- `paper-experiments.html`
- `paper-glossary.html`
- `paper-lab.html`
- `paper-laws.html`
- `paper-medium.html`
- `paper-topology.html`
- `ppt01_scroller.html`
- `ppt02_scroller.html`
- `ppt04_scroller.html`
- `ppt05_scroller.html`
- `ppt06_scroller.html`
- `sdt-for-people.html`
- `solar-system.html`
- `st_00_primitives.html`
- `st_01_law1.html`
- `st_02_law2.html`
- `st_03_law3.html`
- `st_04_law4.html`
- `st_flm01.html`
- `st_gom_gravity.html`
- `st_magic_numbers.html`
- `st_paradox_census.html`
- `st_ring_moons.html`
- `theoretical-model.html`
- `universe-lifecycle.html`

Retained compatibility routes:

- `welcome.html` → `index.html`
- `sdt_walkthrough.html` → `index.html`
- `atomicus-lab-subdued.html` → `atomicus-lab.html`
- `atomicus-lab-v4-tiers.html` → `atomicus-lab.html`
- `atomicus-v1-snapshot.html` → `atomicus-3d.html`
- `atomicus-stick.html` → `atomicus-3d.html`
- `atomicus-stick-v3-polar-caps.html` → `atomicus-3d.html`
- `atomicus-construction-zone.html` → `atomicus-3d.html`
- `atomicus-nuclear-model.html` → `atomicus-3d.html`
- `monoisotopic-morph.html` → `atomicus-3d.html`
- `nuclear-packing-sequencer-raw.html` → `nuclear-packing-sequencer.html`

The nine superseded Atomicus/sequencer files retain their prior source after the redirect metadata. `welcome.html` and `sdt_walkthrough.html` are compatibility shells at their original paths. No HTML file was deleted.

## Deletion-approval ledger

Every item below requires separate explicit approval before deletion. Current approval state: **PENDING — RETAIN**.

- `Release/HTML_SDT_Website/welcome.html` and `docs/welcome.html`
- `Release/HTML_SDT_Website/sdt_walkthrough.html` and `docs/sdt_walkthrough.html`
- `Release/HTML_SDT_Website/atomicus-lab-subdued.html` and `docs/atomicus-lab-subdued.html`
- `Release/HTML_SDT_Website/atomicus-lab-v4-tiers.html` and `docs/atomicus-lab-v4-tiers.html`
- `Release/HTML_SDT_Website/atomicus-v1-snapshot.html` and `docs/atomicus-v1-snapshot.html`
- `Release/HTML_SDT_Website/atomicus-stick.html` and `docs/atomicus-stick.html`
- `Release/HTML_SDT_Website/atomicus-stick-v3-polar-caps.html` and `docs/atomicus-stick-v3-polar-caps.html`
- `Release/HTML_SDT_Website/atomicus-construction-zone.html` and `docs/atomicus-construction-zone.html`
- `Release/HTML_SDT_Website/atomicus-nuclear-model.html` and `docs/atomicus-nuclear-model.html`
- `Release/HTML_SDT_Website/monoisotopic-morph.html` and `docs/monoisotopic-morph.html`
- `Release/HTML_SDT_Website/nuclear-packing-sequencer-raw.html` and `docs/nuclear-packing-sequencer-raw.html`

## Files changed by this consolidation run

The following 58 public relative paths changed in `Release/HTML_SDT_Website/` and were mirrored byte-for-byte to the same paths under `docs/`:

- `.htaccess`
- `404.html`
- `atlas.html`
- `atomicus-3d.html`
- `atomicus-construction-zone.html`
- `atomicus-lab-subdued.html`
- `atomicus-lab-v4-tiers.html`
- `atomicus-lab.html`
- `atomicus-nuclear-model.html`
- `atomicus-stick-v3-polar-caps.html`
- `atomicus-stick.html`
- `atomicus-v1-snapshot.html`
- `causal-chain.html`
- `cq06-eclipse.html`
- `experiments.html`
- `index.html`
- `laws_scroller.html`
- `monoisotopic-morph.html`
- `nuclear-packing-sequencer-raw.html`
- `nuclear-packing-sequencer.html`
- `nuclear-packing-walkthrough.html`
- `paper-01-foundations.html`
- `paper-02-particle-topology.html`
- `paper-03-electromagnetism.html`
- `paper-04-atomic-spectroscopy.html`
- `paper-05-nuclear.html`
- `paper-06-gravitation.html`
- `paper-07-cosmology.html`
- `paper-08-galactic.html`
- `paper-09-stellar.html`
- `paper-10-fluid.html`
- `paper-11-thermodynamics.html`
- `paper-12-condensed-matter.html`
- `paper-13-quantum-foundations.html`
- `paper-14-plasma-magnetism.html`
- `paper-15-optics.html`
- `paper-16-chemistry.html`
- `paper-atomicus.html`
- `paper-cosmology.html`
- `paper-engine.html`
- `paper-experiments.html`
- `paper-glossary.html`
- `paper-lab.html`
- `paper-laws.html`
- `paper-medium.html`
- `paper-topology.html`
- `sdt-canon.js`
- `sdt-for-people.html`
- `sdt-shell.js`
- `sdt_walkthrough.html`
- `search-index.json`
- `sitemap.xml`
- `st_00_primitives.html`
- `st_gom_gravity.html`
- `theoretical-model.html`
- `universe-lifecycle.html`
- `walk.js`
- `welcome.html`

Non-public tooling and record changes:

- `Release/build_search_index.py`
- `Release/verify_public_site.py`
- `Release/SITE_ROUTE_LEDGER.md`

## Verification

Search rebuild:

```text
Release/HTML_SDT_Website: 71 pages
docs: 71 pages
```

Final public-site audit:

```text
PASS  public-site audit: 166 pages, 1646 local references, 0 warnings
```

`node --check` completed with exit code 0 for:

- `Release/HTML_SDT_Website/sdt-shell.js`
- `Release/HTML_SDT_Website/sdt-canon.js`
- `Release/HTML_SDT_Website/walk.js`

No requested site gate remains failing. Unrelated repository suites were not run.

## 2026-08-17 complete-theory amalgamation

### Archive gate

Before any live route was shortened, exact Release and docs copies of
`index.html`, `welcome.html`, `causal-chain.html`, and `atlas.html` were copied
to `_archive/Website/2026-08-17/theory-amalgamation/{release,docs}/`.
All eight source/archive pairs passed byte-identity verification.

- `atlas.html`: `ca512fc769d12fdebe61f8e76a23b5ea2f1cbd1ad1239f82c0857a44bd7a0ee9`
- `causal-chain.html`: `1b2f748511c1b3920e7ef968533b4645d4d8ace3f22e1bb73168e18191365043`
- `index.html`: `3d288857ca1ca41a453b0a79cafcdf6e4098763f6fadcbbbce463c9a5ce4a73f`
- `welcome.html`: `327568884b3c97c94735d818614375d021073d66b9ec449f947d924a095e39a4`

The Release and docs hashes are equal for each relative path. The corresponding
manifest rows name `theory.html` as the active successor.

### Active route roles

- `index.html`: concise indexed front door.
- `theory.html`: canonical complete dependency chain.
- `causal-chain-simple.html`: retained newcomer register.
- `causal-chain-technical.html`: retained technical register.
- `welcome.html`, `causal-chain.html`, `atlas.html`: noindex compatibility
  routes to `theory.html`, with fragment mapping supplied by
  `theory-redirect.js`.

The previous Atlas fragment contract is preserved on `theory.html`:
`#irreducibles`, `#medium`, `#laws`, `#topology`, `#atomicus`, `#lab`,
`#engine`, `#cosmology`, `#experiments`, and `#glossary`. The causal
`#L0` through `#L20` contract is also preserved.

### Dependency contract

`theory-dependencies.json` is the machine-readable L0–L20 graph.
Every step declares its prerequisites, products and status. The site verifier
rejects missing nodes, duplicate nodes, forward references, cycles,
HTML/manifest drift, and missing compatibility anchors.

L17–L19 contain the expanded celestial-mechanics ladder: two-body conics and
invariants; mutual and three-body motion; rotating frames; tides, synchronous
and Hill-like boundaries; perturbations, secular evolution, planetary systems,
stellar binaries, galaxies, and the transition into the cyclic cosmological
account.

### Deletion state

No tracked public route was deleted. The four predecessor pages remain
byte-preserved in the archive, and their original live paths remain as either
the front door or compatibility routes.

## 2026-08-18 rejected reification — charge

Active public trees (`Release/HTML_SDT_Website/`, `docs/`) no longer use
`charge` / `charged` / `charges` / `charging` as SDT vocabulary. Rewrites use
circulation direction, boundary radius, ionisation state, proton count Z,
occlusion geometry, and pressure response. No substitute substance noun was
introduced.

Exceptions retained as verbatim:

- third-party MIT licence wording (`vendor/THREE-LICENSE.txt`)
- exported engine header `dist/laws.hpp` (propose-and-wait canon)
- investigation folder and filename strings that are filesystem identity

The binding rule is `GATEWAY_BEHAVIOURAL.md` §1. The public-site gate is
`audit_charge_terminology()` in `Release/verify_public_site.py`.

Final public-site audit after the terminology pass:

```text
PASS  public-site audit: 172 pages, 1642 local references, 0 warnings
```
