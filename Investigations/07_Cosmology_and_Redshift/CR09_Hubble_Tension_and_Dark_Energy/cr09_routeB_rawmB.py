import numpy as np
from scipy.stats import spearmanr
raw=np.genfromtxt('../../../Datasets/cosmology/PantheonPlusSH0ES.dat',names=True,dtype=None,encoding='utf-8')
z=raw['zHD'].astype(float);mB=raw['mB'].astype(float);e=raw['mBERR'].astype(float);x1=raw['x1'].astype(float);x1e=raw['x1ERR'].astype(float);c=raw['c'].astype(float);ce=raw['cERR'].astype(float);cal=raw['IS_CALIBRATOR'].astype(int)
m=(cal==0)&(z>0.01);z,mB,e,x1,x1e,c,ce=[a[m] for a in (z,mB,e,x1,x1e,c,ce)]
print('SNe used',len(z),'z range %.4f-%.4f'%(z.min(),z.max()))
mu0=5*np.log10((1+z)*np.log(1+z)*1e0)  # d_L/(c/H0) shape; offset absorbed in M
def fit(sint,a=0.15,b=3.0):
    for _ in range(3):
        var=e**2+(a*x1e)**2+(b*ce)**2+sint**2; w=1/var
        X=np.c_[np.ones_like(z),-x1,c]; y=mB-mu0
        A=X.T@(X*w[:,None]); th=np.linalg.solve(A,X.T@(w*y)); M,a,b=th
    res=y-X@th; var=e**2+(a*x1e)**2+(b*ce)**2+sint**2
    return th,res,(res**2/var).sum(),var
th,res,chi2,var=fit(0.0); dof=len(z)-3
print('sigma_int=0: M=%.4f alpha=%.4f beta=%.4f chi2/dof=%.3f (chi2=%.1f dof=%d)'%(*th,chi2/dof,chi2,dof))
lo,hi=0.0,0.6
for _ in range(60):
    mid=(lo+hi)/2; t,r,c2,v=fit(mid)
    if c2/dof>1: lo=mid
    else: hi=mid
sint=(lo+hi)/2; th,res,chi2,var=fit(sint)
print('sigma_int for chi2/dof=1: %.4f mag ; alpha=%.4f beta=%.4f M=%.4f'%(sint,th[1],th[2],th[0]))
print('(a) sigma_int <= 0.15:',sint<=0.15)
order=np.argsort(z);bins=np.array_split(order,8)
mx=0
for i,b in enumerate(bins):
    md=np.median(res[b]); mx=max(mx,abs(md)); print('  bin %d z %.3f-%.3f n=%d median resid %+.4f  mean %+.4f  se %.4f'%(i+1,z[b].min(),z[b].max(),len(b),md,res[b].mean(),res[b].std()/np.sqrt(len(b))))
rho=spearmanr(z,res)[0]
print('(b) max |bin median| = %.4f (<=0.06: %s); Spearman(z,resid) = %+.3f (|rho|<0.10: %s)'%(mx,mx<=0.06,rho,abs(rho)<0.10))
print('T3:', 'MET' if (sint<=0.15 and mx<=0.06 and abs(rho)<0.10) else ('SYSTEMATIC RESIDUAL (lead)' if sint<=0.15 else 'NOT MET'))
