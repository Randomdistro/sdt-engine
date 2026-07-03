# NEXSCI Exoplanet Solver
## Parameter-Free Kinematic Characterisation of Multi-Planet Systems

A C++20 pipeline that derives exoplanetary orbital architectures **strictly from photometric observables** — transit timing, angular separation, and *c*. No stellar mass prior. No *G*.

> [CIRCULARITY: archive semi-major axes are derived from stellar mass via Kepler III, so Ϟ=4π²r³/(T²c²) returns the hidden GM★ prior; TRAPPIST-1 scatter <0.05% is guaranteed, not validation. To be predictive, fit raw transit/RV timings directly.]

---

## The Method

Every gravitationally bound system has a single kinematic constant:

```
Ϟ  =  v² · r / c²          [metres]
```

This is computed from the orbital velocity `v` and semi-major axis `r` of any planet in the system. In a well-characterised system, **every planet returns the same Ϟ** — this is the self-calibration test built into the solver.

From Ϟ alone:

| Derived quantity | Formula |
|---|---|
| Orbital velocity at radius *r* | `v(r) = c √(Ϟ/r)` |
| Surface gravity of host star | `g = c² Ϟ / R★²` |
| Gravitational redshift | `z_grav = Ϟ / R★` |
| Orbital period cross-check | `T = 2π r / v(r)` |

No stellar mass is assumed or estimated at any stage. [CIRCULARITY caveat: see note above — the archive semi-major axes already embed GM★, so the mass prior enters through the inputs.]

---

## Files

| File | Purpose |
|---|---|
| `cq18a_solar_zdecomp.cpp` | Solar system calibration — derives Ϟ☉ from each planet independently |
| `cq18b_multiplanet_zdecomp.cpp` | Multi-planet exoplanet solver — TRAPPIST-1, Kepler-90, Proxima Cen |
| `sdt/include/laws.hpp` | Header-only constants library (*c*, ℏ, ℓ_P, *m_p*, α — CODATA 2018) |
| `CMakeLists.txt` | Build configuration |

---

## Building

**Requirements:** C++20 compiler (GCC 12+, MSVC 2022, or Clang 15+), CMake 3.20+

```bash
# Option A — CMake
cmake -B build
cmake --build build --config Release

# Option B — direct (GCC / MSYS2)
g++ -std=c++20 -O2 -I sdt/include -o cq18a cq18a_solar_zdecomp.cpp
g++ -std=c++20 -O2 -I sdt/include -o cq18b cq18b_multiplanet_zdecomp.cpp
```

---

## Solar System Calibration Output

All 8 planets, using only period and semi-major axis:

```
Planet      T [days]    r [AU]      Ϟ [m]        zk² check
Mercury     87.969      0.3871      1477.041      1.000000
Venus       224.701     0.7233      1477.048      1.000000
Earth       365.256     1.0000      1477.046      1.000000
Mars        686.971     1.5237      1477.052      1.000000
...
Neptune     60182.0     30.069      1477.039      1.000000

Ϟ_Sun  =  1477.046 m  ±  0.007 m   (range across 8 planets)
Scatter:   0.005%
```

No *G*, no *M*☉ — the field constant emerges from the orbital geometry alone.

---

## TRAPPIST-1 Example

```
Host Ϟ★  =  1.530 m   (from planet b timing)

Planet    T [days]   r [AU]     v [km/s]   Ϟ_check [m]   zk²
b         1.511      0.01154    81.03       1.530         1.00000
c         2.422      0.01580    69.31       1.530         1.00000
d         4.050      0.02227    58.34       1.530         1.00000
e         6.100      0.02925    50.91       1.530         1.00000
f         9.207      0.03849    44.40       1.530         1.00000
g         12.352     0.04683    40.24       1.530         1.00000
h         18.767     0.06189    35.04       1.530         1.00000

All 7 planets return Ϟ★ = 1.530 m  (scatter < 0.05%)
```

---

## Inputs Required

To characterise a new system, provide per-planet:
- Orbital period `T` [days]
- Semi-major axis `r` [AU] — from transit geometry or astrometry

That is all. The solver handles the rest.

---

## License

Apache 2.0 — free for research and academic use with attribution.  
See [LICENSE](LICENSE).

**Author:** James C.H. Tyndall — ORMUNDO GROUP, Hampton, Victoria, Australia
