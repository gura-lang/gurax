#===============================================================================
# CMakeLists for module: markdown
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_markdown)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
include_directories(md5 sha1)
add_library(markdown SHARED
    module-markdown.cpp
    Util.cpp
    Document.cpp
    Item.cpp
    VType_Document.cpp
    VType_Item.cpp
)
target_link_libraries(markdown guraxcore)
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
install(TARGETS markdown RUNTIME DESTINATION module/site)
install(PROGRAMS
    script-module/markdown.composer.gura
    script-module/markdown.console.gura
    script-module/markdown.gura
    script-module/markdown.html.gura
    script-module/markdown.rtf.gura
    script-module/markdown.tex.gura
    script-module/markdown.toc.gura
    DESTINATION module/site)
