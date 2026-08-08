# Fetch Cassini SCE1 (CORS_0021–0028) with correct volume routing.
# Large RSR/TLM -> C:\sdt-data\cassini_sce1 ; everything else -> Datasets/.../raw/cassini_sce1
$ErrorActionPreference = 'Continue'
$root = Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
if (-not (Test-Path (Join-Path $root 'Datasets'))) {
  $root = 'c:\Users\Jimmi\OneDrive\Desktop\sdt-engine'
}
$rawRoot = Join-Path $root 'Datasets\solar_propagation_2026-08\raw\cassini_sce1'
$extRoot = 'C:\sdt-data\cassini_sce1'
$log = Join-Path $root 'Datasets\solar_propagation_2026-08\FETCH_LOG_RESUME_2026-08-07.txt'
$pds = 'https://atmos.nmsu.edu/pdsd/archive/data/co-ss-rss-1-sce1-v10'
New-Item -ItemType Directory -Force -Path $rawRoot, $extRoot | Out-Null

$ok=0; $fail=0; $skip=0; $bytes=0
function Log([string]$m) {
  $line = '[{0}] {1}' -f (Get-Date -Format o), $m
  Add-Content -Path $log -Value $line
  Write-Host $line
}
function Sha([string]$p) { (Get-FileHash -Algorithm SHA256 $p).Hash.ToLowerInvariant() }
function Save([string]$url, [string]$dest) {
  $parent = Split-Path $dest -Parent
  New-Item -ItemType Directory -Force -Path $parent | Out-Null
  if ((Test-Path $dest) -and ((Get-Item $dest).Length -gt 0)) {
    # Reject truncated product binaries left by interrupted transfers
    $ext = [IO.Path]::GetExtension($dest).ToLowerInvariant()
    $len = (Get-Item $dest).Length
    $minOk = switch ($ext) {
      '.tdf' { 100000 }
      '.odf' { 10000 }
      '.rsr' { 100000 }
      '.1a1' { 100000 }
      '.1b1' { 100000 }
      '.2b1' { 100000 }
      '.3a1' { 100000 }
      '.515' { 100000 }
      '.158' { 100000 }
      default { 1 }
    }
    if ($len -ge $minOk) {
      $script:skip++; return "SKIP $len $dest"
    }
    Remove-Item -Force -ErrorAction SilentlyContinue $dest
  }
  for ($attempt=1; $attempt -le 3; $attempt++) {
    try {
      Invoke-WebRequest -Uri $url -OutFile $dest -UseBasicParsing -TimeoutSec 900
      $len = (Get-Item $dest).Length
      if ($len -le 0) { throw 'zero-byte download' }
      $script:bytes += $len; $script:ok++
      return "OK $len $(Sha $dest) $dest"
    } catch {
      if ($attempt -eq 3) {
        $script:fail++
        Remove-Item -Force -ErrorAction SilentlyContinue $dest
        return "FAIL $url :: $($_.Exception.Message)"
      }
      Start-Sleep -Seconds (2 * $attempt)
    }
  }
}

function VolForDoy([int]$doy) {
  if ($doy -ge 157 -and $doy -le 160) { return 'cors_0021' }
  if ($doy -ge 161 -and $doy -le 164) { return 'cors_0022' }
  if ($doy -ge 165 -and $doy -le 168) { return 'cors_0023' }
  if ($doy -ge 169 -and $doy -le 172) { return 'cors_0024' }
  if ($doy -ge 173 -and $doy -le 176) { return 'cors_0025' }
  if ($doy -ge 177 -and $doy -le 180) { return 'cors_0026' }
  if ($doy -ge 181 -and $doy -le 184) { return 'cors_0027' }
  if ($doy -ge 185 -and $doy -le 186) { return 'cors_0028' }
  return $null
}

'Cassini SCE1 resume/fetch started' | Set-Content $log

# Ensure volume indexes exist
foreach ($v in 21..28) {
  $vol = "cors_00$v"
  foreach ($f in @('cumindex.tab','cumindex.lbl','index.tab','index.lbl','indxinfo.txt')) {
    Log (Save "$pds/$vol/index/$f" (Join-Path $rawRoot "$vol\index\$f"))
  }
  foreach ($f in @('aareadme.txt','errata.txt','voldesc.cat')) {
    Log (Save "$pds/$vol/$f" (Join-Path $rawRoot "$vol\$f"))
  }
}

