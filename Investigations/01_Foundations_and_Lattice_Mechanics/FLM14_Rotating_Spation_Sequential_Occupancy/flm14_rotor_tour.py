# FLM14 — P1: the geared stepping rule + frustration + two-scale isotropy
#          P2: sequential occupancy — does a dwell law EMERGE from self-entrainment?
# J. C. Harvey, Melbourne — executed 2026-07-04. Gates pre-committed in RUN_LOG.md.
# NO cos^2 / psi^2 is inserted anywhere (R-Born). beta is a DECLARED exploratory
# parameter, scanned and reported as a scan.
import numpy as np
rng = np.random.default_rng(14)

print("=== FLM14: rotating spation & sequential occupancy ===\n")

# ---------------------------------------------------------------- P1 · the rule
# THE STEPPING RULE (P1-G1 — five native quantities, stated):
#   1. phi_i        : internal phase of spation i (the rotation DOF)
#   2. omega0       : base rotation rate, one turn per relay tick (c/l_P scale; units: turn/tick)
#   3. g = -1       : contact gearing — bonded neighbours counter-rotate (antisymmetric)
#   4. W            : the hand-off window — a pulse hops i->j when (phi_i - phi_j) mod 1 < W
#   5. beta         : entrainment — a passing pulse advances the local phase by beta (P2 only)
# That is the whole rule. Rotation is not decoration: hopping is GATED by phase.
print("P1-G1  rule stated in 5 native quantities: {phi, omega0, g=-1, W, beta}  [PASS by construction]")

# ---- P1-G2 · frustration: can an FCC-neighbourhood lattice 2-colour its gearing? ----
# Build FCC sites, bond nearest neighbours, then try to satisfy g=-1 on every bond
# (equivalent to graph 2-colouring). FCC has triangles -> expect frustration > 0.
def fcc(nc):
    pts=[]
    for i in range(-nc,nc+1):
        for j in range(-nc,nc+1):
            for k in range(-nc,nc+1):
                if (i+j+k)%2==0: pts.append((i,j,k))
    return np.array(pts,float)
P = fcc(3)
d2 = ((P[:,None,:]-P[None,:,:])**2).sum(-1)
NN = (d2>0)&(d2<2.0+1e-9)          # nn distance^2 = 2 on this integer FCC
# greedy 2-colouring attempt
col = np.full(len(P), -1); col[0]=0
order = np.argsort(((P-P[0])**2).sum(-1))
for idx in order:
    nb = np.where(NN[idx] & (col>=0))[0]
    if len(nb)==0 and col[idx]<0: col[idx]=0; continue
    want = 1-col[nb]
    col[idx] = np.bincount(want.astype(int),minlength=2).argmax()
bad = 0; tot = 0
for i in range(len(P)):
    for j in np.where(NN[i])[0]:
        if j>i: tot+=1; bad += (col[i]==col[j])
frus = bad/tot
print(f"P1-G2  gearing frustration on FCC neighbourhoods: {frus:.3f} of bonds unsatisfiable "
      f"({'PASS — rotation must be defect-carried (OP-2)' if frus>0.05 else 'FLAG — lattice 2-colours'})")

# ---- P1-G3 · two-scale isotropy: front propagation, geared vs ungeared ----
# Amorphous variant: jitter FCC sites (FLM10 lesson), rebuild neighbours by radius.
Q = P + rng.normal(0,0.13,P.shape)
d2j = ((Q[:,None,:]-Q[None,:,:])**2).sum(-1)
NNj = (d2j>0)&(d2j<2.6)
phases = rng.random(len(Q))                    # random initial rotor phases
W = 0.5                                        # hand-off window duty
def front_speed(geared, ndir=14, T=26):
    # release a front at the site nearest origin; hop each tick where window open
    src = int(np.argmin((Q**2).sum(-1)))
    arr = np.full(len(Q), np.inf); arr[src]=0.0
    act = {src}
    for t in range(1,T):
        new=set()
        for i in act:
            for j in np.where(NNj[i])[0]:
                if arr[j]!=np.inf: continue
                if geared:
                    # window: relative rotor phase at tick t (counter-rotation doubles rate)
                    rel = (phases[i]+phases[j] + 2*0.37*t) % 1.0
                    if rel < W: arr[j]=t; new.add(j)
                else:
                    arr[j]=t; new.add(j)
        act = new
        if not act: break
    # direction-resolved speed: for sites with finite arrival, v = |r|/t binned by direction
    dirs = rng.normal(size=(ndir,3)); dirs/= np.linalg.norm(dirs,axis=1)[:,None]
    vs=[]
    for u in dirs:
        proj = Q@u
        m = (arr>2)&(arr<np.inf)&(proj>0.5*np.abs(Q@u).max())
        if m.sum()<4: continue
        vs.append((np.linalg.norm(Q[m],axis=1)/arr[m]).mean())
    vs=np.array(vs); return vs.std()/vs.mean()
