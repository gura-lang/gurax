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
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/SDL2_image-2.0.5>
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/SDL2_mixer-2.0.4>
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/SDL2_ttf-2.0.15>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(sdl.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/SDL2-2.0.12/VisualC/x64/Release>
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/SDL2_image-2.0.5/VisualC/x64/Release>
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/SDL2_mixer-2.0.4/VisualC/x64/Release>
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/SDL2_ttf-2.0.15/VisualC/x64/Release>
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
	Consts.cpp
	VType_SDL_AudioCVT.cpp
	VType_SDL_AudioSpec.cpp
	VType_SDL_AudioStream.cpp
	VType_SDL_Color.cpp
	VType_SDL_Cursor.cpp
	VType_SDL_DisplayMode.cpp
	VType_SDL_Event.cpp
	VType_SDL_FPoint.cpp
	VType_SDL_FRect.cpp
	VType_SDL_GameController.cpp
	VType_SDL_GLContext.cpp
	VType_SDL_Haptic.cpp
	VType_SDL_HapticDirection.cpp
	VType_SDL_HapticEffect.cpp
	VType_SDL_HapticConstant.cpp
	VType_SDL_Joystick.cpp
	VType_SDL_JoystickGUID.cpp
	VType_SDL_Keysym.cpp
	VType_SDL_Palette.cpp
	VType_SDL_PixelFormat.cpp
	VType_SDL_Point.cpp
	VType_SDL_Rect.cpp
	VType_SDL_Renderer.cpp
	VType_SDL_RendererInfo.cpp
	VType_SDL_RWops.cpp
	VType_SDL_Sensor.cpp
	VType_SDL_Surface.cpp
	VType_SDL_SysWMinfo.cpp
	VType_SDL_Texture.cpp
	VType_SDL_version.cpp
	VType_SDL_Window.cpp
	VType_SDL_CommonEvent.cpp
	VType_SDL_WindowEvent.cpp
	VType_SDL_KeyboardEvent.cpp
	VType_SDL_TextEditingEvent.cpp
	VType_SDL_TextInputEvent.cpp
	VType_SDL_MouseMotionEvent.cpp
	VType_SDL_MouseButtonEvent.cpp
	VType_SDL_MouseWheelEvent.cpp
	VType_SDL_JoyAxisEvent.cpp
	VType_SDL_JoyBallEvent.cpp
	VType_SDL_JoyHatEvent.cpp
	VType_SDL_JoyButtonEvent.cpp
	VType_SDL_JoyDeviceEvent.cpp
	VType_SDL_ControllerAxisEvent.cpp
	VType_SDL_ControllerButtonEvent.cpp
	VType_SDL_ControllerDeviceEvent.cpp
	VType_SDL_AudioDeviceEvent.cpp
	VType_SDL_QuitEvent.cpp
	VType_SDL_UserEvent.cpp
	VType_SDL_SysWMEvent.cpp
	VType_SDL_TouchFingerEvent.cpp
	VType_SDL_MultiGestureEvent.cpp
	VType_SDL_DollarGestureEvent.cpp
	VType_SDL_DropEvent.cpp
	VType_Mix_Chunk.cpp
	VType_Mix_Music.cpp
	VType_TTF_Font.cpp)

#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_libraries(sdl.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:SDL2.lib>
	$<$<PLATFORM_ID:Windows>:SDL2_image.lib>
	$<$<PLATFORM_ID:Windows>:SDL2_mixer.lib>
	$<$<PLATFORM_ID:Windows>:SDL2_ttf.lib>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS sdl.gurd RUNTIME DESTINATION module/site)
