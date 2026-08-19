#!/usr/bin/env python3
"""Deterministic local audit for both published SDT website trees."""

from __future__ import annotations

import json
import re
import sys
from collections import Counter
from html import unescape
from html.parser import HTMLParser
from pathlib import Path
from urllib.parse import unquote, urlsplit


ROOT = Path(__file__).resolve().parents[1]
RELEASE = ROOT / "Release" / "HTML_SDT_Website"
DOCS = ROOT / "docs"

MIRRORED_FILES = (
    ".htaccess",
    "404.html",
    "atomicus-3d.html",
    "atomicus-3d.js",
    "atomicus-construction-zone.html",
    "atomicus-lab.html",
    "atomicus-lab-subdued.html",
    "atomicus-lab-v4-tiers.html",
    "atomicus-nuclear-model.html",
    "atomicus-stick.html",
    "atomicus-stick-v3-polar-caps.html",
    "atomicus-v1-snapshot.html",
    "benchmarks.html",
    "benchmarks_scroller.html",
    "causal-chain.html",
    "cq06-eclipse.html",
    "depth_closure_scroller.html",
    "engine-data.js",
    "experiments.html",
    "i18n_dict.js",
    "index.html",
    "laws_scroller.html",
    "main.js",
    "monoisotopic-morph.html",
    "nuclear-packing-sequencer-raw.html",
    "nuclear-packing-sequencer.html",
    "nuclear-packing-walkthrough.html",
    "paper-01-foundations.html",
    "paper-02-particle-topology.html",
    "paper-03-electromagnetism.html",
    "paper-04-atomic-spectroscopy.html",
    "paper-05-nuclear.html",
    "paper-06-gravitation.html",
    "paper-07-cosmology.html",
    "paper-08-galactic.html",
    "paper-09-stellar.html",
    "paper-10-fluid.html",
    "paper-11-thermodynamics.html",
    "paper-12-condensed-matter.html",
    "paper-13-quantum-foundations.html",
    "paper-14-plasma-magnetism.html",
    "paper-15-optics.html",
    "paper-16-chemistry.html",
    "paper-atomicus.html",
    "paper-cosmology.html",
    "paper-engine.html",
    "paper-experiments.html",
    "paper-glossary.html",
    "paper-lab.html",
    "paper-laws.html",
    "paper-medium.html",
    "paper-topology.html",
    "paper.css",
    "paper.js",
    "sdt-canon.js",
    "sdt-for-people.html",
    "sdt-register.js",
    "sdt-shell.js",
    "sdt_walkthrough.html",
    "search-index.json",
    "st_00_primitives.html",
    "st_gom_gravity.html",
    "theoretical-model.html",
    "theory.html",
    "theory.css",
    "theory.js",
    "theory-dependencies.json",
    "theory-redirect.js",
    "universe-lifecycle.html",
    "walk.js",
    "atlas.html",
    "sitemap.xml",
    "welcome.html",
    "js/pack-nucleus.js",
    "js/nuclear-inputs.js",
    "js/traction-gear-engine.js",
    "dist/SDT_benchmarks_output.txt",
    "dist/laws.hpp",
    "dist/sdt-engine-data.json",
)

SUPERSEDED_INBOUND_ROUTES = (
    "welcome.html",
    "causal-chain.html",
    "atlas.html",
    "atomicus-lab-subdued.html",
    "atomicus-lab-v4-tiers.html",
    "atomicus-v1-snapshot.html",
    "atomicus-stick.html",
    "atomicus-stick-v3-polar-caps.html",
    "atomicus-construction-zone.html",
    "atomicus-nuclear-model.html",
    "monoisotopic-morph.html",
    "nuclear-packing-sequencer-raw.html",
)

SITEMAP_EXCLUDED_ROUTES = {
    "welcome",
    "causal-chain",
    "atlas",
    "atomicus-construction-zone",
    "atomicus-lab-subdued",
    "atomicus-lab-v4-tiers",
    "atomicus-nuclear-model",
    "atomicus-stick",
    "atomicus-stick-v3-polar-caps",
    "atomicus-v1-snapshot",
    "monoisotopic-morph",
    "nuclear-packing-sequencer-raw",
}

