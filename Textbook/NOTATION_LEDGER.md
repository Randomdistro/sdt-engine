# Notation ledger — circulation-boundary symbols

Opened 2026-10-27. Two quantities and one derived ratio are in play:

- **length** — the circular c-boundary length, $R/k^2 = v_{\rm circ}^2R/c^2$, metres;
- **ratio** — the speed ratio $c/v$, dimensionless;
- **depth** — $z_{\rm depth}$ = length / $r$ = 1 / ratio², dimensionless.

Five sources assign symbols to these three. They do not agree.

| source | length | ratio | depth | note |
|---|---|---|---|---|
| Engine `laws.hpp` (lines 1020, 1039, 1289–1290) | **ϟ** ("koppa") | **k** | — | `koppa(v,R) = v²R/c²`; comment at 1289 states that $k$, not ϟ, is the dimensionless ratio |
| `Theory/00_Ruleset.md` T17, `Theory/04_Notation.md` | **ℶ** (beth) | **k** | $z$, $z k^2 = 1$ | `04_Notation.md` line 20 writes ℶ $= GM/c^2$; $GM$ is an output of the koppa structure, not an input (Behavioural §3.8) |
| Textbook plan of 2026-10-27 (pasted; Chapters 1–3, 33) | **Om** | **Ϟ** | $z_{\rm depth}$ | ${\rm Om} = R/Ϟ^2$; $Ϟ^2 = r/{\rm Om}$ |
| `docs/SDT_TEXTBOOK_ARCHITECTURE.md` (2026-10-27) | lower-case **ѻ** (om) | upper-case **Ѻ** (Om) | $z_{\rm depth}=ѻ/r$ | states that it follows the "current Operator convention" and that the Spaz investigation's assignments are older |
| Recorded direction of 2026-10-09 (project memory) | **Ѻ** (Om) | — | — | "R/k² is Ѻ (Om), not ϟ"; files still mix symbols |

## Collisions

1. **ϟ** is the length in the engine and Ϟ is the ratio in the pasted plan; they differ by case only.
2. **Ѻ** is the ratio in `docs/SDT_TEXTBOOK_ARCHITECTURE.md` and the length in the 2026-10-09 direction.
3. **Om** is the length in the pasted plan and the ratio in `docs/SDT_TEXTBOOK_ARCHITECTURE.md` (as upper-case Ѻ).
4. **z** is both $z_{\rm depth}$ and the spectral shift $z_{\rm spec}$; both plans already separate them.

## Status

Chapters 1–3 and 33 as drafted use the pasted-plan column. Chapter 4 uses none of these symbols (it concerns throughput, not circulation), so it is unaffected. Chapters 25 onward need one assignment. The decision belongs to the author; until it is made, no source file is renamed and each chapter states which column it uses in its first line.

## Production default for Chapters 1–64 (applied 2026-11-03)

The author's ruling on the collisions above is not on record, and the edition is being completed without waiting for it. The production default follows the supplied brief (the pasted plan, whose Section 3 states that it controls this edition) and the 2026-10-09 direction that R/k² is Ѻ (Om); the two agree on the length. The ratio is written with the engine's symbol.

| quantity | symbol in this edition | other columns |
|---|---|---|
| circular c-boundary length, $R/k^2=v_{\rm circ}^2R/c^2$ | $\mathrm{Om}$ | ϟ (engine), ℶ (Ruleset), ѻ (architecture note, continuation edition) |
| speed ratio $c/v$ | $k$ | k (engine, Ruleset), Ϟ (supplied brief), Om / Ѻ (architecture note, continuation edition) |
| geometric depth | $z_{\rm depth}=\mathrm{Om}/r$, equal to $1/k^2$ at $r=R$ | $z$, $z k^2=1$ |
| spectral shift | $z_{\rm spec}$ | $z$ |

Each chapter from 1 onward states this column in its first line. The change to any other column is a mechanical substitution through the table, so the choice can be reversed without rewriting an argument. No source file is renamed. The continuation edition in `Projects/sdt-investigations/Investigations/SDT_Textbook_Architecture_2026-10-27_2/continuation/` keeps its own stated amendment (om for the length, Om for the ratio) and is not altered.

## Ruling of 2026-11-03 on the depth (recorded 2026-11-09)

The author's correction of 2026-11-03 (clean-room track): the relay slowing, or any convergence depth, is not koppa over radius or GM/(c²r); it must come out of the model. The engine block `laws.hpp` ~2797–2836 and CONDENSA line 71 still state z = ϟ/r and are untouched (canon: propose-and-wait). In this edition $z_{\rm depth}=\mathrm{Om}/r$ is a *defined geometric ratio* (the supplied brief's notation) and is not asserted to be the relay slowing. Where a chapter evaluates the engine's depth-closure relations it states that the depth is the engine's and carries the residual (Chapter 3, R3.6).
