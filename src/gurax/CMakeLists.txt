#===============================================================================
# CMakeLists for gurax executable
#===============================================================================
add_executable(gurax gurax.cpp)
#if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
#    find_library(LIBREADLINE readline REQUIRED)
#elseif (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
#    find_library(LIBREADLINE readline REQUIRED)
#endif ()
target_link_libraries(gurax guraxcore) # ${LIBREADLINE}
install(TARGETS gurax RUNTIME DESTINATION bin)
