#===============================================================================
# CMakeLists for module: re
# debFiles = ['libonig']
# rpmFiles = ['oniguruma']
# debFilesDevel = ['libonig-dev']
# rpmFilesDevel = ['oniguruma-devel']
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_re)

add_library(re.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if (PROJECT_IS_TOP_LEVEL)
	execute_process(COMMAND gurax --naked -p "sys.dirModule.Chop()" OUTPUT_VARIABLE GURAX_MODULEDIR)
	execute_process(COMMAND gurax --naked -p "sys.version" OUTPUT_VARIABLE GURAX_VERSION)
else()
	set(GURAX_VERSION ${CMAKE_PROJECT_VERSION})
endif()
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(GURAX_MODULEDIR ${GURAX_BASEDIR}/module/site)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(GURAX_MODULEDIR ${CMAKE_INSTALL_PREFIX}/lib/gurax/${GURAX_VERSION}/module/site)
endif()
target_include_directories(re.gurd PRIVATE
	${GURAX_BASEDIR}/include
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/onigmo-6.2.0>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest/include/onigmo>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest/include/onigmo>)
target_link_directories(re.gurd PRIVATE
	${GURAX_BASEDIR}/lib
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/onigmo-6.2.0/build_x86>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest/lib>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest/lib>)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(re.gurd PRIVATE cxx_std_17)
target_precompile_headers(re.gurd PRIVATE stdafx.h)
target_compile_options(re.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(re.gurd PRIVATE GURAX_MODULE_SEPARATED
    $<$<PLATFORM_ID:Windows>:ONIG_EXTERN=extern>)
target_sources(re.gurd PRIVATE
    module-re.cpp
    Util.cpp
    Group.cpp
    Iterators.cpp
    Match.cpp
    Pattern.cpp
    VType_Group.cpp
    VType_Match.cpp
    VType_Pattern.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(re.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:LIBCMT -LTCG -INCREMENTAL:NO>)
target_link_libraries(re.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:onigmo_s>
	$<$<PLATFORM_ID:Linx>:onig>
	$<$<PLATFORM_ID:Darwin>:onig>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS re.gurd LIBRARY DESTINATION ${GURAX_MODULEDIR})
install(FILES
    script/sed.doc.gura
    script/sed.gura
    script/tokenizer.doc.gura
    script/tokenizer.gura
    DESTINATION ${GURAX_MODULEDIR}
	PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE)
