from pathlib import Path
import json,re,shutil
root=Path.cwd(); site=root/'Release/HTML_SDT_Website'
archive=root/'_archive/website/2026-09-22'; archive.mkdir(parents=True,exist_ok=True)
for name in ['sdt-canon.js','theory.html','causal-chain.html','sdt-shell.js']:
 shutil.copyfile(site/name,archive/name)
p=site/'sdt-canon.js'; text=p.read_text(encoding='utf-8'); start=text.index('    primitives: ['); end=text.index('\n    glyphs:',start)
primitives=[
 dict(ord='The first irreducible',name='Space',sdt='The superfluidic hypercrystal',brief='SDT describes space as a particulate medium. Spations constrain material forms and transfer movement through neighbouring contacts.',facets=[['As a fluid','The medium is proposed to rearrange without viscosity. Collective rearrangement allows displacement while individual spations remain incompressible.'],['As a crystal','The lattice description concerns local packing and contact geometry. Packing constraints and defects must be distinguished from a completed dynamical model.'],['As a relay','Radiation is described as contact-mediated transfer at c. The contact and medium-response laws remain necessary for a quantitative microscopic account.']]),
 dict(ord='The second irreducible',name='Matter',sdt='Constrained material form',brief='Matter has a boundary and displaces the surrounding medium. Spation constraint maintains the form; winding alone does not establish self-sustaining matter.',facets=[['Structure','The proton is assigned a continuous (2,3) trefoil structure. A geometric description specifies a path, while physical tube width and contact response require separate definitions.'],['Displacement','Displaced volume, geometrical envelope volume and engaged volume describe different quantities. A shared input does not make the resulting calculations independent predictions.'],['Boundary scale','The measured proton boundary radius and the proposed relation R_p = 4ℏ/(m_p c) have different evidential roles. Numerical agreement does not complete the derivation of the factor four.']]),
 dict(ord='The third irreducible',name='Movement',sdt='Transfer and actuation',brief='Movement includes material motion and contact-mediated transfer. Available freedom describes capacity; actual movement describes actuation.',facets=[['The movement budget','Law V imposes v_circ² + v² = c². Increasing translation reduces the circulation component under the assumed budget.'],['Conditional consequences','Clock-rate and length relations require a stated mapping from the movement budget to the measuring apparatus. Algebraic closure alone is not an independent experiment.'],['The unresolved mechanism','Structural freedom, contact actuation and measured response remain separate until a physical law connects the quantities.']]),
 dict(ord='The fourth irreducible',name='The Ever-Present Now',sdt='Present existence',brief='The Ever-Present Now names the present existence of matter, space and movement. Clocks measure accumulated physical change.',facets=[['Time as a count','Elapsed time is represented through counts of physical processes. Past records and future expectations do not constitute additional material locations.'],['Physical clocks','A clock comparison requires a specified process, trajectory and measurement protocol. The ontology alone does not supply a clock-rate prediction.'],['An open question','The relationship between irreversible records and reversible mathematical descriptions requires a physical account of the relay.']])]
text=text[:start]+'    primitives: '+json.dumps(primitives,ensure_ascii=False,indent=6)+',\n'+text[end:]
a=text.index('    laws: ['); b=text.index('\n  };',a)
laws=[('I','Cosmological Relay Throughput','Law I proposes a cosmological relay throughput. The shell construction and the physical normalisation must be assessed separately.'),('II','The Release Cascade','Law II describes release across pressure domains. The mechanism must specify the boundary and transfer conditions for each domain.'),('III','Convergent Boundary Pressure','Law III relates occlusion geometry to a pressure imbalance. An inverse-square factor does not independently determine the effective pressure or coupling coefficient.'),('IV','Inertial Mass from Throughput Asymmetry','Law IV attributes inertia to the response of the medium to changing material motion. A quantitative contact-response derivation remains required.'),('V','The Movement Budget','Law V imposes v_circ² + v² = c². The equation defines the assumed partition between circulation and translation.'),('VI','Vortex Topology Quantisation','Law VI assigns particle structures to closed winding modes. The proton uses the (2,3) trefoil; topology alone does not establish a stability law.')]
text=text[:a]+'    laws: '+json.dumps([dict(n=n,name=name,one=one) for n,name,one in laws],ensure_ascii=False,indent=6)+text[b:]
p.write_text(text,encoding='utf-8')
p=site/'theory.html';text=p.read_text(encoding='utf-8')
text=text.replace('A complete physics · one dependency chain · Melbourne','A physical framework · mechanisms and evidence · Melbourne')
text=text.replace('Space. Matter. Movement. The Ever-Present Now. Every mechanism below must be built from these four, in that order, without importing a second physical substance.','SDT begins with four irreducibles: space, matter, movement and the Ever-Present Now. The dependency chain connects the proposed mechanisms to calculations, observations and unresolved physical laws.')
text=text.replace('Read the open debts','Read the unresolved questions')
for ident,name in [('ix-space','Space'),('ix-matter','Matter'),('ix-move','Movement'),('ix-now','The Ever-Present Now')]:
 pat=r'(<article class="irreducible" id="'+ident+r'">)(.*?)(</article>)'
 match=re.search(pat,text,re.S); body=match.group(2)
 body=re.sub(r'<p>(.*?)</p>','',body,flags=re.S)
 body=re.sub(r'(<p class="role">).*?(</p>)',lambda m:m[1]+next(x['sdt'] for x in primitives if x['name']==name)+m[2],body,flags=re.S)
 brief=next(x['brief'] for x in primitives if x['name']==name)
 body=re.sub(r'(</p>)',r'\1\n      <p data-sdt-canon-item="'+name+'">'+brief+'</p>',body,count=1)
 text=text[:match.start()]+match[1]+body+match[3]+text[match.end():]
