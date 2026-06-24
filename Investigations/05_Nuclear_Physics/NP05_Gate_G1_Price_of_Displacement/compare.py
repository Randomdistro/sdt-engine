"""CQ-32 compare.py — the ONLY code permitted to read sealed/answers.json (R1).
Usage: python compare.py volumes.json
  volumes.json : {"candidate_name": {"R1_dd_to_a": dV_fm3, ...}, ...}
                 dV = (sum V_disp products) - (sum V_disp reactants), in fm^3 (signed).
Emits the price matrix P_i = Q_i / (-dV_i)  [MeV/fm^3]  and the Gate G1 verdict
(PASS if max/min of the 8 prices <= 1.35), plus Gate G1-M context."""
import json, sys, math, os

HERE = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(HERE, "sealed", "answers.json")) as f:
    ANS = json.load(f)
Q = ANS["Q_values_MeV"]

# Law-I reference prices (Stage-0 ledger; see RUN_LOG unit finding)
P_CONV_Pa = 2.459e48
J_per_MeV = 1.602176634e-13
P_CONV_MeV_fm3 = P_CONV_Pa / J_per_MeV / 1e45          # = 1.535e16 (NOT 15.35)

def verdict(prices):
    vals = [p for p in prices.values() if p is not None and p > 0]
    if len(vals) < len(prices):
        return "INCOMPLETE (non-positive or missing dV)"
    spread = max(vals) / min(vals)
    return f"mean={sum(vals)/len(vals):.4g} MeV/fm^3  spread(max/min)={spread:.3f}  " + \
           ("PASS" if spread <= 1.35 else "FAIL")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("usage: python compare.py volumes.json"); sys.exit(1)
    with open(sys.argv[1]) as f:
        cands = json.load(f)
    for name, dV in cands.items():
        print(f"\n=== candidate {name} ===")
        prices = {}
        for rk, q in Q.items():
            d = dV.get(rk)
            prices[rk] = (q / (-d)) if (d not in (None, 0)) else None
            print(f"  {rk:16s} Q={q:8.4f} MeV  dV={d}  P={prices[rk]}")
        print("  G1:", verdict(prices))
    print(f"\n[ref] P_conv = {P_CONV_MeV_fm3:.4e} MeV/fm^3 (Planck); G1-M compares the nuclear "
          f"mean to this — note the 10^15 scale gap logged in RUN_LOG.")