# Ancillary / catalog / document listings
foreach ($v in 21..28) {
  $vol = "cors_00$v"
  foreach ($sub in @('sce1_ancillary/spk','sce1_ancillary/eop','sce1_ancillary/ion','sce1_ancillary/tro','sce1_ancillary/ckf','catalog','document')) {
    try {
      $html = (Invoke-WebRequest -Uri "$pds/$vol/$sub/" -UseBasicParsing -TimeoutSec 45).Content
      $names = [regex]::Matches($html, 'href="([^"?]+)"') |
        ForEach-Object { $_.Groups[1].Value.Trim('/') } |
        Where-Object { $_ -and $_ -notmatch '^(https?:|C=|\.\.|/)' -and $_ -notmatch 'pds-app-bar|/pdsd/|/archive/' -and $_ -notmatch '/' }
      foreach ($name in $names) {
        Log (Save "$pds/$vol/$sub/$name" (Join-Path $rawRoot "$vol\$($sub.Replace('/','\'))\$name"))
      }
    } catch {
      Log "LIST FAIL $pds/$vol/$sub/ :: $($_.Exception.Message)"
    }
  }
}

# Build unique product jobs from the latest cumulative index (cors_0028)
$idx = Join-Path $rawRoot 'cors_0028\index\cumindex.tab'
$jobs = New-Object 'System.Collections.Generic.List[object]'
$seen = @{}
foreach ($line in Get-Content $idx) {
  if ($line -notmatch '^"[^"]+","([^"]+)","([^"]+)"') { continue }
  $lblRel = $Matches[1].Trim() -replace '\\','/'
  $prodName = $Matches[2].Trim()
  if ([string]::IsNullOrWhiteSpace($prodName)) { continue }
  $parts = @($lblRel.Split('/') | Where-Object { $_ })
  if ($parts.Count -lt 2) { continue }
  $dayDir = $parts[0]          # SCE1_162
  $typeDir = $parts[1]         # TDF / ODF / RSR ...
  if ($dayDir -notmatch '^SCE1_(\d{3})$') { continue }
  $doy = [int]$Matches[1]
  $vol = VolForDoy $doy
  if (-not $vol) { Log "NO VOL for $dayDir"; continue }
  $lblFile = $parts[-1]
  $key = "$vol/$($dayDir.ToLower())/$($typeDir.ToLower())/$($prodName.ToLower())"
  if ($seen.ContainsKey($key)) { continue }
  $seen[$key] = $true
  $large = ($typeDir -match '^(RSR|TLM)$')
  $jobs.Add([pscustomobject]@{
    Vol=$vol; Day=$dayDir.ToLower(); Type=$typeDir.ToLower()
    Prod=$prodName.ToLower(); Lbl=$lblFile.ToLower(); Large=$large
  })
}
Log "Unique product jobs: $($jobs.Count)"

# Priority: non-large first
$ordered = @($jobs | Where-Object { -not $_.Large }) + @($jobs | Where-Object { $_.Large })
foreach ($j in $ordered) {
  $relDir = "$($j.Vol)\$($j.Day)\$($j.Type)"
  $urlBase = "$pds/$($j.Vol)/$($j.Day)/$($j.Type)"
  $labelDest = Join-Path $rawRoot "$relDir\$($j.Lbl)"
  Log (Save "$urlBase/$($j.Lbl)" $labelDest)
  if ($j.Large) {
    Log (Save "$urlBase/$($j.Prod)" (Join-Path $extRoot "$relDir\$($j.Prod)"))
  } else {
    Log (Save "$urlBase/$($j.Prod)" (Join-Path $rawRoot "$relDir\$($j.Prod)"))
  }
}

Log "DONE ok=$ok fail=$fail skip=$skip bytes=$bytes"
"SUMMARY ok=$ok fail=$fail skip=$skip bytes=$bytes" | Set-Content (Join-Path $rawRoot '_FETCH_SUMMARY.txt')
Get-Content (Join-Path $rawRoot '_FETCH_SUMMARY.txt')
