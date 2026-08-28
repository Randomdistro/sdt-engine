param(
    [ValidateRange(1, 65535)]
    [int]$Port = 8766
)

$workspaceRoot = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
Write-Host "Serving SDT Atomic Shell Modeller at http://127.0.0.1:$Port/Release/SDT_Atomic_Shell_Modeller/index.html"
Write-Host 'Press Ctrl+C to stop the server.'
python -m http.server $Port --directory $workspaceRoot
