# Chapter 57 — Engine Law Reference

*Volume VIII — Executable Reference, Verification and Research Closure.*
Draft of 10 November 2026. Notation: a *citation* is a reference of the form `header.hpp:NNN` in the manuscript; a *digest* is the SHA-256 of a header file; "snapshot" is the set of 14 headers of `Engine/include/sdt/` on the date of the run. Executable companion: `Textbook/examples/ch57_engine_law_reference.cpp`; pre-registration and captured output in `Textbook/validation/`. The instrument reads source files only; no physical value is used.

## 57.1 Source symbols and revision

The executable reference is a frozen source snapshot, not a moving filename. The record is the SHA-256 of every consumed header, the repository revision and the working-tree condition. A repository revision alone is insufficient when uncommitted or untracked headers exist. Source hashing establishes traceability, not physical correctness.

The principal map: `law_I` for $u$, $\epsilon$, $N_{\rm shell}$, $\Phi$ and $P_{\rm conv}$; `law_II` for release reference quantities and pressure domains; `law_III` for effective interaction pressure and occlusion force; `law_IV` for resistance volume and transport; `law_V` for movement-budget response; `bridge` for circulation and baryon geometry; `atomic` and `nuclear` for structure; `law_VI` for winding; `depth_closure` for local length, tick-rate ratio and far-frame speed; `measured` for the external inputs.

**Executed (V1, T1).** The SHA-256 routine reproduced the three standard test vectors ("abc"; the empty string; the 56-character two-block message) and the line counter. The 14 headers, with line counts and digests of the snapshot of 2026-11-10:

```
cosmology.hpp         223  874bc6d832843cf9c7b131a3eaa0bcfce9fe0548a662042d41668f2ace46b90b
dynamics.hpp          340  878f6b276050310e43fdf7fee48eec89ac211d2e048a719b74210c122f5027ac
galactic.hpp         1516  051062058c8842ce378b439e2e62118cb3e5ae695023f3fa9bef6b836d757bf0
lattice_structure.hpp  74  12f8348a15088de709ec244f65b8a621abfc732252e0dea8f35bb103224a1e99
laws.hpp             2917  2154c01eb01ebab82daf8ea43f66ec842fd0e3377b098e404dcde490fec8f33e
magnetosphere.hpp     459  c94a5bd43170234a2447d6de246503a729f30413b55374f0bcdab4fbc5c3fc87
materials.hpp         188  61c104da9c100ba0baf3058480e94232c2f0b8a77db10f90bc12d6de77217582
neutrino.hpp          214  1b288768d34c30652dcd94bea82e62290ba3dbd0bf247cd6f12269382838baf8
nuclear.hpp           795  606f2fdf2e86a05500d9b76d79964e652870eb401fc470da033a6c9b4ce04791
occlusion.hpp         185  8e6db9621ce74be18afdff699692ed93dc62f149e9f6c1874a82eea266510ed7
occlusion_sphere.hpp  151  c47882af07b108ebc1ea36f800c1c64881a85d79cc8ec21d54b9aaeae29773e1
packing.hpp           685  aea1faf3521f407be38de92d0f464a8a796ee32bd3c2421952fb08ece1be1994
sphere_frame.hpp      217  487e4bb41786658f73f4137dfd513046fb2043cf1f1f98f800305ef84892743b
state28d.hpp          315  552575a8abcfe8839452f9882b6a5fed0943ad7b8cb1e2b98b7e7861cef41935
```

Hashing the same file twice gives the same digest and the 14 digests are pairwise distinct. The repository revision is `7b49eb7`. The working-tree listing for `Engine/include/sdt` shows that `occlusion_sphere.hpp` and `sphere_frame.hpp` are untracked: they belong to no revision. A statement "the manuscript was checked against revision `7b49eb7`" would therefore not identify two of the 14 consumed headers; the digests do.

