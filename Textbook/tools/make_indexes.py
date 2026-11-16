"""Generate Textbook/equations/EQUATION_INDEX.csv and Textbook/sources/SOURCE_INDEX.csv from the chapter files.

Run from the repository root (Git Bash): python -I Textbook/tools/make_indexes.py
The hand-written EQUATION_REGISTER.md (Chapter 9) and SOURCE_MANIFEST.md are not overwritten; these are generated indexes
(a tag index of every numbered display equation, and a per-chapter source index: headers cited, instrument, run of record).
"""
import csv
import glob
import re
import sys
from collections import Counter
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
TAG = re.compile(r"\\tag\{([^}]*)\}")
HDR = re.compile(r"\b([A-Za-z_0-9]+\.hpp)\b")

eq_rows = []
src_rows = []
for f in sorted(glob.glob("Textbook/volume_0*/ch*.md")):
    p = Path(f)
    ch = int(p.name[2:4])
    text = p.read_text(encoding="utf-8")
    lines = text.splitlines()
    for i, ln in enumerate(lines):
        for m in TAG.finditer(ln):
            j = i
            body = ""
            # the equation text is the nearest non-empty non-$$ line above the tag line (or the tag line itself)
            k = i
            while k >= 0 and (lines[k].strip() in ("$$", "") or "\\tag" in lines[k] and k == i and lines[k].strip().startswith("\\tag")):
                k -= 1
            body = lines[k].strip() if k >= 0 else ""
            body = re.sub(r"\\tag\{[^}]*\}", "", body).strip(" $")
            eq_rows.append([ch, m.group(1), i + 1, body[:160]])
    hdrs = Counter(h for h in HDR.findall(text) if h in {Path(x).name for x in glob.glob("Engine/include/sdt/*.hpp")})
    stem = next((Path(x).stem for x in glob.glob(f"Textbook/examples/ch{ch:02d}_*") ), "")
    runs = sorted(glob.glob(f"Textbook/validation/ch{ch:02d}_run*_output.txt"), key=lambda s: int(re.search(r"run(\d+)", s).group(1)))
    src_rows.append([ch, p.parent.name, p.name, stem, "; ".join(f"{h}:{n}" for h, n in sorted(hdrs.items())), len(runs), Path(runs[-1]).name if runs else ""])

Path("Textbook/equations").mkdir(exist_ok=True)
with open("Textbook/equations/EQUATION_INDEX.csv", "w", encoding="utf-8", newline="") as fh:
    w = csv.writer(fh)
    w.writerow(["chapter", "tag", "line", "equation_text"])
    w.writerows(eq_rows)
with open("Textbook/sources/SOURCE_INDEX.csv", "w", encoding="utf-8", newline="") as fh:
    w = csv.writer(fh)
    w.writerow(["chapter", "volume", "file", "instrument", "headers_cited_with_counts", "runs", "run_of_record_output"])
    w.writerows(src_rows)
print(f"equations indexed: {len(eq_rows)} in {len({r[0] for r in eq_rows})} chapters; source rows: {len(src_rows)}")
