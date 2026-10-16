"""GOM44 tool: registered endpoint formula on Earth flybys with equal-depth controls.

Run:  python -I gom44_flyby_depth_control.py <dir with horizons tables> <out_dir>
Rules are those of PROMPT.md (registered 2026-10-16 before this tool ran). Nothing is tuned.
Tables: <name>_geo.txt / <name>_helio.txt (JPL Horizons VECTORS, CSV, ICRF, km and km/s, 10-min step).
"""
import sys, os, math, csv, random, itertools

sys.stdout.reconfigure(encoding='utf-8')
HZ, OUT = sys.argv[1], sys.argv[2]
os.makedirs(OUT, exist_ok=True)

MU = 398600.4418                       # km^3/s^2, Earth GM as used by Anderson et al. 2008
K_SDT = 2.9992003355950517e-6          # GOM43 RUN_LOG.md:195
AU_KM = 1.495978707e8                  # measured::AU
R_REFS = [50_000.0, 20_000.0, 100_000.0]   # first is primary; others sensitivity only
PRIMARY = R_REFS[0]

# (name, label, date, dVinf_mm_s or None, sigma_mm_s or None, sigma_published, note)
FLYBYS = [
 ("galileo1","Galileo I","1990-12-08", 3.92,0.08,True,"Anderson 2008"),
 ("galileo2","Galileo II","1992-12-08",-4.60,1.00,True,"Anderson 2008 (drag-subtracted)"),
 ("near","NEAR","1998-01-23",13.46,0.13,True,"Anderson 2008"),
 ("cassini","Cassini","1999-08-18",-2.00,1.00,True,"Anderson 2008"),
 ("rosetta1","Rosetta I","2005-03-04",1.80,0.03,True,"Anderson 2008"),
 ("messenger","MESSENGER","2005-08-02",0.02,0.01,True,"Anderson 2008"),
 ("rosetta2","Rosetta II","2007-11-13",0.0,0.5,False,"census; tolerance 0.5"),
 ("rosetta3","Rosetta III","2009-11-13",0.004,0.044,True,"ASTG II text"),
 ("juno","Juno","2013-10-09",0.0,0.8,True,"census/AAS 14-435"),
 ("epoxi1","EPOXI I","2007-12-31",0.0,0.5,False,"census; distant; tolerance 0.5"),
 ("epoxi2","EPOXI II","2008-12-29",0.0,0.5,False,"census; distant; tolerance 0.5"),
 ("epoxi3","EPOXI III","2009-06-28",0.0,0.5,False,"census; distant; tolerance 0.5"),
 ("bepicolombo","BepiColombo","2020-04-10",0.0,0.5,False,"census; tolerance 0.5"),
 ("solarorbiter","Solar Orbiter","2021-11-27",0.0,0.5,False,"census; tolerance 0.5"),
 ("juice","JUICE (LEGA)","2024-08-20",0.6,None,False,"census; sigma unpublished"),
 ("stardust","Stardust","2001-01-15",None,None,False,"no published value"),
 ("hayabusa2","Hayabusa2","2015-12-03",None,None,False,"no published value"),
 ("osirisrex","OSIRIS-REx","2017-09-22",None,None,False,"no published value"),
 ("lucy1","Lucy I","2022-10-16",None,None,False,"no published value"),
 ("lucy2","Lucy II","2024-12-13",None,None,False,"no published value"),
]

def dot(a,b): return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]
def nrm(a): return math.sqrt(dot(a,a))
def sub(a,b): return [a[0]-b[0],a[1]-b[1],a[2]-b[2]]
def cross(a,b): return [a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]]
def un(a): n=nrm(a); return [x/n for x in a]

def load(path):
    t=open(path,encoding='utf-8').read()
    s=t.split("$$SOE")[1].split("$$EOE")[0].strip().split("\n")
    jd=[];st=[]
    for l in s:
        c=[x.strip() for x in l.split(",")]
        jd.append(float(c[0])); st.append([float(x) for x in c[2:8]])
    return jd,st

