# NP26 — Event-resolved fission tomography: rotation and entry point

## Objective

Infer the uranium packing **order**, rather than merely its block inventory, from
coincident fission observables.  Each event is treated as a tomographic ray through
one rotating body.  No fragment remainder is replaced by its average composition.

The fissioning thermal system is excited **U-236**, not bare U-235:

```
U-236* = alpha + 38 d + 52 t
```

Any pre-neutron binary partition must contain two alpha-cored connected components.
Consequently its exact grammar receipt is `2d -> alpha`.  If `nu` tritons are
stripped along the ray or neck, the post-neutron receipt is

```
nu(t -> d+n) + 2d -> alpha
Delta n_t = -nu
Delta n_d = nu - 2
```

## Event map

For event `e`, the latent input is

```
I_e = (R_e, b_e, s_e, E_n)
```

where `R_e` is the body rotation at capture, `b_e` is the entry point/impact
coordinate, and `s_e` is the incoming direction.  In body coordinates the ray is

```
r_e(q) = R_e^-1 (b_e + q s_e).
```

The measured output used by the inverse problem is

```
O_e = (A_L, Z_L, A_H, Z_H, TKE, nu_L, nu_H,
       neutron directions/energies, fragment directions, prompt gammas).
```

Only quantities measured in coincidence belong on the same event row.  Evaluated
mass yields, cumulative yields and separately measured `nu(A)` curves are useful
priors/checks, but must never be joined into synthetic events.

## Geometry ladder and rejection tests

1. **One-dimensional chain.** A cut after `q` proton-bearing blocks fixes one
   cumulative `(n_d,n_t)` and therefore one `(A,Z)`.  A measured charge width at
   fixed primary mass immediately rejects a unique linear ordering unless rotation
   exposes multiple inequivalent chains.
2. **Single ring/toroid.** Rotation changes the cut origin but a single circular
   order still restricts every connected fragment to circular intervals.  Test all
   observed complementary `(A,Z)` pairs for the circular-ones property.  Failure
   requires cross-links or layers.
3. **Layered/branched body.** Infer the smallest contact graph whose connected cuts
   reproduce all event pairs.  Block labels are fixed (`d` mass 2, `t` mass 3);
   only adjacency and body-fixed positions are unknown.
4. **Two-lobed scission graph.** Every accepted cut must leave an alpha seed in
   each lobe.  The new seed is a neighbouring `d-d` pair.  Neutron multiplicity
   identifies traversed/neck tritons; TKE constrains lobe separation/compactness.

Complexity is increased only when the preceding class is contradicted by a held-out
event.  Yield magnitudes are not fitted until reachability and conservation have
passed exactly.

## What current correlation data already force

- The parent cannot have a single unique linear order: primary charge is distributed
  at a given mass, so more than one inequivalent connected cut reaches the same mass.
- The heavy side contains a compact, low-neutron-emission anchor around the
  `Z=50, N=82` neighbourhood.  In grammar coordinates Sn-132 is
  `alpha + 16d + 32t`; its exact U-236 complement is Mo-104,
  `alpha + 20d + 20t`.  Their sum consumes the required extra `2d -> alpha`.
- The prompt-neutron sawtooth proves that neutron-emitting capacity is not uniform.
  The heavy anchor is protected relative to the more deformable light side.  It does
  **not**, by itself, prove that the neutrons were stripped on the entrance ray:
  conventional kinematic analyses assign most prompt emission to the accelerating or
  fully accelerated fragments, while scission-neutron estimates are small.  Ray/neck
  stripping and post-scission emission are rival event maps and must be separated by
  neutron direction and emission-time correlations.
- The measured negative TKE-versus-neutron slope shows that compactness and neutron
  emission share a latent coordinate.  It supports a coupled geometry, but does not
  uniquely identify that coordinate as entry depth or triton exposure.
- Rotation plus entry point therefore selects among multiple cut surfaces through
  a **layered, two-lobed contact graph**.  A bare sequence and a homogeneous ring are
  insufficient.  This is a topology result; it is not yet a unique 3-D coordinate map.

## Identifiability limit and required beam test

Thermal-neutron event records normally do not measure `R_e` or `b_e`.  For an
unpolarised target they are integrated out, so rotations/reflections and many graph
embeddings are observationally equivalent.  Moreover a 0.0253-eV neutron has a de
Broglie wavelength of about 1.80 angstrom, roughly 12,000 nuclear diameters.  Existing
thermal data therefore do not spatially resolve a femtometre-scale entry point.  No
honest algorithm can recover a unique entry coordinate from those marginals.

The decisive experiment must tag the entrance channel and orientation:

1. oriented/polarised U-235 target or a resonance-selected aligned compound state;
2. narrow beam with recorded transverse impact coordinate and incident direction;
3. both fragment masses, charges, velocities and directions in coincidence;
4. prompt-neutron multiplicity, energy and direction assigned to the same event;
5. repeat after rotating target/beam geometry through known angles.

The prediction is a rotating yield map `Y(A,Z,TKE,nu | phi,b)`.  A real body-fixed
packing order must recur at the same phase after `2pi`, with complementary cuts and
the exact grammar receipt on every event.  If conditioning on `(phi,b)` does not
narrow the fragment/nu distributions beyond detector resolution, entry-point
determinism is refuted.

## Data discipline

The reconstruction must publish the raw event identifiers, detector corrections,
and train/held-out split.  The adjacency graph is frozen on the training events.
Pass/fail is then the exact fraction of held-out events that are reachable while
conserving `(A,Z)` and the measured prompt neutrons; no "nearly" channel substitutions
are allowed.
