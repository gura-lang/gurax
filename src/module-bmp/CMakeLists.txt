#===============================================================================
# CMakeLists for module: bmp
#===============================================================================
target_sources(guraxcore PRIVATE
	module-bmp.cpp
	ImageExtension.cpp
	Util.cpp
	Content.cpp
	VType_Content.cpp
	VType_BitmapFileHeader.cpp
	VType_BitmapInfoHeader.cpp
)

install(PROGRAMS
    script/bmp-printinfo.gura
    DESTINATION script)
