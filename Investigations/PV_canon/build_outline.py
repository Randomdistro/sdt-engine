import os
from pathlib import Path
import re
from html import escape

root = Path("SDT")
out_dir = root / "Spatial_Displacement_Theory"
out_dir.mkdir(parents=True, exist_ok=True)
scss_dir = out_dir / "scss"
scss_dir.mkdir(parents=True, exist_ok=True)

text_exts = {
    ".md",
    ".tex",
    ".py",
    ".cpp",
    ".hpp",
    ".json",
    ".csv",
    ".txt",
    ".html",
    ".css",
    ".js",
    ".ts",
    ".tsx",
}


def file_info(path: Path):
    rel = path.as_posix()
    size = path.stat().st_size
    lines = None
    if path.suffix.lower() in text_exts:
        try:
            lines = path.read_text(encoding="utf-8", errors="ignore").count("\n") + 1
        except Exception:
            lines = None
    return rel, size, lines


files = [p for p in root.rglob("*") if p.is_file()]
file_infos = [file_info(p) for p in files]
file_infos.sort(key=lambda x: x[0].lower())

src_md = out_dir / "source_index.md"
with src_md.open("w", encoding="utf-8") as f:
    f.write("# SDT Canonical Source Index\n\n")
    f.write("This is an exhaustive file-level index of the SDT codebase.\n\n")
    f.write("Format: path | size_bytes | line_count (if text)\n\n")
    for rel, size, lines in file_infos:
        line_str = str(lines) if lines is not None else "n/a"
        link = f"../{rel}"
        f.write(f"- [{rel}]({link}) | {size} | {line_str}\n")

def safe_name(value: str) -> str:
    value = value.replace(" ", "_")
    value = re.sub(r"[^A-Za-z0-9_]+", "_", value)
    return re.sub(r"_+", "_", value).strip("_")

