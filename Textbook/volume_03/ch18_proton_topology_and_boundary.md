# Chapter 18 — Proton Topology and Boundary

*Volume III — Persistent Structures and Nuclear Construction.*
Draft of 9 November 2026. Notation: $\varpi_b$ is the engine's baryon koppa length (`bridge::koppa_per_baryon`), as $\varpi_i$ in Chapter 15; $R_{p,\rm lock}$ is the lock length and $R_p$ the stored measured radius; $\bar\lambda_p$ is the proton wake length. No other circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md` are used. Executable companion: `Textbook/examples/ch18_proton_topology_and_boundary.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 18.1 The physical question

The proton is a persistent form of winding number 3 (the trefoil). Three questions are separated here. What geometry fixes the number of relay contacts of the lock, and does the choice precede any comparison with a radius? What is the length scale of the resulting boundary, and what operational radius is it to be compared with? And how does the boundary relate to the wake length and the baryon koppa length, and which parts of that relation are determinations and which are the same stored length evaluated in two directions? The chapter does not claim the proton's response (scattering, excitation, stability); the topological lock sets admissibility, and the response law is a separate computation.

## 18.2 The lock construction

In a close-packed arrangement of touching spheres of radius $R$ there are two kinds of void. The regular tetrahedral void is bounded by four touching spheres, the regular octahedral void by six. A void of radius $\rho R$ is the centre-to-vertex distance of the arrangement minus $R$. For four mutually touching spheres, with centres at alternate vertices of a cube of edge $\sqrt2R$, the centre-to-vertex distance is $R\sqrt{3/2}$; for six spheres at the vertices of an octahedron of edge $2R$ it is $R\sqrt2$. Hence

$$\rho_t=\sqrt{3/2}-1=0.224745,\qquad \rho_o=\sqrt2-1=0.414214. \tag{18.1}$$

The engine's lock premise (FLM07, Law IV's minimum engaged resistance) prices a void of coordination $q$ by $q\,\rho^3$, the count of contacts times the cube of the void ratio. The prices are $4\rho_t^3=0.045408$ for the tetrahedral void and $6\rho_o^3=0.426407$ for the octahedral, a ratio of $9.39$. The lower price selects coordination $q=4$ (`lock_geometry::trefoil_lock_coordination`, `laws.hpp:352`), before any radius is compared.

**Executed (V1, T1).** The routine was first checked on the simple-cubic cell (eight spheres at the corners of a cube of edge 2), where it returned $\sqrt3-1$ to round-off. Then the tetrahedral and octahedral arrangements were built from coordinates, the nearest-neighbour distance was confirmed to be the sphere diameter in both, and the void ratios were computed as centre-to-vertex distance minus one: they equalled the engine's `tetrahedral_void_radius_ratio` and `octahedral_void_radius_ratio` to $10^{-14}$, and so did the two prices. The coordination chosen by the lower price is $4$, and the engine asserts at compile time that it equals $W_{\rm proton}+1$ with $W_{\rm proton}=3$ (`laws.hpp:2428`). The two integers have different origins, a pricing of voids and a winding number of a knot, and their equality is a convergence of two separate constructions, not a definition of one by the other. The price law itself, $q\rho^3$, is a premise of the engine (residual R18.1); the chapter verifies the geometry that enters it.

## 18.3 The directional fingerprint of the four channels

The four contacts of the tetrahedral lock lie along the directions $(\pm1,\pm1,\pm1)/\sqrt3$ with product of signs $+1$. For a unit direction $\hat n$ define the moments $M_k(\hat n)=\frac14\sum_{a=1}^4(\hat n_a\cdot\hat n)^k$ over the four channel directions $\hat n_a$. Then (`lock_geometry::rank4`, `laws.hpp:363`)

$$M_2(\hat n)=\tfrac13,\qquad M_4(\hat n)=\frac{1+4\,(n_x^2n_y^2+n_x^2n_z^2+n_y^2n_z^2)}{9}. \tag{18.2}$$

The rank-two moment is isotropic for every direction, so the channel set is a spherical 2-design; the first directional fingerprint is rank four. $M_4$ lies between $1/9$ (along a cube axis) and $7/27$ (along $(1,1,1)$), against the isotropic continuum value $1/5$; the fractional range $(7/27-1/9)/(1/5)$ is $0.741$.

**Executed (T2).** Over 20000 random directions $M_2$ equalled $1/3$ to $2.8\times10^{-16}$ and the channel sum equalled the analytic $M_4$ of (18.2) to $3.9\times10^{-16}$. The extremes were $1/9$ and $7/27$ to $6\times10^{-16}$, and the sphere average of $M_4$, from an exact quadrature (24-point Gauss–Legendre in the polar cosine and 64 azimuth points), was $0.2000000000000017$, the isotropic value to $1.7\times10^{-15}$. A rank-four anisotropy of this size is a standing prediction of the lock (B37); no measurement of it is available, and it stays outside the engine's benchmark tally.

