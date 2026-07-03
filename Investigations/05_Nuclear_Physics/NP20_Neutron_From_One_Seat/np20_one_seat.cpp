// ─────────────────────────────────────────────────────────────────────────
//  NP20 — The Neutron from One Seat
//  Does ONE seat geometry (electron driven onto the proton boundary at the
//  framework's already-fixed ~1.83c seat speed) GENERATE BOTH
//     (1) the 0.782 MeV free-decay surplus  (form-resistance step, NP19), and
//     (2) the -1.913 mu_N moment (sign AND magnitude, over-rotated negative)
//  with ZERO per-number knobs?
//
//  Author: J. C. Harvey, Melbourne.
//  Engine: #include <sdt/laws.hpp> only — no local constant namespaces.
//  Build : cl /std:c++20 /EHsc /O2 /I Engine\include np20_one_seat.cpp
//
//  STRESS DISCIPLINE: this tool is written to REPORT what the geometry does,
//  not to land the targets. It prints an explicit zero-knob ledger. If a
//  reader needs a per-number coefficient, that coefficient is printed and
//  tagged CALIBRATED(1) — it is NOT hidden inside the geometry.
// ─────────────────────────────────────────────────────────────────────────
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;

// ── ONE geometry, constructed once, passed const& to both readers ─────────
struct SeatGeometry {
    double R_p;        // seat radius  = proton boundary (displacement) radius [m]
    double v_seat;     // seat speed   = traction::v_phase_proton_surface     [m/s]
    int    sense;      // rotation sense of the seated electron: -1 = counter
    double z_seat;     // convergence depth z = (v/c)^2                        [-]
};

// helpers ------------------------------------------------------------------
static double MeV_of(double joules) { return joules / measured::MeV_to_J; }
static double m_e_c2_MeV() { return MeV_of(measured::m_e * measured::c * measured::c); }

// ── READER 1 — MASS (form-resistance step) → tries to make 0.782 MeV ──────
// NP19 reframe: resistance ~ how hard the medium grips the form at depth z.
// The frozen geometry offers ONLY these native dimensionless depth factors:
//   z_seat-1 = 2.349 , sqrt(z_seat)=1.830 , ln(z_seat)=1.209.
// The factor REQUIRED to reach 0.782 MeV from m_e c^2 is 0.782/0.511 = 1.531.
// NONE of the native factors equals 1.531 → any formula that lands 0.782
// must multiply by a per-number coefficient. We expose that coefficient.
struct MassRead {
    double pred_MeV;           // best native (no per-number knob) prediction
    double native_factor;      // the dimensionless depth factor used
    const char* factor_name;
    double required_factor;    // factor that WOULD land 0.782
    double calib_coeff;        // per-number coefficient needed = required/native  (CALIBRATED(1))
};
static MassRead read_mass(const SeatGeometry& s) {
    MassRead r{};
    // Native candidate chosen a priori (NOT fished): the "excess depth" (z-1),
    // the closest single-quantity NP19 resistance analogue, times m_e c^2.
    r.native_factor  = s.z_seat - 1.0;                 // = 2.349  (depth excess)
    r.factor_name    = "(z_seat - 1)";
    r.pred_MeV       = 0.5 * r.native_factor * m_e_c2_MeV(); // /2: two-body split, ASSUMED
    // required factor to hit the OBSERVED-TARGET surplus:
    const double surplus = MeV_of((measured::m_n - measured::m_p) * measured::c * measured::c)
                         - m_e_c2_MeV();               // 1.293 - 0.511 = 0.782 (subtraction rail)
    r.required_factor = surplus / m_e_c2_MeV();         // 1.531
    r.calib_coeff     = r.required_factor / (0.5 * r.native_factor); // knob needed on top of native
    return r;
}

