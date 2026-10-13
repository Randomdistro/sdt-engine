// ═══════════════════════════════════════════════════════════════════════
//  PM07 — Magnetohydrodynamics Coupling to the Fluid Suite
//  Author: J. C. Harvey, Melbourne · 2026-07-05 · pre-commits: RUN_LOG.md
//
//  FIREWALL: no primitive B (advected objects are PM01 wake quanta kappa);
//  no Ohm's-law postulate (slip = FD02 diffusion kicks); no magnetons; the
//  MHD set is a TARGET. The counting sim is real dynamics (RK4, evolved).
//
//  P2 core claim (the earnable theorem): FROZEN-IN FLUX IS A COUNTING
//  STATEMENT. Phi = (number of wake quanta enclosed by a material loop).
//  Both quanta and loop ride the same flow => the enclosed count cannot
//  change (topology of enclosure is advection-invariant). Finite FD02
//  diffusion lets quanta random-walk across the loop => Fick leak ∝ eta.
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>
#include <random>

static constexpr double PI = 3.14159265358979323846;

// smooth incompressible 2-D flow from a streamfunction (3 stirring cells)
static void flow(double x, double y, double& vx, double& vy) {
    struct Cell { double A, cx, cy, s2; };
    static const Cell C[3] = { {0.8, 0.5, 0.3, 0.36}, {-0.6, -0.6, -0.4, 0.25}, {0.5, 0.0, 0.9, 0.49} };
    vx = 0; vy = 0;
    for (const auto& c : C) {
        const double dx = x - c.cx, dy = y - c.cy;
        const double e = c.A * std::exp(-(dx*dx + dy*dy)/(2.0*c.s2));
        // v = (d psi/dy, -d psi/dx), psi = gaussian
        vx += e * (-dy/c.s2);
        vy -= e * (-dx/c.s2);
    }
}

static void rk4(double& x, double& y, double dt) {
    double k1x,k1y,k2x,k2y,k3x,k3y,k4x,k4y;
    flow(x,y,k1x,k1y);
    flow(x+0.5*dt*k1x, y+0.5*dt*k1y, k2x,k2y);
    flow(x+0.5*dt*k2x, y+0.5*dt*k2y, k3x,k3y);
    flow(x+dt*k3x, y+dt*k3y, k4x,k4y);
    x += dt*(k1x+2*k2x+2*k3x+k4x)/6.0;
    y += dt*(k1y+2*k2y+2*k3y+k4y)/6.0;
}

// point-in-polygon (ray casting)
static bool inside(double px, double py, const std::vector<double>& lx, const std::vector<double>& ly) {
    bool in = false; const size_t M = lx.size();
    for (size_t i = 0, j = M-1; i < M; j = i++) {
        if (((ly[i] > py) != (ly[j] > py)) &&
            (px < (lx[j]-lx[i]) * (py-ly[i]) / (ly[j]-ly[i]) + lx[i])) in = !in;
    }
    return in;
}

