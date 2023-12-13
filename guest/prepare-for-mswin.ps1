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
$dirToAdd = "${PSScriptRoot}\buildtools-mswin\7za920;${PSScriptRoot}\buildtools-mswin\UnxUtils;"
if (!$Env:Path.Contains($dirToAdd)) {
	$Env:Path = $dirToAdd + $Env:Path
}

#------------------------------------------------------------------------------
# main
#------------------------------------------------------------------------------
function main([String[]] $packageNames) {
	DownloadBuildTools
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
# DownloadBuildTools
#------------------------------------------------------------------------------
function DownloadBuildTools() {
	if (!(Test-Path "buildtools-mswin")) {
		git clone https://github.com/gura-lang/buildtools-mswin.git
		curl $urlGuest/buildtools-mswin/UnxUpdates.zip -o buildtools-mswin\UnxUpdates.zip
		7za x -y -obuildtools-mswin\UnxUtils buildtools-mswin\UnxUpdates.zip
	}
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
		} elseif ($fileName -match "(?<baseName>.+).tar.xz$") {
			$baseName = $Matches['baseName']
			7za x -y $fileName
			7za x -y "${baseName}.tar"
			Remove-Item -ErrorAction Ignore -Force "${baseName}.tar"
		} elseif (($fileName -match "(?<baseName>wxWidgets.+).(?<extName>7z)$")) {
			$baseName = $Matches['baseName']
			$extName = $Matches['extName']
			$fileName = "${baseName}.${extName}"
			7za x -y -o"${baseName}" "${baseName}.${extName}"
		} elseif (($fileName -match "(?<baseName>.+).(zip|7z)$")) {
			$baseName = $Matches['baseName']
			7za x -y $fileName
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
# Package: pixman
#---------------------------------------------------------------------------------
class Package_pixman {
	[String] $name = "pixman"
	[String] $ver = "0.40.0"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).tar.gz")
	[String] $dirName = $this.baseName
	Build() {
		make.exe -f Makefile.win32 MMX=off pixman
	}
}
$packages += [Package_pixman]::new()

#---------------------------------------------------------------------------------
# Package: curl
#---------------------------------------------------------------------------------
class Package_curl {
	[String] $name = "curl"
	[String] $ver = "7.73.0"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).zip")
	[String] $dirName = $this.baseName
	Build() {
		cd winbuild
		nmake /f makefile.vc mode=static
	}
}
$packages += [Package_curl]::new()

#---------------------------------------------------------------------------------
# Package: dtl
#---------------------------------------------------------------------------------
class Package_dtl {
	[String] $name = "dtl"
	[String] $ver = "1.19"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).tar.gz")
	[String] $dirName = $this.baseName
	Build() {}
}
$packages += [Package_dtl]::new()

#---------------------------------------------------------------------------------
# Package: glew
#---------------------------------------------------------------------------------
class Package_glew {
	[String] $name = "glew"
	[String] $ver = "2.1.0"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).zip")
	[String] $dirName = $this.baseName
	Build() {
		cmake -B build_work build/cmake -G Ninja
		ExecCommand ninja "-C build_work glew_s"
	}
}
$packages += [Package_glew]::new()

#---------------------------------------------------------------------------------
# Package: glfw
#---------------------------------------------------------------------------------
class Package_glfw {
	[String] $name = "glfw"
	[String] $ver = "3.3.2"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).zip")
	[String] $dirName = $this.baseName
	Build() {
		cmake -B build -G Ninja
		ExecCommand ninja "-C build"
	}
}
$packages += [Package_glfw]::new()

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

#---------------------------------------------------------------------------------
# Package: libpng
# Dependencies: zlib
#---------------------------------------------------------------------------------
class Package_libpng {
	[String] $name = "libpng"
	[String] $ver = "1.6.37"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).tar.gz", "$($this.baseName)-gurapatch-vs2019.tar.gz")
	[String] $dirName = $this.baseName
	Build() {
		msbuild projects\vstudio\vstudio.sln /clp:DisableConsoleColor /t:Build /p:Configuration="Release Library" /p:Platform=x64
	}
}
$packages += [Package_libpng]::new()

#---------------------------------------------------------------------------------
# Package: mpir
#---------------------------------------------------------------------------------
class Package_mpir {
	[String] $name = "mpir"
	[String] $ver = "3.0.0"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).zip", "$($this.baseName)-gurapatch-vs2019.zip")
	[String] $dirName = $this.baseName
	Build() {
		msbuild .\build.vc15\lib_mpir_gc\lib_mpir_gc.vcxproj /clp:DisableConsoleColor /t:Build /p:Configuration="Release" /p:Platform=x64
	}
}
$packages += [Package_mpir]::new()

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
# Package: sdl
#---------------------------------------------------------------------------------
class Package_sdl {
	[String] $name = "sdl"
	[String] $ver = "2.0.12"
	[String] $baseName = "SDL2-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).zip", "$($this.baseName)-gurapatch-vs2019.zip")
	[String] $dirName = $this.baseName
	Build() {
		msbuild VisualC\SDL.sln /clp:DisableConsoleColor /t:Build /p:Configuration="Release" /p:Platform=x64
		copy VisualC\x64\Release\SDL2.dll ..\..\bin
	}
}
$packages += [Package_sdl]::new()

