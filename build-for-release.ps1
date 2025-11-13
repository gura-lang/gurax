if (Test-Path build-for-release) {
    Remove-Item build-for-release -Force -Recurse
}
cmake -S . -B build-for-release
cmake --build build-for-release --config Release --parallel
Push-Location build-for-release
cpack -C Release
Pop-Location
Copy-Item build-for-release/gurax-*.exe .
