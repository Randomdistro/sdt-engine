# Chapter 19 — Neutron and Conversion

*Volume III — Persistent Structures and Nuclear Construction.*
Draft of 9 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. Energies are given in MeV through the unit bridge $c^2/(e\cdot10^6)$. The emitted channel with winding number 0 (`W_neutrino = 0`, `neutrino.hpp:75`) is called the open-winding channel. Executable companion: `Textbook/examples/ch19_neutron_and_conversion.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 19.1 The physical question

A conversion $X\to Y+\text{outgoing channels}$ has three parts: a ledger (what energy and momentum are available and where they go), a contact bookkeeping (which contacts of the converting unit survive and which must be re-formed), and a rate (how fast the conversion proceeds). The ledger and the bookkeeping can be executed from the engine's rules. The rate cannot: it needs a barrier, a population of states and a transition operator, and the engine supplies none of them for the neutron. The chapter executes the first two, shows how little they fix, and retains the third as a stated programme.

## 19.2 Construction and environment

In the nuclear construction rule every proton has three neutron slots and every neutron three proton slots; a contact joins an unlike pair only; no unit holds more than three contacts (`nuclear::contact_slots`, `laws.hpp:2137`). The rule fixes a capacity, not a count. The modules are the deuteron (p–n, one contact; two neutron slots and two proton slots remain), the triton (n–p–n, a rod of two contacts; one neutron slot and four proton slots remain) and the alpha ring (p–n–p–n, four contacts; two and two remain), as the engine asserts at compile time (`laws.hpp:2153–2161`). A triton is a rod, not a triangular loop of contacts: like units never touch, so the all-edge triangle p–n–n does not occur.

A free neutron has no contacts. An embedded neutron has up to three, all with protons. The two cases have different boundary conditions: nearby persistent structures alter the available final states and the contacts that must be broken. A single free-neutron rate cannot be applied unchanged to every nuclear seat.

## 19.3 The reaction ledger

For an isolated complete region a conversion obeys

$$\Delta E_{\rm stored}+E_{\rm outgoing}=W_{\rm supplied},\qquad \Delta\vec p_{\rm body}+\vec p_{\rm outgoing}+\Delta\vec p_{\rm medium}=0. \tag{19.1}$$

For the free neutron $W_{\rm supplied}=0$ and baryon count is retained: $n\to p+e+(\text{open-winding channel})$. The medium term is set to zero (a decision of the ledger, listed in the residuals), and the relativistic relation of Chapter 13 is used for each body.

**Energy released.** From the stored masses, $m_nc^2=939.565422$ MeV, $m_pc^2=938.272089$ MeV, $m_ec^2=0.510999$ MeV (checked in V1 against the published CODATA energy values to $6\times10^{-12}$),

$$Q=(m_n-m_p-m_e)c^2=0.782333555\ \text{MeV}. \tag{19.2}$$

**Electron endpoint.** With a massless open-winding channel the electron has its largest energy when the channel carries no energy and the proton recoils alone against the electron:

$$E_e^{\max}=\frac{m_n^2+m_e^2-m_p^2}{2m_n}\,c^2=1.292581313\ \text{MeV},\qquad T_e^{\max}=E_e^{\max}-m_ec^2=0.781582363\ \text{MeV}, \tag{19.3}$$

and the proton recoil kinetic energy at that point is $0.000751193$ MeV (751 eV), so that $T_e^{\max}+T_p=Q$ to the last printed digit (T1).

**Executed (T1).** An independent instrument sampled $2\times10^6$ draws of the electron momentum in $[0,1.1\,p^{\max}]$ with isotropic directions of the electron and of the channel, and solved energy conservation for the channel energy by bisection with the proton momentum fixed by momentum conservation. Of the draws, $1\,817\,439$ were accepted and $182\,561$ rejected (no solution with non-negative channel energy). In every accepted draw the residual of energy conservation was at most $1.1\times10^{-13}$ MeV; no accepted draw had an electron energy above (19.3), no rejected draw had one below it, and the largest accepted electron energy was $1.292581117$ MeV, $2\times10^{-7}$ MeV below the closed form. The channel energy ranged over $[2\times10^{-7},\,0.782008]$ MeV. The energy–momentum constraints therefore allow a continuous range of electron and channel energies below (19.3), with the channel carrying the momentum the electron and proton do not; they select no spectrum.

**What the ledger does and does not fix.** If the open-winding channel were absent the two-body decay would give a single electron energy equal to (19.3). The observed existence of a continuous range requires the channel, and the ledger (19.1) with $\Delta p_{\rm medium}=0$ requires it to carry momentum. The shape of the energy distribution within the allowed range needs a spectrum and a coupling rule for the open-winding channel; a topological label does not supply them (residual R19.2). No measured spectrum was loaded.

**Sensitivity to the channel's absolute scale.** The engine stores three values for the channel's mass, $0.02$, $0.029$ and $0.06$ eV (`neutrino.hpp:47–49`), and its header flags absolute masses of this kind as conventions and not measurements. With the proton and channel moving together as one system of mass $m_p+m_\nu$, the endpoint shifts by $-(m_pm_\nu+m_\nu^2/2)/m_n$: $-1.9972\times10^{-2}$, $-2.8960\times10^{-2}$ and $-5.9917\times10^{-2}$ eV for the three values, i.e. $2.6\times10^{-8}$, $3.7\times10^{-8}$ and $7.7\times10^{-8}$ of $Q$ (T2). The direct root agreed with the closed form to $5.9\times10^{-9}$ of the shift (the resolution of the root-finding, which is set by the rounding of the kinetic-energy equation). An endpoint measurement would have to resolve $Q$ to better than $10^{-7}$ to distinguish these values from zero. They cannot be taken as established inputs of the conversion.

## 19.4 The contact ledger of an in-place conversion

When a neutron inside a nucleus converts to a proton, its contacts are with protons, and a proton touches no proton. All the converting unit's contacts are therefore lost. The other contacts survive. The daughter can re-form contacts only up to its capacity, and the converted unit can touch neutrons that still have a free slot. The number that can be re-formed is a degree-constrained bipartite maximum, which the instrument computes by max-flow with the survivors fixed.

The solver was first checked against the exact maximum of a degree-capped complete bipartite graph, $\min(3Z,\,3N,\,ZN)$, for every $1\le Z,N\le12$ (V2). It then converted one neutron in explicit parent graphs:

| parent | contacts lost | survivors | daughter maximum | re-formed |
|---|---|---|---|---|
| free neutron | 0 | 0 | 0 | 0 |
| deuteron p–n | 1 | 0 | 0 | 0 |
| triton n–p–n | 1 | 1 | 2 | 1 |
| alpha ring p–n–p–n | 2 | 2 | 3 | 1 |

Table 19.1. Contact bookkeeping of the conversion of one neutron, executed (T3); the integers were registered before the run and matched in every cell.

In the deuteron the converted unit has no neutron to touch and no contact remains. In the triton the lost contact can be replaced: the converted unit takes the free slot on the remaining neutron, giving the rod p–n–p of the daughter (the three-nucleon module with two protons). In the alpha ring the daughter has capacity 3, and the converted unit re-forms one of the two lost contacts. A rate is not implied by any of these numbers. They say that an embedded conversion has to break and re-form contacts, and that the number depends on the seat.

**A discrepancy in the engine's capacity function.** `nuclear::contact_capacity(Z,N)` returns $3\min(Z,N)$ and is documented as the largest contact count of any bipartite graph with the slot cap. The exact maximum is $\min(3Z,3N,ZN)$, which equals $3\min(Z,N)$ if and only if $\max(Z,N)\ge3$. Over $1\le Z,N\le12$ the two agree except for exactly $(Z,N)=(1,1),(1,2),(2,1),(2,2)$, where the engine returns $3,\,3,\,3,\,6$ and the exact values are $1,\,2,\,2,\,4$ (T4). The function is an upper bound in those four cases. This is recorded for the author as a proposal (residual R19.5); the engine is not edited.

## 19.5 Lifetime is a rate problem

The endpoint energies constrain the possible final configurations. A lifetime requires a barrier, state populations and a transition operator. A decisive calculation would determine the barrier deformation, the outgoing phase-space measure and the transition probability, or a deterministic escape rate, from one contact law. The engine supplies a conversion energy (19.2) and a contact rule, but no barrier, no population and no transition operator; therefore no ab-initio lifetime is assigned here. A free-neutron lifetime from measurement would be an OBSERVED input, not a derived one, and none is loaded. The conversion programme is retained: derive the barrier from the contact law, derive the rate, then compare with the registered measured lifetime.

## 19.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $m_n$, $m_p$, $m_e$ | `measured::` (CODATA 2022) | MEASURED-INPUT |
| $c$, $e$ (unit bridge to MeV) | `measured::c`, `e_charge` | MEASURED-INPUT (unit bridge) |
| $Q$ (19.2), $E_e^{\max}$ (19.3), recoil | Section 19.3 | COMPUTED |
| channel mass values $0.02,0.029,0.06$ eV | `neutrino.hpp` | CONSTRUCTION (convention values per the engine's header) |
| endpoint shifts | Section 19.3 | COMPUTED |
| contact rule, slot counts | engine's (`nuclear`) | the engine's rule |
| Table 19.1, capacity comparison | Section 19.4 | DERIVED (exact integers) and COMPUTED |

**Residuals.**

* **R19.1 — barrier and rate.** The barrier, the populations and the transition operator for a conversion are not supplied; no lifetime is computed.
* **R19.2 — spectrum and coupling.** The spectrum and coupling rule of the open-winding channel are not supplied; the electron energy distribution within the allowed range is not fixed.
* **R19.3 — the channel's absolute scale.** The stored mass values are conventions; their effect on the endpoint is below $10^{-7}Q$.
* **R19.4 — the medium term.** $\Delta p_{\rm medium}=0$ is a decision of the ledger (an isolated complete region); whether the real medium exchanges momentum in a conversion (Chapter 15, R15.2) is not computed.
* **R19.5 — the capacity function.** `contact_capacity` exceeds the exact maximum for $\max(Z,N)<3$; proposed correction $\min(3Z,3N,ZN)$, not applied.
* **R19.6 — the fate of lost contacts.** Where the energy and momentum of the lost contacts go, and the barrier to re-forming them, are not computed.
* **R19.7 — embedded final states.** The final states available to an embedded conversion depend on its seat; only the contact bookkeeping is executed.

## 19.7 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch19_neutron_and_conversion
```

