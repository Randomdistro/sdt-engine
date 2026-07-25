// FD12 - The Poloidal Parcel Operation (Harvey 2026-07-26)
// P1: does a forward-momentum slug self-organise into the poloidal roll
//     (formation, self-propulsion, roll-back, closed cell) on the FD01 relay lattice?
// P2: DISCRIMINATOR - forward coherence length from transient-gain wavelength
//     selection in a plane channel; export Re_crit=(L/l_c)^2 vs pipe's 48^2.
// Gates pre-committed in PROMPT.md BEFORE this file was written.
// Author: J. C. Harvey, Melbourne. Direct run, main session.
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <numbers>
static const double PI2 = std::numbers::pi;

// ---------- shared: SOR Poisson solve  lap(psi) = -omega ----------
static void sor_poisson(std::vector<double>& psi, const std::vector<double>& om,
                        int nx, int ny, double dx, double dy,
                        int sweeps, bool periodic_x) {
    const double dx2 = dx*dx, dy2 = dy*dy;
    const double denom = 2.0*(dx2+dy2);
    const double w = 1.7; // SOR relaxation
    for (int s = 0; s < sweeps; ++s) {
        for (int j = 1; j < ny-1; ++j) {
            for (int i = 0; i < nx; ++i) {
                if (!periodic_x && (i==0 || i==nx-1)) continue;
                int ip = (i+1)%nx, im = (i-1+nx)%nx;
                if (!periodic_x) { ip = i+1; im = i-1; }
                double rhs = (psi[j*nx+ip]+psi[j*nx+im])*dy2
                           + (psi[(j+1)*nx+i]+psi[(j-1)*nx+i])*dx2
                           + om[j*nx+i]*dx2*dy2;
                double nv = rhs/denom;
                psi[j*nx+i] += w*(nv - psi[j*nx+i]);
            }
        }
    }
}

