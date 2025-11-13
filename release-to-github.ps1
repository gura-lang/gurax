# Release a new version to GitHub Releases
if ($args.Count -eq 0) {
    Write-Host "Usage: .\release-github.ps1 TAG-NAME"
    Write-Host "Example: .\release-github.ps1 v1.0.0"
    exit 1
}
$tagName = $args[0]
gh release create $tagName ./build-for-release/*.exe --generate-notes --title $tagName --draft --prerelease
