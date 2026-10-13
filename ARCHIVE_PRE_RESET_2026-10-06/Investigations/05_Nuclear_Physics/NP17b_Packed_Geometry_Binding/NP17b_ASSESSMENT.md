# NP17b Assessment — packed geometry binding (NP17 α reopen)

**Date:** 2026-08-13  
**Stdout:** `.audit-tmp/np17b_run.txt`  
**Canon edited:** no · **dnn:** frozen 1.45 fm

## Status

`NP17b_PACKED_BINDING_MISS`

## Gates

| Gate | Result |
|---|---|
| G1 Li-6 `E=3αℏc/D_pn` vs 2.224 | **ORDER** rel=0.340 (`D_pn=1.45` fm ⇒ 2.979 MeV) |
| G2 He-4 dependency-traced candidates vs 28.296 | **FAIL** — best 4×(3αℏc/⟨r_pn⟩)=17.25 MeV, rel=0.390 |

Packed deuteron length **is** the frozen `dnn` by construction. NP17's 1.1% used `D=2R_p+R_p/3=1.963` fm, which this packer does not realise. He-4 face-centred tetra: `r_pp=1.049` fm, `⟨r_pn⟩=1.002` fm; electrostatics still under-bind. dnn was not retuned.

NP17 deuteron DERIVED result (old D) is not withdrawn. The live packer does not reproduce it. Alpha lock remains PENDING.
