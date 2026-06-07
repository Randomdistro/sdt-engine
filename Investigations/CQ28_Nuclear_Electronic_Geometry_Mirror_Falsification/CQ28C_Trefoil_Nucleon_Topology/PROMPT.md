# CQ28C — Trefoil Nucleon Topology *(embodiment; positions FROZEN from CQ28B)*

**Purpose.** Replace balls/sticks with the real nucleon topology — each nucleon a 6π (2,3) trefoil / toroidal structure — **at the positions CQ28B already solved**. Rendering is *not* evidence; this stage builds the substrate CQ28D tests for threading.

**Inputs.** CQ28B positions (**frozen** — may not be moved).
**Outputs.** Per nucleon: an oriented (2,3) trefoil tube at its CQ28B site; tube radius at `R_p ≈ 0.84 fm` scale.

**Formulations.**
```
trefoil (2,3):  x=(R+r cos3t)cos2t,  y=(R+r cos3t)sin2t,  z=r sin3t  (6π winding, W=3)
orientation:    knot axis = radial direction of the CQ28B block site
tube scale:     R_p = 4ℏ/(m_p c) = 0.84124 fm   (laws.hpp::winding, frozen)
```

**Hard rule.** Topology is **imposed on** solved positions — it may not perturb them by even one step. A position-drift check (CQ28C site == CQ28B site, exactly) is mandatory.

**Fixed metrics.** (i) knot closure (curve returns to start), correct (2,3) crossing number = 3; (ii) radial orientation per site; (iii) **zero position drift** vs CQ28B; (iv) `R_p` tube scale matches `laws.hpp`.

**Failure criteria.** Any nucleon position differs from CQ28B; degenerate/self-intersecting tube where a trefoil should not; tube scale silently retuned.

**Reuses.** `laws.hpp::winding` (R_p), `CQ11`/`CQ14` (trefoil mechanics). **Provenance:** class **B** (internal embodiment).
