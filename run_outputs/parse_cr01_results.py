from pathlib import Path
import json, csv, re

repo = Path(r'C:\Users\Jimmi\OneDrive\Desktop\sdt-engine')
outdir = repo / 'run_outputs'


def decode(path: Path) -> str:
    b = path.read_bytes()
    if b.startswith(b'\xff\xfe'):
        return b.decode('utf-16', errors='replace')
    if b.startswith(b'\xfe\xff'):
        return b.decode('utf-16-be', errors='replace')
    return b.decode('utf-8', errors='replace')


num = r'[-+]?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?'

# Parse SNe H0 correction file
sne_text = decode(outdir / 'cr01_sne_h0_correction.txt')
sne_lines = sne_text.splitlines()
sne_summary = {'study': 'CR01 SNe H0 correction', 'dataset': 'SNe Ia', 'summary': {}, 'rows': []}
for line in sne_lines:
    if 'Mean H0 (published' in line:
        m = re.search(r'Mean H0 \(published, no correction\):\s*([-+]?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?)', line)
        if m:
            sne_summary['summary']['Mean H0 (published, no correction)'] = float(m.group(1))
    elif 'Mean H0 (after 6-layer subtraction)' in line:
        m = re.search(r'Mean H0 \(after 6-layer subtraction\):\s*([-+]?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?)', line)
        if m:
            sne_summary['summary']['Mean H0 (after 6-layer subtraction)'] = float(m.group(1))
    elif 'Net shift' in line:
        m = re.search(r'Net shift:\s*([-+]?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?)', line)
        if m:
            sne_summary['summary']['Net shift'] = float(m.group(1))
    elif 'CMB value' in line:
        m = re.search(r'CMB value .*?:\s*([-+]?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?)', line)
        if m:
            sne_summary['summary']['CMB value'] = float(m.group(1))
    elif 'Remaining tension after correction' in line:
        m = re.search(r'Remaining tension after correction:\s*([-+]?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?)', line)
        if m:
            sne_summary['summary']['Remaining tension after correction'] = float(m.group(1))

for line in sne_lines:
    m = re.match(
        r'^(?P<name>\S+)\s+'
        r'(?P<z_total>' + num + r')\s+'
        r'(?P<z_star>' + num + r')\s+'
        r'(?P<z_gal>' + num + r')\s+'
        r'(?P<z_rot>' + num + r')\s+'
        r'(?P<z_sun>' + num + r')\s+'
        r'(?P<z_mw>' + num + r')\s+'
        r'(?P<z_cosmo>' + num + r')\s+'
        r'(?P<h0_corr>' + num + r')\s*$',
        line.strip(),
    )
    if m:
        row = m.groupdict()
        row['dataset'] = 'SNe Ia'
        row['study_id'] = 'CR01-SNE-H0'
        row['source_class'] = 'SN Ia'
        row['redshift_type'] = 'heliocentric published'
        sne_summary['rows'].append(row)

# Parse zladder
zladder_text = decode(outdir / 'cr01_zladder.txt')
zladder_lines = zladder_text.splitlines()
zladder = {'study': 'CR01 redshift gradient ladder', 'dataset': 'multi-source', 'summary': {}, 'rows': []}
for line in zladder_lines:
    if 'Mean H0_corrected' in line:
        m = re.search(r'Mean H0_corrected\s*=\s*([-+]?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?)', line)
        if m:
            zladder['summary']['H0_corrected_mean'] = float(m.group(1))
        m = re.search(r'CMB=([-+]?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?)', line)
        if m:
            zladder['summary']['CMB_reference'] = float(m.group(1))
        m = re.search(r'SH0ES=([-+]?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?)', line)
        if m:
            zladder['summary']['SH0ES_reference'] = float(m.group(1))
