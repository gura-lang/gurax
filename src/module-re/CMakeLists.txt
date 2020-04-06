#===============================================================================
# CMakeLists for module: re
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_re)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    include_directories(${PROJECT_SOURCE_DIR}/../../guest/onigmo-6.2.0)
    link_directories(${PROJECT_SOURCE_DIR}/../../guest/onigmo-6.2.0/build_x86)
	add_definitions(-DONIG_EXTERN=extern)
	add_link_options(-LTCG -NODEFAULTLIB:LIBCMT)
    set(GUEST_LIBRARY onigmo_s)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    include_directories(${PROJECT_SOURCE_DIR}/guest/include/onigmo)
    link_directories(${PROJECT_SOURCE_DIR}/guest/lib)
    set(GUEST_LIBRARY onigmo)
else ()
    set(GUEST_LIBRARY onigmo)
endif ()
add_library(re SHARED
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
target_link_libraries(re guraxcore ${GUEST_LIBRARY})
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
install(TARGETS re RUNTIME DESTINATION module/site)
install(PROGRAMS
    script/sed.doc.gura
    script/sed.gura
    script/tokenizer.doc.gura
    script/tokenizer.gura
    DESTINATION module/site)
