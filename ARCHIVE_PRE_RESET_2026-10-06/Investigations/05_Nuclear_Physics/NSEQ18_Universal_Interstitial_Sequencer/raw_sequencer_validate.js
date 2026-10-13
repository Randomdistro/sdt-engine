'use strict';

const fs = require('fs');
const path = require('path');
const vm = require('vm');

const root = path.resolve(__dirname, '..', '..', '..');
const pages = [
  path.join(root, 'Release', 'HTML_SDT_Website', 'nuclear-packing-sequencer-raw.html'),
  path.join(root, 'docs', 'nuclear-packing-sequencer-raw.html')
];

for (const page of pages) {
  const html = fs.readFileSync(page, 'utf8');
  const marker = '<script type="module">';
  const start = html.indexOf(marker);
  const end = html.indexOf('</script>', start + marker.length);
  if (start < 0 || end < 0) throw new Error(`module script missing: ${page}`);
  new vm.SourceTextModule(html.slice(start + marker.length, end));
  for (const token of [
    'addP',
    'addN',
    'TransformControls',
    'SDT-RAW-NUCLEAR-SEQUENCER-1',
    'No automatic packing',
    'No claim is made that centre distance proves toroidal rim contact'
  ]) {
    if (!html.includes(token)) throw new Error(`${token} missing: ${page}`);
  }
  for (const forbidden of [
    'buildNuclide(',
    'tritonClosingScale',
    'calculatedBindingMeV'
  ]) {
    if (html.includes(forbidden)) {
      throw new Error(`automatic-model token ${forbidden} present: ${page}`);
    }
  }
  console.log(`PASS ${path.relative(root, page)}`);
}

