param(
  [string[]]$Symbols = @('H', 'He', 'Li', 'Be', 'B', 'C', 'N', 'O', 'F', 'Ne'),
  [int]$LevelCount = 20,
  [string]$OutputPath = (Join-Path $PSScriptRoot 'data/nist-neutral-excitation-map.json')
)

$ErrorActionPreference = 'Stop'
$atomicNumbers = @{ H = 1; He = 2; Li = 3; Be = 4; B = 5; C = 6; N = 7; O = 8; F = 9; Ne = 10 }
$elements = [ordered]@{}

foreach ($symbol in $Symbols) {
  if (-not $atomicNumbers.ContainsKey($symbol)) { throw "No atomic number is registered for $symbol." }
  $url = "https://physics.nist.gov/cgi-bin/ASD/energy1.pl?spectrum=$symbol+I&units=1&format=3&output=0&page_size=1000&multiplet_ordered=0&conf_out=on&term_out=on&level_out=on&j_out=on&unc_out=1&submit=Retrieve+Data"
  $rows = (Invoke-WebRequest -UseBasicParsing -Uri $url -TimeoutSec 60).Content | ConvertFrom-Csv -Delimiter "`t"
  $limitRow = $rows | Where-Object { $_.Term -eq 'Limit' } | Select-Object -First 1
  if (-not $limitRow) { throw "$symbol I has no ionization limit in the NIST response." }
  $ionizationLimitEv = [double]$limitRow.'Level (eV)'
  $candidates = @()
  foreach ($row in $rows) {
    if ([string]::IsNullOrWhiteSpace($row.Term)) { continue }
    $levelEv = 0.0
    if (-not [double]::TryParse([string]$row.'Level (eV)', [ref]$levelEv)) { continue }
    if ($levelEv -le 0 -or $levelEv -ge $ionizationLimitEv) { continue }
    $candidates += [pscustomobject][ordered]@{
      configuration = [string]$row.Configuration
      term = [string]$row.Term
      j = [string]$row.J
      excitation_ev = $levelEv
      uncertainty_ev = if ([string]::IsNullOrWhiteSpace($row.'Uncertainty (eV)')) { $null } else { [double]$row.'Uncertainty (eV)' }
      evaluation_status = if ($row.Prefix -eq '[' -or $row.Suffix -eq ']') { 'bracketed_evaluated' } else { 'unbracketed_evaluated' }
    }
  }
  $levels = @()
  foreach ($candidate in ($candidates | Sort-Object excitation_ev | Select-Object -First $LevelCount)) {
    $levels += [ordered]@{
      index = $levels.Count + 1
      configuration = $candidate.configuration
      term = $candidate.term
      j = $candidate.j
      excitation_ev = $candidate.excitation_ev
      uncertainty_ev = $candidate.uncertainty_ev
      evaluation_status = $candidate.evaluation_status
    }
  }
  if ($levels.Count -ne $LevelCount) { throw "$symbol I supplied only $($levels.Count) bound levels." }
  $elements[$symbol] = [ordered]@{
    atomic_number = $atomicNumbers[$symbol]
    spectrum = "$symbol I"
    ionization_limit_ev = $ionizationLimitEv
    ionization_limit_uncertainty_ev = if ([string]::IsNullOrWhiteSpace($limitRow.'Uncertainty (eV)')) { $null } else { [double]$limitRow.'Uncertainty (eV)' }
    levels = $levels
    source_url = $url
  }
}

$document = [ordered]@{
  schema_version = '1.0.0'
  retrieved_utc = (Get-Date).ToUniversalTime().ToString('yyyy-MM-ddTHH:mm:ssZ')
  source = [ordered]@{
    title = 'NIST Atomic Spectra Database neutral-atom energy levels'
    citation = 'Kramida, A., Ralchenko, Yu., Reader, J., and NIST ASD Team (2024), NIST ASD ver. 5.12, DOI 10.18434/T4W30F'
    interpretation = 'NIST evaluated spectroscopic levels. Bracketed values are retained and explicitly tagged; they are not relabelled as direct trajectory measurements.'
  }
  level_count_per_element = $LevelCount
  elements = $elements
}

$json = $document | ConvertTo-Json -Depth 8
[IO.File]::WriteAllText([IO.Path]::GetFullPath($OutputPath), $json + "`n", [Text.UTF8Encoding]::new($false))
Write-Output "Wrote $($elements.Count) elements and $($elements.Count * $LevelCount) excitation levels to $OutputPath"
