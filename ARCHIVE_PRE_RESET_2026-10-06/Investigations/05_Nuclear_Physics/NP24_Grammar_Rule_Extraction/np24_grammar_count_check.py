# NP24 reproduction check (audit correction 2026-10-05): recount the grammar-valid isotopes from the repo's NUBASE2020 file.
# Grammar (constitutional, ATOMICUS): n_t = A - 2Z, n_d = 3Z - A - 2, valid for Z >= 3 when both >= 0; identities A = 4 + 2 n_d + 3 n_t, Z = 2 + n_d + n_t.
rows = {}
for l in open('../../../Datasets/nuclear/NUBASE2020.txt', encoding='latin-1'):
    if l.startswith('#') or len(l) < 120: continue
    try: A = int(l[0:3]); Z = int(l[4:7]); i = int(l[7])
    except Exception: continue
    if i == 0: rows[(Z, A)] = l[69:80].strip()
valid = [(Z, A) for (Z, A) in rows if Z >= 3 and A - 2*Z >= 0 and 3*Z - A - 2 >= 0]
bad = [(Z, A) for (Z, A) in valid if (4 + 2*(3*Z-A-2) + 3*(A-2*Z) != A) or (2 + (3*Z-A-2) + (A-2*Z) != Z)]
print('ground-state rows', len(rows), '| Z>=3 grammar-valid', len(valid), '| identity failures', len(bad))
print('(recorded in NP24: 3213 valid-grammar isotopes, 0 failures)')
