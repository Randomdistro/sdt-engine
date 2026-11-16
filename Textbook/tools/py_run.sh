#!/usr/bin/env bash
# Run one Python instrument from Textbook/examples in an isolated interpreter and save its output as the next numbered run.
# Usage: bash Textbook/tools/py_run.sh ch05_operator_law_map
set -u
stem="$1"
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
root="$(cd "$here/../.." && pwd)"
id="${stem%%_*}"
val="$root/Textbook/validation"
n=1
while [ -e "$val/${id}_run${n}_output.txt" ]; do n=$((n + 1)); done
out="$val/${id}_run${n}_output.txt"
cd "$root"
PYTHONIOENCODING=utf-8 python -I "Textbook/examples/${stem}.py" > "$out" 2>&1
code=$?
cat "$out"
echo "exit=$code saved: $out"
exit $code