def hermite(t,t0,t1,x0,v0,x1,v1):
    h=t1-t0; u=(t-t0)/h
    h00=2*u**3-3*u**2+1; h10=u**3-2*u**2+u; h01=-2*u**3+3*u**2; h11=u**3-u**2
    return [h00*x0[i]+h10*h*v0[i]+h01*x1[i]+h11*h*v1[i] for i in range(3)]

def bracket_cross(jd,geo,R,ic,direction):
    """sample pair bracketing |r_geo| = R, scanning away from closest-approach index ic (direction -1 inbound, +1 outbound)."""
    i=ic
    while 0<=i+direction<len(geo):
        a=nrm(geo[i][:3]); b=nrm(geo[i+direction][:3])
        if (a-R)*(b-R)<=0: return (i,i+direction)
        i+=direction
    return None

def endpoint(jd,geo,hel,R,pair):
    ia,ib=sorted(pair)
    t0,t1=jd[ia]*86400.0,jd[ib]*86400.0
    f=lambda t: hermite(t,t0,t1,geo[ia][:3],geo[ia][3:],geo[ib][:3],geo[ib][3:])
    lo,hi=t0,t1
    flo=nrm(f(lo))-R
    for _ in range(100):
        mid=0.5*(lo+hi); fm=nrm(f(mid))-R
        if (fm>0)==(flo>0): lo,flo=mid,fm
        else: hi=mid
    t=0.5*(lo+hi)
    rg=f(t); rh=hermite(t,t0,t1,hel[ia][:3],hel[ia][3:],hel[ib][:3],hel[ib][3:])
    return t,rg,rh

def endpoint_terms(rg,rh,use_earth_R=False):
    earth=sub(rh,rg)                    # Earth heliocentric position (Sun at origin)
    tau=un(earth)                       # Sun -> Earth (anti-solar axis)
    rho=un(rg)
    cpsi=dot(rho,tau)
    Rsun=nrm(earth) if use_earth_R else nrm(rh)
    return cpsi,Rsun,nrm(earth)

def bracket(in_terms,out_terms):
    return (AU_KM/in_terms[1])**2*in_terms[0]-(AU_KM/out_terms[1])**2*out_terms[0]

def asym_vinf(st):
    r=st[:3]; v=st[3:]; R=nrm(r); V=nrm(v)
    return math.sqrt(V*V-2*MU/R)

# ---------------- G1 instrument validation ----------------
print("GOM44 run log (tool output)\n")
g1={}
# (a) symmetric about Sun-Earth axis
D=AU_KM; R=50000.0; a=0.7
earth=[D,0.0,0.0]
rho_in=[R*math.cos(a),R*math.sin(a),0.0]; rho_out=[R*math.cos(a),-R*math.sin(a),0.0]
rh_in=[earth[i]+rho_in[i] for i in range(3)]; rh_out=[earth[i]+rho_out[i] for i in range(3)]
Bs=bracket(endpoint_terms(rho_in,rh_in),endpoint_terms(rho_out,rh_out))
g1['a']=abs(Bs)<1e-12
print(f"G1a symmetric synthetic: B = {Bs:.3e}  -> {'met' if g1['a'] else 'NOT MET'}")
# (b) closed form: rho_in = +R t, rho_out = -R t
rho_in=[R,0.0,0.0]; rho_out=[-R,0.0,0.0]
rh_in=[earth[i]+rho_in[i] for i in range(3)]; rh_out=[earth[i]+rho_out[i] for i in range(3)]
Bt=bracket(endpoint_terms(rho_in,rh_in),endpoint_terms(rho_out,rh_out))
Bc=(D/(D+R))**2+(D/(D-R))**2
g1['b']=abs(Bt-Bc)<1e-9
print(f"G1b closed form: tool {Bt:.12f}  closed {Bc:.12f}  diff {Bt-Bc:.2e} -> {'met' if g1['b'] else 'NOT MET'}")

rows=[]
tables={}
for name,label,date,dv,sg,sgpub,note in FLYBYS:
    jd,geo=load(os.path.join(HZ,f"{name}_geo.txt"))
    jd2,hel=load(os.path.join(HZ,f"{name}_helio.txt"))
    assert len(jd)==len(jd2) and all(abs(x-y)<1e-9 for x,y in zip(jd,jd2)), name
    tables[name]=(jd,geo,hel)

