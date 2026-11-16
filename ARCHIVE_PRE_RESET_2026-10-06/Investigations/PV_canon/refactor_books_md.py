"""
Refactor all Book.md files: normalize heading hierarchy, list spacing, code fences.
- Book title stays H1. '## Book Overview' unchanged (before any chapter).
- '# Chapter' -> '## Chapter'. Inside a chapter, demote ## -> ### and ### -> ####.
- Blank line before first list item when preceded by non-list; blank after list before non-list.
- Bare '```' -> '```text'.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parent
BOOK_GLOB = "**/Book_*/Book.md"

CHAPTER_H1 = re.compile(r"^#\s+(Chapter\s+\d+.*)$")
CHAPTER_H2 = re.compile(r"^##\s+(Chapter\s+\d+.*)$")
H2 = re.compile(r"^##\s+(.+)$")
H3 = re.compile(r"^###\s+(.+)$")
H4 = re.compile(r"^####\s+(.+)$")
LIST_LIKE = re.compile(r"^(\s*[-*+]|\s*\d+\.)\s")


def refactor(content: str) -> str:
    lines = content.splitlines()
    out: list[str] = []
    in_chapter = False
    in_code_block = False
    i = 0
    n = len(lines)

    def prev_nonblank(arr: list[str], start: int) -> str:
        k = start
        while k >= 0:
            s = arr[k].strip() if k < len(arr) else ""
            if s:
                return s
            k -= 1
        return ""

    while i < n:
        line = lines[i]
        stripped = line.strip()

        # Normalize # Chapter -> ## Chapter
        m1 = CHAPTER_H1.match(line)
        if m1:
            out.append("## " + m1.group(1))
            in_chapter = True
            i += 1
            continue

        m2 = CHAPTER_H2.match(line)
        if m2:
            out.append(line)
            in_chapter = True
            i += 1
            continue

        # Other ## : demote to ### when in chapter
        mh2 = H2.match(line)
        if mh2 and in_chapter:
            # Ensure blank before this heading if previous non-blank is not a heading
            prev = prev_nonblank(out, len(out) - 1)
            if out and prev and not prev.startswith("#") and not prev.startswith("---"):
                if out[-1].strip() != "":
                    out.append("")
            out.append("### " + mh2.group(1))
            i += 1
            continue

        if mh2:
            out.append(line)
            i += 1
            continue

        # #### -> ### when in chapter (revert over-demotion; keep idempotent)
        mh4 = H4.match(line)
        if mh4 and in_chapter:
            out.append("### " + mh4.group(1))
            i += 1
            continue

        # ### stays ### when in chapter (no demotion)
        if H3.match(line):
            out.append(line)
            i += 1
            continue

        # Bare ``` (no lang): opening -> ```text, closing -> ```
        if stripped == "```":
            if not in_code_block:
                out.append("```text")
                in_code_block = True
            else:
                out.append("```")
                in_code_block = False
            i += 1
            continue
        if stripped.startswith("```") and stripped != "```":
            in_code_block = not in_code_block

        # List spacing: blank before first list item when preceded by non-list
        if LIST_LIKE.match(line):
            if out:
                prev = prev_nonblank(out, len(out) - 1)
                last_out = out[-1].strip()
                if last_out and not LIST_LIKE.match(out[-1]) and not last_out.startswith("```"):
                    if last_out != "---" and not last_out.startswith("#"):
                        if out[-1].strip() != "":
                            out.append("")
            out.append(line)
            i += 1
            continue

        # Non-list after list: ensure blank between
        if out and LIST_LIKE.match(out[-1]) and stripped and not LIST_LIKE.match(line):
            if not stripped.startswith("```"):
                out.append("")
        out.append(line)
        i += 1

    # Trim trailing blanks, ensure single final newline
    text = "\n".join(out)
    while text.endswith("\n\n\n"):
        text = text[:-1]
    if not text.endswith("\n"):
        text += "\n"
    return text


def fix_volume_10_book_title(content: str) -> str:
    """Fix 'Book 01: Volume 01 Content' -> 'Book 01: Nucleus-Driven Chemistry'."""
    bad = "Volume 10: Molecular Structures Compendium — Book 01: Volume 01: Nucleus-Driven Chemistry"
    good = "Volume 10: Molecular Structures Compendium — Book 01: Nucleus-Driven Chemistry"
    if bad in content:
        content = content.replace(bad, good)
    bad2 = "Book 01: Volume 01 Content"
    if "Volume 10" in content and bad2 in content:
        content = content.replace("# " + bad2, "# Volume 10: Molecular Structures Compendium — Book 01: Nucleus-Driven Chemistry")
    return content


def main():
    base = ROOT
    books = sorted(base.glob(BOOK_GLOB))
    for p in books:
        original = p.read_text(encoding="utf-8")
        raw = fix_volume_10_book_title(original)
        new = refactor(raw)
        if new != original:
            p.write_text(new, encoding="utf-8")
            print("Refactored:", p.relative_to(base))
    print("Done. Books checked:", len(books))


if __name__ == "__main__":
    main()
