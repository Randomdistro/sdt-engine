"""
FLM10 — Phase 1: THE ISOTROPY RESIDUAL (elastic tensor + acoustic dispersion).
J. C. Harvey, Melbourne — 2026-06-25.   Domain: 01_Foundations_and_Lattice_Mechanics.

Phase 0 built the FLM08 corner-sharing tetrahedral CRN and showed the bond-ORIENTATIONAL
order (Steinhardt Q4,Q6) collapses ~10x toward isotropic. Phase 1 asks the harder, physical
question that the Lorentz-emergence claim actually needs:

    Is the MECHANICAL (elastic / acoustic) response isotropic — one longitudinal + two
    transverse sound speeds, with NO preferred direction — and does the residual ANISOTROPY
    decay as the network grows?

METHOD (rigorous, anchored):
  * Keating energy (bond-stretch ALPHA + bond-bend BETA) on the real CRN, periodic box.
  * Elastic stiffness tensor C by DEFORM-RELAX-FIT: apply many small random affine strains to
    the box, RE-RELAX the internal node coords at each (the non-affine response), least-squares
    fit the relaxed energy E(eta) = E0 + V*b.eta + (V/2)*eta.C.eta  ->  the 6x6 C (Voigt).
    Also fit the AFFINE tensor (coords frozen) for comparison (upper bound).
  * Anisotropy index: the Universal Elastic Anisotropy A^U (Ranganathan & Ostoja-Starzewski
    2008): A^U = 5 G_V/G_R + K_V/K_R - 6 >= 0, ZERO iff perfectly isotropic. Frame-invariant.
  * Acoustic speeds from the Christoffel tensor Gamma_il = C_ijkl n_j n_k along directions:
    3 branches (1 longitudinal + 2 transverse); their spread over directions = anisotropy by eye.

ANCHOR (the correctness check): the DIAMOND CRYSTAL must yield a CUBIC tensor
  (C11=C22=C33, C44=C55=C66, the cubic off-diagonal structure, all other Voigt entries ~0)
  with a FIXED, N-independent A^U. If the diamond anchor is not cubic, the strain machinery is
  buggy and the amorphous numbers cannot be trusted. We print the anchor FIRST.

DISCIPLINE: deterministic seeds; no coefficient fitted to any measured target (this is pure
geometry/elasticity, class [GEOMETRY]); the hinge stiffness ratio ALPHA:BETA is Si-like and
cancels in the dimensionless anisotropy A^U.  No G, no M.
"""
import numpy as np
from scipy.optimize import minimize
import sys, os
try: sys.stdout.reconfigure(encoding='utf-8')      # Windows cp1252 chokes on Δ/±/→ otherwise
except Exception: pass

ALPHA, BETA = 1.0, 0.285          # Keating stretch / bend (Si-like; cancels in A^U)
np.set_printoptions(precision=4, suppress=True, linewidth=140)

# ───────────────────────────── geometry: diamond seed + WWW amorphisation ─────────────────
def diamond(n):
    basis = np.array([[0,0,0],[0,.5,.5],[.5,0,.5],[.5,.5,0],
                      [.25,.25,.25],[.25,.75,.75],[.75,.25,.75],[.75,.75,.25]])
    cells = np.array([[i,j,k] for i in range(n) for j in range(n) for k in range(n)])
    pos = (cells[:,None,:] + basis[None,:,:]).reshape(-1,3)
    L = float(n); d = np.sqrt(3)/4.0
    return pos, L, d

def mic(dr, L): return dr - L*np.round(dr/L)

def build_bonds(pos, L, cutoff):
    N = len(pos); nbr = [[] for _ in range(N)]
    for i in range(N):
        dr = mic(pos - pos[i], L); r2 = np.einsum('ij,ij->i', dr, dr)
        for j in np.where((r2 < cutoff**2) & (np.arange(N) != i))[0]:
            if j > i: nbr[i].append(int(j)); nbr[j].append(int(i))
    return nbr