Criteria were registered in `Textbook/validation/ch19_PRE_REGISTRATION.md` before the instrument existed. Run 1 failed the formula clause of T2 by double-precision cancellation of two squared masses near $9\times10^5$ MeV$^2$. The first repair (a bisection on the electron energy in total energies) kept a rounding floor near $5\times10^{-6}$ of the shift, which run 2 reproduced. The second repair (kinetic energies) failed at $8\times10^{-7}$ in run 3 because the repair placed the channel at rest; for a channel of nonzero mass the endpoint is reached when the proton and channel move together, and the deviation equalled the proton recoil energy divided by its mass. That misspecification was introduced at the repair of run 1; the registered closed form was correct. Run 4 (`ch19_run4_output.txt`) is the run of record and met every criterion. The four runs are kept.

## 19.8 Exercises and answers

**Exercise 1.** Compute $Q$ from $m_nc^2-m_pc^2-m_ec^2$.

*Answer.* $939.565422-938.272089-0.510999=0.782334$ MeV.

**Exercise 2.** Derive (19.3).

*Answer.* With the channel carrying zero energy the decay is two-body, $m_nc^2=E_e+E_p$ and $\vec p_p=-\vec p_e$. Then $E_p^2=m_p^2+E_e^2-m_e^2$, and $(m_n-E_e)^2=m_p^2+E_e^2-m_e^2$ gives $E_e=(m_n^2+m_e^2-m_p^2)/(2m_n)$.

