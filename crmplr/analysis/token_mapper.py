"""
CRMPLR Token Mapper — Semantic Ring Analyzer
Maps all tokens in C++ codebases, identifies semantic rings,
measures transition probabilities, and demonstrates delta encoding.
"""

import os, sys, re, collections, json, math

sys.stdout.reconfigure(encoding='utf-8')

# ═══════════════════════════════════════════════════════════════
# UNIVERSAL TOKEN RINGS — Semantic clusters of related tokens
# Tokens within a ring are traversable via forward/backward delta
# ═══════════════════════════════════════════════════════════════

SEMANTIC_RINGS = {
    "CONDITIONAL":   ["if", "else", "switch", "case", "default"],
    "LOOP":          ["for", "while", "do", "break", "continue"],
    "TYPE_PRIM":     ["void", "int", "float", "double", "char", "bool",
                      "short", "long", "unsigned", "signed", "auto", "size_t"],
    "TYPE_QUAL":     ["const", "constexpr", "consteval", "constinit",
                      "volatile", "mutable", "static", "inline", "extern",
                      "thread_local", "register"],
    "ACCESS":        ["public", "private", "protected", "friend"],
    "CLASS":         ["class", "struct", "enum", "union", "namespace",
                      "template", "typename", "concept", "requires"],
    "OOP":           ["virtual", "override", "final", "abstract",
                      "this", "new", "delete"],
    "FLOW":          ["return", "throw", "try", "catch", "noexcept",
                      "co_return", "co_yield", "co_await"],
    "LOGIC":         ["true", "false", "nullptr", "NULL"],
    "INCLUDE":       ["#include", "#define", "#ifdef", "#ifndef",
                      "#endif", "#pragma", "#if", "#else", "#elif", "#undef"],
    "CAST":          ["static_cast", "dynamic_cast", "reinterpret_cast",
                      "const_cast"],
    "MEMORY":        ["sizeof", "alignof", "alignas", "decltype", "typeid"],
    "USING":         ["using", "typedef", "operator"],
    "STD_CONTAINER": ["std::vector", "std::string", "std::map",
                      "std::unordered_map", "std::set", "std::array",
                      "std::pair", "std::tuple", "std::optional",
                      "std::variant", "std::unique_ptr", "std::shared_ptr",
                      "std::weak_ptr", "std::span"],
    "STD_IO":        ["std::cout", "std::cin", "std::cerr", "std::endl",
                      "std::setw", "std::setprecision", "std::fixed",
                      "std::left", "std::right", "std::scientific",
                      "std::noshowpos", "std::showpos", "printf", "fprintf",
                      "sprintf"],
    "STD_ALGO":      ["std::sort", "std::find", "std::transform",
                      "std::accumulate", "std::for_each", "std::count",
                      "std::min", "std::max", "std::clamp", "std::abs",
                      "std::pow", "std::sqrt", "std::log", "std::exp",
                      "std::sin", "std::cos", "std::tan", "std::atan2",
                      "std::floor", "std::ceil", "std::round",
                      "std::numbers::pi"],
    "BRACKET":       ["{", "}", "(", ")", "[", "]", "<", ">", "<<", ">>"],
    "OPERATOR":      ["=", "==", "!=", "<=", ">=", "+=", "-=", "*=", "/=",
                      "++", "--", "&&", "||", "!", "&", "|", "^", "~",
                      "+", "-", "*", "/", "%", "::", "->", ".", ",", ";",
                      ":", "?"],
}

# Build reverse lookup: token -> (ring_name, position_in_ring)
TOKEN_TO_RING = {}
ALL_RING_TOKENS = set()
for ring_name, tokens in SEMANTIC_RINGS.items():
    for i, tok in enumerate(tokens):
        TOKEN_TO_RING[tok] = (ring_name, i)
        ALL_RING_TOKENS.add(tok)

# ═══════════════════════════════════════════════════════════════
# TOKENIZER — Extract tokens from C++ source
# ═══════════════════════════════════════════════════════════════

# Multi-char tokens must be checked before single-char
MULTI_CHAR_OPS = sorted([
    "::", "->", "<<", ">>", "==", "!=", "<=", ">=", "+=", "-=",
    "*=", "/=", "&&", "||", "++", "--", "##",
], key=lambda x: -len(x))

