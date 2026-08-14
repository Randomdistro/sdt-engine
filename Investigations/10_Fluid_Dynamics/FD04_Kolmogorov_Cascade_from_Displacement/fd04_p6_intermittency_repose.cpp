// FD04-P6 - Intermittency as the bath's refusal fraction (Harvey 2026-07-26)
// Chain committed in PROMPT.md P6 BEFORE this file: torus = wrapped poloidal
// roll (1:4 gearing => R=4r, lambda=4); handoff drag-mediated, bath-limited;
// leak per generation = the lattice's icosahedral frustration gap g=0.103.
// beta-model closure: 3-D = ln(1/(1-g))/ln(lambda); slope = -5/3 - (3-D)/3.
// ZERO fitted parameters. Author: J. C. Harvey, Melbourne. Direct run.
#include <cstdio>
#include <cmath>
#include <numbers>

int main(){
    printf("================================================================\n");
    printf(" FD04-P6  intermittency = the bath's refusal fraction\n");
    printf(" (aspect from the wrap; leak from the lattice; nothing fitted)\n");
    printf("================================================================\n");

    // --- the frustration gap, computed from scratch (icosa 12-around-1) ---
    double sqrt5 = sqrt(5.0);
    double aR = 4.0/sqrt(10.0+2.0*sqrt5);       // icosahedron edge/circumradius
    double edge_gap = aR - 1.0;                 // unit spheres touching centre
    printf("\n icosahedral 12-around-1 (unit spheres touching the centre):\n");
    printf("   edge/circumradius a/R = %.5f -> single-pair linear gap = %.5f\n", aR, edge_gap);
    printf("   canon frustration gap g = 0.103 (lattice-fork canon; = 2 x %.4f = %.4f)\n",
           edge_gap, 2.0*edge_gap);

    // --- committed chain ---
    const double g_primary   = 0.103;   // canon (PRIMARY, committed)
    const double lam_primary = 4.0;     // wrap ratio R=4r (PRIMARY, committed)
    auto chain = [&](double g, double lam, const char* tag){
        double codim = log(1.0/(1.0-g))/log(lam);   // 3 - D
        double mu    = codim/3.0;                    // slope correction
        double slope = -5.0/3.0 - mu;
        printf("   %-28s beta=%.4f lam=%.0f : 3-D=%.5f  mu=%.5f  slope=%.5f\n",
               tag, 1.0-g, lam, codim, mu, slope);
        return mu;
    };

    printf("\n PRIMARY (committed):\n");
    double mu = chain(g_primary, lam_primary, "g=0.103 (canon), lam=4");
    printf("\n sensitivities (reported only, per pre-commit):\n");
    chain(g_primary, 5.0,      "g=0.103, lam=5 (extent conv.)");
    chain(2.0*edge_gap, 4.0,   "g=2x edge gap computed");
    chain(edge_gap, 4.0,       "g=single-pair gap 0.0515");
    printf("\n dead branch (rule (a), tube-in-influence-sphere) printed as committed:\n");
    {
        double rho=0.25;
        double f = (3.0 * std::numbers::pi / 2.0) * rho * rho / pow(1.0 + rho, 3.0);
        double codim = log(1.0/f)/log(5.0);
        printf("   f=%.4f  ->  3-D=%.4f  slope=%.3f   [DEAD vs measured -1.71 - as pre-computed]\n",
               f, codim, -5.0/3.0-codim/3.0);
    }

    // --- G6 gate ---
    printf("\n G6 (primary gate): mu_pred = %.5f ; committed band [0.01, 0.10]\n", mu);
    bool pass = (mu>=0.01 && mu<=0.10);
    double slope_pred = -5.0/3.0 - mu;
    printf("   predicted slope = %.5f ; measured anomaly mu ~ 0.03-0.05 (slope ~ -1.70/-1.71)\n",
           slope_pred);
    printf("   distance from measured centre (mu=0.04): factor %.2f UNDER (reported, not absorbed)\n",
           0.04/mu);
    printf("   G6 verdict: %s\n", pass? "PASS (in committed band)":"FAIL (recorded; no rescue)");

    // --- secondary: structure functions (report, not gate) ---
    printf("\n SECONDARY (report only): beta-model zeta_p = p/3 + (3-D)(1-p/3), 3-D=%.5f\n", 3.0*mu);
    double codim = 3.0*mu;
    double z2 = 2.0/3.0 + codim*(1.0-2.0/3.0);
    double z4 = 4.0/3.0 + codim*(1.0-4.0/3.0);
    double z6 = 2.0     + codim*(1.0-2.0);
    printf("   zeta_2 = %.4f  (measured ~0.70-0.71)\n", z2);
    printf("   zeta_4 = %.4f  (measured ~1.28)\n", z4);
    printf("   zeta_6 = %.4f  (measured ~1.78)  <- single-leak model's KNOWN high-order\n", z6);
    printf("      shortfall, printed as committed: one fixed leak under-corrects p>=6;\n");
    printf("      if the refusal COMPOUNDS (frustrated routes, not volume), higher orders\n");
    printf("      steepen - that refinement needs its own pre-commit, not a patch here.\n");

    printf("\n================================================================\n");
    printf(" chain: aspect R=4r from the 1:4 gearing (wrap) ; leak g=0.103 from\n");
    printf(" the lattice's own packing shortfall ; per generation because every\n");
    printf(" generation re-negotiates with the SAME scale-free medium (the bath\n");
    printf(" allows only the freedoms oppositional drag can instil). Rival\n");
    printf(" account: fitted multifractal spectrum. Here: nothing fitted.\n");
    printf("================================================================\n");
    return 0;
}
