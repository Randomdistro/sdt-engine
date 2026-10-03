#!/usr/bin/env python3
"""Generate the deployment mirror from the sole website authoring tree."""
from __future__ import annotations

import argparse
import re
from html import escape
import shutil
from pathlib import Path

from build_search_index import build
from build_paper_manifests import build_site as build_papers
import json

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'Release/HTML_SDT_Website'
OUTPUT = ROOT / 'docs'


def inventory(root):
    return {p.relative_to(root): p for p in root.rglob('*') if p.is_file()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true', help='Fail on any generated-file drift.')
    args = parser.parse_args()
    # Static fallbacks and JS-enabled views share the same authored definitions.
    canon_text = (SOURCE / 'sdt-canon.js').read_text(encoding='utf-8')
    primitives = json.JSONDecoder().raw_decode(canon_text.split('primitives: ', 1)[1])[0]
    definitions = {item['name']: item['brief'] for item in primitives}
    theory_path = SOURCE / 'theory.html'
    theory = theory_path.read_text(encoding='utf-8')
    rendered = re.sub(r'(<p data-sdt-canon-item="([^"]+)">).*?(</p>)',
                      lambda m: m[1] + escape(definitions[m[2]]) + m[3], theory)
    if args.check and rendered != theory:
        raise SystemExit('Primitive fallbacks are stale. Run python Release/build_site.py.')
    if not args.check:
        theory_path.write_text(rendered, encoding='utf-8')
        build_papers(SOURCE)
    expected_search = json.dumps(build(SOURCE), ensure_ascii=False, separators=(',', ':')) + '\n'
    search = SOURCE / 'search-index.json'
    if args.check and search.read_text(encoding='utf-8') != expected_search:
        raise SystemExit('Search index is stale. Run python Release/build_site.py.')
    if not args.check:
        search.write_text(expected_search, encoding='utf-8')
    source, output = inventory(SOURCE), inventory(OUTPUT)
    extra = sorted(set(output) - set(source))
    # Unexpected files may be operator work. Never silently remove mirror-only files.
    if extra:
        raise SystemExit('Mirror-only files require explicit reconciliation: ' + ', '.join(map(str, extra)))
    changed = [name for name, path in source.items()
               if name not in output or path.read_bytes() != output[name].read_bytes()]
    if args.check and changed:
        raise SystemExit('Deployment mirror differs: ' + ', '.join(map(str, changed)))
    for name in changed:
        target = OUTPUT / name
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(source[name], target)
    print(f'PASS: {len(source)} website files; {len(changed)} updated; complete mirror verified.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
