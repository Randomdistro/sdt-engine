import re, math
src=open('../../../Engine/include/sdt/laws.hpp',encoding='utf-8').read()
def K(n): return float(re.search(r'inline constexpr double '+n+r'\s*=\s*([0-9\'.eE+-]+);',src).group(1).replace("'",''))
c,hbar,al,Rp,a0,mp,mn,md,e=[K(n) for n in ('c','hbar','alpha','R_p','a_0','m_p','m_n','m_d','e_charge')]
MeV=1e6*e
Bd=(mp+mn-md)*c*c/MeV
dw=Bd*MeV/hbar
kp=(1/al)*math.sqrt(Rp/a0)
Om=c/(kp*Rp)
print(f'B_d = {Bd:.6f} MeV   (spec 2.224)')
print(f'delta_omega = B_d/hbar = {dw:.4e} rad/s   (spec 3.38e21)  rel {dw/3.38e21-1:+.3%}')
print(f'k(proton surface) = {kp:.5f}  -> seat speed c/k = {1/kp:.4f} c   (spec 1.83c)')
print(f'Omega_rim = c/(k R_p) = {Om:.4e} rad/s   (spec 6.52e23)  rel {Om/6.52e23-1:+.3%}')
print(f'ratio dw/Omega_rim = {dw/Om:.4e}   (spec 5.2e-3)  rel {dw/Om/5.2e-3-1:+.3%};  ratio/alpha = {dw/Om/al:.4f} (spec says ~29% off alpha: {(dw/Om/al-1):+.1%})')
Escale=al*hbar*c/Rp/MeV
print(f'engine interaction scale alpha*hbar*c/R_p = {Escale:.4f} MeV; B_d/scale = {Bd/Escale:.4f}')