// ── READER 2 — MOMENT (composite flux) → tries to make -1.913 mu_N ────────
// Proton carries handed flux mu_P = +2.793 mu_N. A bare electron moment is
// m_p/m_e = 1836 mu_N (mu_B in mu_N units). To turn +2.793 into -1.913 the
// seated (counter, sense=-1) electron must contribute -4.706 mu_N. The gearing
// factor required is -4.706/1836 = -0.002563. That is NOT alpha (0.00730), NOT
// k_ps^2 (0.2986), NOT any clean whitelist combination → a per-number knob.
struct MomentRead {
    double mu_electron_muN;    // bare electron moment in mu_N units = m_p/m_e
    double required_incr;      // increment needed on mu_P to reach mu_N target
    double required_gearing;   // required_incr / mu_electron  (CALIBRATED(1))
    double pred_muN;           // composite moment using the required gearing (identity — for display)
    int    sign;               // sign of the composite (must be negative to survive T1)
};
static MomentRead read_moment(const SeatGeometry& s) {
    MomentRead r{};
    r.mu_electron_muN = measured::m_p / measured::m_e;             // 1836.15 (mu_B/mu_N)
    r.required_incr   = measured::mu_N - measured::mu_P;           // -4.706 mu_N
    r.required_gearing= r.required_incr / r.mu_electron_muN;       // -0.002563 (needs a knob)
    // Compose with the seated (counter) electron. sense enters as the sign of the
    // increment; magnitude REQUIRES the gearing knob → identity read-out, not a prediction.
    const double flux_seat = s.sense * std::fabs(r.required_gearing) * r.mu_electron_muN; // = required_incr
    r.pred_muN = measured::mu_P + flux_seat;
    r.sign = (r.pred_muN < 0.0) ? -1 : +1;
    return r;
}