a_off = front_speed(False); a_on = front_speed(True)
ratio = a_on/max(a_off,1e-9)
print(f"P1-G3  front-speed anisotropy: ungeared {a_off:.4f} · geared {a_on:.4f} · ratio {ratio:.2f} "
      f"[{'PASS' if ratio<=1.2 else 'FAIL'} — gate ≤1.2]")
print("       (global slow rotation axis: PERMITTED per amended F1 — not tested here; local scale only)\n")

# ---------------------------------------------------------------- P2 · the tour
# Minimal closed tour: M seats on a ring. The electron is a defect that HOPS to the next
# seat when that seat's window opens. Passing, it kicks the local phase by beta (entrainment,
# FLM07). The kicks it left behind persist (decay lambda per revolution) — the tour runs
# through its OWN wake. Dwell time at seat k = ticks waited for the window.
# The wake amplitude at seat k is the standing phase perturbation |dphi_k|.
# QUESTION (P2-G1): with what exponent p does dwell track amplitude — dwell ∝ |dphi|^p?
# NOTHING quadratic is inserted; report what emerges, over a beta scan.
def tour(M=180, revs=400, beta=0.05, lam=0.985, W=0.5, seed=7):
    r = np.random.default_rng(seed)
    dphi = np.zeros(M)                 # standing phase perturbation (the wake)
    base = r.random(M)                 # frozen rotor offsets (lattice texture)
    pos, t = 0, 0.0
    dwell = np.zeros(M); visits = np.zeros(M)
    for rev in range(revs):
        for step in range(M):
            k = (pos+1) % M
            # ticks until k's window opens: window phase = (base_k + omega*t + dphi_k) mod 1
            om = 0.37
            ph = (base[k] + om*t + dphi[k]) % 1.0
            wait = ((1.0-ph) % 1.0)/om if ph>=W else 0.0
            t += wait + 1.0                       # wait + the hop tick
            if rev>revs//2: dwell[k]+=wait+1.0; visits[k]+=1
            dphi[k] += beta                        # entrainment kick as it passes
            dphi *= lam**(1.0/M)                   # slow decay
            pos = k
    m = visits>0
    dw = dwell[m]/visits[m]
    amp = np.abs(dphi[m])
    # emergent exponent: fit log(dwell) vs log(amp) where amp spans a decade
    ok = amp>amp.max()*0.05
    if ok.sum()<12 or amp[ok].max()/max(amp[ok].min(),1e-12)<3: return None
    pfit = np.polyfit(np.log(amp[ok]), np.log(dw[ok]), 1)[0]
    drift = abs(dw.mean()-dw[:len(dw)//2].mean())/dw.mean()
    return pfit, drift, dw, amp

print("P2     the tour — emergent dwell-vs-wake exponent p, beta scan (NOTHING inserted):")
print("       beta    p(emergent)   closure-drift")
stable=[]
for beta in [0.01,0.02,0.05,0.10,0.20,0.40]:
    out = tour(beta=beta)
    if out is None:
        print(f"       {beta:.2f}    (amplitude range too narrow — no exponent defined)")
        continue
    p,drift,_,_ = out
    flag = "PASS" if drift<0.01 else "FAIL"
    print(f"       {beta:.2f}    {p:+.3f}        {drift:.4f} [{flag} P2-G2]")
    if drift<0.01: stable.append((beta,p))
if stable:
    ps=[p for _,p in stable]
    print(f"\nP2-G1  emergent exponent across stable regime: p = {np.mean(ps):+.3f} ± {np.std(ps):.3f}")
    print("       committed hope was p→2; the HONEST result is the number above, as measured.")
else:
    print("\nP2-G1  no stable regime — reported as such.")
print("\nP3–P5: gated on P2 per RUN_LOG — see verdict.")
