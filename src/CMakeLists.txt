#===============================================================================
# CMakeLists for source basement
#===============================================================================
add_subdirectory(lib)
add_subdirectory(gurax)
add_subdirectory(unittest)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
#add_subdirectory(module-base64)			# built-in module
#add_subdirectory(module-bmp)				# built-in module
add_subdirectory(module-bzip2)
add_subdirectory(module-cairo)
#add_subdirectory(module-codecs)			# built-in module
#add_subdirectory(module-codecs_basic)		# built-in module
#add_subdirectory(module-codecs_chinese)	# built-in module
#add_subdirectory(module-codecs_iso8859)	# built-in module
#add_subdirectory(module-codecs_japanese)	# built-in module
add_subdirectory(module-conio)
add_subdirectory(module-csv)
add_subdirectory(module-curl)
add_subdirectory(module-diff)
#add_subdirectory(module-fs)				# built-in module
add_subdirectory(module-gif)
add_subdirectory(module-glfw)
add_subdirectory(module-glu)
add_subdirectory(module-gmp)
add_subdirectory(module-gzip)
add_subdirectory(module-hash)
add_subdirectory(module-jpeg)
add_subdirectory(module-markdown)
#add_subdirectory(module-math)				# built-in module
#add_subdirectory(module-ml)
add_subdirectory(module-ml_mnist)
add_subdirectory(module-model_obj)
add_subdirectory(module-model_stl)
add_subdirectory(module-mtp)
add_subdirectory(module-opengl)
#add_subdirectory(module-os)				# built-in module
#add_subdirectory(module-path)				# built-in module
add_subdirectory(module-png)
add_subdirectory(module-re)
add_subdirectory(module-sdl)
#add_subdirectory(module-sys)				# built-in module
add_subdirectory(module-tar)
#add_subdirectory(module-wx)
add_subdirectory(module-xml)
add_subdirectory(module-xpm)
add_subdirectory(module-yaml)
add_subdirectory(module-zip)
endif ()

if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
add_subdirectory(module-markdown)
add_subdirectory(module-zip)
#add_subdirectory(module-re)
endif ()

include(CPack)
