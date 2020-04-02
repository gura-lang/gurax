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
    CheckPackages $packageNames
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
# CheckPackages
#------------------------------------------------------------------------------
function CheckPackages([String[]] $packageNames) {
    if ($packageNames.length -eq 0) { return True }
    foreach ($packageName in $packageNames) {
        if ($packages.name -notcontains $packageName) {
            Write-Host "unknown package: ${packageName}"
            Exit
        }
    }
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
    $progressPreferenceSaved = $global:ProgressPreference
    $global:ProgressPreference = 'silentlyContinue'
    foreach ($package in $packages) {
        if (($packageNames.length -eq 0) -or ($packageNames -contains $package.name)) {
            Write-Host "downloading: $($package.name)"
            foreach ($fileName in $package.fileNames) {
                Write-Host "  $fileName"
                Invoke-WebRequest -Uri "${urlGuest}/${fileName}" -OutFile $fileName
            }
        }
    }
    $global:ProgressPreference = $progressPreferenceSaved
}

#------------------------------------------------------------------------------
# CleanPackages
#------------------------------------------------------------------------------
function CleanPackages([String[]] $packageNames) {
    if ($packageNames.Length -eq 0) {
        $rtn = Read-Host "Are you sure to clean all the packages? [y/N]"
        if ($rtn -ne 'y') { Exit }
    }
    foreach ($package in $packages) {
        if (($packageNames.length -eq 0) -or ($packageNames -contains $package.name)) {
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
function BuildPackages([String[]] $packageNames) {
    foreach ($package in $packages) {
        if (($packageNames.length -eq 0) -or ($packageNames -contains $package.name)) {
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
        if ($fileName -match "(?<baseName>.+).tar.gz$") {
            tar -xf $fileName
        } elseif (($fileName -match "(?<baseName>.+).zip$") -or ($fileName -match "(?<baseName>.+).7z$")) {
            $baseName = $Matches['baseName']
            7z x -y -o"${baseName}" $fileName
        } else {
            Write-Host "unsupported type of archive file: ${fileName}"
            Exit
        }
    }
}

#------------------------------------------------------------------------------
# ExecCommand
# Executes an external command while displaying its progress to the console. 
#------------------------------------------------------------------------------
function ExecCommand([String] $cmd, [String] $argList) {
    Start-Process -FilePath $cmd -ArgumentList $argList -NoNewWindow -Wait
}

#---------------------------------------------------------------------------------
# Package: bzip2
#---------------------------------------------------------------------------------
class Package_bzip2 {
    [String] $name = "bzip2"
    [String] $ver = "1.0.8"
    [String] $baseName = "$($this.name)-$($this.ver)"
    [String[]] $fileNames = @("$($this.baseName).tar.gz")
    [String] $dirName = $this.baseName
    Build() {
        nmake /f makefile.msc
    }
}
$packages += [Package_bzip2]::new()

#---------------------------------------------------------------------------------
# Package: libjpeg
#---------------------------------------------------------------------------------
class Package_libjpeg {
    [String] $name = "libjpeg"
    [String] $ver = "9d"
    [String] $baseName = "jpegsrc.v$($this.ver)"
    [String[]] $fileNames = @("$($this.baseName).tar.gz")
    [String] $dirName = "jpeg-$($($this.ver))"
    Build() {
        copy jconfig.vc jconfig.h
        nmake /f makefile.vc nodebug=1
    }
}
$packages += [Package_libjpeg]::new()

#------------------------------------------------------------------------------
# Package: Onigmo
#------------------------------------------------------------------------------
class Package_onigmo {
    [String] $name = "onigmo"
    [String] $ver = "6.2.0"
    [String] $baseName = "$($this.name)-$($this.ver)"
    [String[]] $fileNames = @("$($this.baseName).tar.gz")
    [String] $dirName = $this.baseName
    Build() {
        Copy-Item win32/Makefile .
        Copy-Item win32/config.h .
        nmake
    }
}
$packages += [Package_onigmo]::new()

#---------------------------------------------------------------------------------
# Package: zlib
#---------------------------------------------------------------------------------
class Package_zlib {
    [String] $name = "zlib"
    [String] $ver = "1.2.11"
    [String] $baseName = "$($this.name)-$($this.ver)"
    [String[]] $fileNames = @("$($this.baseName).tar.gz")
    [String] $dirName = $this.baseName
    Build() {
        nmake /f win32\Makefile.msc
    }
}
$packages += [Package_zlib]::new()

#---------------------------------------------------------------------------------
# Package: wx
#---------------------------------------------------------------------------------
class Package_wx {
    [String] $name = "wx"
    [String] $ver = "3.1.3"
    [String] $baseName = "wxWidgets-$($this.ver)"
    [String[]] $fileNames = @("$($this.baseName).7z")
    [String] $dirName = $this.baseName
    Build() {
        ExecCommand msbuild 'build\msw\wx_vc16.sln /Clp:DisableConsoleColor /t:Build /p:Configuration=Release /p:Platofrm=x64'
    }
}
#$packages += [Package_wx]::new()

#------------------------------------------------------------------------------
# call main
#------------------------------------------------------------------------------
main $args
