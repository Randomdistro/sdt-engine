# Build and run one Textbook instrument, saving its output as the next numbered run.
# Usage: powershell -File Textbook\tools\tb_run.ps1 -Stem ch10_occlusion_geometry [-Id ch10]
# Runs are never overwritten: ch10_run1_output.txt, ch10_run2_output.txt, ... (a failed run stays on record).
param(
    [Parameter(Mandatory = $true)][string]$Stem,
    [string]$Id = ($Stem -replace '_.*', '')
)
$ErrorActionPreference = 'Continue'
$root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
$bat = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat'
$build = Join-Path $env:TEMP 'tb_build'
New-Item -ItemType Directory -Force $build | Out-Null
$src = Join-Path $root "Textbook\examples\$Stem.cpp"
$exe = Join-Path $build "$Stem.exe"
if (-not (Test-Path $src)) { Write-Output "NO SOURCE: $src"; exit 2 }
$cmd = "call `"$bat`" >nul 2>&1 && cd /d `"$root`" && cl /nologo /std:c++20 /EHsc /O2 /utf-8 /W4 /I Engine\include /I Textbook\examples /Fo:`"$build\\`" /Fe:`"$exe`" `"$src`""
$log = cmd /c $cmd 2>&1 | Out-String
if (-not (Test-Path $exe) -or ((Get-Item $exe).LastWriteTime -lt (Get-Item $src).LastWriteTime)) {
    Write-Output "BUILD FAILED"
    Write-Output $log
    exit 1
}
Write-Output $log.Trim()
$val = Join-Path $root 'Textbook\validation'
$n = 1
while (Test-Path (Join-Path $val "${Id}_run${n}_output.txt")) { $n++ }
$outfile = Join-Path $val "${Id}_run${n}_output.txt"
Set-Location $root
$out = & $exe 2>&1 | Out-String
$code = $LASTEXITCODE
[System.IO.File]::WriteAllText($outfile, $out, (New-Object System.Text.UTF8Encoding($false)))
Write-Output $out
Write-Output "exit=$code  saved: $outfile"
exit $code
