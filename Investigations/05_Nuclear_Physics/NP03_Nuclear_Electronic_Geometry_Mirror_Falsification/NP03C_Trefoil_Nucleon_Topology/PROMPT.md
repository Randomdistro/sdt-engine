# NP03C — Trefoil Nucleon Topology *(embodiment; positions FROZEN from NP03B)*

**Purpose.** Replace balls/sticks with the real nucleon topology — each nucleon a 6π (2,3) trefoil / toroidal structure — **at the positions NP03B already solved**. Rendering is *not* evidence; this stage builds the substrate NP03D tests for threading.

**Inputs.** NP03B positions (**frozen** — may not be moved).
**Outputs.** Per nucleon: an oriented (2,3) trefoil tube at its NP03B site; tube radius at `R_p ≈ 0.84 fm` scale.

**Formulations.**
```
trefoil (2,3):  x=(R+r cos3t)cos2t,  y=(R+r cos3t)sin2t,  z=r sin3t  (6π winding, W=3)
orientation:    knot axis = radial direction of the NP03B block site
tube scale:     R_p = 4ℏ/(m_p c) = 0.84124 fm   (laws.hpp::winding, frozen)
```

**Hard rule.** Topology is **imposed on** solved positions — it may not perturb them by even one step. A position-drift check (NP03C site == NP03B site, exactly) is mandatory.

**Fixed metrics.** (i) knot closure (curve returns to start), correct (2,3) crossing number = 3; (ii) radial orientation per site; (iii) **zero position drift** vs NP03B; (iv) `R_p` tube scale matches `laws.hpp`.

**Failure criteria.** Any nucleon position differs from NP03B; degenerate/self-intersecting tube where a trefoil should not; tube scale silently retuned.

**Reuses.** `laws.hpp::winding` (R_p), `PPT05`/`PPT06` (trefoil mechanics). **Provenance:** class **B** (internal embodiment).
