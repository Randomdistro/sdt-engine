# Repository navigation and ownership

## Active sources

| Location | Responsibility |
| --- | --- |
| `Engine/include/sdt/` | Executable definitions and numerical relations. |
| `Laws/`, `Theory/`, `28_Dimensional_Aspects/` | Theory and ontology sources; date and status determine applicability. |
| `Investigations/INVESTIGATION_STACK.md` | Research navigation and unresolved dependencies. |
| `Benchmarks/` | Numerical comparisons; identities and calibrated results remain separate from predictions. |
| `Datasets/` | Input observations and provenance. |
| `Audits/` | Reconciliation findings, limitations and review records. |
| `Release/HTML_SDT_Website/` | Sole website authoring tree. |
| `docs/` | Generated deployment mirror. Never edit independently. |
| `Release/` | Packaging, publication checks and standalone solver releases. |
| `_archive/` | Retained historical material. Historical results do not establish current canon. |
| `build*/`, `tmp/`, `run_outputs/` | Local compilation, scratch work and execution products. |

## Website maintenance

Run `python Release/build_site.py`, then `python Release/build_site.py --check`
and `python Release/verify_public_site.py`. The build refuses to discard files
found only in the deployment mirror. CI checks every mirrored file, rather than
only a hand-maintained subset.

Website explanations use complete sentences, named quantities and explicit
assumptions. Shared primitive definitions belong in `sdt-canon.js`. Demonstration
selection belongs in `demonstrations.html`; research animations are not evidence
of a solved contact law. Use links to the benchmark and input ledgers instead of
copying benchmark totals into new pages.

Keep measured inputs, proposed definitions, conditional derivations, calibration,
identities and independent predictions distinct. Record a superseded derivation
in `_archive/` before replacing an active explanation. Preserve investigation
paths and external solver checkouts until dependency-aware migrations exist.

Root README material below the current navigation notice is a historical release
account and contains superseded paths and claims.
