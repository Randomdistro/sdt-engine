// GOM42 reset, instrument 1 (2026-10-10): koppa N-body velocity-Verlet integrator and its validation gates. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <array>
#include <cmath>
#include <cstdio>
#include <vector>
using V = std::array<double,3>;
struct Body { double k, rc; V r, v; };
static V sub(V a, V b){return {a[0]-b[0],a[1]-b[1],a[2]-b[2]};} static double nrm(V a){return std::sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);}
static std::vector<V> acc(const std::vector<Body>& B, double c2, bool& hit){ std::vector<V> a(B.size(),V{0,0,0}); hit=false;
  for(size_t i=0;i<B.size();++i) for(size_t j=i+1;j<B.size();++j){ V d=sub(B[j].r,B[i].r); double r=nrm(d); if(r<=B[i].rc+B[j].rc){hit=true; return a;} double s=c2/(r*r*r);
    for(int q=0;q<3;++q){ a[i][q]+=s*B[j].k*d[q]; a[j][q]-=s*B[i].k*d[q]; } } return a; }
static bool step(std::vector<Body>& B, double dt, double c2){ const auto save=B; /* attempt 2: a rejected step restores the pre-step state (attempt 1 left the drift in place) */ bool hit; auto a=acc(B,c2,hit); if(hit) return false;
  for(size_t i=0;i<B.size();++i) for(int q=0;q<3;++q){ B[i].v[q]+=0.5*dt*a[i][q]; B[i].r[q]+=dt*B[i].v[q]; }
  auto a2=acc(B,c2,hit); if(hit){ B=save; return false; } for(size_t i=0;i<B.size();++i) for(int q=0;q<3;++q) B[i].v[q]+=0.5*dt*a2[i][q]; return true; }
