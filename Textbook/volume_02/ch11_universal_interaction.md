# Chapter 11 — Universal Interaction

*Volume II — Pressure Response, Inertia and Propagation.*
Draft of 9 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. Executable companion: `Textbook/examples/ch11_universal_interaction.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 11.1 The physical question

Law III claims one law for the electric, gravitational and nuclear interactions. Chapters 9 and 10 derived its geometry. This chapter assembles the law and separates its factors: the geometric ones that follow from the shadow, the pressure that sets the magnitude, the count that enters the handed interaction, and the sign. It states what is executed for the electric case, what the engine records for the others, and what is outstanding.

## 11.2 The assembled law

From Chapters 9 and 10, two spheres of radii $R_1$ and $R_2$ at centre distance $r\ge R_1+R_2$, in a content density $U$ with the response model of Chapter 9, exert on one another the axial force

$$F=\frac{\pi}{4}\,U\,\frac{R_1^2R_2^2}{r^2}, \tag{11.1}$$

exact for finite spheres down to contact (Proposition 10.1). The three factors have separate origins. The factor $1/(4\pi)$ is the content per steradian of an isotropic arrival. The factor $\pi R_1^2/r^2$ is the projected solid angle of the shadow (Eq. 10.1). The factor $\pi R_2^2$ is the cross-section of the target. Their product is $\pi/4$ times $R_1^2R_2^2/r^2$ (test V1: the two forms agree to $10^{-15}$).

The engine's form replaces $U$ by an effective pressure,

$$F=\frac{\pi}{4}\,P_{\rm eff}\,\frac{R_1^2R_2^2}{r^2}\qquad(\texttt{law\_III::F\_occlusion},\ \texttt{laws.hpp:535}). \tag{11.2}$$

The inverse square follows from the solid angle of a shadow in three-dimensional geometry. It needs no field equation, no mediating carrier and no distance-dependent coupling. The law is symmetric in the two bodies, so the force on each is equal and opposite. Over six decades of separation the log-slope of `F_occlusion` between $r$ and $10r$ was $-2$ to $4.4\times10^{-16}$ for two radius pairs (test T3).

## 11.3 The pressure factor

The coefficient $P_{\rm eff}$ is one entry of a ladder of pressures that must not be confused (Chapters 4, 6 and 9). Executed values:

| quantity | value | role |
|---|---|---|
| $u_{\rm CMB}=a_{\rm rad}T^4$ | $4.174783\times10^{-14}$ Pa | radiation energy density |
| $P_{\rm rad}=u/3$ | $1.391594\times10^{-14}$ Pa | radiation pressure |
| $P_{\rm conv}=Nu$ | $2.460822\times10^{48}$ Pa | convergence content density (Law I) |
| $P_{\rm cf}=P_{\rm conv}/3$ | $8.202739\times10^{47}$ Pa | resistance pressure (Law IV) |
| $P_{\rm eff}$ | $5.227252\times10^{31}$ Pa | effective pressure of the atomic and nuclear interaction |
| $f=P_{\rm eff}/P_{\rm conv}$ | $2.124189\times10^{-17}$ | transfer function |

Table 11.1. The pressure ladder, executed.

The engine's $P_{\rm eff}$ has a forward form built from the seed (`laws.hpp:465–476`):

$$P_{\rm eff}=\frac{4\,\alpha\hbar c}{\pi\,R_{\rm lock}^2\,r_e^2},\qquad R_{\rm lock}=\frac{4\hbar}{m_pc}=8.412356\times10^{-16}\ \text{m},\quad r_e=\alpha^2a_0=2.817940\times10^{-15}\ \text{m}. \tag{11.3}$$

$R_{\rm lock}$ is the target-free proton lock boundary of the FLM07 branch (four action relays, the tetrahedral close-packed thread, selected before any comparison with the measured $R_p$), and $r_e$ is the hydrogen c-boundary. No measured $R_p$, no measured $k_e$ and no elementary unit $e$ enters the forward form: the engine labels it class C with the premise that FLM07's minimum-resistance path holds. It has two equal rewrites, both executed (test T1):

$$P_{\rm eff}=\frac{m_p^2m_e^2c^5}{4\pi\alpha\hbar^3}=\frac{m_ec^2}{V_{\rm int}},\qquad V_{\rm int}=\frac\pi4R_{\rm lock}^2\,r_e=1.566235\times10^{-45}\ \text{m}^3, \tag{11.4}$$

the electron's rest energy per interaction volume, the volume of a cylinder of cross-section $(\pi/4)R_{\rm lock}^2$ and length $r_e$. The three forms agree to $1.0\times10^{-11}$, $5.2\times10^{-12}$ and $5.2\times10^{-12}$, which is the level of the consistency of the stored constants (Chapter 6, Table 6.2). The engine states that the volume form is a rewriting of the Coulomb identity $\alpha\hbar c=m_ec^2r_e$ inside $P_{\rm eff}$ and adds no derivation. The step from the electropause balance (EMC04) to (11.3) is not reproduced in this book (residual R11.1).

The transfer function $f=P_{\rm eff}/P_{\rm conv}$ equals $V_{\rm disp,e}/(3V_{\rm int})$ to $5.2\times10^{-12}$ (T7), the same identity read with the electron's exclusion volume of Chapter 1; the label is CONSTRUCTION. Because $P_{\rm conv}$ carries the measured $R_{\rm CMB}$, the absolute value of $f$ is conditioned on that observed boundary and is not an independent cosmological prediction.

### 11.3.1 The hierarchy of the forces as a conversion of surfaces

*Added 16 November 2026 from the author's statement of that date. The arithmetic was evaluated directly from the engine's stored values; it has not yet been placed under a registered instrument (residual R11.7).*

**The statement.** A point of the medium receives the entire output of the release surface about it, at the rate the release dictates, as an immediate boundary contact condition (Chapter 4: every shell contributes the same amount, whatever its distance). The same total therefore lands on whatever surface a structure presents: on the surface of a hydrogen atom, on the surface of a proton, on the surface of an electron, and on the surface of a single spation. The intensity at each rung is fixed by the surface alone, and the ratio of two interactions is a ratio of surfaces.

| surface | radius (m) | area relative to a spation, $(r/\ell_P)^2$ |
|---|---|---|
| spation | $\ell_P=1.616255\times10^{-35}$ | $1$ |
| electron exclusion surface (candidate; Chapter 17, Section 17.3) | $2.877582\times10^{-21}$ | $3.170\times10^{28}$ |
| proton exclusion surface | $3.523686\times10^{-20}$ | $4.753\times10^{30}$ |
| proton boundary $R_p$ | $8.414\times10^{-16}$ | $2.710\times10^{39}$ |
| interaction radius $R_{\rm int}=\sqrt{R_{\rm lock}r_e}$ | $1.539660\times10^{-15}$ | $9.075\times10^{39}$ |
| hydrogen c-boundary $r_e$ | $2.817940\times10^{-15}$ | $3.040\times10^{40}$ |
| hydrogen route $a_0$ | $5.291772\times10^{-11}$ | $1.072\times10^{49}$ |

Table 11.2. The rungs (COMPUTED from the stored lengths; every entry carries the stored $\ell_P$).

**The conversion.** For a proton and an electron the presented surface is the interaction cross-section, a disc of radius $R_{\rm int}$. Set against the whole sphere of a spation, a disc area against $4\pi$ steradians of a sphere of radius $\ell_P$,

$$H=\frac{\pi R_{\rm int}^2}{4\pi\,\ell_P^2}=\frac{R_{\rm lock}\,r_e}{4\,\ell_P^2}=2.268662\times10^{39}, \tag{11.8}$$

and $2.269105\times10^{39}$ with the stored measured $R_p$ in place of $R_{\rm lock}$. This is the ratio of the handed (electric-class) interaction of the pair to its gravity-class interaction. The factor 4 is the disc-to-sphere factor.

Read the other way, the gravity-class force of the pair is Law III with one of the two cross-sections replaced by a spation-scale one:

$$F_{\rm grav}=\frac{F_{\rm C}}{H}=\frac\pi4P_{\rm eff}\,\frac{R_{\rm int}^2\,(2\ell_P)^2}{r^2}. \tag{11.9}$$

One law, two receiving surfaces: the whole interaction cross-section for the handed interaction, a single spation for the gravity class. Substituting $R_{\rm lock}=4\hbar/(m_pc)$ and $r_e=\alpha\hbar/(m_ec)$ in (11.9) gives $\ell_P^2c^3m_pm_e/(\hbar r^2)$ exactly.

**Status.** With $R_{\rm lock}$, (11.8) equals the measured ratio of the two forces identically, because the stored $\ell_P$ is the Planck length and already contains the measured gravitational strength (Chapter 6, R6.1): contaminating input: $G$, entering through the stored $\ell_P$. Label: CONSTRUCTION. What the statement adds is the reading, a mechanism where the sources had a length ratio: why the ratio is a ratio of areas, and why the factor is 4.

**Direction of derivation.** The chain is acyclic in either direction. With the spation pitch $\ell_P$ as the primitive, $H$ follows from (11.8), the baryon source length is $\varpi_b=r_e/H$ (with the measured $R_p$; Chapter 18), and the gravitational constant of the standard description is an output, $c^2\varpi_b/m_p$. Conversely a gravity-free determination of $H$ or of $\varpi_b$ would fix $\ell_P=R_{\rm int}/(2\sqrt H)$. What is missing is a handle on the spation pitch that does not pass through a gravitational measurement (residual R11.8). The transfer ratio $f=P_{\rm eff}/P_{\rm conv}$ of Table 11.1 does not reduce to a ratio of these surfaces alone; it also carries the shell count $N$, and its place in this picture is not worked out.

**A record in the sources that does not hold.** The investigation CQ04 is marked "resolved (superseded)" on the ground that CQ01 and CQ16 derive this hierarchy. Evaluated on the engine's values on 16 November 2026, its stated formulas give $2.8\times10^{167}$, $4.9\times10^{76}$ and $4.0\times10^{9}$ where $2.27\times10^{39}$ is claimed; CQ01 computes the ratio from the measured $G$ and its own test of $G$ is a factor 5 off; CQ16 contains no derivation of the ratio. The hierarchy is therefore not derived in those sources. The only expression in the repository that returns the number is (11.8), from the dossier of 18 October 2026, which certifies itself as an identity.

**The name of $P_{\rm eff}$.** The quantity is not a pressure in the material sense. Material pressure is downstream: it arises from what the lattice conveys, as the transmission of sound depends on the lattice's ability to convey kinetics (author's statement of 16 November 2026), and it first appears in this book in the transport kernel of Chapter 16. $P_{\rm eff}$ is the lattice's delivered intensity at the interaction boundary, in units that coincide with pascals. The symbol is the engine's and is kept; a rename is canon work and waits for approval.

## 11.4 The Coulomb form

Define the interaction radius $R_{\rm int}=\sqrt{R_{\rm lock}\,r_e}=1.539660\times10^{-15}$ m, the geometric mean of the two boundaries. Then

$$F_{\rm C}(r)=\frac\pi4P_{\rm eff}R_{\rm int}^4\frac1{r^2}=\frac\pi4P_{\rm eff}R_{\rm lock}^2r_e^2\frac1{r^2}=\frac{\alpha\hbar c}{r^2}. \tag{11.5}$$

The last step is the definition (11.3) of $P_{\rm eff}$. The engine's `F_coulomb` equalled $\alpha\hbar c/r^2$ exactly at four separations (the Bohr radius, $10^{-9}$ m, $10^{-6}$ m and 1 m), and equalled (11.5) with $R_{\rm int}$ formed in the instrument (test T2). The product $\alpha\hbar c$ equals $k_ee^2$ of the stored CODATA constants to $7.8\times10^{-12}$. At the Bohr radius $F_{\rm C}(a_0)=8.238724\times10^{-8}$ N.

The reading follows from the way the pieces are built. The coupling of the electric interaction is not a separate constant. It is $\alpha\hbar c$, and the Coulomb identity $k_ee^2=\alpha\hbar c$ is the statement that the SI constants $k_e$ and $e$ are a unit bridge for that product. What the law adds to the identity is the geometry of the shadow and the pressure (11.3), which expresses the coupling through the seed constants and the lock boundary.

The measured boundary radius differs from the lock boundary by $0.02\%$ ($R_p=8.414\times10^{-16}$ m against $8.412356\times10^{-16}$ m). With the measured value in place of $R_{\rm lock}$ in one factor the force at $a_0$ changes by the square, $F_{\rm occlusion}(R_p,r_e,a_0)/F_{\rm C}(a_0)=1.000391$ (T6, equal to $(R_p/R_{\rm lock})^2$ to $4\times10^{-16}$). Which radius enters is a matter of scope (residual R11.5).

## 11.5 The handed interaction scales with a count

For an electron and a nucleus of $Z$ proton boundaries the engine takes the effective radius of the nucleus as $\sqrt Z\,R_{\rm lock}$, so that

$$F_{\rm nuc\text{-}e}(Z,r)=\frac\pi4P_{\rm eff}\,(\sqrt Z R_{\rm lock})^2r_e^2\frac1{r^2}=Z\,F_{\rm C}(r) \tag{11.6}$$

(`law_III::F_nuclear_electron`, `laws.hpp:556`). The occluded area is proportional to the count of units, so the effective radius is the square root of the count. The ratio $F_{\rm nuc\text{-}e}(Z,a_0)/F_{\rm nuc\text{-}e}(1,a_0)=Z$ held to $4.4\times10^{-16}$ for $Z=1\ldots20$, and $F_{\rm nuc\text{-}e}(1,a_0)=F_{\rm C}(a_0)$ (test T4). The engine records that the earlier geometry $R_{\rm nuc}=ZR_p$ gave a force proportional to $Z^2$, wrong by a factor $Z$ for every $Z\ge2$ (corrected 2026-07-07); the executed ratio for that geometry at $Z=2$ is $4$. For two units carrying counts $Z_1$ and $Z_2$ the handed interaction is $Z_1Z_2$ times one universal unit area, $F=Z_1Z_2\,\alpha\hbar c/r^2$. The per-body radii form (11.2) is physical for real boundaries, which the engine assigns to the gravity class.

*Supersession.* Section 4.2 of the Complete Laws paper states that the force on He$^+$ at the Bohr radius is four times that on hydrogen ($Z^2$). The engine's corrected rule gives $Z$. The paper's passage predates the correction (residual R11.2).

## 11.6 Hydrogen: the force and the circular law

At the Bohr radius the circular law gives the speed $v=\alpha c$ (Chapter 33), and an electron of inertial mass $m_e$ on that circle needs the centripetal force $m_ev^2/a_0$. The executed values are equal: $F_{\rm C}(a_0)=8.238723504\times10^{-8}$ N against $m_e(\alpha c)^2/a_0=8.238723504\times10^{-8}$ N, within $5.2\times10^{-12}$ (T5). The agreement is algebraic. With the seat relation $a_0=\hbar/(\alpha m_ec)$ and the Coulomb identity $\alpha\hbar c=m_ec^2r_e$,

$$F_{\rm C}(a_0)=\frac{m_ec^2r_e}{a_0^2}=m_e\,\frac{c^2\,\mathrm{Om}_H}{a_0^2},\qquad \mathrm{Om}_H=r_e, \tag{11.7}$$

which is $m_e$ times the circular acceleration $a=c^2\mathrm{Om}/r^2$. Label: CONSTRUCTION, because both sides are built from $\{\alpha,\hbar,m_e,c\}$ and the seat relation. It shows that Law III at the hydrogen rung and the circular law are one relation, with the inertial mass of Law IV supplying the response (Chapter 12).

## 11.7 The sign

Law III as stated in the engine is a magnitude. The shadow of body 1 removes content from one side of the target; the net push on the target comes from the unshadowed directions and carries the target toward the shadowing body. In the electric class the same magnitude can appear with either sign. The engine's source for the sign is EMC03: repulsion is the inverse of convergence, a surplus instead of a deficit, and the sign belongs to the handed redirection of the arrival and not to a substance carried by the bodies. This book states no force law with a sign and no derivation of the handedness (residual R11.3).

## 11.8 Input ledger and residuals

| quantity | role | label |
|---|---|---|
| geometric factors of (11.1) | Chapters 9 and 10 | DERIVED |
| $P_{\rm eff}$ (11.3) | forward form from the seed | COMPUTED, class C with the FLM07 premise; inputs $\alpha$, $\hbar$, $c$, $m_p$, $a_0$ |
| $f=P_{\rm eff}/P_{\rm conv}$ | transfer function | COMPUTED, conditioned on $R_{\rm CMB}$ |
| $F_{\rm C}=\alpha\hbar c/r^2$ | Coulomb form | DERIVED from (11.3); the identity with $k_ee^2$ is a unit bridge |
| $Z$ scaling | handed count | posited rule (engine, 2026-07-07) |
| hydrogen balance | Section 11.6 | CONSTRUCTION |

**Residuals.**

* **R11.1 — the electropause derivation.** The route from the balance of EMC04 to (11.3) and the FLM07 premise are not reproduced here; the engine records the form as class C conditional on that premise.
* **R11.2 — supersession.** The Complete Laws paper (Section 4.2) states $Z^2$ scaling for He$^+$; the engine uses $Z$.
* **R11.3 — the sign.** The handed redirection that gives repulsion its sign has no derivation in this book, and the engine states a magnitude only.
* **R11.4 — the gravity class.** The pressure that goes with the per-body-radii form for real boundaries is not executed here; it enters through the c-boundary in Chapters 33–36. The ratio of the gravity-class and handed couplings is given as a conversion of surfaces in Section 11.3.1, with its status.
* **R11.5 — which radius.** The measured $R_p$ and the lock boundary differ by $0.02\%$, which is $0.04\%$ in the force at the Bohr radius; the scope of each use is stated where it occurs.
* **R11.6 — a stale comment.** The engine's comment at the transfer function gives $2.125\times10^{-17}$; the executed value is $2.1242\times10^{-17}$.
* **R11.7 — the hierarchy arithmetic.** Equations (11.8) and (11.9) and Table 11.2 were evaluated directly and have no registered instrument yet. The electron's own surface in Table 11.2 is a candidate, not a settled length (Chapter 17, R17.7).
* **R11.8 — the spation pitch.** The hierarchy (11.8) is CONSTRUCTION while $\ell_P$ is the stored Planck length. A determination of $\ell_P$, of $H$ or of $\varpi_b$ that does not pass through a gravitational measurement is outstanding; with it the gravitational strength becomes an output.

## 11.9 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch11_universal_interaction
```

