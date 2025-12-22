$localPath = "E:\Obsidian\2-1"
$remotePath = "onedriveDev:2-1"

Write-Host "Starting Sync to OneDrive (Excluding .git)..." -ForegroundColor Cyan

# Use absolute path for rclone to ensure reliability in background tasks
$rcloneExe = "C:\Users\SMTEmon\AppData\Local\Microsoft\WinGet\Packages\Rclone.Rclone_Microsoft.Winget.Source_8wekyb3d8bbwe\rclone-v1.72.1-windows-amd64\rclone.exe"

# 1. Sync files (Upload PDFs, delete non-PDFs on remote)
& $rcloneExe sync $localPath $remotePath -P --include "**/*.pdf" --delete-excluded

# 2. Force delete common system junk files on remote that might prevent folder deletion
& $rcloneExe delete $remotePath --include "desktop.ini" --include "Thumbs.db" --include ".DS_Store"

# 3. Cleanup empty directories on OneDrive
& $rcloneExe rmdirs $remotePath --leave-root

Write-Host "Sync Complete!" -ForegroundColor Green