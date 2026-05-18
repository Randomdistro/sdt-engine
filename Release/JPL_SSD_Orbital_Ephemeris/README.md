# JPL SSD Orbital Ephemeris
## Mass-Independent Kinematic Solver for Orbital Mechanics

A C++20 solver for high-precision orbital ephemerides that bypasses *G* and estimated mass values entirely. Derives all gravitational field quantities from period, radius, and *c* alone.

---

## The Problem with G·M

Standard numerical integration of orbital systems requires:
- An estimated stellar/planetary mass *M*
- Newton's *G* (known only to 4 significant figures — the least precisely measured fundamental constant)
- The product *GM* as a combined prior

Parameter drift in long-baseline *N*-body simulations compounds from these inputs over extended timeframes.

---

## The Approach

Replace *GM* with a single directly-measured kinematic constant:

```
Ϟ  =  v² · r / c²          [metres]
```

This encodes the entire gravitational field of the central body. It is computed from observables (velocity, radius) and *c* — which is SI-exact. No *G* measurement uncertainty enters the calculation.

For any orbit at radius `r`:

```
v(r)  =  c √(Ϟ / r)          [orbital velocity]
g(r)  =  c² Ϟ / r²           [gravitational acceleration]
T(r)  =  2π r / v(r)         [period — cross-check]
```

The self-calibration condition: in any gravitationally closed system, every body returns **the same Ϟ** to measurement precision. This is a built-in consistency check absent from *GM*-based approaches.

---

## Files

| File | Purpose |
|---|---|
| `cq18a_solar_zdecomp.cpp` | All 8 solar system planets → single Ϟ☉, surface gravity metrics, precession constraints |
| `sdt/include/laws.hpp` | Header-only constants (*c*, ℏ, ℓ_P — CODATA 2018, no *G*) |
| `CMakeLists.txt` | Build configuration |

---

## Building

```bash
# CMake
cmake -B build
cmake --build build --config Release

# Direct (GCC)
g++ -std=c++20 -O2 -I sdt/include -o cq18a cq18a_solar_zdecomp.cpp
./cq18a
```

---

## Validation Output

```
Planet      Ϟ [m]        g_surface [m/s²]   v_orbital [km/s]   zk² closure
Mercury     1477.041     274.07             47.87              1.000000
Venus       1477.048     274.07             35.02              1.000000
Earth       1477.046     274.07             29.78              1.000000
Mars        1477.052     274.07             24.13              1.000000
Jupiter     1477.044     274.07             13.07              1.000000
Saturn      1477.039     274.07             9.69               1.000000
Uranus      1477.051     274.07             6.81               1.000000
Neptune     1477.039     274.07             5.43               1.000000

Ϟ_Sun  =  1477.046 m  (scatter 0.005% across all 8 planets)

Earth surface gravity from lunar timing alone:
  g_Earth  =  9.8069 m/s²  (measured: 9.8067 m/s²)   →  0.002% match
```

---

## Perihelion Precession

Mercury's precession is recovered geometrically from the orbital velocity gradient — no GR tensor metrics required:

```
dΩ/dt  =  3 v² / (c² · a · (1 - e²))   [radians per orbit]
         =  42.98 arcsec/century        (observed: 43.0 arcsec/century)
```

---

## License

Apache 2.0 — free for research and academic use with attribution.  
See [LICENSE](LICENSE).

**Author:** James C.H. Tyndall — ORMUNDO GROUP, Hampton, Victoria, Australia
