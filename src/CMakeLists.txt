#===============================================================================
# CMakeLists for source basement
#===============================================================================
add_subdirectory(lib)
add_subdirectory(gurax)
add_subdirectory(unittest)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
#add_subdirectory(module-base64)			# built-in module
add_subdirectory(module-bmp)
add_subdirectory(module-bzip2)
add_subdirectory(module-cairo)
#add_subdirectory(module-codecs)			# built-in module
#add_subdirectory(module-codecs_basic)		# built-in module
#add_subdirectory(module-codecs_chinese)	# built-in module
#add_subdirectory(module-codecs_iso8859)	# built-in module
#add_subdirectory(module-codecs_japanese)	# built-in module
add_subdirectory(module-conio)
add_subdirectory(module-curl)
add_subdirectory(module-diff)
#add_subdirectory(module-fs)				# built-in module
add_subdirectory(module-glfw)
add_subdirectory(module-gzip)
add_subdirectory(module-hash)
add_subdirectory(module-jpeg)
add_subdirectory(module-markdown)
#add_subdirectory(module-math)				# built-in module
add_subdirectory(module-opengl)
#add_subdirectory(module-os)				# built-in module
#add_subdirectory(module-path)				# built-in module
add_subdirectory(module-png)
add_subdirectory(module-re)
add_subdirectory(module-sdl)
#add_subdirectory(module-sys)				# built-in module
add_subdirectory(module-tar)
add_subdirectory(module-zip)
endif ()
