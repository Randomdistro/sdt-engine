#!/usr/bin/env python3
"""
Combine all SDT volumes into a single markdown file.
Reads all Book.md files in order and combines them with proper separators.
"""

import os
from pathlib import Path

# Define the volume structure
VOLUMES = [
    ("Volume_01", "Foundations and Spation Primitives", [
        ("Book_01", "The Four Primitives and Master Equation"),
        ("Book_02", "Treatise Integration and Historical Consolidation"),
    ]),
    ("Volume_02", "Field Theory, Mechanics, and Mathematical Structure", [
        ("Book_01", "Continuum Mechanics from Spation Flow"),
        ("Book_02", "Mathematical Operators and State Space"),
    ]),
    ("Volume_03", "Atomic Physics (Summary Only; Full Canon in ATOMICUS)", [
        ("Book_01", "Atomic Physics Summary and Links"),
    ]),
    ("Volume_04", "Electromagnetism and Magnetic Phenomena", [
        ("Book_01", "Electricity from Spation Pressure"),
        ("Book_02", "Magnetic Moments and Helical Wakes"),
    ]),
    ("Volume_05", "Nuclear Physics and Particle Architecture", [
        ("Book_01", "Nucleon Structures"),
        ("Book_02", "Nuclear Packing and Geometry"),
    ]),
    ("Volume_06", "Thermodynamics and Statistical Mechanics", [
        ("Book_01", "Thermodynamics from Spation Contact Mechanics"),
        ("Book_02", "Transport and Statistical Mechanics"),
    ]),
    ("Volume_07", "Gravitation and Stellar Structure", [
        ("Book_01", "Gravitation from Spation Pressure Gradients"),
    ]),
    ("Volume_08", "Cosmology and Large-Scale Structure", [
        ("Book_01", "Cosmological Structure from Pressure Topology"),
    ]),
    ("Volume_09", "Chemistry and Nucleus-Driven Framework", [
        ("Book_01", "Nucleus-Driven Chemistry"),
    ]),
    ("Volume_10", "Molecular Structures Compendium", [
        ("Book_01", "Nucleus-Driven Chemistry Framework"),
        ("Book_02", "Simple Organic Molecules"),
        ("Book_03", "Complex Organic Molecules"),
        ("Book_04", "Aromatic Systems"),
        ("Book_05", "Heterocyclic Compounds"),
        ("Book_06", "Cyclic and Network Structures"),
        ("Book_07", "Polycyclic Systems"),
        ("Book_08", "Macromolecular Families"),
        ("Book_09", "Biomolecular Structures"),
        ("Book_10", "Coordination Compounds"),
        ("Book_11", "Organometallic Compounds"),
        ("Book_12", "Complex Synthetic Molecules"),
        ("Book_13", "Supramolecular Structures"),
    ]),
    ("Volume_11", "Validation, Benchmarks, and Empirical Tests", [
        ("Book_01", "Benchmark Suite and Validation Reports"),
        ("Book_02", "SDT vs Standard Physics"),
    ]),
    ("Volume_12", "Computation, Code, and Simulation Systems", [
        ("Book_01", "Code Constants and Computational Core"),
        ("Book_02", "Simulations and Visualizations"),
        ("Book_03", "Repository Automation and Build Systems"),
    ]),
    ("Volume_13", "Philosophy, Methodology, and Programmatics", [
        ("Book_01", "Methodology and Professionalization"),
        ("Book_02", "Investigations and Prompts"),
        ("Book_03", "Legacy Compilations and Alternate Builds"),
    ]),
]

def combine_volumes(base_dir: str, output_file: str):
    """Combine all volumes into a single markdown file."""
    
    base_path = Path(base_dir)
    output_path = base_path / output_file
    
    with open(output_path, 'w', encoding='utf-8') as outfile:
        # Write header
        outfile.write("# Spatial Displacement Theory: Complete Canonical Compendium\n\n")
        outfile.write("**Complete compilation of all volumes, books, and chapters of Spatial Displacement Theory.**\n\n")
        outfile.write("This document contains the entirety of the SDT canonical volumes, combining all books and chapters into a single comprehensive reference.\n\n")
        outfile.write("---\n\n")
        
        # Process each volume
        for vol_num, (vol_dir, vol_title, books) in enumerate(VOLUMES, 1):
            vol_path = base_path / vol_dir
            
            # Volume header
            outfile.write(f"\n\n{'=' * 80}\n\n")
            outfile.write(f"# Volume {vol_num:02d}: {vol_title}\n\n")
            outfile.write(f"{'=' * 80}\n\n")
            
            # Process each book in the volume
            for book_num, (book_dir, book_title) in enumerate(books, 1):
                book_path = vol_path / book_dir / "Book.md"
                
                if not book_path.exists():
                    outfile.write(f"\n## Book {book_num:02d}: {book_title}\n\n")
                    outfile.write("*[Book.md file not found]*\n\n")
                    continue
                
                # Book header
                outfile.write(f"\n\n{'-' * 80}\n\n")
                outfile.write(f"## Volume {vol_num:02d} — Book {book_num:02d}: {book_title}\n\n")
                outfile.write(f"{'-' * 80}\n\n")
                
                # Read and write book content
                try:
                    with open(book_path, 'r', encoding='utf-8') as infile:
                        content = infile.read()
                        
                        # Remove the book title if it's a duplicate (since we're adding our own)
                        lines = content.split('\n')
                        if lines and lines[0].startswith('# Volume'):
                            # Skip the first few lines that are just the volume/book title
                            start_idx = 0
                            for i, line in enumerate(lines):
                                if line.startswith('## Book Overview') or line.startswith('## Chapter'):
                                    start_idx = i
                                    break
                            content = '\n'.join(lines[start_idx:])
                        
                        outfile.write(content)
                        outfile.write("\n\n")
                        
                except Exception as e:
                    outfile.write(f"\n*[Error reading {book_path}: {e}]*\n\n")
        
        # Write footer
        outfile.write(f"\n\n{'=' * 80}\n\n")
        outfile.write("# End of Spatial Displacement Theory: Complete Canonical Compendium\n\n")
        outfile.write(f"{'=' * 80}\n\n")
    
    print(f"Combined all volumes into: {output_path}")
    print(f"File size: {output_path.stat().st_size / (1024*1024):.2f} MB")

if __name__ == "__main__":
    base_dir = Path(__file__).parent
    output_file = "SDT_Complete_Canonical_Compendium.md"
    combine_volumes(base_dir, output_file)
