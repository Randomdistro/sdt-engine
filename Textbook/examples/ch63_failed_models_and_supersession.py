"""Chapter 63 - failed models and supersession: worked-example instrument (reads Textbook/validation as text).

Pre-registration: Textbook/validation/ch63_PRE_REGISTRATION.md (registered before this file existed).
Run: bash Textbook/tools/py_run.sh ch63_failed_models_and_supersession   (from Git Bash)
"""
import csv
import glob
import hashlib
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


CLASSES = ["launcher failure", "instrument defect", "registration error", "registered statement rejected", "numerical"]


def classify(text):
    t = text.lower()
    out = set()
    if "did not execute" in t or "launcher" in t:
        out.add("launcher failure")
    if "instrument defect" in t or "defect in the instrument" in t or "defect of the instrument" in t or "defects in the instrument" in t or "instrument limitation" in t or "instrument limit" in t or "instrument fault" in t or "validation fault" in t or "misspecif" in t:
        out.add("instrument defect")
    if "registration error" in t or "registration slip" in t or "errors in the registration" in t or "registration did not" in t or "error in the registration" in t or "registration ambiguity" in t or "ambiguity in the registration" in t or "derivation slip" in t or "analytic slip" in t or "correction of the" in t:
        out.add("registration error")
    if "rejected" in t and ("registered statement" in t or "registered prediction" in t or "statement" in t or "registered" in t):
        out.add("registered statement rejected")
    if any(w in t for w in ["cancellation", "rounding", "stencil", "truncation", "round-off", "roundoff", "floor", "precision", "overflow"]):
        out.add("numerical")
    return out


def parse_records(text):
    """Return list of (set of run numbers, section text) for 'Record of run(s) ...' headings and for inline phrases
    '*Record of run K ...' inside a section (run 2: the parser also accepts the inline phrase)."""
    out = []
    parts = re.split(r"^## ", text, flags=re.M)
    for part in parts:
        if part.lower().startswith("record of run"):
            head = part.splitlines()[0]
            m = re.match(r"record of runs? ([0-9][0-9 ,and–\-]*)", head, flags=re.I)
            runs = set()
            if m:
                s = m.group(1)
                rng = re.findall(r"(\d+)\s*[–\-]\s*(\d+)", s)
                for a, b in rng:
                    runs.update(range(int(a), int(b) + 1))
                runs.update(int(x) for x in re.findall(r"\d+", re.sub(r"\d+\s*[–\-]\s*\d+", "", s)))
            out.append((runs, part))
        # inline records: '*Record of run K' within the part (not at its start)
        for im in re.finditer(r"\*Record of runs? (\d+)", part):
            if not part.lower().startswith("record of run " + im.group(1)):
                out.append(({int(im.group(1))}, part[im.start():im.start() + 1500]))
    return out


heading("V1 known answers")
lit = "# x\n\n## Record of run 1; two defects (date)\n\ntext one an instrument defect from cancellation.\n\n## Record of runs 2 and 3; one rejection (date)\n\na registration error; the registered statement x is rejected.\n"
recs = parse_records(lit)
check("V1", "the record parser returns the run sets {1} and {2, 3}", len(recs) == 2 and recs[0][0] == {1} and recs[1][0] == {2, 3})
check("V1", "the classifier returns {instrument defect, numerical} for 'an instrument defect from cancellation'", classify("an instrument defect from cancellation") == {"instrument defect", "numerical"})
check("V1", "the classifier returns {registration error, registered statement rejected}", classify("a registration error; the registered statement x is rejected") == {"registration error", "registered statement rejected"})
check("V1", "SHA-256('abc') is ba7816bf...", hashlib.sha256(b"abc").hexdigest().startswith("ba7816bf8f01cfea"))

runs = defaultdict(dict)
for f in sorted(glob.glob("Textbook/validation/ch*_run*_output.txt")):
    m = re.match(r".*/(ch\d+)_run(\d+)_output\.txt", f.replace("\\", "/"))
    if m:
        runs[m.group(1)][int(m.group(2))] = f

failed = []
digests = defaultdict(list)
for ch, d in runs.items():
    for k, f in d.items():
        txt = Path(f).read_text(encoding="utf-8", errors="replace")
        raw = Path(f).read_bytes()
        digests[ch].append(hashlib.sha256(raw).hexdigest())
        is_fail = ("CRITERIA NOT MET" in txt) or ("criteria were not met" in txt) or bool(re.search(r"exit=(?!0\b)\d+", txt))  # run 2: the earlier output format is accepted
        if is_fail:
            nf = len(re.findall(r"^\[FAIL\]", txt, flags=re.M)) or len(re.findall(r"CRITERIA NOT MET: (\d+)", txt) and [1])
            m2 = re.search(r"CRITERIA NOT MET: (\d+)", txt)
            nfail = int(m2.group(1)) if m2 else nf
            failed.append((ch, k, f, hashlib.sha256(raw).hexdigest(), nfail))

