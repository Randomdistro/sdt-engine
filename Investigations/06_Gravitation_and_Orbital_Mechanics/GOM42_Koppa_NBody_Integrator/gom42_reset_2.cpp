// GOM42 Round 2, V3' (2026-10-14): stability-correct Lagrange triangle. Registration: GOM42_RESET_ASSESSMENT_2026-10-14.md sections 0-2 (written before this file existed).
// Integrator copied from gom42_reset_1.cpp (velocity Verlet, a_i = c2 sum k_j (r_j - r_i)/r^3, collision stop restoring the pre-step state).
// Author: J. C. Harvey, Melbourne.
#include <array>
#include <cmath>
#include <cstdio>
#include <vector>
static const double PI_ = 3.14159265358979323846;
using V = std::array<double,3>;
struct Body { double k, rc; V r, v; };
static V sub(V a, V b){return {a[0]-b[0],a[1]-b[1],a[2]-b[2]};} static double nrm(V a){return std::sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);}
static std::vector<V> acc(const std::vector<Body>& B, double c2, bool& hit){ std::vector<V> a(B.size(),V{0,0,0}); hit=false;
  for(size_t i=0;i<B.size();++i) for(size_t j=i+1;j<B.size();++j){ V d=sub(B[j].r,B[i].r); double r=nrm(d); if(r<=B[i].rc+B[j].rc){hit=true; return a;} double s=c2/(r*r*r);
    for(int q=0;q<3;++q){ a[i][q]+=s*B[j].k*d[q]; a[j][q]-=s*B[i].k*d[q]; } } return a; }
static bool step(std::vector<Body>& B, double dt, double c2){ const auto save=B; bool hit; auto a=acc(B,c2,hit); if(hit) return false;
  for(size_t i=0;i<B.size();++i) for(int q=0;q<3;++q){ B[i].v[q]+=0.5*dt*a[i][q]; B[i].r[q]+=dt*B[i].v[q]; }
  auto a2=acc(B,c2,hit); if(hit){ B=save; return false; } for(size_t i=0;i<B.size();++i) for(int q=0;q<3;++q) B[i].v[q]+=0.5*dt*a2[i][q]; return true; }
static V P(const std::vector<Body>& B){V p{0,0,0}; for(auto&b:B) for(int q=0;q<3;++q) p[q]+=b.k*b.v[q]; return p;}
static V Lm(const std::vector<Body>& B){V l{0,0,0}; for(auto&b:B){ l[0]+=b.k*(b.r[1]*b.v[2]-b.r[2]*b.v[1]); l[1]+=b.k*(b.r[2]*b.v[0]-b.r[0]*b.v[2]); l[2]+=b.k*(b.r[0]*b.v[1]-b.r[1]*b.v[0]); } return l;}
static V bary(const std::vector<Body>& B){ V c{0,0,0}; double K=0; for(auto&b:B){ K+=b.k; for(int q=0;q<3;++q) c[q]+=b.k*b.r[q]; } for(int q=0;q<3;++q) c[q]/=K; return c; }
static std::vector<Body> lagrange(double k1,double k2,double k3,double s,double c2,double perturb=0){
  double K=k1+k2+k3, w=std::sqrt(c2*K/(s*s*s)); std::vector<Body> B={{k1,0,{0,0,0},{0,0,0}},{k2,0,{s,0,0},{0,0,0}},{k3,0,{s/2,s*std::sqrt(3.0)/2,0},{0,0,0}}};
  V g=bary(B); for(auto&b:B){ for(int q=0;q<3;++q) b.r[q]-=g[q]; b.v={-w*b.r[1], w*b.r[0], 0}; }
  B[2].r[0]+=perturb; return B; }
static double run(std::vector<Body> B,double s,double c2,double dt,int periods,int perP,double* bc,double* pd,double* ld,const int* marks=nullptr,int nm=0){
  auto B0=B; V p0=P(B), l0=Lm(B); double np=0,nl=0; for(auto&b:B){np+=b.k*nrm(b.v); nl+=b.k*nrm(b.r)*nrm(b.v);} double sd=0; *bc=0; int m=0;
  for(int i=1;i<=periods*perP;++i){ step(B,dt,c2); for(int a=0;a<3;++a){int b=(a+1)%3; sd=std::max(sd,std::fabs(nrm(sub(B[a].r,B[b].r))-s)/s);} *bc=std::max(*bc,nrm(bary(B))/s); if(marks&&m<nm&&i==marks[m]*perP){ std::printf("     [diagnostic] max side drift after %2d periods: %.3e\n",marks[m],sd); ++m; } }
  *pd=nrm(sub(P(B),p0))/np; *ld=nrm(sub(Lm(B),l0))/nl; return sd; }
int main(){
  std::printf("GOM42 Round 2, V3' (registered in GOM42_RESET_ASSESSMENT_2026-10-14.md)\n=======================================================================\n\n");
  const double c2=1.0, s=1.0;
  { double K=1.02, mk=27*(1*0.01+0.01*0.01+0.01*1), rt=K*K; std::printf("Routh: 27 sum(k_i k_j) = %.4f < (sum k)^2 = %.4f : %s\n",mk,rt,mk<rt?"stable":"UNSTABLE"); }
  double w=std::sqrt(c2*1.02/(s*s*s)), Pd=2*PI_/w, dt=Pd/4000; double bc,pd,ld;
  double sd=run(lagrange(1.0,0.01,0.01,s,c2),s,c2,dt,20,4000,&bc,&pd,&ld);
  bool ok=sd<=1e-4&&bc<=1e-10&&pd<=1e-11&&ld<=1e-10;
  std::printf("[V3'] sources (1, 0.01, 0.01), 20 periods, dt = P/4000: max side drift %.3e (<= 1e-4), barycentre drift %.3e (<= 1e-10), momentum drift %.2e (<= 1e-11), angular-momentum drift %.2e (<= 1e-10) -> %s\n",sd,bc,pd,ld,ok?"met":"NOT MET");
  { double b2,p2,l2; double sp=run(lagrange(1.0,0.01,0.01,s,c2,1e-8),s,c2,dt,20,4000,&b2,&p2,&l2); std::printf("     perturbation check (one source displaced by 1e-8 s): max side drift over 20 periods %.3e (initial perturbation 1e-8; no exponential growth if the drift stays near the unperturbed value %.3e)\n",sp,sd); }
  { double K=3.0, w3=std::sqrt(c2*K/(s*s*s)), P3=2*PI_/w3, dt3=P3/4000; int marks[3]={1,2,5}; double b3,p3,l3; std::printf("     [post-seen diagnostic, not gated] equal sources (1,1,1):\n"); run(lagrange(1,1,1,s,c2),s,c2,dt3,5,4000,&b3,&p3,&l3,marks,3); }
  return 0; }
