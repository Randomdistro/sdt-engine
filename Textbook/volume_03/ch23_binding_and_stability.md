# Chapter 23 — Binding and Stability

*Volume III — Persistent Structures and Nuclear Construction.*
Draft of 10 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. $B$ is a binding energy in MeV, $E_{\rm contacts}$ a contact count, $S_n$ and $S_p$ separation energies. Executable companion: `Textbook/examples/ch23_binding_and_stability.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 23.1 The physical question

The energy of a nucleus is a property of a configuration, and a statement of binding compares the stored and outgoing energy of a configuration with that of separated reference structures under matched boundary conditions. The engine holds the measured masses of the deuteron, triton and helion and a typed alpha value, from which binding energies follow. It does not hold an energy functional of the contact law. The chapter therefore does three things: it tests the simplest candidate for such a functional, a constant energy per contact, in a form fixed before the data are read; it sets out the separation energies as the finite differences they are; and it states what a calculation of restoring response, barriers and binding residuals must deliver.

## 23.2 Binding as a comparison of configurations

For a configuration $X$ with $Z$ protons and $N$ neutrons, in mass form,

$$B(Z,N)=\big(Zm_p+Nm_n-m(Z,N)\big)c^2. \tag{23.1}$$

The stored values (nuclear masses, CODATA 2022) are $B_d=2.224566$ MeV, $B_t=8.481797$ MeV and $B_h=7.717990$ MeV. The helion value is that of the nuclear-mass form; tabulations that start from atomic masses differ from it by tens of eV through the electron binding, so a comparison needs the same convention. The stored alpha value $B_\alpha=28.296$ MeV is typed to five digits and exceeds the nuclear-mass value $28.295616$ MeV (from $m_\alpha c^2=3727.3794066$ MeV) by $3.8\times10^{-4}$ MeV ($1.4\times10^{-5}$ relative); this is a rounding of the stored number (residual R23.4).

A proposed relation $E_{\rm bind}=\varepsilon_{\rm bond}E_{\rm contacts}$ must establish a constant $\varepsilon_{\rm bond}$ over the comparison domain. Contact count alone is insufficient if contact strengths change with orientation, compression or collective circulation. The engine records that a volume-price form $E=P\,\Delta V$ was excluded (NP05; a spread of a factor 45 across reactions, which a units slip had masked) and that a successor, $E_{\rm bind}=\hbar\Delta\omega$ with $\Delta\omega$ the change in meshed-circulation frequency, is under test. Both are engine-recorded statements; neither was re-run here.

## 23.3 A registered test of a constant energy per contact

The hypothesis $H_c$: $B=\varepsilon E_{\rm contacts}$ with one constant $\varepsilon$ over the four species whose contact graphs were fixed in Chapter 19: the deuteron (p–n, 1 contact), the triton (n–p–n, 2), the helion (p–n–p, 2) and the alpha ring (4). The criterion was registered before the binding energies were read: $H_c$ is accepted only if $(\varepsilon_{\max}-\varepsilon_{\min})/\bar\varepsilon\le0.10$. The registered expectation was that $H_c$ is rejected.

**Executed (T1).**

| species | $B$ (MeV) | contacts | $\varepsilon=B/E$ (MeV) | $B/A$ (MeV) |
|---|---|---|---|---|
| d | 2.2246 | 1 | 2.2246 | 1.1123 |
| t | 8.4818 | 2 | 4.2409 | 2.8273 |
| $^3$He | 7.7180 | 2 | 3.8590 | 2.5727 |
| $^4$He | 28.2960 | 4 | 7.0740 | 7.0740 |

Table 23.1. Energy per contact for the four light species, executed (T1).

The spread $(\varepsilon_{\max}-\varepsilon_{\min})/\bar\varepsilon$ is $1.115$, more than ten times the acceptance limit: $H_c$ is rejected. The energy per added contact rises along the sequence, $2.22$ MeV for the first contact, $6.26$ MeV for the second (triton from deuteron) and $10.29$ MeV per contact for helium-4 from helion (two added contacts). A constant energy per contact is ruled out as a description of these four species with these contact graphs. The result does not say that contacts are irrelevant; it says the energy depends on more than the contact count, as expected if contact strength depends on orientation and circulation. The alternatives (the gear-frequency form) need a computed $\Delta\omega$ for the same four configurations before they can be compared.

## 23.4 Separation energies are finite differences

A separation energy compares two independently relaxed nuclei, not a derivative of one fixed geometry. For neutron removal, with one energy convention,

$$S_n(Z,N)=E(Z,N-1)+E_n-E(Z,N)=B(Z,N)-B(Z,N-1), \tag{23.2}$$

and similarly for $S_p$. **Executed (T2).** $S_n(\mathrm d)=2.224566$, $S_n(\mathrm t)=B_t-B_d=6.257230$, $S_n({}^4\mathrm{He})=B_\alpha-B_h=20.578010$, $S_p({}^4\mathrm{He})=B_\alpha-B_t=19.814203$, $S_p({}^3\mathrm{He})=B_h-B_d=5.493423$ MeV. The mass form of $S_n(\mathrm d)$ equalled $B_d$ to $10^{-12}$ and that of the triton equalled $B_t-B_d$ to $1.4\times10^{-16}$. The mirror difference obeys $B_t-B_h=(m_n-m_p)c^2-(m_t-m_h)c^2=0.763807$ MeV (to $2.6\times10^{-13}$ relative): of the order of $1\,$MeV, it is the neutron–proton mass difference ($1.293332$ MeV) less the mass difference of the mirror pair ($0.529525$ MeV); any model of the energy must reproduce it by the same ledger. A closure-induced drop of $S_n$ after a magic occupancy needs the relaxed energy differences themselves, not occupancy arithmetic; the count generator of Chapter 22 locates proposed closures, and the energy response has to predict the size and sign of the change.

## 23.5 Local stability and decay

At an equilibrium $X^*$ of an energy functional $E(X)$ under the constraints of the construction, the constrained Hessian $H=\partial^2E/\partial X^2$ (restricted to admissible perturbations) determines the restoring modes. A positive $H$ excludes local downhill directions. A finite barrier controls escape to another basin, and a decay rate needs the barrier together with a transition operator (Chapter 19). A functional of this kind has to be supplied by the contact law; the engine supplies none. What a calculation must deliver is therefore stated, not assumed: (i) $E(X)$ for each configuration from one contact law; (ii) its constrained Hessian at the equilibrium, with the zero modes removed; (iii) the barrier to each accessible basin; (iv) the separation energies as differences (23.2) of independently relaxed configurations.

## 23.6 One frozen construction, several observables

One frozen construction should produce radii, binding residuals, low-frequency stiffness and accessible decay channels. Retuning the geometry separately for each observable destroys the cross-domain test. The engine's aggregate radius law, $R(A)=R_p(A/\eta)^{1/3}$ with $\eta=\pi/\sqrt{18}$ the close-packing fraction (`nuclear::nuclear_boundary_radius`), is such a construction for the bulk radius.

**Executed (T3).** $\eta=0.7404805$; $R(8A)/R(A)=2$ exactly; $R(1)=R_p\eta^{-1/3}=0.9300\,$fm. For $A=4$ the bulk-law radius is $1.4763$ fm; the contact diameter $2R_p$ (`R_He_contact_diameter`) is $1.6828$ fm; the stored measured helium radius is $1.6755$ fm. The ratios to the measured value are $0.8811$ (bulk law) and $1.0044$ (contact diameter). The two are different definitions: the bulk law is a rms radius of the aggregate, the contact diameter is a contact-seat length of the alpha module, and the engine states the second as a correspondence and not a prediction of the first. Neither equals the measured radius by construction, and the measured value is an operationally inferred radius (Chapter 18, Section 18.4). Isotope-chain flattening and closure tightening (Chapter 22) need further structure; the engine's stated whole-range comparison of the bulk law with 908 measured radii (rms 4.96%) was not re-run here.

## 23.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $m_p$, $m_n$, $m_d$, $m_t$, $m_h$ | `measured::` (CODATA 2022) | MEASURED-INPUT |
| $B_d$, $B_t$, $B_h$ | (23.1) | COMPUTED from the stored masses |
| $B_\alpha$ | 28.296 MeV | MEASURED-INPUT (typed, rounded; residual R23.4) |
| contact counts 1, 2, 2, 4 | Chapter 19 | DERIVED (explicit graphs) |
| Table 23.1, $S_n$, $S_p$, mirror identity | Sections 23.3–23.4 | COMPUTED |
| bulk radius law | `nuclear_boundary_radius` | the engine's law (NP12; zero-fit by its record); arithmetic checked here |
| $R_p$, $R_{\rm He}$ | `measured::` | MEASURED-INPUT |

**Residuals.**

* **R23.1 — the functional.** No energy functional of the contact law is available; restoring modes, barriers and binding residuals are not computed.
* **R23.2 — beyond the contact count.** What fixes the energy per contact (orientation, compression, circulation) is open; the gear-frequency form needs a computed $\Delta\omega$ for the four configurations.
* **R23.3 — repricing.** Reorganisation can reprice surviving contacts (the thermal analysis TD05 of the sources gives a warning of this kind); it was not re-run here.
* **R23.4 — the typed alpha value.** The stored $B_\alpha$ is rounded to five digits ($1.4\times10^{-5}$ relative above the nuclear-mass value).
* **R23.5 — radius definitions.** The bulk-law radius, the contact diameter and the measured radius are different operational quantities; they are not identified.
* **R23.6 — engine-recorded results.** The NP05 exclusion and the 908-radius comparison are cited from the engine's records and not re-run.

## 23.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch23_binding_and_stability
```

