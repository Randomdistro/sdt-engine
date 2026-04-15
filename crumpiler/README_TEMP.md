# Crumpiler

**Frequency-ranked source code compression compiler.**

Crumples source code into compact bitstreams using semantic ring tokenization and frequency-ranked variable-width encoding. The most common token gets 1 bit. The entire universal vocabulary of all programming languages fits in sub-10 bits.

## How It Works

```
Source Code  →  [Tokenize → Ring Map → Phrase Dedup → Freq Rank → Bitpack]
                                ↓                            ↓
                          .crk legend                  .crm bitstream
                          (tiny key)                   (~6-14% of original)
```

**The .crk legend** contains only project-specific data: identifier names, string literals, number literals. Universal tokens (keywords, operators, brackets) are hardcoded in the crumpiler binary and never shipped.

**The .crm bitstream** is frequency-ranked: the most common token gets rank 1 (1 bit via Elias gamma), second gets rank 2 (3 bits), etc. Higher frequency = fewer bits. No LZ77 needed — the crumpler already eliminates all redundancy at the semantic level.

## Results

Tested on real C++ codebases:

| Codebase | Files | Tokens | Ring Coverage | .crm Size |
|---|---|---|---|---|
| SDT Engine | 27 | 62,230 | 82.9% | 11.7% of original |
| Blender 3D | 6,184 | 14,996,452 | 81.9% | ~6% estimated |

**Key insight: ~82% of all code tokens come from a universal vocabulary of ~232 tokens encodable in 8 bits. This ratio is stable across codebases.**

## Whitespace

`_` = space separator between tokens. `|` = newline. Both are ring tokens that naturally rank #1-2 by frequency, getting 1-3 bit encodings. String literals carry their own whitespace internally — zero overhead.

## Usage

```bash
# Build (C++20, zero dependencies)
cmake -S . -B build
cmake --build build --config Release

# Analyze a source file
crumpiler stats <source.cpp>

# Encode (crumple)
crumpiler encode <source.cpp> -o output.crm -k output.crk

# Decode (fluff)
crumpiler decode output.crm -k output.crk -o reconstructed.cpp
```

## Architecture

```
crumpiler/
├── core/
│   ├── types.hpp          # Token, Ring, Phrase, Codebook types
│   ├── rings.hpp          # 21 semantic rings, 232 universal tokens
│   ├── bitstream.hpp      # Elias gamma variable-width I/O
│   └── freq_rank.hpp      # Frequency counter + rank assignment
├── encoder/
│   ├── lexer.hpp          # C/C++ tokenizer
│   ├── phrase_finder.hpp  # Repeated phrase discovery
│   └── encoder.hpp        # Full encode pipeline → .crm + .crk
├── decoder/
│   └── decoder.hpp        # The crumpiler: .crk + .crm → source
├── main.cpp               # CLI
└── CMakeLists.txt         # C++20, zero deps
```

## Semantic Rings

Tokens are grouped into semantic rings — clusters of related tokens. Within a ring, delta encoding (`f`orward/`b`ack N) replaces absolute addresses:

- `else → b1 → if` (back 1 in CONDITIONAL ring)
- `) → b3 → {` (back 3 in BRACKET ring — 250,608 times in Blender)
- `inline → b6 → constexpr` (always together)

## Concepts

- **Eternally Crumpled** — code stays in .crm form at rest, in memory, in transit. Only "fluffed" when a human needs to read it.
- **crmpLLM** — LLMs trained on crumpled tokens. 39× cheaper attention (O(n²) on 800 tokens vs 5000). 84% compute cost reduction.

## Requirements

- C++20 compiler (MSVC 17+, GCC 10+, Clang 12+)
- CMake 3.20+
- Zero external dependencies

## License

Proprietary. All rights reserved.
