# SDT Games — a catalogue of play-first designs

Author: James Christopher Tyndall, Melbourne. Drafted 2026-10-10.

Voidcaster (https://claude.ai/artifact/BfVQDcERTjDzJFLok349XA) teaches the occlusion law by feel:
bodies are pushed into each other's shadow with `F ∝ r₁² r₂² / d²`, mass goes as `r³`, and an arc
acts through the cross-section it presents. Nobody reads that formula — they just learn that big
things are slow to turn, that a longer arc bends harder, and that you steer rocks by casting shadows.

Every game below follows the same rule: **one SDT structure is the whole physics of the game.**
The player masters the structure to win, and the name of the structure is only revealed afterwards
(an end-of-world card: "What you just learned is called …").

Design rules carried over from the repo canon:

- Bodies are **pushed into shadow**, never pulled. No "gravity well" art that suggests a pulling hand.
- No mass dial, no G. Weight in a game comes from **size and speed** (`g = v²/R`).
- No substance-noun for what a particle boundary does — not in names, tooltips or item text. Use
  boundary, surplus, deficit.
- Movement only: things travel, circulate, rebound, scatter. No rewind or reverse-time mechanics.
- Interactives use **drag the shape**, not sliders.

---

## The twenty

### 1. Shadow Golf — *occlusion, two-body*
Sink a ball into a hole across a course of floating boulders. You never hit the ball after the tee:
you place and resize boulders, and the ball is pushed into whatever shadow it sits in.
**Learns:** push-into-shadow, inverse-square falloff, bigger occluder = stronger push (`R²`).
**Hook:** par counts boulders placed, not strokes.

### 2. Budget Racer — *Law V movement budget `v_circ² + v² = c²`*
A top-down racer where every craft carries a spinning flywheel. Your speed and your spin share one
fixed budget: go faster and the flywheel slows (handling goes vague); brake and the spin returns
(grip comes back). Nothing can reach the full budget in straight speed because spin would hit zero.
**Learns:** special relativity as a shared movement budget — the reason nothing outruns `c`.
**Hook:** the fastest lap is the one that spends the budget best, not the one that floors it.

### 3. Rung Climber — *the koppa ladder, `v = c/k`*
A platformer up a tower of rings. On ring `k` you move at `c/k`. Climb outward (higher `k`) and
everything slows; drop inward and you speed up. The ground floor of the hydrogen tower is `k = 137`
and the game makes you find it by matching a speed gate.
**Learns:** orbits as rungs; α is a rung, not a magic number.

### 4. No Scales — *mass-free orbital mechanics*
A puzzle game of moons and planets with no mass readout anywhere. You get a surface speed and a
radius, and you must predict orbits, landings and slingshots from those alone (`g = v²/R`,
`Ѻ = v²R/c²`). An end-of-level card shows that the "mass" everyone else quotes was a derived number
all along.
**Learns:** weight from movement and size; G and M are outputs, not inputs.

### 5. Gearbox of Light — *emission law `λ = 2L(c/v)`*
Every lamp in this game is a little race track: a bead circles a loop of length `L` at speed `v`.
The colour emitted is the path times the gear. Players build tracks to hit a target colour for each
stained-glass window.
**Learns:** a spectral line is a path length and a gear ratio, nothing more.
**Hook:** the hydrogen window set is real — the targets are the measured lines.

### 6. Octave Run — *redshift as octaves, `1 + z = 2^Δn`*
A rhythm game. Light from distant beacons arrives dropped by whole and fractional octaves; you tap in
time with the correct octave to "tune in" each beacon. The CMB stage is a slow drone ten octaves down.
**Learns:** redshift as a pitch drop through depth, with no expansion.

### 7. Hinge Lines — *Shapiro delay as hinges closing*
Steer a light pulse through a field of bodies. Near each body the lattice's hinges close and the
pulse slows (`c(1 − z)²`). Race a pulse against a rival pulse on a straight path to see who arrives
first.
**Learns:** light slows near matter; the "longest" path can be the fastest one.

### 8. Nucleus Builder — *ATOMICUS grammar: 1 alpha + n_d deuterons + n_t tritons*
A tile puzzle. You get one alpha core and a bag of deuteron and triton tiles. Each target isotope has
exactly one valid build (`n_t = A − 2Z`, `n_d = 3Z − A − 2`). Wrong builds visibly wobble and shed
a piece. Electron-capture isotopes switch you to a He-3 core.
**Learns:** the construction grammar, and that a nucleus has one way to be.
**Hook:** free neutron tiles exist but can never be placed — players discover why.

### 9. Magic Shells — *shell schedule, tiers `(n+1)(n+2)` + belts `2(n+1)`*
Tetris-like stacking on a sphere. Deuteron tiers and triton belts fill in rings; completing a closure
gives a satisfying lock and a bonus. The closures land on the magic numbers. Late game: build toward
`N = 184` — the predicted closure no lab has reached.
**Learns:** magic numbers as geometry; a live prediction the player can say they "found".

### 10. Peel — *beam-peel kinematics: central = fission, grazing = spallation*
A billiards-style shooter at a spinning nucleus with a 1.83c surface. A head-on hit splits it in two;
a glancing hit peels shards from the surface. Missions ask for specific fragment sets.
**Learns:** impact geometry decides split vs peel.

### 11. Tour Guide — *sequential electron occupancy (orbital = tour, Born = dwell time)*
One electron, one atom, many stops. You route the electron on a tour of seats; how long it lingers at
each seat paints a density cloud on screen. Puzzles give you a target cloud shape to reproduce.
**Learns:** an orbital is a route, and the "probability" cloud is where it spends its movement.

### 12. Vortex Tamer — *Law VI winding quantisation, `T = 3(W + 1)`*
You stir a superfluid tank to make ring vortices. Only whole windings hold; anything between unravels
and splashes. Locking a 1:4 gear between ring and core gives the stable twelve-fold knot.
**Learns:** particles as quantised vortices in a lightspeed superfluid; why only certain forms persist.

### 13. Surplus & Deficit — *repulsion is the inverse of convergence*
A two-colour air-hockey game. Pucks either crowd the substrate (surplus, they shove apart) or thin it
(deficit, they converge). Score by herding opposite pucks into each other and keeping like pucks off
your goal.
**Learns:** attraction and repulsion as one mechanism with two signs — no substance needed.

### 14. Spiral Arms — *galactic winding as a standing wave*
Sandbox: spin up a disc of stars and watch arms form. Arms that would wind themselves up are replaced
by a standing pattern; players tune disc size and spin to hold a target arm count. No dark-matter halo
slider exists — the level designer just never gives you one.
**Learns:** arms as a pattern, not a fixed set of stars.

### 15. Drafters — *drafting crossover in wide binaries*
A two-star duet game. Close in, the pair behave like ordinary orbits; widen the pair and they enter
each other's draft and orbit faster than the near-field rule predicts. Players find the crossover
distance by ear (each star hums its speed).
**Learns:** a real wide-binary signal, explained by drafting.

### 16. Logjam — *opacity self-jam, `c/√3` ceiling*
A traffic game of photons in a dense plasma. Push too much light through and it jams; the throughput
caps at `c/√3`. Clear the jam at the right moment and the whole field goes transparent at once.
**Learns:** why the early universe glowed then cleared, without an expansion story.

### 17. Lumiopause — *where a star's light-pressure meets the background*
An exploration game piloting a probe outward from a sun. Your sail rides the star's push until it
balances the background, around 20,857 AU. Past that edge the sky changes and the rules for your sail
flip.
**Learns:** a star has a boundary set by balance, not by a wall.

### 18. Casimir Gap — *relay exclusion between plates*
Two-plate puzzle: close the gap and the plates screen the relay between them, so the outside pushes
them together. Players thread small probes through gaps that are closing on their own.
**Learns:** the Casimir effect as shadowing, same law as Voidcaster at the small end.

### 19. Pipshot — *the neutrino pip and phase pinch*
A tiny-scale shooter. Your craft is a fixed-size pip spiralling outward; crossing the c-boundary
pinches nose against tail and fires you off at a fixed size. Aim pinches through crowded matter that
can barely notice you.
**Learns:** why a neutrino barely interacts — it is too small to cast a useful shadow.

### 20. Depth Gauge — *emission depth, `z = Ѻ/r`*
A detective game. Each star's light arrives with a shift; players read off how deep in its own body
the light set out, then sort a catalogue of stars, white dwarfs and the Sun by depth. The Sun level
is the tutorial and it checks out to 0.03 %.
**Learns:** a shift tells you where light left from, separate from how far it travelled — the
seam behind the Hubble tension.

---

## Five more

21. **Throughpole** — city-builder of influx and release. Each building is a throughput node; you
    route flow so nothing starves. Teaches Law I relay throughput.
22. **Cascade** — chain-reaction puzzle where releases trip pressure domains in sequence. Law II.
23. **Inertia Sled** — pushing a block feels heavy only while it reorganises the relay around it; at
    steady speed it glides. Law IV inertia as reorganisation cost.
24. **Crystal Facets** — rotate a superfluid hypercrystal to find which facet the light is travelling
    on; each puzzle is a different face of the same space. Teaches the substrate picture.
25. **Two Ledgers** — a trading card game where every fusion pays into a mass-defect ledger;
    King-plot-style patterns show up in your deck history.

---

## Build notes

- **Shared engine.** Voidcaster's `step()` (pairwise occlusion with `effR`, mass `∝ r³`) already
  covers 1, 4, 7, 13, 15, 18 with parameter changes. Factor it into `sdt-play.js` and mount it per game.
- **Fastest wins.** 1 (Shadow Golf), 2 (Budget Racer), 8 (Nucleus Builder) and 5 (Gearbox of Light)
  are each a one-screen prototype with a clear goal and need no new physics.
- **Real numbers where it is cheap.** Nucleus Builder can read `ATOMICUS/isotopes/`; Gearbox of Light
  and Depth Gauge can use measured lines and solar values as level targets, so a player who wins has
  reproduced a real result.
- **Reveal card.** Each world ends with one plain sentence naming what was learned and a link to
  the matching page on spatialdisplacementtheory.com.
