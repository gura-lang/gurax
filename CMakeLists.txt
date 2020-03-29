#===============================================================================
# CMakeLists for gurax project
#===============================================================================
project(gurax)

# Handling of precompiled header is supported by 3.16 or newer.
cmake_minimum_required(VERSION 3.16)

set(GURAX_VERSION_MAJOR		0)
set(GURAX_VERSION_MINOR		1)
set(GURAX_VERSION_PATCH		0)
set(GURAX_VERSION			${GURAX_VERSION_MAJOR}.${GURAX_VERSION_MINOR}.${GURAX_VERSION_PATCH})
set(GURAX_SOVERSION 		${GURAX_VERSION_MAJOR})
set(GURAX_SRCDIR_ROOT		${PROJECT_SOURCE_DIR}/src)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_INSTALL_PREFIX /Applications/GURAX.app/Contents/Resources)
else ()
	set(CMAKE_INSTALL_PREFIX /usr)
endif ()

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)