// ================= PHASE 1: slug in a quiescent bath =================
static void phase1() {
    printf("----------------------------------------------------------------\n");
    printf(" PHASE 1  slug -> poloidal roll  (2-D poloidal plane, Re_slug=150)\n");
    printf("----------------------------------------------------------------\n");
    const int nx = 288, ny = 144;
    const double Lx = 3.0, Ly = 1.5;
    const double dx = Lx/nx, dy = Ly/ny;
    const double a = 0.15, U = 1.0, x0 = 0.55, y0 = 0.75;
    const double nu = U*a/150.0;                 // committed Re_slug = 150
    printf("  grid %dx%d, a=%.3f U=%.1f nu=%.3e (Re_slug=%.0f committed)\n",
           nx, ny, a, U, nu, U*a/nu);

    auto run = [&](bool advection, double& xc_travel, double& ratio_pm,
                   double& flank_min_u, double& jet_ratio, double& Upair_out) {
        std::vector<double> om(nx*ny,0.0), psi(nx*ny,0.0), omn(nx*ny,0.0);
        // slug: u = U exp(-r^2/a^2)  ->  omega = -du/dy = 2(y-y0)/a^2 * u
        for (int j=0;j<ny;++j) for(int i=0;i<nx;++i){
            double x=(i+0.5)*dx, y=(j+0.5)*dy;
            double r2=((x-x0)*(x-x0)+(y-y0)*(y-y0))/(a*a);
            om[j*nx+i] = (2.0*(y-y0)/(a*a))*U*std::exp(-r2);
        }
        double dt = 0.2*std::min(dx*dx,dy*dy)/nu;
        dt = std::min(dt, 0.3*dx/ (2.5*U));
        const double t_end = 2.0;                  // enough for >1.5a travel at ~0.4-0.6U
        int steps = (int)(t_end/dt);
        double xc0 = 0.0, wsum0 = 0.0;
        auto centroid = [&](const std::vector<double>& f){
            double s=0, sx=0;
            for (int j=0;j<ny;++j) for(int i=0;i<nx;++i){
                double w2=f[j*nx+i]*f[j*nx+i]; s+=w2; sx+=w2*(i+0.5)*dx; }
            return (s>0)? sx/s : 0.0;
        };
        xc0 = centroid(om); wsum0 = 0;
        double xc_prev = xc0, t_prev = 0.0, Upair = 0.0;
        for (int n=0;n<steps;++n) {
            sor_poisson(psi, om, nx, ny, dx, dy, (n==0)?400:45, false);
            // velocities u=dpsi/dy, v=-dpsi/dx (interior)
            for (int j=1;j<ny-1;++j) for(int i=1;i<nx-1;++i){
                double u = (psi[(j+1)*nx+i]-psi[(j-1)*nx+i])/(2*dy);
                double v = -(psi[j*nx+i+1]-psi[j*nx+i-1])/(2*dx);
                if (!advection) { u=0; v=0; }
                // upwind advection + central diffusion
                double dwdx = (u>0)? (om[j*nx+i]-om[j*nx+i-1])/dx : (om[j*nx+i+1]-om[j*nx+i])/dx;
                double dwdy = (v>0)? (om[j*nx+i]-om[(j-1)*nx+i])/dy : (om[(j+1)*nx+i]-om[j*nx+i])/dy;
                double lap = (om[j*nx+i+1]-2*om[j*nx+i]+om[j*nx+i-1])/(dx*dx)
                           + (om[(j+1)*nx+i]-2*om[j*nx+i]+om[(j-1)*nx+i])/(dy*dy);
                omn[j*nx+i] = om[j*nx+i] + dt*(-u*dwdx - v*dwdy + nu*lap);
            }
            // free-slip box: omega=0 on borders
            for (int i=0;i<nx;++i){ omn[i]=0; omn[(ny-1)*nx+i]=0; }
            for (int j=0;j<ny;++j){ omn[j*nx]=0; omn[j*nx+nx-1]=0; }
            om.swap(omn);
            if (n == steps/2) { xc_prev = centroid(om); t_prev = (n+1)*dt; }
        }
        double xc_end = centroid(om);
        Upair = (xc_end - xc_prev)/(steps*dt - t_prev);
        Upair_out = Upair;
        xc_travel = xc_end - xc0;
        // formation: opposite extrema
        double wmax=0, wmin=0;
        for (double v2 : om){ wmax=std::max(wmax,v2); wmin=std::min(wmin,v2); }
        ratio_pm = (wmax>0 && wmin<0)? std::fabs(wmax/std::fabs(wmin) - 1.0) : 9e9;
        // final psi for probes
        sor_poisson(psi, om, nx, ny, dx, dy, 400, false);
        // locate core x (vorticity-sq centroid), probe flank u and centre jet
        double xc = xc_end;
        int ic = std::min(nx-2, std::max(1, (int)(xc/dx)));
        flank_min_u = 1e9;
        for (int j=1;j<ny-1;++j){
            double y=(j+0.5)*dy, off=std::fabs(y-y0);
            if (off>=1.5*a && off<=3.0*a){
                for (int di=-8; di<=8; ++di){
                    int i = std::min(nx-2,std::max(1,ic+di));
                    double u = (psi[(j+1)*nx+i]-psi[(j-1)*nx+i])/(2*dy);
                    flank_min_u = std::min(flank_min_u, u);
                }
            }
        }
        int jc = std::min(ny-2, std::max(1,(int)(y0/dy)));
        double u_core = (psi[(jc+1)*nx+ic]-psi[(jc-1)*nx+ic])/(2*dy);
        jet_ratio = (Upair>1e-9)? u_core/Upair : 0.0;
    };

    double trav, rpm, flank, jet, Upair;
    run(true,  trav, rpm, flank, jet, Upair);
    double trav0, rpm0, flank0, jet0, Upair0;
    run(false, trav0, rpm0, flank0, jet0, Upair0);   // diffusion-only control

    printf("  pair extrema |w+|/|w-| dev      = %.3f   (gate <0.15)\n", rpm);
    printf("  centroid travel (advective)     = %.3f a  (gate >=1.0a)\n", trav/a);
    printf("  centroid travel (control)       = %.3f a  (gate <0.1a)\n", trav0/a);
    printf("  pair speed U_pair (late)        = %.3f U\n", Upair);
    printf("  flank min u (1.5a..3a off-axis) = %.3f U_pair (gate < -0.05)\n",
           (Upair>1e-9)? flank/Upair : 0.0);
    printf("  centre jet u_core/U_pair        = %.3f   (gate >= 1.3)\n", jet);
    bool g1a = rpm < 0.15;
    bool g1b = (trav/a >= 1.0) && (trav0/a < 0.1);
    bool g1c = (Upair>1e-9) && (flank/Upair < -0.05);
    bool g1d = jet >= 1.3;
    printf("  G1a formation %s | G1b self-propulsion %s | G1c roll-back %s | G1d closed cell %s\n",
           g1a?"PASS":"FAIL", g1b?"PASS":"FAIL", g1c?"PASS":"FAIL", g1d?"PASS":"FAIL");
    printf("  (P1 ceiling: consistency/convergence - Lamb-dipole physics is known;\n");
    printf("   what is banked: the relay lattice performs the operation natively.)\n");
}

