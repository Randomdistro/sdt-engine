#include <sdt/laws.hpp>
#include <cmath>
#include <iostream>
#include <iomanip>
int main(){
 using namespace sdt::laws; using namespace measured;
 const double C=law_III::F_nuclear_electron(1,a_0)*a_0*a_0;
 const double mu=m_e*m_p/(m_e+m_p), L=hbar;
 const double R=L*L/(mu*C), v=C/L, k=c/v, z=1/(k*k), EB=C/(2*R);
 int failures=0;double worst=0;
 for(int Z=1;Z<=92;++Z)for(int n=1;n<=20;++n){
  const double cz=law_III::F_nuclear_electron(Z,a_0)*a_0*a_0;
  const double rn=n*n*L*L/(mu*cz),vn=cz/(n*L);
  const double residual=std::abs(mu*vn*vn/rn-law_III::F_nuclear_electron(Z,rn))/law_III::F_nuclear_electron(Z,rn);
  worst=std::max(worst,residual);if(residual>1e-10)++failures;
 }
 std::cout<<std::setprecision(17)<<"{\"C_J_m\":"<<C<<",\"reduced_mass_kg\":"<<mu<<",\"R_m\":"<<R<<",\"v_m_s\":"<<v<<",\"k\":"<<k<<",\"surface_z\":"<<z<<",\"binding_J\":"<<EB<<",\"conditional_Lyman_alpha_m\":"<<h*c/(EB*(1-1.0/4))<<",\"force_balance_cases\":1840,\"worst_relative_residual\":"<<worst<<",\"failures\":"<<failures<<",\"compression\":[";
 bool first=true;
 for(double x:{1.0,0.5,0.1,0.01}){const double r=x*R;const double delta=L*L/(2*mu*r*r)-C/r+EB;const double expected=EB*std::pow(1/x-1,2);if(std::abs(delta-expected)>1e-10*EB*std::max(1.0,std::pow(1/x-1,2)))++failures;
  if(!first)std::cout<<',';first=false;std::cout<<"{\"r_over_R\":"<<x<<",\"fixed_action_v_over_c\":"<<L/(mu*r*c)<<",\"equilibrium_v_over_c\":"<<std::sqrt(C/(mu*r))/c<<",\"work_J\":"<<delta<<",\"local_depth\":"<<C/(mu*c*c*r)<<"}";
 }
 std::cout<<"],\"new_fit_parameters\":0,\"action_quantisation_assumed\":true,\"high_Z_nonrelativistic_scope\":true}\n";return failures?1:0;
}
