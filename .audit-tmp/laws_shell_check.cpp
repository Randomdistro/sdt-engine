#include <sdt/laws.hpp>
#include <cstdio>
int main(){
  using namespace sdt::laws::nuclear;
  static_assert(triton_shell_capacity(3)==8);
  static_assert(closure(3)==28);
  std::printf("B38 symbols OK: T8=%d pairs0=%d N184=%d\n",
    triton_shell_capacity(3), triton_shell_pairs[0],
    126+surface_remainder(6)+triton_shell_capacity(7));
  return 0;
}