// ============ PHASE 2: coherence-length selection in a channel ============
// ADJ-1 (instrument replacement, gates/conventions UNCHANGED): the v1
// random-seed grid instrument measured G=1.000 at every wavelength - an
// instrument failure (near-zero projection on tilted Orr structures; 1st-order
// upwind numerical diffusion ~ nu at small lambda). v1 output preserved in
// fd12_rerun_2026-07-26.txt; this v2 instrument is spectral single-mode in x
// (zero numerical diffusion) with an explicit tilt sweep (crude optimal-growth
// proxy). Committed T_obs, l_c convention, Re, lambda list, bands: unchanged.
#include <complex>
static void phase2() {
    printf("----------------------------------------------------------------\n");
    printf(" PHASE 2  DISCRIMINATOR: transient-gain wavelength selection\n");
    printf("          plane channel U(y)=U0(1-(2y/L)^2), Re=1000, no-slip\n");
    printf("          instrument v2 (ADJ-1): spectral mode + tilt sweep\n");
    printf("----------------------------------------------------------------\n");
    const double L = 1.0, U0 = 1.0, Re = 1000.0, nu = U0*L/Re;
    const double lam_list[] = {0.25, 0.5, 1.0, 2.0, 4.0, 8.0, 16.0};
    const double tilt_list[] = {0.0, 2.0, 4.0, 8.0, 12.0};   // ky0/kx, committed
    const double T_obs = 10.0*L/U0;               // committed observation window
    printf("  committed: T_obs=10 L/U0, l_c = lambda*/2, tilts {0,2,4,8,12}x(+/-)\n");
    printf("  lambda/L      gain G(lambda)   best tilt\n");
    using cd = std::complex<double>;
    const int ny = 257; const double dy = L/(ny-1);
    double best_g = -1, best_lam = 0; bool interior_max = false;
    std::vector<double> gains;
    for (double lam : lam_list) {
        const double kx = 2.0*PI2/lam;
        double Glam = 0.0, best_t = 0.0;
        for (double tmag : tilt_list) for (int sgn=-1; sgn<=1; sgn+=2) {
            if (tmag==0.0 && sgn==1) continue;    // tilt 0 once
            double ky0 = sgn*tmag*kx;
            std::vector<cd> om(ny), ps(ny), omn(ny);
            // windowed tilted wave in the lower shear half (Orr IC)
            for (int j=0;j<ny;++j){
                double y = -L/2 + j*dy;
                double w = std::exp(-std::pow((y+0.25*L)/(0.15*L),2)); // lower half window
                om[j] = w*std::exp(cd(0.0, ky0*y));
            }
            om[0]=om[ny-1]=cd(0,0);
            // helmholtz solve (d_yy - kx^2) ps = -om ; ps=0 walls (Thomas)
            auto solve_psi = [&](std::vector<cd>& psv, const std::vector<cd>& omv){
                std::vector<cd> a(ny), b(ny), cc(ny), d(ny);
                for (int j=1;j<ny-1;++j){ a[j]=cd(1.0/(dy*dy),0); cc[j]=a[j];
                    b[j]=cd(-2.0/(dy*dy)-kx*kx,0); d[j]=-omv[j]; }
                b[0]=b[ny-1]=cd(1,0); a[0]=cc[0]=a[ny-1]=cc[ny-1]=cd(0,0);
                d[0]=d[ny-1]=cd(0,0);
                for (int j=1;j<ny;++j){ cd m=a[j]/b[j-1]; b[j]-=m*cc[j-1]; d[j]-=m*d[j-1]; }
                psv[ny-1]=d[ny-1]/b[ny-1];
                for (int j=ny-2;j>=0;--j) psv[j]=(d[j]-cc[j]*psv[j+1])/b[j];
            };
            auto energy = [&](const std::vector<cd>& psv){
                double e=0;
                for (int j=1;j<ny-1;++j){
                    cd dpsi=(psv[j+1]-psv[j-1])/(2.0*dy);
                    e += std::norm(dpsi) + kx*kx*std::norm(psv[j]);
                }
                return e;
            };
            solve_psi(ps, om);
            double E0 = energy(ps); if (E0<=0) continue;
            double dt = std::min(0.4*dy*dy/nu, 0.2/(kx*U0));
            int steps = (int)(T_obs/dt);
            double Gm = 1.0;
            // ADJ-2: advection integrated EXACTLY via phase rotation
            // (explicit Euler is unconditionally unstable on -i kx U om;
            //  v2 first run showed the blowup at lambda=0.25 - artifact).
            for (int n=0;n<steps;++n){
                for (int j=1;j<ny-1;++j){
                    double y = -L/2 + j*dy;
                    double Upp = -8.0*U0/(L*L);
                    cd coup= cd(0,1.0)*kx*ps[j]*Upp;        //  i kx psi U''  (v'=i kx psi)
                    cd lap = (om[j+1]-2.0*om[j]+om[j-1])/(dy*dy) - kx*kx*om[j];
                    omn[j] = om[j] + dt*(coup + nu*lap);
                }
                for (int j=1;j<ny-1;++j){
                    double y = -L/2 + j*dy;
                    double Ub = U0*(1.0-4.0*y*y/(L*L));
                    omn[j] *= std::exp(cd(0.0, -kx*Ub*dt)); // exact advection phase
                }
                // no-slip: Thom
                omn[0]    = -2.0*ps[1]/(dy*dy);
                omn[ny-1] = -2.0*ps[ny-2]/(dy*dy);
                om.swap(omn);
                solve_psi(ps, om);
                if ((n & 3) == 0){ double e=energy(ps); if (e/E0>Gm) Gm=e/E0; }
            }
            if (Gm > Glam){ Glam = Gm; best_t = sgn*tmag; }
        }
        gains.push_back(Glam);
        printf("   %6.2f       %10.3f      %+.0f\n", lam/L, Glam, best_t);
        if (Glam > best_g) { best_g = Glam; best_lam = lam; }
    }
    // interior maximum?
    for (size_t k=1;k+1<gains.size();++k)
        if (gains[k] > gains[k-1] && gains[k] > gains[k+1]) interior_max = true;
    double lc = best_lam/2.0;
    double ratio = L/lc;
    double Re_crit = ratio*ratio;
    printf("  selected lambda* = %.2f L  ->  l_c = lambda*/2 = %.3f L\n", best_lam/L, lc/L);
    printf("  L/l_c = %.1f   ->  exported Re_crit = (L/l_c)^2 = %.0f\n", ratio, Re_crit);
    printf("  pipe back-solve target: L/l_c = 48 (Re_crit 2300)\n");
    bool strong = (ratio>=24 && ratio<=96);
    bool order  = (ratio>=10 && ratio<=200);
    if (!interior_max)
        printf("  G2 verdict: FAIL - no interior maximum: no finite roll selected (as committed)\n");
    else if (strong) printf("  G2 verdict: STRONG PASS (in [24,96])\n");
    else if (order)  printf("  G2 verdict: ORDER PASS (in [10,200]; geometry factor owed)\n");
    else             printf("  G2 verdict: FAIL (outside [10,200]) - identification dead as posed\n");
}

int main(){
    printf("================================================================\n");
    printf(" FD12 - The Poloidal Parcel Operation  (gates pre-committed)\n");
    printf(" Author: J. C. Harvey, Melbourne - direct run\n");
    printf("================================================================\n");
    phase1();
    phase2();
    printf("================================================================\n");
    printf(" grading in FD12_VERDICT_DIRECT (P1 capped at consistency;\n");
    printf(" P2 is the discriminator; no re-scoping after the numbers)\n");
    printf("================================================================\n");
    return 0;
}
