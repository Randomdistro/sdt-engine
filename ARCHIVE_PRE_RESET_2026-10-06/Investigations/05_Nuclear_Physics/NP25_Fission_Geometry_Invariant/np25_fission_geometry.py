"""NP25: algebraic constraints on any binary ATOMICUS fission geometry.

No yield fitting and no assumed uranium positional ordering.  The program checks
the grammar receipts for complementary primary fragments before and after prompt
neutron emission.
"""


def grammar(z: int, a: int) -> tuple[int, int]:
    return 3 * z - a - 2, a - 2 * z  # n_d, n_t


def check_pair(parent_z: int, parent_a: int, left_z: int, left_a: int,
               right_z: int, right_a: int, prompt_n: int = 0) -> None:
    pd, pt = grammar(parent_z, parent_a)
    ld, lt = grammar(left_z, left_a)
    rd, rt = grammar(right_z, right_a)
    assert left_z + right_z == parent_z
    assert left_a + right_a + prompt_n == parent_a
    print(
        f"({left_a},{left_z}) + ({right_a},{right_z}) + {prompt_n}n: "
        f"sum_dt=({ld + rd},{lt + rt}); "
        f"receipt d=({ld + rd - pd:+d}), t=({lt + rt - pt:+d})"
    )
    assert ld + rd == pd + prompt_n - 2
    assert lt + rt == pt - prompt_n


if __name__ == "__main__":
    print("NP25 -- binary-fission grammar invariant")
    print("Receipt required for two alpha-cored daughters:")
    print("  before prompt n: 2d -> alpha; delta(n_d,n_t)=(-2,0)")
    print("  with nu prompt n: delta(n_d,n_t)=(nu-2,-nu)")

    # U-236 compound nucleus (thermal-neutron capture on U-235).
    # Representative charge-conserving complementary partitions; these are
    # algebra checks, not claimed yield maxima.
    check_pair(92, 236, 36, 96, 56, 140, 0)
    check_pair(92, 236, 38, 98, 54, 138, 0)
    check_pair(92, 236, 40, 100, 52, 136, 0)

    # Same pre-neutron split after variable prompt-neutron stripping, assigned
    # here one per fragment merely to test the receipt.
    check_pair(92, 236, 36, 95, 56, 139, 2)
    print("All conservation and grammar receipts pass.")