def run(Rref,use_earth_R=False,verbose=False):
    res={}
    for name,label,date,dv,sg,sgpub,note in FLYBYS:
        jd,geo,hel=tables[name]
        rr=[nrm(s[:3]) for s in geo]; ic=min(range(len(rr)),key=lambda j:rr[j])
        rec={'name':name,'label':label,'date':date,'dv':dv,'sg':sg,'sgpub':sgpub,'rmin':rr[ic]}
        if rr[ic]>=Rref or ic<75 or ic>len(jd)-76:
            rec['na']=True; res[name]=rec; continue
        pin=bracket_cross(jd,geo,Rref,ic,-1)
        pout=bracket_cross(jd,geo,Rref,ic,+1)
        if pin is None or pout is None:
            rec['na']=True; res[name]=rec; continue
        tin,rgin,rhin=endpoint(jd,geo,hel,Rref,pin)
        tout,rgout,rhout=endpoint(jd,geo,hel,Rref,pout)
        ti=endpoint_terms(rgin,rhin,use_earth_R); to=endpoint_terms(rgout,rhout,use_earth_R)
        B=bracket(ti,to)
        vinf=asym_vinf(geo[ic-72])
        rec.update(dict(na=False,rin=nrm(rgin),rout=nrm(rgout),cin=ti[0],cout=to[0],Rin=ti[1],Rout=to[1],
                        earth_au_in=ti[2]/AU_KM,earth_au_out=to[2]/AU_KM,B=B,vinf=vinf,
                        P=vinf*1e3*K_SDT*B*1e3,dt_h=(tout-tin)/3600.0))
        res[name]=rec
    return res

R0=run(PRIMARY)
g1['c']=all(abs(r['rin']-PRIMARY)<1e-3 and abs(r['rout']-PRIMARY)<1e-3 for r in R0.values() if not r['na'])
print(f"G1c endpoint radius = R_ref within 1 m for all computed endpoints: {'met' if g1['c'] else 'NOT MET'}")
g1['d']=all(0.983<=r[k]<=1.017 for r in R0.values() if not r['na'] for k in ('earth_au_in','earth_au_out'))
print(f"G1d Earth heliocentric distance in 0.983-1.017 au at all endpoints: {'met' if g1['d'] else 'NOT MET'}")
# (e) Table I geometry check
PRL={"galileo1":(8.949,-12.52,-34.15),"galileo2":(8.877,-34.26,-4.87),"near":(6.851,-20.76,-71.96),"cassini":(16.010,-12.92,-4.99),"rosetta1":(3.863,-2.81,-34.29),"messenger":(4.056,31.44,-31.92)}
def asym_dec(st):
    r=st[:3]; v=st[3:]; Rr=nrm(r); V=nrm(v)
    h=cross(r,v); ev=[x/MU-y/Rr for x,y in zip(cross(v,h),r)]; e=nrm(ev)
    P=un(ev); Q=cross(un(h),P); nu=math.acos(-1/e)
    so=[math.cos(nu)*p+math.sin(nu)*q for p,q in zip(P,Q)]
    si=[-(math.cos(nu)*p-math.sin(nu)*q) for p,q in zip(P,Q)]
    return math.degrees(math.asin(si[2])),math.degrees(math.asin(so[2]))
ok=True
for k,(v,di,do) in PRL.items():
    jd,geo,hel=tables[k]; rr=[nrm(s[:3]) for s in geo]; ic=min(range(len(rr)),key=lambda j:rr[j])
    vi=asym_vinf(geo[ic-72]); d1,d2=asym_dec(geo[ic-72]); d3,d4=asym_dec(geo[ic+72])
    good=abs(vi-v)<0.003 and abs(d1-di)<0.9 and abs(d4-do)<0.9
    ok&=good
    print(f"G1e {k:10s} Vinf {vi:.4f} (PRL {v})  dec_in {d1:7.2f} (PRL {di})  dec_out {d4:7.2f} (PRL {do})  {'ok' if good else 'OUT'}")
