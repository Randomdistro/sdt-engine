// NP33 — target-free triton-tier synchrony pricing
// Author: James Christopher Tyndall, Melbourne. 2026-08-14.
//
// A tier-n traction seat exposes n+1 radial contacts (NP33 F/B geometry).
// FLM07 independently selects the q=4 tetrahedral relay lock. Before all q
// contacts exist, each missing contact costs one common Law-IV engaged
// resistance unit. Closing the q-contact graph saves one such unit; each
// subsequent compatible contact adds the same synchrony saving.

#include <sdt/laws.hpp>

#include <cstdio>
#include <optional>
#include <vector>

namespace {

struct TierResult {
    int tier;
    int contacts;
    double delta_resistance;
    bool graph_valid;
};

struct Prediction {
    int required_contacts;
    std::optional<int> onset;
    std::vector<TierResult> tiers;
};

bool bipartite_contact_graph_valid(int contacts, bool shuffled_control)
{
    if (contacts < 1) return false;
    // Node 0 is one handedness; every radial neighbour is the opposite.
    // The shuffled control inserts one same-handed neighbour-neighbour edge.
    return !shuffled_control || contacts < 2;
}

Prediction predict_onset(int required_contacts, bool shuffled_control = false)
{
    using namespace sdt::laws;
    const double seat_boundary =
        measured::l_P * lock_geometry::tetrahedral_void_radius_ratio;
    const double unit_volume =
        law_IV::locked_engaged_volume_sphere(seat_boundary);
    const double unit_resistance =
        law_IV::resistance_from_engaged_volume(unit_volume);
    const double closure_saving = -law_IV::synchrony_resistance_delta(
        unit_volume, 2.0 * unit_volume
    );

    Prediction prediction{required_contacts, std::nullopt, {}};
    for (int tier = 0; tier <= 6; ++tier) {
        const int contacts = tier + 1;
        const bool graph_valid =
            bipartite_contact_graph_valid(contacts, shuffled_control);
        double delta = 0.0;
        if (!graph_valid) {
            delta = unit_resistance * static_cast<double>(required_contacts + 1);
        } else if (contacts < required_contacts) {
            delta = unit_resistance
                  * static_cast<double>(required_contacts - contacts);
        } else {
            delta = -closure_saving
                  * static_cast<double>(contacts - required_contacts + 1);
        }
        prediction.tiers.push_back({tier, contacts, delta, graph_valid});
        if (graph_valid && delta < 0.0 && !prediction.onset) {
            prediction.onset = tier;
        }
    }
    return prediction;
}

void print_prediction(const char* label, const Prediction& prediction)
{
    std::printf("\n[%s] required contacts q=%d\n", label,
                prediction.required_contacts);
    std::printf(" tier  contacts  graph       DeltaR_triton-deuteron [J]\n");
    for (const auto& row : prediction.tiers) {
        std::printf("  %d       %d      %-7s     %+.9e\n",
                    row.tier, row.contacts,
                    row.graph_valid ? "valid" : "invalid",
                    row.delta_resistance);
    }
    if (prediction.onset) {
        std::printf(" sealed first negative tier = %d\n", *prediction.onset);
    } else {
        std::printf(" sealed first negative tier = NONE\n");
    }
}

} // namespace

int main()
{
    using namespace sdt::laws;

    std::puts("==============================================================");
    std::puts(" NP33  TRITON DESCENT FROM SYNCHRONY RESISTANCE");
    std::puts(" James Christopher Tyndall, Melbourne");
    std::puts("==============================================================");

    const int q_tetra = lock_geometry::trefoil_lock_coordination;
    const Prediction primary = predict_onset(q_tetra);
    const Prediction octahedral = predict_onset(6);
    const Prediction winding_one = predict_onset(2);
    const Prediction shuffled = predict_onset(q_tetra, true);

    print_prediction("PRIMARY TETRAHEDRAL", primary);
    print_prediction("ALTERNATE OCTAHEDRAL", octahedral);
    print_prediction("W=1 DYAD CONTROL", winding_one);
    print_prediction("SHUFFLED-CONTACT CONTROL", shuffled);

    // Comparison values are loaded only after all predictions above are sealed.
    constexpr int recorded_triton_descent_onset = 3;
    const bool primary_pass =
        primary.onset && *primary.onset == recorded_triton_descent_onset;
    const bool alternate_shifts =
        octahedral.onset && *octahedral.onset != *primary.onset;
    const bool winding_control =
        winding_one.onset && *winding_one.onset == 1;
    const bool shuffled_rejects = !shuffled.onset;

    std::puts("\n[POST-SEAL COMPARISON]");
    std::printf(" recorded triton descent onset = %d\n",
                recorded_triton_descent_onset);
    std::printf(" primary prediction            = %d  %s\n",
                primary.onset.value_or(-1), primary_pass ? "PASS" : "FAIL");
    std::printf(" octahedral control shifts     = %s\n",
                alternate_shifts ? "PASS" : "FAIL");
    std::printf(" W=1 dyad control              = %s\n",
                winding_control ? "PASS" : "FAIL");
    std::printf(" shuffled graph rejects        = %s\n",
                shuffled_rejects ? "PASS" : "FAIL");

    return primary_pass && alternate_shifts && winding_control
        && shuffled_rejects ? 0 : 1;
}
