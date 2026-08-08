import json
from pathlib import Path

src = Path(
    r"C:\Users\Jimmi\.cursor\projects\c-Users-Jimmi-OneDrive-Desktop-sdt-engine"
    r"\agent-transcripts\a70937a0-e368-418f-b2fb-cb72e64ca28a"
    r"\a70937a0-e368-418f-b2fb-cb72e64ca28a.jsonl"
)
text = json.loads(src.read_text(encoding="utf-8").splitlines()[0])["message"]["content"][0][
    "text"
]
fence = "```" + "text\n"
close = "\n```"
start = text.find(fence)
if start < 0:
    raise SystemExit("open fence not found")
start += len(fence)
end = text.find(close, start)
if end < 0:
    raise SystemExit("close fence not found")
body = text[start:end]
out = Path(r"c:\Users\Jimmi\OneDrive\Desktop\sdt-engine\Audits\MASTER_PROTOCOL_PROMPT_v1.0.md")
header = (
    "# SDT Total Research Protocol — Master Prompt v1.0\n\n"
    "> Recovered from the 2026-08-07 session that opened this ledger.\n"
    "> Framing line from that message: *Use this as the single master prompt.*\n\n"
    "```text\n"
)
footer = "\n```\n"
out.write_text(header + body + footer, encoding="utf-8", newline="\n")
print(out)
print("body_chars", len(body))
print("starts:", body[:80].replace("\n", "\\n"))
print("ends:", body[-80:].replace("\n", "\\n"))
