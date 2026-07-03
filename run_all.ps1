$ErrorActionPreference = "Stop"

$Port = if ($env:PORT) { $env:PORT } else { "8787" }
$HostName = if ($env:HOST) { $env:HOST } else { "127.0.0.1" }
$Python = if ($env:PYTHON) { $env:PYTHON } else { "python" }

$requiredFiles = @(
  "scripts/build_sdt_trewrite_modelse run run_all.ps1 for me
  .py",
  "scripts/build_sdt_vortex_flow_model.py",
  "scripts/enrich_isotope_catalog.py",
  "scripts/serve_sdt_nuclear_viewer.py",
  "assets/data/isotope_catalog_sample.json"
)

foreach ($file in $requiredFiles) {
  if (-not (Test-Path -LiteralPath $file -PathType Leaf)) {
    Write-Error "Missing required file: $file. Run this script from the project root."
  }
}

New-Item -ItemType Directory -Force -Path "assets/models" | Out-Null

Write-Host "Building SDT rewrite model..."
& $Python scripts/build_sdt_rewrite_model.py

Write-Host "Building SDT vortex flow model..."
& $Python scripts/build_sdt_vortex_flow_model.py

Write-Host "Enriching isotope catalog..."
& $Python scripts/enrich_isotope_catalog.py `
  --input assets/data/isotope_catalog_sample.json `
  --output assets/models/sdt_isotope_catalog_enriched.json

Write-Host "Starting SDT nuclear viewer on http://${HostName}:${Port} ..."
$server = Start-Process `
  -FilePath $Python `
  -ArgumentList @("scripts/serve_sdt_nuclear_viewer.py") `
  -PassThru `
  -WindowStyle Hidden

try {
  $viewerUrl = "http://${HostName}:${Port}/tools/sdt_nuclear_viewer.html"
  $rewriteUrl = "http://${HostName}:${Port}/assets/models/sdt_rewrite_model_he_to_ne.json"

  $ready = $false
  for ($i = 0; $i -lt 30; $i++) {
    try {
      Invoke-WebRequest -Uri $viewerUrl -Method Head -UseBasicParsing | Out-Null
      $ready = $true
      break
    } catch {
      Start-Sleep -Milliseconds 500
    }
  }

  if (-not $ready) {
    throw "Server did not become ready at $viewerUrl"
  }

  Invoke-WebRequest -Uri $viewerUrl -Method Head -UseBasicParsing | Out-Null
  Invoke-WebRequest -Uri $rewriteUrl -Method Head -UseBasicParsing | Out-Null

  Write-Host ""
  Write-Host "All done."
  Write-Host "Viewer: $viewerUrl"
  Write-Host "Rewrite JSON: $rewriteUrl"
  Write-Host ""
  Write-Host "Server is running as process $($server.Id). Close this window or press Ctrl+C to stop it."

  Wait-Process -Id $server.Id
} finally {
  if ($server -and -not $server.HasExited) {
    Stop-Process -Id $server.Id -Force
  }
}
