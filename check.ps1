$lines = Get-Content 'E:\Obsidian\2-1\Final\4301 OOC2\Detailed\1.1 Web Services.md' -Encoding UTF8
for ($i = 30; $i -le 36; $i++) {
    $line = $lines[$i]
    $hex = [System.BitConverter]::ToString([System.Text.Encoding]::UTF8.GetBytes($line))
    Write-Host "Line $($i+1): $hex"
}
