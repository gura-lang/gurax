#===============================================================================
# CMakeLists for module: conio
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_conio)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
add_library(conio SHARED
    module-conio.cpp
    Util.cpp
)
target_link_libraries(conio guraxcore)
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
install(TARGETS conio RUNTIME DESTINATION module/site)