Criteria were registered in `Textbook/validation/ch23_PRE_REGISTRATION.md` before the instrument existed, including the registered expectation that $H_c$ is rejected. Run 1 (`ch23_run1_output.txt`) met every T-criterion and failed two lines of V1: the helion "published value" in the registration was the atomic-mass-based tabulation, not the nuclear-mass form the engine computes, and the stored alpha value is rounded. The V1 lines were repaired without touching the T-tests. Run 2 (`ch23_run2_output.txt`) is the run of record and met every criterion.

## 23.9 Exercises and answers

**Exercise 1.** Compute $B$ for the deuteron from (23.1).

*Answer.* $(m_p+m_n-m_d)c^2=2.2246$ MeV.

**Exercise 2.** Compute the energy per contact of $^4$He.

*Answer.* $28.296/4=7.074$ MeV.

**Exercise 3.** Why is $S_n(\mathrm t)=B_t-B_d$?

*Answer.* Removing a neutron from the triton leaves a deuteron, so $S_n=E(\mathrm d)+E_n-E(\mathrm t)=B_t-B_d$ with $B=(Zm_p+Nm_n-m)c^2$.

**Exercise 4.** What does a rejected $H_c$ allow and not allow one to conclude?

*Answer.* It excludes one constant energy per contact for these four graphs. It does not exclude contacts as carriers of the energy, nor any other functional that depends on the contact geometry.

**Exercise 5.** Why is $R(8A)/R(A)=2$?

*Answer.* $R\propto A^{1/3}$, and $8^{1/3}=2$.

**Exercise 6.** Name the three objects that must come from one contact law for a calculation of decay.

*Answer.* The energy functional and its equilibrium, the barrier to the accessible basin, and the transition operator.

## 23.10 Scope

Established in this chapter: the definition of binding and separation energies as comparisons of independently relaxed configurations, with their mass forms and the mirror identity executed; the rejection of a constant energy per contact for the four light species, by a criterion fixed before the data were read; the arithmetic of the bulk radius law and the separation of three radius definitions.

Not established: an energy functional, restoring modes, barriers and binding residuals (R23.1), the dependence of the energy on more than the contact count (R23.2), repricing of surviving contacts (R23.3), and the engine-recorded exclusion and radius comparison (R23.6).

*Where it leads.* Chapter 24 asks what one frozen configuration says about spin, parity and moments, with sources of observed labels kept separate from the prediction.
