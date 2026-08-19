/* ════════════════════════════════════════════════════════════════════════════
   SDT — site-wide language toggle (multi-language)
   An elegant hamburger (top-right) that exchanges the page between English and
   any translated language, flips to right-to-left for Hebrew, and remembers it.

   Per page:
       <script>window.SDT_I18N = { de:{...}, fr:{...}, ... };</script>
       <script src="i18n.js"></script>
   Each dictionary maps an exact English text-node → its translation. Elements
   with inline markup carry  data-i18n="key"  and their translation lives at
   the dictionary key  "@key"  (full HTML).
   ════════════════════════════════════════════════════════════════════════════ */
(function(){
  'use strict';
  var LS='sdt_lang';
  var LANGS=[
    {code:'en',    label:'English'},
    {code:'tp',    label:'Technical Physics'},
    {code:'de',    label:'Deutsch'},
    {code:'fr',    label:'Français'},
    {code:'es',    label:'Español'},
    {code:'ja',    label:'日本語'},
    {code:'zh',    label:'中文'},
    {code:'de-CH', label:'Schweizer Hochdeutsch'},
    {code:'gsw',   label:'Schwiizerdütsch'},
    {code:'he',    label:'עברית'}
  ];
  var RTL={he:1};
  var DICT=window.SDT_I18N||{};

  var CSS = ''+
  /* labelled button (James Christopher Tyndall 2026-07-30: no hamburger — say the word) */
  '.i18n-burger{position:fixed;top:12px;right:16px;z-index:2000;height:36px;padding:0 14px;'+
    'background:rgba(245,240,232,0.86);-webkit-backdrop-filter:blur(9px);backdrop-filter:blur(9px);'+
    'border:1px solid rgba(176,116,48,0.35);border-radius:10px;cursor:pointer;display:flex;'+
    'align-items:center;gap:7px;font-family:"JetBrains Mono",monospace;font-size:11px;'+
    'letter-spacing:.16em;text-transform:uppercase;color:#b07430;'+
    'transition:border-color .25s,box-shadow .25s;box-shadow:0 2px 14px rgba(30,28,24,0.10);}'+
  '.i18n-burger:hover{border-color:#b07430;box-shadow:0 3px 18px rgba(176,116,48,0.18);}'+
  '.i18n-burger .i18n-chev{font-size:9px;transition:transform .3s cubic-bezier(.16,1,.3,1);}'+
  '.i18n-burger.open .i18n-chev{transform:rotate(180deg);}'+
  '.i18n-panel{position:fixed;top:60px;right:16px;z-index:2000;width:210px;max-height:76vh;overflow-y:auto;'+
    'background:rgba(250,246,239,0.98);-webkit-backdrop-filter:blur(14px);backdrop-filter:blur(14px);'+
    'border:1px solid rgba(176,116,48,0.28);border-radius:13px;box-shadow:0 14px 44px rgba(30,28,24,0.20);'+
    'padding:14px;opacity:0;transform:translateY(-8px) scale(.98);pointer-events:none;'+
    'transition:opacity .28s cubic-bezier(.16,1,.3,1),transform .28s cubic-bezier(.16,1,.3,1);'+
    'font-family:Inter,system-ui,sans-serif;}'+
  '.i18n-panel.open{opacity:1;transform:none;pointer-events:auto;}'+
  '.i18n-panel .i18n-hd{font-family:"JetBrains Mono",monospace;font-size:9px;letter-spacing:.18em;'+
    'text-transform:uppercase;color:#7a7265;margin-bottom:10px;}'+
  '.i18n-langs{display:flex;flex-direction:column;gap:5px;}'+
  '.i18n-langs button{text-align:left;padding:9px 12px;border:1px solid rgba(176,116,48,0.26);border-radius:9px;'+
    'background:transparent;cursor:pointer;font-size:13px;color:#3d3830;font-family:inherit;'+
    'transition:background .2s,color .2s,border-color .2s;display:flex;justify-content:space-between;align-items:center;gap:8px;}'+
  '.i18n-langs button:hover{background:rgba(176,116,48,0.08);}'+
  '.i18n-langs button.active{background:#b07430;color:#faf6ef;border-color:#b07430;}'+
  '.i18n-langs button .tick{opacity:0;font-size:11px;}'+
  '.i18n-langs button.active .tick{opacity:1;}'+
  'html[dir=rtl] .i18n-burger{right:auto;left:16px;}'+
  'html[dir=rtl] .i18n-panel{right:auto;left:16px;text-align:right;}'+
  'html[dir=rtl]{text-align:right;}'+
  'html.i18n-ready .backlink{padding-right:66px;}'+
  'html[dir=rtl] .backlink{flex-direction:row-reverse;padding-right:16px;padding-left:66px;}';

  var st=document.createElement('style'); st.textContent=CSS; document.head.appendChild(st);
  document.documentElement.classList.add('i18n-ready');

  var burger=document.createElement('button');
  burger.className='i18n-burger'; burger.type='button';
  burger.setAttribute('aria-label','Language menu · Sprache · שפה');
  burger.innerHTML='Language <span class="i18n-chev">▾</span>';
  var panel=document.createElement('div'); panel.className='i18n-panel';
  var html='<div class="i18n-hd">Language · Sprache · 言語</div><div class="i18n-langs">';
  for(var i=0;i<LANGS.length;i++) html+='<button type="button" data-lang="'+LANGS[i].code+'"><span>'+LANGS[i].label+'</span><span class="tick">✓</span></button>';
  html+='</div>';
  panel.innerHTML=html;
  document.body.appendChild(burger); document.body.appendChild(panel);

  function setOpen(o){ panel.classList.toggle('open',o); burger.classList.toggle('open',o); }
  burger.addEventListener('click',function(e){ e.stopPropagation(); setOpen(!panel.classList.contains('open')); });
  document.addEventListener('click',function(e){ if(!panel.contains(e.target)&&e.target!==burger&&!burger.contains(e.target)) setOpen(false); });
  document.addEventListener('keydown',function(e){ if(e.key==='Escape') setOpen(false); });

  // capture original innerHTML of rich elements
  var els=[].slice.call(document.querySelectorAll('[data-i18n]'));
  els.forEach(function(el){ el.__en=el.innerHTML; });
  // collect translatable text nodes (skip rich elements, scripts, styles, canvas, the menu)
  var nodes=[];
  (function collect(){
    var w=document.createTreeWalker(document.body, NodeFilter.SHOW_TEXT, { acceptNode:function(n){
      var p=n.parentNode; if(!p) return NodeFilter.FILTER_REJECT;
      var tag=p.nodeName.toLowerCase();
      if(tag==='script'||tag==='style'||tag==='canvas') return NodeFilter.FILTER_REJECT;
      if(p.closest&&(p.closest('.i18n-panel')||p.closest('.i18n-burger')||p.closest('[data-i18n]'))) return NodeFilter.FILTER_REJECT;
      return n.nodeValue.trim() ? NodeFilter.FILTER_ACCEPT : NodeFilter.FILTER_REJECT;
    }});
    var n; while((n=w.nextNode())) nodes.push({node:n, en:n.nodeValue});
  })();

  function apply(lang){
    var d = DICT[lang] || {};
    var he = (lang !== 'en');
    nodes.forEach(function(s){ var t=s.en.trim();
      s.node.nodeValue = (he && d[t]!==undefined) ? s.en.replace(t, d[t]) : s.en; });
    els.forEach(function(el){ var key=el.getAttribute('data-i18n');
      el.innerHTML = (he && d['@'+key]!==undefined) ? d['@'+key] : el.__en; });
    document.documentElement.setAttribute('lang', lang);
    document.documentElement.setAttribute('dir', RTL[lang] ? 'rtl' : 'ltr');
    var bs=panel.querySelectorAll('[data-lang]');
    for(var i=0;i<bs.length;i++) bs[i].classList.toggle('active', bs[i].getAttribute('data-lang')===lang);
    try{ localStorage.setItem(LS,lang); }catch(_){}
  }
  var bs=panel.querySelectorAll('[data-lang]');
  for(var j=0;j<bs.length;j++) bs[j].addEventListener('click',(function(l){ return function(){ apply(l); setOpen(false); }; })(bs[j].getAttribute('data-lang')));

  var saved; try{ saved=localStorage.getItem(LS); }catch(_){ saved=null; }
  var startLang = (saved && DICT[saved]!==undefined) ? saved : 'en';
  apply(startLang);

  // ── register with the site shell (2026-07-30) ──────────────────────────
  // The shell bar is fixed at z-index 9000 across the whole top, which buried
  // this module's own fixed button (z-index 2000) — that is why the language
  // control vanished. The shell now renders a Language TAB and drives us
  // through this API. The legacy button is hidden whenever the shell is
  // present, and kept as the fallback when it is not.
  var current = startLang;
  window.SDT_I18N_API = {
    langs: LANGS,
    current: function(){ return current; },
    set: function(code){ current = code; apply(code); setOpen(false); }
  };
  function shellPresent(){ return !!document.querySelector('.sdtq-bar'); }
  function hideLegacy(){
    if (shellPresent()) { burger.style.display='none'; setOpen(false); }
  }
  if (document.readyState === 'loading')
    document.addEventListener('DOMContentLoaded', function(){ setTimeout(hideLegacy, 0); });
  else setTimeout(hideLegacy, 0);
})();
