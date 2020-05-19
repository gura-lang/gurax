#===============================================================================
# CMakeLists for module: base64
#===============================================================================
target_sources(guraxcore PRIVATE
	module-base64.cpp
	Util.cpp
)

install(PROGRAMS
    script/base64encode.gura
    script/base64decode.gura
    DESTINATION script)
