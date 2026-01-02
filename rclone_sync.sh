#!/bin/bash

# Configuration
LOCAL_PATH="/home/smtemon/Documents/Obs/1/2-1"
REMOTE_PATH="onedrive:2-1"
RCLONE_EXE="/home/smtemon/.local/bin/rclone"

echo -e "\e[36mStarting Sync to OneDrive (Excluding .git)...\e[0m"

# 1. Sync files (Upload PDFs, delete non-PDFs on remote)
$RCLONE_EXE sync "$LOCAL_PATH" "$REMOTE_PATH" -P --include "**/*.pdf" --delete-excluded

# 2. Force delete common system junk files on remote
$RCLONE_EXE delete "$REMOTE_PATH" --include "desktop.ini" --include "Thumbs.db" --include ".DS_Store"

# 3. Cleanup empty directories on OneDrive
$RCLONE_EXE rmdirs "$REMOTE_PATH" --leave-root

echo -e "\e[32mSync Complete!\e[0m"

