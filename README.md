## Setup Guide

You can set up this vault on your local machine using either the command line or directly within Obsidian using a community plugin.

### Prerequisites

1.  **Obsidian:** Download and install [Obsidian](https://obsidian.md/download).
2.  **Git:** Ensure [Git](https://git-scm.com/downloads) is installed on your system.

---

### Method 1: Using Command Line (Recommended)

This is the standard way to clone a repository.

1.  **Clone the Repository**
    Open your terminal or command prompt and run:
    ```bash
    git clone <repository-url>
    ```
    *(Replace `<repository-url>` with the actual URL of this GitHub repository)*

2.  **Open in Obsidian**
    - Launch Obsidian.
    - Click **"Open folder as vault"**.
    - Navigate to the folder you just cloned and select it.

You are now ready to browse and edit the notes!

---

### Method 2: Using Obsidian Git Plugin

If you prefer to stay within the Obsidian interface or want to sync changes easily later, you can use the community plugin.

1.  **Create a New Vault**
    - Open Obsidian.
    - Click **"Create new vault"**.
    - Give it a name (e.g., `Uni-Notes`) and pick a location.

2.  **Install Obsidian Git**
    - Go to **Settings** > **Community plugins**.
    - Turn off **"Safe mode"** (if enabled) to allow community plugins.
    - Click **"Browse"** and search for **"Obsidian Git"**.
    - Install and **Enable** the plugin.

3.  **Clone the Repository**
    - Open the Command Palette (`Ctrl/Cmd + P`).
    - Type `Git: Clone existing remote repo` and select it.
    - Enter the URL of this repository.
    - (Optional) Follow prompts to authenticate if required.
    - Restart Obsidian or reload the vault to see the files.

*Note: This method might nest the repo inside your empty vault depending on how you configure it. The CLI method is generally cleaner for initial setup.*

## Structure

- **.obsidian/**: Contains vault settings, plugins, and themes.
- **Subject Folders**: Each subject has its own folder containing markdown notes.
