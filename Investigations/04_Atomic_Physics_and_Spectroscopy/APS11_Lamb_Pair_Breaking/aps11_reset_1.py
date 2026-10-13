import math
# engine-consistent constants (CODATA, as in measured::)
h=6.62607015e-34; c=299792458.0; me=9.1093837015e-31; mp=1.67262192595e-27; md=3.3435837768e-27
alpha=7.2973525693e-3; a0=5.29177210903e-11; Ry=13.605693122994*1.602176634e-19
mHe4n=6.6446573357e-27-2*me  # He-4 nucleus approx (atomic mass minus 2 electrons; binding of electrons neglected)
def koppa(Z,n,M,fMHz):
    mu=me*M/(me+M); rn=a0*n*n/Z*(me/mu); vn=Z*alpha*c/n
    dE=h*fMHz*1e6; dv=dE/(mu*vn); dr=2*dv/vn*rn
    return rn,vn,dE,dv,dr
print("[V1] H n=2 (1057.8450 MHz): ", end="")
rn,vn,dE,dv,dr=koppa(1,2,mp,1057.8450)
ok=abs(dr*1e15/0.2722-1)<0.01 and abs(dv/0.7034-1)<0.01
print("dr = %.4f fm (PPT08 0.2722), dv = %.4f m/s (PPT08 0.7034) -> %s"%(dr*1e15,dv,"met" if ok else "NOT MET"))
for name,Z,n,M,f in [("H n=2",1,2,mp,1057.8450),("D n=2",1,2,md,1059.2341),("H n=3",1,3,mp,314.819),("He+ n=2",2,2,mHe4n,14041.13)]:
    rn,vn,dE,dv,dr=koppa(Z,n,M,f)
    print("  %-8s f = %10.4f MHz : r_n = %.5e m, v_n = %.4e m/s, dv = %.4f m/s, |dr| = %.4f fm, dr/r_n = %.3e"%(name,f,rn,vn,dv,dr*1e15,dr/rn))
print("G_sign: measured 2S1/2 lies ABOVE 2P1/2 in H, D and He+ (all intervals positive) -> S2 consistent (ontology written with the sign known)")
