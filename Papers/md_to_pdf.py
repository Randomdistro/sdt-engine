"""
Convert an_argument_for_koppa.md to a styled HTML file
with MathJax rendering, suitable for printing to PDF via browser.
"""
import markdown
import re
import sys

input_file = r"c:\Users\Jimmi\sdt-engine\Papers\an_argument_for_koppa.md"
output_file = r"c:\Users\Jimmi\sdt-engine\Papers\an_argument_for_koppa.html"

with open(input_file, "r", encoding="utf-8") as f:
    md_text = f.read()

# Protect LaTeX display math blocks from markdown processing
# Replace $$ ... $$ with placeholders
display_math = []
def replace_display(m):
    idx = len(display_math)
    display_math.append(m.group(1))
    return f"DISPLAYMATH{idx}ENDDISPLAY"

md_text = re.sub(r'\$\$(.*?)\$\$', replace_display, md_text, flags=re.DOTALL)

# Protect inline math $...$
inline_math = []
def replace_inline(m):
    idx = len(inline_math)
    inline_math.append(m.group(1))
    return f"INLINEMATH{idx}ENDINLINE"

md_text = re.sub(r'(?<!\$)\$(?!\$)(.+?)(?<!\$)\$(?!\$)', replace_inline, md_text)

# Convert markdown to HTML
html_body = markdown.markdown(md_text, extensions=['tables', 'fenced_code'])

# Restore display math
for i, math_content in enumerate(display_math):
    html_body = html_body.replace(f"DISPLAYMATH{i}ENDDISPLAY", f'\\[{math_content}\\]')

# Restore inline math
for i, math_content in enumerate(inline_math):
    html_body = html_body.replace(f"INLINEMATH{i}ENDINLINE", f'\\({math_content}\\)')

html_doc = f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>An Argument for Koppa — J. Tyndall 2026</title>
<script>
window.MathJax = {{
  tex: {{
    inlineMath: [['\\\\(', '\\\\)']],
    displayMath: [['\\\\[', '\\\\]']],
  }},
  svg: {{ fontCache: 'global' }}
}};
</script>
<script src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js" async></script>
<style>
@import url('https://fonts.googleapis.com/css2?family=EB+Garamond:ital,wght@0,400;0,600;1,400&family=Source+Code+Pro:wght@400;600&display=swap');

:root {{
  --text: #1a1a1a;
  --bg: #fff;
  --accent: #2c3e50;
  --border: #bdc3c7;
  --table-stripe: #f8f9fa;
  --link: #2980b9;
}}

* {{ margin: 0; padding: 0; box-sizing: border-box; }}

body {{
  font-family: 'EB Garamond', 'Times New Roman', serif;
  font-size: 11.5pt;
  line-height: 1.55;
  color: var(--text);
  background: var(--bg);
  max-width: 750px;
  margin: 0 auto;
  padding: 40px 50px;
}}

h1 {{
  font-size: 22pt;
  font-weight: 600;
  text-align: center;
  margin: 0 0 6pt;
  color: var(--accent);
  letter-spacing: 0.02em;
}}

h2 {{
  font-size: 14pt;
  font-weight: 600;
  margin: 24pt 0 8pt;
  color: var(--accent);
  border-bottom: 1.5px solid var(--border);
  padding-bottom: 4pt;
  page-break-after: avoid;
}}

h3 {{
  font-size: 12pt;
  font-weight: 600;
  margin: 18pt 0 6pt;
  color: var(--accent);
  page-break-after: avoid;
}}

h4 {{
  font-size: 11pt;
  font-weight: 600;
  margin: 12pt 0 4pt;
  color: #34495e;
  page-break-after: avoid;
}}

p {{
  margin: 6pt 0;
  text-align: justify;
  hyphens: auto;
}}

blockquote {{
  border-left: 3px solid var(--accent);
  padding: 4pt 12pt;
  margin: 8pt 0;
  background: #f7f9fb;
  font-style: italic;
}}

table {{
  width: 100%;
  border-collapse: collapse;
  margin: 8pt 0;
  font-size: 9.5pt;
  page-break-inside: avoid;
}}

th {{
  background: var(--accent);
  color: #fff;
  font-weight: 600;
  padding: 4pt 6pt;
  text-align: left;
  border: 1px solid var(--accent);
}}

td {{
  padding: 3pt 6pt;
  border: 1px solid #ddd;
  vertical-align: top;
}}

tr:nth-child(even) {{ background: var(--table-stripe); }}

code {{
  font-family: 'Source Code Pro', monospace;
  font-size: 9pt;
  background: #f0f0f0;
  padding: 1pt 3pt;
  border-radius: 2pt;
}}

pre {{
  background: #2c3e50;
  color: #ecf0f1;
  padding: 10pt;
  border-radius: 4pt;
  overflow-x: auto;
  font-size: 8.5pt;
  line-height: 1.4;
  margin: 8pt 0;
}}

pre code {{
  background: transparent;
  color: inherit;
  padding: 0;
}}

hr {{
  border: none;
  border-top: 1px solid var(--border);
  margin: 16pt 0;
}}

strong {{ font-weight: 600; }}

a {{ color: var(--link); text-decoration: none; }}

ul, ol {{ margin: 6pt 0 6pt 20pt; }}
li {{ margin: 2pt 0; }}

.mjx-chtml {{ font-size: 105% !important; }}

/* Print styles */
@media print {{
  body {{
    padding: 0;
    max-width: none;
    font-size: 10.5pt;
  }}
  h1 {{ font-size: 18pt; }}
  h2 {{ font-size: 13pt; page-break-after: avoid; }}
  h3 {{ font-size: 11pt; page-break-after: avoid; }}
  table {{ font-size: 8.5pt; page-break-inside: avoid; }}
  pre {{ font-size: 7.5pt; }}
  a {{ color: var(--text); }}
}}

@page {{
  size: A4;
  margin: 20mm 18mm;
}}
</style>
</head>
<body>
{html_body}
</body>
</html>
"""

with open(output_file, "w", encoding="utf-8") as f:
    f.write(html_doc)

print(f"HTML written to: {output_file}")
print("Open this file in a browser and use Print -> Save as PDF (Ctrl+P)")
print("MathJax will render all equations automatically.")
