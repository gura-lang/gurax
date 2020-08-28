#===============================================================================
# CMakeLists for module: sdl
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_sdl)

add_library(sdl.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(sdl.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/SDL2-2.0.12/include>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(sdl.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/SDL2-2.0.12/VisualC/x64/Release>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(sdl.gurd PRIVATE cxx_std_17)
target_precompile_headers(sdl.gurd PRIVATE stdafx.h)
target_compile_options(sdl.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(sdl.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(sdl.gurd PRIVATE
	module-sdl.cpp
	Util.cpp
	Functions.cpp
	VTYPE_SDL_Color.cpp
	VTYPE_SDL_DisplayMode.cpp
	VTYPE_SDL_Rect.cpp
	VTYPE_SDL_Window.cpp)

#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_libraries(sdl.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:SDL2.lib>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS sdl.gurd RUNTIME DESTINATION module/site)
