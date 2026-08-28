param(
    [ValidateRange(1, 65535)]
    [int]$Port = 8765
)

$webRoot = Join-Path $PSScriptRoot "web"
if (-not (Test-Path -LiteralPath $webRoot -PathType Container)) {
    throw "Solver web directory not found: $webRoot"
}

Write-Host "SDT three-body solver is available at http://127.0.0.1:$Port/index.html"
Write-Host "Keep this window open while using the solver. Press Ctrl+C to stop it."
python -m http.server $Port --directory $webRoot