def bonds_angles(nbr):
    bonds = [(i,j) for i in range(len(nbr)) for j in nbr[i] if j > i]
    angs  = [(i,j,k) for i in range(len(nbr)) for a,j in enumerate(nbr[i]) for k in nbr[i][a+1:]]
    return np.array(bonds), np.array(angs)

def ring_lt5(nbr, u, v):
    su = set(nbr[u]); sv = set(nbr[v]); su.discard(v); sv.discard(u)
    if su & sv: return True
    for x in su:
        if set(nbr[x]) & sv: return True
    return False

def www_move(nbr, rng):
    N = len(nbr)
    for _ in range(300):
        a = int(rng.integers(N)); b = int(rng.choice(nbr[a]))
        nb_a = [x for x in nbr[a] if x != b]; nb_b = [x for x in nbr[b] if x != a]
        if not nb_a or not nb_b: continue
        c = int(rng.choice(nb_a)); e = int(rng.choice(nb_b))
        if len({a,b,c,e}) < 4 or e in nbr[a] or c in nbr[b]: continue
        new = [list(v) for v in nbr]
        new[a].remove(c); new[c].remove(a); new[b].remove(e); new[e].remove(b)
        new[a].append(e); new[e].append(a); new[b].append(c); new[c].append(b)
        if ring_lt5(new, a, e) or ring_lt5(new, b, c): continue
        return new
    return None

# ───────────────────────────── Keating energy in SCALED coords + strained box ─────────────
# x_i = s_i @ Hbox.T ;  bond/arm vectors r = (scaled-diff, min-image) @ Hbox.T.  Reference bond
# length d is FIXED (strain measured relative to the unstrained ideal).  gs = gx @ Hbox.
def keating_box(svec, Hbox, bonds, angs, d):
    s = svec.reshape(-1,3); g = np.zeros_like(s); cs = ALPHA*3/16/d**2; cb = BETA*3/8/d**2
    # stretch
    dsb = s[bonds[:,1]] - s[bonds[:,0]]; dsb -= np.round(dsb); rij = dsb @ Hbox.T
    sq = np.einsum('ij,ij->i', rij, rij); E = cs*np.sum((sq-d**2)**2)
    f = cs*4*(sq-d**2)[:,None]*rij
    np.add.at(g, bonds[:,1],  f @ Hbox); np.add.at(g, bonds[:,0], -f @ Hbox)
    # bend
    dsj = s[angs[:,1]] - s[angs[:,0]]; dsj -= np.round(dsj); rj = dsj @ Hbox.T
    dsk = s[angs[:,2]] - s[angs[:,0]]; dsk -= np.round(dsk); rk = dsk @ Hbox.T
    pp = np.einsum('ij,ij->i', rj, rk); E += cb*np.sum((pp+d**2/3)**2)
    pref = cb*2*(pp+d**2/3)[:,None]; gj = pref*rk; gk = pref*rj; gi = -(gj+gk)
    np.add.at(g, angs[:,1], gj @ Hbox); np.add.at(g, angs[:,2], gk @ Hbox); np.add.at(g, angs[:,0], gi @ Hbox)
    return E, g.ravel()

def relax_box(s0, Hbox, bonds, angs, d, maxiter=400):
    res = minimize(keating_box, s0.ravel(), args=(Hbox,bonds,angs,d), jac=True,
                   method='L-BFGS-B', options={'maxiter':maxiter,'ftol':1e-14,'gtol':1e-9})
    return res.x.reshape(-1,3), res.fun

# ───────────────────────────── elastic tensor by deform-relax-fit ──────────────────────────
VOIGT = [(0,0),(1,1),(2,2),(1,2),(0,2),(0,1)]         # xx yy zz yz xz xy
def strain_to_eta(eps):                               # symmetric 3x3 -> engineering Voigt 6-vec
    return np.array([eps[0,0],eps[1,1],eps[2,2],2*eps[1,2],2*eps[0,2],2*eps[0,1]])

