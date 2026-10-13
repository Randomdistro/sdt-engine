"""Freeze read-only inputs; create records only inside this continuation run."""
from pathlib import Path
import datetime, hashlib, json, subprocess

RUN = Path(__file__).resolve().parent
ROOT = RUN.parents[2]
def digest(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()
def git(*args):
    p = subprocess.run(['git', '-c', 'core.excludesFile=NUL', *args], cwd=ROOT,
                       capture_output=True, text=True, encoding='utf-8')
    if p.returncode:
        raise RuntimeError(p.stderr)
    return p.stdout.strip()

files = set()
for d in ['Engine/include', 'Release/SDT_Celestial_Three_Body_Solver/src',
          'Release/SDT_Celestial_Three_Body_Solver/include',
          'Release/SDT_Celestial_Three_Body_Solver/datasets',
          'Release/SDT_Celestial_Three_Body_Solver/contracts',
          'Release/SDT_Celestial_Three_Body_Solver/examples',
          'Release/SDT_Celestial_Three_Body_Solver/tests',
          'Investigations/01_Foundations_and_Lattice_Mechanics/FLM15_Influx_Phase_Resistance_Ratio',
          'Investigations/05_Nuclear_Physics/NSEQ16_Perfect_Traction_Gear_Engine',
          'Investigations/05_Nuclear_Physics/NSEQ17_Light_Nucleus_Wake_Mesh',
          'Investigations/05_Nuclear_Physics/NSEQ18_Universal_Interstitial_Sequencer',
          'Investigations/05_Nuclear_Physics/NP04_Neutron_Genesis_to_Tritium']:
    files.update(p for p in (ROOT/d).rglob('*') if p.is_file() and '__pycache__' not in p.parts)
for rel in ['Release/SDT_Celestial_Three_Body_Solver/CMakeLists.txt',
            'Release/SDT_Celestial_Three_Body_Solver/QUALIFICATION_MANIFEST.json',
            'Release/HTML_SDT_Website/js/traction-gear-engine.js',
            'Release/HTML_SDT_Website/js/nuclear-inputs.js',
            'Release/HTML_SDT_Website/nuclear-packing-sequencer.html',
            'docs/js/traction-gear-engine.js', 'docs/js/nuclear-inputs.js',
            'Investigations/05_Nuclear_Physics/pack_nucleus.py',
            'Investigations/HUNTER_PROTOCOL.md', 'Investigations/PROMPT_EXECUTION_PROTOCOL.md',
            'Investigations/PERFECT_PROMPT_TEMPLATE.md', 'Audits/atomica_n82_fission_stocktake.md']:
    files.add(ROOT/rel)
files.update(p for p in RUN.parent.iterdir() if p.is_file() and p.name != 'RUN_LOG.md')
frozen = {p.relative_to(ROOT).as_posix(): {'sha256':digest(p), 'bytes':p.stat().st_size}
          for p in sorted(files)}
canonical = frozen['Engine/include/sdt/laws.hpp']['sha256']
solver = frozen['Release/SDT_Celestial_Three_Body_Solver/include/sdt/laws.hpp']['sha256']
old = json.loads((ROOT/'Release/SDT_Celestial_Three_Body_Solver/QUALIFICATION_MANIFEST.json').read_text(encoding='utf-8'))
data = {'schema':'sdt-continuation-source-freeze-1', 'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'head':git('rev-parse','HEAD'), 'branch':git('branch','--show-current'),
        'status':git('status','--porcelain'), 'files':frozen,
        'canonical_solver_laws_equal':canonical==solver, 'old_manifest_laws_sha256':old['laws_sha256'],
        'canonical_laws_sha256':canonical, 'solver_laws_sha256':solver,
        'new_physical_fit_budget':0, 'prior_targets_known':True}
if (RUN/'SOURCE_FREEZE.json').exists():
    raise RuntimeError('Continuation freeze already exists; preserve the existing run.')
(RUN/'SOURCE_FREEZE.json').write_text(json.dumps(data,indent=2)+'\n',encoding='utf-8')
with (RUN.parent/'RUN_LOG.md').open('a',encoding='utf-8') as log:
    log.write('\n\n## 2026-10-03 — authorised full continuation\n\n'
              'Operator instruction `ok run it please` authorises the requested investigation. '
              'Existing Phase 0 artifacts remain preserved. PRECOMMIT.md in '
              '`run_2026-10-03_continuation/` records ADJ-001 through ADJ-004 and numeric gates '
              'before new implementation or execution. Sources are frozen in the continuation '
              'SOURCE_FREEZE.json. Native rebuild and construction validators run inside the '
              'continuation; no separate approval is inferred for authorised reversible checks.\n')
print(json.dumps({'head':data['head'],'protected_files':len(frozen),
                  'canonical_solver_laws_equal':canonical==solver,'historical_manifest_current':old['laws_sha256']==canonical},indent=2))
