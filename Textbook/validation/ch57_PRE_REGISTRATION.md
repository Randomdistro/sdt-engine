# Chapter 57 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch57_engine_law_reference.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The executable reference as a frozen source snapshot. (a) Traceability: the SHA-256 of every consumed header in `Engine/include/sdt/`, with the repository revision and the working-tree condition recorded; source hashing establishes traceability, not physical correctness. (b) Citations: every `header.hpp:NNN` reference in the manuscript tree must resolve to an existing, non-blank line of the named header in the snapshot; the references to `laws.hpp:99` (the stored $\ell_P$ that carries $G$) must land on the line that defines `l_P`. (c) Function domains: header functions evaluate outside their physical domain unless the caller checks: `depth_closure::clock_rate` ($0\le z\le1$), `law_V::gamma` and `law_V::v_circ` ($|v|\le c$), `depth_closure::depth_from_c_far`, `bridge::circular_speed_from_koppa` (positive radius); `bridge::g_interior` has a numerical cutoff below 1 m that returns $0$ and is an implementation choice, not an analytic limit. (d) Inventory: the top-level namespaces named in the principal map (`measured`, `law_I`…`law_VI`, `bridge`, `atomic`, `nuclear`, `depth_closure`) exist in `laws.hpp`. Inputs: the files themselves; no physical value is read.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | SHA-256("abc") $=$ `ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad`; SHA-256("") $=$ `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`; a 56-character message across a block boundary: SHA-256("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") $=$ `248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1`; the line counter returns 3 for `"a\nb\nc\n"` | exact |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | hashes. 14 headers are hashed in `Engine/include/sdt/`; hashing a file twice gives the same digest; the 14 digests are pairwise distinct; the revision (`git rev-parse --short HEAD`) and the working-tree state of `Engine/include/sdt` (`git status --porcelain`) are printed | as stated | yes |
| T2 | citations. Every `name.hpp:NNN` occurrence under `Textbook/volume_*/` and `Textbook/equations/` with `name` among the 14 headers resolves to a line $\le$ the file's length that is non-blank; at least 25 such citations are found; every `laws.hpp:99` citation lands on a line containing `l_P` | as stated | yes |
| T3 | domains. `clock_rate(1.5)<0`; `clock_rate(-0.1)>1`; `gamma(1.1c)` and `v_circ(1.2c)` are NaN; `depth_from_c_far(1.5c_\infty,c_\infty)` is NaN; `circular_speed_from_koppa(1,-1)` is NaN; `g_interior` returns exactly $0$ at $r=0.5$ m and a nonzero value at $r=2$ m, for the same uniform-density enclosed fraction $(r/R)^3$ | as stated | yes |
| T4 | inventory. Each of the 11 principal namespaces appears as a top-level `namespace NAME {` line in `laws.hpp`; the counts of `[[nodiscard]]` functions and of `inline constexpr double` constants in `laws.hpp` are reported | as stated | yes |

Reported, not criteria: the digests, the revision, the counts, the citation list.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch57_engine_law_reference`

## Record of run 1; one registered statement rejected (2026-11-10)

Run 1 (`ch57_run1_output.txt`): every criterion was met except one. The registered statement "`depth_from_c_far(1.5 c, c)` is NaN" is **rejected**: the function is $1-\sqrt{c_{\rm far}/c_\infty}$, which for $c_{\rm far}=1.5c_\infty$ is the finite negative value $-0.2247$, not NaN (NaN would need a negative argument of the square root, i.e. $c_{\rm far}<0$). The registration assumed a square root of a negative number where the argument is positive; it is a registration error and the criterion is not retuned. Run 2 asserts the rejection and adds, **post-run and marked as such**, two clauses: `depth_from_c_far(1.5c, c)` is negative (a depth below zero is returned without rejection), and `depth_from_c_far(-0.1c, c)` is NaN. Findings of run 1 that stand: the 14 digests, the revision `7b49eb7`, and the working-tree listing showing that `occlusion_sphere.hpp` and `sphere_frame.hpp` are untracked (not in the revision), so the revision alone does not identify those two consumed headers; 65 citations resolved with none unresolved and the 7 `laws.hpp:99` citations all on the `l_P` line. Run 2 is the run of record.

## Record of run 3; repeat after the manuscript review (2026-11-16)

Run 3 (`ch57_run3_output.txt`): instrument and criteria unchanged; every criterion met. The 14 header digests and line counts are identical to run 2. The citation count is 66 with 8 on the `l_P` line (run 2: 65 and 7). The difference has two parts: the text of Chapter 57 itself, written after run 2, contains two `laws.hpp:99` citations (+2); and the review of 2026-11-16 removed one `laws.hpp:99` citation from the Chapter 45 input ledger (−1), where the stored $\ell_P$ had been named as an input of `bridge::koppa_Sun`, which is $R_\odot/k_\odot^2$ and does not contain it. Run 3 is the run of record; runs 1 and 2 are kept.
