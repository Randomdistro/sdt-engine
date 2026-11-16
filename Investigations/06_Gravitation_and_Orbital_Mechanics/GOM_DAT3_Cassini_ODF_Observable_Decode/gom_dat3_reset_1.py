"""GOM_DAT3 cumindex freeze list (2026-10-12). Registration: GOM_DAT3_RESET_ASSESSMENT_2026-10-12.md sections 0-2 (written before this file existed).
Run from the repository root with: python -I Investigations/06_Gravitation_and_Orbital_Mechanics/GOM_DAT3_Cassini_ODF_Observable_Decode/gom_dat3_reset_1.py
Author: J. C. Harvey, Melbourne."""
import csv, os, re

RAW = 'Datasets/solar_propagation_2026-08/raw/'
IDX = RAW + 'cassini_sce1_cors0021_cumindex.tab'
rows = []
with open(IDX, newline='', encoding='ascii') as f:
    for r in csv.reader(f):
        rows.append([c.strip() for c in r])
print('cumindex rows:', len(rows), '; columns per row:', sorted({len(r) for r in rows}))
odf = [r for r in rows if '/ODF/' in r[1].upper() and re.match(r'SCE1_(157|158|159|160)/', r[1].upper())]
print('ODF rows for SCE1_157..160:', len(odf))
fails = 0

def lbl_val(path, key):
    with open(path, 'rb') as g:
        for ln in g.read().decode('ascii', 'replace').splitlines():
            if ln.startswith(key):
                return ln.split('=', 1)[1].strip()
    return None

for r in odf:
    vol, lblpath, name, pid, start, stop, created = r[:7]
    day = lblpath.split('/')[0][-3:]
    fam = name[-9:-4].lower() if name.upper().endswith('.ODF') else name.lower()
    lbl_disk = RAW + 'cassini_sce1/cors_0021/sce1_%s/odf/%s' % (day, lblpath.split('/')[-1].lower())
    odf_disk = RAW + 'cassini_sce1/cors_0021/sce1_%s/odf/%s' % (day, name.lower().strip())
    present = os.path.exists(odf_disk) and os.path.exists(lbl_disk)
    if present:
        ls, le, lc = lbl_val(lbl_disk, 'START_TIME'), lbl_val(lbl_disk, 'STOP_TIME'), lbl_val(lbl_disk, 'PRODUCT_CREATION_TIME')
        ok = (ls[:17] == start[:17]) and (le[:17] == stop[:17]) and (lc[:17] == created[:17])
        print('%-34s start %s stop %s created %s | disk: present ; label %s %s %s -> %s' % (name, start, stop, created, ls, le, lc, 'match' if ok else 'MISMATCH'))
        if not ok:
            fails += 1
    else:
        print('%-34s start %s stop %s created %s | disk: ABSENT -> PENDING_FETCH' % (name, start, stop, created))
        fails += 1
names = sorted(r[2].strip() for r in odf)
expected = sorted('C32EASC2002_%d_0000%s.ODF' % (d, fam) for d in (157, 158, 159, 160) for fam in ('K252V0', 'XMMMV0'))
print('expected eight names listed in the index:', names == expected, '; extra ODF products in the index:', [n for n in names if n not in expected], '; expected but missing from the index:', [n for n in expected if n not in names])
print('C4:', 'met (every frozen record present on disk with start/stop/creation equal to its label)' if fails == 0 and names == expected else 'NOT MET or with additions: see above')
print('C1-C3 not re-run (supplier); no residual or delay computed.')