## 18.4 The lock length and the radius to compare it with

The lock fixes the geometry; the scale is the proton's mass/action seat. With four action relays,

$$R_{p,\rm lock}=q\,\frac{\hbar}{m_pc}=4\,\frac{\hbar}{m_pc}=8.412356402\times10^{-16}\ \text{m}\qquad(\texttt{law\_III::R\_p\_lock},\ \texttt{laws.hpp:461}). \tag{18.3}$$

The order of derivation matters: the lock premise supplies the geometry and (18.3) expresses the resulting scale in action form. It must not be run backwards into a claim that the topology was inferred from an observed radius. The instrument therefore computed and printed (18.3) first, and read the stored measured radius only after.

The measured entry is a different object. The stored $R_p=8.414\times10^{-16}$ m is the radius of the proton's electromagnetic response as inferred from spectroscopy with a muonic atom; it is a root-mean-square radius of a response distribution, whereas $R_{p,\rm lock}$ is the radius of an exclusion envelope. A comparison needs the same operational definition. The chapter keeps the difference as a number,

$$C_g=\frac{R_p}{R_{p,\rm lock}}=1.000195,\qquad W_{\rm eff}=\frac{R_pm_pc}{\hbar}-1=3.000782, \tag{18.4}$$

and does not set $C_g=1$ in advance. Both are COMPUTED from the stored $R_p$ (T3). The lock length agrees with the stored radius to $0.02\%$; $W_{\rm eff}$ is $0.0008$ above the integer 3.

**What the agreement is and is not.** The matching is a convergence of two chains: $R_{p,\rm lock}$ uses $m_p$, $\hbar$, $c$ and an integer chosen from void geometry, and $R_p$ comes from a spectroscopic measurement. The proton mass is measured in a different apparatus from the radius, so the measured inputs are not shared. The look-elsewhere probability was computed: for the offset $0.00078$ of $R_pm_pc/\hbar$ from $4$, a uniform value lands that close to the single pre-selected integer with probability $0.156\%$ and to any integer from 1 to 10 with probability $0.17\%$. The engine's falsification clause, that the branch is false if $\lvert R_p-R_{p,\rm lock}\rvert$ exceeds $n\sigma$ of the combined uncertainty, needs the measurement's uncertainty, and the stored value carries none (residual R18.3). Radii inferred with different methods differ by more than the 0.02% here, so a pass of the clause at one stored value and a fail at another are both possible; the stated agreement is therefore a statement about this stored number. The pre-selection of $q$ before the radius comparison is documented in the engine's header and cannot be re-observed from outside; the instrument verified only the geometry that selects it. The window used in T3 (1%) makes no claim of precision.

## 18.5 The wake closure

The engine closes the baryon koppa length through $\ell_P^2=\varpi_b\,\bar\lambda_p$ with the wake length $\bar\lambda_p=R_p/(W+1)=R_p/4$ (`bridge::proton_wake`, `laws.hpp:1119`), giving

$$\varpi_b=\frac{\ell_P^2}{R_p/4}=1.241873176\times10^{-54}\ \text{m}\qquad(\texttt{bridge::koppa\_per\_baryon}). \tag{18.5}$$

**Executed (T4).** The stored function equals (18.5) to $10^{-14}$, and $\sqrt{\varpi_b R_p/4}$ returns the stored $\ell_P=1.616255\times10^{-35}$ m exactly. That return is an inverse evaluation of one stored length, not a determination of $\ell_P$: if the stored $\ell_P$ enters the calculation of $\varpi_b$, reinserting $\varpi_b$ in the square root reproduces $\ell_P$ whatever its value. An independent determination of $\ell_P$ needs a wake or koppa measurement chain that does not already contain the target. The legacy value, with the Compton-wake length $\hbar/(m_pc)$ in place of $R_p/4$, is $1.242115812\times10^{-54}$ m; the ratio of the engine's value to it is $1/C_g=0.999805$, exactly the inverse of the comparison (18.4). The stored $\ell_P$ is the Planck length, which carries $G$: contaminating input: $G$, measured by laboratory gravitational torsion-balance determinations (CODATA), enters at `laws.hpp:99` (the stored $\ell_P$). This is the classification already entered in Chapter 6 (residual R6.1), $\ell_P$ CALIBRATED(1); the closure (18.5) inherits it.

## 18.6 Pressure and interaction volume