SITEMAP_REQUIRED_ROUTES = {
    "theory",
    "atomicus-3d",
    "experiments",
    "paper-experiments",
    "sdt-for-people",
    "theoretical-model",
    "universe-lifecycle",
}

TEXT_SUFFIXES = {".html", ".js", ".json", ".xml", ".css", ".cff"}
BINARY_SUFFIXES = {
    ".wasm",
    ".png",
    ".jpg",
    ".jpeg",
    ".gif",
    ".webp",
    ".ico",
    ".woff",
    ".woff2",
    ".ttf",
    ".otf",
    ".eot",
    ".bin",
    ".pdf",
    ".zip",
    ".gz",
}
# Assembled so this file does not contain the contiguous banned token as prose.
PROHIBITED_CHARGE_REIFICATION = re.compile(
    r"\b" + "charg" + r"(?:e|ed|es|ing)\b",
    re.IGNORECASE,
)
FORBIDDEN_TEXT = {
    "obsolete attribution": re.compile(
        r"\b(?:J\.\s*C\.|James\s+C(?:hristopher)?\.?)\s+Harvey\b",
        re.IGNORECASE,
    ),
    "banned modifier": re.compile(r"\bhonest(?:ly)?\b", re.IGNORECASE),
    "excluded verdict word": re.compile(r"\bkilled\b", re.IGNORECASE),
    "registration term": re.compile(r"\bpre-commit(?:ted)?\b", re.IGNORECASE),
}


