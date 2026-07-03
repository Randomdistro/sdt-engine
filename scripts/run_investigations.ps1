# Batch compile/run Investigation .cpp tools (MSVC)
$ErrorActionPreference = "Continue"
$root = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
Set-Location $root

$vcvars = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
if (-not (Test-Path $vcvars)) {
    Write-Error "vcvars64.bat not found"
}

$outDir = Join-Path $root "build\investigations"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null
$logDir = Join-Path $outDir "logs"
New-Item -ItemType Directory -Force -Path $logDir | Out-Null

$cppFiles = Get-ChildItem -Path (Join-Path $root "Investigations") -Recurse -Filter "*.cpp" |
    Sort-Object FullName

$results = @()
foreach ($cpp in $cppFiles) {
    $rel = $cpp.FullName.Substring($root.Length + 1)
    $base = [System.IO.Path]::GetFileNameWithoutExtension($cpp.Name)
    $exe = Join-Path $outDir "$base.exe"
    $log = Join-Path $logDir "$base.log"

    $compileCmd = @"
call "$vcvars" >nul 2>&1 && cd /d "$root" && cl /nologo /std:c++20 /EHsc /O2 /I Engine\include /Fe:"$exe" "$($cpp.FullName)" 2>&1
"@
    $compileOut = cmd /c $compileCmd
    $compileOk = $LASTEXITCODE -eq 0 -and (Test-Path $exe)

    $runOk = $false
    $runOut = ""
    if ($compileOk) {
        $runOut = & $exe 2>&1 | Out-String
        $runOk = $LASTEXITCODE -eq 0
        Set-Content -Path $log -Value ($compileOut + "`n--- RUN ---`n" + $runOut) -Encoding UTF8
    } else {
        Set-Content -Path $log -Value $compileOut -Encoding UTF8
    }

    $dir = $cpp.DirectoryName
    $hasVerdict = (Get-ChildItem -Path $dir -Filter "*VERDICT*" -ErrorAction SilentlyContinue).Count -gt 0

    $results += [PSCustomObject]@{
        Tool = $rel
        Compile = if ($compileOk) { "OK" } else { "FAIL" }
        Run = if (-not $compileOk) { "SKIP" } elseif ($runOk) { "OK" } else { "FAIL" }
        HasVerdict = $hasVerdict
    }
}

$results | Format-Table -AutoSize
$summary = Join-Path $outDir "batch_summary.csv"
$results | Export-Csv -Path $summary -NoTypeInformation
Write-Host "Summary: $summary"
