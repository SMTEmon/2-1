$lines = Get-Content 'E:\Obsidian\2-1\Final\4301 OOC2\Detailed\1.1 Web Services.md' -Encoding UTF8
for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i] -match 'mermaid') {
        Write-Host "Line $($i+1): $($lines[$i])"
        # Show next 5 lines
        for ($j = 0; $j -le 5; $j++) {
            $lineNum = $i + $j
            Write-Host "  [$($lineNum+1)]: $($lines[$lineNum])"
        }
        Write-Host ""
    }
}
