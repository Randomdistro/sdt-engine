# VERDICT — GD03: Galactic Spation Topology

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (HUNTER audit re-run).
> **Tools:** all nine May-2026 `.cpp` files compiled AS-IS (zero edits), MSVC 19.44,
> 9/9 exit 0. **Evidence:** `results_<tool>.txt` (real stdout), `RUN_LOG.md`.

## Dual verdict

- **Prompt completion: F** (measured against GD03's own PROMPT: Level 3 fails at Sag A*,
  Level 4 fails its own anchor points, and the tool's final banner misreports both)
- **Physics class: CIRCULAR (the koppa census) / KILLED (the rotation-curve claims) —
  with one narrow CONVERGENCE survivor (solar-system parent invariance)**
- **Superseded by: GD05 twin-regime for anything rotation-curve shaped. Do not rescue.**

## The circularity, located exactly

`gd03_convergence_occlusion.cpp` lines ~360–368:

```cpp
double v_obs = disk_rc[i].v_kms;
double K_obs = Koppa(v_obs * 1e3, R_m);
...
// v from the occluded gradient: just use observed Ϟ as the proxy
double v_occ = std::sqrt(c * c * K_obs / R_m) / 1e3;
```

v_occlusion is √(c²·(v_obs²R/c²)/R) = **v_obs, identically**. The table prints the two
columns equal to the last digit and the prose calls it verification. Likewise the
"linear Ϟ ramp → flat rotation" section computes Ϟ from the OBSERVED v at every radius;
since Ϟ ≡ v²R/c², "v ≈ const ⟺ Ϟ ∝ R" is an algebraic restatement of flatness, not a
derivation of it. **This is the v_obs → ϟ → v_obs loop the 2026-07-02 scour flagged,
confirmed in both source and output. Class: CIRCULAR.**

## The misreported verdict banner (fabrication-by-summary)

`gd03_spation_topology.cpp` computes, and its own stdout shows (2026-07-03 run):

- Level 3, Sag A*: σ/μ = **51.03%** across 5 S-star orbits → the tool prints
  "**Level 3 FAIL**" (threshold 5%).
- Level 4, single-engine wake v(r) = 1.831c·R_p/r: v(r_e)/c = **0.5467** where the claim
  requires ~1; v(a₀)/(αc) = **0.00399** — misses by 1.8× and 250×. The 1/r drag-wake
  ansatz does NOT place the c-boundary at r_e, and does NOT put the electron resonance
  at αc. No drag coefficient was ever derived (the PROMPT's "key unknown" was never
  computed).

Yet the final banner prints: "Level 3 (parent invar.): PASS — 8 planets, 5 S-stars
converge / Level 4 (convergence profile): PASS — cq20g proves flat rotation." **Both
lines contradict the same program's own output above them**, and the Level-4 line
delegates its "proof" to a different tool. This is a hand-typed verdict, the exact
failure mode this repo was burned by.

## What each tool actually shows (real output)

- `gd03_spation_topology`: 12-zone zk² table = IDENTITY (tool admits "trivially true by
  construction"). Solar parent invariance σ/μ = 0.06% = Kepler-III consistency
  (CONVERGENCE — real, but Newtonian-equivalent). Sag A* invariance FAIL 51% (the S-star
  (a,P) inputs as typed are not a consistent Kepler set — S14 row is the outlier).
- `gd03_galactic_occlusion`: the one genuine forward model in the folder. It
  OVER-predicts the MW curve 2–4× everywhere (955 vs 220 km/s at 3.8 kpc; 681 vs 229 at
  8.1; 406 vs 185 at 24.7) and declines where the data are flat. Honest FAIL, no gate
  present. **KILLED.**
- `gd03_bulge_from_sagA`: prints its own 40% core under-prediction at 26 pc. Honest miss.
- `gd03_galactic_skymap`: Great-Attractor bulk-flow ratio prints 0.000 (predicted ~0 vs
  observed ~600 km/s). The anisotropy map is descriptive.
- `gd03_proton_spation_cmb`: "Ϟ(r_e) = r_e exactly" is definitional in laws.hpp; also
  prints an unexplained 5.4e58 "dimensional bridge factor" (numerology-adjacent).
- Three torus/trefoil tools: exploratory geometry, no claims, no verdicts.

## Disposition

- **Class CIRCULAR** for the lattice-census levels (1, 2, and the disk "verification");
  **KILLED** for every galactic-rotation claim (both actual forward models miss by
  40%–400%); the only survivor is solar-system Ϟ-invariance at 0.06%, which is
  CONVERGENCE with Kepler and already banked elsewhere (CQ18a).
- The 37-orders "one lattice, one closure" headline is NOT earned by these tools: what
  holds at all scales is the notation (zk² = 1), which holds for any v by algebra.
- Superseded by GD05 (twin-regime, real SPARC, RMS 23.8%) for rotation curves. GD03's
  folder should be treated as a record of the failure mode, not a foundation.
- No file here was edited or "fixed"; the kill is documented on the tools as they stand.

## §D — Seven questions (on the CIRCULAR census, the Level-3/4 FAILs, and the banner)

1. **Why (exact mechanism)?** (i) Circularity: `v_occ = √(c²·Koppa(v_obs)/R)` — the
   observed velocity is fed in and read back out, error 0 by construction. (ii) Sag A*
   invariance: σ/μ = 51.03% because the typed S-star rows are not a consistent Kepler
   set (S14 at a=1040 AU, P=55.3 yr implies a wildly different ϟ than S2/S62 — a data
   transcription problem, since GRAVITY-collab orbits ARE mutually consistent).
   (iii) Level-4 wake: v(r) = 1.831c·R_p/r puts v=c at 1.83·R_p, not at r_e (ratio
   0.547), and v(a₀)/αc = 0.004 — the bare 1/r ansatz misses both anchors because no
   drag/transfer coefficient was ever derived. (iv) The forward occlusion model
   over-predicts 2–4× and declines — same missing coefficient, other sign.
   (v) The final banner stamps Levels 3–4 PASS against the program's own printed FAIL.
2. **Recoverable?** (i) No — circular code proves nothing to recover. (ii) Yes:
   replace the S-star table with published (a, P) ephemerides. (iii)/(iv) Only by
   paying the occlusion-transfer root (below). (v) Process: verdict banners must be
   computed from the gate variables, never typed.
3. **What did the target fail to account for?** That a lattice CENSUS (v → ϟ at every
   scale) contains no prediction; that a wake law needs a derived decay/transfer
   coefficient before it can claim any anchor; that hand-written summary text can
   contradict computed output.
4. **Errored premise?** "Descriptive closure across scales (zk²=1 everywhere) is
   evidence of one mechanism." It is evidence of one NOTATION. The mechanism claim
   lives entirely in the un-derived occlusion/drag transfer function — the PROMPT even
   names it ("the key unknown: the drag coefficient") and no tool computes it.
5. **Correcting freedom?** Derive the occlusion transfer (drag) coefficient from
   lattice geometry (12-around-1 packing / FLM10-class mechanics), then re-run the
   single-engine wake and the aggregate rotation model with zero galaxy-fitted knobs.
   Per the Closure Principle: CLOSE the coefficient loop, don't keep re-plotting v_obs.
6. **Native or knob?** The needed freedom is native-in-kind but UNBUILT. Every
   attempted stand-in so far (κ_per_baryon in GD04, the effective ^1.3 factor here)
   has been a knob — which is exactly why these tools failed or went circular.
7. **Cascade?** **Yes — this folder is the cascade's clearest exhibit.** Root:
   **OCCLUSION-MECHANISM** (shared with GD04's calibrated κ, GOM13's G1/G2 fork,
   GOM01's imported prefactor). Secondary process root: hand-typed verdict banners
   (the June-2026 fabrication mode) — a discipline fault, not a physics premise.

**Recovery grade: NO RECOVERY** for the tools as built (circular census cannot be
rescued; forward models await the root). PARTIAL only for the Sag A* Level-3 check
(clean-data route named).

---

**Prompt completion F · Physics class CIRCULAR (census/"verification") / KILLED
(rotation claims; misreported PASS banner documented) · Recovery NO RECOVERY (as
built; superseded by GD05) · Cascade root OCCLUSION-MECHANISM.**
