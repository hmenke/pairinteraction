# SPDX-FileCopyrightText: 2026 PairInteraction Developers
# SPDX-License-Identifier: LGPL-3.0-or-later

param(
    [Parameter(Mandatory = $true)]
    [string]$SourceDir,

    [Parameter(Mandatory = $true)]
    [string]$Version,

    [Parameter(Mandatory = $true)]
    [string]$OutputDir
)

$ErrorActionPreference = "Stop"

New-Item -ItemType Directory -Force -Path $OutputDir | Out-Null

$resolvedSourceDir = (Resolve-Path $SourceDir).Path
$resolvedOutputDir = (Resolve-Path $OutputDir).Path
$innoScript = Join-Path $PSScriptRoot "PairInteraction.iss"

$innoSetup = Get-Command ISCC.exe -ErrorAction SilentlyContinue
if ($null -eq $innoSetup) {
    $defaultInnoPath = Join-Path ${env:ProgramFiles(x86)} "Inno Setup 6\ISCC.exe"
    if (-not (Test-Path $defaultInnoPath)) {
        throw "ISCC.exe was not found. Install Inno Setup before running this script."
    }
    $innoSetupPath = $defaultInnoPath
} else {
    $innoSetupPath = $innoSetup.Source
}

& $innoSetupPath "/DMyAppVersion=$Version" "/DMyAppSourceDir=$resolvedSourceDir" "/DMyAppOutputDir=$resolvedOutputDir" $innoScript
