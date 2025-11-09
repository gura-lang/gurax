#===============================================================================
# CMakeLists for gurax project
#===============================================================================
cmake_minimum_required(VERSION 3.16) # 3.16 or newer supports handling of precompiled header
project(gurax
	VERSION			0.0.1
	DESCRIPTION 	"Gurax Programming Language"
	HOMEPAGE_URL	http://www.gura-lang.org/
	LANGUAGES		CXX)

set(GURAX_COPYRIGHT "Copyright (C) 2011-2025 ypsitau")
set(GURAX_VERSION ${CMAKE_PROJECT_VERSION})
set(GURAX_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(GURAX_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(GURAX_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})

configure_file(
	${PROJECT_SOURCE_DIR}/include/gurax/Version.h.in
	${PROJECT_SOURCE_DIR}/include/gurax/Version.h)
if (${CMAKE_SYSTEM_NAME} STREQUAL Windows)
	set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
elseif (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
	set(CMAKE_INSTALL_PREFIX /usr)
	set(GURAX_MODULEDIR ${CMAKE_INSTALL_PREFIX}/lib/gurax/${GURAX_VERSION}/module)
	install(FILES
		${PROJECT_SOURCE_DIR}/module/argopt.gura
		${PROJECT_SOURCE_DIR}/module/cbridge.gura
		${PROJECT_SOURCE_DIR}/module/font.bdf.gura
		${PROJECT_SOURCE_DIR}/module/font.gura
		${PROJECT_SOURCE_DIR}/module/help.gura
		${PROJECT_SOURCE_DIR}/module/model.gura
		${PROJECT_SOURCE_DIR}/module/util.gura
		${PROJECT_SOURCE_DIR}/module/util.tester.gura
		DESTINATION ${GURAX_MODULEDIR}
		PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
	set(CMAKE_INSTALL_PREFIX /Applications/GURAX.app/Contents/Resources)
else ()
	set(CMAKE_INSTALL_PREFIX /usr)
endif ()

add_subdirectory(src)
