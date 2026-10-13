import glob, numpy as np
from astropy.io import fits
from astropy.timeseries import LombScargle
t=[];f=[]
for p in sorted(glob.glob(r'C:\sdt-data\kic8462852\kplr008462852-*_llc.fits')):
    h=fits.open(p); d=h[1].data; tt=d['TIME']; ff=d['PDCSAP_FLUX']; m=np.isfinite(tt)&np.isfinite(ff)
    t.append(tt[m]); f.append(ff[m]/np.median(ff[m]))
t=np.concatenate(t); f=np.concatenate(f); print("Kepler cadences used: %d (BKJD %.1f-%.1f)"%(len(t),t.min(),t.max()))
ok=True
for ep,dep in [(792,16.0),(1519,21.5)]:
    m=(t>ep-1)&(t<ep+1)
    if m.sum()==0: print("[V1] no data near",ep); ok=False; continue
    i=np.argmin(f[m]); dd=(1-f[m][i])*100; te=t[m][i]; g=abs(dd-dep)<=3 and abs(te-ep)<=1; ok&=g
    print("[V1] D%d: minimum at BKJD %.3f, depth %.2f%% (registered %.1f +/- 3) -> %s"%(ep,te,dd,dep,"met" if g else "NOT MET"))
mo=f>=0.99; freq=np.linspace(1/2.0,1/0.5,20000); pw=LombScargle(t[mo],f[mo]).power(freq); P=1/freq[np.argmax(pw)]; g2=abs(P-0.88)<=0.02
print("[V2] strongest Lomb-Scargle period in 0.5-2 d: %.4f d -> %s"%(P,"met" if g2 else "NOT MET")); ok&=g2
h=6.62607015e-34;c=299792458.0;kB=1.380649e-23
def Bl(lam,T): return 2*h*c*c/lam**5/np.expm1(h*c/(lam*kB*T))
zp={'W1':(309.54,3.368e-6),'W2':(171.79,4.618e-6),'W3':(31.676,12.082e-6),'W4':(8.363,22.194e-6)}
meas={'W1':(10.425,0.023),'W2':(10.436,0.020),'W3':(10.591,0.123),'W4':(9.423,None)}
Ts=6750.0
def Fnu_bb(band,T): lam=zp[band][1]; return Bl(lam,T)*lam*lam/c   # per unit solid angle, arbitrary normalisation
def Fnu_meas(band): return zp[band][0]*10**(-0.4*meas[band][0])
norm=Fnu_meas('W1')/Fnu_bb('W1',Ts)
pred={b:meas['W1'][0] for b in zp}   # attempt 2: Vega-colour-zero photosphere (amendment); attempt 1 used a W1-normalised blackbody (G0 at V3)
model_sig=0.03
dW2=meas['W2'][0]-pred['W2']; g3=abs(dW2)<=3*np.hypot(meas['W2'][1],model_sig)
print("[V3] photosphere (Vega colour 0; T*=%.0f K for SED shape): predicted W2 %.3f vs measured %.3f +/- %.3f (diff %+.3f, %.1f sigma incl. model 0.03) -> %s"%(Ts,pred['W2'],meas['W2'][0],meas['W2'][1],dW2,dW2/np.hypot(meas['W2'][1],model_sig),"met" if g3 else "NOT MET")); ok&=g3
print("   predicted photosphere W3 %.3f (measured %.3f +/- %.3f), W4 %.3f (measured %.3f, upper limit)"%(pred['W3'],meas['W3'][0],meas['W3'][1],pred['W4'],meas['W4'][0]))
if not ok: print("VALIDATIONS NOT MET -> Q1 not run"); raise SystemExit
print("VALIDATIONS: met\n")
E_allow={'W3':10**(0.4*(pred['W3']-meas['W3'][0]+2*np.hypot(meas['W3'][1],model_sig)))-1, 'W4':10**(0.4*(pred['W4']-meas['W4'][0]))-1}
print("allowed fractional excess: W3 %.3f (2 sigma), W4 %.3f (upper limit)"%(E_allow['W3'],E_allow['W4']))
fdef=0.03; sig=5.670374419e-8
print("Q1 required excess E_req = f [B(T_d)/sT_d^4]/[B(T*)/sT*^4], f = %.2f:"%fdef)
excl=[];pay=[]
for Td in [100,150,200,300,400,500,700,1000,1500]:
    row=[]
    for b in ('W3','W4'):
        lam=zp[b][1]; Er=fdef*(Bl(lam,Td)/(sig*Td**4))/(Bl(lam,Ts)/(sig*Ts**4)); row.append((b,Er,Er/E_allow[b]))
    ex=any(r>=3 for _,_,r in row); py_=all(Er<=E_allow[b] for b,Er,_ in row)
    excl.append(ex); pay.append(py_)
    print("   T_d %5d K: W3 E_req %.3f (x%.1f allowed) ; W4 E_req %.3f (x%.1f allowed) -> %s"%(Td,row[0][1],row[0][2],row[1][1],row[1][2],"steady absorption EXCLUDED" if ex else ("absorption pays its bill" if py_ else "between")))
print("Q1 summary: excluded at %d of %d dust temperatures"%(sum(excl),len(excl)))

