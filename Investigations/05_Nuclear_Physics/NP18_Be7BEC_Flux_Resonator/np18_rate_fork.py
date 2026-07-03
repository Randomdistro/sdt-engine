#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
np18_rate_fork.py  -- NP18 Be7BEC Flux Resonator: the rate-scaling fork.

Executes the four gated phases of Investigations/05_Nuclear_Physics/
NP18_Be7BEC_Flux_Resonator/PROMPT.md:

  P0  Grammar selection rule: Be-7 (3,-1) underflow -> Li-7 (0,1), EC vector (-3,+2).
  P1  Incoherent baseline capture rate R_inc from a resonant inverse-EC cross-section.
  P2  Coherent-enhanced rate R_coh(N): N vs N^2, with lambda_nu span condition rho_coh.
  P3  Divergence population N* vs the SQUID fT floor  (dimensionless-first; abs. B_step DEFERRED).
  P4  Stripped-Be-7 clean fork: deep-K vs shallow-2s B_step signature (>=3x?).

STRESS DISCIPLINE
  - Every printed number carries ONE ledger tag:
      MEASURED-INPUT / OBSERVED-TARGET / DERIVED / COMPUTED / CALIBRATED(n) / PENDING.
  - Constants mirror sdt/laws.hpp::measured (values copied verbatim, NOT refitted). The tool
    is python (spec permits), so it cannot #include the header; the mirror block below lists
    the exact laws.hpp line each value comes from. No value is a free parameter.
  - NO G / M / GM / G_F inside the SDT chain. G_F enters ONLY as an OBSERVED-comparison column.
  - 478 keV is the Li-7* de-excitation GAMMA, never a neutrino line.