volumes = [
    {
        "id": "01",
        "title": "Foundations and Spation Primitives",
        "books": [
            {
                "id": "01",
                "title": "Foundational Axioms and Core Principles",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Foundational Principles",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/00_Foundations/Foundational_Principles"
                        ],
                    },
                    {
                        "id": "02",
                        "title": "SDT Navier Field Theory",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/00_Foundations/SDT_Navier_Field_Theory"
                        ],
                    },
                    {
                        "id": "03",
                        "title": "Core Engine Mathematical Proof",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/00_Foundations/Core_Engine_Mathematical_Proof"
                        ],
                    },
                    {
                        "id": "04",
                        "title": "Unified Physics from the Master Equation",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/00_Foundations/Unified_Physics_from_Master_Equation"
                        ],
                    },
                    {
                        "id": "05",
                        "title": "Topology from Spation Structure",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/00_Foundations/Topology_from_Spation_Structure"
                        ],
                    },
                    {
                        "id": "06",
                        "title": "Symmetry Breaking from Geometric Instability",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/00_Foundations/Symmetry_Breaking_from_Geometric_Instability"
                        ],
                    },
                    {
                        "id": "07",
                        "title": "Information Theory from Spation States",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/00_Foundations/Information_Theory_from_Spation_States"
                        ],
                    },
                    {
                        "id": "08",
                        "title": "Renormalization from Scale Hierarchy",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/00_Foundations/Renormalization_from_Scale_Hierarchy"
                        ],
                    },
                ],
            },
            {
                "id": "02",
                "title": "Treatise Integration and Foundational Compendium",
                "chapters": [
                    {
                        "id": "01",
                        "title": "De Rerum Todo Existens (Treatise Core)",
                        "sources": ["SDT/Papers/SDT_Foundation/De_Rerum_Todo_Existens"],
                    },
                    {
                        "id": "02",
                        "title": "CMB Cause of Gravitation (Journal Submission)",
                        "sources": ["SDT/Papers/CMB_Cause_of_Gravitation_Journal_Submission.md"],
                    },
                    {
                        "id": "03",
                        "title": "Foundational Phase Archives",
                        "sources": ["SDT/Papers/SDT_Foundation/Historical_Phases_Archive"],
                    },
                ],
            },
        ],
    },
    {
        "id": "02",
        "title": "Field Theory, Mechanics, and Mathematical Structure",
        "books": [
            {
                "id": "01",
                "title": "Continuum Mechanics from Spation Flow",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Fluid Dynamics from Spation Flow",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/08_Fluid_Dynamics"
                        ],
                    },
                    {
                        "id": "02",
                        "title": "Pressure Cascade and Contact Mechanics",
                        "sources": ["SDT/Code/pressure_cascade_derivation.html", "SDT/Code/pressure kernel.py"],
                    },
                    {
                        "id": "03",
                        "title": "Shunt Dynamics and Flow Operators",
                        "sources": ["SDT/Code/sdt_core", "SDT/Code/sdt_navier"],
                    },
                ],
            },
            {
                "id": "02",
                "title": "Mathematical Operators and State Space",
                "chapters": [
                    {"id": "01", "title": "State28D Operators and Usage", "sources": ["SDT/Code/example_state28d_usage.py"]},
                    {
                        "id": "02",
                        "title": "Geometric Operators in Investigations",
                        "sources": ["SDT/Papers/SDT_Foundation/Section_VII_Current_Investigations"],
                    },
                ],
            },
        ],
    },
    {
        "id": "03",
        "title": "Atomic Physics (Summary Only; Full Canon in ATOMICUS)",
        "books": [
            {
                "id": "01",
                "title": "Atomic Physics Summary and Links",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Atomic Structure Overview (Summary)",
                        "sources": ["SDT/Papers/Matter_and_the_Shape_of_Displacement_Atomics_in_SDT", "SDT/ATOMICUS/ATOMICUS_INDEX.md"],
                    },
                    {
                        "id": "02",
                        "title": "Spectra, Fine/Hyperfine, and Electron Geometry",
                        "sources": ["SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/01_Atomic_Physics"],
                    },
                ],
            },
        ],
    },
    {
        "id": "04",
        "title": "Electromagnetism and Magnetic Phenomena",
        "books": [
            {
                "id": "01",
                "title": "Electricity from Spation Pressure",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Electricity from Spation Pressure Deformation",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/02_Electromagnetism/Electricity_from_Spation_Pressure_Deformation"
                        ],
                    },
                    {
                        "id": "02",
                        "title": "Electromagnetic Mechanisms and Effects",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/02_Electromagnetism/Electromagnetic_Mechanisms_and_Effects_Part1",
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/02_Electromagnetism/Electromagnetic_Mechanisms_and_Effects_Part2",
                        ],
                    },
                ],
            },
            {
                "id": "02",
                "title": "Magnetic Moments and Helical Wakes",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Magnetic Moments from Toroidal Circulation",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/02_Electromagnetism/Magnetic_Moments_from_Toroidal_Circulation"
                        ],
                    },
                    {"id": "02", "title": "Benchmarked Magnetic Moments", "sources": ["SDT/benchmarks/Grok_Benchmarks"]},
                ],
            },
        ],
    },
    {
        "id": "05",
        "title": "Nuclear Physics and Particle Architecture",
        "books": [
            {
                "id": "01",
                "title": "Nucleon Structures",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Proton Engine and Trefoil Geometry",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/06_Nuclear_Physics",
                            "SDT/Code/sdt_navier_cpp/include/sdt_navier/constants.hpp",
                        ],
                    },
                    {
                        "id": "02",
                        "title": "Neutron Genesis and Beta Decay",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Deprecated_Papers/Part_I_Axioms_and_Core_Equations/06_Nuclear_Physics/The_Neutron_Genesis.md"
                        ],
                    },
                    {
                        "id": "03",
                        "title": "Alpha Architecture and Nuclear Binding",
                        "sources": ["SDT/Papers/SDT_Foundation/Deprecated_Papers/Part_I_Axioms_and_Core_Equations/06_Nuclear_Physics"],
                    },
                ],
            },
            {
                "id": "02",
                "title": "Nuclear Packing and Geometry",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Nuclear Packing Master Equation",
                        "sources": [
                            "SDT/Papers/SDT_Foundation/Deprecated_Papers/Part_I_Axioms_and_Core_Equations/06_Nuclear_Physics/Nuclear_Packing_Master_Equation"
                        ],
                    },
                    {"id": "02", "title": "Nuclear Structure Investigations", "sources": ["SDT/investigations/nuclear_structure_probe"]},
                ],
            },
        ],
    },
    {
        "id": "06",
        "title": "Thermodynamics and Statistical Mechanics",
        "books": [
            {
                "id": "01",
                "title": "Thermodynamics from Spation Contact Mechanics",
                "chapters": [
                    {"id": "01", "title": "Thermodynamics from Pressure Energy", "sources": ["SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/04_Thermodynamics"]},
                    {"id": "02", "title": "Phase Transitions and Stability", "sources": ["SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/04_Thermodynamics/Phase_Transitions_from_Pressure_Stability"]},
                ],
            },
            {
                "id": "02",
                "title": "Transport and Statistical Mechanics",
                "chapters": [
                    {"id": "01", "title": "Transport Coefficients from Shunt Flux", "sources": ["SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/08_Fluid_Dynamics"]},
                ],
            },
        ],
    },
    {
        "id": "07",
        "title": "Gravitation and Stellar Structure",
        "books": [
            {
                "id": "01",
                "title": "Gravitation from Spation Pressure Gradients",
                "chapters": [
                    {"id": "01", "title": "Gravitation from Spation Pressure Gradients", "sources": ["SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/03_Gravitation_and_Cosmology/Gravitation_from_Spation_Pressure_Gradients"]},
                    {"id": "02", "title": "Stellar Structure from Pressure Geometry", "sources": ["SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/03_Gravitation_and_Cosmology/Stellar_Structure_from_Pressure_Geometry"]},
                ],
            },
        ],
    },
    {
        "id": "08",
        "title": "Cosmology and Large-Scale Structure",
        "books": [
            {
                "id": "01",
                "title": "Cosmological Structure from Pressure Topology",
                "chapters": [
                    {"id": "01", "title": "Galactic Rotation from Disk Occlusion", "sources": ["SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/03_Gravitation_and_Cosmology/Galactic_Rotation_from_Disk_Occlusion"]},
                    {"id": "02", "title": "Cosmological Structure and Topology", "sources": ["SDT/Papers/SDT_Foundation/Part_I_Axioms_and_Core_Equations/03_Gravitation_and_Cosmology/Cosmological_Structure_from_Pressure_Topology"]},
                    {"id": "03", "title": "CMB and Large-Scale Pressure Fields", "sources": ["SDT/Papers/CMB_Cause_of_Gravitation_Journal_Submission.md"]},
                ],
            },
        ],
    },
    {
        "id": "09",
        "title": "Chemistry and Nucleus-Driven Framework",
        "books": [
            {
                "id": "01",
                "title": "Nucleus-Driven Chemistry",
                "chapters": [
                    {"id": "01", "title": "Nucleus-Driven Chemistry Principles", "sources": ["SDT/Molecular_Structures/NUCLEUS_DRIVEN_CHEMISTRY_PRINCIPLES.md"]},
                    {"id": "02", "title": "Nuclear Chemistry Validation", "sources": ["SDT/investigations/NUCLEAR_CHEMISTRY_VALIDATION.md"]},
                ],
            },
        ],
    },
    {
        "id": "10",
        "title": "Molecular Structures Compendium",
        "books": [
            {"id": "01", "title": "Volume 01: Nucleus-Driven Chemistry", "chapters": [{"id": "01", "title": "Volume 01 Content", "sources": ["SDT/Molecular_Structures/Volume_01_NUCLEUS_DRIVEN_CHEMISTRY.md", "SDT/Molecular_Structures/Volume_01_COMPLETE_ANALYSES.md"]}]},
            {"id": "02", "title": "Volume 02: Simple Organic Molecules", "chapters": [{"id": "01", "title": "Volume 02 Content", "sources": ["SDT/Molecular_Structures/Volume_02_Simple_Organic_Molecules.md"]}]},
            {"id": "03", "title": "Volume 03: Biological Building Blocks", "chapters": [{"id": "01", "title": "Volume 03 Content", "sources": ["SDT/Molecular_Structures/Volume_03_Biological_Building_Blocks.md"]}]},
            {"id": "04", "title": "Volume 04: Inorganic Minerals", "chapters": [{"id": "01", "title": "Volume 04 Content", "sources": ["SDT/Molecular_Structures/Volume_04_Inorganic_Minerals.md"]}]},
            {"id": "05", "title": "Volume 05: Complex Organic Molecules", "chapters": [{"id": "01", "title": "Volume 05 Content", "sources": ["SDT/Molecular_Structures/Volume_05_Complex_Organic_Molecules.md"]}]},
            {"id": "06", "title": "Volume 06: Nitrogen Cycle", "chapters": [{"id": "01", "title": "Volume 06 Content", "sources": ["SDT/Molecular_Structures/Volume_06_Nitrogen_Cycle.md"]}]},
            {"id": "07", "title": "Volume 07: Oxygen Network", "chapters": [{"id": "01", "title": "Volume 07 Content", "sources": ["SDT/Molecular_Structures/Volume_07_Oxygen_Network.md"]}]},
            {"id": "08", "title": "Volume 08: Halogen Family", "chapters": [{"id": "01", "title": "Volume 08 Content", "sources": ["SDT/Molecular_Structures/Volume_08_Halogen_Family.md"]}]},
            {"id": "09", "title": "Volume 09: Silicon Foundation", "chapters": [{"id": "01", "title": "Volume 09 Content", "sources": ["SDT/Molecular_Structures/Volume_09_Silicon_Foundation.md"]}]},
            {"id": "10", "title": "Volume 10: Complex Synthetic Molecules", "chapters": [{"id": "01", "title": "Volume 10 Content", "sources": ["SDT/Molecular_Structures/Volume_10_Complex_Synthetic_Molecules.md"]}]},
            {"id": "11", "title": "Volume 11: Highly Complex Synthetic Molecules", "chapters": [{"id": "01", "title": "Volume 11 Content", "sources": ["SDT/Molecular_Structures/Volume_11_Highly_Complex_Synthetic_Molecules.md"]}]},
            {"id": "12", "title": "Volume 12: Extremely Complex Synthetic Molecules", "chapters": [{"id": "01", "title": "Volume 12 Content", "sources": ["SDT/Molecular_Structures/Volume_12_Extremely_Complex_Synthetic_Molecules.md"]}]},
            {"id": "13", "title": "Volume 13: Specialized Synthetic Molecules", "chapters": [{"id": "01", "title": "Volume 13 Content", "sources": ["SDT/Molecular_Structures/Volume_13_Specialized_Synthetic_Molecules.md"]}]},
        ],
    },
    {
        "id": "11",
        "title": "Validation, Benchmarks, and Empirical Tests",
        "books": [
            {"id": "01", "title": "Benchmark Suite and Validation Reports", "chapters": [{"id": "01", "title": "Benchmark Master Index", "sources": ["SDT/benchmarks/BENCHMARK_MASTER_INDEX.md"]}, {"id": "02", "title": "Validation Reports (B01-B60+)", "sources": ["SDT/benchmarks"]}]},
            {"id": "02", "title": "SDT vs Standard Physics", "chapters": [{"id": "01", "title": "Comparative Analyses and Error Reports", "sources": ["SDT/COMPREHENSIVE_ERROR_ANALYSIS.md", "SDT/ERROR_ANALYSIS_REPORT.md", "SDT/benchmarks/SDT_vs_STANDARD_PHYSICS.md"]}]},
        ],
    },
    {
        "id": "12",
        "title": "Computation, Code, and Simulation Systems",
        "books": [
            {
                "id": "01",
                "title": "Code Constants and Computational Core",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Core Constants and SDT Navier",
                        "sources": [
                            "SDT/Code/sdt_navier_cpp/include/sdt_navier/constants.hpp",
                            "SDT/Code/sdt_navier_cpp",
                        ],
                    },
                    {
                        "id": "02",
                        "title": "Computational Tools and Generators",
                        "sources": ["SDT/Code", "SDT/tools"],
                    },
                    {
                        "id": "03",
                        "title": "Data, Tables, and Derived Artifacts",
                        "sources": ["SDT/data", "SDT/validation", "SDT/benchmarks/data"],
                    },
                ],
            },
            {
                "id": "02",
                "title": "Simulations and Visualizations",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Solar System and Galactic Simulations",
                        "sources": ["SDT/Simulations"],
                    },
                    {
                        "id": "02",
                        "title": "Website and Interactive Systems",
                        "sources": ["SDT/website", "SDT/sdt-interactive-website"],
                    },
                    {
                        "id": "03",
                        "title": "Figures, Media, and Rendered Assets",
                        "sources": ["SDT/Figures", "SDT/files.zip"],
                    },
                ],
            },
            {
                "id": "03",
                "title": "Repository Automation and Build Systems",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Automation Scripts and Generators",
                        "sources": [
                            "SDT/sdt_textbook_generator.py",
                            "SDT/repair_links.py",
                            "SDT/populate_derivations.py",
                        ],
                    },
                    {
                        "id": "02",
                        "title": "Build and Workspace Configurations",
                        "sources": [
                            "SDT/Spatial_Displacement_Theory.code-workspace",
                            "SDT/Code/build.bat",
                            "Spatial_Displacement_Theory.sln",
                        ],
                    },
                ],
            },
        ],
    },
    {
        "id": "13",
        "title": "Philosophy, Methodology, and Programmatics",
        "books": [
            {
                "id": "01",
                "title": "Methodology and Professionalization",
                "chapters": [
                    {
                        "id": "01",
                        "title": "Professionalization and Completion Plans",
                        "sources": [
                            "SDT/PROFESSIONALIZATION_PLAN.md",
                            "SDT/PROFESSIONALIZATION_SAMPLE.md",
                            "SDT/COMPLETION_TRACK.md",
                        ],
                    },
                    {
                        "id": "02",
                        "title": "Cross-Reference Maps and Indexes",
                        "sources": ["SDT/CROSS_REFERENCE_MAP.md", "SDT/SDT_INDEX.md"],
                    },
                    {
                        "id": "03",
                        "title": "Project Terms and Glossary",
                        "sources": ["SDT/TERMS.md", "SDT/README.md", "SDT/README_START_HERE.md"],
                    },
                ],
            },
            {
                "id": "02",
                "title": "Investigations and Prompts",
                "chapters": [
                    {"id": "01", "title": "Investigations Suite", "sources": ["SDT/investigations"]},
                    {
                        "id": "02",
                        "title": "Prompts and Roadmaps",
                        "sources": [
                            "SDT/WEBSITE_PLAN.md",
                            "SDT/PROMPT_23_VOLUME_COMPLETE_CHEMISTRY_COMPENDIUM.md",
                            "SDT/PROMPT_23_VOLUME_MOLECULAR_COMPENDIUM.md",
                        ],
                    },
                    {
                        "id": "03",
                        "title": "Archive, Chat Logs, and Metadata",
                        "sources": ["SDT/archive", "SDT/COMPREHENSIVE_ERROR_ANALYSIS.md", "SDT/ERROR_ANALYSIS_REPORT.md"],
                    },
                ],
            },
            {
                "id": "03",
                "title": "Legacy Compilations and Alternate Builds",
                "chapters": [
                    {"id": "01", "title": "Legacy Compilations (nope/)", "sources": ["SDT/Papers/nope"]},
                    {
                        "id": "02",
                        "title": "External Artifacts (PDF/DOCX)",
                        "sources": ["SDT/Papers/DE_RERUM_TODO_EXISTENS_COMPLETE.pdf", "SDT/Papers/DE_RERUM_TODO_EXISTENS_COMPLETE.docx"],
                    },
                ],
            },
        ],
    },
]