static double energy(const std::vector<Body>& B,double c2){ double e=0; for(size_t i=0;i<B.size();++i){ e+=0.5*B[i].k*(B[i].v[0]*B[i].v[0]+B[i].v[1]*B[i].v[1]+B[i].v[2]*B[i].v[2]); for(size_t j=i+1;j<B.size();++j) e-=c2*B[i].k*B[j].k/nrm(sub(B[i].r,B[j].r)); } return e; }
static V P(const std::vector<Body>& B){V p{0,0,0}; for(auto&b:B) for(int q=0;q<3;++q) p[q]+=b.k*b.v[q]; return p;}
static V Lm(const std::vector<Body>& B){V l{0,0,0}; for(auto&b:B){ l[0]+=b.k*(b.r[1]*b.v[2]-b.r[2]*b.v[1]); l[1]+=b.k*(b.r[2]*b.v[0]-b.r[0]*b.v[2]); l[2]+=b.k*(b.r[0]*b.v[1]-b.r[1]*b.v[0]); } return l;}
int main(){
  std::printf("GOM42 reset instrument 1 (2026-10-10)\n=====================================\n\n");
  const double c2=1.0; int bad=0;
  { std::vector<Body> B={{1.0,0,{0,0,0},{0,0,0}},{3.0,0,{2,0,0},{0,0,0}}}; bool h; auto a=acc(B,c2,h); double s=std::fabs(B[0].k*a[0][0]+B[1].k*a[1][0])/std::fabs(B[0].k*a[0][0]);
    std::vector<Body> B2={{1.0,0,{0,0,0},{0,0,0}},{3.0,0,{4,0,0},{0,0,0}}}; auto b=acc(B2,c2,h); double sc=a[0][0]/b[0][0];
    bool ok=s<1e-14&&std::fabs(sc-4)<1e-12; std::printf("[V0] pair symmetry %.1e ; r doubling scales a by %.12f (expect 4) -> %s\n",s,sc,ok?"met":"NOT MET"); bad+=!ok;
    double kk=sdt::laws::bridge::koppa_per_baryon, cc=sdt::laws::measured::c; std::printf("     dimensions: c^2 koppa_b / (1 m)^2 = %.3e m/s^2 (one baryon at 1 m)\n",cc*cc*kk); }
  std::vector<double> pdr,ldr;
  auto inv=[&](std::vector<Body>&B0,std::vector<Body>&B1){ V p0=P(B0),p1=P(B1),l0=Lm(B0),l1=Lm(B1); double sp=0,sl=0,np=0,nl=0; for(auto&b:B0){np+=b.k*nrm(b.v); nl+=b.k*nrm(b.r)*nrm(b.v);} sp=nrm(sub(p1,p0))/np; sl=nrm(sub(l1,l0))/nl; pdr.push_back(sp); ldr.push_back(sl); };
  // V1 circular two-body: equal k=0.5 each, separation 1 -> relative orbit omega^2 = c2*(k1+k2)/r^3
  auto circ=[&](double dt_frac,int periods,double& sepdrift,double& edrift,std::vector<Body>& out){ double k=0.5,r=1.0,w=std::sqrt(c2*(2*k)/(r*r*r)),Pd=2*M_PI/w,vv=w*r/2;
    std::vector<Body> B={{k,0,{-0.5,0,0},{0,-vv,0}},{k,0,{0.5,0,0},{0,vv,0}}}; auto B0=B; double e0=energy(B,c2); sepdrift=0; edrift=0; double dt=Pd*dt_frac; int n=(int)std::llround(periods/dt_frac);
    for(int i=0;i<n;++i){ step(B,dt,c2); sepdrift=std::max(sepdrift,std::fabs(nrm(sub(B[0].r,B[1].r))-1)); edrift=std::max(edrift,std::fabs(energy(B,c2)/e0-1)); } out=B; inv(B0,B); };
  { double sd,ed; std::vector<Body> o; circ(1.0/2000,100,sd,ed,o); bool ok=sd<=5e-5&&ed<=5e-6; std::printf("[V1] circular 100 periods dt=P/2000: max separation drift %.2e (<=5e-5), energy drift %.2e (<=5e-6) -> %s\n",sd,ed,ok?"met":"NOT MET"); bad+=!ok; }
  { auto run=[&](double frac){ double k=0.5,w=1.0,Pd=2*M_PI/w,vv=0.5; std::vector<Body> B={{k,0,{-0.5,0,0},{0,-vv,0}},{k,0,{0.5,0,0},{0,vv,0}}}; double dt=Pd*frac; int n=(int)std::llround(10/frac); for(int i=0;i<n;++i) step(B,dt,c2); return B; };
    auto exact=[&](){ return std::vector<Body>{{0.5,0,{-0.5,0,0},{0,-0.5,0}},{0.5,0,{0.5,0,0},{0,0.5,0}}}; }();
    auto a=run(1.0/500), b=run(1.0/1000); double ea=nrm(sub(a[1].r,exact[1].r)), eb=nrm(sub(b[1].r,exact[1].r)); bool ok=ea/eb>=3.5; std::printf("[V2] convergence: error at 10 periods dt=P/500 %.3e, P/1000 %.3e, ratio %.3f (>=3.5) -> %s\n",ea,eb,ea/eb,ok?"met":"NOT MET"); bad+=!ok; }
  { double k=1.0,s=1.0,R=s/std::sqrt(3.0),w=std::sqrt(c2*3*k/(s*s*s)),Pd=2*M_PI/w; std::vector<Body> B; for(int i=0;i<3;++i){ double th=2*M_PI*i/3; B.push_back({k,0,{R*std::cos(th),R*std::sin(th),0},{-w*R*std::sin(th),w*R*std::cos(th),0}}); }
    auto B0=B; double dt=Pd/4000, sd=0, bc=0; for(int i=0;i<20*4000;++i){ step(B,dt,c2); for(int a=0;a<3;++a){int b=(a+1)%3; sd=std::max(sd,std::fabs(nrm(sub(B[a].r,B[b].r))-s)/s);} V cm{0,0,0}; for(auto&x:B) for(int q=0;q<3;++q) cm[q]+=x.r[q]/3; bc=std::max(bc,nrm(cm)/s); }
    inv(B0,B); { auto Bd=B0; double dd=0; int mark[5]={1,2,5,10,20},m=0; for(int i=1;i<=20*4000&&m<5;++i){ step(Bd,dt,c2); for(int a=0;a<3;++a){int b=(a+1)%3; dd=std::max(dd,std::fabs(nrm(sub(Bd[a].r,Bd[b].r))-s)/s);} if(i==mark[m]*4000){ std::printf("     [V3 diagnostic] max side drift after %2d periods: %.3e\n",mark[m],dd); ++m; } } } bool ok=sd<=1e-4&&bc<=1e-10; std::printf("[V3] Lagrange triangle 20 periods dt=P/4000: side drift %.2e (<=1e-4), barycentre drift %.2e (<=1e-10) -> %s\n",sd,bc,ok?"met":"NOT MET"); bad+=!ok; }
  { V x1={0.97000436,-0.24308753,0}, v3={-0.93240737,-0.86473146,0}; double T=6.32591398; std::vector<Body> B={{1,0,x1,{-v3[0]/2,-v3[1]/2,0}},{1,0,{-x1[0],-x1[1],0},{-v3[0]/2,-v3[1]/2,0}},{1,0,{0,0,0},v3}};
    auto B0=B; double dt=T/50000; for(int i=0;i<50000;++i) step(B,dt,c2); double ep=0,ev=0; for(int i=0;i<3;++i){ ep+=std::pow(nrm(sub(B[i].r,B0[i].r)),2); ev+=std::pow(nrm(sub(B[i].v,B0[i].v)),2);} ep=std::sqrt(ep/3); ev=std::sqrt(ev/3)/nrm(v3);
    inv(B0,B); bool ok=ep<=2e-5&&ev<=2e-5; std::printf("[V4] figure-eight one period dt=T/50000: RMS position error %.2e, velocity error %.2e (each <=2e-5) -> %s\n",ep,ev,ok?"met":"NOT MET"); bad+=!ok; }
  { double mp=0,ml=0; for(double x:pdr) mp=std::max(mp,x); for(double x:ldr) ml=std::max(ml,x); bool ok=mp<=1e-11&&ml<=1e-10; std::printf("[V5] invariants across V1, V3, V4: max normalised P drift %.2e (<=1e-11), L drift %.2e (<=1e-10) -> %s\n",mp,ml,ok?"met":"NOT MET"); bad+=!ok; }
  { std::vector<Body> B={{1,0.1,{-1,0,0},{0,0,0}},{1,0.1,{1,0,0},{0,0,0}}}; int n=0; bool stopped=false; for(;n<10000000;++n){ if(!step(B,1e-4,c2)){stopped=true;break;} } double sep=nrm(sub(B[0].r,B[1].r)); bool ok=stopped&&sep>=0.2-1e-9&&std::isfinite(sep);
    std::printf("[V6] head-on pair with contact boundary 0.2: stopped %s at step %d, separation %.6f (>= 0.2) -> %s\n",stopped?"yes":"no",n,sep,ok?"met":"NOT MET"); bad+=!ok; }
  std::printf("\nALL GATES: %s\n",bad?"NOT MET":"met");
  return 0; }

