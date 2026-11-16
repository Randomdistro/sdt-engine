#include <sdt/laws.hpp>
#include <array>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
using Vec=std::array<double,3>;
struct Seat {Vec x;double count;};
double dist(Vec a,Vec b){double s=0;for(int j=0;j<3;j++)s+=(a[j]-b[j])*(a[j]-b[j]);return std::sqrt(s);}
double signedEnergy(const std::vector<Seat>& s,double C){double E=0;for(size_t i=0;i<s.size();++i)for(size_t j=i+1;j<s.size();++j)E+=s[i].count*s[j].count*C/dist(s[i].x,s[j].x);return E;}
std::vector<Seat> tetra(double edge){double t=edge/(2*std::sqrt(2.0));return {{{t,t,t},1},{{t,-t,-t},1},{{-t,t,-t},1},{{-t,-t,t},1},{{t,0,0},-1},{{-t,0,0},-1}};}
int main(){using namespace sdt::laws;using namespace measured;
 const double Rp=law_III::R_p_lock,C=law_III::F_nuclear_electron(1,Rp)*Rp*Rp;
 const double eps=1e-10;int failures=0;double worst=0;
 const double b=Rp,analytic=law_IV::locked_engaged_volume_sphere(b);
 std::cout<<std::setprecision(17)<<"{\"laws_sha256\":\""<<SDT_LAWS_HASH<<"\",\"R_p_lock_m\":"<<Rp<<",\"C_J_m\":"<<C<<",\"P_conv_Pa\":"<<law_I::P_conv<<",\"canonical_R_p_m\":"<<R_p<<",\"SI_nuclear_magneton_J_T\":"<<e_charge*hbar/(2*m_p)<<",\"lock_volume_m3\":"<<analytic<<",\"lock_resistance_J\":"<<law_IV::resistance_from_engaged_volume(analytic)<<",\"constituent_rest_energy_J\":"<<2*(m_p+m_n)*c*c<<",\"lock_integrals\":[";
 bool first=true;for(int n:{512,1024,2048}){double step=1.0/n,sum=1;for(int i=1;i<n;++i)sum+=(i%2?4:2)*std::pow(i*step,6);double numeric=8*std::numbers::pi*b*b*b*step*sum/3;double residual=std::abs(numeric-analytic)/analytic;worst=std::max(worst,residual);if(residual>eps)++failures;if(!first)std::cout<<',';first=false;std::cout<<"{\"N\":"<<n<<",\"relative_error\":"<<residual<<"}";}
 const double deuteronD=Rp*(2+1.0/3),deuteronB=3*C/deuteronD;
 const double alphaB=-signedEnergy(tetra(2*Rp),C);
 // Source-supported NP17 point-seat control only. No finite neutron/contact closure is supplied.
 const double edge=2*Rp,hstep=edge*1e-4;
 const double gradient=(signedEnergy(tetra(edge+hstep),C)-signedEnergy(tetra(edge-hstep),C))/(2*hstep);
 const double expectedGradient=alphaB/edge;
 const double gradientResidual=std::abs(gradient-expectedGradient)/std::abs(expectedGradient);
 if(gradientResidual>1e-3)++failures;
 const double separated=0; // Limit a->infinity of the 1/a source-supported control.
 const double materialBudgetExcess=1.83*1.83-1;
 std::cout<<"],\"NP17_conditional\":{\"deuteron_binding_MeV\":"<<deuteronB/MeV_to_J<<",\"alpha_binding_MeV\":"<<alphaB/MeV_to_J<<",\"alpha_at_measured_Rp_MeV\":"<<-signedEnergy(tetra(2*R_p),C)/MeV_to_J<<",\"radial_gradient_J_m\":"<<gradient<<",\"gradient_relative_error\":"<<gradientResidual<<",\"separated_limit_J\":"<<separated<<",\"interior_stationary_point\":false,\"finite_contact_physics\":false},\"spherical_union_controls\":{\"disjoint_synchrony_J\":"<<law_IV::synchrony_resistance_delta(4*analytic,4*analytic)<<",\"coincident_synchrony_J\":"<<law_IV::synchrony_resistance_delta(analytic,4*analytic)<<",\"alpha_binding_status\":\"OPEN: resistance is not a derived binding map\"},\"1_83c_material_budget_excess_c2\":"<<materialBudgetExcess<<",\"pattern_speed_mapping\":\"OPEN\",\"worst_analytic_relative_error\":"<<worst<<",\"failures\":"<<failures<<"}\n";
 return failures?1:0;
}