Criteria were registered in `Textbook/validation/ch11_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch11_run1_output.txt`) met every criterion.

## 11.10 Exercises and answers

**Exercise 1.** Show $F_{\rm C}(r)\,r^2=\alpha\hbar c$ from (11.3).

*Answer.* $\tfrac\pi4P_{\rm eff}R_{\rm lock}^2r_e^2=\tfrac\pi4\cdot\dfrac{4\alpha\hbar c}{\pi R_{\rm lock}^2r_e^2}\cdot R_{\rm lock}^2r_e^2=\alpha\hbar c$.

**Exercise 2.** By what fraction does the force at the Bohr radius change if the measured $R_p$ replaces $R_{\rm lock}$ in the product $R_1^2R_2^2$?

*Answer.* By $(R_p/R_{\rm lock})^2-1=3.9\times10^{-4}$.

**Exercise 3.** Show that $F_{\rm nuc\text{-}e}(Z,r)=Z\,F_{\rm C}(r)$.

*Answer.* $R_{\rm nuc}^2=ZR_{\rm lock}^2$ enters (11.2) linearly, so the force is $Z$ times the force with $R_{\rm lock}^2$.

**Exercise 4.** Show $V_{\rm disp,e}/(3V_{\rm int})=f$.

*Answer.* $V_{\rm disp,e}=3m_ec^2/P_{\rm conv}$ (Chapter 1) and $V_{\rm int}=m_ec^2/P_{\rm eff}$, so the ratio is $P_{\rm eff}/P_{\rm conv}$.