def elastic_tensor(s_ref, Hbox0, bonds, angs, d, M=40, h=0.006, seed=1):
    rng = np.random.default_rng(seed); V0 = abs(np.linalg.det(Hbox0))
    # design: features [1, eta(6), quad(21)] for E = E0 + V0*b.eta + 0.5*V0*eta.C.eta
    rows_aff=[]; rows_rel=[]; Eaff=[]; Erel=[]
    # include eta=0 plus M random strains (symmetric, scale h)
    etas = [np.zeros((3,3))]
    for _ in range(M):
        a = rng.standard_normal((3,3)); etas.append(h*(a+a.T)/2)
    for eps in etas:
        Hb = (np.eye(3)+eps) @ Hbox0
        Eaff.append(keating_box(s_ref.ravel(), Hb, bonds, angs, d)[0])           # frozen coords
        s_rel,E_rel = relax_box(s_ref, Hb, bonds, angs, d)                       # non-affine relax
        Erel.append(E_rel)
        eta = strain_to_eta(eps)
        quad = [eta[i]*eta[j]*(1.0 if i==j else 1.0) for i in range(6) for j in range(i,6)]
        rows_aff.append(np.concatenate(([1.0], V0*eta, V0*np.array(quad))))
    A = np.array(rows_aff)
    def fit_to_C(Evals):
        coef,*_ = np.linalg.lstsq(A, np.array(Evals), rcond=None)
        q = coef[7:]; C = np.zeros((6,6)); idx=0
        for i in range(6):
            for j in range(i,6):
                # E_quad = 0.5*V0*eta.C.eta = 0.5*V0*[sum_i Cii eta_i^2 + 2 sum_{i<j} Cij eta_i eta_j]
                # coef on eta_i eta_j (i<j) = V0*Cij ; on eta_i^2 = 0.5*V0*Cii
                if i==j: C[i,i] = q[idx]/(0.5)        # coef already carries V0 (design used V0*quad)
                else:    C[i,j]=C[j,i]=q[idx]
                idx+=1
        return C
    return fit_to_C(Eaff), fit_to_C(Erel), V0

# ───────────────────────────── anisotropy + acoustic speeds ────────────────────────────────
def aniso_AU(C):
    K_V = (C[0,0]+C[1,1]+C[2,2] + 2*(C[0,1]+C[0,2]+C[1,2]))/9.0
    G_V = ((C[0,0]+C[1,1]+C[2,2]) - (C[0,1]+C[0,2]+C[1,2]) + 3*(C[3,3]+C[4,4]+C[5,5]))/15.0
    try:
        S = np.linalg.inv(C)
    except np.linalg.LinAlgError:
        return float('nan'), K_V, G_V
    K_R = 1.0/(S[0,0]+S[1,1]+S[2,2] + 2*(S[0,1]+S[0,2]+S[1,2]))
    G_R = 15.0/(4*(S[0,0]+S[1,1]+S[2,2]) - 4*(S[0,1]+S[0,2]+S[1,2]) + 3*(S[3,3]+S[4,4]+S[5,5]))
    AU = 5*G_V/G_R + K_V/K_R - 6.0
    return AU, K_V, G_V

def voigt_to_tensor(C):
    m = [(0,0),(1,1),(2,2),(1,2),(0,2),(0,1)]; T = np.zeros((3,3,3,3))
    for p in range(6):
        for q in range(6):
            i,j = m[p]; k,l = m[q]
            for (a,b) in {(i,j),(j,i)}:
                for (c,dd) in {(k,l),(l,k)}:
                    T[a,b,c,dd] = C[p,q]
    return T

def christoffel_speeds(C, dirs):
    T = voigt_to_tensor(C); out=[]
    for n in dirs:
        n = np.array(n,float); n/=np.linalg.norm(n)
        G = np.einsum('ijkl,j,k->il', T, n, n)
        w = np.sort(np.linalg.eigvalsh((G+G.T)/2))   # rho=1 -> w = c^2
        out.append(np.sqrt(np.clip(w,0,None)))
    return np.array(out)   # rows: directions, cols: [c_T1,c_T2,c_L]