int main() {
    std::printf("================================================================\n");
    std::printf(" NP20 — The Neutron from One Seat  (execute)\n");
    std::printf(" ONE geometry, two readers, zero-knob ledger.\n");
    std::printf("================================================================\n\n");

    // ── PHASE 1 — declare & freeze the single geometry ────────────────────
    SeatGeometry seat{
        measured::R_p,                         // MEASURED-INPUT
        law_VI::traction::v_phase_proton_surface, // DERIVED (c / k_proton_surface)
        -1,                                    // ASSUMED sign convention: counter-rotating
        0.0
    };
    seat.z_seat = depth_closure::depth_from_v(seat.v_seat);  // DERIVED z=(v/c)^2

    // P1 reconciliation: traction value vs depth-closure v_bound at R_p.
    // koppa at the seat = r_e (hydrogen c-boundary koppa = alpha^2 a_0 = r_e).
    const double v_bound_Rp = depth_closure::v_bound(measured::r_e, measured::R_p);
    const double p1_agree_pct =
        std::fabs(seat.v_seat - v_bound_Rp) / seat.v_seat * 100.0;

    std::printf("PHASE 1 — FROZEN SEAT GEOMETRY (declared before any number)\n");
    std::printf("  R_p     = %.4e m            [MEASURED-INPUT]  proton BOUNDARY radius (not 'charge')\n", seat.R_p);
    std::printf("  v_seat  = %.6f c            [DERIVED]         = c / k_proton_surface (traction/PPT06)\n", seat.v_seat/measured::c);
    std::printf("  v_bound = %.6f c            [DERIVED]         = c*sqrt(r_e/R_p) (depth-closure v=c*sqrt(z))\n", v_bound_Rp/measured::c);
    std::printf("  agree   = %.4f%%  (gate <1%%)  -> %s\n", p1_agree_pct, (p1_agree_pct<1.0?"PASS-GATE":"FAIL"));
    std::printf("  z_seat  = %.4f                [DERIVED]         = (v_seat/c)^2  (v>c depth-closure regime, NOT SR gamma)\n", seat.z_seat);
    std::printf("  sense   = %+d (counter)         [ASSUMED]         sign convention; makes moment increment negative\n\n", seat.sense);

    // ── OBSERVED TARGETS (anchors — measured NUMBERS, not SM story) ───────
    const double surplus_target = MeV_of((measured::m_n - measured::m_p)*measured::c*measured::c) - m_e_c2_MeV();
    std::printf("OBSERVED-TARGETS (measured anchors):\n");
    std::printf("  n-p gap      = %.4f MeV       [OBSERVED-TARGET]  (m_n - m_p)c^2\n", MeV_of((measured::m_n-measured::m_p)*measured::c*measured::c));
    std::printf("  m_e c^2      = %.4f MeV       [OBSERVED-TARGET]  electron rest budget\n", m_e_c2_MeV());
    std::printf("  decay surplus= %.4f MeV       [OBSERVED-TARGET]  gap - m_e c^2 (subtraction rail)\n", surplus_target);
    std::printf("  mu_N         = %+.5f mu_N     [OBSERVED-TARGET]  neutron moment (mu_N = BORROWED unit)\n", measured::mu_N);
    std::printf("  mu_P         = %+.5f mu_N     [OBSERVED-TARGET]  proton moment (mu_N = BORROWED unit)\n\n", measured::mu_P);

    // ── PHASE 2 — MASS reader on the frozen geometry ──────────────────────
    MassRead m = read_mass(seat);
    const double m_err = (m.pred_MeV - surplus_target)/surplus_target*100.0;
    std::printf("PHASE 2 — MASS reader (form-resistance step, NP19)\n");
    std::printf("  native factor  = %-12s = %.4f   [DERIVED]  depth factors offered: (z-1)=%.3f, sqrt(z)=%.3f, ln(z)=%.3f\n",
                m.factor_name, m.native_factor, seat.z_seat-1.0, std::sqrt(seat.z_seat), std::log(seat.z_seat));
    std::printf("  native pred    = %.4f MeV     [COMPUTED]  0.5*(z-1)*m_e c^2  (0.5 two-body split ASSUMED)\n", m.pred_MeV);
    std::printf("  vs 0.782 MeV   = %+.1f%%        (gate <=15%%)  -> %s\n", m_err, (std::fabs(m_err)<=15.0?"PASS":"MISS"));
    std::printf("  required factor= %.4f          [OBSERVED-TARGET]  0.782/0.511 — geometry does NOT emit this\n", m.required_factor);
    std::printf("  KNOB NEEDED    = x%.4f         [CALIBRATED(1)]  coeff to force native->0.782  => per-number knob\n\n", m.calib_coeff);

    // ── PHASE 3 — MOMENT reader on the SAME frozen geometry ───────────────
    MomentRead q = read_moment(seat);
    const double q_err = (std::fabs(q.pred_muN) - std::fabs(measured::mu_N))/std::fabs(measured::mu_N)*100.0;
    std::printf("PHASE 3 — MOMENT reader (composite flux, SAME geometry)\n");
    std::printf("  mu_electron    = %.2f mu_N     [DERIVED]  m_p/m_e (bare electron moment in borrowed mu_N)\n", q.mu_electron_muN);
    std::printf("  required incr  = %+.4f mu_N    [OBSERVED-TARGET]  mu_N - mu_P (what the seat must add)\n", q.required_incr);
    std::printf("  required gearing = %+.6f       [OBSERVED-TARGET]  incr/mu_e ; alpha=%.5f k_ps^2=%.4f — matches NEITHER\n",
                q.required_gearing, measured::alpha, bridge::k_proton_surface*bridge::k_proton_surface);
    std::printf("  composite mu   = %+.5f mu_N    [IDENTITY]  uses required gearing => re-expression, not prediction\n", q.pred_muN);
    std::printf("  SIGN           = %s              (T1 hard gate: must be NEGATIVE) -> %s\n",
                (q.sign<0?"NEGATIVE":"POSITIVE"), (q.sign<0?"survives-sign":"KILL"));
    std::printf("  NOTE: sign is CARRIED by sense=-1 (assumed), magnitude needs a KNOB -> not a native prediction.\n\n");

    // ── PHASE 4 — one-geometry / zero-knob ledger (the actual test) ───────
    std::printf("PHASE 4 — ZERO-KNOB LEDGER (the closure test)\n");
    std::printf("  shared geometry consumed by BOTH: {R_p, v_seat, z_seat, sense}  [whitelist/derived]\n");
    std::printf("  per-number knob used by MASS only  : x%.4f  (CALIBRATED(1))\n", m.calib_coeff);
    std::printf("  per-number knob used by MOMENT only: gearing %+.6f  (CALIBRATED(1))\n", q.required_gearing);
    std::printf("  knob count beyond shared geometry  : 2   (committed pass = 0)\n");
    std::printf("  --> CLOSURE VERDICT: FALSE. Each number needs its OWN per-number coefficient.\n");
    std::printf("      The geometry BRACKETS both targets but PREDICTS neither (FLM12-D1 precedent: UNPAID).\n\n");

    // ── results table (machine) ───────────────────────────────────────────
    std::printf("RESULTS TABLE  [quantity | SDT native | anchor | %%err | sign | label]\n");
    std::printf("  v_seat reconcile | %.5fc | %.5fc(v_bound) | %.4f%% | + | DERIVED(PASS)\n",
                seat.v_seat/measured::c, v_bound_Rp/measured::c, p1_agree_pct);
    std::printf("  mass surplus     | %.4f MeV | %.4f MeV | %+.1f%% | + | COMPUTED(MISS, knob x%.3f)\n",
                m.pred_MeV, surplus_target, m_err, m.calib_coeff);
    std::printf("  neutron moment   | %+.5f | %+.5f | %+.1f%% | %s | IDENTITY(knob gearing)\n",
                q.pred_muN, measured::mu_N, q_err, (q.sign<0?"NEG":"POS"));
    std::printf("\n  ONE genuine non-circular result: v_seat == v_bound to %.4f%% (P1).\n", p1_agree_pct);
    std::printf("  Neither physical number is generated knob-free. Closure NOT paid.\n");
    return 0;
}
