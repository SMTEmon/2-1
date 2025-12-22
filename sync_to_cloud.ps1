$localPath = "E:\Obsidian\2-1"
$remotePath = "onedriveDev:2-1"

Write-Host "Starting Sync to OneDrive (Excluding .git)..." -ForegroundColor Cyan

# --exclude "/.git/**" excludes the .git folder at the root of the sync
# --create-empty-src-dirs ensures your folder structure is preserved
rclone sync $localPath $remotePath -P --exclude "/.git/**" --create-empty-src-dirs

Write-Host "Sync Complete!" -ForegroundColor Green