The interaction volume of the proton–electron pair is the cylinder of cross-section $(\pi/4)R_{p,\rm lock}^2$ and length $r_e$, $V_{\rm int}=(\pi/4)R_{p,\rm lock}^2r_e=1.566235\times10^{-45}$ m$^3$, and the effective pressure of the engine is $P_{\rm eff}=4\alpha\hbar c/(\pi R_{p,\rm lock}^2r_e^2)=5.227252\times10^{31}$ Pa (Chapter 11). Substituting the Coulomb identity $\alpha\hbar c=m_ec^2r_e$ gives $P_{\rm eff}=m_ec^2/V_{\rm int}$.

**Executed (T5).** $P_{\rm eff}V_{\rm int}/(m_ec^2)=1+5.2\times10^{-12}$ and $\alpha\hbar c/(m_ec^2r_e)=1+5.2\times10^{-12}$. The two forms are one derivation chain written twice (the engine labels the volume form an identity); presenting them as two experimental determinations would count the evidence twice. The identity $\alpha\hbar c=m_ec^2r_e$ is the relation among the CODATA entries seen in Chapter 17, so it is shared-input.

## 18.7 What the lock does not fix

A topological lock sets which configurations are admissible. Stability, scattering and excitation of the proton need the response law: the microscopic contact stiffness, the cross-section of the route and the outgoing redistribution. None is computed here (residual R18.4). The engine's classification of the winding number rests on the Alexander polynomial of the $(2,3)$ torus knot; the engine's comment at `laws.hpp:2404` gives the polynomial of the $(2,5)$ knot for it (recorded in Chapter 7, residual R7.1), and the engine itself states that its validation of the classification gives no barrier, lifetime or stability spectrum.

### 18.7.1 The trefoil as an engine on the throughput

*Added 16 November 2026 from the author's statements of that date and from the investigation CQ14 (May 2026). Only the numbers below were re-evaluated; the mechanism statements of CQ14 were not re-derived, and its text predates several rulings on vocabulary (residual R18.7).*

A persistent orbital structure is not a passive obstacle standing in the throughput. The six-$\pi$ trefoil is a necessary way of exploiting it: the structure runs on the convergence that arrives, and it persists because it is continuously driven. In the author's words, atoms are turbines of the background throughput. CQ14 puts it as fuel, engine and transmission: the convergence is the fuel, the trefoil the engine, the lattice the transmission.

The engine header carries the kinematic part of this (`traction` block of `laws.hpp`):

* **The demand.** A $(2,3)$ mode sweeps a contact spation through $q\times2\pi=6\pi$ per circulation, a demanded angular rate $\omega_{\rm demand}=3m_pc^2/\hbar=4.2765\times10^{24}$ rad per SI second.
* **The supply.** At radius $R$ the lattice relays at most $\omega_{\max}=c/R$; at the stored $R_p$ this is $3.5630\times10^{23}$ rad per SI second.
* **The mismatch.** Their ratio is $3R_pm_pc/\hbar$: exactly $3(W+1)=12$ with the lock radius and $12.0023$ with the stored measured radius.
* **The phase rate at the proton boundary.** With $k=(1/\alpha)\sqrt{R_p/a_0}=0.54643$ the phase rate there is $c/k=1.8301\,c$ (the sources quote $1.831\,c$). It is a phase rate inside hydrogen's c-boundary $r_e$ and not a front or signal speed (Chapter 3, Table 3.0); the relay front never exceeds one hop per interval.
* **The gearing.** The ratio of the proton's demanded rate to the hydrogen orbital rate is $3a_0m_pc/(\alpha\hbar)=1.0344\times10^{8}$.

All five are COMPUTED from $\{m_p,\hbar,c,\alpha,a_0,R_p\}$. CQ14 goes on to say that the mismatch is taken up in three outputs: a radial $1/r^2$ gradient, an organised rotation of the lattice, and an azimuthal entrainment in which the electron is driven by the proton's wake at $k=n/\alpha$. Those statements are recorded here as the source's and are not established by this book.

What a turbine statement needs and the sources do not yet supply is a rate of work: the power drawn from the convergence per structure, and its balance against what is released. CQ14 stops at a force per contact spation. The author reports calculations of this kind that were not located in the repository for this edition (residual R18.7).