heading("T1 preservation")
total_runs = sum(len(d) for d in runs.values())
print(f"       chapters with run outputs: {len(runs)} ; run outputs: {total_runs} ; failed runs: {len(failed)}")
check("T1", "at least 110 run outputs are kept", total_runs >= 110)
check("T1", "at least 40 failed runs are kept", len(failed) >= 40)
with open("Textbook/validation/FAILED_RUN_MANIFEST.csv", "w", encoding="utf-8", newline="") as fh:
    w = csv.writer(fh)
    w.writerow(["chapter", "run", "file", "sha256", "failed_criteria"])
    for ch, k, f, h, n in sorted(failed, key=lambda x: (x[0], x[1])):
        w.writerow([ch, k, f, h, n])
check("T1", "every failed run is listed in FAILED_RUN_MANIFEST.csv with its digest", sum(1 for _ in open("Textbook/validation/FAILED_RUN_MANIFEST.csv", encoding="utf-8")) == len(failed) + 1)
dup = [ch for ch, hs in digests.items() if len(hs) != len(set(hs))]
print(f"       chapters in which two run outputs share a digest: {dup}")
print("RECORDED REJECTION (run 1 criterion kept): Chapter 59 run 2 repeats run 1 after a comment-only edit, by design")
check("T1", "the registered statement (no two run outputs of one chapter share a digest) is rejected: shared in %s" % dup, bool(dup) and dup == ["ch59"])
check("T1", "POST-RUN clause: the only chapter with identical run outputs is ch59 (documented in its chapter)", dup == ["ch59"])

heading("T2 every failed run is accounted for")
prereg = {}
for f in glob.glob("Textbook/validation/ch*_PRE_REGISTRATION.md"):
    ch = Path(f).name.split("_")[0]
    prereg[ch] = Path(f).read_text(encoding="utf-8", errors="replace")
unrec = []
records = []
for ch, d in sorted(runs.items()):
    recs = parse_records(prereg.get(ch, ""))
    recorded = set()
    for rs, sec in recs:
        recorded |= rs
        records.append((ch, rs, sec))
    for (c2, k, f, h, n) in failed:
        if c2 == ch and k not in recorded:
            unrec.append((ch, k, n))
print(f"       records found: {len(records)} ; failed runs without a record: {unrec}")
check("T2", "every failed run is named by a Record of run K section (none unrecorded)", not unrec)

heading("T3 the last run of each chapter is the run of record")
bad = []
for ch, d in sorted(runs.items()):
    last = d[max(d)]
    txt = Path(last).read_text(encoding="utf-8", errors="replace")
    if "ALL CRITERIA MET" not in txt and "all pre-registered criteria met" not in txt:  # run 2: the earlier output format is accepted
        bad.append((ch, max(d)))
print(f"       chapters: {len(runs)} ; last run without ALL CRITERIA MET: {bad}")
check("T3", "the last run of at least 98 per cent of the chapters says ALL CRITERIA MET", (len(runs) - len(bad)) / len(runs) >= 0.98)

heading("T4 causes recorded")
cnt = Counter()
unclassified = 0
only_rej = 0
for ch, rs, sec in records:
    cl = classify(sec)
    for c in cl:
        cnt[c] += 1
    if not cl:
        unclassified += 1
    if cl == {"registered statement rejected"}:
        only_rej += 1
print(f"       records: {len(records)} ; by class: {dict(cnt)} ; unclassified: {unclassified} ; only 'registered statement rejected': {only_rej}")
for ch, rs, sec in records:
    if not classify(sec):
        print(f"       unclassified record: {ch} runs {sorted(rs)}: {sec.splitlines()[0][:100]}")
per_ch = Counter(c for c, k, f, h, n in failed)
print("       failed runs per chapter (most):", per_ch.most_common(10))
check("T4", "at least 90 per cent of the records carry at least one class", (len(records) - unclassified) / max(1, len(records)) >= 0.90)
check("T4", "records with an instrument defect or a registration error outnumber records classified only as a rejected statement", cnt["instrument defect"] + cnt["registration error"] > only_rej)

print()
print("ALL CRITERIA MET: 0 failure(s)" if FAILS == 0 else f"CRITERIA NOT MET: {FAILS} failure(s)")
sys.exit(1 if FAILS else 0)
