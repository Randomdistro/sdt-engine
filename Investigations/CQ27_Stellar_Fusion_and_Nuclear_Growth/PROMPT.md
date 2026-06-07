# CQ27: Stellar Fusion, Nuclear Growth, and Reciprocal Shell Mirroring — Prompt

## 1. Objectives

This investigation evaluates the dynamical growth of atomic nuclei from the $^4\text{He}$ core to $Z \le 20$ (H to Ca) using the Atomicus deu/tri construction grammar. We construct a pathway compiler to trace fusion trajectories, compute geometry-only contact occlusion scores and alpha-normalised occlusion units, evaluate trefoil rotational dynamics under local convergence pressure, model stellar/BBN temperature-driven electron capture (EC) delays via Saha ionization, and map the spatial coordinates of the core to the geometry of the electron shells.

## 2. Theoretical Formulations

### A. Pathway Compiler
Every nuclear addition step represents the fusion of a deuteron ($d$) or triton ($t$):
$$\text{Parent}(Z, A) + d \to \text{Child}(Z+1, A+2)$$
$$\text{Parent}(Z, A) + t \to \text{Child}(Z+1, A+3)$$

Growth pathways start at the $^4\text{He}$ core $(n_d=0, n_t=0)$ and grow recursively to target stable states.
*CQ25 Atomicus Nuclear Grammar is declared FROZEN.*

### B. Occlusion Bond Symmetries & Shielding
The occlusion contact count $B_{\text{geom}}$ determines geometric occlusion structure:
$$B_{\text{geom}} = (6 + n_d + 3 n_t) + \text{interface contacts}$$
The alpha-normalised occlusion unit is calculated as:
$$E_{\text{occ\_unit}} = k_{\text{occ}} \cdot B_{\text{geom}}$$
where $k_{\text{occ}} = 28.30 / 6.0$ MeV/contact.
*Note: $E_{\text{occ\_unit}}$ represents the alpha-normalised occlusion unit scale, NOT the total binding energy $E_B$ (which would require Coulomb repulsion and saturation term integrations).*

### C. Trefoil Phase Windings & Symmetries
- **Winding W=3**: Nucleons are modeled as trefoil vortices with surface $k_p \approx 0.5464$ (superluminal rotation speed $v_p = c/k_p \approx 1.83c$).
- **Safeguard**: The rotational velocity is a *phase-winding velocity proxy* ONLY. It is not a material transport velocity and not a signal velocity.
- **Magnetic Gears**: Pairings of tritons ($n_t$ even) form counter-rotating modes, cancelling outer wake drag and maximizing stability. Odd $n_t$ results in an unpaired wake (office-pop active).

### D. Electron Capture (EC) Timing
- **Ionization Gate**: Fully ionized species at temperature $T$ cannot undergo EC due to the absence of bound electrons.
- **Saha Equation**: Determines the bound electron density at the nuclear surface:
  $$\frac{x_{\text{ion}}^2}{1 - x_{\text{ion}}} = \frac{1}{n_e} \left(\frac{m_e k_B T}{2\pi \hbar^2}\right)^{3/2} e^{-\frac{E_{\text{ion}}}{k_B T}}$$
- **Suppressor Factor**: Free electrons have high $v_{\text{trans}}$, yielding small $v_{\text{circ}}$ (movement budget), which prevents coupling to the $W=3$ core. This suppresses EC at high $T$.

### E. Inverted Mirror Mapping
- The spatial arrangement of $(n_d, n_t)$ dictates the symmetry axes of the convergence field.
- The electronic shells adjust to occupy the resulting geometric voids:
  - $n_d = 4$ (C-12) $\implies$ tetrahedral shell symmetry.
  - $n_d = 6$ (O-16) $\implies$ octahedral/cubic shell symmetry.
- **Validation**: Expand the mirror-shell mapping across the first 20 elements (H to Ca), comparing predicted shell categories (valence electron equivalents) directly to known valences with PASS/FAIL columns.

## 3. Verification Stages

- **Stage A**: Tree search from $^4\text{He}$ to $Z=10$ outputting all valid pathways and identifying bottlenecks. Declare CQ25 grammar frozen.
- **Stage B**: Calculate $B_{\text{geom}}$ and $E_{\text{occ\_unit}}$, separating the occlusion-unit scale from total binding energy.
- **Stage C**: Calculate trefoil phase velocity, labeling it as a phase-winding proxy and warning against material/signal interpretations.
- **Stage D**: Temperature-dependent EC rate curves for Be-7, Tl-205, and Re-187 showing ionization state transitions.
- **Stage E**: Mirror-shell predictions across the first 20 elements with validation columns comparing against known valences.
