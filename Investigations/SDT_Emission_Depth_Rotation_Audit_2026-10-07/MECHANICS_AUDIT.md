# Mechanical audit of shell displacement and phased throughput

Date: 2026-10-07, Australia/Sydney.

Scope: attachment `Pasted text.txt`; current `Engine/include/sdt/laws.hpp`; FLM15 influx-phase assessment; FLM09 reconnection/CMB verdict; CR05 pressure-tensor verdict. Existing geometry, canonical code, source data, and prior outputs remained unchanged. Independent arithmetic used Node.js. The attachment's spherical baryon serves solely as a spherical surrogate; the operator-defined winding, routing, crossing, and four-tour geometry remains a separate physical definition.

Status labels: **identity**, **conditional derivation**, **current implementation**, **open mechanism**, **contradicted inference**. Failure of an inference below establishes a scoped failure of the displayed derivation; broader SDT ontology remains outside the demonstrated result.

## 1. Conserved excluded volume: exact map and far-field displacement

Let a baryonic spherical surrogate exclude volume

\[
\Omega=\frac{4\pi R^3}{3}.
\]

Let \(a\) denote an initial material radius and \(r(a)\) denote a final spatial radius. Uniform number density, spherical symmetry, an unbounded medium, and exact incompressibility imply

\[
4\pi r^2\,dr=4\pi a^2\,da,
\qquad r^3=a^3+R^3.
\]

Consequently,

\[
\boxed{u_L(a)=(a^3+R^3)^{1/3}-a},
\qquad
\boxed{u_E(r)=r-(r^3-R^3)^{1/3}},\quad r\geq R.
\]

The subscripts distinguish displacement tabulated against initial material radius from displacement tabulated against final spatial radius. An initially finite cavity of radius \(A\), enlarged to radius \(R\), instead gives \(r^3=a^3+(R^3-A^3)\). Finite reference geometry and preparation history therefore require an explicit boundary condition.

For \(a\gg R\),

\[
u_L(a)=\frac{R^3}{3a^2}-\frac{R^6}{9a^5}
+\frac{5R^9}{81a^8}+O(R^{12}/a^{11}).
\]

For \(r\gg R\),

\[
u_E(r)=\frac{R^3}{3r^2}+\frac{R^6}{9r^5}
+\frac{5R^9}{81r^8}+O(R^{12}/r^{11}).
\]

Thus \(u=\Omega/(4\pi r^2)\) is a far-field linearized displacement, or an exact flux-density definition under a separate flux interpretation. A static displacement field has units of length; a volume flow rate requires \(\dot u\) and units of volume per time. The attachment's phrase “exact geometric origin” needs the appropriate scope.

The exact finite shell identity, evaluated at final radius, is

\[
\Omega=\frac{4\pi}{3}[r^3-(r-u_E)^3]
=4\pi r^2u_E-4\pi r u_E^2+\frac{4\pi}{3}u_E^3.
\]

The attachment drops the quadratic and cubic displacement terms. At initial radius \(a=R\), the exact displacement is \((2^{1/3}-1)R\), whereas the linear expression gives \(R/3\), an overestimate of \(28.2441\%\). At the final cavity boundary \(r=R\), the limiting exact displacement is \(R\), whereas the linear expression gives \(R/3\). The comparison points involve different radial conventions.

**Result: conditional derivation.** Conserved exclusion produces a geometric inverse-square far field. Acceleration, pressure, refractive delay, and pair force require additional relations.

## 2. Packing correction and the one-diameter surface

For spation diameter \(\ell\), the sphere's material volume is

\[
v_s=\frac{\pi\ell^3}{6}.
\]

For packing fraction \(\eta\), the assigned volume per sphere is \(v_s/\eta\), giving

\[
N_{\rm disp}=\eta\frac{\Omega}{v_s}
=8\eta\left(\frac{R}{\ell}\right)^3.
\]

The attachment's \(N=8(R/\ell)^3\) corresponds to material volume divided by material volume, or packing fraction unity; close-packed spheres contain voids. FCC/HCP packing gives \(\eta=\pi/(3\sqrt2)=0.74048049\); simple cubic spheres give \(\eta=\pi/6\). The simple cubic assigned cell volume is \(\ell^3\), distinct from \(\pi\ell^3/6\).

For a thin shell,

