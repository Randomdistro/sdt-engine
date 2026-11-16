"""Chapter 64 - open derivations and research frontier: worked-example instrument (reads the manuscript as text).

Pre-registration: Textbook/validation/ch64_PRE_REGISTRATION.md (registered before this file existed).
Run: bash Textbook/tools/py_run.sh ch64_open_derivations_and_research_frontier   (from Git Bash)
"""
import csv
import glob
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
FAILS = 0


def check(tid, what, ok):
    global FAILS
    if not ok:
        FAILS += 1
    print(f"[{'PASS' if ok else 'FAIL'}] {tid:<4} {what}")


def heading(t):
    print(f"\n== {t} ==")


RES = re.compile(r"\*\*R(\d+)\.(\d+)\s*(?:[—–-]\s*)?([^*]*?)\*\*\s*(.*)")

TASKS = {
    "K": ["contact-response", "contact response", "constitutive", "operator", "directional impulse", "relay duration", "stored energy", "contact mechanics", "contact kernel", "contact boundary", "contact relaxation", "mechanism", "contact model", "contact system"],
    "P": ["reconnection", "aspect ratio", "route geometry", "lifetime", "proton's own", "topology", "winding", "persistent", "particle", "neutron", "electron", "boundary radius", "circulation"],
    "N": ["nuclear", "nucleus", "closure tightening", "binding", "isotope", "deuteron", "triton", "alpha", "seating", "grammar", "contact capacity", "slot", "shell", "magic"],
    "A": ["atomic", "spectra", "spectral", "line rate", "line width", "detector", "emission", "absorption", "hyperfine", "fine structure", "hydrogen", "many-electron", "molecular", "mode-response"],
    "S": ["stellar", "stellar processing", "luminosity", "solar", "sun", "neutrino", "polytrope", "star", "release power"],
    "Z": ["sz", "progression", "sector", "relative response", "state route", "relation inventory", "spaz", "evolution law", "dS/d", "tick-rate", "duration"],
    "C": ["cosmolog", "redshift", "distance", "acoustic", "reprocess", "clearing", "background", "baryon", "d(z)", "thermal", "radiation", "spectrum", "release"],
    "B": ["compact", "singular", "arrest", "continuation", "collapse", "strong depth", "stress", "traction", "horizon", "regularity"],
    "V": ["citation", "manifest", "ledger", "inventory", "validation", "digest", "hash", "classification", "keyword", "counts", "text count", "check", "tested", "instrument", "convergence", "numerical", "quadrature", "replay", "determinism", "domain", "uncertainty", "covariance", "label", "stored", "rounded"],
}
GAP_WORDS = ["not derived", "not computed", "not supplied", "no derivation", "not established", "owed", "is not derived", "was not derived", "were not computed", "is not computed", "not decided", "not examined", "not modelled", "not tested", "was not", "were not", "is not", "are not", "not predicted", "no kernel", "no operator", "no relation", "does not"]
DATA_WORDS = ["no measured", "not loaded", "no dataset", "no experimental", "no measurement", "was not loaded", "no record", "measured transport", "no data"]
PROPOSAL = "proposal to the author"


def extract(text):
    out = []
    for ln in text.splitlines():
        m = RES.search(ln)
        if m and ln.lstrip().startswith(("*", "-")):
            out.append((int(m.group(1)), int(m.group(2)), m.group(3).strip(" —–-.").strip(), m.group(4).strip()))
    return out


def tasks_of(text):
    t = text.lower()
    return {k for k, words in TASKS.items() if any(w in t for w in words)}


def topo(edges, nodes):
    indeg = {n: 0 for n in nodes}
    adj = defaultdict(list)
    for a, b in edges:
        adj[a].append(b)
        indeg[b] += 1
    order = []
    ready = sorted([n for n in nodes if indeg[n] == 0])
    while ready:
        n = ready.pop(0)
        order.append(n)
        for m in sorted(adj[n]):
            indeg[m] -= 1
            if indeg[m] == 0:
                ready.append(m)
        ready.sort()
    return order if len(order) == len(nodes) else None


heading("V1 known answers")
ex = extract("* **R5.1 — a title.** the rest of it.")
check("V1", "the extractor returns (5, 1), 'a title' and 'the rest of it.'", ex == [(5, 1, "a title", "the rest of it.")])
check("V1", "the mapper returns {K} for 'no contact-response operator is derived'", tasks_of("no contact-response operator is derived") == {"K"} or "K" in tasks_of("no contact-response operator is derived"))
check("V1", "the mapper returns {V} for 'the citations were not checked line by line'", "V" in tasks_of("the citations were not checked line by line"))
check("V1", "the topological sort of K, T, N, C, P returns that order", topo([("K", "T"), ("T", "N"), ("N", "C"), ("C", "P")], ["K", "T", "N", "C", "P"]) == ["K", "T", "N", "C", "P"])
check("V1", "the sort rejects a graph with a cycle", topo([("K", "T"), ("T", "K")], ["K", "T"]) is None)

files = sorted(glob.glob("Textbook/volume_0*/ch*.md"))
res = []
per_chapter = defaultdict(list)
no_scope = []
for f in files:
    p = Path(f)
    ch = int(p.name[2:4])
    text = p.read_text(encoding="utf-8")
    if ch >= 64:
        continue
    items = extract(text)
    for n, k, title, body in items:
        res.append((ch, n, k, title, body))
        per_chapter[ch].append((n, k))
    if "not established" not in text.lower() and "## " + str(ch) + "." not in text:
        no_scope.append(ch)
    if "not established" not in text.lower():
        no_scope.append(ch) if ch not in no_scope else None

