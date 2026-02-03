$hookPath = Join-Path $PSScriptRoot ".git\hooks\pre-push"
$syncScript = Join-Path $PSScriptRoot "sync_to_cloud.ps1"
$logFile = Join-Path $PSScriptRoot "sync_hook.log"

# Convert paths to forward slashes for the shell script
$syncScript = $syncScript -replace "\\", "/"
$logFile = $logFile -replace "\\", "/"

$hookContent = "#!/bin/sh
LOGFILE=""$logFile""
echo ""$(date): Git Push detected. Starting background sync..."" >> ""$LOGFILE""

# Run PowerShell script as a detached background process
# We use Start-Process to ensure it runs completely independently of the git process
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command ""Start-Process powershell -ArgumentList '-NoProfile -ExecutionPolicy Bypass -File \""$syncScript\""' -WindowStyle Hidden""

echo ""$(date): Sync process detached."" >> ""$LOGFILE""
"

Write-Host "Installing pre-push hook to $hookPath..."
Set-Content -Path $hookPath -Value $hookContent -NoNewline
Write-Host "Done! Sync hook is active." -ForegroundColor Green
