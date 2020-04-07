#===============================================================================
# CMakeLists for guest library
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_hash_guest)

add_library(guest STATIC md5/md5.c sha1/sha1.c)
