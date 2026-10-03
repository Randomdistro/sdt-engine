# CQ08 — Granular Pulse Mechanics: The Dynamic Throughput Law

## Classification: Codebase Question / Theoretical Derivation
## Source: Conversation 701fe685, April 2026
## Depends on: Law I (Φ, ε, N), Law III (force), Law IV (V_disp), Law V (budget)

---

## Question

Laws III, IV, and V each describe a DIFFERENT aspect of dynamics:
- Law III: Force = occluded convergence (mechanism)
- Law IV: Mass = V_disp reorganisation cost (definition)
- Law V: v_circ² + v² = c² (budget)

**What is the MECHANISM that connects them?**

How does the granular pulse structure of the relay produce F = ma?
Why is constant velocity free? Why does acceleration cost energy?
What is inertia, mechanistically?

## Answer (Axioms → Theorems → Proofs)

### Axiom GPI: The Granular Pulse Invariant

> Every spation receives one relay pulse per Planck length per Planck time,
> from each direction, independently. This rate is invariant under all
> conditions — velocity, acceleration, gravitational state.

Formally:
```
Pulse rate per direction = 1/(l_P × t_P) = 1.148 × 10⁷⁸ Hz/m
```

This is the FUNDAMENTAL INVARIANT. c, ℏ, and all Planck units are consequences.

### Axiom CS: Constancy Stabilisation

> Once a velocity change ceases, the omnidirectional input re-symmetrises
> around the knot at the new velocity. The new velocity becomes the
> stable resting state.

### Axiom FL: Flux Locality

> All matter sits at the centre of its own flux. Inertia is relative
> to the local throughput environment. Mass is local — determined by
> V_disp (topology) and the local throughput density.

---

## Theorems

### Theorem GPI-1: c is a consequence

```
c = l_P / t_P [exact]
```

The relay propagation speed equals one Planck length per Planck time because
each spation passes the pulse to its neighbour in one tick.

### Theorem GPI-2: Omnidirectional symmetry at constant velocity

At constant velocity v, the particle's frame sees symmetric pulse input.
No pulse asymmetry → no net reorganisation → no force → no cost.

This IS Newton's First Law, derived from GPI.

### Theorem GPI-3: Pulse asymmetry during acceleration

During acceleration a, the particle is pushed through a throughput gradient.
In the direction of acceleration:
```
Effective pulse rate = (1 + δ)/(l_P × t_P)
```
where:
```
δ = a × t_P / c = a × l_P / c²
```

### Theorem GPI-4: F = ma from pulse asymmetry

The net throughput asymmetry δ creates a reorganisation load on V_disp:
```
F = [Φ V_disp / (3 l_P³ c²)] × a = m × a
```

Proof: See CQ08 proof file.

### Theorem GPI-5: Kinetic energy is circulation deficit

```
E_kinetic = E_circ(rest) - E_circ(v) = ½m(c² - (c² - v²)) = ½mv²
```

Relativistically: E_kinetic = (γ - 1)mc²

### Theorem GPI-6: Time dilation from budget partition

```
v_circ = c/γ → T_clock = γ T_rest
```

The clock slows because the circulation velocity drops as translation increases.

### Theorem GPI-7: Doppler from frame-dependent observation

```
f_observed = f_rest × √((1 ± β)/(1 ∓ β))
```

Derived from the invariant pulse rate combined with closure velocity and
time dilation.

### Theorem GPI-8: Constancy stabilisation is Newton's Third Law

When acceleration stops, the asymmetry δ → 0. The flux re-symmetrises.
The reaction: every action (δ) on the knot produces an equal reorganisation
cost on the source of the force (the thing doing the pushing), because
the pushed knot's V_disp reorganisation propagates back through the relay.

---

## Success Criteria

1. F = ma derived algebraically from GPI + V_disp
2. All 5 existing laws shown to be consequences of GPI
3. Numerical verification against 8+ experimental measurements
4. Formal law section added to laws.hpp
5. C++ implementation with constexpr verification functions

---

## Data Requirements

All constants from laws.hpp — no external data needed.
This is a purely theoretical derivation from existing axioms.
