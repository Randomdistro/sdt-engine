"""Extract the lab isotope RAW table into js/isotopes.js."""
from pathlib import Path

lab = Path("atomicus-lab-subdued.html").read_text(encoding="utf-8")
start = lab.index("const RAW = [")
end = lab.index("];", start)
body = lab[start : end + 2]  # includes const RAW = [ ... ];
# drop the const — the shared file owns the name
arr = body[body.index("[") : body.rindex("]") + 1]
out = Path("js/isotopes.js")
out.write_text(
    "/* Shared isotope catalogue — extracted from the Atomicus lab.\n"
    "   [Z, A, sym, stability, BE/nucleon MeV, spin, abundance%]\n"
    "   Consumed by the packing sequencer and the lab. */\n"
    "window.SDT_ISO_RAW = "
    + arr
    + ";\n",
    encoding="utf-8",
)
n = arr.count("\n[") + (1 if arr.strip().startswith("[") else 0)
# count array rows more carefully
rows = sum(1 for line in arr.splitlines() if line.lstrip().startswith("["))
print(f"wrote {out} with {rows} isotope rows")