\[
N_{\rm shell}=\eta\frac{4\pi r^2\ell}{v_s}
=24\eta(r/\ell)^2.
\]

The packing factor cancels from the condition \(N_{\rm shell}=N_{\rm disp}\). Consequently, the far-field threshold remains

\[
r_*^{(0)}=\sqrt{\frac{R^3}{3\ell}}.
\]

Exact finite displacement \(u=\ell\) gives

\[
\boxed{r_*^E=\frac{\ell}{2}
+\sqrt{\frac{R^3}{3\ell}-\frac{\ell^2}{12}}},
\qquad
\boxed{a_*^L=-\frac{\ell}{2}
+\sqrt{\frac{R^3}{3\ell}-\frac{\ell^2}{12}}}.
\]

For the specified surrogate, the correction \(\pm\ell/2\) is approximately \(2.31\times10^{-30}\) of the terminal radius. Ordinary double precision cannot resolve the correction. Independent numerical reproduction:

| Quantity | Attachment radius \(R=0.84\) fm | Engine stored radius \(R=0.8414\) fm |
|---|---:|---:|
| Spherical surrogate volume, m³ | \(2.4827127095\times10^{-45}\) | \(2.4951469739\times10^{-45}\) |
| Material-volume count | \(1.1230476953\times10^{60}\) | \(1.1286722977\times10^{60}\) |
| FCC/HCP assigned-cell count | \(8.3159490738\times10^{59}\) | \(8.3575981573\times10^{59}\) |
| Simple cubic assigned-cell count | \(5.8802639821\times10^{59}\) | \(5.9097143315\times10^{59}\) |
| Far-field terminal radius, μm | 3.4962570976 | 3.5050013813 |