class PageParser(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.ids: list[str] = []
        self.links: list[tuple[str, str]] = []
        self.html_lang: str | None = None

    def handle_starttag(
        self, tag: str, attrs: list[tuple[str, str | None]]
    ) -> None:
        values = dict(attrs)
        if tag == "html":
            self.html_lang = values.get("lang")
        if values.get("id"):
            self.ids.append(str(values["id"]))
        for attribute in ("href", "src", "poster"):
            if values.get(attribute):
                self.links.append((attribute, str(values[attribute])))
        if values.get("srcset"):
            for candidate in str(values["srcset"]).split(","):
                url = candidate.strip().split(" ", 1)[0]
                if url:
                    self.links.append(("srcset", url))


def page_inventory(site: Path) -> dict[Path, PageParser]:
    pages: dict[Path, PageParser] = {}
    for path in sorted(site.rglob("*.html")):
        parser = PageParser()
        parser.feed(path.read_text(encoding="utf-8", errors="replace"))
        pages[path.resolve()] = parser
    return pages


def resolve_local_target(site: Path, source: Path, raw_url: str) -> Path | None:
    if not raw_url or raw_url.startswith(("#", "//")):
        return None
    if any(token in raw_url for token in ("{{", "}}", "${")):
        return None
    split = urlsplit(raw_url)
    if split.scheme or split.netloc:
        return None
    local = unquote(split.path).replace("\\", "/")
    if not local:
        return None
    target = site / local.lstrip("/") if local.startswith("/") else source.parent / local
    target = target.resolve()
    if target.exists():
        return target
    if not target.suffix:
        html_target = target.with_suffix(".html")
        if html_target.exists():
            return html_target
        index_target = target / "index.html"
        if index_target.exists():
            return index_target
    return target


def audit_site(site: Path) -> tuple[list[str], list[str], int]:
    errors: list[str] = []
    warnings: list[str] = []
    pages = page_inventory(site)
    ids_by_page = {path: set(parser.ids) for path, parser in pages.items()}
    link_count = 0

    for page, parser in pages.items():
        relative = page.relative_to(site.resolve()).as_posix()
        duplicates = sorted(
            item for item, count in Counter(parser.ids).items() if count > 1
        )
        if duplicates:
            errors.append(f"{site.name}/{relative}: duplicate ids {duplicates}")
        if not parser.html_lang:
            warnings.append(f"{site.name}/{relative}: missing html lang")

        for attribute, raw_url in parser.links:
            target = resolve_local_target(site, page, raw_url)
            if target is None:
                continue
            link_count += 1
            if not target.exists():
                errors.append(
                    f"{site.name}/{relative}: broken {attribute}={raw_url!r}"
                )
                continue
            fragment = unquote(urlsplit(raw_url).fragment)
            if fragment and target.suffix.lower() == ".html":
                target_ids = ids_by_page.get(target.resolve())
                if target_ids is not None and fragment not in target_ids:
                    errors.append(
                        f"{site.name}/{relative}: missing fragment "
                        f"{raw_url!r}"
                    )

    for suffix in TEXT_SUFFIXES:
        for path in sorted(site.rglob(f"*{suffix}")):
            text = path.read_text(encoding="utf-8", errors="replace")
            relative = path.relative_to(site).as_posix()
            for label, pattern in FORBIDDEN_TEXT.items():
                if pattern.search(text):
                    errors.append(f"{site.name}/{relative}: {label}")
            if path.suffix.lower() == ".html":
                for route in SUPERSEDED_INBOUND_ROUTES:
                    if re.search(
                        rf"""(?:href|src)\s*=\s*["'][^"']*{re.escape(route)}""",
                        text,
                        re.IGNORECASE,
                    ):
                        errors.append(
                            f"{site.name}/{relative}: inbound superseded route {route}"
                        )

    return errors, warnings, link_count


def audit_mirrors() -> list[str]:
    errors: list[str] = []
    for relative in MIRRORED_FILES:
        release_path = RELEASE / relative
        docs_path = DOCS / relative
        if not release_path.exists() or not docs_path.exists():
            errors.append(f"missing mirrored file: {relative}")
        elif release_path.read_bytes() != docs_path.read_bytes():
            errors.append(f"website mirror drift: {relative}")

    canonical_laws = ROOT / "Engine" / "include" / "sdt" / "laws.hpp"
    for path in (RELEASE / "dist" / "laws.hpp", DOCS / "dist" / "laws.hpp"):
        if path.exists() and path.read_bytes() != canonical_laws.read_bytes():
            errors.append(
                f"exported laws drift: {path.relative_to(ROOT).as_posix()}"
            )
    return errors


def audit_engine_data() -> list[str]:
    errors: list[str] = []
    path = RELEASE / "dist" / "sdt-engine-data.json"
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        return [f"engine data unreadable: {error}"]

    if data.get("schema_version") != 2:
        errors.append("engine data schema_version is not 2")
    if data.get("promotion_path") != (
        "validated investigation -> canonical engine header -> "
        "benchmark export -> website"
    ):
        errors.append("engine data promotion_path drift")

    results = data.get("results", [])
    summary = data.get("summary", {})
    earned = [
        row
        for row in results
        if row.get("certification") in {"DERIVED", "COMPUTED", "CALIBRATED"}
    ]
    identities = [
        row for row in results if row.get("certification") == "IDENTITY"
    ]
    pending = [row for row in results if row.get("certification") == "PENDING"]
    if summary.get("earned_total") != len(earned):
        errors.append("engine data earned_total does not match result rows")
    if summary.get("earned_passed") != sum(bool(row.get("passed")) for row in earned):
        errors.append("engine data earned_passed does not match result rows")
    if summary.get("identity_passed") != sum(
        bool(row.get("passed")) for row in identities
    ):
        errors.append("engine data identity_passed does not match result rows")
    if summary.get("pending_note_only") != len(pending):
        errors.append("engine data pending_note_only does not match result rows")
    if summary.get("genuine_fail") != sum(
        not bool(row.get("passed")) for row in earned
    ):
        errors.append("engine data genuine_fail does not match result rows")
    return errors


def audit_atomicus_load_order() -> list[str]:
    errors: list[str] = []
    text = (RELEASE / "atomicus-3d.html").read_text(encoding="utf-8")
    scripts = (
        "js/pack-nucleus.js",
        "js/nuclear-inputs.js",
        "js/traction-gear-engine.js",
        "atomicus-3d.js",
    )
    positions = [text.find(f'src="{script}"') for script in scripts]
    if any(position < 0 for position in positions):
        errors.append("Atomicus page is missing a required script")
    elif positions != sorted(positions):
        errors.append("Atomicus scripts are in the wrong load order")
    return errors


def audit_sitemap() -> list[str]:
    errors: list[str] = []
    for site in (RELEASE, DOCS):
        path = site / "sitemap.xml"
        text = path.read_text(encoding="utf-8")
        routes = {
            urlsplit(match).path.strip("/")
            for match in re.findall(r"<loc>(.*?)</loc>", text)
        }
        excluded = sorted(routes & SITEMAP_EXCLUDED_ROUTES)
        missing = sorted(SITEMAP_REQUIRED_ROUTES - routes)
        if excluded:
            errors.append(f"{site.name}/sitemap.xml: superseded routes {excluded}")
        if missing:
            errors.append(f"{site.name}/sitemap.xml: missing active routes {missing}")
    return errors


def audit_route_catalogs() -> list[str]:
    errors: list[str] = []
    for site in (RELEASE, DOCS):
        search_path = site / "search-index.json"
        try:
            entries = json.loads(search_path.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError) as error:
            errors.append(f"{site.name}/search-index.json: unreadable: {error}")
            continue
        indexed_routes = {
            Path(str(entry.get("u", ""))).stem
            for entry in entries
            if isinstance(entry, dict)
        }
        excluded = sorted(indexed_routes & SITEMAP_EXCLUDED_ROUTES)
        missing = sorted(SITEMAP_REQUIRED_ROUTES - indexed_routes)
        if excluded:
            errors.append(
                f"{site.name}/search-index.json: superseded routes {excluded}"
            )
        if missing:
            errors.append(
                f"{site.name}/search-index.json: missing active routes {missing}"
            )

        shell = (site / "sdt-shell.js").read_text(encoding="utf-8")
        shell_retired = sorted(
            route
            for route in SITEMAP_EXCLUDED_ROUTES
            if f"{route}.html" in shell
        )
        if shell_retired:
            errors.append(
                f"{site.name}/sdt-shell.js: superseded routes {shell_retired}"
            )
    return errors


def audit_single_path() -> list[str]:
    errors: list[str] = []
    redirect_targets = {
        "welcome.html": "theory.html",
        "causal-chain.html": "theory.html",
        "atlas.html": "theory.html",
        "atomicus-lab-subdued.html": "atomicus-lab.html",
        "atomicus-lab-v4-tiers.html": "atomicus-lab.html",
        "atomicus-v1-snapshot.html": "atomicus-3d.html",
        "atomicus-stick.html": "atomicus-3d.html",
        "atomicus-stick-v3-polar-caps.html": "atomicus-3d.html",
        "atomicus-construction-zone.html": "atomicus-3d.html",
        "atomicus-nuclear-model.html": "atomicus-3d.html",
        "monoisotopic-morph.html": "atomicus-3d.html",
        "nuclear-packing-sequencer-raw.html": "nuclear-packing-sequencer.html",
    }
    legacy_fragment = re.compile(
        r"""(?:href|src)\s*=\s*["']index\.html#"""
        r"""(?:irreducibles|medium|laws|topology|atomicus|lab|engine|"""
        r"""cosmology|experiments|glossary)["']""",
        re.IGNORECASE,
    )

    for site in (RELEASE, DOCS):
        theory = (site / "theory.html").read_text(encoding="utf-8")
        if (
            '<link rel="canonical" '
            'href="https://spatialdisplacementtheory.com/theory">' not in theory
        ):
            errors.append(f"{site.name}/theory.html: incorrect canonical")

        shell = (site / "sdt-shell.js").read_text(encoding="utf-8")
        if "walk.html" in shell:
            errors.append(f"{site.name}/sdt-shell.js: dead walk.html reference")

        for path in sorted(site.glob("*.html")):
            text = path.read_text(encoding="utf-8", errors="replace")
            if legacy_fragment.search(text):
                errors.append(
                    f"{site.name}/{path.name}: legacy index.html Atlas fragment"
                )

        for relative, target in redirect_targets.items():
            text = (site / relative).read_text(encoding="utf-8", errors="replace")
            required = (
                '<meta name="robots" content="noindex">',
                f"url={target}",
            )
            for token in required:
                if token not in text:
                    errors.append(
                        f"{site.name}/{relative}: missing redirect token {token!r}"
                    )

    return errors


def audit_theory_dependencies() -> list[str]:
    errors: list[str] = []
    required_reference_ids = {
        "arrival",
        "irreducibles",
        "medium",
        "laws",
        "topology",
        "atomicus",
        "lab",
        "engine",
        "cosmology",
        "experiments",
        "glossary",
    }

    for site in (RELEASE, DOCS):
        manifest_path = site / "theory-dependencies.json"
        theory_path = site / "theory.html"
        try:
            manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
            theory = theory_path.read_text(encoding="utf-8")
        except (OSError, json.JSONDecodeError) as error:
            errors.append(f"{site.name}: theory dependency surface unreadable: {error}")
            continue

        if manifest.get("schema") != "sdt-theory-dependencies-1.0.0":
            errors.append(f"{site.name}: unsupported theory dependency schema")
            continue
        nodes = manifest.get("nodes")
        if not isinstance(nodes, list) or len(nodes) != 21:
            errors.append(f"{site.name}: theory manifest must contain L0-L20")
            continue

        by_id: dict[str, dict[str, object]] = {}
        for order, node in enumerate(nodes):
            if not isinstance(node, dict):
                errors.append(f"{site.name}: theory node {order} is not an object")
                continue
            node_id = str(node.get("id", ""))
            if node_id in by_id:
                errors.append(f"{site.name}: duplicate theory node {node_id}")
            by_id[node_id] = node
            if node_id != f"L{order}" or node.get("order") != order:
                errors.append(
                    f"{site.name}: theory nodes are not contiguous at order {order}"
                )

        visiting: set[str] = set()
        visited: set[str] = set()

        def visit(node_id: str) -> None:
            if node_id in visiting:
                errors.append(f"{site.name}: theory dependency cycle at {node_id}")
                return
            if node_id in visited or node_id not in by_id:
                return
            visiting.add(node_id)
            node = by_id[node_id]
            requires = node.get("requires", [])
            if not isinstance(requires, list):
                errors.append(f"{site.name}: {node_id} requires is not a list")
                requires = []
            for required in requires:
                required_id = str(required)
                if required_id not in by_id:
                    errors.append(
                        f"{site.name}: {node_id} requires missing {required_id}"
                    )
                    continue
                if int(by_id[required_id].get("order", 10_000)) >= int(
                    node.get("order", -1)
                ):
                    errors.append(
                        f"{site.name}: {node_id} has forward dependency {required_id}"
                    )
                visit(required_id)
            visiting.remove(node_id)
            visited.add(node_id)

        for node_id in by_id:
            visit(node_id)

        section_dependencies = {
            match.group(1): match.group(2).split()
            for match in re.finditer(
                r'<section\s+class="theory-step"\s+id="(L\d+)"'
                r'\s+data-requires="([^"]*)">',
                theory,
            )
        }
        for node_id, node in by_id.items():
            manifest_requires = [str(item) for item in node.get("requires", [])]
            if section_dependencies.get(node_id) != manifest_requires:
                errors.append(
                    f"{site.name}: {node_id} HTML/manifest dependency mismatch"
                )

        parser = PageParser()
        parser.feed(theory)
        missing_ids = sorted(required_reference_ids - set(parser.ids))
        if missing_ids:
            errors.append(
                f"{site.name}/theory.html: missing compatibility ids {missing_ids}"
            )

    return errors


def _charge_audit_excluded(site: Path, path: Path) -> bool:
    """Immutable / third-party / binary paths are outside the active prose gate."""
    relative = path.relative_to(site).as_posix()
    parts = relative.split("/")
    if "_archive" in parts or "vendor" in parts:
        return True
    if path.name == "THREE-LICENSE.txt":
        return True
    if relative in {"dist/laws.hpp", "dist/SDT_input_ledger_output.txt"}:
        return True
    if path.suffix.lower() in BINARY_SUFFIXES:
        return True
    return False


def audit_charge_terminology() -> list[str]:
    """Fail on active charge / charged / charges / charging in mirrored public trees."""
    errors: list[str] = []
    for site in (RELEASE, DOCS):
        for path in sorted(p for p in site.rglob("*") if p.is_file()):
            if _charge_audit_excluded(site, path):
                continue
            text = path.read_text(encoding="utf-8", errors="replace")
            if PROHIBITED_CHARGE_REIFICATION.search(text):
                relative = path.relative_to(site).as_posix()
                errors.append(
                    f"{site.name}/{relative}: rejected charge reification"
                )
    return errors


def audit_benchmark_capture() -> list[str]:
    errors: list[str] = []
    generated_path = RELEASE / "dist" / "SDT_benchmarks_output.txt"
    generated = generated_path.read_text(encoding="utf-8").replace("\r\n", "\n")
    generated = "\n".join(
        line for line in generated.splitlines()
        if not line.startswith("Website data:")
    ).strip()
    for site in (RELEASE, DOCS):
        text = (site / "benchmarks.html").read_text(encoding="utf-8")
        match = re.search(
            r'<pre[^>]*class=["\'][^"\']*\bbench-pre\b[^"\']*["\'][^>]*>'
            r"(.*?)</pre>",
            text,
            re.DOTALL,
        )
        if match is None:
            errors.append(f"{site.name}/benchmarks.html: missing benchmark capture")
            continue
        captured = unescape(match.group(1)).replace("\r\n", "\n").strip()
        if captured != generated:
            errors.append(
                f"{site.name}/benchmarks.html: capture differs from generated output"
            )
    return errors


def audit_motion_controls() -> list[str]:
    errors: list[str] = []
    required_tokens = {
        "sdt-shell.js": "prefers-reduced-motion: reduce",
        "sdt-shell.css": "@media (prefers-reduced-motion: reduce)",
        "main.js": "motionEnabled",
        "atomicus-3d.js": "renderRequested",
        "atomicus-lab.html": "sdtMotionActive",
        "nuclear-packing-sequencer.html": "sequencerMotionActive",
        "nuclear-packing-walkthrough.html": "canvasMotionActive",
    }
    for site in (RELEASE, DOCS):
        for relative, token in required_tokens.items():
            text = (site / relative).read_text(encoding="utf-8")
            if token not in text:
                errors.append(
                    f"{site.name}/{relative}: missing motion control {token!r}"
                )
    return errors


def main() -> int:
    errors: list[str] = []
    warnings: list[str] = []
    total_pages = 0
    total_links = 0

    for site in (RELEASE, DOCS):
        site_errors, site_warnings, link_count = audit_site(site)
        errors.extend(site_errors)
        warnings.extend(site_warnings)
        total_pages += len(page_inventory(site))
        total_links += link_count

    errors.extend(audit_mirrors())
    errors.extend(audit_engine_data())
    errors.extend(audit_atomicus_load_order())
    errors.extend(audit_sitemap())
    errors.extend(audit_route_catalogs())
    errors.extend(audit_single_path())
    errors.extend(audit_theory_dependencies())
    errors.extend(audit_charge_terminology())
    errors.extend(audit_benchmark_capture())
    errors.extend(audit_motion_controls())

    for warning in warnings:
        print(f"WARN  {warning}")
    for error in errors:
        print(f"FAIL  {error}")

    if errors:
        print(
            f"\nSITE AUDIT FAILED: {len(errors)} errors, "
            f"{len(warnings)} warnings"
        )
        return 1
    print(
        f"PASS  public-site audit: {total_pages} pages, "
        f"{total_links} local references, {len(warnings)} warnings"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