g1['e']=ok
print(f"G1e Table I reproduced (V-inf 0.003 km/s, declinations 0.9 deg): {'met' if ok else 'NOT MET'}")
G1=all(g1.values())
print(f"\nG1 instrument validation: {'MET' if G1 else 'NOT MET'}  {g1}\n")

def classify(r):
    if r['dv'] is None: return 'U'
    if r['sg'] is None: return 'U'
    if not r['sgpub'] and abs(r['dv'])<=0.5: return 'N'
    if abs(r['dv'])>=3*r['sg']: return 'A'
    if abs(r['dv'])<=2*r['sg']: return 'N'
    return 'U'

def spearman(x,y):
    def ranks(a):
        s=sorted(range(len(a)),key=lambda i:a[i]); r=[0.0]*len(a); i=0
        while i<len(a):
            j=i
            while j+1<len(a) and a[s[j+1]]==a[s[i]]: j+=1
            for k in range(i,j+1): r[s[k]]=(i+j)/2+1
            i=j+1
        return r
    rx,ry=ranks(x),ranks(y); n=len(x); mx=sum(rx)/n; my=sum(ry)/n
    num=sum((a-mx)*(b-my) for a,b in zip(rx,ry)); den=math.sqrt(sum((a-mx)**2 for a in rx)*sum((b-my)**2 for b in ry))
    return num/den if den else float('nan')

def evaluate(res,tag):
    comp=[r for r in res.values() if not r['na']]
    for r in comp: r['cls']=classify(r)
    absB=sorted(comp,key=lambda r:abs(r['B']))
    nE=math.ceil(len(comp)/3)
    Eset={r['name'] for r in absB[:nE]}
    out={'tag':tag,'n':len(comp),'nE':nE}
    # G2
    g2=[];g3=[];g4=[]
    for r in comp:
        if r['cls']=='A': g2.append((r['label'],r['P'],r['dv'],r['sg'],abs(r['P']-r['dv'])<=2*r['sg']))
        if r['cls']=='N':
            tol=2*r['sg'] if r['sgpub'] else 0.5     # PROMPT.md section 3: 0.5 mm/s where sigma is unpublished
            g3.append((r['label'],r['P'],r['dv'],tol,abs(r['P'])<=tol))
    for r in comp:
        if r['name'] in Eset:
            tol=(2*r['sg'] if r['sgpub'] else 0.5) if r['sg'] is not None else None
            inA = r['cls']=='A'
            okc = (not inA) and (tol is None or abs(r['P'])<=tol)
            g4.append((r['label'],r['B'],r['P'],r['dv'],r['cls'],okc))
    pub=[r for r in comp if r['dv'] is not None]
    rho=spearman([r['P'] for r in pub],[r['dv'] for r in pub])
    random.seed(20261016)
    xs=[r['P'] for r in pub]; ys=[r['dv'] for r in pub]; cnt=0; T=200000
    for _ in range(T):
        yp=ys[:]; random.shuffle(yp)
        if spearman(xs,yp)>=rho-1e-12: cnt+=1
    out.update(g2=g2,g3=g3,g4=g4,rho=rho,p=cnt/T,npub=len(pub),
               G2=all(x[-1] for x in g2),G3=all(x[-1] for x in g3),G4=all(x[-1] for x in g4),G5=rho>=0.7)
    return comp,Eset,out

