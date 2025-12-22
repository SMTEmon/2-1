$folderToWatch = "E:\Obsidian\2-1\.git"
$scriptToRun = "E:\Obsidian\2-1\sync_to_cloud.ps1"

# Create a FileSystemWatcher to monitor Git changes
$watcher = New-Object System.IO.FileSystemWatcher
$watcher.Path = $folderToWatch
$watcher.IncludeSubdirectories = $true
$watcher.EnableRaisingEvents = $true

# Define the action to take when a change is detected
$action = {
    $path = $Event.SourceEventArgs.FullPath
    # Filter out irrelevant temporary git files to avoid loops or excessive syncing
    if ($path -notmatch "\.lock$" -and $path -notmatch "COMMIT_EDITMSG") {
        Write-Host "Git activity detected at $(Get-Date). Triggering OneDrive Sync..." -ForegroundColor Cyan
        
        # Debounce: Wait a few seconds to let Git finish its operations
        Start-Sleep -Seconds 5
        
        # Run the sync script
        powershell.exe -NoProfile -ExecutionPolicy Bypass -File $scriptToRun
    }
}

# Register events for file changes (Changed, Created, Deleted)
Register-ObjectEvent $watcher "Changed" -Action $action
Register-ObjectEvent $watcher "Created" -Action $action
Register-ObjectEvent $watcher "Deleted" -Action $action

Write-Host "Watching $folderToWatch for Git activity..." -ForegroundColor Green

# Keep the script running indefinitely
while ($true) { Start-Sleep -Seconds 60 }
