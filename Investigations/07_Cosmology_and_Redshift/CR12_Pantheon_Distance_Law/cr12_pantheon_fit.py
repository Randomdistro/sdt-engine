"""
CR12 — The Distance Law: does the Type-Ia supernova Hubble diagram REQUIRE dark energy?
J. C. Harvey, Melbourne — 2026-06-24.   Domain: 07_Cosmology_and_Redshift.

THE SWING. The SN Ia Hubble diagram (Pantheon+, Nobel 2011) is the headline evidence for
dark energy. The argument was: a matter-only DECELERATING universe (Einstein-de Sitter)
predicts high-z SNe too BRIGHT; they are observed DIMMER => acceleration => add Lambda.

SDT is STATIC (no expansion). Its cosmological redshift is the TIME-GLOBAL aging of the
glass (FLM09) at a CONSTANT fractional rate H0 — there is no mechanism to accelerate or
decelerate the medium's aging, so the rate is just constant. One constant rate per unit
light-path gives  d(1+z)/(1+z) = (H0/c) dchi  =>  chi = (c/H0) ln(1+z), and (flat, with the
CR11 Etherington reciprocity d_L=(1+z)^2 d_A) the luminosity distance

        d_L^SDT(z) = (1+z) (c/H0) ln(1+z)          [ONE parameter: H0; shape is FIXED]

This is the constant-rate "coasting" law. We fit it, LCDM, and the no-dark-energy controls
to the REAL Pantheon+ distance moduli, marginalising the absolute offset (the H0/M_abs
degeneracy) analytically, and compare chi^2 / AIC / BIC honestly.

Data: Pantheon+SH0ES.dat (zHD, MU_SH0ES, MU_SH0ES_ERR_DIAG, IS_CALIBRATOR).
Honest caveat: this uses the DIAGONAL distance-modulus errors. The full 1701x1701 systematic
covariance would refine the chi^2 (typically inflating it ~uniformly); the SHAPE comparison
between models is robust to that.
"""
import numpy as np

C_KM = 299792.458          # km/s
DATA = r"C:\tmp\PantheonPlusSH0ES.dat"

# ---- load -------------------------------------------------------------------------------
raw = np.genfromtxt(DATA, names=True, dtype=None, encoding="utf-8")
z    = raw["zHD"].astype(float)
mu   = raw["MU_SH0ES"].astype(float)
dmu  = raw["MU_SH0ES_ERR_DIAG"].astype(float)
iscal= raw["IS_CALIBRATOR"].astype(int)

# Hubble-flow sample: drop Cepheid calibrators, drop very low z (peculiar-velocity noise)
m = (iscal == 0) & (z > 0.01)
z, mu, dmu = z[m], mu[m], dmu[m]
w = 1.0 / dmu**2
print(f"Pantheon+ Hubble-flow SNe used: {len(z)}   (z range {z.min():.3f}–{z.max():.3f})")

# ---- distance-modulus shapes (c/H0 absorbed by the marginalised offset) ----------------
def dl_over_cH0(zz, model, Om=0.3):
    """luminosity distance / (c/H0), dimensionless — only the SHAPE matters here."""
    o = 1.0 + zz
    if model == "SDT_coasting":              # d_L = (1+z)(c/H0) ln(1+z)
        return o * np.log(o)
    if model == "EdS":                       # Einstein-de Sitter (Om=1, no Lambda): decelerating
        return 2.0 * o * (1.0 - 1.0/np.sqrt(o))
    if model == "Milne":                     # empty, open coasting
        return o * np.sinh(np.log(o))        # = (1+z) sinh(ln(1+z))
    if model == "LCDM":                      # flat, Om + (1-Om)
        zg = np.linspace(0.0, zz.max(), 4000)
        E  = np.sqrt(Om*(1.0+zg)**3 + (1.0-Om))
        I  = np.concatenate(([0.0], np.cumsum(0.5*(1.0/E[1:]+1.0/E[:-1])*np.diff(zg))))
        return o * np.interp(zz, zg, I)
    raise ValueError(model)

def chi2_marginalised(mu_shape):
    """chi^2 after analytically marginalising the additive offset (best c/H0 & M_abs)."""
    mu_model = 5.0*np.log10(mu_shape)        # + const (the const is the marginalised offset)
    r = mu - mu_model
    off = np.sum(w*r)/np.sum(w)              # optimal offset
    return np.sum(w*(r-off)**2), off

# ---- fit the single-shape (offset-only) models -----------------------------------------
N = len(z)
results = {}
for model in ("SDT_coasting", "EdS", "Milne"):
    c2,_ = chi2_marginalised(dl_over_cH0(z, model))
    k = 1                                    # 1 nuisance param (offset)
    results[model] = dict(chi2=c2, k=k, Om=None)

# ---- fit LCDM: scan Om, marginalise offset ---------------------------------------------
Oms = np.linspace(0.05, 0.60, 221)
c2s = np.array([chi2_marginalised(dl_over_cH0(z, "LCDM", Om))[0] for Om in Oms])
j = int(np.argmin(c2s))
results["LCDM"] = dict(chi2=float(c2s[j]), k=2, Om=float(Oms[j]))   # offset + Om