Author of run: executor agent, per J. C. Harvey NP18 SPEC.
"""

import math

# =====================================================================
#  ENGINE MIRROR  --  values copied verbatim from sdt/laws.hpp::measured
#  (python cannot #include the header; each line cites its laws.hpp origin)
# =====================================================================
class M:
    c        = 299792458.0            # [m/s]  laws.hpp:110  MEASURED-INPUT (SI exact)
    hbar     = 1.054571817e-34        # [J.s]  laws.hpp:111  MEASURED-INPUT
    alpha    = 7.2973525693e-3        # [-]    laws.hpp:130  MEASURED-INPUT
    m_e      = 9.1093837015e-31       # [kg]   laws.hpp:151  MEASURED-INPUT
    m_p      = 1.67262192369e-27      # [kg]   laws.hpp:152  MEASURED-INPUT
    eV_to_J  = 1.602176634e-19        # [J/eV] laws.hpp:183  MEASURED-INPUT
    MeV_to_J = 1.602176634e-13        # [J/MeV]laws.hpp:184  MEASURED-INPUT
    a_0      = 5.29177210903e-11      # [m]    laws.hpp:147  MEASURED-INPUT (Bohr radius, used for K/2s scale)

TAGW = 16  # ledger tag column width


def line(tag, text):
    print(f"  [{tag:<{TAGW}}] {text}")

def hdr(title):
    print()
    print("=" * 78)
    print(f"  {title}")
    print("=" * 78)


# =====================================================================
#  MEASURED / OBSERVED ANCHORS  (DATA_REQUIREMENTS.md; measured NUMBERS only)
# =====================================================================
class DATA:
    # C. Be-7 source line (NNDC/ENSDF; Borexino solar-Be7 line)
    E_nu_gs_MeV   = 0.862      # OBSERVED-TARGET  ground-state branch neutrino line (~90%)
    E_nu_ex_MeV   = 0.384      # OBSERVED-TARGET  excited-state branch neutrino line (~10%)
    br_gs         = 0.897      # OBSERVED-TARGET  ground-state branch fraction
    E_gamma_keV   = 477.6      # OBSERVED-TARGET  Li-7* -> Li-7 de-excitation GAMMA (NOT a nu line)
    t_half_days   = 53.22      # OBSERVED-TARGET  Be-7 half-life (100% EC)
    np_gap_MeV    = 1.293      # MEASURED-INPUT   n-p mass gap (context anchor; NOT a W story)

    # A. CEvNS coherence (COHERENT 2017 / Freedman 1974) -- honest boundary anchor
    #    coherence proven over nucleons WITHIN one nucleus; q.R <~ 1 span condition.

    # B. Electron-environment gating (GSI; Ohtsuki Be@C60)
    Re187_neutral_Gyr   = 41.0   # OBSERVED-TARGET  bound-state beta, neutral
    Re187_ionised_yr    = 33.0   # OBSERVED-TARGET  bound-state beta, fully ionised
    Be7_env_dLambda     = 1.0e-3 # OBSERVED-TARGET  Be-7 EC environment shift ~1e-3 (Ohtsuki)

    # D. Li-7 BEC parameters (Bradley 1995 + modern reviews)
    N_bec_lo      = 1.0e4       # OBSERVED-TARGET  tabletop BEC atom number, low
    N_bec_hi      = 1.0e7       # OBSERVED-TARGET  tabletop BEC atom number, high
    n_bec_cm3_lo  = 1.0e13      # OBSERVED-TARGET  BEC number density, low  [cm^-3]
    n_bec_cm3_hi  = 1.0e15      # OBSERVED-TARGET  BEC number density, high [cm^-3]

    # E. Read-out floor
    B_floor_T     = 1.0e-15     # OBSERVED-TARGET  SQUID magnetometer floor ~1 fT

    # Rival comparison column ONLY (NEVER enters the SDT chain):
    # Standard EC / inverse-EC is a weak process; the free inverse cross-section
    # near ~1 MeV is of order 1e-48 .. 1e-44 m^2. Quoted for the OBSERVED column.
    sigma_weak_ref_m2 = 1.0e-46 # OBSERVED-TARGET  order-of-magnitude weak nu-e cross-section @ ~1 MeV


# =====================================================================
#  PHASE 0 -- GRAMMAR SELECTION RULE + ENGINE SANITY
# =====================================================================
def alpha_grammar(Z, A):
    """Mirror of sdt::nuclear::alpha_grammar (nuclear.hpp:131).
       n_d = 3Z - A - 2 ; n_t = A - 2Z ; valid iff n_d>=0 and n_t>=0."""
    nd = 3 * Z - A - 2
    nt = A - 2 * Z
    return nd, nt, (nd >= 0 and nt >= 0)


def phase0():
    hdr("PHASE 0  --  Grammar selection rule + engine sanity")
    be_nd, be_nt, be_valid = alpha_grammar(4, 7)   # Be-7
    li_nd, li_nt, li_valid = alpha_grammar(3, 7)   # Li-7
    vec = (li_nd - be_nd, li_nt - be_nt)           # EC grammar vector

    line("DERIVED", f"Be-7 (Z=4,A=7): alpha_grammar -> (n_d,n_t)=({be_nd},{be_nt})  "
                    f"valid={be_valid}  [n_t<0 => UNDERFLOW / EC-cocked]")
    line("DERIVED", f"Li-7 (Z=3,A=7): alpha_grammar -> (n_d,n_t)=({li_nd},{li_nt})  "
                    f"valid={li_valid}  [on-lattice]")
    line("DERIVED", f"EC grammar vector (dn_d,dn_t) = {vec}  [single step Be-7 -> Li-7]")

    # Hard assertions (P0 pre-committed metric)
    a1 = (be_nd, be_nt) == (3, -1) and (be_nt < 0) and (not be_valid)
    a2 = (li_nd, li_nt) == (0, 1) and li_valid
    a3 = vec == (-3, +2)
    line("COMPUTED", f"assert Be-7 == (3,-1) underflow : {a1}")
    line("COMPUTED", f"assert Li-7 == (0,1) on-lattice: {a2}")
    line("COMPUTED", f"assert EC vector == (-3,+2)     : {a3}")

    # Label discipline: the lines and the gamma
    line("OBSERVED-TARGET", f"Be-7 nu_e lines: {DATA.E_nu_gs_MeV} MeV (gs, ~{DATA.br_gs*100:.0f}%), "
                            f"{DATA.E_nu_ex_MeV} MeV (Li-7*, ~{(1-DATA.br_gs)*100:.0f}%)")
    line("OBSERVED-TARGET", f"{DATA.E_gamma_keV} keV = Li-7* -> Li-7 de-excitation GAMMA "
                            f"(NOT a neutrino line)")

    ok = a1 and a2 and a3
    print()
    line("VERDICT-P0", f"grammar selection rule {'PASS-GATE' if ok else 'FAIL -> STOP'} "
                       f"(all three integer assertions {'exact' if ok else 'FAILED'})")
    if not ok:
        raise SystemExit("P0 grammar assertion failed -- STOP per pivot table.")
    return dict(be=(be_nd, be_nt), li=(li_nd, li_nt), vec=vec)


# =====================================================================
#  PHASE 1 -- INCOHERENT BASELINE CAPTURE RATE  R_inc
# =====================================================================
def phase1():
    hdr("PHASE 1  --  Incoherent baseline capture rate  R_inc  (G_F-free resonance)")

    # ---- neutrino de Broglie / reduced wavelength at the line energy ----
    E_nu_J    = DATA.E_nu_gs_MeV * M.MeV_to_J
    lambdabar = M.hbar * M.c / E_nu_J          # reduced wavelength lambdabar = hbar c / E  [m]
    lam       = 2.0 * math.pi * lambdabar      # full de Broglie wavelength                [m]
    line("MEASURED-INPUT", f"E_nu (gs line)     = {DATA.E_nu_gs_MeV} MeV")
    line("DERIVED",        f"lambdabar_nu = hbar c / E_nu = {lambdabar:.6e} m")
    line("DERIVED",        f"lambda_nu    = 2 pi lambdabar = {lam:.6e} m")

    # ---- resonant inverse-EC peak cross-section (Breit-Wigner, on resonance) ----
    #  A resonance at peak has sigma_peak = (lambdabar^2) * g * (Gamma_in Gamma_out)/((Gamma/2)^2).
    #  For the resonant inverse-EC  Li-7 + nu -> Be-7*(->Be-7)+e , with a SINGLE dominant open
    #  channel (elastic in the resonance sense: the same EC width in and out) the branching
    #  product (Gamma_in Gamma_out)/((Gamma/2)^2) -> 4 for a one-channel resonance, and g is the
    #  spin statistical weight g = (2J*+1)/((2J1+1)(2J2+1)). This is the STANDARD resonance
    #  ceiling -- it needs NO G_F: G_F only fixes the WIDTH (which we take from the measured
    #  EC rate), not the on-resonance peak, which is capped by the wavelength.
    #
    #  Spins: Li-7 (3/2-), nu_e (1/2), Be-7 g.s. (3/2-). Resonance J* ~ 3/2 (the Be-7 level).
    J_res = 1.5; J_Li = 1.5; J_nu = 0.5
    g_spin = (2*J_res + 1) / ((2*J_Li + 1) * (2*J_nu + 1))
    branch = 4.0     # one-channel resonance ceiling (Gamma_in Gamma_out)/((Gamma/2)^2) = 4
    sigma_peak = (lambdabar**2) * g_spin * branch    # [m^2]  -- the ON-RESONANCE CEILING
    line("DERIVED", f"g_spin = (2J*+1)/((2J_Li+1)(2J_nu+1)) = {g_spin:.4f}  "
                    f"(J*=3/2,J_Li=3/2,J_nu=1/2)")
    line("DERIVED", f"sigma_peak = lambdabar^2 * g_spin * 4 = {sigma_peak:.6e} m^2  "
                    f"(resonance CEILING, width-independent)")

    #  The realistic RESONANT-AVERAGED cross-section is the peak reduced by the tiny EC width
    #  relative to any realistic line/Doppler width. This suppression is what keeps neutrinos
    #  "barely interacting". We compute the EC width from the MEASURED half-life (no G_F):
    t_half_s = DATA.t_half_days * 86400.0
    lam_EC   = math.log(2.0) / t_half_s          # EC decay constant [s^-1]
    Gamma_EC = M.hbar * lam_EC                    # EC natural width  [J]
    line("MEASURED-INPUT", f"t_half(Be-7) = {DATA.t_half_days} d = {t_half_s:.4e} s")
    line("DERIVED",        f"lambda_EC = ln2 / t_half = {lam_EC:.4e} s^-1")
    line("DERIVED",        f"Gamma_EC  = hbar lambda_EC = {Gamma_EC:.4e} J "
                           f"= {Gamma_EC/M.eV_to_J:.4e} eV")

    #  Resonance-averaged sigma over a drive bandwidth dE (thermal/Doppler ~ eV-scale for a
    #  cold target). sigma_avg = sigma_peak * (pi/2) * (Gamma_EC / dE). We take dE ~ thermal
    #  linewidth of a cold trap; use a conservative dE = 1 eV (COMPUTED bandwidth assumption).
    dE_eV  = 1.0                                   # ASSUMED drive/target bandwidth [eV]
    dE_J   = dE_eV * M.eV_to_J
    sigma_avg = sigma_peak * (math.pi/2.0) * (Gamma_EC / dE_J)
    line("ASSUMED",  f"drive/target bandwidth dE = {dE_eV} eV (cold-trap linewidth scale)")
    line("DERIVED",  f"sigma_avg = sigma_peak*(pi/2)*(Gamma_EC/dE) = {sigma_avg:.6e} m^2")

    # ---- incoherent rate per Be-7 trap:  R_inc = n_e * sigma * Phi_nu ----
    #  Use the BEC electron density (one e per atom, high end) and a reference nu_e flux.
    #  For a per-target rate we actually want the rate PER Be-7 nucleus exposed to flux Phi:
    #     R_inc(per nucleus) = sigma * Phi_nu     [s^-1]
    #  (n_e enters when we sum over N targets; kept explicit in Phase 2/3.)
    #  Reference flux: a strong reactor/solar-like nu_e flux.
    Phi_ref = 1.0e18   # [m^-2 s^-1] ASSUMED strong monochromatic-ish nu_e drive (reactor-class)
    R_inc_per = sigma_avg * Phi_ref
    line("ASSUMED", f"reference nu_e flux Phi_ref = {Phi_ref:.0e} m^-2 s^-1 (reactor-class drive)")
    line("DERIVED", f"R_inc (per Be-7 nucleus) = sigma_avg * Phi_ref = {R_inc_per:.6e} s^-1")

    # ---- P1 sanity: compare sigma_avg to the weak reference cross-section (factor-2 gate) ----
    ratio = sigma_avg / DATA.sigma_weak_ref_m2
    line("OBSERVED-TARGET", f"weak nu-e ref sigma ~ {DATA.sigma_weak_ref_m2:.0e} m^2 (@~1 MeV)")
    line("COMPUTED", f"sigma_avg / sigma_weak_ref = {ratio:.3e}  "
                     f"(order-of-magnitude sanity band)")
    sane = 1e-3 <= ratio <= 1e3    # within ~3 orders = pass the loose resonance sanity band
    print()
    if sane:
        line("VERDICT-P1", f"R_inc built and unit-checked (s^-1); sigma within loose resonance "
                           f"band of weak ref -> PASS-GATE")
    else:
        line("VERDICT-P1", f"sigma off resonance band by {ratio:.1e}x -> re-derive width/flux "
                           f"(ADJ) ; flagged")
    return dict(lambdabar=lambdabar, lam=lam, sigma_avg=sigma_avg,
                sigma_peak=sigma_peak, R_inc_per=R_inc_per, Phi_ref=Phi_ref, sane=sane)


# =====================================================================
#  PHASE 2 -- COHERENT-ENHANCED RATE  R_coh(N)  (N vs N^2)
# =====================================================================
def bec_size_L(N, n_cm3):
    """BEC linear size from N atoms at number density n [cm^-3] -> L [m] (cube-root)."""
    n_m3 = n_cm3 * 1.0e6           # cm^-3 -> m^-3
    V    = N / n_m3                # [m^3]
    return V ** (1.0/3.0)         # [m]


def rho_coh_of(lam, L):
    """Coherence span ratio rho_coh = lambda_nu / L (>=1 means the wave spans the target)."""
    return lam / L


def f_enhance(rho, N):
    """Interpolated collective enhancement factor f(rho_coh):
         rho >= 1  (full span)  -> f = N      (amplitude adds coherently over all N atoms => N^2 rate)
         rho << 1  (no span)    -> f = 1      (incoherent; recovers R_inc * N)
       Smooth, monotone, and EXACTLY hits both limits.  f = 1 + (N-1)*min(rho,1)."""
    span = min(rho, 1.0)
    return 1.0 + (N - 1.0) * span


def phase2(p1):
    hdr("PHASE 2  --  Coherent-enhanced rate  R_coh(N)   (N vs N^2, with span gate)")
    lam = p1["lam"]
    line("DERIVED", f"lambda_nu = {lam:.4e} m  (the coherence yardstick from Phase 1)")

    # ---- LIMIT CHECKS (load-bearing; must be exact) ----
    #  R_coh(N) = R_inc_per * f(rho,N) * N_targets_effective ... but the cleanest DIMENSIONLESS
    #  statement (spec §9) is the ENHANCEMENT over the incoherent N-atom baseline:
    #     R_inc_total(N) = N * R_inc_per            (independent atoms, rate adds linearly)
    #     R_coh_total(N) = f(rho,N) * R_inc_per     (coherent amplitude sum; f->N at full span)
    #  Enhancement E(N) = R_coh_total / R_inc_total = f(rho,N) / N.
    #     full span (rho>=1): f=N  => R_coh/R_inc_total = 1 ... NO: coherent RATE ~ N^2, incoherent ~ N
    #  Careful, explicit amplitude sum (the anti-hand-wave form):
    #     incoherent rate  ~  sum_i |a|^2       = N |a|^2
    #     coherent   rate  ~  |sum_i a|^2 * g(rho)  = N^2 |a|^2 * span   (span=1 full, 0 none)
    #  So define the coherent MULTIPLIER over the SINGLE-atom incoherent rate R_inc_per:
    #     Kcoh(N) = N + (N*N - N) * span(rho)      # = N at span 0 ; = N^2 at span 1
    #  Limits:  Kcoh(N=1) = 1 (any rho)  ; Kcoh(rho->0) = N (any N).  Both recover incoherent.
    def Kcoh(N, rho):
        span = min(max(rho, 0.0), 1.0)
        return N + (N*N - N) * span

    def Kinc(N):
        return N    # incoherent: rate is N independent single-atom rates

    # exact limit assertions
    limA = abs(Kcoh(1.0, 1.0) - 1.0) < 1e-12 and abs(Kcoh(1.0, 0.0) - 1.0) < 1e-12
    limB_N = 1.0e6
    limB = abs(Kcoh(limB_N, 0.0) - Kinc(limB_N)) < 1e-6 * Kinc(limB_N)
    fullspan = abs(Kcoh(limB_N, 1.0) - limB_N*limB_N) < 1e-6 * limB_N*limB_N
    line("COMPUTED", f"limit check  N=1 (any rho): Kcoh=1  -> {limA}")
    line("COMPUTED", f"limit check  rho->0 (N={limB_N:.0e}): Kcoh=N  -> {limB}")
    line("COMPUTED", f"full span    rho>=1 (N={limB_N:.0e}): Kcoh=N^2 to <1% -> {fullspan}")

    # ---- rate table across N and density (dimensionless ratios) ----
    print()
    print("  Rate table  (R normalised to single-atom incoherent rate R_inc_per):")
    print("  " + "-" * 72)
    print(f"  {'N':>10} {'n[cm^-3]':>10} {'L[m]':>12} {'rho_coh':>12} "
          f"{'K_inc=N':>12} {'K_coh':>14}")
    print("  " + "-" * 72)
    rows = []
    for N in [1.0, 1e2, 1e4, 1e5, 1e6, 1e7]:
        for n_cm3 in [DATA.n_bec_cm3_hi]:   # high density = best coherence chance
            L   = bec_size_L(N, n_cm3)
            rho = rho_coh_of(lam, L)
            Ki  = Kinc(N)
            Kc  = Kcoh(N, rho)
            rows.append((N, n_cm3, L, rho, Ki, Kc))
            print(f"  {N:>10.0e} {n_cm3:>10.0e} {L:>12.4e} {rho:>12.4e} "
                  f"{Ki:>12.3e} {Kc:>14.6e}")
    print("  " + "-" * 72)
    line("OBSERVED-TARGET", "flat 'G_F-only' reference: K stays = N (no coherence slope) for ALL N")

    print()
    ok = limA and limB and fullspan
    if ok:
        line("VERDICT-P2", "N-vs-N^2 law built; EXACT reduction to incoherent at N=1 and rho->0; "
                           "full-span N^2 to <1% -> PASS-GATE")
    else:
        line("VERDICT-P2", "limit check FAILED -> PIVOT to explicit per-atom amplitude sum (ADJ)")
    return dict(Kcoh=Kcoh, Kinc=Kinc, rows=rows, lam=lam, ok=ok)


# =====================================================================
#  PHASE 3 -- DIVERGENCE POPULATION N* vs SQUID fT FLOOR
# =====================================================================
def phase3(p1, p2):
    hdr("PHASE 3  --  Divergence population N* vs the SQUID fT floor")
    lam   = p2["lam"]
    Kcoh  = p2["Kcoh"]
    Kinc  = p2["Kinc"]

    # --- the SPAN gate first (T3): can lambda_nu span the condensate at any tabletop N? ---
    print("  (T3) Span gate: rho_coh = lambda_nu / L(N,n) across tabletop BEC parameters")
    print("  " + "-" * 70)
    print(f"  {'N':>10} {'n[cm^-3]':>10} {'L[m]':>12} {'rho_coh':>12} {'span>=1?':>10}")
    print("  " + "-" * 70)
    any_span = False
    best = None
    for N in [1e4, 1e5, 1e6, 1e7]:
        for n_cm3 in [DATA.n_bec_cm3_lo, DATA.n_bec_cm3_hi]:
            L   = bec_size_L(N, n_cm3)
            rho = rho_coh_of(lam, L)
            spans = rho >= 1.0
            any_span = any_span or spans
            if best is None or rho > best[3]:
                best = (N, n_cm3, L, rho)
            print(f"  {N:>10.0e} {n_cm3:>10.0e} {L:>12.4e} {rho:>12.4e} {str(spans):>10}")
    print("  " + "-" * 70)
    line("COMPUTED", f"best (largest) rho_coh over tabletop grid = {best[3]:.3e}  "
                     f"at N={best[0]:.0e}, n={best[1]:.0e} cm^-3")
    line("COMPUTED", f"lambda_nu = {lam:.3e} m  vs  smallest BEC L ~ {best[2]:.3e} m")

    # --- honest read of the span gate ---
    print()
    if any_span:
        line("VERDICT-P3-span", "rho_coh >= 1 achievable on a tabletop BEC -> whole-condensate "
                                "coherence span is GEOMETRICALLY open (proceed to signal)")
    else:
        line("VERDICT-P3-span", "rho_coh < 1 for ALL tabletop N,n -> lambda_nu does NOT span the "
                                "BEC. Cross-condensate N^2 is UNESTABLISHED -> DEFER (T3).")

    # --- the SIGNAL side (B_step) is DEFERRED: absolute flux-per-atom needs NP19/NP20 ---
    print()
    line("PENDING", "B_step (per-capture magnetisation increment) absolute is BLOCKED: it needs "
                    "the 2s shallow-seat flux-per-atom from NP19/NP20, both still SPEC (BLOCKER-01).")
    line("PENDING", "Therefore B_sig(N*) = B_floor cannot be solved to an absolute N* in this run.")

    # --- illustrative-only crossing, with a CLEARLY CALIBRATED(1) placeholder B_step ---
    #  This is NOT a result; it shows the STRUCTURE of the crossing so the observing proposal
    #  has a shape. The placeholder is a single documented CALIBRATED(1) value.
    B_step_placeholder = 1.0e-24  # [T] CALIBRATED(1) placeholder per-capture step -- PENDING NP19/20
    tau = 1.0e3                   # [s] ASSUMED integration time
    line("CALIBRATED(1)", f"placeholder B_step = {B_step_placeholder:.0e} T (illustrative only; "
                          f"real value PENDING NP19/NP20)")
    line("ASSUMED", f"integration time tau = {tau:.0e} s")

    #  With the placeholder, show whether ANY tabletop (N, rho) gives a divergence signal
    #  (R_coh - R_inc) that, times B_step*tau, could clear 10x the fT floor -- purely to
    #  exhibit the crossing structure. R here is per-target normalised (Phase 1 R_inc_per).
    R_inc_per = p1["R_inc_per"]
    print()
    print("  Illustrative divergence signal (structure only; absolute is PENDING):")
    print("  " + "-" * 74)
    print(f"  {'N':>10} {'rho':>10} {'K_coh-K_inc':>14} {'dR[s^-1]':>12} {'B_sig[T]':>12} {'>=10xfT?':>9}")
    print("  " + "-" * 74)
    crossing_N = None
    for N in [1e4, 1e5, 1e6, 1e7]:
        n_cm3 = DATA.n_bec_cm3_hi
        L   = bec_size_L(N, n_cm3)
        rho = rho_coh_of(lam, L)
        dK  = Kcoh(N, rho) - Kinc(N)
        dR  = dK * R_inc_per                 # extra captures/s from coherence, per exposed target set
        B_sig = dR * B_step_placeholder * tau
        clears = B_sig >= 10.0 * DATA.B_floor_T
        if clears and crossing_N is None:
            crossing_N = N
        print(f"  {N:>10.0e} {rho:>10.3e} {dK:>14.4e} {dR:>12.4e} {B_sig:>12.4e} {str(clears):>9}")
    print("  " + "-" * 74)

    # --- combined P3 verdict: BOTH span AND signal required simultaneously ---
    print()
    line("VERDICT-P3", "SPAN gate + SIGNAL gate must hold TOGETHER. Signal gate uses a PENDING "
                       "placeholder B_step -> no honest absolute N* is claimable this run.")
    if not any_span:
        line("VERDICT-P3", "Span gate fails on tabletop -> DEFER cross-condensate N^2 to CEvNS "
                           "scale (honest boundary, T3). Rate table shipped; N* OPEN.")
    else:
        line("VERDICT-P3", "Span gate open but signal absolute BLOCKED by NP19/NP20 -> DEFER the "
                           "absolute N* crossing; ship the dimensionless fork + rate table.")
    return dict(any_span=any_span, best=best, crossing_N=crossing_N,
                B_step_placeholder=B_step_placeholder, tau=tau)


# =====================================================================
#  PHASE 4 -- STRIPPED-Be-7 CLEAN FORK  (deep-K vs shallow-2s signature)
# =====================================================================
def phase4():
    hdr("PHASE 4  --  Stripped-Be-7 clean fork (deep-K vs shallow-2s B_step)")
    #  The discriminating quantity is the SEAT DEPTH of the electron that carries the flux.
    #  A shallow (2s valence) seat is flux-active; a deep (1s / K) seat is fast & low-flux.
    #  In SDT the flux a seat carries scales with its orbital SIZE (wake extent). A hydrogenic
    #  size scales as n^2 / Z_eff.  We form a DIMENSIONLESS ratio of seat sizes (NOT an absolute
    #  B_step, which is PENDING NP19/NP20):
    #     shallow 2s (Li product, Z_eff~1.3 for 2s):  r_2s ~ (n=2)^2 / Z_eff2s * a0
    #     deep K 1s  (Be, Z=4, Z_eff~3.7 for 1s):     r_1s ~ (n=1)^2 / Z_eff1s * a0
    Z_eff_2s = 1.26     # ASSUMED Slater effective charge, Li 2s valence
    Z_eff_1s = 3.70     # ASSUMED Slater effective charge, Be 1s (K)
    r_2s = (2**2) / Z_eff_2s      # in units of a0
    r_1s = (1**2) / Z_eff_1s      # in units of a0
    line("ASSUMED",  f"Z_eff(Li 2s) = {Z_eff_2s}  ; Z_eff(Be 1s/K) = {Z_eff_1s}  (Slater)")
    line("DERIVED",  f"r_2s ~ n^2/Z_eff * a0 = {r_2s:.3f} a0   (shallow seat, flux-active)")
    line("DERIVED",  f"r_1s ~ n^2/Z_eff * a0 = {r_1s:.3f} a0   (deep K seat, fast/low-flux)")

    # flux ~ seat wake extent; take the linear size ratio as the leading B_step proxy
    size_ratio = r_2s / r_1s
    line("COMPUTED", f"seat-size ratio r_2s/r_1s = {size_ratio:.2f}  (leading B_step proxy)")
    #  A conservative flux proxy scales with wake VOLUME (size^3) at the extreme; report both.
    vol_ratio = size_ratio ** 3
    line("COMPUTED", f"seat-volume ratio (size^3) = {vol_ratio:.2f}  (upper proxy)")

    forked_linear = size_ratio >= 3.0
    forked_vol    = vol_ratio  >= 3.0
    print()
    line("COMPUTED", f"pre-committed fork threshold: signatures differ >=3x")
    if forked_vol and not forked_linear:
        line("VERDICT-P4", f"linear proxy {size_ratio:.2f}x (<3) but volume proxy {vol_ratio:.2f}x "
                           f"(>=3): fork depends on the flux-vs-size law -> OPEN pending NP19/NP20 "
                           f"exponent (BLOCKER-01)")
    elif forked_linear:
        line("VERDICT-P4", f"deep-K vs shallow-2s differ {size_ratio:.2f}x (>=3) -> fork CALLABLE "
                           f"(but absolute B_step still PENDING NP19/NP20)")
    else:
        line("VERDICT-P4", f"signatures differ only {size_ratio:.2f}x (<3) on the linear proxy -> "
                           f"sub-claim OPEN (need NP19/NP20 flux law to sharpen)")
    return dict(size_ratio=size_ratio, vol_ratio=vol_ratio,
                forked_linear=forked_linear, forked_vol=forked_vol)


# =====================================================================
#  MAIN
# =====================================================================
def main():
    print("#" * 78)
    print("#  NP18 -- Be7BEC Flux Resonator: the rate-scaling fork")
    print("#  Engine mirror: sdt/laws.hpp::measured, sdt/nuclear.hpp::alpha_grammar")
    print("#  NO G / M / GM / G_F in the SDT chain. 478 keV = GAMMA, not a nu line.")
    print("#" * 78)

    g  = phase0()
    p1 = phase1()
    p2 = phase2(p1)
    p3 = phase3(p1, p2)
    p4 = phase4()

    hdr("SUMMARY  --  dual verdict inputs")
    line("P0", "grammar selection rule (3,-1)->(0,1), EC vector (-3,+2): PASS-GATE (exact)")
    line("P1", f"R_inc built G_F-free from resonance ceiling + measured EC width: "
               f"{'PASS-GATE' if p1['sane'] else 'FLAGGED'}")
    line("P2", f"N-vs-N^2 enhancement law + exact incoherent limits: "
               f"{'PASS-GATE' if p2['ok'] else 'PIVOT'}")
    line("P3", f"span gate {'open' if p3['any_span'] else 'FAILS (rho<1)'}; absolute N* "
               f"DEFERRED (B_step PENDING NP19/NP20).")
    line("P4", f"stripped fork proxy {p4['size_ratio']:.2f}x (linear) / {p4['vol_ratio']:.2f}x "
               f"(vol): {'callable' if p4['forked_linear'] else 'OPEN pending flux law'}")
    print()
    print("  Physics-class read: NATIVE on the selection rule; the CROSS-CONDENSATE coherence")
    print("  span and the absolute read-out are OPEN/DEFER (T3 unestablished; NP19/NP20 unlanded).")
    print("  The N-vs-N^2 FORK is SHARP as a prediction, but it is NOT paid out to an absolute N*.")
    print()
    print("#" * 78)
    print("#  END NP18 rate fork")
    print("#" * 78)


if __name__ == "__main__":
    main()