**Citations (T2).** Every `name.hpp:NNN` occurrence in the manuscript tree (66 citations found under `Textbook/volume_*/` and `Textbook/equations/` in run 3; run 2, made before this chapter's own text existed, found 65) resolves to an existing, non-blank line of the named header, with none unresolved. The eight citations of `laws.hpp:99` (the stored $\ell_P$ that carries $G$) all land on the line that defines `l_P`. Resolving a citation shows that the line exists and is not blank; it does not show that the line says what the manuscript states, and the citations were written against this snapshot.

## 57.2 Function domains

A header function can evaluate outside the physical domain unless the caller checks its inputs.

**Executed (T3).**

| call | value | observation |
|---|---|---|
| `depth_closure::clock_rate(1.5)` | $-0.5$ | $z>1$ not rejected (domain $0\le z\le1$) |
| `depth_closure::clock_rate(-0.1)` | $1.1$ | $z<0$ not rejected |
| `law_V::gamma(1.1c)` | NaN | $v>c$ |
| `law_V::v_circ(1.2c)` | NaN | $v_{\rm trans}>c$ |
| `depth_closure::depth_from_c_far(1.5c,c)` | $-0.224745$ | finite, negative; no rejection |
| `depth_closure::depth_from_c_far(-0.1c,c)` | NaN | negative $c_{\rm far}$ |
| `bridge::circular_speed_from_koppa(1,-1)` | NaN | negative radius |

The registered statement that `depth_from_c_far(1.5c,c)` would be NaN was **rejected** (the square root has a positive argument; recorded in the pre-registration, with the two marked post-run clauses). A caller must check the domain; a c-boundary ratio less than one cannot silently be interpreted as an admissible material translational speed.

`bridge::g_interior` includes a numerical cutoff below a stated radius. With the uniform-density enclosed fraction $(r/R)^3$ for the Earth ($v=7909$ m/s, $R=6.371\times10^6$ m) it returns exactly $0$ at $r=0.5$ m and $3.08218\times10^{-6}$ m s$^{-2}$ at $r=2$ m, while the uniform-density value at $0.5$ m is $7.70545\times10^{-7}$ m s$^{-2}$. The cutoff is an implementation choice and not an analytic central limit; the manuscript uses the finite-density limit explicitly when discussing centre regularity.

## 57.3 Reference ledger

Every displayed expression should carry a source symbol, premise, speed and tick-rate role, domain, approximation order and status. A source-stored measured quantity and a separately rebuilt quantity remain separate entries. **Executed (T4).** `laws.hpp` has 2917 lines, 19 top-level namespaces, 128 `[[nodiscard]]` occurrences and 160 `inline constexpr double` constants (a rough text count, not a symbol inventory); each of the 11 principal namespaces (`measured`, `law_I`…`law_VI`, `bridge`, `atomic`, `nuclear`, `depth_closure`) is a top-level `namespace` line. Regenerating a symbol-and-domain inventory and comparing the frozen manuscript with the frozen implementation before any public release is the determining practice; the present instrument covers the digests, the citations and a domain sample, not a full symbol inventory (R57.2).

## 57.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| digests, line counts, revision | Section 57.1 | COMPUTED (source files) |
| citation resolution | Section 57.1 | COMPUTED (66 citations) |
| function-domain observations | Section 57.2 | COMPUTED (engine calls) |
| $v_{\rm Earth}$, $R_{\rm Earth}$ in the cutoff example | `bridge` | stored values |

**Residuals.**

* **R57.1 — untracked headers.** Two consumed headers are untracked; the revision does not identify them. A commit or a snapshot archive of the 14 files is for the author to decide (nothing was committed).
* **R57.2 — symbol inventory.** No full symbol-and-domain inventory was generated; counts were text counts.
* **R57.3 — citation meaning.** Resolution shows existence and non-blankness; agreement of each cited line with the statement citing it was not checked line by line.
* **R57.4 — unguarded domains.** `clock_rate`, `depth_from_c_far` and the others in Section 57.2 do not check their domains (proposal to the author, canon untouched).
* **R57.5 — manifests.** `Textbook/sources/SOURCE_MANIFEST.md` and `Textbook/equations/EQUATION_REGISTER.md` cover Chapter 9 only; the backfill for the other chapters is outstanding.

## 57.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch57_engine_law_reference
```

Criteria were registered in `Textbook/validation/ch57_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch57_run1_output.txt`) met every criterion except one registered statement (a registration error: the argument of the square root is positive), which is kept as a rejection. Run 2 (`ch57_run2_output.txt`) met every criterion, with the two post-run clauses marked. Run 3 (`ch57_run3_output.txt`, 16 November 2026) repeats it unchanged after the review of the finished manuscript and is the run of record: the header digests are identical to run 2, and the citation count is 66 with eight on the `l_P` line (run 2: 65 and seven; the difference is this chapter's own two citations, added after run 2, less one citation removed from the Chapter 45 ledger, where the stored $\ell_P$ had been named as an input of `koppa_Sun` although it does not enter it).

## 57.6 Exercises and answers

**Exercise 1.** Why is the repository revision not enough to identify the snapshot?

*Answer.* Uncommitted or untracked headers belong to no revision; here `occlusion_sphere.hpp` and `sphere_frame.hpp` are untracked.

**Exercise 2.** What does `clock_rate(1.5)` return and why is it a problem?

*Answer.* $-0.5$: a negative tick-rate ratio outside the domain $0\le z\le1$ that is not rejected.

**Exercise 3.** What does a resolving citation establish?

*Answer.* That the cited line exists and is not blank in the snapshot; it does not establish that the line says what the text states.

**Exercise 4.** Why is the `g_interior` cutoff not a theorem?

*Answer.* It returns $0$ below 1 m where the uniform-density value is $7.7\times10^{-7}$ m s$^{-2}$ at 0.5 m; the value is a cutoff, not a limit of the finite-density expression.

**Exercise 5.** Compute SHA-256 of the empty string.

*Answer.* `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`.

**Exercise 6.** Which domain check would catch `depth_from_c_far(1.5c,c)`?

*Answer.* A check that $0\le c_{\rm far}\le c_\infty$, matching the domain of the inverse relation $c_{\rm far}=c_\infty(1-z)^2$ with $0\le z\le1$.

## 57.7 Scope

Established: the digests of the 14 headers, the revision and the untracked headers; that all 66 citations resolve and the eight `laws.hpp:99` citations are on the `l_P` line; the observed domain behaviour of the sampled functions and the `g_interior` cutoff.

Not established: a full symbol inventory (R57.2), the agreement of each citation with its statement (R57.3), the unguarded domains' repair (R57.4) and the manifests of other chapters (R57.5).

*Where it leads.* Chapter 58 treats the numerical mechanics of the spherical frame: stable differences and the resolution that a double-precision locus can carry.
