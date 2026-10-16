import math
from scipy.integrate import quad
c=299792458.0; T0=2.7255; b=2.897771955e-3; P0=1.39159e-14; Peff=5.2268e31
kop=1476.625; Rs=6.957e8; AU=1.495978707e11
print('c/676.6', c/676.6, 'c/676.6^2', c/676.6**2)
print('c/1090', c/1090, 'c/1090^2', c/1090**2)
N=(Peff/P0)**0.25; print('N_origin',N,'lam',b/T0/N,'cfar',c/N**2,'tau',b/T0/N/(c/N**2))
print('c/c_far(Gamma) given 4.8917e-15 ->', c/4.8917e-15, ' sqrt of that', math.sqrt(c/4.8917e-15))
print('N origin from c/c_far = N^2 consistent?', N**2, c/N**2)
# solar deficits
for r,l in((Rs,'Rsun'),(AU,'1AU'),(3*Rs,'3Rsun')):
    z=kop/r; print(l,z,2*c*z)
print('galactic', 2*c*1.7512e-7)
# DSOC step 2
rS=2*AU; rE=AU; bb=3*Rs
t1=2*kop/c*math.log(4*rS*rE/bb**2); print('Dt1 coeff',2*kop/c,'ln arg',4*rS*rE/bb**2,'ln',math.log(4*rS*rE/bb**2),'Dt1 us',t1*1e6)
t2=kop**2/(c*bb)*math.pi; print('Dt2 ps',t2*1e12,'mm',t2*c*1e3,'cycles@1550nm',t2*c/1550e-9)
print('standard 1st-order Shapiro (1+gamma)GM/c^3 form: 2*kop/c*ln(...)=same form; GR full = (1+g)*kop/c *ln =', 2*kop/c*math.log(4*rS*rE/bb**2))
# SN integral
H=67.4
E=lambda z: 1/math.sqrt(0.25*(1+z)**3+0.75)
I=quad(E,0,11.256)[0]; print('integral to 11.256',I)
DL=c/1e3/H*12.256*I; print('DL SDT',DL)
# LCDM naive at 14.32
Om=0.315
Ec=lambda z: 1/math.sqrt(Om*(1+z)**3+1-Om)
Ic=quad(Ec,0,14.32)[0]; DLc=c/1e3/H*15.32*Ic; print('DL LCDM 14.32 (H=67.4, Om=.315)',DLc, 'ratio',DL/DLc)
I2=quad(E,0,14.32)[0]; print('SDT integral at z=14.32 naive', c/1e3/H*15.32*I2)
print('claimed ratio', (175236/224810)**2*(12.256/15.32)**2)
# ages
Om_rad=1/(4*676.6)
f=lambda lnN: 1/(Om_rad*math.exp(4*lnN)+0.25*math.exp(3*lnN)+0.75)  # dN/N * 1/(..)  with N-dependent H
# local: t = TH * int dN/(N * h(N)) , h = sqrt(Om_rad N^4+ N^3/4+3/4)
Ng=2.4756e11
h=lambda n: math.sqrt(Om_rad*n**4+0.25*n**3+0.75)
TH=977.8/H  # Gyr
loc=quad(lambda l: 1/h(math.exp(l)),0,math.log(Ng),limit=500,epsabs=1e-12)[0]
far=quad(lambda l: math.exp(l)/h(math.exp(l)),0,math.log(Ng),limit=500,epsabs=1e-12)[0]
print('TH',TH,'local int',loc,'->Gyr',loc*TH,' far int',far,'->Gyr',far*TH)
# future
fut=quad(lambda l: 1/math.sqrt(0.25*math.exp(3*l)+0.75+Om_rad*math.exp(4*l)),math.log(1e-12),0)[0]
print('future local to N=1/676.6', quad(lambda l:1/math.sqrt(0.25*math.exp(3*l)+0.75+Om_rad*math.exp(4*l)),math.log(1/676.6),0)[0]*TH)
print('future local to N=1/Ngamma', quad(lambda l:1/math.sqrt(0.25*math.exp(3*l)+0.75+Om_rad*math.exp(4*l)),-math.log(Ng),0)[0]*TH)
print('far future 1->0', quad(lambda n:1/math.sqrt(0.25*n**3+0.75),0,1)[0], '*TH', quad(lambda n:1/math.sqrt(0.25*n**3+0.75),0,1)[0]*TH)
print('far future to 1/676.6', quad(lambda n:1/math.sqrt(0.25*n**3+0.75),1/676.6,1)[0]*TH)
print('2/sqrt3*ln(1/N)',2/math.sqrt(3)*math.log(Ng)*TH)
print('N_lock 2^-1/2 P',P0/4)
# Hubble time consistency
print('Mpc s', 3.0856775814913673e22, 'TH s', 3.0856775814913673e19/H)
# 1+z=1090 depth
print('H0 probe example: c*z/D with z_emit', None)
