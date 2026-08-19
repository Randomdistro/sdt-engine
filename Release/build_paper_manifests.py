#!/usr/bin/env python3
"""Build machine-readable manifests from the public SDT paper corpus."""

from __future__ import annotations

import json
import re
from html.parser import HTMLParser
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SITES = (ROOT / "Release" / "HTML_SDT_Website", ROOT / "docs")


class PaperParser(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.title_parts: list[str] = []
        self.in_title = False
        self.main: dict[str, str] = {}
        self.equations: list[dict[str, str]] = []
        self.claims: list[dict[str, str]] = []
        self.terms: list[dict[str, str]] = []
        self.references: list[dict[str, str]] = []
        self.sections: list[str] = []
        self.links: list[str] = []
        self._term: dict[str, str] | None = None
        self._reference: dict[str, str] | None = None
        self._text: list[str] = []

    def handle_starttag(
        self, tag: str, attrs: list[tuple[str, str | None]]
    ) -> None:
        values = {key: value or "" for key, value in attrs}
        classes = set(values.get("class", "").split())
        if tag == "title":
            self.in_title = True
        if tag == "main" and values.get("data-paper-id"):
            self.main = values
        if tag == "section" and values.get("id"):
            self.sections.append(values["id"])
        if tag == "div" and "eq" in classes:
            self.equations.append(
                {
                    "id": values.get("id", ""),
                    "status": values.get("data-status", ""),
                    "source": values.get("data-source", ""),
                }
            )
        if tag == "tr" and values.get("data-claim"):
            self.claims.append(
                {
                    "id": values["data-claim"],
                    "status": values.get("data-status", ""),
                    "source": values.get("data-source", ""),
                }
            )
        if tag == "dfn" and values.get("id"):
            self._term = {"id": values["id"], "text": ""}
            self._text = []
        if tag == "li" and values.get("id", "").startswith("ref-"):
            self._reference = {
                "id": values["id"],
                "type": values.get("data-type", ""),
                "path": values.get("data-path", ""),
                "doi": values.get("data-doi", ""),
                "url": values.get("data-url", ""),
                "text": "",
            }
            self._text = []
        if tag == "a" and values.get("href"):
            self.links.append(values["href"])

    def handle_endtag(self, tag: str) -> None:
        if tag == "title":
            self.in_title = False
        if tag == "dfn" and self._term is not None:
            self._term["text"] = " ".join(" ".join(self._text).split())
            self.terms.append(self._term)
            self._term = None
            self._text = []
        if tag == "li" and self._reference is not None:
            self._reference["text"] = " ".join(" ".join(self._text).split())
            self.references.append(self._reference)
            self._reference = None
            self._text = []

    def handle_data(self, data: str) -> None:
        if self.in_title:
            self.title_parts.append(data)
        if self._term is not None or self._reference is not None:
            self._text.append(data)

    def manifest(self, file_name: str) -> dict[str, object]:
        return {
            "schema": "sdt-paper-manifest-1.0.0",
            "id": self.main.get("data-paper-id", ""),
            "file": file_name,
            "title": " ".join(" ".join(self.title_parts).split()),
            "domain": self.main.get("data-domain", ""),
            "status": self.main.get("data-status", ""),
            "theory_steps": self.main.get("data-theory-steps", "").split(),
            "equations": self.equations,
            "claims": self.claims,
            "terms": self.terms,
            "references": self.references,
            "sections": self.sections,
            "cross_references": sorted(
                {
                    href
                    for href in self.links
                    if re.match(r"paper-[^#]+\.html(?:#.*)?$", href)
                }
            ),
        }


def build_site(site: Path) -> None:
    output = site / "manifests"
    output.mkdir(exist_ok=True)
    catalog: list[dict[str, object]] = []
    bibliography: dict[str, dict[str, str]] = {}
    glossary: dict[str, dict[str, str]] = {}

    for path in sorted(site.glob("paper-*.html")):
        parser = PaperParser()
        parser.feed(path.read_text(encoding="utf-8"))
        manifest = parser.manifest(path.name)
        paper_id = str(manifest["id"] or path.stem)
        (output / f"{paper_id}.json").write_text(
            json.dumps(manifest, indent=2, ensure_ascii=False) + "\n",
            encoding="utf-8",
        )
        catalog.append(
            {
                "id": paper_id,
                "file": path.name,
                "title": manifest["title"],
                "domain": manifest["domain"],
                "status": manifest["status"],
                "theory_steps": manifest["theory_steps"],
            }
        )
        for reference in manifest["references"]:  # type: ignore[index]
            bibliography[str(reference["id"])] = reference  # type: ignore[index]
        for term in manifest["terms"]:  # type: ignore[index]
            glossary[str(term["id"])] = {  # type: ignore[index]
                "term": str(term["text"]),  # type: ignore[index]
                "paper": paper_id,
            }

    (site / "paper-catalog.json").write_text(
        json.dumps(
            {"schema": "sdt-paper-catalog-1.0.0", "papers": catalog},
            indent=2,
            ensure_ascii=False,
        )
        + "\n",
        encoding="utf-8",
    )
    (site / "paper-bibliography.json").write_text(
        json.dumps(
            {"schema": "sdt-paper-bibliography-1.0.0", "references": bibliography},
            indent=2,
            ensure_ascii=False,
        )
        + "\n",
        encoding="utf-8",
    )
    (site / "paper-glossary.json").write_text(
        json.dumps(
            {"schema": "sdt-paper-glossary-1.0.0", "terms": glossary},
            indent=2,
            ensure_ascii=False,
        )
        + "\n",
        encoding="utf-8",
    )
    print(f"{site.name}: built {len(catalog)} paper manifests")


def main() -> int:
    for site in SITES:
        build_site(site)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