text=text.replace('<script src="theory.js" defer></script>','<script src="sdt-canon.js" defer></script>\n<script src="theory.js" defer></script>')
text=text.replace('A material particle is modelled as a self-maintaining circulation in the substrate.','A material particle is described as a solid form maintained by spation constraint.')
text=text.replace('Matter: persistent circulation that displaces','Matter: constrained form and displacement')
text=text.replace('The complete load path','The dependency structure')
text=text.replace('<main>','<main>\n<aside class="theory-foundations" aria-label="Evidence boundaries"><h2>Reading the mechanisms</h2><p>The ontology specifies seven levels: point, line, plane, sphere, torus, dynamism and energy. The aspect count is 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. Levels 1–6 describe structure and available freedom; level 7 describes expression as movement. The count does not supply a contact law.</p><p>Interactive sketches illustrate proposed mechanisms. Animation does not establish physical validation. <a href="demonstrations.html">Selected mathematical demonstrations</a> state assumptions and limits explicitly. Benchmark identities, calibrated comparisons and independent predictions remain separate.</p></aside>',1)
p.write_text(text,encoding='utf-8')
(site/'causal-chain.html').write_text('''<!DOCTYPE html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><meta name="robots" content="noindex"><meta http-equiv="refresh" content="0;url=theory.html"><link rel="canonical" href="https://spatialdisplacementtheory.com/theory"><title>SDT theory</title></head><body><p>The causal chain is maintained in the <a href="theory.html">theory and evidence account</a>.</p></body></html>
''',encoding='utf-8')
for name in ['causal-chain-simple.html','sdt-shell.js','sdt-register.js']:
 p=site/name; t=p.read_text(encoding='utf-8').replace("'causal-chain.html'","'theory.html'").replace('href="causal-chain.html"','href="theory.html"')
 if name=='sdt-shell.js':
  a=t.index("    lab: ['Lab', [");b=t.index("    bench:",a)
  t=t[:a]+"    lab: ['Demonstrations', [\n      ['Reviewed mathematical scope', [\n        ['Geometry and movement', 'demonstrations.html']\n      ]]\n    ]],\n"+t[b:]
  line="        ['Interactive experiment catalogue', 'experiments.html']"
  t=t.replace(line+',\n'+line+',\n'+line,line)
  t=t.replace("        ['Interactive causal chain', 'theory.html'],\n",'')
  t=t.replace("    'theory.html': 'simple',\n",'')
  t=t.replace("simple: 'theory.html'","simple: 'causal-chain-simple.html'")
 p.write_text(t,encoding='utf-8')
p=site/'index.html'; t=p.read_text(encoding='utf-8').replace('The whole framework now follows one dependency chain: four irreducibles, six laws, matter, atoms, fluids, gravity, the cyclic cosmos, the instruments, and every open debt.','SDT asks how material form and a particulate medium could produce the observed behaviour of matter. Explore the proposed mechanisms, inspect the calculations, and follow the questions that remain unresolved.').replace('Open-debt ledger','Unresolved questions').replace('<a href="benchmarks.html">','<a href="demonstrations.html">Selected demonstrations</a>\n<a href="benchmarks.html">');p.write_text(t,encoding='utf-8')
p=root/'README.md'; t=p.read_text(encoding='utf-8'); p.write_text('> **Current navigation:** [Repository map](REPOSITORY_MAP.md). Website source: `Release/HTML_SDT_Website/`; `docs/` is generated with `python Release/build_site.py`.\n> **Historical release account below:** dated claims and benchmark totals require current source and execution checks before reuse.\n\n'+t,encoding='utf-8')