## 18.8 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $\hbar$, $m_p$, $m_e$, $\alpha$ | `measured::` | MEASURED-INPUT |
| $c$ | `measured::c` | MEASURED-INPUT (unit bridge) |
| void ratios (18.1), prices, $q=4$ | Section 18.2 | DERIVED (geometry, executed from coordinates) under the engine's price law |
| price law $q\rho^3$ (FLM07) | engine's | the engine's premise; not derived here |
| $M_2$, $M_4$ of (18.2) | Section 18.3 | DERIVED and COMPUTED |
| $R_{p,\rm lock}$ (18.3) | $0.841235640$ fm | COMPUTED from the lock and the mass/action seat |
| stored $R_p$ | $8.414\times10^{-16}$ m | MEASURED-INPUT (no uncertainty stored) |
| $C_g$, $W_{\rm eff}$ (18.4) | Section 18.4 | COMPUTED |
| $\ell_P$ | `measured::l_P` | CALIBRATED(1) (carries $G$; Chapter 6, R6.1) |
| $\varpi_b$ (18.5) | $1.241873176\times10^{-54}$ m | COMPUTED from the stored lengths |
| $V_{\rm int}$, $P_{\rm eff}$ | Section 18.6 | COMPUTED; identity, shared-input |

**Residuals.**

* **R18.1 — the price law.** That the lock selects the lowest $q\rho^3$ is the engine's FLM07 premise; the geometry of the voids is verified, the pricing is not derived here.
* **R18.2 — pre-selection.** That $q$ was fixed before the comparison with a radius is documented in the engine header and is not independently observable.
* **R18.3 — the uncertainty.** The stored $R_p$ has no uncertainty, so the engine's falsification clause cannot be evaluated; the operational definitions of the lock radius and the measured radius differ (Section 18.4).
* **R18.4 — response.** Stability, scattering and excitation of the proton are not computed.
* **R18.5 — the wake length.** The closure (18.5) is an inverse evaluation; the independent determination of $\ell_P$ is outstanding.
* **R18.6 — the anisotropy.** The rank-four anisotropy (18.2) is a prediction with no measurement.
* **R18.7 — the engine reading.** The mechanism statements of CQ14 (three outputs of the mismatch, the driven electron) are not re-derived, its text needs restating in current vocabulary, the five numbers of Section 18.7.1 have no registered instrument yet, and the power drawn from the convergence per structure is not computed or located.

## 18.9 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch18_proton_topology_and_boundary
```

Criteria were registered in `Textbook/validation/ch18_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch18_run1_output.txt`) is the run of record and met every criterion.

## 18.10 Exercises and answers

**Exercise 1.** Derive the tetrahedral void ratio.

*Answer.* Alternate vertices of a cube of edge $a$ form a regular tetrahedron of edge $a\sqrt2$. Touching spheres need $a\sqrt2=2R$, so $a=\sqrt2R$. The distance from the cube centre to a vertex is $a\sqrt3/2=R\sqrt{3/2}=1.2247R$, and the void radius is $(\sqrt{3/2}-1)R$.

**Exercise 2.** Compute the ratio of the two prices.

*Answer.* $6\rho_o^3/(4\rho_t^3)=0.426407/0.045408=9.39$.

**Exercise 3.** Show that the sphere average of $M_4$ is $1/5$.

*Answer.* $\langle n_x^2n_y^2\rangle=1/15$ over the sphere, so $\langle n_x^2n_y^2+n_x^2n_z^2+n_y^2n_z^2\rangle=1/5$ and $\langle M_4\rangle=(1+4/5)/9=1/5$.

**Exercise 4.** What does $W_{\rm eff}=3.000782$ mean for $C_g$?

*Answer.* $W_{\rm eff}+1=4C_g$, so $C_g=4.000782/4=1.000195$.

**Exercise 5.** Why is the ratio of the engine's $\varpi_b$ to the legacy value equal to $1/C_g$?

*Answer.* The two differ only in the length in the denominator: $R_p/4$ against $\hbar/(m_pc)=R_{p,\rm lock}/4$. Their ratio is $R_{p,\rm lock}/R_p=1/C_g$.

**Exercise 6.** Why do $P_{\rm eff}$ and $m_ec^2/V_{\rm int}$ not count as two determinations?

*Answer.* They differ by the substitution $\alpha\hbar c=m_ec^2r_e$, an identity of the stored constants, so they are one expression.

## 18.11 Scope

Established in this chapter: the void geometry and the lower price that select coordination 4, executed from coordinates; the rank-two isotropy and rank-four fingerprint of the four channels; the lock length (18.3) as a prediction stated before the comparison, its ratio $C_g=1.000195$ to the stored radius, and the probability of that closeness by chance; the wake closure as an inverse evaluation with its inherited classification; and the interaction-volume identity.

Not established: the price law (R18.1), the pre-selection (R18.2), the significance of the comparison without an uncertainty (R18.3), the proton's response (R18.4), an independent determination of $\ell_P$ (R18.5), a measurement of the rank-four anisotropy (R18.6), and the mechanism and power of the engine reading of Section 18.7.1 (R18.7).

*Where it leads.* Chapter 19 turns to the neutron, the exposed and remnant configurations of the lock and the conversion channels.
