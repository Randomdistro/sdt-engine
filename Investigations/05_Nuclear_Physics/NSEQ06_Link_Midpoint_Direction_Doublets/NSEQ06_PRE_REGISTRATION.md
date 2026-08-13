# NSEQ06 Pre-registration — 14→42 link midpoints → angular directions

**Date:** 2026-08-09  
**Parent:** NSEQ05-C5/C6  
**Objective:** Test the claimed structural signature that the 42 contact
midpoints on the T₁₄ face-normal graph yield **42 distinct 3-D positions**
but only **36 angular directions**, with exactly **six rays carrying a
radial doublet**, and that the two Q–Q orientation branches double
*complementary* ray sets.

## Hypothesis

For each polar branch of the degree-6 face graph on the 14 cuboct face
normals (unit directions as vertex positions on the unit sphere):

1. Midpoint of each edge is a distinct Euclidean point (|midpoints|=42).
2. Projecting midpoints to the unit sphere collapses to |directions|=36.
3. Exactly 6 directions are hit twice (radial doublets); 30 once.
4. The two branches’ doublet-direction sets are complementary (intersection
   empty or proper — **pre-registered**: intersection empty on the unit
   sphere after identifying antipodes? No — keep directed rays; expect
   complementary among the 6 doubled rays of each branch).

## Decision

- SURVIVE if (1)–(3) hold for both branches and (4) holds as stated.
- OPEN if counts match but complementarity needs a different equivalence.
- EXCLUDE if |directions| ≠ 36 or doublet count ≠ 6 on either branch.

## Non-goals

No change to capacities, laws.hpp arithmetic, or emission physics.
