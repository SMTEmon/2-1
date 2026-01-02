#!/bin/bash

# Configuration
LOCAL_PATH="/home/smtemon/Documents/Obs/1/2-1"
REMOTE_PATH="onedrive:2-1"
RCLONE_EXE="/home/smtemon/.local/bin/rclone"

echo -e "\e[36mStarting Sync from OneDrive to Local...\e[0m"

# Sync Cloud -> Local (Download PDFs)
# We use --include "**/*.pdf" to only download PDFs as per your setup
$RCLONE_EXE sync "$REMOTE_PATH" "$LOCAL_PATH" -P --include "**/*.pdf" 

echo -e "\e[32mSync Complete!\e[0m"

