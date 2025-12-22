$localPath = "E:\Obsidian\2-1"
$remotePath = "onedriveDev:2-1"

Write-Host "Starting Sync to OneDrive (Excluding .git)..." -ForegroundColor Cyan

# Use absolute path for rclone to ensure reliability in background tasks
$rcloneExe = "C:\Users\SMTEmon\AppData\Local\Microsoft\WinGet\Packages\Rclone.Rclone_Microsoft.Winget.Source_8wekyb3d8bbwe\rclone-v1.72.1-windows-amd64\rclone.exe"

& $rcloneExe sync $localPath $remotePath -P --exclude "/.git/**" --create-empty-src-dirs

Write-Host "Sync Complete!" -ForegroundColor Green