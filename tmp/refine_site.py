from pathlib import Path
import re,shutil
site=Path('Release/HTML_SDT_Website'); archive=Path('_archive/website/2026-09-22')
for name in ['paper-medium.html','ppt01_scroller.html','causal-chain-technical.html','i18n_dict.js']:
 p=site/name;shutil.copyfile(p,archive/name);t=p.read_text(encoding='utf-8')
 if name=='paper-medium.html':
  t=re.sub(r'<tr><td>Matter</td>.*?</tr>','<tr><td>Matter</td><td>Constrained displacement</td><td>Material form displaces the medium and is maintained by spation constraint. The trefoil describes topology; winding alone does not establish stability. The measured boundary and the proposed W+1 radius relation have separate evidential roles.</td></tr>',t)
  t=re.sub(r'<tr><td>Movement</td>.*?</tr>','<tr><td>Movement</td><td>Transfer and actuation</td><td>Nearest-neighbour transfer propagates at c. Law V imposes v<sub>circ</sub>² + v² = c². Available freedom, actuation and measured response remain distinct.</td></tr>',t)
  t=re.sub(r'<tr><td>The Ever-Present Now</td>.*?</tr>','<tr><td>The Ever-Present Now</td><td>Present existence</td><td>Clocks count physical change. The ontology does not independently specify a clock-rate law or establish simultaneity between separated measurements.</td></tr>',t)
 elif name=='ppt01_scroller.html':
  t=re.sub(r'<p class="opening__desc">.*?</p>','<p class="opening__desc">The torus-mode construction describes circulation around the major ring and the poloidal path. The registered mode partition satisfies the imposed movement budget. Spation constraint maintains material form; the mode equations alone do not establish physical stability.</p>',t,count=1,flags=re.S)
  t=t.replace('Resolved · 5/5','Conditional mode construction')
 elif name=='causal-chain-technical.html':
  t=re.sub(r'<p>A particle is circulation wound.*?</p>','<p>Matter is described as constrained material form with a boundary. The medium constrains the form, and pressure results from the constraint. A trefoil description specifies topology; a physical contact law must still connect geometry to actuation and response.</p>',t,count=1,flags=re.S)
 else:
  # Retire the obsolete translation pair instead of translating an obsolete claim.
  t=re.sub(r'  "The topology of the lattice permits only certain self-sustaining.*?":\s*".*?",\n','',t,count=1,flags=re.S)
 p.write_text(t,encoding='utf-8')
p=site/'sitemap.xml';t=p.read_text(encoding='utf-8').replace('</urlset>','  <url><loc>https://spatialdisplacementtheory.com/demonstrations</loc><lastmod>2026-09-22</lastmod><changefreq>monthly</changefreq><priority>0.8</priority></url>\n</urlset>');p.write_text(t,encoding='utf-8')