**Exercise 3.** Estimate the proton recoil at the endpoint.

*Answer.* $p_e^2=E_e^2-m_e^2=1.4096$ MeV$^2$, so $T_p\approx p_e^2/(2m_p)=7.5\times10^{-4}$ MeV.

**Exercise 4.** Derive the shift of the endpoint for a channel of mass $m_\nu$.

*Answer.* At the largest electron energy the proton and the channel move together as one system of mass $m_p+m_\nu$, so (19.3) holds with $m_p\to m_p+m_\nu$. The difference is $-[(m_p+m_\nu)^2-m_p^2]/(2m_n)=-(m_pm_\nu+m_\nu^2/2)/m_n$.

**Exercise 5.** In the triton, which contact is lost by converting one end neutron, and what replaces it?

*Answer.* The contact between the converting neutron and the proton is lost. The converted unit is now a proton and takes the free proton slot on the remaining neutron, giving p–n–p.

**Exercise 6.** What is the exact contact capacity for $(Z,N)=(2,2)$?

*Answer.* $\min(6,6,4)=4$, the alpha ring; the engine's function returns 6.

## 19.9 Scope

Established in this chapter: the energy released (19.2) and the electron endpoint (19.3), verified by an independent sampler; the constraint that a continuous range requires a momentum-carrying channel; the insensitivity of the endpoint to the channel's stored mass values; the contact bookkeeping of an in-place conversion for four parents; and the exact capacity function with the four-case discrepancy of the engine's version.

Not established: any rate or lifetime (R19.1), the spectrum and coupling of the open-winding channel (R19.2), the real medium's exchange (R19.4), the fate of lost contacts (R19.6) and the final states of an embedded conversion (R19.7).

*Where it leads.* Chapter 20 gives the exact integer grammar of nuclei built from alpha cores, deuterons and tritons; Chapter 21 derives the contact capacity in full.