**Exercise 5.** Verify (11.7) from $a_0=\hbar/(\alpha m_ec)$ and $\alpha\hbar c=m_ec^2r_e$.

*Answer.* $F_{\rm C}(a_0)=\alpha\hbar c/a_0^2=m_ec^2r_e/a_0^2$ by the second relation, and $c^2r_e/a_0^2=a$ is the circular acceleration with $\mathrm{Om}_H=r_e$.

**Exercise 6.** Show that $P_{\rm eff}$ has the dimension of a pressure.

*Answer.* $\alpha\hbar c$ is $\mathrm{M\,L^3T^{-2}}$ and $R_{\rm lock}^2r_e^2$ is $\mathrm L^4$, so the quotient is $\mathrm{M\,L^{-1}T^{-2}}$.

## 11.11 Scope

Established in this chapter: the assembled law and the separate origin of its three geometric factors; the pressure ladder with executed values; the forward form of $P_{\rm eff}$ and its two rewrites, equal to $10^{-11}$; the Coulomb form $\alpha\hbar c/r^2$ and its identity with $k_ee^2$ at the level of the stored constants; the count scaling and the exclusion of the $Z^2$ geometry; and the algebraic identity of the force with the circular law at the hydrogen rung.

Not established: the derivation of $P_{\rm eff}$ from the electropause balance (R11.1), the sign (R11.3), the gravity-class pressure (R11.4), the choice between the measured and the lock radius (R11.5), and a determination of the spation pitch free of a gravitational measurement, without which the hierarchy of Section 11.3.1 is a reading of a construction and not a derived number (R11.7, R11.8).

*Where it leads.* Chapter 12 reads the inertial response that appears in (11.7). Chapter 13 gives the circular speed that enters it. Chapters 33–36 carry the gravity class through the c-boundary.
