#!/usr/bin/env python3
# ================================================================
# enrich_boundary_radius.py -- phase enrichment 2026-07-23
#
# Appends a "Boundary Radius & Triton Contraction" section to each
# isotopes/NNN_XN.md file, carrying the measured boundary radius
# (IAEA ground states, pulled this phase) and the SDT readings
# established the same phase:
#   - triton-contraction rule (r0 falls as n_t rises)
#   - shell-closure compaction (3-point kink curvature)
#   - the electron economy (A protons, A electrons; N stabled, Z fielded)
#
# Data: empirical measured radii only. No fitted values.
# "Boundary radius" = proton displacement boundary. NO charge substance.
#
# The generated isotope files carry mixed legacy byte-encoding, so this
# tool operates in BYTES: it locates the ASCII marker without decoding,
# truncates any prior phase block, and appends ASCII-only content.
# Idempotent: re-running replaces the block, never duplicates it.
# ================================================================
import csv, os, re

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
ISO  = os.path.join(ROOT, "isotopes")
CSV  = os.path.join(HERE, "_iaea_ground_states.csv")
MARK = "## Boundary Radius & Triton Contraction"
MAGIC = [2, 8, 20, 28, 50, 82, 126]
dm = lambda v: min(abs(v - m) for m in MAGIC)

def load():
    R = {}
    for r in csv.DictReader(open(CSV, encoding="utf-8")):
        try:
            z = int(r["z"]); n = int(r["n"]); rad = r["radius"].strip()
            if rad:
                R[(z, n)] = float(rad)
        except Exception:
            pass
    return R

def kink(R, z, n):
    a, b, c = R.get((z, n - 2)), R.get((z, n)), R.get((z, n + 2))
    return (b - (a + c) / 2) * 1000 if (a and b and c) else None

def block(R, sym, Z, A):
    """Return an ASCII-only enrichment block, or None if outside the grammar."""
    N = A - Z
    nd, nt = 3 * Z - A - 2, A - 2 * Z
    if nd < 0 or nt < 0:
        return None                       # outside the grammar (approaching neutronium)
    ft = nt / (nd + nt) if (nd + nt) else 0.0
    rad = R.get((Z, N))
    k = kink(R, Z, N)
    L = [MARK + "  *(phase enrichment 2026-07-23)*", ""]
    if rad:
        L.append(f"- **Boundary radius** (measured, IAEA): R = {rad:.4f} fm "
                 f"-- the proton displacement boundary; no charge substance")
        L.append(f"- **Effective r0 = R / A^(1/3)**: {rad / A**(1/3):.4f} fm")
    else:
        L.append("- **Boundary radius**: not measured for this nuclide")
    L.append(f"- **Grammar / triton fraction**: alpha + {nd}d + {nt}t, f_t = {ft:.2f}")
    L.append(f"- **Electron economy**: {A} protons, {A} electrons -- "
             f"{N} stabled inward (read as neutrons) + {Z} fielded outward (the shell)")
    cl = []
    if dm(N) == 0: cl.append(f"N={N} (closed)")
    if dm(Z) == 0: cl.append(f"Z={Z} (closed)")
    shell = ("**doubly-magic -- full compaction**" if len(cl) == 2
             else (cl[0] if cl else f"open shell (|N-magic|={dm(N)}, |Z-magic|={dm(Z)})"))
    kd = ""
    if k is not None:
        tag = "compact (below local trend)" if k < -1 else ("swollen" if k > 1 else "on trend")
        kd = f", local kink curvature = {k:+.1f} milli-fm ({tag})"
    L.append(f"- **Shell status**: {shell}{kd}")
    # contraction reading -- keyed off the MEASURED kink, cross-checked against shell status
    on_closure = (dm(N) == 0 or dm(Z) == 0)
    if k is not None and k < -3 and on_closure:
        L.append("- **Triton contraction**: sits on a shell closure and is drawn to its tightest -- "
                 "the interleaved scaffold is maximally compact here (measured kink confirms it).")
    elif k is not None and k > 3:
        opener = "N" if dm(N) > dm(Z) else "Z"
        note = (f" despite the closed {'Z' if opener=='N' else 'N'} shell" if on_closure else "")
        L.append(f"- **Triton contraction**: swollen -- the open {opener} shell dominates and deforms the "
                 f"boundary outward{note}; the contraction rule is locally overridden by mid-shell deformation.")
    elif ft == 0:
        L.append("- **Triton contraction**: pure-deuteron build (n_t = 0) -- the loose end of the rule; "
                 "no triton scaffold to contract.")
    else:
        L.append("- **Triton contraction**: the triton scaffold seats tighter than the deuteron filling; "
                 "the boundary contracts as n_t rises (rule holds 88% of chains / 90% of isobars).")
    L.append("")
    L.append("*Triton-contraction rule (phase 2026-07-23): pressure makes the interleaved packing the "
             "path of least resistance; tritons interleave tighter than deuterons, so the boundary "
             "contracts as the triton count climbs -- maximally at shell closures. "
             "See reference/BOUNDARY_RADIUS_TRITON_CONTRACTION.md.*")
    return "\n".join(L)

def main():
    R = load()
    files = sorted(f for f in os.listdir(ISO) if f.endswith(".md"))
    done = skipped = 0
    for f in files:
        m = re.match(r"^(\d+)_([A-Za-z]+)(\d+)", f)
        if not m:
            skipped += 1; continue
        Z, sym, A = int(m.group(1)), m.group(2), int(m.group(3))
        blk = block(R, sym, Z, A)
        if blk is None:
            skipped += 1; continue
        p = os.path.join(ISO, f)
        raw = open(p, "rb").read()
        mb = MARK.encode("ascii")
        if mb in raw:                                    # idempotent: cut any prior block
            raw = raw[:raw.index(mb)]
            raw = re.sub(rb"\n*-{3}\s*$", b"", raw)      # drop the trailing separator too
        body = raw.rstrip() + b"\n\n---\n\n" + blk.encode("utf-8") + b"\n"
        open(p, "wb").write(body)
        done += 1
    print(f"enriched {done} isotope files ({skipped} skipped -- outside grammar / unparsed)")

if __name__ == "__main__":
    main()
