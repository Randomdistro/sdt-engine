"""
CRMPLR — Blender Source Crumple Analysis
Runs semantic ring tokenization on the entire Blender codebase.
"""

import os, sys, re, collections, math, time

sys.stdout.reconfigure(encoding='utf-8')

# ═══════════════════════════════════════════════════════════════
# UNIVERSAL TOKEN RINGS
# ═══════════════════════════════════════════════════════════════

SEMANTIC_RINGS = {
    "CONDITIONAL":   ["if", "else", "switch", "case", "default"],
    "LOOP":          ["for", "while", "do", "break", "continue", "goto"],
    "TYPE_PRIM":     ["void", "int", "float", "double", "char", "bool",
                      "short", "long", "unsigned", "signed", "auto", "size_t",
                      "uint8_t", "uint16_t", "uint32_t", "uint64_t",
                      "int8_t", "int16_t", "int32_t", "int64_t",
                      "uchar", "uint", "ushort", "ulong"],
    "TYPE_QUAL":     ["const", "constexpr", "consteval", "constinit",
                      "volatile", "mutable", "static", "inline", "extern",
                      "thread_local", "register", "restrict"],
    "ACCESS":        ["public", "private", "protected", "friend"],
    "CLASS":         ["class", "struct", "enum", "union", "namespace",
                      "template", "typename", "concept", "requires"],
    "OOP":           ["virtual", "override", "final",
                      "this", "new", "delete"],
    "FLOW":          ["return", "throw", "try", "catch", "noexcept"],
    "LOGIC":         ["true", "false", "nullptr", "NULL", "TRUE", "FALSE"],
    "PREPROC":       ["#include", "#define", "#ifdef", "#ifndef",
                      "#endif", "#pragma", "#if", "#else", "#elif",
                      "#undef", "#error", "#warning"],
    "CAST":          ["static_cast", "dynamic_cast", "reinterpret_cast",
                      "const_cast"],
    "MEMORY":        ["sizeof", "alignof", "offsetof", "decltype", "typeid"],
    "USING":         ["using", "typedef", "operator"],
    "STD_CONTAINER": ["std::vector", "std::string", "std::map",
                      "std::unordered_map", "std::set", "std::array",
                      "std::pair", "std::tuple", "std::optional",
                      "std::variant", "std::unique_ptr", "std::shared_ptr",
                      "std::span", "std::deque", "std::list",
                      "std::unordered_set", "std::string_view"],
    "STD_IO":        ["std::cout", "std::cin", "std::cerr", "std::endl",
                      "printf", "fprintf", "sprintf", "snprintf",
                      "sscanf", "scanf", "puts", "fputs", "fgets",
                      "fopen", "fclose", "fread", "fwrite", "fseek",
                      "ftell", "fflush", "stderr", "stdout", "stdin"],
    "STD_ALGO":      ["std::sort", "std::find", "std::transform",
                      "std::min", "std::max", "std::clamp", "std::abs",
                      "std::move", "std::forward", "std::swap"],
    "MATH":          ["sqrtf", "sqrt", "sinf", "sin", "cosf", "cos",
                      "tanf", "tan", "atan2f", "atan2", "fabsf", "fabs",
                      "floorf", "floor", "ceilf", "ceil", "roundf", "round",
                      "powf", "pow", "logf", "log", "expf", "exp",
                      "fminf", "fmin", "fmaxf", "fmax", "M_PI", "M_PI_2"],
    "ASSERT":        ["BLI_assert", "assert", "UNUSED", "UNUSED_VARS",
                      "BLI_ASSERT_UNIT_V3", "BLI_assert_msg"],
    "BRACKET":       ["{", "}", "(", ")", "[", "]", "<", ">", "<<", ">>"],
    "OPERATOR":      ["=", "==", "!=", "<=", ">=", "+=", "-=", "*=", "/=",
                      "++", "--", "&&", "||", "!", "&", "|", "^", "~",
                      "+", "-", "*", "/", "%", "::", "->", ".", ",", ";",
                      ":", "?", "|=", "&=", "^=", "<<=", ">>="],
}

TOKEN_TO_RING = {}
ALL_RING_TOKENS = set()
for ring_name, tokens in SEMANTIC_RINGS.items():
    for i, tok in enumerate(tokens):
        TOKEN_TO_RING[tok] = (ring_name, i)
        ALL_RING_TOKENS.add(tok)

