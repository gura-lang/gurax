#===============================================================================
# CMakeLists for png module
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_png)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    include_directories(${PROJECT_SOURCE_DIR}/../../guest/libpng-1.6.37)
    link_directories("${PROJECT_SOURCE_DIR}/../../guest/libpng-1.6.37/projects/vstudio/x64/Release Library")
    set(GUEST_LIBRARY libpng16)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(${PROJECT_SOURCE_DIR}/guest/include/libpng)
    link_directories("${PROJECT_SOURCE_DIR}/guest/lib")
    set(GUEST_LIBRARY png16)
else ()
    set(GUEST_LIBRARY png16)
endif ()
add_library(png SHARED
    module-png.cpp
    Util.cpp
)
target_link_libraries(png guraxcore ${GUEST_LIBRARY})
add_definitions("-DGURAX_MODULE_SEPARATED")
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
install(TARGETS png RUNTIME DESTINATION module/site)