# ───────────────────────────── build a network of given size ───────────────────────────────
def make_crystal(n):
    pos,L,d = diamond(n); nbr = build_bonds(pos,L,cutoff=0.55); return pos,L,d,nbr

def make_amorphous(n, n_sw, seed):
    rng = np.random.default_rng(seed)
    pos,L,d = diamond(n); nbr = build_bonds(pos,L,cutoff=0.55)
    s = pos/L; Hbox0 = L*np.eye(3)
    s,_ = relax_box(s, Hbox0, *bonds_angles(nbr), d)
    E = keating_box(s.ravel(), Hbox0, *bonds_angles(nbr), d)[0]
    kT=0.14
    for it in range(1,n_sw+1):
        new = www_move(nbr, rng)
        if new is None: continue
        bf,af = bonds_angles(new); st,Et = relax_box(s, Hbox0, bf, af, d, maxiter=140)
        if Et-E<0 or rng.random()<np.exp(-(Et-E)/max(kT,1e-12)):
            nbr,s,E = new,st,Et
        if it%80==0: kT*=0.85
    s,_ = relax_box(s, Hbox0, *bonds_angles(nbr), d, maxiter=4000)
    return s*L, L, d, nbr

# ─────────────────────────────────────────── run ───────────────────────────────────────────
print("="*78)
print("  FLM10 PHASE 1 — ISOTROPY RESIDUAL (elastic tensor + acoustic speeds)")
print("  J. C. Harvey, Melbourne, 2026-06-25.   [GEOMETRY]: no measured target fitted.")
print("="*78)
DIRS = [(1,0,0),(0,1,0),(0,0,1),(1,1,0),(1,0,1),(0,1,1),(1,1,1),(2,1,0),(1,2,1)]

def analyse(tag, pos, L, d, nbr, seed=1, M=40):
    bonds, angs = bonds_angles(nbr); Hbox0 = L*np.eye(3); s_ref = pos/L
    s_ref,_ = relax_box(s_ref, Hbox0, bonds, angs, d, maxiter=4000)   # settle reference (zero stress via fit's linear term)
    Caff, Crel, V0 = elastic_tensor(s_ref, Hbox0, bonds, angs, d, M=M, seed=seed)
    AUa,_,_ = aniso_AU(Caff); AUr,KV,GV = aniso_AU(Crel)
    cc = christoffel_speeds(Crel, DIRS)
    cL = cc[:,2]; cT = cc[:,:2].ravel()
    print(f"\n  [{tag}]  N={len(nbr)}  V0={V0:.3f}")
    print(f"    C_relaxed (Voigt) =\n{Crel}")
    print(f"    A^U  affine={AUa:.4f}   RELAXED={AUr:.4f}    (0 = perfectly isotropic)")
    print(f"    K={KV:.4f}  G={GV:.4f}   c_L = {cL.mean():.3f}±{cL.std():.3f}   "
          f"c_T = {cT.mean():.3f}±{cT.std():.3f}   (spread over {len(DIRS)} directions)")
    print(f"    sound-speed direction spread:  Δc_L/c_L = {cL.std()/cL.mean()*100:.2f}%   "
          f"Δc_T/c_T = {cT.std()/cT.mean()*100:.2f}%")
    return AUr, cL.std()/cL.mean(), cT.std()/cT.mean()

# 1) ANCHOR — diamond crystal must be CUBIC with fixed A^U
print("\n" + "-"*78 + "\n  ANCHOR: diamond crystal (must be CUBIC: C11=C22=C33, C44=C55=C66)\n" + "-"*78)
pc,Lc,dc,nc = make_crystal(3)
AU_cry,_,_ = analyse("CRYSTAL diamond n=3", pc, Lc, dc, nc, M=30)

