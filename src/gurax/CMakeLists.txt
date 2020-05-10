#===============================================================================
# CMakeLists for gurax executable
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax)

add_executable(gurax)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(gurax PRIVATE ${PROJECT_SOURCE_DIR}/../../include)
target_link_directories(gurax PRIVATE ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(gurax PRIVATE stdafx.h)
target_sources(gurax PRIVATE gurax.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
target_link_libraries(gurax PRIVATE guraxcore) # ${LIBREADLINE}
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS gurax RUNTIME DESTINATION bin)