for line in zladder_lines:
    if not line.strip() or line.startswith('===') or line.startswith('---') or line.startswith('Name'):
        continue
    m = re.match(
        r'^(?P<name>.+?)\s+'
        r'(?P<z_total>' + num + r')\s+'
        r'(?P<z_gal>' + num + r')\s+'
        r'(?P<z_rot>' + num + r')\s+'
        r'(?P<z_sun>' + num + r')\s+'
        r'(?P<z_mw>' + num + r')\s+'
        r'(?P<z_cosmo>' + num + r')\s+'
        r'(?P<h0_corr>' + num + r')\s*$',
        line.strip(),
    )
    if m:
        row = m.groupdict()
        row['study_id'] = 'CR01-ZLADDER'
        row['dataset'] = 'multi-source'
        name = row['name']
        if 'Abell' in name or 'MACS' in name or 'RXJ' in name or 'MS' in name or 'RDCS' in name:
            row['source_class'] = 'Galaxy Cluster'
        elif 'SN' in name:
            row['source_class'] = 'SNe Ia'
        else:
            row['source_class'] = 'AGN/Quasar'
        zladder['rows'].append(row)

# Parse AGN BLR systematic
agn_text = decode(outdir / 'cr01_agn_zdecomp.txt')
agn_lines = agn_text.splitlines()
agn = {'study': 'CR01 AGN gravitational systematic', 'dataset': 'AGN/BLR', 'rows': []}
for line in agn_lines:
    if not line.strip() or line.startswith('===') or line.startswith('---') or line.startswith('AGN'):
        continue
    m = re.match(
        r'^(?P<name>.+?)\s+'
        r'(?P<z_total>' + num + r')\s+'
        r'(?P<delta_v_kms>' + num + r')\s+'
        r'(?P<tau_days>' + num + r')\s+'
        r'(?P<r_blr_lt_d>' + num + r')\s+'
        r'(?P<z_grav_blr>' + num + r')\s+'
        r'(?P<ratio_pct>' + num + r')\s*%?\s*$',
        line.strip(),
    )
    if m:
        row = m.groupdict()
        row['study_id'] = 'CR01-AGN-ZGRAV'
        row['source_class'] = 'AGN/Quasar'
        row['ratio_fraction'] = float(row['ratio_pct']) / 100.0
        agn['rows'].append(row)

# Parse unified scale-hierarchy rows
unified_text = decode(outdir / 'cr01_unified.txt')
unified_lines = unified_text.splitlines()
unified = {'study': 'CR01 unified redshift decomposition', 'dataset': 'scale_hierarchy', 'rows': []}
for line in unified_lines:
    if not line.strip():
        continue
    # This table is monotonic and readable with whitespace-separated fields.
    # Catch rows from the scale-hierarchy block only.
    if 'Scale' in line or 'Object' in line or 'Bridge law' in line or 'Every row' in line:
        continue
    tokens = line.split()
    if len(tokens) >= 7 and tokens[0] not in {'I.', 'II.', 'III.', 'IV.', 'V.', 'VI.', '===', 'Scale', 'Object'}:
        # Convert the row into a compact record if it looks like: object v R k z Ϟ z*k²
        if re.match(r'^[A-Za-z\(\)\-/0-9\.\+]+$', tokens[0]):
            # some rows are object names, not pure tokens; take last 6 fields as numeric values
            try:
                v = float(tokens[-6]); R = float(tokens[-5]); k = float(tokens[-4]); z = float(tokens[-3]); koppa = float(tokens[-2]); zk2 = float(tokens[-1])
            except ValueError:
                continue
            object_name = ' '.join(tokens[:-6])
            unified['rows'].append({'object': object_name, 'v': v, 'R': R, 'k': k, 'z': z, 'koppa': koppa, 'zk2': zk2})

# Flatten rows for CSV export
all_rows = []
for row in sne_summary['rows']:
    all_rows.append({
        'study_id': row['study_id'],
        'source_class': row['source_class'],
        'source_name': row['name'],
        'source_dataset': 'SNe Ia',
        'study_section': 'SN/host correction',
        'z_total': float(row['z_total']),
        'z_star_grav': float(row['z_star']),
        'z_galaxy_grav': float(row['z_gal']),
        'z_rotation_host': float(row['z_rot']),
        'z_sun_galactic': float(row['z_sun']),
        'z_MW_bulk': float(row['z_mw']),
        'z_cosmo': float(row['z_cosmo']),
        'H0_corrected': float(row['h0_corr']),
        'delta_v_kms': '',
        'tau_days': '',
        'r_BLR_lt_d': '',
        'z_grav_BLR': '',
        'z_grav_to_total_fraction': '',
        'observational_basis': 'Published heliocentric SN Ia redshifts decomposed into MW + host + cosmological terms.',
    })
