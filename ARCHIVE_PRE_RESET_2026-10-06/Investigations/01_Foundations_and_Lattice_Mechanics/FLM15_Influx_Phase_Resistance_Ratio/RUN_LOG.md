# FLM15 Run Log

**Run date:** 2026-08-14  
**Forward instrument:** `flm15_influx_phase_resistance.py`  
**Post-seal instrument:** `reveal_flm15.py`

## Sequence

1. Froze `FLM15_PRE_REGISTRATION.md` and `MODEL_SPEC.md`.
2. Built the forward instrument without particle masses, measured
   displacement volumes, exclusion radii, or comparison formulae.
3. Passed five unit tests.
4. Ran 20 matched W=1/W=3 integrations covering the frozen primary geometry
   and orientation scan plus one-factor convergence scans.
5. Wrote `blind_ratio.txt`.
6. Sealed canonical text with SHA-256:

```text
5a1bcb8f65229f8e18e0c0975c0f64ec90126d75759a6509d23f0cd6620d611e
```

7. Verified the seal and only then ran `reveal_flm15.py`.

## Instrument controls

```text
isotropic relative error:       3.99e-5  PASS
circle x/y symmetry error:      2.59e-3  PASS
circulation-squared error:      0         PASS
rotation eigenvalue error:      1.07e-2  PASS
```

All responses were finite and positive. The solver source delete-test found no
forbidden particle-data route.

## Blind result

```text
primary median J_3/J_1:  2.6471383287
primary complete range:  2.4418864938 to 2.8405826825
```

At the reference trefoil aspect `sqrt(2/3)`:

```text
segments  96,192,384:        2.67170, 2.67702, 2.67839
samples   32768,65536,131072: 2.67021, 2.67702, 2.67932
core      0.08,0.12,0.18:     2.67103, 2.67702, 2.66982
padding   3,5,8:               2.67805, 2.67702, 2.67223
```

A finite-domain plateau is present near `2.67–2.68`. Aspect and orientation,
not numerical refinement, dominate the full primary range.

## Reveal

All three large post-seal comparison targets are about `1836.1`; the blind
result is `99.856%` lower. Three targets were inspected, so no one numerical
near-match could have been treated as unique. The bare curve-length ratio
ranges from `2.143` to `2.616`.

The original run left `R4_LOCKED_WAKE` unevaluated because no threshold-free
boundary was then specified.

## R4 extension — 2026-08-14

FLM07's glancing equality supplies the relay-capacity separatrix without an
amplitude threshold. Direct rerun:

```text
python -m unittest test_flm15.py
10 tests PASS

angular lock absolute error          0
locked radial relative error         4.44e-16
wake radial relative error           3.33e-16
lock+wake partition relative error   0
cubic scaling relative error         0
coincident/non-overlap endpoint err  0 / 0
intermediate overlap refinement      1.60e-4 relative
```

The unlocked quick regression over the four frozen aspects returned:

```text
2.609455, 2.440383, 2.665468, 2.820350
median 2.637461
```

This is `0.36%` below the sealed `2.647138` and passes the frozen `0.5%`
regression gate. The R0–R3 conclusion is unchanged. The R4 kernel now computes
target-free engaged volume and synchrony resistance for a separately supplied
mechanical boundary.