# ═══════════════════════════════════════════════════════════════
# TOKENIZER
# ═══════════════════════════════════════════════════════════════

CPP_TOKEN_RE = re.compile(
    r'//.*?$|/\*.*?\*/|'               # comments
    r'"(?:[^"\\]|\\.)*"|'              # string literals
    r"'(?:[^'\\]|\\.)*'|"             # char literals
    r'#\s*\w+|'                        # preprocessor
    r'std::\w+(?:::\w+)?|'            # std:: qualified
    r'BLI_\w+|BKE_\w+|DNA_\w+|RNA_\w+|WM_\w+|ED_\w+|UI_\w+|GPU_\w+|'  # Blender API prefixes
    r'\b\w+\b|'                        # identifiers/keywords
    r'<<=|>>=|'                        # 3-char ops
    r'->|::|<<|>>|==|!=|<=|>=|\+=|-=|\*=|/=|&&|\|\||\+\+|--|&=|\|=|\^=|'  # 2-char ops
    r'[{}()\[\]<>;,.:=+\-*/%&|^~!?]', # single-char ops
    re.MULTILINE | re.DOTALL
)

def tokenize_file(filepath):
    try:
        with open(filepath, encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except:
        return None

    tokens = []
    strings = []

    for match in CPP_TOKEN_RE.finditer(content):
        tok = match.group(0)
        if tok.startswith('//') or tok.startswith('/*'):
            continue
        if tok.startswith('"'):
            strings.append(tok)
            tokens.append('^STRING')
            continue
        if tok.startswith("'"):
            tokens.append('^CHAR')
            continue
        if tok.startswith('#'):
            tok = '#' + tok.lstrip('#').strip()
        if re.match(r'^[0-9]', tok):
            tokens.append('^NUM')
            continue
        tokens.append(tok)

    return tokens, strings

# ═══════════════════════════════════════════════════════════════
# ANALYSIS
# ═══════════════════════════════════════════════════════════════

def main():
    root = r'c:\Users\Jimmi\sdt-engine\crmplr\analysis\blender_src\source'

    print("=" * 72)
    print("  CRMPLR — BLENDER SOURCE CRUMPLE ANALYSIS")
    print("=" * 72)
    print(f"\nScanning: {root}")

    t0 = time.time()

    all_tokens = []
    all_strings = []
    file_count = 0
    total_raw_bytes = 0
    files_by_module = collections.Counter()

    for r, dirs, files in os.walk(root):
        dirs[:] = [d for d in dirs if d not in ('.git', 'CMakeFiles', '__pycache__')]
        for fn in files:
            if fn.endswith(('.c', '.cc', '.cpp', '.h', '.hh', '.hpp')):
                path = os.path.join(r, fn)
                try:
                    total_raw_bytes += os.path.getsize(path)
                except:
                    pass
                result = tokenize_file(path)
                if result:
                    tokens, strings = result
                    all_tokens.extend(tokens)
                    all_strings.extend(strings)
                    file_count += 1
                    # Track module
                    rel = os.path.relpath(path, root)
                    parts = rel.split(os.sep)
                    module = parts[1] if len(parts) > 1 else parts[0]
                    files_by_module[module] += 1

    elapsed = time.time() - t0
    print(f"Scan time: {elapsed:.1f}s")
    print(f"Files scanned: {file_count:,}")
    print(f"Raw source size: {total_raw_bytes:,} bytes ({total_raw_bytes/1048576:.1f} MB)")

    unique_tokens = set(all_tokens)
    token_freq = collections.Counter(all_tokens)

    print(f"\n{'=' * 72}")
    print(f"  TOKENIZATION RESULTS")
    print(f"{'=' * 72}")
    print(f"  Total tokens:          {len(all_tokens):>12,}")
    print(f"  Unique tokens:         {len(unique_tokens):>12,}")
    print(f"  String literals:       {len(all_strings):>12,}")
    print(f"  Repetition ratio:      {len(all_tokens)/len(unique_tokens):>12.1f}x")

    # ── RING COVERAGE ──
    ring_hits = 0
    project_idents = collections.Counter()
    ring_usage = collections.Counter()
    blender_api = collections.Counter()

    for tok in all_tokens:
        if tok in TOKEN_TO_RING:
            ring_hits += 1
            ring_name, _ = TOKEN_TO_RING[tok]
            ring_usage[ring_name] += 1
        elif tok.startswith('^'):
            ring_hits += 1
        elif tok.startswith(('BLI_', 'BKE_', 'DNA_', 'RNA_', 'WM_', 'ED_', 'UI_', 'GPU_')):
            blender_api[tok] += 1
            project_idents[tok] += 1
        else:
            project_idents[tok] += 1

    project_total = sum(project_idents.values())
    unique_project = len(project_idents)

    total_ring = len(ALL_RING_TOKENS)
    bits_ring = math.ceil(math.log2(max(total_ring, 2)))
    bits_project = math.ceil(math.log2(max(unique_project, 2)))

    print(f"\n{'=' * 72}")
    print(f"  SEMANTIC RING COVERAGE")
    print(f"{'=' * 72}")
    print(f"  Ring tokens (universal):     {ring_hits:>10,}  ({ring_hits/len(all_tokens)*100:.1f}%)")
    print(f"  Project identifiers:         {project_total:>10,}  ({project_total/len(all_tokens)*100:.1f}%)")
    print(f"  Unique project identifiers:  {unique_project:>10,}")
    print(f"  Blender API calls:           {sum(blender_api.values()):>10,}  ({len(blender_api):,} unique)")
    print(f"\n  Universal ring tokens:  {total_ring:>6} -> {bits_ring} bits")
    print(f"  Project identifiers:    {unique_project:>6} -> {bits_project} bits")

    print(f"\n  Ring usage breakdown:")
    for ring, count in sorted(ring_usage.items(), key=lambda x: -x[1]):
        pct = count / len(all_tokens) * 100
        bar = "#" * min(int(pct * 2), 60)
        print(f"    {ring:<16} {count:>10,}  ({pct:>5.1f}%)  {bar}")

    # ── TOP PROJECT IDENTIFIERS ──
    print(f"\n{'=' * 72}")
    print(f"  TOP 40 PROJECT IDENTIFIERS")
    print(f"{'=' * 72}\n")
    for ident, count in project_idents.most_common(40):
        print(f"    {count:>7,}x  {ident}")

    # ── TOP BLENDER API CALLS ──
    print(f"\n{'=' * 72}")
    print(f"  TOP 30 BLENDER API FUNCTIONS")
    print(f"{'=' * 72}\n")
    for ident, count in blender_api.most_common(30):
        print(f"    {count:>7,}x  {ident}")

    # ── TRANSITION ANALYSIS ──
    print(f"\n{'=' * 72}")
    print(f"  RING-INTERNAL TRANSITIONS (delta encoding)")
    print(f"{'=' * 72}\n")
    ring_transitions = collections.Counter()
    for i in range(len(all_tokens) - 1):
        t1, t2 = all_tokens[i], all_tokens[i+1]
        if t1 in TOKEN_TO_RING and t2 in TOKEN_TO_RING:
            r1, p1 = TOKEN_TO_RING[t1]
            r2, p2 = TOKEN_TO_RING[t2]
            if r1 == r2:
                delta = p2 - p1
                ring_transitions[(r1, t1, t2, delta)] += 1

    for (ring, t1, t2, delta), count in sorted(
        ring_transitions.items(), key=lambda x: -x[1])[:30]:
        direction = f"f{delta}" if delta >= 0 else f"b{abs(delta)}"
        print(f"    {count:>7,}x  [{ring:<14}]  {t1:<24} -> {direction:>4} -> {t2}")

    # ── TOP BIGRAMS ──
    print(f"\n{'=' * 72}")
    print(f"  TOP 30 TOKEN BIGRAMS")
    print(f"{'=' * 72}\n")
    bigrams = collections.Counter()
    for i in range(len(all_tokens) - 1):
        bigrams[(all_tokens[i], all_tokens[i+1])] += 1
    for (t1, t2), count in bigrams.most_common(30):
        print(f"    {count:>7,}x  {t1} {t2}")

    # ── PHRASE ANALYSIS (sample first 500K tokens for speed) ──
    print(f"\n{'=' * 72}")
    print(f"  REPEATED PHRASES (sampling first 500K tokens)")
    print(f"{'=' * 72}\n")

    sample = all_tokens[:500000]
    phrase_counts = collections.Counter()
    for length in range(3, 9):
        for i in range(len(sample) - length + 1):
            phrase = tuple(sample[i:i+length])
            if all(t in '{}();,.' for t in phrase):
                continue
            phrase_counts[phrase] += 1

    scored = []
    for phrase, count in phrase_counts.items():
        if count >= 5:
            char_len = sum(len(t) for t in phrase) + len(phrase) - 1
            bytes_saved = (count - 1) * char_len
            scored.append((phrase, count, bytes_saved))
    scored.sort(key=lambda x: -x[2])

    total_phrase_savings = 0
    for phrase, count, saved in scored[:40]:
        phrase_str = " ".join(phrase)
        if len(phrase_str) > 60:
            phrase_str = phrase_str[:57] + "..."
        total_phrase_savings += saved
        print(f"    {count:>6}x  ^({saved:>7,}B)  {phrase_str}")

    # ── COMPRESSION ESTIMATE ──
    print(f"\n{'=' * 72}")
    print(f"  CRMPLR COMPRESSION ESTIMATE — BLENDER")
    print(f"{'=' * 72}")

    original_bytes = total_raw_bytes
    
    # Token-only encoding
    ring_bits = ring_hits * (2 + bits_ring)
    proj_bits = project_total * (2 + bits_project)
    token_only_bytes = (ring_bits + proj_bits) / 8

    # With phrase dedup (conservative — only top 200 phrases from sample, scaled)
    phrase_savings_bits = 0
    for phrase, count, saved in scored[:200]:
        phrase_tokens = len(phrase)
        avg_bits = (2 + max(bits_ring, bits_project))
        original_bits_per = phrase_tokens * avg_bits
        phrase_savings_bits += (count - 1) * (original_bits_per - 14)

    with_phrases_bytes = max((ring_bits + proj_bits - phrase_savings_bits) / 8, 1)

    print(f"\n  Raw source on disk:                  {original_bytes:>12,} bytes  ({original_bytes/1048576:.1f} MB)")
    print(f"  CRMPLR token encoding:               {int(token_only_bytes):>12,} bytes  ({int(token_only_bytes)/1048576:.1f} MB)  [{(1-token_only_bytes/original_bytes)*100:.1f}% reduction]")
    print(f"  CRMPLR + phrase dedup:               {int(with_phrases_bytes):>12,} bytes  ({int(with_phrases_bytes)/1048576:.1f} MB)  [{(1-with_phrases_bytes/original_bytes)*100:.1f}% reduction]")
    print(f"  Top phrase savings (sampled):         {total_phrase_savings:>12,} bytes")
    print(f"\n  Encoding:")
    print(f"    Ring tokens:     {bits_ring:>2} bits + 2-bit prefix = {2+bits_ring:>2} bits")
    print(f"    Project idents:  {bits_project:>2} bits + 2-bit prefix = {2+bits_project:>2} bits")
    print(f"    Phrase refs:     12 bits + 2-bit prefix = 14 bits")

    # ── UNIQUE TOKEN CENSUS ──
    print(f"\n{'=' * 72}")
    print(f"  UNIVERSAL TOKEN CENSUS")
    print(f"{'=' * 72}")
    print(f"\n  Across {file_count:,} files and {len(all_tokens):,} tokens:")
    print(f"  Only {len(unique_tokens):,} unique tokens exist.")
    print(f"  Of those, {total_ring} are universal ring tokens (sub-{bits_ring+2} bits).")
    print(f"  The remaining {unique_project:,} are project-specific ({bits_project+2} bits).")
    print(f"\n  Average token reuse: {len(all_tokens)/len(unique_tokens):.1f}x")
    print(f"  Top token reuse: {token_freq.most_common(1)[0][1]:,}x ({token_freq.most_common(1)[0][0]})")

    # Token frequency distribution
    print(f"\n  Token frequency distribution:")
    freq_buckets = {1: 0, 2: 0, '3-10': 0, '11-100': 0, '101-1000': 0, '1000+': 0}
    for tok, cnt in token_freq.items():
        if cnt == 1: freq_buckets[1] += 1
        elif cnt == 2: freq_buckets[2] += 1
        elif cnt <= 10: freq_buckets['3-10'] += 1
        elif cnt <= 100: freq_buckets['11-100'] += 1
        elif cnt <= 1000: freq_buckets['101-1000'] += 1
        else: freq_buckets['1000+'] += 1

    for bucket, count in freq_buckets.items():
        pct = count / len(unique_tokens) * 100
        print(f"    {str(bucket) + 'x':<10}  {count:>8,} unique tokens  ({pct:>5.1f}%)")

    print(f"\n{'=' * 72}")
    print(f"  CRUMPLE COMPLETE")
    print(f"{'=' * 72}")


if __name__ == '__main__':
    main()
