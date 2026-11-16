import re
src=open('../../../Engine/include/sdt/laws.hpp',encoding='utf-8').read()
def K(n): return float(re.search(r'inline constexpr double '+n+r'\s*=\s*([0-9\'.eE+-]+);',src).group(1).replace("'",''))
c,hbar,al,me,mp,md,Rinf,a0=[K(n) for n in ('c','hbar','alpha','m_e','m_p','m_d','R_inf','a_0')]
import math
def mu(M): return me*M/(me+M)
def invlam(Z,M,nl,nu):
    C=Z*al*hbar*c; m=mu(M)
    E=lambda n:-m*C**2/(2*(n*hbar)**2)
    return (E(nu)-E(nl))/(2*math.pi*hbar*c)
# V1,V2,V3
assert abs(invlam(1,1e30,1,2)/(0.75*Rinf)-1)<1e-9,'V1'   # infinite mass
print('V1 infinite-mass Lyman-a vs 0.75 R_inf: rel diff %.2e'%(invlam(1,1e30,1,2)/(0.75*Rinf)-1))
print('V2 Z^2 scaling He+ / H (inf mass): %.9f'%(invlam(2,1e30,1,2)/invlam(1,1e30,1,2)))
RH=Rinf/(1+me/mp)
print('V3 H Lyman-a lambda = %.4f nm; 1/(0.75 R_H) = %.4f nm'%(1e9/invlam(1,mp,1,2),1e9/(0.75*RH)))
print('\nG1: model vs R_H=R_inf/(1+me/mp)')
for nl,nu in ((1,2),(1,3),(2,3),(2,4),(2,5)):
    r=invlam(1,mp,nl,nu)/(RH*(1/nl**2-1/nu**2)); print(f'  {nl}->{nu}: ratio {r:.12f}  {"PASS" if abs(r-1)<1e-9 else "FAIL"}')
print('\nG2: universal R=a0, lambda = 4*pi*k*r_l*r_u/(r_u-r_l) with k=(c/v)sqrt(R/r), v=Z*alpha*c/n, r_n=n^2 a0 (Phase 0 form)')
for Z in range(1,7):
    # per-ion model value at inf mass vs universal-R wavelength; k=(c/v)sqrt(R/r)=1/(alpha sqrt Z)
    lam_ion=1/invlam(Z,1e30,1,2)
    # universal R=a0: r_n=n^2*a0, v_n=Z*alpha*c/n -> k=(c/v)*sqrt(R/r)=n/(Z alpha) * sqrt(a0/(n^2 a0))=1/(Z alpha)
    k=(1/(al*math.sqrt(Z))); rl=a0/Z; ru=4*a0/Z; lam_univ=4*math.pi*k*rl*ru/(ru-rl)
    print(f'  Z={Z}: lambda_univ/lambda_ion = {lam_univ/lam_ion:.6f}  (sqrt Z = {math.sqrt(Z):.6f})  {"PASS" if abs(lam_univ/lam_ion-math.sqrt(Z))<1e-5 else "FAIL"}')
print('\nG3: H-alpha vs D-alpha')
lH=1/invlam(1,mp,2,3); lD=1/invlam(1,md,2,3)
print(f'  model lambda_H = {lH*1e9:.5f} nm, lambda_D = {lD*1e9:.5f} nm, shift = {(lH-lD)*1e9:.5f} nm')
lit=0.179
print(f'  literature (memory, VERIFY) {lit} nm; relative diff {((lH-lD)*1e9/lit-1)*100:.2f}%  {"PASS" if abs((lH-lD)*1e9/lit-1)<0.02 else "FAIL"}')
print('  note: m_d is the deuteron NUCLEAR mass; the atomic reduced mass uses it directly.')