def report(res,tag,full=True):
    comp,Eset,o=evaluate(res,tag)
    print(f"==== {tag} : computed {o['n']} of {len(res)} flybys; equal-depth tercile n = {o['nE']} ====")
    if full:
        print(f"{'flyby':14s}{'rmin km':>10s}{'dt h':>7s}{'cos_in':>9s}{'cos_out':>9s}{'Rsun_in au':>11s}{'Rsun_out au':>12s}{'B':>11s}{'vinf':>8s}{'P mm/s':>9s}{'obs':>8s}{'sigma':>7s}{'cls':>4s}{'E':>3s}")
        for r in sorted(comp,key=lambda r:abs(r['B'])):
            print(f"{r['label']:14s}{r['rmin']:10.0f}{r['dt_h']:7.2f}{r['cin']:9.4f}{r['cout']:9.4f}{r['Rin']/AU_KM:11.6f}{r['Rout']/AU_KM:12.6f}{r['B']:11.3e}{r['vinf']:8.3f}{r['P']:9.3f}"
                  f"{('%8.3f'%r['dv']) if r['dv'] is not None else '       -'}{('%7.3f'%r['sg']) if r['sg'] is not None else '      -'}{r['cls']:>4s}{'  E' if r['name'] in Eset else '   '}")
        for r in res.values():
            if r['na']: print(f"{r['label']:14s} not applicable at this R_ref (r_min {r['rmin']:.0f} km >= R_ref or window)")
    print(f"G2 anomalous class (|P - obs| <= 2 sigma): {'MET' if o['G2'] else 'NOT MET'}")
    for x in o['g2']: print(f"    {x[0]:14s} P {x[1]:8.3f}  obs {x[2]:7.3f}  2sigma {2*x[3]:6.3f}  {'ok' if x[4] else 'FAIL'}")
    print(f"G3 null class (|P| <= 2 sigma or 0.5):     {'MET' if o['G3'] else 'NOT MET'}")
    for x in o['g3']: print(f"    {x[0]:14s} P {x[1]:8.3f}  obs {x[2]:7.3f}  tol {x[3]:6.3f}  {'ok' if x[4] else 'FAIL'}")
    print(f"G4 equal-depth control:                    {'MET' if o['G4'] else 'NOT MET'}")
    for x in o['g4']: print(f"    {x[0]:14s} B {x[1]:11.3e}  P {x[2]:8.3f}  obs {('%7.3f'%x[3]) if x[3] is not None else '      -'}  class {x[4]}  {'ok' if x[5] else 'FAIL'}")
    print(f"G5 Spearman rho(P, obs) = {o['rho']:.3f} over {o['npub']} flybys, permutation p (200000, seed 20261016) = {o['p']:.4f}; threshold 0.7: {'MET' if o['G5'] else 'NOT MET'}\n")
    return o

OP=report(R0,f"PRIMARY R_ref = {PRIMARY:.0f} km (spacecraft R_sun)")
# sensitivity (reported only)
for Rr in R_REFS[1:]:
    report(run(Rr),f"SENSITIVITY R_ref = {Rr:.0f} km",full=False)
report(run(PRIMARY,use_earth_R=True),f"SENSITIVITY R_ref = {PRIMARY:.0f} km, Earth heliocentric distance in place of spacecraft's",full=False)

# CSV
with open(os.path.join(OUT,"flyby_depth_control.csv"),"w",newline='',encoding='utf-8') as f:
    w=csv.writer(f)
    w.writerow(["flyby","date","r_min_km","R_ref_km","t_out_minus_t_in_h","cos_psi_in","cos_psi_out","R_sun_in_au","R_sun_out_au","B","vinf_km_s","P_mm_s","dVinf_obs_mm_s","sigma_mm_s","sigma_published","class","equal_depth_tercile"])
    comp,Eset,_=evaluate(R0,'csv')
    for name,label,date,dv,sg,sgpub,note in FLYBYS:
        r=R0[name]
        if r['na']: w.writerow([label,date,f"{r['rmin']:.0f}",PRIMARY,"","","","","","","","",dv,sg,sgpub,"NA",""]); continue
        w.writerow([label,date,f"{r['rmin']:.0f}",PRIMARY,f"{r['dt_h']:.3f}",f"{r['cin']:.6f}",f"{r['cout']:.6f}",f"{r['Rin']/AU_KM:.6f}",f"{r['Rout']/AU_KM:.6f}",f"{r['B']:.6e}",f"{r['vinf']:.4f}",f"{r['P']:.4f}",dv if dv is not None else "",sg if sg is not None else "",sgpub,r['cls'],"E" if name in Eset else ""])
print("wrote flyby_depth_control.csv")