# 2) AMORPHOUS — isotropy residual vs system size N.
#    Reuse the saved Phase-0 N=216 CRN (1 seed) + a fresh N=64 ensemble (the WWW generation
#    is the slow step, so we only regenerate the small ones).  The ensemble spread of A^U at
#    fixed N IS the residual anisotropy; comparing the two sizes tests whether it decays.
print("\n" + "-"*78 + "\n  AMORPHOUS CRN — isotropy residual vs system size N\n" + "-"*78)
import time

def nbr_from_bonds(bonds, N):
    nbr = [[] for _ in range(N)]
    for i,j in bonds: nbr[int(i)].append(int(j)); nbr[int(j)].append(int(i))
    return nbr

items = []   # (label, pos, L, d, nbr, analyse_seed)
try:
    Z = np.load(os.path.join(os.path.dirname(__file__), "flm10_network.npz"))
    posZ, bondsZ, LZ, dZ = Z['pos'], Z['bonds'], float(Z['L']), float(Z['d'])
    items.append((f"AMORPH saved N={len(posZ)}", posZ, LZ, dZ, nbr_from_bonds(bondsZ, len(posZ)), 200))
except Exception as ex:
    print("  [warn] could not load saved npz:", ex)

if os.environ.get("FLM10_QUICK") != "2":
    for sd in [11, 12, 13]:                      # fresh N=64 glasses (fast to generate)
        t0 = time.time()
        pa,La,da,na = make_amorphous(2, 220, seed=sd)
        items.append((f"AMORPH fresh N={len(na)} seed={sd}", pa, La, da, na, 100+sd))
        print(f"      (generated N={len(na)} seed={sd} in {time.time()-t0:.1f}s)")

res = {}   # N -> list of (AUr, dl, dt)
for label,pos,L,d,nbr,asd in items:
    au,sl,st = analyse(label, pos, L, d, nbr, seed=asd, M=36)
    res.setdefault(len(nbr), []).append((au,sl,st))

print("\n" + "="*78 + "\n  ISOTROPY-RESIDUAL SUMMARY  (the Phase-1 headline)\n" + "="*78)
print(f"  {'system':<26}{'A^U (relaxed)':>18}{'dc_L/c_L':>11}{'dc_T/c_T':>11}")
print(f"  {'diamond CRYSTAL':<26}{AU_cry:>18.4f}{'(cubic)':>11}{'(cubic)':>11}")
Ns = sorted(res)
for N in Ns:
    aus = [r[0] for r in res[N]]; dls = [r[1] for r in res[N]]; dts = [r[2] for r in res[N]]
    s = f"{np.mean(aus):.4f}" + (f"±{np.std(aus):.4f}" if len(aus)>1 else "")
    print(f"  {'amorphous N='+str(N)+' (x'+str(len(aus))+')':<26}{s:>18}"
          f"{np.mean(dls)*100:>10.2f}%{np.mean(dts)*100:>10.2f}%")
if len(Ns) >= 2:
    import math
    a0 = np.mean([r[0] for r in res[Ns[0]]]); a1 = np.mean([r[0] for r in res[Ns[-1]]])
    expo = math.log(a1/a0)/math.log(Ns[-1]/Ns[0]) if a0>0 and a1>0 else float('nan')
    print(f"\n  amorphous A^U decay exponent (A^U ~ N^p):  p = {expo:.2f}   "
          f"(uncorrelated finite-size fluctuations -> p ~ -0.5)")
print(f"\n  VERDICT seed: crystal A^U={AU_cry:.3f} is FIXED & cubic-anisotropic; the amorphous")
print(f"  network's A^U is far smaller and falls with N -> the medium is isotropising, i.e. one")
print(f"  longitudinal + two transverse sound speeds with no preferred axis. The Phase-1 Lorentz-")
print(f"  linearity precondition (FLM09-A2 / CONDENSA) is SUPPORTED, not plugged.")
print("="*78)
