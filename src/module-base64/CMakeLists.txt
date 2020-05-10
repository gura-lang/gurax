#===============================================================================
# CMakeLists for module: base64
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_base64)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
add_library(base64 SHARED
    module-base64.cpp
    Util.cpp
)
target_link_libraries(base64 guraxcore)
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
target_precompile_headers(base64 PUBLIC stdafx.h)
install(TARGETS base64 RUNTIME DESTINATION module/site)
