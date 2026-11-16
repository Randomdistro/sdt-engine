"""Chapter 5 -- operator/law/theorem map. Pre-registration: Textbook/validation/ch05_PRE_REGISTRATION.md.

Reads Theory/00_Ruleset.md, Engine/include/sdt/laws.hpp and Laws/SDT_Complete_Laws.md and reports their structure.
Run: bash Textbook/tools/py_run.sh ch05_operator_law_map
"""
import os
import re
import sys

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
failures = 0


def read(rel):
    with open(os.path.join(ROOT, rel), encoding="utf-8") as fh:
        return fh.read()


def check(cid, what, ok):
    global failures
    if not ok:
        failures += 1
    print(f"[{'PASS' if ok else 'FAIL'}] {cid:<3} {what}")


TOKEN = re.compile(r"(?<![A-Za-z0-9_])T(\d{1,2})(?![A-Za-z0-9_])")
RANGE = re.compile(r"Theorems?\s+T(\d+)(?:\s*[–\-]\s*T?(\d+))?")


def tokens(text):
    return [int(m.group(1)) for m in TOKEN.finditer(text)]


def ranges(text):
    out = []
    for m in RANGE.finditer(text):
        a = int(m.group(1))
        b = int(m.group(2)) if m.group(2) else a
        out.append((a, b))
    return out


print("== V1, V2 scanner validation ==")
check("V1", "token scanner on the fixed test string",
      tokens("T1/T10 x T_CMB y NT2 T18, T3-T4 T5–T7") == [1, 10, 18, 3, 4, 5, 7])
check("V2", "range parser on three forms",
      [ranges("(Theorems T10–T17)")[0], ranges("(Theorems T1-T2)")[0], ranges("Theorem T18")[0]]
      == [(10, 17), (1, 2), (18, 18)])

rules = read("Theory/00_Ruleset.md")
laws = read("Engine/include/sdt/laws.hpp")
complete = read("Laws/SDT_Complete_Laws.md")
laws_lines = laws.split("\n")

operators = re.findall(r"^### \((\d)\) (.+)$", rules, re.M)
axioms = re.findall(r"^\| (R\d|M\d) \| ([^|]+) \|", rules, re.M)
theorems = re.findall(r"^\| (T\d+) \| ([^|]+) \| ([^|]+) \|", rules, re.M)

print("\n== C1 Ruleset structure ==")
check("C1", f"6 operators (found {len(operators)})", len(operators) == 6)
check("C1", f"9 axioms R1-R6, M1-M3 (found {[a[0] for a in axioms]})",
      [a[0] for a in axioms] == ["R1", "R2", "R3", "R4", "R5", "R6", "M1", "M2", "M3"])
check("C1", f"17 consecutive theorems T1-T17 (found {len(theorems)})",
      [t[0] for t in theorems] == [f"T{i}" for i in range(1, 18)])

print("\n== C2 engine header banner ==")
banner = {}
for i, line in enumerate(laws_lines[:30], start=1):
    m = re.match(r"\s*\*\s+Law (I|II|III|IV|V|VI):\s", line)
    if m:
        r = ranges(line)
        banner[m.group(1)] = (i, r[0] if r else None)
want = {"I": (1, 2), "III": (3, 4), "IV": (5, 7), "V": (10, 17), "VI": (18, 18), "II": None}
for law in ["I", "II", "III", "IV", "V", "VI"]:
    got = banner.get(law, (None, "missing"))[1]
    check("C2", f"banner Law {law}: theorem range {got} (predicted {want[law]})", got == want[law])

print("\n== C3 order of banners and namespaces ==")
ban_pos = {}
ns_pos = {}
for i, line in enumerate(laws_lines, start=1):
    m = re.match(r"//\s+LAW (I|II|III|IV|V|VI)\b", line)
    if m and m.group(1) not in ban_pos:
        ban_pos[m.group(1)] = i
    m = re.match(r"namespace (law_(?:I|II|III|IV|V|VI)) \{", line)
    if m:
        ns_pos[m.group(1)] = i
order = ["I", "II", "III", "IV", "V", "VI"]
check("C3", f"banner lines {[ban_pos.get(x) for x in order]} increasing",
      all(x in ban_pos for x in order) and [ban_pos[x] for x in order] == sorted(ban_pos[x] for x in order))
check("C3", f"namespace lines {[ns_pos.get('law_' + x) for x in order]} increasing",
      all(("law_" + x) in ns_pos for x in order) and [ns_pos["law_" + x] for x in order] == sorted(ns_pos["law_" + x] for x in order))

print("\n== C4 T18 ==")
ruleset_ids = {t[0] for t in theorems}
check("C4", "T18 occurs in laws.hpp", 18 in tokens(laws))
check("C4", "T18 absent from the Ruleset theorem table", "T18" not in ruleset_ids)

print("\n== C5 T8 and T9 relative to the banner ranges ==")
covered = set()
for law, rng in want.items():
    if rng:
        covered.update(range(rng[0], rng[1] + 1))
check("C5", f"8 not covered, 9 not covered (covered = {sorted(covered)})", 8 not in covered and 9 not in covered)

print("\n== C6 gravitational dilation ==")
check("C6", "no function named gravitational_time_dilation in laws.hpp", "gravitational_time_dilation" not in laws)
check("C6", "depth_closure::clock_rate defined", re.search(r"auto clock_rate\(double z\)", laws) is not None)
t16 = [t for t in theorems if t[0] == "T16"]
check("C6", "Ruleset T16 row names a square-root form", bool(t16) and "sqrt" in t16[0][2])

print("\n== Reported (not criteria): Ruleset theorem names ==")
for t in theorems:
    print(f"  {t[0]:<4} {t[1].strip():<34} {t[2].strip()}")

print("\n== Reported: T<n> tokens in laws.hpp by theorem number ==")
count = {}
first = {}
current = "header"
per_ns = {}
for i, line in enumerate(laws_lines, start=1):
    m = re.match(r"namespace (\w+)", line)
    if m:
        current = m.group(1)
    for n in tokens(line):
        count[n] = count.get(n, 0) + 1
        first.setdefault(n, i)
        per_ns[current] = per_ns.get(current, 0) + 1
for n in range(1, 25):
    if n in count:
        print(f"  T{n:<3} {count[n]:>3} tokens, first at line {first[n]}")
    elif n <= 18:
        print(f"  T{n:<3}   0 tokens")
print("  tokens by top-level namespace:", ", ".join(f"{k}:{v}" for k, v in per_ns.items()))

print("\n== Reported: theorem and lemma headings of the Complete Laws paper ==")
for m in re.finditer(r"^((?:Theorem|Lemma|Corollary) [0-9.]+)[ .]\s*(.{0,70})", complete, re.M):
    print(f"  {m.group(1):<16} {m.group(2).strip()}")

print(f"\n{'ALL CRITERIA MET' if failures == 0 else 'CRITERIA NOT MET'}: {failures} failure(s)")
sys.exit(0 if failures == 0 else 1)