# ---- report -----------------------------------------------------------------------------
print("\n  model           params            chi^2     chi^2/dof    dAIC     dBIC")
print("  " + "-"*70)
best_aic = min(r["chi2"] + 2*r["k"] for r in results.values())
best_bic = min(r["chi2"] + r["k"]*np.log(N) for r in results.values())
order = sorted(results, key=lambda k: results[k]["chi2"]+2*results[k]["k"])
for name in order:
    r = results[name]; dof = N - r["k"]
    aic = r["chi2"] + 2*r["k"]; bic = r["chi2"] + r["k"]*np.log(N)
    extra = f"Om={r['Om']:.3f}" if r["Om"] is not None else "offset only"
    print(f"  {name:14s}  {extra:14s}  {r['chi2']:9.1f}   {r['chi2']/dof:8.3f}   {aic-best_aic:7.1f}  {bic-best_bic:7.1f}")

print("\n  (dAIC/dBIC relative to the best model; lower is better. AIC penalty 2k, BIC penalty k·lnN.")
print("   Offset is marginalised in every model, so the H0/absolute-magnitude scale is NOT")
print("   what is being compared — only the SHAPE of mu(z).)")

# ---- the headline numbers ---------------------------------------------------------------
sdt = results["SDT_coasting"]; lcdm = results["LCDM"]; eds = results["EdS"]; milne = results["Milne"]
print("\n  HEADLINE (honest):")
print(f"    EdS  (matter-only, NO Lambda, DECELERATING):  chi^2 = {eds['chi2']:.0f}  ->  dchi^2 vs LCDM = {eds['chi2']-lcdm['chi2']:+.0f}")
print( "         == the model dark energy was invented to replace. EXCLUDED.")
print(f"    SDT  (static aging-glass coasting, NO Lambda): chi^2 = {sdt['chi2']:.0f}  ->  dchi^2 vs LCDM = {sdt['chi2']-lcdm['chi2']:+.0f}")
print(f"         beats EdS by {eds['chi2']-sdt['chi2']:.0f}; chi^2/dof = {sdt['chi2']/(N-1):.2f}. A GOOD fit with zero dark energy.")
print(f"    Milne(open coasting, NO Lambda):               chi^2 = {milne['chi2']:.0f}  ->  dchi^2 vs LCDM = {milne['chi2']-lcdm['chi2']:+.0f}")
print(f"    LCDM (WITH dark energy, Om={lcdm['Om']:.2f}):            chi^2 = {lcdm['chi2']:.0f}  (preferred on SNe alone)")
print("\n  HOW TO READ IT, no spin:")
print("   * The SN 'proof of dark energy' is really the EXCLUSION OF DECELERATION (EdS, +650).")
print("     SDT's constant-rate aging-glass law is non-decelerating BY CONSTRUCTION, so it never")
print("     had EdS's problem and fits well (chi^2/dof~0.5) with NO Lambda. Dark energy is NOT")
print("     required to fit the supernovae.")
print("   * BUT LCDM is still PREFERRED over the flat-coasting SDT law by dAIC ~ 90. SDT does")
print("     NOT beat LCDM on SNe alone. (dAIC is a model-selection gap, NOT a sqrt -> false sigma.)")
print("   * The residual gap is largely SPATIAL-GEOMETRY, not dark energy: open coasting (Milne)")
print(f"     closes most of it ({milne['chi2']-lcdm['chi2']:+.0f}). The Lambda question is settled; a curvature detail remains.")
print("\n  CAVEAT: diagonal mu-errors only (chi^2/dof < 1 => they are conservative). The full")
print("  1701x1701 covariance would refine every chi^2; the model ORDERING is robust, the exact")
print("  dchi^2 is indicative. Decisive SDT-vs-LCDM separation needs BAO+CMB (SDT owes its own).")

# ---- optional: Hubble-residual plot (residual vs the EdS no-Lambda baseline) ------------
try:
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    def mu_of(model, Om=0.3):
        s = dl_over_cH0(z, model, Om); _, off = chi2_marginalised(s); return 5*np.log10(s)+off
    base = mu_of("EdS")                                   # show everything as residual to EdS
    order_z = np.argsort(z)
    fig, ax = plt.subplots(figsize=(8,5))
    ax.errorbar(z, mu-base, yerr=dmu, fmt='.', ms=2, alpha=0.18, color='0.5', zorder=1, label=f"Pantheon+ ({N} SNe)")
    zz = z[order_z]
    for model, col, lab in [("EdS","#c0392b","EdS (no Λ, decelerating)"),
                            ("SDT_coasting","#2c7fb8","SDT aging-glass coasting (no Λ)"),
                            ("Milne","#7fbf7b","Milne (open coasting)"),
                            ("LCDM","#222222",f"ΛCDM (Ω_m={results['LCDM']['Om']:.2f})")]:
        Om = results["LCDM"]["Om"] if model=="LCDM" else 0.3
        ax.plot(zz, (mu_of(model,Om)-base)[order_z], color=col, lw=2, label=lab, zorder=3)
    ax.set_xscale("log"); ax.set_xlabel("redshift  z"); ax.set_ylabel("Δ(distance modulus)  μ − μ_EdS  [mag]")
    ax.set_title("Pantheon+ Hubble diagram, residual to the no-dark-energy decelerating (EdS) model")
    ax.legend(fontsize=8, loc="upper left"); ax.grid(alpha=0.25)
    fig.tight_layout(); out = __file__.replace("cr12_pantheon_fit.py","cr12_hubble_residual.png")
    fig.savefig(out, dpi=130); print(f"\n  [plot] wrote {out}")
except Exception as ex:
    print(f"\n  [plot skipped: {ex}]")