int main() {
    std::printf("PM07 — MHD Coupling to the Fluid Suite (J. C. Harvey, 2026-07-05)\n\n");

    // ═══ P1 — the coupling map (bijection gate; orphans NAMED) ══════════
    std::printf("P1  TERM-BY-TERM COUPLING MAP (ideal MHD <-> FD/PM primitives)\n");
    std::printf("    momentum:  dv/dt + v.grad v   <-> FD01 held-content transport      [FD01, class C]\n");
    std::printf("               -grad P / rho      <-> FD01 relay count gradient        [FD01, class C]\n");
    std::printf("               nu laplacian v     <-> FD01/FD02 relay Laplacian        [FD01/FD02, C]\n");
    std::printf("               (curl B) x B / mu0 <-> swirl back-traction on the flow  [ORPHAN-1: the\n");
    std::printf("                 swirl<->momentum coupling GAIN is HG-1 (PM01) — term named, not earned]\n");
    std::printf("    induction: dB/dt = curl(v x B)<-> wake quanta advect with carriers [PM07 P2 BELOW —\n");
    std::printf("                 counting theorem, no Ohm postulate]\n");
    std::printf("               + eta laplacian B  <-> FD02 relay diffusion             [ORPHAN-2: eta==FD02\n");
    std::printf("                 is an IDENTIFICATION (named), its magnitude not derived here]\n");
    std::printf("    solenoidal: div B = 0         <-> B == curl w (PM01 P2c identity)  [E58 theorem]\n");
    std::printf("    ORPHAN-3 (perp closure): see P3/P4 — wake isotropic pressure must equal FULL energy\n");
    std::printf("    density for the Maxwell perp stress; FD05 radiation gives u/3. Mismatch owned.\n");
    std::printf("    Zero silent leftovers; three orphans NAMED. Bijection NOT clean -> Class C by gate.\n\n");

    // ═══ P2 — frozen-in flux as a counting theorem (real dynamics) ══════
    {
        const int NC = 10000, NM = 512;
        const double T = 1.0, dt = 2.5e-3; const int NS = int(T/dt);
        std::mt19937 rng(19);
        std::normal_distribution<double> G01(0.0, 1.0);
        std::uniform_real_distribution<double> U01(0.0, 1.0);

        auto make_carriers = [&](std::vector<double>& cx, std::vector<double>& cy, std::mt19937& r) {
            cx.resize(NC); cy.resize(NC);
            std::normal_distribution<double> g(0.0, 0.7);      // Gaussian blob, sigma=0.7
            for (int i = 0; i < NC; ++i) { cx[i] = g(r); cy[i] = g(r); }
        };
        auto make_loop = [&](std::vector<double>& lx, std::vector<double>& ly) {
            lx.resize(NM); ly.resize(NM);
            for (int i = 0; i < NM; ++i) { lx[i] = std::cos(2*PI*i/NM); ly[i] = std::sin(2*PI*i/NM); }
        };
        auto count = [&](const std::vector<double>& cx, const std::vector<double>& cy,
                         const std::vector<double>& lx, const std::vector<double>& ly) {
            int n = 0;
            for (int i = 0; i < NC; ++i) if (inside(cx[i], cy[i], lx, ly)) ++n;
            return n;
        };

        // η = 0: advective control — count must not change (checked 20x during run)
        {
            std::vector<double> cx, cy, lx, ly;
            std::mt19937 r0(19); make_carriers(cx, cy, r0); make_loop(lx, ly);
            const int N0 = count(cx, cy, lx, ly);
            int worst = 0;
            for (int s = 0; s < NS; ++s) {
                for (int i = 0; i < NC; ++i) rk4(cx[i], cy[i], dt);
                for (int i = 0; i < NM; ++i) rk4(lx[i], ly[i], dt);
                if (s % (NS/20) == 0) worst = std::max(worst, std::abs(count(cx,cy,lx,ly) - N0));
            }
            const int NT = count(cx, cy, lx, ly);
            std::printf("P2  eta=0 control: N_enc start %d, end %d, worst excursion %d  (gate <=0.5%% = %d) -> %s\n",
                        N0, NT, worst, N0/200, (std::abs(NT-N0) <= N0/200 ? "PASS" : "FAIL"));
            std::printf("P2  frozen-in = COUNTING THEOREM: loop and quanta ride one flow; enclosure is\n");
            std::printf("    advection-invariant. Kelvin/induction equation with NO Ohm postulate. NATIVE.\n");
        }

        // η > 0: Fick leak ∝ eta
        std::printf("P2  finite FD02 diffusion (carriers kicked, loop advective):\n");
        std::vector<double> leta, lleak;
        for (double eta : {3e-4, 1e-3, 3e-3, 1e-2}) {
            double dmean = 0; const int ENS = 12;
            for (int e = 0; e < ENS; ++e) {
                std::mt19937 re(100 + e);
                std::vector<double> cx, cy, lx, ly;
                make_carriers(cx, cy, re); make_loop(lx, ly);
                const int N0 = count(cx, cy, lx, ly);
                const double kick = std::sqrt(2.0*eta*dt);
                for (int s = 0; s < NS; ++s) {
                    for (int i = 0; i < NC; ++i) {
                        rk4(cx[i], cy[i], dt);
                        cx[i] += kick*G01(re); cy[i] += kick*G01(re);
                    }
                    for (int i = 0; i < NM; ++i) rk4(lx[i], ly[i], dt);
                }
                dmean += double(N0 - count(cx, cy, lx, ly));   // leak = quanta lost from loop
            }
            dmean /= 12.0;
            std::printf("      eta=%.0e : ensemble-mean leak over T=1  = %+.2f quanta\n", eta, dmean);
            if (dmean > 0) { leta.push_back(std::log(eta)); lleak.push_back(std::log(dmean)); }
        }
        double sx=0,sy=0,sxx=0,sxy=0; const int n=(int)leta.size();
        for (int i=0;i<n;++i){sx+=leta[i];sy+=lleak[i];sxx+=leta[i]*leta[i];sxy+=leta[i]*lleak[i];}
        std::printf("P2  leak-vs-eta log-log slope = %.3f  (gate 1.0 +/- 0.3; Fick flux = -eta grad n)\n\n",
                    (n*sxy-sx*sy)/(n*sxx-sx*sx));
    }

    // ═══ P3/P4 — Alfvén assembly + stress projection (analytic) ═════════
    {
        std::printf("P3  ASSEMBLY (form only, no numeric claim): transverse kink of a swirl bundle:\n");
        std::printf("    restoring = swirl-stream momentum flux (tension) T_par = rho_a <u_w^2>\n");
        std::printf("    inertia   = bulk lattice density rho  =>  v_A = sqrt(T_par/rho) = u_w sqrt(rho_a/rho)\n");
        std::printf("    SI map [IMPORTED, final line only]: with rho_a u_w^2 <-> B^2/mu0: v_A = B/sqrt(mu0 rho).\n");
        std::printf("    The conversion rho_a u_w^2 <-> B^2/mu0 is HG-1-adjacent (ORPHAN-1) — NOT earned.\n");
        std::printf("P3/P4  STRUCTURAL CHECK (dimensionless, arithmetic — flagged, not a discovery):\n");
        const double tension_over_energy_maxwell = (1.0) / (0.5);   // (B^2/mu0) / (B^2/2mu0)
        const double tension_over_energy_stream  = (1.0) / (0.5);   // (rho u^2) / (rho u^2 / 2)
        std::printf("    Maxwell: tension/energy-density = %.1f ; directed relay stream: %.1f  -> MATCH (2:1)\n",
                    tension_over_energy_maxwell, tension_over_energy_stream);
        std::printf("P4  PERP CLOSURE — THE HONEST MISMATCH (ORPHAN-3): Maxwell perp pressure = +B^2/2mu0\n");
        std::printf("    = full energy density (w=+1 stiff). A cold directed stream gives 0; FD05 radiation\n");
        std::printf("    gives u/3. The wake medium must supply isotropic pressure EQUAL to its energy\n");
        std::printf("    density for the Maxwell stress to be relay traction. Not derived. OWNED as open.\n");
        std::printf("    (Candidate: CR05 gamma_eff = 4 stiff-lattice line — logged, untested.)\n");
        std::printf("P4  magnetosonic handshake (assembled): fast mode ~ sqrt(v_A^2 + c_s^2), c_s <= c/sqrt(3)\n");
        std::printf("    (FD05 ceiling); one dispersion surface omega(k,theta) is the PM03-rebuild's job.\n");
    }

    std::printf("\nPM07 done. Verdict: PM07_VERDICT.md\n");
    return 0;
}
