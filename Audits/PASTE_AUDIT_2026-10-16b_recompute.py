import math
hb=1.054571817e-34; c=299792458.0; al=7.2973525693e-3
mp=1.67262192369e-27; me=9.1093837015e-31
lam=hb/(mp*c); Rp=4*lam; re=al*hb/(me*c); lP=1.616255e-35
print('lam_Cp',lam,'Rp',Rp,'re',re)
Peff=4*me*c*c/(math.pi*Rp**2*re); print('Peff = 4 me c2/(pi Rp^2 re)',Peff)
print('Peff closed mp^2 me^2 c^5/(4 pi al hb^3)',mp**2*me**2*c**5/(4*math.pi*al*hb**3))
print('Peff = 4 al hb c/(pi Rp^2 re^2)',4*al*hb*c/(math.pi*Rp**2*re**2))
Vint=math.pi/4*Rp**2*re; print('Vint',Vint,' me c2/Vint',me*c*c/Vint)
Ns=5.894e61; Pcmb=1.39159e-14; Pconv=Ns*3*Pcmb; print('Pconv = N*3*Pcmb',Pconv)
f=Peff/Pconv; print('f = Peff/Pconv',f)
Vd=3*me*c*c/Pconv; print('Vdisp_e = 3 me c2/Pconv (definition)',Vd)
print('Vd/(3 Vint)',Vd/(3*Vint))
print('Vd/(3 Vint) with paste Vd 9.98094e-62:',9.98094e-62/(3*Vint))
B21=Rp*re/(4*lP**2); print('B21 = Rp re/(4 lP^2)',B21)
ko=lP**2/lam; print('koppa_baryon lP^2/lam',ko,' re/ko',re/ko)
G=lP**2*c**3/hb; print('G recovered from lP: lP^2 c^3/hbar',G)
print('G mp/c2 (G=6.6743e-11)',6.6743e-11*mp/c**2)
print('R_charge',math.sqrt(Rp*re),'pi Rcharge^2',math.pi*Rp*re,'4 pi lP^2',4*math.pi*lP**2)
print('ratio of ratio to hbar-free form: re*mp c/(hb) * c^3 hb... G-free check: ko*c^2/mp', ko*c**2/mp)
# two other constant sets the paste uses
for nm,v in (('abstract Peff',5.22725e31),('table Peff',5.2273e31),('header Peff',5.2268e31)):
    print(nm,v,'rel to Coulomb form',v/Peff-1)
for nm,v in (('abstract Pconv',2.46082e48),('header Pconv',2.46061e48),('table P_cf*3',3*8.2027e47)):
    print(nm,v,'rel to N*3*Pcmb',v/Pconv-1)