#---------------------------------------------------------------------------------
# Package: sdl_image
#---------------------------------------------------------------------------------
class Package_sdl_image {
	[String] $name = "sdl_image"
	[String] $ver = "2.0.5"
	[String] $baseName = "SDL2_image-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).zip", "$($this.baseName)-gurapatch-vs2019.zip")
	[String] $dirName = $this.baseName
	Build() {
		msbuild VisualC\SDL_image.sln /clp:DisableConsoleColor /t:Build /p:Configuration="Release" /p:Platform=x64
		copy VisualC\x64\Release\*.dll ..\..\bin
	}
}
$packages += [Package_sdl_image]::new()

#---------------------------------------------------------------------------------
# Package: sdl_mixer
#---------------------------------------------------------------------------------
class Package_sdl_mixer {
	[String] $name = "sdl_mixer"
	[String] $ver = "2.0.4"
	[String] $baseName = "SDL2_mixer-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).zip", "$($this.baseName)-gurapatch-vs2019.zip")
	[String] $dirName = $this.baseName
	Build() {
		msbuild VisualC\SDL_mixer.sln /clp:DisableConsoleColor /t:Build /p:Configuration="Release" /p:Platform=x64
		copy VisualC\x64\Release\*.dll ..\..\bin
	}
}
$packages += [Package_sdl_mixer]::new()

#---------------------------------------------------------------------------------
# Package: sdl_ttf
#---------------------------------------------------------------------------------
class Package_sdl_ttf {
	[String] $name = "sdl_ttf"
	[String] $ver = "2.0.15"
	[String] $baseName = "SDL2_ttf-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).zip", "$($this.baseName)-gurapatch-vs2019.zip")
	[String] $dirName = $this.baseName
	Build() {
		msbuild VisualC\SDL_ttf.sln /clp:DisableConsoleColor /t:Build /p:Configuration="Release" /p:Platform=x64
		copy VisualC\x64\Release\*.dll ..\..\bin
	}
}
$packages += [Package_sdl_ttf]::new()

#---------------------------------------------------------------------------------
# Package: yaml
#---------------------------------------------------------------------------------
class Package_yaml {
	[String] $name = "yaml"
	[String] $ver = "0.2.5"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).zip", "$($this.baseName)-gurapatch.zip")
	[String] $dirName = $this.baseName
	Build() {
		cmake -B build -G Ninja
		ninja -C build
	}
}
$packages += [Package_yaml]::new()

#---------------------------------------------------------------------------------
# Package: cairo
# Dependencies: pixman, zlib, libpng
#---------------------------------------------------------------------------------
class Package_cairo {
	[String] $name = "cairo"
	[String] $ver = "1.16.0"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).tar.xz", "$($this.baseName)-gurapatch.tar.gz")
	[String] $dirName = $this.baseName
	Build() {
		ExecCommand make '-f .\Makefile.win32 PIXMAN_PATH=../../pixman-0.40.0 ZLIB_PATH=../../zlib-1.2.11 LIBPNG_PATH=../../libpng-1.6.37 CFG=release CFLAGS=/wd4819'
	}
}
$packages += [Package_cairo]::new()

#---------------------------------------------------------------------------------
# Package: wx
#---------------------------------------------------------------------------------
class Package_wx {
	[String] $name = "wx"
	[String] $ver = "3.1.5"
	[String] $baseName = "wxWidgets-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).7z", "$($this.baseName)-gurapatch-vs2022.zip")
	[String] $dirName = $this.baseName
	Build() {
		#ExecCommand msbuild 'build\msw\wx_vc16.sln /Clp:DisableConsoleColor /t:Build /p:Configuration="DLL Debug" /p:Platform=x64'
		msbuild build\msw\wx_vc16.sln /clp:DisableConsoleColor /t:Build /p:Configuration="DLL Release" /p:Platform=x64
		#copy lib\vc_x64_dll\*.dll ..\..\bin
	}
}
$packages += [Package_wx]::new()

#---------------------------------------------------------------------------------
# Package: expat
#---------------------------------------------------------------------------------
class Package_expat {
	[String] $name = "expat"
	[String] $ver = "2.4.9"
	[String] $baseName = "$($this.name)-$($this.ver)"
	[String[]] $fileNames = @("$($this.baseName).tar.gz")
	[String] $dirName = $this.baseName
	Build() {
		cmake -B build -DEXPAT_SHARED_LIBS=OFF -DEXPAT_MSVC_STATIC_CRT=ON .
		cmake --build build --config Release
	}
}
$packages += [Package_expat]::new()

#------------------------------------------------------------------------------
# call main
#------------------------------------------------------------------------------
main $args
