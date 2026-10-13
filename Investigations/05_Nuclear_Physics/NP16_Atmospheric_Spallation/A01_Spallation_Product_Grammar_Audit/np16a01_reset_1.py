import re, random, sys
G={}
for s in open('Datasets/nuclear/NUBASE2020.txt',encoding='utf-8'):
    if not s.strip() or s[0]=='#' or len(s)<31 or s[7]!='0': continue
    A=int(s[0:3]); Z=int(s[4:7]); hl=s[69:78].strip(); modes=s[119:].strip() if len(s)>119 else ''
    G[(Z,A)]={'stable': hl=='stbl' or 'IS=' in modes, 'modes':modes}
def dominant(m):
    best=None;bv=-1
    for tok in m.split(';'):
        mm=re.match(r'\s*(B\+|EC|B-|A|p|n)\s*([=~<>])\s*([0-9.]+)',tok)
        if mm:
            v=float(mm.group(3))
            if v>bv: bv=v; best=mm.group(1)
    return best
def step(Z,A,mode):
    return {'B+':(Z-1,A),'EC':(Z-1,A),'B-':(Z+1,A),'A':(Z-2,A-4),'p':(Z-1,A-1),'n':(Z,A-1)}[mode]
def gram(Z,A): nt=A-2*Z; nd=3*Z-A-2; return nt,nd,(nt>=0 and nd>=0)
def gram_ec(Z,A): nt=A-2*Z+1; nd=3*Z-A-3; return (nt>=0 and nd>=0)
def chain(Z,A):
    path=[(Z,A,None)]
    for _ in range(40):
        g=G.get((Z,A))
        if g is None: return path,'missing'
        if g['stable']: return path,'stable'
        m=dominant(g['modes'])
        if m is None: return path,'untracked'
        Z,A=step(Z,A,m); path[-1]=(path[-1][0],path[-1][1],m); path.append((Z,A,None))
    return path,'cap'
print("NP16A01 reset instrument 1 (2026-10-10)\n=======================================\n")
# V1
p,end=chain(32,68); ok1 = end=='stable' and (p[-1][0],p[-1][1])==(30,68) and (68-30)==(69-31)
print("[V1] Ga-69(p,2n) -> Ge-68 chain:", " -> ".join("%d-%d%s"%(z,a,'('+m+')' if m else '') for z,a,m in p), "| endpoint", end, "| N_target 38 vs N_end", 68-p[-1][0], "->", "met" if ok1 else "NOT MET")
random.seed(1); ok2=all((lambda Z,A:(A==4+2*gram(Z,A)[1]+3*gram(Z,A)[0]) and (Z==2+gram(Z,A)[1]+gram(Z,A)[0]))(random.randint(3,100),random.randint(3,260)) for _ in range(1000))
print("[V2] conservation identities on 1000 random (Z,A) ->", "met" if ok2 else "NOT MET")
if not(ok1 and ok2): print("VALIDATIONS NOT MET"); sys.exit(1)
print("VALIDATIONS: met\n")
targets=[(Z,A) for (Z,A),g in G.items() if 3<=Z<=92 and g['stable']]
prods=set(); pairs=[]
for Z,A in targets:
    for x in range(1,11):
        P=(Z+1,A+1-x)
        if P in G: prods.add(P); pairs.append((Z,A,x,P))
print("stable targets Z=3-92: %d ; (p,xn) product listings existing in NUBASE: %d pairs, %d unique products\n"%(len(targets),len(pairs),len(prods)))
steps_all=0; steps_bad=0; prod_bad=0; bad_ex=[]; ends={}; ecalt_ok=0; ecsteps=0; traj_bad=0
for P in sorted(prods):
    path,end=chain(*P); ends[end]=ends.get(end,0)+1
    pbad=False
    for i,(z,a,m) in enumerate(path):
        steps_all+=1; nt,nd,v=gram(z,a)
        if not v:
            steps_bad+=1; pbad=True
            if len(bad_ex)<12: bad_ex.append("%d-%d(N=%d,n_tri=%d,n_deu=%d)"%(z,a,a-z,nt,nd))
        if m in ('B+','EC'):
            ecsteps+=1; ecalt_ok+=gram_ec(z,a)
        if m in ('B+','EC','B-') and i+1<len(path):
            z2,a2,_=path[i+1]; d_t=gram(z2,a2)[0]-nt; d_d=gram(z2,a2)[1]-nd
            exp=(2,-3) if m in ('B+','EC') else (-2,3)
            if (d_t,d_d)!=exp: traj_bad+=1
    prod_bad+=pbad
print("C1 grammar validity at every step: steps %d, invalid %d (%.1f%%) ; products with any invalid step: %d of %d (%.1f%%) -> %s"%(steps_all,steps_bad,100*steps_bad/steps_all,prod_bad,len(prods),100*prod_bad/len(prods),"MET (100%%)" if steps_bad==0 else "NOT MET"))
print("   examples:", " ".join(bad_ex))
print("   EC/B+ steps valid under the EC alternate grammar: %d of %d (%.1f%%)"%(ecalt_ok,ecsteps,100*ecalt_ok/max(1,ecsteps)))
print("C3 trajectory rules (EC: +2/-3 ; B-: -2/+3): violations %d -> %s"%(traj_bad,"met (arithmetic)" if traj_bad==0 else "NOT MET"))
nb_ok=0; nb_n=0; dN={}
for Z,A,x,P in pairs:
    path,end=chain(*P)
    if end!='stable': continue
    nb_n+=1; ze,ae,_=path[-1]; d=(ae-ze)-(A-Z); dN[d]=dN.get(d,0)+1; nb_ok+=(d==0)
print("C2 neutron budget N_end = N_target over %d pairs with a stable endpoint: %d (%.1f%%) ; distribution of N_end - N_target:"%(nb_n,nb_ok,100*nb_ok/nb_n), dict(sorted(dN.items())))
print("chain endpoints:", ends)
