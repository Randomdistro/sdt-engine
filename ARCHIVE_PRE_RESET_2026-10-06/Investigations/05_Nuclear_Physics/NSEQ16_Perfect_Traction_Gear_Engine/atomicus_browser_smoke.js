'use strict';

const path = require('path');
const root = path.resolve(__dirname, '..', '..', '..');
const release = path.join(root, 'Release', 'HTML_SDT_Website');

const listeners = new Map();
function makeElement(id, value = '') {
  const ownListeners = {};
  const element = {
    id,
    value,
    style: {},
    dataset: {},
    options: [],
    selectedIndex: 0,
    innerHTML: '',
    textContent: '',
    classList: {
      toggle() {},
      add() {},
      remove() {}
    },
    addEventListener(type, callback) {
      (ownListeners[type] ||= []).push(callback);
    },
    dispatch(type, event = {}) {
      for (const callback of ownListeners[type] || []) callback(event);
    },
    setAttribute() {},
    closest() {
      return { style: {} };
    }
  };
  listeners.set(id, ownListeners);
  return element;
}

const context = {
  setTransform() {},
  clearRect() {},
  fillRect() {},
  beginPath() {},
  moveTo() {},
  lineTo() {},
  stroke() {},
  arc() {},
  fill() {},
  fillText() {},
  createRadialGradient() {
    return { addColorStop() {} };
  }
};

const elements = {
  scene: Object.assign(makeElement('scene'), {
    getContext: () => context,
    getBoundingClientRect: () => ({ width: 1100, height: 760 }),
    setPointerCapture() {},
    releasePointerCapture() {}
  }),
  readout: makeElement('readout'),
  stepCopy: makeElement('stepCopy'),
  sceneNote: makeElement('sceneNote'),
  playBtn: makeElement('playBtn'),
  resetBtn: makeElement('resetBtn'),
  elementSelect: makeElement('elementSelect', 'He4'),
  nbodySelect: makeElement('nbodySelect', 'figure8'),
  tractionSelect: makeElement('tractionSelect', 'C12'),
  topologySelect: makeElement('topologySelect', 'braid'),
  rule18Btn: makeElement('rule18Btn'),
  materialMode: makeElement('materialMode', 'mass'),
  speed: makeElement('speed', '1'),
  layers: makeElement('layers', '1'),
  alignment: makeElement('alignment', '.65'),
  speedOut: makeElement('speedOut'),
  layerOut: makeElement('layerOut'),
  alignOut: makeElement('alignOut'),
  gearValue: makeElement('gearValue')
};
elements.nbodySelect.options = [
  { text: 'Figure eight' },
  { text: 'Stable Lagrange' },
  { text: 'Two-body limit' },
  { text: 'Material-aware SDT · Li/U' }
];

const stepNames = [
  'rotor',
  'mesh',
  'traction',
  'gear',
  'electron',
  'atom',
  'materials',
  'nbody'
];
const stepButtons = stepNames.map(name => {
  const button = makeElement(`step-${name}`);
  button.dataset.step = name;
  return button;
});

const documentListeners = {};
global.window = global;
global.document = {
  getElementById(id) {
    return elements[id] || makeElement(id);
  },
  querySelectorAll(selector) {
    return selector === '.step' ? stepButtons : [];
  },
  addEventListener(type, callback) {
    (documentListeners[type] ||= []).push(callback);
  }
};
global.devicePixelRatio = 1;
global.addEventListener = () => {};
global.performance = { now: () => 0 };

const animationQueue = [];
global.requestAnimationFrame = callback => {
  animationQueue.push(callback);
  return animationQueue.length;
};

require(path.join(release, 'js', 'pack-nucleus.js'));
require(path.join(release, 'js', 'nuclear-inputs.js'));
require(path.join(release, 'js', 'traction-gear-engine.js'));
require(path.join(release, 'atomicus-3d.js'));

let now = 0;
function render(frames = 1) {
  for (let i = 0; i < frames; i++) {
    const callback = animationQueue.shift();
    if (!callback) throw new Error('animation queue unexpectedly empty');
    now += 16;
    callback(now);
  }
}

function selectStep(name) {
  const button = stepButtons.find(item => item.dataset.step === name);
  button.dispatch('click');
  render();
}

for (const name of stepNames) selectStep(name);

for (const isotope of Object.keys(global.SDT_TRACTION_GEAR.presets)) {
  elements.tractionSelect.value = isotope;
  elements.tractionSelect.dispatch('change');
  selectStep('traction');
}
for (const topology of ['braid', 'trefoil']) {
  elements.topologySelect.value = topology;
  elements.topologySelect.dispatch('change');
  selectStep('traction');
  if (
    topology === 'braid'
    && (
      !elements.readout.innerHTML.includes('(4,5)')
      || !elements.readout.innerHTML.includes('0→1→2→3→0')
    )
  ) {
    throw new Error('cyclic quadruple-helix diagnostics were not rendered');
  }
}

const atomicusElements = ['H1', 'He4', 'Li7', 'Be9', 'B11', 'C12', 'N14', 'O16'];
for (const element of atomicusElements) {
  elements.elementSelect.value = element;
  elements.elementSelect.dispatch('change');
  selectStep('mesh');
  selectStep('atom');
  if (!elements.readout.innerHTML.includes('ATOMICUS_CONTACT_CONSTRUCTION_CANDIDATE')) {
    throw new Error(`${element} atom view did not use the Atomicus contact candidate`);
  }
}
for (const element of ['Fe56', 'U238']) {
  elements.elementSelect.value = element;
  elements.elementSelect.dispatch('change');
  selectStep('mesh');
  selectStep('atom');
  if (!elements.readout.innerHTML.includes('LEGACY_GEOMETRIC_CONTROL')) {
    throw new Error(`${element} atom view did not mark the legacy fallback`);
  }
}
elements.rule18Btn.dispatch('click');
selectStep('atom');

for (const comparison of ['mass', 'size']) {
  elements.materialMode.value = comparison;
  elements.materialMode.dispatch('change');
  selectStep('materials');
  elements.nbodySelect.value = 'material';
  elements.nbodySelect.selectedIndex = 3;
  elements.nbodySelect.dispatch('change');
  selectStep('nbody');
  render(8);
}

for (const [index, scene] of ['figure8', 'lagrange', 'binary'].entries()) {
  elements.nbodySelect.value = scene;
  elements.nbodySelect.selectedIndex = index;
  elements.nbodySelect.dispatch('change');
  selectStep('nbody');
  render(8);
}

if (!elements.readout.innerHTML) throw new Error('readout was not populated');
console.log(
  `PASS Atomicus DOM smoke: ${stepNames.length} steps, `
  + `${Object.keys(global.SDT_TRACTION_GEAR.presets).length} traction isotopes, `
  + `${atomicusElements.length} H–O atom stages, `
  + 'cyclic (4,5) braid + trefoil control, both marked heavy fallbacks, '
  + 'all N-body presets and both material comparisons'
);
