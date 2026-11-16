'use strict';
const fs=require('fs'),path=require('path'),crypto=require('crypto');
const repo=path.resolve(__dirname,'../../..'),parent=path.dirname(repo);
const roots=[repo,...['sdt-investigations','sdt-website','SDT solar system','Spatial_displacement_theoriser'].map(n=>path.join(parent,n))];
const omit=new Set(['.git','node_modules','.venv','venv','myenv','__pycache__','.pytest_cache']);
const text=new Set(['.md','.txt','.cpp','.hpp','.h','.c','.cc','.cxx','.py','.js','.cjs','.mjs','.ts','.tsx','.jsx','.html','.htm','.json','.jsonl','.csv','.tsv','.yaml','.yml','.xml','.tex','.rst','.log','.ps1','.bat','.sh','.sql','.toml','.lbl','.cat']);
const records=[],errors=[],excluded=[];let id=0;
function walk(dir){let entries;try{entries=fs.readdirSync(dir,{withFileTypes:true});}catch(e){errors.push({path:dir,error:e.code});return;}
 for(const e of entries){const p=path.join(dir,e.name);if(p===__dirname)continue;if(e.isDirectory()){if(omit.has(e.name)){excluded.push({path:p,reason:'runtime/dependency or VCS metadata'});continue;}walk(p);continue;}if(!e.isFile()){records.push({path:p,kind:'link-or-special',state:'pending'});continue;}
  try{const st=fs.statSync(p),ext=path.extname(p).toLowerCase();let kind=text.has(ext)?'text':(/\.(pdf|docx?|xlsx?|pptx?|odt)$/.test(ext)?'document':(/\.(zip|7z|rar|gz|tar)$/.test(ext)?'archive':(/\.(png|jpg|jpeg|svg|webp|gif)$/.test(ext)?'image':'binary-or-other')));
   const r={id:++id,path:p,relative_to_desktop:path.relative(parent,p).replaceAll('\\','/'),bytes:st.size,modified:st.mtime.toISOString(),kind,state:'discovered'};
   if(kind==='text'){const b=fs.readFileSync(p);r.sha256=crypto.createHash('sha256').update(b).digest('hex');r.lines=b.toString('utf8').split('\n').length;r.has_nul=b.includes(0);if(r.has_nul)r.kind='encoding-or-binary-review';}
   records.push(r);
  }catch(e){errors.push({path:p,error:e.code||e.message});}
 }
}
for(const r of roots)walk(r);
const groups={};for(const r of records)if(r.sha256)(groups[r.sha256]??=[]).push(r.id);
const unique=Object.keys(groups).length;
const counts={};for(const r of records){counts[r.kind]??={files:0,bytes:0};counts[r.kind].files++;counts[r.kind].bytes+=r.bytes||0;}
const inv={created:'2026-10-27',roots,counts,unique_hashed_contents:unique,duplicate_groups:Object.entries(groups).filter(([h,ids])=>ids.length>1).map(([sha256,ids])=>({sha256,ids})),excluded,errors,records};
fs.writeFileSync(path.join(__dirname,'inventory.json'),JSON.stringify(inv,null,2));
console.log(JSON.stringify({roots,counts,unique_hashed_contents:unique,duplicate_groups:inv.duplicate_groups.length,errors},null,2));