def list_files_for_sources(sources):
    paths = []
    for src in sources:
        src_path = Path(src)
        if src_path.is_dir():
            for p in src_path.rglob("*"):
                if p.is_file():
                    paths.append(p.as_posix())
        elif src_path.is_file():
            paths.append(src_path.as_posix())
    return sorted(set(paths))


def render_canonical_html(volumes_data, list_files_fn):
    """Generate semantic HTML5 for the canonical outline."""
    css = """
:root { --bg: #0a0a0f; --fg: #e6e6e6; --accent: #8fd3ff; --muted: #888; }
* { box-sizing: border-box; }
body {
  font-family: system-ui, 'Segoe UI', Arial, sans-serif;
  background: var(--bg);
  color: var(--fg);
  line-height: 1.5;
  margin: 0;
  padding: 1rem 2rem 3rem;
  max-width: 960px;
  margin-inline: auto;
}
a { color: var(--accent); text-decoration: none; }
a:hover { text-decoration: underline; }
h1 { font-size: 1.5rem; margin-bottom: 0.5rem; }
h2 { font-size: 1.25rem; margin-top: 2rem; margin-bottom: 1rem; border-bottom: 1px solid #333; }
h3 { font-size: 1.1rem; margin-top: 1.5rem; margin-bottom: 0.5rem; }
h4 { font-size: 1rem; margin-top: 1rem; margin-bottom: 0.4rem; color: var(--muted); }
p { margin: 0.5rem 0; color: var(--muted); font-size: 0.95rem; }

nav[aria-label='Volumes'] {
  margin: 1rem 0 1.5rem;
  padding: 0.75rem 0;
  border-bottom: 1px solid #222;
}
nav[aria-label='Volumes'] ul { list-style: none; padding: 0; margin: 0; display: flex; flex-wrap: wrap; gap: 0.5rem 1rem; }
nav[aria-label='Volumes'] li { display: inline; }
nav[aria-label='Volumes'] a { font-size: 0.9rem; }

main { margin-top: 1rem; }
section.volume {
  margin: 24px 0;
  padding: 1rem 0;
  border-bottom: 1px solid #1a1a1a;
}
section.volume:last-of-type { border-bottom: none; }
section.volume h3 { margin-top: 0; }
.book { margin: 1rem 0; }
.book ul { list-style: none; padding-left: 0; margin: 0.5rem 0; }
.book li { margin: 0.4rem 0; padding-left: 0.5rem; border-left: 2px solid transparent; }

.tooltip { position: relative; display: inline-block; }
.tooltip .tip {
  visibility: hidden;
  position: absolute;
  z-index: 10;
  left: 0;
  top: 1.5em;
  background: #111;
  border: 1px solid #444;
  padding: 10px 12px;
  border-radius: 6px;
  width: 420px;
  max-height: 320px;
  overflow-y: auto;
  font-size: 0.85rem;
  box-shadow: 0 8px 24px rgba(0,0,0,0.5);
}
.tooltip:hover .tip { visibility: visible; }
.tooltip .tip ul { list-style: disc; padding-left: 1.2rem; margin: 0.25rem 0; }
.tooltip .tip li { margin: 0.2rem 0; border: none; }
"""

    out = []
    out.append('<!doctype html>')
    out.append('<html lang="en">')
    out.append('<head>')
    out.append('  <meta charset="utf-8">')
    out.append('  <meta name="viewport" content="width=device-width, initial-scale=1">')
    out.append('  <title>SDT Canonical Outline</title>')
    out.append('  <style>')
    out.append(css.strip())
    out.append('  </style>')
    out.append('</head>')
    out.append('<body>')
    out.append('  <header>')
    out.append('    <h1>SDT Canonical Volume-by-Volume Outline</h1>')
    out.append('    <p>Hover over chapters to view source details. Atomic physics is summarized here and canonically detailed in ATOMICUS.</p>')
    out.append('  </header>')
    out.append('  <nav aria-label="Volumes">')
    out.append('    <ul>')
    for v in volumes_data:
        aid = f"vol-{v['id']}"
        out.append(f"      <li><a href=\"#{aid}\">Volume {v['id']}</a></li>")
    out.append('    </ul>')
    out.append('  </nav>')
    out.append('  <main>')
    for v in volumes_data:
        vid = f"vol-{v['id']}"
        out.append(f'  <section class="volume" id="{vid}">')
        out.append(f'    <h2>Volume {v["id"]}: {escape(v["title"])}</h2>')
        for b in v["books"]:
            out.append(f'    <div class="book">')
            out.append(f'      <h3>Book {b["id"]}: {escape(b["title"])}</h3>')
            out.append('      <ul>')
            for c in b["chapters"]:
                files = list_files_fn(c["sources"])
                tip_li = "".join(f'<li><a href="../{escape(p)}">{escape(p)}</a></li>' for p in files)
                out.append('        <li class="tooltip">')
                out.append(f'          Chapter {c["id"]}: {escape(c["title"])}')
                out.append(f'          <div class="tip" role="tooltip"><ul>{tip_li}</ul></div>')
                out.append('        </li>')
            out.append('      </ul>')
            out.append('    </div>')
        out.append('  </section>')
    out.append('  </main>')
    out.append('</body>')
    out.append('</html>')
    return "\n".join(out)


