#===============================================================================
# CMakeLists for module: bmp
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_bmp)

install(PROGRAMS
    script/bmp-printinfo.gura
    DESTINATION script)
