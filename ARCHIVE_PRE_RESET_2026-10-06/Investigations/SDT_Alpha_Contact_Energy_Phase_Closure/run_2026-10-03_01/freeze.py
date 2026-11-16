from pathlib import Path
import hashlib,json,subprocess,datetime
RUN=Path(__file__).resolve().parent
ROOT=RUN.parents[2]
dirs=['Engine/include','Release/HTML_SDT_Website/js','Investigations/01_Foundations_and_Lattice_Mechanics/FLM15_Influx_Phase_Resistance_Ratio','Investigations/05_Nuclear_Physics/NSEQ16_Perfect_Traction_Gear_Engine','Investigations/05_Nuclear_Physics/NSEQ17_Light_Nucleus_Wake_Mesh','Investigations/05_Nuclear_Physics/NSEQ18_Universal_Interstitial_Sequencer','Investigations/05_Nuclear_Physics/NP06_Gear_Frequency_Binding_Functional','Investigations/05_Nuclear_Physics/NP17_Nuclear_Packing_Order_Discovery']
files={p for d in dirs for p in (ROOT/d).rglob('*') if p.is_file() and '__pycache__' not in p.parts}
files.update(ROOT/p for p in ['Investigations/HUNTER_PROTOCOL.md','Investigations/PERFECT_PROMPT_TEMPLATE.md','Investigations/PROMPT_EXECUTION_PROTOCOL.md','Investigations/SDT_Alpha_Contact_Energy_Phase_Closure/PROMPT.md'])
git=lambda *a:subprocess.check_output(['git','-c','core.excludesFile=',*a],cwd=ROOT,text=True).strip()
data={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'head':git('rev-parse','HEAD'),'branch':git('branch','--show-current'),'dirty_state':git('status','--porcelain','--ignore-submodules=all'),'files':{p.relative_to(ROOT).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted(files)},'new_fit_budget':0,'known_targets':['alpha binding','alpha magnetic zero','D/T/He3 calibrated observables'],'toolchain':{'python':subprocess.check_output(['py','-3','--version'],text=True).strip(),'node':subprocess.check_output(['node','--version'],text=True).strip()}}
out=RUN/'SOURCE_FREEZE.json'
if out.exists():raise RuntimeError('Existing freeze remains immutable')
out.write_text(json.dumps(data,indent=2)+'\n',encoding='utf8')
with (RUN/'RUN_LOG.md').open('a',encoding='utf8') as f:f.write(f'\nPhase 0 source freeze completed: {len(files)} protected files. NP06 primary frequency-account source located; independently derived mesh frequency remains an owed prerequisite.\n')
print(json.dumps({'protected_files':len(files),'head':data['head']}))