The Planck-length reference \(1.616255\times10^{-35}\) m matches [CODATA 2022](https://physics.nist.gov/cuu/pdf/all.pdf). The attachment's \(3.5\) μm arithmetic survives packing correction. Interpretation as a physical terminal boundary remains an extra model assumption.

An object diameter, lattice spacing, minimum geometric displacement, and minimum observable length are distinct definitions. A finite lattice spacing alone allows continuous sub-spacing displacements. A discrete relay could instead encode fractional mean displacement through occupancy probability, phase, orientation, or duty fraction. Selection among the representations requires a relay update law; the inequality \(u<\ell\) supplies no selection rule.

## 3. Incompressibility produces shear, without a derived density gradient

For the linear far field \(\mathbf u=C\hat{\mathbf r}/r^2\), \(C=R^3/3\),

\[
\nabla\!\cdot\mathbf u
=\frac1{r^2}\frac{d}{dr}(r^2u_r)=0\quad(r>0).
\]

Distributionally, the extended singular point-source field satisfies \(\nabla\cdot\mathbf u=4\pi C\delta^3(\mathbf r)=\Omega\delta^3(\mathbf r)\). A finite cavity instead requires a surface boundary condition; the physical interior lacks the assumed medium.

The linear strain components are

\[
\varepsilon_{rr}=-2C/r^3,
\qquad \varepsilon_{\theta\theta}=\varepsilon_{\phi\phi}=C/r^3,
\qquad\mathrm{tr}\,\varepsilon=0.
\]

For the exact map,

\[
\lambda_r=dr/da=a^2/r^2,
\quad\lambda_\theta=\lambda_\phi=r/a,
\quad J=\lambda_r\lambda_\theta\lambda_\phi=1.
\]

Mass/number conservation therefore gives \(n_s(r)=n_{s0}/J=n_{s0}\). The attachment's proposed density \(n_s(r)=n_{s0}[1-\Omega/(4\pi r^3)]\) is absent from the incompressible map. The proposed density also decreases near the baryon, whereas the adjacent prose invokes increased compression. A compressible constitutive model can change density, but exact incompressibility must then be replaced by a density-dependent material map.

At the \(u=\ell_P\) surface, tangential strain is approximately \(\ell_P/r_*=4.62\times10^{-30}\). A Planck-length offset at micrometre radius supplies an extremely small dimensionless strain. Pressure magnitude requires stiffness.

For a linear isotropic elastic control,

\[
W=\frac K2(\mathrm{tr}\,\varepsilon)^2
+\mu\,\varepsilon_{\rm dev}:\varepsilon_{\rm dev}
=\frac{6\mu C^2}{r^6}.
\]

The bulk-energy term vanishes outside the cavity; the shear-energy term survives for \(\mu>0\). Formal integration of the linear far field from cutoff \(R\) yields

\[
E_{\rm lin}=\int_R^\infty4\pi r^2W\,dr
=\frac{8\pi\mu C^2}{R^3}
=\frac{8\pi\mu R^3}{9}.
\]

Near-boundary finite strain prevents promotion of the displayed linear energy into an exact physical self-energy. The calculation demonstrates a finite far-field tail under specified shear modulus and cutoff. For an ideal static fluid, \(\mu=0\), the same displacement geometry supplies no shear energy.

For an incompressible linear elastic continuum with no exterior body force,

\[
\sigma_{rr}=-p-4\mu C/r^3,
\quad\sigma_{\theta\theta}=-p+2\mu C/r^3.
\]

Radial equilibrium gives

\[
\frac{d\sigma_{rr}}{dr}
+\frac2r(\sigma_{rr}-\sigma_{\theta\theta})=-\frac{dp}{dr}=0.
\]

The hydrostatic pressure remains constant; the deviatoric stress falls as \(r^{-3}\). Geometric \(u\propto r^{-2}\), shear stress \(\sigma_{\rm dev}\propto r^{-3}\), and a gravitational acceleration \(g\propto r^{-2}\) are distinct mathematical objects.

A proposed rule \(\mathbf g=-\beta\mathbf u\) can generate inverse-square acceleration, but \([\beta]={\rm s}^{-2}\) and the acceleration rule are new constitutive content. A pressure route needs \(\mathbf F=-V_{\rm eng}\nabla p\), an engagement definition, and a pressure solution. The attachment's \(n(r)=1+\alpha\Omega/r\) also needs \([\alpha]={\rm m}^{-2}\); a dimensionless \(\alpha\) makes the expression dimensionally invalid. No pressure-to-index law follows from volume conservation alone.

## 4. Stationary phase delay: conserved throughput does not create an intensity deficit

For a linear, forward, lossless transfer channel,

\[
E_{\rm out}(\omega)=H(\omega)E_{\rm in}(\omega),
\quad H=e^{i\phi(\omega)},\quad |H|^2=1.
\]

For stationary incident radiation with power spectral density \(S_E\),

\[
S_{\rm out}(\omega)=|H|^2S_{\rm in}(\omega)=S_{\rm in}(\omega).
\]

For a pure delay \(E_{\rm out}(t)=E_{\rm in}(t-\tau)\), stationarity gives \(\langle E_{\rm out}^2\rangle=\langle E_{\rm in}^2\rangle\). Propagation direction and frequency remain unchanged. Equal incoming and outgoing momentum flux therefore supplies zero persistent force after the initial pulse transient. A lossless slab can temporarily receive recoil during pulse entry/exit and store field energy; transient recoil supplies no permanent dark momentum cone.

Interference remains a possible force mechanism. For two fields,

\[
\langle|E_1+E_2|^2\rangle
=\langle|E_1|^2\rangle+\langle|E_2|^2\rangle
+2\mathrm{Re}\,\langle E_1E_2^*\rangle.
\]

A phase shift modifies the cross term when the cross correlation is nonzero. Independent thermal directional modes possess no predetermined phase relation. Blackbody spectral fidelity alone supplies no global phase locking across opposite sky directions. The required object is the spatial/temporal correlation tensor, subject of [Mehta and Wolf's primary calculation](https://journals.aps.org/pr/abstract/10.1103/PhysRev.134.A1143).

Conditional scalar Planck energy-weighted temporal coherence takes the form

\[
g^{(1)}(\tau)=\frac1{\zeta(4)}
\sum_{n=1}^{\infty}(n+i k_BT\tau/\hbar)^{-4}.
\]

The correlation follows by expanding \((e^x-1)^{-1}=\sum_{n\geq1}e^{-nx}\) and integrating \(x^3e^{-(n+i k_BT\tau/\hbar)x}\). Electromagnetic polarization and angular averaging require the corresponding tensor. At \(T=2.7255\) K, characteristic scales are

\[
\hbar/(k_BT)=2.80251\times10^{-12}{\rm s},
\quad\hbar c/(k_BT)=0.840170\ {\rm mm};
\]

\[
h/(k_BT)=1.76087\times10^{-11}{\rm s},
\quad hc/(k_BT)=5.27895\ {\rm mm}.
\]

The thermal angular and cycle scales differ by \(2\pi\); neither scale grants coherent Newtonian attraction over astronomical separations.

Losslessness alone does permit nonzero conservative forces through multiple scattering, mode-density changes, evanescent correlations, coherent optical binding, and fluctuation stresses. [Burns, Fournier, and Golovchenko](https://journals.aps.org/prl/abstract/10.1103/PhysRevLett.63.1233) measured optical binding between dielectric spheres; the reported interaction oscillates in sign at optical-wavelength spacing. Such mechanisms supply legitimate mathematical bridges for examination, but the target-free derivation must establish the interaction sign, range, inverse-square coefficient, and universal matter coupling. A single forward all-pass phase delay does not provide the bridge.

For a slowly cooling input intensity,

\[
I_{\rm out}(t)=I_{\rm in}(t-\tau)
=I(t)-\tau\dot I(t)+O(\tau^2).
\]

Cooling gives \(\dot I<0\), so the delayed intensity exceeds the contemporary intensity. The simple cooling-delay picture predicts an excess along the retarded channel, contrary to the asserted deficit. A corrected pressure mechanism needs interference, a changing delay, spatial redistribution, or stored stress. The sign cannot be assigned from the word “delay.”

## 5. Energy, momentum, and drag closure

Indestructibility does not imply lossless dynamics. Persistent constituents can gain thermal motion, excite internal modes, radiate, or transfer momentum. For a coupled field/medium/body system, the operative balances are

\[
\frac{dE_{\rm stored}}{dt}
=P_{\rm in}-P_{\rm out}-\mathbf F\cdot\mathbf v-P_{\rm heat},
\]

\[
\mathbf F_{\rm body}
=\oint_{\partial V}\boldsymbol\sigma_{\rm field}\cdot\mathbf n\,dA
-\frac d{dt}\int_V\mathbf g_{\rm field}\,dV,
\]

using a tensile-stress convention. A relay substrate also needs explicit medium momentum and stress. Net energy transmission can coexist with momentum redirection; the stress balance then determines force. The attachment provides neither an explicit two-body scattering tensor nor a medium traction law.

Lorentz covariance of field equations does not remove drag from a populated thermal radiation state. In the bath rest frame,

\[
T^{\mu\nu}={\rm diag}(u,u/3,u/3,u/3).
\]

A boost along \(x\) gives incident energy flux

\[
S'_x=cT'^{0x}=-\frac43\gamma^2u v.
\]

For an isotropic scattering control at low velocity with momentum-transfer cross section \(\sigma\),

\[
F'_x\simeq\frac{\sigma S'_x}{c}
=-\frac43\sigma u\frac vc.
\]

The bath state selects a rest frame despite covariant equations. The Fresnel propagation correction for a moving dielectric does not cancel the displayed bath momentum imbalance. A baryon law can potentially suppress drag through transparent coupling, reactive medium response, or symmetry, but an explicit moving-boundary stress integral is required. Transparency also removes simple momentum-shadow gravity.

Reactive inertia \(F=-m_{\rm eff}\dot v\) and dissipative drag \(F=-\eta v\) are distinct response coefficients. Suppression of drag and preservation of inertia require separate calculation. Modern primary derivations include [Sinha and Milonni's blackbody dipole analysis](https://arxiv.org/abs/2204.11113); absorption/re-emission balance alone also fails to remove drag in [Guo et al.'s nonequilibrium steady-state calculation](https://arxiv.org/abs/2108.01539).

## 6. CMB radiation budget versus the current mechanical burden

Using SI exact \(h,k_B,c\),

\[
\sigma_{\rm SB}=\frac{2\pi^5k_B^4}{15h^3c^2}
=5.67037441918443\times10^{-8}\ {\rm W\,m^{-2}K^{-4}},
\]

\[
a_{\rm rad}=4\sigma_{\rm SB}/c
=7.56573325028\times10^{-16}\ {\rm J\,m^{-3}K^{-4}}.
\]

The engine's \(T=2.7255\) K agrees with the measured temperature reference [Fixsen 2009](https://arxiv.org/abs/0911.1955). Independent calculation gives

\[
u_{\rm CMB}=4.17480091993\times10^{-14}\ {\rm J\,m^{-3}},
\quad P_{\rm rad}=u/3=1.39160030664\times10^{-14}\ {\rm Pa},
\]

\[
F_{\rm hemisphere}=cu/4=3.12893457362\times10^{-6}\ {\rm W\,m^{-2}}.
\]

For a spherical capture control of projected area \(A=\pi R^2\), the total power intercepted from an isotropic radiation bath is \(P_{\rm inc}=ucA\). Even perfect redirection into maximal opposing momentum gives the conservative budget bound

\[
|F|\leq\frac{2P_{\rm inc}}c=2uA.
\]

At \(R=0.8414\) fm,

\[
2u\pi R^2=1.85703741653\times10^{-43}\ {\rm N},
\quad m_pg_0=1.64028178101\times10^{-26}\ {\rm N}.
\]

The ratio is \(8.8327880\times10^{16}\). A conventional radiation capture mechanism requires an effective area at least

\[
A_{\rm eff}\geq\frac{m_pg_0}{2u}=1.96450299\times10^{-13}\ {\rm m^2}
\]

for the same maximal redirection bound. A isotropic bath alone produces zero net force; the bound already allows maximal directional asymmetry. Resonant scattering cross sections can exceed physical geometric area, so nuclear geometric area is an explicit control assumption. Stored mechanical stress, coherent reservoirs, and vacuum forces require separate energy budgets and do not fall under the simple intercepted-power bound.

The current engine explicitly supplies a much larger burden:

\[
N=R_{\rm CMB}/\ell_P=5.89449065896\times10^{61},
\quad P_{\rm conv}=Nu_{\rm CMB}=2.46083250256\times10^{48}\ {\rm Pa}.
\]

The burden exceeds ordinary CMB radiation pressure by \(3N=1.76834719769\times10^{62}\). The elementary engine content and total burden are

\[
\epsilon=u\ell_P^3=1.76264727829\times10^{-118}\ {\rm J},
\quad\Phi=N\epsilon=1.03899079169\times10^{-56}\ {\rm J}.
\]

The numerical formulas reproduce. The identification of the historical relay count with simultaneous mechanical pressure remains a load-bearing mechanism. Passing a pulse across \(N\) relay sites does not automatically deposit \(N\) simultaneous copies of the pulse energy at a receiving site. An explicit storage variable, release law, and conserved energy ledger can establish a mechanical memory burden. Without the ledger, multiplication by \(N\) supplies an asserted reservoir rather than a radiation-pressure derivation.

Pressure is dimensionally an energy density, but arbitrary material pressure is not identically total stored energy density. Treating \(P_{\rm conv}\) as actual energy density would imply \(P_{\rm conv}/c^2=2.73804542\times10^{31}\) kg m⁻³. The conversion is conditional; a substrate equation of state and stress-energy balance must decide the relation.

Current Law IV assigns

\[
V_{\rm disp,p}=\frac{3m_pc^2}{P_{\rm conv}}
=1.83264519197\times10^{-58}\ {\rm m^3}.
\]

The spherical surrogate volume is \(1.36150029738\times10^{13}\) times larger. Spherical bounding volume, tube material volume, traversal/swept volume, simultaneous spatial union, and resistance engagement volume require separate symbols and independent mappings. Substitution of the spherical surrogate into the current mass engagement formula would change the mass assignment by the same factor. No substitution occurred during the audit.

## 7. Shell-area dilution preserves frequency; blackbody cooling needs a dynamical rule

In static Euclidean propagation with no interaction or time variation, geometric spreading changes intensity and angular coverage while preserving frequency. Pure area dilution of a Planck spectrum gives

\[
n_\nu' =q\,[e^{h\nu/(k_BT)}-1]^{-1}.
\]

Equality to a new Planck spectrum at temperature \(T'\) for every frequency requires

\[
\frac q{e^{h\nu/(k_BT)}-1}
=\frac1{e^{h\nu/(k_BT')}-1}.
\]

The Rayleigh-Jeans limit gives \(T'=qT\); the Wien slope gives \(T'=T\). Both limits agree only for \(q=1\). Area dilution alone therefore yields a diluted spectrum, not cooling into a new perfect blackbody. A frequency/phase-space transformation can preserve Planck form; the medium mechanism must supply the transformation and corresponding energy transfer.

Under the conventional temperature-redshift mapping \(T=T_0(1+z)\), a 20 °C radiation bath corresponds to \(z=106.558246\), whereas \(z=999\) gives \(T=2725.5\) K. The earlier assistant silently changed the operator's \(z999\) into \(z\approx100\), approximately recovering room temperature but changing the input. Any alternative SDT \(T(z)\) must be evaluated from the alternative law.

At 3000 K, ordinary blackbody energy density is \(0.0612824393\) J m⁻³ and radiation pressure is \(0.0204274798\) Pa. The temperature implies intense thermal excitation; the pressure remains approximately five million times below atmospheric pressure. “Immense radiation pressure” requires a separate mechanical amplification definition.

## 8. Gamma-frequency arrest requires explicit dispersion

For a branch \(\omega(\mathbf k;P)\),

\[
\mathbf v_g=\nabla_\mathbf k\omega,
\quad v_{\rm ph}=\omega/|\mathbf k|,
\quad c_{\rm relay}(P)=\ell_{\rm hop}(P)/\tau_{\rm hop}(P).
\]

High frequency, phase velocity, group velocity, relay rate, and thermal temperature are independent quantities until a constitutive dispersion law connects the definitions. Ordinary \(\omega=c|\mathbf k|\) gives \(v_g=c\) at gamma frequencies. Finite-band lattices can exhibit \(v_g=0\), but branch structure, energy storage, stability, and boundary matching determine the arrest condition.

A nearest-neighbour scalar chain provides a mathematical control, without replacing operator geometry:

\[
\omega(k)=\frac{2c_0}{a}\left|\sin\frac{ka}{2}\right|,
\quad v_g=c_0\cos(ka/2)\quad(0<ka<\pi).
\]

Arrest occurs at \(ka=\pi\). For \(a=\ell_P\), the band-edge energy is \(2\hbar c/\ell_P=3.9121633\times10^9\) J, or \(2.4417803\times10^{28}\) eV. At \(T=10^{12}\) K, \(k_BT=86.1733\) MeV and \(ka\approx7.05824\times10^{-21}\); the chain's fractional group-speed deficit is merely \((ka)^2/8=6.22734\times10^{-42}\). A Planck-spacing cutoff by itself does not arrest hard gamma propagation. A pressure-dependent slow branch can potentially alter the outcome, but the required stiffness/inertia ratio must be computed.

Current FLM09 explicitly labels dispersion A2 and CMB-arrival Arm B **OPEN**. Current CR05 verdict excludes the claimed H₀/transfer closure and retains pressure/freeze-out mechanisms as hypotheses; `laws.hpp` records the same exclusion. Older CR05 README claims of complete cosmological closure cannot supply missing dispersion or pressure mechanics.

## 9. Executable closure requirements

The shortest complete mechanism specification contains:

1. **Geometry:** distinct physical volume, resistance engagement volume, topology, packing, boundary preparation, and excluded-medium map.
2. **Relay dynamics:** conserved state variables, neighbour update rule, movement capacity, delay response, and a defined relation between hop length and hop interval.
3. **Constitutive stress:** stored energy \(W(F,q,\ldots)\), pressure/traction relation, medium momentum, and a force expression from virtual work or stress balance.
4. **Radiation statistics:** incident covariance/correlation tensor and the relationship between observed thermal radiation and the proposed synchronized mechanical loading.
5. **Two-body response:** solve the coupled fields for fixed separation, derive \(F_r(r)=-\partial E_{\rm eq}/\partial r\), and establish attraction, inverse-square scaling, additive baryon coupling, and geometry-dependent corrections without force-target fitting.
6. **Moving-body response:** derive reactive inertia and dissipative drag separately; check energy/momentum conservation under steady motion and acceleration.
7. **Optical response:** derive \(\omega(k;P)\), emission clock/line response, wavelength transfer, and group-delay observables from the same mechanical state.
8. **Boundary history:** derive the CMB temperature evolution, Planck-spectrum preservation, and present stored loading without counting successive transmissions as duplicated present energy.

The spherical excluded-volume identity supplies a useful geometric constraint. A complete pressure, inertia, spectral, and gravity calculation becomes possible after the stress and relay laws select a physical response. The current attachment does not complete the response selection.
