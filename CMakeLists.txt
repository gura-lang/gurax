#===============================================================================
# CMakeLists for gurax project
#===============================================================================
cmake_minimum_required(VERSION 3.16) # 3.16 or newer supports handling of precompiled header
project(Gurax
	VERSION			0.1.0
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

add_subdirectory(src)

if(${CMAKE_SYSTEM_NAME} MATCHES Windows)
	set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
	install(DIRECTORY ${PROJECT_SOURCE_DIR}/bin/
		DESTINATION bin
		FILES_MATCHING
		PATTERN "*.dll"
		PATTERN "*.exe"
		PATTERN ".gitkeep" EXCLUDE)
	install(DIRECTORY ${PROJECT_SOURCE_DIR}/module/
		DESTINATION module
		FILES_MATCHING
		PATTERN "*.gura")
	install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
		DESTINATION include
		FILES_MATCHING
		PATTERN "*.h")
	# Include Visual C++ Runtime redistributable
	include(InstallRequiredSystemLibraries)
	if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
		install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
			DESTINATION bin
			COMPONENT Runtime)
	endif()
	set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
	set(CPACK_PACKAGE_INSTALL_DIRECTORY "gurax")
	set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
	set(CPACK_NSIS_PACKAGE_NAME "Gurax")
	set(CPACK_NSIS_DISPLAY_NAME "Gurax ${GURAX_VERSION}")
	set(CPACK_NSIS_MODIFY_PATH ON)
	set(CPACK_NSIS_MENU_LINKS "")
	set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.md")
	set(CPACK_PACKAGE_FILE_NAME "gurax-${GURAX_VERSION}-x64")
elseif(${CMAKE_SYSTEM_NAME} MATCHES Linux)
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
elseif(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
	set(CMAKE_INSTALL_PREFIX /Applications/GURAX.app/Contents/Resources)
else ()
	set(CMAKE_INSTALL_PREFIX /usr)
endif()

include(CPack)
