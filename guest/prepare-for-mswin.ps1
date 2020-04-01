#==============================================================================
# Script to Set-up Guest Packages for MS Windows
#==============================================================================

#------------------------------------------------------------------------------
# Command-line parameter
#------------------------------------------------------------------------------
Param([switch]$help, [switch] $list, [switch] $download, [switch] $clean, [switch] $build)

#------------------------------------------------------------------------------
# Global variables
#------------------------------------------------------------------------------
$urlGuest = "https://www.gura-lang.org/guest"
$packages = @()
$dirName = "${PSScriptRoot}\include"
if ($Env:INCLUDE.Split(";") -notcontains $dirName) {
    $Env:INCLUDE += ";" + $dirName
}

#------------------------------------------------------------------------------
# main
#------------------------------------------------------------------------------
function main([String[]] $packageNames) {
    if ($help) {
        PrintHelp
    } elseif ($list) {
        ListPackages
    } elseif ($download) {
        DownloadPackages $packageNames
    } elseif ($clean) {
        CleanPackages $packageNames
    } elseif ($build) {
        BuildPackages $packageNames
    } else {
        DownloadPackages $packageNames
        BuildPackages $packageNames
    }
}

#------------------------------------------------------------------------------
# PrintHelp
#------------------------------------------------------------------------------
function PrintHelp() {
    Write-Host "usage: prepare-for-mswin.ps1 [options]"
    Write-Host "[options]"
    Write-Host " -help"
    Write-Host " -list"
    Write-Host " -clean [packages*]"
    Write-Host " -download [packages*]"
    Write-Host " -build [packages*]"
}

#------------------------------------------------------------------------------
# ListPackages
#------------------------------------------------------------------------------
function ListPackages() {
    foreach ($package in $packages) {
        Write-Host $package.name
    }
}

#------------------------------------------------------------------------------
# DownloadPackages
#------------------------------------------------------------------------------
function DownloadPackages([String[]] $packageNames) {
    foreach ($package in $packages) {
        if (($packageNames.length -eq 0) -or ($packageNames -contains $package.name)) {
            Write-Host "downloading: $($package.name)"
            foreach ($fileName in $package.fileNames) {
                Write-Host "  $fileName"
                Invoke-WebRequest -Uri "${urlGuest}/${fileName}" -OutFile $fileName
            }
        }
    }
}

#------------------------------------------------------------------------------
# CleanPackages
#------------------------------------------------------------------------------
function CleanPackages([String] $packageName) {
    foreach ($package in $packages) {
        if (($packageName.Length -eq 0) -or ($package.name -eq $packageName)) {
            foreach ($fileName in $package.fileNames) {
                Remove-Item -ErrorAction Ignore -Force $fileName
            }
            Remove-Item -ErrorAction Ignore -Force -Recurse $package.dirName
            Write-Host "cleaned: $($package.name)"
        }
    }
}

#------------------------------------------------------------------------------
# BuildPackages
#------------------------------------------------------------------------------
function BuildPackages([String] $packageName) {
    foreach ($package in $packages) {
        if (($packageName.Length -eq 0) -or ($package.name -eq $packageName)) {
            Write-Host "-------------------------------------------"
            Write-Host "building: $($package.name)"
            ExpandFiles $package.fileNames
            Push-Location $package.dirName
            $package.Build()
            Pop-Location
        }
    }
}

#------------------------------------------------------------------------------
# ExpandFiles
#------------------------------------------------------------------------------
function ExpandFiles([String[]] $fileNames) {
    foreach ($fileName in $fileNames) {
        if ($fileName -like "*.tar.gz") {
            tar -xf $fileName
        } elseif (($fileName -match "(.+).zip$") -or ($fileName -match "(.+).7z$")) {
            $baseName = $Matches[1]
            7z x -y -o"${baseName}" $fileName
        }
    }
}

#---------------------------------------------------------------------------------
# Package: bzip2
#---------------------------------------------------------------------------------
class Package_bzip2 {
    [String] $name = "bzip2"
    [String] $ver = "1.0.8"
    [String] $fullName = "$($this.name)-$($this.ver)"
    [String[]] $fileNames = @("$($this.fullName).tar.gz")
    [String] $dirName = $this.fullName
    Build() {
        nmake /nologo /f makefile.msc
    }
}
$packages += [Package_bzip2]::new()

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
        nmake /nologo /f makefile.vc nodebug=1
    }
}
$packages += [Package_jpegsrc]::new()

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
        nmake /nologo
    }
}
$packages += [Package_onigmo]::new()

#---------------------------------------------------------------------------------
# Package: zlib
#---------------------------------------------------------------------------------
class Package_zlib {
    [String] $name = "zlib"
    [String] $ver = "1.2.11"
    [String] $fullName = "$($this.name)-$($this.ver)"
    [String[]] $fileNames = @("$($this.fullName).tar.gz")
    [String] $dirName = $this.fullName
    Build() {
        nmake /nologo /f win32\Makefile.msc
    }
}
$packages += [Package_zlib]::new()

#------------------------------------------------------------------------------
# call main
#------------------------------------------------------------------------------
main $args
