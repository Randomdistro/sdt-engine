(() => {
  'use strict';

  const get = (object, path) =>
    path.split('.').reduce((value, key) => value?.[key], object);

  const format = (value, mode) => {
    if (typeof value !== 'number') return String(value ?? '');
    if (mode === 'integer') return Math.round(value).toLocaleString('en-AU');
    if (mode === 'scientific') return value.toExponential(6);
    if (mode === 'fixed-4') return value.toFixed(4);
    return String(value);
  };

  fetch('dist/sdt-engine-data.json', { cache: 'no-cache' })
    .then(response => {
      if (!response.ok) throw new Error(`engine data ${response.status}`);
      return response.json();
    })
    .then(data => {
      window.SDT_ENGINE_DATA = Object.freeze(data);
      document.documentElement.dataset.sdtEngineData = 'loaded';

      document.querySelectorAll('[data-sdt-benchmark-summary]').forEach(node => {
        const s = data.summary;
        node.textContent =
          `${s.earned_passed}/${s.earned_total} earned predictions passed · ` +
          `${s.identity_passed} IDENTITY · ${s.calibrated_passed} CALIBRATED · ` +
          `${s.pending_note_only} PENDING note-only`;
      });

      document.querySelectorAll('[data-sdt-data]').forEach(node => {
        const value = get(data, node.dataset.sdtData);
        if (value !== undefined) {
          node.textContent = format(value, node.dataset.sdtFormat);
        }
      });

      document.dispatchEvent(new CustomEvent('sdt-engine-data', { detail: data }));
    })
    .catch(error => {
      document.documentElement.dataset.sdtEngineData = 'fallback';
      document.querySelectorAll('[data-sdt-benchmark-summary]').forEach(node => {
        if (!node.textContent.includes('static fallback')) {
          node.textContent += ' · static fallback';
        }
        node.title = 'Live benchmark data could not be loaded; showing embedded fallback text.';
      });
      document.querySelectorAll('[data-sdt-data]').forEach(node => {
        node.title = 'Live engine data unavailable; showing embedded fallback value.';
      });
      document.dispatchEvent(new CustomEvent('sdt-engine-data-fallback', {
        detail: { message: String(error?.message || error) }
      }));
    });
})();