master_md = out_dir / "Canonical_Outline.md"
with master_md.open("w", encoding="utf-8") as f:
    f.write("# SDT Canonical Volume-by-Volume Outline\n\n")
    f.write("This is the canonical, exhaustive, cross-referenced outline of the SDT codebase.\n\n")
    f.write("## Global Source Index\n")
    f.write("- [source_index.md](source_index.md)\n\n")
    f.write("## Volumes\n")
    for v in volumes:
        f.write(f"- [Volume {v['id']}: {v['title']}](Volume_{v['id']}_{safe_name(v['title'])}.md)\n")

for old in out_dir.glob("Volume_*.md"):
    old.unlink()

for v in volumes:
    vol_name = f"Volume_{v['id']}_{safe_name(v['title'])}.md"
    with (out_dir / vol_name).open("w", encoding="utf-8") as f:
        f.write(f"# Volume {v['id']}: {v['title']}\n\n")
        f.write("## Books\n")
        for b in v["books"]:
            f.write(f"- Book {b['id']}: {b['title']}\n")
        f.write("\n")
        for b in v["books"]:
            f.write(f"## Book {b['id']}: {b['title']}\n\n")
            for c in b["chapters"]:
                f.write(f"### Chapter {c['id']}: {c['title']}\n")
                f.write("<details>\n<summary>Sources and cross-references (exhaustive)</summary>\n\n")
                all_files = list_files_for_sources(c["sources"])
                for p in all_files:
                    f.write(f"- [{p}](../{p})\n")
                f.write("\n</details>\n\n")

html_path = out_dir / "canonical_outline.html"
html_path.write_text(render_canonical_html(volumes, list_files_for_sources), encoding="utf-8")

# Generate consolidated SCSS file using mixin
chapters_scss_lines = [
    "// Chapter styling: All volumes, books, and chapters",
    "// Influences: cyberpunk navigation, greek ruins, holographic projections, smooth transitions, z-axis movement",
    "",
    "@import 'chapter-mixin';",
    "",
    "// Generate styles for all chapters using the mixin",
]
for v in volumes:
    for b in v["books"]:
        for c in b["chapters"]:
            chapter_id = f"vol{v['id']}-book{b['id']}-ch{c['id']}"
            chapters_scss_lines.append(f"@include chapter-styles('{chapter_id}');")

chapters_scss_path = scss_dir / "chapters.scss"
chapters_scss_path.write_text("\n".join(chapters_scss_lines), encoding="utf-8")

print("Canonical outline generated:", out_dir)