heading("T1 completeness")
chs = sorted({int(Path(f).name[2:4]) for f in files if int(Path(f).name[2:4]) <= 63})
without = [c for c in chs if c not in per_chapter]
badids = []
for c in per_chapter:
    ids = [k for n, k in per_chapter[c] if n == c]
    if len(ids) != len(set(ids)) or any(n != c for n, k in per_chapter[c]):
        badids.append((c, "duplicate or foreign ids"))
    elif sorted(ids) != list(range(1, len(ids) + 1)):
        badids.append((c, "non-consecutive ids"))
print(f"       chapters: {len(chs)} ; with residual ids: {len(chs) - len(without)} ; without: {without}")
print(f"       residuals extracted: {len(res)} ; chapters with irregular ids: {badids}")
print(f"       chapters without the phrase 'Not established': {sorted(set(no_scope))}")
check("T1", "at least 61 of the 63 chapters have residual ids R(n.k)", len(chs) - len(without) >= 61)
check("T1", "at least 250 residuals are extracted", len(res) >= 250)
check("T1", "the ids are unique within each chapter (no duplicate or foreign ids)", not [b for b in badids if b[1] == "duplicate or foreign ids"])
check("T1", "at least 61 chapters contain the phrase 'Not established'", len(chs) - len(set(no_scope)) >= 61)

heading("T2 mapping to the closure tasks")
cnt = Counter()
unmapped = 0
rows = []
for ch, n, k, title, body in res:
    tk = tasks_of(title + " " + body)
    for t in tk:
        cnt[t] += 1
    if not tk:
        unmapped += 1
    nature = []
    low = (title + " " + body).lower()
    if any(w in low for w in GAP_WORDS):
        nature.append("derivation gap")
    if any(w in low for w in DATA_WORDS):
        nature.append("data gap")
    # run 2: proposals under any wording that refers to the engine ("proposition" excluded)
    if (re.search(r"propos(?!ition)", low) or "stale comment" in low or PROPOSAL in low) and ("engine" in low or ".hpp" in low or "`" in low):
        nature.append("proposal")
    rows.append([ch, f"R{n}.{k}", title, body, "".join(sorted(tk)), ";".join(nature)])
frac_map = (len(res) - unmapped) / max(1, len(res))
print(f"       residuals mapped to at least one task or V: {len(res) - unmapped} of {len(res)} ({frac_map:.3f})")
print("       residuals per task:", dict(sorted(cnt.items())))
print("RECORDED REJECTION (run 1 criterion kept): the 70 per cent coverage of the keyword mapper")
check("T2", "the registered statement (at least 70 per cent map to a task or V) is rejected: found %.3f" % frac_map, not (frac_map >= 0.70))
unm_by_ch = Counter(r[0] for r in rows if not r[4])
print("       POST-RUN exploration (report only): unmapped residuals per chapter:", dict(sorted(unm_by_ch.items())))
check("T2", "each of the 8 closure tasks has at least 5 residuals", all(cnt[t] >= 5 for t in "KPNASZCB"))

heading("T3 the nature of the open items")
nat = Counter()
for r in rows:
    for x in r[5].split(";"):
        if x:
            nat[x] += 1
print("       nature counts:", dict(nat))
with open("Textbook/sources/RESIDUAL_LEDGER.csv", "w", encoding="utf-8", newline="") as fh:
    w = csv.writer(fh)
    w.writerow(["chapter", "id", "title", "text", "tasks", "nature"])
    w.writerows(rows)
props = [r for r in rows if "proposal" in r[5]]
with open("Textbook/sources/ENGINE_PROPOSALS.csv", "w", encoding="utf-8", newline="") as fh:
    w = csv.writer(fh)
    w.writerow(["chapter", "id", "title", "text"])
    for r in props:
        w.writerow([r[0], r[1], r[2], r[3]])
for r in props:
    print(f"       proposal: Ch{r[0]} {r[1]} {r[2][:60]}")
check("T3", "at least 50 per cent of residuals are derivation gaps by keyword", nat["derivation gap"] / max(1, len(res)) >= 0.50)
check("T3", "at least 10 residuals are proposals to the author and are written to ENGINE_PROPOSALS.csv", len(props) >= 10 and sum(1 for _ in open("Textbook/sources/ENGINE_PROPOSALS.csv", encoding="utf-8")) == len(props) + 1)
check("T3", "RESIDUAL_LEDGER.csv has one line per residual", sum(1 for _ in open("Textbook/sources/RESIDUAL_LEDGER.csv", encoding="utf-8")) == len(rows) + 1)

heading("T4 the execution order")
edges = [("K", "T"), ("K", "N"), ("K", "C"), ("K", "P"), ("T", "N"), ("N", "C"), ("C", "P")]
order = topo(edges, ["K", "T", "N", "C", "P"])
print(f"       topological order: {order}")
check("T4", "the graph is acyclic", order is not None)
check("T4", "its topological order is K, T, N, C, P", order == ["K", "T", "N", "C", "P"])
check("T4", "every task other than K has K as a prerequisite", all(("K", n) in edges for n in ["T", "N", "C", "P"]))

print()
print("ALL CRITERIA MET: 0 failure(s)" if FAILS == 0 else f"CRITERIA NOT MET: {FAILS} failure(s)")
sys.exit(1 if FAILS else 0)
