#!/usr/bin/env python3
"""Rebuild each public tree's compact search index from its current HTML."""

from __future__ import annotations

import argparse
import json
import re
from html.parser import HTMLParser
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SITES = (
    ROOT / "Release" / "HTML_SDT_Website",
    ROOT / "docs",
)
EXCLUDED_PAGES = {
    "404.html",
    "offline.html",
    "welcome.html",
    "causal-chain.html",
    "atlas.html",
    "sdt_walkthrough.html",
    "atomicus-lab-subdued.html",
    "atomicus-lab-v4-tiers.html",
    "atomicus-v1-snapshot.html",
    "atomicus-stick.html",
    "atomicus-stick-v3-polar-caps.html",
    "atomicus-construction-zone.html",
    "atomicus-nuclear-model.html",
    "monoisotopic-morph.html",
    "nuclear-packing-sequencer-raw.html",
}
SKIPPED_TAGS = {"script", "style", "template", "noscript", "svg", "canvas"}
HEADING_TAGS = {"h1", "h2", "h3"}


def compact(value: str) -> str:
    return re.sub(r"\s+", " ", value).strip()


class SearchExtractor(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.skip_depth = 0
        self.title_depth = 0
        self.heading_depth = 0
        self.title_parts: list[str] = []
        self.heading_parts: list[str] = []
        self.current_heading: list[str] = []
        self.body_parts: list[str] = []

    def handle_starttag(
        self, tag: str, attrs: list[tuple[str, str | None]]
    ) -> None:
        del attrs
        if tag in SKIPPED_TAGS:
            self.skip_depth += 1
        if self.skip_depth:
            return
        if tag == "title":
            self.title_depth += 1
        if tag in HEADING_TAGS:
            self.heading_depth += 1
            self.current_heading = []

    def handle_endtag(self, tag: str) -> None:
        if tag in SKIPPED_TAGS and self.skip_depth:
            self.skip_depth -= 1
            return
        if self.skip_depth:
            return
        if tag == "title" and self.title_depth:
            self.title_depth -= 1
        if tag in HEADING_TAGS and self.heading_depth:
            heading = compact(" ".join(self.current_heading))
            if heading:
                self.heading_parts.append(heading)
            self.current_heading = []
            self.heading_depth -= 1

    def handle_data(self, data: str) -> None:
        if self.skip_depth:
            return
        value = compact(data)
        if not value:
            return
        self.body_parts.append(value)
        if self.title_depth:
            self.title_parts.append(value)
        if self.heading_depth:
            self.current_heading.append(value)

    def entry(self, url: str) -> dict[str, str]:
        title = compact(" ".join(self.title_parts))
        headings = " | ".join(dict.fromkeys(self.heading_parts))
        body = compact(" ".join(self.body_parts))
        return {
            "u": url,
            "t": title[:240],
            "h": headings[:1200],
            "b": body[:1400],
        }


def build(site: Path) -> list[dict[str, str]]:
    entries: list[dict[str, str]] = []
    for path in sorted(site.glob("*.html"), key=lambda item: item.name.lower()):
        if path.name in EXCLUDED_PAGES:
            continue
        extractor = SearchExtractor()
        extractor.feed(path.read_text(encoding="utf-8", errors="replace"))
        entry = extractor.entry(path.name)
        if entry["t"] or entry["h"] or entry["b"]:
            entries.append(entry)
    return entries


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "sites",
        nargs="*",
        type=Path,
        help="site roots; defaults to Release/HTML_SDT_Website and docs",
    )
    args = parser.parse_args()
    sites = tuple(path.resolve() for path in args.sites) or DEFAULT_SITES

    for site in sites:
        entries = build(site)
        output = site / "search-index.json"
        output.write_text(
            json.dumps(entries, ensure_ascii=False, separators=(",", ":")) + "\n",
            encoding="utf-8",
        )
        print(f"{site.relative_to(ROOT).as_posix()}: {len(entries)} pages")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