for row in zladder['rows']:
    all_rows.append({
        'study_id': row['study_id'],
        'source_class': row['source_class'],
        'source_name': row['name'],
        'source_dataset': row['dataset'],
        'study_section': 'gradient ladder',
        'z_total': float(row['z_total']),
        'z_star_grav': '',
        'z_galaxy_grav': float(row['z_gal']),
        'z_rotation_host': float(row['z_rot']),
        'z_sun_galactic': float(row['z_sun']),
        'z_MW_bulk': float(row['z_mw']),
        'z_cosmo': float(row['z_cosmo']),
        'H0_corrected': float(row['h0_corr']),
        'delta_v_kms': '',
        'tau_days': '',
        'r_BLR_lt_d': '',
        'z_grav_BLR': '',
        'z_grav_to_total_fraction': '',
        'observational_basis': 'Source-class redshift ladder across SNe Ia, clusters and AGN/quasars.',
    })
for row in agn['rows']:
    all_rows.append({
        'study_id': row['study_id'],
        'source_class': row['source_class'],
        'source_name': row['name'],
        'source_dataset': 'AGN/BLR',
        'study_section': 'BLR gravitational systematic',
        'z_total': float(row['z_total']),
        'z_star_grav': '',
        'z_galaxy_grav': '',
        'z_rotation_host': '',
        'z_sun_galactic': '',
        'z_MW_bulk': '',
        'z_cosmo': '',
        'H0_corrected': '',
        'delta_v_kms': float(row['delta_v_kms']),
        'tau_days': float(row['tau_days']),
        'r_BLR_lt_d': float(row['r_blr_lt_d']),
        'z_grav_BLR': float(row['z_grav_blr']),
        'z_grav_to_total_fraction': float(row['ratio_fraction']),
        'observational_basis': 'Reverberation-mapped BLR line widths and lag measurements.',
    })

# Assemble final JSON
final = {
    'study': {
        'title': 'CR01 Redshift Decomposition',
        'theory': 'Spatial Displacement Theory',
        'date': '2026-09-24',
        'source_datasets': ['SNe Ia', 'Galaxy Clusters', 'AGN/BLR', 'Scale hierarchy'],
        'methodology': 'Six-layer redshift decomposition including stellar gravity, host galaxy gravity, host rotation, Solar motion, MW bulk motion, and cosmological residual.',
        'summary_fields': ['study_id', 'source_class', 'source_name', 'z_total', 'z_star_grav', 'z_galaxy_grav', 'z_rotation_host', 'z_sun_galactic', 'z_MW_bulk', 'z_cosmo', 'H0_corrected', 'delta_v_kms', 'tau_days', 'r_BLR_lt_d', 'z_grav_BLR', 'z_grav_to_total_fraction', 'observational_basis'],
    },
    'summary': {
        'sne_h0_correction': sne_summary['summary'],
        'zladder_summary': zladder['summary'],
    },
    'datasets': {
        'sne_h0_correction': sne_summary,
        'zladder': zladder,
        'agn_grav_systematic': agn,
        'unified_scale_hierarchy': unified,
    },
    'flattened_records': all_rows,
}

(outdir / 'sdt-cr01-results.json').write_text(json.dumps(final, indent=2, ensure_ascii=False), encoding='utf-8')

fieldnames = [
    'study_id', 'source_class', 'source_name', 'source_dataset', 'study_section',
    'z_total', 'z_star_grav', 'z_galaxy_grav', 'z_rotation_host', 'z_sun_galactic',
    'z_MW_bulk', 'z_cosmo', 'H0_corrected', 'delta_v_kms', 'tau_days', 'r_BLR_lt_d',
    'z_grav_BLR', 'z_grav_to_total_fraction', 'observational_basis'
]
with (outdir / 'sdt-cr01-results.csv').open('w', newline='', encoding='utf-8') as fh:
    writer = csv.DictWriter(fh, fieldnames=fieldnames)
    writer.writeheader()
    for row in all_rows:
        writer.writerow({k: row.get(k, '') for k in fieldnames})

print(f'Wrote {outdir / "sdt-cr01-results.json"}')
print(f'Wrote {outdir / "sdt-cr01-results.csv"}')
print(f'Flattened rows: {len(all_rows)}')
