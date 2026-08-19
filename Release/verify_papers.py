#!/usr/bin/env python3
"""Validate the scientific and citation contract of all public SDT papers."""

from __future__ import annotations

import json
import re
import sys
from html.parser import HTMLParser
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RELEASE = ROOT / "Release" / "HTML_SDT_Website"
DOCS = ROOT / "docs"
ARCHIVE = ROOT / "_archive" / "Website" / "2026-08-18" / "paper-corpus-rewrite"
ALLOWED_STATUS = {
    "AXIOM",
    "DEFINITION",
    "DERIVED",
    "COMPUTED",
    "CALIBRATED",
    "MEASURED-INPUT",
    "OBSERVED",
    "IDENTITY",
    "CONJECTURE",
    "PENDING",
    "OPEN",
    "EXCLUDED",
    "WITHDRAWN",
    "NORMATIVE",
    "SPECIFICATION",
}
REQUIRED_SECTIONS = {
    "scope",
    "definitions",
    "derivation",
    "dimensional-analysis",
    "certification",
    "falsification",
    "limitations",
    "references",
}
PROHIBITED_PROSE = re.compile(
    r"\b(?:charge|charged|charges|killed|honest|pre-commit)\b", re.IGNORECASE
)


class ContractParser(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.main: dict[str, str] = {}
        self.sections: set[str] = set()
        self.equations: list[dict[str, str]] = []
        self.claims: list[dict[str, str]] = []
        self.references: list[dict[str, str]] = []
        self.citations: set[str] = set()
        self.ids: set[str] = set()
        self.duplicate_ids: set[str] = set()
        self.stylesheets: set[str] = set()
        self.inline_style = False
        self._in_reference = False
        self._visible: list[str] = []
        self._reference_text: list[str] = []

    def handle_starttag(
        self, tag: str, attrs: list[tuple[str, str | None]]
    ) -> None:
        values = {key: value or "" for key, value in attrs}
        classes = set(values.get("class", "").split())
        element_id = values.get("id")
        if element_id:
            if element_id in self.ids:
                self.duplicate_ids.add(element_id)
            self.ids.add(element_id)
        if tag == "style":
            self.inline_style = True
        if tag == "link" and values.get("rel") == "stylesheet":
            self.stylesheets.add(values.get("href", ""))
        if tag == "main":
            self.main = values
        if tag == "section" and element_id:
            self.sections.add(element_id)
        if tag == "div" and "eq" in classes:
            self.equations.append(values)
        if tag == "tr" and values.get("data-claim"):
            self.claims.append(values)
        if tag == "li" and (element_id or "").startswith("ref-"):
            self._in_reference = True
            self._reference_text = []
            self.references.append(values)
        if tag == "a" and values.get("href", "").startswith("#ref-"):
            self.citations.add(values["href"][1:])

    def handle_endtag(self, tag: str) -> None:
        if tag == "li" and self._in_reference:
            self._in_reference = False

    def handle_data(self, data: str) -> None:
        if self._in_reference:
            self._reference_text.append(data)
        else:
            self._visible.append(data)

    @property
    def visible_text(self) -> str:
        return " ".join(self._visible)


def audit_site(site: Path) -> list[str]:
    errors: list[str] = []
    papers = sorted(site.glob("paper-*.html"))
    if len(papers) != 25:
        errors.append(f"{site.name}: expected 25 papers, found {len(papers)}")
    for path in papers:
        parser = ContractParser()
        text = path.read_text(encoding="utf-8")
        parser.feed(text)
        label = f"{site.name}/{path.name}"

        if parser.inline_style:
            errors.append(f"{label}: inline style remains")
        if "paper.css" not in parser.stylesheets:
            errors.append(f"{label}: missing paper.css")
        if 'src="paper.js"' not in text:
            errors.append(f"{label}: missing paper.js")
        expected_id = path.stem
        if parser.main.get("data-paper-id") != expected_id:
            errors.append(f"{label}: data-paper-id must be {expected_id}")
        for field in ("data-domain", "data-status", "data-theory-steps"):
            if not parser.main.get(field):
                errors.append(f"{label}: missing {field}")
        missing_sections = sorted(REQUIRED_SECTIONS - parser.sections)
        if missing_sections:
            errors.append(f"{label}: missing sections {missing_sections}")
        if parser.duplicate_ids:
            errors.append(f"{label}: duplicate ids {sorted(parser.duplicate_ids)}")

        for index, equation in enumerate(parser.equations, start=1):
            if equation.get("id") != f"eq-{index}":
                errors.append(f"{label}: equation {index} id is not eq-{index}")
            status = equation.get("data-status", "")
            if status not in ALLOWED_STATUS:
                errors.append(f"{label}: equation {index} invalid status {status!r}")
            if not equation.get("data-source"):
                errors.append(f"{label}: equation {index} missing source")
        if not parser.equations:
            errors.append(f"{label}: no equations")

        if len(parser.claims) < 3:
            errors.append(f"{label}: fewer than three claim-ledger rows")
        for claim in parser.claims:
            status = claim.get("data-status", "")
            if status not in ALLOWED_STATUS:
                errors.append(
                    f"{label}: claim {claim.get('data-claim')} invalid status {status!r}"
                )
            if not claim.get("data-source"):
                errors.append(
                    f"{label}: claim {claim.get('data-claim')} missing source"
                )

        reference_ids = {item.get("id", "") for item in parser.references}
        unused = sorted(reference_ids - parser.citations)
        missing = sorted(parser.citations - reference_ids)
        if unused:
            errors.append(f"{label}: uncited references {unused}")
        if missing:
            errors.append(f"{label}: citations missing references {missing}")
        if len(reference_ids) < 2:
            errors.append(f"{label}: fewer than two cited references")
        for reference in parser.references:
            ref_type = reference.get("data-type", "")
            if ref_type == "repo":
                repo_path = reference.get("data-path", "")
                if not repo_path or not (ROOT / repo_path).exists():
                    errors.append(
                        f"{label}: missing repository reference {repo_path!r}"
                    )
            elif ref_type == "external":
                doi = reference.get("data-doi", "")
                url = reference.get("data-url", "")
                if not doi and not url.startswith("https://"):
                    errors.append(
                        f"{label}: external reference lacks DOI or HTTPS URL"
                    )
            else:
                errors.append(
                    f"{label}: reference {reference.get('id')} invalid type {ref_type!r}"
                )

        match = PROHIBITED_PROSE.search(parser.visible_text)
        if match:
            errors.append(f"{label}: prohibited prose term {match.group(0)!r}")
        if "Prepared for Submission" in text:
            errors.append(f"{label}: unverified submission label remains")

        manifest = site / "manifests" / f"{expected_id}.json"
        if not manifest.exists():
            errors.append(f"{label}: missing generated manifest")

    return errors


def audit_mirrors() -> list[str]:
    errors: list[str] = []
    names = [
        *(path.name for path in RELEASE.glob("paper-*.html")),
        "paper.css",
        "paper.js",
        "paper-catalog.json",
        "paper-bibliography.json",
        "paper-glossary.json",
    ]
    for name in names:
        release = RELEASE / name
        docs = DOCS / name
        if not docs.exists() or release.read_bytes() != docs.read_bytes():
            errors.append(f"mirror mismatch: {name}")
    release_manifests = RELEASE / "manifests"
    docs_manifests = DOCS / "manifests"
    for release in release_manifests.glob("paper-*.json"):
        docs = docs_manifests / release.name
        if not docs.exists() or release.read_bytes() != docs.read_bytes():
            errors.append(f"manifest mirror mismatch: {release.name}")
    return errors


def audit_archive() -> list[str]:
    errors: list[str] = []
    for branch in ("release", "docs"):
        folder = ARCHIVE / branch
        files = sorted(folder.glob("paper-*.html")) if folder.exists() else []
        if len(files) != 25:
            errors.append(f"archive {branch}: expected 25 papers, found {len(files)}")
    return errors


def main() -> int:
    errors = [*audit_site(RELEASE), *audit_site(DOCS), *audit_mirrors(), *audit_archive()]
    if errors:
        for error in errors:
            print(f"FAIL  {error}")
        print(f"\nPAPER AUDIT FAILED: {len(errors)} errors")
        return 1
    print("PASS  paper audit: 25 papers, manifests, citations, equations and mirrors")
    return 0


if __name__ == "__main__":
    sys.exit(main())