CPP_TOKEN_RE = re.compile(
    r'//.*?$|/\*.*?\*/|'               # comments
    r'"(?:[^"\\]|\\.)*"|'              # string literals
    r"'(?:[^'\\]|\\.)'|"              # char literals
    r'#\s*\w+|'                        # preprocessor
    r'std::\w+(?:::\w+)?|'            # std:: qualified
    r'\b\w+\b|'                        # identifiers/keywords
    r'->|::|<<|>>|==|!=|<=|>=|\+=|-=|\*=|/=|&&|\|\||\+\+|--|'  # multi-char ops
    r'[{}()\[\]<>;,.:=+\-*/%&|^~!?]', # single-char ops
    re.MULTILINE | re.DOTALL
)

def tokenize_file(filepath):
    """Tokenize a C++ source file into a list of tokens."""
    try:
        with open(filepath, encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except:
        return []
    
    tokens = []
    strings = []
    
    for match in CPP_TOKEN_RE.finditer(content):
        tok = match.group(0)
        
        # Skip comments
        if tok.startswith('//') or tok.startswith('/*'):
            continue
        
        # Capture string literals separately
        if tok.startswith('"'):
            strings.append(tok)
            tokens.append('^STRING')
            continue
        if tok.startswith("'"):
            tokens.append('^CHAR')
            continue
        
        # Normalize preprocessor
        if tok.startswith('#'):
            tok = '#' + tok.lstrip('#').strip()
        
        # Pure numbers -> ^NUM
        if re.match(r'^[0-9]', tok):
            tokens.append('^NUM')
            continue
            
        tokens.append(tok)
    
    return tokens, strings

# ═══════════════════════════════════════════════════════════════
# ANALYSIS ENGINE
# ═══════════════════════════════════════════════════════════════

def analyze_codebase(root):
    all_tokens = []
    all_strings = []
    file_count = 0
    
    for r, dirs, files in os.walk(root):
        # Skip build dirs
        dirs[:] = [d for d in dirs if d not in ('build', '.git', 'CMakeFiles', '__pycache__', 'crmplr')]
        for fn in files:
            if fn.endswith(('.cpp', '.hpp', '.h')):
                path = os.path.join(r, fn)
                result = tokenize_file(path)
                if result:
                    tokens, strings = result
                    all_tokens.extend(tokens)
                    all_strings.extend(strings)
                    file_count += 1
    
    return all_tokens, all_strings, file_count


def compute_ring_stats(tokens):
    """Compute how many tokens fall into semantic rings vs project-specific."""
    ring_hits = 0
    project_idents = collections.Counter()
    ring_usage = collections.Counter()
    
    for tok in tokens:
        if tok in TOKEN_TO_RING:
            ring_hits += 1
            ring_name, _ = TOKEN_TO_RING[tok]
            ring_usage[ring_name] += 1
        elif tok.startswith('^'):
            ring_hits += 1  # these are encoded specially
        else:
            project_idents[tok] += 1
    
    return ring_hits, project_idents, ring_usage


def compute_transitions(tokens):
    """Compute token-to-token transition probabilities."""
    transitions = collections.Counter()
    ring_transitions = collections.Counter()
    
    for i in range(len(tokens) - 1):
        t1, t2 = tokens[i], tokens[i+1]
        transitions[(t1, t2)] += 1
        
        # Track ring-internal transitions (delta = small)
        if t1 in TOKEN_TO_RING and t2 in TOKEN_TO_RING:
            r1, p1 = TOKEN_TO_RING[t1]
            r2, p2 = TOKEN_TO_RING[t2]
            if r1 == r2:
                delta = p2 - p1
                ring_transitions[(r1, t1, t2, delta)] += 1
    
    return transitions, ring_transitions


def find_repeated_phrases(tokens, min_length=3, max_length=12):
    """Find repeated multi-token phrases — the crmplr sweet spot."""
    phrase_counts = collections.Counter()
    
    for length in range(min_length, max_length + 1):
        for i in range(len(tokens) - length + 1):
            phrase = tuple(tokens[i:i+length])
            # Skip phrases that are all punctuation
            if all(t in '{}();,.' for t in phrase):
                continue
            phrase_counts[phrase] += 1
    
    # Filter to phrases appearing 3+ times
    return {p: c for p, c in phrase_counts.items() if c >= 3}


def compute_bits_needed(unique_count):
    """How many bits to encode N unique items."""
    if unique_count <= 0:
        return 0
    return math.ceil(math.log2(max(unique_count, 2)))


# ═══════════════════════════════════════════════════════════════
# MAIN ANALYSIS
# ═══════════════════════════════════════════════════════════════

def main():
    root = r'c:\Users\Jimmi\sdt-engine'
    
    print("═" * 72)
    print("  CRMPLR — SEMANTIC RING ANALYSIS & TOKEN MAPPING")
    print("═" * 72)
    print(f"\nScanning: {root}\n")
    
    tokens, strings, file_count = analyze_codebase(root)
    
    if not tokens:
        print("No tokens found!")
        return
    
    unique_tokens = set(tokens)
    token_freq = collections.Counter(tokens)
    
    # ── BASIC STATS ──
    print(f"Files scanned:        {file_count}")
    print(f"Total tokens:         {len(tokens):,}")
    print(f"Unique tokens:        {len(unique_tokens):,}")
    print(f"String literals:      {len(strings):,}")
    print(f"Tokens per unique:    {len(tokens)/len(unique_tokens):.1f}x repetition")
    
    # ── RING COVERAGE ──
    print(f"\n{'─' * 72}")
    print("  SEMANTIC RING COVERAGE")
    print(f"{'─' * 72}")
    
    ring_hits, project_idents, ring_usage = compute_ring_stats(tokens)
    project_total = sum(project_idents.values())
    
    print(f"\n  Ring tokens (universal):    {ring_hits:>8,}  ({ring_hits/len(tokens)*100:.1f}%)")
    print(f"  Project identifiers:        {project_total:>8,}  ({project_total/len(tokens)*100:.1f}%)")
    print(f"  Unique project identifiers: {len(project_idents):>8,}")
    
    # Bits needed
    total_ring_tokens = len(ALL_RING_TOKENS)
    bits_ring = compute_bits_needed(total_ring_tokens)
    bits_project = compute_bits_needed(len(project_idents))
    
    print(f"\n  Universal ring tokens:  {total_ring_tokens:>4} → {bits_ring} bits to encode")
    print(f"  Project identifiers:    {len(project_idents):>4} → {bits_project} bits to encode")
    
    # ── RING USAGE BREAKDOWN ──
    print(f"\n  Ring usage by category:")
    for ring, count in sorted(ring_usage.items(), key=lambda x: -x[1]):
        pct = count / len(tokens) * 100
        bar = "█" * int(pct * 2)
        print(f"    {ring:<16} {count:>6,}  ({pct:>5.1f}%)  {bar}")
    
    # ── TOP PROJECT IDENTIFIERS ──
    print(f"\n{'─' * 72}")
    print("  TOP PROJECT IDENTIFIERS (programmer-chosen)")
    print(f"{'─' * 72}\n")
    
    for ident, count in project_idents.most_common(30):
        print(f"    {count:>5}x  {ident}")
    
    # ── TRANSITION ANALYSIS (for delta encoding) ──
    print(f"\n{'─' * 72}")
    print("  RING-INTERNAL TRANSITIONS (delta encoding candidates)")
    print(f"{'─' * 72}\n")
    
    transitions, ring_transitions = compute_transitions(tokens)
    
    if ring_transitions:
        print("  These transitions stay WITHIN a semantic ring (small delta):\n")
        for (ring, t1, t2, delta), count in sorted(
            ring_transitions.items(), key=lambda x: -x[1])[:25]:
            direction = f"f{delta}" if delta > 0 else f"b{abs(delta)}"
            print(f"    {count:>5}x  [{ring:<14}]  {t1:<20} → {direction} → {t2}")
    
    # ── TOP TOKEN TRANSITIONS ──
    print(f"\n{'─' * 72}")
    print("  TOP TOKEN BIGRAMS (most common two-token sequences)")
    print(f"{'─' * 72}\n")
    
    for (t1, t2), count in transitions.most_common(30):
        print(f"    {count:>5}x  {t1} {t2}")
    
    # ── REPEATED PHRASES ──
    print(f"\n{'─' * 72}")
    print("  REPEATED MULTI-TOKEN PHRASES (crmplr targets)")
    print(f"{'─' * 72}\n")
    
    phrases = find_repeated_phrases(tokens, min_length=3, max_length=10)
    
    # Sort by bytes saved (count * phrase_length)
    scored = []
    for phrase, count in phrases.items():
        char_len = sum(len(t) for t in phrase) + len(phrase) - 1
        bytes_saved = (count - 1) * char_len
        scored.append((phrase, count, bytes_saved))
    
    scored.sort(key=lambda x: -x[2])
    
    total_phrase_savings = 0
    for phrase, count, saved in scored[:40]:
        phrase_str = " ".join(phrase)
        if len(phrase_str) > 65:
            phrase_str = phrase_str[:62] + "..."
        total_phrase_savings += saved
        print(f"    {count:>4}x  ^({saved:>5}B)  {phrase_str}")
    
    # ── COMPRESSION ESTIMATE ──
    print(f"\n{'═' * 72}")
    print("  CRMPLR COMPRESSION ESTIMATE")
    print(f"{'═' * 72}")
    
    original_chars = sum(len(t) for t in tokens) + len(tokens)  # tokens + spaces
    
    # Ring tokens: 2-bit prefix + bits_ring
    ring_token_bits = ring_hits * (2 + bits_ring)
    # Project idents: 2-bit prefix + bits_project
    project_token_bits = project_total * (2 + bits_project)
    # Total without phrase compression
    total_bits = ring_token_bits + project_token_bits
    total_bytes = total_bits / 8
    
    # With phrase compression (top phrases become single tokens)
    phrase_token_savings = 0
    for phrase, count, saved in scored[:200]:
        # Each occurrence after first becomes a single 14-bit token
        phrase_tokens = len(phrase)
        original_bits_per = phrase_tokens * (2 + max(bits_ring, bits_project))
        replacement_bits = 14  # phrase token
        phrase_token_savings += (count - 1) * (original_bits_per - replacement_bits)
    
    total_bits_with_phrases = total_bits - phrase_token_savings
    total_bytes_with_phrases = max(total_bits_with_phrases / 8, 1)
    
    original_bytes = original_chars
    
    print(f"\n  Original (ASCII):                    {original_bytes:>10,} bytes")
    print(f"  CRMPLR (token encoding only):        {int(total_bytes):>10,} bytes  ({(1-total_bytes/original_bytes)*100:.1f}% reduction)")
    print(f"  CRMPLR (+ phrase dedup):             {int(total_bytes_with_phrases):>10,} bytes  ({(1-total_bytes_with_phrases/original_bytes)*100:.1f}% reduction)")
    print(f"  Top phrase savings alone:            {total_phrase_savings:>10,} bytes")
    print(f"\n  Encoding breakdown:")
    print(f"    Ring tokens:    {bits_ring} bits + 2-bit prefix = {2+bits_ring} bits per token")
    print(f"    Project idents: {bits_project} bits + 2-bit prefix = {2+bits_project} bits per token")
    print(f"    Phrase refs:    12 bits + 2-bit prefix = 14 bits per phrase")
    
    # ── CRMPLR NOTATION DEMO ──
    print(f"\n{'═' * 72}")
    print("  CRMPLR NOTATION DEMO — first 100 tokens encoded")
    print(f"{'═' * 72}\n")
    
    demo_tokens = tokens[:100]
    encoded = []
    for tok in demo_tokens:
        if tok in TOKEN_TO_RING:
            ring_name, pos = TOKEN_TO_RING[tok]
            encoded.append(f"R:{tok}")
        elif tok.startswith('^'):
            encoded.append(tok)
        else:
            encoded.append(f"P:{tok}")
    
    # Print in rows of ~6
    for i in range(0, len(encoded), 6):
        chunk = encoded[i:i+6]
        print(f"    {' | '.join(chunk)}")
    
    print(f"\n{'═' * 72}")
    print("  ANALYSIS COMPLETE")
    print(f"{'═' * 72}")

if __name__ == '__main__':
    main()
