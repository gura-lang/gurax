#==============================================================================
# Script to Set-up Guest Packages for MS Windows
#==============================================================================

#------------------------------------------------------------------------------
# Global variables
#------------------------------------------------------------------------------
Param([String] $cmd)
$urlGuest = "https://www.gura-lang.org/guest"
$packages = @()
$dirName = "${PSScriptRoot}\include"
if ($Env:INCLUDE.Split(";") -notcontains $dirName) {
    $Env:INCLUDE += ";" + $dirName
}
#Write-Host $Env:INCLUDE

#------------------------------------------------------------------------------
# main
#------------------------------------------------------------------------------
function main() {
    switch ($cmd) {
        "clean" {
            CleanPackages
        }
        default {
            DownloadPackages
            BuildPackages
        }
    }
}

#------------------------------------------------------------------------------
# DownloadPackages
#------------------------------------------------------------------------------
function DownloadPackages() {
    foreach ($package in $packages) {
        foreach ($fileName in $package.fileNames) {
            Write-Output $fileName
            Invoke-WebRequest -Uri "${urlGuest}/${fileName}" -OutFile $fileName
        }
    }
}

#------------------------------------------------------------------------------
# CleanPackages
#------------------------------------------------------------------------------
function CleanPackages() {
    foreach ($package in $packages) {
        Write-Output "clean: $($package.name)"
        Remove-Item -ErrorAction Ignore -Force -Recurse $package.dirName
    }
}

#------------------------------------------------------------------------------
# BuildPackages
#------------------------------------------------------------------------------
function BuildPackages() {
    foreach ($package in $packages) {
        ExpandFiles $package.fileNames
        Push-Location $package.dirName
        $package.Build()
        Pop-Location
    }
}

#------------------------------------------------------------------------------
# ExpandFiles
#------------------------------------------------------------------------------
function ExpandFiles([String[]] $fileNames) {
    foreach ($fileName in $fileNames) {
        Write-Host "expand: ${fileName}"
        if ($fileName -like "*.tar.gz") {
            tar -xf $fileName
        } elseif (($fileName -match "(.+).zip$") -or ($fileName -match "(.+).7z$")) {
            $baseName = $Matches[1]
            7z x -y -o"${baseName}" $fileName
        }
    }
}

#------------------------------------------------------------------------------
# Package: Onigmo
#------------------------------------------------------------------------------
class Package_onigmo {
    [String] $name = "onigmo"
    [String] $ver = "6.2.0"
    [String] $fullName = "$($this.name)-$($this.ver)"
    [String[]] $fileNames = @("$($this.fullName).tar.gz")
    [String] $dirName = $this.fullName
    Build() {
        Copy-Item win32/Makefile .
        Copy-Item win32/config.h .
        nmake
    }
}
$packages += [Package_onigmo]::new()

#---------------------------------------------------------------------------------
# Package: jpegsrc
#---------------------------------------------------------------------------------
class Package_jpegsrc {
    [String] $name = "jpegsrc"
    [String] $ver = "9d"
    [String] $fullName = "$($this.name).v$($this.ver)"
    [String[]] $fileNames = @("$($this.fullName).tar.gz")
    [String] $dirName = "jpeg-$($($this.ver))"
    Build() {
        copy jconfig.vc jconfig.h
        nmake -f makefile.vc nodebug=1
    }
}
$packages += [Package_jpegsrc]::new()

main
