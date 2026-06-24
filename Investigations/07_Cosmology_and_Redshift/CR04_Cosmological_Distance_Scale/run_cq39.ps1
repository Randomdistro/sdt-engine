# Compile and run CQ39 tool
$SourceFile = "cq39_cosmological_derivation.cpp"
$ExeFile = "cq39_derivation.exe"
$EngineInclude = "..\..\Engine\include"

# Try MSVC
Write-Host "Attempting compilation with MSVC cl.exe..."
$clPath = & where.exe cl.exe 2>$null
if ($clPath) {
    Write-Host "Found cl.exe at: $clPath"
    cl /std:c++20 /EHsc /O2 /I $EngineInclude /Fe:$ExeFile $SourceFile
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Compilation successful!"
        Write-Host "Running CQ39 derivation tool..."
        Write-Host "════════════════════════════════════════════════════════════════"
        & ".\$ExeFile"
        exit $LASTEXITCODE
    }
}

# Try clang++
Write-Host "MSVC not found. Trying clang++..."
$clangPath = & where.exe clang++ 2>$null
if ($clangPath) {
    Write-Host "Found clang++ at: $clangPath"
    clang++ -std=c++20 -O2 -I $EngineInclude -o $ExeFile $SourceFile
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Compilation successful!"
        Write-Host "Running CQ39 derivation tool..."
        Write-Host "════════════════════════════════════════════════════════════════"
        & ".\$ExeFile"
        exit $LASTEXITCODE
    }
}

Write-Error "No C++ compiler found!"
exit 1
