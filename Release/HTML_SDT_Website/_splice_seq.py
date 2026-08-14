"""Replace the sequencer's inline isotope table with the shared catalogue."""
from pathlib import Path

p = Path("nuclear-packing-sequencer.html")
t = p.read_text(encoding="utf-8")
start = t.index("<!-- ═══════════════ DATA")
end = t.index("</script>", t.index("const ISO = RAW.map")) + len("</script>")
names_line = [ln for ln in t[start:end].splitlines() if ln.startswith("const NAMES=")][0]
new = f'''<script src="js/isotopes.js"></script>
<script>
{names_line}
const LAB = "atomicus-lab-subdued.html";
function labHref(e){{ return LAB + "#Z=" + e.Z + "&A=" + e.A; }}
const RAW = window.SDT_ISO_RAW || [];
const ISO = RAW.map(([Z,A,sym,stab,beA,spin,abd])=>{{
  const nd=3*Z-A-2, nt=A-2*Z;
  const stable = String(stab).toLowerCase().startsWith("stable");
  const be = (beA||0)*A;
  return {{sym,Z,A,abd,stable,be,beA:beA||0,spin,nd,nt,name:NAMES[Z]||sym}};
}}).filter(e=>e.nd>=0 && e.nt>=0);
</script>'''
p.write_text(t[:start] + new + t[end:], encoding="utf-8")
print("spliced data block; ISO source is js/isotopes.js")
