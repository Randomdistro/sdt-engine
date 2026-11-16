# Derives the seatKinds variant of the live engine (Release file is only read). Usage: python -I make_patch3.py <Release engine> <out>.
# options.seatKinds = array of 'd'/'t' over the seats of ONE full shell (construction order); the shell is the full D6-type shell with
# directions for n = seatKinds.length seats. Everything else (placement, contact rule, evaluate) is the live engine.
import sys
src, dst = sys.argv[1], sys.argv[2]
s = open(src, encoding='utf-8', newline='').read()
nl = '\r\n' if '\r\n' in s else '\n'
s = s.replace('\r\n', '\n')

def sub1(old, new):
    global s
    assert s.count(old) == 1, (s.count(old), old[:70])
    s = s.replace(old, new)

sub1("      const allocation = universalShellAllocation(g.nd, g.nt);\n      let moduleIndex = 0;",
     "      const allocation = options?.seatKinds\n        ? universalShellAllocation(g.nd + g.nt, 0)\n        : universalShellAllocation(g.nd, g.nt);\n      let moduleIndex = 0;")
sub1("          const direction = shell.directions[seatIndex];\n",
     "          const direction = shell.directions[seatIndex];\n          const seatKind = options?.seatKinds\n            ? (options.seatKinds[moduleIndex] === 't' ? 'triton' : 'deuteron')\n            : kind;\n")
sub1("          const placement = placeInterstitialModule(\n            builder,\n            kind,\n            direction,",
     "          const placement = placeInterstitialModule(\n            builder,\n            seatKind,\n            direction,")
sub1("          const module = {\n            kind,\n            index: moduleIndex,",
     "          const module = {\n            kind: seatKind,\n            index: moduleIndex,")
open(dst, 'w', encoding='utf-8', newline='').write(s.replace('\n', nl))
print('seatKinds variant ->', dst)
